#include "cheat.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "CHEAT"

static bool s_initialized = false;

exit_code_t cheat_init(void)
{
    if (s_initialized) {
        return EXIT_ALREADY_INITIALIZED;
    }

    // GPIO1/2 推挽输出，初始低电平
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << CHEAT_PIN_B0) | (1ULL << CHEAT_PIN_B1),
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    esp_err_t ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "GPIO config failed: %s", esp_err_to_name(ret));
        return EXIT_HW_FAILURE;
    }

    // 初始化为 00 (IDLE)
    gpio_set_level(CHEAT_PIN_B0, 0);
    gpio_set_level(CHEAT_PIN_B1, 0);

    s_initialized = true;
    ESP_LOGI(TAG, "cheat output pins ready: B0=GPIO%d, B1=GPIO%d", CHEAT_PIN_B0, CHEAT_PIN_B1);
    return EXIT_OK;
}

void cheat_set_state(uint8_t state)
{
    if (!s_initialized) return;

    gpio_set_level(CHEAT_PIN_B0, (state >> 0) & 1);
    gpio_set_level(CHEAT_PIN_B1, (state >> 1) & 1);
}

const char *cheat_state_name(uint8_t state)
{
    switch (state) {
    case 0: return "IDLE";
    case 1: return "NORMAL";
    case 2: return "LOOSE";
    case 3: return "IMBALANCE";
    default: return "UNKNOWN";
    }
}
