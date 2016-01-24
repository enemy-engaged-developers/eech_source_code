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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_POLYGON_VERTICES 256

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex
	polygon_3d_vertices[MAX_POLYGON_VERTICES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_object_polygon ( int num_points, point_3d_short_reference *points, int base_point, int *polygon_outcode )
{

	int
		count;

	unsigned char
		outcode,
		outcode2,
		*outcode_list;

	outcode_list = transformed_3d_point_outcodes + base_point;

	outcode = outcode_list[ points[0].point ];
	outcode2 = outcode_list[ points[0].point ];

	for ( count = 1; count < num_points; count++ )
	{

		outcode |= outcode_list[points[count].point];
		outcode2 &= outcode_list[points[count].point];
	}

	*polygon_outcode = outcode;

	return ( outcode2 );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_object_surface_polygon ( int num_points, int base_point, int *polygon_outcode )
{

	int
		count;

	unsigned char
		outcode,
		outcode2,
		*outcode_list;

	outcode_list = transformed_3d_point_outcodes + base_point;

	outcode = outcode_list[ current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point];
	outcode2 = outcode_list[ current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point];

	for ( count = 1; count < num_points; count++ )
	{

		outcode |= outcode_list[ current_object_3d_surface_point_list[ current_object_3d_point_list[count].point ].point];
		outcode2 &= outcode_list[ current_object_3d_surface_point_list[ current_object_3d_point_list[count].point ].point];
	}

	*polygon_outcode = outcode;

	return ( outcode2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_surface_polygon ( int num_points, int base_point )
{

	int
		count;

	for ( count = 0; count < num_points; count++ )
	{

		int
			surface_point_index,
			point_index;

		surface_point_index = current_object_3d_point_list[count].point;
		point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;

		polygon_3d_vertices[count].x = transformed_3d_3d_points[point_index].x;
		polygon_3d_vertices[count].y = transformed_3d_3d_points[point_index].y;
		polygon_3d_vertices[count].z = transformed_3d_2d_points[point_index].z;
		polygon_3d_vertices[count].i = transformed_3d_2d_points[point_index].i;
		polygon_3d_vertices[count].j = transformed_3d_2d_points[point_index].j;
		polygon_3d_vertices[count].q = transformed_3d_2d_points[point_index].q;
		polygon_3d_vertices[count].outcode = transformed_3d_point_outcodes[point_index];
		polygon_3d_vertices[count].next_vertex = &polygon_3d_vertices[count+1];
	}

	polygon_3d_vertices[ ( num_points - 1 ) ].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		surface_point_index,
		point_index;

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_gouraud_triangle_fan ( int triangle_index, float specular, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	object_3d_transformed_point_normal
		*normals_base,
		*this_normal;

	int
		ispecular,
		surface_point_index,
		point_index;

	normals_base = &transformed_3d_normals[base_point];

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].colour = this_normal->colour;
	polygon_3d_vertices[0].specular = ispecular;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].colour = this_normal->colour;
	polygon_3d_vertices[1].specular = ispecular;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].colour = this_normal->colour;
	polygon_3d_vertices[2].specular = ispecular;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_unclipped_gouraud_triangle_fan ( int triangle_index, float specular, int base_point )
{

	object_3d_transformed_point_normal
		*normals_base,
		*this_normal;

	int
		ispecular,
		surface_point_index,
		point_index;

	normals_base = &transformed_3d_normals[base_point];

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].colour = this_normal->colour;
	polygon_3d_vertices[0].specular = ispecular;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].colour = this_normal->colour;
	polygon_3d_vertices[1].specular = ispecular;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].specular = ispecular;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_textured_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		surface_point_index,
		point_index;

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[0].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[1].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[2].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_gouraud_textured_triangle_fan ( int triangle_index, float specular, int alpha, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	object_3d_transformed_point_normal
		*normals_base,
		*this_normal;

	int
		ispecular,
		surface_point_index,
		point_index;

	normals_base = &transformed_3d_normals[base_point];

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].colour = this_normal->colour;
	polygon_3d_vertices[0].specular = ispecular;
	polygon_3d_vertices[0].alpha = alpha;
	polygon_3d_vertices[0].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[0].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].colour = this_normal->colour;
	polygon_3d_vertices[1].specular = ispecular;
	polygon_3d_vertices[1].alpha = alpha;
	polygon_3d_vertices[1].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[1].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].colour = this_normal->colour;
	polygon_3d_vertices[2].specular = ispecular;
	polygon_3d_vertices[2].alpha = alpha;
	polygon_3d_vertices[2].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[2].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_dual_textured_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		surface_point_index,
		surface_texture_index,
		point_index;

	surface_point_index = current_object_3d_point_list[0].point;
	surface_texture_index = surface_point_index * 2;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].u = current_object_3d_surface_point_texture_list[surface_texture_index].u;
	polygon_3d_vertices[0].v = current_object_3d_surface_point_texture_list[surface_texture_index].v;
	polygon_3d_vertices[0].u2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
	polygon_3d_vertices[0].v2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	surface_texture_index = surface_point_index * 2;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].u = current_object_3d_surface_point_texture_list[surface_texture_index].u;
	polygon_3d_vertices[1].v = current_object_3d_surface_point_texture_list[surface_texture_index].v;
	polygon_3d_vertices[1].u2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
	polygon_3d_vertices[1].v2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	surface_texture_index = surface_point_index * 2;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].u = current_object_3d_surface_point_texture_list[surface_texture_index].u;
	polygon_3d_vertices[2].v = current_object_3d_surface_point_texture_list[surface_texture_index].v;
	polygon_3d_vertices[2].u2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
	polygon_3d_vertices[2].v2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_gouraud_dual_textured_triangle_fan ( int triangle_index, float specular, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	object_3d_transformed_point_normal
		*normals_base,
		*this_normal;

	int
		ispecular,
		surface_point_index,
		surface_texture_index,
		point_index;

	normals_base = &transformed_3d_normals[base_point];

	surface_point_index = current_object_3d_point_list[0].point;
	surface_texture_index = surface_point_index * 2;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].colour = this_normal->colour;
	polygon_3d_vertices[0].specular = ispecular;
	polygon_3d_vertices[0].u = current_object_3d_surface_point_texture_list[surface_texture_index].u;
	polygon_3d_vertices[0].v = current_object_3d_surface_point_texture_list[surface_texture_index].v;
	polygon_3d_vertices[0].u2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
	polygon_3d_vertices[0].v2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;
	polygon_3d_vertices[0].alpha = current_object_3d_dissolve_value;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	surface_texture_index = surface_point_index * 2;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].colour = this_normal->colour;
	polygon_3d_vertices[1].specular = ispecular;
	polygon_3d_vertices[1].u = current_object_3d_surface_point_texture_list[surface_texture_index].u;
	polygon_3d_vertices[1].v = current_object_3d_surface_point_texture_list[surface_texture_index].v;
	polygon_3d_vertices[1].u2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
	polygon_3d_vertices[1].v2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;
	polygon_3d_vertices[1].alpha = current_object_3d_dissolve_value;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	surface_texture_index = surface_point_index * 2;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	this_normal = &normals_base[current_object_3d_surface_point_normal_list[surface_point_index].point];
	asm_convert_float_to_int ( ( specular * this_normal->specular ), &ispecular );
	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].colour = this_normal->colour;
	polygon_3d_vertices[2].specular = ispecular;
	polygon_3d_vertices[2].u = current_object_3d_surface_point_texture_list[surface_texture_index].u;
	polygon_3d_vertices[2].v = current_object_3d_surface_point_texture_list[surface_texture_index].v;
	polygon_3d_vertices[2].u2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
	polygon_3d_vertices[2].v2 = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;
	polygon_3d_vertices[2].alpha = current_object_3d_dissolve_value;
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_surface_line ( int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		surface_point_index,
		point_index;

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].next_vertex = NULL;

	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *construct_3d_surface_unclipped_line ( int base_point )
{

	int
		surface_point_index,
		point_index;

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	surface_point_index = current_object_3d_point_list[1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;

	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_textured_line ( int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		surface_point_index,
		point_index;

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[0].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[1].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[1].next_vertex = NULL;

	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;
	
	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_unclipped_textured_line ( int base_point )
{

	int
		surface_point_index,
		point_index;

	surface_point_index = current_object_3d_point_list[0].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[0].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];

	surface_point_index = current_object_3d_point_list[1].point;
	point_index = current_object_3d_surface_point_list[surface_point_index].point + base_point;
	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].u = current_object_3d_surface_point_texture_list[surface_point_index].u;
	polygon_3d_vertices[1].v = current_object_3d_surface_point_texture_list[surface_point_index].v;
	polygon_3d_vertices[1].next_vertex = NULL;

	return ( polygon_3d_vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_reflective_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode, vec3d *normal )
{

	unsigned char
		outcode,
		outcode2;

	vec3d
		camera_position;

	int
		object_index,
		surface_point_index,
		point_index,
		object_point_index;

	float
		u,
		v;

	camera_position = current_object_3d_object_base->camera_position;

	object_index = current_object_3d_object_base->object_number;

	surface_point_index = current_object_3d_point_list[0].point;
	object_point_index = current_object_3d_surface_point_list[surface_point_index].point;
	point_index = object_point_index + base_point;

	generate_environment_coordinates ( object_index, &objects_3d_data[object_index].points[object_point_index],
													normal, &camera_position, current_object_3d_object_base->object_vp->attitude, &u, &v );

	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].u = u;
	polygon_3d_vertices[0].v = v;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	object_point_index = current_object_3d_surface_point_list[surface_point_index].point;
	point_index = object_point_index + base_point;

	generate_environment_coordinates ( object_index, &objects_3d_data[object_index].points[object_point_index],
													normal, &camera_position, current_object_3d_object_base->object_vp->attitude, &u, &v );

	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].u = u;
	polygon_3d_vertices[1].v = v;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	object_point_index = current_object_3d_surface_point_list[surface_point_index].point;
	point_index = object_point_index + base_point;

	generate_environment_coordinates ( object_index, &objects_3d_data[object_index].points[object_point_index],
													normal, &camera_position, current_object_3d_object_base->object_vp->attitude, &u, &v );

	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].u = u;
	polygon_3d_vertices[2].v = v;
	polygon_3d_vertices[2].specular = 0;
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;

	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_surface_gouraud_reflective_triangle_fan ( int triangle_index, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	vec3d
		camera_position,
		normal;

	object_3d_heading_pitch_normal
		*point_normal;

	int
		object_index,
		surface_point_index,
		surface_point_normal_index,
		point_index,
		object_point_index;

	real_colour
		this_colour;

	float
		u,
		v;

	camera_position = current_object_3d_object_base->camera_position;

	object_index = current_object_3d_object_base->object_number;

	surface_point_index = current_object_3d_point_list[0].point;
	surface_point_normal_index = current_object_3d_surface_point_normal_list[surface_point_index].point;
	object_point_index = current_object_3d_surface_point_list[surface_point_index].point;
	point_index = object_point_index + base_point;
	point_normal = &objects_3d_data[object_index].point_normals[surface_point_normal_index];
	generate_object_3d_point_normal ( point_normal, &normal );
//	normal.x = point_normal->x / 32767.0;
//	normal.y = point_normal->y / 32767.0;
//	normal.z = point_normal->z / 32767.0;

	this_colour.colour = current_object_3d_transformed_normals[surface_point_normal_index].colour;
	this_colour.alpha = current_object_3d_surface->reflectivity;

	generate_environment_coordinates ( object_index, &objects_3d_data[object_index].points[object_point_index],
													&normal, &camera_position, current_object_3d_object_base->object_vp->attitude, &u, &v );

	polygon_3d_vertices[0].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[0].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[0].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[0].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[0].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[0].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[0].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[0].colour = this_colour.colour;
	polygon_3d_vertices[0].u = u;
	polygon_3d_vertices[0].v = v;
	polygon_3d_vertices[0].specular = 0;
	polygon_3d_vertices[0].next_vertex = &polygon_3d_vertices[1];
	outcode = transformed_3d_point_outcodes[point_index];
	outcode2 = transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+1].point;
	surface_point_normal_index = current_object_3d_surface_point_normal_list[surface_point_index].point;
	object_point_index = current_object_3d_surface_point_list[surface_point_index].point;
	point_index = object_point_index + base_point;
	point_normal = &objects_3d_data[object_index].point_normals[surface_point_normal_index];
	generate_object_3d_point_normal ( point_normal, &normal );
