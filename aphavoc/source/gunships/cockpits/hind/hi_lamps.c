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

hind_lamp_flags
	hind_lamps;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_hind_lamps (void)
{
	memset (&hind_lamps, 0, sizeof (hind_lamp_flags));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_weapons_management_panel_lamps (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		hind_lamps.weapons_management_lh_outer_pylon_green = 0;
		hind_lamps.weapons_management_lh_inner_pylon_green = 0;
		hind_lamps.weapons_management_rh_inner_pylon_green = 0;
		hind_lamps.weapons_management_rh_outer_pylon_green = 0;
		hind_lamps.weapons_management_armour_piercing_cannon_green = 0;
		hind_lamps.weapons_management_high_explosive_cannon_green = 0;
		hind_lamps.weapons_management_lh_outer_pylon_red = 0;
		hind_lamps.weapons_management_lh_inner_pylon_red = 0;
		hind_lamps.weapons_management_rh_inner_pylon_red = 0;
		hind_lamps.weapons_management_rh_outer_pylon_red = 0;
		hind_lamps.weapons_management_armour_piercing_cannon_red = 0;
		hind_lamps.weapons_management_high_explosive_cannon_red = 0;
		hind_lamps.weapons_management_chaff_green = 0;
		hind_lamps.weapons_management_flare_green = 0;
		hind_lamps.weapons_management_chaff_red = 0;
		hind_lamps.weapons_management_flare_red = 0;

		timer += get_delta_time ();

		if (timer < (ONE_SECOND * 1.0))
		{
			hind_lamps.weapons_management_lh_outer_pylon_green = 1;
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			hind_lamps.weapons_management_lh_outer_pylon_red = 1;
		}
		else if (timer < (ONE_SECOND * 3.0))
		{
			hind_lamps.weapons_management_lh_inner_pylon_green = 1;
		}
		else if (timer < (ONE_SECOND * 4.0))
		{
			hind_lamps.weapons_management_lh_inner_pylon_red = 1;
		}
		else if (timer < (ONE_SECOND * 5.0))
		{
			hind_lamps.weapons_management_rh_inner_pylon_green = 1;
		}
		else if (timer < (ONE_SECOND * 6.0))
		{
			hind_lamps.weapons_management_rh_inner_pylon_red = 1;
		}
		else if (timer < (ONE_SECOND * 7.0))
		{
			hind_lamps.weapons_management_rh_outer_pylon_green = 1;
		}
		else if (timer < (ONE_SECOND * 8.0))
		{
			hind_lamps.weapons_management_rh_outer_pylon_red = 1;
		}
		else if (timer < (ONE_SECOND * 9.0))
		{
			hind_lamps.weapons_management_armour_piercing_cannon_green = 1;
		}
		else if (timer < (ONE_SECOND * 10.0))
		{
			hind_lamps.weapons_management_armour_piercing_cannon_red = 1;
		}
		else if (timer < (ONE_SECOND * 11.0))
		{
			hind_lamps.weapons_management_high_explosive_cannon_green = 1;
		}
		else if (timer < (ONE_SECOND * 12.0))
		{
			hind_lamps.weapons_management_high_explosive_cannon_red = 1;
		}
		else if (timer < (ONE_SECOND * 13.0))
		{
			hind_lamps.weapons_management_chaff_green = 1;
		}
		else if (timer < (ONE_SECOND * 14.0))
		{
			hind_lamps.weapons_management_chaff_red = 1;
		}
		else if (timer < (ONE_SECOND * 15.0))
		{
			hind_lamps.weapons_management_flare_green = 1;
		}
		else if (timer < (ONE_SECOND * 16.0))
		{
			hind_lamps.weapons_management_flare_red = 1;
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
			#define X_ORG (248)
			#define Y_ORG (412)

			draw_lamp (hind_lamps.weapons_management_lh_inner_pylon_green				, X_ORG +   2, Y_ORG +  65,   3, 320,   7,   3, 250);	// (2% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_inner_pylon_green				, X_ORG +  17, Y_ORG +  48,  18, 303,  30,  20, 247);	// (3% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_green				, X_ORG +  53, Y_ORG +  32,  54, 287,  31,  23, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_green	, X_ORG +  85, Y_ORG +  26,  86, 281,  23,  30, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_green	, X_ORG +  91, Y_ORG +   1,  92, 256,  21,  29, 240);	// (6% alpha)

			draw_lamp (hind_lamps.weapons_management_lh_inner_pylon_red				, X_ORG +   2, Y_ORG +  65,   3, 389,   7,   3, 250);	// (2% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_inner_pylon_red				, X_ORG +  17, Y_ORG +  48,  18, 372,  30,  20, 247);	// (3% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_red				, X_ORG +  53, Y_ORG +  32,  54, 356,  31,  23, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_red		, X_ORG +  85, Y_ORG +  26,  86, 350,  23,  30, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_red		, X_ORG +  91, Y_ORG +   1,  92, 325,  21,  29, 240);	// (6% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (377)
			#define Y_ORG (470)

			draw_lamp (hind_lamps.weapons_management_chaff_green							, X_ORG +   2, Y_ORG +   2, 488,  68,  21,   8,  51);	// (80% alpha)
			draw_lamp (hind_lamps.weapons_management_flare_green							, X_ORG +  22, Y_ORG +   6, 508,  72,  18,   4,  48);	// (81% alpha)

			draw_lamp (hind_lamps.weapons_management_chaff_red							, X_ORG +   2, Y_ORG +   2, 488,  57,  21,   8,  51);	// (80% alpha)
			draw_lamp (hind_lamps.weapons_management_flare_red							, X_ORG +  22, Y_ORG +   6, 508,  61,  18,   4,  48);	// (81% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (0)
			#define Y_ORG (434)

			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_green				, X_ORG +   0, Y_ORG +  40, 160, 135,  11,   6, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_green	, X_ORG +  18, Y_ORG +  29, 178, 124,  25,  17, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_green	, X_ORG +  24, Y_ORG +   0, 184,  95,  27,  32, 240);	// (6% alpha)

			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_red				, X_ORG +   0, Y_ORG +  40, 160, 182,  11,   6, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_red		, X_ORG +  18, Y_ORG +  29, 178, 171,  25,  17, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_red		, X_ORG +  24, Y_ORG +   0, 184, 142,  27,  32, 240);	// (6% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			#define X_ORG (471)
			#define Y_ORG (268)

			draw_lamp (hind_lamps.weapons_management_lh_outer_pylon_green				, X_ORG +   1, Y_ORG +  25, 161,  26,  30,  17, 252);	// (1% alpha)
			draw_lamp (hind_lamps.weapons_management_lh_inner_pylon_green				, X_ORG +  39, Y_ORG +  18, 199,  19,  30,  17, 250);	// (2% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_inner_pylon_green				, X_ORG +  78, Y_ORG +   9, 238,  10,  32,  19, 247);	// (3% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_green				, X_ORG + 120, Y_ORG +   1, 280,   2,  35,  19, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_green	, X_ORG + 161, Y_ORG +   1, 321,   2,   8,  28, 242);	// (5% alpha)

			draw_lamp (hind_lamps.weapons_management_lh_outer_pylon_red				, X_ORG +   1, Y_ORG +  25, 161,  73,  30,  17, 252);	// (1% alpha)
			draw_lamp (hind_lamps.weapons_management_lh_inner_pylon_red				, X_ORG +  39, Y_ORG +  18, 199,  66,  30,  17, 250);	// (2% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_inner_pylon_red				, X_ORG +  78, Y_ORG +   9, 238,  57,  32,  19, 247);	// (3% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_red				, X_ORG + 120, Y_ORG +   1, 280,  49,  35,  19, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_red		, X_ORG + 161, Y_ORG +   1, 321,  49,   8,  28, 242);	// (5% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (203)
			#define Y_ORG (213)

			draw_lamp (hind_lamps.weapons_management_lh_outer_pylon_green				, X_ORG +   0, Y_ORG +  70,   1,  71,  28,  23, 252);	// (1% alpha)
			draw_lamp (hind_lamps.weapons_management_lh_inner_pylon_green				, X_ORG +  32, Y_ORG +  56,  33,  57,  29,  22, 250);	// (2% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_inner_pylon_green				, X_ORG +  65, Y_ORG +  41,  66,  42,  29,  23, 247);	// (3% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_green				, X_ORG +  98, Y_ORG +  27,  99,  28,  30,  22, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_green	, X_ORG + 129, Y_ORG +  23, 130,  24,  21,  26, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_green	, X_ORG + 134, Y_ORG +   0, 135,   1,  22,  26, 240);	// (6% alpha)

			draw_lamp (hind_lamps.weapons_management_lh_outer_pylon_red				, X_ORG +   0, Y_ORG +  70,   1, 166,  28,  23, 252);	// (1% alpha)
			draw_lamp (hind_lamps.weapons_management_lh_inner_pylon_red				, X_ORG +  32, Y_ORG +  56,  33, 152,  29,  22, 250);	// (2% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_inner_pylon_red				, X_ORG +  65, Y_ORG +  41,  66, 137,  29,  23, 247);	// (3% alpha)
			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_red				, X_ORG +  98, Y_ORG +  27,  99, 123,  30,  22, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_red		, X_ORG + 129, Y_ORG +  23, 130, 119,  21,  26, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_red		, X_ORG + 134, Y_ORG +   0, 135,  96,  22,  26, 240);	// (6% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (372)
			#define Y_ORG (264)

			draw_lamp (hind_lamps.weapons_management_chaff_green							, X_ORG +   1, Y_ORG +   1, 533,  76,  21,  14,  51);	// (80% alpha)
			draw_lamp (hind_lamps.weapons_management_flare_green							, X_ORG +  20, Y_ORG +   5, 552,  80,  21,  14,  48);	// (81% alpha)

			draw_lamp (hind_lamps.weapons_management_chaff_red							, X_ORG +   1, Y_ORG +   1, 533,  54,  21,  14,  51);	// (80% alpha)
			draw_lamp (hind_lamps.weapons_management_flare_red							, X_ORG +  20, Y_ORG +   5, 552,  58,  21,  14,  48);	// (81% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (4)
			#define Y_ORG (232)

			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_green				, X_ORG +   0, Y_ORG +  35,   1, 226,  35,  27, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_green	, X_ORG +  36, Y_ORG +  26,  37, 217,  28,  28, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_green	, X_ORG +  39, Y_ORG +   1,  40, 192,  26,  27, 240);	// (6% alpha)

			draw_lamp (hind_lamps.weapons_management_rh_outer_pylon_red				, X_ORG +   0, Y_ORG +  35,  67, 226,  35,  27, 245);	// (4% alpha)
			draw_lamp (hind_lamps.weapons_management_armour_piercing_cannon_red		, X_ORG +  36, Y_ORG +  26, 103, 217,  28,  28, 242);	// (5% alpha)
			draw_lamp (hind_lamps.weapons_management_high_explosive_cannon_red		, X_ORG +  39, Y_ORG +   1, 106, 192,  26,  27, 240);	// (6% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (91)
			#define Y_ORG (280)

			draw_lamp (hind_lamps.weapons_management_chaff_green							, X_ORG +   4, Y_ORG +   2, 481,  79,  22,  11,  51);	// (80% alpha)
			draw_lamp (hind_lamps.weapons_management_flare_green							, X_ORG +  26, Y_ORG +   2, 503,  79,  22,  11,  48);	// (81% alpha)

			draw_lamp (hind_lamps.weapons_management_chaff_red							, X_ORG +   4, Y_ORG +   2, 436,  54,  22,  11,  51);	// (80% alpha)
			draw_lamp (hind_lamps.weapons_management_flare_red							, X_ORG +  26, Y_ORG +   2, 458,  54,  22,  11,  48);	// (81% alpha)

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

