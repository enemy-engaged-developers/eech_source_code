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

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////

#define SAT_WINDOW_X_MIN	(-1.0)
#define SAT_WINDOW_Y_MIN	(-1.0)
#define SAT_WINDOW_X_MAX	(0.999)
#define SAT_WINDOW_Y_MAX	(0.999)

#define SAT_VIEWPORT_SIZE	(512)

static env_2d
	*sat_env = nullptr;

static float
	sat_viewport_x_org,
	sat_viewport_y_org,
	sat_viewport_x_min,
	sat_viewport_y_min,
	sat_viewport_x_max,
	sat_viewport_y_max;

//
// SAT screen co-ords
//

static float
	sat_screen_x_min,
	sat_screen_y_min,
	sat_screen_x_max,
	sat_screen_y_max,
	sat_screen_x_scale,
	sat_screen_y_scale;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SAT_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD2)

static screen
	*sat_texture_screen = nullptr;

static rgb_colour
	clear_hud_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// heading scale
//
////////////////////////////////////////

//
// adjust 2D environment for heading scale clipping
//

#define HDG_WIDTH_RATIO			(0.6)

#define HDG_WINDOW_X_MIN		(SAT_WINDOW_X_MIN * HDG_WIDTH_RATIO)
#define HDG_WINDOW_Y_MIN		(SAT_WINDOW_Y_MIN)
#define HDG_WINDOW_X_MAX		(SAT_WINDOW_X_MAX * HDG_WIDTH_RATIO)
#define HDG_WINDOW_Y_MAX		(SAT_WINDOW_Y_MAX)

#define HDG_WINDOW_X_ORG		(0.0)
#define HDG_WINDOW_Y_ORG		(0.93)

//
// draw heading tape ticks +/-90 degs of centre (plus an extra bit to keep three cardinal points visible (N,S,E,W))
//

#define HDG_TICK_X_SPACING			(HDG_WIDTH_RATIO / 9.5)

#define HDG_TICK_10_DEG_TOP		(HDG_WINDOW_Y_ORG - 0.015)
#define HDG_TICK_10_DEG_BOTTOM	(HDG_TICK_10_DEG_TOP - 0.045)

#define HDG_TICK_30_DEG_TOP		(HDG_WINDOW_Y_ORG)
#define HDG_TICK_30_DEG_BOTTOM	(HDG_TICK_30_DEG_TOP - 0.075)

#define HDG_TICK_DATUM_TOP			(HDG_TICK_30_DEG_BOTTOM - 0.010)
#define HDG_TICK_DATUM_BOTTOM		(HDG_TICK_DATUM_TOP - 0.045)

//
// character position adjust
//

#define HDG_CHAR_ADJUST_SINGLE	(-2.0)
#define HDG_CHAR_ADJUST_DOUBLE	(-5.0)
#define HDG_CHAR_Y_ADJUST			(-8.0)

//
// command heading carat
//

#if 0
#define HDG_CARAT_FSD	(HDG_WIDTH_RATIO - 0.05)

static char command_heading_carat[] =
{
	11,
	6,
	-5,
	0,
	0,0,0,0,0,1,0,0,0,0,0,
	0,0,0,0,1,1,1,0,0,0,0,
	0,0,0,1,1,0,1,1,0,0,0,
	0,0,1,1,0,0,0,1,1,0,0,
	0,1,1,0,0,0,0,0,1,1,0,
	1,1,0,0,0,0,0,0,0,1,1,
};
#endif

//
// radar sweep indicator
//

#if 0
#define RADAR_SWEEP_INDICATOR_FSD	(HDG_WIDTH_RATIO - 0.04)

static char radar_sweep_indicator[] =
{
	11,
	7,
	-5,
	0,
	0,0,1,1,0,0,0,1,1,0,0,
	0,1,1,1,0,0,0,1,1,1,0,
	1,1,1,1,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,1,1,1,1,
	0,1,1,1,0,0,0,1,1,1,0,
	0,0,1,1,0,0,0,1,1,0,0,
};
#endif

