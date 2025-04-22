#include <stdio.h>
#include "esp_log.h"

const char *tag = "main"; 

void app_main(void)
{
    printf("Hello world!\n");
    // esp_log_level_set(tag, ESP_LOG_DEBUG);
    ESP_LOGI(tag, "This is an Information..."); 
    ESP_LOGW(tag, "This is an Warning ...");
    ESP_LOGD(tag, "This is an Debug...");
    ESP_LOGE(tag, "This is an Error...");
    ESP_LOGV(tag, "This is an Verbose...");
}
