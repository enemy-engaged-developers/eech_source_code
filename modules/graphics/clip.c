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

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REPORT_CLIP_STATISTICS 0

//
// Allocate an array of clip coordinates ( slightly bigger - incase on optimised make we get an overflow! )
//

vertex
	clip_3d_crds[64];

int
	clip_3d_coord;
#endif

float
	clip_hither_reciprocal,
	clip_hither,
	clip_yonder_reciprocal,
	clip_yonder;

#ifndef OGRE_EE
static vertex
	*this_point = nullptr,
	*last_point = nullptr,
	*clip_list = nullptr,
	*clip_point = nullptr;

int
	number_of_xmin_coordinates_inserted,
	number_of_xmax_coordinates_inserted,
	number_of_ymin_coordinates_inserted,
	number_of_ymax_coordinates_inserted,
	number_of_polygons_screen_clipped;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_xmin_coordinate ( vertex *point1, vertex *point2 );

void insert_xmax_coordinate ( vertex *point1, vertex *point2 );

void insert_ymin_coordinate ( vertex *point1, vertex *point2 );

void insert_ymax_coordinate ( vertex *point1, vertex *point2 );

void insert_xmin_dual_texture_coordinate ( vertex *point1, vertex *point2 );

void insert_xmax_dual_texture_coordinate ( vertex *point1, vertex *point2 );

void insert_ymin_dual_texture_coordinate ( vertex *point1, vertex *point2 );

