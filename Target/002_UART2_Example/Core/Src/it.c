/*
 * it.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
