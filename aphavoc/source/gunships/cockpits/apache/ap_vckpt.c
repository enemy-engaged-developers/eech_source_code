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


#define DEBUG_MODULE FALSE

#define PNVS_MOVEMENT_RATE  rad(120)   // 120 deg per second
#define THROTTLE_MOVEMENT_RATE rad(60.0)

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
	*virtual_cockpit_display_view_mfd_inst3d,
	*virtual_cockpit_lights_inst3d,
	*virtual_cockpit_nose_inst3d;


static float clipx;
#if DEBUG_MODULE
static float dx, dy, dz;
#endif

static float throttle_pitch_1, throttle_pitch_2;
static float pnvs_heading;

// crew position in first dimension, min/max limit in second
static vec3d head_limits[2][2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	virtual_cockpit_inst3d = NULL;

	pilot_head_pitch_datum = rad(wide_cockpit_position[WIDEVIEW_APACHE_PILOT].c.p);
	co_pilot_head_pitch_datum = rad(wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].c.p);

	if (custom_3d_models.arneh_ah64d_cockpit)
	{
		virtual_cockpit_level1_inst3d = construct_3d_object (OBJECT_3D_ARNEH_AH64D_COCKPIT);
		virtual_cockpit_nose_inst3d = construct_3d_object(OBJECT_3D_ARNEH_AH64D_VCKPT_NOSE);

		virtual_cockpit_adi_inst3d = construct_3d_object (OBJECT_3D_ARNEH_AH64D_INSTRUMENTS_ADI);
		virtual_cockpit_compass_inst3d = construct_3d_object (OBJECT_3D_ARNEH_AH64D_INSTRUMENTS_COMPASS);
		virtual_cockpit_instrument_needles_inst3d = construct_3d_object (OBJECT_3D_ARNEH_AH64D_INSTRUMENTS_NEEDLES);

		virtual_cockpit_lights_inst3d = construct_3d_object(OBJECT_3D_ARNEH_AH64D_VCKPT_FIRE_WARNING_LIGHT);

		virtual_cockpit_level2_inst3d = NULL;
		virtual_cockpit_level3_inst3d = NULL;
		virtual_cockpit_fillet_level1_inst3d = NULL;
		virtual_cockpit_fillet_level2_inst3d = NULL;
		virtual_cockpit_fillet_level3_inst3d = NULL;
	}
	else
	{
		virtual_cockpit_level1_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL1);
		virtual_cockpit_level2_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL2);
		virtual_cockpit_level3_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL3);

		virtual_cockpit_fillet_level1_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL1_FILLET);
		virtual_cockpit_fillet_level2_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL2_FILLET);
		virtual_cockpit_fillet_level3_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL3_FILLET);

		virtual_cockpit_adi_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_ADI);
		virtual_cockpit_compass_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_COMPASS);
		virtual_cockpit_instrument_needles_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_NEEDLES);

		virtual_cockpit_nose_inst3d = NULL;
		virtual_cockpit_lights_inst3d = NULL;
	}

	virtual_cockpit_main_rotor_inst3d = construct_3d_object (OBJECT_3D_ARNEH_AH64D_VCKPT_MAIN_ROTOR);

	virtual_cockpit_large_adi_inst3d = construct_3d_object (OBJECT_3D_APACHE_VIRTUAL_COCKPIT_INSTRUMENTS_LARGE_ADI);
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

	initialise_altitude_counter();

//VJ 050208 cleaing up wideview
	wide_cockpit_nr = WIDEVIEW_APACHE_PILOT;
	set_global_wide_cockpit(TRUE);

#ifdef DEBUG  // don't limit in debug (for all practical purposes
	// pilot limits
	head_limits[0][0].x = -10;
	head_limits[0][1].x =  10;
	head_limits[0][0].y = -10;
	head_limits[0][1].y =  10;
	head_limits[0][0].z = -10;
	head_limits[0][1].z =  10;

	// co-pilot limits
	head_limits[1][0].x = -10;
	head_limits[1][1].x =  10;
	head_limits[1][0].y = -10;
	head_limits[1][1].y =  10;
	head_limits[1][0].z = -10;
	head_limits[1][1].z =  10;
