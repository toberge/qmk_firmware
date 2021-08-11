#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

/**
 * Based on this dude's keymap:
 * https://gist.github.com/DavidRambo/09035d4ba5abbd2b319f67951877b5e3
 * And this dude's #defines of norwegian keys
 */

#define ALT_GR(kc) RALT(kc)

// Layer shorthands
#define _MAIN 0
#define _SYMBOL 1
#define _NAV 2
#define _GAME 3
#define _LEFT 4

// Keycode shorthands
#define KC___   KC_TRNS
#define KC____  KC_TRNS
#define KC_MAIN  TO(_MAIN)
#define KC_SYM  MO(_SYMBOL)
#define KC_NAV  MO(_NAV)
#define KC_TNAV LT(_NAV, KC_TAB)
#define KC_GAM  TO(_GAME)

// Text editor shortcuts for NAV
#define KC_AL   LALT(KC_LEFT)
#define KC_AR   LALT(KC_RGHT)
#define KC_CL   LCTL(KC_LEFT)
#define KC_CR   LCTL(KC_RGHT)
#define KC_A_BS LALT(KC_BSPC)
#define KC_C_BS LALT(KC_BSPC)

// Modifier or normal key
#define KC_SUBS  GUI_T(KC_BSPC)
#define KC_CTBS  CTL_T(KC_BSPC)
#define KC_CESC  CTL_T(KC_ESC)
#define KC_C_TAB LCTL(KC_TAB)
#define KC_G_TAB LGUI(KC_TAB)
#define KC_A_TAB LALT(KC_TAB)

// Symbols!
#define KC_FSLH  S(KC_7)         // forward slash
#define KC_BSLH  KC_EQL          // backward slash
#define KC_EQL   S(KC_0)         // =
#define KC_APOS  KC_BSLS         // '
#define KC_QUOT  S(KC_2)         // "
#define KC_HASH  S(KC_3)         // #
#define KC_TIMS  S(KC_BSLS)      // *
#define KC_PLUS  KC_MINS         // +
#define KC_QUES  S(KC_MINS)      // ?
#define KC_PERC  S(KC_5)         // %
#define KC_EXCL  S(KC_1)         // !
#define KC_HAT   S(KC_RBRC)      // ^
#define KC_TILD  ALT_GR(KC_RBRC) // ~
#define KC_COLO  S(KC_DOT)       // ;
#define KC_SEMI  S(KC_COMM)      // ;
#define KC_DASH  KC_SLSH         // -
#define KC_UNDR  S(KC_SLSH)      // _
#define KC_UML   KC_RBRC         // ¨ (umlaut)
#define KC_PIPE  KC_GRV          // |
#define KC_SECT  S(KC_GRV)       // §
#define KC_GRAV  S(KC_EQL)       // `
#define KC_ACUT  ALT_GR(KC_EQL)  // ´

// Norwegian letters!
#define KC_AA KC_LBRC // Å
#define KC_OE KC_SCLN // Ø
#define KC_AE KC_QUOT // Æ

// Brackets!
#define KC_SBRL ALT_GR(KC_8) // [
#define KC_SBRR ALT_GR(KC_9) // ]
#define KC_CBRL ALT_GR(KC_7) // {
#define KC_CBRR ALT_GR(KC_0) // }
#define KC_RBRL S(KC_8)      // (
#define KC_RBRR S(KC_9)      // )
#define KC_ABRL KC_NUBS      // <
#define KC_ABRR S(KC_NUBS)   // >

enum {
    MAIN = 0,
    SYMBOL,
    NAV, // Navigation layer and media controls
    GAME, // Gaming layer with WASD in usable position
    LEFT, // Left-hand writing
    SFT_LCK // tapdance declaration
};

