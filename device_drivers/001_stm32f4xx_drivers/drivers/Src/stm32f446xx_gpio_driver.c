/**
* @file stm32f446xx_gpio_driver.c
* @brief GPIO driver implementation file for STM32F446xx microcontroller
* @details This file contains all the function implementations for GPIO operations
* including initialization, configuration, data read/write, and interrupt handling
* for STM32F446xx microcontroller series.
*
* @author Rahul B.
* @date Jun 9, 2025
* @version 1.0
*
* @note This driver is specifically designed for STM32F446xx series microcontrollers
* @warning Ensure proper clock configuration before using GPIO functions
*/
#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx.h"

/*
 * Peripheral Clock setup
 */

/******************************************************************************
 * @fn                   - GPIO_PeriClockControl
 *
 * @brief                - This function enables or disables the peripheral clock for the given GPIO port.
 *
 * @param[in] pGPIOx     - Base address of the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @param[in] EnorDi     - ENABLE or DISABLE macro (1 to enable, 0 to disable).
 *
 * @return               - None
 *
 * @note                 - None
 *
 *****************************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        // Enable peripheral clock for GPIOA
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN(); // Macro from stm32f446xx.h, equivalent to (RCC->AHB1ENR |= (1 << 0));
        }
        // Enable peripheral clock for GPIOB
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 1));
        }
        // Enable peripheral clock for GPIOC
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 2));
        }
        // Enable peripheral clock for GPIOD
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 3));
        }
        // Enable peripheral clock for GPIOE
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 4));
        }
        // Enable peripheral clock for GPIOF
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 5));
        }
        // Enable peripheral clock for GPIOG
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 6));
        }
        // Enable peripheral clock for GPIOH
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 7));
        }
        // STM32F446RE does not have GPIOI, J, K. Add if your specific F4 variant does.
    }
    else // EnorDi == DISABLE
    {
        // Disable peripheral clock for GPIOA
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI(); // Macro from stm32f446xx.h, equivalent to (RCC->AHB1ENR &= ~(1 << 0));
        }
        // Disable peripheral clock for GPIOB
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 1));
        }
        // Disable peripheral clock for GPIOC
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 2));
        }
        // Disable peripheral clock for GPIOD
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 3));
        }
        // Disable peripheral clock for GPIOE
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 4));
        }
        // Disable peripheral clock for GPIOF
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 5));
        }
        // Disable peripheral clock for GPIOG
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 6));
        }
        // Disable peripheral clock for GPIOH
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 7));
        }
    }
}

/*
 * Init and De-init
 */

/******************************************************************************
 * @fn                   - GPIO_Init
 *
 * @brief                - This function initializes the specified GPIO pin according to the
 *                         configuration provided in the GPIO_Handle_t structure.
 *                         It configures mode, speed, output type, pull-up/pull-down, and alternate function.
 *
 * @param[in] pGPIOHandle - Pointer to a GPIO_Handle_t structure that contains
 *                          the configuration settings for the GPIO pin.
 *
 * @return               - None
 *
 * @note                 - Ensure the peripheral clock for the GPIO port is enabled BEFORE calling this function.
 *                         Refer to the STM32F446xx Reference Manual for GPIO register details.
 *****************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0; // Temporary register to store configuration values

    // Enable the peripheral clock first
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    // 1. Configure the mode of GPIO pin
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        // Clear existing mode bits for this pin
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        // Set new mode value
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER |= temp;
    }
    else
    {
        // Handle interrupt modes (GPIO_MODE_IT_FT, GPIO_MODE_IT_RT, GPIO_MODE_IT_RFT)

        // Configure falling edge trigger
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            // Set FTSR bit for falling edge
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            // Clear RTSR bit to disable rising edge
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        // Configure rising edge trigger
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            // Set RTSR bit for rising edge
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            // Clear FTSR bit to disable falling edge
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        // Configure both rising and falling edge trigger
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            // Set both FTSR and RTSR bits
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        // Configure GPIO port selection in SYSCFG_EXTICR registers
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;  // Which EXTICR register (0-3)
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;  // Which 4-bit field in register
        uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);   // Get port code (0-7)
        SYSCFG_PCLK_EN(); // Enable SYSCFG peripheral clock
        SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

        // Enable EXTI interrupt delivery using IMR
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp = 0;

    // 2. Configure GPIO pin output speed
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear existing bits
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp = 0;

    // 3. Configure pull-up/pull-down resistor settings
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear existing bits
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp = 0;

    // 4. Configure output type (push-pull or open-drain)
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Clear existing bit
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp = 0;

    // 5. Configure alternate function if pin mode is alternate function
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; // Select AFR[0] or AFR[1]
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; // 4-bit field position within register

        // Clear existing alternate function bits
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
        // Set new alternate function
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
    }
}

/******************************************************************************
 * @fn                   - GPIO_DeInit
 *
 * @brief                - This function resets all the registers of a given GPIO port
 *                         to their default reset values, effectively disabling the port.
 *
 * @param[in] pGPIOx     - Base address of the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 *
 * @return               - None
 *
 * @note                 - This uses the RCC AHB1RSTR register to reset the specific GPIO peripheral.
 *****************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    // Reset GPIOA peripheral
    if (pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    // Reset GPIOB peripheral
    else if (pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    // Reset GPIOC peripheral
    else if (pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    // Reset GPIOD peripheral
    else if (pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    // Reset GPIOE peripheral
    else if (pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    // Reset GPIOF peripheral
    else if (pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    // Reset GPIOG peripheral
    else if (pGPIOx == GPIOG)
    {
        // GPIOG_RESET();
    }
    // Reset GPIOH peripheral
    else if (pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
}

/*
 * Data read and write
 */

