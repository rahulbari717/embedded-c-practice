#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "wifi_connect.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "main";

void app_main(void)
{
    esp_err_t ret;

    ESP_LOGI(TAG, "Initializing NVS...");
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS no free pages or new version found, erasing...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "NVS initialized.");

    wifi_connect_init(); 
    ESP_LOGI(TAG, "Initialized wifi...");

    while(1){
        wifi_connect_ap("esp32AP", "password"); 
        vTaskDelay(pdMS_TO_TICKS(10000));
        wifi_disconnect();

        wifi_connect_sta("Rahul", "rahul8459", 10000);
        vTaskDelay(pdMS_TO_TICKS(10000));
        wifi_disconnect();
    }

   
   
    // wifi_connect_ap("esp32AP", "password"); 

}