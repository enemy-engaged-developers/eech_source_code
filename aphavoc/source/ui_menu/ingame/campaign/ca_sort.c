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

struct MISSION_LIST_SORT_TYPE
{
	entity
		*en;

	common_list_text_types
		text_type;

	entity_sub_types
		type;
};

typedef struct MISSION_LIST_SORT_TYPE mission_list_sort_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GROUP_LIST_SORT_TYPE
{
	entity
		*en;

	common_list_text_types
		text_type;

	entity_sub_types
		type;

	const char
		*name;
};

typedef struct GROUP_LIST_SORT_TYPE group_list_sort_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BASE_LIST_SORT_TYPE
{
	entity
		*en;

	common_list_text_types
		text_type;

	entity_sub_types
		type;

	const char
		*base_name;
};

typedef struct BASE_LIST_SORT_TYPE base_list_sort_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	mission_type_expanded [NUM_TASK_STATE_TYPES][NUM_ENTITY_SUB_TYPE_TASKS],
	group_type_expanded [NUM_GROUP_MODE_TYPES][NUM_ENTITY_SUB_TYPE_GROUPS],
	base_type_expanded [NUM_ENTITY_SUB_TYPE_KEYSITES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int common_list_classify_mission_text (entity *en);

static int common_list_classify_group_text (entity *en);

static int common_list_classify_base_text (entity *en);

static void sort_mission_list (mission_list_sort_type *sort_list, int *indices, int count);

static void sort_group_list (group_list_sort_type *sort_list, int *indices, int count);

static void sort_base_list (base_list_sort_type *sort_list, int *indices, int count);

static void quicksort_int (int *indices, int count, int *sort_order);

static void quicksort_string (int *indices, int count, const char **sort_order);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_sort_objects (void)
{
	int
		loop;

	for (loop = 0; loop < NUM_TASK_STATE_TYPES; loop ++)
	{
		memset (mission_type_expanded [loop], 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_TASKS);
	}

	for (loop = 0; loop < NUM_GROUP_MODE_TYPES; loop ++)
	{
		memset (group_type_expanded [loop], 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_GROUPS);
	}

	memset (base_type_expanded, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_KEYSITES);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int show_sorted_list_item (common_list_text_types text_type)
{
	if (!get_common_list_available_only_state ())
	{
		return TRUE;
	}

	if ((text_type == COMMON_LIST_TEXT_AVAILABLE) || (text_type == COMMON_LIST_TEXT_BUSY))
	{
		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int toggle_mission_type_collapse_state (int type, task_state_types state)
{
	ASSERT ((type >= 0) && (type < NUM_ENTITY_SUB_TYPE_TASKS));

	ASSERT ((state >= 0) && (state < NUM_TASK_STATE_TYPES));

	mission_type_expanded [state][type] = !mission_type_expanded [state][type];

	return mission_type_expanded [state][type];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int toggle_group_type_collapse_state (int type, group_mode_types state)
{
	ASSERT ((type >= 0) && (type < NUM_ENTITY_SUB_TYPE_GROUPS));

	ASSERT ((state >= 0) && (state < NUM_GROUP_MODE_TYPES));

	group_type_expanded [state][type] = !group_type_expanded [state][type];

	return group_type_expanded [state][type];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int toggle_base_type_collapse_state (int type)
{
	ASSERT ((type >= 0) && (type < NUM_ENTITY_SUB_TYPE_KEYSITES));

	base_type_expanded [type] = !base_type_expanded [type];

	return base_type_expanded [type];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void collapse_mission_list (mission_list_sort_type *sort_list, int *indices, int count, task_state_types state)
{
	int
		loop,
		index;

	unsigned char
		buffer [256];

	ui_object
		*new_item;

	rgb_colour
		*col;

	switch (get_mission_sort_mode ())
	{
		case MISSION_SORT_MODE_TYPE:
		{
			int
				i,
				type_count,
				last_type;

			loop = 0;

			while (loop < count)
			{
				index = indices [loop];

				//
				// Count up how many items
				//

				i = loop;

				type_count = 0;

				last_type = sort_list [index].type;

				while (i < count)
				{
					index = indices [i];

					if (sort_list [index].type == last_type)
					{
						type_count ++;

						i ++;
					}
					else
					{
						break;
					}
				}

				//
				// Display Title
				//

				sprintf (buffer, "%dx %s", type_count, get_trans (task_database [last_type].short_name));

				if (mission_type_expanded [state][last_type])
				{
					new_item = add_to_pop_up_list (buffer, common_list [COMMON_LIST_MODE_MISSION], NULL, last_type, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT, ui_ingame_selected_text_colour);
				}
				else
				{
					new_item = add_to_pop_up_list (buffer, common_list [COMMON_LIST_MODE_MISSION], NULL, last_type, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT, ui_ingame_live_text_colour);
				}

				set_ui_object_highlighted_font_type (new_item, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT);

				set_ui_object_highlightable (new_item, TRUE);

				set_ui_object_item_number2 (new_item, state);

				col = &ui_ingame_highlight_text_colour;

				set_ui_object_highlighted_font_colour (new_item, col->r, col->g, col->b, col->a);

				//
				// Display individual missions
				//
					
				if (mission_type_expanded [state][last_type])
				{
					for (i = loop; i < (loop + type_count); i ++)
					{
						index = indices [i];

						add_mission_to_common_list (sort_list [index].en, sort_list [index].text_type);
					}
				}

				loop = i;
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_sorted_collapsed_mission_list (entity *force, entity *base_filter, entity *group_filter)
{
	mission_list_sort_type
		*sort_list;

	entity
		*keysite,
		*mission;

	int
		count,
		*indices;

	ui_object
		*new_item;

	rgb_colour
		col;

	sort_list = NULL;

	col = ui_ingame_dead_text_colour;

	if ((group_filter) && (get_local_group_primary_task (group_filter)))
	{
		//
		// Trivial case : Selected Group is already doing a mission, so only display that one mission
		//

		sort_list = malloc_fast_mem (sizeof (mission_list_sort_type) * 1);
	
		indices = malloc_fast_mem (sizeof (int) * 1);
	
		mission = get_local_group_primary_task (group_filter);

		ASSERT (get_local_entity_int_value (mission, INT_TYPE_VISIBLE_TASK));

		keysite = get_local_entity_parent (mission, LIST_TYPE_ASSIGNED_TASK);

		ASSERT (keysite);

		count = 0;

		sort_list [count].en = mission;
		sort_list [count].text_type = common_list_classify_mission_text (mission);
		sort_list [count].type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);
		
		indices [count] = count;
		
		if (show_sorted_list_item (sort_list [count].text_type))
		{
			count ++;
		}

		new_item = add_to_pop_up_list (get_trans ("Assigned"), common_list [COMMON_LIST_MODE_MISSION], NULL, -1, CAMPAIGN_LIST_TITLE_FONT, col);

		set_ui_object_selected_font_colour (new_item, col.r, col.g, col.b, col.a);

		collapse_mission_list (sort_list, indices, count, TASK_STATE_ASSIGNED);

		free_mem (sort_list);
	
		free_mem (indices);
	}
	else
	{
		////////////////////////////////////
		//	
		// UNASSIGNED
		//
		////////////////////////////////////

		//
		// count number of items
		//
	
		count = 0;
		
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
	
		while (keysite)
		{
			if ((!base_filter) || (base_filter == keysite))
			{
				mission = get_local_entity_first_child (keysite, LIST_TYPE_UNASSIGNED_TASK);
		
				while (mission)
				{
					count ++;

					mission = get_local_entity_child_succ (mission, LIST_TYPE_UNASSIGNED_TASK);
				}
			}
			
			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}

		//
		// create item list
		//
	
		if (count > 0)
		{
			sort_list = malloc_fast_mem (sizeof (mission_list_sort_type) * count);
	
			indices = malloc_fast_mem (sizeof (int) * count);
	
			count = 0;
			
			keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
		
			while (keysite)
			{
				if ((!base_filter) || (base_filter == keysite))
				{
					mission = get_local_entity_first_child (keysite, LIST_TYPE_UNASSIGNED_TASK);
			
					while (mission)
					{
						if (get_local_entity_int_value (mission, INT_TYPE_VISIBLE_TASK))
						{
							ASSERT (get_local_entity_int_value (mission, INT_TYPE_PRIMARY_TASK));
	
							sort_list [count].en = mission;
							sort_list [count].text_type = common_list_classify_mission_text (mission);
							sort_list [count].type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);
				
							indices [count] = count;
				
							if (show_sorted_list_item (sort_list [count].text_type))
							{
								count ++;
							}
						}
	
						mission = get_local_entity_child_succ (mission, LIST_TYPE_UNASSIGNED_TASK);
					}
				}
		
				keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
			}
		
			//
			// sort list
			//
		
			if (count > 1)
			{
				sort_mission_list (sort_list, indices, count);
			}
	
			if (count > 0)
			{
				new_item = add_to_pop_up_list (get_trans ("Unassigned"), common_list [COMMON_LIST_MODE_MISSION], NULL, -1, CAMPAIGN_LIST_TITLE_FONT, col);

				set_ui_object_selected_font_colour (new_item, col.r, col.g, col.b, col.a);

				collapse_mission_list (sort_list, indices, count, TASK_STATE_UNASSIGNED);
			}

			free_mem (sort_list);
		
			free_mem (indices);
		}
	
		////////////////////////////////////
		//	
		// ASSIGNED
		//
		////////////////////////////////////

		//
		// count number of items
		//
	
		count = 0;
		
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
	
		while (keysite)
		{
			if ((!base_filter) || (base_filter == keysite))
			{
				mission = get_local_entity_first_child (keysite, LIST_TYPE_ASSIGNED_TASK);
		
				while (mission)
				{
					count ++;

					mission = get_local_entity_child_succ (mission, LIST_TYPE_ASSIGNED_TASK);
				}
			}
			
			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}

		//
		// create item list
		//
	
		if (count > 0)
		{
			sort_list = malloc_fast_mem (sizeof (mission_list_sort_type) * count);
	
			indices = malloc_fast_mem (sizeof (int) * count);
	
			count = 0;
			
			keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
		
			while (keysite)
			{
				if ((!base_filter) || (base_filter == keysite))
				{
					mission = get_local_entity_first_child (keysite, LIST_TYPE_ASSIGNED_TASK);
			
					while (mission)
					{
						if (get_local_entity_int_value (mission, INT_TYPE_VISIBLE_TASK))
						{
							ASSERT (get_local_entity_int_value (mission, INT_TYPE_PRIMARY_TASK));
	
							sort_list [count].en = mission;
							sort_list [count].text_type = common_list_classify_mission_text (mission);
							sort_list [count].type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);
				
							indices [count] = count;
				
							if (show_sorted_list_item (sort_list [count].text_type))
							{
								count ++;
							}
						}
	
						mission = get_local_entity_child_succ (mission, LIST_TYPE_ASSIGNED_TASK);
					}
				}
		
				keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
			}
		
			//
			// sort list
			//
		
			if (count > 1)
			{
				sort_mission_list (sort_list, indices, count);
			}
	
			if (count > 0)
			{
				new_item = add_to_pop_up_list (get_trans ("Assigned"), common_list [COMMON_LIST_MODE_MISSION], NULL, -1, CAMPAIGN_LIST_TITLE_FONT, col);
	
				set_ui_object_selected_font_colour (new_item, col.r, col.g, col.b, col.a);

				collapse_mission_list (sort_list, indices, count, TASK_STATE_ASSIGNED);
			}
				
			free_mem (sort_list);
		
			free_mem (indices);
		}

		////////////////////////////////////
		//	
		// COMPLETED
		//
		////////////////////////////////////

		//
		// count number of items
		//
	
		count = 0;
		
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
	
		while (keysite)
		{
			if ((!base_filter) || (base_filter == keysite))
			{
				mission = get_local_entity_first_child (keysite, LIST_TYPE_COMPLETED_TASK);
		
				while (mission)
				{
					count ++;

					mission = get_local_entity_child_succ (mission, LIST_TYPE_COMPLETED_TASK);
				}
			}
			
			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}

		//
		// create item list
		//
	
		if (count > 0)
		{
			sort_list = malloc_fast_mem (sizeof (mission_list_sort_type) * count);
	
			indices = malloc_fast_mem (sizeof (int) * count);
	
			count = 0;
			
			keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
		
			while (keysite)
			{
				if ((!base_filter) || (base_filter == keysite))
				{
					mission = get_local_entity_first_child (keysite, LIST_TYPE_COMPLETED_TASK);
			
					while (mission)
					{
						if (get_local_entity_int_value (mission, INT_TYPE_VISIBLE_TASK))
						{
							ASSERT (get_local_entity_int_value (mission, INT_TYPE_PRIMARY_TASK));
	
							sort_list [count].en = mission;
							sort_list [count].text_type = common_list_classify_mission_text (mission);
							sort_list [count].type = get_local_entity_int_value (mission, INT_TYPE_ENTITY_SUB_TYPE);
				
							indices [count] = count;
				
							if (show_sorted_list_item (sort_list [count].text_type))
							{
								count ++;
							}
						}
	
						mission = get_local_entity_child_succ (mission, LIST_TYPE_COMPLETED_TASK);
					}
				}
		
				keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
			}
		
			//
			// sort list
			//
		
			if (count > 1)
			{
				sort_mission_list (sort_list, indices, count);
			}
	
			if (count > 0)
			{
				new_item = add_to_pop_up_list (get_trans ("Completed"), common_list [COMMON_LIST_MODE_MISSION], NULL, -1, CAMPAIGN_LIST_TITLE_FONT, col);

				set_ui_object_selected_font_colour (new_item, col.r, col.g, col.b, col.a);

				collapse_mission_list (sort_list, indices, count, TASK_STATE_COMPLETED);
			}

			free_mem (sort_list);
		
			free_mem (indices);
		}
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void collapse_group_list (group_list_sort_type *sort_list, int *indices, int count, group_mode_types state)
{
	int
		i,
		loop,
		index,
		category,
		last_category,
		type_count,
		last_type;

	unsigned char
		buffer [256];

	ui_object
		*new_item;

	rgb_colour
		*col;

	switch (get_group_sort_mode ())
	{
		case GROUP_SORT_MODE_TYPE:
		{
			loop = 0;

			last_category = -1;

			while (loop < count)
			{
				index = indices [loop];

				//
				// Count up how many items
				//

				i = loop;

				type_count = 0;

				last_type = sort_list [index].type;

				while (i < count)
				{
					index = indices [i];

					if (sort_list [index].type == last_type)
					{
						type_count ++;

						i ++;
					}
					else
					{
						break;
					}
				}

				category = group_database [last_type].group_category;

				if (category != NUM_GROUP_CATEGORY_TYPES)
				{
					if (category != last_category)
					{
						last_category = category;
	
						//
						// Display Group Category Heading
						//
	
						sprintf (buffer, "%s", get_trans (group_category_names [category]));

						new_item = add_to_pop_up_list (buffer, common_list [COMMON_LIST_MODE_GROUP], NULL, category, CAMPAIGN_LIST_SUB_TITLE_FONT, ui_ingame_dead_text_colour);

						set_ui_object_notify_on (new_item, NOTIFY_TYPE_NONE);
					}
	
					//
					// Display Title
					//
	
					sprintf (buffer, "%dx %s", type_count, get_trans (group_database [last_type].group_short_name));
	
					if (group_type_expanded [state][last_type])
					{
						new_item = add_to_pop_up_list (buffer, common_list [COMMON_LIST_MODE_GROUP], NULL, last_type, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT, ui_ingame_selected_text_colour);
					}
					else
					{
						new_item = add_to_pop_up_list (buffer, common_list [COMMON_LIST_MODE_GROUP], NULL, last_type, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT, ui_ingame_live_text_colour);
					}
	
					set_ui_object_highlighted_font_type (new_item, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT);

					set_ui_object_highlightable (new_item, TRUE);
	
					set_ui_object_item_number2 (new_item, state);
	
					col = &ui_ingame_highlight_text_colour;
	
					set_ui_object_highlighted_font_colour (new_item, col->r, col->g, col->b, col->a);
	
					//
					// Display individual groups
					//
						
					if (group_type_expanded [state][last_type])
					{
						for (i = loop; i < (loop + type_count); i ++)
						{
							index = indices [i];
	
							add_group_to_common_list (sort_list [index].en, sort_list [index].text_type);
						}
					}
				}
				
				loop = i;
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_sorted_collapsed_group_list (entity *force, entity *base_filter, entity *mission_filter)
{
	group_list_sort_type
		*sort_list;

	entity
		*guide,
		*group,
		*primary_task,
		*keysite;

	entity_sub_types
		group_type;

	int
		count,
		group_count,
		*indices;

	ui_object
		*new_item;

	rgb_colour
		col;

	col = ui_ingame_dead_text_colour;

	if ((mission_filter) && (get_local_entity_first_child (mission_filter, LIST_TYPE_GUIDE)))
	{
		//
		// Trivial case : Selected Mission is already being done by a group, so only display that one group
		//

		ASSERT (get_local_entity_int_value (mission_filter, INT_TYPE_VISIBLE_TASK));

		sort_list = malloc_fast_mem (sizeof (group_list_sort_type) * 1);
	
		indices = malloc_fast_mem (sizeof (int) * 1);
	
		guide = get_local_entity_first_child (mission_filter, LIST_TYPE_GUIDE);

		group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);

		ASSERT (group);

		// check that only one group is doing this task
		ASSERT (!get_local_entity_child_succ (guide, LIST_TYPE_GUIDE));

		count = 0;

		sort_list [count].en = group;
		sort_list [count].text_type = common_list_classify_group_text (group);
		sort_list [count].type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
		sort_list [count].name = get_local_entity_string (group, STRING_TYPE_DIVISION_NAME);
		
		indices [count] = count;
		
		if (show_sorted_list_item (sort_list [count].text_type))
		{
			count ++;
		}

		new_item = add_to_pop_up_list (get_trans ("Assigned"), common_list [COMMON_LIST_MODE_GROUP], NULL, -1, CAMPAIGN_LIST_TITLE_FONT, col);

		set_ui_object_selected_font_colour (new_item, col.r, col.g, col.b, col.a);

		collapse_group_list (sort_list, indices, count, GROUP_MODE_BUSY);

		free_mem (sort_list);
	
		free_mem (indices);
	}
	else
	{
		//
		// count number of items
		//
	
		group_count = 0;

		// Keysite groups
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

		while (keysite)
		{
			if ((!base_filter) || (base_filter == keysite))
			{
				group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);
		
				while (group)
				{
					group_count ++;
			
					group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
				}
			}
			
			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}

		// Independent groups
		if (!base_filter)
		{
			group = get_local_entity_first_child (force, LIST_TYPE_INDEPENDENT_GROUP);
		
			while (group)
			{
				group_count ++;
			
				group = get_local_entity_child_succ (group, LIST_TYPE_INDEPENDENT_GROUP);
			}
		}
	
		if (group_count > 0)
		{
			sort_list = malloc_fast_mem (sizeof (group_list_sort_type) * group_count);
		
			indices = malloc_fast_mem (sizeof (int) * group_count);
		}
		else
		{
			return;
		}
				
		////////////////////////////////////
		//	
		// UNASSIGNED
		//
		////////////////////////////////////

		//
		// create item list
		//
		
		count = 0;

		// Keysite groups
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

		while (keysite)
		{
			if ((!base_filter) || (base_filter == keysite))
			{
				group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);
		
				while (group)
				{	
					primary_task = get_local_group_primary_task (group);
					
					if (!primary_task)
					{
						sort_list [count].en = group;
						sort_list [count].text_type = common_list_classify_group_text (group);
						sort_list [count].name = get_local_entity_string (group, STRING_TYPE_DIVISION_NAME);
						sort_list [count].type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
			
						indices [count] = count;
			
						if (show_sorted_list_item (sort_list [count].text_type))
						{
							count ++;
						}
					}

					group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
				}
			}

			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}
	
		// Independent groups
		if (!base_filter)
		{
			group = get_local_entity_first_child (force, LIST_TYPE_INDEPENDENT_GROUP);
	
			while (group)
			{
				primary_task = get_local_group_primary_task (group);
					
				if (!primary_task)
				{
					sort_list [count].en = group;
					sort_list [count].text_type = common_list_classify_group_text (group);
					sort_list [count].name = get_local_entity_string (group, STRING_TYPE_DIVISION_NAME);
					sort_list [count].type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
			
					indices [count] = count;
			
					if (show_sorted_list_item (sort_list [count].text_type))
					{
						count ++;
					}
				}

				group = get_local_entity_child_succ (group, LIST_TYPE_INDEPENDENT_GROUP);
			}
		}

		//
		// sort list
		//
	
		if (count > 1)
		{
			sort_group_list (sort_list, indices, count);
		}

		if (count > 0)
		{
			new_item = add_to_pop_up_list (get_trans ("Unassigned"), common_list [COMMON_LIST_MODE_GROUP], NULL, -1, CAMPAIGN_LIST_TITLE_FONT, col);

			set_ui_object_selected_font_colour (new_item, col.r, col.g, col.b, col.a);

			collapse_group_list (sort_list, indices, count, GROUP_MODE_IDLE);
		}

		////////////////////////////////////
		//	
		// ASSIGNED
		//
		////////////////////////////////////
	
		//
		// create item list
		//

		count = 0;
		
		// Keysite groups
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

		while (keysite)
		{
			if ((!base_filter) || (base_filter == keysite))
			{
				group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);
		
				while (group)
				{	
					group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
			
					primary_task = get_local_group_primary_task (group);

					if (primary_task)
					{						
						if ((!mission_filter) || (primary_task == mission_filter))
						{
							sort_list [count].en = group;
							sort_list [count].text_type = common_list_classify_group_text (group);
							sort_list [count].name = get_local_entity_string (group, STRING_TYPE_DIVISION_NAME);
							sort_list [count].type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
				
							indices [count] = count;
				
							if (show_sorted_list_item (sort_list [count].text_type))
							{
								count ++;
							}
						}
					}
						
					group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
				}
			}

			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}
	
		// Independent groups
		if (!base_filter)
		{
			group = get_local_entity_first_child (force, LIST_TYPE_INDEPENDENT_GROUP);
	
			while (group)
			{
				primary_task = get_local_group_primary_task (group);
					
				if (primary_task)
				{
					if ((!mission_filter) || (primary_task == mission_filter))
					{
						sort_list [count].en = group;
						sort_list [count].text_type = common_list_classify_group_text (group);
						sort_list [count].name = get_local_entity_string (group, STRING_TYPE_DIVISION_NAME);
						sort_list [count].type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
			
						indices [count] = count;
			
						if (show_sorted_list_item (sort_list [count].text_type))
						{
							count ++;
						}
					}
				}

				group = get_local_entity_child_succ (group, LIST_TYPE_INDEPENDENT_GROUP);
			}
		}

		//
		// sort list
		//
	
		if (count > 1)
		{
			sort_group_list (sort_list, indices, count);
		}

		if (count > 0)
		{
			new_item = add_to_pop_up_list (get_trans ("Assigned"), common_list [COMMON_LIST_MODE_GROUP], NULL, -1, CAMPAIGN_LIST_TITLE_FONT, col);

			set_ui_object_selected_font_colour (new_item, col.r, col.g, col.b, col.a);

			collapse_group_list (sort_list, indices, count, GROUP_MODE_BUSY);
		}

		free_mem (sort_list);
	
		free_mem (indices);
	}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_sorted_collapsed_base_list (entity *force)
{
	base_list_sort_type
		*sort_list;

	entity
		*keysite;

	unsigned char
		buffer [256];

	ui_object
		*new_item;

	int
		loop,
		count,
		index,
		*indices;

	rgb_colour
		*col;

	//
	// count number of items
	//

	count = 0;
	
	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
		{
			count ++;
		}
		
		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}

	if (count == 0)
	{
		return;
	}

	//
	// create item list
	//

	sort_list = malloc_fast_mem (sizeof (base_list_sort_type) * count);

	indices = malloc_fast_mem (sizeof (int) * count);

	count = 0;
	
	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
		{
			sort_list [count].en = keysite;
		
			sort_list [count].text_type = common_list_classify_base_text (keysite);
	
			sort_list [count].type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);
	
			sort_list [count].base_name = get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME);
		
			indices [count] = count;
		
			if (show_sorted_list_item (sort_list [count].text_type))
			{
				count ++;
			}
		}
			
		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}

	//
	// sort list
	//

	if (count > 1)
	{
		sort_base_list (sort_list, indices, count);
	}

	//
	// Collapse list
	//

	switch (get_base_sort_mode ())
	{
		case BASE_SORT_MODE_TYPE:
		{
			int
				i,
				type_count,
				last_type;

			loop = 0;

			while (loop < count)
			{
				index = indices [loop];

				//
				// Count up how many items
				//

				i = loop;

				type_count = 0;

				last_type = sort_list [index].type;

				while (i < count)
				{
					index = indices [i];

					if (sort_list [index].type == last_type)
					{
						type_count ++;

						i ++;
					}
					else
					{
						break;
					}
				}

				//
				// Display Title
				//

				sprintf (buffer, "%dx %s", type_count, get_trans (keysite_database [last_type].short_name));

				if (base_type_expanded [last_type])
				{
					new_item = add_to_pop_up_list (buffer, common_list [COMMON_LIST_MODE_BASE], NULL, last_type, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT, ui_ingame_selected_text_colour);
				}
				else
				{
					new_item = add_to_pop_up_list (buffer, common_list [COMMON_LIST_MODE_BASE], NULL, last_type, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT, ui_ingame_live_text_colour);
				}

				set_ui_object_highlighted_font_type (new_item, CAMPAIGN_LIST_SUB_SUB_TITLE_FONT);

				set_ui_object_highlightable (new_item, TRUE);

				set_ui_object_item_number2 (new_item, 0);

				col = &ui_ingame_highlight_text_colour;

				set_ui_object_highlighted_font_colour (new_item, col->r, col->g, col->b, col->a);

				//
				// Display individual bases
				//
					
				if (base_type_expanded [last_type])
				{
					for (i = loop; i < (loop + type_count); i ++)
					{
						index = indices [i];

						add_base_to_common_list (sort_list [index].en, sort_list [index].text_type);
					}
				}

				loop = i;
			}

			break;
		}

		default:
		{
			for (loop = 0; loop < count; loop ++)
			{
				index = indices [loop];
	
				add_base_to_common_list (sort_list [index].en, sort_list [index].text_type);
			}

			break;
		}
	}

	free_mem (sort_list);

	free_mem (indices);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int common_list_classify_mission_text (entity *en)
{
	ASSERT (en);

	if (get_mission_player_suitability_status (en))
	{
		if (get_local_entity_int_value (en, INT_TYPE_TASK_STATE) == TASK_STATE_UNASSIGNED)
		{
			//
			// Suitable UNASSIGNED Task 
			//

			return COMMON_LIST_TEXT_AVAILABLE;
		}
		else
		{
			//
			// Suitable ASSIGNED Task 
			//

			return COMMON_LIST_TEXT_BUSY;
		}
	}

	//
	// Unsuitable Task 
	//

	if (get_local_entity_int_value (en, INT_TYPE_TASK_STATE) == TASK_STATE_COMPLETED)
	{
		return COMMON_LIST_TEXT_COMPLETE;
	}
	else
	{
		return COMMON_LIST_TEXT_UNAVAILABLE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int common_list_classify_group_text (entity *en)
{
	ASSERT (en);

	if (get_group_player_suitability_status (en))
	{
		if (get_local_entity_int_value (en, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
		{
			//
			// Suitable IDLE Group
			//

			return COMMON_LIST_TEXT_AVAILABLE;
		}
		else
		{
			//
			// Suitable BUSY Group
			//

			return COMMON_LIST_TEXT_BUSY;
		}
	}

	//
	// Unsuitable Group
	//

	return COMMON_LIST_TEXT_UNAVAILABLE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int common_list_classify_base_text (entity *en)
{
	return COMMON_LIST_TEXT_AVAILABLE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sort_mission_list (mission_list_sort_type *sort_list, int *indices, int count)
{
	int
		*int_order;

	int
		loop;
		
	ASSERT (sort_list);

	ASSERT (indices);

	ASSERT (count > 0);

	switch (get_mission_sort_mode ())
	{
		case MISSION_SORT_MODE_TYPE:
		{
			//
			// Sort by mission type
			//
		
			int_order = malloc_fast_mem (sizeof (int) * count);
	
			for (loop = 0; loop < count; loop ++)
			{
				int_order [loop] = sort_list [loop].type;
			}
		
			quicksort_int (indices, count, int_order);
	
			free_mem (int_order);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sort_group_list (group_list_sort_type *sort_list, int *indices, int count)
{
	int
		*int_order;

	int
		loop;
		
	ASSERT (sort_list);

	ASSERT (indices);

	ASSERT (count > 0);

	switch (get_group_sort_mode ())
	{
		case GROUP_SORT_MODE_TYPE:
		{
			//
			// Sort by group type
			//
		
			int_order = malloc_fast_mem (sizeof (int) * count);
	
			for (loop = 0; loop < count; loop ++)
			{
				int_order [loop] = sort_list [loop].type;
			}
		
			quicksort_int (indices, count, int_order);
	
			free_mem (int_order);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void sort_base_list (base_list_sort_type *sort_list, int *indices, int count)
{
	int
		*int_order;

	const char
		**string_order;

	int
		loop;
		
	ASSERT (sort_list);

	ASSERT (indices);

	ASSERT (count > 0);

	switch (get_base_sort_mode ())
	{
		case BASE_SORT_MODE_TYPE:
		{	
			//
			// Sort by base type
			//
		
			int_order = malloc_fast_mem (sizeof (int) * count);
	
			for (loop = 0; loop < count; loop ++)
			{
				int_order [loop] = sort_list [loop].type;
			}
		
			quicksort_int (indices, count, int_order);
	
			free_mem (int_order);

			break;
		}

		default:
		{
			//
			// Sort by base name
			//
		
			string_order = malloc_fast_mem (sizeof (const char *) * count);
	
			for (loop = 0; loop < count; loop ++)
			{
				string_order [loop] = sort_list [loop].base_name;
			}
		
			quicksort_string (indices, count, string_order);
	
			free_mem (string_order);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void qs_int (int *indices, int *sort_order, int left, int right)
{
   int
      i, j,
      temp;

   int
      x, y;

   i = left;
   j = right;

   x = sort_order [(left + right) / 2];

   do
   {
      while (sort_order [i] < x && i < right) i++;
      while (x < sort_order [j] && j > left) j--;

      if (i <= j)
      {
         y = sort_order [i];
         sort_order [i] = sort_order [j];
         sort_order [j] = y;

         temp = indices [i];
         indices [i] = indices [j];
         indices [j] = temp;
         
         i++;
         j--;
      }
   }
	while (i <= j);

   if (left < j) qs_int (indices, sort_order, left, j);
   if (i < right) qs_int (indices, sort_order, i, right);
}

void quicksort_int (int *indices, int count, int *sort_order)
{
   qs_int (indices, sort_order, 0, count - 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void qs_string (int *indices, const char **sort_order, int left, int right)
{
   int
      i, j,
      temp;

  	const char
      *x, *y;

   i = left;
   j = right;

   x = sort_order [(left + right) / 2];

   do
   {
      while ((strcmp (sort_order [i], x) < 0) && (i < right)) i++;
      while ((strcmp (x, sort_order [j]) < 0) && (j > left)) j--;

      if (i <= j)
      {
         y = sort_order [i];
         sort_order [i] = sort_order [j];
         sort_order [j] = y;

         temp = indices [i];
         indices [i] = indices [j];
         indices [j] = temp;
         
         i++;
         j--;
      }
   }
	while (i <= j);

   if (left < j) qs_string (indices, sort_order, left, j);
   if (i < right) qs_string (indices, sort_order, i, right);
}

void quicksort_string (int *indices, int count, const char **sort_order)
{
   qs_string (indices, sort_order, 0, count - 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


