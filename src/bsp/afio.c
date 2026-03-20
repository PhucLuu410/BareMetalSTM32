#include "afio.h"

void AFIO_Init(void)
{
    // Disable JTAG keep SWD
    AFIO->MAPR &= ~(7 << 24);
    AFIO->MAPR |= (2 << 24);

    // SPI1 remap
    AFIO->MAPR &= ~(1 << 0);
    AFIO->MAPR |= (1 << 0);

    // EXTI0 PB0
    AFIO->EXTICR[0] &= ~(0xF << 0);
    AFIO->EXTICR[0] |= (0x1 << 0);
}