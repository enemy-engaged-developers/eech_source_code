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

#define DEBUG_MODULE		0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	force_hardware_update;

static int
	display_timer_valid;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_force_entity (entity_sides side)
{

	entity
		*force;

	if (!get_session_entity ())
	{

		return NULL;
	}

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{

		debug_assert (get_local_entity_type (force) == ENTITY_TYPE_FORCE);

		if (get_local_entity_int_value (force, INT_TYPE_SIDE) == side)
		{

			return force;
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void add_force_campaign_critiera (entity *force_en, campaign_trigger criteria_type, int value1, int value2, int value3, int value4,
											campaign_result_types result, int experience_points, int rank_points, int *experience_variable, int *rank_variable)
{

	force
		*force_raw;

	campaign_trigger_type
		*new_campaign_trigger;

	force_raw = get_local_entity_data (force_en);

	new_campaign_criteria = (campaign_criteria_type *) malloc_heap_mem (sizeof (campaign_criteria_type));

	memset (new_campaign_criteria, 0, sizeof (campaign_criteria_type));

	new_campaign_criteria->criteria_type = criteria_type;

	new_campaign_criteria->valid = TRUE;

	new_campaign_criteria->value1 = value1;
	new_campaign_criteria->value2 = value2;
	new_campaign_criteria->value3 = value3;
	new_campaign_criteria->value4 = value4;

	new_campaign_criteria->result = result;

	new_campaign_criteria->experience_points = experience_points;
	new_campaign_criteria->experience_variable = experience_variable;

	new_campaign_criteria->rank_points = rank_points;
	new_campaign_criteria->rank_variable = rank_variable;

	new_campaign_criteria->next = force_raw->campaign_criteria;

	force_raw->campaign_criteria = new_campaign_criteria;

	#if DEBUG_MODULE

	debug_log ("FORCE: Campaign Criteria %s, value1 = %d value2 = %d value3 = %d value4 = %d, result %s", campaign_criteria_names [criteria_type],
								 value1, value2, value3, value4, campaign_result_names [result]);

	#endif
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
campaign_criteria_type *get_force_campaign_criteria (entity *force_en, campaign_criteria criteria_type, int sub_type)
{

	force
		*force_raw;
		
	campaign_criteria_type
		*this_criteria;

	force_raw = get_local_entity_data (force_en);

	this_criteria = force_raw->campaign_criteria;

	while (this_criteria)
	{

		if (this_criteria->criteria_type == criteria_type)
		{

			if ((sub_type == -1) || (this_criteria->type == sub_type))
			{

				return this_criteria;
			}
		}

		this_criteria = this_criteria->next;
	}

	return NULL;
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_to_force_info (entity *force_en, entity *new_en)
{

	force
		*raw;

	int
		index;

	if (!force_en)
	{

		return;
	}

	if (!get_force_hardware_update ())
	{

		return;
	}
		
	raw = get_local_entity_data (force_en);

	index = get_local_entity_int_value (new_en, INT_TYPE_FORCE_INFO_CATAGORY);

	raw->force_info_current_hardware [index] ++;

	if (get_game_status () == GAME_STATUS_INITIALISED)
	{

		raw->force_info_reserve_hardware [index] --;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_from_force_info (entity *force_en, entity *new_en)
{

	force
		*raw;

	int
		index;

	add_mobile_to_force_losses_stats (force_en, new_en);

	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{

		return;
	}
		
	raw = get_local_entity_data (force_en);

	index = get_local_entity_int_value (new_en, INT_TYPE_FORCE_INFO_CATAGORY);

	raw->force_info_current_hardware [index] --;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void replace_into_force_info (entity *force_en, entity *new_en)
{

	force
		*raw;

	int
		index;

	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{

		return;
	}
		
	raw = get_local_entity_data (force_en);

	index = get_local_entity_int_value (new_en, INT_TYPE_FORCE_INFO_CATAGORY);

	raw->force_info_reserve_hardware [index] ++;

	debug_log ("FORCE: adding %s (%d) back into the reserves", get_local_entity_type_name (new_en), get_local_entity_index (new_en));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_mobile_to_force_kills_stats (entity *en, entity *victim)
{
	force
		*raw;

	int
		sub_type;

	entity
		*group;

	ASSERT (en);

	ASSERT (victim);

	raw = get_local_entity_data (en);

	group = get_local_entity_parent (victim, LIST_TYPE_MEMBER);

	ASSERT (group);

	sub_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

	raw->kills [sub_type] ++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_mobile_to_force_losses_stats (entity *en, entity *victim)
{
	force
		*raw;

	int
		sub_type;

	entity
		*group;

	ASSERT (en);

	ASSERT (victim);

	raw = get_local_entity_data (en);

	group = get_local_entity_parent (victim, LIST_TYPE_MEMBER);

	ASSERT (group);

	sub_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

	raw->losses [sub_type] ++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_group_type_to_force_info (entity *en, entity_sub_types group_type)
{
	force
		*raw;
		
	ASSERT (en);

	raw = get_local_entity_data (en);

	raw->group_count [group_type] ++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_group_type_from_force_info (entity *en, entity_sub_types group_type)
{
	force
		*raw;
		
	ASSERT (en);

	raw = get_local_entity_data (en);

	ASSERT (raw->group_count [group_type] > 0);

	raw->group_count [group_type] --;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_force_entity_group_count (entity *en, entity_sub_types group_type)
{
	force
		*raw;
		
	ASSERT (en);

	raw = get_local_entity_data (en);

	return (raw->group_count [group_type]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_campaign_criteria_time_remaining (void)
{
#if 0
	entity
		*force_en;

	force
		*force_raw;

	//session
		//*session_raw;

	//campaign_criteria_type
		//*this_campaign_criteria;

	//float
		//elapsed_hours,
		//elapsed_minutes,
		//elapsed_seconds;

	//int
		//remaining_hours,
		//remaining_minutes,
		//remaining_seconds;

	//int
		//x, y;

	//char
		//s [20];

	//
	// display count down timer until campaign completiion (NOT "tour of duty" timer)
	//

	//
	// currently used only for special games, so I have tailored it to suit :-
	// only displays minutes and seconds,
	// doesn't display on the clients until after first time-of-day resync
	//

	if ((get_game_type () != GAME_TYPE_SPECIAL) && (get_game_type () != GAME_TYPE_MAGAZINE_DEMO))
	{

		return;
	}

	ASSERT (get_session_entity ());

	force_en = get_local_force_entity (get_global_gunship_side ());

	ASSERT (force_en);

	force_raw = get_local_entity_data (force_en);
/*
	this_campaign_criteria = force_raw->campaign_criteria;

	while (this_campaign_criteria)
	{
		if (this_campaign_criteria->criteria_type == CAMPAIGN_CRITERIA_TIME_DURATION)
		{
			break;
		}

		this_campaign_criteria = this_campaign_criteria->next;
	}

	if (this_campaign_criteria)
	{
		if (this_campaign_criteria->valid)
		{
			session_raw = get_local_entity_data (get_session_entity ());

			//
			// clients don't display until AFTER first resync (otherwise time will be wrong)
			//

			if (get_comms_model () == COMMS_MODEL_CLIENT)
			{
				if (!display_timer_valid)
				{
					return;
				}
			}

			//
			// get time remaining 
			//

			get_digital_clock_values (session_raw->elapsed_time_of_day, &elapsed_hours, &elapsed_minutes, &elapsed_seconds);

			remaining_seconds = (this_campaign_criteria->days - session_raw->elapsed_days) * ONE_DAY;

			remaining_seconds += (this_campaign_criteria->hours - elapsed_hours) * ONE_HOUR;

			remaining_seconds += (this_campaign_criteria->minutes - elapsed_minutes) * ONE_MINUTE;

			remaining_seconds += (this_campaign_criteria->seconds - elapsed_seconds) * ONE_SECOND;

			if ((remaining_seconds > 0.0) && (remaining_seconds < ONE_HOUR))
			{
				if (remaining_seconds < ONE_MINUTE)
				{
					if (remaining_seconds < 10.0)
					{
						//
						// flash if < 10 seconds
						//
					
						if (frac (session_raw->elapsed_time_of_day) < 0.5)
						{
							return;
						}
					}

					set_ui_font (UI_FONT_ADS_15_ORANGE);
				}
				else
				{
					set_ui_font (UI_FONT_ADS_15_WHITE);
				}

				get_digital_clock_int_values (remaining_seconds, &remaining_hours, &remaining_minutes, &remaining_seconds);

				if (lock_screen (active_screen))
				{
					set_full_screen_viewport ();

					sprintf (s, "T-%02d:%02d", remaining_minutes, remaining_seconds);

					// string WAS right-justified, but looked bad due to proportional fonts changing the width every second !
//					x = get_screen_width (active_screen) - ui_get_string_length (s);
					x = get_screen_width (active_screen) - 62;

					y = ui_get_font_height () + 2;

					ui_display_text (s, x, y);

					unlock_screen (active_screen);
				}
			}
		}
	}
	*/
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_display_campaign_timer_valid (int valid)
{
	display_timer_valid = valid;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
