
#include <stdio.h>
#include <string.h>
#include "stm32f446xx.h"

char msg[1024] = "UART Tx Testing...\r\n";

USART_Handle_t usart2_Handle;

void UART2_Init(void)
{
    usart2_Handle.pUSARTx = USART2;
    usart2_Handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
    usart2_Handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
    usart2_Handle.USART_Config.USART_Mode = USART_MODE_TX;
    usart2_Handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
    usart2_Handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
    usart2_Handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
    USART_Init(&usart2_Handle);
}

int main(void)
{
    UART2_Init();

    while(1)
    {
        UART2_WriteString("UART Tx Testing...\r\n");
        for(int i=0; i<500000; i++);  // Simple delay
    }
}



void UART2_WriteChar(char ch)
{
    while(!(USART2->SR & 0x0080));  // Wait until Tx buffer empty
    USART2->DR = ch;
}

void UART2_WriteString(char *str)
{
    while(*str)
    {
        UART2_WriteChar(*str++);
    }
}
