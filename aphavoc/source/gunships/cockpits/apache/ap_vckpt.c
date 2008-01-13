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
	*virtual_cockpit_nose_inst3d;


static float clipx;
#if DEBUG_MODULE
static float dx, dy, dz;
#endif

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

	pilot_head_pitch_datum = rad(wide_cockpit_position[WIDEVIEW_APACHE_PILOT].p);
	co_pilot_head_pitch_datum = rad(wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].p);

	if (custom_3d_models.arneh_ah64d_cockpit)
	{
		virtual_cockpit_level1_inst3d = construct_3d_object (OBJECT_3D_ARNEH_AH64D_COCKPIT);
		virtual_cockpit_nose_inst3d = construct_3d_object(OBJECT_3D_ARNEH_AH64D_VCKPT_NOSE);
		
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

		virtual_cockpit_nose_inst3d = NULL;
	}

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
		virtual_cockpit_compass_inst3d->sub_objects[0].relative_position.x = -0.101;
		virtual_cockpit_compass_inst3d->sub_objects[0].relative_position.y = -0.101;
		virtual_cockpit_compass_inst3d->sub_objects[0].relative_position.z = 0.800;
	
		virtual_cockpit_adi_inst3d->sub_objects[0].relative_position.x = 0.418;
		virtual_cockpit_adi_inst3d->sub_objects[0].relative_position.y = -0.419;
		virtual_cockpit_adi_inst3d->sub_objects[0].relative_position.z = 0.793;
	
		// airspeed
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_position.x = 0.371;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_position.y = -0.5175;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_position.z = 0.764;
					
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_scale.x = 0.62;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_scale.y = 0.62;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_scale.z = 0.62;
	
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_heading = rad(4.5);
		virtual_cockpit_instrument_needles_inst3d->sub_objects[0].relative_pitch = rad(9.5);

		// altitude
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_position.x = 0.460;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_position.y = -0.5165;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_position.z = 0.762;
					
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_scale.x = 0.62;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_scale.y = 0.62;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_scale.z = 0.62;
	
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_heading = rad(4.5);
		virtual_cockpit_instrument_needles_inst3d->sub_objects[2].relative_pitch = rad(9.5);

		// pnvs
		virtual_cockpit_nose_inst3d->sub_objects[0].sub_objects[0].relative_position.x = -0.025;
		virtual_cockpit_nose_inst3d->sub_objects[0].sub_objects[0].relative_position.z = 3.12;

		virtual_cockpit_nose_inst3d->sub_objects[0].sub_objects[0].relative_heading = rad(-135);

		// throttles
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[1].relative_position.x = -0.552;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[1].relative_position.y = -0.700;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[1].relative_position.z = 0.298;

		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[2].relative_position.x = -0.544;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[2].relative_position.y = -0.700;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[2].relative_position.z = 0.298;

		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[3].relative_position.x = -0.502;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[3].relative_position.y = -0.974;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[3].relative_position.z = 1.588;
	
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[4].relative_position.x = -0.494;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[4].relative_position.y = -0.974;
		virtual_cockpit_level1_inst3d->sub_objects[0].sub_objects[4].relative_position.z = 1.588;

		// don't show clock or sideslip
		virtual_cockpit_instrument_needles_inst3d->sub_objects[1].visible_object = FALSE;  // sideslip
		virtual_cockpit_instrument_needles_inst3d->sub_objects[3].visible_object = FALSE;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[4].visible_object = FALSE;
		virtual_cockpit_instrument_needles_inst3d->sub_objects[5].visible_object = FALSE;
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_apache_virtual_cockpit (void)
{
}

