/*
 * stm32f446xx_gpio_driver.c
 *
 * Created on: Jun 9, 2025
 * Author: Rahul B.
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
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN(); // Macro from stm32f446xx.h, equivalent to (RCC->AHB1ENR |= (1 << 0));
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 1));
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 2));
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 3));
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 4));
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 5));
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 6));
        }
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN(); // (RCC->AHB1ENR |= (1 << 7));
        }
        // STM32F446RE does not have GPIOI, J, K. Add if your specific F4 variant does.
    }
    else // EnorDi == DISABLE
    {
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI(); // Macro from stm32f446xx.h, equivalent to (RCC->AHB1ENR &= ~(1 << 0));
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 1));
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 2));
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 3));
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 4));
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 5));
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI(); // (RCC->AHB1ENR &= ~(1 << 6));
        }
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
    // GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    // 1. Configure the mode of GPIO pin
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        // Clear the existing bits first
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        // Set the new mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER |= temp;
    }
    else
    {
        // Handle interrupt modes (GPIO_MODE_IT_FT, GPIO_MODE_IT_RT, GPIO_MODE_IT_RFT)
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            // 1. Configure the FTSR (Falling Trigger Selection Register)
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            // Clear the corresponding RTSR bit
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            // 1. Configure the RTSR (Rising Trigger Selection Register)
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            // Clear the corresponding FTSR bit
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            // 1. Configure both FTSR and RTSR
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        // 2. Configure the GPIO port selection in SYSCFG_EXTICR
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
       uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
        SYSCFG_PCLK_EN(); // Enable SYSCFG clock
        SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

        // 3. Enable the EXTI interrupt delivery using IMR (Interrupt Mask Register)
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp = 0;

    // 2. Configure the speed
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp = 0;

    // 3. Configure the pull-up/pull-down settings
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp = 0;

    // 4. Configure the output type (Open-drain or Push-pull)
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // Clear
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp = 0;

    // 5. Configure the alternate functionality
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; // AFR[0] or AFR[1]
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; // Bits within the selected AFR register

        // Clear existing bits (4 bits for each pin)
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
    if (pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if (pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if (pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if (pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if (pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if (pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if (pGPIOx == GPIOG)
    {
        // GPIOG_RESET();
    }
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
    if (Value == GPIO_PIN_SET)
    {
        pGPIOx->ODR |= (1 << PinNumber);
    }
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

        // Enable the interrupt
        if (IRQNumber <= 31)
        {
            NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        // Disable the interrupt
        if (IRQNumber <= 31)
        {
            NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
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
    // Find out the IPR register
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    // Calculate the shift amount (only upper 4 bits are implemented in STM32F4)
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    // Clear the existing priority
    *(NVIC_PR_BASE_ADDR + iprx) &= ~(0xF << shift_amount);
    // Set the new priority
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
    // Clear the EXTI PR register corresponding to the pin number
    if (EXTI->PR & (1 << PinNumber))
    {
        // Clear by writing 1 to the bit
        EXTI->PR |= (1 << PinNumber);
    }
}
