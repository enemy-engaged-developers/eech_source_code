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

static entity *create_local (entity_types type, int index, char *pargs)
{
	entity
		*en = nullptr;

	routed_vehicle
		*raw = nullptr;

	entity_sub_types
		group_sub_type;

	float
		heading;

	vec3d
		*face_normal = nullptr;

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

		raw = (routed_vehicle *) malloc_fast_mem (sizeof (routed_vehicle));

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

		memset (raw, 0, sizeof (routed_vehicle));

		//
		// mobile
		//

		raw->vh.mob.sub_type = ENTITY_SUB_TYPE_UNINITIALISED;

		raw->vh.mob.position.x = MID_MAP_X;
		raw->vh.mob.position.y = MID_MAP_Y;
		raw->vh.mob.position.z = MID_MAP_Z;

		get_identity_matrix3x3 (raw->vh.mob.attitude);

		raw->vh.mob.alive = TRUE;

		raw->vh.mob.side = ENTITY_SIDE_UNINITIALISED;

		raw->vh.operational_state = OPERATIONAL_STATE_UNKNOWN;

		//
		// vehicle
		//

		raw->vh.object_3d_shape = OBJECT_3D_INVALID_OBJECT_INDEX;

		raw->vh.weapon_config_type = WEAPON_CONFIG_TYPE_UNINITIALISED;

		raw->vh.selected_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

		raw->vh.weapon_vector.x = 0.0;
		raw->vh.weapon_vector.y = 0.0;
		raw->vh.weapon_vector.z = 1.0;

		raw->vh.weapon_to_target_vector.x = 0.0;
		raw->vh.weapon_to_target_vector.y = 0.0;
		raw->vh.weapon_to_target_vector.z = -1.0;

		raw->vh.weapon_to_intercept_point_vector.x = 0.0;
		raw->vh.weapon_to_intercept_point_vector.y = 0.0;
		raw->vh.weapon_to_intercept_point_vector.z = -1.0;

		raw->vh.weapon_to_intercept_point_range = 0.0;
		
		raw->vh.loading_door_state = VEHICLE_LOADING_DOORS_OPEN_FLOAT_VALUE;

		//
		// routed
		//

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

		ASSERT (raw->vh.member_link.parent);

		ASSERT (get_local_entity_type (raw->vh.member_link.parent) == ENTITY_TYPE_GROUP);

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		raw->sub_route = NULL;

		//
		// side
		//

		if (raw->vh.mob.side == ENTITY_SIDE_UNINITIALISED)
		{
			raw->vh.mob.side = get_local_entity_int_value (raw->vh.member_link.parent, INT_TYPE_SIDE);
		}

		ASSERT (raw->vh.mob.side != ENTITY_SIDE_NEUTRAL);

		//
		// sub_type
		//

		if (raw->vh.mob.sub_type == ENTITY_SUB_TYPE_UNINITIALISED)
		{
			group_sub_type = get_local_entity_int_value (raw->vh.member_link.parent, INT_TYPE_ENTITY_SUB_TYPE);

			if (raw->vh.mob.side == ENTITY_SIDE_BLUE_FORCE)
			{
				raw->vh.mob.sub_type = group_database[group_sub_type].default_blue_force_sub_type;
			}
			else
			{
				raw->vh.mob.sub_type = group_database[group_sub_type].default_red_force_sub_type;
			}
		}

		ASSERT (entity_sub_type_vehicle_valid (raw->vh.mob.sub_type));

		//
		// 3D shape
		//

		if (raw->vh.object_3d_shape == OBJECT_3D_INVALID_OBJECT_INDEX)
		{
			raw->vh.object_3d_shape = vehicle_database[raw->vh.mob.sub_type].default_3d_shape;
		}

		//
		// weapon config
		//

		if (raw->vh.weapon_config_type == WEAPON_CONFIG_TYPE_UNINITIALISED)
		{
			raw->vh.weapon_config_type = vehicle_database[raw->vh.mob.sub_type].default_weapon_config_type;
		}

		ASSERT (weapon_config_type_valid (raw->vh.weapon_config_type));

		//
		// damage levels
		//

		raw->vh.damage_level = vehicle_database[raw->vh.mob.sub_type].initial_damage_level;

		//
		// radar dish rotation (ok to use a random number as this is for visual effect only)
		//

		raw->vh.radar_rotation_state = frand1 ();

		////////////////////////////////////////
		//
		// BUILD COMPONENTS
		//
		////////////////////////////////////////

		//
		// 3D object
		//

		raw->vh.inst3d = construct_3d_object (raw->vh.object_3d_shape);

		set_routed_vehicle_id_number (en);

		set_initial_rotation_angle_of_routed_vehicle_wheels (raw->vh.inst3d);

		//
		// align with terrain
		//

		ASSERT(point_inside_map_area(&raw->vh.mob.position));

		get_3d_terrain_point_data (raw->vh.mob.position.x, raw->vh.mob.position.z, &raw->vh.terrain_info);

		heading = get_heading_from_attitude_matrix (raw->vh.mob.attitude);

		face_normal = get_3d_terrain_point_data_normal (&raw->vh.terrain_info);

		get_3d_transformation_matrix_from_face_normal_and_heading (raw->vh.mob.attitude, face_normal, heading);

		//
		// weapon config
		//

		raw->vh.weapon_package_status_array = (weapon_package_status *) malloc_fast_mem (SIZE_WEAPON_PACKAGE_STATUS_ARRAY);

		memset (raw->vh.weapon_package_status_array, 0, SIZE_WEAPON_PACKAGE_STATUS_ARRAY);

		load_local_entity_weapon_config (en);

		//
		// update force info
		//

		add_to_force_info (get_local_force_entity ((entity_sides) raw->vh.mob.side), en);

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_MEMBER, raw->vh.member_link.parent, raw->vh.member_link.child_pred);

		//
		// insert into LIST_TYPE_MEMBER before LIST_TYPE_VIEW
		//

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_VIEW, get_camera_entity (), get_local_entity_view_list_pred (en));

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->vh.mob.position), NULL);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

		if (tacview_is_logging())
			write_tacview_new_unit(en);
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
		*en = nullptr;

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
		*en = nullptr;

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

