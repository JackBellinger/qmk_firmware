/* Copyright 2021 wuquestudio
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "features/layer_lock.h"

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

enum custom_keycodes {
    MAC_SELWORD = SAFE_RANGE,
    LLOCK,
    MAC_SEARCH,
    MAC_QMKURL,
    MAC_MY_OTHER_MACRO,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
    switch (keycode) {
        case MAC_SELWORD:  // Selects the current word under the cursor.
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
                // Mac users, change LCTL to LALT:
                // SEND_STRING(SS_LALT(SS_TAP(X_RGHT) SS_LSFT(SS_TAP(X_LEFT))));
            }
            return false;
        case MAC_SEARCH:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING(SS_LCTL("c") SS_DELAY(100) SS_LCTL(SS_LALT("u")) SS_DELAY(100) SS_LCTL("l") SS_LCTL("v") "\a\n");
            } else {
                // when keycode QMKBEST is released
            }
            break;

        case MAC_QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://jackbellinger.github.io/blog");
            } else {
                // when keycode QMKURL is released
            }
            break;

        case MAC_MY_OTHER_MACRO:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("ac")); // selects all and copies
            }
            break;
    }
    return true;
};

# Matrix diagram for Wuque Ikki68 Aurora

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐┌───┬───┐     ┌───────┐
│00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │2D ││0E │0F │     │0D     │ 2u Backspace
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤├───┼───┤     └─┬─────┤
│10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D   ││1E │1F │       │     │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤└───┴───┘    ┌──┴┐1D  │ ISO Enter
│20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C      │             │2C │    │
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤┌───┐        └───┴────┘
│30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3C    │3D ││3E │
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴┬──┴┼───┼───┐
│40  │41  │42  │46                      │4A  │4B  │4C  │ │4D │4E │4F │
└────┴────┴────┴────────────────────────┴────┴────┴────┘ └───┴───┴───┘
┌────────┐                                       ┌──────────┐
│30      │ 2.25u LShift             2.75u RShift │3C        │
└────────┘                                       └──────────┘
┌────┬────┬────┬────────┬────┬──────────┬────┬────┬────┐
│40  │41  │42  │44      │46  │48        │4A  │4B  │4C  │ Split Space
└────┴────┴────┴────────┴────┴──────────┴────┴────┴────┘
```


// KC_NO used in empty split key options
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSPC, KC_MPLY, KC_VOLU,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, MAC_SEARCH, KC_VOLD,
        CW_TOGG, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, KC_UP,
        KC_LCTL, KC_LGUI, SC_LAPO, KC_NO, KC_SPC, KC_NO, SC_RAPC, MO(1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),                           //space          space
    [1] = LAYOUT_all(
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_DEL, RGB_TOG, KC_MNXT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WSCH, RGB_MOD, KC_MPRV,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LLOCK,
        _______, KC_NO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NO, KC_PGUP,
        _______, _______, _______, KC_NO, _______, KC_NO, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
};

void keyboard_post_init_user(void) {
  // Call the post init code.
  //rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  //rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
  #ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
  rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 2); // sets mode to rainbow swirlwithout saving
  #endif
}