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

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// This renders whole triangle fans - these HAVE to be unclipped.
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_object_triangle_non_textured_fan ( int num_points, point_3d_plain_reference *points, int base_point )
{

	int
		count,
		this_point;

	vertex
		*vert;

	float
		fr,
		fg,
		fb;

	int
		r,
		g,
		b;

	LPD3DTLVERTEX
		destination_vertices;

	vertex
		*transformed_points;

	transformed_points = &transformed_3d_points[base_point];

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	for ( count = 0; count < num_points; count++ )
	{
	
		this_point = points[count].point;
	
		vert = &transformed_points[this_point];
	
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = vert->q;
		destination_vertices[count].rhw = vert->q;
		fr = vert->red + FLOAT_FLOAT_FACTOR;
		fg = vert->green + FLOAT_FLOAT_FACTOR;
		fb = vert->blue + FLOAT_FLOAT_FACTOR;
		r = ( *( int * ) &fr ) - INTEGER_FLOAT_FACTOR;
		g = ( *( int * ) &fg ) - INTEGER_FLOAT_FACTOR;
		b = ( *( int * ) &fb ) - INTEGER_FLOAT_FACTOR;
		destination_vertices[count].color = RGB_MAKE ( r, g, b );
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular_red, vert->specular_green, vert->specular_blue, f );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

