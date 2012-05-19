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
// VJ 050108: Gotcha: 3d cockpit mod
// this code is very very messy and full of commented out stuff. Just ignore
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_WIDEVIEW 0



#define DEBUG_MODULE 0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BASE_DX  0
#define BASE_DY  0.200
#define BASE_DZ  0.200

#define _DY 0.03

static int subnr;
static float dx, dy, dz;


static rgb_alpha_masked_sprite_data
	sprite_values;

#define draw_lamp(FLAG,X,Y,U,V,WIDTH,HEIGHT,MASK)										\
{																										\
	if ((FLAG))																						\
	{																									\
		sprite_values.x =(int) (X);													\
		sprite_values.y =(int) (Y);													\
		sprite_values.u =(int) (U);																	\
		sprite_values.v =(int) (V);																	\
		sprite_values.width = (int)(WIDTH);														\
		sprite_values.height = (int)(HEIGHT);														\
		sprite_values.mask_value = (unsigned char)(MASK);													\
																										\
		blit_rgb_alpha_masked_sprite (sprite_data, mask_data, &sprite_values);	\
	}																									\
}

#define LAMP1_WINDOW_X_MIN				(-1.0)
#define LAMP1_WINDOW_Y_MIN				(-1.0)
#define LAMP1_WINDOW_X_MAX				(0.999)
#define LAMP1_WINDOW_Y_MAX				(0.999)

#define LAMP1_VIEWPORT_SMALL_SIZE		(128)
#define LAMP1_VIEWPORT_LARGE_SIZE		(331)

#define LAMP1_TEXTURE_SIZE				(128)

#define LAMP1_VIEWPORT_TEXTURE_X_ORG	(LAMP1_TEXTURE_SIZE / 2)
#define LAMP1_VIEWPORT_TEXTURE_Y_ORG	(LAMP1_TEXTURE_SIZE / 2)

static object_3d_instance
	*virtual_cockpit_level1_inst3d,
	*virtual_cockpit_level2_inst3d,
	*virtual_cockpit_level3_inst3d,
	*virtual_cockpit_fillet_level1_inst3d,
	*virtual_cockpit_fillet_level2_inst3d,
	*virtual_cockpit_fillet_level3_inst3d,
	*virtual_cockpit_main_rotor_inst3d,
	*virtual_cockpit_adi_inst3d,
	*virtual_cockpit_large_adi_inst3d,
	*virtual_cockpit_compass_inst3d,
	*virtual_cockpit_instrument_needles_inst3d,
	*virtual_cockpit_instrument_large_needles_inst3d,
	*virtual_cockpit_upfront_display_inst3d,
	*virtual_cockpit_lhs_mfd_inst3d,
	*virtual_cockpit_rhs_mfd_inst3d,
	*virtual_cockpit_display_view_mfd_inst3d;

static env_2d
	*lamp1_env;

static screen
	*lamp1_texture_screen;//,	*Lamp1_overlaid_texture_screen;

static float
	lamp1_viewport_size,
	lamp1_viewport_x_org,
	lamp1_viewport_y_org,
	lamp1_viewport_x_min,
	lamp1_viewport_y_min,
	lamp1_viewport_x_max,
	lamp1_viewport_y_max;

void get_apache_crew_viewpoint (int index, object_3d_instance   *virtual_cockpit_inst3d);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_virtual_cockpit_3d (void)
{
	//
	// 3D instances
	//

	virtual_cockpit_inst3d = NULL;

	pilot_head_pitch_datum = 0.0;
//VJ#
	co_pilot_head_pitch_datum = 0.0;

//C:\gms\Razorworks\eech-new\modules\3d\3dobjdb.c
	virtual_cockpit_level1_inst3d = construct_3d_object (OBJECT_3D_AH64D_APACHE_LONGBOW);

	virtual_cockpit_level2_inst3d = construct_3d_object (OBJECT_3D_AH64D_APACHE_LONGBOW);

	virtual_cockpit_level3_inst3d = construct_3d_object (OBJECT_3D_AH64D_APACHE_LONGBOW);

	virtual_cockpit_fillet_level1_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL1_FILLET);

	virtual_cockpit_fillet_level2_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL2_FILLET);

	virtual_cockpit_fillet_level3_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL3_FILLET);

	virtual_cockpit_main_rotor_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_MAIN_ROTOR);

	virtual_cockpit_adi_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_ADI);

	virtual_cockpit_large_adi_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_LARGE_ADI);

	virtual_cockpit_compass_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_COMPASS);

	virtual_cockpit_instrument_needles_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_NEEDLES);

	virtual_cockpit_instrument_large_needles_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_LARGE_NEEDLES);

	virtual_cockpit_upfront_display_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_DISPLAYS_UPFRONT);

	virtual_cockpit_lhs_mfd_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_DISPLAYS_LHS_MFD);

	virtual_cockpit_rhs_mfd_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_DISPLAYS_RHS_MFD);

	virtual_cockpit_display_view_mfd_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_MFD_DISPLAYS_NEW);

	//
	// wipers and rain
	//

	initialise_apache_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();

