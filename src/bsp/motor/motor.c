#include "motor.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static bool s_channel_used[LEDC_CHANNEL_MAX];
static int s_dir_gpio[LEDC_CHANNEL_MAX];
static bool s_dir_invert[LEDC_CHANNEL_MAX];
static float s_duty[LEDC_CHANNEL_MAX];
static bool s_timer_inited = false;
static SemaphoreHandle_t s_mutex = NULL;

static exit_code_t ensure_timer(void)
{
    if (s_timer_inited) {
        return EXIT_OK;
    }

    s_mutex = xSemaphoreCreateMutex();
    if (s_mutex == NULL) {
        return EXIT_NO_MEMORY;
    }

    ledc_timer_config_t timer_conf = {
        .speed_mode = MOTOR_LEDC_SPEED_MODE,
        .duty_resolution = MOTOR_PWM_RESOLUTION,
        .timer_num = MOTOR_LEDC_TIMER,
        .freq_hz = MOTOR_PWM_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    esp_err_t err = ledc_timer_config(&timer_conf);
    if (err != ESP_OK) {
        return EXIT_HW_FAILURE;
    }

    s_timer_inited = true;
    return EXIT_OK;
}

exit_code_t motor_init(const motor_config_t *config)
{
    if (config == NULL || config->channel >= LEDC_CHANNEL_MAX) {
        return EXIT_INVALID_PARAM;
    }

    if (!GPIO_IS_VALID_GPIO(config->pwm_gpio) || !GPIO_IS_VALID_GPIO(config->dir_gpio)) {
        return EXIT_INVALID_PARAM;
    }

    if (s_channel_used[config->channel]) {
        return EXIT_ALREADY_INITIALIZED;
    }

    exit_code_t ret = ensure_timer();
    if (ret != EXIT_OK) {
        return ret;
    }

    ledc_channel_config_t ch_conf = {
        .gpio_num = config->pwm_gpio,
        .speed_mode = MOTOR_LEDC_SPEED_MODE,
        .channel = config->channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = MOTOR_LEDC_TIMER,
        .duty = 0,
        .hpoint = 0,
        .sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
        .flags = { .output_invert = 0 },
    };
    esp_err_t err = ledc_channel_config(&ch_conf);
    if (err != ESP_OK) {
        return EXIT_HW_FAILURE;
    }

    gpio_config_t dir_conf = {
        .pin_bit_mask = 1ULL << config->dir_gpio,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    esp_err_t gpio_err = gpio_config(&dir_conf);
    if (gpio_err != ESP_OK) {
        return EXIT_HW_FAILURE;
    }
    gpio_set_level(config->dir_gpio, 0);

    s_dir_gpio[config->channel] = config->dir_gpio;
    s_dir_invert[config->channel] = config->dir_invert;
    s_duty[config->channel] = 0.0f;
    s_channel_used[config->channel] = true;
    return EXIT_OK;
}

exit_code_t motor_set_duty(ledc_channel_t channel, float duty)
{
    if (channel >= LEDC_CHANNEL_MAX || !s_channel_used[channel]) {
        return EXIT_NOT_INITIALIZED;
    }
    if (duty < -1.0f || duty > 1.0f) {
        return EXIT_INVALID_PARAM;
    }

    bool forward = duty >= 0.0f;
    bool level = forward ^ s_dir_invert[channel];
    gpio_set_level(s_dir_gpio[channel], level ? 1 : 0);

    float abs_duty = duty >= 0.0f ? duty : -duty;
    uint32_t raw = (uint32_t)(abs_duty * MOTOR_PWM_MAX_DUTY + 0.5f);

    xSemaphoreTake(s_mutex, portMAX_DELAY);

    esp_err_t err = ledc_set_duty(MOTOR_LEDC_SPEED_MODE, channel, raw);
    if (err != ESP_OK) {
        xSemaphoreGive(s_mutex);
        return EXIT_FAIL;
    }
    err = ledc_update_duty(MOTOR_LEDC_SPEED_MODE, channel);
    if (err != ESP_OK) {
        xSemaphoreGive(s_mutex);
        return EXIT_FAIL;
    }

    xSemaphoreGive(s_mutex);

    s_duty[channel] = duty;
    return EXIT_OK;
}

float motor_get_duty(ledc_channel_t channel)
{
    if (channel >= LEDC_CHANNEL_MAX || !s_channel_used[channel]) {
        return 0.0f;
    }
    return s_duty[channel];
}

exit_code_t motor_stop(ledc_channel_t channel)
{
    return motor_set_duty(channel, 0.0f);
}
