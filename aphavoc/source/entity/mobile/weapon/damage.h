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

#define WARHEAD_EFFECTIVE_NONE						0

//
// soft targets
//

#define WARHEAD_EFFECTIVE_SOFT_TARGETS				1

#define WARHEAD_EFFECTIVE_HELICOPTER				1
#define WARHEAD_EFFECTIVE_FIXED_WING				2

#define WARHEAD_EFFECTIVE_INFANTRY					4
#define WARHEAD_EFFECTIVE_LIGHT_VEHICLE			8
#define WARHEAD_EFFECTIVE_LIGHT_SHIP				16

#define WARHEAD_EFFECTIVE_WOOD_BRIDGE				32
#define WARHEAD_EFFECTIVE_STONE_BRIDGE				64

#define WARHEAD_EFFECTIVE_LIGHT_BUILDING			128
#define WARHEAD_EFFECTIVE_STONE_BUILDING			256

//
// hard targets
//

#define WARHEAD_EFFECTIVE_HARD_TARGETS				512

#define WARHEAD_EFFECTIVE_ARMOURED_VEHICLE		512

#define WARHEAD_EFFECTIVE_FRIGATE					1024
#define WARHEAD_EFFECTIVE_CARRIER					2048

#define WARHEAD_EFFECTIVE_METAL_BRIDGE				4096

#define WARHEAD_EFFECTIVE_HARDENED_BUILDING		8192

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int damage_client_server_entity (entity *en, entity *weapon, float damage_modifier);

extern void assess_effectiveness_of_all_weapons_on_entity (entity *en);

extern void display_debug_kill_info (entity *victim, entity *aggressor);

extern int weapon_is_capable_of_damage (entity_sub_types weapon_type);

extern int weapon_is_suitable_for_damaging_target (entity_sub_types weapon_type, entity *target, int direct_hit);

extern void initialise_destroyed_object_database (void);

extern void deinitialise_destroyed_object_database (void);

extern object_3d_index_numbers get_3d_object_destroyed_object_index (object_3d_index_numbers index);

extern object_3d_index_numbers get_3d_object_restored_object_index (object_3d_index_numbers index);

extern int get_damage_debug_invulnerable_flag (void);

extern int toggle_damage_debug_invulnerable_flag (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
