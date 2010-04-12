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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	string [128];

static float
	flash_timer = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_infobar_timers (void)
{
	flash_timer += get_delta_time ();
	
	flash_timer = frac (flash_timer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_campaign_time (ui_object *obj, void *arg)
{
	float
		time;

	int
		day,
		hours,
		minutes,
		seconds;

	static char
		s [128];

	ASSERT (get_session_entity ());

	day = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY);

	time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	get_digital_clock_int_values (time, &hours, &minutes, &seconds);

	sprintf (s, "%s %d\n%02d:%02d:%02d", get_trans ("Day"), day, hours, minutes, seconds);

	set_ui_object_text (obj, s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_campaign_time_acceleration (ui_object *obj, void *arg)
{
	static char
		s [16];

	if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		if (flash_timer < 0.5)
		{
			sprintf (s, "II");
		}
		else
		{
			sprintf (s, "");
		}
	}
	else
	{
		sprintf (s, "x%d", get_time_acceleration ());
	}

	set_ui_object_text (obj, s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_campaign_current_message (ui_object *obj, void *arg)
{
	message_log_type
		*message;

	rgb_colour
		*col = NULL;

	set_ui_object_text (obj, "");

	if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		return;
	}

	if (!get_ui_mouse_over_entity ())
	{
		message = get_current_display_message ();
	
		if (message)
		{
			ASSERT (message->string);
	
			col = &(message->colour);
			
			set_ui_object_font_colour (obj, col->r, col->g, col->b, col->a);
	
			set_ui_object_text (obj, message->string);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

static void draw_campaign_frame_rate (ui_object *obj, void *arg)
{
	static char
		s [16];

	sprintf (s, "FR: %.1f", 1.0 / get_delta_time_average ());

	set_ui_object_text (obj, s);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_common_paused_area (ui_object *obj, void *arg)
{
	set_ui_object_text (obj, "");

	if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		if (flash_timer > 0.5)
		{
		}
		else
		{
			set_ui_object_text (obj, get_trans ("Paused"));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_log_button(ui_object *obj, void *arg)
{
	if ((get_game_type () == GAME_TYPE_CAMPAIGN) || (get_game_type () == GAME_TYPE_SKIRMISH))
	{
		show_log_page ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_mouse_over_task_entity_description (entity *en, ui_object *area1, ui_object *area2)
{
	float
		expire_timer;

	int
		hours,
		minutes,
		seconds;

	entity
		*guide,
		*group,
		*company;

	ASSERT (en);

	switch (get_local_entity_int_value (en, INT_TYPE_TASK_STATE))
	{
		case TASK_STATE_UNASSIGNED:
		{
			//
			// Area 1 - Mission Name + Unassigned
			//
	
			sprintf (string, "%s: %s #%d - %s: %s",
								get_trans ("Mission"),
								get_trans (get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME)),
								get_local_entity_int_value (en, INT_TYPE_TASK_ID),
								get_trans ("Status"),
								get_trans ("Unassigned"));
	
			set_ui_object_text (area1, string);
	
			set_ui_object_drawable (area1, TRUE);
	
			break;
		}

		case TASK_STATE_ASSIGNED:
		{
			//
			// Area 1 - Mission Name + Status + Elapsed Time
			//
	
			expire_timer = get_local_entity_float_value (en, FLOAT_TYPE_ELAPSED_MISSION_TIME);
	
			expire_timer = min (expire_timer, (float) ONE_DAY);
	
			get_digital_countdown_values (expire_timer, NULL, &hours, &minutes, &seconds);
		
			sprintf (string, "%s: %s #%d - %s: %s - %s: %02d:%02d:%02d",
								get_trans ("Mission"),
								get_trans (get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME)),
								get_local_entity_int_value (en, INT_TYPE_TASK_ID),
								get_trans ("Status"),
								get_trans (task_status_names [get_local_entity_int_value (en, INT_TYPE_TASK_COMPLETED)]),
								get_trans ("Elapsed Time"),
								hours, minutes, seconds);
	
			set_ui_object_text (area1, string);
	
			set_ui_object_drawable (area1, TRUE);
	
			//
			// Area 2 - Group Name
			//
	
			guide = get_local_entity_first_child (en, LIST_TYPE_GUIDE);
	
			ASSERT (guide);
	
			group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);
	
			ASSERT (group);
		
			company = get_local_entity_parent (group, LIST_TYPE_DIVISION);
	
			ASSERT (company);
	
			sprintf (string, "%s: %s, %s",
								get_trans ("Assigned To"),
								get_local_entity_string (group, STRING_TYPE_DIVISION_NAME),
								get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));
	
			set_ui_object_text (area2, string);
	
			set_ui_object_drawable (area2, TRUE);

			break;
		}

		case TASK_STATE_COMPLETED:
		{
			//
			// Area 1 - Mission Name + Result
			//
	
			sprintf (string, "%s: %s #%d - %s: %s",
								get_trans ("Mission"),
								get_trans (get_local_entity_string (en, STRING_TYPE_SHORT_DISPLAY_NAME)),
								get_local_entity_int_value (en, INT_TYPE_TASK_ID),
								get_trans ("Status"),
								get_trans (task_debrief_result_names [get_local_entity_int_value (en, INT_TYPE_TASK_COMPLETED)]));
	
			set_ui_object_text (area1, string);
	
			set_ui_object_drawable (area1, TRUE);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_mouse_over_keysite_entity_description (entity *en, ui_object *area1, ui_object *area2)
{
	int
		status;

	float
		ammo,
		fuel;

	entity_sub_types
		sub_type;

	static char
		buf [128];

	ASSERT (en);

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	if (get_local_entity_int_value (en, INT_TYPE_SIDE) == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
	{
		//
		// Allied
		//
		
		//
		// Area 1 - Keysite Name + Status
		//
	
		status = get_local_entity_int_value (en, INT_TYPE_KEYSITE_USABLE_STATE);
	
		sprintf (string, "%s - %s: %s",
							get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME),
							get_trans ("Status"),
							get_trans (keysite_usable_state_names [status]));

		set_ui_object_text (area1, string);

		set_ui_object_drawable (area1, TRUE);

		//
		// Area 2 - Supplies
		//

		sprintf (string, "");

		if (keysite_database [sub_type].report_ammo_level)
		{
			ammo = get_local_entity_float_value (en, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

			sprintf (buf, "%s: %.0f%%   ", get_trans ("Ammo"), ammo);

			strcat (string, buf);
		}

		if (keysite_database [sub_type].report_fuel_level)
		{
			fuel = get_local_entity_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

			sprintf (buf, "%s: %.0f%%", get_trans ("Fuel"), fuel);

			strcat (string, buf);
		}

		set_ui_object_text (area2, string);
	
		set_ui_object_drawable (area2, TRUE);
	}
	else
	{
		//
		// Enemy
		//
		
		//
		// Area 1 - Keysite Name 
		//
	
		sprintf (string, "%s", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME));

		set_ui_object_text (area1, string);

		set_ui_object_drawable (area1, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_mouse_over_waypoint_entity_description (entity *en, ui_object *area1, ui_object *area2)
{
	ASSERT (en);

	//
	// Area 1 - Waypoint ID + Type
	//
	
	sprintf (string, "%s %c - %s",
							get_trans ("Waypoint"),
							get_local_entity_char_value (en, CHAR_TYPE_TAG),
							get_local_entity_string (en, STRING_TYPE_FULL_NAME));

	set_ui_object_text (area1, string);

	set_ui_object_drawable (area1, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_mouse_over_group_entity_description (entity *en, ui_object *area1, ui_object *area2)
{
	float
		expire_timer;

	int
		hours,
		minutes,
		seconds;

	entity
		*mission,
		*company;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_SIDE) == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
	{
		//
		// Allied
		//
		
		company = get_local_entity_parent (en, LIST_TYPE_DIVISION);
	
		ASSERT (company);
	
		//
		// Area 1 - Group Name + Type
		//
	
		sprintf (string, "%s, %s - %s",
								get_local_entity_string (en, STRING_TYPE_DIVISION_NAME),
								get_local_entity_string (company, STRING_TYPE_DIVISION_NAME),
								get_trans (get_local_entity_string (en, STRING_TYPE_FULL_NAME)));
	
		set_ui_object_text (area1, string);
	
		set_ui_object_drawable (area1, TRUE);
	
		mission = get_local_group_primary_task (en);
	
		if (mission)
		{
			//
			// Area 2 - Mission Name + Elapsed Time
			//
	
			if (get_local_entity_int_value (mission, INT_TYPE_TASK_COMPLETED) == TASK_INCOMPLETE)
			{
				expire_timer = get_local_entity_float_value (mission, FLOAT_TYPE_ELAPSED_MISSION_TIME);
		
				expire_timer = min (expire_timer, (float) ONE_DAY);
		
				get_digital_countdown_values (expire_timer, NULL, &hours, &minutes, &seconds);
			
				sprintf (string, "%s: %s #%d - %s: %02d:%02d:%02d",
									get_trans ("Mission"),
									get_trans (get_local_entity_string (mission, STRING_TYPE_SHORT_DISPLAY_NAME)),
									get_local_entity_int_value (mission, INT_TYPE_TASK_ID),
									get_trans ("Elapsed Time"),
									hours, minutes, seconds);
			}
			else
			{
				sprintf (string, "%s: %s #%d - %s",
									get_trans ("Mission"),
									get_trans (get_local_entity_string (mission, STRING_TYPE_SHORT_DISPLAY_NAME)),
									get_local_entity_int_value (mission, INT_TYPE_TASK_ID),
									get_trans (task_debrief_result_names [get_local_entity_int_value (mission, INT_TYPE_TASK_COMPLETED)]));
			}
			
			set_ui_object_text (area2, string);
	
			set_ui_object_drawable (area2, TRUE);
		}
	}
	else
	{
		//
		// Enemy
		//
		
		//
		// Area 1 - Group Type
		//
	
		sprintf (string, "%s", get_trans (get_local_entity_string (en, STRING_TYPE_FULL_NAME)));
	
		set_ui_object_text (area1, string);
	
		set_ui_object_drawable (area1, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_mouse_over_mobile_entity_description (entity *en, ui_object *area1, ui_object *area2)
{
	entity
		*group,
		*mission,
		*company;

	ASSERT (en);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);
		
	if (get_local_entity_int_value (en, INT_TYPE_SIDE) == get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE))
	{
		//
		// Allied
		//

		company = get_local_entity_parent (group, LIST_TYPE_DIVISION);
	
		ASSERT (company);
	
		//
		// Area 1 - Entity name + Group Name
		//
	
		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
		{
			sprintf (string, "%s - %s 1-%d, %s",
								get_trans (get_local_entity_string (en, STRING_TYPE_FULL_NAME)),
								get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN),
								get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_ID),
								get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));
		}
		else
		{
			sprintf (string, "%s - %s, %s",
								get_trans (get_local_entity_string (en, STRING_TYPE_FULL_NAME)),
								get_local_entity_string (group, STRING_TYPE_DIVISION_NAME),
								get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));
		}

		set_ui_object_text (area1, string);
	
		set_ui_object_drawable (area1, TRUE);
	
		mission = get_local_group_primary_task (group);
	
		if (mission)
		{
			//
			// Area 2 - Mission Name + Status
			//
	
			sprintf (string, "%s: %s #%d - %s: %s",
								get_trans ("Mission"),
								get_trans (get_local_entity_string (mission, STRING_TYPE_SHORT_DISPLAY_NAME)),
								get_local_entity_int_value (mission, INT_TYPE_TASK_ID),
								get_trans ("Status"),
								get_trans (group_member_state_names [get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_STATE)]));
	
			set_ui_object_text (area2, string);
	
			set_ui_object_drawable (area2, TRUE);
		}
	}
	else
	{
		//
		// Enemy
		//
		
		//
		// Area 1 - Group Type
		//
	
		sprintf (string, "%s", get_trans (get_local_entity_string (group, STRING_TYPE_FULL_NAME)));
	
		set_ui_object_text (area1, string);
	
		set_ui_object_drawable (area1, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_mouse_over_description_area (ui_object *obj, void *arg)
{
	entity
		*en;

	ui_object
		*area1,
		*area2;

	en = get_ui_mouse_over_entity ();

	ASSERT (obj);
	
	area1 = (ui_object *) get_ui_object_user_ptr (obj);

	ASSERT (area1);

	area2 = (ui_object *) get_ui_object_user_ptr (area1);

	ASSERT (area2);

	set_ui_object_drawable (area1, FALSE);
	set_ui_object_drawable (area2, FALSE);

	draw_common_paused_area (obj, arg);

	if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		return;
	}

	if (en)
	{
		switch (get_local_entity_type (en))
		{
			case ENTITY_TYPE_TASK:
			{
				display_mouse_over_task_entity_description (en, area1, area2);
	
				break;
			}
			case ENTITY_TYPE_KEYSITE:
			{
				display_mouse_over_keysite_entity_description (en, area1, area2);
	
				break;
			}
			case ENTITY_TYPE_GROUP:
			{
				display_mouse_over_group_entity_description (en, area1, area2);
	
				break;
			}
			case ENTITY_TYPE_WAYPOINT:
			{
				display_mouse_over_waypoint_entity_description (en, area1, area2);
	
				break;
			}
			default:
			{
				if ((get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT)) ||
						(get_local_entity_int_value (en, INT_TYPE_IDENTIFY_VEHICLE)))
				{
					display_mouse_over_mobile_entity_description (en, area1, area2);
				}
	
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_info_bar_objects (ui_object *parent)
{
	float
		x1,
		y1,
		x2,
		y2;

	ui_object
		*mouse_over_description_area,
		*area1,
		*area2;

	ASSERT (parent);

	/////////////////////////////////////////////////////////////////
	// Time / Last Log Message
	/////////////////////////////////////////////////////////////////

	y1 = 0.0;
	y2 = 1.0;

	x1 = 0.0;
	x2 = 0.054;

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (parent),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_DRAW_FUNCTION (draw_campaign_time_acceleration),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.054;
	x2 = 0.155;

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (parent),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_DRAW_FUNCTION (draw_campaign_time),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.155;
	x2 = 1.0;

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (parent),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
			UI_ATTR_FUNCTION (notify_log_button),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_DRAW_FUNCTION (draw_campaign_current_message),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	#ifdef DEBUG

	x1 = 0.9f;
	x2 = 1.0;

	create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (parent),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_DRAW_FUNCTION (draw_campaign_frame_rate),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	#endif

	/////////////////////////////////////////////////////////////////
	// Mouse-Over "Tool-Tip"
	/////////////////////////////////////////////////////////////////

	x1 = 0.155;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

	mouse_over_description_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (parent),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
			UI_ATTR_FONT_COLOUR (ui_ingame_dead_text_colour.r, ui_ingame_dead_text_colour.g, ui_ingame_dead_text_colour.b, ui_ingame_dead_text_colour.a),
			UI_ATTR_DRAW_FUNCTION (draw_mouse_over_description_area),
			UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	x1 = 0.01f;
	x2 = 0.9f;

	y1 = 0.0;
	y2 = 0.5;

	area1 = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (mouse_over_description_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (""),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
			UI_ATTR_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	set_ui_object_user_ptr (mouse_over_description_area, area1);

	/////////////////////////////////////////////////////////////////

	x1 = 0.01f;
	x2 = 0.9f;

	y1 = 0.5;
	y2 = 1.0;

	area2 = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (mouse_over_description_area),
			UI_ATTR_VIRTUAL_POSITION (x1, y1),
			UI_ATTR_VIRTUAL_SIZE (x2 - x1, y2 - y1),
			UI_ATTR_TEXT (""),
			UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
			UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_10),
			UI_ATTR_FONT_COLOUR (ui_ingame_highlight_text_colour.r, ui_ingame_highlight_text_colour.g, ui_ingame_highlight_text_colour.b, ui_ingame_highlight_text_colour.a),
			UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_NONE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	set_ui_object_user_ptr (area1, area2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
