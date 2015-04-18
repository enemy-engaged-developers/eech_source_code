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

#include "setup.h"

#include "order.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE   0

#define NUMBER_OF_CAMPAIGN_OBJECTIVES_PER_SIDE	5

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void create_force_campaign_objectives (entity *force);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_campaign (void)
{
	entity
		*force;
		
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_session_entity ());

	//
	// Create force overall campaign objectives
	//

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	ASSERT (force);

	while (force)
	{
		create_force_campaign_objectives (force);

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	//
	// Setup Order Of Battle
	//

	initialise_order_of_battle ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_force_campaign_objectives (entity *force)
{
	entity
		*keysite,
		*target_force,
		**list;

	int
		loop,
		count,
		side,
		target_side;

	float
		highest,
		*rating;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_session_entity ());

	ASSERT (force);

	side = get_local_entity_int_value (force, INT_TYPE_SIDE);

	//
	// count up potential objective keysites
	//

	count = 0;

	target_force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (target_force)
	{
		if (target_force != force)
		{
			keysite = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);

			while (keysite)
			{
				if (get_local_entity_int_value (keysite, INT_TYPE_POTENTIAL_CAMPAIGN_OBJECTIVE))
				{
					if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
					{
						count ++;
					}
				}

				keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
			}
		}

		target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
	}

	if (count == 0)
	{
		debug_fatal ("SETUP: No potential campaign objectives for side %s", entity_side_short_names [side]);
	}

	//
	// construct the list and rate each keysite according to sector importance
	//

	list = (entity **) malloc_heap_mem (sizeof (entity *) * count);

	rating = (float*)malloc_heap_mem (sizeof (float) * count);

	highest = 0.0;

	count = 0;

	target_force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (target_force)
	{
		if (target_force != force)
		{
			target_side = get_local_entity_int_value (target_force, INT_TYPE_SIDE);

			keysite = get_local_entity_first_child (target_force, LIST_TYPE_KEYSITE_FORCE);

			while (keysite)
			{
				if (get_local_entity_int_value (keysite, INT_TYPE_POTENTIAL_CAMPAIGN_OBJECTIVE))
				{
					if (get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
					{
						float
							actual_range;
	
						vec3d
							*pos;
	
						list [count] = keysite;
	
						pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
	
						get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, (entity_sides) target_side, pos, 1.0 * KILOMETRE, &actual_range, TRUE, keysite);
	
						rating [count] = actual_range;
	
						highest = max (highest, rating [count]);
		
						count ++;
					}
				}

				keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
			}
		}

		target_force = get_local_entity_child_succ (target_force, LIST_TYPE_FORCE);
	}

	//
	// Normalise ratings
	//

	if (highest == 0.0)
	{
		debug_fatal ("SETUP: No sector importance for side %s", entity_side_short_names [side]);
	}
	
	for (loop = 0; loop < count; loop ++)
	{
		rating [loop] = rating [loop] / highest;
	}

	//
	// obligatory random factor
	//

	for (loop = 0; loop < count; loop ++)
	{
		rating [loop] += frand1 ();
	}

	//
	// sort the list
	//

	quicksort_entity_list (list, count, rating);

	//
	// now find the best N targets and link them into the force
	//

	count = min (count, NUMBER_OF_CAMPAIGN_OBJECTIVES_PER_SIDE);

	for (loop = 0; loop < count; loop ++)
	{
		insert_local_entity_into_parents_child_list (list [loop], LIST_TYPE_CAMPAIGN_OBJECTIVE, force, NULL);

		debug_log ("Side %s Objective :- %s (%s)", entity_side_short_names [side],
						get_local_entity_string (list [loop], STRING_TYPE_KEYSITE_NAME),
						get_local_entity_string (list [loop], STRING_TYPE_FULL_NAME));
	}

	free_mem (list);

	free_mem (rating);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


