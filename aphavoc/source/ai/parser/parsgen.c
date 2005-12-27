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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include <errno.h>
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE	0
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	debug_mode = FALSE;
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity
	*parser_keysite,
	*parser_force,
	*parser_landing,
	*parser_route,
	*parser_waypoint,
	*parser_member,
	*parser_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char
	*campaign_population_filename,
	*population_placement_filename,
	*side_data_filename;

int
	parser_flight_dynamics_options;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

campaign_trigger_type
	*campaign_trigger_head;

campaign_event_type
	*campaign_event_head;

campaign_while_loop_type
	*campaign_while_loop_head;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void add_campaign_trigger (campaign_trigger type, int value1, int value2, int value3, int value4, char *event_name, campaign_trigger trigger_type);

static campaign_event_type *add_campaign_event (char *name, const char *filename, int file_offset);

static campaign_event_type *get_campaign_event (char *name);

static int trigger_triggered (campaign_trigger_type *this_campaign_trigger);

static campaign_while_loop_type *add_while_loop (const char *filename, int file_offset);

static void destroy_while_loop_head (void);

static int calulate_operator (int value1, char *operator_name, int value2);

static void key_bound_trigger_function (event *ev);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_parser_message (int tag, FILE *file_ptr);

void parser_debug_log (char *msg, ...);

