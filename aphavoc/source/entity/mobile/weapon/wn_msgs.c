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

static int response_to_collision (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	weapon
		*raw;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = (weapon *) get_local_entity_data (receiver);

	raw->mob.kill_next_update = TRUE;

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_decoy_active (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	weapon
		*raw;

	weapon_decoy_types
		decoy_type;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (weapon *) get_local_entity_data (receiver);

	decoy_type = (weapon_decoy_types) get_local_entity_int_value (sender, INT_TYPE_WEAPON_DECOY_TYPE);

	if (get_weapon_locked_onto_decoy (decoy_type))
	{
		switch (weapon_database[raw->mob.sub_type].guidance_type)
		{
			////////////////////////////////////////
			case WEAPON_GUIDANCE_TYPE_NONE:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR:
			case WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR:
			case WEAPON_GUIDANCE_TYPE_RADIO_COMMAND:
			////////////////////////////////////////
			{
				if (decoy_type == WEAPON_DECOY_TYPE_CHAFF)
				{
					set_client_server_entity_parent (receiver, LIST_TYPE_TARGET, sender);
				}

				break;
			}
			////////////////////////////////////////
			case WEAPON_GUIDANCE_TYPE_PASSIVE_INFRA_RED:
			////////////////////////////////////////
			{
				if (decoy_type == WEAPON_DECOY_TYPE_FLARE)
				{
					set_client_server_entity_parent (receiver, LIST_TYPE_TARGET, sender);
				}

				break;
			}
			////////////////////////////////////////
			case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER:
			case WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_LASER_BEAM_RIDING:
			case WEAPON_GUIDANCE_TYPE_ACTIVE_LASER:
			case WEAPON_GUIDANCE_TYPE_WIRE_GUIDED:
			////////////////////////////////////////
			{
				if (decoy_type == WEAPON_DECOY_TYPE_SMOKE_GRENADE)
				{
					set_client_server_entity_parent (receiver, LIST_TYPE_TARGET, sender);
				}

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid weapon guidance type = %d", weapon_database[raw->mob.sub_type].guidance_type);

				break;
			}
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_decoy_expired (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	ASSERT (sender);

	delete_local_entity_from_parents_child_list (receiver, LIST_TYPE_TARGET);

	insert_local_entity_into_parents_child_list (receiver, LIST_TYPE_TARGET, sender, NULL);

	//
	// a comms message is not required as the unlinking will work on both client and server
	//

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

#if DEBUG_MODULE

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	weapon
		*raw;

	list_types
		list_type;

	vec3d
		target_position;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	raw = (weapon *) get_local_entity_data (receiver);

	list_type = va_arg (pargs, list_types);

	if (list_type == LIST_TYPE_TARGET)
	{
		if (get_view_mode () == VIEW_MODE_EXTERNAL)
		{
			if (get_camera_entity ())
			{
				if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_WEAPON)
				{
					if (receiver == get_local_entity_first_child (get_camera_entity (), LIST_TYPE_VIEW_WEAPON))
					{
						if (sender)
						{
							if (!get_local_entity_int_value (sender, INT_TYPE_IDENTIFY_WEAPON))
							{
								if (!get_local_entity_int_value (sender, INT_TYPE_ALIVE))
								{
									get_local_entity_target_point (sender, &target_position);

									if (get_3d_range (&raw->mob.position, &target_position) < 250.0)
									{
										notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_WEAPON_EXPLOSION);

										reset_weapon_explosion_camera_position (get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION));
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_weapon_message_responses (void)
{
	overload_mobile_message_responses (ENTITY_TYPE_WEAPON);

	message_responses[ENTITY_TYPE_WEAPON][ENTITY_MESSAGE_COLLISION]		= response_to_collision;

	message_responses[ENTITY_TYPE_WEAPON][ENTITY_MESSAGE_DECOY_ACTIVE]	= response_to_decoy_active;

	message_responses[ENTITY_TYPE_WEAPON][ENTITY_MESSAGE_DECOY_EXPIRED]	= response_to_decoy_expired;

	#if DEBUG_MODULE

	message_responses[ENTITY_TYPE_WEAPON][ENTITY_MESSAGE_LINK_CHILD]		= response_to_link_child;

	message_responses[ENTITY_TYPE_WEAPON][ENTITY_MESSAGE_UNLINK_CHILD]	= response_to_unlink_child;

	message_responses[ENTITY_TYPE_WEAPON][ENTITY_MESSAGE_LINK_PARENT]		= response_to_link_parent;

	#endif

	message_responses[ENTITY_TYPE_WEAPON][ENTITY_MESSAGE_UNLINK_PARENT]	= response_to_unlink_parent;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