//VJ wideview mod, date: 18-mar-03
	wide_cockpit_nr = WIDEVIEW_APACHE_PILOT;

//VJ wideview mod, date: 20-mar-03
//start up in normal view because when you switch to wideview the parameters are read
   set_global_wide_cockpit(FALSE);
   edit_wide_cockpit = FALSE;

	subnr = 0;
	dx = 0; dy = 0; dz = 0;

//  initialise_apache_lamp_screen ();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_cockpit_lighting (matrix3x3 attitude)
{
	matrix3x3
		directional_light_rotation,
		result;

	vec3d
		directional_light_direction;

	light_colour
		ambient_light_colour,
		directional_light_colour;

	float
		directional_light_heading,
		directional_light_pitch,
		directional_light_roll;


	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAWN:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.0;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAY:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 1.0;
			directional_light_colour.blue			= 1.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-40.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DUSK:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.0;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_NIGHT:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.0;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
	}

	#if DEMO_VERSION

	ambient_light_colour.red		 		= 0.0;
	ambient_light_colour.green		  		= 0.0;
	ambient_light_colour.blue		  		= 0.0;

	directional_light_colour.red			= 1.0;
	directional_light_colour.green		= 1.0;
	directional_light_colour.blue			= 1.0;

	directional_light_heading 				= rad (0.0);
	directional_light_pitch 				= rad (-40.0);
	directional_light_roll 					= rad (0.0);

	#endif

	set_3d_ambient_light (main_3d_single_light_env, &ambient_light_colour);

	get_3d_transformation_matrix (directional_light_rotation, directional_light_heading, directional_light_pitch, directional_light_roll);

	multiply_matrix3x3_matrix3x3 (result, directional_light_rotation, attitude);

	directional_light_direction.x = -result[2][0];
	directional_light_direction.y = -result[2][1];
	directional_light_direction.z = -result[2][2];

	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &directional_light_direction, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_cockpit_white_lighting (matrix3x3 attitude)
{
	matrix3x3
		directional_light_rotation,
		result;

	vec3d
		directional_light_direction;

	light_colour
		ambient_light_colour,
		directional_light_colour;

	float
		directional_light_heading,
		directional_light_pitch,
		directional_light_roll;

	ambient_light_colour.red		 	= 0.0;
	ambient_light_colour.green		  	= 0.0;
	ambient_light_colour.blue		  	= 0.0;

	directional_light_colour.red		= 1.0;
	directional_light_colour.green	= 1.0;
	directional_light_colour.blue		= 1.0;

	directional_light_heading 			= rad (0.0);
	directional_light_pitch 			= rad (-40.0);
	directional_light_roll 				= rad (0.0);

	set_3d_ambient_light (main_3d_single_light_env, &ambient_light_colour);

	get_3d_transformation_matrix (directional_light_rotation, directional_light_heading, directional_light_pitch, directional_light_roll);

	multiply_matrix3x3_matrix3x3 (result, directional_light_rotation, attitude);

	directional_light_direction.x = -result[2][0];
	directional_light_direction.y = -result[2][1];
	directional_light_direction.z = -result[2][2];

	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &directional_light_direction, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///vj draws internal cockpit, dashboad, dials including frame/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_internal_virtual_cockpit_3d (unsigned int flags)
{

	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*virtual_cockpit_inst3d;


//#ifndef DEBUG_WIDEVIEW
   set_global_wide_cockpit(FALSE);
   edit_wide_cockpit = FALSE;
//#endif
	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	vp.x = 0.0;
	vp.y = 0.0;
	vp.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);

	////////////////////////////////////////
	//
	// render displays onto textures (before draw 3D scenes)
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_UPFRONT_DISPLAY)
	{
		draw_apache_upfront_display_on_texture ();
	}

	if (flags & VIRTUAL_COCKPIT_LHS_MFD_DISPLAY)
	{
		draw_apache_mfd_on_texture (MFD_LOCATION_LHS);
	}

	if (flags & VIRTUAL_COCKPIT_RHS_MFD_DISPLAY)
	{
		draw_apache_mfd_on_texture (MFD_LOCATION_RHS);
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_COCKPIT))
	{
		set_cockpit_white_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// virtual cockpit
			//

			if (flags & VIRTUAL_COCKPIT_COCKPIT)
			{
				switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
				{
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAWN:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAY:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DUSK:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_NIGHT:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level3_inst3d;

						break;
					}
				}

				#if DEMO_VERSION

				virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

				#endif

//VJ 28 is the subobject number of the pilot
				get_apache_crew_viewpoint (28, virtual_cockpit_inst3d);

			   virtual_cockpit_inst3d->vp.x += BASE_DX;
			   virtual_cockpit_inst3d->vp.y += BASE_DY;
			   virtual_cockpit_inst3d->vp.z += BASE_DZ;

	   		if (get_global_wide_cockpit ())
				{
				   virtual_cockpit_inst3d->vp.x += wide_cockpit_position[wide_cockpit_nr].c.x;
				   virtual_cockpit_inst3d->vp.y += wide_cockpit_position[wide_cockpit_nr].c.y;
				   virtual_cockpit_inst3d->vp.z += wide_cockpit_position[wide_cockpit_nr].c.z;
					//VJ 050207 included head pitch in fixed view setting
					pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].c.p );
				}