void insert_ymax_dual_texture_coordinate ( vertex *point1, vertex *point2 );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_clip_system ( void )
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_clip_statistics ( void )
{

	number_of_xmin_coordinates_inserted = 0;

	number_of_xmax_coordinates_inserted = 0;

	number_of_ymin_coordinates_inserted = 0;

	number_of_ymax_coordinates_inserted = 0;

	number_of_polygons_screen_clipped = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_clip_statistics ( void )
{

#if REPORT_CLIP_STATISTICS

	debug_log ( "Hither clipped: %d, Yonder clipped: %d, Screen clipped: %d",
							number_of_polygons_hither_clipped,
							number_of_polygons_yonder_clipped,
							number_of_polygons_screen_clipped );

	debug_log ( "Near inserted: %d, Far inserted: %d",
							number_of_near_coordinates_inserted,
							number_of_far_coordinates_inserted );

	debug_log ( "Xmin inserted: %d, Xmax inserted: %d",
							number_of_xmin_coordinates_inserted,
							number_of_xmax_coordinates_inserted );

	debug_log ( "Ymin inserted: %d, Ymax inserted: %d",
							number_of_ymin_coordinates_inserted,
							number_of_ymax_coordinates_inserted );

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

void set_3d_clip_extents ( float yonder, float hither, float xmin, float ymin, float xmax, float ymax, float zbuffer_zmin, float zbuffer_zmax )
{

	clip_yonder = yonder;

	clip_yonder_reciprocal = 1.0 / yonder;

	clip_hither = hither;

	clip_hither_reciprocal = 1.0 / hither;

	set_full_viewport ( xmin, ymin, xmax, ymax, zbuffer_zmin, zbuffer_zmax );

#ifndef OGRE_EE
	set_zbuffer_parameters ( hither, yonder, zbuffer_zmin, zbuffer_zmax );
#endif
}

#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *clip_3d_polygon ( vertex *polygon, int outcode )
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
	
					insert_xmin_coordinate ( last_point, this_point );
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
					
					insert_xmin_coordinate ( last_point, this_point );
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
	
			insert_xmin_coordinate ( last_point, polygon );
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
	
					insert_xmax_coordinate ( last_point, this_point );
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
					
					insert_xmax_coordinate ( last_point, this_point );
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
	
			insert_xmax_coordinate ( last_point, polygon );
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
	
					insert_ymin_coordinate ( last_point, this_point );
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
					
					insert_ymin_coordinate ( last_point, this_point );
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
	
			insert_ymin_coordinate ( last_point, polygon );
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
	
					insert_ymax_coordinate ( last_point, this_point );
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
					
					insert_ymax_coordinate ( last_point, this_point );
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
	
			insert_ymax_coordinate ( last_point, polygon );
		}
	
		clip_point->next_vertex = NULL;

		polygon = clip_list;
	}

	return ( polygon );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *clip_3d_dual_texture_polygon ( vertex *polygon, int outcode )
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
	
					insert_xmin_dual_texture_coordinate ( last_point, this_point );
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
					
					insert_xmin_dual_texture_coordinate ( last_point, this_point );
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
	
			insert_xmin_dual_texture_coordinate ( last_point, polygon );
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
	
					insert_xmax_dual_texture_coordinate ( last_point, this_point );
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
					
					insert_xmax_dual_texture_coordinate ( last_point, this_point );
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
	
			insert_xmax_dual_texture_coordinate ( last_point, polygon );
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
	
					insert_ymin_dual_texture_coordinate ( last_point, this_point );
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
					
					insert_ymin_dual_texture_coordinate ( last_point, this_point );
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
	
			insert_ymin_dual_texture_coordinate ( last_point, polygon );
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
	
					insert_ymax_dual_texture_coordinate ( last_point, this_point );
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
					
					insert_ymax_dual_texture_coordinate ( last_point, this_point );
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
	
			insert_ymax_dual_texture_coordinate ( last_point, polygon );
		}
	
		clip_point->next_vertex = NULL;

		polygon = clip_list;
	}

	return ( polygon );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_xmin_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		alpha,
		fog,
		specular,
		red,
		green,
		blue;

	int
		int_alpha,
		int_dalpha,
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
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

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	alpha += FLOAT_FLOAT_FACTOR;
	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = active_viewport.x_min;
	clip_3d_crds[clip_3d_coord].j = point2->j + ( t * ( point2->j - point1->j ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );

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

void insert_xmax_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		alpha,
		fog,
		specular,
		red,
		green,
		blue;

	int
		int_alpha,
		int_dalpha,
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
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

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	alpha += FLOAT_FLOAT_FACTOR;
	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = active_viewport.x_max;
	clip_3d_crds[clip_3d_coord].j = point2->j + ( t * ( point2->j - point1->j ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );

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

void insert_ymin_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		alpha,
		fog,
		specular,
		red,
		green,
		blue;

	int
		int_alpha,
		int_dalpha,
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
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

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	alpha += FLOAT_FLOAT_FACTOR;
	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = point2->i + ( t * ( point2->i - point1->i ) );
	clip_3d_crds[clip_3d_coord].j = active_viewport.y_min;
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );

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

void insert_ymax_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		alpha,
		fog,
		specular,
		red,
		green,
		blue;

	int
		int_alpha,
		int_dalpha,
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
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

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;

	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );

	alpha += FLOAT_FLOAT_FACTOR;
	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;

	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;

	clip_3d_crds[clip_3d_coord].i = point2->i + ( t * ( point2->i - point1->i ) );
	clip_3d_crds[clip_3d_coord].j = active_viewport.y_max;
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );

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

void insert_xmin_dual_texture_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		specular,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

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

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].blue = int_blue;
	clip_3d_crds[clip_3d_coord].alpha2 = int_alpha2;
	clip_3d_crds[clip_3d_coord].red2 = int_red2;
	clip_3d_crds[clip_3d_coord].green2 = int_green2;
	clip_3d_crds[clip_3d_coord].blue2 = int_blue2;

	clip_3d_crds[clip_3d_coord].i = active_viewport.x_min;
	clip_3d_crds[clip_3d_coord].j = point2->j + ( t * ( point2->j - point1->j ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );
	clip_3d_crds[clip_3d_coord].u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip_3d_crds[clip_3d_coord].v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

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

	clip_3d_coord ++;

#if REPORT_CLIP_STATISTICS

	number_of_xmin_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_xmax_dual_texture_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		specular,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

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

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].alpha2 = int_alpha2;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].red2 = int_red2;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].green2 = int_green2;
	clip_3d_crds[clip_3d_coord].blue = int_blue;
	clip_3d_crds[clip_3d_coord].blue2 = int_blue2;

	clip_3d_crds[clip_3d_coord].i = active_viewport.x_max;
	clip_3d_crds[clip_3d_coord].j = point2->j + ( t * ( point2->j - point1->j ) );
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );
	clip_3d_crds[clip_3d_coord].u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip_3d_crds[clip_3d_coord].v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

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

