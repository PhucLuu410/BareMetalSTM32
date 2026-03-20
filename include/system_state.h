#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

typedef enum
{
    STATE_INIT,
    STATE_IDLE,
    STATE_MODE1,
    STATE_MODE2,
    STATE_MODE3,
    STATE_FAULT
} SystemState;

#endif