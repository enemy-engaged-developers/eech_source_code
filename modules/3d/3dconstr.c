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

vertex * construct_3d_line ( point_3d_plain_reference *points, int base_point, int *polygon_outcode )
{

	int
		outcode,
		outcode2,
		first_point,
		this_point;

	first_point = points[0].point + base_point;
	outcode = transformed_3d_points[first_point].outcode;
	outcode2 = transformed_3d_points[first_point].outcode;

	this_point = points[1].point + base_point;
	outcode |= transformed_3d_points[this_point].outcode;
	outcode2 &= transformed_3d_points[this_point].outcode;
	transformed_3d_points[first_point].next_vertex = &transformed_3d_points[this_point];

	transformed_3d_points[this_point].next_vertex = NULL;

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( &transformed_3d_points[first_point] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_triangle_fan ( int triangle_index, point_3d_plain_reference *points, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		first_point,
		second_point,
		third_point;

	first_point = points[0].point + base_point;
	outcode = transformed_3d_points[ first_point ].outcode;
	outcode2 = transformed_3d_points[ first_point ].outcode;

	second_point = points[triangle_index + 1].point + base_point;
	outcode |= transformed_3d_points[second_point].outcode;
	outcode2 &= transformed_3d_points[second_point].outcode;
	transformed_3d_points[first_point] .next_vertex = &transformed_3d_points [second_point];

	third_point = points[triangle_index + 2].point + base_point;
	outcode |= transformed_3d_points[third_point].outcode;
	outcode2 &= transformed_3d_points[third_point].outcode;
	transformed_3d_points[second_point] .next_vertex = &transformed_3d_points[third_point];

	transformed_3d_points[third_point].next_vertex = NULL;

	*polygon_outcode = outcode;

	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( &transformed_3d_points[first_point] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_surface_shadow_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		first_point,
		second_point,
		third_point;

	first_point = current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point + base_point;
	outcode = transformed_3d_points[ first_point ].outcode;
	outcode2 = transformed_3d_points[ first_point ].outcode;

	second_point = current_object_3d_surface_point_list[ current_object_3d_point_list[triangle_index + 1].point ].point + base_point;
	outcode |= transformed_3d_points[second_point].outcode;
	outcode2 &= transformed_3d_points[second_point].outcode;
	transformed_3d_points[first_point] .next_vertex = &transformed_3d_points [second_point];

	third_point = current_object_3d_surface_point_list[ current_object_3d_point_list[triangle_index + 2].point ].point + base_point;
	outcode |= transformed_3d_points[third_point].outcode;
	outcode2 &= transformed_3d_points[third_point].outcode;
	transformed_3d_points[second_point] .next_vertex = &transformed_3d_points[third_point];

	transformed_3d_points[third_point].next_vertex = NULL;

	*polygon_outcode = outcode;

	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( &transformed_3d_points[first_point] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_textured_triangle_fan ( int triangle_index, point_3d_plain_reference *polygon_points, object_3d_short_textured_point *texture_points, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	vertex
		*points_base,
		*first_point,
		*second_point,
		*third_point;

	points_base = &transformed_3d_points[base_point];

	first_point = &points_base[polygon_points[0].point];
	first_point->u = texture_points[0].u;
	first_point->v = texture_points[0].v;
	outcode = first_point->outcode;
	outcode2 = first_point->outcode;

	second_point = &points_base[polygon_points[triangle_index+1].point];
	second_point->u = texture_points[triangle_index+1].u;
	second_point->v = texture_points[triangle_index+1].v;
	outcode |= second_point->outcode;
	outcode2 &= second_point->outcode;

	third_point = &points_base[polygon_points[triangle_index+2].point];
	third_point->u = texture_points[triangle_index+2].u;
	third_point->v = texture_points[triangle_index+2].v;
	outcode |= third_point->outcode;
	outcode2 &= third_point->outcode;

	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		*polygon_outcode = outcode;

		first_point->next_vertex = second_point;

		second_point->next_vertex = third_point;

		third_point->next_vertex = NULL;
	
		return ( first_point );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_surface_shadow_textured_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		first_point,
		second_point,
		third_point;

	first_point = current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point + base_point;
	outcode = transformed_3d_points[ first_point ].outcode;
	outcode2 = transformed_3d_points[ first_point ].outcode;

	second_point = current_object_3d_surface_point_list[ current_object_3d_point_list[triangle_index + 1].point ].point + base_point;
	outcode |= transformed_3d_points[second_point].outcode;
	outcode2 &= transformed_3d_points[second_point].outcode;
	transformed_3d_points[first_point] .next_vertex = &transformed_3d_points [second_point];

	third_point = current_object_3d_surface_point_list[ current_object_3d_point_list[triangle_index + 2].point ].point + base_point;
	outcode |= transformed_3d_points[third_point].outcode;
	outcode2 &= transformed_3d_points[third_point].outcode;
	transformed_3d_points[second_point] .next_vertex = &transformed_3d_points[third_point];

	transformed_3d_points[first_point].u = current_object_3d_surface_point_texture_list[ current_object_3d_point_list[0].point ].u;
	transformed_3d_points[first_point].v = current_object_3d_surface_point_texture_list[ current_object_3d_point_list[0].point ].v;
	transformed_3d_points[second_point].u = current_object_3d_surface_point_texture_list[ current_object_3d_point_list[triangle_index+1].point ].u;
	transformed_3d_points[second_point].v = current_object_3d_surface_point_texture_list[ current_object_3d_point_list[triangle_index+1].point ].v;
	transformed_3d_points[third_point].u = current_object_3d_surface_point_texture_list[ current_object_3d_point_list[triangle_index+2].point ].u;
	transformed_3d_points[third_point].v = current_object_3d_surface_point_texture_list[ current_object_3d_point_list[triangle_index+2].point ].v;

	transformed_3d_points[third_point].next_vertex = NULL;

	*polygon_outcode = outcode;

	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( &transformed_3d_points[first_point] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_polygon ( int num_points, point_3d_plain_reference *points, int base_point, int *polygon_outcode )
{

	int
		count,
		this_outcode;

	unsigned char
		outcode,
		outcode2;

	vertex
		*points_list;

	points_list = transformed_3d_points + base_point;

	this_outcode = points_list[points[0].point].outcode;
	outcode = this_outcode;
	outcode2 = this_outcode;

	for ( count = 1; count < num_points; count++ )
	{

		this_outcode = points_list[points[count].point].outcode;
		outcode |= this_outcode;
		outcode2 &= this_outcode;
	}

	*polygon_outcode = outcode;

	return ( outcode2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_surface_polygon ( int num_points, int base_point, int *polygon_outcode )
{

	int
		count,
		this_outcode;

	unsigned char
		outcode,
		outcode2;

	vertex
		*points_list;

	points_list = transformed_3d_points + base_point;

	this_outcode = points_list[ current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point].outcode;
	outcode = this_outcode;
	outcode2 = this_outcode;

	for ( count = 1; count < num_points; count++ )
	{

		this_outcode = points_list[ current_object_3d_surface_point_list[ current_object_3d_point_list[count].point ].point].outcode;
		outcode |= this_outcode;
		outcode2 &= this_outcode;
	}

	*polygon_outcode = outcode;

	return ( outcode2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_perspective_to_polygon_texture ( vertex *poly )
{

	while ( poly )
	{

		poly->u = poly->u * poly->q;
		poly->v = poly->v * poly->q;

		poly = poly->next_vertex;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_perspective_from_polygon_texture ( vertex *poly )
{

	while ( poly )
	{

		poly->u = poly->u * poly->z;
		poly->v = poly->v * poly->z;

		poly = poly->next_vertex;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_perspective_to_polygon_dual_texture ( vertex *poly )
{

	while ( poly )
	{

		poly->u = poly->u * poly->q;
		poly->v = poly->v * poly->q;
		poly->u2 = poly->u2 * poly->q;
		poly->v2 = poly->v2 * poly->q;

		poly = poly->next_vertex;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_perspective_from_polygon_dual_texture ( vertex *poly )
{

	while ( poly )
	{

		poly->u = poly->u * poly->z;
		poly->v = poly->v * poly->z;
		poly->u2 = poly->u2 * poly->z;
		poly->v2 = poly->v2 * poly->z;

		poly = poly->next_vertex;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int get_3d_point_outcodes ( float x, float y, float z )
{

	float
		x_rel,
		y_rel,
		z_rel,
		i,
		j,
		q;

	unsigned int
		outcode;

	x -= visual_3d_vp->x;
	y -= visual_3d_vp->y;
	z -= visual_3d_vp->z;

	x_rel = ( ( x * visual_3d_vp->xv.x ) + ( y * visual_3d_vp->xv.y ) + ( z * visual_3d_vp->xv.z ) );
	y_rel = ( ( x * visual_3d_vp->yv.x ) + ( y * visual_3d_vp->yv.y ) + ( z * visual_3d_vp->yv.z ) );
	z_rel = ( ( x * visual_3d_vp->zv.x ) + ( y * visual_3d_vp->zv.y ) + ( z * visual_3d_vp->zv.z ) );

	if ( *( ( int * ) &z_rel ) >= *( ( int * ) &clip_hither ) )
	{

		if ( *( ( int * ) &z_rel ) <= *( ( int * ) &clip_yonder ) )
		{
	
			q = 1.0 / z_rel;
		
			i = ( active_3d_environment->screen_i_scale * x_rel * q );
		
			j = ( active_3d_environment->screen_j_scale * y_rel * q );
		
			j = ( active_3d_environment->y_origin - j );
		
			i += active_3d_environment->x_origin;
		
			outcode = generate_3d_outcode ( i, j );
		}
		else
		{

			outcode = CLIP_YONDER;
		}
	}
	else
	{

		outcode = CLIP_HITHER;
	}

	return ( outcode );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

