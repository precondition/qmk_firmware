/* Colemak DHm with home row mods and hybrid steno
 * for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H

// All custom keycodes and aliases can be found in keymap.h
#include "keymap.h"

/*MAKE SURE THAT ADJUST AND RESET ARE ACCESSIBLE!*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK_DH] = LAYOUT_5x6(
           REDO, UNDO  ,KC_WH_U,KC_WH_D, KC_F4 , KC_F5 ,    DED_UML,DED_CIR,E_GRAVE,E_ACUTE, KC_F10, KC_F11,
        A_GRAVE, KC_Q  , KC_W  , KC_F  , KC_P  , KC_B  ,    KC_J   , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_MINS,
         KC_ESC, HOME_A, HOME_R, HOME_S, HOME_T, KC_G  ,    KC_M   , HOME_N, HOME_E, HOME_I, HOME_O,KC_QUOT,
        MS_CAPS, KC_Z  , KC_X  , KC_C  , KC_D  , KC_V  ,    KC_K   , KC_H  ,KC_COMM, TD_DOT,KC_SLSH,E_ACUTE,
                      KC_BSLASH,C_CDILA,                                    KC_RALT, KC_GRV,
                                        NAV_TAB, KC_SPC,    KC_BSPC,SYM_ENT,
                                        MS_CAPS,OS_LSFT,    OS_RSFT, KC_UP ,
                                         PLOVER,MS_CAPS,    SH_OS  ,KC_DOWN
  ),

  [_SYM] = LAYOUT_5x6(

        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,    KC_F6  , KC_F7 , KC_F8 , KC_F9 , KC_F10 , KC_F11,
        KC_DOT , KC_4  , KC_2  , KC_3  , KC_1  , KC_5  ,    KC_6   , KC_0  , KC_8  , KC_9  , KC_7  ,KC_MINS,
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,    KC_CIRC,KC_AMPR,KC_ASTR,KC_EQL ,KC_PLUS,KC_MINS,
        _______,_______,_______,_______,DED_CIR,_______,    _______,COMPOSE,_______, KC_DOT, UPDIR ,_______,
                        _______,_______,                                    GUILL_L,GUILL_R,
                                        NAV_UND,_______,    _______,_______,
                                        _______,_______,    _______,_______,
                                        _______,_______,    ADJUST, ADJUST
  ),

  [_NAV] = LAYOUT_5x6(
        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,    KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 , KC_F11,
        _______,_______,KC_NLCK,KC_INS ,KC_SLCK,_______,    _______,KC_PGUP, KC_UP ,KC_PGDN,_______,KC_MUTE,
        MS_CAPS,KC_LGUI,KC_LALT,KC_LSFT,KC_LCTL,  GNAV ,    KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END ,KC_VOLU,
        _______, MOUSE ,C(KC_A),C(KC_C),C(KC_V),_______,    _______,KC_PSCR,KC_LCBR,KC_RCBR,KC_INS ,KC_VOLD,
                        _______,_______,                                    KC_BRID,KC_BRIU,
                                         _______,_______,   _______,_______,
                                         _______,_______,   _______,_______,
                                           ADJUST,ADJUST,   _______,_______
  ),

    [_GNAV] = LAYOUT_5x6(
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,    _______,_______, G_UP  ,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,    G_HOME ,_______, G_DOWN,_______, G_END ,_______,
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
                        _______,_______,                                    _______,_______,
                                        _______,_______,    _______,_______,
                                        _______,_______,    _______,_______,
                                        _______,_______,    _______,_______
    ),


    [_MOUSE] = LAYOUT_5x6(
        _______,_______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,_______,
        _______,_______, KC_6  , KC_5  , KC_4  ,_______,    _______,KC_WBAK,KC_MS_U,KC_WFWD,_______,_______,
_______,KC_LGUI,LALT_T(KC_3),LSFT_T(KC_2),LCTL_T(KC_1),KC_0,    _______,KC_MS_L,KC_MS_D,KC_MS_R,_______,_______,
        _______,KC_SPC, KC_9  , KC_8  , KC_7  ,_______,    _______,KC_BTN3,KC_WH_D,KC_WH_U,_______,_______,
                        _______, KC_0  ,                                    _______,_______,
                                        _______,_______,    KC_BTN1,KC_BTN2,
                                        _______,_______,    KC_BTN3,_______,
                                        _______,_______,    _______,_______
    ),

    [_PLOVER] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,    KC_6   ,KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,    KC_Y   ,KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,    KC_H   ,KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_QUOT,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,    KC_N   ,KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLASH,
                         KC_LBRC,KC_RBRC,                                  KC_PLUS, KC_EQL,
                                         KC_C,   KC_V,      KC_N   , KC_M,
                                         KC_TAB,  KC_B ,    KC_BSPC, KC_DEL,
                                         PLOVER, KC_SPC,    KC_LGUI, KC_LALT
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    switch (keycode) {

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
             tap_code16(ALGR(KC_GRV));
             set_mods(mod_state);
             tap_code(KC_A);
         }
         return false;

     case E_GRAVE:
         if (record->event.pressed) {
             del_mods(MOD_MASK_SHIFT);
             tap_code16(ALGR(KC_GRV));
             set_mods(mod_state);
             tap_code(KC_E);
         }
         return false;

    case ARROW_R:
      if (record->event.pressed) {
        SEND_STRING("->");
      }
      break;

    case G_DOWN:
        if (record->event.pressed) {
            register_code(KC_G);
            register_code(KC_DOWN);
        } else {
            unregister_code(KC_G);
            unregister_code(KC_DOWN);
        }
	  break;

    case G_UP:
        if (record->event.pressed) {
            register_code(KC_G);
            register_code(KC_UP);
        } else {
            unregister_code(KC_G);
            unregister_code(KC_UP);
        }
	  break;

    case G_HOME:
        if (record->event.pressed) {
            register_code(KC_G);
            register_code(KC_HOME);
        } else {
            unregister_code(KC_G);
            unregister_code(KC_HOME);
        }
	  break;

    case G_END:
        if (record->event.pressed) {
            register_code(KC_G);
            register_code(KC_END);
        } else {
            unregister_code(KC_G);
            unregister_code(KC_END);
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

    case UPDIR:
      if (record->event.pressed) {
          tap_code(KC_DOT);
          tap_code(KC_DOT);
          tap_code(KC_SLSH);
          return false;
      }
      break;

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

    case HOME_T:
         /*This piece of code nullifies the effect of Left Shift when*/
         /*tapping the HOME_T key. This helps rolling over HOME_S and HOME_T */
         /*to obtain the intended "st" instead of "T". Consequently, capital T can */
         /*only be obtained by tapping HOME_T and holding HOME_E (which is the right shift mod tap).*/
        if (record->event.pressed && record->tap.count == 1 && !record->tap.interrupted) {
            if (mod_state & MOD_BIT(KC_LSHIFT)) {
                unregister_code(KC_LSHIFT);
                tap_code(KC_S);
                tap_code(KC_T);
                set_mods(mod_state);
                return false;
            }
        }
         /*else process HOME_T as usual.*/
        return true;

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
        // These next mod taps are used very frequently during typing.
        // As such, the lower the tapping term, the faster the typing.
        case HOME_S:
        case HOME_E:
            return TAPPING_TERM - 26;
        default:
            return TAPPING_TERM;
    }
};
