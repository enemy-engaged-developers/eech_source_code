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
#include "3d/3dfunc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

D3DTLVERTEX
	*d3d_point_vertices;

int
	number_of_d3d_point_vertices_used = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_d3d_triangle_vertex_buffer ( void );

void get_d3d_line_vertex_buffer ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPD3DTLVERTEX get_d3d_vertices_address ( vertex *polygon, int *return_number_of_vertices )
{

	int
		number_of_vertices;

	number_of_vertices = 0;

	while ( polygon )
	{

		polygon = polygon->next_vertex;

		number_of_vertices++;
	}

	*return_number_of_vertices = number_of_vertices;

	if ( !d3d.triangle_buffer )
	{

		get_d3d_triangle_vertex_buffer ();
	}

	while ( ( d3d.triangle_buffer->vertices_used + number_of_vertices ) >= MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER )
	{

		force_flush_triangle_buffer ( d3d.triangle_buffer );

		d3d.triangle_buffer = NULL;

		get_d3d_triangle_vertex_buffer ();
	}

	return ( d3d.triangle_buffer->vertices + d3d.triangle_buffer->vertices_used );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPD3DTLVERTEX get_d3d_vertices_points_address ( int number_of_vertices )
{

	int
		first,
		second;

	first = second = 0;

	if ( !d3d.triangle_buffer )
	{

		first = TRUE;

		get_d3d_triangle_vertex_buffer ();
	}

	while ( ( d3d.triangle_buffer->vertices_used + number_of_vertices ) >= MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER )
	{

		second++;

		force_flush_triangle_buffer ( d3d.triangle_buffer );

		d3d.triangle_buffer = NULL;

		get_d3d_triangle_vertex_buffer ();
	}

	ASSERT ( d3d.triangle_buffer->vertices );

	return ( d3d.triangle_buffer->vertices + d3d.triangle_buffer->vertices_used );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPD3DTLVERTEX get_d3d_new_vertices_points_address ( int number_of_vertices, int *offset )
{

	LPD3DTLVERTEX
		vertices;

	if ( !d3d.triangle_buffer )
	{

		get_d3d_triangle_vertex_buffer ();
	}

	while ( ( d3d.triangle_buffer->vertices_used + number_of_vertices ) >= MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER )
	{

		force_flush_triangle_buffer ( d3d.triangle_buffer );

		d3d.triangle_buffer = NULL;

		get_d3d_triangle_vertex_buffer ();
	}

	*offset = d3d.triangle_buffer->vertices_used;

	vertices = d3d.triangle_buffer->vertices + d3d.triangle_buffer->vertices_used;

	d3d.triangle_buffer->vertices_used += number_of_vertices;

	ASSERT ( d3d.triangle_buffer->vertices_used < MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER );

	return ( vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unroll_d3d_vertices ( int number_of_vertices )
{

	ASSERT ( d3d.triangle_buffer );

	d3d.triangle_buffer->vertices_used -= number_of_vertices;

	ASSERT ( d3d.triangle_buffer->vertices_used >= 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPD3DTLVERTEX get_d3d_line_vertices_points_address ( void )
{

	if ( !d3d.line_buffer )
	{

		get_d3d_line_vertex_buffer ();
	}

	while ( ( d3d.line_buffer->vertices_used + 2 ) >= MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER )
	{

		flush_line_primitives ();

		get_d3d_line_vertex_buffer ();
	}

	return ( d3d.line_buffer->vertices + d3d.line_buffer->vertices_used );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPD3DTLVERTEX get_d3d_point_vertices_points_address ( int number_of_points )
{
	LPD3DTLVERTEX
		vertices;

	ASSERT ( number_of_points < MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER );

	f3d_vertex_lock ( d3d.point_vertex_buffer, DDLOCK_NOSYSLOCK | DDLOCK_WRITEONLY | DDLOCK_SURFACEMEMORYPTR, ( LPVOID * ) &vertices );

	return ( vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPD3DTLVERTEX get_d3d_alpha_vertex_buffer_vertices ( int buffer )
{
	LPD3DTLVERTEX
		vertices;

	ASSERT ( buffer < MAX_ALPHA_VERTEX_BUFFERS );

	if ( !f3d_vertex_lock ( d3d.alpha_vertex_buffer[buffer], DDLOCK_NOSYSLOCK | DDLOCK_WRITEONLY | DDLOCK_SURFACEMEMORYPTR, ( LPVOID * ) &vertices ) )
	{
		return ( NULL );
	}

	return ( vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unlock_d3d_alpha_vertex_buffer ( int buffer )
{
	ASSERT ( buffer < MAX_ALPHA_VERTEX_BUFFERS );

	f3d_vertex_unlock ( d3d.alpha_vertex_buffer[buffer] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_d3d_triangle_vertex_buffer ( void )
{
	int
		free,
		maximum_index,
		maximum_vertices,
		found,
		index,
		count;

	vertex_buffer_texture_data
		data;

	index = -1;
	free = -1;
	maximum_index = 0,
	maximum_vertices = 0;
	found = FALSE;

	get_d3d_current_texture_pointer ( &data );

	for ( count = 0; count < MAXIMUM_TRIANGLE_BUFFERS; count++ )
	{

		if ( d3d.triangle_buffers[count].vertices )
		{

			if ( d3d.triangle_buffers[count].texture.texture == data.texture )
/*			if (	( d3d.triangle_buffers[count].texture.texture == data.texture ) &&
					( d3d.triangle_buffers[count].texture.texture_settings == data.texture_settings ) )*/
			{

				found = TRUE;

				index = count;

				break;
			}
			else
			{

				if ( d3d.triangle_buffers[count].vertices_used > maximum_vertices )
				{
	
					maximum_index = count;
	
					maximum_vertices = d3d.triangle_buffers[count].vertices_used;
				}
			}
		}
		else
		{

			if ( free == -1 )
			{

				free = count;
			}
		}
	}

	if ( !found )
	{

		if ( free != -1 )
		{

			index = free;
		}
		else
		{
	
			force_flush_triangle_buffer ( &d3d.triangle_buffers[maximum_index] );
	
			index = maximum_index;
		}
	}

	d3d.triangle_buffer = &d3d.triangle_buffers[index];

	if ( !d3d.triangle_buffer->vertices )
	{
	
		d3d.triangle_buffer->vertices_used = 0;
		d3d.triangle_buffer->indices_index = 0;
		d3d.triangle_buffer->texture.texture = data.texture;
		d3d.triangle_buffer->texture.texture_settings = data.texture_settings;

		f3d_vertex_lock ( d3d.triangle_buffer->buffer, DDLOCK_NOSYSLOCK | DDLOCK_WRITEONLY | DDLOCK_DISCARDCONTENTS | DDLOCK_SURFACEMEMORYPTR,
															( LPVOID * ) &d3d.triangle_buffer->vertices );
	}

	ASSERT ( d3d.triangle_buffer->vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_d3d_line_vertex_buffer ( void )
{

	int
		maximum_index,
		maximum_vertices,
		found,
		index,
		count;

	maximum_index = 0,

	maximum_vertices = 0;

	found = FALSE;

	for ( count = 0; count < MAXIMUM_LINE_BUFFERS; count++ )
	{

		if ( d3d.line_buffers[count].vertices )
		{

			if ( d3d.line_buffers[count].vertices_used > maximum_vertices )
			{

				maximum_index = count;

				maximum_vertices = d3d.line_buffers[count].vertices_used;
			}
		}
		else
		{

			found = TRUE;

			index = count;

			break;
		}
	}

	if ( !found )
	{

		d3d.line_buffer = &d3d.line_buffers[maximum_index];

		flush_line_primitives ();

		index = maximum_index;
	}

	d3d.line_buffer = &d3d.line_buffers[index];

	if ( !d3d.line_buffer->vertices )
	{
		
		d3d.line_buffer->vertices_used = 0;
		d3d.line_buffer->indices_index = 0;
	
		f3d_vertex_lock ( d3d.line_buffer->buffer, DDLOCK_NOSYSLOCK | DDLOCK_WRITEONLY | DDLOCK_DISCARDCONTENTS | DDLOCK_SURFACEMEMORYPTR,
															( LPVOID * ) &d3d.line_buffer->vertices );
	}

	ASSERT ( d3d.line_buffer->vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

