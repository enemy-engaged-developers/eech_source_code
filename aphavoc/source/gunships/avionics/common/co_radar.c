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

#define DEBUG_MODULE								0

#define DEBUG_MODULE_BEST_TARGET_SCORING	0

#define DEBUG_MODULE_DISABLE_OBJECT_LOS	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND AND AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TERRAIN_LOS_MARKER_SCALE						(0.5)

#define TERRAIN_LOS_MARKER_LIFETIME					(3.0)

#define TERRAIN_LOS_MARKER_LARGE_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_RED)

#define TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_WHITE)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	draw_radar_sweep = FALSE,
	draw_radar_terrain_los_markers = FALSE;

radar_params
	ground_radar,
	air_radar;

static int
	ground_radar_on = FALSE,
	air_radar_on = FALSE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int
	radar_clutter_hatch_pattern[32] =
	{
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_radar (void)
{
	ground_radar_on = FALSE,
	air_radar_on = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_radar (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void limit_radar_sweep (radar_params *radar)
{
	float
		sweep_min_limit,
		sweep_max_limit;

	ASSERT (radar);

	if (radar->scan_arc_size != RADAR_SCAN_ARC_SIZE_360)
	{
		sweep_min_limit = radar->scan_arc_size * -0.5;

		sweep_max_limit = radar->scan_arc_size * 0.5;

		if (radar->sweep_offset < sweep_min_limit)
		{
			radar->sweep_offset = sweep_min_limit;

			radar->sweep_direction = RADAR_SWEEP_CW;

			if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
			{
				radar->sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
			}
		}
		else if (radar->sweep_offset > sweep_max_limit)
		{
			radar->sweep_offset = sweep_max_limit;

			radar->sweep_direction = RADAR_SWEEP_CCW;

			if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
			{
				radar->sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
			}
		}

		//
		// if single sweep inactive then ensure that the sweep offset is kept to the sweep limit (when scan arc size is increased)
		//

		if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
		{
			if (radar->sweep_offset <= rad (0.0))
			{
				radar->sweep_offset = sweep_min_limit;
			}
			else
			{
				radar->sweep_offset = sweep_max_limit;
			}
		}
	}
	else
	{
		if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
		{
			radar->sweep_offset = rad (0.0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_radar_sweep (radar_params *radar, float *cw_sweep_start_offset, float *cw_sweep_end_offset)
{
	float
		sweep_min_limit,
		sweep_max_limit;

	ASSERT (radar);

	ASSERT (cw_sweep_start_offset);

	ASSERT (cw_sweep_end_offset);

	ASSERT (radar->sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE);

	if (radar->scan_arc_size == RADAR_SCAN_ARC_SIZE_360)
	{
		if (radar->sweep_direction == RADAR_SWEEP_CW)
		{
			*cw_sweep_start_offset = radar->sweep_offset;

			radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset > rad (180.0f))
			{
				radar->sweep_offset -= rad (360.0f);
			}

			*cw_sweep_end_offset = radar->sweep_offset;

			if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
			{
				if ((*cw_sweep_start_offset < rad (0.0)) && (*cw_sweep_end_offset >= rad (0.0)))
				{
					radar->sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;

					radar->sweep_offset = rad (0.0);

					*cw_sweep_end_offset = rad (0.0);
				}
			}
		}
		else
		{
			*cw_sweep_end_offset = radar->sweep_offset;

			radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset < rad (-180.0f))
			{
				radar->sweep_offset += rad (360.0f);
			}

			*cw_sweep_start_offset = radar->sweep_offset;

			if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
			{
				if ((*cw_sweep_start_offset <= rad (0.0)) && (*cw_sweep_end_offset > rad (0.0)))
				{
					radar->sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;

					radar->sweep_offset = rad (0.0);

					*cw_sweep_end_offset = rad (0.0);
				}
			}
		}
	}
	else
	{
		sweep_min_limit = radar->scan_arc_size * -0.5;

		sweep_max_limit = radar->scan_arc_size * 0.5;

		if (radar->sweep_direction == RADAR_SWEEP_CW)
		{
			*cw_sweep_start_offset = radar->sweep_offset;

			radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset > sweep_max_limit)
			{
				*cw_sweep_end_offset = sweep_max_limit;

				if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
				{
					radar->sweep_offset = sweep_max_limit;

					radar->sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
				}
				else
				{
					radar->sweep_offset = sweep_max_limit - (radar->sweep_offset - sweep_max_limit);

					radar->sweep_offset = max (radar->sweep_offset, sweep_min_limit);

					if (radar->sweep_offset < *cw_sweep_start_offset)
					{
						*cw_sweep_start_offset = radar->sweep_offset;
					}
				}

				radar->sweep_direction = RADAR_SWEEP_CCW;
			}
			else
			{
				*cw_sweep_end_offset = radar->sweep_offset;
			}
		}
		else
		{
			*cw_sweep_end_offset = radar->sweep_offset;

			radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset < sweep_min_limit)
			{
				*cw_sweep_start_offset = sweep_min_limit;

				if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
				{
					radar->sweep_offset = sweep_min_limit;

					radar->sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
				}
				else
				{
					radar->sweep_offset = sweep_min_limit + (sweep_min_limit - radar->sweep_offset);

					radar->sweep_offset = min (radar->sweep_offset, sweep_max_limit);

					if (radar->sweep_offset > *cw_sweep_end_offset)
					{
						*cw_sweep_end_offset = radar->sweep_offset;
					}
				}

				radar->sweep_direction = RADAR_SWEEP_CW;
			}
			else
			{
				*cw_sweep_start_offset = radar->sweep_offset;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_bearing_within_cw_sweep_segment (float bearing, float cw_sweep_start_direction, float cw_sweep_end_direction)
{
	int
		result;

	if (cw_sweep_start_direction <= cw_sweep_end_direction)
	{
		result = (bearing >= cw_sweep_start_direction) && (bearing <= cw_sweep_end_direction);
	}
	else
	{
		//
		// crossed over +/-180 degs
		//

		if (bearing > 0.0)
		{
			result = bearing >= cw_sweep_start_direction;
		}
		else
		{
			result = bearing <= cw_sweep_end_direction;
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LARGE_STEP_SIZE			  	((float) 200.0)
#define ONE_OVER_LARGE_STEP_SIZE	((float) 1.0 / LARGE_STEP_SIZE)

#define NUM_SMALL_STEPS				(10)
#define ONE_OVER_NUM_SMALL_STEPS	((float) 1.0 / NUM_SMALL_STEPS)

#define SMALL_STEP_SIZE			 	((float) LARGE_STEP_SIZE / NUM_SMALL_STEPS)
#define ONE_OVER_SMALL_STEP_SIZE	((float) 1.0 / SMALL_STEP_SIZE)

static int get_terrain_los_clear (vec3d *source_position, vec3d *target_position)
{
	int
		count;

	float
		dx,
		dy,
		dz,
		ddx,
		ddy,
		ddz,
		flat_range,
		step_ratio;

	vec3d
		position;

	ASSERT (source_position);

	ASSERT (target_position);

	dx = target_position->x - source_position->x;
	dy = target_position->y - source_position->y;
	dz = target_position->z - source_position->z;

	flat_range = sqrt ((dx * dx) + (dz * dz));

	if (flat_range < (LARGE_STEP_SIZE * 2.0))
	{
		////////////////////////////////////////
		//
		// short range
		//
		////////////////////////////////////////

		//
		// small steps across the entire range
		//

		convert_float_to_int (flat_range * ONE_OVER_SMALL_STEP_SIZE, &count);

		if (count == 0)
		{
			count = 1;
		}

		step_ratio = 1.0 / (float) (count + 1);

		ddx = dx * step_ratio;
		ddy = dy * step_ratio;
		ddz = dz * step_ratio;

		position = *source_position;

		while (count--)
		{
			position.x += ddx;
			position.y += ddy;
			position.z += ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}
	}
	else
	{
		////////////////////////////////////////
		//
		// long range
		//
		////////////////////////////////////////

		//
		// large steps across the entire range
		//

		convert_float_to_int (flat_range * ONE_OVER_LARGE_STEP_SIZE, &count);

		if (count == 0)
		{
			count = 1;
		}

		step_ratio = 1.0 / (float) (count + 1);

		ddx = dx * step_ratio;
		ddy = dy * step_ratio;
		ddz = dz * step_ratio;

		position = *source_position;

		while (count--)
		{
			position.x += ddx;
			position.y += ddy;
			position.z += ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_LARGE_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}

		//
		// small steps across first large step (near source)
		//

		ddx *= ONE_OVER_NUM_SMALL_STEPS;
		ddy *= ONE_OVER_NUM_SMALL_STEPS;
		ddz *= ONE_OVER_NUM_SMALL_STEPS;

		position = *source_position;

		count = NUM_SMALL_STEPS - 1;

		while (count--)
		{
			position.x += ddx;
			position.y += ddy;
			position.z += ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}

		//
		// small steps across last large step (near target)
		//

		position = *target_position;

		count = NUM_SMALL_STEPS - 1;

		while (count--)
		{
			position.x -= ddx;
			position.y -= ddy;
			position.z -= ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}
	}

	return (TRUE);
}

#undef LARGE_STEP_SIZE
#undef ONE_OVER_LARGE_STEP_SIZE

#undef NUM_SMALL_STEPS
#undef ONE_OVER_NUM_SMALL_STEPS

#undef SMALL_STEP_SIZE
#undef ONE_OVER_SMALL_STEP_SIZE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE_DISABLE_OBJECT_LOS

static int get_object_los_clear (entity *target, vec3d *source_position, vec3d *target_position)
{
	return (TRUE);
}

#else

#define OBJECT_LOS_RANGE	((float) 500.0)

static int get_object_los_clear (entity *target, vec3d *source_position, vec3d *target_position)
{
	float
		dx,
		dy,
		dz,
		ddx,
		ddy,
		ddz,
		flat_range,
		ratio;

	vec3d
		position,
		intercept_point,
		face_normal;

	ASSERT (target);

	ASSERT (source_position);

	ASSERT (target_position);

	dx = target_position->x - source_position->x;
	dy = target_position->y - source_position->y;
	dz = target_position->z - source_position->z;

	flat_range = sqrt ((dx * dx) + (dz * dz));

	if (flat_range <= (OBJECT_LOS_RANGE * 2.0))
	{
		if (get_line_of_sight_collision_entity (get_gunship_entity (), target, source_position, target_position, &intercept_point, &face_normal))
		{
			return (FALSE);
		}

		if (get_line_of_sight_collision_tree (source_position, target_position, &intercept_point, &face_normal, FALSE, TRUE))
		{
			return (FALSE);
		}
	}
	else
	{
		ratio = OBJECT_LOS_RANGE / flat_range;

		ddx = dx * ratio;
		ddy = dy * ratio;
		ddz = dz * ratio;

		position.x = source_position->x + ddx;
		position.y = source_position->y + ddy;
		position.z = source_position->z + ddz;

		if (get_line_of_sight_collision_entity (get_gunship_entity (), target, source_position, &position, &intercept_point, &face_normal))
		{
			return (FALSE);
		}

		if (get_line_of_sight_collision_tree (source_position, &position, &intercept_point, &face_normal, FALSE, TRUE))
		{
			return (FALSE);
		}

		////////////////////////////////////////
		//
		// speed up ground radar around large cities - reduce LOS range at target end
		//

		position.x = target_position->x - (ddx * 0.5);
		position.y = target_position->y - (ddy * 0.5);
		position.z = target_position->z - (ddz * 0.5);

		/*
		position.x = target_position->x - ddx;
		position.y = target_position->y - ddy;
		position.z = target_position->z - ddz;
		*/

		//
		////////////////////////////////////////

		if (get_line_of_sight_collision_entity (get_gunship_entity (), target, &position, target_position, &intercept_point, &face_normal))
		{
			return (FALSE);
		}

		if (get_line_of_sight_collision_tree (&position, target_position, &intercept_point, &face_normal, FALSE, TRUE))
		{
			return (FALSE);
		}
	}

	return (TRUE);
}

#undef OBJECT_LOS_RANGE

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_valid_ground_radar_target (entity *target)
{
	target_types
		target_type;

	ASSERT (target);

	if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
	{
		target_type = (target_types) get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE);

		switch (target_type)
		{
			////////////////////////////////////////
			case TARGET_TYPE_INVALID:
			////////////////////////////////////////
			{
				return (get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER));

				break;
			}
			////////////////////////////////////////
			case TARGET_TYPE_GROUND:
			////////////////////////////////////////
			{
				return (TRUE);

				break;
			}
			////////////////////////////////////////
			case TARGET_TYPE_AIR:
			////////////////////////////////////////
			{
				if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
				{
					//
					// allow low and slow flying aircraft
					//

					if (get_local_entity_float_value (target, FLOAT_TYPE_VELOCITY) < knots_to_metres_per_second (50.0))
					{
						if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) < 10.0)
						{
							return (TRUE);
						}
					}
				}
				else
				{
					if (!get_local_entity_int_value (target, INT_TYPE_INSIDE_HANGAR))
					{
						if (!get_local_entity_int_value (target, INT_TYPE_LANDED_ON_CARRIER))
						{
							return (TRUE);
						}
					}
				}

				return (FALSE);

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid target type = %d", target_type);

				return (FALSE);

				break;
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_gunship_target_valid_for_ground_radar (entity *target)
{
	target_types
		target_type;

	ASSERT (target);

	target_type = (target_types) get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE);

	switch (target_type)
	{
		////////////////////////////////////////
		case TARGET_TYPE_INVALID:
		////////////////////////////////////////
		{
			//
			// this implicitly ignores radar clutter
			//

			return (FALSE);

			break;
		}
		////////////////////////////////////////
		case TARGET_TYPE_GROUND:
		////////////////////////////////////////
		{

			// loke 030322
			// infantry should never show up on ground radar

			if (session_ground_radar_ignores_infantry)
			{
				if (get_local_entity_int_value (target, INT_TYPE_VIEW_CATEGORY) == VIEW_CATEGORY_INFANTRY)
				{
					return (FALSE);
				}
			}

			return (TRUE);

			break;
		}
		////////////////////////////////////////
		case TARGET_TYPE_AIR:
		////////////////////////////////////////
		{
			if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
			{
				//
				// allow low and slow flying aircraft
				//

				if (get_local_entity_float_value (target, FLOAT_TYPE_VELOCITY) < knots_to_metres_per_second (50.0))
				{
					if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) < 10.0)
					{
						return (TRUE);
					}
				}
			}
			else
			{
				if (!get_local_entity_int_value (target, INT_TYPE_INSIDE_HANGAR))
				{
					if (!get_local_entity_int_value (target, INT_TYPE_LANDED_ON_CARRIER))
					{
						return (TRUE);
					}
				}
			}

			return (FALSE);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid target type = %d", target_type);

			return (FALSE);

			break;
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_ground_radar_los_clear (entity *target, vec3d *source_position, vec3d *target_position, float dx, float dz)
{
	ASSERT (target);

	ASSERT (source_position);

	ASSERT (target_position);

	if (get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
	{
		return (TRUE);
	}

	if (get_terrain_los_clear (source_position, target_position))
	{
		////////////////////////////////////////
		//
		// speed up ground radar around large cities - ignore bridge segments
		//

		if (get_local_entity_type (target) == ENTITY_TYPE_SEGMENT)
		{
			return (TRUE);
		}

		//
		////////////////////////////////////////

		if (get_object_los_clear (target, source_position, target_position))
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_best_ground_radar_target (void)
{
	float
		score,
		best_score,
		delta_score,
		one_over_scan_range,
		scan_arc_limit,
		weapon_min_range,
		weapon_max_range,
		target_range,
		source_heading,
		dx,
		dz,
		target_bearing,
		theta;

	entity
		*source,
		*target,
		*best_target;

	vec3d
		*source_position,
		*target_position;

	entity_sub_types
		weapon_sub_type;

	//
	// clear best score and target
	//

	best_score = 0.0;

	best_target = NULL;

	//
	// source
	//

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	//
	// scan limits
	//

	one_over_scan_range = 1.0 / ground_radar.scan_range;

	scan_arc_limit = ground_radar.scan_arc_size * 0.5;

	//
	// weapon min and max ranges
	//

	weapon_sub_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		weapon_min_range = weapon_database[weapon_sub_type].min_range;

		weapon_max_range = weapon_database[weapon_sub_type].max_range;
	}
	else
	{
		weapon_min_range = FLT_MAX;

		weapon_max_range = FLT_MIN;
	}

	//
	// evaluate each target
	//

	for (target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);
		 target;
		 target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET))
	{
		////////////////////////////////////////
		//
		// keep MANDATORY checks the same as get_selectable_ground_radar_target ()
		//
		////////////////////////////////////////

		//
		// MANDATORY: valid ground radar target
		//

		if (get_gunship_target_valid_for_ground_radar (target))
		{
			//
			// MANDATORY: target matches declutter criteria
			//

			if (get_target_matches_ground_radar_declutter_criteria (target))
			{
				//
				// MANDATORY: target within scan range
				//

				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

				// arneh, 20061106 - filter away targets outside pfz for apache
				if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE)
					if (!is_valid_pfz_target(target_position))
						continue;

				target_range = get_3d_range (source_position, target_position);
				if (target_range <= ground_radar.scan_range)
				{
					//
					// MANDATORY: ahead of aircraft
					//

					dx = target_position->x - source_position->x;
					dz = target_position->z - source_position->z;

					target_bearing = atan2 (dx, dz);

					theta = target_bearing - source_heading;

					if (theta > rad (180.0f))
					{
						theta -= rad (360.0f);
					}
					else if (theta < rad (-180.0f))
					{
						theta += rad (360.0f);
					}

					if ((theta >= rad (-45.0f)) && (theta <= rad (45.0f)))
					{
						////////////////////////////////////////
						//
						// evaluate score for target
						//
						////////////////////////////////////////

						score = 0.0;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("GROUND RADAR: evaluating %s", get_local_entity_string (target, STRING_TYPE_FULL_NAME));

						#endif

						//
						// SCORE: within radar scan arc limit
						//

						theta = target_bearing - (source_heading + ground_radar.scan_datum);

						if (theta > rad (180.0f))
						{
							theta -= rad (360.0f);
						}
						else if (theta < rad (-180.0f))
						{
							theta += rad (360.0f);
						}

						theta = fabs (theta);

						if (theta <= scan_arc_limit)
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (within radar scan arc limit, theta = %.2f, limit = %.2f)", delta_score, score, deg (theta), deg (scan_arc_limit));

						#endif

						//
						// SCORE: deviation from radar scan datum
						//

						theta = min (theta, rad (45.0f));

						delta_score = 1.0 - (theta * (1.0 / rad (45.0f)));

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (deviation from radar scan datum)", delta_score, score);

						#endif

						//
						// SCORE: line of sight clear
						//

						if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (line of sight clear)", delta_score, score);

						#endif

						//
						// SCORE: target priority
						//

						switch (get_local_entity_int_value (target, INT_TYPE_TARGET_PRIORITY_TYPE))
						{
							case TARGET_PRIORITY_UNKNOWN:
							{
								delta_score = 0.0;

								break;
							}
							case TARGET_PRIORITY_LOW:
							{
								delta_score = 0.5;

								break;
							}
							case TARGET_PRIORITY_MEDIUM:
							{
								delta_score = 1.0;

								break;
							}
							case TARGET_PRIORITY_HIGH:
							{
								delta_score = 2.0;

								break;
							}
							default:
							{
								debug_fatal ("Unknown target priority type");

								break;
							}
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (target priority)", delta_score, score);

						#endif

						//
						// SCORE: targetting player
						//

						if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
						{
							if (source == get_local_entity_parent (target, LIST_TYPE_TARGET))
							{
								delta_score = 1.0;
							}
							else
							{
								delta_score = 0.0;
							}
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (targetting player)", delta_score, score);

						#endif

						//
						// SCORE: within selected weapon range
						//

						if ((target_range >= weapon_min_range) && (target_range <= weapon_max_range))
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (within selected weapon range, min = %.2f, max = %.2f)", delta_score, score, weapon_min_range, weapon_max_range);

						#endif

						//
						// SCORE: range
						//

						delta_score = 1.0 - (target_range * one_over_scan_range);

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (range = %.2f, scan range = %.2f)", delta_score, score, target_range, ground_radar.scan_range);

						#endif

						////////////////////////////////////////
						//
						// compare score with best score
						//
						////////////////////////////////////////

						if (score > best_score)
						{
							best_score = score;

							best_target = target;
						}
					}
				}
			}
		}

		
	}

	return (best_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_selectable_ground_radar_target (entity *target)
{
	float
		target_range,
		source_heading,
		dx,
		dz,
		target_bearing,
		theta;

	entity
		*source;

	vec3d
		*source_position,
		*target_position;

	ASSERT (target);

	////////////////////////////////////////
	//
	// keep MANDATORY checks the same as get_best_ground_radar_target ()
	//
	////////////////////////////////////////

	//
	// MANDATORY: valid ground radar target
	//

	if (get_gunship_target_valid_for_ground_radar (target))
	{
		//
		// MANDATORY: target matches declutter criteria
		//

		if (get_target_matches_ground_radar_declutter_criteria (target))
		{
			source = get_gunship_entity ();

			//
			// MANDATORY: target within scan range
			//

			source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			// arneh, 20061106 - filter away targets outside pfz for apache
			if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE)
				if (!is_valid_pfz_target(target_position))
					return FALSE;

			target_range = get_3d_range (source_position, target_position);
			if (target_range <= ground_radar.scan_range)
			{
				//
				// MANDATORY: ahead of aircraft
				//

				source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

				dx = target_position->x - source_position->x;
				dz = target_position->z - source_position->z;

				target_bearing = atan2 (dx, dz);

				theta = target_bearing - source_heading;

				if (theta > rad (180.0f))
				{
					theta -= rad (360.0f);
				}
				else if (theta < rad (-180.0f))
				{
					theta += rad (360.0f);
				}

				if ((theta >= rad (-45.0f)) && (theta <= rad (45.0f)))
				{
					return (TRUE);
				}
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_target_matches_ground_radar_declutter_criteria (entity *target)
{
	ASSERT (target);

	if (ground_radar.target_priority_type == TARGET_PRIORITY_UNKNOWN)
	{
		return (TRUE);
	}
// Jabberwock 031107 Designated targets

	if (ground_radar.target_priority_type == TARGET_PRIORITY_DESIGNATED)
	{
		if (get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
		{
			return (TRUE);
		}
	}
// Jabberwock 031107 ends

	if (ground_radar.target_priority_type == get_local_entity_int_value (target, INT_TYPE_TARGET_PRIORITY_TYPE))
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_next_ground_radar_target (void)
{
	entity
		*current_target,
		*new_target;

	ground_radar.auto_target = FALSE;

	ground_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_ground_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_succ_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_ground_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_previous_ground_radar_target (void)
{
	entity
		*current_target,
		*new_target;

	ground_radar.auto_target = FALSE;

	ground_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_ground_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_pred_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_ground_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_ground_radar (int inactive_check)
{
	int
		x_sec,
		z_sec,
		x_sec_min,
		z_sec_min,
		x_sec_max,
		z_sec_max;

	float
		cw_sweep_start_offset,
		cw_sweep_end_offset,
		cw_sweep_start_direction,
		cw_sweep_end_direction,
		sweep_direction,
		heading,
		bearing,
		dx,
		dz,
		x_min,
		z_min,
		x_max,
		z_max,
		sqr_scan_range,
		sqr_target_range;

	entity
		*source,
		*target,
		*old_target,
		*new_target,
		*sector;

	vec3d
		*source_position,
		*target_position,
		cw_sweep_start_position,
		cw_sweep_end_position;

	////////////////////////////////////////
	//
	// get source data
	//
	////////////////////////////////////////

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	////////////////////////////////////////
	//
	// get radar sweep start and end
	//
	////////////////////////////////////////

	if ((ground_radar.sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE && ground_radar_is_active())
		|| inactive_check)
	{
		update_radar_sweep (&ground_radar, &cw_sweep_start_offset, &cw_sweep_end_offset);

		//
		// note: it is possible for sweep_mode to have switched to RADAR_SWEEP_MODE_SINGLE_INACTIVE after update_radar_sweep
		//

		heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

		cw_sweep_start_direction = heading + ground_radar.scan_datum + cw_sweep_start_offset;

		if (cw_sweep_start_direction > rad (180.0f))
		{
			cw_sweep_start_direction -= rad (360.0f);
		}
		else if (cw_sweep_start_direction < rad (-180.0f))
		{
			cw_sweep_start_direction += rad (360.0f);
		}

		cw_sweep_end_direction = heading + ground_radar.scan_datum + cw_sweep_end_offset;

		if (cw_sweep_end_direction > rad (180.0f))
		{
			cw_sweep_end_direction -= rad (360.0f);
		}
		else if (cw_sweep_end_direction < rad (-180.0f))
		{
			cw_sweep_end_direction += rad (360.0f);
		}

		////////////////////////////////////////
		//
		// get sector scan area
		//
		////////////////////////////////////////

		cw_sweep_start_position.x = source_position->x + (sin (cw_sweep_start_direction) * ground_radar.scan_range);
		cw_sweep_start_position.y = source_position->y;
		cw_sweep_start_position.z = source_position->z + (cos (cw_sweep_start_direction) * ground_radar.scan_range);

		cw_sweep_end_position.x = source_position->x + (sin (cw_sweep_end_direction) * ground_radar.scan_range);
		cw_sweep_end_position.y = source_position->y;
		cw_sweep_end_position.z = source_position->z + (cos (cw_sweep_end_direction) * ground_radar.scan_range);

		//
		// draw sweep
		//

		if (draw_radar_sweep && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_debug_3d_line (source_position, &cw_sweep_start_position, sys_col_green, 0.0);

			create_debug_3d_line (source_position, &cw_sweep_end_position, sys_col_red, 0.0);

			create_debug_3d_line (&cw_sweep_start_position, &cw_sweep_end_position, sys_col_white, 0.0);
		}

		//
		// sector scan min
		//

		x_min = min (min (cw_sweep_start_position.x, cw_sweep_end_position.x), source_position->x);
		z_min = min (min (cw_sweep_start_position.z, cw_sweep_end_position.z), source_position->z);

		get_x_sector (x_sec_min, x_min);
		get_z_sector (z_sec_min, z_min);

		x_sec_min = max (x_sec_min, MIN_MAP_X_SECTOR);
		z_sec_min = max (z_sec_min, MIN_MAP_Z_SECTOR);

		//
		// sector scan max
		//

		x_max = max (max (cw_sweep_start_position.x, cw_sweep_end_position.x), source_position->x);
		z_max = max (max (cw_sweep_start_position.z, cw_sweep_end_position.z), source_position->z);

		get_x_sector (x_sec_max, x_max);
		get_z_sector (z_sec_max, z_max);

		x_sec_max = min (x_sec_max, MAX_MAP_X_SECTOR);
		z_sec_max = min (z_sec_max, MAX_MAP_Z_SECTOR);

		////////////////////////////////////////
		//
		// sector scan
		//
		////////////////////////////////////////

		sqr_scan_range = ground_radar.scan_range * ground_radar.scan_range;

		for (z_sec = z_sec_min; z_sec <= z_sec_max; z_sec++)
		{
			for (x_sec = x_sec_min; x_sec <= x_sec_max; x_sec++)
			{
				sector = get_local_raw_sector_entity (x_sec, z_sec);

				target = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

				while (target)
				{
					if ((get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID) || get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
					{
						if (get_local_entity_parent (target, LIST_TYPE_GUNSHIP_TARGET))
						{
							////////////////////////////////////////
							//
							// target already on target list
							//
							////////////////////////////////////////

							//
							// reduce number of los checks by only considering 'even' entities on CW sweep and 'odd' entities on CCW sweep
							//

							if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_CONTINUOUS)
							{
								if (get_local_entity_index (target) & 1)
								{
									sweep_direction = RADAR_SWEEP_CCW;
								}
								else
								{
									sweep_direction = RADAR_SWEEP_CW;
								}
							}
							else
							{
								//
								// sweep all targets in single sweep mode
								//

								sweep_direction = ground_radar.sweep_direction;
							}

							if (ground_radar.sweep_direction == sweep_direction && !inactive_check)
							{
								//
								// only update target info if the target is within range, sweep segment and los is clear
								//

								target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

								sqr_target_range = get_sqr_3d_range (source_position, target_position);

								if (sqr_target_range <= sqr_scan_range)
								{
									dx = target_position->x - source_position->x;
									dz = target_position->z - source_position->z;

									bearing = atan2 (dx, dz);

									if (check_bearing_within_cw_sweep_segment (bearing, cw_sweep_start_direction, cw_sweep_end_direction))
									{
										if (get_ground_radar_los_clear (target, source_position, target_position, dx, dz))
										{
											if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
											{
												set_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, TRUE);

												set_local_entity_float_value (target, FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT, AIR_RADAR_CONTACT_TIMEOUT);
											}
											else
											{
												delete_local_entity_from_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET);
											}
										}
										else
										{
											set_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, FALSE);
										}
									}
								}
							}
						}
						else
						{
							////////////////////////////////////////
							//
							// target not on target list
							//
							////////////////////////////////////////

							if ((target != source) && get_valid_ground_radar_target (target))
							{
								//
								// reduce number of los checks by only considering 'even' entities on CW sweep and 'odd' entities on CCW sweep
								//

								if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_CONTINUOUS && !inactive_check)
								{
									if (get_local_entity_index (target) & 1)
									{
										sweep_direction = RADAR_SWEEP_CCW;
									}
									else
									{
										sweep_direction = RADAR_SWEEP_CW;
									}
								}
								else
								{
									//
									// sweep all targets in single sweep mode
									//

									sweep_direction = ground_radar.sweep_direction;
								}

								if (ground_radar.sweep_direction == sweep_direction)
								{
									target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

									sqr_target_range = get_sqr_3d_range (source_position, target_position);

									if (sqr_target_range <= sqr_scan_range)
									{
										dx = target_position->x - source_position->x;
										dz = target_position->z - source_position->z;

										bearing = atan2 (dx, dz);

										if (check_bearing_within_cw_sweep_segment (bearing, cw_sweep_start_direction, cw_sweep_end_direction))
										{
											if (get_ground_radar_los_clear (target, source_position, target_position, dx, dz))
											{
												insert_local_entity_into_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET, source, NULL);
											}
										}
									}
								}
							}
						}
					}

					target = get_local_entity_child_succ (target, LIST_TYPE_SECTOR);
				}
			}
		}
	}
	
	
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
	{
		////////////////////////////////////////
		//
		// update target
		//
		////////////////////////////////////////

		old_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		new_target = old_target;

		if (ground_radar.auto_target && !ground_radar.target_locked)
		{
			new_target = get_best_ground_radar_target ();

			set_gunship_target (new_target);
		}
		else
		{
			if (old_target)
			{
				if (get_local_entity_parent (old_target, LIST_TYPE_GUNSHIP_TARGET))
				{
					if (!get_selectable_ground_radar_target (old_target))
					{
						//
						// target is no longer valid
						//

						new_target = get_best_ground_radar_target ();

						set_gunship_target (new_target);
					}
				}
				else
				{
					//
					// target is no longer on the ground radar
					//

					new_target = get_best_ground_radar_target ();

					set_gunship_target (new_target);
				}
			}
			else
			{
				//
				// no target
				//

				new_target = get_best_ground_radar_target ();

				set_gunship_target (new_target);
			}
		}

		if (ground_radar.target_locked)
		{
			if ((new_target != old_target) || (new_target == NULL))
			{
				ground_radar.target_locked = FALSE;
			}
		}
	}

	target_locked = ground_radar.target_locked;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_common_ground_radar (void)
{
	if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
	{
		ground_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
	}

	ground_radar_on = TRUE;
	air_radar_on = FALSE;

	ground_radar.target_locked = target_locked;
}

void toggle_ground_radar_active(void)
{
	if (ground_radar_on)
		deactivate_common_ground_radar();
	else
		activate_common_ground_radar();	
}

int ground_radar_is_active(void)
{
	return ground_radar_on;
}

void set_ground_radar_is_active(int is_active)
{
	ground_radar_on = is_active;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_common_ground_radar (void)
{
	ground_radar_on = FALSE;
	
	ground_radar.target_locked = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_valid_air_radar_target (entity *target)
{
	ASSERT (target);

	if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
	{
		if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
		{
			if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) > 5.0)
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_gunship_target_valid_for_air_radar (entity *target)
{
	ASSERT (target);

	if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) > 5.0)
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_los_clear (entity *target, vec3d *source_position, vec3d *target_position)
{
	ASSERT (target);

	ASSERT (source_position);

	ASSERT (target_position);

	if (get_terrain_los_clear (source_position, target_position))
	{
		if (!target)
			return TRUE;

		if (get_object_los_clear (target, source_position, target_position))
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_best_air_radar_target (void)
{
	float
		score,
		best_score,
		delta_score,
		one_over_scan_range,
		scan_arc_limit,
		weapon_min_range,
		weapon_max_range,
		target_range,
		source_heading,
		target_heading,
		dx,
		dz,
		source_bearing,
		target_bearing,
		theta;

	entity
		*source,
		*target,
		*best_target;

	entity_sides
		source_side;

	vec3d
		*source_position,
		*target_position;

	entity_sub_types
		weapon_sub_type;

	//
	// clear best score and target
	//

	best_score = 0.0;

	best_target = NULL;

	//
	// source
	//

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	//
	// scan limits
	//

	one_over_scan_range = 1.0 / air_radar.scan_range;

	scan_arc_limit = air_radar.scan_arc_size * 0.5;

	//
	// weapon min and max ranges
	//

	weapon_sub_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		weapon_min_range = weapon_database[weapon_sub_type].min_range;

		weapon_max_range = weapon_database[weapon_sub_type].max_range;
	}
	else
	{
		weapon_min_range = FLT_MAX;

		weapon_max_range = FLT_MIN;
	}

	//
	// evaluate each target
	//

	target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

	while (target)
	{
		////////////////////////////////////////
		//
		// keep MANDATORY checks the same as get_selectable_air_radar_target ()
		//
		////////////////////////////////////////

		if (get_gunship_target_valid_for_air_radar (target))
		{
			//
			// MANDATORY: target matches declutter criteria
			//

			if (get_target_matches_air_radar_declutter_criteria (target, source_side))
			{
				//
				// MANDATORY: target within scan range
				//

				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

				target_range = get_3d_range (source_position, target_position);

				if (target_range <= air_radar.scan_range)
				{
					////////////////////////////////////////
					//
					// evaluate score for target
					//
					////////////////////////////////////////

					score = 0.0;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("AIR RADAR: evaluating %s", get_local_entity_string (target, STRING_TYPE_FULL_NAME));

					#endif

					//
					// SCORE: within radar scan arc limit
					//

					dx = target_position->x - source_position->x;
					dz = target_position->z - source_position->z;

					target_bearing = atan2 (dx, dz);

					if (air_radar.scan_arc_size == RADAR_SCAN_ARC_SIZE_360)
					{
						theta = target_bearing - source_heading;

						if (theta > rad (180.0f))
						{
							theta -= rad (360.0f);
						}
						else if (theta < rad (-180.0f))
						{
							theta += rad (360.0f);
						}

						theta = fabs (theta);

						delta_score = 1.0;
					}
					else
					{
						theta = target_bearing - (source_heading + air_radar.scan_datum);

						if (theta > rad (180.0f))
						{
							theta -= rad (360.0f);
						}
						else if (theta < rad (-180.0f))
						{
							theta += rad (360.0f);
						}

						theta = fabs (theta);

						if (theta <= scan_arc_limit)
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (within radar scan arc limit, theta = %.2f, limit = %.2f)", delta_score, score, deg (theta), deg (scan_arc_limit));

					#endif

					//
					// SCORE: deviation from radar scan datum
					//

					delta_score = 1.0 - (theta * (1.0 / rad (180.0f)));

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (deviation from radar scan datum)", delta_score, score);

					#endif

					//
					// SCORE: aspect (target facing player)
					//

					source_bearing = target_bearing + rad (180.0f);

					if (source_bearing > rad (180.0f))
					{
						source_bearing -= rad (360.0f);
					}
					else if (source_bearing < rad (-180.0f))
					{
						source_bearing += rad (360.0f);
					}

					target_heading = get_local_entity_float_value (target, FLOAT_TYPE_HEADING);

					theta = source_bearing - target_heading;

					if (theta > rad (180.0f))
					{
						theta -= rad (360.0f);
					}
					else if (theta < rad (-180.0f))
					{
						theta += rad (360.0f);
					}

					theta = fabs (theta);

					delta_score = 1.0 - (theta * (1.0 / rad (180.0f)));

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (aspect, theta = %.2f, source bearing = %.2f, target heading = %.2f)", delta_score, score, deg (theta), deg (source_bearing), deg (target_heading));

					#endif

					//
					// SCORE: line of sight clear
					//

					if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
					{
						delta_score = 1.0;
					}
					else
					{
						delta_score = 0.0;
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (line of sight clear)", delta_score, score);

					#endif

					//
					// SCORE: targetting player
					//

					if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_AIRCRAFT))
					{
						if (source == get_local_entity_parent (target, LIST_TYPE_TARGET))
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (targetting player)", delta_score, score);

					#endif

					//
					// SCORE: within selected weapon range
					//

					if ((target_range >= weapon_min_range) && (target_range <= weapon_max_range))
					{
						delta_score = 1.0;
					}
					else
					{
						delta_score = 0.0;
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (within selected weapon range, min = %.2f, max = %.2f)", delta_score, score, weapon_min_range, weapon_max_range);

					#endif

					//
					// SCORE: range
					//

					delta_score = 1.0 - (target_range * one_over_scan_range);

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (range = %.2f, scan range = %.2f)", delta_score, score, target_range, air_radar.scan_range);

					#endif

					//
					// SCORE: enemy
					//

					if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
					{
						delta_score = 1.0;
					}
					else
					{
						delta_score = 0.0;
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (enemy)", delta_score, score);

					#endif

					////////////////////////////////////////
					//
					// compare score with best score
					//
					////////////////////////////////////////

					if (score > best_score)
					{
						best_score = score;

						best_target = target;
					}
				}
			}
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	return (best_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_selectable_air_radar_target (entity *target)
{
	float
		target_range;

	entity
		*source;

	entity_sides
		source_side;

	vec3d
		*source_position,
		*target_position;

	ASSERT (target);

	source = get_gunship_entity ();

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	////////////////////////////////////////
	//
	// keep MANDATORY checks the same as get_best_air_radar_target ()
	//
	////////////////////////////////////////

	if (get_gunship_target_valid_for_air_radar (target))
	{
		//
		// MANDATORY: target matches declutter criteria
		//

		if (get_target_matches_air_radar_declutter_criteria (target, source_side))
		{
			//
			// MANDATORY: target within scan range
			//

			source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			target_range = get_3d_range (source_position, target_position);

			if (target_range <= air_radar.scan_range)
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_target_matches_air_radar_declutter_criteria (entity *target, entity_sides source_side)
{
	ASSERT (target);

	if (air_radar.show_allied_targets)
	{
		return (TRUE);
	}

	if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_next_air_radar_target (void)
{
	entity
		*current_target,
		*new_target;

	air_radar.auto_target = FALSE;

	air_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_air_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_succ_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_air_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_previous_air_radar_target (void)
{
	entity
		*current_target,
		*new_target;

	air_radar.auto_target = FALSE;

	air_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_air_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_pred_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_air_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_air_radar (void)
{
	int
		x_sec,
		z_sec,
		x_sec_min,
		z_sec_min,
		x_sec_max,
		z_sec_max;

	float
		cw_sweep_start_offset,
		cw_sweep_end_offset,
		cw_sweep_start_direction,
		cw_sweep_end_direction,
		heading,
		bearing,
		dx,
		dz,
		x_min,
		z_min,
		x_max,
		z_max,
		sqr_scan_range,
		sqr_target_range,
		radar_stealth_factor;

	entity
		*source,
		*target,
		*old_target,
		*new_target,
		*sector;

	vec3d
		*source_position,
		*target_position,
		cw_sweep_start_position,
		cw_sweep_end_position;

	////////////////////////////////////////
	//
	// get source data
	//
	////////////////////////////////////////

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	////////////////////////////////////////
	//
	// get radar sweep start and end
	//
	////////////////////////////////////////

	if (air_radar.sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE && air_radar_is_active())
	{
		update_radar_sweep (&air_radar, &cw_sweep_start_offset, &cw_sweep_end_offset);

		//
		// note: it is possible for sweep_mode to have switched to RADAR_SWEEP_MODE_SINGLE_INACTIVE after update_radar_sweep
		//

		heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

		cw_sweep_start_direction = heading + air_radar.scan_datum + cw_sweep_start_offset;

		if (cw_sweep_start_direction > rad (180.0f))
		{
			cw_sweep_start_direction -= rad (360.0f);
		}
		else if (cw_sweep_start_direction < rad (-180.0f))
		{
			cw_sweep_start_direction += rad (360.0f);
		}

		cw_sweep_end_direction = heading + air_radar.scan_datum + cw_sweep_end_offset;

		if (cw_sweep_end_direction > rad (180.0f))
		{
			cw_sweep_end_direction -= rad (360.0f);
		}
		else if (cw_sweep_end_direction < rad (-180.0f))
		{
			cw_sweep_end_direction += rad (360.0f);
		}

		////////////////////////////////////////
		//
		// get sector scan area
		//
		////////////////////////////////////////

		cw_sweep_start_position.x = source_position->x + (sin (cw_sweep_start_direction) * air_radar.scan_range);
		cw_sweep_start_position.y = source_position->y;
		cw_sweep_start_position.z = source_position->z + (cos (cw_sweep_start_direction) * air_radar.scan_range);

		cw_sweep_end_position.x = source_position->x + (sin (cw_sweep_end_direction) * air_radar.scan_range);
		cw_sweep_end_position.y = source_position->y;
		cw_sweep_end_position.z = source_position->z + (cos (cw_sweep_end_direction) * air_radar.scan_range);

		//
		// draw sweep
		//

		if (draw_radar_sweep && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_debug_3d_line (source_position, &cw_sweep_start_position, sys_col_green, 0.0);

			create_debug_3d_line (source_position, &cw_sweep_end_position, sys_col_red, 0.0);

			create_debug_3d_line (&cw_sweep_start_position, &cw_sweep_end_position, sys_col_white, 0.0);
		}

		//
		// sector scan min
		//

		x_min = min (min (cw_sweep_start_position.x, cw_sweep_end_position.x), source_position->x);
		z_min = min (min (cw_sweep_start_position.z, cw_sweep_end_position.z), source_position->z);

		get_x_sector (x_sec_min, x_min);
		get_z_sector (z_sec_min, z_min);

		x_sec_min = max (x_sec_min, MIN_MAP_X_SECTOR);
		z_sec_min = max (z_sec_min, MIN_MAP_Z_SECTOR);

		//
		// sector scan max
		//

		x_max = max (max (cw_sweep_start_position.x, cw_sweep_end_position.x), source_position->x);
		z_max = max (max (cw_sweep_start_position.z, cw_sweep_end_position.z), source_position->z);

		get_x_sector (x_sec_max, x_max);
		get_z_sector (z_sec_max, z_max);

		x_sec_max = min (x_sec_max, MAX_MAP_X_SECTOR);
		z_sec_max = min (z_sec_max, MAX_MAP_Z_SECTOR);

		////////////////////////////////////////
		//
		// sector scan
		//
		////////////////////////////////////////

		sqr_scan_range = air_radar.scan_range * air_radar.scan_range;

		for (z_sec = z_sec_min; z_sec <= z_sec_max; z_sec++)
		{
			for (x_sec = x_sec_min; x_sec <= x_sec_max; x_sec++)
			{
				sector = get_local_raw_sector_entity (x_sec, z_sec);

				target = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

				while (target)
				{
					if (get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE) == TARGET_TYPE_AIR)
					{
						if (get_local_entity_parent (target, LIST_TYPE_GUNSHIP_TARGET))
						{
							////////////////////////////////////////
							//
							// target already on target list
							//
							////////////////////////////////////////

							//
							// only update target info if the target is within range, sweep segment and los is clear
							//

							target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							sqr_target_range = get_sqr_3d_range (source_position, target_position);

							radar_stealth_factor = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_STEALTH_FACTOR);

							if (radar_stealth_factor < NO_RADAR_STEALTH_FACTOR)
							{
								sqr_target_range /= radar_stealth_factor * radar_stealth_factor;
							}

							if (sqr_target_range <= sqr_scan_range)
							{
								dx = target_position->x - source_position->x;
								dz = target_position->z - source_position->z;

								bearing = atan2 (dx, dz);

								if (check_bearing_within_cw_sweep_segment (bearing, cw_sweep_start_direction, cw_sweep_end_direction))
								{
									if (get_los_clear (target, source_position, target_position))
									{
										if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
										{
											set_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, TRUE);

											set_local_entity_float_value (target, FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT, AIR_RADAR_CONTACT_TIMEOUT);
										}
										else
										{
											delete_local_entity_from_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET);
										}
									}
									else
									{
										set_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, FALSE);
									}
								}
							}
						}
						else
						{
							////////////////////////////////////////
							//
							// target not on target list
							//
							////////////////////////////////////////

							if ((target != source) && get_valid_air_radar_target (target))
							{
								target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

								sqr_target_range = get_sqr_3d_range (source_position, target_position);

								radar_stealth_factor = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_STEALTH_FACTOR);

								if (radar_stealth_factor < NO_RADAR_STEALTH_FACTOR)
								{
									sqr_target_range /= radar_stealth_factor * radar_stealth_factor;
								}

								if (sqr_target_range <= sqr_scan_range)
								{
									dx = target_position->x - source_position->x;
									dz = target_position->z - source_position->z;

									bearing = atan2 (dx, dz);

									if (check_bearing_within_cw_sweep_segment (bearing, cw_sweep_start_direction, cw_sweep_end_direction))
									{
										if (get_los_clear (target, source_position, target_position))
										{
											insert_local_entity_into_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET, source, NULL);
										}
									}
								}
							}
						}
					}

					target = get_local_entity_child_succ (target, LIST_TYPE_SECTOR);
				}
			}
		}

		////////////////////////////////////////
		//
		// update target
		//
		////////////////////////////////////////

		old_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		new_target = old_target;

		if (air_radar.auto_target && !air_radar.target_locked)
		{
			new_target = get_best_air_radar_target ();

			set_gunship_target (new_target);
		}
		else
		{
			if (old_target)
			{
				if (get_local_entity_parent (old_target, LIST_TYPE_GUNSHIP_TARGET))
				{
					if (!get_selectable_air_radar_target (old_target))
					{
						//
						// target is no longer valid
						//

						new_target = get_best_air_radar_target ();

						set_gunship_target (new_target);
					}
				}
				else
				{
					//
					// target is no longer on the air radar
					//

					new_target = get_best_air_radar_target ();

					set_gunship_target (new_target);
				}
			}
			else
			{
				//
				// no target
				//

				new_target = get_best_air_radar_target ();

				set_gunship_target (new_target);
			}
		}

		if (air_radar.target_locked)
		{
			if ((new_target != old_target) || (new_target == NULL))
			{
				air_radar.target_locked = FALSE;
			}
		}
	}

	target_locked = air_radar.target_locked;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_common_air_radar (void)
{
	if (air_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
	{
		air_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
	}
	
	ground_radar_on = FALSE;
	air_radar_on = TRUE;

	air_radar.target_locked = target_locked;
}

void toggle_air_radar_active(void)
{
	if (air_radar_on)
		deactivate_common_air_radar();
	else
		activate_common_air_radar();	
}

int air_radar_is_active(void)
{
	return air_radar_on;
}

void set_air_radar_is_active(int is_active)
{
	air_radar_on = is_active;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_common_air_radar (void)
{
	air_radar_on = FALSE;

	air_radar.target_locked = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031108 Designated targets

void select_next_designated_ground_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_designated_ground_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_pred_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	set_gunship_target (new_target);
}

void select_next_designated_air_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_designated_air_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_pred_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	set_gunship_target (new_target);
}
