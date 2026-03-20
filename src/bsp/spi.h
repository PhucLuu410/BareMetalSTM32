#include "stm32f103xb.h"
#include <stdio.h>
#include <stdbool.h>

void SPI1_Init(void);
uint8_t SPI1_TransmitReceive(uint8_t data);
void SPI1_CS_Low(void);
void SPI1_CS_High(void);