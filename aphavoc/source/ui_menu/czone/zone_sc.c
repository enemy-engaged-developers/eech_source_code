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

ui_object
	*combat_zone_text_area,
	*combat_zone_screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	valid_combat_zone;

static int
	briefing_red_forces = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_combat_zone_screen (ui_object *obj, void *arg);

static void notify_combat_zone_next_button (ui_object *obj, void *arg);

static void notify_combat_zone_back_button (ui_object *obj, void *arg);

static int combat_zone_read_text (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_combat_zone_screen (void)
{

   combat_zone_screen = create_ui_object
            (
               UI_TYPE_SCREEN,
               UI_ATTR_POSITION (0, 0),
               UI_ATTR_SIZE (640, 480),
					//UI_ATTR_GRAPHIC ( get_graphics_file_data ( GRAPHICS_UI_APACHE_CZONE_SCREEN ) ),
					UI_ATTR_FUNCTION (notify_combat_zone_screen),
               UI_ATTR_END
            );

	combat_zone_text_area = create_ui_object
            (
               UI_TYPE_AREA,
               UI_ATTR_PARENT (combat_zone_screen),
               UI_ATTR_POSITION (10, 20),
               UI_ATTR_SIZE (620, 420),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

   create_ui_object
            (
               UI_TYPE_BUTTON,
               UI_ATTR_PARENT (combat_zone_screen),
               UI_ATTR_POSITION (10, 442),
               UI_ATTR_SIZE (120, 28),
					UI_ATTR_FUNCTION (notify_combat_zone_back_button),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
					//UI_ATTR_ALPHA_GRAPHIC (get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED)),
               UI_ATTR_END
            );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_briefing_side ( int red_forces )
{

	briefing_red_forces = red_forces;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_combat_zone_screen (ui_object *obj, void *arg)
{

	ASSERT ( get_valid_current_game_session () );

	combat_zone_read_text ();

	if ( briefing_red_forces )
	{

		set_ui_object_graphic ( combat_zone_screen, ( unsigned short int * ) get_graphics_file_data ( GRAPHICS_UI_HAVOC_CZONE_SCREEN ) );
	}
	else
	{

		set_ui_object_graphic ( combat_zone_screen, ( unsigned short int * ) get_graphics_file_data ( GRAPHICS_UI_APACHE_CZONE_SCREEN ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_combat_zone_back_button (ui_object *obj, void *arg)
{

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED));

		set_ui_object_redraw (combat_zone_screen, TRUE);
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		pop_ui_screen (SCREEN_POP_ACTUAL);
	}
	else 
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		set_ui_object_redraw (combat_zone_screen, TRUE);
	}

	//set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_3d_terrain_game_data (void)
{

	char
		filename [1024];

	session_list_data_type
		*session;

	//
	// Load 3d terrain
	//

	unload_3d_terrain ();

	session = get_current_game_session ();

	sprintf (filename, "%s\\terrain", session->data_path);

	if (!load_3d_terrain (filename))
	{

		debug_fatal ("ZONE_FN: unable to load terrain");
	}

	//
	// Load 2d map
	//
	
	load_2d_terrain (session->data_path);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int combat_zone_read_text (void)
{

	ui_object
		*ui_line,
		*destroy_ui_line;

	int
		long_text_flag,
		value,
		line_count;

	FILE
		*file_ptr;

	char
		variable [64],
		operator_ [64],
		line [1024],
		filename [1024];

	file_tags
		tag;

	ui_line = get_ui_object_child (combat_zone_text_area);

	while (ui_line)
	{

		destroy_ui_line = ui_line;

		ui_line = get_ui_object_next (ui_line);

		destroy_ui_object (destroy_ui_line);
	}

	//
	//
	//

	line_count = 0;

	sprintf (filename, "%s\\%s\\%s", current_game_session->data_path, current_game_session->campaign_directory, current_game_session->campaign_filename);

	file_ptr = safe_fopen (filename, "r");

	long_text_flag = FALSE;

	while (TRUE)
	{

		tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

		switch (tag)
		{

			case FILE_TAG_LANGUAGE_TEXT_START:
			{

				get_next_file_word (file_ptr, operator_, sizeof (operator_));

				// skip script till correct language

				while (tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
				{

					#if (LANGUAGE == LANGUAGE_FRENCH)

					if (tag == FILE_TAG_LANGUAGE_FRENCH)
					{

						break;
					}
					#elif (LANGUAGE == LANGUAGE_GERMAN)

					if (tag == FILE_TAG_LANGUAGE_GERMAN)
					{

						break;
					}
					#elif (LANGUAGE == LANGUAGE_ITALIAN)

					if (tag == FILE_TAG_LANGUAGE_ITALIAN)
					{

						break;
					}
					#elif (LANGUAGE == LANGUAGE_SPANISH)

					if (tag == FILE_TAG_LANGUAGE_SPANISH)
					{

						break;
					}
					#else //LANGUAGE_ENGLISH

					if (tag == FILE_TAG_LANGUAGE_ENGLISH)
					{

						break;
					}
					#endif

					if (tag == FILE_TAG_LANGUAGE_TEXT_STOP)
					{

						break;
					}
				}

				break;
			}

			case FILE_TAG_LANGUAGE_TEXT_END:
			{

				get_next_file_word (file_ptr, operator_, sizeof (operator_));

				// skip script till end of languages

				while (tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
				{

					if (tag == FILE_TAG_LANGUAGE_TEXT_STOP)
					{

						break;
					}
				}

				break;
			}

			case FILE_TAG_LONG_TEXT_START:
			{

				long_text_flag = TRUE;

				while (TRUE)
				{

					get_next_file_string (file_ptr, line, sizeof (line));

					if (strcmp ((line + 1), application_tag_strings [FILE_TAG_TEXT_END]) == 0)
					{

						break;
					}

					create_ui_object
								(
									UI_TYPE_TEXT,
									UI_ATTR_PARENT (combat_zone_text_area),
									UI_ATTR_POSITION (10, (line_count + 1) * 12),
									UI_ATTR_TEXT (line),
									UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
									UI_ATTR_END
							  );

					line_count ++;
				}

				break;
			}

			case FILE_TAG_IF:
			{

				ASSERT (get_current_player_log ());
	
				get_next_file_word (file_ptr, variable, sizeof (variable));

				get_next_file_word (file_ptr, operator_, sizeof (operator_));

				value = get_next_file_int (file_ptr);

				if (!if_file_tag_variable (variable, operator_, value))
				{

					// skip script till endif

					while (tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG))
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

			case FILE_TAG_END:
			{

				fclose (file_ptr);

				return long_text_flag;
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
