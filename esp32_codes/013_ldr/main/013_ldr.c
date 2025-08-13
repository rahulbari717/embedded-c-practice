#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

void app_main(void)
{
    // Configure ADC
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);  // GPIO32 = ADC1_CHANNEL_4
    
    while(1) {
        // Read LDR value
        int ldr_value = adc1_get_raw(ADC1_CHANNEL_4);
        
        // Print to terminal
        printf("LDR Reading: %d\n", ldr_value);
        
        // Wait 1 second
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
