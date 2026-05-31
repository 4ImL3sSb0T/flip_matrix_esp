#include "imu_data_process.h"
#include "esp_log.h"
#include "esp_dsp.h"

static const char *TAG = "IMU_DSP";
static const uint32_t IMU_FIFO_BATCH_MAX = 120;

void imu_dsp_process(void *pvParameter) {
    StreamBufferHandle_t fifo_buffer = imu_service_get_fifo_buffer();

    if (fifo_buffer == NULL) {
        ESP_LOGE("IMU_DSP", "FIFO buffer not initialized");
        vTaskDelete(NULL);
        return;
    }
    imu_sample_t samples[IMU_FIFO_BATCH_MAX];

    while (1) {
        size_t bytes_received = xStreamBufferReceive(fifo_buffer, samples, sizeof(samples), portMAX_DELAY);
        if (bytes_received > 0) {
            int sample_count = bytes_received / sizeof(imu_sample_t);
            ESP_LOGI(TAG, "Received %d samples from FIFO", sample_count);

            // 这里可以添加对 samples 的 DSP 处理逻辑
            // 例如：滤波、特征提取、状态检测等
        }
    }
}