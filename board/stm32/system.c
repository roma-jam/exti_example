/*
 * system.c
 *
 *  Created on: 6 θώνÿ 2017 γ.
 *      Author: RLeonov
 */

#include "stm32/stm32.h"
#include "../board.h"
#include "../config.h"

#if (DEBUG)
#include "../dbg.h"
#endif

//HardFault Status Register
#define SCB_HFSR                                    (*(unsigned int*)0xE000ED2C)
#define HFSR_VECTTBL                                (1 << 1)

#define PSP_IN_LR                                   0xfffffffd
#define SVC_12                                      0xdf12
#define CALLER_ADDRESS                              6


int pulse_cnt; // This is GLOBAL pulse

void system_early_init()
{
    pulse_cnt = 0;

    // Nothing else to do
}

void on_hard_fault(unsigned int ret_value, unsigned int* stack_value)
{

#if (DEBUG)
    printf("HARD FAULT\n");
    if (SCB_HFSR & HFSR_VECTTBL)
        printf("Vector table read fault at %#.08x\n", stack_value[CALLER_ADDRESS]);
    //wrong sys call
    else if (*(uint16_t*)(stack_value[CALLER_ADDRESS] - 2) == SVC_12)
        printf("SYS call while disabled interrupts at %#.08x\n", stack_value[5] & 0xfffffffe);
    else
        printf("General hard fault at %#.08x\n", stack_value[CALLER_ADDRESS]);

    if (ret_value == PSP_IN_LR && (*(uint16_t*)(stack_value[CALLER_ADDRESS] - 2) == SVC_12))
        asm volatile ("cpsie i");
#endif // DEBUG

    while(1);
}

void on_mem_manage()
{
#if (DEBUG)
    printf("MEM FAULT\n");
#endif // DEBUG
    while(1);
}

void on_bus_fault()
{
#if (DEBUG)
    printf("BUS FAULT\n");
#endif // DEBUG
    while(1);
}

void on_usage_fault()
{
#if (DEBUG)
    printf("USAGE FAULT\n");
#endif // DEBUG
    while(1);
}

void default_handler()
{
#if (DEBUG)
    printf("Unmasked IRQ\n");
#endif // DEBUG
    while(1);
}

void irq_enter(int vector)
{
    // we need onle two interrupts for EXTI
    if(vector == EXTI0_1_IRQn)
    {
        EXTI0_1_IRQ_Handler(&pulse_cnt);
        return;
    }

#if (DEBUG)
    printf("IRQ %d not assigned\n", vector);
#endif // DEBUG
    while(1);
}
