#pragma once
#include QMK_KEYBOARD_H


// #include "eeconfig_users.h"
// #include "keyrecords/wrappers.h"
// #include "keyrecords/process_records.h"
// #include "callbacks.h"

typedef enum {
	ALPHAS,
	FUNCS,
	NAV,
	MATH,
	GAME,
	MIDI
} layers;

#include "features/macro.h"
#include "features/layer_lock.h"
#include "features/timer.h"

#ifdef TAP_DANCE_ENABLE
#    include "features/tap_dance.h"
#endif
#ifdef MOUSEKEY_ENABLE
#    include "features/turbo_click.h"
#endif
// #if defined(RGBLIGHT_ENABLE)
// #    include "rgb/rgb_stuff.h"
// #endif
// #if defined(RGB_MATRIX_ENABLE)
// #    include "rgb/rgb_matrix_stuff.h"
// #endif
// #if defined(OLED_ENABLE)
// #    include "oled/oled_stuff.h"
// #endif
// #ifdef SPLIT_KEYBOARD
// #    include "split/transport_sync.h"
// #endif
// #ifdef POINTING_DEVICE_ENABLE
// #    include "pointing/pointing.h"
// #endif
// #ifdef OS_DETECTION_ENABLE
// #    include "os_detection.h"
// #endif
// #ifdef UNICODE_COMMON_ENABLE
// #    include "keyrecords/unicode.h"
// #endif