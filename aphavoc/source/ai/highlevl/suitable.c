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

#define DEBUG_MODULE   0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	**group_task_array = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float calculate_group_to_task_suitability (entity_sub_types group_type, entity_sub_types task_type)
{

	const ai_statistics
		*group_factors,
		*task_factors;

	float
		a,
		b,
		result;

	int
		landing_type;

	ASSERT (group_task_array);

	group_factors = &(group_database [group_type].ai_stats);

	task_factors = &(task_database [task_type].ai_stats);

	//
	// Critical factors
	//

	// Movement type 

	if ((task_database [task_type].movement_type != MOVEMENT_TYPE_ALL) && (task_database [task_type].movement_type != group_database [group_type].movement_type))
	{
		return 0.0;
	}

	landing_type = group_database [group_type].default_landing_type;

	if (!(task_database [task_type].landing_types & (1 << landing_type)))
	{
		return 0.0;
	}

	// Movement speed 

	if (task_factors->movement_speed > group_factors->movement_speed)
	{
		return 0.0;
	}

	// Movement stealth

	if (task_factors->movement_stealth > group_factors->movement_stealth)
	{
		return 0.0;
	}

	// Cargo space

	if (task_factors->cargo_space > group_factors->cargo_space)
	{
		return 0.0;
	}

	// Troop space

	if (task_factors->troop_space > group_factors->troop_space)
	{
		return 0.0;
	}

	// Ground Attack Strength

	if (task_factors->ground_attack_strength > group_factors->ground_attack_strength)
	{
		return 0.0;
	}

	// Air Attack Strength

	if (task_factors->air_attack_strength > group_factors->air_attack_strength)
	{
		return 0.0;
	}

	// Engage enemy (If task requires engagement - group must be capable)

	if (task_database [task_type].engage_enemy)
	{
		if (!group_database [group_type].default_engage_enemy)
		{
			return 0.0;
		}
	}

	//
	// Non Critical factors
	//

	result = 1.0;

	if (task_factors->air_attack_strength > 0)
	{
		a = (float)(group_factors->air_attack_strength);

		b = (float)(task_factors->air_attack_strength);

		result *= min ((a / b), 1.0);
	}

	if (task_factors->ground_attack_strength > 0)
	{
		a = (float)(group_factors->ground_attack_strength);

		b = (float)(task_factors->ground_attack_strength);

		result *= min ((a / b), 1.0);
	}

	ASSERT ((result >= 0.0) && (result <= 1.0));

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_group_to_task_suitability (entity_sub_types group_type, entity_sub_types task_type)
{
	// JB 030313 Fly any aircraft (test code)
	// return 1;
	return group_task_array [group_type][task_type];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_group_task_array (void)
{
	int
		group,
		task;

	ASSERT (!group_task_array);

	group_task_array = malloc_heap_mem (sizeof (float *) * NUM_ENTITY_SUB_TYPE_GROUPS);

	for (group = 0; group < NUM_ENTITY_SUB_TYPE_GROUPS; group ++)
	{
		group_task_array [group] = malloc_heap_mem (sizeof (float) * NUM_ENTITY_SUB_TYPE_TASKS);

		for (task = 0; task < NUM_ENTITY_SUB_TYPE_TASKS; task ++)
		{
			group_task_array [group][task] = calculate_group_to_task_suitability (group, task);
		}
	}

	#if DEBUG_MODULE

	for (task = 0; task < NUM_ENTITY_SUB_TYPE_TASKS; task ++)
	{
		debug_filtered_log ("TASK %s", task_database [task].full_name);
		debug_filtered_log ("=========================");

		for (group = 0; group < NUM_ENTITY_SUB_TYPE_GROUPS; group ++)
		{
			if (group_task_array [group][task] > 0.0)
			{
				debug_filtered_log ("%s (%f)", group_database [group].full_name, group_task_array [group][task]);
			}
		}

		debug_filtered_log ("");
		debug_filtered_log ("");
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_group_task_array (void)
{
	int
		loop;

	ASSERT (group_task_array);

	for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_GROUPS; loop ++)
	{
		free_mem (group_task_array [loop]);
	}

	free_mem (group_task_array);

	group_task_array = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

