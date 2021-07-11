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


#if KEYBOARD_SIDE == MASTER
std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
        KC_Q,  KC_W,    KC_F,    KC_P,    KC_P, 
        KC_A,  KC_S,    KC_R,    KC_T,    KC_G, 
        KC_Z,  KC_X,    KC_C,    KC_V,    KC_D, 
        KC_NO, KC_NO,   KC_NO,   KC_SPC,  KC_BSPC 
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
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B, 
        KC_A,    KC_S,    KC_R,    KC_T,    KC_G,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,
        KC_NO,   KC_NO,   KC_NO,   KC_SPC,  KC_BSPC
    )};
 
void setupKeymap() {
  uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(                                             \
          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      \
          _______, _______, _______, _______, KC_LBRC,    \
          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LPRN,    \
          _______, _______, _______, _______, _______     \
);
  uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(                                           \
          KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  \
          _______, _______, _______, _______, KC_LBRC,  \
          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LPRN,  \
          _______, _______, _______, _______, _______   \
                                                   );
 
  uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(                                            \
          HOME_ADD, WORK_ADD, EMAIL_1, EMAIL_2, _______, \
          _______,  _______,  _______, _______, _______, \
          _______,  _______,  _______, _______, _______, \
          _______,  _______,  _______, _______, _______  \
                                                         );
  /*
   * add the other layers on the regular presses.
   */
  for (int row = 0; row < MATRIX_ROWS; ++row)
  {
    for (int col = 0; col < MATRIX_COLS; ++col)
    {		
      matrix[row][col].addActivation(_LOWER,  Method::PRESS, lower[row][col]);
      matrix[row][col].addActivation(_RAISE,  Method::PRESS, raise[row][col]);
      matrix[row][col].addActivation(_ADJUST, Method::PRESS, adjust[row][col]);
    }
  }
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
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
}

#endif  // left

#if KEYBOARD_SIDE == RIGHT

std::array<std::array<Key, MATRIX_COLS>, MATRIX_ROWS> matrix =
    {KEYMAP(
         KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPACE, 
         KC_U,    KC_I,    KC_O,    KC_P,     KC_MINS, 
         KC_J,    KC_K,    KC_L,    KC_SCOLON,KC_QUOTE,
         KC_BSPC, KC_SPC,  KC_NO,   KC_NO,    KC_NO
    )};

void setupKeymap() {
  uint32_t lower[MATRIX_ROWS][MATRIX_COLS] =
        KEYMAP( \
            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
            _______, _______, KC_INS , _______, KC_MUTE, \
            KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_VOLU, \
            _______, _______, _______, _______, _______  \
);
  uint32_t raise[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(                                            \
          KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
          KC_P7 ,  KC_P8 ,  KC_P9 ,  KC_MINS, KC_UNDS, \
          KC_P4 ,  KC_P5 ,  KC_P6 ,  KC_PLUS, KC_PIPE, \
          KC_P1 ,  KC_P2 ,  _______, _______, _______          \
);
  uint32_t adjust[MATRIX_ROWS][MATRIX_COLS] =
      KEYMAP(                                                 \
          _______, _______, _______, _______,PRINT_BATTERY,  \
          _______, _______, _______, _______, _______,       \
          _______, _______, _______, _______, _______,  \   
          _______, _______, _______, _______, _______  \
);
    /*
     * add the other layers
     */
    for (int row = 0; row < MATRIX_ROWS; ++row)
    {
        for (int col = 0; col < MATRIX_COLS; ++col)
        {
            matrix[row][col].addActivation(_LOWER, Method::PRESS, lower[row][col]);
            matrix[row][col].addActivation(_RAISE, Method::PRESS, raise[row][col]);
            matrix[row][col].addActivation(_ADJUST, Method::PRESS, adjust[row][col]);
        }
    }
}

void process_user_macros(uint16_t macroid)
{	
}

void process_user_layers(uint16_t layermask)
{
    KeyScanner::process_for_tri_layers(_LOWER, _RAISE, _ADJUST);
}

#endif