static void animate_pnvs(object_3d_instance* inst3d)
{
	float heading = 0.0, current_heading, heading_movement;
	object_3d_sub_instance* pnvs_object = &inst3d->sub_objects[0].sub_objects[0];  // hacky way of getting the pnvs sub object

	if (night_vision_system_active)
		heading = -pilot_head_heading;
	else
		heading = rad(-120);   // PNVS is stowed pointing to the back and left when not active

	current_heading = pnvs_object->relative_heading;
	heading_movement = heading - pnvs_object->relative_heading;

	heading_movement = bound(heading_movement, -PNVS_MOVEMENT_RATE * get_delta_time(), PNVS_MOVEMENT_RATE * get_delta_time());

	pnvs_object->relative_heading += heading_movement;
}
extern float debug_var_x, debug_var_y, debug_var_z;
static void animate_throttles(object_3d_instance* inst3d)
{
	float
		left_throttle = bound (current_flight_dynamics->left_engine_n1_rpm.max, 0.0, 110.0),
		right_throttle = bound (current_flight_dynamics->right_engine_n1_rpm.max, 0.0, 110.0),
		throttle_movement,
		max_movement = THROTTLE_MOVEMENT_RATE * get_delta_time(),
		throttle_angle = 0.0;

	object_3d_sub_instance* cockpit_object = &inst3d->sub_objects[0];

	// left throttle
	if (left_throttle < 60.0)  // idle at -45 deg
		throttle_angle = rad(-45.0);
	else  // otherwise somewhere between -30 and +10 deg
		throttle_angle = rad(-30.0) + rad(40.0 * (left_throttle - 60.0) / 50.0);

	throttle_movement = bound(throttle_angle - cockpit_object->sub_objects[1].relative_pitch, -max_movement, max_movement);

	cockpit_object->sub_objects[1].relative_pitch += throttle_movement;
	cockpit_object->sub_objects[3].relative_pitch += throttle_movement;

	// right throttle
	if (right_throttle < 60.0)  // idle at -45 deg
		throttle_angle = rad(-45.0);
	else  // otherwise somewhere between -30 and +10 deg
		throttle_angle = rad(-30.0) + rad(40.0 * (right_throttle - 60.0) / 50.0);

	throttle_movement = bound(throttle_angle - cockpit_object->sub_objects[2].relative_pitch, -max_movement, max_movement);

	cockpit_object->sub_objects[2].relative_pitch += throttle_movement;
	cockpit_object->sub_objects[4].relative_pitch += throttle_movement;
}

