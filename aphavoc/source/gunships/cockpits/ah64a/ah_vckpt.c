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

static float clipx;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ah64a_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	virtual_cockpit_inst3d = NULL;

	pilot_head_pitch_datum = 0.0;

	co_pilot_head_pitch_datum = 0.0;

	virtual_cockpit_level1_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL1);

	virtual_cockpit_level2_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL2);

	virtual_cockpit_level3_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL3);

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

	initialise_ah64a_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();

//VJ wideview mod, date: 18-mar-03
	wide_cockpit_nr = 4;
//VJ wideview mod, date: 20-mar-03
//start up in normal view because when you switch to wideview the parameters are read
	set_global_wide_cockpit(FALSE);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ah64a_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	destruct_3d_object (virtual_cockpit_level1_inst3d);

	destruct_3d_object (virtual_cockpit_level2_inst3d);

	destruct_3d_object (virtual_cockpit_level3_inst3d);

	destruct_3d_object (virtual_cockpit_fillet_level1_inst3d);

	destruct_3d_object (virtual_cockpit_fillet_level2_inst3d);

	destruct_3d_object (virtual_cockpit_fillet_level3_inst3d);

	destruct_3d_object (virtual_cockpit_main_rotor_inst3d);

	destruct_3d_object (virtual_cockpit_adi_inst3d);

	destruct_3d_object (virtual_cockpit_large_adi_inst3d);

	destruct_3d_object (virtual_cockpit_compass_inst3d);

	destruct_3d_object (virtual_cockpit_instrument_needles_inst3d);

	destruct_3d_object (virtual_cockpit_instrument_large_needles_inst3d);

	destruct_3d_object (virtual_cockpit_upfront_display_inst3d);

	destruct_3d_object (virtual_cockpit_lhs_mfd_inst3d);

	destruct_3d_object (virtual_cockpit_rhs_mfd_inst3d);

	destruct_3d_object (virtual_cockpit_display_view_mfd_inst3d);

	//
	// wipers and rain
	//

	deinitialise_ah64a_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_ah64a_virtual_cockpit (void)
{
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

static void get_display_viewpoint (view_modes mode, viewpoint *display_viewpoint)
{
	object_3d_sub_object_index_numbers
		index;

	object_3d_sub_object_search_data
		search;

	viewpoint
		vp;

	ASSERT (display_viewpoint);

	if ((!full_screen_hi_res) && (application_video_colourdepth == 16))
	{
		display_viewpoint->x = 0.0;
		display_viewpoint->y = 0.0;
		display_viewpoint->z = 0.0;

		get_local_entity_attitude_matrix (get_gunship_entity (), display_viewpoint->attitude);

		return;
	}

	if (mode == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		index = OBJECT_3D_SUB_OBJECT_APACHE_COCKPIT_LHS_MFD_CAMERA;
	}
	else if (mode == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		index = OBJECT_3D_SUB_OBJECT_APACHE_COCKPIT_RHS_MFD_CAMERA;
	}
	else
	{
		debug_fatal ("Invalid view mode = %d", mode);
	}

	virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = index;

	if (find_object_3d_sub_object (&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		debug_fatal ("Failed to locate display viewpoint in virtual cockpit");
	}

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	get_3d_sub_object_world_viewpoint (search.result_sub_object, &vp);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &main_vp.position);

	main_vp.x += vp.x;
	main_vp.y += vp.y;
	main_vp.z += vp.z;

	memcpy (main_vp.attitude, vp.attitude, sizeof (matrix3x3));

	vp.x = -vp.x;
	vp.y = -vp.y;
	vp.z = -vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, vp.attitude, &vp.position);

	memcpy (display_viewpoint, &virtual_cockpit_inst3d->vp, sizeof (viewpoint));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///vj draws internal cockpit, dashboad, dials including frame/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ah64a_internal_virtual_cockpit (unsigned int flags)
{
	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*virtual_cockpit_inst3d;

//VJ wideview mod, date: 18-mar-03
    char buffer[128];

	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD, &vp);
	}
	else if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD, &vp);
	}
	else
	{
		vp.x = 0.0;
		vp.y = 0.0;
		vp.z = 0.0;

//VJ wideview mod, date: 18-mar-03
		if (get_global_wide_cockpit ())
		{
		    vp.y = wide_cockpit_position[wide_cockpit_nr].y;
		    vp.z = wide_cockpit_position[wide_cockpit_nr].z;
		}

		get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);
	}

	////////////////////////////////////////
	//
	// render displays onto textures (before draw 3D scenes)
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_UPFRONT_DISPLAY)
	{
		draw_ah64a_upfront_display_on_texture ();
	}

	if (flags & VIRTUAL_COCKPIT_LHS_MFD_DISPLAY)
	{
		draw_ah64a_mfd_on_texture (MFD_LOCATION_LHS);
	}

	if (flags & VIRTUAL_COCKPIT_RHS_MFD_DISPLAY)
	{
		draw_ah64a_mfd_on_texture (MFD_LOCATION_RHS);
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

//VJ 050108 wideview x coord used to clip apache cockpit
		if (get_global_wide_cockpit ())
		   clipx = wide_cockpit_position[wide_cockpit_nr].x;
		else
		   clipx = 0;

		set_3d_view_distances (main_3d_single_light_env, 10.0+clipx, 0.1, 1.0, 0.0);

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

				memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);
			}

			draw_3d_scene ();

