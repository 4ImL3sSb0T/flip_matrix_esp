#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "service/tools/common_def.h"

#define TCP_SERVER_MAX_CLIENTS  4

typedef void (*tcp_on_data_cb_t)(int client_sock, const char *data, int len);
typedef void (*tcp_on_connect_cb_t)(int client_sock, const char *ip_str);
typedef void (*tcp_on_disconnect_cb_t)(int client_sock);

typedef struct {
    tcp_on_data_cb_t       on_data;
    tcp_on_connect_cb_t    on_connect;
    tcp_on_disconnect_cb_t on_disconnect;
} tcp_server_callbacks_t;

exit_code_t tcp_server_init(uint16_t port, const tcp_server_callbacks_t *cbs);
exit_code_t tcp_server_start(void);
exit_code_t tcp_server_deinit(void);

exit_code_t tcp_server_send(int client_sock, const void *data, int len);

#endif
