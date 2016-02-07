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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define X_AND_Z_ARE_FLOATS	0	// 0 == x and z are unsigned short ints, 1 == x and z are floats

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "terrain.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int
	num_elevation_tests = 0,
	num_elevation_test_failures = 0,
	num_find_fast_successes = 0,
	num_in_poly_tests = 0;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static terrain_3d_point_data
	system_point_data;

static terrain_3d_point_word_reference
	*terrain_elevation_point_word_references;

static terrain_3d_point_byte_reference
	*terrain_elevation_point_byte_references;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_elevation (void)
{
	system_point_data.terrain_sector = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Check if point is inside convex terrain face (plan view).
//
// Co-ordinate system: +x = east, -x = west, +z = north, -z = south
//
// Use cross products of vectors to determine if clockwise or counter-clockwise point order:-
//
// dx1 = x1 - x2
// dz1 = z1 - z2
//
// dx2 = x2 - x3
// dz2 = z2 - z3
//
// result = (dx2 * dz1) - (dx1 * dz2)
//
// where: result >= 0 = clockwise order
//
//        result < 0 = counter-clockwise order
//
// NOTE: An attempt to optimise this function by doing a bounding box check before the inside polygon test failed.
//
//       The result was significantly slower (even after replacing all compares with integer compares).
//

static int point_inside_terrain_word_fan ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int number_of_points, int *triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	int
		internal_triangle_offset;

	terrain_3d_point_word_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_word_references;

	ASSERT ( number_of_points > 2 );

	point = points + point_ref->point;

	x0 = point->x;
	z0 = point->z;

	point_ref++;

	point = points + point_ref->point;

	x2 = point->x;
	z2 = point->z;

	point_ref++;

	internal_triangle_offset = 0;

	number_of_points -= 2;

	while ( number_of_points-- )
	{

		x1 = x2;
		z1 = z2;

		point = points + point_ref->point;

		x2 = point->x;
		z2 = point->z;

		point_ref++;

		//
		// Check against the first side
		//

		dx1 = x0 - x1;
		dz1 = z0 - z1;
		dx2 = x1 - x_offset;
		dz2 = z1 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the third side
			//

			dx1 = x2 - x0;
			dz1 = z2 - z0;
			dx2 = x0 - x_offset;
			dz2 = z0 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				//
				// Check against the second side
				//

				dx1 = x1 - x2;
				dz1 = z1 - z2;
				dx2 = x2 - x_offset;
				dz2 = z2 - z_offset;

				cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

				if ( cyclic >= 0.0 )
				{

					*triangle_offset = internal_triangle_offset;

					return ( TRUE );
				}
			}
		}

		internal_triangle_offset++;
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int point_inside_terrain_byte_fan ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int number_of_points, int *triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	int
		internal_triangle_offset;

	terrain_3d_point_byte_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_byte_references;

	ASSERT ( number_of_points > 2 );

	point = points + point_ref->point;

	x0 = point->x;
	z0 = point->z;

	point_ref++;

	point = points + point_ref->point;

	x2 = point->x;
	z2 = point->z;

	point_ref++;

	internal_triangle_offset = 0;

	number_of_points -= 2;

	while ( number_of_points-- )
	{

		x1 = x2;
		z1 = z2;

		point = points + point_ref->point;

		x2 = point->x;
		z2 = point->z;

		point_ref++;

		//
		// Check against the first side
		//

		dx1 = x0 - x1;
		dz1 = z0 - z1;
		dx2 = x1 - x_offset;
		dz2 = z1 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the third side
			//

			dx1 = x2 - x0;
			dz1 = z2 - z0;
			dx2 = x0 - x_offset;
			dz2 = z0 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				//
				// Check against the second side
				//

				dx1 = x1 - x2;
				dz1 = z1 - z2;
				dx2 = x2 - x_offset;
				dz2 = z2 - z_offset;

				cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

				if ( cyclic >= 0.0 )
				{

					*triangle_offset = internal_triangle_offset;

					return ( TRUE );
				}
			}
		}

		internal_triangle_offset++;
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int point_inside_terrain_word_strip ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int number_of_points, int *triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	int
		even_triangle,
		internal_triangle_offset;

	terrain_3d_point_word_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_word_references;

	ASSERT ( number_of_points > 2 );

	point = points + point_ref[0].point;

	x0 = point->x;
	z0 = point->z;

	point = points + point_ref[1].point;

	x1 = point->x;
	z1 = point->z;

	point = points + point_ref[2].point;

	x2 = point->x;
	z2 = point->z;

	point_ref++;

	even_triangle = FALSE;

	internal_triangle_offset = 0;

	number_of_points -= 2;

	while ( number_of_points-- )
	{

		//
		// Check against the first side
		//

		dx1 = x0 - x1;
		dz1 = z0 - z1;
		dx2 = x1 - x_offset;
		dz2 = z1 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the third side
			//

			dx1 = x2 - x0;
			dz1 = z2 - z0;
			dx2 = x0 - x_offset;
			dz2 = z0 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				//
				// Check against the second side
				//

				dx1 = x1 - x2;
				dz1 = z1 - z2;
				dx2 = x2 - x_offset;
				dz2 = z2 - z_offset;

				cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

				if ( cyclic >= 0.0 )
				{

					*triangle_offset = internal_triangle_offset;

					return ( TRUE );
				}
			}
		}

		if ( number_of_points )
		{

			if ( even_triangle )
			{

				point = points + point_ref[0].point;

				x0 = point->x;
				z0 = point->z;

				point = points + point_ref[1].point;

				x1 = point->x;
				z1 = point->z;

				point = points + point_ref[2].point;

				x2 = point->x;
				z2 = point->z;

				even_triangle = FALSE;
			}
			else
			{

				point = points + point_ref[0].point;

				x0 = point->x;
				z0 = point->z;

				point = points + point_ref[2].point;

				x1 = point->x;
				z1 = point->z;

				point = points + point_ref[1].point;

				x2 = point->x;
				z2 = point->z;

				even_triangle = TRUE;
			}
		}

		point_ref++;

		internal_triangle_offset++;
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int point_inside_terrain_byte_strip ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int number_of_points, int *triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	int
		even_triangle,
		internal_triangle_offset;

	terrain_3d_point_byte_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_byte_references;

	ASSERT ( number_of_points > 2 );

	point = points + point_ref[0].point;

	x0 = point->x;
	z0 = point->z;

	point = points + point_ref[1].point;

	x1 = point->x;
	z1 = point->z;

	point = points + point_ref[2].point;

	x2 = point->x;
	z2 = point->z;

	point_ref++;

	even_triangle = FALSE;

	internal_triangle_offset = 0;

	number_of_points -= 2;

	while ( number_of_points-- )
	{

		//
		// Check against the first side
		//

		dx1 = x0 - x1;
		dz1 = z0 - z1;
		dx2 = x1 - x_offset;
		dz2 = z1 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the third side
			//

			dx1 = x2 - x0;
			dz1 = z2 - z0;
			dx2 = x0 - x_offset;
			dz2 = z0 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				//
				// Check against the second side
				//

				dx1 = x1 - x2;
				dz1 = z1 - z2;
				dx2 = x2 - x_offset;
				dz2 = z2 - z_offset;

				cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

				if ( cyclic >= 0.0 )
				{

					*triangle_offset = internal_triangle_offset;

					return ( TRUE );
				}
			}
		}

		if ( even_triangle )
		{

			point = points + point_ref[0].point;

			x0 = point->x;
			z0 = point->z;

			point = points + point_ref[1].point;

			x1 = point->x;
			z1 = point->z;

			point = points + point_ref[2].point;

			x2 = point->x;
			z2 = point->z;

			even_triangle = FALSE;
		}
		else
		{

			point = points + point_ref[0].point;

			x0 = point->x;
			z0 = point->z;

			point = points + point_ref[2].point;

			x1 = point->x;
			z1 = point->z;

			point = points + point_ref[1].point;

			x2 = point->x;
			z2 = point->z;

			even_triangle = TRUE;
		}

		point_ref++;

		internal_triangle_offset++;
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int point_inside_terrain_fan_word_triangle ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	terrain_3d_point_word_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_word_references;

	point = points + point_ref->point;

	x0 = point->x;
	z0 = point->z;

	point_ref++;

	point_ref += triangle_offset;

	point = points + point_ref->point;

	x1 = point->x;
	z1 = point->z;

	point_ref++;

	point = points + point_ref->point;

	x2 = point->x;
	z2 = point->z;

	point_ref++;

	//
	// Check against the first side
	//

	dx1 = x0 - x1;
	dz1 = z0 - z1;
	dx2 = x1 - x_offset;
	dz2 = z1 - z_offset;

	cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

	if ( cyclic >= 0.0 )
	{

		//
		// Check against the third side
		//

		dx1 = x2 - x0;
		dz1 = z2 - z0;
		dx2 = x0 - x_offset;
		dz2 = z0 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the second side
			//

			dx1 = x1 - x2;
			dz1 = z1 - z2;
			dx2 = x2 - x_offset;
			dz2 = z2 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				return ( TRUE );
			}
		}
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int point_inside_terrain_fan_byte_triangle ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	terrain_3d_point_byte_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_byte_references;

	point = points + point_ref->point;

	x0 = point->x;
	z0 = point->z;

	point_ref++;

	point_ref += triangle_offset;

	point = points + point_ref->point;

	x1 = point->x;
	z1 = point->z;

	point_ref++;

	point = points + point_ref->point;

	x2 = point->x;
	z2 = point->z;

	point_ref++;

	//
	// Check against the first side
	//

	dx1 = x0 - x1;
	dz1 = z0 - z1;
	dx2 = x1 - x_offset;
	dz2 = z1 - z_offset;

	cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

	if ( cyclic >= 0.0 )
	{

		//
		// Check against the third side
		//

		dx1 = x2 - x0;
		dz1 = z2 - z0;
		dx2 = x0 - x_offset;
		dz2 = z0 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the second side
			//

			dx1 = x1 - x2;
			dz1 = z1 - z2;
			dx2 = x2 - x_offset;
			dz2 = z2 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				return ( TRUE );
			}
		}
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int point_inside_terrain_strip_word_triangle ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	terrain_3d_point_word_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_word_references;

	point_ref += triangle_offset;

	if ( triangle_offset & 1 )
	{

		//
		// Checking an odd triangle
		//

		point = points + point_ref->point;
		point_ref++;
		x0 = point->x;
		z0 = point->z;

		point = points + point_ref->point;
		point_ref++;
		x2 = point->x;
		z2 = point->z;

		point = points + point_ref->point;
		x1 = point->x;
		z1 = point->z;
	}
	else
	{

		//
		// Checking an even triangle
		//

		point = points + point_ref->point;
		point_ref++;
		x0 = point->x;
		z0 = point->z;

		point = points + point_ref->point;
		point_ref++;
		x1 = point->x;
		z1 = point->z;

		point = points + point_ref->point;
		x2 = point->x;
		z2 = point->z;
	}

	//
	// Check against the first side
	//

	dx1 = x0 - x1;
	dz1 = z0 - z1;
	dx2 = x1 - x_offset;
	dz2 = z1 - z_offset;

	cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

	if ( cyclic >= 0.0 )
	{

		//
		// Check against the third side
		//

		dx1 = x2 - x0;
		dz1 = z2 - z0;
		dx2 = x0 - x_offset;
		dz2 = z0 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the second side
			//

			dx1 = x1 - x2;
			dz1 = z1 - z2;
			dx2 = x2 - x_offset;
			dz2 = z2 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				return ( TRUE );
			}
		}
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int point_inside_terrain_strip_byte_triangle ( const float x_offset, const float z_offset, terrain_3d_point_xz *points, int triangle_offset )
{

	float
		x0,
		z0,
		x1,
		z1,
		x2,
		z2,
		dx1,
		dz1,
		dx2,
		dz2,
		cyclic;

	terrain_3d_point_byte_reference
		*point_ref;

	terrain_3d_point_xz
		*point;

#if DEBUG_MODULE

	num_in_poly_tests++;

#endif

	point_ref = terrain_elevation_point_byte_references;

	point_ref += triangle_offset;

	if ( triangle_offset & 1 )
	{

		//
		// Checking an odd triangle
		//

		point = points + point_ref->point;
		point_ref++;
		x0 = point->x;
		z0 = point->z;

		point = points + point_ref->point;
		point_ref++;
		x2 = point->x;
		z2 = point->z;

		point = points + point_ref->point;
		x1 = point->x;
		z1 = point->z;
	}
	else
	{

		//
		// Checking an even triangle
		//

		point = points + point_ref->point;
		point_ref++;
		x0 = point->x;
		z0 = point->z;

		point = points + point_ref->point;
		point_ref++;
		x1 = point->x;
		z1 = point->z;

		point = points + point_ref->point;
		x2 = point->x;
		z2 = point->z;
	}

	//
	// Check against the first side
	//

	dx1 = x0 - x1;
	dz1 = z0 - z1;
	dx2 = x1 - x_offset;
	dz2 = z1 - z_offset;

	cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

	if ( cyclic >= 0.0 )
	{

		//
		// Check against the third side
		//

		dx1 = x2 - x0;
		dz1 = z2 - z0;
		dx2 = x0 - x_offset;
		dz2 = z0 - z_offset;

		cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

		if ( cyclic >= 0.0 )
		{

			//
			// Check against the second side
			//

			dx1 = x1 - x2;
			dz1 = z1 - z2;
			dx2 = x2 - x_offset;
			dz2 = z2 - z_offset;

			cyclic = ( dx2 * dz1 ) - ( dx1 * dz2 );

			if ( cyclic >= 0.0 )
			{

				return ( TRUE );
			}
		}
	}

	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// if face_normal == NULL then no face normal data is returned
//
// if find_fast == NULL then the system find fast is used
//

#if (DEBUG_TERRAIN)
float get_3d_terrain_point_data_ex ( float x, float z, terrain_3d_point_data *point_data, char *file, int line )
#else
float get_3d_terrain_point_data ( float x, float z, terrain_3d_point_data *point_data )
#endif
{

	int
		x_sector,
		z_sector,
		number_of_faces,
		number_of_points,
		triangle_offset,
		found,
		found_fast;

	float
		x_offset,
		z_offset,
		scaled_x_offset,
		scaled_z_offset,
		y,
		dx,
		dy,
		dz,
		terrain_elevation;

	terrain_3d_sector
		*terrain_sector;

	terrain_3d_face
		*terrain_face;

	terrain_3d_point_xz
		*point;

	terrain_3d_point_y
		*point_y;

	terrain_3d_surface
		*surface;

	terrain_types
		terrain_type;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

#if DEBUG_MODULE
	num_elevation_tests++;
#endif

	////////////////////////////////////////
	//
	// check point is on the map
	//
	////////////////////////////////////////

	if ( ( x < terrain_3d_min_map_x ) || ( x > terrain_3d_max_map_x ) || ( z < terrain_3d_min_map_z ) || ( z > terrain_3d_max_map_z ) )
	{
		ASSERT (!"Terrain elevation off map");
	
		x = bound(x, terrain_3d_min_map_x + 0.0001f, terrain_3d_max_map_x - 0.0001f);
		z = bound(z, terrain_3d_min_map_z + 0.0001f, terrain_3d_max_map_z - 0.0001f);
		
	}

	////////////////////////////////////////
	//
	// get terrain sector and offsets within sector
	//
	////////////////////////////////////////

	get_terrain_3d_sector (x, z, &x_sector, &z_sector);

	//
	// Setup the point_data ptr
	///

	if ( !point_data )
	{

		point_data = &system_point_data;
	}

	//
	// Detect Cuba terrain flaw area
	//

	if ( current_terrain_version.map_number == 2 )
	{

		if (	( x_sector >= 71 ) && ( x_sector <= 72 ) &&
				( z_sector >= 58 ) && ( z_sector <= 60 ) )
		{
		
			//
			// Fudge the terrain height stuff.
			//

			point_data->terrain_sector = NULL;
	
			point_data->face_normal.x = 0.0;
			point_data->face_normal.y = 1.0;
			point_data->face_normal.z = 0.0;
	
			point_data->terrain_type = TERRAIN_TYPE_INVALID;
	
			terrain_sector = &terrain_sectors[z_sector][x_sector];

			point_data->last_elevation = terrain_sector->maximum_height;
		
			return ( terrain_sector->minimum_height );
		}
	}

	x_offset = x - ( ( float ) x_sector * TERRAIN_3D_SECTOR_SIDE_LENGTH );
	z_offset = z - ( ( float ) z_sector * TERRAIN_3D_SECTOR_SIDE_LENGTH );

	x_offset -= ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );
	z_offset -= ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 );

