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

//
// 3 levels of debug
//

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 3

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 3

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
		type;

	#if DEBUG_MODULE >= 3

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	type = va_arg (pargs, list_types);

	if (type == LIST_TYPE_WAYPOINT)
	{
		if (sender)
		{
			update_local_entity_waypoint_list_tags (sender);
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
		type;

	#if DEBUG_MODULE >= 3

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	type = va_arg (pargs, list_types);

	if (type == LIST_TYPE_WAYPOINT)
	{
		if (sender)
		{
			update_local_entity_waypoint_list_tags (sender);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_set_entity_position (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	vec3d
		*position,
		wp_position,
		delta_position,
		*parent_position;

	float
		cos_heading,
		sin_heading,
		heading;

	waypoint
		*raw;

	raw = get_local_entity_data (receiver);
	
	position = va_arg (pargs, vec3d *);
	
	heading = (float) va_arg (pargs, double);

	//
	// Set position, only if relative to parent
	//

	if (raw->position_type == POSITION_TYPE_RELATIVE)
	{

		parent_position = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

		delta_position.x = (raw->position.x - parent_position->x);
		delta_position.y = (raw->position.y - parent_position->y);
		delta_position.z = (raw->position.z - parent_position->z);

		cos_heading = cos (heading - raw->heading);
		sin_heading = sin (heading - raw->heading);

		wp_position.x = position->x + (cos_heading * delta_position.x) + (sin_heading * delta_position.z);
		wp_position.y = position->y + delta_position.y;
		wp_position.z = position->z + (cos_heading * delta_position.z) - (sin_heading * delta_position.x);

		#if DEBUG_MODULE

		debug_log ("WP_MSGS: setting position, rel pos %f, %f, %f, heading %f, (delta pos %f, %f, %f, old heading %f)",
						position->x, position->y, position->z, deg (heading),
						delta_position.x, delta_position.y, delta_position.z, deg (raw->heading));

		#endif

		set_local_entity_vec3d (receiver, VEC3D_TYPE_POSITION, &wp_position);
	
		set_local_entity_float_value (receiver, FLOAT_TYPE_HEADING, heading);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_action (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	int
		msg;

	waypoint
		*raw;

	entity
		*member;

	#if DEBUG_MODULE >= 3

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GUIDE);

	raw = get_local_entity_data (receiver);

	member = get_local_entity_ptr_value (sender, PTR_TYPE_TASK_LEADER);

	ASSERT (member);

	//
	// get default message
	//

	msg =	waypoint_database [raw->sub_type].waypoint_action_message;

	//
	// only notify the task leader of waypoint reached - he will sort out the rest
	//
		
	if (msg != NUM_ENTITY_MESSAGES)
	{
		notify_local_entity (msg, member, receiver);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	int
		msg,
		return_msg,
		set_next_waypoint;

	waypoint
		*raw;

	entity
		*force,
		*group,
		*member;

	#if DEBUG_MODULE >= 3

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GUIDE);

	raw = get_local_entity_data (receiver);

	member = get_local_entity_ptr_value (sender, PTR_TYPE_TASK_LEADER);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// send message for each waypoint
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	group = get_local_entity_parent (sender, LIST_TYPE_GUIDE_STACK);

	//
	// get default message
	//

	msg =	waypoint_database [raw->sub_type].waypoint_reached_message;

	return_msg = waypoint_database [raw->sub_type].waypoint_reached_return_value;

	set_next_waypoint = TRUE;

	//
	// special cases for some waypoint types
	//

	switch (raw->sub_type)
	{
		case ENTITY_SUB_TYPE_WAYPOINT_RECON:
		{
			//
			// If Human Player is task leader then waypoint cannot be met simply through range - Player must use comms to transmit recon
			//

			if (get_local_entity_int_value (member, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				return_msg = WAYPOINT_REACHED_FALSE;

				msg = NUM_ENTITY_MESSAGES;
			}

			break;
		}

		case ENTITY_SUB_TYPE_WAYPOINT_CAP_LOOP:
		{
			//
			// Loop back to start waypoint (unless task complete) 
			//

			entity
				*wp,
				*task;

			task = get_local_entity_parent (receiver, LIST_TYPE_WAYPOINT);

			ASSERT (task);
			
			if (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) == TASK_INCOMPLETE)
			{
				wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);

				while (wp)
				{
					if (get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_CAP_START)
					{
						break;
					}

					wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
				}

				ASSERT (wp);
				
				set_guide_new_waypoint (sender, wp);

				set_next_waypoint = FALSE;
			}

			break;
		}
	}

	//
	// notify member/s and return
	//

	if (return_msg != WAYPOINT_REACHED_FALSE)
	{

		int
			state;

		// get task and group before notifying first member of wp_reached because it may destroy the task.
		// remember wp may be internal, i.e. parent is not a task but a mobile

		//
		// set guide waypoint
		//

		if (set_next_waypoint)
		{
			set_guide_next_waypoint (sender);
		}

		//
		// set verbose operational state
		//

		state = waypoint_database [raw->sub_type].verbose_operational_state;

		ASSERT (state != VERBOSE_OPERATIONAL_STATE_UNKNOWN);

		set_group_verbose_operational_state (group, state);

		//
		// notify force that waypoints reached
		//

		force = get_local_force_entity (get_local_entity_int_value (group, INT_TYPE_SIDE));

		notify_local_entity (ENTITY_MESSAGE_FORCE_WAYPOINT_REACHED, force, receiver, sender);

		//
		// only notify the task leader of waypoint reached - he will sort out the rest
		//
		
		if (msg != NUM_ENTITY_MESSAGES)
		{
			notify_local_entity (msg, member, receiver);
		}
	}

	return (return_msg);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_waypoint_message_responses (void)
{
	#if DEBUG_MODULE >= 2

	message_responses[ENTITY_TYPE_WAYPOINT][ENTITY_MESSAGE_LINK_CHILD]				= response_to_link_child;

	message_responses[ENTITY_TYPE_WAYPOINT][ENTITY_MESSAGE_UNLINK_CHILD]				= response_to_unlink_child;

	#endif

	message_responses[ENTITY_TYPE_WAYPOINT][ENTITY_MESSAGE_LINK_PARENT] 				= response_to_link_parent;

	message_responses[ENTITY_TYPE_WAYPOINT][ENTITY_MESSAGE_UNLINK_PARENT]			= response_to_unlink_parent;

	message_responses[ENTITY_TYPE_WAYPOINT][ENTITY_MESSAGE_SET_ENTITY_POSITION]	= response_to_set_entity_position;

	message_responses[ENTITY_TYPE_WAYPOINT][ENTITY_MESSAGE_WAYPOINT_ACTION]			= response_to_waypoint_action;

	message_responses[ENTITY_TYPE_WAYPOINT][ENTITY_MESSAGE_WAYPOINT_REACHED]		= response_to_waypoint_reached;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
