#include "imu_service.h"
#include "bsp/imu963ra/imu963ra.h"
#include "bsp/imu963ra/lsm6dsr_reg.h"
#include "service/event_bus/event_bus.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/stream_buffer.h"
#include "esp_log.h"

#define TAG "IMU_SVC"

// ── 配置 ──────────────────────────────────────────────────────────────────────
#define IMU_FIFO_WATERMARK      100
#define IMU_RING_BUF_ITEMS      1024

// ── 静态变量 ──────────────────────────────────────────────────────────────────
static imu_sensor_t *s_sensor = NULL;
static StreamBufferHandle_t s_acc_ring_buf = NULL;
static stmdev_ctx_t s_dev_ctx;
static uint16_t s_event_base_id = 0;

// ── lsm6dsr_reg 平台回调 ──────────────────────────────────────────────────────

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
    uint8_t tx_buf[32];  // lsm6dsr 单次写入不会超过几个字节
    tx_buf[0] = reg;
    memcpy(tx_buf + 1, bufp, len);
    spi_transaction_t t = {
        .length = 8 * (1 + len),
        .tx_buffer = tx_buf,
    };
    return (spi_device_transmit(*(spi_device_handle_t *)handle, &t) == ESP_OK) ? 0 : -1;
}

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
    uint8_t tx_buf[32] = {0};
    uint8_t rx_buf[32];
    tx_buf[0] = reg | 0x80;
    spi_transaction_t t = {
        .length = 8 * (1 + len),
        .tx_buffer = tx_buf,
        .rx_buffer = rx_buf,
    };
    if (spi_device_transmit(*(spi_device_handle_t *)handle, &t) != ESP_OK) return -1;
    memcpy(bufp, rx_buf + 1, len);
    return 0;
}

static void platform_delay(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

// ── FIFO 轮询任务 ────────────────────────────────────────────────────────────

static void imu_fifo_task(void *arg)
{
    spi_device_handle_t spi_handle = imu963ra_get_spi_handle();
    s_dev_ctx.write_reg = platform_write;
    s_dev_ctx.read_reg  = platform_read;
    s_dev_ctx.mdelay    = platform_delay;
    s_dev_ctx.handle    = &spi_handle;

    // 传感器基本配置
    uint8_t whoamI, rst;
    lsm6dsr_device_id_get(&s_dev_ctx, &whoamI);
    ESP_LOGI(TAG, "WHO_AM_I = 0x%02X", whoamI);

    lsm6dsr_reset_set(&s_dev_ctx, PROPERTY_ENABLE);
    do { lsm6dsr_reset_get(&s_dev_ctx, &rst); } while (rst);

    lsm6dsr_i3c_disable_set(&s_dev_ctx, LSM6DSR_I3C_DISABLE);
    lsm6dsr_block_data_update_set(&s_dev_ctx, PROPERTY_ENABLE);

    // 量程
    lsm6dsr_xl_full_scale_set(&s_dev_ctx, LSM6DSR_8g);
    lsm6dsr_gy_full_scale_set(&s_dev_ctx, LSM6DSR_2000dps);

    // FIFO 配置
    lsm6dsr_fifo_watermark_set(&s_dev_ctx, IMU_FIFO_WATERMARK);
    lsm6dsr_fifo_xl_batch_set(&s_dev_ctx, LSM6DSR_XL_BATCHED_AT_6667Hz);
    lsm6dsr_fifo_gy_batch_set(&s_dev_ctx, LSM6DSR_GY_BATCHED_AT_6667Hz);
    lsm6dsr_fifo_mode_set(&s_dev_ctx, LSM6DSR_STREAM_MODE);

    // ODR 启动
    lsm6dsr_xl_data_rate_set(&s_dev_ctx, LSM6DSR_XL_ODR_6667Hz);
    lsm6dsr_gy_data_rate_set(&s_dev_ctx, LSM6DSR_GY_ODR_6667Hz);

    // ── 中断模式代码（注释保留）─────────────────────────────────────────────
    // lsm6dsr_pin_int1_route_t int1_route;
    // lsm6dsr_pin_int1_route_get(&s_dev_ctx, &int1_route);
    // int1_route.reg.int1_ctrl.int1_fifo_th = PROPERTY_ENABLE;
    // lsm6dsr_pin_int1_route_set(&s_dev_ctx, &int1_route);
    //
    // static TaskHandle_t s_task_handle = NULL;
    // static void IRAM_ATTR imu_int1_isr(void *arg) {
    //     BaseType_t woken = pdFALSE;
    //     vTaskNotifyGiveFromISR(s_task_handle, &woken);
    //     if (woken) portYIELD_FROM_ISR();
    // }
    // s_task_handle = xTaskGetCurrentTaskHandle();
    // gpio_install_isr_service(0);
    // gpio_isr_handler_add(IMU963RA_INT1_PIN, imu_int1_isr, NULL);
    // ── 中断模式结束 ─────────────────────────────────────────────────────────

    ESP_LOGI(TAG, "FIFO task started: ODR=6667Hz, watermark=%d, poll=50ms", IMU_FIFO_WATERMARK);

    // 主循环
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(50));

        // [中断模式替代: ulTaskNotifyTake(pdTRUE, portMAX_DELAY)]

        uint8_t wmflag = 0;
        lsm6dsr_fifo_wtm_flag_get(&s_dev_ctx, &wmflag);
        if (wmflag == 0) continue;

        uint16_t num = 0;
        lsm6dsr_fifo_data_level_get(&s_dev_ctx, &num);

        while (num--) {
            lsm6dsr_fifo_tag_t tag;
            lsm6dsr_fifo_sensor_tag_get(&s_dev_ctx, &tag);
            uint8_t raw[6];

            switch (tag) {
            case LSM6DSR_XL_NC_TAG:
                lsm6dsr_fifo_out_raw_get(&s_dev_ctx, raw);
                {
                    int16_t x = (int16_t)((uint16_t)raw[1] << 8 | raw[0]);
                    int16_t y = (int16_t)((uint16_t)raw[3] << 8 | raw[2]);
                    int16_t z = (int16_t)((uint16_t)raw[5] << 8 | raw[4]);
                    vec3f acc = {
                        .x = lsm6dsr_from_fs8g_to_mg(x) / 1000.0f,
                        .y = lsm6dsr_from_fs8g_to_mg(y) / 1000.0f,
                        .z = lsm6dsr_from_fs8g_to_mg(z) / 1000.0f,
                    };
                    xStreamBufferSend(s_acc_ring_buf, &acc, sizeof(vec3f), 0);
                }
                break;

            default:
                // gyro 和其他 tag 全部丢弃
                lsm6dsr_fifo_out_raw_get(&s_dev_ctx, raw);
                break;
            }
        }
    }
}