//use subnr to eliminate each sub_object one by one, in edit_wide_view press the end key
//				virtual_cockpit_inst3d->sub_objects[subnr].visible_object = FALSE;

				//rotor
				virtual_cockpit_inst3d->sub_objects[1].visible_object = FALSE;
				//pilots (28 is back, 29 is front)
				virtual_cockpit_inst3d->sub_objects[28].visible_object = FALSE;
				virtual_cockpit_inst3d->sub_objects[29].visible_object = FALSE;
				//wipers
				virtual_cockpit_inst3d->sub_objects[37].visible_object = FALSE;

			// don't do this because it mersses up change smade to virtual_cockpit_inst3d
			//	memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);
			}

			//C:\gms\Razorworks\eech-new\modules\3d\3dobjbuf.c
			draw_3d_scene ();

			print_edit_wide_cockpit ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES | VIRTUAL_COCKPIT_INSTRUMENT_LARGE_NEEDLES))
	{
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

//VJ#
		/*
		vp.x = wide_cockpit_position[wide_cockpit_nr].c.x;
		vp.y = wide_cockpit_position[wide_cockpit_nr].c.y;
		vp.z = wide_cockpit_position[wide_cockpit_nr].c.z;
		vp.x += dx;
		vp.y += dy;
		vp.z += dz;
		*/
		vp.x = BASE_DX;
		vp.y = BASE_DY - 0.0800;
		vp.z = BASE_DZ;

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// instrument needles
			//

			if (flags & VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES)
			{
				//
				// ADI slip
				//

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_ADI_SIDE_SLIP;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_roll = get_apache_virtual_cockpit_adi_slip_indicator_needle_value ();
				}

				//
				// airspeed
				//

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_AIRSPEED;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = draw_virtual_cockpit_needles_on_fixed_cockpits;

					search.result_sub_object->relative_roll = get_apache_virtual_cockpit_airspeed_indicator_needle_value ();
				}

				//
				// altimeter
				//

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_ALTIMETER;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = draw_virtual_cockpit_needles_on_fixed_cockpits;

					search.result_sub_object->relative_roll = get_apache_virtual_cockpit_barometric_altimeter_needle_value ();
				}

				//
				// clock
				//

				{
					float
						hours,
						minutes,
						seconds;

					//
					// only read clock values if drawing virtual cockpit needles to prevent speeding up clock debug values
					//

					if (draw_virtual_cockpit_needles_on_fixed_cockpits)
					{
						get_apache_virtual_cockpit_clock_hand_values (&hours, &minutes, &seconds);
					}
					else
					{
						hours = 0.0;
						minutes = 0.0;
						seconds = 0.0;
					}

					//
					// hour hand
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_instrument_needles_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_CLOCK_HOUR_HAND;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->visible_object = draw_virtual_cockpit_needles_on_fixed_cockpits;

						search.result_sub_object->relative_roll = hours;
					}

					//
					// minute hand
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_instrument_needles_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_CLOCK_MINUTE_HAND;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->visible_object = draw_virtual_cockpit_needles_on_fixed_cockpits;

						search.result_sub_object->relative_roll = minutes;
					}

					//
					// second hand
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_instrument_needles_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_CLOCK_SECOND_HAND;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->visible_object = draw_virtual_cockpit_needles_on_fixed_cockpits;

						search.result_sub_object->relative_roll = seconds;
					}
				}

				memcpy (&virtual_cockpit_instrument_needles_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_instrument_needles_inst3d->vp.position, virtual_cockpit_instrument_needles_inst3d);
			}

			//
			// instrument large needles
			//

			if (flags & VIRTUAL_COCKPIT_INSTRUMENT_LARGE_NEEDLES)
			{
				//
				// ADI slip
				//

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_large_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_ADI_SIDE_SLIP;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_roll = get_apache_virtual_cockpit_adi_slip_indicator_needle_value ();
				}

				//
				// airspeed
				//

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_large_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_AIRSPEED;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_roll = get_apache_virtual_cockpit_airspeed_indicator_needle_value ();
				}

				memcpy (&virtual_cockpit_instrument_large_needles_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_instrument_large_needles_inst3d->vp.position, virtual_cockpit_instrument_large_needles_inst3d);
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

	if
	(
		(flags & VIRTUAL_COCKPIT_DISPLAY_VIEW) &&
		(flags & VIRTUAL_COCKPIT_LHS_MFD_DISPLAY) &&
		(flags & VIRTUAL_COCKPIT_RHS_MFD_DISPLAY)
	)
	{
		set_3d_active_environment (main_3d_env);

		set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// lhs mfd
			//

			memcpy (&virtual_cockpit_display_view_mfd_inst3d->vp, &vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_display_view_mfd_inst3d->vp.position, virtual_cockpit_display_view_mfd_inst3d);

			//
			// rhs mfd
			//

			memcpy (&virtual_cockpit_display_view_mfd_inst3d->vp, &vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_display_view_mfd_inst3d->vp.position, virtual_cockpit_display_view_mfd_inst3d);

			draw_3d_scene ();

			end_3d_scene ();
		}
	}
	else
	{
		if (flags & (VIRTUAL_COCKPIT_UPFRONT_DISPLAY | VIRTUAL_COCKPIT_LHS_MFD_DISPLAY | VIRTUAL_COCKPIT_RHS_MFD_DISPLAY))
		{
			set_3d_active_environment (main_3d_env);

			set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

			realise_3d_clip_extents (main_3d_env);

			recalculate_3d_environment_settings (main_3d_env);

			clear_zbuffer_screen ();

//		vp.x = wide_cockpit_position[wide_cockpit_nr].c.x;
//		vp.y = wide_cockpit_position[wide_cockpit_nr].c.y;
//		vp.z = wide_cockpit_position[wide_cockpit_nr].c.z;

			if (begin_3d_scene ())
			{
				//
				// up-front display
				//

				vp.y = BASE_DY - 0.0800 - _DY;

				if (flags & VIRTUAL_COCKPIT_UPFRONT_DISPLAY)
				{
					vp.y -= 0.01;
					memcpy (&virtual_cockpit_upfront_display_inst3d->vp, &vp, sizeof (viewpoint));
					vp.y += 0.01;
//					virtual_cockpit_upfront_display_inst3d->vp.position.y = dy;

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_upfront_display_inst3d->vp.position, virtual_cockpit_upfront_display_inst3d);
				}

				//
				// lhs mfd
				//

				if (flags & VIRTUAL_COCKPIT_LHS_MFD_DISPLAY)
				{
					memcpy (&virtual_cockpit_lhs_mfd_inst3d->vp, &vp, sizeof (viewpoint));
					//virtual_cockpit_lhs_mfd_inst3d->vp.position.x += dx;
					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_lhs_mfd_inst3d->vp.position, virtual_cockpit_lhs_mfd_inst3d);
				}

				//
				// rhs mfd
				//

				if (flags & VIRTUAL_COCKPIT_RHS_MFD_DISPLAY)
				{
					memcpy (&virtual_cockpit_rhs_mfd_inst3d->vp, &vp, sizeof (viewpoint));

					//virtual_cockpit_rhs_mfd_inst3d->vp.position.x -= dx;

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_rhs_mfd_inst3d->vp.position, virtual_cockpit_rhs_mfd_inst3d);
				}

				draw_3d_scene ();

				end_3d_scene ();
			}
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	//
	// draw fillet to mask TADS display
	//

	if
	(
		(d3d_can_render_to_texture) &&
		(flags & (VIRTUAL_COCKPIT_COCKPIT)) &&
		(flags & (VIRTUAL_COCKPIT_LHS_MFD_DISPLAY)) &&
		(flags & (VIRTUAL_COCKPIT_RHS_MFD_DISPLAY))
	)
	{
		set_cockpit_white_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
			{
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DAWN:
				////////////////////////////////////////
				{

					virtual_cockpit_inst3d = virtual_cockpit_fillet_level2_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DAY:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level1_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DUSK:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level2_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_NIGHT:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level3_inst3d;

					break;
				}
			}

			#if DEMO_VERSION

			virtual_cockpit_inst3d = virtual_cockpit_fillet_level1_inst3d;

			#endif
//VJ#
			vp.x = BASE_DX;
			vp.y = BASE_DY - 0.086 - _DY;
			vp.z = BASE_DZ-0.010;

			memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			draw_3d_scene ();

			end_3d_scene ();
		}
	}


	//draw_apache_indicator_lamps_3d ();
	//draw_apache_lamp_on_texture ();

	//VJ wideview mod, date: 18-mar-03
