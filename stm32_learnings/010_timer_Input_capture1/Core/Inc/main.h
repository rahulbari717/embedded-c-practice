/*
 * main.h
 *
 *  Created on: Mar 17, 2025
 *      Author: lenovo
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "stm32f4xx_hal.h"

#define TRUE  1
#define FALSE 0

#define SYSCLOCK_FREQ_50MHZ 50
#define SYSCLOCK_FREQ_84MHZ 84
#define SYSCLOCK_FREQ_120MHZ 120

void Error_handler(void);
void SystemClock_Config(uint8_t clock_freq);

void GPIO_Init(void);
void TIMER2_Init(void);
void LSE_Configuration(void);
void UART2_Init(void);
#endif /* INC_MAIN_H_ */


