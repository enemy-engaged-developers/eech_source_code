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

void pack_aircraft_data (entity *en, aircraft *raw, pack_modes mode)
{
	int
		package;

	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			//
			// pack mobile data
			//

			pack_mobile_data (en, &raw->mob, mode);

			//
			// pack aircraft data
			//

			pack_int_value (en, INT_TYPE_OBJECT_3D_SHAPE, raw->object_3d_shape);

			// inst3d

			/////////////////////////////////////////////////////////////////
			if (mode == PACK_MODE_CLIENT_SESSION)
			{
				if (raw->aircrew_root.first_child)
				{
					pack_int_value (en, INT_TYPE_VALID, TRUE);
	
					pack_list_root (en, LIST_TYPE_AIRCREW, &raw->aircrew_root);
				}
				else
				{
					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (mode == PACK_MODE_SERVER_SESSION)
			{
				if (raw->task_dependent_root.first_child)
				{
					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_list_root (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_root);
				}
				else
				{
					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->launched_weapon_root.first_child)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_LAUNCHED_WEAPON, &raw->launched_weapon_root);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (raw->movement_dependent_root.first_child)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_root (en, LIST_TYPE_MOVEMENT_DEPENDENT, &raw->movement_dependent_root);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			pack_list_link (en, LIST_TYPE_FOLLOWER, &raw->follower_link);

			// gunship_target_link

			pack_list_link (en, LIST_TYPE_MEMBER, &raw->member_link);

			// view_link

			if (mode == PACK_MODE_SERVER_SESSION)
			{

				pack_list_link (en, LIST_TYPE_TAKEOFF_QUEUE, &raw->takeoff_queue_link);
			}

			/////////////////////////////////////////////////////////////////
			if (raw->movement_dependent_link.parent)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_link (en, LIST_TYPE_MOVEMENT_DEPENDENT, &raw->movement_dependent_link);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}
			/////////////////////////////////////////////////////////////////

			pack_int_value (en, INT_TYPE_OPERATIONAL_STATE, raw->operational_state);

			if (mode == PACK_MODE_SERVER_SESSION)
			{
				pack_float_value (en, FLOAT_TYPE_DISTANCE, raw->distance);	// only needed by server?
			}

			if (raw->operational_state == OPERATIONAL_STATE_LANDED)
			{

				pack_float_value (en, FLOAT_TYPE_LOADING_DOOR_STATE, raw->loading_door_state);
			}

			pack_float_value (en, FLOAT_TYPE_CARGO_DOOR_STATE, raw->cargo_door_state);

			if (mode == PACK_MODE_SERVER_SESSION)
			{
				pack_float_value (en, FLOAT_TYPE_DEATH_TIMER, raw->death_timer);

				pack_float_value (en, FLOAT_TYPE_TARGET_SCAN_TIMER, raw->target_scan_timer);
			}

			pack_float_value (en, FLOAT_TYPE_UNDERCARRIAGE_STATE, raw->undercarriage_state);

			// view_interest_level

			// weapon_burst_timer

			pack_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE, raw->weapon_system_ready_state);

			if (mode == PACK_MODE_SERVER_SESSION)
			{
				pack_float_value (en, FLOAT_TYPE_DECOY_RELEASE_TIMER, raw->decoy_release_timer);
			}

			// air_radar_contact_timeout

			////////////////////////////////////////

			pack_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE, raw->weapon_config_type);

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[raw->weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					break;
				}

				pack_int_value (en, INT_TYPE_WEAPON_PACKAGE_NUMBER, raw->weapon_package_status_array[package].number);

				pack_int_value (en, INT_TYPE_WEAPON_PACKAGE_DAMAGED, raw->weapon_package_status_array[package].damaged);

				if (weapon_config_database[raw->weapon_config_type][package].rotate)
				{
					pack_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_HEADING, raw->weapon_package_status_array[package].weapon_system_heading);

					pack_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_PITCH, raw->weapon_package_status_array[package].weapon_system_pitch);
				}

				// muzzle_flash_timer
			}

			pack_int_value (en, INT_TYPE_SELECTED_WEAPON, raw->selected_weapon);

			////////////////////////////////////////

			// sound_effect_data

			pack_int_value (en, INT_TYPE_FORMATION_POSITION, raw->formation_position);

			// valid_sound_effect

			// selected_weapon_system_ready

			// weapon_and_target_vectors_valid

			// gunship_radar_los_clear

			if (mode == PACK_MODE_CLIENT_SESSION)
			{
				pack_int_value (en, INT_TYPE_LIGHTS_ON, raw->lights_on);
			}

			// cpg_identified

			pack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER, raw->group_member_number);

			// id_number_significant_digits

			pack_int_value (en, INT_TYPE_EJECTED, raw->ejected);

			pack_int_value (en, INT_TYPE_DAMAGE_LEVEL, raw->damage_level);

			// id_number

			// weapon_vector

			// weapon_to_target_vector

			// terrain_info

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
			//
			// cannot update entity at this level as the update may not apply to all entity types below
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_aircraft_data (entity *en, aircraft *raw, pack_modes mode)
{

	int
		package;

	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			//
			// unpack mobile data
			//

			unpack_mobile_data (en, &raw->mob, mode);

			//
			// unpack aircraft data
			//

			raw->object_3d_shape = unpack_int_value (en, INT_TYPE_OBJECT_3D_SHAPE);

			raw->inst3d = construct_3d_object (raw->object_3d_shape);

			/////////////////////////////////////////////////////////////////
			if (mode == PACK_MODE_CLIENT_SESSION)
			{
				if (unpack_int_value (en, INT_TYPE_VALID))
				{
					unpack_list_root (en, LIST_TYPE_AIRCREW, &raw->aircrew_root);
				}
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (mode == PACK_MODE_SERVER_SESSION)
			{
				if (unpack_int_value (en, INT_TYPE_VALID))
				{
					unpack_list_root (en, LIST_TYPE_TASK_DEPENDENT, &raw->task_dependent_root);
				}
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_LAUNCHED_WEAPON, &raw->launched_weapon_root);
			}
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_root (en, LIST_TYPE_MOVEMENT_DEPENDENT, &raw->movement_dependent_root);
			}
			/////////////////////////////////////////////////////////////////

			unpack_list_link (en, LIST_TYPE_FOLLOWER, &raw->follower_link);

			// gunship_target_link

			unpack_list_link (en, LIST_TYPE_MEMBER, &raw->member_link);

			// view_link

			if (mode == PACK_MODE_SERVER_SESSION)
			{

				unpack_list_link (en, LIST_TYPE_TAKEOFF_QUEUE, &raw->takeoff_queue_link);
			}

			/////////////////////////////////////////////////////////////////
			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				unpack_list_link (en, LIST_TYPE_MOVEMENT_DEPENDENT, &raw->movement_dependent_link);
			}

			raw->operational_state = unpack_int_value (en, INT_TYPE_OPERATIONAL_STATE);

			if (mode == PACK_MODE_SERVER_SESSION)
			{
				raw->distance = unpack_float_value (en, FLOAT_TYPE_DISTANCE);	// only needed by server?
			}

			if (raw->operational_state == OPERATIONAL_STATE_LANDED)
			{

				raw->loading_door_state = unpack_float_value (en, FLOAT_TYPE_LOADING_DOOR_STATE);
			}

			raw->cargo_door_state = unpack_float_value (en, FLOAT_TYPE_CARGO_DOOR_STATE);

			if (mode == PACK_MODE_SERVER_SESSION)
			{
				raw->death_timer = unpack_float_value (en, FLOAT_TYPE_DEATH_TIMER);

				raw->target_scan_timer = unpack_float_value (en, FLOAT_TYPE_TARGET_SCAN_TIMER);
			}

			raw->undercarriage_state = unpack_float_value (en, FLOAT_TYPE_UNDERCARRIAGE_STATE);

			// view_interest_level

			// weapon_burst_timer

			raw->weapon_system_ready_state = unpack_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE);

			if (mode == PACK_MODE_SERVER_SESSION)
			{
				raw->decoy_release_timer = unpack_float_value (en, FLOAT_TYPE_DECOY_RELEASE_TIMER);
			}

			raw->air_radar_contact_timeout = AIR_RADAR_CONTACT_TIMEOUT_INVALID;

			////////////////////////////////////////

			raw->weapon_config_type = (weapon_config_types) unpack_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

			raw->weapon_package_status_array = (weapon_package_status *) malloc_fast_mem (SIZE_WEAPON_PACKAGE_STATUS_ARRAY);

			memset (raw->weapon_package_status_array, 0, SIZE_WEAPON_PACKAGE_STATUS_ARRAY);

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[raw->weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					break;
				}

				raw->weapon_package_status_array[package].number = unpack_int_value (en, INT_TYPE_WEAPON_PACKAGE_NUMBER);

				raw->weapon_package_status_array[package].damaged = unpack_int_value (en, INT_TYPE_WEAPON_PACKAGE_DAMAGED);

				if (weapon_config_database[raw->weapon_config_type][package].rotate)
				{
					raw->weapon_package_status_array[package].weapon_system_heading = unpack_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_HEADING);

					raw->weapon_package_status_array[package].weapon_system_pitch = unpack_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_PITCH);
				}

				// muzzle_flash_timer
			}

			reset_entity_weapon_config_animation (en);

			raw->selected_weapon = unpack_int_value (en, INT_TYPE_SELECTED_WEAPON);

			////////////////////////////////////////

			// sound_effect_data

			raw->formation_position = unpack_int_value (en, INT_TYPE_FORMATION_POSITION);

			// valid_sound_effect

			// selected_weapon_system_ready

			// weapon_and_target_vectors_valid

			// gunship_radar_los_clear

			if (mode == PACK_MODE_CLIENT_SESSION)
			{
				raw->lights_on = unpack_int_value (en, INT_TYPE_LIGHTS_ON);
			}

			// cpg_identified

			raw->group_member_number = unpack_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);

			// id_number_significant_digits

			raw->ejected = unpack_int_value (en, INT_TYPE_EJECTED);

			raw->damage_level = unpack_int_value (en, INT_TYPE_DAMAGE_LEVEL);

			// id_number

			raw->weapon_vector.x = 0.0;
			raw->weapon_vector.y = 0.0;
			raw->weapon_vector.z = 1.0;

			raw->weapon_to_target_vector.x = 0.0;
			raw->weapon_to_target_vector.y = 0.0;
			raw->weapon_to_target_vector.z = -1.0;

			// terrain_info

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
			//
			// cannot update entity at this level as the update may not apply to all entity types below
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
