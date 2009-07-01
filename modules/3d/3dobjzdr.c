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

static void draw_z_sorted_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, light_3d_source *parent_lights, vec3d *position );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_z_sorted_3d_object ( object_3d_instance *obj )
{
	int
		object_number,
		draw_sub_objects,
		count,
		temp,
		num_faces;

	object_3d_face
		*faces;

	light_3d_source
		*this_light,
		*prev_light,
		*light_ptr,
		*light;

	vec3d
		*pos;

	vec3d
		object_pos,
		object_unit_pos;

	polygon_buffer
		*translucent_buffer;

	object_3d_scene_database_entry
		*scene;

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


	//
	// Set the object dissolve variables
	//

	current_object_3d_dissolve_factor = 1.0;
	current_object_3d_dissolve_value = 255;

	//
	// Turn lightmaps off
	//

	current_object_3d_light_maps_enabled = FALSE;

	//
	// Calculate the object's position relative to the view.
	//

	pos = &obj->view_position;

	{
		float
			fog_intensity;

		int
			ifog_intensity;

		fog_intensity = get_fog_distance_value ( pos->z );

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
	}

	//
	// Get the object number
	//

	object_number = get_object_approximation_number ( obj->object_number, pos->z, &draw_sub_objects );

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

			if ( light_ptr->type == LIGHT_3D_TYPE_POINT )
			{
				vec3d
					vector;

				float
					distance;

				//
				// Work out the distance from object to light source
				//

				vector.x = - light_ptr->light_position.x + obj->vp.x;
				vector.y = - light_ptr->light_position.y + obj->vp.y;
				vector.z = - light_ptr->light_position.z + obj->vp.z;

				lx = vector.x * vector.x;
				ly = vector.y * vector.y;
				lz = vector.z * vector.z;

				distance = ( lx + ly + lz );

				if ( distance < light_ptr->radius )
				{
					distance = 1 - ( distance / light_ptr->radius );

					this_light = &light_3d_array[object_3d_light_3d_current_base];

					object_3d_light_3d_current_base++;

					if ( prev_light )
					{
						prev_light->succ = this_light;
					}

					this_light->pred = prev_light;
					this_light->succ = NULL;


					this_light->colour.red = light_ptr->colour.red * distance;
					this_light->colour.green = light_ptr->colour.green * distance;
					this_light->colour.blue = light_ptr->colour.blue * distance;
//					this_light->colour.intensity = light_ptr->colour.intensity * distance;

					normalise_any_3d_vector ( &vector );

					lx = ( vector.x * obj->vp.attitude[0][0] );
					lx += ( vector.y * obj->vp.attitude[0][1] );
					lx += ( vector.z * obj->vp.attitude[0][2] );

					ly = ( vector.x * obj->vp.attitude[1][0] );
					ly += ( vector.y * obj->vp.attitude[1][1] );
					ly += ( vector.z * obj->vp.attitude[1][2] );

					lz = ( vector.x * obj->vp.attitude[2][0] );
					lz += ( vector.y * obj->vp.attitude[2][1] );
					lz += ( vector.z * obj->vp.attitude[2][2] );

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
				}
			}
			else
			{
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
//				this_light->colour.intensity = light_ptr->colour.intensity;

				lx = ( light_ptr->lx * obj->vp.attitude[0][0] );
				lx +=  ( light_ptr->ly * obj->vp.attitude[0][1] );
				lx += ( light_ptr->lz * obj->vp.attitude[0][2] );

				ly = ( light_ptr->lx * obj->vp.attitude[1][0] );
				ly += ( light_ptr->ly * obj->vp.attitude[1][1] );
				ly += ( light_ptr->lz * obj->vp.attitude[1][2] );


				lz = ( light_ptr->lx * obj->vp.attitude[2][0] );
				lz += ( light_ptr->ly * obj->vp.attitude[2][1] );
				lz += ( light_ptr->lz * obj->vp.attitude[2][2] );

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
			}

			light_ptr = light_ptr->succ;
		}
	}

	//
	//	Set up this objects' object info structure
	//

	object_3d_object_base[object_3d_object_current_base].lights = light;

	object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;

	object_3d_object_base[object_3d_object_current_base].object_number = object_number;

	current_object_3d_object_base = &object_3d_object_base[object_3d_object_current_base];

	//
	// Set up the face sorting variables
	//

	num_faces = objects_3d_data[object_number].number_of_faces;

	reset_3d_face_sorting ();

	//
	// Insert this objects' faces into the sorted list.
	//

	faces = objects_3d_data[object_number].faces;

	if ( objects_3d_data[object_number].number_of_points )
	{
		object_short_3d_point
			*object_points;

		point_3d_plain_reference
			*plain_point_list;

		face_surface_description
			*surfaces;

		int
			surface,
			surface_face_count,
			point_reference_index,
			gouraud_point_index,
			face_normal_index,
			texture_point_index;

		surface = 0;
		point_reference_index = 0;
		gouraud_point_index = 0;
		face_normal_index = 0;
		texture_point_index = 0;

		object_points = objects_3d_data[object_number].points;

		plain_point_list = NULL;	//objects_3d_data[object_number].object_faces_point_plain_list;

		surfaces = objects_3d_data[object_number].surfaces;

		surface_face_count = surfaces[surface].number_of_faces;

		for ( count = num_faces; count > 0; count-- )
		{
			if ( surface_face_count == 0 )
			{
				surface++;
				surface_face_count = surfaces[surface].number_of_faces;
			}

			if ( surfaces[surface].polygons )
			{
				float
					tmp;

				vec3d
					true_depth_point;

				{
					point_3d_plain_reference
						*point_list;

					point_list = &plain_point_list[point_reference_index];

					true_depth_point.x = object_points[point_list[0].point].x;
					true_depth_point.y = object_points[point_list[0].point].y;
					true_depth_point.z = object_points[point_list[0].point].z;

					true_depth_point.x += object_points[point_list[1].point].x;
					true_depth_point.y += object_points[point_list[1].point].y;
					true_depth_point.z += object_points[point_list[1].point].z;

					true_depth_point.x += object_points[point_list[2].point].x;
					true_depth_point.y += object_points[point_list[2].point].y;
					true_depth_point.z += object_points[point_list[2].point].z;

					point_list += 3;

					for ( temp = faces->number_of_points; temp > 3; temp-- )
					{
						true_depth_point.x += object_points[point_list->point].x;
						true_depth_point.y += object_points[point_list->point].y;
						true_depth_point.z += object_points[point_list->point].z;

						point_list++;
					}

					tmp = true_depth_point.x * rotation_3d[0][2];
					tmp += true_depth_point.y * rotation_3d[1][2];
					tmp += true_depth_point.z * rotation_3d[2][2];
					tmp *= one_over_table[faces->number_of_points];
					tmp += pos->z;

					//
					// Just use the binary representation of the float z value for z-sorting
					//

					insert_z_sorted_3d_face ( faces, *( ( int * ) &tmp ), surface, point_reference_index, gouraud_point_index, face_normal_index, texture_point_index, current_object_3d_object_base );
//					insert_z_sorted_3d_face ( faces, *( ( int * ) &tmp ), surface, point_reference_index, gouraud_point_index, 0, texture_point_index, this_object_3d_info );
				}
			}
			else
			{
	/*
				float
					tmp;

				point_3d_plain_reference
					*point_list;

				point_list = &plain_point_list[faces->point_reference_index];

				depth_point = &object_points[point_list->point];

				tmp = pos->z;

				point_list++;

				tmp += depth_point->x * rotation_3d[0][2];

				tmp += depth_point->y * rotation_3d[1][2];

				tmp += depth_point->z * rotation_3d[2][2];

				//
				// Just use the binary representation of the float z value for z-sorting
				//

				insert_z_sorted_3d_face ( faces, * ( ( int * ) &tmp ), this_object_3d_info );
			*/
			}

			if ( surfaces[surface].polygons )
			{
				point_reference_index += faces->number_of_points;
				if ( !surfaces[surface].smoothed )
				{
					face_normal_index++;
				}
			}
			else
			{
				point_reference_index += 2;
			}

			if ( surfaces[surface].textured )
			{
				texture_point_index += faces->number_of_points;
			}

			if ( surfaces[surface].smoothed )
			{
				gouraud_point_index += faces->number_of_points;
			}

			faces++;
			surface_face_count--;
		}
	}

	faces = objects_3d_data[object_number].faces;

	//
	// Transform the object's shape data
	//

	if ( objects_3d_data[object_number].number_of_points )
	{
		illuminate_3d_object ( &objects_3d_data[object_number], pos, light, NULL, object_3d_points_current_base );
		transform_3d_object ( &objects_3d_data[object_number], pos, light, NULL, object_3d_points_current_base);
	}

	//
	// Adjust the memory pointers for any sub objects
	//

	object_3d_object_current_base ++;

	object_3d_points_current_base += objects_3d_data[object_number].number_of_points;

	//
	// Recurse down any sub objects
	//

	if ( ( draw_sub_objects ) && ( scene->number_of_sub_objects != 0 ) )
	{
		for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
		{
			if ( obj->sub_objects[count].visible_object )
			{
				draw_z_sorted_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count], &obj->vp, current_object_3d_object_base->lights, pos );
			}
		}
	}

	//
	// Start sorting the translucent polygons
	//

	translucent_buffer = get_translucent_sorted_polygon_buffer ();

	//
	//	Ok, now we're ready to draw the actual faces.
	//

	render_3d_object_faces ();

	if ( finalise_translucent_sorted_polygon_buffer ( translucent_buffer ) )
	{
//		set_d3d_transparency_on ();

		draw_polygon_buffer ( translucent_buffer );

//		set_d3d_transparency_off ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_z_sorted_sub_object ( object_3d_sub_instance *obj, object_3d_database_entry *scene, viewpoint *parent_viewpoint, light_3d_source *parent_lights, vec3d *position )
{
	int
		count,
		num_faces,
		object_number,
		temp;

	object_3d_face
		*faces;

	vec3d
		*pos;

	matrix3x3
		temp_matrix;

	vec3d
		scaled_relative_position,
		temp_scale,
		object_pos,
		object_unit_pos,
		sub_pos,
		*rel;

	light_3d_source
		*this_light,
		*prev_light,
		*light_ptr,
		*light;

	viewpoint
		vp;

	pos = &parent_viewpoint->position;

	rel = &obj->relative_position;

	object_number = scene->index;

	//
	// Calculate the object's position relative to the viewer.
	//
	// NOTE:
	//		BECAUSE THIS USES THE ROTATION_3D MATRIX, IT TAKES INTO ACCOUNT THE PARENT'S SCALE
	//

	sub_pos.x = ( ( obj->relative_position.x * rotation_3d[0][0] ) +
					  ( obj->relative_position.y * rotation_3d[1][0] ) +
					  ( obj->relative_position.z * rotation_3d[2][0] ) );
	sub_pos.y = ( ( obj->relative_position.x * rotation_3d[0][1] ) +
					  ( obj->relative_position.y * rotation_3d[1][1] ) +
					  ( obj->relative_position.z * rotation_3d[2][1] ) );
	sub_pos.z = ( ( obj->relative_position.x * rotation_3d[0][2] ) +
					  ( obj->relative_position.y * rotation_3d[1][2] ) +
					  ( obj->relative_position.z * rotation_3d[2][2] ) );

	sub_pos.x += position->x;
	sub_pos.y += position->y;
	sub_pos.z += position->z;

	//
	// Calculate the object's real world position
	//

	scaled_relative_position.x = rel->x * object_3d_scale.x;
	scaled_relative_position.y = rel->y * object_3d_scale.y;
	scaled_relative_position.z = rel->z * object_3d_scale.z;

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
	// From now on all sub objects are considered to be non-static - so the whole matrix has to be calculated.
	//

	{
		matrix3x3
			relative_attitude;

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

		object_3d_scale.x *= obj->relative_scale.x;
		object_3d_scale.y *= obj->relative_scale.y;
		object_3d_scale.z *= obj->relative_scale.z;

		//
		// Compute the sub object's relative attitude matrix
		//

		get_3d_transformation_matrix ( relative_attitude, obj->relative_heading, -obj->relative_pitch, -obj->relative_roll );

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
	}

	//
	//	Set up this objects' object info structure
	//

	object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;

	object_3d_object_base[object_3d_object_current_base].object_number = object_number;

	current_object_3d_object_base = &object_3d_object_base[object_3d_object_current_base];

	if ( objects_3d_data[object_number].number_of_points )
	{
		//
		// Set up the face sorting variables
		//

		num_faces = objects_3d_data[object_number].number_of_faces;

		faces = objects_3d_data[object_number].faces;

		//
		// Insert this objects' faces into the sorted list.
		//

		{
			object_short_3d_point
				*object_points;

			point_3d_plain_reference
				*plain_point_list;

			face_surface_description
				*surfaces;

			int
				surface,
				surface_face_count,
				gouraud_point_index,
				texture_point_index,
				face_normal_index,
				point_reference_index;

			surface = 0;
			gouraud_point_index = 0;
			face_normal_index = 0;
			texture_point_index = 0;
			point_reference_index = 0;


			object_points = objects_3d_data[object_number].points;

			plain_point_list = NULL;	//objects_3d_data[object_number].object_faces_point_plain_list;

			surfaces = objects_3d_data[object_number].surfaces;

			surface_face_count = surfaces[surface].number_of_faces;

			for ( count = num_faces; count > 0; count-- )
			{
				if ( surface_face_count == 0 )
				{
					surface++;
					surface_face_count = surfaces[surface].number_of_faces;
				}

				if ( surfaces[surface].polygons )
				{
					float
						tmp;

					vec3d
						true_depth_point;

					{
						point_3d_plain_reference
							*point_list;

						point_list = &plain_point_list[point_reference_index];

						true_depth_point.x = object_points[point_list[0].point].x;
						true_depth_point.y = object_points[point_list[0].point].y;
						true_depth_point.z = object_points[point_list[0].point].z;

						true_depth_point.x += object_points[point_list[1].point].x;
						true_depth_point.y += object_points[point_list[1].point].y;
						true_depth_point.z += object_points[point_list[1].point].z;

						true_depth_point.x += object_points[point_list[2].point].x;
						true_depth_point.y += object_points[point_list[2].point].y;
						true_depth_point.z += object_points[point_list[2].point].z;

						point_list += 3;

						for ( temp = faces->number_of_points; temp > 3; temp-- )
						{

							true_depth_point.x += object_points[point_list->point].x;
							true_depth_point.y += object_points[point_list->point].y;
							true_depth_point.z += object_points[point_list->point].z;

							point_list++;
						}

						tmp = true_depth_point.x * rotation_3d[0][2];
						tmp += true_depth_point.y * rotation_3d[1][2];
						tmp += true_depth_point.z * rotation_3d[2][2];
						tmp *= one_over_table[faces->number_of_points];
						tmp += position->z;

						//
						// Just use the binary representation of the float z value for z-sorting
						//

						insert_z_sorted_3d_face ( faces, *( ( int * ) &tmp ), surface, point_reference_index, gouraud_point_index, face_normal_index, texture_point_index, current_object_3d_object_base );
//						insert_z_sorted_3d_face ( faces, *( ( int * ) &tmp ), surface, point_reference_index, gouraud_point_index, 0, texture_point_index, current_object_3d_object_base );
					}
				}
				else
				{
		/*
					float
						tmp;

					point_3d_plain_reference
						*point_list;

					point_list = &plain_point_list[faces->point_reference_index];

					depth_point = &object_points[point_list->point];

					tmp = pos->z;

					point_list++;

					tmp += depth_point->x * rotation_3d[0][2];

					tmp += depth_point->y * rotation_3d[1][2];

					tmp += depth_point->z * rotation_3d[2][2];

					//
					// Just use the binary representation of the float z value for z-sorting
					//

					insert_z_sorted_3d_face ( faces, * ( ( int * ) &tmp ), this_object_3d_info );
				*/
				}

				if ( surfaces[surface].polygons )
				{
					if ( !surfaces[surface].smoothed )
					{
						face_normal_index++;
					}
					point_reference_index += faces->number_of_points;
				}
				else
				{
					point_reference_index += 2;
				}

				if ( surfaces[surface].textured )
				{
					texture_point_index += faces->number_of_points;
				}

				if ( surfaces[surface].smoothed )
				{
					gouraud_point_index += faces->number_of_points;
				}

				faces++;
				surface_face_count--;
			}
		}

		//
		// Transform the object's shape data
		//

		illuminate_3d_object ( &objects_3d_data[object_number], &sub_pos, object_3d_object_base[object_3d_object_current_base].lights, NULL, object_3d_points_current_base );

		transform_3d_object ( &objects_3d_data[object_number], &sub_pos, object_3d_object_base[object_3d_object_current_base].lights, NULL, object_3d_points_current_base );
	}

	//
	// Set the points base index to after the end of the object.
	//

	object_3d_object_current_base ++;

	object_3d_points_current_base += objects_3d_data[object_number].number_of_points;

	//
	// Recurse down any sub objects
	//

	if ( scene->number_of_sub_objects != 0 )
	{
		for ( count = ( scene->number_of_sub_objects -1 ); count >= 0; count-- )
		{
			if ( obj->sub_objects[count].visible_object )
			{
				draw_z_sorted_sub_object ( &obj->sub_objects[count], &scene->sub_objects[count], &vp, current_object_3d_object_base->lights, &sub_pos );
			}
		}
	}

	//
	// Restore the object rotation matrix
	//

	memcpy ( rotation_3d, temp_matrix, sizeof ( matrix3x3 ) );

	memcpy ( &object_3d_scale, &temp_scale, sizeof ( vec3d ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

