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

enum
{
	PLAYER_HELICOPTER_HOURS,
	PLAYER_WARZONE_HOURS
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ui_object
	*flight_hours_text_area,

	*gunship_type_list,
	*gunship_missions_list,
	*gunship_hours_list;

static int
	hours_type = PLAYER_HELICOPTER_HOURS;
//	hours_type = PLAYER_WARZONE_HOURS;

/*static session_list_data_type*
	last_session = NULL;*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

player_warzone_log* get_current_warzone_log(player_log_type *log, int side)
{
	/*
	player_warzone_log* warzone, *last_warzone = NULL;
	session_list_data_type* session = get_current_game_session();
	const char* warzone_name;
	
	if (!log || !session)
		return NULL;

	warzone_name = session->warzone_name;

	debug_log("warzone name: %s, title: %s, display_title: %s", warzone_name, session->title, session->displayed_title);

	for (warzone = log->side_log[side].warzone_log; warzone; warzone = warzone->next)
	{
		if (strcmp(warzone_name, warzone->warzone_name) == 0)
		{
			debug_log("found log for %s with %.2f seconds", warzone->warzone_name, warzone->flying_seconds);
			return warzone;
		}

		last_warzone = warzone;
	}

	debug_log("creating new log for %s", warzone_name);

	// we don't have any log for this zone yet, create it
	warzone = malloc_heap_mem(sizeof(player_warzone_log));
	memset(warzone, 0, sizeof(player_warzone_log));

	// set name
	warzone->warzone_name = malloc_heap_mem(sizeof(warzone_name));
	strcpy(warzone->warzone_name, warzone_name);

	// insert it last
	if (last_warzone)
		last_warzone->next = warzone;
	else
		log->side_log[side].warzone_log = warzone;

	return warzone;
	*/
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_flight_hours_page (ui_object *obj)
{

	display_player_log_page (LOG_PAGE_FLIGHT_HOURS);

	#if DEBUG_MODULE
		debug_filtered_log("Inside show_weapon_log_page");
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rebuild_flight_hours_list (player_log_type *log, int side)
{
	int i;
	ui_object *temp;
	unsigned int hours, minutes, missions;
	char buff[12];
 
 	ui_object_destroy_list_items (gunship_type_list);
 	ui_object_destroy_list_items (gunship_missions_list);
  	ui_object_destroy_list_items (gunship_hours_list);

	if (hours_type == PLAYER_HELICOPTER_HOURS)
	{
		// headers
		temp = add_to_pop_up_list("Helicopter", gunship_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
		temp = add_to_pop_up_list("Miss.", gunship_missions_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
		temp = add_to_pop_up_list("Hours", gunship_hours_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

		for (i = 0; i < NUM_GUNSHIP_TYPES; i++)
		{
			gunship_types type = alphabetical_gunship_types[i];
			const char* gunship = long_gunship_names[type];
	
			hours = (int)(log->side_log[side].gunship_flying_seconds[type] / ONE_HOUR);
			minutes = (int)(log->side_log[side].gunship_flying_seconds[type] / ONE_MINUTE) % 60;
			missions = log->side_log[side].gunship_missions[type];
	
			if (hours == 0 && minutes == 0)
				continue;
			
			// add row for helicopter type
			temp = add_to_pop_up_list (gunship, gunship_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
			sprintf(buff, "%d", missions);
			temp = add_to_pop_up_list (buff, gunship_missions_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
			sprintf(buff, "%d:%02d", hours, minutes);
			temp = add_to_pop_up_list (buff, gunship_hours_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
		}
	}
	else
	{
		player_warzone_log* warzone = log->side_log[side].warzone_log;
		
		// headers
		temp = add_to_pop_up_list("Theater", gunship_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
		temp = add_to_pop_up_list("Miss.", gunship_missions_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
		temp = add_to_pop_up_list("Hours", gunship_hours_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

		for (; warzone; warzone = warzone->next)
		{
			hours = (int)(warzone->flying_seconds / ONE_HOUR);
			minutes = (int)(warzone->flying_seconds / ONE_MINUTE) % 60;
				
			// add row for warzone
			temp = add_to_pop_up_list (warzone->warzone_name, gunship_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
			sprintf(buff, "%d", warzone->missions);
			temp = add_to_pop_up_list (buff, gunship_missions_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
			sprintf(buff, "%d:%02d", hours, minutes);
			temp = add_to_pop_up_list (buff, gunship_hours_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
		}
	}
	
	// empty row
	temp = add_to_pop_up_list ("", gunship_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	temp = add_to_pop_up_list ("", gunship_missions_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	temp = add_to_pop_up_list ("", gunship_hours_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	// total
	hours = (unsigned int)(log->side_log[side].flying_seconds / ONE_HOUR);
	minutes = (unsigned int)(log->side_log[side].flying_seconds / ONE_MINUTE) % 60;
	missions = log->side_log[side].missions_flown;
	
	temp = add_to_pop_up_list ("Total", gunship_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	sprintf(buff, "%d", missions);
	temp = add_to_pop_up_list (buff, gunship_missions_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	sprintf(buff, "%d:%02d", hours, minutes);
	temp = add_to_pop_up_list (buff, gunship_hours_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_flight_hours_page_objects (void)
{

	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	/////////////////////////////////////////////////////////////////
	// Flight hours Area

	x1 = 0.470;
	y1 = 0.280;
	x2 = 0.530;
	y2 = 0.400;

	log_page [LOG_PAGE_FLIGHT_HOURS] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (select_player_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_END
			);

	page = log_page [LOG_PAGE_FLIGHT_HOURS];

	/////////////////////////////////////////////////////////////////
	// Flight Hours List Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	flight_hours_text_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Gunship Type List Object

	x1 = 0.1;
	y1 = 0.0;
	x2 = 0.600;
	y2 = 1.0;

	gunship_type_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (flight_hours_text_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_14)),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	set_ui_list_spacing_proportional_to_font (gunship_type_list, -0.2);

	/////////////////////////////////////////////////////////////////
	// Missions List Object

	x1 = 0.62;
	y1 = 0.0;
	x2 = 0.12;
	y2 = 1.0;

	gunship_missions_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (flight_hours_text_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_14)),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	set_ui_list_spacing_proportional_to_font (gunship_missions_list, -0.2);

	/////////////////////////////////////////////////////////////////
	// Flight Hours List Object

	x1 = 0.75;
	y1 = 0.0;
	x2 = 0.250;
	y2 = 1.0;

	gunship_hours_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (flight_hours_text_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_14)),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	set_ui_list_spacing_proportional_to_font (gunship_hours_list, -0.2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
