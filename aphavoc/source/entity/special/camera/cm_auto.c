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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MOTION_STATES
{
	MOTION_STATE_DONT_CARE,
	MOTION_STATE_STATIC,
	MOTION_STATE_MOVING,
	NUM_MOTION_STATES
};

typedef enum MOTION_STATES motion_states;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *find_matching_entity (camera *raw, entity_forces force, entity_sides side, motion_states state)
{
	entity
		*this_entity,
		*best_entity;

	float
		this_score,
		best_score,
		view_interest_level;

	ASSERT (raw);

	this_entity = raw->view_root.first_child;

	best_entity = NULL;

	best_score = -1.0;

	while (this_entity)
	{
		if (get_entity_available_from_view_menu (this_entity))
		{
			this_score = 0.0;

			if (get_local_entity_int_value (this_entity, INT_TYPE_ALIVE))
			{
				if ((force == ENTITY_FORCE_UNKNOWN) || (get_local_entity_int_value (this_entity, INT_TYPE_FORCE) == force))
				{
					this_score += 1.0;
				}

				////////////////////////////////////////

				if ((side == ENTITY_SIDE_NEUTRAL) || (get_local_entity_int_value (this_entity, INT_TYPE_SIDE) == side))
				{
					this_score += 1.0;
				}

				////////////////////////////////////////

				if (state == MOTION_STATE_DONT_CARE)
				{
					this_score += 1.0;
				}
				else if ((state == MOTION_STATE_STATIC) && (get_local_entity_vec3d_magnitude (this_entity, VEC3D_TYPE_MOTION_VECTOR) < 1.0))
				{
					this_score += 1.0;
				}
				else if ((state == MOTION_STATE_MOVING) && (get_local_entity_vec3d_magnitude (this_entity, VEC3D_TYPE_MOTION_VECTOR) >= 1.0))
				{
					this_score += 1.0;
				}

				////////////////////////////////////////

				view_interest_level = get_local_entity_float_value (this_entity, FLOAT_TYPE_VIEW_INTEREST_LEVEL);

				view_interest_level = bound (view_interest_level, 0.0, DEFAULT_VIEW_INTEREST_LEVEL);

				view_interest_level *= (2.0 / DEFAULT_VIEW_INTEREST_LEVEL);

				this_score += view_interest_level;

				////////////////////////////////////////

				this_score += frand1 ();
			}

			if (this_score > best_score)
			{
				best_score = this_score;

				best_entity = this_entity;
			}

			////////////////////////////////////////
		}

		this_entity = get_local_entity_child_succ (this_entity, LIST_TYPE_VIEW);
	}

	return (best_entity);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_best_view_entity (camera *raw)
{
	entity
		*en;

	entity_forces
		force;

	entity_sides
		side;

	motion_states
		state;

	float
		x;

	ASSERT (raw);

	////////////////////////////////////////
	//
	// force
	//
	////////////////////////////////////////

	x = frand1 ();

	if (x <= 0.6)
	{
		force = ENTITY_FORCE_AIR;
	}
	else if (x <= 0.9)
	{
		force = ENTITY_FORCE_GROUND;
	}
	else
	{
		force = ENTITY_FORCE_SEA;
	}

	////////////////////////////////////////
	//
	// side
	//
	////////////////////////////////////////

	x = frand1 ();

	if (x <= 0.5)
	{
		side = ENTITY_SIDE_BLUE_FORCE;
	}
	else
	{
		side = ENTITY_SIDE_RED_FORCE;
	}

	////////////////////////////////////////
	//
	// motion state
	//
	////////////////////////////////////////

	x = frand1 ();

	if (x <= 0.333)
	{
		state = MOTION_STATE_STATIC;
	}
	else
	{
		state = MOTION_STATE_MOVING;
	}

	////////////////////////////////////////
	//
	// find ideal entity, if not, relax parameters until something is found
	//
	////////////////////////////////////////

	en = find_matching_entity (raw, force, side, state);

	if (!en)
	{
		en = find_matching_entity (raw, force, side, MOTION_STATE_DONT_CARE);

		if (!en)
		{
			en = find_matching_entity (raw, force, ENTITY_SIDE_NEUTRAL, MOTION_STATE_DONT_CARE);

			if (!en)
			{
				en = find_matching_entity (raw, ENTITY_FORCE_UNKNOWN, ENTITY_SIDE_NEUTRAL, MOTION_STATE_DONT_CARE);
			}
		}
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// always switch view entity before switching camera mode so that a suitable camera is selected
//

entity *switch_auto_edit_entity (camera *raw)
{
	entity
		*new_;

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	if (frand1 () < 0.667)
	{
		new_ = get_best_view_entity (raw);

		if (new_)
		{
			set_external_view_entity (new_);
		}
	}
	else
	{
		new_ = NULL;
	}

	return (new_);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

camera_modes get_auto_edit_random_camera_mode (camera *raw)
{
	camera_modes
		mode;

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	//
	// if the viewed entity is not moving then avoid the fly-by camera
	//

	mode = CAMERA_MODE_CINEMATIC;

	if (frand1 () < 0.5)
	{
		if (get_local_entity_vec3d_magnitude (raw->external_view_entity, VEC3D_TYPE_MOTION_VECTOR) >= 1.0)
		{
			mode = CAMERA_MODE_FLY_BY;
		}
	}

	return (mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int switch_auto_edit_camera_mode (camera *raw)
{
	camera_modes
		new_camera_mode;

	int
		changed;

	ASSERT (raw);

	new_camera_mode = get_auto_edit_random_camera_mode (raw);

	if (new_camera_mode == raw->camera_mode)
	{
		changed = FALSE;
	}
	else
	{
		set_camera_mode (raw, new_camera_mode, TRUE);

		if (new_camera_mode == CAMERA_MODE_FLY_BY)
		{
			update_fly_by_camera_continued (raw);
		}
		else
		{
			update_cinematic_camera_continued (raw);
		}

		changed = TRUE;
	}

	return (changed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_local_entity_view_interest_level (entity *en)
{
	float
		level;

	ASSERT (en);

	level = get_local_entity_float_value (en, FLOAT_TYPE_VIEW_INTEREST_LEVEL);

	if (level > 0.0)
	{
		level -= get_delta_time ();

		if (level < 0.0)
		{
			level = 0.0;
		}

		set_local_entity_float_value (en, FLOAT_TYPE_VIEW_INTEREST_LEVEL, level);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
