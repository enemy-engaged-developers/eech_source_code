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

#define DEBUG_UPDATE_LIST_VALIDATION 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_destroy_local_entity[NUM_ENTITY_TYPES]) (entity *en);

void (*fn_destroy_client_server_entity[NUM_ENTITY_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en);

void (*fn_destroy_local_entity_family[NUM_ENTITY_TYPES]) (entity *en);

void (*fn_destroy_client_server_entity_family[NUM_ENTITY_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en);

void (*fn_kill_local_entity[NUM_ENTITY_TYPES]) (entity *en);

void (*fn_kill_client_server_entity[NUM_ENTITY_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_destroy_entity (entity *en)
{
//Werewolf 14 May 2003
//	debug_fatal ("default_destroy_entity invoked: %s (index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_destroy_entity_family (entity *en)
{
   debug_fatal ("default_destroy_entity_family invoked: %s (index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_kill_entity (entity *en)
{
	debug_fatal ("default_kill_entity invoked: %s (index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_destroy_default_functions (void)
{
   int
      i;

   for (i = 0; i < NUM_ENTITY_TYPES; i++)
   {
      fn_destroy_local_entity[i]													= default_destroy_entity;

      fn_destroy_client_server_entity[i][COMMS_MODEL_SERVER]			= default_destroy_entity;

      fn_destroy_client_server_entity[i][COMMS_MODEL_CLIENT]			= default_destroy_entity;

      fn_destroy_local_entity_family[i]										= default_destroy_entity_family;

      fn_destroy_client_server_entity_family[i][COMMS_MODEL_SERVER]	= default_destroy_entity_family;

      fn_destroy_client_server_entity_family[i][COMMS_MODEL_CLIENT]	= default_destroy_entity_family;

      fn_kill_local_entity[i]														= default_kill_entity;

      fn_kill_client_server_entity[i][COMMS_MODEL_SERVER]				= default_kill_entity;

      fn_kill_client_server_entity[i][COMMS_MODEL_CLIENT]				= default_kill_entity;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_local_entity (entity *en)
{
   update_destroy_entity_statistics (en);

	#if DEBUG_MODULE
	{

		static int
			reported_segment = FALSE,
			reported_city_building = FALSE,
			reported_sector = FALSE;

		#if DEBUG_UPDATE_LIST_VALIDATION

		entity
			*succ,
			*pred,
			*updt;

		if (get_update_entity ())
		{
		
			updt = get_local_entity_first_child (get_update_entity (), LIST_TYPE_UPDATE);
	
			while (updt)
			{
	
				ASSERT (updt->type != ENTITY_TYPE_UNKNOWN);

				succ = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);

				if (succ)
				{

					ASSERT (get_local_entity_child_pred (succ, LIST_TYPE_UPDATE) == updt);
				}

				pred = get_local_entity_child_pred (updt, LIST_TYPE_UPDATE);

				if (pred)
				{

					ASSERT (get_local_entity_child_succ (pred, LIST_TYPE_UPDATE) == updt);
				}
	
				updt = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);
			}
		}

		#endif
	
		switch (get_local_entity_type (en))
		{
	
			case ENTITY_TYPE_SEGMENT:
			case ENTITY_TYPE_SECTOR:
			case ENTITY_TYPE_CITY_BUILDING:
			{
	
				if (get_local_entity_type (en) == ENTITY_TYPE_SEGMENT)
				{
		
					if (reported_segment)
					{
		
						break;
					}
		
					reported_segment = TRUE;
				}
	
				if (get_local_entity_type (en) == ENTITY_TYPE_SECTOR)
				{
		
					if (reported_sector)
					{
		
						break;
					}
		
					reported_sector = TRUE;
				}
	
				if (get_local_entity_type (en) == ENTITY_TYPE_CITY_BUILDING)
				{
		
					if (reported_city_building)
					{
		
						break;
					}
		
					reported_city_building = TRUE;
				}
			}
			default:
			{
	
				debug_log ("EN_DSTRY: destroyed %s, index %d, sub_type %d", get_local_entity_type_name (en), get_local_entity_index (en), get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
	
				break;
			} 
		}
	}
	#endif

   fn_destroy_local_entity[get_local_entity_type(en)] (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_local_entities (void)
{
	entity
		*en;

	en = get_local_entity_list ();

	while (en)
   {

		#if DEBUG_MODULE
		{

			static int
				reported_segment = FALSE,
				reported_city_building = FALSE,
				reported_sector = FALSE;
	
			#if DEBUG_UPDATE_LIST_VALIDATION

			entity
				*succ,
				*pred,
				*updt;
	
			if (get_update_entity ())
			{
			
				updt = get_local_entity_first_child (get_update_entity (), LIST_TYPE_UPDATE);
		
				while (updt)
				{
		
					ASSERT (updt->type != ENTITY_TYPE_UNKNOWN);
	
					succ = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);
	
					if (succ)
					{
	
						ASSERT (get_local_entity_child_pred (succ, LIST_TYPE_UPDATE) == updt);
					}
	
					pred = get_local_entity_child_pred (updt, LIST_TYPE_UPDATE);
	
					if (pred)
					{
	
						ASSERT (get_local_entity_child_succ (pred, LIST_TYPE_UPDATE) == updt);
					}
		
					updt = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);
				}
			}

			#endif

			switch (get_local_entity_type (en))
			{
		
				case ENTITY_TYPE_SEGMENT:
				case ENTITY_TYPE_SECTOR:
				case ENTITY_TYPE_CITY_BUILDING:
				{
		
					if (get_local_entity_type (en) == ENTITY_TYPE_SEGMENT)
					{
			
						if (reported_segment)
						{
			
							break;
						}
			
						reported_segment = TRUE;
					}
		
					if (get_local_entity_type (en) == ENTITY_TYPE_SECTOR)
					{
			
						if (reported_sector)
						{
			
							break;
						}
			
						reported_sector = TRUE;
					}
		
					if (get_local_entity_type (en) == ENTITY_TYPE_CITY_BUILDING)
					{
			
						if (reported_city_building)
						{
			
							break;
						}
			
						reported_city_building = TRUE;
					}
				}
				default:
				{
		
					debug_log ("EN_DSTRY: destroying %s, index %d, sub_type %d", get_local_entity_type_name (en), get_local_entity_index (en), get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
		
					break;
				} 
			}
		}
		#endif

      destroy_local_entity_family (en);

		en = get_local_entity_list ();
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_local_entity_children (entity *en, list_types list)
{
   entity
      *child;

   child = get_local_entity_first_child (en, list);

   while (child)
   {

		#if DEBUG_MODULE
		{

			static int
				reported_segment = FALSE,
				reported_city_building = FALSE,
				reported_sector = FALSE;
	
			#if DEBUG_UPDATE_LIST_VALIDATION

			entity
				*succ,
				*pred,
				*updt;
		
			if (get_update_entity ())
			{
			
				updt = get_local_entity_first_child (get_update_entity (), LIST_TYPE_UPDATE);
		
				while (updt)
				{
		
					ASSERT (updt->type != ENTITY_TYPE_UNKNOWN);
	
					succ = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);
	
					if (succ)
					{
	
						ASSERT (get_local_entity_child_pred (succ, LIST_TYPE_UPDATE) == updt);
					}
	
					pred = get_local_entity_child_pred (updt, LIST_TYPE_UPDATE);
	
					if (pred)
					{
	
						ASSERT (get_local_entity_child_succ (pred, LIST_TYPE_UPDATE) == updt);
					}
		
					updt = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);
				}
			}

			#endif
			
			switch (get_local_entity_type (en))
			{
		
				case ENTITY_TYPE_SEGMENT:
				case ENTITY_TYPE_SECTOR:
				case ENTITY_TYPE_CITY_BUILDING:
				{
		
					if (get_local_entity_type (en) == ENTITY_TYPE_SEGMENT)
					{
			
						if (reported_segment)
						{
			
							break;
						}
			
						reported_segment = TRUE;
					}
		
					if (get_local_entity_type (en) == ENTITY_TYPE_SECTOR)
					{
			
						if (reported_sector)
						{
			
							break;
						}
			
						reported_sector = TRUE;
					}
		
					if (get_local_entity_type (en) == ENTITY_TYPE_CITY_BUILDING)
					{
			
						if (reported_city_building)
						{
			
							break;
						}
			
						reported_city_building = TRUE;
					}
				}
				default:
				{
	
					debug_log ("EN_DSTRY: destroying %s, index %d, sub_type %d", get_local_entity_type_name (child), get_local_entity_index (child), get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
		
					break;
				} 
			}
		}
		#endif

      destroy_local_entity_family (child);

      child = get_local_entity_first_child (en, list);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_client_server_entity_children (entity *en, list_types list)
{
   entity
      *child;

   child = get_local_entity_first_child (en, list);

   while (child)
   {

		#if DEBUG_MODULE
		{

			static int
				reported_segment = FALSE,
				reported_city_building = FALSE,
				reported_sector = FALSE;
	
			#if DEBUG_UPDATE_LIST_VALIDATION

			entity
				*succ,
				*pred,
				*updt;
		
			if (get_update_entity ())
			{
			
				updt = get_local_entity_first_child (get_update_entity (), LIST_TYPE_UPDATE);
		
				while (updt)
				{
		
					ASSERT (updt->type != ENTITY_TYPE_UNKNOWN);

				succ = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);

				if (succ)
				{

					ASSERT (get_local_entity_child_pred (succ, LIST_TYPE_UPDATE) == updt);
				}

				pred = get_local_entity_child_pred (updt, LIST_TYPE_UPDATE);

				if (pred)
				{

					ASSERT (get_local_entity_child_succ (pred, LIST_TYPE_UPDATE) == updt);
				}
	
				updt = get_local_entity_child_succ (updt, LIST_TYPE_UPDATE);
				}
			}

			#endif

			switch (get_local_entity_type (en))
			{
		
				case ENTITY_TYPE_SEGMENT:
				case ENTITY_TYPE_SECTOR:
				case ENTITY_TYPE_CITY_BUILDING:
				{
		
					if (get_local_entity_type (en) == ENTITY_TYPE_SEGMENT)
					{
			
						if (reported_segment)
						{
			
							break;
						}
			
						reported_segment = TRUE;
					}
		
					if (get_local_entity_type (en) == ENTITY_TYPE_SECTOR)
					{
			
						if (reported_sector)
						{
			
							break;
						}
			
						reported_sector = TRUE;
					}
		
					if (get_local_entity_type (en) == ENTITY_TYPE_CITY_BUILDING)
					{
			
						if (reported_city_building)
						{
			
							break;
						}
			
						reported_city_building = TRUE;
					}
				}
				default:
				{
	
					debug_log ("EN_DSTRY: destroying %s, index %d, sub_type %d", get_local_entity_type_name (child), get_local_entity_index (child), get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
		
					break;
				} 
			}
		}
		#endif

      destroy_client_server_entity_family (child);

      child = get_local_entity_first_child (en, list);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_local_only_entities (void)
{

	destroy_local_sector_entities ();

	//
	// These functions just assert that the entities have been destroyed by the destroy_local_entity_family system
	//

	destroy_local_pylon_entities ();

	destroy_local_update_entity ();

	destroy_local_camera_entity ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
