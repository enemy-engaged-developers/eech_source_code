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

//////////////////////////////////////////////////////
//
// 2 levels of debug
//
//////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define FATAL 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if LANDING_ROUTE_CHECK

char
	*debug_landing_lock_names [] =
	{

		"LOCK_RESERVE_LOCK",
		"LOCK_LANDING_SITE_LOCK",
		"LOCK_LANDING_ROUTE_LOCK",
		"LOCK_TAKEOFF_ROUTE_LOCK",
		"NUM_DEBUG_LANDING_LOCKS"
	},
	*debug_landing_lock_unlock_names [] =
	{
		"UNLOCKING",
		"LOCKING",
	};

debug_landing_lock_type
	*debug_landing_lock_list = NULL;

void debug_update_entity_landing_locks (entity *en, entity *landing, debug_landing_lock lock, int lock_flag);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE >= 2

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_landing_site_request (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	formation_type
		*formation_data;

	unsigned int
		landed_lock,
		landing_lock,
		member_number,
		formation_landing,
		formation_position;

	entity
		*member,
		*guide,
		*keysite,
		*fw_landing,
		*incoming_group,
		*landing_task,
		*holding_task,
		*landing_route_first_wp;

	landing
		*raw;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	#if DEBUG_MODULE

	debug_log ("LD_MSGS:%d (%s), landing request mb %d", get_local_entity_index (receiver), entity_sub_type_landing_names [raw->sub_type], get_local_entity_index (sender));

	#endif

	incoming_group = get_local_entity_parent (sender, LIST_TYPE_MEMBER);

	member = get_local_entity_first_child (incoming_group, LIST_TYPE_MEMBER);

	//
	// Check for lock
	//

	#if DEBUG_MODULE

	debug_log ("LD_MSGS:%d, landing entity locked", get_local_entity_index (receiver));

	#endif

	landing_task = get_local_landing_entity_task (receiver, ENTITY_SUB_TYPE_TASK_LANDING);

	holding_task = get_local_landing_entity_task (receiver, ENTITY_SUB_TYPE_TASK_LANDING_HOLDING);

	landing_route_first_wp = get_local_entity_first_child (landing_task, LIST_TYPE_WAYPOINT);

	formation_data = get_formation ((formation_types) get_local_entity_int_value (landing_route_first_wp, INT_TYPE_WAYPOINT_FORMATION));

	while (member)
	{

		member_number = get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER);

		//
		// unreserve landing site
		//

		notify_local_entity (ENTITY_MESSAGE_UNRESERVE_LANDING_SITE, receiver, member, 1);

		//
		// Calculate formation position
		//

		formation_position = 0;

		landed_lock = get_local_entity_int_value (receiver, INT_TYPE_LANDED_LOCK);

		while ((formation_position < raw->total_landing_sites) && ((1 << formation_position) & (raw->landed_lock)))
		{

			formation_position ++;
		}

		if (get_local_entity_int_value (member, INT_TYPE_FORMATION_POSITION) != formation_position)
		{

			set_client_server_entity_int_value (member, INT_TYPE_FORMATION_POSITION, formation_position);
		}

		#if DEBUG_MODULE

		debug_log ("LD_MSGS:%d, setting formation position to %d", get_local_entity_index (receiver), formation_position);

		#endif

		formation_landing = formation_position % formation_data->number_in_formation;

		#if DEBUG_MODULE

		debug_log ("LD_MSGS:%d, formation_landing = %d, formation count = %d", get_local_entity_index (receiver), formation_landing, formation_data->number_in_formation);

		#endif

		landing_lock = get_local_entity_int_value (receiver, INT_TYPE_LANDING_LOCK);

		keysite = get_local_entity_parent (receiver, LIST_TYPE_LANDING_SITE);

		fw_landing = get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING);

		if ((get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) &&
			(get_local_entity_int_value (fw_landing, INT_TYPE_LANDING_LOCK)))
		{

			debug_log ("LD_MSGS: can't land TRANSPORT %s (%d) atm, something else is landing on the FW route", get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member));
		}

		// See if the member can land.... or if its a TRANSPORT check if the fw route is clear as well...

		//if (landing_lock & (1 << formation_landing))
		if ((landing_lock & (1 << formation_landing)) ||
			((get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) &&
			(get_local_entity_int_value (fw_landing, INT_TYPE_LANDING_LOCK))))
		{
		
			//
			// Place member on holding route
			//

			#if FATAL

			ASSERT (get_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDING_HOLDING);

			#endif

			set_client_server_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING_HOLDING);

			#if DEBUG_MODULE

			debug_log ("LD_MSGS:%d, inserting %s (%d) into landing holding route", get_local_entity_index (receiver), get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member));

			#endif

			guide = create_client_server_guide_entity (holding_task, NULL, (1 << member_number));

			attach_group_to_guide_entity (incoming_group, guide);

			attach_group_member_to_guide_entity (member, guide);

			//
			// Lock landing site
			//

			notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_SITE, receiver, member);
	
			/////////////////////////////////////////////////////////////////
			//
			// SPECIAL_EFFECT_HOOK FOR PREPARING FOR LANDING-HOLDING PATTERN
			//
			/////////////////////////////////////////////////////////////////

			// PLAY_SPEECH (ATC)
			//
			// [callsign + number],
			// ATC Introduction,
			// [Permission denied],
			// Please proceed to holding route and await further instructions

			if (get_game_status () != GAME_STATUS_INITIALISING)
			{
				if (incoming_group)
				{
					play_client_server_speech
					(
						get_session_entity (),
						member,
						(entity_sides) get_local_entity_int_value (member, INT_TYPE_SIDE),
						ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
						SOUND_LOCALITY_RADIO,
						0.0,
						0.4,
						12.0,
						SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER,
						SPEECH_CATEGORY_LANDING_TAKING_OFF, 10.0,
						SPEECH_ARRAY_CALLSIGNS, get_local_entity_int_value (incoming_group, INT_TYPE_GROUP_CALLSIGN),
						SPEECH_ARRAY_NUMBERS, 1,
						SPEECH_ARRAY_NUMBERS, get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID),
						SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_INTRODUCTION,
						SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_PROCEED_TO_HOLDING_ROUTE,
						-1
					);
				}
			}

			/////////////////////////////////////////////////////////////////
			//
			//
			/////////////////////////////////////////////////////////////////
		}
		else
		{
			
			//
			// Place member on landing route
			//

			#if FATAL

			ASSERT (get_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDING);

			#endif

			set_client_server_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING);

			//
			//
			//
	
			#if DEBUG_MODULE

			debug_log ("LD_MSGS:%d, inserting %d into landing route", get_local_entity_index (receiver), get_local_entity_index (member));

			#endif

			guide = create_client_server_guide_entity (landing_task, NULL, (1 << member_number));

			attach_group_to_guide_entity (incoming_group, guide);

			attach_group_member_to_guide_entity (member, guide);

			notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_ROUTE, receiver, member);
		
			//
			// Lock landing site and route
			//

			notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_SITE, receiver, member);
	
			/////////////////////////////////////////////////////////////////
			//
			// SPECIAL_EFFECT_HOOK FOR LANDING GRANTED
			//
			/////////////////////////////////////////////////////////////////

			// PLAY_SPEECH (ATC)
			//
			// [callsign + number],
			// ATC Introduction,
			// [Permission granted],
			// (You are clear to land) | (sea state calm, you are cleared to land) | (sea state rough, etc)

			if (get_game_status () != GAME_STATUS_INITIALISING)
			{
				if (incoming_group)
				{
					play_client_server_speech
					(
						get_session_entity (),
						member,
						(entity_sides) get_local_entity_int_value (member, INT_TYPE_SIDE),
						ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
						SOUND_LOCALITY_RADIO,
						0.0,
						0.5,
						8.0,
						SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER, 
						SPEECH_CATEGORY_LANDING_TAKING_OFF, 20.0,
						SPEECH_ARRAY_CALLSIGNS, get_local_entity_int_value (incoming_group, INT_TYPE_GROUP_CALLSIGN),
						SPEECH_ARRAY_NUMBERS, 1,
						SPEECH_ARRAY_NUMBERS, get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_ID),
						SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_INTRODUCTION,
						SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_CLEAR_FOR_LANDING,
						SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_WINDS,
						SPEECH_ARRAY_ATC_MESSAGES, get_speech_atc_wind_speed (member),
						-1
					);
				}
			}

			/////////////////////////////////////////////////////////////////
			//
			//
			/////////////////////////////////////////////////////////////////
		}
	
		//
		// Set member's internal wp parameters
		//
	
		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_lock_landing_route (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	formation_type
		*formation_data;

	entity
		*wp;

	landing
		*raw;

	unsigned int
		formation_landing;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	formation_landing = get_local_entity_int_value (sender, INT_TYPE_FORMATION_POSITION);

	wp = get_local_landing_entity_route (receiver, ENTITY_SUB_TYPE_TASK_LANDING);

	formation_data = get_formation ((formation_types) get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

	formation_landing %= formation_data->number_in_formation;

	#if DEBUG_MODULE

	if ((raw->landing_lock & (1 << formation_landing)))
	{

		#if FATAL
		debug_fatal
		#else
		debug_log
		#endif
		("LD_MSGS:%d, type %s: INVALID: lock landing route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}
	else
	{

		#if LANDING_LOCK_USER_ONLY
		if (sender == get_gunship_entity ())
		#endif
		debug_log ("LD_MSGS:BEFORE: %d, type %s: lock landing route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}

	#endif

	#if FATAL

	ASSERT (!(raw->landing_lock & (1 << formation_landing)));

	#endif

	raw->landing_lock |= 1 << formation_landing;

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR PREPARING FOR LANDING
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	#if LANDING_ROUTE_CHECK

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_update_entity_landing_locks (sender, receiver,
													//DEBUG_LANDING_LOCK_RESERVE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
													DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
													//DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
													TRUE);

	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:AFTER : %d, type %s: lock landing route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	#endif
	#endif
												
	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_lock_landing_site (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	landing
		*raw;

	unsigned int
		formation_landing;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	formation_landing = get_local_entity_int_value (sender, INT_TYPE_FORMATION_POSITION);

	#if FATAL

	ASSERT (!(raw->landed_lock & (1 << formation_landing)));

	#endif
	
  	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:BEFORE: %d, type %s: lock landing site by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	#endif

	raw->landed_lock |= 1 << formation_landing;

	raw->free_landing_sites --;

	#if DEBUG_MODULE

	if (raw->free_landing_sites < 0)
	{
	
		#if FATAL
		debug_fatal
		#else
		debug_log
		#endif
		("LD_MSGS:%d, type %s: INVALID: lock landing site by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}

	#endif

	#if FATAL

	ASSERT (raw->free_landing_sites >= 0);

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR REQUESTING LANDING SITE
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	#if LANDING_ROUTE_CHECK

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_update_entity_landing_locks (sender, receiver,
													//DEBUG_LANDING_LOCK_RESERVE_LOCK,
													DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
													//DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
													TRUE);
	
	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:AFTER : %d, type %s: lock landing site by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	#endif
	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_lock_takeoff_route (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	formation_type
		*formation_data;

	entity
		*wp;

	landing
		*raw;

	unsigned int
		formation_takeoff;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	formation_takeoff = get_local_entity_int_value (sender, INT_TYPE_FORMATION_POSITION);

	wp = get_local_landing_entity_route (receiver, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	//
	// get the formation at the end of the takeoff route, i.e. at the taken off waypoint
	//
	
	while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
	{

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}

	formation_data = get_formation ((formation_types) get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

	formation_takeoff %= formation_data->number_in_formation;

	if (!(raw->takeoff_lock & (1 << formation_takeoff)))
	{
	
		#if DEBUG_MODULE

		#if LANDING_LOCK_USER_ONLY
		if (sender == get_gunship_entity ())
		#endif
		debug_log ("LD_MSGS:BEFORE: %d, type %s: lock takeoff route by %d(total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));

		#endif
	
		raw->takeoff_lock |= 1 << formation_takeoff;

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR PREPARING FOR TAKEOFF
		//
		/////////////////////////////////////////////////////////////////

		{
			//
			// open hanger doors if there is one,
			// 	search through buildings looking for the nearest (within a range)
			//

			entity
				*group,
				*hanger,
				*keysite,
				*building;

			float
				sqr_range;

			vec3d
				*en_pos,
				*building_pos;

			keysite = get_local_entity_parent (receiver, LIST_TYPE_LANDING_SITE);

			group = get_local_entity_first_child (keysite, LIST_TYPE_BUILDING_GROUP);

			building = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

			en_pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

			hanger = NULL;

			while (building)
			{

				building_pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

				sqr_range = get_sqr_3d_range (en_pos, building_pos);

				if (sqr_range < 2.0)
				{

					//
					// early out.
					//

					hanger = building;

					break;
				}

				building = get_local_entity_child_succ (building, LIST_TYPE_MEMBER);
			}

			if (hanger)
			{

				open_client_server_entity_loading_doors (hanger);

				set_local_entity_float_value (hanger, FLOAT_TYPE_LOADING_DOOR_TIMER, 30.0);
			}
		}

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR TAKEOFF GRANTED
		//
		/////////////////////////////////////////////////////////////////

		// takeoff speech played in mb_msgs.c
		
		/////////////////////////////////////////////////////////////////
		//
		//
		/////////////////////////////////////////////////////////////////

		#if LANDING_ROUTE_CHECK

		#if LANDING_LOCK_USER_ONLY
		if (sender == get_gunship_entity ())
		#endif
		debug_update_entity_landing_locks (sender, receiver,
													//DEBUG_LANDING_LOCK_RESERVE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
													DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
													TRUE);
		#if DEBUG_MODULE
		#if LANDING_LOCK_USER_ONLY
		if (sender == get_gunship_entity ())
		#endif
		debug_log ("LD_MSGS:AFTER : %d, type %s: lock takeoff route by %d(total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
		#endif
		#endif

		return (TRUE);
	}

	#if DEBUG_MODULE

	debug_log ("LD_MSGS:%d, Can't lock takeoff route for %d", get_local_entity_index (receiver), get_local_entity_index (sender));

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR DENIED TAKEOFF
	//
	/////////////////////////////////////////////////////////////////

	// PLAY_SPEECH (ATC)
	//
	// [callsign + number],
	// ATC Introduction,
	// [Permission denied],
	// Please await takeoff clearance

	if (get_game_status () != GAME_STATUS_INITIALISING)
	{
		entity
			*group;

		group = get_local_entity_parent (sender, LIST_TYPE_MEMBER);

		if (group)
		{
			play_client_server_speech
			(
				get_session_entity (),
				sender,
				(entity_sides) get_local_entity_int_value (sender, INT_TYPE_SIDE),
				ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
				SOUND_LOCALITY_RADIO,
				0.0,
				0.4,
				12.0,
				SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER, 
				SPEECH_CATEGORY_LANDING_TAKING_OFF, 20.0,
				SPEECH_ARRAY_CALLSIGNS, get_local_entity_int_value (group, INT_TYPE_GROUP_CALLSIGN),
				SPEECH_ARRAY_NUMBERS, 1,
				SPEECH_ARRAY_NUMBERS, get_local_entity_int_value (sender, INT_TYPE_GROUP_MEMBER_ID),
				SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_INTRODUCTION,
				SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_PROCEED_TO_HOLDING_ROUTE,
				-1
			);
		}
	}

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_reserve_landing_site (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	landing
		*raw;

	int
		count;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	count = va_arg (pargs, int);
	
  	#if DEBUG_MODULE

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:BEFORE: %d, type %s: reserve landing by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));

	#endif

	raw->reserved_landing_sites += count;

	#if DEBUG_MODULE

	if (raw->reserved_landing_sites > raw->total_landing_sites)
	{
	
		#if FATAL
		debug_fatal
		#else
		debug_log
		#endif
		("LD_MSGS:%d, type %s: INVALID: reserve landing by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}

	#endif

	#if FATAL

	ASSERT (raw->reserved_landing_sites <= raw->total_landing_sites);

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR RESERVE LANDING SITE
	//
	/////////////////////////////////////////////////////////////////

	#if LANDING_ROUTE_CHECK

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	{
		debug_update_entity_landing_locks (sender, receiver,
														DEBUG_LANDING_LOCK_RESERVE_LOCK,
														//DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
														//DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
														//DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
														TRUE);

	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:AFTER : %d, type %s: reserve landing by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	#endif
	}
	#endif

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_set_entity_position (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	float
		velocity,
		heading;

	vec3d
		*position;

	entity
		*task;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	position = va_arg (pargs, vec3d *);

	heading = (float) va_arg (pargs, double);

	velocity = (float) va_arg (pargs, double);

	#if DEBUG_MODULE
/*
	debug_log ("LD_MSGS: %s, setting position %f, %f, %f, heading %f",
					entity_sub_type_landing_names [get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE)],
					position->x, position->y, position->z, heading);
*/
	#endif

	//
	// move tasks (landing, takeoff, landing_holding, takeoff_holding) before setting position (so children can calculate delta move)
	//

	task = get_local_entity_first_child (receiver, LIST_TYPE_ASSIGNED_TASK);

	while (task)
	{

		notify_local_entity (ENTITY_MESSAGE_SET_ENTITY_POSITION, task, receiver, position, (double) heading, (double) velocity);

		task = get_local_entity_child_succ (task, LIST_TYPE_ASSIGNED_TASK);
	}

	//
	// Use full set_position function to keep sector data correct.
	//

	set_local_entity_vec3d (receiver, VEC3D_TYPE_POSITION, position);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_task_terminated (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	formation_type
		*formation_data;

	unsigned int
		exit,
		landing_lock,
		member_number,
		formation_landing;

	entity
		*guide,
		*keysite,
		*landing_task,
		*holding_task,
		*holding_member,
		*next_group,
		*incoming_group,
		*next_landing_member,
//		*landing_route_last_wp,
		*landing_route_first_wp;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE

	debug_log ("LD_MSGS:%d, landing terminated %s (%d)", get_local_entity_index (receiver), get_local_entity_string (sender, STRING_TYPE_FULL_NAME), get_local_entity_index (sender));

	#endif

	incoming_group = get_local_entity_parent (sender, LIST_TYPE_MEMBER);

	//
	// Unlock landing route 
	//

//	if (get_local_entity_int_value (sender, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{

		notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE, receiver, sender);
	}

	//
	// Clear landing route for this member
	//

	landing_task = get_local_landing_entity_task (receiver, ENTITY_SUB_TYPE_TASK_LANDING);

	landing_route_first_wp = get_local_entity_first_child (landing_task, LIST_TYPE_WAYPOINT);

//	set_local_landing_route_clear (landing_task, sender);

	//
	// Land any members that are holding and landing site is free
	// NB. if TRANSPORT flip back to FW landing
	//

	if (get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT)
	{

		debug_log ("LD_MSGS: TRANSPORT %s %d terminated landing... switching to FW landing en", get_local_entity_string (sender, STRING_TYPE_FULL_NAME), get_local_entity_index (sender));

		keysite = get_local_entity_parent (receiver, LIST_TYPE_LANDING_SITE);

		if (get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING))
		{
	
			receiver = get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING);
	
			landing_task = get_local_landing_entity_task (receiver, ENTITY_SUB_TYPE_TASK_LANDING);
	
			landing_route_first_wp = get_local_entity_first_child (landing_task, LIST_TYPE_WAYPOINT);
		}
	}

	holding_task = get_local_landing_entity_task (receiver, ENTITY_SUB_TYPE_TASK_LANDING_HOLDING);

	formation_data = get_formation ((formation_types) get_local_entity_int_value (landing_route_first_wp, INT_TYPE_WAYPOINT_FORMATION));

	next_landing_member = NULL;

	exit = FALSE;

	landing_lock = get_local_entity_int_value (receiver, INT_TYPE_LANDING_LOCK);

	guide = get_local_entity_first_child (holding_task, LIST_TYPE_GUIDE);

	if (guide)
	{
		//
		// find last entity in the list
		//
		
		while (get_local_entity_child_succ (guide, LIST_TYPE_GUIDE))
		{
			guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE);
		}

		//
		// spin backwards through the list
		//

		while ((guide) && (!exit))
		{

			holding_member = get_local_entity_first_child (guide, LIST_TYPE_FOLLOWER);

			while (holding_member)
			{

				formation_landing = get_local_entity_int_value (holding_member, INT_TYPE_FORMATION_POSITION);

				formation_landing %= formation_data->number_in_formation;

				if (!(landing_lock & (1 << formation_landing)))
				{

					next_landing_member = holding_member;

					exit = TRUE;

					break;
				}
				#if DEBUG_MODULE
				else
				{
	
					debug_log ("LANDING_MSGS: Can't land holding member %s (%d), landing route still busy. member formation pos %d, landing formation %d, number in route formation %d",
									get_local_entity_string (holding_member, STRING_TYPE_FULL_NAME),
									get_local_entity_index (holding_member),
									get_local_entity_int_value (holding_member, INT_TYPE_FORMATION_POSITION),
									formation_landing,
									formation_data->number_in_formation);
				}
				#endif

				holding_member = get_local_entity_child_succ (holding_member, LIST_TYPE_FOLLOWER);
			}

			guide = get_local_entity_child_pred (guide, LIST_TYPE_GUIDE);
		}
	}

	if (next_landing_member)
	{
		//
		// remove member from holding route
		//

		guide = get_local_entity_parent (next_landing_member, LIST_TYPE_FOLLOWER);

		ASSERT (get_local_entity_parent (guide, LIST_TYPE_GUIDE) == holding_task);

		destroy_client_server_entity (guide);

		//
		// Place member on landing route
		//

		next_group = get_local_entity_parent (next_landing_member, LIST_TYPE_MEMBER);

		#if DEBUG_MODULE

		debug_log ("LD_MSGS:%d, inserting landing holding %s (%d: AI) into 1st landing route waypoint", get_local_entity_index (receiver), get_local_entity_string (next_landing_member, STRING_TYPE_FULL_NAME), get_local_entity_index (next_landing_member));

		#endif
	
		//
		// Lock landing route and set operational state
		//

		member_number = get_local_entity_int_value (next_landing_member, INT_TYPE_GROUP_MEMBER_NUMBER);

		guide = create_client_server_guide_entity (landing_task, NULL, (1 << member_number));

		attach_group_to_guide_entity (next_group, guide);

		attach_group_member_to_guide_entity (next_landing_member, guide);

		notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_ROUTE, receiver, next_landing_member);

		#if FATAL

		ASSERT (get_local_entity_int_value (next_landing_member, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDING);

		#endif

		set_client_server_entity_int_value (next_landing_member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING);
	}
	else
	{

		if (get_local_entity_int_value (receiver, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_LANDING_FIXED_WING)
		{

			//
			// check TRANSPORT holding pattern
			//

			if (!get_local_entity_int_value (receiver, INT_TYPE_LANDING_LOCK))
			{

				entity
					*keysite,
					*transport_landing;

				debug_log ("LD_MSGS: no more FIXED WING landing, checking TRANSPORT");

				keysite = get_local_entity_parent (receiver, LIST_TYPE_LANDING_SITE);

				transport_landing = get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT);

				if (transport_landing)
				{
	
					holding_task = get_local_landing_entity_task (transport_landing, ENTITY_SUB_TYPE_TASK_LANDING_HOLDING);
	
					ASSERT (holding_task);
	
					guide = get_local_entity_first_child (holding_task, LIST_TYPE_GUIDE);
	
					if (guide)
					{
		
						holding_member = get_local_entity_first_child (guide, LIST_TYPE_FOLLOWER);
		
						if (holding_member)
						{

							debug_log ("LD_MSGS: got a TRANSPORT %s", get_local_entity_string (holding_member, STRING_TYPE_FULL_NAME), get_local_entity_index (holding_member));
	
							landing_task = get_local_landing_entity_task (transport_landing, ENTITY_SUB_TYPE_TASK_LANDING);
					
							destroy_client_server_entity (guide);
					
							//
							// Place member on landing route
							//
					
							next_group = get_local_entity_parent (holding_member, LIST_TYPE_MEMBER);
					
							//#if DEBUG_MODULE
				
							debug_log ("LD_MSGS:%d, inserting TRANSPORT landing holding %s (%d: AI) into 1st landing route waypoint", get_local_entity_index (transport_landing), get_local_entity_string (holding_member, STRING_TYPE_FULL_NAME), get_local_entity_index (holding_member));
					
							//#endif
						
							//
							// Lock landing route and set operational state
							//
				
							member_number = get_local_entity_int_value (holding_member, INT_TYPE_GROUP_MEMBER_NUMBER);
				
							guide = create_client_server_guide_entity (landing_task, NULL, (1 << member_number));
				
							attach_group_to_guide_entity (next_group, guide);
				
							attach_group_member_to_guide_entity (holding_member, guide);
				
							notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_ROUTE, transport_landing, holding_member);

							set_client_server_entity_int_value (holding_member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING);
						}
					}
				}
			}
		}
	}

	//
	// Set group idle if all landed
	//
	{
		entity
			*landed_member;

		int
			count = 0,
			member_count;

		member_count = get_local_entity_int_value (incoming_group, INT_TYPE_MEMBER_COUNT);

		landed_member = get_local_entity_first_child (incoming_group, LIST_TYPE_MEMBER);

		while (landed_member)
		{

			if (get_local_entity_int_value (landed_member, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED)
			{

				count ++;
			}

			landed_member = get_local_entity_child_succ (landed_member, LIST_TYPE_MEMBER);
		}

		if (count == member_count)
		{

			#if DEBUG_MODULE

			debug_log ("LD_MSGS: (counted) all group landed setting sleep and idle");

			#endif

			set_local_entity_float_value (incoming_group, FLOAT_TYPE_SLEEP, 15 * ONE_MINUTE);
		}

		///////////////////////////////////////////////////////////////////////////////
		//
		///////////////////////////////////////////////////////////////////////////////
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unlock_landing_route (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	formation_type
		*formation_data;

	entity
		*wp;

	landing
		*raw;

	unsigned int
		formation_landing;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	formation_landing = get_local_entity_int_value (sender, INT_TYPE_FORMATION_POSITION);

	wp = get_local_landing_entity_route (receiver, ENTITY_SUB_TYPE_TASK_LANDING);

	formation_data = get_formation ((formation_types) get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

	formation_landing %= formation_data->number_in_formation;

	#if DEBUG_MODULE

	if (!(raw->landing_lock & (1 << formation_landing)))
	{
	
		#if FATAL
		debug_fatal
		#else
		debug_log
		#endif
		("LD_MSGS:%d, type %s: INVALID: unlock landing route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}
	else
	{

		#if LANDING_LOCK_USER_ONLY
		if (sender == get_gunship_entity ())
		#endif
		debug_log ("LD_MSGS:BEFORE: %d, type %s: unlock landing route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
						get_local_entity_index (receiver),
						entity_sub_type_landing_names [raw->sub_type],
						get_local_entity_index (sender),
						raw->total_landing_sites,
						raw->free_landing_sites,
						raw->reserved_landing_sites,
						int_bit_count (raw->landing_lock),
						int_bit_count (raw->landed_lock),
						int_bit_count (raw->takeoff_lock));
	}

	#endif

	#if FATAL

	ASSERT (raw->landing_lock & (1 << formation_landing));

	#endif

	formation_landing = ~(1 << formation_landing);

	raw->landing_lock &= formation_landing;

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR LANDING COMPLETE
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	#if LANDING_ROUTE_CHECK

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_update_entity_landing_locks (sender, receiver,
													//DEBUG_LANDING_LOCK_RESERVE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
													DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
													//DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
													FALSE);

	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:AFTER : %d, type %s: unlock landing route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
				get_local_entity_index (receiver),
				entity_sub_type_landing_names [raw->sub_type],
				get_local_entity_index (sender),
				raw->total_landing_sites,
				raw->free_landing_sites,
				raw->reserved_landing_sites,
				int_bit_count (raw->landing_lock),
				int_bit_count (raw->landed_lock),
				int_bit_count (raw->takeoff_lock));
	#endif
	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unlock_landing_site (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	landing
		*raw;

	unsigned int
		formation_landing;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	formation_landing = get_local_entity_int_value (sender, INT_TYPE_FORMATION_POSITION);

	#if FATAL

	ASSERT (raw->landed_lock & (1 << formation_landing));

	#endif

	#if DEBUG_MODULE

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:BEFORE: %d, type %s: unlock landing site by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
						get_local_entity_index (receiver),
						entity_sub_type_landing_names [raw->sub_type],
						get_local_entity_index (sender),
						raw->total_landing_sites,
						raw->free_landing_sites,
						raw->reserved_landing_sites,
						int_bit_count (raw->landing_lock),
						int_bit_count (raw->landed_lock),
						int_bit_count (raw->takeoff_lock));

	#endif

	formation_landing = ~(1 << formation_landing);

	raw->landed_lock &= formation_landing;

	raw->free_landing_sites ++;

	#if DEBUG_MODULE

	if (raw->free_landing_sites > raw->total_landing_sites)
	{
	
		#if FATAL
		debug_fatal
		#else
		debug_log
		#endif
		("LD_MSGS:%d, type %s: INVALID: unlock landing site by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}

	#endif

	#if FATAL

	ASSERT (raw->free_landing_sites <= raw->total_landing_sites);

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR PREPARING FOR TAKEOFF
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	#if LANDING_ROUTE_CHECK

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_update_entity_landing_locks (sender, receiver,
													//DEBUG_LANDING_LOCK_RESERVE_LOCK,
													DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
													//DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
													FALSE);

	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:AFTER : %d, type %s: unlock landing site by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
					get_local_entity_index (receiver),
					entity_sub_type_landing_names [raw->sub_type],
					get_local_entity_index (sender),
					raw->total_landing_sites,
					raw->free_landing_sites,
					raw->reserved_landing_sites,
					int_bit_count (raw->landing_lock),
					int_bit_count (raw->landed_lock),
					int_bit_count (raw->takeoff_lock));
	#endif
	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unlock_takeoff_route (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	formation_type
		*formation_data;

	entity
		*wp,
		*member;

	landing
		*raw;

	unsigned int
		formation_takeoff;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	formation_takeoff = get_local_entity_int_value (sender, INT_TYPE_FORMATION_POSITION);

	wp = get_local_landing_entity_route (receiver, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	// test, get the formation at the end of the takeoff route, i.e. at the taken off waypoint
	while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
	{

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}
	// end test

	formation_data = get_formation ((formation_types) get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

	formation_takeoff %= formation_data->number_in_formation;

	#if DEBUG_MODULE

	if (!(raw->takeoff_lock & (1 << formation_takeoff)))
	{
	
		#if FATAL
		debug_fatal
		#else
		debug_log
		#endif
		("LD_MSGS:%d, type %s: INVALID: unlock takeoff route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}
	else
	{
		#if LANDING_LOCK_USER_ONLY
		if (sender == get_gunship_entity ())
		#endif
		debug_log ("LD_MSGS:BEFORE: %d, type %s: unlock takeoff route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
						get_local_entity_index (receiver),
						entity_sub_type_landing_names [raw->sub_type],
						get_local_entity_index (sender),
						raw->total_landing_sites,
						raw->free_landing_sites,
						raw->reserved_landing_sites,
						int_bit_count (raw->landing_lock),
						int_bit_count (raw->landed_lock),
						int_bit_count (raw->takeoff_lock));
	}

	#endif

	#if FATAL

	ASSERT (raw->takeoff_lock & (1 << formation_takeoff));

	#endif

	formation_takeoff = ~(1 << formation_takeoff);

	raw->takeoff_lock &= formation_takeoff;

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR TAKEOFF COMPLETE
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	#if LANDING_ROUTE_CHECK

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_update_entity_landing_locks (sender, receiver,
													//DEBUG_LANDING_LOCK_RESERVE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
													DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
													FALSE);

	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:AFTER : %d, type %s: unlock takeoff route by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
						get_local_entity_index (receiver),
						entity_sub_type_landing_names [raw->sub_type],
						get_local_entity_index (sender),
						raw->total_landing_sites,
						raw->free_landing_sites,
						raw->reserved_landing_sites,
						int_bit_count (raw->landing_lock),
						int_bit_count (raw->landed_lock),
						int_bit_count (raw->takeoff_lock));
	#endif
	#endif

	//
	// spin through takeoff queue (in reverse order)
	//

	member = get_local_entity_first_child (receiver, LIST_TYPE_TAKEOFF_QUEUE);

	if (member)
	{
		//
		// find last entity in the list
		//
		
		while (get_local_entity_child_succ (member, LIST_TYPE_TAKEOFF_QUEUE))
		{
			member = get_local_entity_child_succ (member, LIST_TYPE_TAKEOFF_QUEUE);
		}

		//
		// spin backwards through the list
		//

		while (member)
		{
			if (notify_local_entity (ENTITY_MESSAGE_LOCK_TAKEOFF_ROUTE, receiver, member))
			{
				//#if DEBUG_MODULE

				debug_log ("LD_MSGS: %s (%d) finished taking off - inserting %s (%d) into takeoff route",
											get_local_entity_string (sender, STRING_TYPE_FULL_NAME),
											get_local_entity_index (sender),
											get_local_entity_string (member, STRING_TYPE_FULL_NAME),
											get_local_entity_index (member));

				//#endif

				insert_mobile_into_takeoff_route (member, receiver);

				delete_local_entity_from_parents_child_list (member, LIST_TYPE_TAKEOFF_QUEUE);

				break;
			}
			else
			{
				//#if DEBUG_MODULE

				debug_log ("LD_MSGS: %s (%d) finished taking off - CAN'T insert %s (%d) into takeoff route",
											get_local_entity_string (sender, STRING_TYPE_FULL_NAME),
											get_local_entity_index (sender),
											get_local_entity_string (member, STRING_TYPE_FULL_NAME),
											get_local_entity_index (member));

				//#endif
			}

			member = get_local_entity_child_pred (member, LIST_TYPE_TAKEOFF_QUEUE);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_unreserve_landing_site (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	landing
		*raw;

	int
		count;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (landing *) get_local_entity_data (receiver);

	count = va_arg (pargs, int);

	#if DEBUG_MODULE

	if (raw->reserved_landing_sites < 0)
	{
	
		#if FATAL
		debug_fatal
		#else
		debug_log
		#endif
		("LD_MSGS:%d, type %d: INVALID: unreserve landing by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}
	else
	{
	
		#if LANDING_LOCK_USER_ONLY
		if (sender == get_gunship_entity ())
		#endif
		debug_log ("LD_MSGS:BEFORE: %d, type %d: unreserve landing by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	}

	#endif

	raw->reserved_landing_sites -= count;

	#if FATAL

	ASSERT (raw->reserved_landing_sites >= 0);

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR NEGOTIATE LANDING POSITION
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	#if LANDING_ROUTE_CHECK

	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_update_entity_landing_locks (sender, receiver,
													DEBUG_LANDING_LOCK_RESERVE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_SITE_LOCK,
													//DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK,
													//DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK,
													FALSE);
	
  	#if DEBUG_MODULE
	#if LANDING_LOCK_USER_ONLY
	if (sender == get_gunship_entity ())
	#endif
	debug_log ("LD_MSGS:AFTER : %d, type %d: unreserve landing by %d (total %d, free %d, reserved %d, landing %d, landed %d, takeoff %d)",
			get_local_entity_index (receiver),
			entity_sub_type_landing_names [raw->sub_type],
			get_local_entity_index (sender),
			raw->total_landing_sites,
			raw->free_landing_sites,
			raw->reserved_landing_sites,
			int_bit_count (raw->landing_lock),
			int_bit_count (raw->landed_lock),
			int_bit_count (raw->takeoff_lock));
	#endif
	#endif

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_waypoint_taken_off_reached (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

//	entity
//		*task;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE

	debug_log ("LD_MSGS:%d, member taken off mb %s %d", get_local_entity_index (receiver), get_local_entity_string (sender, STRING_TYPE_FULL_NAME), get_local_entity_index (sender));

	#endif

	// get takeoff group
#if 0
	task = get_local_landing_entity_task (receiver, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	set_local_landing_route_clear (task, sender);
#endif
	//
	// Unlock takeoff
	//

	notify_local_entity (ENTITY_MESSAGE_UNLOCK_TAKEOFF_ROUTE, receiver, sender);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_landing_message_responses (void)
{
	overload_mobile_message_responses (ENTITY_TYPE_LANDING);

	#if DEBUG_MODULE >= 2

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_LINK_CHILD] 								= response_to_link_child;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_UNLINK_CHILD]								= response_to_unlink_child;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_LINK_PARENT]								= response_to_link_parent;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_UNLINK_PARENT]								= response_to_unlink_parent;

	#endif

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_LANDING_SITE_REQUEST]					= response_to_landing_site_request;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_LOCK_LANDING_ROUTE]						= response_to_lock_landing_route;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_LOCK_LANDING_SITE]						= response_to_lock_landing_site;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_LOCK_TAKEOFF_ROUTE]						= response_to_lock_takeoff_route;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_RESERVE_LANDING_SITE]					= response_to_reserve_landing_site;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_SET_ENTITY_POSITION]						= response_to_set_entity_position;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_TASK_TERMINATED]							= response_to_task_terminated;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE]					= response_to_unlock_landing_route;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_UNLOCK_LANDING_SITE]						= response_to_unlock_landing_site;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_UNLOCK_TAKEOFF_ROUTE]					= response_to_unlock_takeoff_route;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_UNRESERVE_LANDING_SITE]					= response_to_unreserve_landing_site;

	message_responses[ENTITY_TYPE_LANDING][ENTITY_MESSAGE_WAYPOINT_TAKEN_OFF_REACHED]			= response_to_waypoint_taken_off_reached;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if LANDING_ROUTE_CHECK

void debug_update_entity_landing_locks (entity *en, entity *landing, debug_landing_lock lock, int 	lock_flag)
{

	debug_landing_lock_type
		*item;

	item = debug_landing_lock_list;

	while (item)
	{

		if (item->en == en)
		{

			break;
		}

		item = item->next;
	}

	if (!item)
	{

		item = (debug_landing_lock_type *) malloc_heap_mem (sizeof (debug_landing_lock_type));

		memset (item, 0, sizeof (debug_landing_lock_type));

		item->en = en;

		item->next = debug_landing_lock_list;

		debug_landing_lock_list = item;
	}

	item->landing_en = landing;

	#if DEBUG_MODULE

	debug_log ("LD_MSGS: %s check %s (%d) at landing %d %s %s",
					entity_side_names [get_local_entity_int_value (en, INT_TYPE_SIDE)],
					get_local_entity_type_name (en),
					get_local_entity_index (en),
					get_local_entity_index (landing),
					debug_landing_lock_unlock_names [lock_flag],
					debug_landing_lock_names [lock]);

	#endif

	#if FATAL

	if (item->locks [lock] == lock_flag)
	{

		int
			loop;

		entity
			*keysite;

		keysite = get_local_entity_parent (landing, LIST_TYPE_LANDING_SITE);

		debug_log ("LD_MSGS: %s check %s:%s (%d) at landing %d %s %s",
					entity_side_names [get_local_entity_int_value (en, INT_TYPE_SIDE)],
					get_local_entity_type_name (en),
					get_local_entity_string (en, STRING_TYPE_FULL_NAME),
					get_local_entity_index (en),
					get_local_entity_index (landing),
					get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
					debug_landing_lock_unlock_names [lock_flag],
					debug_landing_lock_names [lock]);

		loop = 0;

		for (loop = 0; loop < NUM_DEBUG_LANDING_LOCKS; loop ++)
		{

			debug_log ("LD_MSGS: locks %d", item->locks [loop]);
		}

		ASSERT (item->locks [lock] != lock_flag);
	}

	#endif

	item->locks [lock] = lock_flag;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if LANDING_ROUTE_CHECK

void destroy_debug_landing_route_check (void)
{
	debug_landing_lock_type
		*destroy_item,
		*item;

	item = debug_landing_lock_list;

	while (item)
	{

		destroy_item = item;

		item = item->next;

		free_mem (destroy_item);
	}

	debug_landing_lock_list = NULL;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if LANDING_ROUTE_CHECK

void destroy_debug_entity_landing_route_check (entity *en)
{
	debug_landing_lock_type
		*last_item,
		*item;

	item = debug_landing_lock_list;

	last_item = NULL;

	while (item)
	{

		if (item->en == en)
		{

			if (last_item)
			{

				last_item->next = item->next;
			}

			if (item == debug_landing_lock_list)
			{

				debug_landing_lock_list = item->next;
			}
	
			free_mem (item);

			return;
		}

		last_item = item;

		item = item->next;
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if LANDING_ROUTE_CHECK

void pack_debug_entity_landing_locks (pack_modes mode)
{

	debug_landing_lock_type
		*item;

	if (mode != PACK_MODE_SERVER_SESSION)
	{

		return;
	}

	item = debug_landing_lock_list;

	while (item)
	{
		pack_int_value (NULL, INT_TYPE_VALID, TRUE);

		pack_entity_safe_ptr (item->en);

		pack_entity_safe_ptr (item->landing_en);

		debug_log ("LD_MSGS: packing landing lock for %s (%d) landing entity %d",
						get_local_entity_string (item->en, STRING_TYPE_FULL_NAME),
						get_local_entity_index (item->en),
						get_local_entity_index (item->landing_en));

		pack_int_value (NULL, INT_TYPE_VALUE, item->locks [DEBUG_LANDING_LOCK_RESERVE_LOCK]);

		item = item->next;
	}

	pack_int_value (NULL, INT_TYPE_VALID, FALSE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if LANDING_ROUTE_CHECK

void unpack_debug_entity_landing_locks (pack_modes mode)
{

	int
		valid;

	debug_landing_lock_type
		*item;

	if (mode != PACK_MODE_SERVER_SESSION)
	{

		return;
	}

	debug_landing_lock_list = NULL;

	valid = unpack_int_value (NULL, INT_TYPE_VALID);

	while (valid)
	{

		item = (debug_landing_lock_type *) malloc_heap_mem (sizeof (debug_landing_lock_type));

		memset (item, 0, sizeof (debug_landing_lock_type));

		item->en = (entity *) unpack_entity_safe_ptr ();

		item->landing_en = (entity *) unpack_entity_safe_ptr ();

		debug_log ("LD_MSGS: unpacking landing lock for %s (%d) landing entity %d",
						get_local_entity_string (item->en, STRING_TYPE_FULL_NAME),
						get_local_entity_index (item->en),
						get_local_entity_index (item->landing_en));

		item->locks [DEBUG_LANDING_LOCK_RESERVE_LOCK] = unpack_int_value (NULL, INT_TYPE_VALUE);

		item->next = debug_landing_lock_list;

		debug_landing_lock_list = item;

		valid = unpack_int_value (NULL, INT_TYPE_VALID);
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
