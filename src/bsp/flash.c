#include "flash.h"

void Flash_Unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK)
    {
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

void Flash_ErasePage(uint32_t address)
{
    while (FLASH->SR & FLASH_SR_BSY)
        ; // flash free

    FLASH->CR |= FLASH_CR_PER;  // page erase
    FLASH->AR = address;        // addr
    FLASH->CR |= FLASH_CR_STRT; // start erase

    while (FLASH->SR & FLASH_SR_BSY)
        ; // wait until end

    FLASH->CR &= ~FLASH_CR_PER; // off erase
}

void Flash_WriteHalfWord(uint32_t address, uint16_t data)
{
    while (FLASH->SR & FLASH_SR_BSY)
        ; // wait until flash free

    FLASH->CR |= FLASH_CR_PG; // program mode

    *(volatile uint16_t *)address = data;

    while (FLASH->SR & FLASH_SR_BSY)
        ; // wait until end

    FLASH->CR &= ~FLASH_CR_PG; // off program mode
}