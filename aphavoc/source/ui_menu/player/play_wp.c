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
	*weapon_log_area,
	*weapon_log_text_area,

	*weapon_list_area,
	*weapon_type_list,
	*weapon_hit_list,
	*weapon_fired_list,
	*weapon_eff_list;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_show_weapon_log_page (ui_object *obj)
{

	display_player_log_page (LOG_PAGE_WEAPON);

	#if DEBUG_MODULE
		debug_filtered_log("Inside show_weapon_log_page");
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rebuild_weapon_log_list (player_log_type *log, int side)
{
	ui_object
		*temp;

	char
		buff[7];
		
	int
		eff,
		weapon,
		count = 0;
 
	ui_object_destroy_list_items (weapon_type_list);

	ui_object_destroy_list_items (weapon_fired_list);

	ui_object_destroy_list_items (weapon_hit_list);

	ui_object_destroy_list_items (weapon_eff_list);

	temp = add_to_pop_up_list (get_trans ("WEAPON"), weapon_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	temp = add_to_pop_up_list (get_trans ("FIRED"), weapon_fired_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	temp = add_to_pop_up_list (get_trans ("HIT"), weapon_hit_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	temp = add_to_pop_up_list (get_trans ("EFF"), weapon_eff_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	temp = add_to_pop_up_list (" ", weapon_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	temp = add_to_pop_up_list (" ", weapon_fired_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	temp = add_to_pop_up_list (" ", weapon_hit_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);

	temp = add_to_pop_up_list (" ", weapon_eff_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);


	while (count < NUM_ENTITY_SUB_TYPE_WEAPONS)
	{
		if	(log->side_log[side].weapon_usage[count][WEAPON_LOG_FIRED])
		{
			weapon = log->side_log[side].weapon_usage[count][WEAPON_LOG_FIRED];
			
			if ( (count == ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER) ||
					(count == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) ||
					(count == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II) ||
					(count == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) ||
					(count == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261) ||
					(count == ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND) ||
					(count == ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND) ||
					(count == ENTITY_SUB_TYPE_WEAPON_IGLA_V) ||
					(count == ENTITY_SUB_TYPE_WEAPON_S8) ||
					(count == ENTITY_SUB_TYPE_WEAPON_S13) ||
					(count == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND) ||
					(count == ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND) ||
					(count == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND) ||
					(count == ENTITY_SUB_TYPE_WEAPON_ATAKA) ||
					(count == ENTITY_SUB_TYPE_WEAPON_VIKHR)
				)
			{
			
				temp = add_to_pop_up_list (weapon_database[count].weapon_loading_list_name, weapon_type_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	
				sprintf (buff, "%d", log->side_log[side].weapon_usage[count][WEAPON_LOG_FIRED]);
	
				temp = add_to_pop_up_list (buff, weapon_fired_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	
				sprintf (buff, "%d", log->side_log[side].weapon_usage[count][WEAPON_LOG_HIT]);
	
				temp = add_to_pop_up_list (buff, weapon_hit_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	
				if (log->side_log[side].weapon_usage[count][WEAPON_LOG_FIRED])
				{
					eff = (int) ((100 * log->side_log[side].weapon_usage[count][WEAPON_LOG_HIT]) / log->side_log[side].weapon_usage[count][WEAPON_LOG_FIRED]);
				}
				else
				{
					eff = 0;
				}
				
				sprintf (buff, "%d%%", eff);
	
				temp = add_to_pop_up_list (buff, weapon_eff_list, NULL, ENTITY_INDEX_DONT_CARE, get_current_language_font (UI_FONT_ARIAL_14), ui_option_title_text_colour);
	
			}
		}

		count++;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_weapon_log_page_objects (void)
{

	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*page;

	/////////////////////////////////////////////////////////////////
	// Weapon Log Area

	x1 = 0.511;
	x1 = 0.470;
	y1 = 0.332;
	x2 = 0.489;
	x2 = 0.530;
	y2 = 0.350;

	log_page [LOG_PAGE_WEAPON] = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (select_player_screen),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_DRAWABLE (FALSE),
				UI_ATTR_END
			);

	page = log_page [LOG_PAGE_WEAPON];

	/////////////////////////////////////////////////////////////////
	// Weapon List Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	weapon_list_area = create_ui_object
			(
				UI_TYPE_AREA,
				UI_ATTR_PARENT (page),
				UI_ATTR_VIRTUAL_POSITION (x1, y1),
				UI_ATTR_VIRTUAL_SIZE (x2, y2),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);

	/////////////////////////////////////////////////////////////////
	// Weapon Type List Object

	x1 = 0.1;
	y1 = 0.0;
	x2 = 0.250;
	y2 = 1.0;

	weapon_type_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (weapon_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_14)),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	set_ui_list_spacing_proportional_to_font (weapon_type_list, -0.2);

	/////////////////////////////////////////////////////////////////
	// Weapon Fired List Object

	x1 = 0.35;
	y1 = 0.0;
	x2 = 0.250;
	y2 = 1.0;

	weapon_fired_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (weapon_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_14)),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	set_ui_list_spacing_proportional_to_font (weapon_fired_list, -0.2);

	/////////////////////////////////////////////////////////////////
	// Weapon Hit List Object

	x1 = 0.6;
	y1 = 0.0;
	x2 = 0.240;
	y2 = 1.0;

	weapon_hit_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (weapon_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_14)),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	set_ui_list_spacing_proportional_to_font (weapon_hit_list, -0.2);

	/////////////////////////////////////////////////////////////////
	// Weapon Eff List Object

	x1 = 0.739;
	x1 = 0.840;
	y1 = 0.0;
	x2 = 0.140;
	y2 = 1.0;

	weapon_eff_list = create_ui_object
				(
					UI_TYPE_LIST_BOX,
					UI_ATTR_PARENT (weapon_list_area),
					UI_ATTR_VIRTUAL_POSITION (x1, y1),
					UI_ATTR_VIRTUAL_SIZE (x2, y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_FONT_TYPE (get_current_language_font (UI_FONT_ARIAL_14)),
					UI_ATTR_ITEM_NUMBER (-2),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
					UI_ATTR_END
				);

	set_ui_list_spacing_proportional_to_font (weapon_eff_list, -0.2);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