#else
	// pilot limits
	head_limits[0][0].x = -0.25;
	head_limits[0][1].x =  0.25;
	head_limits[0][0].y = -0.3;
	head_limits[0][1].y =  0.3;
	head_limits[0][0].z = -0.10;
	head_limits[0][1].z =  0.50;

	// co-pilot limits
	head_limits[1][0].x = -0.2;
	head_limits[1][1].x =  0.2;
	head_limits[1][0].y = -0.2;
	head_limits[1][1].y =  0.2;
	head_limits[1][0].z = -0.05;
	head_limits[1][1].z =  0.3;
#endif

	if (custom_3d_models.arneh_ah64d_cockpit)  // move instruments to where they are in this cockpit
	{
		object_3d_sub_object_index_numbers
			index;

		throttle_pitch_1 = 0;
		throttle_pitch_2 = 0;

		// co-pilot's helmet
		initialise_co_pilot_head_animations();

		virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

		// MFD view is too high for pilot in ees file, so move it down 5 cm
		for (index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_1; index <= OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_1; index += (OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_1 - OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_1))
		{
			object_3d_sub_object_search_data
				search;

			search.search_depth = 0;
			search.search_object = virtual_cockpit_inst3d;
			search.sub_object_index = index;

			if (find_object_3d_sub_object (&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				debug_fatal ("Failed to locate display viewpoint in virtual cockpit");

			search.result_sub_object->relative_position.y -= 0.05;
		}

	}

#if DEBUG_MODULE
	dx = 0; dy = 0; dz = 0;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_apache_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	if (custom_3d_models.arneh_ah64d_cockpit)
	{
		destruct_3d_object(virtual_cockpit_level1_inst3d);
		destruct_3d_object(virtual_cockpit_nose_inst3d);
		destruct_3d_object(virtual_cockpit_lights_inst3d);
	}
	else
	{
		destruct_3d_object (virtual_cockpit_level1_inst3d);
		destruct_3d_object (virtual_cockpit_level2_inst3d);
		destruct_3d_object (virtual_cockpit_level3_inst3d);
		destruct_3d_object (virtual_cockpit_fillet_level1_inst3d);
		destruct_3d_object (virtual_cockpit_fillet_level2_inst3d);
		destruct_3d_object (virtual_cockpit_fillet_level3_inst3d);
	}

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

	deinitialise_apache_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();

	deinitialise_altitude_counter();
	
	clear_head_movement_data();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_apache_virtual_cockpit (void)
{
}

static void animate_pnvs(object_3d_instance* nose_inst3d)
{
	float
		heading,
		heading_movement,
		rate = PNVS_MOVEMENT_RATE * get_delta_time();
	object_3d_sub_object_search_data
		search;

	// PNVS is stowed pointing to the back and left when not active
	heading = night_vision_system_active ? -pilot_head_heading : rad(-120);

	heading_movement = heading - pnvs_heading;
	heading_movement = bound(heading_movement, -rate, rate);

	pnvs_heading += heading_movement;

	search.search_depth = 0;
	search.search_object = nose_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_AH64D_PNVS_HEADING;
	if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		search.result_sub_object->relative_heading = pnvs_heading;
}
extern float debug_var_x, debug_var_y, debug_var_z;

static void set_pitch(object_3d_instance* inst3d, float pitch, int sub_object_index)
{
	object_3d_sub_object_search_data
		search;
	int
		depth;

	for ( depth = 0; ; depth++ )
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = sub_object_index;
		if ( find_object_3d_sub_object ( &search ) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
			break;
		search.result_sub_object->relative_pitch = pitch;
	}
}

static void animate_throttles(object_3d_instance* inst3d)
{
	float
		left_throttle = bound (current_flight_dynamics->left_engine_n1_rpm.max, 0.0, 110.0),
		right_throttle = bound (current_flight_dynamics->right_engine_n1_rpm.max, 0.0, 110.0),
		max_movement = THROTTLE_MOVEMENT_RATE * get_delta_time(),
		throttle_angle = 0.0;

	// left throttle
	if (left_throttle < 60.0)  // idle at -45 deg
		throttle_angle = rad(-45.0);
	else  // otherwise somewhere between -30 and +10 deg
		throttle_angle = rad(-30.0) + rad(40.0 * (left_throttle - 60.0) / 50.0);

	throttle_pitch_1 += bound(throttle_angle - throttle_pitch_1, -max_movement, max_movement);
	set_pitch ( inst3d, throttle_pitch_1, OBJECT_3D_SUB_OBJECT_ARNEH_AH64D_THROTTLE_LEFT );

	// right throttle
	if (right_throttle < 60.0)  // idle at -45 deg
		throttle_angle = rad(-45.0);
	else  // otherwise somewhere between -30 and +10 deg
		throttle_angle = rad(-30.0) + rad(40.0 * (right_throttle - 60.0) / 50.0);

	throttle_pitch_2 += bound(throttle_angle - throttle_pitch_2, -max_movement, max_movement);
	set_pitch ( inst3d, throttle_pitch_2, OBJECT_3D_SUB_OBJECT_ARNEH_AH64D_THROTTLE_RIGHT );
}

int apache_pnvs_active(void)
{
	static int pnvs_in_position = FALSE;

	if (!night_vision_system_active)
	{
		pnvs_in_position = FALSE;
		return FALSE;
	}

	if (!custom_3d_models.arneh_ah64d_cockpit || pnvs_in_position)
		return TRUE;

	// night vision isn't activated until the PNVS turret has slewed within 5 degrees of pilots head heading
	pnvs_in_position = pnvs_heading > -pilot_head_heading - rad(5.0);

	return pnvs_in_position;
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
			ambient_light_colour.red		 		= 1.0;
			ambient_light_colour.green		  		= 1.0;
			ambient_light_colour.blue		  		= 1.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 1.0;
			directional_light_colour.blue			= 1.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-40.0);
			directional_light_roll 					= rad (0.0);

			directional_light_pitch 				= rad (0.0);

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

	directional_light_colour.red		= 0.3;
	directional_light_colour.green	= 0.3;
	directional_light_colour.blue		= 0.3;

	directional_light_heading 			= rad (0.0);
	directional_light_pitch 			= rad (0.0);
	directional_light_roll 				= rad (0.0);

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAWN:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.70;
			ambient_light_colour.green		  		= 0.70;
			ambient_light_colour.blue		  		= 0.70;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAY:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.85;
			ambient_light_colour.green		  		= 0.85;
			ambient_light_colour.blue		  		= 0.85;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-40.0);
			directional_light_roll 					= rad (0.0);

			directional_light_pitch 				= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DUSK:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.65;
			ambient_light_colour.green		  		= 0.50;
			ambient_light_colour.blue		  		= 0.50;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_NIGHT:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.45;
			ambient_light_colour.green		  		= 0.45;
			ambient_light_colour.blue		  		= 0.55;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
	}

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

	*display_viewpoint = virtual_cockpit_inst3d->vp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///  Positions and rotates the viewpoint to the correct position for the pilot and view selected
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_apache_crew_viewpoint (viewpoint *crew_viewpoint)
{
	object_3d_sub_instance *head_object;
	int is_copilot = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT;

	viewpoint
		vp;

	ASSERT (crew_viewpoint);

	virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

	{
		object_3d_sub_object_index_numbers
			index;
		object_3d_sub_object_search_data
			search;

		switch (get_view_mode())
		{
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
			index = is_copilot
				? OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_2
				: OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_1;
			break;

		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
			index = is_copilot
				? OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_2
				: OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_1;
			break;

		default:
			index = OBJECT_3D_SUB_OBJECT_PILOT_VIEWPOINT;
			break;
		}

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = index;

		if (find_object_3d_sub_object (&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			debug_fatal ("Failed to locate display viewpoint in virtual cockpit");
		}

		head_object = search.result_sub_object;
	}

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	switch (get_view_mode())
	{
	case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
	case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		break;

	default:
		// adjust pitch according to user preferance
		if (edit_wide_cockpit)
			pilot_head_pitch = rad ( wide_cockpit_position[wide_cockpit_nr].c.p );

		// rotate head
		head_object->relative_heading = -pilot_head_heading;
		head_object->relative_pitch = -pilot_head_pitch;

		// adjust position according to user preferance
		head_object->relative_position.x = wide_cockpit_position[wide_cockpit_nr].c.x;
		head_object->relative_position.y = wide_cockpit_position[wide_cockpit_nr].c.y;
		head_object->relative_position.z = wide_cockpit_position[wide_cockpit_nr].c.z;

		// adjust for track-IR position
		if (query_TIR_active())
		{
			head_object->relative_position.x -= current_custom_cockpit_viewpoint.x;
			head_object->relative_position.y -= current_custom_cockpit_viewpoint.y;
			head_object->relative_position.z -= current_custom_cockpit_viewpoint.z;
		}

		get_head_g_movement(&head_object->relative_position.x, &head_object->relative_position.y, &head_object->relative_position.z, FALSE);

		// keep head inside reasonable limimts
		head_object->relative_position.x = bound(head_object->relative_position.x, head_limits[is_copilot][0].x, head_limits[is_copilot][1].x);
		head_object->relative_position.y = bound(head_object->relative_position.y, head_limits[is_copilot][0].y, head_limits[is_copilot][1].y);
		head_object->relative_position.z = bound(head_object->relative_position.z, head_limits[is_copilot][0].z, head_limits[is_copilot][1].z);

		if (is_copilot)
		{
			// adjust for offset of co-pilot's cockpit compared to pilot's
			head_object->relative_position.y += -0.30;
			head_object->relative_position.z += 1.32;
		}
	}

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);
	get_3d_sub_object_world_viewpoint (head_object, &vp);
	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &main_vp.position);

	main_vp.x += vp.x;
	main_vp.y += vp.y;
	main_vp.z += vp.z;

	memcpy (main_vp.attitude, vp.attitude, sizeof (matrix3x3));

	vp.x = -vp.x;
	vp.y = -vp.y;
	vp.z = -vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, vp.attitude, &vp.position);

	*crew_viewpoint = virtual_cockpit_inst3d->vp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///vj draws internal cockpit, dashboad, dials including frame/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_internal_virtual_cockpit (unsigned int flags)
{
	matrix3x3
		head_rotation;

	viewpoint
		vp;

	vec3d
		vp_position,
		vp_current_position,
		vp_world_position,
		vp_cockpit_world_position;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*virtual_cockpit_inst3d;

	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	if (custom_3d_models.arneh_ah64d_cockpit)
		get_apache_crew_viewpoint(&vp);
	else
	{
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
			vp_position.x = 0.0;
			vp_position.y = 0.0;
			vp_position.z = 0.0;

	//VJ wideview mod, date: 18-mar-03
			if (get_global_wide_cockpit ())
			{
			   vp_position.x = wide_cockpit_position[wide_cockpit_nr].c.x;
			   vp_position.y = wide_cockpit_position[wide_cockpit_nr].c.y;
			   vp_position.z = wide_cockpit_position[wide_cockpit_nr].c.z;
				//VJ 050207 included head pitch in fixed view setting
				pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].c.p );
				if (edit_wide_cockpit)
					pilot_head_pitch = pilot_head_pitch_datum;
			}

			vp_position.x += current_custom_cockpit_viewpoint.x;
			vp_position.y += current_custom_cockpit_viewpoint.y;
			vp_position.z += current_custom_cockpit_viewpoint.z;

			get_head_g_movement(&vp_position.x, &vp_position.y, &vp_position.z, FALSE);

			get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);
			get_3d_transformation_matrix(head_rotation, pilot_head_heading, -pilot_head_pitch, 0.0);

			multiply_matrix3x3_vec3d(&vp_cockpit_world_position, head_rotation, &vp_position);

			vp.x = vp_cockpit_world_position.x;
			vp.y = vp_cockpit_world_position.y;
			vp.z = vp_cockpit_world_position.z;
		}
	}

	////////////////////////////////////////
	//
	// render displays onto textures (before draw 3D scenes)
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_UPFRONT_DISPLAY)
	{
		draw_apache_upfront_display_on_texture ();
	}

	if (flags & VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES)
		draw_apache_altitude_counter();

	if (flags & VIRTUAL_COCKPIT_PILOT_LHS_MFD_DISPLAY)
	{
		draw_apache_mfd_on_texture (MFD_LOCATION_PILOT_LHS);
	}

	if (flags & VIRTUAL_COCKPIT_RHS_MFD_DISPLAY)
	{
		draw_apache_mfd_on_texture (MFD_LOCATION_PILOT_RHS);
	}

	if (flags & VIRTUAL_COCKPIT_CPG_LHS_MFD_DISPLAY)
	{
		draw_apache_mfd_on_texture (MFD_LOCATION_CPG_LHS);
	}

	if (flags & VIRTUAL_COCKPIT_CPG_RHS_MFD_DISPLAY)
	{
		draw_apache_mfd_on_texture (MFD_LOCATION_CPG_RHS);
	}

	if (flags & VIRTUAL_COCKPIT_ORT_DISPLAY && d3d_can_render_to_texture)
		draw_apache_mfd_on_texture (MFD_LOCATION_ORT);

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_COCKPIT))
	{
//		set_cockpit_lighting (vp.attitude);

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
				if (custom_3d_models.arneh_ah64d_cockpit)
					virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;
				else
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
				}

				#if DEMO_VERSION

				virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

				#endif

				if (custom_3d_models.arneh_ah64d_cockpit)
					animate_throttles(virtual_cockpit_inst3d);

				virtual_cockpit_inst3d->vp = vp;

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

				// with new cockpit we have to draw these in internal cockpit
				if (custom_3d_models.arneh_ah64d_cockpit)
				{
					// co-pilot head
					animate_co_pilot_head(virtual_cockpit_inst3d);

					// compass
					{
						search.search_depth = 0;
						search.search_object = virtual_cockpit_compass_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_COMPASS_HEADING_NULL;

						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
						}

						virtual_cockpit_compass_inst3d->vp = vp;

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_compass_inst3d->vp.position, virtual_cockpit_compass_inst3d);
					}

					// ADI
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

						virtual_cockpit_adi_inst3d->vp = vp;

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_adi_inst3d->vp.position, virtual_cockpit_adi_inst3d);
					}

					{
						//
						// airspeed
						//

						search.search_depth = 0;
						search.search_object = virtual_cockpit_instrument_needles_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_AIRSPEED;

						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->relative_roll = get_apache_virtual_cockpit_airspeed_indicator_needle_value ();
						}
					}

					{
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
					}

					virtual_cockpit_instrument_needles_inst3d->vp = vp;
					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_instrument_needles_inst3d->vp.position, virtual_cockpit_instrument_needles_inst3d);

					{
						//
						// Fire warning lights
						//
						search.search_depth = 0;
						search.search_object = virtual_cockpit_lights_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_ARNEH_AH64D_LIGHT_FIRE1;
						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->visible_object = apache_lamps.engine_1_fire;
						}

						search.search_depth = 0;
						search.search_object = virtual_cockpit_lights_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_ARNEH_AH64D_LIGHT_FIRE2;
						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->visible_object = apache_lamps.engine_2_fire;
						}
					}

					{
						//
						// Fire extinguisher lights
						//
						search.search_depth = 0;
						search.search_object = virtual_cockpit_lights_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_ARNEH_AH64D_LIGHT_EXT1;
						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->visible_object = fire_extinguisher_used > 0;
						}

						search.search_depth = 0;
						search.search_object = virtual_cockpit_lights_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_ARNEH_AH64D_LIGHT_EXT2;
						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->visible_object = fire_extinguisher_used > 1;
						}
					}

					{
						//
						// APU lights
						//
						search.search_depth = 0;
						search.search_object = virtual_cockpit_lights_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_ARNEH_AH64D_LIGHT_APU;
						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->visible_object = current_flight_dynamics->apu_rpm.value > 20.0;
						}
					}

					virtual_cockpit_lights_inst3d->vp = vp;
					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_lights_inst3d->vp.position, virtual_cockpit_lights_inst3d);
				}
			}

			draw_3d_scene ();

			print_edit_wide_cockpit ();
			print_repairing_status();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (!custom_3d_models.arneh_ah64d_cockpit && flags & (VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES | VIRTUAL_COCKPIT_INSTRUMENT_LARGE_NEEDLES))
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

