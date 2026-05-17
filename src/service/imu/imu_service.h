#ifndef _IMU_SERVICE_H_
#define _IMU_SERVICE_H_

#include  "service/tools/vec_math.h"
#include "service/tools/common_def.h"
#include "FreeRTOS/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "service/event_bus/event_bus.h"

extern QueueHandle_t imu_data_queue;
extern EventBits_t imu_event_group;
extern uint16_t IMU_EVENT_BASE_ID;

typedef enum : uint32_t
{
    IMU_EVENT_LONG_STATIC,
    IMU_EVENT_DYNAMIC,
    IMU_EVENT_WAKE_UP,
    IMU_EVENT_FALLING,
    IMU_EVENT_RISING,
    IMU_EVENT_FLIP,
    IMU_EVENT_SHAKE,
    IMU_EVENT_TAP,
    IMU_EVENT_ROTATING
} imu_event_bits_t;

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
    exit_code_t (*imu_get_acc)(vec3f* acc);
    exit_code_t (*imu_get_gyro)(vec3f* gyro);
    exit_code_t (*imu_get_mag)(vec3f* mag);
    bool is_initialized;
} imu_sensor_t;

typedef enum
{
    IMU_SERVICE_WITH_MAG = 0,
    IMU_SERVICE_WITHOUT_MAG = 1
} imu_mode_t;


exit_code_t imu_service_init(imu_sensor_t* imu_sensor);
exit_code_t imu_service_start();
exit_code_t imu_service_deinit();

exit_code_t imu_service_get_euler(vec3f* euler);
exit_code_t imu_service_get_raw_data(vec3f* acc, vec3f* gyro, vec3f* mag);
exit_code_t imu_service_get_data(imu_data_t* data);

imu_mode_t imu_service_get_mode();
exit_code_t imu_service_set_mode(imu_mode_t mode);

#endif

