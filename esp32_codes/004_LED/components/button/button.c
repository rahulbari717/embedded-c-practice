#include "button.h"
#include "led.h"
#include "buzzer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char* TAG = "BUTTON";
static int button1_prev_state = 1; // Assuming pull-up, so released = 1
static int button2_prev_state = 1;

void button_init(void) {
    // Configure button 1 pin as input with pull-up
    gpio_config_t button1_config = {
        .pin_bit_mask = (1ULL << BUTTON1_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&button1_config);
    
    // Configure button 2 pin as input with pull-up
    gpio_config_t button2_config = {
        .pin_bit_mask = (1ULL << BUTTON2_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&button2_config);
    
    ESP_LOGI(TAG, "Buttons initialized - Button1: GPIO %d, Button2: GPIO %d", BUTTON1_PIN, BUTTON2_PIN);
}

int button1_is_pressed(void) {
    return !gpio_get_level(BUTTON1_PIN); // Inverted because of pull-up
}

int button2_is_pressed(void) {
    return !gpio_get_level(BUTTON2_PIN); // Inverted because of pull-up
}

void button_monitor_task(void *pvParameters) {
    ESP_LOGI(TAG, "Button monitor task started");
    
    while (1) {
        int button1_current = button1_is_pressed();
        int button2_current = button2_is_pressed();
        
        // Button 1 pressed (detect rising edge)
        if (button1_current && !button1_prev_state) {
            ESP_LOGI(TAG, "Button 1 pressed - Starting LED task");
            xTaskCreate(led_blink_task, "led_blink_task", 2048, NULL, 5, NULL);
        }
        
        // Button 2 pressed (detect rising edge)
        if (button2_current && !button2_prev_state) {
            ESP_LOGI(TAG, "Button 2 pressed - Starting Buzzer task");
            xTaskCreate(buzzer_beep_task, "buzzer_beep_task", 2048, NULL, 5, NULL);
        }
        
        // Update previous states
        button1_prev_state = button1_current;
        button2_prev_state = button2_current;
        
        // Small delay to prevent bouncing and reduce CPU usage
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
