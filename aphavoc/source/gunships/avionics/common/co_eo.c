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

#define SMALL_TERRAIN_LOS_STEP						(20.0)

#define LARGE_TERRAIN_LOS_STEP						(200.0)

#define TERRAIN_LOS_MARKER_SCALE						(0.5)

#define TERRAIN_LOS_MARKER_LIFETIME					(0.0)

#define TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_WHITE)

#define TERRAIN_LOS_MARKER_LARGE_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_RED)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	eo_target_locked,
	eo_on_target,
	eo_low_light,
	eo_ground_stabilised;

target_acquisition_systems
	eo_sensor;

float
	eo_azimuth,
	eo_min_azimuth,
	eo_max_azimuth,
	eo_elevation,
	eo_min_elevation,
	eo_max_elevation,
	eo_max_visual_range;

viewpoint
	eo_vp;

int
	draw_eo_boresight = FALSE,
	draw_eo_terrain_los_markers = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct EO_TARGET
{
	entity
		*target;

	float
		sqr_range,
		radius;

	vec3d
		target_position;

	struct EO_TARGET
		*succ,
		*pred;
};

typedef struct EO_TARGET eo_target;

static eo_target
	*eo_target_root;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_eo (void)
{
	eo_target_locked = FALSE;

	eo_on_target = FALSE;

	eo_low_light = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_eo (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_eo_target_list (void)
{
	eo_target_root = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deinitialise_eo_target_list (void)
{
	eo_target
		*this_eo_target,
		*succ;

	this_eo_target = eo_target_root;

	while (this_eo_target)
	{
		succ = this_eo_target->succ;

		free_mem (this_eo_target);

		this_eo_target = succ;
	}

	eo_target_root = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void insert_entity_into_eo_target_list (entity *target, float sqr_range, float radius, vec3d *target_position)
{
	eo_target
		*new,
		*succ,
		*pred;

	int
		insert;

	ASSERT (target_position);

	new = malloc_fast_mem (sizeof (eo_target));

	new->target = target;
	new->sqr_range = sqr_range;
	new->radius = radius;
	new->target_position = *target_position;

	//
	// sort list in ascending order of sqr_range
	//

	succ = eo_target_root;
	pred = NULL;

	while (TRUE)
	{
		if (succ)
		{
			insert = sqr_range < succ->sqr_range;
		}
		else
		{
			insert = TRUE;
		}

		if (insert)
		{
			new->succ = succ;
			new->pred = pred;

			if (succ)
			{
				succ->pred = new;
			}

			if (pred)
			{
				pred->succ = new;
			}
			else
			{
				eo_target_root = new;
			}

			break;
		}

		pred = succ;

		succ = succ->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_eo_centred_viewpoint (viewpoint *vp)
{
	ASSERT (vp);

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			get_apache_eo_centred_viewpoint (vp);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			get_havoc_eo_centred_viewpoint (vp);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			get_comanche_eo_centred_viewpoint (vp);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			get_hokum_eo_centred_viewpoint (vp);

			break;
		}
		////Moje 030519 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			get_blackhawk_eo_centred_viewpoint (vp);

			break;
		}
		////Moje 030519 End
		////Moje 030612 start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			get_hind_eo_centred_viewpoint (vp);

			break;
		}
		////Moje 030612 end
		////Moje 030816 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			get_ah64a_eo_centred_viewpoint (vp);
			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			get_ka50_eo_centred_viewpoint (vp);
			break;
		}
		////Moje 030816 end
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
		default:
		////////////////////////////////////////
		{
			get_apache_eo_centred_viewpoint (vp);
//			debug_fatal ("Invalid gunship type = %d", get_global_gunship_type ());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_eo_boresight_terrain_los_clear_range (void)
{
	float
		los_clear_range;

	vec3d
		position,
		step;

	//
	// small steps across near range
	//

	position = eo_vp.position;

	los_clear_range = 0.0;

	step.x = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.x;
	step.y = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.y;
	step.z = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.z;

	while (los_clear_range < LARGE_TERRAIN_LOS_STEP)
	{
		los_clear_range += SMALL_TERRAIN_LOS_STEP;

		position.x += step.x;
		position.y += step.y;
		position.z += step.z;

		if (draw_eo_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
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
			return (los_clear_range);
		}
	}

	//
	// large steps across complete range
	//

	position = eo_vp.position;

	los_clear_range = 0.0;

	step.x = LARGE_TERRAIN_LOS_STEP * eo_vp.zv.x;
	step.y = LARGE_TERRAIN_LOS_STEP * eo_vp.zv.y;
	step.z = LARGE_TERRAIN_LOS_STEP * eo_vp.zv.z;

	while (los_clear_range < eo_max_visual_range)
	{
		los_clear_range += LARGE_TERRAIN_LOS_STEP;

		position.x += step.x;
		position.y += step.y;
		position.z += step.z;

		if (draw_eo_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
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
			return (los_clear_range);
		}
	}

	return (eo_max_visual_range);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_eo_boresight_tree_los_clear_range (vec3d *los_start, vec3d *los_end)
{
	float
		los_clear_range;

	vec3d
		intercept_point,
		face_normal;

	ASSERT (los_start);

	ASSERT (los_end);

	if (get_line_of_sight_collision_tree (los_start, los_end, &intercept_point, &face_normal, FALSE, TRUE))
	{
		los_clear_range = get_3d_range (los_start, &intercept_point);
	}
	else
	{
		los_clear_range = eo_max_visual_range;
	}

	return (los_clear_range);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_eo_visibility (void)
{
	vec3d
		*position;

	eo_low_light = FALSE;

	switch (eo_sensor)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

			if (get_simple_session_weather_at_point (position) == WEATHERMODE_HEAVY_RAIN)
			{
				eo_low_light = TRUE;
			}

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DTV:
		case TARGET_ACQUISITION_SYSTEM_DVO:
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		{
			if (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE) == DAY_SEGMENT_TYPE_NIGHT)
			{
				eo_low_light = TRUE;
			}

			break;
		}
		default:
		{
			debug_fatal ("Invalid eo sensor = %d", eo_sensor);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_eo_target (vec3d *los_start, vec3d *los_end, vec3d *los_unit_vector, float max_range, int first_pass, entity *first_pass_target)
{
	int
		x_sector_min,
		z_sector_min,
		x_sector_max,
		z_sector_max,
		x_sector,
		z_sector;

	float
		max_sqr_range,
		target_sqr_range,
		dx,
		dy,
		dz,
		x_min,
		z_min,
		x_max,
		z_max,
		los_to_target_distance,
		target_radius,
		terrain_los_range,
		tree_los_range,
		los_range,
		los_sqr_range,
		los_test_distance;

	entity
		*source,
		*target,
		*this_sector,
		*eo_boresight_target;

	vec3d
		target_position,
		los_test_position1,
		los_test_position2,
		intercept_point,
		face_normal;

	eo_target
		*this_eo_target;

	object_3d_index_numbers
		object_3d_index;

	ASSERT (los_start);

	ASSERT (los_end);

	ASSERT (los_unit_vector);

	if (first_pass)
	{
		ASSERT (!first_pass_target);
	}
	else
	{
		ASSERT (first_pass_target);
	}

	if (draw_eo_boresight && (get_view_mode () == VIEW_MODE_EXTERNAL))
	{
		if (first_pass)
		{
			create_debug_3d_line (los_start, los_end, sys_col_green, 0.0);
		}
		else
		{
			create_debug_3d_line (los_start, los_end, sys_col_magenta, 0.0);
		}
	}

	eo_boresight_target = NULL;

	max_sqr_range = max_range * max_range;

	////////////////////////////////////////
	//
	// source
	//
	////////////////////////////////////////

	source = get_gunship_entity ();

	////////////////////////////////////////
	//
	// calc sector scan (widened to include entites which are overlapping sector edges)
	//
	////////////////////////////////////////

	if (los_start->x <= los_end->x)
	{
		x_min = los_start->x;
		x_max = los_end->x;
	}
	else
	{
		x_min = los_end->x;
		x_max = los_start->x;
	}

	if (los_start->z <= los_end->z)
	{
		z_min = los_start->z;
		z_max = los_end->z;
	}
	else
	{
		z_min = los_end->z;
		z_max = los_start->z;
	}

	x_min = max (x_min - LARGEST_3D_OBJECT_RADIUS, MIN_MAP_X);
	z_min = max (z_min - LARGEST_3D_OBJECT_RADIUS, MIN_MAP_Z);
	x_max = min (x_max + LARGEST_3D_OBJECT_RADIUS, MAX_MAP_X);
	z_max = min (z_max + LARGEST_3D_OBJECT_RADIUS, MAX_MAP_Z);

	get_x_sector (x_sector_min, x_min);
	get_z_sector (z_sector_min, z_min);
	get_x_sector (x_sector_max, x_max);
	get_z_sector (z_sector_max, z_max);

	////////////////////////////////////////
	//
	// sector scan (locate possible targets)
	//
	////////////////////////////////////////

	initialise_eo_target_list ();

	for (z_sector = z_sector_min; z_sector <= z_sector_max; z_sector++)
	{
		for (x_sector = x_sector_min; x_sector <= x_sector_max; x_sector++)
		{
			this_sector = get_local_raw_sector_entity (x_sector, z_sector);

			target = get_local_entity_first_child (this_sector, LIST_TYPE_SECTOR);

			while (target)
			{
				//
				// if second pass then ensure that the first pass target gets inserted into the target list
				//
				// (this is necessary because floating point errors can exclude it)
				//

				if (target == first_pass_target)
				{
					get_local_entity_target_point (target, &target_position);

					dx = target_position.x - los_start->x;
					dy = target_position.y - los_start->y;
					dz = target_position.z - los_start->z;

					target_sqr_range = (dx * dx) + (dy * dy) + (dz * dz);

 					los_to_target_distance = 0.0;

					object_3d_index = get_local_entity_int_value (target, INT_TYPE_OBJECT_3D_SHAPE);

					ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

					target_radius = get_object_3d_radius (object_3d_index);

					insert_entity_into_eo_target_list (target, target_sqr_range, target_radius, &target_position);
				}
				else if (target != source)
				{
					if (get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID)
					{
						if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
						{
							if (!get_local_entity_int_value (target, INT_TYPE_INSIDE_HANGAR))
							{
								get_local_entity_target_point (target, &target_position);

								if
								(
									(target_position.x >= x_min) &&
									(target_position.x <= x_max) &&
									(target_position.z >= z_min) &&
									(target_position.z <= z_max)
								)
								{
									dx = target_position.x - los_start->x;
									dy = target_position.y - los_start->y;
									dz = target_position.z - los_start->z;

									target_sqr_range = (dx * dx) + (dy * dy) + (dz * dz);

									if (target_sqr_range < max_sqr_range)
									{
				 						los_to_target_distance = get_3d_perp_dist_of_point_from_line (los_start, los_end, &target_position, NULL);

										object_3d_index = get_local_entity_int_value (target, INT_TYPE_OBJECT_3D_SHAPE);

										ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

										target_radius = get_object_3d_radius (object_3d_index);

										if (los_to_target_distance < target_radius)
										{
											insert_entity_into_eo_target_list (target, target_sqr_range, target_radius, &target_position);
										}
									}
								}
							}
						}
						else
						{
							delete_local_entity_from_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET);
						}
					}
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_SECTOR);
			}
		}
	}

	////////////////////////////////////////
	//
	// scan possible targets (nearest first)
	//
	////////////////////////////////////////

	if (eo_target_root)
	{
		if (first_pass)
		{
			terrain_los_range = get_eo_boresight_terrain_los_clear_range ();

			tree_los_range = get_eo_boresight_tree_los_clear_range (los_start, los_end);

			los_range = min (terrain_los_range, tree_los_range);
		}
		else
		{
			los_range = max_range + 1.0;
		}

		los_sqr_range = los_range * los_range;

		this_eo_target = eo_target_root;

		los_test_position1.x = los_start->x;
		los_test_position1.y = los_start->y;
		los_test_position1.z = los_start->z;

		while (this_eo_target)
		{
			if (this_eo_target->sqr_range < los_sqr_range)
			{
				los_test_distance = sqrt (this_eo_target->sqr_range);

				los_test_position2.x = los_start->x + los_unit_vector->x * los_test_distance;
				los_test_position2.y = los_start->y + los_unit_vector->y * los_test_distance;
				los_test_position2.z = los_start->z + los_unit_vector->z * los_test_distance;

				target = get_line_of_sight_collision_entity
				(
					source,
					NULL,
					&los_test_position1,
					&los_test_position2,
					&intercept_point,
					&face_normal
				);

				//
				// check if hit this_eo_target else must have hit something else
				//

				if (target)
				{
					if (target == this_eo_target->target)
					{
						eo_boresight_target = target;
					}

					break;
				}
			}
			else
			{
				break;
			}

			los_test_position1 = los_test_position2;

			this_eo_target = this_eo_target->succ;
		}
	}

	deinitialise_eo_target_list ();

	return (eo_boresight_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_eo_boresight_target (void)
{
	float
		range;

	entity
		*target,
		*first_pass_target,
		*second_pass_target;

	vec3d
		los_unit_vector,
		los_start,
		los_end;

	target = NULL;

	if (!eo_low_light)
	{
		//
		// first pass (eo boresight start -> eo boresight end)
		//

		los_start = eo_vp.position;

		los_end.x = los_start.x + eo_vp.zv.x * eo_max_visual_range;
		los_end.y = los_start.y + eo_vp.zv.y * eo_max_visual_range;
		los_end.z = los_start.z + eo_vp.zv.z * eo_max_visual_range;

		first_pass_target = get_eo_target (&los_start, &los_end, &eo_vp.zv, eo_max_visual_range, TRUE, NULL);

		//
		// second pass (eo boresight start -> first pass target)
		//

		if (first_pass_target)
		{
			get_local_entity_target_point (first_pass_target, &los_end);

			range = get_3d_range (&los_start, &los_end);

			if (range > 1.0)
			{
				los_unit_vector.x = los_end.x - los_start.x;
				los_unit_vector.y = los_end.y - los_start.y;
				los_unit_vector.z = los_end.z - los_start.z;

				normalise_3d_vector_given_magnitude (&los_unit_vector, range);

				second_pass_target = get_eo_target (&los_start, &los_end, &los_unit_vector, range, FALSE, first_pass_target);

				if (second_pass_target == first_pass_target)
				{
					target = first_pass_target;
				}
			}
		}
	}

	return (target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_eo (void)
{
	float
		flat_range;

	entity
		*current_target,
		*new_target;

	viewpoint
		vp;

	vec3d
		target_position,
		target_vector,
		offset_vector;

	matrix3x3
		m;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (eo_target_locked)
	{
		if (!current_target)
		{
			eo_target_locked = FALSE;
		}
	}

	get_eo_centred_viewpoint (&vp);

	//
	// track locked target
	//

	if (eo_target_locked)
	{
		get_local_entity_target_point (current_target, &target_position);

		target_vector.x = target_position.x - vp.position.x;
		target_vector.y = target_position.y - vp.position.y;
		target_vector.z = target_position.z - vp.position.z;

		multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &target_vector);

		eo_azimuth = atan2 (offset_vector.x, offset_vector.z);

		flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));

		eo_elevation = atan2 (offset_vector.y, flat_range);

		if (eo_azimuth < eo_min_azimuth)
		{
			eo_azimuth = eo_min_azimuth;

			eo_target_locked = FALSE;
		}
		else if (eo_azimuth > eo_max_azimuth)
		{
			eo_azimuth = eo_max_azimuth;

			eo_target_locked = FALSE;
		}

		if (eo_elevation < eo_min_elevation)
		{
			eo_elevation = eo_min_elevation;

			eo_target_locked = FALSE;
		}
		else if (eo_elevation > eo_max_elevation)
		{
			eo_elevation = eo_max_elevation;

			eo_target_locked = FALSE;
		}
	}

	eo_vp.position = vp.position;

	get_3d_transformation_matrix (m, eo_azimuth, eo_elevation, 0.0);

	multiply_matrix3x3_matrix3x3 (eo_vp.attitude, m, vp.attitude);

	//
	// update target
	//

	update_eo_visibility ();

	new_target = get_eo_boresight_target ();

	if (eo_target_locked)
	{
		if (new_target != current_target)
		{
			eo_target_locked = FALSE;
		}
	}

	if (new_target)
	{
		if (get_local_entity_parent (new_target, LIST_TYPE_GUNSHIP_TARGET) == NULL)
		{
			insert_local_entity_into_parents_child_list (new_target, LIST_TYPE_GUNSHIP_TARGET, get_gunship_entity (), NULL);
		}
	}

	set_gunship_target (new_target);

	target_locked = eo_target_locked;

	//
	// flag eo on target for "CP/G IDENTIFYING..." message
	//

	eo_on_target = new_target != NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_common_eo (void)
{
	eo_target_locked = target_locked;

	eo_sensor = target_acquisition_system;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_common_eo (void)
{
	eo_target_locked = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void slave_common_eo_to_current_target (void)
{
	float
		flat_range,
		aiming_eo_azimuth,
		aiming_eo_elevation,
		delta_eo_azimuth,
		delta_eo_elevation,
		frame_delta_eo_azimuth,
		frame_delta_eo_elevation,
		frame_slew_rate;

	entity
		*current_target;

	viewpoint
		vp;

	vec3d
		target_position,
		target_vector,
		offset_vector;

	matrix3x3
		m;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	get_eo_centred_viewpoint (&vp);

	if (current_target)
	{
		get_local_entity_target_point (current_target, &target_position);

		target_vector.x = target_position.x - vp.position.x;
		target_vector.y = target_position.y - vp.position.y;
		target_vector.z = target_position.z - vp.position.z;

		multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &target_vector);

		aiming_eo_azimuth = atan2 (offset_vector.x, offset_vector.z);

		aiming_eo_azimuth = bound (aiming_eo_azimuth, eo_min_azimuth, eo_max_azimuth);

		flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));

		aiming_eo_elevation = atan2 (offset_vector.y, flat_range);

		aiming_eo_elevation = bound (aiming_eo_elevation, eo_min_elevation, eo_max_elevation);
	}
	else
	{
		aiming_eo_azimuth = rad (0.0);

		aiming_eo_elevation = rad (0.0);
	}

	frame_slew_rate = rad (45.0) * get_delta_time ();

	delta_eo_azimuth = aiming_eo_azimuth - eo_azimuth;

	frame_delta_eo_azimuth = bound (delta_eo_azimuth, -frame_slew_rate, frame_slew_rate);

	eo_azimuth += frame_delta_eo_azimuth;

	delta_eo_elevation = aiming_eo_elevation - eo_elevation;

	frame_delta_eo_elevation = bound (delta_eo_elevation, -frame_slew_rate, frame_slew_rate);

	eo_elevation += frame_delta_eo_elevation;

	eo_vp.position = vp.position;

	get_3d_transformation_matrix (m, eo_azimuth, eo_elevation, 0.0);

	multiply_matrix3x3_matrix3x3 (eo_vp.attitude, m, vp.attitude);

	//
	// flag eo on target for "CP/G IDENTIFYING..." message
	//

	eo_on_target = FALSE;

	update_eo_visibility ();

	if (current_target)
	{
		if (!eo_low_light)
		{
			if
			(
				(delta_eo_azimuth >= rad (-5.0)) &&
				(delta_eo_azimuth <= rad (5.0)) &&
				(delta_eo_elevation >= rad (-5.0)) &&
				(delta_eo_elevation <= rad (5.0))
			)
			{
				eo_on_target = TRUE;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_selectable_eo_target (entity *target)
{
	entity
		*source,
		*boresight_target;

	vec3d
		*source_position,
		target_position,
		target_vector,
		offset_vector;

	float
		target_range,
		flat_range,
		azimuth,
		elevation;

	viewpoint
		vp,
		temp_eo_vp;

	matrix3x3
		m;

	ASSERT (target);

	//
	// check alive (gunship targets may be dead)
	//

	if (!get_local_entity_int_value (target, INT_TYPE_ALIVE))
	{
		return (FALSE);
	}

	//
	// check range
	//

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	get_local_entity_target_point (target, &target_position);

	target_range = get_3d_range (source_position, &target_position);

	if (target_range > eo_max_visual_range)
	{
		return (FALSE);
	}

	//
	// check azimuth and elevation
	//

	get_eo_centred_viewpoint (&vp);

	target_vector.x = target_position.x - vp.position.x;
	target_vector.y = target_position.y - vp.position.y;
	target_vector.z = target_position.z - vp.position.z;

	multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &target_vector);

	azimuth = atan2 (offset_vector.x, offset_vector.z);

	if (azimuth < eo_min_azimuth)
	{
		return (FALSE);
	}

	if (azimuth > eo_max_azimuth)
	{
		return (FALSE);
	}

	flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));

	elevation = atan2 (offset_vector.y, flat_range);

	if (elevation < eo_min_elevation)
	{
		return (FALSE);
	}

	if (elevation > eo_max_elevation)
	{
		return (FALSE);
	}

	//
	// check line of sight
	//

	temp_eo_vp = eo_vp;

	eo_vp.position = vp.position;

	get_3d_transformation_matrix (m, azimuth, elevation, 0.0);

	multiply_matrix3x3_matrix3x3 (eo_vp.attitude, m, vp.attitude);

	boresight_target = get_eo_boresight_target ();

	eo_vp = temp_eo_vp;

	return (boresight_target == target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_eo_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	if (!eo_low_light)
	{
		current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET) == NULL))
		{
			//
			// no current target or current target has been removed from the gunship target list
			//

			target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (get_selectable_eo_target (target))
				{
					new_target = target;

					break;
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
		else
		{
			target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

			while (target != current_target)
			{
				if (get_selectable_eo_target (target))
				{
					new_target = target;

					break;
				}

				target = get_local_entity_child_succ_circular (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
	}

	set_gunship_target (new_target);

	eo_target_locked = new_target != NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_eo_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	if (!eo_low_light)
	{
		current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET) == NULL))
		{
			//
			// no current target or current target has been removed from the gunship target list
			//

			target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (get_selectable_eo_target (target))
				{
					new_target = target;

					break;
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
		else
		{
			target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

			while (target != current_target)
			{
				if (get_selectable_eo_target (target))
				{
					new_target = target;

					break;
				}

				target = get_local_entity_child_pred_circular (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
	}

	set_gunship_target (new_target);

	eo_target_locked = new_target != NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 030318 loke
// This function converts the zoom value from the linear value which is stored in the eo params struct
// to a value which looks better when used in the game (at low zoom levels we want higher response)

float convert_linear_view_value (eo_params_dynamic_move *eo)
{
	float position_rescale_value = 1 - (log (eo->min_zoom) / log (eo->max_zoom));

	float ret = pow (eo->max_zoom, 1 - (eo->zoom * position_rescale_value));

	if (ret < eo->max_zoom)
	{
		return eo->max_zoom;
	}
	else if (ret > eo->min_zoom)
	{
		return eo->min_zoom;
	}
	else
	{
		return ret;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// loke 030315
// this function takes an axis position and returns the value as a float

float make_panning_offset_from_axis (long state)
{
	int panning_deadzone_size = 100;

	long newstate;


	if (state == 0 || (state > 0 && state < panning_deadzone_size) || (state < 0 && state > -panning_deadzone_size))
	{
		return 0.0;
	}

	if (state > 0)
	{
		newstate = state - panning_deadzone_size;
	}
	else
	{
		newstate = state + panning_deadzone_size;
	}

	return newstate / (float)(10000 - panning_deadzone_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031107 Designated targets


void select_next_designated_eo_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	if (!eo_low_light)
	{
		current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
		{
			target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

			while (target)
			{
				if (get_selectable_eo_target (target))
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
				if (get_selectable_eo_target (target))
				{
					new_target = target;

					break;
				}

				target = get_local_entity_child_succ_circular (target, LIST_TYPE_DESIGNATED_TARGET);
			}
		}
	}

	set_gunship_target (new_target);

	eo_target_locked = new_target != NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_designated_eo_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	if (!eo_low_light)
	{
		current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
		{
			//
			// no current target or current target has been removed from the gunship target list
			//

			target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

			while (target)
			{
				if (get_selectable_eo_target (target))
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
				if (get_selectable_eo_target (target))
				{
					new_target = target;

					break;
				}

				target = get_local_entity_child_pred_circular (target, LIST_TYPE_DESIGNATED_TARGET);
			}
		}
	}

	set_gunship_target (new_target);

	eo_target_locked = new_target != NULL;
}


// Jabberwock 031107 ends