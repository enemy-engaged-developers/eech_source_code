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

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void transform_3d_cloud ( object_3d *object, vec3d *pos, light_3d_source *lights, int points_base );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_cloud ( object_3d_instance *obj )
{

	int
		object_number,
		draw_sub_objects,
		count,
		num_faces;

	object_3d_face
		*faces;

	object_3d_info
		*this_object_3d_info;

	light_3d_source
		*this_light,
		*prev_light,
		*light_ptr,
		*light;

	object_3d_info
		object_base;

	vec3d
		*pos,
		object_pos;

	//
	// Setup the object info structure.
	//

	this_object_3d_info = &object_base;

	//
	// Set up the object drawing global variables
	//

	//
	// Calculate the object's position relative to the view.
	//

	pos = &obj->view_position;

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

		light = &light_3d_array[0];

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

					this_light = &light_3d_array[0];
			
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

					normalise_3d_vector ( &vector );

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
		
					prev_light = this_light;
				}
			}
			else
			{
	
				this_light = &light_3d_array[0];
		
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
	
				prev_light = this_light;
			}
	
			light_ptr = light_ptr->succ;
		}
	}

	//
	//	Set up this objects' object info structure
	//

	object_base.lights = light;

	object_base.points_base = 0;

	object_base.object_number = object_number;

	this_object_3d_info = &object_base;

	//
	// Transform the object's shape data
	//

	transform_3d_cloud ( &objects_3d_data[object_number], pos, light, 0 );

	//
	// Render the faces
	//

	num_faces = objects_3d_data[object_number].number_of_faces;

	faces = objects_3d_data[object_number].faces;

	{

		int
			surface,
			point_reference_index,
			gouraud_point_index,
			texture_point_index;

		surface = 0;
		point_reference_index = 0;
		gouraud_point_index = 0;
		texture_point_index = 0;

		for ( count = num_faces; count > 0; count-- )
		{
/*
			if ( faces->flags & FACE_HAS_NEW_SURFACE )
			{

				surface++;
			}

			if ( faces->number_of_points > 2 )
			{

				if ( faces->flags & FACE_TEXTURED )
				{

					if ( faces->flags & FACE_GOURAUD_SHADED )
					{

						render_3d_object_surface_gouraud_textured_diffuse_lit_polygon ( faces, surface, point_reference_index, gouraud_point_index, texture_point_index, this_object_3d_info );
					}
					else
					{
	
						render_3d_object_surface_textured_diffuse_lit_polygon ( faces, surface, point_reference_index, texture_point_index, this_object_3d_info );
					}
				}
				else
				{

					if ( faces->flags & FACE_GOURAUD_SHADED )
					{
	
						render_3d_object_surface_gouraud_diffuse_lit_polygon ( faces, surface, point_reference_index, gouraud_point_index, this_object_3d_info );
					}
					else
					{
	
						render_3d_object_surface_diffuse_lit_polygon ( faces, surface, point_reference_index, this_object_3d_info );
					}
				}
			}
			*/
			point_reference_index += faces->number_of_points;
	
//			if ( faces->flags & FACE_TEXTURED )
//			{
//
//				texture_point_index += faces->number_of_points;
//			}
//
//			if ( faces->flags & FACE_GOURAUD_SHADED )
//			{
//
//				gouraud_point_index += faces->number_of_points;
//			}

			faces++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_cloud ( object_3d *object, vec3d *pos, light_3d_source *lights, int points_base )
{

	int
		count,
		number_of_points,
		number_of_normals;

	object_short_3d_point
		*points;

	object_3d_heading_pitch_normal
		*point_normals;

	vertex
		*last_transformed_point,
		*result_points,
		tmp_vertex;

	object_3d_transformed_point_normal
		*transformed_point_normals,
		*result_normals;

	float
		pos_x,
		pos_y,
		pos_z,
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	number_of_points = object->number_of_points;

	number_of_normals = object->number_of_point_normals;

	points = object->points;

	point_normals = object->point_normals;

	result_points = &transformed_3d_points[points_base];

	result_normals = &transformed_3d_normals[points_base];

	transformed_point_normals = result_normals;

	last_transformed_point = &tmp_vertex;

	pos_x = pos->x;
	pos_y = pos->y;
	pos_z = pos->z;

	for ( count = number_of_normals; count > 0; count-- )
	{


		float
			r,
			g,
			b;

		light_3d_source
			*this_light;

		//
		// Set the light levels
		//

		r = ambient_3d_light.colour.red;
		g = ambient_3d_light.colour.green;
		b = ambient_3d_light.colour.blue;

		this_light = lights;

		while ( this_light )
		{

			float
				temp_intensity;

//			temp_intensity = point_normals->x * this_light->lx + point_normals->y * this_light->ly + point_normals->z * this_light->lz;
			temp_intensity = 0;

			if ( *( ( int *) &temp_intensity ) > *( ( int *) &float_value_zero ) )
			{

				r += temp_intensity * this_light->colour.red;
				g += temp_intensity * this_light->colour.green;
				b += temp_intensity * this_light->colour.blue;
			}

			this_light = this_light->succ;
		}

		if ( *( ( int *) &r ) > *( ( int *) &float_value_one ) )
		{

			r = 1.0;
		}

		if ( *( ( int *) &g ) > *( ( int *) &float_value_one ) )
		{

			g = 1.0;
		}

		if ( *( ( int *) &b ) > *( ( int *) &float_value_one ) )
		{

			b = 1.0;
		}

		result_normals->r = r;
		result_normals->g = g;
		result_normals->b = b;

		point_normals++;

		result_normals++;
	}

	for ( count = number_of_points; count > 0; count-- )
	{

		{

			float
				temp,
				x,
				y,
				z;

			x = points->x * rotation_3d[0][0] + points->y * rotation_3d[1][0] + points->z * rotation_3d[2][0];
			y = points->x * rotation_3d[0][1] + points->y * rotation_3d[1][1] + points->z * rotation_3d[2][1];
			z = points->x * rotation_3d[0][2] + points->y * rotation_3d[1][2] + points->z * rotation_3d[2][2] + pos_z;

//			result_points->red = transformed_point_normals[points->point_normal_index].r;
//			result_points->green = transformed_point_normals[points->point_normal_index].g;
//			result_points->blue = transformed_point_normals[points->point_normal_index].b;

			temp = ( ( x * x ) + ( y * y ) );
			temp -= ( 1.0 * 1.0 );
			temp /= ( ( 10.0 - 1.0 ) * ( 10.0 - 1.0 ) );
			temp = bound ( temp, 0, 0.5 );

			result_points->alpha = 0.5 - temp;

		
			x += pos_x;
			y += pos_y;

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{

				float
					q,
					i,
					j;

				oxmax = active_viewport.x_max - last_transformed_point->i;
				oxmin = last_transformed_point->i - active_viewport.x_min;
				oymax = active_viewport.y_max - last_transformed_point->j;
				oymin = last_transformed_point->j - active_viewport.y_min;
			
				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );

				q = 1.0 / z;

				last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				result_points->x = x;

				result_points->y = y;

				result_points->z = z;

				last_transformed_point = result_points;

				i = ( active_3d_environment->screen_i_scale * x * q );

				j = ( active_3d_environment->screen_j_scale * y * q );

				result_points->j = active_3d_environment->y_origin - j;

				result_points->i = active_3d_environment->x_origin + i;

				result_points->q = q;
			}
			else
			{

				result_points->outcode = CLIP_HITHER;

				result_points->z = z;

				result_points->x = x;

				result_points->y = y;
			}
		}

		point_normals++;

		result_points++;

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

	last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

	//
	// Set back the fpu precision mode.
	//

	set_fpu_precision_mode_double ();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
