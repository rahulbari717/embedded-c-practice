#include "dht11.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"

#define TAG "DHT11_RAW"

static int wait_level(gpio_num_t pin, int level, uint32_t timeout_us) {
    uint32_t start = esp_timer_get_time();
    while (gpio_get_level(pin) == level) {
        if ((esp_timer_get_time() - start) > timeout_us) return -1;
    }
    return esp_timer_get_time() - start;
}

esp_err_t dht11_read(gpio_num_t pin, int *humidity, int *temperature) {
    int data[5] = {0};

    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin, 0);
    vTaskDelay(pdMS_TO_TICKS(20));  // >18ms LOW
    gpio_set_level(pin, 1);
    esp_rom_delay_us(40);
    gpio_set_direction(pin, GPIO_MODE_INPUT);

    if (wait_level(pin, 1, 80) < 0 || wait_level(pin, 0, 80) < 0) {
        ESP_LOGE(TAG, "No response from sensor");
        return ESP_FAIL;
    }

    for (int i = 0; i < 40; ++i) {
        if (wait_level(pin, 1, 50) < 0) return ESP_FAIL;
        int len = wait_level(pin, 0, 70);
        if (len < 0) return ESP_FAIL;

        data[i / 8] <<= 1;
        if (len > 40) data[i / 8] |= 1;
    }

    uint8_t sum = data[0] + data[1] + data[2] + data[3];
    if (data[4] != (sum & 0xFF)) {
        ESP_LOGE(TAG, "Checksum mismatch");
        return ESP_ERR_INVALID_CRC;
    }

    *humidity = data[0];
    *temperature = data[2];

    return ESP_OK;
}
