#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include <stdbool.h>

#include "service/tools/vec_math.h"
#include "service/tools/common_def.h"
#include "zf_device_imu963ra.h"

static int IMU963RA_MOSI_PIN = GPIO_NUM_11;
static int IMU963RA_MISO_PIN = GPIO_NUM_12;
static int IMU963RA_SCK_PIN  = GPIO_NUM_13;
static int IMU963RA_CS_PIN   = GPIO_NUM_10;
static int IMU963RA_INT1_PIN = GPIO_NUM_9;

static spi_device_handle_t spi;


static void imu963ra_spi_write_reg(uint8_t reg, uint8_t data)
{
    uint8_t tx[2] = { reg, data };
    // uint8_t rx[2];
    
    spi_transaction_t t = {
        .length = 8 * sizeof(tx), // bit
        .tx_buffer = tx,
    };
    ESP_ERROR_CHECK(spi_device_transmit(spi, &t));
}

static uint8_t imu963ra_spi_read_reg(uint8_t reg)
{
    uint8_t tx[2] = { reg, 0x00 };
    uint8_t rx[2] = { 0 };
    
    spi_transaction_t t = {
        .length = 8 * sizeof(tx), // bit
        .tx_buffer = tx,
        .rx_buffer = rx,
    };
    ESP_ERROR_CHECK(spi_device_transmit(spi, &t));
    return rx[1];
}

static void imu963ra_spi_read_regs(uint8_t reg, uint8_t *buf, uint32_t len)
{
    uint8_t tx_buf[7];
    uint8_t rx_buf[7];
    tx_buf[0] = reg;
    for (uint32_t i = 1; i <= len; i++)
        tx_buf[i] = 0x00;
    
    spi_transaction_t t = {
        .length = 8 * (len + 1), // bit
        .tx_buffer = tx_buf,
        .rx_buffer = rx_buf,
    };
    ESP_ERROR_CHECK(spi_device_transmit(spi, &t));
    for (uint32_t i = 0; i < len; i++)
        buf[i] = rx_buf[i + 1];
}

/* ── Original ZF logic (types & delays adapted) ─────────────────────── */

#define imu963ra_write_acc_gyro_register(reg, data)   imu963ra_spi_write_reg((reg) | IMU963RA_SPI_W, (data))
#define imu963ra_read_acc_gyro_register(reg)           imu963ra_spi_read_reg((reg) | IMU963RA_SPI_R)
#define imu963ra_read_acc_gyro_registers(reg, buf, len) imu963ra_spi_read_regs((reg) | IMU963RA_SPI_R, (buf), (len))

static uint8_t imu963ra_write_mag_register(uint8_t addr, uint8_t reg, uint8_t data)
{
    uint8_t return_state = 0;
    uint16_t timeout_count = 0;

    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x00);
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 0);
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);
    imu963ra_write_acc_gyro_register(IMU963RA_DATAWRITE_SLV0, data);
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);

    while (0 == (0x80 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        if (IMU963RA_TIMEOUT_COUNT < timeout_count++)
        {
            return_state = 1;
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(2));
    }
    return return_state;
}

static uint8_t imu963ra_read_mag_register(uint8_t addr, uint8_t reg)
{
    uint16_t timeout_count = 0;

    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x01);
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);

    while (0 == (0x01 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        if (IMU963RA_TIMEOUT_COUNT < timeout_count++)
        {
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(2));
    }

    return imu963ra_read_acc_gyro_register(IMU963RA_SENSOR_HUB_1);
}

static void imu963ra_connect_mag(uint8_t addr, uint8_t reg)
{
    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x06);
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x6C);
}

