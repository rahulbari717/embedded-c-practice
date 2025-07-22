#include <stdio.h>
#include "esp_log.h"
#include "led_ctrl.h"

void app_main(void) {
    ESP_LOGI("MAIN", "System Init");
    start_pingpong_on_button();
}

