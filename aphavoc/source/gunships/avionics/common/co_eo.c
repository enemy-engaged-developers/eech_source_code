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

#define MAX_GUN_SHAKE_DEFLECTION  rad(0.1)

#define POINT_LOCK   0x01
#define TARGET_LOCK  0x02

#define NOT_TRACKING    -10000.0

#define FINE_TRACKING_RATE 5.0
#define MEDIUM_TRACKING_RATE 20.0
#define COARSE_TRACKING_RATE 100.0
#define JOYSTICK_TRACKING_RATE 40.0

#define CO_PILOT_SWEEP_SPEED  rad(90.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	eo_on_target,
	eo_low_light,
	eo_ground_stabilised;

target_acquisition_systems
	eo_sensor;

float
	eo_azimuth,
	eo_requested_azimuth,
	eo_min_azimuth,
	eo_max_azimuth,
	eo_elevation,
	eo_requested_elevation,
	eo_min_elevation,
	eo_max_elevation,
	eo_max_visual_range,
	fog_range,
	visible_range,
	fog_start,
	fog_end;

viewpoint
	eo_vp;

int
	draw_eo_boresight = FALSE,
	draw_eo_terrain_los_markers = FALSE;

static int
//	eo_target_locked = FALSE,
	lock_target = FALSE,
	lock_terrain = FALSE;

int eo_target_locked = FALSE;

static vec3d
	eo_tracking_point;

static float
	co_pilot_sweep_heading,
	time_until_next_co_pilot_sweep;

entity
	*next_cpg_target_report,
	*slave_target = NULL;

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

static int
	laser_active = FALSE,
	electrical_system_on = TRUE;

static void co_pilot_scan_for_eo_targets(void);
static void slew_eo(float elevation, float azimuth);

