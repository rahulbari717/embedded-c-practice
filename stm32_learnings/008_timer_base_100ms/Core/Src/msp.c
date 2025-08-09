/*
 * msp.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */

/**
  * @brief  Initialize the MSP.
  * @retval None
  */

#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
	//  NOTE : The HAL_MspInit could be implemented in the user file

	// 1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	// 2. Enable the required system exception of arm cortex mx processor
	SCB ->SHCSR |= 0x7 << 16; // usg fault, memory fault, and bus fault, system exception.
	// 3. configure the priority fro the system exception.
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer){
	// 1. enable the clock access to the timer6 peripheral
	__HAL_RCC_TIM6_CLK_ENABLE();

	// 2. enable the IRQ of TIM6
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	// 3. configure the priority of the IRQ
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);
}
