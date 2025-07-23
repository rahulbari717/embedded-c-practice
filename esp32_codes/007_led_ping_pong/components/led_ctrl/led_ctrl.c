#include "led_ctrl.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "LED_CTRL";

// Task handles to communicate between them
static TaskHandle_t red_task_hdl = NULL;
static TaskHandle_t white_task_hdl = NULL;

// Pingpong mode toggle; needs 'volatile' as it's modified in ISR
static volatile bool pingpong_active = false;

static void IRAM_ATTR button_isr_handler(void *arg);

// button init
void button_init(void){
    // Configure Button GPIO as input with falling edge interrupt
    gpio_config_t btn_conf = {
        .pin_bit_mask = BIT64(BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&btn_conf);

    // Register ISR
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_GPIO, button_isr_handler, NULL);

    // Initialize button state
    ESP_LOGI(TAG, "Button initialized");
}

// RED LED task
static void red_task(void *arg) {
    gpio_set_direction(RED_LED_GPIO, GPIO_MODE_OUTPUT);
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (!pingpong_active) continue;
        gpio_set_level(RED_LED_GPIO, 1);
        ESP_LOGI(TAG, "RED ON");
        vTaskDelay(pdMS_TO_TICKS(2000));
        gpio_set_level(RED_LED_GPIO, 0);
        ESP_LOGI(TAG, "RED OFF");
        xTaskNotifyGive(white_task_hdl);
    }
}

// WHITE LED task
static void white_task(void *arg) {
    gpio_set_direction(WHITE_LED_GPIO, GPIO_MODE_OUTPUT);
    while (1) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        if (!pingpong_active) continue;
        gpio_set_level(WHITE_LED_GPIO, 1);
        ESP_LOGI(TAG, "WHITE ON");
        vTaskDelay(pdMS_TO_TICKS(2000));
        gpio_set_level(WHITE_LED_GPIO, 0);
        ESP_LOGI(TAG, "WHITE OFF");
        xTaskNotifyGive(red_task_hdl);
    }
}

// ISR: toggles pingpong mode and kickstarts red task
static void IRAM_ATTR button_isr_handler(void *arg) {
    static volatile bool last_state = false;  // ISR-local state
    BaseType_t high_wakeup = pdFALSE;

    // toggle active mode
    pingpong_active = !pingpong_active;
    last_state = pingpong_active;

    if (pingpong_active) {
        vTaskNotifyGiveFromISR(red_task_hdl, &high_wakeup);
    }

    portYIELD_FROM_ISR(high_wakeup);
}

// Setup tasks and GPIOs
void start_pingpong_on_button(void) {
    
    button_init();
    // Create tasks
    xTaskCreatePinnedToCore(red_task, "RED", 2048, NULL, 5, &red_task_hdl, 0);
    xTaskCreatePinnedToCore(white_task, "WHITE", 2048, NULL, 5, &white_task_hdl, 1);

    ESP_LOGI(TAG, "Ping-pong LED system ready. Press GPIO %d", BUTTON_GPIO);
}
