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

#include "bsp/motor/motor.h"
#include <math.h>

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

static void uart2tcp_task(void *arg)
{
    const int uart_num = UART_NUM_2;
    const int uart_buffer_size = (1024 * 2);
    const int uart_rx_pin = 16;
    const int uart_tx_pin = 17;

    static uint8_t rx_buf[512];

    QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
    
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, uart_rx_pin, uart_tx_pin, -1, -1));

    ESP_LOGI("UART2TCP", "UART2 to TCP bridge started on UART2 (RX=%d, TX=%d)", uart_rx_pin, uart_tx_pin);
    while (1) {
        int len = uart_read_bytes(uart_num, rx_buf, sizeof(rx_buf), pdMS_TO_TICKS(100));
        if (len > 0) {
            tcp_server_broadcast(rx_buf, len);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }

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
    exit_code_t imu_ret = imu_service_init(&imu963ra_sensor);
    if (imu_ret != EXIT_OK) {
        // IMU没有安装就开启串口转TCP服务，方便调试
        xTaskCreatePinnedToCore(uart2tcp_task, "uart2tcp_task", 4096, NULL, 5, NULL, 1);
        ESP_LOGE("MAIN", "Failed to initialize IMU service");
    }
    imu_service_start();

    // 流体仿真（从 ring buffer 读取 IMU 数据）
    // xTaskCreatePinnedToCore(start_flip_task, "flip_task", 4096, NULL, 5, NULL, 1);
    // xTaskCreatePinnedToCore(cpu_monitor_task, "cpu_mon", 4096, NULL, 3, NULL, 0);

    xTaskCreatePinnedToCore(sp_process_task, "sp_process_task", 4096, NULL, 4, NULL, 1);

    motor_config_t motor_cfg = {
        .pwm_gpio = 21,
        .dir_gpio = 20,
        .channel = LEDC_CHANNEL_0,
        .dir_invert = false,
    };

    exit_code_t motor_ret = motor_init(&motor_cfg);
    if (motor_ret != EXIT_OK) {
        ESP_LOGE("MAIN", "Failed to initialize motor");
        return;
    }

    while (1) {
        float duty = -(0.2f * fabs(sin(0.0001f * xTaskGetTickCount())) + 0.1f);
        motor_set_duty(LEDC_CHANNEL_0, duty);  // 让CNN神经网络更好地学习, T = 12.3s
        vTaskDelay(pdTICKS_TO_MS(10));
        ESP_LOGI("MAIN", "Set motor duty: %.2f%%", duty * 100);
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    esp_system_abort("stack overflow");
}