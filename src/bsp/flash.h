#include "stm32f103xb.h"
#include "stdio.h"

void Flash_Unlock(void);
void Flash_ErasePage(uint32_t address);
void Flash_WriteHalfWord(uint32_t address, uint16_t data);