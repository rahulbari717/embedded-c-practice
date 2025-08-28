/*
 * This is basic code for task notifications workings
 * */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_attr.h" // For IRAM_ATTR

#define LED_GPIO 2     // Built-in LED on most ESP32 dev boards
#define BUTTON_GPIO 32 // Boot button on many ESP32 dev boards

static TaskHandle_t led_task_handle = NULL;
static TaskHandle_t reciever_handler = NULL;

// ISR Handler
static void IRAM_ATTR button_isr_handler(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(led_task_handle, &xHigherPriorityTaskWoken);
    if (xHigherPriorityTaskWoken)
    {
        portYIELD_FROM_ISR();
    }
}

// LED Task (Receiver)
void led_task(void *param)
{
    while (true)
    {
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY); // Wait for notification
        printf("received notification\n");

        gpio_set_level(LED_GPIO, 1);     // LED ON
        vTaskDelay(pdMS_TO_TICKS(3000)); // Keep ON for 500ms
        gpio_set_level(LED_GPIO, 0);     // LED OFF
    }
}

void init(void)
{
    // Configure LED GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);

    // Configure Button GPIO with interrupt
    io_conf.pin_bit_mask = (1ULL << BUTTON_GPIO);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1; // Pull-up for boot button
    io_conf.pull_down_en = 0;
    io_conf.intr_type = GPIO_INTR_NEGEDGE; // Falling edge on press
    gpio_config(&io_conf);

    // Install GPIO ISR service
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_GPIO, button_isr_handler, NULL);
}

void sender(void *arg)
{
    while (1)
    {
        // printf("Sending notification to receiver task\n");
        xTaskNotifyGive(reciever_handler); // Send notification to receiver task
        xTaskNotifyGive(reciever_handler); // Send notification to receiver task

        xTaskNotifyGive(reciever_handler); // Send notification to receiver task
        xTaskNotifyGive(reciever_handler); // Send notification to receiver task
        xTaskNotifyGive(reciever_handler); // Send notification to receiver task
        vTaskDelay(pdMS_TO_TICKS(5000));   // Delay for 2 seconds
    }
}

void reciever(void *arg)
{
    // this perticular task will recieve notification from sender task
    // and holds the notification until it is recieved.

    while (1)
    {
        int count = ulTaskNotifyTake(pdFALSE, portMAX_DELAY); // Wait for notification
        printf("Received notification %d in receiver task\n", count++);
    }
}

void app_main(void)
{
    // init();
    // // Create LED task
    // xTaskCreate(led_task, "LED Task", 2048, NULL, 2, &led_task_handle);

    xTaskCreate(&reciever, "reciever", 2048, NULL, 5, &reciever_handler);
    xTaskCreate(&sender, "sender", 2048, NULL, 5, NULL);
}
