#include "change_mode_button.h"

extern volatile uint32_t g_tick_ms;
extern volatile uint8_t button_event;

bool Change_Mode_Button_Press(void)
{
    if (button_event == 1)
    {
        button_event = 0;
        return true;
    }
    return false;
}

bool Reset(void)
{
    // return ResetIsPress();
    return 0;
}

bool EStop(void)
{
    // return EStopIsPress();
    return 0;
}