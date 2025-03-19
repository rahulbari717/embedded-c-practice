/*
 * it.c
 *
 *  Created on: Mar 19, 2025
 *      Author: Rahul B.
 */

#include "main.h"
extern TIM_HandleTypeDef htimer2;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM2_IRQHandler(void){
	HAL_TIM_IRQHandler(&htimer2);
}