static uint8_t imu963ra_acc_gyro_self_check(void)
{
    uint8_t return_state = 0;
    uint8_t dat = 0;
    uint16_t timeout_count = 0;

    while (0x6B != dat)
    {
        if (IMU963RA_TIMEOUT_COUNT < timeout_count++)
        {
            return_state = 1;
            break;
        }
        dat = imu963ra_read_acc_gyro_register(IMU963RA_WHO_AM_I);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    return return_state;
}

static uint8_t imu963ra_mag_self_check(void)
{
    uint8_t return_state = 0;
    uint8_t dat = 0;
    uint16_t timeout_count = 0;

    while (0xff != dat)
    {
        if (IMU963RA_TIMEOUT_COUNT < timeout_count++)
        {
            return_state = 1;
            break;
        }
        dat = imu963ra_read_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CHIP_ID);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    return return_state;
}

/* ── Public API ─────────────────────────────────────────────────────── */

int16_t imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z;
int16_t imu963ra_acc_x,  imu963ra_acc_y,  imu963ra_acc_z;
int16_t imu963ra_mag_x,  imu963ra_mag_y,  imu963ra_mag_z;
float imu963ra_transition_factor[3] = { 4098, 14.3, 3000 };

void imu963ra_get_acc(void)
{
    uint8_t dat[6];
    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_A, dat, 6);
    imu963ra_acc_x = (int16_t)((uint16_t)dat[1] << 8 | dat[0]);
    imu963ra_acc_y = (int16_t)((uint16_t)dat[3] << 8 | dat[2]);
    imu963ra_acc_z = (int16_t)((uint16_t)dat[5] << 8 | dat[4]);
}

void imu963ra_get_gyro(void)
{
    uint8_t dat[6];
    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_G, dat, 6);
    imu963ra_gyro_x = (int16_t)((uint16_t)dat[1] << 8 | dat[0]);
    imu963ra_gyro_y = (int16_t)((uint16_t)dat[3] << 8 | dat[2]);
    imu963ra_gyro_z = (int16_t)((uint16_t)dat[5] << 8 | dat[4]);
}

void imu963ra_get_mag(void)
{
    uint8_t temp_status;
    uint8_t dat[6];

    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);
    temp_status = imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER);
    if (0x01 & temp_status)
    {
        imu963ra_read_acc_gyro_registers(IMU963RA_SENSOR_HUB_1, dat, 6);
        imu963ra_mag_x = (int16_t)((uint16_t)dat[1] << 8 | dat[0]);
        imu963ra_mag_y = (int16_t)((uint16_t)dat[3] << 8 | dat[2]);
        imu963ra_mag_z = (int16_t)((uint16_t)dat[5] << 8 | dat[4]);
    }
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
}

static bool imu_initialized = false;

