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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define WIPER_RATE  						(1.0 * ONE_SECOND)

#define CONTINUOUS_WIPE_INTERVAL		(0.0 * ONE_SECOND)

#define INTERMITTENT_WIPE_INTERVAL	(5.0 * ONE_SECOND)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LIGHT_RAIN_FALL_RATE 			(100.0)

#define HEAVY_RAIN_FALL_RATE	 		(600.0)

#define BLOWER_LIGHT_RAIN_FALL_RATE	(10.0)

#define BLOWER_HEAVY_RAIN_FALL_RATE	(20.0)

//
// tune CLEAR_RAIN_RATE to clear 'full' window in CLEAR_RAIN_TIME
//

#define CLEAR_RAIN_RATE					(1600.0)

#define CLEAR_RAIN_TIME				 	(60.0 * ONE_SECOND)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum RAIN_FALL_TYPES
{
	RAIN_FALL_TYPE_DRY,
	RAIN_FALL_TYPE_LIGHT,
	RAIN_FALL_TYPE_HEAVY
};

typedef enum RAIN_FALL_TYPES rain_fall_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen
	*pilot_wiped_rain_texture_screen,
	*co_pilot_wiped_rain_texture_screen;

int
	wiper_on,
	pilot_wiper,
	co_pilot_wiper;

wiper_modes
	wiper_mode;

wipe_types
	pilot_wipe_type,
	co_pilot_wipe_type;

float
	wiper_position;

rain_modes
	rain_mode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static screen
	*rain_texture_screen,
	*composite_rain_texture_screen,
	*composite_pilot_wiped_rain_texture_screen,
	*composite_co_pilot_wiped_rain_texture_screen;

static float
	wipe_interval,
	wipe_delay,
	rain_timer;

static int
	intermittent_wipe,
	wiper_pos1,
	wiper_pos2;

static rain_fall_types
	rain_fall_type;

static int
	rain_textures_enabled;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_wiper (void);

static void update_rain_effect (void);

static rain_fall_types get_rain_fall_type (void);

static void clear_full_rain_effect (screen *composite_rain_texture_screen);

static void clear_rain_effect (screen *composite_rain_texture_screen);

static void apply_full_rain_effect (screen *composite_rain_texture_screen);

static void apply_rain_effect (screen *composite_rain_texture_screen, int light_rate, int heavy_rate);

