/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Koji Kitayama
 * Portions copyrighted (c) 2021 Roland Winistoerfer
 * Copyright (c) 2022 Rafael Silva (@perigoso)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

#ifndef _RUSB2_RZ_H_
#define _RUSB2_RZ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "iodefine.h"

#define RUSB2_REG_BASE (0x000A0000)

TU_ATTR_ALWAYS_INLINE static inline rusb2_reg_t* RUSB2_REG(uint8_t rhport) {
  (void) rhport;
  return (rusb2_reg_t *) RUSB2_REG_BASE;
}


#define rusb2_is_highspeed_rhport(_p)  (false)
#define rusb2_is_highspeed_reg(_reg)   (false)

//--------------------------------------------------------------------+
//
//--------------------------------------------------------------------+


// Start/Stop MSTP TODO implement later
TU_ATTR_ALWAYS_INLINE static inline void rusb2_module_start(uint8_t rhport, bool start) {
  (void) rhport;
  (void) start;
}

TU_ATTR_ALWAYS_INLINE static inline void rusb2_int_enable(uint8_t rhport)
{
  // USB interrupts are on 73 and 74
  uint32_t const base_interrupt = 73;
  uint32_t const interrupt = base_interrupt + rhport;

  // Interrupt Set Enable register enables the interrupts that have a bit set in the written value
  volatile uint32_t* addr = (volatile uint32_t*)&INTC.ICDISER0;
  uint32_t mask = 1u << (interrupt & 0x1f);

  *(addr + (interrupt >> 5)) = mask;
}

TU_ATTR_ALWAYS_INLINE static inline void rusb2_int_disable(uint8_t rhport)
{
  // USB interrupts are on 73 and 74
  uint32_t const base_interrupt = 73;
  uint32_t const interrupt = base_interrupt + rhport;

  // Interrupt Clear Enable register disables the interrupts that have a bit set in the written value
  volatile uint32_t* addr = (volatile uint32_t*)&INTC.ICDISER0;
  uint32_t mask = 1u << (interrupt & 0x1f);

  *(addr + (interrupt >> 5)) = mask;
}

// MCU specific PHY init
TU_ATTR_ALWAYS_INLINE static inline void rusb2_phy_init(void)
{
  IR(USB0, USBI0) = 0;
}

#ifdef __cplusplus
}
#endif

#endif /* _RUSB2_RZ_H_ */
