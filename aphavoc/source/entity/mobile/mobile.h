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

#define DEBUG_TERRAIN_CHECK 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MOBILE
{
	entity_sub_types
		sub_type;

	vec3d
		position;

	union
	{
		matrix3x3
			attitude;

		struct
		{
			vec3d
				xv,
				yv,
				zv;
		};
	};

	vec3d
		motion_vector;

	float
		velocity;

	list_root
		special_effect_root,
		target_root;

	list_link
		padlock_link,
		sector_link,
		target_link,
		update_link;

	unsigned int
		alive			  		 	 			: NUM_ALIVE_BITS,
		side		 	  		 	  			: NUM_SIDE_BITS,
		kill_next_update	 	  			: NUM_KILL_NEXT_UPDATE_BITS,
		tacview_logging : 1,
		object_drawn_once_this_frame	: NUM_OBJECT_DRAWN_ONCE_THIS_FRAME_BITS;
};

typedef struct MOBILE mobile;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"mb_att.h"

#include	"mb_float.h"

#include	"mb_funcs.h"

#include	"mb_int.h"

#include	"mb_list.h"

#include	"mb_move.h"

#include	"mb_msgs.h"

#include	"mb_pack.h"

#include	"mb_tgt.h"

#include	"mb_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// INCLUDE ORDER IS CRITICAL
//

#include "weapon/weapon.h"

#include "aircraft/aircraft.h"

#include "cargo/cargo.h"

#include "vehicle/vehicle.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float mobile_terrain_adjust_waypoint_height (entity *en, vec3d *wp_pos, float min_height);

extern void draw_mobile_entity_debug_info (entity *en);

extern void update_mobile_sprite_light_timers (void);

extern void credit_client_server_mobile_kill (entity *victim, entity *aggressor);

extern float calculate_mobile_death_timer_value (entity *en);

extern int insert_mobile_into_takeoff_route (entity *member, entity *landing_entity);

extern int mobile_check_all_members_taken_off (entity *en);

extern void play_mobile_under_attack_speech (entity *en, entity *aggressor);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




