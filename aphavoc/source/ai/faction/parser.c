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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
entity
	*parser_keysite = nullptr,
	*parser_force = nullptr,
	*parser_landing = nullptr,
	*parser_route = nullptr,
	*parser_waypoint = nullptr,
	*parser_member = nullptr,
	*parser_object = nullptr;
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
char
	*campaign_population_filename = nullptr,
	*population_placement_filename = nullptr,
	*side_data_filename = nullptr;

int
	parser_flight_dynamics_options;
#endif
float
	regen_frequency_modifier [NUM_ENTITY_SIDES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void initialise_parser (void)
{

	parser_flight_dynamics_options = 0;

	campaign_population_filename = NULL;

	population_placement_filename = NULL;

	side_data_filename = NULL;

	parser_keysite = NULL;
	
	parser_force = NULL;
	
	parser_landing = NULL;
	
	parser_route = NULL;
	
	parser_waypoint = NULL;
	
	parser_member = NULL;
	
	parser_object = NULL;

	regen_frequency_modifier [ENTITY_SIDE_BLUE_FORCE] = 1.0;

	regen_frequency_modifier [ENTITY_SIDE_RED_FORCE] = 1.0;
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
void load_campaign_file (session_list_data_type *session)
{

	session_list_data_type
		*current_session = nullptr;

	FILE
		*file_ptr = nullptr;

	file_tags
		tag;

	int
		//value,
		result,
		end_wp,
		counter,
		//rank_points,
		faction_side,
		keysite_type,
		start_base_count,
		//experience_points,
		required_landing_types;

	float
		keysite_fuel_supplies,
		keysite_ammo_supplies;

	char
		//variable [64],
		//operator [64],
		temp_filename [128],
		keysite_name [STRING_TYPE_KEYSITE_NAME_MAX_LENGTH];

	ASSERT (get_valid_current_game_session ());

	current_session = get_current_game_session ();

	sprintf (temp_filename, "%s\\%s", session->data_path, session->filename);
	
	start_base_count = 0;

	file_ptr = safe_fopen (temp_filename, "r");

	while (TRUE)
	{
		/////////////////////////////////////////////
		update_gunships_screen_progress_indicator ();
		/////////////////////////////////////////////

		tag = get_next_file_tag (file_ptr);

		switch (tag)
		{

			case FILE_TAG_START:
			{

				continue;
			}
/*
			case FILE_TAG_IF:
			{

				ASSERT (get_current_player_log ());

				get_next_file_word (file_ptr, variable, sizeof (variable));

				get_next_file_word (file_ptr, operator, sizeof (operator));

				value = get_next_file_int (file_ptr);

				if (!if_file_tag_variable (variable, operator, value))
				{

					// skip script till endif

					while (tag = get_next_file_tag (file_ptr))
					{

						if (tag == FILE_TAG_ENDIF)
						{

							break;
						}
					}
				}

				break;
			}
			

			case FILE_TAG_ENDIF:
			{

				break;
			}
*/
			case FILE_TAG_CAMPAIGN_DATA:
			{

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

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_FILENAME);

				memset (&temp_filename, 0, sizeof (temp_filename));
			
				get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));

				#if DEBUG_MODULE

				debug_log ("PARSER: reading side data file %s", temp_filename);

				#endif

				if (side_data_filename)
				{

					free_mem (side_data_filename);
				}

				side_data_filename = (char *) malloc_heap_mem (strlen (temp_filename) + 1);

				sprintf (side_data_filename, "%s", temp_filename);

				//
				// Population data filename
				//

				if (check_next_file_tag (file_ptr) == FILE_TAG_FILENAME)
				{
	
					result = get_next_file_tag (file_ptr);
	
					ASSERT (result == FILE_TAG_FILENAME);
	
					memset (&temp_filename, 0, sizeof (temp_filename));
				
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					#if DEBUG_MODULE
	
					debug_log ("PARSER: reading population data file %s", temp_filename);
	
					#endif
	
					if (population_placement_filename)
					{
	
						free_mem (population_placement_filename);
					}
	
					population_placement_filename = (char *) malloc_heap_mem (strlen (temp_filename) + 1);
	
					sprintf (population_placement_filename, "%s", temp_filename);
				}

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_MAP_X_SIZE);

				x_size = get_next_file_int (file_ptr);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_MAP_Z_SIZE);

				z_size = get_next_file_int (file_ptr);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_MAP_SECTOR_SIZE);

				sector_size = get_next_file_int (file_ptr);

				set_entity_world_map_size (x_size, z_size, sector_size);

				//
				//
				//

				if (check_next_file_tag (file_ptr) == FILE_TAG_FILENAME)
				{
	
					result = get_next_file_tag (file_ptr);
	
					ASSERT (result == FILE_TAG_FILENAME);
	
					memset (&temp_filename, 0, sizeof (temp_filename));
				
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					#if DEBUG_MODULE
	
					debug_log ("PARSER: reading campaign population data file %s", temp_filename);
	
					#endif
	
					if (campaign_population_filename)
					{
	
						free_mem (campaign_population_filename);
					}
	
					campaign_population_filename = (char *) malloc_heap_mem (strlen (temp_filename) + 1);
	
					sprintf (campaign_population_filename, "%s", temp_filename);
				}

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
						*en = nullptr;
									
					en = create_local_entity
					(
						ENTITY_TYPE_SESSION,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_END
					);

					attach_session_sound_effects (en);

					set_session_random_weather_mode (en);
				}

				//
				// create factions
				//

				while (check_next_file_tag (file_ptr) == FILE_TAG_FACTION)
				{
	
					int
						faction_side,
						colour;
	
					result = get_next_file_tag (file_ptr);
	
					ASSERT (result == FILE_TAG_FACTION);
	
					result = get_next_file_tag (file_ptr);
	
					ASSERT (result == FILE_TAG_SIDE);
	
					faction_side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);
	
					result = get_next_file_tag (file_ptr);
	
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

				initialise_ai_sectors ();

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

				initialise_node_awareness ();

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

					load_campaign_object_population_data (campaign_population_filename);
				}

				if (check_next_file_tag (file_ptr) == FILE_TAG_AIR_NODE_ROUTE_DATA)
				{

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_AIR_NODE_ROUTE_DATA);
	
					//
					// load campaign population data
					//
	
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					set_route_node_data_filename (&air_route_node_data_filename, temp_filename);
	
					set_route_node_data_filename (&air_route_node_data_filename, temp_filename);
					set_route_node_data_filename (&air_route_node_positions_filename, temp_filename);
	
					deinitialise_air_route_data ();
	
					read_air_route_data ();
				}

				/////////////////////////////////////////////
				update_gunships_screen_progress_indicator ();
				/////////////////////////////////////////////

				if (check_next_file_tag (file_ptr) == FILE_TAG_ROAD_NODE_ROUTE_DATA)
				{

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_ROAD_NODE_ROUTE_DATA);
	
					//
					// load campaign population data
					//
	
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					set_route_node_data_filename (&road_route_node_data_filename, temp_filename);
					set_route_node_data_filename (&road_route_node_positions_filename, temp_filename);
					set_route_node_data_filename (&road_route_node_link_position_data_filename, temp_filename);
	
					deinitialise_road_route_data ();
	
					read_road_route_data ();
				}

				/////////////////////////////////////////////
				update_gunships_screen_progress_indicator ();
				/////////////////////////////////////////////
