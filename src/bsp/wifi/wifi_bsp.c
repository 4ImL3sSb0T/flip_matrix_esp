#include "wifi_bsp.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "nvs_flash.h"

#define WIFI_TAG "WIFI_BSP"

static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static esp_netif_t *s_sta_netif = NULL;
static esp_event_handler_instance_t s_wifi_handler = NULL;
static esp_event_handler_instance_t s_ip_handler = NULL;
static int s_retry_count = 0;
#define WIFI_BSP_MAX_RETRY 5

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_count < WIFI_BSP_MAX_RETRY) {
            esp_wifi_connect();
            s_retry_count++;
            ESP_LOGW(WIFI_TAG, "Retrying connection (%d/%d)", s_retry_count, WIFI_BSP_MAX_RETRY);
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
            ESP_LOGE(WIFI_TAG, "Connection failed after %d retries", WIFI_BSP_MAX_RETRY);
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(WIFI_TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_count = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

exit_code_t wifi_bsp_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK) {
        ESP_LOGE(WIFI_TAG, "NVS init failed: %s", esp_err_to_name(ret));
        return EXIT_FAIL;
    }

    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    s_sta_netif = esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &s_wifi_handler));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &s_ip_handler));

    ESP_LOGI(WIFI_TAG, "WiFi BSP initialized");
    return EXIT_OK;
}

exit_code_t wifi_bsp_deinit(void)
{
    if (s_wifi_handler) {
        esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, s_wifi_handler);
        s_wifi_handler = NULL;
    }
    if (s_ip_handler) {
        esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, s_ip_handler);
        s_ip_handler = NULL;
    }
    esp_wifi_stop();
    esp_wifi_deinit();
    if (s_sta_netif) {
        esp_netif_destroy_default_wifi(s_sta_netif);
        s_sta_netif = NULL;
    }
    esp_event_loop_delete_default();
    if (s_wifi_event_group) {
        vEventGroupDelete(s_wifi_event_group);
        s_wifi_event_group = NULL;
    }
    ESP_LOGI(WIFI_TAG, "WiFi BSP deinitialized");
    return EXIT_OK;
}

exit_code_t wifi_bsp_connect(const char *ssid, const char *password)
{
    if (!ssid || !password) {
        return EXIT_INVALID_PARAM;
    }

    s_retry_count = 0;
    xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT);

    wifi_config_t wifi_config = {0};
    strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(WIFI_TAG, "Connecting to SSID: %s", ssid);

    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdTRUE, pdFALSE, portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(WIFI_TAG, "Connected");
        return EXIT_OK;
    }
    return EXIT_FAIL;
}

exit_code_t wifi_bsp_disconnect(void)
{
    esp_wifi_disconnect();
    esp_wifi_stop();
    ESP_LOGI(WIFI_TAG, "Disconnected");
    return EXIT_OK;
}
