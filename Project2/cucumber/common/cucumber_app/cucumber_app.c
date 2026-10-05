#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_sntp.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "cucumber_app.h"
#include "cucumber_project_config.h"
#include "sdkconfig.h"

static const char *TAG = "cucumber_p2";
static bool s_sntp_started;

static void show_local_time(void)
{
    time_t now = 0;
    struct tm local_time;
    char text[40];

    time(&now);
    localtime_r(&now, &local_time);
    if (local_time.tm_year < (2016 - 1900)) {
        ESP_LOGI(TAG, "Waiting for NTP synchronization from %s", CUCUMBER_NTP_SERVER);
        return;
    }
    strftime(text, sizeof(text), "%Y-%m-%d %H:%M:%S %Z", &local_time);
    ESP_LOGI(TAG, "NTP synchronized; local time: %s", text);
}

static void time_report_task(void *argument)
{
    while (true) {
        show_local_time();
        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}

static void wifi_event_handler(void *argument, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_ERROR_CHECK(esp_wifi_connect());
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGW(TAG, "Wi-Fi disconnected; reconnecting");
        ESP_ERROR_CHECK(esp_wifi_connect());
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        const ip_event_got_ip_t *got_ip = event_data;
        ESP_LOGI(TAG, "DHCP address: " IPSTR, IP2STR(&got_ip->ip_info.ip));
        if (!s_sntp_started) {
            esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);
            esp_sntp_setservername(0, CUCUMBER_NTP_SERVER);
            esp_sntp_init();
            s_sntp_started = true;
        }
    }
}

void cucumber_app_start(void)
{
    esp_err_t nvs_result = nvs_flash_init();
    if (nvs_result == ESP_ERR_NVS_NO_FREE_PAGES ||
        nvs_result == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs_result = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs_result);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *station = esp_netif_create_default_wifi_sta();
    ESP_ERROR_CHECK(esp_netif_set_hostname(station, CONFIG_CUCUMBER_HOSTNAME));

    wifi_init_config_t init = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&init));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {.capable = true, .required = false},
        },
    };
    strlcpy((char *)wifi_config.sta.ssid, CUCUMBER_WIFI_SSID,
            sizeof(wifi_config.sta.ssid));
    strlcpy((char *)wifi_config.sta.password, CUCUMBER_WIFI_PASSWORD,
            sizeof(wifi_config.sta.password));

    setenv("TZ", CUCUMBER_TIMEZONE, 1);
    tzset();
    ESP_LOGI(TAG, "Board %d (%s) starting as %s", CONFIG_CUCUMBER_BOARD_ID,
             CONFIG_CUCUMBER_OWNER_NAME, CONFIG_CUCUMBER_HOSTNAME);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    xTaskCreate(time_report_task, "time_report", 3072, NULL, 4, NULL);
}
