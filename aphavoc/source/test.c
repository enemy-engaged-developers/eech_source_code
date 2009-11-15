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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE												0

#define DEBUG_MODULE_TERRAIN_ELEVATION_SOAK_TEST		0

#define DEBUG_MODULE_CHECK_ENTITIES_IN_CORRECT_SECTOR	0

#define DEBUG_AIR_MEDAL											0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ai/taskgen/taskgen.h"
#include "ai/ai_misc/ai_misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_CPU_COUNT_HISTORY	100

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double
	cpu_count_av = 0.0,
	cpu_count_av_percent = 0.0,
	cpu_count_max = 0.0;

int
	in_flight_articulation_test = 0,
	in_flight_zoom_test = 0,
	in_flight_debug_misc_info = 0,
	in_flight_debug_pilot_info = 0,
	in_flight_debug_keysite_info = 0,
	in_flight_debug_force_info = 0,
	in_flight_external_view_entity_debug_flight_info = 0,
	in_flight_external_view_entity_debug_task_info = 0,
	in_flight_external_view_entity_weapon_info = 0,
	in_flight_external_view_entity_guide_info = 0,
	in_flight_invisible_object = 0,
	in_flight_gunship_target_list_info = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_flight_test (void)
{
	check_memory_block_system_integrity ();

	if (command_line_dump_session)
	{
		debug_log_entity_session (get_session_entity (), "ENTRY SESSION DATA");
	}

	#if DEBUG_MODULE_TERRAIN_ELEVATION_SOAK_TEST

	terrain_elevation_soak_test (10);

	#endif

	debug_watch ("Test CPU clock count av		= %f (ticks / sec)", MT_DOUBLE, &cpu_count_av);

	debug_watch ("Test CPU clock count av%		= %f%% (ticks / sec)", MT_DOUBLE, &cpu_count_av_percent);

	debug_watch ("Test CPU clock count max		= %f (ticks / sec)", MT_DOUBLE, &cpu_count_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void in_flight_test (void)
{
	#if DEBUG_MODULE_CHECK_ENTITIES_IN_CORRECT_SECTOR

	validate_local_sector_entities ();

	#endif

/*
	if (check_key (DIK_LSHIFT))
	{

		int
			count;

		entity_types
			kill_type;

		entity
			*en;

		kill_type = 0;

		if (check_key (DIK_1))
		{

			kill_type = ENTITY_TYPE_ROUTED_VEHICLE;
		}
		else if (check_key (DIK_2))
		{

			kill_type = ENTITY_TYPE_SHIP_VEHICLE;
		}
		else if (check_key (DIK_3))
		{

			kill_type = ENTITY_TYPE_HELICOPTER;
		}
		else if (check_key (DIK_4))
		{

			kill_type = ENTITY_TYPE_FIXED_WING;
		}
		else if (check_key (DIK_5))
		{

			kill_type = ENTITY_TYPE_ANTI_AIRCRAFT;
		}
		else if (check_key (DIK_6))
		{

			kill_type = ENTITY_TYPE_CARGO;
		}
		else if (check_key (DIK_7))
		{

			kill_type = ENTITY_TYPE_CITY_BUILDING;
		}
		else if (check_key (DIK_8))
		{

			kill_type = ENTITY_TYPE_PYLON;
		}
		else if (check_key (DIK_9))
		{

			kill_type = ENTITY_TYPE_SITE_UPDATABLE;
		}
		else if (check_key (DIK_F1))
		{

			kill_type = ENTITY_TYPE_SCENIC;
		}
		else if (check_key (DIK_F2))
		{

			kill_type = ENTITY_TYPE_TASK;
		}
		else if (check_key (DIK_F3))
		{

			kill_type = ENTITY_TYPE_SEGMENT;
		}

		if (kill_type != 0)
		{

			count = 0;

			debug_log ("TEST: STARTED KILLING ALL...................................");

			en = get_local_entity_list ();

			while (en)
			{

				if (get_local_entity_type (en) == kill_type)
				{

					if (count & 1)
					{

						kill_local_entity (en);
					}

					count ++;
				}

				en = get_local_entity_succ (en);
			}

			debug_log ("TEST: FINISHED KILLING ALL...................................");
		}
	}
*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void post_flight_test (void)
{
	if (command_line_dump_session)
	{
		debug_log_entity_session (get_session_entity (), "EXIT SESSION DATA");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float display_in_flight_debug_misc_info (float y)
{
	char
		s[200];

	float
		y_add_on;

	if (in_flight_debug_misc_info)
	{
		set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

		if (lock_screen (active_screen))
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_colour (hud_colour);

			y_add_on = get_mono_font_char_height ('0');

			////////////////////////////////////////
			//
			// miscellaneous info
			//
			////////////////////////////////////////
			{
				set_mono_font_position (0.0, y);

				sprintf (s, "%-20.20s: %.2f", "Frame rate", get_one_over_delta_time ());

				print_mono_font_string (s);

				y += y_add_on;
			}
			////////////////////////////////////////
			//
			// session info
			//
			////////////////////////////////////////
			{
				if (get_session_entity ())
				{
					set_mono_font_position (0.0, y);

					sprintf (s, "%-20.20s: %d", "Infinite weapons", get_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_WEAPONS));

					print_mono_font_string (s);

					y += y_add_on;

					set_mono_font_position (0.0, y);

					sprintf (s, "%-20.20s: %d", "Infinite fuel", get_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_FUEL));

					print_mono_font_string (s);

					y += y_add_on;

					set_mono_font_position (0.0, y);

					sprintf (s, "%-20.20s: %d", "Suppress AI fire", get_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE));

					print_mono_font_string (s);

					y += y_add_on;

					if (!get_gunship_entity ())
					{
						set_mono_font_position (0.0, y);

						sprintf (s, "%-20.20s: %d", "Invulnerable from Collisions", get_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS));

						print_mono_font_string (s);

						y += y_add_on;

						set_mono_font_position (0.0, y);

						sprintf (s, "%-20.20s: %d", "Invulnerable from Weapons", get_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_WEAPONS));

						print_mono_font_string (s);

						y += y_add_on;
					}
					else
					{

						set_mono_font_position (0.0, y);

						sprintf (s, "%-20.20s: %d", "Invulnerable from Collisions", get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS));

						print_mono_font_string (s);

						y += y_add_on;

						set_mono_font_position (0.0, y);

						sprintf (s, "%-20.20s: %d", "Invulnerable from Weapons", get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INVULNERABLE_FROM_WEAPONS));

						print_mono_font_string (s);

						y += y_add_on;
					}

					set_mono_font_position (0.0, y);

					sprintf (s, "%-20.20s: %d", "AI Invulnerable", get_damage_debug_invulnerable_flag ());

					print_mono_font_string (s);

					y += y_add_on;

					//
					// wind
					//
					{
						vec3d
							*camera_pos,
							wind_velocity;

						float
							wind_speed,
							wind_heading;

						if (in_cockpit)
						{
							camera_pos = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);
						}
						else
						{
							camera_pos = get_local_entity_vec3d_ptr (get_camera_entity (), VEC3D_TYPE_POSITION);
						}

						get_session_wind_velocity_at_point (camera_pos, &wind_velocity);

						wind_speed = get_3d_vector_magnitude (&wind_velocity);

						wind_heading = atan2 (wind_velocity.x, wind_velocity.z);

						wind_heading += PI;		// For the "Aviators" out there

						set_mono_font_position (0.0, y);

						sprintf (s, "%-20.20s: %.2f kts, Heading %.2f", "Wind", metres_per_second_to_knots (wind_speed), deg (wind_heading));

						print_mono_font_string (s);

						y += y_add_on;
					}
				}
			}
			////////////////////////////////////////
			//
			// camera info
			//
			////////////////////////////////////////
			{
				entity
					*en;

				camera
					*raw;

				set_mono_font_position (0.0, y);

				en = get_camera_entity ();

				if (en)
				{
					raw = ( camera * ) get_local_entity_data (en);

					if (get_view_mode () == VIEW_MODE_EXTERNAL)
					{
						sprintf
						(
							s,
							"%-20.20s: %s (auto=%d, index=%d, interest=%.2f)",
							"Camera mode",
							camera_mode_names[raw->camera_mode],
							raw->auto_edit,
							get_local_entity_index (get_external_view_entity ()),
							get_local_entity_float_value (get_external_view_entity (), FLOAT_TYPE_VIEW_INTEREST_LEVEL)
						);

						print_mono_font_string (s);

						y += y_add_on;

						set_mono_font_position (0.0, y);

						sprintf
						(
							s,
							"%-20.20s: (h = %.2f, p = %.2f, r = %.2f)",
							"Camera attitude",
							deg (get_heading_from_attitude_matrix (raw->attitude)),
							deg (get_pitch_from_attitude_matrix (raw->attitude)),
							deg (get_roll_from_attitude_matrix (raw->attitude))
						);

						print_mono_font_string (s);

						y += y_add_on;
					}
				}
			}
			////////////////////////////////////////
			//
			// CP/G assistance
			//
			////////////////////////////////////////
			{
				set_mono_font_position (0.0, y);

				switch (get_global_cpg_assist_type ())
				{
					case CPG_ASSIST_TYPE_NONE:
					{
						sprintf (s, "%-20.20s: CPG_ASSIST_TYPE_NONE", "CP/G Assistance");

						break;
					}
					case CPG_ASSIST_TYPE_EASY:
					{
						sprintf (s, "%-20.20s: CPG_ASSIST_TYPE_EASY", "CP/G Assistance");

						break;
					}
					case CPG_ASSIST_TYPE_REAL:
					{
						sprintf (s, "%-20.20s: CPG_ASSIST_TYPE_REAL", "CP/G Assistance");

						break;
					}
					default:
					{
						debug_fatal ("Invalid cpg assist type = %d", get_global_cpg_assist_type ());

						break;
					}
				}

				print_mono_font_string (s);

				y += y_add_on;
			}
			////////////////////////////////////////
			//
			// crew role
			//
			////////////////////////////////////////
			{
				set_mono_font_position (0.0, y);

				if (get_pilot_entity ())
				{
					switch (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE))
					{
						case CREW_ROLE_PILOT:
						{
							sprintf (s, "%-20.20s: CREW_ROLE_PILOT", "Crew role");

							break;
						}
						case CREW_ROLE_CO_PILOT:
						{
							sprintf (s, "%-20.20s: CREW_ROLE_CO_PILOT", "Crew role");

							break;
						}
						default:
						{
							debug_fatal ("Invalid crew role = %d", get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE));

							break;
						}
					}
				}
				else
				{
					sprintf (s, "%-20.20s: No pilot entity", "Crew role");
				}

				print_mono_font_string (s);

				y += y_add_on;
			}

			#if DEBUG_AIR_MEDAL
			{
				player_log_type
					*player;

				int
					side,
					counter,
					medal_count,
					*medals;

				player = get_current_player_log ();

				side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

				medals = player->side_log[side].medals;

				counter = player->side_log[side].air_medal_counter;

				medal_count = *(medals + MEDAL_AIR_MEDAL);

				set_mono_font_position (0.0, y);

				sprintf (s, "Number Of Air Medals: %d, Mission Counter: %d", medal_count, counter);

				print_mono_font_string (s);

				y += y_add_on;
			}
			#endif

			unlock_screen (active_screen);
		}
	}

	return (y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
static float display_in_flight_debug_demo_message (float y)
{

	int
		last_event_time;

	camera
		*camera_raw;

	switch (get_game_type ())
	{

		case GAME_TYPE_DEMO:
		{

			screen
				*old_screen;

			old_screen = get_active_screen ();

			set_active_screen ( video_screen );

			if ( lock_screen ( active_screen ) )
			{

				//float
					//x,
					//y;

				set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

				set_ui_font (UI_FONT_ADS_15_WHITE);

				////////////////////////////////////////

				//x = (get_screen_width (active_screen) - ui_get_string_length ("Copyright Razorworks Ltd 1998. Press ESCAPE to exit demo")) / 2.0;
				//y = 5;
				//ui_display_text ("Copyright Razorworks Ltd 1998. Press ESCAPE to exit demo", x, y);

				unlock_screen ( active_screen );
			}

			if ( old_screen )
			{

				set_active_screen ( old_screen );
			}

			break;
		}

		default:
		{
			if (get_camera_entity ())
			{

				camera_raw = get_local_entity_data (get_camera_entity ());

				if ((get_view_mode () != VIEW_MODE_EXTERNAL) || (!camera_raw->auto_edit))
				{

					last_event_time = min ((get_system_time () - get_last_key_event_time ()), (get_system_time () - get_last_mouse_event_time ()));

					last_event_time = min (last_event_time, (get_system_time () - get_last_joystick_event_time ()));

					if (last_event_time > TIME_1_HOUR)
					{
						set_local_weather_mode_state (TRUE);

						notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_AUTO_EDIT);
					}
				}
			}

			break;
		}
	}

	return (y);
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float display_in_flight_debug_keysite_info (float y)
{

	#ifdef DEBUG

	entity
		*member;

	char
		s [200];

	float
		y_add_on;

	if (in_flight_debug_keysite_info)
	{

		set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

		if (!lock_screen (active_screen))
		{

			return y;
		}

		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_mono_font_colour (hud_colour);

		////////////////////////////////////////

		y_add_on = get_mono_font_char_height ('0');

		member = get_external_view_entity ();

		if (member)
		{

			entity
				*group,
				*keysite,
				*landing;

			debug_landing_lock_type
				*item;

			group = get_local_entity_parent (member, LIST_TYPE_MEMBER);

			if (group)
			{

				keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

				if ((!keysite) || (get_local_entity_type (keysite) != ENTITY_TYPE_KEYSITE))
				{
					return y;
				}

				set_mono_font_position (0.0, y);
				sprintf (s, "Keysite %s (%d) data", get_local_entity_string (keysite, STRING_TYPE_FULL_NAME), get_local_entity_index (keysite));
				print_mono_font_string (s);
				y += y_add_on;

				landing = get_local_entity_first_child (keysite, LIST_TYPE_LANDING_SITE);

				while (landing)
				{

					if (in_flight_debug_keysite_info - 1 == get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE))
					{

						set_mono_font_position (0.0, y);
						sprintf (s, "Landing %s (%d) data", entity_sub_type_landing_names [get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE)], get_local_entity_index (landing));
						print_mono_font_string (s);
						y+= y_add_on;

						set_mono_font_position (0.0, y);
						sprintf (s, "  Locks: Reserved %d, landed %d, landing %d, takeoff %d",
										get_local_entity_int_value (landing, INT_TYPE_RESERVED_LANDING_SITES),
										get_local_entity_int_value (landing, INT_TYPE_LANDED_LOCK),
										get_local_entity_int_value (landing, INT_TYPE_LANDING_LOCK),
										get_local_entity_int_value (landing, INT_TYPE_TAKEOFF_LOCK));
						print_mono_font_string (s);
						y += y_add_on;

						// reserved list

						item = debug_landing_lock_list;

						while (item)
						{

							if (item->landing_en == landing)
							{

								set_mono_font_position (0.0, y);
								sprintf (s, "  %s (%d) has locks [Res %d, lnd %d, lnding %d, toff %d (Q %d)]",
											get_local_entity_string (item->en, STRING_TYPE_FULL_NAME),
											get_local_entity_index (item->en),
											item->locks [DEBUG_LANDING_LOCK_RESERVE_LOCK],
											item->locks [DEBUG_LANDING_LOCK_LANDING_SITE_LOCK],
											item->locks [DEBUG_LANDING_LOCK_LANDING_ROUTE_LOCK],
											item->locks [DEBUG_LANDING_LOCK_TAKEOFF_ROUTE_LOCK],
											(get_local_entity_parent (item->en, LIST_TYPE_TAKEOFF_QUEUE) ? 1 : 0));
								print_mono_font_string (s);
								y += y_add_on;
							}

							item = item->next;
						}
					}

					landing = get_local_entity_child_succ (landing, LIST_TYPE_LANDING_SITE);
				}
			}
		}

		unlock_screen (active_screen);
	}

	#endif

	return y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float display_in_flight_debug_force_info (float y)
{

	entity
		*keysite_en,
		*force_en;

	force
		*force_raw;

	session
		*session_raw;

	char
		s [200];

	int
		supply_keysite_count,
		total_hardware [NUM_FORCE_INFO_CATAGORIES],
		loop;

	float
		elapsed_hours,
		elapsed_minutes,
		elapsed_seconds,
		supply_ammo,
		supply_fuel;

	if (in_flight_debug_force_info)
	{

		set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

		if (!lock_screen (active_screen))
		{

			return y;
		}

		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_mono_font_colour (hud_colour);

		////////////////////////////////////////

		set_mono_font_position (0.0, y);

		session_raw = ( session * ) get_local_entity_data (get_session_entity ());

		get_digital_clock_values (session_raw->elapsed_time, &elapsed_hours, &elapsed_minutes, &elapsed_seconds);

		sprintf (s, "Elapsed %d days %.0f Hrs %.0f Mins %.0f Secs",
					(int)(session_raw->elapsed_time / ONE_DAY),
					elapsed_hours,
					elapsed_minutes,
					elapsed_seconds);

		print_mono_font_string (s);

		force_en = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

		memset (&total_hardware, 0, sizeof (total_hardware));

		while (force_en)
		{

			force_raw = ( force * ) get_local_entity_data (force_en);

			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);
			sprintf (s, "side %s, attitude %s", entity_side_names [force_raw->side], entity_force_attitude_names [force_raw->force_attitude]);
			print_mono_font_string (s);

		  	for (loop = 0; loop < NUM_FORCE_INFO_CATAGORIES; loop ++)
			{

				total_hardware [loop] += force_raw->force_info_current_hardware [loop];

				y += get_mono_font_char_height ('X');
				set_mono_font_position (0.0, y);

				sprintf (s, "     %s = cur %d, res %d",
							force_info_catagory_names [loop],
							force_raw->force_info_current_hardware [loop],
							force_raw->force_info_reserve_hardware [loop]);

				print_mono_font_string (s);
			}

			force_en = get_local_entity_child_succ (force_en, LIST_TYPE_FORCE);
		}

		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		//
		// Supplies
		//

		force_en = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		sprintf (s, "Supplies");
		print_mono_font_string (s);

		while (force_en)
		{

			force_raw = ( force * ) get_local_entity_data (force_en);

			keysite_en = get_local_entity_first_child (force_en, LIST_TYPE_KEYSITE_FORCE);

			supply_keysite_count = 0;

			supply_ammo = 0.0;

			supply_fuel = 0.0;

			while (keysite_en)
			{

				supply_ammo += get_local_entity_float_value (keysite_en, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

				supply_fuel += get_local_entity_float_value (keysite_en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

				supply_keysite_count ++;

				keysite_en = get_local_entity_child_succ (keysite_en, LIST_TYPE_KEYSITE_FORCE);
			}

			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "%s     Ammo %f %%     Fuel %0.1f %%", entity_side_names [get_local_entity_int_value (force_en, INT_TYPE_SIDE)], supply_ammo / supply_keysite_count, supply_fuel / supply_keysite_count);
			print_mono_font_string (s);

			force_en = get_local_entity_child_succ (force_en, LIST_TYPE_FORCE);
		}

		y += get_mono_font_char_height ('X');

		unlock_screen (active_screen);
	}

	return y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float display_in_flight_external_view_entity_debug_flight_info (float y)
{

	entity
		*group,
		*en;

	vec3d
		*camera_pos,
		*pos;

	char
		s[200];

	matrix3x3
		attitude;

	float
		heading,
		pitch,
		roll;

	routed_vehicle
		*routed;

	if ((in_flight_external_view_entity_debug_flight_info) && (get_external_view_entity ()))
	{

		en = get_external_view_entity ();

		routed = ( routed_vehicle * ) get_local_entity_data (en);

		set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

		if (!lock_screen (active_screen))
		{

			return y;
		}

		set_mono_font_type (MONO_FONT_TYPE_7X12);

		set_mono_font_colour (hud_colour);

		////////////////////////////////////////

		set_mono_font_position (0.0, y);

		sprintf (s, "Drone data (%d) - player %d", get_local_entity_index (en), get_local_entity_int_value (en, INT_TYPE_PLAYER));
		print_mono_font_string (s);

		// Type
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		sprintf (s, "   Type = %s", entity_type_names [en->type]);
		print_mono_font_string (s);

		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
		{

			sprintf (s, "   Sub type = %s", entity_sub_type_aircraft_names [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)]);
			print_mono_font_string (s);

			// Position
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
			sprintf (s, "   Position = %f, %f, %f, alt %f el %f", pos->x, pos->y, pos->z, pos->y - get_3d_terrain_elevation (pos->x, pos->z), get_3d_terrain_elevation (pos->x, pos->z));
			print_mono_font_string (s);
		}
		else
		{

			sprintf (s, "   Sub type = %s", entity_sub_type_vehicle_names [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)]);
			print_mono_font_string (s);

			// Position
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
			sprintf (s, "   Position = %f, %f, %f. road node %d", pos->x, pos->y, pos->z, get_closest_road_node (pos, 20.0));
			print_mono_font_string (s);
		}

		// heading pitch and roll
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		get_local_entity_attitude_matrix (en, attitude);

		heading = get_heading_from_attitude_matrix (attitude);

		pitch = get_pitch_from_attitude_matrix (attitude);

		roll = get_roll_from_attitude_matrix (attitude);

		sprintf (s, "   Heading = %f, Pitch = %f, Roll = %f", heading, pitch, roll);
		print_mono_font_string (s);

		// velocity
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		{
			vec3d
				*mv;

			mv = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

			sprintf (s, "   Velocity = %f kts ( %.2f, %.2f, %.2f )", metres_per_second_to_knots (get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY)), mv->x, mv->y, mv->z);
			print_mono_font_string (s);
		}

		if (en->type == ENTITY_TYPE_ROUTED_VEHICLE)
		{

			sprintf (s, "   Desired Velocity = %f", routed->desired_velocity);
			print_mono_font_string (s);
		}

		// operational state
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		sprintf (s, "   Operational state = %s", operational_state_names [get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE)]);
		print_mono_font_string (s);

		// In hangar
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		sprintf (s, "   Inside Hangar = %d", get_local_entity_int_value (en, INT_TYPE_INSIDE_HANGAR));
		print_mono_font_string (s);

		// damage level
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		sprintf (s, "   Damage Level = %d", get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL));

		print_mono_font_string (s);

		// formation position
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		sprintf (s, "   Formation position = %d", get_local_entity_int_value (en, INT_TYPE_FORMATION_POSITION));
		print_mono_font_string (s);

		// view interest level
		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_MOBILE))
		{

			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Interest level = %f", get_local_entity_float_value (en, FLOAT_TYPE_VIEW_INTEREST_LEVEL));
			print_mono_font_string (s);
		}

		// Rotor RPM
		if (en->type == ENTITY_TYPE_HELICOPTER)
		{

			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Rotor rpm = %f (main), %f (tail) - Timer %f",
								get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM),
								get_local_entity_float_value (en, FLOAT_TYPE_TAIL_ROTOR_RPM),
								get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER));

			print_mono_font_string (s);
		}

		////////////////////////////////////////

		{
			entity
				*parent,
				*cwp;

			vec3d
				*parent_pos,
				*cwp_pos;

			y += get_mono_font_char_height ('X');
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "Waypoint data");
			print_mono_font_string (s);

			// Sub-Type
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			cwp = get_local_entity_current_waypoint (en);

			if (cwp)
			{

				sprintf (s, "   Sub Type = %s (position type %d)", entity_sub_type_waypoint_names [get_local_entity_int_value (cwp, INT_TYPE_ENTITY_SUB_TYPE)], get_local_entity_int_value (cwp, INT_TYPE_POSITION_TYPE));
				print_mono_font_string (s);

				if (get_local_entity_int_value (cwp, INT_TYPE_POSITION_TYPE) == POSITION_TYPE_RELATIVE)
				{

					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					parent = get_local_entity_parent (cwp, LIST_TYPE_WAYPOINT);

					if (parent)
					{

						parent_pos = get_local_entity_vec3d_ptr (parent, VEC3D_TYPE_POSITION);

						sprintf (s, "   P.Position = %f, %f, %f", parent_pos->x, parent_pos->y, parent_pos->z);
						print_mono_font_string (s);
					}
				}

				y += get_mono_font_char_height ('X');
				set_mono_font_position (0.0, y);

				cwp_pos = get_local_entity_vec3d_ptr (cwp, VEC3D_TYPE_POSITION);
				sprintf (s, "   C.Position = %f, %f, %f", cwp_pos->x, cwp_pos->y, cwp_pos->z);
				print_mono_font_string (s);

				// formation
				y += get_mono_font_char_height ('X');
				set_mono_font_position (0.0, y);

				sprintf (s, "   Formation = %s", get_formation_name ((formation_types)get_local_entity_int_value (cwp, INT_TYPE_WAYPOINT_FORMATION)));
				print_mono_font_string (s);
			}

			switch (en->type)
			{

				case ENTITY_TYPE_ROUTED_VEHICLE:
				{

					// waypoint indices
					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					sprintf (s, "   Waypoint index 1 = %d, 2 = %d, sub count %d",
								routed->waypoint_this_index,
								routed->waypoint_next_index,
								routed->sub_waypoint_count);
					print_mono_font_string (s);

					break;
				}
			}
		}

		////////////////////////////////////////

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group)
		{
			y += get_mono_font_char_height ('X');
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "Group data (%d)", get_local_entity_index (group));
			print_mono_font_string (s);

			// sub type
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Sub type = %s", entity_sub_type_group_names [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)]);
			print_mono_font_string (s);

			// formation
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Formation = %s", formation_names [get_local_entity_int_value (group, INT_TYPE_GROUP_FORMATION)]);
			print_mono_font_string (s);

			// member count
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Number of members %d (counted %d)", get_local_entity_int_value (group, INT_TYPE_MEMBER_COUNT), get_local_group_member_count (group));
			print_mono_font_string (s);

			// leader
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Group leader : %d", get_local_entity_int_value (en, INT_TYPE_GROUP_LEADER));
			print_mono_font_string (s);

			// sleep timer
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Group sleep timer %f", get_local_entity_float_value (group, FLOAT_TYPE_SLEEP));
			print_mono_font_string (s);

			// Supplies
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   Group Ammo level %f, Fuel level %f", get_local_entity_float_value (group, FLOAT_TYPE_AMMO_SUPPLY_LEVEL), get_local_entity_float_value (group, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));
			print_mono_font_string (s);

			// engage enemy
			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "   engage enemy %d (losses %d kills %d)",
						get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY),
						get_local_entity_int_value (group, INT_TYPE_LOSSES),
						get_local_entity_int_value (group, INT_TYPE_KILLS));
			print_mono_font_string (s);

			////////////////////////////////////////
		}

		////////////////////////////////////////

		y += get_mono_font_char_height ('X');
		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		sprintf (s, "3D Object data");
		print_mono_font_string (s);

		camera_pos = get_local_entity_vec3d_ptr (get_camera_entity (), VEC3D_TYPE_POSITION);

		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		// Distance
		sprintf (s, "   distance = %fm", get_3d_range (camera_pos, pos));
		print_mono_font_string (s);

		y += get_mono_font_char_height ('X');
		set_mono_font_position (0.0, y);

		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
		{

			aircraft
				*raw;

			raw = ( aircraft * ) get_local_entity_data (en);

			// Approx number
			sprintf (s, "   Approx. number = %d", get_3d_object_approximation_number (raw->inst3d));
			print_mono_font_string (s);
		}
		else
		{

			vehicle
				*raw;

			raw = ( vehicle * ) get_local_entity_data (en);

			// Approx number
			sprintf (s, "   Approx. number = %d", get_3d_object_approximation_number (raw->inst3d));
			print_mono_font_string (s);
		}

		//
		// ID number
		//
		{
			int
				seed,
				id_number;

			y += get_mono_font_char_height ('X');

			seed = get_client_server_entity_random_number_seed (get_external_view_entity ());

			id_number = rand16x (&seed);

			if (id_number == 0)
			{
				id_number = 1;
			}

			set_mono_font_position (0.0, y);

			sprintf (s, "   ID number (LSD's should match) = %05d", id_number);

			print_mono_font_string (s);
		}

		y += get_mono_font_char_height ('X');

		unlock_screen (active_screen);
	}

	return y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float display_in_flight_external_view_entity_debug_task_info (float y)
{

	entity
		*current_task,
		*keysite,
		*group,
		*task,
		*dep,
		*task_parent,
		*mb,
		*wp,
		*cwp,
		*en;

	vec3d
		*en_pos;

	char
		s[200];

	float
		range,
		stop_timer;

	int
		hrs,
		mins,
		secs,
		task_count;

	if ((in_flight_external_view_entity_debug_task_info) && (get_external_view_entity ()))
	{

		en = get_external_view_entity ();

		en_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group)
		{
			set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

			if (!lock_screen (active_screen))
			{

				return y;
			}

			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_colour (hud_colour);

			//
			// members
			//

			mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

			if (mb)
			{

				while (mb)
				{

					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					sprintf (s, "%d : %s %s (form pos %d)", get_local_entity_int_value (mb, INT_TYPE_GROUP_MEMBER_NUMBER), get_local_entity_string (mb, STRING_TYPE_FULL_NAME), operational_state_names [get_local_entity_int_value (mb, INT_TYPE_OPERATIONAL_STATE)], get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION));
					print_mono_font_string (s);

					mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
				}
			}

			current_task = get_local_entity_current_task (en);

			if (current_task)
			{
				////////////////////////////////////////

				set_mono_font_position (0.0, y);

				sprintf (s, "Task Info");
				print_mono_font_string (s);

				// Type
				y += get_mono_font_char_height ('X');
				set_mono_font_position (0.0, y);

				sprintf (s, "   Type = %s (%d)", get_local_entity_string (current_task, STRING_TYPE_FULL_NAME), get_local_entity_index (current_task));
				print_mono_font_string (s);

				// Stop timer
				stop_timer = get_local_entity_float_value (current_task, FLOAT_TYPE_STOP_TIMER);

				if (stop_timer > 0.0)
				{
					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					get_digital_countdown_values (stop_timer, NULL, &hrs, &mins, &secs);

					sprintf (s, "   Time till stop = %02d hrs %02d mins %02d secs", hrs, mins, secs);

					print_mono_font_string (s);
				}

				//
				// Waypoint list
				//

				y += get_mono_font_char_height ('X');

				cwp = get_local_entity_current_waypoint (en);

				task_parent = get_local_entity_parent (current_task, LIST_TYPE_ASSIGNED_TASK);

				keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

				if ((keysite) && (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE))
				{
					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					sprintf (s, "Current base keysite %s", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));
					print_mono_font_string (s);
				}

				wp = get_local_entity_first_child (current_task, LIST_TYPE_WAYPOINT);

				while (wp)
				{

					vec3d
						*wp_pos;

					wp_pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					if (wp == cwp)
					{

						range = get_2d_range (en_pos, wp_pos);

						sprintf (s, "WP %s (%s), (flt time %f), range %f",
									get_local_entity_string (wp, STRING_TYPE_FULL_NAME),
									get_formation_name ((formation_types)get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION)),
									get_local_entity_float_value (wp, FLOAT_TYPE_FLIGHT_TIME),
									range);

					}
					else
					{

						sprintf (s, "WP %s (%s), (flt time %f)",
									get_local_entity_string (wp, STRING_TYPE_FULL_NAME),
									get_formation_name ((formation_types)get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION)),
									get_local_entity_float_value (wp, FLOAT_TYPE_FLIGHT_TIME));
					}

					if ((get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_PICK_UP) ||
						(get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_DROP_OFF))
					{

						keysite = get_local_entity_parent (wp, LIST_TYPE_TASK_DEPENDENT);

						if (keysite)
						{
							char
								buffer [128];

							sprintf (buffer, " keysite %s", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

							strcat (s, buffer);
						}
					}

					print_mono_font_string (s);

					// display waypoint position

					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);
					sprintf (s, "   [%f, %f, %f]", wp_pos->x, wp_pos->y, wp_pos->z);
					print_mono_font_string (s);

					wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
				}
			}

			//
			// Tasks with entity as objective (ie target)
			//

			y += get_mono_font_char_height ('X');
			set_mono_font_position (0.0, y);

			sprintf (s, "Dependent tasks :");
			print_mono_font_string (s);

			dep = get_local_entity_first_child (en, LIST_TYPE_TASK_DEPENDENT);

			task_count = 0;

			while (dep)
			{
				if (get_local_entity_type (dep) == ENTITY_TYPE_WAYPOINT)
				{

					task = get_local_entity_parent (dep, LIST_TYPE_WAYPOINT);

					// sub type
					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					sprintf (s, "%d.   Sub type = %s (%d)", task_count, get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_index (task));
					print_mono_font_string (s);

					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);
					print_mono_font_string (s);

					// group info

					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					print_mono_font_string (s);
				}
				else
				{
					// sub type
					y += get_mono_font_char_height ('X');
					set_mono_font_position (0.0, y);

					sprintf (s, "%d.   type = %s (%d)", task_count, get_local_entity_type_name (dep), get_local_entity_index (dep));
					print_mono_font_string (s);
				}

				task_count ++;

				dep = get_local_entity_child_succ (dep, LIST_TYPE_TASK_DEPENDENT);
			}

			unlock_screen (active_screen);
		}
	}

	return y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_in_flight_external_view_entity_weapon_info (void)
{
	entity
		*en,
		*target,
		*persuer;

	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	entity_sub_types
		selected_weapon;

	float
		y,
		y_add;

	int
		package,
		unarmed,
		col;

	char
		s[200];

	if (in_flight_external_view_entity_weapon_info)
	{
		if (in_cockpit)
		{
			en = get_gunship_entity ();
		}
		else
		{
			en = get_external_view_entity ();
		}

		if (en)
		{
			////////////////////////////////////////
			//
			// weapons info
			//
			////////////////////////////////////////

			if (!lock_screen (active_screen))
			{
				return;
			}

			set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

			set_mono_font_type (MONO_FONT_TYPE_6X7);

			col = get_global_hud_colour ();

			col = (++col <= NUM_HUD_COLOURS - 1) ? col : 0;

			set_mono_font_colour (hud_colour_table[col]);

			y = 0.0;

			y_add = get_mono_font_char_height ('0');

			////////////////////////////////////////

			unarmed = TRUE;

			package_status = ( weapon_package_status * ) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

			if (package_status)
			{
				selected_weapon = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

				config_type = ( weapon_config_types ) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

				ASSERT (weapon_config_type_valid (config_type));

				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
					{
						break;
					}

					if (unarmed)
					{
						set_mono_font_position (0.0, y);

						sprintf (s, "SELECTED WEAPON       = %d", selected_weapon);

						print_mono_font_string (s);

						y += y_add;

						set_mono_font_position (0.0, y);

						sprintf
						(
							s,
							"WEAPONS CONFIGURATION = %d (%d to %d)",
							config_type,
							get_local_entity_int_value (en, INT_TYPE_MIN_WEAPON_CONFIG_TYPE),
							get_local_entity_int_value (en, INT_TYPE_MAX_WEAPON_CONFIG_TYPE)
						);

						print_mono_font_string (s);

						y += y_add;

						unarmed = FALSE;
					}

					set_mono_font_position (0.0, y);

					if (weapon_config_database[config_type][package].sub_type == selected_weapon)
					{
						print_mono_font_char ('>');
					}
					else
					{
						print_mono_font_char (' ');
					}

					sprintf
					(
						s,
						"%4dx (s=%02d) %-30.30s (h=%7.2f (%04X), p=%7.2f (%04X))",
						package_status[package].number,

						weapon_config_database[config_type][package].salvo_size,

						weapon_database[weapon_config_database[config_type][package].sub_type].full_name,
						deg (package_status[package].weapon_system_heading),
						weapon_config_database[config_type][package].heading_share_mask,
						deg (package_status[package].weapon_system_pitch),
						weapon_config_database[config_type][package].pitch_share_mask
					);

					print_mono_font_string (s);

					if (package_status[package].damaged)
					{
						print_mono_font_string (" (DAMAGED)");
					}

					y += y_add;
				}
			}

			if (!unarmed)
			{
				set_mono_font_position (0.0, y);

				sprintf (s, "WEAPON LOAD WEIGHT = %.2fKg", get_local_entity_weapon_load_weight (en));

				print_mono_font_string (s);

				y += y_add;

				set_mono_font_position (0.0, y);

				sprintf (s, "WEAPON BURST TIMER = %.2f", get_local_entity_float_value (en, FLOAT_TYPE_WEAPON_BURST_TIMER));

				print_mono_font_string (s);

				y += y_add;
			}
			else
			{
				set_mono_font_position (0.0, y);

				print_mono_font_string ("NO WEAPONS");

				y += y_add;
			}

			////////////////////////////////////////
			//
			// radar / laser / los to target / radar jammer / infra-red jammer
			//
			////////////////////////////////////////

			y += y_add;

			set_mono_font_position (0.0, y);

			if (get_local_entity_int_value (en, INT_TYPE_RADAR_ON))
			{
				print_mono_font_string ("RADAR        : ON");
			}
			else
			{
				print_mono_font_string ("RADAR        : OFF");
			}

			y += y_add;

			////////////////////////////////////////

			set_mono_font_position (0.0, y);

			if (get_local_entity_int_value (en, INT_TYPE_LASER_ON))
			{
				print_mono_font_string ("LASER        : ON");
			}
			else
			{
				print_mono_font_string ("LASER        : OFF");
			}

			y += y_add;

			////////////////////////////////////////

			set_mono_font_position (0.0, y);

			if (get_local_entity_int_value (en, INT_TYPE_LOS_TO_TARGET))
			{
				print_mono_font_string ("LOS TO TARGET: CLEAR");
			}
			else
			{
				print_mono_font_string ("LOS TO TARGET: OBSCURED");
			}

			y += y_add;

			////////////////////////////////////////

			set_mono_font_position (0.0, y);

			if (get_local_entity_int_value (en, INT_TYPE_RADAR_JAMMER_ON))
			{
				print_mono_font_string ("RADAR JAMMER : ON");
			}
			else
			{
				print_mono_font_string ("RADAR JAMMER : OFF");
			}

			y += y_add;

			////////////////////////////////////////

			set_mono_font_position (0.0, y);

			if (get_local_entity_int_value (en, INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				print_mono_font_string ("IR JAMMER    : ON");
			}
			else
			{
				print_mono_font_string ("IR JAMMER    : OFF");
			}

			y += y_add;

			////////////////////////////////////////

			set_mono_font_position (0.0, y);

			if (get_local_entity_int_value (en, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
			{
				print_mono_font_string ("HELLFIRE     : LOAL");
			}
			else
			{
				print_mono_font_string ("HELLFIRE     : LOBL");
			}

			y += y_add;

			////////////////////////////////////////

			set_mono_font_position (0.0, y);

			if (get_local_entity_int_value (en, INT_TYPE_WEAPONS_HOLD))
			{
				print_mono_font_string ("WEAPONS      : HOLD");
			}
			else
			{
				print_mono_font_string ("WEAPONS      : FREE");
			}

			y += y_add;

			////////////////////////////////////////
			//
			// target info
			//
			////////////////////////////////////////

			y += y_add;

			target = get_local_entity_parent (en, LIST_TYPE_TARGET);

			if (target)
			{
				set_mono_font_position (0.0, y);

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					sprintf (s, "TARGET SCAN TIMER = %.2f:", get_local_entity_float_value (en, FLOAT_TYPE_TARGET_SCAN_TIMER));

					print_mono_font_string (s);

					y += y_add;

					set_mono_font_position (0.0, y);

					sprintf (s, "TARGET FIRE TIMER = %.2f:", get_local_entity_float_value (en, FLOAT_TYPE_TARGET_FIRE_TIMER));

					print_mono_font_string (s);

					y += y_add;

					set_mono_font_position (0.0, y);
				}

				sprintf (s, "TARGET:");

				print_mono_font_string (s);

				y += y_add;

				set_mono_font_position (0.0, y);

				sprintf
				(
					s,
					"%-25.25s (INDEX = %5d, RANGE = %8.2f, DAMAGE = %d)",
					get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_index (target),
					get_3d_range (get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION), get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION)),
					get_local_entity_int_value (target, INT_TYPE_DAMAGE_LEVEL)
				);

				print_mono_font_string (s);

				y += y_add;
			}
			else
			{
				set_mono_font_position (0.0, y);

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					sprintf (s, "NO TARGET (TARGET SCAN TIMER = %.2f):", get_local_entity_float_value (en, FLOAT_TYPE_TARGET_SCAN_TIMER));
				}
				else
				{
					sprintf (s, "NO TARGET:");
				}

				print_mono_font_string (s);

				y += y_add;
			}

			////////////////////////////////////////
			//
			// persuer info
			//
			////////////////////////////////////////

			y += y_add;

			persuer = get_local_entity_first_child (en, LIST_TYPE_TARGET);

			if (persuer)
			{
				set_mono_font_position (0.0, y);

				print_mono_font_string ("PERSUERS:");

				y += y_add;

				while (persuer)
				{
					set_mono_font_position (0.0, y);

					sprintf
					(
						s,
						"%-25.25s (INDEX = %5d, RANGE = %8.2f, DAMAGE = %d)",
						get_local_entity_string (persuer, STRING_TYPE_FULL_NAME), get_local_entity_index (persuer),
						get_3d_range (get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION), get_local_entity_vec3d_ptr (persuer, VEC3D_TYPE_POSITION)),
						get_local_entity_int_value (persuer, INT_TYPE_DAMAGE_LEVEL)
					);

					print_mono_font_string (s);

					y += y_add;

					persuer = get_local_entity_child_succ (persuer, LIST_TYPE_TARGET);
				}
			}
			else
			{
				set_mono_font_position (0.0, y);

				print_mono_font_string ("NO PERSUERS");

				y += y_add;
			}

			////////////////////////////////////////

			unlock_screen (active_screen);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_in_flight_gunship_target_list_info (void)
{
	entity
		*source,
		*target,
		*current_target;

	vec3d
		*source_position,
		*target_position;

	float
		y,
		y_add;

	int
		col;

	char
		s[200];

	if (!get_gunship_entity ())
	{
		return;
	}

	if (in_flight_gunship_target_list_info)
	{
		if (lock_screen (active_screen))
		{
			set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

			set_mono_font_type (MONO_FONT_TYPE_6X7);

			col = get_global_hud_colour ();

			col = (++col <= NUM_HUD_COLOURS - 1) ? col : 0;

			set_mono_font_colour (hud_colour_table[col]);

			y = 0.0;

			y_add = get_mono_font_char_height ('0');

			set_mono_font_position (0.0, y);

			print_mono_font_string ("GUNSHIP TARGET LIST: ");

			print_mono_font_string (get_selected_target_acquisition_system_name ());

			y += y_add;

			source = get_gunship_entity ();

			source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

			target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

			current_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

			while (target)
			{
				if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
				{
					set_mono_font_position (0.0, y);

					if (target == current_target)
					{
						print_mono_font_char ('>');
					}
					else
					{
						print_mono_font_char (' ');
					}

					if (get_gunship_target_valid_for_ground_radar (target))
					{
						print_mono_font_char ('G');
					}
					else
					{
				 		print_mono_font_char (' ');
					}

					if (get_gunship_target_valid_for_air_radar (target))
					{
						print_mono_font_char ('A');
					}
					else
					{
						print_mono_font_char (' ');
					}

					if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
					{
						print_mono_font_char ('L');
					}
					else
					{
						print_mono_font_char (' ');
					}

					target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

					sprintf
					(
						s,
						" %-25.25s (INDEX = %5d, RANGE = %8.2f)",
						get_local_entity_string (target, STRING_TYPE_FULL_NAME),
						get_local_entity_index (target),
						get_3d_range (source_position, target_position)
					);

					print_mono_font_string (s);

					y += y_add;
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}

			unlock_screen (active_screen);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_in_flight_external_view_entity_guide_info (void)
{
	entity
		*en,
		*wp,
		*task,
		*group,
		*guide,
		*member;

	entity_sub_types
		waypoint_type,
		guide_type;

	float
		y,
		y_add;

	int
		loop,
		count,
		current_flag;

	unsigned int
		valid_members,
		member_number;

	char
		s[200],
		member_string [32];

	vec3d
		pos;

	if (in_flight_external_view_entity_guide_info)
	{
		en = get_external_view_entity ();

		if (en)
		{
			if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
			{
				if (!begin_3d_scene ())
				{
					return;
				}

				set_full_screen_viewport ();

  				set_ui_font_type (UI_FONT_ARIAL_14);

  				set_ui_font_colour (sys_col_amber);

				y = 0.0;

				y_add = ui_get_font_height () + 1;

				//
				// current guide info
				//

				guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

				if (guide)
				{
					wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

					ASSERT (wp);

					waypoint_type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);

					guide_type = get_local_entity_int_value (guide, INT_TYPE_ENTITY_SUB_TYPE);

					////////////////////////////////////////

					sprintf (s, "%s", entity_sub_type_guide_names [guide_type]);

					ui_display_text (s, 0, y);

					y += y_add;

					////////////////////////////////////////

					sprintf (s, "%s", waypoint_database [waypoint_type].full_name);

					ui_display_text (s, 0, y);

					y += y_add;

					////////////////////////////////////////

					// criteria

					for (loop = 0; loop < NUM_GUIDE_CRITERIA_TYPES; loop ++)
					{
						if (get_guide_criteria_valid (guide, ( guide_criteria_types ) loop))
						{
							const char
								*criteria_name;

							float
								value;

							criteria_name = guide_criteria_type_names [loop];

							value = get_guide_criteria_value (guide, ( guide_criteria_types ) loop);

							sprintf (s, "%s - %f", criteria_name, value);

							ui_display_text (s, 0, y);

							y += y_add;
						}
					}

					////////////////////////////////////////

					get_local_entity_vec3d (guide, VEC3D_TYPE_GUIDE_POSITION, &pos);

					sprintf (s, "Guide Position %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);

					ui_display_text (s, 0, y);

					y += y_add;

					////////////////////////////////////////

					get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &pos);

					sprintf (s, "Mobile Position %.2f, %.2f, %.2f", pos.x, pos.y, pos.z);

					ui_display_text (s, 0, y);

					y += y_add;

					////////////////////////////////////////

					sprintf (s, "Guide Distance %.2f, Speed %.2f", get_local_entity_float_value (guide, FLOAT_TYPE_DISTANCE), get_local_entity_float_value (guide, FLOAT_TYPE_VELOCITY));

					ui_display_text (s, 0, y);

					y += y_add;

					////////////////////////////////////////

					sprintf (s, "Mobile Distance %.2f, Speed %.2f, Altitide %f",
								get_local_entity_float_value (en, FLOAT_TYPE_DISTANCE),
								get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY),
								get_local_entity_float_value (en, FLOAT_TYPE_RADAR_ALTITUDE) - get_local_entity_float_value (en, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE));

					ui_display_text (s, 0, y);

					y += y_add;

					////////////////////////////////////////

					sprintf (s, "Group Leader %d, Task Leader %d", get_local_entity_int_value (en, INT_TYPE_GROUP_LEADER), get_local_entity_int_value (en, INT_TYPE_TASK_LEADER));

					ui_display_text (s, 0, y);

					y += y_add;

					////////////////////////////////////////

					sprintf (s, "Formation Position %d, Member Number %d", get_local_entity_int_value (en, INT_TYPE_FORMATION_POSITION), get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER));

					ui_display_text (s, 0, y);

					y += y_add;
				}

				//
				// group info
				//

				group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

				ASSERT (group);

				sprintf (s, "Group Mode %s", group_mode_names [get_local_entity_int_value (group, INT_TYPE_GROUP_MODE)]);

				ui_display_text (s, 0, y);

				y += y_add;

				////////////////////////////////////////

				sprintf (s, "Operational State %s", operational_state_names [get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE)]);

				ui_display_text (s, 0, y);

				y += y_add;

				////////////////////////////////////////

				//
				// group guide stack info
				//

				y += y_add;

				guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

				while (guide)
				{
					count = 0;

					current_flag = FALSE;

					//
					// count up members following guide, and see if this entity is one of them
					//

					member = get_local_entity_first_child (guide, LIST_TYPE_FOLLOWER);

					while (member)
					{
						count += 1;

						if (member == en)
						{
							current_flag = TRUE;
						}

						member = get_local_entity_child_succ (member, LIST_TYPE_FOLLOWER);
					}

					task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

					ASSERT (task);

					//
					// determine which members are allowed to do this task
					//

					valid_members = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

					if (valid_members == TASK_ASSIGN_ALL_MEMBERS)
					{
						sprintf (member_string, "ALL");
					}
					else if (valid_members == TASK_ASSIGN_NO_MEMBERS)
					{
						sprintf (member_string, "NONE");
					}
					else
					{
						member_string [0] = 0;

						member_number = 0;

						while (valid_members)
						{
							if (valid_members & 1)
							{
								sprintf (s, "%d ", member_number);

								strcat (member_string, s);
							}

							member_number ++;

							valid_members = valid_members >> 1;
						}
					}

					//
					// print task info
					//

					sprintf (s, "-%d- %s (%d) %s", count, get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_index (task), member_string);

					if (current_flag)
					{
						strcat (s, " <---");
					}

					ui_display_text (s, 0, y);

					y += y_add;

					guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
				}

				////////////////////////////////////////

				end_3d_scene ();
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_cpu_count (void)
{

	static int
		cpu_history_position = 0;

	static double
		cpu_history [MAX_CPU_COUNT_HISTORY];

	int
		loop;

	cpu_history [cpu_history_position] = (get_cpu_clock_count () / get_delta_time ());

	//
	// Max
	//

	if (cpu_history [cpu_history_position] > cpu_count_max)
	{

		cpu_count_max = cpu_history [cpu_history_position];
	}

	//
	// Average
	//

	cpu_count_av = 0.0;

	for (loop = 0; loop < MAX_CPU_COUNT_HISTORY; loop ++)
	{

		cpu_count_av += cpu_history [loop];
	}

	cpu_count_av /= MAX_CPU_COUNT_HISTORY;

	//
	// Percentage, assuming 200 Mhz processor
	//

	cpu_count_av_percent = (cpu_count_av / 200000000) * 100;

	cpu_history_position = ( cpu_history_position + 1 ) % MAX_CPU_COUNT_HISTORY;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_in_flight_debug_info (void)
{
	float
		y;

	////////////////////////////////////////

	y = 0.0;

	//y = display_in_flight_debug_demo_message (y);

	y = display_in_flight_debug_misc_info (y);

	y = display_in_flight_debug_keysite_info (y);

	y = display_in_flight_debug_force_info (y);

	y = display_in_flight_external_view_entity_debug_flight_info (y);

	y = display_in_flight_external_view_entity_debug_task_info (y);

	////////////////////////////////////////

	display_in_flight_external_view_entity_weapon_info ();

	display_in_flight_gunship_target_list_info ();

	display_in_flight_external_view_entity_guide_info ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void flight_test (void)
{

	vec3d
		position,
		direction_vector,
		motion_vector;

	float
		x,
		y,
		m,
		time,
		delta_time,
		velocity,
		pitch,
		heading;

	velocity = 1000.0;

	x = 10.0 * KILOMETRE;

	m = (G * range * range) / (2 * velocity * velocity);

	y = 0.0;

	pitch = atan ((-x + sqrt ((x * x) - (4 * m * m) - (4 * m * y))) / (-2 * m));

	heading = 0.0;

	get_3d_unit_vector_from_heading_and_pitch (&direction_vector, heading, pitch);

	motion_vector.x = direction_vector.x * velocity;
	motion_vector.y = direction_vector.y * velocity;
	motion_vector.z = direction_vector.z * velocity;

	position.x = 0.0;
	position.y = 0.0;
	position.z = 0.0;

	time = 0.0;
	delta_time = 0.01;

	while (position.y >= 0.0)
	{

		position.x += motion_vector.x * delta_time;
		position.y += motion_vector.y * delta_time - (0.5 * G * delta_time * delta_time);
		position.z += motion_vector.z * delta_time;

		motion_vector.y -= G * delta_time;

		time += delta_time;
	}

	debug_log ("TEST: FLOAT  final range = %f (req range %f), time %f, pitch %f. final position %f, %f, %f", position.z, range, time, pitch, position.x, position.y, position.z);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
