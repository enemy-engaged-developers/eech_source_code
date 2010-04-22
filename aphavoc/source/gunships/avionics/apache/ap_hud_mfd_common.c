/*
 * ap_hud_mfd_common.c
 *
 *  Created on: 20. apr. 2010
 *      Author: arneh
 */

#include "project.h"

#include "ap_hud_mfd_common.h"
#include "ap_hud_mfd_common_sprites.h"
#include "ap_hud.h"

static int
	c_scope_enabled;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_apache_c_scope_enabled()
{
	return c_scope_enabled;
}

void toggle_apache_c_scope()
{
	c_scope_enabled = !c_scope_enabled;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// returns TRUE if position is visible
int get_apache_texture_coordinate_for_position(vec3d* absolute_position, float* i, float* j, int is_hud)
{
	object_3d_visibility
		visibility;

	visibility = get_position_3d_screen_coordinates(absolute_position, i, j);

	if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
	{
		float x, y;

		if (is_hud)
			transform_apache_hud_screen_co_ords_to_hud_texture_co_ords(i, j);

		get_2d_world_position (*i, *j, &x, &y);

		*i = x;
		*j = y;

		return TRUE;
	}
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_c_scope_symbology(int is_hud, rgb_colour colour, rgb_colour bg_colour)
{
	unsigned ncontacts;
	radar_contact* contacts = get_radar_contacts(&ncontacts);
	float current_time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	for (contacts = get_radar_contacts(&ncontacts);
		 ncontacts;
		 ncontacts--, contacts++)
	{
		float x, y;
		vec3d position;
		int moving = fabs(contacts->velocity.x) > 1.0 || fabs(contacts->velocity.y) > 0.1 || fabs(contacts->velocity.z > 1.0);

		if (moving)
		{
			float delta_time = current_time - contacts->last_contact;
			// assume contact continues in same direction
			position.x = contacts->last_position.x + contacts->velocity.x * delta_time;
			position.y = contacts->last_position.y + contacts->velocity.y * delta_time;
			position.z = contacts->last_position.z + contacts->velocity.z * delta_time;
		}
		else
			position = contacts->last_position;

		if (get_apache_texture_coordinate_for_position(&position, &x, &y, is_hud))
		{
			y -= 0.02;

			draw_apache_radar_target_symbol(contacts->en, x, y, contacts->age < 2, moving, colour, bg_colour, bg_colour);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CUE_FLASH_INTERVAL (1.0)

void draw_apache_acquisition_source_symbology(viewpoint* vp, rgb_colour colour, float position, float cue_dot_limit)
{
	static float cue_flash_timer = CUE_FLASH_INTERVAL;

	float
		offset_heading,
		offset_pitch,
		i,
		j;

	vec3d
		absolute_position,
		head_relative_position,
		*relative_position = get_acuisition_source_relative_position();

	if (cue_flash_timer > CUE_FLASH_INTERVAL * 0.5)
	{
		multiply_transpose_matrix3x3_vec3d(&head_relative_position, vp->attitude, relative_position);
		normalise_3d_vector(&head_relative_position);
		get_heading_and_pitch_from_3d_unit_vector(&head_relative_position, &offset_heading, &offset_pitch);

		if (offset_heading < -cue_dot_limit)
			draw_2d_mono_sprite(cue_dot, -position, 0.0, colour);
		else if (offset_heading > cue_dot_limit)
			draw_2d_mono_sprite(cue_dot, position, 0.0, colour);

		if (offset_pitch < -cue_dot_limit)
			draw_2d_mono_sprite(cue_dot, 0.0, -position, colour);
		else if (offset_pitch > cue_dot_limit)
			draw_2d_mono_sprite(cue_dot, 0.0, position, colour);
	}

	absolute_position.x = vp->x + relative_position->x;
	absolute_position.y = vp->y + relative_position->y;
	absolute_position.z = vp->z + relative_position->z;

	if (get_apache_texture_coordinate_for_position(&absolute_position, &i, &j, vp != &eo_vp))
	{
		if (i > -0.7 && i < 0.7 && j > -0.7 && j < 0.7)
		{
			draw_2d_half_thick_line(i, j + 0.03, i, j + 0.06, colour);
			draw_2d_half_thick_line(i, j + 0.07, i, j + 0.10, colour);
			draw_2d_half_thick_line(i, j - 0.03, i, j - 0.06, colour);
			draw_2d_half_thick_line(i, j - 0.07, i, j - 0.10, colour);

			draw_2d_half_thick_line(i + 0.03, j, i + 0.06, j, colour);
			draw_2d_half_thick_line(i + 0.07, j, i + 0.10, j, colour);
			draw_2d_half_thick_line(i - 0.03, j, i - 0.06, j, colour);
			draw_2d_half_thick_line(i - 0.07, j, i - 0.10, j, colour);
		}
	}

	cue_flash_timer -= get_delta_time();
	if (cue_flash_timer < 0.0)
		cue_flash_timer += CUE_FLASH_INTERVAL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_apache_display_radar_altitude(void)
{
	float radar_altitude = feet (current_flight_dynamics->radar_altitude.value);

	if (radar_altitude <= 50.0)
		return (int)(radar_altitude + 0.5);
	else
		return 10 * (int)((radar_altitude + 5.0) / 10.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hellfire_lobl_dashed_target_marker (float x, float y, rgb_colour colour)
{
	draw_2d_half_thick_line (x - 0.15000, y + 0.15000, x - 0.13125, y + 0.15000, colour);
	draw_2d_half_thick_line (x - 0.09375, y + 0.15000, x - 0.05626, y + 0.15000, colour);
	draw_2d_half_thick_line (x - 0.01875, y + 0.15000, x + 0.01875, y + 0.15000, colour);
	draw_2d_half_thick_line (x + 0.05625, y + 0.15000, x + 0.09375, y + 0.15000, colour);
	draw_2d_half_thick_line (x + 0.13125, y + 0.15000, x + 0.15000, y + 0.15000, colour);

	draw_2d_half_thick_line (x - 0.15000, y - 0.15000, x - 0.13125, y - 0.15000, colour);
	draw_2d_half_thick_line (x - 0.09375, y - 0.15000, x - 0.05626, y - 0.15000, colour);
	draw_2d_half_thick_line (x - 0.01875, y - 0.15000, x + 0.01875, y - 0.15000, colour);
	draw_2d_half_thick_line (x + 0.05625, y - 0.15000, x + 0.09375, y - 0.15000, colour);
	draw_2d_half_thick_line (x + 0.13125, y - 0.15000, x + 0.15000, y - 0.15000, colour);

	draw_2d_half_thick_line (x + 0.15000, y - 0.15000, x + 0.15000, y - 0.13125, colour);
	draw_2d_half_thick_line (x + 0.15000, y - 0.09375, x + 0.15000, y - 0.05626, colour);
	draw_2d_half_thick_line (x + 0.15000, y - 0.01875, x + 0.15000, y + 0.01875, colour);
	draw_2d_half_thick_line (x + 0.15000, y + 0.05625, x + 0.15000, y + 0.09375, colour);
	draw_2d_half_thick_line (x + 0.15000, y + 0.13125, x + 0.15000, y + 0.15000, colour);

	draw_2d_half_thick_line (x - 0.15000, y - 0.15000, x - 0.15000, y - 0.13125, colour);
	draw_2d_half_thick_line (x - 0.15000, y - 0.09375, x - 0.15000, y - 0.05626, colour);
	draw_2d_half_thick_line (x - 0.15000, y - 0.01875, x - 0.15000, y + 0.01875, colour);
	draw_2d_half_thick_line (x - 0.15000, y + 0.05625, x - 0.15000, y + 0.09375, colour);
	draw_2d_half_thick_line (x - 0.15000, y + 0.13125, x - 0.15000, y + 0.15000, colour);
}

void draw_hellfire_lobl_solid_target_marker (float x, float y, rgb_colour colour)
{
	draw_2d_half_thick_line (x - 0.15, y + 0.15, x + 0.15, y + 0.15, colour);
	draw_2d_half_thick_line (x + 0.15, y + 0.15, x + 0.15, y - 0.15, colour);
	draw_2d_half_thick_line (x + 0.15, y - 0.15, x - 0.15, y - 0.15, colour);
	draw_2d_half_thick_line (x - 0.15, y - 0.15, x - 0.15, y + 0.15, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hellfire_loal_dashed_target_marker (float x, float y, rgb_colour colour)
{
	draw_2d_half_thick_line (x - 0.55, y + 0.55, x - 0.45, y + 0.55, colour);
	draw_2d_half_thick_line (x - 0.35, y + 0.55, x - 0.25, y + 0.55, colour);
	draw_2d_half_thick_line (x - 0.15, y + 0.55, x - 0.05, y + 0.55, colour);
	draw_2d_half_thick_line (x + 0.05, y + 0.55, x + 0.15, y + 0.55, colour);
	draw_2d_half_thick_line (x + 0.25, y + 0.55, x + 0.35, y + 0.55, colour);
	draw_2d_half_thick_line (x + 0.45, y + 0.55, x + 0.55, y + 0.55, colour);

	draw_2d_half_thick_line (x - 0.55, y - 0.55, x - 0.45, y - 0.55, colour);
	draw_2d_half_thick_line (x - 0.35, y - 0.55, x - 0.25, y - 0.55, colour);
	draw_2d_half_thick_line (x - 0.15, y - 0.55, x - 0.05, y - 0.55, colour);
	draw_2d_half_thick_line (x + 0.05, y - 0.55, x + 0.15, y - 0.55, colour);
	draw_2d_half_thick_line (x + 0.25, y - 0.55, x + 0.35, y - 0.55, colour);
	draw_2d_half_thick_line (x + 0.45, y - 0.55, x + 0.55, y - 0.55, colour);

	draw_2d_half_thick_line (x + 0.55, y - 0.55, x + 0.55, y - 0.45, colour);
	draw_2d_half_thick_line (x + 0.55, y - 0.35, x + 0.55, y - 0.25, colour);
	draw_2d_half_thick_line (x + 0.55, y - 0.15, x + 0.55, y - 0.05, colour);
	draw_2d_half_thick_line (x + 0.55, y + 0.05, x + 0.55, y + 0.15, colour);
	draw_2d_half_thick_line (x + 0.55, y + 0.25, x + 0.55, y + 0.35, colour);
	draw_2d_half_thick_line (x + 0.55, y + 0.45, x + 0.55, y + 0.55, colour);

	draw_2d_half_thick_line (x - 0.55, y - 0.55, x - 0.55, y - 0.45, colour);
	draw_2d_half_thick_line (x - 0.55, y - 0.35, x - 0.55, y - 0.25, colour);
	draw_2d_half_thick_line (x - 0.55, y - 0.15, x - 0.55, y - 0.05, colour);
	draw_2d_half_thick_line (x - 0.55, y + 0.05, x - 0.55, y + 0.15, colour);
	draw_2d_half_thick_line (x - 0.55, y + 0.25, x - 0.55, y + 0.35, colour);
	draw_2d_half_thick_line (x - 0.55, y + 0.45, x - 0.55, y + 0.55, colour);
}

void draw_hellfire_loal_solid_target_marker (float x, float y, rgb_colour colour)
{
	draw_2d_half_thick_line (x - 0.55, y + 0.55, x + 0.55, y + 0.55, colour);
	draw_2d_half_thick_line (x + 0.55, y + 0.55, x + 0.55, y - 0.55, colour);
	draw_2d_half_thick_line (x + 0.55, y - 0.55, x - 0.55, y - 0.55, colour);
	draw_2d_half_thick_line (x - 0.55, y - 0.55, x - 0.55, y + 0.55, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_dashed_i_beam(float x, float y, rgb_colour colour)
{
	draw_2d_half_thick_line (x - 0.1000 + 0.0125, y + 0.2, x - 0.0500 - 0.0125, y + 0.2, colour);
	draw_2d_half_thick_line (x - 0.0500 + 0.0125, y + 0.2, x - 0.0000 - 0.0125, y + 0.2, colour);

	draw_2d_half_thick_line (x + 0.1000 - 0.0125, y + 0.2, x + 0.0500 + 0.0125, y + 0.2, colour);
	draw_2d_half_thick_line (x + 0.0500 - 0.0125, y + 0.2, x + 0.0000 + 0.0125, y + 0.2, colour);

	draw_2d_half_thick_line (x, y + 0.2000 - 0.0125, x, y + 0.1500 + 0.0125, colour);
	draw_2d_half_thick_line (x, y + 0.1500 - 0.0125, x, y + 0.1000 + 0.0125, colour);
	draw_2d_half_thick_line (x, y + 0.1000 - 0.0125, x, y + 0.0500 + 0.0125, colour);
	draw_2d_half_thick_line (x, y + 0.0500 - 0.0125, x, y + 0.0000 + 0.0125, colour);

	draw_2d_half_thick_line (x, y - 0.2000 + 0.0125, x, y - 0.1500 - 0.0125, colour);
	draw_2d_half_thick_line (x, y - 0.1500 + 0.0125, x, y - 0.1000 - 0.0125, colour);
	draw_2d_half_thick_line (x, y - 0.1000 + 0.0125, x, y - 0.0500 - 0.0125, colour);
	draw_2d_half_thick_line (x, y - 0.0500 + 0.0125, x, y - 0.0000 - 0.0125, colour);

	draw_2d_half_thick_line (x - 0.1000 + 0.0125, y - 0.2, x - 0.0500 - 0.0125, y - 0.2, colour);
	draw_2d_half_thick_line (x - 0.0500 + 0.0125, y - 0.2, x - 0.0000 - 0.0125, y - 0.2, colour);

	draw_2d_half_thick_line (x + 0.1000 - 0.0125, y - 0.2, x + 0.0500 + 0.0125, y - 0.2, colour);
	draw_2d_half_thick_line (x + 0.0500 - 0.0125, y - 0.2, x + 0.0000 + 0.0125, y - 0.2, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_solid_i_beam(float x, float y, rgb_colour colour)
{
	draw_2d_half_thick_line (x - 0.1000 + 0.0125, y + 0.2, x - 0.0000 - 0.0125, y + 0.2, colour);
	draw_2d_half_thick_line (x + 0.1000 - 0.0125, y + 0.2, x + 0.0000 + 0.0125, y + 0.2, colour);

	draw_2d_half_thick_line (x, y + 0.2000 - 0.0125, x, y + 0.1000 + 0.0125, colour);
	draw_2d_half_thick_line (x, y - 0.2000 + 0.0125, x, y - 0.1000 - 0.0125, colour);

	draw_2d_half_thick_line (x - 0.1000 + 0.0125, y - 0.2, x - 0.0000 - 0.0125, y - 0.2, colour);
	draw_2d_half_thick_line (x + 0.1000 - 0.0125, y - 0.2, x + 0.0000 + 0.0125, y - 0.2, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_field_of_regard_and_view_boxes (avionics_render_target render_target, rgb_colour colour)
{
	vec3d
		acquisition_source_direction,
		*cue_relative_position = get_acuisition_source_relative_position();

	float
		y_pos = (render_target == RENDER_TARGET_HUD) ? -0.6750 : -0.945,
		x,
		y;

	draw_2d_box(-0.3, y_pos, 0.3, y_pos - 0.225, FALSE, TRUE, colour);

	draw_2d_line ( 0.0000, y_pos,  0.0000, y_pos - 0.020, colour);
	draw_2d_line (-0.2250, y_pos, -0.2250, y_pos - 0.020, colour);
	draw_2d_line ( 0.2250, y_pos,  0.2250, y_pos - 0.020, colour);

	draw_2d_line ( 0.0000, y_pos - 0.205,  0.0000, y_pos - 0.225, colour);
	draw_2d_line (-0.2250, y_pos - 0.205, -0.2250, y_pos - 0.225, colour);
	draw_2d_line ( 0.2250, y_pos - 0.205,  0.2250, y_pos - 0.225, colour);

	draw_2d_line (-0.3000, y_pos - 0.075, -0.2800, y_pos - 0.075, colour);
	draw_2d_line ( 0.3000, y_pos - 0.075,  0.2800, y_pos - 0.075, colour);

	// EO direction
	x = eo_azimuth / eo_max_azimuth * 0.3;
	y = (eo_elevation / eo_min_elevation * -0.15) + y_pos - 0.075;

	draw_2d_box(x - 0.04, y - 0.03, x + 0.04, y + 0.03, FALSE, TRUE, colour);

	// acquisition source direction
	multiply_transpose_matrix3x3_vec3d(&acquisition_source_direction, current_flight_dynamics->attitude, cue_relative_position);
	normalise_3d_vector(&acquisition_source_direction);
	get_heading_and_pitch_from_3d_unit_vector(&acquisition_source_direction, &x, &y);

	x = bound(x / eo_max_azimuth * 0.3, -0.3, 0.3);
	y = bound((y / eo_max_elevation * 0.075) + y_pos - 0.075, y_pos - 0.225, y_pos);

	draw_2d_mono_sprite(cue_dot, x, y, colour);
}

void draw_apache_high_action_display(avionics_render_target render_target, rgb_colour colour)
{
#if 0
	const char* s;
	char buffer[200];
	float y_pos = -0.97;

	rangefinding_system rangefinder = get_range_finder();

	float target_range = get_range_to_target();
	int x_adjust, width;

	set_mono_font_type (MONO_FONT_TYPE_8X14);

	if (fill_boxes == 2)
	{
		rgb_colour bg_colour;

		set_rgb_colour (bg_colour, 0, 40, 0, 255);

		draw_2d_box(-0.98, y_pos, -0.35, y_pos - 0.2, TRUE, FALSE, bg_colour);
		draw_2d_box(0.98, y_pos, 0.35, y_pos - 0.2, TRUE, FALSE, bg_colour);
	}

	if (fill_boxes >= 1)
	{
		draw_2d_box(-0.98, y_pos, -0.35, y_pos - 0.2, FALSE, TRUE, colour);
		draw_2d_box(0.98, y_pos, 0.35, y_pos - 0.2, FALSE, TRUE, colour);
	}

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	//
	// target name
	//

	s = get_target_display_name (target, buffer, TRUE);

	if (s)
	{
		width = get_mono_font_string_width (s);
		set_2d_mono_font_position (0.0, y_pos + 0.1);
		set_mono_font_rel_position (-width * 0.5, 0);
		print_mono_font_string (s);
	}

	// airspeed and altitude
	{
		int airspeed = (int)knots(current_flight_dynamics->velocity_z.value);
		int altitude = get_apache_display_radar_altitude();

		sprintf(buffer, "%3d", airspeed);
		set_2d_mono_font_position (-0.7, y_pos + 0.08);
		set_mono_font_rel_position (0, 0);
		print_mono_font_string (buffer);

		if (altitude <= feet(get_low_altitude_warning_limit()))
			set_mono_font_colour(MFD_COLOUR_RED);
		else if (altitude >= feet(get_high_altitude_warning_limit()))
			set_mono_font_colour(MFD_COLOUR_YELLOW);

		if (altitude < 1500.0)
		{
			sprintf(buffer, "%4d", altitude);
			set_2d_mono_font_position (0.4, y_pos + 0.08);
			set_mono_font_rel_position (0, 0);
			print_mono_font_string (buffer);
		}

		set_mono_font_colour(colour);
	}

	// lower left box:
	// rang finder    range
	// targeting status

	switch (rangefinder)
	{
	case RANGEFINDER_FCR:
		s = "FCR";
		sprintf(buffer, "R%.1f", target_range * 0.001);
		break;
	case RANGEFINDER_LASER:
		s = "TADS";
		sprintf(buffer, "L%04.0f", target_range);
		break;
	case RANGEFINDER_TRIANGULATION:
		if (target_acquisition_system != TARGET_ACQUISITION_SYSTEM_OFF)
			s = "TADS";
		else
			s = "NONE";

		if (target_range > 0.0)
			sprintf(buffer, "A%.1f", target_range * 0.001);
		else
			sprintf(buffer, "AX.X");

		break;
	}

	set_2d_mono_font_position (-0.95, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (s);

	set_2d_mono_font_position (-0.40, y_pos - 0.03);
	x_adjust = -get_mono_font_string_width (buffer); // * 0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (buffer);

	// targeting status

	switch (weapon_lock_type)
	{
		case WEAPON_LOCK_NO_ACQUIRE:
			s = "NO ACQUIRE";
			break;
		case WEAPON_LOCK_NO_WEAPON:
			s = "NO WEAPON";
			break;
		case WEAPON_LOCK_NO_TARGET:
			s = "NO TARGET";
			break;
		case WEAPON_LOCK_INVALID_TARGET:
			s = "INVALID TGT";
			break;
		case WEAPON_LOCK_SEEKER_LIMIT:
			s = "SKR LIMIT";
			break;
		case WEAPON_LOCK_NO_LOS:
			s = "NO LOS";
			break;
		case WEAPON_LOCK_MIN_RANGE:
			if (rangefinder != RANGEFINDER_TRIANGULATION)
			{
				s = "MIN RNG";
				break;
			}
		case WEAPON_LOCK_MAX_RANGE:
			if (rangefinder != RANGEFINDER_TRIANGULATION)
			{
				s = "MAX RNG";
				break;
			}
		case WEAPON_LOCK_NO_BORESIGHT:
		case WEAPON_LOCK_VALID:
		case WEAPON_LOCK_BURST_LIMIT:
			s = "VALID LOCK";
			break;
		default:
			debug_fatal ("Invalid weapon lock type = %d", weapon_lock_type);
			break;
	}

	set_2d_mono_font_position (-0.95, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 10);
	print_mono_font_string (s);

	// lower right box:
	// weapon type
	// launch mode

	s = get_weapon_status(buffer, sizeof(buffer));

	set_2d_mono_font_position (0.37, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (s);

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH))
		s = "LOAL-HI";
	else
		s = "LOBL";

	set_2d_mono_font_position (0.37, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 9);
	print_mono_font_string (s);

	////////////////////////////////////////
	//
	// draw field of regard and view boxes
	//
	////////////////////////////////////////
#endif
	draw_field_of_regard_and_view_boxes(render_target, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_hud_mfd_common(void)
{
	c_scope_enabled = FALSE;
}

void deinitialise_apache_hud_mfd_common(void)
{

}
