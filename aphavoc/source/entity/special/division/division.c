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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DIVISION_ID_DATA
{
	int
		valid,
		count,
		next,
		*number_list;
};

typedef struct DIVISION_ID_DATA division_id_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static division_id_data
	division_id_database [NUM_ENTITY_SIDES][NUM_ENTITY_SUB_TYPE_DIVISIONS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_new_division (entity_sub_types type, entity_sides side, entity *parent, entity *hq, int local_only)
{
	entity
		*new_entity;

	int
		id;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (parent);

	id = get_next_free_division_id (side, type);

	if (local_only)
	{
		new_entity = create_local_entity
		(
			ENTITY_TYPE_DIVISION,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (LIST_TYPE_DIVISION, parent),
			ENTITY_ATTR_PARENT (LIST_TYPE_DIVISION_HEADQUARTERS, hq),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_DIVISION_ID, id),
			ENTITY_ATTR_END
		);
	}
	else
	{
		new_entity = create_client_server_entity
		(
			ENTITY_TYPE_DIVISION,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (LIST_TYPE_DIVISION, parent),
			ENTITY_ATTR_PARENT (LIST_TYPE_DIVISION_HEADQUARTERS, hq),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_DIVISION_ID, id),
			ENTITY_ATTR_END
		);
	}

	return new_entity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *add_group_to_division (entity *group, entity *specified_division)
{
	int
		side,
		count,
		max_count,
		group_type,
		keysite_type,
		division_type,
		main_division_type;

	entity
		*en,
		*force,
		*keysite,
		*division;

	vec3d
		*group_pos;
		
	ASSERT (group);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (!get_local_entity_parent (group, LIST_TYPE_DIVISION));

	group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);
	
	group_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);
	
	if (specified_division)
	{
		division = specified_division;
	}
	else
	{
		side = get_local_entity_int_value (group, INT_TYPE_SIDE);
	
		force = get_local_force_entity (side);
	
		ASSERT (force);
	
		division_type = group_database [group_type].default_group_division;
	
		ASSERT (entity_sub_type_division_valid (division_type));
	
		main_division_type = division_database [division_type].default_group_division;
	
		ASSERT (entity_sub_type_division_valid (main_division_type));
	
		//
		// Find the keysite the company should be attached to
		//

		keysite = NULL;
	
		if (get_local_entity_int_value (group, INT_TYPE_GROUP_LIST_TYPE) == LIST_TYPE_KEYSITE_GROUP)
		{
			keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

			if (!keysite)
			{
				keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, side, group_pos, 1.0 * KILOMETRE, NULL, NULL);
			}
	
			ASSERT (keysite);
	
			keysite_type = get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE);
	
			if ((keysite_type == ENTITY_SUB_TYPE_KEYSITE_AIRBASE) || (keysite_type == ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE))
			{
				//
				// Use keysite landed at
				//
			}
			else
			{
				//
				// Find nearest keysite (below)
				//

				keysite = NULL;
			}
		}
		else
		{
			if (group_database [group_type].movement_type == MOVEMENT_TYPE_SEA)
			{
				//
				// Find nearest carrier
				//
			
				keysite = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE, side, group_pos, 0.0, NULL, NULL);
			}
		}

		if (!keysite)
		{
			//
			// Find nearest airbase
			//
			
			keysite = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_AIRBASE, side, group_pos, 0.0, NULL, NULL);

			if (!keysite)
			{
				//
				// Find nearest military base
				//
				
				keysite = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_MILITARY_BASE, side, group_pos, 0.0, NULL, NULL);

				if (!keysite)
				{
					//
					// Find nearest FARP  
					//
				
					keysite = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_FARP, side, group_pos, 0.0, NULL, NULL);
				}
			}
		}
	
		ASSERT (keysite);
	
		//
		// Check all companies at this keysite to see if they have vacancies....
		//
	
		max_count = group_database [group_type].maximum_groups_per_division;
	
		division = get_local_entity_first_child (keysite, LIST_TYPE_DIVISION_HEADQUARTERS);
	
		while (division)
		{
			if (get_local_entity_int_value (division, INT_TYPE_ENTITY_SUB_TYPE) == division_type)
			{
				if (max_count == 0)
				{
					break;
				}
	
				count = 0;
	
				en = get_local_entity_first_child (division, LIST_TYPE_DIVISION);
	
				while (en)
				{
					ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);
	
					count ++;
	
					en = get_local_entity_child_succ (en, LIST_TYPE_DIVISION);
				}
	
				if (count < max_count)
				{
					break;
				}
			}
	
			division = get_local_entity_child_succ (division, LIST_TYPE_DIVISION_HEADQUARTERS);
		}
	
		if (division)
		{
			//
			// found an existing division with space available
			//
		}
		else
		{
			//
			// create a new division
			//
	
			entity
				*main_division;
	
			max_count = division_database [division_type].maximum_groups_per_division;
	
			main_division = get_local_entity_first_child (force, LIST_TYPE_DIVISION);
	
			while (main_division)
			{
				if (get_local_entity_int_value (main_division, INT_TYPE_ENTITY_SUB_TYPE) == main_division_type)
				{
					//
					// check division for vacancies
					//
	
					if (max_count == 0)
					{
						break;
					}
	
					count = 0;
	
					en = get_local_entity_first_child (main_division, LIST_TYPE_DIVISION);
	
					while (en)
					{
						ASSERT (get_local_entity_type (en) == ENTITY_TYPE_DIVISION);
	
						if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) == division_type)
						{
							count ++;
						}
						
						en = get_local_entity_child_succ (en, LIST_TYPE_DIVISION);
					}
	
					if (count < max_count)
					{
						break;
					}
				}
	
				main_division = get_local_entity_child_succ (main_division, LIST_TYPE_DIVISION);
			}
	
			if (main_division)
			{
				//
				// found an existing division with space available
				//
			}
			else
			{
				//
				// create a new division
				//
	
				main_division = create_new_division (main_division_type, side, force, NULL, FALSE);
			}
	
			ASSERT (main_division);
	
			division = create_new_division (division_type, side, main_division, keysite, FALSE);
		}
	}

	ASSERT (division);

	set_client_server_entity_parent (group, LIST_TYPE_DIVISION, division);

	return division;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_number_extension (int number, unsigned char *extension)
{
	int
		remainder;

	ASSERT (extension);

	remainder = (number / 10) % 10;

	if (remainder == 1)
	{
		// (special case for 11th, 111th, 211th etc.)
		sprintf (extension, "th");
	}
	else
	{
		remainder = number % 10;
		
		switch (remainder)
		{
			case 1:
			{
				sprintf (extension, "st");
	
				break;
			}
			case 2:
			{
				sprintf (extension, "nd");
		
				break;
			}
			case 3:
			{
				sprintf (extension, "rd");
		
				break;
			}
			default:
			{
				sprintf (extension, "th");
		
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_local_division_name (entity *en, unsigned char *s)
{
	int
		division_type,
		division_id;

	unsigned char
		extension [10],
		id_string [10];

	entity
		*group;

	ASSERT (en);

	ASSERT (s);

	if (get_local_entity_type (en) == ENTITY_TYPE_DIVISION)
	{
		division_id = get_local_entity_int_value (en, INT_TYPE_DIVISION_ID);
	}
	else
	{
		ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);

		division_id = 1;

		group = en;

		while (get_local_entity_child_succ (group, LIST_TYPE_DIVISION))
		{
			division_id ++;

			group = get_local_entity_child_succ (group, LIST_TYPE_DIVISION);
		}

		if (!get_local_entity_int_value (en, INT_TYPE_AIRCRAFT_GROUP))
		{
			set_local_entity_int_value (en, INT_TYPE_GROUP_CALLSIGN, division_id);
		}
	}

	sprintf (id_string, "%d", division_id);

	//
	// Specify extension after number (bloody English language)
	//	

	get_number_extension (division_id, extension);

	strcat (id_string, extension);

	//
	// Store result
	//
	
	division_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	
	if (get_local_entity_type (en) == ENTITY_TYPE_DIVISION)
	{
		sprintf (s, division_database [division_type].full_name, id_string);
	}
	else
	{
		switch (group_database [division_type].platoon_id_type)
		{
			case PLATOON_ID_NONE:
			{
				sprintf (s, group_database [division_type].platoon_name);

				break;
			}
			case PLATOON_ID_NUMBER:
			{
				sprintf (s, group_database [division_type].platoon_name, id_string);

				break;
			}
			case PLATOON_ID_LETTER:
			{
				sprintf (s, group_database [division_type].platoon_name, ((division_id - 1) + 'A'));

				break;
			}
			case PLATOON_ID_CALLSIGN:
			{
				strcpy (s, get_local_entity_string (en, STRING_TYPE_GROUP_CALLSIGN));

				break;
			}
			case PLATOON_ID_KEYSITE:
			{
				entity
					*keysite,
					*division;

				if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
				{
					division = get_local_entity_parent (en, LIST_TYPE_DIVISION);
				}
				else
				{
					division = en;
				}

				keysite = get_local_entity_parent (division, LIST_TYPE_DIVISION_HEADQUARTERS);

				ASSERT (keysite);
				
				sprintf (s, group_database [division_type].platoon_name, get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

				break;
			}
			default:
			{
				debug_fatal ("Invalid Platoon Id Type %d", group_database [division_type].platoon_id_type);
			}
		}
	}

	return TRUE;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_division_database (void)
{
	int
		side,
		type;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (type = 0; type < NUM_ENTITY_SUB_TYPE_DIVISIONS; type ++)
		{
			memset (&division_id_database [side][type], 0, sizeof (division_id_data));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_division_database (void)
{
	int
		side,
		type;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (type = 0; type < NUM_ENTITY_SUB_TYPE_DIVISIONS; type ++)
		{
			if (division_id_database [side][type].valid)
			{
				#if DEBUG_MODULE

				debug_filtered_log ("SIDE %s - %s : Used %d / %d",
											entity_side_short_names [side], 
											entity_sub_type_division_names [type],
											division_id_database [side][type].next,
											division_id_database [side][type].count);

				#endif

				debug_assert (division_id_database [side][type].count > 0);

				free_mem (division_id_database [side][type].number_list);

				memset (&division_id_database [side][type], 0, sizeof (division_id_data));
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_division_database (pack_modes mode)
{
	int
		side,
		type,
		loop,
		count,
		valid;

	if (mode == PACK_MODE_SERVER_SESSION)
	{
		for (side = 0; side < NUM_ENTITY_SIDES; side ++)
		{
			for (type = 0; type < NUM_ENTITY_SUB_TYPE_DIVISIONS; type ++)
			{
				valid = division_id_database [side][type].valid;
	
				pack_int_value (NULL, INT_TYPE_VALID, valid);
	
				if (valid)
				{
					count = division_id_database [side][type].count;
	
					pack_int_value (NULL, INT_TYPE_COUNT, count);
	
					pack_int_value (NULL, INT_TYPE_COUNT, division_id_database [side][type].next);
	
					for (loop = 0; loop < count; loop ++)
					{
						pack_int_value (NULL, INT_TYPE_COUNT, division_id_database [side][type].number_list [loop]);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_division_database (pack_modes mode)
{
	int
		side,
		type,
		loop,
		count,
		valid;

	if (mode == PACK_MODE_SERVER_SESSION)
	{
		for (side = 0; side < NUM_ENTITY_SIDES; side ++)
		{
			for (type = 0; type < NUM_ENTITY_SUB_TYPE_DIVISIONS; type ++)
			{
				valid = unpack_int_value (NULL, INT_TYPE_VALID);
	
				division_id_database [side][type].valid = valid;
	
				if (valid)
				{
					count = unpack_int_value (NULL, INT_TYPE_COUNT);
	
					ASSERT (count > 0);
	
					division_id_database [side][type].count = count;
	
					division_id_database [side][type].next = unpack_int_value (NULL, INT_TYPE_COUNT);
	
					division_id_database [side][type].number_list = malloc_heap_mem (sizeof (int) * count);
	
					for (loop = 0; loop < count; loop ++)
					{
						division_id_database [side][type].number_list [loop] = unpack_int_value (NULL, INT_TYPE_COUNT);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_division_id_data (int side, int type, int count, int *number_list)
{
	debug_assert (division_id_database [side][type].count == 0);

	debug_assert (!division_id_database [side][type].number_list);

	debug_assert (count > 0);

	debug_assert (number_list);

	division_id_database [side][type].valid = TRUE;

	division_id_database [side][type].count = count;

	division_id_database [side][type].next = 0;

	division_id_database [side][type].number_list = malloc_heap_mem (sizeof (int) * count);

	memcpy (division_id_database [side][type].number_list, number_list, sizeof (int) * count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_next_free_division_id (int side, int type)
{
	int
		id,
		index,
		count;

	if (!division_id_database [side][type].valid)
	{
		debug_fatal ("DIVISION: Side %s Type %d not valid", entity_side_short_names [side], type);
	}

	index = division_id_database [side][type].next;

	count = division_id_database [side][type].count;

	debug_assert (count > 0);

	debug_assert (index < count);

	id = division_id_database [side][type].number_list [index];

	index ++;

	if (index == count)
	{
		debug_filtered_log ("DIVISION: WARNING Side %s - %s wrapped (count = %d)",
											entity_side_short_names [side], 
											entity_sub_type_division_names [type],
											count);

		index = 0;
	}

	division_id_database [side][type].next = index;

	return id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



