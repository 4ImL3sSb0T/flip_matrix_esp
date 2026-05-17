#include "imu_service.h"
#include "MadgwickAHRS/MadgwickAHRS.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"
#include "math.h"
#include "esp_log.h"

SemaphoreHandle_t imu_sensor_handler_semaphore;
QueueHandle_t imu_data_queue;
uint16_t IMU_EVENT_BASE_ID;

static imu_sensor_t* imu_sensor_handler = NULL;
static imu_mode_t imu_mode = IMU_SERVICE_WITHOUT_MAG;
static vec3f euler_angle = {0.0f, 0.0f, 0.0f};
static TaskHandle_t imu_service_task_handle = NULL;
static int queue_size = 1;

const float acc_threshold_static = 0.1f;
const float acc_threshold_dynamic = 0.5f;
const float acc_threshold_shaking = 2.0f;

static exit_code_t imu_service_dispath_event(const imu_data_t data)
{
    const float dt = 0.005f;   // 5ms, 与 vTaskDelayUntil 匹配
    const float g_ref = 1.0f;  // 如果你的 acc 单位是 g

    // ====== 参数区（需要你现场调参） ======
    const float static_acc_th = 0.05f;     // 静止：|acc_mag-1g| < 0.05g
    const float static_gyro_th = 3.0f;     // 静止：gyro < 3 deg/s

    const float dynamic_acc_th = 0.15f;    // 动态：|acc_mag-1g| > 0.15g
    const float shake_hp_th = 0.6f;        // 摇晃：高通加速度幅值阈值
    const float tap_hp_th = 1.2f;          // 敲击：高通尖峰阈值
    const float fall_acc_th = 0.25f;       // 跌落：acc_mag < 0.25g

    const float flip_roll_th = 120.0f;     // 翻转阈值（角度）
    const float rotate_gyro_th = 120.0f;   // 旋转阈值 deg/s

    // 事件防抖（冷却时间）
    const uint32_t cooldown_ms = 300;

    // ====== 状态变量 ======
    static float acc_lp = 1.0f;
    static float last_acc_mag = 1.0f;

    static uint32_t static_ms = 0;
    static uint32_t dynamic_ms = 0;
    static uint32_t shake_ms = 0;

    static uint32_t tap_cooldown = 0;
    static uint32_t flip_cooldown = 0;
    static uint32_t shake_cooldown = 0;
    static uint32_t fall_cooldown = 0;
    static uint32_t rotate_cooldown = 0;

    // ====== 数据计算 ======
    float acc_mag = sqrtf(data.acc.x * data.acc.x +
                          data.acc.y * data.acc.y +
                          data.acc.z * data.acc.z);

    float gyro_mag = sqrtf(data.gyro.x * data.gyro.x +
                           data.gyro.y * data.gyro.y +
                           data.gyro.z * data.gyro.z);

    // 一阶低通滤波（估计重力基准）
    const float alpha = 0.05f;  // 0.01~0.1 可调
    acc_lp = acc_lp + alpha * (acc_mag - acc_lp);

    float acc_hp = acc_mag - acc_lp;
    float acc_diff = fabsf(acc_mag - g_ref);

    float jerk = (acc_mag - last_acc_mag) / dt;
    last_acc_mag = acc_mag;

    // ====== 冷却计时 ======
    if (tap_cooldown)    tap_cooldown -= 5;
    if (flip_cooldown)   flip_cooldown -= 5;
    if (shake_cooldown)  shake_cooldown -= 5;
    if (fall_cooldown)   fall_cooldown -= 5;
    if (rotate_cooldown) rotate_cooldown -= 5;

    // 防止 underflow
    if ((int32_t)tap_cooldown < 0) tap_cooldown = 0;
    if ((int32_t)flip_cooldown < 0) flip_cooldown = 0;
    if ((int32_t)shake_cooldown < 0) shake_cooldown = 0;
    if ((int32_t)fall_cooldown < 0) fall_cooldown = 0;
    if ((int32_t)rotate_cooldown < 0) rotate_cooldown = 0;

    // ====== 1. 静止检测 ======
    if (acc_diff < static_acc_th && gyro_mag < static_gyro_th) {
        static_ms += 5;
        dynamic_ms = 0;
        shake_ms = 0;

        if (static_ms > 10000) { // 静止超过 10 秒
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_SLEEP),
                             NULL, 0, 0);
            static_ms = 0;
        }
    } else {
        static_ms = 0;
    }

    // ====== 2. 普通动态 ======
    if (acc_diff > dynamic_acc_th || gyro_mag > 30.0f) {
        dynamic_ms += 5;
        if (dynamic_ms > 200) { // 动态持续 200ms
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_DYNAMIC),
                             NULL, 0, 0);
            dynamic_ms = 0;
        }
    } else {
        dynamic_ms = 0;
    }

    // ====== 3. 摇晃检测（高通加速度持续较大） ======
    if (fabsf(acc_hp) > shake_hp_th) {
        shake_ms += 5;
        if (shake_ms > 150 && shake_cooldown == 0) {
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_SHAKE),
                             NULL, 0, 0);
            shake_ms = 0;
            shake_cooldown = cooldown_ms;
        }
    } else {
        shake_ms = 0;
    }

    // ====== 4. 敲击检测（尖峰） ======
    // jerk 很大 + 高通幅值很大，基本就是敲击/撞击
    if (fabsf(acc_hp) > tap_hp_th && fabsf(jerk) > 50.0f && tap_cooldown == 0) {
        eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_TAP),
                         NULL, 0, 0);
        tap_cooldown = cooldown_ms;
    }

    // ====== 5. 自由落体检测 ======
    if (acc_mag < fall_acc_th && fall_cooldown == 0) {
        eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_FALLING),
                         NULL, 0, 0);
        fall_cooldown = 1000;
    }

    // ====== 6. 旋转检测（gyro大） ======
    if (gyro_mag > rotate_gyro_th && rotate_cooldown == 0) {
        eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_ROTATING),
                         NULL, 0, 0);
        rotate_cooldown = cooldown_ms;
    }

    // ====== 7. 翻转检测（基于欧拉角 roll/pitch） ======
    // 你已经有 Madgwick 输出的 euler
    if ((fabsf(data.euler.x) > flip_roll_th || fabsf(data.euler.y) > flip_roll_th) &&
        flip_cooldown == 0)
    {
        eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_FLIP),
                         NULL, 0, 0);
        flip_cooldown = 800;
    }

    // 调试打印
    // PRINT(imu, "acc_mag=%.3f acc_hp=%.3f jerk=%.2f gyro=%.2f", acc_mag, acc_hp, jerk, gyro_mag);

    return EXIT_OK;
}

