/* Copyright 2023 Brian Low
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

enum layer_names {
    _QW,
    _SM,
    _FN,
};

#define RGUI_SP RGUI_T(KC_SPC)
#define LGUI_SP LGUI_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE, KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LCTL, KC_LGUI, MO(_SM), KC_LALT,  KC_ENT, KC_SPC,  KC_SPC,  KC_RALT, MO(_FN), KC_RCTL
    ),
    [_SM] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                     KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_F12,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, KC_PEQL, KC_PMNS, KC_PPLS, KC_LCBR, KC_RCBR, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                          _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______
    ),
    [_FN] = LAYOUT(
        QK_BOOT, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   _______, KC_PGDN, KC_PGUP, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
    // [___] = LAYOUT(
    //     _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    // ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QW] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_SM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_FN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) }
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QW:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _SM:
            oled_write_ln_P(PSTR("SYMBOL"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("FUNCTION"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
