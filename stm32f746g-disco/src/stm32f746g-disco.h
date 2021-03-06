/****************************************************************************************************
 * configs/stm32f746g-disco/src/stm32f746g-disco.h
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Authors: Gregory Nutt <gnutt@nuttx.org>
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
 ****************************************************************************************************/

#ifndef __CONFIGS_STM32F746G_DISCO_SRC_STM32F746G_DISCO__H
#define __CONFIGS_STM32F746G_DISCO_SRC_STM32F746G_DISCO__H

/****************************************************************************************************
 * Included Files
 ****************************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

/****************************************************************************************************
 * Pre-processor Definitions
 ****************************************************************************************************/
/* STM32F736G Discovery GPIOs ***********************************************************************/
/* The STM32F746G-DISCO board has numerous LEDs but only one, LD1 located near the reset button, that
 * can be controlled by software (LD2 is a power indicator, LD3-6 indicate USB status, LD7 is
 * controlled by the ST-Link).
 *
 * LD1 is controlled by PI1 which is also the SPI2_SCK at the Arduino interface. One end of LD1 is
 * grounded so a high output on PI1 will illuminate the LED.
 */

#define GPIO_LD1        (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_SPEED_50MHz | \
                         GPIO_OUTPUT_CLEAR | GPIO_PORTI | GPIO_PIN1)

/* Pushbutton B1, labelled "User", is connected to GPIO PI11.  A high value will be sensed when the
 * button is depressed. Note that the EXTI interrupt is configured.
 */

#define GPIO_BTN_USER   (GPIO_INPUT | GPIO_FLOAT | GPIO_EXTI | GPIO_PORTI | GPIO_PIN11)

/****************************************************************************************************
 * Public data
 ****************************************************************************************************/

#ifndef __ASSEMBLY__

/****************************************************************************************************
 * Public Functions
 ****************************************************************************************************/

/****************************************************************************************************
 * Name: stm32_spiinitialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the stm32f746g-disco board.
 *
 ****************************************************************************************************/

void weak_function stm32_spiinitialize(void);

#endif /* __ASSEMBLY__ */
#endif /* __CONFIGS_STM32F746G_DISCO_SRC_STM32F746G_DISCO_H */

