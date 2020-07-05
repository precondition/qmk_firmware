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

#include "stroke.h"
#include "undo.h"
#include "keycodes.h"
#include "tables/shelton_tables.h"
#include "tables/user_tables.h"
#include "tmk_core/common/keycode.h"
#include "tmk_core/common/action_util.h"
#include "tmk_core/common/action.h"
#include "quantum/keymap_extras/keymap_french.h"

stroke_element_t g_stroke_buffer[MAX_STROKE_BUFFER] = {{0}};
uint8_t g_stroke_buffer_count = 0;
uint32_t g_bits_keys_pressed_part1 = 0;
uint32_t g_bits_keys_pressed_part2 = 0;
uint16_t g_separator_mode = CKC_SEPMODE_SPC;
uint16_t g_case_mode = CKC_CASE_NORMAL;
uint8_t g_family_bits[NB_FAMILY] = {0};
uint32_t* g_family_to_keys_pressed[NB_FAMILY] = 
{
    &g_bits_keys_pressed_part1, // Special controls
    &g_bits_keys_pressed_part2, // Left controls
    &g_bits_keys_pressed_part1, // Left hand
    &g_bits_keys_pressed_part1, // Thumbs
    &g_bits_keys_pressed_part1, // Right hand
    &g_bits_keys_pressed_part1, // Right pinky
    &g_bits_keys_pressed_part2, // Right controls
    &g_bits_keys_pressed_part1  // Space ctl
};

// User separator data
typedef struct
{
    uint8_t bits;
    punctuation_table_t* table;
} separator_t;
separator_t g_user_separators[2] = {{0}}; // [0] = left hand bits, [1] = right hand bits

bool can_stroke(void) { return (g_bits_keys_pressed_part1 == 0) && (g_bits_keys_pressed_part2 == 0); }

bool is_letter(uint8_t code)
{
#ifdef AZERTY_OS_ENABLE
    return (code != FR_COMM) && (((code >= KC_A) && (code <= KC_Z)) || (code == FR_M));
#else
    return (code >= KC_A) && (code <= KC_Z);
#endif
}

void send_mods_and_code(uint8_t mods, uint8_t code)
{
    const uint8_t original_mods = get_mods();
    set_mods((mods & 0x10) ? (mods & 0x0F) << 4 : mods); // see tmk_core/common/action_code.h
    register_code(code);
    set_mods(original_mods);
}

void stroke_init_buffer(void)
{
    g_stroke_buffer_count = 0;
    for (uint8_t i = 0; i < MAX_STROKE_BUFFER; ++i)
    {
        g_stroke_buffer[i].kind = KIND_UNKNOWN;
        g_stroke_buffer[i].keycode = 0;
    }
}

void stroke_add_element(kind_table_t kind, uint16_t keycode)
{
    g_stroke_buffer[g_stroke_buffer_count].kind = kind;
    g_stroke_buffer[g_stroke_buffer_count].keycode = keycode;
    g_stroke_buffer_count++;
}

