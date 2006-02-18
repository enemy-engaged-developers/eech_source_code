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

static void create_helicopter_cockpit_sound_effect (entity *en, entity_sub_types sub_type, sound_sample_indices sound_index);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_local (entity_types type, int index, char *pargs)
{
	entity
		*en;

	helicopter
		*raw;

	entity_sub_types
		group_sub_type;

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
		////////////////////////////////////////
   	//
   	// MALLOC ENTITY DATA
   	//
		////////////////////////////////////////

		set_local_entity_type (en, type);

		raw = malloc_fast_mem (sizeof (helicopter));

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

		memset (raw, 0, sizeof (helicopter));

		//
		// mobile
		//

		raw->ac.mob.sub_type = ENTITY_SUB_TYPE_UNINITIALISED;

		raw->ac.mob.position.x = MID_MAP_X;
		raw->ac.mob.position.y = MID_MAP_Y;
		raw->ac.mob.position.z = MID_MAP_Z;

		get_identity_matrix3x3 (raw->ac.mob.attitude);

		raw->ac.mob.alive = TRUE;

		raw->ac.mob.side = ENTITY_SIDE_UNINITIALISED;

		raw->ac.operational_state = OPERATIONAL_STATE_UNKNOWN;

		//
		// aircraft
		//

		raw->ac.object_3d_shape = OBJECT_3D_INVALID_OBJECT_INDEX;

		raw->ac.weapon_config_type = WEAPON_CONFIG_TYPE_UNINITIALISED;

		raw->ac.selected_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

		raw->ac.weapon_vector.x = 0.0;
		raw->ac.weapon_vector.y = 0.0;
		raw->ac.weapon_vector.z = 1.0;

		raw->ac.weapon_to_target_vector.x = 0.0;
		raw->ac.weapon_to_target_vector.y = 0.0;
		raw->ac.weapon_to_target_vector.z = -1.0;

		raw->ac.loading_door_state = AIRCRAFT_LOADING_DOORS_OPEN_FLOAT_VALUE;
		raw->ac.undercarriage_state = AIRCRAFT_UNDERCARRIAGE_DOWN_FLOAT_VALUE;

		raw->ac.air_radar_contact_timeout = AIR_RADAR_CONTACT_TIMEOUT_INVALID;

		//
		// helicopter
		//

		raw->main_rotor_rpm = 0.0;

		raw->player = ENTITY_PLAYER_AI;

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

		ASSERT (raw->ac.member_link.parent);

		ASSERT (get_local_entity_type (raw->ac.member_link.parent) == ENTITY_TYPE_GROUP);

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		raw->fuel_supply_level = aircraft_database [raw->ac.mob.sub_type].fuel_default_weight;

		//
		// side
		//

		if (raw->ac.mob.side == ENTITY_SIDE_UNINITIALISED)
		{
			raw->ac.mob.side = get_local_entity_int_value (raw->ac.member_link.parent, INT_TYPE_SIDE);
		}

		ASSERT (raw->ac.mob.side != ENTITY_SIDE_NEUTRAL);

		//
		// sub type
		//

		if (raw->ac.mob.sub_type == ENTITY_SUB_TYPE_UNINITIALISED)
		{
			group_sub_type = get_local_entity_int_value (raw->ac.member_link.parent, INT_TYPE_ENTITY_SUB_TYPE);

			if (raw->ac.mob.side == ENTITY_SIDE_BLUE_FORCE)
			{
				raw->ac.mob.sub_type = group_database[group_sub_type].default_blue_force_sub_type;
			}
			else
			{
				raw->ac.mob.sub_type = group_database[group_sub_type].default_red_force_sub_type;
			}
		}

		ASSERT (entity_sub_type_aircraft_valid (raw->ac.mob.sub_type));

		//
		// 3D shape
		//

		if (raw->ac.object_3d_shape == OBJECT_3D_INVALID_OBJECT_INDEX)
		{
			raw->ac.object_3d_shape = aircraft_database[raw->ac.mob.sub_type].default_3d_shape;
		}

		//
		// weapon config
		//

		if (raw->ac.weapon_config_type == WEAPON_CONFIG_TYPE_UNINITIALISED)
		{
			raw->ac.weapon_config_type = aircraft_database[raw->ac.mob.sub_type].default_weapon_config_type;
		}

		ASSERT (weapon_config_type_valid (raw->ac.weapon_config_type));

		//
		// damage levels
		//

		raw->ac.damage_level = aircraft_database[raw->ac.mob.sub_type].initial_damage_level;

		////////////////////////////////////////
		//
		// BUILD COMPONENTS
		//
		////////////////////////////////////////

		//
		// 3D object
		//

		raw->ac.inst3d = construct_3d_object (raw->ac.object_3d_shape);

		set_helicopter_id_number (en);

		if (get_local_entity_int_value (en, INT_TYPE_PLAYER_CONTROLLABLE))
		{
			deactivate_weapon_payload_markers (en);
		}

		#if RECOGNITION_GUIDE
		
		raw->ac.loading_door_state = AIRCRAFT_LOADING_DOORS_CLOSED_FLOAT_VALUE;

		#endif

		set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_TAKEOFF_ROUTE, FALSE);
		set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_LANDING_ROUTE, FALSE);

		//
		// vary main rotor start position (ok to use a random number as this is for visual effect only)
		//

		#if RECOGNITION_GUIDE

		set_rotation_angle_of_helicopter_main_rotors (raw->ac.inst3d, 0.0);

		set_rotation_angle_of_helicopter_tail_rotor (raw->ac.inst3d, 0.0);

		#else
		
		set_rotation_angle_of_helicopter_main_rotors (raw->ac.inst3d, sfrand1 () * PI);

		set_rotation_angle_of_helicopter_tail_rotor (raw->ac.inst3d, sfrand1 () * PI);

		#endif

		//
		// weapon config
		//

		raw->ac.weapon_package_status_array = malloc_fast_mem (SIZE_WEAPON_PACKAGE_STATUS_ARRAY);

		memset (raw->ac.weapon_package_status_array, 0, SIZE_WEAPON_PACKAGE_STATUS_ARRAY);

		load_local_entity_weapon_config (en);

		//
		// update force info
		//

		add_to_force_info (get_local_force_entity (raw->ac.mob.side), en);

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_MEMBER, raw->ac.member_link.parent, raw->ac.member_link.child_pred);

		//
		// insert into LIST_TYPE_MEMBER before LIST_TYPE_VIEW
		//

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_VIEW, get_camera_entity (), get_local_entity_view_list_pred (en));

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->ac.mob.position), NULL);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);
	}

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

