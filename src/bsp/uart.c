#include "uart.h"

void UART_Init(void)
{
    USART1->BRR = 0x341;                                      // 9600 baud at 8 MHz
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; // Enable TX, RX and USART
}

void USART1_SendChar(char c)
{
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = c;
    while (!(USART1->SR & USART_SR_TC))
        ; // transmission complete
}

void USART1_SendString(char *str)
{
    while (*str)
    {
        USART1_SendChar(*str++);
    }
}