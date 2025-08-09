/*
 * main.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Rahul B.
 */
#include "main.h"

TIM_HandleTypeDef htimer6;

int main(void){

	HAL_Init();
	GPIO_Init();
	// SystemClock_Config(SYSCLOCK_FREQ_120MHZ);
	Timer6_Init();

	// Lets start the timer
	HAL_TIM_Base_Start(&htimer6);
	while(1){
		while(! (TIM6->SR & TIM_SR_UIF)){
			TIM6->SR = 0; // Clear update flag
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Toggle LED
		}
	}

	return 0;
}

void GPIO_Init(void){

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ledgpio);
}

void Timer6_Init(void){
	/*

	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 24;
	htimer6.Init.Period = 6400-1;

	 *
	 * */
	htimer6.Init.CounterMode = TIM_COUNTERMODE_UP;
	    htimer6.Init.Period = 9999;  // Set auto-reload value
	    htimer6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

	// htimer6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	// htimer6.Init.CounterMode = TIM_COUNTERMODE_UP;
	if(HAL_TIM_Base_Init(&htimer6) != HAL_OK){
		Error_handler();
	}
}

void Error_handler(void){
	while(1);
}

void SystemClock_Config(uint8_t clock_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	uint32_t FLatency = 0;

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

	switch(clock_freq)
	{
		case SYSCLOCK_FREQ_50MHZ: 
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

			FLatency = FLASH_ACR_LATENCY_1WS;
			break;
		}
		case SYSCLOCK_FREQ_84MHZ:
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
			FLatency = FLASH_ACR_LATENCY_2WS;
			break;
		}
		case SYSCLOCK_FREQ_120MHZ:
		{
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;


			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider = RCC_HCLK_DIV2;
			FLatency = FLASH_ACR_LATENCY_3WS;
			break;
		}
		default:
			return;
	}

	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK){
		Error_handler();
	}
	if(HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK){
		Error_handler();
	}
	if(HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000) != HAL_OK){
		Error_handler();
	}
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}
