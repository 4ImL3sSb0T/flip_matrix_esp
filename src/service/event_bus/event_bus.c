#include "event_bus.h"
#include <string.h>

typedef struct {
    eventbus_id_t id;
    eventbus_handler_t cb;
    void *user_ctx;
    bool used;
} subscriber_t;

static QueueHandle_t s_evt_queue = NULL;
static TaskHandle_t s_evt_task = NULL;
static SemaphoreHandle_t s_sub_lock = NULL;

static subscriber_t s_subscribers[EVENTBUS_MAX_SUBSCRIBERS];

static uint32_t get_time_ms(void) {
    return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

static void eventbus_task(void *arg) {
    eventbus_event_t evt;
    while (1) {
        if (xQueueReceive(s_evt_queue, &evt, portMAX_DELAY) == pdTRUE) {
            for (int index = 0; index < EVENTBUS_MAX_SUBSCRIBERS; index++) {
                xSemaphoreTake(s_sub_lock, portMAX_DELAY);
                if (s_subscribers[index].used && s_subscribers[index].id.module_id == evt.id.module_id && s_subscribers[index].id.event_id == evt.id.event_id) {
                    s_subscribers[index].cb(&evt, s_subscribers[index].user_ctx);
                }
                xSemaphoreGive(s_sub_lock);
            }
        }
    }
}

exit_code_t eventbus_init(uint32_t queue_len, UBaseType_t task_prio, uint32_t task_stack) {
    if (s_evt_queue) return EXIT_ALREADY_INITIALIZED;

    s_evt_queue = xQueueCreate(queue_len, sizeof(eventbus_event_t));
    if (!s_evt_queue) return EXIT_FAIL;

    s_sub_lock = xSemaphoreCreateMutex();
    if (!s_sub_lock) return EXIT_FAIL;

    memset(s_subscribers, 0, sizeof(s_subscribers));

    if (xTaskCreate(eventbus_task, "eventbus_task", task_stack, NULL, task_prio, &s_evt_task) != pdPASS) {
        vQueueDelete(s_evt_queue);
        s_evt_queue = NULL;
        vSemaphoreDelete(s_sub_lock);
        s_sub_lock = NULL;
        return EXIT_FAIL;
    }
    return EXIT_OK;
}
exit_code_t eventbus_deinit() {
    if (!s_evt_queue) return EXIT_NOT_INITIALIZED;
    vQueueDelete(s_evt_queue);
    s_evt_queue = NULL;

    if (s_sub_lock) {
        vSemaphoreDelete(s_sub_lock);
        s_sub_lock = NULL;
    }

    if (s_evt_task) {
        vTaskDelete(s_evt_task);
        s_evt_task = NULL;
    }
    return EXIT_OK;
}
exit_code_t eventbus_publish(eventbus_id_t id, const void *payload, uint32_t len, TickType_t timeout) {
    if (!s_evt_queue) return EXIT_NOT_INITIALIZED;
    if (len > EVENTBUS_MAX_PAYLOAD_SIZE) return EXIT_INVALID_PARAM;

    eventbus_event_t evt;
    evt.id = id;
    evt.timestamp_ms = get_time_ms();
    if (payload && len > 0) {
        memcpy(evt.payload, payload, len);
    }
    evt.payload_len = len;

    if (xQueueSend(s_evt_queue, &evt, timeout) != pdTRUE) {
        return EXIT_FAIL;
    }
    return EXIT_OK;
}
exit_code_t eventbus_subscribe(eventbus_id_t id, eventbus_handler_t handler, void *user_ctx) {
    if (!s_sub_lock) return EXIT_NOT_INITIALIZED;
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
    static uint16_t next_module_id = 1; // 从1开始分配，0保留给特殊用途
    if (!module_id) return EXIT_INVALID_PARAM;
    *module_id = next_module_id++;
	return EXIT_OK;
}

eventbus_id_t eventbus_make_event_id(uint16_t module_id, uint16_t event_id) {
	eventbus_id_t evt_id;
    evt_id.module_id = module_id;
    evt_id.event_id = event_id;
    return evt_id;
}