exit_code_t imu963ra_init(void)
{
    spi_bus_config_t buscfg = {
        .mosi_io_num = IMU963RA_MOSI_PIN,
        .miso_io_num = IMU963RA_MISO_PIN,
        .sclk_io_num = IMU963RA_SCK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4096
    };

    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000,  // 10MHz
        .mode = 0,                            // SPI模式0~3
        .spics_io_num = IMU963RA_CS_PIN,     // CS脚
        .queue_size = 3,
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &spi));


    uint8_t return_state = 0;
    vTaskDelay(pdMS_TO_TICKS(10));

    do
    {
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x01);
        vTaskDelay(pdMS_TO_TICKS(2));
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
        if (imu963ra_acc_gyro_self_check())
        {
            return_state = 1;
            break;
        }

        imu963ra_write_acc_gyro_register(IMU963RA_INT1_CTRL, 0x03);

        switch (IMU963RA_ACC_SAMPLE_DEFAULT)
        {
        default:
            return_state = 1;
            break;
        case IMU963RA_ACC_SAMPLE_SGN_2G:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x30);
            imu963ra_transition_factor[0] = 16393;
            break;
        case IMU963RA_ACC_SAMPLE_SGN_4G:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x38);
            imu963ra_transition_factor[0] = 8197;
            break;
        case IMU963RA_ACC_SAMPLE_SGN_8G:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x8C);
            imu963ra_transition_factor[0] = 4098;
            break;
        case IMU963RA_ACC_SAMPLE_SGN_16G:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x34);
            imu963ra_transition_factor[0] = 2049;
            break;
        }
        if (1 == return_state) break;

        switch (IMU963RA_GYRO_SAMPLE_DEFAULT)
        {
        default:
            return_state = 1;
            break;
        case IMU963RA_GYRO_SAMPLE_SGN_125DPS:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x52);
            imu963ra_transition_factor[1] = 228.6;
            break;
        case IMU963RA_GYRO_SAMPLE_SGN_250DPS:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x50);
            imu963ra_transition_factor[1] = 114.3;
            break;
        case IMU963RA_GYRO_SAMPLE_SGN_500DPS:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x54);
            imu963ra_transition_factor[1] = 57.1;
            break;
        case IMU963RA_GYRO_SAMPLE_SGN_1000DPS:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x58);
            imu963ra_transition_factor[1] = 28.6;
            break;
        case IMU963RA_GYRO_SAMPLE_SGN_2000DPS:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x8C);
            imu963ra_transition_factor[1] = 14.3;
            break;
        case IMU963RA_GYRO_SAMPLE_SGN_4000DPS:
            imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x51);
            imu963ra_transition_factor[1] = 7.1;
            break;
        }
        if (1 == return_state) break;

        imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x44);
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL4_C, 0x02);
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL5_C, 0x00);
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL6_C, 0x00);
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL7_G, 0x00);
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL9_XL, 0x01);

        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);
        imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x80);
        vTaskDelay(pdMS_TO_TICKS(2));
        imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x00);
        vTaskDelay(pdMS_TO_TICKS(2));

        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x80);
        vTaskDelay(pdMS_TO_TICKS(2));
        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x00);
        vTaskDelay(pdMS_TO_TICKS(2));

        if (imu963ra_mag_self_check())
        {
            return_state = 1;
            break;
        }

        switch (IMU963RA_MAG_SAMPLE_DEFAULT)
        {
        default:
            return_state = 1;
            break;
        case IMU963RA_MAG_SAMPLE_2G:
            imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL1, 0x09);
            imu963ra_transition_factor[2] = 12000;
            break;
        case IMU963RA_MAG_SAMPLE_8G:
            imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL1, 0x19);
            imu963ra_transition_factor[2] = 3000;
            break;
        }
        if (1 == return_state) break;

        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_FBR, 0x01);
        imu963ra_connect_mag(IMU963RA_MAG_ADDR, IMU963RA_MAG_OUTX_L);
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
        vTaskDelay(pdMS_TO_TICKS(20));

    } while (0);

    if (return_state == 0)
    {
        imu_initialized = true;
        return EXIT_OK;
    }
    return EXIT_HW_FAILURE;
}

exit_code_t imu963ra_deinit(void)
{
    imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x01);
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x00);
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
    imu_initialized = false;
    return EXIT_OK;
}

#define DEG_TO_RAD 0.017453292519943295f

exit_code_t imu963ra_read_acc(vec3f *acc)
{
    if (!imu_initialized || acc == NULL) return EXIT_NOT_INITIALIZED;
    imu963ra_get_acc();
    acc->x = (float)imu963ra_acc_x / imu963ra_transition_factor[0];
    acc->y = (float)imu963ra_acc_y / imu963ra_transition_factor[0];
    acc->z = (float)imu963ra_acc_z / imu963ra_transition_factor[0];
    return EXIT_OK;
}

exit_code_t imu963ra_read_gyro(vec3f *gyro)
{
    if (!imu_initialized || gyro == NULL) return EXIT_NOT_INITIALIZED;
    imu963ra_get_gyro();
    gyro->x = ((float)imu963ra_gyro_x / imu963ra_transition_factor[1]) * DEG_TO_RAD;
    gyro->y = ((float)imu963ra_gyro_y / imu963ra_transition_factor[1]) * DEG_TO_RAD;
    gyro->z = ((float)imu963ra_gyro_z / imu963ra_transition_factor[1]) * DEG_TO_RAD;
    return EXIT_OK;
}

exit_code_t imu963ra_read_mag(vec3f *mag)
{
    if (!imu_initialized || mag == NULL) return EXIT_NOT_INITIALIZED;
    imu963ra_get_mag();
    mag->x = (float)imu963ra_mag_x / imu963ra_transition_factor[2];
    mag->y = (float)imu963ra_mag_y / imu963ra_transition_factor[2];
    mag->z = (float)imu963ra_mag_z / imu963ra_transition_factor[2];
    return EXIT_OK;
}
