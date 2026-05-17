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

static TaskHandle_t imu_service_task_handle = NULL;
static int queue_size = 1;

const float acc_threshold_static = 0.1f;
const float acc_threshold_dynamic = 0.5f;
const float acc_threshold_shaking = 2.0f;

static imu_state_t current_state = IMU_STATE_ACTIVE;

static exit_code_t imu_service_dispath_event(const imu_data_t data)
{
    const float dt = 0.005f;
    const float g_ref = 1.0f;

    // ====== 阈值参数 ======
    const float static_acc_th = 0.05f;
    const float static_gyro_th = 3.0f;
    const float shake_hp_th = 0.6f;
    const float shake_exit_th = 0.3f;
    const float tap_hp_th = 1.2f;
    const float fall_acc_th = 0.25f;
    const float fall_exit_th = 0.7f;
    const float rotate_gyro_th = 120.0f;
    const float rotate_exit_th = 60.0f;
    const float flip_roll_th = 120.0f;

    const uint32_t tap_cooldown_ms = 200;
    const uint32_t flip_cooldown_ms = 1000;
    const uint32_t sleep_hold_ms = 10000;

    // ====== 持久状态 ======
    static float acc_lp = 1.0f;
    static float last_acc_mag = 1.0f;
    static uint32_t idle_ms = 0;
    static uint32_t tap_cooldown = 0;
    static uint32_t flip_cooldown = 0;

    // ====== 数据计算 ======
    float acc_mag = sqrtf(data.acc.x * data.acc.x +
                          data.acc.y * data.acc.y +
                          data.acc.z * data.acc.z);

    float gyro_mag = sqrtf(data.gyro.x * data.gyro.x +
                           data.gyro.y * data.gyro.y +
                           data.gyro.z * data.gyro.z);

    const float alpha = 0.05f;
    acc_lp = acc_lp + alpha * (acc_mag - acc_lp);

    float acc_hp = acc_mag - acc_lp;
    float acc_diff = fabsf(acc_mag - g_ref);

    float jerk = (acc_mag - last_acc_mag) / dt;
    last_acc_mag = acc_mag;

    // ====== 冷却计时 ======
    if (tap_cooldown)  { if (tap_cooldown > 5) tap_cooldown -= 5; else tap_cooldown = 0; }
    if (flip_cooldown) { if (flip_cooldown > 5) flip_cooldown -= 5; else flip_cooldown = 0; }

    // ====== 即时检测事件（独立于状态机） ======
    if (fabsf(acc_hp) > tap_hp_th && fabsf(jerk) > 30.0f && tap_cooldown == 0) {
        eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_TAP),
                         NULL, 0, 0);
        tap_cooldown = tap_cooldown_ms;
    }

    if ((fabsf(data.euler.x) > flip_roll_th || fabsf(data.euler.y) > flip_roll_th) &&
        flip_cooldown == 0)
    {
        eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_FLIP),
                         NULL, 0, 0);
        flip_cooldown = flip_cooldown_ms;
    }

    // ====== 状态机：确定下一状态 ======
    imu_state_t next_state = current_state;
    bool is_static = (acc_diff < static_acc_th && gyro_mag < static_gyro_th);

    switch (current_state) {
    case IMU_STATE_IDLE:
        if (!is_static) {
            next_state = IMU_STATE_ACTIVE;
        }
        break;

    case IMU_STATE_SLEEP:
        if (!is_static) {
            next_state = IMU_STATE_ACTIVE;
        }
        break;

    case IMU_STATE_ACTIVE:
        if (is_static) {
            next_state = IMU_STATE_IDLE;
        } else if (acc_mag < fall_acc_th) {
            next_state = IMU_STATE_FALLING;
        } else if (fabsf(acc_hp) > shake_hp_th) {
            next_state = IMU_STATE_SHAKING;
        } else if (gyro_mag > rotate_gyro_th) {
            next_state = IMU_STATE_ROTATING;
        }
        break;

    case IMU_STATE_SHAKING:
        if (fabsf(acc_hp) <= shake_exit_th) {
            next_state = IMU_STATE_ACTIVE;
        }
        break;

    case IMU_STATE_FALLING:
        if (acc_mag > fall_exit_th) {
            next_state = IMU_STATE_ACTIVE;
        }
        break;

    case IMU_STATE_ROTATING:
        if (gyro_mag < rotate_exit_th) {
            next_state = IMU_STATE_ACTIVE;
        }
        break;
    }

    // ====== 状态转移：发布事件 ======
    if (next_state != current_state) {
        switch (next_state) {
        case IMU_STATE_IDLE:
            idle_ms = 0;
            break;
        case IMU_STATE_ACTIVE:
            if (current_state == IMU_STATE_SLEEP) {
                eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_WAKE_UP),
                                 NULL, 0, 0);
            }
            break;
        case IMU_STATE_SHAKING:
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_SHAKE),
                             NULL, 0, 0);
            break;
        case IMU_STATE_FALLING:
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_FALLING),
                             NULL, 0, 0);
            break;
        case IMU_STATE_ROTATING:
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_ROTATING),
                             NULL, 0, 0);
            break;
        case IMU_STATE_SLEEP:
            break;
        }
        current_state = next_state;
    }

    // ====== IDLE 持续检测 → SLEEP ======
    if (current_state == IMU_STATE_IDLE) {
        idle_ms += 5;
        if (idle_ms >= sleep_hold_ms) {
            current_state = IMU_STATE_SLEEP;
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_SLEEP),
                             NULL, 0, 0);
        }
    }

    // PRINT(imu, "state=%d acc_mag=%.3f acc_hp=%.3f gyro=%.2f",
    //       current_state, acc_mag, acc_hp, gyro_mag);

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

imu_state_t imu_service_get_state() {
    return current_state;
}

imu_mode_t imu_service_get_mode() {
    return imu_mode;
}

exit_code_t imu_service_set_mode(const imu_mode_t mode) {
    if (mode > IMU_SERVICE_WITHOUT_MAG) return EXIT_INVALID_PARAM;
    imu_mode = mode;
    return EXIT_OK;
}
