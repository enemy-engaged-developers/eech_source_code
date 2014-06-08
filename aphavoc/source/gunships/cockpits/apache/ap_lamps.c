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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

apache_lamp_flags
	apache_lamps;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static char
	*lamp_error = "Cannot draw lamps on panel";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_alpha_masked_sprite_data
	sprite_values;

#define draw_lamp(FLAG,X,Y,U,V,WIDTH,HEIGHT,MASK)										\
{																										\
	if ((FLAG))																						\
	{																									\
		sprite_values.x = (X) + ix_640_480;													\
		sprite_values.y = (Y) + iy_640_480;													\
		sprite_values.u = (U);																	\
		sprite_values.v = (V);																	\
		sprite_values.width = (WIDTH);														\
		sprite_values.height = (HEIGHT);														\
		sprite_values.mask_value = (MASK);													\
																										\
		blit_rgb_alpha_masked_sprite (sprite_data, mask_data, &sprite_values);	\
	}																									\
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_lamps (void)
{
	memset (&apache_lamps, 0, sizeof (apache_lamp_flags));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void draw_apache_indicator_lamps (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		apache_lamps.indicator_lamp_1 = 0;
		apache_lamps.indicator_lamp_2 = 0;
		apache_lamps.indicator_lamp_3 = 0;
		apache_lamps.indicator_lamp_4 = 0;
		apache_lamps.indicator_lamp_5 = 0;
		apache_lamps.indicator_lamp_6 = 0;
		apache_lamps.indicator_lamp_7 = 0;
		apache_lamps.indicator_lamp_8 = 0;
		apache_lamps.indicator_lamp_9 = 0;

		timer += get_delta_time ();

		if (timer < (ONE_SECOND * 1.0))
		{
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			apache_lamps.indicator_lamp_1 = 1;
		}
		else if (timer < (ONE_SECOND * 3.0))
		{
			apache_lamps.indicator_lamp_2 = 1;
		}
		else if (timer < (ONE_SECOND * 4.0))
		{
			apache_lamps.indicator_lamp_3 = 1;
		}
		else if (timer < (ONE_SECOND * 5.0))
		{
			apache_lamps.indicator_lamp_4 = 1;
		}
		else if (timer < (ONE_SECOND * 6.0))
		{
			apache_lamps.indicator_lamp_5 = 1;
		}
		else if (timer < (ONE_SECOND * 7.0))
		{
			apache_lamps.indicator_lamp_6 = 1;
		}
		else if (timer < (ONE_SECOND * 8.0))
		{
			apache_lamps.indicator_lamp_7 = 1;
		}
		else if (timer < (ONE_SECOND * 9.0))
		{
			apache_lamps.indicator_lamp_8 = 1;
		}
		else if (timer < (ONE_SECOND * 10.0))
		{
			apache_lamps.indicator_lamp_9 = 1;
		}
		else if (timer < (ONE_SECOND * 11.0))
		{
			apache_lamps.indicator_lamp_1 = 1;
			apache_lamps.indicator_lamp_2 = 1;
			apache_lamps.indicator_lamp_3 = 1;
			apache_lamps.indicator_lamp_4 = 1;
			apache_lamps.indicator_lamp_5 = 1;
			apache_lamps.indicator_lamp_6 = 1;
			apache_lamps.indicator_lamp_7 = 1;
			apache_lamps.indicator_lamp_8 = 1;
			apache_lamps.indicator_lamp_9 = 1;
		}
		else
		{
			timer = 0.0;
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (524)
			#define Y_ORG (378)

			draw_lamp (apache_lamps.indicator_lamp_1, X_ORG +   9, Y_ORG +   5,   9,  45,  22,  21,   0);	// (100% alpha)
			draw_lamp (apache_lamps.indicator_lamp_2, X_ORG +  32, Y_ORG +   8,  32,  48,  22,  22,  13);	// (95% alpha)
			draw_lamp (apache_lamps.indicator_lamp_3, X_ORG +  55, Y_ORG +  11,  55,  51,  23,  22,  25);	// (90% alpha)
			draw_lamp (apache_lamps.indicator_lamp_4, X_ORG +  79, Y_ORG +  14,  79,  54,  24,  22,  38);	// (85% alpha)
			draw_lamp (apache_lamps.indicator_lamp_5, X_ORG + 104, Y_ORG +  16, 104,  56,  12,  22,  51);	// (80% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (225)
			#define Y_ORG (370)

			draw_lamp (apache_lamps.indicator_lamp_1, X_ORG +   7, Y_ORG +   4,   7,   4,  19,  19,   0);	// (100% alpha)
			draw_lamp (apache_lamps.indicator_lamp_2, X_ORG +  27, Y_ORG +   4,  27,   4,  18,  19,  13);	// (95% alpha)
			draw_lamp (apache_lamps.indicator_lamp_3, X_ORG +  47, Y_ORG +   5,  47,   5,  18,  18,  25);	// (90% alpha)
			draw_lamp (apache_lamps.indicator_lamp_4, X_ORG +  66, Y_ORG +   5,  66,   5,  18,  18,  38);	// (85% alpha)
			draw_lamp (apache_lamps.indicator_lamp_5, X_ORG +  86, Y_ORG +   5,  86,   5,  18,  18,  51);	// (80% alpha)
			draw_lamp (apache_lamps.indicator_lamp_6, X_ORG + 106, Y_ORG +   5, 106,   5,  18,  18,  64);	// (75% alpha)
			draw_lamp (apache_lamps.indicator_lamp_7, X_ORG + 125, Y_ORG +   5, 125,   5,  18,  18,  76);	// (70% alpha)
			draw_lamp (apache_lamps.indicator_lamp_8, X_ORG + 144, Y_ORG +   5, 144,   5,  19,  18,  89);	// (65% alpha)
			draw_lamp (apache_lamps.indicator_lamp_9, X_ORG + 164, Y_ORG +   4, 164,   4,  19,  19, 102);	// (60% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (0)
			#define Y_ORG (380)

			draw_lamp (apache_lamps.indicator_lamp_5, X_ORG +   0, Y_ORG +  14, 120,  54,  12,  22,  51);	// (80% alpha)
			draw_lamp (apache_lamps.indicator_lamp_6, X_ORG +  13, Y_ORG +  12, 133,  52,  24,  22,  64);	// (75% alpha)
			draw_lamp (apache_lamps.indicator_lamp_7, X_ORG +  38, Y_ORG +   8, 158,  48,  23,  23,  76);	// (70% alpha)
			draw_lamp (apache_lamps.indicator_lamp_8, X_ORG +  62, Y_ORG +   6, 182,  46,  22,  22,  89);	// (65% alpha)
			draw_lamp (apache_lamps.indicator_lamp_9, X_ORG +  85, Y_ORG +   3, 205,  43,  22,  21, 102);	// (60% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (512)
			#define Y_ORG (174)

			draw_lamp (apache_lamps.indicator_lamp_1, X_ORG +  13, Y_ORG +  12, 393,  12,  23,  20,   0);	// (100% alpha)
			draw_lamp (apache_lamps.indicator_lamp_2, X_ORG +  34, Y_ORG +  14, 414,  14,  24,  21,  13);	// (95% alpha)
			draw_lamp (apache_lamps.indicator_lamp_3, X_ORG +  56, Y_ORG +  17, 436,  17,  25,  21,  25);	// (90% alpha)
			draw_lamp (apache_lamps.indicator_lamp_4, X_ORG +  79, Y_ORG +  20, 459,  20,  25,  21,  38);	// (85% alpha)
			draw_lamp (apache_lamps.indicator_lamp_5, X_ORG + 103, Y_ORG +  23, 483,  23,  25,  21,  51);	// (80% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (229)
			#define Y_ORG (173)

			draw_lamp (apache_lamps.indicator_lamp_1, X_ORG +   6, Y_ORG +   5, 196,   5,  18,  17,   0);	// (100% alpha)
			draw_lamp (apache_lamps.indicator_lamp_2, X_ORG +  25, Y_ORG +   5, 215,   5,  18,  17,  13);	// (95% alpha)
			draw_lamp (apache_lamps.indicator_lamp_3, X_ORG +  44, Y_ORG +   5, 234,   5,  18,  17,  25);	// (90% alpha)
			draw_lamp (apache_lamps.indicator_lamp_4, X_ORG +  63, Y_ORG +   5, 253,   5,  18,  17,  38);	// (85% alpha)
			draw_lamp (apache_lamps.indicator_lamp_5, X_ORG +  82, Y_ORG +   5, 272,   5,  18,  17,  51);	// (80% alpha)
			draw_lamp (apache_lamps.indicator_lamp_6, X_ORG + 101, Y_ORG +   5, 291,   5,  18,  17,  64);	// (75% alpha)
			draw_lamp (apache_lamps.indicator_lamp_7, X_ORG + 120, Y_ORG +   5, 310,   5,  18,  17,  76);	// (70% alpha)
			draw_lamp (apache_lamps.indicator_lamp_8, X_ORG + 139, Y_ORG +   5, 329,   5,  18,  17,  89);	// (65% alpha)
			draw_lamp (apache_lamps.indicator_lamp_9, X_ORG + 158, Y_ORG +   5, 348,   5,  18,  17, 102);	// (60% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (0)
			#define Y_ORG (177)

			draw_lamp (apache_lamps.indicator_lamp_5, X_ORG +   0, Y_ORG +  20, 510,  20,  25,  21,  51);	// (80% alpha)
			draw_lamp (apache_lamps.indicator_lamp_6, X_ORG +  24, Y_ORG +  17, 534,  17,  25,  21,  64);	// (75% alpha)
			draw_lamp (apache_lamps.indicator_lamp_7, X_ORG +  48, Y_ORG +  14, 558,  14,  23,  21,  76);	// (70% alpha)
			draw_lamp (apache_lamps.indicator_lamp_8, X_ORG +  70, Y_ORG +  12, 580,  12,  24,  20,  89);	// (65% alpha)
			draw_lamp (apache_lamps.indicator_lamp_9, X_ORG +  92, Y_ORG +   8, 602,   8,  23,  21, 102);	// (60% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (lamp_error);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_fire_detector_lamps (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		timer += get_delta_time ();

		apache_lamps.engine_1_fire = 0;
		apache_lamps.apu_fire = 0;
		apache_lamps.engine_2_fire = 0;

		if (timer < (ONE_SECOND * 1.0))
		{
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			apache_lamps.engine_1_fire = 1;
		}
		else if (timer < (ONE_SECOND * 3.0))
		{
			apache_lamps.apu_fire = 1;
		}
		else if (timer < (ONE_SECOND * 4.0))
		{
			apache_lamps.engine_2_fire = 1;
		}
		else if (timer < (ONE_SECOND * 5.0))
		{
			apache_lamps.engine_1_fire = 1;
			apache_lamps.apu_fire = 1;
			apache_lamps.engine_2_fire = 1;
		}
		else
		{
			timer = 0.0;
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (461)
			#define Y_ORG (417)

			draw_lamp (apache_lamps.engine_1_fire	, X_ORG +  11, Y_ORG +   5, 371,  95,  26,  28,   0);	// (100% alpha)
			draw_lamp (apache_lamps.apu_fire			, X_ORG +  45, Y_ORG +  10, 405, 100,  26,  29,  13);	// (95% alpha)
			draw_lamp (apache_lamps.engine_2_fire	, X_ORG +  82, Y_ORG +  16, 442, 106,  26,  29,  25);	// (90% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (164)
			#define Y_ORG (408)

			draw_lamp (apache_lamps.engine_1_fire	, X_ORG +  10, Y_ORG +  12,  10, 102,  26,  27,   0);	// (100% alpha)
			draw_lamp (apache_lamps.apu_fire			, X_ORG +  42, Y_ORG +  12,  42, 102,  26,  27,  13);	// (95% alpha)
			draw_lamp (apache_lamps.engine_2_fire	, X_ORG +  75, Y_ORG +  12,  75, 102,  26,  27,  25);	// (90% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (446)
			#define Y_ORG (214)

			draw_lamp (apache_lamps.engine_1_fire	, X_ORG +  16, Y_ORG +   7, 256,  97,  26,  27,   0);	// (100% alpha)
			draw_lamp (apache_lamps.apu_fire			, X_ORG +  48, Y_ORG +  12, 288, 102,  26,  27,  13);	// (95% alpha)
			draw_lamp (apache_lamps.engine_2_fire	, X_ORG +  82, Y_ORG +  18, 322, 108,  26,  27,  25);	// (90% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (172)
			#define Y_ORG (213)

			draw_lamp (apache_lamps.engine_1_fire	, X_ORG +   9, Y_ORG +   5, 129,  95,  26,  27,   0);	// (100% alpha)
			draw_lamp (apache_lamps.apu_fire			, X_ORG +  40, Y_ORG +   5, 160,  95,  26,  27,  13);	// (95% alpha)
			draw_lamp (apache_lamps.engine_2_fire	, X_ORG +  70, Y_ORG +   5, 190,  95,  26,  27,  25);	// (90% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (lamp_error);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_armament_lamps (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		timer += get_delta_time ();

		apache_lamps.armament_lamp_1 = 0;
		apache_lamps.armament_lamp_2 = 0;

		if (timer < (ONE_SECOND * 1.0))
		{
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			apache_lamps.armament_lamp_1 = 1;
		}
		else if (timer < (ONE_SECOND * 3.0))
		{
			apache_lamps.armament_lamp_2 = 1;
		}
		else if (timer < (ONE_SECOND * 4.0))
		{
			apache_lamps.armament_lamp_1 = 1;
			apache_lamps.armament_lamp_2 = 1;
		}
		else
		{
			timer = 0.0;
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			#define X_ORG (613)
			#define Y_ORG (395)

			draw_lamp (apache_lamps.armament_lamp_1 , X_ORG +   4, Y_ORG +   8, 134, 328,  23,  31,   0);	// (100% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (339)
			#define Y_ORG (347)

			draw_lamp (apache_lamps.armament_lamp_1 , X_ORG +   4, Y_ORG +   6,  74, 325,  23,  25,   0);	// (100% alpha)
			draw_lamp (apache_lamps.armament_lamp_2 , X_ORG +  23, Y_ORG +  13,  93, 332,  23,  25,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (72)
			#define Y_ORG (375)

			draw_lamp (apache_lamps.armament_lamp_1 , X_ORG +   9, Y_ORG +   7,   9, 327,  22,  23,   0);	// (100% alpha)
			draw_lamp (apache_lamps.armament_lamp_2 , X_ORG +  31, Y_ORG +   7,  31, 327,  22,  23,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		////////////////////////////////////////
		{
			#define X_ORG (0)
			#define Y_ORG (277)

			draw_lamp (apache_lamps.armament_lamp_2 , X_ORG +   4, Y_ORG +   4, 164, 324,  64,  59,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (lamp_error);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_mfd_lamps (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		timer += get_delta_time ();

		apache_lamps.mfd_lamp_1 = 0;
		apache_lamps.mfd_lamp_2 = 0;

		if (timer < (ONE_SECOND * 1.0))
		{
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			apache_lamps.mfd_lamp_1 = 1;
		}
		else if (timer < (ONE_SECOND * 3.0))
		{
			apache_lamps.mfd_lamp_2 = 1;
		}
		else if (timer < (ONE_SECOND * 4.0))
		{
			apache_lamps.mfd_lamp_1 = 1;
			apache_lamps.mfd_lamp_2 = 1;
		}
		else
		{
			timer = 0.0;
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (577)
			#define Y_ORG (309)

			draw_lamp (apache_lamps.mfd_lamp_1 , X_ORG +  11, Y_ORG +   7,  51, 187,  31,  29,   0);	// (100% alpha)
			draw_lamp (apache_lamps.mfd_lamp_2 , X_ORG +   7, Y_ORG +  30,  47, 210,  29,  30,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (305)
			#define Y_ORG (283)

			draw_lamp (apache_lamps.mfd_lamp_1 , X_ORG +   3, Y_ORG +   3,   3, 183,  24,  22,   0);	// (100% alpha)
			draw_lamp (apache_lamps.mfd_lamp_2 , X_ORG +   3, Y_ORG +  25,   3, 205,  24,  21,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (17)
			#define Y_ORG (311)

			draw_lamp (apache_lamps.mfd_lamp_1 , X_ORG +   3, Y_ORG +   3,  93, 183,  33,  31,   0);	// (100% alpha)
			draw_lamp (apache_lamps.mfd_lamp_2 , X_ORG +   8, Y_ORG +  27,  98, 207,  33,  31,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		////////////////////////////////////////
		{
			#define X_ORG (536)
			#define Y_ORG (9)

			draw_lamp (apache_lamps.mfd_lamp_1 , X_ORG +   2, Y_ORG +   8, 142, 188,  63,  56,   0);	// (100% alpha)
			draw_lamp (apache_lamps.mfd_lamp_2 , X_ORG +   2, Y_ORG +  64, 142, 244,  63,  56,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		////////////////////////////////////////
		{
			#define X_ORG (35)
			#define Y_ORG (11)

			draw_lamp (apache_lamps.mfd_lamp_1 , X_ORG +   4, Y_ORG +   8, 214, 188,  63,  56,   0);	// (100% alpha)
			draw_lamp (apache_lamps.mfd_lamp_2 , X_ORG +   4, Y_ORG +  64, 214, 244,  63,  56,  13);	// (95% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal (lamp_error);

			break;
		}
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
