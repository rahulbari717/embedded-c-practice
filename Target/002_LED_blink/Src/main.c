
#include <stdint.h>
#include <stdio.h>
#include "main.h"

/**
 * @brief Simple delay function
 * @param time: Number of iterations
 */
void delay(volatile uint32_t time)
{
    while (time--);
}

int main(void)
{
    // Pointer initialization for register access using structs
    RCC_AHB1ENR_t volatile *const pClkCtrlReg = ADDR_REG_AHB1ENR;
    GPIOx_MODE_t volatile *const pPortAModeReg = ADDR_REG_GPIOA_MODE;
    GPIOx_ODR_t volatile *const pPortAOutReg = ADDR_REG_GPIOA_OA;

    // 1. Enable GPIOA clock (bit 0 of RCC_AHB1ENR)
    // Fixed: Use either direct register manipulation OR struct approach, not both
    pClkCtrlReg->gpioa_en = CLOCK_ENABLE;
    // Alternative approach: RCC_AHB1ENR |= (1 << 0);

    // 2. Configure PA5 as Output
    // Fixed: Using struct access correctly
    pPortAModeReg->pin_5 = MODE_CONF_OUTPUT; // Set as output (01)
    // Alternative approach: GPIOA_MODER &= ~(3 << (LED_PIN * 2)); GPIOA_MODER |= (1 << (LED_PIN * 2));

    while (1)
    {
        // Turn LED ON
        pPortAOutReg->pin_5 = PIN_STATE_HIGH;
        printf("LED ON\n");
        delay(DELAY_TIME);

        // Turn LED OFF - fixed: was setting to 1 again
        pPortAOutReg->pin_5 = PIN_STATE_LOW;
        printf("LED OFF\n");
        delay(DELAY_TIME);
    }
}