void stroke(void)
{
    // Init stroke buffer
    stroke_init_buffer();
    
    // Send characters for each key family
    const uint8_t original_mods = get_mods();
    del_mods(MOD_LSFT|MOD_RSFT);

    g_new_undo_command.change_index = 0;
    g_new_undo_command.previous_case_mode = g_case_mode - CKC_CASE_NORMAL + 1;
    g_new_undo_command.next_case_mode = 0;
    for (int i = 0; i < MAX_CHANGES; ++i)
    {
        g_new_undo_command.changes[i].kind = NO_CHANGE;
        g_new_undo_command.changes[i].count = 0;
    }

    // Compute the previous index and get the previous undo command
    int8_t previous_index = g_undo_stack_index - 1;
    if (previous_index < 0)
    {
        previous_index = MAX_UNDO - 1;
    }
    undo_command_t* previous_undo_command = &g_undo_stack[previous_index];

    // Get *, + and case controls info
    const uint8_t special_controls_bits = g_family_bits[FAMILY_SPECIAL_CONTROLS];
    const bool has_star = special_controls_bits & (1 << (SC_STAR & 0xF));
    const bool has_left_plus = special_controls_bits & (1 << (SC_LPLUS & 0xF));
    const bool has_right_plus = special_controls_bits & (1 << (SC_RPLUS & 0xF));
    const bool double_first_letter = (has_left_plus && !has_right_plus) || (has_right_plus && !has_left_plus);
    const bool has_separator = special_controls_bits & (1 << (SC_SEP & 0xF));
    const uint8_t thumbs_bits = g_family_bits[FAMILY_THUMBS];
    const bool choose_separator_mode = has_left_plus && has_right_plus && has_star;
    bool punctuation_mode = ((!thumbs_bits && has_star) && (g_family_bits[FAMILY_LEFT_HAND] || g_family_bits[FAMILY_RIGHT_HAND])) || choose_separator_mode;
    uint8_t* left_controls_bits = &g_family_bits[FAMILY_LEFT_CONTROLS];
    if (punctuation_mode)
    {
        // Get bits from right controls and put them in the left controls
        *left_controls_bits |= g_family_bits[FAMILY_RIGHT_CONTROLS];
        *left_controls_bits &= 0x7; // Keep the first 3 bits only
        g_family_bits[FAMILY_RIGHT_CONTROLS] = 0;
    }

    // Choose separator mode init
    if (choose_separator_mode)
    {
        if (*left_controls_bits)
        {
            *left_controls_bits |= STENO_KEY_BIT(L3);
        }
        g_user_separators[0].bits = 0;
        g_user_separators[0].table = g_left_punctuation_table;
        g_user_separators[1].bits = 0;
        g_user_separators[1].table = g_right_punctuation_table;
    }

    // Apply new case mode from the previous command if any
    if (previous_undo_command->next_case_mode)
    {
        g_case_mode = CKC_CASE_NORMAL + previous_undo_command->next_case_mode - 1;
    }

    // Build stroke (but we don't send it yet)
    bool undo_allowed = true;
    for (int family_id = 0; family_id < NB_FAMILY; ++family_id)
    {
        uint8_t family_bits = g_family_bits[family_id];
        if (family_bits == 0)
        {
            continue;
        }

        // Get the lookup table data
        const table_t* table = &g_tables[family_id];
        void* any_table = table->any_table;
        uint8_t kind = table->kind;
        uint8_t element_size = table->element_size;

        undo_allowed = family_id == FAMILY_SPECIAL_CONTROLS;
        if (family_id == FAMILY_THUMBS)
        {
            if (has_star)
            {
                any_table = (void*)g_thumbs_bigrams_table;
            }
            else if (has_right_plus && g_family_bits[FAMILY_LEFT_HAND] == 0 && g_family_bits[FAMILY_RIGHT_HAND] == 0)
            {
                g_case_mode = CKC_CASE_INNER_ONCE; // For 'I'
            }
        }
        else if (family_id == FAMILY_LEFT_HAND)
        {
            if (punctuation_mode)
            {
                any_table = (void*)g_left_punctuation_table;
                kind = KIND_PUNCTUATION;
                element_size = MAX_PUNCTUATION;
                
                if (choose_separator_mode)
                {
                    g_user_separators[0].bits = family_bits;
                    any_table = 0;
                }
            }
        }
        else if (family_id == FAMILY_RIGHT_HAND)
        {
            if (punctuation_mode)
            {
                any_table = (void*)g_right_punctuation_table;
                kind = KIND_PUNCTUATION;
                element_size = MAX_PUNCTUATION;

                if (choose_separator_mode)
                {
                    g_user_separators[1].bits = family_bits;
                    any_table = 0;
                }
            }
        }

        if (any_table)
        {
            switch (kind)
            {
            case KIND_LETTERS:
                {
                    uint8_t (*byte_table)[element_size] = (uint8_t (*)[element_size])any_table;
                    for (int code_pos = 0; code_pos < element_size; ++code_pos)
                    {
                        uint8_t byte = pgm_read_byte(&(byte_table[family_bits][code_pos]));
                        if (byte)
                        {
                            stroke_add_element(kind, byte);

                            // Jackdaw rule: If a 'Q' is detected on the left hand followed by a thumb vowel => add a 'U'
                            if (byte == _Q && thumbs_bits)
                            {
                                stroke_add_element(kind, _U);
                            }

                            // Jackdaw rule: Double the first letter for the right hand only if + is in the stroke
                            if (double_first_letter && (family_id == FAMILY_RIGHT_HAND) && !code_pos)
                            {
                                stroke_add_element(kind, byte);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    break;
                }
            case KIND_SYMBOLS:
            case KIND_PUNCTUATION:
            case KIND_ONE_KEYCODE:
                {
                    uint16_t (*word_table)[element_size] = (uint16_t (*)[element_size])any_table;
                    for (int code_pos = 0; code_pos < element_size; ++code_pos)
                    {
                        const uint16_t word = pgm_read_word(&(word_table[family_bits][code_pos]));
                        if (word)
                        {
                            if (kind == KIND_ONE_KEYCODE)
                            {
                                if (family_id == FAMILY_LEFT_CONTROLS)
                                {
                                    uint16_t previous_case_mode = g_case_mode;
                                    switch (word)
                                    {
                                    case CKC_RESET_SEP_AND_CASE:
                                        {
                                            g_separator_mode = CKC_SEPMODE_SPC;
                                            g_case_mode = CKC_CASE_NORMAL;
                                            g_user_separators[0].bits = 0;
                                            g_user_separators[1].bits = 0;
                                            break;
                                        }
                                    case CKC_CAMEL:
                                        {
                                            g_separator_mode = CKC_SEPMODE_NOSPC;
                                            g_case_mode = CKC_CASE_INNER_LOCKED;
                                            break;
                                        }
                                    default:
                                        {
                                            if ((word >= CKC_CASE_NORMAL) && (word <= CKC_CASE_UPPER_LOCKED))
                                            {
                                                g_case_mode = word;
                                            }
                                            else if ((word >= CKC_SEPMODE_SPC) && (word <= CKC_SEPMODE_NOSPC))
                                            {
                                                g_separator_mode = word;
                                            }
                                            break;
                                        }
                                    }

                                    if (punctuation_mode && !choose_separator_mode)
                                    {
                                        g_new_undo_command.next_case_mode = g_case_mode - CKC_CASE_NORMAL + 1;
                                        g_case_mode = previous_case_mode;
                                    }
                                }
                            }
                            else
                            {
                                stroke_add_element(kind, word);
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
    }

    bool force_normal_case = false;
    // Check if we can send the separator (space, underscore...) before the stroke
    if (g_stroke_buffer_count || (!g_stroke_buffer_count && has_separator && !has_star))
    {
        uint16_t keycode_separator = 0;
        switch (g_separator_mode)
        {
        case CKC_SEPMODE_SPC:
            {
                keycode_separator = KC_SPC;
                break;
            }
        case CKC_SEPMODE_NOSPC:
            {
                // Force normal case for this stroke if the SC_SEP is pressed
                force_normal_case = has_separator;
                break;
            }
        default:
            {
                break;
            }
        }

        bool can_send_separator = true;
        if (g_stroke_buffer_count)
        {
            // Check the first keycode in the stroke
            stroke_element_t* stroke_element = &g_stroke_buffer[0];
            switch (stroke_element->keycode)
            {
            case _COMM:
            case _DOT:
            case _SCLN:
            case KC_ESC:
            case KC_ENT:
            case KC_END:
            case KC_HOME:
                {
                    can_send_separator = false;
                    break;
                }
            default:
                {
                    if (punctuation_mode && *left_controls_bits && !choose_separator_mode)
                    {
                        can_send_separator = false;
                    }
                    break;
                }
            }
        }

        if (can_send_separator && keycode_separator && (!has_separator || (!g_stroke_buffer_count && has_separator && !has_star)))
        {
            if (!g_user_separators[0].bits && ! g_user_separators[1].bits)
            {
                // No user defined separator
                send_mods_and_code(keycode_separator >> 8, keycode_separator);
                unregister_code(keycode_separator);
                undo_command_add_change(&g_new_undo_command, CHARACTER);
            }
            else if (!choose_separator_mode)
            {
                // User defined separator
                for (int i = 0; i < 2; ++i)
                {
                    if (g_user_separators[i].bits)
                    {
                        for (int code_pos = 0; code_pos < MAX_PUNCTUATION; ++code_pos)
                        {
                            const uint16_t word = pgm_read_word(&(g_user_separators[i].table[g_user_separators[i].bits][code_pos]));
                            if (word)
                            {
                                const uint8_t code = (uint8_t)word;
                                send_mods_and_code(word >> 8, code);
                                unregister_code(code);
                                undo_command_add_change_from_code(&g_new_undo_command, code);
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                }
            }
        }
    }

    if (!force_normal_case && (g_case_mode > CKC_CASE_NORMAL))
    {
        add_mods(MOD_LSFT);
    }

    // Send stroke buffer
    uint8_t inserted_characters = 0;
    for (uint8_t i = 0; i < g_stroke_buffer_count; ++i)
    {
        stroke_element_t* stroke_element = &g_stroke_buffer[i];
        switch (stroke_element->kind)
        {
        case KIND_LETTERS:
            {
                register_code(stroke_element->keycode);
                unregister_code(stroke_element->keycode);
                undo_command_add_change(&g_new_undo_command, CHARACTER);
                inserted_characters++;
                break;
            }
        case KIND_SYMBOLS:
            {
                const uint8_t code = (uint8_t)stroke_element->keycode;
                if (is_letter(code))
                {
                    // By doing this the shift mod can be applied on letter code
                    register_code(code);
                }
                else
                {
                    send_mods_and_code(stroke_element->keycode >> 8, code);
                }
                unregister_code(code);
                if (undo_command_add_change_from_code(&g_new_undo_command, code) == CHARACTER)
                {
                    inserted_characters++;
                }
                break;
            }
        case KIND_PUNCTUATION:
            {
                // TODO: Use another table for specific key sequences
                uint16_t specific_sequence[5] = {0};
                uint16_t word = stroke_element->keycode;
                switch (word)
                {
                case CKC_DELWORD:
                    {
                        specific_sequence[0] = LCTL(LSFT(KC_LEFT));
                        specific_sequence[1] = KC_BSPC;
                        break;
                    }
                case CKC_DLEFT:
                    {
                        specific_sequence[0] = KC_LEFT;
                        specific_sequence[1] = KC_LEFT;
                        break;
                    }
                case CKC_ENTABOVE:
                    {
                        specific_sequence[0] = KC_UP;
                        specific_sequence[1] = KC_END;
                        specific_sequence[2] = KC_ENT;
                        break;
                    }
                default:
                    {
                        const uint8_t code = (uint8_t)word;
                        send_mods_and_code(word >> 8, code);
                        unregister_code(code);
                        if (undo_command_add_change_from_code(&g_new_undo_command, code) == CHARACTER)
                        {
                            inserted_characters++;
                        }
                        break;
                    }
                }

                // Specific key sequence if any
                for (int i = 0; i < 5; ++i)
                {
                    const uint16_t word = specific_sequence[i];
                    if (word == 0)
                    {
                        break;
                    }
                    const uint8_t code = (uint8_t)word;
                    send_mods_and_code(word >> 8, code);
                    unregister_code(code);
                    if (undo_command_add_change_from_code(&g_new_undo_command, code) == CHARACTER)
                    {
                        inserted_characters++;
                    }
                }
                break;
            }
        default:
            {
                break;
            }
        }

        // Camel case
        if (inserted_characters == 1)
        {
            switch (g_case_mode)
            {
            case CKC_CASE_INNER_ONCE:
                {
                    g_case_mode = CKC_CASE_NORMAL;
                    // no break
                }
            case CKC_CASE_INNER_LOCKED:
                {
                    del_mods(MOD_LSFT);
                    break;
                }
            default:
                {
                    break;
                }
            }
        }
    }

    if (inserted_characters && (g_case_mode == CKC_CASE_UPPER_ONCE))
    {
        g_case_mode = CKC_CASE_NORMAL;
        del_mods(MOD_LSFT);
    }

    if (can_undo(&g_new_undo_command))
    {
        // Undo history
        if (g_undo_stack_index == MAX_UNDO)
        {
            g_undo_stack_index = 0;
        }

        g_undo_stack[g_undo_stack_index++] = g_new_undo_command;
    }
    else if (has_star)
    {
        // Check if we have data to undo in the previous undo command
        if (can_undo(previous_undo_command))
        {
            if (has_separator)
            {
                // SC_SEP becomes a Backspace
                register_code(KC_BSPC);
                unregister_code(KC_BSPC);
                
                // Patch chars to delete for the next undo
                for (int i = previous_undo_command->change_index; i >= 0; --i)
                {
                    if (previous_undo_command->changes[i].kind == CHARACTER)
                    {
                        previous_undo_command->changes[i].count--;
                        break;
                    }
                }

                // If there is no more data to remove in the previous undo command we can go backward in the undo stack
                const uint8_t inserted_characters = undo_command_get_changes_count(previous_undo_command, CHARACTER);
                if (inserted_characters == 0)
                {
                    g_undo_stack_index = previous_index;
                }
            }
            else if (undo_allowed)
            {
                // Parse changes in reverse order and undo them
                for (int i = previous_undo_command->change_index; i >= 0; --i)
                {
                    change_t* change = &previous_undo_command->changes[i];
                    for (int j = 0; j < change->count; ++j)
                    {
                        switch (change->kind)
                        {
                        case CHARACTER:
                            {
                                register_code(KC_BSPC);
                                unregister_code(KC_BSPC);
                                break;
                            }
                        case MOVE_LEFT:
                            {
                                register_code(KC_RIGHT);
                                unregister_code(KC_RIGHT);
                                break;
                            }
                        case ENTER:
                            {
                                // We use SHIFT to select text. We have to do this for text editors that autoindent text.
                                // Vim users needs to add : 'behave mswin' in their .vimrc file
                                register_code(KC_LSFT);
                                register_code(KC_UP);
                                unregister_code(KC_UP);
                                register_code(KC_END);
                                unregister_code(KC_END);
                                unregister_code(KC_LSFT);

                                register_code(KC_DEL);
                                unregister_code(KC_DEL);
                                break;
                            }
                        case MOVE_UP:
                            {
                                register_code(KC_DOWN);
                                unregister_code(KC_DOWN);
                                break;
                            }
                        default:
                            {
                                break;
                            }
                        }
                    }
                }

                // Restore the case mode used before that command
                if (previous_undo_command->next_case_mode)
                {
                    g_case_mode = CKC_CASE_NORMAL + previous_undo_command->previous_case_mode - 1;
                }

                g_undo_stack_index = previous_index;
            }
        }
        else if (has_separator)
        {
            // No data to remove in the undo stack, but we allow the SC_SEP to become a Backspace
            register_code(KC_BSPC);
            unregister_code(KC_BSPC);
        }
    }

    // Restore original mods
    set_mods(original_mods);

    // Clear bits
    for (int i = 0; i < NB_FAMILY; ++i)
    {
        g_family_bits[i] = 0;
    }
}

