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

#include "terrain.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex
	terrain_3d_copied_points[128];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int get_word_list_outcodes ( int number_of_points, short int *list, int *other_outcode );

#pragma aux get_word_list_outcodes =								\
	"xor	eax, eax"														\
	"xor	edx, edx"														\
	"xor	ebx, ebx"														\
	"mov	ax, WORD PTR [ esi ]"										\
	"lea	esi, [ esi + 2 ]"												\
	"mov	bl, BYTE PTR transformed_3d_point_outcodes[eax]"	\
	"dec	ecx"																\
	"mov	dh, 0xff"														\
"MY_LOOP:"																	\
	"xor	eax, eax"														\
	"or	dl, bl"															\
	"mov	ax, WORD PTR [ esi ]"										\
	"lea	esi, [ esi + 2 ]"												\
	"and	dh, bl"															\
	"dec	ecx"																\
	"mov	bl, BYTE PTR transformed_3d_point_outcodes[eax]"	\
	"jg	MY_LOOP"															\
	"and	dh, bl"															\
	"xor	eax, eax"														\
	"or	dl, bl"															\
	"xor	ebx, ebx"														\
	"mov	al, dh"															\
	"mov	bl, dl"															\
	"mov	dword ptr [ edi ], eax"										\
parm [ ecx ] [ esi ] [ edi ] 											\
value [ ebx ]																\
modify exact [ esi ecx ebx edx eax ];
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int get_word_triangle_outcodes ( short int *list, int *other_outcode );

#pragma aux get_word_triangle_outcodes =							\
	"xor	eax, eax"														\
	"xor	ecx, ecx"														\
	"mov	ax, WORD PTR [ esi ]"										\
	"xor	edx, edx"														\
	"mov	cl, BYTE PTR transformed_3d_point_outcodes[eax]"	\
	"xor	eax, eax"														\
	"mov	ax, WORD PTR [ esi + 2 ]"									\
	"mov	ch, BYTE PTR transformed_3d_point_outcodes[eax]"	\
	"xor	eax, eax"														\
	"mov	ax, WORD PTR [ esi + 4 ]"									\
	"mov	dl, BYTE PTR transformed_3d_point_outcodes[eax]"	\
	"xor	eax, eax"														\
	"xor	ebx, ebx"														\
	"mov	al, cl"															\
	"mov	bl, cl"															\
	"and	al, ch"															\
	"or	bl, ch"															\
	"and	al, dl"															\
	"or	bl, dl"															\
	"mov	[ edi ], eax"													\
