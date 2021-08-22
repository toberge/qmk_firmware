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
#define _MEDIA 3
#define _GAME 4
#define _NAV_GAME 5
#define _ARROW_GAME 6

// Keycode shorthands
#define __   KC_TRNS
#define ___  KC_TRNS
#define KC_MAIN TO(_MAIN)
#define KC_SYM  MO(_SYMBOL)
#define KC_NAV  MO(_NAV)
#define KC_MEDI MO(_MEDIA)
#define KC_TNAV LT(_NAV, KC_TAB)
#define KC_GAME TO(_GAME)
#define KC_NGAM TO(_NAV_GAME)
#define KC_AGAM TO(_ARROW_GAME)

// Text editor shortcuts for NAV
#define KC_AL   LALT(KC_LEFT)
#define KC_AR   LALT(KC_RGHT)
#define KC_CLFT LCTL(KC_LEFT)
#define KC_CDWN LCTL(KC_DOWN)
#define KC_CUP  LCTL(KC_UP)
#define KC_CRGT LCTL(KC_RGHT)
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
#define EQUAL    S(KC_0)         // =
#define KC_APOS  KC_BSLS         // '
#define QUOTE    S(KC_2)         // "
#define HASH     S(KC_3)         // #
#define FWDSLSH  S(KC_7)         // /
#define KC_TIMS  S(KC_BSLS)      // *
#define PLUS     KC_MINS         // +
#define PLUSMIN  ALT_GR(KC_MINS) // ±
#define QUESTIN  S(KC_MINS)      // ?
#define KC_DOLA  ALT_GR(KC_4)    // $
#define KC_ALPH  ALT_GR(KC_2)    // @
#define PERCENT  S(KC_5)         // %
#define KC_EXCL  S(KC_1)         // !
#define KC_HAT   S(KC_RBRC)      // ^
#define TILDE    ALT_GR(KC_RBRC) // ~
#define KC_COLO  S(KC_DOT)       // ;
#define KC_SEMI  S(KC_COMM)      // ;
#define KC_DASH  KC_SLSH         // -
#define KC_UNDR  S(KC_SLSH)      // _
#define KC_UML   KC_RBRC         // ¨ (umlaut)
#define PIPE     KC_GRV          // |
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

// Keyboard setting aliases
#define BREATHE RGB_MODE_BREATHE
#define SWIRL   RGB_MODE_SWIRL


enum {
    MAIN = 0,
    SYMBOL,
    NAV, // Navigation layer and media controls
    MEDIA, // Layer for media keys and kb controls
    GAME, // Gaming layer with WASD in usable position
    NAV_GAME, // Gaming layer with nav cluster
    ARROW_GAME, // Gaming layer with arrow keys
    // SFT_LCK // tapdance declaration
};