/******************************************************************************
 * @fn                   - GPIO_ReadFromInputPin
 *
 * @brief                - This function reads the value of a specific input pin on a GPIO port.
 *
 * @param[in] pGPIOx     - Base address of the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @param[in] PinNumber  - The pin number to read (0-15).
 *
 * @return               - 0 or 1 (GPIO_PIN_RESET or GPIO_PIN_SET) representing the pin state.
 *
 * @note                 - Ensure the pin is configured as an input.
 *****************************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    // Extract specific pin value from IDR register
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
    return value;
}

/******************************************************************************
 * @fn                   - GPIO_ReadFromInputPort
 *
 * @brief                - This function reads the entire 16-bit value from the input data register
 *                         of a specified GPIO port.
 *
 * @param[in] pGPIOx     - Base address of the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 *
 * @return               - A 16-bit unsigned integer representing the states of all input pins
 *                         on the specified port.
 *
 * @note                 - Returns the raw 16-bit value from the IDR register.
 *****************************************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint16_t value;
    // Read entire port input data register
    value = (uint16_t)pGPIOx->IDR;
    return value;
}

/******************************************************************************
 * @fn                   - GPIO_WriteToOutputPin
 *
 * @brief                - This function writes a specific value (HIGH or LOW) to an output pin.
 *
 * @param[in] pGPIOx     - Base address of the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @param[in] PinNumber  - The pin number to write to (0-15).
 * @param[in] Value      - The value to write (GPIO_PIN_SET or GPIO_PIN_RESET).
 *
 * @return               - None
 *
 * @note                 - Ensure the pin is configured as an output.
 *****************************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    // Set pin to HIGH
    if (Value == GPIO_PIN_SET)
    {
        pGPIOx->ODR |= (1 << PinNumber);
    }
    // Set pin to LOW
    else
    {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}

/******************************************************************************
 * @fn                   - GPIO_WriteToOutputPort
 *
 * @brief                - This function writes a 16-bit value to the entire output data register
 *                         of a specified GPIO port, setting the states of all output pins.
 *
 * @param[in] pGPIOx     - Base address of the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @param[in] Value      - The 16-bit value to write to the ODR.
 *
 * @return               - None
 *
 * @note                 - All pins configured as output on the port will be affected.
 *****************************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
    // Write entire 16-bit value to output data register
    pGPIOx->ODR = Value;
}

/******************************************************************************
 * @fn                   - GPIO_ToggleOutputPin
 *
 * @brief                - This function toggles the state of a specific output pin.
 *
 * @param[in] pGPIOx     - Base address of the GPIO peripheral (e.g., GPIOA, GPIOB, etc.).
 * @param[in] PinNumber  - The pin number to toggle (0-15).
 *
 * @return               - None
 *
 * @note                 - Ensure the pin is configured as an output.
 *****************************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    // Toggle pin state using XOR operation
    pGPIOx->ODR ^= (1 << PinNumber);
}

/*
* IRQ Configuration and ISR handling
*/

/******************************************************************************
* @fn - GPIO_IRQInterruptConfig
*
* @brief - This function configures the interrupt for a given IRQ number.
*
* @param[in] IRQNumber - The IRQ number of the peripheral.

* @param[in] EnorDi - ENABLE or DISABLE macro (1 to enable, 0 to disable).
*
* @return - None
*
* @note - This enables/disables the global interrupt in NVIC and sets priority.
******************************************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        // Enable interrupt for IRQ numbers 0-31
        if (IRQNumber <= 31)
        {
            NVIC_ISER0 |= (1 << IRQNumber);
        }
        // Enable interrupt for IRQ numbers 32-63
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        // Enable interrupt for IRQ numbers 64-95
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        // Disable interrupt for IRQ numbers 0-31
        if (IRQNumber <= 31)
        {
            NVIC_ICER0 |= (1 << IRQNumber);
        }
        // Disable interrupt for IRQ numbers 32-63
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        // Disable interrupt for IRQ numbers 64-95
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}

///******************************************************************************
// * @fn                   - GPIO_IRQPriorityConfig
// *
// * @brief                - This function configures the priority for a given IRQ number in the NVIC.
// *
// * @param[in] IRQNumber  - The IRQ number of the peripheral.
// * @param[in] IRQPriority - The priority level to set for the IRQ (0-15).
// *
// * @return               - None
// *
// * @note                 - Lower numerical value means higher priority.
// *****************************************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    // Calculate which IPR register to use (4 IRQs per register)
    uint8_t iprx = IRQNumber / 4;
    // Calculate position within the IPR register
    uint8_t iprx_section = IRQNumber % 4;

    // Calculate bit shift (only upper 4 bits implemented in STM32F4)
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    // Clear existing priority bits
    *(NVIC_PR_BASE_ADDR + iprx) &= ~(0xF << shift_amount);
    // Set new priority value
    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

///******************************************************************************
// * @fn                   - GPIO_IRQHandling
// *
// * @brief                - This function handles the interrupt service routine for GPIO external
// *                         interrupts. It clears the pending bit for the corresponding pin.
// *
// * @param[in] PinNumber  - The pin number for which the interrupt occurred (0-15).
// *
// * @return               - None
// *
// * @note                 - This function should be called from the specific EXTIx_IRQHandler.
// *****************************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
    // Check if interrupt is pending for this pin
    if (EXTI->PR & (1 << PinNumber))
    {
        // Clear pending bit by writing 1
        EXTI->PR |= (1 << PinNumber);
    }
}
