#include "main.h"

/**
 * @brief  System Tick Handler
 * @note   This function handles system tick timer interrupt
 */
void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

/**
 * @brief  Timer 2 Interrupt Handler
 * @note   This function handles Timer 2 global interrupt
 */
void TIM2_IRQHandler(void){
	HAL_TIM_IRQHandler(&htimer2);
}
