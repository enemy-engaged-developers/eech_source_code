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



#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	number_of_3d_star_points,
	number_of_3d_star_surfaces;

static object_3d_star_surface
	*star_3d_surfaces = nullptr;

static object_3d_star_point
	*star_3d_points = nullptr;

static float
	star_3d_x_minimum,
	star_3d_y_minimum,
	star_3d_z_minimum,
	star_3d_x_scale,
	star_3d_y_scale,
	star_3d_z_scale;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	number_of_visible_3d_stars;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_stars ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_stars ( const char *filename )
{

	FILE
		*fp = nullptr;

	int
		count;

	ASSERT ( filename );

	fp = safe_fopen ( filename, "rb" );

	fread ( &number_of_3d_star_points, sizeof ( int ), 1, fp );

	fread ( &number_of_3d_star_surfaces, sizeof ( int ), 1, fp );

	//
	// Allocate room for the surface information
	//

	star_3d_surfaces = ( object_3d_star_surface * ) safe_malloc ( sizeof ( object_3d_star_surface ) * number_of_3d_star_surfaces );

	ASSERT ( star_3d_surfaces );

	//
	// Read in the surface information
	//

	for ( count = 0; count < number_of_3d_star_surfaces; count++ )
	{

		fread ( &star_3d_surfaces[count].red, sizeof ( float ), 1, fp );
		fread ( &star_3d_surfaces[count].green, sizeof ( float ), 1, fp );
		fread ( &star_3d_surfaces[count].blue, sizeof ( float ), 1, fp );
		fread ( &star_3d_surfaces[count].translucency, sizeof ( float ), 1, fp );
	}

	//
	// Allocate room for the points
	//

	star_3d_points = ( object_3d_star_point * ) safe_malloc ( sizeof ( object_3d_star_point ) * number_of_3d_star_points );

	ASSERT ( star_3d_points );

	//
	// Read in the point scaling constants
	//

	fread ( &star_3d_x_minimum, sizeof ( float ), 1, fp );
	fread ( &star_3d_y_minimum, sizeof ( float ), 1, fp );
	fread ( &star_3d_z_minimum, sizeof ( float ), 1, fp );

	fread ( &star_3d_x_scale, sizeof ( float ), 1, fp );
	fread ( &star_3d_y_scale, sizeof ( float ), 1, fp );
	fread ( &star_3d_z_scale, sizeof ( float ), 1, fp );

	//
	// Read in the points themselves
	//

	for ( count = 0; count < number_of_3d_star_points; count++ )
	{

		fread ( &star_3d_points[count].x, sizeof ( unsigned short int ), 1, fp );
		fread ( &star_3d_points[count].y, sizeof ( unsigned short int ), 1, fp );
		fread ( &star_3d_points[count].z, sizeof ( unsigned short int ), 1, fp );
		fread ( &star_3d_points[count].surface, sizeof ( unsigned short int ), 1, fp );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_3d_stars ( void )
{
	if ( star_3d_points )
	{
		safe_free ( star_3d_points );
	}

	if ( star_3d_surfaces )
	{
		safe_free ( star_3d_surfaces );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_stars ( void )
{

	int
		total_translucency,
		count;

	float
		intensity;

	//
	// First, set all the surfaces to the correct colours
	//

	intensity = moon_colour.red * 0.3 + moon_colour.green * 0.59 + moon_colour.blue * 0.11;

	total_translucency = 0;

	for ( count = 0; count < number_of_3d_star_surfaces; count++ )
	{


		int
			red,
			green,
			blue,
			translucency;

		asm_convert_float_to_int ( star_3d_surfaces[count].red * 255, &red );
		asm_convert_float_to_int ( star_3d_surfaces[count].green * 255, &green );
		asm_convert_float_to_int ( star_3d_surfaces[count].blue * 255, &blue );
		asm_convert_float_to_int ( star_3d_surfaces[count].translucency * intensity * 255, &translucency );

		translucency = bound ( translucency, 0, 255 );

		star_3d_surfaces[count].r = red;
		star_3d_surfaces[count].g = green;
		star_3d_surfaces[count].b = blue;
		star_3d_surfaces[count].a = translucency;

		total_translucency += translucency;
	}

	if ( total_translucency )
	{

		transform_3d_stars ();

		//
		// Now go through all the visible stars, drawing them!
		//

		if ( number_of_visible_3d_stars )
		{

			LPTLVERTEX
				destination_vertices;

			set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );

			set_d3d_int_state ( D3DRS_ZFUNC, D3DCMP_ALWAYS );

			set_d3d_plain_renderstate ();

			if ( number_of_visible_3d_stars > 255 )
			{

				debug_log ( "Potentially overrunning stars: %d", number_of_visible_3d_stars );

				number_of_visible_3d_stars = 255;
			}

			destination_vertices = get_d3d_point_vertices_points_address ( number_of_visible_3d_stars );

			for ( count = 0; count < number_of_visible_3d_stars; count++ )
			{

				destination_vertices[count].sx = transformed_3d_points[count].i;
				destination_vertices[count].sy = transformed_3d_points[count].j;
				destination_vertices[count].sz = ( transformed_3d_points[count].q * zbuffer_factor ) + zbuffer_constant;
				destination_vertices[count].rhw = transformed_3d_points[count].q;
				destination_vertices[count].color = transformed_3d_points[count].colour;
				destination_vertices[count].specular = 0;
			}

			draw_point_list_primitive ( number_of_visible_3d_stars );

			set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );

			set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_stars ( void )
{

	int
		count;

	float
		pointx,
		pointy,
		pointz,
		x,
		y,
		z;

	vertex
		*result_points = nullptr;

	number_of_visible_3d_stars = 0;

	result_points = transformed_3d_points;

	for ( count = 0; count < number_of_3d_star_points; count++ )
	{

		float
			star_height;

		pointx = star_3d_points[count].x;
		pointy = star_3d_points[count].y;
		pointz = star_3d_points[count].z;

		star_height = pointy;

		pointx *= star_3d_x_scale;
		pointy *= star_3d_y_scale;
		pointz *= star_3d_z_scale;

		pointx += star_3d_x_minimum;
		pointy += star_3d_y_minimum;
		pointz += star_3d_z_minimum;

		z = pointx * visual_3d_vp->attitude[2][0];
		z += pointy * visual_3d_vp->attitude[2][1];
		z += pointz * visual_3d_vp->attitude[2][2];

		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				oxmax,
				oxmin,
				oymax,
				oymin,
				q,
				i,
				j;

			int
				ixmax,
				ixmin,
				iymax,
				iymin,
				outcode;

			x = pointx * visual_3d_vp->attitude[0][0];
			x += pointy * visual_3d_vp->attitude[0][1];
			x += pointz * visual_3d_vp->attitude[0][2];

			y = pointx * visual_3d_vp->attitude[1][0];
			y += pointy * visual_3d_vp->attitude[1][1];
			y += pointz * visual_3d_vp->attitude[1][2];

			q = 1.0 / z;

			i = ( active_3d_environment->screen_i_scale * x * q );
			j = ( active_3d_environment->screen_j_scale * y * q );

			j = active_3d_environment->y_origin - j;
			i = active_3d_environment->x_origin + i;

			oxmax = active_viewport.x_max - i;
			oxmin = i - active_viewport.x_min;
			oymax = active_viewport.y_max - j;
			oymin = j - active_viewport.y_min;

			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );

			outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			if ( !outcode )
			{

				int
					int_alpha,
					surface;

				float
					tweaked_alpha;


				surface = star_3d_points[count].surface;

				star_height /= 65535.0;
				star_height = 1.0 - star_height;

				star_height *= 2;

				if ( star_height >= 1.0 )
				{

					star_height = 1.0;
				}

				star_height *= star_height;

				tweaked_alpha = star_3d_surfaces[surface].a;
				tweaked_alpha *= ( 1.0 - star_height );

				asm_convert_float_to_int ( tweaked_alpha, &int_alpha );

				result_points->colour = star_3d_surfaces[surface].colour;
				result_points->alpha = int_alpha;

				result_points->i = i;
				result_points->j = j;
				result_points->x = x;
				result_points->y = y;
				result_points->z = z;
				result_points->q = q;

				result_points++;

				number_of_visible_3d_stars++;
			}
		}
	}
}
