#ifndef I2C_H
#define I2C_H

#include "stm32f103xb.h"
#include <stdio.h>

void I2C_Init(void);

void I2C_Address(uint8_t addr);

void I2C_WriteByte(uint8_t addr, uint8_t data, uint8_t size);

void I2C_ReadByte(uint8_t addr, uint8_t size, uint8_t *data);

void I2C_WriteReg(uint8_t addr, uint8_t reg, uint8_t data);

uint8_t I2C_ReadReg(uint8_t addr, uint8_t reg);
#endif