/*
 * 001_Led_toggle.c
 *
 *  Created on: Jun 10, 2025
 *      Author: Rahul B.
 */

#include "stm32f446xx.h"

void delay(void){

	for (uint32_t i = 0; i<500000; i++);
}

int main()
{
	GPIO_Handle_t Gpio_Led;
	Gpio_Led.pGPIOx = GPIOA;
	Gpio_Led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	Gpio_Led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpio_Led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpio_Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpio_Led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&Gpio_Led);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
		delay();
	}

	return 0;
}
