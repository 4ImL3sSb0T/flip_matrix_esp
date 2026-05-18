#include "app_water_sim.h"
#include "freertos/FreeRTOS.h"
#include <math.h>
#include "service/imu/imu_service.h"
#include "service/cli/log/log.h"
#include "esp_log.h"

/* -------------------------------------------------------------------------- */
/* 仿真默认参数                                                                 */
/* -------------------------------------------------------------------------- */
#define SIM_W          1.0f
#define SIM_H          1.0f
#define VISIBLE_RES    16
#define FILL_RATIO     0.6f
#define SIM_DT         0.016f

#define TASK_STACK     4096
#define TASK_PRIORITY  10

/* -------------------------------------------------------------------------- */
/* 颜色方案                                                                     */
/* -------------------------------------------------------------------------- */
typedef enum {
    COLOR_BLUE_GRADIENT = 0,
    COLOR_RAINBOW       = 1,
    COLOR_GRAYSCALE     = 2,
} color_scheme_t;

static color_scheme_t s_color_scheme = COLOR_RAINBOW;
static float s_dt = SIM_DT;
static float s_brightness = 0.2f;

/* -------------------------------------------------------------------------- */
/* 私有状态                                                                     */
/* -------------------------------------------------------------------------- */
static FlipFluid *s_fluid;
static TaskHandle_t s_task_handle;
static float s_led_grid[VISIBLE_RES * VISIBLE_RES];


static void imu_event_handler(const eventbus_event_t *evt, void *user_ctx) {
    // if (evt->payload_len != sizeof(imu_data_t)) return;
    const imu_data_t *data = (const imu_data_t *)evt->payload;
    switch (evt->id.event_id) {
        case IMU_EVENT_SLEEP:
            ESP_LOGI("app_water_sim", "Received IMU_EVENT_SLEEP");
            break;
        case IMU_EVENT_WAKE_UP:
            ESP_LOGI("app_water_sim", "Received IMU_EVENT_WAKE_UP");
            break;
        case IMU_EVENT_FALLING:
            ESP_LOGI("app_water_sim", "Received IMU_EVENT_FALLING");
            break;
        case IMU_EVENT_FLIP:
            ESP_LOGI("app_water_sim", "Received IMU_EVENT_FLIP");
            break;
        case IMU_EVENT_SHAKE:
            ESP_LOGI("app_water_sim", "Received IMU_EVENT_SHAKE");
            break;
        case IMU_EVENT_TAP:
            if (s_brightness > 0.9f) s_brightness = 0.1f;
            else s_brightness += 0.1f;
            app_water_sim_set_brightness(s_brightness);
            ESP_LOGI("app_water_sim", "Received IMU_EVENT_TAP");
            break;
        case IMU_EVENT_ROTATING:
            ESP_LOGI("app_water_sim", "Received IMU_EVENT_ROTATING");
            break;
    }
}
/* -------------------------------------------------------------------------- */
/* 颜色映射                                                                     */
/* -------------------------------------------------------------------------- */
static uint32_t color_blue_gradient(float brightness) {
    if (brightness < 0.0f) brightness = 0.0f;
    if (brightness > 1.0f) brightness = 1.0f;
    uint8_t b = (uint8_t)(brightness * 255.0f);
    return matrix_rgb(0, 0, b);
}

static uint32_t color_rainbow(float brightness) {
    if (brightness < 0.0f) brightness = 0.0f;
    if (brightness > 1.0f) brightness = 1.0f;
    uint16_t hue = (uint16_t)((1.0f - brightness) * 240.0f);
    uint8_t val = (uint8_t)(brightness * 255.0f);
    return matrix_hsv2rgb(hue, 255, val);
}

static uint32_t color_grayscale(float brightness) {
    if (brightness < 0.0f) brightness = 0.0f;
    if (brightness > 1.0f) brightness = 1.0f;
    uint8_t v = (uint8_t)(brightness * 255.0f);
    return matrix_rgb(v, v, v);
}

static uint32_t apply_color(float led_val) {
    float brightness = led_val / LED_VAL_MAX_F;
    switch (s_color_scheme) {
    case COLOR_RAINBOW:   return color_rainbow(brightness);
    case COLOR_GRAYSCALE: return color_grayscale(brightness);
    default:              return color_blue_gradient(brightness);
    }
}

/* -------------------------------------------------------------------------- */
/* 显示更新                                                                     */
/* -------------------------------------------------------------------------- */
static void display_update(const float *grid) {
    for (uint32_t row = 0; row < matrix_rows(); row++) {
        for (uint32_t col = 0; col < matrix_cols(); col++) {
            uint32_t rgb = apply_color(grid[row * matrix_cols() + col]);
            uint8_t r = (uint8_t)(((rgb >> 16) & 0xFF) * s_brightness);
            uint8_t g = (uint8_t)(((rgb >>  8) & 0xFF) * s_brightness);
            uint8_t b = (uint8_t)(( rgb        & 0xFF) * s_brightness);
            matrix_set_pixel(row, col, matrix_rgb(r, g, b));
        }
    }
    matrix_write_async();
}

