/**
 * @file main.c
 * @brief Main application entry point for the Smart Multi-Sensor Hub.
 * @author Rahul B.
 * @version 1.0
 * @date August 2025
 */

#include "esp_debub.h"
#include "esp_config.h"
#include "my_nvs_storage.h"

#include "wifi_connect.h"
#include "mqtt_client.h"

#include "mqtt.h" // Include our MQTT header
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sntp_time.h"

#define WAIT_TIME (60 * 2000) // 2 minute
static const char *TAG = "MAIN";

/**
 * @brief The main application entry point.
 * * This function initializes the device, configures settings,
 * initializes and uses the NVS storage, and then runs the main application loop.
 */
void app_main()
{

	ResetReason();
	/**
	 * @brief Initializes and loads configuration from Kconfig.
	 * * The settings for Wi-Fi and other parameters are read from this.
	 */
	menu_config();

	/**
	 * @brief Initializes and saves/retrieves data from NVS.
	 * * This function handles all Non-Volatile Storage operations.
	 */
	initialize_and_use_nvs();

	// while (1)
	// {

	// 	wifi_connect_ap("rahul_esp32", "password");
	// 	vTaskDelay(pdMS_TO_TICKS(WAIT_TIME));
	// 	wifi_disconnect();

	// 	wifi_connect_sta("Rahul", "rahul8459", 10000);
	// 	vTaskDelay(pdMS_TO_TICKS(WAIT_TIME));
	// 	sntp();
	// 	wifi_disconnect();
	// }

	// mqtt_app_start();

	// Start WiFi with improved error handling
	esp_err_t wifi_result = start_wifi();
	if (wifi_result != ESP_OK)
	{
		ESP_LOGE(TAG, "WiFi initialization failed: %s", esp_err_to_name(wifi_result));
		// Could start AP mode here for configuration
		return;
	}

	// vTaskDelay(pdMS_TO_TICKS(WAIT_TIME));

	// mqtt_main();

	/**
	 * @brief Prints a greeting message to the console.
	 */
	printf("Hello, World!\n");
}