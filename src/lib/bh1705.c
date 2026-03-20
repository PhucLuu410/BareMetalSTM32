#include "bh1705.h"

static uint8_t mode = BH1705_CONT_H_RES;
extern volatile uint32_t g_tick_ms;
volatile uint32_t last_read_time = 0;
void BH1705_Init(void)
{
    I2C_WriteByte(BH1705_ADDR << 1, BH1705_POWER_ON, 1);
    BH1705_SetMode(mode);
}

void BH1705_SetMode(uint8_t mode)
{
    I2C_WriteByte(BH1705_ADDR << 1, mode, 1);
}

void BH1705_PowerDown(void)
{
    I2C_WriteByte(BH1705_ADDR << 1, BH1705_POWER_DOWN, 1);
}

uint16_t BH1705_ReadLux(void)
{
    uint16_t raw;
    uint8_t data[2];
    I2C_ReadByte((BH1705_ADDR << 1) | 1, 2, data);
    raw = (data[0] << 8) | data[1];
    return raw;
}