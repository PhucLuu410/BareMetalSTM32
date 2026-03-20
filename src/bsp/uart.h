#ifndef UART_H
#define UART_H

#include "stm32f103xb.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void UART_Init(void);
void USART1_SendChar(char c);
void USART1_SendString(char *str);

#endif