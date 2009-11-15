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

static void modify_3d_objects_approximations ( float factor );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SUN_RISE_START_TIME	( 6.0 * ONE_HOUR )
#define SUN_RISE_END_TIME 		( 9.0 * ONE_HOUR )
#define MIDDAY_TIME				( 12.0 * ONE_HOUR )
#define SUN_SET_START_TIME		( 17.0 * ONE_HOUR )
#define SUN_SET_END_TIME		( 19.5 * ONE_HOUR )
#define TWILIGHT_TIME			( 22.0 * ONE_HOUR )
#define MIDNIGHT_TIME			( 0 * ONE_HOUR )
#define NIGHT_TIME				( 4.5 * ONE_HOUR )

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_application_3d_system (void)
{

  float light_level = max(min(1.0f,global_night_light_level),0.0f);
	
	
	
	ASSERT ( !main_3d_env );

	ASSERT ( !main_3d_single_light_env );

	//
	// 3D resolution
	//

	set_3d_resolutions (get_global_3d_visual_screen_width (), get_global_3d_visual_screen_height ());

	debug_log ( "Creating mfd 3d textures" );

	//
	// 3D textures
	//

	initialise_common_mfd_3d_textures ();

	initialise_campaign_screen_3d_textures ();

	//
	// Initialise 3ddata
	//

	debug_log ( "Loading textures" );

	load_texturemap_data ( "3ddata" );
	
	//VJ 060218 texture bug autosave fix, mapinfo was reinitialized each autosave
	// moved to beginning
	debug_log("###CUSTOM TEXTURE STARTUP: initialise_application_3d_system: initialise_custom_map_info");
	initialise_custom_map_info();

	initialise_3d_system ();

	initialise_3d_objects ( "3ddata" );

	initialise_3d_displacement_maps ( "3ddata\\displace.bin" );

	initialise_3d_terrain ();

	//
	//
	//

	initialise_common_crew_skins ();

	//
	// Initialise Default Terrain Data
	//

	set_3d_terrain_detail_blend_parameters ( 0.7 );
//set_3d_terrain_detail_blend_parameters ( 0 );

	//set_terrain_3d_sector_scan_radius ( 10 );
	set_terrain_3d_sector_scan_radius ( 5 );

	//
	// Initialise 3D environment
	//

	initialise_3d_lightning ( TEXTURE_ANIMATION_INDEX_LIGHTNING, TEXTURE_INDEX_LIGHTNING_BASE );

	main_3d_env = create_3d_environment ();

	{

		//
		// Initialise the horizon.
		//

		initialise_3d_horizon ( main_3d_env, OBJECT_3D_HORIZON );

		//
		// Dry weather mode images
		//

		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry6am",		SUN_RISE_START_TIME,	WEATHERMODE_DRY );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry9am",		SUN_RISE_END_TIME,	WEATHERMODE_DRY );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry12pm",	MIDDAY_TIME,			WEATHERMODE_DRY );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry3pm",		SUN_SET_START_TIME,	WEATHERMODE_DRY );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry6pm",		SUN_SET_END_TIME,		WEATHERMODE_DRY );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry9pm",		TWILIGHT_TIME,			WEATHERMODE_DRY );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry12am",	MIDNIGHT_TIME,			WEATHERMODE_DRY );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\dry12am",	NIGHT_TIME,				WEATHERMODE_DRY );

		//
		// light rain weather mode images
		//

		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr6am",		SUN_RISE_START_TIME,	WEATHERMODE_LIGHT_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr9am",		SUN_RISE_END_TIME,	WEATHERMODE_LIGHT_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr12pm",		MIDDAY_TIME,			WEATHERMODE_LIGHT_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr3pm",		SUN_SET_START_TIME,	WEATHERMODE_LIGHT_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr6pm",		SUN_SET_END_TIME,		WEATHERMODE_LIGHT_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr9pm",		TWILIGHT_TIME,			WEATHERMODE_LIGHT_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr12am",		MIDNIGHT_TIME,			WEATHERMODE_LIGHT_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\lr12am",		NIGHT_TIME,				WEATHERMODE_LIGHT_RAIN );

		//
		// heavy rain weather mode images
		//

		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr6am",		SUN_RISE_START_TIME,	WEATHERMODE_HEAVY_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr9am",		SUN_RISE_END_TIME,	WEATHERMODE_HEAVY_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr12pm",		MIDDAY_TIME,			WEATHERMODE_HEAVY_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr3pm",		SUN_SET_START_TIME,	WEATHERMODE_HEAVY_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr6pm",		SUN_SET_END_TIME,		WEATHERMODE_HEAVY_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr9pm",		TWILIGHT_TIME,			WEATHERMODE_HEAVY_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr12am",		MIDNIGHT_TIME,			WEATHERMODE_HEAVY_RAIN );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\hr12am",		NIGHT_TIME,				WEATHERMODE_HEAVY_RAIN );

		//
		// snow weather mode images
		//

		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow6am",	SUN_RISE_START_TIME,	WEATHERMODE_SNOW );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow9am",	SUN_RISE_END_TIME,	WEATHERMODE_SNOW );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow12pm",	MIDDAY_TIME,			WEATHERMODE_SNOW );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow3pm",	SUN_SET_START_TIME,	WEATHERMODE_SNOW );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow6pm",	SUN_SET_END_TIME,		WEATHERMODE_SNOW );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow9pm",	TWILIGHT_TIME,			WEATHERMODE_SNOW );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow12am",	MIDNIGHT_TIME,			WEATHERMODE_SNOW );
		add_3d_horizon_image ( main_3d_env, "3ddata\\horizon\\snow12am",	NIGHT_TIME,				WEATHERMODE_SNOW );
	}

	//
	// Initialise sun / moon / stars
	//

	initialise_3d_sun ( TEXTURE_INDEX_SUN, TEXTURE_INDEX_SUN_COLOUR_FLARE );

	initialise_3d_moon ( TEXTURE_INDEX_MOON );

	initialise_3d_stars ( "3ddata\\stars.bin" );

	//
	// Initialise the clouds
	//

	initialise_3d_clouds ();

	add_3d_cloud_texture ( TEXTURE_INDEX_CLOUDDRY, WEATHERMODE_DRY );

	add_3d_cloud_texture ( TEXTURE_INDEX_CLOUDLR, WEATHERMODE_LIGHT_RAIN );

	add_3d_cloud_texture ( TEXTURE_INDEX_CLOUDHR, WEATHERMODE_HEAVY_RAIN );

	add_3d_cloud_texture ( TEXTURE_INDEX_CLOUDSNOW, WEATHERMODE_SNOW );

	set_cloud_3d_base_height ( 6000 );

	set_cloud_3d_scan_radius ( 7 );

	//
	// Initialise the viewing system for the environment
	//

	set_3d_viewport ( main_3d_env, full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max );

	set_3d_origin ( main_3d_env, full_screen_x_min + (full_screen_width / 2.0), full_screen_y_min + (full_screen_height / 2.0) );

	set_3d_viewcone ( main_3d_env, full_screen_width, full_screen_height, rad ( 59.99 ), rad ( 46.82 ) );

