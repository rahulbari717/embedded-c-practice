/**
 * @file    stm32f446xx_i2c_driver.c
 * @brief   I2C driver source file for STM32F446xx microcontroller
 * @details This file implements all the APIs declared in stm32f446xx_i2c_driver.h
 *          for configuring the I2C peripheral, sending and receiving data,
 *          and handling interrupts and events.
 *
 * @author Rahul B.
 * @date   Jun 17, 2025
 * @version 1.0
 */

#include "stm32f446xx_i2c_driver.h"

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512}; 
uint16_t AHB1_PreScaler[4] = {2,4,8,16}; 

/**
 * @brief  Get the status of a specific I2C flag
 * @param  pI2Cx: Pointer to I2C peripheral base address
 * @param  FlagName: Name of the flag to check (e.g., I2C_SR1_TXE, I2C_SR1_RXNE)
 * @retval FLAG_SET or FLAG_RESET
 */
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
    if ((pI2Cx->SR1 & FlagName) == FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}

// Helper function to generate start condition
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

// Helper function to clear ADDR flag
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{
    uint32_t dummyRead;
    dummyRead = pI2Cx->SR1;
    dummyRead = pI2Cx->SR2;
    (void)dummyRead; // To suppress compiler warning about unused variable
}

// Helper function to execute address phase
static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;
    SlaveAddr &= ~(1 << 0); // Clear LSB for write
    pI2Cx->DR = SlaveAddr;
}

// Helper function to execute address phase for read
static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;
    SlaveAddr |= (1 << 0); // Set LSB for read
    pI2Cx->DR = SlaveAddr;
}


/**
 * @brief  Enable or disable I2C peripheral clock
 * @param  pI2Cx: Pointer to I2C peripheral base address
 * @param  EnOrDi: ENABLE or DISABLE macros
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        // Enable the I2C peripheral by setting the PE bit in CR1 register
        pI2Cx->CR1 |= (1 << I2C_CR1_PE);
    }
    else
    {
        // Disable the I2C peripheral by clearing the PE bit in CR1 register
        pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
    }
}


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
 * @brief  Initialize the I2C peripheral
 * @param  pI2CHandle: Pointer to I2C handle structure
 * @note   Configures clock speed, device address, ACK, etc.
 */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t tempreg = 0;

    // 1. Enable peripheral clock
    I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

    // 2. Configure ACK control
    tempreg |= (pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK);
    pI2CHandle->pI2Cx->CR1 = tempreg;

    // 3. Configure frequency in CR2
    // HCLK = 16 MHz (example); specify APB1 in MHz
    // Assuming RCC_GetPCLK1Val() returns the PCLK1 frequency in Hz
    tempreg = RCC_GetPCLK1Val() / 1000000U;
    pI2CHandle->pI2Cx->CR2 |= (tempreg & 0x3F);

    // 4. Configure own address
    // The OAR1 register expects the address shifted by 1 bit, and bit 0 must be 1 for 7-bit addressing mode.
    pI2CHandle->pI2Cx->OAR1 = (pI2CHandle->I2C_Config.I2C_DeviceAddress << 1) | (1 << 14); // Set bit 14 as per RM

    // 5. Configure CCR register (standard vs fast mode)
    if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM) // Standard Mode
    {
        // CCR = PCLK1 / (2 * SCL_SPEED)
        tempreg = (RCC_GetPCLK1Val() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
    }
    else // Fast Mode
    {
        tempreg = (RCC_GetPCLK1Val() / (pI2CHandle->I2C_Config.I2C_SCLSpeed * 3)); // Default for FM, will be adjusted by DUTY
        tempreg |= (1 << I2C_CCR_FS); // Set F/S bit for Fast Mode
        if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_16_9)
        {
            tempreg = (RCC_GetPCLK1Val() / (pI2CHandle->I2C_Config.I2C_SCLSpeed * 25)); // For 16/9 duty cycle
            tempreg |= (1 << I2C_CCR_DUTY); // Set DUTY bit for 16/9
        }
        else // I2C_FM_DUTY_2
        {
            tempreg = (RCC_GetPCLK1Val() / (pI2CHandle->I2C_Config.I2C_SCLSpeed * 3)); // For 2 duty cycle
        }
    }
    pI2CHandle->pI2Cx->CCR = (tempreg & 0xFFF); // CCR is 12-bit

    // 6. Configure rise time in TRISE
    if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM) // Standard Mode
    {
        // TRISE = (PCLK1_FREQ / 10^6) + 1 (for 100ns max rise time)
        pI2CHandle->pI2Cx->TRISE = (RCC_GetPCLK1Val() / 1000000U) + 1;
    }
    else // Fast Mode
    {
        // TRISE = ((PCLK1_FREQ * 300) / 10^9) + 1 (for 300ns max rise time)
        pI2CHandle->pI2Cx->TRISE = ((RCC_GetPCLK1Val() * 300) / 1000000000U) + 1;
    }

    // 7. Enable the peripheral (This step is often done after all configurations are complete)
    // pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_PE); // Moved to I2C_PeripheralControl for consistency
}

