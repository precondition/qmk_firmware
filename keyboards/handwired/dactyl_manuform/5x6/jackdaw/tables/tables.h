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
#include <stdint.h>
#include <stdbool.h>

// Keys family
enum key_family
{
    FAMILY_SPECIAL_CONTROLS,
    FAMILY_LEFT_CONTROLS,
    FAMILY_LEFT_HAND,
    FAMILY_THUMBS,
    FAMILY_RIGHT_HAND,
    FAMILY_RIGHT_PINKY,
    FAMILY_RIGHT_CONTROLS,
    FAMILY_SPACES,
    NB_FAMILY
};

extern const uint8_t g_family_to_bit_offset[NB_FAMILY];
extern table_t g_tables[NB_FAMILY];
