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

struct LIGHT_3D_SOURCE
{

	union
	{

		vec3d
			light_direction;

		vec3d
			light_position;

		struct
		{

			float
				lx,
				ly,
				lz;
		};

		struct
		{

			float
				x,
				y,
				z;
		};
	};

	light_colour
		colour;

	//
	// NB The radius is in fact the radius squared.
	//

	float
		radius;

	enum LIGHT_3D_TYPE
		type;

	struct LIGHT_3D_SOURCE
		*pred,
		*succ;
};

typedef struct LIGHT_3D_SOURCE light_3d_source;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FOG_SETTING
{

	struct FOG_SETTING
		*succ;

	float
		start,
		end,
		time;
};

typedef struct FOG_SETTING fog_setting;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MAIN_LIGHT_SETTING
{

	struct MAIN_LIGHT_SETTING
		*succ;

	light_colour
		light_colour,
		object_colour;

	float
		heading,
		pitch,
		time,
		scale;

	int
		main_light;
};

typedef struct MAIN_LIGHT_SETTING main_light_setting;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct HORIZON_COLOUR
{

	unsigned char
		blue,
		green,
		red,
		pad;
};

typedef struct HORIZON_COLOUR horizon_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct HORIZON_IMAGE_DATA
{

	struct HORIZON_IMAGE_DATA
		*succ;

	float
		time;

	rgb_colour
		fog_colour;

	horizon_colour
		*point_colours;
};

typedef struct HORIZON_IMAGE_DATA horizon_image_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ENV_3D
{

	float

		//
		// internal scaling variables, calculated from other variables in the structure
		//

		screen_i_scale,
		screen_j_scale,

		//
		// not used in transformation process, but used in calculating screen_i_scale, and screen_j_scale
		//

		width_view_angle,
		height_view_angle,

		//
		// specifies the centre of the 3d projection on the screen.
		//

		x_origin,
		y_origin,

		//
		// 3d clipping information ( yonder & hither planes )
		//

		yonder_distance,
		hither_distance,

		//
		// 2d screen clipping information
		//

		clip_xmin,
		clip_ymin,
		clip_xmax,
		clip_ymax;

	struct VIEWPOINT

		//
		// Information about where to view 3d world from
		//

		*view;

	fogmodes
		fogmode;

	int
		number_of_fog_settings;

	fog_setting
		*fog_settings[WEATHERMODE_LAST];

	float
		fog_start,
		fog_end;

	rgb_colour
		fog_colour;

	//
	// Light mode -	NO_LIGHT:			There is no lighting in the scene apart from the ambient light, and any specified lights.
	//						AUTOMATIC_LIGHT:	The lighting is calculated from all the light settings & time of day.
	//						MANUAL_LIGHT:		The lighting is user specifed
	//

	lightmodes
		lightmode;

	//
	// Automatic lighting settings
	//

	int
		number_of_ambient_light_settings,
		number_of_sun_settings,
		number_of_moon_settings,
		number_of_cloud_light_settings,
		number_of_shadow_settings;

	main_light_setting
		*ambient_light_settings[WEATHERMODE_LAST],
		*cloud_light_settings[WEATHERMODE_LAST],
		*sun_settings[WEATHERMODE_LAST],
		*moon_settings[WEATHERMODE_LAST],
		*shadow_settings[WEATHERMODE_LAST];

	main_light_setting
		sun_light,
		moon_light,
		cloud_light,
		shadow_setting;

	//
	// Main light settings - either set manually, or automatically
	//

	struct LIGHT_COLOUR
		ambient_light;

	light_3d_source
		sun_3d_light,
		moon_3d_light,
		main_3d_light;

	int
		shadows_enabled;

	//
	// Other light settings
	//

	light_3d_source
		*secondary_light_sources;

	//
	// Horizon rendering information
	//

	rgb_colour
		horizon_3d_fog_colour;
	
	horizon_colour
		*horizon_point_colours;

	int
		horizon_3d_scene_index,
		horizon_3d_object_number;

	float
		horizon_maximum_height;
	
	horizon_image_data
		*horizon_images_lists[WEATHERMODE_LAST];

	//
	// Infrared modes
	//

	infrared_modes
		infrared_mode;

	//
	// Weather mode - set to the current weather state - you must set this value
	//

	weathermodes
		weathermode;

	//
	// Weather target mode - if you are changing weather states, you must set this to the target mode
	//

	weathermodes
		target_weathermode;

	//
	// How near to the target weather mode it is ( value between 0 and 1 )
	//

	float
		weather_targetdistance;

	//
	// Time value from 0 up to a maximum of 86399.99999999999 - This is the number of seconds past midnight.
	//

	float
		time_of_day,
		delta_time;
};

typedef struct ENV_3D env_3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

