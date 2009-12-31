/*
 * ap_keyboard_unit.c
 *
 *  Created on: 29.sep.2009
 *      Author: arneh
 */

#include "project.h"

#include "ap_keyboard_unit.h"

#define MAX_BUFFER_LENGTH 24


static char ku_buffer[MAX_BUFFER_LENGTH];
static unsigned input_length;
static mfd_locations current_location;
static mfd_modes current_mfd_mode;
static const char* prompt = NULL;

static void (*input_handler)(const char*, mfd_locations, mfd_modes);

static unsigned
	keyboard_unit_active;

static event_stack keyboard_unit_event_stack;

int apache_keyboard_unit_active(void)
{
	return keyboard_unit_active;
}

void toggle_apache_keyboard_unit_active(int ensure_on)
{
	if (!keyboard_unit_active)
	{
		if (prompt)
		{
			// Give keyboard focus to input unit
			push_event_overlay_with_stack_item(enable_apache_keyboard_unit_input, NULL, &keyboard_unit_event_stack);
			keyboard_unit_active = TRUE;
		}
	}
	else if (!ensure_on)
	{
		// Removed keyboard focus again
		pop_event_delete(enable_apache_keyboard_unit_input, FALSE);
		keyboard_unit_active = FALSE;

		// Signal the handler that we're done.  No input.
		if (input_handler)
			input_handler(NULL, current_location, current_mfd_mode);

		prompt = NULL;
		input_handler = NULL;
	}
}

void get_apache_keyboard_unit_input(const char* prmt, mfd_locations location, mfd_modes mfd_mode, void (*input_handler_function)(const char* input, mfd_locations location, mfd_modes mfd_mode))
{
	prompt = prmt;
	current_location = location;
	current_mfd_mode = mfd_mode;
	input_handler = input_handler_function;
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

static const char chartable[0x39] = {
	' ',
	' ',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	' ',
	' ',
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'[',
	']',
	' ',
	' ',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	';',
	'\'',
	'`',
	' ',
	' ',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	',',
	'.',
	'/',
	' ',
	' ',
	' ',
};

static const char shifted_chartable[0x39] = {
	' ',
	' ',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'+',
	' ',
	' ',
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'{',
	'}',
	' ',
	' ',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	':',
	'"',
	'~',
	' ',
	' ',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',
	'<',
	'>',
	'?',
	' ',
	' ',
	' ',
};

// Get character from the DIK_* scancodes
static char get_character_from_key(unsigned key, unsigned shifted)
{
	char letter = 0;

	if (key > ARRAY_LENGTH(chartable))
		return 0;

	if (shifted)
		letter = shifted_chartable[key];
	else
		letter = chartable[key];

	return letter;
/*
	HKL layout = GetKeyboardLayout(0);
	static unsigned char keyboard_state[256];
	unsigned vk;
	unsigned short ascii_val;

	if (!GetKeyboardState(keyboard_state))
		return 0;

	vk = MapVirtualKeyEx(key, 1, layout);
	ToAscii(vk, key, keyboard_state, &ascii_val, 0);

	return (char)ascii_val;
*/
}

// Handle a keypress
static void keyboard_unit_input(event* ev)
{
	if (ev->key == DIK_RETURN)
	{
		void (*handler)(const char*, mfd_locations, mfd_modes) = input_handler;
		input_handler = NULL;

		// deactivate keyboard focus first (it is active now)
		// the handler may active it again (for more input), so we need to do this first
		toggle_apache_keyboard_unit_active(FALSE);

		// Input done, signal handler
		if (handler)
			handler(ku_buffer, current_location, current_mfd_mode);

		return;
	}

	if (ev->key == DIK_BACK)
	{
		if (input_length > 0)
		{
			input_length--;
			ku_buffer[input_length] = 0;
		}

		return;
	}

	if (input_length >= MAX_BUFFER_LENGTH)
		return;

	ku_buffer[input_length++] = toupper(get_character_from_key(ev->key, ev->modifier == MODIFIER_LEFT_SHIFT));
	ku_buffer[input_length] = 0;
}

void enable_apache_keyboard_unit_input(void)
{
	unsigned key;

	for (key = DIK_1; key <= DIK_BACK; key++)
		set_event(key, MODIFIER_NONE, KEY_STATE_DOWN, keyboard_unit_input);

	for (key = DIK_Q; key <= DIK_RETURN; key++)
		set_event(key, MODIFIER_NONE, KEY_STATE_DOWN, keyboard_unit_input);

	for (key = DIK_A; key <= DIK_GRAVE; key++)
		set_event(key, MODIFIER_NONE, KEY_STATE_DOWN, keyboard_unit_input);

	for (key = DIK_Z; key <= DIK_SLASH; key++)
		set_event(key, MODIFIER_NONE, KEY_STATE_DOWN, keyboard_unit_input);

	set_event(DIK_SPACE, MODIFIER_NONE, KEY_STATE_DOWN, keyboard_unit_input);

	// shiftet keys
	set_event(DIK_EQUALS, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, keyboard_unit_input);
	set_event(DIK_SEMICOLON, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, keyboard_unit_input);
	set_event(DIK_APOSTROPHE, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, keyboard_unit_input);
	set_event(DIK_COMMA, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, keyboard_unit_input);
	set_event(DIK_PERIOD, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, keyboard_unit_input);
	set_event(DIK_SLASH, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, keyboard_unit_input);

	input_length = 0;
	ku_buffer[input_length] = 0;
}

void draw_apache_keyboard_unit(void)
{
	rgb_colour col, bg_col;
	set_rgb_colour(col, 0, 240, 30, 255);
	set_rgb_colour(bg_col, 0, 40, 10, 255);

	if (keyboard_unit_active)
	{
		int x, y;
		char buffer[80];

		set_ui_font_type (UI_FONT_ARIAL_16);
		set_ui_font_colour (col);

		x = 10;
		y = get_screen_height(active_screen);

		set_block(0, y - 28, 450, y - 1, bg_col);
		sprintf(buffer, "%s> %s", prompt ? prompt : "", ku_buffer);

		ui_display_text (buffer, x, y - 24);
	}
}


void update_apache_keyboard_unit(void)
{

}
