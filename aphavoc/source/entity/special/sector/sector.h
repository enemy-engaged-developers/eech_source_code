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

struct SECTOR
{
	list_root
		sector_root,
		sector_task_root,
		special_effect_root;

	unsigned int
		keysite_count	: 8,
		x_sector			: NUM_SECTOR_BITS,
		z_sector			: NUM_SECTOR_BITS,
		side				: NUM_SIDE_BITS;

	float
		tallest_structure_height,
		sector_side [NUM_ENTITY_SIDES],
		fog_of_war [NUM_ENTITY_SIDES],
		importance_level [NUM_ENTITY_SIDES],
		distance_to_friendly_base [NUM_ENTITY_SIDES],
		surface_to_air_defence_level [NUM_ENTITY_SIDES],
		surface_to_surface_defence_level [NUM_ENTITY_SIDES];
};

typedef struct SECTOR sector;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity
	**entity_sector_map;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG

#define get_local_raw_sector_entity(X_SEC,Z_SEC) ((entity_sector_map [(X_SEC) + ((Z_SEC) * (NUM_MAP_X_SECTORS))]) ? (entity_sector_map[(X_SEC) + ((Z_SEC) * (NUM_MAP_X_SECTORS))]) : (process_assert (null_sector_entity_map_pointer_message, __FILE__, __LINE__), NULL))

#else

#define get_local_raw_sector_entity(X_SEC,Z_SEC) (entity_sector_map [(X_SEC) + ((Z_SEC) * (NUM_MAP_X_SECTORS))])

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern char
	*null_sector_entity_map_pointer_message;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity *get_local_sector_entity (vec3d *pos);

extern float get_local_sector_entity_enemy_surface_to_air_defence_level (entity *sector_en, entity_sides side);

extern float get_local_sector_entity_enemy_surface_to_surface_defence_level (entity *sector_en, entity_sides side);

extern float get_sector_importance_level (int sx, int sz, entity_sides side);

extern float get_sector_distance_to_friendly_base (int sx, int sz, entity_sides side);

extern void add_mobile_values_to_sector (entity *sector_en, entity *mobile_en);

extern void remove_mobile_values_from_sector (entity *sector_en, entity *mobile_en);

extern float get_local_sector_side_ratio (int sx, int sz, entity_sides side);

extern void set_sector_fog_of_war_value (entity *en, entity *sector_en);

extern float get_sector_fog_of_war_value (entity *en, entity_sides side);

extern void update_sector_fog_of_war (void);

extern void update_client_server_sector_fog_of_war (void);

extern void update_sector_side_count (void);

extern void update_client_server_sector_side_count (void);

extern void validate_local_sector_entities (void);

extern int get_sector_task_type_count (entity *en, entity_sub_types task_type, entity_sides side);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// JB 030311 VC rename source files
#include "sc_seccreat.h"

#include "sc_dstry.h"

#include "sc_float.h"

// JB 030311 VC rename source files
#include "sc_secfuncs.h"

#include "sc_int.h"

#include "sc_list.h"

#include "sc_msgs.h"

#include "sc_pack.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
