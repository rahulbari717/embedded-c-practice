/*
 * it.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */
#include "main.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
