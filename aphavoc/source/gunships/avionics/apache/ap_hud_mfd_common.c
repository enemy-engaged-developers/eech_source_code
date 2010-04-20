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

void initialise_apache_hud_mfd_common(void)
{
	c_scope_enabled = FALSE;
}

void deinitialise_apache_hud_mfd_common(void)
{

}
