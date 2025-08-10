#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define IR_SENSOR_PIN           GPIO_NUM_4
#define BUZZER_PIN              GPIO_NUM_32

static const char *TAG = "IR_BUZZER";

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

    ESP_LOGI(TAG, "IR sensor + buzzer initialize successfull");
}
 

void app_main(void)
{

    init_ir_sensor(); 

    while (1) {
        int ir_state = gpio_get_level(IR_SENSOR_PIN);

        // Log the current IR sensor value continuously
        ESP_LOGI(TAG, "IR Sensor Output: %d", ir_state);

        if (ir_state == 0) {  // Assuming LOW = Object detected
            gpio_set_level(BUZZER_PIN, 1);
            ESP_LOGI(TAG, "Object detected! Buzzer ON");
        } else {
            gpio_set_level(BUZZER_PIN, 0);
            ESP_LOGI(TAG, "No object. Buzzer OFF");
        }

        vTaskDelay(pdMS_TO_TICKS(200)); // 200ms delay
    }
}

