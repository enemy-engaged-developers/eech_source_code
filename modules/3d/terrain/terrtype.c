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

#include "userint.h"

#include "graphics.h"

#include "terrain.h"

#include "misc.h"

//VJ 050304 needed for texture colour mod
#include "cmndline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TERRAIN_DEFAULT_TEXTURE_SIZE 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_type_info
	terrain_type_information[TERRAIN_TYPE_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	terrain_dual_pass_rendering_enabled = TRUE;
		
//VJ 050818 dynamic water mod	
static int delay_count = 1;	
static int change_river_texture = 0;
static int change_sea_texture = 0;
static int change_reservoir_texture = 0;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_terrain_rendering_routines ( terrain_types type, terrain_polygon_type polygon_type,
																void ( *render_word_clipped ) ( int ),
																void ( *render_byte_clipped ) ( int ),
																void ( *render_word_unclipped ) ( int ),
																void ( *render_byte_unclipped ) ( int ) );

void set_terrain_type_textures ( terrain_types type, int texture, int texture2,
											float xz_texture_scale, float y_texture_scale,
											float xz_texture_scale2, float y_texture_scale2,
											int red, int green, int blue, surface_types surface_type );

void set_terrain_textures ( terrain_types type,  int texture, int texture2 );

static void initialise_3d_thailand_terrain_types ( void );

static void initialise_3d_yemen_terrain_types ( void );

static void initialise_3d_taiwan_terrain_types ( void );

static void initialise_3d_cuba_terrain_types ( void );

static void initialise_3d_lebanon_terrain_types ( void );

static void initialise_3d_georgia_terrain_types ( void );
//VJ 051007 for Maverick, add user maps in terrain display ==>
static void initialise_3d_alaska_terrain_types ( void );

static void initialise_3d_aleut_terrain_types ( void );

static void initialise_3d_kuwait_terrain_types ( void );
//VJ 051007 <==
static void initialise_3d_custom_terrain_types( void );

static void initialise_all_custom_terrain_types ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	terrain_texture_sea_detail,							terrain_texture_sea_colour_pass,
	terrain_texture_beach_detail,						terrain_texture_beach_colour_pass,
	terrain_texture_land_detail,						terrain_texture_land_colour_pass,
	terrain_texture_forest_detail,						terrain_texture_forest_colour_pass,
	terrain_texture_forest_top_detail,						terrain_texture_forest_top_colour_pass,
	terrain_texture_forest_middle_detail,						terrain_texture_forest_middle_colour_pass,
	terrain_texture_forest_bottom_detail,						terrain_texture_forest_bottom_colour_pass,
	terrain_texture_builtup_area1_detail,				terrain_texture_builtup_area1_colour_pass,
	terrain_texture_builtup_area2_detail,				terrain_texture_builtup_area2_colour_pass,
	terrain_texture_builtup_area3_detail,				terrain_texture_builtup_area3_colour_pass,
	terrain_texture_builtup_area4_detail,				terrain_texture_builtup_area4_colour_pass,
	terrain_texture_builtup_area1_infrared_detail,		terrain_texture_builtup_area1_infrared_colour_pass,
	terrain_texture_builtup_area2_infrared_detail,		terrain_texture_builtup_area2_infrared_colour_pass,
	terrain_texture_builtup_area3_infrared_detail,		terrain_texture_builtup_area3_infrared_colour_pass,
	terrain_texture_builtup_area4_infrared_detail,		terrain_texture_builtup_area4_infrared_colour_pass,
	terrain_texture_road_detail,						terrain_texture_road_colour_pass,
	terrain_texture_track_detail,						terrain_texture_track_colour_pass,
	terrain_texture_river_detail,						terrain_texture_river_colour_pass,
	terrain_texture_reservoir_detail,					terrain_texture_reservoir_colour_pass,
	terrain_texture_rail_detail,						terrain_texture_rail_colour_pass,
	terrain_texture_road_bank_detail,					terrain_texture_road_bank_colour_pass,
	terrain_texture_river_bank_detail,					terrain_texture_river_bank_colour_pass,
	terrain_texture_rail_bank_detail,					terrain_texture_rail_bank_colour_pass,
	terrain_texture_field1_detail,						terrain_texture_field1_colour_pass,
	terrain_texture_field2_detail,						terrain_texture_field2_colour_pass,
	terrain_texture_field3_detail,						terrain_texture_field3_colour_pass,
	terrain_texture_field4_detail,						terrain_texture_field4_colour_pass,
	terrain_texture_field5_detail,						terrain_texture_field5_colour_pass,
	terrain_texture_field6_detail,						terrain_texture_field6_colour_pass,
	terrain_texture_field7_detail,						terrain_texture_field7_colour_pass,
	terrain_texture_field8_detail,						terrain_texture_field8_colour_pass,
	terrain_texture_field9_detail,						terrain_texture_field9_colour_pass,
	terrain_texture_field10_detail,						terrain_texture_field10_colour_pass,
	terrain_texture_field11_detail,						terrain_texture_field11_colour_pass,
	terrain_texture_altered_land1_detail,				terrain_texture_altered_land1_colour_pass,
	terrain_texture_altered_land2_detail,				terrain_texture_altered_land2_colour_pass,
	terrain_texture_altered_land3_detail,				terrain_texture_altered_land3_colour_pass,
	terrain_texture_hedge_detail,						terrain_texture_hedge_colour_pass,
	terrain_texture_wall_detail,						terrain_texture_wall_colour_pass,
	terrain_texture_trench_detail,						terrain_texture_trench_colour_pass;

// Xhit: added following to set the surface_type for the terrain_type. (030328)
static int
	terrain_surface_sea,
	terrain_surface_beach,
	terrain_surface_land,
	terrain_surface_forest,
	terrain_surface_builtup_area1,
	terrain_surface_builtup_area2,
	terrain_surface_builtup_area3,
	terrain_surface_builtup_area4,
	terrain_surface_builtup_area1_infrared,
	terrain_surface_builtup_area2_infrared,
	terrain_surface_builtup_area3_infrared,
	terrain_surface_builtup_area4_infrared,
	terrain_surface_road,
	terrain_surface_track,
	terrain_surface_river,
	terrain_surface_reservoir,
	terrain_surface_rail,
	terrain_surface_road_bank,
	terrain_surface_river_bank,
	terrain_surface_rail_bank,
	terrain_surface_field1,
	terrain_surface_field2,
	terrain_surface_field3,
	terrain_surface_field4,
	terrain_surface_field5,
	terrain_surface_field6,
	terrain_surface_field7,
	terrain_surface_field8,
	terrain_surface_field9,
	terrain_surface_field10,
	terrain_surface_field11,
	terrain_surface_altered_land1,
	terrain_surface_altered_land2,
	terrain_surface_altered_land3,
	terrain_surface_hedge,
	terrain_surface_wall,
	terrain_surface_trench;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void set_3d_terrain_dual_pass_rendering ( int enabled )
{

	if ( enabled != terrain_dual_pass_rendering_enabled )
	{

		terrain_dual_pass_rendering_enabled = enabled;

		//
		// Reinitialise the terrain rendering routines
		//

		initialise_3d_terrain_rendering_routines ( terrain_dual_pass_rendering_enabled );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_terrain_dual_pass_rendering ( void )
{

	return ( terrain_dual_pass_rendering_enabled );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_rendering_routines ( int dual_pass )
{

	terrain_types
		count;


	void ( *draw_unclipped_fan_word_face ) ( int );
	void ( *draw_unclipped_fan_byte_face ) ( int );
	void ( *draw_unclipped_strip_word_face ) ( int );
	void ( *draw_unclipped_strip_byte_face ) ( int );
	void ( *draw_texture_x_unclipped_fan_word_face ) ( int );
	void ( *draw_texture_x_unclipped_fan_byte_face ) ( int );
	void ( *draw_texture_z_unclipped_fan_word_face ) ( int );
	void ( *draw_texture_z_unclipped_fan_byte_face ) ( int );
	void ( *draw_texture_x_unclipped_strip_word_face ) ( int );
	void ( *draw_texture_x_unclipped_strip_byte_face ) ( int );
	void ( *draw_texture_z_unclipped_strip_word_face ) ( int );
	void ( *draw_texture_z_unclipped_strip_byte_face ) ( int );

	void ( *draw_colour_unclipped_fan_word_face ) ( int );
	void ( *draw_colour_unclipped_fan_byte_face ) ( int );
	void ( *draw_colour_unclipped_strip_word_face ) ( int );
	void ( *draw_colour_unclipped_strip_byte_face ) ( int );
	void ( *draw_texture_x_colour_unclipped_fan_word_face ) ( int );
	void ( *draw_texture_x_colour_unclipped_fan_byte_face ) ( int );
	void ( *draw_texture_z_colour_unclipped_fan_word_face ) ( int );
	void ( *draw_texture_z_colour_unclipped_fan_byte_face ) ( int );
	void ( *draw_texture_x_colour_unclipped_strip_word_face ) ( int );
	void ( *draw_texture_x_colour_unclipped_strip_byte_face ) ( int );
	void ( *draw_texture_z_colour_unclipped_strip_word_face ) ( int );
	void ( *draw_texture_z_colour_unclipped_strip_byte_face ) ( int );

	void ( *draw_clipped_fan_word_face ) ( int );
	void ( *draw_clipped_fan_byte_face ) ( int );
	void ( *draw_clipped_strip_word_face ) ( int );
	void ( *draw_clipped_strip_byte_face ) ( int );
	void ( *draw_texture_x_clipped_fan_word_face ) ( int );
	void ( *draw_texture_x_clipped_fan_byte_face ) ( int );
	void ( *draw_texture_z_clipped_fan_word_face ) ( int );
	void ( *draw_texture_z_clipped_fan_byte_face ) ( int );
	void ( *draw_texture_x_clipped_strip_word_face ) ( int );
	void ( *draw_texture_x_clipped_strip_byte_face ) ( int );
	void ( *draw_texture_z_clipped_strip_word_face ) ( int );
	void ( *draw_texture_z_clipped_strip_byte_face ) ( int );

	void ( *draw_colour_clipped_fan_word_face ) ( int );
	void ( *draw_colour_clipped_fan_byte_face ) ( int );
	void ( *draw_colour_clipped_strip_word_face ) ( int );
	void ( *draw_colour_clipped_strip_byte_face ) ( int );
	void ( *draw_texture_x_colour_clipped_fan_word_face ) ( int );
	void ( *draw_texture_x_colour_clipped_fan_byte_face ) ( int );
	void ( *draw_texture_z_colour_clipped_fan_word_face ) ( int );
	void ( *draw_texture_z_colour_clipped_fan_byte_face ) ( int );
	void ( *draw_texture_x_colour_clipped_strip_word_face ) ( int );
	void ( *draw_texture_x_colour_clipped_strip_byte_face ) ( int );
	void ( *draw_texture_z_colour_clipped_strip_word_face ) ( int );
	void ( *draw_texture_z_colour_clipped_strip_byte_face ) ( int );


	for ( count = ( TERRAIN_TYPE_INVALID + 1 ); count < TERRAIN_TYPE_LAST; count++ )
	{

		terrain_type_information[count].initialised = FALSE;
		terrain_type_information[count].render_word_clipped = NULL;
		terrain_type_information[count].render_byte_clipped = NULL;
		terrain_type_information[count].render_word_unclipped = NULL;
		terrain_type_information[count].render_byte_unclipped = NULL;
	}

	//
	// Switch on the two pass rendering routines ( override on the modulate alpha )
	//

	//NOTE: dual_pass is TRUE normally !!!!
	if ( ( dual_pass ) && ( d3d_modulate_alpha ) )
	{

		draw_unclipped_fan_word_face = draw_3d_terrain_twopass_unclipped_fan_word_face;
		draw_unclipped_fan_byte_face = draw_3d_terrain_twopass_unclipped_fan_byte_face;
		draw_unclipped_strip_word_face = draw_3d_terrain_twopass_unclipped_strip_word_face;
		draw_unclipped_strip_byte_face = draw_3d_terrain_twopass_unclipped_strip_byte_face;
		draw_texture_x_unclipped_fan_word_face = draw_3d_terrain_twopass_texture_x_unclipped_fan_word_face;
		draw_texture_x_unclipped_fan_byte_face = draw_3d_terrain_twopass_texture_x_unclipped_fan_byte_face;
		draw_texture_z_unclipped_fan_word_face = draw_3d_terrain_twopass_texture_z_unclipped_fan_word_face;
		draw_texture_z_unclipped_fan_byte_face = draw_3d_terrain_twopass_texture_z_unclipped_fan_byte_face;
		draw_texture_x_unclipped_strip_word_face = draw_3d_terrain_twopass_texture_x_unclipped_strip_word_face;
		draw_texture_x_unclipped_strip_byte_face = draw_3d_terrain_twopass_texture_x_unclipped_strip_byte_face;
		draw_texture_z_unclipped_strip_word_face = draw_3d_terrain_twopass_texture_z_unclipped_strip_word_face;
		draw_texture_z_unclipped_strip_byte_face = draw_3d_terrain_twopass_texture_z_unclipped_strip_byte_face;

		draw_colour_unclipped_strip_word_face = draw_3d_terrain_twopass_colour_unclipped_strip_word_face;
		draw_colour_unclipped_strip_byte_face = draw_3d_terrain_twopass_colour_unclipped_strip_byte_face;
		draw_colour_unclipped_fan_word_face = draw_3d_terrain_twopass_colour_unclipped_fan_word_face;
		draw_colour_unclipped_fan_byte_face = draw_3d_terrain_twopass_colour_unclipped_fan_byte_face;
		draw_texture_x_colour_unclipped_strip_word_face = draw_3d_terrain_twopass_texture_x_colour_unclipped_strip_word_face;
		draw_texture_x_colour_unclipped_strip_byte_face = draw_3d_terrain_twopass_texture_x_colour_unclipped_strip_byte_face;
		draw_texture_z_colour_unclipped_strip_word_face = draw_3d_terrain_twopass_texture_z_colour_unclipped_strip_word_face;
		draw_texture_z_colour_unclipped_strip_byte_face = draw_3d_terrain_twopass_texture_z_colour_unclipped_strip_byte_face;
		draw_texture_x_colour_unclipped_fan_word_face = draw_3d_terrain_twopass_texture_x_colour_unclipped_fan_word_face;
		draw_texture_x_colour_unclipped_fan_byte_face = draw_3d_terrain_twopass_texture_x_colour_unclipped_fan_byte_face;
		draw_texture_z_colour_unclipped_fan_word_face = draw_3d_terrain_twopass_texture_z_colour_unclipped_fan_word_face;
		draw_texture_z_colour_unclipped_fan_byte_face = draw_3d_terrain_twopass_texture_z_colour_unclipped_fan_byte_face;

		draw_clipped_fan_word_face = draw_3d_terrain_twopass_clipped_fan_word_face;
		draw_clipped_fan_byte_face = draw_3d_terrain_twopass_clipped_fan_byte_face;
		draw_clipped_strip_word_face = draw_3d_terrain_twopass_clipped_strip_word_face;
		draw_clipped_strip_byte_face = draw_3d_terrain_twopass_clipped_strip_byte_face;
		draw_texture_x_clipped_fan_word_face = draw_3d_terrain_twopass_texture_x_clipped_fan_word_face;
		draw_texture_x_clipped_fan_byte_face = draw_3d_terrain_twopass_texture_x_clipped_fan_byte_face;
		draw_texture_z_clipped_fan_word_face = draw_3d_terrain_twopass_texture_z_clipped_fan_word_face;
		draw_texture_z_clipped_fan_byte_face = draw_3d_terrain_twopass_texture_z_clipped_fan_byte_face;
		draw_texture_x_clipped_strip_word_face = draw_3d_terrain_twopass_texture_x_clipped_strip_word_face;
		draw_texture_x_clipped_strip_byte_face = draw_3d_terrain_twopass_texture_x_clipped_strip_byte_face;
		draw_texture_z_clipped_strip_word_face = draw_3d_terrain_twopass_texture_z_clipped_strip_word_face;
		draw_texture_z_clipped_strip_byte_face = draw_3d_terrain_twopass_texture_z_clipped_strip_byte_face;

		draw_colour_clipped_strip_word_face = draw_3d_terrain_twopass_colour_clipped_strip_word_face;
		draw_colour_clipped_strip_byte_face = draw_3d_terrain_twopass_colour_clipped_strip_byte_face;
		draw_colour_clipped_fan_word_face = draw_3d_terrain_twopass_colour_clipped_fan_word_face;
		draw_colour_clipped_fan_byte_face = draw_3d_terrain_twopass_colour_clipped_fan_byte_face;
		draw_texture_x_colour_clipped_fan_word_face = draw_3d_terrain_twopass_texture_x_colour_clipped_fan_word_face;
		draw_texture_x_colour_clipped_fan_byte_face = draw_3d_terrain_twopass_texture_x_colour_clipped_fan_byte_face;
		draw_texture_z_colour_clipped_fan_word_face = draw_3d_terrain_twopass_texture_z_colour_clipped_fan_word_face;
		draw_texture_z_colour_clipped_fan_byte_face = draw_3d_terrain_twopass_texture_z_colour_clipped_fan_byte_face;
		draw_texture_x_colour_clipped_strip_word_face = draw_3d_terrain_twopass_texture_x_colour_clipped_strip_word_face;
		draw_texture_x_colour_clipped_strip_byte_face = draw_3d_terrain_twopass_texture_x_colour_clipped_strip_byte_face;
		draw_texture_z_colour_clipped_strip_word_face = draw_3d_terrain_twopass_texture_z_colour_clipped_strip_word_face;
		draw_texture_z_colour_clipped_strip_byte_face = draw_3d_terrain_twopass_texture_z_colour_clipped_strip_byte_face;
	}
	else
	{
		//'normal UNCLIPPED polys and strips'
		draw_unclipped_fan_word_face = draw_3d_terrain_unclipped_fan_word_face;
		draw_unclipped_fan_byte_face = draw_3d_terrain_unclipped_fan_byte_face;
		draw_unclipped_strip_word_face = draw_3d_terrain_unclipped_strip_word_face;
		draw_unclipped_strip_byte_face = draw_3d_terrain_unclipped_strip_byte_face;
		//'not used' ?
		draw_texture_x_unclipped_fan_word_face = draw_3d_terrain_texture_x_unclipped_fan_word_face;
		draw_texture_x_unclipped_fan_byte_face = draw_3d_terrain_texture_x_unclipped_fan_byte_face;
		draw_texture_z_unclipped_fan_word_face = draw_3d_terrain_texture_z_unclipped_fan_word_face;
		draw_texture_z_unclipped_fan_byte_face = draw_3d_terrain_texture_z_unclipped_fan_byte_face;
		draw_texture_x_unclipped_strip_word_face = draw_3d_terrain_texture_x_unclipped_strip_word_face;
		draw_texture_x_unclipped_strip_byte_face = draw_3d_terrain_texture_x_unclipped_strip_byte_face;
		draw_texture_z_unclipped_strip_word_face = draw_3d_terrain_texture_z_unclipped_strip_word_face;
		draw_texture_z_unclipped_strip_byte_face = draw_3d_terrain_texture_z_unclipped_strip_byte_face;

		//'normal COLOUR UNCLIPPED polys and strips'
		draw_colour_unclipped_strip_word_face = draw_3d_terrain_colour_unclipped_strip_word_face;
		draw_colour_unclipped_strip_byte_face = draw_3d_terrain_colour_unclipped_strip_byte_face;
		draw_colour_unclipped_fan_word_face = draw_3d_terrain_colour_unclipped_fan_word_face;
		draw_colour_unclipped_fan_byte_face = draw_3d_terrain_colour_unclipped_fan_byte_face;

		//'not used'?
		draw_texture_x_colour_unclipped_fan_word_face = draw_3d_terrain_texture_x_colour_unclipped_fan_word_face;
		draw_texture_x_colour_unclipped_fan_byte_face = draw_3d_terrain_texture_x_colour_unclipped_fan_byte_face;
		draw_texture_z_colour_unclipped_fan_word_face = draw_3d_terrain_texture_z_colour_unclipped_fan_word_face;
		draw_texture_z_colour_unclipped_fan_byte_face = draw_3d_terrain_texture_z_colour_unclipped_fan_byte_face;
		draw_texture_x_colour_unclipped_strip_word_face = draw_3d_terrain_texture_x_colour_unclipped_strip_word_face;
		draw_texture_x_colour_unclipped_strip_byte_face = draw_3d_terrain_texture_x_colour_unclipped_strip_byte_face;
		draw_texture_z_colour_unclipped_strip_word_face = draw_3d_terrain_texture_z_colour_unclipped_strip_word_face;
		draw_texture_z_colour_unclipped_strip_byte_face = draw_3d_terrain_texture_z_colour_unclipped_strip_byte_face;

		//'normal CLIPPED polys and strips'
		draw_clipped_fan_word_face = draw_3d_terrain_clipped_fan_word_face;
		draw_clipped_fan_byte_face = draw_3d_terrain_clipped_fan_byte_face;
		draw_clipped_strip_word_face = draw_3d_terrain_clipped_strip_word_face;
		draw_clipped_strip_byte_face = draw_3d_terrain_clipped_strip_byte_face;

		draw_texture_x_clipped_fan_word_face = draw_3d_terrain_texture_x_clipped_fan_word_face;
		draw_texture_x_clipped_fan_byte_face = draw_3d_terrain_texture_x_clipped_fan_byte_face;
		draw_texture_z_clipped_fan_word_face = draw_3d_terrain_texture_z_clipped_fan_word_face;
		draw_texture_z_clipped_fan_byte_face = draw_3d_terrain_texture_z_clipped_fan_byte_face;
		draw_texture_x_clipped_strip_word_face = draw_3d_terrain_texture_x_clipped_strip_word_face;
		draw_texture_x_clipped_strip_byte_face = draw_3d_terrain_texture_x_clipped_strip_byte_face;
		draw_texture_z_clipped_strip_word_face = draw_3d_terrain_texture_z_clipped_strip_word_face;
		draw_texture_z_clipped_strip_byte_face = draw_3d_terrain_texture_z_clipped_strip_byte_face;

		//'normal COLOUR CLIPPED polys and strips'
		draw_colour_clipped_strip_word_face = draw_3d_terrain_colour_clipped_strip_word_face;
		draw_colour_clipped_strip_byte_face = draw_3d_terrain_colour_clipped_strip_byte_face;
		draw_colour_clipped_fan_word_face = draw_3d_terrain_colour_clipped_fan_word_face;
		draw_colour_clipped_fan_byte_face = draw_3d_terrain_colour_clipped_fan_byte_face;

		draw_texture_x_colour_clipped_fan_word_face = draw_3d_terrain_texture_x_colour_clipped_fan_word_face;
		draw_texture_x_colour_clipped_fan_byte_face = draw_3d_terrain_texture_x_colour_clipped_fan_byte_face;
		draw_texture_z_colour_clipped_fan_word_face = draw_3d_terrain_texture_z_colour_clipped_fan_word_face;
		draw_texture_z_colour_clipped_fan_byte_face = draw_3d_terrain_texture_z_colour_clipped_fan_byte_face;
		draw_texture_x_colour_clipped_strip_word_face = draw_3d_terrain_texture_x_colour_clipped_strip_word_face;
		draw_texture_x_colour_clipped_strip_byte_face = draw_3d_terrain_texture_x_colour_clipped_strip_byte_face;
		draw_texture_z_colour_clipped_strip_word_face = draw_3d_terrain_texture_z_colour_clipped_strip_word_face;
		draw_texture_z_colour_clipped_strip_byte_face = draw_3d_terrain_texture_z_colour_clipped_strip_byte_face;
	}

	set_terrain_rendering_routines ( TERRAIN_TYPE_SEA, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_BEACH, POLYGON_TYPE_STRIP,
												draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
												draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_LAND, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_FLOOR, POLYGON_TYPE_FAN,
												draw_3d_terrain_clipped_fan_word_face, draw_3d_terrain_clipped_fan_byte_face,
												draw_3d_terrain_unclipped_fan_word_face, draw_3d_terrain_unclipped_fan_byte_face );
												
	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_x_clipped_strip_word_face, draw_3d_terrain_texture_x_clipped_strip_byte_face,
												draw_3d_terrain_texture_x_unclipped_strip_word_face, draw_3d_terrain_texture_x_unclipped_strip_byte_face );
	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_MID_X, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_x_clipped_strip_word_face, draw_3d_terrain_texture_x_clipped_strip_byte_face,
												draw_3d_terrain_texture_x_unclipped_strip_word_face, draw_3d_terrain_texture_x_unclipped_strip_byte_face );
	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_TOP_X, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_x_clipped_strip_word_face, draw_3d_terrain_texture_x_clipped_strip_byte_face,
												draw_3d_terrain_texture_x_unclipped_strip_word_face, draw_3d_terrain_texture_x_unclipped_strip_byte_face );
	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_z_clipped_strip_word_face, draw_3d_terrain_texture_z_clipped_strip_byte_face,
												draw_3d_terrain_texture_z_unclipped_strip_word_face, draw_3d_terrain_texture_z_unclipped_strip_byte_face );
	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_MID_Z, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_z_clipped_strip_word_face, draw_3d_terrain_texture_z_clipped_strip_byte_face,
												draw_3d_terrain_texture_z_unclipped_strip_word_face, draw_3d_terrain_texture_z_unclipped_strip_byte_face );
	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_TOP_Z, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_z_clipped_strip_word_face, draw_3d_terrain_texture_z_clipped_strip_byte_face,
												draw_3d_terrain_texture_z_unclipped_strip_word_face, draw_3d_terrain_texture_z_unclipped_strip_byte_face );
