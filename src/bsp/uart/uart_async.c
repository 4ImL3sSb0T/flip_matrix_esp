#include "driver/uart.h"
#include "driver/gpio.h"
#include "uart_async.h"
#include "service/tools/common_def.h"
#include "esp_log.h"

#define UART_RX_BUF_SIZE 2048
#define UART_TX_BUF_SIZE 2048

// PIN9和10不能使用!!!
static int RX_PIN = GPIO_NUM_5;
static int TX_PIN = GPIO_NUM_4;
const char *TAG = "uart_async";

exit_code_t uart_async_init(void)
{
    uart_config_t cfg = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT
    };
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &cfg));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE, 16, NULL, 0));
    return EXIT_OK;
}

exit_code_t uart_async_deinit(void)
{
    ESP_ERROR_CHECK(uart_driver_delete(UART_NUM_2));
    return EXIT_OK;
}

exit_code_t uart_async_start(void) {
    return EXIT_OK;
}

exit_code_t uart_async_write(const uint8_t* data, const uint32_t len, const TickType_t timeout) {
    if (len == 0) return EXIT_OK;
    const int sent = uart_write_bytes(UART_NUM_2, data, len);
    if (sent != len)
        return EXIT_FAIL;
    return EXIT_OK;
}

size_t uart_async_read(uint8_t* data, const uint32_t len, const TickType_t timeout) {
    size_t read_len = uart_read_bytes(UART_NUM_2, data, len, timeout);
    return read_len;
}
