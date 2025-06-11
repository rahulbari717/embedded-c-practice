/*
 * 003_button_interrupt.c
 *
 *  Created on: Jun 11, 2025
 *      Author: Rahul B.
 */
#include <string.h>
#include "stm32f446xx.h"

#define LOW 						(0)
#define BTN_PRESSED		LOW

void delay(void)
{
	for (uint32_t i=0; i<500000/2; i++);
}
int main()
{
    GPIO_Handle_t Gpio_Led, Gpio_Button;
    memset(&Gpio_Led,0,sizeof(Gpio_Led));
    memset(&Gpio_Button,0,sizeof(Gpio_Button));

    // LED Configurations
    Gpio_Led.pGPIOx = GPIOC;
    Gpio_Led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    Gpio_Led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Gpio_Led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    Gpio_Led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    Gpio_Led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&Gpio_Led);

    // Button Configurations
    Gpio_Button.pGPIOx = GPIOC;
    Gpio_Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    Gpio_Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;  // rising edge trigger
    Gpio_Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    Gpio_Button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;   // Enable pull-up resistor

    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&Gpio_Button);

	// IRQ configurations
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI5);

	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	while(1);

    return 0;
}

void EXTI15_10_IRQHandler(void)
{
    // Clear the pending interrupt flag first
	delay();
    GPIO_IRQHandling(GPIO_PIN_NO_1);
    GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_NO_0);

}
