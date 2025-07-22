#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TASK_STACK_SIZE    4096

static const char *TAG = "MAIN";

/* ───────────── TASK DEFINITIONS ───────────── */

void task1_blink_led(void *arg) {                                   // task 1 led task blinking
    while (1) {
        ESP_LOGI(TAG, "[Task 1] Blinking LED...");
        vTaskDelay(pdMS_TO_TICKS(1000));                            // 1 sec delay 
    }
}

void task2_read_sensor(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 2] Reading sensor value...");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void task3_write_log(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 3] Writing system logs...");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void task4_check_battery(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 4] Battery level OK.");
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}

void task5_send_data(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 5] Sending data to server...");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void task6_button_monitor(void *arg) {
    while (1) {
        ESP_LOGD(TAG, "[Task 6] Monitoring button state...");
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}

void task7_buzzer_beep(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 7] Activating buzzer...");
        vTaskDelay(pdMS_TO_TICKS(7000));
    }
}

void task8_process_command(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 8] Parsing command input...");
        vTaskDelay(pdMS_TO_TICKS(8000));
    }
}

void task9_monitor_temp(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 9] Monitoring temperature...");
        vTaskDelay(pdMS_TO_TICKS(9000));
    }
}

void task10_heartbeat(void *arg) {
    while (1) {
        ESP_LOGI(TAG, "[Task 10] System heartbeat OK.");
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_LOGW(TAG, "Free heap: %u", esp_get_free_heap_size());

    }
}

/* ───────────── CREATE TASK WRAPPER ───────────── */

void create_task(TaskFunction_t func, const char *name, UBaseType_t prio) {
    BaseType_t res = xTaskCreate(func, name, TASK_STACK_SIZE, NULL, prio, NULL);
    if (res != pdPASS) {
        ESP_LOGE(TAG, "Failed to create task: %s", name);
    } else {
        ESP_LOGI(TAG, "Task created: %s", name);
    }
}

/* ───────────── ENTRY POINT ───────────── */

void app_main(void) {
    ESP_LOGI(TAG, "Starting multitasking system");

    create_task(task1_blink_led,     "task1_led", 2);
    create_task(task2_read_sensor,   "task2_sensor", 4);
    create_task(task3_write_log,     "task3_log", 6);
    create_task(task4_check_battery, "task4_battery", 8);
    create_task(task5_send_data,     "task5_data", 10);
    create_task(task6_button_monitor,"task6_button", 12);
    create_task(task7_buzzer_beep,   "task7_buzzer", 14);
    create_task(task8_process_command,"task8_cmd", 16);
    create_task(task9_monitor_temp,  "task9_temp", 18);
    create_task(task10_heartbeat,    "task10_beat", 20);
}

