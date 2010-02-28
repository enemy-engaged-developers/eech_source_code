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

bridge_data
	bridge_database[NUM_ENTITY_SUB_TYPE_BRIDGES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_bridge_database()
{
	bridge_data
		*bridge_info;

	int
		loop;

	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_BOAT
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_BOAT];

	//

	bridge_info->valid_bridge_type							= TRUE;

	bridge_info->start_section_type							= BOAT_BRIDGE_START;
	bridge_info->end_section_type								= BOAT_BRIDGE_END;

	bridge_info->default_leg_height							= 5.0;

	bridge_info->min_suitable_span							= 0.0;
	bridge_info->max_suitable_span							= 300.0;

	bridge_info->min_suitable_depth							= 0.0;
	bridge_info->max_suitable_depth							= 12.0;

	bridge_info->max_suitable_slope							= rad (5);

	bridge_info->num_elements_in_mid_section_pattern	= 3;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	bridge_info->mid_section_type [0]						= BOAT_BRIDGE_DECK;
	bridge_info->mid_section_type [1]						= BOAT_BRIDGE_MID;
	bridge_info->mid_section_type [2]						= BOAT_BRIDGE_DECK;

	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_CAUSEWAY
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_CAUSEWAY];

	//

	bridge_info->valid_bridge_type							= FALSE;

	bridge_info->start_section_type							= CAUSEWAY_BRIDGE_END;
	bridge_info->end_section_type								= CAUSEWAY_BRIDGE_START;

	bridge_info->default_leg_height							= 500.0;

	bridge_info->min_suitable_span							= 250.0;
	bridge_info->max_suitable_span							= FLT_MAX;

	bridge_info->min_suitable_depth							= 0.0;
	bridge_info->max_suitable_depth							= 20.0;

	bridge_info->max_suitable_slope							= rad (2.0);

	bridge_info->num_elements_in_mid_section_pattern	= 9;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	bridge_info->mid_section_type [0]						= CAUSEWAY_BRIDGE_MID;
	bridge_info->mid_section_type [1]						= CAUSEWAY_BRIDGE_MID;
	bridge_info->mid_section_type [2]						= CAUSEWAY_BRIDGE_END;
	
	bridge_info->mid_section_type [3]						= STONE_BRIDGE_MID;
	bridge_info->mid_section_type [4]						= STONE_BRIDGE_MID;
	bridge_info->mid_section_type [5]						= STONE_BRIDGE_MID;

	bridge_info->mid_section_type [6]						= CAUSEWAY_BRIDGE_START;
	bridge_info->mid_section_type [7]						= CAUSEWAY_BRIDGE_MID;
	bridge_info->mid_section_type [8]						= CAUSEWAY_BRIDGE_MID;
	
	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_CONCRETE_ARCH
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_CONCRETE_ARCH];

	//

	bridge_info->valid_bridge_type							= TRUE;

	bridge_info->start_section_type							= CONCRETE_WIDE_BRIDGE_START;
	bridge_info->end_section_type								= CONCRETE_WIDE_BRIDGE_END;

	bridge_info->default_leg_height							= 500.0;

	bridge_info->min_suitable_span							= 250.0;
	bridge_info->max_suitable_span							= FLT_MAX;

	bridge_info->min_suitable_depth							= 0.0;
	bridge_info->max_suitable_depth							= FLT_MAX;

	bridge_info->max_suitable_slope							= rad (15);

	bridge_info->num_elements_in_mid_section_pattern	= 16;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	bridge_info->mid_section_type [0]						= CONCRETE_WIDE_BRIDGE_DECK;

	bridge_info->mid_section_type [1]						= CONCRETE_ARCH_BRIDGE_START;

	for ( loop = 2 ; loop <= 13 ; loop ++ )
	{
		bridge_info->mid_section_type [loop]				= CONCRETE_ARCH_BRIDGE_DECK;
	}

	bridge_info->mid_section_type [14]						= CONCRETE_ARCH_BRIDGE_END;

	bridge_info->mid_section_type [15]						= CONCRETE_WIDE_BRIDGE_DECK;

	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_CONCRETE_WIDE
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_CONCRETE_WIDE];

	//

	bridge_info->valid_bridge_type							= TRUE;

	bridge_info->start_section_type							= CONCRETE_WIDE_BRIDGE_START;
	bridge_info->end_section_type								= CONCRETE_WIDE_BRIDGE_END;

	bridge_info->min_suitable_span							= 0.0;
	bridge_info->max_suitable_span							= 300.0;

	bridge_info->min_suitable_depth							= 0.0;
	bridge_info->max_suitable_depth							= 20.0;

	bridge_info->max_suitable_slope							= rad (90);

	bridge_info->default_leg_height							= 500.0;

	bridge_info->num_elements_in_mid_section_pattern	= 1;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	bridge_info->mid_section_type [0]						= CONCRETE_WIDE_BRIDGE_DECK;

	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_DESERT
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_DESERT];

	//

	bridge_info->valid_bridge_type							= TRUE;

	bridge_info->start_section_type							= DESERT_BRIDGE_START;
	bridge_info->end_section_type								= DESERT_BRIDGE_END;

	bridge_info->default_leg_height							= 500.0;

	bridge_info->min_suitable_span							= 0.0;
	bridge_info->max_suitable_span							= 500.0;

	bridge_info->min_suitable_depth							= 10.0;
	bridge_info->max_suitable_depth							= 30.0;

	bridge_info->max_suitable_slope							= rad (20);

	bridge_info->num_elements_in_mid_section_pattern	= 1;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	bridge_info->mid_section_type [0]						= DESERT_BRIDGE_MID;

	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_GIRDER
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_GIRDER];

	//

	bridge_info->valid_bridge_type							= TRUE;

	bridge_info->start_section_type							= GIRDER_BRIDGE_START;
	bridge_info->end_section_type								= GIRDER_BRIDGE_END;

	bridge_info->default_leg_height							= 500.0;

	bridge_info->min_suitable_span							= 250.0;
	bridge_info->max_suitable_span							= FLT_MAX;

	bridge_info->min_suitable_depth							= 0.0;
	bridge_info->max_suitable_depth							= FLT_MAX;

	bridge_info->max_suitable_slope							= rad (90);

	bridge_info->num_elements_in_mid_section_pattern	= 3;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	bridge_info->mid_section_type [0]								= GIRDER_BRIDGE_DECK;
	bridge_info->mid_section_type [1]								= GIRDER_BRIDGE_MID;
	bridge_info->mid_section_type [2]								= GIRDER_BRIDGE_DECK;

	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_STONE
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_STONE];

	//

	bridge_info->valid_bridge_type							= TRUE;

	bridge_info->start_section_type							= STONE_BRIDGE_START;
	bridge_info->end_section_type								= STONE_BRIDGE_END;

	bridge_info->default_leg_height							= 500.0;

	bridge_info->min_suitable_span							= 0.0;
	bridge_info->max_suitable_span							= 500.0;

	bridge_info->min_suitable_depth							= 10.0;
	bridge_info->max_suitable_depth							= 30.0;

	bridge_info->max_suitable_slope							= rad (20);

	bridge_info->num_elements_in_mid_section_pattern	= 1;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	bridge_info->mid_section_type [0]						= STONE_BRIDGE_MID;

	////////////////////////////////////////
	//
	// ENTITY_SUB_TYPE_BRIDGE_SUSPENSION
	//
	////////////////////////////////////////

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_SUSPENSION];

	//

	bridge_info->valid_bridge_type							= TRUE;

	bridge_info->start_section_type							= SUSPENSION_BRIDGE_START;
	bridge_info->end_section_type								= SUSPENSION_BRIDGE_END;

	bridge_info->default_leg_height							= 500.0;

	bridge_info->min_suitable_span							= 200.0;
	bridge_info->max_suitable_span							= FLT_MAX;

	bridge_info->min_suitable_depth							= 10.0;
	bridge_info->max_suitable_depth							= FLT_MAX;

	bridge_info->max_suitable_slope							= rad (10);

	bridge_info->num_elements_in_mid_section_pattern	= 20;

	bridge_info->mid_section_type = (bridge_segment_types *) malloc_fast_mem (sizeof (int) * bridge_info->num_elements_in_mid_section_pattern);

	//

	for ( loop = 0 ; loop <= 9 ; loop ++ )
	{
		bridge_info->mid_section_type [loop]						= SUSPENSION_BRIDGE_DECK;
	}

	bridge_info->mid_section_type [10]								= SUSPENSION_BRIDGE_MID;

	for ( loop = 11 ; loop <= 19 ; loop ++ )
	{
		bridge_info->mid_section_type [loop]						= SUSPENSION_BRIDGE_DECK;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_bridge_database()
{
	bridge_data
		*bridge_info;

	//

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_BOAT];

	free_mem (bridge_info->mid_section_type);

	//

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_CAUSEWAY];

	free_mem (bridge_info->mid_section_type);

	//

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_CONCRETE_ARCH];

	free_mem (bridge_info->mid_section_type);

	//
	
	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_CONCRETE_WIDE];

	free_mem (bridge_info->mid_section_type);

	//
	
	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_GIRDER];

	free_mem (bridge_info->mid_section_type);

	//

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_STONE];

	free_mem (bridge_info->mid_section_type);

	//

	bridge_info = &bridge_database [ENTITY_SUB_TYPE_BRIDGE_SUSPENSION];

	free_mem (bridge_info->mid_section_type);

	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