#if RECOGNITION_GUIDE
	set_3d_view_distances ( main_3d_env, 10000.0, 100.0, 1.0, 0.0 );
#else
	set_3d_view_distances ( main_3d_env, 10000.0, 1.0, 1.0, 0.0 );
#endif

	//
	// Initialise the ambient lighting system for the environment
	//

	{

		rgb_colour
			ambient_colour[8];

		set_rgb_colour ( ambient_colour[0], 50, 50, 63, 0 );
		set_rgb_colour ( ambient_colour[1], 90, 97, 118, 0 );
		set_rgb_colour ( ambient_colour[2], 127, 127, 127, 0 );
		set_rgb_colour ( ambient_colour[3], 85, 100, 110, 0 );
		set_rgb_colour ( ambient_colour[4], 100, 40, 20, 0 );
		set_rgb_colour ( ambient_colour[5], 9, 34, 50, 0 );
		set_rgb_colour ( ambient_colour[6], 51, 51, 61, 0 );
		set_rgb_colour ( ambient_colour[7], 53, 53, 53, 0 );

#if RECOGNITION_GUIDE
		set_rgb_colour ( ambient_colour[0], 224, 224, 224, 0 );
		set_rgb_colour ( ambient_colour[1], 224, 224, 224, 0 );
		set_rgb_colour ( ambient_colour[2], 224, 224, 224, 0 );
		set_rgb_colour ( ambient_colour[3], 224, 224, 224, 0 );
		set_rgb_colour ( ambient_colour[4], 224, 224, 224, 0 );
		set_rgb_colour ( ambient_colour[5], 224, 224, 224, 0 );
		set_rgb_colour ( ambient_colour[6], 224, 224, 224, 0 );
		set_rgb_colour ( ambient_colour[7], 224, 224, 224, 0 );
#endif
    //VJ060920 night light level mod
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[0], 0.75, SUN_RISE_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[1], 0.75, SUN_RISE_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[2], 0.75, MIDDAY_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[3], 0.75, SUN_SET_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[4], 0.75, SUN_SET_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[5], 0.75, TWILIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[5], 0.75*light_level, MIDNIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[5], 0.75*light_level, NIGHT_TIME );

		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[6], 0.675, SUN_RISE_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[1], 0.675, SUN_RISE_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[2], 0.675, MIDDAY_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[3], 0.675, SUN_SET_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[7], 0.675, SUN_SET_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[5], 0.675, TWILIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[5], 0.675*light_level, MIDNIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[5], 0.675*light_level, NIGHT_TIME );

		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[6], 0.525, SUN_RISE_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[1], 0.525, SUN_RISE_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[2], 0.525, MIDDAY_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[3], 0.525, SUN_SET_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[7], 0.525, SUN_SET_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[5], 0.525, TWILIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[5], 0.525*light_level, MIDNIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[5], 0.525*light_level, NIGHT_TIME );

		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[6], 0.6, SUN_RISE_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[1], 0.6, SUN_RISE_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[2], 0.6, MIDDAY_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[3], 0.6, SUN_SET_START_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[7], 0.6, SUN_SET_END_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[5], 0.6, TWILIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[5], 0.6*light_level, MIDNIGHT_TIME );
		add_3d_ambient_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[5], 0.6*light_level, NIGHT_TIME );
	}

	//
	// Initialise the sun lighting system for the environment
	//

	{

		rgb_colour
			sun_colour[4],
			sun_light_colour[9];

		set_rgb_colour ( sun_colour[0], 255, 232, 112, 0 );	// Sun rise object colour
		set_rgb_colour ( sun_colour[1], 255, 243, 183, 128 );	// Sun rise imtermetiate colour
		set_rgb_colour ( sun_colour[2], 255, 255, 255, 255 );	// White object colour
		set_rgb_colour ( sun_colour[3], 255, 255, 255, 0 );	// White object colour - no flare

		set_rgb_colour ( sun_light_colour[0], 64, 58, 33, 0 );		// 6am ( 22% )
		set_rgb_colour ( sun_light_colour[1], 128, 116, 66, 0 );		// 9am ( 44% )
		set_rgb_colour ( sun_light_colour[2], 128, 128, 128, 0 );	// 12pm ( 50% )
		set_rgb_colour ( sun_light_colour[3], 125, 113, 98, 0 );		// 3pm ( 45% )
		set_rgb_colour ( sun_light_colour[4], 122, 23, 15, 0 ); 		// 6pm ( 20% )
		set_rgb_colour ( sun_light_colour[5], 55, 12, 1, 0 );			// 9pm ( 9% )
		set_rgb_colour ( sun_light_colour[6], 0, 0, 0, 0 );			// 12am, 3am ( 0% )
		set_rgb_colour ( sun_light_colour[7], 56, 56, 56, 0 );		// 6am rain colour( 22% )
		set_rgb_colour ( sun_light_colour[8], 51, 51, 51, 0 ); 		// 6pm rain colour ( 20% )

		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 1.0, sun_colour[0], 1.0, sun_light_colour[0], 1.5, rad ( 70 ), rad ( 0 ), TRUE, SUN_RISE_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 1.0, sun_colour[1], 1.0, sun_light_colour[1], 1.5, rad ( 70 ), rad ( 45 ), TRUE, SUN_RISE_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 1.0, sun_colour[2], 1.0, sun_light_colour[2], 1.5, rad ( 70 ), rad ( 90 ), TRUE, MIDDAY_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 1.0, sun_colour[2], 1.0, sun_light_colour[3], 1.5, rad ( 70 ), rad ( 135 ), TRUE, SUN_SET_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 2.0, 1.0, sun_colour[3], 1.0, sun_light_colour[4], 1.5, rad ( 70 ), rad ( 180 ), TRUE, SUN_SET_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 0.0, 0.0, sun_colour[3], 1.0, sun_light_colour[5], 1.5, rad ( 70 ), rad ( 225 ), TRUE, TWILIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 0.0, 0.0, sun_colour[3], 1.0, sun_light_colour[6], 1.5, rad ( 70 ), rad ( 270 ), FALSE, MIDNIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_DRY, 0.0, 0.0, sun_colour[3], 1.0, sun_light_colour[6], 1.5, rad ( 70 ), rad ( 315 ), TRUE, NIGHT_TIME );

		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.6, sun_colour[0], 0.70, sun_light_colour[7], 1.35, rad ( 90 ), rad ( 0 ), TRUE, SUN_RISE_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.6, sun_colour[1], 0.70, sun_light_colour[1], 1.35, rad ( 90 ), rad ( 45 ), TRUE, SUN_RISE_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.6, sun_colour[2], 0.70, sun_light_colour[2], 1.35, rad ( 90 ), rad ( 90 ), TRUE, MIDDAY_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.6, sun_colour[2], 0.70, sun_light_colour[3], 1.35, rad ( 90 ), rad ( 135 ), TRUE, SUN_SET_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 2.0, 0.6, sun_colour[2], 0.70, sun_light_colour[8], 1.35, rad ( 90 ), rad ( 180 ), TRUE, SUN_SET_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 0.0, 0.0, sun_colour[2], 0.70, sun_light_colour[5], 1.35, rad ( 90 ), rad ( 225 ), TRUE, TWILIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 0.0, 0.0, sun_colour[2], 0.70, sun_light_colour[6], 1.35, rad ( 90 ), rad ( 270 ), FALSE, MIDNIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 0.0, 0.0, sun_colour[2], 0.70, sun_light_colour[6], 1.35, rad ( 90 ), rad ( 315 ), TRUE, NIGHT_TIME );

		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.2, sun_colour[0], 0.05, sun_light_colour[7], 1.05, rad ( 90 ), rad ( 0 ), TRUE, SUN_RISE_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.2, sun_colour[1], 0.20, sun_light_colour[1], 1.05, rad ( 90 ), rad ( 45 ), TRUE, SUN_RISE_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.2, sun_colour[2], 0.20, sun_light_colour[2], 1.05, rad ( 90 ), rad ( 90 ), TRUE, MIDDAY_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.2, sun_colour[2], 0.20, sun_light_colour[3], 1.05, rad ( 90 ), rad ( 135 ), TRUE, SUN_SET_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 2.0, 0.2, sun_colour[2], 0.05, sun_light_colour[8], 1.05, rad ( 90 ), rad ( 180 ), TRUE, SUN_SET_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 0.0, 0.0, sun_colour[2], 0.20, sun_light_colour[5], 1.05, rad ( 90 ), rad ( 225 ), TRUE, TWILIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 0.0, 0.0, sun_colour[2], 0.20, sun_light_colour[6], 1.05, rad ( 90 ), rad ( 270 ), FALSE, MIDNIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 0.0, 0.0, sun_colour[2], 0.20, sun_light_colour[6], 1.05, rad ( 90 ), rad ( 315 ), TRUE, NIGHT_TIME );

		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.3, sun_colour[0], 0.10, sun_light_colour[7], 1.20, rad ( 90 ), rad ( 0 ), TRUE, SUN_RISE_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.3, sun_colour[1], 0.10, sun_light_colour[1], 1.20, rad ( 90 ), rad ( 45 ), TRUE, SUN_RISE_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.3, sun_colour[2], 0.10, sun_light_colour[2], 1.20, rad ( 90 ), rad ( 90 ), TRUE, MIDDAY_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.3, sun_colour[2], 0.10, sun_light_colour[3], 1.20, rad ( 90 ), rad ( 135 ), TRUE, SUN_SET_START_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 2.0, 0.3, sun_colour[2], 0.10, sun_light_colour[8], 1.20, rad ( 90 ), rad ( 180 ), TRUE, SUN_SET_END_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 0.0, 0.0, sun_colour[2], 0.10, sun_light_colour[5], 1.20, rad ( 90 ), rad ( 225 ), TRUE, TWILIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 0.0, 0.0, sun_colour[2], 0.10, sun_light_colour[6], 1.20, rad ( 90 ), rad ( 270 ), FALSE, MIDNIGHT_TIME );
		add_3d_sun_setting ( main_3d_env, WEATHERMODE_SNOW, 0.0, 0.0, sun_colour[2], 0.10, sun_light_colour[6], 1.20, rad ( 90 ), rad ( 315 ), TRUE, NIGHT_TIME );
	}


	//
	// Initialise the moon lighting system for the environment
	//

	{

		rgb_colour
			moon_colour[3],
			moon_light_colour[3];
 
    
		set_rgb_colour ( moon_colour[0],  0, 0, 0, 0 );
		set_rgb_colour ( moon_colour[1],  255, 255, 255, 0 );
		set_rgb_colour ( moon_colour[2],  255, 255, 255, 0 );

		set_rgb_colour ( moon_light_colour[0], 0, 0, 0, 0 );
		set_rgb_colour ( moon_light_colour[1], 23, 33, 41, 0 ); // 24% 9pm, 12am,
		set_rgb_colour ( moon_light_colour[2], 23, 33, 41, 0 ); // 24% 3am
    
    //VJ060920 night light level mod
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[0], 1.0, moon_light_colour[0], 1.0, rad ( 90 ), rad ( 180 ), FALSE, SUN_RISE_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[0], 1.0, moon_light_colour[0], 1.0, rad ( 90 ), rad ( 225 ), FALSE, SUN_RISE_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[0], 1.0, moon_light_colour[0], 1.0, rad ( 90 ), rad ( 270 ), FALSE, MIDDAY_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[0], 1.0, moon_light_colour[0], 1.0, rad ( 90 ), rad ( 315 ), FALSE, SUN_SET_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[0], 1.0, moon_light_colour[0], 1.0, rad ( 90 ), rad ( 0 ), TRUE, SUN_SET_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[1], 1.0, moon_light_colour[1], 1.0, rad ( 90 ), rad ( 45 ), TRUE, TWILIGHT_TIME );//VJ was 1.0
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[2], 1.0, moon_light_colour[2], light_level, rad ( 90 ), rad ( 90 ), TRUE, MIDNIGHT_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_DRY, 1.0, 0.0, moon_colour[2], 1.0, moon_light_colour[2], light_level, rad ( 90 ), rad ( 135 ), TRUE, NIGHT_TIME );

		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[0], 0.70, moon_light_colour[0], 0.90, rad ( 90 ), rad ( 180 ), FALSE, SUN_RISE_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[0], 0.70, moon_light_colour[0], 0.90, rad ( 90 ), rad ( 225 ), FALSE, SUN_RISE_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[0], 0.70, moon_light_colour[0], 0.90, rad ( 90 ), rad ( 270 ), FALSE, MIDDAY_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[0], 0.70, moon_light_colour[0], 0.90, rad ( 90 ), rad ( 315 ), FALSE, SUN_SET_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[0], 0.70, moon_light_colour[0], 0.90, rad ( 90 ), rad ( 0 ), TRUE, SUN_SET_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[1], 0.70, moon_light_colour[1], 0.90*light_level, rad ( 90 ), rad ( 45 ), TRUE, TWILIGHT_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[2], 0.70, moon_light_colour[2], 0.90*light_level, rad ( 90 ), rad ( 90 ), TRUE, MIDNIGHT_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, 1.0, 0.0, moon_colour[2], 0.70, moon_light_colour[2], 0.90*light_level, rad ( 90 ), rad ( 135 ), TRUE, NIGHT_TIME );

		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[0], 0.00, moon_light_colour[0], 0.70, rad ( 90 ), rad ( 180 ), FALSE, SUN_RISE_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[0], 0.00, moon_light_colour[0], 0.70, rad ( 90 ), rad ( 225 ), FALSE, SUN_RISE_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[0], 0.00, moon_light_colour[0], 0.70, rad ( 90 ), rad ( 270 ), FALSE, MIDDAY_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[0], 0.00, moon_light_colour[0], 0.70, rad ( 90 ), rad ( 315 ), FALSE, SUN_SET_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[0], 0.00, moon_light_colour[0], 0.70, rad ( 90 ), rad ( 0 ), TRUE, SUN_SET_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[1], 0.00, moon_light_colour[1], 0.70, rad ( 90 ), rad ( 45 ), TRUE, TWILIGHT_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[2], 0.00, moon_light_colour[2], 0.70*light_level, rad ( 90 ), rad ( 90 ), TRUE, MIDNIGHT_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, 1.0, 0.0, moon_colour[2], 0.00, moon_light_colour[2], 0.70*light_level, rad ( 90 ), rad ( 135 ), TRUE, NIGHT_TIME );

		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[0], 0.50, moon_light_colour[0], 0.80, rad ( 90 ), rad ( 180 ), FALSE, SUN_RISE_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[0], 0.50, moon_light_colour[0], 0.80, rad ( 90 ), rad ( 225 ), FALSE, SUN_RISE_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[0], 0.50, moon_light_colour[0], 0.80, rad ( 90 ), rad ( 270 ), FALSE, MIDDAY_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[0], 0.50, moon_light_colour[0], 0.80, rad ( 90 ), rad ( 315 ), FALSE, SUN_SET_START_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[0], 0.50, moon_light_colour[0], 0.80, rad ( 90 ), rad ( 0 ), TRUE, SUN_SET_END_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[1], 0.50, moon_light_colour[1], 0.80, rad ( 90 ), rad ( 45 ), TRUE, TWILIGHT_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[2], 0.50, moon_light_colour[2], 0.80*light_level, rad ( 90 ), rad ( 90 ), TRUE, MIDNIGHT_TIME );
		add_3d_moon_setting ( main_3d_env, WEATHERMODE_SNOW, 1.0, 0.0, moon_colour[2], 0.50, moon_light_colour[2], 0.80*light_level, rad ( 90 ), rad ( 135 ), TRUE, NIGHT_TIME );
	}


	//
	// Initialise the cloud lighting system for the environment
	//

	{

		rgb_colour
			ambient_colour[6],
			sun_light_colour[3];

		set_rgb_colour ( ambient_colour[0], 128, 128, 128, 64 );		// 6am ( 20% )
		set_rgb_colour ( ambient_colour[1], 196, 196, 196, 255 );		// 9am ( 38% )
		set_rgb_colour ( ambient_colour[2], 255, 255, 255, 255 );	// 12pm ( 60% )
		set_rgb_colour ( ambient_colour[3], 180, 180, 180, 255 );		// 3pm ( 38% )
		set_rgb_colour ( ambient_colour[4], 128, 128, 128, 255 );		// 6pm ( 21% )
		set_rgb_colour ( ambient_colour[5], 128, 128, 128, 255 );		// 9pm, 12am, 3am ( 2% )

		set_rgb_colour ( sun_light_colour[0], 0, 0, 0, 255 );			// No penumbra
		set_rgb_colour ( sun_light_colour[1], 59, 62, 76, 255 );		// 6am ( 24% )
		set_rgb_colour ( sun_light_colour[2], 122, 23, 15, 255 ); 		// 6pm ( 20% )

		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[1], sun_light_colour[1], rad ( 90 ), rad ( 0 ), SUN_RISE_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[2], ambient_colour[2], rad ( 90 ), rad ( 45 ), SUN_RISE_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[2], ambient_colour[2], rad ( 90 ), rad ( 90 ), MIDDAY_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[2], ambient_colour[2], rad ( 90 ), rad ( 135 ), SUN_SET_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[1], sun_light_colour[2], rad ( 90 ), rad ( 180 ), SUN_SET_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[0], ambient_colour[0], rad ( 90 ), rad ( 225 ), TWILIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[0], ambient_colour[0], rad ( 90 ), rad ( 270 ), MIDNIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_DRY, ambient_colour[0], ambient_colour[0], rad ( 90 ), rad ( 315 ), NIGHT_TIME );

		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[1], sun_light_colour[1], rad ( 90 ), rad ( 0 ), SUN_RISE_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 45 ), SUN_RISE_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 90 ), MIDDAY_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 135 ), SUN_SET_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[1], sun_light_colour[1], rad ( 90 ), rad ( 180 ), SUN_SET_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 225 ), TWILIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 270 ), MIDNIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 315 ), NIGHT_TIME );

		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[1], sun_light_colour[1], rad ( 90 ), rad ( 0 ), SUN_RISE_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 45 ), SUN_RISE_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 90 ), MIDDAY_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 135 ), SUN_SET_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[1], sun_light_colour[1], rad ( 90 ), rad ( 180 ), SUN_SET_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 225 ), TWILIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 270 ), MIDNIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 315 ), NIGHT_TIME );

		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[1], sun_light_colour[1], rad ( 90 ), rad ( 0 ), SUN_RISE_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 45 ), SUN_RISE_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 90 ), MIDDAY_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[2], sun_light_colour[2], rad ( 90 ), rad ( 135 ), SUN_SET_START_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[1], sun_light_colour[1], rad ( 90 ), rad ( 180 ), SUN_SET_END_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 225 ), TWILIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 270 ), MIDNIGHT_TIME );
		add_3d_cloud_light_setting ( main_3d_env, WEATHERMODE_SNOW, ambient_colour[0], sun_light_colour[0], rad ( 90 ), rad ( 315 ), NIGHT_TIME );
	}

	set_3d_lightmode ( main_3d_env, LIGHTMODE_AUTOMATIC_LIGHT );

	//
	// Initialise the fog settings
	//

	{

		float
			fog_scale;

		fog_scale = 1.0;

		add_3d_fog_setting ( main_3d_env, WEATHERMODE_DRY, fog_scale, 0.0, 7000.0, SUN_RISE_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_DRY, fog_scale, 0.0, 8000.0, SUN_RISE_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_DRY, fog_scale, 0.0, 8000.0, MIDDAY_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_DRY, fog_scale, 0.0, 8000.0, SUN_SET_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_DRY, fog_scale, 0.0, 7000.0, SUN_SET_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_DRY, fog_scale, 0.0, 6000.0, TWILIGHT_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_DRY, fog_scale, 0.0, 6000.0, NIGHT_TIME );

		add_3d_fog_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, fog_scale, 0.0, 6000.0, SUN_RISE_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, fog_scale, 0.0, 7000.0, SUN_RISE_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, fog_scale, 0.0, 7000.0, MIDDAY_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, fog_scale, 0.0, 7000.0, SUN_SET_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, fog_scale, 0.0, 6000.0, SUN_SET_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, fog_scale, 0.0, 5000.0, TWILIGHT_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, fog_scale, 0.0, 5000.0, NIGHT_TIME );

		add_3d_fog_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, fog_scale, 0.0, 4000.0, SUN_RISE_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, fog_scale, 0.0, 5000.0, SUN_RISE_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, fog_scale, 0.0, 5000.0, MIDDAY_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, fog_scale, 0.0, 5000.0, SUN_SET_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, fog_scale, 0.0, 4000.0, SUN_SET_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, fog_scale, 0.0, 3000.0, TWILIGHT_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, fog_scale, 0.0, 3000.0, NIGHT_TIME );

		add_3d_fog_setting ( main_3d_env, WEATHERMODE_SNOW, fog_scale, 0.0, 4000.0, SUN_RISE_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_SNOW, fog_scale, 0.0, 6000.0, SUN_RISE_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_SNOW, fog_scale, 0.0, 6000.0, MIDDAY_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_SNOW, fog_scale, 0.0, 6000.0, SUN_SET_START_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_SNOW, fog_scale, 0.0, 4000.0, SUN_SET_END_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_SNOW, fog_scale, 0.0, 3000.0, TWILIGHT_TIME );
		add_3d_fog_setting ( main_3d_env, WEATHERMODE_SNOW, fog_scale, 0.0, 3000.0, NIGHT_TIME );
	}

	//
	// Set the shadow colours
	//

	{

		rgb_colour
			shadow_colour[7];

		set_rgb_colour ( shadow_colour[0],  0, 0, 0, 0 );
		set_rgb_colour ( shadow_colour[1],  255, 0, 0, 0 );
		set_rgb_colour ( shadow_colour[2],  255, 255, 0, 0 );
		set_rgb_colour ( shadow_colour[3],  255, 255, 255, 0 );
		set_rgb_colour ( shadow_colour[4],  255, 255, 255, 0 );
		set_rgb_colour ( shadow_colour[5],  255, 255, 255, 0 );
		set_rgb_colour ( shadow_colour[6],  255, 255, 255, 0 );

		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[2], SUN_RISE_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[0], SUN_RISE_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[0], MIDDAY_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[0], SUN_SET_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[1], SUN_SET_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[0], TWILIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[0], MIDNIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_DRY, shadow_colour[0], NIGHT_TIME );

		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], SUN_RISE_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], SUN_RISE_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], MIDDAY_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], SUN_SET_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], SUN_SET_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], TWILIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], MIDNIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_LIGHT_RAIN, shadow_colour[0], NIGHT_TIME );

		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], SUN_RISE_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], SUN_RISE_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], MIDDAY_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], SUN_SET_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], SUN_SET_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], TWILIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], MIDNIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_HEAVY_RAIN, shadow_colour[0], NIGHT_TIME );

		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], SUN_RISE_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], SUN_RISE_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], MIDDAY_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], SUN_SET_START_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], SUN_SET_END_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], TWILIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], MIDNIGHT_TIME );
		add_3d_shadow_setting ( main_3d_env, WEATHERMODE_SNOW, shadow_colour[0], NIGHT_TIME );
	}

	//
	// Set the time of day for the environment
	//

	set_3d_time_of_day ( main_3d_env, ( 12 * ONE_HOUR ) );

	//
	// Set the initial weather mode
	//

	set_3d_weathermode ( main_3d_env, WEATHERMODE_DRY );

	set_3d_target_weathermode ( main_3d_env, WEATHERMODE_DRY );

	set_3d_target_weathermode_transitional_status ( main_3d_env, 0 );

	//
	// Sort out the initial fog values
	//

	set_3d_fogmode ( main_3d_env, FOGMODE_ON_AUTOMATIC );

	set_3d_fog_distances ( main_3d_env, 0.0, 10000.0 );

	//
	// Initialise the weather conditions
	//

	{

		vec3d
			position;

		position.x = 0;
		position.y = 0;
		position.z = 0;

		initialise_3d_rain ( 12 * ONE_HOUR, &position );

		set_3d_rain_speed ( 64 );

		position.x = 0;
		position.y = -1;
		position.z = 0;

		set_3d_rain_wind ( &position, 0 );

		set_3d_snow_texture ( TEXTURE_INDEX_SNOW_1 );
	}

	//
	// initialise viewpoint
	//

	get_3d_transformation_matrix (main_vp.attitude, 0.0, 0.0, 0.0);

	main_vp.x = MID_MAP_X;
	main_vp.z = MID_MAP_Z;
	main_vp.y = MID_MAP_Y;

	set_3d_viewpoint (main_3d_env, &main_vp);

	//
	// Initialise a second 3d environment - this time with just one main light, and ambient light
	//

	main_3d_single_light_env = create_3d_environment ();

	//
	// Initialise the viewing system for the environment
	//

	set_3d_viewport ( main_3d_single_light_env, full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max );

	set_3d_origin ( main_3d_single_light_env, full_screen_x_min + (full_screen_width / 2.0), full_screen_y_min + (full_screen_height / 2.0) );

	set_3d_viewcone ( main_3d_single_light_env, full_screen_width, full_screen_height, rad ( 59.99 ), rad ( 46.82 ) );

	set_3d_view_distances ( main_3d_single_light_env, 10000.0, 1.0, 1.0, 0.0 );

	//
	// Initalise the lighting conditions
	//

	set_3d_lightmode ( main_3d_single_light_env, LIGHTMODE_MANUAL_LIGHT );

	{

		light_colour
			single_light_ambient_colour,
			single_light_colour;

		vec3d
			single_light_direction;

		single_light_ambient_colour.red = 0.5;
		single_light_ambient_colour.green = 0.5;
		single_light_ambient_colour.blue = 0.5;

		set_3d_ambient_light ( main_3d_single_light_env, &single_light_ambient_colour );

		single_light_colour.red = 1.0;
		single_light_colour.green = 1.0;
		single_light_colour.blue = 1.0;

		single_light_direction.x = 0;
		single_light_direction.y = 0;
		single_light_direction.z = 1;

		set_3d_main_light_source ( main_3d_single_light_env, &single_light_colour, &single_light_direction, FALSE );
	}

	//
	// Set the weather modes, these are ignored anyway, but for completeness.
	//

	set_3d_weathermode ( main_3d_single_light_env, WEATHERMODE_DRY );

	set_3d_target_weathermode ( main_3d_single_light_env, WEATHERMODE_DRY );

	set_3d_target_weathermode_transitional_status ( main_3d_single_light_env, 0 );

	//
	// Sort out the initial fog values
	//

	set_3d_fogmode ( main_3d_single_light_env, FOGMODE_ON_MANUAL );

	set_3d_fog_distances ( main_3d_single_light_env, 0.0, 10000.0 );

	{

		rgb_colour
			single_light_fog_colour;

		single_light_fog_colour.r = 255;
		single_light_fog_colour.g = 255;
		single_light_fog_colour.b = 255;
		single_light_fog_colour.a = 255;

		set_3d_fog_colour ( main_3d_single_light_env, single_light_fog_colour );
	}

	//
	// Set the viewpoint used with this environent
	//

	set_3d_viewpoint ( main_3d_single_light_env, &main_vp );

	//
	// Set the initial detail levels
	//

	set_3d_detail_levels ();

	////////////////////////////////////////
	//

	original_d3d_can_render_to_texture = d3d_can_render_to_texture;

	//
	////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_application_3d_system (void)
{
	display_terrain_elevation_statistics ();

	destroy_3d_environment (main_3d_env);

	main_3d_env = NULL;

	destroy_3d_environment (main_3d_single_light_env);

	main_3d_single_light_env = NULL;

	//
	// 3D textures
	//

	deinitialise_common_mfd_3d_textures ();

	deinitialise_common_crew_skins ();

	deinitialise_campaign_screen_3d_textures ();

	//
	// In case there is a terrain loaded - free it up.
	//

	unload_3d_terrain ();

	unload_2d_terrain ();

	unload_terrain_simple_elevation_grid ();

	report_objects_not_destructed ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_detail_levels ( void )
{

	int
		level;

	float
		factor;

	//
	// Adjust the object detail levels
	//

	level = get_global_graphics_object_detail_level ();

	switch ( level )
	{

		case 1: factor = 0.5; break;
		case 2: factor = 0.7; break;
		case 3: factor = 1.0; break;
	}

	modify_3d_objects_approximations ( factor );

	//
	// Adjust the terrain detail levels
	//

	level = get_global_graphics_terrain_detail_level ();

	switch ( level )
	{

		case 1: factor = 0.7; break;
		case 2: factor = 0.85; break;
		case 3: factor = 1.0; break;
	}

	set_global_3d_fog_scale_setting ( main_3d_env, factor );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void modify_3d_objects_approximations ( float factor )
{

	scale_object_3d_approximation_distances ( OBJECT_3D_AH64D_APACHE_LONGBOW,	1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_UH60_BLACKHAWK,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_CH_3,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_CH_46,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_CH47D_CHINOOK,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_MI28N_HAVOC,				1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_KA29_HELIX_B,				1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_MI24_HIND,					1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_MI17_HIP,					1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_MI6_HOOK,					1.0 * factor );

	scale_object_3d_approximation_distances ( OBJECT_3D_A10A_THUNDERBOLT,		1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_F16_FIGHTING_FALCON,	1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_FA_18,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_MIG29_FULCRUM,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_HARRIER,					1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_HARRIER_DESTROYED,		1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_SU25,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_SU33,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_YAK_41,						1.0 * factor );

	scale_object_3d_approximation_distances ( OBJECT_3D_M730A1,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_SA13,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_SA13_DESTROYED,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_SA19_GRISON,				1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_SA19_GRISON_DESTROYED,	1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M_163_A1,					1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M_163_A1_DESTROYED,		1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M1A2_ABRAMS,				1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_BMP2,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_BMP3,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M2A2_BRADLEY,				1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_BRDM_2,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_BTR_80,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_T_80,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_2S19,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_BM_21,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M109A2,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_MLRS,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_HMMWV,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_HMMWV_DESTROYED,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M_923A1_COVERED,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M_923A1_OPEN,				1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M998,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M998_DESTROYED,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M_113_A1,					1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M_113_A1_DESTROYED,		1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_M_978,						1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_UAZ,							1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_UAZ_DESTROYED,			1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_URAL_4320,					1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_URAL_4320_DESTROYED,	1.0 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_URAL_FUEL,					1.0 * factor );

	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_AERIAL01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_AERIAL02,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_AIRPORT01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_BUILDING01,			0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_BUILDING02,			0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_CONTROL_TOWER01,		0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_FACTORY01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_FACTORY02,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_FACTORY03,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_FACTORY04,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_GUARD_POST01,			0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_HANGAR01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_HANGAR02,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_HANGAR03,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_HANGAR11,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_HANGAR12,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_HUT01,					0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_LAMP01,					0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_OIL_TANK01,			0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_OIL_TANK02,			0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_SHED01,					0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_TOWER_BUILDING01,	0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_WATER_TOWER01,		0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_AMERICAN_WATER_TOWER02,		0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_AIRPORT01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_BUILDING01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_BUILDING02,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_BUILDING03,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_BUILDING04,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_CONTROL_TOWER01,		0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_FACTORY01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_FACTORY02,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_FACTORY03,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_HANGAR01,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_HANGAR02,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_HANGAR03,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_HANGAR05,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_HANGAR07,				0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_LAMP01,					0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_LAMP02,					0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_RADAR01,					0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_SHED01,					0.7 * factor );
	scale_object_3d_approximation_distances ( OBJECT_3D_RUSSIAN_SHED02,					0.7 * factor );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_application_display_3d_mode (display_3d_tints tint, display_3d_light_levels light_level, display_3d_noise_levels noise_level)
{

	current_3d_display_tint = tint;

	current_3d_light_level = light_level;

	current_3d_noise_level = noise_level;

	switch (tint)
	{

		light_colour
			ambient_light,
			main_light;

		vec3d
			direction;

		rgb_colour
			fog_colour;

		case DISPLAY_3D_TINT_CLEAR:
		{

			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_AUTOMATIC_LIGHT );

			set_3d_infrared_mode ( main_3d_env, INFRARED_OFF );

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_AUTOMATIC );

			break;
		}

		case DISPLAY_3D_TINT_BLUEGREEN:
		{

			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_MANUAL_LIGHT );

			// start russian NVG WITHOUT FLIR by GCsDriver  08-12-2007
			if(command_line_russian_nvg_no_ir)
			{
				set_3d_infrared_mode ( main_3d_env, RENDER_MONOCHROME );
			}else{
				set_3d_infrared_mode ( main_3d_env, INFRARED_ON );
			}
			// end russian NVG WITHOUT FLIR by GCsDriver  08-12-2007

			//
			// Set the light in the scene
			//

			switch ( current_3d_light_level )
			{
				// start no red to avoid purple trees by GCsDriver  08-12-2007
				case DISPLAY_3D_LIGHT_LEVEL_LOW:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.468;
					ambient_light.blue = 0.4;

					main_light.red = 0.0;
					main_light.green = 0.15;
					main_light.blue = 0.12;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_MEDIUM:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.574;
					ambient_light.blue = 0.5;

					main_light.red = 0.0;
					main_light.green = 0.2;
					main_light.blue = 0.16;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_HIGH:
				{
					ambient_light.red = 0.0;
					ambient_light.green = 0.7;
					ambient_light.blue = 0.6;

					main_light.red = 0.0;
					main_light.green = 0.25;
					main_light.blue = 0.2;

					break;
				}
			}
			// end no red to avoid purple trees by GCsDriver  08-12-2007

			set_3d_ambient_light_source ( main_3d_env, &ambient_light );

			direction.x = -main_vp.zv.x;
			direction.y = -main_vp.zv.y;
			direction.z = -main_vp.zv.z;

			set_3d_main_light_source ( main_3d_env, &main_light, &direction, FALSE );

			//
			// Set the fogmode
			//

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_MANUAL );

			fog_colour.r = ambient_light.red * 128;
			fog_colour.g = ambient_light.green * 128;
			fog_colour.b = ambient_light.blue * 128;
			fog_colour.a = 0;

			set_3d_fog_colour ( main_3d_env, fog_colour );

			break;
			
		}

		case DISPLAY_3D_TINT_BLUE:
		{

			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_MANUAL_LIGHT );

			set_3d_infrared_mode ( main_3d_env, INFRARED_ON );

			//
			// Set the light in the scene
			//

			switch ( current_3d_light_level )
			{
				case DISPLAY_3D_LIGHT_LEVEL_LOW:
				{

					ambient_light.red = 0.25;
					ambient_light.green = 0.25;
					ambient_light.blue = 0.7;

					main_light.red = 0.0;
					main_light.green = 0.0;
					main_light.blue = 0.2;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_MEDIUM:
				{

					ambient_light.red = 0.4;
					ambient_light.green = 0.4;
					ambient_light.blue = 0.8;

					main_light.red = 0.0;
					main_light.green = 0.0;
					main_light.blue = 0.25;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_HIGH:
				{
					ambient_light.red = 0.6;
					ambient_light.green = 0.6;
					ambient_light.blue = 1.0;

					main_light.red = 0.3;
					main_light.green = 0.3;
					main_light.blue = 0.4;

					break;
				}
			}

			set_3d_ambient_light_source ( main_3d_env, &ambient_light );

			direction.x = -main_vp.zv.x;
			direction.y = -main_vp.zv.y;
			direction.z = -main_vp.zv.z;

			set_3d_main_light_source ( main_3d_env, &main_light, &direction, FALSE );

			//
			// Set the fogmode
			//

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_MANUAL );

			fog_colour.r = ambient_light.red * 128;
			fog_colour.g = ambient_light.green * 128;
			fog_colour.b = ambient_light.blue * 128;
			fog_colour.a = 0;

			set_3d_fog_colour ( main_3d_env, fog_colour );

			break;
		}

		case DISPLAY_3D_TINT_AMBER:
		case DISPLAY_3D_TINT_AMBER_VISUAL:
		{

			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_MANUAL_LIGHT );

			if (tint == DISPLAY_3D_TINT_AMBER_VISUAL)
				set_3d_infrared_mode ( main_3d_env, RENDER_MONOCHROME );
			else
				set_3d_infrared_mode ( main_3d_env, RENDER_INFRARED );

			//
			// Set the light in the scene
			//

			switch ( current_3d_light_level )
			{
				// start 3d effect by GCsDriver  08-12-2007
				case DISPLAY_3D_LIGHT_LEVEL_LOW:
				{

					ambient_light.red = 0.7;
					ambient_light.green = 0.35;
					ambient_light.blue = 0.0;

					main_light.red = 0.24;
					main_light.green = 0.12;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_MEDIUM:
				{

					ambient_light.red = 0.9;
					ambient_light.green = 0.45;
					ambient_light.blue = 0.0;

					main_light.red = 0.32;
					main_light.green = 0.16;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_HIGH:
				{
					ambient_light.red = 1.1;
					ambient_light.green = 0.55;
					ambient_light.blue = 0.0;

					main_light.red = 0.4;
					main_light.green = 0.2;
					main_light.blue = 0.0;

					break;
				}

				// end 3d effect by GCsDriver  08-12-2007
/* buggy
//VJ 060105 extra light level for PNVS
				case DISPLAY_3D_LIGHT_LEVEL_VERY_HIGH:
				{

					ambient_light.red = 1.2;
					ambient_light.green = 1.0;
					ambient_light.blue = 0.2;

					main_light.red = 0.5;
					main_light.green = 0.4;
					main_light.blue = 0.2;
					break;
				}
*/
			}

			set_3d_ambient_light_source ( main_3d_env, &ambient_light );

			direction.x = -main_vp.zv.x;
			direction.y = -main_vp.zv.y;
			direction.z = -main_vp.zv.z;

			set_3d_main_light_source ( main_3d_env, &main_light, &direction, FALSE );

			//
			// Set the fogmode
			//

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_MANUAL );

			fog_colour.r = ambient_light.red * 128;
			fog_colour.g = ambient_light.green * 128;
			fog_colour.b = ambient_light.blue * 0;
			fog_colour.a = 0;

			set_3d_fog_colour ( main_3d_env, fog_colour );

			break;
		}

		case DISPLAY_3D_TINT_GREEN:
		case DISPLAY_3D_TINT_GREEN_VISUAL:
		{

			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_MANUAL_LIGHT );

			if (tint == DISPLAY_3D_TINT_GREEN_VISUAL)
				set_3d_infrared_mode ( main_3d_env, RENDER_MONOCHROME );
			else
				set_3d_infrared_mode ( main_3d_env, RENDER_INFRARED );

			//
			// Set the light in the scene
			//

			switch ( current_3d_light_level )
			{

				case DISPLAY_3D_LIGHT_LEVEL_LOW:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.48;
					ambient_light.blue = 0.0;

					main_light.red = 0.0;
					main_light.green = 0.12;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_MEDIUM:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.64;
					ambient_light.blue = 0.0;

					main_light.red = 0.0;
					main_light.green = 0.16;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_HIGH:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.8;
					ambient_light.blue = 0.0;

					main_light.red = 0.0;
					main_light.green = 0.2;
					main_light.blue = 0.0;

					break;
				}
			}

			set_3d_ambient_light_source ( main_3d_env, &ambient_light );

			direction.x = -visual_3d_vp->zv.x;
			direction.y = -visual_3d_vp->zv.y;
			direction.z = -visual_3d_vp->zv.z;

			set_3d_main_light_source ( main_3d_env, &main_light, &direction, FALSE );

			//
			// Set the fogmode
			//

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_MANUAL );

			fog_colour.r = ambient_light.red * 0;
			fog_colour.g = ambient_light.green * 128;
			fog_colour.b = ambient_light.blue * 0;
			fog_colour.a = 0;

			set_3d_fog_colour ( main_3d_env, fog_colour );

			break;
		}

		case DISPLAY_3D_TINT_ORANGE:
		{

			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_MANUAL_LIGHT );

			set_3d_infrared_mode ( main_3d_env, INFRARED_ON );

			//
			// Set the light in the scene
			//

			switch ( current_3d_light_level )
			{

				case DISPLAY_3D_LIGHT_LEVEL_LOW:
				{

					ambient_light.red = 0.6;
					ambient_light.green = 0.468 * 0.5;
					ambient_light.blue = 0.0;

					main_light.red = 0.15;
					main_light.green = 0.12 * 0.5;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_MEDIUM:
				{

					ambient_light.red = 0.8;
					ambient_light.green = 0.624 * 0.5;
					ambient_light.blue = 0.0;

					main_light.red = 0.2;
					main_light.green = 0.16 * 0.5;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_HIGH:
				{

					ambient_light.red = 1.0;
					ambient_light.green = 0.78 * 0.5;
					ambient_light.blue = 0.0;

					main_light.red = 0.25;
					main_light.green = 0.2 * 0.5;
					main_light.blue = 0.0;

					break;
				}
			}

			set_3d_ambient_light_source ( main_3d_env, &ambient_light );

			direction.x = -main_vp.zv.x;
			direction.y = -main_vp.zv.y;
			direction.z = -main_vp.zv.z;

			set_3d_main_light_source ( main_3d_env, &main_light, &direction, FALSE );

			//
			// Set the fogmode
			//

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_MANUAL );

			fog_colour.r = ambient_light.red * 128;
			fog_colour.g = ambient_light.green * 128;
			fog_colour.b = ambient_light.blue * 128;
			fog_colour.a = 0;

			set_3d_fog_colour ( main_3d_env, fog_colour );

			break;
		}

		case DISPLAY_3D_TINT_GREY:
		{

			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_MANUAL_LIGHT );

			set_3d_infrared_mode ( main_3d_env, RENDER_INFRARED );

			//
			// Set the light in the scene
			//

			switch ( current_3d_light_level )
			{

				case DISPLAY_3D_LIGHT_LEVEL_LOW:
				{

					ambient_light.red = 0.48;
					ambient_light.green = 0.48;
					ambient_light.blue = 0.48;

					main_light.red = 0.12;
					main_light.green = 0.12;
					main_light.blue = 0.12;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_MEDIUM:
				{

					ambient_light.red = 0.64;
					ambient_light.green = 0.64;
					ambient_light.blue = 0.64;

					main_light.red = 0.16;
					main_light.green = 0.16;
					main_light.blue = 0.16;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_HIGH:
				{

					ambient_light.red = 0.8;
					ambient_light.green = 0.8;
					ambient_light.blue = 0.8;

					main_light.red = 0.2;
					main_light.green = 0.2;
					main_light.blue = 0.2;

					break;
				}
			}
/*			switch ( current_3d_light_level )
			{

				case DISPLAY_3D_LIGHT_LEVEL_LOW:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.48;
					ambient_light.blue = 0.0;

					main_light.red = 0.0;
					main_light.green = 0.12;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_MEDIUM:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.64;
					ambient_light.blue = 0.0;

					main_light.red = 0.0;
					main_light.green = 0.16;
					main_light.blue = 0.0;

					break;
				}

				case DISPLAY_3D_LIGHT_LEVEL_HIGH:
				{

					ambient_light.red = 0.0;
					ambient_light.green = 0.8;
					ambient_light.blue = 0.0;

					main_light.red = 0.0;
					main_light.green = 0.2;
					main_light.blue = 0.0;

					break;
				}
			}
*/
			set_3d_ambient_light_source ( main_3d_env, &ambient_light );

			direction.x = -visual_3d_vp->zv.x;
			direction.y = -visual_3d_vp->zv.y;
			direction.z = -visual_3d_vp->zv.z;

			set_3d_main_light_source ( main_3d_env, &main_light, &direction, FALSE );

			//
			// Set the fogmode
			//

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_MANUAL );

			fog_colour.r = ambient_light.red * 128;
			fog_colour.g = ambient_light.green * 128;
			fog_colour.b = ambient_light.blue * 128;

			fog_colour.a = 0;

			set_3d_fog_colour ( main_3d_env, fog_colour );

			break;
		}

		// Jabberwock 031009 Satellite tint for satellite view
		case DISPLAY_3D_TINT_BLUE_HAZE:
		{
			
			int
				interference;
				
			camera
				*raw;
				
			
			//
			// Set the light modes
			//

			set_3d_lightmode ( main_3d_env, LIGHTMODE_AUTOMATIC_LIGHT );

			set_3d_infrared_mode ( main_3d_env, INFRARED_OFF );
	
			//
			// Set the fogmode
			//

			set_3d_fogmode ( main_3d_env, FOGMODE_ON_MANUAL );

			raw = (camera *) get_local_entity_data (get_camera_entity ());
						
			interference = raw->fly_by_camera_timer;

			if (interference < 180)
			{
				fog_colour.r = 32;
				fog_colour.g = 64;
				fog_colour.b = 96;
			}
			else
			{
				fog_colour.r = 255;
				fog_colour.g = 255;
				fog_colour.b = 255;
			}
			
			
			//if (interference < 150)
			//{
				//fog_colour.a = frand1() * 40 + 150;
			//	fog_colour.a += 1;
			//}
			//else
			//{
				fog_colour.a = interference;
			//}

	
			set_3d_fog_colour ( main_3d_env, fog_colour );

			break;
		}
	}
// Jabberwock 031009 ends
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
