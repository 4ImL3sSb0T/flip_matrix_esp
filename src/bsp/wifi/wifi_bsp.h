#ifndef _WIFI_BSP_H_
#define _WIFI_BSP_H_

#include "service/tools/common_def.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

exit_code_t wifi_bsp_init(void);
exit_code_t wifi_bsp_deinit(void);
exit_code_t wifi_bsp_connect(const char *ssid, const char *password);
exit_code_t wifi_bsp_disconnect(void);

void wifi_bsp_set_service_task(TaskHandle_t task);
bool wifi_bsp_wait_disconnect(TickType_t timeout);

#endif
