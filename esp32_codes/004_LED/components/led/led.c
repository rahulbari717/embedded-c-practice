#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char* TAG = "LED";

void led_init(void) {
    // Configure LED pin as output
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << LED_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led_config);
    
    // Turn off LED initially
    gpio_set_level(LED_PIN, 0);
    ESP_LOGI(TAG, "LED initialized on GPIO %d", LED_PIN);
}

void led_on(void) {
    gpio_set_level(LED_PIN, 1);
    ESP_LOGI(TAG, "LED turned ON");
}

void led_off(void) {
    gpio_set_level(LED_PIN, 0);
    ESP_LOGI(TAG, "LED turned OFF");
}

void led_blink_task(void *pvParameters) {
    ESP_LOGI(TAG, "LED blink task started");
    
    // Turn on LED
    led_on();
    
    // Wait for 2 seconds
    vTaskDelay(pdMS_TO_TICKS(2000));
    
    // Turn off LED
    led_off();
    
    // Delete this task
    vTaskDelete(NULL);
}