void parser_debug_fatal (char *msg, ...);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
void initialise_parser (void)
{

	campaign_trigger_head = NULL;

	campaign_event_head = NULL;
	
	campaign_while_loop_head = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_campaign_triggers (void)
{

	campaign_trigger
		trigger;

	trigger = CAMPAIGN_TRIGGER_NONE;

	//while (TRUE)
	{

		//trigger = ( trigger + 1 ) % NUM_CAMPAIGN_TRIGGER_TYPES;

		if (!update_script_triggers (trigger))
		{

			//break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int parser_campaign_file (const char *filename, int *offset)
{

	file_tags
		tag;

	campaign_trigger
		trigger;

	int
		return_value,
		value1,
		value2,
		result;

	char
		event_name [64],
		new_filename [64],
		variable_name [64],
		operator_name [64];

	FILE
		*file_ptr;

	session_list_data_type
		*current_session;

	int
		end_wp,
		counter,
		faction_side,
		keysite_type,
		start_base_count,
		required_landing_types;

	float
		keysite_fuel_supplies,
		keysite_ammo_supplies;

	char
		temp_filename [128],
		keysite_name [STRING_TYPE_KEYSITE_NAME_MAX_LENGTH];

	fcloseall ();

	file_ptr = safe_fopen (filename, "r");

	ASSERT (get_valid_current_game_session ());

	current_session = get_current_game_session ();
	
	start_base_count = 0;

	if (!file_ptr)
	{

		debug_fatal ("PARSER: can't load file %s errno %d", filename, errno);

		return 0;
	}

	fseek (file_ptr, *offset, SEEK_SET);

	return_value = 0;

	while (TRUE)
	{

		tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

		if (debug_mode)
		{

			debug_parser_message (tag, file_ptr);
		}

		switch (tag)
		{
	
			case FILE_TAG_START:
			{

				continue;
			}

			case FILE_TAG_ECHO_MESSAGE:
			{

				char
					message [128];

				get_next_file_string (file_ptr, message, sizeof (message));

				parser_debug_log (message);
				debug_log (message);

				return_value = TRUE;

				break;
			}

			case FILE_TAG_END_CAMPAIGN:
			{

				int
					campaign_result;

				campaign_result = get_next_file_enum (file_ptr, campaign_result_names, NUM_CAMPAIGN_RESULT_TYPES);

				return_value = TRUE;

				break;
			}

			case FILE_TAG_WHILE:
			{

				long int
					file_offset;

				file_offset = ftell (file_ptr);

				add_while_loop (filename, file_offset);

				// skip to WHILE_END to induce while_loop
				while (tag = check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
				{

					if (tag == FILE_TAG_END_WHILE)
					{

						break;
					}

					tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				}

				break;
			}

			case FILE_TAG_END_WHILE:
			{

				int
					file_offset;

				file_offset = campaign_while_loop_head->file_offset;

				fseek (file_ptr, file_offset, SEEK_SET);

				*offset = ftell (file_ptr);

				value1 = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				get_next_file_word (file_ptr, operator_name, sizeof (operator_name));

				*offset = ftell (file_ptr);

				value2 = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				if (!if_file_tag_operator (value1, operator_name, value2))
				{
	
					destroy_while_loop_head ();

					while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
					{
	
						if (tag == FILE_TAG_END_WHILE)
						{
	
							break;
						}
					}
				}

				break;
			}

			case FILE_TAG_AUTO_ASSIGN_GUNSHIP:
			{

				int
					flag;

				flag = get_next_file_int (file_ptr);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_AUTO_ASSIGN_GUNSHIP, flag);

				#if DEBUG_MODULE

				debug_log ("PARSER: auto assign gunship = %d", flag);

				#endif

				break;
			}


			case FILE_TAG_CALCULATE:
			{

				*offset = ftell (file_ptr);
				
				value1 = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				get_next_file_word (file_ptr, operator_name, sizeof (operator_name));

				*offset = ftell (file_ptr);

				value2 = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				return_value = calulate_operator (value1, operator_name, value2);

				fclose (file_ptr);

				return return_value;
			}

			case FILE_TAG_IF:
			{

				*offset = ftell (file_ptr);

				value1 = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				get_next_file_word (file_ptr, operator_name, sizeof (operator_name));

				*offset = ftell (file_ptr);

				value2 = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				return_value = if_file_tag_operator (value1, operator_name, value2);

				if (!return_value)
				{
	
					// skip script to ENDIF
					while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
					{
	
						if ((tag == FILE_TAG_ENDIF) || (tag == FILE_TAG_ELSE))
						{
	
							break;
						}
					}
				}

				break;
			}

			case FILE_TAG_ELSE:
			{

				// skip script to ENDIF
				while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
				{

					if ((tag == FILE_TAG_ENDIF) || (tag == FILE_TAG_ELSE))
					{

						break;
					}
				}

				break;
			}

			case FILE_TAG_ENDIF:
			{

				break;
			}

			case FILE_TAG_CREATE_VARIABLE:
			{

				int
					*parser_variable;

				parser_variable = (int *) malloc (sizeof (int));

				get_next_file_word (file_ptr, variable_name, sizeof (variable_name));

				unregister_file_tag_variable (variable_name);

				*offset = ftell (file_ptr);

				*parser_variable = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				register_file_tag_variable (variable_name, parser_variable);

				return_value = TRUE;

				break;
			}

			case FILE_TAG_CALL:
			{

				*offset = ftell (file_ptr);

				return_value = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				break;
			}

			case FILE_TAG_FILENAME:
			{

				int
					file_offset;

				get_next_file_word (file_ptr, new_filename, sizeof (new_filename));

				*offset = ftell (file_ptr);

				file_offset = 0;

				return_value = parser_campaign_file (new_filename, &file_offset);

				fseek (file_ptr, *offset, SEEK_SET);

				break;
			}

			case FILE_TAG_EVENT:
			{

				int
					file_offset;

				campaign_event_type
					*event;

				get_next_file_word (file_ptr, event_name, sizeof (event_name));

				event = get_campaign_event (event_name);

				*offset = ftell (file_ptr);

				file_offset = event->file_offset;

				return_value = parser_campaign_file (filename, &file_offset);

				fseek (file_ptr, *offset, SEEK_SET);

				fclose (file_ptr);

				return return_value;
			}

			case FILE_TAG_CREATE_EVENT:
			{

				long int
					file_offset;

				get_next_file_word (file_ptr, event_name, sizeof (event_name));

				file_offset = ftell (file_ptr);

				add_campaign_event (event_name, filename, file_offset);

				// now skip event script
				while (tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
				{

					if (tag == FILE_TAG_END_EVENT)
					{

						break;
					}
				}

				return_value = TRUE;

				break;
			}

			case FILE_TAG_CREATE_TRIGGER:
			{

				int
					value1,
					value2,
					value3,
					value4,
					type;

				#if DEBUG_MODULE

				debug_log ("PARSER: reading campaign trigger");

				#endif

				type = get_next_file_enum (file_ptr, campaign_trigger_names, NUM_CAMPAIGN_TRIGGER_TYPES);

				value1 = 0;
				value2 = 0;
				value3 = 0;
				value4 = 0;

				switch (type)
				{

					case CAMPAIGN_TRIGGER_BALANCE_OF_POWER:
					{

						// side
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_SIDE);
						value1 = get_next_file_int (file_ptr);

						// goal
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_GOAL);
						value2 = get_next_file_int (file_ptr);

						// event
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_EVENT);
						get_next_file_word (file_ptr, event_name, sizeof (event_name));

						// trigger
						trigger = type;

						break;
					}

					case CAMPAIGN_TRIGGER_TASK_COMPLETED:
					case CAMPAIGN_TRIGGER_TASK_FAILED:
					case CAMPAIGN_TRIGGER_OBJECT_DESTROYED:
					case CAMPAIGN_TRIGGER_OBJECT_FIRED:
					case CAMPAIGN_TRIGGER_OBJECT_TARGETED:
					case CAMPAIGN_TRIGGER_OBJECT_LANDED:
					case CAMPAIGN_TRIGGER_USER_LANDED:
					case CAMPAIGN_TRIGGER_INEFFICIENT_KEYSITE:
					case CAMPAIGN_TRIGGER_WAYPOINT_REACHED:
					case CAMPAIGN_TRIGGER_SECTOR_WON:
					case CAMPAIGN_TRIGGER_SECTOR_LOST:
					case CAMPAIGN_TRIGGER_SECTOR_REACHED:
					{

						// event
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_EVENT);
						get_next_file_word (file_ptr, event_name, sizeof (event_name));

						// trigger
						trigger = type;

						break;
					}
					
					case CAMPAIGN_TRIGGER_TIME_DURATION:
					{

						// days
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_DAYS);
						value1 = get_next_file_int (file_ptr);

						// hours
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_HOURS);
						value2 = get_next_file_int (file_ptr);

						// minutes
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_MINUTES);
						value3 = get_next_file_int (file_ptr);

						// seconds
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_SECONDS);
						value4 = get_next_file_int (file_ptr);

						// event
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_EVENT);
						get_next_file_word (file_ptr, event_name, sizeof (event_name));

						// trigger
						trigger = CAMPAIGN_TRIGGER_NONE;

						break;
					}
					
					case CAMPAIGN_TRIGGER_VARIABLE_CONDITION:
					{

						// if
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_IF);

						// variable_name
						get_next_file_word (file_ptr, variable_name, sizeof (variable_name));
						value1 = get_variable_id (variable_name);

						// operator
						get_next_file_word (file_ptr, operator_name, sizeof (operator_name));
						value2 = get_operator_id (operator_name);

						// value
						value3 = get_next_file_int (file_ptr);

						// event
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_EVENT);
						get_next_file_word (file_ptr, event_name, sizeof (event_name));

						// trigger
						trigger = CAMPAIGN_TRIGGER_NONE;

						break;
					}
					
					case CAMPAIGN_TRIGGER_RANDOM:
					{

						// value
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_VALUE);
						value1 = get_next_file_int (file_ptr);

						// event
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_EVENT);
						get_next_file_word (file_ptr, event_name, sizeof (event_name));

						// trigger
						trigger = CAMPAIGN_TRIGGER_NONE;

						break;
					}

					case CAMPAIGN_TRIGGER_KEY_PRESS:
					{

						// key_code
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_KEY_CODE);
						value1 = get_next_file_enum (file_ptr, dik_names, DIK_APPS);

						// key_modifier
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_KEY_MODIFIER);
						//value2 = get_next_file_int (file_ptr);
						value2 = get_next_file_enum (file_ptr, modifier_type_names, NUM_MODIFIER_TYPES);

						// key_state
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_KEY_STATE);
						//value3 = get_next_file_int (file_ptr);
						value3 = get_next_file_enum (file_ptr, button_state_names, KEY_STATE_EITHER);

						// event
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_EVENT);
						get_next_file_word (file_ptr, event_name, sizeof (event_name));

						// trigger
						trigger = type;

						break;
					}

					case CAMPAIGN_TRIGGER_NONE:
					default:
					{

						parser_debug_log ("Reached unknown trigger");
						debug_fatal ("PARSGEN: unknown trigger %d", type);
					}
				}

				add_campaign_trigger (type, value1, value2, value3, value4, event_name, trigger);

				return_value = TRUE;

				break;
			}

			case FILE_TAG_SET_EVENT_TRIGGERED:
			{

				campaign_event_type
					*event;

				get_next_file_word (file_ptr, event_name, sizeof (event_name));

				event = get_campaign_event (event_name);

				if (!event)
				{

					parser_debug_log ("Unknown event %s", event_name);

					debug_fatal ("PARSGEN: unknown event %s", event_name);
				}

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_VALUE);

				value1 = get_next_file_int (file_ptr);

				event->triggered = value1;

				break;
			}

			case FILE_TAG_SET_VARIABLE:
			{

				int
					*variable_ptr;

				get_next_file_word (file_ptr, variable_name, sizeof (variable_name));

				variable_ptr = get_file_tag_variable (variable_name);

				*offset = ftell (file_ptr);

				*variable_ptr = parser_campaign_file (filename, offset);

				fseek (file_ptr, *offset, SEEK_SET);

				return_value = *variable_ptr;

				break;
			}

			case FILE_TAG_VALUE:
			{

				return_value = get_next_file_int (file_ptr);

				*offset = ftell (file_ptr);

				fclose (file_ptr);

				return return_value;
			}

			case FILE_TAG_VARIABLE:
			{

				int
					*variable;

				get_next_file_word (file_ptr, variable_name, sizeof (variable_name));

				variable = get_file_tag_variable (variable_name);

				return_value = *variable;

				*offset = ftell (file_ptr);

				fclose (file_ptr);

				return return_value;
			}

			case FILE_TAG_SHORT_TEXT_START:
			case FILE_TAG_LONG_TEXT_START:
			case FILE_TAG_TEXT_END:
			{

				break;
			}

			case FILE_TAG_END:
			case FILE_TAG_END_EVENT:
			{

				*offset = ftell (file_ptr);

				fclose (file_ptr);

				return return_value;
			}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GAME STUFF
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			case FILE_TAG_FORCE_NAME:
			{

				char
					name [STRING_TYPE_FORCE_NAME_MAX_LENGTH + 1];

				get_next_file_string (file_ptr, name, sizeof (name));

				set_local_entity_string (get_parser_force (), STRING_TYPE_FORCE_NAME, name);

				break;
			}

			case FILE_TAG_CAMPAIGN_REQUIRES_APACHE_HAVOC:
			{

				int
					flag;

				ASSERT (get_session_entity ());

				flag = get_next_file_int (file_ptr);

				set_client_server_entity_int_value (get_session_entity (), INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC, flag);

				if (flag)
				{
	
					debug_log ("PARSGEN: Marking Campaign as requiring Apache Havoc to be installed");
				}

				break;
			}

			case FILE_TAG_MEDAL:
			{

				int
					medal;

				ASSERT (get_session_entity ());

				medal = get_next_file_enum (file_ptr, medal_type_names, NUM_MEDAL_TYPES);

				set_client_server_entity_int_value (get_session_entity (), INT_TYPE_CAMPAIGN_MEDAL, medal);

				if (medal)
				{
	
					debug_log ("PARSGEN: Campaign medal = %s", medal_type_names [medal]);
				}

				break;
			}

			case FILE_TAG_CAMPAIGN_DATA:
			{

				float
					x_min,
					x_max,
					z_min,
					z_max;

				vec3d
					pos;

				int
					sector_size,
					x_size,
					z_size;

				char
					temp_filename [256];
			
				if (get_gunship_entity ())
				{
			
					get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pos);
				}
				else
				{
			
					pos.x = MID_MAP_X;
					pos.z = MID_MAP_Z;
				}
			