#if DEBUG_WIDEVIEW
	if (edit_wide_cockpit)
	{
		if (check_key(DIK_NUMPAD7))
		{
			system_sleep(20);
			  dy+= 0.002;
		}
		if (check_key(DIK_NUMPAD9))
		{
			system_sleep(20);
			  dy-= 0.002;
		}
		if (check_key(DIK_NUMPADSLASH))
		{
			system_sleep(20);
			  dx+= 0.002;
		}
		if (check_key(DIK_NUMPADSTAR))
		{
			system_sleep(20);
			  dx-= 0.002;
		}
		if (check_key(DIK_NUMPADMINUS))
		{
			system_sleep(20);
			  dz+= 0.002;
		}
		if (check_key(DIK_NUMPADPLUS))
		{
			system_sleep(20);
			  dz-= 0.002;
		}
		if (check_key(DIK_END))
		{
			system_sleep (100);
				subnr++;
	   }
		if (check_key(DIK_NUMPAD0))
		{
				dx = 0;
				dy = 0;
				dz = 0;
		}
	}
#endif

	move_edit_wide_cockpit ();

	////////////////////////////////////////
	//
	// tidy up
	//
	////////////////////////////////////////

	#if RECOGNITION_GUIDE

	set_3d_view_distances (main_3d_env, 10000.0, 100.0, 1.0, 0.0);

	#else

	set_3d_view_distances (main_3d_env, 10000.0, 1.0, 1.0, 0.0);

	#endif

	realise_3d_clip_extents (main_3d_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_external_virtual_cockpit_3d (unsigned int flags)
{
	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	float
		theta;

	object_3d_instance
		*inst3d;

	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

//NO wideview for 3d cockpit
//#ifndef DEBUG_WIDEVIEW
	set_global_wide_cockpit(FALSE);
   edit_wide_cockpit = FALSE;

//#endif


		vp.x = 0.0;
		vp.y = 0.0;
		vp.z = 0.0;

		get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_MAIN_ROTOR | VIRTUAL_COCKPIT_STOWED_WIPER | VIRTUAL_COCKPIT_MOVING_WIPER))
	{
		set_3d_active_environment (main_3d_env);

		set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

/*
		vp.x += dx;
		vp.y += dy;
		vp.z += dz;
		  vp.x = wide_cockpit_position[wide_cockpit_nr].c.x;
		  vp.y = wide_cockpit_position[wide_cockpit_nr].c.y;
		  vp.z = wide_cockpit_position[wide_cockpit_nr].c.z;
*/
			vp.x = BASE_DX;
			vp.y = BASE_DY - 0.164;
			vp.z = BASE_DZ;

		if (begin_3d_scene ())
		{
			//
			// main rotor
			//

			if (flags & VIRTUAL_COCKPIT_MAIN_ROTOR)
			{
				if (!(get_helicopter_main_rotors_blurred (get_gunship_entity ()) && (!get_global_blurred_main_rotors_visible_from_cockpit ())))
				{
					if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_MAIN_ROTOR_DAMAGED))
					{
						animate_damaged_helicopter_main_rotors (get_gunship_entity (), TRUE);
					}
					else
					{
						animate_helicopter_main_rotors (get_gunship_entity (), TRUE, FALSE);
					}

					inst3d = (object_3d_instance *) get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

					theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

					set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

					animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

					memcpy (&virtual_cockpit_main_rotor_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_main_rotor_inst3d->vp.position, virtual_cockpit_main_rotor_inst3d);
				}
			}

			//
			// wiper
			//

			if (wiper_mode == WIPER_MODE_STOWED)
			{
				if (flags & VIRTUAL_COCKPIT_STOWED_WIPER)
				{
					draw_apache_virtual_cockpit_wiper (&vp);
				}
			}
			else
			{
				if (flags & VIRTUAL_COCKPIT_MOVING_WIPER)
				{
					draw_apache_virtual_cockpit_wiper (&vp);
				}
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_COMPASS | VIRTUAL_COCKPIT_ADI | VIRTUAL_COCKPIT_LARGE_ADI))
	{
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		vp.x = BASE_DX;
		vp.y = BASE_DY;
		vp.z = BASE_DZ-0.1;
/*
		vp.x = BASE_DX+dx;
		vp.y = BASE_DY+dy;
		vp.z = BASE_DZ+dz;

			vp.x = wide_cockpit_position[wide_cockpit_nr].c.x;
			vp.y = wide_cockpit_position[wide_cockpit_nr].c.y;
			vp.z = wide_cockpit_position[wide_cockpit_nr].c.z;
*/
//VJ#

		if (begin_3d_scene ())
		{
			//
			// compass
			//
			if (flags & VIRTUAL_COCKPIT_COMPASS)
			{
				search.search_depth = 0;
				search.search_object = virtual_cockpit_compass_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_COMPASS_HEADING_NULL;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
				}

				memcpy (&virtual_cockpit_compass_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_compass_inst3d->vp.position, virtual_cockpit_compass_inst3d);
			}

			//
			// ADI
			//
			/*
			  vp.x = wide_cockpit_position[wide_cockpit_nr].c.x;
			  vp.y = wide_cockpit_position[wide_cockpit_nr].c.y;
			  vp.z = wide_cockpit_position[wide_cockpit_nr].c.z;
			vp.x += 0.0;
			vp.y += 0.22;
			vp.z += 0.18;
*/


			if (flags & VIRTUAL_COCKPIT_ADI)
			{
				search.search_depth = 0;
				search.search_object = virtual_cockpit_adi_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_ADI;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						heading,
						pitch,
						roll;

					get_apache_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

					search.result_sub_object->relative_heading = -heading;

					search.result_sub_object->relative_pitch = pitch;

					search.result_sub_object->relative_roll = -roll;
				}

				memcpy (&virtual_cockpit_adi_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_adi_inst3d->vp.position, virtual_cockpit_adi_inst3d);
			}

			//
			// large ADI
			//

			if (flags & VIRTUAL_COCKPIT_LARGE_ADI)
			{
				search.search_depth = 0;
				search.search_object = virtual_cockpit_large_adi_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_ADI;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						heading,
						pitch,
						roll;

					get_apache_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

					search.result_sub_object->relative_heading = -heading;

					search.result_sub_object->relative_pitch = pitch;

					search.result_sub_object->relative_roll = -roll;
				}

				memcpy (&virtual_cockpit_large_adi_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_large_adi_inst3d->vp.position, virtual_cockpit_large_adi_inst3d);
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// rain effect
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_RAIN_EFFECT)
	{
		if (rain_mode != RAIN_MODE_DRY)
		{
			set_3d_active_environment (main_3d_env);

			set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

			realise_3d_clip_extents (main_3d_env);

			recalculate_3d_environment_settings (main_3d_env);

			clear_zbuffer_screen ();

			if (begin_3d_scene ())
			{
				draw_apache_virtual_cockpit_rain_effect (&vp);

				draw_3d_scene ();

				end_3d_scene ();
			}
		}
	}

	////////////////////////////////////////
	//
	// tidy up
	//
	////////////////////////////////////////

	#if RECOGNITION_GUIDE

	set_3d_view_distances (main_3d_env, 10000.0, 100.0, 1.0, 0.0);

	#else

	set_3d_view_distances (main_3d_env, 10000.0, 1.0, 1.0, 0.0);

	#endif

	realise_3d_clip_extents (main_3d_env);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_apache_crew_viewpoint (int index, object_3d_instance   *virtual_cockpit_inst3d)
{
	viewpoint
		vp;

	float
		head_pitch_datum;

	head_pitch_datum = pilot_head_pitch_datum;

	//
	// rotate head
	//

	virtual_cockpit_inst3d->sub_objects[index].relative_heading = -pilot_head_heading;
	virtual_cockpit_inst3d->sub_objects[index].relative_pitch = head_pitch_datum - pilot_head_pitch;
	virtual_cockpit_inst3d->sub_objects[index].relative_roll = 0.0;

	//
	// get viewpoint (avoid jitter)
	//

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	get_3d_sub_object_world_viewpoint (&virtual_cockpit_inst3d->sub_objects[index], &vp);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

// x,y,z is here north south east west!
//inserting fixed values here does not work because of head movement

	pilot_head_vp.x += vp.x;
	pilot_head_vp.y += vp.y;
	pilot_head_vp.z += vp.z;

	memcpy (pilot_head_vp.attitude, vp.attitude, sizeof (matrix3x3));

	vp.x = -vp.x;
	vp.y = -vp.y;
	vp.z = -vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, pilot_head_vp.attitude, &vp.position);


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_indicator_lamps_3d (void)
{
	unsigned char
		*sprite_data,
		*mask_data;

	int X_ORG;
	int Y_ORG;

	base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL1_BASE;

	sprite_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES);

	mask_data = get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_SPRITES_MASK);


