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

struct INDICES_INFO
{

	int
		base_index,
		number,
		number_of_vertices_buffered;
};

typedef struct INDICES_INFO indices_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	vertex_buffer,
	base_index;

screen
	*terrain_buffered_polygons_texture;

LPTLVERTEX
	buffered_vertices;

indices_info
	vertex_buffer_indices[MAX_ALPHA_VERTEX_BUFFERS];

static WORD
	*buffered_indices;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_terrain_3d_buffered_polygons ( void )
{

	vertex_buffer = -1;
	buffered_indices = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPTLVERTEX get_terrain_3d_buffered_vertices ( int number_of_vertices )
{

	if ( vertex_buffer == -1 )
	{

		//
		// Open up a vertex buffer
		//

		base_index = 0;

		vertex_buffer = 0;

		vertex_buffer_indices[vertex_buffer].base_index = 0;
		vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered = 0;

		buffered_vertices = get_d3d_alpha_vertex_buffer_vertices ( vertex_buffer );
	}

	if ( vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + number_of_vertices > MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER )
	{

		//
		// Move onto the next vertex buffer
		//

		ASSERT ( vertex_buffer < ( MAX_ALPHA_VERTEX_BUFFERS -1 ) );

		unlock_d3d_alpha_vertex_buffer ( vertex_buffer );

		vertex_buffer_indices[vertex_buffer].number = base_index - vertex_buffer_indices[vertex_buffer].base_index;

		vertex_buffer++;

		vertex_buffer_indices[vertex_buffer].base_index = base_index;

		vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered = 0;

		buffered_vertices = get_d3d_alpha_vertex_buffer_vertices ( vertex_buffer );
	}

	return ( &buffered_vertices[vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered] );
}

static void terrain_lock_buffered_indices ( void )
{
	f3d_index_lock ( d3d.alpha_index_buffer, D3DLOCK_NOSYSLOCK, &buffered_indices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_terrain_3d_buffered_triangle_fan ( int number_of_vertices, screen *texture )
{

	int
		point_count;

	terrain_buffered_polygons_texture = texture;

	if ( !buffered_indices )
	{
		terrain_lock_buffered_indices ();
	}

	ASSERT ( base_index + ( number_of_vertices - 1 ) * 3 < MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER );

	for ( point_count = 1; point_count < ( number_of_vertices - 1 ); point_count++ )
	{

		buffered_indices[base_index++] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered;
		buffered_indices[base_index++] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count;
		buffered_indices[base_index++] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count + 1;
	}

	vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered += number_of_vertices;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_terrain_3d_buffered_triangle_strip ( int number_of_vertices, screen *texture )
{

	int
		direction_toggle,
		point_count;

	terrain_buffered_polygons_texture = texture;

	direction_toggle = FALSE;

	if ( !buffered_indices )
	{
		terrain_lock_buffered_indices ();
	}

	ASSERT ( base_index + ( number_of_vertices - 2 ) * 3 < MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER );

	for ( point_count = 0; point_count < ( number_of_vertices - 2 ); point_count++ )
	{

		if ( direction_toggle )
		{

			buffered_indices[base_index] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count + 2;
			buffered_indices[base_index+1] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count + 1;
			buffered_indices[base_index+2] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count;
			direction_toggle = FALSE;
		}
		else
		{

			buffered_indices[base_index] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count;
			buffered_indices[base_index+1] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count + 1;
			buffered_indices[base_index+2] = vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered + point_count + 2;
			direction_toggle = TRUE;
		}

		base_index += 3;
	}

	vertex_buffer_indices[vertex_buffer].number_of_vertices_buffered += number_of_vertices;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_terrain_3d_buffered_polygons ( void )
{

	if ( vertex_buffer != -1 )
	{

		//
		// Finalise the last vertex buffer used
		//

		unlock_d3d_alpha_vertex_buffer ( vertex_buffer );

		vertex_buffer_indices[vertex_buffer].number = base_index - vertex_buffer_indices[vertex_buffer].base_index;

		if ( base_index )
		{

			int
				count;

			f3d_index_unlock ( d3d.alpha_index_buffer );

			//
			// Flush any buffered primitives
			//

			finalise_primitives ();

			//
			// Set the alpha blend modes
			//

			set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

			//
			// Set the texture handle
			//

			set_d3d_texture ( 0, terrain_buffered_polygons_texture );

			//
			// Draw all the buffered vertex buffers
			//

			for ( count = 0; count <= vertex_buffer; count++ )
			{
				f3d_dip ( D3DPT_TRIANGLELIST, d3d.alpha_vertex_buffer[count], 0, vertex_buffer_indices[count].number_of_vertices_buffered, d3d.alpha_index_buffer, vertex_buffer_indices[count].base_index, vertex_buffer_indices[count].number / 3, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1, sizeof ( TLVERTEX ) );
			}

			//
			// Turn the blend mode off
			//

			set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
		}

		//
		// Reset the things!
		//

		reset_terrain_3d_buffered_polygons ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

