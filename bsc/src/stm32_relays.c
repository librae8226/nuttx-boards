/****************************************************************************
 * configs/cloudctrl/src/stm32_relays.c
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *           Librae <librae@linkgo.io>
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
#include <unistd.h>
#include <debug.h>

#include <nuttx/arch.h>
#include <arch/board/board.h>

#include "bsc_stm32f107.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define RELAYS_MIN_RESET_TIME 5
#define RELAYS_RESET_MTIME 5
#define RELAYS_POWER_MTIME 50

/****************************************************************************
 * Private Data
 ****************************************************************************/

static uint32_t g_relays_stat = 0;

static const uint16_t g_relays[NUM_RELAYS] =
{
  GPIO_RELAYS_R01,
  GPIO_RELAYS_R02,
  GPIO_RELAYS_R03,
  GPIO_RELAYS_R04,
  GPIO_RELAYS_R05,
  GPIO_RELAYS_R06,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void relays_setstat(int relays,bool stat)
{
  if ((unsigned)relays < NUM_RELAYS)
    {
      stm32_configgpio(g_relays[relays]);
      stm32_gpiowrite(g_relays[relays], stat);
      if (!stat)
        {
          g_relays_stat &= ~(1 << relays);
        }
      else
        {
          g_relays_stat |= (1 << relays);
        }
    }
}

bool relays_getstat(int relays)
{
  if ((unsigned)relays < NUM_RELAYS)
    {
      return (g_relays_stat & (1 << relays)) != 0;
    }

  return false;
}

void relays_setstats(uint32_t relays_stat)
{
  int i;

  for (i = 0; i < NUM_RELAYS; i++)
    {
      relays_setstat(i, (relays_stat & (1<<i))!=0);
    }
}

uint32_t relays_getstats(void)
{
  return (uint32_t)g_relays_stat;
}

void relays_onoff(int relays, uint32_t mdelay)
{
  if ((unsigned)relays < NUM_RELAYS)
    {
      if (mdelay>0)
        {
          if (relays_getstat(relays))
            {
              relays_setstat(relays, false);
              usleep(RELAYS_MIN_RESET_TIME*1000*1000);
            }

          relays_setstat(relays,true);
          usleep(mdelay*100*1000);
          relays_setstat(relays, false);
        }
    }
}

void relays_onoffs(uint32_t relays_stat, uint32_t mdelay)
{
  int i;

  for (i = 0; i < NUM_RELAYS; i++)
    {
      relays_onoff(i, mdelay);
    }
}

void relays_resetmode(int relays)
{
  relays_onoff(relays, RELAYS_RESET_MTIME);
}

void relays_powermode(int relays)
{
  relays_onoff(relays, RELAYS_POWER_MTIME);
}

void relays_resetmodes(uint32_t relays_stat)
{
  relays_onoffs(relays_stat, RELAYS_RESET_MTIME);
}

void relays_powermodes(uint32_t relays_stat)
{
  relays_onoffs(relays_stat, RELAYS_POWER_MTIME);
}
