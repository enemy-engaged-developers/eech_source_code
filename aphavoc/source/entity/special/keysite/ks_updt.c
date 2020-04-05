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

#include "ai/highlevl/highlevl.h"
#include "ai/taskgen/taskgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
	keysite
		*raw = nullptr;

	entity_sides
		side;

	vec3d
		*pos = nullptr;

	raw = (keysite *) get_local_entity_data (en);

	if (!raw->alive)
	{
		return;
	}
	
	raw->assist_timer -= get_delta_time ();

	if (raw->assist_timer <= 0.0)
	{
		raw->assist_timer = 0.0;
	}

	raw->assign_timer -= get_delta_time ();

	if (raw->assign_timer <= 0.0)
	{
		if (raw->in_use)
		{
			assign_keysite_tasks (en, TASK_CATEGORY_RECON);
			assign_keysite_tasks (en, TASK_CATEGORY_STRIKE);
			assign_keysite_tasks (en, TASK_CATEGORY_SUPPORT);
		}

		raw->assign_timer = KEYSITE_TASK_ASSIGN_TIMER;

		if (raw->keysite_usable_state != KEYSITE_STATE_USABLE)
		{
			raw->assign_timer *= 2.0;
		}
	}

	raw->sleep -= get_delta_time ();

	if (raw->sleep <= 0.0)
	{
		raw->sleep = KEYSITE_UPDATE_SLEEP_TIMER;
	
		//
		// Keysite operation depending upon type
		//

		raw->supplies.ammo_supply_level += AMMO_USAGE_ACCELERATOR * keysite_database [raw->sub_type].default_supply_usage.ammo_supply_level;
	
		raw->supplies.fuel_supply_level += FUEL_USAGE_ACCELERATOR * keysite_database [raw->sub_type].default_supply_usage.fuel_supply_level;
				
		update_keysite_cargo (en, raw->supplies.ammo_supply_level, ENTITY_SUB_TYPE_CARGO_AMMO, CARGO_AMMO_SIZE);
	
		update_keysite_cargo (en, raw->supplies.fuel_supply_level, ENTITY_SUB_TYPE_CARGO_FUEL, CARGO_FUEL_SIZE);
		
		raw->supplies.ammo_supply_level = bound (raw->supplies.ammo_supply_level, KEYSITE_MINIMUM_AMMO_SUPPLY_LEVEL, 100.0);
		
		raw->supplies.fuel_supply_level = bound (raw->supplies.fuel_supply_level, KEYSITE_MINIMUM_FUEL_SUPPLY_LEVEL, 100.0);
	
		#if (DEBUG_MODULE || DEBUG_SUPPLY)

		if ((keysite_database [raw->sub_type].default_supply_usage.ammo_supply_level < 0.0) || 	
			(keysite_database [raw->sub_type].default_supply_usage.fuel_supply_level < 0.0))
		{

			debug_log ("KS_UPDT: SUPPLY_INFO: keysite %s %s ammo %.1f, fuel %.1f (usage %.2f, %.2f)",
						raw->keysite_name,
						entity_sub_type_keysite_names [raw->sub_type],
						raw->supplies.ammo_supply_level, raw->supplies.fuel_supply_level,
						keysite_database [raw->sub_type].default_supply_usage.ammo_supply_level,
						keysite_database [raw->sub_type].default_supply_usage.fuel_supply_level);
		}

		#endif
	}

	//
	// Check if keysite is being repaired.
	//

	if (raw->repair_timer > 2047)
		raw->repair_timer = 2047;
	
	if (raw->keysite_usable_state == KEYSITE_STATE_REPAIRING)
	{
		raw->repair_timer -= get_delta_time ();

		if (raw->repair_timer <= 0.0)
		{
			raw->repair_timer = 0.0;

			if (!repair_client_server_entity_keysite (en))
			{
				//
				// All buildings repaired - set state back to usable
				//

				set_client_server_entity_int_value (en, INT_TYPE_KEYSITE_USABLE_STATE, KEYSITE_STATE_USABLE);
			}
		}
	}
	else
	{
		static float task_timer = 0.0;
		
		task_timer += get_delta_time();
		
		if (task_timer < 1.0 * ONE_MINUTE)
			return;
		else
			task_timer = 0.0;
		
		//
		// Check if keysite needs repairing.
		//

		if (raw->keysite_strength < raw->keysite_maximum_strength)
		{
			if (keysite_database [raw->sub_type].repairable)
			{
				side = (entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE);

				if (!entity_is_object_of_task (en, ENTITY_SUB_TYPE_TASK_REPAIR, side))
				{
					pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

					if (create_repair_task (side, pos, en, 10.0, NULL, NULL))
					{
						ai_log ("(KEYSITE) Creating REPAIR mission to %s (strength %f / %f)", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME), raw->keysite_strength, raw->keysite_maximum_strength);
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_keysite_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_KEYSITE][COMMS_MODEL_SERVER]  	= update_server;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
