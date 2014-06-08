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

//
// This buffers up temporary translucent faces
//
// This is a different system to "tranbuf.c" - that buffers polygons up and sorts them as well. This just buffers the
//		polygons in the order given, and then draws them in that order later on. It is used for lightmaps etc. Whereas the
//		sorted version is used for translucent polygons ( rather than translucent polygons on top of solid ones )
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_BUFFERED_TRANSLUCENT_VERTICES 4096

#define MAX_BUFFERED_TRANSLUCENT_POLYGONS 4096

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BUFFERED_TRANSLUCENT_POLYGON
{

	unsigned char
		texture_mag,
		texture_min,
		texture_u_address,
		texture_v_address,
		source_alpha_blend,
		destination_alpha_blend;

	unsigned short int
		number_of_vertices;

	screen
		*texture;
};

typedef struct BUFFERED_TRANSLUCENT_POLYGON buffered_translucent_polygon;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	number_of_temporary_polygons,
	number_of_temporary_vertices;

static buffered_translucent_polygon
	temporary_polygons[MAX_BUFFERED_TRANSLUCENT_POLYGONS];

static TLVERTEX
	temporary_vertices[MAX_BUFFERED_TRANSLUCENT_VERTICES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_temporary_buffered_translucent_polygons ( void )
{

	number_of_temporary_polygons = 0;

	number_of_temporary_vertices = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_number_of_temporary_translucent_polygons ( void )
{

	return ( number_of_temporary_polygons );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_temporary_translucent_polygons ( void )
{

	int
		vertex_index,
		count;

	//
	// No need to set the default blending mode, as each buffered polygon will set it itself
	//

	vertex_index = 0;

	set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );

	//
	// Flush any buffered vertex buffers
	//

	finalise_primitives ();

	for ( count = 0; count < number_of_temporary_polygons; count++ )
	{

		LPTLVERTEX
			vertices;

		set_d3d_int_state ( D3DRS_SRCBLEND, temporary_polygons[count].source_alpha_blend );
		set_d3d_int_state ( D3DRS_DESTBLEND, temporary_polygons[count].destination_alpha_blend );

		if ( temporary_polygons[count].texture )
		{

			set_d3d_texture ( 0, temporary_polygons[count].texture );
			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

			set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSU, temporary_polygons[count].texture_u_address );
			set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSV, temporary_polygons[count].texture_v_address );
			set_d3d_sampler_state ( 0, D3DSAMP_MAGFILTER, temporary_polygons[count].texture_mag );
			set_d3d_sampler_state ( 0, D3DSAMP_MINFILTER, temporary_polygons[count].texture_mag );
			set_d3d_sampler_state ( 0, D3DSAMP_MIPFILTER, temporary_polygons[count].texture_min );
		}
		else
		{

			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
			set_d3d_texture ( 0, NULL );
		}


		if ( temporary_polygons[count].number_of_vertices > 2 )
		{

			vertices = get_d3d_vertices_points_address ( temporary_polygons[count].number_of_vertices );

			memcpy ( vertices, &temporary_vertices[vertex_index], sizeof ( TLVERTEX ) * temporary_polygons[count].number_of_vertices );

			draw_fan_primitive ( temporary_polygons[count].number_of_vertices, vertices );
		}
		else
		{

			vertices = get_d3d_line_vertices_points_address ();

			memcpy ( vertices, &temporary_vertices[vertex_index], sizeof ( TLVERTEX ) * 2 );

			draw_line_primitive ( vertices );
		}

		vertex_index += temporary_polygons[count].number_of_vertices;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TLVERTEX *get_temporary_translucent_polygon_vertices ( void )
{

	return ( &temporary_vertices[number_of_temporary_vertices] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_temporary_buffered_processed_polygon ( int number_of_vertices, struct SCREEN *texture, int filter, int mipmap, int address_u, int address_v, int additive )
{

	ASSERT ( number_of_vertices );

	if ( additive )
	{

		temporary_polygons[number_of_temporary_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		temporary_polygons[number_of_temporary_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		temporary_polygons[number_of_temporary_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		temporary_polygons[number_of_temporary_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	temporary_polygons[number_of_temporary_polygons].texture = texture;
	temporary_polygons[number_of_temporary_polygons].texture_mag = filter;
	temporary_polygons[number_of_temporary_polygons].texture_min = mipmap;
	temporary_polygons[number_of_temporary_polygons].texture_u_address = address_u;
	temporary_polygons[number_of_temporary_polygons].texture_v_address = address_v;
	temporary_polygons[number_of_temporary_polygons].number_of_vertices = number_of_vertices;

	number_of_temporary_polygons++;

	number_of_temporary_vertices += number_of_vertices;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

