#include "i2c.h"

void I2C_Init(void)
{
    I2C1->CR1 |= (1 << 15); // SWRST
    I2C1->CR1 &= ~(1 << 15);

    I2C1->CR2 = 8;  // APB1 = 8MHz
    I2C1->CCR = 40; // 100kHz
    I2C1->TRISE = 9;

    I2C1->CR1 |= (1 << 0); // PE enable
}

void I2C_Start(void)
{
    I2C1->CR1 |= (1 << 8);

    while (!(I2C1->SR1 & (1 << 0)))
        ;
}

void I2C_Stop(void)
{
    I2C1->CR1 |= (1 << 9);
}

void I2C_Address(uint8_t addr)
{
    volatile uint32_t temp;

    I2C1->DR = addr;

    while (!(I2C1->SR1 & (1 << 1)))
        ;

    temp = I2C1->SR1;
    temp = I2C1->SR2;
}

void I2C_WriteByte(uint8_t addr, uint8_t data, uint8_t size)
{
    I2C_Start();

    I2C_Address(addr & ~1);
    for (int i = 0; i < size; i++)
    {
        while (!(I2C1->SR1 & (1 << 7)))
            ;

        I2C1->DR = data;

        while (!(I2C1->SR1 & (1 << 2)))
            ;
    }

    I2C_Stop();
}

void I2C_ReadByte(uint8_t addr, uint8_t size, uint8_t *data)
{
    volatile uint32_t temp;

    I2C1->CR1 |= (1 << 10); // ACK

    I2C_Start();

    I2C_Address(addr | 1);

    for (int i = 0; i < size - 1; i++)
    {
        while (!(I2C1->SR1 & (1 << 6)))
            ;

        *data = I2C1->DR;
        data++;
    }
    I2C_Stop();
}

void I2C_WriteReg(uint8_t addr, uint8_t reg, uint8_t data)
{
    I2C_Start();

    I2C_Address(addr & ~1);

    while (!(I2C1->SR1 & (1 << 7)))
        ;
    I2C1->DR = reg;

    while (!(I2C1->SR1 & (1 << 7)))
        ;
    I2C1->DR = data;

    while (!(I2C1->SR1 & (1 << 2)))
        ;

    I2C_Stop();
}

uint8_t I2C_ReadReg(uint8_t addr, uint8_t reg)
{
    uint8_t data;

    I2C_Start();

    I2C_Address(addr & ~1);

    while (!(I2C1->SR1 & (1 << 7)))
        ;
    I2C1->DR = reg;

    I2C_Start();

    I2C_Address(addr | 1);

    while (!(I2C1->SR1 & (1 << 6)))
        ;
    data = I2C1->DR;

    I2C_Stop();

    return data;
}
