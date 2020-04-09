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

//VJ 050619 included to check global_anisotropic setting
#include "cmndline.h"
//VJ 040206 included for season check
#include "global.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_3d_sector
	**terrain_sectors,
	*terrain_sector_memory,
	*terrain_sector_approximations = NULL;

terrain_3d_tree_sector
	**terrain_tree_sectors;

static unsigned char
	*terrain_3d_geometry_data,
	*terrain_3d_colour_data,
	*terrain_3d_trees_data;

static int
	terrain_initialised = FALSE;

int
	terrain_3d_sector_x_max,
	terrain_3d_sector_z_max;

float
	terrain_3d_min_map_x,
	terrain_3d_min_map_z,
	terrain_3d_max_map_x,
	terrain_3d_max_map_z;

int
	terrain_3d_map_width,
	terrain_3d_map_height,
	terrain_3d_tree_map_width,
	terrain_3d_tree_map_height,
	terrain_3d_number_of_sector_approximations;

#ifndef OGRE_EE
object_3d_instance
	*terrain_3d_tree_object = NULL;

int
	terrain_3d_tree_rendering_enabled = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	terrain_3d_alpha_fog_factor,
	terrain_3d_alpha_start,
	terrain_3d_alpha_end,
	terrain_3d_alpha_distance,
	terrain_3d_alpha_constant,
	terrain_3d_alpha_factor;
#endif

float
	terrain_3d_map_minimum_height,
	terrain_3d_map_maximum_height,
	terrain_3d_map_scaled_height_difference;

#ifndef OGRE_EE
float
	terrain_colour_conversion_table[256];
#endif

terrain_3d_file_validation
	current_terrain_version;

#ifndef OGRE_EE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Casm 20MAY12 Cloud puffs
terrain_3d_cloud_puff_sector
	**terrain_cloud_puff_sectors;

object_3d_instance
	*terrain_3d_cloud_puff_object = NULL;

real_colour
	*terrain_3d_cloud_puff_colours = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_sector_colours ( void );

void initialise_3d_terrain_colour_conversion_table ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_3d_colour
	white_col[4048];
#endif

