//if you've got error in this line, than this file is compiled wrong

#include "config.h"
#include "core.h"

/* Define constants used in low-level initialization.  */

    .equ   ICER0,                 0xe000e180
    .equ   ICPR0,                 0xe000e280

    .equ   SHPR1,                 0xe000ed18
    .equ   SHPR2,                 0xe000ed1c
    .equ   SHPR3,                 0xe000ed20
    .equ   SHPR1_VALUE,           ((0x00 << 0) | (0x00 << 8) | (0x00 << 16))
    .equ   SHPR2_VALUE,           (0xff << 24)
    .equ   SHPR3_VALUE,           (0xff << 16)

/* exported global constant and functions */
    .global delay_ms
    .global delay_us

    .extern main

/* interrupt vectors */
    .section  .isr_vectors, "ax"

int_vectors:
    .word  (SRAM_BASE + SRAM_SIZE)
    .word  Reset_Handler
    .word  NMI_Handler
    .word  HardFault_Handler
    .word  0
    .word  0
    .word  0
    .word  0
    .word  0
    .word  0
    .word  0
    .word  SVC_Handler
    .word  0
    .word  0
    .word  PendSV_Handler
    .word  SysTick_Handler

    .rept IRQ_VECTORS_COUNT
        .word  irq_handler
    .endr

/*********************** reset vector handler *********************/
    .section  .reset, "ax"
    .syntax unified
    .cpu cortex-m0
    .thumb

    .thumb_func
Reset_Handler:
    cpsid i

    bl    system_early_init

    @setup system and fault handlers priority
    ldr   r1, =SHPR2
    ldr   r0, =SHPR2_VALUE
    str   r0, [r1]

    ldr   r1, =SHPR3
    ldr   r0, =SHPR3_VALUE
    str   r0, [r1]

    @clear all pending interrupts
    ldr r1, =ICPR0
    str r0, [r1]

    @enable IRQ
    cpsie i
    @go to main
    bl       main
    @never reach
    b      .

    /* code segment */
    .section  .text, "ax"
    .syntax unified
    .thumb

    .thumb_func
delay_ms:
    ldr r1, =DELAY_COEF_MS
    muls    r0, r1

loop_ms:
    subs    r0, #1
    bge loop_ms

    bx      lr

    .thumb_func
delay_us:
    ldr r1, =DELAY_COEF_US
    muls    r0, r1

loop_us:
    subs    r0, #1
    bge loop_us

    bx      lr

/*********************** exception vectors handlers *********************/
.macro exception_enter
    mov   r0, lr
    movs  r1, #0
    subs  r1, r1, #3
    cmp   r0, r1
    bne   1f
    mrs   r1, psp
    b     2f
1:
    mrs   r1, msp
2:
.endm

    .thumb_func
HardFault_Handler:
    exception_enter
    b   on_hard_fault

    .thumb_func
irq_handler:
    mrs   r0, ipsr
    subs  r0, r0, #16
    b     irq_enter

/*********************** weak unhandled vectors *********************/
.macro weak_vector vector
    .weak   \vector
    .thumb_set \vector, default_handler
.endm

weak_vector   NMI_Handler
weak_vector   SVC_Handler
weak_vector   PendSV_Handler
weak_vector   SysTick_Handler
