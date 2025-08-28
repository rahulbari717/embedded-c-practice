#include "esp_debub.h"

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