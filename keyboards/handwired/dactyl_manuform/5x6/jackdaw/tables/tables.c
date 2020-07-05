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

#include "tables.h"
#include "table.h"
#include "../keycodes.h"
#include "shelton_tables.h"
#include "user_tables.h"

// Table to convert family id to bit offset
const uint8_t g_family_to_bit_offset[NB_FAMILY] =
{
    OFFSET_SPECIAL_CONTROLS,
    OFFSET_LEFT_CONTROLS,
    OFFSET_LEFT_HAND,
    OFFSET_THUMBS,
    OFFSET_RIGHT_HAND,
    OFFSET_RIGHT_PINKY,
    OFFSET_RIGHT_CONTROLS,
    OFFSET_SPACE_CONTROLS
};

table_t g_tables[NB_FAMILY] =
{
    {
        0,
        0,
        KIND_UNKNOWN,
    },
    {
        (void*)g_left_controls_table,
        MAX_ONE_KEYCODE,
        KIND_ONE_KEYCODE,
    },
    {
        (void*)g_left_hand_table,
        MAX_LETTERS,
        KIND_LETTERS,
    },
    {
        (void*)g_thumbs_table,
        MAX_VOWELS,
        KIND_LETTERS,
    },
    {
        (void*)g_right_hand_table,
        MAX_LETTERS,
        KIND_LETTERS,
    },
    {
        (void*)g_right_pinky_table,
        2,
        KIND_LETTERS,
    },
    {
        (void*)g_right_controls_table,
        MAX_SYMBOLS,
        KIND_SYMBOLS,
    },
    {
        (void*)g_spaces_ctl_table,
        1,
        KIND_SYMBOLS,
    },
};
