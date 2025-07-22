/**
 * @file    main.c
 * @brief   ESP32-PICO 1 LED and 1 buzzer Control with push buttons (2) using FreeRTOS 
 * @author  Rahul B. 
 * @version 2.0
 * @date    22nd July 2025
 * 
* @description 
*           This project implements a simple control system using an ESP32-PICO microcontroller.
*           The system features two push buttons that control a LED and a buzzer independently.
*           Button 1 (GPIO 32) triggers the LED to turn on for 2 seconds when pressed.
*           Button 2 (GPIO 33) activates the buzzer for 1 second when pressed.
*           The system utilizes FreeRTOS for task management and hardware control.
 * 
 * @hardware
 * - Target: ESP32-PICO Development Board
 * - Buttons: GPIO 32 and GPIO 33
 * - LED    : GPIO 2
 * - BUZZER : GPIO 4
*/

/*============================================================================
 * Include Files
 *============================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "led.h"
#include "buzzer.h"
#include "button.h"

static const char* TAG = "MAIN";

/* Reset reason lookup table */
static const char *reset_reasons[] = {
                                        "ESP_RST_UNKNOWN", 
                                        "ESP_RST_POWERON", 
                                        "ESP_RST_EXT", 
                                        "ESP_RST_SW",
                                        "ESP_RST_PANIC", 
                                        "ESP_RST_INT_WDT", 
                                        "ESP_RST_TASK_WDT", 
                                        "ESP_RST_WDT",
                                        "ESP_RST_DEEPSLEEP", 
                                        "ESP_RST_BROWNOUT", 
                                        "ESP_RST_SDIO"
};


/* ────── Shutdown Handler ────── */
void FirmwareShutdownHandler(void) {
    char task_info[1024];
    TaskHandle_t current = xTaskGetCurrentTaskHandle();
    printf("Shutdown from: %s\n", pcTaskGetName(current));
    vTaskList(task_info);
    printf("Active Tasks:\n%s\n", task_info);
}

/* ────── Initializer ────── */
static esp_err_t initializer(void) {
    // Initialize all components
    ESP_LOGI(TAG, "Start Intialize Button-LED-Buzzer System");
    led_init();
    buzzer_init();
    button_init();
    return ESP_OK;
}


/**
 * @brief Print project and system details in banner format
 */
static void print_project_banner(void)
{
    ESP_LOGI(TAG, "\n");
//    ESP_LOGI(TAG, "🔥 Starting ESP32 Dual LED Controller");
    ESP_LOGI(TAG, "================================================");
    ESP_LOGI(TAG, "Project    : ESP32-PICO LED Buzzer Push Buttons");
    ESP_LOGI(TAG, "Author     : Rahul B.");
    ESP_LOGI(TAG, "Version    : 2.0");
    ESP_LOGI(TAG, "Board      : ESP32-PICO Development Board");
    ESP_LOGI(TAG, "FreeRTOS   : %s", tskKERNEL_VERSION_NUMBER);
    ESP_LOGI(TAG, "ESP-IDF    : %s", esp_get_idf_version());
    ESP_LOGI(TAG, "================================================");
}

/**
 * @brief Initialize system-level settings and handlers with error handling
 */
static void initialize_system(void)
{
    printf("Software Start...\n");

    // Set log level
    esp_log_level_set(TAG, ESP_LOG_DEBUG);

    // Log reset reason
    esp_reset_reason_t reason = esp_reset_reason();
    printf("Reset Reason: %s\n", reset_reasons[reason]);

    // Register shutdown handler
    esp_err_t ret = esp_register_shutdown_handler(FirmwareShutdownHandler);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register shutdown handler: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGD(TAG, "Shutdown handler registered successfully");
    }

    // Initialize system components
    ret = initializer();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "System initializer failed: %s", esp_err_to_name(ret));
        vTaskDelay(pdMS_TO_TICKS(100));
        esp_restart();
    }

    ESP_LOGD(TAG, "System initialized successfully");
}

void app_main(void) {

    initialize_system();
    print_project_banner();
    
    // Create button monitoring task
    BaseType_t result = xTaskCreate(button_monitor_task, "button_monitor_task", 4096, NULL, 10, NULL);
if (result != pdPASS) {
    ESP_LOGE(TAG, "Failed to create button monitor task");
}

    
    ESP_LOGI(TAG, "System initialized successfully!");
    ESP_LOGI(TAG, "Press Button 1 (GPIO 32) to turn on LED for 2 seconds");
    ESP_LOGI(TAG, "Press Button 2 (GPIO 33) to turn on Buzzer for 1 second");
}
