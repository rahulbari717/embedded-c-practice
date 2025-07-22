#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"

// Button GPIO pins
#define BUTTON1_PIN GPIO_NUM_32
#define BUTTON2_PIN GPIO_NUM_33

// Function declarations
void button_init(void);
int button1_is_pressed(void);
int button2_is_pressed(void);
void button_monitor_task(void *pvParameters);

#endif // BUTTON_H
