/*
 ******************************************************************************
 * @file    multi_read_fifo_simple.c
 * @author  Sensors Software Solution Team
 * @brief   This file show how to get data from sensor FIFO.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/*
 * This example was developed using the following STMicroelectronics
 * evaluation boards:
 *
 * - STEVAL_MKI109V3 + STEVAL-MKI194V1
 * - STEVAL_MKI109D  + STEVAL-MKI194V1
 * - NUCLEO_F401RE + X_NUCLEO_IKS01A3
 * - NUCLEO_H503RB + X-NUCLEO-IKS4A1
 * - DISCOVERY_SPC584B + STEVAL-MKI194A
 *
 * Used interfaces:
 *
 * STEVAL_MKI109D     - Host side:   USB (Virtual COM)
 *                    - Sensor side: SPI(Default) / I2C(supported)
 *
 * STEVAL_MKI109V3    - Host side:   USB (Virtual COM)
 *                    - Sensor side: SPI(Default) / I2C(supported)
 *
 * NUCLEO_STM32F401RE - Host side: UART(COM) to USB bridge
 *                    - Sensor side: I2C(Default) / SPI(supported)
 *
 * DISCOVERY_SPC584B  - Host side: UART(COM) to USB bridge
 *                    - Sensor side: I2C(Default) / SPI(supported)
 *
 * NUCLEO_STM32H503RG - Host side: UART(COM) to USB bridge
 *                    - Sensor side: I3C(Default)
 *
 * If you need to run this example on a different hardware platform a
 * modification of the functions: `platform_write`, `platform_read`,
 * `tx_com` and 'platform_init' is required.
 *
 */

/* STMicroelectronics evaluation boards definition
 *
 * Please uncomment ONLY the evaluation boards in use.
 * If a different hardware is used please comment all
 * following target board and redefine yours.
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "lsm6dsr_reg.h"

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "service/tcp/tcp_server.h"

/* ESP32-S3 SPI pin configuration */
#define IMU_SPI_HOST        SPI2_HOST
#define IMU_SPI_MOSI_PIN    GPIO_NUM_11
#define IMU_SPI_MISO_PIN    GPIO_NUM_12
#define IMU_SPI_SCK_PIN     GPIO_NUM_13
#define IMU_SPI_CS_PIN      GPIO_NUM_10
#define IMU_SPI_FREQ_HZ     (10 * 1000 * 1000)  /* 10 MHz */

static spi_device_handle_t imu_spi_handle;