//#define KC_SFLK TD(SFT_LCK)     // alias for tapdance

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Main layer with letters, number row and mods
    [_MAIN] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
      KC_GRV, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
      KC_TAB, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                      KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  , KC_AA ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_CESC, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                      KC_H  , KC_J  , KC_K  , KC_L  , KC_OE , KC_AE ,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_MUTE,     KC_BSPC, KC_N  , KC_M  ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,
  //`-------+-------+-------+-----+-+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                   KC_LGUI, KC_NAV, KC_ENT,          KC_SPC , KC_SYM,KC_LALT
  //                              `-------+-------+-------'        `--------+-------+-------'
  ),

  // Symbol layer based on https://www.youtube.com/watch?v=yiwUjLaebuw
  // Has number row 1u above home row, and symbols on remaining rows
  // Upper row contains ALT_GR of number row, to ease transition from full keyboard, and some added symbols
    [_SYMBOL] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
  //|       |   ±   |   @   |   ¨   |   $   |   ~   |                    |   `   |   {   |   [   |   ]   |   }   |       |
       ___  ,PLUSMIN,KC_ALPH, KC_UML,KC_DOLA, TILDE ,                     KC_GRAV,KC_CBRL,KC_SBRL,KC_SBRR,KC_CBRR,  ___  ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
  //|   ^   |       |       |       |       |       |                    |       |       |       |       |       |   \`  |
      KC_HAT, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  , KC_EQL,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
  //|   <   |   +   |   '   |   (   |   )   |   @   |                    |   |   |   /   |   =   |   "   |   *   |   >   |
     KC_ABRL,  PLUS ,KC_APOS,KC_RBRL,KC_RBRR,KC_ALPH,                       PIPE ,FWDSLSH, EQUAL , QUOTE ,KC_TIMS,KC_ABRR,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
  //|       |   !   |   #   |   {   |   }   |   ?   |       |    |       |   &   |   [   |   ]   |   %   |   $   |       |
       ___  ,KC_EXCL,  HASH ,KC_CBRL,KC_CBRR,QUESTIN,  ___  ,       ___  ,KC_AMPR,KC_SBRL,KC_SBRR,PERCENT,KC_DOLA,  ___  ,
  //`-------+-------+-------+-----+-+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                     ___  ,KC_MEDI,  ___  ,           ___   ,  ___  ,  ___
  //                              `-------+-------+-------'        `--------+-------+-------'
  ),

  // Navigation layer with arrow keys, nav cluster, F keys and homerow mods
    [_NAV] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
      RESET , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                      KC_F6 , KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
       ___  , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                       ___  ,KC_HOME,KC_PGDN,KC_PGUP, KC_END, KC_F12,
  //|-------|-------+-------+-------+-------+-------+                    |-------+-------+-------+-------+-------+-------|
     KC_GAME,KC_LGUI,KC_LALT,KC_LCTL,KC_LSFT,  ___  ,                       ___  ,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,  ___  ,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,      KC_DEL,KC_PSCR,KC_CLFT,KC_CDWN, KC_CUP,KC_CRGT,  ___  ,
  //`-------+-------+-------+-----+-+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                     ___  ,  ___  ,  ___  ,           ___   ,KC_MEDI,  ___
  //                              `-------+-------+-------'        `--------+-------+-------'
  ),

  // Layer for media keys and keyboard controls
  // Get here by holding both NAV and SYM
    [_MEDIA] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
      RESET , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                      KC_F6 , KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
       ___  ,BREATHE,RGB_VAI,  ___  ,  ___  ,KC_BRIU,                     KC_VOLU,  ___  ,KC_MSTP,  ___  ,  ___  , KC_F12,
  //|-------|-------+-------+-------+-------+-------+                    |-------+-------+-------+-------+-------+-------|
     KC_GAME,RGB_TOG,RGB_VAD,  ___  ,KC_CALC,KC_BRID,                     KC_VOLD,KC_MPRV,KC_MPLY,KC_MNXT,  ___  ,KC_GAME,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
       ___  , SWIRL ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,
  //`-------+-------+-------+-----+-+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                     ___  ,  ___  ,  ___  ,           ___   ,  ___  ,  ___
  //                              `-------+-------+-------'        `--------+-------+-------'
  ),

  // Gaming layer where left hand is shifted to the right for WASD
    [_GAME] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_MAIN, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                      KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,  ___  ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
      KC_TAB, KC_ESC, KC_Q  , KC_W  , KC_E  , KC_R  ,                      KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,  ___  ,
  //|-------|-------+-------+-------+-------+-------+                    |-------+-------+-------+-------+-------+-------|
      KC_T  ,KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  ,                      KC_H  , KC_J  , KC_K  , KC_L  , KC_T  ,KC_NGAM,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
      KC_M  ,KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  ,  ___  ,       ___  , KC_N  , KC_M  , KC_G  , KC_B  ,  ___  ,KC_AGAM,
  //`-------+-------+-------+-----+-+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                   KC_LGUI,KC_LALT, KC_SPC,         KC_ENT  ,  ___  ,  ___
  //                              `-------+-------+-------'        `--------+-------+-------'
  ),

  // Alternative gaming layer with nav cluster
    [_NAV_GAME] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,                       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,                       ___  , KC_INS,KC_HOME,KC_PGUP,  ___  ,  ___  ,
  //|-------|-------+-------+-------+-------+-------+                    |-------+-------+-------+-------+-------+-------|
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,                       ___  , KC_DEL, KC_END,KC_PGDN,  ___  ,KC_GAME,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,
  //`-------+-------+-------+---+---+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                   ___  ,  ___  ,   ___   ,           ___   ,  ___  ,  ___
  //                            `-------+-------+---------'        `--------+-------+-------'
  ),

  // Alternative gaming layer with arrow keys
    [_ARROW_GAME] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,                       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,                       ___  ,  ___  , KC_UP ,  ___  ,  ___  ,  ___  ,
  //|-------|-------+-------+-------+-------+-------+                    |-------+-------+-------+-------+-------+-------|
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,                       ___  ,KC_LEFT,KC_DOWN,KC_RGHT,  ___  ,KC_NGAM,
  //|-------+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,       ___  ,  ___  ,  ___  ,  ___  ,  ___  ,  ___  ,KC_GAME,
  //`-------+-------+-------+---+---+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                   ___  ,  ___  ,   ___   ,           ___   ,  ___  ,  ___
  //                            `-------+-------+---------'        `--------+-------+-------'
  ),

};

