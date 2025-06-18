/*
 * stm32f4xx_rcc_driver.c
 *
 * @author Rahul B.
 * @date Jun 9, 2025
 * @version 1.0
 *
 */

#include "stm32f4xx_rcc_driver.h"

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t AHB1_PreScaler[4] = {2,4,8,16};

/**
 * @brief  Get APB1 clock frequency value
 * @return APB1 clock frequency in Hz
 * @note   This function calculates the actual PCLK1 frequency based on
 *         system clock source and various prescalers
 */
uint32_t RCC_GetPCLK1Val(void)
{
    uint32_t pclk1;
    uint32_t systemClk;
    uint8_t clkSource, temp, ahbPrescaler, apb1Prescaler;

    // Get clock source
    clkSource = ((RCC->CFGR >> 2) & 0x3);

    // Calculate system clock based on source
    if (clkSource == 0) {
        systemClk = 16000000;  // HSI is selected as system clock
    } else if (clkSource == 1) {
        systemClk = 8000000;   // HSE is selected as system clock
    } else if (clkSource == 2) {
        // PLL is selected as system clock
        // Add PLL calculation here if needed
        systemClk = 16000000;  // Default to HSI frequency
    }

    // Get AHB prescaler
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8) {
        ahbPrescaler = 1;
    } else {
        ahbPrescaler = AHB_PreScaler[temp - 8];
    }

    // Get APB1 prescaler
    temp = ((RCC->CFGR >> 10) & 0x7);
    if (temp < 4) {
        apb1Prescaler = 1;
    } else {
        apb1Prescaler = AHB1_PreScaler[temp - 4];
    }

    // Calculate PCLK1 frequency
    pclk1 = (systemClk / ahbPrescaler) / apb1Prescaler;

    return pclk1;
}

/**
 * @brief  Get APB2 clock frequency value
 * @return APB2 clock frequency in Hz
 * @note   This function calculates the actual PCLK2 frequency based on
 *         system clock source and various prescalers
 */
uint32_t RCC_GetPCLK2Val(void)
{
    uint32_t pclk2;
    uint32_t systemClk;
    uint8_t clkSource, temp, ahbPrescaler, apb2Prescaler;

    // Get clock source
    clkSource = ((RCC->CFGR >> 2) & 0x3);

    // Calculate system clock based on source
    if (clkSource == 0) {
        systemClk = 16000000;  // HSI is selected as system clock
    } else if (clkSource == 1) {
        systemClk = 8000000;   // HSE is selected as system clock
    } else if (clkSource == 2) {
        // PLL is selected as system clock
        // Add PLL calculation here if needed
        systemClk = 16000000;  // Default to HSI frequency
    }

    // Get AHB prescaler
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8) {
        ahbPrescaler = 1;
    } else {
        ahbPrescaler = AHB_PreScaler[temp - 8];
    }

    // Get APB2 prescaler
    temp = ((RCC->CFGR >> 13) & 0x7);
    if (temp < 4) {
        apb2Prescaler = 1;
    } else {
        apb2Prescaler = AHB1_PreScaler[temp - 4];
    }

    // Calculate PCLK2 frequency
    pclk2 = (systemClk / ahbPrescaler) / apb2Prescaler;

    return pclk2;
}
