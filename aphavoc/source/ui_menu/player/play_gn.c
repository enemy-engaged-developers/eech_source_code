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

ui_object
	*general_log_area,

	*general_log_text_list_area,
	*general_log_text_list,
	*general_log_output_list_area,
	*general_log_output_list;
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_general_log_page (ui_object *obj)
{

	display_player_log_page (LOG_PAGE_GENERAL);

	#if DEBUG_MODULE
		debug_filtered_log("Inside show_general_log_page");
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rebuild_general_log_list (player_log_type *player_log, int side)
{
	char
		buf [100];

		float
			float_flying_hours;

		set_ui_list_spacing_proportional_to_font (general_log_text_list, -0.2);

		set_ui_list_spacing_proportional_to_font (general_log_output_list, -0.2);

		ui_object_destroy_list_items (general_log_text_list);

		ui_object_destroy_list_items (general_log_output_list);

		if ( ( player_log->name ) && ( strlen ( player_log->name ) > 0 ) )
		{

			direct_play_set_player_name ( player_log->name );
		}

		// Air kills
		add_to_pop_up_list (get_trans ("Air Kills"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		sprintf (buf, "%d", player_log->side_log[side].kills.air );

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		// Ground kills
		sprintf (buf, "%d", player_log->side_log[side].kills.ground );

		add_to_pop_up_list (get_trans ("Ground Kills"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		// Sea kills
		sprintf (buf, "%d", player_log->side_log[side].kills.sea );

		add_to_pop_up_list (get_trans ("Sea Kills"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);


		add_to_pop_up_list ("   ", general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_10), ui_option_title_text_colour);

		add_to_pop_up_list ("   ", general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_10), ui_option_title_text_colour);


		// Deaths
		sprintf (buf, "%d", player_log->side_log[side].kills.deaths );

		add_to_pop_up_list (get_trans ("KIA"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		// Fratricides
		sprintf (buf, "%d", player_log->side_log[side].kills.friendly );

		add_to_pop_up_list (get_trans ("Fratricides"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);


		add_to_pop_up_list ("   ", general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_10), ui_option_title_text_colour);

		add_to_pop_up_list ("   ", general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_10), ui_option_title_text_colour);


		//
		// Flying hours
		debug_log ( "Flying seconds: %f", player_log->side_log[side].flying_seconds );

		float_flying_hours = ((float) (player_log->side_log[side].flying_seconds / ONE_HOUR ));

		sprintf (buf, "%.1f", float_flying_hours );

		add_to_pop_up_list (get_trans ("Flying Hours"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		// Successful tours
		sprintf (buf, "%d", player_log->side_log[side].successful_tours );

		add_to_pop_up_list (get_trans ("Successful Tours"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		// Failed tours
		sprintf (buf, "%d", player_log->side_log[side].failed_tours );

		add_to_pop_up_list (get_trans ("Failed Tours"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);


		add_to_pop_up_list ("   ", general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_10), ui_option_title_text_colour);

		add_to_pop_up_list ("   ", general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_10), ui_option_title_text_colour);


		// Missions flown
		sprintf (buf, "%d", player_log->side_log[side].missions_flown );

		add_to_pop_up_list (get_trans ("Missions Flown"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		// Success rate
		sprintf (buf, "%d%%", (int) (player_log->side_log[side].mission_success_rate * 100.0));

		add_to_pop_up_list (get_trans ("Success Rate"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

		// Total points
//		sprintf (buf, "%d", ( int ) ( player_log->side_log[side].experience ));

//		add_to_pop_up_list (get_trans ("Total Points"), general_log_text_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

//		add_to_pop_up_list (buf, general_log_output_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_16), ui_option_title_text_colour);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_general_log_page_objects (void)
{

	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	/////////////////////////////////////////////////////////////////
	// general Log Area

	x1 = 0.623;
	y1 = 0.286;
//	x2 = 0.271;
	x2 = 0.3;
	y2 = 0.464;

	log_page [LOG_PAGE_GENERAL] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (select_player_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_END
			);

	page = log_page [LOG_PAGE_GENERAL];

	/////////////////////////////////////////////////////////////////
	// Text List Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 0.745;
	x2 = 0.85;
	y2 = 1.0;

	general_log_text_list_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Text List Object

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	general_log_text_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (general_log_text_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_16)),
  				   UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      			UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	/////////////////////////////////////////////////////////////////
	// Output List Area

	x2 = 0.745;
	x1 = 0.85;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	general_log_output_list_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_TEXT_JUSTIFY ( TEXT_JUSTIFY_RIGHT_CENTRE ),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Output List Object

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	general_log_output_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (general_log_output_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_16)),
  				   UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      			UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


