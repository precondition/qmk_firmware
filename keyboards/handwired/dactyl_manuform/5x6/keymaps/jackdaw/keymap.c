/* 
 * An implementation of the Jackdaw orthographic steno system
 * for the Dactyl Manuform 5x6 Keyboard (with fallback colemak)
 */ 

#include QMK_KEYBOARD_H
#include "jackdaw/keycodes.h"
#include "jackdaw/stroke.h"

// Layer names
#define _COLEMAK_DHM 0
#define _SYM 1
#define _NAV 2
#define _JACKDAW 3
#define _ADJUST 4

// Layer keys
#define NAV MO(_NAV)
#define SYM MO(_SYM)
#define ADJUST MO(_ADJUST)
#define SYM_ENT LT(_SYM, KC_ENT)

// Miscellaneous keyboard shortcuts in direct access
#define UNDO LCTL(KC_Z)
#define REDO LCTL(KC_Y)

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_O LGUI_T(KC_O)
#define HOME_I LALT_T(KC_I)
#define HOME_E RSFT_T(KC_E)
#define HOME_N LCTL_T(KC_N)

#define NAV MO(_NAV)
#define LOWER MO(_LOWER)
#define ADJUST MO(_ADJUST)

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;

typedef const uint32_t steno_layout_t[MATRIX_COLS];
extern steno_layout_t* get_steno_layout(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch (keycode) {

    case CKC_STENO:
        {
			steno_layout_t* steno_keymap_p = get_steno_layout();
			if (steno_keymap_p)
			{
				const uint32_t dword = pgm_read_dword(&(steno_keymap_p[record->event.key.row][record->event.key.col]));
				if (dword & STENO_BIT)
				{
					const uint32_t bit_key = 1L << (dword & 0x0F);
					const uint8_t family = (dword >> 4) & 0x0F;
					const uint8_t family_offset = g_family_to_bit_offset[family];
					uint32_t* keys_pressed_p = g_family_to_keys_pressed[family];
					if (record->event.pressed)
					{
						(*keys_pressed_p) |= (bit_key << family_offset);
						g_family_bits[family] |= bit_key;
					}
					else
					{
						(*keys_pressed_p) &= ~(bit_key << family_offset);

						// Stroke if all steno keys are released
						if (can_stroke())
						{
							stroke();
						}
					}
				}
			}
            return false;
        }

    case KC_ESC:
        // Home row alt-tabbing.
        if (mod_state & MOD_MASK_ALT) {
            if (record->event.pressed) {
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        }
        // Else, let QMK process the KC_ESC keycode as usual
        return true;

    case HOME_I:
        // This piece of code nullifies the effect of Right Shift when
        // tapping the HOME_I key. This helps rolling over HOME_E and HOME_I 
        // to obtain the intended "ei" instead of "I". Consequently, capital I can 
        // only be obtained by tapping HOME_I and holding HOME_S (which is the left shift mod tap).
        if (record->event.pressed && record->tap.count == 1 && !record->tap.interrupted) {
            if (mod_state & MOD_BIT(KC_RSHIFT)) {
                unregister_code(KC_RSHIFT);
                tap_code(KC_E);
                tap_code(KC_I);
                set_mods(mod_state);
                return false;
            }
        }
        // else process HOME_I as usual.
        return true;


    case HOME_N:
         /*This piece of code nullifies the effect of Right Shift when*/
         /*tapping the HOME_N key. This helps rolling over HOME_E and HOME_N */
         /*to obtain the intended "en" instead of "N". Consequently, capital N can */
         /*only be obtained by tapping HOME_N and holding HOME_S (which is the left shift mod tap).*/
        if (record->event.pressed && record->tap.count == 1 && !record->tap.interrupted) {
            if (mod_state & MOD_BIT(KC_RSHIFT)) {
                unregister_code(KC_RSHIFT);
                tap_code(KC_E);
                tap_code(KC_N);
                set_mods(mod_state);
                return false;
            }
        }
         /*else process HOME_N as usual.*/
        return true;

    }
    return true;
};

/*
 * Per key tapping term settings
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_I:
            // My ring finger tends to linger on the key 
            // This tapping term allows me to type "ion" effortlessly.
            return TAPPING_TERM + 200;
        case HOME_O:
            return TAPPING_TERM + 10;
        case SYM_ENT:
            // Very low tapping term to make sure I don't hit Enter accidentally.
            return TAPPING_TERM - 65;
        // These next mod taps are used very frequently during typing.
        // As such, the lower the tapping term, the faster the typing.
        case HOME_S:
            return TAPPING_TERM - 28;
        case HOME_E:
            return TAPPING_TERM - 26;
        default:
            return TAPPING_TERM;
    }
}

const uint32_t PROGMEM g_steno_layout[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_5x6(
           0   ,   0   ,   0   ,   0   ,   0   ,   0   ,       0   ,   0   ,   0   ,   0   ,   0   ,   0   ,
           0   ,  L3   ,  L2   ,  L1   ,  L0   , S_ENT ,       0   ,   R0  ,  R1   ,  R2   ,  R3   ,  R4   ,
          L4   ,  L_A  ,  L_C  ,  L_W  ,  L_N  ,SC_STAR,     SC_SEP,  R_R  ,  R_L  ,  R_C  ,  R_T  , RP_E  ,
          L5   ,  L_S  ,  L_T  ,  L_H  ,  L_R  ,SC_SEP ,     SC_SEP,  R_N  ,  R_G  ,  R_H  ,  R_S  , RP_Y  ,
                           0   ,   0   ,                                       0   ,   0   ,
                                         T_O   , T_E   ,       T_I ,  T_Y  ,
                                       SC_LPLUS, T_A   ,       T_U ,SC_RPLUS,
                                           0   ,   0   ,       0   ,   0   
    );


steno_layout_t* get_steno_layout(void) { return g_steno_layout; }

/*MAKE SURE THAT ADJUST AND RESET ARE ACCESSIBLE !!*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK_DHM] = LAYOUT_5x6(
           REDO, UNDO  , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,    KC_F6 , KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11,
         KC_TAB, KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,    KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_MINS,
         KC_ESC, HOME_A, HOME_R, HOME_S, HOME_T, KC_G  ,    KC_M  , HOME_N, HOME_E, HOME_I, HOME_O,KC_QUOT,
      KC_BSLASH, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,    KC_K  , KC_H  ,KC_COMM,KC_DOT ,KC_SLSH, KC_GRV,
                      KC_BSLASH,KC_NO,                                     KC_LPRN,KC_RPRN, 
                                          NAV  , KC_SPC,    KC_BSPC, SYM_ENT,
                                          KC_NO, KC_NO ,    KC_DEL , KC_APP ,
                                   TG(_JACKDAW),KC_CAPS,    ADJUST , OSM(MOD_LSFT)
  ),

  [_SYM] = LAYOUT_5x6(

        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,    KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_BSPC,
        KC_DOT , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,    KC_6   , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,    KC_CIRC,KC_AMPR,KC_ASTR,KC_EQL ,KC_PLUS,KC_MINS,
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
                        _______,_______,                                    KC_LBRC, KC_RBRC, 
                                        _______,KC_UNDS,    _______,_______,
                                        _______,_______,    _______,_______,
                                        _______,_______,    ADJUST, ADJUST
  ),

  [_NAV] = LAYOUT_5x6(
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,KC_NLCK,KC_INS ,KC_SLCK,_______,    KC_PGUP,KC_PGDN, KC_UP ,KC_WH_D,KC_WH_U,KC_MUTE,
        _______,KC_LGUI,KC_LALT,KC_LSFT,KC_LCTL,_______,    KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END ,KC_VOLU,
        _______,_______,_______,_______,_______,_______,    _______,KC_PSCR,KC_LCBR,KC_RCBR,KC_INS ,KC_VOLD,
                        _______,_______,                                    KC_BRID,KC_BRIU,
                                         _______,_______,   _______,_______,
                                         _______,_______,   _______,_______,
                                           ADJUST,ADJUST,   _______,_______
  ),

    // See g_steno_layout
    [_JACKDAW] = LAYOUT_5x6(
        KC_ESC,KC_LGUI,KC_LALT,KC_LSFT,KC_LCTL,_______,    _______,_______,_______,_______,_______,_______,
        CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,    CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,
        CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,    CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,
        CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,    CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,CKC_STENO,
                        CKC_STENO,CKC_STENO,                                    CKC_STENO,CKC_STENO,
                                        CKC_STENO,CKC_STENO,    CKC_STENO,CKC_STENO,
                                        CKC_STENO,CKC_STENO,    CKC_STENO,CKC_STENO,
                                        TG(_JACKDAW),_______,    _______,TG(_COLEMAK_DHM)
    ),

    [_ADJUST] = LAYOUT_5x6(
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______, RESET ,    _______,_______,_______,_______,_______,_______,
                        _______,_______,                                    _______,_______,
                                        _______,_______,    _______,_______,
                                        _______,_______,    _______,_______,
                                        _______,_______,    _______,_______
    )
};
