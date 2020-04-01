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

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MONO_FONT_TYPES
{
	MONO_FONT_TYPE_3X6,
	MONO_FONT_TYPE_5X7,
	MONO_FONT_TYPE_5X9,
	MONO_FONT_TYPE_6X7,
	MONO_FONT_TYPE_6X10,
	MONO_FONT_TYPE_7X12,
	MONO_FONT_TYPE_8X14,
	MONO_FONT_TYPE_10X16,
	MONO_FONT_TYPE_12X20,
	MONO_FONT_TYPE_14X21,
	MONO_FONT_TYPE_17X26,
	MONO_FONT_TYPE_17X26_DIGITAL,
	NUM_MONO_FONT_TYPES
};

typedef enum MONO_FONT_TYPES mono_font_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_mono_font_type (const mono_font_types type);

extern mono_font_types get_mono_font_type (void);

extern void set_mono_font_position (const float x, const float y);

extern void get_mono_font_position (float *x, float *y);

extern void set_mono_font_rel_position (const float x_rel, const float y_rel);

extern void set_mono_font_colour (const rgb_colour col);

extern rgb_colour get_mono_font_colour (void);

extern float get_mono_font_char_width (const char c);

extern float get_mono_font_char_height (const char c);

extern void print_mono_font_char (const char c);

extern float get_mono_font_string_width (const char *s);

extern void print_mono_font_string (const char *s);
extern void print_vertical_mono_font_string(float x, float y, const char* string, float h_align, int v_centre);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
