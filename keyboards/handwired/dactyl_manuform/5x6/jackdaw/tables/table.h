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

// A lookup table can stores letters (8 bits) or symbols (16 bits)
typedef enum
{
    KIND_UNKNOWN,
    KIND_ONE_KEYCODE,
    KIND_LETTERS,
    KIND_SYMBOLS,
    KIND_PUNCTUATION
} kind_table_t;

typedef struct
{
    void* any_table;
    uint8_t element_size;
    kind_table_t kind;
} table_t;

#define NO_ENTRY {0}

#define MAX_VOWELS 3
#define _V1(c1) {c1, 0, 0}
#define _V2(c1, c2) {c1, c2, 0}
#define _V3(c1, c2, c3) {c1, c2, c3}

#define MAX_LETTERS 6
#define _1(c1) {c1, 0, 0, 0, 0, 0}
#define _2(c1, c2) {c1, c2, 0, 0, 0, 0}
#define _3(c1, c2, c3) {c1, c2, c3, 0, 0, 0}
#define _4(c1, c2, c3, c4) {c1, c2, c3, c4, 0, 0}
#define _5(c1, c2, c3, c4, c5) {c1, c2, c3, c4, c5, 0}
#define _6(c1, c2, c3, c4, c5, c6) {c1, c2, c3, c4, c5, c6}

#define MAX_SYMBOLS 3
#define _S1(c1) {c1, 0, 0}
#define _S2(c1, c2) {c1, c2, 0}
#define _S3(c1, c2, c3) {c1, c2, c3}

#define MAX_PUNCTUATION 4
#define _P1(c1) {c1, 0, 0, 0}
#define _P2(c1, c2) {c1, c2, 0, 0}
#define _P3(c1, c2, c3) {c1, c2, c3, 0}
#define _P4(c1, c2, c3, c4) {c1, c2, c3, c4}

#define MAX_ONE_KEYCODE 1
#define _K1(c1) {c1}

typedef const uint16_t punctuation_table_t[MAX_PUNCTUATION];

