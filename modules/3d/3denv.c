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

//
// This handles all the environment based things that go on in the 3d visual.
//  Including:
//
// Sun positioning / colouring / lighting
// Moon positioning / colouring / lighting
// Horizon colouring
// Weather mode changing
//  and many many more.........
//
//
// Remember, these functions are not available from the shops.....
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// All the access functions will set the relevant variables in the specified 3d environment,
//  but after setting all the values, a call *must* be made to commit_3d_environment_settings to make the changes apparent.
//
//
// set_3d_time_of_day
//		sets the time of day - the positioning of the sun / moon is derived from this, as well as the colouring
//		of the horizon.
//
// set_3d_
//
//
//
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

env_3d *create_3d_environment ( void )
{

	env_3d
		*env;

	env = ( env_3d * ) safe_malloc ( sizeof ( env_3d ) );

	ASSERT ( env );

	//
	// Set up default values in the environment
	//

	return ( env );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_3d_environment ( env_3d *env )
{

	ASSERT ( env );

	if ( active_3d_environment == env )
	{

		active_3d_environment = NULL;
	}

	safe_free ( env );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_active_environment ( env_3d *env )
{

	ASSERT ( env );

	active_3d_environment = env;

	//
	// Set the global 3d variables
	//

	realise_3d_clip_extents ( env );

	realise_3d_lightmode ( env );

	realise_3d_viewpoint ( env );

	realise_3d_fogmode ( env );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_time_of_day ( env_3d *env, float time )
{

	ASSERT ( env );

	env->time_of_day = time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_delta_time ( env_3d_*env, float delta_time )
{

	ASSERT ( env );

	env->delta_time = delta_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_weathermode ( env_3d *env, weathermodes mode )
{

	ASSERT ( env );

	env->weathermode = mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_target_weathermode ( env_3d *env, weathermodes mode )
{

	ASSERT ( env );

	env->target_weathermode = mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_target_weathermode_transitional_status ( env_3d *env, float value )
{

	ASSERT ( env );

	ASSERT ( value >= 0 );
	ASSERT ( value <= 1 );

	env->weather_targetdistance = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_monochrome_mode(env_3d *env, int monochrome)
{
	env->monochrome_mode = monochrome;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_monochrome_mode(env_3d *env)
{
	return env->monochrome_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_ambient_lighting ( env_3d *env )
{

	ASSERT ( env );

	env->number_of_ambient_light_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_ambient_lighting ( env_3d *env )
{

	ASSERT ( env );

	if ( env->number_of_ambient_light_settings )
	{

		//
		// Free the memory for these settings up.
		//
	}

	env->number_of_ambient_light_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_ambient_light_setting ( env_3d *env, rgb_colour light, float time )
{

	ambient_light_setting
		*light;

	ASSERT ( env );

	light = safe_malloc ( sizeof ( ambient_light_setting ) );

	light->colour = light;

	light->time = time;

	if ( env->number_of_ambient_light_settings )
	{
	}
	else
	{

		env->number_of_ambient_light_settings = 1;

		env->ambient_light_settings = light;

		light->succ = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void commit_3d_environment_settings ( void )
{

	//
	// Update all the positions etc
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour

	horizon_3d_fog_colour;

float
	horizon_3d_ambient_light_red,
	horizon_3d_ambient_light_green,
	horizon_3d_ambient_light_blue;

unsigned char
	*horizon_image;

horizon_image_data
	horizon_images[MAX_HORIZON_IMAGES];

horizon_image_data
	*horizon_images_list;

int
	number_of_horizon_images,
	horizon_image_width,
	horizon_image_height;

float
	horizon_maximum_height;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static horizon_colour
	*horizon_point_colours = NULL;

static int
	horizon_3d_scene_index,
	horizon_3d_object_number;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void insert_3d_horizon_image ( horizon_image_data *image );

static void transform_3d_horizon ( object_3d *object );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_horizon ( char *filename, enum OBJECT_3D_INDEX_NUMBERS index )
{

	short int
		width,
		height;

	int
		bits,
		count;

	object_3d
		*object;

	number_of_horizon_images = 0;

	horizon_3d_scene_index = index;

	horizon_3d_object_number = objects_3d_scene_database[index].index;

	object = &objects_3d_data[horizon_3d_object_number];

	if ( horizon_point_colours )
	{

		safe_free ( horizon_point_colours );

		horizon_point_colours = NULL;
	}

	horizon_point_colours = safe_malloc ( object->number_of_points * sizeof ( horizon_colour ) );

	if ( !horizon_point_colours )
	{

		debug_fatal ( "Unable to malloc enough memory for horizon object" );
	}

	if ( filename )
	{

		horizon_image = load_tga_file ( filename, &width, &height, &bits );
	
		horizon_image_width = width;
	
		horizon_image_height = height;
	
		if ( bits != 24 )
		{
	
			debug_fatal ( "Unable to read the horizon file - not a 24bit image" );
		}

		horizon_maximum_height = 0;
	
		for ( count = 0; count < object->number_of_points; count++ )
		{
	
			if ( object->points[count].y > horizon_maximum_height )
			{

				horizon_maximum_height = object->points[count].y;
			}
		}

		for ( count = 0; count < object->number_of_points; count++ )
		{
	
			vec3d
				vector;
	
			float
				heading,
				pitch;
	
			int
				x,
				y;
	
			vector.x = object->points[count].x;
			vector.y = object->points[count].y;
			vector.z = object->points[count].z;

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

			pitch = object->points[count].y / horizon_maximum_height;

			pitch = bound ( pitch, 0, 1 );
	
			x = heading * width;
	
			y = pitch * height;
	
			horizon_point_colours[count].red = ( ( ( float ) horizon_image[x*3 + y*3*width + 2] ) / 255.0 );
			horizon_point_colours[count].green = ( ( ( float ) horizon_image[x*3 + y*3*width + 1] ) / 255.0 );
			horizon_point_colours[count].blue = ( ( ( float ) horizon_image[x*3 + y*3*width + 0] ) / 255.0 );
		}
	
		horizon_3d_fog_colour.r = horizon_image[ ( ( height - 1 ) * 3 ) + 2 ];
		horizon_3d_fog_colour.g = horizon_image[ ( ( height - 1 ) * 3 ) + 1 ];
		horizon_3d_fog_colour.b = horizon_image[ ( ( height - 1 ) * 3 ) + 0 ];

		{

			float
				fog_red,
				fog_green,
				fog_blue;

			fog_red = horizon_3d_fog_colour.r;
			fog_green = horizon_3d_fog_colour.g;
			fog_blue = horizon_3d_fog_colour.b;

			fog_red /= 255;
			fog_green /= 255;
			fog_blue /= 255;

			horizon_3d_ambient_light_red = fog_red * 0.5;
			horizon_3d_ambient_light_green = fog_green * 0.5;
			horizon_3d_ambient_light_blue = fog_blue * 0.5;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_horizon_image ( char *filename, float time, weathermodes mode )
{

	short int
		width,
		height;

	int
		bits,
		count;

	object_3d
		*object;

	horizon_colour
		*point_colours;

	horizon_image = load_tga_file ( filename, &width, &height, &bits );

	horizon_image_width = width;

	horizon_image_height = height;

	if ( bits != 24 )
	{

		debug_fatal ( "Unable to read the horizon file - not a 24bit image" );
	}

	object = &objects_3d_data[horizon_3d_object_number];

	point_colours = safe_malloc ( object->number_of_points * sizeof ( horizon_colour ) );

	if ( !point_colours )
	{

		debug_fatal ( "Unable to malloc enough memory for horizon object" );
	}

	for ( count = 0; count < object->number_of_points; count++ )
	{

		vec3d
			vector;

		float
			heading,
			pitch;

		int
			x,
			y;

		vector.x = object->points[count].x;
		vector.y = object->points[count].y;
		vector.z = object->points[count].z;

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

		pitch = object->points[count].y / horizon_maximum_height;

		pitch = bound ( pitch, 0, 1 );

		x = heading * width;

		y = pitch * height;

		point_colours[count].red = ( ( ( float ) horizon_image[x*3 + y*3*width + 2] ) / 255.0 );
		point_colours[count].green = ( ( ( float ) horizon_image[x*3 + y*3*width + 1] ) / 255.0 );
		point_colours[count].blue = ( ( ( float ) horizon_image[x*3 + y*3*width + 0] ) / 255.0 );
	}

	horizon_images[number_of_horizon_images].point_colours = point_colours;

	horizon_images[number_of_horizon_images].time = time;

	horizon_images[number_of_horizon_images].weather_mode = mode;

	horizon_images[number_of_horizon_images].fog_colour.r = horizon_image[ ( ( height -1 ) * 3 ) + 2 ];
	horizon_images[number_of_horizon_images].fog_colour.g = horizon_image[ ( ( height -1 ) * 3 ) + 1 ];
	horizon_images[number_of_horizon_images].fog_colour.b = horizon_image[ ( ( height -1 ) * 3 ) + 0 ];

	{

		float
			fog_red,
			fog_green,
			fog_blue;

		fog_red = horizon_images[number_of_horizon_images].fog_colour.r;
		fog_green = horizon_images[number_of_horizon_images].fog_colour.g;
		fog_blue = horizon_images[number_of_horizon_images].fog_colour.b;

		fog_red /= 255;
		fog_green /= 255;
		fog_blue /= 255;

		horizon_images[number_of_horizon_images].ambient_light_red = fog_red * 0.5;
		horizon_images[number_of_horizon_images].ambient_light_green = fog_green * 0.5;
		horizon_images[number_of_horizon_images].ambient_light_blue = fog_blue * 0.5;
	}

	strcpy ( horizon_images[number_of_horizon_images].name, filename );

	insert_3d_horizon_image ( &horizon_images[number_of_horizon_images] );

	number_of_horizon_images++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_3d_horizon_image ( horizon_image_data *image )
{

	if ( horizon_images_list )
	{

		horizon_image_data
			*this_image,
			*last_image;

		last_image = horizon_images_list;

		this_image = horizon_images_list;

		while ( this_image )
		{

			if ( this_image->time > image->time )
			{

				//
				// Insert *before* this_image
				//

				if ( last_image == this_image )
				{

					image->succ = horizon_images_list;

					horizon_images_list = image;

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

		horizon_images_list = image;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_3d_horizon ( float time )
{

	object_3d
		*object;

	horizon_image_data
		*image1,
		*image2;

	float
		dr,
		dg,
		db,
		t;

	int
		count;

	//
	// Find the point colours for just *before* this time
	//

	image1 = horizon_images_list;

	image2 = horizon_images_list;

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

			t = 0;
		}
		else
		{

			t = ( ( time - image1->time ) / ( image2->time - image1->time ) );
		}
	}
	else
	{

		//
		// We are somewhere between the last image and the first image
		//

		image2 = horizon_images_list;

		t = ( ( time - image1->time ) / ( ( image2->time + ONE_DAY ) - image1->time ) );
	}

	//
	// Combine the two images
	//

	object = &objects_3d_data[horizon_3d_object_number];

	for ( count = 0; count < object->number_of_points; count++ )
	{

		dr = image2->point_colours[count].red - image1->point_colours[count].red;
		dg = image2->point_colours[count].green - image1->point_colours[count].green;
		db = image2->point_colours[count].blue - image1->point_colours[count].blue;

		horizon_point_colours[count].red = image1->point_colours[count].red + ( t * dr );
		horizon_point_colours[count].green = image1->point_colours[count].green + ( t * dg );
		horizon_point_colours[count].blue = image1->point_colours[count].blue + ( t * db );
	}

	dr = image2->fog_colour.r - image1->fog_colour.r;
	dg = image2->fog_colour.g - image1->fog_colour.g;
	db = image2->fog_colour.b - image1->fog_colour.b;

	horizon_3d_fog_colour.r = image1->fog_colour.r + ( t * dr );
	horizon_3d_fog_colour.g = image1->fog_colour.g + ( t * dg );
	horizon_3d_fog_colour.b = image1->fog_colour.b + ( t * db );

	dr = image2->ambient_light_red - image1->ambient_light_red;
	dg = image2->ambient_light_green - image1->ambient_light_green;
	db = image2->ambient_light_blue - image1->ambient_light_blue;

	horizon_3d_ambient_light_red = image1->ambient_light_red + ( t * dr );
	horizon_3d_ambient_light_green = image1->ambient_light_green + ( t * dg );
	horizon_3d_ambient_light_blue = image1->ambient_light_blue + ( t * db );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_horizon ( void )
{

	int
		object_number,
		count,
		num_faces;

	face_3d
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

	object_base.object_number = horizon_3d_object_number;


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

	object_number = horizon_3d_object_number;

	//
	// Set up the face sorting variables
	//

	num_faces = objects_3d_data[object_number].number_of_faces;

	reset_3d_face_sorting ();

	//
	// Insert this objects' faces into the sorted list.
	//

	faces = objects_3d_data[object_number].faces;

	{

		object_3d_point
			*object_points;

		point_3d_textured_reference
			*textured_point_list;

		point_3d_plain_reference
			*plain_point_list;

		object_points = objects_3d_data[object_number].points;

		plain_point_list = objects_3d_data[object_number].object_faces_point_plain_list;

		textured_point_list = objects_3d_data[object_number].object_faces_point_textured_list;

		for ( count = num_faces; count > 0; count-- )
		{
	
			object_3d_point
				*depth_point;
	
			if ( faces->number_of_points > 2 )
			{
	
				float
					normal_direction,
					normal_direction1,
					normal_direction2;
	
				point_3d_plain_reference
					*point_list;
			
				point_list = &plain_point_list[faces->point_reference_index];

				depth_point = &object_points[point_list->point];

				normal_direction = ( depth_point->x ) * faces->normal_data.x;
				normal_direction1 = ( depth_point->y ) * faces->normal_data.y;
				normal_direction2 = ( depth_point->z ) * faces->normal_data.z;
		
				normal_direction += normal_direction1 + normal_direction2;

				if ( *( ( int * ) &normal_direction ) <= *( ( int * ) &float_value_zero ) )
				{

					insert_3d_face ( faces, this_object_3d_info );
				}
			}
	
			faces++;
		}
	}

	faces = objects_3d_data[object_number].faces;

	//
	// Transform the object's shape data
	//

	transform_3d_horizon ( &objects_3d_data[object_number] );

	//
	// This is the furthest object. Set the Z buffering system to reflect this
	//

	suspend_d3d_fog ();

	render_3d_object_diffuse_lit_faces ();

	reinstate_d3d_fog ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_horizon ( object_3d *object )
{

	int
		count,
		number_of_points;

	object_3d_point
		*points;

	vertex
		*last_transformed_point,
		*result_points,
		tmp_vertex;

	float
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

	point_colours = horizon_point_colours;

	for ( count = number_of_points; count > 0; count-- )
	{

		float
			x,
			y,
			z;

		z = points->x * rotation_3d[0][2] + points->y * rotation_3d[1][2] + points->z * rotation_3d[2][2];

		result_points->red = point_colours->red;

		result_points->green = point_colours->green;

		result_points->blue = point_colours->blue;
	
		if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				q,
				i,
				j;

			x = points->x * rotation_3d[0][0] + points->y * rotation_3d[1][0] + points->z * rotation_3d[2][0];

			y = points->x * rotation_3d[0][1] + points->y * rotation_3d[1][1] + points->z * rotation_3d[2][1];

			oxmax = active_viewport.x_max - last_transformed_point->i;
			oxmin = last_transformed_point->i - active_viewport.x_min;
			oymax = active_viewport.y_max - last_transformed_point->j;
			oymin = last_transformed_point->j - active_viewport.y_min;
		
			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );
		
			last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			result_points->x = x;

			result_points->y = y;

			result_points->z = z;

			last_transformed_point = result_points;

			q = 1.0 / z;

			i = ( active_3d_environment->screen_i_scale * x * q );

			j = ( active_3d_environment->screen_j_scale * y * q );

			result_points->j = active_3d_environment->y_origin - j;

			result_points->i = active_3d_environment->x_origin + i;

			result_points->q = q;
		}
		else
		{

			x = points->x * rotation_3d[0][0] + points->y * rotation_3d[1][0] + points->z * rotation_3d[2][0];

			y = points->x * rotation_3d[0][1] + points->y * rotation_3d[1][1] + points->z * rotation_3d[2][1];

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

