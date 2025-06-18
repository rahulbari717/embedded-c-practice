/*
 * stm32f446xx_USART_driver.c
 *
 *  Created on: Jun 18, 2025
 *      Author: Rahul B.
 */

#include "stm32f446xx_USART_driver.h"

/*********************************************************************
 * @fn      		  - USART_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given USART port
 *
 * @param[in]         - Base address of the USART peripheral
 * @param[in]         - ENABLE or DISABLE macros
 *
 * @return            - none
 *
 * @Note              - none
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pUSARTx == USART1)
        {
            USART1_PCLK_EN();
        }else if(pUSARTx == USART2)
        {
            USART2_PCLK_EN();
        }else if(pUSARTx == USART3)
        {
            USART3_PCLK_EN();
        }else if(pUSARTx == UART4)
        {
            UART4_PCLK_EN();
        }else if(pUSARTx == UART5)
        {
            UART5_PCLK_EN();
        }else if(pUSARTx == USART6)
        {
            USART6_PCLK_EN();
        }
    }
    else
    {
        if(pUSARTx == USART1)
        {
            USART1_PCLK_DI();
        }else if(pUSARTx == USART2)
        {
            USART2_PCLK_DI();
        }else if(pUSARTx == USART3)
        {
            USART3_PCLK_DI();
        }else if(pUSARTx == UART4)
        {
            UART4_PCLK_DI();
        }else if(pUSARTx == UART5)
        {
            UART5_PCLK_DI();
        }else if(pUSARTx == USART6)
        {
            USART6_PCLK_DI();
        }
    }
}

/*********************************************************************
 * @fn      		  - USART_Init
 *
 * @brief             - This function initializes the USART peripheral
 *
 * @param[in]         - USART handle
 *
 * @return            - none
 *
 * @Note              - none
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{
    uint32_t tempreg = 0;
    USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);
    // Configure the CR1 register
    tempreg = 0;
    
    if (pUSARTHandle->USART_Config.USART_Mode & USART_MODE_ONLY_RX)
    {
        tempreg |= (1 << USART_CR1_RE);
    } else if (pUSARTHandle->USART_Config.USART_Mode & USART_MODE_ONLY_TX) {
        tempreg |= (1 << USART_CR1_TE);
    } else if (pUSARTHandle->USART_Config.USART_Mode & USART_MODE_TXRX) {
        tempreg |= ((1 << USART_CR1_RE) | (1 << USART_CR1_TE));
    }    
    // Implement the code to configure the word length
    tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;
    // Configure the parity control bit 
    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        tempreg |= (1 << USART_CR1_PCE);
    } else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
    {
        tempreg |= (1 << USART_CR1_PCE);
        tempreg |= (1 << USART_CR1_PS);
    }    

    pUSARTHandle->pUSARTx->CR1 = tempreg;

    // Configure the CR2 register
    tempreg = 0;
    tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;
    
    pUSARTHandle->pUSARTx->CR2 = tempreg;

    // Configure the CR3 register
    tempreg = 0;
    if(pUSARTHandle ->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS ){
        tempreg |= pUSARTHandle->USART_Config.USART_HWFlowControl << USART_CR3_CTSE;
    }
    else if(pUSARTHandle ->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS ){
        tempreg |= pUSARTHandle->USART_Config.USART_HWFlowControl << USART_CR3_RTSE;
    }
    else if(pUSARTHandle ->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS ){
        tempreg |= pUSARTHandle->USART_Config.USART_HWFlowControl << USART_CR3_RTSE;
        tempreg |= pUSARTHandle->USART_Config.USART_HWFlowControl << USART_CR3_CTSE;
    }

    pUSARTHandle->pUSARTx->CR3 = tempreg;

    // Configure the baud rate
    USART_SetBaudRate(pUSARTHandle->pUSARTx, pUSARTHandle->USART_Config.USART_Baud);
}
/*********************************************************************
 * @fn      		  - USART_DeInit
 *
 * @brief             - This function de-initializes the USART peripheral
 *
 * @param[in]         - Base address of the USART peripheral
 *
 * @return            - none
 *
 * @Note              - none
 */
void USART_DeInit(USART_RegDef_t *pUSARTx)
{
    if(pUSARTx == USART1)
    {
        USART1_REG_RESET();
    }else if(pUSARTx == USART2)
    {
        USART2_REG_RESET();
    }else if(pUSARTx == USART3)
    {
        USART3_REG_RESET();
    }else if(pUSARTx == UART4)
    {
        UART4_REG_RESET();
    }else if(pUSARTx == UART5)
    {
        UART5_REG_RESET();
    }else if(pUSARTx == USART6)
    {
        USART6_REG_RESET();
    }
}

