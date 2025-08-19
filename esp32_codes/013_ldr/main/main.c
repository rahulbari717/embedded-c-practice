#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"


static const char *TAG = "ADC_EXAMPLE";

void app_main(void)
{
    // Create ADC unit handle (use ADC unit 2, because GPIO14 = ADC2_CH6)
    adc_oneshot_unit_handle_t adc2_handle;
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_2,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc2_handle));

    // Configure channel (GPIO14 -> ADC2_CH6)
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,  // usually 12 bits
        .atten = ADC_ATTEN_DB_11,          // up to 3.3V input
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc2_handle, ADC_CHANNEL_6, &config));

    while (1) {
        int adc_raw = 0;
        esp_err_t ret = adc_oneshot_read(adc2_handle, ADC_CHANNEL_6, &adc_raw);
        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "ADC Raw: %d", adc_raw);
        } else {
            ESP_LOGE(TAG, "ADC read failed: %s", esp_err_to_name(ret));
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1s delay
    }
}
