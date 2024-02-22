#pragma once
#include QMK_KEYBOARD_H

typedef enum {
	TURBO = SAFE_RANGE,
	TDM,
	LLOCK,
	MACRO_RANGE_START
} custom_keycodes;

typedef enum {
	ALPHAS,
	FUNCS,
	NAV,
	MATH,
	GAME,
	MIDI
} layers;