/*********************************************************************
 * @fn      		  - USART_SendData
 *
 * @brief             - This function sends data over USART
 *
 * @param[in]         - USART handle
 * @param[in]         - Pointer to TX buffer
 * @param[in]         - Length of data to send
 *
 * @return            - none
 *
 * @Note              - Blocking call
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint16_t *pdata;

    for(uint32_t i = 0; i < Len; i++)
    {
        // Wait until TXE flag is set
        while(!(pUSARTHandle->pUSARTx->SR & (1 << USART_SR_TXE)));

        if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            pdata = (uint16_t*)pTxBuffer;
            pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);
            
            if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                pTxBuffer++;
                pTxBuffer++;
            }
            else
            {
                pTxBuffer++;
            }
        }
        else
        {
            pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
            pTxBuffer++;
        }
    }

    // Wait until TC flag is set
    while(!(pUSARTHandle->pUSARTx->SR & (1 << USART_SR_TC)));
}

/*********************************************************************
 * @fn      		  - USART_ReceiveData
 *
 * @brief             - This function receives data over USART
 *
 * @param[in]         - USART handle
 * @param[in]         - Pointer to RX buffer
 * @param[in]         - Length of data to receive
 *
 * @return            - none
 *
 * @Note              - Blocking call
 */
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    for(uint32_t i = 0; i < Len; i++)
    {
        // Wait until RXNE flag is set
        while(!(pUSARTHandle->pUSARTx->SR & (1 << USART_SR_RXNE)));

        if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                *((uint16_t*)pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);
                pRxBuffer++;
                pRxBuffer++;
            }
            else
            {
                *pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
                pRxBuffer++;
            }
        }
        else
        {
            if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
            }
            else
            {
                *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);
            }
            pRxBuffer++;
        }
    }
}

/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *
 * @brief             - This function sets the baud rate for USART communication
 *
 * @param[in]         - Base address of the USART peripheral
 * @param[in]         - Desired baud rate
 *
 * @return            - none
 *
 * @Note              - none
 */
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
    uint32_t PCLKx;
    uint32_t usartdiv;
    uint32_t M_part,F_part;
    uint32_t tempreg = 0;

    // Get the value of APB clock
    if(pUSARTx == USART1 || pUSARTx == USART6)
    {
        PCLKx = RCC_GetPCLK2Value();
    }else
    {
        PCLKx = RCC_GetPCLK1Value();
    }

    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
    {
        // OVER8 = 1, over sampling by 8
        usartdiv = ((25 * PCLKx) / (2 * BaudRate));
    }else
    {
        // OVER8 = 0, over sampling by 16
        usartdiv = ((25 * PCLKx) / (4 * BaudRate));
    }

    M_part = usartdiv/100;
    F_part = (usartdiv - (M_part * 100));

    if(pUSARTx->CR1 & (1 << USART_CR1_OVER8))
    {
        F_part = ((((F_part * 8) + 50) / 100)) & ((uint8_t)0x07);
    }else
    {
        F_part = ((((F_part * 16) + 50) / 100)) & ((uint8_t)0x0F);
    }

    tempreg |= M_part << 4;
    tempreg |= F_part;

    pUSARTx->BRR = tempreg;
}/*********************************************************************
 * @fn      		  - USART_IRQInterruptConfig
 *
 * @brief             - This function configures the interrupt for USART peripheral
 *
 * @param[in]         - IRQ number
 * @param[in]         - ENABLE or DISABLE macros
 *
 * @return            - none
 *
 * @Note              - none
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        if(IRQNumber <= 31)
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if(IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if(IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}

/*********************************************************************
 * @fn      		  - USART_IRQPriorityConfig
 *
 * @brief             - This function configures the priority for USART interrupt
 *
 * @param[in]         - IRQ number
 * @param[in]         - IRQ priority
 *
 * @return            - none
 *
 * @Note              - none
 */
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}


 /*********************************************************************
 * @fn      		  - USART_IRQHandling
 *
 * @brief             - This function handles USART interrupt
 *
 * @param[in]         - USART handle
 *
 * @return            - none
 *
 * @Note              - none
 */
void USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp1, temp2, temp3;

    // Check for TC flag
    temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_TC);
    temp2 = pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_TCIE);

    if(temp1 && temp2)
    {
        // Handle TC interrupt
        if(pUSARTHandle->TxState == USART_BUSY_IN_TX)
        {
            if(pUSARTHandle->TxLen == 0)
            {
                pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TCIE);
                pUSARTHandle->TxState = USART_READY;
                pUSARTHandle->pTxBuffer = NULL;
                pUSARTHandle->TxLen = 0;

                // Execute the application callback if TxCpltCallback is not NULL
                if(pUSARTHandle->TxCpltCallback != NULL)
                {
                    pUSARTHandle->TxCpltCallback(pUSARTHandle);
                }
            }
        }
    }

    // Check for RXNE flag
    temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_RXNE);
    temp2 = pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_RXNEIE);

    if(temp1 && temp2)
    {
        // Handle RXNE interrupt
        if(pUSARTHandle->RxState == USART_BUSY_IN_RX)
        {
            if(pUSARTHandle->RxLen > 0)
            {
                if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
                {
                    if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
                    {
                        *((uint16_t*)pUSARTHandle->pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)0x01FF);
                        pUSARTHandle->pRxBuffer += 2;
                        pUSARTHandle->RxLen -= 2;
                    }
                    else
                    {
                        *pUSARTHandle->pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
                        pUSARTHandle->pRxBuffer++;
                        pUSARTHandle->RxLen--;
                    }
                }
                else
                {
                    if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
                    {
                        *pUSARTHandle->pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
                    }
                    else
                    {
                        *pUSARTHandle->pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);
                    }
                    pUSARTHandle->pRxBuffer++;
                    pUSARTHandle->RxLen--;
                }
            }

            if(pUSARTHandle->RxLen == 0)
            {
                pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_RXNEIE);
                pUSARTHandle->RxState = USART_READY;
                pUSARTHandle->pRxBuffer = NULL;
                pUSARTHandle->RxLen = 0;

                // Execute the application callback if RxCpltCallback is not NULL
                if(pUSARTHandle->RxCpltCallback != NULL)
                {
                    pUSARTHandle->RxCpltCallback(pUSARTHandle);
                }
            }
        }
    }

    // Check for CTS flag
    temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_CTS);
    temp2 = pUSARTHandle->pUSARTx->CR3 & (1 << USART_CR3_CTSE);
    temp3 = pUSARTHandle->pUSARTx->CR3 & (1 << USART_CR3_CTSIE);

    if(temp1 && temp2 && temp3)
    {
        // Clear the CTS flag
        pUSARTHandle->pUSARTx->SR &= ~(1 << USART_SR_CTS);

        // Execute the application callback if CTSCallback is not NULL
        if(pUSARTHandle->CTSCallback != NULL)
        {
            pUSARTHandle->CTSCallback(pUSARTHandle);
        }
    }

    // Check for IDLE detection flag
    temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_IDLE);
    temp2 = pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_IDLEIE);

    if(temp1 && temp2)
    {
        // Clear the IDLE flag
        temp1 = pUSARTHandle->pUSARTx->SR;
        temp1 = pUSARTHandle->pUSARTx->DR;

        // Execute the application callback if IDLECallback is not NULL
        if(pUSARTHandle->IDLECallback != NULL)
        {
            pUSARTHandle->IDLECallback(pUSARTHandle);
        }
    }

    // Check for Overrun detection flag
    temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_ORE);
    temp2 = pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_RXNEIE);

    if(temp1 && temp2)
    {
        // Execute the application callback if ORECallback is not NULL
        if(pUSARTHandle->ORECallback != NULL)
        {
            pUSARTHandle->ORECallback(pUSARTHandle);
        }
    }

    // Check for Error flag
    temp2 = pUSARTHandle->pUSARTx->CR3 & (1 << USART_CR3_EIE);

    if(temp2)
    {
        temp1 = pUSARTHandle->pUSARTx->SR;
        if(temp1 & (1 << USART_SR_FE))
        {
            if(pUSARTHandle->ErrorCallback != NULL)
            {
                pUSARTHandle->ErrorCallback(pUSARTHandle);
            }
        }

        if(temp1 & (1 << USART_SR_NE))
        {
            if(pUSARTHandle->ErrorCallback != NULL)
            {
                pUSARTHandle->ErrorCallback(pUSARTHandle);
            }
        }

        if(temp1 & (1 << USART_SR_ORE))
        {
            if(pUSARTHandle->ErrorCallback != NULL)
            {
                pUSARTHandle->ErrorCallback(pUSARTHandle);
            }
        }
    }
}

