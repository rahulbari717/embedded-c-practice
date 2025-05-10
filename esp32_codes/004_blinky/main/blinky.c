#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freeRTOS/task.h"
#include "driver/gpio.h"

#define LED_PIN         2           // led pin    

void app_main(void)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    uint32_t isOn = 0;
    while(1)
    {
        isOn = !isOn;
        gpio_set_level(LED_PIN, isOn);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
