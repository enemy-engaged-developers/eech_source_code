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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

static void pack_local_data (entity *en, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		////////////////////////////////////////
		{
			helicopter
				*raw;

			raw = get_local_entity_data (en);

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack aircraft data
			//

			pack_aircraft_data (en, &raw->ac, mode);

			pack_float_value (en, FLOAT_TYPE_MEDIUM_VELOCITY, raw->ac.mob.velocity);

			//
			// pack helicopter data
			//

			pack_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, raw->fuel_supply_level);

			// invulnerable timer

			pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM, raw->main_rotor_rpm / 7.0);

			pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_PITCH, raw->main_rotor_pitch);

			pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_ROLL, raw->main_rotor_roll);

			pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE, raw->main_rotor_blade_coning_angle);

			pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER, raw->main_rotor_spin_up_timer);

			pack_float_value (en, FLOAT_TYPE_TAIL_ROTOR_RPM, raw->tail_rotor_rpm);

			/////////////////////////////////////////////////////////////////
			if (raw->helicopter_damage_flags)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_FLAGS, raw->helicopter_damage_flags);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			pack_int_value (en, INT_TYPE_AUTO_PILOT, raw->auto_pilot);

			pack_int_value (en, INT_TYPE_PLAYER, ENTITY_PLAYER_AI);

			pack_int_value (en, INT_TYPE_MAIN_ROTOR_DAMAGED, raw->main_rotor_damaged);

			pack_int_value (en, INT_TYPE_TAIL_ROTOR_DAMAGED, raw->tail_rotor_damaged);

			// los_to_target

			// radar_on

			// laser_on

			// infra_red_jammer_on

			// radar_jammer_on

			// weapons_hold

			// position_hold

			// lock_on_after_launch

			// gunship_target_root

			pack_vec3d (en, VEC3D_TYPE_COVER_POSITION, &raw->cover_position);

			// wait_position

			//
			// pack local only special effects
			//

			pack_mobile_local_sound_effects (en, mode);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			helicopter
				*raw;

			raw = get_local_entity_data (en);

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack aircraft data
			//

			pack_aircraft_data (en, &raw->ac, mode);

			if ((raw->ac.mob.velocity == 0.0) && (raw->main_rotor_rpm == 0.0))
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER, raw->main_rotor_spin_up_timer);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);

				pack_float_value (en, FLOAT_TYPE_MEDIUM_VELOCITY, raw->ac.mob.velocity);

				pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM, raw->main_rotor_rpm / 7.0);
			}

			//
			// pack helicopter data
			//

			pack_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, raw->fuel_supply_level);

			// invulnerable timer

			// main_rotor_pitch

			// main_rotor_roll

			// main_rotor_blade_coning_angle

			// tail_rotor_rpm

			/////////////////////////////////////////////////////////////////
			if (raw->helicopter_damage_flags)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_FLAGS, raw->helicopter_damage_flags);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			if (raw->player == ENTITY_PLAYER_LOCAL)
			{
				pack_int_value (en, INT_TYPE_PLAYER, ENTITY_PLAYER_REMOTE);
			}
			else
			{
				pack_int_value (en, INT_TYPE_PLAYER, raw->player);
			}

			if (raw->player != ENTITY_PLAYER_AI)
			{

				pack_int_value (en, INT_TYPE_AUTO_PILOT, raw->auto_pilot);

				pack_int_value (en, INT_TYPE_LOS_TO_TARGET, raw->los_to_target);

				pack_int_value (en, INT_TYPE_RADAR_ON, raw->radar_on);

				pack_int_value (en, INT_TYPE_LASER_ON, raw->laser_on);

				pack_int_value (en, INT_TYPE_INFRA_RED_JAMMER_ON, raw->infra_red_jammer_on);

				pack_int_value (en, INT_TYPE_RADAR_JAMMER_ON, raw->radar_jammer_on);

				pack_int_value (en, INT_TYPE_LOCK_ON_AFTER_LAUNCH, raw->lock_on_after_launch);
			}

			pack_int_value (en, INT_TYPE_MAIN_ROTOR_DAMAGED, raw->main_rotor_damaged);

			pack_int_value (en, INT_TYPE_TAIL_ROTOR_DAMAGED, raw->tail_rotor_damaged);

			pack_int_value (en, INT_TYPE_WEAPONS_HOLD, raw->weapons_hold);

			pack_int_value (en, INT_TYPE_POSITION_HOLD, raw->position_hold);

			// gunship_target_root

			// cover_position

			pack_vec3d (en, VEC3D_TYPE_WAIT_POSITION, &raw->wait_position);

			//
			// pack local only special effects
			//

			pack_mobile_local_sound_effects (en, mode);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			helicopter
				*raw;

			raw = get_local_entity_data (en);

			pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->ac.mob.position);

			pack_attitude_matrix (en, raw->ac.mob.attitude);

			pack_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->ac.mob.motion_vector);

			pack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM, raw->main_rotor_rpm / 7.0);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void unpack_local_data (entity *en, entity_types type, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		////////////////////////////////////////
		{
			int
				main_rotor_damaged,
				tail_rotor_damaged,
				index;

			helicopter
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = malloc_fast_mem (sizeof (helicopter));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (helicopter));

			//
			// unpack data aircraft (in exactly the same order as the data was packed)
			//

			unpack_aircraft_data (en, &raw->ac, mode);

			raw->ac.mob.velocity = unpack_float_value (en, FLOAT_TYPE_MEDIUM_VELOCITY);

			//
			// unpack helicopter data
			//

			raw->fuel_supply_level = unpack_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

			// invulnerable timer

			raw->main_rotor_rpm = (unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM) * 7);

			raw->main_rotor_pitch = unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_PITCH);

			raw->main_rotor_roll = unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_ROLL);

			raw->main_rotor_blade_coning_angle = unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE);

			raw->main_rotor_spin_up_timer = unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER);
			
			raw->tail_rotor_rpm = unpack_float_value (en, FLOAT_TYPE_TAIL_ROTOR_RPM);

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				raw->helicopter_damage_flags = unpack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_FLAGS);
			}
			/////////////////////////////////////////////////////////////////

			raw->auto_pilot = unpack_int_value (en, INT_TYPE_AUTO_PILOT);

			raw->player = unpack_int_value (en, INT_TYPE_PLAYER);

			main_rotor_damaged = unpack_int_value (en, INT_TYPE_MAIN_ROTOR_DAMAGED);

			tail_rotor_damaged = unpack_int_value (en, INT_TYPE_TAIL_ROTOR_DAMAGED);

			// los_to_target

			// radar_on

			// laser_on

			// infra_red_jammer_on

			// radar_jammer_on

			raw->weapons_hold = FALSE;

			raw->position_hold = FALSE;

			// lock_on_after_launch

			// gunship_target_root

			unpack_vec3d (en, VEC3D_TYPE_COVER_POSITION, &raw->cover_position);

			// wait_position

			//
			// unpack local only special effects
			//

			unpack_mobile_local_sound_effects (en, mode);

			/////////////////////////////////////////////////////////////////

			set_helicopter_id_number (en);

			if (main_rotor_damaged)
			{
				damage_helicopter_main_rotors (en);

				raw->main_rotor_damaged = TRUE;
			}

			if (tail_rotor_damaged)
			{
				damage_helicopter_tail_rotors (en);

				raw->tail_rotor_damaged = TRUE;
			}

			//
			// vary main rotor start position (ok to use a random number as this is for visual effect only)
			//

			set_rotation_angle_of_helicopter_main_rotors (raw->ac.inst3d, sfrand1 () * PI);

			set_rotation_angle_of_helicopter_tail_rotor (raw->ac.inst3d, sfrand1 () * PI);

			//
			// hide weapon loading specific sub-objects
			//

			if (get_local_entity_int_value (en, INT_TYPE_PLAYER_CONTROLLABLE))
			{
				deactivate_weapon_payload_markers (en);
			}

			set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_TAKEOFF_ROUTE, FALSE);
			set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_LANDING_ROUTE, FALSE);

			//
			// link into system
			//

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_VIEW, get_camera_entity (), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->ac.mob.position), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

			add_to_force_info (get_local_force_entity (raw->ac.mob.side), en);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			int
				main_rotor_damaged,
				tail_rotor_damaged,
				index;

			helicopter
				*raw;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = malloc_fast_mem (sizeof (helicopter));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (helicopter));

			//
			// unpack data aircraft (in exactly the same order as the data was packed)
			//

			unpack_aircraft_data (en, &raw->ac, mode);

			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				raw->ac.mob.velocity = 0.0;

				raw->main_rotor_rpm = 0.0;

				raw->main_rotor_spin_up_timer = unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER);
			}
			else
			{

				raw->ac.mob.velocity = unpack_float_value (en, FLOAT_TYPE_MEDIUM_VELOCITY);

				raw->main_rotor_rpm = (unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM) * 7);

				raw->main_rotor_spin_up_timer = 0.0;
			}

			//
			// unpack helicopter data
			//

			raw->fuel_supply_level = unpack_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

			// invulnerable timer

			// main_rotor_pitch

			// main_rotor_roll

			// main_rotor_blade_coning_angle

			raw->tail_rotor_rpm = raw->main_rotor_rpm;

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				raw->helicopter_damage_flags = unpack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_FLAGS);
			}
			/////////////////////////////////////////////////////////////////

			raw->player = unpack_int_value (en, INT_TYPE_PLAYER);

			if (raw->player != ENTITY_PLAYER_AI)
			{

				raw->auto_pilot = unpack_int_value (en, INT_TYPE_AUTO_PILOT);

				raw->los_to_target = unpack_int_value (en, INT_TYPE_LOS_TO_TARGET);

				raw->radar_on = unpack_int_value (en, INT_TYPE_RADAR_ON);

				raw->laser_on = unpack_int_value (en, INT_TYPE_LASER_ON);

				raw->infra_red_jammer_on = unpack_int_value (en, INT_TYPE_INFRA_RED_JAMMER_ON);

				raw->radar_jammer_on = unpack_int_value (en, INT_TYPE_RADAR_JAMMER_ON);

				raw->lock_on_after_launch = unpack_int_value (en, INT_TYPE_LOCK_ON_AFTER_LAUNCH);
			}

			main_rotor_damaged = unpack_int_value (en, INT_TYPE_MAIN_ROTOR_DAMAGED);

			tail_rotor_damaged = unpack_int_value (en, INT_TYPE_TAIL_ROTOR_DAMAGED);

			raw->weapons_hold = unpack_int_value (en, INT_TYPE_WEAPONS_HOLD);

			raw->position_hold = unpack_int_value (en, INT_TYPE_POSITION_HOLD);

			// gunship_target_root

			// cover_position

			unpack_vec3d (en, VEC3D_TYPE_WAIT_POSITION, &raw->wait_position);

			//
			// unpack local only special effects
			//

			unpack_mobile_local_sound_effects (en, mode);

			/////////////////////////////////////////////////////////////////

			set_helicopter_id_number (en);

			if (main_rotor_damaged)
			{
				damage_helicopter_main_rotors (en);

				raw->main_rotor_damaged = TRUE;
			}

			if (tail_rotor_damaged)
			{
				damage_helicopter_tail_rotors (en);

				raw->tail_rotor_damaged = TRUE;
			}

			//
			// vary main rotor start position (ok to use a random number as this is for visual effect only)
			//

			set_rotation_angle_of_helicopter_main_rotors (raw->ac.inst3d, sfrand1 () * PI);

			set_rotation_angle_of_helicopter_tail_rotor (raw->ac.inst3d, sfrand1 () * PI);

			//
			// hide weapon loading specific sub-objects
			//

			if (get_local_entity_int_value (en, INT_TYPE_PLAYER_CONTROLLABLE))
			{
				deactivate_weapon_payload_markers (en);
			}

			set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_TAKEOFF_ROUTE, FALSE);
			set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_LANDING_ROUTE, FALSE);

			//
			// link into system
			//

			add_to_force_info (get_local_force_entity (raw->ac.mob.side), en);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_VIEW, get_camera_entity (), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->ac.mob.position), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			vec3d
				position,
				motion_vector;

			matrix3x3
				attitude;

			float
				velocity,
				main_rotor_rpm,
				main_rotor_blade_coning_angle,
				tail_rotor_rpm;

			velocity = 0;

			//
			// unpack all data (even if the echoed data is to be ignored)
			//

			unpack_vec3d (en, VEC3D_TYPE_POSITION, &position);

			unpack_attitude_matrix (en, attitude);

			unpack_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &motion_vector);

			if (!check_zero_3d_vector (&motion_vector))
			{

				vec3d
					normalised_motion_vector;

				normalised_motion_vector = motion_vector;

				normalise_3d_vector (&normalised_motion_vector);

				velocity = get_3d_vector_magnitude (&motion_vector) *
									(normalised_motion_vector.x * attitude [2][0] +
									normalised_motion_vector.y * attitude [2][1] +
									normalised_motion_vector.z * attitude [2][2]);
			}

			main_rotor_rpm = (unpack_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM) * 7);

			main_rotor_blade_coning_angle = rad ((((max_coning_angle - min_coning_angle) / 100.0) * main_rotor_rpm) - min_coning_angle);

			tail_rotor_rpm = main_rotor_rpm;

			//
			// the local player always ignores its echoed data
			//

			if (en != get_gunship_entity ())
			{
				//
				// always use access functions to set the data
				//

				set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &position);

				set_local_entity_attitude_matrix (en, attitude);

				set_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &motion_vector);

				set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, velocity);

				set_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM, main_rotor_rpm);

			 	set_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE, main_rotor_blade_coning_angle);

				set_local_entity_float_value (en, FLOAT_TYPE_TAIL_ROTOR_RPM, tail_rotor_rpm);
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_helicopter_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_HELICOPTER]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_HELICOPTER]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_gunship_entity (pack_modes mode)
{

	if (mode != PACK_MODE_SERVER_SESSION)
	{

		return;
	}

	// gunship

	if (get_gunship_entity ())
	{

		ASSERT (get_local_entity_type (get_gunship_entity ()) == ENTITY_TYPE_HELICOPTER);

		pack_int_value (get_gunship_entity (), INT_TYPE_VALID, TRUE);

		pack_entity_safe_ptr (get_gunship_entity ());
	}
	else
	{

		pack_int_value (get_gunship_entity (), INT_TYPE_VALID, FALSE);
	}

	// base keysite
/*
	if (get_base_current_keysite ())
	{

		pack_int_value (get_gunship_entity (), INT_TYPE_VALID, TRUE);

		pack_entity_safe_ptr (get_base_current_keysite ());
	}
	else
	*/
	{

		pack_int_value (get_gunship_entity (), INT_TYPE_VALID, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_gunship_entity (pack_modes mode)
{

	entity
		*ks,
		*gs;

	if (mode != PACK_MODE_SERVER_SESSION)
	{

		return;
	}

	// gunship entity

	if (unpack_int_value (NULL, INT_TYPE_VALID))
	{

		gs = unpack_entity_safe_ptr ();

		ASSERT (get_local_entity_type (gs) == ENTITY_TYPE_HELICOPTER);

		set_raw_gunship_entity (gs);
	}

	// current base keysite

	if (unpack_int_value (NULL, INT_TYPE_VALID))
	{

		ks = unpack_entity_safe_ptr ();

		if (get_global_gunship_side () == get_local_entity_int_value (ks, INT_TYPE_SIDE))
		{

			//set_base_current_keysite (ks);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_helicopter_delta_rotor_direction (entity *en)
{

	ASSERT (en);

	if (get_gunship_entity () == en)
	{

		if (current_flight_dynamics)
		{

			if (current_flight_dynamics->main_rotor_rpm.delta < 0.0)
			{

				return -1;
			}
			else if (current_flight_dynamics->main_rotor_rpm.delta > 0.0)
			{

				return 1;
			}
		}
	}
	else
	{

		//return get_local_entity_int_value (en, INT_TYPE_DELTA_ROTOR_DIRECTION);
		return 1;
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
