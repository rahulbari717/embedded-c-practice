// ========================================
// FILE: main/main.c
// ========================================
#include <stdio.h>

#include "wifi_connect.h"
#include "mqtt.h" // Include our MQTT header
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "mqtt_client.h"

static char *TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting ESP32 MQTT application");
    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for 2 seconds to ensure WiFi is connected
    // Wait for Wi-Fi to be connected
    ESP_LOGI(TAG, "Waiting for Wi-Fi connection...");
    ESP_ERROR_CHECK(nvs_flash_init());

    // Initialize and connect to WiFi
    wifi_connect_init();
    ESP_ERROR_CHECK(wifi_connect_sta("Rahul", "rahul8459", 10000));
    ESP_LOGI(TAG, "Wi-Fi is now connected.");

    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for 2 seconds to ensure WiFi is connected
    // Initialize and start MQTT
    mqtt_init();
    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for 2 seconds to ensure WiFi is connected
    mqtt_start();
    vTaskDelay(pdMS_TO_TICKS(2000)); // Wait for 2 seconds to ensure WiFi is connected

    ESP_LOGI(TAG, "Application started successfully");
    // Create task for sending messages
    xTaskCreate(test_send_messages, "test send messages", 1024 * 2, NULL, 5, NULL);
}