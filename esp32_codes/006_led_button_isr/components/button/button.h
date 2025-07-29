#ifndef BUTTON_H
#define BUTTON_H

#include "driver/gpio.h"

#define BUTTON1_PIN GPIO_NUM_32

void button1_isr_init(void);
void button1_isr_monitor_task(void *pvParameters);

#endif // BUTTON_H