//	normal.x = point_normal->x / 32767.0;
//	normal.y = point_normal->y / 32767.0;
//	normal.z = point_normal->z / 32767.0;

	this_colour.colour = current_object_3d_transformed_normals[surface_point_normal_index].colour;
	this_colour.alpha = current_object_3d_surface->reflectivity;

	generate_environment_coordinates ( object_index, &objects_3d_data[object_index].points[object_point_index],
													&normal, &camera_position, current_object_3d_object_base->object_vp->attitude, &u, &v );

	polygon_3d_vertices[1].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[1].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[1].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[1].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[1].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[1].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[1].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[1].colour = this_colour.colour;
	polygon_3d_vertices[1].u = u;
	polygon_3d_vertices[1].v = v;
	polygon_3d_vertices[1].specular = 0;
	polygon_3d_vertices[1].next_vertex = &polygon_3d_vertices[2];
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	surface_point_index = current_object_3d_point_list[triangle_index+2].point;
	surface_point_normal_index = current_object_3d_surface_point_normal_list[surface_point_index].point;
	object_point_index = current_object_3d_surface_point_list[surface_point_index].point;
	point_index = object_point_index + base_point;
	point_normal = &objects_3d_data[object_index].point_normals[surface_point_normal_index];
	generate_object_3d_point_normal ( point_normal, &normal );