//VJ wideview mod, date: 18-mar-03
            if (edit_wide_cockpit)
         	{
				sprintf(buffer,"AH64a wide cockpit mod edit:");
                ui_display_text (buffer, 10, 40);
				sprintf(buffer,"X: numpad 1/3; Y: numpad 8/2; Z: numpad 4/6; Restore: numpad 0; Save: Alt-\\");
                ui_display_text (buffer, 10, 60);
                sprintf(buffer,"x=%.3f y=%.3f z=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z);
                ui_display_text (buffer, 10, 100);
            }

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
					search.result_sub_object->relative_roll = get_ah64a_virtual_cockpit_adi_slip_indicator_needle_value ();
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

					search.result_sub_object->relative_roll = get_ah64a_virtual_cockpit_airspeed_indicator_needle_value ();
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

					search.result_sub_object->relative_roll = get_ah64a_virtual_cockpit_barometric_altimeter_needle_value ();
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
						get_ah64a_virtual_cockpit_clock_hand_values (&hours, &minutes, &seconds);
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


//VJ wideview mod, date: 18-mar-03
		        if (get_global_wide_cockpit ())
		        {
                    vp.z = wide_cockpit_position[wide_cockpit_nr].z+0.03;
                    vp.y = wide_cockpit_position[wide_cockpit_nr].y+0.01;
                }
				memcpy (&virtual_cockpit_instrument_needles_inst3d->vp, &vp, sizeof (viewpoint));

				if (get_global_wide_cockpit ())
				{
                   vp.y = wide_cockpit_position[wide_cockpit_nr].y;
                   vp.z = wide_cockpit_position[wide_cockpit_nr].z;
                }
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
					search.result_sub_object->relative_roll = get_ah64a_virtual_cockpit_adi_slip_indicator_needle_value ();
				}

				//
				// airspeed
				//

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_large_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_AIRSPEED;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_roll = get_ah64a_virtual_cockpit_airspeed_indicator_needle_value ();
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

			if (begin_3d_scene ())
			{
				//
				// up-front display
				//

				if (flags & VIRTUAL_COCKPIT_UPFRONT_DISPLAY)
				{
					memcpy (&virtual_cockpit_upfront_display_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_upfront_display_inst3d->vp.position, virtual_cockpit_upfront_display_inst3d);
				}

//VJ wideview mod, date: 18-mar-03
	          	if (get_global_wide_cockpit ())
                     vp.z = wide_cockpit_position[wide_cockpit_nr].z+0.02;

				//
				// lhs mfd
				//

				if (flags & VIRTUAL_COCKPIT_LHS_MFD_DISPLAY)
				{
					memcpy (&virtual_cockpit_lhs_mfd_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_lhs_mfd_inst3d->vp.position, virtual_cockpit_lhs_mfd_inst3d);
				}

				//
				// rhs mfd
				//

				if (flags & VIRTUAL_COCKPIT_RHS_MFD_DISPLAY)
				{
					memcpy (&virtual_cockpit_rhs_mfd_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_rhs_mfd_inst3d->vp.position, virtual_cockpit_rhs_mfd_inst3d);
				}

//VJ wideview mod, date: 18-mar-03
	        	if (get_global_wide_cockpit ())
                   vp.z = wide_cockpit_position[wide_cockpit_nr].z;

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
		(get_ah64a_tads_display_visible ()) &&
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

			memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			draw_3d_scene ();
//VJ 300303 bug fix: the following line was omitted from the source accidently
			end_3d_scene ();
		}
	}

