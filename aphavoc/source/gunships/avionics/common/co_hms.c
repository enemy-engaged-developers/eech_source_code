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

#define TERRAIN_LOS_MARKER_SCALE						(0.5)

#define TERRAIN_LOS_MARKER_LIFETIME					(0.0)

#define TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_WHITE)

#define TERRAIN_LOS_MARKER_LARGE_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_RED)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	hms_target_locked;

float
	hms_max_visual_range,
	hms_max_field_of_view;

int
	draw_hms_field_of_view = FALSE,
	draw_hms_terrain_los_markers = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	numpad_events_overlaid;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct HMS_TARGET
{
	entity
		*target;

	float
		cos_angular_error;

	vec3d
		target_position;

	int
		locked;

	struct HMS_TARGET
		*succ,
		*pred;
};

typedef struct HMS_TARGET hms_target;

static hms_target
	*hms_target_root;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_hms (void)
{
	hms_target_locked = FALSE;

	numpad_events_overlaid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_hms (void)
{
	if (numpad_events_overlaid)
	{
		pop_numpad_cockpit_view_events_overlay ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_hms_target_list (void)
{
	hms_target_root = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deinitialise_hms_target_list (void)
{
	hms_target
		*this_hms_target,
		*succ;

	this_hms_target = hms_target_root;

	while (this_hms_target)
	{
		succ = this_hms_target->succ;

		free_mem (this_hms_target);

		this_hms_target = succ;
	}

	hms_target_root = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void insert_entity_into_hms_target_list (entity *target, entity *locked_target, float cos_angular_error, vec3d *target_position)
{
	hms_target
		*new_,
		*succ,
		*pred;

	int
		insert;

	ASSERT (target_position);

	new_ = (hms_target *) malloc_fast_mem (sizeof (hms_target));

	new_->target = target;
	new_->cos_angular_error = cos_angular_error;
	new_->target_position = *target_position;
	new_->locked = FALSE;

	//
	// sort list in descending order of cos_angular_error
	//

	succ = hms_target_root;
	pred = NULL;

	while (TRUE)
	{
		//
		// force the locked target to start of list so that it gets checked first
		//

		if (target == locked_target)
		{
			new_->locked = TRUE;

			insert = TRUE;
		}
		else if (succ)
		{
			//
			// force skip over locked target
			//

			if (succ->locked)
			{
				insert = FALSE;
			}
			else
			{
				insert = cos_angular_error > succ->cos_angular_error;
			}
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
				hms_target_root = new_;
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

			if (draw_hms_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
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

			if (draw_hms_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
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

			if (draw_hms_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
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

			if (draw_hms_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
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

static int get_hms_valid (void)
{
	if (get_global_avionics_realism_level () > AVIONICS_REALISM_LEVEL_SIMPLE)
	{
		if (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE) == DAY_SEGMENT_TYPE_NIGHT)
		{
			if (!night_vision_system_active)
			{
				return (FALSE);
			}
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_hms_boresight_target (void)
{
	int
		x_sector_min,
		z_sector_min,
		x_sector_max,
		z_sector_max,
		x_sector,
		z_sector;

	float
		cos_hms_max_field_of_view,
		hms_max_visual_sqr_range,
		target_sqr_range,
		heading,
		x_min,
		z_min,
		x_max,
		z_max,
		target_cos_angular_error;

	vec3d
		lh_extent_position,
		rh_extent_position,
		target_position,
		uvec_target,
		intercept_point,
		face_normal;

	entity
		*source,
		*target,
		*locked_target,
		*this_sector,
		*hms_boresight_target;

	hms_target
		*this_hms_target;

	ASSERT (hms_max_visual_range > 0.0);

	ASSERT ((hms_max_field_of_view > rad (0.0)) && (hms_max_field_of_view <= rad (90.0)));

	hms_boresight_target = NULL;

	if (get_hms_valid ())
	{
		source = get_gunship_entity ();

		cos_hms_max_field_of_view = cos (hms_max_field_of_view);

		hms_max_visual_sqr_range = hms_max_visual_range * hms_max_visual_range;

		if (hms_target_locked)
		{
			locked_target = get_local_entity_parent (source, LIST_TYPE_TARGET);
		}
		else
		{
			locked_target = NULL;
		}

		////////////////////////////////////////
		//
		// calc sector scan
		//
		////////////////////////////////////////

		//
		// (this scan should really check a pyramid but it is ok for horizontal flight)
		//

		lh_extent_position = pilot_head_vp.position;
		rh_extent_position = pilot_head_vp.position;

		heading = get_heading_from_attitude_matrix (pilot_head_vp.attitude);

		lh_extent_position.x += sin (heading - hms_max_field_of_view) * hms_max_visual_range;
		lh_extent_position.z += cos (heading - hms_max_field_of_view) * hms_max_visual_range;

		rh_extent_position.x += sin (heading + hms_max_field_of_view) * hms_max_visual_range;
		rh_extent_position.z += cos (heading + hms_max_field_of_view) * hms_max_visual_range;

		if (draw_hms_field_of_view && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_debug_3d_line (&pilot_head_vp.position, &lh_extent_position, sys_col_green, 0.0);
			create_debug_3d_line (&pilot_head_vp.position, &rh_extent_position, sys_col_red, 0.0);
		}

		//
		// sector scan min
		//

		x_min = min (min (lh_extent_position.x, rh_extent_position.x), pilot_head_vp.position.x);
		z_min = min (min (lh_extent_position.z, rh_extent_position.z), pilot_head_vp.position.z);

		get_x_sector (x_sector_min, x_min);
		get_z_sector (z_sector_min, z_min);

		x_sector_min = max (x_sector_min, MIN_MAP_X_SECTOR);
		z_sector_min = max (z_sector_min, MIN_MAP_Z_SECTOR);

		//
		// sector scan max
		//

		x_max = max (max (lh_extent_position.x, rh_extent_position.x), pilot_head_vp.position.x);
		z_max = max (max (lh_extent_position.z, rh_extent_position.z), pilot_head_vp.position.z);

		get_x_sector (x_sector_max, x_max);
		get_z_sector (z_sector_max, z_max);

		x_sector_max = min (x_sector_max, MAX_MAP_X_SECTOR);
		z_sector_max = min (z_sector_max, MAX_MAP_Z_SECTOR);

		////////////////////////////////////////
		//
		// sector scan (locate possible targets)
		//
		////////////////////////////////////////

		initialise_hms_target_list ();

		for (z_sector = z_sector_min; z_sector <= z_sector_max; z_sector++)
		{
			for (x_sector = x_sector_min; x_sector <= x_sector_max; x_sector++)
			{
				this_sector = get_local_raw_sector_entity (x_sector, z_sector);

				target = get_local_entity_first_child (this_sector, LIST_TYPE_SECTOR);

				while (target)
				{
					if (target != source)
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
										uvec_target.x = target_position.x - pilot_head_vp.position.x;
										uvec_target.y = target_position.y - pilot_head_vp.position.y;
										uvec_target.z = target_position.z - pilot_head_vp.position.z;

										target_sqr_range = (uvec_target.x * uvec_target.x) + (uvec_target.y * uvec_target.y) + (uvec_target.z * uvec_target.z);

										if (target_sqr_range < hms_max_visual_sqr_range * ((float) get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT) + 1.0)) // multiply on 1.4 if it's aircraft
										{
											if (target_sqr_range > 1.0)
											{
												normalise_3d_vector (&uvec_target);

												target_cos_angular_error = get_3d_unit_vector_dot_product (&pilot_head_vp.zv, &uvec_target);

												if (target_cos_angular_error >= cos_hms_max_field_of_view)
												{
													insert_entity_into_hms_target_list (target, locked_target, target_cos_angular_error, &target_position);
												}
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
		// scan possible targets (nearest to boresight first)
		//
		////////////////////////////////////////

		if (hms_target_root)
		{
			this_hms_target = hms_target_root;

			while (this_hms_target)
			{
				if (get_terrain_los_clear (&pilot_head_vp.position, &this_hms_target->target_position))
				{
					if (!get_line_of_sight_collision_tree (&pilot_head_vp.position, &this_hms_target->target_position, &intercept_point, &face_normal, FALSE, TRUE))
					{
						target = get_line_of_sight_collision_entity
						(
							source,
							NULL,
							&pilot_head_vp.position,
							&this_hms_target->target_position,
							&intercept_point,
							&face_normal
						);

						if (target == this_hms_target->target)
						{
							hms_boresight_target = target;

							break;
						}
					}
				}

				this_hms_target = this_hms_target->succ;
			}
		}

		deinitialise_hms_target_list ();
	}

	return (hms_boresight_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_hms (void)
{
	entity
		*current_target,
		*new__target;

	get_pilot_head_viewpoint ();

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (hms_target_locked)
	{
		if (!current_target)
		{
			hms_target_locked = FALSE;
		}
	}

	new__target = get_hms_boresight_target ();

	if (hms_target_locked)
	{
		if (new__target != current_target)
		{
			hms_target_locked = FALSE;
		}
	}

	if (new__target)
	{
		if (get_local_entity_parent (new__target, LIST_TYPE_GUNSHIP_TARGET) == NULL)
		{
			insert_local_entity_into_parents_child_list (new__target, LIST_TYPE_GUNSHIP_TARGET, get_gunship_entity (), NULL);
		}
	}

	set_gunship_target (new__target);

	target_locked = hms_target_locked;

	//
	// if not locked then unpadlock the target
	//

	if (!hms_target_locked)
	{
		if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET)
		{
			select_padlock_view_event (PADLOCK_MODE_NONE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_common_hms (void)
{
	hms_target_locked = target_locked;

	if (!numpad_events_overlaid)
	{
		numpad_events_overlaid = TRUE;

		push_numpad_cockpit_view_events_overlay ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_common_hms (void)
{
	hms_target_locked = FALSE;

	if (numpad_events_overlaid)
	{
		numpad_events_overlaid = FALSE;

		pop_numpad_cockpit_view_events_overlay ();
	}

	// start unpadlock on target handover by GCsDriver  08-12-2007	
	if(command_line_unpadlock_on_handover)
	{
		if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET)
		{
			select_padlock_view_event (PADLOCK_MODE_NONE);
			set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);
			//set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);
		}
	}
	// end unpadlock on target handover by GCsDriver  08-12-2007
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_selectable_hms_target (entity *target)
{
	entity
		*source,
		*boresight_target;

	vec3d
		*source_position,
		target_position;

	float
		target_range,
		temp_heading,
		temp_pitch;

	viewpoint
		temp_vp;

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

	if (target_range > hms_max_visual_range)
	{
		return (FALSE);
	}

	//
	// check line of sight
	//

	temp_heading = pilot_head_heading;

	temp_pitch = pilot_head_pitch;

	temp_vp = pilot_head_vp;

	get_pilot_head_heading_and_pitch_to_target (target);

	get_pilot_head_viewpoint ();

	boresight_target = get_hms_boresight_target ();

	pilot_head_heading = temp_heading;

	pilot_head_pitch = temp_pitch;

	pilot_head_vp = temp_vp;

	return (boresight_target == target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_hms_target (void)
{
	entity
		*target,
		*new__target,
		*current_target;

	new__target = NULL;

	hms_target_locked = FALSE;

	if (get_hms_valid ())
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
				if (get_selectable_hms_target (target))
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
				if (get_selectable_hms_target (target))
				{
					new__target = target;

					break;
				}

				target = get_local_entity_child_succ_circular (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
	}

	set_gunship_target (new__target);

	if (new__target)
	{
		hms_target_locked = TRUE;

		get_pilot_head_heading_and_pitch_to_target (new__target);

		if (in_cockpit)
		{
			if (set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET))
			{
				set_common_target_acquisition_system_lock_target (TRUE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_hms_target (void)
{
	entity
		*target,
		*new__target,
		*current_target;

	new__target = NULL;

	hms_target_locked = FALSE;

	if (get_hms_valid ())
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
				if (get_selectable_hms_target (target))
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
				if (get_selectable_hms_target (target))
				{
					new__target = target;

					break;
				}

				target = get_local_entity_child_pred_circular (target, LIST_TYPE_GUNSHIP_TARGET);
			}
		}
	}

	set_gunship_target (new__target);

	if (new__target)
	{
		hms_target_locked = TRUE;

		get_pilot_head_heading_and_pitch_to_target (new__target);

		if (in_cockpit)
		{
			if (set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET))
			{
				set_common_target_acquisition_system_lock_target (TRUE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031108 Designated targets

void select_next_designated_hms_target (void)
{
	entity
		*target,
		*new__target,
		*current_target;

	new__target = NULL;

	hms_target_locked = FALSE;

	if (get_hms_valid ())
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
				if (get_selectable_hms_target (target))
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
				if (get_selectable_hms_target (target))
				{
					new__target = target;

					break;
				}

				target = get_local_entity_child_succ_circular (target, LIST_TYPE_DESIGNATED_TARGET);
			}
		}
	}

	set_gunship_target (new__target);

	if (new__target)
	{
		hms_target_locked = TRUE;

		get_pilot_head_heading_and_pitch_to_target (new__target);

		if (in_cockpit)
		{
			if (set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET))
			{
				set_common_target_acquisition_system_lock_target (TRUE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_designated_hms_target (void)
{
	entity
		*target,
		*new__target,
		*current_target;

	new__target = NULL;

	hms_target_locked = FALSE;

	if (get_hms_valid ())
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
				if (get_selectable_hms_target (target))
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
				if (get_selectable_hms_target (target))
				{
					new__target = target;

					break;
				}

				target = get_local_entity_child_pred_circular (target, LIST_TYPE_DESIGNATED_TARGET);
			}
		}
	}

	set_gunship_target (new__target);

	if (new__target)
	{
		hms_target_locked = TRUE;

		get_pilot_head_heading_and_pitch_to_target (new__target);

		if (in_cockpit)
		{
			if (set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET))
			{
				set_common_target_acquisition_system_lock_target (TRUE);
			}
		}
	}
}

// Jabberwock 031108 ends