void insert_ymin_dual_texture_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		specular,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

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

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].alpha2 = int_alpha2;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].red2 = int_red2;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].green2 = int_green2;
	clip_3d_crds[clip_3d_coord].blue = int_blue;
	clip_3d_crds[clip_3d_coord].blue2 = int_blue2;

	clip_3d_crds[clip_3d_coord].i = point2->i + ( t * ( point2->i - point1->i ) );
	clip_3d_crds[clip_3d_coord].j = active_viewport.y_min;
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );
	clip_3d_crds[clip_3d_coord].u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip_3d_crds[clip_3d_coord].v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

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

void insert_ymax_dual_texture_coordinate ( vertex *point1, vertex *point2 )
{

	vertex
		*tmp = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		specular,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_fog,
		int_dfog,
		int_specular,
		int_dspecular,
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

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

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_specular = point2->specular;
	int_dspecular = int_specular - ( int ) point1->specular;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	specular = ( float ) int_specular + ( t * ( float ) int_dspecular );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	specular += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_specular = ( *( ( int * ) &specular ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip_3d_crds[clip_3d_coord].fog = int_fog;
	clip_3d_crds[clip_3d_coord].specular = int_specular;
	clip_3d_crds[clip_3d_coord].alpha = int_alpha;
	clip_3d_crds[clip_3d_coord].alpha2 = int_alpha2;
	clip_3d_crds[clip_3d_coord].red = int_red;
	clip_3d_crds[clip_3d_coord].red2 = int_red2;
	clip_3d_crds[clip_3d_coord].green = int_green;
	clip_3d_crds[clip_3d_coord].green2 = int_green2;
	clip_3d_crds[clip_3d_coord].blue = int_blue;
	clip_3d_crds[clip_3d_coord].blue2 = int_blue2;

	clip_3d_crds[clip_3d_coord].i = point2->i + ( t * ( point2->i - point1->i ) );
	clip_3d_crds[clip_3d_coord].j = active_viewport.y_max;
	clip_3d_crds[clip_3d_coord].q = point2->q + ( t * ( point2->q - point1->q ) );
	clip_3d_crds[clip_3d_coord].z = 1.0 / clip_3d_crds[clip_3d_coord].q;

	clip_3d_crds[clip_3d_coord].u = point2->u + ( t * ( point2->u - point1->u ) );
	clip_3d_crds[clip_3d_coord].v = point2->v + ( t * ( point2->v - point1->v ) );
	clip_3d_crds[clip_3d_coord].u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip_3d_crds[clip_3d_coord].v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

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

int generate_3d_outcode ( float i, float j )
{

	int
		outcode,
		ixmax,
		ixmin,
		iymax,
		iymin;

	float
		oxmax,
		oxmin,
		oymax,
		oymin;

	oxmax = active_viewport.x_max - i;
	oxmin = i - active_viewport.x_min;
	oymax = active_viewport.y_max - j;
	oymin = j - active_viewport.y_min;

	ixmax = *( ( int * ) &oxmax ) >> 31;
	ixmin = *( ( int * ) &oxmin ) >> 31;
	iymax = *( ( int * ) &oymax ) >> 31;
	iymin = *( ( int * ) &oymin ) >> 31;

	outcode = right_clip_bit_array[ ixmax + 1 ];
	outcode |= left_clip_bit_array[ ixmin + 1 ];
	outcode |= bottom_clip_bit_array[ iymax + 1 ];
	outcode |= top_clip_bit_array[ iymin + 1 ];

	return ( outcode );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_3d_j_outcode ( float j )
{

	int
		outcode,
		iymax,
		iymin;

	float
		oymax,
		oymin;

	oymax = active_viewport.y_max - j;
	oymin = j - active_viewport.y_min;

	iymax = *( ( int * ) &oymax ) >> 31;
	iymin = *( ( int * ) &oymin ) >> 31;

	outcode = bottom_clip_bit_array[ iymax + 1 ];
	outcode |= top_clip_bit_array[ iymin + 1 ];

	return ( outcode );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
