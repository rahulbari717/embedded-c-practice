#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_log.h"

#define MAX_APs 20
static const char *TAG = "WIFI_SCANNER";

char *getAuthModeName(wifi_auth_mode_t wifi_auth_mode)
{
    switch (wifi_auth_mode)
    {
    case WIFI_AUTH_OPEN:
        return "WIFI_AUTH_OPEN";
    case WIFI_AUTH_WEP:
        return "WIFI_AUTH_WEP";
    case WIFI_AUTH_WPA_PSK:
        return "WIFI_AUTH_WPA_PSK";
    case WIFI_AUTH_WPA2_PSK:
        return "WIFI_AUTH_WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:
        return "WIFI_AUTH_WPA_WPA2_PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE:
        return "WIFI_AUTH_WPA2_ENTERPRISE";
    case WIFI_AUTH_WPA3_PSK:
        return "WIFI_AUTH_WPA3_PSK";
    case WIFI_AUTH_WPA2_WPA3_PSK:
        return "WIFI_AUTH_WPA2_WPA3_PSK";
    case WIFI_AUTH_WAPI_PSK:
        return "WIFI_AUTH_WAPI_PSK";
    case WIFI_AUTH_OWE:
        return "WIFI_AUTH_OWE";
    case WIFI_AUTH_MAX:
        return "WIFI_AUTH_MAX";
    case WIFI_AUTH_WPA3_ENT_192:
    return "WIFI_AUTH_WPA3_ENT_192";
    case WIFI_AUTH_WPA3_EXT_PSK:
        return "WIFI_AUTH_WPA3_EXT_PSK";
    case WIFI_AUTH_WPA3_EXT_PSK_MIXED_MODE:
        return "WIFI_AUTH_WPA3_EXT_PSK_MIXED_MODE";
    case WIFI_AUTH_DPP:
        return "WIFI_AUTH_DPP";
    case WIFI_AUTH_WPA3_ENTERPRISE:
        return "WIFI_AUTH_WPA3_ENTERPRISE";
    case WIFI_AUTH_WPA2_WPA3_ENTERPRISE:
        return "WIFI_AUTH_WPA2_WPA3_ENTERPRISE";
    default:
    return "UNKNOWN";
    }    
}

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

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(TAG, "Initializing WiFi...");
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));
    ESP_LOGI(TAG, "WiFi init done.");

    ESP_LOGI(TAG, "Setting WiFi mode to STA...");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_LOGI(TAG, "WiFi mode set to STA.");

    ESP_LOGI(TAG, "Starting WiFi...");
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "WiFi started.");

    ESP_LOGI(TAG, "Starting WiFi scan...");
    wifi_scan_config_t wifi_scan_config = {
        .show_hidden = true,
        .channel = 0   // scan all channels
    };
    ESP_ERROR_CHECK(esp_wifi_scan_start(&wifi_scan_config, true));
    ESP_LOGI(TAG, "WiFi scan complete.");

    wifi_ap_record_t wifi_records[MAX_APs];
    uint16_t max_record = MAX_APs;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&max_record, wifi_records));
    ESP_LOGI(TAG, "Retrieved %d scan results.", max_record);

    printf("Found %d access points:\n", max_record);
    printf("\n");
    printf("               SSID              | Channel | RSSI |   Auth Mode \n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < max_record; i++)
    {
        ESP_LOGI(TAG, "AP[%d]: SSID=%s, CH=%d, RSSI=%d, AUTH=%s",
                 i, (char *)wifi_records[i].ssid,
                 wifi_records[i].primary,
                 wifi_records[i].rssi,
                 getAuthModeName(wifi_records[i].authmode));

        printf("%32s | %7d | %4d | %12s\n",
               (char *)wifi_records[i].ssid,
               wifi_records[i].primary,
               wifi_records[i].rssi,
               getAuthModeName(wifi_records[i].authmode));
    }
    printf("----------------------------------------------------------------\n");

    ESP_LOGI(TAG, "WiFi scan finished.");
}