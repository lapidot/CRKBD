#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)
#define KC_CTLDEL CTL_T(KC_DEL)
#define KC_UNDO LCTL(KC_Z)
#define KC_CUT LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PASTE LCTL(KC_V)
#define KC_ALT_TAB LALT(KC_TAB)
#define KC_LANGSWP LALT(KC_LSFT)
#define KC_CTRL_S LCTL_T(KC_S)
#define KC_CTRL_L LCTL_T(KC_L)
#define KC_ALT_D LALT_T(KC_D)
#define KC_ALT_K LALT_T(KC_K)
#define KC_GUI_F LGUI_T(KC_F)
#define KC_GUI_J LGUI_T(KC_J)
#define KC_SHFT_SCL RSFT_T(KC_SCLN)
#define KC_SHFT_A LSFT_T(KC_A)
#define PAR 31
#define CRL 32
#define SQU 33
#define CLS 34
#define SCL 35
#define QUO 36
#define KC_PARAN TD(PAR)
#define KC_CURLY TD(CRL)
#define KC_SQUAR TD(SQU)
#define KC_QUOTA TD(QUO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        ESC,SHFT_A, CTRL_S, ALT_D, GUI_F,     G,                      H, GUI_J, ALT_K, CTRL_L, SHFT_SCL,  QUOTA,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,  BSPC,  CTLDEL,      ENT, SPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
     ALT_TAB, VOLU, 2,     3,     4,     5,                      PLUS,     7,     8,     9,     0,  SLSH,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LANGSWP,VOLD, CURLY, SQUAR, PARAN, XXXXX,                     MINS,    4,    5,    6,   PLUS, ASTR,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,   UNDO, CUT, COPY, PASTE, PSCR,                         0,   1,    2,      3,   MINS, EQL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, BSPC,  CTLDEL,       ENT, DOT, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      CTLTB,  VOLU,  AT,  HASH,   DLR,  PERC,                   CIRC,  HOME, UP,   PGUP,  RPRN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      ESC,  VOLD,  CURLY, SQUAR, PARAN, XXXXX,                   MINS,   LEFT, DOWN, RIGHT,  PIPE,   GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, MUTE, XXXXX, XXXXX, XXXXX, XXXXX,                   UNDS,  END,  DOWN, PGDN,  BSLS,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER, BSPC,   CTLDEL,      ENT, SPC, RAISE \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  MINS,   EQL,  LCBR,  RCBR,  PIPE,   GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  UNDS,  PLUS,  LBRC,  RBRC,  BSLS,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LOWER,  BSPC,  CTLDEL,      ENT, SPC, RAISE \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}



// Shift vs capslock function
void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LSFT);
    } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        register_code (KC_CAPS);
    }
}
void caps_tap_end (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_LSFT);
    } else {
        unregister_code (KC_CAPS);
    }
}

// Parantheses
void paranthesis_dance (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("()"); register_code(KC_LEFT); unregister_code(KC_LEFT);
        } else if (state->count == 2) {
            SEND_STRING("(");
        } else if (state->count == 3) {
            SEND_STRING(")");
    }
}
void curly_dance (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("{}"); register_code(KC_LEFT); unregister_code(KC_LEFT);
        } else if (state->count == 2) {
            SEND_STRING("{");
        } else if (state->count == 3) {
            SEND_STRING("}");
    }
}

void square_dance (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("[]"); register_code(KC_LEFT); unregister_code(KC_LEFT);
        } else if (state->count == 2) {
            SEND_STRING("[");
        } else if (state->count == 3) {
            SEND_STRING("]");
    }
}


enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum {
  SINGLE_TAP_OR_HOLD = 1,
  DOUBLE_TAP_OR_HOLD = 2,
};
typedef struct {
  bool is_press_action;
  int state;
} S_tap;
/*
static xtap xtap_state = {
  .is_press_action = true,
  .state = 0
};*/

///////////////////////////////////////////////end hope
int cur_dance (qk_tap_dance_state_t *state) {
  if ((state->count == 1) && (!state->pressed)) return SINGLE_TAP;
  else if ((state->count == 1) && (state->pressed)) return SINGLE_HOLD;
  else if ((state->count == 2) && (!state->pressed)) return DOUBLE_TAP;
  else if ((state->count == 2) && (state->pressed)) return DOUBLE_HOLD;
  else return 5; //magic number. At some point this method will expand to work for more presses
}



qk_tap_dance_action_t tap_dance_actions[] = {
  [CLS] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end ),
    // Shifting for double quote and semicolon
    [SCL] = ACTION_TAP_DANCE_DOUBLE( KC_SCLN, KC_COLN ),
    [QUO] = ACTION_TAP_DANCE_DOUBLE( KC_QUOT, KC_DQUO),
    // Tap dances for paranthesis, which sends macros
    [PAR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, paranthesis_dance ),
    [CRL] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, curly_dance ),
    [SQU] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, square_dance )
  };
  const uint16_t PROGMEM fn_actions[] = {

};



//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

//const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
//matrix_write_ln(matrix, "DanL4 0536064132");
//matrix_write_ln(matrix, read_host_led_state());
//matrix_write_ln(matrix, read_timelog());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    matrix_write(matrix, read_logo());
    //matrix_write_ln(matrix, read_host_led_state());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

#endif
