#pragma once
#include "jack.h"

/* Define the macros (enum variant name, enum value, function to call) */
#define MACRO_TABLE \
	MACRO(MAC_SEARCH, search)\
	MACRO(MAC_TERMINAL, terminal)\
	MACRO(MAC_EDITOR, editor)\
	MACRO(MAC_BROWSER, browser)\
	MACRO(MAC_SCREENSHOT, screenshot)


/* Generate function prototypes */
#define MACRO(a, b) void b(void);
    MACRO_TABLE
#undef MACRO

typedef void (*func_p)(void);
struct action {
  func_p map[LLOCK - SAFE_RANGE];
};
struct action macros;

int KC_isMacro(uint16_t keycode);

void send_macro(uint16_t keycode);
