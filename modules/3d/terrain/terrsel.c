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

#include "misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// This is responsible for a simple ( and fast ) terrain elevation calculation.
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char
	*terrain_3d_simple_elevation_memory_map;

float
	*terrain_3d_simple_elevation_grid;

int
	terrain_3d_simple_elevation_memory_mapped;

int
	terrain_3d_simple_elevation_width,
	terrain_3d_simple_elevation_height;

float
	terrain_3d_simple_elevation_x_grid_size,
	terrain_3d_simple_elevation_z_grid_size,
	terrain_3d_simple_elevation_x_grid_size_reciprocal,
	terrain_3d_simple_elevation_z_grid_size_reciprocal;

static int
	num_simple_elevation_tests = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_terrain_simple_elevation ( void )
{
	
	terrain_3d_simple_elevation_memory_map = NULL;
	
	terrain_3d_simple_elevation_grid = NULL;
	
	terrain_3d_simple_elevation_memory_mapped = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_3d_terrain_fast_elevation ( float x, float z )
{
	
	int
		grid_x1,
		grid_x2,
		grid_z1,
		grid_z2;
	
	float
		x_offset,
		z_offset,
		height_x1z1,
		height_x2z1,
		height_x1z2,
		height_x2z2,
		height_zx1,
		height_zx2,
		height;
		
	num_simple_elevation_tests++;
	
	convert_float_to_int ( ( x * terrain_3d_simple_elevation_x_grid_size_reciprocal ), &grid_x1 );
	convert_float_to_int ( ( z * terrain_3d_simple_elevation_z_grid_size_reciprocal ), &grid_z1 );
	
	x_offset = x - ( grid_x1 * terrain_3d_simple_elevation_x_grid_size );
	z_offset = z - ( grid_z1 * terrain_3d_simple_elevation_z_grid_size );
	
	x_offset *= terrain_3d_simple_elevation_x_grid_size_reciprocal;
	z_offset *= terrain_3d_simple_elevation_z_grid_size_reciprocal;
	
	grid_x2 = grid_x1 + 1;
	grid_z2 = grid_z1 + 1;
	
	grid_x1 = bound ( grid_x1, 0, ( terrain_3d_simple_elevation_width - 1 ) );
	grid_x2 = bound ( grid_x2, 0, ( terrain_3d_simple_elevation_width - 1 ) );
	grid_z1 = bound ( grid_z1, 0, ( terrain_3d_simple_elevation_height - 1 ) );
	grid_z2 = bound ( grid_z2, 0, ( terrain_3d_simple_elevation_height - 1 ) );
	
	height_x1z1 = terrain_3d_simple_elevation_grid[ ( grid_z1 * terrain_3d_simple_elevation_width + grid_x1 ) ];
	height_x2z1 = terrain_3d_simple_elevation_grid[ ( grid_z1 * terrain_3d_simple_elevation_width + grid_x2 ) ];
	height_x1z2 = terrain_3d_simple_elevation_grid[ ( grid_z2 * terrain_3d_simple_elevation_width + grid_x1 ) ];
	height_x2z2 = terrain_3d_simple_elevation_grid[ ( grid_z2 * terrain_3d_simple_elevation_width + grid_x2 ) ];
	
	height_zx1 = ( ( height_x1z1 * ( 1 - z_offset ) ) + ( height_x1z2 * z_offset ) );
	height_zx2 = ( ( height_x2z1 * ( 1 - z_offset ) ) + ( height_x2z2 * z_offset ) );
	
	height = ( ( height_zx1 * ( 1 - x_offset ) ) + ( height_zx2 * x_offset ) );
	
	return ( height );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int load_terrain_simple_elevation ( char *filename )
{
	
	unsigned char
		*ptr;
	
	unload_terrain_simple_elevation_grid ();
	
	//
	// Memory map the file ( we won't be altering the data! )
	//
	
	terrain_3d_simple_elevation_memory_map = mopen ( filename );
	
	if ( !terrain_3d_simple_elevation_memory_map )
	{
		
		return ( FALSE );
	}
	
	ptr = terrain_3d_simple_elevation_memory_map;
	
	terrain_3d_simple_elevation_width = get_list_item ( ptr, int );
	
	terrain_3d_simple_elevation_height = get_list_item ( ptr, int );
	
	terrain_3d_simple_elevation_x_grid_size = get_list_item ( ptr, float );
	
	terrain_3d_simple_elevation_z_grid_size = get_list_item ( ptr, float );
	
	terrain_3d_simple_elevation_grid = ( float * ) ptr;
	
	terrain_3d_simple_elevation_x_grid_size_reciprocal = 1.0 / terrain_3d_simple_elevation_x_grid_size;

	terrain_3d_simple_elevation_z_grid_size_reciprocal = 1.0 / terrain_3d_simple_elevation_z_grid_size;
	
	terrain_3d_simple_elevation_memory_mapped = TRUE;
	
	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unload_terrain_simple_elevation_grid ( void )
{
	
	if ( terrain_3d_simple_elevation_grid )
	{
		
		//
		// Free up the elevation map already loaded
		//
		
		if ( terrain_3d_simple_elevation_memory_mapped )
		{
			
			safe_mclose ( terrain_3d_simple_elevation_memory_map );
		}
		else
		{
			
			safe_free ( terrain_3d_simple_elevation_grid );
		}
		
		terrain_3d_simple_elevation_memory_map = NULL;
		
		terrain_3d_simple_elevation_grid = NULL;
		
		terrain_3d_simple_elevation_memory_mapped = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_terrain_simple_elevation ( float elevation_grid_size )
{
	
	int
		x_size,
		z_size,
		x_grid,
		z_grid;

	int
		power,
		x_rounded,
		z_rounded;

	float
		x_elevation_grid_size,
		z_elevation_grid_size,
		sea_height;
	
	unload_terrain_simple_elevation_grid ();
	
	//
	// Figure out the dimensions of the array.
	//
	
	x_size = ( ( terrain_3d_sector_x_max * TERRAIN_3D_SECTOR_SIDE_LENGTH ) / elevation_grid_size );
	
	z_size = ( ( terrain_3d_sector_z_max * TERRAIN_3D_SECTOR_SIDE_LENGTH ) / elevation_grid_size );

	//
	// Round them to the nearest power of 2
	//

	x_rounded = z_rounded = FALSE;

	for ( power = 2; power < 32768; power *= 2 )
	{

		if ( !x_rounded )
		{

			if ( ( x_size == power ) || ( x_size < power ) )
			{

				x_size = power;

				x_rounded = TRUE;
			}
		}

		if ( !z_rounded )
		{

			if ( ( z_size == power ) || ( z_size < power ) )
			{

				z_size = power;

				z_rounded = TRUE;
			}
		}
	}

	x_elevation_grid_size = ( terrain_3d_sector_x_max * TERRAIN_3D_SECTOR_SIDE_LENGTH ) / x_size;

	z_elevation_grid_size = ( terrain_3d_sector_z_max * TERRAIN_3D_SECTOR_SIDE_LENGTH ) / z_size;

	x_size++;

	z_size++;
	
	terrain_3d_simple_elevation_grid = safe_malloc ( x_size * z_size * sizeof ( float ) );
	
	terrain_3d_simple_elevation_width = x_size;
	
	terrain_3d_simple_elevation_height = z_size;
	
	terrain_3d_simple_elevation_x_grid_size = x_elevation_grid_size;

	terrain_3d_simple_elevation_z_grid_size = z_elevation_grid_size;
	
	terrain_3d_simple_elevation_x_grid_size_reciprocal = 1.0 / terrain_3d_simple_elevation_x_grid_size;

	terrain_3d_simple_elevation_z_grid_size_reciprocal = 1.0 / terrain_3d_simple_elevation_z_grid_size;
	
	for ( z_grid = 0; z_grid < z_size; z_grid++ )
	{
		
		float
			*elevations;
		
		elevations = terrain_3d_simple_elevation_grid + ( z_grid * x_size );
		
		for ( x_grid = 0; x_grid < x_size; x_grid++ )
		{
			
			float
				x,
				z,
				height;

			terrain_types
				type;
			
			x = x_grid * x_elevation_grid_size;
			z = z_grid * z_elevation_grid_size;

			x = bound ( x, 0, terrain_3d_max_map_x );
			z = bound ( z, 0, terrain_3d_max_map_z );

			height = get_3d_terrain_elevation ( x, z );

			//
			// Find if sea or not
			//

			type = get_3d_terrain_point_data_type ( NULL );

			switch ( type )
			{

				case TERRAIN_TYPE_SEA:
				{

					height = -5000;

					break;
				}

				default:
				{

					height += 2;
				}
			}

			if ( type == TERRAIN_TYPE_SEA )
//			if ( ( type == TERRAIN_TYPE_SEA ) || ( type == TERRAIN_TYPE_BEACH ) )
			{

				height = -5000;
			}
			
			*elevations++ = height;
		}
	}

	//
	// Now go through detecting the coast line
	//

	sea_height = -1;

	for ( z_grid = 0; z_grid < z_size; z_grid++ )
	{
		
		for ( x_grid = 0; x_grid < x_size; x_grid++ )
		{

			float
				height1,
				height2;

			height1 = terrain_3d_simple_elevation_grid[((z_grid*x_size)+x_grid)];

			if ( height1 == -5000 )
			{

				int
					checked;

				float
					t,
					x1,
					z1;

				checked = FALSE;

				x1 = x_grid * x_elevation_grid_size;

				z1 = z_grid * z_elevation_grid_size;

				if ( ( !checked ) && ( z_grid < ( z_size - 1 ) ) && ( x_grid < ( x_size - 1 ) ) )
				{

					height2 = terrain_3d_simple_elevation_grid[(((z_grid+1)*x_size)+x_grid+1)];

					if ( height2 > 0 )
					{
		
						t = check_coastal_river_intersection ( x1, z1, x1 + x_elevation_grid_size, z1 + z_elevation_grid_size );

						if ( t != -1.0 )
						{

							height1 = ( sea_height - ( t * height2 ) ) / ( 1.0 - t );

							checked = TRUE;
						}
					}
				}

				if ( ( !checked ) && ( z_grid > 0 ) && ( x_grid > 0 ) )
				{

					height2 = terrain_3d_simple_elevation_grid[(((z_grid-1)*x_size)+x_grid-1)];

					if ( height2 > 0 )
					{
		
						t = check_coastal_river_intersection ( x1, z1, x1 - x_elevation_grid_size, z1 - z_elevation_grid_size );

						if ( t != -1.0 )
						{
	
							height1 = ( sea_height - ( t * height2 ) ) / ( 1.0 - t );

							checked = TRUE;
						}
					}
				}

				if ( ( !checked ) && ( z_grid > 0 ) )
				{

					height2 = terrain_3d_simple_elevation_grid[(((z_grid-1)*x_size)+x_grid)];

					if ( height2 > 0 )
					{
	
						t = check_coastal_river_intersection ( x1, z1, x1, z1 - z_elevation_grid_size );

						if ( t != -1.0 )
						{

							height1 = ( sea_height - ( t * height2 ) ) / ( 1.0 - t );

							checked = TRUE;
						}
					}
				}

				if ( ( !checked ) && ( x_grid > 0 ) )
				{

					height2 = terrain_3d_simple_elevation_grid[((z_grid*x_size)+x_grid-1)];

					if ( height2 > 0 )
					{
		
						t = check_coastal_river_intersection ( x1, z1, x1 - x_elevation_grid_size, z1 );

						if ( t != -1.0 )
						{
	
							height1 = ( sea_height - ( t * height2 ) ) / ( 1.0 - t );

							checked = TRUE;
						}
					}
				}

				if ( ( !checked ) && ( x_grid < ( x_size - 1 ) ) )
				{

					height2 = terrain_3d_simple_elevation_grid[((z_grid*x_size)+x_grid+1)];

					if ( height2 > 0 )
					{
		
						t = check_coastal_river_intersection ( x1, z1, x1 + x_elevation_grid_size, z1 );

						if ( t != -1.0 )
						{
	
							height1 = ( sea_height - ( t * height2 ) ) / ( 1.0 - t );

							checked = TRUE;
						}
					}
				}

				if ( ( !checked ) && ( z_grid < ( z_size - 1 ) ) )
				{

					height2 = terrain_3d_simple_elevation_grid[(((z_grid+1)*x_size)+x_grid)];

					if ( height2 > 0 )
					{
		
						t = check_coastal_river_intersection ( x1, z1, x1, z1 + z_elevation_grid_size );

						if ( t != -1.0 )
						{
	
							height1 = ( sea_height - ( t * height2 ) ) / ( 1.0 - t );

							checked = TRUE;
						}
					}
				}

				if ( checked )
				{

					terrain_3d_simple_elevation_grid[((z_grid*x_size)+x_grid)] = height1;
				}
			}
		}
	}

	//
	// Now bring the sea points into line
	///

	for ( z_grid = 0; z_grid < z_size; z_grid++ )
	{
		
		for ( x_grid = 0; x_grid < x_size; x_grid++ )
		{

			if ( terrain_3d_simple_elevation_grid[((z_grid*x_size)+x_grid)] == -5000 )
			{

				terrain_3d_simple_elevation_grid[((z_grid*x_size)+x_grid)] = sea_height -1;
			}
		}
	}
	
	terrain_3d_simple_elevation_memory_mapped = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_terrain_simple_elevation ( char *filename )
{
	
	FILE
		*fp;
	
	fp = safe_fopen ( filename, "wb" );
	
	fwrite ( &terrain_3d_simple_elevation_width, sizeof ( int ), 1, fp );
	
	fwrite ( &terrain_3d_simple_elevation_height, sizeof ( int ), 1, fp );
	
	fwrite ( &terrain_3d_simple_elevation_x_grid_size, sizeof ( float ), 1, fp );

	fwrite ( &terrain_3d_simple_elevation_z_grid_size, sizeof ( float ), 1, fp );
	
	fwrite ( terrain_3d_simple_elevation_grid, sizeof ( float ), terrain_3d_simple_elevation_width * terrain_3d_simple_elevation_height, fp );
	
	fclose ( fp );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_terrain_simple_elevation_statistics ( void )
{
	
	debug_log ( "num_simple_elevation_tests     = %d", num_simple_elevation_tests );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

