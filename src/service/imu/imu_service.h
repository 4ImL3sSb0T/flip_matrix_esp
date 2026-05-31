#ifndef _IMU_SERVICE_H_
#define _IMU_SERVICE_H_

#include  "service/tools/vec_math.h"
#include "service/tools/common_def.h"
#include "FreeRTOS/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/stream_buffer.h"
#include "freertos/event_groups.h"

#include "service/event_bus/event_bus.h"
#include "bsp/imu963ra/imu963ra.h"

extern QueueHandle_t imu_data_queue;
extern EventBits_t imu_event_group;
extern uint16_t IMU_EVENT_BASE_ID;

// IMU 运行状态（状态机）
typedef enum {
    IMU_STATE_IDLE,       // 静止
    IMU_STATE_ACTIVE,     // 正常运动
    IMU_STATE_SHAKING,    // 摇晃
    IMU_STATE_FALLING,    // 自由落体
    IMU_STATE_ROTATING,   // 高速旋转
    IMU_STATE_SLEEP,      // 深度休眠（IDLE 持续 10s）
} imu_state_t;

// 状态转移时发布的事件，TAP/FLIP 为即时检测事件
// 所有事件 payload 均为 imu_data_t
typedef enum : uint32_t
{
    IMU_EVENT_SLEEP,      // → SLEEP
    IMU_EVENT_WAKE_UP,    // SLEEP → ACTIVE
    IMU_EVENT_FALLING,    // → FALLING
    IMU_EVENT_FLIP,       // 即时检测
    IMU_EVENT_SHAKE,      // → SHAKING
    IMU_EVENT_TAP,        // 即时检测
    IMU_EVENT_ROTATING    // → ROTATING
} imu_event_t;

typedef struct {
    vec3f acc;
    vec3f gyro;
    vec3f mag;
    vec3f euler;
} imu_data_t;

typedef struct
{
    exit_code_t (*imu_init)();
    exit_code_t (*imu_deinit)();
    // 轮询接口
    exit_code_t (*imu_get_acc)(vec3f* acc);
    exit_code_t (*imu_get_gyro)(vec3f* gyro);
    exit_code_t (*imu_get_mag)(vec3f* mag);
    // FIFO 接口（可选，NULL 则无法使用 FIFO 模式）
    exit_code_t (*imu_fifo_init)(void);
    int32_t (*imu_fifo_read_samples)(imu_sample_t *samples, uint32_t max_samples);
    uint32_t (*imu_get_odr_hz)(void);
    bool is_initialized;
} imu_sensor_t;

typedef enum
{
    IMU_SERVICE_WITH_MAG = 0,
    IMU_SERVICE_WITHOUT_MAG = 1
} imu_mode_t;

// IMU 运行模式：轮询 vs FIFO
typedef enum {
    IMU_RUN_MODE_POLLING = 0,   // 200Hz 轮询（FLIP 水仿真 + 状态机）
    IMU_RUN_MODE_FIFO = 1,      // 833Hz FIFO + 中断（高频震动分析，数据写入 ring buffer）
} imu_run_mode_t;

exit_code_t imu_service_set_run_mode(imu_run_mode_t mode);
exit_code_t imu_service_init(imu_sensor_t* imu_sensor);
exit_code_t imu_service_start();
exit_code_t imu_service_deinit();

exit_code_t imu_service_get_euler(vec3f* euler);
exit_code_t imu_service_get_raw_data(vec3f* acc, vec3f* gyro, vec3f* mag);
exit_code_t imu_service_get_data(imu_data_t* data);

// FIFO 模式：获取 ring buffer 句柄（供 DSP 任务读取原始 imu_sample_t 数据）
// 仅在 IMU_RUN_MODE_FIFO 模式下有效，轮询模式返回 NULL
StreamBufferHandle_t imu_service_get_fifo_buffer(void);

imu_state_t imu_service_get_state();
imu_mode_t imu_service_get_mode();
exit_code_t imu_service_set_mode(imu_mode_t mode);

#endif

