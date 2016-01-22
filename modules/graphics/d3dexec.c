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

LPD3DTLVERTEX get_d3d_execute_buffer_vertices_address ( vertex *polygon, int *return_number_of_vertices )
{

	int
		number_of_vertices,
		vertex_size,
		instruction_size;

	//
	// Count the number of vertices in the polygon.
	//

	number_of_vertices = 0;

	while ( polygon )
	{

		number_of_vertices++;

		polygon = polygon->next_vertex;
	}

	vertex_size = number_of_vertices * sizeof ( D3DTLVERTEX );

	if ( number_of_vertices == 2 )
	{

		//
		// We are drawing a line with these vertices
		//

		instruction_size = ( sizeof ( D3DLINE ) + sizeof ( D3DINSTRUCTION ) );
	}
	else
	{

		int
			number_of_triangles;

		//
		// We are drawing at least 1 triangle
		//

		number_of_triangles = number_of_vertices - 2;

		instruction_size = ( ( number_of_triangles * sizeof ( D3DTRIANGLE ) ) + ( sizeof ( D3DINSTRUCTION ) ) );
	}

	//
	// Check the execute buffer size, for space available.
	//

	d3d_check_execute_size ( vertex_size, instruction_size );

	*return_number_of_vertices = number_of_vertices;

	return ( ( LPD3DTLVERTEX ) ( ( ( unsigned char * ) d3d.execute_buffer_description.lpData ) + d3d.execute_buffer_vertex_offset ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPD3DTLVERTEX get_d3d_execute_buffer_vertices_points_address ( int number_of_vertices )
{

	int
		vertex_size,
		instruction_size;

	vertex_size = number_of_vertices * sizeof ( D3DTLVERTEX );

	if ( number_of_vertices == 2 )
	{

		//
		// We are drawing a line with these vertices
		//

		instruction_size = ( sizeof ( D3DLINE ) + sizeof ( D3DINSTRUCTION ) );
	}
	else
	{

		int
			number_of_triangles;

		//
		// We are drawing at least 1 triangle
		//

		number_of_triangles = number_of_vertices - 2;

		instruction_size = ( ( number_of_triangles * sizeof ( D3DTRIANGLE ) ) + ( sizeof ( D3DINSTRUCTION ) ) );
	}


	//
	// Check the execute buffer size, for space available.
	//

	d3d_check_execute_size ( vertex_size, instruction_size );

	return ( ( LPD3DTLVERTEX ) ( ( ( unsigned char * ) d3d.execute_buffer_description.lpData ) + d3d.execute_buffer_vertex_offset ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_check_execute_size ( int vertex_size, int instruction_size )
{

	ASSERT ( d3d.execute_buffer );

	if (	( vertex_size >= d3d.execute_buffer_vertex_space ) ||
			( instruction_size >= ( d3d.execute_buffer_instruction_space - ( sizeof ( D3DINSTRUCTION  ) * 3 ) ) ) )
	{

		d3d_flush_execute_buffer ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_flush_execute_buffer ( void )
{

	LPVOID
		lpPointer;

	D3DEXECUTEDATA
		exdata;

	HRESULT
		d3drval;

	if ( d3d.execute_buffer_instruction_offset != d3d.execute_buffer_vertex_size )
	{

		int
			instruction_start_offset;


		flush_execute_buffer_states ();

		flush_execute_buffer_triangles ();

		flush_execute_buffer_lines ();

		lpPointer = ( ( ( char * ) d3d.execute_buffer_description.lpData ) + d3d.execute_buffer_instruction_offset );
	
		OP_EXIT ( lpPointer );
	
		d3d.execute_buffer_instruction_offset += sizeof ( D3DINSTRUCTION );

		if ( d3d.execute_buffer_vertex_base )
		{

			LPVOID
				lpPointer;

			//
			// Have to put a PROCESS vertices instruction at start of instruction stream.
			//

			lpPointer = ( ( ( char * ) d3d.execute_buffer_description.lpData ) + d3d.execute_buffer_vertex_size );

			OP_PROCESS_VERTICES ( 1, lpPointer );
				PROCESSVERTICES_DATA ( D3DPROCESSVERTICES_COPY, 0, d3d.execute_buffer_vertex_base, lpPointer );

			instruction_start_offset = d3d.execute_buffer_vertex_size;
		}
		else
		{

			instruction_start_offset = d3d.execute_buffer_vertex_size + sizeof ( D3DINSTRUCTION ) + sizeof ( D3DPROCESSVERTICES );
		}
	
		//
		// Unlock the execute buffer
		//
	
		d3drval = IDirect3DExecuteBuffer_Unlock ( d3d.execute_buffer );
	
		if ( d3drval != D3D_OK )
		{
	
			debug_log ( get_d3d_error_message ( d3drval ) );
	
			return;
		}
	
		//
		// Setup the execute data structure
		//
	
		memset ( &exdata, 0, sizeof ( D3DEXECUTEDATA ) );
	
		exdata.dwSize = sizeof ( D3DEXECUTEDATA );
	
		exdata.dwVertexCount = d3d.execute_buffer_vertex_base;
	
		exdata.dwInstructionOffset = instruction_start_offset;

		exdata.dwInstructionLength = d3d.execute_buffer_instruction_offset - instruction_start_offset;
	
		d3drval = IDirect3DExecuteBuffer_SetExecuteData ( d3d.execute_buffer, &exdata );
	
		if ( d3drval != D3D_OK )
		{
	
			debug_log ( "Unable to set execute data: %s", get_d3d_error_message ( d3drval ) );
	
			return;
		}
	
		d3drval = IDirect3DDevice_Execute ( d3d.device, d3d.execute_buffer, d3d.viewport, D3DEXECUTE_CLIPPED );
	
		if ( d3drval != D3D_OK )
		{
	
			debug_log ( "Unable to execute buffer: %s", get_d3d_error_message ( d3drval ) );
		}

		memset ( &d3d.execute_buffer_description, 0, sizeof ( D3DEXECUTEBUFFERDESC ) );
	
		d3d.execute_buffer_description.dwSize = sizeof ( D3DEXECUTEBUFFERDESC );
	
		d3drval = IDirect3DExecuteBuffer_Lock ( d3d.execute_buffer, &d3d.execute_buffer_description );

		if ( d3drval != D3D_OK )
		{

			debug_log ( get_d3d_error_message ( d3drval ) );
		}
	}

	//
	// Reset the execute buffer offsets & space left
	//

	d3d.execute_buffer_vertex_space = d3d.execute_buffer_vertex_size;
	d3d.execute_buffer_instruction_space = d3d.execute_buffer_instruction_size;

	d3d.execute_buffer_vertex_offset = 0;
	d3d.execute_buffer_instruction_offset = d3d.execute_buffer_vertex_size + sizeof ( D3DINSTRUCTION ) + sizeof ( D3DPROCESSVERTICES );

	d3d.execute_buffer_vertex_base = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void d3d_adjust_execute_size ( int num_vertices, int instruction_size )
{

	d3d.execute_buffer_vertex_base += num_vertices;

	d3d.execute_buffer_vertex_offset += ( num_vertices * sizeof ( D3DVERTEX ) );

	d3d.execute_buffer_vertex_space -= ( num_vertices * sizeof ( D3DVERTEX ) );

	d3d.execute_buffer_instruction_offset += instruction_size;

	d3d.execute_buffer_instruction_space -= instruction_size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
