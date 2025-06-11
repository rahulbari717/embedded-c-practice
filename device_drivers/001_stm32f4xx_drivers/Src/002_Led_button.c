/*
 * 002_Led_button.c
 *
 *  Created on: Jun 10, 2025
 *      Author: Rahul B.
 */

#include "stm32f446xx.h"
#define LOW 						(0)
#define BTN_PRESSED		LOW

void delay(void){

	for (uint32_t i = 0; i<500000 / 2; i++);
}

int main()
{
	GPIO_Handle_t Gpio_Led, Gpio_Button;
	// this is led Configurations
	Gpio_Led.pGPIOx = GPIOA;
	Gpio_Led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	Gpio_Led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpio_Led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpio_Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpio_Led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&Gpio_Led);

	// this is button configurations
	Gpio_Button.pGPIOx = GPIOC;
	Gpio_Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	Gpio_Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Gpio_Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	// Gpio_Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpio_Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOC, ENABLE);
	GPIO_Init(&Gpio_Button);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) == BTN_PRESSED){
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
		}

	}

	return 0;
}
