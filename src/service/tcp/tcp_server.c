#include "tcp_server.h"

#include <string.h>
#include <errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"

#include "service/event_bus/event_bus.h"
#include "service/wifi/wifi_service.h"

#define TAG "TCP_SVC"
#define INVALID_SOCK (-1)

#define TCP_NOTIFY_START  1
#define TCP_NOTIFY_STOP   0

static uint16_t s_event_base_id = 0;
static TaskHandle_t s_task_handle = NULL;

static uint16_t s_port = 0;
static tcp_server_callbacks_t s_cbs = {0};

// ── WiFi 事件回调 ───────────────────────────────────────────────────────────

static void wifi_event_handler(const eventbus_event_t *evt, void *ctx)
{
    if (!s_task_handle) return;

    if (evt->id.event_id == WIFI_SVC_EVENT_CONNECTED) {
        xTaskNotify(s_task_handle, TCP_NOTIFY_START, eSetValueWithOverwrite);
    } else if (evt->id.event_id == WIFI_SVC_EVENT_DISCONNECTED) {
        xTaskNotify(s_task_handle, TCP_NOTIFY_STOP, eSetValueWithOverwrite);
    }
}

// ── 工具函数 ────────────────────────────────────────────────────────────────

static inline char *get_client_ip(struct sockaddr_storage *addr, char *buf, size_t len)
{
    if (addr->ss_family == PF_INET) {
        inet_ntoa_r(((struct sockaddr_in *)addr)->sin_addr, buf, len - 1);
    } else {
        buf[0] = '\0';
    }
    return buf;
}

static void set_nonblocking(int sock)
{
    int flags = fcntl(sock, F_GETFL);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

static void close_all_clients(int *clients, int listen_sock)
{
    for (int i = 0; i < TCP_SERVER_MAX_CLIENTS; i++) {
        if (clients[i] != INVALID_SOCK) {
            if (s_cbs.on_disconnect) {
                s_cbs.on_disconnect(clients[i]);
            }
            close(clients[i]);
            clients[i] = INVALID_SOCK;
        }
    }
    if (listen_sock != INVALID_SOCK) {
        close(listen_sock);
    }
}

// ── TCP server 主任务 ───────────────────────────────────────────────────────

static void tcp_server_task(void *arg)
{
    int clients[TCP_SERVER_MAX_CLIENTS];
    for (int i = 0; i < TCP_SERVER_MAX_CLIENTS; i++) {
        clients[i] = INVALID_SOCK;
    }

    while (1) {
        // 等待 WiFi 连接事件
        uint32_t notify_val = 0;
        xTaskNotifyWait(0, ULONG_MAX, &notify_val, portMAX_DELAY);
        if (notify_val != TCP_NOTIFY_START) {
            continue;
        }
        ESP_LOGI(TAG, "WiFi connected, starting server on port %d", s_port);

        // 创建 listener socket
        int listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        if (listen_sock < 0) {
            ESP_LOGE(TAG, "socket() failed: errno %d", errno);
            continue;
        }

        int opt = 1;
        setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        struct sockaddr_in dest_addr = {
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_family = AF_INET,
            .sin_port = htons(s_port),
        };

        if (bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) != 0) {
            ESP_LOGE(TAG, "bind() failed: errno %d", errno);
            close(listen_sock);
            continue;
        }

        if (listen(listen_sock, 1) != 0) {
            ESP_LOGE(TAG, "listen() failed: errno %d", errno);
            close(listen_sock);
            continue;
        }

        set_nonblocking(listen_sock);
        ESP_LOGI(TAG, "Listening on port %d", s_port);

        // select 主循环
        while (1) {
            fd_set read_fds;
            FD_ZERO(&read_fds);
            FD_SET(listen_sock, &read_fds);
            int max_fd = listen_sock;

            for (int i = 0; i < TCP_SERVER_MAX_CLIENTS; i++) {
                if (clients[i] != INVALID_SOCK) {
                    FD_SET(clients[i], &read_fds);
                    if (clients[i] > max_fd) {
                        max_fd = clients[i];
                    }
                }
            }

            struct timeval tv = { .tv_sec = 1, .tv_usec = 0 };
            int ret = select(max_fd + 1, &read_fds, NULL, NULL, &tv);

            // 检查 WiFi 断开通知
            uint32_t notify = 0;
            if (xTaskNotifyWait(0, ULONG_MAX, &notify, 0) == pdTRUE) {
                if (notify == TCP_NOTIFY_STOP) {
                    ESP_LOGW(TAG, "WiFi disconnected, closing server");
                    close_all_clients(clients, listen_sock);
                    listen_sock = INVALID_SOCK;
                    break;
                }
            }

            if (ret < 0) {
                ESP_LOGE(TAG, "select() failed: errno %d", errno);
                break;
            }
            if (ret == 0) {
                continue;  // 超时，继续检查通知
            }

            // accept 新连接
            if (FD_ISSET(listen_sock, &read_fds)) {
                struct sockaddr_storage source_addr;
                socklen_t addr_len = sizeof(source_addr);
                int new_sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);

                if (new_sock >= 0) {
                    int slot = -1;
                    for (int i = 0; i < TCP_SERVER_MAX_CLIENTS; i++) {
                        if (clients[i] == INVALID_SOCK) {
                            slot = i;
                            break;
                        }
                    }

                    if (slot >= 0) {
                        set_nonblocking(new_sock);
                        clients[slot] = new_sock;

                        char ip_str[64];
                        get_client_ip(&source_addr, ip_str, sizeof(ip_str));
                        ESP_LOGI(TAG, "[sock=%d] Client connected from %s", new_sock, ip_str);

                        if (s_cbs.on_connect) {
                            s_cbs.on_connect(new_sock, ip_str);
                        }
                    } else {
                        ESP_LOGW(TAG, "Max clients reached, rejecting connection");
                        close(new_sock);
                    }
                }
            }

            // 处理已有客户端数据
            for (int i = 0; i < TCP_SERVER_MAX_CLIENTS; i++) {
                if (clients[i] == INVALID_SOCK || !FD_ISSET(clients[i], &read_fds)) {
                    continue;
                }

                char rx_buffer[256];
                int len = recv(clients[i], rx_buffer, sizeof(rx_buffer) - 1, 0);

                if (len > 0) {
                    rx_buffer[len] = '\0';
                    if (s_cbs.on_data) {
                        s_cbs.on_data(clients[i], rx_buffer, len);
                    }
                } else if (len == 0) {
                    ESP_LOGI(TAG, "[sock=%d] Client disconnected", clients[i]);
                    if (s_cbs.on_disconnect) {
                        s_cbs.on_disconnect(clients[i]);
                    }
                    close(clients[i]);
                    clients[i] = INVALID_SOCK;
                } else {
                    if (errno != EAGAIN && errno != EWOULDBLOCK) {
                        ESP_LOGE(TAG, "[sock=%d] recv() error: errno %d", clients[i], errno);
                        if (s_cbs.on_disconnect) {
                            s_cbs.on_disconnect(clients[i]);
                        }
                        close(clients[i]);
                        clients[i] = INVALID_SOCK;
                    }
                }
            }
        }

        // 清理（WiFi 断开跳出循环后）
        if (listen_sock != INVALID_SOCK) {
            close(listen_sock);
        }
        for (int i = 0; i < TCP_SERVER_MAX_CLIENTS; i++) {
            if (clients[i] != INVALID_SOCK) {
                close(clients[i]);
                clients[i] = INVALID_SOCK;
            }
        }
    }
}

