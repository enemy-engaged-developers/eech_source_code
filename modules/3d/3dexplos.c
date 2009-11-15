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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct EXPLOSION_POINT_UV_LOOKUP
{
	int
		offset;
};

typedef struct EXPLOSION_POINT_UV_LOOKUP explosion_point_uv_lookup;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct EXPLOSION_OBJECT_POINTS_LOOKUP
{
	int
		object_number;

	struct EXPLOSION_OBJECT_POINTS_LOOKUP
		*succ;

	explosion_point_uv_lookup
		*points;
};

typedef struct EXPLOSION_OBJECT_POINTS_LOOKUP explosion_object_points_lookup;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sub_explosion ( object_3d_database_entry *obj, viewpoint *parent_viewpoint, vec3d *position, object_3d_explosion *explosion );

static void transform_3d_explosion_object ( object_3d *object, vec3d *pos, displacement_map *displacement, explosion_object_points_lookup *points_lookup, float amplitude, vec3d *camera_direction );

static void draw_3d_explosion_clipped_faces ( int object_number, vec3d *pos, light_3d_source *lights, object_3d_info *this_object_3d_info );

static void draw_3d_explosion_unclipped_faces ( int object_number, vec3d *pos, light_3d_source *lights, object_3d_info *this_object_3d_info );

static explosion_object_points_lookup * generate_explosion_object_texture_points ( int object_number, displacement_map *displacement );

static void get_displacement_map_position ( vec3d *pos, displacement_map *displacement, int *offset );

void apply_displacement_maps ( vec3d *pos, displacement_map *displacement, float amplitude );

static void set_explosion_texture_animations ( object_3d_index_numbers scene, float animation );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

explosion_object_points_lookup
	*explosion_object_points_lookup_list = NULL;

