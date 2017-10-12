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

// TODO This is used by the Hind. It should be moved to that code
static rgb_colour
	white_needle_colour_level1,
	grey_needle_colour_level1,
	yellow_needle_colour_level1,
	orange_needle_colour_level1,
	red_needle_colour_level1,
	white_digit_colour_level1,
	yellow_digit_colour_level1,
	white_needle_colour_level2,
	grey_needle_colour_level2,
	yellow_needle_colour_level2,
	orange_needle_colour_level2,
	red_needle_colour_level2,
	white_digit_colour_level2,
	yellow_digit_colour_level2,
	white_needle_colour_level3,
	grey_needle_colour_level3,
	yellow_needle_colour_level3,
	orange_needle_colour_level3,
	red_needle_colour_level3,
	white_digit_colour_level3,
	yellow_digit_colour_level3;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO This is used by the Hind. It should be moved to that code

void initialise_havoc_instrument_colours (void)
{
	set_rgb_colour (white_needle_colour_level1,  255, 255, 255, 0);
	set_rgb_colour (grey_needle_colour_level1,  128, 128, 128, 0);
	set_rgb_colour (yellow_needle_colour_level1, 205, 183,  13, 0);
	set_rgb_colour (orange_needle_colour_level1, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level1,    188,  58,  26, 0);
	set_rgb_colour (white_digit_colour_level1,   200, 200, 200, 0);
	set_rgb_colour (yellow_digit_colour_level1,  205, 183,  13, 0);
	set_rgb_colour (white_needle_colour_level2,  255, 147,   0, 0);
	set_rgb_colour (grey_needle_colour_level2,   128,  74,   0, 0);
	set_rgb_colour (yellow_needle_colour_level2, 255, 147,   0, 0);
	set_rgb_colour (orange_needle_colour_level2, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level2,    255, 147,   0, 0);
	set_rgb_colour (white_digit_colour_level2,   255, 147,   0, 0);
	set_rgb_colour (yellow_digit_colour_level2,  205, 183,  13, 0);
	set_rgb_colour (white_needle_colour_level3,  255, 147,   0, 0);
	set_rgb_colour (grey_needle_colour_level3,   128,  74,   0, 0);
	set_rgb_colour (yellow_needle_colour_level3, 255, 147,   0, 0);
	set_rgb_colour (orange_needle_colour_level3, 255, 147,   0, 0);
	set_rgb_colour (red_needle_colour_level3,    255, 147,   0, 0);
	set_rgb_colour (white_digit_colour_level3,   255, 147,   0, 0);
	set_rgb_colour (yellow_digit_colour_level3,  205, 183,  13, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_havoc_virtual_cockpit_adi_angles (matrix3x3 attitude, float *heading, float *pitch, float *roll)
{
	matrix3x3
		inverse_attitude,
		heading_rotation,
		result;

	//
	// get inverse attitude (attitude * inverse attitude = identity) which aligns the ADI with the world axis
	//

	inverse_attitude[0][0] = attitude[0][0];
	inverse_attitude[1][0] = attitude[0][1];
	inverse_attitude[2][0] = attitude[0][2];
	inverse_attitude[0][1] = attitude[1][0];
	inverse_attitude[1][1] = attitude[1][1];
	inverse_attitude[2][1] = attitude[1][2];
	inverse_attitude[0][2] = attitude[2][0];
	inverse_attitude[1][2] = attitude[2][1];
	inverse_attitude[2][2] = attitude[2][2];

	//
	// rotate heading so that the ADI pitch markings face the pilot
	//

	get_3d_transformation_matrix (heading_rotation, get_heading_from_attitude_matrix (attitude), 0.0, 0.0);

	multiply_matrix3x3_matrix3x3 (result, heading_rotation, inverse_attitude);

	*heading = get_heading_from_attitude_matrix (result);

	*pitch = get_pitch_from_attitude_matrix (result);

	*roll = get_roll_from_attitude_matrix (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
{
	float
		direction_finder_needle_value,
		flight_path_needle_value,
		drift_needle_value,
		dx,
		dz,
		heading,
		bearing,
		length1,
		length2,
		dot_product,
		cross_product;

	entity
		*en,
		*wp,
		*prev_wp;

	vec3d
		*motion_vector,
		wind_vector,
		*en_position,
		wp_position,
		prev_wp_position;

	vec2d
		v1,
		v2;

	ASSERT (direction_finder);

	ASSERT (flight_path);

	ASSERT (drift);

	direction_finder_needle_value = 0.0;

	flight_path_needle_value = 0.0;

	drift_needle_value = 0.0;

	if (test_cockpit_instruments)
	{
		static float
			direction_finder_value = rad (0.0),
			flight_path_value = rad (90.0),
			drift_value = rad (-20.0);

		//
		// automatic direction finder
		//

		direction_finder_value += rad (5.0);

		if (direction_finder_value > rad (360.0))
		{
			direction_finder_value -= rad (360.0);
		}

		direction_finder_needle_value = direction_finder_value;

		//
		// flight path
		//

		flight_path_value += rad (3.0);

		if (flight_path_value > rad (360.0))
		{
			flight_path_value -= rad (360.0);
		}

		flight_path_needle_value = flight_path_value;

		//
		// drift
		//

		drift_value += rad (1.0);

		if (drift_value > rad (35.0))
		{
			drift_value = rad (-35.0);
		}

		drift_needle_value = drift_value;
	}
	else
	{
		if (!havoc_damage.navigation_computer)
		{
			en = get_gunship_entity ();

			wp = get_local_entity_current_waypoint (en);

			if (wp)
			{
				//
				// automatic direction finder
				//

				heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

				en_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

				get_waypoint_display_position (en, wp, &wp_position);

				dx = wp_position.x - en_position->x;
				dz = wp_position.z - en_position->z;

				bearing = atan2 (dx, dz);

				direction_finder_needle_value = bearing - heading;

				//
				// flight path
				//

				prev_wp = get_local_entity_prev_waypoint (en);

				if ((prev_wp) && (prev_wp != wp))
				{
					get_waypoint_display_position (en, prev_wp, &prev_wp_position);

					dx = wp_position.x - prev_wp_position.x;
					dz = wp_position.z - prev_wp_position.z;

					bearing = atan2 (dx, dz);

					flight_path_needle_value = bearing - heading;
				}
				else
				{
					flight_path_needle_value = direction_finder_needle_value;
				}

				//
				// drift
				//

				drift_needle_value = 0.0;

				motion_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

				v1.x = motion_vector->x;
				v1.y = motion_vector->z;

				length1 = (v1.x * v1.x) + (v1.y * v1.y);

				if (length1 > 0.001)
				{
					length1 = sqrt (length1);

					v1.x /= length1;
					v1.y /= length1;

					get_session_wind_velocity_at_point (en_position, &wind_vector);

					v2.x = motion_vector->x + wind_vector.x;
					v2.y = motion_vector->z + wind_vector.z;

					length2 = (v2.x * v2.x) + (v2.y * v2.y);

					if (length2 > 0.001)
					{
						length2 = sqrt (length2);

						v2.x /= length2;
						v2.y /= length2;

						dot_product = get_2d_unit_vector_dot_product (&v1, &v2);

						drift_needle_value = acos (dot_product);

						cross_product = (v1.x * v2.y) - (v2.x * v1.y);

						if (cross_product > 0.0)
						{
							drift_needle_value = -drift_needle_value;
						}
					}
				}
			}
		}
	}

	drift_needle_value = bound (drift_needle_value, rad (-30.0), rad (30.0));

	*direction_finder = direction_finder_needle_value;

	*flight_path = flight_path_needle_value;

	*drift = drift_needle_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_havoc_virtual_cockpit_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
{
	float
		direction_finder_needle_value,
		flight_path_needle_value,
		drift_needle_value;

	ASSERT  (direction_finder);

	ASSERT (flight_path);

	ASSERT (drift);

	get_hsi_needle_values (&direction_finder_needle_value, &flight_path_needle_value, &drift_needle_value);

	*direction_finder = direction_finder_needle_value * -1.0;

	*flight_path = flight_path_needle_value * -1.0;

	*drift = drift_needle_value * -1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
