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

#include "order.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE   0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static void debug_output_force_order_of_battle (entity *force);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_armoured_divisions (entity *force)
{
	int
		loop,
		d,
		count,
		group_type,
		side,
		division_count,
		frontline_count,
		artillery_count;

	entity
		*en,
		*first_group,
		*division,
		*keysite,
		**list,
		**frontline_groups,
		**artillery_groups;

	float
		*rating,
		frontline_remainder,
		artillery_remainder,
		f_count,
		a_count,
		frontline_per_division,
		artillery_per_division;

	vec3d
		*pos1,
		*pos2;

	ASSERT (force);

	side = get_local_entity_int_value (force, INT_TYPE_SIDE);

	//
	// Count up frontline / artillery groups
	//

	frontline_count = 0;
	artillery_count = 0;

	en = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

	while (en)
	{
		group_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

		switch (group_type)
		{
			case ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE:
			case ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE:
			{
				frontline_count ++;

				break;
			}
			case ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY:
			{
				artillery_count ++;

				break;
			}
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_GROUND_REGISTRY);
	}

	//
	// calculate required number of divisions
	//

	convert_float_to_int (ceil ((float)frontline_count / 12.0), &division_count);

	convert_float_to_int (ceil ((float)artillery_count / 2.0), &count);

	division_count = max (division_count, count);

	//
	// Store list of groups
	//

	if (frontline_count > 0)
	{
		frontline_groups = (entity **) malloc_heap_mem (sizeof (entity *) * frontline_count);
	}
	else
	{
		frontline_groups = NULL;
	}

	if (artillery_count > 0)
	{
		artillery_groups = (entity **) malloc_heap_mem (sizeof (entity *) * artillery_count);
	}
	else
	{
		artillery_groups = NULL;
	}

	if ((!frontline_groups) && (!artillery_groups))
	{
		return;
	}

	ASSERT (division_count > 0);

	frontline_per_division = (float)frontline_count / (float)division_count;

	artillery_per_division = (float)artillery_count / (float)division_count;

	frontline_count = 0;
	artillery_count = 0;

	en = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

	while (en)
	{
		group_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

		switch (group_type)
		{
			case ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE:
			case ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE:
			{
				ASSERT (frontline_groups);

				frontline_groups [frontline_count] = en;

				frontline_count ++;

				break;
			}
			case ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY:
			{
				ASSERT (artillery_groups);

				artillery_groups [artillery_count] = en;

				artillery_count ++;

				break;
			}
		}

		en = get_local_entity_child_succ (en, LIST_TYPE_GROUND_REGISTRY);
	}

	//
	// group together divisions
	//

	frontline_remainder = 0;
	artillery_remainder = 0;

	for (d = 0; d < division_count; d ++)
	{
		division = create_new_division (ENTITY_SUB_TYPE_DIVISION_ARMOURED_DIVISION, (entity_sides) side, force, NULL, TRUE);

		//
		// decide how many of each group type are to be added to this division
		//

		f_count = floor (frontline_per_division + frontline_remainder);
		a_count = floor (artillery_per_division + artillery_remainder);

		frontline_remainder = frontline_per_division - f_count;
		artillery_remainder = artillery_per_division - a_count;

		//
		// find first group NOT in a division, and sort remaining groups with regard to distance from chosen group
		//

		first_group = NULL;

		if (frontline_groups)
		{
			list = frontline_groups;

			count = frontline_count;
		}
		else
		{
			list = artillery_groups;

			count = artillery_count;
		}

		for (loop = 0; loop < count; loop ++)
		{
			en = list [loop];

			ASSERT (en);

			if (!get_local_entity_parent (en, LIST_TYPE_DIVISION))
			{
				first_group = en;

				break;
			}
		}

		if (!first_group)
		{
			//
			// All checked groups are in a division, so break out and handle the remaining groups
			//

			break;
		}

		pos1 = get_local_entity_vec3d_ptr (first_group, VEC3D_TYPE_POSITION);

		keysite = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_AIRBASE, (entity_sides) side, pos1, 0.0, NULL, NULL);

		//
		// Sort Frontline groups
		//

		if (frontline_groups)
		{
			int
				c,
				n,
				company_count;

			entity
				*company;

			ASSERT (frontline_count > 0);

			rating = (float*) malloc_heap_mem (sizeof (float) * frontline_count);

			for (loop = 0; loop < frontline_count; loop ++)
			{
				en = frontline_groups [loop];

				if (get_local_entity_parent (en, LIST_TYPE_DIVISION))
				{
					rating [loop] = FLT_MAX;
				}
				else if (en == first_group)
				{
					rating [loop] = 0.0;
				}
				else
				{
					pos2 = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

					rating [loop] = get_2d_range (pos1, pos2);
				}
			}

			quicksort_entity_list (frontline_groups, frontline_count, rating);

			//
			// organise division into companies
			//

			convert_float_to_int (ceil (f_count / 3.0), &company_count);

			count = 0;

			loop = frontline_count - 1;

			for (c = 0; c < company_count; c ++)
			{
				company = create_new_division (ENTITY_SUB_TYPE_DIVISION_ARMOURED_COMPANY, (entity_sides) side, division, keysite, TRUE);

				n = 0;

				while ((loop >= 0) && (rating [loop] != FLT_MAX) && (n < 3) && (count < f_count))
				{
					//
					// link group to company
					//

					en = frontline_groups [loop];

					ASSERT (!get_local_entity_parent (en, LIST_TYPE_DIVISION));

					add_group_to_division (en, company);

					n ++;

					count ++;

					loop --;
				}
			}

			free_mem (rating);
		}

		//
		// Sort Artillery groups
		//

		if (artillery_groups)
		{
			int
				c,
				company_count;

			entity
				*company;

			ASSERT (artillery_count > 0);

			rating = (float*) malloc_heap_mem (sizeof (float) * artillery_count);

			for (loop = 0; loop < artillery_count; loop ++)
			{
				en = artillery_groups [loop];

				if (get_local_entity_parent (en, LIST_TYPE_DIVISION))
				{
					rating [loop] = FLT_MAX;
				}
				else if (en == first_group)
				{
					rating [loop] = 0.0;
				}
				else
				{
					pos2 = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

					rating [loop] = get_2d_range (pos1, pos2);
				}
			}

			quicksort_entity_list (artillery_groups, artillery_count, rating);

			//
			// organise division into companies
			//

			convert_float_to_int (a_count, &company_count);

			loop = artillery_count - 1;

			for (c = 0; c < company_count; c ++)
			{
				company = create_new_division (ENTITY_SUB_TYPE_DIVISION_ARTILLERY_COMPANY, (entity_sides) side, division, keysite, TRUE);

				en = artillery_groups [loop];

				ASSERT (!get_local_entity_parent (en, LIST_TYPE_DIVISION));

				add_group_to_division (en, company);

				loop --;
			}

			free_mem (rating);
		}
	}

	//
	// Check for any groups not in a division
	//


	//
	// Free memory
	//

	if (frontline_groups)
	{
		free_mem (frontline_groups);
	}

	if (artillery_groups)
	{
		free_mem (artillery_groups);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_airborne_divisions (entity *force)
{
	entity
		*keysite,
		*hc_division,
		*fw_division,
		*transport_division;

	int
		side;

	ASSERT (force);

	side = get_local_entity_int_value (force, INT_TYPE_SIDE);

	hc_division = create_new_division (ENTITY_SUB_TYPE_DIVISION_AIRBORNE_HELICOPTER_DIVISION, (entity_sides) side, force, NULL, TRUE);

	fw_division = create_new_division (ENTITY_SUB_TYPE_DIVISION_AIRBORNE_FIXED_WING_DIVISION, (entity_sides) side, force, NULL, TRUE);

	transport_division = create_new_division (ENTITY_SUB_TYPE_DIVISION_AIRBORNE_TRANSPORT_DIVISION, (entity_sides) side, force, NULL, TRUE);

	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_AIRBASE)
		{
			//
			// Assign one company of each type per airbase
			//

			create_new_division (ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY, (entity_sides) side, hc_division, keysite, TRUE);

			create_new_division (ENTITY_SUB_TYPE_DIVISION_HC_TRANSPORT_COMPANY, (entity_sides) side, transport_division, keysite, TRUE);

			create_new_division (ENTITY_SUB_TYPE_DIVISION_FW_ATTACK_COMPANY, (entity_sides) side, fw_division, keysite, TRUE);

			create_new_division (ENTITY_SUB_TYPE_DIVISION_FW_FIGHTER_COMPANY, (entity_sides) side, fw_division, keysite, TRUE);

			create_new_division (ENTITY_SUB_TYPE_DIVISION_FW_TRANSPORT_COMPANY, (entity_sides) side, transport_division, keysite, TRUE);
		}
		else if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE)
		{
			//
			// Assign one company of each type per carrier
			//

			create_new_division (ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY, (entity_sides) side, hc_division, keysite, TRUE);

			create_new_division (ENTITY_SUB_TYPE_DIVISION_HC_TRANSPORT_COMPANY, (entity_sides) side, hc_division, keysite, TRUE);
		}

		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_infantry_divisions (entity *force)
{
	entity
		*keysite,
		*division;

	int
		side;

	ASSERT (force);

	side = get_local_entity_int_value (force, INT_TYPE_SIDE);

	division = create_new_division (ENTITY_SUB_TYPE_DIVISION_INFANTRY_DIVISION, (entity_sides) side, force, NULL, TRUE);

	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_AIRBASE)
		{
			//
			// Assign one company of each type per airbase
			//

			create_new_division (ENTITY_SUB_TYPE_DIVISION_INFANTRY_COMPANY, (entity_sides) side, division, keysite, TRUE);
		}

		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_carrier_divisions (entity *force)
{
	entity
		*keysite,
		*group,
		*company,
		*division;

	int
		side;

	ASSERT (force);

	side = get_local_entity_int_value (force, INT_TYPE_SIDE);

	division = create_new_division (ENTITY_SUB_TYPE_DIVISION_CARRIER_DIVISION, (entity_sides) side, force, NULL, TRUE);

	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE)
		{
			//
			// Assign one company per carrier
			//

			company = create_new_division (ENTITY_SUB_TYPE_DIVISION_CARRIER_COMPANY, (entity_sides) side, division, keysite, TRUE);

			//
			// Assign everything at that carrier to the company
			//

			group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);

			while (group)
			{
				if (get_local_entity_int_value (group, INT_TYPE_MOVEMENT_TYPE) == MOVEMENT_TYPE_SEA)
				{
					ASSERT (!get_local_entity_parent (group, LIST_TYPE_DIVISION));

					add_group_to_division (group, company);
				}

				group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
			}
		}

		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void assign_remaining_groups_to_divisions (entity *force)
{
	entity
		*group;

	ASSERT (force);

	//
	// AIR
	//

	group = get_local_entity_first_child (force, LIST_TYPE_AIR_REGISTRY);

	while (group)
	{
		if (!get_local_entity_parent (group, LIST_TYPE_DIVISION))
		{
			add_group_to_division (group, NULL);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_AIR_REGISTRY);
	}

	//
	// GROUND
	//

	group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

	while (group)
	{
		if (!get_local_entity_parent (group, LIST_TYPE_DIVISION))
		{
			add_group_to_division (group, NULL);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
	}

	//
	// SEA
	//

	group = get_local_entity_first_child (force, LIST_TYPE_SEA_REGISTRY);

	while (group)
	{
		if (!get_local_entity_parent (group, LIST_TYPE_DIVISION))
		{
			add_group_to_division (group, NULL);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_SEA_REGISTRY);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_order_of_battle (void)
{
	entity
		*force;

	ASSERT (get_session_entity ());

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		initialise_armoured_divisions (force);

		initialise_airborne_divisions (force);

		initialise_carrier_divisions (force);

		initialise_infantry_divisions (force);

		assign_remaining_groups_to_divisions (force);

		#if DEBUG_MODULE

		debug_output_force_order_of_battle (force);

		#endif

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static void debug_output_division (entity *en)
{
	int
		sub_type,
		id;

	entity
		*next,
		*hq;

	ASSERT (en);

	if (get_local_entity_type (en) == ENTITY_TYPE_GROUP)
	{
		debug_filtered_log ("%s (%s %d)", get_local_entity_string (en, STRING_TYPE_DIVISION_NAME), get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));
	}
	else
	{
		next = get_local_entity_first_child (en, LIST_TYPE_DIVISION);

		if (next)
		{
			id = get_local_entity_int_value (en, INT_TYPE_DIVISION_ID);

			sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

			hq = get_local_entity_parent (en, LIST_TYPE_DIVISION_HEADQUARTERS);

			if (hq)
			{
				debug_filtered_log ("%s (@ %s)", get_local_entity_string (en, STRING_TYPE_DIVISION_NAME), get_local_entity_string (hq, STRING_TYPE_KEYSITE_NAME));
			}
			else
			{
				debug_filtered_log ("%s", get_local_entity_string (en, STRING_TYPE_DIVISION_NAME));
			}

			while (next)
			{
				debug_output_division (next);

				next = get_local_entity_child_succ (next, LIST_TYPE_DIVISION);
			}
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

void debug_output_force_order_of_battle (entity *force)
{
	entity
		*en;

	ASSERT (force);

	debug_filtered_log ("%s", entity_side_names [get_local_entity_int_value (force, INT_TYPE_SIDE)]);

	en = get_local_entity_first_child (force, LIST_TYPE_DIVISION);

	while (en)
	{
		debug_output_division (en);

		en = get_local_entity_child_succ (en, LIST_TYPE_DIVISION);
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
