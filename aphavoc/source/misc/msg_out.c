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

#include "ai/taskgen/engage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE	0

#define MAX_KEYBOARD_MESSAGE_LENGTH	96

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MESSAGE_TYPE
{
	message_categories
		type;

	int
		value;
};

typedef struct MESSAGE_TYPE	message_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MESSAGE_ACTION_TYPE
{

	int
		number_of_actions;

	message_type
		message,
		*actions;

	char
		*title,
		**action_text;

	int
		*keycodes;

	void
		((*function) (message_type message));

	struct MESSAGE_ACTION_TYPE
		*next;
};

typedef struct MESSAGE_ACTION_TYPE message_action_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static message_type
	current_message,
	message_destination;

static message_action_type
	*message_database;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	in_flight_messages = FALSE;

static char
	keyboard_message [MAX_KEYBOARD_MESSAGE_LENGTH],
	attack_my_target_message [512];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// list of messages which should print text on human players screens...
//

static struct WINGMAN_MESSAGE_TEXT_TABLE
{
	message_categories
		message_type;

	const char
		*text;

} wingman_message_text_table[] =
	{
		MESSAGE_WINGMAN_ATTACK_MY_TARGET,		"Attack My Target",
		MESSAGE_WINGMAN_HELP_ME,					"Help Me",
		MESSAGE_WINGMAN_WEAPONS_HOLD,				"Weapons Hold",
		MESSAGE_WINGMAN_WEAPONS_FREE,				"Weapons Free",
		MESSAGE_WINGMAN_HOLD_POSITION,			"Hold Position",
		MESSAGE_WINGMAN_REJOIN_FORMATION,		"Rejoin Formation",
		MESSAGE_WINGMAN_RETURN_TO_BASE,			"Return To Base",
		(message_categories)-1
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_messages (void);

static void deinitialise_messages (void);

static void initialise_message_database (void);

static message_action_type *create_message_database_list (message_categories type, int value, void ((*function) (message_type message)), int number_of_actions, const char *title);

static void add_message_action_to_database (message_action_type *parent, int index, message_categories type, int value, int keycode, const char *text);

static void create_leaf_message_action (message_categories type, int value, void ((*function) (message_type message)));

static message_action_type *get_message_action (message_type message);

static void message_list (message_type message);

static void message_function (event *ev);

static int get_message_keyboard_input (message_type message);

static void send_wingman_message (message_type message);

static void send_group_message (message_type message);

static void send_local_base_message (message_type message);

static void send_simple_message (message_type message);

static void send_wingman_message_to_human_player (entity *sender, message_categories message_type, entity *wingman);

static void enter_wingman_message (message_type message);

static void enter_pilot_message (message_type message);

static void message_input_entry (int key_code);

static void message_pilot_input_end (int key_code);

static void message_wingman_input_end (int key_code);

static void message_input_abort (int key_code);

static void message_set_input_events (void);

static void send_pilot_keyboard_message (message_type message);

static void send_wingman_keyboard_message (message_type message);

static const char *get_wingman_message_text (message_categories message_type);

static const char *get_wingman_attack_my_target_text (entity *sender, entity *wingman);

// GCsDriver  08-12-2007
static void send_channel_message (message_type message);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_messages (void)
{

	message_database = NULL;

	initialise_message_database ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_messages (void)
{

	message_action_type
		*destroy_message_action,
		*message_action;

	message_action = message_database;

	while (message_action)
	{

		destroy_message_action = message_action;

		message_action = message_action->next;

		if (destroy_message_action->actions)
		{

			free_mem (destroy_message_action->actions);
		}

		if (destroy_message_action->keycodes)
		{

			free_mem (destroy_message_action->keycodes);
		}

		if (destroy_message_action->title)
		{

			free_mem (destroy_message_action->title);
		}

		if (destroy_message_action->action_text)
		{
			int
				loop;

			for (loop = 0; loop < destroy_message_action->number_of_actions; loop ++)
			{
				if (destroy_message_action->action_text [loop])
				{
					free_mem (destroy_message_action->action_text [loop]);
				}
			}

			free_mem (destroy_message_action->action_text);
		}

		free_mem (destroy_message_action);
	}

	message_database = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_messaging_system (event *ev)
{
	message_type
		start_message;

	ASSERT (get_pilot_entity ());

	if (!in_flight_messages)
	{
		set_view_menu_display_visible_status (FALSE);

		initialise_messages ();

		memset (keyboard_message, 0, sizeof (keyboard_message));

		in_flight_messages = TRUE;

		message_destination.type = MESSAGE_NONE;
		message_destination.value = 0;

		current_message.type = MESSAGE_NONE;
		current_message.value = 0;

		push_event_overlay (set_message_events, "message events");

		start_message.type = MESSAGE_DESTINATION_LIST;
		start_message.value = 0;

		message_list (start_message);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_messaging_system (event *ev)
{
	if (in_flight_messages)
	{
		message_destination.type = MESSAGE_NONE;
		message_destination.value = 0;

		pop_event (set_message_events);

		in_flight_messages = FALSE;

		deinitialise_messages ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

message_action_type *get_message_action (message_type message)
{

	message_action_type
		*message_action;

	ASSERT (message_database);

	message_action = message_database;

	while (message_action)
	{

		if ((message_action->message.type == message.type) && (message_action->message.value == message.value))
		{

			return message_action;
		}

		message_action = message_action->next;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void message_list (message_type message)
{

	message_destination = message;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void message_function (event *ev)
{
	int
		loop;

	message_action_type
		*message_action,
		*message_action2;

	message_action = get_message_action (message_destination);

	for (loop = 0; loop < message_action->number_of_actions; loop ++)
	{
		if (message_action->keycodes [loop] == ev->key)
		{
			message_action2 = get_message_action (message_action->actions [loop]);

			if (message_action2)
			{

				current_message = message_action2->message;

				message_action2->function (current_message);
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_message_events (void)
{

	set_event (DIK_1, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_2, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_3, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_4, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_5, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_6, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_7, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_8, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_9, MODIFIER_NONE, KEY_STATE_DOWN, message_function);
	set_event (DIK_0, MODIFIER_NONE, KEY_STATE_DOWN, message_function);

	set_event (DIK_ESCAPE, MODIFIER_NONE, KEY_STATE_DOWN, stop_messaging_system);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void request_wingmen_status (message_type message)
{
	entity
		*en,
		*group,
		*member;

	en = get_pilot_entity ();
	group = get_local_entity_safe_ptr (message.value);

	if (group)
	{
		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			if (member != get_gunship_entity())
				set_incoming_message(member, en, MESSAGE_WINGMAN_STATUS_REPORT, NULL);

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}

	stop_messaging_system (NULL);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//
// Function keys are not consecutive, so need look-up table ....
//

static struct FUNCTION_KEY_TABLE
{
	int			key;
	int			index;
} function_key_table[] =
	{
		DIK_1,	1,
		DIK_2,	2,
		DIK_3,	3,
		DIK_4,	4,
		DIK_5,	5,
		DIK_6,	6,
		DIK_7,	7,
		DIK_8,	8,
		DIK_9,	9,
		DIK_0,	10,
		DIK_MINUS, 11,
		-1,		-1
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_display_message_index_number (int key)
{
	int
		loop,
		index;

	loop = 0;

	while (function_key_table [loop].key > 0)
	{
		if (function_key_table [loop].key == key)
		{
			index = function_key_table [loop].index;

			return index;
		}

		loop ++;
	}

	debug_fatal ("MSG_OUT: No Fn Key index for key %d", key);

	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_display_message_key_number (int index)
{
	int
		key,
		loop;

	loop = 0;

	while (function_key_table [loop].key > 0)
	{
		if (function_key_table [loop].index == index)
		{
			key = function_key_table [loop].key;

			return key;
		}

		loop ++;
	}

	debug_fatal ("MSG_OUT: No Fn Key for index %d", index);

	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_message_database (void)
{
	int
		loop,
		count,
		index;

	message_action_type
		*new_item,
		*sub_item;

	message_categories
		message;

	/////////////////////////////////////////////////////////////////
	//
	// Destination list
	//
	/////////////////////////////////////////////////////////////////

	new_item = create_message_database_list (MESSAGE_DESTINATION_LIST, 0, message_list, 5, "Select Destination");

	add_message_action_to_database (new_item, 0, MESSAGE_GROUP_LIST, 0, DIK_1, "Flight Group");
	add_message_action_to_database (new_item, 1, MESSAGE_WINGMAN_LIST, 0, DIK_2, "Wingmen");
	add_message_action_to_database (new_item, 2, MESSAGE_LOCAL_BASE_LIST, 0, DIK_3, "Local Base");
	add_message_action_to_database (new_item, 3, MESSAGE_PILOT_LIST, 0, DIK_4, "Other Players");

	// GCsDriver  08-12-2007
	add_message_action_to_database (new_item, 4, MESSAGE_CHANNEL_LIST, 0, DIK_5, "COMM Channels");

	/////////////////////////////////////////////////////////////////
	//
	// Wingmen / Flight Group
	//
	/////////////////////////////////////////////////////////////////
	{
		entity
			*group,
			*member;

		int
			leader_flag,
			human_group,
			human_wingman;

		if (get_gunship_entity ())
		{
			group = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER);

			if (group)
			{
				leader_flag = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_GROUP_LEADER);

				//
				// count up wingmen
				//

				count = 0;

				human_group = FALSE;

				member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

				while (member)
				{
					if (member != get_gunship_entity ())
					{
						if (get_local_entity_int_value (member, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
						{
							human_group = TRUE;
						}

						count ++;
					}

					member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
				}

				//
				// create list
				//

				if (count > 0)
				{
					new_item = create_message_database_list (MESSAGE_WINGMAN_LIST, 0, message_list, count, "Wingman List");

					loop = 0;

					member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

/*					// reverse wingman list
					while (get_local_entity_child_succ (member, LIST_TYPE_MEMBER))
					{
						member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
					}
Commented out by Retro because of change '//VJ for JvS 030411' below */
					while (member)
					{
						if (member != get_gunship_entity ())
						{
							index = get_local_entity_index (member);

							add_message_action_to_database (new_item, loop, MESSAGE_WINGMAN_SELECT, index, get_display_message_key_number (1 + loop), NULL);

							human_wingman = (get_local_entity_int_value (member, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI);

							//
							// 9 Options
							//

							sub_item = create_message_database_list (MESSAGE_WINGMAN_SELECT, index, message_list, 10, "Select Message");

							//
							// Attack My Target (F1) and Help Me (F2) - Always available
							//

							add_message_action_to_database (sub_item, 0, MESSAGE_WINGMAN_ATTACK_MY_TARGET,		index, DIK_1, "Attack My Target");
							add_message_action_to_database (sub_item, 1, MESSAGE_WINGMAN_HELP_ME, 					index, DIK_2, "Help Me");

							//
							// Hold Position (F3) - Leader only, and only if wingman is not already holding position
							//

							if ((leader_flag) && (!get_local_entity_int_value (member, INT_TYPE_POSITION_HOLD)))
							{
								add_message_action_to_database (sub_item, 2, MESSAGE_WINGMAN_HOLD_POSITION, 		index, DIK_3, "Hold Position");
							}
							else
							{
								add_message_action_to_database (sub_item, 2, MESSAGE_NONE, 								index, DIK_3, "Hold Position");
							}

							//
							// Rejoin Formation (F4) - Leader only
							//

							if (leader_flag)
							{
								add_message_action_to_database (sub_item, 3, MESSAGE_WINGMAN_REJOIN_FORMATION, 	index, DIK_4, "Rejoin Formation");
							}
							else
							{
								add_message_action_to_database (sub_item, 3, MESSAGE_NONE, 								index, DIK_4, "Rejoin Formation");
							}

							//
							// Weapons Hold (F5) - Leader only, and only if wingman is not already weapons hold
							//

							if ((leader_flag) && (!get_local_entity_int_value (member, INT_TYPE_WEAPONS_HOLD)))
							{
								add_message_action_to_database (sub_item, 4, MESSAGE_WINGMAN_WEAPONS_HOLD, 		index, DIK_5, "Weapons Hold");
							}
							else
							{
								add_message_action_to_database (sub_item, 4, MESSAGE_NONE, 								index, DIK_5, "Weapons Hold");
							}

							//
							// Weapons Free (F6) - Leader only, and only if wingman is weapons hold
							//

							if ((leader_flag) && (get_local_entity_int_value (member, INT_TYPE_WEAPONS_HOLD)))
							{
								add_message_action_to_database (sub_item, 5, MESSAGE_WINGMAN_WEAPONS_FREE, 		index, DIK_6, "Weapons Free");
							}
							else
							{
								add_message_action_to_database (sub_item, 5, MESSAGE_NONE, 								index, DIK_6, "Weapons Free");
							}

							//
							// Bob-Up (F7) - Leader Only, and only if wingman is in position
							//

							message = MESSAGE_NONE;

							if (leader_flag)
							{
								entity
									*guide;

								guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

								if (guide)
								{
									if (get_local_entity_int_value (guide, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER)
									{
										message = MESSAGE_WINGMAN_BOB_UP;
									}
								}
							}

							add_message_action_to_database (sub_item, 6, message,	index, DIK_7, "Bob-Up");

							// Attack PFZ, leader only
							if (pfz_active()
								&& get_local_entity_int_value(member, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW)
								add_message_action_to_database (sub_item, 7, MESSAGE_WINGMAN_ATTACK_PFZ,	index, DIK_8, "Attack PFZ");
							else
								add_message_action_to_database (sub_item, 7, MESSAGE_NONE,	index, DIK_8, "Attack PFZ");

							//
							// Request Target List (F8) and Keyboard Message (F9) - Human wingmen only
							//

							if (human_wingman)
							{
								add_message_action_to_database (sub_item, 8, MESSAGE_WINGMAN_REQUEST_TARGET_LIST,	index, DIK_9, "Request Target List");

								add_message_action_to_database (sub_item, 9, MESSAGE_WINGMAN_KEYBOARD, 					index, DIK_0, "Keyboard Message");
							}
							else
							{
								add_message_action_to_database (sub_item, 8, MESSAGE_NONE,	index, DIK_9, "Request Target List");

								add_message_action_to_database (sub_item, 9, MESSAGE_NONE, 	index, DIK_0, "Keyboard Message");
							}

/*
							// request status
							if (leader_flag)
								add_message_action_to_database (sub_item, 10, MESSAGE_WINGMAN_REQUEST_STATUS,	index, DIK_MINUS, "Request Status");
							else
								add_message_action_to_database (sub_item, 10, MESSAGE_NONE,	index, DIK_MINUS, "Request Status");
*/
							create_leaf_message_action (MESSAGE_WINGMAN_ATTACK_MY_TARGET, 		index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_HELP_ME, 					index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_BOB_UP, 					index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_WEAPONS_HOLD, 			index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_WEAPONS_FREE, 			index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_HOLD_POSITION, 			index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_REJOIN_FORMATION,		index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_ATTACK_PFZ, 			index, send_wingman_message);
							create_leaf_message_action (MESSAGE_WINGMAN_REQUEST_TARGET_LIST, 	index, send_simple_message);
							create_leaf_message_action (MESSAGE_WINGMAN_KEYBOARD, 				index, send_wingman_keyboard_message);
//							create_leaf_message_action (MESSAGE_WINGMAN_REQUEST_STATUS, 	index, send_wingman_message);

							loop ++;
						}

						//VJ for JvS 030411, change order of wingman to facilitate joystick programming
						member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
					}

					ASSERT (loop == count);

					//
					// Flight Group - 10 options
					//

					index = get_local_entity_index (group);

					sub_item = create_message_database_list (MESSAGE_GROUP_LIST, 0, message_list, 10, "Select Message");

					//
					// Attack My Target (F1) and Help Me (F2) - Always available
					//

					add_message_action_to_database (sub_item, 0, MESSAGE_WINGMAN_ATTACK_MY_TARGET,		index, DIK_1, "Attack My Target");
					add_message_action_to_database (sub_item, 1, MESSAGE_WINGMAN_HELP_ME, 					index, DIK_2, "Help Me");

					//
					// Hold Position (F3) - Leader only
					//

					if (leader_flag)
					{
						add_message_action_to_database (sub_item, 2, MESSAGE_WINGMAN_HOLD_POSITION, 		index, DIK_3, "Hold Position");
					}
					else
					{
						add_message_action_to_database (sub_item, 2, MESSAGE_NONE, 								index, DIK_3, "Hold Position");
					}

					//
					// Rejoin Formation (F4) - Leader only
					//

					if (leader_flag)
					{
						add_message_action_to_database (sub_item, 3, MESSAGE_WINGMAN_REJOIN_FORMATION, 	index, DIK_4, "Rejoin Formation");
					}
					else
					{
						add_message_action_to_database (sub_item, 3, MESSAGE_NONE, 								index, DIK_4, "Rejoin Formation");
					}

					//
					// Weapons Hold (F5) - Leader only
					//

					if (leader_flag)
					{
						add_message_action_to_database (sub_item, 4, MESSAGE_WINGMAN_WEAPONS_HOLD, 		index, DIK_5, "Weapons Hold");
					}
					else
					{
						add_message_action_to_database (sub_item, 4, MESSAGE_NONE, 								index, DIK_5, "Weapons Hold");
					}

					//
					// Weapons Free (F6) - Leader only
					//

					if (leader_flag)
					{
						add_message_action_to_database (sub_item, 5, MESSAGE_WINGMAN_WEAPONS_FREE, 		index, DIK_6, "Weapons Free");
					}
					else
					{
						add_message_action_to_database (sub_item, 5, MESSAGE_NONE, 								index, DIK_6, "Weapons Free");
					}

					//
					// Bob-Up (F7) - Leader Only, and only if wingman is in position
					//

					message = MESSAGE_NONE;

					if (leader_flag)
					{
						entity
							*guide;

						member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

						while (member)
						{
							guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

							if (guide)
							{
								if (get_local_entity_int_value (guide, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER)
								{
									message = MESSAGE_WINGMAN_BOB_UP;

									break;
								}
							}

							member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
						}
					}

					add_message_action_to_database (sub_item, 6, message,	index, DIK_7, "Bob-Up");

					//
					// Formation List (F8) - Leader Only
					//

					if (leader_flag)
					{
						add_message_action_to_database (sub_item, 7, MESSAGE_FORMATION_LIST, 			index, DIK_8, "Formation List");
					}
					else
					{
						add_message_action_to_database (sub_item, 7, MESSAGE_NONE, 							index, DIK_8, "Formation List");
					}


					// request status
					if (leader_flag)
						add_message_action_to_database (sub_item, 8, MESSAGE_WINGMAN_REQUEST_STATUS,	index, DIK_9, "Report Status");
					else
						add_message_action_to_database (sub_item, 8, MESSAGE_NONE,	index, DIK_9, "Report Status");

					//
					// Return To Base (F0) - Leader Only
					//

					if (leader_flag)
					{
						add_message_action_to_database (sub_item, 9, MESSAGE_WINGMAN_RETURN_TO_BASE, 		index, DIK_0, "Return To Base");
					}
					else
					{
						add_message_action_to_database (sub_item, 9, MESSAGE_NONE, 					index, DIK_0, "Return To Base");
					}

					create_leaf_message_action (MESSAGE_WINGMAN_ATTACK_MY_TARGET, 	index, send_group_message);
					create_leaf_message_action (MESSAGE_WINGMAN_HELP_ME, 				index, send_group_message);
					create_leaf_message_action (MESSAGE_WINGMAN_HOLD_POSITION, 		index, send_group_message);
					create_leaf_message_action (MESSAGE_WINGMAN_REJOIN_FORMATION,	index, send_group_message);
					create_leaf_message_action (MESSAGE_WINGMAN_WEAPONS_HOLD, 		index, send_group_message);
					create_leaf_message_action (MESSAGE_WINGMAN_WEAPONS_FREE, 		index, send_group_message);
					create_leaf_message_action (MESSAGE_WINGMAN_BOB_UP, 				index, send_group_message);
					create_leaf_message_action (MESSAGE_WINGMAN_REQUEST_STATUS,		index, request_wingmen_status);
					create_leaf_message_action (MESSAGE_WINGMAN_RETURN_TO_BASE, 	index, send_group_message);

					sub_item = create_message_database_list (MESSAGE_FORMATION_LIST, index, message_list, 9, "Formation List");

					////////////////////////////////////////////////
					//
					// Formation list Sub Menu - 9 options
					//
					////////////////////////////////////////////////

					add_message_action_to_database (sub_item, 0, MESSAGE_GROUP_ROW_LEFT,			  index, DIK_1, "Row Left");
					add_message_action_to_database (sub_item, 1, MESSAGE_GROUP_ROW_RIGHT,		      index, DIK_2, "Row Right");
					add_message_action_to_database (sub_item, 2, MESSAGE_GROUP_ECHELON_LEFT,	      index, DIK_3, "Echelon Left");
					add_message_action_to_database (sub_item, 3, MESSAGE_GROUP_ECHELON_RIGHT,	      index, DIK_4, "Echelon Right");
					add_message_action_to_database (sub_item, 4, MESSAGE_GROUP_COLUMN,			      index, DIK_5, "Column");
					add_message_action_to_database (sub_item, 5, MESSAGE_GROUP_WEDGE,				  index, DIK_6, "Wedge");   
			//VJ 060305 three new formations for maverick                  
						add_message_action_to_database (sub_item, 6, MESSAGE_GROUP_DIAMOND,				  index, DIK_7, "Diamond");
						add_message_action_to_database (sub_item, 7, MESSAGE_GROUP_STAGGERED_TRAIL_LEFT,  index, DIK_8, "Staggered Trail Left");
						add_message_action_to_database (sub_item, 8, MESSAGE_GROUP_STAGGERED_TRAIL_RIGHT,  index, DIK_9, "Staggered Trail Right");

					create_leaf_message_action (MESSAGE_GROUP_ROW_LEFT, 		      index, send_group_message);
					create_leaf_message_action (MESSAGE_GROUP_ROW_RIGHT, 		      index, send_group_message);
					create_leaf_message_action (MESSAGE_GROUP_ECHELON_LEFT, 	      index, send_group_message);
					create_leaf_message_action (MESSAGE_GROUP_ECHELON_RIGHT,          index, send_group_message);
					create_leaf_message_action (MESSAGE_GROUP_COLUMN, 			      index, send_group_message);
					create_leaf_message_action (MESSAGE_GROUP_WEDGE, 			      index, send_group_message);
                    //Mavericks Formations mod
                    create_leaf_message_action (MESSAGE_GROUP_DIAMOND, 			      index, send_group_message);
                    create_leaf_message_action (MESSAGE_GROUP_STAGGERED_TRAIL_LEFT,   index, send_group_message);
                    create_leaf_message_action (MESSAGE_GROUP_STAGGERED_TRAIL_RIGHT,  index, send_group_message);
                    
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////
	//
	// LOCAL BASE
	//
	/////////////////////////////////////////////////////////////////
	{
		int
			recon_flag;

		entity
			*guide;
		entity
			*group;

		recon_flag = FALSE;

		if (get_gunship_entity ())
		{
			guide = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_FOLLOWER);

			if (guide)
			{
				if (get_guide_criteria_valid (guide, GUIDE_CRITERIA_TRANSMIT_DATA))
				{
					recon_flag = TRUE;
				}
			}

			//
			// 4 options
			//

			group = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER);

			if (group)
			{
				index = get_local_entity_index (group);

				sub_item = create_message_database_list (MESSAGE_LOCAL_BASE_LIST, 0, message_list, 4, "Select Message");

				add_message_action_to_database (sub_item, 0, MESSAGE_LOCAL_BASE_REQUEST_AIRSTRIKE,	index, DIK_1, "Request Airstrike");
				add_message_action_to_database (sub_item, 1, MESSAGE_LOCAL_BASE_REQUEST_ARTILLERY,	index, DIK_2, "Request Artillery");
				add_message_action_to_database (sub_item, 2, MESSAGE_LOCAL_BASE_REQUEST_ASSISTANCE,	index, DIK_3, "Request Assistance");

				if (recon_flag)
				{
					add_message_action_to_database (sub_item, 3, MESSAGE_LOCAL_BASE_TRANSMIT_RECON,	index, DIK_4, "Transmit Recon");
				}
				else
				{
					add_message_action_to_database (sub_item, 3, MESSAGE_NONE,								index, DIK_4, "Transmit Recon");
				}

				create_leaf_message_action (MESSAGE_LOCAL_BASE_REQUEST_AIRSTRIKE, 	index, send_local_base_message);
				create_leaf_message_action (MESSAGE_LOCAL_BASE_REQUEST_ARTILLERY, 	index, send_local_base_message);
				create_leaf_message_action (MESSAGE_LOCAL_BASE_REQUEST_ASSISTANCE,	index, send_local_base_message);
				create_leaf_message_action (MESSAGE_LOCAL_BASE_TRANSMIT_RECON,	index, send_local_base_message);
			}
		}
	}

	/////////////////////////////////////////////////////////////////
	//
	// Pilots
	//
	/////////////////////////////////////////////////////////////////
	{
		entity
			*force_en,
			*pilot_en;

		int
			list_count,
			list_max,
			unique_id;

		ASSERT (get_session_entity ());

		//
		// count up player pilots
		//

		count = 0;

		force_en = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

		while (force_en)
		{
			pilot_en = get_local_entity_first_child (force_en, LIST_TYPE_PILOT);

			while (pilot_en)
			{
				if (pilot_en != get_pilot_entity ())
				{
					count ++;
				}

				pilot_en = get_local_entity_child_succ (pilot_en, LIST_TYPE_PILOT);
			}

			force_en = get_local_entity_child_succ (force_en, LIST_TYPE_FORCE);
		}

		//
		// create list
		//

		list_count = 0;

		list_max = (count >> 3) + 1;

		if (count > 8)
		{
			new_item = create_message_database_list (MESSAGE_PILOT_LIST, list_count, message_list, 10, "Player List");
		}
		else
		{
			new_item = create_message_database_list (MESSAGE_PILOT_LIST, list_count, message_list, count + 1, "Player List");
		}

		loop = 0;

		if (count > 0)
		{
			force_en = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

			while (force_en)
			{
				pilot_en = get_local_entity_first_child (force_en, LIST_TYPE_PILOT);

				while (pilot_en)
				{
					if (pilot_en != get_pilot_entity ())
					{
						//
						// check for overflow
						//

						if (loop >= 8)
						{
							ASSERT (loop == 8);

							//
							// broadcast to all pilots (F0)
							//

							unique_id = get_local_entity_safe_index (get_session_entity ());

							add_message_action_to_database (new_item, loop + 1, MESSAGE_PILOT_KEYBOARD, unique_id, DIK_0, NULL);

							create_leaf_message_action (MESSAGE_PILOT_KEYBOARD, unique_id, send_pilot_keyboard_message);

							//
							// create sub-list, and assign to 'F9' key
							//

							list_count ++;

							add_message_action_to_database (new_item, loop, MESSAGE_PILOT_LIST, list_count, DIK_9, "More...");

							if (count > 8)
							{
								new_item = create_message_database_list (MESSAGE_PILOT_LIST, list_count, message_list, 10, "Player List");
							}
							else
							{
								new_item = create_message_database_list (MESSAGE_PILOT_LIST, list_count, message_list, count + 1, "Player List");
							}

							loop = 0;
						}

						unique_id = get_local_entity_safe_index (pilot_en);

						add_message_action_to_database (new_item, loop, MESSAGE_PILOT_KEYBOARD, unique_id, get_display_message_key_number (1 + loop), NULL);

						create_leaf_message_action (MESSAGE_PILOT_KEYBOARD, unique_id, send_pilot_keyboard_message);

						loop ++;

						count --;
					}

					pilot_en = get_local_entity_child_succ (pilot_en, LIST_TYPE_PILOT);
				}

				force_en = get_local_entity_child_succ (force_en, LIST_TYPE_FORCE);
			}

			ASSERT (count == 0);
		}

		//
		// broadcast to all pilots
		//

		unique_id = get_local_entity_safe_index (get_session_entity ());

		add_message_action_to_database (new_item, loop, MESSAGE_PILOT_KEYBOARD, unique_id, DIK_0, NULL);

		create_leaf_message_action (MESSAGE_PILOT_KEYBOARD, unique_id, send_pilot_keyboard_message);
	}

	/////////////////////////////////////////////////////////////////
	//
	// COMM Channels by GCsDriver  08-12-2007
	//
	/////////////////////////////////////////////////////////////////
	{

		entity
			*group;

		if (get_gunship_entity ())
		{

			//
			// 4 options
			//

			group = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER);

			if (group)
			{
				index = get_local_entity_index (group);

				sub_item = create_message_database_list (MESSAGE_CHANNEL_LIST, 0, message_list, 4, "Select Message");


				if (get_sound_channel_muted (SOUND_CHANNEL_AIR_TRAFFIC_CONTROLLER))
				{
					add_message_action_to_database (sub_item, 0, MESSAGE_ATC,	index, DIK_1, "Air Traffic Controller OFF");
				}else{
					add_message_action_to_database (sub_item, 0, MESSAGE_ATC,	index, DIK_1, "Air Traffic Controller ON");
				}
				if (get_sound_channel_muted (SOUND_CHANNEL_FORWARD_AIR_CONTROLLER))
				{
					add_message_action_to_database (sub_item, 1, MESSAGE_FAC,	index, DIK_2, "Forward Air Controller OFF");
				}else{
					add_message_action_to_database (sub_item, 1, MESSAGE_FAC,	index, DIK_2, "Forward Air Controller ON");
				}
				if (get_sound_channel_muted (SOUND_CHANNEL_GROUND_CONTROLLER))
				{
					add_message_action_to_database (sub_item, 2, MESSAGE_GC,	index, DIK_3, "Ground Controller OFF");
				}else{
					add_message_action_to_database (sub_item, 2, MESSAGE_GC,	index, DIK_3, "Ground Controller ON");
				}
				if (get_sound_channel_muted (SOUND_CHANNEL_WINGMAN))
				{
					add_message_action_to_database (sub_item, 3, MESSAGE_WM,	index, DIK_4, "Wingmen OFF");
				}else{
					add_message_action_to_database (sub_item, 3, MESSAGE_WM,	index, DIK_4, "Wingmen ON");
				}
				create_leaf_message_action (MESSAGE_ATC, 	index, send_channel_message);
				create_leaf_message_action (MESSAGE_FAC, 	index, send_channel_message);
				create_leaf_message_action (MESSAGE_GC,	index, send_channel_message);
				create_leaf_message_action (MESSAGE_WM,	index, send_channel_message);
			}
		}
	}
	// GCsDriver  08-12-2007

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

message_action_type *create_message_database_list (message_categories type, int value, void ((*function) (message_type message)), int number_of_actions, const char *title)
{
	message_action_type
		*new_message_action;

	const char
		*text;

	new_message_action = (message_action_type *) malloc_fast_mem (sizeof (message_action_type));

	memset (new_message_action, 0, sizeof (message_action_type));

	if (title)
	{
		text = get_trans (title);

		ASSERT (text);

		new_message_action->title = (char *) malloc_fast_mem (strlen (text) + 4);

		strcpy (new_message_action->title, text);
	}

	new_message_action->number_of_actions = number_of_actions;

	new_message_action->message.type = type;
	new_message_action->message.value = value;

	new_message_action->function = function;

	if (number_of_actions)
	{

		new_message_action->actions = (message_type *) malloc_fast_mem (sizeof (message_type) * number_of_actions);
		memset (new_message_action->actions, 0, sizeof (message_type) * number_of_actions);

		new_message_action->keycodes = (int *) malloc_fast_mem (sizeof (int) * number_of_actions);
		memset (new_message_action->keycodes, 0, sizeof (int) * number_of_actions);

		new_message_action->action_text = (char * *) malloc_fast_mem (sizeof (char *) * number_of_actions);
		memset (new_message_action->action_text, 0, sizeof (char *) * number_of_actions);
	}

	new_message_action->next = message_database;

	message_database = new_message_action;

	return new_message_action;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_leaf_message_action (message_categories type, int value, void ((*function) (message_type message)))
{

	message_action_type
		*new_message_action;

	new_message_action = (message_action_type *) malloc_fast_mem (sizeof (message_action_type));

	memset (new_message_action, 0, sizeof (message_action_type));

	new_message_action->number_of_actions = 1;

	new_message_action->message.type = type;
	new_message_action->message.value = value;

	new_message_action->function = function;

	new_message_action->next = message_database;

	message_database = new_message_action;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_message_action_to_database (message_action_type *parent, int index, message_categories type, int value, int keycode, const char *text)
{
	const char
		*translated_text;

	ASSERT (parent);

	ASSERT (index < parent->number_of_actions);

	parent->actions [index].type = type;
	parent->actions [index].value = value;

	parent->keycodes [index] = keycode;

	if (text)
	{
		translated_text = get_trans (text);

		ASSERT (translated_text);

		parent->action_text [index] = (char *) malloc_fast_mem (strlen (translated_text) + 4);

		strcpy (parent->action_text [index], translated_text);
	}
	else
	{
		parent->action_text [index] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_message_keyboard_input (message_type message)
{

	switch (message.type)
	{

		case MESSAGE_PILOT_KEYBOARD:
		case MESSAGE_WINGMAN_KEYBOARD:
		{

			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void enter_pilot_message (message_type message)
{

	set_alpha_event_functions (message_input_entry, message_pilot_input_end, message_input_abort);

	push_event (message_set_input_events, "mesage input events");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void enter_wingman_message (message_type message)
{

	set_alpha_event_functions (message_input_entry, message_wingman_input_end, message_input_abort);

	push_event (message_set_input_events, "mesage input events");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void message_input_entry (int key_code)
{

	char
		c [3];

	int
		len;

	if (key_code == dinput_to_ascii (DIK_BACK))
	{

		if (keyboard_message)
		{

			len = strlen (keyboard_message);

			len = bound (len, 1, MAX_KEYBOARD_MESSAGE_LENGTH);

			keyboard_message [len - 1] = '\0';
		}
	}
	else
	{

		if (strlen (keyboard_message) < MAX_KEYBOARD_MESSAGE_LENGTH - 1)
		{

			sprintf (c, "%c\0", key_code);

			strcat (keyboard_message, c);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void message_pilot_input_end (int key_code)
{
	send_text_message (get_pilot_entity (), get_local_entity_safe_ptr (current_message.value), MESSAGE_TEXT_PILOT_STRING, keyboard_message);

	stop_messaging_system (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void message_wingman_input_end (int key_code)
{
	entity
		*member;

	member = get_local_entity_safe_ptr (current_message.value);

	ASSERT (member);

	send_text_message (get_pilot_entity (), member, MESSAGE_TEXT_WINGMAN_STRING, keyboard_message);

	stop_messaging_system (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void message_input_abort (int key_code)
{
	stop_messaging_system (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void message_set_input_events (void)
{
	set_alpha_events ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_text_message (entity *sender, entity *target, message_text_types type, const char *text)
{
	const char
		*kb;
	char
		*pm,
		*parsed_message;

	int
		length;

	parsed_message = NULL;

	if (message_text_type_send_string (type))
	{
		ASSERT (text);

		//
		// strip out any illegal characters
		//

		if (strlen (text) > 0)
		{
			parsed_message = (char *) malloc_fast_mem (strlen (text) + 1);

			pm = parsed_message;

			kb = text;

			length = 0;

			while ((*kb) && (length < MAX_KEYBOARD_MESSAGE_LENGTH))
			{
				//DEBUG//if (*kb < 128)
				{
					*pm = *kb;

					pm ++;
				}

				kb ++;

				length ++;
			}

			//
			// terminate new string
			//

			*pm = '\0';	//NULL;
		}
		else
		{
			//
			// valid string, but zero length - abort send
			//

			return;
		}
	}
	else
	{
		ASSERT (text == NULL);
	}

	//
	// send message
	//

	transmit_entity_comms_message (ENTITY_COMMS_PILOT_COMMUNICATION, sender, target, type, parsed_message);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		if (message_text_info [type].echo)
		{
			set_incoming_message (sender, target, type, parsed_message);
		}
	}

	if (parsed_message)
	{
		free_mem (parsed_message);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_wingman_message (message_type message)
{
	entity
		*wingman,
		*en;

	en = get_gunship_entity ();
	wingman = get_local_entity_safe_ptr (message.value);

	if (message.type == MESSAGE_WINGMAN_ATTACK_PFZ)
	{
		entity* targets[17];
		entity* target;
		unsigned int i=0;
		pfz* p;
		
		ASSERT(current_pfz != NO_PFZ);
		p = get_pfz((unsigned)current_pfz);

		// collect first 16 targets in pfz and send along

		for (target = get_local_entity_first_child(en, LIST_TYPE_GUNSHIP_TARGET);
			 target;
			 target = get_local_entity_child_succ(target, LIST_TYPE_GUNSHIP_TARGET))
		{
			if (get_gunship_target_valid_for_ground_radar(target)
				&& coordinate_is_inside_square(get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION),
											   &p->corner1, &p->corner2, &p->corner3, &p->corner4))
			{
				debug_log("transmitting engage for %i: %s", i, get_local_entity_string(target, STRING_TYPE_FULL_NAME));

				targets[i++] = target;
				if (i == (sizeof(targets) / sizeof(targets[0])) - 1)
					break;
			}
		}

		// terminate target list
		targets[i] = NULL;

		if (get_comms_model () == COMMS_MODEL_SERVER
			&& get_local_entity_int_value (wingman, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			engage_specific_targets(wingman, targets);
		}
		else
			transmit_pfz(en, wingman,
				p->corner1.x, p->corner1.z,
				p->corner2.x, p->corner2.z,
				p->corner3.x, p->corner3.z,
				p->corner4.x, p->corner4.z,
				targets);

		if (get_comms_model () == COMMS_MODEL_SERVER)
			process_radio_message (en, message.type, message.value);
	}
	else
	{
		if (get_comms_model () == COMMS_MODEL_SERVER)
			process_radio_message (en, message.type, message.value);
		else
			transmit_entity_comms_message (ENTITY_COMMS_RADIO_MESSAGE, en, message.type, message.value);

		//
		// message value should hold the index number of the target wingman
		// if that wingman is a human player, transmit text message as well
		//

		send_wingman_message_to_human_player (en, message.type, wingman);
	}

	stop_messaging_system (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_group_message (message_type message)
{
	entity
		*en,
		*group,
		*member;

	en = get_gunship_entity ();

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		process_radio_message (en, message.type, message.value);
	}
	else
	{
		transmit_entity_comms_message (ENTITY_COMMS_RADIO_MESSAGE, en, message.type, message.value);
	}

	//
	// message value should hold the index number of the target group
	// if that group contains human players, transmit text message as well
	//

	group = get_local_entity_safe_ptr (message.value);

	if (group)
	{
		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			send_wingman_message_to_human_player (en, message.type, member);

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}

	stop_messaging_system (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_local_base_message (message_type message)
{
	entity
		*en;

	en = get_gunship_entity ();

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		process_radio_message (en, message.type, message.value);
	}
	else
	{
		transmit_entity_comms_message (ENTITY_COMMS_RADIO_MESSAGE, en, message.type, message.value);
	}

	stop_messaging_system (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_simple_message (message_type message)
{
	entity
		*en;

	en = get_gunship_entity ();

	process_radio_message (en, message.type, message.value);

	stop_messaging_system (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_wingman_message_to_human_player (entity *sender, message_categories message_type, entity *wingman)
{
	const char
		*text;

	ASSERT (sender);

	if (message_type == MESSAGE_WINGMAN_ATTACK_MY_TARGET)
	{
		text = get_wingman_attack_my_target_text (sender, wingman);
	}
	else
	{
		text = get_wingman_message_text (message_type);
	}

	if (text)
	{
		ASSERT (wingman);

		send_text_message (get_pilot_entity (), wingman, MESSAGE_TEXT_WINGMAN_STRING, text);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void comms_shortcut_attack_my_target (event *ev)
{
	message_type
		message;

	entity
		*en,
		*group;

	en = get_gunship_entity ();

	if (en)
	{
		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		message.type = MESSAGE_WINGMAN_ATTACK_MY_TARGET;
		message.value = get_local_entity_safe_index (group);

		send_group_message (message);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_wingman_message_text (message_categories message_type)
{
	int
		loop;

	const char
		*text;

	loop = 0;

	while (wingman_message_text_table[loop].message_type >= 0)
	{
		if (wingman_message_text_table[loop].message_type == message_type)
		{
			text = get_trans (wingman_message_text_table[loop].text);

			ASSERT (text);

			return text;
		}

		loop ++;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_wingman_attack_my_target_text (entity *sender, entity *wingman)
{
	entity
		*target;

	vec3d
		target_vec,
		*target_pos,
		*wingman_pos;

	float
		range,
		float_heading;

	int
		int_heading;

	const char
		*target_description;

	ASSERT (sender);
	ASSERT (wingman);

	target = get_local_entity_parent (sender, LIST_TYPE_TARGET);

	if (!target)
	{
		return NULL;
	}

	if (get_local_entity_int_value (target, INT_TYPE_CPG_IDENTIFIED))
	{
		target_description = get_local_entity_string (target, STRING_TYPE_SHORT_DISPLAY_NAME);
	}
	else
	{
		target_description = get_local_entity_string (target, STRING_TYPE_EASY_DISPLAY_NAME);
	}

	if (!target_description)
	{
		return NULL;
	}

	get_local_entity_string (target, STRING_TYPE_SHORT_DISPLAY_NAME),

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	wingman_pos = get_local_entity_vec3d_ptr (wingman, VEC3D_TYPE_POSITION);

	target_vec.x = target_pos->x - wingman_pos->x;
	target_vec.y = 0.0;
	target_vec.z = target_pos->z - wingman_pos->z;

	range = get_3d_vector_magnitude (&target_vec);

	float_heading = deg (atan2 (target_vec.x, target_vec.z));

	convert_float_to_int (float_heading, &int_heading);

	if (range < 1500.0)
	{
		sprintf (attack_my_target_message, "%s - %s %s %03d %s %.0fm",
					get_wingman_message_text (MESSAGE_WINGMAN_ATTACK_MY_TARGET),
					target_description,
					get_trans ("Heading"), int_heading,
					get_trans ("Range"), range);
	}
	else
	{
		sprintf (attack_my_target_message, "%s - %s %s %03d %s %.1fkm",
					get_wingman_message_text (MESSAGE_WINGMAN_ATTACK_MY_TARGET),
					target_description,
					get_trans ("Heading"), int_heading,
					get_trans ("Range"), range / 1000.0);
	}

	return attack_my_target_message;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_pilot_keyboard_message (message_type message)
{
	ASSERT (message.type == MESSAGE_PILOT_KEYBOARD);

	enter_pilot_message (message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_wingman_keyboard_message (message_type message)
{
	ASSERT (message.type == MESSAGE_WINGMAN_KEYBOARD);

	enter_wingman_message (message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_outgoing_in_flight_message_flag (void)
{
	return in_flight_messages;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_in_flight_outgoing_messages (void)
{
	int
		index,
		loop;

	float
		y,
		indent;

	char
		s [200],
		pilot_name [STRING_TYPE_PLAYERS_NAME_MAX_LENGTH + 10],
		*message_name;

	static float
		flash_timer = 0.0;

	if (in_flight_messages)
	{
		set_ui_font_type (UI_FONT_ARIAL_16);

		indent = ui_get_string_length ("88.--");

		//
		// show message list
		//

		y = ui_get_font_height () + 2 + 2;

		if (get_message_keyboard_input (current_message))
		{
			//
			// Show user message
			//

			if (flash_timer < 0.5)
			{
				sprintf (s, "%s : %s_", get_trans ("Enter Message"), keyboard_message);
			}
			else
			{
				sprintf (s, "%s : %s", get_trans ("Enter Message"), keyboard_message);
			}

			set_ui_font_colour (ext_col_list_title);

			ui_display_text (s, 2, y);

			//
			// update cursor flashing
			//

			flash_timer += get_delta_time ();

			flash_timer = frac (flash_timer);
		}
		else
		{

			message_action_type
				*message_action;

			//
			// show predefined messages
			//

			message_action = get_message_action (message_destination);

			message_name = message_action->title;

			if (message_name)
			{
				sprintf (s, "%s:", message_name);
			}
			else
			{
				sprintf (s, "(NO TITLE):");
			}

			set_ui_font_colour (ext_col_list_title);

			ui_display_text (s, 2, y);

			y += ui_get_font_height ();

			for (loop = 0; loop < message_action->number_of_actions; loop ++)
			{
				y += ui_get_font_height ();

				index = get_display_message_index_number (message_action->keycodes [loop]);

				if (get_message_action (message_action->actions [loop]) == NULL)
				{
					set_ui_font_colour (ext_col_list_item_unavailable);
				}
				else
				{
					set_ui_font_colour (ext_col_list_item_available);
				}

				sprintf (s, "%d.", index);
				ui_display_text (s, 2, y);

				switch (message_action->actions [loop].type)
				{
					case MESSAGE_WINGMAN_SELECT:
					{

						entity
							*group,
							*pilot,
							*wingman;

						int
							wingman_index;

						wingman_index = message_action->actions [loop].value;

						wingman = get_local_entity_safe_ptr (wingman_index);

						if (wingman)
						{
							if (get_local_entity_int_value (wingman, INT_TYPE_ALIVE))
							{
								group = get_local_entity_parent (wingman, LIST_TYPE_MEMBER);

								if (group)
								{
									sprintf (s, "%s 1-%d", get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN), get_local_entity_int_value (wingman, INT_TYPE_GROUP_MEMBER_ID));

									if (get_local_entity_int_value (wingman, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
									{
										pilot = get_local_entity_first_child (wingman, LIST_TYPE_AIRCREW);

										while (pilot)
										{
											sprintf (pilot_name, " (%s)", get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));

											strcat (s, pilot_name);

											pilot = get_local_entity_child_succ (pilot, LIST_TYPE_AIRCREW);
										}
									}

									ui_display_text (s, indent, y);
								}
							}
						}

						break;
					}

					case MESSAGE_PILOT_KEYBOARD:
					{
						entity
							*pilot;

						int
							pilot_id;

						pilot_id = message_action->actions [loop].value;

						if (pilot_id == get_local_entity_safe_index (get_session_entity ()))
						{
							sprintf (s, get_trans ("All Players"));

							ui_display_text (s, indent, y);
						}
						else
						{
							pilot = get_local_entity_safe_ptr (pilot_id);

							ASSERT (pilot);

							if (get_local_entity_int_value (pilot, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
							{
								set_ui_font_colour (ext_col_blue_force);
							}
							else
							{
								set_ui_font_colour (ext_col_red_force);
							}

							sprintf (s, "%s", get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));

							ui_display_text (s, indent, y);
						}

						break;
					}

					default:
					{
						message_name = message_action->action_text [loop];

						//
						// grey-out unselectables
						//

						if (message_name)
						{
							sprintf (s, "%s", message_name);
						}
						else
						{
							sprintf (s, "(NO TITLE)");
						}

						ui_display_text (s, indent, y);

						break;
					}
				}
			}
		}

		y += ui_get_font_height () + 2;

		set_ui_font_colour (ext_col_list_item_available);

		sprintf (s, get_trans ("Esc - Exit"));

		ui_display_text (s, 2, y);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GCsDriver  08-12-2007
void send_channel_message (message_type message)
{
	int channel;

	entity
		*en;

	en = get_gunship_entity ();

	switch (message.type)
	{
		case MESSAGE_ATC:
		{
			channel = SOUND_CHANNEL_AIR_TRAFFIC_CONTROLLER;
			break;
		}
		case MESSAGE_FAC:
		{
			channel = SOUND_CHANNEL_FORWARD_AIR_CONTROLLER;
			break;
		}
		case MESSAGE_GC:
		{
  			channel = SOUND_CHANNEL_GROUND_CONTROLLER;
			break;
		}
		case MESSAGE_WM:
		{
  			channel = SOUND_CHANNEL_WINGMAN;
			break;
		}
	}

	if (get_sound_channel_muted (channel))
	{
		set_sound_channel_muted (channel, FALSE);
	}else{
		set_sound_channel_muted (channel, TRUE);
	}

	// menu off as change is not displayed
	//stop_messaging_system (NULL);

	// reinit for change in text
	//initialise_message_database ();
	initialise_messages ();
	// set current menu again to show change
	current_message = message;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