/**
 * @brief  De-initialize the I2C peripheral
 * @param  pI2Cx: Pointer to I2C peripheral base address
 * @note   Resets the I2C peripheral to its default state
 */
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
    // Assuming a macro to reset peripheral. For STM32, this typically involves
    // setting and clearing the corresponding bit in the RCC_APBxRSTR register.
    if (pI2Cx == I2C1)
    {
        I2C1_REG_RESET(); // Assuming this macro is defined in stm32f446xx.h
    }
    else if (pI2Cx == I2C2)
    {
        I2C2_REG_RESET();
    }
    else if (pI2Cx == I2C3)
    {
        I2C3_REG_RESET();
    }
    // Disable peripheral clock after reset
    I2C_PeriClockControl(pI2Cx, DISABLE);
}

/**
 * @brief  Master send data in blocking mode (polling)
 * @param  pI2CHandle: Pointer to I2C handle structure
 * @param  pTxBuffer: Pointer to transmit buffer
 * @param  Len: Length of data to be transmitted
 * @param  SlaveAddr: 7-bit slave address
 * @param  RepeatedStart: Enable or disable repeated start
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,
                       uint8_t *pTxBuffer, uint32_t Len,
                       uint8_t SlaveAddr, uint8_t RepeatedStart)
{
    // 1. Generate START condition
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    // 2. Confirm START bit is set (SB flag)
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_SB));

    // 3. Send address (7-bit slave address + R/W bit = 0 for write)
    I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SlaveAddr);

    // 4. Confirm ADDR flag is set (address matched)
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_ADDR));

    // 5. Clear ADDR flag (read SR1, then SR2)
    I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

    // 6. Send data until Len becomes 0
    while (Len > 0)
    {
        while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_TXE)); // Wait for TXE to be set (data register empty)
        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        Len--;
    }

    // 7. Wait for TXE and BTF (Byte Transfer Finished) flags to be set
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_TXE));
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_BTF));

    // 8. Generate STOP condition if RepeatedStart is not requested
    if (RepeatedStart == DISABLE)
    {
        I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
    }
}

/**
 * @brief  Master receive data in blocking mode (polling)
 * @param  pI2CHandle: Pointer to I2C handle structure
 * @param  pRxBuffer: Pointer to receive buffer
 * @param  Len: Length of data to be received
 * @param  SlaveAddr: 7-bit slave address
 * @param  RepeatedStart: Enable or disable repeated start
 */
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,
                          uint8_t *pRxBuffer, uint32_t Len,
                          uint8_t SlaveAddr, uint8_t RepeatedStart)
{
    // 1. Generate START condition
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    // 2. Confirm START bit is set (SB flag)
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_SB));

    // 3. Send address (7-bit slave address + R/W bit = 1 for read)
    I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx, SlaveAddr);

    // 4. Confirm ADDR flag is set (address matched)
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_ADDR));

    // 5. Receive data for Len-1 bytes
    if (Len == 1)
    {
        // Disable ACK
        I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE);

        // Clear ADDR flag
        I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

        // Wait for RXNE
        while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RXNE));

        // Generate STOP condition
        if (RepeatedStart == DISABLE)
        {
            I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
        }

        // Read data
        *pRxBuffer = pI2CHandle->pI2Cx->DR;
    }
    else // Len > 1
    {
        // Clear ADDR flag
        I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

        while (Len > 0)
        {
            while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RXNE)); // Wait for RXNE

            if (Len == 2) // Last two bytes
            {
                I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE); // Disable ACK for the second to last byte

                if (RepeatedStart == DISABLE)
                {
                    I2C_GenerateStopCondition(pI2CHandle->pI2Cx); // Generate STOP for the very last byte
                }
            }
            *pRxBuffer = pI2CHandle->pI2Cx->DR;
            pRxBuffer++;
            Len--;
        }
    }

    // Re-enable ACK if it was enabled initially
    if (pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE)
    {
        I2C_ManageAcking(pI2CHandle->pI2Cx, ENABLE);
    }
}


/*
 * IRQ Configuration & ISR Handling
*/

