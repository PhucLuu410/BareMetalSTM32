#ifndef COUNTING_H
#define COUNTING_H

#include <stdio.h>
#include "bsp/bsp.h"

extern volatile uint32_t g_tick_ms;

uint32_t GetTick(void);

#endif