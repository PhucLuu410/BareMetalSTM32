#ifndef RTOS_H
#define RTOS_H

#include "stm32f103xb.h"

#define MAX_TASKS 5
#define STACK_SIZE 256
#define STACK_ADDRESS 0x20005000

typedef struct
{
    uint32_t *stack_pointer;
} TaskControlBlock;

extern TaskControlBlock tasks[MAX_TASKS];
extern uint32_t current_task;
extern uint8_t Task_Count;

void RTOS_Init(void);
uint32_t *Task_Init(uint32_t *sp, void (*task_func)(void));
void Task_Create(void (*task_func)(void));
void Scheduler(void);
void RTOS_Yield(void);

#endif