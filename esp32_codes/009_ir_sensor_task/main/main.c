#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define IR_SENSOR_PIN           GPIO_NUM_4
#define BUZZER_PIN              GPIO_NUM_32

static const char *TAG = "IR_BUZZER";

// Queue to communicate between tasks
QueueHandle_t ir_queue;

void init_ir_sensor(void){
    // Configure IR sensor pin as input
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << IR_SENSOR_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    
    // Configure buzzer pin as output
    io_conf.pin_bit_mask = (1ULL << BUZZER_PIN);
    io_conf.mode = GPIO_MODE_OUTPUT;
    gpio_config(&io_conf);
    
    // Initialize buzzer to OFF state
    gpio_set_level(BUZZER_PIN, 0);
    
    // Create queue for communication between tasks
    ir_queue = xQueueCreate(5, sizeof(int));
    
    ESP_LOGI(TAG, "IR sensor + buzzer initialize successful");
}

// IR sensor task - reads sensor and sends data to buzzer task
void ir_sensor_task(void *pvParameters) {
    int ir_state;
    
    ESP_LOGI(TAG, "IR sensor task started");
    
    while (1) {
        ir_state = gpio_get_level(IR_SENSOR_PIN);
        
        // Log the current IR sensor value
        ESP_LOGI(TAG, "IR Sensor Output: %d", ir_state);
        
        // Send IR state to buzzer task via queue
        if (xQueueSend(ir_queue, &ir_state, portMAX_DELAY) != pdPASS) {
            ESP_LOGE(TAG, "Failed to send IR state to queue");
        }
        
        vTaskDelay(pdMS_TO_TICKS(200)); // 200ms delay
    }
}

// Buzzer task - receives sensor data and controls buzzer
void buzzer_task(void *pvParameters) {
    int received_ir_state;
    
    ESP_LOGI(TAG, "Buzzer task started");
    
    while (1) {
        // Wait for IR sensor data from queue
        if (xQueueReceive(ir_queue, &received_ir_state, portMAX_DELAY) == pdPASS) {
            
            if (received_ir_state == 0) {  // Assuming LOW = Object detected
                gpio_set_level(BUZZER_PIN, 1);
                ESP_LOGI(TAG, "Object detected! Buzzer ON");
            } else {
                gpio_set_level(BUZZER_PIN, 0);
                ESP_LOGI(TAG, "No object. Buzzer OFF");
            }
        }
    }
}

void start_ir_sensor_task() {
    // Create IR sensor task
    xTaskCreate(
        ir_sensor_task,           // Task function
        "ir_sensor_task",         // Task name
        2048,                     // Stack size
        NULL,                     // Parameters
        5,                        // Priority
        NULL                      // Task handle
    );
    ESP_LOGI(TAG, "IR sensor task created");
}

void start_buzzer_task() {
    // Create buzzer task
    xTaskCreate(
        buzzer_task,              // Task function
        "buzzer_task",            // Task name
        2048,                     // Stack size
        NULL,                     // Parameters
        5,                        // Priority
        NULL                      // Task handle
    );
    ESP_LOGI(TAG, "Buzzer task created");
}

void app_main(void) {
    // Initialize hardware
    init_ir_sensor();
    
    // Start tasks
    start_ir_sensor_task();
    start_buzzer_task();
    
    ESP_LOGI(TAG, "All tasks started successfully");
}
