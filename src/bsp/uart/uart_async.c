#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"

#include "uart_async.h"
#include "service/tools/common_def.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/stream_buffer.h"

#define UART_ASYNC_RX_STREAM_BUFFER_SIZE 4096

#define UART_ASYNC_TX_DMA_BUFFER_SIZE 2048
#define UART_ASYNC_RX_DMA_BUFFER_SIZE 2048

#define EVENT_QUEUE_SIZE 16

static int RX_PIN = GPIO_NUM_9;
static int TX_PIN = GPIO_NUM_10;

static QueueHandle_t uart_queue;


static StreamBufferHandle_t uart_tx_stream_buffer = NULL;
static StreamBufferHandle_t uart_rx_stream_buffer = NULL;

static TaskHandle_t uart_async_tx_task_handle = NULL;

// 唐完了，这里要加互斥锁,AI瞎jb说,StreamBuffer不支持多任务写入
static SemaphoreHandle_t uart_rx_mutex = NULL;

static volatile uint16_t rx_last_pos = 0;
static volatile uint32_t rx_errors = 0;
static volatile uint32_t rx_dropped = 0;

static volatile uint32_t tx_errors = 0;

void uart_async_rx_task(void *param) {
    uart_event_t event;
    uint8_t tmp_buf[256];

    while (1) {
        if (xQueueReceive(uart_queue, (void*)&event, portMAX_DELAY)) {
            switch (event.type) {
            case UART_DATA:
                if (event.size > 0) {
                    const int len = uart_read_bytes(UART_NUM_1, tmp_buf, event.size, pdMS_TO_TICKS(20));
                    if (len > 0) {
                        xSemaphoreTake(uart_rx_mutex, portMAX_DELAY);
                        const size_t sent = xStreamBufferSend(uart_rx_stream_buffer, tmp_buf, len, 0);
                        xSemaphoreGive(uart_rx_mutex);
                        if (sent < (size_t)len) {
                            rx_dropped += len - sent;
                        }
                    }
                }
                break;

            case UART_FIFO_OVF:
                ESP_LOGW("uart_async", "FIFO overflow");
                rx_errors++;
                uart_flush_input(UART_NUM_1);
                xQueueReset(uart_queue);
                break;

            case UART_FRAME_ERR:
                ESP_LOGW("uart_async", "frame error");
                rx_errors++;
                break;

            case UART_PARITY_ERR:
                ESP_LOGW("uart_async", "parity error");
                rx_errors++;
                break;

            case UART_BREAK:
                ESP_LOGW("uart_async", "break detected");
                rx_errors++;
                break;

            case UART_PATTERN_DET:
                break;

            default:
                break;
            }
        }
    }
}

exit_code_t uart_async_init(void)
{
    uart_config_t cfg = {
        .baud_rate = 921600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT
    };
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, UART_ASYNC_RX_DMA_BUFFER_SIZE, UART_ASYNC_TX_DMA_BUFFER_SIZE, EVENT_QUEUE_SIZE, &uart_queue, 0));

    uart_rx_stream_buffer = xStreamBufferCreate(UART_ASYNC_RX_STREAM_BUFFER_SIZE, sizeof(uint8_t));
    uart_rx_mutex = xSemaphoreCreateMutex();

    return EXIT_OK;
}

exit_code_t uart_async_deinit(void)
{
    ESP_ERROR_CHECK(uart_driver_delete(UART_NUM_1));
    vStreamBufferDelete(uart_tx_stream_buffer);
    vStreamBufferDelete(uart_rx_stream_buffer);
    vSemaphoreDelete(uart_rx_mutex);
    return EXIT_OK;
}

exit_code_t uart_async_start() {
    if (uart_tx_stream_buffer == NULL || uart_rx_stream_buffer == NULL || uart_rx_mutex == NULL) return EXIT_FAIL;
    const BaseType_t xTaskCreate_status = xTaskCreate(uart_async_rx_task, "uart_async_rx_task", 256, NULL, 24, &uart_async_tx_task_handle);

    if (xTaskCreate_status != pdPASS) return EXIT_FAIL;
    return EXIT_OK;
}

exit_code_t uart_async_write(const uint8_t* data, const uint32_t len, const TickType_t timeout) {
    if (len == 0) return EXIT_OK;

    // ESP32 串口自带Buffer和DMA, 并且串口驱动已经做好了互斥, 这里就不再加锁了, 直接写入串口驱动的Buffer即可
    const int sent = uart_write_bytes(UART_NUM_1, data, len);

    if (sent != len)
        return EXIT_FAIL;
    return EXIT_OK;
}

size_t uart_async_read(uint8_t* data, const uint32_t len, const TickType_t timeout) {
    xSemaphoreTake(uart_rx_mutex, portMAX_DELAY);
    const size_t received = xStreamBufferReceive(uart_rx_stream_buffer, data, len, timeout);
    xSemaphoreGive(uart_rx_mutex);
    return received;
}
