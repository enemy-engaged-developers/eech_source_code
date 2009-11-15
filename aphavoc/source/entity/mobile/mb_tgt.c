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
//
// ** These functions used by AI ONLY **
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TEXT_DEBUG_MODULE 0

#define LINE_DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LOS_COARSE_CHECK_DISTANCE					200.0f

#define LOS_FINE_CHECK_DISTANCE_SOURCE_END		40.0f
#define LOS_NUMBER_OF_FINE_CHECKS_SOURCE_END		8.0f

#define LOS_FINE_CHECK_DISTANCE_TARGET_END		24.0f
#define LOS_NUMBER_OF_FINE_CHECKS_TARGET_END		8.0f

#define LOS_OBJECT_CHECK_DISTANCE_SOURCE_END		200.0f

#define LOS_OBJECT_CHECK_DISTANCE_TARGET_END		200.0f

//
// Ignore any obstacles within a certain radius of the target
//

#define LOS_OBJECT_EXCLUDE_DISTANCE_TARGET_END	12.0f

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_entity_line_of_sight (entity *source, entity *target, mobile_los_check_criteria criteria)
{
	vec3d
		*source_position,
		*target_position;

	ASSERT (source);

	ASSERT (target);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	return check_position_line_of_sight (source, target, source_position, target_position, criteria);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_position_line_of_sight (entity *source, entity *target, vec3d *source_position, vec3d *target_position, mobile_los_check_criteria criteria)
{

	entity
		*collision_en;

	vec3d
		increment,
		collision_point,
		normal,
		#if LINE_DEBUG_MODULE
		old_position,
		#endif
		check_position,
		direction;

	float
		target_range,
		collision_distance,
		number_of_terrain_checks,
		terrain_elevation;

	terrain_3d_point_data
		terrain_info;

	ASSERT (source);

	ASSERT (target);

	ASSERT (source_position);

	ASSERT (target_position);

	direction.x = target_position->x - source_position->x;
	direction.y = target_position->y - source_position->y;
	direction.z = target_position->z - source_position->z;

	target_range = sqrt ((direction.x * direction.x) + (direction.z * direction.z));

	normalise_3d_vector (&direction);
	
	////////////////////////////////////////////////////////////////
	// COARSE line of sight check with terrain
	////////////////////////////////////////////////////////////////

	if (criteria &	MOBILE_LOS_CHECK_COURSE_TERRAIN)
	{
		number_of_terrain_checks = target_range / LOS_COARSE_CHECK_DISTANCE;
	
		increment.x = direction.x * LOS_COARSE_CHECK_DISTANCE;
		increment.y = direction.y * LOS_COARSE_CHECK_DISTANCE;
		increment.z = direction.z * LOS_COARSE_CHECK_DISTANCE;
	
		check_position = *source_position;
	
		memset (&terrain_info, 0, sizeof (terrain_3d_point_data));
	
		while (number_of_terrain_checks > 1.0)
		{
			#if LINE_DEBUG_MODULE
	
			old_position = check_position;
	
			#endif
	
			check_position.x += increment.x;
			check_position.y += increment.y;
			check_position.z += increment.z;
	
			get_3d_terrain_point_data (check_position.x, check_position.z, &terrain_info);
	
			terrain_elevation = get_3d_terrain_point_data_elevation (&terrain_info);
	
			if (terrain_elevation > check_position.y)
			{
	
				#if TEXT_DEBUG_MODULE
	
				debug_log ("MB_TGT: (%s -> %s) failed COURSE terrain LOS", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME));
	
				#endif
	
				return FALSE;
			}
	
			#if LINE_DEBUG_MODULE
	
			create_debug_3d_line (&old_position, &check_position, sys_col_yellow, 10.0);
	
			#endif
	
			number_of_terrain_checks --;
		}
	}
	
	////////////////////////////////////////////////////////////////
	// SOURCE END FINE line of sight check with terrain
	////////////////////////////////////////////////////////////////

	if (criteria &	MOBILE_LOS_CHECK_SOURCE_END_TERRAIN)
	{
		number_of_terrain_checks = target_range / LOS_FINE_CHECK_DISTANCE_SOURCE_END;
	
		number_of_terrain_checks = min (number_of_terrain_checks, LOS_NUMBER_OF_FINE_CHECKS_SOURCE_END);
	
		increment.x = direction.x * LOS_FINE_CHECK_DISTANCE_SOURCE_END;
		increment.y = direction.y * LOS_FINE_CHECK_DISTANCE_SOURCE_END;
		increment.z = direction.z * LOS_FINE_CHECK_DISTANCE_SOURCE_END;
	
		check_position = *source_position;
	
		while (number_of_terrain_checks > 1.0)
		{
			#if LINE_DEBUG_MODULE
	
			old_position = check_position;
	
			#endif
	
			check_position.x += increment.x;
			check_position.y += increment.y;
			check_position.z += increment.z;
	
			get_3d_terrain_point_data (check_position.x, check_position.z, &terrain_info);
	
			terrain_elevation = get_3d_terrain_point_data_elevation (&terrain_info);
	
			if (terrain_elevation > check_position.y)
			{
	
				#if TEXT_DEBUG_MODULE
	
				debug_log ("MB_TGT: (%s -> %s) failed FINE terrain LOS (source end)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME));
	
				#endif
	
				return FALSE;
			}
	
			#if LINE_DEBUG_MODULE
	
			create_debug_3d_line (&old_position, &check_position, sys_col_yellow, 10.0);
	
			#endif
	
			number_of_terrain_checks --;
		}
	}
	
	////////////////////////////////////////////////////////////////
	// TARGET END FINE line of sight check with terrain
	////////////////////////////////////////////////////////////////

	if (criteria &	MOBILE_LOS_CHECK_TARGET_END_TERRAIN)
	{
		number_of_terrain_checks = target_range / LOS_FINE_CHECK_DISTANCE_TARGET_END;
	
		number_of_terrain_checks = min (number_of_terrain_checks, LOS_NUMBER_OF_FINE_CHECKS_TARGET_END);
	
		increment.x = direction.x * LOS_FINE_CHECK_DISTANCE_TARGET_END;
		increment.y = direction.y * LOS_FINE_CHECK_DISTANCE_TARGET_END;
		increment.z = direction.z * LOS_FINE_CHECK_DISTANCE_TARGET_END;
	
		check_position = *target_position;
	
		while (number_of_terrain_checks > 1.0)
		{
			#if LINE_DEBUG_MODULE
	
			old_position = check_position;
	
			#endif
	
			check_position.x -= increment.x;
			check_position.y -= increment.y;
			check_position.z -= increment.z;
	
			get_3d_terrain_point_data (check_position.x, check_position.z, &terrain_info);
	
			terrain_elevation = get_3d_terrain_point_data_elevation (&terrain_info);
	
			if (terrain_elevation > check_position.y)
			{
	
				#if TEXT_DEBUG_MODULE
	
				debug_log ("MB_TGT: (%s -> %s) failed FINE terrain LOS (target end)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME));
	
				#endif
	
				return FALSE;
			}
	
			#if LINE_DEBUG_MODULE
	
			create_debug_3d_line (&old_position, &check_position, sys_col_yellow, 10.0);
	
			#endif
	
			number_of_terrain_checks --;
		}
	}

	////////////////////////////////////////////////////////////////
	// SOURCE END line of sight check with objects
	////////////////////////////////////////////////////////////////

	if (criteria &	MOBILE_LOS_CHECK_SOURCE_END_OBJECTS)
	{
		check_position.x = source_position->x + (direction.x * LOS_OBJECT_CHECK_DISTANCE_TARGET_END);
		check_position.y = source_position->y + (direction.y * LOS_OBJECT_CHECK_DISTANCE_TARGET_END);
		check_position.z = source_position->z + (direction.z * LOS_OBJECT_CHECK_DISTANCE_TARGET_END);

		collision_en = get_line_of_sight_collision_entity
							(
								source,
								target,
								source_position,
								&check_position,
								&collision_point,
								&normal
							);
	
		if (collision_en)
		{
	
			#if TEXT_DEBUG_MODULE

			debug_log ("MB_TGT: (%s -> %s) failed OBJECT LOS with %s (source end)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_type_name (collision_en));
			
			#endif
	
			return FALSE;
		}
	}
	
	////////////////////////////////////////////////////////////////
	// TARGET END line of sight check with objects
	////////////////////////////////////////////////////////////////

	if (criteria &	MOBILE_LOS_CHECK_TARGET_END_OBJECTS)
	{	
		check_position.x = target_position->x - (direction.x * LOS_OBJECT_CHECK_DISTANCE_TARGET_END);
		check_position.y = target_position->y - (direction.y * LOS_OBJECT_CHECK_DISTANCE_TARGET_END);
		check_position.z = target_position->z - (direction.z * LOS_OBJECT_CHECK_DISTANCE_TARGET_END);

		collision_en = get_line_of_sight_collision_entity
							(
								source,
								target,
								target_position,
								&check_position,
								&collision_point,
								&normal
							);
	
		if (collision_en)
		{
			collision_distance = get_sqr_3d_range (&collision_point, target_position);

			if (collision_distance > (LOS_OBJECT_EXCLUDE_DISTANCE_TARGET_END * LOS_OBJECT_EXCLUDE_DISTANCE_TARGET_END))
			{
				#if TEXT_DEBUG_MODULE
			
				debug_log ("MB_TGT: (%s -> %s) failed OBJECT LOS with %s (target end)", get_local_entity_string (source, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME), get_local_entity_type_name (collision_en));
			
				#endif
	
				return FALSE;
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

