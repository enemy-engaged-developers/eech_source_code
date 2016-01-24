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

#include "terrain.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_word_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			u,
			v;

		this_point = terrain_3d_sector_point_word_references[count].point;

		v = current_terrain_points_xz[this_point].z;
		u = current_terrain_points_xz[this_point].x;

		*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
		v *= texture_scale;

		*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );

		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;

		u *= texture_scale;

		*( ( int * ) &destination_vertices[count].rhw ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );

		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;

		destination_vertices[count].tv = v;
		destination_vertices[count].tu = u;

		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_byte_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			u,
			v;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		v = current_terrain_points_xz[this_point].z;
		u = current_terrain_points_xz[this_point].x;

		*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &transformed_3d_2d_points[this_point].i );
		v *= texture_scale;

		*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &transformed_3d_2d_points[this_point].j );
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;

		u *= texture_scale;

		*( ( int * ) &destination_vertices[count].rhw ) = *( ( int * ) &transformed_3d_2d_points[this_point].q );

		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;

		destination_vertices[count].tv = v;
		destination_vertices[count].tu = u;

		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_word_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		this_point = terrain_3d_sector_point_word_references[count].point;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_byte_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	//
	// Always do 3 points in a face, cos they're guaranteed
	//

	for ( count = 0; count < num_points; count++ )
	{

		this_point = terrain_3d_sector_point_byte_references[count].point;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_word_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_byte_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_word_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_byte_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_word_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_byte_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_word_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_byte_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_word_colour_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		this_point = terrain_3d_sector_point_word_references[count].point;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_byte_colour_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_word_colour_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		this_point = terrain_3d_sector_point_word_references[count].point;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_byte_colour_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_word_colour_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		int
			red,
			green,
			blue,
			normal_index;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_byte_colour_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	//
	// Always do 3 points in a face, cos they're guaranteed
	//

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_word_colour_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		float
			y;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_byte_colour_fan ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_word_colour_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		int
			red,
			green,
			blue,
			normal_index;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;
		destination_vertices[count].color = transformed_3d_point_colours[this_point].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_xy_byte_colour_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	//
	// Always do 3 points in a face, cos they're guaranteed
	//

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_word_colour_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		float
			y;

		this_point = terrain_3d_sector_point_word_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_texture_zy_byte_colour_strip ( int num_points )
{

	int
		count,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		int
			red,
			green,
			blue,
			normal_index;

		float
			y;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = D3DCOLOR_XRGB ( red, green, blue );
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_word_fan ( int num_points )
{

	int
		count,
		this_point,
		normal_index;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale2;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_word_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_byte_fan ( int num_points )
{

	int
		count,
		this_point,
		normal_index;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale2;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;

		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_word_strip ( int num_points )
{

	int
		count,
		this_point,
		normal_index;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale2;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_word_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_strip ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_byte_strip ( int num_points )
{

	int
		count,
		this_point,
		normal_index;

	LPTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale2;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_strip ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_xy_word_fan ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_word_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_xy_byte_fan ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_zy_word_fan ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_word_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_zy_byte_fan ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_xy_word_strip ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_word_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_strip ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_xy_byte_strip ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_strip ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_zy_word_strip ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_word_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_strip ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_texture_zy_byte_strip ( int num_points )
{

	int
		count,
		normal_index,
		this_point;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.red = terrain_3d_transformed_point_normals[normal_index].colour.red;
		this_colour.green = terrain_3d_transformed_point_normals[normal_index].colour.green;
		this_colour.blue = terrain_3d_transformed_point_normals[normal_index].colour.blue;
		this_colour.alpha = transformed_3d_point_colours[this_point].alpha;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = 0;
	}

	add_terrain_3d_buffered_triangle_strip ( num_points, current_terrain_type_class->texture2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_secondary_vertex_polygon ( vertex *polygon )
{

	int
		count;

	unsigned char
		alpha;

	LPTLVERTEX
		destination_vertices;

	destination_vertices = get_terrain_3d_buffered_vertices ( 64 );

	count = 0;

	alpha = 0;

	while ( polygon )
	{

		destination_vertices[count].tu = polygon->u2;
		destination_vertices[count].tv = polygon->v2;
		destination_vertices[count].sx = polygon->i;
		destination_vertices[count].sy = polygon->j;
		destination_vertices[count].sz = ( polygon->q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = polygon->q;
		destination_vertices[count].color = polygon->colour2;
		destination_vertices[count].specular = 0;

		alpha |= polygon->alpha2;

		polygon = polygon->next_vertex;

		count++;
	}

	if ( alpha )
	{

		add_terrain_3d_buffered_triangle_fan ( count, current_terrain_type_class->texture2 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_stripe_word_fan ( int num_points )
{

	int
		count,
		this_point,
		normal_index;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_word_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.colour = transformed_3d_point_colours[this_point].colour;
		this_colour.red = 255;
		this_colour.green = 0;
		this_colour.blue = 0;
		this_colour.alpha = 64;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_stripe_byte_fan ( int num_points )
{

	int
		count,
		this_point,
		normal_index;

	LPTLVERTEX
		destination_vertices;

	float
		xz_texture_scale,
		y_texture_scale;

	xz_texture_scale = current_terrain_type_class->xz_texture_scale;
	y_texture_scale = current_terrain_type_class->y_texture_scale;

	destination_vertices = get_terrain_3d_buffered_vertices ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			y;

		real_colour
			this_colour;

		this_point = terrain_3d_sector_point_byte_references[count].point;

		normal_index = transformed_3d_point_colours[this_point].normal_index;

		y = terrain_3d_map_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * terrain_3d_map_scaled_height_difference );

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;

		destination_vertices[count].sx = transformed_3d_2d_points[this_point].i;
		destination_vertices[count].sy = transformed_3d_2d_points[this_point].j;
		destination_vertices[count].sz = ( transformed_3d_2d_points[this_point].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = transformed_3d_2d_points[this_point].q;

		this_colour.colour = transformed_3d_point_colours[this_point].colour;
		this_colour.red = 255;
		this_colour.green = 0;
		this_colour.blue = 0;
		this_colour.alpha = 64;

		destination_vertices[count].color = this_colour.colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, transformed_3d_point_colours[this_point].fog );
	}

	add_terrain_3d_buffered_triangle_fan ( num_points, current_terrain_type_class->texture );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *terrain_3d_copy_and_recolour_polygon ( vertex *polygon )
{

	int
		vertex_count;

	vertex_count = 0;

	while ( polygon )
	{

		int
			red,
			green,
			blue,
			normal_index;

		terrain_3d_copied_points[vertex_count].x = polygon->x;
		terrain_3d_copied_points[vertex_count].y = polygon->y;
		terrain_3d_copied_points[vertex_count].z = polygon->z;
		terrain_3d_copied_points[vertex_count].q = polygon->q;
		terrain_3d_copied_points[vertex_count].i = polygon->i;
		terrain_3d_copied_points[vertex_count].j = polygon->j;
		terrain_3d_copied_points[vertex_count].u = polygon->u;
		terrain_3d_copied_points[vertex_count].v = polygon->v;
		terrain_3d_copied_points[vertex_count].u2 = polygon->u2;
		terrain_3d_copied_points[vertex_count].v2 = polygon->v2;
		terrain_3d_copied_points[vertex_count].colour2 = polygon->colour2;
		terrain_3d_copied_points[vertex_count].outcode = polygon->outcode;
		terrain_3d_copied_points[vertex_count].fog = polygon->fog;

		normal_index = polygon->normal_index;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		terrain_3d_copied_points[vertex_count].red = red;
		terrain_3d_copied_points[vertex_count].green = green;
		terrain_3d_copied_points[vertex_count].blue = blue;
//		terrain_3d_copied_points[vertex_count].alpha2 = 0;

		terrain_3d_copied_points[vertex_count].next_vertex = &terrain_3d_copied_points[vertex_count+1];

		vertex_count++;

		polygon = polygon->next_vertex;
	}

	terrain_3d_copied_points[vertex_count-1].next_vertex = NULL;

	return ( terrain_3d_copied_points );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_clipped_fan ( int num_points, vertex *points )
{

	int
		count;

	LPTLVERTEX
		destination_vertices;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		destination_vertices[count].tu = points[count].u;
		destination_vertices[count].tv = points[count].v;
		destination_vertices[count].sx = points[count].i;
		destination_vertices[count].sy = points[count].j;
		destination_vertices[count].sz = ( points[count].q * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[count].rhw = points[count].q;
		destination_vertices[count].color = points[count].colour;
		destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, points[count].fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_clipped_fan_new ( void )
{

	int
		number_of_points,
		primitive_count,
		*vertex_indices,
		count;

	LPTLVERTEX
		destination_vertices;

	vertex_indices = clipping_primitives_vertex_indices;

	for ( primitive_count = 0; primitive_count < number_of_clipping_primitives; primitive_count++ )
	{

		number_of_points = clipping_primitives_results[primitive_count];

		destination_vertices = get_d3d_vertices_points_address ( number_of_points );

		terrain_3d_faces_constructed += ( number_of_points - 2 );

		for ( count = 0; count < number_of_points; count++ )
		{

			int
				vertex_index;

			vertex_index = *vertex_indices++;

			destination_vertices[count].tu = clipping_vertices[vertex_index].u;
			destination_vertices[count].tv = clipping_vertices[vertex_index].v;
			destination_vertices[count].sx = clipping_vertices[vertex_index].i;
			destination_vertices[count].sy = clipping_vertices[vertex_index].j;
			destination_vertices[count].sz = ( clipping_vertices[vertex_index].q * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = clipping_vertices[vertex_index].q;
			destination_vertices[count].color = clipping_vertices[vertex_index].colour;
			destination_vertices[count].specular = D3DCOLOR_RGBA ( 0, 0, 0, clipping_vertices[vertex_index].fog );
		}

		draw_fan_primitive ( clipping_primitives_results[primitive_count], destination_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
