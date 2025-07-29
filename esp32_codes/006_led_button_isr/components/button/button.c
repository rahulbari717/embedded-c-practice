#include "button.h"
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"

#define DEBOUNCE_TIME_MS 100

static const char* TAG = "BUTTON_ISR";

// Shared across ISR and task
static portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
static volatile bool button_event_flag = false;
static uint64_t last_isr_time = 0;

// ISR for rising edge (button release)
static void IRAM_ATTR button1_isr_handler(void* arg)
{
    uint64_t now = esp_timer_get_time(); // µs
    if ((now - last_isr_time) > (DEBOUNCE_TIME_MS * 1000)) {
        portENTER_CRITICAL_ISR(&mux);
        button_event_flag = true;
        portEXIT_CRITICAL_ISR(&mux);
        last_isr_time = now;
        ESP_EARLY_LOGI(TAG, "ISR fired: Rising edge");
    }
}

// Configure GPIO32 for rising edge interrupt
void button1_isr_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON1_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE,
    };
    gpio_config(&io_conf);

    esp_err_t err = gpio_install_isr_service(0);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "ISR service install failed: %s", esp_err_to_name(err));
    }

    gpio_isr_handler_add(BUTTON1_PIN, button1_isr_handler, NULL);
    ESP_LOGI(TAG, "Button1 ISR initialized on GPIO %d", BUTTON1_PIN);
}

// Task to act on button release
void button1_isr_monitor_task(void *pvParameters)
{
    ESP_LOGI(TAG, "ISR monitor task started");

    while (1) {
        bool event = false;

        // Safely copy the flag and reset
        portENTER_CRITICAL(&mux);
        event = button_event_flag;
        button_event_flag = false;
        portEXIT_CRITICAL(&mux);

        if (event) {
            if (gpio_get_level(BUTTON1_PIN) == 1) {  // Released
                ESP_LOGI(TAG, "Button released → toggling LED");
                led_on();
                vTaskDelay(pdMS_TO_TICKS(300));
                led_off();
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