/*
				if (check_next_file_tag (file_ptr) == FILE_TAG_RIVER_NODE_ROUTE_DATA)
				{
	
					result = get_next_file_tag (file_ptr);
	
					ASSERT (result == FILE_TAG_ROAD_NODE_ROUTE_DATA);
	
					//
					// load campaign population data
					//
	
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					set_route_node_data_filename (&river_route_node_data_filename, temp_filename);
					set_route_node_data_filename (&river_route_node_positions_filename, temp_filename);
					set_route_node_data_filename (&river_route_node_link_position_data_filename, temp_filename);
	
					deinitialise_river_route_data ();
	
					read_river_route_data ();
				}
*/
				if (check_next_file_tag (file_ptr) == FILE_TAG_SEA_NODE_ROUTE_DATA)
				{
		
					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_SEA_NODE_ROUTE_DATA);
	
					//
					// load campaign population data
					//
	
					get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));
	
					set_route_node_data_filename (&sea_route_node_data_filename, temp_filename);
					set_route_node_data_filename (&sea_route_node_positions_filename, temp_filename);
	
					deinitialise_sea_route_data ();
	
					read_sea_route_data ();
				}

				/////////////////////////////////////////////
				update_gunships_screen_progress_indicator ();
				/////////////////////////////////////////////

				break;
			}
/*
			case FILE_TAG_START_BASE:
			{

				if (get_parser_keysite ())
				{

					if (get_global_gunship_side () == get_local_entity_int_value (get_parser_keysite (), INT_TYPE_SIDE))
					{

						start_base_count ++;

						if (!get_base_current_keysite ())
						{

							set_base_current_keysite (get_parser_keysite ());
						}
						else if (!(rand16 () % start_base_count))
						{

							set_base_current_keysite (get_parser_keysite ());
						}
					}
				}

				break;
			}
			*/
/*
			case FILE_TAG_OPTION_INVULNERABLE:
			{

				int
					flag;

				flag = get_next_file_int (file_ptr);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE, flag);

				//#if DEBUG_MODULE

				debug_log ("PARSER: campaign load : invulnerable %d", flag);

				//#endif

				break;
			}

			case FILE_TAG_OPTION_INFINITE_FUEL:
			{

				int
					flag;

				flag = get_next_file_int (file_ptr);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_FUEL, flag);

				//#if DEBUG_MODULE

				debug_log ("PARSER: campaign load : infinite_fuel %d", flag);

				//#endif

				break;
			}

			case FILE_TAG_OPTION_INFINITE_WEAPONS:
			{

				int
					flag;

				flag = get_next_file_int (file_ptr);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_WEAPONS, flag);

				//#if DEBUG_MODULE

				debug_log ("PARSER: campaign load : infinite_weapons %d", flag);

				//#endif

				break;
			}

			case FILE_TAG_OPTION_SUPPRESS_AI_FIRE:
			{

				int
					flag;

				flag = get_next_file_int (file_ptr);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE, flag);

				//#if DEBUG_MODULE

				debug_log ("PARSER: campaign load : suppress_ai_fire %d", flag);

				//#endif

				break;
			}

			case FILE_TAG_TOUR_OF_DUTY:
			{

				float
					initial_tour_of_duty;

				//
				// in hours.
				//

				initial_tour_of_duty = 0.0;

				if (check_next_file_tag (file_ptr) == FILE_TAG_HOURS)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_HOURS);

					initial_tour_of_duty += get_next_file_int (file_ptr) * ONE_HOUR;
				}

				if (check_next_file_tag (file_ptr) == FILE_TAG_MINUTES)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_MINUTES);

					initial_tour_of_duty += get_next_file_int (file_ptr) * ONE_MINUTE;
				}

				if (check_next_file_tag (file_ptr) == FILE_TAG_SECONDS)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_SECONDS);

					initial_tour_of_duty += get_next_file_int (file_ptr) * ONE_SECOND;
				}

				debug_log ("PARSER: setting tour of duty timer to %f hours", initial_tour_of_duty);

				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TOUR_OF_DUTY_TIME, initial_tour_of_duty);

				break;
			}

			case FILE_TAG_TIME:
			{

				float
					hour,
					minute,
					second;

				hour = get_next_file_float (file_ptr);

				minute = get_next_file_float (file_ptr);

				second = get_next_file_float (file_ptr);

				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY, get_time_of_day (hour, minute, second));

				#if DEBUG_MODULE

				debug_log ("PARSER: campaign load : time = %.0f:%.0f.%.0f", hour, minute, second);

				#endif

				break;
			}

			case FILE_TAG_WEATHER:
			{

				vec3d
					position,
					velocity;

				float
					radius;

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_POSITION);

				position.x = get_next_file_float (file_ptr);
				position.y = get_next_file_float (file_ptr);
				position.z = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_VELOCITY);

				velocity.x = get_next_file_float (file_ptr);
				velocity.y = get_next_file_float (file_ptr);
				velocity.z = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_RADIUS);

				radius = get_next_file_float (file_ptr);

				set_local_entity_vec3d (get_session_entity (), VEC3D_TYPE_WEATHER_POSITION, &position);

				set_local_entity_vec3d (get_session_entity (), VEC3D_TYPE_WEATHER_VELOCITY, &velocity);

				set_local_entity_float_value (get_session_entity (), FLOAT_TYPE_RADIUS, radius);

				#if DEBUG_MODULE

				debug_log ("PARSER: setting weather position %f, %f, %f, velocity %f, %f, %f, radius %f", position.x, position.y, position.z, velocity.x, velocity.y, velocity.z, radius);

				#endif

				break;
			}
*/
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

			case FILE_TAG_FLIGHT_DYNAMICS:
			{

				int
					flag;

				dynamics_options_types
					option_type;

				while (check_next_file_tag (file_ptr) == FILE_TAG_TYPE)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_TYPE);

					option_type = get_next_file_enum (file_ptr, dynamics_options_type_names, NUM_DYNAMICS_OPTIONS_TYPES);

					flag = get_next_file_int (file_ptr);

					if (flag)
					{

						parser_flight_dynamics_options |= (1 << option_type);
							
						#if DEBUG_MODULE

						debug_log ("PARSER: campaign load: flight dynamics %s = %d", dynamics_options_type_names [option_type], flag);

						#endif
					}
				}

				break;
			}

			case FILE_TAG_PLANNER_DATA:
			{

				int
					zoom;

				vec3d
					pos;

				if (check_next_file_tag (file_ptr) == FILE_TAG_POSITION)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_POSITION);

					pos.x = get_next_file_float (file_ptr);
					pos.z = get_next_file_float (file_ptr);