void overload_helicopter_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_HELICOPTER]		  								= create_local;

	fn_create_client_server_entity[ENTITY_TYPE_HELICOPTER][COMMS_MODEL_SERVER]	= create_server;

	fn_create_client_server_entity[ENTITY_TYPE_HELICOPTER][COMMS_MODEL_CLIENT]	= create_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_client_server_entity_helicopter (int index, entity_sub_types sub_type, entity *group, vec3d *position)
{
	entity
		*new_entity;

	helicopter
		*raw;

	ASSERT (get_comms_model() == COMMS_MODEL_SERVER);

	//
	// create helicopter entity
	//

	new_entity = create_client_server_entity
	(
		ENTITY_TYPE_HELICOPTER,
		index,
		ENTITY_ATTR_PARENT (LIST_TYPE_MEMBER, group),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
		ENTITY_ATTR_END
	);

	//
	// create and attach special effects
	//

	create_helicopter_rotor_sound_effects (new_entity);

	{
		sound_sample_indices
			mca_effect_index,
			lock_on_effect_index,
			tracked_effect_index,
			locked_effect_index,
			incoming_effect_index;

		//
		// sound effects
		//

		mca_effect_index = SOUND_SAMPLE_INDEX_NONE;
		lock_on_effect_index = SOUND_SAMPLE_INDEX_NONE;
		tracked_effect_index = SOUND_SAMPLE_INDEX_NONE;
		locked_effect_index = SOUND_SAMPLE_INDEX_NONE;
		incoming_effect_index = SOUND_SAMPLE_INDEX_NONE;

		switch (sub_type)
		{
			case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_APACHE_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_APACHE_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
			case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_COMANCHE_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_COMANCHE_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
		////Moje 030527 start
			case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
		////Moje 030527 End
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_BLACKHAWK_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_BLACKHAWK_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
		////Moje 030816 start
			case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
		////Moje 030816 End
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_APACHE_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_APACHE_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
			case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_HAVOC_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_HAVOC_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
			case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_HOKUM_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_HOKUM_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
			////Moje 030612 line below added
			case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_HIND_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_HIND_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
			////Moje 030816 line below added
			case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
			{
				mca_effect_index = SOUND_SAMPLE_INDEX_HOKUM_MCA;
				lock_on_effect_index = SOUND_SAMPLE_INDEX_HOKUM_LOCK_ON;
				tracked_effect_index = SOUND_SAMPLE_INDEX_WARNING_TRACKED_BY_RADAR;
				locked_effect_index = SOUND_SAMPLE_INDEX_WARNING_LOCKED_BY_RADAR;
				incoming_effect_index = SOUND_SAMPLE_INDEX_WARNING_INCOMING_MISSILE;
				break;
			}
		}

		create_helicopter_cockpit_sound_effect (new_entity, ENTITY_SUB_TYPE_EFFECT_SOUND_MCA, mca_effect_index);
		create_helicopter_cockpit_sound_effect (new_entity, ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE, lock_on_effect_index);
		create_helicopter_cockpit_sound_effect (new_entity, ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_TRACKED, tracked_effect_index);
		create_helicopter_cockpit_sound_effect (new_entity, ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED, locked_effect_index);
		create_helicopter_cockpit_sound_effect (new_entity, ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING, incoming_effect_index);
	}

	//
	// initialise terrain elevation cache
	//

	raw = get_local_entity_data (new_entity);

	get_3d_terrain_point_data (position->x, position->z, &raw->ac.terrain_info);

	return new_entity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_helicopter_cockpit_sound_effect (entity *en, entity_sub_types sub_type, sound_sample_indices sound_index)
{
	int
		index;

	index = sound_index;

	if (index != SOUND_SAMPLE_INDEX_NONE)
	{
		create_client_server_sound_effect_entity
		(
			en,
			get_local_entity_int_value (en, INT_TYPE_SIDE),
			sub_type,
			SOUND_CHANNEL_SOUND_EFFECT,
			SOUND_LOCALITY_INTERIOR,
			NULL,												// position
			1.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			TRUE,												// looping
			1,													// sample count
			&index											// sample index list
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



