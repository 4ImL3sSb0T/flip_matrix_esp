#ifndef _IMU_SERVICE_H_
#define _IMU_SERVICE_H_

#include "service/tools/vec_math.h"
#include "service/tools/common_def.h"
#include "freertos/FreeRTOS.h"
#include "freertos/message_buffer.h"

typedef struct
{
    exit_code_t (*imu_init)(void);
    exit_code_t (*imu_deinit)(void);
    exit_code_t (*imu_get_mag)(vec3f *mag);
} imu_sensor_t;

exit_code_t imu_service_init(imu_sensor_t *imu_sensor);
exit_code_t imu_service_start(void);
exit_code_t imu_service_deinit(void);
bool imu_service_is_ok(void);

// 获取 acc ring buffer（数据类型 vec3f，单位 g）
MessageBufferHandle_t imu_service_get_acc_buffer(void);

#endif
