/*
 * main.c
 *
 *  Created on: Jun 11, 2025
 *      Author: Rahul B
 */
#include "stm32f446xx.h"

int main(void) {return 0; }

void EXTI0_IRQHandler (void)
{
	// handle the interrupt
	GPIO_IRQHandling(0);
}
