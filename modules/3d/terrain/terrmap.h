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

struct CONTOUR_PATH
{

	int
		from,
		to,
		type,
		count;

	float
		xmin,
		xmax,
		zmin,
		zmax;

	vec3d
		*points;
};

typedef struct CONTOUR_PATH contour_path;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CONTOUR_LAKE
{

	int
		number_of_triangles;

	float
		xmin,
		xmax,
		zmin,
		zmax;

	vec3d
		*triangle_points;
};

typedef struct CONTOUR_LAKE contour_lake;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	terrain_2d_map_contour_lines_drawn;

extern vec3d
	*contour_map_river_nodes,
	*contour_map_river_path_positions,
	*contour_map_road_nodes,
	*contour_map_road_path_positions;

extern contour_path
	*contour_map_river_paths,
	*contour_map_road_paths;

extern int
	contour_map_number_of_mipmaps,
	contour_map_number_of_river_nodes,
	contour_map_number_of_river_paths,
	contour_map_number_of_road_nodes,
	contour_map_number_of_road_paths,
	number_of_contour_lakes;

extern float
	**contour_map_mipmaps;

extern contour_lake
	*contour_lakes;

extern vec3d
	*contour_lake_vertices;

extern float
	contour_minimum_height,
	contour_maximum_height;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_2d_terrain_map_textured ( int flag );

extern void draw_2d_terrain_map ( void );

extern void generate_2d_terrain_contour_mipmaps ( void );

extern void set_2d_terrain_contour_colour ( int flag );

extern void set_2d_terrain_contour_heights ( int number_of_heights, float *heights );

extern void load_2d_terrain ( const char *path );

extern void unload_2d_terrain ( void );

extern void load_contour_map_colours ( const char *filename );

extern float check_coastal_river_intersection ( float x1, float z1, float x2, float z2 );

extern void draw_2d_terrain_contour_map ( void );

extern void set_2d_terrain_map_dimensions ( float world_xmin, float world_zmin, float world_xmax, float world_zmax,
													float screen_xmin, float screen_ymin, float screen_xmax, float screen_ymax );

extern void get_2d_terrain_map_world_dimensions ( float *wxmin, float *wzmin, float *wxmax, float *wzmax );

extern void get_2d_terrain_map_screen_dimensions ( float *sxmin, float *symin, float *sxmax, float *symax );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
