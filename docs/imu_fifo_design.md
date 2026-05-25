# IMU FIFO + 中断驱动采样设计文档

## 1. 背景

当前 IMU 架构是 200Hz 轮询：FreeRTOS 任务每 5ms 执行 3 次阻塞 SPI 读取（acc/gyro/mag），数据经 Madgwick 滤波后发布。LSM6DSR 的 ODR 实际已设为 16.6kHz，但被软件丢弃到 200Hz，浪费了传感器能力。

**目标**: 利用 LSM6DSR 硬件 FIFO + INT1 中断，实现 833Hz 高频采样，批量读取，提升运动检测精度。

## 2. 架构对比

### 旧架构（轮询）

```
IMU963RA (ODR 16.6kHz)
    │
    │  每 5ms 轮询
    v
imu_service_task (200Hz, priority 1)
    ├── SPI read acc   (阻塞)
    ├── SPI read gyro  (阻塞)
    ├── SPI read mag   (阻塞, Sensor Hub I2C)
    ├── Madgwick filter (sampleFreq=200.0f)
    ├── xQueueOverwrite → 消费者
    └── 状态机 + 事件总线
```

### 新架构（FIFO + 中断）

```
IMU963RA FIFO (ODR=BDR=833Hz, Continuous模式)
    │
    │  watermark=100帧 触发 INT1
    v
ESP32 GPIO ISR (GPIO_NUM_14, 上升沿)
    │
    │  vTaskNotifyGiveFromISR
    v
IMU_FIFO task (priority 3, stack 8192)
    ├── ulTaskNotifyTake (阻塞等待)
    ├── 批量 SPI 读取 FIFO (100帧 × 7字节 = 700字节)
    ├── 解析 tag → acc[] + gyro[] 配对
    ├── 读取磁力计 (~100Hz, 每10批一次)
    ├── Madgwick filter (833Hz)
    ├── xQueueOverwrite → 消费者
    └── 状态机 + 事件总线 (仅最后样本)
```

## 3. 设计参数

| 参数 | 值 | 理由 |
|------|-----|------|
| ODR/BDR | 833Hz | 4x 当前速率，流体仿真足够 |
| FIFO 模式 | Continuous (0b110) | 溢出时覆盖旧数据，不阻塞传感器 |
| Watermark | 100 帧 | ~120ms 缓冲，700 字节批量读 |
| 压缩 | 关闭 | 833Hz 数据量不大 |
| 磁力计 | ~100Hz | 不在 FIFO 中，每 10 批读一次 |
| Madgwick | 833Hz 全速 | ESP32-S3 双核 240MHz，算力充足 |
| INT1 引脚 | GPIO_NUM_14 | 硬件确认 |
| 任务优先级 | 3 | 高于 IMU(1)，低于显示(10) |
| 任务栈 | 8192 字节 | 批量缓冲 700B + Madgwick 计算 |

## 4. 寄存器配置

### 传感器 ODR 和量程

| 寄存器 | 地址 | 值 | 含义 |
|--------|------|-----|------|
| CTRL1_XL | 0x10 | 0x7C | ODR=833Hz, FS=±8g |
| CTRL2_G | 0x11 | 0x7C | ODR=833Hz, FS=2000dps |
| CTRL3_C | 0x12 | 0x44 | BDU=1, IF_INC=1 |
| CTRL4_C | 0x13 | 0x02 | I2C_disable=1 |

### FIFO 配置

| 寄存器 | 地址 | 值 | 含义 |
|--------|------|-----|------|
| FIFO_CTRL1 | 0x07 | 0x64 | WTM[7:0]=100 |
| FIFO_CTRL2 | 0x08 | 0x00 | WTM8=0, 无压缩 |
| FIFO_CTRL3 | 0x09 | 0x77 | BDR_GY=833Hz, BDR_XL=833Hz |
| FIFO_CTRL4 | 0x0A | 0x06 | FIFO_MODE=Continuous |

### 中断配置

| 寄存器 | 地址 | 值 | 含义 |
|--------|------|-----|------|
| INT1_CTRL | 0x0D | 0x10 | 仅 FIFO watermark 中断 |

### BDR 编码 (FIFO_CTRL3)

| 编码 | BDR |
|------|-----|
| 0x01 | 1.6 Hz |
| 0x02 | 12.5 Hz |
| 0x03 | 26 Hz |
| 0x04 | 52 Hz |
| 0x05 | 104 Hz |
| 0x06 | 208 Hz |
| 0x07 | 417 Hz |
| 0x08 | 833 Hz |
| 0x09 | 1667 Hz |
| 0x0A | 3333 Hz |
| 0x0B | 6667 Hz |

## 5. 文件修改

### 5.1 `src/bsp/imu963ra/zf_device_imu963ra.h`

**删除**:
- `extern int16_t imu963ra_acc_x/y/z`, `imu963ra_gyro_x/y/z` 等全局变量
- `imu963ra_get_acc/gyro/mag()` 内部函数声明
- `imu963ra_read_acc/gyro()` 公共函数声明

