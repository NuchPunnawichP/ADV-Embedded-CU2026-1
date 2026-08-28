#include <stdbool.h>
#include <stdint.h>

#include "driver/gpio.h"
#include "esp_chip_info.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define CUCUMBER_STATUS_LED_GPIO GPIO_NUM_2
#define BLINK_PERIOD_MS 1000

static const char *TAG = "cucumber";

void app_main(void)
{
    const gpio_config_t led_config = {
        .pin_bit_mask = 1ULL << CUCUMBER_STATUS_LED_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    ESP_ERROR_CHECK(gpio_config(&led_config));

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    ESP_LOGI(TAG, "Cucumber ESP32-S2 starter is running");
    ESP_LOGI(TAG, "Detected %d CPU core(s)", chip_info.cores);
    ESP_LOGI(TAG, "Status LED is connected to GPIO%d", CUCUMBER_STATUS_LED_GPIO);

    bool led_on = false;
    while (true) {
        led_on = !led_on;
        ESP_ERROR_CHECK(gpio_set_level(CUCUMBER_STATUS_LED_GPIO, led_on));
        ESP_LOGI(TAG, "LED on GPIO%d: %s", CUCUMBER_STATUS_LED_GPIO,
                 led_on ? "ON" : "OFF");
        vTaskDelay(pdMS_TO_TICKS(BLINK_PERIOD_MS));
    }
}
