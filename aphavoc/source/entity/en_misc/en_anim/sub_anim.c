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

#define DEBUG_MODULE					0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int object_contains_sub_object_type( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, int depth, object_3d_sub_object_search_data *search_result)
{
	object_3d_sub_object_search_data
		search;

	search.search_object = inst3d;
	search.search_depth = depth;
	search.sub_object_index = sub_object_type;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		if (search_result)
		{
			memcpy( search_result, &search, sizeof( object_3d_sub_object_search_data ) );
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sub_object_contains_sub_object_type( object_3d_sub_object_search_data *parent_search, object_3d_sub_object_index_numbers sub_object_type, int depth, object_3d_sub_object_search_data *search_result)
{
	object_3d_sub_object_search_data
		search;

	memcpy( &search, parent_search, sizeof( object_3d_sub_object_search_data ) );

	search.search_depth = depth;
	search.sub_object_index = sub_object_type;

	if (find_object_3d_sub_object_from_sub_object (parent_search, &search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		if (search_result)
		{
			memcpy( search_result, &search, sizeof( object_3d_sub_object_search_data ) );
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int count_sub_object_type_depth( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type )
{
	object_3d_sub_object_search_data
		search;

	int
		depth;

	depth = 0;

	while (TRUE)
	{
		search.search_object = inst3d;
		search.search_depth = depth;
		search.sub_object_index = sub_object_type;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			depth ++;
		}
		else
		{
			return depth;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_sub_object_relative_position( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, int depth, vec3d *relative_position, object_3d_sub_object_search_data *search_result )
{
	object_3d_sub_object_search_data
		search;

	viewpoint
		rel_vp;

	search.search_object = inst3d;
	search.search_depth = depth;
	search.sub_object_index = sub_object_type;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (search.result_sub_object, &rel_vp);

//		relative_position->x = search.object->relative_position.x;
//		relative_position->y = search.object->relative_position.y;
//		relative_position->z = search.object->relative_position.z;

		relative_position->x = rel_vp.x - inst3d->vp.x;
		relative_position->y = rel_vp.y - inst3d->vp.y;
		relative_position->z = rel_vp.z - inst3d->vp.z;

		if ( search_result )
		{
			memcpy( search_result, &search, sizeof( object_3d_sub_object_search_data ) );
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_sub_object_type_visible_status( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, int visible )
{
	object_3d_sub_object_search_data
		search;

	int
		depth,
		found_flag;

	depth = 0;

	found_flag = FALSE;

	while (TRUE)
	{
		search.search_object = inst3d;
		search.search_depth = depth;
		search.sub_object_index = sub_object_type;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = visible;

			found_flag = TRUE;
		}
		else
		{
			break;
		}

		depth++;
	}

	return found_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_sub_object_type_relative_scale( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, vec3d *relative_scale )
{
	object_3d_sub_object_search_data
		search;

	int
		depth,
		found_flag;

	depth = 0;

	found_flag = FALSE;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = sub_object_type;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_scale.x = relative_scale->x;
			search.result_sub_object->relative_scale.y = relative_scale->y;
			search.result_sub_object->relative_scale.z = relative_scale->z;

			found_flag = TRUE;
		}
		else
		{
			break;
		}

		depth++;
	}

	return found_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_sub_object_type_heading_pitch_and_roll( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, float heading, float pitch, float roll )
{
	object_3d_sub_object_search_data
		search;

	int
		depth;

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = sub_object_type;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_heading = heading;
			search.result_sub_object->relative_pitch = pitch;
			search.result_sub_object->relative_roll = roll;
		}
		else
		{
			break;
		}

		depth++;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int modify_sub_object_type_heading_pitch_and_roll( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, float dh, float dp, float dr )
{
	object_3d_sub_object_search_data
		search;

	int
		depth;

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = sub_object_type;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_heading = wrap_angle (search.result_sub_object->relative_heading + dh);
			search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + dp);
			search.result_sub_object->relative_roll = wrap_angle (search.result_sub_object->relative_roll + dr);
		}
		else
		{
			break;
		}

		depth++;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int activate_and_modify_sub_object_type_heading_pitch_and_roll( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, int visible, float dh, float dp, float dr )
{
	object_3d_sub_object_search_data
		search;

	int
		depth,
		found_flag;

	depth = 0;

	found_flag = FALSE;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = sub_object_type;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = visible;

			search.result_sub_object->relative_heading = wrap_angle (search.result_sub_object->relative_heading + dh);
			search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + dp);
			search.result_sub_object->relative_roll = wrap_angle (search.result_sub_object->relative_roll + dr);

			found_flag = TRUE;
		}
		else
		{
			break;
		}

		depth++;
	}

	return found_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int interpolate_sub_object_type_heading_pitch_and_roll( object_3d_instance *inst3d, object_3d_sub_object_index_numbers sub_object_type, float scale_value )
{
	object_3d_sub_object_search_data
		search;

	int
		depth,
		found_flag;

	float
		min_angle,
		max_angle;

	depth = 0;

	found_flag = FALSE;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = sub_object_type;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// heading
			//

			min_angle = search.relative_heading_minimum;
			max_angle = search.relative_heading_maximum;

			search.result_sub_object->relative_heading = min_angle + ( scale_value * ( max_angle - min_angle ) );

			//
			// pitch
			//

			min_angle = search.relative_pitch_minimum;
			max_angle = search.relative_pitch_maximum;

			search.result_sub_object->relative_pitch = min_angle + ( scale_value * ( max_angle - min_angle ) );

			//
			// roll
			//

			min_angle = search.relative_roll_minimum;
			max_angle = search.relative_roll_maximum;

			search.result_sub_object->relative_roll = min_angle + ( scale_value * ( max_angle - min_angle ) );

			found_flag = TRUE;

		}
		else
		{
			break;
		}

		depth++;
	}

	return found_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////












