/*
 * board.h
 *
 *  Created on: 5 θώνÿ 2017 γ.
 *      Author: RLeonov
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <stdbool.h>

#include "stm32/stm32.h"

#if defined(STM32)
#include "board/stm32/stm32_pin.h"
#include "board/stm32/stm32_power.h"
#endif

// ------------------------------ EXTI Handler -----------------------------------------
// For EXTI Purpose
extern void EXTI0_1_IRQ_Handler(int *param);

//main
extern void board_init();
extern void board_reset();

//dbg
extern void board_dbg_init();
extern void board_dbg(const char *const buf, unsigned int size);

//delay
extern void delay_us(unsigned int us);
extern void delay_ms(unsigned int ms);

#endif /* BOARD_H_ */
