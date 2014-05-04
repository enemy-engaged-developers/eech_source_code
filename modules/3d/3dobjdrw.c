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

#include	"3d.h"
#include "cmndline.h" // trees_fog thealx 130430

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MANUAL_VIEWS 0

#define FORCE_LIGHTMAP_MIPMAPPING 1

#define CURRENT_3D_OBJECT_FACE_FACING(X) (transformed_3d_normal_visibilities[current_object_3d_face_normal_list->point])

#define ALWAYS_SPECULAR_RENDER 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, vec3d *position, int infrared_override );

static void add_transparent_surface ( int clipped );

int OLD_CURRENT_3D_OBJECT_FACE_FACING ( void );

static int scene_index;

static int fog = FALSE;

void draw_3d_translucent_surface_clipped_faces ( translucent_object_surface *surface );

void draw_3d_translucent_surface_unclipped_faces ( translucent_object_surface *surface );

void draw_3d_translucent_surface_clipped_reflection_faces ( translucent_object_surface *surface );

void draw_3d_translucent_surface_unclipped_reflection_faces ( translucent_object_surface *surface );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

translucent_object_surface
	*current_object_3d_translucent_surfaces;

vec3d
	*current_object_3d_relative_position,
	*current_object_3d_unit_position;

matrix3x3
	object_to_eye_attitude;

int
	previous_object_3d_transparent_surface_index;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_3d_object ( object_3d_instance *obj, int object_is_flat, int infrared_override )
{

	int
		object_number;

	light_3d_source
		*light;

	vec3d
		object_camera_position,
		object_camera_direction,
		object_unit_pos;

	object_3d_scene_database_entry
		*scene;

	set_d3d_texture_batching ( TRUE );

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

	//
	// Set the scene pointer
	//

	scene = &objects_3d_scene_database[obj->object_number];
	
	scene_index = obj->object_number;

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

	current_object_3d_diffuse_factor = obj->object_diffuse_value / 255.0;

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

	{

		float
			x,
			y,
			z;

		x = ( ( visual_3d_vp->x - obj->vp.x ) * obj->vp.xv.x );
		x += ( ( visual_3d_vp->y - obj->vp.y ) *  obj->vp.xv.y );
		x += ( ( visual_3d_vp->z - obj->vp.z ) *  obj->vp.xv.z );

		y = ( ( visual_3d_vp->x - obj->vp.x ) * obj->vp.yv.x );
		y += ( ( visual_3d_vp->y - obj->vp.y ) *  obj->vp.yv.y );
		y += ( ( visual_3d_vp->z - obj->vp.z ) *  obj->vp.yv.z );

		z = ( ( visual_3d_vp->x - obj->vp.x ) * obj->vp.zv.x );
		z += ( ( visual_3d_vp->y - obj->vp.y ) *  obj->vp.zv.y );
		z += ( ( visual_3d_vp->z - obj->vp.z ) *  obj->vp.zv.z );

		object_unit_pos.x = -x;
		object_unit_pos.y = -y;
		object_unit_pos.z = -z;

		normalise_any_3d_vector ( &object_unit_pos );

		current_object_3d_unit_position = &object_unit_pos;
	}

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

	previous_object_3d_transparent_surface_index = object_3d_transparent_surface_index;

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

#if !ALWAYS_SPECULAR_RENDER
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
#endif

		if ( d3d_transparency_enabled )
		{

			draw_temporary_translucent_polygons ();
		}
		else
		{

			set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

			draw_temporary_translucent_polygons ();

			if ( active_3d_environment->fogmode == FOGMODE_OFF )
			{

				set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, TRUE, TRUE );
			}
			else
			{

				set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
			}
		}
	}

	if ( current_object_3d_translucent_surfaces )
	{

		if ( obj->requires_immediate_render )
		{

			if ( d3d_transparency_enabled )
			{

				draw_3d_translucent_object ( current_object_3d_translucent_surfaces );
			}
			else
			{

				set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );
				
				draw_3d_translucent_object ( current_object_3d_translucent_surfaces );

				if ( active_3d_environment->fogmode == FOGMODE_OFF )
				{

				set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, TRUE, TRUE );
				}
				else
				{

				set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
				}
			}

			object_3d_transparent_surface_index = previous_object_3d_transparent_surface_index;
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

	if ( ( obj->object_sprite_lights ) && ( scene->number_of_sprite_lights ) && ( object_3d_sprite_flare_texture ) )
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
			sprite.texture = object_3d_sprite_flare_texture;

			insert_zbiased_object_into_3d_scene ( OBJECT_3D_DRAW_TYPE_SPRITE, &sprite, 0 );
		}
	}
	
	scene_index = FALSE;
	current_object_3d_diffuse_factor = 1;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, vec3d *position, int infrared_override )
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

			object_unit_pos.x = -x;
			object_unit_pos.y = -y;
			object_unit_pos.z = -z;

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

