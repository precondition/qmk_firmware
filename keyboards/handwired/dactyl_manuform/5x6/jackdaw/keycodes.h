/*
Copyright 2018 FromtonRouge

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum/quantum_keycodes.h"
#include "tmk_core/common/keycode.h"

enum kaladrius_custom_keycodes
{
    CKC_STENO = SAFE_RANGE,
    CKC_CASE_NORMAL,
    CKC_CASE_INNER_ONCE,
    CKC_CASE_INNER_LOCKED,
    CKC_CASE_UPPER_ONCE,
    CKC_CASE_UPPER_LOCKED,
    CKC_SEPMODE_SPC,
    CKC_SEPMODE_NOSPC,
    CKC_RESET_SEP_AND_CASE, // Set CKC_CASE_NORMAL + CKC_SEPMODE_SPC
    CKC_CAMEL,  // Set CKC_SEPMODE_NOSPC + CKC_CASE_INNER_LOCKED
    CKC_DELWORD,
    CKC_DLEFT,
    CKC_ENTABOVE,
    CKC_KALADRIUS_SAFE_RANGE,
};

#define STENO_KEY_BIT(x) (1L << (x & 0xF))

#ifdef AZERTY_OS_ENABLE

#include "keymap_extras/keymap_french.h"

#define _SUP2   FR_SUP2
#define _AMP    FR_AMP
#define _EACU   FR_EACU
#define _DQUOT  FR_QUOT
#define _APOS   FR_APOS
#define _LPRN   FR_LPRN
#define _MINS   FR_MINS
#define _EGRV   FR_EGRV
#define _UNDS   FR_UNDS
#define _CCED   FR_CCED
#define _AGRV   FR_AGRV
#define _RPRN   FR_RPRN
#define _EQL    FR_EQL
#define _A      FR_A 
#define _Z      FR_Z
#define _DLR    FR_DLR
#define _Q      FR_Q 
#define _M      FR_M 
#define _UGRV   FR_UGRV
#define _ASTR   FR_ASTR
#define _LESS   FR_LESS
#define _W      FR_W
#define _COMM   FR_COMM
#define _SCLN   FR_SCLN
#define _COLN   FR_COLN
#define _EXLM   FR_EXLM
#define _N1     FR_1 
#define _N2     FR_2 
#define _N3     FR_3 
#define _N4     FR_4 
#define _N5     FR_5 
#define _N6     FR_6 
#define _N7     FR_7 
#define _N8     FR_8 
#define _N9     FR_9 
#define _N0     FR_0 
#define _OVRR   FR_OVRR
#define _PLUS   FR_PLUS
#define _UMLT   FR_UMLT
#define _PND    FR_PND
#define _PERC   FR_PERC
#define _MU     FR_MU 
#define _GRTR   FR_GRTR
#define _QUES   FR_QUES
#define _DOT    FR_DOT
#define _SLSH   FR_SLSH
#define _SECT   FR_SECT
#define _TILD   FR_TILD
#define _HASH   FR_HASH
#define _LCBR   FR_LCBR
#define _LBRC   FR_LBRC
#define _PIPE   FR_PIPE
#define _GRV    FR_GRV 
#define _BSLS   FR_BSLS
#define _CIRC   ALGR(KC_9)
#define _AT     FR_AT 
#define _RBRC   FR_RBRC
#define _RCBR   FR_RCBR
#define _EURO   FR_EURO
#define _BULT   FR_BULT

#else

#define _SUP2   KC_SUP2
#define _AMP    LSFT(KC_7)
#define _EACU   KC_EACU
#define _DQUOT  LSFT(KC_QUOT)
#define _APOS   KC_QUOT
#define _LPRN   KC_LPRN
#define _MINS   KC_MINS
#define _EGRV   KC_EGRV
#define _UNDS   KC_UNDS
#define _CCED   KC_CCED
#define _AGRV   KC_AGRV
#define _RPRN   KC_RPRN
#define _EQL    KC_EQL
#define _A      KC_A 
#define _Z      KC_Z
#define _DLR    KC_DLR
#define _Q      KC_Q 
#define _M      KC_M 
#define _UGRV   KC_UGRV
#define _ASTR   KC_ASTR
#define _LESS   LSFT(KC_COMM)
#define _W      KC_W
#define _COMM   KC_COMM
#define _SCLN   KC_SCLN
#define _COLN   KC_COLN
#define _EXLM   KC_EXLM
#define _N1     KC_1 
#define _N2     KC_2 
#define _N3     KC_3 
#define _N4     KC_4 
#define _N5     KC_5 
#define _N6     KC_6 
#define _N7     KC_7 
#define _N8     KC_8 
#define _N9     KC_9 
#define _N0     KC_0 
#define _OVRR   KC_OVRR
#define _PLUS   KC_PLUS
#define _UMLT   KC_UMLT
#define _PND    KC_PND
#define _PERC   KC_PERC
#define _MU     KC_MU 
#define _GRTR   LSFT(KC_DOT)
#define _QUES   LSFT(KC_SLSH)
#define _DOT    KC_DOT
#define _SLSH   KC_SLSH
#define _SECT   KC_SECT
#define _TILD   KC_TILD
#define _HASH   KC_HASH
#define _LCBR   KC_LCBR
#define _LBRC   KC_LBRC
#define _PIPE   KC_PIPE
#define _GRV    KC_GRV 
#define _BSLS   KC_BSLS
#define _CIRC   RALT(KC_9)
#define _AT     KC_AT 
#define _RBRC   KC_RBRC
#define _RCBR   KC_RCBR
#define _EURO   KC_EURO
#define _BULT   KC_BULT

#endif

#define _B      KC_B
#define _C      KC_C
#define _D      KC_D
#define _E      KC_E
#define _F      KC_F
#define _G      KC_G
#define _H      KC_H
#define _I      KC_I
#define _J      KC_J
#define _K      KC_K
#define _L      KC_L
#define _N      KC_N
#define _O      KC_O
#define _P      KC_P
#define _R      KC_R
#define _S      KC_S
#define _T      KC_T
#define _U      KC_U
#define _V      KC_V
#define _X      KC_X
#define _Y      KC_Y

// Bit to identify a steno key
#define STENO_BIT (1L << 31) 

// 4 bits for star and the plus key
#define OFFSET_SPECIAL_CONTROLS 0
#define SC_STAR (0 | (FAMILY_SPECIAL_CONTROLS << 4) | STENO_BIT)
#define SC_LPLUS (1 | (FAMILY_SPECIAL_CONTROLS << 4) | STENO_BIT)
#define SC_RPLUS (2 | (FAMILY_SPECIAL_CONTROLS << 4) | STENO_BIT)
#define SC_SEP  (3 | (FAMILY_SPECIAL_CONTROLS << 4) | STENO_BIT)

// 8 bits for the left hand
#define OFFSET_LEFT_HAND 4
#define L_N (0 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_R (1 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_W (2 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_H (3 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_C (4 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_T (5 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_A (6 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)
#define L_S (7 | (FAMILY_LEFT_HAND << 4) | STENO_BIT)

// 6 bits for thumbs
#define OFFSET_THUMBS 12
#define T_E (0 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_O (1 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_A (2 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_Y (3 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_U (4 | (FAMILY_THUMBS << 4) | STENO_BIT)
#define T_I (5 | (FAMILY_THUMBS << 4) | STENO_BIT)

// 8 bits for the right hand
#define OFFSET_RIGHT_HAND 18
#define R_R (0 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_N (1 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_L (2 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_G (3 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_C (4 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_H (5 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_T (6 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)
#define R_S (7 | (FAMILY_RIGHT_HAND << 4) | STENO_BIT)

// 2 bits for E and Y
#define OFFSET_RIGHT_PINKY 26
#define RP_E  (0 | (FAMILY_RIGHT_PINKY << 4) | STENO_BIT)
#define RP_Y  (1 | (FAMILY_RIGHT_PINKY << 4) | STENO_BIT)

// 1 bit for space controls
#define OFFSET_SPACE_CONTROLS 28
#define S_ENT  (0 | (FAMILY_SPACES << 4) | STENO_BIT)

// 5 bits for right controls
#define OFFSET_RIGHT_CONTROLS 0
#define R0  (0 | (FAMILY_RIGHT_CONTROLS << 4) | STENO_BIT)
#define R1  (1 | (FAMILY_RIGHT_CONTROLS << 4) | STENO_BIT)
#define R2  (2 | (FAMILY_RIGHT_CONTROLS << 4) | STENO_BIT)
#define R3  (3 | (FAMILY_RIGHT_CONTROLS << 4) | STENO_BIT)
#define R4  (4 | (FAMILY_RIGHT_CONTROLS << 4) | STENO_BIT)

// 6 bits for left controls
#define OFFSET_LEFT_CONTROLS 5
#define L0  (0 | (FAMILY_LEFT_CONTROLS << 4) | STENO_BIT)
#define L1  (1 | (FAMILY_LEFT_CONTROLS << 4) | STENO_BIT)
#define L2  (2 | (FAMILY_LEFT_CONTROLS << 4) | STENO_BIT)
#define L3  (3 | (FAMILY_LEFT_CONTROLS << 4) | STENO_BIT)
#define L4  (4 | (FAMILY_LEFT_CONTROLS << 4) | STENO_BIT)
#define L5  (5 | (FAMILY_LEFT_CONTROLS << 4) | STENO_BIT)
