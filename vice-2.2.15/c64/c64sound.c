/*
 * c64sound.c - C64/C128 sound emulation.
 *
 * Written by
 *  Marco van den Heuvel <blackystardust68@yahoo.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#include <stdio.h>
#include <string.h>

#include "digimax.h"
#include "machine.h"
#include "sfx_soundexpander.h"
#include "sfx_soundsampler.h"
#include "sid.h"
#include "sound.h"
#include "types.h"

int machine_sid2_check_range(unsigned int sid2_adr)
{
    if (machine_class == VICE_MACHINE_C128) {
        if (sid2_adr >= 0xd420 && sid2_adr <= 0xd4e0) {
            return 0;
        }

        if (sid2_adr >= 0xd700 && sid2_adr <= 0xd7e0) {
            return 0;
        }
    } else {
        if (sid2_adr >= 0xd420 && sid2_adr <= 0xd7e0) {
            return 0;
        }
    }

    if (sid2_adr >= 0xde00 && sid2_adr <= 0xdfe0) {
        return 0;
    }

    return -1;
}

sound_t *sound_machine_open(int chipno)
{
    return sid_sound_machine_open(chipno);
}

int sound_machine_init(sound_t *psid, int speed, int cycles_per_sec)
{
    digimax_sound_machine_init(psid, speed, cycles_per_sec);
    sfx_soundexpander_sound_machine_init(psid, speed, cycles_per_sec);
    sfx_soundsampler_sound_machine_init(psid, speed, cycles_per_sec);

    return sid_sound_machine_init(psid, speed, cycles_per_sec);
}

void sound_machine_close(sound_t *psid)
{
    sfx_soundexpander_sound_machine_close(psid);
    sid_sound_machine_close(psid);
}

/* for read/store 0x00 <= addr <= 0x1f is the sid
 *                0x20 <= addr <= 0x3f is the digimax
 *                0x40 <= addr <= 0x5f is the SFX sound sampler
 *                0x60 <= addr <= 0x7f is the SFX sound expander
 *
 * future sound devices will be able to use 0x80 and up
 */

BYTE sound_machine_read(sound_t *psid, WORD addr)
{
    if (addr >= 0x20 && addr <= 0x3f) {
        return digimax_sound_machine_read(psid, (WORD)(addr - 0x20));
    }

    if (addr >= 0x40 && addr <= 0x5f) {
        return sfx_soundsampler_sound_machine_read(psid, (WORD)(addr - 0x40));
    }

    if (addr >= 0x60 && addr <= 0x7f) {
        return sfx_soundexpander_sound_machine_read(psid, (WORD)(addr - 0x40));
    }

    return sid_sound_machine_read(psid, addr);
}

void sound_machine_store(sound_t *psid, WORD addr, BYTE byte)
{
    if (addr >= 0x20 && addr <= 0x3f) {
        digimax_sound_machine_store(psid, (WORD)(addr - 0x20), byte);
    }

    if (addr >= 0x40 && addr <= 0x5f) {
        sfx_soundsampler_sound_machine_store(psid, (WORD)(addr - 0x40), byte);
    }

    if (addr >= 0x60 && addr <= 0x7f) {
        sfx_soundexpander_sound_machine_store(psid, (WORD)(addr - 0x60), byte);
    }

    sid_sound_machine_store(psid, addr, byte);
}

void sound_machine_reset(sound_t *psid, CLOCK cpu_clk)
{
    digimax_sound_reset();
    sfx_soundexpander_sound_reset();
    sfx_soundsampler_sound_reset();
    sid_sound_machine_reset(psid, cpu_clk);
}

int sound_machine_calculate_samples(sound_t *psid, SWORD *pbuf, int nr, int interleave, int *delta_t)
{
    int temp;

    temp=sid_sound_machine_calculate_samples(psid, pbuf, nr, interleave, delta_t);
    digimax_sound_machine_calculate_samples(psid, pbuf, nr, interleave, delta_t);
    sfx_soundexpander_sound_machine_calculate_samples(psid, pbuf, nr, interleave, delta_t);
    sfx_soundsampler_sound_machine_calculate_samples(psid, pbuf, nr, interleave, delta_t);

    return temp;
}

void sound_machine_prevent_clk_overflow(sound_t *psid, CLOCK sub)
{
    sid_sound_machine_prevent_clk_overflow(psid, sub);
}

char *sound_machine_dump_state(sound_t *psid)
{
    return sid_sound_machine_dump_state(psid);
}

int sound_machine_cycle_based(void)
{
    return sid_sound_machine_cycle_based();
}

int sound_machine_channels(void)
{
    return sid_sound_machine_channels();
}

void sound_machine_enable(int enable)
{
    sid_sound_machine_enable(enable);
}
