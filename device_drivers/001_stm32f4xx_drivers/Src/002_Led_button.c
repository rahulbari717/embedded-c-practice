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

// Function to handle LED control based on button and timer
void led_control_task(void)
{
    static uint32_t counter = 0;
    static uint32_t ten_second_count = 100000; // Adjust this value based on your delay function timing

    if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_6) == BTN_PRESSED){
        delay();
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_SET);  // LED ON when button pressed
    }
    else {
        GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET); // LED OFF when button not pressed
    }

    // Toggle LED every 10 seconds regardless of button state
    counter++;
    if(counter >= ten_second_count) {
        // GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
    	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_5, GPIO_PIN_RESET); // LED OFF
        counter = 0; // Reset counter
    }
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

	// this is button configurations
	Gpio_Button.pGPIOx = GPIOA;
	Gpio_Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	Gpio_Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	Gpio_Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	// Gpio_Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpio_Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);
	GPIO_Init(&Gpio_Button);

	GPIO_Init(&Gpio_Led);

	while(1)
	{
		led_control_task();
	}

	return 0;
}
