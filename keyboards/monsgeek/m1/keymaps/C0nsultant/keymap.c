/* Copyright (C) 2023 jonylee@hfd
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

#include QMK_KEYBOARD_H

enum __layers {
    WIN_B,
    WIN_U,
    WIN_F,
    MAC_B,
    MAC_U,
    MAC_F
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// WIN versions of umlauts and eszett
// works really well with US-International (WIN) and us-acentos (LINUX)
#define WIN_AE RALT(KC_Q)
#define WIN_OE RALT(KC_P)
#define WIN_UE RALT(KC_Y)
#define WIN_SZ RALT(KC_S)
#define WIN_EUR RALT(KC_5)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT_all( /* Base */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   KC_DEL,           KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,KC_EQL,   KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,KC_RBRC,  KC_BSLS,          KC_PGUP,
       MO(WIN_U),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,KC_NUHS,  KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT,MO(WIN_F),KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_U] = LAYOUT_all( /* Umlauts */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, WIN_EUR, _______, _______, _______, WIN_UE,  _______, WIN_OE,  _______, _______, _______, _______,          _______,
        _______, WIN_AE,  WIN_SZ,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                   _______,                            _______,MO(WIN_F),_______,          _______, _______, _______),

    [WIN_F] = LAYOUT_all( /* FN */
        _______, KC_MYCM, KC_MAIL, KC_WSCH, KC_WHOM, KC_MSEL, KC_MPLY, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______,           RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______,           _______,
        _______, _______,TG(WIN_U),_______, _______, _______, _______, _______, KC_INS, DF(MAC_B),KC_PSCR, _______, _______, RGB_MOD,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______, RGB_MOD, RGB_HUI,           _______,
        _______, _______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______,  RGB_VAI, _______,
        _______, GU_TOGG, _______,                   _______,                            _______, _______, _______,          RGB_SAD,  RGB_VAD, RGB_SAI),

    [MAC_B] = LAYOUT_all( /* Base */
        KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD,KC_VOLU,  KC_DEL,           KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,KC_EQL,   KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,KC_RBRC,  KC_BSLS,          KC_PGUP,
       MO(MAC_U),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,KC_NUHS,  KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI,MO(MAC_F),KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_U] = LAYOUT_all( /* Umlauts */
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                   _______,                            _______,MO(MAC_F),_______,          _______, _______, _______),

    [MAC_F] = LAYOUT_all( /* FN */
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL,            RGB_MOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______,           _______,
        _______, _______,TG(MAC_U),_______, _______, _______, _______, _______, KC_INS, DF(WIN_B),KC_PSCR, _______, _______, RGB_MOD,           _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______, RGB_MOD, RGB_HUI,           _______,
        _______, _______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______,  RGB_VAI, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______,          RGB_SAD,  RGB_VAD, RGB_SAI)
};


// clang-format off
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [WIN_B] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [WIN_U] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [WIN_F] = { ENCODER_CCW_CW(RGB_VAI, RGB_VAD) },
    [MAC_B] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [MAC_U] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [MAC_F] = { ENCODER_CCW_CW(RGB_VAI, RGB_VAD) }
};
#endif

