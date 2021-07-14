/*
  Copyright 2018 <Pierre Constantineau>

  3-Clause BSD License

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "keymap.h"

#if KEYBOARD_SIDE == SINGLE
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
{KEYMAP(
    KC_1,  KC_2,    KC_3,    KC_4,    KC_5,
    KC_A,  KC_B,    KC_C,    KC_D,    KC_E,
    KC_F,  KC_G,    KC_H,    KC_I,    KC_J,
    KC_K,  KC_L,    KC_M,    KC_N,    KC_O
                                                )};

void setupKeymap() {
  // no layers for master keymap
  // this is a keymap that's used for testing that each key is responding properly to key presses
  // flash this keymap to both left and right to test whether each half works properly.
  // once tested, you can flash the left and right to their respective halves.
}

void process_user_macros(uint16_t macroid)
{
}	

void process_user_layers(uint16_t layermask)
{
}	

#endif

#if KEYBOARD_SIDE == LEFT
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
{KEYMAP(
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO 
        )};

//  _COLEMAK, _SYM, _NAV, _NUM, _MISC
void setupKeymap() {
  uint32_t colemak[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_Q,    KC_W,    KC_F,    KC_P,    KC_B, 
          KC_A,    KC_R,    KC_S,    KC_T,    KC_G,
          KC_Z,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
          KC_NO,   KC_NO,   KC_NO,   KC_SPC,  KC_BSPC
             );
 
  uint32_t sym[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_GT,   KC_RCBR, KC_RBRC, KC_RPRN, KC_BSLASH,
          KC_LT,   KC_LCBR, KC_LBRC, KC_LPRN, KC_SLASH,
          KC_HASH, KC_DLR,  KC_QUES, KC_EXLM, KC_PIPE,
          KC_NO,   KC_NO,   KC_NO,   KC_UNDS, KC_QUOT
                                                          );
     
  uint32_t nav[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_PGUP,   KC_NO,   KC_UP,   KC_NO,    LCTL(KC_GRAVE),
          KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RIGHT, LGUI(KC_GRAVE),
          KC_APP,    KC_HOME, KC_SPC,  KC_END,   LALT(KC_GRAVE),
          KC_NO,     KC_NO,   KC_NO,   KC_LCTL,  KC_LGUI
                                                         );
 
  uint32_t num[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_MINS,   KC_7,   KC_8,  KC_9,    KC_EQL   ,
          KC_KP_PLUS, KC_4,   KC_5,  KC_6,    KC_DOT  ,
          KC_0,       KC_1,   KC_2,  KC_3,    KC_COMMA ,
          KC_NO,      KC_NO,  KC_NO, KC_TRNS, KC_TRNS
                                                         );
  uint32_t misc[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5),
          LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LGUI(KC_9), KC_VOLUP,
          RESET,      KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_VOLDOWN,
          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO
                                                             );
 
   uint32_t tap[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
          KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
          KC_TRNS,    KC_X,      KC_C,      KC_D,      KC_V,
          KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_SPC,   KC_BSPC
                                                             );

   uint32_t hold[MATRIX_ROWS][MATRIX_COLS] =
       KEYMAP(
           KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,    KC_LCTL,   KC_LSFT,   KC_LALT,   KC_LGUI,
           KC_TRNS,    KC_TRNS,   KC_TRNS,   L_NUM,     L_MISC
              );

   
   for (int row = 0; row < MATRIX_ROWS; ++row)
          {
            for (int col = 0; col < MATRIX_COLS; ++col)
            {
              matrix[row][col].addActivation(_COLEMAK, Method::PRESS, colemak[row][col]);
              matrix[row][col].addActivation(_SYM, Method::PRESS, sym[row][col]);
              matrix[row][col].addActivation(_NAV, Method::PRESS, nav[row][col]);
              matrix[row][col].addActivation(_NUM, Method::PRESS, num[row][col]);
              matrix[row][col].addActivation(_MISC, Method::PRESS, misc[row][col]);
              matrix[row][col].addActivation(_COLEMAK, Method::MT_HOLD, hold[row][col]);
              matrix[row][col].addActivation(_COLEMAK, Method::MT_TAP, tap[row][col]);
            }
          }
   COMB(tab,      KC_TAB,        KC_P, KC_B);
   COMB(esc,      KC_ESC,        KC_Q, KC_W);
}

void process_user_macros(uint16_t macroid)
{	  
  switch ((macroid))
  {  
    case HOME_ADD:
      addStringToQueue("123 Quiet Crescent");
      break;
    case WORK_ADD:
      addStringToQueue("123 Work Place");
      break;
    case EMAIL_1:
      addStringToQueue("Primary@Email");
      break;
    case EMAIL_2:
      addStringToQueue("Other@Email");
      break;  
  }
}

void process_user_layers(uint16_t layermask)
{
  // KeyScanner::process_for_tri_layers(_SYM, _NAV, _NUM, _MISC);
}

#endif  // left

#if KEYBOARD_SIDE == RIGHT

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
{KEYMAP(
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,
    KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO 
        )};

void setupKeymap() {
   uint32_t colemak[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_J,    KC_L,    KC_U,    KC_Y,     KC_ENTER, 
          KC_M,    KC_N,    KC_E,    KC_I,     KC_O, 
          KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_NO,
          KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_NO
             );

  uint32_t sym[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_TILD, KC_CIRC, KC_MINS,  KC_PLUS, KC_AT ,
          KC_PERC, KC_ASTR, KC_COLN, KC_SCLN, KC_DQT,
          KC_EQL,  KC_AMPR, KC_DOT,  KC_COMM, KC_QUOT,
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
              );
  uint32_t nav[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_KP_MINUS, KC_P7, KC_P8,  KC_P9, KC_EQL,
          KC_KP_PLUS,  KC_P4, KC_P5,  KC_P6, KC_PDOT,
          KC_P0,   KC_P1, KC_P2,  KC_P3, RESET,
          KC_NO,   KC_NO, KC_NO,  KC_NO, KC_NO
                                                                );
  uint32_t num[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_F1,  KC_F2,   KC_F3, KC_F4,   KC_F5,
          KC_F6,  KC_F7,   KC_F8, KC_F9,   KC_F10,
          RESET,  KC_PSCR, KC_NO, KC_F11,  KC_F12,
          KC_TRNS,KC_TRNS, KC_TRNS, KC_NO, KC_NO
                                                            );
  uint32_t misc[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          LGUI(KC_0), RGB_TOG, RGB_MOD,  RGB_VAI, RGB_M_B,
          KC_NLCK,    KC_LALT, KC_LSFT,  KC_LCTL, KC_MUTE,
          RGB_HUI,    RGB_SAI, RGB_VAI,  KC_NO,   KC_NO,
          KC_NO,      KC_NO,   KC_NO,    KC_NO,   KC_NO
             );


   uint32_t tap[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(
          KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
          KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
          KC_K,       KC_H,      KC_DOT,    KC_COMMA,  KC_SLASH,
          KC_BSPC,    KC_SPC,    KC_TRNS,   KC_TRNS,   KC_TRNS
                                                             );

   uint32_t hold[MATRIX_ROWS][MATRIX_COLS] =
       KEYMAP(
           KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
           KC_LGUI,    KC_LALT,   KC_LSFT,   KC_LCTL,   KC_TRNS,
           L_SYM,      L_NAV,   KC_TRNS,   KC_TRNS,   KC_TRNS
              );

   for (int row = 0; row < MATRIX_ROWS; ++row)
   {
     for (int col = 0; col < MATRIX_COLS; ++col)
     {
       matrix[row][col].addActivation(_COLEMAK, Method::PRESS, colemak[row][col]);
       matrix[row][col].addActivation(_SYM, Method::PRESS, sym[row][col]);
       matrix[row][col].addActivation(_NAV, Method::PRESS, nav[row][col]);
       matrix[row][col].addActivation(_NUM, Method::PRESS, num[row][col]);
       matrix[row][col].addActivation(_MISC, Method::PRESS, misc[row][col]);
       matrix[row][col].addActivation(_COLEMAK, Method::MT_HOLD, hold[row][col]);
       matrix[row][col].addActivation(_COLEMAK, Method::MT_TAP, tap[row][col]);
     }
   }
  
   COMB(del,      KC_DEL,        KC_L, KC_J);
}

      void process_user_macros(uint16_t macroid)
  {	
  }

  void process_user_layers(uint16_t layermask)
  {
    // KeyScanner::process_for_tri_layers(_SYM, _NAV, _NUM, _MISC);
  }

#endif