//find out where the lamps are in 3d, tranform with pilot viewpoint, convert to pixels depending on resolution, use center of cockpit


	lock_screen (active_screen);

	X_ORG = 225;	Y_ORG = 470;
	X_ORG = (int)((virtual_cockpit_inst3d->vp.x*0.4+0.5)*300);
					 draw_lamp (apache_lamps.indicator_lamp_1, X_ORG +   7, Y_ORG +   4,   7,   4,  19,  19,   0);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_2, X_ORG +  27, Y_ORG +   4,  27,   4,  18,  19,  13);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_3, X_ORG +  47, Y_ORG +   5,  47,   5,  18,  18,  25);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_4, X_ORG +  66, Y_ORG +   5,  66,   5,  18,  18,  38);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_5, X_ORG +  86, Y_ORG +   5,  86,   5,  18,  18,  51);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_6, X_ORG + 106, Y_ORG +   5, 106,   5,  18,  18,  64);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_7, X_ORG + 125, Y_ORG +   5, 125,   5,  18,  18,  76);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_8, X_ORG + 144, Y_ORG +   5, 144,   5,  19,  18,  89);
	X_ORG += 20; draw_lamp (apache_lamps.indicator_lamp_9, X_ORG + 164, Y_ORG +   4, 164,   4,  19,  19, 102);

	X_ORG = 164;	Y_ORG = 408;
					 draw_lamp (apache_lamps.engine_1_fire	, X_ORG +  10, Y_ORG +  12,  10, 102,  26,  27,   0);
	X_ORG += 27; draw_lamp (apache_lamps.apu_fire		, X_ORG +  42, Y_ORG +  12,  42, 102,  26,  27,  13);
	X_ORG += 27; draw_lamp (apache_lamps.engine_2_fire	, X_ORG +  75, Y_ORG +  12,  75, 102,  26,  27,  25);

	X_ORG = 72;	Y_ORG = 375;
					 draw_lamp (apache_lamps.armament_lamp_1 , X_ORG +   9, Y_ORG +   7,   9, 327,  22,  23,   0);
	X_ORG += 23; draw_lamp (apache_lamps.armament_lamp_2 , X_ORG +  31, Y_ORG +   7,  31, 327,  22,  23,  13);

	X_ORG = 305;
	Y_ORG = 283;
					 draw_lamp (apache_lamps.mfd_lamp_1 , X_ORG +   3, Y_ORG +   3,   3, 183,  24,  22,   0);
	Y_ORG += 23; draw_lamp (apache_lamps.mfd_lamp_2 , X_ORG +   3, Y_ORG +  25,   3, 205,  24,  21,  13);

	unlock_screen (active_screen);

}

