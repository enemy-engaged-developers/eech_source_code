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

static void update_server (entity *en)
{

	routed_vehicle
		*raw;

	int
		loop;

	raw = get_local_entity_data (en);

	update_local_entity_view_interest_level (en);

	raw->vh.sleep -= get_delta_time ();

	raw->vh.sleep = max (raw->vh.sleep, 0.0);

	#if DEBUG_MODULE
	// debug
	{

		entity
			*group;

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group)
		{
		
			if (group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].frontline_flag)
			{
		
				if (get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP))
				{
		
					if (get_local_entity_type (get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP)) == ENTITY_TYPE_KEYSITE)
					{
	
						if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDED)
						{
	
							entity
								*task;
	
							task = get_local_entity_current_task (en);
	
							if (task)
							{
	
								if ((get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_TASK_LANDING) &&
									(get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_TASK_TAKEOFF) &&
									(get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING))
								{
	
									debug_fatal ("GP_UPDAT: frontline entity %s, %d connected to KEYSITE", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));
								}
							}
						}
					}
				}
			}
		}
	
	}
	#endif
	// debug

	if (raw->vh.mob.alive)
	{

		//
		// Update
		//

		for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
		{

			routed_vehicle_movement (en);
		}

		////////////////////////////////////////

		update_vehicle_loading_doors (en);

		update_vehicle_radar (en);

		////////////////////////////////////////
		//
		// ORDER IS CRITICAL
		//

		update_vehicle_target_scan (en);
			
		update_vehicle_weapon_system_ready (en);
	
		update_entity_weapon_systems (en);
	
		update_entity_weapon_system_weapon_and_target_vectors (en);
	
		update_vehicle_weapon_fire (en);

		update_vehicle_decoy_release (en);

		//
		////////////////////////////////////////
	}
	else
	{
		if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_DEAD)
		{
			raw->vh.death_timer -= get_delta_time ();

			if (raw->vh.death_timer <= 0.0)
			{
				destroy_client_server_entity_family (en);
			}
		}
		else
		{
			for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
			{
				get_3d_terrain_point_data (raw->vh.mob.position.x, raw->vh.mob.position.z, &raw->vh.terrain_info);

				routed_vehicle_death_movement (en);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	routed_vehicle
		*raw;

	int
		loop;

	raw = get_local_entity_data (en);

	raw->vh.sleep -= get_delta_time ();

	raw->vh.sleep = max (raw->vh.sleep, 0.0);

	update_local_entity_view_interest_level (en);

	if (raw->vh.mob.alive)
	{

		////////////////////////////////////////

		for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
		{

			routed_vehicle_movement (en);
		}

		////////////////////////////////////////

		update_vehicle_loading_doors (en);

		update_vehicle_radar (en);

		////////////////////////////////////////
		//
		// ORDER IS CRITICAL
		//

		update_vehicle_weapon_system_ready (en);

		update_entity_weapon_systems (en);

		update_entity_weapon_system_weapon_and_target_vectors (en);

		//
		////////////////////////////////////////
	}
	else
	{
		if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_DEAD)
		{
		}
		else
		{
			for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
			{
				get_3d_terrain_point_data (raw->vh.mob.position.x, raw->vh.mob.position.z, &raw->vh.terrain_info);
	
				routed_vehicle_death_movement (en);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_routed_vehicle_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_ROUTED_VEHICLE][COMMS_MODEL_SERVER]	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_ROUTED_VEHICLE][COMMS_MODEL_CLIENT]	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
