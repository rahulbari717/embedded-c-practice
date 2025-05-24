/* Includes header files*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* macros */
#define LED_ON 				(1)
#define LED_OFF 			(0)
#define BLINK_DELAY_MS  		(1000)         	// Blinking delay in milliseconds

#define LED_PIN         		(2)           	// led pin

/* globle variables */
static const char *TAG = 		"BLINKY";  	// Tag for logging


// 1) create a struct with typedef 
// Let's create a structure to hold information about the LED.

typedef struct {
    gpio_num_t pin;         // GPIO pin number for the LED (e.g., pin 2)
    uint32_t on_delay_ms;   // How long the LED stays ON in milliseconds
    uint32_t off_delay_ms;  // How long the LED stays OFF in milliseconds
} LedConfig_t; // Now, you can use 'LedConfig_t' instead of 'struct LedConfig_t'


typedef enum {
	LED_Green,
	LED_BLUE
}LED_Type;

void Led_init(){
	// Example of using the typedef struct:
LedConfig_t my_led_config = {
    .pin = LED_PIN,
    .on_delay_ms = BLINK_DELAY_MS,
    .off_delay_ms = BLINK_DELAY_MS
};
	gpio_set_direction(my_led_config.pin, GPIO_MODE_OUTPUT);
}



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
