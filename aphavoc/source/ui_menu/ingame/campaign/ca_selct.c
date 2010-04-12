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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "ai/taskgen/assign.h"
#include "ai/highlevl/suitable.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*mission_title_area,
	*select_mission_button,
	*member_title_area,
	*select_member_button,
	*mission_time_text,
	*mission_time_area,
	*member_status_text,
	*member_status_area,
	*selections_area,
	*auto_select_mission_button,
	*auto_select_member_button,
	*cockpit_button,
	*accept_current_selections_button,
	*clear_current_selections_button,
	*quit_current_mission_button;

static char
	string [128];

static int
	waiting_for_gunship = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void resize_select_ui_objects (ui_object *left_obj, ui_object *right_obj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_selection_objects (void)
{
	//
	// Current selections
	//

	set_ui_object_item_number (select_mission_button, ENTITY_INDEX_DONT_CARE);

	set_ui_object_item_number (select_member_button, ENTITY_INDEX_DONT_CARE);
	
	set_currently_selected_mission (ENTITY_INDEX_DONT_CARE);

	set_currently_selected_member (ENTITY_INDEX_DONT_CARE);

	waiting_for_gunship = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int activate_accept_selections_button (void)
{
	entity
		*mission,
		*member,
		*member_current_mission,
		*group,
		*mission_base,
		*member_base;

	member = get_local_entity_safe_ptr (get_ui_object_item_number (select_member_button));

	if (get_gunship_entity ())
	{
		//
		// player currently has a gunship 
		//
// GCsDriver
		//ASSERT ((member == get_gunship_entity ()) || (member == NULL));

		set_ui_object_drawable (cockpit_button, TRUE);

		set_ui_object_drawable (accept_current_selections_button, FALSE);

		set_ui_object_drawable (clear_current_selections_button, FALSE);

		set_ui_object_drawable (quit_current_mission_button, TRUE);

		waiting_for_gunship = FALSE;

		return FALSE;
	}

	//
	// default states
	//

	set_ui_object_drawable (cockpit_button, FALSE);

	set_ui_object_drawable (accept_current_selections_button, FALSE);

	set_ui_object_drawable (clear_current_selections_button, TRUE);

	set_ui_object_drawable (quit_current_mission_button, FALSE);

	//
	// Campaign complete? 
	//

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
	{
		return FALSE;
	}

	//
	// Clear ALL buttons if waiting for gunship...
	//

	if (waiting_for_gunship)
	{
		set_ui_object_drawable (clear_current_selections_button, FALSE);

		return FALSE;
	}

	//
	// Check member selected
	//
	
	if (!member)
	{
		return FALSE;
	}

	group = get_local_entity_parent (member, LIST_TYPE_MEMBER);

	ASSERT (member);

	//
	// Check mission selected
	//
	
	mission = get_local_entity_safe_ptr (get_ui_object_item_number (select_mission_button));

	if (!mission)
	{
		return FALSE;
	}

	//
	// Check mission and member belong to same base (only if mission unassigned)
	//

	if (get_local_entity_int_value (mission, INT_TYPE_TASK_STATE) == TASK_STATE_UNASSIGNED)
	{
		member_base = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);
	
		ASSERT (member_base);

		ASSERT (get_local_entity_type (member_base) == ENTITY_TYPE_KEYSITE);

		mission_base = get_local_entity_parent (mission, get_local_task_list_type (mission));
	
		if (member_base != mission_base)
		{
			return FALSE;
		}
	}

	//
	// If member is doing a mission - check that it is the selected mission
	//

	member_current_mission = get_local_entity_primary_task (member);

	if (member_current_mission)
	{
		if (member_current_mission != mission)
		{
			return FALSE;
		}
	}

	//
	// If the mission is already being done by a group - check that it is the selected member's group
	//

	if (get_local_entity_int_value (mission, INT_TYPE_TASK_STATE) == TASK_STATE_ASSIGNED)
	{
		if (get_local_group_primary_task (group) != mission)
		{
			return FALSE;
		}
	}

	set_ui_object_drawable (accept_current_selections_button, TRUE);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_raw_currently_selected_mission (int index)
{
	entity
		*en,
		*next,
		*mission;

	//
	// Clear any locks the player has on a mission
	//

	if (get_pilot_entity ())
	{
		en = get_local_entity_first_child (get_pilot_entity (), LIST_TYPE_PILOT_LOCK);
	
		while (en)
		{
			next = get_local_entity_child_succ (en, LIST_TYPE_PILOT_LOCK);

			if (get_local_entity_type (en) == ENTITY_TYPE_TASK)
			{
				set_client_server_entity_parent (en, LIST_TYPE_PILOT_LOCK, NULL);
			}
	
			en = next;
		}
	}
	
	//
	// Set selected mission
	//

	mission = get_local_entity_safe_ptr (index);

	if (mission)
	{
		//
		// Check for other players lock
		//

		en = get_local_entity_parent (mission, LIST_TYPE_PILOT_LOCK);
		
		if ((en) && (get_pilot_entity ()) && (en != get_pilot_entity ()))
		{
			set_ui_object_item_number (select_mission_button, ENTITY_INDEX_DONT_CARE);

			return;
		}

		//
		// Lock the mission
		//

		if (get_pilot_entity ())
		{
			set_client_server_entity_parent (mission, LIST_TYPE_PILOT_LOCK, get_pilot_entity ());
		}
	}
	else
	{
	}

	set_ui_object_item_number (select_mission_button, index);

	// reactivate channels when crashed or new mission by GCsDriver 08-12-2007
	set_sound_channel_muted (SOUND_CHANNEL_AIR_TRAFFIC_CONTROLLER, FALSE);
	set_sound_channel_muted (SOUND_CHANNEL_FORWARD_AIR_CONTROLLER, FALSE);
	set_sound_channel_muted (SOUND_CHANNEL_GROUND_CONTROLLER, FALSE);
	set_sound_channel_muted (SOUND_CHANNEL_WINGMAN, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_raw_currently_selected_member (int index)
{
	entity
		*member,
		*group,
		*next,
		*en;

	//
	// Clear any locks the player has on a group
	//

	if (get_pilot_entity ())
	{
		en = get_local_entity_first_child (get_pilot_entity (), LIST_TYPE_PILOT_LOCK);
	
		while (en)
		{
			next = get_local_entity_child_succ (en, LIST_TYPE_PILOT_LOCK);

			if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
			{
				set_client_server_entity_parent (en, LIST_TYPE_PILOT_LOCK, NULL);
			}
	
			en = next;
		}
	}
	
	//
	// Set selected group
	//

	member = get_local_entity_safe_ptr (index);

	if (member)
	{
		ASSERT (get_local_entity_suitable_for_player (member, get_pilot_entity ()));
	
		group = get_local_entity_parent (member, LIST_TYPE_MEMBER);
	
		ASSERT (group);

		//
		// Check for other players lock
		//

		en = get_local_entity_parent (group, LIST_TYPE_PILOT_LOCK);
		
		if ((en) && (get_pilot_entity ()) && (en != get_pilot_entity ()))
		{
			set_ui_object_item_number (select_member_button, ENTITY_INDEX_DONT_CARE);

			return;
		}

		//
		// Lock the group
		//

		if (get_pilot_entity ())
		{
			set_client_server_entity_parent (group, LIST_TYPE_PILOT_LOCK, get_pilot_entity ());
		}
	}

	set_ui_object_item_number (select_member_button, index);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_currently_selected_mission (int index)
{
	entity
		*en,
		*base,
		*member,
		*group,
		*mission;

	en = get_local_entity_safe_ptr (index);

	if (en)
	{
		if (get_gunship_entity ())
		{
			return;
		}

		//
		// Set base
		//

		base = get_local_entity_parent (en, LIST_TYPE_UNASSIGNED_TASK);

		ASSERT (base);

		//
		// Set Group List Filter
		//
	
		set_group_filter (index);
		
		//
		// Clear Current Member if not available for mission, or at different base
		//

		member = get_local_entity_safe_ptr (get_ui_object_item_number (select_member_button));
	
		if (member)
		{
			mission = get_local_entity_primary_task (member);

			if ((mission) && (mission != en))
			{
				set_raw_currently_selected_member (ENTITY_INDEX_DONT_CARE);
			}
			else
			{
				group = get_local_entity_parent (member, LIST_TYPE_MEMBER);

				ASSERT (group);

				if (get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP) != base)
				{
					set_raw_currently_selected_member (ENTITY_INDEX_DONT_CARE);
				}
			}
		}
	}

	//
	// Set Current Mission
	//
		
	set_raw_currently_selected_mission (index);

	activate_accept_selections_button ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_currently_selected_member (int index)
{
	entity
		*en,
		*base,
		*group,
		*mission;

	en = get_local_entity_safe_ptr (index);

	if (en)
	{
		if (get_gunship_entity ())
		{
			//
			// Can't select a member if already got gunship
			//
			
			return;
		}

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		ASSERT (group);
		
		//
		// Set base
		//

		base = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

		ASSERT (base);

		ASSERT (get_local_entity_type (base) == ENTITY_TYPE_KEYSITE);

		//
		// Set Mission List Filter
		//
	
		set_mission_filter (get_local_entity_safe_index (group));
		
		//
		// Clear Current Mission if not at Members base
		//

		mission = get_local_entity_safe_ptr (get_ui_object_item_number (select_mission_button));
	
		if (mission)
		{
			if (get_local_entity_parent (mission, LIST_TYPE_UNASSIGNED_TASK) != base)
			{
				set_raw_currently_selected_mission (ENTITY_INDEX_DONT_CARE);
			}
		}

		//
		// If Member doing Mission - Set Current Mission
		//

		mission = get_local_entity_primary_task (en);

		if (mission) 
		{
			if (get_mission_player_suitability_status (mission))
			{
				set_raw_currently_selected_mission (get_local_entity_safe_index (mission));
			}
		}
	}

	//
	// Set Current Member
	//
		
	set_raw_currently_selected_member (index);

	activate_accept_selections_button ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_currently_selected_mission (void)
{
	return get_local_entity_safe_ptr (get_ui_object_item_number (select_mission_button));
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_currently_selected_member (void)
{
	return get_local_entity_safe_ptr (get_ui_object_item_number (select_member_button));
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_select_mission_button (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*en;
		
	index = get_ui_object_item_number (obj);

	if (index != ENTITY_INDEX_DONT_CARE)
	{
		en = get_local_entity_ptr (index);

		if (get_local_entity_int_value (en, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED)
		{
			show_debriefing_page (en, FALSE, FALSE);
		}
		else
		{
			show_briefing_page (en, FALSE);
		}
	}
	else
	{
		set_common_list_available_only_state (TRUE);

		show_mission_list (obj, arg);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_select_member_button (ui_object *obj, void *arg)
{
	int
		index;

	entity
		*group;
		
	index = get_ui_object_item_number (obj);

	if (index != ENTITY_INDEX_DONT_CARE)
	{
		group = get_local_entity_parent (get_local_entity_safe_ptr (index), LIST_TYPE_MEMBER);
		
		show_group_page (group, FALSE);
	}
	else
	{
		set_common_list_available_only_state (TRUE);

		show_group_list (obj, arg);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_clear_current_selections (ui_object *obj, void *arg)
{
	int
		index;

	index = ENTITY_INDEX_DONT_CARE;
	
	waiting_for_gunship = FALSE;

	set_raw_currently_selected_mission (index);

	set_raw_currently_selected_member (index);

	set_mission_filter (index);

	set_group_filter (index);

	activate_accept_selections_button ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_quit_current_mission (ui_object *obj, void *arg)
{
	setup_campaign_quit_mission_dialog ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_quit_campaign (ui_object *obj, void *arg)
{
	setup_campaign_quit_campaign_dialog ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_auto_select_mission (ui_object *obj, void *arg)
{
	entity
		*base,
		*group,
		*mission,
		*force,
		*selected_base,
		*selected_member;

	int
		side;

	entity_sub_types
		group_type,
		mission_type;

	mission = get_local_entity_safe_ptr (get_ui_object_item_number (select_mission_button));

	ASSERT (!mission);

	selected_base = NULL;

	selected_member = get_local_entity_safe_ptr (get_ui_object_item_number (select_member_button));

	if (selected_member)
	{
		group = get_local_entity_parent (selected_member, LIST_TYPE_MEMBER);

		ASSERT (group);

		selected_base = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

		ASSERT (selected_base);

		ASSERT (get_local_entity_type (selected_base) == ENTITY_TYPE_KEYSITE);

		mission = get_local_entity_primary_task (selected_member);
	} 

	if (mission)
	{								
		set_raw_currently_selected_mission (get_local_entity_safe_index (mission));

		set_group_filter (get_local_entity_safe_index (mission));

		show_briefing_page (mission, FALSE);

		activate_accept_selections_button ();

		return;
	}
	else
	{
		side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

		force = get_local_force_entity ((entity_sides) side);

		ASSERT (force);

		//
		// First choose a base
		//

		base = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

		while (base)
		{
			if ((selected_base == NULL) || (base == selected_base))
			{
				if (get_local_entity_int_value (base, INT_TYPE_IN_USE))
				{
					//
					// Next choose a group
					//

					group = get_local_entity_first_child (base, LIST_TYPE_KEYSITE_GROUP);
	
					while (group)
					{
						mission = NULL;

						if ((!selected_member) || (group == get_local_entity_parent (selected_member, LIST_TYPE_MEMBER)))
						{
							if (get_group_player_suitability_status (group))
							{
								//
								// Finally pick a mission
								//

								if (!get_local_group_primary_task (group))
								{	
									mission = get_local_entity_first_child (base, LIST_TYPE_UNASSIGNED_TASK);
	
									while (mission)
									{
										group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
	
										mission_type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);
	
										if ((task_database [mission_type].primary_task) && (task_database [mission_type].visible_task))
										{
											if (get_group_to_task_suitability (group_type, mission_type) > 0.0)
											{
												break;
											}
										}
	
										mission = get_local_entity_child_succ (mission, LIST_TYPE_UNASSIGNED_TASK);
									}

									//
									// Set selected entities
									//	

									if (mission) 
									{								
										set_raw_currently_selected_mission (get_local_entity_safe_index (mission));

										set_group_filter (get_local_entity_safe_index (mission));

										show_briefing_page (mission, FALSE);

										activate_accept_selections_button ();

										return;
									}
								}
							}
						}

						group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
					}
				}
			}

			base = get_local_entity_child_succ (base, LIST_TYPE_KEYSITE_FORCE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_auto_select_member (ui_object *obj, void *arg)
{
	entity
		*base,
		*group,
		*guide,
		*member,
		*mission,
		*group_current_mission,
		*force,
		*selected_base,
		*selected_group,
		*selected_mission;

	int
		side;

	entity_sub_types
		group_type,
		mission_type;

	member = get_local_entity_safe_ptr (get_ui_object_item_number (select_member_button));

	ASSERT (!member);

	selected_base = NULL;

	selected_group = NULL;

	selected_mission = get_local_entity_safe_ptr (get_ui_object_item_number (select_mission_button));

	if (selected_mission)
	{
		selected_base = get_local_entity_parent (selected_mission, get_local_task_list_type (selected_mission));

		ASSERT (selected_base);

		guide = get_local_entity_first_child (selected_mission, LIST_TYPE_GUIDE);

		if (guide)
		{
			selected_group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);

			ASSERT (selected_group);
		}
	}

	side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	force = get_local_force_entity ((entity_sides) side);

	ASSERT (force);

	//
	// First choose a base
	//

	base = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (base)
	{
		if ((selected_base == NULL) || (base == selected_base))
		{
			if (get_local_entity_int_value (base, INT_TYPE_IN_USE))
			{
				//
				// Next choose a group
				//

				group = get_local_entity_first_child (base, LIST_TYPE_KEYSITE_GROUP);

				while (group)
				{
					if ((!selected_group) || (group == selected_group))
					{
						if (get_group_player_suitability_status (group))
						{
							//
							// Finally pick a mission
							//

							mission = get_local_group_primary_task (group);

							group_current_mission = mission;

							if ((selected_mission) && (mission) && (mission != selected_mission))
							{
								group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);

								continue;
							}

							if (!mission)
							{
								mission = get_local_entity_first_child (base, LIST_TYPE_UNASSIGNED_TASK);

								while (mission)
								{
									if ((!selected_mission) || (mission == selected_mission))
									{
										group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

										mission_type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);

										if ((task_database [mission_type].primary_task) && (task_database [mission_type].visible_task))
										{
											if (get_group_to_task_suitability (group_type, mission_type) > 0.0)
											{
												break;
											}
										}
									}

									mission = get_local_entity_child_succ (mission, LIST_TYPE_UNASSIGNED_TASK);
								}
							}

							if (mission)
							{	
								//
								// Pick a member from the group
								//

								member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

								while (member)
								{
									if (get_local_entity_suitable_for_player (member, get_pilot_entity ()))
									{
										break;
									}

									member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
								}

								//
								// Set selected entities
								//	

								if (member)
								{
									show_group_page (group, FALSE);

									set_raw_currently_selected_member (get_local_entity_safe_index (member));

									set_mission_filter (get_local_entity_safe_index (group));
	
									if ((group_current_mission) && (!selected_mission))
									{
										ASSERT (mission == group_current_mission);

										set_raw_currently_selected_mission (get_local_entity_safe_index (mission));

										set_group_filter (get_local_entity_safe_index (mission));
									}

									activate_accept_selections_button ();

									return;
								}
							}
						}
					}

					group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
				}
			}
		}

		base = get_local_entity_child_succ (base, LIST_TYPE_KEYSITE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_accept_current_selections (ui_object *obj, void *arg)
{
	#if !DEMO_VERSION

	entity
		*mission,
		*member,
		*group,
		*next,
		*en;

	member = get_local_entity_safe_ptr (get_ui_object_item_number (select_member_button));

	ASSERT (member);
	
	mission = get_local_entity_safe_ptr (get_ui_object_item_number (select_mission_button));

	ASSERT (mission);

	ASSERT (!get_gunship_entity ());
	
	waiting_for_gunship = TRUE;

	//
	// Clear ALL locks
	//

	en = get_local_entity_first_child (get_pilot_entity (), LIST_TYPE_PILOT_LOCK);

	while (en)
	{
		next = get_local_entity_child_succ (en, LIST_TYPE_PILOT_LOCK);
		
		set_client_server_entity_parent (en, LIST_TYPE_PILOT_LOCK, NULL);

		en = next;
	}

	//
	// Clear List Filters
	//
	
	set_mission_filter (ENTITY_INDEX_DONT_CARE);

	set_group_filter (ENTITY_INDEX_DONT_CARE);

	//
	// Assign task
	//

	group = get_local_entity_parent (member, LIST_TYPE_MEMBER);

	if ((!get_local_entity_first_child (mission, LIST_TYPE_GUIDE)) && (!get_local_group_primary_task (group)))
	{
		if (get_comms_model () == COMMS_MODEL_SERVER)
		{
			//
			// SERVER UNASSIGNED TASK
			//

			if (!assign_primary_task_to_group (group, mission))
			{
				waiting_for_gunship = FALSE;

				return;
			}

			player_assigned_new_task (member, mission);
		}
		else
		{
			//
			// CLIENT UNASSIGNED TASK
			//

			transmit_entity_comms_message (ENTITY_COMMS_TASK_ASSIGN_REQUEST, get_pilot_entity (), mission, member);
		}
	}
	else
	{
		if (get_local_group_primary_task (group))
		{
			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				//
				// SERVER ASSIGNED TASK
				//

				player_assigned_new_task (member, mission);
			}
			else
			{
				//
				// CLIENT ASSIGNED TASK
				//

				transmit_entity_comms_message (ENTITY_COMMS_TASK_ASSIGN_REQUEST, get_pilot_entity (), mission, member);
			}
		}
	}

	#endif

	activate_accept_selections_button ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_cockpit_button (ui_object *obj, void *arg)
{
	ASSERT (get_gunship_entity ());

	set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);

	toggle_in_flight_game_modes (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_current_selection_buttons (void)
{
	static float
		timer = 0.0;

	float
		expire_timer;

	int
		status,
		hours,
		minutes,
		seconds;

	entity
		*en,
		*mouse_en,
		*group;

	rgb_colour
		*col;

	mouse_en = get_ui_mouse_over_entity ();

	timer += get_delta_time ();
	
	timer = frac (timer);

	//
	// MISSION SELECTION
	//

	// recalc size & position
	process_ingame_text_object_size (mission_title_area, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_ui_object_x_end (select_mission_button, (get_ui_object_x_end (mission_title_area) + get_ui_object_virtual_x_size (mission_title_area)));
		
	set_ui_object_drawable (auto_select_mission_button, FALSE);

	col = NULL;

	en = get_local_entity_safe_ptr (get_ui_object_item_number (select_mission_button)); 

	if (en)
	{
		//
		// Currently selected mission
		//
		
		col = &ui_ingame_live_text_colour;
	}
	else
	{
		//
		// Mouse over task
		//
		
		if (!en)
		{
			if ((mouse_en) && (get_local_entity_type (mouse_en) == ENTITY_TYPE_TASK) && (get_mission_player_suitability_status (mouse_en)))
			{
				en = mouse_en;

				col = &ui_ingame_dead_text_colour;
			}
		}

		//
		// Mouse over group
		//
	
		if (!en)
		{
			if ((mouse_en) && (get_local_entity_type (mouse_en) == ENTITY_TYPE_GROUP))
			{
				en = get_local_group_primary_task (mouse_en);

				if (en)
				{
					if (!get_mission_player_suitability_status (en))
					{
						en = NULL;
					}

					col = &ui_ingame_dead_text_colour;
				}
			}
		}

		//
		// Mouse over mobile
		//
	
		if (!en)
		{
			if ((mouse_en) && (get_local_entity_type (mouse_en) == ENTITY_TYPE_HELICOPTER))
			{
				en = get_local_entity_primary_task (mouse_en);

				if (en)
				{
					if (!get_mission_player_suitability_status (en))
					{
						en = NULL;
					}

					col = &ui_ingame_dead_text_colour;
				}
			}
		}

		//
		// Mouse over briefing accept button
		//
/*			
		if (!en)
		{
			if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_BRIEFING]))
			{
				if (get_current_highlighted_object () == mission_accept_button)
				{
					en = get_local_entity_safe_ptr (get_ui_object_item_number (campaign_page [CAMPAIGN_PAGE_BRIEFING]));

					if (!get_mission_player_suitability_status (en))
					{
						en = NULL;
					}

					col = &ui_ingame_dead_text_colour;
				}
			}
		}
*/
		//
		// Mouse over member accept button
		//
/*			
		if (!en)
		{
			if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
			{
				if (get_current_highlighted_object () == gunship_accept_button)
				{
					en = get_group_page_member_list_current_entity ();

					if (en)
					{
						en = get_local_entity_primary_task (en);

						if (en)
						{
							if (!get_mission_player_suitability_status (en))
							{
								en = NULL;
							}

							col = &ui_ingame_dead_text_colour;
						}
					}
				}
			}
		}
*/
	}

	if (en)
	{
		sprintf (string, "%s #%d", get_trans (get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME)), get_local_entity_int_value (en, INT_TYPE_TASK_ID));

		set_ui_object_text (select_mission_button, string);

		//
		// Show expire / Elapsed Time
		//

		switch (get_local_entity_int_value (en, INT_TYPE_TASK_STATE))
		{
			case TASK_STATE_UNASSIGNED:
			{
				sprintf (string, "%s: ", get_trans ("Expires"));
				set_ui_object_text (mission_time_text, string);
				process_ingame_text_object_size (mission_time_text, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

				expire_timer = get_local_entity_float_value (en, FLOAT_TYPE_EXPIRE_TIMER);
				ASSERT (expire_timer < ONE_DAY);
				get_digital_countdown_values (expire_timer, NULL, &hours, &minutes, &seconds);
				sprintf (string, "%01d:%02d:%02d", hours, minutes, seconds);

				break;
			}

			default:
			{
				status = get_local_entity_int_value (en, INT_TYPE_TASK_COMPLETED);
				sprintf (string, "%s: ", get_trans (task_status_names [status]));
				set_ui_object_text (mission_time_text, string);
				process_ingame_text_object_size (mission_time_text, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

				expire_timer = get_local_entity_float_value (en, FLOAT_TYPE_ELAPSED_MISSION_TIME);
				expire_timer = min (expire_timer, (float) ONE_DAY);
				get_digital_countdown_values (expire_timer, NULL, &hours, &minutes, &seconds);
				sprintf (string, "%01d:%02d:%02d", hours, minutes, seconds);

				break;
			}
		}
		
		set_ui_object_text (mission_time_area, string);

		set_ui_object_drawable (mission_time_area, TRUE);

		set_ui_object_drawable (mission_time_text, TRUE);
	}
	else
	{
		set_ui_object_text (select_mission_button, get_trans ("MP_NONE"));

		set_ui_object_drawable (mission_time_area, FALSE);

		set_ui_object_drawable (mission_time_text, FALSE);
		
		if (!get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
		{
			set_ui_object_drawable (auto_select_mission_button, TRUE);
		}

		col = &ui_ingame_live_text_colour;
	}

	ASSERT (col);

	set_ui_object_font_colour (select_mission_button, col->r, col->g, col->b, col->a);

	//
	// GUNSHIP SELECTION
	//

	// recalc size & position
	process_ingame_text_object_size (member_title_area, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	set_ui_object_x_end (select_member_button, (get_ui_object_x_end (member_title_area) + get_ui_object_virtual_x_size (member_title_area)));
		
	set_ui_object_drawable (auto_select_member_button, FALSE);

	col = NULL;

	en = get_local_entity_safe_ptr (get_ui_object_item_number (select_member_button));

	if (en)
	{
		col = &ui_ingame_live_text_colour;
	}
	else if ((mouse_en) && (get_local_entity_type (mouse_en) == ENTITY_TYPE_GROUP) && (get_group_player_suitability_status (mouse_en)))
	{
		en = get_local_entity_first_child (mouse_en, LIST_TYPE_MEMBER);

		col = &ui_ingame_dead_text_colour;
	}
	else if ((mouse_en) && (get_local_entity_type (mouse_en) == ENTITY_TYPE_HELICOPTER))
	{
		if (get_local_entity_suitable_for_player (mouse_en, get_pilot_entity ()))
		{
			group = get_local_entity_parent (mouse_en, LIST_TYPE_MEMBER);

			if (group) // TG added
			{
			
				if (get_group_player_suitability_status (group))
				{
					en = mouse_en;
		
					col = &ui_ingame_dead_text_colour;
				}
			}
		}
	}
/*	else if (get_ui_object_drawable (campaign_page [CAMPAIGN_PAGE_GROUP]))
	{
		if (get_current_highlighted_object () == gunship_accept_button)
		{
			en = get_group_page_member_list_current_entity ();

			col = &ui_ingame_dead_text_colour;
		}
	}
*/
	if (en)
	{
		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		ASSERT (group);

		sprintf (string, "%s 1-%d %s",
					get_local_entity_string (group, STRING_TYPE_DIVISION_NAME),
					get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_ID),
					get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME));

		set_ui_object_text (select_member_button, string);

		//
		// Gunship status
		//
		
		sprintf (string, "%s", get_trans (group_member_state_names [get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_STATE)]));

		set_ui_object_text (member_status_area, string);

		set_ui_object_drawable (member_status_text, TRUE);

		set_ui_object_drawable (member_status_area, TRUE);
	}
	else
	{
		set_ui_object_text (select_member_button, get_trans ("MP_NONE"));

		set_ui_object_text (member_status_area, "");

		set_ui_object_drawable (member_status_text, FALSE);

		set_ui_object_drawable (member_status_area, FALSE);

		if (!get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
		{
			entity
				*current_mission;

			set_ui_object_drawable (auto_select_member_button, TRUE);

			//
			// HACK because of problem where assigned entities doing transfer "belong" to the *objective* keysite
			//
			
			current_mission = get_currently_selected_mission ();
			
			if (current_mission)
			{
				if (get_local_entity_int_value (current_mission, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER)
				{
					if (get_local_entity_int_value (current_mission, INT_TYPE_TASK_STATE) == TASK_STATE_ASSIGNED)
					{
						set_ui_object_drawable (auto_select_member_button, FALSE);
					}
				}
			}
		}

		col = &ui_ingame_live_text_colour;
	}

	ASSERT (col);

	set_ui_object_font_colour (select_member_button, col->r, col->g, col->b, col->a);

	resize_select_ui_objects (member_status_text, member_status_area);
		
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_selection_area (ui_object *obj, void *arg)
{
	update_current_selection_buttons ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_campaign_screen_selection_objects (void)
{
	char
		string [256];
		
	float
		x1,
		y1,
		x2,
		y2;

	/////////////////////////////////////////////////////////////////
	// Currently selected mission / member + Accept button
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Current selections

	x1 = CAMPAIGN_INSET_PAGE_X1;
	y1 = 0.84;
	x2 = 1.0;
	y2 = 0.92;

	selections_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_DRAW_FUNCTION (update_selection_area),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\mission.psd")),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Currently selected mission 

	x1 = 0.2f;
	x2 = 0.2f;

	y1 = 0.5;
	y2 = 1.0;

	sprintf (string, "%s: ", get_trans ("Mission"));

	mission_title_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (string),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	process_ingame_text_object_size (mission_title_area, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

//	x1 = 0.22f;
	x2 = 0.5;

	y1 = 0.5;
	y2 = 1.0;

	x1 = get_ui_object_x_end (mission_title_area) + get_ui_object_virtual_x_size (mission_title_area);

	select_mission_button = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (""),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_ITEM_NUMBER (ENTITY_INDEX_DONT_CARE),
			UI_ATTR_FUNCTION (notify_select_mission_button),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	set_ui_mouse_over_entity_function (select_mission_button);

	/////////////////////////////////////////////////////////////////
	// Currently selected mission status

	x1 = 0.68;
	x2 = 0.68;

	y1 = 0.5;
	y2 = 1.0;

	sprintf (string, "%s: ", get_trans ("Expires"));
	
	mission_time_text = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (string),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	process_ingame_text_object_size (mission_time_text, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	x1 = 0.68;
	x2 = 0.782;

	y1 = 0.5;
	y2 = 1.0;

	mission_time_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (""),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Auto Select Mission

	x1 = 0.75;
	x2 = 0.782;

	y1 = 0.5;
	y2 = 1.0;

	auto_select_mission_button = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Auto-Select")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_FUNCTION (notify_auto_select_mission),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	process_ingame_text_object_size (auto_select_mission_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	/////////////////////////////////////////////////////////////////
	// Currently selected member

	x1 = 0.09;
	x2 = 0.3f;

	y1 = 0.0;
	y2 = 0.5;

	sprintf (string, "%s: ", get_trans ("Gunship"));

	member_title_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (string),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	process_ingame_text_object_size (member_title_area, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	x1 = get_ui_object_x_end (member_title_area) + get_ui_object_virtual_x_size (member_title_area);
//	x1 = 0.31;
	x2 = 0.5;

	y1 = 0.0;
	y2 = 0.5;

	select_member_button = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (""),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_ITEM_NUMBER (ENTITY_INDEX_DONT_CARE),
			UI_ATTR_FUNCTION (notify_select_member_button),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	set_ui_mouse_over_entity_function (select_member_button);

	/////////////////////////////////////////////////////////////////
	// Currently selected member group status

	x1 = 0.5;
	x2 = 0.66;

	y1 = 0.0;
	y2 = 0.5;

	sprintf (string, "%s: ", get_trans ("Status"));

	member_status_text = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (string),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	process_ingame_text_object_size (member_status_text, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	x1 = get_ui_object_x_end (member_status_text) + get_ui_object_x_size (member_status_text);

//	x1 = 0.85;
	x2 = 0.895;

	y1 = 0.0;
	y2 = 0.5;

	member_status_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (""),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Auto Select Member

	x1 = 0.85;
	x2 = 0.895;

	y1 = 0.0;
	y2 = 0.5;

	auto_select_member_button = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (selections_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Auto-Select")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FUNCTION (notify_auto_select_member),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_RIGHT_CENTRE),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	process_ingame_text_object_size (auto_select_member_button, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

	/////////////////////////////////////////////////////////////////
	// Accept current selections 
	/////////////////////////////////////////////////////////////////

	x1 = 0.831;
	y1 = 0.90;
	x2 = 1.0;
	y2 = 0.987;

	accept_current_selections_button = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Confirm")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FUNCTION (notify_accept_current_selections),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\flybtn.psd")),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Cockpit Button

	x1 = 0.831;
	y1 = 0.90;
	x2 = 1.0;
	y2 = 0.987;

	cockpit_button = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Cockpit")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FUNCTION (notify_cockpit_button),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\flybtn.psd")),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Clear current selections 

	x1 = 0.468;
	y1 = 0.949;
	x2 = 0.741;
	y2 = 0.986;

	clear_current_selections_button = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("CLEAR")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FUNCTION (notify_clear_current_selections),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\cbtn.psd")),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Quit current mission button

	x1 = 0.468;
	y1 = 0.949;
	x2 = 0.741;
	y2 = 0.986;

	quit_current_mission_button = create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("QUIT MISSION")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_FUNCTION (notify_quit_current_mission),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\cbtn.psd")),
			UI_ATTR_END
		);

	/////////////////////////////////////////////////////////////////
	// Exit Campaign

	x1 = 0.0;
	y1 = 0.90;
	x2 = 0.168;
	y2 = 0.987;

	create_ui_object
		(
			UI_TYPE_BUTTON,
			UI_ATTR_PARENT (campaign_screen),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (get_trans ("Exit")),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_16),
			UI_ATTR_FONT_COLOUR (ui_ingame_live_text_colour.r, ui_ingame_live_text_colour.g, ui_ingame_live_text_colour.b, ui_ingame_live_text_colour.a),
			UI_ATTR_HIGHLIGHTED_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_SELECTED_FONT_COLOUR (ui_ingame_selected_text_colour.r, ui_ingame_selected_text_colour.g, ui_ingame_selected_text_colour.b, ui_ingame_selected_text_colour.a),
			UI_ATTR_HIGHLIGHTABLE (TRUE),
			UI_ATTR_TEXTURE_GRAPHIC (create_texture_graphic ("graphics\\ui\\cohokum\\map\\exitbtn.psd")),
			UI_ATTR_FUNCTION (notify_quit_campaign),
			UI_ATTR_END
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_group_remove_member (campaign_screen_messages message, entity *sender)
{
	entity
		*en;

	//
	// Check selected gunship to see if it is dead, or has no group
	//

	en = get_currently_selected_member ();

	if (en)
	{
		if ((!get_local_entity_int_value (en, INT_TYPE_ALIVE)) || (!get_local_entity_parent (en, LIST_TYPE_MEMBER)))
		{
			set_currently_selected_member (ENTITY_INDEX_DONT_CARE);
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_mission_destroyed (campaign_screen_messages message, entity *sender)
{
	if (sender == get_currently_selected_mission ())
	{
		set_currently_selected_mission (ENTITY_INDEX_DONT_CARE);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_campaign_selection_message_responses (void)
{
	campaign_screen_message_targets
		target;

	target = CAMPAIGN_SCREEN_TARGET_SELECTIONS;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_GROUP_REMOVE_MEMBER]	=	response_to_group_remove_member;

	campaign_screen_message_responses [target][CAMPAIGN_SCREEN_MISSION_DESTROYED]		=	response_to_mission_destroyed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resize_select_ui_objects (ui_object *left_obj, ui_object *right_obj)
{

	if (right_obj) // TG added
	{

		process_ingame_text_object_size (right_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);

		if (left_obj) // TG added
		{

			set_ui_object_x_end (left_obj, get_ui_object_x_end (right_obj) - 0.1f);
		}
	}

	if (left_obj) // TG added
	{
	
		set_ui_object_virtual_x_size (left_obj, 0.1f);
	
		process_ingame_text_object_size (left_obj, NULL, NULL, 0, RESIZE_OPTION_FIXED_BUTTON);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