//					planner_set_current_viewpoint (&pos);
				}

				if (check_next_file_tag (file_ptr) == FILE_TAG_ZOOM)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_ZOOM);

					zoom = get_next_file_int (file_ptr);

//					planner_set_map_zoom (zoom);
				}

				#if DEBUG_MODULE

				debug_log ("PARSER: planenr data : position %f, %f zoom %d", planner_map_data.centre_x, planner_map_data.centre_z, planner_map_data.actual_map_zoom);

				#endif

				break;
			}
/*
			case FILE_TAG_DATE:
			{

				int
					day,
					month,
					year;

				day = get_next_file_int (file_ptr);

				month = get_next_file_int (file_ptr);

				year = get_next_file_int (file_ptr);

				ASSERT (day <= month_data [month].number_of_days);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_DAY, day);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_MONTH, month);

				set_local_entity_int_value (get_session_entity (), INT_TYPE_YEAR, year);

				#if DEBUG_MODULE

				debug_log ("PARSER: campaign load : date = %d %s %d", day, month_data [month].name, year);

				#endif

				break;
			}

			case FILE_TAG_CAMPAIGN_CRITERIA:
			{

				char
					variable_name [64];

				campaign_criteria_result_types
					campaign_result;

				int
					*experience_variable = nullptr,
					*rank_variable = nullptr,
					value1,
					value2,
					value3,
					value4,
					type;

				force
					*raw = nullptr;

				ASSERT (get_parser_force ());

				raw = get_local_entity_data (get_parser_force ());

				#if DEBUG_MODULE

				debug_log ("PARSER: reading campaign criteria");

				#endif

				while (check_next_file_tag (file_ptr) == FILE_TAG_CRITERIA)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_CRITERIA);

					type = get_next_file_enum (file_ptr, campaign_criteria_names, NUM_CAMPAIGN_CRITERIA_TYPES);

					value1 = 0;
					value2 = 0;
					value3 = 0;
					value4 = 0;

					experience_points = 0;
					experience_variable = NULL;

					rank_points = 0;
					rank_variable = NULL;

					switch (type)
					{

						case CAMPAIGN_CRITERIA_BALANCE_OF_POWER:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_COMPLETED_TASKS:
						case CAMPAIGN_CRITERIA_FAILED_TASKS:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_TYPE);
							value3 = get_next_file_enum (file_ptr, entity_sub_type_task_names, NUM_ENTITY_SUB_TYPE_TASKS);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_DESTROYED_ALLIED_OBJECTS:
						case CAMPAIGN_CRITERIA_DESTROYED_ENEMY_OBJECTS:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_TYPE);
							value3 = get_next_file_enum (file_ptr, object_3d_enumeration_names, OBJECT_3D_LAST);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_INEFFICIENT_ALLIED_KEYSITES:
						case CAMPAIGN_CRITERIA_INEFFICIENT_ENEMY_KEYSITES:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_TYPE);
							value3 = get_next_file_enum (file_ptr, entity_sub_type_keysite_names, NUM_ENTITY_SUB_TYPE_KEYSITES);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_SURRENDERED_SIDES:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_SECTOR_REACHED:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_X_SECTOR);
							value3 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_Z_SECTOR);
							value4 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_REACHED_WAYPOINTS:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_TYPE);
							value3 = get_next_file_enum (file_ptr, entity_sub_type_waypoint_names, NUM_ENTITY_SUB_TYPE_WAYPOINTS);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_TIME_DURATION:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_DAYS);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_HOURS);
							value2 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_MINUTES);
							value3 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_SECONDS);
							value4 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_CAPTURED_SECTORS:
						case CAMPAIGN_CRITERIA_LOST_SECTORS:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}

						case CAMPAIGN_CRITERIA_ENEMY_FIRED:
						{

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_GOAL);
							value1 = get_next_file_int (file_ptr);

							result = get_next_file_tag (file_ptr);
							ASSERT (result == FILE_TAG_RESULT);
							campaign_result = get_next_file_enum (file_ptr, campaign_criteria_result_names, NUM_CAMPAIGN_CRITERIA_RESULT_TYPES);

							break;
						}
					}

					if (check_next_file_tag (file_ptr) == FILE_TAG_EXPERIENCE_POINTS)
					{

						result = get_next_file_tag (file_ptr);
						ASSERT (result == FILE_TAG_EXPERIENCE_POINTS);
						experience_points = get_next_file_int (file_ptr);

						result = get_next_file_tag (file_ptr);
						ASSERT (result == FILE_TAG_VARIABLE);

						get_next_file_string (file_ptr, variable_name, sizeof (variable_name));
						experience_variable = get_file_tag_variable (&variable_name);
					}

					if (check_next_file_tag (file_ptr) == FILE_TAG_RANK_POINTS)
					{

						result = get_next_file_tag (file_ptr);
						ASSERT (result == FILE_TAG_RANK_POINTS);
						rank_points = get_next_file_int (file_ptr);

						result = get_next_file_tag (file_ptr);
						ASSERT (result == FILE_TAG_VARIABLE);

						get_next_file_string (file_ptr, variable_name, sizeof (variable_name));
						rank_variable = get_file_tag_variable (&variable_name);
					}

					add_force_campaign_critiera (get_parser_force (), type, value1, value2, value3, value4, campaign_result, experience_points, rank_points, experience_variable, rank_variable);
				}

				break;
			}
			*/

			case FILE_TAG_TASK_GENERATION:
			{

				float
					duration,
					frequency,
					urgency;

				ASSERT (get_parser_force ());

				while (check_next_file_tag (file_ptr) == FILE_TAG_TYPE)
				{

					int
						this_type;

					force
						*raw = nullptr;

					raw = get_local_entity_data (get_parser_force ());

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_TYPE);

					this_type = get_next_file_enum (file_ptr, entity_sub_type_task_names, NUM_ENTITY_SUB_TYPE_TASKS);

					duration = get_next_file_float (file_ptr);

					ASSERT ((duration >= 0.0) && (duration <= 48 * ONE_HOUR));

					frequency = get_next_file_float (file_ptr) / 100.0;

					ASSERT ((frequency >= 0.0) && (frequency <= 1.0));

					urgency = get_next_file_float (file_ptr) / 100.0;

					ASSERT ((urgency >= 0.0) && (urgency <= 1.0));

					raw->task_generation [this_type].valid = TRUE;

					raw->task_generation [this_type].duration = duration;

					raw->task_generation [this_type].frequency = frequency;

					raw->task_generation [this_type].urgency = urgency;

					#if DEBUG_MODULE

					debug_log ("PARSER: campaign load : setting %s force %s task generation to duration %f frequency %f, urgency %f", entity_side_names [get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)], entity_sub_type_task_names [this_type], duration, frequency, urgency);

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
					*force_raw = nullptr;

				ASSERT (get_parser_force ());

				force_raw = get_local_entity_data (get_parser_force ());

				while (check_next_file_tag (file_ptr) == FILE_TAG_TYPE)
				{

					result = get_next_file_tag (file_ptr);
					ASSERT (result == FILE_TAG_TYPE);

					hardware_type = get_next_file_enum (file_ptr, force_info_catagory_names, NUM_FORCE_INFO_CATAGORIES);

					result = get_next_file_tag (file_ptr);
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

				#if DEBUG_MODULE

				debug_log ("PARSER: campaign load: faction title %s", title);

				#endif

				break;
			}

			case FILE_TAG_FACTION:
			{

				int
					colour;

				entity_force_attitude_types
					attitude;

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_SIDE);

				faction_side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_COLOUR);

				colour = get_next_file_enum (file_ptr, sys_colour_names, NUM_SYS_COLOURS);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_ATTITUDE);

				attitude = get_next_file_enum (file_ptr, entity_force_attitude_names, NUM_ENTITY_FORCE_ATTITUDES);

				set_parser_force (get_local_force_entity (faction_side));

				if (!get_parser_force ())
				{

					debug_fatal ("PARSER: campaign load: Undefined Faction %d", faction_side);
				}

				set_local_entity_int_value (get_parser_force (), INT_TYPE_FORCE_ATTITUDE, attitude);

				create_frontline (get_parser_force ());

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
					frequency_modifier;

				entity
					*regen = nullptr,
					*keysite = nullptr;

				entity_sides
					side;

				frequency_modifier = get_next_file_float (file_ptr);

				ASSERT (get_parser_force ());

				debug_log ("PARSER: %s setting regen frequency to %f, modifier %f", entity_side_names [get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)], regen_update_frequency, frequency_modifier);

				regen_frequency_modifier [get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)] = frequency_modifier;

				keysite = get_local_entity_first_child (get_parser_force (), LIST_TYPE_KEYSITE);

				side = get_local_entity_int_value (keysite, INT_TYPE_SIDE);

				while (keysite)
				{

					regen = get_local_entity_first_child (keysite, LIST_TYPE_REGEN);
	
					while (regen)
					{

						set_local_entity_float_value (regen, FLOAT_TYPE_FREQUENCY, regen_update_frequency / regen_frequency_modifier [side]);
	
						regen = get_local_entity_child_succ (regen, LIST_TYPE_REGEN);
					}

					keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE);
				}

				break;
			}

			case FILE_TAG_FRONTLINE_FORCES:
			{

				int
					value,
					group_type,
					formation_component;

				entity
					*keysite = nullptr;

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
				
								group_type = ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER;

								if (counter & 0x1)
								{

									formation_component = FORMATION_COMPONENT_HELICOPTER_SCOUT_GROUP;
								}
								else
								{

									formation_component = FORMATION_COMPONENT_HELICOPTER_RECON_GROUP;
								}
				
								create_landed_faction_group (keysite, group_type, formation_component, TRUE);

								counter ++;

								#if DEBUG_MODULE

								debug_log ("PARSER: placing FARP %s helicopters for side %s", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME), entity_side_names [get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)]);

								#endif
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

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_NAME);

				get_next_file_string (file_ptr, keysite_name, STRING_TYPE_KEYSITE_NAME_MAX_LENGTH);

				//
				// get what type of landing entities are required
				//

				required_landing_types = 0;

				while (check_next_file_tag (file_ptr) == FILE_TAG_TYPE)
				{

					int
						this_type;

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_TYPE);

					this_type = get_next_file_enum (file_ptr, entity_sub_type_landing_names, NUM_ENTITY_SUB_TYPE_LANDINGS);

					ASSERT (!(required_landing_types & 1 << this_type));

					required_landing_types |= 1 << this_type;
				}

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_AMMO_SUPPLIES);

				keysite_ammo_supplies = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_FUEL_SUPPLIES);

				keysite_fuel_supplies = get_next_file_float (file_ptr);

				#if DEBUG_MODULE

				debug_log ("PARSER: campaign load: keysite type %s, ammo %f fuel %f", entity_sub_type_keysite_names [keysite_type], keysite_ammo_supplies, keysite_fuel_supplies);

				#endif

				break;
			}

			case FILE_TAG_FLAG_PYLONS:
			{

				int
					value;

				value = get_next_file_int (file_ptr);

				if (value > 0)
				{

					//faction_place_pylons ();
				}

				#if DEBUG_MODULE

				debug_log ("PARSER: campaign load: flag pylons %d", value);

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
					*group = nullptr,
					*member = nullptr;

				member = NULL;

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_GROUP);

				group_type = get_next_file_enum (file_ptr, entity_sub_type_group_names, NUM_ENTITY_SUB_TYPE_GROUPS);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_MEMBER);

				switch (group_database [group_type].list_type)
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

				result = get_next_file_tag (file_ptr);

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

					debug_fatal ("PARSER: campaign load: Can't locate keysite %s", keysite_name);
				}

				if (check_next_file_tag (file_ptr) == FILE_TAG_MOBILE_KEYSITE)
				{

					formation_component_types
						formation_components;

					get_next_file_tag (file_ptr);

					result = get_next_file_tag (file_ptr);
	
					ASSERT (result == FILE_TAG_FORMATION_COMPONENT);
		
					formation_components = get_next_file_enum (file_ptr, formation_component_names, NUM_FORMATION_TYPES);
	
					group = create_faction_members (get_parser_keysite (), group_type, formation_components, count, get_local_entity_int_value (get_parser_keysite (), INT_TYPE_SIDE), get_local_entity_vec3d_ptr (get_parser_keysite (), VEC3D_TYPE_POSITION), TRUE, TRUE);

					ASSERT (group);

					member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

					insert_local_entity_into_parents_child_list (get_parser_keysite (), LIST_TYPE_MOVEMENT_DEPENDENT, member, NULL);
				}
				else
				{

					group = create_landed_faction_members (get_parser_keysite (), member_type, group_type, count, TRUE);
	
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
					*group = nullptr;

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_GROUP);

				group_type = get_next_file_enum (file_ptr, entity_sub_type_group_names, NUM_ENTITY_SUB_TYPE_GROUPS);

				result = get_next_file_tag (file_ptr);

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

					debug_fatal ("PARSER: campaign load: Can't locate keysite %s", keysite_name);
				}

				group = create_landed_faction_group (get_parser_keysite (), group_type, formation_component_type, TRUE);
	
				#if DEBUG_MODULE
	
				debug_log ("PARSER: campaign load: create group, keysite %d, formation component type %s, entity type %d, member type %d, count %d", get_parser_keysite (), formation_component_names [formation_component_type], member_type, count);
	
				#endif

				break;
			}

			case FILE_TAG_CREATE_TASK:
			{

				vec3d
					*wp_nodes = nullptr;

				movement_types
					movement_type;

				entity
					*wp = nullptr,
					*group_en = nullptr,
					*guide = nullptr,
					*new_task = nullptr;

				entity_sub_types
					task_type,
					*wp_types = nullptr;

				entity_sides
					side;

				float
					*wp_radius = nullptr,
					start_time,
					stop_time,
					expire_time;

				int
//					*wp_criteria,
					*wp_delta_time = nullptr,
					count,
					wp_count;

				ASSERT (get_parser_member ());

				group_en = get_local_entity_parent (get_parser_member (), LIST_TYPE_MEMBER);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_TYPE);
				task_type = get_next_file_enum (file_ptr, entity_sub_type_task_names, NUM_ENTITY_SUB_TYPE_TASKS);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_SIDE);
				side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_MOVEMENT);
				movement_type = get_next_file_enum (file_ptr, movement_names, NUM_MOVEMENT_TYPES);

				result = get_next_file_tag (file_ptr);
				//ASSERT (result == FILE_TAG_TIME);
				start_time = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr);
				//ASSERT (result == FILE_TAG_TIME);
				stop_time = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr);
				//ASSERT (result == FILE_TAG_TIME);
				expire_time = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_CREATE_WAYPOINT);

				result = get_next_file_tag (file_ptr);
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

				while ((!end_wp) && (check_next_file_tag (file_ptr) != FILE_TAG_TEXT_END))
				{

					result = get_next_file_tag (file_ptr);

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
									expire_time,
									group_en,
									10.0,
									&wp_nodes [0], NULL, wp_types [0], FORMATION_5_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

				count = 0;

				wp = NULL;

				while (count <= wp_count)
				{
/*
					if (wp_criteria [count] == 0)
					{

						wp_criteria [count] = WAYPOINT_CRITERIA_MIN_RADIUS;
					}
*/				
					wp = create_local_entity
					(
						ENTITY_TYPE_WAYPOINT,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT (LIST_TYPE_WAYPOINT, new_task),
						ENTITY_ATTR_CHILD_PRED (LIST_TYPE_WAYPOINT, wp),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, wp_types [count]),
//						ENTITY_ATTR_INT_VALUE (INT_TYPE_WAYPOINT_CRITERIA, wp_criteria [count]),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_WAYPOINT_FORMATION, FORMATION_5_ROW_LEFT),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_POSITION_TYPE, POSITION_TYPE_ABSOLUTE),
//						ENTITY_ATTR_INT_VALUE (INT_TYPE_TERRAIN_CHECK, TRUE),
//						ENTITY_ATTR_INT_VALUE (INT_TYPE_DELTA_TIME, wp_delta_time [count]),
//						ENTITY_ATTR_INT_VALUE (INT_TYPE_TIMER, wp_delta_time [count]),
						ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, wp_nodes [count].x, wp_nodes [count].y, wp_nodes [count].z),
						ENTITY_ATTR_PTR_VALUE (PTR_TYPE_POSITION_ENTITY, NULL),
//						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_RADIUS, wp_radius [count]),
//						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_VELOCITY, waypoint_database [wp_types [count]].hc_velocity),
						ENTITY_ATTR_END
					);
				
			  		count ++;
				}

				//
				// Assign task
				//

				guide = push_task_onto_group_task_stack (group_en, new_task, TASK_ASSIGN_ALL_MEMBERS);
		
				assign_task_to_group_members (group_en, guide, TASK_ASSIGN_ALL_MEMBERS);

				break;
			}

			case FILE_TAG_SAVED_CAMPAIGN:
			{

				int
					server_version_number,
					client_version_number,
					campaign_size;

				FILE
					*saved_file_ptr = nullptr;

				char
					*load_ptr = nullptr,
					*campaign_buffer = nullptr,
					filename [128];

//				comms_model_types
//					comms_model;

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_PATH);

				get_next_file_string (file_ptr, current_session->data_path, sizeof (current_session->data_path));

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_FILENAME);

				get_next_file_string (file_ptr, filename, sizeof (filename));

				sprintf (temp_filename, "%s\\%s", current_session->data_path, filename);

				saved_file_ptr = safe_fopen (temp_filename, "rb");

				campaign_size = file_size (temp_filename);

				campaign_buffer = (char *) malloc_heap_mem (sizeof (char) * (campaign_size + 1));

				load_ptr = campaign_buffer;

				fread (campaign_buffer, campaign_size + 1, 1, saved_file_ptr);

				//
				// set into client mode for unpacking
				//