//				planner_set_map_zoom (1);
//				planner_set_current_viewpoint (&pos);
			
				//
				// side data filename
				//

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_FILENAME);

				memset (&temp_filename, 0, sizeof (temp_filename));
			
				get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));

				if (side_data_filename)
				{

					free_mem (side_data_filename);
				}

				side_data_filename = (char *) malloc_heap_mem (strlen (temp_filename) + 1);

				sprintf (side_data_filename, "%s", temp_filename);

				//
				// Population data filename
				//

				if (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_FILENAME)
				{
	
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
	
					ASSERT (result == FILE_TAG_FILENAME);
	
					memset (&temp_filename, 0, sizeof (temp_filename));
				
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					if (population_placement_filename)
					{
	
						free_mem (population_placement_filename);
					}
	
					population_placement_filename = (char *) malloc_heap_mem (strlen (temp_filename) + 1);
	
					sprintf (population_placement_filename, "%s", temp_filename);
				}

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_MAP_X_SIZE);

				x_size = get_next_file_int (file_ptr);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_MAP_Z_SIZE);

				z_size = get_next_file_int (file_ptr);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_MAP_SECTOR_SIZE);

				sector_size = get_next_file_int (file_ptr);

				set_entity_world_map_size (x_size, z_size, sector_size);

				x_min = MIN_MAP_X;
				x_max = MAX_MAP_X;
				z_min = MIN_MAP_Z;
				z_max = MAX_MAP_Z;

				// check for population size
				if (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_MAP_X_MIN)
				{

					// x_min

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					ASSERT (result == FILE_TAG_MAP_X_MIN);

					x_min = get_next_file_float (file_ptr);

					// z_min

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					ASSERT (result == FILE_TAG_MAP_Z_MIN);

					z_min = get_next_file_float (file_ptr);

					// x_max

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					ASSERT (result == FILE_TAG_MAP_X_MAX);

					x_max = get_next_file_float (file_ptr);

					// z_max

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					ASSERT (result == FILE_TAG_MAP_Z_MAX);

					z_max = get_next_file_float (file_ptr);
				}

				//
				// remove.............
				/*
				if (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_FILENAME)
				{
	
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
	
					ASSERT (result == FILE_TAG_FILENAME);
	
					memset (&temp_filename, 0, sizeof (temp_filename));
				
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					if (campaign_population_filename)
					{
	
						free_mem (campaign_population_filename);
					}
	
					campaign_population_filename = (char *) malloc_heap_mem (strlen (temp_filename) + 1);
	
					sprintf (campaign_population_filename, "%s", temp_filename);
				}
				*/
				// remove.............
				//

				//
				// Reinitialise the AI systems
				//

				create_local_only_entities (PACK_MODE_SERVER_SESSION);

				reinitialise_ai_system ();

				load_route_data ();

				/////////////////////////////////////////////
				update_gunships_screen_progress_indicator ();
				/////////////////////////////////////////////

				//
				// create session
				//

				if (!get_session_entity ())
				{
					entity
						*en;
									
					en = create_local_entity
					(
						ENTITY_TYPE_SESSION,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_END
					);

					set_session_random_weather_mode (en);
				}

				//
				// Set population size
				//

				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_X_MIN, x_min);
				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_X_MAX, x_max);
				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_Z_MIN, z_min);
				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_POPULATION_Z_MAX, z_max);

				//
				// create factions
				//

				while (get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_FACTION)
				{
	
					int
						faction_side,
						colour;
	
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
	
					ASSERT (result == FILE_TAG_SIDE);
	
					faction_side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);
	
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
	
					ASSERT (result == FILE_TAG_COLOUR);
	
					colour = get_next_file_enum (file_ptr, sys_colour_names, NUM_SYS_COLOURS);
	
					create_faction (faction_side, colour);
	
					#if DEBUG_MODULE
	
					debug_log ("PARSER: loading campaign populate: faction id %d, colour %d", faction_side, colour);
	
					#endif
				}

				//
				// initialise sectors now all factions are declared.
				//

				/////////////////////////////////////////////
				update_gunships_screen_progress_indicator ();
				/////////////////////////////////////////////

				if (strstr (strupr (side_data_filename), "SID"))
				{

					read_sector_side_file (side_data_filename);
				}
				else if (strstr (strupr (side_data_filename), "DAT"))
				{

					load_ai_sector_data (side_data_filename);
				}

				/////////////////////////////////////////////
				update_gunships_screen_progress_indicator ();
				/////////////////////////////////////////////

				if (population_placement_filename)
				{
	
					read_population_placement_file (population_placement_filename);
				}

				//
				// Read pop file if there is one
				//

				/////////////////////////////////////////////
				update_gunships_screen_progress_indicator ();
				/////////////////////////////////////////////

				if (campaign_population_filename)
				{

					//load_campaign_object_population_data (campaign_population_filename);
				}

				break;
			}

			case FILE_TAG_WEATHER_RAIN:
			{

				int
					rain_effect;

				ASSERT (get_session_entity ());

				rain_effect = get_next_file_int (file_ptr);
				//if (get_global_season() == SESSION_SEASON_WINTER)
					//rain_effect = 1;
	
				if (!rain_effect)
				{

					set_session_fixed_weather_mode (get_session_entity (), WEATHERMODE_DRY);
				}

				debug_log ("PARSGEN: Rain effect %d", rain_effect);

				break;
			}

			case FILE_TAG_WEATHER_WIND:
			{

				float
					wind_effect;

				wind_effect = get_next_file_float (file_ptr);

				debug_log ("PARSGEN: Wind effect %f", wind_effect);

				break;
			}

			case FILE_TAG_START_BASE:
			{

				if (get_parser_keysite ())
				{

					if (get_global_gunship_side () == get_local_entity_int_value (get_parser_keysite (), INT_TYPE_SIDE))
					{

						start_base_count ++;
/*
						if (!get_base_current_keysite ())
						{

							set_base_current_keysite (get_parser_keysite ());
						}
						else if (!(rand16 () % start_base_count))
						{

							set_base_current_keysite (get_parser_keysite ());
						}
						*/
					}
				}

				break;
			}

			case FILE_TAG_TASK_GENERATION:
			{
				ASSERT (get_parser_force ());

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_TYPE)
				{

					int
						valid,
						this_type;

					force
						*raw;

					raw = get_local_entity_data (get_parser_force ());

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					ASSERT (result == FILE_TAG_TYPE);

					this_type = get_next_file_enum (file_ptr, entity_sub_type_task_names, NUM_ENTITY_SUB_TYPE_TASKS);

					valid = get_next_file_int (file_ptr);

					ASSERT ((valid == 0) || (valid == 1));

					raw->task_generation [this_type].valid = valid;

					#if DEBUG_MODULE

					debug_log ("PARSER: campaign load : setting %s force %s task generation to ", entity_side_names [get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)], entity_sub_type_task_names [this_type], duration, frequency, urgency);

					#endif
				}

				break;
			}

			case FILE_TAG_HARDWARE_RESERVES:
			{

				force_info_catagories
					hardware_type;

				int
					count;

				force
					*force_raw;

				ASSERT (get_parser_force ());

				force_raw = get_local_entity_data (get_parser_force ());

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_TYPE)
				{

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					ASSERT (result == FILE_TAG_TYPE);

					hardware_type = get_next_file_enum (file_ptr, force_info_catagory_names, NUM_FORCE_INFO_CATAGORIES);

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					ASSERT (result == FILE_TAG_COUNT);

					count = get_next_file_int (file_ptr);

					force_raw->force_info_reserve_hardware [hardware_type] = count;

					#if DEBUG_MODULE

					debug_log ("PARSER: %s reserve %d", force_info_catagory_names [hardware_type], count);

					#endif
				}

				break;
			}

			case FILE_TAG_TITLE:
			{

				char
					title [256];

				get_next_file_string (file_ptr, title, 256);

				break;
			}

			case FILE_TAG_FACTION:
			{

				int
					colour;

				entity_force_attitude_types
					attitude;

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_SIDE);

				faction_side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_COLOUR);

				colour = get_next_file_enum (file_ptr, sys_colour_names, NUM_SYS_COLOURS);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_ATTITUDE);

				attitude = get_next_file_enum (file_ptr, entity_force_attitude_names, NUM_ENTITY_FORCE_ATTITUDES);

				set_parser_force (get_local_force_entity (faction_side));

				if (!get_parser_force ())
				{

					debug_fatal ("PARSER: campaign load: Undefined Faction %d", faction_side);
				}

				set_local_entity_int_value (get_parser_force (), INT_TYPE_FORCE_ATTITUDE, attitude);