/*

#define draw_lamp(FLAG,X,Y,U,V,WIDTH,HEIGHT,MASK)										\
{																										\
	if ((FLAG))																						\
	{																									\
		sprite_values.x = int (X);													\
		sprite_values.y = (Y);													\
		sprite_values.u = (U);																	\
		sprite_values.v = (V);																	\
		sprite_values.width = (WIDTH);														\
		sprite_values.height = (HEIGHT);														\
		sprite_values.mask_value = (MASK);													\
																										\
		blit_rgb_alpha_masked_sprite (sprite_data, mask_data, &sprite_values);	\
	}																									\
}
*/



void initialise_apache_lamp_screen (void)
{

	lamp1_env = create_2d_environment ();

	lamp1_texture_screen = create_system_texture_screen (LAMP1_TEXTURE_SIZE, LAMP1_TEXTURE_SIZE, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD, TEXTURE_TYPE_SINGLEALPHA);

//	Lamp1_overlaid_texture_screen = create_system_texture_screen (LAMP1_TEXTURE_SIZE, LAMP1_TEXTURE_SIZE, LAMP1_OVERLAID_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

}

void deinitialise_apache_lamp_screen (void)
{
	destroy_2d_environment (lamp1_env);

	destroy_screen (lamp1_texture_screen);

//	destroy_screen (lamp1_overlaid_texture_screen);
}