//				comms_model = get_comms_model ();
//				set_comms_model (COMMS_MODEL_CLIENT);

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

//				set_comms_model (comms_model);

				//
				//
				//

				fclose (saved_file_ptr);

				free_mem (campaign_buffer);

				break;
			}

			case FILE_TAG_SHORT_TEXT_START:
			case FILE_TAG_LONG_TEXT_START:
			case FILE_TAG_TEXT_END:
			{

				break;
			}

			case FILE_TAG_END:
			{

				fclose (file_ptr);

				return;
			}

			default:
			{

				debug_log ("PARSER: campaign load: unknown campaign tag %d (string %s)", tag, tag_strings [tag]);
			}
		}
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_campaign_object_population_data (char *filename)
{
	#if 0

	FILE
		*file_ptr = nullptr;

	file_tags
		tag;

	entity
		*keysite = nullptr,
		*building = nullptr,
		*landing = nullptr,
		*route = nullptr;

	int
		value,
		result;

	char
		variable [64],
		operator [64];

	file_ptr = safe_fopen (filename, "r");

	while (TRUE)
	{

		tag = get_next_file_tag (file_ptr);

		switch (tag)
		{

			case FILE_TAG_IF:
			{

				ASSERT (get_current_player_log ());

				get_next_file_word (file_ptr, variable, sizeof (variable));

				get_next_file_word (file_ptr, operator, sizeof (operator));

				value = get_next_file_int (file_ptr);

				if (!if_file_tag_variable (variable, operator, value))
				{

					// skip script till endif

					while (tag = get_next_file_tag (file_ptr))
					{

						if ((tag == FILE_TAG_ENDIF) || (tag == FILE_TAG_END))
						{

							break;
						}
					}
				}

				break;
			}

			case FILE_TAG_ENDIF:
			{

				break;
			}

			case FILE_TAG_BUILDING:
			{

				vec3d
					*keysite_pos = nullptr;

				entity
					*keysite_group = nullptr;

				int
					side,
					type,
					object_number;

				float
					scaling,
					heading;

				vec3d
					position;

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_TYPE);

				type = get_next_file_enum (file_ptr, entity_type_names, NUM_ENTITY_TYPES);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_OBJECT_NUMBER);

				object_number = get_next_file_enum (file_ptr, object_3d_enumeration_names, OBJECT_3D_LAST);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_HEADING);

				heading = get_next_file_float (file_ptr);

				heading = rad (heading);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_POSITION);

				position.x = get_next_file_float (file_ptr);

				position.y = get_next_file_float (file_ptr);

				position.z = get_next_file_float (file_ptr);

				if (check_next_file_tag (file_ptr) == FILE_TAG_RADIUS)
				{
	
					result = get_next_file_tag (file_ptr);
	
					ASSERT (result == FILE_TAG_RADIUS);
	
					scaling = get_next_file_float (file_ptr);
				}

				if (get_parser_keysite ())
				{

					keysite_group = get_local_entity_first_child (get_parser_keysite (), LIST_TYPE_BUILDING_GROUP);

					ASSERT (keysite_group);

					keysite_pos = get_local_entity_vec3d_ptr (get_parser_keysite (), VEC3D_TYPE_POSITION);

					position.x += keysite_pos->x;

					position.y += keysite_pos->y;

					position.z += keysite_pos->z;

					position.y = get_3d_terrain_elevation (position.x, position.z);

					side = get_local_entity_int_value (get_parser_keysite (), INT_TYPE_SIDE);

					building = create_local_entity
					(
						ENTITY_TYPE_SITE,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT (LIST_TYPE_MEMBER, keysite_group),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, object_number),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
						ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position.x, position.y, position.z),
						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, heading),
						ENTITY_ATTR_END
					);
				}
				else
				{

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_SIDE);

					side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);

					building = create_local_entity
					(
						ENTITY_TYPE_SCENIC,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, object_number),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
						ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position.x, position.y, position.z),
						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, heading),
						ENTITY_ATTR_END
					);
				}

				set_parser_object (building);

				result = check_next_file_tag (file_ptr);

				if (result == FILE_TAG_REGEN)
				{

					entity
						*wp = nullptr,
						*regen = nullptr,
						*landing = nullptr,
						*closest_wp = nullptr;

					entity_sub_types
						sub_type;

					float
						timer,
						wp_range,
						closest_wp_range;

					get_next_file_tag (file_ptr);

					sub_type = get_next_file_enum (file_ptr, entity_sub_type_regen_names, NUM_ENTITY_SUB_TYPE_REGENS);

					//
					// find closest waypoint
					//

					landing = get_local_entity_landing_entity (get_parser_keysite (), regen_to_landing_conversion [sub_type]);

					wp = get_local_landing_entity_route (landing, ENTITY_SUB_TYPE_TASK_LANDING);

					closest_wp = NULL;

					closest_wp_range = 10000000;

					while (wp)
					{

						wp_range = get_approx_3d_range (get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION), &position);

						if (wp_range < closest_wp_range)
						{

							closest_wp_range = wp_range;

							closest_wp = wp;
						}

						wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
					}

					//
					//
					//

					result = get_next_file_tag (file_ptr);

					//ASSERT (result == FILE_TAG_TIME);

					timer = get_next_file_float (file_ptr);

					//
					// Create regen
					//

					regen = create_local_entity
					(
						ENTITY_TYPE_REGEN,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT (LIST_TYPE_REGEN, get_parser_force ()),
						ENTITY_ATTR_PARENT (LIST_TYPE_CURRENT_WAYPOINT, closest_wp),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_ALIVE, TRUE),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)),
						ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position.x, position.y, position.z),
						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FREQUENCY, timer),
						ENTITY_ATTR_END
					);

					//
					// move building from keysite group into regen group
					//

					delete_local_entity_from_parents_child_list (building, LIST_TYPE_MEMBER);

					insert_local_entity_into_parents_child_list (building, LIST_TYPE_MEMBER, regen, NULL);
				}

				#if DEBUG_MODULE

				debug_log ("PARSER: load keysite database: create building %d at %f, %f, %f", object_number, position.x, position.y, position.z);

				#endif

				break;
			}

			case FILE_TAG_SCENIC_OBJECT:
			{

				int
					object_number;

				float
					heading;

				vec3d
					scaling,
					position;

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_OBJECT_NUMBER);
				object_number = get_next_file_enum (file_ptr, object_3d_enumeration_names, OBJECT_3D_LAST);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_HEADING);
				heading = get_next_file_float (file_ptr);
				heading = rad (heading);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_POSITION);
				position.x = get_next_file_float (file_ptr);
				position.y = get_next_file_float (file_ptr);
				position.z = get_next_file_float (file_ptr);

				result = get_next_file_tag (file_ptr);
				ASSERT (result == FILE_TAG_OBJECT_SCALING);
				scaling.x = get_next_file_float (file_ptr);
				scaling.y = get_next_file_float (file_ptr);
				scaling.z = get_next_file_float (file_ptr);

				create_local_entity
				(
					ENTITY_TYPE_OBJECT,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_SCENIC_OBJECT),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, object_number),
					ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position.x, position.y, position.z),
					ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, heading),
					ENTITY_ATTR_VEC3D (VEC3D_TYPE_OBJECT_SCALING, scaling.x, scaling.y, scaling.z),
					ENTITY_ATTR_END
				);

				#if DEBUG_MODULE

				debug_log ("PARSER: create scenic %s at %f, %f, %f", object_3d_enumeration_names [object_number], position.x, position.y, position.z);

				#endif

				break;
			}

			case FILE_TAG_TERRAIN_OBJECT:
			{

				object_3d_instance
					*inst3d = nullptr;

				int
					type,
					object_number;

				float
					heading;

				vec3d
					position;

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_TYPE);

				type = get_next_file_enum (file_ptr, entity_type_names, NUM_ENTITY_TYPES);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_OBJECT_NUMBER);

				object_number = get_next_file_enum (file_ptr, object_3d_enumeration_names, OBJECT_3D_LAST);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_HEADING);

				heading = get_next_file_float (file_ptr);

				heading = rad (heading);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_POSITION);

				position.x = get_next_file_float (file_ptr);

				position.y = get_next_file_float (file_ptr);

				position.z = get_next_file_float (file_ptr);

				inst3d = construct_3d_object (object_number);

				inst3d->vp.position = position;

				inst3d->object_has_shadow = FALSE;

				get_3d_transformation_matrix (inst3d->vp.attitude, heading, 0.0, 0.0);

				insert_3d_object_into_terrain (inst3d);

