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

typedef enum
{
	BRIDGE_SEGMENT_TYPE_NONE,

	BOAT_BRIDGE_START,
	BOAT_BRIDGE_END,
	BOAT_BRIDGE_MID,
	BOAT_BRIDGE_DECK,

	CAUSEWAY_BRIDGE_START,
	CAUSEWAY_BRIDGE_END,
	CAUSEWAY_BRIDGE_MID,

	CONCRETE_ARCH_BRIDGE_START,
	CONCRETE_ARCH_BRIDGE_END,
	CONCRETE_ARCH_BRIDGE_DECK,

	CONCRETE_WIDE_BRIDGE_START,
	CONCRETE_WIDE_BRIDGE_END,
	CONCRETE_WIDE_BRIDGE_DECK,

	DESERT_BRIDGE_START,
	DESERT_BRIDGE_END,
	DESERT_BRIDGE_MID,

	GIRDER_BRIDGE_START,
	GIRDER_BRIDGE_END,
	GIRDER_BRIDGE_MID,
	GIRDER_BRIDGE_DECK,

	STONE_BRIDGE_START,
	STONE_BRIDGE_END,
	STONE_BRIDGE_MID,

	SUSPENSION_BRIDGE_START,
	SUSPENSION_BRIDGE_END,
	SUSPENSION_BRIDGE_MID,
	SUSPENSION_BRIDGE_DECK,

	NUM_BRIDGE_SEGMENT_TYPES

} bridge_segment_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BRIDGE_SEGMENT_DATA
{

	object_3d_index_numbers
		normal_object,
		destroyed_object,
		pred_destroyed_object,
		succ_destroyed_object,
		both_destroyed_object;

	entity_sub_types
		sub_type;

	float
		length;

	int
		initial_damage_level,
		target_type,
		warhead_effective_class;
};

typedef struct BRIDGE_SEGMENT_DATA bridge_segment_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern bridge_segment_data
	segment_database[NUM_BRIDGE_SEGMENT_TYPES];

#define bridge_segment_normal_object(a) segment_database[(a)].normal_object

#define bridge_segment_length(a) segment_database[(a)].length

#define bridge_segment_sub_type(a) segment_database[(a)].sub_type

#define bridge_segment_initial_damage_level(a) segment_database[(a)].initial_damage_level

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_segment_database();

extern void deinitialise_segment_database();

extern object_3d_index_numbers get_bridge_segment_damaged_object (entity *en, entity *pred, entity *succ);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
