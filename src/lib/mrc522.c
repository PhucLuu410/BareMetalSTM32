#include "mrc522.h"
#include "bsp/spi.h"

/* ==== RC522 Register ==== */

#define CommandReg 0x01
#define ErrorReg 0x06
#define Status2Reg 0x08
#define FIFODataReg 0x09
#define FIFOLevelReg 0x0A
#define ControlReg 0x0C
#define BitFramingReg 0x0D
#define ModeReg 0x11
#define TxControlReg 0x14
#define CRCResultRegM 0x21
#define CRCResultRegL 0x22
#define TModeReg 0x2A
#define TPrescalerReg 0x2B
#define TReloadRegH 0x2C
#define TReloadRegL 0x2D

/* ===== Write Register ===== */

void RC522_WriteRegister(uint8_t addr, uint8_t val)
{
    SPI1_CS_Low();

    SPI1_TransmitReceive((addr << 1) & 0x7E);
    SPI1_TransmitReceive(val);

    SPI1_CS_High();
}

/* ===== Read Register ===== */

uint8_t RC522_ReadRegister(uint8_t addr)
{
    uint8_t val;

    SPI1_CS_Low();

    SPI1_TransmitReceive(((addr << 1) & 0x7E) | 0x80);
    val = SPI1_TransmitReceive(0x00);

    SPI1_CS_High();

    return val;
}

/* ===== Reset ===== */

void RC522_Reset(void)
{
    RC522_WriteRegister(CommandReg, 0x0F);
}

/* ===== Antenna ON ===== */

void RC522_AntennaOn(void)
{
    uint8_t temp;

    temp = RC522_ReadRegister(TxControlReg);

    if (!(temp & 0x03))
    {
        RC522_WriteRegister(TxControlReg, temp | 0x03);
    }
}

/* ===== Init ===== */

void RC522_Init(void)
{
    RC522_Reset();

    RC522_WriteRegister(TModeReg, 0x8D);
    RC522_WriteRegister(TPrescalerReg, 0x3E);
    RC522_WriteRegister(TReloadRegL, 30);
    RC522_WriteRegister(TReloadRegH, 0);

    RC522_WriteRegister(TxControlReg, 0x03);

    RC522_AntennaOn();
}

/* ===== Request Card ===== */

uint8_t RC522_Request(uint8_t *TagType)
{
    RC522_WriteRegister(BitFramingReg, 0x07);

    SPI1_CS_Low();

    SPI1_TransmitReceive(0x26);
    TagType[0] = SPI1_TransmitReceive(0x00);

    SPI1_CS_High();

    if (TagType[0] == 0x04)
        return RC522_OK;

    return RC522_ERROR;
}

/* ===== Anti Collision ===== */

uint8_t RC522_Anticoll(uint8_t *serNum)
{
    uint8_t i;

    SPI1_CS_Low();

    SPI1_TransmitReceive(0x93);
    SPI1_TransmitReceive(0x20);

    for (i = 0; i < 5; i++)
    {
        serNum[i] = SPI1_TransmitReceive(0x00);
    }

    SPI1_CS_High();

    return RC522_OK;
}