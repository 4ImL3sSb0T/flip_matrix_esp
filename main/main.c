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
#include "bsp/imu963ra/zf_device_imu963ra.h"
#include "driver/uart.h"
#include "service/event_bus/event_bus.h"
#include "service/wifi/wifi_service.h"
#include <stdlib.h>

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

void led_task(void *pvParameter)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = GPIO_NUM_48, // The GPIO that connected to the LED strip's data line
        .max_leds = 1,      // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812,        // LED strip model
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color order of the strip: GRB
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000, // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
        .mem_block_symbols = 0, // let the driver choose a proper memory block size automatically
        .flags = {
            .with_dma = false,
        }
    };

    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ESP_LOGI("example", "Created LED strip object with RMT backend");

    int hue = 0, saturation = 255, value = 100;
    static int count = 0;
    while (1) {
        esp_err_t err;
        err = led_strip_set_pixel_hsv(led_strip, 0, hue, saturation, value);
        if (err != ESP_OK) { ESP_LOGE("example", "set_pixel failed: %s", esp_err_to_name(err)); }
        err = led_strip_refresh(led_strip);
        if (err != ESP_OK) { ESP_LOGE("example", "refresh failed: %s", esp_err_to_name(err)); }
        vTaskDelay(pdTICKS_TO_MS(20));

        err = led_strip_clear(led_strip);
        if (err != ESP_OK) { ESP_LOGE("example", "clear failed: %s", esp_err_to_name(err)); }
        err = led_strip_refresh(led_strip);
        if (err != ESP_OK) { ESP_LOGE("example", "refresh2 failed: %s", esp_err_to_name(err)); }

        hue = (hue + 1) % 360;
        // saturation = (saturation + 10) % 255;
        // value = (value + 51) % 255;
        
        ESP_LOGI("LED", "Updated LED color to R:%d, G:%d, B:%d", hue, saturation, value);
        ESP_LOGI("LED", "LED task running... Count: %d", count++);
    }
}

void start_flip_task(void *pvParameter)
{

    wifi_service_init();
    wifi_service_start();

    shell_port_init();
    shell_port_start();

    static imu_sensor_t imu963ra_sensor = {
        .imu_init = imu963ra_init,
        .imu_deinit = imu963ra_deinit,
        .imu_get_acc = imu963ra_read_acc,
        .imu_get_gyro = imu963ra_read_gyro,
        .imu_get_mag = imu963ra_read_mag,
        .is_initialized = false,
    };
    imu_service_init(&imu963ra_sensor);
    imu_service_start();

    app_water_sim_init();
    app_water_sim_start();

    while (1) {
        vec3f euler;
        imu_service_get_euler(&euler);
        ESP_LOGI("IMU", "Euler angles: Roll: %.2f, Pitch: %.2f, Yaw: %.2f", euler.x, euler.y, euler.z);
        vTaskDelay(pdTICKS_TO_MS(200));
    }
}


void app_main(void)
{
    eventbus_init(16, 12, 4096);
    uart_async_init();
    uart_async_start();
    // xTaskCreatePinnedToCore(led_task, "led_task", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(start_flip_task, "flip_task", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(cpu_monitor_task, "cpu_mon", 4096, NULL, 3, NULL, 0);
    while (1) {
        // ESP_LOGI("main", "Main task running... Count: %d", count++);
        vTaskDelay(pdTICKS_TO_MS(10));
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    esp_system_abort("stack overflow");
}