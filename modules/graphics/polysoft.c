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

#include	"graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// This contains all the drawing of software drawn polygons.
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	num_plain_polys,
	num_shaded_polys,
	num_shaded_textures,
	num_textures;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_polygon ( vertex *polygon, unsigned int colour, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	y_max = y_min;

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;
	last_point = polygon;

//	scan_zbuffer_plain_line ( last_point, this_point );
	scan_plain_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;
		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

//		scan_zbuffer_plain_line ( last_point, this_point );
		scan_plain_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

//		fill_zbuffer_plain_polygon ( colour );
		fill_plain_polygon ( colour );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_polygon ( vertex *polygon, unsigned int colour, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;


	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	y_max = y_min;

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_gouraud_shaded_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_gouraud_shaded_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_gouraud_polygon ( colour );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_textured_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_plain_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_flat_shaded_textured_polygon ( vertex *polygon, struct TEXTURE_MAP *texture, float intensity, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_flat_shaded_textured_polygon ( texture, intensity );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_textured_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_gouraud_shaded_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_gouraud_shaded_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_gouraud_shaded_textured_polygon ( texture );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_textured_anchored_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_plain_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_flat_shaded_textured_anchored_polygon ( vertex *polygon, struct TEXTURE_MAP *texture, float intensity, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_flat_shaded_textured_polygon ( texture, intensity );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_textured_anchored_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_gouraud_shaded_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_gouraud_shaded_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_gouraud_shaded_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_textured_perspective_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_plain_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_flat_shaded_textured_perspective_polygon ( vertex *polygon, struct TEXTURE_MAP *texture, float intensity, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_flat_shaded_textured_polygon ( texture, intensity );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_textured_perspective_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_gouraud_shaded_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_gouraud_shaded_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_gouraud_shaded_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_wrapped_textured_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_plain_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_flat_shaded_wrapped_textured_polygon ( vertex *polygon, struct TEXTURE_MAP *texture, float intensity, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_flat_shaded_wrapped_textured_polygon ( texture, intensity );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_wrapped_textured_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_gouraud_shaded_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_gouraud_shaded_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_gouraud_shaded_wrapped_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_wrapped_textured_anchored_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_plain_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_flat_shaded_wrapped_textured_anchored_polygon ( vertex *polygon, struct TEXTURE_MAP *texture, float intensity, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_flat_shaded_textured_polygon ( texture, intensity );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_wrapped_textured_anchored_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_gouraud_shaded_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_gouraud_shaded_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_gouraud_shaded_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_wrapped_textured_perspective_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_plain_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_flat_shaded_wrapped_textured_perspective_polygon ( vertex *polygon, struct TEXTURE_MAP *texture, float intensity, float red, float green, float blue )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_plain_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_plain_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_flat_shaded_textured_polygon ( texture, intensity );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_wrapped_textured_perspective_polygon ( vertex *polygon, struct TEXTURE_MAP *texture )
{

	vertex
		*this_point,
		*last_point;

	convert_float_to_int ( polygon->j, &y_min );							// Initialise the fill buffers size

	convert_float_to_int ( polygon->i, &rhs_x[y_min] );

	y_max = y_min;

	lhs_x[y_min] = rhs_x[y_min];

	this_point = polygon->next_vertex;

	last_point = polygon;

	scan_gouraud_shaded_textured_line ( last_point, this_point );

	while ( this_point != polygon )
	{

		last_point = this_point;

		this_point = this_point->next_vertex;

		if ( ! this_point )
		{

			this_point = polygon;
		}

		scan_gouraud_shaded_textured_line ( last_point, this_point );
	}

	if ( y_min != y_max )
	{

		fill_gouraud_shaded_textured_polygon ( texture );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

