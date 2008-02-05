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

#define DEBUG_MODULE									0

#define DEBUG_MODULE_EFFECTIVE_SHIP_WEAPONS	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int guidance_type_can_use_point_lock(weapon_guidance_types type)
{
	switch (type)
	{
	case WEAPON_GUIDANCE_TYPE_NONE:
	case WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED:					// fire and forget
	case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR:					// illumination source
	case WEAPON_GUIDANCE_TYPE_ACTIVE_LASER:							// fire and forget
	case WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR:							// fire and forget
	default:
		return FALSE;
	case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER:					// illumination source
	case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER_BEAM_RIDING:   // illumination source
	case WEAPON_GUIDANCE_TYPE_RADIO_COMMAND:							// control source
	case WEAPON_GUIDANCE_TYPE_WIRE_GUIDED:   						// control source
		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_local_entity_weapon_config (entity *en)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package;

	ASSERT (en);

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		memset (package_status, 0, SIZE_WEAPON_PACKAGE_STATUS_ARRAY);

		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		#if DEBUG_MODULE

		debug_log ("Loading weapon config (entity = %d, config = %d)", get_local_entity_index (en), config_type);

		#endif

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			package_status[package].number = weapon_config_database[config_type][package].number;

			package_status[package].damaged = FALSE;
		}
	}

	////////////////////////////////////////
	//

	if (!get_local_entity_weapon_available (en, get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON)))
	{
		#if 0
		{
			entity_sub_types
				weapon_sub_type;

			weapon_sub_type = get_local_entity_int_value (en, INT_TYPE_DEFAULT_WEAPON_TYPE);

			if (!get_local_entity_weapon_available (en, weapon_sub_type))
			{
				weapon_sub_type = get_first_available_weapon_sub_type (en);
			}

			set_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON, weapon_sub_type);
		}
		#else
		{
			set_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
		}
		#endif
	}

	//
	////////////////////////////////////////

	reset_entity_weapon_config_animation (en);

	if (en == get_gunship_entity ())
	{
		repair_gunship_weapon_damage ();
	}

	////////////////////////////////////////
	//
	// set Comanche stub wing visibility (not a very elegant solution)
	//
	////////////////////////////////////////

	set_comanche_stub_wing_visibility (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_viewpoint_from_weapon(weapon_config_types config_type, 
	weapon_package_status *package_status, int package, 
	object_3d_instance* inst3d, viewpoint *vp,
	object_3d_sub_object_search_data* search_weapon_system_heading,
	object_3d_sub_object_search_data* search_weapon_system_pitch)
{
	search_weapon_system_heading->search_depth = weapon_config_database[config_type][package].heading_depth;
	search_weapon_system_heading->search_object = inst3d;
	search_weapon_system_heading->sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

	if (find_object_3d_sub_object (search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_weapon_system_pitch->search_depth = weapon_config_database[config_type][package].pitch_depth;
		search_weapon_system_pitch->sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

		if (find_object_3d_sub_object_from_sub_object (search_weapon_system_heading, search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// get viewpoint of unrotated heading and pitch devices
			//

			search_weapon_system_heading->result_sub_object->relative_heading = 0.0;
			search_weapon_system_pitch->result_sub_object->relative_pitch = 0.0;

			get_3d_sub_object_world_viewpoint (search_weapon_system_pitch->result_sub_object, vp);

			// reset heading and pitch
			search_weapon_system_heading->result_sub_object->relative_heading = package_status->weapon_system_heading;
			search_weapon_system_pitch->result_sub_object->relative_pitch = -package_status->weapon_system_pitch;
			
			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_weapon_available (entity *launcher, entity_sub_types weapon_sub_type)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package;

	ASSERT (launcher);

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		package_status = get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

		if (package_status)
		{
			config_type = get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

			ASSERT (weapon_config_type_valid (config_type));

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					break;
				}

				ASSERT (package_status[package].number <= weapon_config_database[config_type][package].number);

				if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
				{
					if (!package_status[package].damaged)
					{
						if (package_status[package].number > 0)
						{
							return (TRUE);
						}
					}
				}
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_pylon_to_launch(entity_sub_types weapon_type, weapon_config_types config_type, weapon_package_status* package_status, int* number)
{
	int package, best_package = 0;
	
	*number = 0;
	
	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		ASSERT (package_status[package].number <= weapon_config_database[config_type][package].number);

		if (weapon_config_database[config_type][package].sub_type == weapon_type)
		{
			if (!package_status[package].damaged)
			{
				if (package_status[package].number > *number)
				{
					*number = package_status[package].number;

					best_package = package;
				}
			}
		}
	}

	return best_package;
}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void detach_local_entity_weapon (entity *launcher, entity_sub_types weapon_sub_type, int burst_size, viewpoint *vp)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		found,
		found_package,
		found_package_number;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch,
		search_weapon_system_weapon,
		search_weapon_system_muzzle;

	muzzle_flash_types
		muzzle_flash_type;

	float
		terrain_elevation;

	ASSERT (launcher);

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	ASSERT (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

	ASSERT (vp);

	ASSERT (burst_size > 0);

	//
	// set viewpoint to launcher origin
	//

	get_local_entity_vec3d (launcher, VEC3D_TYPE_POSITION, &vp->position);

	get_local_entity_attitude_matrix (launcher, vp->attitude);

	found = FALSE;

	package_status = get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		//
		// find undamaged package with most weapons remaining
		//

		found_package = get_next_pylon_to_launch(weapon_sub_type, config_type, package_status, &found_package_number);

		//
		// detach weapon
		//

		if (found_package_number > 0)
		{
			inst3d = get_local_entity_ptr_value (launcher, PTR_TYPE_INSTANCE_3D_OBJECT);

			ASSERT (inst3d);

			//
			// ensure that the 3D instance viewpoint is up to date (the object may not have been drawn)
			//

			memcpy (&inst3d->vp, vp, sizeof (viewpoint));

			search_weapon_system_heading.search_depth = weapon_config_database[config_type][found_package].heading_depth;
			search_weapon_system_heading.search_object = inst3d;
			search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

			if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search_weapon_system_pitch.search_depth = weapon_config_database[config_type][found_package].pitch_depth;
				search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

				if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search_weapon_system_weapon.search_depth = weapon_config_database[config_type][found_package].number - package_status[found_package].number;
					search_weapon_system_weapon.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_WEAPON;

					if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_pitch, &search_weapon_system_weapon) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_weapon_system_weapon.result_sub_object->visible_object = FALSE;

						get_3d_sub_object_world_viewpoint (search_weapon_system_weapon.result_sub_object, vp);

						#if DEBUG_MODULE

						debug_log
						(
							"Detach weapon as WEAPON device (h = %d, p = %d, w = %d, x = %.2f, y = %.2f, z = %.2f)",
							search_weapon_system_heading.search_depth,
							search_weapon_system_pitch.search_depth,
							search_weapon_system_weapon.search_depth,
							vp->position.x,
							vp->position.y,
							vp->position.z
						);

						#endif
					}
					else
					{
						search_weapon_system_muzzle.search_depth = weapon_config_database[config_type][found_package].muzzle_depth;
						search_weapon_system_muzzle.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_MUZZLE;

						if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_pitch, &search_weapon_system_muzzle) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							get_3d_sub_object_world_viewpoint (search_weapon_system_muzzle.result_sub_object, vp);

							////////////////////////////////////////
							//
							// ADD AN OFFSET TO THE ROCKET LAUNCH POSITION
							//
							// This has been added for the Comanche and Hokum cockpits
							// as the stub wing weapons are clearly visible from the cockpit.
							//
							// Ideally any values would have been added to the weapon database.
							//
							// The rotational firing order will be constant multi-player but the
							// z-offset is not. This could have been accomplished by passing the
							// weapon entity pointer and using its index as the random number
							// seed.
							//
							////////////////////////////////////////

							if (get_local_entity_int_value (launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
							{
								if (get_comanche_hokum_gunship ())
								{
									switch (weapon_sub_type)
									{
										case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
										case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
										case ENTITY_SUB_TYPE_WEAPON_S8:
										case ENTITY_SUB_TYPE_WEAPON_S13:
										{
											matrix3x3
												m1,
												m2;

											float
												roll,
												length,
												dz;

											roll = ((float) package_status[found_package].number * rad (360.0)) / (float) weapon_config_database[config_type][found_package].number;

											get_3d_transformation_matrix (m1, 0.0, 0.0, roll);

											multiply_matrix3x3_matrix3x3 (m2, m1, vp->attitude);

											memcpy (vp->attitude, m2, sizeof (matrix3x3));

											vp->x += vp->xv.x * 0.1;
											vp->y += vp->xv.y * 0.1;
											vp->z += vp->xv.z * 0.1;

											switch (weapon_sub_type)
											{
												case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
												case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
												{
													length = 1.44;	// weapon length

													break;
												}
												case ENTITY_SUB_TYPE_WEAPON_S8:
												{
													length = 1.65;	// weapon length

													break;
												}
												case ENTITY_SUB_TYPE_WEAPON_S13:
												{
													length = 3.03;	// weapon length

													break;
												}
											}

											dz = (length * 0.6) + (frand1 () * length * 0.5);

											vp->x += vp->zv.x * dz;
											vp->y += vp->zv.y * dz;
											vp->z += vp->zv.z * dz;

											break;
										}
									}
								}
							}

							//
							// muzzle flash effect
							//

							if (weapon_config_database[config_type][found_package].muzzle_flash_type != MUZZLE_FLASH_INVALID)
							{
								//
								// do not interrupt an on-going animation
								//

								if (package_status[found_package].muzzle_flash_timer == 0.0)
								{
									muzzle_flash_type = weapon_config_database[config_type][found_package].muzzle_flash_type;

									//
									// lock timer for one frame by making value negative (ensures first animation frame is drawn)
									//

									package_status[found_package].muzzle_flash_timer = -muzzle_flash_animation_database[muzzle_flash_type].muzzle_flash_duration;
								}
							}

							#if DEBUG_MODULE

							debug_log
							(
								"Detach weapon as MUZZLE device (h = %d, p = %d, m = %d, x = %.2f, y = %.2f, z = %.2f)",
								search_weapon_system_heading.search_depth,
								search_weapon_system_pitch.search_depth,
								search_weapon_system_muzzle.search_depth,
								vp->position.x,
								vp->position.y,
								vp->position.z
							);

							#endif
						}
						else
						{
							get_3d_sub_object_world_viewpoint (search_weapon_system_pitch.result_sub_object, vp);

							#if DEBUG_MODULE

							debug_log
							(
								"Detach weapon as PITCH device (h = %d, p = %d, x = %.2f, y = %.2f, z = %.2f)",
								search_weapon_system_heading.search_depth,
								search_weapon_system_pitch.search_depth,
								vp->position.x,
								vp->position.y,
								vp->position.z
							);

							#endif
						}
					}

					found = TRUE;
				}
			}

			//
			// update number of weapons
			//

			if (burst_size <= package_status[found_package].number)
			{
				package_status[found_package].number -= burst_size;
			}
			else
			{
				package_status[found_package].number = 0;
			}
		}
	}

	//
	// if the position is outside of the map volume then reset the viewpoint to the launcher origin
	//

	if (found)
	{
		if (!point_inside_map_volume (&vp->position))
		{
			//
			// the launcher origin must be on the map (else the position would debug fatal)
			//

			get_local_entity_vec3d (launcher, VEC3D_TYPE_POSITION, &vp->position);

			get_local_entity_attitude_matrix (launcher, vp->attitude);

			#if DEBUG_MODULE

			debug_log
			(
				"Position outside map volume - detach weapon as ORIGIN device (x = %.2f, y = %.2f, z = %.2f)",
				vp->position.x,
				vp->position.y,
				vp->position.z
			);

			#endif
		}
	}
	else
	{
		#if DEBUG_MODULE

		debug_log
		(
			"Detach weapon as ORIGIN device (x = %.2f, y = %.2f, z = %.2f)",
			vp->position.x,
			vp->position.y,
			vp->position.z
		);

		#endif
	}

	//
	// ensure that the weapon is above ground
	//

	terrain_elevation = get_3d_terrain_elevation (vp->position.x, vp->position.z);

	if (vp->position.y < terrain_elevation)
	{
		vp->position.y = terrain_elevation + 1.0;

		#if DEBUG_MODULE

		debug_colour_log
		(
			DEBUG_COLOUR_RED,
			"WARNING! Weapon below ground (repositioned above) (x = %.2f, y = %.2f, z = %.2f)",
			vp->position.x,
			vp->position.y,
			vp->position.z
		);

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// NOTE: KEEP THIS FUNCTION IN SYNC WITH THE SIMILAR FUNCTION IN WN_MOVE.C
//
////////////////////////////////////////

static void get_intercept_point (vec3d *pitch_device_position, float weapon_velocity, entity *target, vec3d *intercept_point)
{
	int
		number_of_iterations;

	float
		target_true_velocity,
		velocity_ratio,
		target_move_distance;

	vec3d
		target_position,
		target_motion_vector;

	ASSERT (pitch_device_position);

	ASSERT (target);

	ASSERT (intercept_point);

	get_local_entity_target_point (target, intercept_point);

	target_true_velocity = get_local_entity_vec3d_magnitude (target, VEC3D_TYPE_MOTION_VECTOR);

	if ((weapon_velocity > 0.001) && (target_true_velocity > 0.001))
	{
		if (target_true_velocity < weapon_velocity)
		{
			velocity_ratio = target_true_velocity / weapon_velocity;

			target_position = *intercept_point;

			get_local_entity_vec3d (target, VEC3D_TYPE_MOTION_VECTOR, &target_motion_vector);

			normalise_3d_vector (&target_motion_vector);

			number_of_iterations = 3;

			while (number_of_iterations--)
			{
				target_move_distance = get_3d_range (pitch_device_position, intercept_point) * velocity_ratio;

				intercept_point->x = target_position.x + (target_motion_vector.x * target_move_distance);
				intercept_point->y = target_position.y + (target_motion_vector.y * target_move_distance);
				intercept_point->z = target_position.z + (target_motion_vector.z * target_move_distance);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_ballistic_intercept_point_and_angle_of_projection
(
	vec3d *pitch_device_position,
	float weapon_velocity,
	entity *source,
	entity *target,
	vec3d *intercept_point,
	float *angle_of_projection
)
{
	int
		airborne_target,
		triangulate_range,
		result,
		number_of_iterations;

	float
		range,
		new_pitch,
		time_of_flight,
		target_true_velocity,
		target_move_distance;

	vec3d
		current_target_position,
		new_intercept_point,
		target_motion_vector;

	ASSERT (pitch_device_position);

	ASSERT (target);

	ASSERT (intercept_point);

	ASSERT (angle_of_projection);

	result = FALSE;

	*angle_of_projection = 0.0;

	get_local_entity_target_point (target, &current_target_position);
	*intercept_point = current_target_position;

	airborne_target = get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT);

	triangulate_range = (source == get_gunship_entity() && get_range_finder() == RANGEFINDER_TRIANGULATION);
	if (triangulate_range)
	{
		range = get_triangulated_by_position_range(pitch_device_position, intercept_point);
		if (range == -1.0)
			range = 1000.0;  // use 1000 meters if unable to triangulate range
		#ifdef DEBUG_MODULE
		debug_log("triangulated range: %.0f (real range: %.0f)", range, get_2d_range (pitch_device_position, intercept_point));
		#endif
	}
	else
		range = get_2d_range (pitch_device_position, intercept_point);

	//
	// target point differs to position so test inside map area before terrain elevation check
	//

	if (point_inside_map_area (intercept_point))
	{
		if (!airborne_target)
			intercept_point->y = get_3d_terrain_elevation (intercept_point->x, intercept_point->z);

		target_true_velocity = get_local_entity_vec3d_magnitude (target, VEC3D_TYPE_MOTION_VECTOR);

		if (target_true_velocity > 0.001)
		{
			//
			// moving target
			//

			get_local_entity_vec3d (target, VEC3D_TYPE_MOTION_VECTOR, &target_motion_vector);

			normalise_3d_vector_given_magnitude (&target_motion_vector, target_true_velocity);

			new_intercept_point = *intercept_point;

			number_of_iterations = 3;

			// refine ballistic calulation
			while (number_of_iterations--)
			{
				if (get_angle_of_projection_with_range(pitch_device_position, &new_intercept_point, weapon_velocity, &new_pitch, range))
				{
					result = TRUE;

					*angle_of_projection = new_pitch;

					*intercept_point = new_intercept_point;

					if (number_of_iterations > 0)
					{
						if (triangulate_range)
						{
							range = get_triangulated_by_position_range(pitch_device_position, intercept_point);
							if (range == -1.0)
								range = 1000.0;  // use 1000 meters if unable to triangulate range
						}
						else
							range = get_2d_range (pitch_device_position, intercept_point);
						
						if (airborne_target)
							// no use calulating ballistic trajectory to point on ground at target's distance
							time_of_flight = range / weapon_velocity;
						else
							time_of_flight = 2.0 * weapon_velocity * sin (new_pitch) * ONE_OVER_G;

						target_move_distance = time_of_flight * target_true_velocity;

						new_intercept_point.x = current_target_position.x + (target_motion_vector.x * target_move_distance);
						new_intercept_point.y = current_target_position.y + (target_motion_vector.y * target_move_distance);
						new_intercept_point.z = current_target_position.z + (target_motion_vector.z * target_move_distance);

						#ifdef DEBUG_MODULE
						debug_log("intercept point range: %.0f, ToF: %.2f, position: (%.0f, %.0f, %.0f)", range, time_of_flight, new_intercept_point.x, new_intercept_point.z, new_intercept_point.y);
						#endif
						if (point_inside_map_area (&new_intercept_point))
						{
							if (!airborne_target)
								new_intercept_point.y = get_3d_terrain_elevation (new_intercept_point.x, new_intercept_point.z);
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			//
			// stationary target
			//

			result = get_angle_of_projection (pitch_device_position, intercept_point, weapon_velocity, angle_of_projection);
		}
	}
	else
	{
		//
		// target off map
		//

		result = get_angle_of_projection (pitch_device_position, intercept_point, weapon_velocity, angle_of_projection);
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_lead_and_ballistic_intercept_point_and_angle_of_projection
(
	vec3d *pitch_device_position,
	entity_sub_types wpn_type,
	float weapon_velocity,
	entity *source,
	entity *target,
	vec3d *intercept_point,
	float *angle_of_projection
)
{
	int
		airborne_target,
		triangulate_range,
		result,
		number_of_iterations;

	float
		range,
		time_of_flight,
		target_move_distance;

	vec3d
		current_target_position,
		new_intercept_point,
		target_motion_vector;

	ASSERT (pitch_device_position);

	ASSERT (target);

	ASSERT (intercept_point);

	ASSERT (angle_of_projection);

	result = FALSE;

	*angle_of_projection = 0.0;

	get_local_entity_target_point (target, &current_target_position);
	*intercept_point = current_target_position;

	airborne_target = get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT);

	triangulate_range = (source == get_gunship_entity() && get_range_finder() == RANGEFINDER_TRIANGULATION);
	if (triangulate_range)
	{
		range = get_triangulated_by_position_range(pitch_device_position, intercept_point);
		if (range == -1.0)
			range = 1000.0;  // use 1000 meters if unable to triangulate range
		#ifdef DEBUG_MODULE
		debug_log("triangulated range: %.0f (real range: %.0f)", range, get_2d_range (pitch_device_position, intercept_point));
		#endif
	}
	else
		range = get_2d_range (pitch_device_position, intercept_point);

	if (range < 0.001)
		return FALSE;

	//
	// target point differs to position so test inside map area before terrain elevation check
	//

	if (point_inside_map_area (intercept_point))
	{
		float target_true_velocity = 0.0;
		
		if (target)
			target_true_velocity = get_local_entity_vec3d_magnitude (target, VEC3D_TYPE_MOTION_VECTOR);

		#if DEBUG_MODULE
		debug_log("Aiming at target moving at %.1f m/s", target_true_velocity);
		#endif

		if (target_true_velocity > 0.1)
		{
			//
			// moving target
			//

			result = TRUE;

			get_local_entity_vec3d (target, VEC3D_TYPE_MOTION_VECTOR, &target_motion_vector);
			normalise_3d_vector_given_magnitude (&target_motion_vector, target_true_velocity);
			new_intercept_point = *intercept_point;

			// refine ballistic calulation
			if (source == get_gunship_entity())
				number_of_iterations = 5;
			else
				number_of_iterations = 3;
			while (number_of_iterations--)
			{
				int simplified = (number_of_iterations > 1);   // only calculate with highest accuracy the last time
				if (!get_ballistic_pitch_deflection(wpn_type, range, pitch_device_position->y - intercept_point->y, angle_of_projection, &time_of_flight, simplified))
					return FALSE;
				*intercept_point = new_intercept_point;

				if (number_of_iterations > 0)
				{
					if (triangulate_range)
					{
						range = get_triangulated_by_position_range(pitch_device_position, intercept_point);
						if (range == -1.0)
							range = 1000.0;  // use 200 meters if unable to triangulate range
					}
					else
						range = get_2d_range (pitch_device_position, intercept_point);

					target_move_distance = time_of_flight * target_true_velocity;

					new_intercept_point.x = current_target_position.x + (target_motion_vector.x * target_move_distance);
					new_intercept_point.y = current_target_position.y + (target_motion_vector.y * target_move_distance);
					new_intercept_point.z = current_target_position.z + (target_motion_vector.z * target_move_distance);

					#ifdef DEBUG_MODULE
					debug_log("intercept point range: %.0f, ToF: %.2f, position: (%.0f, %.0f, %.0f)", range, time_of_flight, new_intercept_point.x, new_intercept_point.z, new_intercept_point.y);
					#endif
					if (!point_inside_map_area (&new_intercept_point))
						break;
				}
			}
			#ifdef DEBUG_MODULE
			debug_log("intercept point range: %.0f, ToF: %.2f, position: (%.0f, %.0f, %.0f)", range, time_of_flight, new_intercept_point.x, new_intercept_point.z, new_intercept_point.y);
			#endif
		}
		else
		{
			float time_of_flight;
			//
			// stationary target
			//

			result = TRUE;
			if (!get_ballistic_pitch_deflection(wpn_type, range, pitch_device_position->y - intercept_point->y, angle_of_projection, &time_of_flight, FALSE))
				return FALSE;
		}
	}
	else
	{
		//
		// target off map
		//

		result = get_angle_of_projection (pitch_device_position, intercept_point, weapon_velocity, angle_of_projection);
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_pitch_device_to_target_vector
(
	entity *source,
	entity *target,
	entity_sub_types weapon_sub_type,
	vec3d *pitch_device_position,
	vec3d *target_vector
)
{
	int
		result;

	float
		weapon_velocity,
		dx,
		dz,
		heading,
		pitch;

	vec3d
		target_position;

	matrix3x3
		m;

	ASSERT (source);
	ASSERT (target);
	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));
	ASSERT (pitch_device_position);
	ASSERT (target_vector);

	result = FALSE;

	target_vector->x = 0.0;
	target_vector->y = 0.0;
	target_vector->z = 0.0;

	switch (weapon_database[weapon_sub_type].aiming_type)
	{
		////////////////////////////////////////
		case WEAPON_AIMING_TYPE_NONE:
		////////////////////////////////////////
		{
			debug_fatal ("WEAPON_AIMING_TYPE_NONE invalid");

			break;
		}
		////////////////////////////////////////
		case WEAPON_AIMING_TYPE_CALC_INTERCEPT_POINT:
		////////////////////////////////////////
		{
			// arneh - this is the old aiming code, and unused with newer GWUT-files
			if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
			{
				weapon_velocity = weapon_database[weapon_sub_type].cruise_velocity;

				if (weapon_database[weapon_sub_type].acquire_parent_forward_velocity)
				{
					weapon_velocity += get_local_entity_float_value (source, FLOAT_TYPE_VELOCITY);
				}

				get_intercept_point (pitch_device_position, weapon_velocity, target, &target_position);
			}
			else
			{
				get_local_entity_target_point (target, &target_position);
			}

			////////////////////////////////////////
			//
			// disperse tracer effect
			//

			if (weapon_database[weapon_sub_type].gun_shake)
			{
				float
					target_range,
					max_range,
					error;

				target_range = get_3d_range (&target_position, pitch_device_position);

				max_range = weapon_database[weapon_sub_type].max_range;

				target_range = min (target_range, max_range);

				error = 3.0 * target_range / max_range;

				target_position.x += error * sfrand1 ();
				target_position.y += error * sfrand1 ();
				target_position.z += error * sfrand1 ();
			}

			//
			////////////////////////////////////////

			target_vector->x = target_position.x - pitch_device_position->x;
			target_vector->y = target_position.y - pitch_device_position->y;
			target_vector->z = target_position.z - pitch_device_position->z;

			result = TRUE;

			break;
		}
		////////////////////////////////////////
		case WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION:
		case WEAPON_AIMING_TYPE_CALC_LEAD_AND_BALLISTIC:
		////////////////////////////////////////
		{
			weapon_velocity = weapon_database[weapon_sub_type].cruise_velocity;

			if (weapon_database[weapon_sub_type].acquire_parent_forward_velocity)
			{
				weapon_velocity += get_local_entity_float_value (source, FLOAT_TYPE_VELOCITY);
			}

			if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
			{
				if (weapon_database[weapon_sub_type].aiming_type == WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION)
					result = get_ballistic_intercept_point_and_angle_of_projection (pitch_device_position, weapon_velocity, source, target, &target_position, &pitch);
				else
					result = get_lead_and_ballistic_intercept_point_and_angle_of_projection (pitch_device_position, weapon_sub_type, weapon_velocity, source, target, &target_position, &pitch);
			}
			else
			{
				get_local_entity_target_point (target, &target_position);

				//
				// target point differs to position so test inside map area before terrain elevation check
				//

				if (point_inside_map_area (&target_position))
				{
					target_position.y = get_3d_terrain_elevation (target_position.x, target_position.z);
				}

				if (weapon_database[weapon_sub_type].aiming_type == WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION)
					result = get_angle_of_projection (pitch_device_position, &target_position, weapon_velocity, &pitch);
				else
					result = get_lead_and_ballistic_intercept_point_and_angle_of_projection (pitch_device_position, weapon_sub_type, weapon_velocity, source, target, &target_position, &pitch);
			}

			if (result)
			{
				dx = target_position.x - pitch_device_position->x;
				dz = target_position.z - pitch_device_position->z;

				heading = atan2 (dx, dz);

				get_3d_transformation_matrix (m, heading, pitch, 0.0);

				target_vector->x = m[2][0];
				target_vector->y = m[2][1];
				target_vector->z = m[2][2];
			}

			break;
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_entity_weapon_systems (entity *source)
{
	entity
		*target;

	entity_sub_types
		selected_weapon;

	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch;

	viewpoint
		vp;

	vec3d
		target_vector;

	int
		package,
		located_heading_and_pitch_devices,
		selected_weapon_system_ready;

	unsigned int
		selected_weapon_mask;

	float
		required_heading_offset,
		required_pitch_offset,
		delta_heading_offset,
		delta_pitch_offset,
		heading_rate_delta_time,
		pitch_rate_delta_time,
		new_heading_offset,
		new_pitch_offset,
		flat_range;

	ASSERT (source);

	//
	// assume that the selected weapon system is ready
	//

	selected_weapon_system_ready = TRUE;

	set_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON_SYSTEM_READY, TRUE);

	////////////////////////////////////////

	package_status = get_local_entity_ptr_value (source, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		////////////////////////////////////////

		config_type = get_local_entity_int_value (source, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		if (config_type != WEAPON_CONFIG_TYPE_UNARMED)
		{
			selected_weapon = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

			ASSERT (entity_sub_type_weapon_valid (selected_weapon));

			////////////////////////////////////////

			inst3d = get_local_entity_ptr_value (source, PTR_TYPE_INSTANCE_3D_OBJECT);

			ASSERT (inst3d);

			get_local_entity_vec3d (source, VEC3D_TYPE_POSITION, &inst3d->vp.position);

			get_local_entity_attitude_matrix (source, inst3d->vp.attitude);

			////////////////////////////////////////

			target = get_local_entity_parent (source, LIST_TYPE_TARGET);

			////////////////////////////////////////////////////////////////////////////////
			//
			// Open and close weapon system ready devices.
			//
			// If the selected weapon system needs to be opened then all weapons with weapon
			// system ready devices are opened.
			//
			// Some attempt is made to prevent the weapon aiming code wrestling with the weapon
			// system ready code but where there are shared heading and pitch devices this is
			// not always possible.
			//
			////////////////////////////////////////////////////////////////////////////////
			{
				int
					found_weapon_system_ready_device,
					make_selected_weapon_system_ready,
					weapon_system_heading_returned,
					weapon_system_pitch_returned;

				//
				// are there any weapon system ready devices? are any of these the selected weapon?
				//

				found_weapon_system_ready_device = FALSE;

				make_selected_weapon_system_ready = FALSE;

				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
					{
						break;
					}

					if (weapon_config_database[config_type][package].make_weapon_system_ready)
					{
						found_weapon_system_ready_device = TRUE;

						if (weapon_config_database[config_type][package].sub_type == selected_weapon)
						{
							make_selected_weapon_system_ready = TRUE;
						}
					}
				}

				//
				// open and close weapon system ready devices
				//

				if (found_weapon_system_ready_device)
				{
					if (make_selected_weapon_system_ready)
					{
						//
						// open all weapon system ready devices and get a true indication of their ready state
						//

						open_entity_weapon_system_ready (source);

						selected_weapon_system_ready = get_local_entity_int_value (source, INT_TYPE_WEAPON_SYSTEM_READY);
					}
					else
					{
						//
						// before closing all weapon system ready devices, return heading and pitch devices to their rest position
						//

						weapon_system_heading_returned = TRUE;

						weapon_system_pitch_returned = TRUE;

						for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
						{
							if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
							{
								break;
							}

							if (weapon_config_database[config_type][package].make_weapon_system_ready)
							{
								//
								// ignore shared devices
								//

								if (!weapon_config_database[config_type][package].heading_share_mask)
								{
									if (package_status[package].weapon_system_heading != 0.0)
									{
										weapon_system_heading_returned = FALSE;
									}
								}

								if (!weapon_config_database[config_type][package].pitch_share_mask)
								{
									if (package_status[package].weapon_system_pitch != 0.0)
									{
										weapon_system_pitch_returned = FALSE;
									}
								}
							}
						}

						if (weapon_system_heading_returned && weapon_system_pitch_returned)
						{
							close_entity_weapon_system_ready (source);
						}
					}
				}
			}

			////////////////////////////////////////
			//
			// selected weapons take priority in shared heading and pitch devices
			//
			////////////////////////////////////////
			{
				unsigned int
					mask;

				selected_weapon_mask = 0;

				mask = 1;

				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
					{
						break;
					}

					if (weapon_config_database[config_type][package].sub_type == selected_weapon)
					{
						if (package_status[package].number > 0)
						{
							selected_weapon_mask |= mask;
						}
					}

					mask <<= 1;
				}
			}

			////////////////////////////////////////////////////////////////////////////////
			//
			// rotate and animate weapon systems
			//
			////////////////////////////////////////////////////////////////////////////////

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					break;
				}

				////////////////////////////////////////
				//
				// rotate heading and pitch
				//
				////////////////////////////////////////

				if (weapon_config_database[config_type][package].rotate)
				{
					located_heading_and_pitch_devices = FALSE;

					required_heading_offset = 0.0;

					required_pitch_offset = 0.0;

					if (weapon_config_database[config_type][package].sub_type == selected_weapon)
					{
						if (selected_weapon_system_ready)
						{
							if (package_status[package].number > 0)
							{
								if (get_local_entity_float_value (source, FLOAT_TYPE_VELOCITY) < weapon_config_database[config_type][package].rotate_inhibit_velocity)
								{
									if (target)
									{
										located_heading_and_pitch_devices = 
											get_viewpoint_from_weapon(config_type, &package_status[package], package, inst3d, &vp, &search_weapon_system_heading, &search_weapon_system_pitch);
										
										if (!located_heading_and_pitch_devices)
										{
											debug_colour_log (DEBUG_COLOUR_AMBER, "Cannot locate device to rotate (name = %s, package = %d)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), package);
											
											return;
										}

										//
										// get pitch device to target vector
										//
										// (using the unrotated pitch device position is not pin-point accurate but is close enough)
										//

										if (get_pitch_device_to_target_vector (source, target, selected_weapon, &vp.position, &target_vector))
										{
											vec3d offset_vector;
											
											//
											// get heading and pitch offsets
											//

											multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &target_vector);

											required_heading_offset = atan2 (offset_vector.x, offset_vector.z);
											required_heading_offset = bound
											(
												required_heading_offset,
												weapon_config_database[config_type][package].min_heading_limit,
												weapon_config_database[config_type][package].max_heading_limit
											);

											flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));

											required_pitch_offset = atan2 (offset_vector.y, flat_range);
											required_pitch_offset = bound
											(
												required_pitch_offset,
												weapon_config_database[config_type][package].min_pitch_limit,
												weapon_config_database[config_type][package].max_pitch_limit
											);
										}
									}
								}
							}
						}
						else
						{
							//
							// weapon system ready device is not ready, hold the current position
							//

							required_heading_offset = package_status[package].weapon_system_heading;

							required_pitch_offset = package_status[package].weapon_system_pitch;

							set_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON_SYSTEM_READY, FALSE);
						}

						// 050320 Jabberwock - Cannon tracking - major restructuring for MP
						
						if (get_local_entity_int_value (source, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
						{
							if (get_local_entity_int_value (source, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL) // Jabberwock 050128 Bug removed!
							{
								switch (command_line_cannontrack)
								{
									case 1:
									{
										if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_OFF)
										{
											required_heading_offset = -pilot_head_heading;

											required_pitch_offset = pilot_head_pitch;
											
											set_client_server_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_HEADING, required_heading_offset);
																				
											set_client_server_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_PITCH, required_pitch_offset);

										}
										break;
									}

									case 2:
									{
										if ((target_acquisition_system == TARGET_ACQUISITION_SYSTEM_IHADSS) || (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HIDSS) || (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS))
										{
											required_heading_offset = -pilot_head_heading;

											required_pitch_offset = pilot_head_pitch;
											
											set_client_server_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_HEADING, required_heading_offset);
																				
											set_client_server_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_PITCH, required_pitch_offset);

										}
										break;
									}
								}
							
								// slave to EO system if it is active (and doesn't have a target)
								if (!target && is_using_eo_system(command_line_cannontrack != 2))
								{
									vec3d* tracking_point = get_eo_tracking_point();

									ASSERT(source == get_gunship_entity());
									
									required_heading_offset = eo_azimuth;
									required_pitch_offset = eo_elevation;

									// if using point lock, then aim for that point
									if (tracking_point && weapon_database[selected_weapon].aiming_type == WEAPON_AIMING_TYPE_CALC_LEAD_AND_BALLISTIC)
									{
										float pitch, dummy;
										float height_diff;
										float range;

										#ifdef DEBUG_MODULE
										debug_log("Aiming for point lock at %.0f, %.0f,  %.0f", tracking_point->x, tracking_point->y, tracking_point->z);
										#endif

										// if we don't already have it we need to get the viewpoint of the weapon
										if (!located_heading_and_pitch_devices)
										{
											located_heading_and_pitch_devices = 
												get_viewpoint_from_weapon(config_type, &package_status[package], package, inst3d, &vp, &search_weapon_system_heading, &search_weapon_system_pitch);
											
											if (!located_heading_and_pitch_devices)
												debug_fatal("Cannot locate device to rotate (name = %s, package = %d)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), package);
										}

										height_diff = vp.position.y - tracking_point->y;
										range = get_range_to_target();

										if (range <= 0.0)
											range = 1000.0;   // use 1000 meters if unable to determine range

										// adjust weapon elevation for range
										if (get_ballistic_pitch_deflection(selected_weapon, range, height_diff, &pitch, &dummy, FALSE))
										{
											matrix3x3 m;
											float dx, dz;
											float heading;
											vec3d offset_vector, tracking_vector;
												
											// get heading and pitch offsets

											dx = tracking_point->x - vp.position.x;
											dz = tracking_point->z - vp.position.z;
							
											heading = atan2 (dx, dz);
											
											// need to adjust for the gun's attitude, as the helicopter may not fly level all the time
											get_3d_transformation_matrix (m, heading, pitch, 0.0);

											tracking_vector.x = m[2][0];
											tracking_vector.y = m[2][1];
											tracking_vector.z = m[2][2];

											multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &tracking_vector);

											required_heading_offset = atan2 (offset_vector.x, offset_vector.z);
	
											flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));
											required_pitch_offset = atan2 (offset_vector.y, flat_range);
										}
									}
								}	
							}
							else
							{	
								if ((get_comms_model () == COMMS_MODEL_SERVER) && (get_local_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_HEADING) || get_local_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_PITCH)))
								{
									required_heading_offset = get_local_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_HEADING);

									required_pitch_offset = get_local_entity_float_value (source, FLOAT_TYPE_PLAYER_WEAPON_PITCH);
								}
							}
							required_heading_offset = bound
							(
								required_heading_offset,
								weapon_config_database[config_type][package].min_heading_limit,
								weapon_config_database[config_type][package].max_heading_limit
							);

							required_pitch_offset = bound
							(
								required_pitch_offset,
								weapon_config_database[config_type][package].min_pitch_limit,
								weapon_config_database[config_type][package].max_pitch_limit
							);

						}
					// 050320 Jabberwock ends
					}

						//set_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON_SYSTEM_READY, FALSE);


					if ((required_heading_offset != package_status[package].weapon_system_heading) || (required_pitch_offset != package_status[package].weapon_system_pitch))
					{
						if (!located_heading_and_pitch_devices)
						{
							search_weapon_system_heading.search_depth = weapon_config_database[config_type][package].heading_depth;
							search_weapon_system_heading.search_object = inst3d;
							search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

							if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
							{
								search_weapon_system_pitch.search_depth = weapon_config_database[config_type][package].pitch_depth;
								search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

								if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
								{
									debug_colour_log (DEBUG_COLOUR_AMBER, "Cannot locate pitch device to rotate (name = %s, package = %d)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), package);

									return;
								}
							}
							else
							{
								debug_colour_log (DEBUG_COLOUR_AMBER, "Cannot locate heading device to rotate (name = %s, package = %d)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), package);

								return;
							}
						}

						delta_heading_offset = required_heading_offset - package_status[package].weapon_system_heading;

						if
						(
							(weapon_config_database[config_type][package].min_heading_limit == (float) rad (-180.0)) &&
							(weapon_config_database[config_type][package].max_heading_limit == (float) rad (180.0))
						)
						{
							if (delta_heading_offset > rad (180.0))
							{
								delta_heading_offset -= rad (360.0);
							}
							else if (delta_heading_offset < rad (-180.0))
							{
								delta_heading_offset += rad (360.0);
							}
						}

						heading_rate_delta_time = weapon_config_database[config_type][package].heading_rate * get_delta_time ();

						delta_heading_offset = bound (delta_heading_offset, -heading_rate_delta_time, heading_rate_delta_time);

						new_heading_offset = package_status[package].weapon_system_heading + delta_heading_offset;

						if (new_heading_offset > rad (180.0))
						{
							new_heading_offset -= rad (360);
						}
						else if (new_heading_offset < rad (-180.0))
						{
							new_heading_offset += rad (360);
						}

						////////////////////////////////////////

						delta_pitch_offset = required_pitch_offset - package_status[package].weapon_system_pitch;

						pitch_rate_delta_time = weapon_config_database[config_type][package].pitch_rate * get_delta_time ();

						delta_pitch_offset = bound (delta_pitch_offset, -pitch_rate_delta_time, pitch_rate_delta_time);

						new_pitch_offset = package_status[package].weapon_system_pitch + delta_pitch_offset;

						////////////////////////////////////////
						//
						// shared heading devices arbitrate for control
						//
						////////////////////////////////////////

						if (weapon_config_database[config_type][package].heading_share_mask)
						{
							unsigned int
								heading_share_mask,
								mask;

							int
								i,
								control_package;

							heading_share_mask = weapon_config_database[config_type][package].heading_share_mask;

							//
							// selected weapon packages take priority
							//

							mask = selected_weapon_mask & heading_share_mask;

							if (!mask)
							{
								mask = heading_share_mask;
							}

							ASSERT (mask);

							//
							// first shared package encountered takes control of the heading device
							//

							control_package = 0;

							for (i = 0; i < NUM_WEAPON_PACKAGES; i++)
							{
								if (mask & 1)
								{
									break;
								}

								control_package++;

								mask >>= 1;
							}

							ASSERT (control_package < NUM_WEAPON_PACKAGES);

							//
							// set heading value in all shared devices
							//

							if (package == control_package)
							{
								mask = 1;

								for (i = 0; i < NUM_WEAPON_PACKAGES; i++)
								{
									if (weapon_config_database[config_type][i].number == 0)
									{
										break;
									}

									if (mask & heading_share_mask)
									{
										package_status[i].weapon_system_heading = new_heading_offset;
									}

									mask <<= 1;
								}

								search_weapon_system_heading.result_sub_object->relative_heading = new_heading_offset;
							}
						}
						else
						{
							package_status[package].weapon_system_heading = new_heading_offset;

							search_weapon_system_heading.result_sub_object->relative_heading = new_heading_offset;
						}

						////////////////////////////////////////
						//
						// shared pitch devices arbitrate for control
						//
						////////////////////////////////////////

						if (weapon_config_database[config_type][package].pitch_share_mask)
						{
							unsigned int
								pitch_share_mask,
								mask;

							int
								i,
								control_package;

							pitch_share_mask = weapon_config_database[config_type][package].pitch_share_mask;

							//
							// selected weapon packages take priority
							//

							mask = selected_weapon_mask & pitch_share_mask;

							if (!mask)
							{
								mask = pitch_share_mask;
							}

							ASSERT (mask);

							//
							// first shared package encountered takes control of the pitch device
							//

							control_package = 0;

							for (i = 0; i < NUM_WEAPON_PACKAGES; i++)
							{
								if (mask & 1)
								{
									break;
								}

								control_package++;

								mask >>= 1;
							}

							ASSERT (control_package < NUM_WEAPON_PACKAGES);

							//
							// set pitch value in all shared devices
							//

							if (package == control_package)
							{
								mask = 1;

								for (i = 0; i < NUM_WEAPON_PACKAGES; i++)
								{
									if (weapon_config_database[config_type][i].number == 0)
									{
										break;
									}

									if (mask & pitch_share_mask)
									{
										package_status[i].weapon_system_pitch = new_pitch_offset;
									}

									mask <<= 1;
								}

								search_weapon_system_pitch.result_sub_object->relative_pitch = -new_pitch_offset;
							}
						}
						else
						{
							package_status[package].weapon_system_pitch = new_pitch_offset;

							search_weapon_system_pitch.result_sub_object->relative_pitch = -new_pitch_offset;
						}
					}
				}

				////////////////////////////////////////
				//
				// update animations
				//
				////////////////////////////////////////

				if (weapon_config_database[config_type][package].muzzle_flash_type != MUZZLE_FLASH_INVALID)
				{
					if (package_status[package].muzzle_flash_timer > 0.0)
					{
						package_status[package].muzzle_flash_timer -= get_delta_time ();

						if (package_status[package].muzzle_flash_timer < 0.0)
						{
							package_status[package].muzzle_flash_timer = 0.0;
						}
					}
					else if (package_status[package].muzzle_flash_timer < 0.0)
					{
						//
						// unlock timer
						//

						package_status[package].muzzle_flash_timer = -package_status[package].muzzle_flash_timer;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_and_draw_entity_muzzle_flash_effect (entity *en)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package,
		num_frames,
		current_frame;

	float
		duration,
		elapsed_time,
		muzzle_rotation_angle;

	object_3d_instance
		*entity_inst3d,
		*effect_inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch,
		search_weapon_system_muzzle;

	muzzle_flash_types
		muzzle_flash_type;

	texture_animation_indices
		texture_animation_index;

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return;
	}

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		entity_inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

		ASSERT (entity_inst3d);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			if (weapon_config_database[config_type][package].muzzle_flash_type != MUZZLE_FLASH_INVALID)
			{
				if (package_status[package].muzzle_flash_timer != 0.0)
				{
					//
					// unlock timer
					//

					if (package_status[package].muzzle_flash_timer < 0.0)
					{
						package_status[package].muzzle_flash_timer = -package_status[package].muzzle_flash_timer;
					}

					search_weapon_system_heading.search_depth = weapon_config_database[config_type][package].heading_depth;
					search_weapon_system_heading.search_object = entity_inst3d;
					search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

					if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_weapon_system_pitch.search_depth = weapon_config_database[config_type][package].pitch_depth;
						search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

						if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_weapon_system_muzzle.search_depth = weapon_config_database[config_type][package].muzzle_depth;
							search_weapon_system_muzzle.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_MUZZLE;

							if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_pitch, &search_weapon_system_muzzle) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
							{
								muzzle_flash_type = weapon_config_database[config_type][package].muzzle_flash_type;

								effect_inst3d = construct_temporary_3d_object (muzzle_flash_animation_database[muzzle_flash_type].object_3d_index_number, TRUE);

								if (effect_inst3d)
								{
									//
									// ensure that the 3D instance viewpoint is up to date (the object may not have been drawn)
									//

									get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &entity_inst3d->vp.position);

									get_local_entity_attitude_matrix (en, entity_inst3d->vp.attitude);

									//
									// viewpoint
									//

									get_3d_sub_object_world_viewpoint (search_weapon_system_muzzle.result_sub_object, &effect_inst3d->vp);

									//
									// timing info
									//

									duration = muzzle_flash_animation_database[muzzle_flash_type].muzzle_flash_duration;

									elapsed_time = duration - package_status[package].muzzle_flash_timer;

									ASSERT (elapsed_time >= 0.0);

									//
									// animate texture 1
									//

									texture_animation_index = muzzle_flash_animation_database[muzzle_flash_type].texture_animation_index1;

									if (texture_animation_index != TEXTURE_ANIMATION_INDEX_LAST)
									{
										num_frames = get_texture_animation_number_of_frames (texture_animation_index);

										current_frame = (int) ((elapsed_time * num_frames) / duration);

										set_texture_animation_frame_on_object (effect_inst3d, texture_animation_index, current_frame);
									}

									//
									// animate texture 2
									//

									texture_animation_index = muzzle_flash_animation_database[muzzle_flash_type].texture_animation_index2;

									if (texture_animation_index != TEXTURE_ANIMATION_INDEX_LAST)
									{
										num_frames = get_texture_animation_number_of_frames (texture_animation_index);

										current_frame = (int) ((elapsed_time * num_frames) / duration);

										set_texture_animation_frame_on_object (effect_inst3d, texture_animation_index, current_frame);
									}

									//
									// draw
									//

									effect_inst3d->object_has_shadow = FALSE;

									insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, effect_inst3d);

									//
									// rotate muzzle
									//

									muzzle_rotation_angle = weapon_config_database[config_type][package].muzzle_rotate_rate;

									if (muzzle_rotation_angle != 0.0)
									{
										muzzle_rotation_angle *= get_delta_time ();

										muzzle_rotation_angle += search_weapon_system_muzzle.result_sub_object->relative_roll;

										muzzle_rotation_angle = wrap_angle (muzzle_rotation_angle);

										search_weapon_system_muzzle.result_sub_object->relative_roll = muzzle_rotation_angle;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_entity_weapon_system_weapon_and_target_vectors (entity *launcher)
{
	weapon_package_status
		*package_status;

	entity_sub_types
		weapon_sub_type;

	weapon_config_types
		config_type;

	int
		package,
		found_package,
		found_package_number;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch;

	viewpoint
		vp;

	vec3d
		weapon_to_target_vector,
		*weapon_vector_ptr,
		*weapon_to_target_vector_ptr;

	entity
		*target;

	ASSERT (launcher);
	ASSERT(launcher->type != ENTITY_TYPE_WEAPON);

	weapon_vector_ptr = get_local_entity_vec3d_ptr (launcher, VEC3D_TYPE_WEAPON_VECTOR);

	ASSERT (weapon_vector_ptr);

	weapon_to_target_vector_ptr = get_local_entity_vec3d_ptr (launcher, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);

	ASSERT (weapon_to_target_vector_ptr);

	//
	// set default values (force 180 degree error)
	//

	set_local_entity_int_value (launcher, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID, FALSE);

	weapon_vector_ptr->x = 0.0;
	weapon_vector_ptr->y = 0.0;
	weapon_vector_ptr->z = 1.0;

	weapon_to_target_vector_ptr->x = 0.0;
	weapon_to_target_vector_ptr->y = 0.0;
	weapon_to_target_vector_ptr->z = -1.0;

	package_status = get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		weapon_sub_type = get_local_entity_int_value (launcher, INT_TYPE_SELECTED_WEAPON);

		if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			target = get_local_entity_parent (launcher, LIST_TYPE_TARGET);

			if (target || get_local_entity_int_value(launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				config_type = get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

				//
				// find undamaged package with most weapons remaining
				//

				found_package_number = 0;

				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
					{
						break;
					}

					if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
					{
						if (!package_status[package].damaged)
						{
							if (package_status[package].number > found_package_number)
							{
								found_package = package;

								found_package_number = package_status[package].number;
							}
						}
					}
				}

				if (found_package_number > 0)
				{
					inst3d = get_local_entity_ptr_value (launcher, PTR_TYPE_INSTANCE_3D_OBJECT);

					ASSERT (inst3d);

					//
					// ensure that the 3D instance viewpoint is up to date (the object may not have been drawn)
					//

					get_local_entity_vec3d (launcher, VEC3D_TYPE_POSITION, &inst3d->vp.position);

					get_local_entity_attitude_matrix (launcher, inst3d->vp.attitude);

					search_weapon_system_heading.search_depth = weapon_config_database[config_type][found_package].heading_depth;
					search_weapon_system_heading.search_object = inst3d;
					search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

					if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_weapon_system_pitch.search_depth = weapon_config_database[config_type][found_package].pitch_depth;
						search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

						if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							vec3d* tracking_point = NULL;
							get_3d_sub_object_world_viewpoint (search_weapon_system_pitch.result_sub_object, &vp);

							if (get_local_entity_int_value(launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
								tracking_point = get_local_entity_vec3d_ptr(launcher, VEC3D_TYPE_EO_TRACKING_POINT);

							if (tracking_point)  // use get vector to EO tracking point, if any
							{
								ASSERT(get_local_entity_int_value(launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI);  // only player aircraft have tracking point

								if (!eo_tracking_point_valid(tracking_point))
									return;

								weapon_to_target_vector.x = tracking_point->x - vp.position.x;
								weapon_to_target_vector.y = tracking_point->y - vp.position.y;
								weapon_to_target_vector.z = tracking_point->z - vp.position.z;
							}
							else
							{
								ASSERT(target);
								if (!get_pitch_device_to_target_vector (launcher, target, weapon_sub_type, &vp.position, &weapon_to_target_vector))
									return;
							}

							normalise_3d_vector (&weapon_to_target_vector);

							*weapon_vector_ptr = vp.zv;
							*weapon_to_target_vector_ptr = weapon_to_target_vector;

							set_local_entity_int_value (launcher, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID, TRUE);
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_selected_weapon_to_target_offsets (entity *launcher, float *heading_offset, float *pitch_offset)
{
	weapon_package_status
		*package_status;

	entity_sub_types
		weapon_sub_type;

	weapon_config_types
		config_type;

	int
		result,
		package,
		found_package,
		found_package_number;

	float
		flat_range;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch;

	viewpoint
		vp;

	vec3d
		weapon_to_target_vector,
		offset_vector;

	entity
		*target;

	ASSERT (launcher);

	ASSERT (heading_offset);

	ASSERT (pitch_offset);

	result = FALSE;

	package_status = get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		weapon_sub_type = get_local_entity_int_value (launcher, INT_TYPE_SELECTED_WEAPON);

		if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			target = get_local_entity_parent (launcher, LIST_TYPE_TARGET);

			if (target)
			{
				config_type = get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

				//
				// find undamaged package with most weapons remaining
				//

				found_package_number = 0;

				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
					{
						break;
					}

					if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
					{
						if (!package_status[package].damaged)
						{
							if (package_status[package].number > found_package_number)
							{
								found_package = package;

								found_package_number = package_status[package].number;
							}
						}
					}
				}

				if (found_package_number > 0)
				{
					inst3d = get_local_entity_ptr_value (launcher, PTR_TYPE_INSTANCE_3D_OBJECT);

					ASSERT (inst3d);

					//
					// ensure that the 3D instance viewpoint is up to date (the object may not have been drawn)
					//

					get_local_entity_vec3d (launcher, VEC3D_TYPE_POSITION, &inst3d->vp.position);

					get_local_entity_attitude_matrix (launcher, inst3d->vp.attitude);

					search_weapon_system_heading.search_depth = weapon_config_database[config_type][found_package].heading_depth;
					search_weapon_system_heading.search_object = inst3d;
					search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

					if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_weapon_system_pitch.search_depth = weapon_config_database[config_type][found_package].pitch_depth;
						search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

						if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							get_3d_sub_object_world_viewpoint (search_weapon_system_pitch.result_sub_object, &vp);

							if (get_pitch_device_to_target_vector (launcher, target, weapon_sub_type, &vp.position, &weapon_to_target_vector))
							{
								multiply_transpose_matrix3x3_vec3d (&offset_vector, vp.attitude, &weapon_to_target_vector);

								*heading_offset = atan2 (offset_vector.x, offset_vector.z);

								flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));

								*pitch_offset = atan2 (offset_vector.y, flat_range);

								result = TRUE;
							}
						}
					}
				}
			}
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_selected_weapon_viewpoint (entity *launcher, viewpoint *vp)
{
	weapon_package_status
		*package_status;

	entity_sub_types
		weapon_sub_type;

	weapon_config_types
		config_type;

	int
		result,
		package,
		found_package,
		found_package_number;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch;

	ASSERT (launcher);

	ASSERT (vp);

	result = FALSE;

	package_status = get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		weapon_sub_type = get_local_entity_int_value (launcher, INT_TYPE_SELECTED_WEAPON);

		if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			config_type = get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

			//
			// find undamaged package with most weapons remaining
			//

			found_package_number = 0;

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					break;
				}

				if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
				{
					if (!package_status[package].damaged)
					{
						if (package_status[package].number > found_package_number)
						{
							found_package = package;

							found_package_number = package_status[package].number;
						}
					}
				}
			}

			if (found_package_number > 0)
			{
				inst3d = get_local_entity_ptr_value (launcher, PTR_TYPE_INSTANCE_3D_OBJECT);

				ASSERT (inst3d);

				//
				// ensure that the 3D instance viewpoint is up to date (the object may not have been drawn)
				//

				get_local_entity_vec3d (launcher, VEC3D_TYPE_POSITION, &inst3d->vp.position);

				get_local_entity_attitude_matrix (launcher, inst3d->vp.attitude);

				search_weapon_system_heading.search_depth = weapon_config_database[config_type][found_package].heading_depth;
				search_weapon_system_heading.search_object = inst3d;
				search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

				if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search_weapon_system_pitch.search_depth = weapon_config_database[config_type][found_package].pitch_depth;
					search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

					if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						get_3d_sub_object_world_viewpoint (search_weapon_system_pitch.result_sub_object, vp);

						result = TRUE;
					}
				}
			}
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_target_intercept_point (entity *source, entity *target, entity_sub_types weapon_sub_type, vec3d *intercept_point)
{
	float
		weapon_velocity;

	vec3d
		*source_position;

	ASSERT (source);

	ASSERT (target);

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	ASSERT (intercept_point);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		weapon_velocity = weapon_database[weapon_sub_type].cruise_velocity;

		if (weapon_database[weapon_sub_type].acquire_parent_forward_velocity)
		{
			weapon_velocity += get_local_entity_float_value (source, FLOAT_TYPE_VELOCITY);
		}
	}
	else
	{
		weapon_velocity = 0.0;
	}

	get_intercept_point (source_position, weapon_velocity, target, intercept_point);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_weapon_ammunition_available (entity *launcher)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package;

	entity_sub_types
		weapon_type;

	ASSERT (launcher);

	//
	// get list of weapons available on the launcher
	//

	package_status = get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (!package_status)
	{
		return FALSE;
	}

	config_type = get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

	ASSERT (weapon_config_type_valid (config_type));

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		weapon_type = weapon_config_database[config_type][package].sub_type;

		//
		// check package is valid
		//

		if (weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ASSERT (package_status[package].number <= weapon_config_database[config_type][package].number);

			//
			// check package is not damaged
			//

			if (!package_status[package].damaged)
			{
				//
				// check package has rounds left
				//

				if (package_status[package].number > 0)
				{
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_weapon_salvo_size (entity *launcher, entity_sub_types weapon_sub_type)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package;

	ASSERT (launcher);

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		package_status = get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

		if (package_status)
		{
			config_type = get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

			ASSERT (weapon_config_type_valid (config_type));

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					break;
				}

				if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
				{
					if (!package_status[package].damaged)
					{
						if (package_status[package].number > 0)
						{
							return (weapon_config_database[config_type][package].salvo_size);
						}
					}
				}
			}
		}
	}

	return (1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// WARNING: This function totally abuses the damage flag system and it is likely that the server and
//          clients will get out of sync but this should be ok as the detach function is fail safe.
//
// This function tags any of the ships selected weapon packages as damaged if they cannot see the
// target. This is an attempt to prevent the weapon systems from 'stalling' if the next available
// weapon cannot see the target.
//
// If none of the weapons can see the target then none of them are tagged as damaged. Also, if only
// once instance of the weapon package exists then this system is not invoked. This is to prevent
// the weapon type from being made unavailable and effecting other functions.
//
// This function assumes that the damage flags are not otherwise used.
//
////////////////////////////////////////

void suppress_ineffective_ship_weapons (entity *source)
{
	int
		package,
		num_weapon_instances,
		num_effective_weapons;

	float
		dx,
		dz,
		heading,
		min_heading,
		max_heading,
		bearing,
		normalised_max_heading,
		normalised_bearing;

	entity
		*target;

	vec3d
		target_position;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch;

	entity_sub_types
		selected_weapon;

	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	viewpoint
		vp;

	#if DEBUG_MODULE_EFFECTIVE_SHIP_WEAPONS

	rgb_colour
		heading_line_colour,
		min_heading_line_colour,
		max_heading_line_colour;

	#endif

	ASSERT (source);

	ASSERT (get_local_entity_int_value (source, INT_TYPE_IDENTIFY_SHIP_VEHICLE));

	//
	// check valid package status
	//

	package_status = get_local_entity_ptr_value (source, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (!package_status)
	{
		return;
	}

	//
	// get config type
	//

	config_type = get_local_entity_int_value (source, INT_TYPE_WEAPON_CONFIG_TYPE);

	ASSERT (weapon_config_type_valid (config_type));

	//
	// set all packages to undamaged
	//

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		package_status[package].damaged = FALSE;
	}

	//
	// check valid config type
	//

	if (config_type == WEAPON_CONFIG_TYPE_UNARMED)
	{
		return;
	}

	//
	// check valid selected weapon
	//

	selected_weapon = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	ASSERT (entity_sub_type_weapon_valid (selected_weapon));

	if (selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		return;
	}

	//
	// check valid target
	//

	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (!target)
	{
		return;
	}

	get_local_entity_vec3d (target, VEC3D_TYPE_POSITION, &target_position);

	//
	// check more than one instance of the selected weapon type is available (so that the weapon type is always available)
	//

	num_weapon_instances = 0;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[config_type][package].sub_type == selected_weapon)
		{
			if (package_status[package].number > 0)
			{
				num_weapon_instances++;
			}
		}
	}

	if (num_weapon_instances <= 1)
	{
		return;
	}

	//
	// update the source's 3D instance position and attitude (in case it has not been drawn yet)
	//

	inst3d = get_local_entity_ptr_value (source, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	get_local_entity_vec3d (source, VEC3D_TYPE_POSITION, &inst3d->vp.position);

	get_local_entity_attitude_matrix (source, inst3d->vp.attitude);

	//
	// check each instance of the selected weapon to see if the target is within its view cone
	//

	num_effective_weapons = 0;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[config_type][package].sub_type == selected_weapon)
		{
			if (package_status[package].number > 0)
			{
				search_weapon_system_heading.search_depth = weapon_config_database[config_type][package].heading_depth;
				search_weapon_system_heading.search_object = inst3d;
				search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

				if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search_weapon_system_pitch.search_depth = weapon_config_database[config_type][package].pitch_depth;
					search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

					if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						//
						// get viewpoint of unrotated heading and pitch devices
						//

						search_weapon_system_heading.result_sub_object->relative_heading = 0.0;

						search_weapon_system_pitch.result_sub_object->relative_pitch = 0.0;

						get_3d_sub_object_world_viewpoint (search_weapon_system_pitch.result_sub_object, &vp);

						search_weapon_system_heading.result_sub_object->relative_heading = package_status[package].weapon_system_heading;

						search_weapon_system_pitch.result_sub_object->relative_pitch = -package_status[package].weapon_system_pitch;

						//
						// (keep angles in range 0 to 360 degrees)
						//

						heading = get_heading_from_attitude_matrix (vp.attitude);

						if (heading < 0.0)
						{
							heading += rad (360.0);
						}

						min_heading = heading + weapon_config_database[config_type][package].min_heading_limit;

						if (min_heading < 0.0)
						{
							min_heading += rad (360.0);
						}
						else if (min_heading > rad (360.0))
						{
							min_heading -= rad (360.0);
						}

						max_heading = heading + weapon_config_database[config_type][package].max_heading_limit;

						if (max_heading < 0.0)
						{
							max_heading += rad (360.0);
						}
						else if (max_heading > rad (360.0))
						{
							max_heading -= rad (360.0);
						}

						dx = target_position.x - vp.x;
						dz = target_position.z - vp.z;

						bearing = atan2 (dx, dz);

						if (bearing < 0.0)
						{
							bearing += rad (360.0);
						}

						normalised_max_heading = max_heading - min_heading;

						if (normalised_max_heading < 0.0)
						{
							normalised_max_heading += rad (360.0);
						}

						normalised_bearing = bearing - min_heading;

						if (normalised_bearing < 0.0)
						{
							normalised_bearing += rad (360.0);
						}

						if (normalised_bearing <= normalised_max_heading)
						{
							num_effective_weapons++;

							#if DEBUG_MODULE_EFFECTIVE_SHIP_WEAPONS

							heading_line_colour = sys_col_green;
							min_heading_line_colour = sys_col_yellow;
							max_heading_line_colour = sys_col_amber;

							#endif
						}
						else
						{
							package_status[package].damaged = TRUE;

							#if DEBUG_MODULE_EFFECTIVE_SHIP_WEAPONS

							heading_line_colour = sys_col_red;
							min_heading_line_colour = sys_col_cyan;
							max_heading_line_colour = sys_col_magenta;

							#endif
						}

						#if DEBUG_MODULE_EFFECTIVE_SHIP_WEAPONS

						if (source == get_external_view_entity ())
						{
							float
								heading;

							vec3d
								p2;

							matrix3x3
								m;

							heading = get_heading_from_attitude_matrix (vp.attitude);

							p2 = vp.position;

							p2.x += vp.zv.x * 2000.0;
							p2.y += vp.zv.y * 2000.0;
							p2.z += vp.zv.z * 2000.0;

							create_debug_3d_line (&vp.position, &p2, heading_line_colour, 0.0);

							get_arbitrary_rotation_matrix (m, &vp.yv, heading + weapon_config_database[config_type][package].min_heading_limit);

							p2 = vp.position;

							p2.x += m[0][2] * 2000.0;
							p2.y += m[1][2] * 2000.0;
							p2.z += m[2][2] * 2000.0;

							create_debug_3d_line (&vp.position, &p2, min_heading_line_colour, 0.0);

							get_arbitrary_rotation_matrix (m, &vp.yv, heading + weapon_config_database[config_type][package].max_heading_limit);

							p2 = vp.position;

							p2.x += m[0][2] * 2000.0;
							p2.y += m[1][2] * 2000.0;
							p2.z += m[2][2] * 2000.0;

							create_debug_3d_line (&vp.position, &p2, max_heading_line_colour, 0.0);
						}

						#endif
					}
				}
			}
		}
	}

	//
	// if no effective weapons are available then tag them all as undamaged (so the weapon type is still available)
	//

	if (num_effective_weapons == 0)
	{
		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			package_status[package].damaged = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_weapon_launched_sound_effects (entity *launcher, entity_sub_types weapon_sub_type)
{
	int
		looping;

	entity_sub_types
		sound_effect_sub_type;

	sound_sample_indices
		launch_sound_effect;

	vec3d
		*position;

	position = get_local_entity_vec3d_ptr (launcher, VEC3D_TYPE_POSITION);

	//
	// launch sounds
	//

	if (resume_client_server_continuous_weapon_sound_effect (launcher, weapon_sub_type))
	{
	}
	else
	{
		sound_effect_sub_type = weapon_database[weapon_sub_type].launch_sound_effect_sub_type;

		if (sound_effect_sub_type == ENTITY_SUB_TYPE_EFFECT_SOUND_MISC)
		{
			looping = FALSE;
		}
		else
		{
			looping = TRUE;
		}

		if (get_local_entity_int_value (launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			//
			// interior sound
			//

			launch_sound_effect = weapon_database[weapon_sub_type].interior_launch_sound_effect;

			if (launch_sound_effect != SOUND_SAMPLE_INDEX_NONE)
			{
				create_client_server_sound_effect_entity
				(
					launcher,
					ENTITY_SIDE_NEUTRAL,
					sound_effect_sub_type,
					SOUND_CHANNEL_SOUND_EFFECT,
					SOUND_LOCALITY_INTERIOR,
					NULL,												// position
					1.0,												// amplification
					1.0,												// Werewolf pitch
					TRUE,												// valid sound effect
					looping,											// looping
					1,													// sample count
					&launch_sound_effect							// sample index list
				);
			}

			//
			// exterior sound
			//

			launch_sound_effect = weapon_database[weapon_sub_type].exterior_launch_sound_effect;

			if (launch_sound_effect != SOUND_SAMPLE_INDEX_NONE)
			{
				create_client_server_sound_effect_entity
				(
					launcher,
					ENTITY_SIDE_NEUTRAL,
					sound_effect_sub_type,
					SOUND_CHANNEL_SOUND_EFFECT,
					SOUND_LOCALITY_EXTERIOR,
					NULL,												// position
					1.0,												// amplification
					1.0,												// Werewolf pitch
					TRUE,												// valid sound effect
					looping,											// looping
					1,													// sample count
					&launch_sound_effect							// sample index list
				);
			}
		}
		else
		{
			//
			// normal sound
			//

			launch_sound_effect = weapon_database[weapon_sub_type].exterior_launch_sound_effect;

			if (launch_sound_effect != SOUND_SAMPLE_INDEX_NONE)
			{
				position = get_local_entity_vec3d_ptr (launcher, VEC3D_TYPE_POSITION);

				create_client_server_sound_effect_entity
				(
					launcher,
					ENTITY_SIDE_NEUTRAL,
					sound_effect_sub_type,
					SOUND_CHANNEL_SOUND_EFFECT,
					SOUND_LOCALITY_ALL,
					NULL,												// position
					1.0,												// amplification
					1.0,												// Werewolf pitch
					TRUE,												// valid sound effect
					looping,											// looping
					1,													// sample count
					&launch_sound_effect							// sample index list
				);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
