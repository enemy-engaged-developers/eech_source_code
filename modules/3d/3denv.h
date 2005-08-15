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


enum INFRARED_MODES
{

	INFRARED_INVALID,
	INFRARED_OFF,
	INFRARED_ON,
};

typedef enum INFRARED_MODES infrared_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum LIGHTMODES
{

	LIGHTMODE_NO_LIGHT,
	LIGHTMODE_AUTOMATIC_LIGHT,
	LIGHTMODE_MANUAL_LIGHT,
};

typedef enum LIGHTMODES lightmodes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum FOGMODES
{

	FOGMODE_INVALID,
	FOGMODE_ON_AUTOMATIC,
	FOGMODE_ON_MANUAL,
	FOGMODE_OFF,
};

typedef enum FOGMODES fogmodes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum WEATHERMODES
{

	WEATHERMODE_INVALID,

	WEATHERMODE_DRY,
	WEATHERMODE_LIGHT_RAIN,
	WEATHERMODE_HEAVY_RAIN,
	WEATHERMODE_SNOW,

	WEATHERMODE_LAST
};

typedef enum WEATHERMODES weathermodes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum LIGHT_3D_TYPE
{

	LIGHT_3D_TYPE_INVALID,
	LIGHT_3D_TYPE_DIRECTIONAL,
	LIGHT_3D_TYPE_POINT,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LIGHT_COLOUR
{

	float
		red,
		green,
		blue,
		alpha;
};

typedef struct LIGHT_COLOUR light_colour;

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

	vec3d
		highlight_vector;

	light_colour
		colour;

	float
		intensity;

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
		scale,
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
		light__colour,
		object_colour;

	float
		heading,
		pitch,
		time,
		scale,
		shadow;

	int
		main_light;
};

typedef struct MAIN_LIGHT_SETTING main_light_setting;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)

struct HORIZON_COLOUR
{

	unsigned char
		blue,
		green,
		red,
		pad;
};

typedef struct HORIZON_COLOUR horizon_colour;

#pragma pack()

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
		// Zbuffer information
		//

		zbuffer_z_minimum_value,
		zbuffer_z_maximum_value,
		zbuffer_scaled_z_minimum_value,
		zbuffer_scaled_z_maximum_value,

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

	float
		shadow_strength;

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

extern env_3d
	*active_3d_environment;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Creation / destruction routines
//

extern env_3d *create_3d_environment ( void );

extern void destroy_3d_environment ( env_3d *env );

//
// Set routines
//

extern void set_3d_active_environment ( env_3d *env );

extern void set_3d_time_of_day ( env_3d *env, float time );

extern void set_3d_weathermode ( env_3d *env, weathermodes mode );

extern void set_3d_target_weathermode ( env_3d *env, weathermodes mode );

extern void set_3d_target_weathermode_transitional_status ( env_3d *env, float value );

extern void set_3d_infrared_mode ( env_3d *env, infrared_modes mode );

extern void set_3d_main_light_source ( env_3d *env, light_colour *colour, vec3d *direction, int shadows_enabled );

extern void set_3d_ambient_light ( env_3d *env, light_colour *colour );

extern void set_3d_fog_colour ( env_3d *env, struct REAL_COLOUR fog_colour );

//
// Adding information to the environment
//

extern void add_3d_fog_setting ( env_3d *env, weathermodes mode, float scale, float start, float end, float time );

extern void add_3d_ambient_light_setting ( env_3d *env, weathermodes mode, rgb_colour colour, float intensity, float time );

extern void add_3d_sun_setting ( env_3d *env, weathermodes mode, float scale, float shadow, rgb_colour object_colour, float object_intensity, rgb_colour light_colour, float light_intensity, float heading, float pitch, int main_light, float time );

extern void add_3d_moon_setting ( env_3d *env, weathermodes mode, float scale, float shadow, rgb_colour object_colour, float object_intensity, rgb_colour light_colour, float light_intensity, float heading, float pitch, int main_light, float time );

extern void add_3d_cloud_light_setting ( env_3d *env, weathermodes mode, rgb_colour colour, rgb_colour object_colour, float heading, float pitch, float time );

extern void add_3d_shadow_setting ( env_3d *env, weathermodes mode, rgb_colour colour, float time );

extern void add_3d_light_to_environment ( env_3d *env, light_3d_source *light );

extern void remove_3d_light_from_environment ( env_3d *env, light_3d_source *light );

//
// Get routines
//

extern env_3d *get_3d_active_environment ( void );

extern float get_3d_time_of_day ( env_3d *env );

extern float get_3d_delta_time ( env_3d *env );

extern weathermodes get_3d_weathermode ( env_3d *env );

extern weathermodes get_3d_target_weathermode ( env_3d *env );

extern float get_3d_target_weathermode_transitional_status ( env_3d *env );

extern enum INFRARED_MODES get_3d_infrared_mode ( env_3d *env );

extern rgb_colour get_3d_fog_colour ( env_3d *env );

//
// Recalculating the environment
//

extern void set_global_3d_fog_scale_setting ( env_3d *env, float new_fog_scale );

extern void recalculate_3d_environment_settings ( env_3d *env );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

