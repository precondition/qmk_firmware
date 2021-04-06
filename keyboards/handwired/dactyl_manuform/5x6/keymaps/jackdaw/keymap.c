/* 
 * An implementation of the Jackdaw orthographic steno system
 * for the Dactyl Manuform 5x6 Keyboard (with fallback colemak)
 */ 

#include QMK_KEYBOARD_H
#include "jackdaw/keycodes.h"
#include "jackdaw/stroke.h"

// All custom keycodes and aliases can be found in keymap.h
#include "keymap.h"

typedef const uint32_t steno_layout_t[MATRIX_COLS];
extern steno_layout_t* get_steno_layout(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();
    uint8_t oneshot_mod_state = get_oneshot_mods();
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


    case KC_BSPC:
        {
        static bool delkey_registered;
        if (record->event.pressed) {
            if (mod_state & MOD_MASK_SHIFT) {
                // In case only one shift is held
                // see https://stackoverflow.com/questions/1596668/logical-xor-operator-in-c
                // This also means that in case of holding both shifts and pressing KC_BSPC,
                // Shift+Delete is sent (useful in Firefox) since the shift modifiers aren't deleted.
                if (!(mod_state & MOD_BIT(KC_LSHIFT)) != !(mod_state & MOD_BIT(KC_RSHIFT))) {
                    del_mods(MOD_MASK_SHIFT);
                }
                register_code(KC_DEL);
                delkey_registered = true;
                set_mods(mod_state);
                return false;
            }
        } else {
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        return true;
    }

     case A_GRAVE:
         if (record->event.pressed) {
             del_mods(MOD_MASK_SHIFT);
             // Equivalent to `del_oneshot_mods`
             set_oneshot_mods(oneshot_mod_state & ~MOD_MASK_SHIFT);
             tap_code16(ALGR(KC_GRV));
             set_mods(mod_state);
             set_oneshot_mods(oneshot_mod_state);
             tap_code(KC_A);
         }
         return false;

     case E_GRAVE:
         if (record->event.pressed) {
             del_mods(MOD_MASK_SHIFT);
             // Equivalent to `del_oneshot_mods`
             set_oneshot_mods(oneshot_mod_state & ~MOD_MASK_SHIFT);
             tap_code16(ALGR(KC_GRV));
             set_mods(mod_state);
             set_oneshot_mods(oneshot_mod_state);
             tap_code(KC_E);
         }
         return false;

    case ARROW_R:
      if (record->event.pressed) {
          if (mod_state & MOD_MASK_SHIFT || oneshot_mod_state & MOD_MASK_SHIFT) {
            del_mods(MOD_MASK_SHIFT);
            // Equivalent to `del_oneshot_mods`
            set_oneshot_mods(oneshot_mod_state & ~MOD_MASK_SHIFT);
            send_string("=>");
            set_mods(mod_state);
          } else {
            SEND_STRING("->");
          }
      }
      break;

    case GUILL_L:
        if (record->event.pressed) {
            tap_code(COMPOSE);
            tap_code16(KC_LT);
            tap_code16(KC_LT);
        }
      break;

    case GUILL_R:
        if (record->event.pressed) {
            tap_code(COMPOSE);
            tap_code16(KC_GT);
            tap_code16(KC_GT);
        }
      break;

    case NAV_UND:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          // send advanced keycode, etc.
          register_code16(KC_UNDS);
        } else {
          unregister_code16(KC_UNDS);
        }
        // do not continue with default tap action if the MT was pressed or released, but not held
        return false;
      }
      break;

    }
    return true;
};

/*
 * Per key tapping term settings
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_O:
            return TAPPING_TERM + 20;
        case SYM_ENT:
            // Very low tapping term to make sure I don't hit Enter accidentally.
            return TAPPING_TERM - 65;
        default:
            return TAPPING_TERM;
    }
};

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

  [_COLEMAK_DH] = LAYOUT_5x6(
           REDO, UNDO  ,KC_WH_U,KC_WH_D, KC_F4 , KC_F5 ,    DED_UML,DED_CIR,E_GRAVE,E_ACUTE, KC_F10, KC_F11,
        A_GRAVE, KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,    KC_J   , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_MINS,
         KC_ESC, HOME_A, HOME_R, HOME_S, HOME_T, KC_G  ,    KC_M   , HOME_N, HOME_E, HOME_I, HOME_O,KC_QUOT,
         TG_MIC, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,    KC_K   , KC_H  ,KC_COMM, KC_DOT,KC_SLSH,ARROW_R,
                      KC_BSLASH,C_CDILA,                                    KC_LPRN, KC_RPRN,
                                        NAV_TAB, KC_SPC,    KC_BSPC,SYM_ENT,
                                        COMPOSE,OS_LSFT,    OS_RSFT, KC_UP ,
                                        JACKDAW,KC_LBRC,    KC_RBRC,KC_DOWN
  ),

  [_SYM] = LAYOUT_5x6(

        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,    KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 , KC_F11,
        KC_DOT , KC_4  , KC_2  , KC_3  , KC_1  , KC_5  ,    KC_6   , KC_0  , KC_8  , KC_9  , KC_7  ,KC_MINS,
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,    KC_CIRC,KC_AMPR,KC_ASTR,KC_EQL ,KC_PLUS, KC_GRV,
        _______,_______,KC_LCBR,KC_LBRC,KC_LPRN,_______,    _______,KC_RPRN,KC_RBRC,KC_RCBR,_______,_______,
                        _______,_______,                                    GUILL_L,GUILL_R, 
                                        NAV_UND,_______,    _______,_______,
                                        _______,_______,    _______,_______,
                                        _______,_______,    ADJUST, ADJUST
  ),

  [_NAV] = LAYOUT_5x6(
        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,    KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 , KC_F11,
        _______,_______,KC_NLCK,KC_SLCK,KC_INS ,_______,    _______,KC_PGUP, KC_UP ,KC_PGDN,_______,KC_MUTE,
        _______,KC_LGUI,KC_LALT,KC_LSFT,KC_LCTL,_______,    KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END ,KC_VOLU,
        _______,_______,C(KC_A),C(KC_C),C(KC_V),_______,    _______,KC_PSCR,KC_LCBR,KC_RCBR,KC_INS ,KC_VOLD,
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
                                        JACKDAW  ,  _______,      _______,TG(_COLEMAK_DH)
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