// ── 服务接口 ────────────────────────────────────────────────────────────────

exit_code_t tcp_server_init(uint16_t port, const tcp_server_callbacks_t *cbs)
{
    if (!cbs) return EXIT_INVALID_PARAM;

    s_port = port;
    s_cbs = *cbs;

    eventbus_allocate_module_id(&s_event_base_id);

    eventbus_subscribe(
        eventbus_make_event_id(WIFI_EVENT_BASE_ID, EVENTBUS_EVENT_ID_ALL),
        wifi_event_handler, NULL);

    ESP_LOGI(TAG, "TCP server init (port=%d, module_id=%d)", port, s_event_base_id);
    return EXIT_OK;
}

exit_code_t tcp_server_start(void)
{
    BaseType_t ret = xTaskCreatePinnedToCore(
        tcp_server_task, "tcp_srv", 4096, NULL, 4, &s_task_handle, 0);
    if (ret != pdPASS) {
        ESP_LOGE(TAG, "Failed to create task");
        return EXIT_FAIL;
    }

    ESP_LOGI(TAG, "TCP server task started");
    return EXIT_OK;
}

exit_code_t tcp_server_deinit(void)
{
    if (s_task_handle) {
        xTaskNotify(s_task_handle, TCP_NOTIFY_STOP, eSetValueWithOverwrite);
        vTaskDelay(pdMS_TO_TICKS(200));
        vTaskDelete(s_task_handle);
        s_task_handle = NULL;
    }

    eventbus_unsubscribe(
        eventbus_make_event_id(WIFI_EVENT_BASE_ID, EVENTBUS_EVENT_ID_ALL),
        wifi_event_handler);

    s_port = 0;
    memset(&s_cbs, 0, sizeof(s_cbs));

    ESP_LOGI(TAG, "TCP server deinitialized");
    return EXIT_OK;
}

exit_code_t tcp_server_send(int client_sock, const void *data, int len)
{
    if (client_sock < 0 || !data || len <= 0) return EXIT_INVALID_PARAM;

    int written = send(client_sock, data, len, 0);
    if (written < 0) {
        ESP_LOGE(TAG, "[sock=%d] send() failed: errno %d", client_sock, errno);
        return EXIT_FAIL;
    }
    return EXIT_OK;
}
