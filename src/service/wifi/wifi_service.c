#include "wifi_service.h"
#include "wifi_config.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "bsp/wifi/wifi_bsp.h"

#define WIFI_TAG "WIFI_SVC"
#define WIFI_TASK_STACK 4096
#define WIFI_TASK_PRIO  4
#define WIFI_RECONNECT_DELAY_MS 5000

uint16_t WIFI_EVENT_BASE_ID = 0;

static wifi_state_t s_state = WIFI_STATE_DISCONNECTED;
static TaskHandle_t s_task_handle = NULL;

static void publish_event(wifi_event_t event_id)
{
    eventbus_publish(
        eventbus_make_event_id(WIFI_EVENT_BASE_ID, event_id),
        NULL, 0, pdMS_TO_TICKS(100));
}

static void wifi_service_task(void *arg)
{
    while (1) {
        if (strlen(WIFI_SSID) == 0) {
            ESP_LOGW(WIFI_TAG, "SSID not configured, skipping connect");
            s_state = WIFI_STATE_DISCONNECTED;
            vTaskDelay(pdMS_TO_TICKS(10000));
            continue;
        }

        s_state = WIFI_STATE_CONNECTING;
        publish_event(WIFI_EVENT_DISCONNECTED);

        exit_code_t ret = wifi_bsp_connect(WIFI_SSID, WIFI_PASSWORD);
        if (ret == EXIT_OK) {
            s_state = WIFI_STATE_CONNECTED;
            publish_event(WIFI_EVENT_CONNECTED);
            // 等待断开事件
            vTaskDelay(pdMS_TO_TICKS(30000));
        } else {
            s_state = WIFI_STATE_FAILED;
            publish_event(WIFI_EVENT_FAILED);
            ESP_LOGW(WIFI_TAG, "Connect failed, retrying in %dms", WIFI_RECONNECT_DELAY_MS);
            vTaskDelay(pdMS_TO_TICKS(WIFI_RECONNECT_DELAY_MS));
        }
    }
}

exit_code_t wifi_service_init(void)
{
    eventbus_allocate_module_id(&WIFI_EVENT_BASE_ID);
    ESP_LOGI(WIFI_TAG, "WiFi service init (module_id=%d)", WIFI_EVENT_BASE_ID);
    return EXIT_OK;
}

exit_code_t wifi_service_start(void)
{
    exit_code_t ret = wifi_bsp_init();
    if (ret != EXIT_OK) {
        return ret;
    }

    BaseType_t xret = xTaskCreatePinnedToCore(
        wifi_service_task, "wifi_svc", WIFI_TASK_STACK, NULL,
        WIFI_TASK_PRIO, &s_task_handle, 0);
    if (xret != pdPASS) {
        return EXIT_FAIL;
    }

    ESP_LOGI(WIFI_TAG, "WiFi service started");
    return EXIT_OK;
}

exit_code_t wifi_service_deinit(void)
{
    if (s_task_handle) {
        vTaskDelete(s_task_handle);
        s_task_handle = NULL;
    }
    wifi_bsp_disconnect();
    wifi_bsp_deinit();
    s_state = WIFI_STATE_DISCONNECTED;
    ESP_LOGI(WIFI_TAG, "WiFi service deinitialized");
    return EXIT_OK;
}

wifi_state_t wifi_service_get_state(void)
{
    return s_state;
}
