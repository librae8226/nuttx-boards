/****************************************************************************
 * configs/arduino-due/src/sam_autoleds.c
 *
 *   Copyright (C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <debug.h>

#include <arch/board/board.h>

#include "chip.h"
#include "sam_gpio.h"
#include "arduino-due.h"

#ifdef CONFIG_ARCH_LEDS

/****************************************************************************
 * Definitions
 ****************************************************************************/
/*   There are two user-controllable LEDs on board the Arduino Due board:
 *
 *     LED              GPIO
 *     ---------------- -----
 *     TX  Yellow LED   PA21
 *     RX  Yellow LED   PC30
 *
 * Both are pulled high and can be illuminated by driving the corresponding
 * GPIO output to low.
 *
 * These LEDs are not used by the board port unless CONFIG_ARCH_LEDS is
 * defined.  In that case, the usage by the board port is defined in
 * include/board.h and src/sam_leds.c. The LEDs are used to encode OS-related
 * events as follows:
 *
 *   SYMBOL                Meaning                     LED state
 *                                                   RX       TX
 *   -------------------  -----------------------  -------- --------
 *   LED_STARTED          NuttX has been started     OFF      OFF
 *   LED_HEAPALLOCATE     Heap has been allocated    OFF      OFF
 *   LED_IRQSENABLED      Interrupts enabled         OFF      OFF
 *   LED_STACKCREATED     Idle stack created         ON       OFF
 *   LED_INIRQ            In an interrupt              No change
 *   LED_SIGNAL           In a signal handler          No change
 *   LED_ASSERTION        An assertion failed          No change
 *   LED_PANIC            The system has crashed     OFF      Blinking
 *   LED_IDLE             MCU is is sleep mode         Not used
 *
 * Thus if RX is statically on, NuttX has successfully booted and is,
 * apparently, running normmally.  If TX is flashing at approximately
 * 2Hz, then a fatal error has been detected and the system has halted.
 */

/* CONFIG_DEBUG_LEDS enables debug output from this file (needs CONFIG_DEBUG
 * with CONFIG_DEBUG_VERBOSE too)
 */

#ifdef CONFIG_DEBUG_LEDS
#  define leddbg  lldbg
#  define ledvdbg llvdbg
#else
#  define leddbg(x...)
#  define ledvdbg(x...)
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: up_ledinit
 ****************************************************************************/

void up_ledinit(void)
{
  /* Configure RX and TX LED GPIOs for output */

  sam_configgpio(GPIO_LED_RX);
  sam_configgpio(GPIO_LED_TX);
}

/****************************************************************************
 * Name: up_ledon
 ****************************************************************************/

void up_ledon(int led)
{
  bool rxledon = false;
  bool txledon = false;

  switch (led)
    {
      case 0:  /* LED_STARTED, LED_HEAPALLOCATE, LED_IRQSENABLED */
        break;

      case 1:  /* LED_STACKCREATED */
        rxledon = true;
        break;

      default:
      case 2:  /* LED_INIRQ, LED_SIGNAL, LED_ASSERTION */
        return;

      case 3:  /* LED_PANIC */
        txledon = true;
        break;
    }

  sam_gpiowrite(GPIO_LED_RX, rxledon);
  sam_gpiowrite(GPIO_LED_TX, txledon);
}

/****************************************************************************
 * Name: up_ledoff
 ****************************************************************************/

void up_ledoff(int led)
{
  if (led != 2)
    {
      sam_gpiowrite(GPIO_LED_RX, false);
      sam_gpiowrite(GPIO_LED_TX, false);
    }
}

#endif /* CONFIG_ARCH_LEDS */
