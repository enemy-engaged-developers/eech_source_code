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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NORMAL_ZBIAS 1

#define ELEVATED_ZBIAS 2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, vec3d *position, int infrared_override );

static void draw_zbuffered_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, vec3d *position, int infrared_override );

static void draw_3d_object_hardware_faces ( int object_number, object_3d_info *this_object_3d_info );

static void draw_3d_object_untextured_hardware_faces ( int object_number, object_3d_info *this_object_3d_info );

static void add_transparent_surface ( void );

void draw_3d_object_hardware_translucent_faces ( translucent_object_surface *surface );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static D3DMATRIX
	d3d_matrix;
	
object_3d_surface_info
	*current_object_3d_surface_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hardware_3d_object ( object_3d_instance *obj, int infrared_override )
{

	int
		object_number;

	light_3d_source
		*light;

	vec3d
		object_camera_position,
		object_camera_direction,
		object_pos,
		object_unit_pos;

	object_3d_scene_database_entry
		*scene;

	// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG
	//
	// Turn fogging OFF for now
	//
	// DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG

	set_d3d_int_state ( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_LINEAR );

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_CCW );

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

	current_3d_object_is_flat = FALSE;

	current_object_3d_light_maps_enabled = obj->object_internal_lighting;

	//
	// Get the object's position relative to the camera
	//

	current_object_3d_relative_position = &obj->view_position;	//rel_vp.position;

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

		object_pos.x = x;
		object_pos.y = y;
		object_pos.z = z;

		object_unit_pos.x = -object_pos.x;
		object_unit_pos.y = -object_pos.y;
		object_unit_pos.z = -object_pos.z;

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

			matrix4x4
				matrix;

			vec3d
				posn,
				rel;

			rel.x = current_object_3d_relative_position->x;
			rel.y = current_object_3d_relative_position->y;
			rel.z = current_object_3d_relative_position->z;

			posn.x = visual_3d_vp->attitude[0][0] * rel.x + visual_3d_vp->attitude[1][0] * rel.y + visual_3d_vp->attitude[2][0] * rel.z;
			posn.y = visual_3d_vp->attitude[0][1] * rel.x + visual_3d_vp->attitude[1][1] * rel.y + visual_3d_vp->attitude[2][1] * rel.z;
			posn.z = visual_3d_vp->attitude[0][2] * rel.x + visual_3d_vp->attitude[1][2] * rel.y + visual_3d_vp->attitude[2][2] * rel.z;

			//
			// Set the world transformation matrix
			//

			matrix[0][0] = obj->vp.attitude[0][0] * object_3d_scale.x;
			matrix[0][1] = obj->vp.attitude[0][1] * object_3d_scale.x;
			matrix[0][2] = obj->vp.attitude[0][2] * object_3d_scale.x;
			matrix[0][3] = 0;

			matrix[1][0] = obj->vp.attitude[1][0] * object_3d_scale.y;
			matrix[1][1] = obj->vp.attitude[1][1] * object_3d_scale.y;
			matrix[1][2] = obj->vp.attitude[1][2] * object_3d_scale.y;
			matrix[1][3] = 0;

			matrix[2][0] = obj->vp.attitude[2][0] * object_3d_scale.z;
			matrix[2][1] = obj->vp.attitude[2][1] * object_3d_scale.z;
			matrix[2][2] = obj->vp.attitude[2][2] * object_3d_scale.z;
			matrix[2][3] = 0;

			matrix[3][0] = posn.x;	//obj->vp.position.x;
			matrix[3][1] = posn.y;	//obj->vp.position.y;
			matrix[3][2] = posn.z;	//obj->vp.position.z;
			matrix[3][3] = 1;

			memcpy ( &d3d_matrix, matrix, sizeof ( matrix ) );

			f3d_set_transform ( D3DTRANSFORMSTATE_WORLD, &d3d_matrix );
		
			if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
			{
	
				draw_3d_object_hardware_faces ( object_number, current_object_3d_object_base );
			}
			else
			{

				draw_3d_object_untextured_hardware_faces ( object_number, current_object_3d_object_base );
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
		
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );

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

		if ( obj->requires_immediate_render )
		{

			draw_3d_hardware_translucent_object ( current_object_3d_translucent_surfaces );
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

				buffer->type = OBJECT_3D_DRAW_TYPE_ZBUFFERED_TRANSLUCENT_OBJECT;
	
				buffer->z = *( ( int * ) &obj->view_position );
	
				buffer->translucent_surfaces = current_object_3d_translucent_surfaces;
	
				insert_transparent_buffer_into_3d_scene ( buffer );
			}
		}
	}


	//
	// Now finish sorting the translucent polygons.
	//

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
			sprite.texture = system_textures[TEXTURE_INDEX_FLARE001];

			insert_zbiased_object_into_3d_scene ( OBJECT_3D_DRAW_TYPE_SPRITE, &sprite, 0 );
		}
	}

	set_d3d_int_state ( D3DRENDERSTATE_FOGVERTEXMODE, D3DFOG_NONE );
	set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, 0 );
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
		object_pos,
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
	
			object_pos.x = x;
			object_pos.y = y;
			object_pos.z = z;
	
			object_unit_pos.x = -object_pos.x;
			object_unit_pos.y = -object_pos.y;
			object_unit_pos.z = -object_pos.z;
	
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
		
			if ( !get_object_3d_outcode ( object_number, &sub_pos, &object_outcode ) )
			{

				matrix4x4
					matrix;

				vec3d
					posn,
					rel;
	
				//
				// Set the world transformation matrix
				//

				matrix[0][0] = vp.attitude[0][0] * object_3d_scale.x;
				matrix[0][1] = vp.attitude[0][1] * object_3d_scale.x;
				matrix[0][2] = vp.attitude[0][2] * object_3d_scale.x;
				matrix[0][3] = 0;
	
				matrix[1][0] = vp.attitude[1][0] * object_3d_scale.y;
				matrix[1][1] = vp.attitude[1][1] * object_3d_scale.y;
				matrix[1][2] = vp.attitude[1][2] * object_3d_scale.y;
				matrix[1][3] = 0;
	
				matrix[2][0] = vp.attitude[2][0] * object_3d_scale.z;
				matrix[2][1] = vp.attitude[2][1] * object_3d_scale.z;
				matrix[2][2] = vp.attitude[2][2] * object_3d_scale.z;
				matrix[2][3] = 0;

				rel.x = current_object_3d_relative_position->x;
				rel.y = current_object_3d_relative_position->y;
				rel.z = current_object_3d_relative_position->z;
	
				posn.x = visual_3d_vp->attitude[0][0] * rel.x + visual_3d_vp->attitude[1][0] * rel.y + visual_3d_vp->attitude[2][0] * rel.z;
				posn.y = visual_3d_vp->attitude[0][1] * rel.x + visual_3d_vp->attitude[1][1] * rel.y + visual_3d_vp->attitude[2][1] * rel.z;
				posn.z = visual_3d_vp->attitude[0][2] * rel.x + visual_3d_vp->attitude[1][2] * rel.y + visual_3d_vp->attitude[2][2] * rel.z;
	/*
				matrix[3][0] = vp.position.x;
				matrix[3][1] = vp.position.y;
				matrix[3][2] = vp.position.z;
				matrix[3][3] = 1;
*/
				matrix[3][0] = posn.x;
				matrix[3][1] = posn.y;
				matrix[3][2] = posn.z;
				matrix[3][3] = 1;

				memcpy ( &d3d_matrix, matrix, sizeof ( matrix ) );
	
				f3d_set_transform ( D3DTRANSFORMSTATE_WORLD, &d3d_matrix );

				if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
				{
		
					draw_3d_object_hardware_faces ( object_number, current_object_3d_object_base );
				}
				else
				{
	
					draw_3d_object_untextured_hardware_faces ( object_number, current_object_3d_object_base );
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
	
					draw_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count], &vp, &sub_pos, infrared_override );
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
	
					draw_sub_object ( NULL, &scene->sub_objects[count], &vp, &sub_pos, infrared_override );
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

