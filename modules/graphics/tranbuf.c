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
// This buffers up whole objects of transparancies
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_TRANSLUCENT_POLYGON_BUFFERS 1024

#define MAX_BUFFERED_TRANSLUCENT_VERTICES 8192

#define MAX_BUFFERED_TRANSLUCENT_POLYGONS 2048

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	number_of_buffered_translucent_polygons,
	number_of_buffered_translucent_vertices,
	number_of_translucent_polygon_buffers,
	current_number_of_translucent_polygons,
	current_number_of_translucent_vertices;

polygon_buffer
	*active_translucent_sorted_polygon_buffer,
	translucent_polygon_buffers[MAX_TRANSLUCENT_POLYGON_BUFFERS];

buffered_polygon
	*buffered_sorted_translucent_polygons_head,
	*buffered_sorted_translucent_polygons_tail,
	*buffered_sorted_translucent_polygons_insert,
	buffered_translucent_polygons_array[MAX_BUFFERED_TRANSLUCENT_POLYGONS];

TLVERTEX
	buffered_translucent_vertices_array[MAX_BUFFERED_TRANSLUCENT_VERTICES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void add_buffered_sorted_translucent_polygon ( int index );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_translucent_buffering_system ( void )
{

	number_of_buffered_translucent_polygons = 0;

	number_of_buffered_translucent_vertices = 0;

	number_of_translucent_polygon_buffers = 0;

	//
	// Reset the sorted polygon buffer
	//

	active_translucent_sorted_polygon_buffer = NULL;

	buffered_sorted_translucent_polygons_head = NULL;

	buffered_sorted_translucent_polygons_tail = NULL;

	buffered_sorted_translucent_polygons_insert = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

polygon_buffer * get_translucent_sorted_polygon_buffer ( void )
{

	ASSERT ( number_of_translucent_polygon_buffers < MAX_TRANSLUCENT_POLYGON_BUFFERS );

	active_translucent_sorted_polygon_buffer = &translucent_polygon_buffers[number_of_translucent_polygon_buffers];

	translucent_polygon_buffers[number_of_translucent_polygon_buffers].number_of_polygons = 0;

	translucent_polygon_buffers[number_of_translucent_polygon_buffers].polygons = NULL;

	number_of_translucent_polygon_buffers++;

	//
	// Reset the internal polygon sorting variables
	//

	buffered_sorted_translucent_polygons_head = NULL;

	buffered_sorted_translucent_polygons_tail = NULL;

	buffered_sorted_translucent_polygons_insert = NULL;

	current_number_of_translucent_polygons = 0;

	current_number_of_translucent_vertices = 0;

	ASSERT ( number_of_translucent_polygon_buffers < MAX_TRANSLUCENT_POLYGON_BUFFERS );

	return ( active_translucent_sorted_polygon_buffer );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int finalise_translucent_sorted_polygon_buffer ( polygon_buffer *buffer )
{

	ASSERT ( buffer == active_translucent_sorted_polygon_buffer );

	if ( buffered_sorted_translucent_polygons_head )
	{

		buffer->polygons = buffered_sorted_translucent_polygons_head;

		buffered_sorted_translucent_polygons_head = NULL;

		buffered_sorted_translucent_polygons_tail = NULL;

		buffered_sorted_translucent_polygons_insert = NULL;

		return ( TRUE );
	}
	else
	{

		//
		// There are no polygons buffered - so unwind back
		//

		number_of_translucent_polygon_buffers--;

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_translucent_polygon_buffer ( polygon_buffer *buffer )
{

	number_of_buffered_translucent_polygons -= current_number_of_translucent_polygons;

	number_of_buffered_translucent_vertices -= current_number_of_translucent_vertices;

	number_of_translucent_polygon_buffers--;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_polygon_buffer ( polygon_buffer *buffer )
{

	buffered_polygon
		*polygon;

	//
	// First, flush all the buffered primitives!
	//

	polygon = buffer->polygons;

	set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );

	while ( polygon )
	{

		LPTLVERTEX
			vertices;

		set_d3d_int_state ( D3DRS_SPECULARENABLE, polygon->specular );
		set_d3d_int_state ( D3DRS_SRCBLEND, polygon->source_alpha_blend );
		set_d3d_int_state ( D3DRS_DESTBLEND, polygon->destination_alpha_blend );

		if ( polygon->texture )
		{

			set_d3d_texture ( 0, polygon->texture );
			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

			set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSU, polygon->texture_u_address );
			set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSV, polygon->texture_v_address );
			set_d3d_sampler_state ( 0, D3DSAMP_MAGFILTER, polygon->texture_mag );
			set_d3d_sampler_state ( 0, D3DSAMP_MINFILTER, polygon->texture_mag );
			set_d3d_sampler_state ( 0, D3DSAMP_MIPFILTER, polygon->texture_min );
		}
		else
		{

			set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
			set_d3d_texture ( 0, NULL );
		}

		if ( polygon->number_of_vertices > 2 )
		{

			vertices = get_d3d_vertices_points_address ( polygon->number_of_vertices );

			memcpy ( vertices, &buffered_translucent_vertices_array[polygon->point_offset], sizeof ( TLVERTEX ) * polygon->number_of_vertices );

			draw_fan_primitive ( polygon->number_of_vertices, vertices );
		}
		else
		{

			vertices = get_d3d_line_vertices_points_address ();

			memcpy ( vertices, &buffered_translucent_vertices_array[polygon->point_offset], sizeof ( TLVERTEX ) * 2 );

			draw_line_primitive ( vertices );
		}

		polygon = polygon->succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void add_buffered_sorted_translucent_polygon ( int index )
{

	unsigned int
		distance;

	ASSERT ( buffered_translucent_polygons_array[index].number_of_vertices );
	ASSERT ( buffered_translucent_polygons_array[index].number_of_vertices < 256 );


	distance = buffered_translucent_polygons_array[index].distance;

	if ( buffered_sorted_translucent_polygons_insert )
	{

		buffered_polygon
			*previous_polygon,
			*this_polygon;

		this_polygon = buffered_sorted_translucent_polygons_insert;

		previous_polygon = buffered_sorted_translucent_polygons_insert;

		if ( distance < this_polygon->distance )
		{

			//
			// Start searching BACKWARDS ( more distant polygons drawn first )
			//

			while ( this_polygon )
			{

				if ( distance >= this_polygon->distance )
				{

					break;
				}
				else
				{

					previous_polygon = this_polygon;

					this_polygon = this_polygon->pred;
				}
			}

			if ( this_polygon )
			{

				//
				// Add new polygon AFTER this_polygon
				//

				if ( !this_polygon->succ )
				{

					//
					// We are at the tail end of the list
					//

					buffered_translucent_polygons_array[index].pred = this_polygon;

					buffered_translucent_polygons_array[index].succ = NULL;

					this_polygon->succ = &buffered_translucent_polygons_array[index];

					buffered_sorted_translucent_polygons_tail = &buffered_translucent_polygons_array[index];

					buffered_sorted_translucent_polygons_insert = &buffered_translucent_polygons_array[index];
				}
				else
				{

					//
					// Insert into list normally.
					//

					buffered_translucent_polygons_array[index].succ = this_polygon->succ;

					buffered_translucent_polygons_array[index].pred = this_polygon;

					this_polygon->succ->pred = &buffered_translucent_polygons_array[index];

					this_polygon->succ = &buffered_translucent_polygons_array[index];

					buffered_sorted_translucent_polygons_insert = &buffered_translucent_polygons_array[index];
				}
			}
			else
			{

				//
				// Add this polygon at the HEAD of the list
				//

				buffered_translucent_polygons_array[index].succ = buffered_sorted_translucent_polygons_head;

				buffered_translucent_polygons_array[index].pred = NULL;

				buffered_sorted_translucent_polygons_head->pred = &buffered_translucent_polygons_array[index];

				buffered_sorted_translucent_polygons_head = &buffered_translucent_polygons_array[index];

				buffered_sorted_translucent_polygons_insert = &buffered_translucent_polygons_array[index];
			}
		}
		else
		{

			//
			// Start searching FORWARDS ( less distant polygons drawn last )
			//

			while ( this_polygon )
			{

				if ( distance <= this_polygon->distance )
				{

					break;
				}
				else
				{

					previous_polygon = this_polygon;

					this_polygon = this_polygon->succ;
				}
			}

			if ( this_polygon )
			{

				//
				// Add new polygon BEFORE this_polygon
				//

				if ( !this_polygon->pred )
				{

					//
					// We are at the head end of the list
					//

					buffered_translucent_polygons_array[index].pred = NULL;

					buffered_translucent_polygons_array[index].succ = this_polygon;

					this_polygon->pred = &buffered_translucent_polygons_array[index];

					buffered_sorted_translucent_polygons_head = &buffered_translucent_polygons_array[index];

					buffered_sorted_translucent_polygons_insert = &buffered_translucent_polygons_array[index];
				}
				else
				{

					//
					// Insert into list normally.
					//

					buffered_translucent_polygons_array[index].pred = this_polygon->pred;

					buffered_translucent_polygons_array[index].succ = this_polygon;

					this_polygon->pred->succ = &buffered_translucent_polygons_array[index];

					this_polygon->pred = &buffered_translucent_polygons_array[index];

					buffered_sorted_translucent_polygons_insert = &buffered_translucent_polygons_array[index];
				}
			}
			else
			{

				//
				// Add this polygon at the TAIL of the list
				//

				buffered_translucent_polygons_array[index].pred = buffered_sorted_translucent_polygons_tail;

				buffered_translucent_polygons_array[index].succ = NULL;

				buffered_sorted_translucent_polygons_tail->succ = &buffered_translucent_polygons_array[index];

				buffered_sorted_translucent_polygons_tail = &buffered_translucent_polygons_array[index];

				buffered_sorted_translucent_polygons_insert = &buffered_translucent_polygons_array[index];
			}
		}
	}
	else
	{

		buffered_translucent_polygons_array[index].succ = NULL;

		buffered_translucent_polygons_array[index].pred = NULL;

		buffered_sorted_translucent_polygons_head = &buffered_translucent_polygons_array[index];

		buffered_sorted_translucent_polygons_tail = &buffered_translucent_polygons_array[index];

		buffered_sorted_translucent_polygons_insert = &buffered_translucent_polygons_array[index];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TLVERTEX *get_translucent_polygon_vertices ( void )
{

	ASSERT ( number_of_buffered_translucent_vertices < MAX_BUFFERED_TRANSLUCENT_VERTICES );

	return ( &buffered_translucent_vertices_array[number_of_buffered_translucent_vertices] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buffered_polygon * add_buffered_processed_polygon ( int points, float distance, int shading, screen *texture, int filter, int mipmap, int u, int v, int specular, int additive )
{

	ASSERT ( points );
	ASSERT ( number_of_buffered_translucent_polygons < MAX_BUFFERED_TRANSLUCENT_POLYGONS );

	current_number_of_translucent_polygons++;
	current_number_of_translucent_vertices += points;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].shade_mode = shading;

	if ( additive )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture = texture;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_mag = filter;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_min = mipmap;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_u_address = u;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_v_address = v;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].point_offset = number_of_buffered_translucent_vertices;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].distance = *( ( int * ) &distance );
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = specular;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].number_of_vertices = points;

	add_buffered_sorted_translucent_polygon ( number_of_buffered_translucent_polygons );

	number_of_buffered_translucent_vertices += points;

	return ( &buffered_translucent_polygons_array[number_of_buffered_translucent_polygons++] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buffered_polygon * buffer_wbuffered_plain_polygon ( vertex *polygon, real_colour colour, real_colour specular, int additive )
{

	int
		number_of_vertices;

	vertex
		*vert;

	TLVERTEX
		*vptr;

	float
		distance;

	ASSERT ( number_of_buffered_translucent_polygons < MAX_BUFFERED_TRANSLUCENT_POLYGONS );

	current_number_of_translucent_polygons++;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture = NULL;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].shade_mode = D3DSHADE_FLAT;

	if ( additive )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	if ( specular.red != 0 )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = TRUE;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = FALSE;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].point_offset = number_of_buffered_translucent_vertices;

	number_of_vertices = 0;

	vert = polygon;

	vptr = &buffered_translucent_vertices_array[number_of_buffered_translucent_vertices];

	//
	// Set up the colour of the polygon
	//

	distance = 0;

	while ( vert )
	{

		distance += vert->q;

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
		vptr->color = colour.colour;
		vptr->specular = specular.colour;

		vptr++;

		vert = vert->next_vertex;

		number_of_vertices++;
	}

	distance *= one_over_table[number_of_vertices];

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].distance = *( ( int * ) &distance );

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].number_of_vertices = number_of_vertices;

	add_buffered_sorted_translucent_polygon ( number_of_buffered_translucent_polygons );

	number_of_buffered_translucent_vertices += number_of_vertices;

	current_number_of_translucent_vertices += number_of_vertices;

	return ( &buffered_translucent_polygons_array[number_of_buffered_translucent_polygons++] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buffered_polygon * buffer_wbuffered_gouraud_shaded_polygon ( vertex *polygon, float red, float green, float blue, int alpha, float specularity, int additive )
{

	int
		number_of_vertices,
		r,
		g,
		b;

	vertex
		*vert;

	TLVERTEX
		*vptr;

	float
		fr,
		fg,
		fb,
		distance;

	real_colour
		colour,
		specular;

	ASSERT ( number_of_buffered_translucent_polygons < MAX_BUFFERED_TRANSLUCENT_POLYGONS );

	current_number_of_translucent_polygons++;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture = NULL;

	if ( additive )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].shade_mode = D3DSHADE_GOURAUD;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].point_offset = number_of_buffered_translucent_vertices;

	if ( specularity > 0 )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = TRUE;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = FALSE;
	}

	distance = 0;

	number_of_vertices = 0;

	vert = polygon;

	vptr = &buffered_translucent_vertices_array[number_of_buffered_translucent_vertices];

	//
	// Set up the colour of the polygon
	//

	colour.alpha = alpha;
	specular.colour = d3d_fog_intensity;

	while ( vert )
	{

		distance += vert->q;

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );

		fr = ( vert->red * red ) + FLOAT_FLOAT_FACTOR;
		fg = ( vert->green * green ) + FLOAT_FLOAT_FACTOR;
		fb = ( vert->blue * blue ) + FLOAT_FLOAT_FACTOR;

		r = ( *( int * ) &fr ) - INTEGER_FLOAT_FACTOR;
		g = ( *( int * ) &fg ) - INTEGER_FLOAT_FACTOR;
		b = ( *( int * ) &fb ) - INTEGER_FLOAT_FACTOR;

		colour.red = r;
		colour.green = g;
		colour.blue = b;

		specular.red = vert->specular;
		specular.green = vert->specular;
		specular.blue = vert->specular;

		vptr->color = colour.colour;
		vptr->specular = specular.colour;

		vptr++;

		vert = vert->next_vertex;

		number_of_vertices++;
	}

	distance *= one_over_table[number_of_vertices];

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].distance = *( ( int * ) &distance );

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].number_of_vertices = number_of_vertices;

	add_buffered_sorted_translucent_polygon ( number_of_buffered_translucent_polygons );

	number_of_buffered_translucent_vertices += number_of_vertices;

	current_number_of_translucent_vertices += number_of_vertices;

	return ( &buffered_translucent_polygons_array[number_of_buffered_translucent_polygons++] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buffered_polygon * buffer_wbuffered_flat_shaded_textured_polygon ( vertex *polygon, screen *texture, int filter, int mipmap, int u, int v, real_colour colour, real_colour specular, int additive )
{

	int
		number_of_vertices;

	vertex
		*vert;

	TLVERTEX
		*vptr;

	float
		distance;

	ASSERT ( number_of_buffered_translucent_polygons < MAX_BUFFERED_TRANSLUCENT_POLYGONS );

	current_number_of_translucent_polygons++;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].shade_mode = D3DSHADE_FLAT;

	if ( additive )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture = texture;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_mag = filter;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_min = mipmap;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_u_address = u;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_v_address = v;

	if ( specular.red != 0 )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = TRUE;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = FALSE;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].point_offset = number_of_buffered_translucent_vertices;

	distance = 0;

	number_of_vertices = 0;

	vert = polygon;

	vptr = &buffered_translucent_vertices_array[number_of_buffered_translucent_vertices];

	while ( vert )
	{

		distance += vert->q;

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
		*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );

		vptr->color = colour.colour;
		vptr->specular = specular.colour;

		vptr++;

		vert = vert->next_vertex;

		number_of_vertices++;
	}

	distance *= one_over_table[number_of_vertices];

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].distance = *( ( int * ) &distance );

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].number_of_vertices = number_of_vertices;

	add_buffered_sorted_translucent_polygon ( number_of_buffered_translucent_polygons );

	number_of_buffered_translucent_vertices += number_of_vertices;

	current_number_of_translucent_vertices += number_of_vertices;

	return ( &buffered_translucent_polygons_array[number_of_buffered_translucent_polygons++] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buffered_polygon * buffer_wbuffered_gouraud_shaded_textured_polygon ( vertex *polygon, screen *texture, int filter, int mipmap, int u, int v, int specular, int additive, int alpha )
{

	int
		number_of_vertices;

	vertex
		*vert;

	TLVERTEX
		*vptr;

	float
		distance;

	ASSERT ( number_of_buffered_translucent_polygons < MAX_BUFFERED_TRANSLUCENT_POLYGONS );

	current_number_of_translucent_polygons++;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].shade_mode = D3DSHADE_GOURAUD;

	if ( additive )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture = texture;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_mag = filter;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_min = mipmap;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_u_address = u;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_v_address = v;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = specular;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].point_offset = number_of_buffered_translucent_vertices;

	distance = 0;

	number_of_vertices = 0;

	vert = polygon;

	vptr = &buffered_translucent_vertices_array[number_of_buffered_translucent_vertices];

	//
	// Set up the colour of the polygon
	//

	while ( vert )
	{

		real_colour
			colour,
			specular_colour;

		distance += vert->q;

		*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
		*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
		*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
		*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
		*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );

		colour.red = vert->red;
		colour.green = vert->green;
		colour.blue = vert->blue;
		colour.alpha = alpha;

		specular_colour.red = vert->specular;
		specular_colour.green = vert->specular;
		specular_colour.blue = vert->specular;
		specular_colour.alpha = 255;

		vptr->color = colour.colour;
		vptr->specular = specular_colour.colour;

		vptr++;

		vert = vert->next_vertex;

		number_of_vertices++;
	}

	distance *= one_over_table[number_of_vertices];

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].distance = *( ( int * ) &distance );

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].number_of_vertices = number_of_vertices;

	add_buffered_sorted_translucent_polygon ( number_of_buffered_translucent_polygons );

	number_of_buffered_translucent_vertices += number_of_vertices;

	current_number_of_translucent_vertices += number_of_vertices;

	return ( &buffered_translucent_polygons_array[number_of_buffered_translucent_polygons++] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buffered_polygon * buffer_wbuffered_flat_shaded_textured_line ( vertex *polygon, screen *texture, int filter, int mipmap, int u, int v, real_colour colour, int additive )
{

	vertex
		*vert;

	TLVERTEX
		*vptr;

	float
		distance;

	ASSERT ( number_of_buffered_translucent_polygons < MAX_BUFFERED_TRANSLUCENT_POLYGONS );

	current_number_of_translucent_polygons++;

	current_number_of_translucent_vertices += 2;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].shade_mode = D3DSHADE_FLAT;

	if ( additive )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture = texture;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_mag = filter;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_min = mipmap;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_u_address = u;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_v_address = v;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = FALSE;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].point_offset = number_of_buffered_translucent_vertices;

	vert = polygon;

	vptr = &buffered_translucent_vertices_array[number_of_buffered_translucent_vertices];

	distance = vert->q;
	*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
	vptr->color = colour.colour;
	vptr->specular = d3d_fog_intensity;

	vptr++;
	vert = vert->next_vertex;

	distance += vert->q;
	*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
	vptr->color = colour.colour;
	vptr->specular = d3d_fog_intensity;

	distance /= 2.0;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].distance = *( ( int * ) &distance );

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].number_of_vertices = 2;

	add_buffered_sorted_translucent_polygon ( number_of_buffered_translucent_polygons );

	number_of_buffered_translucent_vertices += 2;

	return ( &buffered_translucent_polygons_array[number_of_buffered_translucent_polygons++] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

buffered_polygon * buffer_wbuffered_gouraud_shaded_textured_line ( vertex *polygon, screen *texture, int filter, int mipmap, int u, int v, int additive )
{

	vertex
		*vert;

	TLVERTEX
		*vptr;

	float
		distance;

	ASSERT ( number_of_buffered_translucent_polygons < MAX_BUFFERED_TRANSLUCENT_POLYGONS );

	current_number_of_translucent_polygons++;

	current_number_of_translucent_vertices += 2;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].shade_mode = D3DSHADE_GOURAUD;

	if ( additive )
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = ADDITIVE_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = ADDITIVE_DESTINATION_BLEND;
	}
	else
	{

		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].source_alpha_blend = TRANSLUCENT_SOURCE_BLEND;
		buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].destination_alpha_blend = TRANSLUCENT_DESTINATION_BLEND;
	}

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture = texture;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_mag = filter;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_min = mipmap;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_u_address = u;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].texture_v_address = v;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].specular = FALSE;
	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].point_offset = number_of_buffered_translucent_vertices;

	distance = 0;

	vert = polygon;

	vptr = &buffered_translucent_vertices_array[number_of_buffered_translucent_vertices];

	//
	// Set up the colour of the polygon
	//

	distance = vert->q;
	*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
	vptr->color = D3DCOLOR_RGBA ( vert->red, vert->green, vert->blue, 255 );
	vptr->specular = d3d_fog_intensity;

	vptr++;
	vert = vert->next_vertex;

	distance += vert->q;
	*( ( int * ) &vptr->sx ) = *( ( int * ) &vert->i );
	*( ( int * ) &vptr->sy ) = *( ( int * ) &vert->j );
	*( ( int * ) &vptr->tu ) = *( ( int * ) &vert->u );
	*( ( int * ) &vptr->tv ) = *( ( int * ) &vert->v );
		vptr->sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
	*( ( int * ) &vptr->rhw ) = *( ( int * ) &vert->q );
	vptr->color = D3DCOLOR_RGBA ( vert->red, vert->green, vert->blue, 255 );
	vptr->specular = d3d_fog_intensity;

	distance /= 2.0;

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].distance = *( ( int * ) &distance );

	buffered_translucent_polygons_array[number_of_buffered_translucent_polygons].number_of_vertices = 2;

	add_buffered_sorted_translucent_polygon ( number_of_buffered_translucent_polygons );

	number_of_buffered_translucent_vertices += 2;

	return ( &buffered_translucent_polygons_array[number_of_buffered_translucent_polygons++] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
