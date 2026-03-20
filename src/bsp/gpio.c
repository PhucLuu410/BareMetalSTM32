#include "gpio.h"

volatile uint8_t button_event = 0;

void GPIO_Init(void)
{
    // LED PA0 -> PA5
    GPIOA->CRL &= ~(0xFFFFFF); // clear PA0 -> PA5
    GPIOA->CRL |= 0x222222;

    // UART
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |= (0xB << 4); // PA9

    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |= (0x4 << 8); // PA10

    // Button PB0
    GPIOB->CRL &= ~(0xF << 0);
    GPIOB->CRL |= (0x8 << 0);
    GPIOB->BSRR = (1 << 0); // pull-up

    // I2C
    GPIOB->CRL &= ~(0xF << 24);
    GPIOB->CRL |= (0xF << 24);

    GPIOB->CRL &= ~(0xF << 28);
    GPIOB->CRL |= (0xF << 28);

    // PB3 SCK
    GPIOB->CRL &= ~(0xF << 12);
    GPIOB->CRL |= (0xB << 12);

    // PB4 MISO
    GPIOB->CRL &= ~(0xF << 16);
    GPIOB->CRL |= (0x8 << 16);

    // PB5 MOSI
    GPIOB->CRL &= ~(0xF << 20);
    GPIOB->CRL |= (0xB << 20);

    // CS
    GPIOA->CRH &= ~(0xF << 28);
    GPIOA->CRH |= (0x3 << 28);

    GPIOA->BSRR = (1 << 15);
}

bool GPIO_ReadPin(uint8_t pin)
{
    return (GPIOB->IDR) & (1 << pin);
}

void GPIO_WritePin(uint8_t pin)
{
    GPIOA->ODR |= (1 << pin);
}

void GPIO_ResetPin(uint8_t pin)
{
    GPIOA->ODR &= ~(1 << pin);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & (1 << 0))
    {
        EXTI->PR = (1 << 0);
        button_event = 1;
    }
}