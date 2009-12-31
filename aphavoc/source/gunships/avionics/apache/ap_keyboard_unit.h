/*
 * ap_keyboard_unit.h
 *
 *  Created on: 29.sep.2009
 *      Author: arneh
 */

#ifndef AP_KEYBOARD_UNIT_H_
#define AP_KEYBOARD_UNIT_H_

void enable_apache_keyboard_unit_input(void);

// Does it have keyboard focus?
int apache_keyboard_unit_active(void);

/*
 * Toggles keyboard focus for keyboard unit, and also displays the input window
 * Ensure on makes sure the unit is on, no matter if it had focus previously
 */
void toggle_apache_keyboard_unit_active(int ensure_on);

void update_apache_keyboard_unit(void);

/*
 * Displays the input window in the bottom left corner of screen if it has focus
 */
void draw_apache_keyboard_unit(void);

/*
 * Gives keyboard unit focus and calls the handler function when input is received
 */
void get_apache_keyboard_unit_input(const char* prompt, mfd_locations location, mfd_modes mfd_mode, void (*input_handler_function)(const char* input, mfd_locations location, mfd_modes mfd_mode));

#endif /* AP_KEYBOARD_UNIT_H_ */
