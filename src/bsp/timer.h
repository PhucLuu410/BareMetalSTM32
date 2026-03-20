#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <stdbool.h>
#include "stm32f103xb.h"

void Timer_Init(void);
void TIM2_PWM_SetDutyCycle(uint8_t duty);

#endif