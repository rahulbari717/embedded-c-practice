
#include "main.h"

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

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim2OC_ch_gpio;
	// 1. Enable the clock for TIM2
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2. Configure the GPIO pin to behave like timer2 channel 1, 2, 3, 4
	/* PA0 --> TIM2_CH1
	PA1 --> TIM2_CH2
	PB10 --> TIM2_CH3
	PB2 --> TIM2_CH4 */

	tim2OC_ch_gpio.Pin = GPIO_PIN_5;
	tim2OC_ch_gpio.Mode = GPIO_MODE_AF_PP;
	tim2OC_ch_gpio.Pull = GPIO_NOPULL;
	tim2OC_ch_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	tim2OC_ch_gpio.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &tim2OC_ch_gpio);

	// 3. Configure the NVIC IRQ and its priority
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
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
