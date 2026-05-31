#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "led_strip_rmt.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_console.h"

#include "bsp/uart/uart_async.h"
#include "service/cli/port/shell_port.h"
#include "app/app_water_sim.h"
#include "service/matrix/matrix.h"
#include "service/imu/imu_service.h"
#include "bsp/imu963ra/imu963ra.h"
#include "driver/uart.h"
#include "service/event_bus/event_bus.h"
#include "service/wifi/wifi_service.h"
#include "service/tcp/tcp_server.h"
#include <stdlib.h>
#include <service/signal_process/imu_data_process.h>

// ── CPU 运行时监控 ──────────────────────────────────────────────────────────
#define MON_TAG       "CPU"
#define MON_BUF_SIZE  512

static void cpu_monitor_task(void *arg)
{
    TaskStatus_t *status_a = NULL, *status_b = NULL;
    UBaseType_t prev_num = 0;

    // 延迟 1s 让系统先跑起来，采集的是稳态数据
    vTaskDelay(pdMS_TO_TICKS(1000));

    while (1) {
        // ── 采样 A ──
        UBaseType_t num = uxTaskGetNumberOfTasks();
        if (num > prev_num) {
            free(status_a);
            free(status_b);
            status_a = malloc(sizeof(TaskStatus_t) * num);
            status_b = malloc(sizeof(TaskStatus_t) * num);
            prev_num = num;
        }

        uint32_t total_a = 0;
        UBaseType_t n_a = 0;
        if (status_a) {
            n_a = uxTaskGetSystemState(status_a, num, &total_a);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));

        // ── 采样 B ──
        uint32_t total_b = 0;
        UBaseType_t n_b = 0;
        if (status_b) {
            n_b = uxTaskGetSystemState(status_b, num, &total_b);
        }

        if (!status_a || !status_b || n_a == 0 || n_b == 0)
            continue;

        uint32_t total_delta = total_b - total_a;
        if (total_delta == 0)
            continue;

        // ── 对齐 A/B 中的 task handle，计算差值 ──
        ESP_LOGI(MON_TAG, "------------------------------------");
        ESP_LOGI(MON_TAG, "%-16s %8s", "Task", "% CPU");

        for (UBaseType_t i = 0; i < n_b; i++) {
            // 在 A 中找同一个 task
            uint32_t run_a = 0;
            for (UBaseType_t j = 0; j < n_a; j++) {
                if (status_a[j].xHandle == status_b[i].xHandle) {
                    run_a = status_a[j].ulRunTimeCounter;
                    break;
                }
            }

            uint32_t run_delta = status_b[i].ulRunTimeCounter - run_a;
            int pct = (int)((run_delta * 100) / total_delta);

            if (pct > 0) {
                ESP_LOGI(MON_TAG, "%-16s %7d%%",
                         status_b[i].pcTaskName, pct);
            }
        }

        // ── 堆内存 ──
        ESP_LOGI(MON_TAG, "Heap free: %d  (low: %d)",
                 (int)esp_get_free_heap_size(),
                 (int)esp_get_minimum_free_heap_size());
    }
}

// ── TCP server 回调（留空，由用户填充业务逻辑）──────────────────────────────
static void tcp_on_data(int client_sock, const char *data, int len)
{
    ESP_LOGI("TCP", "[sock=%d] Received %d bytes: %.*s", client_sock, len, len, data);
}

static void tcp_on_connect(int client_sock, const char *ip_str)
{
    ESP_LOGI("TCP", "[sock=%d] Client connected: %s", client_sock, ip_str);
}

static void tcp_on_disconnect(int client_sock)
{
    ESP_LOGI("TCP", "[sock=%d] Client disconnected", client_sock);
}

void start_flip_task(void *pvParameter)
{
    app_water_sim_init();
    app_water_sim_start();
    vTaskDelete(NULL);
}


void app_main(void)
{
    eventbus_init(16, 12, 4096);

    uart_async_init();
    uart_async_start();

    wifi_service_init();
    wifi_service_start();

    static tcp_server_callbacks_t tcp_cbs = {
        .on_data       = tcp_on_data,
        .on_connect    = tcp_on_connect,
        .on_disconnect = tcp_on_disconnect,
    };

    tcp_server_init(8080, &tcp_cbs);
    tcp_server_start();

    // shell_port_init();
    // shell_port_start();

    // IMU 服务（FIFO 轮询，数据写入 ring buffer）
    static imu_sensor_t imu963ra_sensor = {
        .imu_init = imu963ra_init,
        .imu_deinit = imu963ra_deinit,
        .imu_get_mag = imu963ra_read_mag,
    };
    imu_service_init(&imu963ra_sensor);
    imu_service_start();

    // 流体仿真（从 ring buffer 读取 IMU 数据）
    // xTaskCreatePinnedToCore(start_flip_task, "flip_task", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(cpu_monitor_task, "cpu_mon", 4096, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(imu_dsp_process, "imu_dsp", 4096, NULL, 4, NULL, 1);

    while (1) {
        vTaskDelay(pdTICKS_TO_MS(10));
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    esp_system_abort("stack overflow");
}