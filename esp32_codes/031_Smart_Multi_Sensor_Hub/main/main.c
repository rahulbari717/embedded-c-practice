/**
 * @file main.c
 * @brief Main application entry point for the Smart Multi-Sensor Hub.
 * * @author Rahul B.
 * @version 1.0
 * @date August 2025
 */

// #include "esp_log.h"

#include "esp_debub.h"
#include "esp_config.h"
#include "my_nvs_storage.h"
#include "nimble.h"

// static const char *TAG = "MAIN";

/**
 * @brief The main application entry point.
 * * This function initializes the device, configures settings,
 * initializes and uses the NVS storage, and then runs the main application loop.
 */
void app_main()
{
	/**
	 * @brief Logs the reset reason of the ESP32.
	 * * This helps in debugging issues related to unexpected reboots.
	 */
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

	/**
	 * @brief Prints a greeting message to the console.
	 */
	printf("Hello, World!\n");
	ibeacon();
}