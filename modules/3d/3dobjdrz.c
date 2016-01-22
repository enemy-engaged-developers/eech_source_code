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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MANUAL_VIEWS 0

#define FORCE_LIGHTMAP_MIPMAPPING 1

#define CURRENT_3D_OBJECT_FACE_FACING(X) (transformed_3d_normal_visibilities[current_object_3d_face_normal_list->point])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, vec3d *position, int infrared_override );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3d
	old_visual_3d_vp;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_zbuffered_3d_object ( object_3d_instance *obj, int object_is_flat, int infrared_override )
{

	int
		object_number;

	light_3d_source
		*light;

	vec3d
		object_camera_position,
		object_camera_direction,
		object_unit_pos;

	polygon_buffer
		*translucent_sorted_buffer;

	object_3d_scene_database_entry
		*scene;

	viewpoint
		old_object_vp;

	//
	// Set the scene pointer
	//

	scene = &objects_3d_scene_database[obj->object_number];

	//
	// Set up the texture animations for this object.
	//

	initialise_object_texture_animations ( obj );

	//
	// Set up the object drawing global variables
	//

	object_3d_points_current_base = 0;
	object_3d_object_current_base = 0;
	object_3d_light_3d_current_base = 0;

	current_3d_object_is_flat = object_is_flat;

	current_object_3d_light_maps_enabled = obj->object_internal_lighting;

	//
	// Get the object's position relative to the camera
	//

	current_object_3d_relative_position = &obj->view_position;

	{

		float
			fog_intensity;

		int
			ifog_intensity;

		fog_intensity = get_fog_distance_value ( current_object_3d_relative_position->z );

		asm_convert_float_to_int ( fog_intensity, &ifog_intensity );

		set_d3d_fog_face_intensity ( ifog_intensity );
	}

	//
	// Set the main objects' scaling values
	//

	object_3d_scale.x = obj->relative_scale.x;
	object_3d_scale.y = obj->relative_scale.y;
	object_3d_scale.z = obj->relative_scale.z;

	//
	// Set the object dissolve variables
	//

	current_object_3d_dissolve_value = obj->object_dissolve_value;
	current_object_3d_dissolve_factor = current_object_3d_dissolve_value;
	current_object_3d_dissolve_factor /= 255.0;

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

	rotation_3d[0][0] = ( obj->vp.xv.x * visual_3d_vp->xv.x + obj->vp.xv.y * visual_3d_vp->xv.y + obj->vp.xv.z * visual_3d_vp->xv.z );
	rotation_3d[0][1] = ( obj->vp.xv.x * visual_3d_vp->yv.x + obj->vp.xv.y * visual_3d_vp->yv.y + obj->vp.xv.z * visual_3d_vp->yv.z );
	rotation_3d[0][2] = ( obj->vp.xv.x * visual_3d_vp->zv.x + obj->vp.xv.y * visual_3d_vp->zv.y + obj->vp.xv.z * visual_3d_vp->zv.z );

	rotation_3d[1][0] = ( obj->vp.yv.x * visual_3d_vp->xv.x + obj->vp.yv.y * visual_3d_vp->xv.y + obj->vp.yv.z * visual_3d_vp->xv.z );
	rotation_3d[1][1] = ( obj->vp.yv.x * visual_3d_vp->yv.x + obj->vp.yv.y * visual_3d_vp->yv.y + obj->vp.yv.z * visual_3d_vp->yv.z );
	rotation_3d[1][2] = ( obj->vp.yv.x * visual_3d_vp->zv.x + obj->vp.yv.y * visual_3d_vp->zv.y + obj->vp.yv.z * visual_3d_vp->zv.z );

	rotation_3d[2][0] = ( obj->vp.zv.x * visual_3d_vp->xv.x + obj->vp.zv.y * visual_3d_vp->xv.y + obj->vp.zv.z * visual_3d_vp->xv.z );
	rotation_3d[2][1] = ( obj->vp.zv.x * visual_3d_vp->yv.x + obj->vp.zv.y * visual_3d_vp->yv.y + obj->vp.zv.z * visual_3d_vp->yv.z );
	rotation_3d[2][2] = ( obj->vp.zv.x * visual_3d_vp->zv.x + obj->vp.zv.y * visual_3d_vp->zv.y + obj->vp.zv.z * visual_3d_vp->zv.z );

	rotation_3d[0][0] *= object_3d_scale.x;
	rotation_3d[1][0] *= object_3d_scale.y;
	rotation_3d[2][0] *= object_3d_scale.z;

	rotation_3d[0][1] *= object_3d_scale.x;
	rotation_3d[1][1] *= object_3d_scale.y;
	rotation_3d[2][1] *= object_3d_scale.z;

	rotation_3d[0][2] *= object_3d_scale.x;
	rotation_3d[1][2] *= object_3d_scale.y;
	rotation_3d[2][2] *= object_3d_scale.z;

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	old_object_vp.position = obj->vp.position;

	{

		vec3d
			v1,
			v2;

		multiply_matrix3x3_vec3d ( &v1, visual_3d_vp->attitude, current_object_3d_relative_position );
//		v1.x = -v1.x;
//		v1.y = -v1.y;
//		v1.z = -v1.z;

		obj->vp.x = v1.x;
		obj->vp.y = v1.y;
		obj->vp.z = v1.z;
//		obj->vp.x = visual_3d_vp->x + v1.x;
//		obj->vp.y = visual_3d_vp->y + v1.y;
//		obj->vp.z = visual_3d_vp->z + v1.z;

		v2.x = ( v1.x * obj->vp.xv.x );
		v2.x += ( v1.y * obj->vp.xv.y );
		v2.x += ( v1.z * obj->vp.xv.z );

		v2.y = ( v1.x * obj->vp.yv.x );
		v2.y += ( v1.y * obj->vp.yv.y );
		v2.y += ( v1.z * obj->vp.yv.z );

		v2.z = ( v1.x * obj->vp.zv.x );
		v2.z += ( v1.y * obj->vp.zv.y );
		v2.z += ( v1.z * obj->vp.zv.z );

		object_unit_pos.x = -v2.x;
		object_unit_pos.y = -v2.y;
		object_unit_pos.z = -v2.z;

		normalise_any_3d_vector ( &object_unit_pos );

		current_object_3d_unit_position = &object_unit_pos;

	}

	//
	// Set the camera to ( 0, 0, 0 )
	//

	old_visual_3d_vp = visual_3d_vp->position;

	//
	// Get the object number
	//

#if DEBUG_MANUAL_VIEWS

	object_number = get_object_approximation_number ( obj->object_number, 0, &object_3d_approximation_level );

#else

	if ( object_3d_perform_lod_calculations )
	{

		object_number = get_object_approximation_number ( obj->object_number, current_object_3d_relative_position->z, &object_3d_approximation_level );
	}
	else
	{

		object_number = get_object_approximation_number ( obj->object_number, 0, &object_3d_approximation_level );
	}

#endif

	//
	// Rotate the light source vector to be relative to the object.
	//

	light = generate_relative_lights ( &obj->vp, current_object_3d_unit_position, current_3d_lights );

	{

		vec3d
			rel_pos;

		//
		// Calculate the relative camera position in the object viewspace
		//

		rel_pos.x = visual_3d_vp->x - obj->vp.x;
		rel_pos.y = visual_3d_vp->y - obj->vp.y;
		rel_pos.z = visual_3d_vp->z - obj->vp.z;

		object_camera_position.x = ( rel_pos.x * obj->vp.attitude[0][0] + rel_pos.y * obj->vp.attitude[0][1] + rel_pos.z * obj->vp.attitude[0][2] );
		object_camera_position.y = ( rel_pos.x * obj->vp.attitude[1][0] + rel_pos.y * obj->vp.attitude[1][1] + rel_pos.z * obj->vp.attitude[1][2] );
		object_camera_position.z = ( rel_pos.x * obj->vp.attitude[2][0] + rel_pos.y * obj->vp.attitude[2][1] + rel_pos.z * obj->vp.attitude[2][2] );

		object_camera_direction.x = ( visual_3d_vp->zv.x * obj->vp.attitude[0][0] + visual_3d_vp->zv.y * obj->vp.attitude[1][0] + visual_3d_vp->zv.z * obj->vp.attitude[2][0] );
		object_camera_direction.y = ( visual_3d_vp->zv.x * obj->vp.attitude[0][1] + visual_3d_vp->zv.y * obj->vp.attitude[1][1] + visual_3d_vp->zv.z * obj->vp.attitude[2][1] );
		object_camera_direction.z = ( visual_3d_vp->zv.x * obj->vp.attitude[0][2] + visual_3d_vp->zv.y * obj->vp.attitude[1][2] + visual_3d_vp->zv.z * obj->vp.attitude[2][2] );
	}


	//
	//	Set up this objects' object info structure
	//

	object_3d_object_base[object_3d_object_current_base].lights = light;

	object_3d_object_base[object_3d_object_current_base].camera_position = object_camera_position;

	object_3d_object_base[object_3d_object_current_base].camera_direction = object_camera_direction;

	object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;

	object_3d_object_base[object_3d_object_current_base].object_number = object_number;

	object_3d_object_base[object_3d_object_current_base].object_vp = &obj->vp;

	current_object_3d_object_base = &object_3d_object_base[object_3d_object_current_base];

	//
	// Set up the face sorting variables
	//

	current_object_3d_translucent_surfaces = NULL;

	translucent_sorted_buffer = get_translucent_sorted_polygon_buffer ();

	//
	// Reset the temporary buffered faces
	//

	reset_temporary_buffered_translucent_polygons ();

	//
	// Now start transforming etc
	//

	if ( objects_3d_data[object_number].number_of_points )
	{

		int
			object_outcode;

		if ( !get_object_3d_outcode ( object_number, current_object_3d_relative_position, &object_outcode ) )
		{

			illuminate_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );

			if ( object_outcode )
			{

				if ( current_3d_object_is_flat )
				{


					transform_flat_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );
				}
				else
				{

					transform_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );
				}
			}
			else
			{

				if ( current_3d_object_is_flat )
				{

					transform_unclipped_flat_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );
				}
				else
				{

					transform_unclipped_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );
				}
			}

			if ( object_outcode )
			{

				if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
				{

					draw_3d_object_clipped_faces ( object_number );
				}
				else
				{

					draw_3d_object_untextured_clipped_faces ( object_number );
				}
			}
			else
			{

				if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
				{

					draw_3d_object_unclipped_faces ( object_number );
				}
				else
				{

					draw_3d_object_untextured_unclipped_faces ( object_number );
				}
			}
		}
	}

	//
	// Recurse down any sub objects
	//

	if ( scene->number_of_sub_objects )
	{

		int
			count;

		if ( obj->sub_objects )
		{

			for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
			{

				if (	( obj->sub_objects[count].visible_object ) &&
						( scene->sub_objects[count].sub_object_approximation_in_level <= object_3d_approximation_level ) &&
						( scene->sub_objects[count].sub_object_approximation_out_level >= object_3d_approximation_level ) )
				{

					draw_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count], &obj->vp, current_object_3d_relative_position, infrared_override );
				}
			}
		}
		else
		{

			for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
			{

				if (	( scene->sub_objects[count].default_visibility ) &&
						( scene->sub_objects[count].sub_object_approximation_in_level <= object_3d_approximation_level ) &&
						( scene->sub_objects[count].sub_object_approximation_out_level >= object_3d_approximation_level ) )
				{

					draw_sub_object ( NULL, &scene->sub_objects[count], &obj->vp, current_object_3d_relative_position, infrared_override );
				}
			}
		}
	}

	//
	// If there are any temporary tranlucent polygons, draw them now
	//

	if ( get_number_of_temporary_translucent_polygons () )
	{

		//
		// Set the translucent rendering mode - and turn off specular highlighting
		//

		set_d3d_int_state ( D3DRS_SPECULARENABLE, FALSE );

		if ( d3d_transparency_enabled )
		{

			draw_temporary_translucent_polygons ();
		}
		else
		{

			set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

			draw_temporary_translucent_polygons ();

			set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
		}
	}

	if ( current_object_3d_translucent_surfaces )
	{

//		draw_3d_translucent_object ( current_object_3d_translucent_surfaces );
		if ( obj->requires_immediate_render )
		{
		}
		else
		{

			scene_slot_drawing_list
				*buffer;

			//
			// Insert surface list into renderer
			//

			buffer = get_3d_scene_slot ();

			if ( buffer )
			{

				buffer->type = OBJECT_3D_DRAW_TYPE_TRANSLUCENT_OBJECT;

				buffer->z = *( ( int * ) &obj->view_position );

				buffer->translucent_surfaces = current_object_3d_translucent_surfaces;

				insert_transparent_buffer_into_3d_scene ( buffer );
			}
		}
	}

	//
	// Now finish sorting the translucent polygons.
	//

	if ( finalise_translucent_sorted_polygon_buffer ( translucent_sorted_buffer ) )
	{

		if ( obj->requires_immediate_render )
		{

			if ( d3d_transparency_enabled )
			{

				draw_polygon_buffer ( translucent_sorted_buffer );
			}
			else
			{

				set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

				draw_polygon_buffer ( translucent_sorted_buffer );

				set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
			}

			remove_translucent_polygon_buffer ( translucent_sorted_buffer );
		}
		else
		{

			scene_slot_drawing_list
				*buffer;

			//
			// There were translucencies there, insert this buffer into the scene list
			//

			buffer = get_3d_scene_slot ();

			if ( buffer )
			{

				buffer->type = OBJECT_3D_DRAW_TYPE_TRANSLUCENT_POLYGON_BUFFER;

				buffer->z = *( ( int * ) &obj->view_position );

				buffer->translucent_buffer = translucent_sorted_buffer;

				insert_transparent_buffer_into_3d_scene ( buffer );
			}
		}
	}

	if ( ( obj->object_sprite_lights ) && ( scene->number_of_sprite_lights ) )
	{

		object_3d_sprite
			sprite;

		int
			count;

		for ( count = 0; count < scene->number_of_sprite_lights; count++ )
		{

			vec3d
				position;

			position.x = scene->sprite_lights[count].position.x * obj->vp.attitude[0][0] +
								scene->sprite_lights[count].position.y * obj->vp.attitude[1][0] +
								scene->sprite_lights[count].position.z * obj->vp.attitude[2][0];

			position.y = scene->sprite_lights[count].position.x * obj->vp.attitude[0][1] +
								scene->sprite_lights[count].position.y * obj->vp.attitude[1][1] +
								scene->sprite_lights[count].position.z * obj->vp.attitude[2][1];

			position.z = scene->sprite_lights[count].position.x * obj->vp.attitude[0][2] +
								scene->sprite_lights[count].position.y * obj->vp.attitude[1][2] +
								scene->sprite_lights[count].position.z * obj->vp.attitude[2][2];

			position.x += obj->vp.position.x;
			position.y += obj->vp.position.y;
			position.z += obj->vp.position.z;

			sprite.position = position;
			sprite.radius = scene->sprite_lights[count].scale.x * 4;
			sprite.red = scene->sprite_lights[count].colour.red;
			sprite.green = scene->sprite_lights[count].colour.green;
			sprite.blue = scene->sprite_lights[count].colour.blue;
			sprite.additive = TRUE;
			//DEBUG// THIS LINE WAS COMMENTED OUT
			sprite.texture = system_textures[TEXTURE_INDEX_FLARE001];
			//DEBUG// THIS LINE WAS COMMENTED OUT

			insert_zbiased_object_into_3d_scene ( OBJECT_3D_DRAW_TYPE_SPRITE, &sprite, 0 );
		}
	}

	obj->vp.position = old_object_vp.position;

	visual_3d_vp->position = old_visual_3d_vp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, vec3d *position, int infrared_override )
{

	int
		count,
		object_number,
		relative_dissolve;

	float
		old_current_object_3d_dissolve_factor;

	matrix3x3
		relative_attitude,
		temp_matrix;

	vec3d
		object_camera_position,
		object_camera_direction,
		scaled_relative_position,
		temp_scale,
		object_unit_pos,
		sub_pos,
		relative_position,
		relative_scale,
		*old_current_object_3d_relative_position;

	float
		relative_heading,
		relative_pitch,
		relative_roll;

	light_3d_source
		*light;

	viewpoint
		vp;

	//
	// We no longer need the lights to be used for all the objects, so just reset the stats!
	//

	object_3d_points_current_base = 0;

	object_3d_object_current_base = 0;

	object_3d_light_3d_current_base = 0;

	//
	// Get the positions & object number
	//

	if ( obj )
	{

		relative_position = obj->relative_position;
		relative_scale = obj->relative_scale;
		relative_heading = obj->relative_heading;
		relative_pitch = obj->relative_pitch;
		relative_roll = obj->relative_roll;
		relative_dissolve = obj->object_dissolve_value;
	}
	else
	{

		relative_position.x = scene->keyframes[0].x;
		relative_position.y = scene->keyframes[0].y;
		relative_position.z = scene->keyframes[0].z;
		relative_scale.x = scene->keyframes[0].scale_x;
		relative_scale.y = scene->keyframes[0].scale_y;
		relative_scale.z = scene->keyframes[0].scale_z;
		relative_heading = scene->keyframes[0].heading;
		relative_pitch = scene->keyframes[0].pitch;
		relative_roll = scene->keyframes[0].roll;
		relative_dissolve = scene->object_dissolve * 255.0;
	}

	object_number = scene->index;

	//
	// Set the object dissolve variables
	//

	{

		float
			tmp;

		int
			itmp;

		old_current_object_3d_dissolve_factor = current_object_3d_dissolve_factor;

		current_object_3d_dissolve_value = relative_dissolve;	//obj->object_dissolve_value;

		tmp = current_object_3d_dissolve_value;
		tmp /= 255.0;

		current_object_3d_dissolve_factor *= tmp;

		asm_convert_float_to_int ( current_object_3d_dissolve_factor * 255.0, &itmp );

		current_object_3d_dissolve_value = itmp;
	}

	//
	// Calculate the object's position relative to the viewer.
	//
	// NOTE:
	//		BECAUSE THIS USES THE ROTATION_3D MATRIX, IT TAKES INTO ACCOUNT THE PARENT'S SCALE
	//

	sub_pos.x = ( ( relative_position.x * rotation_3d[0][0] ) +
					  ( relative_position.y * rotation_3d[1][0] ) +
					  ( relative_position.z * rotation_3d[2][0] ) );
	sub_pos.y = ( ( relative_position.x * rotation_3d[0][1] ) +
					  ( relative_position.y * rotation_3d[1][1] ) +
					  ( relative_position.z * rotation_3d[2][1] ) );
	sub_pos.z = ( ( relative_position.x * rotation_3d[0][2] ) +
					  ( relative_position.y * rotation_3d[1][2] ) +
					  ( relative_position.z * rotation_3d[2][2] ) );

	sub_pos.x += position->x;
	sub_pos.y += position->y;
	sub_pos.z += position->z;

	old_current_object_3d_relative_position = current_object_3d_relative_position;

	current_object_3d_relative_position = &sub_pos;

	//
	// Calculate the object's real world position
	//

	scaled_relative_position.x = relative_position.x * object_3d_scale.x;
	scaled_relative_position.y = relative_position.y * object_3d_scale.y;
	scaled_relative_position.z = relative_position.z * object_3d_scale.z;

	vp.x = (	( scaled_relative_position.x * parent_viewpoint->xv.x ) +
				( scaled_relative_position.y * parent_viewpoint->yv.x ) +
				( scaled_relative_position.z * parent_viewpoint->zv.x ) );

	vp.y = (	( scaled_relative_position.x * parent_viewpoint->xv.y ) +
				( scaled_relative_position.y * parent_viewpoint->yv.y ) +
				( scaled_relative_position.z * parent_viewpoint->zv.y ) );

	vp.z = (	( scaled_relative_position.x * parent_viewpoint->xv.z ) +
				( scaled_relative_position.y * parent_viewpoint->yv.z ) +
				( scaled_relative_position.z * parent_viewpoint->zv.z ) );

	vp.x += parent_viewpoint->x;
	vp.y += parent_viewpoint->y;
	vp.z += parent_viewpoint->z;

	//
	//	Store the rotation matrix, so when we go back to the parent, other sub objects can inherit the matrix safely
	//

	memcpy ( temp_matrix, rotation_3d, sizeof ( matrix3x3 ) );

	//
	// Store the scaling before we trash it
	//

	memcpy ( &temp_scale, &object_3d_scale, sizeof ( vec3d ) );

	//
	// Alter the scaling according to this object's scale
	//

	object_3d_scale.x *= relative_scale.x;
	object_3d_scale.y *= relative_scale.y;
	object_3d_scale.z *= relative_scale.z;

	//
	// Compute the sub object's relative attitude matrix
	//

	get_3d_transformation_matrix ( relative_attitude, relative_heading, -relative_pitch, -relative_roll );

	//
	// Calculate the sub object's rotation matrix, to transform its 3d points relative to the parent object.
	//

	vp.xv.x = ( ( relative_attitude[0][0] * parent_viewpoint->xv.x ) + ( relative_attitude[0][1] * parent_viewpoint->yv.x ) + ( relative_attitude[0][2] * parent_viewpoint->zv.x ) );
	vp.xv.y = ( ( relative_attitude[0][0] * parent_viewpoint->xv.y ) + ( relative_attitude[0][1] * parent_viewpoint->yv.y ) + ( relative_attitude[0][2] * parent_viewpoint->zv.y ) );
	vp.xv.z = ( ( relative_attitude[0][0] * parent_viewpoint->xv.z ) + ( relative_attitude[0][1] * parent_viewpoint->yv.z ) + ( relative_attitude[0][2] * parent_viewpoint->zv.z ) );

	vp.yv.x = ( ( relative_attitude[1][0] * parent_viewpoint->xv.x ) + ( relative_attitude[1][1] * parent_viewpoint->yv.x ) + ( relative_attitude[1][2] * parent_viewpoint->zv.x ) );
	vp.yv.y = ( ( relative_attitude[1][0] * parent_viewpoint->xv.y ) + ( relative_attitude[1][1] * parent_viewpoint->yv.y ) + ( relative_attitude[1][2] * parent_viewpoint->zv.y ) );
	vp.yv.z = ( ( relative_attitude[1][0] * parent_viewpoint->xv.z ) + ( relative_attitude[1][1] * parent_viewpoint->yv.z ) + ( relative_attitude[1][2] * parent_viewpoint->zv.z ) );

	vp.zv.x = ( ( relative_attitude[2][0] * parent_viewpoint->xv.x ) + ( relative_attitude[2][1] * parent_viewpoint->yv.x ) + ( relative_attitude[2][2] * parent_viewpoint->zv.x ) );
	vp.zv.y = ( ( relative_attitude[2][0] * parent_viewpoint->xv.y ) + ( relative_attitude[2][1] * parent_viewpoint->yv.y ) + ( relative_attitude[2][2] * parent_viewpoint->zv.y ) );
	vp.zv.z = ( ( relative_attitude[2][0] * parent_viewpoint->xv.z ) + ( relative_attitude[2][1] * parent_viewpoint->yv.z ) + ( relative_attitude[2][2] * parent_viewpoint->zv.z ) );

	//
	// Calculate the main matrix to transform the points to the screen
	//

	rotation_3d[0][0] = ( ( vp.xv.x * visual_3d_vp->xv.x ) + ( vp.xv.y * visual_3d_vp->xv.y ) + ( vp.xv.z * visual_3d_vp->xv.z ) );
	rotation_3d[0][1] = ( ( vp.xv.x * visual_3d_vp->yv.x ) + ( vp.xv.y * visual_3d_vp->yv.y ) + ( vp.xv.z * visual_3d_vp->yv.z ) );
	rotation_3d[0][2] = ( ( vp.xv.x * visual_3d_vp->zv.x ) + ( vp.xv.y * visual_3d_vp->zv.y ) + ( vp.xv.z * visual_3d_vp->zv.z ) );

	rotation_3d[1][0] = ( ( vp.yv.x * visual_3d_vp->xv.x ) + ( vp.yv.y * visual_3d_vp->xv.y ) + ( vp.yv.z * visual_3d_vp->xv.z ) );
	rotation_3d[1][1] = ( ( vp.yv.x * visual_3d_vp->yv.x ) + ( vp.yv.y * visual_3d_vp->yv.y ) + ( vp.yv.z * visual_3d_vp->yv.z ) );
	rotation_3d[1][2] = ( ( vp.yv.x * visual_3d_vp->zv.x ) + ( vp.yv.y * visual_3d_vp->zv.y ) + ( vp.yv.z * visual_3d_vp->zv.z ) );

	rotation_3d[2][0] = ( ( vp.zv.x * visual_3d_vp->xv.x ) + ( vp.zv.y * visual_3d_vp->xv.y ) + ( vp.zv.z * visual_3d_vp->xv.z ) );
	rotation_3d[2][1] = ( ( vp.zv.x * visual_3d_vp->yv.x ) + ( vp.zv.y * visual_3d_vp->yv.y ) + ( vp.zv.z * visual_3d_vp->yv.z ) );
	rotation_3d[2][2] = ( ( vp.zv.x * visual_3d_vp->zv.x ) + ( vp.zv.y * visual_3d_vp->zv.y ) + ( vp.zv.z * visual_3d_vp->zv.z ) );

	//
	// Scale the rotation matrix
	//

	rotation_3d[0][0] *= object_3d_scale.x;
	rotation_3d[1][0] *= object_3d_scale.y;
	rotation_3d[2][0] *= object_3d_scale.z;

	rotation_3d[0][1] *= object_3d_scale.x;
	rotation_3d[1][1] *= object_3d_scale.y;
	rotation_3d[2][1] *= object_3d_scale.z;

	rotation_3d[0][2] *= object_3d_scale.x;
	rotation_3d[1][2] *= object_3d_scale.y;
	rotation_3d[2][2] *= object_3d_scale.z;

	if ( object_number )
	{

		//
		// Calculate the relative camera position in the object viewspace
		//

		{

			vec3d
				rel_pos;

			rel_pos.x = visual_3d_vp->x - vp.x;
			rel_pos.y = visual_3d_vp->y - vp.y;
			rel_pos.z = visual_3d_vp->z - vp.z;

			object_camera_position.x = ( rel_pos.x * vp.attitude[0][0] + rel_pos.y * vp.attitude[0][1] + rel_pos.z * vp.attitude[0][2] );
			object_camera_position.y = ( rel_pos.x * vp.attitude[1][0] + rel_pos.y * vp.attitude[1][1] + rel_pos.z * vp.attitude[1][2] );
			object_camera_position.z = ( rel_pos.x * vp.attitude[2][0] + rel_pos.y * vp.attitude[2][1] + rel_pos.z * vp.attitude[2][2] );

			object_camera_direction.x = ( visual_3d_vp->zv.x * vp.attitude[0][0] + visual_3d_vp->zv.y * vp.attitude[1][0] + visual_3d_vp->zv.z * vp.attitude[2][0] );
			object_camera_direction.y = ( visual_3d_vp->zv.x * vp.attitude[0][1] + visual_3d_vp->zv.y * vp.attitude[1][1] + visual_3d_vp->zv.z * vp.attitude[2][1] );
			object_camera_direction.z = ( visual_3d_vp->zv.x * vp.attitude[0][2] + visual_3d_vp->zv.y * vp.attitude[1][2] + visual_3d_vp->zv.z * vp.attitude[2][2] );
		}

		//
		// Calculate the vector from the object to the viewpoint, in the object's view system
		//

		{

			float
				x,
				y,
				z;

			x = ( ( visual_3d_vp->x - vp.x ) * vp.xv.x );
			x += ( ( visual_3d_vp->y - vp.y ) *  vp.xv.y );
			x += ( ( visual_3d_vp->z - vp.z ) *  vp.xv.z );

			y = ( ( visual_3d_vp->x - vp.x ) * vp.yv.x );
			y += ( ( visual_3d_vp->y - vp.y ) *  vp.yv.y );
			y += ( ( visual_3d_vp->z - vp.z ) *  vp.yv.z );

			z = ( ( visual_3d_vp->x - vp.x ) * vp.zv.x );
			z += ( ( visual_3d_vp->y - vp.y ) *  vp.zv.y );
			z += ( ( visual_3d_vp->z - vp.z ) *  vp.zv.z );

			object_unit_pos.x = x;
			object_unit_pos.y = y;
			object_unit_pos.z = z;

			normalise_any_3d_vector ( &object_unit_pos );

			current_object_3d_unit_position = &object_unit_pos;
		}

		//
		// Rotate the light source vector to be relative to the object.
		//

		light = generate_relative_lights ( &vp, current_object_3d_unit_position, current_3d_lights );

		object_3d_object_base[object_3d_object_current_base].lights = light;

		//
		//	Set up this objects' object info structure
		//

		object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;
		object_3d_object_base[object_3d_object_current_base].camera_position = object_camera_position;
		object_3d_object_base[object_3d_object_current_base].camera_direction = object_camera_direction;
		object_3d_object_base[object_3d_object_current_base].object_vp = &vp;
		object_3d_object_base[object_3d_object_current_base].object_number = object_number;

		current_object_3d_object_base = &object_3d_object_base[object_3d_object_current_base];

		if ( objects_3d_data[object_number].number_of_points )
		{

			int
				object_outcode;

			//
			// Setup the objects scaling information
			//

			if ( !get_object_3d_outcode ( object_number, current_object_3d_relative_position, &object_outcode ) )
			{

				illuminate_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );

				if ( object_outcode )
				{

					if ( current_3d_object_is_flat )
					{

						transform_flat_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );
					}
					else
					{

						transform_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );
					}
				}
				else
				{

					if ( current_3d_object_is_flat )
					{

						transform_unclipped_flat_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );
					}
					else
					{

						transform_unclipped_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );
					}
				}

				//
				// Render the faces now.
				//

				if ( object_outcode )
				{

					if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
					{

						draw_3d_object_clipped_faces ( object_number );
					}
					else
					{

						draw_3d_object_untextured_clipped_faces ( object_number );
					}
				}
				else
				{

					if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
					{

						draw_3d_object_unclipped_faces ( object_number );
					}
					else
					{

						draw_3d_object_untextured_unclipped_faces ( object_number );
					}
				}
			}
		}
	}

	//
	// Recurse down any sub objects
	//

	if ( scene->number_of_sub_objects )
	{

		if ( ( obj ) && ( obj->sub_objects ) )
		{

			for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
			{

				if (	( obj->sub_objects[count].visible_object ) &&
						( scene->sub_objects[count].sub_object_approximation_in_level <= object_3d_approximation_level ) &&
						( scene->sub_objects[count].sub_object_approximation_out_level >= object_3d_approximation_level ) )
				{

					draw_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count], &vp, current_object_3d_relative_position, infrared_override );
				}
			}
		}
		else
		{

			for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
			{

				if (	( scene->sub_objects[count].default_visibility ) &&
						( scene->sub_objects[count].sub_object_approximation_in_level <= object_3d_approximation_level ) &&
						( scene->sub_objects[count].sub_object_approximation_out_level >= object_3d_approximation_level ) )
				{

					draw_sub_object ( NULL, &scene->sub_objects[count], &vp, current_object_3d_relative_position, infrared_override );
				}
			}
		}
	}

	//
	// Restore object dissolve
	//

	{

		int
			itmp;

		current_object_3d_dissolve_factor = old_current_object_3d_dissolve_factor;

		asm_convert_float_to_int ( current_object_3d_dissolve_factor * 255, &itmp );

		current_object_3d_dissolve_value = itmp;
	}

	//
	// Restore the object rotation matrix
	//

	memcpy ( rotation_3d, temp_matrix, sizeof ( matrix3x3 ) );

	memcpy ( &object_3d_scale, &temp_scale, sizeof ( vec3d ) );

	current_object_3d_relative_position = old_current_object_3d_relative_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