int load_3d_terrain ( const char *path )
{

	int
		total_points,
		count,
		x,
		z,
		int_map_number;

	unsigned char
		*terrain_3d_local_data,
		*terrain_3d_sector_data;
	const char
		*map_number;

	char
		free_form_polygon_file[1024],
		sector_file[1024],
		colour_file[1024],
		tree_sector_file[1024],
		tree_data_file[1024];

	terrain_3d_sector
		*terrain_sector_ptr;

#ifndef OGRE_EE
	memset(white_col, 255, sizeof(white_col));
#endif

	ASSERT ( !terrain_initialised );

	sprintf ( free_form_polygon_file, "%s\\terrain.ffp", path );

	sprintf ( sector_file, "%s\\default.sec", path );

	sprintf ( colour_file, "%s\\default.rgb", path );

	//VJ 040206 read different point colour files when available for winter,
	// made for skagway etc maps of craigmire and maverick
	if (get_global_season() == SESSION_SEASON_WINTER)
	{
		sprintf ( sector_file, "%s\\default-W.sec", path );
		sprintf ( colour_file, "%s\\default-W.rgb", path );

		if (!file_exist(sector_file) || !file_exist(colour_file))
		{
			sprintf ( sector_file, "%s\\default.sec", path );
			sprintf ( colour_file, "%s\\default.rgb", path );
		}
	}

	sprintf ( tree_sector_file, "%s\\tree_pos.sec", path );

	sprintf ( tree_data_file, "%s\\tree_pos.dat", path );

	//
	// Find the map number
	//
	//
	// This assumes the path is in the format "path\map%d\terrain"
	//
	//

	map_number = path + strlen ( path );

	while ( *map_number != '\\' )
	{

		map_number--;
	}

	map_number--;

	while ( isdigit ( *map_number ) )
	{

		map_number--;
	}

	map_number++;

	sscanf ( map_number, "%d", &int_map_number );

	//
	// Memory map the ffp file
	//

	terrain_3d_geometry_data = ( unsigned char * ) safe_mopen ( free_form_polygon_file );

	if ( !terrain_3d_geometry_data )
	{

		return ( FALSE );
	}

	//
	// Memory map the colour palette file
	//

	terrain_3d_colour_data = ( unsigned char * ) safe_mopen ( colour_file );

	if ( !terrain_3d_colour_data )
	{

		safe_mclose ( terrain_3d_geometry_data );

		terrain_3d_geometry_data = NULL;

		return ( FALSE );
	}

	//
	// Memory map the sector file
	//

	terrain_3d_sector_data = ( unsigned char * ) safe_mopen ( sector_file );

	if ( !terrain_3d_sector_data )
	{

		safe_mclose ( terrain_3d_colour_data );
		safe_mclose ( terrain_3d_geometry_data );

		terrain_3d_colour_data = NULL;
		terrain_3d_geometry_data = NULL;

		return ( FALSE );
	}

	total_points = 0;

	terrain_3d_local_data = terrain_3d_sector_data;

	//
	// Read the version integer at the start of the sector data
	//

	current_terrain_version.whole_value = get_list_item ( terrain_3d_local_data, int );

	current_terrain_version.map_number = int_map_number;

	//
	// Initialise the terrain rendering routines ( sets the type of polygon )
	//

	set_3d_terrain_dual_pass_rendering ( command_line_texture_colour == 2 || global_dynamic_water );

	initialise_3d_terrain_rendering_routines ( get_3d_terrain_dual_pass_rendering () );

	//
	// The sectors are listed going along each x axis in turn
	//

	//
	// Find the dimensions of the terrain data
	//

	terrain_3d_map_width = get_list_item ( terrain_3d_local_data, unsigned short int );

	terrain_3d_map_height = get_list_item ( terrain_3d_local_data, unsigned short int );

	//
	// Set the dimensions globally
	//

	terrain_3d_sector_x_max = terrain_3d_map_width;

	terrain_3d_sector_z_max = terrain_3d_map_height;

	terrain_3d_min_map_x = 0.0;

	terrain_3d_min_map_z = 0.0;

	terrain_3d_max_map_x = ( ( float ) ( terrain_3d_sector_x_max * TERRAIN_3D_SECTOR_SIDE_LENGTH ) - 1 );

	terrain_3d_max_map_z = ( ( float ) ( terrain_3d_sector_z_max * TERRAIN_3D_SECTOR_SIDE_LENGTH ) - 1 );

	//
	// Allocate the sectors themselves.
	//

	terrain_sector_memory = ( terrain_3d_sector * ) safe_malloc ( terrain_3d_map_width * terrain_3d_map_height * sizeof ( terrain_3d_sector ) );

	if ( !terrain_sector_memory )
	{

		safe_mclose ( terrain_3d_sector_data );
		safe_mclose ( terrain_3d_colour_data );
		safe_mclose ( terrain_3d_geometry_data );

		terrain_3d_sector_data = NULL;
		terrain_3d_colour_data = NULL;
		terrain_3d_geometry_data = NULL;

		return ( FALSE );
	}

	terrain_sector_ptr = terrain_sector_memory;

	//
	// Allocate enough space for the arrays
	//

	terrain_sectors = ( terrain_3d_sector * * ) safe_malloc ( terrain_3d_map_height * sizeof ( terrain_3d_sector * ) );

	if ( !terrain_sectors )
	{

		safe_free ( terrain_sectors );
		safe_mclose ( terrain_3d_sector_data );
		safe_mclose ( terrain_3d_colour_data );
		safe_mclose ( terrain_3d_geometry_data );

		terrain_sectors = NULL;
		terrain_3d_sector_data = NULL;
		terrain_3d_colour_data = NULL;
		terrain_3d_geometry_data = NULL;

		return ( FALSE );
	}

	terrain_3d_map_minimum_height = get_list_item ( terrain_3d_local_data, float );

	terrain_3d_map_maximum_height = get_list_item ( terrain_3d_local_data, float );

	debug_log ( "Terrain minimum height: %f", terrain_3d_map_minimum_height );

	debug_log ( "Terrain maximum height: %f", terrain_3d_map_maximum_height );

	terrain_3d_map_scaled_height_difference = ( terrain_3d_map_maximum_height - terrain_3d_map_minimum_height ) * TERRAIN_3D_Y_SCALE;

	for ( z = 0; z < terrain_3d_map_height; z++ )
	{

		//
		// First, allocate the sector array for this depth
		//

		terrain_sectors[z] = terrain_sector_ptr;

		terrain_sector_ptr += terrain_3d_map_width;

		for ( x = 0; x < terrain_3d_map_width; x++ )
		{

			int
				offset;

			//
			// First short int is the number of points in this sector
			//

			terrain_sectors[z][x].number_of_points = get_list_item ( terrain_3d_local_data, unsigned short int );

			total_points += terrain_sectors[z][x].number_of_points;

			//
			// Next short int is the number of polys in this sector
			//

			terrain_3d_local_data += 2;

			terrain_sectors[z][x].number_of_polygons = get_list_item ( terrain_3d_local_data,  unsigned short int );

			//
			// Next short int is the radius of the sector
			//

			terrain_sectors[z][x].radius = get_list_item ( terrain_3d_local_data, unsigned short int );

			//
			// Next short int is the minimum height of the sector
			//

			terrain_sectors[z][x].minimum_height = get_list_item ( terrain_3d_local_data, short int );

			//
			// Next short int is the maximum height of the sector
			//

			terrain_sectors[z][x].maximum_height = get_list_item ( terrain_3d_local_data, short int );

			//
			// Next short int is the average height of the sector
			//

			terrain_sectors[z][x].average_height = get_list_item ( terrain_3d_local_data, short int );

			//
			// Read in padding word
			//

			offset = get_list_item ( terrain_3d_local_data, short int );

			//
			// Get the offsets into the geometry file
			//

			offset = get_list_item ( terrain_3d_local_data, int );

			terrain_sectors[z][x].points_y = ( terrain_3d_point_y * ) ( terrain_3d_geometry_data + offset );

			offset = get_list_item ( terrain_3d_local_data, int );

			terrain_sectors[z][x].points_xz = ( terrain_3d_point_xz * ) ( terrain_3d_geometry_data + offset );

			offset = get_list_item ( terrain_3d_local_data, int );

			terrain_sectors[z][x].point_byte_references = ( terrain_3d_point_byte_reference * ) ( terrain_3d_geometry_data + offset );

			offset = get_list_item ( terrain_3d_local_data, int );

			terrain_sectors[z][x].polygons = ( terrain_3d_face * ) ( terrain_3d_geometry_data + offset );

			offset = get_list_item ( terrain_3d_local_data, int );

			terrain_sectors[z][x].surface_changes = ( terrain_3d_surface * ) ( terrain_3d_geometry_data + offset );

			offset = get_list_item ( terrain_3d_local_data, int );

			terrain_sectors[z][x].normal_changes = ( terrain_3d_normal_index * ) ( terrain_3d_geometry_data + offset );

			//
			// OFFSET OF NORMAL BITSTREAM
			//

			//
			// Get the offsets into the colours file
			//
			offset = get_list_item ( terrain_3d_local_data, int );

#ifndef OGRE_EE
			terrain_sectors[z][x].colour_indices = ( terrain_3d_colour_index * ) ( terrain_3d_colour_data + offset );
#endif

			offset = get_list_item ( terrain_3d_local_data, int );

#ifndef OGRE_EE
			terrain_sectors[z][x].point_colours = ( terrain_3d_colour * ) ( terrain_3d_colour_data + offset );
#endif

  // Craig start Feb. 2009
			////////////////////////////////////////////////////////////////////////////////////////
			// Changed the above if() to this so gouraud shading can be used as was originally
			// designed by Razorworks and still be able to use all the work VJ (Gotcha)
			// did on the external textures.
			// The gouraud_shading variable is set in mapinfo.txt, if the field exists,
			// and is set to the default zero if the field doesn't exist as in the existing
			// mapinfo.txt files  -  Craig
			////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
			if (command_line_texture_colour && !current_map_info.gouraud_shading)
			{
				// the colour is mixed with the textures' colours.
				// This will however darken the texture substantially, so disable it
				// when texture colour is enabled by setting it to white

				ASSERT(terrain_sectors[z][x].number_of_points < ARRAY_LENGTH(white_col));
				if (terrain_sectors[z][x].number_of_points < ARRAY_LENGTH(white_col))
					terrain_sectors[z][x].point_colours = white_col;
			}
#endif

// Craig end
			//
			// Set the approximation to off
			//

//			terrain_sectors[z][x].approximation = NULL;
		}
	}

	//
	// Now read in the number of sector approximations
	//

	terrain_3d_number_of_sector_approximations = get_list_item ( terrain_3d_local_data, unsigned int );

	if ( terrain_3d_number_of_sector_approximations )
	{

		if ( terrain_sector_approximations )
		{

			safe_free ( terrain_sector_approximations );

			terrain_sector_approximations = NULL;
		}

		terrain_sector_approximations = ( struct TERRAIN_3D_SECTOR * ) safe_malloc ( terrain_3d_number_of_sector_approximations * sizeof ( struct TERRAIN_3D_SECTOR ) );

		debug_log ( "Got %d approximated sectors", terrain_3d_number_of_sector_approximations );

		//
		// Now read in the actual approximation data
		//

		for ( count = 0; count < terrain_3d_number_of_sector_approximations; count++ )
		{

			x = get_list_item ( terrain_3d_local_data, unsigned short int );

			z = get_list_item ( terrain_3d_local_data, unsigned short int );

//			terrain_sectors[z][x].approximation = &terrain_sector_approximations[count];

			{
				int
					offset;

				//
				// First short int is the number of points in this sector
				//

				terrain_sector_approximations[count].number_of_points = get_list_item ( terrain_3d_local_data, unsigned short int );

				//
				// Next short int is the number of polys in this sector
				//

				terrain_3d_local_data += 2;

				terrain_sector_approximations[count].number_of_polygons = get_list_item ( terrain_3d_local_data,  unsigned short int );

				//
				// Next set of data is the dimensions
				//

				terrain_sector_approximations[count].radius = get_list_item ( terrain_3d_local_data, unsigned short int );

				terrain_sector_approximations[count].minimum_height = get_list_item ( terrain_3d_local_data, short int );

				terrain_sector_approximations[count].maximum_height = get_list_item ( terrain_3d_local_data, short int );

				terrain_sector_approximations[count].average_height = get_list_item ( terrain_3d_local_data, short int );

				//
				// Read in padding word
				//

				offset = get_list_item ( terrain_3d_local_data, short int );

				//
				// Get the offsets into the geometry file
				//

				offset = get_list_item ( terrain_3d_local_data, int );

				terrain_sector_approximations[count].points_y = ( terrain_3d_point_y * ) ( terrain_3d_geometry_data + offset );

				offset = get_list_item ( terrain_3d_local_data, int );

				terrain_sector_approximations[count].points_xz = ( terrain_3d_point_xz * ) ( terrain_3d_geometry_data + offset );

				offset = get_list_item ( terrain_3d_local_data, int );

				terrain_sector_approximations[count].point_byte_references = ( terrain_3d_point_byte_reference * ) ( terrain_3d_geometry_data + offset );

				offset = get_list_item ( terrain_3d_local_data, int );

				terrain_sector_approximations[count].polygons = ( terrain_3d_face * ) ( terrain_3d_geometry_data + offset );

				offset = get_list_item ( terrain_3d_local_data, int );

				terrain_sector_approximations[count].surface_changes = ( terrain_3d_surface * ) ( terrain_3d_geometry_data + offset );

				offset = get_list_item ( terrain_3d_local_data, int );

				terrain_sector_approximations[count].normal_changes = ( terrain_3d_normal_index * ) ( terrain_3d_geometry_data + offset );

				//
				// Get the offsets into the colours file
				//

				offset = get_list_item ( terrain_3d_local_data, int );

#ifndef OGRE_EE
				terrain_sector_approximations[count].colour_indices = ( terrain_3d_colour_index * ) ( terrain_3d_colour_data + offset );
#endif

				offset = get_list_item ( terrain_3d_local_data, int );

#ifndef OGRE_EE
				terrain_sector_approximations[count].point_colours = ( terrain_3d_colour * ) ( terrain_3d_colour_data + offset );
#endif
			}
		}
	}

	safe_mclose ( terrain_3d_sector_data );

	debug_log ( "TERRAIN HAS %d points", total_points );

	//
	// initialise terrain elevation (it is essential to do this every time a new map is loaded)
	//

	initialise_3d_terrain_elevation ();

#ifndef OGRE_EE
	//
	// Initialise the objects in the terrain
	//

	initialise_terrain_objects ();
#endif

	terrain_initialised = TRUE;

	//
	// Initialise the terrain trees - if there are any
	//

	if ( file_exist ( tree_sector_file ) && file_exist ( tree_data_file ) )
	{

		//
		// Map the datafile
		//

		terrain_3d_trees_data = ( unsigned char * ) safe_mopen ( tree_data_file );

		if ( terrain_3d_trees_data )
		{

			terrain_3d_sector_data = ( unsigned char * ) safe_mopen ( tree_sector_file );

			if ( terrain_3d_sector_data )
			{

				terrain_3d_local_data = terrain_3d_sector_data;

				terrain_3d_tree_map_width = get_list_item ( terrain_3d_local_data, int );

				terrain_3d_tree_map_height = get_list_item ( terrain_3d_local_data, int );

				if (	( terrain_3d_tree_map_width != terrain_3d_map_width ) ||
						( terrain_3d_tree_map_height != terrain_3d_map_height ) )
				{

					debug_colour_log ( DEBUG_COLOUR_DARK_RED, "######################################################" );
					debug_colour_log ( DEBUG_COLOUR_DARK_RED, "TREE DATA DOES NOT MATCH TERRAIN DATA - DITCHING TREES" );
					debug_colour_log ( DEBUG_COLOUR_DARK_RED, "######################################################" );
					debug_colour_log ( DEBUG_COLOUR_DARK_RED, "TREE SECTORS: %d, %d - TERRAIN SECTORS %d, %d",
																				terrain_3d_tree_map_width, terrain_3d_tree_map_height,
																				terrain_3d_map_width, terrain_3d_map_height );


					mclose ( terrain_3d_sector_data );

					mclose ( terrain_3d_trees_data );

					terrain_3d_sector_data = NULL;

					terrain_3d_trees_data = NULL;
				}
				else
				{


					terrain_tree_sectors = ( terrain_3d_tree_sector * * ) safe_malloc ( terrain_3d_tree_map_height * sizeof ( terrain_3d_tree_sector * ) );

					for ( z = 0; z < terrain_3d_tree_map_height; z++ )
					{

						terrain_tree_sectors[z] = ( terrain_3d_tree_sector * ) safe_malloc ( terrain_3d_tree_map_width * sizeof ( terrain_3d_tree_sector ) );

						for ( x = 0; x < terrain_3d_tree_map_width; x++ )
						{

							int
								offset;

							terrain_tree_sectors[z][x].number_of_trees = get_list_item ( terrain_3d_local_data, int );

							offset = get_list_item ( terrain_3d_local_data, int );

							terrain_tree_sectors[z][x].trees = ( terrain_3d_tree_data * ) terrain_3d_trees_data + offset;
						}
					}

					debug_log ( "READ IN THE TREE DATA" );

#ifndef OGRE_EE
					//
					// Construct a 3d object instance for the rendering of the terrain trees
					//

					switch ( current_terrain_version.map_number )
					{

						case 6:
						{

							//terrain_3d_tree_object = construct_3d_object_by_name ( "Y_DATE_PALM" );
							//VJ 051030 for Maverick, change to whole tree else only truncs of palms are shown
							terrain_3d_tree_object = construct_3d_object_by_name ( "FOREST_TREE_OBJECT" );
							// start render_tree_shadows-mod by GCsDriver 08-12-2007
							if ( command_line_render_shadows != 2 )
								terrain_3d_tree_object->object_has_shadow = FALSE;

							break;
						}

						default:
						{

							terrain_3d_tree_object = construct_3d_object_by_name ( "FOREST_TREE_OBJECT" );

							if ( command_line_render_shadows != 2 )
								terrain_3d_tree_object->object_has_shadow = FALSE;

							// end render_tree_shadows-mod by GCsDriver 08-12-2007
							break;
						}
					}
#endif

					mclose ( terrain_3d_sector_data );
				}
			}
		}
	}
	else
	{

		terrain_3d_trees_data = NULL;

		terrain_3d_sector_data = NULL;

		debug_log ( "Cant find the terrain tree data" );
	}

#ifndef OGRE_EE
	// Casm 20MAY12 Cloud puffs
	terrain_3d_cloud_puff_object = construct_3d_object_by_name ( "CLOUD" );

	if (session_cloud_puffs > 1 || session_cloud_puffs == 1 && get_global_season() != SESSION_SEASON_DESERT)
	{
		terrain_cloud_puff_sectors = ( terrain_3d_cloud_puff_sector** ) safe_malloc ( terrain_3d_tree_map_height * sizeof ( *terrain_cloud_puff_sectors ) );
		for ( z = 0; z < terrain_3d_tree_map_height; z++ )
		{
			terrain_cloud_puff_sectors[z] = ( terrain_3d_cloud_puff_sector* ) safe_malloc ( terrain_3d_tree_map_width * sizeof ( **terrain_cloud_puff_sectors ) );
			for ( x = 0; x < terrain_3d_tree_map_width; x++ )
			{
				int
					base,
					pack;

				int
					number_of_cloud_puffs;
				terrain_3d_cloud_puff_data
					*cloud_puffs;

				float
					center_x,
					center_y,
					center_z;

				base = rand() % 8;
				pack = rand() % 4 + 1;

				number_of_cloud_puffs = base * pack;
				cloud_puffs = number_of_cloud_puffs ? ( terrain_3d_cloud_puff_data* ) safe_malloc ( number_of_cloud_puffs * sizeof ( *cloud_puffs ) ) : NULL;

				terrain_cloud_puff_sectors[z][x].number_of_cloud_puffs = number_of_cloud_puffs;
				terrain_cloud_puff_sectors[z][x].cloud_puffs = cloud_puffs;

				for ( count = 0; count < number_of_cloud_puffs; count++, cloud_puffs++ )
				{
					float brightness,
						y_center_min = TERRAIN_3D_CLOUD_Y_CENTER_MIN;

					if ( !( count % pack ) )
					{
						do
						{
							center_x = (x + rand() / (RAND_MAX + 1.0)) * TERRAIN_3D_SECTOR_SIDE_LENGTH;
						}
						while ( center_x <= terrain_3d_min_map_x || center_x >= terrain_3d_max_map_x );
						do
						{
							center_z = (z + rand() / (RAND_MAX + 1.0)) * TERRAIN_3D_SECTOR_SIDE_LENGTH;
						}
						while ( center_z <= terrain_3d_min_map_z || center_z >= terrain_3d_max_map_z );

						ASSERT( ( center_x > terrain_3d_min_map_x ) && ( center_x < terrain_3d_max_map_x ) && ( center_z > terrain_3d_min_map_z ) && ( center_z < terrain_3d_max_map_z ) );

						y_center_min += get_3d_terrain_elevation ( center_x, center_z );

						center_y = (float)rand() / RAND_MAX * TERRAIN_3D_CLOUD_Y_CENTER_MAX + y_center_min;
					}

					cloud_puffs->x = center_x + ((float)rand() / RAND_MAX - 0.5) * 100.0;
					cloud_puffs->y = center_y + ((float)rand() / RAND_MAX - 0.5) * TERRAIN_3D_CLOUD_Y_DIFF;
					cloud_puffs->z = center_z + ((float)rand() / RAND_MAX - 0.5) * 100;
					cloud_puffs->heading = (float)rand() / RAND_MAX * PI2;
					cloud_puffs->scale = 5 + (float)rand() / RAND_MAX * 5.0;
					brightness = bound((cloud_puffs->y - y_center_min) / (TERRAIN_3D_CLOUD_Y_CENTER_MAX - TERRAIN_3D_CLOUD_Y_CENTER_MIN + TERRAIN_3D_CLOUD_Y_DIFF), 0, 1);
					cloud_puffs->colour = brightness * (number_of_cloud_puffs_colours - 1);
				}
			}
		}
		terrain_3d_cloud_puff_colours = ( real_colour* ) safe_malloc ( number_of_cloud_puffs_colours * sizeof ( *terrain_3d_cloud_puff_colours ) );
	}
	else
	{
		terrain_cloud_puff_sectors = NULL;
		terrain_3d_cloud_puff_colours = NULL;
	}
#endif

	return ( TRUE );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unload_3d_terrain ( void )
{
#ifndef OGRE_EE

	int
		x,
		z;

	//
	// Destruct any terrain objects
	//

	for ( z = 0; z < terrain_3d_sector_z_max; z++ )
	{

		for ( x = 0; x < terrain_3d_sector_x_max; x++ )
		{

			if ( terrain_sectors[z][x].objects )
			{

				terrain_3d_object
					*object;

				object = terrain_sectors[z][x].objects;

				while ( object )
				{

					destruct_3d_object ( object->object );

					object = object->next_object;
				}
			}

		}
	}
#endif

	//
	// Now free up the memory
	//

	if ( terrain_3d_geometry_data )
	{

		safe_mclose ( terrain_3d_geometry_data );

		terrain_3d_geometry_data = NULL;
	}


	if ( terrain_3d_colour_data )
	{

		safe_mclose ( terrain_3d_colour_data );

		terrain_3d_colour_data = NULL;
	}

	//
	// Free up the memory for the sectors
	//

	if ( terrain_sector_memory )
	{

		safe_free ( terrain_sector_memory );

		terrain_sector_memory = NULL;
	}

	if ( terrain_sectors )
	{

		safe_free ( terrain_sectors );

		terrain_sectors = NULL;
	}

	if ( terrain_tree_sectors )
	{
		int
			z;

		for ( z = 0; z < terrain_3d_tree_map_height; z++ )
		{
			if ( terrain_tree_sectors[z] )
			{
				safe_free ( terrain_tree_sectors[z] );
				terrain_tree_sectors[z] = NULL;
			}
		}

		safe_free ( terrain_tree_sectors );

		terrain_tree_sectors = NULL;
	}

#ifndef OGRE_EE
	if ( terrain_3d_tree_object )
	{

		destruct_3d_object ( terrain_3d_tree_object );

		terrain_3d_tree_object = NULL;
	}
#endif

	if ( terrain_3d_trees_data )
	{

		safe_mclose ( terrain_3d_trees_data );

		terrain_3d_trees_data = NULL;
	}

	terrain_initialised = FALSE;

#ifndef OGRE_EE
	//
	// Unload the simple elevation map as well
	//

	unload_terrain_simple_elevation_grid ();

	//VJ 060120 flag certain terrtain types to add textures
	// free structure
	//free_flag_terrain_types ();

	// Casm 20MAY12 Cloud puffs
	if ( terrain_3d_cloud_puff_object )
	{

		destruct_3d_object ( terrain_3d_cloud_puff_object );

		terrain_3d_cloud_puff_object = NULL;
	}

	if ( terrain_cloud_puff_sectors )
	{
		int
			z,
			x;

		for ( z = 0; z < terrain_3d_tree_map_height; z++ )
		{
			if ( terrain_cloud_puff_sectors[z] )
			{
				for ( x = 0; x < terrain_3d_tree_map_width; x++ )
				{
					if ( terrain_cloud_puff_sectors[z][x].cloud_puffs )
					{
						safe_free ( terrain_cloud_puff_sectors[z][x].cloud_puffs );
					}
				}
				safe_free ( terrain_cloud_puff_sectors[z] );
			}
		}

		safe_free ( terrain_cloud_puff_sectors );

		terrain_cloud_puff_sectors = NULL;

		safe_free ( terrain_3d_cloud_puff_colours );

		terrain_3d_cloud_puff_colours = NULL;
	}
#endif
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_terrain_detail_blend_parameters ( float fog_factor )
{

	terrain_3d_alpha_fog_factor = fog_factor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_terrain_detail_blend_factors ( void )
{

	terrain_3d_alpha_start = d3d_fog_start * terrain_3d_alpha_fog_factor;

	terrain_3d_alpha_end = d3d_fog_end * terrain_3d_alpha_fog_factor;

	terrain_3d_alpha_distance = terrain_3d_alpha_end - terrain_3d_alpha_start;

	terrain_3d_alpha_constant = terrain_3d_alpha_distance - terrain_3d_alpha_start;

	terrain_3d_alpha_factor = ( ( 255.0 / terrain_3d_alpha_distance ) * 1.0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

void initialise_3d_terrain ( void )
{

#ifndef OGRE_EE
	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Points in terrain: %d", MT_INT, &final_total_number_of_terrain_points );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Points transformed: %d", MT_INT, &final_total_number_of_terrain_points_transformed );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Faces considered: %d", MT_INT, &final_terrain_3d_faces_considered );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Faces outcoded: %d", MT_INT, &final_terrain_3d_faces_outcoded );

	debug_colour_watch ( DEBUG_COLOUR_RED, "Faces constructed: %d", MT_INT, &final_terrain_3d_faces_constructed );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Faces rejected: %d", MT_INT, &final_terrain_3d_faces_rejected );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Faces hither clipped: %d", MT_INT, &final_terrain_3d_faces_hither_clipped );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Faces screen clipped: %d", MT_INT, &final_terrain_3d_faces_screen_clipped );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Sectors inserted: %d", MT_INT, &final_terrain_3d_sectors_inserted );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Sectors totally visible: %d", MT_INT, &final_terrain_3d_sectors_totally_visible );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Sectors trivially culled: %d", MT_INT, &final_terrain_3d_sectors_trivially_culled );

	debug_colour_watch ( DEBUG_COLOUR_BLUE, "Sectors complex culled: %d", MT_INT, &final_terrain_3d_sectors_complex_culled );

	initialise_3d_terrain_colour_conversion_table ();

	initialise_3d_terrain_normals ();

	//
	// Set the terrain texture filtering states
	//

	//if ( d3d_trilinear_filtering )
	{
		terrain_texture_mag_filter = D3DTEXF_LINEAR;
		terrain_texture_min_filter = D3DTEXF_LINEAR;

		//VJ 050619 if anisotropic is on set higher filter for blending
		if( global_anisotropic )
			{ terrain_texture_mip_filter = D3DTEXF_LINEAR; }
		else
			{ terrain_texture_mip_filter = D3DTEXF_POINT; }
//		terrain_texture_mip_filter = D3DTEXF_POINT;
	}
	/*else
	{

		terrain_texture_mag_filter = D3DTFG_LINEAR;
		terrain_texture_min_filter = D3DTFN_LINEAR;

		//VJ 050619 if anisotropic is on set higher filter for blending
		if( global_anisotropic )
			{ terrain_texture_mip_filter = D3DTFP_LINEAR; }
		else
			{ terrain_texture_mip_filter = D3DTFP_POINT; }
//		terrain_texture_mip_filter = D3DTFP_POINT;
	}*/

	//
	// Set the terrain initialised flag to FALSE - as no terrain is loaded.
	//
#endif

	terrain_initialised = FALSE;
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_colour_conversion_table ( void )
{

	int
		count;

	for ( count = 0; count < 256; count++ )
	{

		terrain_colour_conversion_table[count] = ( float ) count;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_terrain_sector_as_lw_3d_object ( int x, int z, const char *filename )
{

	FILE
		*fp;

	char
		id[8];

	terrain_3d_sector
		*sector;

	int
		count,
		size,
		number_of_triangles,
		number_of_point_references;

	terrain_3d_face
		*polygon;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	fp = safe_fopen ( filename, "wb" );

	sector = &terrain_sectors[z][x];

	points_y = sector->points_y;

	points_xz = ( terrain_3d_point_xz * ) points_y + sector->number_of_points;

	fwrite ( "FORM", 4, 1, fp );

	//
	// Work out the size of the file.
	//

	//
	//
	//
	// LWOB identifier
	//			4 bytes
	//
	// Surface names:
	//			8 bytes + 8 * number of surfaces
	//
	// Surface descriptions:
	//			26 * number of surfaces
	//
	// Points:
	//			8 bytes + 12 * number of points
	//
	// Faces:
	//			8 bytes + 4 * number of faces + 2 * number of point references
	//
	// Total:
	//			28 + 12 * Points + 4 * faces + 2 * point refs
	//

	polygon = sector->polygons;

	number_of_point_references = 0;

	number_of_triangles = 0;

	for ( count = 0; count < sector->number_of_polygons; count++ )
	{

		int
			number_of_polygon_triangles;

		number_of_polygon_triangles = ( polygon->number_of_points - 2 );

		number_of_triangles += number_of_polygon_triangles;

		number_of_point_references += 3 * number_of_polygon_triangles;

		polygon++;
	}

	size = 28 +
			( 26 * ( TERRAIN_TYPE_LAST - 1 ) ) +
			( 8 * ( TERRAIN_TYPE_LAST - 1 ) ) +
			( 12 * sector->number_of_points ) +
			( 4 * number_of_triangles ) +
			( 2 * number_of_point_references );

	iff_int_write ( size, fp );

	fwrite ( "LWOB", 4, 1, fp );

	//
	// Detail the surface names
	//

	fwrite ( "SRFS", 4, 1, fp );

	iff_int_write ( ( ( TERRAIN_TYPE_LAST -1 ) * 8 ), fp );

	for ( count = 1; count < TERRAIN_TYPE_LAST; count++ )
	{

		sprintf ( id, "%07d", count );

		fwrite ( id, 8, 1, fp );
	}

	//
	// Describe the 3d points
	//

	fwrite ( "PNTS", 4, 1, fp );

	iff_int_write ( ( 12 * sector->number_of_points ), fp );

	for ( count = 0; count < sector->number_of_points; count++ )
	{

		float
			x,
			y,
			z;

		x = points_xz[count].x;
		y = points_y[count].y;
		z = points_xz[count].z;
/*
		x *= ( 2048.0 / 65535.0 );
		z *= ( 2048.0 / 65535.0 );
		y = ( sector->maximum_height - sector->minimum_height );

		if ( y == 0 )
		{

			y = sector->maximum_height;
		}
		else
		{

			y = sector->minimum_height + ( ( float ) points_y[count].y / 32767.0 ) * y;
		}
*/

		iff_float_write ( x, fp );
		iff_float_write ( y, fp );
		iff_float_write ( z, fp );
	}

	//
	// Describe the polygons
	//

	{

		int
			points_offset;

		terrain_3d_surface
			*surface;

		fwrite ( "POLS", 4, 1, fp );

		iff_int_write ( ( ( 4 * number_of_triangles ) + ( 2 * number_of_point_references ) ), fp );

		points_offset = 0;

		polygon = sector->polygons;

		surface = sector->surface_changes;

		for ( count = 0; count < sector->number_of_polygons; count++ )
		{

			int
				point_count;

			if ( polygon->surface_change )
			{

				surface++;
			}

			if ( terrain_type_information[surface->surface_id].polygon_type == POLYGON_TYPE_FAN )
			{

				if ( sector->number_of_points < 257 )
				{

					for ( point_count = 0; point_count < ( polygon->number_of_points - 2 ); point_count++ )
					{

						iff_short_int_write ( 3, fp );
						iff_short_int_write ( sector->point_byte_references[points_offset].point, fp );
						iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 1].point, fp );
						iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 2].point, fp );
						iff_short_int_write ( ( short int ) surface->surface_id, fp );
					}
				}
				else
				{

					for ( point_count = 0; point_count < ( polygon->number_of_points - 2 ); point_count++ )
					{

						iff_short_int_write ( 3, fp );
						iff_short_int_write ( sector->point_word_references[points_offset].point, fp );
						iff_short_int_write ( sector->point_word_references[points_offset + point_count + 1].point, fp );
						iff_short_int_write ( sector->point_word_references[points_offset + point_count + 2].point, fp );
						iff_short_int_write ( ( short int ) surface->surface_id, fp );
					}
				}
			}
			else
			{

				if ( sector->number_of_points < 257 )
				{

					for ( point_count = 0; point_count < ( polygon->number_of_points - 2 ); point_count++ )
					{

						if ( point_count & 1 )
						{

							iff_short_int_write ( 3, fp );
							iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 0].point, fp );
							iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 2].point, fp );
							iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 1].point, fp );
							iff_short_int_write ( ( short int ) surface->surface_id, fp );
						}
						else
						{

							iff_short_int_write ( 3, fp );
							iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 0].point, fp );
							iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 1].point, fp );
							iff_short_int_write ( sector->point_byte_references[points_offset + point_count + 2].point, fp );
							iff_short_int_write ( ( short int ) surface->surface_id, fp );
						}
					}
				}
				else
				{

					for ( point_count = 0; point_count < ( polygon->number_of_points - 2 ); point_count++ )
					{

						if ( point_count & 1 )
						{

							iff_short_int_write ( 3, fp );
							iff_short_int_write ( sector->point_word_references[points_offset + point_count + 0].point, fp );
							iff_short_int_write ( sector->point_word_references[points_offset + point_count + 2].point, fp );
							iff_short_int_write ( sector->point_word_references[points_offset + point_count + 1].point, fp );
							iff_short_int_write ( ( short int ) surface->surface_id, fp );
						}
						else
						{

							iff_short_int_write ( 3, fp );
							iff_short_int_write ( sector->point_word_references[points_offset + point_count + 0].point, fp );
							iff_short_int_write ( sector->point_word_references[points_offset + point_count + 1].point, fp );
							iff_short_int_write ( sector->point_word_references[points_offset + point_count + 2].point, fp );
							iff_short_int_write ( ( short int ) surface->surface_id, fp );
						}
					}
				}
			}



			points_offset += polygon->number_of_points;

			polygon++;
		}
	}

	//
	// Describe the surface colours
	//

	for ( count = 1; count < TERRAIN_TYPE_LAST; count++ )
	{

		unsigned char
			value;

		fwrite ( "SURF", 4, 1, fp );

		iff_int_write ( 18, fp );

		sprintf ( id, "%07d", count );

		fwrite ( id, 8, 1, fp );

		fwrite ( "COLR", 4, 1, fp );

		iff_short_int_write ( 4, fp );

		value = terrain_type_information[count].red;
		fwrite ( &value, 1, 1, fp );

		value = terrain_type_information[count].green;
		fwrite ( &value, 1, 1, fp );

		value = terrain_type_information[count].blue;
		fwrite ( &value, 1, 1, fp );

		value = 0;
		fwrite ( &value, 1, 1, fp );
	}

	fclose ( fp );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