#ifdef OGRE_EE
				destruct_3d_object (inst3d);
#endif

				#if DEBUG_MODULE

				debug_log ("PARSER: load keysite database: insert terrain object %d at %f, %f, %f", object_number, position.x, position.y, position.z);

				#endif

				break;
			}

			case FILE_TAG_KEYSITE:
			{

				vec3d
					keysite_position;

				char
					name [STRING_TYPE_KEYSITE_NAME_MAX_LENGTH];

				int
					type,
					side;

				type = get_next_file_enum (file_ptr, entity_sub_type_keysite_names, NUM_ENTITY_SUB_TYPE_KEYSITES);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_NAME);

				get_next_file_string (file_ptr, name, STRING_TYPE_KEYSITE_NAME_MAX_LENGTH);

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_SIDE);

				side = get_next_file_enum (file_ptr, entity_side_names, NUM_ENTITY_SIDES);

				//
				// find force
				//

				set_parser_force (get_local_force_entity (side));

				//
				// read in keysite
				//

				ASSERT (get_parser_force ());

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_POSITION);

				keysite_position.x = get_next_file_float (file_ptr);

				keysite_position.y = get_next_file_float (file_ptr);

				keysite_position.z = get_next_file_float (file_ptr);

				keysite_position.y = get_3d_terrain_elevation (keysite_position.x, keysite_position.z);

				keysite = create_local_entity
				(
					ENTITY_TYPE_KEYSITE,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_PARENT (LIST_TYPE_KEYSITE_FORCE, get_parser_force ()),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, type),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, get_local_entity_int_value (get_parser_force (), INT_TYPE_SIDE)),
					ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, keysite_position.x, keysite_position.y, keysite_position.z),
					ENTITY_ATTR_STRING (STRING_TYPE_KEYSITE_NAME, name),
					ENTITY_ATTR_END
				);

				set_parser_keysite (keysite);

				#if DEBUG_MODULE

				debug_log ("PARSER: load keysite database: create keysite %s (%d) at %f, %f, %f", name, type, keysite_position.x, keysite_position.y, keysite_position.z);

				#endif

				break;
			}

			case FILE_TAG_KEYSITE_END:
			{

				set_parser_keysite (NULL);

				break;
			}

			case FILE_TAG_TRAFFIC_ROUTE:
			{

				vec3d
					*keysite_pos = nullptr;

				char
					filename [512],
					temp_filename [128];

				int
					type,
					landing_types,
					total_landing_sites;

				if (!get_parser_keysite ())
				{

					break;
				}

				ASSERT (get_valid_current_game_session ());

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_TYPE);

				type = get_next_file_enum (file_ptr, entity_sub_type_landing_names, NUM_ENTITY_SUB_TYPE_LANDINGS);

				result = get_next_file_tag (file_ptr);

				ASSERT (result  == FILE_TAG_COUNT);

				total_landing_sites = get_next_file_int (file_ptr);

				result = get_next_file_tag (file_ptr);

				ASSERT (result  == FILE_TAG_FILENAME);

				get_next_file_string (file_ptr, temp_filename, sizeof (temp_filename));

				sprintf (filename, "%s\\route\\%s", current_game_session->data_path, temp_filename);

				keysite_pos = get_local_entity_vec3d_ptr (get_parser_keysite (), VEC3D_TYPE_POSITION);

				landing = create_local_entity
				(
					ENTITY_TYPE_LANDING,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_PARENT (LIST_TYPE_LANDING_SITE, get_parser_keysite ()),
					ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, keysite_pos->x, keysite_pos->y, keysite_pos->z),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, type),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_TOTAL_LANDING_SITES, total_landing_sites),
					ENTITY_ATTR_END
				);

				set_parser_landing (landing);

				//
				// set keysite landing types bitfield
				//

				landing_types = get_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES);

				ASSERT (!(landing_types & 1 << type));

				landing_types |= 1 << type;

				set_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES, landing_types);

				load_campaign_object_population_data (filename);

				#if DEBUG_MODULE

				debug_log ("PARSER: load keysite database: create traffic route %d", type);

				#endif

				break;
			}

			case FILE_TAG_ROUTE:
			{

				int
					type,
					count,
//					criteria,
					formation,
					last_type,
					last_formation;
					//this_criteria;

				float
					velocity,
					radius;

				vec3d
					*landing_pos = nullptr,
					position;

				entity
					*wp = nullptr;

				if (!get_parser_landing ())
				{

					break;
				}

				ASSERT (get_parser_keysite ());

				formation = FORMATION_NONE;

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_TYPE);

				type = get_next_file_enum (file_ptr, entity_sub_type_task_names, NUM_ENTITY_SUB_TYPE_TASKS);

				route = get_local_landing_entity_task (get_parser_landing (), type);

				set_parser_route (route);

				ASSERT (get_parser_route ());

				result = get_next_file_tag (file_ptr);

				ASSERT (result == FILE_TAG_COUNT);

				count = get_next_file_int (file_ptr);

				while (count)
				{

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_TYPE);

					last_type = type;

					type = get_next_file_enum (file_ptr, entity_sub_type_waypoint_names, NUM_ENTITY_SUB_TYPE_WAYPOINTS);

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_FORMATION);

					last_formation = formation;

					formation = get_next_file_enum (file_ptr, formation_names, NUM_FORMATION_TYPES);

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_POSITION);

					position.x = get_next_file_float (file_ptr);

					position.y = get_next_file_float (file_ptr);

					position.z = get_next_file_float (file_ptr);

					landing_pos = get_local_entity_vec3d_ptr (get_parser_landing (), VEC3D_TYPE_POSITION);

					// adjust relative coords into world coords

					position.x += landing_pos->x;
					position.y += landing_pos->y;
					position.z += landing_pos->z;

					// debug code while ground isn't flattened.
					position.y = bound (position.y, get_3d_terrain_elevation (position.x, position.z), MAX_MAP_Y);
					// end
