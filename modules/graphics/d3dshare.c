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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


D3DTLVERTEX
	shared_vertices[2048];

WORD
	shared_triangle_indices[4096];

WORD
	shared_line_indices[2048];

WORD
	shared_vertices_translation_table[2048];

int
	number_of_shared_vertices,
	number_of_shared_triangles,
	number_of_shared_lines;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_shared_primitive ( int number_of_vertices )
{

	number_of_shared_vertices = number_of_vertices;

	number_of_shared_triangles = 0;

	number_of_shared_lines = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_shared_primitive_number_of_vertices ( int number_of_vertices )
{

	number_of_shared_vertices = number_of_vertices;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_shared_polygon_to_shared_primitive ( int number_of_vertices, WORD *indices )
{

	WORD
		first_index,
		number_of_triangles,
		*index_list = nullptr;

	int
		count;

	index_list = &shared_triangle_indices[ ( number_of_shared_triangles * 3 ) ];

	first_index = *indices;

	number_of_triangles = number_of_vertices - 2;

	number_of_shared_triangles += number_of_triangles;

	//
	// Fill out the first triangle
	//

	index_list[0] = first_index;
	index_list[1] = indices[1];
	index_list[2] = indices[2];

	for ( count = 1; count < number_of_triangles; count++ )
	{

		index_list += 3;
		indices += 1;
	
		index_list[0] = first_index;
		index_list[1] = indices[1];
		index_list[2] = indices[2];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_shared_line_to_shared_primitive ( WORD *indices )
{

	WORD
		*index_list = nullptr;

	index_list = &shared_line_indices[ ( number_of_shared_lines * 2 ) ];

	index_list[0] = indices[0];
	index_list[1] = indices[1];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_shared_primitive ( void )
{

	HRESULT
		d3drval;

	//
	// Just draw em all in one go!
	//

	if ( number_of_shared_triangles )
	{

		d3drval = IDirect3DDevice2_DrawIndexedPrimitive ( d3d.device2,
																			D3DPT_TRIANGLELIST,
																			D3DVT_TLVERTEX,
																			( LPVOID ) shared_vertices,
																			( DWORD ) number_of_shared_vertices,
																			( LPWORD ) shared_triangle_indices,
																			( WORD ) ( number_of_shared_triangles * 3 ),
																			( DWORD ) ( 0 ) ) ;
						

		if ( d3drval != DD_OK )
		{
	
			debug_log ( "Unable to draw SHARED triangle primitive: %s", get_ddraw_error_message ( d3drval ) );
		}

		number_of_shared_triangles = 0;
	}

	if ( number_of_shared_lines )
	{

		d3drval = IDirect3DDevice2_DrawIndexedPrimitive ( d3d.device2,
																			D3DPT_LINELIST,
																			D3DVT_TLVERTEX,
																			( LPVOID ) shared_vertices,
																			( DWORD ) number_of_shared_vertices,
																			( LPWORD ) shared_line_indices,
																			( WORD ) ( number_of_shared_lines * 2 ),
																			( DWORD ) ( 0 ) ) ;
						

		if ( d3drval != DD_OK )
		{
	
			debug_log ( "Unable to draw SHARED line primitive: %s", get_ddraw_error_message ( d3drval ) );
		}

		number_of_shared_lines = 0;
	}

	number_of_shared_vertices = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remap_shared_triangle_primitive_indices ( void )
{

	int
		number_of_indices,
		count;

	number_of_indices = number_of_shared_triangles * 3;


	for ( count = 0; count < number_of_indices; count++ )
	{

		shared_triangle_indices[count] = shared_vertices_translation_table[ shared_triangle_indices[count] ];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
