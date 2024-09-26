#include QMK_KEYBOARD_H

enum dasbob_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _SUPER,
    _FUNCTION
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_HOLD,
    TD_DOUBLE,
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_ALT_WIN,
    L1_SHFT,
    L2_CTRL,
};

td_state_t cur_dance(tap_dance_state_t *state);

void l1_finished(tap_dance_state_t *state, void *user_data);
void l1_reset(tap_dance_state_t *state, void *user_data);
void l2_finished(tap_dance_state_t *state, void *user_data);
void l2_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT_WIN] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
    [L1_SHFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l1_finished, l1_reset),
    [L2_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l2_finished, l2_reset),
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        return TD_SINGLE_HOLD;
    } else {
        return TD_DOUBLE;
    }

    return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'l1' tap dance.
static td_tap_t l1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Create an instance of 'td_tap_t' for the 'l2' tap dance.
static td_tap_t l2_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void l1_finished(tap_dance_state_t *state, void *user_data) {
    l1_tap_state.state = cur_dance(state);
    switch (l1_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(1);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: register_code(KC_LSFT); break;
        default: break;
    }
}

void l1_reset(tap_dance_state_t *state, void *user_data) {
    switch (l1_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(1);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: unregister_code(KC_LSFT); break;
        default: break;
    }
    l1_tap_state.state = TD_NONE;
}

void l2_finished(tap_dance_state_t *state, void *user_data) {
    l2_tap_state.state = cur_dance(state);
    switch (l2_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(2);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: register_code(KC_LCTL); break;
        default: break;
    }
}

void l2_reset(tap_dance_state_t *state, void *user_data) {
    switch (l2_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(2);
            update_tri_layer(_LOWER, _RAISE, _SUPER);
            break;
        case TD_DOUBLE: unregister_code(KC_LCTL); break;
        default: break;
    }
    l2_tap_state.state = TD_NONE;
}

#define LTZ LT(_FUNCTION, KC_Z)
#define TD1 TD(TD_ALT_WIN)
#define TD2 TD(L1_SHFT)
#define LCT_ENT LCTL_T(KC_ENT)
#define LST_SPC LSFT_T(KC_SPC)
#define TD3 TD(L2_CTRL)
#define KC_NUTL S(KC_NUHS)
#define KC_NUPI S(KC_NUBS)
#define KC_NUAT S(KC_QUOT)
#define KC_TASK C(S(KC_ESC))
#define KC_CAD C(A(KC_DEL))
#define AT_BCK A(S(KC_TAB))
#define AT_FWD A(KC_TAB)
#define TAB_BCK C(S(KC_TAB))
#define TAB_FWD C(KC_TAB)
#define DSK_LFT C(A(KC_LEFT))
#define DSK_RGT C(A(KC_RIGHT))
#define KC_EURO RALT(KC_4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ W │ L │ R │ B │ Z │       │ ; │ Q │ U │ D │ J │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ S │ H │ N │ T │ , │       │ . │ A │ E │ O │ I │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ F │ M │ V │ C │ / │       │ G │ P │ X │ K │ Y │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┐                   ┌───┐
      *           │ALT├───┐           ┌───┤ESC│
      *           └───┤LOW├───┐   ┌───┤RSE├───┘
      *               └───│ENT│   │SPC├───┘
      *                   └───┘   └───┘
      */


    [_QWERTY] = LAYOUT(
    // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
             LTZ,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
    // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                               TD1,     TD2, LCT_ENT,    LST_SPC,     TD3, KC_BSPC
    //                   ╰───────────────────────────╯ ╰──────────────────────────╯
    ),

    [_LOWER] = LAYOUT(
        KC_1,                   KC_2,               KC_3,            KC_4,              KC_5,               S(KC_1),            S(KC_2),        S(KC_3),        S(KC_4),        S(KC_5),
        KC_6,                   KC_7,               KC_8,            KC_9,              KC_0,               S(KC_6),            S(KC_7),        S(KC_8),        KC_QUOT,        KC_NUHS,
        KC_GRV,                 KC_NUBS,            KC_MINS,         KC_EQL,            KC_NUHS,            S(KC_NUHS),         S(KC_EQL),      S(KC_MINS),     S(KC_NUBS),     KC_DEL,
                                                    KC_TRNS,         KC_TRNS,           KC_TRNS,            KC_TRNS,            KC_TRNS,        KC_TAB
    ),

    [_RAISE] = LAYOUT(
        KC_ESC,                 XXXXXXX,            KC_LBRC,         KC_RBRC,           XXXXXXX,            KC_QUOT,            KC_UP,          S(KC_QUOT),     KC_HOME,     KC_PGUP,
        KC_TAB,                 XXXXXXX,            S(KC_9),         S(KC_0),           RALT(KC_4),         KC_LEFT,            KC_DOWN,        KC_RIGHT,       KC_END,      KC_PGDN,
        XXXXXXX,                XXXXXXX,            S(KC_LBRC),      S(KC_RBRC),        XXXXXXX,            XXXXXXX,            XXXXXXX,        XXXXXXX,        XXXXXXX,     KC_BSPC,
                                                    KC_TRNS,         KC_TRNS,           KC_TRNS,            KC_TRNS,            KC_TRNS,        KC_ESC
    ),

    [_SUPER] = LAYOUT(
        C(S(KC_ESC)),  XXXXXXX,       XXXXXXX,         XXXXXXX,          XXXXXXX,            KC_PSCR,         XXXXXXX,        XXXXXXX,          XXXXXXX, C(A(KC_DEL)),
        XXXXXXX,       XXXXXXX,       A(S(KC_TAB)),    A(KC_TAB),        XXXXXXX,            XXXXXXX,         C(G(KC_LEFT)),  C(G(KC_RIGHT)),   XXXXXXX, XXXXXXX,
        XXXXXXX,       XXXXXXX,       C(S(KC_TAB)),    C(KC_TAB),        XXXXXXX,            XXXXXXX,         C(S(KC_TAB)),   C(KC_TAB),        XXXXXXX, XXXXXXX,
                                      KC_TRNS,         KC_TRNS,          KC_TRNS,            KC_TRNS,         KC_TRNS,        KC_TRNS
    ),

    [_FUNCTION] = LAYOUT(
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        KC_F5,          KC_F6,          KC_F7,          KC_F8,          XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        KC_F9,          KC_F10,         KC_F11,         KC_F12,         XXXXXXX,
                                        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS
    ),

};
#ifdef OLED_ENABLE
#include "oled.c"
#endif