/*
					criteria = WAYPOINT_CRITERIA_NONE;

					while (check_next_file_tag (file_ptr) == FILE_TAG_CRITERIA)
					{

						result = get_next_file_tag (file_ptr);

						ASSERT (result == FILE_TAG_CRITERIA);

						this_criteria = get_next_file_enum (file_ptr, waypoint_criteria_names, NUM_WAYPOINT_CRITERIA_TYPES);

						if (this_criteria != WAYPOINT_CRITERIA_NONE)
						{

							criteria |= 1 << (this_criteria - 1);
						}
					}
*/
					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_VELOCITY);

					velocity = get_next_file_float (file_ptr);

					result = get_next_file_tag (file_ptr);

					ASSERT (result == FILE_TAG_RADIUS);

					radius = get_next_file_float (file_ptr);

					wp = create_local_entity
					(
						ENTITY_TYPE_WAYPOINT,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT (LIST_TYPE_WAYPOINT, get_parser_route ()),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, type),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_WAYPOINT_FORMATION, formation),
//						ENTITY_ATTR_INT_VALUE (INT_TYPE_WAYPOINT_CRITERIA, criteria),
						ENTITY_ATTR_INT_VALUE (INT_TYPE_POSITION_TYPE, POSITION_TYPE_RELATIVE),
