/* Copyright 2020 Snipeye
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

enum uno_keycode
{
  UNO = SAFE_RANGE
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _HORSCRL,
    _VERSCRL,
    _TAB,
    _UNDOREDO
};

enum encoder_names {
	_ENCODER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        UNO
    ),
    [1] = LAYOUT(
        UNO
    ),
    [2] = LAYOUT(
        UNO
    ),
    [3] = LAYOUT(
        UNO
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_HORSCRL] =   { ENCODER_CCW_CW(KC_WH_L, KC_WH_R)  },
    [_VERSCRL] =   { ENCODER_CCW_CW(KC_WH_U, KC_WH_D)  },
    [_TAB] =  { ENCODER_CCW_CW(C(KC_PGDN), C(KC_PGUP))  },
    [_UNDOREDO] =  { ENCODER_CCW_CW(C(KC_Z), C(KC_Y))  },
};
#endif

int active_layer = 0;
#define NO_OF_LAYERS 4;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case UNO:
			if (record->event.pressed) {
				// SEND_STRING("Hello!");
                active_layer = (active_layer + 1) % NO_OF_LAYERS;
                layer_move(active_layer);
			}
			break;
			return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(255, 255, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _TAB:
        rgblight_sethsv (HSV_GREEN);
        break;
    case _UNDOREDO:
        rgblight_sethsv (HSV_RED);
        break;
    case _VERSCRL:
        rgblight_sethsv (HSV_PURPLE);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv (HSV_CYAN);
        break;
    }
  return state;
}