// ── 公共 API ──────────────────────────────────────────────────────────────────

exit_code_t imu_service_init(imu_sensor_t *imu_sensor)
{
    if (!imu_sensor || !imu_sensor->imu_init) return EXIT_INVALID_PARAM;

    s_sensor = imu_sensor;
    exit_code_t ret = s_sensor->imu_init();
    if (ret != EXIT_OK) return ret;

    eventbus_allocate_module_id(&s_event_base_id);

    s_acc_ring_buf = xStreamBufferCreate(IMU_RING_BUF_ITEMS * sizeof(vec3f), sizeof(vec3f));
    ESP_LOGI(TAG, "acc_ring_buf=%p (items=%d)", s_acc_ring_buf, IMU_RING_BUF_ITEMS);
    if (!s_acc_ring_buf) {
        ESP_LOGE(TAG, "ring buffer alloc failed!");
        return EXIT_FAIL;
    }

    ESP_LOGI(TAG, "init OK");
    return EXIT_OK;
}

exit_code_t imu_service_start(void)
{
    if (!s_sensor || !s_acc_ring_buf) return EXIT_NOT_INITIALIZED;
    BaseType_t ret = xTaskCreatePinnedToCore(imu_fifo_task, "IMU_FIFO", 8192, NULL, 3, NULL, 1);
    return (ret == pdPASS) ? EXIT_OK : EXIT_FAIL;
}

exit_code_t imu_service_deinit(void)
{
    if (!s_sensor) return EXIT_NOT_INITIALIZED;
    if (s_sensor->imu_deinit) s_sensor->imu_deinit();
    if (s_acc_ring_buf) { vStreamBufferDelete(s_acc_ring_buf); s_acc_ring_buf = NULL; }
    s_sensor = NULL;
    return EXIT_OK;
}

StreamBufferHandle_t imu_service_get_acc_buffer(void)
{
    return s_acc_ring_buf;
}
