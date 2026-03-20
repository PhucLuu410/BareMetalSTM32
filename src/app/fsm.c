#include "fsm.h"

volatile uint8_t Init_Flag = 0;
volatile uint8_t Reset_Flag = 0;
volatile uint8_t EStop_Flag = 0;

SystemEvent GetEvent(void)
{
    if (EStop())
    {
        return EVENT_ESTOP;
    }

    if (Reset())
    {
        Init_Flag = 0;
        return EVENT_RESET;
    }

    if (Init_Flag == 0)
    {
        Init_Flag = 1;
        return EVENT_INITIALIZE;
    }

    if (Change_Mode_Button_Press())
    {
        return EVENT_CHANGE_MODE_BUTTON_PRESS;
    }

    else
    {
        return EVENT_NONE;
    }
}

SystemState ChangeState(SystemState state, SystemEvent event)
{
    switch (state)
    {
    case STATE_INIT:
        if (event == EVENT_INITIALIZE)
        {
            return STATE_IDLE;
        }
        break;

    case STATE_IDLE:
        if (event == EVENT_CHANGE_MODE_BUTTON_PRESS)
        {
            return STATE_MODE1;
        }
        if (event == EVENT_ESTOP)
        {
            return STATE_FAULT;
        }
        break;

    case STATE_MODE1:
        if (event == EVENT_ESTOP)
        {
            return STATE_FAULT;
        }
        if (event == EVENT_RESET)
        {
            return STATE_IDLE;
        }
        if (event == EVENT_CHANGE_MODE_BUTTON_PRESS)
        {
            return STATE_MODE2;
        }
        break;

    case STATE_MODE2:
        if (event == EVENT_ESTOP)
        {
            return STATE_FAULT;
        }
        if (event == EVENT_RESET)
        {
            return STATE_IDLE;
        }
        if (event == EVENT_CHANGE_MODE_BUTTON_PRESS)
        {
            return STATE_MODE3;
        }
        break;

    case STATE_MODE3:
        if (event == EVENT_ESTOP)
        {
            return STATE_FAULT;
        }
        if (event == EVENT_RESET)
        {
            return STATE_IDLE;
        }
        if (event == EVENT_CHANGE_MODE_BUTTON_PRESS)
        {
            return STATE_IDLE;
        }
        break;

    case STATE_FAULT:
    {
        if (event == EVENT_RESET)
        {
            return STATE_IDLE;
        }
        break;
    }

    default:
        break;
    }
    return state;
}

void Executed(SystemState state, SystemEvent event)
{
    if (event == EVENT_ESTOP)
    {
        EStop();
        return;
    }
    switch (state)
    {
    case STATE_INIT:
        System_Init();
        break;

    case STATE_IDLE:
        Idle();
        break;

    case STATE_MODE1:
        Mode1_Run();
        break;

    case STATE_MODE2:
        Mode2_Run();
        break;

    case STATE_MODE3:
        Mode3_Run();
        break;

    case STATE_FAULT:
        Fault_Handler();
        break;

    default:
        break;
    }
}