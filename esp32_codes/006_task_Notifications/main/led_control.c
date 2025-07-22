#include "led_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "LED_CTRL";

TaskHandle_t red_task_handle = NULL;
TaskHandle_t white_task_handle = NULL;

static void configure_gpio(int gpio_num) {
    gpio_reset_pin(gpio_num);
    gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT);
    gpio_set_level(gpio_num, 0);
}

void red_led_task(void *arg) {
    configure_gpio(RED_LED_GPIO);
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        ESP_LOGI(TAG, "RED ON");
        gpio_set_level(RED_LED_GPIO, 1);
        gpio_set_level(WHITE_LED_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        gpio_set_level(RED_LED_GPIO, 0);
        ESP_LOGI(TAG, "RED OFF");

        xTaskNotifyGive(white_task_handle);
    }
}

void white_led_task(void *arg) {
    configure_gpio(WHITE_LED_GPIO);
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        ESP_LOGI(TAG, "WHITE ON");
        gpio_set_level(WHITE_LED_GPIO, 1);
        gpio_set_level(RED_LED_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        gpio_set_level(WHITE_LED_GPIO, 0);
        ESP_LOGI(TAG, "WHITE OFF");

        xTaskNotifyGive(red_task_handle);
    }
}

void start_led_tasks(void) {
    xTaskCreatePinnedToCore(red_led_task, "Red_LED_Task", 2048, NULL, 5, &red_task_handle, 0);
    xTaskCreatePinnedToCore(white_led_task, "White_LED_Task", 2048, NULL, 5, &white_task_handle, 1);

    vTaskDelay(pdMS_TO_TICKS(500)); // Let tasks start up
    xTaskNotifyGive(red_task_handle); // Start with RED
}

