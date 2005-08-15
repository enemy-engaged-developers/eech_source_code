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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void insert_3d_horizon_image ( env_3d *env, weathermodes mode, horizon_image_data *image );

static void transform_3d_horizon ( object_3d *object );

static void render_3d_horizon_face ( object_3d_face *this_face, int surface_index, int reference_offset, struct OBJECT_3D_INFO *object_base );

static void render_3d_horizon_infrared_face ( object_3d_face *this_face, int surface_index, int reference_offset, struct OBJECT_3D_INFO *object_base );

static int outcode_3d_horizon_polygon ( int num_points, point_3d_short_reference *points, int base_point, int *polygon_outcode );

static vertex * construct_3d_horizon_triangle_fan ( int triangle_index, point_3d_short_reference *points, int base_point, int *polygon_outcode );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_horizon ( env_3d *env, object_3d_index_numbers index )
{

	object_3d
		*object;

	int
		count;

	float
		maximum_height;

	env->horizon_3d_scene_index = index;

	env->horizon_3d_object_number = objects_3d_scene_database[index].index;

	for ( count = 0; count < WEATHERMODE_LAST; count++ )
	{

		env->horizon_images_lists[count] = NULL;
	}

	object = &objects_3d_data[env->horizon_3d_object_number];

	env->horizon_point_colours = safe_malloc ( object->number_of_points * sizeof ( horizon_colour ) );

	if ( !env->horizon_point_colours )
	{

		debug_fatal ( "Unable to malloc enough memory for horizon object" );
	}

	maximum_height = object->bounding_box.ymax;

	env->horizon_maximum_height = maximum_height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_horizon_image ( env_3d *env, const char *filename, float time, weathermodes mode )
{

	short int
		width,
		height;

	int
		point_count,
		binary_loaded,
		bits,
		count,
		horizon_image_width,
		horizon_image_height;

	float
		maximum_height;

	object_3d
		*object;

	horizon_colour
		*point_colours;

	unsigned char
		*horizon_image;

	horizon_image_data
		*horizon_image_info;

	char
		binary_filename[256];

	FILE
		*fp;

	ASSERT ( env );

	binary_loaded = FALSE;

	object = &objects_3d_data[env->horizon_3d_object_number];
	
	//
	// Check to see if we have a pre-processed version of this file
	//

	sprintf ( binary_filename, "%s.bin", filename );

	if ( file_exist ( binary_filename ) )
	{

		fp = safe_fopen ( binary_filename, "rb" );

		fread ( &point_count, sizeof ( int ), 1, fp );

		if ( point_count == object->number_of_points )
		{

			binary_loaded = TRUE;

			horizon_image_info = malloc_fast_mem ( sizeof ( horizon_image_data ) );
		
			ASSERT ( horizon_image_info );
		
			point_colours = safe_malloc ( object->number_of_points * sizeof ( horizon_colour ) );
	
			horizon_image_info->point_colours = point_colours;
		
			horizon_image_info->time = time;
		
			fread ( point_colours, sizeof ( horizon_colour ), point_count, fp );

			fread ( &horizon_image_info->fog_colour, sizeof ( rgb_colour ), 1, fp );

			insert_3d_horizon_image ( env, mode, horizon_image_info );
		}

		fclose ( fp );
	}

	if ( !binary_loaded )
	{

		float
			xmax,
			ymax,
			zmax;

		sprintf ( binary_filename, "%s.tga", filename );

		horizon_image = load_tga_file ( binary_filename, &width, &height, &bits );
	
		horizon_image_width = width;
	
		horizon_image_height = height;
	
		if ( bits != 24 )
		{
	
			debug_fatal ( "Unable to read the horizon file - not a 24bit image" );
		}
	
		point_colours = safe_malloc ( object->number_of_points * sizeof ( horizon_colour ) );
	
		if ( !point_colours )
		{
	
			debug_fatal ( "Unable to malloc enough memory for horizon object" );
		}
	
		maximum_height = env->horizon_maximum_height;
	
		xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
		ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
		zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

		xmax /= 32767.0;
		ymax /= 32767.0;
		zmax /= 32767.0;

		for ( count = 0; count < object->number_of_points; count++ )
		{
	
			vec3d
				vector;
	
			float
				heading,
				pitch,
				pointx,
				pointy,
				pointz;
	
			int
				x,
				y;
	
			pointx = object->points[count].x;
			pointy = object->points[count].y;
			pointz = object->points[count].z;

			pointx *= xmax;
			pointy *= ymax;
			pointz *= zmax;
	
			vector.x = pointx;
			vector.y = pointy;
			vector.z = pointz;
	
			normalise_any_3d_vector ( &vector );
	
			heading = atan2 ( vector.x, vector.z );
	
			if ( heading < 0 )
			{
	
				heading = PI + ( PI + heading );
			}
	
			pitch = asin ( vector.y );
	
			pitch = bound ( pitch, 0, ( PI/2 ) );
	
			heading = bound ( heading, 0, ( PI*2 ) );
	
			heading /= ( PI * 2 );
	
			pitch /= ( PI / 2 );
	
			pitch = pointy / maximum_height;	//( ( float ) object->points[count].y ) / 65535.0;
	
			pitch = bound ( pitch, 0, 1 );
	
			x = heading * ( width - 1 );
	
			y = pitch * ( height - 1 );
	
			point_colours[count].red = ( unsigned char ) horizon_image[x*3 + y*3*width + 2];
			point_colours[count].green = ( unsigned char ) horizon_image[x*3 + y*3*width + 1];
			point_colours[count].blue = ( unsigned char ) horizon_image[x*3 + y*3*width + 0];
			point_colours[count].pad = 0;
		}
	
		horizon_image_info = malloc_fast_mem ( sizeof ( horizon_image_data ) );
	
		ASSERT ( horizon_image_info );
	
	
		horizon_image_info->point_colours = point_colours;
	
		horizon_image_info->time = time;
	
		horizon_image_info->fog_colour.r = horizon_image[ ( ( height -1 ) * 3 ) + 2 ];
		horizon_image_info->fog_colour.g = horizon_image[ ( ( height -1 ) * 3 ) + 1 ];
		horizon_image_info->fog_colour.b = horizon_image[ ( ( height -1 ) * 3 ) + 0 ];
	
		insert_3d_horizon_image ( env, mode, horizon_image_info );
	
		safe_free ( horizon_image );

		//
		// Now write out the binary file
		//

		sprintf ( binary_filename, "%s.bin", filename );

		debug_log ( "Writing binary horizon file: %s", binary_filename );

		fp = safe_fopen ( binary_filename, "wb" );

		point_count = object->number_of_points;

		fwrite ( &point_count, sizeof ( int ), 1, fp );

		fwrite ( point_colours, sizeof ( horizon_colour ), object->number_of_points, fp );

		fwrite ( &horizon_image_info->fog_colour, sizeof ( rgb_colour ), 1, fp );

		fclose ( fp );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_3d_horizon_image ( env_3d *env, weathermodes mode, horizon_image_data *image )
{

	ASSERT ( env );

	if ( env->horizon_images_lists[mode] )
	{

		horizon_image_data
			*this_image,
			*last_image;

		last_image = env->horizon_images_lists[mode];

		this_image = env->horizon_images_lists[mode];

		while ( this_image )
		{

			if ( this_image->time > image->time )
			{

				//
				// Insert *before* this_image
				//

				if ( last_image == this_image )
				{

					image->succ = env->horizon_images_lists[mode];

					env->horizon_images_lists[mode] = image;

					return;
				}
				else
				{

					last_image->succ = image;

					image->succ = this_image;

					return;
				}
			}
			else
			{

				last_image = this_image;

				this_image = this_image->succ;
			}
		}

		//
		// Got to the end of the list, and have to put it here.
		//

		image->succ = NULL;

		last_image->succ = image;
	}
	else
	{

		image->succ = NULL;

		env->horizon_images_lists[mode] = image;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_all_3d_horizon_images ( env_3d *env )
{

	weathermodes
		mode;

	ASSERT ( env );

	for ( mode = WEATHERMODE_INVALID + 1; mode < WEATHERMODE_LAST; mode++ )
	{
	
		if ( env->horizon_images_lists[mode] )
		{

			horizon_image_data
				*last_horizon_image_info,
				*this_horizon_image_info;

			this_horizon_image_info = env->horizon_images_lists[mode];

			while ( this_horizon_image_info )
			{

				last_horizon_image_info = this_horizon_image_info;

				this_horizon_image_info = this_horizon_image_info->succ;

				safe_free ( last_horizon_image_info->point_colours );

				free_mem ( last_horizon_image_info );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_3d_horizon ( env_3d *env )
{

	object_3d
		*object;

	horizon_image_data
		*image1,
		*image2,
		*image3,
		*image4;

	float
		dr,
		dg,
		db,
		t1,
		t2;

	int
		ir,
		ig,
		ib,
		count;

	float
		time,
		weather_t;

	weathermodes
		start_mode,
		end_mode;

	//
	// Get the variables
	//

	time = get_3d_time_of_day ( env );

	start_mode = get_3d_weathermode ( env );

	end_mode = get_3d_target_weathermode ( env );

	weather_t = get_3d_target_weathermode_transitional_status ( env );

	//
	// Find the point colours for just *before* this time
	//

	image1 = env->horizon_images_lists[start_mode];

	image2 = env->horizon_images_lists[start_mode];

	if ( !image1 )
	{

		debug_fatal ( "Unable to update the horizon - no information for current weathermode: %d", start_mode );
	}

	while ( ( image2 ) && ( image2->time < time ) )
	{

		image1 = image2;

		image2 = image2->succ;
	}

	if ( image2 )
	{

		//
		// Have to work out how far between these two images we are.
		//

		if ( image1 == image2 )
		{

			t1 = 0;
		}
		else
		{

			t1 = ( ( time - image1->time ) / ( image2->time - image1->time ) );
		}
	}
	else
	{

		//
		// We are somewhere between the last image and the first image
		//

		image2 = env->horizon_images_lists[start_mode];

		t1 = ( ( time - image1->time ) / ( ( image2->time + ONE_DAY ) - image1->time ) );
	}

	if ( ( weather_t != 0 ) && ( end_mode != start_mode ) )
	{

	
		float
			r1,
			g1,
			b1,
			r2,
			g2,
			b2;
	
		image3 = env->horizon_images_lists[end_mode];
	
		image4 = env->horizon_images_lists[end_mode];

		if ( !image3 )
		{

			debug_fatal ( "Unable to update the horizon - no information for weathermode: %d", end_mode );
		}
	
		while ( ( image4 ) && ( image4->time < time ) )
		{
	
			image3 = image4;
	
			image4 = image4->succ;
		}
	
		if ( image4 )
		{
	
			//
			// Have to work out how far between these two images we are.
			//
	
			if ( image3 == image4 )
			{
	
				t2 = 0;
			}
			else
			{
	
				t2 = ( ( time - image3->time ) / ( image4->time - image3->time ) );
			}
		}
		else
		{
	
			//
			// We are somewhere between the last image and the first image
			//
	
			image4 = env->horizon_images_lists[end_mode];
	
			t2 = ( ( time - image3->time ) / ( ( image4->time + ONE_DAY ) - image3->time ) );
		}

		//
		// Combine four images together!!!
		//

		object = &objects_3d_data[env->horizon_3d_object_number];
	
		for ( count = 0; count < object->number_of_points; count++ )
		{

			dr = image2->point_colours[count].red - image1->point_colours[count].red;
			dg = image2->point_colours[count].green - image1->point_colours[count].green;
			db = image2->point_colours[count].blue - image1->point_colours[count].blue;

			r1 = image1->point_colours[count].red + ( t1 * dr );
			g1 = image1->point_colours[count].green + ( t1 * dg );
			b1 = image1->point_colours[count].blue + ( t1 * db );

			dr = image4->point_colours[count].red - image3->point_colours[count].red;
			dg = image4->point_colours[count].green - image3->point_colours[count].green;
			db = image4->point_colours[count].blue - image3->point_colours[count].blue;

			r2 = image3->point_colours[count].red + ( t2 * dr );
			g2 = image3->point_colours[count].green + ( t2 * dg );
			b2 = image3->point_colours[count].blue + ( t2 * db );

			dr = r2 - r1;
			dg = g2 - g1;
			db = b2 - b1;

			asm_convert_float_to_int ( ( r1 + ( weather_t * dr ) ), &ir );
			asm_convert_float_to_int ( ( g1 + ( weather_t * dg ) ), &ig );
			asm_convert_float_to_int ( ( b1 + ( weather_t * db ) ), &ib );

			env->horizon_point_colours[count].red = ir;
			env->horizon_point_colours[count].green = ig;
			env->horizon_point_colours[count].blue = ib;
		}
	
		dr = image2->fog_colour.r - image1->fog_colour.r;
		dg = image2->fog_colour.g - image1->fog_colour.g;
		db = image2->fog_colour.b - image1->fog_colour.b;

		r1 = image1->fog_colour.r + ( t1 * dr );
		g1 = image1->fog_colour.g + ( t1 * dg );
		b1 = image1->fog_colour.b + ( t1 * db );

		dr = image4->fog_colour.r - image3->fog_colour.r;
		dg = image4->fog_colour.g - image3->fog_colour.g;
		db = image4->fog_colour.b - image3->fog_colour.b;

		r2 = image3->fog_colour.r + ( t2 * dr );
		g2 = image3->fog_colour.g + ( t2 * dg );
		b2 = image3->fog_colour.b + ( t2 * db );

		dr = r2 - r1;
		dg = g2 - g1;
		db = b2 - b1;

		asm_convert_float_to_int ( ( r1 + ( weather_t * dr ) ), &ir );
		asm_convert_float_to_int ( ( g1 + ( weather_t * dg ) ), &ig );
		asm_convert_float_to_int ( ( b1 + ( weather_t * db ) ), &ib );

		env->horizon_3d_fog_colour.r = ir;
		env->horizon_3d_fog_colour.g = ig;
		env->horizon_3d_fog_colour.b = ib;
	}
	else
	{
	
		//
		// Combine the two images together
		//
	
		object = &objects_3d_data[env->horizon_3d_object_number];
	
		for ( count = 0; count < object->number_of_points; count++ )
		{

			float
				fr,
				fg,
				fb;
/*
			int
				r1,
				r2,
				g1,
				g2,
				b1,
				b2,


			 image2->point_colours[count].red - image1->point_colours[count].red;
			 image2->point_colours[count].green - image1->point_colours[count].green;
			 image2->point_colours[count].blue - image1->point_colours[count].blue;
*/
			dr = image2->point_colours[count].red - image1->point_colours[count].red;
			dg = image2->point_colours[count].green - image1->point_colours[count].green;
			db = image2->point_colours[count].blue - image1->point_colours[count].blue;

			fr = t1 * dr;
			fg = t1 * dg;
			fb = t1 * db;

			asm_convert_float_to_int ( fr, &ir );
			asm_convert_float_to_int ( fg, &ig );
			asm_convert_float_to_int ( fb, &ib );

			env->horizon_point_colours[count].red = image1->point_colours[count].red + ir;
			env->horizon_point_colours[count].green = image1->point_colours[count].green + ig;
			env->horizon_point_colours[count].blue = image1->point_colours[count].blue + ib;
		}
	
		dr = image2->fog_colour.r - image1->fog_colour.r;
		dg = image2->fog_colour.g - image1->fog_colour.g;
		db = image2->fog_colour.b - image1->fog_colour.b;

		asm_convert_float_to_int ( ( t1 * dr ), &ir );
		asm_convert_float_to_int ( ( t1 * dg ), &ig );
		asm_convert_float_to_int ( ( t1 * db ), &ib );

		env->horizon_3d_fog_colour.r = image1->fog_colour.r + ir;
		env->horizon_3d_fog_colour.g = image1->fog_colour.g + ig;
		env->horizon_3d_fog_colour.b = image1->fog_colour.b + ib;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_horizon ( void )
{

	int
		object_number,
		count;

	object_3d_face
		*faces;

	object_3d_info
		*this_object_3d_info;

	object_3d_info
		object_base;

	//
	// Set the fog value to non fogged
	//

	set_d3d_fog_face_intensity ( 255 );

	//
	// Set up object base variable
	//

	this_object_3d_info = &object_base;

	object_base.lights = NULL;

	object_base.points_base = 0;

	object_base.object_number = active_3d_environment->horizon_3d_object_number;

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

	rotation_3d[0][0] = ( visual_3d_vp->xv.x );
	rotation_3d[0][1] = ( visual_3d_vp->yv.x );
	rotation_3d[0][2] = ( visual_3d_vp->zv.x );

	rotation_3d[1][0] = ( visual_3d_vp->xv.y );
	rotation_3d[1][1] = ( visual_3d_vp->yv.y );
	rotation_3d[1][2] = ( visual_3d_vp->zv.y );

	rotation_3d[2][0] = ( visual_3d_vp->xv.z );
	rotation_3d[2][1] = ( visual_3d_vp->yv.z );
	rotation_3d[2][2] = ( visual_3d_vp->zv.z );

	//
	// Get the object number
	//

	object_number = active_3d_environment->horizon_3d_object_number;

	//
	// Transform the object's shape data
	//

	transform_3d_horizon ( &objects_3d_data[object_number] );

	//
	// Set clipping & lighting to FALSE
	//

	force_set_d3d_int_state ( D3DRENDERSTATE_CLIPPING, FALSE );
	force_set_d3d_int_state ( D3DRENDERSTATE_LIGHTING, FALSE );

	//
	// Set transparency off, fogging off, zcomparison off, zwriting on
	//

	set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );

	set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );
	set_d3d_int_state ( D3DRENDERSTATE_SPECULARENABLE, TRUE );
	set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

	//
	// Set up the face sorting variables
	//

	faces = objects_3d_data[object_number].faces;
	current_object_3d_surface = objects_3d_data[object_number].surfaces;
	current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;

	if ( active_3d_environment->infrared_mode == INFRARED_OFF )
	{

		int
			surface,
			surface_face_count,
			number_of_surface_points;

		int
			point_reference_index;

		point_reference_index = 0;

		for ( surface = 0; surface < objects_3d_data[object_number].number_of_surfaces; surface++ )
		{
	
			surface_face_count = current_object_3d_surface->number_of_faces;
	
			number_of_surface_points = current_object_3d_surface->number_of_points;
	
			if ( number_of_surface_points == 0 )
			{
	
				number_of_surface_points = 256;
			}
		
			for ( count = surface_face_count; count > 0; count-- )
			{
	
				if ( faces->number_of_points > 2 )
				{
	
					render_3d_horizon_face ( faces, surface, point_reference_index, this_object_3d_info );
				}
	
				point_reference_index += faces->number_of_points;
	
				faces++;
			}
	
			current_object_3d_surface_point_list += number_of_surface_points;

			current_object_3d_surface++;
		}
	}
	else
	{

		int
			surface,
			number_of_surface_points,
			surface_face_count;

		int
			point_reference_index;

		point_reference_index = 0;

		for ( surface = 0; surface < objects_3d_data[object_number].number_of_surfaces; surface++ )
		{
	
			surface_face_count = current_object_3d_surface->number_of_faces;
	
			number_of_surface_points = current_object_3d_surface->number_of_points;
	
			if ( number_of_surface_points == 0 )
			{
	
				number_of_surface_points = 256;
			}

			surface_face_count = objects_3d_data[object_number].surfaces[surface].number_of_faces;
	
			for ( count = surface_face_count; count > 0; count-- )
			{
	
				if ( faces->number_of_points > 2 )
				{
	
					render_3d_horizon_infrared_face ( faces, surface, point_reference_index, this_object_3d_info );
				}
	
				point_reference_index += faces->number_of_points;
	
				faces++;
			}
	
			current_object_3d_surface_point_list += number_of_surface_points;

			current_object_3d_surface++;
		}
	}

	//
	// Turn fogging back on again
	//

	finalise_primitives ();

	if ( active_3d_environment->fogmode == FOGMODE_OFF )
	{

		set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, TRUE, TRUE );
	}
	else
	{

		set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
	}

	set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, zbuffer_default_comparison );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_horizon ( object_3d *object )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	vertex
		*last_transformed_point,
		*result_points,
		tmp_vertex;

	float
		xmax,
		ymax,
		zmax,
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	horizon_colour
		*point_colours;

	//
	// We only need the fpu to be in single precision mode
	//

	set_fpu_precision_mode_single ();

	number_of_points = object->number_of_points;

	points = object->points;

	result_points = transformed_3d_points;

	last_transformed_point = &tmp_vertex;

	point_colours = active_3d_environment->horizon_point_colours;

	xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
	ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
	zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

	rotation_3d[0][0] *= active_3d_environment->screen_i_scale * ( xmax / 32767.0 );
	rotation_3d[0][1] *= active_3d_environment->screen_j_scale * ( xmax / 32767.0 );
	rotation_3d[0][2] *= ( xmax / 32767.0 );

	rotation_3d[1][0] *= active_3d_environment->screen_i_scale * ( ymax / 32767.0 );
	rotation_3d[1][1] *= active_3d_environment->screen_j_scale * ( ymax / 32767.0 );
	rotation_3d[1][2] *= ( ymax / 32767.0 );

	rotation_3d[2][0] *= active_3d_environment->screen_i_scale * ( zmax / 32767.0 );
	rotation_3d[2][1] *= active_3d_environment->screen_j_scale * ( zmax / 32767.0 );
	rotation_3d[2][2] *= ( zmax / 32767.0 );

	for ( count = number_of_points; count > 0; count-- )
	{

		float
			pointx,
			pointy,
			pointz,
			x,
			y,
			z;

		pointx = points->x;
		pointy = points->y;
		pointz = points->z;

		x = pointx * rotation_3d[0][0] + pointy * rotation_3d[1][0] + pointz * rotation_3d[2][0];
		y = pointx * rotation_3d[0][1] + pointy * rotation_3d[1][1] + pointz * rotation_3d[2][1];
		z = pointx * rotation_3d[0][2] + pointy * rotation_3d[1][2] + pointz * rotation_3d[2][2];

		result_points->red = point_colours->red;
		result_points->green = point_colours->green;
		result_points->blue = point_colours->blue;
		result_points->alpha = 255;
	
		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			oxmax = active_viewport.x_max - last_transformed_point->i;
			oxmin = last_transformed_point->i - active_viewport.x_min;
			oymax = active_viewport.y_max - last_transformed_point->j;
			oymin = last_transformed_point->j - active_viewport.y_min;
		
			q = 1.0 / z;

			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );

			last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			result_points->x = x;
			result_points->y = y;
			result_points->z = z;

			last_transformed_point = result_points;

			i = ( x * q );
			j = ( y * q );

			result_points->q = q;
			result_points->j = active_3d_environment->y_origin - j;
			result_points->i = active_3d_environment->x_origin + i;
		}
		else
		{

			result_points->outcode = CLIP_HITHER;

			result_points->z = z;
			result_points->x = x;
			result_points->y = y;
		}

		point_colours++;

		result_points++;

		points++;
	}

	oxmax = active_viewport.x_max - last_transformed_point->i;
	oxmin = last_transformed_point->i - active_viewport.x_min;
	oymax = active_viewport.y_max - last_transformed_point->j;
	oymin = last_transformed_point->j - active_viewport.y_min;

	ixmax = *( ( int * ) &oxmax );
	ixmin = *( ( int * ) &oxmin );
	iymax = *( ( int * ) &oymax );
	iymin = *( ( int * ) &oymin );

	last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

	//
	// Set back the fpu precision mode.
	//

	set_fpu_precision_mode_double ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void render_3d_horizon_face ( object_3d_face *this_face, int surface_index, int reference_offset, struct OBJECT_3D_INFO *object_base )
{

	face_surface_description
		*surface;

	surface = &objects_3d_data[ object_base->object_number ].surfaces[surface_index];

	if ( surface->textured )
	{

		debug_fatal ( "Trying to draw a textured polygon in the horizon object" );
	}

	if ( !surface->smoothed )
	{

		debug_fatal ( "Trying to draw a flat shaded polygon in the horizon object" );
	}

	if ( surface->polygons )
	{

		vertex
			*poly;

		int
			outcode;
	
		//
		// The face is a triangle fan
		//
	
		{

			point_3d_short_reference
				*point_list;

			point_list = objects_3d_data[object_base->object_number].object_faces_point_plain_list;

			point_list += reference_offset;

			if ( !outcode_3d_horizon_polygon ( this_face->number_of_points, point_list, object_base->points_base, &outcode ) )
			{

				if ( outcode == 0 )
				{
				
					int
						count,
						surface_point_index,
						this_point;
				
					vertex
						*vert;
				
					LPD3DTLVERTEX
						destination_vertices;
				
					vertex
						*transformed_points;

					transformed_points = transformed_3d_points;	//[object_base->points_base];
				
					destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
				
					for ( count = 0; count < this_face->number_of_points; count++ )
					{

						surface_point_index = point_list[count].point;
						this_point = current_object_3d_surface_point_list[surface_point_index].point;
					
						vert = &transformed_points[this_point];
					
						destination_vertices[count].sx = vert->i;
						destination_vertices[count].sy = vert->j;
						destination_vertices[count].sz = POLYGON_ZDISTANCE_FARTHEST;
						destination_vertices[count].rhw = vert->q;
						destination_vertices[count].color = vert->colour;
						destination_vertices[count].specular = 0;	//RGBA_MAKE ( 0, 0, 0, 0 );	//vert->colour;
					}
				
					draw_fan_primitive ( this_face->number_of_points, destination_vertices );
				}
				else
				{

					int
						triangle_count;
	
					for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
					{

						poly = construct_3d_horizon_triangle_fan ( triangle_count, point_list, object_base->points_base, &outcode );
	
						if ( poly )
						{
		
							clip_3d_coord = 0;
						
							if ( outcode )
							{
				
								if ( outcode & CLIP_HITHER )
								{
							
									poly = hither_clip_3d_polygon ( poly, &outcode );
								}
	
								if ( poly )
								{
	
									if ( outcode )
									{
								
										poly = clip_3d_polygon ( poly, outcode );
									}
								}
							}

							if ( poly )
							{

								int
									count,
									number_of_points;
							
								LPD3DTLVERTEX
									destination_vertices;
							
								destination_vertices = get_d3d_vertices_address ( poly, &number_of_points );
							
								for ( count = 0; count < number_of_points; count++ )
								{
								
									destination_vertices[count].sx = poly->i;
									destination_vertices[count].sy = poly->j;
									destination_vertices[count].sz = POLYGON_ZDISTANCE_FARTHEST;
									destination_vertices[count].rhw = poly->q;
									destination_vertices[count].color = poly->colour;
									destination_vertices[count].specular = RGBA_MAKE ( 0, 0, 0, 0 );

									poly = poly->next_vertex;
								}
							
								draw_fan_primitive ( number_of_points, destination_vertices );
							}
						}
					}
				}
			}
		}
	}
	else
	{

		debug_fatal ( "Trying to draw a line/point in the horizon object" );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void render_3d_horizon_infrared_face ( object_3d_face *this_face, int surface_index, int reference_offset, struct OBJECT_3D_INFO *object_base )
{

	face_surface_description
		*surface;

	real_colour
		face_colour;

	surface = &objects_3d_data[object_base->object_number].surfaces[surface_index];

	face_colour.red = active_3d_environment->fog_colour.r;
	face_colour.green = active_3d_environment->fog_colour.g;
	face_colour.blue = active_3d_environment->fog_colour.b;
	face_colour.alpha = 255;

	if ( this_face->number_of_points > 2 )
	{

		vertex
			*poly;

		int
			outcode;
	
		//
		// The face is a triangle fan
		//
	
		{

			point_3d_short_reference
				*point_list;

			point_list = objects_3d_data[object_base->object_number].object_faces_point_plain_list;

			point_list += reference_offset;

			if ( !outcode_3d_horizon_polygon ( this_face->number_of_points, point_list, object_base->points_base, &outcode ) )
			{

				if ( outcode == 0 )
				{
				
					int
						count,
						surface_point_index,
						this_point;
				
					vertex
						*vert;
				
					LPD3DTLVERTEX
						destination_vertices;
				
					vertex
						*transformed_points;
				
					transformed_points = &transformed_3d_points[object_base->points_base];
				
					destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
				
					for ( count = 0; count < this_face->number_of_points; count++ )
					{
					
						surface_point_index = point_list[count].point;
						this_point = current_object_3d_surface_point_list[surface_point_index].point;
					
						vert = &transformed_points[this_point];
					
						destination_vertices[count].sx = vert->i;
						destination_vertices[count].sy = vert->j;
						destination_vertices[count].sz = POLYGON_ZDISTANCE_FARTHEST;
						destination_vertices[count].rhw = vert->q;
						destination_vertices[count].color = face_colour.colour;
						destination_vertices[count].specular = 0;	//RGBA_MAKE ( 255, 0, 0, 0 );	//vert->colour;
					}
				
					draw_fan_primitive ( this_face->number_of_points, destination_vertices );
				}
				else
				{

					int
						triangle_count;
	
					for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
					{
	
						poly = construct_3d_horizon_triangle_fan ( triangle_count, point_list, object_base->points_base, &outcode );
	
						if ( poly )
						{
		
							clip_3d_coord = 0;
						
							if ( outcode )
							{
				
								if ( outcode & CLIP_HITHER )
								{
							
									poly = hither_clip_3d_polygon ( poly, &outcode );
								}
	
								if ( poly )
								{
	
									if ( outcode )
									{
								
										poly = clip_3d_polygon ( poly, outcode );
									}
								}
							}
	
							if ( poly )
							{

								int
									count,
									number_of_points;
							
								LPD3DTLVERTEX
									destination_vertices;
							
								destination_vertices = get_d3d_vertices_address ( poly, &number_of_points );
							
								for ( count = 0; count < number_of_points; count++ )
								{
								
									destination_vertices[count].sx = poly->i;
									destination_vertices[count].sy = poly->j;
									destination_vertices[count].sz = POLYGON_ZDISTANCE_FARTHEST;
									destination_vertices[count].rhw = poly->q;
									destination_vertices[count].color = face_colour.colour;
									destination_vertices[count].specular = 0;	//RGBA_MAKE ( 255, 0, 0, 0 );	//vert->colour;

									poly = poly->next_vertex;
								}
							
								draw_fan_primitive ( number_of_points, destination_vertices );
							}
						}
					}
				}
			}
		}
	}
	else
	{

		debug_fatal ( "Trying to draw a line/point in the horizon object" );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int outcode_3d_horizon_polygon ( int num_points, point_3d_short_reference *points, int base_point, int *polygon_outcode )
{

	int
		this_outcode,
		count;

	unsigned char
		outcode,
		outcode2;

	vertex
		*vertices;

	vertices = transformed_3d_points + base_point;

	this_outcode = vertices[ current_object_3d_surface_point_list[ points[0].point].point ].outcode;

	outcode = this_outcode;
	outcode2 = this_outcode;

	for ( count = 1; count < num_points; count++ )
	{

		this_outcode = vertices[ current_object_3d_surface_point_list[ points[count].point].point ].outcode;

		outcode |= this_outcode;
		outcode2 &= this_outcode;
	}

	*polygon_outcode = outcode;

	return ( outcode2 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_3d_horizon_triangle_fan ( int triangle_index, point_3d_short_reference *points, int base_point, int *polygon_outcode )
{

	unsigned char
		outcode,
		outcode2;

	int
		surface_point_index,
		first_point,
		second_point,
		third_point;

	surface_point_index = points[0].point;
	first_point = current_object_3d_surface_point_list[surface_point_index].point + base_point;

	surface_point_index = points[triangle_index + 1].point;
	second_point = current_object_3d_surface_point_list[surface_point_index].point + base_point;

	surface_point_index = points[triangle_index + 2].point;
	third_point = current_object_3d_surface_point_list[surface_point_index].point + base_point;

	outcode = transformed_3d_points[first_point].outcode;
	outcode2 = transformed_3d_points[first_point].outcode;

	outcode |= transformed_3d_points[second_point].outcode;
	outcode2 &= transformed_3d_points[second_point].outcode;

	outcode |= transformed_3d_points[third_point].outcode;
	outcode2 &= transformed_3d_points[third_point].outcode;

	transformed_3d_points[first_point].next_vertex = &transformed_3d_points[second_point];
	transformed_3d_points[second_point].next_vertex = &transformed_3d_points[third_point];
	transformed_3d_points[third_point].next_vertex = NULL;

	*polygon_outcode = outcode;

	if ( outcode2 )
	{

		return ( NULL );
	}
	else
	{

		return ( &transformed_3d_points[first_point] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

