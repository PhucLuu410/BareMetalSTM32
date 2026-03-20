#include "iwdg.h"

void IWDG_Init(void)
{
    IWDG->KR = 0x5555; // unlock
    IWDG->PR = 6;      // prescaler = 256
    IWDG->RLR = 155;   // ~1s timeout
    IWDG->KR = 0xCCCC; // start watchdog
    IWDG->KR = 0xAAAA; // reload
}

void IWDG_Reset(void)
{
    IWDG->KR = 0xAAAA; // Reload the watchdog
}
