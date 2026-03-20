#include "rtos.h"
#include "uart.h"
#include <stdio.h>

uint8_t Task_Count = 0;
TaskControlBlock tasks[MAX_TASKS];
uint32_t current_task = 0;

void RTOS_Init(void)
{
    for (int i = 0; i < MAX_TASKS; i++)
    {
        uint32_t stack_top = STACK_ADDRESS - (i * STACK_SIZE);
        tasks[i].stack_pointer = (uint32_t *)stack_top;
    }
}

uint32_t *Task_Init(uint32_t *sp, void (*task_func)(void))
{
    *(--sp) = 0x01000000;          // xPSR
    *(--sp) = (uint32_t)task_func; // PC
    *(--sp) = 0xFFFFFFFD;          // LR (EXC_RETURN value)

    *(--sp) = 0x00000000; // R12
    *(--sp) = 0x00000000; // R3
    *(--sp) = 0x00000000; // R2
    *(--sp) = 0x00000000; // R1
    *(--sp) = 0x00000000; // R0

    // Now prepare software-saved registers R11..R4 so that
    // a subsequent LDMIA will restore them in the correct order.
    *(--sp) = 0x00000000; // R11
    *(--sp) = 0x00000000; // R10
    *(--sp) = 0x00000000; // R9
    *(--sp) = 0x00000000; // R8
    *(--sp) = 0x00000000; // R7
    *(--sp) = 0x00000000; // R6
    *(--sp) = 0x00000000; // R5
    *(--sp) = 0x00000000; // R4

    return sp;
}

void Task_Create(void (*task_func)(void))
{
    if (Task_Count >= MAX_TASKS)
        return;

    uint32_t *sp = tasks[Task_Count].stack_pointer;

    sp = Task_Init(sp, task_func);

    tasks[Task_Count].stack_pointer = sp;

    Task_Count++;
}

void RTOS_Yield(void)
{
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}