//VJ goes to C:\gms\Razorworks\eech-new\modules\graphics\polyd3d.c
	set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_TOP, POLYGON_TYPE_FAN,
												draw_3d_terrain_clipped_fan_word_face, draw_3d_terrain_clipped_fan_byte_face,
												draw_3d_terrain_unclipped_fan_word_face, draw_3d_terrain_unclipped_fan_byte_face );

	//cities

   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA1, POLYGON_TYPE_FAN,
												draw_colour_clipped_fan_word_face, draw_colour_clipped_fan_byte_face,
												draw_colour_unclipped_fan_word_face, draw_colour_unclipped_fan_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA2, POLYGON_TYPE_FAN,
												draw_colour_clipped_fan_word_face, draw_colour_clipped_fan_byte_face,
												draw_colour_unclipped_fan_word_face, draw_colour_unclipped_fan_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA3, POLYGON_TYPE_FAN,
												draw_colour_clipped_fan_word_face, draw_colour_clipped_fan_byte_face,
												draw_colour_unclipped_fan_word_face, draw_colour_unclipped_fan_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA4, POLYGON_TYPE_FAN,
												draw_colour_clipped_fan_word_face, draw_colour_clipped_fan_byte_face,
												draw_colour_unclipped_fan_word_face, draw_colour_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_ROAD, POLYGON_TYPE_STRIP,
												draw_colour_clipped_strip_word_face, draw_colour_clipped_strip_byte_face,
												draw_colour_unclipped_strip_word_face, draw_colour_unclipped_strip_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_TRACK, POLYGON_TYPE_STRIP,
												draw_colour_clipped_strip_word_face, draw_colour_clipped_strip_byte_face,
												draw_colour_unclipped_strip_word_face, draw_colour_unclipped_strip_byte_face );

	set_terrain_rendering_routines ( TERRAIN_TYPE_RIVER, POLYGON_TYPE_STRIP,
												draw_3d_terrain_clipped_strip_word_face, draw_3d_terrain_clipped_strip_byte_face,
												draw_3d_terrain_unclipped_strip_word_face, draw_3d_terrain_unclipped_strip_byte_face );

	set_terrain_rendering_routines ( TERRAIN_TYPE_RESERVOIR, POLYGON_TYPE_FAN,
												draw_3d_terrain_clipped_fan_word_face, draw_3d_terrain_clipped_fan_byte_face,
												draw_3d_terrain_unclipped_fan_word_face, draw_3d_terrain_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_RAIL, POLYGON_TYPE_STRIP,
												draw_3d_terrain_clipped_strip_word_face, draw_3d_terrain_clipped_strip_byte_face,
												draw_3d_terrain_unclipped_strip_word_face, draw_3d_terrain_unclipped_strip_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_ROAD_BANK, POLYGON_TYPE_STRIP,
												draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
												draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_RIVER_BANK, POLYGON_TYPE_STRIP,
												draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
												draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_RAIL_BANK, POLYGON_TYPE_STRIP,
												draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
												draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face );

	//
	// Field types
	//

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD1, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD2, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD3, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD4, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD5, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD6, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD7, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD8, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD9, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD10, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_FIELD11, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

	//
	// Varied Land Types (e.g. snow, rock etc.)
	//

   set_terrain_rendering_routines ( TERRAIN_TYPE_ALTERED_LAND1, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_ALTERED_LAND2, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_ALTERED_LAND3, POLYGON_TYPE_FAN,
												draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
												draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

	//
	// Hedges / Walls
	//

   set_terrain_rendering_routines ( TERRAIN_TYPE_HEDGE_TOP, POLYGON_TYPE_STRIP,
												draw_3d_terrain_clipped_strip_word_face, draw_3d_terrain_clipped_strip_byte_face,
												draw_3d_terrain_unclipped_strip_word_face, draw_3d_terrain_unclipped_strip_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_HEDGE_SIDE_X, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_x_clipped_strip_word_face, draw_3d_terrain_texture_x_clipped_strip_byte_face,
												draw_3d_terrain_texture_x_unclipped_strip_word_face, draw_3d_terrain_texture_x_unclipped_strip_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_HEDGE_SIDE_Z, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_z_clipped_strip_word_face, draw_3d_terrain_texture_z_clipped_strip_byte_face,
												draw_3d_terrain_texture_z_unclipped_strip_word_face, draw_3d_terrain_texture_z_unclipped_strip_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_WALL_TOP, POLYGON_TYPE_STRIP,
												draw_3d_terrain_colour_clipped_strip_word_face, draw_3d_terrain_colour_clipped_strip_byte_face,
												draw_3d_terrain_colour_unclipped_strip_word_face, draw_3d_terrain_colour_unclipped_strip_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_WALL_SIDE_X, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_x_colour_clipped_strip_word_face, draw_3d_terrain_texture_x_colour_clipped_strip_byte_face,
												draw_3d_terrain_texture_x_colour_unclipped_strip_word_face, draw_3d_terrain_texture_x_colour_unclipped_strip_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_WALL_SIDE_Z, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_z_colour_clipped_strip_word_face, draw_3d_terrain_texture_z_colour_clipped_strip_byte_face,
												draw_3d_terrain_texture_z_colour_unclipped_strip_word_face, draw_3d_terrain_texture_z_colour_unclipped_strip_byte_face );

   set_terrain_rendering_routines ( TERRAIN_TYPE_TRENCH, POLYGON_TYPE_STRIP,
												draw_3d_terrain_clipped_strip_word_face, draw_3d_terrain_clipped_strip_byte_face,
												draw_3d_terrain_unclipped_strip_word_face, draw_3d_terrain_unclipped_strip_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_TRENCH_SIDE_X, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_x_clipped_strip_word_face, draw_3d_terrain_texture_x_clipped_strip_byte_face,
												draw_3d_terrain_texture_x_unclipped_strip_word_face, draw_3d_terrain_texture_x_unclipped_strip_byte_face );
   set_terrain_rendering_routines ( TERRAIN_TYPE_TRENCH_SIDE_Z, POLYGON_TYPE_STRIP,
												draw_3d_terrain_texture_z_clipped_strip_word_face, draw_3d_terrain_texture_z_clipped_strip_byte_face,
												draw_3d_terrain_texture_z_unclipped_strip_word_face, draw_3d_terrain_texture_z_unclipped_strip_byte_face );
	//
	// All the types that are used in the terrain generation tool
	//

   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_BEACH_MID,			POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_FRINGE,				POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_POWER_LINE,			POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_TELEPHONE_LINE,	POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_SEA_BANK,			POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_COASTAL_RIVER,		POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );

   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK3,		POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK5,		POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK7,		POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_LAKE,							POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_FOREST_SIDE_X,				POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_FOREST_SIDE_Z,				POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_OFFROAD,						POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_POLITICAL_BOUNDARY,		POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );
   set_terrain_rendering_routines ( TEMP_TERRAIN_TYPE_BUILT_UP_AREA_BANK,		POLYGON_TYPE_UNKNOWN, NULL, NULL, NULL, NULL );


	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze	
	if (command_line_texture_colour == 1)
	{
			
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_FLOOR, POLYGON_TYPE_FAN,
													draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
													draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );											
