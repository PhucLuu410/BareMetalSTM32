#ifndef DS1307_H
#define DS1307_H

#include "bsp/i2c.h"
#include <stdint.h>

#define DS1307_ADDR 0x68

void DS1307_SetTime(uint8_t sec,
                    uint8_t min,
                    uint8_t hour,
                    uint8_t day,
                    uint8_t date,
                    uint8_t month,
                    uint8_t year);

void DS1307_GetTime(uint8_t *sec,
                    uint8_t *min,
                    uint8_t *hour,
                    uint8_t *day,
                    uint8_t *date,
                    uint8_t *month,
                    uint8_t *year);

uint8_t BCD_to_DEC(uint8_t bcd);
uint8_t DEC_to_BCD(uint8_t dec);

#endif