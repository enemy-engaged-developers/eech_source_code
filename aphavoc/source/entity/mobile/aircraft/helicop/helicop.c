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

entity
	*gunship_entity = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Werewolf: Changed to accomodate new rotor sound components: turbine sound, rotorslap sound
static void create_specified_helicopter_rotor_sound_effects (entity *en, sound_locality_types locality, sound_sample_indices looping_effect, sound_sample_indices wind_up_effect, sound_sample_indices wind_down_effect, sound_sample_indices turbine_effect, sound_sample_indices rotorslap_effect);
static float kill_sound_effect(entity* en, entity_sub_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_gunship_entity (entity *en)
{
	stop_messaging_system (NULL);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		assign_entity_to_user (en);
	}
	else
	{
		if (en == NULL)
		{
			//
			// client doesn't need confirmation from server if setting g/s to NULL
			//

			assign_entity_to_user (en);
		}
		else
		{
			client_gunship_request_data
				pilot_data;

			//
			// pack required gunship data
			//

			pilot_data.gunship_type = global_options.gunship_type;

			pilot_data.gunship_index = get_local_entity_safe_index (en);

			//
			// Send request
			//

			send_packet (get_server_id (), PACKET_TYPE_CLIENT_GUNSHIP_REQUEST, (void *) &pilot_data, sizeof (client_gunship_request_data), SEND_TYPE_PERSONAL);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assign_entity_to_user (entity *en)
{
   entity
		*group,
		*member,
		*previous,
		*primary_task,
		*old_group;

	float
		fuel;

	int
		input_events_flag,
		ingame_events_flag;

	comms_data_flow_types
		store_data_flow;

	ASSERT (get_pilot_entity ());

	old_group = NULL;

	//
	// Maintain Input Events
	//
	
	if (get_event_stack_head_function () == set_input_events)
	{
		pop_event (set_input_events);

		input_events_flag = TRUE;
	}
	else
	{
		input_events_flag = FALSE;
	}

	//
	// Maintain Planner Events
	//
	
	if (get_event_stack_head_function () == ingame_screen_set_events)
	{
		ASSERT (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_PLANNER);

		pop_event (ingame_screen_set_events);

		ingame_events_flag = TRUE;
	}
	else
	{
		ingame_events_flag = FALSE;
	}

	previous = gunship_entity;

	if (previous)
	{

		if (get_current_flight_dynamics ())
		{

			fuel = get_current_flight_dynamics_fuel_weight ();

			set_client_server_entity_float_value (previous, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, fuel);
		}
	}

	if (en)
	{
		if (!get_local_entity_suitable_for_player (en, get_pilot_entity ()))
		{
			en = NULL;

			notify_clear_current_selections (NULL, NULL);
		}
	}

	if (en)
	{
		// set invulnerable timer and display message

		set_local_entity_float_value (en, FLOAT_TYPE_INVULNERABLE_TIMER, command_line_user_invulnerable_time);

		//set_status_message ("Invulnerable", STATUS_MESSAGE_TYPE_ALERT);

		if (get_time_acceleration () != TIME_ACCELERATION_PAUSE)
		{
			set_min_time_acceleration (NULL);
		}

		set_global_gunship_type (get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE));
	}
	else
	{

		set_global_gunship_type (NUM_GUNSHIP_TYPES);

		if (previous)
		{
			set_external_view_entity (previous);

			notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_END_OF_MISSION);
		}
		else
		{
			notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_CINEMATIC);
		}
	}

	//
	// big problems as this function can be called by the client in RX mode,
	// but it needs to do a lot of setting things c/s (i.e. it really needs to be in TX mode)
	//

	store_data_flow = get_comms_data_flow ();

	set_comms_data_flow (COMMS_DATA_FLOW_TX);

	//
	// release old gunship entity
	//

	primary_task = NULL;

	if (gunship_entity)
	{
		//
		// Award Points for mission
		//

		primary_task = get_local_entity_primary_task (gunship_entity);

		if (primary_task)
		{
			if (get_local_entity_int_value (primary_task, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED)
			{
				//
				// Only award points for COMPLETE missions (also means player can't rejoin that mission and get points again)
				//

				notify_gunship_entity_mission_terminated (gunship_entity, primary_task);
			}
		}

		//
		// Deinitialise
		//

		deinitialise_cockpits ();

		deinitialise_avionics ();

		//
		// Deinitialise flight dynamics
		//

		if (get_current_flight_dynamics ())
		{
			//
			// damage helicopter according to flight model
			//

			damage_entity_to_flight_model (gunship_entity);

			deinitialise_flight_dynamics ();
		}

		set_client_server_entity_int_value (gunship_entity, INT_TYPE_PLAYER, ENTITY_PLAYER_AI);

		// check if this is necessary...
		switch (get_local_entity_int_value (gunship_entity, INT_TYPE_OPERATIONAL_STATE))
		{
			case OPERATIONAL_STATE_LANDED:
			{
				if (primary_task)
				{
					set_client_server_entity_int_value (gunship_entity, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);
				}

				break;
			}
		}

		old_group = get_local_entity_parent (gunship_entity, LIST_TYPE_MEMBER);
	}

	//
	// set new gunship entity
	//

	gunship_entity = en;

	//
	// assign pilot
	//

	set_client_server_entity_parent (get_pilot_entity (), LIST_TYPE_AIRCREW, en);

	set_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE, CREW_ROLE_PILOT);

	//
	// Tidy up old group (must be done after gunship_entity and aircrew link set)
	//

	if (old_group)
	{
		notify_campaign_screen (CAMPAIGN_SCREEN_GROUP_REMOVE_MEMBER, old_group);

		//
		// set all helicopters in old group to "weapons free", and clear "hold position" flag
		//

		member = get_local_entity_first_child (old_group, LIST_TYPE_MEMBER);

		while (member)
		{
			set_client_server_entity_int_value (member, INT_TYPE_WEAPONS_HOLD, FALSE);

			set_client_server_entity_int_value (member, INT_TYPE_POSITION_HOLD, FALSE);

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}

	//
	//
	//

	if (en)
	{
		set_client_server_entity_int_value (en, INT_TYPE_PLAYER, ENTITY_PLAYER_REMOTE);

		debug_log ("Setting gunship_entity (type = %s, index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));

		set_valid_helicopter (TRUE);

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		//
		// Initialise avionics, cockpits and flight model
		//

		initialise_flight_dynamics (en);

		initialise_avionics ();

		initialise_cockpits ();

		fuel = get_local_entity_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

		set_current_flight_dynamics_fuel_weight (fuel);

		restore_helicopter_entity (en, NULL, get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE));

		//
		// set view mode
		//

		set_external_view_entity (en);

		notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_CHASE);

		reinitialise_virtual_cockpit_view ();

		set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);

		//
		// set all helicopters in new group to "weapons hold"
		//

		if (!get_global_simple_avionics ())
		{
			if (group)
			{
				entity
					*member;

				member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

				while (member)
				{
					set_client_server_entity_int_value (member, INT_TYPE_WEAPONS_HOLD, TRUE);

					member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
				}
			}
		}

		//
		// setup gunship
		//

		set_client_server_entity_int_value (en, INT_TYPE_UNIQUE_ID, direct_play_get_player_id ());

		//
		// Notify campaign screen
		//

		activate_accept_selections_button ();
	}
	else
	{
		set_valid_helicopter (FALSE);

		debug_log ("Setting gunship_entity to NULL");

		if (previous)
		{
			player_quit_current_task ();
		}
	}

	//
	//
	//

	if (ingame_events_flag)
	{
		push_event (ingame_screen_set_events, "ingame screen events");
	}

	if (input_events_flag)
	{
		push_event (set_input_events, "input events");
	}

	set_comms_data_flow (store_data_flow);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_raw_gunship_entity (entity *en)
{
	//
	// set gunship entity
	//

	gunship_entity = en;

	if (en)
	{
		debug_log ("Setting raw gunship_entity (type = %s, index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
	}
	else
	{
		debug_log ("Setting raw gunship_entity to NULL");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_gunship_entity_to_external_view_entity (event *ev)
{
	#if !DEMO_VERSION

	entity
		*en,
		*pilot,
		*task;

	pilot = get_pilot_entity ();
	
	if (!get_local_entity_int_value (get_session_entity (), INT_TYPE_SESSION_COMPLETE))
	{
		en = get_external_view_entity ();

		if (en)
		{
			if (get_local_entity_suitable_for_player (en, get_pilot_entity ()))
			{
				task = get_local_entity_primary_task (en);
				
				if (task)
				{
					// Should be TRUE through "get_local_entity_suitable_for_player"
					ASSERT (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) == TASK_INCOMPLETE);

					//
					// Update Campaign Screen to reflect new gunship/mission
					//

					set_gunship_entity (NULL);
					
					set_currently_selected_member (get_local_entity_safe_index (en));

					player_assigned_new_task (en, task);
				}
				// Jabberwock 040201 - No tasks needed for Free flight
				else
				{
					if (get_game_type () == GAME_TYPE_FREE_FLIGHT)
					{
						set_gunship_entity (en);
					}
				}
				
				if (get_local_entity_int_value (pilot, INT_TYPE_SIDE) != get_local_entity_int_value (en, INT_TYPE_SIDE))
				{
					set_local_entity_int_value (en, INT_TYPE_SIDE, get_local_entity_int_value (pilot, INT_TYPE_SIDE));
				}
				
				// Jabberwock 040201 ends
			}
		}
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_helicopter_entity (entity *en, vec3d *pos, operational_state_types operational_state)
{
	ASSERT (en);

	restore_helicopter_main_rotors (en);

	restore_helicopter_tail_rotors (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_gunship_entity_mission_completed (entity *en, entity *task)
{
	char
		s [128];

	ASSERT (en);

	ASSERT (en == get_gunship_entity ());

	ASSERT (task);

	ASSERT (get_local_entity_int_value (task, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED);

	ASSERT (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) != TASK_INCOMPLETE);

	//
	// CAMPAIGN :- Set-up debriefing page
	//

	autoselect_debriefing_page (task, FALSE);

	//
	// Show Mission Complete Message
	//

	sprintf (s, "Mission %s", task_status_names [get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED)]);

	set_status_message (get_trans (s), STATUS_MESSAGE_TYPE_ALERT);

	//
	// Play Mission Complete CD track
	//

	if (!command_line_no_mission_complete_music)
	{
		play_cd_music (CD_MUSIC_TYPE_MISSION_COMPLETE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_gunship_entity_mission_terminated (entity *en, entity *task)
{
	int
		side,
		rank,
		medal,
		points;

	player_log_type
		*log;

	ASSERT (en);

	ASSERT (en == get_gunship_entity ());

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	ASSERT (task);

	ASSERT (get_local_entity_int_value (task, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED);

	log = get_current_player_log ();

	medal = MEDAL_TYPE_NONE;

	rank = PILOT_RANK_NONE;

	points = get_local_entity_int_value (task, INT_TYPE_TASK_SCORE);

	// increment player experience points

	inc_player_log_experience (side, log, points);

	// increment number of missions flown

	inc_player_log_missions_flown (side, log);

	switch (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED))
	{

		case TASK_COMPLETED_SUCCESS:
		{

			//
			// SUCCESSFUL MISSION
			//

			debug_filtered_log ("HELICOP: Awarded %d Points to player for %s %d", points, get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_index (task));

			if (points > 0)
			{

				//
				// AWARD VALOUR MEDALS
				//

				medal |= 1 << award_valour_medal (side, points);

				//
				// AWARD PROMOTION
				//

				rank = award_player_rank (side);
			}

			//
			// AWARD AIR MEDAL (no. of successful missions in a row)
			//

			medal |= 1 << award_air_medal_medal (side, TRUE);

			//
			// AWARD FLIGHT TIME MEDALS
			//

			medal |= 1 << award_aviator_wings (side);

			//
			// AWARD PURPLE HEART
			//

			medal |= 1 << award_purple_heart_medal (side);

			//
			// Update Success Rate
			//

			update_player_log_mission_success_rate (side, log, 1.0);

			break;
		}

		case TASK_COMPLETED_PARTIAL:
		{

			//
			// AWARD FLIGHT TIME MEDALS
			//

			medal |= 1 << award_aviator_wings (side);

			//
			// AWARD PURPLE HEART
			//

			medal |= 1 << award_purple_heart_medal (side);

			//
			// Update Success Rate
			//

			update_player_log_mission_success_rate (side, log, 0.5);

			break;
		}

		case TASK_COMPLETED_FAILURE:
		{

			//
			// AWARD FLIGHT TIME MEDALS
			//

			medal |= 1 << award_aviator_wings (side);

			// reset air_medal counter
			award_air_medal_medal (side, FALSE);

			//
			// Update Success Rate
			//

			update_player_log_mission_success_rate (side, log, 0.0);

			break;
		}

		default:
		{

			debug_fatal ("HELICOP: unknown task completed %d", get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED));
		}
	}

	//
	// store medals awarding in task
	//

	set_local_entity_int_value (task, INT_TYPE_AWARDED_MEDALS, medal);

	set_local_entity_int_value (task, INT_TYPE_AWARDED_PROMOTION, rank);

	//
	// CAMPAIGN :- Set-up debriefing page
	//

	autoselect_debriefing_page (task, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_helicopter_rotor_sound_effects (entity *en)
{

	entity_sub_types
		sub_type;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	switch (sub_type)
	{
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_SLAP
			);

			break;
		}
		//Werewolf: Additional sounds
		case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_COMANCHE_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_COMANCHE_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_COMANCHE_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_COMANCHE_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_COMANCHE_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_COMANCHE_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_COMANCHE_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_COMANCHE_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_COMANCHE_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_COMANCHE_ROTOR_SLAP
			);

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_HAVOC_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HAVOC_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HAVOC_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_HAVOC_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_HAVOC_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_HAVOC_ROTOR_SLAP
			);

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_SLAP
			);

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_BLACKHAWK_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_BLACKHAWK_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_BLACKHAWK_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_BLACKHAWK_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_BLACKHAWK_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_BLACKHAWK_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_BLACKHAWK_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_BLACKHAWK_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_BLACKHAWK_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_BLACKHAWK_ROTOR_SLAP
			);

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_HIND_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_HIND_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_HIND_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_HIND_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_HIND_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HIND_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HIND_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_HIND_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_HIND_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_HIND_ROTOR_SLAP
			);

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_APACHE_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_APACHE_ROTOR_SLAP
			);

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_KA50_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_KA50_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_HOKUM_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_HOKUM_ROTOR_SLAP
			);
			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
        case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_AH1T_SEACOBRA_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_AH1T_SEACOBRA_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_AH1T_SEACOBRA_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_AH1T_SEACOBRA_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_AH1T_SEACOBRA_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_AH1T_SEACOBRA_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_AH1T_SEACOBRA_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_AH1T_SEACOBRA_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_AH1T_SEACOBRA_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_AH1T_SEACOBRA_ROTOR_SLAP
			);
		   break;
		}
	    case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_KIOWA_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_KIOWA_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_KIOWA_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_KIOWA_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_KIOWA_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_KIOWA_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_KIOWA_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_KIOWA_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_KIOWA_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_KIOWA_ROTOR_SLAP
          );
	     break;
		}
	    case  ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_KA29_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_KA29_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_KA29_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_KA29_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_KA29_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_KA29_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_KA29_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_KA29_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_KA29_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_KA29_ROTOR_SLAP
			);
			break;
		}
        case  ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
        case  ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH46E_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH46E_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH46E_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH46E_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH46E_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_CH46E_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_CH46E_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_CH46E_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_CH46E_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_CH46E_ROTOR_SLAP
			);
			break;
		}
       case  ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_EXTERIOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH3_ROTOR,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH3_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH3_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH3_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_EXTERIOR_CH3_ROTOR_SLAP
			);

			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_INTERIOR,
				SOUND_SAMPLE_INDEX_INTERIOR_CH3_ROTOR,
				SOUND_SAMPLE_INDEX_INTERIOR_CH3_ROTOR_WIND_UP,
				SOUND_SAMPLE_INDEX_INTERIOR_CH3_ROTOR_WIND_DOWN,
				SOUND_SAMPLE_INDEX_INTERIOR_CH3_ROTOR_TURBINE,
				SOUND_SAMPLE_INDEX_INTERIOR_CH3_ROTOR_SLAP
			);
			break;
		}
		//Werewolf: End additional sounds


		default:
		{
			create_specified_helicopter_rotor_sound_effects
			(
				en,
				SOUND_LOCALITY_ALL,
				aircraft_database [sub_type].continuous_sound_effect_index,
				SOUND_SAMPLE_INDEX_NONE,
				SOUND_SAMPLE_INDEX_NONE,
				SOUND_SAMPLE_INDEX_NONE,
				SOUND_SAMPLE_INDEX_NONE
			);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_specified_helicopter_rotor_sound_effects (entity *en, sound_locality_types locality, sound_sample_indices looping_effect, sound_sample_indices wind_up_effect, sound_sample_indices wind_down_effect, sound_sample_indices turbine_effect, sound_sample_indices rotorslap_effect)
{
	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// looping
	//

	ASSERT (looping_effect != SOUND_SAMPLE_INDEX_NONE);

	create_client_server_sound_effect_entity
	(
		en,
		ENTITY_SIDE_NEUTRAL,
		ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING,
		SOUND_CHANNEL_SOUND_EFFECT,
		locality,
		NULL,												// position
		0.0,												// amplification
		1.0,												// Werewolf pitch
		FALSE,											// valid sound effect
		TRUE,												// looping
		1,													// sample count
		&looping_effect								// sample index list
	);

	// Werewolf:
	// Turbine noise
	//

	if (turbine_effect != SOUND_SAMPLE_INDEX_NONE)
	{
		create_client_server_sound_effect_entity
		(
			en,
			ENTITY_SIDE_NEUTRAL,
			ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE1,
			SOUND_CHANNEL_SOUND_EFFECT,
			locality,
			NULL,												// position
			0.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			TRUE,												// looping
			1,													// sample count
			&turbine_effect								// sample index list
		);

		create_client_server_sound_effect_entity
		(
			en,
			ENTITY_SIDE_NEUTRAL,
			ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2,
			SOUND_CHANNEL_SOUND_EFFECT,
			locality,
			NULL,												// position
			0.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			TRUE,												// looping
			1,													// sample count
			&turbine_effect								// sample index list
		);

		create_client_server_sound_effect_entity
		(
			en,
			ENTITY_SIDE_NEUTRAL,
			ENTITY_SUB_TYPE_EFFECT_SOUND_APU_TURBINE,
			SOUND_CHANNEL_SOUND_EFFECT,
			locality,
			NULL,												// position
			0.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			TRUE,												// looping
			1,													// sample count
			&turbine_effect								// sample index list
		);
	}

	// Werewolf:
	// Rotorslap
	//

	if (rotorslap_effect != SOUND_SAMPLE_INDEX_NONE)
	create_client_server_sound_effect_entity
	(
		en,
		ENTITY_SIDE_NEUTRAL,
		ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP,
		SOUND_CHANNEL_SOUND_EFFECT,
		locality,
		NULL,												// position
		0.0,												// amplification  
		1.0,												// Werewolf pitch
		FALSE,											// valid sound effect 
		TRUE,												// looping
		1,													// sample count
		&rotorslap_effect								// sample index list
	);

	//
	// wind up
	//

	if (wind_up_effect != SOUND_SAMPLE_INDEX_NONE)
	{
		create_client_server_sound_effect_entity
		(
			en,
			ENTITY_SIDE_NEUTRAL,
			ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP1,
			SOUND_CHANNEL_SOUND_EFFECT,
			locality,
			NULL,												// position
			0.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			FALSE,											// looping
			1,													// sample count
			&wind_up_effect								// sample index list
		);
		
		create_client_server_sound_effect_entity
		(
			en,
			ENTITY_SIDE_NEUTRAL,
			ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP2,
			SOUND_CHANNEL_SOUND_EFFECT,
			locality,
			NULL,												// position
			0.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			FALSE,											// looping
			1,													// sample count
			&wind_up_effect								// sample index list
		);
	}

	//
	// wind down
	//

	if (wind_down_effect != SOUND_SAMPLE_INDEX_NONE)
	{
		create_client_server_sound_effect_entity
		(
			en,
			ENTITY_SIDE_NEUTRAL,
			ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN1,
			SOUND_CHANNEL_SOUND_EFFECT,
			locality,
			NULL,												// position
			0.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			FALSE,											// looping
			1,													// sample count
			&wind_down_effect								// sample index list
		);

		create_client_server_sound_effect_entity
		(
			en,
			ENTITY_SIDE_NEUTRAL,
			ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN2,
			SOUND_CHANNEL_SOUND_EFFECT,
			locality,
			NULL,												// position
			0.0,												// amplification
			1.0,												// Werewolf pitch
			FALSE,											// valid sound effect
			FALSE,											// looping
			1,													// sample count
			&wind_down_effect								// sample index list
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kill_helicopter_rotor_sound_effects (entity *en)
{
	entity
		*spec,
		*next;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	spec = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

	while (spec)
	{
		next = get_local_entity_child_succ (spec, LIST_TYPE_SPECIAL_EFFECT);

		if (get_local_entity_type (spec) == ENTITY_TYPE_SOUND_EFFECT)
		{
			if ((get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING) ||
					(get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE1) ||
					(get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2) ||
					(get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP) ||
					(get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP1) ||
					(get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP2) ||
					(get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN1) ||
					(get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN2))
			{
				kill_client_server_entity (spec);
			}
		}

		spec = next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HELICOPTER_ROTOR_SOUNDS_LOOPING_MAX_RPM_VALUE	45
#define HELICOPTER_ROTOR_SOUNDS_LOOPING_MIN_RPM_VALUE	30

void update_local_helicopter_rotor_sounds (entity *en)
{
	helicopter
		*raw;

	float
		looping_amp,
		looping_pitch, //Werewolf pitch
		slap_amp,
		left_turbine_amp, right_turbine_amp, apu_amp,
		left_turbine_pitch = 1.0, right_turbine_pitch = 1.0, apu_pitch = 1.0,
		winding_amp,
//		main_rotor_pitch,
//		main_rotor_roll,
		acc_force;

	vec3d
		acc_direction;

	entity
		*spec;

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (raw->main_rotor_rpm >= HELICOPTER_ROTOR_SOUNDS_LOOPING_MAX_RPM_VALUE)
	{
		looping_amp = 1.0;
	}
	else if (raw->main_rotor_rpm <= HELICOPTER_ROTOR_SOUNDS_LOOPING_MIN_RPM_VALUE)
	{
		looping_amp = 0.0;
	}
	else
	{
		looping_amp = (raw->main_rotor_rpm - HELICOPTER_ROTOR_SOUNDS_LOOPING_MIN_RPM_VALUE) /
							(HELICOPTER_ROTOR_SOUNDS_LOOPING_MAX_RPM_VALUE - HELICOPTER_ROTOR_SOUNDS_LOOPING_MIN_RPM_VALUE);
	}

	//Werewolf pitch
	looping_pitch = raw->main_rotor_rpm / 100.0;

	//For AI choppers we need to invert and tweak the RPM value changes, because AI choppers base their rotor RPM on the produced lift
	//(For the AI, more lift => more RPM, which is the exact opposite of what it should be)
	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		looping_pitch = 1.0; //Disabled since it simply doesn't sound right. Someday, someone should figure out a nice way of doing it.

//		looping_pitch = (1.0 - looping_pitch); //this would go from 0.1 to 0.3, so we need further tweaks
//		looping_pitch = looping_pitch / 12.0; //make the pitch changes less drastic
//		looping_pitch = 0.95 + looping_pitch;
	}

	//Slapping sound depends on how harsh the direction changes are: Do a tight turn and the rotor blades will slap
	if (get_current_flight_dynamics ())
	{
		acc_direction.x += current_flight_dynamics->model_acceleration_vector.x;
		acc_direction.y += current_flight_dynamics->model_acceleration_vector.y;
		acc_direction.z += current_flight_dynamics->model_acceleration_vector.z;
		acc_force = (get_3d_vector_magnitude (&acc_direction) / 20.0); //force vector can get as high as 30.0, but 20.0 should suffice for the maximum slap sound
		slap_amp = (acc_force) * looping_amp;
		slap_amp = bound (slap_amp, 0.0, 1.0);
//		debug_log ( "SLAP FORCE %f", acc_force );
	}
	else
	{
		acc_force = 0.0;
		slap_amp = 0.0;
	}



	// arneh - get the engine rpm statistics so we can control the turbine sounds accordingly
	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL
		&& get_current_flight_dynamics ())
	{
		float lrpm = current_flight_dynamics->left_engine_n1_rpm.value;
		float rrpm = current_flight_dynamics->right_engine_n1_rpm.value;
		float apu_rpm = current_flight_dynamics->apu_rpm.value;
		short play_both_sounds = fabs(lrpm - rrpm) > 1.0;    // only play one sound if both engines have same RPM
		
		// sound for left turbine:
		left_turbine_pitch = lrpm / 100.0;
		left_turbine_pitch = bound (left_turbine_pitch, 0.0, 1.6)+0.6;
		left_turbine_amp = 0.2 + bound((lrpm - 40.0) * 0.02, 0.0, 0.4);

		if (lrpm > 1)
			resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE1);
		else
			pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE1, 0.0);

		if (play_both_sounds)
		{
			// sound for right turbine:
			right_turbine_pitch = rrpm / 100.0;
			right_turbine_pitch = bound (right_turbine_pitch, 0.0, 1.6)+0.6;
			right_turbine_amp = 0.2 + bound((rrpm - 40.0) * 0.02, 0.0, 0.4);
	
			if (rrpm > 1)
				resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2);
			else
				pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2, 0.0);
		}
		else
		{
			pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2, 0.0);
			left_turbine_amp *= 1.2;  // if only one sound is used for both engines, compensate by making it louder
		}
		
		// sound for APU:
		if (apu_rpm > 0.0)
		{
			apu_pitch = bound(apu_rpm * 0.02, 0.0, 2.0) + 0.2;
			apu_amp = bound(apu_rpm * 0.01, 0.0, 0.25);
			resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_APU_TURBINE);
		}
		else
			pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_APU_TURBINE, 0.0);
	}
	else
	{
		left_turbine_pitch = right_turbine_pitch = 1.3;
		left_turbine_amp = right_turbine_amp = 0.0;
		apu_pitch = 1.0;
		apu_amp = 0.0;
	}

