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

#include <stdint.h>
#include <stdbool.h>

#define MAX_UNDO 100

typedef enum
{
    NO_CHANGE,
    CHARACTER,
    MOVE_LEFT,
    MOVE_UP,
    ENTER
} change_kind_t;

typedef struct
{
    change_kind_t kind  :4;
    uint8_t count       :6;
} change_t;

#define MAX_CHANGES 6

typedef struct 
{
    uint8_t change_index       :3;
    uint8_t previous_case_mode :3;
    uint8_t next_case_mode     :3;
    change_t changes[MAX_CHANGES];
} undo_command_t;

bool can_undo(undo_command_t* undo_command);
void undo_command_add_change(undo_command_t* undo_command, change_kind_t kind);
change_kind_t undo_command_add_change_from_code(undo_command_t* undo_command, uint8_t code);
uint8_t undo_command_get_changes_count(undo_command_t* undo_command, change_kind_t kind);

extern undo_command_t g_undo_stack[MAX_UNDO];
extern int8_t g_undo_stack_index;
extern undo_command_t g_new_undo_command; // Must be global for ErgoDox Infinity to avoid a lock between the two halves
