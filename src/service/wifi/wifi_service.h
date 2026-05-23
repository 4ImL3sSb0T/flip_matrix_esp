#ifndef _WIFI_SERVICE_H_
#define _WIFI_SERVICE_H_

#include "service/tools/common_def.h"
#include "service/event_bus/event_bus.h"

extern uint16_t WIFI_EVENT_BASE_ID;

typedef enum {
    WIFI_STATE_DISCONNECTED,
    WIFI_STATE_CONNECTING,
    WIFI_STATE_CONNECTED,
    WIFI_STATE_FAILED,
} wifi_state_t;

typedef enum : uint32_t {
    WIFI_EVENT_CONNECTED,
    WIFI_EVENT_DISCONNECTED,
    WIFI_EVENT_GOT_IP,
    WIFI_EVENT_FAILED,
} wifi_event_t;

exit_code_t wifi_service_init(void);
exit_code_t wifi_service_start(void);
exit_code_t wifi_service_deinit(void);

wifi_state_t wifi_service_get_state(void);

#endif
