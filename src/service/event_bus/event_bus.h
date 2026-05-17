#ifndef _EVENT_BUS_H_
#define _EVENT_BUS_H_

#include "service/tools/common_def.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

// 最大订阅者数量（工程可调）
#define EVENTBUS_MAX_SUBSCRIBERS  32
// #define EVENTBUS_MAX_PAYLOAD_SIZE 64

typedef struct {
    uint16_t module_id;
    uint16_t event_id;
} eventbus_id_t;

typedef struct {
    eventbus_id_t id;
    uint32_t timestamp_ms;
    uint32_t payload_len;
    uint8_t payload[];
} eventbus_event_t;

typedef void (*eventbus_handler_t)(const eventbus_event_t *evt, void *user_ctx);

exit_code_t eventbus_init(uint32_t queue_len, UBaseType_t task_prio, uint32_t task_stack);
exit_code_t eventbus_deinit();
exit_code_t eventbus_publish(eventbus_id_t id, const void *payload, uint32_t len, TickType_t timeout);
exit_code_t eventbus_subscribe(eventbus_id_t id, eventbus_handler_t handler, void *user_ctx);
exit_code_t eventbus_unsubscribe(eventbus_id_t id, eventbus_handler_t handler);
exit_code_t eventbus_allocate_module_id(uint16_t *module_id);
eventbus_id_t eventbus_make_event_id(uint16_t module_id, uint16_t event_id);

#endif