// Rotary encoder(s)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // First encoder is volume control,
        // mute on press.
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

// Combos
const uint16_t PROGMEM f11_combo[] = {KC_9, KC_0, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(f11_combo, KC_F11)};

#define GOLD 36, 255, 200
#define CYAN 128, 255, 180
#define RED 0, 255, 200
#define GREEN 85, 255, 200
#define PURPLE 191, 255, 200
#define PINK 234, 128, 200

// Layer colors
const rgblight_segment_t PROGMEM my_main_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, GOLD}
);
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, PINK}
);
const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, CYAN}
);
const rgblight_segment_t PROGMEM my_media_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, PURPLE}
);
const rgblight_segment_t PROGMEM my_gaming_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, PURPLE}
);

// Layer precedence, later = higher
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    // possible caps lock if you realllly want
    my_main_layer,
    my_symbol_layer,
    my_nav_layer,
    my_media_layer,
    my_gaming_layer
);

//bool led_update_user(led_t led_state) {
//    rgblight_set_layer_state(0, led_state.caps_lock);
//    return true;
//}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_MAIN, layer_state_cmp(state, _MAIN));
    rgblight_set_layer_state(_GAME, layer_state_cmp(state, _GAME));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_SYMBOL, layer_state_cmp(state, _SYMBOL));
    rgblight_set_layer_state(_NAV, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(_MEDIA, layer_state_cmp(state, _MEDIA));
    rgblight_set_layer_state(_GAME, layer_state_cmp(state, _GAME));
    rgblight_set_layer_state(_GAME, layer_state_cmp(state, _NAV_GAME));
    rgblight_set_layer_state(_GAME, layer_state_cmp(state, _ARROW_GAME));
    return state;
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Shift vs. capslock function. From bbaserdem's Planck keymap.
//void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
//    if (state->count == 1) {
//        register_code (KC_LSFT);
//    } else if (state->count == 2) {
//        unregister_code (KC_LSFT);
//        register_code (KC_CAPS);
//    }
//}
//void caps_tap_end (qk_tap_dance_state_t *state, void *user_data) {
//    if (state->count == 1) {
//        unregister_code (KC_LSFT);
//    } else {
//        unregister_code (KC_CAPS);
//    }
//}
//
//qk_tap_dance_action_t tap_dance_actions[] = {
//    //Tap once for Shift, twice for Caps Lock
//    [SFT_LCK] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end)
//};
