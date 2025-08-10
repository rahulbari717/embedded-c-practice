/**
 * @file led_blink_freertos.c
 * @brief ESP-IDF FreeRTOS example - Blink 3 LEDs using individual tasks
 * @author Rahul B.
 *
 * This example demonstrates how to blink three LEDs at different rates
 * using separate FreeRTOS tasks. It uses the ESP-IDF GPIO driver and 
 * FreeRTOS task creation API.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

// ---------------- TAG FOR LOGGING ----------------
static const char *TAG = "LED_APP";

// -------------------- GPIO PINS --------------------
#define RED_LED_PIN             GPIO_NUM_2
#define YELLOW_LED_PIN          GPIO_NUM_4
#define BLUE_LED_PIN            GPIO_NUM_5

// -------------------- LED STATES --------------------
#define LED_ON                  1
#define LED_OFF                 0

// -------------------- TASK CONFIG --------------------
#define LED_TASK_STACK_SIZE     2048
#define LED_TASK_PRIORITY       5

// -------------------- BLINK DELAYS (ms) --------------------
#define RED_LED_DELAY_MS        1000
#define YELLOW_LED_DELAY_MS     2000
#define BLUE_LED_DELAY_MS       3000

/**
 * @brief Initialize GPIO pins for LEDs
 */
static void init_leds(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << RED_LED_PIN) | (1ULL << YELLOW_LED_PIN) | (1ULL << BLUE_LED_PIN),
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    ESP_LOGI(TAG, "LED GPIOs initialized");
}

/**
 * @brief Task for blinking RED LED
 */
static void red_led_task(void *pvParameters) {
    (void) pvParameters; // Unused
    ESP_LOGI(TAG, "Red LED task started");
    for (;;) {
        gpio_set_level(RED_LED_PIN, LED_ON);
        ESP_LOGI(TAG, "Red LED ON");
        vTaskDelay(pdMS_TO_TICKS(RED_LED_DELAY_MS));

        gpio_set_level(RED_LED_PIN, LED_OFF);
        ESP_LOGI(TAG, "Red LED OFF");
        vTaskDelay(pdMS_TO_TICKS(RED_LED_DELAY_MS));
    }
}

/**
 * @brief Task for blinking YELLOW LED
 */
static void yellow_led_task(void *pvParameters) {
    (void) pvParameters; // Unused
    ESP_LOGI(TAG, "Yellow LED task started");
    for (;;) {
        gpio_set_level(YELLOW_LED_PIN, LED_ON);
        ESP_LOGI(TAG, "Yellow LED ON");
        vTaskDelay(pdMS_TO_TICKS(YELLOW_LED_DELAY_MS));

        gpio_set_level(YELLOW_LED_PIN, LED_OFF);
        ESP_LOGI(TAG, "Yellow LED OFF");
        vTaskDelay(pdMS_TO_TICKS(YELLOW_LED_DELAY_MS));
    }
}

/**
 * @brief Task for blinking BLUE LED
 */
static void blue_led_task(void *pvParameters) {
    (void) pvParameters; // Unused
    ESP_LOGI(TAG, "Blue LED task started");
    for (;;) {
        gpio_set_level(BLUE_LED_PIN, LED_ON);
        ESP_LOGI(TAG, "Blue LED ON");
        vTaskDelay(pdMS_TO_TICKS(BLUE_LED_DELAY_MS));

        gpio_set_level(BLUE_LED_PIN, LED_OFF);
        ESP_LOGI(TAG, "Blue LED OFF");
        vTaskDelay(pdMS_TO_TICKS(BLUE_LED_DELAY_MS));
    }
}

/**
 * @brief Create LED blinking tasks
 */
static void start_led_tasks(void) {
    BaseType_t xReturned;

    xReturned = xTaskCreate(red_led_task, "Red_LED_Task", LED_TASK_STACK_SIZE, NULL, LED_TASK_PRIORITY, NULL);
    configASSERT(xReturned == pdPASS);

    xReturned = xTaskCreate(yellow_led_task, "Yellow_LED_Task", LED_TASK_STACK_SIZE, NULL, LED_TASK_PRIORITY, NULL);
    configASSERT(xReturned == pdPASS);

    xReturned = xTaskCreate(blue_led_task, "Blue_LED_Task", LED_TASK_STACK_SIZE, NULL, LED_TASK_PRIORITY, NULL);
    configASSERT(xReturned == pdPASS);

    ESP_LOGI(TAG, "All LED tasks created successfully");
}

/**
 * @brief Main application entry point
 */
void app_main(void) {
    ESP_LOGI(TAG, "Application started");

    init_leds();
    start_led_tasks();
}
