#include QMK_KEYBOARD_H
#include <print.h>

extern keymap_config_t keymap_config;

#define L_CURBR LSFT(KC_LBRC)
#define R_CURBR LSFT(KC_RBRC)
#define EMOJI   LCTL(LCMD(KC_SPC))

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,
    GO1 = TO(1),
    GO2 = TO(2),
    GO3 = TO(3),
    MAY2 = TT(2),
    MAY3 = TT(3)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 KC_ESC , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC,
                 KC_TAB , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, GO1    ,
                 KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT,
                                   KC_LCTL, KC_LALT, KC_LCMD, KC_ENT , KC_SPC , KC_RCMD, MAY2   , MAY3
                 ),
    [1] = LAYOUT(
                 _______, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , _______,
                 _______, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, GO2    ,
                 _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
                 ),
    [2] = LAYOUT(
                 _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , _______,
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_QUOT, GO3    ,
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_BSLS, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
                 ),
    [3] = LAYOUT(
                 _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, GO1    ,
                 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, EMOJI  , _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
                 )
//    [?] = LAYOUT(
//                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                 _______, _______, _______, _______, _______, _______, _______, _______
//                 )
};

void _leds_off(void) {
    dprint("turning off all leds\n");
    rgblight_sethsv_noeeprom(0x00, 0x00, 0x00);
}

void _level_1_leds(void) {
    dprint("setting level 1 leds\n");
    rgblight_setrgb_at(0x00, 0x74, 0xd9, 0);
    rgblight_setrgb_at(0x00, 0x00, 0x00, 1);
    rgblight_setrgb_at(0x00, 0x00, 0x00, 2);
};

void _level_2_leds(void) {
    dprint("setting level 2 leds\n");
    rgblight_setrgb_at(0x00, 0x00, 0x00, 0);
    rgblight_setrgb_at(0xf0, 0x12, 0xbe, 1);
    rgblight_setrgb_at(0x00, 0x00, 0x00, 2);
};

void _level_3_leds(void) {
    dprint("setting level 3 leds\n");
    rgblight_setrgb_at(0x00, 0x00, 0x00, 0);
    rgblight_setrgb_at(0x00, 0x00, 0x00, 1);
    rgblight_setrgb_at(0xff, 0x85, 0x1b, 2);
};

void matrix_init_user(void) {
    rgblight_init();
    _leds_off();
    rgblight_mode(1);
};

void keyboard_post_init_user(void) {
    debug_enable=true;
    
    _level_1_leds();
    layer_on(1);
};

void rgblight_init_leds(void) {
    _level_1_leds();
};

void led_set_user(uint8_t usb_led) {
    layer_state_set_user(layer_state);
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case 0:
        dprint("case 0\n");
        break;
    case 1:
        dprint("case 1\n");
        _level_1_leds();
        break;
    case 2:
        dprint("case 2\n");
        _level_2_leds();
        break;
    case 3:
        dprint("case 3\n");
        _level_3_leds();
        break;
    default:
        dprint("case default\n");
        break;
    }
    return state;
}