void get_terrain_3d_sector ( float x, float z, int *sectorx, int *sectorz )
{

	set_fpu_rounding_mode_zero ();

	convert_float_to_int ( ( x / TERRAIN_3D_SECTOR_SIDE_LENGTH ), sectorx );

	convert_float_to_int ( ( z / TERRAIN_3D_SECTOR_SIDE_LENGTH ), sectorz );
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	river_texture_index = 1;

void animate_river_textures ( void )
{

	river_texture_index++;

	if ( river_texture_index > 16 )
	{

		river_texture_index = 1;
	}
/*
	switch ( river_texture_index )
	{

		case 1: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER001]; break;
		case 2: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER002]; break;
		case 3: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER003]; break;
		case 4: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER004]; break;
		case 5: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER005]; break;
		case 6: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER006]; break;
		case 7: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER007]; break;
		case 8: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER008]; break;
		case 9: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER009]; break;
		case 10: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER010]; break;
		case 11: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER011]; break;
		case 12: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER012]; break;
		case 13: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER013]; break;
		case 14: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER014]; break;
		case 15: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER015]; break;
		case 16: terrain_type_information[TERRAIN_TYPE_RIVER].texture = &system_textures[TEXTURE_INDEX_WATERLAYER016]; break;
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_all_types ( int index )
{

	int
		count;

	for ( count = ( TERRAIN_TYPE_INVALID + 1 ); count < TERRAIN_TYPE_LAST; count++ )
	{

#ifdef OGRE_EE
		terrain_type_information[count].texture_index = index;
#endif
		terrain_type_information[count].texture = system_textures[index];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int position_on_3d_terrain ( float x, float z )
{

	if ( ( x < terrain_3d_min_map_x ) || ( x > terrain_3d_max_map_x ) || ( z < terrain_3d_min_map_z ) || ( z > terrain_3d_max_map_z ) )
	{

		return ( FALSE );
	}
	else
	{

		return ( TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_terrain_3d_point_sector_min_elevation ( float x, float z )
{

	int
		sector_x,
		sector_z;

	ASSERT ( terrain_initialised );

	if ( ( x < terrain_3d_min_map_x ) || ( x > terrain_3d_max_map_x ) || ( z < terrain_3d_min_map_z ) || ( z > terrain_3d_max_map_z ) )
	{

		debug_fatal ( "Sector minimum terrain elevation off map: %f, %f", x, z );
	}

	get_terrain_3d_sector ( x, z, &sector_x, &sector_z );

	return ( ( float ) terrain_sectors[sector_z][sector_x].minimum_height );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

float get_terrain_3d_point_sector_max_elevation ( float x, float z )
{

	int
		sector_x,
		sector_z;

	ASSERT ( terrain_initialised );

	if ( ( x < terrain_3d_min_map_x ) || ( x > terrain_3d_max_map_x ) || ( z < terrain_3d_min_map_z ) || ( z > terrain_3d_max_map_z ) )
	{

		debug_fatal ( "Sector maximum terrain elevation off map: %f, %f", x, z );
	}

	get_terrain_3d_sector ( x, z, &sector_x, &sector_z );

	return ( ( float ) terrain_sectors[sector_z][sector_x].maximum_height );
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_terrain_3d_point_sector_average_elevation ( float x, float z )
{

	int
		sector_x,
		sector_z;

	ASSERT ( terrain_initialised );

	if ( ( x < terrain_3d_min_map_x ) || ( x > terrain_3d_max_map_x ) || ( z < terrain_3d_min_map_z ) || ( z > terrain_3d_max_map_z ) )
	{

		debug_fatal ( "Sector average terrain elevation off map: %f, %f", x, z );
	}

	get_terrain_3d_sector ( x, z, &sector_x, &sector_z );

	return ( ( float ) terrain_sectors[sector_z][sector_x].average_height );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

int get_terrain_3d_tree_sector_data ( int x, int z, terrain_3d_tree_data **ptr )
{

	ASSERT ( x < terrain_3d_sector_x_max );
	ASSERT ( z < terrain_3d_sector_z_max );
	ASSERT ( x >= 0 );
	ASSERT ( z >= 0 );

	if ( terrain_tree_sectors )
	{

		*ptr = terrain_tree_sectors[z][x].trees;

		return ( terrain_tree_sectors[z][x].number_of_trees );
	}
	else
	{

		return ( 0 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// keep TERRAIN_3D_MAX_TREE_HEIGHT in TERRDATA.H up to date
//

float get_terrain_3d_tree_scale ( terrain_3d_tree_data *tree )
{

	float
		scale;

	scale = tree->height;
	scale *= ( ( 25 - 6 ) / 127.0f );
	scale += 6;
	scale *= 1.10f;

	return ( scale );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	terrain_types_in_sector[TERRAIN_TYPE_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_terrain_3d_types_in_sector ( float x, float z )
{

	int
		number_of_types,
		count,
		x_sec,
		z_sec;

	struct TERRAIN_3D_FACE
		*polygon;

	struct TERRAIN_3D_SURFACE
		*surface;

	terrain_3d_sector
		*sector;

	get_terrain_3d_sector ( x, z, &x_sec, &z_sec );

	sector = &terrain_sectors[z_sec][x_sec];

	surface = sector->surface_changes;

	polygon = sector->polygons;

	memset (	terrain_types_in_sector, 0, sizeof ( int ) * TERRAIN_TYPE_LAST );

	terrain_types_in_sector[surface->surface_id] = TRUE;

	number_of_types = 1;

	for ( count = sector->number_of_polygons; count > 0; count-- )
	{

		if ( polygon->surface_change )
		{

			surface++;

			terrain_types_in_sector[surface->surface_id] = TRUE;

			number_of_types++;
		}

		polygon++;
	}

	return ( number_of_types );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_terrain_3d_number_of_type_triangles_in_sector ( float x, float z, terrain_types type )
{

	int
		total,
		count,
		x_sec,
		z_sec;

	struct TERRAIN_3D_FACE
		*polygon;

	struct TERRAIN_3D_SURFACE
		*surface;

	terrain_3d_sector
		*sector;

	get_terrain_3d_sector ( x, z, &x_sec, &z_sec );

	sector = &terrain_sectors[z_sec][x_sec];

	surface = sector->surface_changes;

	polygon = sector->polygons;

	total = 0;

	for ( count = sector->number_of_polygons; count > 0; count-- )
	{

		if ( polygon->surface_change )
		{

			surface++;

			terrain_types_in_sector[surface->surface_id] = TRUE;
		}
		else
		{

			if ( surface->surface_id == type )
			{

				total += ( polygon->number_of_points - 2 );
			}
		}

		polygon++;
	}

	return ( total );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_terrain_3d_type_triangles_in_sector ( float x, float z, terrain_types type, terrain_3d_triangle *triangles )
{

	int
		triangle_index,
		x_sec,
		z_sec,
		count;

	float
		sector_x_offset,
		sector_z_offset;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_point_y
		*points_y;

	terrain_3d_face
		*polygon;

	terrain_3d_surface
		*surface;

	terrain_3d_sector
		*sector;

	terrain_3d_triangle
		*triangle;

	get_terrain_3d_sector ( x, z, &x_sec, &z_sec );

	sector = &terrain_sectors[z_sec][x_sec];
	sector_x_offset = ( float ) ( x_sec * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 ) );
	sector_z_offset = ( float ) ( z_sec * TERRAIN_3D_SECTOR_SIDE_LENGTH + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 ) );

	points_xz = sector->points_xz;
	points_y = sector->points_y;

	polygon = sector->polygons;
	surface = sector->surface_changes;
	current_terrain_type = surface->surface_id;

	triangle_index = 0;

	triangle = triangles;

	if ( sector->number_of_points < 257 )
	{

		terrain_3d_sector_point_byte_references = sector->point_byte_references;

		for ( count = sector->number_of_polygons; count > 0; count-- )
		{

			if ( current_terrain_type == type )
			{

				while ( ( !polygon->surface_change ) && ( count > 0 ) )
				{

					int
						number_of_triangles,
						triangle_count;

					number_of_triangles = polygon->number_of_points - 2;

					if ( terrain_type_information[current_terrain_type].polygon_type == POLYGON_TYPE_FAN )
					{

						for ( triangle_count = 0; triangle_count < number_of_triangles; triangle_count++ )
						{

							int
								index;

							vec3d
								vector1,
								vector2;

							index = terrain_3d_sector_point_byte_references[0].point;
							triangle->point1.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point1.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point1.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_byte_references[triangle_count+1].point;
							triangle->point2.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point2.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point2.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_byte_references[triangle_count+2].point;
							triangle->point3.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point3.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point3.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							vector2.x = triangle->point3.x - triangle->point2.x;
							vector2.y = triangle->point3.y - triangle->point2.y;
							vector2.z = triangle->point3.z - triangle->point2.z;

							vector1.x = triangle->point2.x - triangle->point1.x;
							vector1.y = triangle->point2.y - triangle->point1.y;
							vector1.z = triangle->point2.z - triangle->point1.z;

							triangle->normal.x = ( vector1.y * vector2.z ) - ( vector1.z * vector2.y );
							triangle->normal.y = ( vector1.z * vector2.x ) - ( vector1.x * vector2.z );
							triangle->normal.z = ( vector1.x * vector2.y ) - ( vector1.y * vector2.x );

							normalise_any_3d_vector ( &triangle->normal );

							triangle++;
						}
					}
					else
					{

						int
							flag;

						flag = TRUE;

						for ( triangle_count = 0; triangle_count < number_of_triangles; triangle_count++ )
						{

							int
								index;

							vec3d
								vector1,
								vector2;

							index = terrain_3d_sector_point_byte_references[triangle_count].point;
							triangle->point1.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point1.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point1.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_byte_references[triangle_count+1].point;
							triangle->point2.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point2.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point2.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_byte_references[triangle_count+2].point;
							triangle->point3.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point3.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point3.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							if ( flag )
							{

								vector2.x = triangle->point3.x - triangle->point2.x;
								vector2.y = triangle->point3.y - triangle->point2.y;
								vector2.z = triangle->point3.z - triangle->point2.z;

								vector1.x = triangle->point2.x - triangle->point1.x;
								vector1.y = triangle->point2.y - triangle->point1.y;
								vector1.z = triangle->point2.z - triangle->point1.z;
							}
							else
							{

								vector2.x = triangle->point1.x - triangle->point2.x;
								vector2.y = triangle->point1.y - triangle->point2.y;
								vector2.z = triangle->point1.z - triangle->point2.z;

								vector1.x = triangle->point2.x - triangle->point3.x;
								vector1.y = triangle->point2.y - triangle->point3.y;
								vector1.z = triangle->point2.z - triangle->point3.z;
							}

							triangle->normal.x = ( vector1.y * vector2.z ) - ( vector1.z * vector2.y );
							triangle->normal.y = ( vector1.z * vector2.x ) - ( vector1.x * vector2.z );
							triangle->normal.z = ( vector1.x * vector2.y ) - ( vector1.y * vector2.x );

							normalise_any_3d_vector ( &triangle->normal );

							triangle++;

							flag ^= 1;
						}
					}

					terrain_3d_sector_point_byte_references += polygon->number_of_points;

					polygon++;
				}

				return;
			}

			if ( polygon->surface_change )
			{

				surface++;

				current_terrain_type = surface->surface_id;
			}

			terrain_3d_sector_point_byte_references += polygon->number_of_points;

			polygon++;
		}
	}
	else
	{

		terrain_3d_sector_point_word_references = sector->point_word_references;

		for ( count = sector->number_of_polygons; count > 0; count-- )
		{

			if ( current_terrain_type == type )
			{

				while ( ( !polygon->surface_change ) && ( count > 0 ) )
				{

					int
						number_of_triangles,
						triangle_count;

					number_of_triangles = polygon->number_of_points - 2;

					if ( terrain_type_information[current_terrain_type].polygon_type == POLYGON_TYPE_FAN )
					{

						for ( triangle_count = 0; triangle_count < number_of_triangles; triangle_count++ )
						{

							int
								index;

							vec3d
								vector1,
								vector2;

							index = terrain_3d_sector_point_word_references[0].point;
							triangle->point1.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point1.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point1.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_word_references[triangle_count+1].point;
							triangle->point2.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point2.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point2.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_word_references[triangle_count+2].point;
							triangle->point3.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point3.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point3.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							vector2.x = triangle->point3.x - triangle->point2.x;
							vector2.y = triangle->point3.y - triangle->point2.y;
							vector2.z = triangle->point3.z - triangle->point2.z;

							vector1.x = triangle->point2.x - triangle->point1.x;
							vector1.y = triangle->point2.y - triangle->point1.y;
							vector1.z = triangle->point2.z - triangle->point1.z;

							triangle->normal.x = ( vector1.y * vector2.z ) - ( vector1.z * vector2.y );
							triangle->normal.y = ( vector1.z * vector2.x ) - ( vector1.x * vector2.z );
							triangle->normal.z = ( vector1.x * vector2.y ) - ( vector1.y * vector2.x );

							normalise_any_3d_vector ( &triangle->normal );

							triangle++;
						}
					}
					else
					{

						int
							flag;

						flag = TRUE;

						for ( triangle_count = 0; triangle_count < number_of_triangles; triangle_count++ )
						{

							int
								index;

							vec3d
								vector1,
								vector2;

							index = terrain_3d_sector_point_word_references[triangle_count].point;
							triangle->point1.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point1.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point1.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_word_references[triangle_count+1].point;
							triangle->point2.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point2.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point2.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							index = terrain_3d_sector_point_word_references[triangle_count+2].point;
							triangle->point3.x = ( ( ( float ) points_xz[index].x ) * terrain_3d_xz_scale ) + sector_x_offset;
							triangle->point3.y = ( ( ( float ) points_y[index].y ) * terrain_3d_map_scaled_height_difference ) + terrain_3d_map_minimum_height;
							triangle->point3.z = ( ( ( float ) points_xz[index].z ) * terrain_3d_xz_scale ) + sector_z_offset;

							if ( flag )
							{

								vector2.x = triangle->point3.x - triangle->point2.x;
								vector2.y = triangle->point3.y - triangle->point2.y;
								vector2.z = triangle->point3.z - triangle->point2.z;

								vector1.x = triangle->point2.x - triangle->point1.x;
								vector1.y = triangle->point2.y - triangle->point1.y;
								vector1.z = triangle->point2.z - triangle->point1.z;
							}
							else
							{

								vector2.x = triangle->point1.x - triangle->point2.x;
								vector2.y = triangle->point1.y - triangle->point2.y;
								vector2.z = triangle->point1.z - triangle->point2.z;

								vector1.x = triangle->point2.x - triangle->point3.x;
								vector1.y = triangle->point2.y - triangle->point3.y;
								vector1.z = triangle->point2.z - triangle->point3.z;
							}

							triangle->normal.x = ( vector1.y * vector2.z ) - ( vector1.z * vector2.y );
							triangle->normal.y = ( vector1.z * vector2.x ) - ( vector1.x * vector2.z );
							triangle->normal.z = ( vector1.x * vector2.y ) - ( vector1.y * vector2.x );

							normalise_any_3d_vector ( &triangle->normal );

							triangle++;

							flag ^= 1;
						}
					}

					terrain_3d_sector_point_word_references += polygon->number_of_points;

					polygon++;
				}

				return;
			}

			if ( polygon->surface_change )
			{

				surface++;

				current_terrain_type = surface->surface_id;
			}

			terrain_3d_sector_point_word_references += polygon->number_of_points;

			polygon++;
		}
	}
}


#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Casm 20MAY12 Cloud puffs
void set_terrain_3d_cloud_puffs_colours ( void )
{
	int
		count;

	if ( !terrain_3d_cloud_puff_colours )
	{
		return;
	}

	for ( count = 0; count < number_of_cloud_puffs_colours; count++ )
	{
		terrain_3d_cloud_puff_colours[count].red = min(cloud_puffs_colours[count].red, (unsigned char)255);
		terrain_3d_cloud_puff_colours[count].green = min(cloud_puffs_colours[count].green, (unsigned char)255);
		terrain_3d_cloud_puff_colours[count].blue = min(cloud_puffs_colours[count].blue, (unsigned char)255);
		terrain_3d_cloud_puff_colours[count].alpha = 255;
	}
}
#endif
