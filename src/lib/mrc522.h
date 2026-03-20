#ifndef __MFRC522_H
#define __MFRC522_H

#include <stdint.h>
#include "stm32f103xb.h"
/* ===== RC522 Status ===== */

#define RC522_OK 0
#define RC522_ERROR 1
#define RC522_NOTAG 2

/* ===== Function ===== */

void RC522_Init(void);
void RC522_Reset(void);

uint8_t RC522_Request(uint8_t *TagType);
uint8_t RC522_Anticoll(uint8_t *serNum);

uint8_t RC522_ReadRegister(uint8_t addr);
void RC522_WriteRegister(uint8_t addr, uint8_t val);

#endif