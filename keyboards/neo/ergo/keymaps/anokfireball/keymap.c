/*
Copyright 2024 NEO

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

enum __layers {
    WIN_B,
    WIN_U,
    WIN_F,
    MAC_B,
    MAC_U,
    MAC_F
};

// 0: ESC
// 1: 1
// 2: 2
// 3: 3
// 4: 4
// 5: indicator bottom
// 6: indicator middle
// 7: indicator top
// 8: barrier top left
// 9: barrier upper mid left
// 10: barrier lower mid left
// 11: barrier bottom left
// 12: barrier top right
// 13: barrier upper mid right
// 14: barrier lower mid right
// 15: barrier bottom right
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = 0; i < 5; i++) {
        rgb_matrix_set_color(i, RGB_OFF);
    }
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case WIN_B:
        case WIN_U:
        case WIN_F:
            rgb_matrix_set_color(5, RGB_BLUE);
            rgb_matrix_set_color(6, RGB_BLUE);
            rgb_matrix_set_color(7, RGB_BLUE);
            break;
        case MAC_B:
        case MAC_U:
        case MAC_F:
            rgb_matrix_set_color(5, RGB_GREEN);
            rgb_matrix_set_color(6, RGB_GREEN);
            rgb_matrix_set_color(7, RGB_GREEN);
            break;
        default:
            rgb_matrix_set_color(5, RGB_WHITE);
            rgb_matrix_set_color(6, RGB_WHITE);
            rgb_matrix_set_color(7, RGB_WHITE);
            break;
    }
    for (uint8_t i = 8; i < 16; i++) {
        rgb_matrix_set_color(i, RGB_OFF);
    }
    return false;
}

// WIN versions of umlauts and eszett
// works really well with US-International (WIN) and us-acentos (LINUX)
#define WIN_AE   RALT(KC_Q)
#define WIN_OE   RALT(KC_P)
#define WIN_UE   RALT(KC_Y)
#define WIN_SZ   RALT(KC_S)
#define WIN_EUR  RALT(KC_5)
#define WIN_SLP  LWIN(KC_L)
#define WIN_CAPS CTL_T(KC_ESC)
#define WIN_SPC  LT(WIN_U, KC_SPC)

enum custom_keycodes {
    // avoid dead keys
    // only really useful with US-International (WIN)
    WIN_QUOT = SAFE_RANGE,
    WIN_GRV,
    WIN_6,
    // OSX versions of umlauts and eszett
    // works really well with plain US ANSI (OSX)
    MAC_AE,
    MAC_OE,
    MAC_UE,
};

void send_string_(const char *str) {
    // Save the current modifier state to ensure that any active modifiers (e.g., shift, ctrl)
    // are not lost when sending the string. Left-Shift somehow loses its modifier state when
    // SEND_STRING
    uint8_t mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();
    clear_mods();
    clear_oneshot_mods();
    SEND_STRING(str);
    set_mods(mods);
    set_oneshot_mods(oneshot_mods);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const bool shift = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;

    if (record->event.pressed) {
        switch (keycode) {
            case WIN_QUOT:
                if (shift) {
                    send_string_("\" ");
                } else {
                    send_string_("' ");
                }
                return false; // Skip all further processing of this key
            case WIN_GRV:
                if (shift) {
                    send_string_("~ ");
                } else {
                    send_string_("` ");
                }
                return false; // Skip all further processing of this key
            case WIN_6:
                if (shift) {
                    send_string_("^ ");
                } else {
                    send_string_("6");
                }
                return false; // Skip all further processing of this key
            case MAC_AE:
                if (shift) {
                    send_string_(SS_LALT("u") "A");
                } else {
                    send_string_(SS_LALT("u") "a");
                }
                return false; // Skip all further processing of this key
            case MAC_UE:
                if (shift) {
                    send_string_(SS_LALT("u") "U");
                } else {
                    send_string_(SS_LALT("u") "u");
                }
                return false; // Skip all further processing of this key
            case MAC_OE:
                if (shift) {
                    send_string_(SS_LALT("u") "O");
                } else {
                    send_string_(SS_LALT("u") "o");
                }
                return false; // Skip all further processing of this key
        }
    }
    return true; // Process all other keycodes normally
}
#define MAC_SZ   LALT(KC_S)
#define MAC_EUR  LSA(KC_2)
#define MAC_SLP  LCTL(LCMD(KC_Q))
#define MAC_CAPS CMD_T(KC_ESC)

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    KC_RSPC
};

td_state_t cur_dance(tap_dance_state_t *state);

void rspc_finished(tap_dance_state_t *state, void *user_data);
void rspc_reset(tap_dance_state_t *state, void *user_data);


td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    }
    return TD_UNKNOWN;
}

static td_tap_t space_right_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void rspc_finished(tap_dance_state_t *state, void *user_data) {
    bool isWin = false;
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case WIN_B:
        case WIN_U:
        case WIN_F:
            isWin = true;
            break;
        case MAC_B:
        case MAC_U:
        case MAC_F:
            isWin = false;
            break;
        default:
            break;
    }
    space_right_state.state = cur_dance(state);
    switch (space_right_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            if (isWin) {
                layer_on(WIN_U);
            } else {
                layer_on(MAC_U);
            }
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            if (isWin) {

            } else {
                register_code(KC_LCTL);
                register_code(KC_LOPT);
                register_code(KC_LCMD);
            }
            break;
        default:
            break;
    }
}

void rspc_reset(tap_dance_state_t *state, void *user_data) {
    bool isWin = false;
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case WIN_B:
        case WIN_U:
        case WIN_F:
            isWin = true;
            break;
        case MAC_B:
        case MAC_U:
        case MAC_F:
            isWin = false;
            break;
        default:
            break;
    }
    switch (space_right_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            if (isWin) {
                layer_off(WIN_U);
            } else {
                layer_off(MAC_U);
            }
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            if (isWin) {

            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LOPT);
                unregister_code(KC_LCMD);
            }
            break;
        default:
            break;
    }
    space_right_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [KC_RSPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rspc_finished, rspc_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_B] = LAYOUT_hot( /* Base */
        KC_HOME,WIN_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   WIN_6,             KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
        KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_PGDN,WIN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,   KC_L,    KC_SCLN,WIN_QUOT,           KC_ENT,
        KC_END,  KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,
                 KC_LCTL, KC_LGUI,          KC_LALT,          KC_SPC,                          WIN_SPC,            KC_RALT,         MO(WIN_F),KC_RGUI, KC_RCTL
    ),

    [WIN_U] = LAYOUT_hot( /* Umlauts */
        _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  KC_DEL,
        _______, _______, _______, _______, WIN_EUR, _______, _______,                   _______,  WIN_UE, _______,  WIN_OE, _______, _______, _______, _______,
        _______, _______,  WIN_AE,  WIN_SZ, _______, _______, _______,                   KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______,          _______,          _______,                            _______,          _______,          _______, _______, _______
    ),

    [WIN_F] = LAYOUT_hot( /* FN */
        _______, _______, KC_BRID, KC_BRIU, _______, _______, _______, _______,          _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        _______,PDF(MAC_B),_______,_______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,          QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, _______, WIN_SLP,
                 _______, _______,          _______,          RGB_TOG,                            RGB_TOG,          _______,          _______, _______, _______
    ),

    [MAC_B] = LAYOUT_hot( /* Base */
        KC_HOME,  KC_GRV, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,             KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC,
        KC_PGUP,  KC_TAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_PGDN,MAC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,   KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_END,  KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,
                 KC_LCTL, KC_LOPT,          KC_LCMD,          KC_SPC,                          TD(KC_RSPC),        KC_RCMD,         MO(MAC_F),KC_ROPT, KC_RCTL
    ),

    [MAC_U] = LAYOUT_hot( /* Umlauts */
        _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,            KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  KC_DEL,
        _______, _______, _______, _______, MAC_EUR, _______, _______,                   _______,  MAC_UE, _______,  MAC_OE, _______, _______, _______, _______,
        _______, _______,  MAC_AE,  MAC_SZ, _______, _______, _______,                   KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______,
                 _______, _______,          _______,          _______,                            _______,          _______,          _______, _______, _______
    ),

    [MAC_F] = LAYOUT_hot( /* FN */
        _______, _______, KC_BRID, KC_BRIU, _______, _______, _______, _______,          _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        _______,PDF(WIN_B),_______,_______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,          QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, _______, MAC_SLP,
                 _______, _______,          _______,          RGB_TOG,                            RGB_TOG,          _______,          _______, _______, _______
    )
};