/* -------------------------------------------------------------------------- */
/* 组合任务：计算 + 显示                                                          */
/* -------------------------------------------------------------------------- */
static void water_sim_task(void *param) {
    (void)param;

    TickType_t last_wake = xTaskGetTickCount();

    for (;;) {
        float dt = s_dt;
        vec3f acc, gyro, meg;
        imu_service_get_raw_data(&acc, &gyro, &meg);

        float gx = acc.x;
        float gy = acc.y;
        float mag = sqrtf(gx * gx + gy * gy);
        if (mag > 2.0f) { gx *= 2.0f / mag; gy *= 2.0f / mag; }

        flip_step(s_fluid, dt, gx, gy);
        flip_get_led_grid(s_fluid, s_led_grid);

        display_update(s_led_grid);
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS((uint32_t)(dt * 1000.0f)));
    }
}

/* -------------------------------------------------------------------------- */
/* 公开 API                                                                     */
/* -------------------------------------------------------------------------- */
exit_code_t app_water_sim_init(void) {
    if (s_fluid) return EXIT_ALREADY_INITIALIZED;

    const matrix_config_t mcfg = {
        .rows      = VISIBLE_RES,
        .cols      = VISIBLE_RES,
        .gpio_num  = 48,
        .topology  = MATRIX_TOPO_PROGRESSIVE,
    };
    exit_code_t ret = matrix_init(&mcfg);
    if (ret != EXIT_OK) return ret;

    s_fluid = flip_create(SIM_W, SIM_H, VISIBLE_RES, FILL_RATIO);
    if (!s_fluid) {
        matrix_deinit();
        return EXIT_NO_MEMORY;
    }

    flip_set_solver_quality(s_fluid, 4, 12, 0.6f);
    flip_set_gravity_scale(s_fluid, 9.81f);

    eventbus_subscribe(eventbus_make_event_id(IMU_EVENT_BASE_ID, EVENTBUS_EVENT_ID_ALL), imu_event_handler, NULL);

    return EXIT_OK;
}

exit_code_t app_water_sim_start(void) {
    if (!s_fluid) return EXIT_NOT_INITIALIZED;
    if (s_task_handle) return EXIT_ALREADY_INITIALIZED;

    const BaseType_t ok = xTaskCreate(water_sim_task, "water_sim",
                                      TASK_STACK, NULL,
                                      TASK_PRIORITY, &s_task_handle);
    return (ok == pdPASS) ? EXIT_OK : EXIT_FAIL;
}

exit_code_t app_water_sim_stop(void) {
    if (s_task_handle) {
        vTaskDelete(s_task_handle);
        s_task_handle = NULL;
    }
    if (s_fluid) {
        flip_destroy(s_fluid);
        s_fluid = NULL;
    }
    matrix_deinit();
    return EXIT_OK;
}

void app_water_sim_set_gravity(float scale) {
    if (s_fluid) flip_set_gravity_scale(s_fluid, scale);
}

void app_water_sim_set_solver(int push_iters, int pressure_iters, float flip_ratio) {
    if (s_fluid) flip_set_solver_quality(s_fluid, push_iters, pressure_iters, flip_ratio);
}

void app_water_sim_set_color_scheme(int scheme) {
    if (scheme >= 0 && scheme <= 2) s_color_scheme = (color_scheme_t)scheme;
}

void app_water_sim_set_dt(float dt) {
    if (dt > 0.0f) s_dt = dt;
}

void app_water_sim_set_brightness(float percent) {
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 1.0f) percent = 1.0f;
    s_brightness = percent;
}

void app_water_sim_status(void) {
    static const char *scheme_names[] = {"blue", "rainbow", "grayscale"};
    logInfo("gravity_scale: %.2f", flip_get_gravity_scale(s_fluid));
    logInfo("solver: push=%d pressure=%d flip=%.2f",
            flip_get_push_iters(s_fluid),
            flip_get_pressure_iters(s_fluid),
            flip_get_flip_ratio(s_fluid));
    logInfo("dt: %.4f s (%.0f Hz)", s_dt, 1.0f / s_dt);
    logInfo("color: %s (%d)", scheme_names[s_color_scheme], (int)s_color_scheme);
    logInfo("brightness: %.0f%%", s_brightness * 100.0f);
    logInfo("matrix: %lux%lu", matrix_rows(), matrix_cols());
}
