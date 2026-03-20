#ifndef BH1705_H
#define BH1705_H

#include <stdint.h>
#include "bsp/i2c.h"
#include "bsp/uart.h"
#define BH1705_ADDR 0x23

#define BH1705_POWER_DOWN 0x00
#define BH1705_POWER_ON 0x01
#define BH1705_RESET 0x07

#define BH1705_CONT_H_RES 0x10
#define BH1705_CONT_H_RES2 0x11
#define BH1705_CONT_L_RES 0x13

void BH1705_Init(void);

void BH1705_SetMode(uint8_t mode);
void BH1705_PowerDown(void);
uint16_t BH1705_ReadLux(void);

#endif