typedef union {
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME            10 //ms

/* Private variables ---------------------------------------------------------*/
static axis3bit16_t data_raw_acceleration;
static axis3bit16_t data_raw_angular_rate;
static float_t acceleration_mg[3];
static float_t angular_rate_mdps[3];
static uint8_t whoamI, rst;
static uint8_t tx_buffer[1000];

/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void tx_com( uint8_t *tx_buffer, uint16_t len );
static void platform_delay(uint32_t ms);
static void platform_init(void *handle);

/* Main Example --------------------------------------------------------------*/
void lsm6dsr_fifo(void)
{
  stmdev_ctx_t dev_ctx;
  /* Uncomment to configure INT 1 */
  //lsm6dsr_pin_int1_route_t int1_route;
  /* Uncomment to configure INT 2 */
  //lsm6dsr_pin_int2_route_t int2_route;
  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.mdelay = platform_delay;
  dev_ctx.handle = NULL;
  /* Init test platform */
  platform_init(NULL);

  /* Wait sensor boot time */
  platform_delay(BOOT_TIME);
  lsm6dsr_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LSM6DSR_ID)
    while (1);

  /* Restore default configuration */
  lsm6dsr_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do {
    lsm6dsr_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Disable I3C interface */
  lsm6dsr_i3c_disable_set(&dev_ctx, LSM6DSR_I3C_DISABLE);
  /* Enable Block Data Update */
  lsm6dsr_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set full scale */
  lsm6dsr_xl_full_scale_set(&dev_ctx, LSM6DSR_2g);
  lsm6dsr_gy_full_scale_set(&dev_ctx, LSM6DSR_2000dps);
  /* Set FIFO watermark (number of unread sensor data TAG + 6 bytes
   * stored in FIFO) to 10 samples
   */
  lsm6dsr_fifo_watermark_set(&dev_ctx, 10);
  /* Set FIFO batch XL/Gyro ODR to 12.5Hz */
  lsm6dsr_fifo_xl_batch_set(&dev_ctx, LSM6DSR_XL_BATCHED_AT_12Hz5);
  lsm6dsr_fifo_gy_batch_set(&dev_ctx, LSM6DSR_GY_BATCHED_AT_12Hz5);
  /* Set FIFO mode to Stream mode (aka Continuous Mode) */
  lsm6dsr_fifo_mode_set(&dev_ctx, LSM6DSR_STREAM_MODE);
  /* Enable drdy 75 μs pulse: uncomment if interrupt must be pulsed */
  //lsm6dsr_data_ready_mode_set(&dev_ctx, LSM6DSR_DRDY_PULSED);
  /* Uncomment if interrupt generation on Free Fall INT1 pin */
  //lsm6dsr_pin_int1_route_get(&dev_ctx, &int1_route);
  //int1_route.reg.int1_ctrl.int1_fifo_th = PROPERTY_ENABLE;
  //lsm6dsr_pin_int1_route_set(&dev_ctx, &int1_route);
  /* Uncomment if interrupt generation on Free Fall INT2 pin */
  //lsm6dsr_pin_int2_route_get(&dev_ctx, &int2_route);
  //int2_route.reg.int2_ctrl.int2_fifo_th = PROPERTY_ENABLE;
  //lsm6dsr_pin_int2_route_set(&dev_ctx, &int2_route);
  /* Set Output Data Rate */
  lsm6dsr_xl_data_rate_set(&dev_ctx, LSM6DSR_XL_ODR_12Hz5);
  lsm6dsr_gy_data_rate_set(&dev_ctx, LSM6DSR_GY_ODR_12Hz5);

  /* Wait samples. */
  while (1) {
    uint16_t num = 0;
    uint8_t wmflag = 0;
    lsm6dsr_fifo_tag_t reg_tag;
    axis3bit16_t dummy;
    /* Read watermark flag */
    lsm6dsr_fifo_wtm_flag_get(&dev_ctx, &wmflag);

    if (wmflag == 0) {
      vTaskDelay(pdMS_TO_TICKS(1));
      continue;
    }
    {
      /* Read number of samples in FIFO */
      lsm6dsr_fifo_data_level_get(&dev_ctx, &num);

      while (num--) {
        /* Read FIFO tag */
        lsm6dsr_fifo_sensor_tag_get(&dev_ctx, &reg_tag);

        switch (reg_tag) {
          case LSM6DSR_XL_NC_TAG:
            memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
            lsm6dsr_fifo_out_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
            acceleration_mg[0] =
              lsm6dsr_from_fs2g_to_mg(data_raw_acceleration.i16bit[0]);
            acceleration_mg[1] =
              lsm6dsr_from_fs2g_to_mg(data_raw_acceleration.i16bit[1]);
            acceleration_mg[2] =
              lsm6dsr_from_fs2g_to_mg(data_raw_acceleration.i16bit[2]);
            snprintf((char *)tx_buffer, sizeof(tx_buffer),
                    "Acceleration [mg]:%4.2f\t%4.2f\t%4.2f\r\n",
                    acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
            tx_com(tx_buffer, strlen((char const *)tx_buffer));
            break;

          case LSM6DSR_GYRO_NC_TAG:
            memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
            lsm6dsr_fifo_out_raw_get(&dev_ctx, data_raw_angular_rate.u8bit);
            angular_rate_mdps[0] =
              lsm6dsr_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[0]);
            angular_rate_mdps[1] =
              lsm6dsr_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[1]);
            angular_rate_mdps[2] =
              lsm6dsr_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[2]);
            snprintf((char *)tx_buffer, sizeof(tx_buffer),
                    "Angular rate [mdps]:%4.2f\t%4.2f\t%4.2f\r\n",
                    angular_rate_mdps[0], angular_rate_mdps[1], angular_rate_mdps[2]);
            tx_com(tx_buffer, strlen((char const *)tx_buffer));
            break;

          default:
            /* Flush unused samples */
            memset(dummy.u8bit, 0x00, 3 * sizeof(int16_t));
            lsm6dsr_fifo_out_raw_get(&dev_ctx, dummy.u8bit);
            break;
        }
      }
    }
  }
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  /* Allocate tx buffer: 1 byte reg + len bytes data */
  uint8_t *tx_buf = malloc(1 + len);
  if (tx_buf == NULL) return -1;

  tx_buf[0] = reg;
  memcpy(tx_buf + 1, bufp, len);

  spi_transaction_t t = {
    .length = 8 * (1 + len),
    .tx_buffer = tx_buf,
    .rx_buffer = NULL,
  };
  esp_err_t ret = spi_device_transmit(imu_spi_handle, &t);
  free(tx_buf);
  return (ret == ESP_OK) ? 0 : -1;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  /* SPI read: set MSB of register address */
  uint8_t *tx_buf = calloc(1, 1 + len);
  uint8_t *rx_buf = malloc(1 + len);
  if (tx_buf == NULL || rx_buf == NULL) {
    free(tx_buf); free(rx_buf);
    return -1;
  }

  tx_buf[0] = reg | 0x80;  /* SPI read bit */

  spi_transaction_t t = {
    .length = 8 * (1 + len),
    .tx_buffer = tx_buf,
    .rx_buffer = rx_buf,
  };
  esp_err_t ret = spi_device_transmit(imu_spi_handle, &t);
  if (ret == ESP_OK) {
    memcpy(bufp, rx_buf + 1, len);  /* skip dummy byte */
  }
  free(tx_buf);
  free(rx_buf);
  return (ret == ESP_OK) ? 0 : -1;
}

/*
 * @brief  Send buffer to console (platform dependent)
 *
 * @param  tx_buffer     buffer to transmit
 * @param  len           number of byte to send
 */
static void tx_com(uint8_t *tx_buffer, uint16_t len)
{
  /* Output via TCP to all connected clients */
  tcp_server_broadcast(tx_buffer, len);
}

/*
 * @brief  platform specific delay (platform dependent)
 *
 * @param  ms        delay in ms
 */
static void platform_delay(uint32_t ms)
{
  vTaskDelay(pdMS_TO_TICKS(ms));
}

/*
 * @brief  platform specific initialization (platform dependent)
 */
static void platform_init(void *handle)
{
  /* Initialize SPI bus */
  spi_bus_config_t buscfg = {
    .mosi_io_num = IMU_SPI_MOSI_PIN,
    .miso_io_num = IMU_SPI_MISO_PIN,
    .sclk_io_num = IMU_SPI_SCK_PIN,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = 4096,
  };
  ESP_ERROR_CHECK(spi_bus_initialize(IMU_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO));

  spi_device_interface_config_t devcfg = {
    .clock_speed_hz = IMU_SPI_FREQ_HZ,
    .mode = 0,                       /* SPI mode 0 (CPOL=0, CPHA=0) */
    .spics_io_num = IMU_SPI_CS_PIN,
    .queue_size = 3,
  };
  ESP_ERROR_CHECK(spi_bus_add_device(IMU_SPI_HOST, &devcfg, &imu_spi_handle));
}
