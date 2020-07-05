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

#include "undo.h"
#include "tmk_core/common/keycode.h"

undo_command_t g_undo_stack[MAX_UNDO] = { {0} };
int8_t g_undo_stack_index = 0;
undo_command_t g_new_undo_command;

bool can_undo(undo_command_t* undo_command) { return undo_command->changes[0].kind != NO_CHANGE;}

void undo_command_add_change(undo_command_t* undo_command, change_kind_t kind)
{
    if (undo_command->change_index >= MAX_CHANGES || kind == NO_CHANGE)
    {
        return;
    }

    change_t* current_change = &undo_command->changes[undo_command->change_index];
    if (current_change->kind == NO_CHANGE || current_change->kind == kind)
    {
        current_change->kind = kind;
        current_change->count++;
    }
    else
    {
        undo_command->change_index++;
        undo_command_add_change(undo_command, kind);
    }
}

change_kind_t undo_command_add_change_from_code(undo_command_t* undo_command, uint8_t code)
{
    change_kind_t kind = CHARACTER;
    switch (code)
    {
    case KC_END:
        {
            kind = NO_CHANGE;
            break;
        }
    case KC_ENT:
        {
            kind = ENTER;
            break;
        }
    case KC_LEFT:
        {
            kind = MOVE_LEFT;
            break;
        }
    case KC_UP:
        {
            kind = MOVE_UP;
            break;
        }
    }
    undo_command_add_change(undo_command, kind);
    return kind;
}

uint8_t undo_command_get_changes_count(undo_command_t* undo_command, change_kind_t kind)
{
    uint8_t result = 0;
    for (int i = 0; i < MAX_CHANGES; ++i)
    {
        change_kind_t change_kind = undo_command->changes[i].kind;
        if (change_kind == kind)
        {
            result += undo_command->changes[i].count;
        }
        else if (change_kind == NO_CHANGE)
        {
            break;
        }
    }
    return result;
}

