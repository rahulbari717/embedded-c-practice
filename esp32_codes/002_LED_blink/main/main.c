#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 2
#define LED_ON 1
#define LED_OFF 0

const char *TAG = "LED";

void app_main(void)
{
    gpio_set_direction(LED, GPIO_MODE_OUTPUT); 

    while (1){

        gpio_set_level(LED, LED_ON);
        ESP_LOGI(TAG, "LED ON");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        gpio_set_level(LED, LED_OFF);
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