//				create_frontline (get_parser_force ());

				#if DEBUG_MODULE

				debug_log ("PARSER: campaign load: faction side %s, colour %s, attitude %s",
								entity_side_names [faction_side],
								sys_colour_names [colour],
								entity_force_attitude_names [attitude]);

				#endif

				break;
			}

			case FILE_TAG_REGEN_FREQUENCY:
			{

				float
					frequency;

				entity_sides
					side;

				frequency = get_next_file_float (file_ptr);

				ASSERT (get_parser_force ());

				ASSERT (frequency > 0.0);

				side = get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE);

				debug_log ("PARSER: %s setting regen frequency to %f", entity_side_names [side], frequency);

				regen_frequency [side] = frequency;

				break;
			}

			case FILE_TAG_DIVISION_ID_LIST:
			{

				entity_sides
					side;

				entity_sub_types
					sub_type;

				int
					value,
					count;

				static int
					number_list [128];

				side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_TYPE)
				{
				 	result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					 
				   ASSERT (result == FILE_TAG_TYPE);

					sub_type = get_next_file_enum (file_ptr, entity_sub_type_division_names, NUM_ENTITY_SUB_TYPE_DIVISIONS);

				   result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					
				   ASSERT (result == FILE_TAG_LIST);

					count = 0;

					value = get_next_file_int (file_ptr);

					while (value != -1 )
					{
						ASSERT (value > 0);

						if (count >= 128)
						{
							debug_fatal ("PARSGEN: Side %s, Division Type %s, Count Exceeded Max (128)",
													entity_side_short_names [side],
													entity_sub_type_division_names [sub_type]);
						}
					
						number_list [count] = value;

						count ++;

						value = get_next_file_int (file_ptr);
					}

					if (count > 0)
					{
						add_division_id_data (side, sub_type, count, number_list);
					}
				}

				break;
			}

			case FILE_TAG_FRONTLINE_FORCES:
			{

				int
					value;

				entity
					*keysite;

				value = get_next_file_int (file_ptr);

				if (value > 0)
				{

					place_frontline_forces (get_parser_force (), value);

					//
					// initialise forces at farps
					//

					keysite = get_local_entity_first_child (get_parser_force (), LIST_TYPE_KEYSITE_FORCE);

					counter = 0;

					while (keysite)
					{

						if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
						{

							if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_FARP)
							{

								set_parser_keysite (keysite);
				
								switch (counter & 0x03)
								{
									case 0:
									{
										create_landed_faction_group (keysite, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER, FORMATION_COMPONENT_HELICOPTER_LIGHT_RECON_ATTACK_GROUP);
										create_landed_faction_group (keysite, ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER, FORMATION_COMPONENT_HELICOPTER_LIGHT_ASSAULT_GROUP);

										break;
									}
									case 1:
									{
										create_landed_faction_group (keysite, ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER, FORMATION_COMPONENT_HELICOPTER_LIGHT_ATTACK_GROUP_A);
										create_landed_faction_group (keysite, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER, FORMATION_COMPONENT_HELICOPTER_LIGHT_RECON_ATTACK_GROUP);

										break;
									}
									case 2:
									{
										create_landed_faction_group (keysite, ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER, FORMATION_COMPONENT_HELICOPTER_LIGHT_ATTACK_GROUP_A);
										create_landed_faction_group (keysite, ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER, FORMATION_COMPONENT_HELICOPTER_LIGHT_ASSAULT_GROUP);

										break;
									}
									case 3:
									{
										create_landed_faction_group (keysite, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER, FORMATION_COMPONENT_HELICOPTER_LIGHT_RECON_ATTACK_GROUP);

										break;
									}
								}

								counter ++;

								debug_log ("PARSER: placing FARP %s helicopters for side %s", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME), entity_side_names [get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)]);
							}
						}

						keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
					}
				}

				break;
			}

			case FILE_TAG_KEYSITE:
			{

				keysite_type = get_next_file_enum (file_ptr, entity_sub_type_keysite_names, NUM_ENTITY_SUB_TYPE_KEYSITES);

				ASSERT (get_parser_force ());

				set_parser_keysite (NULL);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_NAME);

				get_next_file_string (file_ptr, keysite_name, STRING_TYPE_KEYSITE_NAME_MAX_LENGTH);

				//
				// get what type of landing entities are required
				//

				required_landing_types = 0;

				while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_TYPE)
				{

					int
						this_type;

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					ASSERT (result == FILE_TAG_TYPE);

					this_type = get_next_file_enum (file_ptr, entity_sub_type_landing_names, NUM_ENTITY_SUB_TYPE_LANDINGS);

					ASSERT (!(required_landing_types & 1 << this_type));

					required_landing_types |= 1 << this_type;
				}

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_AMMO_SUPPLIES);

				keysite_ammo_supplies = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_FUEL_SUPPLIES);

				keysite_fuel_supplies = get_next_file_float (file_ptr);

				#if DEBUG_MODULE

				debug_log ("PARSER: campaign load: keysite type %s, ammo %f fuel %f", entity_sub_type_keysite_names [keysite_type], keysite_ammo_supplies, keysite_fuel_supplies);

				#endif

				break;
			}

			case FILE_TAG_CREATE_MEMBERS:
			{

				int
					group_type,
					member_type,
					count;

				entity
					*group,
					*member;

				member = NULL;

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_GROUP);

				group_type = get_next_file_enum (file_ptr, entity_sub_type_group_names, NUM_ENTITY_SUB_TYPE_GROUPS);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_MEMBER);

				switch (group_database [group_type].registry_list_type)
				{

					case LIST_TYPE_AIR_REGISTRY:
					{

						member_type = get_next_file_enum (file_ptr, entity_sub_type_aircraft_names, NUM_ENTITY_SUB_TYPE_AIRCRAFT);

						break;
					}

					default:
					{

                  member_type = get_next_file_enum (file_ptr, entity_sub_type_vehicle_names, NUM_ENTITY_SUB_TYPE_VEHICLES);

						break;
					}
				}

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_COUNT);

				count = get_next_file_int (file_ptr);

				if (!get_parser_keysite ())
				{

					//
					// local keysite with correct landing entity
					//

					ASSERT (get_parser_force ());

					//
					// Locate suitable free keysite
					//

					set_parser_keysite (get_local_entity_first_child (get_parser_force (), LIST_TYPE_KEYSITE_FORCE));

					while (get_parser_keysite ())
					{

						if ((get_local_entity_int_value (get_parser_keysite (), INT_TYPE_ENTITY_SUB_TYPE) == keysite_type) &&
							(get_local_entity_int_value (get_parser_keysite (), INT_TYPE_IN_USE) == FALSE) &&
							(get_local_entity_int_value (get_parser_keysite (), INT_TYPE_SIDE) == faction_side) &&
							(strcmpi (keysite_name, get_local_entity_string (get_parser_keysite (), STRING_TYPE_KEYSITE_NAME)) == 0))
						{

							if (get_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES) != required_landing_types)
							{

								#if DEBUG_MODULE

								debug_log ("PARSER: warning ! keysite landing types not fully used");

								#endif
							}

							//
							// DONT mark Keysite as used (do it after it has Actually been used!)
							// set_local_entity_int_value (keysite, INT_TYPE_IN_USE, TRUE);
							//

							set_local_entity_float_value (get_parser_keysite (), FLOAT_TYPE_AMMO_SUPPLY_LEVEL, keysite_ammo_supplies);

							set_local_entity_float_value (get_parser_keysite (), FLOAT_TYPE_FUEL_SUPPLY_LEVEL, keysite_fuel_supplies);

							break;
						}

						set_parser_keysite (get_local_entity_child_succ (get_parser_keysite (), LIST_TYPE_KEYSITE_FORCE));
					}
				}

  				if (!get_parser_keysite ())
				{

					debug_fatal ("PARSER: campaign load: Side %s - Can't locate keysite %s", entity_side_short_names [faction_side], keysite_name);
				}

				if (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) == FILE_TAG_MOBILE_KEYSITE)
				{

					formation_component_types
						formation_components;

					get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
	
					ASSERT (result == FILE_TAG_FORMATION_COMPONENT);
		
					formation_components = get_next_file_enum (file_ptr, formation_component_names, NUM_FORMATION_COMPONENT_TYPES);
	
					group = create_faction_members (get_parser_keysite (), group_type, formation_components, count, get_local_entity_int_value (get_parser_keysite (), INT_TYPE_SIDE), get_local_entity_vec3d_ptr (get_parser_keysite (), VEC3D_TYPE_POSITION), TRUE, TRUE);

					ASSERT (group);

					member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

					insert_local_entity_into_parents_child_list (get_parser_keysite (), LIST_TYPE_MOVEMENT_DEPENDENT, member, NULL);
				}
				else
				{

					group = create_landed_faction_members (get_parser_keysite (), member_type, group_type, count);
	
					if (group)
					{

						member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
	
						#if DEBUG_MODULE
	
						debug_log ("PARSER: campaign load: create members, keysite %d, group type %d, entity type %d, member type %d, count %d", get_parser_keysite (), group_type, member_type, count);
	
						#endif
					}
				}

				set_parser_member (member);

				break;
			}

			case FILE_TAG_CREATE_GROUP:
			{

				int
					group_type,
					formation_component_type;

				entity
					*group;

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_GROUP);

				group_type = get_next_file_enum (file_ptr, entity_sub_type_group_names, NUM_ENTITY_SUB_TYPE_GROUPS);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_TYPE);

				formation_component_type = get_next_file_enum (file_ptr, formation_component_names, NUM_FORMATION_COMPONENT_TYPES);

				if (!get_parser_keysite ())
				{

					//
					// local keysite with correct landing entity
					//

					ASSERT (get_parser_force ());

					//
					// Locate suitable free keysite
					//

					set_parser_keysite (get_local_entity_first_child (get_parser_force (), LIST_TYPE_KEYSITE_FORCE));

					while (get_parser_keysite ())
					{

						if ((get_local_entity_int_value (get_parser_keysite (), INT_TYPE_ENTITY_SUB_TYPE) == keysite_type) &&
							(get_local_entity_int_value (get_parser_keysite (), INT_TYPE_IN_USE) == FALSE) &&
							(get_local_entity_int_value (get_parser_keysite (), INT_TYPE_SIDE) == faction_side) &&
							(strcmpi (keysite_name, get_local_entity_string (get_parser_keysite (), STRING_TYPE_KEYSITE_NAME)) == 0))
						{

							if (get_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES) != required_landing_types)
							{

								#if DEBUG_MODULE

								debug_log ("PARSER: warning ! keysite landing types not fully used");

								#endif
							}

							//
							// DONT mark Keysite as used (do it after it has Actually been used!)
							// set_local_entity_int_value (keysite, INT_TYPE_IN_USE, TRUE);
							//

							set_local_entity_float_value (get_parser_keysite (), FLOAT_TYPE_AMMO_SUPPLY_LEVEL, keysite_ammo_supplies);

							set_local_entity_float_value (get_parser_keysite (), FLOAT_TYPE_FUEL_SUPPLY_LEVEL, keysite_fuel_supplies);

							break;
						}

						set_parser_keysite (get_local_entity_child_succ (get_parser_keysite (), LIST_TYPE_KEYSITE_FORCE));
					}
				}

  				if (!get_parser_keysite ())
				{

					debug_fatal ("PARSER: campaign load: Side %s - Can't locate keysite %s", entity_side_short_names [faction_side], keysite_name);
				}

				group = create_landed_faction_group (get_parser_keysite (), group_type, formation_component_type);
	
				#if DEBUG_MODULE
	
				debug_log ("PARSER: campaign load: create group, keysite %d, formation component type %s, entity type %d, member type %d, count %d",
				get_parser_keysite (),
				formation_component_names [formation_component_type],
				member_type,
				count);
	
				#endif

				break;
			}

			case FILE_TAG_CREATE_TASK:
			{

				vec3d
					*wp_nodes;

				movement_types
					movement_type;

				entity
					*wp,
					*group_en,
					*new_task;

				entity_sub_types
					task_type,
					*wp_types;

				entity_sides
					side;

				float
					*wp_radius,
					start_time,
					stop_time,
					expire_time;

				int
//					*wp_criteria,
					*wp_delta_time,
					count,
					wp_count;

				ASSERT (get_parser_member ());

				group_en = get_local_entity_parent (get_parser_member (), LIST_TYPE_MEMBER);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_TYPE);
				task_type = get_next_file_enum (file_ptr, entity_sub_type_task_names, NUM_ENTITY_SUB_TYPE_TASKS);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_SIDE);
				side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_MOVEMENT);
				movement_type = get_next_file_enum (file_ptr, movement_names, NUM_MOVEMENT_TYPES);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				//ASSERT (result == FILE_TAG_TIME);
				start_time = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				//ASSERT (result == FILE_TAG_TIME);
				stop_time = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				//ASSERT (result == FILE_TAG_TIME);
				expire_time = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_CREATE_WAYPOINT);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_COUNT);

				wp_count = get_next_file_int (file_ptr);
				wp_nodes = (vec3d *) malloc_heap_mem (sizeof (vec3d) * wp_count);
				wp_types = (entity_sub_types *) malloc_heap_mem (sizeof (entity_sub_types) * wp_count);
				wp_radius = (float *) malloc_heap_mem (sizeof (float) * wp_count);
