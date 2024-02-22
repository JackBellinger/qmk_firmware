#include "macro.h"

bool search(keyrecord_t* record) {
	SEND_STRING(SS_LCTL("c"));
	send_macro(MAC_BROWSER, NULL);
	SEND_STRING(SS_DELAY(200) SS_LCTL("t" "l" "v") SS_TAP(X_ENT));
	return true;
}
bool editor(keyrecord_t* record) {
	SEND_STRING(SS_LGUI("1"));
	return true;
}
bool terminal(keyrecord_t* record) {
	SEND_STRING(SS_LGUI("2"));
	return true;
}
bool browser(keyrecord_t* record) {
	SEND_STRING(SS_LGUI("3"));
	return true;
}
bool blog_url(keyrecord_t* record) {
	SEND_STRING("https://jackbellinger.github.io/blog");
	return true;
}
bool screenshot(keyrecord_t* record) {
	SEND_STRING(SS_LALT(SS_TAP(X_PSCR)) SS_LGUI("r") SS_DELAY(500) "mspaint" SS_TAP(X_ENTER) SS_DELAY(600) SS_LCTL("v"));
	return true;
}

/* Generate function to check if keycode is a macro */
int KC_isMacro(uint16_t keycode) {
	switch (keycode) {
		case MAC_TRUE:
		case MAC_FALSE:
	#define MACRO(a, b) case a:
		MACRO_TABLE
	#undef MACRO
		return 1;
	};
	return 0;
}

bool true_macro(keyrecord_t* record) { return false; }
bool false_macro(keyrecord_t* record) { return false; }

/* Generate Macro keycode to function map*/
struct action macros = {{
	&true_macro,
	#define MACRO(a, b) &b,
		MACRO_TABLE
	#undef MACRO
	&false_macro
}};

bool send_macro(uint16_t keycode, keyrecord_t* record) {
	return macros.map[keycode - MACRO_RANGE_START](record);
}

bool process_macro(uint16_t keycode, keyrecord_t* record) {
	if (KC_isMacro(keycode)) {
		return send_macro(keycode, record);
	}
	return true;
}

/* Key event container for recording */
// typedef struct {
//     keyevent_t event;
//     tap_t tap; //if tap enabled
//     uint16_t keycode; // if combo or repeat key enabled
// } keyrecord_t;

/* key event */
// typedef struct {
//     keypos_t        key;
//     uint16_t        time;
//     keyevent_type_t type;
//     bool            pressed;
// } keyevent_t;

/* key matrix position */
// typedef struct {
//     uint8_t col;
//     uint8_t row;
// } keypos_t;

// typedef enum keyevent_type_t { 
//     TICK_EVENT = 0, 
//     KEY_EVENT = 1, 
//     ENCODER_CW_EVENT = 2, E
//     NCODER_CCW_EVENT = 3, 
//     COMBO_EVENT = 4 
// } keyevent_type_t;

/* tapping count and state */
// typedef struct {
//     bool    interrupted : 1;
//     bool    reserved2 : 1;
//     bool    reserved1 : 1;
//     bool    reserved0 : 1;
//     uint8_t count : 4;
// } tap_t;
