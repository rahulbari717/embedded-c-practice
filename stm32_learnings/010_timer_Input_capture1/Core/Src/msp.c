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

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim2ch1_gpio;
	// 1. Enable the clock for the timer2 peripheral
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2. configure the GPIO to behave as timer2 channel 1
	tim2ch1_gpio.Pin = GPIO_PIN_0;
	tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim2ch1_gpio.Alternate = GPIO_AF1_TIM2;

	HAL_GPIO_Init(GPIOA, &tim2ch1_gpio);

	// 3. Enable the nvic setting for the timer2 global interrupt
	HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	// here we are going to do low level inits of uart2
	GPIO_InitTypeDef gpio_uart;
	// 1. enable the clock for USART2
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// 2. Do the pin muxing configurations
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;				// UART2_TX

	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3;							// UART2_RX
	HAL_GPIO_Init(GPIOA, &gpio_uart);
	// 3. Enable the IRQ and set up the priority (NVIC)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}
