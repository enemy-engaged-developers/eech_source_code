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

//VJ 030423 TSD render mod
// common functions used by all choppers

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static rgb_colour
		terrain_colour[33];

static int 
	draw_large_mfd;

static int
	contour_spacing,
	contour_samples;

#define OPTIMISE_CONTOURS	0

#define OPTIMISE_PATHS		0


#if OPTIMISE_CONTOURS
static int
	num_contour_loops,
	num_contour_lines;
#endif


#define elevation_factor terrain_3d_map_maximum_height

#define colour_base 32
#define colour_scale(a) min(colour_base,(int)(colour_base*a/elevation_factor)+1);			   	   			   

#define TSD_ASE_RANGE_2000		((float) 2000.0)
#define TSD_ASE_RANGE_5000		((float) 5000.0)
#define TSD_ASE_RANGE_10000	((float) 10000.0)
#define TSD_ASE_RANGE_25000	((float) 25000.0)

static rgb_colour
		dummy_colours[11];

#define MFD_COLOUR1 		  		(dummy_colours[0])
#define MFD_COLOUR2 		  		(dummy_colours[1])
#define MFD_COLOUR3 		  		(dummy_colours[2])
#define MFD_COLOUR4	  	  		(dummy_colours[3])
#define MFD_COLOUR5				(dummy_colours[4])
#define MFD_COLOUR6				(dummy_colours[5])
#define MFD_CONTOUR_COLOUR		(dummy_colours[6])
#define MFD_RIVER_COLOUR		(dummy_colours[7])
#define MFD_ROAD_COLOUR			(dummy_colours[8])
#define MFD_BACKGROUND_COLOUR	(dummy_colours[9])
#define clear_mfd_colour		(dummy_colours[10])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void set_tsd_colours(void)
{
		set_rgb_colour (MFD_COLOUR1,   0, 0,  96, 255);  //dark blue
	   set_rgb_colour (MFD_COLOUR2,	32, 32,  164, 255); //light blue
		set_rgb_colour (MFD_COLOUR3, 220, 48,   0, 255); //bright red
		set_rgb_colour (MFD_COLOUR4, 148, 32,   0, 255);//dark red
		set_rgb_colour (MFD_COLOUR5,   0, 128,   192, 255);
		set_rgb_colour (MFD_COLOUR6,  255, 255,  0, 255);
	
		set_rgb_colour (MFD_CONTOUR_COLOUR,      48, 48,  48, 255);
		set_rgb_colour (MFD_RIVER_COLOUR,        50,  75, 225, 255);
//		set_rgb_colour (MFD_ROAD_COLOUR,        255, 220,   0, 255);
		set_rgb_colour (MFD_ROAD_COLOUR,        64,64,64, 255);
		set_rgb_colour (clear_mfd_colour,        255,255,255,255);
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_tsd_colours(void)
{
	set_rgb_colour (MFD_COLOUR1,              0, 255,   0, 255);
	set_rgb_colour (MFD_COLOUR2,              0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,              0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,              0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,              0, 128,   0, 255);
	set_rgb_colour (MFD_COLOUR6,             40,  68,  56, 255);

	set_rgb_colour (MFD_CONTOUR_COLOUR,     255, 100,   0, 255);
	set_rgb_colour (MFD_RIVER_COLOUR,        50,  75, 225, 255);
	set_rgb_colour (MFD_ROAD_COLOUR,        255, 200,   0, 255);
	set_rgb_colour (clear_mfd_colour,        255,255,255,0);
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Initialise_TSD_render_terrain(void)
{
	draw_large_mfd = TRUE;
	
	set_tsd_colours();
	
	set_rgb_colour(terrain_colour[0	],100,	150,	240,	255);	
	set_rgb_colour(terrain_colour[1	],	70	,	208,	106,	255);
	set_rgb_colour(terrain_colour[2	],	92	,	213,	115,	255);
	set_rgb_colour(terrain_colour[3	],	114,	219,	124,	255);
	set_rgb_colour(terrain_colour[4	],	135,	224,	133,	255);
	set_rgb_colour(terrain_colour[5	],	157,	230,	142,	255);
	set_rgb_colour(terrain_colour[6	],	179,	235,	151,	255);
	set_rgb_colour(terrain_colour[7	],	201,	241,	160,	255);
	set_rgb_colour(terrain_colour[8	],	222,	246,	169,	255);
	set_rgb_colour(terrain_colour[9	],	244,	252,	178,	255);
	set_rgb_colour(terrain_colour[10	],	251,	246,	190,	255);
	set_rgb_colour(terrain_colour[11	],	248,	241,	182,	255);
	set_rgb_colour(terrain_colour[12	],	244,	237,	173,	255);
	set_rgb_colour(terrain_colour[13	],	241,	232,	165,	255);
	set_rgb_colour(terrain_colour[14	],	238,	228,	157,	255);
	set_rgb_colour(terrain_colour[15	],	235,	223,	149,	255);
	set_rgb_colour(terrain_colour[16	],	232,	219,	141,	255);
	set_rgb_colour(terrain_colour[17	],	229,	214,	133,	255);
	set_rgb_colour(terrain_colour[18	],	225,	210,	125,	255);
	set_rgb_colour(terrain_colour[19	],	222,	205,	117,	255);
	set_rgb_colour(terrain_colour[20	],	219,	201,	109,	255);
	set_rgb_colour(terrain_colour[21	],	216,	196,	101,	255);
	set_rgb_colour(terrain_colour[22	],	213,	192,	93,	255);
	set_rgb_colour(terrain_colour[23	],	210,	187,	85,	255);
	set_rgb_colour(terrain_colour[24	],	206,	183,	77,	255);
	set_rgb_colour(terrain_colour[25	],	203,	178,	69,	255);
	set_rgb_colour(terrain_colour[26	],	200,	174,	61,	255);
	set_rgb_colour(terrain_colour[27	],	197,	169,	53,	255);
	set_rgb_colour(terrain_colour[28	],	194,	164,	45,	255);
	set_rgb_colour(terrain_colour[29	],	191,	160,	37,	255);
	set_rgb_colour(terrain_colour[30	],	187,	155,	29,	255);
	set_rgb_colour(terrain_colour[31	],	184,	151,	21,	255);
	set_rgb_colour(terrain_colour[32	],	181,	146,	13,	255);
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_contour_lines (vec3d *p1, vec3d *p2, vec3d *p3)
{
	int
		y,
		y1,
		y2,
		y3,
		dy,
		y_tmp,
		contour_samples_minus_one;

	float
		x1,
		z1,
		x2,
		z2,
		x3,
		z3,
		dx1,
		dz1,
		dx2,
		dz2,
		x_tmp,
		z_tmp,
		one_over_dy;

	x1 = p1->x;
	convert_float_to_int (p1->y, &y1);
	z1 = p1->z;

	x2 = p2->x;
	convert_float_to_int (p2->y, &y2);
	z2 = p2->z;

	x3 = p3->x;
	convert_float_to_int (p3->y, &y3);
	z3 = p3->z;

	//
	// ensure above sea level
	//

	y1 = max (y1, 0);

	y2 = max (y2, 0);

	y3 = max (y3, 0);

	//
	// scale height values for contour line spacing
	//

	y1 /= contour_spacing;
	y2 /= contour_spacing;
	y3 /= contour_spacing;

	contour_samples_minus_one = contour_samples - 1;

	//
	// check if flat
	//

	if ((y1 == y2) && (y2 == y3))
	{
		return;
	}

	//
	// sort height values (y1 = lowest, y3 = highest)
	//

	if (y1 > y3)
	{
		x_tmp = x1;
		y_tmp = y1;
		z_tmp = z1;

		x1 = x3;
		y1 = y3;
		z1 = z3;

		x3 = x_tmp;
		y3 = y_tmp;
		z3 = z_tmp;
	}

	if (y2 > y3)
	{
		x_tmp = x2;
		y_tmp = y2;
		z_tmp = z2;

		x2 = x3;
		y2 = y3;
		z2 = z3;

		x3 = x_tmp;
		y3 = y_tmp;
		z3 = z_tmp;
	}

	if (y1 > y2)
	{
		x_tmp = x1;
		y_tmp = y1;
		z_tmp = z1;

		x1 = x2;
		y1 = y2;
		z1 = z2;

		x2 = x_tmp;
		y2 = y_tmp;
		z2 = z_tmp;
	}

	//
	// draw contour lines
	//

	if (y1 == y2)
	{
		dy = y3 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx1 = (x3 - x1) * one_over_dy;
		dz1 = (z3 - z1) * one_over_dy;
		dx2 = (x3 - x2) * one_over_dy;
		dz2 = (z3 - z2) * one_over_dy;

		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);
			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}
	}
	else if (y2 == y3)
	{
		dy = y2 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx1 = (x2 - x1) * one_over_dy;
		dz1 = (z2 - z1) * one_over_dy;
		dx2 = (x3 - x1) * one_over_dy;
		dz2 = (z3 - z1) * one_over_dy;

		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);

		x2 = x1;
		z2 = z1;

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);

			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}
	}
	else
	{
		dy = y3 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx1 = (x3 - x1) * one_over_dy;
		dz1 = (z3 - z1) * one_over_dy;

		dy = y2 - y1;

		one_over_dy = 1.0 / (float) dy;

		dx2 = (x2 - x1) * one_over_dy;
		dz2 = (z2 - z1) * one_over_dy;

		y = contour_samples_minus_one - ((y1 - 1) % contour_samples);

		x2 = x1;
		z2 = z1;

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);

			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}

		dy = y3 - y2;

		one_over_dy = 1.0 / (float) dy;

		dx2 = (x3 - x2) * one_over_dy;
		dz2 = (z3 - z2) * one_over_dy;

		y = contour_samples_minus_one - ((y2 - 1) % contour_samples);

		while (dy--)
		{
			#if OPTIMISE_CONTOURS

			num_contour_loops++;

			#endif

			if (y == 0)
			{
				#if OPTIMISE_CONTOURS

				num_contour_lines++;

				#endif

				y = contour_samples;

				draw_2d_line (x1, z1, x2, z2, MFD_CONTOUR_COLOUR);
			}

			y--;

			x1 += dx1;
			z1 += dz1;
			x2 += dx2;
			z2 += dz2;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_path_lines
(
	int number_of_paths,
	contour_path *paths,
	vec3d *nodes,
	rgb_colour colour,
	int detail_level,
	float x_world_min,
	float z_world_min,
	float x_world_mid,
	float z_world_mid,
	float x_world_max,
	float z_world_max,
	float scale,
	int draw_thick_lines,
	int draw_large_mfd
)
{
	int
		this_path,
		outcode1,
		outcode2,
		index,
		step_size;

	#if OPTIMISE_PATHS

	int
		num_paths_traversed,
		num_lines_drawn;

	#endif

	float
		x1,
		z1,
		x2,
		z2;

	vec3d
		*sub_positions;

	ASSERT (number_of_paths > 0);

	ASSERT (paths);

	ASSERT (nodes);

	#if OPTIMISE_PATHS

	num_paths_traversed = 0;

	num_lines_drawn = 0;

	#endif

	step_size = max (detail_level << 3, 1);

	for (this_path = 0; this_path < number_of_paths; this_path++)
	{
		if
		(
			(paths[this_path].type != TEMP_TERRAIN_TYPE_COASTAL_RIVER) &&
			(paths[this_path].type != TEMP_TERRAIN_TYPE_LAKE) &&
			(paths[this_path].type != TEMP_TERRAIN_TYPE_OFFROAD)
		)
		{
			//
			// trivially reject path
			//

			outcode1 = 0;

			if (paths[this_path].xmin < x_world_min) outcode1 |= CLIP_LEFT;
			if (paths[this_path].xmin > x_world_max) outcode1 |= CLIP_RIGHT;
			if (paths[this_path].zmin < z_world_min) outcode1 |= CLIP_TOP;
			if (paths[this_path].zmin > z_world_max) outcode1 |= CLIP_BOTTOM;

			outcode2 = 0;

			if (paths[this_path].xmax < x_world_min) outcode2 |= CLIP_LEFT;
			if (paths[this_path].xmax > x_world_max) outcode2 |= CLIP_RIGHT;
			if (paths[this_path].zmax < z_world_min) outcode2 |= CLIP_TOP;
			if (paths[this_path].zmax > z_world_max) outcode2 |= CLIP_BOTTOM;

			if (!(outcode1 & outcode2))
			{
				#if OPTIMISE_PATHS

				num_paths_traversed++;

				#endif

				//
				// this also catches conditions where (count == 0)
				//

				if (paths[this_path].count <= step_size)
				{
					////////////////////////////////////////
					//
					// draw path as a single line
					//
					////////////////////////////////////////

					x1 = (nodes[paths[this_path].from].x - x_world_mid) * scale;
					z1 = (nodes[paths[this_path].from].z - z_world_mid) * scale;

					x2 = (nodes[paths[this_path].to].x - x_world_mid) * scale;
					z2 = (nodes[paths[this_path].to].z - z_world_mid) * scale;

					if (draw_thick_lines && draw_large_mfd)
					{
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}
					else
					{
						draw_2d_line (x1, z1, x2, z2, colour);
					}

					#if OPTIMISE_PATHS

					num_lines_drawn++;

					#endif
				}
				else
				{
					////////////////////////////////////////
					//
					// draw path with variable detail level
					//
					////////////////////////////////////////

					sub_positions = paths[this_path].points;

					index = step_size - 1;;

					//
					// draw line from start node to first sub-position
					//

					x1 = (nodes[paths[this_path].from].x - x_world_mid) * scale;
					z1 = (nodes[paths[this_path].from].z - z_world_mid) * scale;

					x2 = (sub_positions[index].x - x_world_mid) * scale;
					z2 = (sub_positions[index].z - z_world_mid) * scale;

					if (draw_thick_lines && draw_large_mfd)
					{
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}
					else
					{
						draw_2d_line (x1, z1, x2, z2, colour);
					}

					#if OPTIMISE_PATHS

					num_lines_drawn++;

					#endif

					//
					// draw sub-position lines
					//

					index += step_size;

					while (index < paths[this_path].count)
					{
						x1 = x2;
						z1 = z2;

						x2 = (sub_positions[index].x - x_world_mid) * scale;
						z2 = (sub_positions[index].z - z_world_mid) * scale;

						if (draw_thick_lines && draw_large_mfd)
						{
							draw_2d_half_thick_line (x1, z1, x2, z2, colour);
						}
						else
						{
							draw_2d_line (x1, z1, x2, z2, colour);
						}

						#if OPTIMISE_PATHS

						num_lines_drawn++;

						#endif

						index += step_size;
					}

					//
					// draw line from last sub-position to end node
					//

					x1 = x2;
					z1 = z2;

					x2 = (nodes[paths[this_path].to].x - x_world_mid) * scale;
					z2 = (nodes[paths[this_path].to].z - z_world_mid) * scale;

					if (draw_thick_lines && draw_large_mfd)
					{
						draw_2d_half_thick_line (x1, z1, x2, z2, colour);
					}
					else
					{
						draw_2d_line (x1, z1, x2, z2, colour);
					}

					#if OPTIMISE_PATHS

					num_lines_drawn++;

					#endif
				}
			}
		}
	}

	#if OPTIMISE_PATHS

	debug_filtered_log ("paths=%d, paths drawn=%d, lines drawn=%d", number_of_paths, num_paths_traversed, num_lines_drawn);

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_tsd_terrain_map (env_2d *mfd_env, float y_translate, float range, float scale, vec3d *position, float heading)
{
	int
		x_index,
		z_index,
		row_add_on,
		x_min_index,
		z_min_index,
		x_max_index,
		z_max_index;

	float
		x_min,
		z_min,
		x_mid,
		z_mid,
		x_max,
		z_max,
		radius,
		distance,
		dx0,
		dz0,
		dx1,
		dz1,
		dx_grid,
		dz_grid,
		dx_start,
		dz_start,
		*this_row_ptr,
		*next_row_ptr,
		*this_row_start_ptr,
		*next_row_start_ptr;

		float 
			terrain_elev=0;
		rgb_colour 
			terrain_col;

      int step = 1;
      int stepmask;

	ASSERT (position);


	//
	// rotate map
	//

	set_2d_window_rotation (mfd_env, heading);

	//
	// get map centre position
	//

	distance = y_translate / scale;

	x_mid = position->x + (distance * sin (heading));
	z_mid = position->z + (distance * cos (heading));

	//
	// get map area (increased by one grid, where hypotenuse is approx (x + z))
	//

	radius = range + terrain_3d_simple_elevation_x_grid_size + terrain_3d_simple_elevation_z_grid_size;

	x_min = x_mid - radius;
	z_min = z_mid - radius;

	x_max = x_mid + radius;
	z_max = z_mid + radius;

	//
	// clip map area
	//

	x_min = max (x_min, MIN_MAP_X);
	z_min = max (z_min, MIN_MAP_Z);

	x_max = min (x_max, MAX_MAP_X);
	z_max = min (z_max, MAX_MAP_Z);


	//
	// get simple terrain map indices
	//

	convert_float_to_int ((x_min * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_min_index);
	convert_float_to_int ((z_min * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_min_index);

	convert_float_to_int ((x_max * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_max_index);
	convert_float_to_int ((z_max * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_max_index);

   if (range == TSD_ASE_RANGE_25000)
     step = 2;
   stepmask = ~(step - 1);

	//
	// scan map
	//

	x_min_index &= stepmask;
	z_min_index &= stepmask;

	x_max_index += step - 1;
	z_max_index += step - 1;

	x_max_index &= stepmask;
	z_max_index &= stepmask;

	if (x_max_index >= terrain_3d_simple_elevation_width)
	{
		x_max_index = terrain_3d_simple_elevation_width & stepmask;
	}

	if (z_max_index >= terrain_3d_simple_elevation_height)
	{
		z_max_index = terrain_3d_simple_elevation_height & stepmask;
	}

	if ((x_min_index < x_max_index) && (z_min_index < z_max_index))
	{		
		this_row_start_ptr = &terrain_3d_simple_elevation_grid[(z_min_index * terrain_3d_simple_elevation_width) + x_min_index];

		row_add_on = terrain_3d_simple_elevation_width * step;

		next_row_start_ptr = this_row_start_ptr + row_add_on;

		dx_start = ((((float) x_min_index) * terrain_3d_simple_elevation_x_grid_size) - x_mid) * scale;
		dz_start = ((((float) z_min_index) * terrain_3d_simple_elevation_z_grid_size) - z_mid) * scale;

		dx_grid = terrain_3d_simple_elevation_x_grid_size * (float) step * scale;
		dz_grid = terrain_3d_simple_elevation_z_grid_size * (float) step * scale;

		dz0 = dz_start;
		dz1 = dz_start + dz_grid;

		for (z_index = z_min_index; z_index < z_max_index; z_index += step)
		{			
			float mid_x, mid_z, mid_y;			

			dx0 = dx_start;
			dx1 = dx_start + dx_grid;

			mid_z = 0.5*(dz0+dz1);

			this_row_ptr = this_row_start_ptr;
			next_row_ptr = next_row_start_ptr;

			for (x_index = x_min_index; x_index < x_max_index; x_index += step)
			{
				int c = 0;
				mid_x = 0.5*(dx0+dx1);
			   mid_y = (this_row_ptr[0]+this_row_ptr[1]+next_row_ptr[0]+next_row_ptr[1])/4.0;

			   terrain_elev = (this_row_ptr[0]+this_row_ptr[1]+mid_y)/3.0;			   
		   	c = colour_scale(terrain_elev);
			   if (terrain_elev > 0)
			   	terrain_col = terrain_colour[c];			   	
			   else
			   	terrain_col = terrain_colour[0];
			   draw_2d_filled_triangle (dx0,dz0,mid_x,mid_z,dx1,dz0,terrain_col);
			                                                                 
			   terrain_elev = (this_row_ptr[1]+next_row_ptr[1]+mid_y)/3.0;   
		   	c = colour_scale(terrain_elev);
			   if (terrain_elev > 0)
			   	terrain_col = terrain_colour[c];			   	
			   else
			   	terrain_col = terrain_colour[0];
			   draw_2d_filled_triangle (dx1,dz0,mid_x,mid_z,dx1,dz1,terrain_col);
                                                                          
			   terrain_elev = (this_row_ptr[0]+next_row_ptr[0]+mid_y)/3.0;   
		   	c = colour_scale(terrain_elev);
			   if (terrain_elev > 0)
			   	terrain_col = terrain_colour[c];			   	
			   else
			   	terrain_col = terrain_colour[0];
			   draw_2d_filled_triangle (dx0,dz0,dx0,dz1,mid_x,mid_z,terrain_col);
                                                                          
			   terrain_elev = (next_row_ptr[0]+next_row_ptr[1]+mid_y)/3.0;   
		   	c = colour_scale(terrain_elev);
			   if (terrain_elev > 0)
			   	terrain_col = terrain_colour[c];			   	
			   else
			   	terrain_col = terrain_colour[0];
			   draw_2d_filled_triangle (dx0,dz1,dx1,dz1,mid_x,mid_z,terrain_col);			   
			                                                                                       
				//                                  
				// next column                      
				//                                  
                                                
				dx0 += dx_grid;                     
				dx1 += dx_grid;                     
                                                
				this_row_ptr += step;                  
				next_row_ptr += step;                  
			}                                      
                                                
			//                                     
			// next row                            
			//                                     
                                                
			dz0 += dz_grid;                        
			dz1 += dz_grid;                        

			this_row_start_ptr += row_add_on;
			next_row_start_ptr += row_add_on;
		}
	}

	set_2d_window_rotation (mfd_env, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_tsd_contour_map (env_2d *mfd_env, float y_translate, float range, float scale, vec3d *position, float heading, int draw_large_mfd)
{
	int
		x_index,
		z_index,
		row_add_on,
		x_min_index,
		z_min_index,
		x_max_index,
		z_max_index,
		path_detail_level,
		contour_granularity,
		contour_granularity_mask;

	float
		x_min,
		z_min,
		x_mid,
		z_mid,
		x_max,
		z_max,
		radius,
		distance,
		dx0,
		dz0,
		dx1,
		dz1,
		dx_grid,
		dz_grid,
		dx_start,
		dz_start,
		*this_row_ptr,
		*next_row_ptr,
		*this_row_start_ptr,
		*next_row_start_ptr;

	vec3d
		p1,
		p2,
		p3;

	ASSERT (position);

	#if OPTIMISE_CONTOURS

	num_contour_loops = 0;

	num_contour_lines = 0;

	#endif

	if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
	  reset_tsd_colours();
	else  
	  set_tsd_colours();

	//
	// rotate map
	//

	set_2d_window_rotation (mfd_env, heading);

	//
	// get map centre position
	//

	distance = y_translate / scale;

	x_mid = position->x + (distance * sin (heading));
	z_mid = position->z + (distance * cos (heading));

	//
	// get map area (increased by one grid, where hypotenuse is approx (x + z))
	//

	radius = range + terrain_3d_simple_elevation_x_grid_size + terrain_3d_simple_elevation_z_grid_size;

	x_min = x_mid - radius;
	z_min = z_mid - radius;

	x_max = x_mid + radius;
	z_max = z_mid + radius;

	//
	// clip map area
	//

	x_min = max (x_min, MIN_MAP_X);
	z_min = max (z_min, MIN_MAP_Z);

	x_max = min (x_max, MAX_MAP_X);
	z_max = min (z_max, MAX_MAP_Z);

	////////////////////////////////////////
	//
	// DRAW CONTOURS
	//
	////////////////////////////////////////

	//
	// get simple terrain map indices
	//

	convert_float_to_int ((x_min * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_min_index);
	convert_float_to_int ((z_min * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_min_index);

	convert_float_to_int ((x_max * terrain_3d_simple_elevation_x_grid_size_reciprocal), &x_max_index);
	convert_float_to_int ((z_max * terrain_3d_simple_elevation_z_grid_size_reciprocal), &z_max_index);

	////////////////////////////////////////
	//
	// contour_granularity: chunks the terrain grid
	// contour_samples    : culls the number of contour line samples
	// contour_spacing    : height between contour lines (meters)
	// path_detail_level  : 0 = highest detail (ie draw all sub-lines)
	//
	////////////////////////////////////////

	////////////////////////////////////////
	if (range == TSD_ASE_RANGE_2000)
	////////////////////////////////////////
	{
		contour_granularity = 1;

		contour_samples = 5;

		contour_spacing = 100;

		if (draw_large_mfd)
		{
			path_detail_level = 0;
		}
		else
		{
			path_detail_level = 2;
		}
	}
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_5000)
	////////////////////////////////////////
	{
		if (draw_large_mfd)
		{
			contour_granularity = 1;

			contour_samples = 10;

			path_detail_level = 0;
		}
		else
		{
			contour_granularity = 2;

			contour_samples = 10;

			path_detail_level = 2;
		}

		contour_spacing = 100;
	}
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_10000)
	////////////////////////////////////////
	{
		if (draw_large_mfd)
		{
			contour_granularity = 2;

			contour_samples = 10;

			path_detail_level = 1;
		}
		else
		{
			contour_granularity = 4;

			contour_samples = 20;

			path_detail_level = 3;
		}

		contour_spacing = 100;
	}
	
	////////////////////////////////////////
	else if (range == TSD_ASE_RANGE_25000)
	////////////////////////////////////////
	{
		if (draw_large_mfd)
		{
			contour_granularity = 4;

			contour_samples = 10;

			path_detail_level = 2;
		}
		else
		{
			contour_granularity = 8;

			contour_samples = 15;

			path_detail_level = 4;
		}

		contour_spacing = 250;
	}
	
	////////////////////////////////////////
	else
	///////////////////////////////////////
	{
		debug_fatal ("Unknown TSD/ASE range %.2f", range);
	}


if (tsd_render_mode != TSD_RENDER_RELIEF_MODE)
{	


	contour_spacing /= contour_samples;

	contour_granularity_mask = ~(contour_granularity - 1);

	//
	// scan map
	//

	x_min_index &= contour_granularity_mask;
	z_min_index &= contour_granularity_mask;

	x_max_index += contour_granularity - 1;
	z_max_index += contour_granularity - 1;

	x_max_index &= contour_granularity_mask;
	z_max_index &= contour_granularity_mask;

	if (x_max_index >= terrain_3d_simple_elevation_width)
	{
		x_max_index = terrain_3d_simple_elevation_width & contour_granularity_mask;
	}

	if (z_max_index >= terrain_3d_simple_elevation_height)
	{
		z_max_index = terrain_3d_simple_elevation_height & contour_granularity_mask;
	}

	if ((x_min_index < x_max_index) && (z_min_index < z_max_index))
	{		
		this_row_start_ptr = &terrain_3d_simple_elevation_grid[(z_min_index * terrain_3d_simple_elevation_width) + x_min_index];

		row_add_on = terrain_3d_simple_elevation_width * contour_granularity;

		next_row_start_ptr = this_row_start_ptr + row_add_on;

		dx_start = ((((float) x_min_index) * terrain_3d_simple_elevation_x_grid_size) - x_mid) * scale;
		dz_start = ((((float) z_min_index) * terrain_3d_simple_elevation_z_grid_size) - z_mid) * scale;

		dx_grid = terrain_3d_simple_elevation_x_grid_size * (float) contour_granularity * scale;
		dz_grid = terrain_3d_simple_elevation_z_grid_size * (float) contour_granularity * scale;

		dz0 = dz_start;
		dz1 = dz_start + dz_grid;

		for (z_index = z_min_index; z_index < z_max_index; z_index += contour_granularity)
		{			
			dx0 = dx_start;
			dx1 = dx_start + dx_grid;

			this_row_ptr = this_row_start_ptr;
			next_row_ptr = next_row_start_ptr;

			for (x_index = x_min_index; x_index < x_max_index; x_index += contour_granularity)
			{
				//
				// offset [z=0][x=0]
				//

				p1.x = dx0;
				p1.y = this_row_ptr[0];
				p1.z = dz0;

				//
				// offset [z=0][x=1]
				//

				p2.x = dx1;
				p2.y = this_row_ptr[contour_granularity];
				p2.z = dz0;

				//
				// offset [z=1][x=0]
				//

				p3.x = dx0;
				p3.y = next_row_ptr[0];
				p3.z = dz1;

            
				draw_contour_lines (&p1, &p2, &p3);

				//
				// offset [z=1][x=1]
				//

				p1.x = dx1;
				p1.y = next_row_ptr[contour_granularity];
				p1.z = dz1;


				draw_contour_lines (&p1, &p2, &p3);

				//
				// next column
				//

				dx0 += dx_grid;
				dx1 += dx_grid;

				this_row_ptr += contour_granularity;
				next_row_ptr += contour_granularity;
			}

			//
			// next row
			//

			dz0 += dz_grid;
			dz1 += dz_grid;

			this_row_start_ptr += row_add_on;
			next_row_start_ptr += row_add_on;
		}
	}

	#if OPTIMISE_CONTOURS

	debug_filtered_log ("num_contour_loops = %d, num_contour_lines = %d", num_contour_loops, num_contour_lines);

	#endif
}
	////////////////////////////////////////
	//
	// DRAW RIVERS
	//
	////////////////////////////////////////

	draw_path_lines
	(
		contour_map_number_of_river_paths,
		contour_map_river_paths,
		contour_map_river_nodes,
		MFD_RIVER_COLOUR,
		path_detail_level,
		x_min,
		z_min,
		x_mid,
		z_mid,
		x_max,
		z_max,
		scale,
		TRUE,
		draw_large_mfd
	);

	////////////////////////////////////////
	//
	// DRAW ROADS
	//
	////////////////////////////////////////

	draw_path_lines
	(
		contour_map_number_of_road_paths,
		contour_map_road_paths,
		contour_map_road_nodes,
		MFD_ROAD_COLOUR,
		path_detail_level,
		x_min,
		z_min,
		x_mid,
		z_mid,
		x_max,
		z_max,
		scale,
		FALSE,
		draw_large_mfd
	);

	//
	// reset window rotation
	//

	set_2d_window_rotation (mfd_env, 0.0);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