**新增**:
```c
// FIFO 批量数据结构
typedef struct {
    int16_t acc_x, acc_y, acc_z;
    int16_t gyro_x, gyro_y, gyro_z;
} imu963ra_sample_t;

// FIFO 配置
typedef struct {
    int int1_pin;         // GPIO 引脚 (GPIO_NUM_14)
    uint16_t watermark;   // 水印阈值 (100)
} imu963ra_fifo_config_t;

// 新 API
exit_code_t imu963ra_fifo_init(imu963ra_fifo_config_t *cfg);
exit_code_t imu963ra_read_fifo_batch(imu963ra_sample_t *samples, uint16_t max_count, uint16_t *actual_count);
float imu963ra_get_sample_rate(void);
void imu963ra_set_fifo_task_handle(TaskHandle_t handle);
```

### 5.2 `src/bsp/imu963ra/zf_device_imu963ra.c`

**修改 `spi_read_regs()`**: 缓冲区从 7 字节扩大到 707 字节
```c
#define FIFO_MAX_BURST_BYTES  707  // 100帧 × 7字节 + 余量

static void imu963ra_spi_read_regs(uint8_t reg, uint8_t *buf, uint32_t len)
{
    uint8_t tx_buf[FIFO_MAX_BURST_BYTES];
    uint8_t rx_buf[FIFO_MAX_BURST_BYTES];
    tx_buf[0] = reg;
    memset(tx_buf + 1, 0x00, len);
    spi_transaction_t t = {
        .length = 8 * (len + 1),
        .tx_buffer = tx_buf,
        .rx_buffer = rx_buf,
    };
    ESP_ERROR_CHECK(spi_device_transmit(spi, &t));
    memcpy(buf, rx_buf + 1, len);
}
```

**修改 `imu963ra_init()`**:
- ODR 改为 833Hz: `CTRL1_XL=0x7C`, `CTRL2_G=0x7C`
- 新增 FIFO 配置: `FIFO_CTRL1-4`
- INT1_CTRL 改为 `0x10`（仅 watermark 中断）
- 保留量程选择的 transition factor 赋值
- 删除旧的 ODR switch-case 块（ODR 固定为 833Hz）
- 磁力计初始化不变

**新增 `imu963ra_fifo_init()`**:
```c
static TaskHandle_t fifo_task_handle = NULL;

static void IRAM_ATTR imu963ra_int1_isr(void *arg)
{
    if (fifo_task_handle != NULL) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        vTaskNotifyGiveFromISR(fifo_task_handle, &xHigherPriorityTaskWoken);
        if (xHigherPriorityTaskWoken) portYIELD_FROM_ISR();
    }
}

exit_code_t imu963ra_fifo_init(imu963ra_fifo_config_t *cfg)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << cfg->int1_pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&io_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(cfg->int1_pin, imu963ra_int1_isr, NULL);
    return EXIT_OK;
}
```

**新增 `imu963ra_read_fifo_batch()`**:
1. 读 `FIFO_STATUS1+2` 获取未读帧数
2. 批量读 `fifo_count × 7` 字节
3. 遍历每帧，解析 tag:
   - `0x02` = 加速度计 (NC 格式)
   - `0x01` = 陀螺仪 (NC 格式)
   - 其他忽略
4. 当 acc + gyro 都有时，输出一个配对样本

**删除**: `imu963ra_get_acc/gyro/mag()`, `imu963ra_read_acc/gyro()`

### 5.3 `src/service/imu/imu_service.h`

**扩展 `imu_sensor_t` vtable**:
```c
typedef struct {
    exit_code_t (*imu_init)(void);
    exit_code_t (*imu_deinit)(void);
    exit_code_t (*imu_get_acc)(vec3f *acc);      // 保留兼容
    exit_code_t (*imu_get_gyro)(vec3f *gyro);    // 保留兼容
    exit_code_t (*imu_get_mag)(vec3f *mag);

    // 新增: FIFO 接口 (可选，NULL 则回退轮询)
    exit_code_t (*imu_fifo_init)(void *cfg);
    exit_code_t (*imu_read_fifo_batch)(void *samples, uint16_t max, uint16_t *actual);
    float (*imu_get_sample_rate)(void);

    bool is_initialized;
} imu_sensor_t;
```

**新增**:
```c
typedef struct {
    uint16_t fifo_watermark;
    int decimation_factor;  // 1=全速, 4=~208Hz
} imu_fifo_config_t;

exit_code_t imu_service_init_fifo(imu_sensor_t *imu_sensor, imu_fifo_config_t *fifo_cfg);
```

### 5.4 `src/service/imu/imu_service.c`

