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

game_exit_types
	game_exit_type;

int
	display_exit_message_flag = FALSE,
   exit_flight_loop_flag = FALSE;

view_modes
	old_view_mode;

camera_modes
	old_camera_mode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned char
	*game_exit_text [NUM_GAME_EXIT_TYPES] =
	{
		"INVALID",
		"Quit Mission? (Y/N)",
		"Exit Campaign? (Y/N)",
		"Exit Dynamic Missions? (Y/N)",
		"Exit Comanche Versus Hokum? (Y/N)",
		"Press Space",
		"KICKOUT",
		"Exit Demo? (Y/N)",	
		"Quit Mission? (Y/N)",
		"",
		"Press Space",
	};


/*
		{ GAME_EXIT_INVALID,
			{
				{ LANGUAGE_ENGLISH,	"Exit INVALID",	0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Exit INVALID",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Exit INVALID",	0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Exit INVALID",	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"Exit INVALID",	0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_MISSION,
			{
				{ LANGUAGE_ENGLISH,	"Quit Mission? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Einsatz beenden? (J/N)",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Abandonner la mission? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Abbandonare la missione? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"¿Abandonar la Misión? (S/N)",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_CAMPAIGN,
			{
				{ LANGUAGE_ENGLISH,	"Exit Campaign? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Unternehmen beenden? (J/N)",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Abandonner la campagne? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Abbandonare la campagna? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"¿Abandonar la Campaña? (S/N)",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_DYNAMIC_MISSIONS,
			{
				{ LANGUAGE_ENGLISH,	"Quit Dynamic Missions? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Dynamisches Unternehmen beenden? (J/N)",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Abandonner les missions dynamiques? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Quit Dynamic Missions? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"¿Abandonar misión? (S/N)",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_APACHE_HAVOC,
			{
				{ LANGUAGE_ENGLISH,	"Exit Apache Havoc? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Apache Havoc beenden? (J/N)",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Exit Apache Havoc? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Exit Apache Havoc? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"¿Exit Apache Havoc? (S/N)",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_DEBRIEF,
			{
				{ LANGUAGE_ENGLISH,	"Press Space",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Leertaste drücken",		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Press Space",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Press Space",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"Pulsa Espacio",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_KICKOUT,
			{
				{ LANGUAGE_ENGLISH,	"Kick out",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Ausschließen",		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Kick out",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Kick out",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"Kick out",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_DEMO,
			{
				{ LANGUAGE_ENGLISH,	"Exit Demo? (Y/N)",	0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Demo beenden? (J/N)",		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Quitter la démo? (Y/N)",	0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Exit Demo? (Y/N)",	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"¿Exit Demo? (S/N)",	0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_SPECIAL_RESTART,
			{
				{ LANGUAGE_ENGLISH,	"SIERRA HOTEL",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"SIERRA HOTEL",		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"SIERRA HOTEL",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"SIERRA HOTEL",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"SIERRA HOTEL",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_CRASH,
			{
				{ LANGUAGE_ENGLISH,	"Quit Mission? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"Einsatz beenden? (J/N)",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"Abandonner la mission? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"Abbandonare la missione? (Y/N)",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"¿Abandonar la misión? (S/N)",		0, 0,		0, 0 },
			}
		},

		{ GAME_EXIT_KEYBOARD_EVENTS,
			{
				{ LANGUAGE_ENGLISH,	"", DIK_Y, DIK_N, 0, 0 },
				{ LANGUAGE_GERMAN,	"", DIK_J, DIK_N, 0, 0 },
				{ LANGUAGE_FRENCH,	"", DIK_Y, DIK_N, 0, 0 },
				{ LANGUAGE_ITALIAN,	"", DIK_Y, DIK_N, 0, 0 },
				{ LANGUAGE_SPANISH,	"", DIK_S, DIK_N, 0, 0 },
			}
		},

		{ GAME_EXIT_PILOT_EJECTED,
			{
				{ LANGUAGE_ENGLISH,	"Press space", DIK_SPACE, DIK_SPACE, 0, 0 },
				{ LANGUAGE_GERMAN,	"Press space", DIK_SPACE, DIK_SPACE, 0, 0 },
				{ LANGUAGE_FRENCH,	"Press space", DIK_SPACE, DIK_SPACE, 0, 0 },
				{ LANGUAGE_ITALIAN,	"Press space", DIK_SPACE, DIK_SPACE, 0, 0 },
				{ LANGUAGE_SPANISH,	"Press space", DIK_SPACE, DIK_SPACE, 0, 0 },
			}
		},

		{ NUM_GAME_EXIT_TYPES,
			{
				{ LANGUAGE_ENGLISH,	"NUM_GAME_EXIT_TYPES",	0, 0,		0, 0 },
				{ LANGUAGE_GERMAN,	"NUM_GAME_EXIT_TYPES",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH,	"NUM_GAME_EXIT_TYPES",	0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN,	"NUM_GAME_EXIT_TYPES",	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH,	"NUM_GAME_EXIT_TYPES",	0, 0,		0, 0 },
			}
		}
	};
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void dont_exit_game_function (event *ev);

static void exit_game_events (void);

static void pilot_ejected_events (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exit_game (event *ev)
{

	if (get_gunship_entity ())
	{

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
		{

			start_game_exit (GAME_EXIT_PILOT_EJECTED, FALSE);
		}
		else
		{

			start_game_exit (GAME_EXIT_MISSION, FALSE);
		}
	}
	else
	{

		if (get_game_type () == GAME_TYPE_DEMO)
		{

			start_game_exit (GAME_EXIT_DEMO, FALSE);
		}
		else
		{

			start_game_exit (GAME_EXIT_CAMPAIGN, FALSE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exit_apache_havoc (event *ev)
{

	start_game_exit (GAME_EXIT_APACHE_HAVOC, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void start_game_exit (game_exit_types type, int pause_flag)
{
	game_exit_type = type;

	if (pause_flag)
	{

		set_time_acceleration (TIME_ACCELERATION_PAUSE);
	}
	else
	{
		
		set_min_time_acceleration (NULL);
	}

	//
	// turn off messaging system ( the events would be lost anyway ! )
	//

	stop_messaging_system (NULL);

	//
	//
	//

	switch (game_exit_type)
	{

		case GAME_EXIT_KICKOUT:
		{

			if (get_event_stack_head_function () == exit_game_events)
			{
		
				pop_event (exit_game_events);
			}

			set_exit_flight_loop (TRUE);

			set_game_type (GAME_TYPE_INVALID);

			set_game_initialisation_phase (GAME_INITIALISATION_PHASE_GAME_TYPE);

			push_ui_screen (game_type_screen);

			break;
		}

		case GAME_EXIT_CRASH:
		case GAME_EXIT_DEBRIEF:
		{

			set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_SIMULATOR);

			// intentional follow through...
		}

		case GAME_EXIT_MISSION:
		case GAME_EXIT_CAMPAIGN:
		case GAME_EXIT_DEMO:
		{

			if (get_event_stack_head_function () == exit_game_events)
			{
		
				pop_event (exit_game_events);
			}
		
			push_event (exit_game_events, "Exit Game Events");

			set_display_exit_message (TRUE);
		
			notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_DEBRIEFING);

			break;
		}

		case GAME_EXIT_PILOT_EJECTED:
		{

			push_event (pilot_ejected_events, "Pilot Ejected Events");

			break;
		}

		case GAME_EXIT_APACHE_HAVOC:
		{

			exit_game_function (NULL);

			break;
		}

		default:
		{

			debug_fatal ("GAMEEXIT: Illegal exit type %d", game_exit_type);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exit_game_events (void)
{

	set_event (DIK_S, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, save_screen_image_event);

	switch (game_exit_type)
	{

		case GAME_EXIT_DEBRIEF:
		{

			set_event (DIK_SPACE, MODIFIER_NONE, KEY_STATE_DOWN, exit_game_function);

			break;
		}

		case GAME_EXIT_MISSION:
		case GAME_EXIT_CRASH:
		case GAME_EXIT_CAMPAIGN:
		case GAME_EXIT_DEMO:
		case GAME_EXIT_APACHE_HAVOC:
		{

//			set_event ( get_localisation_x_position ( text_translation_list, GAME_EXIT_KEYBOARD_EVENTS ), MODIFIER_NONE, KEY_STATE_DOWN, exit_game_function);
//			set_event ( get_localisation_y_position ( text_translation_list, GAME_EXIT_KEYBOARD_EVENTS ), MODIFIER_NONE, KEY_STATE_DOWN, dont_exit_game_function);
			set_event ( DIK_Y, MODIFIER_NONE, KEY_STATE_DOWN, exit_game_function);
			set_event ( DIK_T, MODIFIER_NONE, KEY_STATE_DOWN, exit_game_function);
			set_event ( DIK_N, MODIFIER_NONE, KEY_STATE_DOWN, dont_exit_game_function);

			break;
		}

		case GAME_EXIT_KICKOUT:
		case GAME_EXIT_PILOT_EJECTED:
		{

			// no events

			break;
		}
		default:
		{

			debug_fatal ("GAMEEXIT: Illegal exit type %d", game_exit_type);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exit_game_function (event *ev)
{

	switch (game_exit_type)
	{

		case GAME_EXIT_MISSION:
		case GAME_EXIT_CRASH:
		case GAME_EXIT_DEBRIEF:
		{

			pop_event (exit_game_events);

			set_display_exit_message (FALSE);
		
			set_gunship_entity (NULL);
		
			set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);

			//set_game_initialisation_phase (GAME_INITIALISATION_PHASE_NONE); // needed?
		
			/////////////////////////////////////////////////////////////////
			switch (get_game_type ())
			{
				case GAME_TYPE_CAMPAIGN:
				case GAME_TYPE_SKIRMISH:
				{
					#if !DEMO_VERSION

					push_ui_screen (campaign_screen);

					#endif
		
					break;
				}
				case GAME_TYPE_FREE_FLIGHT:
				{
					push_ui_screen (free_flight_screen);

					break;
				}
				case GAME_TYPE_DEMO:
				{

					set_game_initialisation_phase (GAME_INITIALISATION_PHASE_GAME_TYPE);

					set_game_type (GAME_TYPE_INVALID);

					push_ui_screen (game_type_screen);

					set_exit_flight_loop (TRUE);
		
					break;
				}
			}
			/////////////////////////////////////////////////////////////////
		
			break;
		}

		case GAME_EXIT_CAMPAIGN:
		case GAME_EXIT_DEMO:
		{

			//set_game_initialisation_phase (GAME_INITIALISATION_PHASE_GAME_TYPE);

			initialise_game_initialisation_phases ();

			pop_event (exit_game_events);

			set_display_exit_message (FALSE);

			set_exit_flight_loop (TRUE);

			push_ui_screen (game_type_screen);

			break;
		}

		case GAME_EXIT_PILOT_EJECTED:
		{

			pop_event (pilot_ejected_events);

			set_display_exit_message (FALSE);
		
			set_gunship_entity (NULL);
		
			set_in_flight_game_mode (IN_FLIGHT_GAME_MODE_PLANNER);
		
			/////////////////////////////////////////////////////////////////
			switch (get_game_type ())
			{
				case GAME_TYPE_CAMPAIGN:
				case GAME_TYPE_SKIRMISH:
				{
					#if !DEMO_VERSION

					push_ui_screen (campaign_screen);

					#endif
		
					break;
				}
				case GAME_TYPE_FREE_FLIGHT:
				{
					push_ui_screen (free_flight_screen);

					break;
				}
				case GAME_TYPE_DEMO:
				{

					set_game_initialisation_phase (GAME_INITIALISATION_PHASE_GAME_TYPE);

					set_game_type (GAME_TYPE_INVALID);

					push_ui_screen (game_type_screen);

					set_exit_flight_loop (TRUE);
		
					break;
				}
			}
			/////////////////////////////////////////////////////////////////

			break;
		}

		case GAME_EXIT_APACHE_HAVOC:
		{
extern int query_TIR_active ( void );	// Retro 030318
extern void ExitTrackIR ( void );		// Retro 030318

			push_ui_screen (exit_screen);

			pop_event (exit_game_events);

			set_display_exit_message (FALSE);

//			set_ui_object_drawable (exit_back_button, FALSE);
//			set_ui_object_drawable (exit_screen_text, FALSE);
//			set_ui_object_drawable (exit_forward_button, FALSE);

			set_exit_flight_loop (TRUE);

			set_exit_ui (TRUE);

		// By Retro.. 030318
		// ..if TrackIR is active, tell it to stop transmitting before closing down..
			if (query_TIR_active() == TRUE)
				ExitTrackIR();
		// end Retro

			break;
		}

		case GAME_EXIT_INVALID:
		case GAME_EXIT_KICKOUT:
		{

			break;
		}

		default:
		{

			debug_fatal ("GAMEEXIT: Illegal exit type %d", game_exit_type);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dont_exit_game_function (event *ev)
{

	set_min_time_acceleration (NULL);
	
	set_display_exit_message (FALSE);

	pop_event (exit_game_events);

	switch (game_exit_type)
	{
		case GAME_EXIT_DEMO:
		case GAME_EXIT_CRASH:
		case GAME_EXIT_MISSION:
		case GAME_EXIT_CAMPAIGN:
		{
		
			if ((get_gunship_entity ()) && (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE)))
			{
			
				notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_MODE_CHASE);
			
				set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);
			}
			else
			{
		
				notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_AUTO_EDIT);
			}

			break;
		}
		case GAME_EXIT_APACHE_HAVOC:
		case GAME_EXIT_DEBRIEF:
		case GAME_EXIT_KICKOUT:
		case GAME_EXIT_PILOT_EJECTED:
		default:
		{

			debug_fatal ("GAMEEXIT: Illegal exit type %d", game_exit_type);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_display_exit_message (int flag)
{

	display_exit_message_flag = flag;

	switch (game_exit_type)
	{

		case GAME_EXIT_MISSION:
		case GAME_EXIT_CRASH:
		case GAME_EXIT_CAMPAIGN:
		{
//			set_ui_object_text (planner_exit_message, get_localisation_text (text_translation_list, game_exit_type));
		
			break;
		}

		case GAME_EXIT_INVALID:
		{
			// not illegal.

			break;
		}

		case GAME_EXIT_KICKOUT:
		{
			display_exit_message_flag = FALSE;

			break;
		}

		case GAME_EXIT_DEBRIEF:
		case GAME_EXIT_APACHE_HAVOC:
		case GAME_EXIT_DEMO:
		case GAME_EXIT_PILOT_EJECTED:
		{

			// not invalid.

			break;
		}

		default:
		{

			debug_fatal ("GAMEEXIT: Illegal exit type %d", game_exit_type);
		}
	}

	//set_ui_object_text (bmission_exit_message, get_localisation_text (text_translation_list, GAME_EXIT_CAMPAIGN));

//	set_ui_object_drawable (planner_exit_message, flag);
//	set_ui_object_drawable (planner_exit_message_gfx, flag);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_exit_message (void)
{

	char
		buffer [64];

	float
		x;


	if (display_exit_message_flag)
	{
	
		set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);
	
		if (begin_3d_scene ())	//lock_screen (active_screen))
		{

			int
				string_length,
				screen_x_offset,
				screen_y_offset;

			set_ui_font_type (UI_FONT_ARIAL_18);

			set_ui_font_colour (sys_col_yellow);

			screen_x_offset = full_screen_x_mid - 320;
	
			screen_y_offset = full_screen_y_mid - 240;

			switch (get_game_type ())
			{
/*
				case GAME_TYPE_SPECIAL:
				{

//					ui_draw_alpha_graphic (220 + screen_x_offset, 20 + screen_y_offset, 204 + screen_x_offset, 126 + screen_y_offset,
//													(unsigned short int *) get_graphics_file_data ( GRAPHICS_UI_COMMON_APACHE_HAVOC_V ) );

					if (game_exit_type == GAME_EXIT_SPECIAL_RESTART)
					{
						//
						// SPECIAL GAMES display session title, a heading for the high score table, and a message prompting
						// the player to press the spacebar
						//
						
						draw_special_restart_text ();

						set_ui_font_type (UI_FONT_ARIAL_14);

						set_ui_font_colour (sys_col_white);

						sprintf (buffer, "%s", game_exit_text [game_exit_type]);
						string_length = ui_get_string_length ( buffer );
					
						x = (220 + (204 / 2)) - ( string_length / 2 );
					
						ui_display_text (buffer, x + screen_x_offset, 96 + screen_y_offset);
					
						set_ui_font_type (UI_FONT_ARIAL_18);

						set_ui_font_colour (sys_col_yellow);
					}
					else
					{
						sprintf (buffer, "%s", game_exit_text [game_exit_type]);
						string_length = ui_get_string_length ( buffer );
		
						x = (220 + (204 / 2)) - ( string_length / 2 );
			
						ui_display_text (buffer, x + screen_x_offset, 83 + screen_y_offset);
					}
					
					break;
				}
*/
				case GAME_TYPE_FREE_FLIGHT:
				{
	
					sprintf (buffer, "%s", game_exit_text [game_exit_type]);
					string_length = ui_get_string_length ( buffer );
	
//					ui_draw_alpha_graphic (220 + screen_x_offset, 180 + screen_y_offset, 204 + screen_x_offset, 126 + screen_y_offset,
//													(unsigned short int *) get_graphics_file_data ( GRAPHICS_UI_COMMON_APACHE_HAVOC_V ) );
	
					x = (220 + (204 / 2)) - ( string_length / 2 );
		
					ui_display_text (buffer, x + screen_x_offset, 243 + screen_y_offset);

					break;
				}
				default:
				{
		
					switch (game_exit_type)
					{
		
						case GAME_EXIT_DEBRIEF:
						case GAME_EXIT_MISSION:
						case GAME_EXIT_CRASH:
						{
	
							sprintf (buffer, "%s", game_exit_text [game_exit_type]);
							string_length = ui_get_string_length ( buffer );
		
//							ui_draw_alpha_graphic (340 + screen_x_offset, 170 + screen_y_offset, 204 + screen_x_offset, 126 + screen_y_offset,
//															(unsigned short int *) get_graphics_file_data ( GRAPHICS_UI_COMMON_APACHE_HAVOC_V ) );
		
							x = (340 + (204 / 2)) - ( string_length / 2 );
				
							ui_display_text (buffer, x + screen_x_offset, 238 + screen_y_offset);
			
							break;
						}
		
						case GAME_EXIT_CAMPAIGN:
						case GAME_EXIT_APACHE_HAVOC:
						case GAME_EXIT_DEMO:
						{

							if (game_exit_type == GAME_EXIT_DEMO)
							{
								sprintf (buffer, "%s", get_trans ("Exit Demo? (Y/N)"));
							}
							else
							{
								sprintf (buffer, "%s", game_exit_text [game_exit_type]);
							}
							
							string_length = ui_get_string_length ( buffer );
		
//							ui_draw_alpha_graphic (218 + screen_x_offset, 178 + screen_y_offset, 204 + screen_x_offset, 126 + screen_y_offset,
//															(unsigned short int *) get_graphics_file_data ( GRAPHICS_UI_COMMON_APACHE_HAVOC_V ) );
		
							x = (218 + (204 / 2)) - ( string_length / 2 );
				
							ui_display_text (buffer, x + screen_x_offset, 246 + screen_y_offset);
			
							break;
						}
						case GAME_EXIT_KICKOUT:
						case GAME_EXIT_PILOT_EJECTED:
						{

							break;
						}

						default:
						{

							debug_fatal ("GAMEEXIT: Illegal exit type %d", game_exit_type);
						}
					}

					break;
				}
			}

			end_3d_scene (); //unlock_screen (active_screen);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pilot_ejected_events (void)
{

	set_event (DIK_SPACE, MODIFIER_NONE, KEY_STATE_DOWN, exit_game_function);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
