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

#include "tables/tables.h"
#include "tables/table.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    kind_table_t kind;
    uint16_t keycode;
} stroke_element_t;

bool is_letter(uint8_t code);
void send_mods_and_code(uint8_t mods, uint8_t code);
bool can_stroke(void);
void stroke_init_buffer(void);
void stroke_add_element(kind_table_t kind, uint16_t keycode);
void stroke(void);

#define MAX_STROKE_BUFFER 64

extern stroke_element_t g_stroke_buffer[MAX_STROKE_BUFFER];
extern uint8_t g_stroke_buffer_count;
extern uint32_t g_bits_keys_pressed_part1;
extern uint32_t g_bits_keys_pressed_part2;
extern uint16_t g_separator_mode;
extern uint16_t g_case_mode;
extern uint8_t g_family_bits[NB_FAMILY];
extern uint32_t* g_family_to_keys_pressed[NB_FAMILY];
