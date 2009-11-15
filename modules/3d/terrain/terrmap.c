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

#define MAX_3D_CLIP_COORDINATES 16

#define CONTOUR_SHADING_FACTOR 0.05

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	command_line_campaign_map,
	command_line_campaign_map_palette;	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	terrain_2d_map_contour_lines_drawn = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	terrain_2d_map_world_xmin,
	terrain_2d_map_world_xmax,
	terrain_2d_map_world_xcentre,

	terrain_2d_map_world_zmin,
	terrain_2d_map_world_zmax,
	terrain_2d_map_world_zcentre,

	terrain_2d_map_screen_xmin,
	terrain_2d_map_screen_xmax,
	terrain_2d_map_screen_xcentre,

	terrain_2d_map_screen_ymin,
	terrain_2d_map_screen_ymax,
	terrain_2d_map_screen_ycentre,

	terrain_2d_map_screen_xscale,
	terrain_2d_map_screen_yscale;

static int
	terrain_2d_map_textured = TRUE;

rgb_colour
	*terrain_2d_contour_colours = NULL,
	*terrain_2d_contour_intensities = NULL,
	*terrain_2d_current_contour_colours = NULL,

	contour_colours[1024] =
	{
		{ 240,190,130 },  // water colour

		// Made with hue: 0.32 - 0.02, value: 0.40 - 0.60, saturation: 0.70 - 0.65
		{ 30, 102,  36},
		{ 31, 103,  41},
		{ 32, 105,  47},
		{ 32, 107,  53},
		{ 33, 109,  59},
		{ 34, 111,  65},
		{ 35, 112,  71},
		{ 35, 114,  77},
		{ 36, 116,  84},
		{ 37, 118,  90},
		{ 38, 120,  97},
		{ 39, 122, 104},
		{ 39, 123, 111},
		{ 40, 125, 118},
		{ 41, 127, 125},
		{ 42, 125, 129},
		{ 43, 121, 131},
		{ 43, 117, 132},
		{ 44, 113, 134},
		{ 45, 109, 136},
		{ 46, 104, 138},
		{ 47, 100, 140},
		{ 48,  95, 142},
		{ 49,  90, 143},
		{ 49,  86, 145},
		{ 50,  81, 147},
		{ 51,  76, 149},
		{ 52,  70, 151},
		{ 53,  65, 152},
		{ 74,  84, 161},
		{ 96, 105, 169},
		{120, 127, 178},
		{146, 151, 186},
		{174, 176, 195},
		{203, 203, 203},
		{212, 212, 212},
		{221, 221, 221},
		{229, 229, 229},
		{238, 238, 238},
		{246, 246, 246},
		{255, 255, 255},
	},

	contour_paper_colours[1024] =
	{
		// made with hue: 0.32 - 0.04, value 0.6 - 0.7, saturation 0.3 - 0.2
		{ 240,190,130 },  // water colour
		{108, 153, 114},
		{109, 154, 118},
		{110, 155, 122},
		{111, 156, 126},
		{113, 157, 129},
		{114, 158, 133},
		{115, 159, 137},
		{116, 160, 141},
		{118, 161, 144},
		{119, 162, 148},
		{120, 163, 151},
		{121, 163, 155},
		{123, 164, 158},
		{124, 165, 162},
		{125, 166, 165},
		{126, 165, 167},
		{128, 164, 168},
		{129, 163, 169},
		{130, 161, 170},
		{132, 160, 171},
		{133, 158, 172},
		{134, 157, 173},
		{136, 156, 173},
		{137, 155, 174},
		{138, 154, 175},
		{140, 153, 176},
		{141, 152, 177},
		{142, 142, 178},
		{155, 152, 184},
		{167, 163, 190},
		{179, 173, 196},
		{190, 184, 202},
		{201, 196, 207},
		{210, 207, 213},
		{219, 219, 219},
		{225, 225, 225},
		{231, 231, 231},
		{237, 237, 237},
		{243, 243, 243},
		{249, 249, 249},
		{255, 255, 255},
	};

float
	*terrain_2d_contour_heights = NULL,
	contour_heights[] =
	{
		-1000,
		-0.0001,
		10,
		25,
		50,
		75,
		100,
		150,
		200,
		250,
		300,
		350,
		400,
		450,
		500,
		600,
		700,
		800,
		900,
		1000,
		1100,
		1200,
		1300,
		1400,
		1500,
		1600,
		1700,
		1800,
		1900,
		2000,
		2100,
		2200,
		2300,
		2400,
		2500,
		2750,
		3000,
		3250,
		3500,
		3750,
		4000,
		6000
	};

float
	*contour_height_difference_reciprocals;

int
	number_of_contour_height_lines = 42;

static vertex
	*this_point,
	*last_point,
	*clip_list,
	*clip_point;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3d
	*contour_map_river_nodes = NULL,
	*contour_map_river_path_positions = NULL,
	*contour_map_road_nodes = NULL,
	*contour_map_road_path_positions = NULL,
	*contour_map_boundary_nodes = NULL,
	*contour_map_boundary_path_positions = NULL;

contour_path
	*contour_map_river_paths = NULL,
	*contour_map_road_paths = NULL,
	*contour_map_boundary_paths = NULL;

int
	contour_map_number_of_mipmaps = 0,
	contour_map_number_of_river_nodes = 0,
	contour_map_number_of_river_paths = 0,
	contour_map_number_of_road_nodes = 0,
	contour_map_number_of_road_paths = 0,
	contour_map_number_of_boundary_nodes = 0,
	contour_map_number_of_boundary_paths = 0,
	number_of_contour_lakes = 0,
	number_of_contour_citybases = 0;

float
	**contour_map_mipmaps = NULL;

contour_lake
	*contour_lakes,
	*contour_citybases;

vec3d
	*contour_lake_vertices,
	*contour_citybase_vertices;

float
	contour_minimum_height,
	contour_maximum_height;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int load_2d_terrain_contour_river_data ( char *nodes_filenamne, char *path_filename );

static int load_2d_terrain_contour_road_data ( char *nodes_filenamne, char *path_filename );

static void load_contour_map_lakes ( char *filename );

static void load_contour_map_citybases ( char *filename );

static void set_node_database_extents ( int number_of_nodes, contour_path *paths, vec3d *nodes );

static void set_lake_database_extents ( int number_of_triangle_sets, contour_lake *lakes );

static void render_contour_triangle_database ( int number_of_triangle_sets, contour_lake *lakes, real_colour lake_colour );

void generate_simple_elevation_vertex ( int x, int z, vertex *v );

static void generate_world_position_vertex ( vec3d *position, vertex *v );

float get_simple_elevation_height ( int x, int z );

static unsigned char generate_contour_outcode ( float i, float j );

static void render_contour_terrain_quad ( vertex *vertices, int start_contour, int end_contour );

/*static*/ void render_contour_terrain_quad_quad ( vertex *vertices, int contour_start_index, int contour_end_index );
//static void render_contour_terrain_poly ( vertex *poly, real_colour contour_colour, float contour_height_difference_reciprocal );

static void render_shaded_contour_terrain_poly ( vertex *poly, real_colour contour_colour);

void render_contour_node_database ( int number_of_nodes, contour_path *paths, vec3d *nodes, real_colour colour, int mipmap_level );

void render_contour_node_thick_database ( int number_of_nodes, contour_path *paths, vec3d *nodes, real_colour colour, int mipmap_level );

static void draw_contour_line ( vertex *vertices, real_colour colour );

static void draw_thick_contour_line ( vertex *vertices, real_colour colour );

static vertex *clip_contour_polygon ( vertex *polygon, int outcode );

static vertex *bottom_clip_contour_polygon ( vertex *polygon, int *polygon_outcode );

static vertex *top_clip_contour_polygon ( vertex *polygon, int *polygon_outcode );

static void insert_bottom_contour_coordinate ( vertex *point1, vertex *point2 );

static void insert_top_contour_coordinate ( vertex *point1, vertex *point2 );

static void insert_xmin_contour_coordinate ( vertex *point1, vertex *point2 );

static void insert_xmax_contour_coordinate ( vertex *point1, vertex *point2 );

static void insert_ymin_contour_coordinate ( vertex *point1, vertex *point2 );

static void insert_ymax_contour_coordinate ( vertex *point1, vertex *point2 );

