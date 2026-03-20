#include <stm32f103xb.h>
#include "app/app.h"
#include "bsp/bsp.h"
extern volatile uint32_t g_tick_ms;

int main(void)
{
    System_Init();
    USB_Init();
    while (1)
    {
    }
}