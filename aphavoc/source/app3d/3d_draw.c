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

int
	application_3d_rain_active = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void render_infrared_interference ( int alpha );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_3d_rain_wind_values (entity *en, vec3d *rain_wind_unit_vector, float *rain_wind_velocity)
{
	vec3d
		v,
		wind_velocity;

	float
		true_velocity;

	ASSERT (en);

	ASSERT (rain_wind_unit_vector);

	get_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &v);

	get_session_wind_velocity_at_point (get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION), &wind_velocity);

	v.x -= wind_velocity.x;
	v.z -= wind_velocity.z;

	true_velocity = get_3d_vector_magnitude (&v);

	if (true_velocity < 0.01)
	{
		true_velocity = 0.0;

		v.x = 0.0;
		v.y = 0.0;
		v.z = 0.0;
	}
	else
	{
		normalise_3d_vector_given_magnitude (&v, true_velocity);
	}

	*rain_wind_unit_vector = v;

	*rain_wind_velocity = true_velocity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_main_3d_rain_wind (void)
{
	vec3d
		rain_wind_unit_vector;

	float
		rain_wind_velocity;

	if (in_cockpit)
	{
		get_3d_rain_wind_values (get_gunship_entity (), &rain_wind_unit_vector, &rain_wind_velocity);
	}
	else if (get_view_mode () == VIEW_MODE_EXTERNAL)
	{
		get_3d_rain_wind_values (get_camera_entity (), &rain_wind_unit_vector, &rain_wind_velocity);
	}
	else
	{
		//
		// this will happen if VIEW_MODE_SAFE (which should never happen)
		//

		rain_wind_unit_vector.x = 0.0;
		rain_wind_unit_vector.y = 0.0;
		rain_wind_unit_vector.z = 0.0;

		rain_wind_velocity = 0.0;
	}

	set_3d_rain_wind (&rain_wind_unit_vector, rain_wind_velocity);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_application_3d_scene ( void )
{

	if ( application_3d_rain_active )
	{
	
		update_3d_rain (main_3d_env, get_3d_time_of_day (main_3d_env), main_vp.attitude);
	
		update_3d_lightning_strikes ( main_3d_env );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_application_3d_scene (void)
{

	set_3d_active_environment (main_3d_env);

	set_3d_weathermode (main_3d_env, get_local_entity_int_value (get_session_entity (), INT_TYPE_WEATHER_MODE));

	set_3d_target_weathermode (main_3d_env, get_local_entity_int_value (get_session_entity (), INT_TYPE_TARGET_WEATHER_MODE));

	set_3d_target_weathermode_transitional_status (main_3d_env, get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS));

	set_3d_time_of_day (main_3d_env, get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY));

	set_3d_view_distances ( main_3d_env, 10000.0, 1.0, 1.0, 0.0 );

	if ( application_3d_rain_active )
	{
	
		set_main_3d_rain_wind ();
	}

	recalculate_3d_environment_settings (main_3d_env);

	if ( command_line_3d_visual_clear_edges )
	{

		//
		// If this is the fullscreen visual, draw the right & bottom edges of the screen in black first
		//

		if ( ( active_viewport.x_max == full_screen_x_max ) && ( active_viewport.y_max == full_screen_y_max ) )
		{

			if ( lock_screen ( active_screen ) )
			{

				rgb_colour
					black;


				black.r = 0;
				black.g = 0;
				black.b = 0;
				black.a = 255;

				draw_line ( active_viewport.x_max, active_viewport.y_min, active_viewport.x_max, active_viewport.y_max, black );

				draw_line ( active_viewport.x_min, active_viewport.y_max, active_viewport.x_max, active_viewport.y_max, black );

				unlock_screen ( active_screen );
			}
		}
	}

	if ( begin_3d_scene () )
	{

		clear_zbuffer_screen ();

		if ( active_screen != video_screen )
		{

			clear_zbuffer_screen_using_viewport ();
		}

		scan_3d_terrain ();

		if ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_OFF )
		{

			scan_3d_clouds ();
		}

		scan_local_entity_3d_objects (&main_vp);

		draw_3d_horizon ();

		if ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_OFF )
		{

			draw_3d_stars ();

			draw_3d_sun ();

			draw_3d_moon ();
		}

		draw_3d_scene ();

		if ( ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_OFF ) && ( application_3d_rain_active ) )
		{

			draw_3d_rain ();

			draw_3d_lightning_strikes ();
		}

		end_3d_scene ();
	}

	if ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_ON ) 
	{

		switch ( current_3d_noise_level )
		{

			case DISPLAY_3D_NOISE_LEVEL_NONE:
			{

				render_infrared_interference ( 64 );

				break;
			}

			case DISPLAY_3D_NOISE_LEVEL_LOW:
			{

				render_infrared_interference ( 96 );

				break;
			}

			case DISPLAY_3D_NOISE_LEVEL_MEDIUM:
			{

				render_infrared_interference ( 168 );

				break;
			}

			case DISPLAY_3D_NOISE_LEVEL_HIGH:
			{

				render_infrared_interference ( 240 );

				break;
			}
		}
	}
	
	// Jabberwock 031009 - Get fog for satellite
	
	if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_SATELLITE)
	{
		render_infrared_interference ( 0 ); // no matter, we use variable alpha anyway
	}
	
	// Jabberwock 031009 ends
	
	update_application_3d_scene ();