#if X_AND_Z_ARE_FLOATS

	scaled_x_offset = x_offset;
	scaled_z_offset = z_offset;

#else

	scaled_x_offset = ( x_offset / TERRAIN_3D_XZ_SCALE );
	scaled_z_offset = ( z_offset / TERRAIN_3D_XZ_SCALE );

#endif

	////////////////////////////////////////
	//
	// attempt find fast
	//
	////////////////////////////////////////

	found = found_fast = FALSE;

	if ( point_data->terrain_sector )
	{

		ASSERT ( point_data->terrain_face );

		if ( ( x_sector == point_data->x_sector ) && ( z_sector == point_data->z_sector ) )
		{

			terrain_sector = point_data->terrain_sector;

			points_y = terrain_sector->points_y;
		
			points_xz = terrain_sector->points_xz;
		
			terrain_face = point_data->terrain_face;

			triangle_offset = point_data->terrain_triangle_offset;

			terrain_type = point_data->terrain_type;

			if ( terrain_sector->number_of_points < 257 )
			{

				terrain_elevation_point_byte_references = point_data->terrain_elevation_point_byte_references;

				switch ( terrain_type_information[terrain_type].polygon_type )
				{

					case POLYGON_TYPE_FAN:
					{

						if ( point_inside_terrain_fan_byte_triangle ( scaled_x_offset, scaled_z_offset, points_xz, triangle_offset ) )
						{

							found = TRUE;

							found_fast = TRUE;
						}

						break;
					}

					case POLYGON_TYPE_STRIP:
					{

						if ( point_inside_terrain_strip_byte_triangle ( scaled_x_offset, scaled_z_offset, points_xz, triangle_offset ) )
						{

							found = TRUE;

							found_fast = TRUE;
						}

						break;
					}

					default:
					{

						debug_fatal ( "Unknown polygon type in terrain elevation, sector: %d, %d", x_sector, z_sector );
					}
				}
			}
			else
			{

				terrain_elevation_point_word_references = point_data->terrain_elevation_point_word_references;

				switch ( terrain_type_information[terrain_type].polygon_type )
				{

					case POLYGON_TYPE_FAN:
					{

						if ( point_inside_terrain_fan_word_triangle ( scaled_x_offset, scaled_z_offset, points_xz, triangle_offset ) )
						{

							found = TRUE;

							found_fast = TRUE;
						}

						break;
					}

					case POLYGON_TYPE_STRIP:
					{

						if ( point_inside_terrain_strip_word_triangle ( scaled_x_offset, scaled_z_offset, points_xz, triangle_offset ) )
						{

							found = TRUE;

							found_fast = TRUE;
						}

						break;
					}

					default:
					{

						debug_fatal ( "Unknown polygon type in terrain elevation, sector: %d, %d", x_sector, z_sector );
					}
				}
			}

#if DEBUG_MODULE

			if ( found )
			{

				num_find_fast_successes++;
			}

#endif
		}
	}

	////////////////////////////////////////
	//
	// scan sector
	//
	////////////////////////////////////////

	if ( !found_fast )
	{

		terrain_sector = &terrain_sectors[z_sector][x_sector];

		points_y = terrain_sector->points_y;
	
		points_xz = terrain_sector->points_xz;
	
		if ( terrain_sector->number_of_points < 257 )
		{

			//
	 		// Search through all the polygon fans first of all
			//

			number_of_faces = terrain_sector->number_of_polygons;

			terrain_face = terrain_sector->polygons;

			terrain_elevation_point_byte_references = terrain_sector->point_byte_references;

			surface = terrain_sector->surface_changes;

			while ( number_of_faces-- )
			{

				surface += terrain_face->surface_change;

				number_of_points = terrain_face->number_of_points;

				terrain_type = surface->surface_id;

				if ( terrain_type_information[terrain_type].polygon_type == POLYGON_TYPE_FAN )
				{

					if ( point_inside_terrain_byte_fan ( scaled_x_offset, scaled_z_offset, points_xz, number_of_points, &triangle_offset ) )
					{

						found = TRUE;

						break;
					}
				}

				terrain_elevation_point_byte_references += number_of_points;

				terrain_face++;
			}

			//
			// If the point isn't over a polygon fan - search the polygon strips
			//

			if ( !found )
			{

				number_of_faces = terrain_sector->number_of_polygons;

				terrain_face = terrain_sector->polygons;

				terrain_elevation_point_byte_references = terrain_sector->point_byte_references;

				surface = terrain_sector->surface_changes;

				while ( number_of_faces-- )
				{

					surface += terrain_face->surface_change;

					number_of_points = terrain_face->number_of_points;

					terrain_type = surface->surface_id;

					switch ( terrain_type )
					{

						case TERRAIN_TYPE_HEDGE_SIDE_X:
						case TERRAIN_TYPE_HEDGE_SIDE_Z:
						case TERRAIN_TYPE_WALL_SIDE_X:
						case TERRAIN_TYPE_WALL_SIDE_Z:
						case TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X:
						case TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z:
						case TERRAIN_TYPE_FOREST_SIDE_MID_X:
						case TERRAIN_TYPE_FOREST_SIDE_MID_Z:
						{

							break;
						}

						default:
						{

							if ( terrain_type_information[terrain_type].polygon_type == POLYGON_TYPE_STRIP )
							{
		
								if ( point_inside_terrain_byte_strip ( scaled_x_offset, scaled_z_offset, points_xz, number_of_points, &triangle_offset ) )
								{
		
									found = TRUE;
		
									break;
								}
							}

							break;
						}
					}

					if ( found )
					{

						break;
					}

					terrain_elevation_point_byte_references += number_of_points;

					terrain_face++;
				}
			}
		}
		else
		{

			//
			// Search through all the polygon fans first
			//

			number_of_faces = terrain_sector->number_of_polygons;

			terrain_face = terrain_sector->polygons;

			terrain_elevation_point_word_references = terrain_sector->point_word_references;

			surface = terrain_sector->surface_changes;

			while ( number_of_faces-- )
			{

				surface += terrain_face->surface_change;

				number_of_points = terrain_face->number_of_points;

				terrain_type = surface->surface_id;

				if ( terrain_type_information[terrain_type].polygon_type == POLYGON_TYPE_FAN )
				{

					if ( point_inside_terrain_word_fan ( scaled_x_offset, scaled_z_offset, points_xz, number_of_points, &triangle_offset ) )
					{

						found = TRUE;

						break;
					}
				}

				terrain_elevation_point_word_references += number_of_points;

				terrain_face++;
			}

			//
			// If the point isn't over a polygon fan - search the polygon strips
			//

			if ( !found )
			{

				number_of_faces = terrain_sector->number_of_polygons;

				terrain_face = terrain_sector->polygons;

				terrain_elevation_point_word_references = terrain_sector->point_word_references;

				surface = terrain_sector->surface_changes;

				while ( number_of_faces-- )
				{

					surface += terrain_face->surface_change;

					number_of_points = terrain_face->number_of_points;

					terrain_type = surface->surface_id;

					if ( terrain_type_information[terrain_type].polygon_type == POLYGON_TYPE_STRIP )
					{

						switch ( terrain_type )
						{
	
							case TERRAIN_TYPE_HEDGE_SIDE_X:
							case TERRAIN_TYPE_HEDGE_SIDE_Z:
							case TERRAIN_TYPE_WALL_SIDE_X:
							case TERRAIN_TYPE_WALL_SIDE_Z:
							case TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X:
							case TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z:
							case TERRAIN_TYPE_FOREST_SIDE_MID_X:
							case TERRAIN_TYPE_FOREST_SIDE_MID_Z:
							{
	
								break;
							}
	
							default:
							{
			
								if ( point_inside_terrain_word_strip ( scaled_x_offset, scaled_z_offset, points_xz, number_of_points, &triangle_offset ) )
								{
		
									found = TRUE;
		
									break;
								}
		
								break;
							}
						}
					}

					if ( found )
					{

						break;
					}

					terrain_elevation_point_word_references += number_of_points;

					terrain_face++;
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// get terrain elevation and face normal
	//
	////////////////////////////////////////

	if ( found )
	{

		if ( !found_fast )
		{

#if DEBUG_TERRAIN
			debug_log ( "Elevation: %s, %d: SLOW", file, line );
#endif

			point_data->x_sector = x_sector;

			point_data->z_sector = z_sector;

			point_data->terrain_sector = terrain_sector;

			point_data->terrain_face = terrain_face;

			if ( terrain_sector->number_of_points < 257 )
			{

				point_data->terrain_elevation_point_byte_references = terrain_elevation_point_byte_references;
			}
			else
			{

				point_data->terrain_elevation_point_word_references = terrain_elevation_point_word_references;
			}

			point_data->terrain_triangle_offset = triangle_offset;

			point_data->terrain_type = terrain_type;

			{

				vec3d
					vector1,
					vector2,
					normal;

				terrain_3d_point_xz
					*point0xz,
					*point1xz,
					*point2xz;

				terrain_3d_point_y
					*point0y,
					*point1y,
					*point2y;

				float
					y0,
					y1,
					y2;

				switch ( terrain_type_information[terrain_type].polygon_type )
				{

					case POLYGON_TYPE_FAN:
					{

						if ( terrain_sector->number_of_points < 257 )
						{

							point0xz = points_xz + terrain_elevation_point_byte_references[0].point;
							point0y = points_y + terrain_elevation_point_byte_references[0].point;

							point1xz = points_xz + terrain_elevation_point_byte_references[triangle_offset + 1].point;
							point1y = points_y + terrain_elevation_point_byte_references[triangle_offset + 1].point;

							point2xz = points_xz + terrain_elevation_point_byte_references[triangle_offset + 2].point;
							point2y = points_y + terrain_elevation_point_byte_references[triangle_offset + 2].point;
						}
						else
						{

							point0xz = points_xz + terrain_elevation_point_word_references[0].point;
							point0y = points_y + terrain_elevation_point_word_references[0].point;

							point1xz = points_xz + terrain_elevation_point_word_references[triangle_offset + 1].point;
							point1y = points_y + terrain_elevation_point_word_references[triangle_offset + 1].point;

							point2xz = points_xz + terrain_elevation_point_word_references[triangle_offset + 2].point;
							point2y = points_y + terrain_elevation_point_word_references[triangle_offset + 2].point;
						}

						break;
					}

					case POLYGON_TYPE_STRIP:
					{

						if ( terrain_sector->number_of_points < 257 )
						{

							if ( triangle_offset & 1 )
							{

								point0xz = points_xz + terrain_elevation_point_byte_references[triangle_offset].point;
								point0y = points_y + terrain_elevation_point_byte_references[triangle_offset].point;

								point1xz = points_xz + terrain_elevation_point_byte_references[triangle_offset + 2].point;
								point1y = points_y + terrain_elevation_point_byte_references[triangle_offset + 2].point;

								point2xz = points_xz + terrain_elevation_point_byte_references[triangle_offset + 1].point;
								point2y = points_y + terrain_elevation_point_byte_references[triangle_offset + 1].point;
							}
							else
							{

								point0xz = points_xz + terrain_elevation_point_byte_references[triangle_offset].point;
								point0y = points_y + terrain_elevation_point_byte_references[triangle_offset].point;

								point1xz = points_xz + terrain_elevation_point_byte_references[triangle_offset + 1].point;
								point1y = points_y + terrain_elevation_point_byte_references[triangle_offset + 1].point;

								point2xz = points_xz + terrain_elevation_point_byte_references[triangle_offset + 2].point;
								point2y = points_y + terrain_elevation_point_byte_references[triangle_offset + 2].point;
							}
						}
						else
						{

							if ( triangle_offset & 1 )
							{

								point0xz = points_xz + terrain_elevation_point_word_references[triangle_offset].point;
								point0y = points_y + terrain_elevation_point_word_references[triangle_offset].point;

								point1xz = points_xz + terrain_elevation_point_word_references[triangle_offset + 2].point;
								point1y = points_y + terrain_elevation_point_word_references[triangle_offset + 2].point;

								point2xz = points_xz + terrain_elevation_point_word_references[triangle_offset + 1].point;
								point2y = points_y + terrain_elevation_point_word_references[triangle_offset + 1].point;
							}
							else
							{

								point0xz = points_xz + terrain_elevation_point_word_references[triangle_offset].point;
								point0y = points_y + terrain_elevation_point_word_references[triangle_offset].point;

								point1xz = points_xz + terrain_elevation_point_word_references[triangle_offset + 1].point;
								point1y = points_y + terrain_elevation_point_word_references[triangle_offset + 1].point;

								point2xz = points_xz + terrain_elevation_point_word_references[triangle_offset + 2].point;
								point2y = points_y + terrain_elevation_point_word_references[triangle_offset + 2].point;
							}
						}

						break;
					}
				}

				//
				// Get the y components in world coordinates:
				//

				y0 = terrain_3d_map_minimum_height + ( point0y->y * terrain_3d_map_scaled_height_difference );
				y1 = terrain_3d_map_minimum_height + ( point1y->y * terrain_3d_map_scaled_height_difference );
				y2 = terrain_3d_map_minimum_height + ( point2y->y * terrain_3d_map_scaled_height_difference );

				vector2.x = ( float ) ( point2xz->x - point0xz->x );
				vector2.y = y2 - y0;
				vector2.z = ( float ) ( point2xz->z - point0xz->z );

				vector1.x = ( float ) ( point1xz->x - point0xz->x );
				vector1.y = y1 - y0;
				vector1.z = ( float ) ( point1xz->z - point0xz->z );

				//
				// The x & z parts of the vectors have been scaled by ( 65535 / 2048 ), so do the same to the y vectors.
				//

				vector1.y /= TERRAIN_3D_XZ_SCALE;	//( 65535.0 / TERRAIN_3D_SECTOR_SIDE_LENGTH );
				vector2.y /= TERRAIN_3D_XZ_SCALE;	//( 65535.0 / TERRAIN_3D_SECTOR_SIDE_LENGTH );

				normal.x = ( vector1.y * vector2.z ) - ( vector1.z * vector2.y );
				normal.y = ( vector1.z * vector2.x ) - ( vector1.x * vector2.z );
				normal.z = ( vector1.x * vector2.y ) - ( vector1.y * vector2.x );

				normalise_3d_vector (&normal);

				point_data->face_normal = normal;
			}
		}
#if DEBUG_TERRAIN
		else
		{

			debug_log ( "Elevation: %s, %d: FAST", file, line );
		}
#endif


		//
		// Here the find_fast structure is guaranteed to have the correct information in it.
		//

		if ( terrain_sector->number_of_points < 257 )
		{

			point = points_xz + terrain_elevation_point_byte_references[triangle_offset + 1].point;
			point_y = points_y + terrain_elevation_point_byte_references[triangle_offset + 1].point;
		}
		else
		{

			point = points_xz + terrain_elevation_point_word_references[triangle_offset + 1].point;
			point_y = points_y + terrain_elevation_point_word_references[triangle_offset + 1].point;
		}

#if X_AND_Z_ARE_FLOATS

		dx = x_offset - point->x;
		dz = z_offset - point->z;

#else

		dx = x_offset - ( ( ( float ) point->x ) * TERRAIN_3D_XZ_SCALE );
		dz = z_offset - ( ( ( float ) point->z ) * TERRAIN_3D_XZ_SCALE );

#endif

		dy = ( ( point_data->face_normal.x * dx ) + ( point_data->face_normal.z * dz ) ) / point_data->face_normal.y;

		y = terrain_3d_map_minimum_height + ( ( ( float ) point_y->y ) * terrain_3d_map_scaled_height_difference );

		terrain_elevation = y - dy;

/*
		//DEBUG//
		if (point_data->face_normal.y < 0.00001)
		{
			if (point_data->face_normal.y < 0.0)
			{
				debug_log ("Face normal is undercut %f", point_data->face_normal.y);
			}
			else
			{
				debug_log ("Face normal y component is %f", point_data->face_normal.y);
			}

			point_data->face_normal.x = 0.0;
			point_data->face_normal.y = 1.0;
			point_data->face_normal.z = 0.0;

			terrain_elevation = terrain_sector->maximum_height;
		}
		//DEBUG//
		*/
	}
	else
	{

		debug_log ( "Failed to locate a terrain face (x = %.4f, z = %.4f, x_sector = %d, z_sector = %d, x_offset = %f, z_offset = %f",
																				x, z, x_sector, z_sector, x_offset + 1024, z_offset + 1024 );

#if DEBUG_MODULE

		num_elevation_test_failures++;

#endif

		point_data->terrain_sector = NULL;

		point_data->face_normal.x = 0.0;
		point_data->face_normal.y = 1.0;
		point_data->face_normal.z = 0.0;

		point_data->terrain_type = TERRAIN_TYPE_INVALID;

		terrain_elevation = terrain_sector->maximum_height;
	}

	////////////////////////////////////////
	//
	// return values
	//
	////////////////////////////////////////

	if ( ( terrain_elevation < -32000 ) || ( terrain_elevation > 32000 ) )
	{

		terrain_elevation = 0;
	}

	point_data->last_elevation = terrain_elevation;

	return ( terrain_elevation );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void terrain_elevation_soak_test (int samples_per_sector_side)
{
	int
		x_sec,
		z_sec;

	float
		sample_distance,
		x,
		x_start,
		x_end,
		z,
		z_start,
		z_end;

	debug_log ("*** start terrain elevation soak test ***");

	sample_distance = ((float) TERRAIN_3D_SECTOR_SIDE_LENGTH) / ((float) samples_per_sector_side);

	for (z_sec = 0; z_sec < terrain_3d_sector_z_max; z_sec++)
	{
		debug_log ("z sector = %d", z_sec);

		for (x_sec = 0; x_sec < terrain_3d_sector_x_max; x_sec++)
		{
			z_start = (float) (z_sec * TERRAIN_3D_SECTOR_SIDE_LENGTH);

			z_end = (float) ((z_sec + 1) * TERRAIN_3D_SECTOR_SIDE_LENGTH);

			for (z = z_start; z < z_end; z += sample_distance)
			{
				x_start = (float) (x_sec * TERRAIN_3D_SECTOR_SIDE_LENGTH);

				x_end = (float) ((x_sec + 1) * TERRAIN_3D_SECTOR_SIDE_LENGTH);

				for (x = x_start; x < x_end; x += sample_distance)
				{
					ASSERT( ( x > terrain_3d_min_map_x ) && ( x < terrain_3d_max_map_x ) && ( z > terrain_3d_min_map_z ) && ( z < terrain_3d_max_map_z ) );

					get_3d_terrain_point_data (x, z, NULL);
				}
			}
		}
	}

	debug_log ("*** end terrain elevation soak test ***");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

void display_terrain_elevation_statistics (void)
{
	debug_log ("=====================================");
	debug_log ("TERRAIN ELEVATION STATISTICS");
	debug_log ("-------------------------------------");
	debug_log ("num_elevation_tests            = %d", num_elevation_tests);

	if (num_elevation_tests > 0)
	{
		debug_log ("num_in_poly_tests              = %d", num_in_poly_tests);
		debug_log (".. average per elevation test  = %.2f", (float) num_in_poly_tests / (float) num_elevation_tests);
		debug_log ("num_find_fast_successes        = %d", num_find_fast_successes);
		debug_log (".. overall percentage          = %.2f", ((float) num_find_fast_successes / (float) num_elevation_tests) * 100.0);
		debug_log ("num_elevation_test_failures    = %d", num_elevation_test_failures);
	}

	display_terrain_simple_elevation_statistics ();

	debug_log ("=====================================");
}

#else

void display_terrain_elevation_statistics (void)
{
	debug_log ("WARNING! Terrain elevation statistics are not enabled");
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Terrain point data access functions
//

vec3d *get_3d_terrain_point_data_normal ( terrain_3d_point_data *point_data )
{

	if ( !point_data )
	{

		point_data = &system_point_data;
	}

	return ( &point_data->face_normal );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_3d_terrain_point_data_elevation ( terrain_3d_point_data *point_data )
{

	if ( !point_data )
	{

		point_data = &system_point_data;
	}

	return ( point_data->last_elevation );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_types get_3d_terrain_point_data_type ( terrain_3d_point_data *point_data )
{

	if ( !point_data )
	{

		point_data = &system_point_data;
	}

	return ( point_data->terrain_type );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_3d_terrain_point_data ( terrain_3d_point_data *point_data )
{

	if ( !point_data )
	{

		point_data = &system_point_data;
	}

	point_data->terrain_sector = NULL;
	point_data->terrain_face = NULL;
	point_data->terrain_type = TERRAIN_TYPE_INVALID;
	point_data->face_normal.x = 0;
	point_data->face_normal.y = 0;
	point_data->face_normal.z = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_3d_terrain_elevation_and_face_normal ( float x, float z, vec3d *normal, terrain_3d_point_data *point_data )
{

	float
		height;

	ASSERT( ( x > terrain_3d_min_map_x ) && ( x < terrain_3d_max_map_x ) && ( z > terrain_3d_min_map_z ) && ( z < terrain_3d_max_map_z ) );

	height = get_3d_terrain_point_data ( x, z, NULL );

	if ( normal )
	{
	
		get_3d_terrain_last_normal ( normal );
	}

	return ( height );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_3d_terrain_face_normal ( vec3d *normal, float x, float z )
{
	ASSERT( ( x > terrain_3d_min_map_x ) && ( x < terrain_3d_max_map_x ) && ( z > terrain_3d_min_map_z ) && ( z < terrain_3d_max_map_z ) );

	get_3d_terrain_point_data ( x, z, NULL );

	get_3d_terrain_last_normal ( normal );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_3d_terrain_last_normal ( vec3d *normal )
{

	*normal = system_point_data.face_normal;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
