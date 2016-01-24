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



#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"3d.h"
#include "cmndline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// This handles all the environment based things that go on in the 3d visual.
//  Including:
//
// Sun positioning / colouring / lighting
//
// Moon positioning / colouring / lighting
//
// Horizon colouring
//
// Weather mode changing
//
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
// set_3d_delta_time
//		sets the frame time for the rendering system - this affects things like speed of the rain etc.
//
//
//
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_interpolated_angle ( float angle1, float angle2, float t );

static void initialise_3d_light_settings ( env_3d *env );

void reset_3d_fog_settings ( env_3d *env );

void reset_3d_ambient_light_settings ( env_3d *env );

void reset_3d_sun_settings ( env_3d *env );

void reset_3d_moon_settings ( env_3d *env );

void reset_3d_cloud_light_settings ( env_3d *env );

void reset_3d_shadow_settings ( env_3d *env );

void initialise_3d_moon_settings ( env_3d *env );

void initialise_3d_ambient_light_settings ( env_3d *env );

void initialise_3d_fog_settings ( env_3d *env );

void initialise_3d_sun_settings ( env_3d *env );

void initialise_3d_cloud_light_settings ( env_3d *env );

void initialise_3d_shadow_settings ( env_3d *env );

void calculate_3d_moon_light ( env_3d *env );

void calculate_3d_fog_settings ( env_3d *env );

void calculate_3d_ambient_light ( env_3d *env );

void calculate_3d_sun_light ( env_3d *env );

void calculate_3d_cloud_light ( env_3d *env );

void calculate_3d_shadow_light ( env_3d *env );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

