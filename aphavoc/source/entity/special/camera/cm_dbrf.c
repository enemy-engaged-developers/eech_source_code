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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int debriefing_camera_valid (camera *raw)
{
	ASSERT (raw);

	if (get_gunship_entity ())
	{
		if (raw->external_view_entity == get_gunship_entity ())
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_debriefing_camera (camera *raw)
{
	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	//
	// motion vector
	//

	get_local_entity_vec3d (raw->external_view_entity, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);

//	set_assess_debriefing (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_debriefing_camera (camera *raw)
{
	entity
		*en;

	vec3d
		rel_camera_position;

	//
	// pre-amble
	//

	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	en = raw->external_view_entity;

	//
	// get camera attitude
	//

	get_3d_transformation_matrix (raw->attitude, get_local_entity_float_value (en, FLOAT_TYPE_HEADING) + rad (180.0), rad (-15.0), 0.0);

	//
	// get camera position
	//

	rel_camera_position.x = 0.0;
	rel_camera_position.y = 0.0;
	rel_camera_position.z = -get_local_entity_float_value (en, FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE);

	multiply_matrix3x3_vec3d (&rel_camera_position, raw->attitude, &rel_camera_position);

	get_local_entity_target_point (en, &raw->position);

	raw->position.x += rel_camera_position.x;
	raw->position.y += rel_camera_position.y;
	raw->position.z += rel_camera_position.z;

	//
	// keep point above ground (unless point off map)
	//

	if (point_inside_map_area (&raw->position))
	{
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + 0.5);
	}

	//
	// motion vector
	//

	get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->motion_vector);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