void draw_hardware_zbuffered_3d_object ( object_3d_instance *obj, int object_is_flat, int infrared_override )
{

	int
		object_number;

	vec3d
		object_camera_position,
		object_camera_direction,
		object_unit_pos;

	object_3d_scene_database_entry
		*scene;

	viewpoint
		old_object_vp;

	set_d3d_int_state ( D3DRENDERSTATE_FOGENABLE, FALSE );

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

	old_object_vp.position = obj->vp.position;

	{

		vec3d
			v1,
			v2;

		multiply_matrix3x3_vec3d ( &v1, visual_3d_vp->attitude, current_object_3d_relative_position );
		v1.x = -v1.x;
		v1.y = -v1.y;
		v1.z = -v1.z;

		obj->vp.x = visual_3d_vp->x - v1.x;
		obj->vp.y = visual_3d_vp->y - v1.y;
		obj->vp.z = visual_3d_vp->z - v1.z;

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

	object_3d_object_base[object_3d_object_current_base].lights = NULL;	//light;
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

			matrix4x4
				matrix;

			//
			// Set the world transformation matrix
			//

			matrix[0][0] = obj->vp.attitude[0][0] * object_3d_scale.x;
			matrix[0][1] = obj->vp.attitude[0][1] * object_3d_scale.y;
			matrix[0][2] = obj->vp.attitude[0][2] * object_3d_scale.z;
			matrix[0][3] = 0;

			matrix[1][0] = obj->vp.attitude[1][0] * object_3d_scale.x;
			matrix[1][1] = obj->vp.attitude[1][1] * object_3d_scale.y;
			matrix[1][2] = obj->vp.attitude[1][2] * object_3d_scale.z;
			matrix[1][3] = 0;

			matrix[2][0] = obj->vp.attitude[2][0] * object_3d_scale.x;
			matrix[2][1] = obj->vp.attitude[2][1] * object_3d_scale.y;
			matrix[2][2] = obj->vp.attitude[2][2] * object_3d_scale.z;
			matrix[2][3] = 0;


			{

				vec3d
					rel;

				rel.x = visual_3d_vp->attitude[0][0] * current_object_3d_relative_position->x +
							visual_3d_vp->attitude[1][0] * current_object_3d_relative_position->y +
							visual_3d_vp->attitude[2][0] * current_object_3d_relative_position->z;

				rel.y = visual_3d_vp->attitude[0][1] * current_object_3d_relative_position->x +
							visual_3d_vp->attitude[1][1] * current_object_3d_relative_position->y +
							visual_3d_vp->attitude[2][1] * current_object_3d_relative_position->z;

				rel.z = visual_3d_vp->attitude[0][2] * current_object_3d_relative_position->x +
							visual_3d_vp->attitude[1][2] * current_object_3d_relative_position->y +
							visual_3d_vp->attitude[2][2] * current_object_3d_relative_position->z;

				matrix[3][0] = rel.x;
				matrix[3][1] = rel.y;
				matrix[3][2] = rel.z;
				matrix[3][3] = 1;
			}

			memcpy ( &d3d_matrix, matrix, sizeof ( matrix ) );

			f3d_set_transform ( D3DTRANSFORMSTATE_WORLD, &d3d_matrix );
		
			if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
			{
	
				draw_3d_object_hardware_faces ( object_number, current_object_3d_object_base );
			}
			else
			{

				draw_3d_object_untextured_hardware_faces ( object_number, current_object_3d_object_base );
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
	
					draw_zbuffered_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count], &obj->vp, current_object_3d_relative_position, infrared_override );
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
	
					draw_zbuffered_sub_object ( NULL, &scene->sub_objects[count], &obj->vp, current_object_3d_relative_position, infrared_override );
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
		
		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );

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

		if ( obj->requires_immediate_render )
		{

			draw_3d_translucent_object ( current_object_3d_translucent_surfaces );
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

				buffer->type = OBJECT_3D_DRAW_TYPE_ZBUFFERED_TRANSLUCENT_OBJECT;
	
				buffer->z = *( ( int * ) &obj->view_position );
	
				buffer->translucent_surfaces = current_object_3d_translucent_surfaces;
	
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
			sprite.texture = system_textures[TEXTURE_INDEX_FLARE001];

			insert_zbiased_object_into_3d_scene ( OBJECT_3D_DRAW_TYPE_SPRITE, &sprite, 0 );
		}
	}

	obj->vp.position = old_object_vp.position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_zbuffered_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, vec3d *position, int infrared_override )
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
		object_pos,
		object_unit_pos,
		sub_pos,
		relative_position,
		relative_scale,
		*old_current_object_3d_relative_position;

	float
		relative_heading,
		relative_pitch,
		relative_roll;

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
	
			object_pos.x = x;
			object_pos.y = y;
			object_pos.z = z;
	
			object_unit_pos.x = -object_pos.x;
			object_unit_pos.y = -object_pos.y;
			object_unit_pos.z = -object_pos.z;
	
			normalise_any_3d_vector ( &object_unit_pos );

			current_object_3d_unit_position = &object_unit_pos;
		}
	
		//
		//	Set up this objects' object info structure
		//
	
		object_3d_object_base[object_3d_object_current_base].lights = NULL;	//light;
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
		
			if ( !get_object_3d_outcode ( object_number, &sub_pos, &object_outcode ) )
			{

				matrix4x4
					matrix;

				//
				// Set the world transformation matrix
				//

				matrix[0][0] = vp.attitude[0][0] * object_3d_scale.x;
				matrix[0][1] = vp.attitude[0][1] * object_3d_scale.y;
				matrix[0][2] = vp.attitude[0][2] * object_3d_scale.z;
				matrix[0][3] = 0;
	
				matrix[1][0] = vp.attitude[1][0] * object_3d_scale.x;
				matrix[1][1] = vp.attitude[1][1] * object_3d_scale.y;
				matrix[1][2] = vp.attitude[1][2] * object_3d_scale.z;
				matrix[1][3] = 0;
	
				matrix[2][0] = vp.attitude[2][0] * object_3d_scale.x;
				matrix[2][1] = vp.attitude[2][1] * object_3d_scale.y;
				matrix[2][2] = vp.attitude[2][2] * object_3d_scale.z;
				matrix[2][3] = 0;

				{
	
					vec3d
						rel;
	
					rel.x = visual_3d_vp->attitude[0][0] * current_object_3d_relative_position->x +
								visual_3d_vp->attitude[1][0] * current_object_3d_relative_position->y +
								visual_3d_vp->attitude[2][0] * current_object_3d_relative_position->z;
		
					rel.y = visual_3d_vp->attitude[0][1] * current_object_3d_relative_position->x +
								visual_3d_vp->attitude[1][1] * current_object_3d_relative_position->y +
								visual_3d_vp->attitude[2][1] * current_object_3d_relative_position->z;
		
					rel.z = visual_3d_vp->attitude[0][2] * current_object_3d_relative_position->x +
								visual_3d_vp->attitude[1][2] * current_object_3d_relative_position->y +
								visual_3d_vp->attitude[2][2] * current_object_3d_relative_position->z;

					matrix[3][0] = rel.x;
					matrix[3][1] = rel.y;
					matrix[3][2] = rel.z;
					matrix[3][3] = 1;
				}

				memcpy ( &d3d_matrix, matrix, sizeof ( matrix ) );
	
				f3d_set_transform ( D3DTRANSFORMSTATE_WORLD, &d3d_matrix );

				if ( ( textured_object_rendering_enabled ) || ( infrared_override ) )
				{
		
					draw_3d_object_hardware_faces ( object_number, current_object_3d_object_base );
				}
				else
				{
	
					draw_3d_object_untextured_hardware_faces ( object_number, current_object_3d_object_base );
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
	
					draw_zbuffered_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count], &vp, &sub_pos, infrared_override );
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
	
					draw_zbuffered_sub_object ( NULL, &scene->sub_objects[count], &vp, &sub_pos, infrared_override );
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

