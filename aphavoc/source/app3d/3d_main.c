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

void set_full_screen_viewport (void)
{
	set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_main_3d_params
(
	display_3d_tints tint,
	display_3d_light_levels light_level,
	display_3d_noise_levels noise_level,
	float x,
	float y,
	float width,
	float height,
	float width_view_angle,
	float height_view_angle
)
{
	set_3d_viewport (main_3d_env, x, y, x + width - 0.001, y + height - 0.001);

	set_3d_origin (main_3d_env, x + (width * 0.5), y + (height * 0.5));

	set_3d_viewcone (main_3d_env, width, height, width_view_angle, height_view_angle);

	set_application_display_3d_mode (tint, light_level, noise_level);

	application_3d_rain_active = TRUE;

	//
	// keep single light environment in sync (for Apache & Havoc virtual cockpits)
	//

	set_3d_viewport (main_3d_single_light_env, x, y, x + width - 0.001, y + height - 0.001);

	set_3d_origin (main_3d_single_light_env, x + (width * 0.5), y + (height * 0.5));

	set_3d_viewcone (main_3d_single_light_env, width, height, width_view_angle, height_view_angle);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_main_3d_full_screen_params (display_3d_tints tint, display_3d_light_levels light_level, display_3d_noise_levels noise_level)
{
	set_main_3d_params
	(
		tint,
		light_level,
		noise_level,
		full_screen_x_min,
		full_screen_y_min,
		full_screen_width,
		full_screen_height,
		full_screen_width_view_angle,
		full_screen_height_view_angle
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_pilots_full_screen_params (int night_vision_system_active)
{
	display_3d_tints
		tint;
	display_3d_light_levels
		level;

	if (night_vision_system_active)
	{
		tint = gunship_sides[get_global_gunship_type ()] != ENTITY_SIDE_RED_FORCE ? DISPLAY_3D_TINT_GREEN : DISPLAY_3D_TINT_BLUE;
//VJ 050818 PNVS brighness levels
// switched 0 and 2 so high level is default by GCsDriver 08-12-2007
		switch (global_PNVS_level)
		{
			default:
			case 0 :
				{
					level = DISPLAY_3D_LIGHT_LEVEL_HIGH;
					break;
				}
			case 1:
				{
					level = DISPLAY_3D_LIGHT_LEVEL_MEDIUM;
					break;
				}
			case 2:
				{
					level = DISPLAY_3D_LIGHT_LEVEL_LOW;
					break;
				}
		}
	}
	else
	{
		tint = DISPLAY_3D_TINT_CLEAR;
		level = DISPLAY_3D_LIGHT_LEVEL_HIGH;
	}
	set_main_3d_full_screen_params (tint, level, DISPLAY_3D_NOISE_LEVEL_NONE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_main_3d_inset_target_screen_params (void)
{
	set_main_3d_params
	(
		DISPLAY_3D_TINT_CLEAR,
		DISPLAY_3D_LIGHT_LEVEL_HIGH,
		DISPLAY_3D_NOISE_LEVEL_NONE,
		(full_screen_x_max - full_screen_x_min) * (1.0 - 0.25 - 0.025),
		(full_screen_y_max - full_screen_y_min) * 0.025,
		(full_screen_x_max - full_screen_x_min) * 0.25,
		(full_screen_y_max - full_screen_y_min) * 0.25,
		full_screen_width_view_angle,
		full_screen_height_view_angle
	);

	application_3d_rain_active = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_crew_view_full_screen_params (void)
{
	set_main_3d_params
	(
		DISPLAY_3D_TINT_CLEAR,
		DISPLAY_3D_LIGHT_LEVEL_HIGH,
		DISPLAY_3D_NOISE_LEVEL_NONE,
		full_screen_x_min,
		full_screen_y_min,
		full_screen_width,
		full_screen_height,
		rad (59.99),
		rad (46.82)
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_main_3d_scene (viewpoint *vp)
{
	viewpoint
		tmp;

	ASSERT (vp);

	if (vp != &main_vp)
	{
		tmp = main_vp;

		main_vp = *vp;
	}

	draw_application_3d_scene ();

	if (vp != &main_vp)
	{
		main_vp = tmp;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
