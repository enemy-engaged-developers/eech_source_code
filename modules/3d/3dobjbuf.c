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

#include "3d.h"
#include "cmndline.h" // trees_fog

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DRAW_OBJECT_BOUNDING_BOX 0

#define BATCH_DEFINED 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// There are FIVE lists of objects in a scene.
//
//  1) High zbuffered objects - objects which are ABOVE the cloud layer and have zbuffer writing enabled
//  2) High non-zbuffered objects - objects which are ABOVE the cloud layer and have zbuffer writing disabled
//  3) Middle objects - objects which are IN the cloud layer ( including the cloud layer itself ) - Z buffer writing disabled
//  4) Low zbuffered objects - objects which are BELOW the cloud layer and have zbuffer writing enabled
//  5) Low non-zbuffered objects - objects which are BELOW the cloud layer and have zbuffer writing disabled
//  6) Near objects - objects which have to be z sorted - with no z buffering turned on at all
//

scene_slot_drawing_list
	*high_zbuffered_scene_slot_sorted_list,
	*high_nonzbuffered_scene_slot_sorted_list,
	*middle_scene_slot_sorted_list,
	*low_zbuffered_scene_slot_sorted_list,
	*low_nonzbuffered_scene_slot_sorted_list,
#if 0
	*near_scene_slot_list,
#endif
	*current_scene_slot_list;

float
	middle_scene_slot_height;
static int
	fog = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scene_slot_drawing_list
	*last_high_zbuffered_scene_slot_insert_point,
	*last_high_nonzbuffered_scene_slot_insert_point,
	*last_middle_scene_slot_insert_point,
	*last_low_zbuffered_scene_slot_insert_point,
	*last_low_nonzbuffered_scene_slot_insert_point,
#if 0
	*last_near_scene_slot_insert_point,
#endif
	scene_slot_order_list[MAX_3D_OBJECTS];

static int
	scene_slot_order_index;

object_3d_instance
	*exclusive_3d_instance = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_objects_in_3d_scene,
	final_number_of_objects_in_3d_scene,
	number_of_sprites_in_3d_scene,
	final_number_of_sprites_in_3d_scene;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void insert_near_3d_scene_slot_into_3d_scene ( scene_slot_drawing_list *object );
#endif

void draw_normal_scene_objects ( scene_slot_drawing_list *object_order );

void draw_transparent_scene_objects ( scene_slot_drawing_list *object_order );

#if 0
void draw_z_sorted_scene_objects ( scene_slot_drawing_list *object_order );
#endif

