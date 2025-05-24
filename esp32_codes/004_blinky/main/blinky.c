#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_ON 				(1)
#define LED_OFF 			(0)
#define BLINK_DELAY_MS  		(1000)         	// Blinking delay in milliseconds

#define LED_PIN         		(2)           	// led pin
static const char *TAG = 		"BLINKY";  	// Tag for logging

/**
 * @brief Blink LED function - runs indefinitely
 */
static void blink_led(void)
{
    ESP_LOGI(TAG, "Blinky application started");
    
    while(1)
    {
        // Turn LED ON
        gpio_set_level(LED_PIN, LED_ON);
        ESP_LOGI(TAG, "LED ON");
        vTaskDelay(BLINK_DELAY_MS / portTICK_PERIOD_MS);
        
        // Turn LED OFF
        gpio_set_level(LED_PIN, LED_OFF);
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(BLINK_DELAY_MS / portTICK_PERIOD_MS);
    }
}


void app_main(void)
{
    // Configure LED pin as output
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
   blink_led(); 
}