void overload_routed_vehicle_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_ROUTED_VEHICLE]		  								= create_local;

	fn_create_client_server_entity[ENTITY_TYPE_ROUTED_VEHICLE][COMMS_MODEL_SERVER]	= create_server;

	fn_create_client_server_entity[ENTITY_TYPE_ROUTED_VEHICLE][COMMS_MODEL_CLIENT]	= create_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_client_server_entity_routed_vehicle (int index, entity_sub_types sub_type, entity *group, vec3d *position)
{
	entity
		*new_entity = nullptr;

	sound_sample_indices
		sample_index;

	ASSERT (get_comms_model() == COMMS_MODEL_SERVER);

	//
	// create routed entity
	//

	new_entity = create_client_server_entity
	(
		ENTITY_TYPE_ROUTED_VEHICLE,
		index,
		ENTITY_ATTR_PARENT (LIST_TYPE_MEMBER, group),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
		ENTITY_ATTR_END
	);

	//
	// create and attach special effects
	//

	{
		//
		// dust trails
		//

		attach_routed_vehicle_meta_smoke_lists (new_entity);

		//
		// headlights
		//

		set_vehicle_headlight_state (new_entity, OFF);

		//
		// sound effects
		//

		sample_index = vehicle_database [sub_type].idle_sound_effect;

		if (sample_index != SOUND_SAMPLE_INDEX_NONE)
		{
			create_client_server_sound_effect_entity
			(
				new_entity,
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_ALL,
				NULL,												// position
				1.0,												// amplification
				1.0,												// Werewolf pitch
				TRUE,												// valid sound effect
				TRUE,												// looping
				1,													// sample count
				&sample_index									// sample index list
			);
		}

		sample_index = vehicle_database [sub_type].moving_sound_effect;

		if (sample_index != SOUND_SAMPLE_INDEX_NONE)
		{
			create_client_server_sound_effect_entity
			(
				new_entity,
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_ALL,
				NULL,												// position
				1.0,												// amplification
				1.0,												// Werewolf pitch
				FALSE,											// valid sound effect
				TRUE,												// looping
				1,													// sample count
				&sample_index									// sample index list
			);
		}
	}

	//
	//
	//

	return new_entity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_local_entity_routed_vehicle (int index, entity_sub_types sub_type, entity *group, vec3d *position)
{
	entity
		*new_entity = nullptr;

	ASSERT (get_comms_model() == COMMS_MODEL_SERVER);

	//
	// create routed entity
	//

	new_entity = create_local_entity
	(
		ENTITY_TYPE_ROUTED_VEHICLE,
		index,
		ENTITY_ATTR_PARENT (LIST_TYPE_MEMBER, group),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
		ENTITY_ATTR_END
	);

	//
	// create and attach special effects
	//

	//
	//
	//

	return new_entity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



