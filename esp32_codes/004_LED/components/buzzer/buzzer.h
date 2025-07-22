#ifndef BUZZER_H
#define BUZZER_H

#include "driver/gpio.h"

// Buzzer GPIO pin
#define BUZZER_PIN GPIO_NUM_4

// Function declarations
void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);
void buzzer_beep_task(void *pvParameters);

#endif // BUZZER_H
