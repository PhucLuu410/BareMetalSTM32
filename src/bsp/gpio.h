#ifndef GPIO_H
#define GPIO_H

#include <stdbool.h>
#include <stdio.h>
#include "stm32f103xb.h"

void GPIO_Init(void);
bool GPIO_ReadPin(uint8_t pin);
void GPIO_WritePin(uint8_t pin);
void GPIO_ResetPin(uint8_t pin);
void EXTI0_IRQHandler(void);

#endif