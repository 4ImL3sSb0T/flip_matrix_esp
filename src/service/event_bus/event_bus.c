#include "event_bus.h"
#include <string.h>

typedef struct {
    eventbus_id_t id;
    eventbus_handler_t cb;
    void *user_ctx;
    bool used;
} subscriber_t;

// 哨兵事件：module_id=0xFFFF, event_id=0xFFFF 用于通知任务退出
#define POISON_MODULE_ID 0xFFFF
#define POISON_EVENT_ID  0xFFFF
static QueueHandle_t s_evt_queue = NULL;
static TaskHandle_t s_evt_task = NULL;
static SemaphoreHandle_t s_sub_lock = NULL;

static subscriber_t s_subscribers[EVENTBUS_MAX_SUBSCRIBERS];
static uint16_t s_next_module_id = 1;
static TaskHandle_t s_deinit_waiter = NULL;
static eventbus_event_t s_poison_evt;
static eventbus_event_t *const POISON_PTR = &s_poison_evt;

static volatile bool s_running = false;

static uint32_t get_time_ms(void) {
    return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static void eventbus_task(void *arg) {
    eventbus_event_t *evt;

    while (1) {
        if (xQueueReceive(s_evt_queue, &evt, portMAX_DELAY) == pdTRUE) {

            if (evt == POISON_PTR) {
                break;
            }

            subscriber_t matched[EVENTBUS_MAX_SUBSCRIBERS];
            int match_count = 0;

            xSemaphoreTake(s_sub_lock, portMAX_DELAY);
            for (int i = 0; i < EVENTBUS_MAX_SUBSCRIBERS; i++) {
                if (s_subscribers[i].used &&
                    s_subscribers[i].id.module_id == evt->id.module_id &&
                    (s_subscribers[i].id.event_id == EVENTBUS_EVENT_ID_ALL ||
                     s_subscribers[i].id.event_id == evt->id.event_id)) {
                    matched[match_count++] = s_subscribers[i];
                }
            }
            xSemaphoreGive(s_sub_lock);

            for (int i = 0; i < match_count; i++) {
                matched[i].cb(evt, matched[i].user_ctx);
            }

            vPortFree(evt);
        }
    }

    if (s_deinit_waiter) {
        xTaskNotifyGive(s_deinit_waiter);
    }

    vTaskDelete(NULL);
}

exit_code_t eventbus_init(uint32_t queue_len, UBaseType_t task_prio, uint32_t task_stack) {
    if (s_evt_queue) return EXIT_ALREADY_INITIALIZED;
    s_evt_queue = xQueueCreate(queue_len, sizeof(eventbus_event_t *));
    if (!s_evt_queue) return EXIT_FAIL;
    s_sub_lock = xSemaphoreCreateMutex();
    if (!s_sub_lock) {
        vQueueDelete(s_evt_queue);
        s_evt_queue = NULL;
        return EXIT_FAIL;
    }
    memset(s_subscribers, 0, sizeof(s_subscribers));
    s_next_module_id = 1;
    if (xTaskCreate(eventbus_task, "eventbus_task", task_stack, NULL, task_prio, &s_evt_task) != pdPASS) {
        vQueueDelete(s_evt_queue);
        s_evt_queue = NULL;
        vSemaphoreDelete(s_sub_lock);
        s_sub_lock = NULL;
        return EXIT_FAIL;
    }
    s_running = true;
    return EXIT_OK;
}

exit_code_t eventbus_deinit() {   
    if (!s_evt_queue) return EXIT_NOT_INITIALIZED;
    s_running = false;
    s_deinit_waiter = xTaskGetCurrentTaskHandle();

    // 如果队列满了，丢弃一个旧事件腾空间（并释放内存）
    eventbus_event_t *drop;
    if (uxQueueSpacesAvailable(s_evt_queue) == 0) {
        if (xQueueReceive(s_evt_queue, &drop, 0) == pdTRUE) {
            if (drop != POISON_PTR) {
                vPortFree(drop);
            }
        }
    }

    if (xQueueSend(s_evt_queue, &POISON_PTR, pdMS_TO_TICKS(100)) != pdTRUE) {
        s_deinit_waiter = NULL;
        return EXIT_FAIL;
    }

    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    eventbus_event_t *remaining;
    while (xQueueReceive(s_evt_queue, &remaining, 0) == pdTRUE) {
        if (remaining != POISON_PTR) {
            vPortFree(remaining);
        }
    }

    vQueueDelete(s_evt_queue);
    s_evt_queue = NULL;

    if (s_sub_lock) {
        vSemaphoreDelete(s_sub_lock);
        s_sub_lock = NULL;
    }

    s_evt_task = NULL;
    s_deinit_waiter = NULL;


    return EXIT_OK;
}

exit_code_t eventbus_publish(eventbus_id_t id, const void *payload, uint32_t len, TickType_t timeout) {
    if (!s_evt_queue) return EXIT_NOT_INITIALIZED;
    if (!s_running) return EXIT_NOT_INITIALIZED;
    // if (len > EVENTBUS_MAX_PAYLOAD_SIZE) return EXIT_INVALID_PARAM;
    // 按实际 payload 长度分配，无 payload 时柔性数组占 0 字节
    eventbus_event_t *evt = pvPortMalloc(sizeof(eventbus_event_t) + len);
    if (!evt) return EXIT_FAIL;
    evt->id = id;
    evt->timestamp_ms = get_time_ms();
    evt->payload_len = len;
    if (payload && len > 0) {
        memcpy(evt->payload, payload, len);
    }
    if (xQueueSend(s_evt_queue, &evt, timeout) != pdTRUE) {
        vPortFree(evt);
        return EXIT_FAIL;
    }
    return EXIT_OK;
}
exit_code_t eventbus_subscribe(eventbus_id_t id, eventbus_handler_t handler, void *user_ctx) {
    if (!s_sub_lock) return EXIT_NOT_INITIALIZED;
    if (!handler) return EXIT_INVALID_PARAM;
    xSemaphoreTake(s_sub_lock, portMAX_DELAY);
    for (int index = 0; index < EVENTBUS_MAX_SUBSCRIBERS; index++) {
        if (!s_subscribers[index].used) {
            s_subscribers[index].id = id;
            s_subscribers[index].cb = handler;
            s_subscribers[index].user_ctx = user_ctx;
            s_subscribers[index].used = true;
            xSemaphoreGive(s_sub_lock);
            return EXIT_OK;
        }
    }
    xSemaphoreGive(s_sub_lock);
    return EXIT_FAIL;
}
exit_code_t eventbus_unsubscribe(eventbus_id_t id, eventbus_handler_t handler) {
    if (!s_sub_lock) return EXIT_NOT_INITIALIZED;
    if (!handler) return EXIT_INVALID_PARAM;
    xSemaphoreTake(s_sub_lock, portMAX_DELAY);
    for (int index = 0; index < EVENTBUS_MAX_SUBSCRIBERS; index++) {
        if (s_subscribers[index].used && s_subscribers[index].id.module_id == id.module_id && s_subscribers[index].id.event_id == id.event_id && s_subscribers[index].cb == handler) {
            s_subscribers[index].used = false;
            xSemaphoreGive(s_sub_lock);
            return EXIT_OK;
        }
    }
    xSemaphoreGive(s_sub_lock);
    return EXIT_FAIL;
}
exit_code_t eventbus_allocate_module_id(uint16_t *module_id) {
    if (!module_id) return EXIT_INVALID_PARAM;
    if (!s_sub_lock) return EXIT_NOT_INITIALIZED;
    xSemaphoreTake(s_sub_lock, portMAX_DELAY);
    *module_id = s_next_module_id++;
    xSemaphoreGive(s_sub_lock);
    return EXIT_OK;
}
eventbus_id_t eventbus_make_event_id(uint16_t module_id, uint16_t event_id) {
    eventbus_id_t evt_id;
    evt_id.module_id = module_id;
    evt_id.event_id = event_id;
    return evt_id;
}