void draw_3d_object_clipped_faces ( int object_number )
{
	int
		number_of_surface_points,
		faces_left,
		surfaces_left;

	surfaces_left = objects_3d_data[object_number].number_of_surfaces;

	current_object_3d_faces = objects_3d_data[object_number].faces;
	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;
	current_object_3d_transformed_normals = &transformed_3d_normals[object_3d_points_current_base];

	current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;
	current_object_3d_surface_point_texture_list = objects_3d_data[object_number].surface_texture_points;
	current_object_3d_surface_point_normal_list = objects_3d_data[object_number].surface_point_normals;

	for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
	{
		number_of_surface_points = current_object_3d_surface->number_of_points;
		if ( number_of_surface_points == 0 )
		{
			number_of_surface_points = 256;
		}

		if ( ( current_object_3d_surface->additive ) || ( current_object_3d_surface->translucent ) || current_object_3d_dissolve_value < 200 )
		{
			add_transparent_surface ( TRUE );
		}
		else
		{
			zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
			current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

			if ( current_object_3d_surface->textured )
			{
				if ( current_object_3d_surface->texture_animation )
				{
					int
						frame;

					frame = texture_animations[current_object_3d_surface->texture_index].current_frame;
					current_object_3d_texture = system_textures[ texture_animations[current_object_3d_surface->texture_index].texture_indices[frame] ];
				}
				else
				{
					current_object_3d_texture = system_textures[current_object_3d_surface->texture_index];
				}
				if ( current_object_3d_texture->contains_alpha )
				{
					add_transparent_surface ( TRUE );
				}
				else
				{
					current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
					current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
					current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
					current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;

					reset_deferred_state_changes ();

#if ALWAYS_SPECULAR_RENDER
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif

					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

					set_deferred_d3d_texture ( 0, current_object_3d_texture );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

					if ( current_object_3d_surface->has_luminosity_texture )
					{
						if ( current_object_3d_surface->luminosity_texture_animation )
						{
							int
								frame;

							frame = texture_animations[current_object_3d_surface->luminosity_texture_index].current_frame;
							current_object_3d_luminosity_texture = system_textures[ texture_animations[current_object_3d_surface->luminosity_texture_index].texture_indices[frame] ];
						}
						else
						{
							current_object_3d_luminosity_texture = system_textures[current_object_3d_surface->luminosity_texture_index];
						}

						if ( current_object_3d_surface->luminosity_texture_wrapped_u )	{ current_object_3d_luminosity_texture_u_address = D3DTADDRESS_WRAP; }
						else																				{ current_object_3d_luminosity_texture_u_address = D3DTADDRESS_CLAMP; }

						if ( current_object_3d_surface->luminosity_texture_wrapped_v )	{ current_object_3d_luminosity_texture_v_address = D3DTADDRESS_WRAP; }
						else																				{ current_object_3d_luminosity_texture_v_address = D3DTADDRESS_CLAMP; }

						if ( current_object_3d_surface->luminosity_texture_filtered )	{ current_object_3d_luminosity_texture_filter = D3DTFG_LINEAR; }
						else																				{ current_object_3d_luminosity_texture_filter = D3DTFG_POINT; }

		#if ( FORCE_LIGHTMAP_MIPMAPPING )
						if ( current_object_3d_surface->luminosity_texture_mipmapped )	{ current_object_3d_luminosity_texture_mipmap = D3DTFP_POINT; }
						else																				{ current_object_3d_luminosity_texture_mipmap = D3DTFP_POINT; }
		#else
						if ( current_object_3d_surface->luminosity_texture_mipmapped )	{ current_object_3d_luminosity_texture_mipmap = D3DTFP_POINT; }
						else																				{ current_object_3d_luminosity_texture_mipmap = D3DTFP_NONE; }
		#endif

						if ( current_object_3d_surface->smoothed )
						{
							for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
							{
								if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, 0, &current_object_3d_outcode ) )
								{
									if ( current_object_3d_outcode == 0 )
									{
										wrender_unclipped_3d_object_gouraud_textured_lightmap_polygon ( current_object_3d_faces );
									}
									else
									{
										wrender_clipped_3d_object_gouraud_textured_lightmap_polygon ( current_object_3d_faces );
									}
								}

								current_object_3d_point_list += current_object_3d_faces->number_of_points;
								current_object_3d_faces++;
							}
						}
						else
						{
							if ( current_object_3d_surface->polygons )
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
									{
										if ( current_object_3d_outcode == 0 )
										{
											wrender_unclipped_3d_object_textured_lightmap_polygon ( current_object_3d_faces );
										}
										else
										{
											wrender_clipped_3d_object_textured_lightmap_polygon ( current_object_3d_faces );
										}
									}

									current_object_3d_face_normal_list++;
									current_object_3d_point_list += current_object_3d_faces->number_of_points;
									current_object_3d_faces++;
								}
							}
							else
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									if ( d3d_textured_lines )
									{
										if ( !outcode_3d_object_surface_polygon ( 2, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
										{
											if ( current_object_3d_outcode == 0 )
											{
												wrender_unclipped_3d_object_textured_line ();
											}
											else
											{
												wrender_clipped_3d_object_textured_line ();
											}
										}
									}
									current_object_3d_point_list += 2;
								}
							}
						}
					}
					else
					{
						if ( current_object_3d_surface->smoothed )
						{
							for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
							{
								if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
								{
									if ( current_object_3d_outcode == 0 )
									{
										if ( current_object_3d_specular )
										{
											wrender_unclipped_3d_object_gouraud_textured_polygon ( current_object_3d_faces );
										}
										else
										{
											wrender_unclipped_3d_object_gouraud_textured_nospecular_polygon ( current_object_3d_faces );
										}
									}
									else
									{
										wrender_clipped_3d_object_gouraud_textured_polygon ( current_object_3d_faces );
									}
								}

								current_object_3d_point_list += current_object_3d_faces->number_of_points;
								current_object_3d_faces++;
							}
						}
						else
						{
							if ( current_object_3d_surface->polygons )
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
									{
										if ( current_object_3d_outcode == 0 )
										{
											wrender_unclipped_3d_object_textured_polygon ( current_object_3d_faces );
										}
										else
										{
											wrender_clipped_3d_object_textured_polygon ( current_object_3d_faces );
										}
									}
									current_object_3d_face_normal_list++;
									current_object_3d_point_list += current_object_3d_faces->number_of_points;
									current_object_3d_faces++;
								}
							}
							else
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									if ( d3d_textured_lines )
									{
										if ( !outcode_3d_object_surface_polygon ( 2, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
										{
											if ( current_object_3d_outcode == 0 )
											{
												wrender_unclipped_3d_object_textured_line ();
											}
											else
											{
												wrender_clipped_3d_object_textured_line ();
											}
										}
									}
									current_object_3d_point_list += 2;
								}
							}
						}
					}
				}
			}
			else
			{
				reset_deferred_state_changes ();

#if ALWAYS_SPECULAR_RENDER
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif

				set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

				if ( current_object_3d_surface->smoothed )
				{
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
						{
							if ( current_object_3d_outcode == 0 )
							{
								wrender_unclipped_3d_object_gouraud_polygon ( current_object_3d_faces );
							}
							else
							{
								wrender_clipped_3d_object_gouraud_polygon ( current_object_3d_faces );
							}
						}

						current_object_3d_point_list += current_object_3d_faces->number_of_points;
						current_object_3d_faces++;
					}
				}
				else
				{
					if ( current_object_3d_surface->polygons )
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
							{
								if ( current_object_3d_outcode == 0 )
								{
									wrender_unclipped_3d_object_polygon ( current_object_3d_faces );
								}
								else
								{
									wrender_clipped_3d_object_polygon ( current_object_3d_faces );
								}
							}

							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
					}
					else
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							if ( !outcode_3d_object_surface_polygon ( 2, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
							{
								if ( current_object_3d_outcode == 0 )
								{
									wrender_unclipped_3d_object_plain_line ();
								}
								else
								{
									wrender_clipped_3d_object_plain_line ();
								}
							}
							current_object_3d_point_list += 2;
						}
					}
				}
			}
		}

		current_object_3d_surface_point_list += number_of_surface_points;

		if ( current_object_3d_surface->smoothed )
		{
			current_object_3d_surface_point_normal_list += number_of_surface_points;
		}

		if ( current_object_3d_surface->textured )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}

		if ( current_object_3d_surface->has_luminosity_texture )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}

		current_object_3d_surface++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_object_unclipped_faces ( int object_number )
{
	int
		number_of_surface_points,
		faces_left,
		surfaces_left,
		vertices_used;

	surfaces_left = objects_3d_data[object_number].number_of_surfaces;

	current_object_3d_faces = objects_3d_data[object_number].faces;
	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;
	current_object_3d_transformed_normals = &transformed_3d_normals[object_3d_points_current_base];

	current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;
	current_object_3d_surface_point_texture_list = objects_3d_data[object_number].surface_texture_points;
	current_object_3d_surface_point_normal_list = objects_3d_data[object_number].surface_point_normals;

	for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
	{
		number_of_surface_points = current_object_3d_surface->number_of_points;
		if ( number_of_surface_points == 0 )
		{
			number_of_surface_points = 256;
		}

		if ( ( current_object_3d_surface->additive ) || ( current_object_3d_surface->translucent ) || current_object_3d_dissolve_value < 200 )
		{
			add_transparent_surface ( FALSE );
		}
		else
		{
			zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
			current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

			if ( current_object_3d_surface->textured )
			{
				if ( current_object_3d_surface->texture_animation )
				{
					int
						frame;

					frame = texture_animations[current_object_3d_surface->texture_index].current_frame;

					current_object_3d_texture = system_textures[ texture_animations[current_object_3d_surface->texture_index].texture_indices[frame] ];
				}
				else
				{
					current_object_3d_texture = system_textures[current_object_3d_surface->texture_index];
				}

				if ( current_object_3d_texture->contains_alpha )
				{
					add_transparent_surface ( FALSE );
				}
				else
				{
					current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
					current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
					current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
					current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;

					reset_deferred_state_changes ();

#if ALWAYS_SPECULAR_RENDER
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif

					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

					set_deferred_d3d_texture ( 0, current_object_3d_texture );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
					set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

					if ( current_object_3d_surface->has_luminosity_texture )
					{
						if ( current_object_3d_surface->luminosity_texture_animation )
						{
							int
								frame;

							frame = texture_animations[current_object_3d_surface->luminosity_texture_index].current_frame;
							current_object_3d_luminosity_texture = system_textures[ texture_animations[current_object_3d_surface->luminosity_texture_index].texture_indices[frame] ];
						}
						else
						{
							current_object_3d_luminosity_texture = system_textures[current_object_3d_surface->luminosity_texture_index];
						}

						if ( current_object_3d_surface->luminosity_texture_wrapped_u )	{ current_object_3d_luminosity_texture_u_address = D3DTADDRESS_WRAP; }
						else																				{ current_object_3d_luminosity_texture_u_address = D3DTADDRESS_CLAMP; }

						if ( current_object_3d_surface->luminosity_texture_wrapped_v )	{ current_object_3d_luminosity_texture_v_address = D3DTADDRESS_WRAP; }
						else																				{ current_object_3d_luminosity_texture_v_address = D3DTADDRESS_CLAMP; }

						if ( current_object_3d_surface->luminosity_texture_filtered )	{ current_object_3d_luminosity_texture_filter = D3DTFG_LINEAR; }
						else																				{ current_object_3d_luminosity_texture_filter = D3DTFG_POINT; }

#if ( FORCE_LIGHTMAP_MIPMAPPING )
						if ( current_object_3d_surface->luminosity_texture_mipmapped )	{ current_object_3d_luminosity_texture_mipmap = D3DTFP_POINT; }
						else																				{ current_object_3d_luminosity_texture_mipmap = D3DTFP_POINT; }
#else
						if ( current_object_3d_surface->luminosity_texture_mipmapped )	{ current_object_3d_luminosity_texture_mipmap = D3DTFP_POINT; }
						else																				{ current_object_3d_luminosity_texture_mipmap = D3DTFP_NONE; }
#endif

						if ( current_object_3d_surface->smoothed )
						{
							for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
							{
								wrender_unclipped_3d_object_gouraud_textured_lightmap_polygon ( current_object_3d_faces );
								current_object_3d_point_list += current_object_3d_faces->number_of_points;
								current_object_3d_faces++;
							}
						}
						else
						{
							if ( current_object_3d_surface->polygons )
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									wrender_unclipped_3d_object_textured_lightmap_polygon ( current_object_3d_faces );
									current_object_3d_face_normal_list++;
									current_object_3d_point_list += current_object_3d_faces->number_of_points;
									current_object_3d_faces++;
								}
							}
							else
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									if ( d3d_textured_lines )
									{
										wrender_unclipped_3d_object_textured_line ();
									}
									current_object_3d_point_list += 2;
								}
							}
						}
					}
					else
					{
						commit_deferred_state_changes ();

						current_object_3d_surface_vertices = get_d3d_new_vertices_points_address ( number_of_surface_points, &current_object_3d_surface_point_index );

						memset ( current_object_3d_surface_vertices_used, 0, number_of_surface_points );

						if ( current_object_3d_surface->smoothed )
						{
							for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
							{
								add_triangle_fan_primitive_to_buffer ( current_object_3d_faces->number_of_points, current_object_3d_surface_point_index, ( unsigned char * ) current_object_3d_point_list );

								current_object_3d_point_list += current_object_3d_faces->number_of_points;
								current_object_3d_faces++;
							}

							if ( current_object_3d_specular )
							{
								wrender_3d_object_gouraud_textured_surface ( number_of_surface_points );
							}
							else
							{
								wrender_3d_object_gouraud_textured_nospecular_surface ( number_of_surface_points );
							}
						}
						else
						{
							if ( current_object_3d_surface->polygons )
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									real_colour
										colour,
										specular_colour;

									int
										point_index;

									get_textured_surface_face_colour ( &colour, &specular_colour );
									add_triangle_fan_primitive_to_buffer ( current_object_3d_faces->number_of_points, current_object_3d_surface_point_index, ( unsigned char * ) current_object_3d_point_list );
									for ( point_index = 0; point_index < current_object_3d_faces->number_of_points; point_index++ )
									{
										int
											index;

										index = current_object_3d_point_list[point_index].point;
										current_object_3d_surface_vertices[index].color = colour.colour;
										current_object_3d_surface_vertices[index].specular = specular_colour.colour;
									}
									current_object_3d_face_normal_list++;
									current_object_3d_point_list += current_object_3d_faces->number_of_points;
									current_object_3d_faces++;
								}

								wrender_3d_object_textured_surface ( number_of_surface_points );
							}
							else
							{
								for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
								{
									if ( d3d_textured_lines )
									{
										wrender_unclipped_3d_object_textured_line ();
									}
									current_object_3d_point_list += 2;
								}
							}
						}
					}
				}
			}
			else
			{

				reset_deferred_state_changes ();

#if ALWAYS_SPECULAR_RENDER
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

				//
				// Set up the vertex buffer for this set of triangles / vertices
				//

				commit_deferred_state_changes ();

				current_object_3d_surface_vertices = get_d3d_new_vertices_points_address ( number_of_surface_points, &current_object_3d_surface_point_index );

				memset ( current_object_3d_surface_vertices_used, 0, number_of_surface_points );

				vertices_used = FALSE;

				if ( current_object_3d_surface->smoothed )
				{
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						add_triangle_fan_primitive_to_buffer ( current_object_3d_faces->number_of_points, current_object_3d_surface_point_index, ( unsigned char * ) current_object_3d_point_list );
						current_object_3d_point_list += current_object_3d_faces->number_of_points;
						current_object_3d_faces++;
					}
					wrender_3d_object_gouraud_surface ( number_of_surface_points );
				}
				else
				{
					if ( current_object_3d_surface->polygons )
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							real_colour
								colour,
								specular_colour;

							int
								point_index;

							get_surface_face_colour ( &colour, &specular_colour );
							add_triangle_fan_primitive_to_buffer ( current_object_3d_faces->number_of_points, current_object_3d_surface_point_index, ( unsigned char * ) current_object_3d_point_list );
							for ( point_index = 0; point_index < current_object_3d_faces->number_of_points; point_index++ )
							{
								int
									index;

								index = current_object_3d_point_list[point_index].point;
								current_object_3d_surface_vertices[index].color = colour.colour;
								current_object_3d_surface_vertices[index].specular = specular_colour.colour;
							}

							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
						wrender_3d_object_surface ( number_of_surface_points );
					}
					else
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							wrender_unclipped_3d_object_plain_line ();
							current_object_3d_point_list += 2;
						}
					}
				}
			}
		}

		current_object_3d_surface_point_list += number_of_surface_points;

		if ( current_object_3d_surface->smoothed )
		{
			current_object_3d_surface_point_normal_list += number_of_surface_points;
		}

		if ( current_object_3d_surface->textured )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}

		if ( current_object_3d_surface->has_luminosity_texture )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}

		current_object_3d_surface++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_object_untextured_clipped_faces ( int object_number )
{
	int
		number_of_surface_points,
		faces_left,
		surfaces_left;

	surfaces_left = objects_3d_data[object_number].number_of_surfaces;

	current_object_3d_faces = objects_3d_data[object_number].faces;
	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;
	current_object_3d_transformed_normals = &transformed_3d_normals[object_3d_points_current_base];

	current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;
	current_object_3d_surface_point_texture_list = objects_3d_data[object_number].surface_texture_points;
	current_object_3d_surface_point_normal_list = objects_3d_data[object_number].surface_point_normals;

	for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
	{
		int
			skip_surface;

		number_of_surface_points = current_object_3d_surface->number_of_points;
		if ( number_of_surface_points == 0 )
		{
			number_of_surface_points = 256;
		}

		skip_surface = FALSE;

		if ( current_object_3d_surface->translucent )
		{
			skip_surface = TRUE;
		}

		if ( current_object_3d_surface->textured )
		{
			if ( current_object_3d_surface->texture_animation )
			{
				int
					frame;

				frame = texture_animations[current_object_3d_surface->texture_index].current_frame;
				current_object_3d_texture = system_textures[ texture_animations[current_object_3d_surface->texture_index].texture_indices[frame] ];
			}
			else
			{
				current_object_3d_texture = system_textures[current_object_3d_surface->texture_index];
			}

			if ( current_object_3d_texture->contains_alpha )
			{
				skip_surface = TRUE;
			}
		}

		if ( !skip_surface )
		{
			reset_deferred_state_changes ();

			zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
			current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

#if ALWAYS_SPECULAR_RENDER
			set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
			set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif
			set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

			if ( current_object_3d_surface->additive )
			{
				current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
				current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
				current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
				current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;

				set_deferred_d3d_texture ( 0, current_object_3d_texture );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

				set_deferred_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
				set_deferred_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
			}
			else
			{
				set_deferred_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
			}

			if ( current_object_3d_surface->smoothed )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
					{
						if ( current_object_3d_outcode == 0 )
						{
							wrender_unclipped_3d_object_gouraud_white_polygon ( current_object_3d_faces );
						}
						else
						{
							wrender_clipped_3d_object_gouraud_white_polygon ( current_object_3d_faces );
						}
					}
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				if ( current_object_3d_surface->polygons )
				{
					if ( current_object_3d_surface->additive )
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
							{
								if ( current_object_3d_outcode == 0 )
								{
									wrender_unclipped_3d_object_white_textured_polygon ( current_object_3d_faces );
								}
								else
								{
									wrender_clipped_3d_object_white_textured_polygon ( current_object_3d_faces );
								}
							}

							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
					}
					else
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
							{
								if ( current_object_3d_outcode == 0 )
								{
									wrender_unclipped_3d_object_white_polygon ( current_object_3d_faces );
								}
								else
								{
									wrender_clipped_3d_object_white_polygon ( current_object_3d_faces );
								}
							}

							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
					}
				}
				else
				{
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( !outcode_3d_object_surface_polygon ( 2, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
						{
							if ( current_object_3d_outcode == 0 )
							{
								wrender_unclipped_3d_object_plain_white_line ();
							}
							else
							{
								wrender_clipped_3d_object_plain_white_line ();
							}
						}
						current_object_3d_point_list += 2;
					}
				}
			}
		}
		else
		{
			//
			// Move on through the point list & normals list
			//

			if ( current_object_3d_surface->polygons )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( !current_object_3d_surface->smoothed )
					{
						current_object_3d_face_normal_list++;
					}
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				current_object_3d_point_list += 2 * current_object_3d_surface->number_of_faces;
			}
		}

		current_object_3d_surface_point_list += number_of_surface_points;
		if ( current_object_3d_surface->smoothed )
		{
			current_object_3d_surface_point_normal_list += number_of_surface_points;
		}
		if ( current_object_3d_surface->textured )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}
		if ( current_object_3d_surface->has_luminosity_texture )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}
		current_object_3d_surface++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_object_untextured_unclipped_faces ( int object_number )
{
	int
		number_of_surface_points,
		faces_left,
		surfaces_left;

	surfaces_left = objects_3d_data[object_number].number_of_surfaces;

	current_object_3d_faces = objects_3d_data[object_number].faces;
	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;
	current_object_3d_transformed_normals = &transformed_3d_normals[object_3d_points_current_base];

	current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;
	current_object_3d_surface_point_texture_list = objects_3d_data[object_number].surface_texture_points;
	current_object_3d_surface_point_normal_list = objects_3d_data[object_number].surface_point_normals;

	for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
	{
		int
			skip_surface;

		number_of_surface_points = current_object_3d_surface->number_of_points;
		if ( number_of_surface_points == 0 )
		{
			number_of_surface_points = 256;
		}

		skip_surface = FALSE;

		if ( current_object_3d_surface->translucent )
		{
			skip_surface = TRUE;
		}

		if ( current_object_3d_surface->textured )
		{
			if ( current_object_3d_surface->texture_animation )
			{
				int
					frame;

				frame = texture_animations[current_object_3d_surface->texture_index].current_frame;
				current_object_3d_texture = system_textures[ texture_animations[current_object_3d_surface->texture_index].texture_indices[frame] ];
			}
			else
			{
				current_object_3d_texture = system_textures[current_object_3d_surface->texture_index];
			}

			if ( current_object_3d_texture->contains_alpha )
			{
				skip_surface = TRUE;
			}
		}

		if ( !skip_surface )
		{
			reset_deferred_state_changes ();

			zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
			current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

#if ALWAYS_SPECULAR_RENDER
			set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
			set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif
			set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

			if ( current_object_3d_surface->additive )
			{
				current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
				current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
				current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
				current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;

				set_deferred_d3d_texture ( 0, current_object_3d_texture );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

				set_deferred_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
				set_deferred_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
			}
			else
			{
				set_deferred_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
				set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
			}

			if ( current_object_3d_surface->smoothed )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					wrender_unclipped_3d_object_gouraud_white_polygon ( current_object_3d_faces );
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				if ( current_object_3d_surface->polygons )
				{
					if ( current_object_3d_surface->additive )
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							wrender_unclipped_3d_object_white_textured_polygon ( current_object_3d_faces );
							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
					}
					else
					{
						for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
						{
							wrender_unclipped_3d_object_white_polygon ( current_object_3d_faces );
							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
					}
				}
				else
				{
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						wrender_unclipped_3d_object_plain_white_line ();
						current_object_3d_point_list += 2;
					}
				}
			}
		}
		else
		{
			//
			// Move on through the point list & normals list
			//

			if ( current_object_3d_surface->polygons )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( !current_object_3d_surface->smoothed )
					{
						current_object_3d_face_normal_list++;
					}

					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				current_object_3d_point_list += 2 * current_object_3d_surface->number_of_faces;
			}
		}

		current_object_3d_surface_point_list += number_of_surface_points;
		if ( current_object_3d_surface->smoothed )
		{
			current_object_3d_surface_point_normal_list += number_of_surface_points;
		}
		if ( current_object_3d_surface->textured )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}
		if ( current_object_3d_surface->has_luminosity_texture )
		{
			current_object_3d_surface_point_texture_list += number_of_surface_points;
		}
		current_object_3d_surface++;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_transparent_surface ( int clipped )
{
	int
		faces_left;

	ASSERT ( object_3d_transparent_surface_index < MAXIMUM_TRANLUCENT_SURFACES );

	if ( !current_object_3d_surface->polygons )
	{
		current_object_3d_point_list += ( 2 * current_object_3d_surface->number_of_faces );
	}
	else
	{
		//
		// Setup the data in the translucent surface holder
		//

		memcpy ( object_3d_translucent_surfaces[object_3d_transparent_surface_index].vp.attitude, current_object_3d_object_base->object_vp->attitude, sizeof ( matrix3x3 ) );
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].vp.position = current_object_3d_object_base->object_vp->position;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].object_view_position = *current_object_3d_relative_position;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].object_unit_position = *current_object_3d_unit_position;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].dissolve_value = current_object_3d_dissolve_value;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].object_3d_scale = object_3d_scale;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].object_index = current_object_3d_object_base->object_number;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface = current_object_3d_surface;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].faces = current_object_3d_faces;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface_point_list = current_object_3d_surface_point_list;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface_point_normal_list = current_object_3d_surface_point_normal_list;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface_point_texture_list = current_object_3d_surface_point_texture_list;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].faces_point_list = current_object_3d_point_list;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].faces_normal_list = current_object_3d_face_normal_list;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].clipped = clipped;
		object_3d_translucent_surfaces[object_3d_transparent_surface_index].lightmaps_enabled = current_object_3d_light_maps_enabled;

		if ( current_object_3d_surface->textured )
		{
			if ( current_object_3d_surface->texture_animation )
			{
				int
					frame;

				frame = texture_animations[current_object_3d_surface->texture_index].current_frame;
				object_3d_translucent_surfaces[object_3d_transparent_surface_index].texture_index = texture_animations[current_object_3d_surface->texture_index].texture_indices[frame];
			}
			else
			{
				object_3d_translucent_surfaces[object_3d_transparent_surface_index].texture_index = current_object_3d_surface->texture_index;
			}
		}

		//
		// Attach this surface to the list of transparent surfaces
		//

		object_3d_translucent_surfaces[object_3d_transparent_surface_index].succ = current_object_3d_translucent_surfaces;

		current_object_3d_translucent_surfaces = &object_3d_translucent_surfaces[object_3d_transparent_surface_index];

		object_3d_transparent_surface_index++;

		//
		// Skip over the faces & increment the points ptr along
		//

		for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
		{
			if ( !current_object_3d_surface->smoothed )
			{
				current_object_3d_face_normal_list++;
			}
			current_object_3d_point_list += current_object_3d_faces->number_of_points;
			current_object_3d_faces++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_translucent_object ( translucent_object_surface *translucent_surfaces )
{

	int
		object_number;

	light_3d_source
		*light;

	vec3d
		object_camera_position,
		object_camera_direction;

	translucent_object_surface
		*surface;

	reset_deferred_state_changes ();

	surface = translucent_surfaces;

	while ( surface )
	{

		if ( surface->surface->polygons )
		{

			matrix3x3
				temp;
			vec3d
				temp_vec;
			float
					heading,
					pitch;

			//
			// Set up the object drawing global variables
			//

			object_3d_points_current_base = 0;
			object_3d_object_current_base = 0;
			object_3d_light_3d_current_base = 0;

			current_object_3d_light_maps_enabled = surface->lightmaps_enabled;

			//
			// Get the object's position relative to the camera
			//

			current_object_3d_relative_position = &surface->object_view_position;

			//
			// Set the main objects' scaling values
			//

			object_3d_scale = surface->object_3d_scale;

			//
			// Set the object dissolve variables
			//

			current_object_3d_dissolve_value = surface->dissolve_value;
			current_object_3d_dissolve_factor = current_object_3d_dissolve_value;
			current_object_3d_dissolve_factor /= 255.0;

			// particle clouds hack - make billboard from subobject
			
			if (scene_index == OBJECT_3D_CLOUD)
			{
				memcpy ( &temp, surface->vp.attitude, sizeof ( matrix3x3 ) );

				temp_vec.x = visual_3d_vp->position.x - surface->vp.position.x;
				temp_vec.y = visual_3d_vp->position.y - surface->vp.position.y;
				temp_vec.z = visual_3d_vp->position.z - surface->vp.position.z;

				normalise_any_3d_vector(&temp_vec);
				get_heading_and_pitch_from_3d_unit_vector(&temp_vec, &heading, &pitch);
				get_3d_transformation_matrix(&surface->vp.attitude, heading, pitch - PI/2, 0);
			}

			//
			// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
			//

			rotation_3d[0][0] = ( surface->vp.xv.x * visual_3d_vp->xv.x + surface->vp.xv.y * visual_3d_vp->xv.y + surface->vp.xv.z * visual_3d_vp->xv.z );
			rotation_3d[0][1] = ( surface->vp.xv.x * visual_3d_vp->yv.x + surface->vp.xv.y * visual_3d_vp->yv.y + surface->vp.xv.z * visual_3d_vp->yv.z );
			rotation_3d[0][2] = ( surface->vp.xv.x * visual_3d_vp->zv.x + surface->vp.xv.y * visual_3d_vp->zv.y + surface->vp.xv.z * visual_3d_vp->zv.z );

			rotation_3d[1][0] = ( surface->vp.yv.x * visual_3d_vp->xv.x + surface->vp.yv.y * visual_3d_vp->xv.y + surface->vp.yv.z * visual_3d_vp->xv.z );
			rotation_3d[1][1] = ( surface->vp.yv.x * visual_3d_vp->yv.x + surface->vp.yv.y * visual_3d_vp->yv.y + surface->vp.yv.z * visual_3d_vp->yv.z );
			rotation_3d[1][2] = ( surface->vp.yv.x * visual_3d_vp->zv.x + surface->vp.yv.y * visual_3d_vp->zv.y + surface->vp.yv.z * visual_3d_vp->zv.z );

			rotation_3d[2][0] = ( surface->vp.zv.x * visual_3d_vp->xv.x + surface->vp.zv.y * visual_3d_vp->xv.y + surface->vp.zv.z * visual_3d_vp->xv.z );
			rotation_3d[2][1] = ( surface->vp.zv.x * visual_3d_vp->yv.x + surface->vp.zv.y * visual_3d_vp->yv.y + surface->vp.zv.z * visual_3d_vp->yv.z );
			rotation_3d[2][2] = ( surface->vp.zv.x * visual_3d_vp->zv.x + surface->vp.zv.y * visual_3d_vp->zv.y + surface->vp.zv.z * visual_3d_vp->zv.z );

			if (scene_index == OBJECT_3D_CLOUD)
				memcpy ( surface->vp.attitude, &temp, sizeof ( matrix3x3 ) );

			memcpy ( object_to_eye_attitude, rotation_3d, sizeof ( matrix3x3 ) );
			
			rotation_3d[0][0] *= surface->object_3d_scale.x;
			rotation_3d[1][0] *= surface->object_3d_scale.y;
			rotation_3d[2][0] *= surface->object_3d_scale.z;

			rotation_3d[0][1] *= surface->object_3d_scale.x;
			rotation_3d[1][1] *= surface->object_3d_scale.y;
			rotation_3d[2][1] *= surface->object_3d_scale.z;

			rotation_3d[0][2] *= surface->object_3d_scale.x;
			rotation_3d[1][2] *= surface->object_3d_scale.y;
			rotation_3d[2][2] *= surface->object_3d_scale.z;

			//
			// Get the object number
			//

			object_number = surface->object_index;

			//
			// Rotate the light source vector to be relative to the object.
			//

			light = generate_relative_lights ( &surface->vp, &surface->object_unit_position, current_3d_lights );
			
			if (scene_index == OBJECT_3D_CLOUD) // light up clouds
			{
				light->x = 0;
				light->z = light->y = - sin(PI/4);
			}

			{

				vec3d
					rel_pos;
				
				//
				// Calculate the relative camera position in the object viewspace
				//

				rel_pos.x = visual_3d_vp->x - surface->vp.x;
				rel_pos.y = visual_3d_vp->y - surface->vp.y;
				rel_pos.z = visual_3d_vp->z - surface->vp.z;

				object_camera_position.x = ( rel_pos.x * surface->vp.attitude[0][0] + rel_pos.y * surface->vp.attitude[0][1] + rel_pos.z * surface->vp.attitude[0][2] );
				object_camera_position.y = ( rel_pos.x * surface->vp.attitude[1][0] + rel_pos.y * surface->vp.attitude[1][1] + rel_pos.z * surface->vp.attitude[1][2] );
				object_camera_position.z = ( rel_pos.x * surface->vp.attitude[2][0] + rel_pos.y * surface->vp.attitude[2][1] + rel_pos.z * surface->vp.attitude[2][2] );

				object_camera_direction.x = ( visual_3d_vp->zv.x * surface->vp.attitude[0][0] + visual_3d_vp->zv.y * surface->vp.attitude[1][0] + visual_3d_vp->zv.z * surface->vp.attitude[2][0] );
				object_camera_direction.y = ( visual_3d_vp->zv.x * surface->vp.attitude[0][1] + visual_3d_vp->zv.y * surface->vp.attitude[1][1] + visual_3d_vp->zv.z * surface->vp.attitude[2][1] );
				object_camera_direction.z = ( visual_3d_vp->zv.x * surface->vp.attitude[0][2] + visual_3d_vp->zv.y * surface->vp.attitude[1][2] + visual_3d_vp->zv.z * surface->vp.attitude[2][2] );
			}


			//
			//	Set up this objects' object info structure
			//

			object_3d_object_base[object_3d_object_current_base].lights = light;
			object_3d_object_base[object_3d_object_current_base].camera_position = object_camera_position;
			object_3d_object_base[object_3d_object_current_base].camera_direction = object_camera_direction;
			object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;
			object_3d_object_base[object_3d_object_current_base].object_number = object_number;
			object_3d_object_base[object_3d_object_current_base].object_vp = &surface->vp;

			current_object_3d_object_base = &object_3d_object_base[object_3d_object_current_base];

			//
			// Now start transforming etc
			//

			current_object_3d_surface = surface->surface;
			current_object_3d_faces = surface->faces;
			current_object_3d_surface_point_list = surface->surface_point_list;
			current_object_3d_surface_point_normal_list = surface->surface_point_normal_list;
			current_object_3d_surface_point_texture_list = surface->surface_point_texture_list;
			current_object_3d_point_list = surface->faces_point_list;
			current_object_3d_face_normal_list = surface->faces_normal_list;
			current_object_3d_light_maps_enabled = surface->lightmaps_enabled;

			if ( objects_3d_data[object_number].number_of_points )
			{

				int
					illuminated_surface;

				illuminated_surface = TRUE;

				if ( illuminated_surface )
				{

		//			illuminate_3d_object ( &objects_3d_data[object_number], current_object_3d_relative_position, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );
					illuminate_3d_object_surface ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );
				}

				if ( surface->clipped )
				{

					transform_3d_object_surface ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );

					draw_3d_translucent_surface_clipped_faces ( surface );

					if ( ( surface->surface->polygons ) && ( surface->surface->reflectivity != 0 ) )
					{

						current_object_3d_surface = surface->surface;
						current_object_3d_faces = surface->faces;
						current_object_3d_surface_point_list = surface->surface_point_list;
						current_object_3d_surface_point_normal_list = surface->surface_point_normal_list;
						current_object_3d_surface_point_texture_list = surface->surface_point_texture_list;
						current_object_3d_point_list = surface->faces_point_list;
						current_object_3d_face_normal_list = surface->faces_normal_list;
						current_object_3d_light_maps_enabled = surface->lightmaps_enabled;

						draw_3d_translucent_surface_clipped_reflection_faces ( surface );
					}
				}
				else
				{

					transform_unclipped_3d_object_surface ( &objects_3d_data[object_number], current_object_3d_relative_position, light, &object_camera_position, object_3d_points_current_base );

					draw_3d_translucent_surface_unclipped_faces ( surface );

					if ( ( surface->surface->polygons ) && ( surface->surface->reflectivity != 0 ) )
					{

						current_object_3d_surface = surface->surface;
						current_object_3d_faces = surface->faces;
						current_object_3d_surface_point_list = surface->surface_point_list;
						current_object_3d_surface_point_normal_list = surface->surface_point_normal_list;
						current_object_3d_surface_point_texture_list = surface->surface_point_texture_list;
						current_object_3d_point_list = surface->faces_point_list;
						current_object_3d_face_normal_list = surface->faces_normal_list;
						current_object_3d_light_maps_enabled = surface->lightmaps_enabled;

						draw_3d_translucent_surface_unclipped_reflection_faces ( surface );
					}
				}
			}
		}

		surface = surface->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_translucent_surface_clipped_faces ( translucent_object_surface *surface )
{
	int
		number_of_surface_points,
		faces_left;

	number_of_surface_points = current_object_3d_surface->number_of_points;
	if ( number_of_surface_points == 0 )
	{
		number_of_surface_points = 256;
	}

	zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
	current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

	if ( command_line_trees_fog == 1 || command_line_trees_fog == 2 && (1 / get_delta_time_average() >= (20 + 10 * !fog)) ) // clipped trees fog
		fog = TRUE;
	else
	{
		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );
		fog = FALSE;
	}

	if ( current_object_3d_surface->additive )
	{
		set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
		set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
	}
	else
	{
		set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
		set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}

	if ( current_object_3d_surface->textured )
	{
		current_object_3d_texture = system_textures[surface->texture_index];
		current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
		current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
		current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
		current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;

#if ALWAYS_SPECULAR_RENDER
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif
		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

		set_d3d_texture ( 0, current_object_3d_texture );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
		set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
		set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
		set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

		if ( current_object_3d_surface->smoothed )
		{
			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{
				if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
				{
					if ( current_object_3d_outcode == 0 )
					{
						wrender_translucent_unclipped_3d_object_gouraud_textured_polygon ( current_object_3d_faces );
					}
					else
					{
						wrender_translucent_clipped_3d_object_gouraud_textured_polygon ( current_object_3d_faces );
					}
				}

				current_object_3d_point_list += current_object_3d_faces->number_of_points;
				current_object_3d_faces++;
			}
		}
		else
		{
			if ( current_object_3d_surface->polygons )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
					{
						if ( current_object_3d_outcode == 0 )
						{
							wrender_translucent_unclipped_3d_object_textured_polygon ( current_object_3d_faces );
						}
						else
						{
							wrender_translucent_clipped_3d_object_textured_polygon ( current_object_3d_faces );
						}
					}
					current_object_3d_face_normal_list++;
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( d3d_textured_lines )
					{
						if ( !outcode_3d_object_surface_polygon ( 2, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
						{
							if ( current_object_3d_outcode == 0 )
							{
								wrender_unclipped_3d_object_textured_line ();
							}
							else
							{
								wrender_clipped_3d_object_textured_line ();
							}
						}
					}
					current_object_3d_point_list += 2;
				}
			}
		}
	}
	else
	{
#if ALWAYS_SPECULAR_RENDER
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif
		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

		if ( current_object_3d_surface->smoothed )
		{
			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{
				if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
				{
					if ( current_object_3d_outcode == 0 )
					{
						wrender_translucent_unclipped_3d_object_gouraud_polygon ( current_object_3d_faces );
					}
					else
					{
						wrender_translucent_clipped_3d_object_gouraud_polygon ( current_object_3d_faces );
					}
				}
				current_object_3d_point_list += current_object_3d_faces->number_of_points;
				current_object_3d_faces++;
			}
		}
		else
		{
			if ( current_object_3d_surface->polygons )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )

				{
					if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
					{
						if ( current_object_3d_outcode == 0 )
						{
							wrender_translucent_unclipped_3d_object_polygon ( current_object_3d_faces );
						}
						else
						{
							wrender_translucent_clipped_3d_object_polygon ( current_object_3d_faces );
						}
					}
					current_object_3d_face_normal_list++;
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( !outcode_3d_object_surface_polygon ( 2, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
					{
						if ( current_object_3d_outcode == 0 )
						{
							wrender_unclipped_3d_object_plain_line ();
						}
						else
						{
							wrender_clipped_3d_object_plain_line ();
						}
					}
					current_object_3d_point_list += 2;
				}
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_translucent_surface_unclipped_faces ( translucent_object_surface *surface )
{
	int
		number_of_surface_points,
		faces_left;

	number_of_surface_points = current_object_3d_surface->number_of_points;
	if ( number_of_surface_points == 0 )
	{
		number_of_surface_points = 256;
	}

	zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
	current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

	if ( current_object_3d_surface->additive )
	{
		set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
		set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
	}
	else
	{
		set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
		set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}

	if ( current_object_3d_surface->textured )
	{
		current_object_3d_texture = system_textures[surface->texture_index];
		current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
		current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
		current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
		current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;

#if ALWAYS_SPECULAR_RENDER
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif
		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

		set_d3d_texture ( 0, current_object_3d_texture );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
		set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
		set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
		set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

		if ( current_object_3d_surface->smoothed )
		{
			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{
				wrender_translucent_unclipped_3d_object_gouraud_textured_polygon ( current_object_3d_faces );
				current_object_3d_point_list += current_object_3d_faces->number_of_points;
				current_object_3d_faces++;
			}
		}
		else
		{
			if ( current_object_3d_surface->polygons )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					wrender_translucent_unclipped_3d_object_textured_polygon ( current_object_3d_faces );
					current_object_3d_face_normal_list++;
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( d3d_textured_lines )
					{
//						wrender_translucent_unclipped_3d_object_textured_line ( current_object_3d_faces );
					}
					current_object_3d_point_list += 2;
				}
			}
		}
	}
	else
	{
#if ALWAYS_SPECULAR_RENDER
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
#else
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
#endif
		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

		if ( current_object_3d_surface->smoothed )
		{
			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{
				wrender_translucent_unclipped_3d_object_gouraud_polygon ( current_object_3d_faces );
				current_object_3d_point_list += current_object_3d_faces->number_of_points;
				current_object_3d_faces++;
			}
		}
		else
		{
			if ( current_object_3d_surface->polygons )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )

				{
					wrender_translucent_unclipped_3d_object_polygon ( current_object_3d_faces );
					current_object_3d_face_normal_list++;
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
//					wrender_translucent_unclipped_3d_object_plain_line ();
					current_object_3d_point_list += 2;
				}
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_translucent_surface_clipped_reflection_faces ( translucent_object_surface *surface )
{
	int
		number_of_surface_points,
		faces_left;

	number_of_surface_points = current_object_3d_surface->number_of_points;
	if ( number_of_surface_points == 0 )
	{
		number_of_surface_points = 256;
	}

	zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
	current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

	set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

	set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
	set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );

	{
		current_object_3d_texture = current_object_3d_reflection_texture_map;
		current_object_3d_texture_u_address = D3DTADDRESS_WRAP;
		current_object_3d_texture_v_address = D3DTADDRESS_WRAP;
		current_object_3d_texture_filter = D3DTFG_LINEAR;
		current_object_3d_texture_mipmap = D3DTFP_POINT;

		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

		set_d3d_texture ( 0, current_object_3d_texture );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
		set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
		set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
		set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

		if ( current_object_3d_surface->smoothed )
		{
			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{
				if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
				{
					if ( current_object_3d_outcode == 0 )
					{
						wrender_translucent_unclipped_3d_object_reflective_gouraud_polygon ( current_object_3d_faces );
					}
					else
					{
						wrender_translucent_clipped_3d_object_reflective_gouraud_polygon ( current_object_3d_faces );
					}
				}
				current_object_3d_point_list += current_object_3d_faces->number_of_points;
				current_object_3d_faces++;
			}
		}
		else
		{
			if ( current_object_3d_surface->polygons )
			{
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, current_object_3d_object_base->points_base, &current_object_3d_outcode ) )
					{
						if ( current_object_3d_outcode == 0 )
						{
							wrender_translucent_unclipped_3d_object_reflective_polygon ( current_object_3d_faces );
						}
						else
						{
							wrender_translucent_clipped_3d_object_reflective_polygon ( current_object_3d_faces );
						}
					}
					current_object_3d_face_normal_list++;
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				ASSERT ( FALSE );
				current_object_3d_point_list += 2 * current_object_3d_surface->number_of_faces;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_translucent_surface_unclipped_reflection_faces ( translucent_object_surface *surface )
{
	int
		number_of_surface_points,
		faces_left;

	number_of_surface_points = current_object_3d_surface->number_of_points;
	if ( number_of_surface_points == 0 )
	{
		number_of_surface_points = 256;
	}

	zbuffer_constant = ( current_object_3d_surface->detail ) ? zbuffer_constant_elevated_bias: zbuffer_constant_normal_bias;
	current_object_3d_specular = ( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

	set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA );
	set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA );

	current_object_3d_texture = current_object_3d_reflection_texture_map;
	current_object_3d_texture_u_address = D3DTADDRESS_WRAP;
	current_object_3d_texture_v_address = D3DTADDRESS_WRAP;
	current_object_3d_texture_filter = D3DTFG_LINEAR;
	current_object_3d_texture_mipmap = D3DTFP_POINT;

	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture ( 0, current_object_3d_texture );
	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
	set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

	if ( current_object_3d_surface->smoothed )
	{
		for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
		{
			wrender_translucent_unclipped_3d_object_reflective_gouraud_polygon ( current_object_3d_faces );
			current_object_3d_point_list += current_object_3d_faces->number_of_points;
			current_object_3d_faces++;
		}
	}
	else
	{
		if ( current_object_3d_surface->polygons )
		{
			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{
				wrender_translucent_unclipped_3d_object_reflective_polygon ( current_object_3d_faces );
				current_object_3d_face_normal_list++;
				current_object_3d_point_list += current_object_3d_faces->number_of_points;
				current_object_3d_faces++;
			}
		}
		else
		{
			ASSERT ( FALSE );
			current_object_3d_point_list += 2 * current_object_3d_surface->number_of_faces;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

