#include "ds1307.h"

uint8_t BCD_to_DEC(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t DEC_to_BCD(uint8_t dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}

void DS1307_SetTime(uint8_t sec,
                    uint8_t min,
                    uint8_t hour,
                    uint8_t day,
                    uint8_t date,
                    uint8_t month,
                    uint8_t year)
{
    I2C_WriteReg(DS1307_ADDR << 1, 0x00, DEC_to_BCD(sec));
    I2C_WriteReg(DS1307_ADDR << 1, 0x01, DEC_to_BCD(min));
    I2C_WriteReg(DS1307_ADDR << 1, 0x02, DEC_to_BCD(hour));
    I2C_WriteReg(DS1307_ADDR << 1, 0x03, DEC_to_BCD(day));
    I2C_WriteReg(DS1307_ADDR << 1, 0x04, DEC_to_BCD(date));
    I2C_WriteReg(DS1307_ADDR << 1, 0x05, DEC_to_BCD(month));
    I2C_WriteReg(DS1307_ADDR << 1, 0x06, DEC_to_BCD(year));
}

void DS1307_GetTime(uint8_t *sec,
                    uint8_t *min,
                    uint8_t *hour,
                    uint8_t *day,
                    uint8_t *date,
                    uint8_t *month,
                    uint8_t *year)
{
    *sec = BCD_to_DEC(I2C_ReadReg(DS1307_ADDR << 1, 0x00));
    *min = BCD_to_DEC(I2C_ReadReg(DS1307_ADDR << 1, 0x01));
    *hour = BCD_to_DEC(I2C_ReadReg(DS1307_ADDR << 1, 0x02));
    *day = BCD_to_DEC(I2C_ReadReg(DS1307_ADDR << 1, 0x03));
    *date = BCD_to_DEC(I2C_ReadReg(DS1307_ADDR << 1, 0x04));
    *month = BCD_to_DEC(I2C_ReadReg(DS1307_ADDR << 1, 0x05));
    *year = BCD_to_DEC(I2C_ReadReg(DS1307_ADDR << 1, 0x06));
}