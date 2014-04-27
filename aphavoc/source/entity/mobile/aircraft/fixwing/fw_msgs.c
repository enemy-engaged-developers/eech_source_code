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

#if DEBUG_MODULE

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

// WARNING: THIS IS OVERLOADED AT AIRCRAFT LEVEL //

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

// WARNING: THIS IS OVERLOADED AT AIRCRAFT LEVEL //

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_collision (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*force,
		*enemy_force,
		*aggressor;

	int
		total_damage_level;

	aircraft_damage_types
		old_damage_state,
		new_damage_state;

	float
		damage_modifier;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	damage_modifier = va_arg (pargs, double);

	if (sender)
	{
		if (get_local_entity_type (sender) == ENTITY_TYPE_WEAPON)
		{
			aggressor = get_local_entity_parent (sender, LIST_TYPE_LAUNCHED_WEAPON);
		}
		else
		{
			aggressor = sender;
		}
	}
	else
	{
		aggressor = NULL;
	}

	force = get_local_force_entity ((entity_sides) get_local_entity_int_value (receiver, INT_TYPE_SIDE));

	enemy_force = get_local_force_entity (get_enemy_side (get_local_entity_int_value (receiver, INT_TYPE_SIDE)));

	//
	// assess damage
	//

	old_damage_state = aircraft_critically_damaged (receiver);

	damage_client_server_entity (receiver, sender, damage_modifier);

	total_damage_level = get_local_entity_int_value (receiver, INT_TYPE_DAMAGE_LEVEL);

	new_damage_state = aircraft_critically_damaged (receiver);

	/////////////////////////////////////////////////////////////////
	//
	// credit kill
	//
	/////////////////////////////////////////////////////////////////

	if ((aggressor) && (old_damage_state == AIRCRAFT_DAMAGE_NONE) && (new_damage_state > AIRCRAFT_DAMAGE_NONE))
	{
		credit_client_server_mobile_kill (receiver, aggressor);
	}

	/////////////////////////////////////////////////////////////////
	//
	// Assess damage caused
	//
	/////////////////////////////////////////////////////////////////

	if (total_damage_level <= 0)
	{

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, force, receiver, aggressor);

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, enemy_force, receiver, aggressor);

		kill_client_server_entity (receiver);

		if (aggressor)
		{
			play_aircraft_destroyed_speech (receiver, aggressor);
		}
	}
	else
	{

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR GETTING_SHOT
		//
		/////////////////////////////////////////////////////////////////

		if (aggressor)
		{
			play_aircraft_shot_at_speech (receiver, aggressor);
		}

		/////////////////////////////////////////////////////////////////
		//
		//
		/////////////////////////////////////////////////////////////////

		//notify hit. ?
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_lift_off_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	debug_log ("FW_MSGS: switching to navigating state");

	#endif

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{

		ASSERT (get_local_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_TAXIING);

		set_client_server_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF);

		write_tacview_unit_event(receiver, TACVIEW_UNIT_TOOK_OFF, NULL);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_start_up_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	debug_log ("FW_MSGS: switching to navigating state");

	#endif

	set_client_server_fixed_wing_afterburner_state (receiver, ON);

	open_client_server_entity_flaps( receiver );

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR PROCEEDING TO TAKEOFF
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_touch_down_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	debug_log ("FW_MSGS: switching to taxiing state");

	#endif

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		set_client_server_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAXIING);

		open_client_server_entity_airbrakes( receiver );

		close_client_server_entity_flaps( receiver );

		write_tacview_unit_event(receiver, TACVIEW_UNIT_LANDED, NULL);

		//
		// sound effect
		//
		{
			vec3d
				*position;

			sound_sample_indices
				sound_sample_index;

			#if DEBUG_MODULE

			debug_log_entity_message (message, receiver, sender, pargs);

			#endif

			position = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION);

			sound_sample_index = SOUND_SAMPLE_INDEX_JET_TOUCHDOWN_SCREECH;

			create_client_server_sound_effect_entity
			(
				receiver,
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_ALL,
				NULL,												// position
				1.0,												// amplification
				1.0,												// Werewolf pitch
				TRUE,												// valid sound effect
				FALSE,											// looping
				1,													// sample count
				&sound_sample_index							// sample index list
			);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_check_mobile_reached_guide (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	float
		range,
		velocity;

	vec3d
		*pos1,
		pos2,
		guide_pos,
		*mv;

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GUIDE);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// Check if landed
	//

	if (get_local_entity_int_value (receiver, INT_TYPE_LANDED))
	{
		return FALSE;
	}

	//
	// check range to guide
	//

	if (get_guide_criteria_valid (sender, GUIDE_CRITERIA_RADIUS))
	{
		range = get_local_entity_float_value (receiver, FLOAT_TYPE_DISTANCE);

		velocity = get_local_entity_float_value (receiver, FLOAT_TYPE_VELOCITY);

		//
		// Early-out checks
		//

		if ((range - velocity) > get_guide_criteria_value (sender, GUIDE_CRITERIA_RADIUS))
		{
			return FALSE;
		}

		if (range <= get_guide_criteria_value (sender, GUIDE_CRITERIA_RADIUS))
		{
		}
		else
		{
			//
			// Pass through check
			//

			mv = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_MOTION_VECTOR);

			pos1 = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION);

			if (get_local_entity_int_value (receiver, INT_TYPE_UPDATED))
			{
				pos2.x = pos1->x - (mv->x * get_delta_time ());
				pos2.y = pos1->y - (mv->y * get_delta_time ());
				pos2.z = pos1->z - (mv->z * get_delta_time ());
			}
			else
			{
				pos2.x = pos1->x + (mv->x * get_delta_time ());
				pos2.y = pos1->y + (mv->y * get_delta_time ());
				pos2.z = pos1->z + (mv->z * get_delta_time ());
			}

			get_local_entity_vec3d (receiver, VEC3D_TYPE_GUIDE_POSITION, &guide_pos);

			range = get_3d_perp_dist_of_point_from_line (pos1, &pos2, &guide_pos, NULL);

			if (range > get_guide_criteria_value (sender, GUIDE_CRITERIA_RADIUS))
			{
				return FALSE;
			}
		}
	}

	//
	// check weapon vector
	//

	if (get_guide_criteria_valid (sender, GUIDE_CRITERIA_WEAPON_VECTOR))
	{
		entity_sub_types
			selected_weapon;

		vec3d
			*weapon_vector,
			*weapon_to_target_vector;

		float
			launch_angle_error;

		selected_weapon = get_local_entity_int_value (receiver, INT_TYPE_SELECTED_WEAPON);

		ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

		if (get_local_entity_int_value (receiver, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
		{
			weapon_vector = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_WEAPON_VECTOR);

			ASSERT (weapon_vector);

			weapon_to_target_vector = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);

			ASSERT (weapon_to_target_vector);

			launch_angle_error = acos (get_3d_unit_vector_dot_product (weapon_vector, weapon_to_target_vector));

			if (fabs (launch_angle_error) > weapon_database[selected_weapon].max_launch_angle_error)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_fixed_wing_message_responses (void)
{
	overload_aircraft_message_responses (ENTITY_TYPE_FIXED_WING);

	#if DEBUG_MODULE

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_LINK_CHILD]		= response_to_link_child;

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_UNLINK_CHILD]	= response_to_unlink_child;

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_LINK_PARENT]	= response_to_link_parent;

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_UNLINK_PARENT]	= response_to_unlink_parent;

	#endif

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_COLLISION]							= response_to_collision;

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_WAYPOINT_LIFT_OFF_REACHED]		= response_to_waypoint_lift_off_reached;

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_WAYPOINT_START_UP_REACHED]		= response_to_waypoint_start_up_reached;

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_WAYPOINT_TOUCH_DOWN_REACHED]	= response_to_waypoint_touch_down_reached;

	message_responses[ENTITY_TYPE_FIXED_WING][ENTITY_MESSAGE_CHECK_MOBILE_REACHED_GUIDE]	= response_to_check_mobile_reached_guide;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