#if ( OEM_3DLABS_VERSION )

	if ( full_screen_3d_information )
	{

		char
			s[256];

		if ( lock_screen ( active_screen ) )
		{

			float
				y_addon,
				y;

			rgb_colour
				col;

			col.r = 255;
			col.g = 255;
			col.b = 255;

			y_addon = get_mono_font_char_height ('0');

			y = 5.0;

			set_mono_font_type ( MONO_FONT_TYPE_7X12 );

			set_mono_font_colour ( col );

			set_mono_font_position (5.0, y);

			sprintf (s, "%-20.20s: %.2f", "Frame rate", get_one_over_delta_time ());

			print_mono_font_string (s);

			y += y_addon;

			set_mono_font_position (5.0, y);

			sprintf (s, "%-20.20s: %d", "Number of triangles", total_number_of_d3d_triangles );

			print_mono_font_string (s);

			y += y_addon;

			set_mono_font_position (5.0, y);

			sprintf (s, "%-20.20s: %d x %d x %d", "Resolution", ( int ) full_screen_width, ( int ) full_screen_height, full_screen_colourdepth );

			print_mono_font_string (s);

			y += y_addon;

			set_mono_font_position (5.0, y);

			if ( object_3d_perform_lod_calculations )
			{

				sprintf (s, "%-20.20s: ON", "Object Lod:" );
			}
			else
			{

				sprintf (s, "%-20.20s: OFF", "Object Lod:" );
			}

			print_mono_font_string (s);

			unlock_screen (active_screen);
		}
	}

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_application_highres_screen ( int x, int y, int x_repeat, int y_repeat )
{

	float
		middle_origin_x,
		middle_origin_y,
		origin_x,
		origin_y;

	int
		in_recognition_guide,
		screen_width,
		screen_height;

	ddraw_flip_surface ();

	screen_width = get_screen_width ( video_screen );

	screen_height = get_screen_height ( video_screen );

	middle_origin_x = screen_width * x_repeat / 2;

	middle_origin_y = screen_height * y_repeat / 2;

	origin_x = middle_origin_x - ( x * screen_width );

	origin_y = middle_origin_y - ( y * screen_height );

	set_3d_origin ( main_3d_env, origin_x, origin_y );

	set_3d_viewcone ( main_3d_env, screen_width * x_repeat, screen_height * y_repeat, full_screen_width_view_angle, full_screen_height_view_angle );

	set_3d_active_environment (main_3d_env);

	set_3d_weathermode (main_3d_env, get_local_entity_int_value (get_session_entity (), INT_TYPE_WEATHER_MODE));

	set_3d_target_weathermode (main_3d_env, get_local_entity_int_value (get_session_entity (), INT_TYPE_TARGET_WEATHER_MODE));

	set_3d_target_weathermode_transitional_status (main_3d_env, get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS));

	set_3d_time_of_day (main_3d_env, get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY));

	set_main_3d_rain_wind ();

	update_3d_rain (main_3d_env, get_3d_time_of_day (main_3d_env), main_vp.attitude);

	recalculate_3d_environment_settings (main_3d_env);

	switch (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE))
	{

		case CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW:
		case CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW:
		case CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW:
		case CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW:
		{

			in_recognition_guide = TRUE;

			break;
		}

		default:
		{

			in_recognition_guide = FALSE;

			break;
		}
	}

	if ( begin_3d_scene ())
	{

//		set_d3d_int_state ( D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID );

		clear_zbuffer_screen ();

		if ( !in_recognition_guide )
		{
	
			scan_3d_terrain ();
	
			scan_3d_clouds ();
		}
		else
		{

			rgb_colour
				col;

			col.r = 255;
			col.g = 255;
			col.b = 255;
			col.a = 255;

			set_block ( 0, 0, screen_width - 1, screen_height - 1, col );
		}

		scan_local_entity_3d_objects (&main_vp);

		if ( !in_recognition_guide )
		{
	
			draw_3d_horizon ();
	
			draw_3d_stars ();
	
			draw_3d_sun ();
	
			draw_3d_moon ();
		}

		draw_3d_scene ();

		if ( !in_recognition_guide )
		{

			draw_3d_rain ();
	
			draw_3d_lightning_strikes ();
		}

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_application_ui_3d_scene (void)
{

	set_3d_active_environment (main_3d_env);

	set_3d_weathermode (main_3d_env, get_local_entity_int_value (get_session_entity (), INT_TYPE_WEATHER_MODE));

	set_3d_target_weathermode (main_3d_env, get_local_entity_int_value (get_session_entity (), INT_TYPE_TARGET_WEATHER_MODE));

	set_3d_target_weathermode_transitional_status (main_3d_env, get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS));

	set_3d_time_of_day (main_3d_env, get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY));

	set_main_3d_rain_wind ();

	recalculate_3d_environment_settings (main_3d_env);

	clear_zbuffer_screen ();

	scan_3d_terrain ();

	if ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_OFF )
	{

		scan_3d_clouds ();
	}

	scan_local_entity_3d_objects (&main_vp);

	draw_3d_horizon ();

	if ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_OFF )
	{

		draw_3d_stars ();

		draw_3d_sun ();

		draw_3d_moon ();
	}

	draw_3d_scene ();
