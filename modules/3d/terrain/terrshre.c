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

void render_3d_terrain_short_word_fan ( int num_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		const *vert;

	LPD3DTLVERTEX
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
			v,
			i,
			j,
			q;

		int
			colour;
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];

		u = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		v = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		i = vert->i;
		j = vert->j;
		q = vert->q;
		colour = vert->colour;

		destination_vertices[count].tu = u;
		destination_vertices[count].tv = v;
		destination_vertices[count].sx = i;
		destination_vertices[count].sy = j;
		destination_vertices[count].sz = polygon_zdistance_bias - q;
		destination_vertices[count].rhw = q;
		destination_vertices[count].color = colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_byte_fan ( int num_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;

		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].color = vert->colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_word_strip ( int num_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		const *vert;

	LPD3DTLVERTEX
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
			v,
			i,
			j,
			q;

		int
			colour;


		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];

		u = current_terrain_points_xz[this_point].x * texture_scale;
		v = current_terrain_points_xz[this_point].z * texture_scale;
		i = vert->i;
		j = vert->j;
		q = vert->q;
		colour =  vert->colour;

		destination_vertices[count].tu = u;
		destination_vertices[count].tu = v;
		destination_vertices[count].sx = i;
		destination_vertices[count].sy = j;
		destination_vertices[count].sz = polygon_zdistance_bias - q;
		destination_vertices[count].rhw = q;
		destination_vertices[count].color = colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_byte_strip ( int num_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].color = vert->colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_xy_word_strip ( int num_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].color = vert->colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_xy_byte_strip ( int num_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].color = vert->colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_zy_word_strip ( int num_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].color = vert->colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_zy_byte_strip ( int num_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;
		destination_vertices[count].color = vert->colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_xy_word_colour_strip ( int num_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;

		normal_index = vert->userdata;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = RGB_MAKE ( red, green, blue );
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_xy_byte_colour_strip ( int num_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].x ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;

		normal_index = vert->userdata;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = RGB_MAKE ( red, green, blue );
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_zy_word_colour_strip ( int num_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;

		normal_index = vert->userdata;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = RGB_MAKE ( red, green, blue );
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_short_texture_zy_byte_colour_strip ( int num_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
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
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];
	
		y = terrain_3d_current_sector_minimum_height + ( ( ( float ) current_terrain_points_y[this_point].y ) * TERRAIN_3D_Y_SCALE ) * terrain_3d_current_sector_height_difference;

		destination_vertices[count].tu = (  current_terrain_points_xz[this_point].z ) * xz_texture_scale;
		destination_vertices[count].tv = y * y_texture_scale;
		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;

		normal_index = vert->userdata;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		destination_vertices[count].color = RGB_MAKE ( red, green, blue );
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_strip_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_water_short_word_fan ( int num_points, terrain_3d_point_word_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		const *vert;

	LPD3DTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale2;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		float
			u,
			v,
			i,
			j,
			q;

		real_colour
			colour;
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];

		u = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		v = ( current_terrain_points_xz[this_point].z ) * texture_scale;
		i = vert->i;
		j = vert->j;
		q = vert->q;
		colour.colour = vert->colour;
		colour.alpha = 255;

		destination_vertices[count].tu = u;
		destination_vertices[count].tv = v;
		destination_vertices[count].sx = i;
		destination_vertices[count].sy = j;
		destination_vertices[count].sz = polygon_zdistance_bias - q;
		destination_vertices[count].rhw = q;
		destination_vertices[count].color = colour.colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_3d_terrain_water_short_byte_fan ( int num_points, terrain_3d_point_byte_reference *reference_points )
{

	int
		count,
		this_point;

	short_vertex
		*vert;

	LPD3DTLVERTEX
		destination_vertices;

	float
		texture_scale;

	texture_scale = current_terrain_type_class->xz_texture_scale2;

	destination_vertices = get_d3d_vertices_points_address ( num_points );

	terrain_3d_faces_constructed += ( num_points - 2 );

	for ( count = 0; count < num_points; count++ )
	{

		real_colour
			colour;
	
		this_point = reference_points[count].point;
	
		vert = &( ( short_vertex * ) transformed_3d_points ) [ this_point ];

		destination_vertices[count].tu = ( current_terrain_points_xz[this_point].x ) * texture_scale;
		destination_vertices[count].tv = ( current_terrain_points_xz[this_point].z ) * texture_scale;

		destination_vertices[count].sx = vert->i;
		destination_vertices[count].sy = vert->j;
		destination_vertices[count].sz = polygon_zdistance_bias - vert->q;
		destination_vertices[count].rhw = vert->q;
		colour.colour = vert->colour;
		colour.alpha = 255;
		destination_vertices[count].color = colour.colour;
		destination_vertices[count].specular = RGBA_MAKE ( vert->specular, vert->specular, vert->specular, vert->fog );
	}

	draw_fan_primitive ( num_points, destination_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

short_vertex *terrain_3d_copy_and_recolour_short_polygon ( short_vertex *polygon )
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

		terrain_3d_copied_short_points[vertex_count].q = polygon->q;
		terrain_3d_copied_short_points[vertex_count].i = polygon->i;
		terrain_3d_copied_short_points[vertex_count].j = polygon->j;
		terrain_3d_copied_short_points[vertex_count].u = polygon->u;
		terrain_3d_copied_short_points[vertex_count].v = polygon->v;
		terrain_3d_copied_short_points[vertex_count].outcode = polygon->outcode;
		terrain_3d_copied_short_points[vertex_count].fog = polygon->fog;

		normal_index = polygon->userdata;

		asm_convert_float_to_int ( ( current_terrain_type_class->red * terrain_3d_transformed_point_normals[normal_index].r ), &red );
		asm_convert_float_to_int ( ( current_terrain_type_class->green * terrain_3d_transformed_point_normals[normal_index].g ), &green );
		asm_convert_float_to_int ( ( current_terrain_type_class->blue * terrain_3d_transformed_point_normals[normal_index].b ), &blue );

		terrain_3d_copied_short_points[vertex_count].red = red;
		terrain_3d_copied_short_points[vertex_count].green = green;
		terrain_3d_copied_short_points[vertex_count].blue = blue;

		terrain_3d_copied_short_points[vertex_count].next_vertex = &terrain_3d_copied_short_points[vertex_count+1];

		vertex_count++;

		polygon = polygon->next_vertex;
	}

	terrain_3d_copied_short_points[vertex_count-1].next_vertex = NULL;

	return ( terrain_3d_copied_short_points );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

