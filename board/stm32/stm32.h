/*
 * stm32.h
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: RLeonov
 */

/* truncated file for external demo */


#ifndef STM32_H_
#define STM32_H_


#if defined(STM32F072CB) || defined(STM32F072RB) || defined(STM32F072VB)
#define STM32F072xB
#endif

#if defined(STM32F072x8) || defined(STM32F072xB)
#define STM32F072
#define SRAM_SIZE           0x4000
#define UARTS_COUNT         4
#define IRQ_VECTORS_COUNT   32
#define I2C_COUNT           2
#endif

#if defined(STM32F071) || defined(STM32F072) || defined(STM32F078)
#define STM32F07x
#endif

#if defined(STM32F042) || defined(STM32F072)
#define STM32F0x2
#endif

#if defined(STM32F070xB) || defined(STM32F071xB) || defined(STM32F072xB) || defined(STM32F078xB) || defined(STM32F091xB)
#define FLASH_SIZE          0x20000
#endif

#if defined(STM32F0x0) || defined(STM32F0x1) || defined(STM32F0x2) || defined(STM32F0x8)
#define STM32F0
//All models have A, B, C, F
#define GPIO_COUNT          6
#endif

#if defined(STM32L0) || defined(STM32F0)
#define STM32
#ifndef CORTEX_M0
#define CORTEX_M0
#endif
#endif //STM32L0 || STM32F0

#if defined(STM32)
#ifndef FLASH_BASE
#define FLASH_BASE                0x08000000
#endif
#endif

#if !defined(LDS) && !defined(__ASSEMBLER__)

#if defined(STM32)

#undef SRAM_BASE
#undef FLASH_BASE

#include "stm32_config.h"

#if defined(STM32F0)
#include "stm32f0xx.h"
#endif

#endif //STM32
#endif //!defined(LDS) && !defined(__ASSEMBLER__)

#if !defined(STM32)
#error "STM32F072xB example only. Please, correct the MCU in makefile. (C) RL"
#endif


#endif /* STM32_H_ */
