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

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

D3DCOLOR
	polygon_shadow_colour;

float
	polygon_shadow_zbias = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_plain_line ( vertex *line, real_colour colour )
{

	vertex
		*point1,
		*point2;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vertices = get_d3d_line_vertices_points_address ();

	vptr = vertices;

	point1 = line->next_vertex;

	point2 = line;

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point1->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point1->j );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point1->q );
	vptr->sz = ( point1->q * zbuffer_factor ) + zbuffer_constant;
	vptr->color = *( ( D3DCOLOR * ) &colour );
	vptr->specular = d3d_fog_intensity;
	vptr++;

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point2->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point2->j );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point2->q );
	vptr->sz = ( point2->q * zbuffer_factor ) + zbuffer_constant;
	vptr->color = *( ( D3DCOLOR * ) &colour );
	vptr->specular = d3d_fog_intensity;

	draw_line_primitive ( vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_flat_shaded_textured_line ( vertex *line, screen *texture, real_colour colour )
{

	vertex
		*point1,
		*point2;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vertices = get_d3d_line_vertices_points_address ();

	vptr = vertices;

	point2 = line;

	point1 = line->next_vertex;

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point1->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point1->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &point1->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &point1->v );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point1->q );
	vptr->sz = ( point1->q * zbuffer_factor ) + zbuffer_constant;
	vptr->color = colour.colour;
	vptr->specular = d3d_fog_intensity;
	vptr++;

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point2->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point2->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &point2->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &point2->v );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point2->q );
	vptr->sz = ( point2->q * zbuffer_factor ) + zbuffer_constant;
	vptr->color = colour.colour;
	vptr->specular = d3d_fog_intensity;

	draw_line_primitive ( vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_gouraud_shaded_line ( vertex *line, float red, float green, float blue )
{

	int
		r,
		g,
		b;

	float
		fr,
		fg,
		fb;

	vertex
		*point1,
		*point2;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vertices = get_d3d_line_vertices_points_address ();

	vptr = vertices;

	point2 = line;

	point1 = line->next_vertex;

	fr = ( point1->red * red ) + FLOAT_FLOAT_FACTOR;
	fg = ( point1->green * green ) + FLOAT_FLOAT_FACTOR;
	fb = ( point1->blue * blue ) + FLOAT_FLOAT_FACTOR;

	r = ( *( int * ) &fr ) - INTEGER_FLOAT_FACTOR;
	g = ( *( int * ) &fg ) - INTEGER_FLOAT_FACTOR;
	b = ( *( int * ) &fb ) - INTEGER_FLOAT_FACTOR;

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point1->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point1->j );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point1->q );
	vptr->sz = ( point1->q * zbuffer_factor ) + zbuffer_constant;

	vptr->color = RGB_MAKE ( r, g, b );
	vptr->specular = d3d_fog_intensity;

	vptr++;

	fr = ( point2->red * red ) + FLOAT_FLOAT_FACTOR;
	fg = ( point2->green * green ) + FLOAT_FLOAT_FACTOR;
	fb = ( point2->blue * blue ) + FLOAT_FLOAT_FACTOR;

	r = ( *( int * ) &fr ) - INTEGER_FLOAT_FACTOR;
	g = ( *( int * ) &fg ) - INTEGER_FLOAT_FACTOR;
	b = ( *( int * ) &fb ) - INTEGER_FLOAT_FACTOR;

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point2->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point2->j );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point2->q );
	vptr->sz = ( point2->q * zbuffer_factor ) + zbuffer_constant;

	vptr->color = RGB_MAKE ( r, g, b );
	vptr->specular = d3d_fog_intensity;

	draw_line_primitive ( vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_gouraud_shaded_textured_line ( vertex *line, screen *texture )
{

	vertex
		*point1,
		*point2;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vertices = get_d3d_line_vertices_points_address ();

	vptr = vertices;

	point2 = line;

	point1 = line->next_vertex;

	//
	// Put the first vertex on twice
	//

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point1->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point1->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &point1->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &point1->v );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point1->q );
	vptr->sz = ( point1->q * zbuffer_factor ) + zbuffer_constant;

	vptr->color = point1->colour;
	vptr->specular = d3d_fog_intensity;

	vptr++;

	*( ( int * ) &vptr->sx ) = *( ( int * ) &point2->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &point2->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &point2->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &point2->v );
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &point2->q );
	vptr->sz = ( point2->q * zbuffer_factor ) + zbuffer_constant;

	vptr->color = point2->colour;
	vptr->specular = d3d_fog_intensity;

	draw_line_primitive ( vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_plain_polygon ( vertex *polygon, real_colour colour, real_colour specular )
{

	int
		number_of_vertices;

	vertex
		*vert;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vert = polygon;

	vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );

	vptr = vertices;

	while ( vert )
	{

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		vptr->color = colour.colour;
		vptr->specular = specular.colour;

		vptr++;

		vert = vert->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_gouraud_shaded_polygon ( vertex *polygon, float red, float green, float blue, int alpha )
{

	int
		number_of_vertices,
		r,
		g,
		b;

	vertex
		*vert;

	LPD3DTLVERTEX
		vertices,
		vptr;

	real_colour
		colour,
		specular_colour;

	vert = polygon;

	vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );

	vptr = vertices;

	colour.alpha = alpha;

	while ( vert )
	{

		float
			fr,
			fg,
			fb;

		fr = ( vert->red * red ) + FLOAT_FLOAT_FACTOR;
		fg = ( vert->green * green ) + FLOAT_FLOAT_FACTOR;
		fb = ( vert->blue * blue ) + FLOAT_FLOAT_FACTOR;

		r = ( *( int * ) &fr ) - INTEGER_FLOAT_FACTOR;
		g = ( *( int * ) &fg ) - INTEGER_FLOAT_FACTOR;
		b = ( *( int * ) &fb ) - INTEGER_FLOAT_FACTOR;

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;

		colour.red = r;
		colour.green = g;
		colour.blue = b;

		vptr->color = colour.colour;

		specular_colour.colour = d3d_fog_intensity;
		specular_colour.red = vert->specular;
		specular_colour.green = vert->specular;
		specular_colour.blue = vert->specular;
		vptr->specular = specular_colour.colour;	//d3d_fog_intensity;
		vptr++;

		vert = vert->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_flat_shaded_textured_polygon ( vertex *polygon, struct REAL_COLOUR colour, struct REAL_COLOUR specular )
{

	int
		number_of_vertices;

	vertex
		*vert;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vert = polygon;

	vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );

	vptr = vertices;

	while ( vert )
	{

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
		*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		vptr->color = colour.colour;
		vptr->specular = specular.colour;
		vptr++;

		vert = vert->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_gouraud_shaded_textured_polygon ( vertex *polygon )
{

	int
		number_of_vertices;

	vertex
		*vert;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vert = polygon;

	vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );

	vptr = vertices;

	while ( vert )
	{

		real_colour
			specular;

		specular.colour = d3d_fog_intensity;
		specular.red = vert->specular;
		specular.green = vert->specular;
		specular.blue = vert->specular;

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
		*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;

		vptr->color = vert->colour;
		vptr->specular = specular.colour;

		vptr++;

		vert = vert->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_gouraud_coloured_distance_fogged_textured_polygon ( vertex *polygon, screen *texture )
{

	int
		number_of_vertices;

	vertex
		*vert;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vert = polygon;

	vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );

	vptr = vertices;

	while ( vert )
	{

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
		*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		vptr->color = vert->colour;
		vptr->specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );

		vptr++;

		vert = vert->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_shadow_polygon ( vertex *polygon, float r, float g, float b )
{

	int
		number_of_vertices;

	vertex
		*vert;

	LPD3DTLVERTEX
		vertices,
		vptr;

	//
	// First, set the rendering method
	//

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 0, NULL );

	vert = polygon;

	vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );

	vptr = vertices;

	while ( vert )
	{

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		vptr->color = polygon_shadow_colour;
		vptr->specular = d3d_fog_intensity;

		vptr++;

		vert = vert->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_wbuffered_shadow_textured_polygon ( vertex *polygon, screen *texture )
{

	int
		number_of_vertices;

	vertex
		*vert;

	LPD3DTLVERTEX
		vertices,
		vptr;

	//
	// First, make sure the texture has a hardware component
	//

	set_d3d_texture ( 0, load_hardware_texture_map ( texture ) );

	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );

	vert = polygon;

	vertices = get_d3d_vertices_address ( polygon, &number_of_vertices );

	vptr = vertices;

	while ( vert )
	{

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
		*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		vptr->color = polygon_shadow_colour;
		vptr->specular = d3d_fog_intensity;

		vptr++;

		vert = vert->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_shadow_colour ( float red, float green, float blue, float alpha )
{

	int
		r,
		g,
		b,
		a;

	float
		fr,
		fg,
		fb,
		fa;

	fr = red + FLOAT_FLOAT_FACTOR;
	fg = green + FLOAT_FLOAT_FACTOR;
	fb = blue + FLOAT_FLOAT_FACTOR;
	fa = alpha + FLOAT_FLOAT_FACTOR;

	r = ( *( int * ) &fr ) - INTEGER_FLOAT_FACTOR;
	g = ( *( int * ) &fg ) - INTEGER_FLOAT_FACTOR;
	b = ( *( int * ) &fb ) - INTEGER_FLOAT_FACTOR;
	a = ( *( int * ) &fa ) - INTEGER_FLOAT_FACTOR;

	polygon_shadow_colour = RGBA_MAKE ( r, g, b, a );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_shadow_zbias ( float bias )
{

	polygon_shadow_zbias = bias;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

