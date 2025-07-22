#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);        // Keep system at INFO level
    // Small delay to ensure settings take effect
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ESP_LOGI("LOG", "This is an info message!");
    ESP_LOGD("LOG", "Debuging!");
    ESP_LOGW("LOG", "Warning!");
    ESP_LOGE("LOG", "Error!");
    ESP_LOGI("LOG", "Info!");
    printf("Hello world!\n");
}
