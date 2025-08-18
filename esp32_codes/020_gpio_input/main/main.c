#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/dac.h"

void app_main(void)
{
    dac_output_enable(DAC_CHANNEL_1);  // GPIO25

    while (1)
    {
        // 3V to 1V (decreasing)
        for (int val = 232; val >= 78; val -= 5) {
            dac_output_voltage(DAC_CHANNEL_1, val);
            vTaskDelay(pdMS_TO_TICKS(20));  // smooth step delay
        }

        // 1V to 3V (increasing)
        for (int val = 78; val <= 232; val += 5) {
            dac_output_voltage(DAC_CHANNEL_1, val);
            vTaskDelay(pdMS_TO_TICKS(20));  // smooth step delay
        }
    }
}