static float
	environment_x_origin,
	environment_y_origin;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_explosion ( object_3d_explosion *explosion )
{
	int
		object_number;

	vec3d
		*object_relative_position;

	vec3d
		object_camera_position,
		object_camera_direction,
		object_pos,
		object_unit_pos;

	polygon_buffer
		*translucent_sorted_buffer;

	float
		amplitude;

	int
		number_of_frames,
		displacement_frame;

	displacement_map
		*displacement;

	object_3d_scene_database_entry
		*scene;

	viewpoint
		vp;

	explosion_object_points_lookup
		*displacement_points_lookup;

	//
	// Set the scene pointer
	//

	scene = &objects_3d_scene_database[explosion->object_index];

	//
	// Set up the texture animations for this explosion
	//

	set_explosion_texture_animations ( explosion->object_index, explosion->animation );

	//
	// Set the main objects' scaling values
	//

	object_3d_scale.x = explosion->scale;
	object_3d_scale.y = explosion->scale;
	object_3d_scale.z = explosion->scale;

	{
		vec3d
			scale;

		//
		// Get the amplitude keyframes
		//

		if ( scene->number_of_displacement_amplitude_keyframes )
		{
			object_3d_sub_object_value_keyframe
				keyframe;

			calculate_value_keyframe ( scene->number_of_displacement_amplitude_keyframes, scene->displacement_amplitude_keyframes, &keyframe, explosion->animation );

			amplitude = keyframe.value;
		}
		else
		{
			amplitude = 0.5;
		}

		if ( scene->number_of_keyframes )
		{
			object_3d_sub_object_keyframe
				keyframe;

			calculate_keyframe ( scene->number_of_keyframes, scene->keyframes, &keyframe, explosion->animation );

			scale.x = keyframe.scale_x;
			scale.y = keyframe.scale_y;
			scale.z = keyframe.scale_z;
		}

		object_3d_scale.x *= scale.x;
		object_3d_scale.y *= scale.y;
		object_3d_scale.z *= scale.z;

		number_of_frames = displacement_animations[0].number_of_frames;

		asm_convert_float_to_int ( ( ( ( float ) ( number_of_frames - 1 ) ) * explosion->animation ), &displacement_frame );

		displacement = &displacement_maps[ displacement_animations[0].texture_indices[displacement_frame] ];
	}

	//
	// Set up the object drawing global variables
	//

	object_3d_points_current_base = 0;

	object_3d_object_current_base = 0;

	object_3d_light_3d_current_base = 0;

	current_object_3d_light_maps_enabled = FALSE;

	//
	// Get the object's position relative to the camera
	//

	object_relative_position = &explosion->relative_position;

	vp.position = explosion->position;
	vp.xv.x = 1;
	vp.xv.y = 0;
	vp.xv.z = 0;
	vp.yv.x = 0;
	vp.yv.y = 1;
	vp.yv.z = 0;
	vp.zv.x = 0;
	vp.zv.y = 0;
	vp.zv.z = 1;

	{
		float
			fog_intensity;

		int
			ifog_intensity;

		fog_intensity = get_fog_distance_value ( object_relative_position->z );

		asm_convert_float_to_int ( fog_intensity, &ifog_intensity );

		set_d3d_fog_face_intensity ( ifog_intensity );
	}


	//
	// Set the object dissolve variables
	//

	if ( objects_3d_scene_database[explosion->object_index].number_of_object_dissolve_keyframes )
	{
		object_3d_sub_object_value_keyframe
			keyframe;

		int
			dissolve_value;

		calculate_value_keyframe (
											objects_3d_scene_database[explosion->object_index].number_of_object_dissolve_keyframes,
											objects_3d_scene_database[explosion->object_index].object_dissolve_keyframes,
											&keyframe,
											explosion->animation );

		current_object_3d_dissolve_factor = 1.0 - keyframe.value;

		asm_convert_float_to_int ( ( current_object_3d_dissolve_factor * 255 ), &dissolve_value );

		current_object_3d_dissolve_value = dissolve_value;
	}
	else
	{
		current_object_3d_dissolve_value = 255;
		current_object_3d_dissolve_factor = 1.0;
	}

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

	rotation_3d[0][0] = visual_3d_vp->xv.x * object_3d_scale.x;
	rotation_3d[0][1] = visual_3d_vp->yv.x * object_3d_scale.x;
	rotation_3d[0][2] = visual_3d_vp->zv.x * object_3d_scale.x;

	rotation_3d[1][0] = visual_3d_vp->xv.y * object_3d_scale.y;
	rotation_3d[1][1] = visual_3d_vp->yv.y * object_3d_scale.y;
	rotation_3d[1][2] = visual_3d_vp->zv.y * object_3d_scale.y;

	rotation_3d[2][0] = visual_3d_vp->xv.z * object_3d_scale.z;
	rotation_3d[2][1] = visual_3d_vp->yv.z * object_3d_scale.z;
	rotation_3d[2][2] = visual_3d_vp->zv.z * object_3d_scale.z;

	//
	// Calculate the vector from the object to the viewpoint, in the object's view system
	//

	{
		object_pos.x = ( visual_3d_vp->x - explosion->position.x );
		object_pos.y = ( visual_3d_vp->y - explosion->position.y );
		object_pos.z = ( visual_3d_vp->z - explosion->position.z );

		object_unit_pos.x = -object_pos.x;
		object_unit_pos.y = -object_pos.y;
		object_unit_pos.z = -object_pos.z;

		normalise_any_3d_vector ( &object_unit_pos );
	}

	//
	// Get the raw object number
	//

	object_number = get_object_approximation_number ( explosion->object_index, object_relative_position->z, &object_3d_approximation_level );

	//
	// Generate the texture x, y lookups for the points in the object.
	//

	displacement_points_lookup = generate_explosion_object_texture_points ( object_number, displacement );

	{
		vec3d
			rel_pos;

		//
		// Calculate the relative camera position in the object viewspace
		//

		rel_pos.x = visual_3d_vp->x - explosion->position.x;
		rel_pos.y = visual_3d_vp->y - explosion->position.y;
		rel_pos.z = visual_3d_vp->z - explosion->position.z;

		object_camera_position.x = rel_pos.x;
		object_camera_position.y = rel_pos.y;
		object_camera_position.z = rel_pos.z;

		object_camera_direction.x = visual_3d_vp->zv.x;
		object_camera_direction.y = visual_3d_vp->zv.y;
		object_camera_direction.z = visual_3d_vp->zv.z;
	}

	//
	// Calculate the x, y offsets for lookup into the displacement maps
	//



	//
	//	Set up this objects' object info structure
	//

	object_3d_object_base[object_3d_object_current_base].lights = current_3d_lights;
	object_3d_object_base[object_3d_object_current_base].camera_position = object_camera_position;
	object_3d_object_base[object_3d_object_current_base].camera_direction = object_camera_direction;
	object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;
	object_3d_object_base[object_3d_object_current_base].object_number = object_number;
	object_3d_object_base[object_3d_object_current_base].object_vp = NULL;	//&obj->vp;

	current_object_3d_object_base = &object_3d_object_base[object_3d_object_current_base];

	//
	// Set up the face sorting variables
	//

	translucent_sorted_buffer = get_translucent_sorted_polygon_buffer ();

	//
	// Reset the temporary buffered faces
	//

	reset_temporary_buffered_translucent_polygons ();

	//
	// Now start transforming etc
	//

	current_object_3d_light_maps_enabled = TRUE;

	if ( objects_3d_data[object_number].number_of_points )
	{
		object_3d_scale.x = explosion->scale;
		object_3d_scale.y = explosion->scale;
		object_3d_scale.z = explosion->scale;

		transform_3d_explosion_object ( &objects_3d_data[object_number],
														object_relative_position,
														displacement,
														displacement_points_lookup,
														amplitude,
														&object_camera_position );

		draw_3d_explosion_clipped_faces ( object_number, object_relative_position, current_3d_lights, current_object_3d_object_base );
	}

	//
	// Adjust the memory pointers for any sub objects
	//

	if ( scene->number_of_sub_objects )
	{
		int
			count;

		for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
		{

			draw_sub_explosion ( &scene->sub_objects[count], &vp, object_relative_position, explosion );
		}
	}

	//
	// Now finish sorting the translucent polygons and render them now
	//

	if ( finalise_translucent_sorted_polygon_buffer ( translucent_sorted_buffer ) )
	{
		draw_polygon_buffer ( translucent_sorted_buffer );

		remove_translucent_polygon_buffer ( translucent_sorted_buffer );
	}

	//
	// If there are any temporary tranlucent polygons, draw them now
	//

	if ( get_number_of_temporary_translucent_polygons () )
	{
		//
		// No need to set translucency on, its already on! but turn off specular
		//

		set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );

		draw_temporary_translucent_polygons ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_sub_explosion ( object_3d_database_entry *obj, viewpoint *parent_viewpoint, vec3d *position, object_3d_explosion *explosion )
{
	int
		count,
		object_3d_object_initial_base,
		object_3d_light_3d_initial_base,
		object_number;

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
		sub_pos;

	light_3d_source
		*this_light,
		*prev_light,
		*light_ptr,
		*light;

	viewpoint
		vp;

	float
		old_current_object_3d_dissolve_factor;

	//
	// Remember what temporary objects & lights we have used up to now
	//

	object_3d_object_initial_base = object_3d_object_current_base;

	object_3d_light_3d_initial_base = object_3d_light_3d_current_base,

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

	{
		vec3d
			scale;

		if ( obj->number_of_keyframes )
		{
			object_3d_sub_object_keyframe
				keyframe;

			calculate_keyframe ( obj->number_of_keyframes, obj->keyframes, &keyframe, explosion->animation );

			scale.x = keyframe.scale_x;
			scale.y = keyframe.scale_y;
			scale.z = keyframe.scale_z;
		}

		object_3d_scale.x *= scale.x;
		object_3d_scale.y *= scale.y;
		object_3d_scale.z *= scale.z;
	}

	//
	// Get the positions & object number
	//

//	rel = &obj->relative_position;

	object_number = obj->index;

	//
	// Set the object dissolve variables
	//


	//
	// Calculate the object's position relative to the viewer.
	//
	// NOTE:
	//		BECAUSE THIS USES THE ROTATION_3D MATRIX, IT TAKES INTO ACCOUNT THE PARENT'S SCALE
	//

	sub_pos.x = ( ( obj->keyframes->x * rotation_3d[0][0] ) +
					  ( obj->keyframes->y * rotation_3d[1][0] ) +
					  ( obj->keyframes->z * rotation_3d[2][0] ) );
	sub_pos.y = ( ( obj->keyframes->x * rotation_3d[0][1] ) +
					  ( obj->keyframes->y * rotation_3d[1][1] ) +
					  ( obj->keyframes->z * rotation_3d[2][1] ) );
	sub_pos.z = ( ( obj->keyframes->x * rotation_3d[0][2] ) +
					  ( obj->keyframes->y * rotation_3d[1][2] ) +
					  ( obj->keyframes->z * rotation_3d[2][2] ) );

	sub_pos.x += position->x;
	sub_pos.y += position->y;
	sub_pos.z += position->z;

	//
	// Calculate the object's real world position
	//

	scaled_relative_position.x = obj->keyframes->x * object_3d_scale.x;
	scaled_relative_position.y = obj->keyframes->y * object_3d_scale.y;
	scaled_relative_position.z = obj->keyframes->z * object_3d_scale.z;

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
	// Alter the object dissolve
	//

	old_current_object_3d_dissolve_factor = current_object_3d_dissolve_factor;

	if ( obj->number_of_object_dissolve_keyframes )
	{

		object_3d_sub_object_value_keyframe
			keyframe;

		int
			dissolve_value;

		float
			factor;

		calculate_value_keyframe ( obj->number_of_object_dissolve_keyframes, obj->object_dissolve_keyframes, &keyframe, explosion->animation );

		factor = 1.0 - keyframe.value;

		current_object_3d_dissolve_factor *= factor;

		asm_convert_float_to_int ( ( current_object_3d_dissolve_factor * 255 ), &dissolve_value );

		current_object_3d_dissolve_value = dissolve_value;
	}
	else
	{
		current_object_3d_dissolve_value = 255;
		current_object_3d_dissolve_factor = 1.0;
	}

	//
	// Compute the sub object's relative attitude matrix
	//

	get_3d_transformation_matrix ( relative_attitude, obj->keyframes->heading, -obj->keyframes->pitch, -obj->keyframes->roll );

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
		}

		//
		// Rotate the light source vector to be relative to the object.
		//

		light_ptr = current_3d_lights;

		prev_light = NULL;

		light = NULL;

		if ( light_ptr )
		{

			light = &light_3d_array[object_3d_light_3d_current_base];

			while ( light_ptr )
			{
				float
					lx,
					ly,
					lz;

				this_light = &light_3d_array[object_3d_light_3d_current_base];

				object_3d_light_3d_current_base++;

				if ( prev_light )
				{
					prev_light->succ = this_light;
				}

				this_light->pred = prev_light;
				this_light->succ = NULL;

				this_light->colour.red = light_ptr->colour.red;
				this_light->colour.green = light_ptr->colour.green;
				this_light->colour.blue = light_ptr->colour.blue;
				this_light->intensity = this_light->colour.red * 0.30 + this_light->colour.green * 0.59 + this_light->colour.blue * 0.11;

				lx = ( light_ptr->lx * vp.attitude[0][0] );
				lx += ( light_ptr->ly * vp.attitude[0][1] );
				lx += ( light_ptr->lz * vp.attitude[0][2] );

				ly = ( light_ptr->lx * vp.attitude[1][0] );
				ly += ( light_ptr->ly * vp.attitude[1][1] );
				ly += ( light_ptr->lz * vp.attitude[1][2] );

				lz = ( light_ptr->lx * vp.attitude[2][0] );
				lz += ( light_ptr->ly * vp.attitude[2][1] );
				lz += ( light_ptr->lz * vp.attitude[2][2] );

				this_light->lx = lx;
				this_light->ly = ly;
				this_light->lz = lz;

				//
				// Generate a highlight vector
				//

				this_light->highlight_vector.x = ( lx - object_unit_pos.x );
				this_light->highlight_vector.y = ( ly - object_unit_pos.y );
				this_light->highlight_vector.z = ( lz - object_unit_pos.z );

				normalise_any_3d_vector ( &this_light->highlight_vector );

				prev_light = this_light;

				light_ptr = light_ptr->succ;
			}
		}

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

			vec3d
				scale;

			//
			// Setup the objects scaling information
			//

			scale.x = 2.0;
			scale.y = 2.0;
			scale.z = 2.0;

			if ( !get_scaled_object_3d_outcode ( object_number, &sub_pos, &scale, &object_outcode ) )
//			if ( !get_object_3d_outcode ( object_number, &sub_pos, &object_outcode ) )
			{
				if ( object_outcode )
				{
					transform_3d_object ( &objects_3d_data[object_number], &sub_pos, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );
				}
				else
				{
					transform_unclipped_3d_object ( &objects_3d_data[object_number], &sub_pos, object_3d_object_base[object_3d_object_current_base].lights, &object_camera_position, object_3d_points_current_base );
				}

				//
				// Render the faces now.
				//

				if ( object_outcode )
				{
					draw_3d_explosion_clipped_faces ( object_number, &sub_pos, object_3d_object_base[object_3d_object_current_base].lights, current_object_3d_object_base );
				}
				else
				{
					draw_3d_explosion_unclipped_faces ( object_number, &sub_pos, object_3d_object_base[object_3d_object_current_base].lights, current_object_3d_object_base );
				}
			}
		}
	}

	//
	// Recurse down any sub objects
	//

	if ( obj->number_of_sub_objects )
	{

		for ( count = ( obj->number_of_sub_objects -1 ); count >= 0; count-- )
		{
			draw_sub_explosion ( &obj->sub_objects[count], &vp, &sub_pos, explosion );
		}
	}

	//
	// Restore object dissolve
	//

	{
		int
			dissolve_value;

		current_object_3d_dissolve_factor = old_current_object_3d_dissolve_factor;

		asm_convert_float_to_int ( ( current_object_3d_dissolve_factor * 255 ), &dissolve_value );

		current_object_3d_dissolve_value = dissolve_value;
	}

	//
	// Restore the object rotation matrix
	//

	memcpy ( rotation_3d, temp_matrix, sizeof ( matrix3x3 ) );

	memcpy ( &object_3d_scale, &temp_scale, sizeof ( vec3d ) );

	//
	// Release all the temporary lights & objects used.
	//

	object_3d_object_current_base = object_3d_object_initial_base;

	object_3d_light_3d_current_base = object_3d_light_3d_initial_base;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_explosion_object ( object_3d *object, vec3d *pos, displacement_map *displacement, explosion_object_points_lookup *points_lookup, float amplitude, vec3d *camera_direction )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		*result_2d_points,
		*last_transformed_point,
		temp_last_transformed_point;

	unsigned char
		*result_outcode,
		*last_transformed_point_outcode,
		temp_last_transformed_point_outcode;

	float
		xmax,
		ymax,
		zmax,
		pos_x,
		pos_y,
		pos_z,
		oxmax,
		oxmin,
		oymax,
		oymin,
		x_factor,
		y_factor,
		z_factor;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	illuminate_object_point_normals ( object->point_normals, object->number_of_lighting_normals, current_3d_lights, 0 );
