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

#if 0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_surface_uv_mappings ( int number_of_points, point_3d_textured_reference *point_list, int *return_outcode )
{

	int
		number_of_quad_points,
		remainder_of_points,
		count;

	int
		outcode,
		outcode2;

	number_of_quad_points = number_of_points >> 2;

	remainder_of_points = number_of_points - ( number_of_quad_points << 2 );

	outcode = 0;
	outcode2 = CLIP_HITHER | CLIP_YONDER | CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;

	for ( count = number_of_quad_points; count > 0; count-- )
	{

		int
			point;

		point = point_list[0].point;
		*( ( int * ) &transformed_3d_points[point].u ) = *( ( int * ) &point_list[0].u );
		*( ( int * ) &transformed_3d_points[point].v ) = *( ( int * ) &point_list[0].v );
		outcode |= transformed_3d_points[point].outcode;
		outcode2 &= transformed_3d_points[point].outcode;

		point = point_list[1].point;
		*( ( int * ) &transformed_3d_points[point].u ) = *( ( int * ) &point_list[1].u );
		*( ( int * ) &transformed_3d_points[point].v ) = *( ( int * ) &point_list[1].v );
		outcode |= transformed_3d_points[point].outcode;
		outcode2 &= transformed_3d_points[point].outcode;

		point = point_list[2].point;
		*( ( int * ) &transformed_3d_points[point].u ) = *( ( int * ) &point_list[2].u );
		*( ( int * ) &transformed_3d_points[point].v ) = *( ( int * ) &point_list[2].v );
		outcode |= transformed_3d_points[point].outcode;
		outcode2 &= transformed_3d_points[point].outcode;

		point = point_list[3].point;
		*( ( int * ) &transformed_3d_points[point].u ) = *( ( int * ) &point_list[3].u );
		*( ( int * ) &transformed_3d_points[point].v ) = *( ( int * ) &point_list[3].v );
		outcode |= transformed_3d_points[point].outcode;
		outcode2 &= transformed_3d_points[point].outcode;

		point_list += 4;
	}

	for ( count = remainder_of_points; count > 0; count-- )
	{

		int
			point;

		point = point_list->point;
		*( ( int * ) &transformed_3d_points[point].u ) = *( ( int * ) &point_list[0].u );
		*( ( int * ) &transformed_3d_points[point].v ) = *( ( int * ) &point_list[0].v );
		outcode |= transformed_3d_points[point].outcode;
		outcode2 &= transformed_3d_points[point].outcode;

		point_list++;
	}

	*return_outcode = outcode;


	if ( outcode2 )
	{

		return ( FALSE );
	}
	else
	{

		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_surface_textured_shared_points ( int number_of_points, point_3d_textured_reference *point_list )
{

	int
		count;

	LPD3DTLVERTEX
		vptr;

	vptr = shared_vertices;

	if ( number_of_points > 2047 )
	{

		debug_fatal ( "Exceeded maximum number of shared vertices in an object surface: %d", number_of_points );
	}

	for ( count = 0; count < number_of_points; count++ )
	{

		float
			fr,
			fg,
			fb;

		int
			r,
			g,
			b,
			point;

		point = point_list->point;

		fr = ( transformed_3d_points[point].red * 255 ) + FLOAT_FLOAT_FACTOR;
		fg = ( transformed_3d_points[point].green * 255 ) + FLOAT_FLOAT_FACTOR;
		fb = ( transformed_3d_points[point].blue * 255 ) + FLOAT_FLOAT_FACTOR;

		r = ( *( int * ) &fr ) - INTEGER_FLOAT_FACTOR;
		g = ( *( int * ) &fg ) - INTEGER_FLOAT_FACTOR;
		b = ( *( int * ) &fb ) - INTEGER_FLOAT_FACTOR;

		*( ( int * ) &vptr->sx ) = *( ( int * ) &transformed_3d_points[point].i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &transformed_3d_points[point].j );
		*( ( int * ) &vptr->tu ) = *( ( int * ) &transformed_3d_points[point].u );
		*( ( int * ) &vptr->tv ) = *( ( int * ) &transformed_3d_points[point].v );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &transformed_3d_points[point].q );
		*( ( int * ) &vptr->sz ) = *( ( int * ) &transformed_3d_points[point].q );
		vptr->color = D3DCOLOR_XRGB ( r, g, b );
		vptr->specular = d3d_fog_intensity;

		point_list++;

		vptr++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
