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

#define DEBUG_MODULE						0

#define DEBUG_MODULE_MESSAGE_TEXT	0

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

			break;
		}
		////////////////////////////////////////
		case LIST_TYPE_TARGET:
		////////////////////////////////////////
		{
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

			//
			// Special effect hook for entity being targeted
			//

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				play_aircraft_targeted_speech (sender, receiver);
			}

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

	vehicle
		*raw;

	raw = get_local_entity_data (receiver);

	#if DEBUG_MODULE_MESSAGE_TEXT

	debug_log ("VEHICLE MSGS: received task terminated, vh %s made safe", entity_sub_type_vehicle_names [raw->mob.sub_type]);

	#endif

	debug_assert (raw->member_link.parent);

	//
	// Check if vehicle was on a landing/takeoff/holding route
	//

	guide = get_local_entity_parent (receiver, LIST_TYPE_FOLLOWER);

	if (!guide)
	{
		return TRUE;
	}

	task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

	ASSERT (task);

	landing_en = get_local_entity_parent (task, LIST_TYPE_ASSIGNED_TASK);

	switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
	{

		case ENTITY_SUB_TYPE_TASK_LANDING:
		{

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("VH_MSGS: mobile was on a %s route, unlocking route and landing site", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE, landing_en, receiver);

			notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing_en, receiver);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_TAKEOFF:
		{

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("VH_MSGS: mobile was on a %s route, unlocking route", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			notify_local_entity (ENTITY_MESSAGE_UNLOCK_TAKEOFF_ROUTE, landing_en, receiver);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
		{

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("VH_MSGS: mobile was on a %s route, locking route and landing site", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing_en, receiver);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
		{

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("VH_MSGS: mobile was on a %s route, no route to unlock", entity_sub_type_task_names [get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)]);

			#endif

			break;
		}
	}

	if (get_local_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_NAVIGATING)
	{

		set_local_entity_int_value (receiver, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_check_mobile_reached_guide (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	vec3d
		guide_pos;

	float
		range;

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

		if (range > get_guide_criteria_value (sender, GUIDE_CRITERIA_RADIUS))
		{
			return FALSE;
		}
	}

	//
	// check altitude
	//

	if (get_guide_criteria_valid (sender, GUIDE_CRITERIA_ALTITUDE))
	{
		get_local_entity_vec3d (sender, VEC3D_TYPE_POSITION, &guide_pos);
			
		range = get_local_entity_float_value (receiver, FLOAT_TYPE_ALTITUDE);

		range -= guide_pos.y;

		if (fabs (range) > get_guide_criteria_value (sender, GUIDE_CRITERIA_ALTITUDE))
		{
			return FALSE;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_vehicle_message_responses (entity_types type)
{
	overload_mobile_message_responses (type);

	#if DEBUG_MODULE

	message_responses[type][ENTITY_MESSAGE_LINK_CHILD] 							= response_to_link_child;

	message_responses[type][ENTITY_MESSAGE_UNLINK_CHILD]							= response_to_unlink_child;

	#endif

	message_responses[type][ENTITY_MESSAGE_LINK_PARENT]							= response_to_link_parent;

	message_responses[type][ENTITY_MESSAGE_UNLINK_PARENT]							= response_to_unlink_parent;

	message_responses[type][ENTITY_MESSAGE_TASK_TERMINATED]						= response_to_task_terminated;

	message_responses[type][ENTITY_MESSAGE_CHECK_MOBILE_REACHED_GUIDE]		= response_to_check_mobile_reached_guide;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////