#define KC_SFLK TD(SFT_LCK)     // alias for tapdance

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Main layer with letters, number row and mods
    [_MAIN] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRAV, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,MINS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TNAV, Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  , AA ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CESC, A  , S  , D  , F  , G  ,                H  , J  , K  , L  , OE , AE ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SFLK, Z  , X  , C  , V  , B  ,MUTE,     ENT , K  , M  ,COMM, DOT,SLSH,RSFT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,NAV,CTBS,         SPC, SYM, LALT // shift+space = _ ?
  //                  `----+----+----'        `----+----+----' // see https://www.reddit.com/r/olkb/comments/4u36wk/qmk_question_how_do_i_make_backspace_send_delete/
  ),

  // Symbol layer based on https://www.youtube.com/watch?v=yiwUjLaebuw
  // Add angled brackets where - and _ are now, since those are on main layer?
  // --> whoops, you forgot ? as well...
    [_SYMBOL] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
      F12, F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 , F10, F11,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //| :  |    |    |    |    |    |              |    |    |    |    |    | ;  |
     COLO, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,SEMI,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
  //| <  | $  | +  | (  | )  | @  |              | |  | ?  | =  | _  | *  | >  |
     ABRL, A  , S  , D  , F  , G  ,               PIPE,QUES, EQU,UNDR,APOS,ABRR,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
  //|    | !  | #  | {  | }  | ~  |    |    |    | &  | [  | ]  | %  | ^  |    |
      __ ,EXCL,HASH,CBRL,CBRR,TILD, __ ,      __ ,AMPR,SBRL,CBRL,PERC, HAT, __ ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                        __ , __ , __ ,          __ , __ , __
  //                  `----+----+----'        `----+----+----'
  ),

  // Navigation layer with arrow keys, nav cluster, F keys and homerow mods
    [_NAV] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GAME, F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 , F10, F11,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      __ , __ , __ , __ , __ , __ ,               HOME,PGDN,PGUP, END, __ , F12,
  //|----|----+----+----+----+----+              |----+----+----+----+----+----|
      __ ,LGUI,LALT,LCTL,LSFT, __ ,               LEFT,DOWN, UP ,RGHT, __ , __ ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
      __ , __ , __ , __ , __ , __ , __        __ ,CLFT,CDWN, CUP,CRGT, __ , __ ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                        __ , __ , __ ,          __ , __ , __
  //                  `----+----+----'        `----+----+----'
  ),

  // Gaming layer where left hand is shifted to the right for WASD
    [_GAME] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     MAIN, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  , __ ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      TAB, ESC, Q  , W  , E  , R  ,                Y  , U  , I  , O  , P  , __ ,
  //|----|----+----+----+----+----+              |----+----+----+----+----+----|
      T  ,LSFT, A  , S  , D  , F  ,                H  , J  , K  , L  , T  , __ ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
      M  ,LCTL, Z  , X  , C  , V  , __        __ , N  , M  , G  , B  , __ , __ ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LALT, SPC,          __ , __ , __
  //                  `----+----+----'        `----+----+----'
  ),

  // Alternative gaming layer with nav cluster
    [_NAV_GAME] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GAME, F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 , F10, F11,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
      __ , __ , __ , __ , __ , __ ,               HOME,PGDN,PGUP, END, __ , F12,
  //|----|----+----+----+----+----+              |----+----+----+----+----+----|
      __ ,LGUI,LALT,LCTL,LSFT, __ ,               LEFT,DOWN, UP ,RGHT, __ , __ ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
      __ , __ , __ , __ , __ , __ , __        __ ,CLFT,CDWN, CUP,CRGT, __ , __ ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                        __ , __ , __ ,          __ , __ , __
  //                  `----+----+----'        `----+----+----'

};

// Layer colors
const rgblight_segment_t PROGMEM my_main_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_GOLD}
);
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_RED}
);
const rgblight_segment_t PROGMEM my_gaming_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 12, HSV_PINK}
);

// Layer precedence, later = higher
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    // possible caps lock if you realllly want
    my_main_layer,
    my_nav_layer,
    my_symbol_layer,
    my_gaming_layer
);

//bool led_update_user(led_t led_state) {
//    rgblight_set_layer_state(0, led_state.caps_lock);
//    return true;
//}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_MAIN, layer_state_cmp(state, _MAIN));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_SYMBOL, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_GAME, layer_state_cmp(state, _GAME));
    return state;
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Shift vs. capslock function. From bbaserdem's Planck keymap.
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

qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Shift, twice for Caps Lock
    [SFT_LCK] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end)
};