/**
 * @brief  Configure I2C interrupt (enable/disable)
 * @param  IRQNumber: IRQ number of the I2C peripheral
 * @param  EnOrDi: ENABLE or DISABLE macros
 */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (IRQNumber < 32)
        {
            // Program ISER0 register
            NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber >= 32 && IRQNumber < 64)
        {
            // Program ISER1 register
            NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            // Program ISER2 register
            NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        if (IRQNumber < 32)
        {
            // Program ICER0 register
            NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber >= 32 && IRQNumber < 64)
        {
            // Program ICER1 register
            NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            // Program ICER2 register
            NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}

/**
 * @brief  Configure I2C interrupt priority
 * @param  IRQNumber: IRQ number of the I2C peripheral
 * @param  IRQPriority: Priority value
 */
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    // Find IPR register
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED); // NO_PR_BITS_IMPLEMENTED is MCU specific

    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

/**
 * @brief  I2C Event Interrupt Service Routine Handling
 * @param  pI2CHandle: Pointer to I2C handle structure
 */
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle)
{
    // Implement event handling logic here. This is complex and depends on whether
    // the I2C is in master/slave mode, transmitting/receiving, etc.
    // This typically involves checking SR1 and SR2 registers and clearing flags.

    // Example: Master mode, Byte Transfer Finished (BTF)
    if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_BTF))
    {
        // Handle BTF event (e.g., if transmit complete, generate stop or send more data)
        // This is where you would transition states in a non-blocking communication
    }
    // Example: Master mode, Address Sent (ADDR)
    else if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_ADDR))
    {
        // Handle ADDR event (e.g., clear flag, prepare to send/receive data)
        I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
    }
    // Example: Master mode, Start Bit (SB)
    else if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_SB))
    {
        // Handle SB event (e.g., send slave address)
    }
    // Example: Transmit Data Register Empty (TXE)
    else if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_TXE))
    {
        // Handle TXE event (e.g., load next byte into DR)
    }
    // Example: Receive Data Register Not Empty (RXNE)
    else if (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_RXNE))
    {
        // Handle RXNE event (e.g., read byte from DR)
    }
    // ... add more event handling for STOPF, AF, etc. ...
}

/**
 * @brief  I2C Error Interrupt Service Routine Handling
 * @param  pI2CHandle: Pointer to I2C handle structure
 */
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle)
{
    uint32_t temp1, temp2;

    // Check for Bus Error (BERR)
    temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITERREN);
    temp2 = I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_BERR);
    if (temp1 && temp2)
    {
        // Clear BERR flag
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_BERR);
        // Handle Bus Error: Notify application, reset I2C, etc.
    }

    // Check for Arbitration Lost (ARLO)
    temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITERREN);
    temp2 = I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_ARLO);
    if (temp1 && temp2)
    {
        // Clear ARLO flag
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_ARLO);
        // Handle Arbitration Lost: Notify application, retry transaction, etc.
    }

    // Check for Acknowledge Failure (AF)
    temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITERREN);
    temp2 = I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_AF);
    if (temp1 && temp2)
    {
        // Clear AF flag
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_AF);
        // Handle Acknowledge Failure: Slave not responding, invalid address, etc.
    }

    // Check for Overrun/Underrun (OVR)
    temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITERREN);
    temp2 = I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_OVR);
    if (temp1 && temp2)
    {
        // Clear OVR flag
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_OVR);
        // Handle Overrun/Underrun
    }

    // Check for Timeout (TIMEOUT)
    temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITERREN);
    temp2 = I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SR1_TIMEOUT);
    if (temp1 && temp2)
    {
        // Clear TIMEOUT flag
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_TIMEOUT);
        // Handle Timeout
    }
}


/*
 * Other Peripheral Control APIs
*/

/**
 * @brief  Enable or disable the I2C peripheral
 * @param  pI2Cx: Pointer to I2C peripheral base address
 * @param  EnOrDi: ENABLE or DISABLE macros
 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        pI2Cx->CR1 |= (1 << I2C_CR1_PE);
    }
    else
    {
        pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
    }
}

/**
 * @brief  Manage I2C Acknowledgment (ACK)
 * @param  pI2Cx: Pointer to I2C peripheral base address
 * @param  EnOrDi: ENABLE or DISABLE macros
 */
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
    }
    else
    {
        pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
    }
}

/**
 * @brief  Generate I2C STOP condition
 * @param  pI2Cx: Pointer to I2C peripheral base address
 */
void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

/**
 * @brief  Enable or disable I2C Slave Address Call
 * @param  pI2Cx: Pointer to I2C peripheral base address
 * @param  EnOrDi: ENABLE or DISABLE macros
 */
void I2C_SlaveEnableDisableCall(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        pI2Cx->CR1 |= (1 << I2C_CR1_ENGC); // Enable General Call (ENGC bit in CR1)
    }
    else
    {
        pI2Cx->CR1 &= ~(1 << I2C_CR1_ENGC); // Disable General Call
    }
}
