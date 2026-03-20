#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <stdio.h>
#include <stdbool.h>
#include "bsp/bsp.h"
#include "lib/ds1307.h"
#include "lib/bh1705.h"
#include "lib/mrc522.h"
bool System_Init(void);

#endif