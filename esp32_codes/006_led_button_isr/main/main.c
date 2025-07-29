#include "led.h"
#include "button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BUTTON GPIO_NUM_5

static volatile uint16_t interrupt_count = 0;
static volatile bool button_state = false;

static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    interrupt_count++;
    button_state = true;
}

void app_main(void)
{
    led_init();

    gpio_reset_pin(BUTTON);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(BUTTON, GPIO_INTR_POSEDGE); // Rising edge = button released

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON, gpio_isr_handler, NULL);

    while (1) {
        if (button_state) {
            button_state = false;
            printf("Interrupt count: %d\n", interrupt_count);
            led_on();
            vTaskDelay(pdMS_TO_TICKS(2000));
            led_off();
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    // led_init();
    // led_on();  // should glow bright
    // while (1) {
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    // }

}
