/* Copyright 2018 FromtonRouge
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "table.h"
#include "../keycodes.h"
#include "tmk_core/common/progmem.h"
#include <stdint.h>

extern const uint16_t PROGMEM g_left_controls_table[64][MAX_ONE_KEYCODE];
extern const uint16_t PROGMEM g_right_controls_table[32][MAX_SYMBOLS];
extern const uint16_t PROGMEM g_left_punctuation_table[256][MAX_PUNCTUATION];
extern const uint16_t PROGMEM g_right_punctuation_table[256][MAX_PUNCTUATION];
extern const uint16_t PROGMEM g_spaces_ctl_table[2][1];