/*
	if ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_OFF )
	{

		draw_3d_rain ();

		draw_3d_lightning_strikes ();
	}
*/
/*	if ( get_3d_infrared_mode ( main_3d_env ) == INFRARED_ON )
	{

		switch ( current_3d_noise_level )
		{

			case DISPLAY_3D_NOISE_LEVEL_NONE:
			{

				render_infrared_interference ( 64 );

				break;
			}

			case DISPLAY_3D_NOISE_LEVEL_LOW:
			{

				render_infrared_interference ( 96 );

				break;
			}

			case DISPLAY_3D_NOISE_LEVEL_MEDIUM:
			{

				render_infrared_interference ( 168 );

				break;
			}

			case DISPLAY_3D_NOISE_LEVEL_HIGH:
			{

				render_infrared_interference ( 240 );

				break;
			}
		}
	}
	*/

	update_application_3d_scene ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_application_3d_scene_to_texture (screen *scr, float size)
{
	set_3d_viewport ( main_3d_env, 0.0, 0.0, ( size - 0.001 ), ( size - 0.001 ) );
	set_3d_origin ( main_3d_env, ( size / 2 ), ( size / 2 ) );
	set_3d_active_environment (main_3d_env);

	set_3d_render_target ( scr );
	set_active_screen ( scr );

	if ( begin_3d_scene () )
	{
	
		clear_zbuffer_screen ();
		clear_zbuffer_screen_using_viewport ();
		scan_3d_terrain ();
		scan_local_entity_3d_objects (&main_vp);
		draw_3d_horizon ();
		draw_3d_sun ();
		draw_3d_moon ();
		draw_3d_scene ();
	
		end_3d_scene ();
	}

	finalise_3d_render_target_texture ( scr );

	set_3d_render_target ( video_screen );
	set_active_screen ( video_screen );

	set_3d_viewport ( main_3d_env, full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max );
	set_3d_origin ( main_3d_env, full_screen_x_min + (full_screen_width / 2.0), full_screen_y_min + (full_screen_height / 2.0) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_infrared_interference ( int alpha )
{

	float
		x1,
		y1,
		x2,
		y2;

	float
		noise;

	rgb_colour
		fog_colour;

	if ( !d3d_modulate_alpha )
	{

		//
		// Graphics card can't render the interference properly.... don't bother.
		//

		return;
	}

	get_3d_viewport ( main_3d_env, &x1, &y1, &x2, &y2 );

	fog_colour = get_3d_fog_colour ( main_3d_env );

	noise = sfrand1 ();

	if ( begin_3d_scene () )
	{

		vertex
			quad[4];

		real_colour
			colour,
			specular;

		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison ( FALSE );

		set_d3d_culling ( FALSE );

		set_d3d_texture_wrapping ( 0, TRUE  );

		set_d3d_flat_shaded_textured_renderstate ( get_system_texture_ptr ( TEXTURE_INDEX_NIGHT_VISION ) );

		colour.red = fog_colour.r;
		colour.green = fog_colour.g;
		colour.blue = fog_colour.b;
		
		// Jabberwock 031009 Use fog_colour alpha for variable fog
		
		if ((fog_colour.a) > 0)
		{
			colour.alpha = fog_colour.a;
		}
		else
		{
			colour.alpha = alpha;
		}
		
		// Jabberwock 031009 ends
		
		specular.red = 0;
		specular.green = 0;
		specular.blue = 0;
		specular.alpha = 255;

		quad[0].i = x1;
		quad[0].j = y1;
		quad[0].z = 0.5;
		quad[0].q = 0.5;
		quad[0].u = 0 + noise;
		quad[0].v = 0 + noise;

		quad[1].i = x2;
		quad[1].j = y1;
		quad[1].z = 0.5;
		quad[1].q = 0.5;
		quad[1].u = 2 + noise;
		quad[1].v = 0 + noise;

		quad[2].i = x2;
		quad[2].j = y2;
		quad[2].z = 0.5;
		quad[2].q = 0.5;
		quad[2].u = 2 + noise;
		quad[2].v = 2 + noise;

		quad[3].i = x1;
		quad[3].j = y2;
		quad[3].z = 0.5;
		quad[3].q = 0.5;
		quad[3].u = 0 + noise;
		quad[3].v = 2 + noise;

		quad[0].next_vertex = &quad[1];
		quad[1].next_vertex = &quad[2];
		quad[2].next_vertex = &quad[3];
		quad[3].next_vertex = NULL;

		draw_wbuffered_flat_shaded_textured_polygon ( quad, colour, specular );

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison ( TRUE );

		set_d3d_culling ( TRUE );

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

