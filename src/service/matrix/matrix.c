#include "matrix.h"
#include "service/cli/log/log.h"
#include "led_strip.h"
#include "led_strip_rmt.h"

#ifndef MATRIX_MAX_LEDS
  #define MATRIX_MAX_LEDS 256
#endif

static matrix_config_t matrix_cfg;
static bool initialized;

static led_strip_handle_t strip_handle;
static SemaphoreHandle_t matrix_mutex;

typedef uint32_t (*pixel_mapper_fn)(uint32_t row, uint32_t col, uint32_t cols);
static pixel_mapper_fn pixel_mapper;

static uint32_t map_progressive(uint32_t row, uint32_t col, uint32_t cols)
{
  return row * cols + col;
}

static uint32_t map_snake(uint32_t row, uint32_t col, uint32_t cols)
{
  if (row & 1) {
    col = cols - 1 - col;
  }
  return row * cols + col;
}

static uint32_t matrix_led_count(void)
{
  return matrix_cfg.rows * matrix_cfg.cols;
}

exit_code_t matrix_init(const matrix_config_t *config)
{
  if (!config) return EXIT_INVALID_PARAM;
  if (config->rows == 0 || config->cols == 0) return EXIT_INVALID_PARAM;

  uint32_t led_count = config->rows * config->cols;
  if (led_count > MATRIX_MAX_LEDS) {
    logError("too many LEDs: %lu (max %d)", led_count, MATRIX_MAX_LEDS);
    return EXIT_NO_RESOURCE;
  }

  matrix_cfg = *config;

  switch (config->topology) {
    case MATRIX_TOPO_SNAKE:
      pixel_mapper = map_snake;
      break;
    default:
      pixel_mapper = map_progressive;
      break;
  }

  matrix_mutex = xSemaphoreCreateMutex();
  if (!matrix_mutex) return EXIT_NO_MEMORY;

  led_strip_config_t strip_cfg = {
    .strip_gpio_num = config->gpio_num,
    .max_leds = led_count,
    .led_model = LED_MODEL_WS2812,
    .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
    .flags = { .invert_out = false },
  };

  led_strip_rmt_config_t rmt_cfg = {
    .clk_src = RMT_CLK_SRC_DEFAULT,
    .resolution_hz = 10 * 1000 * 1000,
    .mem_block_symbols = 0,
    .flags = { .with_dma = true },
  };

  esp_err_t err = led_strip_new_rmt_device(&strip_cfg, &rmt_cfg, &strip_handle);
  if (err != ESP_OK) {
    vSemaphoreDelete(matrix_mutex);
    matrix_mutex = NULL;
    logError("led_strip init failed: %s", esp_err_to_name(err));
    return EXIT_HW_FAILURE;
  }

  initialized = true;
  logInfo("matrix %lux%lu topo=%u gpio=%d, %lu LEDs",
          config->rows, config->cols, config->topology, config->gpio_num, led_count);
  return EXIT_OK;
}

exit_code_t matrix_deinit(void)
{
  if (!initialized) return EXIT_NOT_INITIALIZED;

  led_strip_del(strip_handle);
  strip_handle = NULL;

  if (matrix_mutex) {
    vSemaphoreDelete(matrix_mutex);
    matrix_mutex = NULL;
  }

  initialized = false;
  logInfo("matrix deinitialized");
  return EXIT_OK;
}

exit_code_t matrix_write_async(void)
{
  if (!initialized) return EXIT_NOT_INITIALIZED;

  xSemaphoreTake(matrix_mutex, portMAX_DELAY);
  esp_err_t err = led_strip_refresh(strip_handle);
  xSemaphoreGive(matrix_mutex);

  if (err != ESP_OK) {
    logError("refresh failed: %s", esp_err_to_name(err));
    return EXIT_FAIL;
  }
  return EXIT_OK;
}

exit_code_t matrix_write_buffer(const uint32_t *data, uint32_t len)
{
  if (!initialized) return EXIT_NOT_INITIALIZED;
  if (!data) return EXIT_INVALID_PARAM;

  uint32_t led_count = matrix_led_count();
  if (len != led_count) {
    logError("write_buffer len %lu != %lu", len, led_count);
    return EXIT_INVALID_PARAM;
  }

  xSemaphoreTake(matrix_mutex, portMAX_DELAY);
  for (uint32_t row = 0; row < matrix_cfg.rows; row++) {
    for (uint32_t col = 0; col < matrix_cfg.cols; col++) {
      uint32_t logical_idx = row * matrix_cfg.cols + col;
      uint32_t physical_idx = pixel_mapper(row, col, matrix_cfg.cols);
      uint32_t rgb = data[logical_idx];
      led_strip_set_pixel(strip_handle, physical_idx,
                          (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
    }
  }
  xSemaphoreGive(matrix_mutex);

  return EXIT_OK;
}

exit_code_t matrix_set_pixel(uint32_t row, uint32_t col, uint32_t rgb)
{
  if (!initialized) return EXIT_NOT_INITIALIZED;
  if (row >= matrix_cfg.rows || col >= matrix_cfg.cols) {
    logError("set_pixel out of bounds: (%lu,%lu)", row, col);
    return EXIT_INVALID_PARAM;
  }

  xSemaphoreTake(matrix_mutex, portMAX_DELAY);
  led_strip_set_pixel(strip_handle, pixel_mapper(row, col, matrix_cfg.cols),
                      (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
  xSemaphoreGive(matrix_mutex);

  return EXIT_OK;
}

exit_code_t matrix_fill(uint32_t rgb)
{
  if (!initialized) return EXIT_NOT_INITIALIZED;

  uint8_t r = (rgb >> 16) & 0xFF;
  uint8_t g = (rgb >> 8) & 0xFF;
  uint8_t b = rgb & 0xFF;

  xSemaphoreTake(matrix_mutex, portMAX_DELAY);
  for (uint32_t i = 0; i < matrix_led_count(); i++) {
    led_strip_set_pixel(strip_handle, i, r, g, b);
  }
  xSemaphoreGive(matrix_mutex);

  return EXIT_OK;
}

exit_code_t matrix_clear(void)
{
  if (!initialized) return EXIT_NOT_INITIALIZED;

  xSemaphoreTake(matrix_mutex, portMAX_DELAY);
  led_strip_clear(strip_handle);
  xSemaphoreGive(matrix_mutex);

  return EXIT_OK;
}

uint32_t matrix_pixel_count(void)
{
  return matrix_led_count();
}

uint32_t matrix_rows(void)
{
  return matrix_cfg.rows;
}

uint32_t matrix_cols(void)
{
  return matrix_cfg.cols;
}

uint32_t matrix_rgb(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

uint32_t matrix_hsv2rgb(uint16_t h, uint8_t s, uint8_t v)
{
  if (s == 0) {
    return ((uint32_t)v << 16) | ((uint32_t)v << 8) | v;
  }

  h %= 360;
  uint8_t region = h / 60;
  uint8_t rem = (uint8_t)(((uint32_t)(h % 60) * 255) / 60);

  uint8_t p = (uint8_t)(((uint32_t)v * (255 - s)) >> 8);
  uint8_t q = (uint8_t)(((uint32_t)v * (255 - (uint16_t)(((uint32_t)s * rem) >> 8))) >> 8);
  uint8_t t = (uint8_t)(((uint32_t)v * (255 - (uint16_t)(((uint32_t)s * (255 - rem)) >> 8))) >> 8);

  uint8_t r, g, b;
  switch (region) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    default: r = v; g = p; b = q; break;
  }

  return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}