void draw_hind_status_panel_lamps (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		hind_lamps.status_1 = 0;
		hind_lamps.status_2 = 0;
		hind_lamps.status_3 = 0;
		hind_lamps.status_4 = 0;
		hind_lamps.status_5 = 0;
		hind_lamps.status_6 = 0;
		hind_lamps.status_7 = 0;
		hind_lamps.status_8 = 0;
		hind_lamps.status_9 = 0;
		hind_lamps.status_10 = 0;
		hind_lamps.status_11 = 0;
		hind_lamps.status_12 = 0;
		hind_lamps.status_13 = 0;
		hind_lamps.status_14 = 0;
		hind_lamps.status_15 = 0;
		hind_lamps.status_16 = 0;
		hind_lamps.status_17 = 0;
		hind_lamps.status_18 = 0;

		timer += get_delta_time ();

		if (timer < (ONE_SECOND * 1.0))
		{
			hind_lamps.status_1 = 1;
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			hind_lamps.status_2 = 1;
		}
		else if (timer < (ONE_SECOND * 3.0))
		{
			hind_lamps.status_3 = 1;
		}
		else if (timer < (ONE_SECOND * 4.0))
		{
			hind_lamps.status_4 = 1;
		}
		else if (timer < (ONE_SECOND * 5.0))
		{
			hind_lamps.status_5 = 1;
		}
		else if (timer < (ONE_SECOND * 6.0))
		{
			hind_lamps.status_6 = 1;
		}
		else if (timer < (ONE_SECOND * 7.0))
		{
			hind_lamps.status_7 = 1;
		}
		else if (timer < (ONE_SECOND * 8.0))
		{
			hind_lamps.status_8 = 1;
		}
		else if (timer < (ONE_SECOND * 9.0))
		{
			hind_lamps.status_9 = 1;
		}
		else if (timer < (ONE_SECOND * 10.0))
		{
			hind_lamps.status_10 = 1;
		}
		else if (timer < (ONE_SECOND * 11.0))
		{
			hind_lamps.status_11 = 1;
		}
		else if (timer < (ONE_SECOND * 12.0))
		{
			hind_lamps.status_12 = 1;
		}
		else if (timer < (ONE_SECOND * 13.0))
		{
			hind_lamps.status_13 = 1;
		}
		else if (timer < (ONE_SECOND * 14.0))
		{
			hind_lamps.status_14 = 1;
		}
		else if (timer < (ONE_SECOND * 15.0))
		{
			hind_lamps.status_15 = 1;
		}
		else if (timer < (ONE_SECOND * 16.0))
		{
			hind_lamps.status_16 = 1;
		}
		else if (timer < (ONE_SECOND * 17.0))
		{
			hind_lamps.status_17 = 1;
		}
		else if (timer < (ONE_SECOND * 18.0))
		{
			hind_lamps.status_18 = 1;
		}
		else if (timer < (ONE_SECOND * 19.0))
		{
			hind_lamps.status_1 = 1;
			hind_lamps.status_2 = 1;
			hind_lamps.status_3 = 1;
			hind_lamps.status_4 = 1;
			hind_lamps.status_5 = 1;
			hind_lamps.status_6 = 1;
			hind_lamps.status_7 = 1;
			hind_lamps.status_8 = 1;
			hind_lamps.status_9 = 1;
			hind_lamps.status_10 = 1;
			hind_lamps.status_11 = 1;
			hind_lamps.status_12 = 1;
			hind_lamps.status_13 = 1;
			hind_lamps.status_14 = 1;
			hind_lamps.status_15 = 1;
			hind_lamps.status_16 = 1;
			hind_lamps.status_17 = 1;
			hind_lamps.status_18 = 1;
		}
		else
		{
			timer = 0.0;
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (260)
			#define Y_ORG (472)

			draw_lamp (hind_lamps.status_3	, X_ORG +   6, Y_ORG +   1, 399, 172,  24,   7, 115);	// (55% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (507)
			#define Y_ORG (289)

			draw_lamp (hind_lamps.status_1	, X_ORG +   2, Y_ORG +   1, 332,   2,  22,  11, 120);	// (53% alpha)
			draw_lamp (hind_lamps.status_2	, X_ORG +  24, Y_ORG +   1, 354,   2,  22,  11, 117);	// (54% alpha)
			draw_lamp (hind_lamps.status_3	, X_ORG +  46, Y_ORG +   1, 376,   2,  22,  11, 115);	// (55% alpha)
			draw_lamp (hind_lamps.status_4	, X_ORG +   2, Y_ORG +  12, 332,  13,  22,  11, 112);	// (56% alpha)
			draw_lamp (hind_lamps.status_5	, X_ORG +  24, Y_ORG +  12, 354,  13,  22,  11, 110);	// (57% alpha)
			draw_lamp (hind_lamps.status_6	, X_ORG +  46, Y_ORG +  12, 376,  13,  22,  11, 107);	// (58% alpha)
			draw_lamp (hind_lamps.status_7	, X_ORG +   2, Y_ORG +  23, 332,  24,  22,  11, 105);	// (59% alpha)
			draw_lamp (hind_lamps.status_8	, X_ORG +  24, Y_ORG +  23, 354,  24,  22,  11, 102);	// (60% alpha)
			draw_lamp (hind_lamps.status_9	, X_ORG +  46, Y_ORG +  23, 376,  24,  22,  11,  99);	// (61% alpha)
			draw_lamp (hind_lamps.status_10	, X_ORG +   2, Y_ORG +  34, 332,  35,  22,  11,  97);	// (62% alpha)
			draw_lamp (hind_lamps.status_11	, X_ORG +  24, Y_ORG +  34, 354,  35,  22,  11,  94);	// (63% alpha)
			draw_lamp (hind_lamps.status_12	, X_ORG +  46, Y_ORG +  34, 376,  35,  22,  11,  92);	// (64% alpha)
			draw_lamp (hind_lamps.status_13	, X_ORG +   2, Y_ORG +  45, 332,  46,  22,  11,  89);	// (65% alpha)
			draw_lamp (hind_lamps.status_14	, X_ORG +  24, Y_ORG +  45, 354,  46,  22,  11,  87);	// (66% alpha)
			draw_lamp (hind_lamps.status_15	, X_ORG +  46, Y_ORG +  45, 376,  46,  22,  11,  84);	// (67% alpha)
			draw_lamp (hind_lamps.status_16	, X_ORG +   2, Y_ORG +  56, 332,  57,  22,  11,  82);	// (68% alpha)
			draw_lamp (hind_lamps.status_17	, X_ORG +  24, Y_ORG +  56, 354,  57,  22,  11,  79);	// (69% alpha)
			draw_lamp (hind_lamps.status_18	, X_ORG +  46, Y_ORG +  56, 376,  57,  22,  11,  76);	// (70% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (234)
			#define Y_ORG (266)

			draw_lamp (hind_lamps.status_1	, X_ORG +   1, Y_ORG +   9, 331,  79,  22,  14, 120);	// (53% alpha)
			draw_lamp (hind_lamps.status_2	, X_ORG +  21, Y_ORG +   5, 351,  75,  20,  14, 117);	// (54% alpha)
			draw_lamp (hind_lamps.status_3	, X_ORG +  40, Y_ORG +   0, 370,  70,  19,  15, 115);	// (55% alpha)
			draw_lamp (hind_lamps.status_4	, X_ORG +   3, Y_ORG +  19, 333,  89,  21,  15, 112);	// (56% alpha)
			draw_lamp (hind_lamps.status_5	, X_ORG +  23, Y_ORG +  15, 353,  85,  20,  14, 110);	// (57% alpha)
			draw_lamp (hind_lamps.status_6	, X_ORG +  42, Y_ORG +  11, 372,  81,  19,  14, 107);	// (58% alpha)
			draw_lamp (hind_lamps.status_7	, X_ORG +   6, Y_ORG +  29, 336,  99,  20,  15, 105);	// (59% alpha)
			draw_lamp (hind_lamps.status_8	, X_ORG +  25, Y_ORG +  25, 355,  95,  20,  14, 102);	// (60% alpha)
			draw_lamp (hind_lamps.status_9	, X_ORG +  44, Y_ORG +  21, 374,  91,  19,  14,  99);	// (61% alpha)
			draw_lamp (hind_lamps.status_10	, X_ORG +   7, Y_ORG +  39, 337, 109,  21,  15,  97);	// (62% alpha)
			draw_lamp (hind_lamps.status_11	, X_ORG +  27, Y_ORG +  35, 357, 105,  19,  14,  94);	// (63% alpha)
			draw_lamp (hind_lamps.status_12	, X_ORG +  45, Y_ORG +  31, 375, 101,  19,  14,  92);	// (64% alpha)
			draw_lamp (hind_lamps.status_13	, X_ORG +   9, Y_ORG +  49, 339, 119,  21,  15,  89);	// (65% alpha)
			draw_lamp (hind_lamps.status_14	, X_ORG +  29, Y_ORG +  45, 359, 115,  20,  15,  87);	// (66% alpha)
			draw_lamp (hind_lamps.status_15	, X_ORG +  47, Y_ORG +  40, 377, 110,  19,  14,  84);	// (67% alpha)
			draw_lamp (hind_lamps.status_16	, X_ORG +  11, Y_ORG +  60, 341, 130,  20,  14,  82);	// (68% alpha)
			draw_lamp (hind_lamps.status_17	, X_ORG +  31, Y_ORG +  55, 361, 125,  19,  14,  79);	// (69% alpha)
			draw_lamp (hind_lamps.status_18	, X_ORG +  49, Y_ORG +  50, 379, 120,  19,  14,  76);	// (70% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			#define X_ORG (0)
			#define Y_ORG (325)

			draw_lamp (hind_lamps.status_9	, X_ORG +   0, Y_ORG +   1, 309,  96,   6,  13,  99);	// (61% alpha)
			draw_lamp (hind_lamps.status_12	, X_ORG +   0, Y_ORG +  11, 309, 106,  11,  16,  92);	// (64% alpha)
			draw_lamp (hind_lamps.status_15	, X_ORG +   0, Y_ORG +  22, 309, 117,  15,  17,  84);	// (67% alpha)
			draw_lamp (hind_lamps.status_18	, X_ORG +   0, Y_ORG +  32, 309, 127,  19,  20,  76);	// (70% alpha)

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

void draw_hind_threat_warning_display (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		////////////////////////////////////////
		//
		// test radar type lamps
		//
		////////////////////////////////////////
		{
			static float
				timer = 0.0;

			hind_lamps.threat_warning_radar_type_1 = 0;
			hind_lamps.threat_warning_radar_type_2 = 0;
			hind_lamps.threat_warning_radar_type_3 = 0;
			hind_lamps.threat_warning_radar_type_4 = 0;
			hind_lamps.threat_warning_radar_type_5 = 0;
			hind_lamps.threat_warning_radar_type_6 = 0;

			timer += get_delta_time ();

			if (timer < (ONE_SECOND * 1.0))
			{
				hind_lamps.threat_warning_radar_type_1 = 1;
			}
			else if (timer < (ONE_SECOND * 2.0))
			{
				hind_lamps.threat_warning_radar_type_2 = 1;
			}
			else if (timer < (ONE_SECOND * 3.0))
			{
				hind_lamps.threat_warning_radar_type_3 = 1;
			}
			else if (timer < (ONE_SECOND * 4.0))
			{
				hind_lamps.threat_warning_radar_type_4 = 1;
			}
			else if (timer < (ONE_SECOND * 5.0))
			{
				hind_lamps.threat_warning_radar_type_5 = 1;
			}
			else if (timer < (ONE_SECOND * 6.0))
			{
				hind_lamps.threat_warning_radar_type_6 = 1;
			}
			else if (timer < (ONE_SECOND * 7.0))
			{
				hind_lamps.threat_warning_radar_type_1 = 1;
				hind_lamps.threat_warning_radar_type_2 = 1;
				hind_lamps.threat_warning_radar_type_3 = 1;
				hind_lamps.threat_warning_radar_type_4 = 1;
				hind_lamps.threat_warning_radar_type_5 = 1;
				hind_lamps.threat_warning_radar_type_6 = 1;
			}
			else
			{
				timer = 0.0;
			}
		}
		////////////////////////////////////////
		//
		// test radar bearing lamps
		//
		////////////////////////////////////////
		{
			static float
				timer = 0.0;

			hind_lamps.threat_warning_bearing_lh_rear_close_range = 0;
			hind_lamps.threat_warning_bearing_lh_90_close_range = 0;
			hind_lamps.threat_warning_bearing_lh_67_close_range = 0;
			hind_lamps.threat_warning_bearing_lh_45_close_range = 0;
			hind_lamps.threat_warning_bearing_lh_22_close_range = 0;
			hind_lamps.threat_warning_bearing_rh_22_close_range = 0;
			hind_lamps.threat_warning_bearing_rh_45_close_range = 0;
			hind_lamps.threat_warning_bearing_rh_67_close_range = 0;
			hind_lamps.threat_warning_bearing_rh_90_close_range = 0;
			hind_lamps.threat_warning_bearing_rh_rear_close_range = 0;
			hind_lamps.threat_warning_bearing_lh_rear = 0;
			hind_lamps.threat_warning_bearing_lh_90 = 0;
			hind_lamps.threat_warning_bearing_lh_67 = 0;
			hind_lamps.threat_warning_bearing_lh_45 = 0;
			hind_lamps.threat_warning_bearing_lh_22 = 0;
			hind_lamps.threat_warning_bearing_rh_22 = 0;
			hind_lamps.threat_warning_bearing_rh_45 = 0;
			hind_lamps.threat_warning_bearing_rh_67 = 0;
			hind_lamps.threat_warning_bearing_rh_90 = 0;
			hind_lamps.threat_warning_bearing_rh_rear = 0;

			timer += get_delta_time ();

			if (timer < (ONE_SECOND * 1.0))
			{
				hind_lamps.threat_warning_bearing_lh_rear_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 2.0))
			{
				hind_lamps.threat_warning_bearing_lh_90_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 3.0))
			{
				hind_lamps.threat_warning_bearing_lh_67_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 4.0))
			{
				hind_lamps.threat_warning_bearing_lh_45_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 5.0))
			{
				hind_lamps.threat_warning_bearing_lh_22_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 6.0))
			{
				hind_lamps.threat_warning_bearing_rh_22_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 7.0))
			{
				hind_lamps.threat_warning_bearing_rh_45_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 8.0))
			{
				hind_lamps.threat_warning_bearing_rh_67_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 9.0))
			{
				hind_lamps.threat_warning_bearing_rh_90_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 10.0))
			{
				hind_lamps.threat_warning_bearing_rh_rear_close_range = 1;
			}
			else if (timer < (ONE_SECOND * 11.0))
			{
				hind_lamps.threat_warning_bearing_lh_rear = 1;
			}
			else if (timer < (ONE_SECOND * 12.0))
			{
				hind_lamps.threat_warning_bearing_lh_90 = 1;
			}
			else if (timer < (ONE_SECOND * 13.0))
			{
				hind_lamps.threat_warning_bearing_lh_67 = 1;
			}
			else if (timer < (ONE_SECOND * 14.0))
			{
				hind_lamps.threat_warning_bearing_lh_45 = 1;
			}
			else if (timer < (ONE_SECOND * 15.0))
			{
				hind_lamps.threat_warning_bearing_lh_22 = 1;
			}
			else if (timer < (ONE_SECOND * 16.0))
			{
				hind_lamps.threat_warning_bearing_rh_22 = 1;
			}
			else if (timer < (ONE_SECOND * 17.0))
			{
				hind_lamps.threat_warning_bearing_rh_45 = 1;
			}
			else if (timer < (ONE_SECOND * 18.0))
			{
				hind_lamps.threat_warning_bearing_rh_67 = 1;
			}
			else if (timer < (ONE_SECOND * 19.0))
			{
				hind_lamps.threat_warning_bearing_rh_90 = 1;
			}
			else if (timer < (ONE_SECOND * 20.0))
			{
				hind_lamps.threat_warning_bearing_rh_rear = 1;
			}
			else if (timer < (ONE_SECOND * 21.0))
			{
				hind_lamps.threat_warning_bearing_lh_rear_close_range = 1;
				hind_lamps.threat_warning_bearing_lh_90_close_range = 1;
				hind_lamps.threat_warning_bearing_lh_67_close_range = 1;
				hind_lamps.threat_warning_bearing_lh_45_close_range = 1;
				hind_lamps.threat_warning_bearing_lh_22_close_range = 1;
				hind_lamps.threat_warning_bearing_rh_22_close_range = 1;
				hind_lamps.threat_warning_bearing_rh_45_close_range = 1;
				hind_lamps.threat_warning_bearing_rh_67_close_range = 1;
				hind_lamps.threat_warning_bearing_rh_90_close_range = 1;
				hind_lamps.threat_warning_bearing_rh_rear_close_range = 1;
				hind_lamps.threat_warning_bearing_lh_rear = 1;
				hind_lamps.threat_warning_bearing_lh_90 = 1;
				hind_lamps.threat_warning_bearing_lh_67 = 1;
				hind_lamps.threat_warning_bearing_lh_45 = 1;
				hind_lamps.threat_warning_bearing_lh_22 = 1;
				hind_lamps.threat_warning_bearing_rh_22 = 1;
				hind_lamps.threat_warning_bearing_rh_45 = 1;
				hind_lamps.threat_warning_bearing_rh_67 = 1;
				hind_lamps.threat_warning_bearing_rh_90 = 1;
				hind_lamps.threat_warning_bearing_rh_rear = 1;
			}
			else
			{
				timer = 0.0;
			}
		}
		////////////////////////////////////////
		//
		// test close range lamps
		//
		////////////////////////////////////////
		{
			static float
				timer = 0.0;

			hind_lamps.threat_warning_close_range_1 = 0;
			hind_lamps.threat_warning_close_range_2 = 0;
			hind_lamps.threat_warning_close_range_3 = 0;
			hind_lamps.threat_warning_close_range_4 = 0;
			hind_lamps.threat_warning_close_range_5 = 0;
			hind_lamps.threat_warning_close_range_6 = 0;
			hind_lamps.threat_warning_close_range_7 = 0;
			hind_lamps.threat_warning_close_range_8 = 0;
			hind_lamps.threat_warning_close_range_9 = 0;
			hind_lamps.threat_warning_close_range_10 = 0;
			hind_lamps.threat_warning_close_range_11 = 0;
			hind_lamps.threat_warning_close_range_12 = 0;
			hind_lamps.threat_warning_close_range_13 = 0;
			hind_lamps.threat_warning_close_range_14 = 0;
			hind_lamps.threat_warning_close_range_15 = 0;

			timer += get_delta_time ();

			if (timer < (ONE_SECOND * 1.0))
			{
				hind_lamps.threat_warning_close_range_1 = 1;
			}
			else if (timer < (ONE_SECOND * 2.0))
			{
				hind_lamps.threat_warning_close_range_2 = 1;
			}
			else if (timer < (ONE_SECOND * 3.0))
			{
				hind_lamps.threat_warning_close_range_3 = 1;
			}
			else if (timer < (ONE_SECOND * 4.0))
			{
				hind_lamps.threat_warning_close_range_4 = 1;
			}
			else if (timer < (ONE_SECOND * 5.0))
			{
				hind_lamps.threat_warning_close_range_5 = 1;
			}
			else if (timer < (ONE_SECOND * 6.0))
			{
				hind_lamps.threat_warning_close_range_6 = 1;
			}
			else if (timer < (ONE_SECOND * 7.0))
			{
				hind_lamps.threat_warning_close_range_7 = 1;
			}
			else if (timer < (ONE_SECOND * 8.0))
			{
				hind_lamps.threat_warning_close_range_8 = 1;
			}
			else if (timer < (ONE_SECOND * 9.0))
			{
				hind_lamps.threat_warning_close_range_9 = 1;
			}
			else if (timer < (ONE_SECOND * 10.0))
			{
				hind_lamps.threat_warning_close_range_10 = 1;
			}
			else if (timer < (ONE_SECOND * 11.0))
			{
				hind_lamps.threat_warning_close_range_11 = 1;
			}
			else if (timer < (ONE_SECOND * 12.0))
			{
				hind_lamps.threat_warning_close_range_12 = 1;
			}
			else if (timer < (ONE_SECOND * 13.0))
			{
				hind_lamps.threat_warning_close_range_13 = 1;
			}
			else if (timer < (ONE_SECOND * 14.0))
			{
				hind_lamps.threat_warning_close_range_14 = 1;
			}
			else if (timer < (ONE_SECOND * 15.0))
			{
				hind_lamps.threat_warning_close_range_15 = 1;
			}
			else if (timer < (ONE_SECOND * 16.0))
			{
				hind_lamps.threat_warning_close_range_1 = 1;
				hind_lamps.threat_warning_close_range_2 = 1;
				hind_lamps.threat_warning_close_range_3 = 1;
				hind_lamps.threat_warning_close_range_4 = 1;
				hind_lamps.threat_warning_close_range_5 = 1;
				hind_lamps.threat_warning_close_range_6 = 1;
				hind_lamps.threat_warning_close_range_7 = 1;
				hind_lamps.threat_warning_close_range_8 = 1;
				hind_lamps.threat_warning_close_range_9 = 1;
				hind_lamps.threat_warning_close_range_10 = 1;
				hind_lamps.threat_warning_close_range_11 = 1;
				hind_lamps.threat_warning_close_range_12 = 1;
				hind_lamps.threat_warning_close_range_13 = 1;
				hind_lamps.threat_warning_close_range_14 = 1;
				hind_lamps.threat_warning_close_range_15 = 1;
			}
			else
			{
				timer = 0.0;
			}
		}
		////////////////////////////////////////
		//
		// test radar lock lamps
		//
		////////////////////////////////////////
		{
			static float
				timer = 0.0;

			hind_lamps.threat_warning_missile_below = 0;
			hind_lamps.threat_warning_missile_above = 0;
			hind_lamps.threat_warning_missile_lh_lock = 0;
			hind_lamps.threat_warning_missile_rh_lock = 0;

			timer += get_delta_time ();

			if (timer < (ONE_SECOND * 1.0))
			{
				hind_lamps.threat_warning_missile_below = 1;
			}
			else if (timer < (ONE_SECOND * 2.0))
			{
				hind_lamps.threat_warning_missile_above = 1;
			}
			else if (timer < (ONE_SECOND * 3.0))
			{
				hind_lamps.threat_warning_missile_lh_lock = 1;
			}
			else if (timer < (ONE_SECOND * 4.0))
			{
				hind_lamps.threat_warning_missile_rh_lock = 1;
			}
			else if (timer < (ONE_SECOND * 5.0))
			{
				hind_lamps.threat_warning_missile_below = 1;
				hind_lamps.threat_warning_missile_above = 1;
				hind_lamps.threat_warning_missile_lh_lock = 1;
				hind_lamps.threat_warning_missile_rh_lock = 1;
			}
			else
			{
				timer = 0.0;
			}
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (460)
			#define Y_ORG (379)

			draw_lamp (hind_lamps.threat_warning_radar_type_1							, X_ORG +   6, Y_ORG +  54, 390, 235,   9,   6, 229);	// (10% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_2							, X_ORG +  15, Y_ORG +  54, 399, 235,   8,   6, 227);	// (11% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_3							, X_ORG +  23, Y_ORG +  54, 407, 235,   8,   6, 224);	// (12% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_4							, X_ORG +  31, Y_ORG +  54, 415, 235,   8,   6, 222);	// (13% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_5							, X_ORG +  39, Y_ORG +  54, 423, 235,   9,   6, 219);	// (14% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_6							, X_ORG +  48, Y_ORG +  54, 432, 235,   8,   6, 217);	// (15% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear						, X_ORG +  14, Y_ORG +  47, 398, 228,   7,   7, 214);	// (16% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear						, X_ORG +  40, Y_ORG +  47, 424, 228,   7,   7, 212);	// (17% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_1						, X_ORG +  21, Y_ORG +  43, 405, 224,   6,   3, 209);	// (18% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_2						, X_ORG +  16, Y_ORG +  39, 400, 220,   5,   5, 207);	// (19% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_3						, X_ORG +  12, Y_ORG +  33, 396, 214,   5,   6, 204);	// (20% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_4						, X_ORG +  11, Y_ORG +  25, 395, 206,   3,   8, 201);	// (21% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_5						, X_ORG +  11, Y_ORG +  19, 395, 200,   5,   6, 199);	// (22% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_6						, X_ORG +  14, Y_ORG +  15, 398, 196,   5,   4, 196);	// (23% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_7						, X_ORG +  18, Y_ORG +  12, 402, 193,   7,   4, 194);	// (24% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_8						, X_ORG +  25, Y_ORG +  12, 409, 193,   4,   2, 191);	// (25% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_9						, X_ORG +  29, Y_ORG +  12, 413, 193,   7,   4, 189);	// (26% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_10						, X_ORG +  35, Y_ORG +  14, 419, 195,   7,   7, 186);	// (27% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_11						, X_ORG +  40, Y_ORG +  20, 424, 201,   5,   6, 184);	// (28% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_12						, X_ORG +  43, Y_ORG +  26, 427, 207,   3,   7, 181);	// (29% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_13						, X_ORG +  42, Y_ORG +  33, 426, 214,   3,   5, 178);	// (30% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_14						, X_ORG +  38, Y_ORG +  38, 422, 219,   6,   5, 176);	// (31% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_15						, X_ORG +  33, Y_ORG +  43, 417, 224,   6,   4, 173);	// (32% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90_close_range		, X_ORG +   7, Y_ORG +  23, 391, 204,   4,   5, 171);	// (33% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67_close_range		, X_ORG +  10, Y_ORG +  16, 394, 197,   4,   4, 168);	// (34% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45_close_range		, X_ORG +  14, Y_ORG +  11, 398, 192,   4,   4, 166);	// (35% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22_close_range		, X_ORG +  21, Y_ORG +   8, 405, 189,   4,   4, 163);	// (36% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22_close_range		, X_ORG +  28, Y_ORG +   8, 412, 189,   4,   4, 161);	// (37% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45_close_range		, X_ORG +  35, Y_ORG +  11, 419, 192,   4,   4, 158);	// (38% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67_close_range		, X_ORG +  41, Y_ORG +  16, 425, 197,   4,   4, 156);	// (39% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90_close_range		, X_ORG +  45, Y_ORG +  23, 429, 204,   4,   5, 153);	// (40% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90						, X_ORG +   1, Y_ORG +  21, 385, 202,   7,   7, 150);	// (41% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67						, X_ORG +   4, Y_ORG +  12, 388, 193,   7,   7, 148);	// (42% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45						, X_ORG +  10, Y_ORG +   5, 394, 186,   6,   7, 145);	// (43% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22						, X_ORG +  18, Y_ORG +   2, 402, 183,   7,   6, 143);	// (44% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22						, X_ORG +  27, Y_ORG +   2, 411, 183,   7,   6, 140);	// (45% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45						, X_ORG +  36, Y_ORG +   5, 420, 186,   7,   7, 138);	// (46% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67						, X_ORG +  43, Y_ORG +  12, 427, 193,   7,   7, 135);	// (47% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90						, X_ORG +  48, Y_ORG +  21, 432, 202,   7,   7, 133);	// (48% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_below						, X_ORG +  23, Y_ORG +  27, 407, 208,  11,   5, 130);	// (49% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_above						, X_ORG +  23, Y_ORG +  22, 407, 203,  10,   5, 127);	// (50% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_lh_lock		 				, X_ORG +  17, Y_ORG +  17, 401, 198,  11,  24, 125);	// (51% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_rh_lock						, X_ORG +  29, Y_ORG +  17, 413, 198,  11,  23, 122);	// (52% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear_close_range		, X_ORG +  17, Y_ORG +  44, 401, 225,   4,   4, 120);	// (53% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear_close_range		, X_ORG +  39, Y_ORG +  44, 423, 225,   4,   4, 117);	// (54% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (162)
			#define Y_ORG (377)

			draw_lamp (hind_lamps.threat_warning_radar_type_1							, X_ORG +   6, Y_ORG +  55, 332, 236,   9,   7, 229);	// (10% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_2							, X_ORG +  15, Y_ORG +  54, 341, 235,   9,   6, 227);	// (11% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_3							, X_ORG +  24, Y_ORG +  52, 350, 233,   7,   7, 224);	// (12% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_4							, X_ORG +  31, Y_ORG +  51, 357, 232,   8,   7, 222);	// (13% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_5							, X_ORG +  39, Y_ORG +  50, 365, 231,   7,   6, 219);	// (14% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_6							, X_ORG +  46, Y_ORG +  48, 372, 229,   9,   7, 217);	// (15% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear						, X_ORG +  14, Y_ORG +  48, 340, 229,   7,   6, 214);	// (16% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear						, X_ORG +  40, Y_ORG +  43, 366, 224,   6,   7, 212);	// (17% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_1						, X_ORG +  21, Y_ORG +  43, 347, 224,   6,   3, 209);	// (18% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_2						, X_ORG +  15, Y_ORG +  39, 341, 220,   7,   5, 207);	// (19% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_3						, X_ORG +  11, Y_ORG +  33, 337, 214,   6,   6, 204);	// (20% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_4						, X_ORG +  11, Y_ORG +  27, 337, 208,   3,   6, 201);	// (21% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_5						, X_ORG +  12, Y_ORG +  21, 338, 202,   4,   6, 199);	// (22% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_6						, X_ORG +  14, Y_ORG +  16, 340, 197,   5,   5, 196);	// (23% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_7						, X_ORG +  19, Y_ORG +  12, 345, 193,   6,   5, 194);	// (24% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_8						, X_ORG +  25, Y_ORG +  11, 351, 192,   4,   3, 191);	// (25% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_9						, X_ORG +  29, Y_ORG +  11, 355, 192,   7,   4, 189);	// (26% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_10						, X_ORG +  35, Y_ORG +  13, 361, 194,   6,   4, 186);	// (27% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_11						, X_ORG +  39, Y_ORG +  17, 365, 198,   5,   6, 184);	// (28% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_12						, X_ORG +  42, Y_ORG +  23, 368, 204,   3,   6, 181);	// (29% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_13						, X_ORG +  42, Y_ORG +  29, 368, 210,   3,   6, 178);	// (30% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_14						, X_ORG +  38, Y_ORG +  35, 364, 216,   6,   6, 176);	// (31% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_15						, X_ORG +  33, Y_ORG +  40, 359, 221,   6,   4, 173);	// (32% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90_close_range		, X_ORG +   8, Y_ORG +  25, 334, 206,   4,   4, 171);	// (33% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67_close_range		, X_ORG +  10, Y_ORG +  18, 336, 199,   4,   4, 168);	// (34% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45_close_range		, X_ORG +  15, Y_ORG +  12, 341, 193,   4,   4, 166);	// (35% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22_close_range		, X_ORG +  21, Y_ORG +   8, 347, 189,   4,   4, 163);	// (36% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22_close_range		, X_ORG +  28, Y_ORG +   7, 354, 188,   4,   4, 161);	// (37% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45_close_range		, X_ORG +  35, Y_ORG +   9, 361, 190,   4,   4, 158);	// (38% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67_close_range		, X_ORG +  41, Y_ORG +  13, 367, 194,   3,   4, 156);	// (39% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90_close_range		, X_ORG +  44, Y_ORG +  20, 370, 201,   4,   4, 153);	// (40% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90						, X_ORG +   2, Y_ORG +  23, 328, 204,   6,   7, 150);	// (41% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67						, X_ORG +   4, Y_ORG +  14, 330, 195,   7,   7, 148);	// (42% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45						, X_ORG +  10, Y_ORG +   7, 336, 188,   7,   6, 145);	// (43% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22						, X_ORG +  18, Y_ORG +   2, 344, 183,   7,   6, 143);	// (44% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22						, X_ORG +  27, Y_ORG +   1, 353, 182,   7,   6, 140);	// (45% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45						, X_ORG +  36, Y_ORG +   3, 362, 184,   6,   7, 138);	// (46% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67						, X_ORG +  43, Y_ORG +   9, 369, 190,   6,   6, 135);	// (47% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90						, X_ORG +  47, Y_ORG +  17, 373, 198,   6,   6, 133);	// (48% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_below						, X_ORG +  23, Y_ORG +  25, 349, 206,  11,   7, 130);	// (49% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_above						, X_ORG +  23, Y_ORG +  21, 349, 202,  10,   6, 127);	// (50% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_lh_lock		 				, X_ORG +  16, Y_ORG +  17, 342, 198,  12,  23, 125);	// (51% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_rh_lock						, X_ORG +  29, Y_ORG +  16, 355, 197,  11,  23, 122);	// (52% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear_close_range		, X_ORG +  17, Y_ORG +  44, 343, 225,   5,   4, 120);	// (53% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear_close_range		, X_ORG +  38, Y_ORG +  41, 364, 222,   4,   4, 117);	// (54% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (453)
			#define Y_ORG (182)

			draw_lamp (hind_lamps.threat_warning_radar_type_1							, X_ORG +   5, Y_ORG +  49, 274, 230,   8,   6, 229);	// (10% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_2							, X_ORG +  13, Y_ORG +  49, 282, 230,   8,   6, 227);	// (11% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_3							, X_ORG +  21, Y_ORG +  49, 290, 230,   8,   6, 224);	// (12% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_4							, X_ORG +  29, Y_ORG +  49, 298, 230,   7,   6, 222);	// (13% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_5							, X_ORG +  36, Y_ORG +  49, 305, 230,   8,   6, 219);	// (14% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_6							, X_ORG +  44, Y_ORG +  49, 313, 230,   8,   6, 217);	// (15% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear						, X_ORG +  12, Y_ORG +  43, 281, 224,   7,   6, 214);	// (16% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear						, X_ORG +  38, Y_ORG +  43, 307, 224,   6,   6, 212);	// (17% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_1						, X_ORG +  20, Y_ORG +  40, 289, 221,   5,   3, 209);	// (18% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_2						, X_ORG +  15, Y_ORG +  36, 284, 217,   5,   5, 207);	// (19% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_3						, X_ORG +  12, Y_ORG +  30, 281, 211,   4,   6, 204);	// (20% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_4						, X_ORG +  12, Y_ORG +  24, 281, 205,   3,   6, 201);	// (21% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_5						, X_ORG +  13, Y_ORG +  19, 282, 200,   3,   5, 199);	// (22% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_6						, X_ORG +  16, Y_ORG +  14, 285, 195,   4,   5, 196);	// (23% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_7						, X_ORG +  20, Y_ORG +  11, 289, 192,   6,   4, 194);	// (24% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_8						, X_ORG +  26, Y_ORG +  11, 295, 192,   5,   2, 191);	// (25% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_9						, X_ORG +  31, Y_ORG +  11, 300, 192,   6,   4, 189);	// (26% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_10						, X_ORG +  37, Y_ORG +  14, 306, 195,   4,   5, 186);	// (27% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_11						, X_ORG +  41, Y_ORG +  19, 310, 200,   3,   6, 184);	// (28% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_12						, X_ORG +  42, Y_ORG +  25, 311, 206,   3,   5, 181);	// (29% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_13						, X_ORG +  40, Y_ORG +  30, 309, 211,   5,   6, 178);	// (30% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_14						, X_ORG +  37, Y_ORG +  36, 306, 217,   5,   4, 176);	// (31% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_15						, X_ORG +  31, Y_ORG +  39, 300, 220,   6,   4, 173);	// (32% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90_close_range		, X_ORG +   9, Y_ORG +  22, 278, 203,   4,   4, 171);	// (33% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67_close_range		, X_ORG +  12, Y_ORG +  15, 281, 196,   4,   4, 168);	// (34% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45_close_range		, X_ORG +  16, Y_ORG +  10, 285, 191,   4,   4, 166);	// (35% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22_close_range		, X_ORG +  23, Y_ORG +   7, 292, 188,   4,   4, 163);	// (36% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22_close_range		, X_ORG +  30, Y_ORG +   7, 299, 188,   4,   4, 161);	// (37% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45_close_range		, X_ORG +  36, Y_ORG +  10, 305, 191,   4,   4, 158);	// (38% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67_close_range		, X_ORG +  41, Y_ORG +  15, 310, 196,   4,   4, 156);	// (39% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90_close_range		, X_ORG +  44, Y_ORG +  22, 313, 203,   4,   4, 153);	// (40% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90						, X_ORG +   3, Y_ORG +  19, 272, 200,   6,   7, 150);	// (41% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67						, X_ORG +   6, Y_ORG +  11, 275, 192,   7,   7, 148);	// (42% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45						, X_ORG +  12, Y_ORG +   5, 281, 186,   7,   6, 145);	// (43% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22						, X_ORG +  21, Y_ORG +   2, 290, 183,   6,   6, 143);	// (44% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22						, X_ORG +  30, Y_ORG +   2, 299, 183,   6,   6, 140);	// (45% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45						, X_ORG +  38, Y_ORG +   5, 307, 186,   6,   6, 138);	// (46% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67						, X_ORG +  44, Y_ORG +  11, 313, 192,   7,   7, 135);	// (47% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90						, X_ORG +  48, Y_ORG +  20, 317, 201,   6,   6, 133);	// (48% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_below						, X_ORG +  23, Y_ORG +  25, 292, 206,  11,   5, 130);	// (49% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_above						, X_ORG +  23, Y_ORG +  21, 292, 202,  11,   4, 127);	// (50% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_lh_lock		 				, X_ORG +  17, Y_ORG +  16, 286, 197,  11,  23, 125);	// (51% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_rh_lock						, X_ORG +  29, Y_ORG +  16, 298, 197,  11,  23, 122);	// (52% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear_close_range		, X_ORG +  16, Y_ORG +  41, 285, 222,   4,   4, 120);	// (53% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear_close_range		, X_ORG +  36, Y_ORG +  41, 305, 222,   5,   4, 117);	// (54% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (168)
			#define Y_ORG (179)

			draw_lamp (hind_lamps.threat_warning_radar_type_1							, X_ORG +   9, Y_ORG +  52, 221, 233,   8,   6, 229);	// (10% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_2							, X_ORG +  17, Y_ORG +  51, 229, 232,   8,   6, 227);	// (11% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_3							, X_ORG +  25, Y_ORG +  49, 237, 230,   7,   7, 224);	// (12% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_4							, X_ORG +  32, Y_ORG +  48, 244, 229,   8,   6, 222);	// (13% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_5							, X_ORG +  40, Y_ORG +  47, 252, 228,   6,   6, 219);	// (14% alpha)
			draw_lamp (hind_lamps.threat_warning_radar_type_6							, X_ORG +  46, Y_ORG +  46, 258, 227,   8,   6, 217);	// (15% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear						, X_ORG +  16, Y_ORG +  45, 228, 226,   6,   6, 214);	// (16% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear						, X_ORG +  40, Y_ORG +  41, 252, 222,   6,   6, 212);	// (17% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_1						, X_ORG +  22, Y_ORG +  41, 234, 222,   5,   2, 209);	// (18% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_2						, X_ORG +  16, Y_ORG +  37, 228, 218,   6,   5, 207);	// (19% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_3						, X_ORG +  12, Y_ORG +  32, 224, 213,   5,   6, 204);	// (20% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_4						, X_ORG +  12, Y_ORG +  27, 224, 208,   2,   5, 201);	// (21% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_5						, X_ORG +  12, Y_ORG +  21, 224, 202,   2,   6, 199);	// (22% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_6						, X_ORG +  13, Y_ORG +  15, 225, 196,   6,   6, 196);	// (23% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_7						, X_ORG +  18, Y_ORG +  12, 230, 193,   5,   4, 194);	// (24% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_8						, X_ORG +  23, Y_ORG +  11, 235, 192,   4,   3, 191);	// (25% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_9						, X_ORG +  27, Y_ORG +  12, 239, 193,   6,   3, 189);	// (26% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_10						, X_ORG +  33, Y_ORG +  13, 245, 194,   5,   5, 186);	// (27% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_11						, X_ORG +  38, Y_ORG +  18, 250, 199,   4,   5, 184);	// (28% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_12						, X_ORG +  41, Y_ORG +  23, 253, 204,   2,   5, 181);	// (29% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_13						, X_ORG +  41, Y_ORG +  29, 253, 210,   2,   5, 178);	// (30% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_14						, X_ORG +  37, Y_ORG +  34, 249, 215,   5,   5, 176);	// (31% alpha)
			draw_lamp (hind_lamps.threat_warning_close_range_15						, X_ORG +  33, Y_ORG +  39, 245, 220,   5,   3, 173);	// (32% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90_close_range		, X_ORG +   8, Y_ORG +  25, 220, 206,   4,   4, 171);	// (33% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67_close_range		, X_ORG +   9, Y_ORG +  18, 221, 199,   4,   4, 168);	// (34% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45_close_range		, X_ORG +  13, Y_ORG +  12, 225, 193,   4,   4, 166);	// (35% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22_close_range		, X_ORG +  19, Y_ORG +   9, 231, 190,   4,   4, 163);	// (36% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22_close_range		, X_ORG +  26, Y_ORG +   8, 238, 189,   4,   4, 161);	// (37% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45_close_range		, X_ORG +  33, Y_ORG +  10, 245, 191,   3,   3, 158);	// (38% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67_close_range		, X_ORG +  38, Y_ORG +  14, 250, 195,   4,   4, 156);	// (39% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90_close_range		, X_ORG +  42, Y_ORG +  20, 254, 201,   4,   4, 153);	// (40% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_90						, X_ORG +   2, Y_ORG +  23, 214, 204,   6,   7, 150);	// (41% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_67						, X_ORG +   3, Y_ORG +  14, 215, 195,   7,   7, 148);	// (42% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_45						, X_ORG +   8, Y_ORG +   7, 220, 188,   7,   7, 145);	// (43% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22						, X_ORG +  16, Y_ORG +   3, 228, 184,   6,   6, 143);	// (44% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_22						, X_ORG +  25, Y_ORG +   2, 237, 183,   6,   6, 140);	// (45% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_45						, X_ORG +  33, Y_ORG +   4, 245, 185,   7,   7, 138);	// (46% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_67						, X_ORG +  40, Y_ORG +  10, 252, 191,   6,   6, 135);	// (47% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_90						, X_ORG +  45, Y_ORG +  17, 257, 198,   6,   6, 133);	// (48% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_below						, X_ORG +  23, Y_ORG +  25, 235, 206,   9,   6, 130);	// (49% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_above						, X_ORG +  23, Y_ORG +  21, 235, 202,   9,   6, 127);	// (50% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_lh_lock		 				, X_ORG +  16, Y_ORG +  17, 228, 198,  12,  22, 125);	// (51% alpha)
			draw_lamp (hind_lamps.threat_warning_missile_rh_lock						, X_ORG +  27, Y_ORG +  17, 239, 198,  12,  20, 122);	// (52% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_rear_close_range		, X_ORG +  18, Y_ORG +  42, 230, 223,   5,   4, 120);	// (53% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_rh_rear_close_range		, X_ORG +  38, Y_ORG +  39, 250, 220,   4,   4, 117);	// (54% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			#define X_ORG (605)
			#define Y_ORG (465)

			draw_lamp (hind_lamps.threat_warning_bearing_lh_45						, X_ORG +   3, Y_ORG +  10, 180, 234,  12,   5, 145);	// (43% alpha)
			draw_lamp (hind_lamps.threat_warning_bearing_lh_22						, X_ORG +  18, Y_ORG +   3, 195, 227,  14,  12, 143);	// (44% alpha)

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

void draw_hind_master_caution_lamp (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		timer += get_delta_time ();

		if (timer < (ONE_SECOND * 1.0))
		{
			hind_lamps.master_caution = 0;
		}
		else
		{
			hind_lamps.master_caution = 1;

			if (timer > (ONE_SECOND * 2.0))
			{
				timer = 0.0;
			}
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (452)
			#define Y_ORG (328)

			draw_lamp (hind_lamps.master_caution, X_ORG +   1, Y_ORG +   0, 348, 150,  38,  28, 232);	// (9% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (154)
			#define Y_ORG (328)

			draw_lamp (hind_lamps.master_caution, X_ORG +   1, Y_ORG +   0, 303, 150,  40,  29, 232);	// (9% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			#define X_ORG (453)
			#define Y_ORG (132)

			draw_lamp (hind_lamps.master_caution, X_ORG +   0, Y_ORG +   0, 257, 150,  39,  29, 232);	// (9% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (153)
			#define Y_ORG (132)

			draw_lamp (hind_lamps.master_caution, X_ORG +   1, Y_ORG +   0, 213, 150,  42,  29, 232);	// (9% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			#define X_ORG (0)
			#define Y_ORG (372)

			draw_lamp (hind_lamps.master_caution, X_ORG +   2, Y_ORG +   1, 214,  96,  71,  50, 232);	// (9% alpha)

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

void draw_hind_warning_panel_lamps (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		hind_lamps.warning_1 = 0;
		hind_lamps.warning_2 = 0;
		hind_lamps.warning_3 = 0;
		hind_lamps.warning_4 = 0;
		hind_lamps.warning_5 = 0;
		hind_lamps.warning_6 = 0;
		hind_lamps.warning_7 = 0;
		hind_lamps.warning_8 = 0;

		timer += get_delta_time ();

		if (timer < (ONE_SECOND * 1.0))
		{
			hind_lamps.warning_1 = 1;
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			hind_lamps.warning_2 = 1;
		}
		else if (timer < (ONE_SECOND * 3.0))
		{
			hind_lamps.warning_3 = 1;
		}
		else if (timer < (ONE_SECOND * 4.0))
		{
			hind_lamps.warning_4 = 1;
		}
		else if (timer < (ONE_SECOND * 5.0))
		{
			hind_lamps.warning_5 = 1;
		}
		else if (timer < (ONE_SECOND * 6.0))
		{
			hind_lamps.warning_6 = 1;
		}
		else if (timer < (ONE_SECOND * 7.0))
		{
			hind_lamps.warning_7 = 1;
		}
		else if (timer < (ONE_SECOND * 8.0))
		{
			hind_lamps.warning_8 = 1;
		}
		else if (timer < (ONE_SECOND * 9.0))
		{
			hind_lamps.warning_1 = 1;
			hind_lamps.warning_2 = 1;
			hind_lamps.warning_3 = 1;
			hind_lamps.warning_4 = 1;
			hind_lamps.warning_5 = 1;
			hind_lamps.warning_6 = 1;
			hind_lamps.warning_7 = 1;
			hind_lamps.warning_8 = 1;
		}
		else
		{
			timer = 0.0;
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (456)
			#define Y_ORG (325)

			draw_lamp (hind_lamps.warning_1, X_ORG +   2, Y_ORG +   1, 434,   2,  23,  11,  71);	// (72% alpha)
			draw_lamp (hind_lamps.warning_2, X_ORG +  25, Y_ORG +   1, 457,   2,  23,  11,  69);	// (73% alpha)
			draw_lamp (hind_lamps.warning_3, X_ORG +   3, Y_ORG +  13, 435,  14,  23,  11,  66);	// (74% alpha)
			draw_lamp (hind_lamps.warning_4, X_ORG +  26, Y_ORG +  13, 458,  14,  23,  11,  64);	// (75% alpha)
			draw_lamp (hind_lamps.warning_5, X_ORG +   3, Y_ORG +  24, 435,  25,  24,  11,  61);	// (76% alpha)
			draw_lamp (hind_lamps.warning_6, X_ORG +  27, Y_ORG +  24, 459,  25,  23,  11,  59);	// (77% alpha)
			draw_lamp (hind_lamps.warning_7, X_ORG +   4, Y_ORG +  36, 436,  37,  24,  11,  56);	// (78% alpha)
			draw_lamp (hind_lamps.warning_8, X_ORG +  28, Y_ORG +  36, 460,  37,  23,  11,  54);	// (79% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (159)
			#define Y_ORG (323)

			draw_lamp (hind_lamps.warning_1, X_ORG +   1, Y_ORG +   2, 487,   3,  24,  14,  71);	// (72% alpha)
			draw_lamp (hind_lamps.warning_2, X_ORG +  24, Y_ORG +   1, 510,   2,  22,  12,  69);	// (73% alpha)
			draw_lamp (hind_lamps.warning_3, X_ORG +   3, Y_ORG +  13, 489,  14,  22,  13,  66);	// (74% alpha)
			draw_lamp (hind_lamps.warning_4, X_ORG +  25, Y_ORG +  12, 511,  13,  22,  12,  64);	// (75% alpha)
			draw_lamp (hind_lamps.warning_5, X_ORG +   3, Y_ORG +  24, 489,  25,  24,  15,  61);	// (76% alpha)
			draw_lamp (hind_lamps.warning_6, X_ORG +  26, Y_ORG +  23, 512,  24,  22,  12,  59);	// (77% alpha)
			draw_lamp (hind_lamps.warning_7, X_ORG +   4, Y_ORG +  36, 490,  37,  24,  14,  56);	// (78% alpha)
			draw_lamp (hind_lamps.warning_8, X_ORG +  27, Y_ORG +  34, 513,  35,  22,  14,  54);	// (79% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (457)
			#define Y_ORG (129)

			draw_lamp (hind_lamps.warning_1, X_ORG +   2, Y_ORG +   1, 539,   2,  22,  12,  71);	// (72% alpha)
			draw_lamp (hind_lamps.warning_2, X_ORG +  24, Y_ORG +   1, 561,   2,  23,  12,  69);	// (73% alpha)
			draw_lamp (hind_lamps.warning_3, X_ORG +   2, Y_ORG +  13, 539,  14,  22,  11,  66);	// (74% alpha)
			draw_lamp (hind_lamps.warning_4, X_ORG +  24, Y_ORG +  13, 561,  14,  23,  11,  64);	// (75% alpha)
			draw_lamp (hind_lamps.warning_5, X_ORG +   2, Y_ORG +  24, 539,  25,  22,  11,  61);	// (76% alpha)
			draw_lamp (hind_lamps.warning_6, X_ORG +  24, Y_ORG +  24, 561,  25,  23,  11,  59);	// (77% alpha)
			draw_lamp (hind_lamps.warning_7, X_ORG +   2, Y_ORG +  35, 539,  36,  22,  12,  56);	// (78% alpha)
			draw_lamp (hind_lamps.warning_8, X_ORG +  24, Y_ORG +  35, 561,  36,  23,  12,  54);	// (79% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (158)
			#define Y_ORG (127)

			draw_lamp (hind_lamps.warning_1, X_ORG +   1, Y_ORG +   3, 587,   4,  24,  13,  71);	// (72% alpha)
			draw_lamp (hind_lamps.warning_2, X_ORG +  24, Y_ORG +   1, 610,   2,  23,  12,  69);	// (73% alpha)
			draw_lamp (hind_lamps.warning_3, X_ORG +   3, Y_ORG +  14, 589,  15,  24,  13,  66);	// (74% alpha)
			draw_lamp (hind_lamps.warning_4, X_ORG +  25, Y_ORG +  12, 611,  13,  24,  13,  64);	// (75% alpha)
			draw_lamp (hind_lamps.warning_5, X_ORG +   5, Y_ORG +  25, 591,  26,  25,  14,  61);	// (76% alpha)
			draw_lamp (hind_lamps.warning_6, X_ORG +  29, Y_ORG +  23, 615,  24,  22,  12,  59);	// (77% alpha)
			draw_lamp (hind_lamps.warning_7, X_ORG +   8, Y_ORG +  36, 594,  37,  23,  13,  56);	// (78% alpha)
			draw_lamp (hind_lamps.warning_8, X_ORG +  30, Y_ORG +  34, 616,  35,  23,  13,  54);	// (79% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			#define X_ORG (582)
			#define Y_ORG (362)

			draw_lamp (hind_lamps.warning_1, X_ORG +   7, Y_ORG +   6, 407,  75,  42,  19,  71);	// (72% alpha)
			draw_lamp (hind_lamps.warning_2, X_ORG +  51, Y_ORG +   6, 451,  75,   7,  19,  69);	// (73% alpha)
			draw_lamp (hind_lamps.warning_3, X_ORG +   8, Y_ORG +  27, 408,  96,  43,  19,  66);	// (74% alpha)
			draw_lamp (hind_lamps.warning_4, X_ORG +  52, Y_ORG +  27, 452,  96,   6,  19,  64);	// (75% alpha)
			draw_lamp (hind_lamps.warning_5, X_ORG +  10, Y_ORG +  48, 410, 117,  43,  20,  61);	// (76% alpha)
			draw_lamp (hind_lamps.warning_6, X_ORG +  54, Y_ORG +  48, 454, 117,   4,  20,  59);	// (77% alpha)
			draw_lamp (hind_lamps.warning_7, X_ORG +  11, Y_ORG +  70, 411, 139,  43,  20,  56);	// (78% alpha)
			draw_lamp (hind_lamps.warning_8, X_ORG +  56, Y_ORG +  70, 456, 139,   2,  20,  54);	// (79% alpha)

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

void draw_hind_radio_lamp (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		timer += get_delta_time ();

		if (timer < (ONE_SECOND * 1.0))
		{
			hind_lamps.radio = 0;
		}
		else
		{
			hind_lamps.radio = 1;

			if (timer > (ONE_SECOND * 2.0))
			{
				timer = 0.0;
			}
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (585)
			#define Y_ORG (376)

			draw_lamp (hind_lamps.radio, X_ORG +   1, Y_ORG +   1, 401,  50,  29,  17,  74);	// (71% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (313)
			#define Y_ORG (335)

			draw_lamp (hind_lamps.radio, X_ORG +   1, Y_ORG +   1, 401,  29,  24,  19,  74);	// (71% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			#define X_ORG (39)
			#define Y_ORG (368)

			draw_lamp (hind_lamps.radio, X_ORG +   0, Y_ORG +   1, 400,   2,  30,  25,  74);	// (71% alpha)

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

void draw_hind_oil_gauges (cockpit_panels panel)
{
	unsigned char
		*sprite_data,
		*mask_data;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

	if (test_cockpit_instruments)
	{
		static float
			timer = 0.0;

		hind_lamps.lh_engine_oil_pressure_normal = 0;
		hind_lamps.rh_engine_oil_pressure_normal = 0;
		hind_lamps.lh_engine_oil_pressure_low = 0;
		hind_lamps.rh_engine_oil_pressure_low = 0;
		hind_lamps.lh_engine_oil_temperature_normal = 0;
		hind_lamps.rh_engine_oil_temperature_normal = 0;
		hind_lamps.lh_engine_oil_temperature_high = 0;
		hind_lamps.rh_engine_oil_temperature_high = 0;

		timer += get_delta_time ();

		if (timer < (ONE_SECOND * 1.0))
		{
			hind_lamps.lh_engine_oil_pressure_normal = 1;
			hind_lamps.rh_engine_oil_pressure_normal = 1;
			hind_lamps.lh_engine_oil_temperature_normal = 1;
			hind_lamps.rh_engine_oil_temperature_normal = 1;
		}
		else if (timer < (ONE_SECOND * 2.0))
		{
			hind_lamps.lh_engine_oil_pressure_low = 1;
			hind_lamps.rh_engine_oil_pressure_low = 1;
			hind_lamps.lh_engine_oil_temperature_high = 1;
			hind_lamps.rh_engine_oil_temperature_high = 1;
		}
		else if (timer > (ONE_SECOND * 3.0))
		{
			timer = 0.0;
		}
	}

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			#define X_ORG (547)
			#define Y_ORG (383)

			draw_lamp (hind_lamps.lh_engine_oil_pressure_normal		, X_ORG +   2, Y_ORG +   2, 580,  55,   3,  13,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_pressure_normal		, X_ORG +  13, Y_ORG +   2, 591,  55,   4,  13,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (547)
			#define Y_ORG (393)

			draw_lamp (hind_lamps.lh_engine_oil_pressure_low			, X_ORG +   1, Y_ORG +   1, 579,  90,   4,   5,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_pressure_low			, X_ORG +  13, Y_ORG +   1, 591,  90,   4,   5,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (547)
			#define Y_ORG (420)

			draw_lamp (hind_lamps.lh_engine_oil_temperature_normal	, X_ORG +   1, Y_ORG +   1, 579,  72,   5,  15,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_temperature_normal	, X_ORG +  13, Y_ORG +   1, 591,  72,   5,  15,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (547)
			#define Y_ORG (410)

			draw_lamp (hind_lamps.lh_engine_oil_temperature_high		, X_ORG +   1, Y_ORG +   1, 576,  99,   4,  25,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_temperature_high		, X_ORG +  13, Y_ORG +   1, 588,  99,   4,  25,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			#define X_ORG (284)
			#define Y_ORG (353)

			draw_lamp (hind_lamps.lh_engine_oil_pressure_normal		, X_ORG +   1, Y_ORG +   4, 600,  57,   4,  12,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_pressure_normal		, X_ORG +  11, Y_ORG +   1, 610,  54,   4,  12,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (284)
			#define Y_ORG (362)

			draw_lamp (hind_lamps.lh_engine_oil_pressure_low			, X_ORG +   2, Y_ORG +   3, 601,  92,   4,   5,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_pressure_low			, X_ORG +  12, Y_ORG +   0, 611,  89,   4,   4,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (290)
			#define Y_ORG (386)

			draw_lamp (hind_lamps.lh_engine_oil_temperature_normal	, X_ORG +   0, Y_ORG +   4, 599,  75,   6,  13,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_temperature_normal	, X_ORG +  11, Y_ORG +   1, 610,  72,   5,  12,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (288)
			#define Y_ORG (377)

			draw_lamp (hind_lamps.lh_engine_oil_temperature_high		, X_ORG +   0, Y_ORG +   3, 596, 101,   8,  23,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_temperature_high		, X_ORG +  10, Y_ORG +   0, 606,  98,   8,  22,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			#define X_ORG (5)
			#define Y_ORG (399)

			draw_lamp (hind_lamps.lh_engine_oil_pressure_normal		, X_ORG +   0, Y_ORG +   9, 618,  62,   9,  14,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_pressure_normal		, X_ORG +  12, Y_ORG +   2, 630,  55,   8,  13,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (6)
			#define Y_ORG (410)

			draw_lamp (hind_lamps.lh_engine_oil_pressure_low			, X_ORG +   4, Y_ORG +   7, 622, 107,   3,   4,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_pressure_low			, X_ORG +  16, Y_ORG +   0, 634, 100,   3,   3,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (20)
			#define Y_ORG (434)

			draw_lamp (hind_lamps.lh_engine_oil_temperature_normal	, X_ORG +   1, Y_ORG +   9, 619,  86,   8,  13,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_temperature_normal	, X_ORG +  13, Y_ORG +   1, 631,  78,   7,  14,  43);	// (83% alpha)

			#undef X_ORG
			#undef Y_ORG

			#define X_ORG (16)
			#define Y_ORG (425)

			draw_lamp (hind_lamps.lh_engine_oil_temperature_high		, X_ORG +   0, Y_ORG +   7, 615, 120,  14,  25,  46);	// (82% alpha)
			draw_lamp (hind_lamps.rh_engine_oil_temperature_high		, X_ORG +  11, Y_ORG +   0, 626, 113,  13,  23,  43);	// (83% alpha)

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


void draw_overlaid_hind_threat_warning_display (int x_org, int y_org)
{
	unsigned char
		*sprite_data,
		*mask_data;

	if (application_video_colourdepth != 16)
	{
		return;
	}

	////////////////////////////////////////
	//
	// select cockpit graphics wrt time of day - required here for hi-res virtual cockpits
	//

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		case DAY_SEGMENT_TYPE_DAWN:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DAY:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL1_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DUSK:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_NIGHT:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL3_BASE;

			break;
		}
	}

	#if DEMO_VERSION

	base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL1_BASE;

	#endif

	//
	////////////////////////////////////////

	if (lock_screen (active_screen))
	{
		blit_rgb_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_TWD), x_org, y_org);

		sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES);

		mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_SPRITES_MASK);

		if (test_cockpit_instruments)
		{
			////////////////////////////////////////
			//
			// test radar type lamps
			//
			////////////////////////////////////////
			{
				static float
					timer = 0.0;

				hind_lamps.threat_warning_radar_type_1 = 0;
				hind_lamps.threat_warning_radar_type_2 = 0;
				hind_lamps.threat_warning_radar_type_3 = 0;
				hind_lamps.threat_warning_radar_type_4 = 0;
				hind_lamps.threat_warning_radar_type_5 = 0;
				hind_lamps.threat_warning_radar_type_6 = 0;

				timer += get_delta_time ();

				if (timer < (ONE_SECOND * 1.0))
				{
					hind_lamps.threat_warning_radar_type_1 = 1;
				}
				else if (timer < (ONE_SECOND * 2.0))
				{
					hind_lamps.threat_warning_radar_type_2 = 1;
				}
				else if (timer < (ONE_SECOND * 3.0))
				{
					hind_lamps.threat_warning_radar_type_3 = 1;
				}
				else if (timer < (ONE_SECOND * 4.0))
				{
					hind_lamps.threat_warning_radar_type_4 = 1;
				}
				else if (timer < (ONE_SECOND * 5.0))
				{
					hind_lamps.threat_warning_radar_type_5 = 1;
				}
				else if (timer < (ONE_SECOND * 6.0))
				{
					hind_lamps.threat_warning_radar_type_6 = 1;
				}
				else if (timer < (ONE_SECOND * 7.0))
				{
					hind_lamps.threat_warning_radar_type_1 = 1;
					hind_lamps.threat_warning_radar_type_2 = 1;
					hind_lamps.threat_warning_radar_type_3 = 1;
					hind_lamps.threat_warning_radar_type_4 = 1;
					hind_lamps.threat_warning_radar_type_5 = 1;
					hind_lamps.threat_warning_radar_type_6 = 1;
				}
				else
				{
					timer = 0.0;
				}
			}
			////////////////////////////////////////
			//
			// test radar bearing lamps
			//
			////////////////////////////////////////
			{
				static float
					timer = 0.0;

				hind_lamps.threat_warning_bearing_lh_rear_close_range = 0;
				hind_lamps.threat_warning_bearing_lh_90_close_range = 0;
				hind_lamps.threat_warning_bearing_lh_67_close_range = 0;
				hind_lamps.threat_warning_bearing_lh_45_close_range = 0;
				hind_lamps.threat_warning_bearing_lh_22_close_range = 0;
				hind_lamps.threat_warning_bearing_rh_22_close_range = 0;
				hind_lamps.threat_warning_bearing_rh_45_close_range = 0;
				hind_lamps.threat_warning_bearing_rh_67_close_range = 0;
				hind_lamps.threat_warning_bearing_rh_90_close_range = 0;
				hind_lamps.threat_warning_bearing_rh_rear_close_range = 0;
				hind_lamps.threat_warning_bearing_lh_rear = 0;
				hind_lamps.threat_warning_bearing_lh_90 = 0;
				hind_lamps.threat_warning_bearing_lh_67 = 0;
				hind_lamps.threat_warning_bearing_lh_45 = 0;
				hind_lamps.threat_warning_bearing_lh_22 = 0;
				hind_lamps.threat_warning_bearing_rh_22 = 0;
				hind_lamps.threat_warning_bearing_rh_45 = 0;
				hind_lamps.threat_warning_bearing_rh_67 = 0;
				hind_lamps.threat_warning_bearing_rh_90 = 0;
				hind_lamps.threat_warning_bearing_rh_rear = 0;

				timer += get_delta_time ();

				if (timer < (ONE_SECOND * 1.0))
				{
					hind_lamps.threat_warning_bearing_lh_rear_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 2.0))
				{
					hind_lamps.threat_warning_bearing_lh_90_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 3.0))
				{
					hind_lamps.threat_warning_bearing_lh_67_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 4.0))
				{
					hind_lamps.threat_warning_bearing_lh_45_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 5.0))
				{
					hind_lamps.threat_warning_bearing_lh_22_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 6.0))
				{
					hind_lamps.threat_warning_bearing_rh_22_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 7.0))
				{
					hind_lamps.threat_warning_bearing_rh_45_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 8.0))
				{
					hind_lamps.threat_warning_bearing_rh_67_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 9.0))
				{
					hind_lamps.threat_warning_bearing_rh_90_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 10.0))
				{
					hind_lamps.threat_warning_bearing_rh_rear_close_range = 1;
				}
				else if (timer < (ONE_SECOND * 11.0))
				{
					hind_lamps.threat_warning_bearing_lh_rear = 1;
				}
				else if (timer < (ONE_SECOND * 12.0))
				{
					hind_lamps.threat_warning_bearing_lh_90 = 1;
				}
				else if (timer < (ONE_SECOND * 13.0))
				{
					hind_lamps.threat_warning_bearing_lh_67 = 1;
				}
				else if (timer < (ONE_SECOND * 14.0))
				{
					hind_lamps.threat_warning_bearing_lh_45 = 1;
				}
				else if (timer < (ONE_SECOND * 15.0))
				{
					hind_lamps.threat_warning_bearing_lh_22 = 1;
				}
				else if (timer < (ONE_SECOND * 16.0))
				{
					hind_lamps.threat_warning_bearing_rh_22 = 1;
				}
				else if (timer < (ONE_SECOND * 17.0))
				{
					hind_lamps.threat_warning_bearing_rh_45 = 1;
				}
				else if (timer < (ONE_SECOND * 18.0))
				{
					hind_lamps.threat_warning_bearing_rh_67 = 1;
				}
				else if (timer < (ONE_SECOND * 19.0))
				{
					hind_lamps.threat_warning_bearing_rh_90 = 1;
				}
				else if (timer < (ONE_SECOND * 20.0))
				{
					hind_lamps.threat_warning_bearing_rh_rear = 1;
				}
				else if (timer < (ONE_SECOND * 21.0))
				{
					hind_lamps.threat_warning_bearing_lh_rear_close_range = 1;
					hind_lamps.threat_warning_bearing_lh_90_close_range = 1;
					hind_lamps.threat_warning_bearing_lh_67_close_range = 1;
					hind_lamps.threat_warning_bearing_lh_45_close_range = 1;
					hind_lamps.threat_warning_bearing_lh_22_close_range = 1;
					hind_lamps.threat_warning_bearing_rh_22_close_range = 1;
					hind_lamps.threat_warning_bearing_rh_45_close_range = 1;
					hind_lamps.threat_warning_bearing_rh_67_close_range = 1;
					hind_lamps.threat_warning_bearing_rh_90_close_range = 1;
					hind_lamps.threat_warning_bearing_rh_rear_close_range = 1;
					hind_lamps.threat_warning_bearing_lh_rear = 1;
					hind_lamps.threat_warning_bearing_lh_90 = 1;
					hind_lamps.threat_warning_bearing_lh_67 = 1;
					hind_lamps.threat_warning_bearing_lh_45 = 1;
					hind_lamps.threat_warning_bearing_lh_22 = 1;
					hind_lamps.threat_warning_bearing_rh_22 = 1;
					hind_lamps.threat_warning_bearing_rh_45 = 1;
					hind_lamps.threat_warning_bearing_rh_67 = 1;
					hind_lamps.threat_warning_bearing_rh_90 = 1;
					hind_lamps.threat_warning_bearing_rh_rear = 1;
				}
				else
				{
					timer = 0.0;
				}
			}
			////////////////////////////////////////
			//
			// test close range lamps
			//
			////////////////////////////////////////
			{
				static float
					timer = 0.0;

				hind_lamps.threat_warning_close_range_1 = 0;
				hind_lamps.threat_warning_close_range_2 = 0;
				hind_lamps.threat_warning_close_range_3 = 0;
				hind_lamps.threat_warning_close_range_4 = 0;
				hind_lamps.threat_warning_close_range_5 = 0;
				hind_lamps.threat_warning_close_range_6 = 0;
				hind_lamps.threat_warning_close_range_7 = 0;
				hind_lamps.threat_warning_close_range_8 = 0;
				hind_lamps.threat_warning_close_range_9 = 0;
				hind_lamps.threat_warning_close_range_10 = 0;
				hind_lamps.threat_warning_close_range_11 = 0;
				hind_lamps.threat_warning_close_range_12 = 0;
				hind_lamps.threat_warning_close_range_13 = 0;
				hind_lamps.threat_warning_close_range_14 = 0;
				hind_lamps.threat_warning_close_range_15 = 0;

				timer += get_delta_time ();

				if (timer < (ONE_SECOND * 1.0))
				{
					hind_lamps.threat_warning_close_range_1 = 1;
				}
				else if (timer < (ONE_SECOND * 2.0))
				{
					hind_lamps.threat_warning_close_range_2 = 1;
				}
				else if (timer < (ONE_SECOND * 3.0))
				{
					hind_lamps.threat_warning_close_range_3 = 1;
				}
				else if (timer < (ONE_SECOND * 4.0))
				{
					hind_lamps.threat_warning_close_range_4 = 1;
				}
				else if (timer < (ONE_SECOND * 5.0))
				{
					hind_lamps.threat_warning_close_range_5 = 1;
				}
				else if (timer < (ONE_SECOND * 6.0))
				{
					hind_lamps.threat_warning_close_range_6 = 1;
				}
				else if (timer < (ONE_SECOND * 7.0))
				{
					hind_lamps.threat_warning_close_range_7 = 1;
				}
				else if (timer < (ONE_SECOND * 8.0))
				{
					hind_lamps.threat_warning_close_range_8 = 1;
				}
				else if (timer < (ONE_SECOND * 9.0))
				{
					hind_lamps.threat_warning_close_range_9 = 1;
				}
				else if (timer < (ONE_SECOND * 10.0))
				{
					hind_lamps.threat_warning_close_range_10 = 1;
				}
				else if (timer < (ONE_SECOND * 11.0))
				{
					hind_lamps.threat_warning_close_range_11 = 1;
				}
				else if (timer < (ONE_SECOND * 12.0))
				{
					hind_lamps.threat_warning_close_range_12 = 1;
				}
				else if (timer < (ONE_SECOND * 13.0))
				{
					hind_lamps.threat_warning_close_range_13 = 1;
				}
				else if (timer < (ONE_SECOND * 14.0))
				{
					hind_lamps.threat_warning_close_range_14 = 1;
				}
				else if (timer < (ONE_SECOND * 15.0))
				{
					hind_lamps.threat_warning_close_range_15 = 1;
				}
				else if (timer < (ONE_SECOND * 16.0))
				{
					hind_lamps.threat_warning_close_range_1 = 1;
					hind_lamps.threat_warning_close_range_2 = 1;
					hind_lamps.threat_warning_close_range_3 = 1;
					hind_lamps.threat_warning_close_range_4 = 1;
					hind_lamps.threat_warning_close_range_5 = 1;
					hind_lamps.threat_warning_close_range_6 = 1;
					hind_lamps.threat_warning_close_range_7 = 1;
					hind_lamps.threat_warning_close_range_8 = 1;
					hind_lamps.threat_warning_close_range_9 = 1;
					hind_lamps.threat_warning_close_range_10 = 1;
					hind_lamps.threat_warning_close_range_11 = 1;
					hind_lamps.threat_warning_close_range_12 = 1;
					hind_lamps.threat_warning_close_range_13 = 1;
					hind_lamps.threat_warning_close_range_14 = 1;
					hind_lamps.threat_warning_close_range_15 = 1;
				}
				else
				{
					timer = 0.0;
				}
			}
			////////////////////////////////////////
			//
			// test radar lock lamps
			//
			////////////////////////////////////////
			{
				static float
					timer = 0.0;

				hind_lamps.threat_warning_missile_below = 0;
				hind_lamps.threat_warning_missile_above = 0;
				hind_lamps.threat_warning_missile_lh_lock = 0;
				hind_lamps.threat_warning_missile_rh_lock = 0;

				timer += get_delta_time ();

				if (timer < (ONE_SECOND * 1.0))
				{
					hind_lamps.threat_warning_missile_below = 1;
				}
				else if (timer < (ONE_SECOND * 2.0))
				{
					hind_lamps.threat_warning_missile_above = 1;
				}
				else if (timer < (ONE_SECOND * 3.0))
				{
					hind_lamps.threat_warning_missile_lh_lock = 1;
				}
				else if (timer < (ONE_SECOND * 4.0))
				{
					hind_lamps.threat_warning_missile_rh_lock = 1;
				}
				else if (timer < (ONE_SECOND * 5.0))
				{
					hind_lamps.threat_warning_missile_below = 1;
					hind_lamps.threat_warning_missile_above = 1;
					hind_lamps.threat_warning_missile_lh_lock = 1;
					hind_lamps.threat_warning_missile_rh_lock = 1;
				}
				else
				{
					timer = 0.0;
				}
			}
		}

		x_org += 2 - ix_640_480;
		y_org += 2 - iy_640_480;

		draw_lamp (hind_lamps.threat_warning_radar_type_1							, x_org +   5, y_org +  49, 274, 230,   8,   6, 229);	// (10% alpha)
		draw_lamp (hind_lamps.threat_warning_radar_type_2							, x_org +  13, y_org +  49, 282, 230,   8,   6, 227);	// (11% alpha)
		draw_lamp (hind_lamps.threat_warning_radar_type_3							, x_org +  21, y_org +  49, 290, 230,   8,   6, 224);	// (12% alpha)
		draw_lamp (hind_lamps.threat_warning_radar_type_4							, x_org +  29, y_org +  49, 298, 230,   7,   6, 222);	// (13% alpha)
		draw_lamp (hind_lamps.threat_warning_radar_type_5							, x_org +  36, y_org +  49, 305, 230,   8,   6, 219);	// (14% alpha)
		draw_lamp (hind_lamps.threat_warning_radar_type_6							, x_org +  44, y_org +  49, 313, 230,   8,   6, 217);	// (15% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_rear						, x_org +  12, y_org +  43, 281, 224,   7,   6, 214);	// (16% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_rear						, x_org +  38, y_org +  43, 307, 224,   6,   6, 212);	// (17% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_1						, x_org +  20, y_org +  40, 289, 221,   5,   3, 209);	// (18% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_2						, x_org +  15, y_org +  36, 284, 217,   5,   5, 207);	// (19% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_3						, x_org +  12, y_org +  30, 281, 211,   4,   6, 204);	// (20% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_4						, x_org +  12, y_org +  24, 281, 205,   3,   6, 201);	// (21% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_5						, x_org +  13, y_org +  19, 282, 200,   3,   5, 199);	// (22% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_6						, x_org +  16, y_org +  14, 285, 195,   4,   5, 196);	// (23% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_7						, x_org +  20, y_org +  11, 289, 192,   6,   4, 194);	// (24% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_8						, x_org +  26, y_org +  11, 295, 192,   5,   2, 191);	// (25% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_9						, x_org +  31, y_org +  11, 300, 192,   6,   4, 189);	// (26% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_10						, x_org +  37, y_org +  14, 306, 195,   4,   5, 186);	// (27% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_11						, x_org +  41, y_org +  19, 310, 200,   3,   6, 184);	// (28% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_12						, x_org +  42, y_org +  25, 311, 206,   3,   5, 181);	// (29% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_13						, x_org +  40, y_org +  30, 309, 211,   5,   6, 178);	// (30% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_14						, x_org +  37, y_org +  36, 306, 217,   5,   4, 176);	// (31% alpha)
		draw_lamp (hind_lamps.threat_warning_close_range_15						, x_org +  31, y_org +  39, 300, 220,   6,   4, 173);	// (32% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_90_close_range		, x_org +   9, y_org +  22, 278, 203,   4,   4, 171);	// (33% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_67_close_range		, x_org +  12, y_org +  15, 281, 196,   4,   4, 168);	// (34% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_45_close_range		, x_org +  16, y_org +  10, 285, 191,   4,   4, 166);	// (35% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_22_close_range		, x_org +  23, y_org +   7, 292, 188,   4,   4, 163);	// (36% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_22_close_range		, x_org +  30, y_org +   7, 299, 188,   4,   4, 161);	// (37% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_45_close_range		, x_org +  36, y_org +  10, 305, 191,   4,   4, 158);	// (38% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_67_close_range		, x_org +  41, y_org +  15, 310, 196,   4,   4, 156);	// (39% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_90_close_range		, x_org +  44, y_org +  22, 313, 203,   4,   4, 153);	// (40% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_90						, x_org +   3, y_org +  19, 272, 200,   6,   7, 150);	// (41% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_67						, x_org +   6, y_org +  11, 275, 192,   7,   7, 148);	// (42% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_45						, x_org +  12, y_org +   5, 281, 186,   7,   6, 145);	// (43% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_22						, x_org +  21, y_org +   2, 290, 183,   6,   6, 143);	// (44% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_22						, x_org +  30, y_org +   2, 299, 183,   6,   6, 140);	// (45% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_45						, x_org +  38, y_org +   5, 307, 186,   6,   6, 138);	// (46% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_67						, x_org +  44, y_org +  11, 313, 192,   7,   7, 135);	// (47% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_90						, x_org +  48, y_org +  20, 317, 201,   6,   6, 133);	// (48% alpha)
		draw_lamp (hind_lamps.threat_warning_missile_below						, x_org +  23, y_org +  25, 292, 206,  11,   5, 130);	// (49% alpha)
		draw_lamp (hind_lamps.threat_warning_missile_above						, x_org +  23, y_org +  21, 292, 202,  11,   4, 127);	// (50% alpha)
		draw_lamp (hind_lamps.threat_warning_missile_lh_lock		 				, x_org +  17, y_org +  16, 286, 197,  11,  23, 125);	// (51% alpha)
		draw_lamp (hind_lamps.threat_warning_missile_rh_lock						, x_org +  29, y_org +  16, 298, 197,  11,  23, 122);	// (52% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_lh_rear_close_range		, x_org +  16, y_org +  41, 285, 222,   4,   4, 120);	// (53% alpha)
		draw_lamp (hind_lamps.threat_warning_bearing_rh_rear_close_range		, x_org +  36, y_org +  41, 305, 222,   5,   4, 117);	// (54% alpha)

		unlock_screen (active_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
