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

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CLOUD_TRUMPET_TEXTURE_INFO
{

	float
		u,
		v,
		alpha;
};

typedef struct CLOUD_TRUMPET_TEXTURE_INFO cloud_trumpet_texture_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static object_3d_instance
	*cloud_trumpet_object;

static cloud_trumpet_texture_info
	cloud_trumpet_texture_values[256];

float
	cloud_3d_trumpet_blend_start,
	cloud_3d_trumpet_blend_end,
	cloud_3d_trumpet_blend_distance,
	cloud_3d_trumpet_blend_start_squared,
	cloud_3d_trumpet_blend_distance_squared,
	cloud_3d_trumpet_blend_constant,
	cloud_3d_trumpet_blend_factor;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void transform_3d_cloud_trumpet ( object_3d *object, viewpoint *vp, vec3d *relative_position );

static void render_3d_cloud_trumpet_face ( object_3d_face *this_face, int surface, int reference_offset, object_3d_info *object_info );

static vertex *construct_3d_cloud_trumpet_polygon ( int num_points, point_3d_plain_reference *points, int *polygon_outcode );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_cloud_trumpet_object ( object_3d_index_numbers object_number )
{

	cloud_trumpet_object = construct_3d_object ( object_number );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_cloud_trumpet ( void )
{

	int
		object_number,
		count,
		draw_sub_objects,
		num_faces;

	object_3d_face
		*faces;

	object_3d_info
		*this_object_3d_info;

	object_3d_info
		object_base;

	object_3d_instance
		*obj;

	//
	// Construct an attitude matrix from the visual viewpoint
	//

	if ( visual_3d_vp->zv.y > 0.9 )
	{

		//
		// If you're looking directly up, don't bother with the trumpet!
		//

		return;
	}

	obj = cloud_trumpet_object;

	{

		float
			heading;

		heading = get_heading_from_attitude_matrix ( visual_3d_vp->attitude );

		get_3d_transformation_matrix ( obj->vp.attitude, heading, 0, 0 );

		//get_matrix3x3_from_unit_vec3d ( obj->vp.attitude, &visual_3d_vp->zv );
	}

	obj->vp.position.x = visual_3d_vp->x;
	obj->vp.position.y = cloud_3d_base_height;
	obj->vp.position.z = visual_3d_vp->z;

	set_object_3d_instance_relative_position ( obj );

	//
	// Set the fog value to non fogged
	//

	set_d3d_fog_face_intensity ( 255 );

	//
	// Set the cloud carpet blend factors
	//

	{

		float
			blend_distance,
			blend_factor;

		blend_distance = fabs ( cloud_3d_base_height - visual_3d_vp->y );

		blend_factor = 1.0 - ( blend_distance / 300 );

		blend_factor *= 1;

		if ( blend_factor < 0 )
		{

			blend_factor = 0;
		}

		if ( blend_factor > 1 )
		{

			blend_factor = 1;
		}

		cloud_3d_trumpet_blend_start = 100.0;
	
		cloud_3d_trumpet_blend_end = 200.0;
	
		cloud_3d_trumpet_blend_distance = cloud_3d_trumpet_blend_end - cloud_3d_trumpet_blend_start;
	
		cloud_3d_trumpet_blend_start_squared = cloud_3d_trumpet_blend_start * cloud_3d_trumpet_blend_start;
	
		cloud_3d_trumpet_blend_distance_squared = cloud_3d_trumpet_blend_distance * cloud_3d_trumpet_blend_distance;
	
		cloud_3d_trumpet_blend_constant = cloud_3d_trumpet_blend_distance_squared - cloud_3d_trumpet_blend_start_squared;
	
		cloud_3d_trumpet_blend_factor = blend_factor;	// / cloud_3d_trumpet_blend_distance_squared;

		if ( blend_factor == 0 )
		{

			return;
		}
	}

	//
	// Set up object base variable
	//

	this_object_3d_info = &object_base;

	object_base.lights = NULL;

	object_base.points_base = 0;

	//
	// Calculate the object's rotation matrix, to transform its 3d points into world coordinate system
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

//	rotation_3d[0][0] = ( visual_3d_vp->xv.x );
//	rotation_3d[0][1] = ( visual_3d_vp->yv.x );
//	rotation_3d[0][2] = ( visual_3d_vp->zv.x );

//	rotation_3d[1][0] = ( visual_3d_vp->xv.y );
//	rotation_3d[1][1] = ( visual_3d_vp->yv.y );
//	rotation_3d[1][2] = ( visual_3d_vp->zv.y );

//	rotation_3d[2][0] = ( visual_3d_vp->xv.z );
//	rotation_3d[2][1] = ( visual_3d_vp->yv.z );
//	rotation_3d[2][2] = ( visual_3d_vp->zv.z );

	//
	// Get the object number
	//

	object_number = get_object_approximation_number ( obj->object_number, 0, &draw_sub_objects );

	object_base.object_number = object_number;

	//
	// Transform the object's shape data
	//

	transform_3d_cloud_trumpet ( &objects_3d_data[object_number], &obj->vp, &obj->view_position );

	//
	// Remove fogging temporarily
	//

	suspend_d3d_fog ();

	//
	// Render the faces
	//

	num_faces = objects_3d_data[object_number].number_of_faces;

	faces = objects_3d_data[object_number].faces;

	{

		int
			surface,
			point_reference_index;

		point_reference_index = 0;
	
		surface = 0;

		for ( count = num_faces; count > 0; count-- )
		{
	
//			if ( faces->flags & FACE_HAS_NEW_SURFACE )
			{

				surface++;
			}

			if ( faces->number_of_points > 2 )
			{
	
				render_3d_cloud_trumpet_face ( faces, surface, point_reference_index, this_object_3d_info );
			}

			point_reference_index += faces->number_of_points;
	
			faces++;
		}
	}

	reinstate_d3d_fog ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_cloud_trumpet ( object_3d *object, viewpoint *vp, vec3d *relative_position )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	vertex
		*last_transformed_point,
		*result_points,
		tmp_vertex;

	float
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	cloud_trumpet_texture_info
		*texture_values;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	number_of_points = object->number_of_points;

	points = object->points;

	result_points = transformed_3d_points;

	texture_values = cloud_trumpet_texture_values;

	last_transformed_point = &tmp_vertex;

	for ( count = number_of_points; count > 0; count-- )
	{

		{

			float
				x_world,
				y_world,
				z_world,
				x,
				y,
				z;

			x_world = points->x * vp->attitude[0][0] + points->y * vp->attitude[1][0] + points->z * vp->attitude[2][0] + vp->position.x;
			z_world = points->x * vp->attitude[0][2] + points->y * vp->attitude[1][2] + points->z * vp->attitude[2][2] + vp->position.z;

			x_world /= CLOUD_3D_SECTOR_SIDE_LENGTH;
			z_world /= CLOUD_3D_SECTOR_SIDE_LENGTH;

			y_world = points->y;
			y_world *= y_world;

			texture_values->alpha = cloud_3d_trumpet_blend_factor;	//( ( y_world - cloud_3d_trumpet_blend_constant ) * cloud_3d_trumpet_blend_factor );

			if ( texture_values->alpha > 1 )
			{

				texture_values->alpha = 1;
			}

			if ( texture_values->alpha < 0 )
			{

				texture_values->alpha = 0;
			}

			texture_values->u = x_world;
			texture_values->v = z_world;

//			texture_values->alpha = 1;

			z = points->x * rotation_3d[0][2] + points->y * rotation_3d[1][2] + points->z * rotation_3d[2][2] + relative_position->z;

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{

				float
					q,
					i,
					j;

				x = points->x * rotation_3d[0][0] + points->y * rotation_3d[1][0] + points->z * rotation_3d[2][0] + relative_position->x;

				y = points->x * rotation_3d[0][1] + points->y * rotation_3d[1][1] + points->z * rotation_3d[2][1] + relative_position->y;

				oxmax = active_viewport.x_max - last_transformed_point->i;
				oxmin = last_transformed_point->i - active_viewport.x_min;
				oymax = active_viewport.y_max - last_transformed_point->j;
				oymin = last_transformed_point->j - active_viewport.y_min;
			
				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );
			
				last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				result_points->x = x;

				result_points->y = y;

				result_points->z = z;

				last_transformed_point = result_points;

				q = 1.0 / z;

				i = ( active_3d_environment->screen_i_scale * x * q );

				j = ( active_3d_environment->screen_j_scale * y * q );

				result_points->j = active_3d_environment->y_origin - j;

				result_points->i = active_3d_environment->x_origin + i;

				result_points->q = q;
			}
			else
			{

				x = points->x * rotation_3d[0][0] + points->y * rotation_3d[1][0] + points->z * rotation_3d[2][0] + relative_position->x;

				y = points->x * rotation_3d[0][1] + points->y * rotation_3d[1][1] + points->z * rotation_3d[2][1] + relative_position->y;

				result_points->outcode = CLIP_HITHER;

				result_points->z = z;

				result_points->x = x;

				result_points->y = y;
			}
		}

		texture_values++;

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

void render_3d_cloud_trumpet_face ( object_3d_face *this_face, int surface_index, int reference_offset, object_3d_info *object_base )
{

	face_surface_description
		*surface;

	clip_3d_coord = 0;

	surface = &objects_3d_data[ object_base->object_number ].surfaces[surface_index];


	{

		vertex
			*poly;

		int
			outcode;
	
		point_3d_plain_reference
			*point_list;

		point_list = NULL;	//objects_3d_data[object_base->object_number].object_faces_point_plain_list;

		point_list += reference_offset;

		poly = construct_3d_cloud_trumpet_polygon ( this_face->number_of_points,
																	point_list,
																	&outcode );
		if ( !poly )
		{

			return;
		}

		if ( outcode & CLIP_HITHER )
		{
	
			poly = hither_clip_3d_polygon ( poly, &outcode );

			if ( !poly )
			{

				return;
			}
		}
	
		if ( outcode )
		{

			apply_perspective_to_polygon_texture ( poly );
			
			poly = clip_3d_polygon ( poly, outcode );

			if ( !poly )
			{

				return;
			}

			remove_perspective_from_polygon_texture ( poly );
		}
	
//		buffer_translucent_gouraud_shaded_textured_polygon ( poly, &system_textures[TEXTURE_INDEX_CLOUDDRY],
//																				D3DFILTER_LINEAR, D3DFILTER_MIPLINEAR, D3DTADDRESS_WRAP );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_cloud_trumpet_polygon ( int num_points, point_3d_plain_reference *points, int *polygon_outcode )
{

	int
		count,
		outcode,
		outcode2,
		first_point,
		this_point,
		previous_point;

	//
	// Always do 3 points in a face, cos they're guaranteed
	//

	first_point = points[0].point;
	transformed_3d_points[first_point].u = cloud_trumpet_texture_values[first_point].u;
	transformed_3d_points[first_point].v = cloud_trumpet_texture_values[first_point].v;
	transformed_3d_points[first_point].alpha = cloud_trumpet_texture_values[first_point].alpha;
	transformed_3d_points[first_point].red = 1;
	transformed_3d_points[first_point].green = 1;
	transformed_3d_points[first_point].blue = 1;
	outcode = transformed_3d_points[ first_point ].outcode;
	outcode2 = transformed_3d_points[ first_point ].outcode;

	//
	// Second point
	//

	previous_point = points[1].point;
	transformed_3d_points[previous_point].u = cloud_trumpet_texture_values[previous_point].u;
	transformed_3d_points[previous_point].v = cloud_trumpet_texture_values[previous_point].v;
	transformed_3d_points[previous_point].alpha = cloud_trumpet_texture_values[previous_point].alpha;
	transformed_3d_points[previous_point].red = 1;
	transformed_3d_points[previous_point].green = 1;
	transformed_3d_points[previous_point].blue = 1;
	outcode |= transformed_3d_points[ previous_point ].outcode;
	outcode2 &= transformed_3d_points[ previous_point ].outcode;
	transformed_3d_points[ first_point ] .next_vertex = & transformed_3d_points [ previous_point ];

	//
	// Third point
	//

	this_point = points[2].point;
	transformed_3d_points[this_point].u = cloud_trumpet_texture_values[this_point].u;
	transformed_3d_points[this_point].v = cloud_trumpet_texture_values[this_point].v;
	transformed_3d_points[this_point].alpha = cloud_trumpet_texture_values[this_point].alpha;
	transformed_3d_points[this_point].red = 1;
	transformed_3d_points[this_point].green = 1;
	transformed_3d_points[this_point].blue = 1;
	outcode |= transformed_3d_points[ this_point ].outcode;
	outcode2 &= transformed_3d_points[ this_point ].outcode;
	transformed_3d_points[ previous_point ] .next_vertex = & transformed_3d_points [ this_point ];

	previous_point = this_point;

	for ( count = 3; count < num_points; count++ )
	{

		this_point = points[count].point;
		transformed_3d_points[this_point].u = cloud_trumpet_texture_values[this_point].u;
		transformed_3d_points[this_point].v = cloud_trumpet_texture_values[this_point].v;
		transformed_3d_points[this_point].alpha = cloud_trumpet_texture_values[this_point].alpha;
		transformed_3d_points[this_point].red= 1;
		transformed_3d_points[this_point].green = 1;
		transformed_3d_points[this_point].blue = 1;
		outcode |= transformed_3d_points[this_point].outcode;
		outcode2 &= transformed_3d_points[this_point].outcode;
		transformed_3d_points[previous_point].next_vertex = &transformed_3d_points[this_point];

		previous_point = this_point;
	}

	transformed_3d_points[this_point].next_vertex = NULL;

	if ( outcode2 )
	{

		// The polygon is totally off the screen!

		return ( NULL );
	}
	else
	{

		*polygon_outcode = outcode;
	
		return ( &transformed_3d_points[ first_point ] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

