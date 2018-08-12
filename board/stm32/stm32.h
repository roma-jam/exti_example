/*
 * stm32.h
 *
 *  Created on: 12 февр. 2018 г.
 *      Author: RLeonov
 */

/* truncated file for external demo */


#ifndef STM32_H_
#define STM32_H_


#if defined(STM32L052C6) || defined(STM32L052C8) || defined(STM32L052K6) || defined(STM32L052K8) || defined(STM32L052R6) || defined(STM32L052R8) \
 || defined(STM32L052T6) || defined(STM32L052T8)
#define STM32L052xx
#endif

#if defined(STM32L051C8) || defined(STM32L051K8) || defined(STM32L051R8) || defined(STM32L051T8) \
 || defined(STM32L052C8) || defined(STM32L052K8) || defined(STM32L052R8) || defined(STM32L052T8) \
 || defined(STM32L053C8) || defined(STM32L053R8) || defined(STM32L062K8) || defined(STM32L063C8) \
 || defined(STM32L063R8)
#define FLASH_SIZE          0x10000
#endif

#if defined(STM32L051xx) || defined(STM32L052xx) || defined(STM32L053xx) || defined(STM32L061xx) || defined(STM32L062xx) || defined(STM32L063xx)
#define STM32L0
#define SRAM_SIZE           0x2000
#define GPIO_COUNT          3
#define UARTS_COUNT         2
#define DAC_CHANNELS_COUNT  1
#define SPI_COUNT           3
#define I2C_COUNT           2

#if defined(STM32L051xx) || defined(STM32L061xx)
#define IRQ_VECTORS_COUNT   30
#else
#define IRQ_VECTORS_COUNT   32
#endif

#endif


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
#if defined(STM32L0)
#include "stm32l0xx.h"
#endif

#endif //STM32
#endif //!defined(LDS) && !defined(__ASSEMBLER__)

#if !defined(STM32)
#error "STM32F072xB example only. Please, correct the MCU in makefile. (C) RL"
#endif


#endif /* STM32_H_ */
