#include "timer.h"

volatile uint32_t g_tick_ms = 0;

void Timer_Init(void)
{
    TIM2->CR1 = 0;
    TIM2->CR1 |= (1 << 7); // ARPE enable

    TIM2->PSC = 799; // prescaler
    TIM2->ARR = 9;   // auto reload

    TIM2->CNT = 0;

    TIM2->DIER |= 1; // update interrupt
    TIM2->CR1 |= 1;  // start timer
}
void TIM2_PWM_SetDutyCycle(uint8_t duty)
{
    if (duty > 9)
        duty = 9;
    TIM2->CCR1 = duty;
}

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & 1)
    {
        TIM2->SR &= ~1;
        g_tick_ms++;
    }
}