/*
 * main.c
 *
 *  Created on: Mar 11, 2025
 *      Author: Rahul B.
 */
#include <string.h>


#include "main.h"

UART_HandleTypeDef huart2;

char * user_data = "The application is running\r\n";

uint8_t data_buffer[100];
uint8_t received_data;
uint32_t count = 0;
uint8_t reception_complete = FALSE;

void SystemClockConfig(void){

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

int main(void){

	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	// uint16_t len_of_data = strlen(user_data);
//	if (HAL_UART_Transmit(&huart2, (uint8_t *) user_data, len_of_data, HAL_MAX_DELAY) != HAL_OK) {
//		Error_handler();
//	}

	while(reception_complete != TRUE)
		HAL_UART_Receive_IT(&huart2, &received_data, 1);

	while(1);

	return 0;
}