**新增 `imu_fifo_service_task()`**:
```c
static void imu_fifo_service_task(void *arg)
{
    imu963ra_sample_t fifo_samples[120];
    uint32_t mag_counter = 0;
    vec3f last_mag = {0};

    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // 等待 ISR

        uint16_t count = 0;
        imu_sensor_handler->imu_read_fifo_batch(fifo_samples, 120, &count);
        if (count == 0) continue;

        // 每 10 批读一次磁力计 (~100Hz)
        if (++mag_counter >= 10) {
            mag_counter = 0;
            xSemaphoreTake(imu_sensor_handler_semaphore, portMAX_DELAY);
            imu_sensor_handler->imu_get_mag(&last_mag);
            xSemaphoreGive(imu_sensor_handler_semaphore);
        }

        // 每个样本过 Madgwick
        for (uint16_t i = 0; i < count; i++) {
            imu_data_t imu_data;
            // 转换物理单位 → Madgwick → xQueueOverwrite
            // 状态机仅在最后样本调度
            if (i == count - 1)
                imu_service_dispath_event(imu_data);
        }
    }
}
```

**新增 `imu_service_init_fifo()`**: 初始化硬件 + FIFO + GPIO ISR + 创建队列

**修改 `imu_service_start()`**: 检测 FIFO 指针，有则创建 FIFO 任务，无则回退旧任务

### 5.5 `src/service/imu/MadgwickAHRS/MadgwickAHRS.c`

```c
// 修改前:
#define sampleFreq  200.0f

// 修改后:
static float sampleFreq = 200.0f;
void MadgwickAHRS_setSampleFreq(float freq) { sampleFreq = freq; }
```

### 5.6 `main/main.c`

```c
static imu_sensor_t imu963ra_sensor = {
    .imu_init = imu963ra_init,
    .imu_deinit = imu963ra_deinit,
    .imu_get_acc = NULL,          // FIFO 模式不使用
    .imu_get_gyro = NULL,         // FIFO 模式不使用
    .imu_get_mag = imu963ra_read_mag,
    .imu_fifo_init = (exit_code_t(*)(void*))imu963ra_fifo_init,
    .imu_read_fifo_batch = (exit_code_t(*)(void*,uint16_t,uint16_t*))imu963ra_read_fifo_batch,
    .imu_get_sample_rate = imu963ra_get_sample_rate,
    .is_initialized = false,
};
imu_service_init_fifo(&imu963ra_sensor, NULL);
imu_service_start();
```

### 5.7 `src/app/app_water_sim.c` — 无改动

队列接口不变，事件订阅不变。

## 6. FIFO Tag 解析

LSM6DSR FIFO 每帧 7 字节: 1 TAG + 6 DATA

| Tag | 含义 |
|-----|------|
| 0x01 | Gyroscope NC (非压缩) |
| 0x02 | Accelerometer NC (非压缩) |
| 0x03 | Temperature |
| 0x04 | Timestamp |
| 0x06-0x09 | Accelerometer 压缩 |
| 0x0A-0x0D | Gyroscope 压缩 |

数据格式 (NC): TAG(1B) + X_L(1B) + X_H(1B) + Y_L(1B) + Y_H(1B) + Z_L(1B) + Z_H(1B)

解析逻辑: 跟踪最后读到的 acc 和 gyro，当两者都有时输出一个配对样本。

## 7. 实现顺序

1. Madgwick: `sampleFreq` 改动态 + setter
2. BSP 头文件: 新类型和声明
3. BSP 源文件: spi_read_regs 扩大 → init 改 FIFO 配置 → 新增函数 → 删除旧函数
4. IMU Service 头文件: vtable 扩展 + 新声明
5. IMU Service 源文件: 新 FIFO 任务 + init_fifo + 修改 start
6. main.c: 更新 vtable 和初始化调用
7. `idf.py build` 编译验证

## 8. 验证方法

1. `idf.py build` 编译通过
2. 烧录后串口监控: 读取 FIFO_STATUS1/2 确认帧数增长
3. INT1 引脚逻辑分析仪: 应以 ~8.3Hz 频率触发 (833Hz / 100帧)
4. 日志输出: 确认 acc/gyro 数据合理，Madgwick 四元数收敛
5. 水仿真仍正常工作 (60Hz 读取 acc.x/acc.y)
6. 状态机事件 (TAP/SHAKE 等) 仍正常触发

## 9. 已知风险

| 风险 | 影响 | 缓解 |
|------|------|------|
| FIFO tag 顺序不确定 | acc/gyro 配对可能错位 | 跟踪"最后值"策略，丢一帧可接受 |
| `gpio_install_isr_service` 重复调用 | 初始化失败 | 检查返回值，忽略 `ESP_ERR_INVALID_STATE` |
| SPI 总线竞争 | 数据损坏 | FIFO 任务是唯一 SPI 用户，互斥锁保护 mag 读取 |
| Watermark 中断未清除 | 中断风暴 | 读 FIFO 到 watermark 以下自动清除 |
| Madgwick 积分时间漂移 | 四元数偏差 | 833Hz 下偏差极小，可接受 |