/*
   				vp_current_position = vp_position;

				vp_current_position.x += dx; // -0.019;
				vp_current_position.y += dy; // + 0.024;
				vp_current_position.z += dz; // -0.042;

				multiply_matrix3x3_vec3d(&vp_world_position, head_rotation, &vp_current_position);

				vp.x = vp_world_position.x;
				vp.y = vp_world_position.y;
				vp.z = vp_world_position.z;
*/
				virtual_cockpit_instrument_needles_inst3d->vp = vp;

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

				vp_current_position = vp_position;

				vp_current_position.x += -0.019;
				vp_current_position.y += 0.024;
				vp_current_position.z += -0.042;

				multiply_matrix3x3_vec3d(&vp_world_position, head_rotation, &vp_current_position);

				vp.x = vp_world_position.x;
				vp.y = vp_world_position.y;
				vp.z = vp_world_position.z;

				virtual_cockpit_instrument_large_needles_inst3d->vp = vp;

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

	if (!custom_3d_models.arneh_ah64d_cockpit)
	{
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

				virtual_cockpit_display_view_mfd_inst3d->vp = vp;

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_display_view_mfd_inst3d->vp.position, virtual_cockpit_display_view_mfd_inst3d);

				//
				// rhs mfd
				//

				virtual_cockpit_display_view_mfd_inst3d->vp = vp;

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
						virtual_cockpit_upfront_display_inst3d->vp = vp;

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_upfront_display_inst3d->vp.position, virtual_cockpit_upfront_display_inst3d);
					}

					vp_current_position = vp_position;

					vp_current_position.y += 0.008;
					vp_current_position.z += 0.005;

					multiply_matrix3x3_vec3d(&vp_world_position, head_rotation, &vp_current_position);

					vp.x = vp_world_position.x;
					vp.y = vp_world_position.y;
					vp.z = vp_world_position.z;

					//
					// lhs mfd
					//

					if (flags & VIRTUAL_COCKPIT_LHS_MFD_DISPLAY)
					{
						virtual_cockpit_lhs_mfd_inst3d->vp = vp;

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_lhs_mfd_inst3d->vp.position, virtual_cockpit_lhs_mfd_inst3d);
					}

					//
					// rhs mfd
					//

					if (flags & VIRTUAL_COCKPIT_RHS_MFD_DISPLAY)
					{
						virtual_cockpit_rhs_mfd_inst3d->vp = vp;

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_rhs_mfd_inst3d->vp.position, virtual_cockpit_rhs_mfd_inst3d);
					}

					draw_3d_scene ();

					end_3d_scene ();
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (get_view_mode () != VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD
		&& get_view_mode () != VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		vp.x = vp_cockpit_world_position.x;
		vp.y = vp_cockpit_world_position.y;
		vp.z = vp_cockpit_world_position.z;
	}

	//
	// draw fillet to mask TADS display
	//

	if
	(!custom_3d_models.arneh_ah64d_cockpit &&
		(d3d_can_render_to_texture) &&
		//always draw fillet not only with tads
		//(get_apache_tads_display_visible ()) &&
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

			virtual_cockpit_inst3d->vp = vp;

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

//VJ wideview mod, date: 18-mar-03
#if DEBUG_MODULE
	if (check_key(DIK_NUMPAD7))
	{
		system_sleep(20);
		dy+= 0.001;
	}
	if (check_key(DIK_NUMPAD9))
	{
		system_sleep(20);
		dy-= 0.001;
	}
	if (check_key(DIK_NUMPADSLASH))
	{
		system_sleep(20);
		dx+= 0.001;
	}
	if (check_key(DIK_NUMPADSTAR))
	{
		system_sleep(20);
		dx-= 0.001;
	}
	if (check_key(DIK_NUMPADMINUS))
	{
		system_sleep(20);
		dz+= 0.001;
	}
	if (check_key(DIK_NUMPADPLUS))
	{
		system_sleep(20);
		dz-= 0.001;
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

void draw_apache_external_virtual_cockpit (unsigned int flags, unsigned char *wiper_rle_graphic)
{
	vec3d
		vp_position,
		vp_cockpit_world_position,
		vp_current_position,
		vp_world_position;

	matrix3x3
		head_rotation;

	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*inst3d;

	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	if (custom_3d_models.arneh_ah64d_cockpit)
		get_apache_crew_viewpoint(&vp);
	else
	{
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
			vp_position.x = 0.0;
			vp_position.y = 0.0;
			vp_position.z = 0.0;

	//VJ wideview mod, date: 18-mar-03
			if (get_global_wide_cockpit ())
			{
			   vp_position.x = wide_cockpit_position[wide_cockpit_nr].c.x;
			   vp_position.y = wide_cockpit_position[wide_cockpit_nr].c.y;
			   vp_position.z = wide_cockpit_position[wide_cockpit_nr].c.z;
				//VJ 050207 included head pitch in fixed view setting
	//			pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].c.p );
	//			if (edit_wide_cockpit)
	//				pilot_head_pitch = pilot_head_pitch_datum;
			}

			vp_position.x += current_custom_cockpit_viewpoint.x;
			vp_position.y += current_custom_cockpit_viewpoint.y;
			vp_position.z += current_custom_cockpit_viewpoint.z;

			get_head_g_movement(&vp_position.x, &vp_position.y, &vp_position.z, FALSE);

			get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);
			get_3d_transformation_matrix(head_rotation, pilot_head_heading, -pilot_head_pitch, 0.0);

			multiply_matrix3x3_vec3d(&vp_cockpit_world_position, head_rotation, &vp_position);

			vp.x = vp_cockpit_world_position.x;
			vp.y = vp_cockpit_world_position.y;
			vp.z = vp_cockpit_world_position.z;
		}
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
					inst3d = (object_3d_instance *) get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

					animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d, inst3d);

					virtual_cockpit_main_rotor_inst3d->vp = vp;

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_main_rotor_inst3d->vp.position, virtual_cockpit_main_rotor_inst3d);
				}
			}

			// nose

			if (custom_3d_models.arneh_ah64d_cockpit)
			{
				ASSERT(virtual_cockpit_nose_inst3d);
				animate_pnvs(virtual_cockpit_nose_inst3d);
				virtual_cockpit_nose_inst3d->vp = vp;
				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_nose_inst3d->vp.position, virtual_cockpit_nose_inst3d);
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

	if (!custom_3d_models.arneh_ah64d_cockpit && (flags & (VIRTUAL_COCKPIT_COMPASS | VIRTUAL_COCKPIT_ADI | VIRTUAL_COCKPIT_LARGE_ADI)))
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


			vp_current_position = vp_position;

