#include "imu_service.h"
#include "bsp/imu963ra/imu963ra.h"
#include "bsp/imu963ra/lsm6dsr_reg.h"
#include "service/event_bus/event_bus.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

#define TAG "IMU_SVC"

// ── 配置 ──────────────────────────────────────────────────────────────────────
#define IMU_FIFO_WATERMARK      256
#define IMU_RING_BUF_ITEMS      1024

// ── 静态变量 ──────────────────────────────────────────────────────────────────
static imu_sensor_t *s_sensor = NULL;
static MessageBufferHandle_t s_acc_ring_buf = NULL;
static stmdev_ctx_t s_dev_ctx;
static uint16_t s_event_base_id = 0;
static bool s_is_ok = false;

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

    ESP_LOGI(TAG, "FIFO task started: ODR=6667Hz, watermark=%d, poll=5ms", IMU_FIFO_WATERMARK);

    // DMA 缓冲区一次性分配（最大 watermark × 7 字节 + 1）
    const uint32_t max_payload = IMU_FIFO_WATERMARK * 7;
    const uint32_t max_total = 1 + max_payload;
    uint8_t *tx_buf = heap_caps_malloc(max_total, MALLOC_CAP_DMA);
    uint8_t *rx_buf = heap_caps_malloc(max_total, MALLOC_CAP_DMA);
    if (!tx_buf || !rx_buf) {
        ESP_LOGE(TAG, "DMA buffer alloc failed!");
        vTaskDelete(NULL);
        return;
    }
    tx_buf[0] = 0x78 | 0x80;  // FIFO_DATA_OUT_TAG + SPI read bit，只需设一次

    // 主循环
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(5));

        // [中断模式替代: ulTaskNotifyTake(pdTRUE, portMAX_DELAY)]

        uint8_t wmflag = 0;
        lsm6dsr_fifo_wtm_flag_get(&s_dev_ctx, &wmflag);
        if (wmflag == 0) continue;

        uint16_t num = 0;
        lsm6dsr_fifo_data_level_get(&s_dev_ctx, &num);
        if (num == 0) continue;
        if (num > IMU_FIFO_WATERMARK) num = IMU_FIFO_WATERMARK;

        // 批量读取：一次 SPI 事务读 num 帧（每帧 7 字节：TAG + 6 DATA）
        uint32_t payload = num * 7;
        uint32_t total = 1 + payload;
        memset(tx_buf + 1, 0x00, payload);
        spi_transaction_t t = {
            .length = 8 * total,
            .tx_buffer = tx_buf,
            .rx_buffer = rx_buf,
        };
        if (spi_device_transmit(*(spi_device_handle_t *)s_dev_ctx.handle, &t) != ESP_OK)
            continue;

        // 内存中解析 tag，提取 acc 数据
        for (uint16_t i = 0; i < num; i++) {
            uint8_t *f = rx_buf + 1 + i * 7;  // +1 跳过 dummy byte
            uint8_t tag = f[0] >> 3;  // tag_sensor 在 bits[7:3]

            if (tag == LSM6DSR_XL_NC_TAG) {
                int16_t x = (int16_t)((uint16_t)f[2] << 8 | f[1]);
                int16_t y = (int16_t)((uint16_t)f[4] << 8 | f[3]);
                int16_t z = (int16_t)((uint16_t)f[6] << 8 | f[5]);
                vec3f acc = {
                    .x = lsm6dsr_from_fs8g_to_mg(x) / 1000.0f,
                    .y = lsm6dsr_from_fs8g_to_mg(y) / 1000.0f,
                    .z = lsm6dsr_from_fs8g_to_mg(z) / 1000.0f,
                };
                xMessageBufferSend(s_acc_ring_buf, &acc, sizeof(vec3f), 0);
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
    if (ret != EXIT_OK) {
        return ret;
    }
    s_is_ok = true;

    eventbus_allocate_module_id(&s_event_base_id);

    s_acc_ring_buf = xMessageBufferCreate(IMU_RING_BUF_ITEMS * sizeof(vec3f));
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
    if (s_acc_ring_buf) { vMessageBufferDelete(s_acc_ring_buf); s_acc_ring_buf = NULL; }
    s_sensor = NULL;
    return EXIT_OK;
}

bool imu_service_is_ok(void) {
	return s_is_ok;
}

MessageBufferHandle_t imu_service_get_acc_buffer(void)
{
    return s_acc_ring_buf;
}
