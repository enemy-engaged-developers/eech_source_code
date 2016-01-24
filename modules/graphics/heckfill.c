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

#include "graphics.h"

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int
	stack_register_location;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define STEP_PLAIN_TRIANGLE_EDGE(EDGE) \
				{ \
					EDGE.i += EDGE.i_step; \
					EDGE.j++; \
					EDGE.height--; \
					EDGE.error_term += EDGE.numerator; \
					if ( EDGE.error_term >= EDGE.denominator ) \
					{ \
						EDGE.i++; \
						EDGE.error_term -= EDGE.denominator; \
					} \
				}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int step_triangle_edge ( triangle_edge_data *edge );

static void calculate_floor_div_mod ( int numerator, int denominator, int *floor, int *mod );

static int construct_triangle_gradients ( void );

static void construct_triangle_edge ( int top, int bottom, triangle_edge_data *edge );

static void fill_plain_horizontal_scanline ( unsigned int *dst, triangle_edge_data *left, triangle_edge_data *right, unsigned int colour );

static void fill_software_plain_polygon ( unsigned int colour );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_floor_div_mod ( int numerator, int denominator, int *floor, int *mod )
{

	ASSERT ( denominator > 0 );

	if ( numerator >= 0 )
	{

		//
		// positive case, C is okay
		//

		*floor = get_div_mod ( numerator, denominator, mod );
	}
	else
	{

		//
		// Numerator is negative, do the right thing
		//

		*floor = - ( get_div_mod ( ( -numerator ), denominator, mod ) );

		if ( *mod )
		{

			//
			// there is a remainder
			//

			(*floor)--;

			*mod = denominator - *mod;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int construct_triangle_gradients ( void )
{

	float
		x1y0,
		x0y1,
		x1y0_minus_x0y1,
		d02i,
		d12i,
		d02j,
		d12j,
		one_over_dx,
		one_over_dy;

	d02i = triangle_point0->i - triangle_point2->i;
	d12i = triangle_point1->i - triangle_point2->i;
	d02j = triangle_point0->j - triangle_point2->j;
	d12j = triangle_point1->j - triangle_point2->j;

	x0y1 = d02i * d12j;
	x1y0 = d12i * d02j;
	x1y0_minus_x0y1 = x1y0 - x0y1;

	if ( *( ( int * ) &x1y0_minus_x0y1 ) == *( ( int * ) &float_value_zero ) )
	{

		return ( FALSE );
	}

	one_over_dx = 1.0 / x1y0_minus_x0y1;

	one_over_dy = -one_over_dx;

	triangle_gradients_points[0] = triangle_point0;
	triangle_gradients_points[1] = triangle_point1;
	triangle_gradients_points[2] = triangle_point2;

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void construct_plain_triangle_edge ( int top, int bottom, triangle_edge_data *edge )
{

	int
		j_end;

	edge->j = ceil_fixed28_point4 ( triangle_points[top].j );

	j_end = ceil_fixed28_point4 ( triangle_points[bottom].j );

	edge->height = j_end - edge->j;

	if ( edge->height )
	{

		int
			dn,
			dm,
			initial_numerator;

		dn = triangle_points[bottom].j - triangle_points[top].j;

		dm = triangle_points[bottom].i - triangle_points[top].i;

		initial_numerator = ( dm * 16 * edge->j ) - ( dm * triangle_points[top].j ) +
					( dn * triangle_points[top].i ) - ( 1 ) + ( dn * 16 );

		calculate_floor_div_mod ( initial_numerator, ( dn * 16 ), &edge->i, &edge->error_term );

		calculate_floor_div_mod ( ( dm * 16 ), ( dn * 16 ), &edge->i_step, &edge->numerator );

		edge->denominator = ( dn * 16 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_triangle ( float x1, float y1, float x2, float y2, float x3, float y3, rgb_colour colour )
{

	vertex
		points[3],
		*polygon;

	float
		oxmax,
		oxmin,
		oymax,
		oymin;

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	int
		outcode,
		outcode2;

	points[0].i = x1;
	points[0].j = y1;
	points[0].next_vertex = &points[1];

	points[1].i = x2;
	points[1].j = y2;
	points[1].next_vertex = &points[2];

	points[2].i = x3;
	points[2].j = y3;
	points[2].next_vertex = NULL;

	polygon = points;

	while ( polygon )
	{

		oxmax = active_viewport.x_max - polygon->i;
		oxmin = polygon->i - active_viewport.x_min;
		oymax = active_viewport.y_max - polygon->j;
		oymin = polygon->j - active_viewport.y_min;

		ixmax = *( ( unsigned int * ) &oxmax );
		ixmin = *( ( unsigned int * ) &oxmin );
		iymax = *( ( unsigned int * ) &oymax );
		iymin = *( ( unsigned int * ) &oymin );

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
		polygon->outcode = ( ixmin | ixmax );

		polygon = polygon->next_vertex;
	}

	outcode = points[0].outcode;
	outcode2 = points[0].outcode;

	outcode |= points[1].outcode;
	outcode2 &= points[1].outcode;

	outcode |= points[2].outcode;
	outcode2 &= points[2].outcode;

	if ( outcode2 == 0 )
	{

		unsigned int
			triangle_colour;

		vertex
			*fan_centre,
			*point1,
			*point2;

		polygon = points;

		if ( outcode )
		{

			clip_3d_coord = 0;

			polygon = clip_3d_polygon ( polygon, outcode );
		}

		if ( polygon )
		{

			//
			// Draw the polygon
			//

			triangle_colour = colour.colour;

			fan_centre = polygon;

			point1 = polygon->next_vertex;

			point2 = point1->next_vertex;

			while ( point2 )
			{

				convert_float_to_int ( ( fan_centre->i * 16 ), &triangle_points[0].i );
				convert_float_to_int ( ( fan_centre->j * 16 ), &triangle_points[0].j );

				convert_float_to_int ( ( point1->i * 16 ), &triangle_points[1].i );
				convert_float_to_int ( ( point1->j * 16 ), &triangle_points[1].j );

				convert_float_to_int ( ( point2->i * 16 ), &triangle_points[2].i );
				convert_float_to_int ( ( point2->j * 16 ), &triangle_points[2].j );

				triangle_point0 = fan_centre;
				triangle_point1 = point1;
				triangle_point2 = point2;

				fill_software_plain_polygon ( triangle_colour );

				point1 = point2;

				point2 = point2->next_vertex;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
#ifdef __WATCOMC__

void solid_fill_horizontal_line ( unsigned int *ptr, unsigned colour, int count );

#pragma aux solid_fill_horizontal_line =	\
	"test edi, 2"									\
	"je	noleadin"								\
	"dec	edx"										\
	"mov	[ edi ], cx"							\
	"add	edi, 2"									\
"noleadin:"											\
	"cmp	edx, 4"									\
	"jl	leadout2"								\
"loopmain:"											\
	"mov	[ edi ], ecx"							\
	"sub	edx, 4"									\
	"mov	[ edi + 4 ], ecx"						\
	"lea	edi, [ edi + 8 ]"						\
	"cmp	edx, 4"									\
	"jge	loopmain"								\
"leadout2:"											\
	"cmp	edx, 2"									\
	"jl	leadout0"								\
	"mov	[ edi ], ecx"							\
	"add	edi, 4"									\
	"sub	edx, 2"									\
"leadout0:"											\
	"test	edx, edx"								\
	"jle	endprag"									\
	"mov	[ edi ], cx"							\
"endprag:"											\
parm [ edi ] [ ecx ]	[ edx ]					\
modify exact [ eax ebx ecx edx edi ];
#endif

#else

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void solid_fill_horizontal_line ( unsigned int *ptr, unsigned colour, int count )
{
	for ( ; count > 0; count-- )
	{

		*ptr++ = colour;
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fill_software_plain_polygon ( unsigned int colour )
{

	int
		top,
		middle,
		bottom,
		middle_for_compare,
		bottom_for_compare,
		middle_is_left,
		height,
		y,
		screen_pitch;

	fixed28_point4
		y0,
		y1,
		y2;

	triangle_edge_data
		*left_edge,
		*right_edge;

	unsigned int
		*screen_ptr;

	//
	// This routine only accepts TRIANGLES at the moment.
	//

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	screen_ptr = get_screen_data ( active_screen );

	screen_pitch = get_screen_pitch ( active_screen );

	y0 = triangle_points[0].j;
	y1 = triangle_points[1].j;
	y2 = triangle_points[2].j;

	//
	// sort vertices in y
	//

	if ( y0 < y1 )
	{

		if ( y2 < y0 )	{ top = 2; middle = 0; bottom = 1; middle_for_compare = 0; bottom_for_compare = 1; }
		else
		{

			top = 0;

			if ( y1 < y2 )	{ middle = 1; bottom = 2; middle_for_compare = 1; bottom_for_compare = 2; }
			else				{ middle = 2; bottom = 1; middle_for_compare = 2; bottom_for_compare = 1; }
		}
	}
	else
	{

		if ( y2 < y1) { top = 2; middle = 1; bottom = 0; middle_for_compare = 1; bottom_for_compare = 0; }
		else
		{

			top = 1;

			if ( y0 < y2 )	{ middle = 0; bottom = 2; middle_for_compare = 3; bottom_for_compare = 2; }
			else				{ middle = 2; bottom = 0; middle_for_compare = 2; bottom_for_compare = 3; }
		}
	}

	construct_triangle_gradients ();

	construct_plain_triangle_edge ( top, bottom, &top_to_bottom_edge );
	construct_plain_triangle_edge ( top, middle, &top_to_middle_edge );
	construct_plain_triangle_edge ( middle, bottom, &middle_to_bottom_edge );

	//
	// the triangle is clockwise, so if bottom > middle then middle is right
	//

	if ( bottom_for_compare > middle_for_compare)
	{

		middle_is_left = FALSE;
		left_edge = &top_to_bottom_edge;
		right_edge = &top_to_middle_edge;
	}
	else
	{

		middle_is_left = TRUE;
		left_edge = &top_to_middle_edge;
		right_edge = &top_to_bottom_edge;
	}

	height = top_to_middle_edge.height;

	y = top_to_middle_edge.j;

	screen_ptr += top_to_middle_edge.j * screen_pitch;

	while ( height-- )
	{

		int
			width;

		unsigned int
			*word_ptr;

		word_ptr = screen_ptr;

		word_ptr += left_edge->i;

		width = right_edge->i - left_edge->i;

		if ( width > 0 )
		{

			solid_fill_horizontal_line ( word_ptr, colour, width );
		}

		STEP_PLAIN_TRIANGLE_EDGE ( top_to_middle_edge );

		STEP_PLAIN_TRIANGLE_EDGE ( top_to_bottom_edge );

		screen_ptr += screen_pitch;

		y++;
	}

	height = middle_to_bottom_edge.height;

	if ( middle_is_left )
	{

		left_edge = &middle_to_bottom_edge;

		right_edge = &top_to_bottom_edge;
	}
	else
	{

		left_edge = &top_to_bottom_edge;

		right_edge = &middle_to_bottom_edge;
	}

	while ( height--)
	{

		int
			width;

		unsigned int
			*word_ptr;

		word_ptr = screen_ptr;

		word_ptr += left_edge->i;

		width = right_edge->i - left_edge->i;

		if ( width > 0 )
		{

			solid_fill_horizontal_line ( word_ptr, colour, width );
		}

		STEP_PLAIN_TRIANGLE_EDGE ( middle_to_bottom_edge );

		STEP_PLAIN_TRIANGLE_EDGE ( top_to_bottom_edge );

		screen_ptr += screen_pitch;

		y++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
