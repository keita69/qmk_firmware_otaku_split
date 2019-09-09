/* Copyright 2019 takashiski
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
#include <print.h>
#include <stdio.h>
#include <string.h>

static bool lower_pressed = false; 
static bool raise_pressed = false; 

extern keymap_config_t keymap_config;

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

uint16_t key_tap_count = 0;
char key_tap_count_buf[11];

bool is_del_tab_active = false;
uint16_t del_tap_count = 0;
char del_tap_count_buf[11];

// Key Tap Counter
void key_tap_counter(void) {
  key_tap_count++;
}

// Del Tap Counter
void del_tap_counter(void) {
  del_tap_count++;
}

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,

  K8SCTL,
  ALT_TB,
  ESCx2,   // ESC x2
  SD_CBR,  // Surround {}
  SD_CRB,  // Surround []
  SD_PRN,  // Surround ()
  SD_SCLN, // Surround ""
  SD_QUOT, // Surround ''
  SD_GRV3, // Surround ``````
  TAP_CNT  // get key tap count
};

#define EISU   LALT(KC_GRV)
#define CLALDL LCTL(LALT(KC_DEL))  // Crrl+Alt+Del
#define CTL_W  LCTL(KC_W)          // Crrl+W
#define CTLTAB LCTL(KC_TAB)        // Crrl+TAB
#define CTLSTB LCTL(LSFT(KC_TAB))  // Crrl+Shift+TAB
#define WWW_BK KC_WWW_BACK	       // Browser Back (Windows)
#define WWW_FW KC_WWW_FORWARD      // Browser Forward (Windows)
#define GUI_RT LGUI(KC_RGHT)       // Windows+Right
#define GUI_LT LGUI(KC_LEFT)       // Windows+Left
#define GUI_UP LGUI(KC_UP)         // Windows+Up
#define GUI_DW LGUI(KC_DOWN)       // Windows+Down
#define ALTSUP LALT(LSFT(KC_UP))   // ALT+Shift+Up
#define ALTSDN LALT(LSFT(KC_DOWN)) // ALT+Shift+Down
#define ALT_SP LALT(KC_SPC)        // ALT+Space

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /* Qwerty
     * ,----------------------------------------------------------------------------------------------------------------------.
     * | ESCx2|   1  |   2  |   3  |   4  |   5  |   6  ||||||||SD_GRV3|   7  |   8  |   9  |   0  |   -  |   =  |   \  |  `   |
     * |------+------+------+------+------+------+------+--------------+------+------+------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |K8SCTL||||||||   Y   |   U  |   I  |   O  |   P  |   [  |  ]   |    Enter    |
     * |------+------+------+------+------+------+------+--------------+------+------+------+------+------+------+------+      |
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |||||||||||||||||||||||   H  |   J  |   K  |   L  |   ;  |   ;  | Enter|      |
     * |------+------+------+------+------+------+---------------------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |AltSpc|||||||||||||||||||||||   B  |   N  |   M  |   ,  |   .  |   /  | ---- | Shift|
     * |-------------+------+------+------+------+------+------+-------+------|------+------+------+------+------+-------------|
     * | Ctrl | GUI  | Alt  |GUI_LT|AltTab| Lower| Del  |||||||||||||||| Bksp | Raise| EISU | GUI  |GUI_RT|GUI_UP|CLATDL| Ctrl |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
  [_QWERTY] = LAYOUT(
			ESCx2  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   ,      SD_GRV3, KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL  , KC_BSLS, KC_GRV,
			KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , K8SCTL ,      KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC , KC_ENT ,
			KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,               KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT  ,
			KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , ALT_SP ,               KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______ , KC_RSFT,
			KC_LCTL, KC_LGUI, KC_LALT, GUI_LT , ALT_TB , LOWER  , KC_DEL ,      KC_BSPC, RAISE  , EISU   , KC_RGUI, GUI_RT , GUI_UP , CLALDL  , KC_RCTL
  ),
     /* Lower
     * ,----------------------------------------------------------------------------------------------------------------------.
     * | ESCx2|  F1  |  F2  |  F3  |  F4  |  F5  |      ||||||||  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |      |
     * |------+------+------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
     * | Tab  |      |      |      |      |      |      ||||||||      |      |      |      |      |      |      |    Enter    |
     * |------+------+------+------+------+------+------+-------------+------+------+------+------+------+------+------+      |
     * | Ctrl |      |      |      |      |      ||||||||||||||||||||||      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------+------|
     * | Shift|      |      |      |      |      ||||||||||||||||||||||      |      |      |      |      |      |      | Shift|
     * |-------------+------+------+------+------+------+------+------+------|------+------+------+------+------+-------------|
     * | Ctrl | GUI  | Alt  |GUI_UP| Space| Lower| Space||||||||||||||| Bksp | Raise|AltTab| GUI  |GUI_UP|GUI_DW|CLATDL| Ctrl |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
  [_LOWER] = LAYOUT(
			ESCx2  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12  , _______, _______,
			KC_TAB , _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______ , KC_ENT ,
			KC_LCTL, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______ , 
			KC_LSFT, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______ , KC_RSFT,
			KC_LCTL, KC_LGUI, KC_LALT, GUI_UP , KC_SPC , LOWER  , KC_SPC ,      KC_BSPC, RAISE  , ALT_TB , KC_RGUI, GUI_RT , GUI_UP , CLALDL  , KC_RCTL
  ),
     /* Raise
     * ,----------------------------------------------------------------------------------------------------------------------.
     * | ESCx2|  F1  |  F2  |  F3  |  F4  |  F5  |      ||||||||  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |      |      |
     * |------+------+------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
     * | Tab  |      |      |      |      |      |      ||||||||      |MsLeft|MsDown| MsUp |MsRght|MsBtn1|MsBtn2|    Enter    |
     * |------+------+------+------+------+------+------+-------------+------+------+------+------+------+------+------+      |
     * | Ctrl |      |      |      |      |      |||||||||||||||||||||| Left | Down |  Up  | Right| Enter|WinApp|      |      |
     * |------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------+------|
     * | Shift|      |      |      |      |      ||||||||||||||||||||||WhLeft|WhDown| WhUp |WhRght| Home | End  |      | Shift|
     * |-------------+------+------+------+------+------+------+------+------|------+------+------+------+------+-------------|
     * | Ctrl | GUI  | Alt  |    Space    | Lower| Space||||||||||||||| Bksp | Raise|AltTab| GUI  |GUI_UP|GUI_DW|CLATDL| Ctrl |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
  [_RAISE] = LAYOUT(
			ESCx2  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______,      KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12  , _______, _______,
			KC_TAB , _______, _______, _______, _______, _______, _______,      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, _______ , KC_ENT ,
			KC_LCTL, _______, _______, _______, _______, _______,               KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_ENT , KC_APP , _______ ,
			KC_LSFT, _______, _______, _______, _______, _______,               KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_HOME, KC_END , _______ , KC_RSFT,
			KC_LCTL, KC_LGUI, KC_LALT, GUI_UP , KC_SPC , LOWER  , KC_SPC ,      KC_BSPC, RAISE  , ALT_TB , KC_RGUI, GUI_RT , GUI_UP , CLALDL  , KC_RCTL
  ),
      /* Adjust
     * ,----------------------------------------------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      ||||||||      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+-------------+------+------+------+------+------+------+------+------|
     * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      ||||||||      |      |  SAT-|  SAT+|  VAL-|  VAL+|      |             |
     * |------+------+------+------+------+------+------+-------------+------+------+------+------+------+------+------+      |
     * |      |      |      |      |      |      ||||||||||||||||||||||      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      ||||||||||||||||||||||      |      |      |      |      |      |      |      |
     * |-------------+------+------+------+------+------+------+------+------|------+------+------+------+------+-------------|
     * |TAPCNT|      |      |             |      |      |||||||||||||||      |      |      |      |      |      |      |      |
     * ,----------------------------------------------------------------------------------------------------------------------.
     */
  [_ADJUST] = LAYOUT(
			_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______ , _______, _______,
			_______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, _______,      _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______ , _______,
			_______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______ ,
			_______, _______, _______, _______, _______, _______,               _______, _______, _______, _______, _______, _______, _______ , _______,
			TAP_CNT, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______ , _______
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 

  if (record->event.pressed) {
    // tap is twice evnets. events are proessed and release event.
    key_tap_counter();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // http://okapies.hateblo.jp/entry/2019/02/02/133953
        if (lower_pressed) {
          register_code(KC_SPC);
          unregister_code(KC_SPC);
        }
        lower_pressed = true;
      }
 
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // http://okapies.hateblo.jp/entry/2019/02/02/133953
        if (raise_pressed) {
          register_code(KC_ENT);
          unregister_code(KC_ENT);
        }
        lower_pressed = true;
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case SD_CBR:
      if (record->event.pressed) {
        // when keycode this is pressed to surround {}
        SEND_STRING("{");
        SEND_STRING("}");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_CRB:
      if (record->event.pressed) {
        // when keycode this is pressed to surround []
        SEND_STRING("[");
        SEND_STRING("]");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_PRN:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ()
        SEND_STRING("(");
        SEND_STRING(")");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_SCLN:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ""
        SEND_STRING("\"");
        SEND_STRING("\"");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_QUOT:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ''
        SEND_STRING("'");
        SEND_STRING("'");
        SEND_STRING(SS_TAP(X_LEFT));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case SD_GRV3:
      if (record->event.pressed) {
        // when keycode this is pressed to surround ``````
        SEND_STRING(SS_TAP(X_ESCAPE)); // 無変換
        SEND_STRING("```");
        SEND_STRING(SS_TAP(X_ENTER));
        SEND_STRING(SS_TAP(X_ENTER));
        SEND_STRING("```");
        SEND_STRING(SS_TAP(X_UP));
      } else {
        // when keycode this is pressed
      }
      return false;
      break;
    case ESCx2:
      if (record->event.pressed) {
        // when keycode ESC is pressed two times 
        // https://qiita.com/chesscommands/items/ce2883ad0a0c6c27c8de#ss_tap
        // https://github.com/qmk/qmk_firmware/blob/6590f3c81155f5d5cfb59c5b8a28610d6f3207d0/quantum/send_string_keycodes.h
        SEND_STRING(SS_TAP(X_ESCAPE));
        SEND_STRING(SS_TAP(X_ESCAPE));
      } else {
        // when keycode ESC is pressed two times 
      }
      return false;
      break;
   case K8SCTL:
      if (record->event.pressed) {
        // when keycode K8SCTL is pressed
        SEND_STRING("kubectl ");
      } else {
        // when keycode K8SCTL is pressed
      }
      return false;
      break;
   case KC_DEL:
      if (record->event.pressed) {
        // when keycode DEL is pressed
        del_tap_counter();
        SEND_STRING(SS_DOWN(X_DELETE));
      } else {
        // when keycode DEL is released
        SEND_STRING(SS_UP(X_DELETE));
      }
      return false;
      break;
   case KC_BSPC:
      if (record->event.pressed) {
        // when keycode BS is pressed
        del_tap_counter();
        SEND_STRING(SS_DOWN(X_BSPACE));
      } else {
        // when keycode BS is released
        SEND_STRING(SS_UP(X_BSPACE));
      }
      return false;
      break;
   case TAP_CNT:
      if (record->event.pressed) {
        // when keycode TAP_CNT is pressed
        SEND_STRING("total tap : ");
        memset(key_tap_count_buf, 0, sizeof(key_tap_count_buf));
        snprintf(key_tap_count_buf, 11, "%d ", key_tap_count);
        send_string(key_tap_count_buf);

        SEND_STRING("[del/BS ");
        memset(del_tap_count_buf, 0, sizeof(del_tap_count_buf));
        snprintf(del_tap_count_buf, 11, "%d ", del_tap_count);
        send_string(del_tap_count_buf);

        memset(del_tap_count_buf, 0, sizeof(del_tap_count_buf));
        snprintf(del_tap_count_buf, 11, "(%d%%)]", (100 * del_tap_count) / key_tap_count);
        send_string(del_tap_count_buf);

        SEND_STRING(SS_TAP(X_ENTER));
      } else {
        // when keycode TAP_CNT is released
      }
      return false;
      break;
    case ALT_TB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    default:
      if (record->event.pressed) {
        // reset the flag
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}

// static void render_otaku_split_logo(void) {
//   static const char PROGMEM otaku_logo[] = {
//     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
//     0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
//     0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
//   };
//   oled_write_P(otaku_logo, false);
//   oled_scroll_left();
// }

// Super ALT↯TAB
// https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 350) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

void matrix_init_user(void) {
//  render_otaku_split_logo();
}

// Debug
// https://docs.qmk.fm/#/newbs_testing_debugging?id=debugging
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

void led_set_user(uint8_t usb_led) {

}
