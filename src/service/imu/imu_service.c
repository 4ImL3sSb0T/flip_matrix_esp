#include "imu_service.h"
#include "MadgwickAHRS/MadgwickAHRS.h"
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"
#include "math.h"

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

static exit_code_t imu_service_dispath_event(imu_data_t data) {
    static uint32_t static_counter = 0;
    static uint32_t dynamic_counter = 0;
    static uint32_t flip_counter = 0;
    static uint32_t shaking_counter = 0;
    static uint32_t falling_counter = 0;
    static uint32_t rising_counter = 0;

    float acc_magnitude = sqrtf(data.acc.x * data.acc.x + data.acc.y * data.acc.y + data.acc.z * data.acc.z);
    float acc_diff = fabsf(acc_magnitude - 1.0f); // Assuming 1g is the static state

    float gyro_magnitude = sqrtf(data.gyro.x * data.gyro.x + data.gyro.y * data.gyro.y + data.gyro.z * data.gyro.z);

    if (acc_diff < acc_threshold_static && gyro_magnitude < 0.1f) {
        static_counter++;
        dynamic_counter = 0;
        shaking_counter = 0;
        flip_counter = 0;
        falling_counter = 0;
        rising_counter = 0;
        if (static_counter > 1000) {
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_LONG_STATIC), NULL, 0, portMAX_DELAY);
            static_counter = 0;
        }
    } else if (acc_diff >= acc_threshold_static && acc_diff < acc_threshold_dynamic) {
        dynamic_counter++;
        static_counter = 0;
        shaking_counter = 0;
        flip_counter = 0;
        falling_counter = 0;
        rising_counter = 0;
        if (dynamic_counter > 10) {
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_DYNAMIC), NULL, 0, portMAX_DELAY);
            dynamic_counter = 0;
        }
    } else if (acc_diff >= acc_threshold_dynamic && acc_diff < acc_threshold_shaking) {
        shaking_counter++;
        static_counter = 0;
        dynamic_counter = 0;
        flip_counter = 0;
        falling_counter = 0;
        rising_counter = 0;
        if (shaking_counter > 10) {
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_WAKE_UP), NULL, 0, portMAX_DELAY);
            shaking_counter = 0;
        }
    } else if (acc_diff >= acc_threshold_shaking) {
        flip_counter++;
        static_counter = 0;
        dynamic_counter = 0;
        shaking_counter = 0;
        falling_counter = 0;
        rising_counter = 0;
        if (flip_counter > 10) {
            eventbus_publish(eventbus_make_event_id(IMU_EVENT_BASE_ID, IMU_EVENT_FLIP), NULL, 0, portMAX_DELAY);
            flip_counter = 0;
        }
    }

     // Additional logic for falling and rising events can be implemented here based on specific thresholds and conditions
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
    const BaseType_t xTaskCreateStatus = xTaskCreate(imu_service_task, "IMU_Service", configMINIMAL_STACK_SIZE, NULL, 1, &imu_service_task_handle);
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
