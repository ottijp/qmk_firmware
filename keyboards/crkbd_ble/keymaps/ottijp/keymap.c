/*
Copyright 2019 ottijp

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
#include "app_ble_func.h"

extern keymap_config_t keymap_config;
extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    QWERTY,
    COLEMAK,
    DVORAK,
    LOWER,
    RAISE,
    ADJUST,
    BACKLIT,
    RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                   KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,KC_MINS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                   KC_H,  KC_J,  KC_K,  KC_L,KC_SCLN,KC_QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                   KC_N,  KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RALT \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,                   KC_6,  KC_7,  KC_8,  KC_9,  KC_0,KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL,KC_F11,KC_F12, KC_NO, KC_NO, KC_NO,                 KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_NO,KC_DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LSFT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                  KC_F6, KC_F7, KC_F8, KC_F9,KC_F10,KC_RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RALT \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------.                    ,-----------------------------------------.
     KC_TILD,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,                 KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_GRV,\
  //|------+------+------+------+------+------|                    |------+------+------+------+------+------|
    KC_LCTL,LCTL(KC_1),LCTL(KC_2),LCTL(KC_3),LCTL(KC_4),LCTL(KC_5),KC_PLUS,KC_EQL,KC_LCBR,KC_RCBR,KC_LBRC,KC_RBRC,\
  //|------+------+------+------+------+------|                    |------+------+------+------+------+------|
    KC_LSFT,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO,KC_LABK,KC_RABK,KC_BSLS,KC_PIPE,\
  //|------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER,KC_SPC,       KC_ENT, RAISE,KC_RALT \
                              //`--------------------'      `--------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------.                ,-----------------------------------------.
      RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                AD_WO_L,ADV_ID0,ADV_ID1,ADV_ID2,ADV_ID3,ADV_ID4,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_NO,KC__VOLDOWN,KC__VOLUP,KC__MUTE,KC_NO,KC_NO,         DELBNDS,DEL_ID0,DEL_ID1,DEL_ID2,DEL_ID3,DEL_ID4,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                BATT_LV,ENT_SLP,ENT_DFU,BLE_EN,BLE_DIS,KC_NO,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER,KC_SPC,   KC_ENT, RAISE,KC_RALT \
                              //`--------------------'  `--------------------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  layer_state_set(default_layer);
}

// state for single action
static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    case QWERTY:
      persistent_default_layer_set(1UL<<_QWERTY);
      return false;
    case LOWER:
      lower_pressed = true;
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      return false;
    case RAISE:
      raise_pressed = true;
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      return false;
    case ADJUST:
      layer_on(_ADJUST);
      return false;
    default:
      lower_pressed = false;
      raise_pressed = false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    case LOWER:
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      if (lower_pressed) {
        register_code(KC_LANG2);
        unregister_code(KC_LANG2);
      }
      return false;
    case RAISE:
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
      if (raise_pressed) {
        register_code(KC_LANG1);
        unregister_code(KC_LANG1);
      }
      return false;
    case ADJUST:
      layer_off(_ADJUST);
      return false;
    default:
      lower_pressed = false;
      raise_pressed = false;
    }
  }
  return true;
}
;