/*
	if ( camera_direction )
	{

		calculate_object_normal_factors ( object->point_normals + object->culling_normals_offset,
														object->number_of_point_normals - object->culling_normals_offset,
														camera_direction, &object->bounding_box, object->culling_normals_offset );
	}
*/
	number_of_points = object->number_of_points;

	points = object->points;

	result_3d_points = transformed_3d_3d_points;

	result_2d_points = transformed_3d_2d_points;

	result_outcode = transformed_3d_point_outcodes;

	last_transformed_point = &temp_last_transformed_point;

	last_transformed_point_outcode = &temp_last_transformed_point_outcode;

	environment_x_origin = active_3d_environment->x_origin;
	environment_y_origin = active_3d_environment->y_origin;

	pos_x = pos->x * active_3d_environment->screen_i_scale;
	pos_y = pos->y * active_3d_environment->screen_j_scale;
	pos_z = pos->z;

	xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
	ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
	zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[0][2] = rotation_3d[0][2];

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = rotation_3d[1][2];

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[2][2] = rotation_3d[2][2];

	x_factor = xmax / 32767.0;
	y_factor = ymax / 32767.0;
	z_factor = zmax / 32767.0;

	amplitude *= 2.0 / 255.0;

	for ( count = 0; count < number_of_points; count++ )
	{
		vec3d
			pos;

		float
			x,
			y,
			z,
			displacement_factor;

		pos.x = points->x;
		pos.y = points->y;
		pos.z = points->z;

		pos.x *= x_factor;
		pos.y *= y_factor;
		pos.z *= z_factor;

		//
		// Apply the displacement mapping
		//

		displacement_factor = displacement->data[points_lookup->points[count].offset];

		displacement_factor *= amplitude;

		pos.x += displacement_factor * pos.x;
		pos.y += displacement_factor * pos.y;
		pos.z += displacement_factor * pos.z;

		//
		// Rotate the point
		//

		x = pos_x + pos.x * scaled_rotation[0][0] + pos.y * scaled_rotation[1][0] + pos.z * scaled_rotation[2][0];
		y = pos_y + pos.x * scaled_rotation[0][1] + pos.y * scaled_rotation[1][1] + pos.z * scaled_rotation[2][1];
		z = pos_z + pos.x * scaled_rotation[0][2] + pos.y * scaled_rotation[1][2] + pos.z * scaled_rotation[2][2];

		result_3d_points->x = x;
		result_3d_points->y = y;
		result_2d_points->z = z;

		if ( *( ( int * ) &result_2d_points->z ) >= *( ( int * ) &clip_hither ) )
		{
			float
				q,
				i,
				j;

			oxmax = active_viewport.x_max - last_transformed_point->i;
			oxmin = last_transformed_point->i - active_viewport.x_min;
			oymax = active_viewport.y_max - last_transformed_point->j;
			oymin = last_transformed_point->j - active_viewport.y_min;

			ixmax = *( ( unsigned int * ) &oxmax );
			ixmin = *( ( unsigned int * ) &oxmin );
			iymax = *( ( unsigned int * ) &oymax );
			iymin = *( ( unsigned int * ) &oymin );

			q = 1.0 / result_2d_points->z;

			ixmin >>= 31;
			iymin &= 0x80000000;
			ixmax >>= 29;
			iymax &= 0x80000000;
			iymin >>= 30;
			ixmin &= 0x00000001;
			iymax >>= 28;
			ixmax &= 0x00000004;
			ixmin |= iymin;
			ixmax |= iymax;
			*last_transformed_point_outcode = ( ixmin | ixmax );

//				start_float_divide ( result_2d_points->z, 1.0 );

//				*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			last_transformed_point = result_2d_points;

			last_transformed_point_outcode = result_outcode;

//				q = end_float_divide ();

			i = ( result_3d_points->x * q );
			j = ( result_3d_points->y * q );

			result_2d_points->q = q;
			result_2d_points->j = environment_y_origin - j;
			result_2d_points->i = environment_x_origin + i;
		}
		else
		{
			*result_outcode = CLIP_HITHER;
		}

		result_3d_points++;
		result_2d_points++;
		result_outcode++;
		points++;
	}

	oxmax = active_viewport.x_max - last_transformed_point->i;
	oxmin = last_transformed_point->i - active_viewport.x_min;
	oymax = active_viewport.y_max - last_transformed_point->j;
	oymin = last_transformed_point->j - active_viewport.y_min;

	ixmax = *( ( int * ) &oxmax );
	ixmin = *( ( int * ) &oxmin );
	iymax = *( ( int * ) &oymax );
	iymin = *( ( int * ) &oymin );

	*last_transformed_point_outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

	//
	// Set back the fpu precision mode.
	//

	set_fpu_precision_mode_double ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_explosion_clipped_faces ( int object_number, vec3d *pos, light_3d_source *lights, object_3d_info *this_object_3d_info )
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

		if ( current_object_3d_surface->detail )				{ zbuffer_constant = zbuffer_constant_elevated_bias; }
		else																{ zbuffer_constant = zbuffer_constant_normal_bias; }

		if ( current_object_3d_surface->specularity )		{ current_object_3d_specular = specular_rendering_enabled; }
		else																{ current_object_3d_specular = FALSE; }

		//
		// Do deferred state changes
		//

		reset_deferred_state_changes ();

		set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );

		if ( current_object_3d_surface->textured )
		{
			if ( current_object_3d_surface->texture_wrapped_u )	{ current_object_3d_texture_u_address = D3DTADDRESS_WRAP; }
			else																	{ current_object_3d_texture_u_address = D3DTADDRESS_CLAMP; }

			if ( current_object_3d_surface->texture_wrapped_v )	{ current_object_3d_texture_v_address = D3DTADDRESS_WRAP; }
			else																	{ current_object_3d_texture_v_address = D3DTADDRESS_CLAMP; }

			if ( current_object_3d_surface->texture_filtered )		{ current_object_3d_texture_filter = D3DTFG_LINEAR; }
			else																	{ current_object_3d_texture_filter = D3DTFG_POINT; }

			if ( current_object_3d_surface->texture_mipmapped )	{ current_object_3d_texture_mipmap = D3DTFN_LINEAR; }
			else																	{ current_object_3d_texture_mipmap = D3DTFN_POINT; }

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

			set_deferred_d3d_texture ( 0, current_object_3d_texture );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_mipmap );

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

				if ( current_object_3d_surface->luminosity_texture_mipmapped )	{ current_object_3d_luminosity_texture_mipmap = D3DTFN_LINEAR; }
				else																				{ current_object_3d_luminosity_texture_mipmap = D3DTFN_POINT; }

				if ( current_object_3d_surface->smoothed )
				{
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( current_object_3d_surface->polygons )
						{
							if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
						else
						{
							if ( !outcode_3d_object_surface_polygon ( 2, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
							current_object_3d_point_list += 2;
						}
					}
				}
			}
			else
			{
				if ( current_object_3d_surface->smoothed )
				{
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( current_object_3d_surface->polygons )
						{
							if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
						else
						{
							if ( !outcode_3d_object_surface_polygon ( 2, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
							current_object_3d_point_list += 2;
						}
					}
				}
			}
		}
		else
		{
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
			set_deferred_d3d_texture ( 0, NULL );
			if ( current_object_3d_surface->smoothed )
			{
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( current_object_3d_surface->polygons )
					{
						if ( !outcode_3d_object_surface_polygon ( current_object_3d_faces->number_of_points, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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
					else
					{

						if ( !outcode_3d_object_surface_polygon ( 2, this_object_3d_info->points_base, &current_object_3d_outcode ) )
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

void draw_3d_explosion_unclipped_faces ( int object_number, vec3d *pos, light_3d_source *lights, object_3d_info *this_object_3d_info )
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

		if ( current_object_3d_surface->detail )				{ zbuffer_constant = zbuffer_constant_elevated_bias; }
		else																{ zbuffer_constant = zbuffer_constant_normal_bias; }

		if ( current_object_3d_surface->specularity )		{ current_object_3d_specular = specular_rendering_enabled; }
		else																{ current_object_3d_specular = FALSE; }

		reset_deferred_state_changes ();

		set_deferred_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, current_object_3d_specular );

		if ( current_object_3d_surface->textured )
		{
			if ( current_object_3d_surface->texture_wrapped_u )	{ current_object_3d_texture_u_address = D3DTADDRESS_WRAP; }
			else																	{ current_object_3d_texture_u_address = D3DTADDRESS_CLAMP; }

			if ( current_object_3d_surface->texture_wrapped_v )	{ current_object_3d_texture_v_address = D3DTADDRESS_WRAP; }
			else																	{ current_object_3d_texture_v_address = D3DTADDRESS_CLAMP; }

			if ( current_object_3d_surface->texture_filtered )		{ current_object_3d_texture_filter = D3DTFG_LINEAR; }
			else																	{ current_object_3d_texture_filter = D3DTFG_POINT; }

			if ( current_object_3d_surface->texture_mipmapped )	{ current_object_3d_texture_mipmap = D3DTFN_LINEAR; }
			else																	{ current_object_3d_texture_mipmap = D3DTFN_POINT; }

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

			set_deferred_d3d_texture ( 0, current_object_3d_texture );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, current_object_3d_texture_u_address );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, current_object_3d_texture_v_address );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, current_object_3d_texture_filter );
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, current_object_3d_texture_mipmap );

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

				if ( current_object_3d_surface->luminosity_texture_mipmapped )	{ current_object_3d_luminosity_texture_mipmap = D3DTFN_LINEAR; }
				else																				{ current_object_3d_luminosity_texture_mipmap = D3DTFN_POINT; }

				if ( current_object_3d_surface->smoothed )
				{
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						wrender_unclipped_3d_object_gouraud_textured_lightmap_polygon ( current_object_3d_faces );
						current_object_3d_point_list += current_object_3d_faces->number_of_points;
						current_object_3d_faces++;
					}
				}
				else
				{
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( current_object_3d_surface->polygons )
						{
							wrender_unclipped_3d_object_textured_lightmap_polygon ( current_object_3d_faces );
							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
						else
						{
							wrender_unclipped_3d_object_textured_line ();
							current_object_3d_point_list += 2;
						}
					}
				}
			}
			else
			{
				if ( current_object_3d_surface->smoothed )
				{
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( current_object_3d_specular )
						{
							wrender_unclipped_3d_object_gouraud_textured_polygon ( current_object_3d_faces );
						}
						else
						{
							wrender_unclipped_3d_object_gouraud_textured_nospecular_polygon ( current_object_3d_faces );
						}

						current_object_3d_point_list += current_object_3d_faces->number_of_points;
						current_object_3d_faces++;
					}
				}
				else
				{
					set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
					for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
					{
						if ( current_object_3d_surface->polygons )
						{
							wrender_unclipped_3d_object_textured_polygon ( current_object_3d_faces );
							current_object_3d_face_normal_list++;
							current_object_3d_point_list += current_object_3d_faces->number_of_points;
							current_object_3d_faces++;
						}
						else
						{
							wrender_unclipped_3d_object_textured_line ();
							current_object_3d_point_list += 2;
						}
					}
				}
			}
		}
		else
		{
			set_deferred_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
			set_deferred_d3d_texture ( 0, NULL );
			if ( current_object_3d_surface->smoothed )
			{
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					wrender_unclipped_3d_object_gouraud_polygon ( current_object_3d_faces );
					current_object_3d_point_list += current_object_3d_faces->number_of_points;
					current_object_3d_faces++;
				}
			}
			else
			{
				set_deferred_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( current_object_3d_surface->polygons )
					{
						wrender_unclipped_3d_object_polygon ( current_object_3d_faces );
						current_object_3d_face_normal_list++;
						current_object_3d_point_list += current_object_3d_faces->number_of_points;
						current_object_3d_faces++;
					}
					else
					{
						wrender_unclipped_3d_object_plain_line ();
						current_object_3d_point_list += 2;
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

explosion_object_points_lookup * generate_explosion_object_texture_points ( int object_number, displacement_map *displacement )
{
	explosion_object_points_lookup
		*list;

	list = explosion_object_points_lookup_list;

	while ( list )
	{
		if ( list->object_number == object_number )
		{
			return ( list );
		}

		list = list->succ;
	}

	//
	// Not found the list - create one.
	//

	{
		int
			count;

		vec3d
			point;

		float
			xmax,
			ymax,
			zmax;

		list = ( explosion_object_points_lookup * ) safe_malloc ( sizeof ( explosion_object_points_lookup ) );

		list->points = ( explosion_point_uv_lookup * ) safe_malloc ( objects_3d_data[object_number].number_of_points * sizeof ( explosion_point_uv_lookup ) );

		xmax = max ( fabs ( objects_3d_data[object_number].bounding_box.xmin ), fabs ( objects_3d_data[object_number].bounding_box.xmax ) );
		ymax = max ( fabs ( objects_3d_data[object_number].bounding_box.ymin ), fabs ( objects_3d_data[object_number].bounding_box.ymax ) );
		zmax = max ( fabs ( objects_3d_data[object_number].bounding_box.zmin ), fabs ( objects_3d_data[object_number].bounding_box.zmax ) );

		xmax /= 32767.0;
		ymax /= 32767.0;
		zmax /= 32767.0;

		for ( count = 0; count < objects_3d_data[object_number].number_of_points; count++ )
		{
			point.x = objects_3d_data[object_number].points[count].x;
			point.y = objects_3d_data[object_number].points[count].y;
			point.z = objects_3d_data[object_number].points[count].z;

			point.x *= xmax;
			point.y *= ymax;
			point.z *= zmax;

			get_displacement_map_position ( &point, //( vec3d * ) &objects_3d_data[object_number].points[count],
														displacement,
														&list->points[count].offset );
		}

		list->object_number = object_number;

		list->succ = explosion_object_points_lookup_list;

		explosion_object_points_lookup_list = list;

		debug_log ( "Generated list for object %d", object_number );

		return ( list );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_displacement_map_position ( vec3d *pos, displacement_map *displacement, int *offset )
{
	float
		heading,
		pitch,
		length;

	int
		displacement_x,
		displacement_y;

	vec3d
		normalised_pos;

	normalised_pos = *pos;

	length = normalise_any_3d_vector ( &normalised_pos );

	get_heading_and_pitch_from_3d_unit_vector ( &normalised_pos, &heading, &pitch );

	heading += PI;
	pitch += PI/2;

	heading /= PI2;
	pitch /= PI;

	ASSERT ( ( pitch >= 0 ) && ( pitch <= 1 ) );
	ASSERT ( ( heading >= 0 ) && ( heading <= 1 ) );

	asm_convert_float_to_int ( ( heading * ( displacement->width - 1 ) ), &displacement_x );
	asm_convert_float_to_int ( ( pitch * ( displacement->height - 1 ) ), &displacement_y );

	*offset = ( ( displacement_y * displacement->width ) + displacement_x );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_displacement_maps ( vec3d *pos, displacement_map *displacement, float amplitude )
{
	float
		heading,
		pitch,
		length,
		factor;

	int
		displacement_x,
		displacement_y;

	vec3d
		normalised_pos;

	normalised_pos = *pos;

	length = normalise_any_3d_vector ( &normalised_pos );

	get_heading_and_pitch_from_3d_unit_vector ( &normalised_pos, &heading, &pitch );

	heading += PI;
	pitch += PI/2;

	heading /= PI2;
	pitch /= PI;

	ASSERT ( ( pitch >= 0 ) && ( pitch <= 1 ) );
	ASSERT ( ( heading >= 0 ) && ( heading <= 1 ) );

	asm_convert_float_to_int ( ( heading * ( displacement->width - 1 ) ), &displacement_x );
	asm_convert_float_to_int ( ( pitch * ( displacement->height - 1 ) ), &displacement_y );

	factor = displacement->data[ ( ( displacement_y * displacement->width ) + displacement_x ) ];

	factor /= 255.0;

	factor *= amplitude * 2;

	pos->x += factor * length * normalised_pos.x;
	pos->y += factor * length * normalised_pos.y;
	pos->z += factor * length * normalised_pos.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_explosion_texture_animations ( object_3d_index_numbers scene, float animation )
{
	if ( objects_3d_scene_database[scene].number_of_texture_animations )
	{
		int
			count;

		for ( count = 0; count < objects_3d_scene_database[scene].number_of_texture_animations; count++ )
		{
			int
				texture_animation_index,
				number_of_frames,
				animation_frame;

			texture_animation_index = objects_3d_scene_database[scene].texture_animations[count];

			number_of_frames = texture_animations[texture_animation_index].number_of_frames;

			asm_convert_float_to_int ( ( ( ( float ) ( number_of_frames - 1 ) ) * animation ), &animation_frame );

			texture_animations[texture_animation_index].current_frame = animation_frame;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