//				wp_criteria = (int *) malloc_heap_mem (sizeof (int) * wp_count);
				wp_delta_time = (int *) malloc_heap_mem (sizeof (int) * wp_count);

				memset (wp_nodes, 0, sizeof (vec3d) * wp_count);
				memset (wp_types, 0, sizeof (entity_sub_types) * wp_count);
				memset (wp_radius, 0, sizeof (float) * wp_count);
//				memset (wp_criteria, 0, sizeof (int) * wp_count);
				memset (wp_delta_time, 0, sizeof (int) * wp_count);

				wp_count = -1;

				end_wp = FALSE;

				while ((!end_wp) && (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) != FILE_TAG_TEXT_END))
				{

					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

					switch (result)
					{

						case FILE_TAG_TYPE:
						{

							wp_count ++;
	
							wp_types [wp_count] = get_next_file_enum (file_ptr, entity_sub_type_waypoint_names, NUM_ENTITY_SUB_TYPE_WAYPOINTS);

							break;
						}

						case FILE_TAG_POSITION:
						{

							ASSERT (wp_count >= 0);
									
							wp_nodes [wp_count].x = get_next_file_float (file_ptr);
							wp_nodes [wp_count].y = get_next_file_float (file_ptr);
							wp_nodes [wp_count].z = get_next_file_float (file_ptr);
			
							break;
						}
/*
						case FILE_TAG_CRITERIA:
						{

							ASSERT (wp_count >= 0);

							wp_criteria [wp_count] |= (1 << (get_next_file_enum (file_ptr, waypoint_criteria_names, NUM_WAYPOINT_CRITERIA_TYPES) - 1));

							break;
						}

*/						case FILE_TAG_RADIUS:
						{

							ASSERT (wp_count >= 0);

							wp_radius [wp_count] = get_next_file_float (file_ptr);

							break;
						}

						case FILE_TAG_DELTA_TIME:
						{

							ASSERT (wp_count >= 0);

							wp_delta_time [wp_count] = get_next_file_int (file_ptr) * TIME_1_SECOND;

							break;
						}

						case FILE_TAG_TEXT_END:
						{

							ASSERT (wp_count >= 0);

							end_wp = TRUE;

							break;
						}
					}
				}

				new_task = create_task (task_type,
									side,
									movement_type,
									NULL,
									NULL,
									NULL,
									TRUE,
									expire_time,
									0.0,
									group_en,
									10.0,
									&wp_nodes [0], NULL, wp_types [0], FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

				count = 0;

				wp = NULL;

				while (count <= wp_count)
				{
					wp = create_local_entity
					(
						ENTITY_TYPE_WAYPOINT,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT (LIST_TYPE_WAYPOINT, new_task),
						ENTITY_ATTR_CHILD_PRED (LIST_TYPE_WAYPOINT, wp),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, wp_types [count]),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_WAYPOINT_FORMATION, FORMATION_ROW_LEFT),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_POSITION_TYPE, POSITION_TYPE_ABSOLUTE),
						ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, wp_nodes [count].x, wp_nodes [count].y, wp_nodes [count].z),
						ENTITY_ATTR_PTR_VALUE (PTR_TYPE_POSITION_ENTITY, NULL),
						ENTITY_ATTR_END
					);
				
			  		count ++;
				}

				//
				// Assign task
				//
		
				push_task_onto_group_task_stack (group_en, new_task, TASK_ASSIGN_ALL_MEMBERS);
		
				assign_task_to_group_members (group_en, new_task, TASK_ASSIGN_ALL_MEMBERS);

				break;
			}

			case FILE_TAG_VERSION_NUMBER:
			{

				int
					version;

				version = get_next_file_int (file_ptr);

				#if DEBUG_MODULE

				debug_log ("PARSGEN: version number %d", version);

				#endif

				break;
			}

	//VJ 051202 add season file tag for winter/summer camo		
			case FILE_TAG_SEASON:
			{
				int
					season = 0;
				
				season = get_next_file_int (file_ptr);
				//VJ 051227 use set and get global season here
				set_global_season( season );

				#if DEBUG_MODULE

				debug_log ("PARSGEN: season %d", get_global_season() );

				#endif

				
				break;
			}


			case FILE_TAG_SAVED_CAMPAIGN:
			{

				int
					server_version_number,
					client_version_number,
					campaign_size;

				FILE
					*saved_file_ptr;

				char
					*load_ptr,
					*campaign_buffer,
					filename [128];

//				comms_model_types
//					comms_model;

				// Data Path
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_PATH);

				get_next_file_string (file_ptr, current_session->data_path, sizeof (current_session->data_path));

				// Campaign Directory
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_PATH);

				get_next_file_string (file_ptr, current_session->campaign_directory, sizeof (current_session->campaign_directory));

				// Get full pathname for .SAV file (must be done before campaign filename overwritten)
				strcpy (temp_filename, current_session->campaign_filename);

				load_ptr = strrchr (temp_filename, '.');

				*load_ptr = 0;

				sprintf (filename, "%s\\%s\\%s.sav",
								current_session->data_path,
								current_session->campaign_directory,
								temp_filename);

				// Campaign Filename
				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_FILENAME);

				get_next_file_string (file_ptr, current_session->campaign_filename, sizeof (current_session->campaign_filename));

				// load .save file
				saved_file_ptr = safe_fopen (filename, "rb");

				campaign_size = file_size (filename);

				campaign_buffer = (char *) malloc_heap_mem (sizeof (char) * (campaign_size + 1));

				load_ptr = campaign_buffer;

				fread (campaign_buffer, campaign_size + 1, 1, saved_file_ptr);

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// check version number
				client_version_number = get_global_version_number ();

				server_version_number = get_list_item (load_ptr, int);

				campaign_size -= sizeof (int);

				if (client_version_number != server_version_number)
				{

					debug_fatal ("COMM_MAN: Server Version No. %d, Client Version No. %d", server_version_number, client_version_number);
				}
				//
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// unpack session
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				unpack_session (load_ptr, campaign_size, PACK_MODE_SERVER_SESSION);
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				fclose (saved_file_ptr);

				free_mem (campaign_buffer);

				break;
			}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLD PARSER
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			default:
			{

				debug_fatal ("PARSGEN: unknown TAG");
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_campaign_trigger (campaign_trigger type, int value1, int value2, int value3, int value4, char *event_name, campaign_trigger trigger_type)
{

	campaign_trigger_type
		*new_campaign_trigger;

	new_campaign_trigger = (campaign_trigger_type *) malloc (sizeof (campaign_trigger_type));

	memset (new_campaign_trigger, 0, sizeof (campaign_trigger_type));

	new_campaign_trigger->type = type;

	new_campaign_trigger->trigger_type = trigger_type;

	new_campaign_trigger->value1 = value1;
	new_campaign_trigger->value2 = value2;
	new_campaign_trigger->value3 = value3;
	new_campaign_trigger->value4 = value4;

	new_campaign_trigger->event_name = (char *) malloc (strlen (event_name) + 1);
	sprintf (new_campaign_trigger->event_name, "%s", event_name);

	new_campaign_trigger->next = campaign_trigger_head;

	campaign_trigger_head = new_campaign_trigger;

	#if DEBUG_MODULE

	debug_log ("FORCE: Campaign trigger %s, value1 = %d value2 = %d value3 = %d value4 = %d, result %s", campaign_trigger_names [trigger_type], value1, value2, value3, value4, campaign_trigger_result_names [result]);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

campaign_event_type *add_campaign_event (char *name, const char *filename, int file_offset)
{

	campaign_event_type
		*new_event;

	if (get_campaign_event (name))
	{

		parser_debug_log ("ERROR: EVENT %s already exists", name);

		return NULL;
	}

	new_event = (campaign_event_type *) malloc (sizeof (campaign_event_type));

	memset (new_event, 0, sizeof (campaign_event_type));

	new_event->name = (char *) malloc (strlen (name) + 1);
	sprintf (new_event->name, "%s", name);

	new_event->filename = (char *) malloc (strlen (filename) + 1);
	sprintf (new_event->filename, "%s", filename);

	new_event->triggered = FALSE;

	new_event->file_offset = file_offset;

	new_event->next = campaign_event_head;

	campaign_event_head = new_event;

	return new_event;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_script_triggers (campaign_trigger trigger)
{

	int
		offset,
		return_value;

	campaign_trigger_type
		*this_campaign_trigger;

	campaign_event_type
		*event;

	return_value = 0;

	this_campaign_trigger = campaign_trigger_head;

	while (this_campaign_trigger)
	{

		if (this_campaign_trigger->trigger_type == trigger)
		{
	
			if (trigger_triggered (this_campaign_trigger))
			{
	
				if (this_campaign_trigger->event_name)
				{
		
					event = get_campaign_event (this_campaign_trigger->event_name);
		
					if (event)
					{

						if (!event->triggered)
						{
	
							//parser_debug_log ("EXECUTING EVENT %s", this_campaign_trigger->event_name);
	
							offset = event->file_offset;

							event->triggered = FALSE;
			
							return_value = parser_campaign_file (event->filename, &offset);
						}
					}
				}
			}
		}

		this_campaign_trigger = this_campaign_trigger->next;
	}

	return return_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_key_bound_triggers (void)
{

	int
		key,
		state,
		modifier;

	campaign_trigger_type
		*this_campaign_trigger;

	campaign_event_type
		*event;

	this_campaign_trigger = campaign_trigger_head;

	while (this_campaign_trigger)
	{

		if (this_campaign_trigger->trigger_type == CAMPAIGN_TRIGGER_KEY_PRESS)
		{
	
			if (this_campaign_trigger->event_name)
			{
	
				event = get_campaign_event (this_campaign_trigger->event_name);
	
				if (event)
				{

					parser_debug_log ("Binding EVENT %s to key %d, modifier %d, state %d", this_campaign_trigger->event_name, this_campaign_trigger->value1, this_campaign_trigger->value2, this_campaign_trigger->value3);
					debug_log ("Binding EVENT %s to key %d, modifier %d, state %d", this_campaign_trigger->event_name, this_campaign_trigger->value1, this_campaign_trigger->value2, this_campaign_trigger->value3);

					key = this_campaign_trigger->value1;
					modifier = this_campaign_trigger->value2;
					state = this_campaign_trigger->value3;

					set_event (key, modifier, state, key_bound_trigger_function);
				}
			}
		}

		this_campaign_trigger = this_campaign_trigger->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void key_bound_trigger_function (event *ev)
{

	int
		return_value,
		offset;

	campaign_trigger_type
		*this_campaign_trigger;

	campaign_event_type
		*event;

	this_campaign_trigger = campaign_trigger_head;

	while (this_campaign_trigger)
	{

		if (this_campaign_trigger->value1 == ev->key)
		{

			if (this_campaign_trigger->value2 == ev->modifier)
			{

				if (this_campaign_trigger->value3 == ev->state)
				{
		
					event = get_campaign_event (this_campaign_trigger->event_name);
		
					if (event)
					{

						if (!event->triggered)
						{
		
							parser_debug_log ("calling EVENT %s to key %d, modifier %d, state %d", this_campaign_trigger->event_name, this_campaign_trigger->value1, this_campaign_trigger->value2, this_campaign_trigger->value3);
							debug_log ("calling EVENT %s to key %d, modifier %d, state %d", this_campaign_trigger->event_name, this_campaign_trigger->value1, this_campaign_trigger->value2, this_campaign_trigger->value3);
	
							offset = event->file_offset;

							event->triggered = FALSE;
				
							return_value = parser_campaign_file (event->filename, &offset);
						}
					}
				}
			}
		}

		this_campaign_trigger = this_campaign_trigger->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

campaign_event_type *get_campaign_event (char *name)
{
	campaign_event_type
		*this_campaign_event;

	this_campaign_event = campaign_event_head;

	while (this_campaign_event)
	{

		if (stricmp (this_campaign_event->name, name) == 0)
		{

			return this_campaign_event;
		}

		this_campaign_event = this_campaign_event->next;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int trigger_triggered (campaign_trigger_type *this_campaign_trigger)
{

	int
		return_value;

	const char
		*variable_name;
	char
		operator_name;

	return_value = FALSE;

	switch (this_campaign_trigger->type)
	{

		case CAMPAIGN_TRIGGER_BALANCE_OF_POWER:
		{

			int
				balance_of_power;

			balance_of_power = 50.0; // done per side...

			if (balance_of_power > this_campaign_trigger->value2)
			{

				return_value =  TRUE;
			}

			break;
		}
		case CAMPAIGN_TRIGGER_TASK_COMPLETED:
		case CAMPAIGN_TRIGGER_TASK_FAILED:
		case CAMPAIGN_TRIGGER_OBJECT_DESTROYED:
		case CAMPAIGN_TRIGGER_OBJECT_FIRED:
		case CAMPAIGN_TRIGGER_OBJECT_TARGETED:
		case CAMPAIGN_TRIGGER_INEFFICIENT_KEYSITE:
		case CAMPAIGN_TRIGGER_WAYPOINT_REACHED:
		case CAMPAIGN_TRIGGER_SECTOR_WON:
		case CAMPAIGN_TRIGGER_SECTOR_LOST:
		case CAMPAIGN_TRIGGER_SECTOR_REACHED:
		{

			return_value =  TRUE;

			break;
		}

		case CAMPAIGN_TRIGGER_TIME_DURATION:
		{

			int
				elapsed_days,
				elapsed_hours,
				elapsed_minutes,
				elapsed_seconds;

			float
				elapsed_time;

			//
			// check time criteria
			//

			elapsed_time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_ELAPSED_TIME);

			convert_float_to_int (elapsed_time / ONE_DAY, &elapsed_days);

			elapsed_time = fmod (elapsed_time, ONE_DAY);

			get_digital_clock_int_values (elapsed_time, &elapsed_hours, &elapsed_minutes, &elapsed_seconds);

			if (elapsed_days >= this_campaign_trigger->days)
			{

				if (elapsed_hours >= this_campaign_trigger->hours)
				{

					if (elapsed_minutes >= this_campaign_trigger->minutes)
					{

						if (elapsed_seconds >= this_campaign_trigger->seconds)
						{

							return_value = TRUE;
						}
					}
				}
			}

			break;
		}
		case CAMPAIGN_TRIGGER_VARIABLE_CONDITION:
		{

			variable_name = get_variable_name (this_campaign_trigger->value1);

			operator_name = get_operator_name (this_campaign_trigger->value2);

			return_value = if_file_tag_variable (variable_name, &operator_name, this_campaign_trigger->value3);

			break;
		}

		case CAMPAIGN_TRIGGER_RANDOM:
		{

			int
				random;

			random = (rand16 () % this_campaign_trigger->value1);

			if (random == 0)
			{

				return_value = TRUE;
			}

			break;
		}
	}

	return return_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

campaign_while_loop_type *add_while_loop (const char *filename, int file_offset)
{

	campaign_while_loop_type
		*new_while_loop;

	new_while_loop = (campaign_while_loop_type *) malloc (sizeof (campaign_while_loop_type));

	memset (new_while_loop, 0, sizeof (campaign_while_loop_type));

	new_while_loop->filename = (char *) malloc (strlen (filename) + 1);
	sprintf (new_while_loop->filename, "%s", filename);

	new_while_loop->file_offset = file_offset;

	new_while_loop->next = campaign_while_loop_head;

	campaign_while_loop_head = new_while_loop;

	return new_while_loop;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_while_loop_head (void)
{

	campaign_while_loop_type
		*destroy_while_loop;

	destroy_while_loop = campaign_while_loop_head;

	campaign_while_loop_head = campaign_while_loop_head->next;

	free (destroy_while_loop->filename);

	free (destroy_while_loop);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int calulate_operator (int value1, char *operator_name, int value2)
{

	int
		return_value;

	switch (*operator_name)
	{

		case '+':
		{

			return_value = value1 + value2;

			break;
		}

		case '-':
		{

			return_value = value1 - value2;

			break;
		}
		case '*':
		{

			return_value = value1 * value2;

			break;
		}
		case '/':
		{

			return_value = value1 / value2;

			break;
		}

		default:
		{

			char
				log_string [256];

			sprintf (log_string, "PARSGEN: unknown operator %c", operator_name [0]);
			debug_fatal (log_string);
		}
	}

	return return_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_parser_message (int tag, FILE *file_ptr)
{

	char
		event_name [64],
		operator_name [64],
		variable_name [64];

	int
		value1,
		//value2,
		//offset,
		original_file_offset;

	original_file_offset = ftell (file_ptr);

	switch (tag)
	{

		case FILE_TAG_START:
		{

			parser_debug_log ("START");

			break;
		}

		case FILE_TAG_ECHO_MESSAGE:
		{

			char
				message [128];

			get_next_file_string (file_ptr, message, sizeof (message));

			parser_debug_log ("%s (format : %s message) found %s", application_tag_strings [tag], application_tag_strings [tag], message);

			break;
		}

		case FILE_TAG_END_CAMPAIGN:
		{

			value1 = get_next_file_enum (file_ptr, campaign_result_names, NUM_CAMPAIGN_RESULT_TYPES);

			parser_debug_log ("%s (format : %s result) found %s", application_tag_strings [tag], application_tag_strings [tag], campaign_result_names [value1]);

			break;
		}

		case FILE_TAG_WHILE:
		{

			parser_debug_log ("%s (format : %s condition, SCRIPT, END_WHILE)", application_tag_strings [tag], application_tag_strings [tag]);

			while (tag = check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
			{

				if (tag == FILE_TAG_END_WHILE)
				{

					break;
				}

				parser_debug_log ("			script = tag %s", application_tag_strings [tag]);

				tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
			}

			parser_debug_log ("END_WHILE");

			break;
		}

		case FILE_TAG_END_WHILE:
		{

			parser_debug_log ("%s evaluating condition", application_tag_strings [tag]);
			parser_debug_log ("");

			break;
		}

		case FILE_TAG_CALCULATE:
		{

			parser_debug_log ("%s (format : %s value1 operator value2)", application_tag_strings [tag], application_tag_strings [tag]);

			break;
		}

		case FILE_TAG_IF:
		{

			parser_debug_log ("%s (format : %s value1 operator value2)", application_tag_strings [tag], application_tag_strings [tag]);

			break;
		}

		case FILE_TAG_ELSE:
		{

			parser_debug_log ("");

			break;
		}

		case FILE_TAG_ENDIF:
		{

			parser_debug_log ("");

			break;
		}

		case FILE_TAG_CREATE_VARIABLE:
		{

			parser_debug_log ("");

			get_next_file_word (file_ptr, variable_name, sizeof (variable_name));

			parser_debug_log ("%s (format : %s name value) : %s", application_tag_strings [tag], application_tag_strings [tag], variable_name);

			break;
		}

		case FILE_TAG_CALL:
		{

			parser_debug_log ("%s (format : %s :SCRIPT)", application_tag_strings [tag], application_tag_strings [tag]);

			break;
		}

		case FILE_TAG_EVENT:
		{

			get_next_file_word (file_ptr, event_name, sizeof (event_name));

			parser_debug_log ("%s (format : %s name) = %s", application_tag_strings [tag], application_tag_strings [tag], event_name);

			break;
		}

		case FILE_TAG_CREATE_EVENT:
		{

			parser_debug_log ("");

			get_next_file_word (file_ptr, event_name, sizeof (event_name));

			parser_debug_log ("%s (format : %s name) = %s", application_tag_strings [tag], application_tag_strings [tag], event_name);

			break;
		}

		case FILE_TAG_CREATE_TRIGGER:
		{

			int
				result,
				value1,
				value2,
				value3,
				value4,
				type;

			parser_debug_log ("");

			parser_debug_log ("%s (format : %s TRIGGER)", application_tag_strings [tag], application_tag_strings [tag]);

			type = get_next_file_enum (file_ptr, campaign_trigger_names, NUM_CAMPAIGN_TRIGGER_TYPES);

			value1 = 0;
			value2 = 0;
			value3 = 0;
			value4 = 0;

			switch (type)
			{

				case CAMPAIGN_TRIGGER_BALANCE_OF_POWER:
				{

					// side
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value1 = get_next_file_int (file_ptr);

					// goal
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value2 = get_next_file_int (file_ptr);

					// event
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					get_next_file_word (file_ptr, event_name, sizeof (event_name));

					parser_debug_log ("%s (format : %s :SIDE side :GOAL goal :EVENT event_name) = %d, %d, %s",
									campaign_trigger_names [type], campaign_trigger_names [type], value1, value2, event_name);

					break;
				}

				case CAMPAIGN_TRIGGER_TASK_COMPLETED:
				case CAMPAIGN_TRIGGER_TASK_FAILED:
				case CAMPAIGN_TRIGGER_OBJECT_DESTROYED:
				case CAMPAIGN_TRIGGER_OBJECT_FIRED:
				case CAMPAIGN_TRIGGER_OBJECT_TARGETED:
				case CAMPAIGN_TRIGGER_INEFFICIENT_KEYSITE:
				case CAMPAIGN_TRIGGER_WAYPOINT_REACHED:
				case CAMPAIGN_TRIGGER_SECTOR_WON:
				case CAMPAIGN_TRIGGER_SECTOR_LOST:
				case CAMPAIGN_TRIGGER_SECTOR_REACHED:
				{

					// side
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value1 = get_next_file_int (file_ptr);

					// event
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					get_next_file_word (file_ptr, event_name, sizeof (event_name));

					parser_debug_log ("%s (format : %s :SIDE side :EVENT event_name) = %d, %s",
									campaign_trigger_names [type], campaign_trigger_names [type], value1, event_name);

					break;
				}
				
				case CAMPAIGN_TRIGGER_TIME_DURATION:
				{

					// days
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value1 = get_next_file_int (file_ptr);

					// hours
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value2 = get_next_file_int (file_ptr);

					// minutes
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value3 = get_next_file_int (file_ptr);

					// seconds
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value4 = get_next_file_int (file_ptr);

					// event
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					get_next_file_word (file_ptr, event_name, sizeof (event_name));

					parser_debug_log ("%s (format : %s :DAYS days :HOURS hours :MINUTES minutes :SECONDS seconds :EVENT event_name) = %d, %d, %d, %d, %s",
									campaign_trigger_names [type], campaign_trigger_names [type], value1, value2, value3, value4, event_name);

					break;
				}
				
				case CAMPAIGN_TRIGGER_VARIABLE_CONDITION:
				{

					// if
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					ASSERT (result == FILE_TAG_IF);

					// variable_name
					get_next_file_word (file_ptr, variable_name, sizeof (variable_name));
					value1 = get_variable_id (variable_name);

					// operator
					get_next_file_word (file_ptr, operator_name, sizeof (operator_name));
					value2 = get_operator_id (operator_name);

					// value
					value3 = get_next_file_int (file_ptr);

					// event
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					get_next_file_word (file_ptr, event_name, sizeof (event_name));

					parser_debug_log ("%s (format : %s :IF variable_name operator value :EVENT event) = %s, %s, %d, %s",
									campaign_trigger_names [type], campaign_trigger_names [type], variable_name, &operator_name [0], value3, event_name);

					break;
				}
				
				case CAMPAIGN_TRIGGER_RANDOM:
				{

					// value
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					value1 = get_next_file_int (file_ptr);

					// event
					result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
					get_next_file_word (file_ptr, event_name, sizeof (event_name));

					parser_debug_log ("%s (format : %s range :EVENT event) = %d, %s",
									campaign_trigger_names [type], campaign_trigger_names [type], value1, event_name);

					break;
				}
			}

			break;
		}

		case FILE_TAG_SET_EVENT_TRIGGERED:
		{

			int
				result;

			campaign_event_type
				*event;

			get_next_file_word (file_ptr, event_name, sizeof (event_name));

			event = get_campaign_event (event_name);

			result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
			ASSERT (result == FILE_TAG_VALUE);

			value1 = get_next_file_int (file_ptr);

			if (!event)
			{

				parser_debug_log ("Unknown event %s", event_name);

				debug_fatal ("PARSGEN: unknown event %s", event_name);
			}
			else
			{

				parser_debug_log ("%s (format : %s event_name flag) = %s, %d",
							application_tag_strings [tag], application_tag_strings [tag], event_name, value1);
			}

			break;
		}

		case FILE_TAG_SET_VARIABLE:
		{

			get_next_file_word (file_ptr, variable_name, sizeof (variable_name));

			parser_debug_log ("%s (format : %s variable_name :SCRIPT) = %s",
							application_tag_strings [tag], application_tag_strings [tag], variable_name);

			break;
		}

		case FILE_TAG_VALUE:
		{

			value1 = get_next_file_int (file_ptr);

			parser_debug_log ("%s (format : %s value) = %d",
							application_tag_strings [tag], application_tag_strings [tag], value1);

			break;
		}

		case FILE_TAG_VARIABLE:
		{

			get_next_file_word (file_ptr, variable_name, sizeof (variable_name));

			parser_debug_log ("%s (format : %s variable_name) = %s",
							application_tag_strings [tag], application_tag_strings [tag], variable_name);

			break;
		}
/*
		case FILE_TAG_CREATE_TASK:
		case FILE_TAG_CREATE_GROUP:
		case FILE_TAG_CREATE_MEMBERS:
		{

			parser_debug_log ("");

			parser_debug_log ("%s (format : %s :TYPE type :SIDE side :WAYPOINTS x, y, z ...)",
							application_tag_strings [tag], application_tag_strings [tag]);

			break;
		}
*/
		case FILE_TAG_END:
		case FILE_TAG_END_EVENT:
		{

			parser_debug_log ("");

			break;
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLD PARSER
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case FILE_TAG_CAMPAIGN_DATA:
		case FILE_TAG_START_BASE:
		case FILE_TAG_AUTO_ASSIGN_GUNSHIP:
		case FILE_TAG_TASK_GENERATION:
		case FILE_TAG_HARDWARE_RESERVES:
		case FILE_TAG_TITLE:
		case FILE_TAG_FACTION:
		case FILE_TAG_ATTITUDE:
		case FILE_TAG_REGEN_FREQUENCY:
		case FILE_TAG_FRONTLINE_FORCES:
		{

			parser_debug_log ("placing frontline forces");

			break;
		}
		case FILE_TAG_KEYSITE:
		{

			parser_debug_log ("creating keysite");

			break;
		}

		case FILE_TAG_CREATE_MEMBERS:
		{

			parser_debug_log ("creating member");

			break;
		}

		case FILE_TAG_CREATE_GROUP:
		{

			parser_debug_log ("creating group");

			break;
		}

		case FILE_TAG_CREATE_TASK:
		{

			parser_debug_log ("creating task");

			break;
		}

		case FILE_TAG_SAVED_CAMPAIGN:
		{

			parser_debug_log ("loading saved campaign");

			break;
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OLD PARSER
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		default:
		{

			parser_debug_log ("unknown TAG");
		}
	}

	fseek (file_ptr, original_file_offset, SEEK_SET);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parser_debug_log (char *msg, ...)
{

	FILE
		*file_ptr;

	static char
		buffer [1000];

	va_list
		args;

	file_ptr = fopen ("parser.log", "a");

	if (file_ptr)
	{

		va_start (args, msg);

		vsprintf (buffer, msg, args);

		va_end (args);

		fwrite (buffer, 1, strlen (buffer), file_ptr);

		fwrite ("\n", 1, 1, file_ptr);

		fclose (file_ptr);

		debug_filtered_log (buffer);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parser_debug_fatal (char *msg, ...)
{

	FILE
		*file_ptr;

	static char
		buffer [1000];

	va_list
		args;

	file_ptr = fopen ("parser.log", "a");

	if (file_ptr)
	{
		sprintf (buffer, "***************************** FATAL ******************************");
		fwrite (buffer, 1, strlen (buffer), file_ptr);

		va_start (args, msg);

		vsprintf (buffer, msg, args);

		va_end (args);

		fwrite (buffer, 1, strlen (buffer), file_ptr);

		fwrite ("\n", 1, 1, file_ptr);

		fclose (file_ptr);

		exit (1);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
