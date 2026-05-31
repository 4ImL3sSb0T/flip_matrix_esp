#include "imu_data_process.h"
#include "service/imu/imu_service.h"
#include "service/tools/vec_math.h"
#include "service/tcp/tcp_server.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>

static const char *TAG = "IMU_DSP";

void imu_dsp_process(void *pvParameter) {
    MessageBufferHandle_t acc_buf = imu_service_get_acc_buffer();

    if (!acc_buf) {
        ESP_LOGE(TAG, "acc ring buffer not initialized");
        vTaskDelete(NULL);
        return;
    }

    vec3f batch[120];
    int total = 0;
    TickType_t last_print = xTaskGetTickCount();

    while (1) {
        size_t n = xMessageBufferReceive(acc_buf, batch, sizeof(batch), pdMS_TO_TICKS(50));
        if (n > 0) {
            total += n / sizeof(vec3f);
        }

        if (xTaskGetTickCount() - last_print >= pdMS_TO_TICKS(1000)) {
            ESP_LOGI(TAG, "acc samples/s: %d", total);
            total = 0;
            last_print = xTaskGetTickCount();
        }
    }
}
