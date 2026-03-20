#include "spi.h"

void SPI1_Init(void)
{
    SPI1->CR1 = 0;

    SPI1->CR1 |= (1 << 2); // Master
    SPI1->CR1 |= (2 << 3); // Baudrate /8
    SPI1->CR1 |= (1 << 9); // SSM
    SPI1->CR1 |= (1 << 8); // SSI

    SPI1->CR1 &= ~(1 << 11); // 8bit
    SPI1->CR1 &= ~(1 << 1);  // CPOL
    SPI1->CR1 &= ~(1 << 0);  // CPHA

    SPI1->CR1 |= (1 << 6); // SPI enable
}

void SPI1_CS_Low(void)
{
    GPIOA->BRR = (1 << 15);
}

void SPI1_CS_High(void)
{
    GPIOA->BSRR = (1 << 15);
}

uint8_t SPI1_TransmitReceive(uint8_t data)
{

    while (!(SPI1->SR & (1 << 1)))
        ; // TXE

    SPI1->DR = data;

    while (!(SPI1->SR & (1 << 0)))
        ; // RXNE

    uint8_t rx = SPI1->DR;

    while (SPI1->SR & (1 << 7))
        ; // BSY

    return rx;
}
