#ifndef _WIFI_BSP_H_
#define _WIFI_BSP_H_

#include "service/tools/common_def.h"

exit_code_t wifi_bsp_init(void);
exit_code_t wifi_bsp_deinit(void);
exit_code_t wifi_bsp_connect(const char *ssid, const char *password);
exit_code_t wifi_bsp_disconnect(void);

#endif
