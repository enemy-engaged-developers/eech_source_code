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

static void debug_log_text (entity *receiver, entity *sender, char *format, ...)
{
	va_list
		pargs;

	char
		s1[400],
		s2[400];

	//
	// prefix
	//

	strcpy (s1, "MESSAGE: ");

	//
	// receiver type and index
	//

	sprintf (s2, "To %s (index = %d) ", get_local_entity_type_name (receiver), get_local_entity_index (receiver));

	strcat (s1, s2);

	//
	// sender type and index (if known)
	//

	if (sender)
	{
		sprintf (s2, "From %s (index = %d): ", get_local_entity_type_name (sender), get_local_entity_index (sender));

		strcat (s1, s2);
	}
	else
	{
		strcat (s1, "From ANONYMOUS: ");
	}

	//
	// args
	//

	va_start (pargs, format);

	vsprintf (s2, format, pargs);

	va_end (pargs);

	strcat (s1, s2);

	debug_log (s1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WARNING! CHARS AND SHORT INTS ARE PROMOTED TO INTS ON THE VARIABLE ARGUMENT LIST
//
//				FLOATS ARE PROMOTED TO DOUBLES ON THE VARIABLE ARGUMENT LIST
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_log_entity_message (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	va_list
		tmp;

	ASSERT (receiver);

	//
	// store pargs
	//

	memcpy (&tmp, pargs, sizeof (va_list));

	////////////////////////////////////////
	//
	// sort debug log text
	//
	////////////////////////////////////////

	switch (message)
	{
		////////////////////////////////////////
		case ENTITY_MESSAGE_ADJUST_LAND_URGENCY:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "adjust land urgency");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_CHILD_MOVE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "child move");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_COLLISION:
		////////////////////////////////////////
		{
			float
				distance;

			distance = va_arg (pargs, double);

			debug_log_text (receiver, sender, "collision (distance = %.3f)", distance);

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_DECOY_ACTIVE:
		////////////////////////////////////////
		{
			debug_log_text (receiver, sender, "decoy active");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_DECOY_EXPIRED:
		////////////////////////////////////////
		{
			debug_log_text (receiver, sender, "decoy expired");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_GROUP_KILLED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "group return to base");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_GROUP_TAKEN_OFF:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "group taken off");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_LANDING_SITE_REQUEST:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "landing site request");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_LINK_CHILD:
		////////////////////////////////////////
		{
			list_types
				type;

			type = va_arg (pargs, list_types);

			debug_log_text (receiver, sender, "link child (%s)", get_list_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_LINK_PARENT:
		////////////////////////////////////////
		{
			list_types
				type;

			type = va_arg (pargs, list_types);

			debug_log_text (receiver, sender, "link parent (list = %s)", get_list_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_LOCK_LANDING_ROUTE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "lock landing route");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_LOCK_LANDING_SITE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "lock landing site");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_LOCK_TAKEOFF_ROUTE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "lock takeoff route");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_PROTOTYPE_1:
		////////////////////////////////////////
		{
			debug_log_text (receiver, sender, "prototype 1");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_PROTOTYPE_2:
		////////////////////////////////////////
		{
			debug_log_text (receiver, sender, "prototype 2");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_PROTOTYPE_3:
		////////////////////////////////////////
		{
			debug_log_text (receiver, sender, "prototype 3");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_PROTOTYPE_4:
		////////////////////////////////////////
		{
			debug_log_text (receiver, sender, "prototype 4");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_RESERVE_LANDING_SITE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "reserve landing site");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_SET_CAMERA_ACTION:
		////////////////////////////////////////
		{
			camera_actions
				action;

			action = va_arg (pargs, int);

			if ((action >= 0) && (action < NUM_CAMERA_ACTIONS))
			{
				debug_log_text (receiver, sender, "set camera action (%s)", camera_action_names[action]);
			}
			else
			{
				debug_log_text (receiver, sender, "set camera action (action = %d)", action);
			}

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_SET_ENTITY_POSITION:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "set entity position");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_TASK_ASSIGNED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "task assigned");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_TASK_OBJECTIVE_MET:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "task objective met");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_TASK_OBJECTIVE_FAILED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "task objective failed");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_TASK_TERMINATED:
		////////////////////////////////////////
		{
			list_types
				type;

			type = va_arg (pargs, list_types);

			debug_log_text (receiver, sender, "task terminated");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_UNLINK_CHILD:
		////////////////////////////////////////
		{
			list_types
				type;

			type = va_arg (pargs, list_types);

			debug_log_text (receiver, sender, "unlink child (list = %s)", get_list_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_UNLINK_PARENT:
		////////////////////////////////////////
		{
			list_types
				type;

			type = va_arg (pargs, list_types);

			debug_log_text (receiver, sender, "unlink parent (list = %s)", get_list_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "unlock landing route");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_UNLOCK_LANDING_SITE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "unlock landing site");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_UNLOCK_TAKEOFF_ROUTE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "unlock takeoff route");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_UNRESERVE_LANDING_SITE:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "unreserve landing site");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_ATTACK_ACTION:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint attack reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_DROP_OFF_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint drop-off reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_END_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint end reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_LAND_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint land reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_LANDED_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint landed reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_LOOP_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint loop reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_NAVIGATION_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint navigation reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_SUB_ROUTE_NAVIGATION_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint sub_route navigation reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_PICK_UP_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint pick-up reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_TAKEN_OFF_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint taken-off reached");

			break;
		}
		////////////////////////////////////////
		case ENTITY_MESSAGE_WAYPOINT_TAXI_REACHED:
		////////////////////////////////////////
		{

			debug_log_text (receiver, sender, "waypoint taxi reached");

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid entity message = %d", message);

			break;
		}
	}

	//
	// restore pargs
	//

	memcpy (pargs, tmp, sizeof (va_list));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
