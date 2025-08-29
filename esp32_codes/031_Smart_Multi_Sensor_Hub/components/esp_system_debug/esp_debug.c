/**
 * @file esp_debug.c
 * @brief Firmware debugging and logging functions.
 * * @author Rahul B.
 * @version 1.0
 * @date August 2025
 */

#include "esp_debub.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_err.h"

/**
 * @brief Firmware shutdown handler.
 * * This function is registered to be called before the device reboots.
 * It provides a snapshot of the running tasks and a shutdown message,
 * which is useful for debugging and firmware stability analysis.
 */
void FirmwareShutdownHandler(void)
{
    printf("............ In the shutdown handler ...................\n");
    static char buf[1024];
    TaskHandle_t currentTaskHandle = NULL;
    currentTaskHandle = xTaskGetCurrentTaskHandle();
    printf(">>> CurrentTaskHandle: %s <<<\n", pcTaskGetName(currentTaskHandle));
    vTaskList(buf);
    printf(">>>>>>>>>>>>>> Vtasklist Info <<<<<<<<<<<<<\n");
    printf("  Name        State   Priority  Stack   Num\n");
    printf("_____________________________________________\n");
    printf("%s\n", buf);
    printf("******************* Shutting down **************************\n");
}

/**
 * @brief Logs the reset reason of the ESP32 and registers a shutdown handler.
 * * This provides critical information for debugging unexpected resets,
 * such as a crash or a watchdog timer event.
 */
void ResetReason(void)
{
    esp_reset_reason_t resetReason;
    const char *swResetReasons[] = {"ESP_RST_UNKNOWN",
                                    "ESP_RST_POWERON",
                                    "ESP_RST_EXT",
                                    "ESP_RST_SW",
                                    "ESP_RST_PANIC",
                                    "ESP_RST_INT_WDT",
                                    "ESP_RST_TASK_WDT",
                                    "ESP_RST_WDT",
                                    "ESP_RST_DEEPSLEEP",
                                    "ESP_RST_BROWNOUT",
                                    "ESP_RST_SDIO"};

    shutdown_handler_t handler = FirmwareShutdownHandler;
    esp_err_t ret = esp_register_shutdown_handler(handler);
    printf("Shutdown Handler result : %s\n", esp_err_to_name(ret));
    resetReason = esp_reset_reason();
    printf("Reset Reason: %s\n", swResetReasons[resetReason]);
    printf("Software Start\n");
}