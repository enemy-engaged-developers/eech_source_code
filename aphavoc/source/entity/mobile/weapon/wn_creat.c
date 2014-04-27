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

#include "entity/tacview/tacview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

viewpoint
	*weapon_viewpoint;
float
	weapon_velocity = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_local (entity_types type, int index, char *pargs)
{
	entity
		*en;

	weapon
		*raw;

	int
		seed,
		submunition = (weapon_velocity != 0); // if it's submunition, we will use weapon position, attitude and velocity values

	viewpoint
		vp;

	////////////////////////////////////////
  	//
  	// VALIDATE
  	//
	////////////////////////////////////////

	validate_local_create_entity_index (index);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_CREATE, NULL, type, index);

	#endif

	en = get_free_entity (index);

	if (en)
	{
		float dispersion;

		////////////////////////////////////////
   	//
   	// MALLOC ENTITY DATA
   	//
		////////////////////////////////////////

		set_local_entity_type (en, type);

		raw = (weapon *) malloc_fast_mem (sizeof (weapon));

		set_local_entity_data (en, raw);

		////////////////////////////////////////
   	//
   	// INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
		//
		// DO NOT USE ACCESS FUNCTIONS
		//
		// DO NOT USE RANDOM VALUES
		//
		////////////////////////////////////////

		memset (raw, 0, sizeof (weapon));

		//
		// mobile
		//

		raw->mob.sub_type = ENTITY_SUB_TYPE_UNINITIALISED;

		raw->mob.position.x = MID_MAP_X;
		raw->mob.position.y = MID_MAP_Y;
		raw->mob.position.z = MID_MAP_Z;

		get_identity_matrix3x3 (raw->mob.attitude);

		raw->mob.alive = TRUE;
		
		//
		// weapon
		//

		raw->kill_code = WEAPON_KILL_CODE_OK;

		////////////////////////////////////////
		//
		// OVERWRITE DEFAULT VALUES WITH GIVEN ATTRIBUTES
		//
		////////////////////////////////////////

		set_local_entity_attributes (en, pargs);

		////////////////////////////////////////
		//
		// CHECK MANDATORY ATTRIBUTES HAVE BEEN GIVEN
		//
		////////////////////////////////////////

		ASSERT (entity_sub_type_weapon_valid (raw->mob.sub_type));

		ASSERT (raw->launched_weapon_link.parent);

		ASSERT (raw->burst_size > 0);
		
		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		if (!submunition)
		{
			if (weapon_database[raw->mob.sub_type].acquire_parent_forward_velocity)
				raw->mob.velocity = get_local_entity_float_value (raw->launched_weapon_link.parent, FLOAT_TYPE_VELOCITY);
			else
				raw->mob.velocity = 0.0;
		}
		else
		{
			memcpy ( vp.attitude, weapon_viewpoint->attitude, sizeof ( matrix3x3 ));
			raw->mob.velocity = weapon_velocity;
		}
		
		raw->mob.velocity += weapon_database[raw->mob.sub_type].muzzle_velocity;

		seed = get_client_server_entity_random_number_seed (en);

		raw->mob.velocity += weapon_database[raw->mob.sub_type].muzzle_velocity_max_error * frand1x (&seed);

		raw->weapon_lifetime = weapon_database[raw->mob.sub_type].boost_time + weapon_database[raw->mob.sub_type].sustain_time;

		raw->decoy_timer = get_decoy_timer_start_value (weapon_database[raw->mob.sub_type].decoy_type);

		//
		// detach weapon from launcher (get position and attitude)
		//

		if (!submunition)
		{
			detach_local_entity_weapon (raw->launched_weapon_link.parent, raw->mob.sub_type, raw->burst_size, &vp);
			raw->mob.position = vp.position;
		}
		else
			raw->mob.position = weapon_viewpoint->position;

		// shells or convertional munitions with remote fuze, decoy_timer is time value
		
		if ((weapon_database[raw->mob.sub_type].warhead_type == WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_AIRCRAFT || weapon_database[raw->mob.sub_type].warhead_type == WEAPON_WARHEAD_TYPE_CONVERTIONAL_MUNITIONS) && 
				!weapon_database[raw->mob.sub_type].guidance_type)
		{
			entity *target;
			float time_of_flight, dummy;
			vec3d intercept_point;
			
			target = get_local_entity_parent (raw->launched_weapon_link.parent, LIST_TYPE_TARGET);
			
			if (target)
				if (get_lead_and_ballistic_intercept_point_and_angle_of_projection(&raw->mob.position, raw->mob.sub_type, 0, en, target, &intercept_point, &dummy, &time_of_flight))
				{
					raw->decoy_timer = - (weapon_database[raw->mob.sub_type].boost_time + weapon_database[raw->mob.sub_type].sustain_time - time_of_flight + 0.5 * sfrand1() * weapon_database[raw->mob.sub_type].cruise_time_max_error);
					
					if (weapon_database[raw->mob.sub_type].warhead_type == WEAPON_WARHEAD_TYPE_CONVERTIONAL_MUNITIONS)
						raw->decoy_timer -= 1;
					
					raw->decoy_timer = max(0, raw->decoy_timer);
				}
		}

		// arneh - add dispersion as random rotation in heading and pitch up to max error angle
		// dispersion is ratio of circular error probability value to range (for CEP 0.5m at 1000m ratio value is 0.0005)

		dispersion = weapon_database[raw->mob.sub_type].circular_error_probable;

		if (dispersion > 0.0)
		{
			matrix3x3
				m;

			float
				heading = 3 * sfrand1norm() * tan(dispersion),
				pitch = 3 * sfrand1norm() * tan(dispersion);
			
			get_3d_transformation_matrix(m, heading, pitch, 0.0);
			multiply_matrix3x3_matrix3x3(raw->mob.attitude, vp.attitude, m);
		}
		else
			memcpy (raw->mob.attitude, vp.attitude, sizeof (matrix3x3));

		//
		// interest level
		//

		set_local_entity_float_value (raw->launched_weapon_link.parent, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_LAUNCHED_WEAPON, raw->launched_weapon_link.parent, NULL);

		if (raw->mob.target_link.parent)
		{
			insert_local_entity_into_parents_child_list (en, LIST_TYPE_TARGET, raw->mob.target_link.parent, NULL);
		}

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->mob.position), NULL);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

		if (tacview_is_logging())
			write_tacview_new_unit(en);

		//
		// check if the weapon camera is primed and this weapon has been launched by the external view entity
		//

		if (get_camera_entity ())
		{
			if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_WEAPON_CAMERA_PRIMED))
			{
				if (raw->launched_weapon_link.parent == get_external_view_entity ())
				{
					if (get_local_entity_int_value (en, INT_TYPE_VIEWABLE_WEAPON))
					{
						notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_WEAPON);

						set_local_entity_int_value (get_camera_entity (), INT_TYPE_WEAPON_CAMERA_PRIMED, FALSE);
					}
				}
			}
		}
	}

	weapon_velocity = 0;
	
	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_remote (entity_types type, int index, char *pargs)
{
	validate_remote_create_entity_index (index);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_CREATE, NULL, type, index);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_CREATE, NULL, type, index, pargs);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_server (entity_types type, int index, char *pargs)
{
	entity
		*en;

	validate_client_server_local_fn ();

	en = create_local (type, index, pargs);

	if (en)
	{
		validate_client_server_remote_fn ();

		create_remote (type, get_local_entity_index (en), pargs);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_client (entity_types type, int index, char *pargs)
{
	entity
		*en;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		en = create_remote (type, index, pargs);
	}
	else
	{
		validate_client_server_local_fn ();

		en = create_local (type, index, pargs);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_weapon_create_functions (void)
{
	fn_create_local_entity				[ENTITY_TYPE_WEAPON]								= create_local;

	fn_create_client_server_entity	[ENTITY_TYPE_WEAPON][COMMS_MODEL_SERVER]	= create_server;

	fn_create_client_server_entity	[ENTITY_TYPE_WEAPON][COMMS_MODEL_CLIENT]	= create_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_entity_weapon (entity *launcher, entity_sub_types weapon_sub_type, int weapon_index, int burst_size, int *smoke_trail_indices, int salvo)
{
	entity
		*force,
		*target,
		*weapon;

	meta_smoke_list_types
		smoke_trail_type;

	int
		i,
		num_smoke_trail_entities,
		valid_sound_effect,
		current_weapon_count,
		new_weapon_count;

	ASSERT (launcher);

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	//
	// get target
	//

	if (!(weapon_database[weapon_sub_type].weapon_class & (WEAPON_CLASS_DECOY | WEAPON_CLASS_CARGO | WEAPON_CLASS_DEBRIS)))
	{
		target = get_local_entity_parent (launcher, LIST_TYPE_TARGET);

/*		if (weapon_database[weapon_sub_type].flight_profile_or_self_destr == 1)
		{
			if (get_local_entity_int_value (launcher, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
			{
				target = NULL;
			}
		} */
	}
	else
	{
		target = NULL;
	}

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		////////////////////////////////////////
		//
		// SERVER/TX and SERVER/RX
		//
		////////////////////////////////////////

		ASSERT (weapon_index == ENTITY_INDEX_DONT_CARE);

		ASSERT (burst_size == BURST_SIZE_DONT_CARE);

		ASSERT (!smoke_trail_indices);

		// NOTE: The clients' weapon counters lag the servers' so it is possible that the
		//       client may unknowingly attempt to create more weapons than are available.
		//       This is prone to happen during rapid firing.

		current_weapon_count = get_local_entity_weapon_count (launcher, weapon_sub_type);

		if (current_weapon_count > 0)
		{
			int loal_mode = weapon_database[weapon_sub_type].flight_profile_or_self_destr == 1 && get_local_entity_int_value (launcher, INT_TYPE_LOCK_ON_AFTER_LAUNCH);

			//
			// get burst size wrt rate of fire
			//

			if (weapon_database[weapon_sub_type].rate_of_fire != FIRE_SINGLE_WEAPON)
			{
				float time_per_shot = weapon_database[weapon_sub_type].inverse_rate_of_fire * ONE_MINUTE;
				unsigned int* last_shot = NULL;

				switch (launcher->type)
				{
				case ENTITY_TYPE_HELICOPTER:
					last_shot = &((helicopter*)get_local_entity_data(launcher))->ac.weapon_salvo_timer;
					break;

				case ENTITY_TYPE_FIXED_WING:
					last_shot = &((fixed_wing*)get_local_entity_data(launcher))->ac.weapon_salvo_timer;
					break;

				case ENTITY_TYPE_ANTI_AIRCRAFT:
					last_shot = &((anti_aircraft*)get_local_entity_data(launcher))->vh.weapon_salvo_timer;
					break;

				case ENTITY_TYPE_PERSON:
					last_shot = &((person*)get_local_entity_data(launcher))->vh.weapon_salvo_timer;
					break;

				case ENTITY_TYPE_ROUTED_VEHICLE:
					last_shot = &((routed_vehicle*)get_local_entity_data(launcher))->vh.weapon_salvo_timer;
					break;

				case ENTITY_TYPE_SHIP_VEHICLE:
					last_shot = &((ship_vehicle*)get_local_entity_data(launcher))->vh.weapon_salvo_timer;
					break;
				}

				if (last_shot)
				{
					unsigned int current_time = get_system_time();
					float elapsed_time = 1;

					if (*last_shot > 0)
					{
						if (current_time < *last_shot)
							return;
						elapsed_time = (current_time - *last_shot) * 0.001;
						
						if (current_time > *last_shot + 500) //Magitek: ensure elapsed time does not continue to expire on client excessively, note 500ms is a fudge value.
						{
							if (get_local_entity_int_value (launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)//only fix player helicopters
							{
								elapsed_time = get_delta_time();
								*last_shot = current_time;
							}
						}
					}
					else
						elapsed_time = get_delta_time();

					burst_size = (int)(weapon_database[weapon_sub_type].rate_of_fire * ONE_OVER_ONE_MINUTE * elapsed_time);
					if (burst_size < 1)
					{
						if (*last_shot == 0)  // first shot in salvo always get fired
							burst_size = 1;
						else
							return;
					}

					if (*last_shot)
						*last_shot += (int)(burst_size * time_per_shot * 1000.0);
					else
						*last_shot = current_time;
				}
				else
				{
					ASSERT(FALSE);
					burst_size = 1;
				}
			}
			else
			{
				burst_size = 1;
			}

			//
			// set burst timer
			//

			valid_sound_effect = FALSE;

			if (get_local_entity_float_value (launcher, FLOAT_TYPE_WEAPON_BURST_TIMER) <= 0)
			{
				set_local_entity_float_value (launcher, FLOAT_TYPE_WEAPON_BURST_TIMER, weapon_database[weapon_sub_type].burst_duration);

				valid_sound_effect = TRUE;
			}

			//
			// create weapon
			//

			if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
			{
				set_force_local_entity_create_stack_attributes (TRUE);
			}

			weapon = create_local_entity
			(
				ENTITY_TYPE_WEAPON,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, weapon_sub_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_WEAPON_BURST_SIZE, burst_size),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_WEAPON_MISSILE_PHASE, MISSILE_PHASE1),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_LOCK_ON_AFTER_LAUNCH, loal_mode),
				ENTITY_ATTR_PARENT (LIST_TYPE_LAUNCHED_WEAPON, launcher),
				ENTITY_ATTR_PARENT (LIST_TYPE_TARGET, target),
				ENTITY_ATTR_END
			);

			set_force_local_entity_create_stack_attributes (FALSE);

			if (weapon)
			{
				int decoy = weapon_database[weapon_sub_type].weapon_class & (WEAPON_CLASS_DECOY | WEAPON_CLASS_CARGO | WEAPON_CLASS_DEBRIS);
				
				//
				// send FIRE message to force (unless it's a decoy/cargo/debris being launched)
				//

				if (target && !decoy)
				{
					force = get_local_force_entity ((entity_sides) get_local_entity_int_value (target, INT_TYPE_SIDE));

					if (force)
					{
						notify_local_entity (ENTITY_MESSAGE_ENTITY_FIRED_AT, force, launcher, target);
					}
				}

				//
				// create sound effect(s)
				//

				if (valid_sound_effect)
				{
					create_weapon_launched_sound_effects (launcher, weapon_sub_type);
				}

				//
				// create smoke trail
				//

				smoke_trail_type = (meta_smoke_list_types) get_local_entity_int_value (weapon, INT_TYPE_WEAPON_SMOKE_TRAIL_TYPE);

				if (smoke_trail_type != META_SMOKE_LIST_TYPE_NONE && !(!decoy && command_line_smoke_optimisation && (salvo % 4 != 0))) // smoke optimisation, only for weapons
				{
					struct OBJECT_3D_BOUNDS
						*bounding_box;

					vec3d
						exhaust_offset;

					num_smoke_trail_entities = count_entities_in_meta_smoke_list (smoke_trail_type);

					ASSERT (num_smoke_trail_entities > 0);

					smoke_trail_indices = (int *) malloc_fast_mem (sizeof (int) * num_smoke_trail_entities);

					for (i = 0; i < num_smoke_trail_entities; i++)
					{
						smoke_trail_indices[i] = ENTITY_INDEX_DONT_CARE;
					}

					bounding_box = get_object_3d_bounding_box (get_local_entity_int_value (weapon, INT_TYPE_DEFAULT_3D_SHAPE));

					if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT) ||(weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT))
					{
						exhaust_offset.x = 0.0;
						exhaust_offset.y = 0.0;
						exhaust_offset.z = 0.0;
					}
					else
					{
						exhaust_offset.x = 0.0;
						exhaust_offset.y = 0.0;
						exhaust_offset.z = bounding_box->zmin;
					}

					create_meta_smoke_list_specified_offset (smoke_trail_type, weapon, &exhaust_offset, smoke_trail_indices);
				}

				transmit_entity_comms_message
				(
					ENTITY_COMMS_CREATE_WEAPON,
					NULL,
					launcher,
					weapon_sub_type,
					get_local_entity_safe_index (weapon),
					burst_size,
					smoke_trail_indices
				);

				if (smoke_trail_indices)
				{
					free_mem (smoke_trail_indices);
				}

				//
				// out of weapons (if infinite weapons then reload else select next weapon)
				//

				new_weapon_count = get_local_entity_weapon_count (launcher, weapon_sub_type);

				if (new_weapon_count <= 0)
				{
					#if !DEMO_VERSION
					if (get_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_WEAPONS))
					{
						weapon_config_types
							config_type;

						config_type = (weapon_config_types) get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

						set_client_server_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE, config_type);
					}
					else
					#endif
					{
						//
						// play weapon out of ammo speech
						//

						play_entity_weapon_out_speech (launcher, weapon_sub_type);

						//
						// select next weapon
						//
/*
						if (!(weapon_database[weapon_sub_type].weapon_class & (WEAPON_CLASS_DECOY | WEAPON_CLASS_CARGO | WEAPON_CLASS_DEBRIS)))
						{
							entity_sub_types
								next_weapon_sub_type;

							if (get_local_entity_int_value (launcher, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
							{
								next_weapon_sub_type = get_next_available_weapon_sub_type (launcher);
							}
							else
							{
								next_weapon_sub_type = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
							}

							set_client_server_entity_int_value (launcher, INT_TYPE_SELECTED_WEAPON, next_weapon_sub_type);
						}
*/
					}
				}
				else
				{
					int
						report_ammo_low_count;

					report_ammo_low_count = weapon_database[weapon_sub_type].report_ammo_low_count;

					if ((current_weapon_count > report_ammo_low_count) && (new_weapon_count <= report_ammo_low_count))
					{
						//
						// play weapon low speech
						//

						play_entity_weapon_low_speech (launcher, weapon_sub_type);
					}
					else
					{
						//
						// weapon launch speech
						//

						play_entity_weapon_launched_speech (launcher, weapon_sub_type);
					}
				}
			}
		}
		else
		{
			pause_client_server_continuous_weapon_sound_effect (launcher, weapon_sub_type);
		}
	}
	else
	{
		if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
		{
			////////////////////////////////////////
			//
			// CLIENT/TX
			//
			////////////////////////////////////////

			ASSERT (weapon_index == ENTITY_INDEX_DONT_CARE);

			ASSERT (burst_size == BURST_SIZE_DONT_CARE);

			ASSERT (!smoke_trail_indices);

			set_force_local_entity_create_stack_attributes (FALSE);

			// NOTE: The clients' weapon counters lag the servers' so it is possible that the
			//       client may unknowingly attempt to create more weapons than are available.
			//       This is prone to happen during rapid firing.

			if (get_local_entity_weapon_available (launcher, weapon_sub_type))
			{
				transmit_entity_comms_message
				(
					ENTITY_COMMS_CREATE_WEAPON,
					NULL,
					launcher,
					weapon_sub_type,
					ENTITY_INDEX_DONT_CARE,
					burst_size,
					NULL
				);
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// CLIENT/RX
			//
			////////////////////////////////////////

			ASSERT (weapon_index != ENTITY_INDEX_DONT_CARE);

			ASSERT (burst_size > 0);

			set_force_local_entity_create_stack_attributes (TRUE);

			weapon = create_local_entity
			(
				ENTITY_TYPE_WEAPON,
				weapon_index,
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, weapon_sub_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_WEAPON_BURST_SIZE, burst_size),
				ENTITY_ATTR_PARENT (LIST_TYPE_LAUNCHED_WEAPON, launcher),
				ENTITY_ATTR_PARENT (LIST_TYPE_TARGET, target),
				ENTITY_ATTR_END
			);

			ASSERT (weapon);

			//
			// create smoke trail
			//

			smoke_trail_type = (meta_smoke_list_types) get_local_entity_int_value (weapon, INT_TYPE_WEAPON_SMOKE_TRAIL_TYPE);

			if (smoke_trail_type != META_SMOKE_LIST_TYPE_NONE)
			{
				struct OBJECT_3D_BOUNDS
					*bounding_box;

				vec3d
					exhaust_offset;

				ASSERT (smoke_trail_indices);

				bounding_box = get_object_3d_bounding_box (get_local_entity_int_value (weapon, INT_TYPE_DEFAULT_3D_SHAPE));

				if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT) ||(weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT))
				{
					exhaust_offset.x = 0.0;
					exhaust_offset.y = 0.0;
					exhaust_offset.z = 0.0;
				}
				else
				{
					exhaust_offset.x = 0.0;
					exhaust_offset.y = 0.0;
					exhaust_offset.z = bounding_box->zmin;
				}

				create_meta_smoke_list_specified_offset (smoke_trail_type, weapon, &exhaust_offset, smoke_trail_indices);
			}
			else
			{
				ASSERT (!smoke_trail_indices);
			}

			set_force_local_entity_create_stack_attributes (FALSE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void launch_client_server_weapon (entity *launcher, entity_sub_types weapon_sub_type, int salvo_count)
{
	int
		salvo_size;
	unsigned
		pods_firing;

	ASSERT (launcher);

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	//
	// prevent dead objects from firing (causes problems if the 3D object has been replaced with a destroyed object)
	//

	if (!get_local_entity_int_value (launcher, INT_TYPE_ALIVE))
	{
		return;
	}

	pods_firing = max(1, get_number_of_pods_firing(launcher, weapon_sub_type));
	
	if (get_local_entity_int_value (launcher, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		salvo_size = get_local_entity_weapon_salvo_size (launcher, weapon_sub_type);
	}
	else
	{
		if (weapon_database[weapon_sub_type].weapon_class & (WEAPON_CLASS_DECOY | WEAPON_CLASS_CARGO | WEAPON_CLASS_DEBRIS))
		{
			salvo_size = get_local_entity_weapon_salvo_size (launcher, weapon_sub_type);
		}
		else
		{
			salvo_size = 1;
		}
	}

	ASSERT (salvo_size > 0);
	ASSERT (salvo_count >= 0);

	while (salvo_size--)
	{
		if (get_local_entity_int_value (launcher, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
			salvo_count = salvo_size;
		
		salvo_count /= pods_firing;
		
		create_client_server_entity_weapon (launcher, weapon_sub_type, ENTITY_INDEX_DONT_CARE, BURST_SIZE_DONT_CARE, NULL, salvo_count);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_entity_submunition_weapon (entity *launcher, entity *target, entity_sub_types weapon_sub_type, int weapon_index, viewpoint *vp, float velocity)
{
	entity
		*force,
		*weapon;

	ASSERT (launcher);
	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	weapon_viewpoint = vp;
	weapon_velocity = velocity;
	
	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		////////////////////////////////////////
		//
		// SERVER/TX and SERVER/RX
		//
		////////////////////////////////////////

		ASSERT (weapon_index == ENTITY_INDEX_DONT_CARE);

		if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
		{
			set_force_local_entity_create_stack_attributes (TRUE);
		}
		//
		// create weapon
		//

		weapon = create_local_entity
		(
			ENTITY_TYPE_WEAPON,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, weapon_sub_type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_WEAPON_BURST_SIZE, 1),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_WEAPON_MISSILE_PHASE, MISSILE_PHASE1),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_LOCK_ON_AFTER_LAUNCH, FALSE),
			ENTITY_ATTR_PARENT (LIST_TYPE_LAUNCHED_WEAPON, launcher),
			ENTITY_ATTR_PARENT (LIST_TYPE_TARGET, target),
			ENTITY_ATTR_END
		);

		if (weapon)
		{
			//
			// send FIRE message to force (unless it's a decoy/cargo/debris being launched)
			//

			if ((target) && (!(weapon_database[weapon_sub_type].weapon_class & (WEAPON_CLASS_DECOY | WEAPON_CLASS_CARGO | WEAPON_CLASS_DEBRIS))))
			{
				force = get_local_force_entity ((entity_sides) get_local_entity_int_value (target, INT_TYPE_SIDE));

				if (force)
				{
					notify_local_entity (ENTITY_MESSAGE_ENTITY_FIRED_AT, force, launcher, target);
				}
			}

			transmit_entity_comms_message
			(
				ENTITY_COMMS_CREATE_WEAPON,
				NULL,
				launcher,
				weapon_sub_type,
				get_local_entity_safe_index (weapon),
				1,
				0
			);
		}

		set_force_local_entity_create_stack_attributes (FALSE);
	}
/*	else
	{
		if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
		{
			////////////////////////////////////////
			//
			// CLIENT/TX
			//
			////////////////////////////////////////

			ASSERT (weapon_index == ENTITY_INDEX_DONT_CARE);

			// NOTE: The clients' weapon counters lag the servers' so it is possible that the
			//       client may unknowingly attempt to create more weapons than are available.
			//       This is prone to happen during rapid firing.

			transmit_entity_comms_message
			(
				ENTITY_COMMS_CREATE_WEAPON,
				NULL,
				launcher,
				weapon_sub_type,
				ENTITY_INDEX_DONT_CARE,
				1,
				NULL
			);
		}
		else
		{
			////////////////////////////////////////
			//
			// CLIENT/RX
			//
			////////////////////////////////////////

			ASSERT (weapon_index != ENTITY_INDEX_DONT_CARE);

			set_force_local_entity_create_stack_attributes (TRUE);

			weapon = create_local_entity
			(
				ENTITY_TYPE_WEAPON,
				weapon_index,
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, weapon_sub_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_WEAPON_BURST_SIZE, 1),
				ENTITY_ATTR_PARENT (LIST_TYPE_LAUNCHED_WEAPON, launcher),
				ENTITY_ATTR_PARENT (LIST_TYPE_TARGET, target),
				ENTITY_ATTR_END
			);

			ASSERT (weapon);

			set_force_local_entity_create_stack_attributes (FALSE);
		}
	}*/
	
	weapon_velocity = 0;
}
