#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char* TAG = "BUZZER";

void buzzer_init(void) {
    // Configure buzzer pin as output
    gpio_config_t buzzer_config = {
        .pin_bit_mask = (1ULL << BUZZER_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&buzzer_config);
    
    // Turn off buzzer initially
    gpio_set_level(BUZZER_PIN, 0);
    ESP_LOGI(TAG, "Buzzer initialized on GPIO %d", BUZZER_PIN);
}

void buzzer_on(void) {
    gpio_set_level(BUZZER_PIN, 1);
    ESP_LOGI(TAG, "Buzzer turned ON");
}

void buzzer_off(void) {
    gpio_set_level(BUZZER_PIN, 0);
    ESP_LOGI(TAG, "Buzzer turned OFF");
}

void buzzer_beep_task(void *pvParameters) {
    ESP_LOGI(TAG, "Buzzer beep task started");
    
    // Turn on buzzer
    buzzer_on();
    
    // Wait for 1 second
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    // Turn off buzzer
    buzzer_off();
    
    // Delete this task
    vTaskDelete(NULL);
}
