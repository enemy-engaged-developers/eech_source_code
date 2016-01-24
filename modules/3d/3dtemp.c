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



#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static temporary_object_3d_instance
	*temporary_3d_objects = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_temporary_3d_instances ( void )
{

	temporary_3d_objects = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_temporary_3d_instances ( void )
{

	while ( temporary_3d_objects )
	{

		temporary_object_3d_instance
			*this_temp;

		this_temp = temporary_3d_objects;

		temporary_3d_objects = temporary_3d_objects->next_temporary_instance;

		if ( this_temp->real_object )
		{

			destruct_3d_object ( this_temp->instance );
		}
		else
		{
	
			//
			// Free up the memory for the last 3d instance
			//

			if ( this_temp->instance->texture_animations )
			{

				free_mem ( this_temp->instance->texture_animations );
			}

			free_mem ( this_temp->instance );
		}

		free_mem ( this_temp );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_instance *construct_temporary_3d_object ( object_3d_index_numbers index, int real_object )
{

	temporary_object_3d_instance
		*this_instance;

	object_3d_instance
		*object;

	this_instance = ( temporary_object_3d_instance * ) malloc_fast_mem ( sizeof ( temporary_object_3d_instance ) );

	ASSERT ( this_instance );

	this_instance->real_object = real_object;

	if ( real_object )
	{

		this_instance->instance = construct_3d_object ( index );
	}
	else
	{

		object = ( object_3d_instance * ) malloc_fast_mem ( sizeof ( object_3d_instance ) );

		this_instance->instance = object;

		get_3d_transformation_matrix ( object->vp.attitude, 0, 0, 0 );
		object->object_number = index;
		object->parent = NULL;
		object->sub_objects = NULL;
		object->vp.x = 0;
		object->vp.y = 0;
		object->vp.z = 0;
		object->relative_scale.x = 1;
		object->relative_scale.y = 1;
		object->relative_scale.z = 1;
		object->object_has_shadow = TRUE;
		object->object_internal_lighting = FALSE;
		object->object_sprite_lights = FALSE;
		object->requires_immediate_render = FALSE;
		object->object_dissolve_value = 255;
		object->object_diffuse_value = 255;

		if ( objects_3d_scene_database[index].number_of_texture_animations )
		{
	
			object->texture_animations = ( int * ) malloc_fast_mem ( sizeof ( int ) * objects_3d_scene_database[index].number_of_texture_animations );
	
			ASSERT ( object->texture_animations );
	
			memset ( object->texture_animations, 0, ( sizeof ( int ) * objects_3d_scene_database[index].number_of_texture_animations ) );
		}
		else
		{
	
			object->texture_animations = NULL;
		}
	}

	if ( temporary_3d_objects )
	{

		this_instance->next_temporary_instance = temporary_3d_objects;

		temporary_3d_objects = this_instance;
	}
	else
	{

		this_instance->next_temporary_instance = NULL;

		temporary_3d_objects = this_instance;
	}

	return ( this_instance->instance );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