void draw_apache_lamp_on_texture (void)
{
	screen
		*lamp_texture_screen;

	lamp_texture_screen = lamp1_texture_screen;

	set_system_texture_screen (lamp_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);

	////////////////////////////////////////
	//
	// set up MFD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (lamp1_env);

	//
	// window
	//

	set_2d_window (lamp1_env, LAMP1_WINDOW_X_MIN, LAMP1_WINDOW_Y_MIN, LAMP1_WINDOW_X_MAX, LAMP1_WINDOW_Y_MAX);

	//
	// viewport
	//

	lamp1_viewport_size = LAMP1_VIEWPORT_SMALL_SIZE;

	lamp1_viewport_x_org = LAMP1_VIEWPORT_TEXTURE_X_ORG;
	lamp1_viewport_y_org = LAMP1_VIEWPORT_TEXTURE_Y_ORG;
	lamp1_viewport_x_min = lamp1_viewport_x_org - (lamp1_viewport_size * 0.5);
	lamp1_viewport_y_min = lamp1_viewport_y_org - (lamp1_viewport_size * 0.5);
	lamp1_viewport_x_max = lamp1_viewport_x_org + (lamp1_viewport_size * 0.5) - 0.001;
	lamp1_viewport_y_max = lamp1_viewport_y_org + (lamp1_viewport_size * 0.5) - 0.001;

	set_2d_viewport (lamp1_env, lamp1_viewport_x_min, lamp1_viewport_y_min, lamp1_viewport_x_max, lamp1_viewport_y_max);

	set_active_screen (lamp1_texture_screen);

	if (lock_screen (lamp1_texture_screen))
	{

		draw_apache_indicator_lamps_3d ();

		flush_screen_texture_graphics (lamp1_texture_screen);

		unlock_screen (lamp1_texture_screen);
	}


	set_active_screen (video_screen);
}
