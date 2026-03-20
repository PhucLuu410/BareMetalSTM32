#include "bsp/bsp.h"

extern volatile uint32_t g_tick_ms;
volatile uint32_t last_tick = 0;

void Idle(void)
{
    for (int i = 0; i < 6; i++)
    {
        GPIO_ResetPin(i);
    }
}
void Mode1_Run(void)
{
    for (int i = 0; i < 6; i++)
    {
        GPIO_WritePin(i);
    }
}
void Mode2_Run(void)
{
    uint32_t phase = g_tick_ms % 1000;

    if (phase < 500)
    {
        GPIO_WritePin(1);
        GPIO_WritePin(3);
        GPIO_WritePin(5);

        GPIO_ResetPin(0);
        GPIO_ResetPin(2);
        GPIO_ResetPin(4);
    }
    else
    {
        GPIO_WritePin(0);
        GPIO_WritePin(2);
        GPIO_WritePin(4);

        GPIO_ResetPin(1);
        GPIO_ResetPin(3);
        GPIO_ResetPin(5);
    }
}
void Mode3_Run(void)
{
    uint32_t phase = g_tick_ms % 800;

    if (phase < 100)
    {
        GPIO_WritePin(0);
        GPIO_ResetPin(5);
    }
    else if (phase < 200)
    {
        GPIO_WritePin(1);
        GPIO_ResetPin(0);
    }
    else if (phase < 300)
    {
        GPIO_WritePin(2);
        GPIO_ResetPin(1);
    }
    else if (phase < 400)
    {
        GPIO_WritePin(3);
        GPIO_ResetPin(2);
    }
    else if (phase < 500)
    {
        GPIO_WritePin(4);
        GPIO_ResetPin(3);
    }
    else if (phase < 600)
    {
        GPIO_WritePin(5);
        GPIO_ResetPin(4);
    }
}
void Fault_Handler(void)
{
}