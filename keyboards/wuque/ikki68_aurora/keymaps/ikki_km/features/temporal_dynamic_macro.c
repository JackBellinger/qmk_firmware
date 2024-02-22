// Copyright 2024 Jack Bellinger
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		 https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file temporal_dynamic_macro.c
 * @brief Temporal Dynamic Macro implementation
 *
 * For full documentation, see
 * <https://jackbellinger.github.io/blog/articles/qmk-temporal-dynamic-macro>
 */

#include "features/temporal_dynamic_macro.h"
#include "../custom_keycodes.h"

#if !defined(DEFERRED_EXEC_ENABLE)
#error "temporal_dynamic_macro: Please set `DEFERRED_EXEC_ENABLE = yes` in rules.mk."
#else


/**
 * Record a single key in a dynamic macro.
 *
 * @param macro_buffer[in] The start of the used macro buffer.
 * @param macro_pointer[in,out] The current buffer position.
 * @param macro2_end[in] The end of the other macro.
 * @param direction[in]  Either +1 or -1, which way to iterate the buffer.
 * @param record[in]     The current keypress.
 */
void temporal_dynamic_macro_record_key(keyrecord_t *macro_buffer, keyrecord_t **macro_pointer, keyrecord_t *macro2_end, int8_t direction, keyrecord_t *record) {
    /* If we've just started recording, ignore all the key releases. */
    if (!record->event.pressed && *macro_pointer == macro_buffer) {
        dprintln("dynamic macro: ignoring a leading key-up event");
        return;
    }
	#ifdef TEMPORAL_DYNAMIC_MACRO_SIZE
	if (record.)
	#endif
    /* The other end of the other macro is the last buffer element it
     * is safe to use before overwriting the other macro.
     */
    if (*macro_pointer - direction != macro2_end) {
        **macro_pointer = *record;
        *macro_pointer += direction;
    } else {
        dynamic_macro_record_key_user(direction, record);
    }

    dprintf("dynamic macro: slot %d length: %d/%d\n", DYNAMIC_MACRO_CURRENT_SLOT(), DYNAMIC_MACRO_CURRENT_LENGTH(macro_buffer, *macro_pointer), DYNAMIC_MACRO_CURRENT_CAPACITY(macro_buffer, macro2_end));
}


static deferred_token click_token = INVALID_DEFERRED_TOKEN;
static bool click_registered = false;

// Callback used with deferred execution. It alternates between registering and
// unregistering (pressing and releasing) `MOUSE_TURBO_CLICK_KEY`.
static uint32_t turbo_click_callback(uint32_t trigger_time, void* cb_arg) {
	if (click_registered) {
		unregister_code16(MOUSE_TURBO_CLICK_KEY);
		click_registered = false;
	} else {
		click_registered = true;
		register_code16(MOUSE_TURBO_CLICK_KEY);
	}
	return MOUSE_TURBO_CLICK_PERIOD / 2;	// Execute again in half a period.
}

// Starts Turbo Click, begins the `turbo_click_callback()` callback.
static void turbo_click_start(void) {
	if (click_token == INVALID_DEFERRED_TOKEN) {
		uint32_t next_delay_ms = turbo_click_callback(0, NULL);
		click_token = defer_exec(next_delay_ms, turbo_click_callback, NULL);
	}
}

// Stops Turbo Click, cancels the callback.
static void turbo_click_stop(void) {
	if (click_token != INVALID_DEFERRED_TOKEN) {
		cancel_deferred_exec(click_token);
		click_token = INVALID_DEFERRED_TOKEN;
		if (click_registered) {
			// If `MOUSE_TURBO_CLICK_KEY` is currently registered, release it.
			unregister_code16(MOUSE_TURBO_CLICK_KEY);
			click_registered = false;
		}
	}
}

bool process_temporal_dynamic_macro(uint16_t keycode, keyrecord_t* record, uint16_t turbo_click_keycode) {
	static bool locked = false;
	static bool tapped = false;
	static uint16_t tap_timer = 0;

	if (keycode == tdm_keycode) {
		if (record->event.pressed) {	// Turbo Click key was pressed.
			if (tapped && !timer_expired(record->event.time, tap_timer)) {
				// If the key was recently tapped, lock turbo click.
				locked = true;
				rgblight_mode_noeeprom(RGBLIGHT_MODE_ALTERNATING);
			} else if (locked) {
				// Otherwise if currently locked, unlock and stop.
				locked = false;
				tapped = false;
				turbo_click_stop();
				rgblight_reload_from_eeprom();
				return false;
			}
			// Set that the first tap occurred in a potential double tap.
			tapped = true;
			tap_timer = record->event.time + TAPPING_TERM;

			turbo_click_start();
		} else if (!locked) {
			// If not currently locked, stop on key release.
			turbo_click_stop();
		}

		return false;
	} else {
		// On an event with any other key, reset the double tap state.
		tapped = false;
		return true;
	}
}

#endif