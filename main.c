/*
 * main.c
 *
 *  Created on: 5 θώνÿ 2017 γ.
 *      Author: RLeonov
 */

#include "board.h"
#include "config.h"

#if (DEBUG)
#include "dbg.h"
#endif // DFU_DEBUG

#define CLEAR_EXTI_IRQ_BIT(n)       (EXTI->PR |= (1 << n))
#define IS_EXTI_LINE(n)             (EXTI->PR & (1 << n))

void main()
{
    board_init();

#if (DEBUG)
    board_dbg_init();
    printf("exti example, v.%s, %s\n", __VERSION, __BUILD_TIME);
    printf("%s core, %d MHz\n", __MCU, power_get_core_clock() / 1000000);
#endif // DFU_DEBUG


    // enable blue LED
    gpio_enable(C7, GPIO_MODE_OUT);
    pin_set(C7);

    // setup PIN
    gpio_enable(A0, GPIO_MODE_IN_PULLDOWN);
    gpio_enable(A1, GPIO_MODE_IN_PULLDOWN);

    // enable EXTI
    pin_exti_enable(A0, EXTI_FLAGS_RISING);
    pin_exti_enable(A1, EXTI_FLAGS_RISING);

    // clear pending bit's
    CLEAR_EXTI_IRQ_BIT(0);
    CLEAR_EXTI_IRQ_BIT(1);

    NVIC_SetPriority(EXTI0_1_IRQn, 20);
    NVIC_EnableIRQ(EXTI0_1_IRQn);

    for(;;) { }
}


//IRQ Handlers
void EXTI0_1_IRQ_Handler(int *param)
{
    if(IS_EXTI_LINE(0))
    {
        *param = (*param) + 1;
        CLEAR_EXTI_IRQ_BIT(0);
    }

    if(IS_EXTI_LINE(1))
    {
        *param = (*param) - 1;
        CLEAR_EXTI_IRQ_BIT(1);
    }

#if (DEBUG)
    printf("Pulse count: %d\n", *param);
#endif // DFU_DEBUG
}