/*			if (get_global_wide_cockpit ())
			{
				vp_current_position.x += -0.018 + dx;
				vp_current_position.y += 0.019 + dy;
				vp_current_position.z += -0.049 + dz;
			}
			else */
			{
				vp_current_position.x += 0.003;
				vp_current_position.y += 0.000;
				vp_current_position.z += -0.003;
			}

			multiply_matrix3x3_vec3d(&vp_world_position, head_rotation, &vp_current_position);

			vp.x = vp_world_position.x;
			vp.y = vp_world_position.y;
			vp.z = vp_world_position.z;

			if (flags & VIRTUAL_COCKPIT_COMPASS)
			{
				search.search_depth = 0;
				search.search_object = virtual_cockpit_compass_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_COMPASS_HEADING_NULL;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
				}

				virtual_cockpit_compass_inst3d->vp = vp;

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

					get_apache_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

					search.result_sub_object->relative_heading = -heading;

					search.result_sub_object->relative_pitch = pitch;

					search.result_sub_object->relative_roll = -roll;
				}

				virtual_cockpit_adi_inst3d->vp = vp;

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

				virtual_cockpit_large_adi_inst3d->vp = vp;

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_large_adi_inst3d->vp.position, virtual_cockpit_large_adi_inst3d);
			}

			draw_3d_scene ();

			end_3d_scene ();
		}

		vp.x = vp_cockpit_world_position.x;
		vp.y = vp_cockpit_world_position.y;
		vp.z = vp_cockpit_world_position.z;
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
