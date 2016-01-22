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

#define MAX_POLYLINES 1024

#define MAX_POLYLINE_POINTS 2048

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


polyline_header
	polyline_headers[MAX_POLYLINES];

polyline_point
	polyline_points[MAX_POLYLINE_POINTS];

int
	number_of_3d_polylines,
	number_of_3d_polyline_points;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int transform_3d_polyline_points ( int number_of_vertices, vec3d *vertices, polyline_point *result_points );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_polylines ( void )
{

	number_of_3d_polylines = 0;

	number_of_3d_polyline_points = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int insert_3d_line_into_3d_scene ( rgb_colour colour, vec3d *point1, vec3d *point2 )
{

	vec3d
		new_points[2];

	new_points[0] = *point1;
	new_points[1] = *point2;

	return ( insert_zbiased_polyline_into_3d_scene ( 2, 0.0, FALSE, colour, new_points ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int insert_3d_polyline_into_3d_scene ( int number_of_points, rgb_colour colour, vec3d *points )
{

	return ( insert_zbiased_polyline_into_3d_scene ( number_of_points, 0.0, FALSE, colour, points ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern object_3d_instance
	*exclusive_3d_instance;

int insert_zbiased_polyline_into_3d_scene ( int number_of_points, float zbias, int lit, rgb_colour colour, vec3d *points )
{

	polyline_point
		*rotated_points;

	int
		count,
		visible;

	real_colour
		polyline_colour;

	if ( exclusive_3d_instance )
	{

		return ( FALSE );
	}

	//
	// First, ensure we have enough memory
	//

	if ( number_of_3d_polyline_points + number_of_points > MAX_POLYLINE_POINTS )
	{

		return ( FALSE );
	}

	if ( number_of_3d_polylines + 1 > MAX_POLYLINES )
	{

		return ( FALSE );
	}

	//
	// First, copy the ROTATED point data over to an internal 3d visual buffer ( checking for visibility )
	//

	visible = FALSE;

	rotated_points = &polyline_points[number_of_3d_polyline_points];

	//
	// Copy the colour value
	//

	polyline_colour.red = colour.r;
	polyline_colour.green = colour.g;
	polyline_colour.blue = colour.b;
	polyline_colour.alpha = 0;

	if ( rotated_points )
	{

		visible = transform_3d_polyline_points ( number_of_points, points, rotated_points );

		if ( visible )
		{

			polyline_header
				*polyline;
	
			//
			// Some part ( or all ) of the polyline is visible
			//

			polyline = &polyline_headers[number_of_3d_polylines];

			number_of_3d_polylines++;

			number_of_3d_polyline_points += number_of_points;

			polyline->number_of_points = number_of_points;
	
			polyline->points = rotated_points;

			polyline->colour = polyline_colour;

			polyline->lit = lit;
	
			//
			// Now insert each segment dependant on it being visible or not.
			//
	
			for ( count = 0; count < ( number_of_points - 1 ); count++ )
			{
	
				if ( ( rotated_points[count].transformed_point.z > clip_hither ) || ( rotated_points[count+1].transformed_point.z > clip_hither ) )
				{
	
					scene_slot_drawing_list
						*buffer;
	
					float
						average_z;
	
					average_z = ( rotated_points[count].transformed_point.z + rotated_points[count+1].transformed_point.z ) / 2.0;
	
					average_z += zbias;
	
					buffer = get_3d_scene_slot ();
		
					if ( buffer )
					{
	
						buffer->type = OBJECT_3D_DRAW_TYPE_POLYLINE;
		
						buffer->z = *( ( int * ) &average_z );
		
						buffer->polyline.polyline = polyline;
	
						buffer->polyline.segment = count;
	
						if ( points[count].y > middle_scene_slot_height )
						{
		
							insert_high_zbuffered_scene_slot_into_3d_scene ( buffer );
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

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_polyline ( struct OBJECT_3D_POLYLINE *polyline )
{

	int
		segment,
		outcode;

	float
		average_distance;

	polyline_point
		*points;

	vertex
		*line;

	real_colour
		colour;

	//
	// Connect the two vertices up
	//

	points = polyline->polyline->points;

	segment = polyline->segment;

	points[segment].transformed_point.next_vertex = &points[segment+1].transformed_point;

	points[segment+1].transformed_point.next_vertex = NULL;

	outcode = points[segment].transformed_point.outcode;
	outcode |= points[segment+1].transformed_point.outcode;

	//
	// Calculate the average distance of the polyline
	//

	average_distance = ( points[segment].transformed_point.z + points[segment+1].transformed_point.z ) / 2.0;

	//
	// Set the fog value for this polyline
	//

	{

		float
			fog_intensity;

		int
			ifog_intensity;

		fog_intensity = get_fog_distance_value ( average_distance );

		convert_float_to_int ( fog_intensity, &ifog_intensity );

		set_d3d_fog_face_intensity ( ifog_intensity );
	}

	//
	// Calculate the lighting if required
	//

	if ( polyline->polyline->lit )
	{

		vec3d
			point1,
			point2,
			plane_normal,
			line_normal;

		float
			red,
			green,
			blue,
			ndotn,
			ndotp1,
			ndotcamera,
			direction_factor;

		light_3d_source
			*this_light;

		int
			ired,
			igreen,
			iblue;
	
		//
		// This bit is a work of a genius matey!
		//

		point1 = points[segment].world_point;
		point2 = points[segment+1].world_point;

		point1.x = ( ( point2.x - point1.x ) / 2 ) + point1.x;
		point1.y = ( ( point2.y - point1.y ) / 2 ) + point1.y;
		point1.z = ( ( point2.z - point1.z ) / 2 ) + point1.z;

		plane_normal.x = point2.x - point1.x;
		plane_normal.y = point2.y - point1.y;
		plane_normal.z = point2.z - point1.z;

		ndotn = ( ( plane_normal.x * plane_normal.x ) + ( plane_normal.y * plane_normal.y ) + ( plane_normal.z * plane_normal.z ) );
		ndotp1 = ( ( point1.x * plane_normal.x ) + ( point1.y * plane_normal.y ) + ( point1.z * plane_normal.z ) );

		ndotcamera = (	( visual_3d_vp->x * plane_normal.x ) + ( visual_3d_vp->y * plane_normal.y ) + ( visual_3d_vp->z * plane_normal.z ) );

		direction_factor = ( ( ndotp1 - ndotcamera ) / ndotn );

		line_normal.x = visual_3d_vp->x + direction_factor * ( plane_normal.x );
		line_normal.y = visual_3d_vp->y + direction_factor * ( plane_normal.y );
		line_normal.z = visual_3d_vp->z + direction_factor * ( plane_normal.z );

		line_normal.x = line_normal.x - point1.x;
		line_normal.y = line_normal.y - point1.y;
		line_normal.z = line_normal.z - point1.z;

		normalise_any_3d_vector ( &line_normal );

		this_light = current_3d_lights;

		red = ambient_3d_light.colour.red;
		green = ambient_3d_light.colour.green;
		blue = ambient_3d_light.colour.blue;

		while ( this_light )
		{

			float
				intensity;

			intensity = ( ( line_normal.x * this_light->lx ) + ( line_normal.y * this_light->ly ) + ( line_normal.z * this_light->lz ) );

			if ( ( *( int * ) &intensity ) > ( *( int * ) &float_value_zero ) )
			{

				red += intensity * this_light->colour.red;
				green += intensity * this_light->colour.green;
				blue += intensity * this_light->colour.blue;
			}

			this_light = this_light->succ;
		}
	
		red = bound ( red, 0, 1 );
		green = bound ( green, 0, 1 );
		blue = bound ( blue, 0, 1 );

		red *= polyline->polyline->colour.red;
		green *= polyline->polyline->colour.green;
		blue *= polyline->polyline->colour.blue;

		red += FLOAT_FLOAT_FACTOR;
		green += FLOAT_FLOAT_FACTOR;
		blue += FLOAT_FLOAT_FACTOR;

		ired = ( *( int * ) &red ) - INTEGER_FLOAT_FACTOR;
		igreen = ( *( int * ) &green ) - INTEGER_FLOAT_FACTOR;
		iblue = ( *( int * ) &blue ) - INTEGER_FLOAT_FACTOR;

		colour.red = ired;
		colour.green = igreen;
		colour.blue = iblue;
		colour.alpha = 0;
	}
	else
	{

		colour = polyline->polyline->colour;
	}

	//
	// Go through all the vertices, creating lines to draw, then render them.
	//

	line = &points[segment].transformed_point;

	clip_3d_coord = 0;

	if ( outcode & CLIP_HITHER )
	{

		line = hither_clip_3d_polygon ( line, &outcode );
	}

	if ( line )
	{

		if ( outcode )
		{

			line = clip_3d_polygon ( line, outcode );
		}

		if ( line )
		{

			set_d3d_plain_renderstate ();

			draw_wbuffered_plain_line ( line, colour );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int transform_3d_polyline_points ( int number_of_vertices, vec3d *vertices, polyline_point *result_points )
{

	int
		count,
		visible;

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

	visible = FALSE;

	for ( count = number_of_vertices; count > 0; count-- )
	{

		float
			pointx,
			pointy,
			pointz,
			x,
			y,
			z;

		result_points->world_point = *vertices;

		pointx = vertices->x - visual_3d_vp->x;
		pointy = vertices->y - visual_3d_vp->y;
		pointz = vertices->z - visual_3d_vp->z;

		x = pointx * visual_3d_vp->xv.x;
		y = pointx * visual_3d_vp->yv.x;
		z = pointx * visual_3d_vp->zv.x;

		x += pointy * visual_3d_vp->xv.y;
		y += pointy * visual_3d_vp->yv.y;
		z += pointy * visual_3d_vp->zv.y;

		x += pointz * visual_3d_vp->xv.z;
		y += pointz * visual_3d_vp->yv.z;
		z += pointz * visual_3d_vp->zv.z;

		x *= active_3d_environment->screen_i_scale;
		y *= active_3d_environment->screen_j_scale;

		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			visible = TRUE;

			q = 1.0 / z;

			result_points->transformed_point.x = x;
			result_points->transformed_point.y = y;
			result_points->transformed_point.z = z;

			i = active_3d_environment->x_origin + ( x * q );

			j = active_3d_environment->y_origin - ( y * q );

			oxmax = active_viewport.x_max - i;
			oxmin = i - active_viewport.x_min;
			oymax = active_viewport.y_max - j;
			oymin = j - active_viewport.y_min;
		
			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );
		
			result_points->transformed_point.outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			result_points->transformed_point.j = j;
			result_points->transformed_point.i = i;
			result_points->transformed_point.q = q;
		}
		else
		{

			result_points->transformed_point.outcode = CLIP_HITHER;

			result_points->transformed_point.z = z;
			result_points->transformed_point.x = x;
			result_points->transformed_point.y = y;
		}

		result_points++;

		vertices++;
	}

	return ( visible );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
