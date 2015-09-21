/******************************************************************************
 * configs/bsc/src/bsc_stm32f107.h
 *
 *   Copyright (C) 2013-2014 Gregory Nutt. All rights reserved.
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
 ******************************************************************************/

#ifndef __CONFIGS_BSC_STM32F107_SRC_INTERNAL_H
#define __CONFIGS_BSC_STM32F107_SRC_INTERNAL_H

/******************************************************************************
 * Included Files
 ******************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>
#include <stdint.h>

/******************************************************************************
 * Pre-processor Definitions
 ******************************************************************************/
/* Configuration **************************************************************/
/* Assume that everything is supported */

#define HAVE_USBDEV   1
#define HAVE_MMCSD    1

/* Handle chip differences */

#if defined(CONFIG_ARCH_CHIP_STM32F103VC)
#  undef CONFIG_STM32_OTGFS
#elif defined(CONFIG_ARCH_CHIP_STM32F107VC)
#  undef CONFIG_STM32_USB
#  undef CONFIG_STM32_SDIO
#else
#  error Unknown chip on Viewtool board
#  undef HAVE_USBDEV
#  undef HAVE_MMCSD
#endif

/* Check if USB is enabled */

#if !defined(CONFIG_STM32_OTGFS) && !defined(CONFIG_STM32_USB)
#  undef HAVE_USBDEV
#elif !defined(CONFIG_USBDEV)
#  warning CONFIG_STM32_OTGFS (F107) or CONFIG_STM32_USB (F103) is enabled but CONFIG_USBDEV is not
#  undef HAVE_USB
#endif

/* Can't support MMC/SD features if the SDIO peripheral is disabled */

#ifndef CONFIG_STM32_SDIO
#  undef HAVE_MMCSD
#endif

/* Can't support MMC/SD features if mountpoints are disabled */

#ifdef CONFIG_DISABLE_MOUNTPOINT
#  undef HAVE_MMCSD
#endif

/* Default MMC/SD slot number/device minor number */

#define BSC_MMCSD_SLOTNO 0

/* GPIO Configuration *********************************************************/

/*
 * LEDs
 */

#define GPIO_LED4       (GPIO_OUTPUT | GPIO_CNF_OUTPP | GPIO_MODE_50MHz|\
                         GPIO_OUTPUT_SET | GPIO_PORTC | GPIO_PIN8)

/*
 * Buttons
 */

#define MIN_IRQBUTTON   BUTTON_SW8
#define MAX_IRQBUTTON   BUTTON_SW8
#define NUM_IRQBUTTONS  1

#define GPIO_SW8        (GPIO_INPUT | GPIO_CNF_INFLOAT | GPIO_MODE_INPUT | \
                         GPIO_EXTI | GPIO_PORTC | GPIO_PIN7)

/* Relays
 */

#define NUM_RELAYS      6

#define GPIO_RELAYS_R01 (GPIO_OUTPUT|GPIO_CNF_OUTPP|GPIO_MODE_50MHz|\
                         GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN0)
#define GPIO_RELAYS_R02 (GPIO_OUTPUT|GPIO_CNF_OUTPP|GPIO_MODE_50MHz|\
                         GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN3)
#define GPIO_RELAYS_R03 (GPIO_OUTPUT|GPIO_CNF_OUTPP|GPIO_MODE_50MHz|\
                         GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN4)
#define GPIO_RELAYS_R04 (GPIO_OUTPUT|GPIO_CNF_OUTPP|GPIO_MODE_50MHz|\
                         GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN5)
#define GPIO_RELAYS_R05 (GPIO_OUTPUT|GPIO_CNF_OUTPP|GPIO_MODE_50MHz|\
                         GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN6)
#define GPIO_RELAYS_R06 (GPIO_OUTPUT|GPIO_CNF_OUTPP|GPIO_MODE_50MHz|\
                         GPIO_OUTPUT_SET|GPIO_PORTA|GPIO_PIN15)

/************************************************************************************
 * Public Functions
 ************************************************************************************/

#ifndef __ASSEMBLY__

/************************************************************************************
 * Name: stm32_spiinitialize
 *
 * Description:
 *   Called to configure SPI chip select GPIO pins for the M3 Wildfire board.
 *
 ************************************************************************************/

void weak_function stm32_spiinitialize(void);

/************************************************************************************
 * Name: stm32_usbdev_initialize
 *
 * Description:
 *   Called from stm32_usbdev_initialize very early in initialization to setup USB-related
 *   GPIO pins for the Viewtool STM32F107 board.
 *
 ************************************************************************************/

#if defined(CONFIG_STM32_OTGFS) && defined(CONFIG_USBDEV)
void weak_function stm32_usbdev_initialize(void);
#endif

/************************************************************************************
 * Name: stm32_sdinitialize
 *
 * Description:
 *   Initialize the SPI-based SD card.  Requires CONFIG_DISABLE_MOUNTPOINT=n
 *   and CONFIG_STM32_SPI1=y
 *
 ************************************************************************************/

int stm32_sdinitialize(int minor);

/************************************************************************************
 * Name: stm32_mpl115ainitialize
 *
 * Description:
 *   Initialize and register the MPL115A Pressure Sensor driver.
 *
 * Input parameters:
 *   devpath - The full path to the driver to register. E.g., "/dev/press0"
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ************************************************************************************/

#if defined(CONFIG_SPI) && defined(CONFIG_MPL115A) && defined(CONFIG_STM32_SPI3)
int stm32_mpl115ainitialize(FAR const char *devpath);
#endif

int stm32_adc_initialize(void);
int board_app_initialize(void);

#endif  /* __ASSEMBLY__ */
#endif /* __CONFIGS_BSC_STM32F107_SRC_INTERNAL_H */
