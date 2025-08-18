#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN GPIO_NUM_2  // Built-in LED on most ESP32 boards

void init(void)
{   
    // Step 1: Configure GPIO pin as output
    gpio_config_t io_config = {
        .pin_bit_mask = (1ULL << LED_PIN),     // Select which pin to configure
        .mode = GPIO_MODE_OUTPUT,              // Set as output mode
        .pull_up_en = GPIO_PULLUP_DISABLE,     // Disable pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // Disable pull-down  
        .intr_type = GPIO_INTR_DISABLE         // Disable interrupts
    };
    
    // Apply the configuration
    gpio_config(&io_config);

}

void led_on(void){
    // Turn LED ON (set pin HIGH)
    gpio_set_level(LED_PIN, 1);
    printf("LED ON\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Wait 1 second

}

void led_off(void){
    // Turn LED OFF (set pin LOW)
    gpio_set_level(LED_PIN, 0);
    printf("LED OFF\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Wait 1 second

}

void app_main(void)
{
    init(); 
    while(1) {
        led_on(); 
        led_off();             
    }
}