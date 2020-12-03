/* Copyright 2019 Ryota Goto
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
#include "secret_stuff.h"

#define ENTRY _______
#define UNUSED XXXXXXX
#define PREV KC_MEDIA_PREV_TRACK
#define NEXT KC_MEDIA_NEXT_TRACK
#define PLAY KC_MEDIA_PLAY_PAUSE
#define VOL_UP KC_AUDIO_VOL_UP
#define VOL_DOWN KC_AUDIO_VOL_DOWN
#define MOUSE1 KC_MS_BTN1
#define MOUSE2 KC_MS_BTN2
#define SCROLL_UP KC_WH_U
#define SCROLL_DOWN KC_WH_D

#define CTL_ALT_DEL LCTL(LALT(KC_DEL))

enum layers {
	_DEFAULT = 0,
	_MSPACE, 
	_LCTRL,
	_GAMING,
	_GAMING2,
	_GAMING_PSO2,
	_GAMING_PSO2_2, 
	_FUNCT,
	_RSPACE,
	_RALT,
	_MOUSE_KEYS,
};

/* Custom keycodes that start at the safe range to ensure no overlap with pre-existing keycodes 
Each macro must have a custom keycode */
enum custom_keycodes {
	RIGHT_ARROW = SAFE_RANGE,
	ARROW_FUNC,
	PASSWD_UH,
	PASSWD_KP,
	VERIFY_1,
	VERIFY_2,
	VERIFY_3,
	VERIFY_4,
	SPAM_2
};

uint8_t verified = 0;

/* For processing macros or altercating the function of any existing keycodes */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case RIGHT_ARROW:
			if (record->event.pressed) {
				// when keycode is pressed
				SEND_STRING("->");
			} else {
				// when keycode is released
			} 
			break;
		case ARROW_FUNC:
			if (record->event.pressed) {
				SEND_STRING("=>");
			}
			break;
		case PASSWD_UH:
			if (record->event.pressed) {
				if (verified == KNOCK_SEQ_RESULT) {
					SEND_STRING(PASSWD_STR_1);
				}
			}
			break;
		case PASSWD_KP:
			if (record->event.pressed) {
				if (verified == KNOCK_SEQ_RESULT) {
					SEND_STRING(PASSWD_STR_2);	
				}
			}
			break;
		case VERIFY_1:
			if (record->event.pressed) {
				verified = KNOCK_V1;
			}
			break;
		case VERIFY_2:
			if (record->event.pressed) {
				verified = KNOCK_V2;
			}
			break;
		case VERIFY_3:
			if (record->event.pressed) {
				verified = KNOCK_V3;
			}
			break;
		case VERIFY_4:
			if (record->event.pressed) { 
				verified = KNOCK_V4;
			}
			break;
		case SPAM_2:
			if (record->event.pressed) {
				SEND_STRING(SS_TAP(X_2));
        		_delay_ms(10);
                SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
				SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
				SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
				SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
				SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
				SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
				SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
				SEND_STRING(SS_TAP(X_2));
                _delay_ms(10);
			}
			break;
	}
	return true;
};

/*
    [_LAYER] = LAYOUT_all(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_BSPACE,
    MO(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
    KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,        KC_RSFT, KC_GRAVE,
    KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           KC_SPC,           KC_SPC,                    ENTRY,  KC_RALT,  KC_RGUI, KC_RCTL
    ),
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_DEFAULT] = LAYOUT_all( /* Base */
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL, 
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,       KC_BSPACE,
		LCTL_T(KC_MINS),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                   KC_ENT,
		LSFT_T(KC_EQL), UNUSED, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,        MO(_MOUSE_KEYS), KC_GRAVE,
		MO(_LCTRL), KC_LGUI, KC_LALT,      LSFT_T(KC_SPC),         MO(_MSPACE),           LT(_RSPACE, KC_SPC),            MO(_RALT), KC_RGUI, KC_RALT, KC_RCTL
	),

	[_MSPACE] = LAYOUT_all( 
		KC_GRAVE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, KC_INS,
		_______, RIGHT_ARROW, ARROW_FUNC, KC_LPRN, KC_RPRN, KC_GRAVE, XXXXXXX, S(KC_LBRC), S(KC_RBRC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPACE,
		_______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, XXXXXXX, XXXXXXX,
		_______, UNUSED,XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, KC_COMM, KC_DOT, KC_BSLS, XXXXXXX, XXXXXXX,
		_______, _______, _______,          _______,          ENTRY,          KC_LSFT,                  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
	),

	[_LCTRL] = _LCTRL_CONTENT,

	[_GAMING] = LAYOUT_all(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		KC_LSFT, UNUSED, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, KC_SPC, MO(_GAMING2), LT(_RSPACE, KC_SPC),             KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
	),	

	[_GAMING2] = LAYOUT_all(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX, XXXXXXX, 
		_______, _______, _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, _______, _______, 
		_______, UNUSED, _______, _______, _______, _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, _______, _______,
		_______, _______, _______,    KC_SPC, ENTRY, KC_SPC,            MOUSE1, MOUSE1, MOUSE2, MOUSE2
	),

	[_GAMING_PSO2] = LAYOUT_all(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		KC_LSFT, UNUSED, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, KC_SPC, MO(_GAMING_PSO2_2), LT(_RSPACE, KC_SPC),             KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
	),

	[_GAMING_PSO2_2] = LAYOUT_all(
		KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_PSCR, XXXXXXX, XXXXXXX,
		KC_7, KC_8, _______, KC_9, KC_5, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		KC_0, _______, _______, _______, KC_6, SPAM_2, _______, _______, _______, _______, _______, _______, _______, 
		KC_LSFT, UNUSED, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, KC_SPC, ENTRY, LT(_RSPACE, KC_SPC),             KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
	),

	[_RSPACE] = LAYOUT_all( 
		KC_ESC, KC_MUTE, VOL_DOWN, VOL_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, PREV, PLAY, NEXT, XXXXXXX, XXXXXXX,
		XXXXXXX, C(KC_U), XXXXXXX, KC_PGUP, XXXXXXX, C(KC_UP), XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		KC_LCTL, C(KC_D), KC_HOME, KC_PGDN, KC_END, C(KC_DOWN), XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, XXXXXXX,
		KC_LSFT, UNUSED, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
		XXXXXXX, XXXXXXX, KC_LALT,          _______,          XXXXXXX,          ENTRY,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
	),

	[_RALT] = LAYOUT_all( 
		KC_GRAVE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		LCTL_T(KC_MINS), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		LSFT_T(KC_EQL), UNUSED, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
		XXXXXXX, XXXXXXX, XXXXXXX,          LSFT_T(KC_SPC),          XXXXXXX,          XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
	),

	[_MOUSE_KEYS] = LAYOUT_all( /* Mouse Keys */
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, MOUSE1,  KC_MS_U, MOUSE2, SCROLL_UP, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, KC_MS_L, KC_MS_D, KC_MS_R, SCROLL_DOWN, _______, _______, _______, _______, _______, _______, _______, 
		_______, UNUSED, _______, _______, MOUSE1, MOUSE1, _______, _______, _______, _______, _______, _______, ENTRY, _______,
		_______, _______, _______,          MOUSE1,          MOUSE2,           KC_SPC,                    _______,  _______, _______, _______
	)
};
