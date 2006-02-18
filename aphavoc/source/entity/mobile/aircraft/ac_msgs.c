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

#define DEBUG_MODULE 					0

#define DEBUG_MODULE_MESSAGE_TEXT	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_articulate_undercarriage (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	vec3d
		*position;

	object_3d_instance
		*inst3d;

	sound_sample_indices
		sample_index;

	#if DEBUG_MODULE

	//debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	inst3d = get_local_entity_ptr_value (receiver, PTR_TYPE_INSTANCE_3D_OBJECT);

	if (inst3d)
	{
		if (object_contains_sub_object_type (inst3d, OBJECT_3D_SUB_OBJECT_UNDERCARRIAGE, 0, NULL))
		{
			position = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION);

			sample_index = SOUND_SAMPLE_INDEX_UNDERCARRIAGE;

			create_client_server_sound_effect_entity
			(
				receiver,
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_ALL,
				NULL, 											// position
				1.0,												// amplification
				1.0,												// Werewolf pitch
				TRUE,												// valid sound effect
				FALSE,											// looping
				1,													// sample count
				&sample_index									// sample index list
			);
		}
	}

	return (TRUE);
}

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

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	list_types
		list_type;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	list_type = va_arg (pargs, list_types);

	switch (list_type)
	{
		////////////////////////////////////////
		case LIST_TYPE_GUNSHIP_TARGET:
		////////////////////////////////////////
		{
			set_local_entity_int_value (receiver, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, TRUE);

			set_local_entity_float_value (receiver, FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT, AIR_RADAR_CONTACT_TIMEOUT);

			// show icon on map if gunship scans it.
/*
			if (get_local_entity_int_value (receiver, INT_TYPE_SIDE) == get_global_gunship_side ())
			{

				set_planner_icon_update (receiver, FALSE);
			}
*/
			break;
		}
		////////////////////////////////////////
		case LIST_TYPE_TARGET:
		////////////////////////////////////////
		{
			entity
				*group;

			//
			// Notify the group that it has been targeted
			//
			
			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				if (get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_MOBILE))
				{
					group = get_local_entity_parent (sender, LIST_TYPE_MEMBER);

					if (group)
					{
						notify_local_entity (ENTITY_MESSAGE_ENTITY_TARGETED, group, receiver, sender);
					}
				}
			}

			//
			// if targetting the player then insert into the gunship target list if not already there
			//

			if (sender == get_gunship_entity ())
			{
				if (!get_local_entity_parent (receiver, LIST_TYPE_GUNSHIP_TARGET))
				{
					if (get_local_entity_int_value (receiver, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID)
					{
						if (get_local_entity_int_value (receiver, INT_TYPE_THREAT_TYPE) != THREAT_TYPE_INVALID)
						{
							insert_local_entity_into_parents_child_list (receiver, LIST_TYPE_GUNSHIP_TARGET, sender, NULL);
						}
					}
				}
			}

			break;
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	list_types
		list_type;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	list_type = va_arg (pargs, list_types);

	switch (list_type)
	{
		////////////////////////////////////////
		case LIST_TYPE_GUNSHIP_TARGET:
		////////////////////////////////////////
		{
			set_local_entity_int_value (receiver, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, FALSE);

			set_local_entity_float_value (receiver, FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT, AIR_RADAR_CONTACT_TIMEOUT_INVALID);

			break;
		}
		////////////////////////////////////////
		case LIST_TYPE_UPDATE:
		////////////////////////////////////////
		{
			set_local_entity_float_value (receiver, FLOAT_TYPE_VIEW_INTEREST_LEVEL, 0.0);

			break;
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_terminated (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*guide,
		*landing_en,
		*task;

	aircraft
		*raw;

	raw = get_local_entity_data (receiver);

	#if DEBUG_MODULE_MESSAGE_TEXT

	debug_log ("AIRCRAFT MSGS: received task terminated, ac %s made safe", entity_sub_type_aircraft_names [raw->mob.sub_type]);

	#endif

	debug_assert (raw->member_link.parent);

	//
	// Check if aircraft was on a landing/takeoff/holding route
	//

	guide = get_local_entity_parent (receiver, LIST_TYPE_FOLLOWER);

	ASSERT (guide);

	task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

	ASSERT (task);

	landing_en = get_local_entity_parent (task, LIST_TYPE_ASSIGNED_TASK);

	switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
	{

		case ENTITY_SUB_TYPE_TASK_LANDING:
		{
			ASSERT (landing_en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("AC_MSGS: mobile was on a %s route, unlocking route and landing site", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
			{

				notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE, landing_en, receiver);
			}

			notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing_en, receiver);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_TAKEOFF:
		{
			ASSERT (landing_en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("AC_MSGS: mobile was on a %s route, unlocking route", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			notify_local_entity (ENTITY_MESSAGE_UNLOCK_TAKEOFF_ROUTE, landing_en, receiver);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
		{
			ASSERT (landing_en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("AC_MSGS: mobile was on a %s route, locking route and landing site", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing_en, receiver);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
		{
			ASSERT (landing_en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("AC_MSGS: mobile was on a %s route, no route to unlock", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			break;
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_lower_undercarriage_action (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		if (
				(get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI) ||
				(get_local_entity_int_value (receiver, INT_TYPE_AUTO_PILOT))
			)
		{
			lower_client_server_entity_undercarriage (receiver);
		}
	}

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_raise_undercarriage_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			raise_client_server_entity_undercarriage (receiver);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_guide_cover_position_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	entity
		*aggressor;
		
	float
		silence_timer;
		
	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GUIDE);

	ASSERT (get_local_entity_int_value (receiver, INT_TYPE_GROUP_LEADER));

	if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		//
		// AI group leader notifies sender to fire straight away (PLAYER group leader must use radio message)
		//

		attack_guide_proceed_to_fire_positon (sender);

		return (TRUE);
	}

	aggressor = get_local_entity_first_child (sender, LIST_TYPE_FOLLOWER);

	ASSERT (aggressor);

	ASSERT (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT));

	if (!get_local_entity_int_value (aggressor, INT_TYPE_WEAPONS_HOLD))
	{
		//
		// If the aggressor is in weapons free mode, then he does not have to wait for the player's notification
		//

		attack_guide_proceed_to_fire_positon (sender);

		return (TRUE);
	}

	//
	// Play Speech
	//

	silence_timer = 15.0 + (frand1 () * 12.0);

	play_client_server_wingman_message
	(
		aggressor,
		0.8,
		1.5,
		SPEECH_CATEGORY_IN_POSITION,
		silence_timer,
		SPEECH_INTRODUCTION_ALWAYS,
		SPEECH_ARRAY_WINGMAN_MESSAGES,
		SPEECH_WINGMAN_IN_POSITION
	);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_aircraft_message_responses (entity_types type)
{
	overload_mobile_message_responses (type);

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_ARTICULATE_UNDERCARRIAGE]	= response_to_articulate_undercarriage;

	#if DEBUG_MODULE

	message_responses[type][ENTITY_MESSAGE_LINK_CHILD] 									= response_to_link_child;

	message_responses[type][ENTITY_MESSAGE_UNLINK_CHILD]									= response_to_unlink_child;

	#endif

	message_responses[type][ENTITY_MESSAGE_LINK_PARENT]									= response_to_link_parent;

	message_responses[type][ENTITY_MESSAGE_UNLINK_PARENT]									= response_to_unlink_parent;

	message_responses[type][ENTITY_MESSAGE_TASK_TERMINATED]								= response_to_task_terminated;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_LOWER_UNDERCARRIAGE_ACTION]	= response_to_waypoint_lower_undercarriage_action;

	message_responses[type][ENTITY_MESSAGE_WAYPOINT_RAISE_UNDERCARRIAGE_REACHED]	= response_to_waypoint_raise_undercarriage_reached;

	message_responses[type][ENTITY_MESSAGE_GUIDE_COVER_POSITION_REACHED]				= response_to_guide_cover_position_reached;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
