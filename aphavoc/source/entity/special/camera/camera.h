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

enum CAMERA_MODES
{
	CAMERA_MODE_CHASE,
	CAMERA_MODE_END_OF_MISSION,
	CAMERA_MODE_DROP,
	CAMERA_MODE_STATIC,
	CAMERA_MODE_SATELLITE, // Jabberwock 031009 Satellite view
	CAMERA_MODE_EJECT,
	CAMERA_MODE_FLY_BY,
	CAMERA_MODE_CINEMATIC,
	CAMERA_MODE_BUILDING,
	CAMERA_MODE_WEAPON,
	CAMERA_MODE_WEAPON_EXPLOSION,
	CAMERA_MODE_DEBRIEFING,
	CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW,
	CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW,
	CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW,
	CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW,
	CAMERA_MODE_FREE,
	NUM_CAMERA_MODES
};

typedef enum CAMERA_MODES camera_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CAMERA_ACTIONS
{
	CAMERA_ACTION_CHASE,
	CAMERA_ACTION_RESET_CHASE_POSITION,
	CAMERA_ACTION_TOGGLE_CHASE_LOCK_ROTATE,
	CAMERA_ACTION_END_OF_MISSION,
	CAMERA_ACTION_DROP,
	CAMERA_ACTION_STATIC,
	CAMERA_ACTION_SATELLITE, // Jabberwock 031009 Satellite view
	CAMERA_ACTION_EJECT,
	CAMERA_ACTION_FLY_BY,
	CAMERA_ACTION_CINEMATIC,
	CAMERA_ACTION_BUILDING,
	CAMERA_ACTION_WEAPON,
	CAMERA_ACTION_WEAPON_EXPLOSION,
	CAMERA_ACTION_AUTO_EDIT,
	CAMERA_ACTION_DEBRIEFING,
	CAMERA_ACTION_RECOGNITION_GUIDE_TOP_VIEW,
	CAMERA_ACTION_RECOGNITION_GUIDE_SIDE_VIEW,
	CAMERA_ACTION_RECOGNITION_GUIDE_FRONT_VIEW,
	CAMERA_ACTION_RECOGNITION_GUIDE_3D_VIEW,
	CAMERA_ACTION_FREE,
	NUM_CAMERA_ACTIONS
};

typedef enum CAMERA_ACTIONS camera_actions;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CAMERA
{
	////////////////////////////////////////
	//
	// camera data
	//
	////////////////////////////////////////

	vec3d
		position,
		motion_vector;		// required for 3D rain effect

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

	camera_modes
		camera_mode;

	list_link
		update_link;

	int
		auto_edit;
	
	terrain_3d_point_data
		terrain_info;

	//
	// chase camera
	//

	int
		chase_camera_lock_rotate;

	float
		chase_camera_heading,
		chase_camera_pitch,
		chase_camera_zoom;

	//
	// end of mission camera
	//

	float
		end_of_mission_camera_heading;

	//
	// fly-by camera
	//

	float
		fly_by_camera_timer;

	//
	// cinematic camera
	//

	float
		cinematic_camera_lifetime,
		cinematic_camera_timer,
		cinematic_camera_heading,
		cinematic_camera_pitch;

	object_3d_camera_index_numbers
		cinematic_camera_index;

	int
		cinematic_camera_depth,
		cinematic_camera_previous_moving_depth,
		cinematic_camera_previous_static_depth;

	//
	// building camera
	//

	vec3d
		building_camera_position;

	float
		building_camera_radius,
		building_camera_heading,
		building_camera_pitch,
		building_camera_zoom;

	//
	// weapon camera
	//

	vec3d
		weapon_camera_direction;

	int
		weapon_camera_primed;

	//
	// inset reverse tactical
	//

	vec3d
		stored_reverse_tactical_position,
		stored_reverse_tactical_motion_vector;

	matrix3x3
		stored_reverse_tactical_attitude;

	////////////////////////////////////////
	//
	// view data
	//
	////////////////////////////////////////

	list_root
		view_root,
		view_weapon_root;

	entity
		*external_view_entity;

	vec3d
		velocity;

	vec3d
		offset,      // adjustment for not looking directly at object
		offset_movement,  // for smooth movement
		turbulence_offset,   // offset for wobbly external camera
		turbulence_movement; // movement of wobbly camera
};

typedef struct CAMERA camera;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*camera_mode_names[NUM_CAMERA_MODES];
	
extern const char
	*camera_action_names[NUM_CAMERA_ACTIONS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity
	*camera_entity;

#define get_camera_entity() (camera_entity)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_camera_entity (entity *en);

extern entity *get_local_entity_view_list_pred (entity *en);

extern const char *get_camera_mode_name (camera_modes mode);

extern int camera_previous_mouse_update_flag;

extern void adjust_camera_smooth(camera* raw, vec3d* new_position);

extern void adjust_offset(camera*);
extern void reset_offset(camera*);

extern void add_turbulence(camera*, vec3d* position);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CAMERA_MODE_TEXT_DISPLAY_PERIOD	(1.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CAMERA_MIN_HEIGHT_ABOVE_GROUND		(1.1)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "cm_actn.h"

#include "cm_att.h"

#include "cm_auto.h"

#include "cm_build.h"

#include "cm_chase.h"

#include "cm_cine.h"

#include "cm_creat.h"

#include "cm_dbrf.h"

#include "cm_drop.h"

#include "cm_dstry.h"

#include "cm_eject.h"

#include "cm_end.h"

#include "cm_explo.h"

#include "cm_float.h"

#include "cm_flyby.h"

#include "cm_free.h"

#include "cm_funcs.h"

#include "cm_int.h"

#include "cm_list.h"

#include "cm_mode.h"

#include "cm_msgs.h"

#include "cm_pack.h"

#include "cm_ptr.h"

#include "cm_recog.h"

#include "cm_rvrs.h"

#include "cm_stat.h"

#include "cm_satel.h" // Jabberwock 031009 Satellite view

#include "cm_updt.h"

#include "cm_vec3d.h"

#include "cm_view.h"

#include "cm_wpn.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
