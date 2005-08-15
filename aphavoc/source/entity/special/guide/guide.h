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

enum GUIDE_POSITION_TYPES
{

	GUIDE_POSITION_ABSOLUTE,
	GUIDE_POSITION_WAYPOINT,
	GUIDE_POSITION_RELATIVE_WORLD_SPACE,
	GUIDE_POSITION_RELATIVE_OBJECT_SPACE,
	GUIDE_POSITION_RELATIVE_CIRCULAR,

	NUM_GUIDE_POSITION_TYPES
};

typedef enum GUIDE_POSITION_TYPES guide_position_types;

extern const int
	guide_position_type_virtual [NUM_GUIDE_POSITION_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GUIDE_CRITERIA_TYPES
{

	GUIDE_CRITERIA_RADIUS,
	GUIDE_CRITERIA_HEADING,
	GUIDE_CRITERIA_ALTITUDE,	
	GUIDE_CRITERIA_TRANSMIT_DATA,	
	GUIDE_CRITERIA_LAST_TO_REACH,	
	GUIDE_CRITERIA_WEAPON_VECTOR,

	NUM_GUIDE_CRITERIA_TYPES
};

typedef enum GUIDE_CRITERIA_TYPES guide_criteria_types;

extern const char
	*guide_criteria_type_names [NUM_GUIDE_CRITERIA_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GUIDE_CRITERIA_ELEMENT
{
	int
		valid;

	float
		value;
};

typedef struct GUIDE_CRITERIA_ELEMENT guide_criteria_element;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_SEEK_COVER_COUNT_BITS 5

struct GUIDE_SEEK_COVER_RESULT_TYPE
{
	unsigned int
		search_mode			: 4,
		sector				: 1,
		count					: NUM_SEEK_COVER_COUNT_BITS,
		score					: 8;
};
	
typedef struct GUIDE_SEEK_COVER_RESULT_TYPE guide_seek_cover_result_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GUIDE
{
	entity_sub_types
		sub_type;

	list_root
		follower_root;

	list_link
		current_waypoint_link,
		guide_link,
		guide_stack_link,
		update_link;

	guide_position_types
		guide_position_type;

	vec3d
		position;

	entity
		*position_entity;

	unsigned int
		valid_guide_members;

	unsigned int
		check_waypoint_action				: 1;

	float
		velocity;

	guide_criteria_element
		criteria [NUM_GUIDE_CRITERIA_TYPES];

	//
	// Server only seek-cover data
	//
	// Not packed up - CLIENT does not need it - SERVER can simply start seeking again upon reload
	//

	guide_seek_cover_result_type
		current_seek_cover_result,
		best_seek_cover_result;

	terrain_3d_triangle
		*terrain_polygon_list;

	int
		terrain_polygon_count;
};

typedef struct GUIDE guide;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GUIDE_TERRAIN_FOLLOW_MODES
{
	GUIDE_TERRAIN_FOLLOW_NONE,
	GUIDE_TERRAIN_FOLLOW_CRUISE_ALTITUDE,
	GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE,

	NUM_GUIDE_TERRAIN_FOLLOW_MODES
};

typedef enum GUIDE_TERRAIN_FOLLOW_MODES guide_terrain_follow_modes;

#define NUM_GUIDE_TERRAIN_FOLLOW_BITS	2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"gd_attck.h"

#include	"gd_cover.h"

#include	"gd_creat.h"

#include	"gd_dbase.h"

#include	"gd_draw.h"

#include	"gd_dstry.h"

#include	"gd_float.h"

#include	"gd_funcs.h"

#include	"gd_int.h"

#include	"gd_list.h"

#include	"gd_msgs.h"

#include	"gd_nav.h"

#include	"gd_pack.h"

#include	"gd_ptr.h"

#include	"gd_updt.h"

#include	"gd_vec3d.h"

#include	"ag_attck.h"

#include	"aa_attck.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity *create_client_server_guide_entity (entity *task_en, entity *first_waypoint, unsigned int valid_members);

extern int validate_local_guide_entity (entity *en);

extern int check_guide_reached_waypoint (entity *en);

extern int check_guide_waypoint_action_reached (entity *en);

extern int set_guide_new_waypoint (entity *en, entity *wp);

extern int set_guide_next_waypoint (entity *en);

extern int set_guide_prev_waypoint (entity *en);

extern void get_local_guide_position (entity *en, vec3d *pos);

extern void attach_group_member_to_guide_entity (entity *member, entity *guide);

extern void attach_group_to_guide_entity (entity *group, entity *guide);

extern void delete_group_member_from_guide_entity (entity *member, entity *guide);

extern void delete_group_member_from_engage_guide (entity *member, entity *guide, int engage_enemy);

extern void set_client_server_guide_entity_new_position (entity *en, vec3d *position, entity *position_entity);

extern entity *get_local_group_primary_guide (entity *en);

extern entity *get_local_entity_primary_guide (entity *en);

extern void get_local_guide_entity_pointers (entity *en, entity **aggressor, entity **waypoint, entity **task, entity **objective);

extern int get_guide_required_heading (entity *en, entity *mobile, float *heading);

extern int get_guide_required_pitch (entity *en, entity *mobile, float *pitch);

extern int get_guide_criteria_valid (entity *en, guide_criteria_types type);

extern float get_guide_criteria_value (entity *en, guide_criteria_types type);

extern void set_client_server_guide_criteria_valid (entity *en, guide_criteria_types type, int valid, float value);

extern void set_local_guide_criteria_valid (entity *en, guide_criteria_types type, int valid, float value);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
