/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  // Layer 0: Root layer
  [0] = LAYOUT_universal(
    KC_Q, KC_W, KC_E, KC_R, KC_T,     KC_Y, KC_U, KC_I, KC_O, KC_P,
    CTL_T(KC_A), KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K, KC_L, RSFT_T(KC_ENT),
    SFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
    KC_LCTL, KC_LSFT, LT(4,KC_LALT), LGUI_T(KC_LNG2), LT(1,KC_SPC), LT(3,KC_TAB),    LT(1,KC_BSPC), RGUI_T(KC_LNG1), XXXXXXX, XXXXXXX, XXXXXXX, LT(3,KC_ESC)
  ),
  // Layer 1: Symbol layer
  [1] = LAYOUT_universal(
    S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),    S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0),
    KC_MINS, S(KC_MINS), KC_LBRC, KC_RBRC, S(KC_QUOT),    S(KC_SCLN), _______, KC_BTN1, KC_BTN2, _______,
    KC_EQL,S(KC_EQL),S(KC_LBRC), S(KC_RBRC), KC_QUOT,    KC_SCLN, KC_GRV, KC_BSLS, _______, _______,
    KC_LSFT, _______, MO(4), _______, _______, _______,    _______, MO(4), XXXXXXX, XXXXXXX, XXXXXXX, _______
  ),
  // Layer 2: Mouse layer
  [2] = LAYOUT_universal(
    KC_PPLS, KC_P7, KC_P8, KC_P9, KC_PAST,    C(KC_UP), SGUI(KC_4), _______, SGUI(KC_5), C(KC_DOWN),
    KC_PMNS, KC_P4, KC_P5, KC_P6, KC_PSLS,    G(KC_LBRC), G(KC_RBRC), KC_BTN1, KC_BTN2, _______,
    KC_P0, KC_P1, KC_P2, KC_P3, KC_PEQL,    KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, _______,
    KC_PDOT, _______, MO(4), _______, _______, _______,    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______
  ),
  // Layer 3: Number layer
  [3] = LAYOUT_universal(
    KC_PPLS, KC_P7, KC_P8, KC_P9, KC_PAST,    C(KC_UP), SGUI(KC_4), _______, SGUI(KC_5), C(KC_DOWN),
    KC_PMNS, KC_P4, KC_P5, KC_P6, KC_PSLS,    G(KC_LBRC), G(KC_RBRC), KC_BTN1, KC_BTN2, _______,
    KC_P0, KC_P1, KC_P2, KC_P3, KC_PEQL,    KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, _______,
    KC_PDOT, _______, MO(4), _______, _______, _______,    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______
  ),
  // Layer 4: Function & Scroll layerk
  [4] = LAYOUT_universal(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,    CPI_D100, CPI_I100, KC_BTN5, KC_BTN4, KBC_SAVE,
    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,    KC_BRMD, KC_BRMU, KC_BTN1, KC_BTN2, AML_TO,
    KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,    KC_KB_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, CPI_D1K, CPI_I1K,
    _______, _______, _______, _______, _______, _______,      _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______
  ),
  // Layer 5: Sub layer
  [5] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  // Auto enable scroll mode when the highest layer is 4
  keyball_set_scroll_mode(get_highest_layer(state) == 4);
  keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);

// Disable auto mouse when the layer is 1
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
  switch (get_highest_layer(remove_auto_mouse_layer(state, true))) {
  case 1:
    state = remove_auto_mouse_layer(state, false);
    set_auto_mouse_enable(false);
    break;
  default:
    set_auto_mouse_enable(true);
    break;
  }
#endif
  return state;
}

#ifdef OLED_ENABLE

#include "custom_oled.c"
#include "lib/oledkit/oledkit.h"

// change OLED rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

// OLED rendering functions
void oledkit_render_info_user(void) {
  // keyball_oled_render_keyinfo();
  // keyball_oled_render_ballinfo();
  // keyball_oled_render_layerinfo();
  keyball_oled_render_custom();
}

void oledkit_render_logo_user(void) { keyball_oled_render_custom_sub(); }

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oledkit_render_info_user();
  } else {
    oledkit_render_logo_user();
  }

  return true;
}

#endif