void update_eo_max_visual_range(void);
static int get_selectable_eo_target (entity *target);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_eo (void)
{
	laser_active = FALSE;

	eo_target_locked = 0;

	eo_on_target = FALSE;

	eo_low_light = FALSE;

	eo_requested_elevation = 0.0;
	eo_requested_azimuth = 0.0;

	electrical_system_on = !command_line_dynamics_engine_startup || get_local_entity_int_value(get_gunship_entity(), INT_TYPE_AIRBORNE_AIRCRAFT);

	eo_stop_tracking();

	lock_target = FALSE;
	lock_terrain = FALSE;

	slave_target = NULL;

	co_pilot_sweep_heading = -rad(90.0);
	time_until_next_co_pilot_sweep = 2.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_eo (void)
{
}

void copy_eo_zoom(eo_params_dynamic_move* from, eo_params_dynamic_move* to)
{
	to->zoom = from->zoom;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_using_eo_system(int include_hms)
{
	switch (target_acquisition_system)
	{
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_LLLTV:
	case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
	case TARGET_ACQUISITION_SYSTEM_DVO:
		return TRUE;
	case TARGET_ACQUISITION_SYSTEM_HMS:
	case TARGET_ACQUISITION_SYSTEM_HIDSS:
	case TARGET_ACQUISITION_SYSTEM_IHADSS:
		return include_hms;
	default:
		return FALSE;
	}
}

int eo_is_locked(void)
{
	return eo_target_locked != 0;
}

void toggle_eo_lock(void)
{
	slave_target = NULL;

	if (eo_target_locked & TARGET_LOCK)
	{
		// if we have a target lock this disables all locks
		lock_target = FALSE;
		lock_terrain = FALSE;
	}
	else if (eo_target_locked & POINT_LOCK)
	{
		// if we have point lock then try locking a target, or unlock terrain
		lock_target = TRUE;
		lock_terrain = FALSE;
	}
	else
	{
		// if we have no lock try to get one of any type
		lock_target = TRUE;
		lock_terrain = TRUE;
	}
}

void set_eo_lock(int locked)
{
	lock_target = locked;
	lock_terrain = locked;

	slave_target = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_triangulated_range(entity* target)
{
	vec3d *target_position, *ownship_position;
	entity* ownship = get_gunship_entity();

	if (!target)
		return 0.0;

	ASSERT(ownship);

	ownship_position = get_local_entity_vec3d_ptr(ownship, VEC3D_TYPE_POSITION);
	target_position = get_local_entity_vec3d_ptr(target, VEC3D_TYPE_POSITION);

	return get_triangulated_by_position_range(ownship_position, target_position);
}

float get_triangulated_by_position_range(vec3d *ownship_position, vec3d *target_position)
{
	ASSERT(ownship_position && target_position);
	if (ownship_position->y > target_position->y + 2.0)
	{
		float angle;
		float range_2d = get_2d_range(ownship_position, target_position);

		// angle to target
		angle = atan((ownship_position->y - target_position->y) / range_2d);

		// calculate range based on ground being at same altitude at target's position
		return bound((ownship_position->y - target_position->y) / sin(angle), 0.0, 9900.0);
	}
	else
		return -1.0;
}

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
		*new_,
		*succ,
		*pred;

	int
		insert;

	ASSERT (target_position);

	new_ = (eo_target *) malloc_fast_mem (sizeof (eo_target));

	new_->target = target;
	new_->sqr_range = sqr_range;
	new_->radius = radius;
	new_->target_position = *target_position;

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
			new_->succ = succ;
			new_->pred = pred;

			if (succ)
			{
				succ->pred = new_;
			}

			if (pred)
			{
				pred->succ = new_;
			}
			else
			{
				eo_target_root = new_;
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
		case GUNSHIP_TYPE_VIPER:
		{
			get_viper_eo_centred_viewpoint (vp);
			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			get_kiowa_eo_centred_viewpoint (vp);

			break;
		}
		////////////////////////////////////////

		////////////////////////////////////////
		// GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			get_default_eo_centred_viewpoint (vp);
			// get_apache_eo_centred_viewpoint (vp);
			// //debug_fatal ("Invalid gunship type = %d", get_global_gunship_type ());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_eo_boresight_terrain_los_clear_range (vec3d* position)
{
	float
		los_clear_range;

	vec3d
		step;

	//
	// small steps across near range
	//

	*position = eo_vp.position;

	los_clear_range = 0.0;

	step.x = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.x;
	step.y = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.y;
	step.z = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.z;

	while (los_clear_range < LARGE_TERRAIN_LOS_STEP)
	{
		los_clear_range += SMALL_TERRAIN_LOS_STEP;

		position->x += step.x;
		position->y += step.y;
		position->z += step.z;

		if (draw_eo_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_rotated_debug_3d_object
			(
				position,
				0.0,
				0.0,
				0.0,
				TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
				TERRAIN_LOS_MARKER_LIFETIME,
				TERRAIN_LOS_MARKER_SCALE
			);
		}

		if (point_below_ground (position))
		{
			return (los_clear_range);
		}
	}

	//
	// large steps across complete range
	//

	*position = eo_vp.position;

	los_clear_range = 0.0;

	step.x = LARGE_TERRAIN_LOS_STEP * eo_vp.zv.x;
	step.y = LARGE_TERRAIN_LOS_STEP * eo_vp.zv.y;
	step.z = LARGE_TERRAIN_LOS_STEP * eo_vp.zv.z;

	while (los_clear_range < eo_max_visual_range)
	{
		los_clear_range += LARGE_TERRAIN_LOS_STEP;

		position->x += step.x;
		position->y += step.y;
		position->z += step.z;

		if (draw_eo_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_rotated_debug_3d_object
			(
				position,
				0.0,
				0.0,
				0.0,
				TERRAIN_LOS_MARKER_LARGE_STEP_3D_OBJECT,
				TERRAIN_LOS_MARKER_LIFETIME,
				TERRAIN_LOS_MARKER_SCALE
			);
		}

		if (point_below_ground (position))
		{
			// refine range by backing up to last range and do smaller steps
			float max_range = los_clear_range;
			los_clear_range -= LARGE_TERRAIN_LOS_STEP;

			position->x -= step.x;
			position->y -= step.y;
			position->z -= step.z;

			step.x = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.x;
			step.y = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.y;
			step.z = SMALL_TERRAIN_LOS_STEP * eo_vp.zv.z;

			while (los_clear_range < max_range)
			{
				los_clear_range += SMALL_TERRAIN_LOS_STEP;

				position->x += step.x;
				position->y += step.y;
				position->z += step.z;

				if (draw_eo_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
				{
					create_rotated_debug_3d_object
					(
						position,
						0.0,
						0.0,
						0.0,
						TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
						TERRAIN_LOS_MARKER_LIFETIME,
						TERRAIN_LOS_MARKER_SCALE
					);
				}

				if (point_below_ground (position))
					return (los_clear_range);
			}

			return max_range;
		}
	}

	return (eo_max_visual_range);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_eo_boresight_tree_los_clear_range (vec3d *los_start, vec3d *los_end, vec3d* intercept_point)
{
	float
		los_clear_range;

	vec3d
		face_normal;

	ASSERT (intercept_point);
	ASSERT (los_start);
	ASSERT (los_end);

	if (get_line_of_sight_collision_tree (los_start, los_end, intercept_point, &face_normal, FALSE, TRUE))
	{
		los_clear_range = get_3d_range (los_start, intercept_point);
	}
	else
	{
		los_clear_range = eo_max_visual_range;
		intercept_point->x = 0.0;
		intercept_point->y = 0.0;
		intercept_point->z = 0.0;
	}

	return (los_clear_range);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_eo_los_intercept_point(vec3d* intercept_point)
{
	vec3d object_intercept_point, los_start, los_end;
	float terrain_clear = get_eo_boresight_terrain_los_clear_range(intercept_point);
	float object_range = 10000.0;

	los_start = eo_vp.position;

	los_end.x = los_start.x + eo_vp.zv.x * eo_max_visual_range;
	los_end.y = los_start.y + eo_vp.zv.y * eo_max_visual_range;
	los_end.z = los_start.z + eo_vp.zv.z * eo_max_visual_range;

	object_range = get_eo_boresight_tree_los_clear_range (&los_start, &los_end, &object_intercept_point);

	if (object_range < terrain_clear)  // some object blocks line of sigth before terrain
	{
		*intercept_point = object_intercept_point;
		return object_range;
	}
	else
		return terrain_clear;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_eo_visibility (void)
{
	vec3d
		*position;

	// start full_eo_range by GCsDriver  08-12-2007
//	if (command_line_eo_full_range)
	{
		entity
			*current_target;

		update_eo_max_visual_range();

		current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);
		if (current_target)
		{
			if (!get_selectable_eo_target(current_target))
			{
				eo_target_locked = FALSE;
			}
		}
	}
	// end full_eo_range by GCsDriver  08-12-2007

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
			vec3d intercept_point;

			terrain_los_range = get_eo_boresight_terrain_los_clear_range (&intercept_point);

			tree_los_range = get_eo_boresight_tree_los_clear_range (los_start, los_end, &intercept_point);

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

//	if (!eo_low_light)
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
		adjusted_elevation,
		adjusted_azimuth,
		flat_range;

	entity
		*current_target,
		*new__target;

	viewpoint
		vp;

	vec3d
		target_position,
		target_vector,
		offset_vector;

	matrix3x3
		m;

	if (get_time_acceleration() == TIME_ACCELERATION_PAUSE)
		return;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (slave_target)
	{
		if (get_local_entity_int_value (slave_target, INT_TYPE_TARGET_TYPE) == TARGET_TYPE_INVALID)
			slave_target = NULL;

		else
		{
			slave_common_eo_to_current_target();

			if (get_eo_boresight_target() != slave_target)
				return;   // not done slewing to target yet

			slave_target = NULL;
			lock_target = TRUE;
		}
	}
	else if (eo_target_locked & TARGET_LOCK)
	{
		if (!current_target)
			eo_target_locked = 0;
	}

	get_eo_centred_viewpoint (&vp);

	//
	// track locked target or point
	//

	if (eo_target_locked)
	{
		float req_azimuth, req_elevation, delta_eo_azimuth, delta_eo_elevation, frame_delta_eo_azimuth, frame_delta_eo_elevation;
		float frame_slew_rate = rad(60) * get_delta_time();

		if (eo_target_locked & TARGET_LOCK)
		{
			get_local_entity_target_point (current_target, &target_position);

			target_vector.x = target_position.x - vp.position.x;
			target_vector.y = target_position.y - vp.position.y;
			target_vector.z = target_position.z - vp.position.z;
		}
		else
		{
			target_vector = eo_tracking_point;

			target_vector.x -= vp.position.x;
			target_vector.y -= vp.position.y;
			target_vector.z -= vp.position.z;
		}

		multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &target_vector);

		flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));
		req_elevation = atan2(offset_vector.y, flat_range);
		req_azimuth = atan2(offset_vector.x, offset_vector.z);

		delta_eo_azimuth = req_azimuth - eo_azimuth;
		frame_delta_eo_azimuth = bound (delta_eo_azimuth, -frame_slew_rate, frame_slew_rate);
		eo_azimuth += frame_delta_eo_azimuth;

		delta_eo_elevation = req_elevation - eo_elevation;
		frame_delta_eo_elevation = bound (delta_eo_elevation, -frame_slew_rate, frame_slew_rate);
		eo_elevation += frame_delta_eo_elevation;

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

	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DVO)
		new__target = NULL;
	else
		new__target = get_eo_boresight_target ();

	if (eo_target_locked & TARGET_LOCK)
	{
		if (new__target != current_target)
			eo_target_locked = 0;
	}

	// update target lock
	if (new__target)
	{
		if (get_local_entity_parent (new__target, LIST_TYPE_GUNSHIP_TARGET) == NULL)
			insert_local_entity_into_parents_child_list (new__target, LIST_TYPE_GUNSHIP_TARGET, get_gunship_entity (), NULL);

		if (lock_target)
		{
			eo_target_locked = TARGET_LOCK;
			lock_terrain = FALSE;
		}
		else
			eo_target_locked &= ~TARGET_LOCK;
	}

	// update point lock
	if (lock_terrain)
	{
		if (!eo_is_tracking_point())
		{
			// try locking onto point on ground
			eo_max_visual_range = fog_range;

			if (get_eo_los_intercept_point(&eo_tracking_point) < eo_max_visual_range)
				eo_target_locked = POINT_LOCK;
			else
				eo_stop_tracking();

			eo_max_visual_range = visible_range;

			// have to update server's tracking point so that missiles will aim in multiplayer
			set_client_server_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_EO_TRACKING_POINT, &eo_tracking_point);
		}
	}
	else
		eo_stop_tracking();

	// update the requested lock status
	lock_target = (eo_target_locked & TARGET_LOCK) != 0;
	lock_terrain = (eo_target_locked & POINT_LOCK) != 0;

	set_gunship_target (new__target);

	target_locked = eo_target_locked;

	if (!command_line_manual_laser_radar)
		set_laser_is_active(target_locked != 0 || new__target);

	//
	// flag eo on target for "CP/G IDENTIFYING..." message
	//

	eo_on_target = new__target != NULL;

	// apply camera shake
	// do this after check for boresight, otherwise the shaking will make it
	// lose lock on target
	if (gun_is_firing)
	{
		adjusted_elevation = eo_elevation + sfrand1norm() * MAX_GUN_SHAKE_DEFLECTION;
		adjusted_azimuth = eo_azimuth + sfrand1norm() * 0.5 * MAX_GUN_SHAKE_DEFLECTION;
	}
	else
	{
		adjusted_elevation = eo_elevation;
		adjusted_azimuth = eo_azimuth;
	}

	eo_vp.position = vp.position;
	get_3d_transformation_matrix (m, adjusted_azimuth, adjusted_elevation, 0.0);
	multiply_matrix3x3_matrix3x3 (eo_vp.attitude, m, vp.attitude);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_common_eo (void)
{
	eo_target_locked = target_locked;

	eo_sensor = target_acquisition_system;

	// start full_eo_range by GCsDriver  08-12-2007
//	if (command_line_eo_full_range)
	{
		update_eo_max_visual_range();
	}
	// end full_eo_range by GCsDriver  08-12-2007
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_common_eo (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void slew_eo_to_direction(float elevation, float azimuth)
{
	eo_requested_azimuth = azimuth;
	eo_requested_elevation = elevation;
}

static void slew_eo(float elevation, float azimuth)
{
	float
		adjusted_elevation,
		adjusted_azimuth,
		 delta_eo_azimuth,
		 frame_delta_eo_azimuth,
		 delta_eo_elevation,
		 frame_delta_eo_elevation;


	float frame_slew_rate = rad (60.0) * get_delta_time ();

	viewpoint
		vp;

	matrix3x3
		m;

	get_eo_centred_viewpoint (&vp);

	delta_eo_azimuth = azimuth - eo_azimuth;
	frame_delta_eo_azimuth = bound (delta_eo_azimuth, -frame_slew_rate, frame_slew_rate);
	eo_azimuth += frame_delta_eo_azimuth;

	delta_eo_elevation = elevation - eo_elevation;
	frame_delta_eo_elevation = bound (delta_eo_elevation, -frame_slew_rate, frame_slew_rate);
	eo_elevation += frame_delta_eo_elevation;

	// apply camera shake
	if (gun_is_firing)
	{
		adjusted_elevation = eo_elevation + sfrand1norm() * MAX_GUN_SHAKE_DEFLECTION;
		adjusted_azimuth = eo_azimuth + sfrand1norm() * 0.5 * MAX_GUN_SHAKE_DEFLECTION;
	}
	else
	{
		adjusted_elevation = eo_elevation;
		adjusted_azimuth = eo_azimuth;
	}

	eo_vp.position = vp.position;

	get_3d_transformation_matrix (m, adjusted_azimuth, adjusted_elevation, 0.0);
	multiply_matrix3x3_matrix3x3 (eo_vp.attitude, m, vp.attitude);

	eo_on_target = FALSE;

	if (/*!eo_low_light && */get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET))
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

void slave_common_eo_to_current_target (void)
{
	vec3d position;
	entity* current_target;

	if (slave_target)
		current_target = slave_target;
	else
		current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target)
	{
		get_local_entity_target_point (current_target, &position);
		slave_common_eo_to_position (&position);
	}
	else
		slave_common_eo_to_position (NULL);
}


void slave_common_eo_to_position (vec3d* target_position)
{
	float
		flat_range,
		aiming_eo_azimuth,
		aiming_eo_elevation;

	viewpoint
		vp;

	vec3d
		target_vector,
		offset_vector;

	int
		target_in_fov = FALSE;

	get_eo_centred_viewpoint (&vp);

	if (target_position)
	{
		target_vector.x = target_position->x - vp.position.x;
		target_vector.y = target_position->y - vp.position.y;
		target_vector.z = target_position->z - vp.position.z;

		multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &target_vector);

		aiming_eo_azimuth = atan2 (offset_vector.x, offset_vector.z);

		if (aiming_eo_azimuth < eo_min_azimuth || aiming_eo_azimuth > eo_max_azimuth)
			aiming_eo_azimuth = bound (aiming_eo_azimuth, eo_min_azimuth, eo_max_azimuth);
		else
			target_in_fov = TRUE;

		flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));

		aiming_eo_elevation = atan2 (offset_vector.y, flat_range);

		if (aiming_eo_elevation < eo_min_azimuth || aiming_eo_elevation > eo_max_azimuth)
		{
			aiming_eo_elevation = bound (aiming_eo_elevation, eo_min_elevation, eo_max_elevation);
			target_in_fov = FALSE;
		}
	}
	else
	{
		aiming_eo_azimuth = eo_requested_azimuth;

		aiming_eo_elevation = eo_requested_elevation;
	}


	slew_eo(aiming_eo_elevation, aiming_eo_azimuth);

	//
	// flag eo on target for "CP/G IDENTIFYING..." message
	//

	update_eo_visibility ();

	if (target_in_fov &&
		(eo_on_target || !is_using_eo_system(FALSE)))
	{
		if (!command_line_manual_laser_radar)
			set_laser_is_active(TRUE);
	}
	else
		set_laser_is_active(FALSE);
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
		*new__target,
		*current_target;

	new__target = NULL;

//	if (!eo_low_light)
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
					new__target = target;

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
					new__target = target;

					break;
				}

				target = get_local_entity_child_succ_circular (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
	}

	set_eo_slave_target(new__target);

	if(new__target)
		cpg_report_next_prev_target(new__target); //ataribaby 4/1/2009 added CPG next/prev target lock and ID
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_eo_target (void)
{
	entity
		*target,
		*new__target,
		*current_target;

	new__target = NULL;

//	if (!eo_low_light)
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
					new__target = target;

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
					new__target = target;

					break;
				}

				target = get_local_entity_child_pred_circular (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
	}

	set_eo_slave_target(new__target);

  if(new__target)
  {
    cpg_report_next_prev_target(new__target); //ataribaby 4/1/2009 added CPG next/prev target lock and ID
  }
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
	int panning_deadzone_size = 0;
	long new_state;

	if (state == 0 || (state > 0 && state < panning_deadzone_size) || (state < 0 && state > -panning_deadzone_size))
	{
		return 0.0;
	}

	if (state > 0)
	{
		new_state = state - panning_deadzone_size;
	}
	else
	{
		new_state = state + panning_deadzone_size;
	}

	return new_state / (float)(10000 - panning_deadzone_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031107 Designated targets


void select_next_designated_eo_target (void)
{
	entity
		*target,
		*new__target,
		*current_target;

	new__target = NULL;

//	if (!eo_low_light)
	{
		current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
		{
			target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

			while (target)
			{
				if (get_selectable_eo_target (target))
				{
					new__target = target;

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
					new__target = target;

					break;
				}

				target = get_local_entity_child_succ_circular (target, LIST_TYPE_DESIGNATED_TARGET);
			}
		}
	}

	set_eo_slave_target(new__target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_designated_eo_target (void)
{
	entity
		*target,
		*new__target,
		*current_target;

	new__target = NULL;

//	if (!eo_low_light)
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
					new__target = target;

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
					new__target = target;

					break;
				}

				target = get_local_entity_child_pred_circular (target, LIST_TYPE_DESIGNATED_TARGET);
			}
		}
	}

	set_eo_slave_target(new__target);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031107 ends

int laser_is_active(void)
{
	return laser_active;
}

void set_laser_is_active(int is_active)
{
	laser_active = is_active;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int electrical_system_active(void)
{
	return electrical_system_on;
}

void set_electrical_system_active(int active)
{
	electrical_system_on = active;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int eo_is_tracking_point(void)
{
	return eo_tracking_point.y != NOT_TRACKING;
}

vec3d* get_eo_tracking_point(void)
{
	if (eo_tracking_point.y == NOT_TRACKING)
		return NULL;

	return &eo_tracking_point;
}

void eo_stop_tracking(void)
{
	eo_tracking_point.x = 0.0;
	eo_tracking_point.y = NOT_TRACKING;
	eo_tracking_point.z = 0.0;

	set_client_server_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_EO_TRACKING_POINT, &eo_tracking_point);

	eo_target_locked &= ~POINT_LOCK;
}

void eo_start_tracking(vec3d* tracking_point)
{
	eo_target_locked = POINT_LOCK;
	lock_terrain = TRUE;

	eo_tracking_point = *tracking_point;
	set_client_server_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_EO_TRACKING_POINT, &eo_tracking_point);
}

int eo_tracking_point_valid(vec3d* tracking_point)
{
	return tracking_point && (tracking_point->y != NOT_TRACKING);
}

static void switch_to_point_lock(void)
{
	// get pointer to tracking point so we can set it
	entity* target = get_local_entity_parent(get_gunship_entity(), LIST_TYPE_TARGET);

	lock_target = FALSE;

	eo_max_visual_range = fog_range;

	if (target && !get_local_entity_int_value(target, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		// get position of target
		get_local_entity_vec3d(target, VEC3D_TYPE_POSITION, &eo_tracking_point);
		set_client_server_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_EO_TRACKING_POINT, &eo_tracking_point);

		eo_target_locked = POINT_LOCK;
		lock_terrain = TRUE;
	}
	// try locking onto point on ground
	else if (get_eo_los_intercept_point(&eo_tracking_point) < eo_max_visual_range)
	{
		eo_target_locked = POINT_LOCK;
		lock_terrain = TRUE;
	}
	else  // unsuccessful, lose lock
	{
		eo_target_locked = 0;
		eo_stop_tracking();
	}
	
	eo_max_visual_range = visible_range;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_range_to_target(void)
{
	rangefinding_system rangefinder = get_range_finder();
	entity* target = get_local_entity_parent(get_gunship_entity(), LIST_TYPE_TARGET);

	if (target || eo_is_tracking_point())
	{
		vec3d* source_position = get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION);
		vec3d* target_position;

		if (target)
			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
		else
			target_position = get_eo_tracking_point();

		if (rangefinder != RANGEFINDER_TRIANGULATION)
			return get_3d_range (source_position, target_position);
		else
			return get_triangulated_by_position_range(source_position, target_position);
	}
	else
		return 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void keyboard_slew_eo_system(float fine_slew_rate, float medium_slew_rate, float coarse_slew_rate)
{
	if (eo_target_locked)
	{
		float
			movement_rate = 0.0,
			movement,
			eo_heading = get_heading_from_attitude_matrix (eo_vp.attitude),
			sin_heading = sin(eo_heading),
			cos_heading = cos(eo_heading),
			dx = 0.0, dy = 0.0;

		int
			has_moved;

		static int previous_mouse_update_flag = 1;

		if (command_line_mouse_look != MOUSELOOK_ON && command_line_eo_pan_joystick_index == -1 && previous_mouse_update_flag != get_mouse_update_flag())
		{
			dx = get_mouse_move_delta_x() / get_delta_time();
			dy = get_mouse_move_delta_y() / get_delta_time();

			previous_mouse_update_flag = get_mouse_update_flag();
		}
		
		// move tracking point perpendicular
		if (continuous_target_acquisition_system_steer_left_fast_key || dx < - 2500.0)
			movement_rate -= COARSE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_left_fine_key)
			movement_rate -= FINE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_left_key)
			movement_rate -= MEDIUM_TRACKING_RATE;

		////////////////////////////////////////

		if (continuous_target_acquisition_system_steer_right_fast_key || (dx > 2500.0))
			movement_rate += COARSE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_right_fine_key)
			movement_rate += FINE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_right_key)
			movement_rate += MEDIUM_TRACKING_RATE;

		has_moved = movement_rate != 0.0;

		if (has_moved)
		{
			// if moving while in target lock then switch to point lock
			if (eo_target_locked & TARGET_LOCK)
				switch_to_point_lock();

			movement = movement_rate * get_delta_time();

			eo_tracking_point.x += cos_heading * movement;
			eo_tracking_point.z -= sin_heading * movement;
			movement_rate = 0.0;
		}

		// move closer farther
		if (continuous_target_acquisition_system_steer_up_fast_key || dy < - 2500.0)
			movement_rate += COARSE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_up_fine_key)
			movement_rate += FINE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_up_key)
			movement_rate += MEDIUM_TRACKING_RATE;

		////////////////////////////////////////

		if (continuous_target_acquisition_system_steer_down_fast_key || dy > 2500.0)
			movement_rate -= COARSE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_down_fine_key)
			movement_rate -= FINE_TRACKING_RATE;
		else if (continuous_target_acquisition_system_steer_down_key)
			movement_rate -= MEDIUM_TRACKING_RATE;

		if (!has_moved && movement_rate != 0.0)
		{
			// if moving while in target lock then switch to point lock
			if (eo_target_locked & TARGET_LOCK)
				switch_to_point_lock();

			has_moved = TRUE;
		}

		movement = movement_rate * 4 * get_delta_time();  // multiply vertical rate by two since it appears much smaller from usual angles

		eo_tracking_point.x += sin_heading * movement;
		eo_tracking_point.z += cos_heading * movement;

		// keep point on ground (unless point off map)
		if (has_moved && point_inside_map_area (&eo_tracking_point))
		{
			helicopter *raw = (helicopter *) get_local_entity_data(get_gunship_entity());
			eo_tracking_point.y = get_3d_terrain_point_data(eo_tracking_point.x, eo_tracking_point.z, &raw->ac.terrain_info);

			// have to update server's tracking point so that missiles will aim in multiplayer
			set_client_server_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_EO_TRACKING_POINT, &eo_tracking_point);

			slave_target = NULL;
		}
	}
	else
	{
		if (continuous_target_acquisition_system_steer_left_fast_key)
		{
			eo_azimuth -= coarse_slew_rate;
			eo_azimuth = max (eo_azimuth, eo_min_azimuth);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_left_fine_key)
		{
			eo_azimuth -= fine_slew_rate;
			eo_azimuth = max (eo_azimuth, eo_min_azimuth);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_left_key)
		{
			eo_azimuth -= medium_slew_rate;
			eo_azimuth = max (eo_azimuth, eo_min_azimuth);
			slave_target = NULL;
		}

		////////////////////////////////////////

		if (continuous_target_acquisition_system_steer_right_fast_key)
		{
			eo_azimuth += coarse_slew_rate;
			eo_azimuth = min (eo_azimuth, eo_max_azimuth);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_right_fine_key)
		{
			eo_azimuth += fine_slew_rate;
			eo_azimuth = min (eo_azimuth, eo_max_azimuth);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_right_key)
		{
			eo_azimuth += medium_slew_rate;
			eo_azimuth = min (eo_azimuth, eo_max_azimuth);
			slave_target = NULL;
		}

		////////////////////////////////////////

		if (continuous_target_acquisition_system_steer_up_fast_key)
		{
			eo_elevation += coarse_slew_rate;
			eo_elevation = min (eo_elevation, eo_max_elevation);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_up_fine_key)
		{
			eo_elevation += fine_slew_rate;
			eo_elevation = min (eo_elevation, eo_max_elevation);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_up_key)
		{
			eo_elevation += medium_slew_rate;
			eo_elevation = min (eo_elevation, eo_max_elevation);
			slave_target = NULL;
		}

		////////////////////////////////////////

		if (continuous_target_acquisition_system_steer_down_fast_key)
		{
			eo_elevation -= coarse_slew_rate;
			eo_elevation = max (eo_elevation, eo_min_elevation);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_down_fine_key)
		{
			eo_elevation -= fine_slew_rate;
			eo_elevation = max (eo_elevation, eo_min_elevation);
			slave_target = NULL;
		}
		else if (continuous_target_acquisition_system_steer_down_key)
		{
			eo_elevation -= medium_slew_rate;
			eo_elevation = max (eo_elevation, eo_min_elevation);
			slave_target = NULL;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void joystick_slew_eo_system(float slew_rate)
{
	if (command_line_eo_pan_joystick_index != -1)
	{
		float
			panning_offset_horiz,
			panning_offset_vert;

		int
			horizontal_value,
			vertical_value;

		horizontal_value = get_joystick_axis (command_line_eo_pan_joystick_index, command_line_eo_pan_horizontal_joystick_axis);
		panning_offset_horiz = make_panning_offset_from_axis (horizontal_value);

		vertical_value = get_joystick_axis (command_line_eo_pan_joystick_index, command_line_eo_pan_vertical_joystick_axis);
		panning_offset_vert = make_panning_offset_from_axis (vertical_value);

		if (panning_offset_horiz != 0.0 || panning_offset_vert != 0.0)
		{
			slave_target = NULL;

			if (eo_target_locked)
			{
				float
					eo_heading = get_heading_from_attitude_matrix (eo_vp.attitude),
					sin_heading = sin(eo_heading),
					cos_heading = cos(eo_heading);

				// if moving while in target lock then switch to point lock
				if (eo_target_locked & TARGET_LOCK)
					switch_to_point_lock();

				eo_tracking_point.x += cos_heading * panning_offset_horiz * JOYSTICK_TRACKING_RATE * get_delta_time();
				eo_tracking_point.z -= sin_heading * panning_offset_horiz * FINE_TRACKING_RATE * get_delta_time();

				eo_tracking_point.x += sin_heading * panning_offset_vert * 4 * JOYSTICK_TRACKING_RATE * get_delta_time();
				eo_tracking_point.z += cos_heading * panning_offset_vert * 4 * JOYSTICK_TRACKING_RATE * get_delta_time();

				// keep point on ground (unless point off map)
				if (point_inside_map_area (&eo_tracking_point))
				{
					helicopter *raw = (helicopter *) get_local_entity_data(get_gunship_entity());
					eo_tracking_point.y = get_3d_terrain_point_data(eo_tracking_point.x, eo_tracking_point.z, &raw->ac.terrain_info);

					// have to update server's tracking point so that missiles will aim in multiplayer
					set_client_server_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_EO_TRACKING_POINT, &eo_tracking_point);
				}
			}
			else
			{
				eo_azimuth += panning_offset_horiz * slew_rate;
				eo_azimuth = bound(eo_azimuth, eo_min_azimuth, eo_max_azimuth);

				eo_elevation -= panning_offset_vert * slew_rate;
				eo_elevation = bound(eo_elevation, eo_min_elevation, eo_max_elevation);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_eo_azimuth (float rotate_rate, float coarse_slew_rate, float eo_azimuth, float eo_min_azimuth, float eo_max_azimuth, float mouse_slew_rate)
{
	 // POV flir control thealx 130215

	if (!eo_target_locked)
	{
		if (command_line_mouse_look == MOUSELOOK_ON)
		{
			if (joystick_pov_left)
			{
				eo_azimuth -= rotate_rate * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_azimuth = max (eo_azimuth, eo_min_azimuth);
			}
			else if (joystick_pov_right)
			{
				eo_azimuth += rotate_rate * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_azimuth = min (eo_azimuth, eo_max_azimuth);
			}
		}

	// Jabberwock 030930 - Mouse FLIR control functions
	// Improved mouse control thealx 130215

		else
		{
			static int previous_mouse_update_flag = 1;
			float dh;

			if (previous_mouse_update_flag != get_mouse_update_flag())
			{
				dh = get_mouse_move_delta_x() / 5000.0 * mouse_slew_rate * command_line_mouse_look_speed;

				previous_mouse_update_flag = get_mouse_update_flag();

				eo_azimuth += dh;
				eo_azimuth = bound (eo_azimuth, eo_min_azimuth, eo_max_azimuth);
			}
		}
	}
	
	return eo_azimuth;
}

float get_eo_elevation (float rotate_rate, float coarse_slew_rate, float eo_elevation, float eo_min_elevation, float eo_max_elevation, float mouse_slew_rate)
{
	 // POV flir control thealx 130215

	if (!eo_target_locked)
	{
		if (command_line_mouse_look == MOUSELOOK_ON)
		{
			if (joystick_pov_up)
			{
				eo_elevation += rotate_rate * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_elevation = min (eo_elevation, eo_max_elevation);
			}
			else if (joystick_pov_down)
			{
				eo_elevation -= rotate_rate * get_delta_time () * coarse_slew_rate * command_line_mouse_look_speed;

				eo_elevation = max (eo_elevation, eo_min_elevation);
			}
		}

	// Jabberwock 030930 - Mouse FLIR control functions
	// Improved mouse control thealx 130215

		else
		{
			static int previous_mouse_update_flag = 1;
			float dp;

			if (previous_mouse_update_flag != get_mouse_update_flag())
			{
				dp = get_mouse_move_delta_y() / 5000.0 * mouse_slew_rate * command_line_mouse_look_speed;

				previous_mouse_update_flag = get_mouse_update_flag();

				eo_elevation -= dp;
				eo_elevation = bound (eo_elevation, eo_min_elevation, eo_max_elevation);
			}
		}
	}

	return eo_elevation;
}

float get_new_eo_zoom (float zoom)
{
			if (mouse_wheel_down)
			{
				mouse_wheel_down--;
				if (zoom < 1.0)
					zoom += 0.1;
			}
			else if (mouse_wheel_up)
			{
				mouse_wheel_up--;
				if (zoom > 0.0)
					zoom -= 0.1;
			}

			return zoom;
}

float get_old_eo_zoom (float fov, float max_fov, float min_fov)
{

		// "Old EO" Zoom control by Joystick thealx 130215 

		if (command_line_eo_zoom_joystick_index != -1 && min_fov != max_fov)
		{
			int pos = get_joystick_axis (command_line_eo_zoom_joystick_index, command_line_eo_zoom_joystick_axis);

			if (pos < -5500)
			{
				fov = min_fov;
			}
			else if ((pos > -5500) && (pos < 5000))
			{
				fov = min_fov + 1;
			}
			else if (pos > 5000)
			{
				fov = max_fov;
			}
		}
		else if ((command_line_mouse_look != MOUSELOOK_ON) || (command_line_field_of_view_joystick_index != -1))
		{
			if (mouse_wheel_down)
			{
				mouse_wheel_down--;
					if (fov < max_fov)
						fov++;
			}
			else if (mouse_wheel_up)
			{
				mouse_wheel_up--;
					if (fov > min_fov)
						fov--;
			}
		}
			return fov;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// start full_eo_range by GCsDriver  08-12-2007
void update_eo_max_visual_range(void)
{
	//see 3d_init.c & 3dview.c
	//eo_max_visual_range = main_3d_env->fog_end;
	float amb_red, amb_green, amb_blue,
			sun_red, sun_green, sun_blue;

#ifndef OGRE_EE
	get_3d_fog_distances (main_3d_env, &fog_start, &fog_end);
	get_3d_ambient_light_level (&amb_red, &amb_green, &amb_blue);
	get_3d_main_light_level (&sun_red, &sun_green, &sun_blue);
#else
	// FIXME
	fog_start = 5000.0f; fog_end = 10000.0f;
	amb_red = amb_green = amb_blue = 1.0f;
	sun_red = sun_green = sun_blue = 1.0f;
#endif

	//eo_max_visual_range = fog_end;

	switch (eo_sensor)
	{
		case TARGET_ACQUISITION_SYSTEM_DTV:
		case TARGET_ACQUISITION_SYSTEM_DVO:
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		{
			if (eo_sensor == TARGET_ACQUISITION_SYSTEM_LLLTV || eo_sensor == TARGET_ACQUISITION_SYSTEM_DTV)
				fog_end = min(1.25f * fog_end, 10000.0f); // synch it with LLLTV fog value in 3d_init.c!!
			fog_range = fog_end - 500; // how far will be possible to lock ground point
			visible_range = fog_range * sqrt(bound((amb_red + amb_green + amb_blue + sun_red + sun_green + sun_blue) / 3, 0.0, 1.0)); // target recognition tange
			visible_range /= 1 + eo_low_light; // decrease recognition tange
			break;
		}
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			fog_range = 10000 / (1 + eo_low_light) - 500; // synch it with FLIR fog value in 3d_init.c!!
			visible_range = fog_range - 500; // lock on target up to full range
			break;
		}
		default:
		{
			debug_fatal ("Invalid eo sensor = %d", eo_sensor);
			break;
		}
	}
	
	eo_max_visual_range = visible_range;
	
//	debug_log("eo_max_visual_range %f, fog end %f, eo_low_light %i", eo_max_visual_range, fog_range, eo_low_light);
}
// end full_eo_range by GCsDriver  08-12-2007


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_eo_slave_target(entity* target)
{
	slave_target = target;

	set_gunship_target(NULL);
	eo_target_locked = 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float evaluate_target(entity* target, float sqr_range)
{
	if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
	{
		float
			rank = 0.0;

		entity_sub_types sub_type = get_local_entity_int_value (target, INT_TYPE_ENTITY_SUB_TYPE);

		switch (get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE))
		{
			case TARGET_TYPE_INVALID:
				return 0.0;

			case TARGET_TYPE_GROUND:
			{
				switch (target->type)
				{
				case ENTITY_TYPE_ANTI_AIRCRAFT:
				case ENTITY_TYPE_ROUTED_VEHICLE:
				case ENTITY_TYPE_SHIP_VEHICLE:
					rank = vehicle_database[sub_type].potential_surface_to_air_threat;
					break;
				default:
					return 0.0;
				}

				break;
			}
			case TARGET_TYPE_AIR:
			////////////////////////////////////////
			{
				if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT) && get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) > 5.0)
					rank = aircraft_database[sub_type].potential_air_to_air_threat;
				else
					return 0.0;

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid target type = %d", get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE));

				return 0.0;

				break;
			}
		}

		rank *= (5000 * 5000);
		rank /= sqr_range;

		rank *= frand1();

		return rank;
	}

	return 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void co_pilot_perform_eo_scan(void)
{
	static float
		best_target_rank = 0.0;

	static entity*
		best_target = NULL;

	int
		sweep_done = FALSE,
		x_sec,
		z_sec,
		x_sec_min,
		z_sec_min,
		x_sec_max,
		z_sec_max;

	float
		scan_range = 5000.0,
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
		sqr_scan_range;

	entity
		*source,
		*target,
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

	{
		entity_sides source_side = (entity_sides) get_local_entity_int_value(source, INT_TYPE_SIDE);

		heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);
		cw_sweep_start_offset = co_pilot_sweep_heading;
		co_pilot_sweep_heading += CO_PILOT_SWEEP_SPEED * get_delta_time();

		if (co_pilot_sweep_heading >= rad(90.0))  // this is last segment of sweep
		{
			sweep_done = TRUE;
			cw_sweep_end_offset = rad(90.0);
			co_pilot_sweep_heading = rad(-90.0);
		}
		else
			cw_sweep_end_offset = co_pilot_sweep_heading;

		cw_sweep_start_direction = heading + cw_sweep_start_offset;

		if (cw_sweep_start_direction > rad (180.0))
			cw_sweep_start_direction -= rad (360.0);
		else if (cw_sweep_start_direction < rad (-180.0))
			cw_sweep_start_direction += rad (360.0);

		cw_sweep_end_direction = heading + cw_sweep_end_offset;

		if (cw_sweep_end_direction > rad (180.0))
			cw_sweep_end_direction -= rad (360.0);
		else if (cw_sweep_end_direction < rad (-180.0))
			cw_sweep_end_direction += rad (360.0);

		////////////////////////////////////////
		//
		// get sector scan area
		//
		////////////////////////////////////////

		cw_sweep_start_position.x = source_position->x + (sin (cw_sweep_start_direction) * scan_range);
		cw_sweep_start_position.y = source_position->y;
		cw_sweep_start_position.z = source_position->z + (cos (cw_sweep_start_direction) * scan_range);

		cw_sweep_end_position.x = source_position->x + (sin (cw_sweep_end_direction) * scan_range);
		cw_sweep_end_position.y = source_position->y;
		cw_sweep_end_position.z = source_position->z + (cos (cw_sweep_end_direction) * scan_range);

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

		// reduce scan range in bad visibility
		if (get_simple_session_weather_at_point (source_position) == WEATHERMODE_HEAVY_RAIN)
			scan_range -= 1500.0;
		if (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE) == DAY_SEGMENT_TYPE_NIGHT)
			scan_range -= 1500.0;

		sqr_scan_range = scan_range * scan_range;

		for (z_sec = z_sec_min; z_sec <= z_sec_max; z_sec++)
		{
			for (x_sec = x_sec_min; x_sec <= x_sec_max; x_sec++)
			{
				sector = get_local_raw_sector_entity (x_sec, z_sec);

				target = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

				while (target)
				{
					if (get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID)
					{
						if (!get_local_entity_parent (target, LIST_TYPE_GUNSHIP_TARGET))
						{
							////////////////////////////////////////
							//
							// target not on target list
							//
							////////////////////////////////////////

							if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
							{
								float sqr_target_range;

								target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
								sqr_target_range = get_sqr_3d_range (source_position, target_position);

								if (sqr_target_range <= sqr_scan_range)
								{
									dx = target_position->x - source_position->x;
									dz = target_position->z - source_position->z;

									bearing = atan2 (dx, dz);

									if (check_bearing_within_cw_sweep_segment (bearing, cw_sweep_start_direction, cw_sweep_end_direction))
									{
										float rank = evaluate_target(target, sqr_target_range);

										if (rank > best_target_rank && get_los_clear (target, source_position, target_position))
										{
											best_target_rank = rank;
											best_target = target;
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

		if (sweep_done)
		{
			next_cpg_target_report = best_target;

			if (best_target)  // if we found a target, wait the proper detection time before reporting it
			{
				float range;

				target_position = get_local_entity_vec3d_ptr (best_target, VEC3D_TYPE_POSITION);
				range = get_2d_range(source_position, target_position);

				time_until_next_co_pilot_sweep = 5.0 + frand1() * 0.005 * range;
			}

			best_target = NULL;
			best_target_rank = 0.0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cpg_scan_for_eo_targets(void)
{
	if (!global_co_pilot_scans_for_targets)
		return;

	// wait until timeout
	if (time_until_next_co_pilot_sweep > 0.0)
		time_until_next_co_pilot_sweep -= get_delta_time();
	else
	{
		// enough time has passed to detect this target
		if (next_cpg_target_report)
		{
			entity*
				source = get_gunship_entity();

			vec3d
				*source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION),
				*target_position = get_local_entity_vec3d_ptr (next_cpg_target_report, VEC3D_TYPE_POSITION);

			// report target, and add to target list.  Have to retest conditions, since they may have changed since we selected it
			if (get_local_entity_int_value (next_cpg_target_report, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID
				&& !get_local_entity_parent (next_cpg_target_report, LIST_TYPE_GUNSHIP_TARGET)
				&& get_los_clear(next_cpg_target_report, source_position, target_position))
			{
				insert_local_entity_into_parents_child_list (next_cpg_target_report, LIST_TYPE_GUNSHIP_TARGET, source, NULL);
				cpg_report_target(next_cpg_target_report);
			}

			next_cpg_target_report = NULL;
		}

		// find more targets to report
		co_pilot_perform_eo_scan();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void get_eo_azimuth_and_elevation(float* az, float* el)
{
	*az = eo_azimuth;
	*el = eo_elevation;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ataribaby 4/1/2009 added CPG next/prev target lock and ID
void cpg_report_identified_target(entity* target)
{
	if (get_gunship_entity() && target)
	{
		if (get_local_entity_int_value(target, INT_TYPE_CPG_IDENTIFIED))
		{
			int allied = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SIDE) == get_local_entity_int_value (target, INT_TYPE_SIDE);

			if (allied)
				play_client_server_cpg_message(get_gunship_entity (), 1.0, 30.0, SPEECH_CATEGORY_CPG_SYSTEMS, 0.0, SPEECH_CPG_FRIENDLY);
			else
				play_client_server_cpg_message(get_gunship_entity (), 1.0, 30.0, SPEECH_CATEGORY_CPG_SYSTEMS, 0.0,	SPEECH_CPG_ENEMY);
		}
	}
}

//ataribaby 4/1/2009 added CPG next/prev target lock and ID
void cpg_report_next_prev_target(entity* target)
{
	if (get_gunship_entity() && target)
	{
		int allied = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SIDE) == get_local_entity_int_value (target, INT_TYPE_SIDE);

		if (!get_local_entity_int_value(target, INT_TYPE_CPG_IDENTIFIED))
		{
			play_client_server_cpg_message(get_gunship_entity (), 1.0, 30.0, SPEECH_CATEGORY_CPG_SYSTEMS, 0.0,
					SPEECH_CPG_SPOT_ON);
		}
		else if (allied)
		{
			play_client_server_cpg_message(get_gunship_entity (), 1.0, 30.0, SPEECH_CATEGORY_CPG_SYSTEMS, 0.0,
					SPEECH_CPG_FRIENDLY);
		}
		else if (!allied)
		{
			play_client_server_cpg_message(get_gunship_entity (), 1.0, 30.0, SPEECH_CATEGORY_CPG_SYSTEMS, 0.0,
					SPEECH_CPG_ENEMY);
		}
	}
}