parm [ esi ] [ edi ] 													\
value [ ebx ]																\
modify exact [ esi ecx ebx edx eax ];
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_terrain_word_polygon ( int num_points, terrain_3d_point_word_reference *reference_points, int *polygon_outcode )
{

	int
		count,
		outcode,
		outcode2;

	//
	// Always do 3 points in a face, cos they're guaranteed
	//

	outcode = transformed_3d_point_outcodes[ reference_points[0].point ];
	outcode2 = transformed_3d_point_outcodes[ reference_points[0].point ];

	outcode |= transformed_3d_point_outcodes[ reference_points[1].point ];
	outcode2 &= transformed_3d_point_outcodes[ reference_points[1].point ];

	outcode |= transformed_3d_point_outcodes[ reference_points[2].point ];
	outcode2 &= transformed_3d_point_outcodes[ reference_points[2].point ];

	for ( count = 3; count < num_points; count++ )
	{

		outcode |= transformed_3d_point_outcodes[ reference_points[count].point ];
		outcode2 &= transformed_3d_point_outcodes[ reference_points[count].point ];
	}

	if ( outcode2 )
	{

		//
		// The polygon is totally off the screen!
		//

		return ( FALSE );
	}
	else
	{

		//
		// Some part of the polygon is visible, check for fogging
		//

		*polygon_outcode = outcode;
	
		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_terrain_byte_polygon ( int num_points, terrain_3d_point_byte_reference *reference_points, int *polygon_outcode )
{

	int
		count;

	unsigned char
		outcode,
		outcode2;

	//
	// Always do 3 points in a face, cos they're guaranteed
	//

	outcode = transformed_3d_point_outcodes[ reference_points->point ];
	outcode2 = transformed_3d_point_outcodes[ reference_points->point ];
	reference_points++;

	outcode |= transformed_3d_point_outcodes[ reference_points->point ];
	outcode2 &= transformed_3d_point_outcodes[ reference_points->point ];
	reference_points++;

	outcode |= transformed_3d_point_outcodes[ reference_points->point ];
	outcode2 &= transformed_3d_point_outcodes[ reference_points->point ];
	reference_points++;

	for ( count = ( num_points - 1 ); count > 2; count-- )
	{

		outcode |= transformed_3d_point_outcodes[ reference_points->point ];
		outcode2 &= transformed_3d_point_outcodes[ reference_points->point ];
		reference_points++;
	}

	if ( outcode2 )
	{

		//
		// The polygon is totally off the screen!
		//

		return ( FALSE );
	}
	else
	{

		//
		// Some part of the polygon is visible, check for fogging
		//

		*polygon_outcode = outcode;
	
		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_terrain_triangle ( int *reference_points, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	outcode = transformed_3d_point_outcodes[ reference_points[0] ];
	outcode2 = transformed_3d_point_outcodes[ reference_points[0] ];

	outcode |= transformed_3d_point_outcodes[ reference_points[1] ];
	outcode2 &= transformed_3d_point_outcodes[ reference_points[1] ];

	outcode |= transformed_3d_point_outcodes[ reference_points[2] ];
	outcode2 &= transformed_3d_point_outcodes[ reference_points[2] ];

	if ( outcode2 )
	{

		return ( FALSE );
	}
	else
	{

		*polygon_outcode = outcode;
	
		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int terrain_alpha_visible_word ( int number_of_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count;

	unsigned char
		alpha;

	alpha = 0;

	for ( count = 0; count < number_of_points; count++ )
	{

		alpha |= transformed_3d_point_colours[ reference_points[count].point ].alpha;
	}

	return ( alpha );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int terrain_alpha_visible_byte ( int number_of_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count;

	unsigned char
		alpha;

	alpha = 0;

	for ( count = 0; count < number_of_points; count++ )
	{

		alpha |= transformed_3d_point_colours[ reference_points[count].point ].alpha;
	}

	return ( alpha );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void construct_3d_terrain_word_clipping_primitive ( int number_of_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	float
		texture_scale;

	terrain_3d_faces_constructed++;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	for ( count = 0; count < number_of_points; count++ )
	{
	
		this_point = reference_points[count].point;
		*( ( int * ) &clipping_vertices[count].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
		*( ( int * ) &clipping_vertices[count].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
		*( ( int * ) &clipping_vertices[count].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
		*( ( int * ) &clipping_vertices[count].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
		*( ( int * ) &clipping_vertices[count].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
		*( ( int * ) &clipping_vertices[count].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
		clipping_vertices[count].outcode = transformed_3d_point_outcodes[this_point];
		clipping_vertices[count].colour = transformed_3d_point_colours[this_point].colour;
		clipping_vertices[count].fog = transformed_3d_point_colours[this_point].fog;
		clipping_vertices[count].u = current_terrain_points_xz[this_point].x * texture_scale;
		clipping_vertices[count].v = current_terrain_points_xz[this_point].z * texture_scale;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void construct_3d_terrain_byte_clipping_primitive ( int number_of_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	float
		texture_scale;

	terrain_3d_faces_constructed++;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	for ( count = 0; count < number_of_points; count++ )
	{
	
		this_point = reference_points[count].point;
		*( ( int * ) &clipping_vertices[count].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
		*( ( int * ) &clipping_vertices[count].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
		*( ( int * ) &clipping_vertices[count].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
		*( ( int * ) &clipping_vertices[count].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
		*( ( int * ) &clipping_vertices[count].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
		*( ( int * ) &clipping_vertices[count].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
		clipping_vertices[count].outcode = transformed_3d_point_outcodes[this_point];
		clipping_vertices[count].colour = transformed_3d_point_colours[this_point].colour;
		clipping_vertices[count].fog = transformed_3d_point_colours[this_point].fog;
		clipping_vertices[count].u = current_terrain_points_xz[this_point].x * texture_scale;
		clipping_vertices[count].v = current_terrain_points_xz[this_point].z * texture_scale;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_terrain_triangle ( int *reference_points )
{

	int
		this_point;

	float
		texture_scale;

	terrain_3d_faces_constructed++;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	this_point = reference_points[0];
	*( ( int * ) &polygon_3d_vertices[0].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[0].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[0].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[0].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[0].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[0].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[0].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[0].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[0].u = current_terrain_points_xz[this_point].x * texture_scale;
	polygon_3d_vertices[0].v = current_terrain_points_xz[this_point].z * texture_scale;
	polygon_3d_vertices[0].normal_index = transformed_3d_point_colours[this_point].normal_index;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	this_point = reference_points[1];
	*( ( int * ) &polygon_3d_vertices[1].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[1].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[1].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[1].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[1].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[1].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[1].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[1].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[1].u = current_terrain_points_xz[this_point].x * texture_scale;
	polygon_3d_vertices[1].v = current_terrain_points_xz[this_point].z * texture_scale;
	polygon_3d_vertices[1].normal_index = transformed_3d_point_colours[this_point].normal_index;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];

	this_point = reference_points[2];
	*( ( int * ) &polygon_3d_vertices[2].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[2].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[2].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[2].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[2].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[2].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[2].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[2].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[2].u = current_terrain_points_xz[this_point].x * texture_scale;
	polygon_3d_vertices[2].v = current_terrain_points_xz[this_point].z * texture_scale;
	polygon_3d_vertices[2].normal_index = transformed_3d_point_colours[this_point].normal_index;
	polygon_3d_vertices[2].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_terrain_xy_triangle ( int *reference_points )
{

	int
		this_point,
		normal_index;

	float
		xz_texture_scale,
		y_texture_scale,
		y,
		u,
		v;

	terrain_3d_faces_constructed++;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	this_point = reference_points[0];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].x * xz_texture_scale;
	v = y * y_texture_scale;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[this_point].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[this_point].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[this_point].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[this_point].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[this_point].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[this_point].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[0].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[0].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[0].u = u;
	polygon_3d_vertices[0].v = v;
	polygon_3d_vertices[0].normal_index = normal_index;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	this_point = reference_points[1];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].x * xz_texture_scale;
	v = y * y_texture_scale;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[this_point].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[this_point].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[this_point].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[this_point].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[this_point].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[this_point].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[1].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[1].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[1].u = u;
	polygon_3d_vertices[1].v = v;
	polygon_3d_vertices[1].normal_index = normal_index;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];

	this_point = reference_points[2];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].x * xz_texture_scale;
	v = y * y_texture_scale;
	polygon_3d_vertices[2].x = transformed_3d_3d_points[this_point].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[this_point].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[this_point].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[this_point].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[this_point].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[this_point].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[2].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[2].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[2].u = u;
	polygon_3d_vertices[2].v = v;
	polygon_3d_vertices[2].normal_index = normal_index;
	polygon_3d_vertices[2].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_terrain_zy_triangle ( int *reference_points )
{

	int
		this_point,
		normal_index;

	float
		xz_texture_scale,
		y_texture_scale,
		y,
		u,
		v;

	terrain_3d_faces_constructed++;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	this_point = reference_points[0];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].z * xz_texture_scale;
	v = y * y_texture_scale;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[this_point].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[this_point].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[this_point].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[this_point].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[this_point].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[this_point].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[0].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[0].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[0].u = u;
	polygon_3d_vertices[0].v = v;
	polygon_3d_vertices[0].normal_index = normal_index;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	this_point = reference_points[1];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].z * xz_texture_scale;
	v = y * y_texture_scale;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[this_point].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[this_point].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[this_point].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[this_point].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[this_point].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[this_point].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[1].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[1].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[1].u = u;
	polygon_3d_vertices[1].v = v;
	polygon_3d_vertices[1].normal_index = normal_index;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];

	this_point = reference_points[2];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].z * xz_texture_scale;
	v = y * y_texture_scale;
	polygon_3d_vertices[2].x = transformed_3d_3d_points[this_point].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[this_point].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[this_point].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[this_point].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[this_point].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[this_point].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[2].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[2].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[2].u = u;
	polygon_3d_vertices[2].v = v;
	polygon_3d_vertices[2].normal_index = normal_index;
	polygon_3d_vertices[2].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_terrain_dual_texture_triangle ( int *reference_points )
{

	int
		this_point,
		normal_index;

	float
		texture_scale,
		texture_scale2;

	terrain_3d_faces_constructed++;

	texture_scale = current_terrain_type_class->xz_texture_scale;
	texture_scale2 = current_terrain_type_class->xz_texture_scale2;

	this_point = reference_points[0];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	*( ( int * ) &polygon_3d_vertices[0].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[0].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[0].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[0].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[0].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[0].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[0].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[0].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[0].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[0].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[0].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[0].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[0].u = current_terrain_points_xz[this_point].x * texture_scale;
	polygon_3d_vertices[0].v = current_terrain_points_xz[this_point].z * texture_scale;
	polygon_3d_vertices[0].u2 = current_terrain_points_xz[this_point].x * texture_scale2;
	polygon_3d_vertices[0].v2 = current_terrain_points_xz[this_point].z * texture_scale2;
	polygon_3d_vertices[0].normal_index = normal_index;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	this_point = reference_points[1];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	*( ( int * ) &polygon_3d_vertices[1].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[1].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[1].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[1].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[1].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[1].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[1].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[1].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[1].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[1].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[1].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[1].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[1].u = current_terrain_points_xz[this_point].x * texture_scale;
	polygon_3d_vertices[1].v = current_terrain_points_xz[this_point].z * texture_scale;
	polygon_3d_vertices[1].u2 = current_terrain_points_xz[this_point].x * texture_scale2;
	polygon_3d_vertices[1].v2 = current_terrain_points_xz[this_point].z * texture_scale2;
	polygon_3d_vertices[1].normal_index = normal_index;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];

	this_point = reference_points[2];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	*( ( int * ) &polygon_3d_vertices[2].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[2].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[2].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[2].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[2].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[2].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[2].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[2].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[2].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[2].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[2].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[2].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[2].u = current_terrain_points_xz[this_point].x * texture_scale;
	polygon_3d_vertices[2].v = current_terrain_points_xz[this_point].z * texture_scale;
	polygon_3d_vertices[2].u2 = current_terrain_points_xz[this_point].x * texture_scale2;
	polygon_3d_vertices[2].v2 = current_terrain_points_xz[this_point].z * texture_scale2;
	polygon_3d_vertices[2].normal_index = normal_index;
	polygon_3d_vertices[2].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_terrain_dual_texture_xy_triangle ( int *reference_points )
{

	int
		this_point,
		normal_index;

	float
		xz_texture_scale,
		xz_texture_scale2,
		y_texture_scale,
		y_texture_scale2,
		y,
		u,
		u2,
		v,
		v2;

	terrain_3d_faces_constructed++;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	xz_texture_scale2 = current_terrain_type_class->xz_texture_scale2;
	y_texture_scale = current_terrain_type_class->y_texture_scale;
	y_texture_scale2 = current_terrain_type_class->y_texture_scale2;

	this_point = reference_points[0];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].x * xz_texture_scale;
	u2 = current_terrain_points_xz[this_point].x * xz_texture_scale2;
	v = y * y_texture_scale;
	v2 = y * y_texture_scale2;
	*( ( int * ) &polygon_3d_vertices[0].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[0].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[0].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[0].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[0].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[0].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[0].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[0].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[0].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[0].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[0].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[0].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[0].u = u;
	polygon_3d_vertices[0].v = v;
	polygon_3d_vertices[0].u2 = u2;
	polygon_3d_vertices[0].v2 = v2;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	this_point = reference_points[1];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].x * xz_texture_scale;
	u2 = current_terrain_points_xz[this_point].x * xz_texture_scale2;
	v = y * y_texture_scale;
	v2 = y * y_texture_scale2;
	*( ( int * ) &polygon_3d_vertices[1].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[1].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[1].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[1].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[1].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[1].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[1].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[1].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[1].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[1].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[1].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[1].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[1].u = u;
	polygon_3d_vertices[1].v = v;
	polygon_3d_vertices[1].u2 = u2;
	polygon_3d_vertices[1].v2 = v2;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];

	this_point = reference_points[2];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].x * xz_texture_scale;
	u2 = current_terrain_points_xz[this_point].x * xz_texture_scale2;
	v = y * y_texture_scale;
	v2 = y * y_texture_scale2;
	*( ( int * ) &polygon_3d_vertices[2].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[2].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[2].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[2].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[2].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[2].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[2].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[2].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[2].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[2].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[2].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[2].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[2].u = u;
	polygon_3d_vertices[2].v = v;
	polygon_3d_vertices[2].u2 = u2;
	polygon_3d_vertices[2].v2 = v2;
	polygon_3d_vertices[2].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


vertex *construct_3d_terrain_dual_texture_zy_triangle ( int *reference_points )
{

	int
		this_point,
		normal_index;

	float
		xz_texture_scale,
		xz_texture_scale2,
		y_texture_scale,
		y_texture_scale2,
		y,
		u,
		u2,
		v,
		v2;

	terrain_3d_faces_constructed++;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	xz_texture_scale2 = current_terrain_type_class->xz_texture_scale2;
	y_texture_scale = current_terrain_type_class->y_texture_scale;
	y_texture_scale2 = current_terrain_type_class->y_texture_scale2;

	this_point = reference_points[0];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].z * xz_texture_scale;
	u2 = current_terrain_points_xz[this_point].z * xz_texture_scale2;
	v = y * y_texture_scale;
	v2 = y * y_texture_scale2;
	*( ( int * ) &polygon_3d_vertices[0].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[0].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[0].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[0].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[0].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[0].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[0].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[0].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[0].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[0].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[0].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[0].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[0].u = u;
	polygon_3d_vertices[0].v = v;
	polygon_3d_vertices[0].u2 = u2;
	polygon_3d_vertices[0].v2 = v2;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	this_point = reference_points[1];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].z * xz_texture_scale;
	u2 = current_terrain_points_xz[this_point].z * xz_texture_scale2;
	v = y * y_texture_scale;
	v2 = y * y_texture_scale2;
	*( ( int * ) &polygon_3d_vertices[1].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[1].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[1].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[1].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[1].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[1].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[1].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[1].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[1].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[1].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[1].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[1].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[1].u = u;
	polygon_3d_vertices[1].v = v;
	polygon_3d_vertices[1].u2 = u2;
	polygon_3d_vertices[1].v2 = v2;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];

	this_point = reference_points[2];
	normal_index = transformed_3d_point_colours[this_point].normal_index;
	y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );
	u = current_terrain_points_xz[this_point].z * xz_texture_scale;
	u2 = current_terrain_points_xz[this_point].z * xz_texture_scale2;
	v = y * y_texture_scale;
	v2 = y * y_texture_scale2;
	*( ( int * ) &polygon_3d_vertices[2].x ) = *( ( int * ) &transformed_3d_3d_points[this_point].x );
	*( ( int * ) &polygon_3d_vertices[2].y ) = *( ( int * ) &transformed_3d_3d_points[this_point].y );
	*( ( int * ) &polygon_3d_vertices[2].z ) = *( ( int * ) &transformed_3d_2d_points[this_point].z );
	*( ( int * ) &polygon_3d_vertices[2].i ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
	*( ( int * ) &polygon_3d_vertices[2].j ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
	*( ( int * ) &polygon_3d_vertices[2].q ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[this_point];
	polygon_3d_vertices[2].colour = transformed_3d_point_colours[this_point].colour;
	polygon_3d_vertices[2].fog = transformed_3d_point_colours[this_point].fog;
	polygon_3d_vertices[2].red2 = terrain_3d_transformed_point_normals[normal_index].colour.red;
	polygon_3d_vertices[2].green2 = terrain_3d_transformed_point_normals[normal_index].colour.green;
	polygon_3d_vertices[2].blue2 = terrain_3d_transformed_point_normals[normal_index].colour.blue;
	polygon_3d_vertices[2].alpha2 = transformed_3d_point_colours[this_point].alpha;
	polygon_3d_vertices[2].u = u;
	polygon_3d_vertices[2].v = v;
	polygon_3d_vertices[2].u2 = u2;
	polygon_3d_vertices[2].v2 = v2;
	polygon_3d_vertices[2].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