//	resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE);
//	winding_amp = 1.0 - (looping_amp * looping_amp);
	winding_amp = 0.75;

	if (looping_amp == 0.0)
	{
		pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING, 0.0);
		pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP, 0.0);
	}
	else
	{
		resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING);
		resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP);
	}

	//
	// set sound effect amplification
	//

	spec = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

	while (spec)
	{
		if (spec->type == ENTITY_TYPE_SOUND_EFFECT)
		{
			switch (get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE))
			{
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING:
//			if (get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING)
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, (looping_amp-slap_amp)); //Werewolf: regular rotor sound cuts out when slapping sets in
				set_local_entity_float_value (spec, FLOAT_TYPE_SOUNDPITCH, looping_pitch);            
				break;			
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE1:
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, left_turbine_amp); //Werewolf: turbine sound
				set_local_entity_float_value (spec, FLOAT_TYPE_SOUNDPITCH, left_turbine_pitch); 
				break;
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2:
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, right_turbine_amp);
				set_local_entity_float_value (spec, FLOAT_TYPE_SOUNDPITCH, right_turbine_pitch); 
				break;
			case ENTITY_SUB_TYPE_EFFECT_SOUND_APU_TURBINE:
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, apu_amp);
				set_local_entity_float_value (spec, FLOAT_TYPE_SOUNDPITCH, apu_pitch); 
				break;
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP1:
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP2:
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN1:
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN2:
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, winding_amp);
				break;
			//Werewolf TODO: Implement pitch and volume curves for turbine and slap sounds
			case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP:
				set_local_entity_float_value (spec, FLOAT_TYPE_AMPLIFICATION, (slap_amp)); //Werewolf: slapping sound
				set_local_entity_float_value (spec, FLOAT_TYPE_SOUNDPITCH, looping_pitch);
				break;
			}
		}

		spec = get_local_entity_child_succ (spec, LIST_TYPE_SPECIAL_EFFECT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float kill_sound_effect(entity* en, entity_sub_types type)
{
	float start_position = 0.0;
	sound_effect* sound_raw;
	entity* spec = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

	while (spec)
	{
		if (spec->type == ENTITY_TYPE_SOUND_EFFECT)
		{
			if (get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == type)
			{
				sound_raw = get_local_entity_data (spec);

				if (sound_raw->valid_sound_effect)
				{
					//
					// <stop type> IS playing
					//

					start_position = sound_raw->effect_lifetime;

					//
					// stop it playing
					//

					kill_local_entity (spec);
				}
			}
		}

		spec = get_local_entity_child_succ (spec, LIST_TYPE_SPECIAL_EFFECT);
	}
	
	return start_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_helicopter_winding_rotor_sounds (entity *en, int direction, int engine_num)
{
	helicopter
		*raw;

	sound_effect
		*sound_raw;

	entity
		*spec;

	float
		start_position;

	entity_sub_types
		start_type,
		stop_type;

	ASSERT (en);
	ASSERT ((direction == 1) || (direction == -1));
	ASSERT (engine_num >= 0 && engine_num <= 2);

	raw = get_local_entity_data (en);

	if (direction == 1)
	{
		if (engine_num == 1)
			start_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP1;
		else 
			start_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP2;
		
		if (engine_num == 1)
			stop_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN1;
		else
			stop_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN2;
	}
	else
	{
		if (engine_num == 1)
			start_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN1;
		else
			start_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN2;
			
		if (engine_num == 1)
			stop_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP1;
		else
			stop_type = ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP2;
	}

	//
	// see if <stop type> is playing
	//

	start_position = kill_sound_effect(en, stop_type);

	//
	// set <start type> playing
	//

	spec = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

	while (spec)
	{
		if (spec->type == ENTITY_TYPE_SOUND_EFFECT)
		{
			if (get_local_entity_int_value (spec, INT_TYPE_ENTITY_SUB_TYPE) == start_type)
			{
				sound_raw = get_local_entity_data (spec);

				if (!sound_raw->valid_sound_effect)
				{
					sound_raw->valid_sound_effect = TRUE;

					//
					// set correct effect lifetime
					//

					{
						float
							rate,
							size;

						ASSERT (sound_raw->sound_effect_sequence_count == 1);

						rate = (float)(application_sound_effects [sound_raw->effect_index [0]].rate);
						size = (float)(application_sound_effects [sound_raw->effect_index [0]].size);

						sound_raw->effect_lifetime = (size / rate);

						start_position = bound (start_position, 0.0, sound_raw->effect_lifetime);

						sound_raw->effect_lifetime -= start_position;
					}

					if (!get_local_entity_parent (spec, LIST_TYPE_UPDATE))
					{
						insert_local_entity_into_parents_child_list (spec, LIST_TYPE_UPDATE, get_update_entity (), NULL);
					}
				}
			}
		}

		spec = get_local_entity_child_succ (spec, LIST_TYPE_SPECIAL_EFFECT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_suitable_for_player (entity *en, entity *pilot)
{
	entity
		*task;

	if (!en)
	{
		return FALSE;
	}

	if (get_local_entity_type (en) != ENTITY_TYPE_HELICOPTER)
	{
		// JB 030313 Fly any aircraft
		//return FALSE;
	}

	//
	// don't allow user to set gunship to wrong side helicopter
	// Jabberwock 040202 - unless we're in free flight

	if (pilot)
	{
		if ((get_local_entity_int_value (pilot, INT_TYPE_SIDE) != get_local_entity_int_value (en, INT_TYPE_SIDE)) && (get_game_type () != GAME_TYPE_FREE_FLIGHT))
		{
			return FALSE;
		}
	}

	//
	// check that the entity is the correct sub_type, i.e apache or havoc / comanche or hokum
	//

	if (!get_local_entity_int_value (en, INT_TYPE_PLAYER_CONTROLLABLE))
	{
		return FALSE;
	}

	switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
	{
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
		{
			if (!get_global_apache_havoc_installed())
			{
				// JB 030311 Disable EEAH check
				//return FALSE;
			}

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
		////Moje 030606 Fly the Black-Hawk, 030612 Hind 030816 AH64A and KA50
		case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
		{
			break;
		}
		default:
		{
			// JB 030311 Fly any aircraft
			//debug_fatal ("HELICOP: Player Controllable Flag Set For Invalid Aircraft (%s)", get_local_entity_string (en, STRING_TYPE_FULL_NAME));
		}
	}

	//
	// check that new gunship entity is not already being flown by another human
	//
	
	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		return FALSE;
	}

	//
	// check that new gunship entity is alive
	//

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE) == FALSE)
	{
		return FALSE;
	}

	//
	// check that new gunship entity hasn't ejected
	//

	if (get_local_entity_int_value (en, INT_TYPE_EJECTED))
	{
		return FALSE;
	}

	//
	// check that gunship isn't landing
	//

	// JB 030313 Enable control of aircraft while landing and taxiing.
	/*
	switch (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE))
	{

		case OPERATIONAL_STATE_LANDING:
		case OPERATIONAL_STATE_LANDING_HOLDING:
		case OPERATIONAL_STATE_TAXIING:
		{

			return FALSE;
		}
	}
	*/

	//
	// If the entity is doing a task, only allow player to join it if task incomplete
	//

	task = get_local_entity_primary_task (en);

	if (task)
	{
		if (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) != TASK_INCOMPLETE)
		{
			return TRUE;	////Moje 030606 Changed FALSE to TRUE, makes choppers flyable after mission complete
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_assume_player_control (entity *en)
{
	entity
		*group,
		*guide,
		*task;

	unsigned int
		member_number,
		valid_members;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI);

	//
	// If the helicopter is doing an engage task - destroy the guide, and reassign the helicopter to a valid task
	//

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		ASSERT (task);

		if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE)
		{
			member_number = (1 << get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER));

			valid_members = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

			ASSERT (valid_members == member_number);

			destroy_client_server_entity (guide);

			reassign_group_members_to_valid_tasks (group, task, member_number, FALSE);
		}
	}	

	set_client_server_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER, 0.0);

	update_player_helicopter_waypoint_distance (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void helicopter_release_player_control (entity *en)
{
	entity
		*group,
		*guide,
		*task;

	unsigned int
		member_number;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI);

	//
	// If the helicopter is doing a primary task - reassign the helicopter to a valid task (so it can pick up engage tasks again)
	//

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);
	
		ASSERT (group);
	
		guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);
	
		if (guide)
		{
			task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);
	
			ASSERT (task);
	
			if (get_local_entity_int_value (task, INT_TYPE_PRIMARY_TASK))
			{
				member_number = (1 << get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER));
	
				reassign_group_members_to_valid_tasks (group, task, member_number, TRUE);
			}
		}	
	
		update_player_helicopter_waypoint_distance (en);
	
		if (get_local_entity_int_value (en, INT_TYPE_LANDED))
		{
			set_client_server_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER, MAIN_ROTOR_SPIN_UP_TIMER);
		}
		else
		{
			set_client_server_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER, 0.0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transmit_player_recon_data (entity *en)
{
	entity
		*guide,
		*current_waypoint;

	vec3d
		*wp_pos,
		*en_pos;

	float
		recon_radius;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (guide)
	{
		if (get_guide_criteria_valid (guide, GUIDE_CRITERIA_TRANSMIT_DATA))
		{
			current_waypoint = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);
	
			ASSERT (current_waypoint);

			en_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

			wp_pos = get_local_entity_vec3d_ptr (current_waypoint, VEC3D_TYPE_POSITION);

			recon_radius = get_local_entity_waypoint_database_action_radius_value (current_waypoint, en);

			if (get_sqr_2d_range (wp_pos, en_pos) < (recon_radius * recon_radius))
			{
				debug_log ("HELICOP: Transmitting recon data");

				notify_local_entity (ENTITY_MESSAGE_WAYPOINT_RECON_REACHED, en, current_waypoint);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_helicopter_allowed_to_rearm (entity *en)
{

	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{

		if (helicopter_within_keysite_area (en))
		{

			return TRUE;
		}
	}
	else
	{

		if ((helicopter_within_keysite_area (en)) && (!get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT)))
		{

			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int helicopter_within_keysite_area (entity *en)
{

	vec3d
		*hc_position;

	float
		actual_range;

	entity
		*keysite;

	hc_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, get_local_entity_int_value (en, INT_TYPE_SIDE), hc_position, 5 * KILOMETRE, &actual_range, NULL);

	if (keysite)
	{

		object_3d_instance
			*inst3d;

		vec3d
			position,
			*keysite_pos;
	
		struct OBJECT_3D_BOUNDS
			*bounding_box;

		float
			xmin,
			xmax,
			zmin,
			zmax;
	
		debug_log ("DYNAMICS: landed close to keysite %s (range %f)", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME), actual_range);

		xmin = 0.0;
		xmax = 0.0;
		zmin = 0.0;
		zmax = 0.0;

		switch (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE))
		{

			case ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE:
			{
	
				float
					heading = 0.0;
	
				entity
					*ship;
	
				ship = get_local_entity_parent (keysite, LIST_TYPE_MOVEMENT_DEPENDENT);
	
				ASSERT (ship);
				ASSERT (get_local_entity_type (ship) == ENTITY_TYPE_SHIP_VEHICLE);
	
				heading = get_local_entity_float_value (ship, FLOAT_TYPE_HEADING);
	
				//
				// rotate model position into 'keysite space'
				//
	
				keysite_pos = get_local_entity_vec3d_ptr (ship, VEC3D_TYPE_POSITION);
		
				position.x = hc_position->x - keysite_pos->x;
				position.y = hc_position->y - keysite_pos->y;
				position.z = hc_position->z - keysite_pos->z;
	
				position.x = position.x * cos (-heading) + position.z * sin (-heading);
				position.z = position.z * cos (-heading) - position.x * sin (-heading);
	
				inst3d = get_local_entity_ptr_value (ship, PTR_TYPE_INSTANCE_3D_OBJECT);
	
				bounding_box = get_object_3d_bounding_box_without_lines (inst3d->object_number);

				// make sure that the keysite is at least 200 m radius
				xmin = min (bounding_box->xmin, -200.0);
				xmax = max (bounding_box->xmax, 200.0);
				zmin = min (bounding_box->zmin, -200.0);
				zmax = max (bounding_box->zmax, 200.0);

				break;
			}
			case ENTITY_SUB_TYPE_KEYSITE_FARP:
			{
		
				keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
		
				position.x = hc_position->x - keysite_pos->x;
				position.y = hc_position->y - keysite_pos->y;
				position.z = hc_position->z - keysite_pos->z;
	
				bounding_box = get_object_3d_bounding_box_without_lines (get_local_entity_int_value (keysite, INT_TYPE_OBJECT_INDEX));

				// make sure that the keysite is at least 400 m radius
				xmin = min (bounding_box->xmin, -400.0);
				xmax = max (bounding_box->xmax, 400.0);
				zmin = min (bounding_box->zmin, -400.0);
				zmax = max (bounding_box->zmax, 400.0);

				break;
			}
			default:
			{
		
				keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
		
				position.x = hc_position->x - keysite_pos->x;
				position.y = hc_position->y - keysite_pos->y;
				position.z = hc_position->z - keysite_pos->z;
	
				bounding_box = get_object_3d_bounding_box_without_lines (get_local_entity_int_value (keysite, INT_TYPE_OBJECT_INDEX));

				// make sure that the airbase is at least 400 m radius
				xmin = min (bounding_box->xmin, -400.0);
				xmax = max (bounding_box->xmax, 400.0);
				zmin = min (bounding_box->zmin, -400.0);
				zmax = max (bounding_box->zmax, 400.0);

				break;
			}
		}
	
		if (((position.x > xmin) && (position.x < xmax)) && ((position.z > zmin) && (position.z < zmax)))
		{

			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
