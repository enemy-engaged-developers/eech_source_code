//
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
//
// 	 Please see the document LICENSE.TXT for the full licence agreement
//
// 2. LICENCE
//  2.1
//  	Subject to the provisions of this Agreement we now grant to you the
//  	following rights in respect of the Source Code:
//   2.1.1
//   	the non-exclusive right to Exploit  the Source Code and Executable
//   	Code on any medium; and
//   2.1.2
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
//
// 3. GENERAL OBLIGATIONS
//  3.1
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5
// 	not to place any restrictions on the operability of the Source
// 	Code;
//   3.1.6
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
//



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char dinput_to_ascii_table [256];

char dinput_to_ascii_upper_table [256];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_dinput_to_ascii_conversion_table (void)
{

	int
		loop;

	//
	// Lowercase characters
	//

	for (loop = 0; loop < sizeof (dinput_to_ascii_table); loop ++)
	{

		dinput_to_ascii_table [loop] = loop;
	}

	dinput_to_ascii_table [DIK_BACK] = 8;
	dinput_to_ascii_table [DIK_ESCAPE] = 27;
	dinput_to_ascii_table [DIK_RETURN] = 13;

	dinput_to_ascii_table [DIK_1] = '1';
	dinput_to_ascii_table [DIK_2] = '2';
	dinput_to_ascii_table [DIK_3] = '3';
	dinput_to_ascii_table [DIK_4] = '4';
	dinput_to_ascii_table [DIK_5] = '5';
	dinput_to_ascii_table [DIK_6] = '6';
	dinput_to_ascii_table [DIK_7] = '7';
	dinput_to_ascii_table [DIK_8] = '8';
	dinput_to_ascii_table [DIK_9] = '9';
	dinput_to_ascii_table [DIK_0] = '0';
	dinput_to_ascii_table [DIK_MINUS] = '-';
	dinput_to_ascii_table [DIK_EQUALS] = '=';
	dinput_to_ascii_table [DIK_TAB] = '	';
	dinput_to_ascii_table [DIK_Q] = 'Q';
	dinput_to_ascii_table [DIK_W] = 'W';
	dinput_to_ascii_table [DIK_E] = 'E';
	dinput_to_ascii_table [DIK_R] = 'R';
	dinput_to_ascii_table [DIK_T] = 'T';
	dinput_to_ascii_table [DIK_Y] = 'Y';
	dinput_to_ascii_table [DIK_U] = 'U';
	dinput_to_ascii_table [DIK_I] = 'I';
	dinput_to_ascii_table [DIK_O] = 'O';
	dinput_to_ascii_table [DIK_P] = 'P';
	dinput_to_ascii_table [DIK_LBRACKET] = '[';
	dinput_to_ascii_table [DIK_RBRACKET] = ']';
	dinput_to_ascii_table [DIK_A] = 'A';
	dinput_to_ascii_table [DIK_S] = 'S';
	dinput_to_ascii_table [DIK_D] = 'D';
	dinput_to_ascii_table [DIK_F] = 'F';
	dinput_to_ascii_table [DIK_G] = 'G';
	dinput_to_ascii_table [DIK_H] = 'H';
	dinput_to_ascii_table [DIK_J] = 'J';
	dinput_to_ascii_table [DIK_K] = 'K';
	dinput_to_ascii_table [DIK_L] = 'L';
	dinput_to_ascii_table [DIK_SEMICOLON] = ';';
	dinput_to_ascii_table [DIK_APOSTROPHE] = '\'';
	dinput_to_ascii_table [DIK_GRAVE] = '`';
	dinput_to_ascii_table [DIK_BACKSLASH] = '\\';
	dinput_to_ascii_table [DIK_Z] = 'Z';
	dinput_to_ascii_table [DIK_X] = 'X';
	dinput_to_ascii_table [DIK_C] = 'C';
	dinput_to_ascii_table [DIK_V] = 'V';
	dinput_to_ascii_table [DIK_B] = 'B';
	dinput_to_ascii_table [DIK_N] = 'N';
	dinput_to_ascii_table [DIK_M] = 'M';
	dinput_to_ascii_table [DIK_COMMA] = ',';
	dinput_to_ascii_table [DIK_PERIOD] = '.';
	dinput_to_ascii_table [DIK_SLASH] = '/';
	dinput_to_ascii_table [DIK_MULTIPLY] = '*';
	dinput_to_ascii_table [DIK_SPACE] = ' ';
	dinput_to_ascii_table [DIK_NUMPAD7] = '7';
	dinput_to_ascii_table [DIK_NUMPAD8] = '8';
	dinput_to_ascii_table [DIK_NUMPAD9] = '9';
	dinput_to_ascii_table [DIK_SUBTRACT] = '-';
	dinput_to_ascii_table [DIK_NUMPAD4] = '4';
	dinput_to_ascii_table [DIK_NUMPAD5] = '5';
	dinput_to_ascii_table [DIK_NUMPAD6] = '6';
	dinput_to_ascii_table [DIK_ADD] = '+';
	dinput_to_ascii_table [DIK_NUMPAD1] = '1';
	dinput_to_ascii_table [DIK_NUMPAD2] = '2';
	dinput_to_ascii_table [DIK_NUMPAD3] = '3';
	dinput_to_ascii_table [DIK_NUMPAD0] = '0';
	dinput_to_ascii_table [DIK_DECIMAL] = '.';
	dinput_to_ascii_table [DIK_NUMPADEQUALS] = '=';
	dinput_to_ascii_table [DIK_CIRCUMFLEX] = '~';
	dinput_to_ascii_table [DIK_COLON] = ':';
	dinput_to_ascii_table [DIK_UNDERLINE] = '_';
	dinput_to_ascii_table [DIK_STOP] = '.';
	dinput_to_ascii_table [DIK_DIVIDE] = '/';

	//
	// Uppercase characters
	//

	for (loop = 0; loop < sizeof (dinput_to_ascii_table); loop ++)
	{

		dinput_to_ascii_upper_table [loop] = loop;
	}

	dinput_to_ascii_upper_table [DIK_BACK] = 8;
	dinput_to_ascii_upper_table [DIK_ESCAPE] = 27;
	dinput_to_ascii_upper_table [DIK_RETURN] = 13;

	dinput_to_ascii_upper_table [DIK_1] = '!';
	dinput_to_ascii_upper_table [DIK_2] = '"';
	dinput_to_ascii_upper_table [DIK_3] = '£';
	dinput_to_ascii_upper_table [DIK_4] = '$';
	dinput_to_ascii_upper_table [DIK_5] = '%';
	dinput_to_ascii_upper_table [DIK_6] = '^';
	dinput_to_ascii_upper_table [DIK_7] = '&';
	dinput_to_ascii_upper_table [DIK_8] = '*';
	dinput_to_ascii_upper_table [DIK_9] = '(';
	dinput_to_ascii_upper_table [DIK_0] = ')';
	dinput_to_ascii_upper_table [DIK_MINUS] = '_';
	dinput_to_ascii_upper_table [DIK_EQUALS] = '+';
	dinput_to_ascii_upper_table [DIK_TAB] = '	';
	dinput_to_ascii_upper_table [DIK_Q] = 'Q';
	dinput_to_ascii_upper_table [DIK_W] = 'W';
	dinput_to_ascii_upper_table [DIK_E] = 'E';
	dinput_to_ascii_upper_table [DIK_R] = 'R';
	dinput_to_ascii_upper_table [DIK_T] = 'T';
	dinput_to_ascii_upper_table [DIK_Y] = 'Y';
	dinput_to_ascii_upper_table [DIK_U] = 'U';
	dinput_to_ascii_upper_table [DIK_I] = 'I';
	dinput_to_ascii_upper_table [DIK_O] = 'O';
	dinput_to_ascii_upper_table [DIK_P] = 'P';
	dinput_to_ascii_upper_table [DIK_LBRACKET] = '{';
	dinput_to_ascii_upper_table [DIK_RBRACKET] = '}';
	dinput_to_ascii_upper_table [DIK_A] = 'A';
	dinput_to_ascii_upper_table [DIK_S] = 'S';
	dinput_to_ascii_upper_table [DIK_D] = 'D';
	dinput_to_ascii_upper_table [DIK_F] = 'F';
	dinput_to_ascii_upper_table [DIK_G] = 'G';
	dinput_to_ascii_upper_table [DIK_H] = 'H';
	dinput_to_ascii_upper_table [DIK_J] = 'J';
	dinput_to_ascii_upper_table [DIK_K] = 'K';
	dinput_to_ascii_upper_table [DIK_L] = 'L';
	dinput_to_ascii_upper_table [DIK_SEMICOLON] = ':';
	dinput_to_ascii_upper_table [DIK_APOSTROPHE] = '\'';
	dinput_to_ascii_upper_table [DIK_GRAVE] = '`';
	dinput_to_ascii_upper_table [DIK_BACKSLASH] = '\\';
	dinput_to_ascii_upper_table [DIK_Z] = 'Z';
	dinput_to_ascii_upper_table [DIK_X] = 'X';
	dinput_to_ascii_upper_table [DIK_C] = 'C';
	dinput_to_ascii_upper_table [DIK_V] = 'V';
	dinput_to_ascii_upper_table [DIK_B] = 'B';
	dinput_to_ascii_upper_table [DIK_N] = 'N';
	dinput_to_ascii_upper_table [DIK_M] = 'M';
	dinput_to_ascii_upper_table [DIK_COMMA] = '<';
	dinput_to_ascii_upper_table [DIK_PERIOD] = '>';
	dinput_to_ascii_upper_table [DIK_SLASH] = '\?';
	dinput_to_ascii_upper_table [DIK_MULTIPLY] = '*';
	dinput_to_ascii_upper_table [DIK_SPACE] = ' ';
	dinput_to_ascii_upper_table [DIK_NUMPAD7] = '7';
	dinput_to_ascii_upper_table [DIK_NUMPAD8] = '8';
	dinput_to_ascii_upper_table [DIK_NUMPAD9] = '9';
	dinput_to_ascii_upper_table [DIK_SUBTRACT] = '-';
	dinput_to_ascii_upper_table [DIK_NUMPAD4] = '4';
	dinput_to_ascii_upper_table [DIK_NUMPAD5] = '5';
	dinput_to_ascii_upper_table [DIK_NUMPAD6] = '6';
	dinput_to_ascii_upper_table [DIK_ADD] = '+';
	dinput_to_ascii_upper_table [DIK_NUMPAD1] = '1';
	dinput_to_ascii_upper_table [DIK_NUMPAD2] = '2';
	dinput_to_ascii_upper_table [DIK_NUMPAD3] = '3';
	dinput_to_ascii_upper_table [DIK_NUMPAD0] = '0';
	dinput_to_ascii_upper_table [DIK_DECIMAL] = '.';
	dinput_to_ascii_upper_table [DIK_NUMPADEQUALS] = '=';
	dinput_to_ascii_upper_table [DIK_CIRCUMFLEX] = '~';
	dinput_to_ascii_upper_table [DIK_COLON] = ':';
	dinput_to_ascii_upper_table [DIK_UNDERLINE] = '_';
	dinput_to_ascii_upper_table [DIK_STOP] = '.';
	dinput_to_ascii_upper_table [DIK_DIVIDE] = '/';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char dinput_to_ascii (int dinput_code)
{

	return dinput_to_ascii_table [dinput_code];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char dinput_to_upper_ascii (int dinput_code)
{

	return dinput_to_ascii_upper_table [dinput_code];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ascii_to_dinput (int ascii_code)
{

	int
		loop;

	for (loop = 0; loop < sizeof (dinput_to_ascii_table); loop ++)
	{

		if (dinput_to_ascii_table [loop] == ascii_code)
		{

			return loop;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*dik_names [] =
	{
		"NONE",
		"ESCAPE",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"MINUS",
		"EQUALS",
		"BACK",
		"TAB",
		"Q",
		"W",
		"E",
		"R",
		"T",
		"Y",
		"U",
		"I",
		"O",
		"P",
		"LBRACKET",
		"RBRACKET",
		"RETURN",
		"LCONTROL",
		"A",
		"S",
		"D",
		"F",
		"G",
		"H",
		"J",
		"K",
		"L",
		"SEMICOLON",
		"APOSTROPHE",
		"GRAVE",
		"LSHIFT",
		"BACKSLASH",
		"Z",
		"X",
		"C",
		"V",
		"B",
		"N",
		"M",
		"COMMA",
		"PERIOD",
		"SLASH",
		"RSHIFT",
		"MULTIPLY",
		"LALT",
		"SPACE",
		"CAPITAL",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"NUMLOCK",
		"SCROLL",
		"NUMPAD7",
		"NUMPAD8",
		"NUMPAD9",
		"SUBTRACT",
		"NUMPAD4",
		"NUMPAD5",
		"NUMPAD6",
		"ADD",
		"NUMPAD1",
		"NUMPAD2",
		"NUMPAD3",
		"NUMPAD0",
		"DECIMAL",
		"F11",
		"F12",

		"F13",
		"F14",
		"F15",

		"KANA",
		"CONVERT",
		"NOCONVERT",
		"YEN",
		"NUMPADEQUALS",
		"CIRCUMFLEX",
		"AT",
		"COLON",
		"UNDERLINE",
		"KANJI",
		"STOP",
		"AX",
		"UNLABELED",
		"NUMPADENTER",
		"RCONTROL",
		"NUMPADCOMMA",
		"DIVIDE",
		"SYSRQ",
		"RALT",
		"HOME",
		"UP",
		"PGUP",
		"LEFT",
		"RIGHT",
		"END",
		"DOWN",
		"PGDN",
		"INSERT",
		"DELETE",
		"LWIN",
		"RWIN",
		"APPS"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	char utf8[2];
} utf8_conversion;

utf8_conversion conversion_table[94];

const int utf8_start = 161;

void initialise_utf8_conversion_table(void)
{
	int chr;

	for (chr = utf8_start; chr <= 191; chr++)
	{
		conversion_table[chr - utf8_start].utf8[0] = 0xc2;
		conversion_table[chr - utf8_start].utf8[1] = 0xa1 + (chr-utf8_start);
	}

	for (chr = 192; chr <= 255; chr++)
	{
		conversion_table[chr - utf8_start].utf8[0] = 0xc3;
		conversion_table[chr - utf8_start].utf8[1] = 0x80 + (chr-192);
	}
}

void latin1_to_utf8(const char* latin1_text, char* result, unsigned result_len, int remove_equals)
{
	const char* tmp = latin1_text;
	char* out = result;

	for (tmp = latin1_text; *tmp && ((out - result) < (result_len - 2)); tmp++)
	{
		if (remove_equals && *tmp == '=')
			continue;

		if (*tmp < utf8_start)
			*out++ = *tmp;
		else
		{
			*out++ = conversion_table[*tmp - utf8_start].utf8[0];
			*out++ = conversion_table[*tmp - utf8_start].utf8[1];
		}
	}

	*out = '\0';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
