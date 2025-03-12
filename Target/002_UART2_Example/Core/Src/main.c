/*
 * main.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */
#include <string.h>

#include "stm32f4xx_hal.h"
#include "main.h"

UART_HandleTypeDef huart2;

char * user_data = "The application is running\r\n";

void SystemClockConfig(void){

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

int main(void){

	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	// uint16_t len_of_data = strlen(user_data);
//	if (HAL_UART_Transmit(&huart2, (uint8_t *) user_data, len_of_data, HAL_MAX_DELAY) != HAL_OK) {
//		Error_handler();
//	}

	uint8_t rxvd_data;
	uint8_t data_buffer[100];
	uint32_t count = 0;
	while (1) {
		HAL_UART_Receive(&huart2, &rxvd_data, 1, HAL_MAX_DELAY);
		if(rxvd_data == '\r'){
			break;
		} else {
			data_buffer[count++] = rxvd_data;
		}
	}
	data_buffer[count++] = '\r';
	HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);

	while(1);
	return 0;
}

