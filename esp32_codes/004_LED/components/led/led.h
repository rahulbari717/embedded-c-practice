#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

// LED GPIO pin
#define LED_PIN GPIO_NUM_2

// Function declarations
void led_init(void);
void led_on(void);
void led_off(void);
void led_blink_task(void *pvParameters);

#endif // LED_H
