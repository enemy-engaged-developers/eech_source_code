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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "3d.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_texture_animations ( object_3d_instance *obj )
{

	int
		count,
		scene,
		*animations,
		*indices;

	scene = obj->object_number;

	if ( objects_3d_scene_database[scene].number_of_texture_animations )
	{

		animations = objects_3d_scene_database[scene].texture_animations;

		indices = obj->texture_animations;

		ASSERT ( animations );
		ASSERT ( indices );

		for ( count = objects_3d_scene_database[scene].number_of_texture_animations; count > 0; count-- )
		{
	
			texture_animations[ *animations ].current_frame = *indices;

			animations++;

			indices++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_texture_animation_frame_on_object ( object_3d_instance *obj, enum TEXTURE_ANIMATION_INDICES index, int frame )
{

	int
		scene,
		count;

	if ( frame < 0 )
	{

		debug_log ( "Setting an animation frame to an invalid number: %d", frame );
	}

	scene = obj->object_number;

	if ( objects_3d_scene_database[scene].number_of_texture_animations )
	{

		for ( count = 0; count < objects_3d_scene_database[scene].number_of_texture_animations; count++ )
		{

			if ( objects_3d_scene_database[scene].texture_animations[count] == index )
			{

				if ( frame > texture_animations[index].number_of_frames )
				{

					debug_log ( "Trying to set an animation frame outside the number of frames" );
				}
				else
				{
	
					obj->texture_animations[count] = frame;

					return ( TRUE );
				}
			}
		}

		return ( FALSE );
	}
	else
	{

		return ( FALSE );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int advance_texture_animation_frame_on_object ( object_3d_instance *obj, enum TEXTURE_ANIMATION_INDICES index )
{

	int
		scene,
		count;

	scene = obj->object_number;

	if ( objects_3d_scene_database[scene].number_of_texture_animations )
	{

		for ( count = 0; count < objects_3d_scene_database[scene].number_of_texture_animations; count++ )
		{

			if ( objects_3d_scene_database[scene].texture_animations[count] == index )
			{

				if ( ++( obj->texture_animations[count] ) >= texture_animations[index].number_of_frames )
				{

					obj->texture_animations[count] = 0;
				}

				return ( TRUE );
			}
		}

		return ( FALSE );
	}
	else
	{

		return ( FALSE );
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_texture_animation_number_of_frames ( enum TEXTURE_ANIMATION_INDICES index )
{

	return ( texture_animations[index].number_of_frames );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen *get_texture_animation_texture_pointer ( enum TEXTURE_ANIMATION_INDICES index, int frame )
{

	if ( ( frame < 0 ) || ( frame >= texture_animations[index].number_of_frames ) )
	{

		debug_log ( "Trying to get texture animation frame %d", frame );
	}

	return ( system_textures[ texture_animations[index].texture_indices[frame] ] );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen *get_texture_map_pointer ( texture_index_numbers index )
{


	ASSERT ( index >= 0 );
	ASSERT ( index < TEXTURE_INDEX_LAST );

	return ( system_textures[index] );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