//	normal.x = point_normal->x / 32767.0;
//	normal.y = point_normal->y / 32767.0;
//	normal.z = point_normal->z / 32767.0;

	this_colour.colour = current_object_3d_transformed_normals[surface_point_normal_index].colour;
	this_colour.alpha = current_object_3d_surface->reflectivity;

	generate_environment_coordinates ( object_index, &objects_3d_data[object_index].points[object_point_index],
													&normal, &camera_position, current_object_3d_object_base->object_vp->attitude, &u, &v );

	polygon_3d_vertices[2].x = transformed_3d_3d_points[point_index].x;
	polygon_3d_vertices[2].y = transformed_3d_3d_points[point_index].y;
	polygon_3d_vertices[2].z = transformed_3d_2d_points[point_index].z;
	polygon_3d_vertices[2].i = transformed_3d_2d_points[point_index].i;
	polygon_3d_vertices[2].j = transformed_3d_2d_points[point_index].j;
	polygon_3d_vertices[2].q = transformed_3d_2d_points[point_index].q;
	polygon_3d_vertices[2].outcode = transformed_3d_point_outcodes[point_index];
	polygon_3d_vertices[2].colour = this_colour.colour;
	polygon_3d_vertices[2].u = u;
	polygon_3d_vertices[2].v = v;
	polygon_3d_vertices[2].specular = 0;
	polygon_3d_vertices[2].next_vertex = NULL;
	outcode |= transformed_3d_point_outcodes[point_index];
	outcode2 &= transformed_3d_point_outcodes[point_index];

	*polygon_outcode = outcode;

	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( polygon_3d_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
