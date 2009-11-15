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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"
#include "ai/highlevl/imaps.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void pack_local_data (entity *en, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void unpack_local_data (entity *en, entity_types type, pack_modes mode)
{

	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			//
			// always use access functions to set the data
			//

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_keysite_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_KEYSITE]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_KEYSITE]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_keysite_data (pack_modes mode)
{
   entity
      *en,
		*landing_en;

	landing
		*landing_raw;

   keysite
      *raw;

   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode == PACK_MODE_BROWSE_SESSION)
   {
      return;
   }

	en = get_local_entity_list ();

	while (en)
	{

		if (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE)
		{

			//
			// pack keysite data
			//

			pack_entity_safe_ptr (en);

			raw = (keysite *) get_local_entity_data (en);

			pack_float_value (en, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, raw->supplies.ammo_supply_level);

			pack_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, raw->supplies.fuel_supply_level);

			pack_float_value (en, FLOAT_TYPE_KEYSITE_STRENGTH, raw->keysite_strength);

			pack_float_value (en, FLOAT_TYPE_KEYSITE_MAXIMUM_STRENGTH, raw->keysite_maximum_strength);

			pack_int_value (en, INT_TYPE_ALIVE, raw->alive);

			pack_int_value (en, INT_TYPE_SIDE, raw->side);

			pack_int_value (en, INT_TYPE_IN_USE, raw->in_use);

			pack_int_value (en, INT_TYPE_KEYSITE_ID, raw->keysite_id);

			pack_int_value (en, INT_TYPE_KEYSITE_USABLE_STATE, raw->keysite_usable_state);

			pack_list_root (en, LIST_TYPE_UNASSIGNED_TASK, &raw->unassigned_task_root);
			pack_list_root (en, LIST_TYPE_ASSIGNED_TASK, &raw->assigned_task_root);
			pack_list_root (en, LIST_TYPE_COMPLETED_TASK, &raw->completed_task_root);

//			pack_list_root (en, LIST_TYPE_KEYSITE_GROUP, &raw->keysite_group_root);

			pack_list_root (en, LIST_TYPE_DIVISION_HEADQUARTERS, &raw->division_headquarters_root);

			if (raw->campaign_objective_link.parent)
			{
				pack_int_value (en, INT_TYPE_VALID, TRUE);

				pack_list_link (en, LIST_TYPE_CAMPAIGN_OBJECTIVE, &raw->campaign_objective_link);
			}
			else
			{
				pack_int_value (en, INT_TYPE_VALID, FALSE);
			}

			#if DEBUG_MODULE

			debug_log ("KS_PACK: packing up keysite %s", raw->keysite_name);

			#endif

			if (mode == PACK_MODE_SERVER_SESSION)
			{
	
				pack_float_value (en, FLOAT_TYPE_REPAIR_TIMER, raw->repair_timer);

				pack_float_value (en, FLOAT_TYPE_SLEEP, raw->sleep);

				pack_float_value (en, FLOAT_TYPE_ASSIST_TIMER, raw->assist_timer);

				pack_float_value (en, FLOAT_TYPE_ASSIGN_TIMER, raw->assign_timer);

				//
				// pack landing data
				//
	
				landing_en = get_local_entity_first_child (en, LIST_TYPE_LANDING_SITE);
	
				while (landing_en)
				{
	
					landing_raw = (landing *) get_local_entity_data (landing_en);
	
					pack_int_value (landing_en, INT_TYPE_RESERVED_LANDING_SITES, landing_raw->reserved_landing_sites);
	
					//pack_int_value (en, INT_TYPE_FREE_LANDING_SITES, landing_raw->free_landing_sites);
	
					pack_int_value (landing_en, INT_TYPE_LANDING_LOCK, landing_raw->landing_lock);
	
					pack_int_value (landing_en, INT_TYPE_LANDED_LOCK, landing_raw->landed_lock);
	
					pack_int_value (landing_en, INT_TYPE_TAKEOFF_LOCK, landing_raw->takeoff_lock);

					pack_list_root (landing_en, LIST_TYPE_TAKEOFF_QUEUE, &landing_raw->takeoff_queue_root);

					#if DEBUG_MODULE

					debug_log ("KS_PACK: packing up %s landing entity, reserved %d, free %d, locks (landing %d, landed %d, takeoff %d)", entity_sub_type_landing_names [landing_raw->sub_type], landing_raw->reserved_landing_sites, landing_raw->free_landing_sites, landing_raw->landing_lock, landing_raw->landed_lock, landing_raw->takeoff_lock );

					#endif
	
					landing_en = get_local_entity_child_succ (landing_en, LIST_TYPE_LANDING_SITE);
				}
			}

		}

		en = get_local_entity_succ (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_keysite_data (pack_modes mode)
{
   entity
      *en,
		*landing_en;

	landing
		*landing_raw;

   keysite
      *raw;

	int
		side,
		landing_lock,
		landed_lock,
		takeoff_lock,
		in_use,
		index;

   ASSERT (mode != PACK_MODE_UPDATE_ENTITY);

   if (mode == PACK_MODE_BROWSE_SESSION)
   {
      return;
   }

	en = get_local_entity_list ();

	while (en)
	{

		if (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE)
		{

			//
			// unpack keysite
			//

			index = unpack_entity_safe_index ();

			raw = (keysite *) get_local_entity_data (en);

			raw->supplies.ammo_supply_level = unpack_float_value (en, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

			raw->supplies.fuel_supply_level = unpack_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

			raw->keysite_strength = unpack_float_value (en, FLOAT_TYPE_KEYSITE_STRENGTH);

			raw->keysite_maximum_strength = unpack_float_value (en, FLOAT_TYPE_KEYSITE_MAXIMUM_STRENGTH);

			raw->alive = unpack_int_value (en, INT_TYPE_ALIVE);

			side = unpack_int_value (en, INT_TYPE_SIDE);

			if (side != raw->side)
			{
				//
				// update I-Maps (remove old side)
				//

				if (raw->in_use)
				{
					update_imap_sector_side (en, FALSE);

					if (mode == PACK_MODE_SERVER_SESSION)
					{
						update_imap_importance_level (en, FALSE);
					}
				}

				//
				// change side of keysite buildings
				//

				change_local_keysite_building_sides (en, (entity_sides) side);

				//
				// place into other sides force
				//

				delete_local_entity_from_parents_child_list (en, LIST_TYPE_KEYSITE_FORCE);

				insert_local_entity_into_parents_child_list (en, LIST_TYPE_KEYSITE_FORCE, get_local_force_entity ((entity_sides) side), NULL);

				if (mode == PACK_MODE_SERVER_SESSION)
				{
					// Must be done after removed from force
					update_imap_distance_to_friendly_base ((entity_sides) raw->side);
				}

				//
				// switch sides
				//

				raw->side = side;

				//
				// update I-Maps (add new side)
				//

				if (raw->in_use)
				{
					update_imap_sector_side (en, TRUE);

					if (mode == PACK_MODE_SERVER_SESSION)
					{
						update_imap_importance_level (en, TRUE);

						update_keysite_distance_to_friendly_base (en, (entity_sides) side);
					}
				}
			}

			in_use = unpack_int_value (en, INT_TYPE_IN_USE);

			raw->keysite_id = unpack_int_value (en, INT_TYPE_KEYSITE_ID);

			raw->keysite_usable_state = unpack_int_value (en, INT_TYPE_KEYSITE_USABLE_STATE);

			if (raw->in_use != in_use)
			{
				//
				// Update I-Maps (in use flag changed)
				//

				raw->in_use = in_use;

				update_imap_sector_side (en, in_use);

				if (mode == PACK_MODE_SERVER_SESSION)
				{
					update_imap_importance_level (en, in_use);

					if (in_use)
					{
						update_keysite_distance_to_friendly_base (en, (entity_sides) side);
					}
					else
					{
						update_imap_distance_to_friendly_base ((entity_sides) side);
					}
				}
			}

			unpack_list_root (en, LIST_TYPE_UNASSIGNED_TASK, &raw->unassigned_task_root);
			unpack_list_root (en, LIST_TYPE_ASSIGNED_TASK, &raw->assigned_task_root);
			unpack_list_root (en, LIST_TYPE_COMPLETED_TASK, &raw->completed_task_root);

//			unpack_list_root (en, LIST_TYPE_KEYSITE_GROUP, &raw->keysite_group_root);

			unpack_list_root (en, LIST_TYPE_DIVISION_HEADQUARTERS, &raw->division_headquarters_root);

			if (unpack_int_value (en, INT_TYPE_VALID))
			{
				unpack_list_link (en, LIST_TYPE_CAMPAIGN_OBJECTIVE, &raw->campaign_objective_link);
			}

			#if DEBUG_MODULE

			debug_log ("KS_PACK: unpacking keysite %s", raw->keysite_name);

			#endif

			if (mode == PACK_MODE_SERVER_SESSION)
			{
				raw->repair_timer = unpack_float_value (en, FLOAT_TYPE_REPAIR_TIMER);

				raw->sleep = unpack_float_value (en, FLOAT_TYPE_SLEEP);

				raw->assist_timer = unpack_float_value (en, FLOAT_TYPE_ASSIST_TIMER);

				raw->assign_timer = unpack_float_value (en, FLOAT_TYPE_ASSIGN_TIMER);

				//
				// unpack landing data
				//

				landing_en = get_local_entity_first_child (en, LIST_TYPE_LANDING_SITE);
	
				while (landing_en)
				{
	
					landing_raw = (landing *) get_local_entity_data (landing_en);
	
					landing_raw->reserved_landing_sites = unpack_int_value (landing_en, INT_TYPE_RESERVED_LANDING_SITES);
	
					//landing_raw->free_landing_sites = unpack_int_value (en, INT_TYPE_FREE_LANDING_SITES);
					landing_raw->free_landing_sites = landing_raw->total_landing_sites;
	
					landing_lock = unpack_int_value (landing_en, INT_TYPE_LANDING_LOCK);
	
					landed_lock = unpack_int_value (landing_en, INT_TYPE_LANDED_LOCK);
	
					takeoff_lock = unpack_int_value (landing_en, INT_TYPE_TAKEOFF_LOCK);
	
					#if DEBUG_MODULE

					debug_log ("KS_PACK: %s (%d) unpacking %s landing entity, reserved %d, free %d, locks (saved :landing %d, landed %d, takeoff %d, calc landing %d, landed %d, takeoff %d)",
									raw->keysite_name,
									get_local_entity_index (en),
									entity_sub_type_landing_names [landing_raw->sub_type],
									landing_raw->reserved_landing_sites, landing_raw->free_landing_sites,
									landing_lock, landed_lock, takeoff_lock,
									landing_raw->landing_lock, landing_raw->landed_lock, landing_raw->takeoff_lock);

					if (landing_raw->landing_lock != landing_lock)
					{

						debug_log ("KS_PACK: %s %s landing entity needs landing_lock repairing", raw->keysite_name, entity_sub_type_landing_names [landing_raw->sub_type]);
					}
					if (landing_raw->landed_lock != landed_lock)
					{

						debug_log ("KS_PACK: %s %s landing entity needs landed_lock repairing", raw->keysite_name, entity_sub_type_landing_names [landing_raw->sub_type]);
					}
					if (landing_raw->takeoff_lock != takeoff_lock)
					{

						debug_log ("KS_PACK: %s %s landing entity needs takeoff_lock repairing", raw->keysite_name, entity_sub_type_landing_names [landing_raw->sub_type]);
					}

					#endif
	
					unpack_list_root (landing_en, LIST_TYPE_TAKEOFF_QUEUE, &landing_raw->takeoff_queue_root);

					landing_en = get_local_entity_child_succ (landing_en, LIST_TYPE_LANDING_SITE);
				}
			}
		}

		en = get_local_entity_succ (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
