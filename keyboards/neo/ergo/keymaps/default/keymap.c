// Copyright 2024 Fabian Koller (@anokfireball)
// SPDX-License-Identifier: GPL-2.0-or-later

// Placeholder keymap so the board carries a buildable `default` target.
// The real keymaps live in the external QMK userspace repository
// (github.com/anokfireball/qmk_userspace, keymap `anokfireball`).

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_hot(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,       KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO,          KC_NO,          KC_NO,                   KC_NO,          KC_NO,  KC_NO,  KC_NO, KC_NO
    )
};
// clang-format on