//
// bob-up command heading carat
//

#if 0
#define BOB_UP_HDG_CARAT_FSD	(HDG_WIDTH_RATIO - 0.05)

static char bob_up_command_heading_carat[] =
{
	7,
	9,
	-3,
	0,
	0,0,0,1,0,0,0,
	0,0,1,1,1,0,0,
	0,1,1,1,1,1,0,
	1,1,1,1,1,1,1,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
	0,0,1,1,1,0,0,
};
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static void clip_2d_point_to_sat_extent (float *x, float *y)
{
	ASSERT (x);

	ASSERT (y);

	//
	// clipping assumes that the SAT origin is at (0.0, 0.0)
	//

	if (*x > SAT_WINDOW_X_MAX)
	{
		*y = (*y * SAT_WINDOW_X_MAX) / *x;

		*x = SAT_WINDOW_X_MAX;
	}
	else if (*x < SAT_WINDOW_X_MIN)
	{
		*y = (*y * SAT_WINDOW_X_MIN) / *x;

		*x = SAT_WINDOW_X_MIN;
	}

	if (*y > SAT_WINDOW_Y_MAX)
	{
		*x = (*x * SAT_WINDOW_Y_MAX) / *y;

		*y = SAT_WINDOW_Y_MAX;
	}
	else if (*y < SAT_WINDOW_Y_MIN)
	{
		*x = (*x * SAT_WINDOW_Y_MIN) / *y;

		*y = SAT_WINDOW_Y_MIN;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static void transform_sat_screen_co_ords_to_sat_texture_co_ords (float *i, float *j)
{
	ASSERT (i);
	ASSERT (j);

	*i -= sat_screen_x_min;
	*j -= sat_screen_y_min;

	*i *= sat_screen_x_scale;
	*j *= sat_screen_y_scale;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_layout_grid (void)
{
	float
		x,
		y;

	for (x = SAT_WINDOW_X_MIN; x <= SAT_WINDOW_X_MAX; x += 0.1)
	{
		draw_2d_line (x, SAT_WINDOW_Y_MIN, x, SAT_WINDOW_Y_MAX, sys_col_red);
	}

	for (y = SAT_WINDOW_Y_MIN; y <= SAT_WINDOW_Y_MAX; y += 0.1)
	{
		draw_2d_line (SAT_WINDOW_X_MIN, y, SAT_WINDOW_X_MAX, y, sys_col_red);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sat_centre_datum (void)
{
	draw_2d_line (-3.10, +0.00, -0.05, +0.00, hud_colour);
	draw_2d_line (+3.10, +0.00, +0.05, +0.00, hud_colour);
	draw_2d_line (+0.00, -3.10, +0.00, -0.05, hud_colour);
	draw_2d_line (+0.00, +3.10, +0.00, +0.05, hud_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_bank_scale (void)
{
	float
		roll;

	//
	// adjust 2D environment for bank scale clipping
	//

	set_2d_window (sat_env, BANK_SCALE_WINDOW_X_MIN, BANK_SCALE_WINDOW_Y_MIN, BANK_SCALE_WINDOW_X_MAX, BANK_SCALE_WINDOW_Y_MAX);

	bank_scale_viewport_x_min = (sat_viewport_x_org - (SAT_VIEWPORT_SIZE * 0.5));

	bank_scale_viewport_y_min = (sat_viewport_y_org - (SAT_VIEWPORT_SIZE * 0.5 * 0.8));

	bank_scale_viewport_x_max = (sat_viewport_x_org + (SAT_VIEWPORT_SIZE * 0.5));

	bank_scale_viewport_y_max = (sat_viewport_y_org - (SAT_VIEWPORT_SIZE * 0.5 * 0.5));

	set_2d_viewport (sat_env, bank_scale_viewport_x_min, bank_scale_viewport_y_min, bank_scale_viewport_x_max, bank_scale_viewport_y_max);

	//
	// draw bank scale
	//

	set_2d_instance_position (sat_env, 0.0, 0.0);

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	set_2d_instance_rotation (sat_env, roll);
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (sat_env, roll + rad (5.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (sat_env, roll - rad (5.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (sat_env, roll + rad (10.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (sat_env, roll - rad (10.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (sat_env, roll + rad (15.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (sat_env, roll - rad (15.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (sat_env, roll + rad (20.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (sat_env, roll - rad (20.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (sat_env, roll + rad (25.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (sat_env, roll - rad (25.0));
	draw_2d_line (0.0, BANK_SCALE_MINOR_TICK_Y1, 0.0, BANK_SCALE_MINOR_TICK_Y2, hud_colour);

	set_2d_instance_rotation (sat_env, roll + rad (30.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);
	set_2d_instance_rotation (sat_env, roll - rad (30.0));
	draw_2d_line (0.0, BANK_SCALE_MAJOR_TICK_Y1, 0.0, BANK_SCALE_MAJOR_TICK_Y2, hud_colour);

	reset_2d_instance (sat_env);

	//
	// restore 2D environment
	//

	set_2d_window (sat_env, SAT_WINDOW_X_MIN, SAT_WINDOW_Y_MIN, SAT_WINDOW_X_MAX, SAT_WINDOW_Y_MAX);

	set_2d_viewport (sat_env, sat_viewport_x_min, sat_viewport_y_min, sat_viewport_x_max, sat_viewport_y_max);
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static void display_coords (void)
{
	float
		true_airspeed;

	char
		s[20];

	true_airspeed = current_flight_dynamics->velocity_z.value;

	true_airspeed = knots (true_airspeed);

	sprintf (s, "%d", (int) true_airspeed);

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	set_2d_mono_font_position (-1.0, 0.0);

	set_mono_font_rel_position (1.0, -4.0);

	print_mono_font_string (s);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_target_symbology (void)
{
	int
		target_visible;

	entity_sub_types
		selected_weapon_type;

	object_3d_visibility
		visibility;

	float
		i,
		j,
		target_x,
		target_y,
		intercept_point_x,
		intercept_point_y,
		heading_offset,
		pitch_offset;

	entity
		*source = nullptr,
		*target = nullptr;

	vec3d
		target_position,
		intercept_point;

	source = get_gunship_entity ();

	selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	if (selected_weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		target = get_local_entity_parent (source, LIST_TYPE_TARGET);

		target_visible = FALSE;

		if (target)
		{
			//
			// draw target marker
			//

			get_local_entity_target_point (target, &target_position);

			visibility = get_position_3d_screen_coordinates (&target_position, &i, &j);

			if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
			{
				target_visible = TRUE;

				transform_sat_screen_co_ords_to_sat_texture_co_ords (&i, &j);

				get_2d_world_position (i, j, &target_x, &target_y);

				clip_2d_point_to_sat_extent (&target_x, &target_y);

				draw_target_marker (target_x, target_y);
			}
		}

		switch (selected_weapon_type)
		{
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND:
			////////////////////////////////////////
			{
				if (target_visible)
				{
					if (weapon_lock_type == WEAPON_LOCK_VALID)
					{
						draw_solid_gun_target_marker (target_x, target_y);
					}
					else
					{
						draw_dashed_gun_target_marker (target_x, target_y);
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
			case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
			////////////////////////////////////////
			{
				if (target_visible)
				{
					if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
					{
						get_target_intercept_point (source, target, selected_weapon_type, &intercept_point);

						visibility = get_position_3d_screen_coordinates (&intercept_point, &i, &j);

						if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
						{
							transform_sat_screen_co_ords_to_sat_texture_co_ords (&i, &j);

							get_2d_world_position (i, j, &intercept_point_x, &intercept_point_y);

							clip_2d_point_to_sat_extent (&intercept_point_x, &intercept_point_y);

							draw_airborne_target_computed_intercept_point (intercept_point_x, intercept_point_y);
						}
					}

					if (get_local_entity_selected_weapon_to_target_offsets (source, &heading_offset, &pitch_offset))
					{
						heading_offset = bound (heading_offset, rad (-10.0), rad (10.0));

						heading_offset *= 0.7 / 0.17453293;	// rad (10.0)

						pitch_offset = bound (pitch_offset, rad (-5.0), rad (5.0));

						pitch_offset *= 0.35 / 0.08726646;	// rad (5.0)

						if (weapon_lock_type == WEAPON_LOCK_VALID)
						{
							draw_solid_i_beam (heading_offset, pitch_offset);
						}
						else
						{
							draw_dashed_i_beam (heading_offset, pitch_offset);
						}
					}
					else
					{
						//
						// this should never happen
						//

						debug_colour_log (DEBUG_COLOUR_RED, "WARNING! get_local_entity_selected_weapon_to_target_offsets failed");
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
			case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
			case ENTITY_SUB_TYPE_WEAPON_AGM114R_HELLFIRE_II:
			////////////////////////////////////////
			{
				if (!get_local_entity_int_value (source, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
				{
					if (target_visible)
					{
						if (weapon_lock_type == WEAPON_LOCK_VALID)
						{
							draw_hellfire_lobl_solid_target_marker (target_x, target_y);
						}
						else
						{
							draw_hellfire_lobl_dashed_target_marker (target_x, target_y);
						}
					}
				}
				else
				{
					if (target_visible)
					{
						if (weapon_lock_type == WEAPON_LOCK_VALID)
						{
							draw_hellfire_loal_solid_target_marker (target_x, target_y);
						}
						else
						{
							draw_hellfire_loal_dashed_target_marker (target_x, target_y);
						}
					}
					else
					{
						draw_hellfire_loal_dashed_target_marker (0.0, 0.0);
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_SUB_TYPE_WEAPON_AIM92A_STINGER:
			////////////////////////////////////////
			{
				if ((weapon_lock_type == WEAPON_LOCK_VALID) && target_visible)
				{
					draw_solid_stinger_target_marker (target_x, target_y);
				}
				else
				{
					draw_dashed_stinger_target_marker (apache_stinger_seeker_head_x_position, apache_stinger_seeker_head_y_position);
				}

				break;
			}
		}
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

void initialise_satellite_info (void)
{
#ifndef OGRE_EE
	sat_env = create_2d_environment ();

	sat_texture_screen = create_system_texture_screen (SAT_VIEWPORT_SIZE, SAT_VIEWPORT_SIZE, SAT_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	clear_hud_colour.r = 255;
	clear_hud_colour.g = 255;
	clear_hud_colour.b = 255;
	clear_hud_colour.a = 0;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_satellite_info (void)
{
#ifndef OGRE_EE
	destroy_2d_environment (sat_env);

	destroy_screen (sat_texture_screen);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_satellite_info (void)
{
#ifndef OGRE_EE
	rgb_colour
		store_hud_colour;

	const int
		alpha = 255;

#if 0
	float
		heading_offset,
		pitch_offset,
		max_offset;
#endif

	vertex
		quad[4];

	real_colour
		colour,
		specular;

	////////////////////////////////////////
	//
	// set active 3D environment now else 2D clipping will be affected
	//
	////////////////////////////////////////

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

	set_3d_active_environment (main_3d_env);

	////////////////////////////////////////
	//
	// set up SAT 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (sat_env);

	set_2d_window (sat_env, SAT_WINDOW_X_MIN, SAT_WINDOW_Y_MIN, SAT_WINDOW_X_MAX, SAT_WINDOW_Y_MAX);

	sat_viewport_x_org = SAT_VIEWPORT_SIZE * 0.5;

	sat_viewport_y_org = SAT_VIEWPORT_SIZE * 0.5;

	sat_viewport_x_min = 0.0;

	sat_viewport_y_min = 0.0;

	sat_viewport_x_max = SAT_VIEWPORT_SIZE;

	sat_viewport_y_max = SAT_VIEWPORT_SIZE;

	set_2d_viewport (sat_env, sat_viewport_x_min, sat_viewport_y_min, sat_viewport_x_max, sat_viewport_y_max);

	//
	// get screen co-ords (scaled to keep SAT size constant)
	//

	if (get_global_unscaled_displays ())
	{
		sat_screen_x_min = full_screen_x_mid - 256.0;
		sat_screen_y_min = full_screen_y_mid - 256.0;

		sat_screen_x_max = full_screen_x_mid + 255.999;
		sat_screen_y_max = full_screen_y_mid + 255.999;

		sat_screen_x_scale = 1.0;
		sat_screen_y_scale = 1.0;
	}
	else
	{
		sat_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 1.0)) * full_screen_width);
		sat_screen_y_min = full_screen_y_mid - ((256.0 / (480.0 * 1.0)) * full_screen_height);

		sat_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 1.0)) * full_screen_width);
		sat_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 1.0)) * full_screen_height);

		sat_screen_x_scale = 640.0 / full_screen_width;
		sat_screen_y_scale = 480.0 / full_screen_height;
	}

	////////////////////////////////////////
	//
	// draw SAT on texture
	//
	////////////////////////////////////////

	set_active_screen (sat_texture_screen);

	if (lock_screen (sat_texture_screen))
	{
	 	store_hud_colour = hud_colour;

		set_rgb_colour (hud_colour, 255, 255, 255, 255);

		set_mono_font_colour (hud_colour);

		set_block (0, 0, SAT_VIEWPORT_SIZE - 1, SAT_VIEWPORT_SIZE - 1, clear_hud_colour);

		draw_layout_grid ();

		draw_sat_centre_datum ();

		hud_colour = store_hud_colour;

		unlock_screen (sat_texture_screen);
	}

	set_active_screen (video_screen);

	////////////////////////////////////////
	//
	// render SAT to screen
	//
	////////////////////////////////////////

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_culling (FALSE);

		set_d3d_texture_wrapping (0, FALSE);

		if ((application_video_width == 640) || (get_global_unscaled_displays ()))
		{
			set_d3d_texture_mag_filtering (FALSE);
			set_d3d_texture_min_filtering (FALSE);
			set_d3d_texture_mip_filtering (FALSE);
		}
		else
		{
			set_d3d_texture_mag_filtering (TRUE);
			set_d3d_texture_min_filtering (TRUE);
			set_d3d_texture_mip_filtering (FALSE);
		}

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (SAT_TEXTURE_INDEX));

		////////////////////////////////////////
		//

		colour.red	  			= hud_colour_table[get_global_hud_colour ()].r;
		colour.green 			= hud_colour_table[get_global_hud_colour ()].g;
		colour.blue	 			= hud_colour_table[get_global_hud_colour ()].b;
		colour.alpha			= alpha;

		specular.red  			= 0;
		specular.green			= 0;
		specular.blue			= 0;
		specular.alpha			= 255;

		quad[0].i				= sat_screen_x_min;
		quad[0].j	  			= sat_screen_y_min;
		quad[0].z	  			= 0.5;
		quad[0].q	  			= 0.5;
		quad[0].u	  			= 0.0;
		quad[0].v	  			= 0.0;

		quad[1].i  				= sat_screen_x_max;
		quad[1].j  				= sat_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 1.0;
		quad[1].v  				= 0.0;

		quad[2].i				= sat_screen_x_max;
		quad[2].j  				= sat_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 1.0;
		quad[2].v  				= 1.0;

		quad[3].i				= sat_screen_x_min;
		quad[3].j				= sat_screen_y_max;
		quad[3].z				= 0.5;
		quad[3].q				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 1.0;

		quad[0].next_vertex 	= &quad[1];
		quad[1].next_vertex 	= &quad[2];
		quad[2].next_vertex 	= &quad[3];
		quad[3].next_vertex	= NULL;

		//
		////////////////////////////////////////

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		set_d3d_culling (TRUE);

		end_3d_scene ();
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