//						ENTITY_ATTR_INT_VALUE (INT_TYPE_TERRAIN_CHECK, FALSE),
//						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_VELOCITY, velocity),
//						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_RADIUS, radius),
						ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position.x, position.y, position.z),
						ENTITY_ATTR_PTR_VALUE (PTR_TYPE_POSITION_ENTITY, NULL),
						ENTITY_ATTR_END
					);

					switch (get_local_entity_int_value (get_parser_landing (), INT_TYPE_ENTITY_SUB_TYPE))
					{

						case ENTITY_SUB_TYPE_LANDING_FIXED_WING:
						{

							switch (get_local_entity_int_value (get_parser_route (), INT_TYPE_ENTITY_SUB_TYPE))
							{

								case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
								case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
								{

//									set_local_entity_int_value (wp, INT_TYPE_TERRAIN_CHECK, TRUE);
								}
							}

							break;
						}

						case ENTITY_SUB_TYPE_LANDING_HELICOPTER:
						{

							switch (get_local_entity_int_value (get_parser_route (), INT_TYPE_ENTITY_SUB_TYPE))
							{

								case ENTITY_SUB_TYPE_TASK_LANDING:
								{

									// last wp only
									if (count == 1)
									{

//										set_local_entity_int_value (wp, INT_TYPE_TERRAIN_CHECK, TRUE);
									}

									break;
								}

								case ENTITY_SUB_TYPE_TASK_TAKEOFF:
								{

									// 1st wp only
									if (!get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
									{

//										set_local_entity_int_value (wp, INT_TYPE_TERRAIN_CHECK, TRUE);
									}

									break;
								}

								case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
								case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
								{

//									set_local_entity_int_value (wp, INT_TYPE_TERRAIN_CHECK, TRUE);

									break;
								}
							}

							break;
						}

						case ENTITY_SUB_TYPE_LANDING_GROUND:
						{

//							set_local_entity_int_value (wp, INT_TYPE_TERRAIN_CHECK, TRUE);

							break;
						}

						case ENTITY_SUB_TYPE_LANDING_SEA:
						{

//							set_local_entity_int_value (wp, INT_TYPE_TERRAIN_CHECK, TRUE);

							break;
						}
					}

					#if DEBUG_MODULE

					debug_log ("PARSER: load keysite %s %s database: create %s route waypoint %s at %f, %f, %f",
									entity_sub_type_keysite_names [get_local_entity_int_value (get_parser_keysite (), INT_TYPE_ENTITY_SUB_TYPE)],
									get_local_entity_string (get_parser_keysite (), STRING_TYPE_KEYSITE_NAME),
									movement_names [waypoint_database [type].movement_type],
									entity_sub_type_waypoint_names [type],
									position.x, position.y, position.z);

					#endif

					count --;
				}

				validate_landing_route (get_parser_route ());

				break;
			}

			case FILE_TAG_END:
			{

				//
				// Campaign loaded and session entity created.
				//

				fclose (file_ptr);

				return;
			}
		}
	}
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
