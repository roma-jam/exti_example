/*
 * board.c
 *
 *  Created on: 5 ���� 2017 �.
 *      Author: RLeonov
 */

#include "stm32/stm32.h"
#include "stm32_power.h"

void board_init()
{
    power_init();
//    flash_init();
}

void board_reset()
{
    NVIC_SystemReset();
}