static void wipe_rain_effect (screen *wiped_rain_texture_screen, screen *composite_wiped_rain_texture_screen, wipe_types wipe_type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_virtual_cockpit_wiper_and_rain_effect (void)
{
	#if DEBUG_MODULE

	debug_watch ("wiper_on = %d", MT_INT, &wiper_on);

	debug_watch ("intermittent_wipe = %d", MT_INT, &intermittent_wipe);

	debug_watch ("wiper_mode = %d", MT_INT, &wiper_mode);

	debug_watch ("wiper_position = %f", MT_FLOAT, &wiper_position);

	debug_watch ("wiper_pos1 = %d", MT_INT, &wiper_pos1);

	debug_watch ("wiper_pos2 = %d", MT_INT, &wiper_pos2);

	debug_watch ("wipe_interval = %f", MT_FLOAT, &wipe_interval);

	debug_watch ("wipe_delay = %f", MT_FLOAT, &wipe_delay);

	debug_watch ("rain_mode = %d", MT_INT, &rain_mode);

	debug_watch ("rain_fall_type = %d", MT_INT, &rain_fall_type);

	debug_watch ("rain_timer = %f", MT_FLOAT, &rain_timer);

	#endif

	rain_texture_screen = create_screen_for_system_texture (TEXTURE_INDEX_RAIN);

	composite_rain_texture_screen = create_system_texture_screen (RAIN_TEXTURE_SIZE, RAIN_TEXTURE_SIZE, TEXTURE_INDEX_RAIN_EFFECT, TEXTURE_TYPE_MULTIPLEALPHA);

	composite_pilot_wiped_rain_texture_screen = create_system_texture_screen (RAIN_TEXTURE_SIZE, RAIN_TEXTURE_SIZE, TEXTURE_INDEX_PILOT_RAIN_WIPE_EFFECT, TEXTURE_TYPE_MULTIPLEALPHA);

	composite_co_pilot_wiped_rain_texture_screen = create_system_texture_screen (RAIN_TEXTURE_SIZE, RAIN_TEXTURE_SIZE, TEXTURE_INDEX_COPILOT_RAIN_WIPE_EFFECT, TEXTURE_TYPE_MULTIPLEALPHA);

	wiper_on = FALSE;

	wiper_mode = WIPER_MODE_STOWED;

	intermittent_wipe = FALSE;

	wiper_position = 0.0;

	wiper_pos1 = 0;

	wiper_pos2 = 0;

	wipe_interval = CONTINUOUS_WIPE_INTERVAL;

	wipe_delay = CONTINUOUS_WIPE_INTERVAL;

	rain_fall_type = get_rain_fall_type ();

	rain_timer = 0.0;

	rain_textures_enabled = get_global_graphics_rain_textures_enabled ();

	if (rain_fall_type == RAIN_FALL_TYPE_DRY)
	{
		rain_mode = RAIN_MODE_DRY;

		clear_full_rain_effect (composite_rain_texture_screen);

		if (pilot_wiper)
		{
			clear_full_rain_effect (composite_pilot_wiped_rain_texture_screen);
		}

		if (co_pilot_wiper)
		{
			clear_full_rain_effect (composite_co_pilot_wiped_rain_texture_screen);
		}
	}
	else
	{
		rain_mode = RAIN_MODE_APPLY;

		apply_full_rain_effect (composite_rain_texture_screen);

		if (pilot_wiper)
		{
			apply_full_rain_effect (composite_pilot_wiped_rain_texture_screen);
		}

		if (co_pilot_wiper)
		{
			apply_full_rain_effect (composite_co_pilot_wiped_rain_texture_screen);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_virtual_cockpit_wiper_and_rain_effect (void)
{
	destroy_screen (rain_texture_screen);

	destroy_screen (composite_rain_texture_screen);

	destroy_screen (composite_pilot_wiped_rain_texture_screen);

	destroy_screen (composite_co_pilot_wiped_rain_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_virtual_cockpit_wiper_and_rain_effect (void)
{
	if (rain_textures_enabled != get_global_graphics_rain_textures_enabled ())
	{
		if (!get_global_graphics_rain_textures_enabled ())
		{
			clear_full_rain_effect (composite_rain_texture_screen);

			if (pilot_wiper)
			{
				clear_full_rain_effect (composite_pilot_wiped_rain_texture_screen);
			}

			if (co_pilot_wiper)
			{
				clear_full_rain_effect (composite_co_pilot_wiped_rain_texture_screen);
			}
		}
	}

	rain_textures_enabled = get_global_graphics_rain_textures_enabled ();

	update_wiper ();

	if (rain_textures_enabled)
	{
		update_rain_effect ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_wiper_on (void)
{
	wiper_on ^= 1;

	wipe_delay = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_intermittent_wipe (void)
{
	if (intermittent_wipe)
	{
		intermittent_wipe = FALSE;

		wipe_interval = CONTINUOUS_WIPE_INTERVAL;

		wipe_delay = CONTINUOUS_WIPE_INTERVAL;
	}
	else
	{
		intermittent_wipe = TRUE;

		wipe_interval = INTERMITTENT_WIPE_INTERVAL;

		wipe_delay = INTERMITTENT_WIPE_INTERVAL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_wiper (void)
{
	wiper_pos1 = wiper_pos2;

	switch (wiper_mode)
	{
		////////////////////////////////////////
		case WIPER_MODE_STOWED:
		////////////////////////////////////////
		{
			if (wiper_on)
			{
				wipe_delay -= get_delta_time ();

				if (wipe_delay < 0.0)
				{
					wiper_mode = WIPER_MODE_EXTEND_SWEEP;

					wipe_delay = wipe_interval;
				}
			}

			wiper_position = MIN_WIPER_POSITION;

			break;
		}
		////////////////////////////////////////
		case WIPER_MODE_EXTEND_SWEEP:
		////////////////////////////////////////
		{
			wiper_position += (MAX_WIPER_POSITION - MIN_WIPER_POSITION) * WIPER_RATE * get_delta_time ();

			if (wiper_position > MAX_WIPER_POSITION)
			{
				wiper_position = MAX_WIPER_POSITION;

				wiper_mode = WIPER_MODE_RETURN_SWEEP;
			}

			break;
		}
		////////////////////////////////////////
		case WIPER_MODE_RETURN_SWEEP:
		////////////////////////////////////////
		{
			wiper_position -= (MAX_WIPER_POSITION - MIN_WIPER_POSITION) * WIPER_RATE * get_delta_time ();

			if (wiper_position < MIN_WIPER_POSITION)
			{
				wiper_position = MIN_WIPER_POSITION;

				if ((!wiper_on) || intermittent_wipe)
				{
					wiper_mode = WIPER_MODE_STOWED;
				}
				else
				{
					wiper_mode = WIPER_MODE_EXTEND_SWEEP;
				}
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid wiper mode = %d", wiper_mode);

			break;
		}
	}

	convert_float_to_int (wiper_position, &wiper_pos2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_rain_effect (void)
{
	rain_fall_type = get_rain_fall_type ();

	switch (rain_mode)
	{
		////////////////////////////////////////
		case RAIN_MODE_DRY:
		////////////////////////////////////////
		{
			if (rain_fall_type != RAIN_FALL_TYPE_DRY)
			{
				rain_mode = RAIN_MODE_APPLY;

				rain_timer = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case RAIN_MODE_APPLY:
		////////////////////////////////////////
		{
			if (rain_fall_type == RAIN_FALL_TYPE_DRY)
			{
				rain_mode = RAIN_MODE_CLEAR;

				rain_timer = CLEAR_RAIN_TIME;

				break;
			}

			apply_rain_effect (composite_rain_texture_screen, LIGHT_RAIN_FALL_RATE, HEAVY_RAIN_FALL_RATE);

			if (pilot_wiper)
			{
				if (pilot_wipe_type == WIPE_TYPE_BLOWER)
				{
					apply_rain_effect (composite_pilot_wiped_rain_texture_screen, BLOWER_LIGHT_RAIN_FALL_RATE, BLOWER_HEAVY_RAIN_FALL_RATE);

					clear_rain_effect (composite_pilot_wiped_rain_texture_screen);
				}
				else
				{
					apply_rain_effect (composite_pilot_wiped_rain_texture_screen, LIGHT_RAIN_FALL_RATE, HEAVY_RAIN_FALL_RATE);

					wipe_rain_effect (pilot_wiped_rain_texture_screen, composite_pilot_wiped_rain_texture_screen, pilot_wipe_type);
				}
			}

			if (co_pilot_wiper)
			{
				if (co_pilot_wipe_type == WIPE_TYPE_BLOWER)
				{
					apply_rain_effect (composite_co_pilot_wiped_rain_texture_screen, BLOWER_LIGHT_RAIN_FALL_RATE, BLOWER_HEAVY_RAIN_FALL_RATE);

					clear_rain_effect (composite_co_pilot_wiped_rain_texture_screen);
				}
				else
				{
					apply_rain_effect (composite_co_pilot_wiped_rain_texture_screen, LIGHT_RAIN_FALL_RATE, HEAVY_RAIN_FALL_RATE);

					wipe_rain_effect (co_pilot_wiped_rain_texture_screen, composite_co_pilot_wiped_rain_texture_screen, co_pilot_wipe_type);
				}
			}

			break;
		}
		////////////////////////////////////////
		case RAIN_MODE_CLEAR:
		////////////////////////////////////////
		{
			if (rain_fall_type != RAIN_FALL_TYPE_DRY)
			{
				rain_mode = RAIN_MODE_APPLY;

				rain_timer = 0.0;

				break;
			}

			rain_timer -= get_delta_time ();

			if (rain_timer < 0.0)
			{
				rain_mode = RAIN_MODE_DRY;

				rain_timer = 0.0;

				clear_full_rain_effect (composite_rain_texture_screen);

				if (pilot_wiper)
				{
					clear_full_rain_effect (composite_pilot_wiped_rain_texture_screen);
				}

				if (co_pilot_wiper)
				{
					clear_full_rain_effect (composite_co_pilot_wiped_rain_texture_screen);
				}

				break;
			}

			clear_rain_effect (composite_rain_texture_screen);

			if (pilot_wiper)
			{
				clear_rain_effect (composite_pilot_wiped_rain_texture_screen);

				if (pilot_wipe_type != WIPE_TYPE_BLOWER)
				{
					wipe_rain_effect (pilot_wiped_rain_texture_screen, composite_pilot_wiped_rain_texture_screen, pilot_wipe_type);
				}
			}

			if (co_pilot_wiper)
			{
				clear_rain_effect (composite_co_pilot_wiped_rain_texture_screen);

				if (co_pilot_wipe_type != WIPE_TYPE_BLOWER)
				{
					wipe_rain_effect (co_pilot_wiped_rain_texture_screen, composite_co_pilot_wiped_rain_texture_screen, co_pilot_wipe_type);
				}
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rain_fall_types get_rain_fall_type (void)
{
	weathermodes
		weather_mode;

	vec3d
		*position;

	float
		altitude;

	rain_fall_types
		rain_fall_type;

	ASSERT (get_gunship_entity ());

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	altitude = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ALTITUDE);

	switch (weather_mode)
	{
		////////////////////////////////////////
		case WEATHERMODE_DRY:
		////////////////////////////////////////
		{
			rain_fall_type = RAIN_FALL_TYPE_DRY;

			break;
		}
		////////////////////////////////////////
		case WEATHERMODE_LIGHT_RAIN:
		////////////////////////////////////////
		{
			if (get_position_in_clouds (altitude) == POSITION_BELOW_CLOUDS)
			{
				rain_fall_type = RAIN_FALL_TYPE_LIGHT;
			}
			else
			{
				rain_fall_type = RAIN_FALL_TYPE_DRY;
			}

			break;
		}
		////////////////////////////////////////
		case WEATHERMODE_HEAVY_RAIN:
		////////////////////////////////////////
		{
			if (get_position_in_clouds (altitude) == POSITION_BELOW_CLOUDS)
			{
				rain_fall_type = RAIN_FALL_TYPE_HEAVY;
			}
			else
			{
				rain_fall_type = RAIN_FALL_TYPE_DRY;
			}

			break;
		}
		////////////////////////////////////////
		case WEATHERMODE_SNOW:
		////////////////////////////////////////
		{
			if (get_position_in_clouds (altitude) == POSITION_BELOW_CLOUDS)
			{
				rain_fall_type = RAIN_FALL_TYPE_LIGHT;
			}
			else
			{
				rain_fall_type = RAIN_FALL_TYPE_DRY;
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid weather mode = %d", weather_mode);

			break;
		}
	}

	return (rain_fall_type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_full_rain_effect (screen *composite_rain_texture_screen)
{
	unsigned char
		*composite_rain_texture_screen_data,
		*dst;

	int
		composite_rain_texture_screen_pitch,
		y;

	ASSERT (composite_rain_texture_screen);

	if (lock_screen (composite_rain_texture_screen))
	{

		int
			size;

		composite_rain_texture_screen_data = get_screen_data (composite_rain_texture_screen);
		composite_rain_texture_screen_pitch = get_screen_pitch (composite_rain_texture_screen);

		size = get_screen_pixel_width (composite_rain_texture_screen);

		dst = composite_rain_texture_screen_data;

		for (y = 0; y < RAIN_TEXTURE_SIZE; y++)
		{
			memset (dst, 0, RAIN_TEXTURE_SIZE * size);

			dst += composite_rain_texture_screen_pitch;
		}

		flush_screen_texture_graphics (composite_rain_texture_screen);

		unlock_screen (composite_rain_texture_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_rain_effect (screen *composite_rain_texture_screen)
{
	unsigned char
		*composite_rain_texture_screen_data,
		*dst;

	int
		composite_rain_texture_screen_pitch,
		count,
		x,
		y;

	ASSERT (composite_rain_texture_screen);

	if (lock_screen (composite_rain_texture_screen))
	{
		composite_rain_texture_screen_data = get_screen_data (composite_rain_texture_screen);
		composite_rain_texture_screen_pitch = get_screen_pitch (composite_rain_texture_screen);

		count = (int) (CLEAR_RAIN_RATE * get_delta_time ());

		if (get_screen_pixel_width(composite_rain_texture_screen) == 2)
		{

			while (count--)
			{
				x = rand16 () & (RAIN_TEXTURE_SIZE - 1);
				y = rand16 () & (RAIN_TEXTURE_SIZE - 1);

				dst = composite_rain_texture_screen_data + (y * composite_rain_texture_screen_pitch) + (x * sizeof (rgb_packed));

				*(rgb_packed *)dst = 0;
			}
		}
		else
		{

			while (count--)
			{
				x = rand16 () & (RAIN_TEXTURE_SIZE - 1);
				y = rand16 () & (RAIN_TEXTURE_SIZE - 1);

				dst = composite_rain_texture_screen_data + (y * composite_rain_texture_screen_pitch) + (x * sizeof (unsigned int));

				*(unsigned int *)dst = 0;
			}
		}

		flush_screen_texture_graphics (composite_rain_texture_screen);

		unlock_screen (composite_rain_texture_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_full_rain_effect (screen *composite_rain_texture_screen)
{

	ASSERT (composite_rain_texture_screen);

	if ( ( command_line_cpu_blit_textures ) || ( !d3d_modulate_alpha ) )
	{

		unsigned char
			*rain_texture_screen_data,
			*composite_rain_texture_screen_data,
			*src,
			*dst;

		int
			rain_texture_screen_pitch,
			composite_rain_texture_screen_pitch,
			y;

		ASSERT (composite_rain_texture_screen);

		if (lock_screen (rain_texture_screen))
		{
			rain_texture_screen_data = get_screen_data (rain_texture_screen);
			rain_texture_screen_pitch = get_screen_pitch (rain_texture_screen);

			if (lock_screen (composite_rain_texture_screen))
			{
				composite_rain_texture_screen_data = get_screen_data (composite_rain_texture_screen);
				composite_rain_texture_screen_pitch = get_screen_pitch (composite_rain_texture_screen);

				src = rain_texture_screen_data;

				dst = composite_rain_texture_screen_data;

				for (y = 0; y < RAIN_TEXTURE_SIZE; y++)
				{
					memcpy (dst, src, RAIN_TEXTURE_SIZE * sizeof (rgb_packed));

					src += rain_texture_screen_pitch;

					dst += composite_rain_texture_screen_pitch;
				}

				unlock_screen (composite_rain_texture_screen);
			}

			unlock_screen (rain_texture_screen);
		}
	}
	else
	{

		blit_screens ( rain_texture_screen, composite_rain_texture_screen,
								0, 0, RAIN_TEXTURE_SIZE, RAIN_TEXTURE_SIZE,
								0, 0, RAIN_TEXTURE_SIZE, RAIN_TEXTURE_SIZE );
	}

	flush_screen_texture_graphics (composite_rain_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_rain_effect (screen *composite_rain_texture_screen, int light_rate, int heavy_rate)
{

	float
		rain_fall_rate;

	int
		count,
		x1,
		y1,
		x2,
		y2;

	ASSERT (composite_rain_texture_screen);

	if (rain_fall_type == RAIN_FALL_TYPE_LIGHT)
	{
		rain_fall_rate = light_rate;
	}
	else
	{
		rain_fall_rate = heavy_rate;
	}

	count = (int) (rain_fall_rate * get_delta_time ());

	if ( ( command_line_cpu_blit_textures ) || ( !d3d_modulate_alpha ) )
	{

		unsigned char
			*rain_texture_screen_data,
			*composite_rain_texture_screen_data,
			*src,
			*dst;

		int
			texture_pixel_width,
			rain_texture_screen_pitch,
			composite_rain_texture_screen_pitch,
			x,
			y;

		rgb_packed
			col;

		unsigned int
			col32;

		texture_pixel_width = get_screen_pixel_width (rain_texture_screen);

		if (lock_screen (rain_texture_screen))
		{
			rain_texture_screen_data = get_screen_data (rain_texture_screen);
			rain_texture_screen_pitch = get_screen_pitch (rain_texture_screen);

			if (lock_screen (composite_rain_texture_screen))
			{
				composite_rain_texture_screen_data = get_screen_data (composite_rain_texture_screen);
				composite_rain_texture_screen_pitch = get_screen_pitch (composite_rain_texture_screen);

				if (texture_pixel_width == 2)
				{
					while (count--)
					{
						//
						// copy a random pixel from the rain texture to the composite texture
						//

						x = rand16 () & (RAIN_TEXTURE_SIZE - 1);
						y = rand16 () & (RAIN_TEXTURE_SIZE - 1);

						src = rain_texture_screen_data + (y * rain_texture_screen_pitch) + (x * sizeof (rgb_packed));

						col = *(rgb_packed *)src;

						dst = composite_rain_texture_screen_data + (y * composite_rain_texture_screen_pitch) + (x * sizeof (rgb_packed));

						*(rgb_packed *)dst = col;

						//
						// copy this pixel to an offset value to create a changing effect
						//

						x += 64;
						y += 64;

						x &= RAIN_TEXTURE_SIZE - 1;
						y &= RAIN_TEXTURE_SIZE - 1;

						dst = composite_rain_texture_screen_data + (y * composite_rain_texture_screen_pitch) + (x * sizeof (rgb_packed));

						*(rgb_packed *)dst = col;
					}
				}
				else
				{

					//
					// Texture pixel width == 4 ( 32bit texture )
					//

					while (count--)
					{
						//
						// copy a random pixel from the rain texture to the composite texture
						//

						x = rand16 () & (RAIN_TEXTURE_SIZE - 1);
						y = rand16 () & (RAIN_TEXTURE_SIZE - 1);

						src = rain_texture_screen_data + (y * rain_texture_screen_pitch) + (x * texture_pixel_width);

						col32 = *(unsigned int *)src;

						dst = composite_rain_texture_screen_data + (y * composite_rain_texture_screen_pitch) + (x * texture_pixel_width);

						*(unsigned int *)dst = col32;

						//
						// copy this pixel to an offset value to create a changing effect
						//

						x += 64;
						y += 64;

						x &= RAIN_TEXTURE_SIZE - 1;
						y &= RAIN_TEXTURE_SIZE - 1;

						dst = composite_rain_texture_screen_data + (y * composite_rain_texture_screen_pitch) + (x * texture_pixel_width);

						*(unsigned int *)dst = col32;
					}
				}

				unlock_screen (composite_rain_texture_screen);
			}

			unlock_screen (rain_texture_screen);
		}
	}
	else
	{

		while (count--)
		{
			//
			// copy a random pixel from the rain texture to the composite texture
			//

			x1 = rand16 () & (RAIN_TEXTURE_SIZE - 1);
			y1 = rand16 () & (RAIN_TEXTURE_SIZE - 1);

			blit_screens ( rain_texture_screen, composite_rain_texture_screen, x1, y1, x1+1, y1+1, x1, y1, x1+1, y1+1 );

			//
			// copy this pixel to an offset value to create a changing effect
			//

			x2 = x1 + 64;
			y2 = y1 + 64;

			x2 &= RAIN_TEXTURE_SIZE - 1;
			y2 &= RAIN_TEXTURE_SIZE - 1;

			blit_screens ( rain_texture_screen, composite_rain_texture_screen, x1, y1, x1+1, y1+1, x2, y2, x2+1, y2+1 );
		}
	}

	flush_screen_texture_graphics (composite_rain_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wipe_rain_effect (screen *wiped_rain_texture_screen, screen *composite_wiped_rain_texture_screen, wipe_types wipe_type)
{
	unsigned char
		*wiped_rain_texture_screen_data,
		*composite_wiped_rain_texture_screen_data,
		*src,
		*dst;

	int
		wiped_rain_texture_screen_pitch,
		composite_wiped_rain_texture_screen_pitch,
		pos1,
		pos2,
		pos3,
		x,
		y,
		x1,
		y1,
		x2,
		y2,
		dx,
		texture_pixel_width,
		src_add_on,
		dst_add_on;

	unsigned int
		r_mask,
		g_mask,
		b_mask,
		a_mask;

	ASSERT (wiped_rain_texture_screen);

	ASSERT (composite_wiped_rain_texture_screen);

	ASSERT (wipe_type != WIPE_TYPE_BLOWER);

	if (wiper_mode != WIPER_MODE_STOWED)
	{
		texture_pixel_width = get_screen_pixel_width (composite_wiped_rain_texture_screen);

		get_screen_rgba_masks (composite_wiped_rain_texture_screen, &r_mask, &g_mask, &b_mask, &a_mask);

		if (lock_screen (wiped_rain_texture_screen))
		{
			wiped_rain_texture_screen_data = get_screen_data (wiped_rain_texture_screen);
			wiped_rain_texture_screen_pitch = get_screen_pitch (wiped_rain_texture_screen);

			if (lock_screen (composite_wiped_rain_texture_screen))
			{
				composite_wiped_rain_texture_screen_data = get_screen_data (composite_wiped_rain_texture_screen);
				composite_wiped_rain_texture_screen_pitch = get_screen_pitch (composite_wiped_rain_texture_screen);

				switch (wipe_type)
				{
					////////////////////////////////////////
					case WIPE_TYPE_INVALID:
					////////////////////////////////////////
					{
						debug_fatal ("WIPE_TYPE_INVALID");

						break;
					}
					////////////////////////////////////////
					case WIPE_TYPE_LEFT_THEN_RIGHT:
					////////////////////////////////////////
					{
						pos1 = RAIN_TEXTURE_SIZE - 1 - wiper_pos1;
						pos2 = RAIN_TEXTURE_SIZE - 1 - wiper_pos2;

						if (pos1 > pos2)
						{
							pos3 = pos1;
							pos1 = pos2;
							pos2 = pos3;
						}

						x1 = pos1;
						y1 = 0;

						x2 = pos2;
						y2 = RAIN_TEXTURE_SIZE - 1;

						break;
					}
					////////////////////////////////////////
					case WIPE_TYPE_RIGHT_THEN_LEFT:
					////////////////////////////////////////
					{
						pos1 = wiper_pos1;
						pos2 = wiper_pos2;

						if (pos1 > pos2)
						{
							pos3 = pos1;
							pos1 = pos2;
							pos2 = pos3;
						}

						x1 = pos1;
						y1 = 0;

						x2 = pos2;
						y2 = RAIN_TEXTURE_SIZE - 1;

						break;
					}
					////////////////////////////////////////
					case WIPE_TYPE_UP_THEN_DOWN:
					////////////////////////////////////////
					{
						pos1 = RAIN_TEXTURE_SIZE - 1 - wiper_pos1;
						pos2 = RAIN_TEXTURE_SIZE - 1 - wiper_pos2;

						if (pos1 > pos2)
						{
							pos3 = pos1;
							pos1 = pos2;
							pos2 = pos3;
						}

						x1 = 0;
						y1 = pos1;

						x2 = RAIN_TEXTURE_SIZE - 1;
						y2 = pos2;

						break;
					}
					////////////////////////////////////////
					case WIPE_TYPE_DOWN_THEN_UP:
					////////////////////////////////////////
					{
						pos1 = wiper_pos1;
						pos2 = wiper_pos2;

						if (pos1 > pos2)
						{
							pos3 = pos1;
							pos1 = pos2;
							pos2 = pos3;
						}

						x1 = 0;
						y1 = pos1;

						x2 = RAIN_TEXTURE_SIZE - 1;
						y2 = pos2;

						break;
					}
				}

				dx = (x2 - x1 + 1) * texture_pixel_width;

				src_add_on = wiped_rain_texture_screen_pitch - dx;

				dst_add_on = composite_wiped_rain_texture_screen_pitch - dx;

				src = wiped_rain_texture_screen_data + (y1 * wiped_rain_texture_screen_pitch) + (x1 * texture_pixel_width);

				dst = composite_wiped_rain_texture_screen_data + (y1 * composite_wiped_rain_texture_screen_pitch) + (x1 * texture_pixel_width);

				if (texture_pixel_width == 2)
				{
					for (y = y1; y <= y2; y++)
					{
						for (x = x1; x <= x2; x++)
						{
							if ((*(rgb_packed *)src & a_mask) == 0)
							{
								*(rgb_packed *)dst = 0;
							}

							src += texture_pixel_width;
							dst += texture_pixel_width;
						}

						src += src_add_on;
						dst += dst_add_on;
					}
				}
				else
				{
					for (y = y1; y <= y2; y++)
					{
						for (x = x1; x <= x2; x++)
						{
							if ((*(unsigned int *)src & a_mask) == 0)
							{
								*(unsigned int *)dst = 0;
							}

							src += texture_pixel_width;
							dst += texture_pixel_width;
						}

						src += src_add_on;
						dst += dst_add_on;
					}
				}

				flush_screen_texture_graphics (composite_wiped_rain_texture_screen);

				unlock_screen (composite_wiped_rain_texture_screen);
			}

			unlock_screen (wiped_rain_texture_screen);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
