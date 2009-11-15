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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics.h"
#include "3d/3dfunc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CHECK_PRIMITIVE_VERTICES 0

#define DEBUG_REPORT_PRIMITIVES 0

#define DEBUG_ASSESS_VERTEX_CACHES 0

#define DEBUG_CHECK_END_OF_VERTEX_OVERWRITES 0

#define TEXTURE_BATCHING_VERTEX_MAXIMUM 346

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check_primitive_vertices ( D3DTLVERTEX *base, int number_of_vertices );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	d3d_texture_batching_vertex_maximum,
	number_of_d3d_triangle_primitives_drawn = 0,
	number_of_d3d_line_primitives_drawn = 0,
	number_of_d3d_point_primitives_drawn = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_d3d_texture_batching ( int flag )
{

	if ( flag )
	{

		d3d_texture_batching_vertex_maximum = TEXTURE_BATCHING_VERTEX_MAXIMUM;
	}
	else
	{

		finalise_primitives ();

		d3d_texture_batching_vertex_maximum = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_primitives ( void )
{

	int
		count;

	set_d3d_texture_batching ( FALSE );

	for ( count = 0; count < MAXIMUM_TRIANGLE_BUFFERS; count++ )
	{

		d3d.triangle_buffers[count].vertices = NULL;
		d3d.triangle_buffers[count].texture.texture = 0;
		d3d.triangle_buffers[count].texture.texture_settings = 0;
		d3d.triangle_buffers[count].vertices_used = 0;
		d3d.triangle_buffers[count].indices_index = 0;
	}

	for ( count = 0; count < MAXIMUM_LINE_BUFFERS; count++ )
	{

		d3d.line_buffers[count].vertices = NULL;
		d3d.line_buffers[count].texture.texture = 0;
		d3d.line_buffers[count].texture.texture_settings = 0;
		d3d.line_buffers[count].vertices_used = 0;
		d3d.line_buffers[count].indices_index = 0;
	}

	d3d.triangle_buffer = NULL;

	d3d.line_buffer = NULL;

	reset_deferred_state_changes ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flush_triangle_primitives ( void )
{

	if ( ( d3d.triangle_buffer ) && ( d3d.triangle_buffer->vertices_used ) )
	{

		ASSERT ( d3d_in_3d_scene );

	//	if ( ( !d3d.triangle_buffer->vertices ) || ( d3d.triangle_buffer->vertices_used > d3d_texture_batching_vertex_maximum ) )
		{

			force_flush_triangle_buffer ( d3d.triangle_buffer );
		}

		d3d.triangle_buffer = NULL;
	}
	else
	{

		d3d.triangle_buffer = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_flush_triangle_buffer ( vertex_buffer_header *buffer )
{

	if ( buffer->vertices_used )
	{
		//
		// Unlock the vertex buffer
		//
	
		f3d_vertex_unlock ( buffer->buffer );

#if DEBUG_REPORT_PRIMITIVES
		debug_log ( "Drawing triangle primitive with %d vertices", buffer->vertices_used );
#endif
	
#if DEBUG_ASSESS_VERTEX_CACHES
		assess_vertex_cache_usage ( buffer->indices, buffer->indices_index );
#endif
	
		//
		// Make sure we're not telling D3D to clip or light
		//

		set_d3d_int_state_no_flush ( D3DRENDERSTATE_CLIPPING, FALSE );
	
		set_d3d_int_state_no_flush ( D3DRENDERSTATE_LIGHTING, FALSE );

//		if ( d3d_texture_batching_vertex_maximum )
		{

//			ASSERT ( render_d3d_state_table[D3DRENDERSTATE_ALPHABLENDENABLE].value == FALSE );

//			set_d3d_current_texture_pointer ( &buffer->texture );
		}
		
		f3d_draw_vb ( D3DPT_TRIANGLELIST, buffer->buffer, 0, buffer->vertices_used, ( LPWORD ) &buffer->indices[0], ( DWORD ) buffer->indices_index );
/*
		if ( d3d_texture_batching_vertex_maximum )
		{
	
			restore_d3d_current_texture_pointer ();
		}
*/
//		debug_log ( "Vertices: %d, texture %08x", buffer->vertices_used, buffer->texture );

		number_of_d3d_triangle_primitives_drawn++;
	}

	buffer->vertices = NULL;
	buffer->texture.texture = 0;
	buffer->texture.texture_settings = 0;
	buffer->vertices_used = 0;
	buffer->indices_index = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flush_line_primitives ( void )
{

	if ( ( d3d.line_buffer ) && ( d3d.line_buffer->vertices_used ) )
	{

		if ( d3d_in_order_rendering )
		{
	
			flush_triangle_primitives ();
		}

		force_flush_line_buffer ( d3d.line_buffer );

		d3d.line_buffer = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void force_flush_line_buffer ( vertex_buffer_header *buffer )
{

	if ( buffer->vertices_used )
	{
		f3d_vertex_unlock ( buffer->buffer );

#if DEBUG_REPORT_PRIMITIVES
		debug_log ( "Drawing line primitive with %d vertices", buffer->vertices_used );
#endif

		//
		// Make sure we're not telling D3D to clip or light
		//

		set_d3d_int_state_no_flush ( D3DRENDERSTATE_CLIPPING, FALSE );
	
		set_d3d_int_state_no_flush ( D3DRENDERSTATE_LIGHTING, FALSE );

		f3d_draw_vb ( D3DPT_LINELIST, buffer->buffer, 0, buffer->vertices_used, (LPWORD) &buffer->indices[0], (DWORD) buffer->indices_index );

		number_of_d3d_line_primitives_drawn++;
	}

	buffer->vertices = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void finalise_primitives ( void )
{

	int
		count;

	for ( count = 0; count < MAXIMUM_TRIANGLE_BUFFERS; count++ )
	{

		if ( d3d.triangle_buffers[count].vertices )
		{

			force_flush_triangle_buffer ( &d3d.triangle_buffers[count] );
		}
	}

	d3d.triangle_buffer = NULL;

	for ( count = 0; count < MAXIMUM_LINE_BUFFERS; count++ )
	{

		if ( d3d.line_buffers[count].vertices )
		{

			force_flush_line_buffer ( &d3d.line_buffers[count] );
		}
	}

	d3d.line_buffer = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*void render_alpha_vertex_buffer ( int buffer, LPWORD indices, int number_of_indices )
{
	f3d_draw_vb ( D3DPT_TRIANGLELIST,
																			d3d.alpha_vertex_buffer[buffer],
																			0,
																			MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER,
																			indices,
																			number_of_indices );
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WORD *get_d3d_raw_primitive_indices_address ( void )
{

	ASSERT ( d3d.triangle_buffer );

	return ( d3d.triangle_buffer->indices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_fan_primitive ( int number_of_vertices, LPD3DTLVERTEX vertices )
{

	WORD
		*indices;

	int
		index,
		vertex,
		point_count;

#if ( CHECK_PRIMITIVE_VERTICES )
	check_primitive_vertices ( vertices, number_of_vertices );
#endif


	indices = d3d.triangle_buffer->indices;
	index = d3d.triangle_buffer->indices_index;
	vertex = d3d.triangle_buffer->vertices_used;

	for ( point_count = 1; point_count < ( number_of_vertices - 1 ); point_count++ )
	{

		indices[index++] = vertex;
		indices[index++] = vertex + point_count;
		indices[index++] = vertex + point_count + 1;
	}

	d3d.triangle_buffer->vertices_used += number_of_vertices;
	d3d.triangle_buffer->indices_index = index;

#if DEBUG_CHECK_END_OF_VERTEX_OVERWRITES
	ASSERT ( d3d.triangle_buffer->vertices_used < MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER );
	ASSERT ( d3d.triangle_buffer->indices_index < MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER );
#endif

	assert_check_texture_match ();

	number_of_d3d_triangles_drawn += number_of_vertices - 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_strip_primitive ( int number_of_vertices, LPD3DTLVERTEX vertices )
{

	WORD
		*indices;

	int
		index,
		vertex,
		direction_toggle,
		point_count;

	direction_toggle = FALSE;

#if ( CHECK_PRIMITIVE_VERTICES )
	check_primitive_vertices ( vertices, number_of_vertices );
#endif

	indices = d3d.triangle_buffer->indices;
	index = d3d.triangle_buffer->indices_index;
	vertex = d3d.triangle_buffer->vertices_used;

	for ( point_count = 0; point_count < ( number_of_vertices - 2 ); point_count++ )
	{

		if ( direction_toggle )
		{

			indices[index] = vertex + point_count + 2;
			indices[index+1] = vertex + point_count + 1;
			indices[index+2] = vertex + point_count;
			direction_toggle = FALSE;
		}
		else
		{

			indices[index] = vertex + point_count;
			indices[index+1] = vertex + point_count + 1;
			indices[index+2] = vertex + point_count + 2;
			direction_toggle = TRUE;
		}

		index += 3;
	}

	d3d.triangle_buffer->vertices_used += number_of_vertices;
	d3d.triangle_buffer->indices_index = index;

#if DEBUG_CHECK_END_OF_VERTEX_OVERWRITES
	ASSERT ( d3d.triangle_buffer->vertices_used < MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER );
	ASSERT ( d3d.triangle_buffer->indices_index < MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER );
#endif

	number_of_d3d_triangles_drawn += number_of_vertices - 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_line_primitive ( LPD3DTLVERTEX vertices )
{

	WORD
		*indices;

	int
		index,
		vertex;

#if ( CHECK_PRIMITIVE_VERTICES )
	check_primitive_vertices ( vertices, 2 );
#endif

	indices = d3d.line_buffer->indices;
	index = d3d.line_buffer->indices_index;
	vertex = d3d.line_buffer->vertices_used;

	indices[index++] = vertex++;
	indices[index++] = vertex++;

	d3d.line_buffer->vertices_used = vertex;
	d3d.line_buffer->indices_index = index;

	number_of_d3d_lines_drawn++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_point_list_primitive ( int number_of_vertices )
{
	ASSERT ( number_of_vertices < 256 );

	if ( d3d.point_vertex_buffer )
	{
	
		f3d_vertex_unlock ( d3d.point_vertex_buffer );

		f3d_draw ( D3DPT_POINTLIST, d3d.point_vertex_buffer, 0, number_of_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_triangle_fan_primitive_to_buffer ( int number_of_vertices, int offset, unsigned char *indices )
{

	WORD
		*buffer_indices;

	int
		index,
		index_count;

	unsigned short int
		base_index,
		next_index;

	base_index = indices[0] + offset;
	next_index = indices[1] + offset;

	buffer_indices = d3d.triangle_buffer->indices;
	index = d3d.triangle_buffer->indices_index;

	for ( index_count = 0; index_count < ( number_of_vertices - 2 ); index_count++ )
	{

		buffer_indices[index++] = base_index;
		buffer_indices[index++] = next_index;

		next_index = indices[index_count+2] + offset;
		buffer_indices[index++] = next_index;
	}

	d3d.triangle_buffer->indices_index = index;

#if DEBUG_CHECK_END_OF_VERTEX_OVERWRITES
	ASSERT ( d3d.triangle_buffer->vertices_used < MAXIMUM_D3D_VERTICES_IN_VERTEX_BUFFER );
	ASSERT ( d3d.triangle_buffer->indices_index < MAXIMUM_D3D_INDICES_IN_VERTEX_BUFFER );
#endif

	number_of_d3d_triangles_drawn += number_of_vertices - 2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_special_quad_quad_primitive ( int number_of_vertices )
{

	WORD
		*indices;

	int
		vertex,
		index;

	ASSERT ( number_of_vertices == 9 );

	indices = d3d.triangle_buffer->indices;
	index = d3d.triangle_buffer->indices_index;
	vertex = d3d.triangle_buffer->vertices_used;

	indices[index++] = vertex + 0;
	indices[index++] = vertex + 1;
	indices[index++] = vertex + 3;
	indices[index++] = vertex + 1;
	indices[index++] = vertex + 4;
	indices[index++] = vertex + 3;
	indices[index++] = vertex + 1;
	indices[index++] = vertex + 2;
	indices[index++] = vertex + 4;
	indices[index++] = vertex + 2;
	indices[index++] = vertex + 5;
	indices[index++] = vertex + 4;

	indices[index++] = vertex + 3;
	indices[index++] = vertex + 4;
	indices[index++] = vertex + 6;
	indices[index++] = vertex + 4;
	indices[index++] = vertex + 7;
	indices[index++] = vertex + 6;
	indices[index++] = vertex + 4;
	indices[index++] = vertex + 5;
	indices[index++] = vertex + 7;
	indices[index++] = vertex + 5;
	indices[index++] = vertex + 8;
	indices[index++] = vertex + 7;

	d3d.triangle_buffer->indices_index = index;
	d3d.triangle_buffer->vertices_used += number_of_vertices;

	number_of_d3d_triangles_drawn += 8;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void check_primitive_vertices ( D3DTLVERTEX *base, int number_of_vertices )
{

	int
		count;

	for ( count = 0; count < number_of_vertices; count++ )
	{

		if ( ( base[count].sz < 0 ) || ( base[count].sz > 1 ) )
		{

			debug_log ( "Incorrect Z value: %f", base[count].sz );
		}

		if ( ( base[count].sx < 0 ) || ( base[count].sx >= 640.0 ) )
		{

			debug_log ( "Error x: %f", base[count].sx );
		}

		if ( ( base[count].sy < 0 ) || ( base[count].sy >= 480.0 ) )
		{

			debug_log ( "Error y: %f", base[count].sy );
		}
	}
	/*
	int
		degenerate,
		count;

	degenerate = FALSE;

	for ( count = 0; count < ( number_of_vertices - 1 ); count++ )
	{

		int
			valuex1,
			valuex2,
			valuey1,
			valuey2;

		//
		// Check the two vertices screen coordinates
		//

		convert_float_to_int ( base[count].sx, &valuex1 );
		convert_float_to_int ( base[count + 1].sx, &valuex2 );
		convert_float_to_int ( base[count].sy, &valuey1 );
		convert_float_to_int ( base[count + 1].sy, &valuey2 );

		if (	( valuex1 == valuex2 ) &&
				( valuey1 == valuey2 ) )
		{

			degenerate = TRUE;

			break;
		}
	}

	if ( degenerate )
	{

		number_of_d3d_degenerate_triangles++;

		debug_log ( "Degenerate polygon, number of vertices: %d, vertices %d and %d", number_of_vertices, count, count + 1 );

		for ( count = 0; count < number_of_vertices; count++ )
		{

			debug_log ( "%f, %f", base[count].sx, base[count].sy );
		}
	}

	for ( count = 0; count < number_of_vertices; count++ )
	{

		debug_log ( "(%f,%f) (%f,%f) (%f)",
							base[count].sx,
							base[count].sy,
							base[count].tu,
							base[count].tv,
							base[count].sz );
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