//VJ wideview mod, date: 18-mar-03
	////////////////////////////////////////
	//
	// wide cockpit position edit
	//
	////////////////////////////////////////

	if (edit_wide_cockpit)
	{
		if (check_key(DIK_NUMPAD6))
		{
            wide_cockpit_position[wide_cockpit_nr].z += 0.01;
      }
		if (check_key(DIK_NUMPAD4))
		{
            wide_cockpit_position[wide_cockpit_nr].z -= 0.01;
      }
		if (check_key(DIK_NUMPAD8))
		{
            wide_cockpit_position[wide_cockpit_nr].y += 0.01;
      }
		if (check_key(DIK_NUMPAD2))
		{
            wide_cockpit_position[wide_cockpit_nr].y -= 0.01;
      }
		if (check_key(DIK_NUMPAD1))
		{
            wide_cockpit_position[wide_cockpit_nr].x -= 0.01;
      }
		if (check_key(DIK_NUMPAD3))
		{
            wide_cockpit_position[wide_cockpit_nr].x += 0.01;
      }
		if (check_key(DIK_NUMPAD5))
		{
			wide_cockpit_position[wide_cockpit_nr].x = -8.0;
		}
		if (check_key(DIK_NUMPAD0))
		{
				wide_cockpit_position[wide_cockpit_nr].x = 0;
				wide_cockpit_position[wide_cockpit_nr].y = 0.07;
				wide_cockpit_position[wide_cockpit_nr].z = 0.55;
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

void draw_ah64a_external_virtual_cockpit (unsigned int flags, unsigned char *wiper_rle_graphic)
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

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD, &vp);
	}
	else if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD, &vp);
	}
	else
	{
		vp.x = 0.0;
		vp.y = 0.0;
		vp.z = 0.0;

		if (get_global_wide_cockpit ())
		{
		    vp.y = wide_cockpit_position[wide_cockpit_nr].y;
		    vp.z = wide_cockpit_position[wide_cockpit_nr].z;
		}

		get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);
	}

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_MAIN_ROTOR | VIRTUAL_COCKPIT_STOWED_WIPER | VIRTUAL_COCKPIT_MOVING_WIPER))
	{
		set_3d_active_environment (main_3d_env);

//VJ 050108 wideview x coord used to clip apache cockpit
		set_3d_view_distances (main_3d_env, 10.0+clipx, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

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

					inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

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
					draw_ah64a_virtual_cockpit_wiper (&vp);
				}
			}
			else
			{
				if (flags & VIRTUAL_COCKPIT_MOVING_WIPER)
				{
					draw_ah64a_virtual_cockpit_wiper (&vp);
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

//VJ wideview mod, date: 18-mar-03
				if (get_global_wide_cockpit ())
                   vp.y = wide_cockpit_position[wide_cockpit_nr].y+0.01;

				memcpy (&virtual_cockpit_compass_inst3d->vp, &vp, sizeof (viewpoint));

//VJ wideview mod, date: 18-mar-03
				if (get_global_wide_cockpit ())
                   vp.y = wide_cockpit_position[wide_cockpit_nr].y;

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_compass_inst3d->vp.position, virtual_cockpit_compass_inst3d);
			}

			//
			// ADI
			//

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

					get_ah64a_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

					search.result_sub_object->relative_heading = -heading;

					search.result_sub_object->relative_pitch = pitch;

					search.result_sub_object->relative_roll = -roll;
				}
//VJ wideview mod, date: 18-mar-03
				if (get_global_wide_cockpit ())
                   vp.y = wide_cockpit_position[wide_cockpit_nr].y+0.02;

				memcpy (&virtual_cockpit_adi_inst3d->vp, &vp, sizeof (viewpoint));

//VJ wideview mod, date: 18-mar-03
				if (get_global_wide_cockpit ())
                   vp.y = wide_cockpit_position[wide_cockpit_nr].y;

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

					get_ah64a_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

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
	// rendered wiper
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_RENDERED_WIPER)
	{
		if (wiper_mode == WIPER_MODE_STOWED)
		{
			ASSERT (wiper_rle_graphic);

			if (lock_screen (active_screen))
			{
				blit_rle_graphic (wiper_rle_graphic, ix_640_480, iy_640_480);

				unlock_screen (active_screen);
			}
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
				draw_ah64a_virtual_cockpit_rain_effect (&vp);

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

void damage_ah64a_virtual_cockpit_main_rotors (int seed)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_main_rotor_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

	damage_helicopter_main_rotor_inst3d (virtual_cockpit_main_rotor_inst3d, seed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_ah64a_virtual_cockpit_main_rotors (void)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_main_rotor_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

	restore_helicopter_main_rotor_inst3d (virtual_cockpit_main_rotor_inst3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
