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

#define DEBUG_MODULE	0

#define MESSAGE_LIST_INC	100

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	current_message_timer = 0.0;

static message_log_type
	*message_log = NULL;

static int
	num_messages = 0,
	max_messages = 0,
	current_message = -1,
	group_wingman_cycle_forwards = FALSE;

static rgb_colour
	message_side_colour [NUM_ENTITY_SIDES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void clear_in_flight_received_message (void);

static void process_message_attack_my_target (entity *en, entity *wingman);

static void process_message_help_me (entity *en, entity *wingman);

static void process_message_return_to_base (entity *en);

static void process_message_weapons_hold (entity *en, entity *wingman, int state, int play_speech);

static void process_message_hold_position (entity *en, entity *wingman);

static void process_message_rejoin_formation (entity *en, entity *wingman);

static void process_message_bob_up (entity *en, entity *wingman);

static void process_message_change_formation (entity *en, entity *group, int new_formation);

static void process_message_request_airstrike (entity *en);

static void process_message_request_artillery (entity *en);

static void process_message_request_assistance (entity *en);

static void set_new_display_message (int index);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

message_log_type *get_message_log (int index)
{
	ASSERT ((index >= 0) && (index < num_messages));

	return &message_log [index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_message_log_number_of_messages (void)
{
	return num_messages;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

message_log_type *get_current_display_message (void)
{
	if (current_message == -1)
	{
		return NULL;
	}
	else
	{
		return &message_log [current_message];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_message_log (void)
{
	ASSERT (message_log == NULL);

	num_messages = 0;

	max_messages = 0;

	clear_in_flight_received_message ();

	message_side_colour [ENTITY_SIDE_NEUTRAL] = sys_col_white;

	message_side_colour [ENTITY_SIDE_BLUE_FORCE].r = 60;
	message_side_colour [ENTITY_SIDE_BLUE_FORCE].g = 78;
	message_side_colour [ENTITY_SIDE_BLUE_FORCE].b = 255;
	message_side_colour [ENTITY_SIDE_BLUE_FORCE].a = 255;

	message_side_colour [ENTITY_SIDE_RED_FORCE].r = 255;
	message_side_colour [ENTITY_SIDE_RED_FORCE].g = 20;
	message_side_colour [ENTITY_SIDE_RED_FORCE].b = 0;
	message_side_colour [ENTITY_SIDE_RED_FORCE].a = 255;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_message_log (void)
{
	message_log_type
		*log;

	int
		loop;

	if (message_log)
	{
		for (loop = 0; loop < num_messages; loop ++)
		{
			log = &message_log [loop];

			ASSERT (log);

			if (log->string)
			{
				free_mem (log->string);
			}
		}

		free_mem (message_log);

		message_log = NULL;
	}

	clear_in_flight_received_message ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_in_flight_received_message (void)
{
	current_message_timer = 0.0;

	current_message = -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int message_intended_for_recipient (entity *sender, entity *target, message_text_types type)
{
	if (!get_pilot_entity ())
	{
		//
		// can't display messages until player is properly in the game
		//

		return FALSE;
	}

	switch (type)
	{
		case MESSAGE_TEXT_SYSTEM_NEW_PILOT:
		case MESSAGE_TEXT_SYSTEM_ENTITY_KILLED:
		case MESSAGE_TEXT_SYSTEM_KEYSITE_CAPTURED:
		case MESSAGE_TEXT_SYSTEM_KEYSITE_DESTROYED:
		case MESSAGE_TEXT_LOCAL_MESSAGE:
		{
			//
			// all pilots display these messages
			//

			return TRUE;
		}

		case MESSAGE_TEXT_SYSTEM_RECON_DATA:
		case MESSAGE_TEXT_SYSTEM_ENTITY_UNDER_ATTACK:
		{
			ASSERT (target);

			if (get_local_entity_int_value (target, INT_TYPE_SIDE) == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
			{
				//
				// message broadcast to all pilots on this side
				//

				return TRUE;
			}

			break;
		}

		case MESSAGE_TEXT_SYSTEM_TASK_COMPLETED:
		{
			//
			// all pilots on this side display these messages - but only if the task was a primary task
			//

			ASSERT (target);

			if (task_database [get_local_entity_int_value (target, INT_TYPE_ENTITY_SUB_TYPE)].primary_task)
			{
				if (get_local_entity_int_value (target, INT_TYPE_SIDE) == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
				{
					return TRUE;
				}
			}

			break;
		}

		case MESSAGE_TEXT_PILOT_STRING:
		{
			ASSERT (sender);

			ASSERT (target);

			if (target == get_pilot_entity ())
			{
				//
				// personal message for this pilot
				//

				return TRUE;
			}

			if (sender == get_pilot_entity ())
			{
				//
				// Echo Message sent by this pilot
				//

				return TRUE;
			}

			if (target == get_session_entity ())
			{
				//
				// message broadcast to all pilots 
				//

				return TRUE;
			}

			ASSERT (target);

			if ((get_local_entity_type (target) == ENTITY_TYPE_FORCE) && (get_pilot_entity () != sender))
			{
				//
				// message broadcast to all pilots on this side (but don't display it if you sent it!!)
				//

				if (get_local_entity_int_value (target, INT_TYPE_SIDE) == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
				{
					return TRUE;
				}
			}

			break;
		}

		case MESSAGE_TEXT_WINGMAN_STRING:
		case MESSAGE_TEXT_SHORT_WINGMAN_STRING:
		{
			entity
				*parent;

			ASSERT (sender);
			ASSERT (target);

			parent = get_local_entity_parent (get_pilot_entity (), LIST_TYPE_AIRCREW);

			if (target == parent)
			{
				//
				// personal message for this pilot
				//

				return TRUE;
			}

			break;
		}
		
		case MESSAGE_WINGMAN_STATUS_REPORT:
		{
			if (target == get_pilot_entity())
				return TRUE;

			break;	
		}

		default:
		{
			debug_fatal ("MESSAGE: Unknown message type %d", type);
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *format_incoming_message (message_log_type *message, entity *sender, entity *target, char *raw_string)
{
	message_text_types
		type;

	const char
		*pilot_name,
		*flight_name;
	char
		temp_string [512];

	entity
		*group,
		*gunship,
		*subject,
		*objective;

	vec3d
		*pos;

	int
		side,
		enemy_side,
		member_id;

	ASSERT (message);

	temp_string [0] = 0;

	type = message->type;

	message->position.x = -1;
	message->position.y = -1;
	message->position.z = -1;

	message->colour = message_side_colour [ENTITY_SIDE_NEUTRAL];

	pos = NULL;

	subject = NULL;

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	enemy_side = get_enemy_side (side);

	//
	// format text
	//

	switch (type)
	{
		case MESSAGE_TEXT_PILOT_STRING:
		case MESSAGE_TEXT_WINGMAN_STRING:
		case MESSAGE_TEXT_SHORT_WINGMAN_STRING:
		case MESSAGE_TEXT_LOCAL_MESSAGE:
		{
			ASSERT (sender);

			ASSERT (raw_string);

			if (type == MESSAGE_TEXT_LOCAL_MESSAGE)
			{
				pilot_name = NULL;
				gunship = sender;
			}
			else
			{
				pilot_name = get_local_entity_string (sender, STRING_TYPE_PILOTS_NAME);
				gunship = get_local_entity_parent (sender, LIST_TYPE_AIRCREW);
			}

			if (gunship)
			{
				group = get_local_entity_parent (gunship, LIST_TYPE_MEMBER);

				if (group)
				{
					flight_name = get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN);
					member_id = get_local_entity_int_value (gunship, INT_TYPE_GROUP_MEMBER_ID);

					if (pilot_name)
						sprintf (temp_string, "%s (%s 1-%d): %s", pilot_name, flight_name, member_id, raw_string);
					else
						sprintf (temp_string, "%s 1-%d: %s", flight_name, member_id, raw_string);

					get_local_entity_vec3d (gunship, VEC3D_TYPE_POSITION, &(message->position));

					break;
				}
			}

			sprintf (temp_string, "%s : %s", pilot_name, raw_string);

			message->colour = message_side_colour [ENTITY_SIDE_NEUTRAL];

			break;
		}
		
		case MESSAGE_WINGMAN_STATUS_REPORT:
		{
			group = get_local_entity_parent (sender, LIST_TYPE_MEMBER);

			ASSERT(get_local_entity_type(sender) == ENTITY_TYPE_HELICOPTER);

			// callsign
			if (group)
			{
				flight_name = get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN);

				member_id = get_local_entity_int_value (sender, INT_TYPE_GROUP_MEMBER_ID);

				sprintf (temp_string, "%s 1-%d: ", flight_name, member_id);

				get_local_entity_vec3d (sender, VEC3D_TYPE_POSITION, &(message->position));
			}
			else
				temp_string[0] = '\0';

			// weapons
			{
				weapon_count weapon_load[10];
				unsigned i, not_first = FALSE;

				get_local_entity_weapon_load(sender, weapon_load, 10);

				for (i=0; weapon_load[i].weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON; i++)
				{
					if (weapon_load[i].weapon_type != ENTITY_SUB_TYPE_WEAPON_CHAFF
						&& weapon_load[i].weapon_type != ENTITY_SUB_TYPE_WEAPON_FLARE
						&& weapon_load[i].count > 0)
					{
						snprintf (temp_string, 511, "%s%s %s %d ", 
							temp_string, (not_first ? "," : ""),
							weapon_database[weapon_load[i].weapon_type].hud_name, weapon_load[i].count);

						not_first = TRUE;
					}
				}

			}

			// damage
			{
				helicopter
					*raw;
			
				int
					percent_damaged;
			
				char
					*damage;

				raw = get_local_entity_data (sender);
				percent_damaged = (100 * raw->ac.damage_level) / aircraft_database[raw->ac.mob.sub_type].initial_damage_level;

				if (percent_damaged == 100)
					damage = "No damage";
				else if (percent_damaged > 75)
					damage = "Slight damage";
				else if (percent_damaged > 50)
					damage = "Moderate damage";
				else if (percent_damaged > 25)
					damage = "Heavy damage";
				else
					damage = "Critical damage";
				
				snprintf (temp_string, 511, "%s, %s", temp_string, damage);
			}

			message->colour = message_side_colour [ENTITY_SIDE_NEUTRAL];

			break;	
		}

		case MESSAGE_TEXT_SYSTEM_ENTITY_KILLED:
		{
			ASSERT (sender);

			ASSERT (target);

			ASSERT (raw_string == NULL);

			sprintf (temp_string, "%s %s %s", get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_trans ("destroyed by"), get_local_entity_string (sender, STRING_TYPE_FULL_NAME));

			get_local_entity_vec3d (target, VEC3D_TYPE_POSITION, &(message->position));

			if (get_local_entity_int_value (target, INT_TYPE_SIDE) == side)
			{
				message->colour = message_side_colour [enemy_side];
			}
			else
			{
				message->colour = message_side_colour [side];
			}

			subject = target;

			break;
		}

		case MESSAGE_TEXT_SYSTEM_ENTITY_UNDER_ATTACK:
		{
			ASSERT (sender);

			ASSERT (target);

			ASSERT (raw_string == NULL);

			ASSERT ((get_local_entity_type (target) == ENTITY_TYPE_GROUP) || (get_local_entity_type (target) == ENTITY_TYPE_KEYSITE));

			if (get_local_entity_type (target) == ENTITY_TYPE_GROUP)
			{
				entity
					*division;

				division = get_local_entity_parent (target, LIST_TYPE_DIVISION);

				ASSERT (division);

				sprintf (temp_string, "%s, %s %s %s",
							get_local_entity_string (target, STRING_TYPE_DIVISION_NAME),
							get_local_entity_string (division, STRING_TYPE_DIVISION_NAME),
							get_trans ("under attack by"),
							get_trans (get_local_entity_string (sender, STRING_TYPE_FULL_NAME)));
			}
			else if (get_local_entity_type (target) == ENTITY_TYPE_KEYSITE)
			{
				sprintf (temp_string, "%s %s %s", get_local_entity_string (target, STRING_TYPE_KEYSITE_NAME), get_trans ("under attack by"), get_local_entity_string (sender, STRING_TYPE_FULL_NAME));
			}
			else
			{
				sprintf (temp_string, "%s %s %s", get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_trans ("under attack by"), get_local_entity_string (sender, STRING_TYPE_FULL_NAME));
			}

			pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

			ASSERT (pos);

			message->position = *pos;

			ASSERT (get_local_entity_int_value (target, INT_TYPE_SIDE) == side);

			message->colour = message_side_colour [enemy_side];

			subject = sender;

			break;
		}

		case MESSAGE_TEXT_SYSTEM_RECON_DATA:
		{
			ASSERT (target);

			ASSERT (raw_string);

			sprintf (temp_string, "%s", raw_string);

			if (sender)
			{
				pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

				subject = sender;
			}
			else
			{
				pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

				subject = target;
			}

			ASSERT (pos);

			message->position = *pos;

			ASSERT (get_local_entity_int_value (target, INT_TYPE_SIDE) == side);

			message->colour = message_side_colour [side];

			break;
		}

		case MESSAGE_TEXT_SYSTEM_TASK_COMPLETED:
		{
			ASSERT (sender);		// sender is the group

			ASSERT (target);		// target is the task

			ASSERT (raw_string == NULL);

			sprintf (temp_string, "%s %s %s %s",
											get_trans (get_local_entity_string (target, STRING_TYPE_SHORT_DISPLAY_NAME)),
											get_trans (task_debrief_result_names [get_local_entity_int_value (target, INT_TYPE_TASK_COMPLETED)]),
											get_trans ("by"),
											get_trans (get_local_entity_string (sender, STRING_TYPE_FULL_NAME)));

			objective = get_local_entity_parent (target, LIST_TYPE_TASK_DEPENDENT);

			if (objective)
			{
				pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

				subject = objective;
			}
			else
			{
				pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

				subject = sender;
			}

			if (pos)
			{		
				message->position = *pos;
			}

			ASSERT (get_local_entity_int_value (sender, INT_TYPE_SIDE) == side);

			message->colour = message_side_colour [side];

			break;
		}

		case MESSAGE_TEXT_SYSTEM_KEYSITE_CAPTURED:
		{
			ASSERT (sender);		// sender is the keysite

			ASSERT (raw_string == NULL);

			sprintf (temp_string, "%s %s %s",
							get_local_entity_string (sender, STRING_TYPE_KEYSITE_NAME),
							get_trans ("captured by"),
							entity_side_short_names [get_local_entity_int_value (sender, INT_TYPE_SIDE)]);

			get_local_entity_vec3d (sender, VEC3D_TYPE_POSITION, &(message->position));

			if (get_local_entity_int_value (sender, INT_TYPE_SIDE) == side)
			{
				message->colour = message_side_colour [side];
			}
			else
			{
				message->colour = message_side_colour [enemy_side];
			}

			subject = sender;

			break;
		}

		case MESSAGE_TEXT_SYSTEM_KEYSITE_DESTROYED:
		{
			ASSERT (sender);		// sender is the keysite

			ASSERT (raw_string == NULL);

			sprintf (temp_string, "%s %s", get_local_entity_string (sender, STRING_TYPE_KEYSITE_NAME), get_trans ("destroyed"));

			get_local_entity_vec3d (sender, VEC3D_TYPE_POSITION, &(message->position));

			if (get_local_entity_int_value (sender, INT_TYPE_SIDE) == side)
			{
				message->colour = message_side_colour [enemy_side];
			}
			else
			{
				message->colour = message_side_colour [side];
			}

			subject = sender;

			break;
		}

		default:
		{
			ASSERT (raw_string);

			strcpy (temp_string, raw_string);

			message->colour = message_side_colour [ENTITY_SIDE_NEUTRAL];

			break;
		}
	}

	ASSERT (strlen (temp_string) > 0);

	message->string = malloc_heap_mem (strlen (temp_string) + 4);

	strcpy (message->string, temp_string);

	return subject;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_message_objective_view_interest_level (entity *sender, entity *target, message_text_types type)
{
	entity
		*en;

	switch (type)
	{
		case MESSAGE_TEXT_SYSTEM_ENTITY_KILLED:
		{
			//
			// Show victim + aggressor
			//

			set_local_entity_float_value (sender, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);
			set_local_entity_float_value (target, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

			break;
		}
		case MESSAGE_TEXT_SYSTEM_ENTITY_UNDER_ATTACK:
		{
			//
			// Show victim (target is a group) + aggressor
			//
			
			if (get_local_entity_type (target) == ENTITY_TYPE_GROUP)
			{
				en = get_local_entity_ptr_value (target, PTR_TYPE_GROUP_LEADER);

				if (en)
				{
					set_local_entity_float_value (en, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);
				}
			}

			set_local_entity_float_value (sender, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);

			break;
		}
		
		case MESSAGE_TEXT_SYSTEM_TASK_COMPLETED:
		{
			//
			// Show group leader (sender is a group)
			//
			
			en = get_local_entity_ptr_value (sender, PTR_TYPE_GROUP_LEADER);

			if (en)
			{
				set_local_entity_float_value (en, FLOAT_TYPE_VIEW_INTEREST_LEVEL, DEFAULT_VIEW_INTEREST_LEVEL);
			}

			break;
		}

		case MESSAGE_TEXT_SYSTEM_KEYSITE_CAPTURED:
		case MESSAGE_TEXT_SYSTEM_KEYSITE_DESTROYED:
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_incoming_message (entity *sender, entity *target, message_text_types type, char *string)
{
	message_log_type
		*temp,
		*new_message;

	entity
		*subject;

	//
	// check that this player SHOULD display the message
	//

	if (!message_intended_for_recipient (sender, target, type))
	{
		return;
	}

	//
	// Need more log space ?
	//

	if (num_messages >= max_messages)
	{
		max_messages += MESSAGE_LIST_INC;

		temp = malloc_heap_mem (sizeof (message_log_type) * max_messages);

		if (num_messages > 0)
		{
			ASSERT (message_log);

			memcpy (temp, message_log, sizeof (message_log_type) * num_messages);

			free_mem (message_log);
		}

		message_log = temp;
	}

	//
	// add to log
	//

	new_message = &message_log [num_messages];

	new_message->type = type;

	if (get_session_entity ())
	{
		new_message->day = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY);

		new_message->time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
	}
	else
	{
		new_message->day = 0;

		new_message->time_of_day = 0.0;
	}

	subject = format_incoming_message (new_message, sender, target, string);

	num_messages ++;
	
	// Jabberwock 031129 Chat server log
	if ((type == MESSAGE_TEXT_PILOT_STRING) && (get_comms_model () == COMMS_MODEL_SERVER))
	{
		server_log ("%s: %s", get_local_entity_string (sender, STRING_TYPE_PILOTS_NAME), string);
	}

	if ((current_message == -1) || (message_text_info [type].skip_queue))
	{
		set_new_display_message (num_messages - 1);
	}

	notify_campaign_screen (CAMPAIGN_SCREEN_NEW_MESSAGE, subject);

	set_message_objective_view_interest_level (sender, target, type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_last_received_message (event *arg)
{
	if (message_log)
	{
		if (current_message == -1)
		{
			set_new_display_message (num_messages - 1);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_radio_message (entity *en, message_categories type, int value)
{
	entity
		*group,
		*wingman;

	switch (type)
	{
		case MESSAGE_WINGMAN_ATTACK_MY_TARGET:
		{
			wingman = get_local_entity_safe_ptr (value);

			process_message_attack_my_target (en, wingman);

			break;
		}
		case MESSAGE_WINGMAN_ATTACK_PFZ:
		{
			wingman = get_local_entity_safe_ptr (value);
			process_message_attack_pfz (en, wingman);
			
			break;	
		}
		case MESSAGE_WINGMAN_RETURN_TO_BASE:
		{
			process_message_return_to_base (en);

			break;
		}
		case MESSAGE_WINGMAN_REQUEST_STATUS:
		{
			wingman = get_local_entity_safe_ptr (value);
			if (wingman == get_gunship_entity())
			{
				debug_log("request message from me!");	
			}

			break;
		}
		case MESSAGE_WINGMAN_HELP_ME:
		{
			wingman = get_local_entity_safe_ptr (value);

			process_message_help_me (en, wingman);

			break;
		}
		case MESSAGE_WINGMAN_WEAPONS_HOLD:
		{
			wingman = get_local_entity_safe_ptr (value);

			process_message_weapons_hold (en, wingman, TRUE, TRUE);

			break;
		}
		case MESSAGE_WINGMAN_WEAPONS_FREE:
		{
			wingman = get_local_entity_safe_ptr (value);

			process_message_weapons_hold (en, wingman, FALSE, TRUE);

			break;
		}
		case MESSAGE_WINGMAN_BOB_UP:
		{
			wingman = get_local_entity_safe_ptr (value);

			process_message_bob_up (en, wingman);

			break;
		}
		case MESSAGE_WINGMAN_HOLD_POSITION:
		{
			wingman = get_local_entity_safe_ptr (value);

			process_message_hold_position (en, wingman);

			break;
		}
		case MESSAGE_WINGMAN_REJOIN_FORMATION:
		{
			wingman = get_local_entity_safe_ptr (value);

			process_message_rejoin_formation (en, wingman);

			break;
		}
		case MESSAGE_WINGMAN_REQUEST_TARGET_LIST:
		{
			wingman = get_local_entity_safe_ptr (value);

			transmit_entity_comms_message (ENTITY_COMMS_REQUEST_TARGET_LIST, en, wingman);

			break;
		}
		case MESSAGE_GROUP_ROW_LEFT:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_ROW_LEFT);

			break;
		}
		case MESSAGE_GROUP_ROW_RIGHT:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_ROW_RIGHT);

			break;
		}
		case MESSAGE_GROUP_ECHELON_LEFT:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_ECHELON_LEFT);

			break;
		}
		case MESSAGE_GROUP_ECHELON_RIGHT:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_ECHELON_RIGHT);

			break;
		}
		case MESSAGE_GROUP_COLUMN:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_COLUMN);

			break;
		}
		case MESSAGE_GROUP_WEDGE:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_WEDGE);    

			break;
	    }
//VJ 060305 three new formations for maverick ====>
		case MESSAGE_GROUP_DIAMOND:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_DIAMOND);

			break;
        }
		case MESSAGE_GROUP_STAGGERED_TRAIL_LEFT:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_STAGGERED_TRAIL_LEFT);

			break;
         }
		case MESSAGE_GROUP_STAGGERED_TRAIL_RIGHT:
		{
			group = get_local_entity_safe_ptr (value);

			process_message_change_formation (en, group, FORMATION_STAGGERED_TRAIL_RIGHT);

			break;
       
		}
//VJ 060305 three new formations for maverick <====
		case MESSAGE_LOCAL_BASE_REQUEST_AIRSTRIKE:
		{
			process_message_request_airstrike (en);

			break;
		}
		case MESSAGE_LOCAL_BASE_REQUEST_ARTILLERY:
		{
			process_message_request_artillery (en);

			break;
		}
		case MESSAGE_LOCAL_BASE_REQUEST_ASSISTANCE:
		{
			process_message_request_assistance (en);

			break;
		}
		case MESSAGE_LOCAL_BASE_TRANSMIT_RECON:
		{
			transmit_player_recon_data (en);

			break;
		}
// Jabberwock 031119 CamCom MP compatible
		case MESSAGE_LOCAL_BASE_CAMCOM_MESSAGE:
		{
			create_reaction_to_map_click (en);

			break;
		}		
// Jabberwock 031119 ends
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_client_server_radio_message_response (entity *en, int speech_index, float priority, float expire_time)
{
	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		play_client_server_wingman_message
		(
			en,
			priority,
			expire_time,
			SPEECH_CATEGORY_RADIO_RESPONSE, -1.0,
			SPEECH_INTRODUCTION_ALWAYS,
			SPEECH_ARRAY_WINGMAN_MESSAGES, speech_index
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void play_radio_message_affirmative_response (entity *en, int speech_index, float priority, float expire_time)
{
	int
		index;

	static int
		val = 0;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	index = speech_index;

	switch (val)
	{
		case 1:
		{
			index = SPEECH_WINGMAN_AFFIRMATIVE;

			break;
		}
		case 3:
		{
			index = SPEECH_WINGMAN_ACKNOWLEDGE;

			break;
		}
	}

	val += (rand16 () & 0x03);

	if (val > 3) val = 0;

	play_client_server_radio_message_response (en, index, priority, expire_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void play_client_server_radio_message_affirmative_response (entity *en, int speech_index, float priority, float expire_time)
{
	entity
		*sender;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
	{
		//
		// if the message was to the whole flight group, select a non-player member to make the response
		//

		if (group_wingman_cycle_forwards)
		{
			//
			// forward through w/m list
			//
			
			sender = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

			while (sender)
			{
				play_radio_message_affirmative_response (sender, speech_index, priority, expire_time);

				sender = get_local_entity_child_succ (sender, LIST_TYPE_MEMBER);
			}

			group_wingman_cycle_forwards = FALSE;
		}
		else
		{
			//
			// backward through w/m list
			//
			
			sender = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

			while (get_local_entity_child_succ (sender, LIST_TYPE_MEMBER))
			{
				sender = get_local_entity_child_succ (sender, LIST_TYPE_MEMBER);
			}

			while (sender)
			{
				play_radio_message_affirmative_response (sender, speech_index, priority, expire_time);

				sender = get_local_entity_child_pred (sender, LIST_TYPE_MEMBER);
			}

			group_wingman_cycle_forwards = TRUE;
		}
	}
	else
	{
		//
		// only play speech if the responder is AI controlled
		//
	
		play_radio_message_affirmative_response (en, speech_index, priority, expire_time);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void play_radio_message_negative_response (entity *en, int speech_index, float priority, float expire_time)
{
	int
		index;

	static int
		flag = FALSE;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	index = speech_index;

	if (flag)
	{
		index = SPEECH_WINGMAN_NEGATIVE;
	}

	flag = !flag;

	play_client_server_radio_message_response (en, index, priority, expire_time);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void play_client_server_radio_message_negative_response (entity *en, int speech_index, float priority, float expire_time)
{
	entity
		*sender;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
	{
		//
		// if the message was to the whole flight group, select a non-player member to make the response
		//

		if (group_wingman_cycle_forwards)
		{
			//
			// forward through w/m list
			//
			
			sender = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

			while (sender)
			{
				play_radio_message_negative_response (sender, speech_index, priority, expire_time);

				sender = get_local_entity_child_succ (sender, LIST_TYPE_MEMBER);
			}

			group_wingman_cycle_forwards = FALSE;
		}
		else
		{
			//
			// backward through w/m list
			//
			
			sender = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

			while (get_local_entity_child_succ (sender, LIST_TYPE_MEMBER))
			{
				sender = get_local_entity_child_succ (sender, LIST_TYPE_MEMBER);
			}

			while (sender)
			{
				play_radio_message_negative_response (sender, speech_index, priority, expire_time);

				sender = get_local_entity_child_pred (sender, LIST_TYPE_MEMBER);
			}

			group_wingman_cycle_forwards = TRUE;
		}
	}
	else
	{
		//
		// only play speech if the responder is AI controlled
		//
	
		play_radio_message_negative_response (en, speech_index, priority, expire_time);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MESSAGE SPECIFIC FUNCTIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ATTACK MY TARGET
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_attack_my_target (entity *en, entity *wingman)
{
	entity
		*group,
		*target;

	unsigned int
		valid_members,
		member_number;

	ASSERT (en);

	ASSERT (wingman);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	target = get_local_entity_parent (en, LIST_TYPE_TARGET);

	if (target)
	{
		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group)
		{
			if (get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
			{
//				if (get_local_entity_int_value (target, INT_TYPE_SIDE) != get_local_entity_int_value (group, INT_TYPE_SIDE))
				{
					if (get_local_entity_type (wingman) == ENTITY_TYPE_GROUP)
					{
						valid_members = TASK_ASSIGN_ALL_MEMBERS;
					}
					else
					{
						member_number = get_local_entity_int_value (wingman, INT_TYPE_GROUP_MEMBER_NUMBER);

						valid_members = (1 << member_number);
					}

					//
					// call to "attack my target" also cancels "weapons hold"
					//

					process_message_weapons_hold (en, wingman, FALSE, FALSE);

					//
					// Engage
					//

					engage_specific_target (group, target, valid_members, TRUE);

					play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_ENGAGING_TARGET, 1.0, 10.0);

					return;
				}
			}
		}
	}

	play_client_server_radio_message_negative_response (wingman, SPEECH_WINGMAN_UNABLE_TO_COMPLY, 1.0, 10.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_attack_pfz(entity *en, entity *wingman)
{
	entity
		*group,
		*target;

	ASSERT (en);
	ASSERT (wingman);
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
	ASSERT (get_local_entity_type(wingman) == ENTITY_TYPE_HELICOPTER);
	ASSERT (get_local_entity_int_value(wingman, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);
	if (group && get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
	{
		if (get_local_entity_int_value (wingman, INT_TYPE_WEAPONS_HOLD))
			play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ACKNOWLEDGE, 1.0, 10.0);
		else
			play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_ENGAGING_TARGET, 1.0, 10.0);
	
		return;
	}

	play_client_server_radio_message_negative_response (wingman, SPEECH_WINGMAN_UNABLE_TO_COMPLY, 1.0, 10.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Help Me
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_help_me (entity *en, entity *wingman)
{
	entity
		*group,
		*target,
		*new_task;

	unsigned int
		valid_members,
		member_number;

	int
		task_assigned;

	ASSERT (en);

	ASSERT (wingman);

	new_task = NULL;

	task_assigned = FALSE;

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (group)
	{
		if (get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
		{
			target = get_local_entity_first_child (en, LIST_TYPE_TARGET);

			while (target)
			{
				if ((get_local_entity_int_value (target, INT_TYPE_IDENTIFY_AIRCRAFT)) ||
						(get_local_entity_int_value (target, INT_TYPE_IDENTIFY_VEHICLE)))
				{
					new_task = create_engage_task (group, target, en, TRUE);

					if (new_task)
					{
						if (get_local_entity_type (wingman) == ENTITY_TYPE_GROUP)
						{
							valid_members = TASK_ASSIGN_ALL_MEMBERS;
						}
						else
						{
							member_number = get_local_entity_int_value (wingman, INT_TYPE_GROUP_MEMBER_NUMBER);

							valid_members = (1 << member_number);
						}

						if (assign_task_to_group (group, new_task, TASK_ASSIGN_NO_MEMBERS))
						{
							task_assigned = TRUE;
						}
						else
						{
							debug_log ("MESSAGE: can't assign my persuer %s to my wingmen", get_local_entity_string (target, STRING_TYPE_FULL_NAME));
						}
					}
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_TARGET);
			}
		}

		if (task_assigned)
		{
			play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_COMING_TO_ASSIST, 1.0, 8.0);

			//
			// call to "help me" also cancels "weapons hold"
			//

			process_message_weapons_hold (en, wingman, FALSE, FALSE);
		}
		else
		{
			play_client_server_radio_message_negative_response (wingman, SPEECH_WINGMAN_UNABLE_TO_COMPLY, 1.0, 8.0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// RETURN TO BASE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_return_to_base (entity *en)
{
	entity
		*group;

	ASSERT (en);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	if (get_local_group_primary_guide (group))
	{
		group_return_to_base (group);

		play_client_server_radio_message_affirmative_response (group, SPEECH_WINGMAN_ROGER_RETURNING_TO_BASE, 0.2, 20.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WEAPONS FREE / WEAPONS HOLD
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_weapons_hold (entity *en, entity *wingman, int state, int play_speech)
{
	entity
		*group,
		*guide,
		*task,
		*member;

	unsigned int
		member_number,
		valid_members;

	ASSERT (wingman);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	valid_members = 0;

	group = NULL;

	if (get_local_entity_type (wingman) == ENTITY_TYPE_GROUP)
	{
		group = wingman;

		member = get_local_entity_first_child (wingman, LIST_TYPE_MEMBER);

		while (member)
		{
			if (get_local_entity_int_value (member, INT_TYPE_WEAPONS_HOLD) != state)
			{
				set_client_server_entity_int_value (member, INT_TYPE_WEAPONS_HOLD, state);

				//
				// If setting weapons free, see if member should be assigned to existing engage tasks
				//
				
				if (!state)
				{
					entity* target;

					if (get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
					{
						member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));
	
						// add engage task for all PFZ targets
						for (target = get_local_entity_first_child (member, LIST_TYPE_DESIGNATED_TARGET);
							 target;
							 target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET))
						{
							engage_specific_target(group, target, member_number, FALSE);
						}
					}
					
					guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

					if (guide)
					{
						task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

						ASSERT (task);
						
						if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_TASK_ENGAGE)
						{	
							valid_members |= member_number;
						}
					}
				}
			}

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}
	else
	{
		member = wingman;
	
		group = get_local_entity_parent (member, LIST_TYPE_MEMBER);
		
		set_client_server_entity_int_value (member, INT_TYPE_WEAPONS_HOLD, state);

		//
		// If setting weapons free, see if member should be assigned to existing engage tasks
		//
				
		if (!state)
		{
			entity* target;

			member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

			if (get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY))
			{
				// add engage task for all PFZ targets
				for (target = get_local_entity_first_child (member, LIST_TYPE_DESIGNATED_TARGET);
					 target;
					 target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET))
				{
					engage_specific_target(group, target, member_number, FALSE);
				}
			}

			guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

			if (guide)
			{
				task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

				ASSERT (task);
						
				if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_TASK_ENGAGE)
					valid_members |= member_number;
			}
		}
	}

	if (play_speech)
	{
		if (state)
		{
			play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_WEAPONS_HOLD, 0.6, 6.0);
		}
		else
		{
			play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_WEAPONS_FREE, 0.6, 6.0);
		}
	}
	
	//
	// re-assign "forgotten" engage tasks
	//

	if (valid_members)
	{
		ASSERT (group);
		
		assign_engage_tasks_to_group (group, valid_members);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HOLD POSITION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_hold_position (entity *en, entity *wingman)
{
	entity
		*member;

	ASSERT (wingman);

	if (get_local_entity_type (wingman) == ENTITY_TYPE_GROUP)
	{
		member = get_local_entity_first_child (wingman, LIST_TYPE_MEMBER);

		while (member)
		{
			process_message_hold_position (en, member);

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}
	else
	{
		if ((!get_local_entity_int_value (wingman, INT_TYPE_GROUP_LEADER)) && (get_local_entity_primary_task (wingman)))
		{
			set_client_server_entity_int_value (wingman, INT_TYPE_POSITION_HOLD, TRUE);

			set_client_server_entity_vec3d (wingman, VEC3D_TYPE_WAIT_POSITION, get_local_entity_vec3d_ptr (wingman, VEC3D_TYPE_POSITION));

			play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_MAINTAINING_POSITION, 0.6, 10.0);
		}
		else
		{
			play_client_server_radio_message_negative_response (wingman, SPEECH_WINGMAN_UNABLE_TO_COMPLY, 0.6, 8.0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// REJOIN FORMATION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_rejoin_formation (entity *en, entity *wingman)
{
	entity
		*member;

	ASSERT (wingman);

	if (get_local_entity_type (wingman) == ENTITY_TYPE_GROUP)
	{
		member = get_local_entity_first_child (wingman, LIST_TYPE_MEMBER);

		while (member)
		{
			process_message_rejoin_formation (en, member);

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}
	else
	{
		//
		// Cancel Position Hold
		//
		
		set_client_server_entity_int_value (wingman, INT_TYPE_POSITION_HOLD, FALSE);

		//
		// Play Speech
		//

		play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_REJOINING_FORMATION, 0.5, 7.0);

		//
		// Abort any engage tasks
		//

		terminate_entity_current_engage_task (wingman);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BOB-UP
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_bob_up (entity *en, entity *wingman)
{
	entity
		*guide,
		*follower;

	ASSERT (wingman);

	if (get_local_entity_type (wingman) == ENTITY_TYPE_GROUP)
	{
		guide = get_local_entity_first_child (wingman, LIST_TYPE_GUIDE_STACK);

		while (guide)
		{
			if (get_local_entity_int_value (guide, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER)
			{
				attack_guide_proceed_to_fire_positon (guide);

				follower = get_local_entity_first_child (guide, LIST_TYPE_FOLLOWER);

				if (follower)
				{
					play_client_server_radio_message_affirmative_response (follower, SPEECH_WINGMAN_ROGER_BOBBING_UP, 1.0, 4.0);
				}
			}

			guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
		}
	}
	else
	{
		guide = get_local_entity_parent (wingman, LIST_TYPE_FOLLOWER);

		if (guide)
		{
			if (get_local_entity_int_value (guide, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER)
			{
				attack_guide_proceed_to_fire_positon (guide);

				play_client_server_radio_message_affirmative_response (wingman, SPEECH_WINGMAN_ROGER_BOBBING_UP, 1.0, 4.0);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_change_formation (entity *en, entity *group, int new_formation)
{
	ASSERT (group);

	ASSERT (get_local_entity_type (group) == ENTITY_TYPE_GROUP);

	set_client_server_entity_int_value (group, INT_TYPE_GROUP_FORMATION, new_formation);

	play_client_server_radio_message_affirmative_response (group, SPEECH_WINGMAN_ROGER_MOVING_INTO_ORDERED_POSITION, 0.1, 5.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Request Airstrike
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_request_airstrike (entity *en)
{
	entity
		*target,
		*task_objective,
		*group,
		*assigned_group,
		*new_task;

	entity_sides
		side;

	ASSERT (en);

	new_task = NULL;

	target = get_local_entity_parent (en, LIST_TYPE_TARGET);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (target)
	{
		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		if (get_local_entity_int_value (target, INT_TYPE_SIDE) != side)
		{
			switch (get_local_entity_type (target))
			{
				case ENTITY_TYPE_SITE:
				case ENTITY_TYPE_SITE_UPDATABLE:
				{
					entity
						*building_group;

					//
					// create deep strike
					//

					building_group = get_local_entity_parent (target, LIST_TYPE_MEMBER);

					if ((building_group) && (get_local_entity_type (building_group) == ENTITY_TYPE_GROUP))
					{
						task_objective = get_local_entity_parent (building_group, LIST_TYPE_BUILDING_GROUP);

						if ((task_objective) && (get_local_entity_type (task_objective) == ENTITY_TYPE_KEYSITE))
						{
							if (get_local_entity_float_value (task_objective, FLOAT_TYPE_EFFICIENCY) >= get_local_entity_float_value (task_objective, FLOAT_TYPE_MINIMUM_EFFICIENCY))
							{
								if (!entity_is_object_of_task (task_objective, ENTITY_SUB_TYPE_TASK_GROUND_STRIKE, side))
								{
									new_task = create_ground_strike_task (side, task_objective, group, TRUE, task_database [ENTITY_SUB_TYPE_TASK_GROUND_STRIKE].task_priority, NULL, NULL);
								}
							}
						}
					}

					break;
				}
				case ENTITY_TYPE_ANTI_AIRCRAFT:
				{
					//
					// create SEAD
					//

					task_objective = get_local_entity_parent (target, LIST_TYPE_MEMBER);

					if (task_objective)
					{
						if (!entity_is_object_of_task (task_objective, ENTITY_SUB_TYPE_TASK_SEAD, side))
						{
							new_task = create_sead_task (side, task_objective, group, TRUE, task_database [ENTITY_SUB_TYPE_TASK_SEAD].task_priority, NULL, NULL);
						}
					}

					break;
				}
				case ENTITY_TYPE_ROUTED_VEHICLE:
				{
					//
					// create CAS
					//

					task_objective = get_local_entity_parent (target, LIST_TYPE_MEMBER);

					if (task_objective)
					{
						if (!entity_is_object_of_task (task_objective, ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT, side))
						{
							new_task = create_close_air_support_task (side, task_objective, group, TRUE, task_database [ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT].task_priority, NULL, NULL);
						}
					}

					break;
				}
			}

			if (new_task)
			{
				assigned_group = get_suitable_registered_group (new_task, NULL);

				if (assigned_group)
				{
					if (assign_primary_task_to_group (assigned_group, new_task))
					{
						//
						// Affirmative response speech...
						//

						play_client_server_speech
						(
							get_session_entity (),
							en,
							get_local_entity_int_value (en, INT_TYPE_SIDE),
							ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
							SOUND_LOCALITY_RADIO,
							0.0,
							1.0,
							20.0,
							SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER,
							SPEECH_CATEGORY_RADIO_RESPONSE,
							-1.0,
							SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_INTRODUCTION,
							SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_REQUEST_ACCEPTED,
							-1
						);

						return;
					}
				}
			}

			//
			// Negative response speech...
			//

			play_client_server_speech
			(
				get_session_entity (),
				en,
				get_local_entity_int_value (en, INT_TYPE_SIDE),
				ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
				SOUND_LOCALITY_RADIO,
				0.0,
				1.0,
				20.0,
				SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER,
				SPEECH_CATEGORY_RADIO_RESPONSE,
				-1.0,
				SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_INTRODUCTION,
				SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_REQUEST_DENIED,
				-1
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Request Artillery
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ARTILLERY_ATTACK_RADIUS	(1.0 * KILOMETRE)

void process_message_request_artillery (entity *en)
{
	entity
		*target,
		*force,
		*group,
		*member,
		*best_group,
		*new_task;

	entity_sides
		side;

	vec3d
		*group_pos,
		*target_pos;

	float
		range,
		best_range,
		weapon_range;

	ASSERT (en);

	new_task = NULL;

	target = get_local_entity_parent (en, LIST_TYPE_TARGET);

	if (target)
	{
		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		if (get_local_entity_int_value (target, INT_TYPE_SIDE) != side)
		{
			//
			// Find closest friendly artillery group
			//

			target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			force = get_local_force_entity (side);

			best_group = NULL;

			best_range = FLT_MAX;

			group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

			while (group)
			{
				if (
						(get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY) ||
						(get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_MLRS)
					)
				{
					if (get_local_entity_int_value (group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
					{
						group_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

						range = get_2d_range (target_pos, group_pos);

						debug_log ("MSG_IN: Artillery Range = %f", range);

						if (range < best_range)
						{
							//
							// Check range is within groups weapon range
							//

							member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

							while (member)
							{
								weapon_range = get_local_entity_max_weapon_range (member);

								if (weapon_range > 0.0)
								{
									if (weapon_range > range)
									{
										best_range = range;

										best_group = group;
									}

									break;
								}

								member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
							}
						}
					}
				}

				group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
			}

			//
			// found group ?
			//

			if (best_group)
			{
				group = best_group;

				if (engage_targets_in_area (group, target_pos, ARTILLERY_ATTACK_RADIUS, get_local_entity_int_value (target, INT_TYPE_TASK_TARGET_TYPE), TRUE))
				{
					debug_log ("MSG_IN: Created Artillery Strike - range %f", best_range);

					//
					// Affirmative response speech...
					//

					play_client_server_speech
					(
						get_session_entity (),
						en,
						get_local_entity_int_value (en, INT_TYPE_SIDE),
						ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
						SOUND_LOCALITY_RADIO,
						0.0,
						1.0,
						20.0,
						SPEECH_ORIGINATOR_GROUND_CONTROLLER,
						SPEECH_CATEGORY_RADIO_RESPONSE,
						-1.0,
						SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
						SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_FIRE_MISSION_RECEIVED,
						-1
					);

					return;
				}

				//
				// Negative response speech... (group available but can't engage)
				//
			
				play_client_server_speech
				(
					get_session_entity (),
					en,
					get_local_entity_int_value (en, INT_TYPE_SIDE),
					ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
					SOUND_LOCALITY_RADIO,
					0.0,
					1.0,
					20.0,
					SPEECH_ORIGINATOR_GROUND_CONTROLLER,
					SPEECH_CATEGORY_RADIO_RESPONSE,
					-1.0,
					SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
					SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_ARTILLERY_SHIFTING_POSITION,
					-1
				);

				return;
			}

			//
			// Negative response speech... (no group available)
			//
		
			play_client_server_speech
			(
				get_session_entity (),
				en,
				get_local_entity_int_value (en, INT_TYPE_SIDE),
				ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
				SOUND_LOCALITY_RADIO,
				0.0,
				1.0,
				20.0,
				SPEECH_ORIGINATOR_GROUND_CONTROLLER,
				SPEECH_CATEGORY_RADIO_RESPONSE,
				-1.0,
				SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
				SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_ARTILLERY_BUSY,
				-1
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Request Assistance
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_message_request_assistance (entity *en)
{
	entity
		*force,
		*group,
		*aggressor;

	ASSERT (en);

	aggressor = get_local_entity_first_child (en, LIST_TYPE_TARGET);

	//
	// check that we actually have at least one pursuer before spinning through the group lists...
	//

	if (aggressor)
	{
		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		ASSERT (group);

		force = get_local_force_entity (get_local_entity_int_value (en, INT_TYPE_SIDE));

		ASSERT (force);

		while (aggressor)
		{
			if (
					(get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT)) ||
					(get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_VEHICLE))
				)
			{
				notify_local_entity (ENTITY_MESSAGE_REQUEST_ASSISTANCE, force, en, aggressor);
			}

			aggressor = get_local_entity_child_succ (aggressor, LIST_TYPE_TARGET);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_incoming_in_flight_message_flag (void)
{
	return (current_message != -1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_in_flight_incoming_messages (void)
{
	int
		hours,
		minutes,
		seconds;

	char
		*s;

	message_log_type
		*log;

	//
	// Don't display message if status message active
	//

	if (get_status_message_displayed ())
	{
		return;
	}

	//
	// Display current message
	//

	log = get_current_display_message ();

	if (log)
	{
		ASSERT (message_log);

		ASSERT (num_messages > 0);

		ASSERT (current_message_timer > 0.0);

		ASSERT (log->string);

		//
		// Don't display message if in-flight intelligence messages are disabled
		//

		if (!get_global_display_in_flight_intelligence_messages ())
		{
			if ((log->type != MESSAGE_TEXT_PILOT_STRING) && (log->type != MESSAGE_TEXT_WINGMAN_STRING))
			{
				return;
			}
		}

		set_ui_font_type (UI_FONT_ARIAL_16);

		set_ui_font_colour (log->colour);

		get_digital_clock_int_values (log->time_of_day, &hours, &minutes, &seconds);

		s = malloc_fast_mem (strlen (log->string) + 20);

		sprintf (s, "[%02d:%02d] %s", hours, minutes, log->string);

		ui_display_text (s, 2, 2);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_message_log (void)
{
	if (current_message != -1)
	{
		ASSERT (message_log);

		ASSERT (num_messages > 0);

		ASSERT (current_message_timer > 0.0);

		if (get_time_acceleration () != TIME_ACCELERATION_PAUSE)
		{
			current_message_timer -= get_delta_time ();

			if (current_message_timer <= 0.0)
			{
				set_new_display_message (current_message + 1);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_new_display_message (int index)
{
	message_log_type
		*log;

	if ((index >= num_messages) || (index < 0))
	{
		current_message = -1;

		current_message_timer = 0.0;
	}
	else
	{
		current_message = index;

		log = &message_log [current_message];

		ASSERT (log);
		ASSERT (log->type < NUM_MESSAGE_TEXT_TYPES);

		current_message_timer = message_text_info [log->type].display_time;

		ASSERT (current_message_timer > 0.0);

		if (point_inside_map_area (&(log->position)))
		{
			add_map_event (MAP_EVENT_LOG_EVENT, log->position.x, log->position.z, current_message_timer);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_message_log (pack_modes mode)
{
	int
		loop,
		index,
		num_packed_messages;

	message_log_type
		*log;

   ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

   switch (mode)
   {
      ////////////////////////////////////////
      case PACK_MODE_SERVER_SESSION:
      case PACK_MODE_CLIENT_SESSION:
      ////////////////////////////////////////
		{
			num_packed_messages = min (num_messages, MAX_LOG_DISPLAY_MESSAGES);

			pack_int_value (NULL, INT_TYPE_VALUE, num_packed_messages);
			pack_int_value (NULL, INT_TYPE_VALUE, current_message);
		
			for (loop = 0; loop < num_packed_messages; loop ++)
			{
				index = (num_messages - loop) - 1;
				
				log = &message_log [index];

				ASSERT (log);

				pack_int_value (NULL, INT_TYPE_VALUE, log->type);

				pack_int_value (NULL, INT_TYPE_DAY, log->day);

				pack_float_value (NULL, FLOAT_TYPE_TIME_OF_DAY, log->time_of_day);

				if (point_inside_map_volume (&(log->position)))
				{
					pack_int_value (NULL, INT_TYPE_VALID, TRUE);
					
					pack_vec3d (NULL, VEC3D_TYPE_POSITION, &(log->position));
				}
				else
				{
					pack_int_value (NULL, INT_TYPE_VALID, FALSE);
				}

				pack_int_value (NULL, INT_TYPE_COLOUR_RED, log->colour.r);
				pack_int_value (NULL, INT_TYPE_COLOUR_GREEN, log->colour.g);
				pack_int_value (NULL, INT_TYPE_COLOUR_BLUE, log->colour.b);

				ASSERT (log->string);

	         pack_string (NULL, STRING_TYPE_PILOT_MESSAGE, log->string);
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_message_log (pack_modes mode)
{
	int
		loop,
		index,
		length;

	message_log_type
		*log;

	static char
		s [STRING_TYPE_MESSAGE_LENGTH + 4];
		
   ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

   switch (mode)
   {
      ////////////////////////////////////////
      case PACK_MODE_SERVER_SESSION:
      case PACK_MODE_CLIENT_SESSION:
      ////////////////////////////////////////
		{
			deinitialise_message_log ();

			num_messages = unpack_int_value (NULL, INT_TYPE_VALUE);
			current_message = unpack_int_value (NULL, INT_TYPE_VALUE);

			if (current_message >= 0)
			{
				current_message = num_messages - 1;
			}
		
			max_messages = num_messages; 

			if (max_messages > 0)
			{
				message_log = malloc_heap_mem (sizeof (message_log_type) * max_messages);
	
				for (loop = 0; loop < num_messages; loop ++)
				{
					index = (num_messages - loop) - 1;
				
					log = &message_log [index];
	
					ASSERT (log);
	
					log->type = unpack_int_value (NULL, INT_TYPE_VALUE);
	
					log->day = unpack_int_value (NULL, INT_TYPE_DAY);
	
					log->time_of_day = unpack_float_value (NULL, FLOAT_TYPE_TIME_OF_DAY);
	
					if (unpack_int_value (NULL, INT_TYPE_VALID))
					{
						unpack_vec3d (NULL, VEC3D_TYPE_POSITION, &(log->position));
					}
					else
					{
						log->position.x = -1;
						log->position.y = -1;
						log->position.z = -1;
					}
	
					log->colour.r = unpack_int_value (NULL, INT_TYPE_COLOUR_RED);
					log->colour.g = unpack_int_value (NULL, INT_TYPE_COLOUR_GREEN);
					log->colour.b = unpack_int_value (NULL, INT_TYPE_COLOUR_BLUE);
					log->colour.a = 255;
	
					unpack_string (NULL, STRING_TYPE_PILOT_MESSAGE, s);

					length = strlen (s);

					ASSERT (length <= STRING_TYPE_MESSAGE_LENGTH);
					
					log->string = malloc_heap_mem (length + 4);

					strcpy (log->string, s);
				}
			}
			else
			{
				ASSERT (num_messages == 0);
			}

			set_new_display_message (current_message);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