static void imu_service_task(void* dt) {
    if (imu_sensor_handler == NULL) return;
    TickType_t ticks = xTaskGetTickCount();
    while (1) {
        imu_data_t imu_data;
        xSemaphoreTake(imu_sensor_handler_semaphore, portMAX_DELAY);
        imu_sensor_handler->imu_get_acc(&imu_data.acc);
        imu_sensor_handler->imu_get_gyro(&imu_data.gyro);
        imu_sensor_handler->imu_get_mag(&imu_data.mag);
        xSemaphoreGive(imu_sensor_handler_semaphore);
        switch (imu_mode) {
            case IMU_SERVICE_WITHOUT_MAG:
                MadgwickAHRSupdateIMU(imu_data.gyro.x, imu_data.gyro.y, imu_data.gyro.z, imu_data.acc.x, imu_data.acc.y, imu_data.acc.z);
                break;
            case IMU_SERVICE_WITH_MAG:
                MadgwickAHRSupdate(imu_data.gyro.x, imu_data.gyro.y, imu_data.gyro.z, imu_data.acc.x, imu_data.acc.y, imu_data.acc.z, imu_data.mag.x, imu_data.mag.y, imu_data.mag.z);
                break;
        }
        MadgwickAHRS_getEuler(&imu_data.euler.x, &imu_data.euler.y, &imu_data.euler.z);
        xQueueOverwrite(imu_data_queue, &imu_data);
        imu_service_dispath_event(imu_data);
        vTaskDelayUntil(&ticks, 5);
    }

}


exit_code_t imu_service_init(imu_sensor_t* imu_sensor) {
    if (imu_sensor == NULL || imu_sensor->imu_init == NULL || imu_sensor->imu_get_acc == NULL ||
        imu_sensor->imu_get_gyro == NULL || imu_sensor->imu_get_mag == NULL) return EXIT_INVALID_PARAM;

    exit_code_t ret = eventbus_allocate_module_id(&IMU_EVENT_BASE_ID);
    if (ret != EXIT_OK) return ret;
    imu_sensor_handler = imu_sensor;
    imu_sensor_handler->imu_init();
    imu_sensor_handler->is_initialized = true;
    imu_sensor_handler_semaphore = xSemaphoreCreateMutex();
    imu_data_queue = xQueueCreate(queue_size, sizeof(imu_data_t));
    return EXIT_OK;
}

exit_code_t imu_service_start() {
    if (imu_sensor_handler == NULL) return EXIT_NOT_INITIALIZED;
    const BaseType_t xTaskCreateStatus = xTaskCreate(imu_service_task, "IMU_Service", 4096, NULL, 1, &imu_service_task_handle);
    if (xTaskCreateStatus != pdPASS) return EXIT_FAIL;
    return EXIT_OK;
}

exit_code_t imu_service_get_euler(vec3f* euler) {
    if (imu_sensor_handler == NULL) return EXIT_NOT_INITIALIZED;
    imu_data_t imu_data;
    xQueuePeek(imu_data_queue, &imu_data, portMAX_DELAY);
    if (euler) *euler = imu_data.euler;
    return EXIT_OK;
}
exit_code_t imu_service_get_raw_data(vec3f* acc, vec3f* gyro, vec3f* mag) {
    if (imu_sensor_handler == NULL) return EXIT_NOT_INITIALIZED;
    imu_data_t imu_data;
    xQueuePeek(imu_data_queue, &imu_data, portMAX_DELAY);
    if (acc) *acc = imu_data.acc;
    if (gyro) *gyro = imu_data.gyro;
    if (mag) *mag = imu_data.mag;
    return EXIT_OK;
}
exit_code_t imu_service_get_data(imu_data_t *data) {
	if (imu_sensor_handler == NULL) return EXIT_NOT_INITIALIZED;
    imu_data_t imu_data;
    xQueuePeek(imu_data_queue, &imu_data, portMAX_DELAY);
    if (data) *data = imu_data;
    return EXIT_OK;
}
exit_code_t imu_service_deinit() {
	if (imu_sensor_handler == NULL || imu_sensor_handler->imu_deinit == NULL) return EXIT_NOT_INITIALIZED;
    vTaskDelete(imu_service_task_handle);
    xSemaphoreTake(imu_sensor_handler_semaphore, portMAX_DELAY);
    imu_sensor_handler->imu_deinit();
    xSemaphoreGive(imu_sensor_handler_semaphore);
    return EXIT_OK;
}

imu_mode_t imu_service_get_mode() {
    return imu_mode;
}

exit_code_t imu_service_set_mode(const imu_mode_t mode) {
    if (mode > IMU_SERVICE_WITHOUT_MAG) return EXIT_INVALID_PARAM;
    imu_mode = mode;
    return EXIT_OK;
}
