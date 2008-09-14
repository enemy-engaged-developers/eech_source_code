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

#include "routegen.h"

#include "popread.h"

#include "briefing.h"

#include "ai/ai_misc/ai_misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum FRONTLINE_FORCE_PLACEMENT_TYPES
{

	FRONTLINE_FORCE_NONE,
	FRONTLINE_FORCE_PRIMARY,
	FRONTLINE_FORCE_SECONDARY,
	FRONTLINE_FORCE_ARTILLERY,
	NUM_FRONTLINE_FORCE_TYPES
};

typedef enum FRONTLINE_FORCE_PLACEMENT_TYPES frontline_force_placement_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FRONTLINE_FORCES_PLACEMENT_DATA
{

	unsigned int
		side						: NUM_SIDE_BITS,
		route_node				: NUM_ROUTE_NODE_BITS,
		force_placement_type	: NUM_FRONTLINE_FORCE_TYPES;
};

typedef struct FRONTLINE_FORCES_PLACEMENT_DATA frontline_forces_placement_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* forward declarations for types used below */
struct SESSION_LIST_DATA_TYPE;
/*********************************************/

extern void create_faction (entity_sides side, int colour);

extern void create_campaign (struct SESSION_LIST_DATA_TYPE *session);

extern void clear_factions (void);

extern void destroy_campaign (void);

extern entity *create_faction_members (entity *keysite, entity_sub_types group_type, formation_component_types formation, int number, entity_sides side, vec3d *position, int client_server_create, int place_at_ground_height);

extern entity *create_landed_faction_members (entity *this_keysite, entity_sub_types member_type, entity_sub_types group_type, int number);

extern entity *create_landed_faction_group (entity *keysite, entity_sub_types group_type, formation_component_types formation_component);

extern entity *create_landing_faction_members (entity *keysite, entity_sub_types member_type, entity_sub_types group_type, int number, entity *cwp, vec3d *start_position);

extern void place_frontline_forces (entity *force, int force_size);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
