#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "dht11.h"

#define DHT_PIN 32
static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "📡 Starting DHT11 Task on GPIO%d", DHT_PIN);

    while (true) {
        int hum = 0, temp = 0;
        ESP_LOGI(TAG, "⏱️ Time: %lld µs", esp_timer_get_time());

        esp_err_t res = dht11_read(DHT_PIN, &hum, &temp);

        if (res == ESP_OK) {
            ESP_LOGI(TAG, "✅ Temp: %d°C | Humidity: %d%%", temp, hum);
        } else {
            ESP_LOGE(TAG, "❌ DHT11 read failed: %s", esp_err_to_name(res));
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
