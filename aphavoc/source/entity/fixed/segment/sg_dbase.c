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

bridge_segment_data
	segment_database[NUM_BRIDGE_SEGMENT_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_segment_database()
{
	bridge_segment_data
		*segment_info = nullptr;

	////////////////////////////////////////
	//
	// BRIDGE_SEGMENT_TYPE_NONE
	//
	////////////////////////////////////////

	segment_info = &segment_database [BRIDGE_SEGMENT_TYPE_NONE];

	//

	segment_info->normal_object					= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->destroyed_object				= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->pred_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->succ_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->both_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 0.0;

	segment_info->initial_damage_level			= 0;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 1;

	////////////////////////////////////////
	//
	// BOAT_BRIDGE_START 
	//
	////////////////////////////////////////

	segment_info = &segment_database [BOAT_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_BOAT_BRIDGE_START;
	segment_info->destroyed_object				= OBJECT_3D_BOAT_BRIDGE_START_DAMAGE2;
	segment_info->pred_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_START;
	segment_info->succ_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_START_DAMAGE_1;
	segment_info->both_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_START_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 20.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 1;

	////////////////////////////////////////
	//
	// BOAT_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [BOAT_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_BOAT_BRIDGE_END;
	segment_info->destroyed_object				= OBJECT_3D_BOAT_BRIDGE_END_DAMAGE_2;
	segment_info->pred_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_END_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_END;
	segment_info->both_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_END_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 20.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 1;

	////////////////////////////////////////
	//
	// BOAT_BRIDGE_MID
	//
	////////////////////////////////////////

	segment_info = &segment_database [BOAT_BRIDGE_MID];

	//

	segment_info->normal_object					= OBJECT_3D_BOAT_BRIDGE_MID;
	segment_info->destroyed_object				= OBJECT_3D_BOAT_BRIDGE_MID_DAMAGE_3;
	segment_info->pred_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_MID_DAMAGE_2;
	segment_info->succ_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_MID_DAMAGE_1;
	segment_info->both_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_MID_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 20.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 1;

	////////////////////////////////////////
	//
	// BOAT_BRIDGE_DECK
	//
	////////////////////////////////////////

	segment_info = &segment_database [BOAT_BRIDGE_DECK];

	//

	segment_info->normal_object					= OBJECT_3D_BOAT_BRIDGE_DECK;
	segment_info->destroyed_object				= OBJECT_3D_BOAT_BRIDGE_DECK_DAMAGE;
	segment_info->pred_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_DECK_DAMAGE;
	segment_info->succ_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_DECK_DAMAGE;
	segment_info->both_destroyed_object			= OBJECT_3D_BOAT_BRIDGE_DECK_DAMAGE;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_UNSUPPORTED_MID_SECTION;

	segment_info->length								= 20.0;

	segment_info->initial_damage_level			= 400;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 1;

	////////////////////////////////////////
	//
	// CAUSEWAY_BRIDGE_START
	//
	////////////////////////////////////////

	segment_info = &segment_database [CAUSEWAY_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->destroyed_object				= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->pred_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->succ_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->both_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 0.0;

	segment_info->initial_damage_level			= 0;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CAUSEWAY_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [CAUSEWAY_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->destroyed_object				= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->pred_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->succ_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->both_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 0.0;

	segment_info->initial_damage_level			= 0;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CAUSEWAY_BRIDGE_MID
	//
	////////////////////////////////////////

	segment_info = &segment_database [CAUSEWAY_BRIDGE_MID];

	//

	segment_info->normal_object					= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->destroyed_object				= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->pred_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->succ_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;
	segment_info->both_destroyed_object			= OBJECT_3D_INVALID_OBJECT_INDEX;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 0.0;

	segment_info->initial_damage_level			= 0;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CONCRETE_ARCH_BRIDGE_START
	//
	////////////////////////////////////////

	segment_info = &segment_database [CONCRETE_ARCH_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_CONCRETE_ARCH_BRIDGE_START;
	segment_info->destroyed_object				= OBJECT_3D_CONCRETE_ARCH_BRIDGE_START_DAMAGE_1;
	segment_info->pred_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_START;
	segment_info->succ_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_START_DAMAGE_1;
	segment_info->both_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_START_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CONCRETE_ARCH_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [CONCRETE_ARCH_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_CONCRETE_ARCH_BRIDGE_END;
	segment_info->destroyed_object				= OBJECT_3D_CONCRETE_ARCH_BRIDGE_END_DAMAGE_1;
	segment_info->pred_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_END_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_END;
	segment_info->both_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_END_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CONCRETE_ARCH_BRIDGE_DECK
	//
	////////////////////////////////////////

	segment_info = &segment_database [CONCRETE_ARCH_BRIDGE_DECK];

	//

	segment_info->normal_object					= OBJECT_3D_CONCRETE_ARCH_BRIDGE_DECK;
	segment_info->destroyed_object				= OBJECT_3D_CONCRETE_ARCH_BRIDGE_DECK_DAMAGE_3;
	segment_info->pred_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_DECK_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_DECK_DAMAGE_2;
	segment_info->both_destroyed_object			= OBJECT_3D_CONCRETE_ARCH_BRIDGE_DECK_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_UNSUPPORTED_MID_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CONCRETE_WIDE_BRIDGE_START
	//
	////////////////////////////////////////

	segment_info = &segment_database [CONCRETE_WIDE_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_CONCRETE_WIDE_BRIDGE_START;
	segment_info->destroyed_object				= OBJECT_3D_CONCRETE_WIDE_BRIDGE_START_DAMAGE_1;
	segment_info->pred_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_START;
	segment_info->succ_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_START_DAMAGE_1;
	segment_info->both_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_START_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 30.0;

	segment_info->initial_damage_level			= 800;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CONCRETE_WIDE_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [CONCRETE_WIDE_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_CONCRETE_WIDE_BRIDGE_END;
	segment_info->destroyed_object				= OBJECT_3D_CONCRETE_WIDE_BRIDGE_END_DAMAGE_1;
	segment_info->pred_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_END_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_END;
	segment_info->both_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_END_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 30.0;

	segment_info->initial_damage_level			= 800;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// CONCRETE_WIDE_BRIDGE_DECK
	//
	////////////////////////////////////////

	segment_info = &segment_database [CONCRETE_WIDE_BRIDGE_DECK];

	//

	segment_info->normal_object					= OBJECT_3D_CONCRETE_WIDE_BRIDGE_DECK;
	segment_info->destroyed_object				= OBJECT_3D_CONCRETE_WIDE_BRIDGE_DECK_DAMAGE_4;
	segment_info->pred_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_DECK_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_DECK_DAMAGE_2;
	segment_info->both_destroyed_object			= OBJECT_3D_CONCRETE_WIDE_BRIDGE_DECK_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 30.0;

	segment_info->initial_damage_level			= 800;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// DESERT_BRIDGE_START
	//
	////////////////////////////////////////

	segment_info = &segment_database [DESERT_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_YEMEN_BRIDGE_START;
	segment_info->destroyed_object				= OBJECT_3D_YEMEN_BRIDGE_START;
	segment_info->pred_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_START;
	segment_info->succ_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_START;
	segment_info->both_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_START;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 200;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// DESERT_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [DESERT_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_YEMEN_BRIDGE_END;
	segment_info->destroyed_object				= OBJECT_3D_YEMEN_BRIDGE_END;
	segment_info->pred_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_END;
	segment_info->succ_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_END;
	segment_info->both_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_END;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 200;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// DESERT_BRIDGE_MID
	//
	////////////////////////////////////////

	segment_info = &segment_database [DESERT_BRIDGE_MID];

	//

	segment_info->normal_object					= OBJECT_3D_YEMEN_BRIDGE_MID;
	segment_info->destroyed_object				= OBJECT_3D_YEMEN_BRIDGE_MID_DAMAGE_4;
	segment_info->pred_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_MID_DAMAGE_2;
	segment_info->succ_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_MID_DAMAGE_3;
	segment_info->both_destroyed_object			= OBJECT_3D_YEMEN_BRIDGE_MID_DAMAGE_4;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 200;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// GIRDER_BRIDGE_START
	//
	////////////////////////////////////////

	segment_info = &segment_database [GIRDER_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_GIRDER_BRIDGE_START;
	segment_info->destroyed_object				= OBJECT_3D_GIRDER_BRIDGE_START_DAMAGE_1;
	segment_info->pred_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_START;
	segment_info->succ_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_START_DAMAGE_1;
	segment_info->both_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_START_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 10;

	////////////////////////////////////////
	//
	// GIRDER_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [GIRDER_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_GIRDER_BRIDGE_END;
	segment_info->destroyed_object				= OBJECT_3D_GIRDER_BRIDGE_END_DAMAGE_1;
	segment_info->pred_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_END_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_END;
	segment_info->both_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_END_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 10;

	////////////////////////////////////////
	//
	// GIRDER_BRIDGE_MID
	//
	////////////////////////////////////////

	segment_info = &segment_database [GIRDER_BRIDGE_MID];

	//

	segment_info->normal_object					= OBJECT_3D_GIRDER_BRIDGE_MID;
	segment_info->destroyed_object				= OBJECT_3D_GIRDER_BRIDGE_MID_DAMAGE_3;
	segment_info->pred_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_MID_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_MID_DAMAGE_2;
	segment_info->both_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_MID_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 20.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 10;

	////////////////////////////////////////
	//
	// GIRDER_BRIDGE_DECK
	//
	////////////////////////////////////////

	segment_info = &segment_database [GIRDER_BRIDGE_DECK];

	//

	segment_info->normal_object					= OBJECT_3D_GIRDER_BRIDGE_DECK;
	segment_info->destroyed_object				= OBJECT_3D_GIRDER_BRIDGE_DECK_DAMAGE_1;
	segment_info->pred_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_DECK_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_DECK_DAMAGE_1;
	segment_info->both_destroyed_object			= OBJECT_3D_GIRDER_BRIDGE_DECK_DAMAGE_1;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_UNSUPPORTED_MID_SECTION;

	segment_info->length								= 50.0;

	segment_info->initial_damage_level			= 500;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 10;

	////////////////////////////////////////
	//
	// STONE_BRIDGE_START
	//
	////////////////////////////////////////

	segment_info = &segment_database [STONE_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_STONE_BRIDGE_START;
	segment_info->destroyed_object				= OBJECT_3D_STONE_BRIDGE_START;
	segment_info->pred_destroyed_object			= OBJECT_3D_STONE_BRIDGE_START;
	segment_info->succ_destroyed_object			= OBJECT_3D_STONE_BRIDGE_START;
	segment_info->both_destroyed_object			= OBJECT_3D_STONE_BRIDGE_START;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 200;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// STONE_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [STONE_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_STONE_BRIDGE_END;
	segment_info->destroyed_object				= OBJECT_3D_STONE_BRIDGE_END;
	segment_info->pred_destroyed_object			= OBJECT_3D_STONE_BRIDGE_END;
	segment_info->succ_destroyed_object			= OBJECT_3D_STONE_BRIDGE_END;
	segment_info->both_destroyed_object			= OBJECT_3D_STONE_BRIDGE_END;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 200;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// STONE_BRIDGE_MID
	//
	////////////////////////////////////////

	segment_info = &segment_database [STONE_BRIDGE_MID];

	//

	segment_info->normal_object					= OBJECT_3D_STONE_BRIDGE_MID;
	segment_info->destroyed_object				= OBJECT_3D_STONE_BRIDGE_MID_DAMAGE_4;
	segment_info->pred_destroyed_object			= OBJECT_3D_STONE_BRIDGE_MID_DAMAGE_2;
	segment_info->succ_destroyed_object			= OBJECT_3D_STONE_BRIDGE_MID_DAMAGE_3;
	segment_info->both_destroyed_object			= OBJECT_3D_STONE_BRIDGE_MID_DAMAGE_4;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 200;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// SUSPENSION_BRIDGE_START
	//
	////////////////////////////////////////

	segment_info = &segment_database [SUSPENSION_BRIDGE_START];

	//

	segment_info->normal_object					= OBJECT_3D_SUSPENSION_BRIDGE_START;
	segment_info->destroyed_object				= OBJECT_3D_SUSPENSION_BRIDGE_START_DAMAGE_3;
	segment_info->pred_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_START_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_START_DAMAGE_2;
	segment_info->both_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_START_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 750;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// SUSPENSION_BRIDGE_END
	//
	////////////////////////////////////////

	segment_info = &segment_database [SUSPENSION_BRIDGE_END];

	//

	segment_info->normal_object					= OBJECT_3D_SUSPENSION_BRIDGE_END;
	segment_info->destroyed_object				= OBJECT_3D_SUSPENSION_BRIDGE_END_DAMAGE_3;
	segment_info->pred_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_END_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_END_DAMAGE_2;
	segment_info->both_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_END_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 750;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// SUSPENSION_BRIDGE_MID
	//
	////////////////////////////////////////

	segment_info = &segment_database [SUSPENSION_BRIDGE_MID];

	//

	segment_info->normal_object					= OBJECT_3D_SUSPENSION_BRIDGE_MID;
	segment_info->destroyed_object				= OBJECT_3D_SUSPENSION_BRIDGE_MID_DAMAGE_3;
	segment_info->pred_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_MID_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_MID_DAMAGE_2;
	segment_info->both_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_MID_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 800;
	segment_info->target_type						= TARGET_TYPE_GROUND;
	segment_info->armor_level		= 5;

	////////////////////////////////////////
	//
	// SUSPENSION_BRIDGE_DECK
	//
	////////////////////////////////////////

	segment_info = &segment_database [SUSPENSION_BRIDGE_DECK];

	//

	segment_info->normal_object					= OBJECT_3D_SUSPENSION_BRIDGE_DECK;
	segment_info->destroyed_object				= OBJECT_3D_SUSPENSION_BRIDGE_DECK_DAMAGE_3;
	segment_info->pred_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_DECK_DAMAGE_1;
	segment_info->succ_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_DECK_DAMAGE_2;
	segment_info->both_destroyed_object			= OBJECT_3D_SUSPENSION_BRIDGE_DECK_DAMAGE_3;

	segment_info->sub_type							= ENTITY_SUB_TYPE_FIXED_BRIDGE_UNSUPPORTED_MID_SECTION;

	segment_info->length								= 10.0;

	segment_info->initial_damage_level			= 100;
	segment_info->target_type						= TARGET_TYPE_INVALID;
	segment_info->armor_level		= 5;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_segment_database()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_index_numbers get_bridge_segment_damaged_object (entity *en, entity *pred, entity *succ)
{

	bridge_segment_types
		bridge_segment_type;

	object_3d_index_numbers
		damaged_object;

	int
		alive,
		pred_alive,
		succ_alive;

	bridge_segment_type = (bridge_segment_types) get_local_entity_int_value (en, INT_TYPE_BRIDGE_SEGMENT_TYPE);

	alive = get_local_entity_int_value (en, INT_TYPE_ALIVE);

	pred_alive = ((pred == NULL) || (get_local_entity_int_value (pred, INT_TYPE_ALIVE)));

	succ_alive = ((succ == NULL) || (get_local_entity_int_value (succ, INT_TYPE_ALIVE)));

	//
	// select correct object shape dependant on the state of it's neighbours
	//

	if (!alive)
	{
		damaged_object = segment_database[ bridge_segment_type ].destroyed_object;
	}
	else if ((!pred_alive) && (succ_alive))
	{
		damaged_object = segment_database[ bridge_segment_type ].pred_destroyed_object;
	}
	else if ((pred_alive) && (!succ_alive))
	{
		damaged_object = segment_database[ bridge_segment_type ].succ_destroyed_object;
	}
	else if ((!pred_alive) && (!succ_alive))
	{
		damaged_object = segment_database[ bridge_segment_type ].both_destroyed_object;
	}
	else
	{
		damaged_object = segment_database[ bridge_segment_type ].normal_object;
	}

	return damaged_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
