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

#define LANDING_ROUTE_CHECK (1 && DEBUG)

#define LANDING_LOCK_USER_ONLY 0

#define LANDING_KEYSITE_DEBUG_OUTPUT 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LANDING
{

	entity_sub_types
		sub_type;

	vec3d
		position;

	list_root
		task_dependent_root,
		assigned_task_root,
		takeoff_queue_root;

	list_link
		#if LANDING_ROUTE_CHECK

		update_link,

		#endif
		landing_site_link;

	int
		route_node;

	unsigned int
		reserved_landing_sites,
		free_landing_sites,
		total_landing_sites;

	unsigned int
		inside_hangar	: NUM_INSIDE_HANGAR_BITS,
		landing_lock	: NUM_FORMATION_BITS,
		landed_lock		: NUM_FORMATION_BITS,
		takeoff_lock	: NUM_FORMATION_BITS;
};

typedef struct LANDING landing;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ld_creat.h"

#include "ld_dstry.h"

#include "ld_float.h"

#include "ld_funcs.h"

#include "ld_int.h"

#include "ld_list.h"

#include "ld_msgs.h"

#include "ld_pack.h"

#include "ld_str.h"

#include "ld_updt.h"

#include "ld_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity *get_local_entity_landing_entity (entity *en, entity_sub_types landing_type);

extern entity *get_local_landing_entity_route (entity *landing_en, entity_sub_types type);

extern entity *get_local_landing_entity_task (entity *landing_en, entity_sub_types type);

extern entity *get_local_group_member_landing_entity_from_keysite (entity *en);

extern entity *get_local_group_member_landing_entity_from_task (entity *en);

extern void validate_landing_entity_routes (entity *en);

extern int check_available_landing_route_lock (entity *landing_en);

extern int check_landing_route_lock_clear (entity *landing_en, entity *en);

extern int check_takeoff_route_lock_clear (entity *landing_en, entity *en);

extern int check_landing_site_lock_clear (entity *landing_en, entity *en);

extern void release_mobile_entity_landing_locks (entity *en);

extern void play_landing_clear_for_takeoff_speech (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
