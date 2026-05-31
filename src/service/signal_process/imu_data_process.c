#include "imu_data_process.h"
#include "service/imu/imu_service.h"
#include "service/tools/vec_math.h"
#include "esp_log.h"

static const char *TAG = "IMU_DSP";

void imu_dsp_process(void *pvParameter) {
    StreamBufferHandle_t acc_buf = imu_service_get_acc_buffer();

    if (!acc_buf) {
        ESP_LOGE(TAG, "acc ring buffer not initialized");
        vTaskDelete(NULL);
        return;
    }

    vec3f batch[120];

    while (1) {
        size_t n = xStreamBufferReceive(acc_buf, batch, sizeof(batch), pdMS_TO_TICKS(50));
        if (n > 0) {
            int count = n / sizeof(vec3f);
            ESP_LOGI(TAG, "acc: %d samples", count);
            // DSP 处理...
        }
    }
}
