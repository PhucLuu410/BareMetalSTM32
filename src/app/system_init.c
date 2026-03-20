#include "system_init.h"

bool System_Init(void)
{
    Clock_Init();
    AFIO_Init();
    GPIO_Init();
    EXTI_Init();
    Timer_Init();
    UART_Init();
    I2C_Init();
    // IWDG_Init();
    SPI1_Init();

    return 1;
}