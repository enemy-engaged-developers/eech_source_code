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

struct WAYPOINT
{
	entity_sub_types
		sub_type;

	list_root
		current_waypoint_root;

	list_link
		task_dependent_link,
		waypoint_link;

	float
		flight_time,
		altitude,
		heading;

	unsigned int
		waypoint_action_notified				: NUM_WAYPOINT_REACHED_BITS,
		position_type								: NUM_POSITION_TYPE_BITS,
		route_node									: NUM_ROUTE_NODE_BITS,
		tag											: NUM_TAG_BITS,
		waypoint_formation						: NUM_WAYPOINT_FORMATION_BITS;

	vec3d
		position;

	entity
		*position_entity;
};

typedef struct WAYPOINT waypoint;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"wp_char.h"

#include	"wp_creat.h"

#include	"wp_dbase.h"

#include	"wp_draw.h"

#include	"wp_dstry.h"

#include	"wp_float.h"

#include	"wp_funcs.h"

#include	"wp_int.h"

#include	"wp_list.h"

#include	"wp_msgs.h"

#include	"wp_pack.h"

#include	"wp_ptr.h"

#include	"wp_str.h"

#include	"wp_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity *get_local_entity_first_waypoint (entity *en);

extern entity *get_local_entity_current_waypoint (entity *en);

extern entity *get_local_entity_last_waypoint (entity *en);

extern entity *get_local_entity_next_waypoint (entity *en);

extern entity *get_local_entity_prev_waypoint (entity *en);

extern void get_local_waypoint_formation_position_offset (int formation_position, entity *wp, vec3d *offset);

extern void get_local_entity_formation_position_offset (entity *en, entity *wp, vec3d *offset);

extern void get_local_waypoint_formation_position (int formation_position, entity *wp, vec3d *pos);

extern void get_local_entity_formation_position (entity *en, entity *wp, vec3d *pos);

extern void get_local_waypoint_simple_formation_position (int formation_position, vec3d *origin, int type, vec3d *pos);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