env_3d *create_3d_environment ( void )
{

	env_3d
		*env;

	env = ( env_3d * ) safe_malloc ( sizeof ( env_3d ) );

	memset ( env, 0, sizeof ( env_3d ) );

	ASSERT ( env );

	//
	// Set up default values in the environment
	//

	initialise_3d_fog_settings ( env );

	initialise_3d_light_settings ( env );

	initialise_3d_ambient_light_settings ( env );

	initialise_3d_sun_settings ( env );

	initialise_3d_moon_settings ( env );

	initialise_3d_cloud_light_settings ( env );

	initialise_3d_shadow_settings ( env );

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

	reset_3d_fog_settings ( env );

	//
	// Clear up any ambient light settings.
	//

	reset_3d_ambient_light_settings ( env );

	reset_3d_sun_settings ( env );

	reset_3d_moon_settings ( env );

	reset_3d_cloud_light_settings ( env );

	reset_3d_shadow_settings ( env );

	//
	// Remove any horizon images
	//

	destroy_all_3d_horizon_images ( env );

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

	realise_3d_fogmode ( env );

	realise_3d_clip_extents ( env );

	realise_3d_lightmode ( env );

	realise_3d_viewpoint ( env );

	realise_3d_shadow_setting ( env );
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

void set_3d_delta_time ( env_3d *env, float delta_time )
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

void set_3d_infrared_mode ( env_3d *env, render_filters mode )
{

	ASSERT ( env );

	env->render_filter = mode;
}

void set_3d_render_filter ( env_3d *env, render_filters mode )
{

	ASSERT ( env );

	env->render_filter = mode;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void interpolate_two_fog_settings  ( fog_setting *result_fog, fog_setting *start_fog, fog_setting *end_fog, float t )
{

	float
		dscale,
		dstart,
		dend;

	dscale = end_fog->scale - start_fog->scale;
	dstart = end_fog->start - start_fog->start;
	dend = end_fog->end - start_fog->end;

	result_fog->scale = start_fog->scale + ( t * dscale );
	result_fog->start = start_fog->start + ( t * dstart );
	result_fog->end = start_fog->end + ( t * dend );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_interpolated_fog_setting ( float time_of_day, fog_setting *fog_head, fog_setting *result_fog )
{

	//
	// Handle the case where there is only one fog setting
	//

	if ( !fog_head->succ )
	{

		result_fog->scale = fog_head->scale;
		result_fog->start = fog_head->start;
		result_fog->end = fog_head->end;
	}
	else
	{

		fog_setting
			*fog1,
			*fog2;

		float
			t;

		fog1 = fog_head;
		fog2 = fog_head;

		while ( ( fog2 ) && ( fog2->time < time_of_day ) )
		{

			fog1 = fog2;

			fog2 = fog2->succ;
		}

		if ( fog2 )
		{

			//
			// Have to work out how far between these two settings we are.
			//

			if ( fog1 == fog2 )
			{

				t = 0;
			}
			else
			{

				t = ( ( time_of_day - fog1->time ) / ( fog2->time - fog1->time ) );
			}
		}
		else
		{

			//
			// We are somewhere between the last setting and the first setting
			//

			fog2 = fog_head;

			t = ( ( time_of_day - fog1->time ) / ( ( fog2->time + ONE_DAY ) - fog1->time ) );
		}

		interpolate_two_fog_settings  ( result_fog, fog1, fog2, t );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void interpolate_two_light_settings  ( main_light_setting *result_light, main_light_setting *start_light, main_light_setting *end_light, float t )
{

	float
		dr,
		dg,
		db,
		da,
		dscale,
		dshadow;

	//
	// Calculate the light light colour
	//

	dr = end_light->light__colour.red - start_light->light__colour.red;
	dg = end_light->light__colour.green - start_light->light__colour.green;
	db = end_light->light__colour.blue - start_light->light__colour.blue;
	da = end_light->light__colour.alpha - start_light->light__colour.alpha;

	result_light->light__colour.red = start_light->light__colour.red + ( t * dr );
	result_light->light__colour.green = start_light->light__colour.green + ( t * dg );
	result_light->light__colour.blue = start_light->light__colour.blue + ( t * db );
	result_light->light__colour.alpha = start_light->light__colour.alpha + ( t * da );

	//
	// Calculate the light object colour
	//

	dr = end_light->object_colour.red - start_light->object_colour.red;
	dg = end_light->object_colour.green - start_light->object_colour.green;
	db = end_light->object_colour.blue - start_light->object_colour.blue;
	da = end_light->object_colour.alpha - start_light->object_colour.alpha;

	result_light->object_colour.red = start_light->object_colour.red + ( t * dr );
	result_light->object_colour.green = start_light->object_colour.green + ( t * dg );
	result_light->object_colour.blue = start_light->object_colour.blue + ( t * db );
	result_light->object_colour.alpha = start_light->object_colour.alpha + ( t * da );

	result_light->heading = get_interpolated_angle ( start_light->heading, end_light->heading, t );
	result_light->pitch = get_interpolated_angle ( start_light->pitch, end_light->pitch, t );

	dscale = end_light->scale - start_light->scale;

	result_light->scale = start_light->scale + ( t * dscale );

	dshadow = end_light->shadow - start_light->shadow;

	result_light->shadow = start_light->shadow + ( t * dshadow );

	result_light->main_light = start_light->main_light;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_interpolated_light_setting ( float time_of_day, main_light_setting *light_head, main_light_setting *result_light )
{

	//
	// Handle the case where there is only one light setting
	//

	if ( !light_head->succ )
	{

		result_light->light__colour.red = light_head->light__colour.red;
		result_light->light__colour.green = light_head->light__colour.green;
		result_light->light__colour.blue = light_head->light__colour.blue;
		result_light->light__colour.alpha = light_head->light__colour.alpha;

		result_light->object_colour.red = light_head->object_colour.red;
		result_light->object_colour.green = light_head->object_colour.green;
		result_light->object_colour.blue = light_head->object_colour.blue;
		result_light->object_colour.alpha = light_head->object_colour.alpha;

		result_light->heading = light_head->heading;
		result_light->pitch = light_head->pitch;

		result_light->scale = light_head->scale;
		result_light->shadow = light_head->shadow;

		result_light->main_light = light_head->main_light;
	}
	else
	{

		main_light_setting
			*light1,
			*light2;

		float
			t;

		light1 = light_head;
		light2 = light_head;

		while ( ( light2 ) && ( light2->time < time_of_day ) )
		{

			light1 = light2;

			light2 = light2->succ;
		}

		if ( light2 )
		{

			//
			// Have to work out how far between these two settings we are.
			//

			if ( light1 == light2 )
			{

				t = 0;
			}
			else
			{

				t = ( ( time_of_day - light1->time ) / ( light2->time - light1->time ) );
			}
		}
		else
		{

			//
			// We are somewhere between the last setting and the first setting
			//

			light2 = light_head;

			t = ( ( time_of_day - light1->time ) / ( ( light2->time + ONE_DAY ) - light1->time ) );
		}

		interpolate_two_light_settings  ( result_light, light1, light2, t );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_fog_settings ( env_3d *env )
{

	int
		mode;

	ASSERT ( env );

	env->number_of_fog_settings = 0;

	for ( mode = WEATHERMODE_INVALID + 1; mode < WEATHERMODE_LAST; mode++ )
	{

		env->fog_settings[mode] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_fog_settings ( env_3d *env )
{

	ASSERT ( env );

	if ( env->number_of_fog_settings )
	{

		int
			weathermode;

		fog_setting
			*old_fog,
			*fog;

		for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
		{

			if ( env->fog_settings[weathermode] )
			{

				fog = env->fog_settings[weathermode];

				while ( fog )
				{

					old_fog = fog;

					fog = fog->succ;

					safe_free ( old_fog );
				}

				env->fog_settings[weathermode] = NULL;
			}
		}
	}

	env->number_of_fog_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_fog_setting ( env_3d *env, weathermodes mode, float fog_scale, float start, float end, float time )
{

	fog_setting
		*fog;

	ASSERT ( env );

	fog = ( fog_setting * ) safe_malloc ( sizeof ( fog_setting ) );

	fog->scale = fog_scale;
	fog->start = start;
	fog->end = end;
	fog->time = time;

	if ( env->fog_settings[mode] )
	{

		fog_setting
			*this_fog,
			*last_fog;

		env->number_of_fog_settings++;

		last_fog = env->fog_settings[mode];

		this_fog = env->fog_settings[mode];

		while ( this_fog )
		{

			if ( this_fog->time > fog->time )
			{

				//
				// Insert *before* this_fog
				//

				if ( last_fog == this_fog )
				{

					fog->succ = env->fog_settings[mode];

					env->fog_settings[mode] = fog;

					return;
				}
				else
				{

					last_fog->succ = fog;

					fog->succ = this_fog;

					return;
				}
			}
			else
			{

				last_fog = this_fog;

				this_fog = this_fog->succ;
			}
		}

		//
		// Got to the end of the list, and have to put it here.
		//

		fog->succ = NULL;

		last_fog->succ = fog;
	}
	else
	{

		env->number_of_fog_settings++;

		env->fog_settings[mode] = fog;

		fog->succ = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_light_settings ( env_3d *env )
{

	env->sun_3d_light.pred = NULL;

	env->sun_3d_light.succ = NULL;

	env->moon_3d_light.pred = NULL;

	env->moon_3d_light.succ = NULL;

	env->secondary_light_sources = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_ambient_light_settings ( env_3d *env )
{

	int
		weathermode;

	ASSERT ( env );

	env->number_of_ambient_light_settings = 0;

	for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
	{

		env->ambient_light_settings[weathermode] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_ambient_light_settings ( env_3d *env )
{

	ASSERT ( env );

	if ( env->number_of_ambient_light_settings )
	{

		int
			weathermode;

		main_light_setting
			*old_light,
			*light;

		for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
		{

			if ( env->ambient_light_settings[weathermode] )
			{

				light = env->ambient_light_settings[weathermode];

				while ( light )
				{

					old_light = light;

					light = light->succ;

					safe_free ( old_light );
				}

				env->ambient_light_settings[weathermode] = NULL;
			}
		}
	}

	env->number_of_ambient_light_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_ambient_light_setting ( env_3d *env, weathermodes mode, rgb_colour colour, float intensity, float time )
{

	main_light_setting
		*light;

	float
		r,
		g,
		b;

	ASSERT ( env );

	light = ( main_light_setting * ) safe_malloc ( sizeof ( main_light_setting ) );
	memset ( light, 0, sizeof ( *light ) );

	r = colour.r;
	g = colour.g;
	b = colour.b;

	r *= intensity;
	g *= intensity;
	b *= intensity;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;

	light->light__colour.red = r;
	light->light__colour.green = g;
	light->light__colour.blue = b;

	light->time = time;

	if ( env->ambient_light_settings[mode] )
	{

		main_light_setting
			*this_light,
			*last_light;

		env->number_of_ambient_light_settings++;

		last_light = env->ambient_light_settings[mode];

		this_light = env->ambient_light_settings[mode];

		while ( this_light )
		{

			if ( this_light->time > light->time )
			{

				//
				// Insert *before* this_light
				//

				if ( last_light == this_light )
				{

					light->succ = env->ambient_light_settings[mode];

					env->ambient_light_settings[mode] = light;

					return;
				}
				else
				{

					last_light->succ = light;

					light->succ = this_light;

					return;
				}
			}
			else
			{

				last_light = this_light;

				this_light = this_light->succ;
			}
		}

		//
		// Got to the end of the list, and have to put it here.
		//

		light->succ = NULL;

		last_light->succ = light;
	}
	else
	{

		env->number_of_ambient_light_settings++;

		env->ambient_light_settings[mode] = light;

		light->succ = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_sun_settings ( env_3d *env )
{

	int
		weathermode;

	ASSERT ( env );

	env->number_of_sun_settings = 0;

	for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
	{

		env->sun_settings[weathermode] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_sun_settings ( env_3d *env )
{

	ASSERT ( env );

	if ( env->number_of_sun_settings )
	{

		main_light_setting
			*old_light,
			*light;

		int
			weathermode;

		//
		// Free the memory for these settings up.
		//

		for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
		{

			if ( env->sun_settings[weathermode] )
			{

				light = env->sun_settings[weathermode];

				while ( light )
				{

					old_light = light;

					light = light->succ;

					safe_free ( old_light );
				}

				env->sun_settings[weathermode] = NULL;
			}
		}
	}

	env->number_of_sun_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_sun_setting ( env_3d *env, weathermodes weathermode, float scale, float shadow, rgb_colour object_colour, float object_intensity, rgb_colour light_colour, float light_intensity, float heading, float pitch, int main_light, float time )
{

	main_light_setting
		*light;

	float
		r,
		g,
		b,
		a;

	ASSERT ( env );

	light = ( main_light_setting * ) safe_malloc ( sizeof ( main_light_setting ) );
	memset ( light, 0, sizeof ( *light ) );

	r = light_colour.r;
	g = light_colour.g;
	b = light_colour.b;
	a = light_colour.a;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	a /= 255.0;

	r *= light_intensity;
	g *= light_intensity;
	b *= light_intensity;
	a *= light_intensity;

	light->light__colour.red = r;
	light->light__colour.green = g;
	light->light__colour.blue = b;
	light->light__colour.alpha = a;

	r = object_colour.r;
	g = object_colour.g;
	b = object_colour.b;
	a = object_colour.a;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	a /= 255.0;

	r *= object_intensity;
	g *= object_intensity;
	b *= object_intensity;
	a *= object_intensity;

	light->object_colour.red = r;
	light->object_colour.green = g;
	light->object_colour.blue = b;
	light->object_colour.alpha = a;

	light->time = time;

	light->heading = heading;
	light->pitch = pitch;

	light->scale = scale;

	light->shadow = shadow;

	light->main_light = main_light;

	if ( env->sun_settings[weathermode] )
	{

		main_light_setting
			*this_light,
			*last_light;

		env->number_of_sun_settings++;

		last_light = env->sun_settings[weathermode];

		this_light = env->sun_settings[weathermode];

		while ( this_light )
		{

			if ( this_light->time > light->time )
			{

				//
				// Insert *before* this_light
				//

				if ( last_light == this_light )
				{

					light->succ = env->sun_settings[weathermode];

					env->sun_settings[weathermode] = light;

					return;
				}
				else
				{

					last_light->succ = light;

					light->succ = this_light;

					return;
				}
			}
			else
			{

				last_light = this_light;

				this_light = this_light->succ;
			}
		}

		//
		// Got to the end of the list, and have to put it here.
		//

		light->succ = NULL;

		last_light->succ = light;
	}
	else
	{

		env->number_of_sun_settings++;

		env->sun_settings[weathermode] = light;

		light->succ = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_moon_settings ( env_3d *env )
{

	int
		weathermode;

	ASSERT ( env );

	env->number_of_moon_settings = 0;

	for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
	{

		env->moon_settings[weathermode] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_moon_settings ( env_3d *env )
{

	ASSERT ( env );

	if ( env->number_of_moon_settings )
	{

		main_light_setting
			*old_light,
			*light;

		int
			weathermode;

		//
		// Free the memory for these settings up.
		//

		for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
		{

			if ( env->moon_settings[weathermode] )
			{

				light = env->moon_settings[weathermode];

				while ( light )
				{

					old_light = light;

					light = light->succ;

					safe_free ( old_light );
				}

				env->moon_settings[weathermode] = NULL;
			}
		}
	}

	env->number_of_moon_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_moon_setting ( env_3d *env, weathermodes weathermode, float scale, float shadow, rgb_colour object_colour, float object_intensity, rgb_colour light_colour, float light_intensity, float heading, float pitch, int main_light, float time )
{

	main_light_setting
		*light;

	float
		r,
		g,
		b;

	ASSERT ( env );

	light = ( main_light_setting * ) safe_malloc ( sizeof ( main_light_setting ) );
	memset ( light, 0, sizeof ( *light ) );

	r = light_colour.r;
	g = light_colour.g;
	b = light_colour.b;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;

	r *= light_intensity;
	g *= light_intensity;
	b *= light_intensity;

	light->light__colour.red = r;
	light->light__colour.green = g;
	light->light__colour.blue = b;

	r = object_colour.r;
	g = object_colour.g;
	b = object_colour.b;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;

	r *= object_intensity;
	g *= object_intensity;
	b *= object_intensity;

	light->object_colour.red = r;
	light->object_colour.green = g;
	light->object_colour.blue = b;

	light->time = time;

	light->heading = heading;
	light->pitch = pitch;

	light->scale = scale;

	light->shadow = shadow;

	light->main_light = main_light;

	if ( env->moon_settings[weathermode] )
	{

		main_light_setting
			*this_light,
			*last_light;

		env->number_of_moon_settings++;

		last_light = env->moon_settings[weathermode];

		this_light = env->moon_settings[weathermode];

		while ( this_light )
		{

			if ( this_light->time > light->time )
			{

				//
				// Insert *before* this_light
				//

				if ( last_light == this_light )
				{

					light->succ = env->moon_settings[weathermode];

					env->moon_settings[weathermode] = light;

					return;
				}
				else
				{

					last_light->succ = light;

					light->succ = this_light;

					return;
				}
			}
			else
			{

				last_light = this_light;

				this_light = this_light->succ;
			}
		}

		//
		// Got to the end of the list, and have to put it here.
		//

		light->succ = NULL;

		last_light->succ = light;
	}
	else
	{

		env->number_of_moon_settings++;

		env->moon_settings[weathermode] = light;

		light->succ = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_cloud_light_settings ( env_3d *env )
{

	int
		weathermode;

	ASSERT ( env );

	env->number_of_cloud_light_settings = 0;

	for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
	{

		env->cloud_light_settings[weathermode] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_cloud_light_settings ( env_3d *env )
{

	ASSERT ( env );

	if ( env->number_of_cloud_light_settings )
	{

		int
			weathermode;

		main_light_setting
			*old_light,
			*light;

		for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
		{

			if ( env->cloud_light_settings[weathermode] )
			{

				light = env->cloud_light_settings[weathermode];

				while ( light )
				{

					old_light = light;

					light = light->succ;

					safe_free ( old_light );
				}

				env->cloud_light_settings[weathermode] = NULL;
			}
		}
	}

	env->number_of_cloud_light_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_cloud_light_setting ( env_3d *env, weathermodes mode, rgb_colour colour, rgb_colour object_colour, float heading, float pitch, float time )
{

	main_light_setting
		*light;

	ASSERT ( env );

	light = ( main_light_setting * ) safe_malloc ( sizeof ( main_light_setting ) );
	memset ( light, 0, sizeof ( *light ) );

	light->light__colour.red = ( ( float ) colour.r ) / 255.0;
	light->light__colour.green = ( ( float ) colour.g ) / 255.0;
	light->light__colour.blue = ( ( float ) colour.b ) / 255.0;
	light->light__colour.alpha = ( ( float ) colour.a ) / 255.0;

	light->object_colour.red = ( ( float ) object_colour.r ) / 255.0;
	light->object_colour.green = ( ( float ) object_colour.g ) / 255.0;
	light->object_colour.blue = ( ( float ) object_colour.b ) / 255.0;
	light->object_colour.alpha = ( ( float ) object_colour.a ) / 255.0;

	light->time = time;
	light->heading = heading;
	light->pitch = pitch;

	if ( env->cloud_light_settings[mode] )
	{

		main_light_setting
			*this_light,
			*last_light;

		env->number_of_cloud_light_settings++;

		last_light = env->cloud_light_settings[mode];

		this_light = env->cloud_light_settings[mode];

		while ( this_light )
		{

			if ( this_light->time > light->time )
			{

				//
				// Insert *before* this_light
				//

				if ( last_light == this_light )
				{

					light->succ = env->cloud_light_settings[mode];

					env->cloud_light_settings[mode] = light;

					return;
				}
				else
				{

					last_light->succ = light;

					light->succ = this_light;

					return;
				}
			}
			else
			{

				last_light = this_light;

				this_light = this_light->succ;
			}
		}

		//
		// Got to the end of the list, and have to put it here.
		//

		light->succ = NULL;

		last_light->succ = light;
	}
	else
	{

		env->number_of_cloud_light_settings++;

		env->cloud_light_settings[mode] = light;

		light->succ = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_shadow_settings ( env_3d *env )
{

	int
		weathermode;

	ASSERT ( env );

	env->number_of_shadow_settings = 0;

	for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
	{

		env->shadow_settings[weathermode] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_3d_shadow_settings ( env_3d *env )
{

	ASSERT ( env );

	if ( env->number_of_shadow_settings )
	{

		int
			weathermode;

		main_light_setting
			*old_light,
			*light;

		for ( weathermode = WEATHERMODE_INVALID + 1; weathermode < WEATHERMODE_LAST; weathermode++ )
		{

			if ( env->shadow_settings[weathermode] )
			{

				light = env->shadow_settings[weathermode];

				while ( light )
				{

					old_light = light;

					light = light->succ;

					safe_free ( old_light );
				}

				env->shadow_settings[weathermode] = NULL;
			}
		}
	}

	env->number_of_shadow_settings = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_3d_shadow_setting ( env_3d *env, weathermodes mode, rgb_colour colour, float time )
{

	main_light_setting
		*light;

	float
		r,
		g,
		b;

	ASSERT ( env );

	light = ( main_light_setting * ) safe_malloc ( sizeof ( main_light_setting ) );
	memset ( light, 0, sizeof ( *light ) );

	r = colour.r;
	g = colour.g;
	b = colour.b;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;

	light->light__colour.red = r;
	light->light__colour.green = g;
	light->light__colour.blue = b;

	light->time = time;

	if ( env->shadow_settings[mode] )
	{

		main_light_setting
			*this_light,
			*last_light;

		env->number_of_shadow_settings++;

		last_light = env->shadow_settings[mode];

		this_light = env->shadow_settings[mode];

		while ( this_light )
		{

			if ( this_light->time > light->time )
			{

				//
				// Insert *before* this_light
				//

				if ( last_light == this_light )
				{

					light->succ = env->shadow_settings[mode];

					env->shadow_settings[mode] = light;

					return;
				}
				else
				{

					last_light->succ = light;

					light->succ = this_light;

					return;
				}
			}
			else
			{

				last_light = this_light;

				this_light = this_light->succ;
			}
		}

		//
		// Got to the end of the list, and have to put it here.
		//

		light->succ = NULL;

		last_light->succ = light;
	}
	else
	{

		env->number_of_shadow_settings++;

		env->shadow_settings[mode] = light;

		light->succ = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Now all the routines that set the main light source directly etc.
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_ambient_light ( env_3d *env, light_colour *colour )
{

	ASSERT ( env );

	env->ambient_light = *colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_fog_colour ( env_3d *env, rgb_colour fog_colour )
{

	ASSERT ( env );

	env->fog_colour = fog_colour;
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

void add_3d_light_to_environment ( env_3d *env, light_3d_source *light )
{

	light_3d_source
		*lights;

	ASSERT ( env );

	//
	// Check that the light isn't in the environment already.
	//

	lights = env->secondary_light_sources;

	while ( lights )
	{

		if ( lights == light )
		{

			return;
		}
		else
		{

			lights = lights->succ;
		}
	}

	//
	// It isn't in the list - add it
	//

	light->succ = env->secondary_light_sources;

	light->pred = NULL;

	if ( env->secondary_light_sources )
	{

		env->secondary_light_sources->pred = light;
	}

	env->secondary_light_sources = light;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_global_3d_fog_scale_setting ( env_3d *env, float new_fog_scale )
{

	int
		mode;

	ASSERT ( env );

	//
	// Go through all the fog settings, altering the scale of each one to the new scale
	//

	for ( mode = WEATHERMODE_INVALID + 1; mode < WEATHERMODE_LAST; mode++ )
	{

		fog_setting
			*fog;

		fog = env->fog_settings[mode];

		while ( fog )
		{

			fog->scale = new_fog_scale;

			fog = fog->succ;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_3d_light_from_environment ( env_3d *env, light_3d_source *light )
{

	light_3d_source
		*lights;

	int
		in_list;

	ASSERT ( env );

	//
	// Check that the light is in the environment already.
	//

	in_list = FALSE;

	lights = env->secondary_light_sources;

	while ( lights )
	{

		if ( lights == light )
		{

			in_list = TRUE;

			break;
		}
		else
		{

			lights = lights->succ;
		}
	}

	if ( !in_list )
	{

		debug_fatal ( "Trying to remove light from environment, but its not in there in the first place!" );
	}
	else
	{

		//
		// Remove the light
		//

		if ( env->secondary_light_sources == light )
		{

			//
			// Remove from the head of the list
			//

			env->secondary_light_sources = light->succ;

			if ( light->succ )
			{

				light->succ->pred = NULL;
			}
		}
		else
		{

			if ( light->succ )
			{

				light->succ->pred = light->pred;
			}

			if ( light->pred )
			{

				light->pred->succ = light->succ;
			}
		}

		//
		// Destroy any lingering pointers
		//

		light->succ = NULL;

		light->pred = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recalculate_3d_environment_settings ( env_3d *env )
{

	ASSERT ( env );

	//
	// Calcualate the light settings
	//

	if ( env->lightmode == LIGHTMODE_AUTOMATIC_LIGHT )
	{

		calculate_3d_ambient_light ( env );

		calculate_3d_sun_light ( env );

		calculate_3d_moon_light ( env );

		calculate_3d_cloud_light ( env );

		calculate_3d_shadow_light ( env );
	}

	//
	// Update the positioning according to the time of day
	//

	update_3d_horizon ( env );

	if ( env->fogmode == FOGMODE_ON_AUTOMATIC )
	{

		env->fog_colour = env->horizon_3d_fog_colour;

		//
		// Calculate the fog start / end positions
		//

		calculate_3d_fog_settings ( env );
	}

	//
	// If this is the current 3d environment, update all the 3d variables
	//

	if ( env == active_3d_environment )
	{

		set_3d_active_environment ( env );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_3d_fog_settings ( env_3d *env )
{

	fog_setting
		start_fog,
		end_fog,
		result_fog;

	float
		weather_t;

	weathermodes
		start_mode,
		end_mode;

	ASSERT ( env );

	start_mode = get_3d_weathermode ( env );

	end_mode = get_3d_target_weathermode ( env );

	weather_t = get_3d_target_weathermode_transitional_status ( env );

	if ( weather_t == 0 )
	{

		end_mode = start_mode;
	}

	if ( weather_t == 1 )
	{

		start_mode = end_mode;
	}

	//
	// Bomb out if we don't have any fog settings
	//

	if ( !env->fog_settings[start_mode] )
	{

		debug_fatal ( "Unable to calculate the fog levels - no settings have been specified for weather mode %d", start_mode );
	}

	if ( !env->fog_settings[end_mode] )
	{

		debug_fatal ( "Unable to calculate the fog levels - no settings have been specified for weather mode %d", end_mode );
	}

	calculate_interpolated_fog_setting ( env->time_of_day, env->fog_settings[start_mode], &start_fog );

	calculate_interpolated_fog_setting ( env->time_of_day, env->fog_settings[end_mode], &end_fog );

	interpolate_two_fog_settings ( &result_fog, &start_fog, &end_fog, weather_t );

	env->fog_start = ( result_fog.start * result_fog.scale );
	env->fog_end = ( result_fog.end * result_fog.scale );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_3d_ambient_light ( env_3d *env )
{

	main_light_setting
		start_light,
		end_light,
		result_light;

	float
		weather_t;

	weathermodes
		start_mode,
		end_mode;

	ASSERT ( env );

	start_mode = get_3d_weathermode ( env );

	end_mode = get_3d_target_weathermode ( env );

	weather_t = get_3d_target_weathermode_transitional_status ( env );

	if ( weather_t == 0 )
	{

		end_mode = start_mode;
	}

	if ( weather_t == 1 )
	{

		start_mode = end_mode;
	}

	//
	// Bomb out if we don't have any ambient light settings
	//

	if ( !env->ambient_light_settings[start_mode] )
	{

		debug_fatal ( "Unable to calculate the ambient light - no settings have been specified for weather mode %d", start_mode );
	}

	if ( !env->ambient_light_settings[end_mode] )
	{

		debug_fatal ( "Unable to calculate the ambient light - no settings have been specified for weather mode %d", end_mode );
	}

	calculate_interpolated_light_setting ( env->time_of_day, env->ambient_light_settings[start_mode], &start_light );

	calculate_interpolated_light_setting ( env->time_of_day, env->ambient_light_settings[end_mode], &end_light );

	interpolate_two_light_settings ( &result_light, &start_light, &end_light, weather_t );

	env->ambient_light.red = result_light.light__colour.red;
	env->ambient_light.green = result_light.light__colour.green;
	env->ambient_light.blue = result_light.light__colour.blue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_3d_sun_light ( env_3d *env )
{

	main_light_setting
		start_light,
		end_light;

	float
		weather_t;

	weathermodes
		start_mode,
		end_mode;

	int
		sun_is_main_light;

	ASSERT ( env );

	//
	// Get the weather information
	//

	start_mode = get_3d_weathermode ( env );

	end_mode = get_3d_target_weathermode ( env );

	weather_t = get_3d_target_weathermode_transitional_status ( env );

	if ( weather_t == 0 )
	{

		end_mode = start_mode;
	}

	if ( weather_t == 1 )
	{

		start_mode = end_mode;
	}

	//
	// Bomb out if we don't have any sun light settings
	//

	if ( !env->sun_settings[start_mode] )
	{

		debug_fatal ( "Unable to calculate the sun light - no settings have been specified for mode %d", start_mode );
	}

	if ( !env->sun_settings[end_mode] )
	{

		debug_fatal ( "Unable to calculate the sun light - no settings have been specified for mode %d", end_mode );
	}

	sun_is_main_light = FALSE;

	calculate_interpolated_light_setting ( env->time_of_day, env->sun_settings[start_mode], &start_light );

	calculate_interpolated_light_setting ( env->time_of_day, env->sun_settings[end_mode], &end_light );

	interpolate_two_light_settings ( &env->sun_light, &start_light, &end_light, weather_t );

	//
	// Handle the case where there is only one light setting
	//

	set_3d_sun_position ( env->sun_light.heading, env->sun_light.pitch );

	set_3d_sun_colour ( &env->sun_light.object_colour );

	set_3d_sun_scale ( env->sun_light.scale );

	if ( env->sun_light.main_light )
	{

		matrix3x3
			sun_attitude;

		get_3d_transformation_matrix ( sun_attitude, env->sun_light.heading, env->sun_light.pitch, 0 );

		env->sun_3d_light.type = LIGHT_3D_TYPE_DIRECTIONAL;

		env->sun_3d_light.colour = env->sun_light.light__colour;
		env->sun_3d_light.intensity = ( env->sun_3d_light.colour.red * 0.3 ) + ( env->sun_3d_light.colour.green * 0.59 ) + ( env->sun_3d_light.colour.blue * 0.11 );

		env->sun_3d_light.light_direction.x = sun_attitude[2][0];
		env->sun_3d_light.light_direction.y = sun_attitude[2][1];
		env->sun_3d_light.light_direction.z = sun_attitude[2][2];

		env->shadows_enabled = TRUE * !!command_line_render_shadows;
		env->shadow_strength = env->sun_light.shadow;

		set_3d_sun_light_intensity ( env->sun_light.object_colour.alpha );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_3d_moon_light ( env_3d *env )
{

	main_light_setting
		start_light,
		end_light;

	float
		weather_t;

	weathermodes
		start_mode,
		end_mode;

	int
		moon_is_main_light;

	ASSERT ( env );

	//
	// Get the weather information
	//

	start_mode = get_3d_weathermode ( env );

	end_mode = get_3d_target_weathermode ( env );

	weather_t = get_3d_target_weathermode_transitional_status ( env );

	if ( weather_t == 0 )
	{

		end_mode = start_mode;
	}

	if ( weather_t == 1 )
	{

		start_mode = end_mode;
	}

	//
	// Bomb out if we don't have any sun light settings
	//

	if ( !env->moon_settings[start_mode] )
	{

		debug_fatal ( "Unable to calculate the moon light - no settings have been specified for mode %d", start_mode );
	}

	if ( !env->moon_settings[end_mode] )
	{

		debug_fatal ( "Unable to calculate the moon light - no settings have been specified for mode %d", end_mode );
	}

	moon_is_main_light = FALSE;

	calculate_interpolated_light_setting ( env->time_of_day, env->moon_settings[start_mode], &start_light );

	calculate_interpolated_light_setting ( env->time_of_day, env->moon_settings[end_mode], &end_light );

	interpolate_two_light_settings ( &env->moon_light, &start_light, &end_light, weather_t );

	//
	// Handle the case where there is only one light setting
	//

	set_3d_moon_position ( env->moon_light.heading, env->moon_light.pitch );

	set_3d_moon_colour ( &env->moon_light.object_colour );

	if ( env->moon_light.main_light )
	{

		matrix3x3
			moon_attitude;

		get_3d_transformation_matrix ( moon_attitude, env->moon_light.heading, env->moon_light.pitch, 0 );

		env->moon_3d_light.type = LIGHT_3D_TYPE_DIRECTIONAL;

		env->moon_3d_light.colour = env->moon_light.light__colour;
		env->moon_3d_light.intensity = ( env->moon_3d_light.colour.red * 0.3 ) + ( env->moon_3d_light.colour.green * 0.59 ) + ( env->moon_3d_light.colour.blue * 0.11 );

		env->moon_3d_light.light_direction.x = moon_attitude[2][0];
		env->moon_3d_light.light_direction.y = moon_attitude[2][1];
		env->moon_3d_light.light_direction.z = moon_attitude[2][2];

		env->shadows_enabled = FALSE;

		env->shadow_strength = env->moon_light.shadow;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_3d_cloud_light ( env_3d *env )
{

	main_light_setting
		start_light,
		end_light,
		result_light;

	float
		weather_t;

	weathermodes
		start_mode,
		end_mode;

	ASSERT ( env );

	start_mode = get_3d_weathermode ( env );

	end_mode = get_3d_target_weathermode ( env );

	weather_t = get_3d_target_weathermode_transitional_status ( env );

	if ( weather_t == 0 )
	{

		end_mode = start_mode;
	}

	if ( weather_t == 1 )
	{

		start_mode = end_mode;
	}

	//
	// Bomb out if we don't have any cloud light settings
	//

	if ( !env->cloud_light_settings[start_mode] )
	{

		debug_fatal ( "Unable to calculate the cloud light - no settings have been specified for weather mode %d", start_mode );
	}

	if ( !env->cloud_light_settings[end_mode] )
	{

		debug_fatal ( "Unable to calculate the cloud light - no settings have been specified for weather mode %d", end_mode );
	}

	calculate_interpolated_light_setting ( env->time_of_day, env->cloud_light_settings[start_mode], &start_light );

	calculate_interpolated_light_setting ( env->time_of_day, env->cloud_light_settings[end_mode], &end_light );

	interpolate_two_light_settings ( &result_light, &start_light, &end_light, weather_t );

	env->cloud_light.light__colour.red = result_light.light__colour.red;
	env->cloud_light.light__colour.green = result_light.light__colour.green;
	env->cloud_light.light__colour.blue = result_light.light__colour.blue;
	env->cloud_light.light__colour.alpha = result_light.light__colour.alpha;

	env->cloud_light.object_colour.red = result_light.object_colour.red;
	env->cloud_light.object_colour.green = result_light.object_colour.green;
	env->cloud_light.object_colour.blue = result_light.object_colour.blue;
	env->cloud_light.object_colour.alpha = result_light.object_colour.alpha;

	env->cloud_light.heading = result_light.heading;
	env->cloud_light.pitch = result_light.pitch;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_3d_shadow_light ( env_3d *env )
{

	main_light_setting
		start_light,
		end_light,
		result_light;

	float
		weather_t;

	weathermodes
		start_mode,
		end_mode;

	ASSERT ( env );

	start_mode = get_3d_weathermode ( env );

	end_mode = get_3d_target_weathermode ( env );

	weather_t = get_3d_target_weathermode_transitional_status ( env );

	if ( weather_t == 0 )
	{

		end_mode = start_mode;
	}

	if ( weather_t == 1 )
	{

		start_mode = end_mode;
	}

	//
	// Bomb out if we don't have any ambient light settings
	//

	if ( !env->shadow_settings[start_mode] )
	{

		debug_fatal ( "Unable to calculate the shadow light - no settings have been specified for weather mode %d", start_mode );
	}

	if ( !env->shadow_settings[end_mode] )
	{

		debug_fatal ( "Unable to calculate the shadow light - no settings have been specified for weather mode %d", end_mode );
	}

	calculate_interpolated_light_setting ( env->time_of_day, env->shadow_settings[start_mode], &start_light );

	calculate_interpolated_light_setting ( env->time_of_day, env->shadow_settings[end_mode], &end_light );

	interpolate_two_light_settings ( &result_light, &start_light, &end_light, weather_t );

	env->shadow_setting.light__colour.red = result_light.light__colour.red;
	env->shadow_setting.light__colour.green = result_light.light__colour.green;
	env->shadow_setting.light__colour.blue = result_light.light__colour.blue;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_interpolated_angle ( float angle1, float angle2, float t )
{

	float
		difference1,
		difference2;

	//
	// Both angles are between 0 and 2*PI - ( ie 0 -> 360 )
	//

	//
	// Find the smallest distance between angle1, and angle2
	//

	difference1 = angle2 - angle1;

	difference2 = ( angle2 + PI2 ) - angle1;

	if ( fabs ( difference1 ) <= fabs ( difference2 ) )
	{

		//
		// Interpolate as normal
		//

		return ( angle1 + ( difference1 * t ) );
	}
	else
	{

		float
			angle;

		angle = ( angle1 + ( difference2 * t ) );

		if ( angle < 0 )
		{

			angle += PI2;
		}

		if ( angle > PI2 )
		{

			angle -= PI2;
		}

		return ( angle );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
