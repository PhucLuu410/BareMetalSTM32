#include "stm32f103xb.h"

void Clock_Init(void)
{
    // Enable HSE
    RCC->CR |= (1 << 16);
    while (!(RCC->CR & (1 << 17)))
        ;

    // Flash latency
    FLASH->ACR |= (2 << 0);

    // PLL = HSE * 9 = 72MHz
    RCC->CFGR &= ~(1 << 16); // PLLSRC = HSE
    RCC->CFGR &= ~(1 << 17);
    RCC->CFGR |= (7 << 18); // PLL x9

    // APB1 = 36MHz
    RCC->CFGR |= (4 << 8); // /2

    // USB prescaler = 1.5 → 48MHz
    RCC->CFGR &= ~(1 << 22);

    // Enable PLL
    RCC->CR |= (1 << 24);
    while (!(RCC->CR & (1 << 25)))
        ;

    // Switch SYSCLK to PLL
    RCC->CFGR &= ~(3 << 0);
    RCC->CFGR |= (2 << 0);
    while (((RCC->CFGR >> 2) & 3) != 2)
        ;

    // Enable GPIOA, AFIO, USB
    RCC->APB2ENR |= (1 << 2);  // GPIOA
    RCC->APB2ENR |= (1 << 0);  // AFIO
    RCC->APB1ENR |= (1 << 23); // USB
}