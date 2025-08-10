#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIR_SENSOR_PIN          GPIO_NUM_4
#define LED_PIN                 GPIO_NUM_2   // Built-in LED
#define LED_ON_TIME_SEC         2            // LED stays ON for 5 seconds

static const char *TAG = "PIR_LED";

void init_pir_sensor(void){
    // Configure PIR sensor pin as input
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PIR_SENSOR_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    
    // Configure LED pin as output
    io_conf.pin_bit_mask = (1ULL << LED_PIN);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);
    
    // Initialize LED to OFF state
    gpio_set_level(LED_PIN, 0);
    
    ESP_LOGI(TAG, "PIR sensor + LED initialize successful");
    ESP_LOGI(TAG, "LED will stay ON for %d seconds when motion detected", LED_ON_TIME_SEC);
}

// PIR sensor task with 5-second timer
void pir_sensor_task(void *pvParameters) {
    int pir_state;
    int motion_count = 0;
    
    ESP_LOGI(TAG, "PIR sensor task started");
    
    while (1) {
        pir_state = gpio_get_level(PIR_SENSOR_PIN);
        
        if (pir_state == 1) {  // PIR HIGH = Motion detected
            motion_count++;
            
            // Turn ON LED
            gpio_set_level(LED_PIN, 1);
            ESP_LOGI(TAG, "🚨 MOTION #%d DETECTED! LED ON for %d seconds", motion_count, LED_ON_TIME_SEC);
            
            // Keep LED ON for defined time
            vTaskDelay(pdMS_TO_TICKS(LED_ON_TIME_SEC * 1000));
            
            // After 5 seconds, check motion again
            pir_state = gpio_get_level(PIR_SENSOR_PIN);
            
            if (pir_state == 1) {
                ESP_LOGI(TAG, "✅ Motion still detected after %d seconds - LED stays ON", LED_ON_TIME_SEC);
                // LED remains ON, continue loop for another check
            } else {
                // Turn OFF LED
                gpio_set_level(LED_PIN, 0);
                ESP_LOGI(TAG, "❌ No motion after %d seconds - LED OFF", LED_ON_TIME_SEC);
            }
            
        } else {  // PIR LOW = No motion
            // Turn OFF LED
            gpio_set_level(LED_PIN, 0);
            ESP_LOGI(TAG, "No motion detected - LED OFF");
        }
        
        vTaskDelay(pdMS_TO_TICKS(100)); // Check every 200ms
    }
}

void start_pir_sensor_task() {
    // Create PIR sensor task
    xTaskCreate(
        pir_sensor_task,          // Task function
        "pir_sensor_task",        // Task name
        2048,                     // Stack size
        NULL,                     // Parameters
        5,                        // Priority
        NULL                      // Task handle
    );
    ESP_LOGI(TAG, "PIR sensor task created");
}

void app_main(void) {
    // Initialize hardware
    init_pir_sensor();
    
    // Start task
    start_pir_sensor_task();
    
    ESP_LOGI(TAG, "PIR Motion Detection System Started!");
    ESP_LOGI(TAG, "LED ON for %d seconds when motion detected", LED_ON_TIME_SEC);
}