//VJ 050619 changed these to display without greyish haze in the distance
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X, POLYGON_TYPE_STRIP,
													draw_texture_x_clipped_strip_word_face, draw_texture_x_clipped_strip_byte_face,
													draw_texture_x_unclipped_strip_word_face, draw_texture_x_unclipped_strip_byte_face );
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_MID_X, POLYGON_TYPE_STRIP,
													draw_texture_x_clipped_strip_word_face, draw_texture_x_clipped_strip_byte_face,
													draw_texture_x_unclipped_strip_word_face, draw_texture_x_unclipped_strip_byte_face );
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_TOP_X, POLYGON_TYPE_STRIP,
													draw_texture_x_clipped_strip_word_face, draw_texture_x_clipped_strip_byte_face,
													draw_texture_x_unclipped_strip_word_face, draw_texture_x_unclipped_strip_byte_face );
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z, POLYGON_TYPE_STRIP,
													draw_texture_z_clipped_strip_word_face, draw_texture_z_clipped_strip_byte_face,
													draw_texture_z_unclipped_strip_word_face, draw_texture_z_unclipped_strip_byte_face );
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_MID_Z, POLYGON_TYPE_STRIP,
													draw_texture_z_clipped_strip_word_face, draw_texture_z_clipped_strip_byte_face,
													draw_texture_z_unclipped_strip_word_face, draw_texture_z_unclipped_strip_byte_face );
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_SIDE_TOP_Z, POLYGON_TYPE_STRIP,
													draw_texture_z_clipped_strip_word_face, draw_texture_z_clipped_strip_byte_face,
													draw_texture_z_unclipped_strip_word_face, draw_texture_z_unclipped_strip_byte_face );
		
//the difference between colour_clipped_fan and clipped fan is a recolouring before rendering 
//where the colours (255,255,255) are applied. This ignores than light and time of day so no good!	
//it also affects NPVS view: lighting ignored so CITIES showing up as bright!
		set_terrain_rendering_routines ( TERRAIN_TYPE_FOREST_TOP, POLYGON_TYPE_FAN,
													draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
													draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );
//												draw_colour_clipped_fan_word_face, draw_colour_clipped_fan_byte_face,
//												draw_colour_unclipped_fan_word_face, draw_colour_unclipped_fan_byte_face );
//very little difference between these		

	   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA1, POLYGON_TYPE_FAN,
													draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
													draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );
	   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA2, POLYGON_TYPE_FAN,
													draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
													draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );
	   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA3, POLYGON_TYPE_FAN,
													draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
													draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );
	   set_terrain_rendering_routines ( TERRAIN_TYPE_BUILT_UP_AREA4, POLYGON_TYPE_FAN,
													draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
													draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

   	set_terrain_rendering_routines ( TERRAIN_TYPE_TRENCH, POLYGON_TYPE_STRIP,
													draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
													draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face);

	   set_terrain_rendering_routines ( TERRAIN_TYPE_WALL_TOP, POLYGON_TYPE_STRIP,
													draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
													draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face);
		
		set_terrain_rendering_routines ( TERRAIN_TYPE_RIVER, POLYGON_TYPE_STRIP,
													draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
													draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face);

		set_terrain_rendering_routines ( TERRAIN_TYPE_RESERVOIR, POLYGON_TYPE_FAN,
													draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
													draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

	   set_terrain_rendering_routines ( TERRAIN_TYPE_HEDGE_TOP, POLYGON_TYPE_STRIP,
													draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
													draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face);
	//VJ 050619 changed these to display without greyish haze in the distance
	   set_terrain_rendering_routines ( TERRAIN_TYPE_HEDGE_SIDE_X, POLYGON_TYPE_STRIP,
													draw_texture_x_clipped_strip_word_face, draw_texture_x_clipped_strip_byte_face,
													draw_texture_x_unclipped_strip_word_face, draw_texture_x_unclipped_strip_byte_face );
	   set_terrain_rendering_routines ( TERRAIN_TYPE_HEDGE_SIDE_Z, POLYGON_TYPE_STRIP,
													draw_texture_z_clipped_strip_word_face, draw_texture_z_clipped_strip_byte_face,
													draw_texture_z_unclipped_strip_word_face, draw_texture_z_unclipped_strip_byte_face );

	}

	//
	// All the types that have been axed, due to visual impairments ( don't look nice! ) or speed considerations
	//

	for ( count = ( TERRAIN_TYPE_INVALID + 1 ); count < TERRAIN_TYPE_LAST; count++ )
	{

		if ( !terrain_type_information[count].initialised )
		{

			debug_log ( "terrain type %s not initialised", get_terrain_type_name ( count ) );
		}
	}

	//VJ 050321 texture colour mod
	if (command_line_texture_colour == 0)
	switch ( current_terrain_version.map_number )
	{

		case 1:	// THAILAND
		case 2:	// CUBA
		case 4:	// TAIWAN
		{

			set_terrain_rendering_routines ( TERRAIN_TYPE_ALTERED_LAND3, POLYGON_TYPE_FAN,
														draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
														draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

			break;
		}

		default:	// GEORGIA
		{

			set_terrain_rendering_routines ( TERRAIN_TYPE_ALTERED_LAND3, POLYGON_TYPE_FAN,
														draw_colour_clipped_fan_word_face, draw_colour_clipped_fan_byte_face,
														draw_colour_unclipped_fan_word_face, draw_colour_unclipped_fan_byte_face );

			break;
		}

		case 6: // YEMEN
		{

			set_terrain_rendering_routines ( TERRAIN_TYPE_ALTERED_LAND3, POLYGON_TYPE_FAN,
														draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
														draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

			set_terrain_rendering_routines ( TERRAIN_TYPE_RIVER, POLYGON_TYPE_STRIP,
														draw_clipped_strip_word_face, draw_clipped_strip_byte_face,
														draw_unclipped_strip_word_face, draw_unclipped_strip_byte_face );

			set_terrain_rendering_routines ( TERRAIN_TYPE_RESERVOIR, POLYGON_TYPE_FAN,
														draw_clipped_fan_word_face, draw_clipped_fan_byte_face,
														draw_unclipped_fan_word_face, draw_unclipped_fan_byte_face );

			break;
		}
	}

	initialise_3d_terrain_map_specific_texture_indices ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_map_specific_texture_indices ( void )
{

	switch ( current_terrain_version.map_number )
	{

		case 1:	// THAILAND
		{

			initialise_3d_thailand_terrain_types ();

			break;
		}

		case 4:	// TAIWAN
		{

			initialise_3d_taiwan_terrain_types ();

			break;
		}

		case 2:	// CUBA
		{

			initialise_3d_cuba_terrain_types ();

			break;
		}

		case 3: // GEORGIA
		default:
		{

			initialise_3d_georgia_terrain_types ();

			break;
		}

		case 5:	// LEBANON
		{

			initialise_3d_lebanon_terrain_types ();

			break;
		}

		case 6:	// YEMEN
		{

			initialise_3d_yemen_terrain_types ();

			break;
		}
		//VJ 051007 for Maverick, add user maps in terrain display =>
		case 7:	
		{

			initialise_3d_alaska_terrain_types ();

			break;
		}


		case 8:	
		{

			initialise_3d_aleut_terrain_types ();

			break;
		}

		case 9:	
		{

			initialise_3d_kuwait_terrain_types ();

			break;
		}
		//VJ 051007 <==
	}

	initialise_3d_terrain_types ();

//VJ 050314	texture colour mod
	if (command_line_texture_colour == 1){
		initialise_3d_custom_terrain_types();
		
	}	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050322 texture colour mod, function to read texture scales form file and apply
//VJ 051001 rearranged the order 
void initialise_3d_custom_terrain_types( void )
{
	int count = 0;
	float sl, sld, sldd;
	
	for (count = 0; count < 64; count++)
	if (texture_override_scales[count][0] > 0)
	{
		int index = texture_override_scales[count][0];
		sl = texture_override_scales[count][1];
		sld = sl;
		sldd = sl;	

		//VJ 051001 sld equals sl but may not in future alpha blended display
		if (index == terrain_texture_beach_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BEACH, terrain_texture_beach_detail, terrain_texture_beach_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_beach );
		if (index == terrain_texture_land_detail   ) set_terrain_type_textures ( TERRAIN_TYPE_LAND, terrain_texture_land_detail, terrain_texture_land_colour_pass, sld, sld, sl, sl,  255, 255, 255, terrain_surface_land);
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_TOP, terrain_texture_forest_detail, terrain_texture_forest_colour_pass, sld, sld, sl, sl, 255, 255, 255,terrain_surface_forest );
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_FLOOR, terrain_texture_altered_land1_detail, terrain_texture_altered_land2_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_forest);
   	
   	if (index == terrain_texture_field1_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD1, terrain_texture_field1_detail, terrain_texture_field1_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field1 );
   	if (index == terrain_texture_field2_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD2, terrain_texture_field2_detail, terrain_texture_field2_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field2 );
   	if (index == terrain_texture_field3_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD3, terrain_texture_field3_detail, terrain_texture_field3_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field3 );
   	if (index == terrain_texture_field4_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD4, terrain_texture_field4_detail, terrain_texture_field4_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field4 );
   	if (index == terrain_texture_field5_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD5, terrain_texture_field5_detail, terrain_texture_field5_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field5 );
   	if (index == terrain_texture_field6_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD6, terrain_texture_field6_detail, terrain_texture_field6_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field6 );
   	if (index == terrain_texture_field7_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD7, terrain_texture_field7_detail, terrain_texture_field7_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field7 );
   	if (index == terrain_texture_field8_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD8, terrain_texture_field8_detail, terrain_texture_field8_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field8 );
   	if (index == terrain_texture_field9_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD9, terrain_texture_field9_detail, terrain_texture_field9_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field9 );
   	if (index == terrain_texture_field10_detail    ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD10, terrain_texture_field10_detail, terrain_texture_field10_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field10 );
   	if (index == terrain_texture_field11_detail    ) set_terrain_type_textures ( TERRAIN_TYPE_FIELD11, terrain_texture_field11_detail, terrain_texture_field11_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_field11 );
   	   	
		if (index == terrain_texture_sea_detail    ) set_terrain_type_textures ( TERRAIN_TYPE_SEA, terrain_texture_sea_detail, terrain_texture_sea_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_sea );		
		if (index == terrain_texture_river_detail    ) set_terrain_type_textures ( TERRAIN_TYPE_RIVER, terrain_texture_river_detail, terrain_texture_river_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_river );		
   	if (index == terrain_texture_reservoir_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_RESERVOIR, terrain_texture_reservoir_detail, terrain_texture_reservoir_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_reservoir );

   	if (index == terrain_texture_altered_land1_detail ) set_terrain_type_textures ( TERRAIN_TYPE_ALTERED_LAND1, terrain_texture_altered_land1_detail, terrain_texture_altered_land1_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_altered_land1 );
   	if (index == terrain_texture_altered_land2_detail ) set_terrain_type_textures ( TERRAIN_TYPE_ALTERED_LAND2, terrain_texture_altered_land2_detail, terrain_texture_altered_land2_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_altered_land2 );
   	if (index == terrain_texture_altered_land3_detail ) set_terrain_type_textures ( TERRAIN_TYPE_ALTERED_LAND3, terrain_texture_altered_land3_detail, terrain_texture_altered_land3_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_altered_land3 );

   	if (index == terrain_texture_road_detail   ) set_terrain_type_textures ( TERRAIN_TYPE_ROAD, terrain_texture_road_detail, terrain_texture_road_colour_pass, sld, sld, sl, sl,  255, 255, 255, terrain_surface_road );
   	if (index == terrain_texture_track_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_TRACK, terrain_texture_track_detail, terrain_texture_track_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_track );
   	if (index == terrain_texture_rail_detail       ) set_terrain_type_textures ( TERRAIN_TYPE_RAIL, terrain_texture_rail_detail, terrain_texture_rail_colour_pass, sl, sl, 0, 0, 38, 38, 38, terrain_surface_rail );
   	if (index == terrain_texture_road_bank_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_ROAD_BANK, terrain_texture_road_bank_detail, terrain_texture_road_bank_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_road_bank );

		if ( ( active_3d_environment ) && ( active_3d_environment->infrared_mode == INFRARED_ON ) )
		{
			if (index == terrain_texture_builtup_area1_infrared_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA1, terrain_texture_builtup_area1_infrared_detail, terrain_texture_builtup_area1_infrared_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area1_infrared );
			if (index == terrain_texture_builtup_area2_infrared_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA2, terrain_texture_builtup_area2_infrared_detail, terrain_texture_builtup_area2_infrared_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area2_infrared );
			if (index == terrain_texture_builtup_area3_infrared_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA3, terrain_texture_builtup_area3_infrared_detail, terrain_texture_builtup_area3_infrared_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area3_infrared );
			if (index == terrain_texture_builtup_area4_infrared_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA4, terrain_texture_builtup_area4_infrared_detail, terrain_texture_builtup_area4_infrared_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area4_infrared );
		}
		else
		{
			if (index == terrain_texture_builtup_area1_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA1, terrain_texture_builtup_area1_detail, terrain_texture_builtup_area1_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area1 );
			if (index == terrain_texture_builtup_area2_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA2, terrain_texture_builtup_area2_detail, terrain_texture_builtup_area2_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area2 );
			if (index == terrain_texture_builtup_area3_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA3, terrain_texture_builtup_area3_detail, terrain_texture_builtup_area3_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area3 );
			if (index == terrain_texture_builtup_area4_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA4, terrain_texture_builtup_area4_detail, terrain_texture_builtup_area4_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_builtup_area4 );
		}

   	if (index == terrain_texture_hedge_detail      ) set_terrain_type_textures ( TERRAIN_TYPE_HEDGE_TOP, terrain_texture_hedge_detail, terrain_texture_hedge_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_hedge );
   	if (index == terrain_texture_hedge_detail      ) set_terrain_type_textures ( TERRAIN_TYPE_HEDGE_SIDE_X, terrain_texture_hedge_detail, terrain_texture_hedge_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_hedge );
   	if (index == terrain_texture_hedge_detail      ) set_terrain_type_textures ( TERRAIN_TYPE_HEDGE_SIDE_Z, terrain_texture_hedge_detail, terrain_texture_hedge_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_hedge );
   	if (index == terrain_texture_wall_detail       ) set_terrain_type_textures ( TERRAIN_TYPE_WALL_TOP, terrain_texture_wall_detail, terrain_texture_wall_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_wall );
   	if (index == terrain_texture_wall_detail       ) set_terrain_type_textures ( TERRAIN_TYPE_WALL_SIDE_X, terrain_texture_wall_detail, terrain_texture_wall_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_wall );
   	if (index == terrain_texture_wall_detail       ) set_terrain_type_textures ( TERRAIN_TYPE_WALL_SIDE_Z, terrain_texture_wall_detail, terrain_texture_wall_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_wall );
   	if (index == terrain_texture_trench_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_TRENCH, terrain_texture_trench_detail, terrain_texture_trench_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_trench );
   	if (index == terrain_texture_trench_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_TRENCH_SIDE_X, terrain_texture_trench_detail, terrain_texture_trench_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_trench );
   	if (index == terrain_texture_trench_detail     ) set_terrain_type_textures ( TERRAIN_TYPE_TRENCH_SIDE_Z, terrain_texture_trench_detail, terrain_texture_trench_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_trench );
   	if (index == terrain_texture_rail_bank_detail  ) set_terrain_type_textures ( TERRAIN_TYPE_RAIL_BANK, terrain_texture_rail_bank_detail, terrain_texture_rail_bank_colour_pass, sld, sld, sl, sl, 255, 255, 255, terrain_surface_rail_bank );

		//VJ 051001 textures that have a different vertical scale
		sld = sl;   	
   	sldd = sld/2;  //river bank doisplays ok if vertical scale 0.5 of horizontal scale
   						//do not change because then all texture packs look strange
   	if (index == terrain_texture_river_bank_detail ) set_terrain_type_textures ( TERRAIN_TYPE_RIVER_BANK, terrain_texture_river_bank_detail, terrain_texture_river_bank_colour_pass, sld, sldd, sl, sldd, 255, 255, 255, terrain_surface_river_bank );   	

		sld = sl; 
		sldd = sld*0.25;
		//if this is too small there are simply more textures displayed
		//sldd = the vertical scale is 0.25 of the horizontal scale
		//scale top-side forest texture between top and side
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_TOP_X, terrain_texture_forest_top_detail, terrain_texture_forest_top_colour_pass,    		sld, sldd, sl, sldd, 255, 255, 255, terrain_surface_forest);
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_TOP_Z, terrain_texture_forest_top_detail, terrain_texture_forest_top_colour_pass,    		sld, sldd, sl, sldd, 255, 255, 255, terrain_surface_forest);
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X, terrain_texture_forest_bottom_detail, terrain_texture_forest_bottom_colour_pass, sld, sldd, sl, sldd, 255, 255, 255, terrain_surface_forest);
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z, terrain_texture_forest_bottom_detail, terrain_texture_forest_bottom_colour_pass, sld, sldd, sl, sldd, 255, 255, 255, terrain_surface_forest);
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_MID_X, terrain_texture_forest_middle_detail, terrain_texture_forest_middle_colour_pass,    sld, sldd, sl, sldd, 255, 255, 255, terrain_surface_forest);
		if (index == terrain_texture_forest_detail ) set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_MID_Z, terrain_texture_forest_middle_detail, terrain_texture_forest_middle_colour_pass,    sld, sldd, sl, sldd, 255, 255, 255, terrain_surface_forest);
			
		//VJ 051001 dynamic water textures
		//if (terrain_water_information[0].delay == -1) 
		  // return;
	
		delay_count++;	
		if (delay_count % terrain_water_information[0].delay == 0) 	
			change_river_texture++;
		if (delay_count % terrain_water_information[1].delay == 0) 	
			change_sea_texture++;
		if (delay_count % terrain_water_information[2].delay == 0) 	
			change_reservoir_texture++;
	
		if (delay_count == 50000) 
			delay_count = 0;
	
		if (change_river_texture == terrain_water_information[0].number)
			change_river_texture = 0;  
		if (change_sea_texture == terrain_water_information[1].number)
			change_sea_texture = 0;  
		// Casm 19AUG05 - Reservoir here, not sea
		if (change_reservoir_texture == terrain_water_information[2].number)
			change_reservoir_texture = 0;  
	
		//	start_of_river_textures = first bottom texture, start_of_river_textures+1 is the start of the transparent changing textures
		sl = terrain_water_information[0].scale_bottom;
		sld = terrain_water_information[0].scale_top;
		set_terrain_type_textures ( TERRAIN_TYPE_RIVER, terrain_water_information[0].placenr, terrain_water_information[0].placenr+1+change_river_texture, sld, sld, sl, sl, 255,255,255, terrain_surface_river );		
		
		sl = terrain_water_information[1].scale_bottom;
		sld = terrain_water_information[1].scale_top;
		set_terrain_type_textures ( TERRAIN_TYPE_SEA, terrain_water_information[1].placenr, terrain_water_information[1].placenr+1+change_sea_texture, sld, sld, sl, sl, 255,255,255, terrain_surface_sea );		
	
		sl = terrain_water_information[2].scale_bottom;
		sld = terrain_water_information[2].scale_top;
		set_terrain_type_textures ( TERRAIN_TYPE_RESERVOIR, terrain_water_information[2].placenr, terrain_water_information[2].placenr+1+change_reservoir_texture, sld, sld, sl, sl, 255,255,255, terrain_surface_reservoir );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_terrain_types ( void )
{
	// Xhit: the last argument in follwing calls sets the type of surface for the terrain. (030328)

	set_terrain_type_textures ( TERRAIN_TYPE_SEA, terrain_texture_sea_detail, terrain_texture_sea_colour_pass, 256, 256, 2048, 2048, 4, 103, 115, terrain_surface_sea );
   set_terrain_type_textures ( TERRAIN_TYPE_BEACH, terrain_texture_beach_detail, terrain_texture_beach_colour_pass, 256, 256, 2048, 2048, 199, 172, 120, terrain_surface_beach );
   set_terrain_type_textures ( TERRAIN_TYPE_LAND, terrain_texture_land_detail, terrain_texture_land_colour_pass, 256, 256, 2048, 2048, 61, 135, 75, terrain_surface_land);

	//
	// Forest textures
	//

	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_FLOOR, terrain_texture_forest_detail, 0, 512, 512, 0, 0, 80, 60, 30, terrain_surface_forest );
	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X, terrain_texture_forest_detail, 0, 512, 512, 0, 0, 80, 60, 30, terrain_surface_forest );
	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_MID_X, terrain_texture_forest_detail, 0, 512, 512, 0, 0, 80, 60, 30, terrain_surface_forest );
	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_TOP_X, terrain_texture_forest_detail, 0, 512, 512, 0, 0, 80, 60, 30, terrain_surface_forest );
	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z, terrain_texture_forest_detail, 0, 512, 512, 0, 0, 80, 60, 30, terrain_surface_forest );
	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_MID_Z, terrain_texture_forest_detail, 0, 512, 512, 0, 0, 80, 60, 30, terrain_surface_forest );
	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_SIDE_TOP_Z, terrain_texture_forest_detail, 0, 512, 512, 0, 0, 80, 60, 30, terrain_surface_forest );
	set_terrain_type_textures ( TERRAIN_TYPE_FOREST_TOP, terrain_texture_forest_detail, terrain_texture_forest_colour_pass, 512, 512, 1024, 1024, 190, 170, 15, terrain_surface_forest );

	//
	// Builtup areas
	//

   set_terrain_type_textures ( TERRAIN_TYPE_ROAD, terrain_texture_road_detail, terrain_texture_road_colour_pass, 8, 8, 1024, 1024, 255, 255, 255, terrain_surface_road );
   set_terrain_type_textures ( TERRAIN_TYPE_TRACK, terrain_texture_track_detail, terrain_texture_track_colour_pass, 8, 8, 1024, 1024, 255, 255, 255, terrain_surface_track );

	if ( ( active_3d_environment ) && ( active_3d_environment->infrared_mode == INFRARED_ON ) )
	{
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA1, terrain_texture_builtup_area1_infrared_detail, terrain_texture_builtup_area1_infrared_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area1_infrared );
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA2, terrain_texture_builtup_area2_infrared_detail, terrain_texture_builtup_area2_infrared_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area2_infrared );
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA3, terrain_texture_builtup_area3_infrared_detail, terrain_texture_builtup_area3_infrared_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area3_infrared );
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA4, terrain_texture_builtup_area4_infrared_detail, terrain_texture_builtup_area4_infrared_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area4_infrared );
	}
	else
	{
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA1, terrain_texture_builtup_area1_detail, terrain_texture_builtup_area1_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area1 );
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA2, terrain_texture_builtup_area2_detail, terrain_texture_builtup_area2_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area2 );
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA3, terrain_texture_builtup_area3_detail, terrain_texture_builtup_area3_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area3 );
		set_terrain_type_textures ( TERRAIN_TYPE_BUILT_UP_AREA4, terrain_texture_builtup_area4_detail, terrain_texture_builtup_area4_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_builtup_area4 );
	}

   set_terrain_type_textures ( TERRAIN_TYPE_RIVER, terrain_texture_river_detail, terrain_texture_river_colour_pass, 256, 256, 2048, 2048, 4, 103, 115, terrain_surface_river);
   set_terrain_type_textures ( TERRAIN_TYPE_RESERVOIR, terrain_texture_reservoir_detail, terrain_texture_reservoir_colour_pass, 1024, 1024, 2048, 2048, 4, 103, 115, terrain_surface_reservoir );
   set_terrain_type_textures ( TERRAIN_TYPE_RAIL, terrain_texture_rail_detail, terrain_texture_rail_colour_pass, 256, 256, 0, 0, 38, 38, 38, terrain_surface_rail );
   set_terrain_type_textures ( TERRAIN_TYPE_ROAD_BANK, terrain_texture_road_bank_detail, terrain_texture_road_bank_colour_pass, 256, 256, 2048, 2048, 61, 135, 75, terrain_surface_road_bank );
   set_terrain_type_textures ( TERRAIN_TYPE_RIVER_BANK, terrain_texture_river_bank_detail, terrain_texture_river_bank_colour_pass, 256, 256, 2048, 2048, 141, 122, 84, terrain_surface_river_bank );
   set_terrain_type_textures ( TERRAIN_TYPE_RAIL_BANK, terrain_texture_rail_bank_detail, terrain_texture_rail_bank_colour_pass, 256, 256, 2048, 2048, 141, 122, 84, terrain_surface_rail_bank );

	//
	// Field types
	//

   set_terrain_type_textures ( TERRAIN_TYPE_FIELD1, terrain_texture_field1_detail, terrain_texture_field1_colour_pass, 256, 256, 1024, 1024, 255, 255, 80, terrain_surface_field1 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD2, terrain_texture_field2_detail, terrain_texture_field2_colour_pass, 256, 256, 1024, 1024, 100, 70, 40, terrain_surface_field2 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD3, terrain_texture_field3_detail, terrain_texture_field3_colour_pass, 256, 256, 1024, 1024, 140, 70, 50, terrain_surface_field3 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD4, terrain_texture_field4_detail, terrain_texture_field4_colour_pass, 256, 256, 1024, 1024, 190, 170, 15, terrain_surface_field4 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD5, terrain_texture_field5_detail, terrain_texture_field5_colour_pass, 256, 256, 1024, 1024, 170, 140, 0, terrain_surface_field5 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD6, terrain_texture_field6_detail, terrain_texture_field6_colour_pass, 256, 256, 1024, 1024, 81, 165, 85, terrain_surface_field6 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD7, terrain_texture_field7_detail, terrain_texture_field7_colour_pass, 256, 256, 1024, 1024, 41, 115, 50, terrain_surface_field7 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD8, terrain_texture_field8_detail, terrain_texture_field8_colour_pass, 256, 256, 1024, 1024, 255, 255, 80, terrain_surface_field8 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD9, terrain_texture_field9_detail, terrain_texture_field9_colour_pass, 256, 256, 1024, 1024, 100, 70, 40, terrain_surface_field9 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD10, terrain_texture_field10_detail, terrain_texture_field10_colour_pass, 256, 256, 1024, 1024, 140, 70, 50, terrain_surface_field10 );
   set_terrain_type_textures ( TERRAIN_TYPE_FIELD11, terrain_texture_field11_detail, terrain_texture_field11_colour_pass, 256, 256, 1024, 1024, 190, 170, 15, terrain_surface_field11 );

	//
	// Varied Land Types (e.g. snow, rock etc.)
	//

	set_terrain_type_textures ( TERRAIN_TYPE_ALTERED_LAND1, terrain_texture_altered_land1_detail, terrain_texture_altered_land1_colour_pass, 256, 256, 2048, 2048, 170, 140, 0, terrain_surface_altered_land1 );
	set_terrain_type_textures ( TERRAIN_TYPE_ALTERED_LAND2, terrain_texture_altered_land2_detail, terrain_texture_altered_land2_colour_pass, 128, 128, 2048, 2048, 81, 165, 85, terrain_surface_altered_land2 );
	set_terrain_type_textures ( TERRAIN_TYPE_ALTERED_LAND3, terrain_texture_altered_land3_detail, terrain_texture_altered_land3_colour_pass, 256, 256, 2048, 2048, 255, 255, 255, terrain_surface_altered_land3 );


	//
	// Hedges / Walls
	//

   set_terrain_type_textures ( TERRAIN_TYPE_HEDGE_TOP, terrain_texture_hedge_detail, terrain_texture_hedge_colour_pass, 40, 40, 0, 0, 190, 170, 15, terrain_surface_hedge );
   set_terrain_type_textures ( TERRAIN_TYPE_HEDGE_SIDE_X, terrain_texture_hedge_detail, terrain_texture_hedge_colour_pass, 40, 40, 0, 0, 190, 170, 15, terrain_surface_hedge );
   set_terrain_type_textures ( TERRAIN_TYPE_HEDGE_SIDE_Z, terrain_texture_hedge_detail, terrain_texture_hedge_colour_pass, 40, 40, 0, 0, 190, 170, 15, terrain_surface_hedge );

	set_terrain_type_textures ( TERRAIN_TYPE_WALL_TOP, terrain_texture_wall_detail, terrain_texture_wall_colour_pass, 5, 5, 0, 0, 255, 255, 255, terrain_surface_wall );
	set_terrain_type_textures ( TERRAIN_TYPE_WALL_SIDE_X, terrain_texture_wall_detail, terrain_texture_wall_colour_pass, 5, 5, 0, 0, 255, 255, 255, terrain_surface_wall );
	set_terrain_type_textures ( TERRAIN_TYPE_WALL_SIDE_Z, terrain_texture_wall_detail, terrain_texture_wall_colour_pass, 5, 5, 0, 0, 255, 255, 255, terrain_surface_wall );

   set_terrain_type_textures ( TERRAIN_TYPE_TRENCH, terrain_texture_trench_detail, terrain_texture_trench_colour_pass, 256, 256, 0, 0, 190, 170, 15, terrain_surface_trench );
   set_terrain_type_textures ( TERRAIN_TYPE_TRENCH_SIDE_X, terrain_texture_trench_detail, terrain_texture_trench_colour_pass, 256, 256, 0, 0, 190, 170, 15, terrain_surface_trench );
   set_terrain_type_textures ( TERRAIN_TYPE_TRENCH_SIDE_Z, terrain_texture_trench_detail, terrain_texture_trench_colour_pass, 256, 256, 0, 0, 190, 170, 15, terrain_surface_trench );

	//
	// All the types that are used in the terrain generation tool
	//

   set_terrain_type_textures ( TEMP_TERRAIN_TYPE_BEACH_MID,			0, 0, 256, 256, 0, 0, 255, 0, 255, 0 );
   set_terrain_type_textures ( TEMP_TERRAIN_TYPE_FRINGE,				0, 0, 256, 256, 0, 0, 255, 0, 255, 0 );
   set_terrain_type_textures ( TEMP_TERRAIN_TYPE_POWER_LINE,		0, 0, 256, 256, 0, 0, 255, 0, 255, 0 );
   set_terrain_type_textures ( TEMP_TERRAIN_TYPE_TELEPHONE_LINE,	0, 0, 256, 256, 0, 0, 255, 0, 255, 0 );
   set_terrain_type_textures ( TEMP_TERRAIN_TYPE_SEA_BANK,			0, 0, 256, 256, 0, 0, 255, 0, 255, 0 );
   set_terrain_type_textures ( TEMP_TERRAIN_TYPE_COASTAL_RIVER,	0, 0, 256, 256, 0, 0, 255, 0, 255, 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_thailand_terrain_types ( void )
{

	float
		contour_heights[] =
		{

			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1500,
			2200,
			3000,
		};

	int
		reflection_texture_index;

	//
	// Don't allow snowing effect in thailand
	//

	set_3d_rain_special_snow_flag ( FALSE );

	terrain_texture_sea_detail								= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA" );
	terrain_texture_beach_detail							= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_land_colour_pass						= get_system_texture_index ( "CH_TERRAIN_CP1" );
	terrain_texture_forest_detail							= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_forest_colour_pass						= 0;
	terrain_texture_builtup_area1_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY4" );
	terrain_texture_builtup_area1_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area2_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY3" );
	terrain_texture_builtup_area2_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area3_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY2" );
	terrain_texture_builtup_area3_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area4_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY1" );
	terrain_texture_builtup_area4_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area1_infrared_detail			= get_system_texture_index ( "TERRAIN_BW_CITY4" );
	terrain_texture_builtup_area1_infrared_colour_pass		= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area2_infrared_detail			= get_system_texture_index ( "TERRAIN_BW_CITY3" );
	terrain_texture_builtup_area2_infrared_colour_pass		= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area3_infrared_detail			= get_system_texture_index ( "TERRAIN_BW_CITY2" );
	terrain_texture_builtup_area3_infrared_colour_pass		= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area4_infrared_detail			= get_system_texture_index ( "TERRAIN_BW_CITY1" );
	terrain_texture_builtup_area4_infrared_colour_pass		= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass						= get_system_texture_index ( "COLOUR_PASS_WALL" );
	terrain_texture_track_detail							= get_system_texture_index ( "TERRAIN_THAI_DIRT_TRACK" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_WALL" );
	terrain_texture_river_detail							= get_system_texture_index ( "TERRAIN_THAILAND_RIVER" );
	terrain_texture_river_colour_pass						= 0;
	terrain_texture_reservoir_detail						= get_system_texture_index ( "TERRAIN_THAILAND_RIVER" );
	terrain_texture_reservoir_colour_pass					= 0;
	terrain_texture_rail_detail								= 0;
	terrain_texture_rail_colour_pass						= 0;
	terrain_texture_road_bank_detail						= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_rail_bank_detail						= 0;
	terrain_texture_rail_bank_colour_pass					= 0;
	terrain_texture_field1_detail							= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field1_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field2_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field2_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field3_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field3_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field4_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field4_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field5_detail							= get_system_texture_index ( "TERRAIN_WHEATFIELD" );
	terrain_texture_field5_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field6_detail							= get_system_texture_index ( "TERRAIN_LIGHTGREENFIELD" );
	terrain_texture_field6_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field7_detail							= get_system_texture_index ( "TERRAIN_DARKGREENFIELD" );
	terrain_texture_field7_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field8_detail							= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field8_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field9_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field9_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field10_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field10_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field11_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field11_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_SWAMP1" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_SWAMP2" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_HIGHLAND" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_hedge_detail							= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_hedge_colour_pass						= 0;
	terrain_texture_wall_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_wall_colour_pass						= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_trench_detail							= get_system_texture_index ( "TERRAIN_THAILAND_RIVER" );
	terrain_texture_trench_colour_pass						= 0;

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SOIL;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_road										= SURFACE_TYPE_ASPHALT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land2							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land3							= SURFACE_TYPE_SOIL;
	terrain_surface_hedge									= SURFACE_TYPE_SOIL;
	terrain_surface_wall										= SURFACE_TYPE_ROCK;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DEFAULT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_cuba_terrain_types ( void )
{

	float
		contour_heights[] =
		{

			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1250,
			1500,
			2000,
		};

	int
		reflection_texture_index;

	//
	// Don't allow snowing effect in Cuba
	//

	set_3d_rain_special_snow_flag ( FALSE );

	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "CH_TERRAIN_CP1" );
	terrain_texture_forest_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_forest_colour_pass						= 0;
	terrain_texture_builtup_area1_detail					= get_system_texture_index ( "TERRAIN_CUBA_CITY4" );
	terrain_texture_builtup_area1_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area2_detail					= get_system_texture_index ( "TERRAIN_CUBA_CITY3" );
	terrain_texture_builtup_area2_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area3_detail					= get_system_texture_index ( "TERRAIN_CUBA_CITY2" );
	terrain_texture_builtup_area3_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area4_detail					= get_system_texture_index ( "TERRAIN_CUBA_CITY1" );
	terrain_texture_builtup_area4_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area1_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY4" );
	terrain_texture_builtup_area1_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area2_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY3" );
	terrain_texture_builtup_area2_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area3_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY2" );
	terrain_texture_builtup_area3_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area4_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY1" );
	terrain_texture_builtup_area4_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_WALL" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_THAI_TRACK" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_WALL" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_river_colour_pass						= 0;
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_reservoir_colour_pass					= 0;
	terrain_texture_rail_detail								= 0;
	terrain_texture_rail_colour_pass							= 0;
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_rail_bank_detail							= 0;
	terrain_texture_rail_bank_colour_pass					= 0;
	terrain_texture_field1_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field1_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field2_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field2_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field3_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field3_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field4_detail								= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field4_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field5_detail								= get_system_texture_index ( "TERRAIN_WHEATFIELD" );
	terrain_texture_field5_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field6_detail								= get_system_texture_index ( "TERRAIN_LIGHTGREENFIELD" );
	terrain_texture_field6_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field7_detail								= get_system_texture_index ( "TERRAIN_DARKGREENFIELD" );
	terrain_texture_field7_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field8_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field8_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field9_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field9_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field10_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field10_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field11_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field11_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_SCRUB" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_MOUNTAINS" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_BARE_ROCK2" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_SNOW" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SNOW" );
	terrain_texture_hedge_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_hedge_colour_pass						= 0;
	terrain_texture_wall_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_wall_colour_pass							= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_trench_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_trench_colour_pass						= 0;

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SOIL;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_road										= SURFACE_TYPE_ASPHALT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_ROCK;
	terrain_surface_altered_land2							= SURFACE_TYPE_ROCK;
	terrain_surface_altered_land3							= SURFACE_TYPE_SNOW;
	terrain_surface_hedge									= SURFACE_TYPE_SOIL;
	terrain_surface_wall										= SURFACE_TYPE_SOIL;
	terrain_surface_trench									= SURFACE_TYPE_WATER;


	set_object_3d_texture_camoflage_by_name ( "DEFAULT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_georgia_terrain_types ( void )
{

	float
		contour_heights[] =
		{

			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1500,
			3000,
			5000,
		};

	int
		reflection_texture_index;

	//
	// DO allow snowing effect in Georgia
	//

	set_3d_rain_special_snow_flag ( TRUE );

	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_GRG_SEA" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "CH_TERRAIN_CP1" );
	terrain_texture_forest_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_forest_colour_pass						= 0;
	terrain_texture_builtup_area1_detail					= get_system_texture_index ( "TERRAIN_GRG_CITY4" );
	terrain_texture_builtup_area1_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area2_detail					= get_system_texture_index ( "TERRAIN_GRG_CITY3" );
	terrain_texture_builtup_area2_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area3_detail					= get_system_texture_index ( "TERRAIN_GRG_CITY2" );
	terrain_texture_builtup_area3_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area4_detail					= get_system_texture_index ( "TERRAIN_GRG_CITY1" );
	terrain_texture_builtup_area4_colour_pass				= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area1_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY4" );
	terrain_texture_builtup_area1_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area2_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY3" );
	terrain_texture_builtup_area2_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area3_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY2" );
	terrain_texture_builtup_area3_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_builtup_area4_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY1" );
	terrain_texture_builtup_area4_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_WALL" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_THAI_TRACK" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_WALL" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_river_colour_pass						= 0;
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_reservoir_colour_pass					= 0;
	terrain_texture_rail_detail								= 0;
	terrain_texture_rail_colour_pass							= 0;
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_rail_bank_detail							= 0;
	terrain_texture_rail_bank_colour_pass					= 0;
	terrain_texture_field1_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field1_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field2_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field2_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field3_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field3_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field4_detail								= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field4_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field5_detail								= get_system_texture_index ( "TERRAIN_WHEATFIELD" );
	terrain_texture_field5_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field6_detail								= get_system_texture_index ( "TERRAIN_LIGHTGREENFIELD" );
	terrain_texture_field6_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field7_detail								= get_system_texture_index ( "TERRAIN_DARKGREENFIELD" );
	terrain_texture_field7_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field8_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field8_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field9_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field9_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field10_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field10_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field11_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field11_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_SCRUB" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_MOUNTAINS" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_BARE_ROCK2" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_SNOW" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SNOW" );
	terrain_texture_hedge_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_hedge_colour_pass						= 0;
	terrain_texture_wall_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_wall_colour_pass							= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_trench_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_trench_colour_pass						= 0;

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();
	
	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SOIL;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_road										= SURFACE_TYPE_ASPHALT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_ROCK;
	terrain_surface_altered_land2							= SURFACE_TYPE_ROCK;
	terrain_surface_altered_land3							= SURFACE_TYPE_SNOW;
	terrain_surface_hedge									= SURFACE_TYPE_SOIL;
	terrain_surface_wall										= SURFACE_TYPE_SOIL;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DEFAULT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_lebanon_terrain_types ( void )
{

	float
		contour_heights[] =
		{

			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1600,
			2300,
			3100,
		};

	int
		reflection_texture_index;

	set_3d_rain_special_snow_flag ( FALSE );

	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_DETAIL_LEBANON" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_forest_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_LEBANON" );
	terrain_texture_forest_colour_pass						= get_system_texture_index ( "COLOUR_PASS_FOREST_LEBANON" );

	terrain_texture_builtup_area1_detail					= get_system_texture_index ( "CP_LEBANON_V2_CITY1" );
	terrain_texture_builtup_area1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_builtup_area2_detail					= get_system_texture_index ( "CP_LEBANON_V2_CITY2" );
	terrain_texture_builtup_area2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_builtup_area3_detail					= get_system_texture_index ( "CP_LEBANON_V2_CITY3" );
	terrain_texture_builtup_area3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_builtup_area4_detail					= get_system_texture_index ( "CP_LEBANON_V2_CITY4" );
	terrain_texture_builtup_area4_colour_pass				= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_builtup_area1_infrared_detail		= get_system_texture_index ( "BW_LEBANON_V2_CITY1" );
	terrain_texture_builtup_area1_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_builtup_area2_infrared_detail		= get_system_texture_index ( "BW_LEBANON_V2_CITY2" );
	terrain_texture_builtup_area2_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_builtup_area3_infrared_detail		= get_system_texture_index ( "BW_LEBANON_V2_CITY3" );
	terrain_texture_builtup_area3_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_builtup_area4_infrared_detail		= get_system_texture_index ( "BW_LEBANON_V2_CITY4" );
	terrain_texture_builtup_area4_infrared_colour_pass	= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_ROCK_LEBANON" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_ROCK_LEBANON" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_river_colour_pass						= 0;
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_reservoir_colour_pass					= 0;
	terrain_texture_rail_detail								= 0;
	terrain_texture_rail_colour_pass							= 0;
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_LEBANON" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_rail_bank_detail							= 0;
	terrain_texture_rail_bank_colour_pass					= 0;
	terrain_texture_field1_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field1_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field2_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field2_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field3_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field3_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field4_detail								= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field4_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field5_detail								= get_system_texture_index ( "TERRAIN_WHEATFIELD" );
	terrain_texture_field5_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field6_detail								= get_system_texture_index ( "TERRAIN_LIGHTGREENFIELD" );
	terrain_texture_field6_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field7_detail								= get_system_texture_index ( "TERRAIN_DARKGREENFIELD" );
	terrain_texture_field7_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field8_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field8_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field9_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field9_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field10_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field10_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_field11_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field11_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_DETAIL_LEBANON" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SCRUB_LEBANON" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_BARE_ROCK_LEBANON" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_ROCK_LEBANON" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_SNOW_LEBANON" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SNOW" );
	terrain_texture_hedge_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
	terrain_texture_hedge_colour_pass						= 0;
	terrain_texture_wall_detail								= get_system_texture_index ( "TERRAIN_WALL_LEBANON" );
	terrain_texture_wall_colour_pass							= get_system_texture_index ( "COLOUR_PASS_ROCK_LEBANON" );
	terrain_texture_trench_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_trench_colour_pass						= 0;


	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_DESERT;
	terrain_surface_land										= SURFACE_TYPE_DESERT;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_DESERT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_DESERT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_DESERT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_DESERT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_DESERT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_DESERT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_DESERT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_DESERT;
	terrain_surface_road										= SURFACE_TYPE_DESERT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_DESERT;
	terrain_surface_rail_bank								= SURFACE_TYPE_DESERT;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_DESERT;
	terrain_surface_altered_land2							= SURFACE_TYPE_DESERT;
	terrain_surface_altered_land3							= SURFACE_TYPE_SNOW;
	terrain_surface_hedge									= SURFACE_TYPE_DESERT;
	terrain_surface_wall										= SURFACE_TYPE_DESERT;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DESERT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{
		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_yemen_terrain_types ( void )
{

	float
		contour_heights[] =
		{

			-1000,
			-0.0001,
			250,
			500,
			750,
			1250,
			2000,
			2500,
			3000,
		};

	int
		reflection_texture_index;

	set_3d_rain_special_snow_flag ( FALSE );
	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );

	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_YEMEN_GRITTY" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );

	terrain_texture_forest_detail								= get_system_texture_index ( "TERRAIN_BARE_ROCK2" );
	terrain_texture_forest_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );

	terrain_texture_builtup_area1_detail					= get_system_texture_index ( "YEMEN_CITY3" );
	terrain_texture_builtup_area1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_builtup_area2_detail					= get_system_texture_index ( "YEMEN_CITY1" );
	terrain_texture_builtup_area2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_builtup_area3_detail					= get_system_texture_index ( "YEMEN_CITY1" );
	terrain_texture_builtup_area3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_builtup_area4_detail					= get_system_texture_index ( "YEMEN_CITY1" );
	terrain_texture_builtup_area4_colour_pass				= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );

	terrain_texture_builtup_area1_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY4" );
	terrain_texture_builtup_area1_infrared_colour_pass	= 0;
	terrain_texture_builtup_area2_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY3" );
	terrain_texture_builtup_area2_infrared_colour_pass	= 0;
	terrain_texture_builtup_area3_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY2" );
	terrain_texture_builtup_area3_infrared_colour_pass	= 0;
	terrain_texture_builtup_area4_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY1" );
	terrain_texture_builtup_area4_infrared_colour_pass = 0;
	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_WALL" );      //TERRAIN_THAI_TRACK" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_YEMEN_STONY" );
	terrain_texture_river_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_YEMEN_GRITTY" );
	terrain_texture_reservoir_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_rail_detail								= 0;
	terrain_texture_rail_colour_pass							= 0;
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_YEMEN_GRITTY" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_rail_bank_detail							= 0;
	terrain_texture_rail_bank_colour_pass					= 0;
	terrain_texture_field1_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field1_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field2_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field2_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field3_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field3_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field4_detail								= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field4_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field5_detail								= get_system_texture_index ( "TERRAIN_WHEATFIELD" );
	terrain_texture_field5_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field6_detail								= get_system_texture_index ( "TERRAIN_LIGHTGREENFIELD" );
	terrain_texture_field6_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field7_detail								= get_system_texture_index ( "TERRAIN_DARKGREENFIELD" );
	terrain_texture_field7_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field8_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field8_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field9_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field9_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field10_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field10_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field11_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field11_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_YEMEN_BAKED" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_YEMEN_STONY" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_YEMEN_LUNAR" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_hedge_detail								= get_system_texture_index ( "TERRAIN_YEMEN_STONY" );
	terrain_texture_hedge_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_wall_detail								= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_wall_colour_pass							= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_trench_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_trench_colour_pass						= 0;

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SAND;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_SAND;
	terrain_surface_builtup_area2							= SURFACE_TYPE_SAND;
	terrain_surface_builtup_area3							= SURFACE_TYPE_SAND;
	terrain_surface_builtup_area4							= SURFACE_TYPE_SAND;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_SAND;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_SAND;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_SAND;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_SAND;
	terrain_surface_road										= SURFACE_TYPE_SAND;
	terrain_surface_track									= SURFACE_TYPE_SAND;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SAND;
	terrain_surface_road_bank								= SURFACE_TYPE_SAND;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SAND;
	terrain_surface_field1									= SURFACE_TYPE_SAND;
	terrain_surface_field2									= SURFACE_TYPE_SAND;
	terrain_surface_field3									= SURFACE_TYPE_SAND;
	terrain_surface_field4									= SURFACE_TYPE_SAND;
	terrain_surface_field5									= SURFACE_TYPE_SAND;
	terrain_surface_field6									= SURFACE_TYPE_SAND;
	terrain_surface_field7									= SURFACE_TYPE_SAND;
	terrain_surface_field8									= SURFACE_TYPE_SAND;
	terrain_surface_field9									= SURFACE_TYPE_SAND;
	terrain_surface_field10									= SURFACE_TYPE_SAND;
	terrain_surface_field11									= SURFACE_TYPE_SAND;
	terrain_surface_altered_land1							= SURFACE_TYPE_SAND;
	terrain_surface_altered_land2							= SURFACE_TYPE_SAND;
	terrain_surface_altered_land3							= SURFACE_TYPE_SNOW;
	terrain_surface_hedge									= SURFACE_TYPE_SAND;
	terrain_surface_wall										= SURFACE_TYPE_SAND;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DESERT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_taiwan_terrain_types ( void )
{

	float
		contour_heights[] =
		{

			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1750,
			2600,
			3700,
		};

	int
		reflection_texture_index;

	set_3d_rain_special_snow_flag ( FALSE );

	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );

	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_HIGHLAND" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SWAMP" );

	terrain_texture_forest_detail								= get_system_texture_index ( "TERRAIN_TREE_CANOPY_LEBANON" );
	terrain_texture_forest_colour_pass						= get_system_texture_index ( "COLOUR_PASS_FOREST_LEBANON" );

	terrain_texture_builtup_area1_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY3" );
	terrain_texture_builtup_area1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SWAMP" );
	terrain_texture_builtup_area2_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY2" );
	terrain_texture_builtup_area2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SWAMP" );
	terrain_texture_builtup_area3_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY1" );
	terrain_texture_builtup_area3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SWAMP" );
	terrain_texture_builtup_area4_detail					= get_system_texture_index ( "TERRAIN_THAI_CITY3" );
	terrain_texture_builtup_area4_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SWAMP" );

	terrain_texture_builtup_area1_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY4" );
	terrain_texture_builtup_area1_infrared_colour_pass	= 0;
	terrain_texture_builtup_area2_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY3" );
	terrain_texture_builtup_area2_infrared_colour_pass	= 0;
	terrain_texture_builtup_area3_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY2" );
	terrain_texture_builtup_area3_infrared_colour_pass	= 0;
	terrain_texture_builtup_area4_infrared_detail		= get_system_texture_index ( "TERRAIN_BW_CITY1" );
	terrain_texture_builtup_area4_infrared_colour_pass = 0;
	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_WALL" );      //TERRAIN_THAI_TRACK" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_river_colour_pass						= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_reservoir_colour_pass					= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_rail_detail								= 0;
	terrain_texture_rail_colour_pass							= 0;
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_YEMEN_GRITTY" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_rail_bank_detail							= 0;
	terrain_texture_rail_bank_colour_pass					= 0;
	terrain_texture_field1_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field1_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field2_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field2_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field3_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field3_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field4_detail								= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field4_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field5_detail								= get_system_texture_index ( "TERRAIN_WHEATFIELD" );
	terrain_texture_field5_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field6_detail								= get_system_texture_index ( "TERRAIN_LIGHTGREENFIELD" );
	terrain_texture_field6_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field7_detail								= get_system_texture_index ( "TERRAIN_DARKGREENFIELD" );
	terrain_texture_field7_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field8_detail								= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
	terrain_texture_field8_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field9_detail								= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
	terrain_texture_field9_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field10_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
	terrain_texture_field10_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_field11_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
	terrain_texture_field11_colour_pass						= get_system_texture_index ( "COLOUR_PASS" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_YEMEN_BAKED" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SWAMP" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_SCRUB" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SWAMP" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_YEMEN_STONY" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_MOUNTAINS" );
	terrain_texture_hedge_detail								= get_system_texture_index ( "TERRAIN_YEMEN_STONY" );
	terrain_texture_hedge_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_wall_detail								= get_system_texture_index ( "CP_LEBANON_V2_CITY3" );
	terrain_texture_wall_colour_pass							= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_trench_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_trench_colour_pass						= 0;

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SOIL;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_road										= SURFACE_TYPE_ASPHALT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land2							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land3							= SURFACE_TYPE_SOIL;
	terrain_surface_hedge									= SURFACE_TYPE_SOIL;
	terrain_surface_wall										= SURFACE_TYPE_ROCK;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DEFAULT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_terrain_rendering_routines ( terrain_types type, terrain_polygon_type polygon_type,
													void ( *render_word_clipped ) ( int ),
													void ( *render_byte_clipped ) ( int ),
													void ( *render_word_unclipped ) ( int ),
													void ( *render_byte_unclipped ) ( int ) )
{

	terrain_type_information[type].initialised = TRUE;

	terrain_type_information[type].polygon_type = polygon_type;

	terrain_type_information[type].render_word_clipped = render_word_clipped;
	terrain_type_information[type].render_byte_clipped = render_byte_clipped;
	terrain_type_information[type].render_word_unclipped = render_word_unclipped;
	terrain_type_information[type].render_byte_unclipped = render_byte_unclipped;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture is detail, texture2 is colour pass
void set_terrain_type_textures ( terrain_types type, int texture, int texture2,
											float xz_texture_size, float y_texture_size,
											float xz_texture_size2, float y_texture_size2,
											int red, int green, int blue, surface_types surface_type )
{

	if ( xz_texture_size == 0.0 )		xz_texture_size = TERRAIN_DEFAULT_TEXTURE_SIZE;
	if ( y_texture_size == 0.0 )		y_texture_size = TERRAIN_DEFAULT_TEXTURE_SIZE;
	if ( xz_texture_size2 == 0.0 )	xz_texture_size2 = TERRAIN_DEFAULT_TEXTURE_SIZE;
	if ( y_texture_size2 == 0.0 )		y_texture_size2 = TERRAIN_DEFAULT_TEXTURE_SIZE;

	terrain_type_information[type].texture = system_textures[texture];
	terrain_type_information[type].xz_texture_scale = ( TERRAIN_3D_XZ_SCALE / xz_texture_size );
	terrain_type_information[type].y_texture_scale =  1.0 / y_texture_size;

	terrain_type_information[type].texture2 = system_textures[texture2];
	terrain_type_information[type].xz_texture_scale2 = ( TERRAIN_3D_XZ_SCALE / xz_texture_size2 );
	terrain_type_information[type].y_texture_scale2 = 1.0 / y_texture_size2;

	terrain_type_information[type].red = red;
	terrain_type_information[type].green = green;
	terrain_type_information[type].blue = blue;

	// Xhit: set the appropiate surface type according to campaign and terrain type. (030328)
	terrain_type_information[type].surface_type = surface_type;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_terrain_textures ( terrain_types type,  int texture, int texture2 )
{

	terrain_type_information[type].texture = system_textures[texture];
	terrain_type_information[type].texture2 = system_textures[texture2];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TERRAIN_TYPE_NAME
{

	terrain_types
		type;

	char
		*name;
};

typedef struct TERRAIN_TYPE_NAME terrain_type_name;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

terrain_type_name
	terrain_type_names[] =
	{

		{ TERRAIN_TYPE_INVALID, "TERRAIN_TYPE_INVALID" },
   	{ TERRAIN_TYPE_RIVER, "TERRAIN_TYPE_RIVER" },
   	{ TERRAIN_TYPE_RESERVOIR, "TERRAIN_TYPE_RESERVOIR" },
   	{ TERRAIN_TYPE_TRENCH, "TERRAIN_TYPE_TRENCH" },
   	{ TERRAIN_TYPE_RIVER_BANK, "TERRAIN_TYPE_RIVER_BANK" },
   	{ TERRAIN_TYPE_TRENCH_SIDE_X, "TERRAIN_TYPE_TRENCH_SIDE_X" },
   	{ TERRAIN_TYPE_TRENCH_SIDE_Z, "TERRAIN_TYPE_TRENCH_SIDE_Z" },
   	{ TERRAIN_TYPE_SEA, "TERRAIN_TYPE_SEA" },
   	{ TERRAIN_TYPE_BEACH, "TERRAIN_TYPE_BEACH" },
   	{ TERRAIN_TYPE_LAND, "TERRAIN_TYPE_LAND" },
		{ TERRAIN_TYPE_FIELD1, "TERRAIN_TYPE_FIELD1" },
		{ TERRAIN_TYPE_FIELD2, "TERRAIN_TYPE_FIELD2" },
		{ TERRAIN_TYPE_FIELD3, "TERRAIN_TYPE_FIELD3" },
		{ TERRAIN_TYPE_FIELD4, "TERRAIN_TYPE_FIELD4" },
		{ TERRAIN_TYPE_FIELD5, "TERRAIN_TYPE_FIELD5" },
		{ TERRAIN_TYPE_FIELD6, "TERRAIN_TYPE_FIELD6" },
		{ TERRAIN_TYPE_FIELD7, "TERRAIN_TYPE_FIELD7" },
		{ TERRAIN_TYPE_FIELD8, "TERRAIN_TYPE_FIELD8" },
		{ TERRAIN_TYPE_FIELD9, "TERRAIN_TYPE_FIELD9" },
		{ TERRAIN_TYPE_FIELD10, "TERRAIN_TYPE_FIELD10" },
		{ TERRAIN_TYPE_FIELD11, "TERRAIN_TYPE_FIELD11" },
		{ TERRAIN_TYPE_ALTERED_LAND1, "TERRAIN_TYPE_ALTERED_LAND1" },
		{ TERRAIN_TYPE_ALTERED_LAND2, "TERRAIN_TYPE_ALTERED_LAND2" },
		{ TERRAIN_TYPE_ALTERED_LAND3, "TERRAIN_TYPE_ALTERED_LAND3" },
		{ TERRAIN_TYPE_FOREST_FLOOR, "TERRAIN_TYPE_FOREST_FLOOR" },
 		{ TERRAIN_TYPE_ROAD_BANK, "TERRAIN_TYPE_ROAD_BANK" },
 		{ TERRAIN_TYPE_RAIL_BANK, "TERRAIN_TYPE_RAIL_BANK" },
		{ TERRAIN_TYPE_HEDGE_SIDE_X, "TERRAIN_TYPE_HEDGE_SIDE_X" },
		{ TERRAIN_TYPE_HEDGE_SIDE_Z, "TERRAIN_TYPE_HEDGE_SIDE_Z" },
		{ TERRAIN_TYPE_WALL_SIDE_X, "TERRAIN_TYPE_WALL_SIDE_X" },
		{ TERRAIN_TYPE_WALL_SIDE_Z, "TERRAIN_TYPE_WALL_SIDE_Z" },
 		{ TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X, "TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X" },
 		{ TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z, "TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z" },
 		{ TERRAIN_TYPE_FOREST_SIDE_MID_X, "TERRAIN_TYPE_FOREST_SIDE_MID_X" },
 		{ TERRAIN_TYPE_FOREST_SIDE_MID_Z, "TERRAIN_TYPE_FOREST_SIDE_MID_Z" },
 		{ TERRAIN_TYPE_FOREST_SIDE_TOP_X, "TERRAIN_TYPE_FOREST_SIDE_TOP_X" },
 		{ TERRAIN_TYPE_FOREST_SIDE_TOP_Z, "TERRAIN_TYPE_FOREST_SIDE_TOP_Z" },
 		{ TERRAIN_TYPE_BUILT_UP_AREA1, "TERRAIN_TYPE_BUILT_UP_AREA1" },
 		{ TERRAIN_TYPE_BUILT_UP_AREA2, "TERRAIN_TYPE_BUILT_UP_AREA2" },
 		{ TERRAIN_TYPE_BUILT_UP_AREA3, "TERRAIN_TYPE_BUILT_UP_AREA3" },
 		{ TERRAIN_TYPE_BUILT_UP_AREA4, "TERRAIN_TYPE_BUILT_UP_AREA4" },
 		{ TERRAIN_TYPE_ROAD, "TERRAIN_TYPE_ROAD" },
 		{ TERRAIN_TYPE_TRACK, "TERRAIN_TYPE_TRACK" },
 		{ TERRAIN_TYPE_RAIL, "TERRAIN_TYPE_RAIL" },
		{ TERRAIN_TYPE_WALL_TOP, "TERRAIN_TYPE_WALL_TOP" },
		{ TERRAIN_TYPE_HEDGE_TOP, "TERRAIN_TYPE_HEDGE_TOP" },
 		{ TERRAIN_TYPE_FOREST_TOP, "TERRAIN_TYPE_FOREST_TOP" },
		{ TEMP_TERRAIN_TYPE_FRINGE, "TEMP_TERRAIN_TYPE_FRINGE" },
		{ TEMP_TERRAIN_TYPE_POWER_LINE, "TEMP_TERRAIN_TYPE_POWER_LINE" },
		{ TEMP_TERRAIN_TYPE_TELEPHONE_LINE, "TEMP_TERRAIN_TYPE_TELEPHONE_LINE" },
		{ TEMP_TERRAIN_TYPE_SEA_BANK, "TEMP_TERRAIN_TYPE_SEA_BANK" },
		{ TEMP_TERRAIN_TYPE_COASTAL_RIVER, "TEMP_TERRAIN_TYPE_COASTAL_RIVER" },
		{ TEMP_TERRAIN_TYPE_BEACH_MID, "TEMP_TERRAIN_TYPE_BEACH_MID" },
 		{ TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK3, "TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK3" },
 		{ TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK5, "TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK5" },
 		{ TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK7, "TEMP_TERRAIN_TYPE_STEPPED_RIVER_BANK7" },
 		{ TEMP_TERRAIN_TYPE_LAKE, "TEMP_TERRAIN_TYPE_LAKE" },
 		{ TEMP_TERRAIN_TYPE_FOREST_SIDE_X, "TEMP_TERRAIN_TYPE_FOREST_SIDE_X" },
 		{ TEMP_TERRAIN_TYPE_FOREST_SIDE_Z, "TEMP_TERRAIN_TYPE_FOREST_SIDE_Z" },
 		{ TEMP_TERRAIN_TYPE_OFFROAD, "TEMP_TERRAIN_TYPE_OFFROAD" },
 		{ TEMP_TERRAIN_TYPE_POLITICAL_BOUNDARY, "TEMP_TERRAIN_TYPE_POLITICAL_BOUNDARY" },
 		{ TEMP_TERRAIN_TYPE_BUILT_UP_AREA_BANK, "TEMP_TERRAIN_TYPE_BUILT_UP_AREA_BANK" },
		{ TERRAIN_TYPE_LAST, "TERRAIN_TYPE_LAST" },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_terrain_type_name ( terrain_types type )
{

	int
		count,
		elements;

	elements = sizeof ( terrain_type_names ) / sizeof ( terrain_type_name );

	for ( count = 0; count < elements; count++ )
	{

		if ( terrain_type_names[count].type == type )
		{

			return ( terrain_type_names[count].name );
		}
	}

	return ( terrain_type_names[0].name );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Xhit: added to get surface_type for downwash effect. (030328)
int get_terrain_surface_type ( terrain_types type )
{
	return ( terrain_type_information [type].surface_type ) ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_all_custom_terrain_types ( void )
{

	 	terrain_texture_sea_detail								= get_system_texture_index ( "TERRAIN_SEA_1" );
		terrain_texture_beach_detail							= get_system_texture_index ( "TERRAIN_BEACH" );
		terrain_texture_land_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
		terrain_texture_altered_land1_detail				= get_system_texture_index ( "TERRAIN_SCRUB" );
		terrain_texture_altered_land2_detail				= get_system_texture_index ( "TERRAIN_BARE_ROCK2" );
		terrain_texture_altered_land3_detail				= get_system_texture_index ( "TERRAIN_SNOW" );

		terrain_texture_forest_detail							= get_system_texture_index ( "TERRAIN_TREE_CANOPY_1" );
		terrain_texture_forest_top_detail					= get_system_texture_index ( "TERRAIN_TREE_CANOPY_LEBANON" );
		terrain_texture_forest_middle_detail				= get_system_texture_index ( "TERRAIN_SWAMP2" );
		terrain_texture_forest_bottom_detail				= get_system_texture_index ( "TERRAIN_SWAMP1" );

		terrain_texture_builtup_area1_detail				= get_system_texture_index ( "TERRAIN_GRG_CITY4" );
		terrain_texture_builtup_area2_detail				= get_system_texture_index ( "TERRAIN_GRG_CITY3" );
		terrain_texture_builtup_area3_detail				= get_system_texture_index ( "TERRAIN_GRG_CITY2" );
		terrain_texture_builtup_area4_detail				= get_system_texture_index ( "TERRAIN_GRG_CITY1" );
		terrain_texture_builtup_area1_infrared_detail	= get_system_texture_index ( "TERRAIN_BW_CITY4" );
		terrain_texture_builtup_area2_infrared_detail	= get_system_texture_index ( "TERRAIN_BW_CITY3" );
		terrain_texture_builtup_area3_infrared_detail	= get_system_texture_index ( "TERRAIN_BW_CITY2" );
		terrain_texture_builtup_area4_infrared_detail	= get_system_texture_index ( "TERRAIN_BW_CITY1" );

		terrain_texture_road_detail							= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
		terrain_texture_road_bank_detail						= get_system_texture_index ( "TERRAIN_DETAIL_LEBANON" );
		terrain_texture_track_detail							= get_system_texture_index ( "TERRAIN_THAI_TRACK" );

		terrain_texture_river_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
		terrain_texture_river_bank_detail					= get_system_texture_index ( "TERRAIN_HIGHLAND" );
		terrain_texture_reservoir_detail						= get_system_texture_index ( "TERRAIN_THAILAND_RIVER" );
		terrain_texture_trench_detail							= get_system_texture_index ( "CH_TERRAIN_DRY_MUD1");
		
		terrain_texture_field1_detail							= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
		terrain_texture_field2_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
		terrain_texture_field3_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
		terrain_texture_field4_detail							= get_system_texture_index ( "TERRAIN_CORNFIELD" );
		terrain_texture_field5_detail							= get_system_texture_index ( "TERRAIN_WHEATFIELD" );
		terrain_texture_field6_detail							= get_system_texture_index ( "TERRAIN_LIGHTGREENFIELD" );
		terrain_texture_field7_detail							= get_system_texture_index ( "TERRAIN_DARKGREENFIELD" );
		terrain_texture_field8_detail							= get_system_texture_index ( "TERRAIN_MUSTARDFIELD" );
		terrain_texture_field9_detail							= get_system_texture_index ( "TERRAIN_PLOUGHED1FIELD" );
		terrain_texture_field10_detail						= get_system_texture_index ( "TERRAIN_PLOUGHED2FIELD" );
		terrain_texture_field11_detail						= get_system_texture_index ( "TERRAIN_CORNFIELD" );

		terrain_texture_hedge_detail							= get_system_texture_index ( "TERRAIN_WALL_LEBANON" );
		terrain_texture_wall_detail							= get_system_texture_index ( "TERRAIN_WALL" );
		terrain_texture_trench_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
			
		terrain_texture_sea_colour_pass						= terrain_texture_sea_detail;
		terrain_texture_beach_colour_pass					= terrain_texture_beach_detail;
		terrain_texture_land_colour_pass						= terrain_texture_land_detail;
		terrain_texture_forest_colour_pass					= terrain_texture_forest_detail;
		terrain_texture_forest_bottom_colour_pass			= terrain_texture_forest_bottom_detail;
		terrain_texture_forest_middle_colour_pass			= terrain_texture_forest_middle_detail;
		terrain_texture_forest_top_colour_pass				= terrain_texture_forest_top_detail;

		terrain_texture_builtup_area1_colour_pass				= terrain_texture_builtup_area1_detail;
		terrain_texture_builtup_area2_colour_pass				= terrain_texture_builtup_area2_detail;
		terrain_texture_builtup_area3_colour_pass				= terrain_texture_builtup_area3_detail;
		terrain_texture_builtup_area4_colour_pass				= terrain_texture_builtup_area4_detail;
		terrain_texture_builtup_area1_infrared_colour_pass	= terrain_texture_builtup_area1_infrared_detail;
		terrain_texture_builtup_area2_infrared_colour_pass	= terrain_texture_builtup_area2_infrared_detail;
		terrain_texture_builtup_area3_infrared_colour_pass	= terrain_texture_builtup_area3_infrared_detail;
		terrain_texture_builtup_area4_infrared_colour_pass	= terrain_texture_builtup_area4_infrared_detail;

		terrain_texture_road_colour_pass							= terrain_texture_road_detail;
		terrain_texture_track_colour_pass						= terrain_texture_track_detail;
		terrain_texture_river_colour_pass						= terrain_texture_river_detail;
		terrain_texture_reservoir_colour_pass					= terrain_texture_reservoir_detail;

		terrain_texture_road_bank_colour_pass					= terrain_texture_road_bank_detail;
		terrain_texture_river_bank_colour_pass					= terrain_texture_river_bank_detail;
		terrain_texture_trench_colour_pass						= terrain_texture_trench_detail;

		terrain_texture_field1_colour_pass						= terrain_texture_field1_detail;
		terrain_texture_field2_colour_pass						= terrain_texture_field2_detail;
		terrain_texture_field3_colour_pass						= terrain_texture_field3_detail;
		terrain_texture_field4_colour_pass						= terrain_texture_field4_detail;
		terrain_texture_field5_colour_pass						= terrain_texture_field5_detail;
		terrain_texture_field6_colour_pass						= terrain_texture_field6_detail;
		terrain_texture_field7_colour_pass						= terrain_texture_field7_detail;
		terrain_texture_field8_colour_pass						= terrain_texture_field8_detail;
		terrain_texture_field9_colour_pass						= terrain_texture_field9_detail;
		terrain_texture_field10_colour_pass						= terrain_texture_field10_detail;
		terrain_texture_field11_colour_pass						= terrain_texture_field11_detail;

		terrain_texture_altered_land1_colour_pass				= terrain_texture_altered_land1_detail;
		terrain_texture_altered_land2_colour_pass				= terrain_texture_altered_land2_detail;
		terrain_texture_altered_land3_colour_pass				= terrain_texture_altered_land3_detail;

		terrain_texture_hedge_colour_pass						= terrain_texture_hedge_detail;
		terrain_texture_wall_colour_pass							= terrain_texture_wall_detail;
		terrain_texture_trench_colour_pass						= terrain_texture_trench_detail;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 051007 for Maverick, add user maps in terrain display ==>
void initialise_3d_alaska_terrain_types ( void )
{

	float
		contour_heights[] =
		{

			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1750,
			2600,
			3700,
		};

	int
		reflection_texture_index;

	set_3d_rain_special_snow_flag ( TRUE ); //????

	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );

	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_HIGHLAND" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SWAMP" );

	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_WALL" );      //TERRAIN_THAI_TRACK" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_river_colour_pass						= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_reservoir_colour_pass					= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_YEMEN_GRITTY" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_SCRUB" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_MOUNTAINS" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_BARE_ROCK2" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_SNOW" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SNOW" );

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SOIL;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_road										= SURFACE_TYPE_ASPHALT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land2							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land3							= SURFACE_TYPE_SOIL;
	terrain_surface_hedge									= SURFACE_TYPE_SOIL;
	terrain_surface_wall										= SURFACE_TYPE_ROCK;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DEFAULT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_aleut_terrain_types ( void )
{

	float
		contour_heights[] =
		{
			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1500,
			3000,
			5000,
		};

	int
		reflection_texture_index;

	set_3d_rain_special_snow_flag ( TRUE ); //????

	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );

	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_HIGHLAND" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SWAMP" );

	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_WALL" );      //TERRAIN_THAI_TRACK" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_river_colour_pass						= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_reservoir_colour_pass					= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_YEMEN_GRITTY" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_SCRUB" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_MOUNTAINS" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_BARE_ROCK2" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_SNOW" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SNOW" );

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SOIL;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_road										= SURFACE_TYPE_ASPHALT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land2							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land3							= SURFACE_TYPE_SOIL;
	terrain_surface_hedge									= SURFACE_TYPE_SOIL;
	terrain_surface_wall										= SURFACE_TYPE_ROCK;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DEFAULT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_kuwait_terrain_types ( void )
{

	float
		contour_heights[] =
		{
			-1000,
			-0.0001,
			250,
			500,
			750,
			1000,
			1250,
			1500,
			2000,
		};

	int
		reflection_texture_index;

	set_3d_rain_special_snow_flag ( FALSE ); //????

	terrain_texture_sea_detail									= get_system_texture_index ( "TERRAIN_SEA_1" );
	terrain_texture_sea_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_beach_detail								= get_system_texture_index ( "TERRAIN_BEACH" );
	terrain_texture_beach_colour_pass						= get_system_texture_index ( "COLOUR_PASS_LEBANON" );

	terrain_texture_land_detail								= get_system_texture_index ( "TERRAIN_HIGHLAND" );
	terrain_texture_land_colour_pass							= get_system_texture_index ( "COLOUR_PASS_SWAMP" );

	terrain_texture_road_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_road_colour_pass							= get_system_texture_index ( "COLOUR_PASS_WALL" );      //TERRAIN_THAI_TRACK" );
	terrain_texture_track_detail								= get_system_texture_index ( "TERRAIN_DETAIL_ROAD" );
	terrain_texture_track_colour_pass						= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_detail								= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_river_colour_pass						= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_reservoir_detail							= get_system_texture_index ( "TERRAIN_RIVER" );
	terrain_texture_reservoir_colour_pass					= get_system_texture_index ( "COLOUR_PASS_SEA_LEBANON" );
	terrain_texture_road_bank_detail							= get_system_texture_index ( "TERRAIN_DETAIL_4" );
	terrain_texture_road_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_river_bank_detail						= get_system_texture_index ( "TERRAIN_YEMEN_GRITTY" );
	terrain_texture_river_bank_colour_pass					= get_system_texture_index ( "COLOUR_PASS_YEMEN_BAKED2" );
	terrain_texture_altered_land1_detail					= get_system_texture_index ( "TERRAIN_SCRUB" );
	terrain_texture_altered_land1_colour_pass				= get_system_texture_index ( "COLOUR_PASS_MOUNTAINS" );
	terrain_texture_altered_land2_detail					= get_system_texture_index ( "TERRAIN_BARE_ROCK2" );
	terrain_texture_altered_land2_colour_pass				= get_system_texture_index ( "COLOUR_PASS_ROCK" );
	terrain_texture_altered_land3_detail					= get_system_texture_index ( "TERRAIN_SNOW" );
	terrain_texture_altered_land3_colour_pass				= get_system_texture_index ( "COLOUR_PASS_SNOW" );

	//VJ 050303 texture colour mod: use texture colour directly instead of brownish haze
	if (command_line_texture_colour == 1)
		initialise_all_custom_terrain_types ();

	// Xhit: the surface types for the various terrain types are set according to the surroundings. (030328)
	terrain_surface_sea										= SURFACE_TYPE_WATER;
	terrain_surface_beach									= SURFACE_TYPE_SAND;
	terrain_surface_land										= SURFACE_TYPE_SOIL;
	terrain_surface_forest									= SURFACE_TYPE_NONE;
	terrain_surface_builtup_area1							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4							= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area1_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area2_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area3_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_builtup_area4_infrared				= SURFACE_TYPE_ASPHALT;
	terrain_surface_road										= SURFACE_TYPE_ASPHALT;
	terrain_surface_track									= SURFACE_TYPE_SOIL;
	terrain_surface_river									= SURFACE_TYPE_WATER;
	terrain_surface_reservoir								= SURFACE_TYPE_WATER;
	terrain_surface_rail										= SURFACE_TYPE_SOIL;
	terrain_surface_road_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_river_bank								= SURFACE_TYPE_SAND;
	terrain_surface_rail_bank								= SURFACE_TYPE_SOIL;
	terrain_surface_field1									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field2									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field3									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field4									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field5									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field6									= SURFACE_TYPE_SOIL;
	terrain_surface_field7									= SURFACE_TYPE_SOIL;
	terrain_surface_field8									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field9									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_field10									= SURFACE_TYPE_FIELD_DARKBROWN;
	terrain_surface_field11									= SURFACE_TYPE_FIELD_LIGHTBROWN;
	terrain_surface_altered_land1							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land2							= SURFACE_TYPE_SOIL;
	terrain_surface_altered_land3							= SURFACE_TYPE_SOIL;
	terrain_surface_hedge									= SURFACE_TYPE_SOIL;
	terrain_surface_wall										= SURFACE_TYPE_ROCK;
	terrain_surface_trench									= SURFACE_TYPE_WATER;

	set_object_3d_texture_camoflage_by_name ( "DEFAULT" );

	reflection_texture_index = get_system_texture_index ( "ENVIRO_YEMEN_SMALL" );

	if ( reflection_texture_index != -1 )
	{

		set_object_3d_reflection_texture_map ( reflection_texture_index );
	}

	set_2d_terrain_contour_heights ( sizeof ( contour_heights ) / sizeof ( float ), contour_heights );
}
//VJ 051007 <===