static void draw_3d_object_hardware_faces ( int object_number, object_3d_info *this_object_3d_info )
{

	int
		surfaces_left;

	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_faces = objects_3d_data[object_number].faces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;

	current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;
	current_object_3d_surface_point_texture_list = objects_3d_data[object_number].surface_texture_points;
	current_object_3d_surface_point_normal_list = objects_3d_data[object_number].surface_point_normals;

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
	{

		int
			number_of_surface_points;

		number_of_surface_points = current_object_3d_surface->number_of_points;

		if ( number_of_surface_points == 0 )
		{

			number_of_surface_points = 256;
		}
	
		if ( current_object_3d_surface->detail )				{ zbuffer_constant = zbuffer_constant_elevated_bias; }
		else																{ zbuffer_constant = zbuffer_constant_normal_bias; }

		if ( current_object_3d_surface->specularity )		{ current_object_3d_specular = specular_rendering_enabled; }
		else																{ current_object_3d_specular = FALSE; }

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

			if ( ( current_object_3d_surface->additive ) || ( current_object_3d_surface->translucent ) || ( current_object_3d_texture->contains_alpha ) || current_object_3d_dissolve_value < 200 )
			{

				add_transparent_surface ();
			}
			else
			{

				if ( current_object_3d_surface->luminous )
				{

					set_d3d_material_emissive_colour ( current_object_3d_surface->red * current_object_3d_diffuse_factor, current_object_3d_surface->green * current_object_3d_diffuse_factor, current_object_3d_surface->blue * current_object_3d_diffuse_factor, current_object_3d_surface->alpha );
				}
				else
				{

					set_d3d_material_colour ( 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, current_object_3d_surface->alpha, current_object_3d_surface->specularity );
				}

				current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
				current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
				current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
				current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;

				set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
				set_d3d_texture ( 0, current_object_3d_texture );
				set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

				set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
				set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
				set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
				set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
				set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

				if ( current_object_3d_surface->detail )
				{

					set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, ELEVATED_ZBIAS );
				}
				else
				{

					set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, NORMAL_ZBIAS );
				}

				if ( current_object_3d_surface->polygons )
				{

					object_3d_render_hardware_surface ( &objects_3d_data[object_number] );

					if ( ( current_object_3d_surface->has_luminosity_texture ) && ( current_object_3d_surface->polygons ) && ( current_object_3d_light_maps_enabled ) )
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
		
						current_object_3d_luminosity_texture_u_address = ( current_object_3d_surface->luminosity_texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
						current_object_3d_luminosity_texture_v_address = ( current_object_3d_surface->luminosity_texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
						current_object_3d_luminosity_texture_filter = ( current_object_3d_surface->luminosity_texture_filtered )	? D3DTFG_LINEAR : D3DTFG_POINT;
						current_object_3d_luminosity_texture_mipmap = ( current_object_3d_surface->luminosity_texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;
	
#if ( FORCE_LIGHTMAP_MIPMAPPING )
						current_object_3d_luminosity_texture_mipmap = D3DTFP_POINT;
#endif
	
						set_d3d_material_emissive_colour ( current_object_3d_surface->red * current_object_3d_diffuse_factor, current_object_3d_surface->green * current_object_3d_diffuse_factor, current_object_3d_surface->blue * current_object_3d_diffuse_factor, current_object_3d_surface->alpha );
	
						set_d3d_texture ( 0, current_object_3d_luminosity_texture );
						set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	
						set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
						set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
						set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
	
						set_d3d_texture_stage_state ( 0, D3DTSS_TEXCOORDINDEX, 1 );
						set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_luminosity_texture_u_address );
						set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_luminosity_texture_v_address );
						set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_luminosity_texture_filter );
						set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_luminosity_texture_filter );
						set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_luminosity_texture_mipmap );
	
						object_3d_render_hardware_surface ( &objects_3d_data[object_number] );

						set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
						set_d3d_texture_stage_state ( 0, D3DTSS_TEXCOORDINDEX, 0 );
					}
				}
				else
				{

					int
						point_count,
						count;

					D3DVERTEX
						*vertices;

					float
						xmax,
						ymax,
						zmax;

					if ( !f3d_vertex_lock ( d3d.hardware_untransformed_buffer, DDLOCK_DISCARDCONTENTS, ( LPVOID * ) &vertices ) )
					{

						current_object_3d_point_list += current_object_3d_surface->number_of_faces * 2;
					}
					else
					{
	
						xmax = max ( fabs ( objects_3d_data[object_number].bounding_box.xmin ), fabs ( objects_3d_data[object_number].bounding_box.xmax ) );
						ymax = max ( fabs ( objects_3d_data[object_number].bounding_box.ymin ), fabs ( objects_3d_data[object_number].bounding_box.ymax ) );
						zmax = max ( fabs ( objects_3d_data[object_number].bounding_box.zmin ), fabs ( objects_3d_data[object_number].bounding_box.zmax ) );
	
						xmax = xmax / 32767.0;
						ymax = ymax / 32767.0;
						zmax = zmax / 32767.0;
	
						point_count = 0;
	
						for ( count = 0; count < current_object_3d_surface->number_of_faces; count++ )
						{
	
							int
								surface_point_index,
								point_index;
	
							vec3d
								normal;
	
							calculate_line_normal ( this_object_3d_info, &normal );
	
							surface_point_index = current_object_3d_point_list[point_count].point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							point_count++;
	
							surface_point_index = current_object_3d_point_list[point_count].point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							point_count++;
						}
	
						ASSERT ( point_count < 2048 );
	
						f3d_vertex_unlock ( d3d.hardware_untransformed_buffer );
	
						f3d_draw_vb ( D3DPT_LINELIST, d3d.hardware_untransformed_buffer,
																							0,
																							current_object_3d_surface->number_of_faces * 2,
																							d3d_hardware_vertex_indices,
																							current_object_3d_surface->number_of_faces * 2 );
					}
				}
			}
		}
		else
		{

			if ( ( current_object_3d_surface->additive ) || ( current_object_3d_surface->translucent ) || current_object_3d_dissolve_value < 200)
			{

				add_transparent_surface ();
			}
			else
			{
	
				set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
				set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	
				if ( current_object_3d_surface->luminous )
				{

					set_d3d_material_emissive_colour ( current_object_3d_surface->red, current_object_3d_surface->green, current_object_3d_surface->blue, current_object_3d_surface->alpha );
				}
				else
				{

					set_d3d_material_colour ( current_object_3d_surface->red *	current_object_3d_diffuse_factor,
														current_object_3d_surface->green *	current_object_3d_diffuse_factor,
														current_object_3d_surface->blue *	current_object_3d_diffuse_factor,
														current_object_3d_surface->alpha,
														current_object_3d_surface->specularity );
				}

				if ( current_object_3d_surface->polygons )
				{
	
					if ( current_object_3d_surface->detail )
					{
	
						set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, ELEVATED_ZBIAS );
					}
					else
					{
	
						set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, NORMAL_ZBIAS );
					}
	
					object_3d_render_hardware_surface ( &objects_3d_data[object_number] );
				}
				else
				{

					int
						point_count,
						count;

					D3DVERTEX
						*vertices;

					float
						xmax,
						ymax,
						zmax;

					if ( !f3d_vertex_lock ( d3d.hardware_untransformed_buffer, DDLOCK_DISCARDCONTENTS, ( LPVOID * ) &vertices ) )
					{

						current_object_3d_point_list += current_object_3d_surface->number_of_faces * 2;
					}
					else
					{
						
						xmax = max ( fabs ( objects_3d_data[object_number].bounding_box.xmin ), fabs ( objects_3d_data[object_number].bounding_box.xmax ) );
						ymax = max ( fabs ( objects_3d_data[object_number].bounding_box.ymin ), fabs ( objects_3d_data[object_number].bounding_box.ymax ) );
						zmax = max ( fabs ( objects_3d_data[object_number].bounding_box.zmin ), fabs ( objects_3d_data[object_number].bounding_box.zmax ) );
	
						xmax = xmax / 32767.0;
						ymax = ymax / 32767.0;
						zmax = zmax / 32767.0;
	
						point_count = 0;
	
						for ( count = 0; count < current_object_3d_surface->number_of_faces; count++ )
						{
	
							int
								surface_point_index,
								point_index;
	
							vec3d
								normal;
	
							calculate_line_normal ( this_object_3d_info, &normal );
	
							surface_point_index = current_object_3d_point_list[point_count].point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							point_count++;
	
							surface_point_index = current_object_3d_point_list[point_count].point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							point_count++;
						}
	
						ASSERT ( point_count < 2048 );
	
						f3d_vertex_unlock ( d3d.hardware_untransformed_buffer );
	
						f3d_draw_vb ( D3DPT_LINELIST, d3d.hardware_untransformed_buffer,
																							0,
																							current_object_3d_surface->number_of_faces * 2,
																							d3d_hardware_vertex_indices,
																							current_object_3d_surface->number_of_faces * 2 );
					}
				}
			}
		}

		//
		// Move onto the next surface
		//

		if ( current_object_3d_surface->polygons )
		{

			int
				faces_left;

			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{

				current_object_3d_point_list += current_object_3d_faces->number_of_points;

				if ( !current_object_3d_surface->smoothed )
				{

					current_object_3d_face_normal_list++;
				}

				current_object_3d_faces++;
			}
		}
		else
		{
			current_object_3d_point_list += current_object_3d_surface->number_of_faces * 2;
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

static void draw_3d_object_untextured_hardware_faces ( int object_number, object_3d_info *this_object_3d_info )
{

	int
		surfaces_left;

	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_faces = objects_3d_data[object_number].faces;
	current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
	current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;

	current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;
	current_object_3d_surface_point_texture_list = objects_3d_data[object_number].surface_texture_points;
	current_object_3d_surface_point_normal_list = objects_3d_data[object_number].surface_point_normals;

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture_stage_state ( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );

	for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
	{

		int
			number_of_surface_points;

		number_of_surface_points = current_object_3d_surface->number_of_points;

		if ( number_of_surface_points == 0 )
		{

			number_of_surface_points = 256;
		}
	
		if ( current_object_3d_surface->detail )				{ zbuffer_constant = zbuffer_constant_elevated_bias; }
		else																{ zbuffer_constant = zbuffer_constant_normal_bias; }

		if ( current_object_3d_surface->specularity )		{ current_object_3d_specular = specular_rendering_enabled; }
		else																{ current_object_3d_specular = FALSE; }

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

			if ( ( current_object_3d_surface->translucent ) || ( current_object_3d_texture->contains_alpha ) )
			{

//				add_transparent_surface ();
			}
			else
			{

				if ( ( current_object_3d_surface->luminous ) || ( current_object_3d_surface->additive ) )
				{

					int
						ir,
						ig,
						ib;

					float
						r,
						g,
						b,
						intensity;

					r = current_object_3d_surface->red;
					g = current_object_3d_surface->green;
					b = current_object_3d_surface->blue;

					intensity = r * 0.3 + g * 0.59 + b * 0.11;

					intensity *= current_object_3d_dissolve_factor;
		
					convert_float_to_int ( ( intensity * ambient_3d_light.colour.red ), &ir );
					convert_float_to_int ( ( intensity * ambient_3d_light.colour.green ), &ig );
					convert_float_to_int ( ( intensity * ambient_3d_light.colour.blue ), &ib );
	
					set_d3d_material_emissive_colour ( ir * current_object_3d_diffuse_factor, ig * current_object_3d_diffuse_factor, ib * current_object_3d_diffuse_factor, current_object_3d_surface->alpha );

					if ( current_object_3d_surface->additive )
					{

						current_object_3d_texture_u_address = ( current_object_3d_surface->texture_wrapped_u ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
						current_object_3d_texture_v_address = ( current_object_3d_surface->texture_wrapped_v ) ? D3DTADDRESS_WRAP: D3DTADDRESS_CLAMP;
						current_object_3d_texture_filter = ( current_object_3d_surface->texture_filtered ) ? D3DTFG_LINEAR : D3DTFG_POINT;
						current_object_3d_texture_mipmap = ( current_object_3d_surface->texture_mipmapped )	? D3DTFP_POINT : D3DTFP_NONE;
		
						set_d3d_texture ( 0, current_object_3d_texture );
						set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		
						set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
						set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
						set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
						set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
						set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );

						set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
						set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE );
						set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE );
					}
					else
					{

						set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
						set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
					}
				}
				else
				{

					set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
					set_d3d_material_colour ( 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, current_object_3d_surface->alpha, current_object_3d_surface->specularity );
				}

				set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );

				if ( current_object_3d_surface->detail )
				{

					set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, ELEVATED_ZBIAS );
				}
				else
				{

					set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, NORMAL_ZBIAS );
				}

				if ( current_object_3d_surface->polygons )
				{

					object_3d_render_hardware_surface ( &objects_3d_data[object_number] );
				}
				else
				{

					int
						point_count,
						count;

					D3DVERTEX
						*vertices;

					float
						xmax,
						ymax,
						zmax;

					if ( !f3d_vertex_lock ( d3d.hardware_untransformed_buffer, DDLOCK_DISCARDCONTENTS, ( LPVOID * ) &vertices ) )
					{

						current_object_3d_point_list += current_object_3d_surface->number_of_faces * 2;
					}
					else
					{
	
						xmax = max ( fabs ( objects_3d_data[object_number].bounding_box.xmin ), fabs ( objects_3d_data[object_number].bounding_box.xmax ) );
						ymax = max ( fabs ( objects_3d_data[object_number].bounding_box.ymin ), fabs ( objects_3d_data[object_number].bounding_box.ymax ) );
						zmax = max ( fabs ( objects_3d_data[object_number].bounding_box.zmin ), fabs ( objects_3d_data[object_number].bounding_box.zmax ) );
	
						xmax = xmax / 32767.0;
						ymax = ymax / 32767.0;
						zmax = zmax / 32767.0;
	
						point_count = 0;
	
						for ( count = 0; count < current_object_3d_surface->number_of_faces; count++ )
						{
	
							int
								surface_point_index,
								point_index;
	
							vec3d
								normal;
	
							calculate_line_normal ( this_object_3d_info, &normal );
	
							surface_point_index = current_object_3d_point_list->point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							current_object_3d_point_list++;
							point_count++;
	
							surface_point_index = current_object_3d_point_list->point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							current_object_3d_point_list++;
							point_count++;
						}
	
						ASSERT ( point_count < 2048 );
	
						f3d_vertex_unlock ( d3d.hardware_untransformed_buffer );
	
						f3d_draw_vb ( D3DPT_LINELIST, d3d.hardware_untransformed_buffer,
																							0,
																							current_object_3d_surface->number_of_faces * 2,
																							d3d_hardware_vertex_indices,
																							current_object_3d_surface->number_of_faces * 2 );
					}
				}
			}
		}
		else
		{

			set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

			if ( ( current_object_3d_surface->additive ) || ( current_object_3d_surface->translucent ) )
			{

//				add_transparent_surface ();
			}
			else
			{
	
				int
					iint;

				float
					r,
					g,
					b,
					intensity;

				r = current_object_3d_surface->red;
				g = current_object_3d_surface->green;
				b = current_object_3d_surface->blue;

				intensity = r * 0.3 + g * 0.59 + b * 0.11;

				convert_float_to_int ( intensity, &iint );

				set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
	
				if ( current_object_3d_surface->luminous )
				{

					set_d3d_material_emissive_colour ( iint * current_object_3d_diffuse_factor, iint * current_object_3d_diffuse_factor, iint * current_object_3d_diffuse_factor, current_object_3d_surface->alpha );
				}
				else
				{

					set_d3d_material_colour ( 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, current_object_3d_surface->alpha, current_object_3d_surface->specularity );
				}

				if ( current_object_3d_surface->detail )
				{

					set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, ELEVATED_ZBIAS );
				}
				else
				{

					set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, NORMAL_ZBIAS );
				}

				if ( current_object_3d_surface->polygons )
				{
	
					object_3d_render_hardware_surface ( &objects_3d_data[object_number] );
				}
				else
				{

					int
						point_count,
						count;

					D3DVERTEX
						*vertices;

					float
						xmax,
						ymax,
						zmax;

					if ( !f3d_vertex_lock ( d3d.hardware_untransformed_buffer, DDLOCK_DISCARDCONTENTS, ( LPVOID * ) &vertices ) )
					{

						current_object_3d_point_list += current_object_3d_surface->number_of_faces * 2;
					}
					else
					{
						
						xmax = max ( fabs ( objects_3d_data[object_number].bounding_box.xmin ), fabs ( objects_3d_data[object_number].bounding_box.xmax ) );
						ymax = max ( fabs ( objects_3d_data[object_number].bounding_box.ymin ), fabs ( objects_3d_data[object_number].bounding_box.ymax ) );
						zmax = max ( fabs ( objects_3d_data[object_number].bounding_box.zmin ), fabs ( objects_3d_data[object_number].bounding_box.zmax ) );
	
						xmax = xmax / 32767.0;
						ymax = ymax / 32767.0;
						zmax = zmax / 32767.0;
	
						point_count = 0;
	
						for ( count = 0; count < current_object_3d_surface->number_of_faces; count++ )
						{
	
							int
								surface_point_index,
								point_index;
	
							vec3d
								normal;
	
							calculate_line_normal ( this_object_3d_info, &normal );
	
							surface_point_index = current_object_3d_point_list->point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							current_object_3d_point_list++;
							point_count++;
	
							surface_point_index = current_object_3d_point_list->point;
							point_index = current_object_3d_surface_point_list[surface_point_index].point;
	
							vertices[point_count].x = ( float ) objects_3d_data[object_number].points[point_index].x * xmax;
							vertices[point_count].y = ( float ) objects_3d_data[object_number].points[point_index].y * ymax;
							vertices[point_count].z = ( float ) objects_3d_data[object_number].points[point_index].z * zmax;
	
							vertices[point_count].nx = normal.x;
							vertices[point_count].ny = normal.y;
							vertices[point_count].nz = normal.z;
	
							current_object_3d_point_list++;
							point_count++;
						}
	
						ASSERT ( point_count < 2048 );
	
						f3d_vertex_unlock ( d3d.hardware_untransformed_buffer );
	
						f3d_draw_vb ( D3DPT_LINELIST, d3d.hardware_untransformed_buffer,
																							0,
																							current_object_3d_surface->number_of_faces * 2,
																							d3d_hardware_vertex_indices,
																							current_object_3d_surface->number_of_faces * 2 );
					}
				}
			}
		}

		//
		// Move onto the next surface
		//

		if ( current_object_3d_surface->polygons )
		{

			int
				faces_left;

			//
			// Only update point list if they're polygons - lines already have been updated.
			//

			for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
			{

				current_object_3d_point_list += current_object_3d_faces->number_of_points;

				if ( !current_object_3d_surface->smoothed )
				{

					current_object_3d_face_normal_list++;
				}

				current_object_3d_faces++;
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

void add_transparent_surface ( void )
{

	if ( current_object_3d_surface->polygons )
	{
	
		ASSERT ( object_3d_transparent_surface_index < MAXIMUM_TRANLUCENT_SURFACES );
	
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
	
			object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface_point_list = current_object_3d_surface_point_list;
			object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface_point_normal_list = current_object_3d_surface_point_normal_list;
			object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface_point_texture_list = current_object_3d_surface_point_texture_list;
			object_3d_translucent_surfaces[object_3d_transparent_surface_index].faces = current_object_3d_faces;
			object_3d_translucent_surfaces[object_3d_transparent_surface_index].faces_point_list = current_object_3d_point_list;
			object_3d_translucent_surfaces[object_3d_transparent_surface_index].faces_normal_list = current_object_3d_face_normal_list;
	
	//	object_3d_translucent_surfaces[object_3d_transparent_surface_index].surface_info = current_object_3d_surface_info;
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
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_hardware_translucent_object ( translucent_object_surface *translucent_surfaces )
{

	int
		object_number;

	vec3d
		object_camera_position,
		object_camera_direction;

	translucent_object_surface
		*surface;

	surface = translucent_surfaces;

	while ( surface )
	{
	
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
	
		object_3d_object_base[object_3d_object_current_base].lights = NULL;
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
	
		//
		// Set the world transformation matrix
		//

		{

			matrix4x4
				matrix;

			matrix[0][0] = surface->vp.attitude[0][0] * surface->object_3d_scale.x;
			matrix[0][1] = surface->vp.attitude[0][1] * surface->object_3d_scale.x;
			matrix[0][2] = surface->vp.attitude[0][2] * surface->object_3d_scale.x;
			matrix[0][3] = 0;
	
			matrix[1][0] = surface->vp.attitude[1][0] * surface->object_3d_scale.y;
			matrix[1][1] = surface->vp.attitude[1][1] * surface->object_3d_scale.y;
			matrix[1][2] = surface->vp.attitude[1][2] * surface->object_3d_scale.y;
			matrix[1][3] = 0;
	
			matrix[2][0] = surface->vp.attitude[2][0] * surface->object_3d_scale.z;
			matrix[2][1] = surface->vp.attitude[2][1] * surface->object_3d_scale.z;
			matrix[2][2] = surface->vp.attitude[2][2] * surface->object_3d_scale.z;
			matrix[2][3] = 0;
	
			matrix[3][0] = surface->vp.position.x;
			matrix[3][1] = surface->vp.position.y;
			matrix[3][2] = surface->vp.position.z;
			matrix[3][3] = 1;

			if ( surface->object_index == 7830 )	//OBJECT_3D_CANNON_SHELL_RED )
			{

				debug_log ( "Transparent matrix:" );
				debug_log ( "%f %f %f %f", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3] );
				debug_log ( "%f %f %f %f", matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3] );
				debug_log ( "%f %f %f %f", matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3] );
				debug_log ( "%f %f %f %f", matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3] );
			}

			memcpy ( &d3d_matrix, matrix, sizeof ( matrix ) );
	
			f3d_set_transform ( D3DTRANSFORMSTATE_WORLD, &d3d_matrix );
		}

		draw_3d_object_hardware_translucent_faces ( surface );

		surface = surface->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_hardware_zbuffered_translucent_object ( translucent_object_surface *translucent_surfaces )
{

	int
		object_number;

	vec3d
		object_camera_position,
		object_camera_direction;

	translucent_object_surface
		*surface;

	surface = translucent_surfaces;

	while ( surface )
	{
	
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
	
		object_3d_object_base[object_3d_object_current_base].lights = NULL;
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
	
		//
		// Set the world transformation matrix
		//

		{

			matrix4x4
				matrix;

			matrix[0][0] = surface->vp.attitude[0][0] * object_3d_scale.x;
			matrix[0][1] = surface->vp.attitude[0][1] * object_3d_scale.x;
			matrix[0][2] = surface->vp.attitude[0][2] * object_3d_scale.x;
			matrix[0][3] = 0;
	
			matrix[1][0] = surface->vp.attitude[1][0] * object_3d_scale.y;
			matrix[1][1] = surface->vp.attitude[1][1] * object_3d_scale.y;
			matrix[1][2] = surface->vp.attitude[1][2] * object_3d_scale.y;
			matrix[1][3] = 0;
	
			matrix[2][0] = surface->vp.attitude[2][0] * object_3d_scale.z;
			matrix[2][1] = surface->vp.attitude[2][1] * object_3d_scale.z;
			matrix[2][2] = surface->vp.attitude[2][2] * object_3d_scale.z;
			matrix[2][3] = 0;
	
			{

				vec3d
					rel;

				rel.x = visual_3d_vp->attitude[0][0] * current_object_3d_relative_position->x +
							visual_3d_vp->attitude[1][0] * current_object_3d_relative_position->y +
							visual_3d_vp->attitude[2][0] * current_object_3d_relative_position->z;
	
				rel.y = visual_3d_vp->attitude[0][1] * current_object_3d_relative_position->x +
							visual_3d_vp->attitude[1][1] * current_object_3d_relative_position->y +
							visual_3d_vp->attitude[2][1] * current_object_3d_relative_position->z;
	
				rel.z = visual_3d_vp->attitude[0][2] * current_object_3d_relative_position->x +
							visual_3d_vp->attitude[1][2] * current_object_3d_relative_position->y +
							visual_3d_vp->attitude[2][2] * current_object_3d_relative_position->z;

				matrix[3][0] = rel.x;
				matrix[3][1] = rel.y;
				matrix[3][2] = rel.z;
				matrix[3][3] = 1;
			}

			memcpy ( &d3d_matrix, matrix, sizeof ( matrix ) );
	
			f3d_set_transform ( D3DTRANSFORMSTATE_WORLD, &d3d_matrix );

			matrix[0][0] = visual_3d_vp->xv.x * 0.5;
			matrix[1][0] = visual_3d_vp->yv.x * 0.5;
			matrix[2][0] = visual_3d_vp->zv.x * 0.5;
			matrix[3][0] = 0.5;

			matrix[0][1] = -visual_3d_vp->xv.y * 0.5;
			matrix[1][1] = -visual_3d_vp->yv.y * 0.5;
			matrix[2][1] = -visual_3d_vp->zv.y * 0.5;
			matrix[3][1] = 0.5;

			matrix[0][2] = visual_3d_vp->xv.z;
			matrix[1][2] = visual_3d_vp->yv.z;
			matrix[2][2] = visual_3d_vp->zv.z;
			matrix[3][2] = 1;

			matrix[0][3] = 1.0;
			matrix[1][3] = 1.0;
			matrix[2][3] = 1.0;
			matrix[3][3] = 1.0;

			memcpy ( &d3d_matrix, matrix, sizeof ( matrix ) );
	
			f3d_set_transform ( D3DTRANSFORMSTATE_TEXTURE0, &d3d_matrix );
		}

		draw_3d_object_hardware_translucent_faces ( surface );

		surface = surface->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_object_hardware_translucent_faces ( translucent_object_surface *surface )
{

	int
		ialpha;

	current_object_3d_surface = surface->surface;

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	zbuffer_constant =				( current_object_3d_surface->detail )			?	zbuffer_constant_elevated_bias : zbuffer_constant_normal_bias;
	current_object_3d_specular =	( current_object_3d_surface->specularity )	?	specular_rendering_enabled : FALSE;

	if ( current_object_3d_surface->detail )
	{

		set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, ELEVATED_ZBIAS );
	}
	else
	{

		set_d3d_int_state ( D3DRENDERSTATE_ZBIAS, NORMAL_ZBIAS );
	}

	if ( current_object_3d_surface->polygons )
	{
	
		if ( current_object_3d_surface->translucent )
		{

			float
				alpha;
		
			alpha = current_object_3d_surface->alpha;

			asm_convert_float_to_int ( ( alpha * current_object_3d_dissolve_factor ), &ialpha );
		}
		else
		{

			ialpha = current_object_3d_dissolve_value;
		}

		if ( current_object_3d_surface->textured )
		{
	
			current_object_3d_texture = system_textures[surface->texture_index];
	
			if ( ( current_object_3d_surface->luminous ) || ( current_object_3d_surface->additive ) )
			{
	
				if ( current_object_3d_surface->additive )
				{
			
					int
						ired,
						igreen,
						iblue;
			
					asm_convert_float_to_int ( ( ( ( float ) current_object_3d_surface->red ) * current_object_3d_dissolve_factor ), &ired );
					asm_convert_float_to_int ( ( ( ( float ) current_object_3d_surface->green ) * current_object_3d_dissolve_factor ), &igreen );
					asm_convert_float_to_int ( ( ( ( float ) current_object_3d_surface->blue ) * current_object_3d_dissolve_factor ), &iblue );
			
					set_d3d_material_emissive_colour ( ired *	current_object_3d_diffuse_factor, igreen *	current_object_3d_diffuse_factor, iblue *	current_object_3d_diffuse_factor, ialpha );
				}
				else
				{
	
					set_d3d_material_emissive_colour ( current_object_3d_surface->red *	current_object_3d_diffuse_factor, current_object_3d_surface->green *	current_object_3d_diffuse_factor, current_object_3d_surface->blue *	current_object_3d_diffuse_factor, ialpha );
				}
			}
			else
			{
	
				set_d3d_material_colour ( 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, ialpha, current_object_3d_surface->specularity );
			}
	
			if ( current_object_3d_surface->texture_wrapped_u )	{ current_object_3d_texture_u_address = D3DTADDRESS_WRAP; }
			else																	{ current_object_3d_texture_u_address = D3DTADDRESS_CLAMP; }
	
			if ( current_object_3d_surface->texture_wrapped_v )	{ current_object_3d_texture_v_address = D3DTADDRESS_WRAP; }
			else																	{ current_object_3d_texture_v_address = D3DTADDRESS_CLAMP; }
	
			if ( current_object_3d_surface->texture_filtered )		{ current_object_3d_texture_filter = D3DTFG_LINEAR; }
			else																	{ current_object_3d_texture_filter = D3DTFG_POINT; }
	
			if ( current_object_3d_surface->texture_mipmapped )	{ current_object_3d_texture_mipmap = D3DTFP_POINT; }
			else																	{ current_object_3d_texture_mipmap = D3DTFP_NONE; }
	
			set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
			set_d3d_texture ( 0, current_object_3d_texture );
			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
			set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
			set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
			set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );
	
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
	
			object_3d_render_hardware_surface ( &objects_3d_data[surface->object_index] );
		}
		else
		{
	
			set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );
			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	
			if ( ( current_object_3d_surface->luminous ) || ( current_object_3d_surface->additive ) )
			{
	
				if ( current_object_3d_surface->additive )
				{
			
					int
						ired,
						igreen,
						iblue;
			
					asm_convert_float_to_int ( ( ( ( float ) current_object_3d_surface->red ) * current_object_3d_dissolve_factor ), &ired );
					asm_convert_float_to_int ( ( ( ( float ) current_object_3d_surface->green ) * current_object_3d_dissolve_factor ), &igreen );
					asm_convert_float_to_int ( ( ( ( float ) current_object_3d_surface->blue ) * current_object_3d_dissolve_factor ), &iblue );
			
					set_d3d_material_emissive_colour ( ired *	current_object_3d_diffuse_factor, igreen *	current_object_3d_diffuse_factor, iblue *	current_object_3d_diffuse_factor, ialpha );
				}
				else
				{
	
					set_d3d_material_emissive_colour ( current_object_3d_surface->red *	current_object_3d_diffuse_factor, current_object_3d_surface->green *	current_object_3d_diffuse_factor, current_object_3d_surface->blue *	current_object_3d_diffuse_factor, ialpha );
				}
			}
			else
			{
	
				set_d3d_material_colour ( current_object_3d_surface->red *	current_object_3d_diffuse_factor,
													current_object_3d_surface->green *	current_object_3d_diffuse_factor,
													current_object_3d_surface->blue *	current_object_3d_diffuse_factor,
													ialpha,
													current_object_3d_surface->specularity );
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
	
			object_3d_render_hardware_surface ( &objects_3d_data[surface->object_index] );
		}
	
		if ( ( current_object_3d_surface->polygons ) && ( current_object_3d_surface->reflectivity != 0 ) )
		{
	
			set_d3d_material_colour ( 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, 255 *	current_object_3d_diffuse_factor, current_object_3d_surface->reflectivity, current_object_3d_surface->specularity );
	
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
		
			set_d3d_int_state ( D3DRENDERSTATE_NORMALIZENORMALS, TRUE );
			set_d3d_texture_stage_state ( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR );
			set_d3d_texture_stage_state ( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 );// | D3DTTFF_PROJECTED );
	
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
			set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
			set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
			set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_filter );
			set_d3d_texture_stage_state ( 0, D3DTSS_MIPFILTER, current_object_3d_texture_mipmap );
	
			object_3d_render_hardware_surface ( &objects_3d_data[surface->object_index] );
	
			set_d3d_texture_stage_state ( 0, D3DTSS_TEXCOORDINDEX, 0 );
			set_d3d_texture_stage_state ( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

