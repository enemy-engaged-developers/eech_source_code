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

struct SESSION
{
	////////////////////////////////////////
	//
	// ALWAYS KEEP THIS FIRST
	//

	int
		version_number;

	//
	////////////////////////////////////////

	list_root
		force_root,
		special_effect_root;

	list_link
		update_link;

	float
		start_time,
		elapsed_time,
		lightning_timer,
		time_of_day_resync,
		time_of_day_acceleration,
		fog_of_war_maximum_value;

	//
	// rain effect
	//

	float
		weather_radius,								// used for local weather model only
		weather_mode_transitional_period,		// used for global weather model only
		weather_mode_transitional_status;

	weathermodes
		weather_mode,
		target_weather_mode;

	vec3d
		weather_position,								// used for local weather model only
		weather_velocity;								// used for local weather model only

	//
	// wind effect
	//

	float
		wind_effect_radius,							// used for local weather model only
		wind_gusting_value,
		wind_minimum_speed,
		wind_maximum_speed;

	vec3d
		wind_direction_vector,
		wind_effect_position,						// used for local weather model only
		wind_effect_velocity;						// used for local weather model only

	//

	day_segment_types
		day_segment_type;

	float
		population_x_min, 							// population size of map (for Reduced games like Skirmishs)
		population_x_max,
		population_z_min,
		population_z_max;

	unsigned int
		campaign_medal								: NUM_CAMPAIGN_MEDAL_BITS,
		campaign_requires_apache_havoc		: NUM_CAMPAIGN_REQUIRES_APACHE_HAVOC_BITS,
		auto_assign_gunship						: NUM_AUTO_ASSIGN_GUNSHIP_BITS,
		session_complete							: NUM_SESSION_COMPLETE_BITS,
		infinite_fuel								: NUM_INFINITE_FUEL_BITS,
		infinite_weapons							: NUM_INFINITE_WEAPONS_BITS,
		suppress_ai_fire							: NUM_SUPPRESS_AI_FIRE_BITS,
		invulnerable_from_collisions			: NUM_INVULNERABLE_BITS,
		invulnerable_from_weapons				: NUM_INVULNERABLE_BITS,
		cheats_enabled								: NUM_CHEATS_ENABLED_BITS,
		skip_night_time							: NUM_SKIP_NIGHT_TIME_BITS,
		weather_increasing						: NUM_WEATHER_INCREASING_BITS,
		wind_increasing							: NUM_WEATHER_INCREASING_BITS,
		local_weather_model						: NUM_LOCAL_WEATHER_MODEL_BITS;
};

typedef struct SESSION session;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity
	*session_entity;

#define get_session_entity() (session_entity)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MIN_WEATHER_RADIUS	5000.0
#define MAX_WEATHER_RADIUS	100000.0
#define WEATHER_EXPANSION_RATE	100.0

#define WEATHER_EFFECT_SPEED			knots_to_metres_per_second (360.0f)

#define MIN_WIND_RADIUS	8000.0
#define MAX_WIND_RADIUS	128000.0
#define WIND_EXPANSION_RATE	200.0

#define WIND_EFFECT_SPEED				knots_to_metres_per_second (400.0f)

#define WIND_GUST_FREQUENCY	0.1

// magnitude of 0 to 15 knots works well with smoke effects
#define DEFAULT_MIN_WIND_SPEED		knots_to_metres_per_second (5.0f)
#define DEFAULT_MAX_WIND_SPEED		knots_to_metres_per_second (25.0f)

#define SESSION_RESYNC_FREQUENCY		ONE_MINUTE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float
	weather_rain_radius_min,
	weather_rain_radius_max,
	weather_rain_speed,
	weather_wind_radius_min,
	weather_wind_radius_max,
	weather_wind_speed;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_session_entity (entity *en);

extern float calculate_session_time_of_day (entity *en, int *day);

extern day_segment_types get_day_segment_type (float time_of_day);

extern float get_segment_time_of_day (day_segment_types segment);

extern float get_session_random_start_time_of_day (void);

extern float get_session_preset_time_of_day (session_time_of_day_settings preset_enum);

extern void get_session_weather_at_point (vec3d *pos, weathermodes *current_weather_mode, weathermodes *target_weather_mode, float *transitional_state);

extern weathermodes get_simple_session_weather_at_point (vec3d *pos);

extern void set_session_fixed_weather_mode (entity *en, weathermodes weather_mode);

extern void set_session_random_weather_mode (entity *en);

extern float get_session_wind_velocity_at_point (vec3d *pos, vec3d *wind_velocity);

extern void attach_session_sound_effects (entity *en);

extern int check_point_inside_population_area (vec3d *point);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ss_creat.h"

#include "ss_dstry.h"

#include "ss_float.h"

#include "ss_funcs.h"

#include "ss_int.h"

#include "ss_list.h"

#include "ss_msgs.h"

#include "ss_pack.h"

#include "ss_updt.h"

#include "ss_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
