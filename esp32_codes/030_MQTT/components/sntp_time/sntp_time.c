#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <time.h>
#include "esp_sntp.h"

#define TAG "NTP TIME"

SemaphoreHandle_t got_time_semaphore;

void print_time()
{
    time_t now = 0;
    time(&now);
    struct tm *time_info = localtime(&now);

    char time_buffer[50];
    strftime(time_buffer, sizeof(time_buffer), "%c", time_info);
    ESP_LOGI(TAG, "************ %s ***********", time_buffer);
}

void on_got_time(struct timeval *tv)
{
    printf("on got callback %lld\n", tv->tv_sec);
    print_time();
    xSemaphoreGive(got_time_semaphore);
}

void sntp(void) {
    got_time_semaphore = xSemaphoreCreateBinary();

    // Set Indian Standard Time (UTC+5:30)
    setenv("TZ", "IST-5:30", 1);
    tzset();

    ESP_LOGI(TAG, "Before NTP sync (local time may be wrong)");
    print_time();

    // Configure SNTP
    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_set_time_sync_notification_cb(on_got_time);
    esp_sntp_init();

    // Wait until we actually get time from server
    if (xSemaphoreTake(got_time_semaphore, pdMS_TO_TICKS(20000)) == pdTRUE) {
        ESP_LOGI(TAG, "SNTP sync successful!");
    } else {
        ESP_LOGE(TAG, "SNTP sync timed out!");
    }

    // Print a few samples
    for (int i = 0; i < 5; i++) {
        print_time();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}