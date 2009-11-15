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

#define DEBUG_MODULE				0

#define DEBUG_MODULE_PACK_ONE	0

#define DEBUG_MODULE_PACK_ALL	(PACK_ENTIRE_SESSION || 0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*null_entity_pointer_message = "Overloaded entity function invoked with NULL entity pointer";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	**entity_type_names;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_type_data
	entity_type_database[NUM_ENTITY_TYPES] =
	{
		{
			"ENTITY_TYPE_UNKNOWN",						// name
			0,													// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_ANTI_AIRCRAFT",				// name
			sizeof (anti_aircraft),						// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_BRIDGE",						// name
			sizeof (bridge),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_CAMERA",						// name
			sizeof (camera),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_CARGO",							// name
			sizeof (cargo),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_CITY",							// name
			sizeof (city),									// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_CITY_BUILDING",				// name
			sizeof (city_building),						// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_CRATER",						// name
			sizeof (crater),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_DIVISION",						// name
			sizeof (division),							// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_EXPLOSION",					// name
			sizeof (explosion),							// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_FIXED_WING",					// name
			sizeof (fixed_wing),							// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_FORCE",							// name
			sizeof (force), 								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_GROUP",							// name
			sizeof (group),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_GUIDE",							// name
			sizeof (guide),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_HELICOPTER",					// name
			sizeof (helicopter),							// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_KEYSITE",						// name
			sizeof (keysite),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_LANDING",						// name
			sizeof (landing),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_OBJECT",						// name
			sizeof (object), 								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_PARTICLE",						// name
			sizeof (particle), 							// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_PERSON",						// name
			sizeof (person), 								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_PILOT",							// name
			sizeof (pilot),  								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_PYLON",							// name
			sizeof (pylon), 								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_REGEN",							// name
			sizeof (regen), 								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_ROUTED_VEHICLE",				// name
			sizeof (routed_vehicle), 					// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SCENIC",						// name
			sizeof (scenic), 								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SECTOR",						// name
			sizeof (sector),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SEGMENT",						// name
			sizeof (segment),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SESSION",						// name
			sizeof (session),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SHIP_VEHICLE",				// name
			sizeof (ship_vehicle),						// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SITE",							// name
			sizeof (site),									// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SITE_UPDATABLE",				// name
			sizeof (site_updatable),					// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SMOKE_LIST",					// name
			sizeof (smoke_list),							// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SOUND_EFFECT",				// name
			sizeof (sound_effect),						// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_SPRITE",						// name
			sizeof (sprite),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_TASK",							// name
			sizeof (task),									// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_UPDATE",						// name
			sizeof (update),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_WAYPOINT",						// name
			sizeof (waypoint),							// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_TYPE_WEAPON",						// name
			sizeof (weapon),								// size_of_data
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_type_names (void)
{

	int
		loop;

	entity_type_names = (const char **) malloc_heap_mem (sizeof (const char *) * NUM_ENTITY_TYPES + 1);

	for (loop = 0; loop < NUM_ENTITY_TYPES; loop ++)
	{

		entity_type_names [loop] = get_entity_type_name (loop);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_entity_type_names (void)
{

	free_mem (entity_type_names);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_entity_type (entity_types type)
{
	ASSERT ((type >= 0) && (type < NUM_ENTITY_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (entity_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_ENTITY_TYPE, NULL, type);
	}

	#endif

	ASSERT(!(type >> NUM_ENTITY_TYPE_PACK_BITS));

	pack_unsigned_data (type, NUM_ENTITY_TYPE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_types unpack_entity_type (void)
{
	entity_types
		type;

	type = (entity_types) unpack_unsigned_data (NUM_ENTITY_TYPE_PACK_BITS);

	ASSERT ((type >= 0) && (type < NUM_ENTITY_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (entity_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_ENTITY_TYPE, NULL, type);
	}

	#endif

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
