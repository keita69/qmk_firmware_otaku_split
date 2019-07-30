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

#pragma once

// place overrides here

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

#define RGB_DI_PIN D4
#ifdef RGB_DI_PIN
   #define RGBLED_SPLIT { 7, 14 }    // Number of LEDs ( left, right )
   #define RGBLED_NUM 21
   #define RGBLIGHT_HUE_STEP 8
   #define RGBLIGHT_SAT_STEP 8
   #define RGBLIGHT_VAL_STEP 8
   #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
   #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
 /*== all animations enable ==*/
//   #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
// /*== customize breathing effect ==*/
   /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
   #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
   /*==== use exp() and sin() ====*/
   #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
   #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
 #endif

//#undef RGBLED_NUM
//#define RGBLIGHT_ANIMATIONS
//#define RGBLED_NUM 24
//#define RGBLIGHT_HUE_STEP 10
//#define RGBLIGHT_SAT_STEP 17
//#define RGBLIGHT_VAL_STEP 17

// Configuring mouse keys
// https://docs.qmk.fm/#/feature_mouse_keys
#define MOUSEKEY_DELAY	1
#define MOUSEKEY_INTERVAL	25
#define MOUSEKEY_MAX_SPEED	20
#define MOUSEKEY_TIME_TO_MAX 30

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_TAPPING