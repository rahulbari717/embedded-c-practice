/*
 * stm32f446xx_gpio_driver.c
 *
 *  Created on: Mar 31, 2025
 *      Author: Rahul B.
 */

#include "stm32f446xx_gpio_driver.h"

/*
 * Init and De-init
*/

/*************************************************************************
 * 
 * @fn      - GPIO_Init
 * @brief   - Initializes the specified GPIO pin with the given configuration settings
 * 
 * @param[in]  - pGPIOHandle: Pointer to the GPIO handle structure
 * 
 * @return    - None
 * 
 * @note      - None 
 * 
 *************************************************************************/

/*
 * Init and De-init
*/
/************************************************************************
 * 
 * @fn      - GPIO_Init
 * @brief   - This function initializes the GPIO pin based on the given configuration
 * 
 * @param[in]  - pGPIOHandle: Pointer to GPIO handle structure containing pin configuration
 * 
 * @return    - None
 * 
 * @note      - None 
 * 
 ************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;      // temp. register value

    // 1. configure the mode of the GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)   
    {
        // non interrupt mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));     // clearing 
        pGPIOHandle->pGPIOx->MODER |= temp;     // setting
        

    } 
    else
    {
        // to do later 
    } 
    // 2. configure the speed of the GPIO pin
    temp = 0;

    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));     // clearing
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    // 3. configure the pupd of the GPIO pin
    temp = 0;

    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));     // clearing
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    // 4. configure the otype of the GPIO pin
    temp = 0;

    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);     // clearing
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    // 5. configure the alternate function mode of the GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        // configure the alternate function mode of the GPIO pin

        uint8_t temp1, temp2; 

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));

    }


}
/*************************************************************************
 * 
 * @fn      - GPIO_DeInit
 * @brief   - Resets the specified GPIO port to its default state
 * 
 * @param[in]  - pGPIOx: Base address of the GPIO port
 * 
 * @return    - None
 * 
 * @note      - None 
 * 
 *************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }

}

/*
 * Peripheral Clock Setup
*/

/*************************************************************************
 * 
 * @fn      - GPIO_PeriClockControl
 * @brief   - This function enables or disables the peripheral clock for the given GPIO port
 * 
 * @param[in]  - pGPIOx: Base address of the GPIO port
 * @param[in]  - EnorDi: Enable (1) or Disable (0) macros
 * 
 * @return    - None
 * 
 * @note      - None 
 * 
 *************************************************************************/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
    }
    else 
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
    }    

}

/*
 * Data read and write
*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x01);
    return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint16_t value;
    value = (uint16_t) pGPIOx->IDR;
    return value;

}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == SET)
    {
        pGPIOx->ODR |= (1 << PinNumber);   // write 1 to the output data register at the bit filed of the pin
    }
    else
    {
        pGPIOx->ODR &= ~(1 << PinNumber);   // write 0 
    }
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber);
}

/*
 * IRQ Configuration and ISR handling
*/
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

}
void GPIO_IRQHandling(uint8_t PinNumber)
{

}
