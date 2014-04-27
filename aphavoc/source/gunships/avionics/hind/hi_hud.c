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

static void initialise_hms_gun_pipper (void);
static void display_target_information (void);
static void display_weapon_information (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////

#define HUD_WINDOW_X_MIN  				(-1.0)
#define HUD_WINDOW_Y_MIN				(-1.0)
#define HUD_WINDOW_X_MAX  				(0.999)
#define HUD_WINDOW_Y_MAX 				(0.999)

#define HUD_VIEWPORT_LARGE_SIZE		(256)
#define HUD_VIEWPORT_SMALL_SIZE		(256)

#define HUD_VIEWPORT_TEXTURE_X_ORG	(HUD_VIEWPORT_SMALL_SIZE / 2)
#define HUD_VIEWPORT_TEXTURE_Y_ORG	(HUD_VIEWPORT_SMALL_SIZE / 2)

#define SIN60 0.8660254

static env_2d
	*hud_env;

static float
	hud_viewport_size,
	hud_viewport_x_org,
	hud_viewport_y_org,
	hud_viewport_x_min,
	hud_viewport_y_min,
	hud_viewport_x_max,
	hud_viewport_y_max;

static int
	backup_sight_active,
	draw_large_hud;

static float
	hud_width,
	hud_height,
	hud_distance,
	hud_position_z,
	hud_position_y,
	hud_screen_x_min,
	hud_screen_y_min,
	hud_screen_x_max,
	hud_screen_y_max,
	hud_screen_x_scale,
	hud_screen_y_scale,
	x_offset,
	y_offset;

static object_3d*
	hud_display_model;

static unsigned
	num_texture_coordinates = 0;

static object_3d_short_textured_point*
	hud_texture_uv_coordinates = NULL;

rgb_colour
	backup_sight_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LARGE_HUD_TEXTURE_INDEX (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD)
#define LARGE_HMS_TEXTURE_INDEX (TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD)

static screen
	*hud_texture_screen;

static rgb_colour
	clear_hud_colour;

static char small_hud_plus[] =
{
	3,
	3,
	-1,
	-1,
	0,1,0,
	1,1,1,
	0,1,0,
};

static char big_hud_dot[] =
{
	5,
	5,
	-2,
	-2,
	0,1,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	0,1,1,1,0,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_hud_colours(void);

static void clip_2d_point_to_hud_extent (float *x, float *y)
{
	ASSERT (x);

	ASSERT (y);

	//
	// clipping assumes that the HUD origin is at (0.0, 0.0)
	//

	if (*x > HUD_WINDOW_X_MAX)
	{
		*y = (*y * HUD_WINDOW_X_MAX) / *x;

		*x = HUD_WINDOW_X_MAX;
	}
	else if (*x < HUD_WINDOW_X_MIN)
	{
		*y = (*y * HUD_WINDOW_X_MIN) / *x;

		*x = HUD_WINDOW_X_MIN;
	}

	if (*y > HUD_WINDOW_Y_MAX)
	{
		*x = (*x * HUD_WINDOW_Y_MAX) / *y;

		*y = HUD_WINDOW_Y_MAX;
	}
	else if (*y < HUD_WINDOW_Y_MIN)
	{
		*x = (*x * HUD_WINDOW_Y_MIN) / *y;

		*y = HUD_WINDOW_Y_MIN;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_layout_grid (void)
{
	float
		x,
		y;

	if (display_hud_layout_grid)
	{
		for (x = HUD_WINDOW_X_MIN; x <= HUD_WINDOW_X_MAX; x += 0.1)
		{
			draw_2d_line (x, HUD_WINDOW_Y_MIN, x, HUD_WINDOW_Y_MAX, sys_col_red);
		}

		for (y = HUD_WINDOW_Y_MIN; y <= HUD_WINDOW_Y_MAX; y += 0.1)
		{
			draw_2d_line (HUD_WINDOW_X_MIN, y, HUD_WINDOW_X_MAX, y, sys_col_red);
		}
	}
}

static void draw_backup_sight(void)
{
	const float
		nar_tick = 0.035,
		wide_tick = 0.075;

	set_2d_pixel(0.0, 0.0, backup_sight_colour);
	draw_2d_circle(0.0, 0.0, 0.15, backup_sight_colour);
	draw_2d_circle(0.0, 0.0, 0.4, backup_sight_colour);

	draw_2d_line(0.0, 0.6, 0.0, 0.1, backup_sight_colour);
	draw_2d_line(0.0, -0.1, 0.0, -1.0, backup_sight_colour);
	draw_2d_line(0.8, 0.0, 0.1, 0.0, backup_sight_colour);
	draw_2d_line(-0.8, 0.0, -0.1, 0.0, backup_sight_colour);

	// horizontal tick marks
	draw_2d_line(-wide_tick, 0.2, wide_tick, 0.2, backup_sight_colour);
	draw_2d_line(-wide_tick, -0.2, wide_tick, -0.2, backup_sight_colour);
	draw_2d_line(-wide_tick, -0.6, wide_tick, -0.6, backup_sight_colour);
	draw_2d_line(-wide_tick, -0.8, wide_tick, -0.8, backup_sight_colour);

	draw_2d_line(-nar_tick, 0.5, nar_tick, 0.5, backup_sight_colour);
	draw_2d_line(-nar_tick, 0.3, nar_tick, 0.3, backup_sight_colour);
	draw_2d_line(-nar_tick, -0.3, nar_tick, -0.3, backup_sight_colour);
	draw_2d_line(-nar_tick, -0.5, nar_tick, -0.5, backup_sight_colour);
	draw_2d_line(-nar_tick, -0.7, nar_tick, -0.7, backup_sight_colour);
	draw_2d_line(-nar_tick, -0.9, nar_tick, -0.9, backup_sight_colour);

	// vertical tick marks
	draw_2d_line(-0.6, wide_tick, -0.6, -wide_tick, backup_sight_colour);
	draw_2d_line(-0.2, wide_tick, -0.2, -wide_tick, backup_sight_colour);
	draw_2d_line( 0.2, wide_tick,  0.2, -wide_tick, backup_sight_colour);
	draw_2d_line( 0.6, wide_tick,  0.6, -wide_tick, backup_sight_colour);

	draw_2d_line(-0.7, nar_tick, -0.7, -nar_tick, backup_sight_colour);
	draw_2d_line(-0.5, nar_tick, -0.5, -nar_tick, backup_sight_colour);
	draw_2d_line(-0.3, nar_tick, -0.3, -nar_tick, backup_sight_colour);

	draw_2d_line( 0.7, nar_tick,  0.7, -nar_tick, backup_sight_colour);
	draw_2d_line( 0.5, nar_tick,  0.5, -nar_tick, backup_sight_colour);
	draw_2d_line( 0.3, nar_tick,  0.3, -nar_tick, backup_sight_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_mode_hud (int draw_on_virtual_cockpit_texture)
{
	display_target_information();
	display_weapon_information();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_hind_hud (void)
{
	hud_env = create_2d_environment ();

	hud_texture_screen = create_system_texture_screen (HUD_VIEWPORT_SMALL_SIZE, HUD_VIEWPORT_SMALL_SIZE, TEXTURE_INDEX_HVCKPT_HUD_DISPLAY, TEXTURE_TYPE_SINGLEALPHA);

	set_2d_view_offset(hud_env, 0.0, 0.0);

	initialise_hud_colours();
	initialise_hms_gun_pipper ();
	backup_sight_active = FALSE;

	if (objects_3d_scene_database[OBJECT_3D_MI24V_HUD_DISPLAY].index)
	{
		unsigned i, mem_size;

		hud_display_model = &objects_3d_data[objects_3d_scene_database[OBJECT_3D_MI24V_HUD_DISPLAY].index];

		hud_position_y = (hud_display_model->bounding_box.ymin + hud_display_model->bounding_box.ymax) * 0.5;
		hud_position_z = (hud_display_model->bounding_box.zmin + hud_display_model->bounding_box.zmax) * 0.5;
		hud_width = (hud_display_model->bounding_box.xmax - hud_display_model->bounding_box.xmin);
		hud_height = (hud_display_model->bounding_box.ymax - hud_display_model->bounding_box.ymin);

		// make a copy of original texture coordinates
		if (!hud_texture_uv_coordinates)
		{
			num_texture_coordinates = 0;
			if (hud_display_model->surfaces[0].texture_index)
			{
				for (i=0; i < hud_display_model->surfaces[0].number_of_faces; i++)
					num_texture_coordinates += hud_display_model->faces[i].number_of_points;

				mem_size = 6 * sizeof(object_3d_short_textured_point);

				hud_texture_uv_coordinates = (object_3d_short_textured_point *) safe_malloc(mem_size);
				memcpy(hud_texture_uv_coordinates, hud_display_model->surface_texture_points, mem_size);
			}
			else
				debug_fatal("Untextured HUD display");
		}
	}
	else
		hud_display_model = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_hud (void)
{
	destroy_2d_environment (hud_env);

	destroy_screen (hud_texture_screen);

	if (hud_texture_uv_coordinates)
	{
		// copy back original coordinates
		size_t mem_size = 6 * sizeof(object_3d_short_textured_point);
		memcpy(hud_display_model->surface_texture_points, hud_texture_uv_coordinates, mem_size);

		safe_free(hud_texture_uv_coordinates);
		hud_texture_uv_coordinates = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_hud_on_cockpit (int hud_enlarge)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_hud_on_texture (void)
{
	//
	// set active 3D environment now else 2D clipping will be affected
	//

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

	set_3d_active_environment (main_3d_env);

	////////////////////////////////////////
	//
	// set up HUD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (hud_env);

	//
	// window
	//

	set_2d_window (hud_env, HUD_WINDOW_X_MIN, HUD_WINDOW_Y_MIN, HUD_WINDOW_X_MAX, HUD_WINDOW_Y_MAX);

	if (hud_display_model)
	{
		// move HUD coordinate system with head movements to simulate the collimation effect (focus on infinity)
		float head_offset_x = 0.0, head_offset_y = 0.0, head_offset_z = 0.0;

		if (get_view_mode() == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD)
		{
			if (custom_3d_models.arneh_mi24v_cockpit)
				get_hind_3d_cockpit_hud_view_position(&head_offset_x, &head_offset_y, &head_offset_z);
		}
		else
		{
			head_offset_x = -getViewpointOffsetX(head_offset_x);
			head_offset_y = -getViewpointOffsetY(head_offset_y);
			head_offset_z = -getViewpointOffsetY(head_offset_z);

			head_offset_x += wide_cockpit_position[WIDEVIEW_HIND_PILOT].c.x;
			head_offset_y += wide_cockpit_position[WIDEVIEW_HIND_PILOT].c.y;
			head_offset_z += wide_cockpit_position[WIDEVIEW_HIND_PILOT].c.z;
		}

		{
			// move texture UV coordinates to move and scale the texture
			unsigned i;
			float scale;
			
			if (d3d_using_hardware_tnl) // UV handling doesn't work in this case
				scale = 1;
			else
			{
				hud_distance = hud_position_z - head_offset_z;
				scale = hud_position_z / hud_distance;

				for (i=0; i<num_texture_coordinates; i++)
				{
					float
						u = hud_texture_uv_coordinates[i].u,
						v = hud_texture_uv_coordinates[i].v;

					// scale hud to keep same absolute size no matter distance to hud
					u -= 0.5;
					v -= 0.5;

					u *= scale;
					v *= scale;

					u += 0.5;
					v += 0.5;

					hud_display_model->surface_texture_points[i].u = u;
					hud_display_model->surface_texture_points[i].v = v;
				}
			}
			
			x_offset = head_offset_x / hud_width * scale * 2.22;
			y_offset = (head_offset_y - hud_position_y) / hud_height * scale * 2.22;
			set_2d_view_offset(hud_env, x_offset, y_offset);
		}
	}

	//
	// viewport
	//

	draw_large_hud = FALSE;

	hud_viewport_size = HUD_VIEWPORT_SMALL_SIZE;
	hud_viewport_x_org = HUD_VIEWPORT_TEXTURE_X_ORG;
	hud_viewport_y_org = HUD_VIEWPORT_TEXTURE_Y_ORG;

	hud_viewport_x_min = hud_viewport_x_org - (hud_viewport_size * 0.5);
	hud_viewport_y_min = hud_viewport_y_org - (hud_viewport_size * 0.5);
	hud_viewport_x_max = hud_viewport_x_org + (hud_viewport_size * 0.5) - 0.001;
	hud_viewport_y_max = hud_viewport_y_org + (hud_viewport_size * 0.5) - 0.001;

	set_2d_viewport (hud_env, hud_viewport_x_min, hud_viewport_y_min, hud_viewport_x_max, hud_viewport_y_max);

	//
	// get screen co-ords (vitural cockpit texture - scaling only works near screen centre)
	//

	hud_screen_x_min = full_screen_x_mid - ((HUD_VIEWPORT_SMALL_SIZE / (640.0 * 2.0)) * full_screen_width);
	hud_screen_y_min = full_screen_y_mid - ((HUD_VIEWPORT_SMALL_SIZE / (480.0 * 2.0)) * full_screen_height);

	hud_screen_x_max = full_screen_x_mid + ((HUD_VIEWPORT_SMALL_SIZE / (640.0 * 2.0)) * full_screen_width) - 0.001;
	hud_screen_y_max = full_screen_y_mid + ((HUD_VIEWPORT_SMALL_SIZE / (480.0 * 2.0)) * full_screen_height) - 0.001;

	hud_screen_x_scale = 640.0 / full_screen_width;
	hud_screen_y_scale = 480.0 / full_screen_height;

	////////////////////////////////////////
	//
	// draw HUD
	//
	////////////////////////////////////////

	set_active_screen (hud_texture_screen);

	if (lock_screen (hud_texture_screen))
	{
		rgb_colour
			clear_hud_colour;

		if (backup_sight_active)
		{
			set_rgb_colour (clear_hud_colour, backup_sight_colour.r, backup_sight_colour.g, backup_sight_colour.b, 0);
		}
		else
		{
			set_rgb_colour (clear_hud_colour, hud_colour.r, hud_colour.g, hud_colour.b, 0);
		}

		set_block (0, 0, HUD_VIEWPORT_SMALL_SIZE - 1, HUD_VIEWPORT_SMALL_SIZE - 1, clear_hud_colour);


		if (electrical_system_active())
			if (backup_sight_active)
				draw_backup_sight();
			else if (!hind_damage.head_up_display)
			{
				set_mono_font_colour (hud_colour);

				draw_layout_grid ();

				if (hud_mode == HUD_MODE_WEAPON)
					draw_weapon_mode_hud (TRUE);
			}

		// last pixel must be transparent because it's repeated when texture doesn't fill entire polygon
		draw_line(0, 0, 0, HUD_VIEWPORT_SMALL_SIZE - 1, clear_hud_colour);
		draw_line(0, 0, HUD_VIEWPORT_SMALL_SIZE - 1, 0, clear_hud_colour);
		draw_line(0, HUD_VIEWPORT_SMALL_SIZE - 1, HUD_VIEWPORT_SMALL_SIZE - 1, HUD_VIEWPORT_SMALL_SIZE - 1, clear_hud_colour);
		draw_line(HUD_VIEWPORT_SMALL_SIZE - 1, 0, HUD_VIEWPORT_SMALL_SIZE - 1, HUD_VIEWPORT_SMALL_SIZE - 1, clear_hud_colour);

		flush_screen_texture_graphics (hud_texture_screen);

		unlock_screen (hud_texture_screen);
	}

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_external_hind_hud (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define GUN_PIPPER_MAX_RANGE                4000.0
#define GUN_PIPPER_SIZE						(0.3)
#define GUN_PIPPER_SIZE2					(0.32)
#define NUM_GUN_PIPPER_POINTS				(70)
#define GUN_PIPPER_ANGULAR_STEP_SIZE	((8.0 / 12.0) * PI / NUM_GUN_PIPPER_POINTS)

static float
	gun_pipper_points[NUM_GUN_PIPPER_POINTS][2],
	gun_pipper_points2[NUM_GUN_PIPPER_POINTS][2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_hms_gun_pipper (void)
{
	int
		i;

	float
		theta,
		sin_theta,
		cos_theta;

	theta = rad(0);

	for (i = 0; i < NUM_GUN_PIPPER_POINTS; i++)
	{
		sin_theta = sin (theta);
		cos_theta = cos (theta);

		gun_pipper_points[i][0] = sin_theta * GUN_PIPPER_SIZE;
		gun_pipper_points[i][1] = cos_theta * GUN_PIPPER_SIZE;
		gun_pipper_points2[i][0] = sin_theta * GUN_PIPPER_SIZE2;
		gun_pipper_points2[i][1] = cos_theta * GUN_PIPPER_SIZE2;

		theta += GUN_PIPPER_ANGULAR_STEP_SIZE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_aim_marker(float x, float y, float range, float min_range)
{
	const float
		tick_end = GUN_PIPPER_SIZE - 0.035,
		start = 0.05,
		end = 0.25;

	// draw cross
	draw_2d_half_thick_line(x, y + start, x, y + end, hud_colour);
	draw_2d_half_thick_line(x, y - start, x, y - end, hud_colour);
	draw_2d_half_thick_line(x + start, y, x + end, y, hud_colour);
	draw_2d_half_thick_line(x - start, y, x - end, y, hud_colour);

	// draw range bar
	{
		int
			i,
			min_range_i,
			end_i;

		for (i=0; i<NUM_GUN_PIPPER_POINTS; i++)
			set_2d_pixel(x + gun_pipper_points[i][0], y + gun_pipper_points[i][1], hud_colour);

		min_range_i = bound((min_range / GUN_PIPPER_MAX_RANGE) * NUM_GUN_PIPPER_POINTS, 0, NUM_GUN_PIPPER_POINTS);
		end_i = bound((range / GUN_PIPPER_MAX_RANGE) * NUM_GUN_PIPPER_POINTS, 0, NUM_GUN_PIPPER_POINTS);

		for (i=0; i<end_i; i++)
		{
			if (i < min_range_i)
				draw_2d_mono_sprite (small_hud_plus, x + gun_pipper_points2[i][0], y + gun_pipper_points2[i][1], hud_colour);
			else
				draw_2d_mono_sprite (big_hud_dot, x + gun_pipper_points2[i][0], y + gun_pipper_points2[i][1], hud_colour);
		}
	}

	// draw range tick marks
	draw_2d_line(x, y + GUN_PIPPER_SIZE, x, y + tick_end, hud_colour);
	draw_2d_line(x + GUN_PIPPER_SIZE * 0.5, y + GUN_PIPPER_SIZE * SIN60, x + tick_end * 0.5, y + tick_end * SIN60, hud_colour);
	draw_2d_line(x + GUN_PIPPER_SIZE * SIN60, y + GUN_PIPPER_SIZE * 0.5, x + tick_end * SIN60, y + tick_end * 0.5, hud_colour);
	draw_2d_line(x + GUN_PIPPER_SIZE, y, x + GUN_PIPPER_SIZE - tick_end, y, hud_colour);
	draw_2d_line(x + GUN_PIPPER_SIZE * SIN60, y - GUN_PIPPER_SIZE * 0.5, x + tick_end * SIN60, y - tick_end * 0.5, hud_colour);
}

static int angles_to_hud_coordinates(float azimuth, float elevation, float* x, float* y, int clamp_to_edge)
{
	*x = atan(azimuth) * hud_position_z / (0.5 * hud_width);
	*y = atan(elevation) * hud_position_z / (0.5 * hud_height);

	if (clamp_to_edge)
		clip_2d_point_to_hud_extent(x, y);
	else
	{
		if (*x < HUD_WINDOW_X_MIN)
			return FALSE;
		if (*x > HUD_WINDOW_X_MAX)
			return FALSE;
		if (*y < HUD_WINDOW_Y_MIN)
			return FALSE;
		if (*y > HUD_WINDOW_Y_MAX)
			return FALSE;
	}

	return TRUE;
}

static float
	hud_aim_range = 0.0;

float get_hud_aiming_range(void)
{
	return hud_aim_range;
}

static void display_weapon_information (void)
{
	entity_sub_types
		weapon_sub_type;

	float
		x,
		y,
		angle_of_drop,
		drop_hud_distance,
		roll;

	weapon_sub_type = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		//
		// weapon specific
		//

		if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S5)
			|| (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S8)
			|| (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_S13)
			|| (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
			|| (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_YAK_B_12P7MM_ROUND && target_acquisition_system != TARGET_ACQUISITION_SYSTEM_HMS))
		{
			float
				x,y;
				angle_of_drop = 0.0;
				drop_hud_distance;
				roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

			angle_of_drop = get_ballistic_weapon_drop(weapon_sub_type, &hud_aim_range);
			drop_hud_distance = atan(angle_of_drop) * hud_position_z / (0.5 * hud_height);

			y = cos(roll) * -drop_hud_distance;
			x = sin(roll) * drop_hud_distance;

			draw_aim_marker(x, y, hud_aim_range, weapon_database[weapon_sub_type].min_range);

			// draw target marker around target if having cpg assist
			if (get_global_cpg_assist_type() != CPG_ASSIST_TYPE_NONE && eo_is_locked())
			{
				float az, el;

				get_eo_azimuth_and_elevation(&az, &el);
				if (angles_to_hud_coordinates(az, el, &x, &y, TRUE))
					draw_2d_circle(x, y, 0.15, hud_colour);
			}
		}
		else
		{
			entity* target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);
			vec3d* tracking_point;

			// will use point lock if no target
			tracking_point = get_eo_tracking_point();
			if (target || tracking_point)
			{
				vec3d
					target_position,
					*source_position;

				float
					elevation,
					azimuth;

				if (target)
					get_local_entity_target_point (target, &target_position);
				else
					target_position = *tracking_point;

				source_position = get_local_entity_vec3d_ptr(get_gunship_entity(), VEC3D_TYPE_POSITION);

				get_eo_azimuth_and_elevation(&azimuth, &elevation);

				hud_aim_range = get_triangulated_by_position_range(source_position, &target_position);

				if (angles_to_hud_coordinates(azimuth, elevation, &x, &y, TRUE))
					draw_aim_marker(x, y, hud_aim_range, weapon_database[weapon_sub_type].min_range);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_target_information (void)
{
	const char
		*s;
	char
		buffer[200];

	entity
		*target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	set_mono_font_type (MONO_FONT_TYPE_8X14);
	s = get_target_display_name (target, buffer, FALSE);
	if (s && strcmp(s, "NO TARGET") != 0)
	{
		float width = get_mono_font_string_width (s);
		set_2d_mono_font_position (0.0, -0.75);
		set_mono_font_rel_position (-width * 0.5, 0.0);
		print_mono_font_string (s);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_hms (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour hind_hud_colours[4];
static int current_hud_colour = 0;

static void initialise_hud_colours(void)
{
	set_rgb_colour(hind_hud_colours[0],   192, 255,128, 255);
	set_rgb_colour(hind_hud_colours[1],   128, 255, 48, 255);
	set_rgb_colour(hind_hud_colours[2],    48,  64, 16, 255);
	set_rgb_colour(hind_hud_colours[3],   255, 220, 64, 255);

	set_rgb_colour(backup_sight_colour,  255, 50, 0, 255);

	current_hud_colour = 0;
	hud_colour = hind_hud_colours[current_hud_colour];
	set_rgb_colour (clear_hud_colour, 255, 255, 255, 0);
}

rgb_colour get_hind_hud_colour(void)
{
	return hind_hud_colours[current_hud_colour];
}

rgb_colour get_next_hind_hud_colour(void)
{
	current_hud_colour++;
	if (current_hud_colour >= ARRAY_LENGTH(hind_hud_colours))
		current_hud_colour = 0;

	return hind_hud_colours[current_hud_colour];
}

rgb_colour get_prev_hind_hud_colour(void)
{
	current_hud_colour--;
	if (current_hud_colour < 0)
		current_hud_colour = ARRAY_LENGTH(hind_hud_colours) - 1;

	return hind_hud_colours[current_hud_colour];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_hind_backup_sight(void)
{
	backup_sight_active = !backup_sight_active;
}