int apache_pnvs_active(void)
{
	static int pnvs_in_position = FALSE;
	
	object_3d_sub_instance* pnvs_object;
	
	if (!night_vision_system_active)
	{
		pnvs_in_position = FALSE;
		return FALSE;
	}

	if (!custom_3d_models.arneh_ah64d_cockpit || pnvs_in_position)
		return TRUE;

	// night vision isn't activated until the PNVS turret has slewed within 5 degrees of pilots head heading
	pnvs_object = &virtual_cockpit_nose_inst3d->sub_objects[0].sub_objects[0];
	pnvs_in_position = pnvs_object->relative_heading > -pilot_head_heading - rad(5.0);

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

	ambient_light_colour.red		 		= 0.7;
	ambient_light_colour.green		  		= 0.7;
	ambient_light_colour.blue		  		= 0.7;

	directional_light_colour.red		= 0.3;
	directional_light_colour.green	= 0.3;
	directional_light_colour.blue		= 0.3;

	directional_light_heading 			= rad (0.0);
	directional_light_pitch 			= rad (0.0);
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
///  Positions and rotates the viewpoint to the correct position for the pilot and view selected
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_apache_crew_viewpoint (viewpoint *crew_viewpoint)
{
	object_3d_sub_instance *head_object;
	int is_copilot = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT;
	int left_mfd_view;

	viewpoint
		vp;

	ASSERT (crew_viewpoint);

	virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

#if 0  // use this if we have an actual 3D head.  not implemented for apache, used for hokum+comanche
	{
		object_3d_sub_object_index_numbers
			index;
	
		object_3d_sub_object_search_data
			search;

		index = OBJECT_3D_SUB_OBJECT_APACHE_COCKPIT_LHS_MFD_CAMERA;
	
		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = index;
	
		if (find_object_3d_sub_object (&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			debug_fatal ("Failed to locate display viewpoint in virtual cockpit");
		}
		
		head_object = search.result_sub_object;
	}
#else
	{
		// arnah - hack!  hardcode which sub-object to use.  I put it there, so I know where it is
		head_object = &virtual_cockpit_inst3d->sub_objects[0].sub_objects[0];
	}
#endif

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	left_mfd_view = get_view_mode() == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD;
	if (left_mfd_view || get_view_mode() == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (is_copilot)
		{
			head_object->relative_position.x = left_mfd_view ? -0.10 : 0.10;
			head_object->relative_position.y = -0.47;
			head_object->relative_position.z =  1.52;
	
			head_object->relative_heading = left_mfd_view ? rad(-4.0) : rad(4.0);
			head_object->relative_pitch = rad(21.0);
		}		
		else
		{
			head_object->relative_position.x = left_mfd_view ? -0.10 : 0.10;
			head_object->relative_position.y = -0.28;
			head_object->relative_position.z =  0.40;
	
			head_object->relative_heading = left_mfd_view ? rad(-4.0) : rad(4.0);
			head_object->relative_pitch = rad(17.0);
		}
	}
	else
	{
		// adjust pitch according to user preferance
		if (edit_wide_cockpit)
			pilot_head_pitch = rad ( wide_cockpit_position[wide_cockpit_nr].p );
	
		// rotate head
		head_object->relative_heading = -pilot_head_heading;
		head_object->relative_pitch = -pilot_head_pitch;
	
		// adjust position according to user preferance
		head_object->relative_position.x = wide_cockpit_position[wide_cockpit_nr].x;
		head_object->relative_position.y = wide_cockpit_position[wide_cockpit_nr].y;
		head_object->relative_position.z = wide_cockpit_position[wide_cockpit_nr].z;
	
		// adjust for track-IR position
		if (query_TIR_active())
		{
			head_object->relative_position.x -= current_custom_cockpit_viewpoint.x;
			head_object->relative_position.y -= current_custom_cockpit_viewpoint.y;
			head_object->relative_position.z -= current_custom_cockpit_viewpoint.z;
		}
	
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

	memcpy (crew_viewpoint, &virtual_cockpit_inst3d->vp, sizeof (viewpoint));
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

//VJ wideview mod, date: 18-mar-03
    char buffer[128];

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
			   vp_position.x = wide_cockpit_position[wide_cockpit_nr].x;
			   vp_position.y = wide_cockpit_position[wide_cockpit_nr].y;
			   vp_position.z = wide_cockpit_position[wide_cockpit_nr].z;
				//VJ 050207 included head pitch in fixed view setting
				pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].p );
				if (edit_wide_cockpit)
					pilot_head_pitch = pilot_head_pitch_datum;
			}
	
			vp_position.x += current_custom_cockpit_viewpoint.x;
			vp_position.y += current_custom_cockpit_viewpoint.y; 
			vp_position.z += current_custom_cockpit_viewpoint.z;
	
			vp_position.x += bound(current_flight_dynamics->model_acceleration_vector.x * ONE_OVER_G, -3.0, 3.0) * 0.025 * command_line_g_force_head_movment_modifier;
			if (!current_flight_dynamics->auto_hover)   // arneh - auto hover has some weird dynamics which cause lots of g-forces, so disable head movement when auto hover is enabled
				vp_position.y += bound(current_flight_dynamics->g_force.value - 1.0, -1.5, 5.0) * 0.025 * command_line_g_force_head_movment_modifier;
	
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

	if (flags & VIRTUAL_COCKPIT_ORT_DISPLAY)
		draw_apache_mfd_on_texture (MFD_LOCATION_ORT);

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_COCKPIT))
	{
		set_cockpit_white_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

#if 0  // arneh - don't clip with the new cockpit
//VJ 050108 wideview x coord used to clip apache cockpit
		if (get_global_wide_cockpit ())
		   clipx = wide_cockpit_position[wide_cockpit_nr].x;
		else
		   clipx = 0;
#endif

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

				memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);
				
				// with new cockpit we have to draw these in internal cockpit
				if (custom_3d_models.arneh_ah64d_cockpit)
				{
					// compass
					{
						search.search_depth = 0;
						search.search_object = virtual_cockpit_compass_inst3d;
						search.sub_object_index = OBJECT_3D_SUB_OBJECT_APACHE_VIRTUAL_COCKPIT_COMPASS_HEADING_NULL;
		
						virtual_cockpit_compass_inst3d->vp.position.y = 0.5;
	
						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
						}
		
						memcpy (&virtual_cockpit_compass_inst3d->vp, &vp, sizeof (viewpoint));
		
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
		
						memcpy (&virtual_cockpit_adi_inst3d->vp, &vp, sizeof (viewpoint));
		
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
		
					memcpy (&virtual_cockpit_instrument_needles_inst3d->vp, &vp, sizeof (viewpoint));
					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_instrument_needles_inst3d->vp.position, virtual_cockpit_instrument_needles_inst3d);
				}
			}

			draw_3d_scene ();

			//VJ wideview mod, date: 18-mar-03
			//VJ 50208 added pilot head pitch
         if (edit_wide_cockpit)
         {
				sprintf(buffer,"APACHE wide cockpit mod edit (set freelook off):");
				ui_display_text (buffer, 10, 40);
				sprintf(buffer,"Y: num 8/2; Z: num 4/6; pitch: num 7/9; Clip: num 1/3/5; Restore: num 0; Ctrl-\\ Leave");
				ui_display_text (buffer, 10, 60);
				sprintf(buffer,"x=%.3f, y=%.3f, z=%.3f, pitch=%.3f, clip=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z, wide_cockpit_position[wide_cockpit_nr].p, clipx);
				ui_display_text (buffer, 10, 100);
				
              
           }

		#if DEBUG_MODULE
           	sprintf(buffer,"x=%.3f y=%.3f z=%.3f", dx, dy, dz);
           	ui_display_text (buffer, 10, 120);
		#endif               

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

  				vp_current_position = vp_position;

				vp_current_position.x += -0.019;
				vp_current_position.y += 0.024;
				vp_current_position.z += -0.042;

				multiply_matrix3x3_vec3d(&vp_world_position, head_rotation, &vp_current_position);

				vp.x = vp_world_position.x;
				vp.y = vp_world_position.y;
				vp.z = vp_world_position.z;

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

			memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

//VJ wideview mod, date: 18-mar-03
	////////////////////////////////////////
	//
	// wide cockpit position edit
	//
	////////////////////////////////////////

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
	if (edit_wide_cockpit)
	{
		int is_copilot = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT;
		//VJ 50208 added pilot head pitch
		if (check_key(DIK_NUMPAD7))
		{
            wide_cockpit_position[wide_cockpit_nr].p += 0.5;
		}
		if (check_key(DIK_NUMPAD9))
		{
            wide_cockpit_position[wide_cockpit_nr].p -= 0.5;
		}
		if (check_key(DIK_NUMPAD6))
		{
            wide_cockpit_position[wide_cockpit_nr].z += 0.01;
            if (wide_cockpit_position[wide_cockpit_nr].z > head_limits[is_copilot][1].z)
            	wide_cockpit_position[wide_cockpit_nr].z = head_limits[is_copilot][1].z;
		}
		if (check_key(DIK_NUMPAD4))
		{
            wide_cockpit_position[wide_cockpit_nr].z -= 0.01;
            if (wide_cockpit_position[wide_cockpit_nr].z < head_limits[is_copilot][0].z)
            	wide_cockpit_position[wide_cockpit_nr].z = head_limits[is_copilot][0].z;
		}
		if (check_key(DIK_NUMPAD8))
		{
            wide_cockpit_position[wide_cockpit_nr].y += 0.01;
            if (wide_cockpit_position[wide_cockpit_nr].y > head_limits[is_copilot][1].y)
            	wide_cockpit_position[wide_cockpit_nr].y = head_limits[is_copilot][1].y;
		}
		if (check_key(DIK_NUMPAD2))
		{
            wide_cockpit_position[wide_cockpit_nr].y -= 0.01;
            if (wide_cockpit_position[wide_cockpit_nr].y < head_limits[is_copilot][0].y)
            	wide_cockpit_position[wide_cockpit_nr].y = head_limits[is_copilot][0].y;
		}
		if (check_key(DIK_NUMPAD1))
		{
            wide_cockpit_position[wide_cockpit_nr].x -= 0.01;
            if (wide_cockpit_position[wide_cockpit_nr].x < head_limits[is_copilot][0].x)
            	wide_cockpit_position[wide_cockpit_nr].x = head_limits[is_copilot][0].x;
		}
		if (check_key(DIK_NUMPAD3))
		{
            wide_cockpit_position[wide_cockpit_nr].x += 0.01;
            if (wide_cockpit_position[wide_cockpit_nr].x > head_limits[is_copilot][1].x)
            	wide_cockpit_position[wide_cockpit_nr].x = head_limits[is_copilot][1].x;
		}
  		if (check_key(DIK_NUMPAD5))
		{
			wide_cockpit_position[wide_cockpit_nr].x = 0.0;
		}

		if (check_key(DIK_NUMPAD0))
		{
				wide_cockpit_position[wide_cockpit_nr].x = BASE_X_APACHE;
				wide_cockpit_position[wide_cockpit_nr].y = BASE_Y_APACHE;
				wide_cockpit_position[wide_cockpit_nr].z = BASE_Z_APACHE;
				wide_cockpit_position[wide_cockpit_nr].p = BASE_P_APACHE;
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

	float
		theta;

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
			   vp_position.x = wide_cockpit_position[wide_cockpit_nr].x;
			   vp_position.y = wide_cockpit_position[wide_cockpit_nr].y;
			   vp_position.z = wide_cockpit_position[wide_cockpit_nr].z;
				//VJ 050207 included head pitch in fixed view setting
	//			pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].p );
	//			if (edit_wide_cockpit)
	//				pilot_head_pitch = pilot_head_pitch_datum;
			}
			
			vp_position.x += current_custom_cockpit_viewpoint.x;
			vp_position.y += current_custom_cockpit_viewpoint.y; 
			vp_position.z += current_custom_cockpit_viewpoint.z;
	
			vp_position.x += bound(current_flight_dynamics->model_acceleration_vector.x * ONE_OVER_G, -3.0, 3.0) * 0.025 * command_line_g_force_head_movment_modifier;
			if (!current_flight_dynamics->auto_hover)   // arneh - auto hover has some weird dynamics which cause lots of g-forces, so disable head movement when auto hover is enabled
				vp_position.y += bound(current_flight_dynamics->g_force.value - 1.0, -1.5, 5.0) * 0.025 * command_line_g_force_head_movment_modifier;
	
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

			// nose

			if (custom_3d_models.arneh_ah64d_cockpit)
			{
				ASSERT(virtual_cockpit_nose_inst3d);
				animate_pnvs(virtual_cockpit_nose_inst3d);
				memcpy (&virtual_cockpit_nose_inst3d->vp, &vp, sizeof (viewpoint));
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

				memcpy (&virtual_cockpit_compass_inst3d->vp, &vp, sizeof (viewpoint));

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

void damage_apache_virtual_cockpit_main_rotors (int seed)
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

void restore_apache_virtual_cockpit_main_rotors (void)
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
