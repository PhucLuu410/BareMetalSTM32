#include "exti.h"

void EXTI_Init(void)
{
    EXTI->IMR |= 1 << 0; // unmask EXTI0
    EXTI->FTSR |= (1 << 0);
    EXTI->RTSR &= ~(1 << 0);
    EXTI->PR |= (1 << 0);
    NVIC_EnableIRQ(EXTI0_IRQn); // enable EXTI0 interrupt
    NVIC_EnableIRQ(TIM2_IRQn);
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
}