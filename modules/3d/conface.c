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

vertex * construct_3d_face ( int	num_points, point_3d_reference *points, int base_point )
{

	int
		count,
		outcode,
		outcode2,
		first_point,
		this_point,
		previous_point;

	outcode = 0;

	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	//
	// Always do 3 points in a face, cos they're guaranteed
	//

	first_point = points[0].point + base_point;
	outcode |= transformed_3d_points[ first_point ].outcode;
	outcode2 &= transformed_3d_points[ first_point ].outcode;

	previous_point = points[1].point + base_point;
	outcode |= transformed_3d_points[ previous_point ].outcode;
	outcode2 &= transformed_3d_points[ previous_point ].outcode;
	transformed_3d_points[ first_point ] .next_vertex = & transformed_3d_points [ previous_point ];

	this_point = points[2].point + base_point;
	outcode |= transformed_3d_points[ this_point ].outcode;
	outcode2 &= transformed_3d_points[ this_point ].outcode;
	transformed_3d_points[ previous_point ] .next_vertex = & transformed_3d_points [ this_point ];

	previous_point = this_point;

	for ( count=3; count<num_points; count++ )
	{

		this_point = points[count].point + base_point;

		outcode |= transformed_3d_points[ this_point ].outcode;
		outcode2 &= transformed_3d_points[ this_point ].outcode;
		transformed_3d_points[ previous_point ].next_vertex = & transformed_3d_points[ this_point ];

		previous_point = this_point;
	}

	transformed_3d_points[ this_point ].next_vertex = NULL;

	if ( outcode2 )
	{

		// The polygon is totally off the screen!

		return ( NULL );
	}
	else
	{

		transformed_3d_points [ first_point ].polygon_outcode = outcode;
	
		return ( & transformed_3d_points[ first_point ] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_affine_textured_face ( int num_points, point_3d_reference *points, int base_point )
{

	int
		count,
		outcode,
		outcode2;

	vertex
		*points_base,
		*first_point,
		*this_point,
		*previous_point;

	outcode = 0;
	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	points_base = & transformed_3d_points[base_point];
	first_point = & points_base[points->point];
	previous_point = first_point;
	first_point->u = points->u << 16;
	first_point->v = points->v << 16;
	points++;

	for ( count=1; count<num_points; count++ )
	{

		this_point = & points_base[points->point];
		this_point->u = points->u << 16;
		this_point->v = points->v << 16;

		outcode |= previous_point->outcode;
		outcode2 &= previous_point->outcode;
		previous_point->next_vertex = this_point;

		previous_point = this_point;
		points++;
	}

	outcode |= previous_point->outcode;
	outcode2 &= previous_point->outcode;
	previous_point->next_vertex = NULL;

	if ( outcode2 )
	{

		// The polygon is totally off the screen!

		return ( NULL );
	}
	else
	{

		first_point->polygon_outcode = outcode;
	
		return ( first_point );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_perspective_textured_face ( int num_points, point_3d_reference *points, int base_point )
{

	int
		count,
		outcode,
		outcode2;

	vertex
		*points_base,
		*first_point,
		*this_point,
		*previous_point;

	outcode = 0;
	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	points_base = & transformed_3d_points[base_point];
	first_point = & points_base[points->point];
	previous_point = first_point;
	first_point->u = points->u << 16;
	first_point->v = points->v << 16;
	first_point->u_z = ( first_point->u * first_point->q );
	first_point->v_z = ( first_point->v * first_point->q );
	points++;

	for ( count=1; count<num_points; count++ )
	{

		this_point = & points_base[points->point];
		this_point->u = points->u << 16;
		this_point->v = points->v << 16;
		this_point->u_z = ( this_point->u * this_point->q );
		this_point->v_z = ( this_point->v * this_point->q );

		outcode |= previous_point->outcode;
		outcode2 &= previous_point->outcode;
		previous_point->next_vertex = this_point;

		previous_point = this_point;
		points++;
	}

	outcode |= previous_point->outcode;
	outcode2 &= previous_point->outcode;
	previous_point->next_vertex = NULL;

	if ( outcode2 )
	{

		// The polygon is totally off the screen!

		return ( NULL );
	}
	else
	{

		first_point->polygon_outcode = outcode;
	
		return ( first_point );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

