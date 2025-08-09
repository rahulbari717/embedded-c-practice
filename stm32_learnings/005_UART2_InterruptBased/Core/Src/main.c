/*
 * main.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */
#include "main.h"
TIM_HandleTypeDef htimer6;
UART_HandleTypeDef huart2;
extern uint8_t some_data[];

int main(void){

	HAL_Init();

	GPIO_Init();

	SystemClockConfig_HSE(uint8_t clock_freq);

	UART2_Init();

	TIMER6_Init();

	TIM6-> SR = 0;

	// Lets start timer in interrupt mode

	HAL_TIM_Base_Start_IT(&htimer);

	while(1);

	return 0;
}




void SystemClockConfig(uint8_t clock_freq){
	RCC_OscInitTypeDef Osc_Init;
	RCC_ClkInitTypeDef Clock_Init;

	uint8_t flash_latency = 0;
	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	Osc_Init.HSEState = RCC_HSE_ON;
	Osc_Init.PLL.PLLState = RCC_PLL_ON;
	Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

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

}




void HAL_UART_RxCPltCallback(UART_HandleTypeDef *huart){
	if(received_data == '\r'){
		reception_complete = TRUE;
		HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);
	} else{
		data_buffer[count++] = received_data;
	}


}

void Error_handler(void){
	while(1);
}


void UART2_Init(){
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	if(HAL_UART_Init(&huart2) != HAL_OK){
		// there is problem
		Error_handler();

	}
}



