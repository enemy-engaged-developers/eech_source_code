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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_local_3d_object (entity *en, float range)
{
	segment
		*raw;

	entity
		*parent;

	object_3d_instance
		*inst3d;

	float
		pitch;

	raw = get_local_entity_data (en);

	if (raw->fix.object_3d_shape == OBJECT_3D_INVALID_OBJECT_INDEX)
	{
		return;
	}

	inst3d = construct_temporary_3d_object (raw->fix.object_3d_shape, TRUE);

	if (inst3d)
	{
		inst3d->object_has_shadow = FALSE;

		parent = get_local_entity_parent (en, LIST_TYPE_SEGMENT);

		ASSERT (parent);

		memcpy (&inst3d->vp.position, &raw->fix.position, sizeof (vec3d));

		pitch = get_local_entity_float_value (parent, FLOAT_TYPE_PITCH);

		get_3d_transformation_matrix (inst3d->vp.attitude, raw->fix.heading, pitch, 0.0);

		if (parent->type == ENTITY_TYPE_BRIDGE)
		{
			//
			// special case for bridges - scale the legs
			//

			vec3d
				relative_scale;

			float
				leg_scale;

			leg_scale = get_local_entity_float_value (parent, FLOAT_TYPE_SCALE);

			if (leg_scale != 1.0)
			{
				relative_scale.x = 1.0;
				relative_scale.y = leg_scale;
				relative_scale.z = 1.0;

				set_sub_object_type_relative_scale(inst3d, OBJECT_3D_SUB_OBJECT_BRIDGE_LEG, &relative_scale);
			}

			set_sub_object_type_heading_pitch_and_roll(inst3d, OBJECT_3D_SUB_OBJECT_BRIDGE_LEG, 0.0, pitch, 0.0);

		}

		insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
static void draw_local_2d_symbol (entity *en)
{
	segment
		*raw;

	struct OBJECT_3D_BOUNDS
		*bounding_box;

	if (command_line_run_mode == RUN_MODE_AITOOL)
	{
	
		raw = get_local_entity_data (en);
	
		set_2d_instance_position (active_2d_environment, raw->fix.position.x, raw->fix.position.z);
	
		bounding_box = get_object_3d_bounding_box (raw->fix.object_3d_shape);
	
		set_2d_instance_scaling (active_2d_environment, bounding_box->xmax - bounding_box->xmin, bounding_box->zmax - bounding_box->zmin);
	
		set_2d_instance_rotation (active_2d_environment, -get_local_entity_float_value (en, FLOAT_TYPE_HEADING));
	
		draw_2d_square (sys_col_dark_red);
	
		reset_2d_instance (planner_map_env);
	}
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_segment_draw_functions (void)
{
	fn_draw_local_entity_3d_object[ENTITY_TYPE_SEGMENT]	= draw_local_3d_object;

	//fn_draw_local_entity_2d_symbol[ENTITY_TYPE_SEGMENT]	= draw_local_2d_symbol;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
