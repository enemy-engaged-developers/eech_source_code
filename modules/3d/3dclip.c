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

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static vertex
	*this_point,
	*last_point,
	*clip_list,
	*clip_point;

int
	number_of_near_coordinates_inserted,
	number_of_far_coordinates_inserted,
	number_of_polygons_yonder_clipped,
	number_of_polygons_hither_clipped;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void insert_z_far_coordinate ( vertex *point1, vertex *point2 );

static void insert_z_near_coordinate ( vertex *point1, vertex *point2 );

static void insert_horizon_coordinate ( vertex *point1, vertex *point2 );

static void insert_z_near_dual_texture_coordinate ( vertex *point1, vertex *point2 );

static void insert_z_far_dual_texture_coordinate ( vertex *point1, vertex *point2 );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *hither_clip_3d_polygon ( vertex *polygon, int *polygon_outcode )
{

	int
		outcode,
		outcode2;

	number_of_polygons_hither_clipped++;

	clip_list = NULL;

	clip_point = NULL;

	last_point = polygon;

	this_point = polygon->next_vertex;

	outcode = 0;

	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	if ( polygon->z >= clip_hither )
	{

		//
		// We are ok for the first point.
		//

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

			//
			// This point is on the screen
			//

			outcode |= this_point->outcode;

			outcode2 &= this_point->outcode;

			if ( last_point->outcode & CLIP_HITHER )
			{

				//
				// Last point was not on the screen, so we have to add a clip point.
				//

				insert_z_near_coordinate ( last_point, this_point );

				outcode |= clip_point->outcode;

				outcode2 &= clip_point->outcode;
			}

			// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put one in!

			clip_point->next_vertex = this_point;

			clip_point = this_point;
		}
		else
		{

			//
			// This point is not on the screen
			//

			if ( ! ( last_point->outcode & CLIP_HITHER ) )
			{

				//
				// The last point was visible - find intersection point
				//

				insert_z_near_coordinate ( this_point, last_point );

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
		
			insert_z_near_coordinate ( last_point, polygon );
		}
		else
		{
	
			insert_z_near_coordinate ( polygon, last_point );
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

	if ( ( outcode2 ) || ( !clip_list ) )	//( outcode2 ) || ( ! clip_list ) )
	{

		return ( NULL );
	}

	*polygon_outcode = outcode;
//	clip_list->polygon_outcode = outcode;

	return ( clip_list );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *yonder_clip_3d_polygon ( vertex *polygon, int *polygon_outcode )
{

	int
		outcode,
		outcode2;

	number_of_polygons_yonder_clipped++;

	clip_list = NULL;

	clip_point = NULL;

	last_point = polygon;

	this_point = polygon->next_vertex;

	outcode = 0;

	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	if ( polygon->z <= clip_yonder )
	{

		//
		// We are ok for the first point.
		//

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

			//
			// This point is on the screen
			//

			outcode |= this_point->outcode;

			outcode2 &= this_point->outcode;

			if ( last_point->outcode & CLIP_YONDER )
			{

				//
				// Last point was not on the screen, so we have to add a clip point.
				//

				insert_z_far_coordinate ( last_point, this_point );

				outcode |= clip_point->outcode;

				outcode2 &= clip_point->outcode;
			}

			// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put one in!

			clip_point->next_vertex = this_point;

			clip_point = this_point;
		}
		else
		{

			//
			// This point is not on the screen
			//

			if ( ! ( last_point->outcode & CLIP_YONDER ) )
			{

				//
				// The last point was visible - find intersection point
				//

				insert_z_far_coordinate ( this_point, last_point );

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
		
			insert_z_far_coordinate ( last_point, polygon );
		}
		else
		{
	
			insert_z_far_coordinate ( polygon, last_point );
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

vertex *hither_clip_3d_dual_texture_polygon ( vertex *polygon, int *polygon_outcode )
{

	int
		outcode,
		outcode2;

	number_of_polygons_hither_clipped++;

	clip_list = NULL;

	clip_point = NULL;

	last_point = polygon;

	this_point = polygon->next_vertex;

	outcode = 0;

	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	if ( polygon->z >= clip_hither )
	{

		//
		// We are ok for the first point.
		//

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

			//
			// This point is on the screen
			//

			outcode |= this_point->outcode;

			outcode2 &= this_point->outcode;

			if ( last_point->outcode & CLIP_HITHER )
			{

				//
				// Last point was not on the screen, so we have to add a clip point.
				//

				insert_z_near_dual_texture_coordinate ( last_point, this_point );

				outcode |= clip_point->outcode;

				outcode2 &= clip_point->outcode;
			}

			// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put one in!

			clip_point->next_vertex = this_point;

			clip_point = this_point;
		}
		else
		{

			//
			// This point is not on the screen
			//

			if ( ! ( last_point->outcode & CLIP_HITHER ) )
			{

				//
				// The last point was visible - find intersection point
				//

				insert_z_near_dual_texture_coordinate ( this_point, last_point );

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
		
			insert_z_near_dual_texture_coordinate ( last_point, polygon );
		}
		else
		{
	
			insert_z_near_dual_texture_coordinate ( polygon, last_point );
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

	if ( ( outcode2 ) || ( !clip_list ) )	//( outcode2 ) || ( ! clip_list ) )
	{

		return ( NULL );
	}

	*polygon_outcode = outcode;
//	clip_list->polygon_outcode = outcode;

	return ( clip_list );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex *yonder_clip_3d_dual_texture_polygon ( vertex *polygon, int *polygon_outcode )
{

	int
		outcode,
		outcode2;

	number_of_polygons_yonder_clipped++;

	clip_list = NULL;

	clip_point = NULL;

	last_point = polygon;

	this_point = polygon->next_vertex;

	outcode = 0;

	outcode2 = CLIP_YONDER | CLIP_HITHER | CLIP_TOP | CLIP_BOTTOM | CLIP_LEFT | CLIP_RIGHT;

	if ( polygon->z <= clip_yonder )
	{

		//
		// We are ok for the first point.
		//

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

			//
			// This point is on the screen
			//

			outcode |= this_point->outcode;

			outcode2 &= this_point->outcode;

			if ( last_point->outcode & CLIP_YONDER )
			{

				//
				// Last point was not on the screen, so we have to add a clip point.
				//

				insert_z_far_dual_texture_coordinate ( last_point, this_point );

				outcode |= clip_point->outcode;

				outcode2 &= clip_point->outcode;
			}

			// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put one in!

			clip_point->next_vertex = this_point;

			clip_point = this_point;
		}
		else
		{

			//
			// This point is not on the screen
			//

			if ( ! ( last_point->outcode & CLIP_YONDER ) )
			{

				//
				// The last point was visible - find intersection point
				//

				insert_z_far_dual_texture_coordinate ( this_point, last_point );

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
		
			insert_z_far_dual_texture_coordinate ( last_point, polygon );
		}
		else
		{
	
			insert_z_far_dual_texture_coordinate ( polygon, last_point );
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

vertex *horizon_clip_3d_polygon ( vertex *polygon )
{

	clip_list = NULL;

	clip_point = NULL;

	last_point = polygon;

	this_point = polygon->next_vertex;

	if ( polygon->y >= 0 )
	{

		//
		// We are ok for the first point.
		//

		clip_list = polygon;

		clip_point = polygon;

		polygon->next_vertex = NULL;
	}

	while ( this_point )
	{

		if ( !( this_point->y < 0 ) )	//this_point->outcode & CLIP_HITHER ) )
		{

			//
			// This point is on the screen
			//

			if ( last_point->y < 0 )	//last_point->outcode & CLIP_HITHER )
			{

				//
				// Last point was not on the screen, so we have to add a clip point.
				//

				insert_horizon_coordinate ( last_point, this_point );
			}

			// Here, we are guaranteed to have a coordinate in the clip list - the above routine just put one in!

			clip_point->next_vertex = this_point;

			clip_point = this_point;
		}
		else
		{

			//
			// This point is not on the screen
			//

			if ( ! ( last_point->y < 0 ) )	//last_point->outcode & CLIP_HITHER ) )
			{

				//
				// The last point was visible - find intersection point
				//

				insert_horizon_coordinate ( this_point, last_point );
			}
		}

		last_point = this_point;

		this_point = this_point->next_vertex;
	}

	if ( ( last_point->y < 0 ) ^ ( polygon->y < 0 ) )	//last_point->outcode & CLIP_HITHER ) ^ ( polygon->outcode & CLIP_HITHER ) )
	{

		if ( last_point->y < 0 )	//last_point->outcode & CLIP_HITHER )
		{
		
			insert_horizon_coordinate ( last_point, polygon );
		}
		else
		{
	
			insert_horizon_coordinate ( polygon, last_point );
		}
	}

	if ( clip_point )
	{

		clip_point->next_vertex = NULL;
	}

	if ( !clip_list )
	{

		return ( NULL );
	}

	return ( clip_list );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_z_near_coordinate ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip;

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

	t = ( ( clip_hither - point2->z ) / ( point2->z - point1->z ) );

	clip = &clip_3d_crds[clip_3d_coord];

	clip_3d_coord++;

	*( ( int * ) &clip->z ) = *( ( int * ) &clip_hither );
	*( ( int * ) &clip->q ) = *( ( int * ) &clip_hither_reciprocal );

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

	clip->x = point2->x + ( t * ( point2->x - point1->x ) );
	clip->y = point2->y + ( t * ( point2->y - point1->y ) );

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

	clip->alpha = int_alpha;
	clip->fog = int_fog;
	clip->specular = int_specular;
	clip->red = int_red;
	clip->green = int_green;
	clip->blue = int_blue;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );

	clip->j = active_3d_environment->y_origin;

	clip->i = ( clip->x * clip->q );

	clip->j -= ( clip->y * clip->q );

	clip->i += active_3d_environment->x_origin;

	clip->outcode = generate_3d_outcode ( clip->i, clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_near_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_z_far_coordinate ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip;

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

	t = ( ( clip_yonder - point2->z ) / ( point2->z - point1->z ) );

	clip = &clip_3d_crds[clip_3d_coord];

	clip_3d_coord++;

	*( ( int * ) &clip->z ) = *( ( int * ) &clip_yonder );
	*( ( int * ) &clip->q ) = *( ( int * ) &clip_yonder_reciprocal );

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

	clip->x = point2->x + ( t * ( point2->x - point1->x ) );
	clip->y = point2->y + ( t * ( point2->y - point1->y ) );

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

	clip->alpha = int_alpha;
	clip->fog = int_fog;
	clip->specular = int_specular;
	clip->red = int_red;
	clip->green = int_green;
	clip->blue = int_blue;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );

	clip->j = active_3d_environment->y_origin;

	clip->i = ( clip->x * clip->q );

	clip->j -= ( clip->y * clip->q );

	clip->i += active_3d_environment->x_origin;

	clip->outcode = generate_3d_outcode ( clip->i, clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_far_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_z_near_dual_texture_coordinate ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip;

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

	t = ( ( clip_hither - point2->z ) / ( point2->z - point1->z ) );

	clip = &clip_3d_crds[clip_3d_coord];

	clip_3d_coord++;

	*( ( int * ) &clip->z ) = *( ( int * ) &clip_hither );
	*( ( int * ) &clip->q ) = *( ( int * ) &clip_hither_reciprocal );

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

	clip->x = point2->x + ( t * ( point2->x - point1->x ) );
	clip->y = point2->y + ( t * ( point2->y - point1->y ) );

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

	clip->fog = int_fog;
	clip->specular = int_specular;
	clip->alpha = int_alpha;
	clip->alpha2 = int_alpha2;
	clip->red = int_red;
	clip->red2 = int_red2;
	clip->green = int_green;
	clip->green2 = int_green2;
	clip->blue = int_blue;
	clip->blue2 = int_blue2;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->j = active_3d_environment->y_origin;

	clip->i = ( clip->x * clip->q );

	clip->j -= ( clip->y * clip->q );

	clip->i += active_3d_environment->x_origin;

	clip->outcode = generate_3d_outcode ( clip->i, clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_near_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_z_far_dual_texture_coordinate ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip;

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

	t = ( ( clip_yonder - point2->z ) / ( point2->z - point1->z ) );

	clip = &clip_3d_crds[clip_3d_coord];

	clip_3d_coord++;

	*( ( int * ) &clip->z ) = *( ( int * ) &clip_yonder );
	*( ( int * ) &clip->q ) = *( ( int * ) &clip_yonder_reciprocal );

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

	clip->x = point2->x + ( t * ( point2->x - point1->x ) );
	clip->y = point2->y + ( t * ( point2->y - point1->y ) );

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

	clip->fog = int_fog;
	clip->specular = int_specular;
	clip->alpha = int_alpha;
	clip->alpha2 = int_alpha2;
	clip->red = int_red;
	clip->red2 = int_red2;
	clip->green = int_green;
	clip->green2 = int_green2;
	clip->blue = int_blue;
	clip->blue2 = int_blue2;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->j = active_3d_environment->y_origin;

	clip->i = ( clip->x * clip->q );

	clip->j -= ( clip->y * clip->q );

	clip->i += active_3d_environment->x_origin;

	clip->outcode = generate_3d_outcode ( clip->i, clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_far_coordinates_inserted++;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_horizon_coordinate ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip;

	float
		value,
		value1,
		value2;

	int
		int_value;

	ASSERT ( clip_3d_coord < MAX_3D_CLIP_COORDINATES );

	t = ( ( 0 - point2->y ) / ( point2->y - point1->y ) );

	clip = &clip_3d_crds[clip_3d_coord];

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

	clip_3d_coord++;

	clip->x = point2->x + ( t * ( point2->x - point1->x ) );

	clip->y = 0;

	clip->z = point2->z + ( t * ( point2->z - point1->z ) );

	value1 = point1->red;
	value2 = point2->red;
	value = value2 + ( t * ( value2 - value1 ) );
	asm_convert_float_to_int ( value, &int_value );
	clip->red = int_value;

	value1 = point1->green;
	value2 = point2->green;
	value = value2 + ( t * ( value2 - value1 ) );
	asm_convert_float_to_int ( value, &int_value );
	clip->green = int_value;

	value1 = point1->blue;
	value2 = point2->blue;
	value = value2 + ( t * ( value2 - value1 ) );
	asm_convert_float_to_int ( value, &int_value );
	clip->blue = int_value;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