int load_2d_terrain_contour_boundary_data ( char *nodes_filename, char *path_filename );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_terrain_map_textured ( int flag )
{

	terrain_2d_map_textured = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_terrain_map_dimensions ( float wxmin, float wzmin, float wxmax, float wzmax, float sxmin, float symin, float sxmax, float symax )
{

	terrain_2d_map_world_xmin = wxmin;
	terrain_2d_map_world_xmax = wxmax;
	terrain_2d_map_world_xcentre = ( wxmin + wxmax ) / 2;


	terrain_2d_map_world_zmin = wzmin;
	terrain_2d_map_world_zmax = wzmax;
	terrain_2d_map_world_zcentre = ( wzmin + wzmax ) / 2;


	terrain_2d_map_screen_xmin = sxmin;
	terrain_2d_map_screen_xmax = sxmax;
	terrain_2d_map_screen_xcentre = ( sxmin + sxmax ) / 2;


	terrain_2d_map_screen_ymin = symin;
	terrain_2d_map_screen_ymax = symax;
	terrain_2d_map_screen_ycentre = ( symin + symax ) / 2;

	//
	// Need to take into account the scale of the world vs the scale of the screen
	//

	terrain_2d_map_screen_xscale = ( ( terrain_2d_map_screen_xmax - terrain_2d_map_screen_xcentre ) /
												( terrain_2d_map_world_xmax - terrain_2d_map_world_xcentre ) );

	terrain_2d_map_screen_yscale = ( ( terrain_2d_map_screen_ymax - terrain_2d_map_screen_ycentre ) /
												( terrain_2d_map_world_zmax - terrain_2d_map_world_zcentre ) );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_terrain_map_world_dimensions ( float *wxmin, float *wzmin, float *wxmax, float *wzmax )
{

	*wxmin = terrain_2d_map_world_xmin;
	*wxmax = terrain_2d_map_world_xmax;
	*wzmin = terrain_2d_map_world_zmin;
	*wzmax = terrain_2d_map_world_zmax;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_terrain_map_screen_dimensions ( float *sxmin, float *symin, float *sxmax, float *symax )
{

	*sxmin = terrain_2d_map_screen_xmin;
	*sxmax = terrain_2d_map_screen_xmax;
	*symin = terrain_2d_map_screen_ymin;
	*symax = terrain_2d_map_screen_ymax;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_terrain_map ( void )
{

	int
		count,
		current_sector_x,
		current_sector_z,
		minimum_sector_x,
		minimum_sector_z,
		maximum_sector_x,
		maximum_sector_z,
		sector_x_count,
		sector_z_count,
		sector_x_total,
		sector_z_total,
		sector_x_increment,
		sector_z_increment;

	terrain_3d_face
		*polygon;

	object_transformed_3d_point
		*result_3d_points;

	object_transformed_2d_point
		*result_2d_points;

	terrain_3d_transformed_point_colour
		*result_colours;

	unsigned char
		*result_outcodes;

	float
		current_sector_x_offset,
		current_sector_z_offset,
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	terrain_3d_point_xz
		*points_xz;

	terrain_3d_surface
		*surface;

	terrain_3d_colour
		*colours;

	terrain_3d_colour_index
		*colour_indices;

	//
	// Turn off Z buffering for the 2d map.
	//

	set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, FALSE );

	//
	// Turn off fogging
	//

	suspend_d3d_fog ();

	//
	// Set up the texturing & renderstates
	//

	set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESS, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, TERRAIN_TEXTURE_FILTER );
	set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, TERRAIN_TEXTURE_MIN_FILTER );

	if ( terrain_2d_map_textured )
	{

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	}
	else
	{

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
		set_d3d_texture ( 0, NULL );
	}

	set_d3d_texture_stage_state ( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 1, NULL );

	//
	// Set up the lighting indices
	//

	terrain_3d_transformed_point_normals[0].r = 1;
	terrain_3d_transformed_point_normals[0].g = 1;
	terrain_3d_transformed_point_normals[0].b = 1;

	//
	// Set up the sectors to scan
	//

	set_viewport ( terrain_2d_map_screen_xmin, terrain_2d_map_screen_ymin, terrain_2d_map_screen_xmax, terrain_2d_map_screen_ymax );

	get_terrain_3d_sector ( terrain_2d_map_world_xmin, terrain_2d_map_world_zmin, &minimum_sector_x, &minimum_sector_z );

	get_terrain_3d_sector ( terrain_2d_map_world_xmax, terrain_2d_map_world_zmax, &maximum_sector_x, &maximum_sector_z );

	minimum_sector_x = bound ( minimum_sector_x, 0, ( terrain_3d_sector_x_max - 1 ) );
	minimum_sector_z = bound ( minimum_sector_z, 0, ( terrain_3d_sector_z_max - 1 ) );
	maximum_sector_x = bound ( maximum_sector_x, 0, ( terrain_3d_sector_x_max - 1 ) );
	maximum_sector_z = bound ( maximum_sector_z, 0, ( terrain_3d_sector_z_max - 1 ) );

	sector_x_total = abs ( maximum_sector_x - minimum_sector_x ) + 1;

	sector_z_total = abs ( maximum_sector_z - minimum_sector_z ) + 1;

	if ( maximum_sector_x > minimum_sector_x )
	{

		sector_x_increment = 1;
	}
	else
	{

		sector_x_increment = -1;
	}


	if ( maximum_sector_z > minimum_sector_z )
	{

		sector_z_increment = 1;
	}
	else
	{

		sector_z_increment = -1;
	}


	for ( current_sector_z = minimum_sector_z, sector_z_count = 0;

				sector_z_count < sector_z_total;

				current_sector_z += sector_z_increment, sector_z_count++ )
	{

		for ( current_sector_x = minimum_sector_x, sector_x_count = 0;

					sector_x_count < sector_x_total;

					current_sector_x += sector_x_increment, sector_x_count++ )
		{

			current_sector_x_offset = current_sector_x * TERRAIN_3D_SECTOR_SIDE_LENGTH;

			current_sector_z_offset = current_sector_z * TERRAIN_3D_SECTOR_SIDE_LENGTH;

			//
			// Transform all the points in the sector.
			//

			current_terrain_sector = &terrain_sectors[current_sector_z][current_sector_x];

			result_3d_points = transformed_3d_3d_points;

			result_2d_points = transformed_3d_2d_points;

			result_outcodes = transformed_3d_point_outcodes;

			result_colours = transformed_3d_point_colours;

			points_xz = current_terrain_sector->points_xz;

			current_terrain_points_xz = current_terrain_sector->points_xz;

			current_terrain_points_y = current_terrain_sector->points_y;

			colours = current_terrain_sector->point_colours;

			colour_indices = current_terrain_sector->colour_indices;

			for ( count = 0; count < current_terrain_sector->number_of_points; count++ )
			{

				float
					posx,
					posz;

				int
					colour_index;

				posx = ( ( current_sector_x_offset + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 ) +
							( ( float ) points_xz->x ) * TERRAIN_3D_XZ_SCALE ) - terrain_2d_map_world_xcentre );

				posz = ( ( current_sector_z_offset + ( TERRAIN_3D_SECTOR_SIDE_LENGTH / 2 ) +
							( ( float ) points_xz->z ) * TERRAIN_3D_XZ_SCALE ) - terrain_2d_map_world_zcentre );

				result_3d_points->x = posx;
				result_3d_points->y = posz;

				result_2d_points->z = 100;
				result_2d_points->q = 0.01;

				result_2d_points->i = ( ( posx * terrain_2d_map_screen_xscale ) + terrain_2d_map_screen_xcentre );
				result_2d_points->j = ( ( posz * terrain_2d_map_screen_yscale ) + terrain_2d_map_screen_ycentre );

				colour_index = colour_indices->index;

				result_colours->red = colours[colour_index].red;
				result_colours->green = colours[colour_index].green;
				result_colours->blue = colours[colour_index].blue;
				result_colours->normal_index = 0;

				result_colours->fog = 255;

				oxmax = active_viewport.x_max - result_2d_points->i;
				oxmin = result_2d_points->i - active_viewport.x_min;
				oymax = active_viewport.y_max - result_2d_points->j;
				oymin = result_2d_points->j - active_viewport.y_min;

				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );

				*result_outcodes = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				result_3d_points++;
				result_2d_points++;
				result_colours++;
				result_outcodes++;

				points_xz++;

				colour_indices++;
			}

			//
			// Go through all the polygons in the sector, drawing them.
			//

			points_xz = ( terrain_3d_point_xz * ) current_terrain_sector->points_y + current_terrain_sector->number_of_points;

			polygon = current_terrain_sector->polygons;

			surface = current_terrain_sector->surface_changes;

			current_terrain_type = surface->surface_id;

			current_terrain_type_class = &terrain_type_information[current_terrain_type];

			set_d3d_texture ( 0, current_terrain_type_class->texture );

			reset_terrain_3d_buffered_polygons ();

			if ( current_terrain_sector->number_of_points < 257 )
			{

				terrain_3d_sector_point_byte_references = current_terrain_sector->point_byte_references;

				for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
				{

					int
						number_of_points;

					if ( polygon->surface_change )
					{

						surface += polygon->surface_change;

						draw_terrain_3d_buffered_polygons ();

						current_terrain_type = surface->surface_id;

						current_terrain_type_class = &terrain_type_information[current_terrain_type];

						if ( terrain_2d_map_textured )
						{

							set_d3d_texture ( 0, current_terrain_type_class->texture );
						}
					}

					number_of_points = polygon->number_of_points;

					{

						if ( outcode_3d_terrain_byte_polygon ( number_of_points, terrain_3d_sector_point_byte_references, &terrain_3d_face_outcode ) )
						{

							if ( terrain_3d_face_outcode )
							{

								current_terrain_type_class->render_byte_clipped ( number_of_points );
							}
							else
							{

								current_terrain_type_class->render_byte_unclipped ( number_of_points );
							}
						}

						terrain_3d_sector_point_byte_references += number_of_points;

						polygon++;
					}
				}
			}
			else
			{

				terrain_3d_sector_point_word_references = current_terrain_sector->point_word_references;

				for ( count = current_terrain_sector->number_of_polygons; count > 0; count-- )
				{

					int
						number_of_points;

					if ( polygon->surface_change )
					{

						surface += polygon->surface_change;

						draw_terrain_3d_buffered_polygons ();

						current_terrain_type = surface->surface_id;

						current_terrain_type_class = &terrain_type_information[current_terrain_type];

						if ( terrain_2d_map_textured )
						{

							set_d3d_texture ( 0, current_terrain_type_class->texture );
						}
					}

					number_of_points = polygon->number_of_points;

					{

						if ( outcode_3d_terrain_word_polygon ( number_of_points, terrain_3d_sector_point_word_references, &terrain_3d_face_outcode ) )
						{

							if ( terrain_3d_face_outcode )
							{

								current_terrain_type_class->render_word_clipped ( number_of_points );
							}
							else
							{

								current_terrain_type_class->render_word_unclipped ( number_of_points );
							}
						}

						terrain_3d_sector_point_word_references += number_of_points;

						polygon++;
					}
				}
			}
		}
	}

	//
	// Restore the fog
	//

	reinstate_d3d_fog ();

	//
	// Turn Z buffering back on again
	//

	set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_2d_terrain_contour_mipmaps ( void )
{

	int
		count,
		x,
		y,
		width,
		height,
		parent_width,
		parent_height;

	float
		*parent_data,
		*data,
		min_value;

	//
	// Assess the number of mipmaps
	//

	width = terrain_3d_simple_elevation_width - 1;

	height = terrain_3d_simple_elevation_height - 1;

	min_value = min ( width, height );

	contour_map_number_of_mipmaps = 0;

	while ( min_value == ( ( int ) min_value ) )
	{

		contour_map_number_of_mipmaps += 1;

		min_value /= 2;
	}

	contour_map_number_of_mipmaps = bound ( contour_map_number_of_mipmaps, 0, 12 );

	ASSERT ( contour_map_number_of_mipmaps );

	contour_map_mipmaps = ( float * * ) safe_malloc ( sizeof ( float * ) * contour_map_number_of_mipmaps );

	for ( count = 0; count < contour_map_number_of_mipmaps; count++ )
	{

		parent_width = width;
		parent_height = height;

		width /= 2;
		height /= 2;

		parent_width++;
		parent_height++;

		width++;
		height++;

		contour_map_mipmaps[count] = ( float * ) safe_malloc ( sizeof ( float ) * ( width * height ) );

		data = contour_map_mipmaps[count];

		if ( count == 0 )
		{

			parent_data = terrain_3d_simple_elevation_grid;
		}
		else
		{

			parent_data = contour_map_mipmaps[count-1];
		}

		for ( y = 0; y < height; y++ )
		{

			for ( x = 0; x < width; x++ )
			{

				int
					x_av,
					y_av,
					total;

				float
					average;

				total = 0;

				average = 0;

				for ( y_av = -1; y_av <= 1; y_av++ )
				{

					if ( ( ( ( y * 2 ) + y_av ) >= 0 ) && ( ( ( y * 2 ) + y_av ) < parent_height ) )
					{
	
						for ( x_av = -1; x_av <= 1; x_av++ )
						{
	
							if ( ( ( ( x * 2 ) + x_av ) >= 0 ) && ( ( ( x * 2 ) + x_av ) < parent_width ) )
							{

								if ( ( x_av == 0 ) && ( y_av == 0 ) )
								{
	
									average += 4 * ( parent_data[(y*2+y_av)*parent_width+(x*2+x_av)] );

									total += 4;
								}
								else
								{
	
									average += parent_data[(y*2+y_av)*parent_width+(x*2+x_av)];

									total++;
								}
							}
						}
					}
				}

				average /= total;

				data[y*width+x] = average;
			}
		}

		parent_width--;
		parent_height--;

		width--;
		height--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_terrain_contour_colour ( int flag )
{
#if 0   // arneh - unused code with new map
	if (command_line_campaign_map != 0)
		return;

	ASSERT ( ( terrain_2d_contour_colours ) && ( terrain_2d_contour_intensities ) );

	if ( flag )
	{

		terrain_2d_current_contour_colours = terrain_2d_contour_colours;
	}
	else
	{

		terrain_2d_current_contour_colours = terrain_2d_contour_intensities;
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_terrain_contour_heights ( int number_of_heights, float *heights )
{
	terrain_2d_contour_heights = contour_heights;

#if 0  // arneh - unused code with new map
	ASSERT ( number_of_heights );
	ASSERT ( heights );

	if ( terrain_2d_contour_heights && terrain_2d_contour_heights != contour_heights)
	{
		safe_free ( terrain_2d_contour_heights );

		terrain_2d_contour_heights = NULL;
	}

	if (command_line_campaign_map != 0)
		terrain_2d_contour_heights = contour_heights;
	else
	{
		terrain_2d_contour_heights = safe_malloc ( sizeof ( float ) * number_of_heights );
	
		memcpy ( terrain_2d_contour_heights, heights, ( sizeof ( float ) * number_of_heights ) );
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_2d_terrain ( const char *path )
{

	char
		node_file[1024],
		path_file[1024];

	//
	// First unload the previous terrain data if it exists
	//

	unload_2d_terrain ();

	//
	// Load the rivers
	//

	sprintf ( node_file, "%s\\route\\rivers.nde", path );
	sprintf ( path_file, "%s\\route\\rivers.wp", path );

	if ( file_exist ( node_file ) )
	{

		load_2d_terrain_contour_river_data ( node_file, path_file );
	}
	else
	{

		sprintf ( node_file, "%s\\route\\rivdata.nde", path );
		sprintf ( path_file, "%s\\route\\rivdata.wp", path );

//VJ for loading homemade maps without rivers 030405
    	if ( file_exist ( node_file ) )
		   load_2d_terrain_contour_river_data ( node_file, path_file );
	}

	//
	// Load the roads
	//

	sprintf ( node_file, "%s\\route\\roads.nde", path );
	sprintf ( path_file, "%s\\route\\roads.wp", path );

	if ( file_exist ( node_file ) )
	{

		load_2d_terrain_contour_road_data ( node_file, path_file );
	}
	else
	{

		sprintf ( node_file, "%s\\route\\roaddata.nde", path );
		sprintf ( path_file, "%s\\route\\roaddata.wp", path );

//VJ for loading homemade maps without roads 030405
    	if ( file_exist ( node_file ) )
    		load_2d_terrain_contour_road_data ( node_file, path_file );
	}

	//
	// Load the country boundaries
	//

	sprintf ( node_file, "%s\\route\\boundary.nde", path );
	sprintf ( path_file, "%s\\route\\boundary.wp", path );

	load_2d_terrain_contour_boundary_data ( node_file, path_file );

	//
	// Load the lakes
	//

	sprintf ( node_file, "%s\\route\\lakes.ply", path );

	if ( file_exist ( node_file ) )
	{

		load_contour_map_lakes ( node_file );
	}

	//
	// Load the citybases
	//

	sprintf ( node_file, "%s\\route\\citybase.ply", path );

	if ( file_exist ( node_file ) )
	{

		load_contour_map_citybases ( node_file );
	}

	//
	// Load the contour colours
	//

	sprintf ( node_file, "%s\\terrain\\2dmapcol.psd", path );

	if ( file_exist ( node_file ) )
	{
	
		load_contour_map_colours ( node_file );
	}

	//
	// Load gridpost elevation map
	//

	initialise_terrain_simple_elevation ();

	sprintf ( node_file, "%s\\terrain\\terrain.sim", path );

	if ( !load_terrain_simple_elevation ( node_file ) )
	{

//		generate_terrain_simple_elevation ( 512.0 );
// Vadim 051120 We need higher resolution 2D map for fjords and such.
// it will only work if the original file is absent though.
		generate_terrain_simple_elevation ( 256.0 );

		save_terrain_simple_elevation ( node_file );
	}

	//
	// Generate the gridpost mipmaps
	//

	generate_2d_terrain_contour_mipmaps ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unload_2d_terrain ( void )
{

	//
	// Unload the lakes
	//

	number_of_contour_lakes = 0;

	if ( contour_lake_vertices )
	{

		safe_free ( contour_lake_vertices );

		contour_lake_vertices = NULL;
	}

	if ( contour_lakes )
	{

		safe_free ( contour_lakes );

		contour_lakes = NULL;
	}

	//
	// Unload the citybases
	//

	number_of_contour_citybases = 0;

	if ( contour_citybase_vertices )
	{

		safe_free ( contour_citybase_vertices );

		contour_citybase_vertices = NULL;
	}

	if ( contour_citybases )
	{

		safe_free ( contour_citybases );

		contour_citybases = NULL;
	}

	//
	// Unload the contour map colours
	//

	//
	// No memory is allocated for colours
	//

	//
	// Unload contour road data
	//

	contour_map_number_of_road_nodes = 0;

	contour_map_number_of_road_paths = 0;

	if ( contour_map_road_nodes )
	{

		safe_free ( contour_map_road_nodes );

		contour_map_road_nodes = NULL;
	}

	if ( contour_map_road_paths )
	{

		safe_free ( contour_map_road_paths );

		contour_map_road_paths = NULL;
	}

	if ( contour_map_road_path_positions )
	{
		
		safe_free ( contour_map_road_path_positions );

		contour_map_road_path_positions = NULL;
	}

	//
	// Unload contour river data
	//

	contour_map_number_of_river_nodes = 0;

	contour_map_number_of_river_paths = 0;

	if ( contour_map_river_nodes )
	{

		safe_free ( contour_map_river_nodes );

		contour_map_river_nodes = NULL;
	}

	if ( contour_map_river_paths )
	{

		safe_free ( contour_map_river_paths );

		contour_map_river_paths = NULL;
	}

	if ( contour_map_river_path_positions )
	{

		safe_free ( contour_map_river_path_positions );

		contour_map_river_path_positions = NULL;
	}

	//
	// Unload contour boundary data
	//

	contour_map_number_of_boundary_nodes = 0;

	contour_map_number_of_boundary_paths = 0;

	if ( contour_map_boundary_nodes )
	{

		safe_free ( contour_map_boundary_nodes );

		contour_map_boundary_nodes = NULL;
	}

	if ( contour_map_boundary_paths )
	{

		safe_free ( contour_map_boundary_paths );

		contour_map_boundary_paths = NULL;
	}

	if ( contour_map_boundary_path_positions )
	{
		
		safe_free ( contour_map_boundary_path_positions );

		contour_map_boundary_path_positions = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int load_2d_terrain_contour_river_data ( char *nodes_filename, char *path_filename )
{

	FILE
		*fp;

	int
		total,
		count;

	vec3d
		*current_position;

	//
	// Read in the river nodes
	//

	// JB 030311 Enable running out of separate directories
	fp = safe_fopen ( nodes_filename, "rb" );

	if ( !fp )
	{

		return ( FALSE );
	}

	fread ( &contour_map_number_of_river_nodes, sizeof ( int ), 1, fp );

	contour_map_river_nodes = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * contour_map_number_of_river_nodes );

	fread ( contour_map_river_nodes, sizeof ( vec3d ), contour_map_number_of_river_nodes, fp );

	safe_fclose ( fp );

	//
	// Read in the river paths
	//

	fp = safe_fopen ( path_filename, "rb" );

	fread ( &contour_map_number_of_river_paths, sizeof ( int ), 1, fp );

	contour_map_river_paths = ( contour_path * ) safe_malloc ( sizeof ( contour_path ) * contour_map_number_of_river_paths );

	//
	// Process the paths
	//

	total = 0;

	for ( count = 0; count < contour_map_number_of_river_paths; count++ )
	{

		fread ( &contour_map_river_paths[count].from, sizeof ( int ), 1, fp );
		fread ( &contour_map_river_paths[count].to, sizeof ( int ), 1, fp );
		fread ( &contour_map_river_paths[count].type, sizeof ( int ), 1, fp );
		fread ( &contour_map_river_paths[count].count, sizeof ( int ), 1, fp );

		total += contour_map_river_paths[count].count;

		fseek ( fp, ( contour_map_river_paths[count].count * sizeof ( vec3d ) ), SEEK_CUR );
	}

	fseek ( fp, 4, SEEK_SET );

	contour_map_river_path_positions = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * total );

	current_position = contour_map_river_path_positions;

	for ( count = 0; count < contour_map_number_of_river_paths; count++ )
	{

		fread ( &contour_map_river_paths[count].from, sizeof ( int ), 1, fp );
		fread ( &contour_map_river_paths[count].to, sizeof ( int ), 1, fp );
		fread ( &contour_map_river_paths[count].type, sizeof ( int ), 1, fp );
		fread ( &contour_map_river_paths[count].count, sizeof ( int ), 1, fp );

		contour_map_river_paths[count].from = bound ( contour_map_river_paths[count].from, 0, contour_map_number_of_river_nodes );
		contour_map_river_paths[count].to = bound ( contour_map_river_paths[count].to, 0, contour_map_number_of_river_nodes );

		contour_map_river_paths[count].points = current_position;

		fread ( current_position, sizeof ( vec3d ), contour_map_river_paths[count].count, fp );

		current_position += contour_map_river_paths[count].count;
	}

	safe_fclose ( fp );

	//
	// Go through setting all the node bounds
	//

	set_node_database_extents ( contour_map_number_of_river_paths, contour_map_river_paths, contour_map_river_nodes );

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int load_2d_terrain_contour_road_data ( char *nodes_filename, char *path_filename )
{

	FILE
		*fp;

	int
		total,
		count;

	vec3d
		*current_position;

	//
	// Read in the nodes
	//

	// JB 030311 Enable running out of separate directories
	fp = safe_fopen ( nodes_filename, "rb" );

	if ( !fp )
	{

		return ( FALSE );
	}

	fread ( &contour_map_number_of_road_nodes, sizeof ( int ), 1, fp );

	contour_map_road_nodes = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * contour_map_number_of_road_nodes );

	fread ( contour_map_road_nodes, sizeof ( vec3d ), contour_map_number_of_road_nodes, fp );

	safe_fclose ( fp );

	//
	// Read in the paths
	//

	fp = safe_fopen ( path_filename, "rb" );

	fread ( &contour_map_number_of_road_paths, sizeof ( int ), 1, fp );

	contour_map_road_paths = ( contour_path * ) safe_malloc ( sizeof ( contour_path ) * contour_map_number_of_road_paths );

	//
	// Process the paths
	//

	total = 0;

	for ( count = 0; count < contour_map_number_of_road_paths; count++ )
	{

		fread ( &contour_map_road_paths[count].from, sizeof ( int ), 1, fp );
		fread ( &contour_map_road_paths[count].to, sizeof ( int ), 1, fp );
		fread ( &contour_map_road_paths[count].type, sizeof ( int ), 1, fp );
		fread ( &contour_map_road_paths[count].count, sizeof ( int ), 1, fp );

		total += contour_map_road_paths[count].count;

		fseek ( fp, ( contour_map_road_paths[count].count * sizeof ( vec3d ) ), SEEK_CUR );
	}

	fseek ( fp, 4, SEEK_SET );

	contour_map_road_path_positions = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * total );

	current_position = contour_map_road_path_positions;

	for ( count = 0; count < contour_map_number_of_road_paths; count++ )
	{

		fread ( &contour_map_road_paths[count].from, sizeof ( int ), 1, fp );
		fread ( &contour_map_road_paths[count].to, sizeof ( int ), 1, fp );
		fread ( &contour_map_road_paths[count].type, sizeof ( int ), 1, fp );
		fread ( &contour_map_road_paths[count].count, sizeof ( int ), 1, fp );

		contour_map_road_paths[count].from = bound ( contour_map_road_paths[count].from, 0, contour_map_number_of_road_nodes );
		contour_map_road_paths[count].to = bound ( contour_map_road_paths[count].to, 0, contour_map_number_of_road_nodes );

		contour_map_road_paths[count].points = current_position;

		fread ( current_position, sizeof ( vec3d ), contour_map_road_paths[count].count, fp );

		current_position += contour_map_road_paths[count].count;
	}

	safe_fclose ( fp );

	//
	// Go through setting all the node bounds
	//

	set_node_database_extents ( contour_map_number_of_road_paths, contour_map_road_paths, contour_map_road_nodes );

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int load_2d_terrain_contour_boundary_data ( char *nodes_filename, char *path_filename )
{

	FILE
		*fp;

	int
		total,
		count;

	vec3d
		*current_position;

	//
	// Read in the nodes
	//

	fp = fopen ( nodes_filename, "rb" );

	if ( !fp )
	{

		return ( FALSE );
	}

	fread ( &contour_map_number_of_boundary_nodes, sizeof ( int ), 1, fp );

	contour_map_boundary_nodes = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * contour_map_number_of_boundary_nodes );

	fread ( contour_map_boundary_nodes, sizeof ( vec3d ), contour_map_number_of_boundary_nodes, fp );

	safe_fclose ( fp );

	//
	// Read in the paths
	//

	fp = safe_fopen ( path_filename, "rb" );

	fread ( &contour_map_number_of_boundary_paths, sizeof ( int ), 1, fp );

	contour_map_boundary_paths = ( contour_path * ) safe_malloc ( sizeof ( contour_path ) * contour_map_number_of_boundary_paths );

	//
	// Process the paths
	//

	total = 0;

	for ( count = 0; count < contour_map_number_of_boundary_paths; count++ )
	{

		fread ( &contour_map_boundary_paths[count].from, sizeof ( int ), 1, fp );
		fread ( &contour_map_boundary_paths[count].to, sizeof ( int ), 1, fp );
		fread ( &contour_map_boundary_paths[count].type, sizeof ( int ), 1, fp );
		fread ( &contour_map_boundary_paths[count].count, sizeof ( int ), 1, fp );

		total += contour_map_boundary_paths[count].count;

		fseek ( fp, ( contour_map_boundary_paths[count].count * sizeof ( vec3d ) ), SEEK_CUR );
	}

	fseek ( fp, 4, SEEK_SET );

	contour_map_boundary_path_positions = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * total );

	current_position = contour_map_boundary_path_positions;

	for ( count = 0; count < contour_map_number_of_boundary_paths; count++ )
	{

		fread ( &contour_map_boundary_paths[count].from, sizeof ( int ), 1, fp );
		fread ( &contour_map_boundary_paths[count].to, sizeof ( int ), 1, fp );
		fread ( &contour_map_boundary_paths[count].type, sizeof ( int ), 1, fp );
		fread ( &contour_map_boundary_paths[count].count, sizeof ( int ), 1, fp );

		contour_map_boundary_paths[count].from = bound ( contour_map_boundary_paths[count].from, 0, contour_map_number_of_boundary_nodes );
		contour_map_boundary_paths[count].to = bound ( contour_map_boundary_paths[count].to, 0, contour_map_number_of_boundary_nodes );

		contour_map_boundary_paths[count].points = current_position;

		fread ( current_position, sizeof ( vec3d ), contour_map_boundary_paths[count].count, fp );

		current_position += contour_map_boundary_paths[count].count;
	}

	safe_fclose ( fp );

	//
	// Go through setting all the node bounds
	//

	set_node_database_extents ( contour_map_number_of_boundary_paths, contour_map_boundary_paths, contour_map_boundary_nodes );

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_node_database_extents ( int number_of_paths, contour_path *paths, vec3d *nodes )
{

	int
		path;

	for ( path = 0; path < number_of_paths; path++ )
	{

		int
			count;

		float
			xmin,
			xmax,
			zmin,
			zmax;

		xmin = min ( nodes[ paths[path].from ].x, nodes[ paths[path].to ].x );
		xmax = max ( nodes[ paths[path].from ].x, nodes[ paths[path].to ].x );
		zmin = min ( nodes[ paths[path].from ].z, nodes[ paths[path].to ].z );
		zmax = max ( nodes[ paths[path].from ].z, nodes[ paths[path].to ].z );

		for ( count = 0; count < paths[path].count; count++ )
		{

			xmin = min ( xmin, paths[path].points[count].x );
			xmax = max ( xmax, paths[path].points[count].x );
			zmin = min ( zmin, paths[path].points[count].z );
			zmax = max ( zmax, paths[path].points[count].z );
		}

		paths[path].xmin = xmin;
		paths[path].xmax = xmax;
		paths[path].zmin = zmin;
		paths[path].zmax = zmax;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_lake_database_extents ( int number_of_triangle_sets, contour_lake *lakes )
{

	int
		lake;

	for ( lake = 0; lake < number_of_triangle_sets; lake++ )
	{

		int
			count;

		float
			xmin,
			xmax,
			zmin,
			zmax;

		xmin = lakes[lake].triangle_points[0].x;
		xmax = lakes[lake].triangle_points[0].x;
		zmin = lakes[lake].triangle_points[0].z;
		zmax = lakes[lake].triangle_points[0].z;

		for ( count = 0; count < lakes[lake].number_of_triangles; count++ )
		{

			xmin = min ( xmin, lakes[lake].triangle_points[count*3+0].x );
			xmax = max ( xmax, lakes[lake].triangle_points[count*3+0].x );
			zmin = min ( zmin, lakes[lake].triangle_points[count*3+0].z );
			zmax = max ( zmax, lakes[lake].triangle_points[count*3+0].z );

			xmin = min ( xmin, lakes[lake].triangle_points[count*3+1].x );
			xmax = max ( xmax, lakes[lake].triangle_points[count*3+1].x );
			zmin = min ( zmin, lakes[lake].triangle_points[count*3+1].z );
			zmax = max ( zmax, lakes[lake].triangle_points[count*3+1].z );

			xmin = min ( xmin, lakes[lake].triangle_points[count*3+2].x );
			xmax = max ( xmax, lakes[lake].triangle_points[count*3+2].x );
			zmin = min ( zmin, lakes[lake].triangle_points[count*3+2].z );
			zmax = max ( zmax, lakes[lake].triangle_points[count*3+2].z );
		}

		lakes[lake].xmin = xmin;
		lakes[lake].xmax = xmax;
		lakes[lake].zmin = zmin;
		lakes[lake].zmax = zmax;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_contour_map_colours ( const char *filename )
{
	if ( terrain_2d_contour_colours && terrain_2d_contour_colours != contour_colours)
	{
		safe_free ( terrain_2d_contour_colours );

		terrain_2d_contour_colours = NULL;
	}

	if ( terrain_2d_contour_intensities )
	{
		safe_free ( terrain_2d_contour_intensities );

		terrain_2d_contour_intensities = NULL;
	}

//	if (command_line_campaign_map != 0)
	{
		if (command_line_campaign_map_palette == 1)
			terrain_2d_contour_colours = contour_colours;
		else
			terrain_2d_contour_colours = contour_paper_colours;
	}
#if 0   // arneh - unused code with new map
	else
	{
		int
			count,
			width,
			height,
			channels;
	
		char
			*data;

		data = load_psd_file ( filename, &width, &height, &channels );
	
		ASSERT ( channels == 3 );
	
		terrain_2d_contour_colours = safe_malloc ( sizeof ( rgb_colour ) * height );
	
		terrain_2d_contour_intensities = safe_malloc ( sizeof ( rgb_colour ) * height );
	
		terrain_2d_contour_intensities = safe_malloc(sizeof(contour_colours));
	
		for ( count = 0; count < height; count++ )
		{
	
			float
				intensity;

			terrain_2d_contour_colours[count].r = data[ width * channels * count + 0];
			terrain_2d_contour_colours[count].g = data[ width * channels * count + 1];
			terrain_2d_contour_colours[count].b = data[ width * channels * count + 2];

			intensity = ( float ) terrain_2d_contour_colours[count].r * 0.30;
			intensity += ( float ) terrain_2d_contour_colours[count].g * 0.59;
			intensity += ( float ) terrain_2d_contour_colours[count].b * 0.11;
	
			terrain_2d_contour_intensities[count].r = intensity;
			terrain_2d_contour_intensities[count].g = intensity;
			terrain_2d_contour_intensities[count].b = intensity;
		}
	
		safe_free ( data );
	}
#endif
	terrain_2d_current_contour_colours = terrain_2d_contour_colours;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_contour_map_lakes ( char *filename )
{

	FILE
		*fp;

	int
		number_of_lake_triangles,
		total_triangles,
		count;

	vec3d
		*vertices;

	fp = safe_fopen ( filename, "rb" );

	//
	// Assess the number of lakes
	//

	number_of_contour_lakes = 0;

	total_triangles = 0;

	fread ( &number_of_contour_lakes, sizeof ( int ), 1, fp );

	for ( count = 0; count < number_of_contour_lakes; count++ )
	{

		fread ( &number_of_lake_triangles, sizeof ( int ), 1, fp );

		total_triangles += number_of_lake_triangles;

		fseek ( fp, sizeof ( vec3d ) * 3 * number_of_lake_triangles, SEEK_CUR );
	}

	//
	// Now read in the data properly
	//

	contour_lake_vertices = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * 3 * total_triangles );

	contour_lakes = ( contour_lake * ) safe_malloc ( sizeof ( contour_lake ) * number_of_contour_lakes );

	fseek ( fp, 4, SEEK_SET );

	vertices = contour_lake_vertices;

	for ( count = 0; count < number_of_contour_lakes; count++ )
	{

		int
			point;

		fread ( &number_of_lake_triangles, sizeof ( int ), 1, fp );
	
		fread ( vertices, sizeof ( vec3d ) * 3, number_of_lake_triangles, fp );

		contour_lakes[count].number_of_triangles = number_of_lake_triangles;

		contour_lakes[count].triangle_points = vertices;

		for ( point = 0; point < number_of_lake_triangles; point++ )
		{

			vertices[point*3+0].z = terrain_3d_max_map_z - vertices[point*3+0].z;
			vertices[point*3+1].z = terrain_3d_max_map_z - vertices[point*3+1].z;
			vertices[point*3+2].z = terrain_3d_max_map_z - vertices[point*3+2].z;
		}

		vertices += ( number_of_lake_triangles * 3 );
	}

	safe_fclose ( fp );

	//
	// Generate a bounding box round all the lakes
	//

	set_lake_database_extents ( number_of_contour_lakes, contour_lakes );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_contour_map_citybases ( char *filename )
{

	FILE
		*fp;

	int
		number_of_triangles,
		total_triangles,
		count;

	vec3d
		*vertices;

	fp = safe_fopen ( filename, "rb" );

	number_of_contour_citybases = 0;

	total_triangles = 0;

	fread ( &number_of_contour_citybases, sizeof ( int ), 1, fp );

	if ( number_of_contour_citybases == 0 )
	{

		safe_fclose ( fp );

		return;
	}

	for ( count = 0; count < number_of_contour_citybases; count++ )
	{

		fread ( &number_of_triangles, sizeof ( int ), 1, fp );

		total_triangles += number_of_triangles;

		fseek ( fp, sizeof ( vec3d ) * 3 * number_of_triangles, SEEK_CUR );
	}

	//
	// Now read in the data properly
	//

	contour_citybase_vertices = ( vec3d * ) safe_malloc ( sizeof ( vec3d ) * 3 * total_triangles );

	contour_citybases = ( contour_lake * ) safe_malloc ( sizeof ( contour_lake ) * number_of_contour_citybases );

	fseek ( fp, 4, SEEK_SET );

	vertices = contour_citybase_vertices;

	for ( count = 0; count < number_of_contour_citybases; count++ )
	{

		int
			point;

		fread ( &number_of_triangles, sizeof ( int ), 1, fp );
	
		fread ( vertices, sizeof ( vec3d ) * 3, number_of_triangles, fp );

		contour_citybases[count].number_of_triangles = number_of_triangles;

		contour_citybases[count].triangle_points = vertices;

		for ( point = 0; point < number_of_triangles; point++ )
		{

			vertices[point*3+0].z = terrain_3d_max_map_z - vertices[point*3+0].z;
			vertices[point*3+1].z = terrain_3d_max_map_z - vertices[point*3+1].z;
			vertices[point*3+2].z = terrain_3d_max_map_z - vertices[point*3+2].z;
		}

		vertices += ( number_of_triangles * 3 );
	}

	safe_fclose ( fp );

	set_lake_database_extents ( number_of_contour_citybases, contour_citybases );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float check_coastal_river_intersection ( float x1, float z1, float x2, float z2 )
{

	int
		count;

	float
		dx,
		dy,
		t;

	vec2d
		pt1,
		pt2,
		pt3,
		pt4,
		intercept_point;

	//
	// Go through all the coastal rivers checking the lines against this edge
	//

	pt1.x = x1;
	pt1.y = z1;

	pt2.x = x2;
	pt2.y = z2;

	dx = fabs ( x2 - x1 );
	dy = fabs ( z2 - z1 );

	t = -1;

	for ( count = 0; count < contour_map_number_of_river_paths; count++ )
	{

		if ( contour_map_river_paths[count].type == TEMP_TERRAIN_TYPE_COASTAL_RIVER )
		{

			if ( contour_map_river_paths[count].count == 0 )
			{

				pt3.x = contour_map_river_nodes[ contour_map_river_paths[count].from ].x;
				pt3.y = contour_map_river_nodes[ contour_map_river_paths[count].from ].z;

				pt4.x = contour_map_river_nodes[ contour_map_river_paths[count].to ].x;
				pt4.y = contour_map_river_nodes[ contour_map_river_paths[count].to ].z;

				if ( line_line_2d_intercept ( &pt1, &pt2, &pt3, &pt4, &intercept_point ) )
				{

					if ( dx > dy )
					{

						t = ( intercept_point.x - pt1.x ) / ( pt2.x - pt1.x );
					}
					else
					{

						t = ( intercept_point.y - pt1.y ) / ( pt2.y - pt1.y );
					}

					return ( t );
				}
			}
			else
			{
		
				vec3d
					*sub_positions;
	
				int
					sub_count;
	
				sub_positions = contour_map_river_paths[count].points;

				sub_count = 0;
	
				pt3.x = contour_map_river_nodes[ contour_map_river_paths[count].from ].x;
				pt3.y = contour_map_river_nodes[ contour_map_river_paths[count].from ].z;

				pt4.x = sub_positions[0].x;
				pt4.y = sub_positions[0].z;
		
				if ( line_line_2d_intercept ( &pt1, &pt2, &pt3, &pt4, &intercept_point ) )
				{

					if ( dx > dy )
					{

						t = ( intercept_point.x - pt1.x ) / ( pt2.x - pt1.x );
					}
					else
					{

						t = ( intercept_point.y - pt1.y ) / ( pt2.y - pt1.y );
					}

					return ( t );
				}


				for ( sub_count = 0; sub_count < ( contour_map_river_paths[count].count - 1 ); sub_count++ )
				{

					pt3.x = sub_positions[sub_count].x;
					pt3.y = sub_positions[sub_count].z;

					pt4.x = sub_positions[sub_count+1].x;
					pt4.y = sub_positions[sub_count+1].z;

					if ( line_line_2d_intercept ( &pt1, &pt2, &pt3, &pt4, &intercept_point ) )
					{
	
						if ( dx > dy )
						{
	
							t = ( intercept_point.x - pt1.x ) / ( pt2.x - pt1.x );
						}
						else
						{
	
							t = ( intercept_point.y - pt1.y ) / ( pt2.y - pt1.y );
						}
	
						return ( t );
					}
				}
		

				pt3.x = sub_positions[sub_count].x;
				pt3.y = sub_positions[sub_count].z;

				pt4.x = contour_map_river_nodes[ contour_map_river_paths[count].to ].x;
				pt4.y = contour_map_river_nodes[ contour_map_river_paths[count].to ].z;

				if ( line_line_2d_intercept ( &pt1, &pt2, &pt3, &pt4, &intercept_point ) )
				{

					if ( dx > dy )
					{

						t = ( intercept_point.x - pt1.x ) / ( pt2.x - pt1.x );
					}
					else
					{

						t = ( intercept_point.y - pt1.y ) / ( pt2.y - pt1.y );
					}

					return ( t );
				}
			}
		}
	}

	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_shaded_terrain_contour_map ( void )
{
	int
		current_x,
		current_z,
		minimum_x,
		minimum_z,
		maximum_x,
		maximum_z,
		x_count,
		z_count,
		x_total,
		z_total,
		x_increment,
		z_increment,
		terrain_height_data_width,
		terrain_height_data_height;

	float
		i1,
		i2,
		j1,
		j2,
		screen_i_increment,
		screen_j_increment,
		mipmap_distance_factor,
		terrain_height_data_x_distance,
		terrain_height_data_z_distance,
		contour_shading_zoom_adjustment,
		*terrain_height_data;

	float
		world_width,
		screen_width,
		ratio;

	unsigned int
		mipmap_mask;

	int
		count,
		mipmap_index,
		mipmap_level,
		new_total;

	vertex
		vertices[9];

	real_colour
		river_colour,
		road_colour,
		boundary_colour;

	river_colour.red = 90;
	river_colour.green = 120;
	river_colour.blue = 180;
	river_colour.alpha = 192;

	road_colour.red = 0;
	road_colour.green = 0;
	road_colour.blue = 0;
	road_colour.alpha = 255;

	boundary_colour.red = 200;
	boundary_colour.green = 20;
	boundary_colour.blue = 0;
	boundary_colour.alpha = 255;

	//
	// Set up the rendering states
	//

	set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );

	set_d3d_int_state ( D3DRENDERSTATE_CULLMODE, D3DCULL_NONE );
	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, FALSE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture ( 0, NULL );

	set_d3d_fog_face_intensity ( 255 );

	contour_height_difference_reciprocals = ( float * ) safe_malloc ( number_of_contour_height_lines * sizeof ( float ) );

	for ( count = 0; count < ( number_of_contour_height_lines - 1 ); count++ )
	{

		contour_height_difference_reciprocals[count] = 1.0 / ( terrain_2d_contour_heights[count+1] - terrain_2d_contour_heights[count] );
	}

	d3d_in_order_rendering = TRUE;

	//
	// Set up the viewport
	//

	set_viewport ( terrain_2d_map_screen_xmin, terrain_2d_map_screen_ymin, terrain_2d_map_screen_xmax, terrain_2d_map_screen_ymax );

	//
	// Set up the bounds to render between
	//

	minimum_x = terrain_2d_map_world_xmin / terrain_3d_simple_elevation_x_grid_size;
	maximum_x = terrain_2d_map_world_xmax / terrain_3d_simple_elevation_x_grid_size;
	minimum_z = terrain_2d_map_world_zmin / terrain_3d_simple_elevation_z_grid_size;
	maximum_z = terrain_2d_map_world_zmax / terrain_3d_simple_elevation_z_grid_size;

	minimum_x = bound ( minimum_x, 0, ( terrain_3d_simple_elevation_width - 1 ) );
	minimum_z = bound ( minimum_z, 0, ( terrain_3d_simple_elevation_height - 1 ) );
	maximum_x = bound ( maximum_x, 0, ( terrain_3d_simple_elevation_width - 1 ) );
	maximum_z = bound ( maximum_z, 0, ( terrain_3d_simple_elevation_height - 1 ) );

	x_total = abs ( maximum_x - minimum_x ) + 1;
	z_total = abs ( maximum_z - minimum_z ) + 1;

	if ( maximum_x > minimum_x )	x_increment = 1;
	else									x_increment = -1;

	if ( maximum_z > minimum_z )	z_increment = 1;
	else									z_increment = -1;

	//
	// Find out how many metres per pixel
	//

	{
		int map_resolution = (command_line_campaign_map == 2) ? 120 : 60;
		
		new_total = x_total;

		screen_width = fabs ( terrain_2d_map_screen_xmax - terrain_2d_map_screen_xmin );

		world_width = fabs ( terrain_2d_map_world_xmax - terrain_2d_map_world_xmin );
		world_width /= terrain_3d_simple_elevation_x_grid_size;

		ratio = world_width;

		mipmap_level = 1;
		mipmap_mask = 0xffffffff;

		mipmap_index = -1;
		terrain_height_data_width = terrain_3d_simple_elevation_width - 1;
		terrain_height_data_height = terrain_3d_simple_elevation_height - 1;

		

		while ( ( ratio > map_resolution ) && ( mipmap_index < ( contour_map_number_of_mipmaps - 1 ) ) && ( mipmap_level < 64 ) )
		{

			mipmap_level *= 2;
			ratio /= 2;
			mipmap_mask <<= 1;

			mipmap_index++;
			terrain_height_data_width /= 2;
			terrain_height_data_height /= 2;
		}

		//
		// Now adjust the increments & starting & ending positions
		//

		mipmap_distance_factor = mipmap_level;

		x_increment *= mipmap_level;
		z_increment *= mipmap_level;

		minimum_x &= mipmap_mask;
		minimum_x -= x_increment;

		maximum_x &= mipmap_mask;
		maximum_x += x_increment;

		minimum_z &= mipmap_mask;
		minimum_z -= z_increment;

		maximum_z &= mipmap_mask;
		maximum_z += z_increment;

		minimum_x /= mipmap_level;
		maximum_x /= mipmap_level;
		x_increment /= mipmap_level;

		minimum_z /= mipmap_level;
		maximum_z /= mipmap_level;
		z_increment /= mipmap_level;

		minimum_x = bound ( minimum_x, 0, ( terrain_height_data_width ) );
		maximum_x = bound ( maximum_x, 0, ( terrain_height_data_width ) );
		minimum_z = bound ( minimum_z, 0, ( terrain_height_data_height ) );
		maximum_z = bound ( maximum_z, 0, ( terrain_height_data_height ) );

		x_total = abs ( maximum_x - minimum_x );
		z_total = abs ( maximum_z - minimum_z );

		//
		// Get the terrain height data pointer
		//

		if ( mipmap_index == -1 )
		{

			terrain_height_data = terrain_3d_simple_elevation_grid;
		}
		else
		{

			terrain_height_data = contour_map_mipmaps[mipmap_index];
		}

		terrain_height_data_x_distance = terrain_3d_simple_elevation_x_grid_size * mipmap_distance_factor;
		terrain_height_data_z_distance = terrain_3d_simple_elevation_z_grid_size * mipmap_distance_factor;

		// this is just an ad-hoc method for getting an adjustment for
		// relief shading at different zoom levels
		contour_shading_zoom_adjustment = 1.0 / (log(terrain_height_data_x_distance / 10.0));
	}

	terrain_height_data_width += 1;
	terrain_height_data_height += 1;

	//
	// Initialise the vertices
	//

	for ( count = 0; count < 9; count++ )
	{
		vertices[count].x = 0.0;
		vertices[count].z = 10;
		vertices[count].q = 0.1;
	}

	//
	// Calculate the screen increments
	//

	i1 = ( minimum_x * terrain_height_data_x_distance ) - terrain_2d_map_world_xcentre;
	j1 = ( minimum_z * terrain_height_data_z_distance ) - terrain_2d_map_world_zcentre;
	i2 = ( ( minimum_x + x_increment ) * terrain_height_data_x_distance ) - terrain_2d_map_world_xcentre;
	j2 = ( ( minimum_z + z_increment ) * terrain_height_data_z_distance ) - terrain_2d_map_world_zcentre;
	
	i1 = ( i1 * terrain_2d_map_screen_xscale ) + terrain_2d_map_screen_xcentre;
	j1 = ( j1 * terrain_2d_map_screen_yscale ) + terrain_2d_map_screen_ycentre;
	i2 = ( i2 * terrain_2d_map_screen_xscale ) + terrain_2d_map_screen_xcentre;
	j2 = ( j2 * terrain_2d_map_screen_yscale ) + terrain_2d_map_screen_ycentre;

	screen_i_increment = i2 - i1;
	screen_j_increment = j2 - j1;

	current_z = minimum_z;

	for ( z_count = 0; z_count < z_total; z_count++ )
	{
#define GET_ELEVATION(x,z) terrain_height_data[(z_indices[z] * terrain_height_data_width) + x_indices[x]]
		float
			i_coordinates[3],
			j_coordinates[3];

		int
			i,
			next_x_valid,
			next_z_valid,
			next_two_z_valid;

		float
			*elevation_grid[4],
			elevation_data[4][4];
	
		int
			z_indices[4],
			x_indices[4];

		for (i = 0; i <4 ; i++)
			elevation_grid[i] = elevation_data[i];

		next_z_valid = z_count < (z_total - 1);
		next_two_z_valid = z_count < (z_total - 2);

		current_x = minimum_x;

		// x and z coordinates we want to get height for
		z_indices[0] = current_z - z_increment;
		x_indices[0] = current_x - x_increment;
		for (i=1; i<4; i++)
		{
			z_indices[i] = z_indices[i-1] + z_increment;
			x_indices[i] = x_indices[i-1] + x_increment;
		}

		// initialize elevation grid
		for (i = 2; i < 4; i++)  // iterate over columns, will be shifted one to left
		{
			elevation_grid[i][1] = GET_ELEVATION(i-1, 1);
			elevation_grid[i][2] = GET_ELEVATION(i-1, 2);

			if (z_count > 0)
				elevation_grid[i][0] = GET_ELEVATION(i-1, 0);
			else  // it is outside, initalize to same as the one below
				elevation_grid[i][0] = elevation_grid[i][1];

			if (next_z_valid)
				elevation_grid[i][3] = GET_ELEVATION(i-1, 3);
			else   // it is outside, initalize to same as the one above
				elevation_grid[i][3] = elevation_grid[i][2];
		}
		// initialize second column (which really is outside view) to same as third
		for (i = 0; i < 4; i++)
			elevation_grid[1][i] = elevation_grid[2][i];

		// get screen coordinates
		i_coordinates[1] = (((x_indices[1] * terrain_height_data_x_distance) - terrain_2d_map_world_xcentre) * terrain_2d_map_screen_xscale) + terrain_2d_map_screen_xcentre;

		j_coordinates[0] = (((z_indices[1] * terrain_height_data_z_distance) - terrain_2d_map_world_zcentre) * terrain_2d_map_screen_yscale) + terrain_2d_map_screen_ycentre;
		j_coordinates[1] = j_coordinates[0] + screen_j_increment;

		x_indices[1] = x_indices[0];

		// fill out the other rows of the height grid
		for ( x_count = 0; x_count < x_total; x_count++ )
		{
			float* next_free_row;

			unsigned char
				outcode_top_left,
				outcode_bottom_right,

				outcode_left,
				outcode_right,
				outcode_top,
				outcode_bottom,
				outcode_whole1,
				outcode_whole2;

			next_x_valid = x_count < (x_total - 2);

			// shift coordinates
			x_indices[0] = x_indices[1];
			for (i=1; i<4; i++)
				x_indices[i] = x_indices[i-1] + x_increment;

			// shift screen coordinates
			i_coordinates[0] = i_coordinates[1];
			i_coordinates[1] = i_coordinates[0] + screen_i_increment;

			// shift one row right
			next_free_row = elevation_grid[0];  // we'll overwrite this one
			elevation_grid[0] = elevation_grid[1];
			elevation_grid[1] = elevation_grid[2];
			elevation_grid[2] = elevation_grid[3];
			elevation_grid[3] = next_free_row;

			// get height values for next column
			if (next_x_valid)
			{
				elevation_grid[3][1] = GET_ELEVATION(3, 1);
				elevation_grid[3][2] = GET_ELEVATION(3, 2);
	
				if (z_count > 0)
					elevation_grid[3][0] = GET_ELEVATION(3, 0);
				else  // it is outside, initalize to same as the one below
					elevation_grid[3][0] = elevation_grid[3][1];

				if (next_z_valid)
					elevation_grid[3][3] = GET_ELEVATION(3, 3);
				else   // it is outside, initalize to same as the one above
					elevation_grid[3][3] = elevation_grid[3][2];
			}
			else  // if we don't have any then copy last column
				for (i=0; i<4; i++)
					elevation_grid[3][i] = elevation_grid[2][i];
#undef GET_ELEVATION

			outcode_top_left = generate_contour_outcode ( i_coordinates[0], j_coordinates[0] );
			outcode_bottom_right = generate_contour_outcode ( i_coordinates[1], j_coordinates[1] );

			outcode_left = outcode_top_left & ( CLIP_LEFT | CLIP_RIGHT );
			outcode_right = outcode_bottom_right & ( CLIP_LEFT | CLIP_RIGHT );
			outcode_top = outcode_top_left & ( CLIP_TOP | CLIP_BOTTOM );
			outcode_bottom = outcode_bottom_right & ( CLIP_TOP | CLIP_BOTTOM );

			outcode_whole1 = outcode_top_left | outcode_bottom_right;
			outcode_whole2 = outcode_top_left & outcode_bottom_right;

			if ( !outcode_whole2 )  // not entire grid outside view
			{
				float
					min_height = FLT_MAX,
					max_height = FLT_MIN;

				int
					contour_start_index,
					contour_end_index;

				min_height = min (elevation_grid[1][1], min_height);
				min_height = min (elevation_grid[1][2], min_height);
				min_height = min (elevation_grid[2][1], min_height);
				min_height = min (elevation_grid[2][2], min_height);

				max_height = max (elevation_grid[1][1], max_height);
				max_height = max (elevation_grid[1][2], max_height);
				max_height = max (elevation_grid[2][1], max_height);
				max_height = max (elevation_grid[2][2], max_height);

				// find index of starting contour
				for ( contour_start_index = 0; contour_start_index < number_of_contour_height_lines; contour_start_index++ )
				{
					if ( min_height <= terrain_2d_contour_heights[contour_start_index] )
					{
						contour_start_index--;

						// found it, now find ending contour
						for ( contour_end_index = contour_start_index; contour_end_index < number_of_contour_height_lines; contour_end_index++ )
							if ( max_height < terrain_2d_contour_heights[contour_end_index] )
							{
								contour_end_index--;
								break;
							}

						break;
					}
				}

				// render quad
				vertices[0].i = i_coordinates[0]; vertices[0].j = j_coordinates[0]; vertices[0].y = elevation_grid[1][1];
				vertices[1].i = i_coordinates[1]; vertices[1].j = j_coordinates[0]; vertices[1].y = elevation_grid[2][1];
				vertices[2].i = i_coordinates[0]; vertices[2].j = j_coordinates[1]; vertices[2].y = elevation_grid[1][2];
				vertices[3].i = i_coordinates[1]; vertices[3].j = j_coordinates[1]; vertices[3].y = elevation_grid[2][2];

				// add shading
				vertices[0].x = contour_shading_zoom_adjustment * (2 * (elevation_grid[1][0] - elevation_grid[1][2]) + (elevation_grid[0][1] - elevation_grid[2][1]));
				vertices[1].x = contour_shading_zoom_adjustment * (2 * (elevation_grid[2][0] - elevation_grid[2][2]) + (elevation_grid[1][1] - elevation_grid[3][1]));
				vertices[2].x = contour_shading_zoom_adjustment * (2 * (elevation_grid[1][1] - elevation_grid[1][3]) + (elevation_grid[0][2] - elevation_grid[2][2]));
				vertices[3].x = contour_shading_zoom_adjustment * (2 * (elevation_grid[2][1] - elevation_grid[2][3]) + (elevation_grid[1][2] - elevation_grid[3][2]));

				vertices[0].outcode = outcode_top_left;
				vertices[1].outcode = outcode_top | outcode_right;
				vertices[2].outcode = outcode_left | outcode_bottom;
				vertices[3].outcode = outcode_bottom_right;

				render_contour_terrain_quad ( vertices, contour_start_index, contour_end_index );
			}

			current_x += x_increment;
		}

		current_z += z_increment;
	}

	//
	// Render the features
	//

	//
	// Rivers
	//

	render_contour_node_database ( contour_map_number_of_river_paths, contour_map_river_paths, contour_map_river_nodes, river_colour, mipmap_level );

	//
	// Roads
	//

	render_contour_node_database ( contour_map_number_of_road_paths, contour_map_road_paths, contour_map_road_nodes, road_colour, mipmap_level );

	//
	// Lakes
	//

	{

		real_colour
			lake_colour;

		lake_colour.r = terrain_2d_current_contour_colours[0].r;
		lake_colour.g = terrain_2d_current_contour_colours[0].g;
		lake_colour.b = terrain_2d_current_contour_colours[0].b;
		lake_colour.a = terrain_2d_current_contour_colours[0].a;
	
		render_contour_triangle_database ( number_of_contour_lakes, contour_lakes, lake_colour );
	}

	//
	// Citybases
	//

	{

		real_colour
			citybase_colour;

		citybase_colour.r = 70;
		citybase_colour.g = 70;
		citybase_colour.b = 70;
		citybase_colour.a = 255;
	
		render_contour_triangle_database ( number_of_contour_citybases, contour_citybases, citybase_colour );
	}

	//
	// Boundaries
	//

	render_contour_node_thick_database ( contour_map_number_of_boundary_paths, contour_map_boundary_paths, contour_map_boundary_nodes, boundary_colour, 1 );

	//
	// Restore the fog
	//

	reinstate_d3d_fog ();

	//
	// Turn Z buffering back on again
	//

	set_d3d_int_state ( D3DRENDERSTATE_ZENABLE, TRUE );

	d3d_in_order_rendering = FALSE;

	safe_free ( contour_height_difference_reciprocals );

	contour_height_difference_reciprocals = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_contour_triangle_database ( int number_of_triangle_sets, contour_lake *lakes, real_colour lake_colour )
{

	int
		count;

	real_colour
		specular;

	float
		xmin,
		xmax,
		zmin,
		zmax;

	xmin = min ( terrain_2d_map_world_xmin, terrain_2d_map_world_xmax );
	xmax = max ( terrain_2d_map_world_xmin, terrain_2d_map_world_xmax );

	zmin = min ( terrain_2d_map_world_zmin, terrain_2d_map_world_zmax );
	zmax = max ( terrain_2d_map_world_zmin, terrain_2d_map_world_zmax );

	specular.red = 0;
	specular.green = 0;
	specular.blue = 0;
	specular.alpha = 255;

	for ( count = 0; count < number_of_triangle_sets; count++ )
	{

		int
			outcode,
			outcode1,
			outcode2,
			triangle;

		vec3d
			*points;

		vertex
			vertices[3];

		points = lakes[count].triangle_points;

		//
		// Outcode the lake first
		//

		outcode = 0;
		if ( lakes[count].xmin < xmin )	outcode |= CLIP_LEFT;
		if ( lakes[count].xmin > xmax )	outcode |= CLIP_RIGHT;
		if ( lakes[count].zmin < zmin )	outcode |= CLIP_TOP;
		if ( lakes[count].zmin > zmax )	outcode |= CLIP_BOTTOM;

		outcode1 = outcode;
		outcode2 = outcode;

		outcode = 0;
		if ( lakes[count].xmax < xmin )	outcode |= CLIP_LEFT;
		if ( lakes[count].xmax > xmax )	outcode |= CLIP_RIGHT;
		if ( lakes[count].zmax < zmin )	outcode |= CLIP_TOP;
		if ( lakes[count].zmax > zmax )	outcode |= CLIP_BOTTOM;

		outcode1 |= outcode;
		outcode2 &= outcode;

		if ( outcode2 == 0 )
		{

			vertices[0].z = 10;
			vertices[0].q = 0.1;
			vertices[1].z = 10;
			vertices[1].q = 0.1;
			vertices[2].z = 10;
			vertices[2].q = 0.1;
		
			for ( triangle = 0; triangle < lakes[count].number_of_triangles; triangle++ )
			{
	
				int
					outcode,
					outcode2;
	
				vertices[0].i = ( points[0].x - terrain_2d_map_world_xcentre ) * terrain_2d_map_screen_xscale + terrain_2d_map_screen_xcentre;
				vertices[0].j = ( points[0].z - terrain_2d_map_world_zcentre ) * terrain_2d_map_screen_yscale + terrain_2d_map_screen_ycentre;
	
				vertices[1].i = ( points[1].x - terrain_2d_map_world_xcentre ) * terrain_2d_map_screen_xscale + terrain_2d_map_screen_xcentre;
				vertices[1].j = ( points[1].z - terrain_2d_map_world_zcentre ) * terrain_2d_map_screen_yscale + terrain_2d_map_screen_ycentre;
	
				vertices[2].i = ( points[2].x - terrain_2d_map_world_xcentre ) * terrain_2d_map_screen_xscale + terrain_2d_map_screen_xcentre;
				vertices[2].j = ( points[2].z - terrain_2d_map_world_zcentre ) * terrain_2d_map_screen_yscale + terrain_2d_map_screen_ycentre;
	
				vertices[0].outcode = generate_contour_outcode ( vertices[0].i, vertices[0].j );
				vertices[1].outcode = generate_contour_outcode ( vertices[1].i, vertices[1].j );
				vertices[2].outcode = generate_contour_outcode ( vertices[2].i, vertices[2].j );
	
				vertices[0].next_vertex = &vertices[1];
				vertices[1].next_vertex = &vertices[2];
				vertices[2].next_vertex = NULL;
	
				outcode = vertices[0].outcode;
				outcode2 = vertices[0].outcode;
	
				outcode |= vertices[1].outcode;
				outcode2 &= vertices[1].outcode;
	
				outcode |= vertices[2].outcode;
				outcode2 &= vertices[2].outcode;
	
				if ( outcode2 == 0 )
				{
		
					vertex
						*poly;
		
					poly = &vertices[0];
		
					clip_3d_coord = 0;
		
					if ( outcode )
					{

						poly = clip_3d_polygon ( poly, outcode );
					}
			
					if ( poly )
					{
	
						draw_wbuffered_plain_polygon ( poly, lake_colour, specular );
					}
				}
	
				points += 3;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_contour_terrain_quad ( vertex *vertices, int contour_start_index, int contour_end_index )
{
	int
		count;

	real_colour
		contour_colour,
		contour_line_colour,
		specular;

	specular.red = 0;
	specular.green = 0;
	specular.blue = 0;
	specular.alpha = 255;

	contour_line_colour.red = 60;
	contour_line_colour.green = 40;
	contour_line_colour.blue = 20;

	vertices[0].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;
	vertices[1].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;
	vertices[2].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;
	vertices[3].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;

	if ( contour_start_index == contour_end_index )	// no contour line in this quad
	{

		int
			quad_outcode,
			quad_outcode2,
			triangle1_outcode,
			triangle1_outcode2,
			triangle2_outcode,
			triangle2_outcode2;

		contour_minimum_height = terrain_2d_contour_heights[contour_start_index];
		contour_maximum_height = terrain_2d_contour_heights[contour_start_index+1];
	
		contour_colour.red = terrain_2d_current_contour_colours[contour_start_index].r;
		contour_colour.green = terrain_2d_current_contour_colours[contour_start_index].g;
		contour_colour.blue = terrain_2d_current_contour_colours[contour_start_index].b;

		quad_outcode = vertices[1].outcode;
		quad_outcode2 = vertices[1].outcode;
		quad_outcode |= vertices[2].outcode;
		quad_outcode2 &= vertices[2].outcode;

		triangle1_outcode = quad_outcode | vertices[0].outcode;
		triangle1_outcode2 = quad_outcode2 & vertices[0].outcode;

		triangle2_outcode = quad_outcode | vertices[3].outcode;
		triangle2_outcode2 = quad_outcode2 & vertices[3].outcode;

		quad_outcode2 &= triangle1_outcode2;
		quad_outcode2 &= triangle2_outcode2;

		quad_outcode |= triangle1_outcode;
		quad_outcode |= triangle2_outcode;

		if ( quad_outcode == 0 )
		{
	
			vertices[1].next_vertex = &vertices[3];
			vertices[3].next_vertex = &vertices[2];
			vertices[2].next_vertex = &vertices[0];
			vertices[0].next_vertex = NULL;

			render_shaded_contour_terrain_poly ( &vertices[1], contour_colour);
		}
		else
		{

			if ( triangle1_outcode2 == 0 )
			{
	
				vertex
					*poly;
	
				vertices[0].next_vertex = &vertices[1];
				vertices[1].next_vertex = &vertices[2];
				vertices[2].next_vertex = NULL;

				poly = &vertices[0];
	
				clip_3d_coord = 0;
	
				if ( triangle1_outcode )
				{
		
					poly = clip_contour_polygon ( poly, triangle1_outcode );
				}
		
				if ( poly )
				{
				
					render_shaded_contour_terrain_poly ( poly, contour_colour);
				}
			}
	
			if ( triangle2_outcode2 == 0 )
			{
	
				vertex
					*poly;
	
				vertices[2].next_vertex = &vertices[1];
				vertices[1].next_vertex = &vertices[3];
				vertices[3].next_vertex = NULL;
	
				poly = &vertices[2];
	
				clip_3d_coord = 0;
	
				if ( triangle2_outcode )
				{
		
					poly = clip_contour_polygon ( poly, triangle2_outcode );
				}
		
				if ( poly )
				{
				
					render_shaded_contour_terrain_poly ( poly, contour_colour);
				}
			}
		}
	}
	else  // contains contour line(s)
	{
		float
			i_scale = 1.0 / (vertices[3].i - vertices[0].i),
			j_scale = 1.0 / (vertices[3].j - vertices[0].j);

		for ( count = contour_start_index; count <= contour_end_index; count++ )
		{
	
			vertex
				contour_line_vertices[4];
	
			int
				line_vertex_index,
				quad_outcode,
				quad_outcode2,
				triangle1_outcode,
				triangle1_outcode2,
				triangle2_outcode,
				triangle2_outcode2;

			contour_minimum_height = terrain_2d_contour_heights[count];
			contour_maximum_height = terrain_2d_contour_heights[count+1];
	
			line_vertex_index = 0;
	
			contour_colour.red = terrain_2d_current_contour_colours[count].r;
			contour_colour.green = terrain_2d_current_contour_colours[count].g;
			contour_colour.blue = terrain_2d_current_contour_colours[count].b;

			//
			// Add in height outcodes
			//

			vertices[0].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;
			vertices[1].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;
			vertices[2].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;
			vertices[3].outcode &= CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;

			{
	
				unsigned int
					outcode_gen1,
					outcode_gen2;
	
				float
					foutcode_gen;
		
				foutcode_gen = vertices[0].y - contour_minimum_height; outcode_gen1 = *( ( int * ) &foutcode_gen );
				foutcode_gen =  contour_maximum_height - vertices[0].y; outcode_gen2 = *( ( int * ) &foutcode_gen );
				outcode_gen1 >>= 26; outcode_gen1 &= CLIP_HITHER;
				outcode_gen2 >>= 27; outcode_gen2 &= CLIP_YONDER;
				vertices[0].outcode |= ( outcode_gen1 | outcode_gen2 );
	
				foutcode_gen = vertices[1].y - contour_minimum_height; outcode_gen1 = *( ( int * ) &foutcode_gen );
				foutcode_gen = contour_maximum_height - vertices[1].y; outcode_gen2 = *( ( int * ) &foutcode_gen );
				outcode_gen1 >>= 26; outcode_gen1 &= CLIP_HITHER;
				outcode_gen2 >>= 27; outcode_gen2 &= CLIP_YONDER;
				vertices[1].outcode |= ( outcode_gen1 | outcode_gen2 );
	
				foutcode_gen = vertices[2].y - contour_minimum_height; outcode_gen1 = *( ( int * ) &foutcode_gen );
				foutcode_gen = contour_maximum_height - vertices[2].y; outcode_gen2 = *( ( int * ) &foutcode_gen );
				outcode_gen1 >>= 26; outcode_gen1 &= CLIP_HITHER;
				outcode_gen2 >>= 27; outcode_gen2 &= CLIP_YONDER;
				vertices[2].outcode |= ( outcode_gen1 | outcode_gen2 );
	
				foutcode_gen = vertices[3].y - contour_minimum_height; outcode_gen1 = *( ( int * ) &foutcode_gen );
				foutcode_gen = contour_maximum_height - vertices[3].y; outcode_gen2 = *( ( int * ) &foutcode_gen );
				outcode_gen1 >>= 26; outcode_gen1 &= CLIP_HITHER;
				outcode_gen2 >>= 27; outcode_gen2 &= CLIP_YONDER;
				vertices[3].outcode |= ( outcode_gen1 | outcode_gen2 );
			}

			quad_outcode = vertices[1].outcode;
			quad_outcode2 = vertices[1].outcode;
			quad_outcode |= vertices[2].outcode;
			quad_outcode2 &= vertices[2].outcode;
	
			triangle1_outcode = quad_outcode | vertices[0].outcode;
			triangle1_outcode2 = quad_outcode2 & vertices[0].outcode;
	
			triangle2_outcode = quad_outcode | vertices[3].outcode;
			triangle2_outcode2 = quad_outcode2 & vertices[3].outcode;
	
			quad_outcode2 &= triangle1_outcode2;
			quad_outcode2 &= triangle2_outcode2;
	
			if ( quad_outcode2 == 0 )
			{
				quad_outcode |= triangle1_outcode;
				quad_outcode |= triangle2_outcode;

				if ( quad_outcode == 0 )
				{
					vertices[1].next_vertex = &vertices[3];
					vertices[3].next_vertex = &vertices[2];
					vertices[2].next_vertex = &vertices[0];
					vertices[0].next_vertex = NULL;
	
					render_shaded_contour_terrain_poly ( &vertices[1], contour_colour);
				}
				else  // contour line goes through quad, split into triangles
				{
					if ( triangle1_outcode2 == 0 )
					{
						vertex
							*poly;

						vertices[0].next_vertex = &vertices[1];
						vertices[1].next_vertex = &vertices[2];
						vertices[2].next_vertex = NULL;

						poly = &vertices[0];
			
						clip_3d_coord = 0;
			
						if ( triangle1_outcode & CLIP_HITHER )
						{
			
							poly = bottom_clip_contour_polygon ( poly, &triangle1_outcode );

							// set coordinates for the contour itself:
							contour_line_vertices[line_vertex_index].i = clip_3d_crds[0].i;
							contour_line_vertices[line_vertex_index].j = clip_3d_crds[0].j;
							contour_line_vertices[line_vertex_index].outcode = clip_3d_crds[0].outcode;
		
							line_vertex_index++;
		
							contour_line_vertices[line_vertex_index].i = clip_3d_crds[1].i;
							contour_line_vertices[line_vertex_index].j = clip_3d_crds[1].j;
							contour_line_vertices[line_vertex_index].outcode = clip_3d_crds[1].outcode;
		
							line_vertex_index++;
						}

						if ( poly )
						{
							if ( triangle1_outcode & CLIP_YONDER )
								poly = top_clip_contour_polygon ( poly, &triangle1_outcode );
			
							if ( poly )
							{
			
								if ( triangle1_outcode )
									poly = clip_contour_polygon ( poly, triangle1_outcode );
						
								if ( poly )
								{
									vertex* new_v;

									for (new_v = poly; new_v; new_v = new_v->next_vertex)
									{
										float delta_i, delta_j;

										if (new_v == &vertices[0]
											|| new_v == &vertices[1]
											|| new_v == &vertices[2]
											|| new_v == &vertices[3])
										{
											continue;
										}
										
										delta_i = (new_v->i - vertices[0].i) * i_scale;
										delta_j = (new_v->j - vertices[0].j) * j_scale;

										// weighted average of corner xs (weighted according to distance to each corner
										new_v->x = ((1 - delta_i) * (1 - delta_j) * vertices[0].x) + 
												   (delta_i       * (1 - delta_j) * vertices[1].x) +
												   ((1 - delta_i) * delta_j       * vertices[2].x) +
												   (delta_i       * delta_j       * vertices[3].x);
									}

									render_shaded_contour_terrain_poly ( poly, contour_colour);
								}
							}
						}
					}
			
					if ( triangle2_outcode2 == 0 )
					{
			
						vertex
							*poly;
			
						vertices[2].next_vertex = &vertices[1];
						vertices[1].next_vertex = &vertices[3];
						vertices[3].next_vertex = NULL;
			
						poly = &vertices[2];
			
						clip_3d_coord = 0;
			
						if ( triangle2_outcode & CLIP_HITHER )
						{
			
							poly = bottom_clip_contour_polygon ( poly, &triangle2_outcode );
		
							contour_line_vertices[line_vertex_index].i = clip_3d_crds[0].i;
							contour_line_vertices[line_vertex_index].j = clip_3d_crds[0].j;
							contour_line_vertices[line_vertex_index].outcode = clip_3d_crds[0].outcode;
		
							line_vertex_index++;
		
							contour_line_vertices[line_vertex_index].i = clip_3d_crds[1].i;
							contour_line_vertices[line_vertex_index].j = clip_3d_crds[1].j;
							contour_line_vertices[line_vertex_index].outcode = clip_3d_crds[1].outcode;
		
							line_vertex_index++;
						}
			
						if ( poly )
						{
			
							if ( triangle2_outcode & CLIP_YONDER )
							{
			
								poly = top_clip_contour_polygon ( poly, &triangle2_outcode );
							}
			
							if ( poly )
							{
			
								if ( triangle2_outcode )
								{
						
									poly = clip_contour_polygon ( poly, triangle2_outcode );
								}
						
								if ( poly )
								{
									vertex* new_v;
									for (new_v = poly; new_v; new_v = new_v->next_vertex)
									{
										float delta_i, delta_j;

										if (new_v == &vertices[0]
											|| new_v == &vertices[1]
											|| new_v == &vertices[2]
											|| new_v == &vertices[3])
										{
											continue;
										}
										
										delta_i = (new_v->i - vertices[0].i) * i_scale;
										delta_j = (new_v->j - vertices[0].j) * j_scale;

//										ASSERT(delta_i >= 0.0 && delta_i <= 1.0);
//										ASSERT(delta_j >= 0.0 && delta_j <= 1.0);

										// weighted average of corner xs (weighted according to distance to each corner
										new_v->x = ((1 - delta_i) * (1 - delta_j) * vertices[0].x) + 
												   (delta_i       * (1 - delta_j) * vertices[1].x) +
												   ((1 - delta_i) * delta_j       * vertices[2].x) +
												   (delta_i       * delta_j       * vertices[3].x);
									}

									render_shaded_contour_terrain_poly ( poly, contour_colour);
								}
							}
						}
					}
	
					//
					// Draw the contour lines if there are any
					//

					if ( ( line_vertex_index > 0 ) && ( terrain_2d_map_contour_lines_drawn ) )
					{
						draw_contour_line ( &contour_line_vertices[0], contour_line_colour );
		
						if ( line_vertex_index > 2 )
						{
		
							draw_contour_line ( &contour_line_vertices[2], contour_line_colour );
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_contour_terrain_quad_quad ( vertex *vertices, int contour_start_index, int contour_end_index )
{

	int
		count;


	LPD3DTLVERTEX
		vptr;

	float
		source_red,
		source_green,
		source_blue;

	real_colour
		specular;

	specular.red = 0;
	specular.green = 0;
	specular.blue = 0;
	specular.alpha = 255;

	vptr = get_d3d_vertices_points_address ( 8 );

	source_red = terrain_2d_current_contour_colours[contour_start_index].r;
	source_green = terrain_2d_current_contour_colours[contour_start_index].g;
	source_blue = terrain_2d_current_contour_colours[contour_start_index].b;

	contour_minimum_height = terrain_2d_contour_heights[contour_start_index];

	for ( count = 0; count < 9; count++ )
	{

		float
			r,
			g,
			b,
			factor;

		int
			ir,
			ig,
			ib;

		real_colour
			col;

		factor = ( vertices[count].y - contour_minimum_height ) * contour_height_difference_reciprocals[contour_start_index] * CONTOUR_SHADING_FACTOR;
		factor -= ( CONTOUR_SHADING_FACTOR / 2 );

		r = source_red + ( source_red * factor );
		g = source_green + ( source_green * factor );
		b = source_blue + ( source_blue * factor );

		convert_float_to_int ( r, &ir );
		convert_float_to_int ( g, &ig );
		convert_float_to_int ( b, &ib );

		ir = bound ( ir, 0, 255 );
		ig = bound ( ig, 0, 255 );
		ib = bound ( ib, 0, 255 );

		col.red = ir;
		col.green = ig;
		col.blue = ib;

		vptr[count].sx = vertices[count].i;
		vptr[count].sy = vertices[count].j;
		vptr[count].rhw = vertices[count].q;
		vptr[count].sz = vertices[count].q;
		vptr[count].color = col.colour;
		vptr[count].specular = specular.colour;
	}

	draw_special_quad_quad_primitive ( 9 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_shaded_contour_terrain_poly (vertex *poly, real_colour contour_colour)
{

	int
		number_of_vertices;

	LPD3DTLVERTEX
		vertices,
		vptr;

	vertices = get_d3d_vertices_address ( poly, &number_of_vertices );

	vptr = vertices;

	while ( poly )
	{
		real_colour
			col;

		float
			r,
			g,
			b,
			shadow_factor;
	
		int
			ir,
			ig,
			ib;

		r = contour_colour.red;
		g = contour_colour.green;
		b = contour_colour.blue;
	
		// adjust shade for steepness
		shadow_factor = 1 - poly->x * 0.0025; // 0.0003;
		if (shadow_factor < 0.25)
			shadow_factor = 0.25;
	
		r *= shadow_factor;
		g *= shadow_factor;
		b *= shadow_factor;

		convert_float_to_int ( r, &ir );
		convert_float_to_int ( g, &ig );
		convert_float_to_int ( b, &ib );


		col.red = bound ( ir, 0, 255 );
		col.green = bound ( ig, 0, 255 );
		col.blue = bound ( ib, 0, 255 );

		vptr->sx = poly->i;
		vptr->sy = poly->j;
		vptr->rhw = poly->q;
		vptr->sz = poly->q;
		vptr->color = col.colour;
		vptr->specular = 0x000000ff;  // solid black

		vptr++;

		poly = poly->next_vertex;
	}

	draw_fan_primitive ( number_of_vertices, vertices );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_contour_node_database ( int number_of_nodes, contour_path *paths, vec3d *nodes, real_colour colour, int mipmap_level )
{

	int
		initial_node_skip,
		node_skip,
		node;

	vertex
		vertices[4];

	float
		xmin,
		xmax,
		zmin,
		zmax;

	xmin = min ( terrain_2d_map_world_xmin, terrain_2d_map_world_xmax );
	xmax = max ( terrain_2d_map_world_xmin, terrain_2d_map_world_xmax );

	zmin = min ( terrain_2d_map_world_zmin, terrain_2d_map_world_zmax );
	zmax = max ( terrain_2d_map_world_zmin, terrain_2d_map_world_zmax );

//	initial_node_skip = mipmap_level * 8;
	initial_node_skip = ( mipmap_level -1 ) * 2;

	for ( node = 0; node < number_of_nodes; node++ )
	{

		if (	( paths[node].type != TEMP_TERRAIN_TYPE_COASTAL_RIVER ) &&
				( paths[node].type != TEMP_TERRAIN_TYPE_LAKE ) &&
				( paths[node].type != TEMP_TERRAIN_TYPE_OFFROAD ) )
		{
	
			if ( paths[node].count <= initial_node_skip )
			{
	
				generate_world_position_vertex ( &nodes[paths[node].from], &vertices[0] );
				generate_world_position_vertex ( &nodes[paths[node].to], &vertices[1] );

				draw_contour_line ( vertices, colour );
			}
			else
			{
		
				vec3d
					*sub_positions;
	
				int
					outcode,
					outcode1,
					outcode2,
					count;
	
				sub_positions = paths[node].points;
	
				//
				// Outcode the stretch of road
				//
	
				outcode = 0;
				if ( paths[node].xmin < xmin )	outcode |= CLIP_LEFT;
				if ( paths[node].xmin > xmax )	outcode |= CLIP_RIGHT;
				if ( paths[node].zmin < zmin )	outcode |= CLIP_TOP;
				if ( paths[node].zmin > zmax )	outcode |= CLIP_BOTTOM;
	
				outcode1 = outcode;
				outcode2 = outcode;
	
				outcode = 0;
				if ( paths[node].xmax < xmin )	outcode |= CLIP_LEFT;
				if ( paths[node].xmax > xmax )	outcode |= CLIP_RIGHT;
				if ( paths[node].zmax < zmin )	outcode |= CLIP_TOP;
				if ( paths[node].zmax > zmax )	outcode |= CLIP_BOTTOM;
	
				outcode1 |= outcode;
				outcode2 &= outcode;
	
				if ( outcode2 == 0 )
				{

					node_skip = initial_node_skip;

					//
					// Draw the start point
					//
	
					generate_world_position_vertex ( &nodes[paths[node].from], &vertices[0] );
					generate_world_position_vertex ( &sub_positions[0], &vertices[1] );
		
					draw_contour_line ( vertices, colour );
			
					for ( count = 0; count < ( paths[node].count - 1 ); count++ )
					{

						if ( node_skip == 0 )
						{

							node_skip = initial_node_skip;

							vertices[0].i = vertices[1].i;
							vertices[0].j = vertices[1].j;
							vertices[0].outcode = vertices[1].outcode;
							generate_world_position_vertex ( &sub_positions[count+1], &vertices[1] );
				
							draw_contour_line ( vertices, colour );
						}
						else
						{

							node_skip--;
						}
					}
			
					vertices[0].i = vertices[1].i;
					vertices[0].j = vertices[1].j;
					vertices[0].outcode = vertices[1].outcode;
					generate_world_position_vertex ( &nodes[paths[node].to], &vertices[1] );
			
					draw_contour_line ( vertices, colour );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_contour_node_thick_database ( int number_of_nodes, contour_path *paths, vec3d *nodes, real_colour colour, int mipmap_level )
{

	int
		initial_node_skip,
		node_skip,
		node;

	vertex
		vertices[4];

	float
		xmin,
		xmax,
		zmin,
		zmax;

	xmin = min ( terrain_2d_map_world_xmin, terrain_2d_map_world_xmax );
	xmax = max ( terrain_2d_map_world_xmin, terrain_2d_map_world_xmax );

	zmin = min ( terrain_2d_map_world_zmin, terrain_2d_map_world_zmax );
	zmax = max ( terrain_2d_map_world_zmin, terrain_2d_map_world_zmax );

//	initial_node_skip = mipmap_level * 8;
	initial_node_skip = ( mipmap_level -1 ) * 2;

	for ( node = 0; node < number_of_nodes; node++ )
	{

		if (	( paths[node].type != TEMP_TERRAIN_TYPE_COASTAL_RIVER ) &&
				( paths[node].type != TEMP_TERRAIN_TYPE_LAKE ) &&
				( paths[node].type != TEMP_TERRAIN_TYPE_OFFROAD ) )
		{
	
			if ( paths[node].count <= initial_node_skip )
			{
	
				generate_world_position_vertex ( &nodes[paths[node].from], &vertices[0] );
				generate_world_position_vertex ( &nodes[paths[node].to], &vertices[1] );

				draw_thick_contour_line ( vertices, colour );
			}
			else
			{
		
				vec3d
					*sub_positions;
	
				int
					outcode,
					outcode1,
					outcode2,
					count;
	
				sub_positions = paths[node].points;
	
				//
				// Outcode the stretch of road
				//
	
				outcode = 0;
				if ( paths[node].xmin < xmin )	outcode |= CLIP_LEFT;
				if ( paths[node].xmin > xmax )	outcode |= CLIP_RIGHT;
				if ( paths[node].zmin < zmin )	outcode |= CLIP_TOP;
				if ( paths[node].zmin > zmax )	outcode |= CLIP_BOTTOM;
	
				outcode1 = outcode;
				outcode2 = outcode;
	
				outcode = 0;
				if ( paths[node].xmax < xmin )	outcode |= CLIP_LEFT;
				if ( paths[node].xmax > xmax )	outcode |= CLIP_RIGHT;
				if ( paths[node].zmax < zmin )	outcode |= CLIP_TOP;
				if ( paths[node].zmax > zmax )	outcode |= CLIP_BOTTOM;
	
				outcode1 |= outcode;
				outcode2 &= outcode;
	
				if ( outcode2 == 0 )
				{

					node_skip = initial_node_skip;

					//
					// Draw the start point
					//
	
					generate_world_position_vertex ( &nodes[paths[node].from], &vertices[0] );
					generate_world_position_vertex ( &sub_positions[0], &vertices[1] );
		
					draw_thick_contour_line ( vertices, colour );
			
					for ( count = 0; count < ( paths[node].count - 1 ); count++ )
					{

						if ( node_skip == 0 )
						{

							node_skip = initial_node_skip;

							vertices[0].i = vertices[1].i;
							vertices[0].j = vertices[1].j;
							vertices[0].outcode = vertices[1].outcode;
							generate_world_position_vertex ( &sub_positions[count+1], &vertices[1] );
				
							draw_thick_contour_line ( vertices, colour );
						}
						else
						{

							node_skip--;
						}
					}
			
					vertices[0].i = vertices[1].i;
					vertices[0].j = vertices[1].j;
					vertices[0].outcode = vertices[1].outcode;
					generate_world_position_vertex ( &nodes[paths[node].to], &vertices[1] );
			
					draw_thick_contour_line ( vertices, colour );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_simple_elevation_vertex ( int x, int z, vertex *v )
{

	float
		fx,
		fy;

	fx = ( x * terrain_3d_simple_elevation_x_grid_size ) - terrain_2d_map_world_xcentre;
	fy = ( z * terrain_3d_simple_elevation_z_grid_size ) - terrain_2d_map_world_zcentre;
	
	v->i = ( fx * terrain_2d_map_screen_xscale ) + terrain_2d_map_screen_xcentre;
	v->j = ( fy * terrain_2d_map_screen_yscale ) + terrain_2d_map_screen_ycentre;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_simple_elevation_height ( int x, int z )
{

	return ( terrain_3d_simple_elevation_grid[(z*terrain_3d_simple_elevation_width)+x] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char generate_contour_outcode ( float i, float j )
{

	float
		oxmax,
		oxmin,
		oymax,
		oymin;
	
	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	oxmax = active_viewport.x_max - i;
	oxmin = i - active_viewport.x_min;
	oymax = active_viewport.y_max - j;
	oymin = j - active_viewport.y_min;

	ixmax = *( ( unsigned int * ) &oxmax );
	ixmin = *( ( unsigned int * ) &oxmin );
	iymax = *( ( unsigned int * ) &oymax );
	iymin = *( ( unsigned int * ) &oymin );

	ixmin >>= 31;
	iymin &= 0x80000000;
	ixmax >>= 29;
	iymax &= 0x80000000;
	iymin >>= 30;
	ixmin &= 0x00000001;
	iymax >>= 28;
	ixmax &= 0x00000004;
	ixmin |= iymin;
	ixmax |= iymax;

	return ( ixmin | ixmax );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generate_world_position_vertex ( vec3d *position, vertex *v )
{

	float
		fx,
		fy;

	fx = position->x - terrain_2d_map_world_xcentre;
	fy = position->z - terrain_2d_map_world_zcentre;
	
	v->i = ( fx * terrain_2d_map_screen_xscale ) + terrain_2d_map_screen_xcentre;
	v->j = ( fy * terrain_2d_map_screen_yscale ) + terrain_2d_map_screen_ycentre;

	v->outcode = generate_contour_outcode ( v->i, v->j );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_contour_line ( vertex *vertices, real_colour colour )
{

	unsigned char
		outcode,
		outcode2;

	vertices[0].next_vertex = &vertices[1];
	vertices[1].next_vertex = NULL;
	vertices[0].z = 10;
	vertices[0].q = 0.1;
	vertices[1].z = 10;
	vertices[1].q = 0.1;

	outcode = vertices[0].outcode;
	outcode2 = vertices[0].outcode;

	outcode |= vertices[1].outcode;
	outcode2 &= vertices[1].outcode;

	if ( outcode2 == 0 )
	{

		vertex
			*poly;

		poly = &vertices[0];

		if ( outcode )
		{

			clip_3d_coord = 0;;

			poly = clip_3d_polygon ( poly, outcode );
		}

		if ( poly )
		{

			zbuffer_constant = zbuffer_constant_elevated_bias;

			draw_wbuffered_plain_line ( poly, colour );

			zbuffer_constant = zbuffer_constant_normal_bias;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_thick_contour_line ( vertex *vertices, real_colour colour )
{

	draw_thick_line ( vertices[0].i, vertices[0].j, vertices[1].i, vertices[1].j, colour, 2.0 );
/*
	unsigned char
		outcode,
		outcode2;

	vertex
		new_vertices[4];

	vec3d
		normal;

	real_colour
		specular;

	specular.red = 0;
	specular.green = 0;
	specular.blue = 0;
	specular.alpha = 0;
	normal.x = vertices[1].j - vertices[0].j;
	normal.z = vertices[0].i - vertices[1].i;
	normal.y = 0;
	normalise_any_3d_vector ( &normal );
	normal.x *= 2;
	normal.z *= 2;

	new_vertices[0].i = vertices[0].i - normal.x;
	new_vertices[0].j = vertices[0].j - normal.z;
	new_vertices[1].i = vertices[0].i + normal.x;
	new_vertices[1].j = vertices[0].j + normal.z;
	new_vertices[2].i = vertices[1].i - normal.x;
	new_vertices[2].j = vertices[1].j - normal.z;
	new_vertices[3].i = vertices[1].i + normal.x;
	new_vertices[3].j = vertices[1].j + normal.z;

	new_vertices[0].outcode = generate_contour_outcode ( new_vertices[0].i, new_vertices[0].j );
	new_vertices[1].outcode = generate_contour_outcode ( new_vertices[1].i, new_vertices[1].j );
	new_vertices[2].outcode = generate_contour_outcode ( new_vertices[2].i, new_vertices[2].j );
	new_vertices[3].outcode = generate_contour_outcode ( new_vertices[3].i, new_vertices[3].j );

	new_vertices[0].next_vertex = &new_vertices[1];
	new_vertices[1].next_vertex = &new_vertices[3];
	new_vertices[3].next_vertex = &new_vertices[2];
	new_vertices[2].next_vertex = NULL;

	new_vertices[0].z = 10; new_vertices[0].q = 0.1;
	new_vertices[1].z = 10; new_vertices[1].q = 0.1;
	new_vertices[2].z = 10; new_vertices[2].q = 0.1;
	new_vertices[3].z = 10; new_vertices[3].q = 0.1;

	outcode = new_vertices[0].outcode; outcode2 = new_vertices[0].outcode;
	outcode |= new_vertices[1].outcode; outcode2 &= new_vertices[1].outcode;
	outcode |= new_vertices[2].outcode; outcode2 &= new_vertices[2].outcode;
	outcode |= new_vertices[3].outcode; outcode2 &= new_vertices[3].outcode;

	if ( outcode2 == 0 )
	{

		vertex
			*poly;

		poly = &new_vertices[0];

		if ( outcode )
		{

			clip_3d_coord = 0;;

			poly = clip_3d_polygon ( poly, outcode );
		}

		if ( poly )
		{

			zbuffer_constant = zbuffer_constant_elevated_bias;

			draw_wbuffered_plain_polygon ( poly, colour, specular );

			zbuffer_constant = zbuffer_constant_normal_bias;
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *clip_contour_polygon ( vertex *polygon, int outcode )
{

	number_of_polygons_screen_clipped++;

	if ( outcode & CLIP_LEFT )
	{
	
		//
		// First clip against the left side of the viewing rectangle
		//
	
		clip_list = NULL;
	
		clip_point = NULL;
	
		last_point = polygon;
	
		this_point = polygon->next_vertex;
	
		if ( polygon->i >= active_viewport.x_min )
		{
	
			//
			// Start the clipped list off.
			//
	
			clip_list = polygon;
	
			clip_point = polygon;
	
			polygon->next_vertex = NULL;
		}
	
		while ( this_point )
		{
	
			if ( this_point->i >= active_viewport.x_min )
			{
	
				//
				// This point is inside the screen boundary
				//
	
				if ( last_point->i < active_viewport.x_min )
				{
	
					//
					//	The last point isn't in the screen, but this one is, find intersection
					//
	
					insert_xmin_contour_coordinate ( last_point, this_point );
				}
	
				//
				// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put 1.0 in!
				//
	
				clip_point->next_vertex = this_point;
	
				clip_point = this_point;
			}
			else
			{
	
				//
				// This point isn't in the screen area
				//
	
				if ( last_point->i >= active_viewport.x_min )
				{
	
					//
					// The last point was visible - find intersection point
					//
					
					insert_xmin_contour_coordinate ( last_point, this_point );
				}
			}
	
			last_point = this_point;
	
			this_point = this_point->next_vertex;
		}
	
		if ( !clip_point )
		{
	
			return ( NULL );						// If there are no valid points in the polygon, exit
		}
	
		if ( ( last_point->i < active_viewport.x_min ) ^ ( polygon->i < active_viewport.x_min ) )
		{
	
			//
			// The last point in the polygon was off the screen, the first 1.0 isn't, so add a clip point
			//
	
			insert_xmin_contour_coordinate ( last_point, polygon );
		}
	
		clip_point->next_vertex = NULL;
	
		polygon = clip_list;
	}

	if ( outcode & CLIP_RIGHT )
	{
	
		//
		// Next clip against the right side of the viewing rectangle
		//
	
		clip_list = NULL;
	
		clip_point = NULL;
	
		last_point = polygon;
	
		this_point = polygon->next_vertex;
	
		if ( polygon->i <= active_viewport.x_max )
		{
	
			//
			// Start the clipped list off.
			//
	
			clip_list = polygon;
	
			clip_point = polygon;
	
			polygon->next_vertex = NULL;
		}
	
		while ( this_point )
		{
	
			if ( this_point->i <= active_viewport.x_max )
			{
	
				//
				// This point is inside the screen boundary
				//
	
				if ( last_point->i > active_viewport.x_max )
				{
	
					//
					//	The last point isn't in the screen, but this one is, find intersection
					//
	
					insert_xmax_contour_coordinate ( last_point, this_point );
				}
	
				//
				// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put 1.0 in!
				//
	
				clip_point->next_vertex = this_point;
	
				clip_point = this_point;
			}
			else
			{
	
				//
				// This point isn't in the screen area
				//
	
				if ( last_point->i <= active_viewport.x_max )
				{
	
					//
					// The last point was visible - find intersection point
					//
					
					insert_xmax_contour_coordinate ( last_point, this_point );
				}
			}
	
			last_point = this_point;
	
			this_point = this_point->next_vertex;
		}
	
		if ( !clip_point )
		{
	
			return ( NULL );
		}
	
		if ( ( last_point->i > active_viewport.x_max ) ^ ( polygon->i > active_viewport.x_max ) )
		{
	
			//
			// The last point in the polygon was off the screen, the first 1.0 isn't, so add a clip point
			//
	
			insert_xmax_contour_coordinate ( last_point, polygon );
		}
	
		clip_point->next_vertex = NULL;
	
		polygon = clip_list;
	}

	if ( outcode & CLIP_TOP )
	{
	
		//
		// Next clip against the top of the viewing rectangle
		//
	
		clip_list = NULL;
	
		clip_point = NULL;
	
		last_point = polygon;
	
		this_point = polygon->next_vertex;
	
		if ( polygon->j >= active_viewport.y_min )
		{
	
			//
			// Start the clipped list off.
			//
	
			clip_list = polygon;
	
			clip_point = polygon;
	
			polygon->next_vertex = NULL;
		}
	
		while ( this_point )
		{
	
			if ( this_point->j >= active_viewport.y_min )
			{
	
				//
				// This point is inside the screen boundary
				//
	
				if ( last_point->j < active_viewport.y_min )
				{
	
					//
					//	The last point isn't in the screen, but this one is, find intersection
					//
	
					insert_ymin_contour_coordinate ( last_point, this_point );
				}
	
				//
				// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put one in!
				//
	
				clip_point->next_vertex = this_point;
	
				clip_point = this_point;
			}
			else
			{
	
				//
				// This point isn't in the screen area
				//
	
				if ( last_point->j >= active_viewport.y_min )
				{
	
					//
					// The last point was visible - find intersection point
					//
					
					insert_ymin_contour_coordinate ( last_point, this_point );
				}
			}
	
			last_point = this_point;
	
			this_point = this_point->next_vertex;
		}
	
		if ( !clip_point )
		{
	
			return ( NULL );
		}
	
		if ( ( last_point->j < active_viewport.y_min ) ^ ( polygon->j < active_viewport.y_min ) )
		{
	
			//
			// The last point in the polygon was off the screen, the first one isn't, so add a clip point
			//
	
			insert_ymin_contour_coordinate ( last_point, polygon );
		}
	
		clip_point->next_vertex = NULL;
	
		polygon = clip_list;
	}

	if ( outcode & CLIP_BOTTOM )
	{
	
		//
		// Next clip against the bottom of the viewing rectangle
		//
	
		clip_list = NULL;
	
		clip_point = NULL;
	
		last_point = polygon;
	
		this_point = polygon->next_vertex;
	
		if ( polygon->j <= active_viewport.y_max )
		{
	
			//
			// Start the clipped list off.
			//
	
			clip_list = polygon;
	
			clip_point = polygon;
	
			polygon->next_vertex = NULL;
		}
	
		while ( this_point )
		{
	
			if ( this_point->j <= active_viewport.y_max )
			{
	
				//
				// This point is inside the screen boundary
				//
	
				if ( last_point->j > active_viewport.y_max )
				{
	
					//
					//	The last point isn't in the screen, but this one is, find intersection
					//
	
					insert_ymax_contour_coordinate ( last_point, this_point );
				}
	
				//
				// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put 1.0 in!
				//
	
				clip_point->next_vertex = this_point;
	
				clip_point = this_point;
			}
			else
			{
	
				//
				// This point isn't in the screen area
				//
	
				if ( last_point->j <= active_viewport.y_max )
				{
	
					//
					// The last point was visible - find intersection point
					//
					
					insert_ymax_contour_coordinate ( last_point, this_point );
				}
			}
	
			last_point = this_point;
	
			this_point = this_point->next_vertex;
		}
	
		if ( !clip_point )
		{
	
			return ( NULL );
		}
	
		// Case 0 last point is on screen, first point is on screen			NO ACTION
		//	Case 1 last point is off screen, first point is on screen		GENERATE CLIP
		// Case 2 last point is on screen, first point is off screen		GENERATE CLIP
		// Case 3 last point is off screen, first point is off screen		NO ACTION
	
		if ( ( last_point->j > active_viewport.y_max ) ^ ( polygon->j > active_viewport.y_max ) )
		{
	
			//
			// The last point in the polygon was off the screen, the first one isn't, so add a clip point
			//
	
			insert_ymax_contour_coordinate ( last_point, polygon );
		}
	
		clip_point->next_vertex = NULL;

		polygon = clip_list;
	}

	return ( polygon );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_xmin_contour_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp;

	double
		t,
		numerator,
		denominator;

	float
		red,
		green,
		blue;

	int
		int_red,
		int_dred,
		int_green,
		int_dgreen,
		int_blue,
		int_dblue;

	ASSERT ( clip_3d_coord < MAX_3D_CLIP_COORDINATES );

	if ( point1->j > point2->j )
	{

		tmp = point1;

		point1 = point2;

		point2 = tmp;
	}

	numerator = active_viewport.x_min - point2->i;

	denominator = point2->i - point1->i;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = active_viewport.x_min;
	clip_3d_crds[clip_3d_coord].j = point2->j + ( t * ( point2->j - point1->j ) );
	clip_3d_crds[clip_3d_coord].y = point2->y + ( t * ( point2->y - point1->y ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	if ( !clip_point )
	{

		clip_list = & clip_3d_crds[clip_3d_coord];

		clip_point = clip_list;
	}
	else
	{

		clip_point->next_vertex = & clip_3d_crds[clip_3d_coord];

		clip_point = clip_point->next_vertex;
	}

	clip_3d_coord++;

#if REPORT_CLIP_STATISTICS

	number_of_xmin_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_xmax_contour_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp;

	double
		t,
		numerator,
		denominator;

	float
		red,
		green,
		blue;

	int
		int_red,
		int_dred,
		int_green,
		int_dgreen,
		int_blue,
		int_dblue;

	ASSERT ( clip_3d_coord < MAX_3D_CLIP_COORDINATES );

	if ( point1->j > point2->j )
	{

		tmp = point1;

		point1 = point2;

		point2 = tmp;
	}

	numerator = active_viewport.x_max - point2->i;

	denominator = point2->i - point1->i;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = active_viewport.x_max;
	clip_3d_crds[clip_3d_coord].j = point2->j + ( t * ( point2->j - point1->j ) );
	clip_3d_crds[clip_3d_coord].y = point2->y + ( t * ( point2->y - point1->y ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	if ( ! clip_point )
	{

		clip_list = & clip_3d_crds[clip_3d_coord];

		clip_point = clip_list;
	}
	else
	{

		clip_point->next_vertex = & clip_3d_crds[clip_3d_coord];

		clip_point = clip_point->next_vertex;
	}

	clip_3d_coord ++;

#if REPORT_CLIP_STATISTICS

	number_of_xmax_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_ymin_contour_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp;

	double
		t,
		numerator,
		denominator;

	float
		red,
		green,
		blue;

	int
		int_red,
		int_dred,
		int_green,
		int_dgreen,
		int_blue,
		int_dblue;

	ASSERT ( clip_3d_coord < MAX_3D_CLIP_COORDINATES );

	if ( point1->i > point2->i )
	{

		tmp = point1;

		point1 = point2;

		point2 = tmp;
	}

	numerator = active_viewport.y_min - point2->j;

	denominator = point2->j - point1->j;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = point2->i + ( t * ( point2->i - point1->i ) );
	clip_3d_crds[clip_3d_coord].j = active_viewport.y_min;
	clip_3d_crds[clip_3d_coord].y = point2->y + ( t * ( point2->y - point1->y ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	if ( ! clip_point )
	{

		clip_list = & clip_3d_crds[clip_3d_coord];

		clip_point = clip_list;
	}
	else
	{

		clip_point->next_vertex = & clip_3d_crds[clip_3d_coord];

		clip_point = clip_point->next_vertex;
	}

	clip_3d_coord ++;

#if REPORT_CLIP_STATISTICS

	number_of_ymin_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_ymax_contour_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp;

	double
		t,
		numerator,
		denominator;

	float
		red,
		green,
		blue;

	int
		int_red,
		int_dred,
		int_green,
		int_dgreen,
		int_blue,
		int_dblue;

	ASSERT ( clip_3d_coord < MAX_3D_CLIP_COORDINATES );

	if ( point1->i > point2->i )
	{

		tmp = point1;

		point1 = point2;

		point2 = tmp;
	}

	numerator = active_viewport.y_max - point2->j;

	denominator = point2->j - point1->j;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = point2->i + ( t * ( point2->i - point1->i ) );
	clip_3d_crds[clip_3d_coord].j = active_viewport.y_max;
	clip_3d_crds[clip_3d_coord].y = point2->y + ( t * ( point2->y - point1->y ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	if ( ! clip_point )
	{

		clip_list = &clip_3d_crds[clip_3d_coord];

		clip_point = clip_list;
	}
	else
	{

		clip_point->next_vertex	= &clip_3d_crds[clip_3d_coord];

		clip_point = clip_point->next_vertex;
	}

	clip_3d_coord ++;

#if REPORT_CLIP_STATISTICS

	number_of_ymax_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *bottom_clip_contour_polygon ( vertex *polygon, int *polygon_outcode )
{

	int
		outcode,
		outcode2;

	clip_list = NULL;
	clip_point = NULL;
	last_point = polygon;
	this_point = polygon->next_vertex;

	outcode = 0;
	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	if ( !( polygon->outcode & CLIP_HITHER ) )
	{

		clip_list = polygon;
		clip_point = polygon;

		polygon->next_vertex = NULL;

		outcode |= polygon->outcode;
		outcode2 &= polygon->outcode;
	}

	while ( this_point )
	{

		if ( !( this_point->outcode & CLIP_HITHER ) )
		{

			outcode |= this_point->outcode;
			outcode2 &= this_point->outcode;

			if ( last_point->outcode & CLIP_HITHER )
			{

				insert_bottom_contour_coordinate ( last_point, this_point );

				outcode |= clip_point->outcode;
				outcode2 &= clip_point->outcode;
			}

			clip_point->next_vertex = this_point;

			clip_point = this_point;
		}
		else
		{

			if ( !( last_point->outcode & CLIP_HITHER ) )
			{

				insert_bottom_contour_coordinate ( this_point, last_point );

				outcode |= clip_point->outcode;
				outcode2 &= clip_point->outcode;
			}
		}

		last_point = this_point;

		this_point = this_point->next_vertex;
	}

	if ( ( last_point->outcode & CLIP_HITHER ) ^ ( polygon->outcode & CLIP_HITHER ) )
	{

		if ( last_point->outcode & CLIP_HITHER )
		{
		
			insert_bottom_contour_coordinate ( last_point, polygon );
		}
		else
		{
	
			insert_bottom_contour_coordinate ( polygon, last_point );
		}

		outcode |= clip_point->outcode;
		outcode2 &= clip_point->outcode;
	}

	if ( clip_point )
	{

		clip_point->next_vertex = NULL;

		outcode |= clip_point->outcode;
		outcode2 &= clip_point->outcode;
	}

	if ( ( outcode2 ) || ( !clip_list ) )
	{

		return ( NULL );
	}

	*polygon_outcode = outcode;

	return ( clip_list );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *top_clip_contour_polygon ( vertex *polygon, int *polygon_outcode )
{

	int
		outcode,
		outcode2;

	clip_list = NULL;
	clip_point = NULL;
	last_point = polygon;
	this_point = polygon->next_vertex;

	outcode = 0;
	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	if ( !( polygon->outcode & CLIP_YONDER ) )
	{

		clip_list = polygon;
		clip_point = polygon;

		polygon->next_vertex = NULL;

		outcode |= polygon->outcode;
		outcode2 &= polygon->outcode;
	}

	while ( this_point )
	{

		if ( !( this_point->outcode & CLIP_YONDER ) )
		{

			outcode |= this_point->outcode;
			outcode2 &= this_point->outcode;

			if ( last_point->outcode & CLIP_YONDER )
			{

				insert_top_contour_coordinate ( last_point, this_point );

				outcode |= clip_point->outcode;
				outcode2 &= clip_point->outcode;
			}

			clip_point->next_vertex = this_point;
			clip_point = this_point;
		}
		else
		{

			if ( ! ( last_point->outcode & CLIP_YONDER ) )
			{

				insert_top_contour_coordinate ( this_point, last_point );

				outcode |= clip_point->outcode;
				outcode2 &= clip_point->outcode;
			}
		}

		last_point = this_point;
		this_point = this_point->next_vertex;
	}

	if ( ( last_point->outcode & CLIP_YONDER ) ^ ( polygon->outcode & CLIP_YONDER ) )
	{

		if ( last_point->outcode & CLIP_YONDER )
		{
		
			insert_top_contour_coordinate ( last_point, polygon );
		}
		else
		{
	
			insert_top_contour_coordinate ( polygon, last_point );
		}

		outcode |= clip_point->outcode;
		outcode2 &= clip_point->outcode;
	}

	if ( clip_point )
	{

		clip_point->next_vertex = NULL;

		outcode |= clip_point->outcode;
		outcode2 &= clip_point->outcode;
	}

	if ( ( outcode2 ) || ( !clip_list ) )
	{

		return ( NULL );
	}

	*polygon_outcode = outcode;

	return ( clip_list );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_bottom_contour_coordinate ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip;

	ASSERT ( clip_3d_coord < MAX_3D_CLIP_COORDINATES );

	t = ( ( contour_minimum_height - point2->y ) / ( point2->y - point1->y ) );

	clip = &clip_3d_crds[clip_3d_coord];

	clip_3d_coord++;

	if ( !clip_point )
	{

		clip_list = clip;

		clip_point = clip_list;
	}
	else
	{

		clip_point->next_vertex	= clip;

		clip_point = clip_point->next_vertex;
	}

	clip->i = point2->i + ( t * ( point2->i - point1->i ) );
	clip->j = point2->j + ( t * ( point2->j - point1->j ) );
	clip->outcode = generate_contour_outcode ( clip->i, clip->j );
	clip->y = contour_minimum_height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_top_contour_coordinate ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip;

	ASSERT ( clip_3d_coord < MAX_3D_CLIP_COORDINATES );

	t = ( ( contour_maximum_height - point2->y ) / ( point2->y - point1->y ) );

	clip = &clip_3d_crds[clip_3d_coord];

	clip_3d_coord++;

	if ( !clip_point )
	{

		clip_list = clip;

		clip_point = clip_list;
	}
	else
	{

		clip_point->next_vertex	= clip;

		clip_point = clip_point->next_vertex;
	}

	clip->i = point2->i + ( t * ( point2->i - point1->i ) );
	clip->j = point2->j + ( t * ( point2->j - point1->j ) );
	clip->outcode = generate_contour_outcode ( clip->i, clip->j );
	clip->y = contour_maximum_height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


