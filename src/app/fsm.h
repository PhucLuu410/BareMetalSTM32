#ifndef FSM_H
#define FSM_H

#include <stdio.h>
#include <stdbool.h>
#include "system_state.h"
#include "system_event.h"
#include "system_init.h"
#include "led_effect.h"
#include "change_mode_button.h"
#include "counting.h"

SystemEvent GetEvent(void);
SystemState ChangeState(SystemState state, SystemEvent event);
void Executed(SystemState state, SystemEvent event);

#endif