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

float get_local_entity_target_bearing (entity *source, entity *target, float *range)
{
	vec3d
		*source_pos,
		*target_pos;

	float
		dx,
		dz,
		bearing;

	ASSERT (source);

	ASSERT (target);

	source_pos = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = target_pos->x - source_pos->x;
	dz = target_pos->z - source_pos->z;

	if (range)
	{
		*range = sqrt ((dx * dx) + (dz * dz));
	}

	bearing = atan2 (dx, dz);

	if (bearing < 0.0)
	{
		bearing += rad (360.0f);
	}

	return (bearing);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_entity_target_relative_bearing (entity *source, entity *target)
{
	vec3d
		*source_pos,
		*target_pos;

	float
		dx,
		dz,
		bearing,
		heading,
		relative_bearing;

	ASSERT (source);

	ASSERT (target);

	source_pos = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = target_pos->x - source_pos->x;
	dz = target_pos->z - source_pos->z;

	bearing = atan2 (dx, dz);

	heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	relative_bearing = bearing - heading;

	if (relative_bearing > rad (180.0f))
	{
		relative_bearing -= rad (360.0f);
	}
	else if (relative_bearing < rad (-180.0f))
	{
		relative_bearing += rad (360.0f);
	}

	return (relative_bearing);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_local_entity_target_point (entity *en, vec3d *target_point)
{
	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	viewpoint
		vp;

	object_3d_index_numbers
		index;

	float
		heading,
		sin_heading,
		cos_heading,
		rotated_x_offset,
		rotated_z_offset;

	ASSERT (en);

	ASSERT (target_point);

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

	if (inst3d)
	{
		search.search_depth = 0;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TARGET_POINT;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &inst3d->vp.position);

			get_local_entity_attitude_matrix (en, inst3d->vp.attitude);

			get_3d_sub_object_world_viewpoint (search.result_sub_object, &vp);

			*target_point = vp.position;
		}
		else
		{
			get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, target_point);
		}
	}
	else
	{
		get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, target_point);

		//
		// if this is a fixed object then add the target point offset rotated by heading (assume flat ground)
		//

		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_FIXED))
		{
			index = get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE);

			if (index != OBJECT_3D_INVALID_OBJECT_INDEX)
			{
				if ((target_point_offsets[index].x != 0.0) || (target_point_offsets[index].z != 0.0))
				{
					heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

					if (heading != 0.0)
					{
						sin_heading = sin (heading);
						cos_heading = cos (heading);

						rotated_x_offset = (cos_heading * target_point_offsets[index].x) + (sin_heading * target_point_offsets[index].z);
						rotated_z_offset = (cos_heading * target_point_offsets[index].z) - (sin_heading * target_point_offsets[index].x);

						target_point->x += rotated_x_offset;
						target_point->z += rotated_z_offset;
					}
				}

				target_point->y += target_point_offsets[index].y;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