static void set_up_tnl_hardware ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_middle_scene_slot_height ( float height )
{

	middle_scene_slot_height = height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

scene_slot_drawing_list * get_3d_scene_slot ( void )
{

	if ( scene_slot_order_index < MAX_3D_OBJECTS )
	{

		return ( &scene_slot_order_list[scene_slot_order_index++] );
	}
	else
	{

		debug_log ( "Exceeded object count for scene" );

		return ( NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_zbiased_object_into_3d_scene ( enum OBJECT_3D_DRAWING_TYPES type, void *data, float distance_bias )
{

	scene_slot_drawing_list
		*buffer;

	number_of_objects_in_3d_scene++;

	switch ( type )
	{
	
		case OBJECT_3D_DRAW_TYPE_OBJECT:
		{

			object_3d_instance
				*object;

			enum OBJECT_3D_VISIBILITY
				visibility;

			object = ( object_3d_instance * ) data;

			if ( ( !exclusive_3d_instance ) || ( exclusive_3d_instance == object ) )
			{

				if ( ( object->object_has_shadow ) && ( shadows_enabled ) && ( !exclusive_3d_instance ) )
				{

					enum OBJECT_3D_VISIBILITY
						visible;

					visible = get_object_3d_instance_shadow_visibility ( object );

					if ( visible != OBJECT_3D_NOT_VISIBLE )
					{
	
						buffer = get_3d_scene_slot ();
			
						if ( buffer )
						{
		
							distance_bias += object->view_position.z;
		
							distance_bias += SHADOW_DISTANCE_BIAS;
		
							buffer->type = OBJECT_3D_DRAW_TYPE_OBJECT_SHADOW;
			
							buffer->z = *( ( int * ) &distance_bias );

							buffer->object = object;
		
							if ( get_3d_shadows_translucent () )
							{
		
								insert_low_nonzbuffered_scene_slot_into_3d_scene ( buffer );
							}
							else
							{
			
								insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
							}
						}
					}
				}
	
				//
				// Set the relative position & clip object
				//
	
				set_object_3d_instance_relative_position ( object );
	
				visibility = get_object_3d_instance_visibility ( object );
	
				if ( visibility != OBJECT_3D_NOT_VISIBLE )
				{
	
					buffer = get_3d_scene_slot ();
		
					if ( buffer )
					{
	
						distance_bias += object->view_position.z;
	
						buffer->type = OBJECT_3D_DRAW_TYPE_OBJECT;
		
						buffer->z = *( ( int * ) &distance_bias );

						buffer->object = object;
	
						if ( object->vp.y > middle_scene_slot_height )
						{
	
							insert_high_zbuffered_scene_slot_into_3d_scene ( buffer );
						}
						else
						{
	
							insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
						}

						//
						// Hack in here to pre-load any textures on the object
						//

//						if ( active_3d_environment->infrared_mode == RENDER_CLEAR )
						{
	
//							pre_render_3d_object ( object );
						}
					}
				}
			}

			break;
		}

		case OBJECT_3D_DRAW_TYPE_OBJECT_SCENE:
		{

			struct OBJECT_3D_SCENE
				*object;

			enum OBJECT_3D_VISIBILITY
				visibility;

			object = ( object_3d_scene * ) data;

			//
			// Set the relative position & clip object
			//

			get_position_3d_relative_position ( &object->position, &object->relative_position );

			visibility = get_scene_3d_instance_visibility ( object->object_index, &object->relative_position );

			if ( visibility != OBJECT_3D_NOT_VISIBLE )
			{

				buffer = get_3d_scene_slot ();
	
				if ( buffer )
				{

					distance_bias += object->relative_position.z;

					buffer->type = OBJECT_3D_DRAW_TYPE_OBJECT_SCENE;
	
					buffer->z = *( ( int * ) &distance_bias );
	
					buffer->scene = *object;

					if ( object->position.y > middle_scene_slot_height )
					{

						insert_high_zbuffered_scene_slot_into_3d_scene ( buffer );
					}
					else
					{

						insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
					}
				}
			}

			break;
		}

		case OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT:
		{

			object_3d_instance
				*object;

			enum OBJECT_3D_VISIBILITY
				visibility;

			object = ( object_3d_instance * ) data;

			if ( ( !exclusive_3d_instance ) || ( exclusive_3d_instance == object ) )
			{

				//
				// Set the relative position & clip object
				//
	
				set_object_3d_instance_relative_position ( object );
	
				visibility = get_object_3d_instance_visibility ( object );
	
				if ( visibility != OBJECT_3D_NOT_VISIBLE )
				{
	
					buffer = get_3d_scene_slot ();
		
					if ( buffer )
					{
	
						distance_bias += object->view_position.z;
	
						buffer->type = OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT;
		
						buffer->z = *( ( int * ) &distance_bias );
		
						buffer->object = object;
	
						if ( object->vp.y > middle_scene_slot_height )
						{
	
							insert_high_zbuffered_scene_slot_into_3d_scene ( buffer );
						}
						else
						{
	
							insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
						}

						//
						// Hack in here to pre-load any textures on the object
						//

//						if ( active_3d_environment->infrared_mode == RENDER_CLEAR )
						{
	
//							pre_render_3d_object ( object );
						}
					}
				}
			}

			break;
		}

		case OBJECT_3D_DRAW_TYPE_SPRITE:
		{

			object_3d_sprite
				*sprite;

			vec3d
				relative_position;

			if ( !exclusive_3d_instance )
			{
	
				sprite = ( object_3d_sprite * ) data;
	
				get_position_3d_relative_position ( &sprite->position, &relative_position );
	
				if ( relative_position.z >= clip_hither )
				{
	
					buffer = get_3d_scene_slot ();
		
					if ( buffer )
					{
	
						distance_bias += relative_position.z;
	
						buffer->type = OBJECT_3D_DRAW_TYPE_SPRITE;
		
						buffer->z = *( ( int * ) &distance_bias );
		
						buffer->sprite.position = relative_position;

						if (sprite->additive && (active_3d_environment->render_filter == RENDER_INFRARED || active_3d_environment->render_filter == RENDER_MONOCHROME))
							buffer->sprite.texture = system_textures[ texture_animations[TEXTURE_ANIMATION_INDEX_INFRARED_FLAME].texture_indices[0] ];
						else
							buffer->sprite.texture = sprite->texture;

						buffer->sprite.radius = sprite->radius;
						buffer->sprite.colour = sprite->colour;
						buffer->sprite.additive = sprite->additive;
						buffer->sprite.roll = sprite->roll;
	
						if ( sprite->position.y > middle_scene_slot_height )
						{
	
							insert_high_nonzbuffered_scene_slot_into_3d_scene ( buffer );
						}
						else
						{
	
							insert_low_nonzbuffered_scene_slot_into_3d_scene ( buffer );
						}
					}
				}
			}

			break;
		}

		case OBJECT_3D_DRAW_TYPE_EXPLOSION:
		{

			object_3d_explosion
				*explosion;

			vec3d
				relative_position;

			if ( !exclusive_3d_instance )
			{
	
				explosion = ( object_3d_explosion * ) data;
	
				get_position_3d_relative_position ( &explosion->position, &relative_position );
	
				if ( relative_position.z >= clip_hither )
				{
	
					buffer = get_3d_scene_slot ();
		
					if ( buffer )
					{
	
						distance_bias += relative_position.z;
	
						buffer->type = OBJECT_3D_DRAW_TYPE_EXPLOSION;
		
						buffer->z = *( ( int * ) &distance_bias );
		
						buffer->explosion.position = explosion->position;
						buffer->explosion.relative_position = relative_position;
						buffer->explosion.scale = explosion->scale;
						buffer->explosion.animation = explosion->animation;
						buffer->explosion.object_index = explosion->object_index;
	
						if ( explosion->position.y > middle_scene_slot_height )
						{
	
							insert_high_nonzbuffered_scene_slot_into_3d_scene ( buffer );
						}
						else
						{
	
							insert_low_nonzbuffered_scene_slot_into_3d_scene ( buffer );
						}
					}
				}
			}

			break;
		}

	
		default:
		{

			debug_fatal ( "Unknown object type in insert_object_3d_instance_into_scene" );

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_object_shadow_into_3d_scene ( object_3d_instance *object )
{

	scene_slot_drawing_list
		*buffer;

	number_of_objects_in_3d_scene++;

	if ( ( !exclusive_3d_instance ) || ( exclusive_3d_instance == object ) )
	{

		if ( ( object->object_has_shadow ) && ( shadows_enabled ) )
		{

			enum OBJECT_3D_VISIBILITY
				visible;

			visible = get_object_3d_instance_shadow_visibility ( object );

			if ( visible != OBJECT_3D_NOT_VISIBLE )
			{

				buffer = get_3d_scene_slot ();
	
				if ( buffer )
				{

					buffer->type = OBJECT_3D_DRAW_TYPE_OBJECT_SHADOW;
	
					buffer->z = *( ( int * ) &object->view_position.z );
	
					buffer->object = object;

					if ( get_3d_shadows_translucent () )
					{

						insert_low_nonzbuffered_scene_slot_into_3d_scene ( buffer );
					}
					else
					{
	
						insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_zbiased_relative_object_into_3d_scene ( enum OBJECT_3D_DRAWING_TYPES type, vec3d *relative_position, void *data, float distance_bias )
{

	scene_slot_drawing_list
		*buffer;

	number_of_objects_in_3d_scene++;

	switch ( type )
	{
	
		case OBJECT_3D_DRAW_TYPE_OBJECT:
		{

			object_3d_instance
				*object;

			enum OBJECT_3D_VISIBILITY
				visibility;

			object = ( object_3d_instance * ) data;

			if ( ( !exclusive_3d_instance ) || ( exclusive_3d_instance == object ) )
			{

				//
				// No shadows on relative objects
				//

				//
				// Set the relative position & clip object
				//

				object->view_position = *relative_position;

//				set_object_3d_instance_relative_position ( object );
	
				visibility = get_object_3d_instance_visibility ( object );
	
				if ( visibility != OBJECT_3D_NOT_VISIBLE )
				{
	
					buffer = get_3d_scene_slot ();
		
					if ( buffer )
					{
	
						distance_bias += object->view_position.z;
	
						buffer->type = OBJECT_3D_DRAW_TYPE_OBJECT;
		
						buffer->z = *( ( int * ) &distance_bias );
		
						buffer->object = object;
	
						if ( object->vp.y > middle_scene_slot_height )
						{
	
							insert_high_zbuffered_scene_slot_into_3d_scene ( buffer );
						}
						else
						{
	
							insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
						}

						//
						// Hack in here to pre-load any textures on the object
						//

//						if ( active_3d_environment->infrared_mode == RENDER_CLEAR )
						{
	
//							pre_render_3d_object ( object );
						}
					}
				}
			}

			break;
		}

		case OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT:
		{

			object_3d_instance
				*object;

			enum OBJECT_3D_VISIBILITY
				visibility;

			object = ( object_3d_instance * ) data;

			if ( ( !exclusive_3d_instance ) || ( exclusive_3d_instance == object ) )
			{

				//
				// Set the relative position & clip object
				//
	
				object->view_position = *relative_position;

				visibility = get_object_3d_instance_visibility ( object );
	
				if ( visibility != OBJECT_3D_NOT_VISIBLE )
				{
	
					buffer = get_3d_scene_slot ();
		
					if ( buffer )
					{
	
						distance_bias += object->view_position.z;
	
						buffer->type = OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT;
		
						buffer->z = *( ( int * ) &distance_bias );
		
						buffer->object = object;
	
						if ( object->vp.y > middle_scene_slot_height )
						{
	
							insert_high_zbuffered_scene_slot_into_3d_scene ( buffer );
						}
						else
						{
	
							insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
						}

						//
						// Hack in here to pre-load any textures on the object
						//

//						if ( active_3d_environment->infrared_mode == RENDER_CLEAR )
						{
	
//							pre_render_3d_object ( object );
						}
					}
				}
			}

			break;
		}

		default:
		{

			debug_fatal ( "Unknown object type in insert_object_3d_instance_into_scene" );

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_zbiased_coloured_object_into_3d_scene ( enum OBJECT_3D_DRAWING_TYPES type, void *data, real_colour colour, float distance_bias )
{

	scene_slot_drawing_list
		*buffer;

	number_of_objects_in_3d_scene++;

	switch ( type )
	{
	
		case OBJECT_3D_DRAW_TYPE_OBJECT_COLOURED:
		{

			object_3d_instance
				*object;

			enum OBJECT_3D_VISIBILITY
				visibility;

			object = ( object_3d_instance * ) data;

			//
			// Set the relative position & clip object
			//

			set_object_3d_instance_relative_position ( object );

			visibility = get_object_3d_instance_visibility ( object );

			if ( visibility != OBJECT_3D_NOT_VISIBLE )
			{

				buffer = get_3d_scene_slot ();
	
				if ( buffer )
				{

					distance_bias += object->view_position.z;

					buffer->type = OBJECT_3D_DRAW_TYPE_OBJECT_COLOURED;
	
					buffer->z = *( ( int * ) &distance_bias );
	
					buffer->object = object;

					buffer->colour = colour;

					if ( object->vp.y > middle_scene_slot_height )
					{

						insert_high_zbuffered_scene_slot_into_3d_scene ( buffer );
					}
					else
					{

						insert_low_zbuffered_scene_slot_into_3d_scene ( buffer );
					}
				}
			}

			break;
		}

		default:
		{

			debug_fatal ( "Unknown object type in insert_object_3d_instance_into_scene" );

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void insert_near_object_into_3d_scene ( enum OBJECT_3D_DRAWING_TYPES type, void *data )
{

	scene_slot_drawing_list
		*buffer;

	number_of_objects_in_3d_scene++;

	if ( number_of_objects_in_3d_scene == 1000 )
	{

		debug_log ( "Inserted 1000 objects in 3d scene" );
	}

	if ( number_of_objects_in_3d_scene == 2000 )
	{

		debug_log ( "Inserted 2000 objects in 3d scene" );
	}

	if ( number_of_objects_in_3d_scene == 4000 )
	{

		debug_log ( "Inserted 4000 objects in 3d scene" );
	}

	switch ( type )
	{
	
		case OBJECT_3D_DRAW_TYPE_OBJECT:
		{

			object_3d_instance
				*object;

			object = ( object_3d_instance * ) data;

			//
			// Set the relative position & clip object
			//

			set_object_3d_instance_relative_position ( object );

			buffer = get_3d_scene_slot ();

			if ( buffer )
			{

				buffer->type = OBJECT_3D_DRAW_TYPE_OBJECT;

				buffer->z = *( ( int * ) &object->view_position.z );

				buffer->object = object;

				insert_near_3d_scene_slot_into_3d_scene ( buffer );
			}

			break;
		}
	
		default:
		{

			debug_fatal ( "Unknown object type in insert_object_3d_instance_into_scene" );

			break;
		}
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_high_zbuffered_scene_slot_into_3d_scene ( scene_slot_drawing_list *object )
{

	if ( !last_high_zbuffered_scene_slot_insert_point )
	{

		high_zbuffered_scene_slot_sorted_list = object;

		high_zbuffered_scene_slot_sorted_list->pred = NULL;

		high_zbuffered_scene_slot_sorted_list->succ = NULL;

		last_high_zbuffered_scene_slot_insert_point = high_zbuffered_scene_slot_sorted_list;
	}
	else
	{

		if ( object->z < last_high_zbuffered_scene_slot_insert_point->z )
		{

			//
			// Search Forwards
			//

			while ( last_high_zbuffered_scene_slot_insert_point )
			{

				if ( object->z >= last_high_zbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert before this one.
					//

					object->pred = last_high_zbuffered_scene_slot_insert_point->pred;
					object->succ = last_high_zbuffered_scene_slot_insert_point;

					last_high_zbuffered_scene_slot_insert_point->pred = object;

					if ( object->pred )
					{

						object->pred->succ = object;
					}

					last_high_zbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_high_zbuffered_scene_slot_insert_point->succ )
				{

					last_high_zbuffered_scene_slot_insert_point = last_high_zbuffered_scene_slot_insert_point->succ;
				}
				else
				{

					//
					// Insert at end of list
					//

					last_high_zbuffered_scene_slot_insert_point->succ = object;

					object->pred = last_high_zbuffered_scene_slot_insert_point;

					object->succ = NULL;

					last_high_zbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
		else
		{

			//
			// Search Backwards
			//

			while ( last_high_zbuffered_scene_slot_insert_point )
			{

				if ( object->z <= last_high_zbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert after this one.
					//

					object->pred = last_high_zbuffered_scene_slot_insert_point;
					object->succ = last_high_zbuffered_scene_slot_insert_point->succ;

					last_high_zbuffered_scene_slot_insert_point->succ = object;

					if ( object->succ )
					{

						object->succ->pred = object;
					}

					last_high_zbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_high_zbuffered_scene_slot_insert_point->pred )
				{

					last_high_zbuffered_scene_slot_insert_point = last_high_zbuffered_scene_slot_insert_point->pred;
				}
				else
				{

					//
					// Insert at start of list
					//

					high_zbuffered_scene_slot_sorted_list->pred = object;

					object->succ = high_zbuffered_scene_slot_sorted_list;
					object->pred = NULL;

					high_zbuffered_scene_slot_sorted_list = object;

					last_high_zbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_high_nonzbuffered_scene_slot_into_3d_scene ( scene_slot_drawing_list *object )
{

	if ( !last_high_nonzbuffered_scene_slot_insert_point )
	{

		high_nonzbuffered_scene_slot_sorted_list = object;

		high_nonzbuffered_scene_slot_sorted_list->pred = NULL;

		high_nonzbuffered_scene_slot_sorted_list->succ = NULL;

		last_high_nonzbuffered_scene_slot_insert_point = high_nonzbuffered_scene_slot_sorted_list;
	}
	else
	{

		if ( object->z < last_high_nonzbuffered_scene_slot_insert_point->z )
		{

			//
			// Search Forwards
			//

			while ( last_high_nonzbuffered_scene_slot_insert_point )
			{

				if ( object->z >= last_high_nonzbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert before this one.
					//

					object->pred = last_high_nonzbuffered_scene_slot_insert_point->pred;
					object->succ = last_high_nonzbuffered_scene_slot_insert_point;

					last_high_nonzbuffered_scene_slot_insert_point->pred = object;

					if ( object->pred )
					{

						object->pred->succ = object;
					}

					last_high_nonzbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_high_nonzbuffered_scene_slot_insert_point->succ )
				{

					last_high_nonzbuffered_scene_slot_insert_point = last_high_nonzbuffered_scene_slot_insert_point->succ;
				}
				else
				{

					//
					// Insert at end of list
					//

					last_high_nonzbuffered_scene_slot_insert_point->succ = object;

					object->pred = last_high_nonzbuffered_scene_slot_insert_point;

					object->succ = NULL;

					last_high_nonzbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
		else
		{

			//
			// Search Backwards
			//

			while ( last_high_nonzbuffered_scene_slot_insert_point )
			{

				if ( object->z <= last_high_nonzbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert after this one.
					//

					object->pred = last_high_nonzbuffered_scene_slot_insert_point;
					object->succ = last_high_nonzbuffered_scene_slot_insert_point->succ;

					last_high_nonzbuffered_scene_slot_insert_point->succ = object;

					if ( object->succ )
					{

						object->succ->pred = object;
					}

					last_high_nonzbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_high_nonzbuffered_scene_slot_insert_point->pred )
				{

					last_high_nonzbuffered_scene_slot_insert_point = last_high_nonzbuffered_scene_slot_insert_point->pred;
				}
				else
				{

					//
					// Insert at start of list
					//

					high_nonzbuffered_scene_slot_sorted_list->pred = object;

					object->succ = high_nonzbuffered_scene_slot_sorted_list;
					object->pred = NULL;

					high_nonzbuffered_scene_slot_sorted_list = object;

					last_high_nonzbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_middle_scene_slot_into_3d_scene ( scene_slot_drawing_list *object )
{

	if ( !last_middle_scene_slot_insert_point )
	{

		middle_scene_slot_sorted_list = object;

		middle_scene_slot_sorted_list->pred = NULL;

		middle_scene_slot_sorted_list->succ = NULL;

		last_middle_scene_slot_insert_point = middle_scene_slot_sorted_list;
	}
	else
	{

		if ( object->z < last_middle_scene_slot_insert_point->z )
		{

			//
			// Search Forwards
			//

			while ( last_middle_scene_slot_insert_point )
			{

				if ( object->z >= last_middle_scene_slot_insert_point->z )
				{

					//
					// Insert before this one.
					//

					object->pred = last_middle_scene_slot_insert_point->pred;
					object->succ = last_middle_scene_slot_insert_point;

					last_middle_scene_slot_insert_point->pred = object;

					if ( object->pred )
					{

						object->pred->succ = object;
					}

					last_middle_scene_slot_insert_point = object;

					return;
				}

				if ( last_middle_scene_slot_insert_point->succ )
				{

					last_middle_scene_slot_insert_point = last_middle_scene_slot_insert_point->succ;
				}
				else
				{

					//
					// Insert at end of list
					//

					last_middle_scene_slot_insert_point->succ = object;

					object->pred = last_middle_scene_slot_insert_point;

					object->succ = NULL;

					last_middle_scene_slot_insert_point = object;

					return;
				}
			}
		}
		else
		{

			//
			// Search Backwards
			//

			while ( last_middle_scene_slot_insert_point )
			{

				if ( object->z <= last_middle_scene_slot_insert_point->z )
				{

					//
					// Insert after this one.
					//

					object->pred = last_middle_scene_slot_insert_point;
					object->succ = last_middle_scene_slot_insert_point->succ;

					last_middle_scene_slot_insert_point->succ = object;

					if ( object->succ )
					{

						object->succ->pred = object;
					}

					last_middle_scene_slot_insert_point = object;

					return;
				}

				if ( last_middle_scene_slot_insert_point->pred )
				{

					last_middle_scene_slot_insert_point = last_middle_scene_slot_insert_point->pred;
				}
				else
				{

					//
					// Insert at start of list
					//

					middle_scene_slot_sorted_list->pred = object;

					object->succ = middle_scene_slot_sorted_list;
					object->pred = NULL;

					middle_scene_slot_sorted_list = object;

					last_middle_scene_slot_insert_point = object;

					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_low_zbuffered_scene_slot_into_3d_scene ( scene_slot_drawing_list *object )
{

	if ( !last_low_zbuffered_scene_slot_insert_point )
	{

		low_zbuffered_scene_slot_sorted_list = object;

		low_zbuffered_scene_slot_sorted_list->pred = NULL;

		low_zbuffered_scene_slot_sorted_list->succ = NULL;

		last_low_zbuffered_scene_slot_insert_point = low_zbuffered_scene_slot_sorted_list;
	}
	else
	{

		if ( object->z < last_low_zbuffered_scene_slot_insert_point->z )
		{

			//
			// Search Forwards
			//

			while ( last_low_zbuffered_scene_slot_insert_point )
			{

				if ( object->z >= last_low_zbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert before this one.
					//

					object->pred = last_low_zbuffered_scene_slot_insert_point->pred;
					object->succ = last_low_zbuffered_scene_slot_insert_point;

					last_low_zbuffered_scene_slot_insert_point->pred = object;

					if ( object->pred )
					{

						object->pred->succ = object;
					}

					last_low_zbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_low_zbuffered_scene_slot_insert_point->succ )
				{

					last_low_zbuffered_scene_slot_insert_point = last_low_zbuffered_scene_slot_insert_point->succ;
				}
				else
				{

					//
					// Insert at end of list
					//

					last_low_zbuffered_scene_slot_insert_point->succ = object;

					object->pred = last_low_zbuffered_scene_slot_insert_point;

					object->succ = NULL;

					last_low_zbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
		else
		{

			//
			// Search Backwards
			//

			while ( last_low_zbuffered_scene_slot_insert_point )
			{

				if ( object->z <= last_low_zbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert after this one.
					//

					object->pred = last_low_zbuffered_scene_slot_insert_point;
					object->succ = last_low_zbuffered_scene_slot_insert_point->succ;

					last_low_zbuffered_scene_slot_insert_point->succ = object;

					if ( object->succ )
					{

						object->succ->pred = object;
					}

					last_low_zbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_low_zbuffered_scene_slot_insert_point->pred )
				{

					last_low_zbuffered_scene_slot_insert_point = last_low_zbuffered_scene_slot_insert_point->pred;
				}
				else
				{

					//
					// Insert at start of list
					//

					low_zbuffered_scene_slot_sorted_list->pred = object;

					object->succ = low_zbuffered_scene_slot_sorted_list;
					object->pred = NULL;

					low_zbuffered_scene_slot_sorted_list = object;

					last_low_zbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_low_nonzbuffered_scene_slot_into_3d_scene ( scene_slot_drawing_list *object )
{

	if ( !last_low_nonzbuffered_scene_slot_insert_point )
	{

		low_nonzbuffered_scene_slot_sorted_list = object;

		low_nonzbuffered_scene_slot_sorted_list->pred = NULL;

		low_nonzbuffered_scene_slot_sorted_list->succ = NULL;

		last_low_nonzbuffered_scene_slot_insert_point = low_nonzbuffered_scene_slot_sorted_list;
	}
	else
	{

		if ( object->z < last_low_nonzbuffered_scene_slot_insert_point->z )
		{

			//
			// Search Forwards
			//

			while ( last_low_nonzbuffered_scene_slot_insert_point )
			{

				if ( object->z >= last_low_nonzbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert before this one.
					//

					object->pred = last_low_nonzbuffered_scene_slot_insert_point->pred;
					object->succ = last_low_nonzbuffered_scene_slot_insert_point;

					last_low_nonzbuffered_scene_slot_insert_point->pred = object;

					if ( object->pred )
					{

						object->pred->succ = object;
					}

					last_low_nonzbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_low_nonzbuffered_scene_slot_insert_point->succ )
				{

					last_low_nonzbuffered_scene_slot_insert_point = last_low_nonzbuffered_scene_slot_insert_point->succ;
				}
				else
				{

					//
					// Insert at end of list
					//

					last_low_nonzbuffered_scene_slot_insert_point->succ = object;

					object->pred = last_low_nonzbuffered_scene_slot_insert_point;

					object->succ = NULL;

					last_low_nonzbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
		else
		{

			//
			// Search Backwards
			//

			while ( last_low_nonzbuffered_scene_slot_insert_point )
			{

				if ( object->z <= last_low_nonzbuffered_scene_slot_insert_point->z )
				{

					//
					// Insert after this one.
					//

					object->pred = last_low_nonzbuffered_scene_slot_insert_point;
					object->succ = last_low_nonzbuffered_scene_slot_insert_point->succ;

					last_low_nonzbuffered_scene_slot_insert_point->succ = object;

					if ( object->succ )
					{

						object->succ->pred = object;
					}

					last_low_nonzbuffered_scene_slot_insert_point = object;

					return;
				}

				if ( last_low_nonzbuffered_scene_slot_insert_point->pred )
				{

					last_low_nonzbuffered_scene_slot_insert_point = last_low_nonzbuffered_scene_slot_insert_point->pred;
				}
				else
				{

					//
					// Insert at start of list
					//

					low_nonzbuffered_scene_slot_sorted_list->pred = object;

					object->succ = low_nonzbuffered_scene_slot_sorted_list;
					object->pred = NULL;

					low_nonzbuffered_scene_slot_sorted_list = object;

					last_low_nonzbuffered_scene_slot_insert_point = object;

					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void insert_near_3d_scene_slot_into_3d_scene ( scene_slot_drawing_list *object )
{

	if ( !last_near_scene_slot_insert_point )
	{

		near_scene_slot_list = object;

		near_scene_slot_list->pred = NULL;

		near_scene_slot_list->succ = NULL;

		last_near_scene_slot_insert_point = object;
	}
	else
	{


		//
		// just insert at tail of list
		//

		last_near_scene_slot_insert_point->succ = object;

		object->pred = near_scene_slot_list;

		object->succ = NULL;

		last_near_scene_slot_insert_point = object;
	}
}
#endif


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_transparent_buffer_into_3d_scene ( scene_slot_drawing_list *object )
{

	//
	// This inserts the object into the non-zbuffered list, dependant on which list is currently being drawn
	//

	if ( current_scene_slot_list == high_zbuffered_scene_slot_sorted_list )
	{

		//
		// Insert into the high scene list
		//

		insert_high_nonzbuffered_scene_slot_into_3d_scene ( object );
	}
	else
	{

		//
		// Insert into the low scene list
		//

		insert_low_nonzbuffered_scene_slot_into_3d_scene ( object );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_scene ( void )
{

	//
	// Two cases here either we are above the middle layer, or below the middle layer.
	//

	set_up_tnl_hardware ();

	set_d3d_in_order_rendering ( FALSE );

	if ( visual_3d_vp->y > middle_scene_slot_height )
	{

		scene_slot_drawing_list
			*zbuffered_list,
			*zbuffered_insert,
			*nonzbuffered_list,
			*nonzbuffered_insert;

		//
		// Swap the layers around
		//

		zbuffered_list = high_zbuffered_scene_slot_sorted_list;
		zbuffered_insert = last_high_zbuffered_scene_slot_insert_point;
		nonzbuffered_list = high_nonzbuffered_scene_slot_sorted_list;
		nonzbuffered_insert = last_high_nonzbuffered_scene_slot_insert_point;

		high_zbuffered_scene_slot_sorted_list = low_zbuffered_scene_slot_sorted_list;
		last_high_zbuffered_scene_slot_insert_point = last_low_zbuffered_scene_slot_insert_point;
		high_nonzbuffered_scene_slot_sorted_list = low_nonzbuffered_scene_slot_sorted_list;
		last_high_nonzbuffered_scene_slot_insert_point = last_low_nonzbuffered_scene_slot_insert_point;

		low_zbuffered_scene_slot_sorted_list = zbuffered_list;
		last_low_zbuffered_scene_slot_insert_point = zbuffered_insert;
		low_nonzbuffered_scene_slot_sorted_list = nonzbuffered_list;
		last_low_nonzbuffered_scene_slot_insert_point = nonzbuffered_insert;
	}

	if ( high_zbuffered_scene_slot_sorted_list )
	{

		current_scene_slot_list = high_zbuffered_scene_slot_sorted_list;

		draw_normal_scene_objects ( high_zbuffered_scene_slot_sorted_list );
	}

	if ( high_nonzbuffered_scene_slot_sorted_list )
	{

		//
		// Set the transparency stuff on
		//

#if BATCH_DEFINED
		set_d3d_texture_batching ( FALSE );
#endif

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

		draw_transparent_scene_objects ( high_nonzbuffered_scene_slot_sorted_list );

		if ( active_3d_environment->fogmode == FOGMODE_OFF )
		{

			set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, TRUE, TRUE );
		}
		else
		{

			set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
		}
	}

	if ( middle_scene_slot_sorted_list )
	{
#if BATCH_DEFINED
		set_d3d_texture_batching ( FALSE );
#endif

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

		draw_normal_scene_objects ( middle_scene_slot_sorted_list );

		if ( active_3d_environment->fogmode == FOGMODE_OFF )
		{

			set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, TRUE, TRUE );
		}
		else
		{

			set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
		}
	}

	if ( low_zbuffered_scene_slot_sorted_list )
	{

		current_scene_slot_list = low_zbuffered_scene_slot_sorted_list;

#if BATCH_DEFINED
		set_d3d_texture_batching ( TRUE );
#endif

		draw_normal_scene_objects ( low_zbuffered_scene_slot_sorted_list );
	}

	if ( low_nonzbuffered_scene_slot_sorted_list )
	{

#if BATCH_DEFINED
		set_d3d_texture_batching ( FALSE );
#endif

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

		draw_transparent_scene_objects ( low_nonzbuffered_scene_slot_sorted_list );

		if ( active_3d_environment->fogmode == FOGMODE_OFF )
		{

			set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, TRUE, TRUE );
		}
		else
		{

			set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
		}
	}

#if 0
	//
	// Now render any "near" objects in the scene
	//

	if ( near_scene_slot_list )
	{

		draw_z_sorted_scene_objects ( near_scene_slot_list );
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_normal_scene_objects ( scene_slot_drawing_list *object_order )
{

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	if ( d3d_using_hardware_tnl )
	{

		set_up_tnl_hardware ();
	}

	while ( object_order )
	{

		switch ( object_order->type )
		{

			case	OBJECT_3D_DRAW_TYPE_OBJECT:
			{

				if ( d3d_using_hardware_tnl )
				{
	
					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, TRUE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, TRUE );
	
						draw_hardware_3d_object ( object_order->object, FALSE );
				}
				else
				{
	
					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

						draw_wbuffered_3d_object ( object_order->object, FALSE, FALSE );
				}

#if DRAW_OBJECT_BOUNDING_BOX

				draw_3d_object_bounding_box ( object_order->object );

#endif

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT:
			{

				if ( d3d_using_hardware_tnl )
				{
	
					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, TRUE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, TRUE );
	
					draw_hardware_zbuffered_3d_object ( object_order->object, FALSE, FALSE );
				}
				else
				{
	
					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );
	
					draw_zbuffered_3d_object ( object_order->object, FALSE, FALSE );
				}

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_OBJECT_COLOURED:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				if ( shadows_enabled )
				{

					if ( object_order->object->object_has_shadow )
					{
	
						draw_3d_object_shadow ( object_order->object );
					}
				}

				//
				// Recolour the lights
				//

				copy_and_recolour_current_3d_lights ( object_order->colour );

				draw_wbuffered_3d_object ( object_order->object, FALSE, TRUE );

				restore_uncoloured_current_3d_lights ();

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_TERRAIN_3D_OBJECT:
			{

				if ( d3d_using_hardware_tnl )
				{
	
					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, TRUE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, TRUE );
	
					draw_hardware_3d_object ( object_order->object, FALSE );
				}
				else
				{
	
					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );
	
					draw_wbuffered_3d_object ( object_order->object, FALSE, TRUE );
				}

				break;
			}

			case OBJECT_3D_DRAW_TYPE_POLYLINE:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				draw_3d_polyline ( &object_order->polyline );

				break;
			}


			case	OBJECT_3D_DRAW_TYPE_TERRAIN_3D_CLIPPED_SECTOR:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				if ( active_3d_environment->render_filter != RENDER_CLEAR )
				{
	
					draw_3d_terrain_3d_clipped_bw_sector ( object_order );
				}
				else
				{
	
					draw_3d_terrain_3d_clipped_sector ( object_order );
				}

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_TERRAIN_2D_CLIPPED_SECTOR:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				if ( active_3d_environment->render_filter != RENDER_CLEAR )
				{

					draw_3d_terrain_2d_clipped_bw_sector ( object_order );
				}
				else
				{

					draw_3d_terrain_2d_clipped_sector ( object_order );
				}

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_TERRAIN_UNCLIPPED_SECTOR:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				if ( active_3d_environment->render_filter != RENDER_CLEAR )
				{

					draw_3d_terrain_unclipped_bw_sector ( object_order );
				}
				else
				{

					draw_3d_terrain_unclipped_sector ( object_order );
				}

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_TERRAIN_3D_TREE_OBJECT:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				draw_3d_terrain_tree_object ( object_order );

				break;
			}

			// Casm 20MAY12 Cloud puffs
			case	OBJECT_3D_DRAW_TYPE_TERRAIN_3D_CLOUD_PUFF_OBJECT:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				draw_3d_terrain_cloud_puff_object ( object_order );

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_CLOUD_SECTOR:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				draw_3d_cloud_sector ( object_order );

				break;
			}

			default:
			{

				debug_fatal ( "Unknown object type in draw_3d_objects" );

				break;
			}
		}

		object_order = object_order->succ;
	}

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_transparent_scene_objects ( scene_slot_drawing_list *object_order )
{

	while ( object_order )
	{

		switch ( object_order->type )
		{

			case	OBJECT_3D_DRAW_TYPE_SPRITE:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );
//				set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, TRUE );
//				set_d3d_int_state ( D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_LINEAR );
//				set_3d_fogmode ( active_3d_environment, FOGMODE_ON_MANUAL );
//				set_3d_fog_distances ( active_3d_environment, 0.0, 10.0 );
//				{
//
//					rgb_colour
//						single_light_fog_colour;
//
//					single_light_fog_colour.r = 255;
//					single_light_fog_colour.g = 255;
//					single_light_fog_colour.b = 255;
//					single_light_fog_colour.a = 255;
//
//					set_3d_fog_colour ( active_3d_environment, single_light_fog_colour );
//				}
//
//				set_d3d_alpha_fog_zbuffer ( TRUE, TRUE, TRUE, FALSE );
				draw_3d_sprite ( &object_order->sprite );
//				set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_EXPLOSION:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );

				draw_3d_explosion ( &object_order->explosion );

				break;
			}

			case OBJECT_3D_DRAW_TYPE_SMOKE_TRAIL:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );

				draw_3d_smoke_trail ( &object_order->smoke_trail );

				break;
			}

			case OBJECT_3D_DRAW_TYPE_TRANSLUCENT_POLYGON_BUFFER:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

				draw_polygon_buffer ( object_order->translucent_buffer );

				break;
			}

			case OBJECT_3D_DRAW_TYPE_OBJECT_SHADOW:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

				draw_3d_object_shadow ( object_order->object );

				break;
			}

			case	OBJECT_3D_DRAW_TYPE_TERRAIN_3D_TREE_OBJECT:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

			
				if ( command_line_trees_fog == 1 || command_line_trees_fog == 2 && (1 / get_delta_time_average() >= (20 + 10 * !fog)) ) // trees fog thealx 130501
				{
					fog = TRUE;
					set_d3d_alpha_fog_zbuffer ( TRUE, TRUE, TRUE, FALSE );
					draw_3d_terrain_tree_object ( object_order ); 
					set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );
				}
				else
				{
					draw_3d_terrain_tree_object ( object_order ); 
					fog = FALSE;
				}

				break;
			}

			// Casm 20MAY12 Cloud puffs
			case	OBJECT_3D_DRAW_TYPE_TERRAIN_3D_CLOUD_PUFF_OBJECT:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
				set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

				draw_3d_terrain_cloud_puff_object ( object_order );

				break;
			}

			case OBJECT_3D_DRAW_TYPE_TRANSLUCENT_OBJECT:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

				if ( d3d_using_hardware_tnl )
				{

					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, TRUE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, TRUE );

					draw_3d_hardware_translucent_object ( object_order->translucent_surfaces );
				}
				else
				{

					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

						draw_3d_translucent_object ( object_order->translucent_surfaces );
				}

				break;
			}

			case OBJECT_3D_DRAW_TYPE_ZBUFFERED_TRANSLUCENT_OBJECT:
			{

				set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

				if ( d3d_using_hardware_tnl )
				{

					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, TRUE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, TRUE );

					draw_3d_hardware_zbuffered_translucent_object ( object_order->translucent_surfaces );
				}
				else
				{

					set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
					set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

					draw_3d_translucent_object ( object_order->translucent_surfaces );
				}

				break;
			}

			default:
			{

				debug_fatal ( "Unknown object type in draw_3d_objects" );

				break;
			}
		}

		object_order = object_order->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void draw_z_sorted_scene_objects ( scene_slot_drawing_list *object_order )
{

	set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, FALSE);
	set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	while ( object_order )
	{

		switch ( object_order->type )
		{

			case	OBJECT_3D_DRAW_TYPE_OBJECT:
			{

//				draw_z_sorted_3d_object ( object_order->object );

				break;
			}

			default:
			{

				debug_fatal ( "Invalid object type in near objects list" );

				break;
			}
		}

		object_order = object_order->succ;
	}

	set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, TRUE/*ddraw.use_z_buffer*/ );
	set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, TRUE/*ddraw.use_z_buffer*/ );
	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_3d_scene_objects ( void )
{

	//
	// Remove all the 3d objects in the visual drawing list
	//

	high_zbuffered_scene_slot_sorted_list = NULL;
	high_nonzbuffered_scene_slot_sorted_list = NULL;
	middle_scene_slot_sorted_list = NULL;
	low_zbuffered_scene_slot_sorted_list = NULL;
	low_nonzbuffered_scene_slot_sorted_list = NULL;
#if 0
	near_scene_slot_list = NULL;
#endif

	last_high_zbuffered_scene_slot_insert_point = NULL;
	last_high_nonzbuffered_scene_slot_insert_point = NULL;
	last_middle_scene_slot_insert_point = NULL;
	last_low_zbuffered_scene_slot_insert_point = NULL;
	last_low_nonzbuffered_scene_slot_insert_point = NULL;
#if 0
	last_near_scene_slot_insert_point = NULL;
#endif

	scene_slot_order_index = 0;

	//
	// Remove all the light sources from the visual light list
	//

	//
	// Reset translucent object surfaces
	//

	object_3d_transparent_surface_index = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_exclusive_instance ( object_3d_instance *instance )
{

	exclusive_3d_instance = instance;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_up_tnl_hardware ( void )
{
	matrix4x4
		m;

	D3DMATRIX
		d3d_matrix;

	//
	// Set lights
	//

	flush_triangle_primitives ();

	flush_line_primitives ();

	if ( current_3d_lights )
	{

		D3DLIGHT7
			light;

		light_3d_source
			*this_light;

		int
			count;

		this_light = current_3d_lights;

		count = 0;

		while ( this_light )
		{
	
			memset ( &light, 0, sizeof ( light ) );
	
			light.dltType = D3DLIGHT_DIRECTIONAL;
	
			light.dcvDiffuse.r = this_light->colour.red;
			light.dcvDiffuse.g = this_light->colour.green;
			light.dcvDiffuse.b = this_light->colour.blue;

			if ( count == 0 )
			{

				light.dcvAmbient.r = ambient_3d_light.colour.red;
				light.dcvAmbient.g = ambient_3d_light.colour.green;
				light.dcvAmbient.b = ambient_3d_light.colour.blue;

				if (active_3d_environment->render_filter == RENDER_INFRARED) // FLIR objects HW
					light.dcvAmbient.r = light.dcvAmbient.g = light.dcvAmbient.b = 1.0;
			}
			else
			{
	
				light.dcvAmbient.r = 0;
				light.dcvAmbient.g = 0;
				light.dcvAmbient.b = 0;
			}
	
			light.dcvSpecular.r = this_light->colour.red;
			light.dcvSpecular.g = this_light->colour.green;
			light.dcvSpecular.b = this_light->colour.blue;
	
			light.dvDirection.x = -this_light->light_direction.x;
			light.dvDirection.y = -this_light->light_direction.y;
			light.dvDirection.z = -this_light->light_direction.z;

			f3d_set_light(count, &light);

			f3d_light_enable(count, TRUE);
	
			this_light = this_light->succ;

			count++;
		}

		for ( ; count < 4; count++ )
		{
			f3d_light_enable(count, FALSE);
		}
	}

	//
	// Set view ( viewer's ) transformation matrix
	//

	{

		vec3d
			rel;

		rel.x = visual_3d_vp->attitude[0][0] * visual_3d_vp->x + visual_3d_vp->attitude[0][1] * visual_3d_vp->y + visual_3d_vp->attitude[0][2] * visual_3d_vp->z;
		rel.y = visual_3d_vp->attitude[1][0] * visual_3d_vp->x + visual_3d_vp->attitude[1][1] * visual_3d_vp->y + visual_3d_vp->attitude[1][2] * visual_3d_vp->z;
		rel.z = visual_3d_vp->attitude[2][0] * visual_3d_vp->x + visual_3d_vp->attitude[2][1] * visual_3d_vp->y + visual_3d_vp->attitude[2][2] * visual_3d_vp->z;
	
		m[0][0] = visual_3d_vp->attitude[0][0];
		m[0][1] = visual_3d_vp->attitude[1][0];
		m[0][2] = visual_3d_vp->attitude[2][0];
		m[1][0] = visual_3d_vp->attitude[0][1];
		m[1][1] = visual_3d_vp->attitude[1][1];
		m[1][2] = visual_3d_vp->attitude[2][1];
		m[2][0] = visual_3d_vp->attitude[0][2];
		m[2][1] = visual_3d_vp->attitude[1][2];
		m[2][2] = visual_3d_vp->attitude[2][2];
		m[0][3] = 0;
		m[1][3] = 0;
		m[2][3] = 0;

//		if ( use_zbuffer_view )
		{

			m[3][0] = 0;
			m[3][1] = 0;
			m[3][2] = 0;
		}
/*		else
		{
	
			m[3][0] = -rel.x;
			m[3][1] = -rel.y;
			m[3][2] = -rel.z;
		}*/
		m[3][3] = 1;

		memcpy ( &d3d_matrix, m, sizeof ( D3DMATRIX ) );
	
		f3d_set_transform ( D3DTRANSFORMSTATE_VIEW, &d3d_matrix );
	}

	//
	// Set projection ( perspective ) matrix
	//

	{

		float
			near_plane,
			far_plane,
			view_width_angle,
			view_height_angle;

		near_plane = 1.0;
		far_plane = 10000.0;

		view_width_angle = rad ( 59.99 );
		view_height_angle = rad ( 46.82 );

		if ( active_3d_environment )
		{

			near_plane = active_3d_environment->hither_distance;
			far_plane = active_3d_environment->yonder_distance;

			view_width_angle = active_3d_environment->width_view_angle;
			view_height_angle = active_3d_environment->height_view_angle;
		}

		get_4d_projection_matrix ( m, near_plane, far_plane, view_width_angle, view_height_angle );
	
		memcpy ( &d3d_matrix, m, sizeof ( D3DMATRIX ) );
	
		f3d_set_transform ( D3DTRANSFORMSTATE_PROJECTION, &d3d_matrix );
	}

	//
	// Set default material
	//

	set_d3d_material_default ();

	//
	// Setup the Z buffering properly
	//

	if ( active_3d_environment )
	{

		//
		// Create & set the viewport for the device2 interface.
		//

		D3DVIEWPORT7
			viewdata;

		//
		// Set up the viewport values for initial values
		//

		viewdata.dwX = active_3d_environment->clip_xmin;
		viewdata.dwY = active_3d_environment->clip_ymin;

		viewdata.dwWidth = active_3d_environment->clip_xmax - active_3d_environment->clip_xmin + 0.01;
		viewdata.dwHeight = active_3d_environment->clip_ymax - active_3d_environment->clip_ymin + 0.01;
		
		viewdata.dvMinZ = 0.0;	//active_3d_environment->zbuffer_z_maximum_value;
		viewdata.dvMaxZ = 1.0;	//active_3d_environment->zbuffer_z_minimum_value;

		f3d_set_viewport ( &viewdata );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

