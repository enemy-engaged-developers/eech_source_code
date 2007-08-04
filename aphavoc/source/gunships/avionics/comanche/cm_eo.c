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

eo_params_dynamic_move
	comanche_flir,
	comanche_dtv,
	comanche_dvo;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	eo_ground_stabilisation_value_heading,
	eo_ground_stabilisation_value_pitch;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_comanche_eo (void)
{
	eo_sensor								= TARGET_ACQUISITION_SYSTEM_FLIR;

	eo_azimuth								= rad (0.0);
	eo_min_azimuth							= rad (-120.0);
	eo_max_azimuth							= rad (120.0);
	eo_elevation							= rad (0.0);
	eo_min_elevation						= rad (-60.0);
	eo_max_elevation						= rad (30.0);
	eo_max_visual_range					= 5000.0;
	eo_ground_stabilised					= 0;

#ifdef OLD_EO
	comanche_flir.field_of_view		= EO_FOV_WIDE;
	comanche_flir.min_field_of_view	= EO_FOV_NARROW;
	comanche_flir.max_field_of_view	= EO_FOV_WIDE;

	comanche_dtv.field_of_view			= EO_FOV_NARROW; // Jabberwock 031002 EO_FOV_WIDE; to zoom (out) DTV
	comanche_dtv.min_field_of_view	= EO_FOV_NARROW;
	comanche_dtv.max_field_of_view	= EO_FOV_NARROW; // Jabberwock 031002 EO_FOV_WIDE; to zoom (out) DTV

	comanche_dvo.field_of_view			= EO_FOV_MEDIUM;
	comanche_dvo.min_field_of_view	= EO_FOV_NARROW;
	comanche_dvo.max_field_of_view	= EO_FOV_MEDIUM;
#else
	comanche_flir.zoom					= 1.0;
	comanche_flir.min_zoom				= 1.0;
	comanche_flir.max_zoom				= 1.0 / 128.0;

	comanche_dtv.zoom						= 1.0 / 2.0;
	comanche_dtv.min_zoom				= 1.0 / 2.0; // Jabberwock 031002 1.0 to zoom (out) DTV
	comanche_dtv.max_zoom				= 1.0 / 128.0;

	comanche_dvo.zoom						= 1.0 / 8.0;
	comanche_dvo.min_zoom				= 1.0 / 8.0;
	comanche_dvo.max_zoom				= 1.0 / 128.0;
#endif
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_comanche_eo (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_comanche_eo_centred_viewpoint (viewpoint *vp)
{
	entity
		*source;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	ASSERT (vp);

	source = get_gunship_entity ();

	inst3d = get_local_entity_ptr_value (source, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	get_local_entity_vec3d (source, VEC3D_TYPE_POSITION, &inst3d->vp.position);

	get_local_entity_attitude_matrix (source, inst3d->vp.attitude);

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COMANCHE_EO_CAMERA;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (search.result_sub_object, vp);
	}
	else
	{
		//
		// can happpen if the object is being destroyed
		//

		memcpy (&vp->position, &inst3d->vp.position, sizeof (vec3d));

		debug_log ("OBJECT_3D_SUB_OBJECT_COMANCHE_EO_CAMERA missing from Comanche");
	}

	memcpy (&vp->attitude, &inst3d->vp.attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_comanche_eo_relative_centred_viewpoint (viewpoint *vp)
{
	entity
		*source;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	ASSERT (vp);

	source = get_gunship_entity ();

	inst3d = get_local_entity_ptr_value (source, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	inst3d->vp.x = 0.0;
	inst3d->vp.y = 0.0;
	inst3d->vp.z = 0.0;

	get_local_entity_attitude_matrix (source, inst3d->vp.attitude);

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COMANCHE_EO_CAMERA;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (search.result_sub_object, vp);
	}
	else
	{
		//
		// can happpen if the object is being destroyed
		//

		memcpy (&vp->position, &inst3d->vp.position, sizeof (vec3d));

		debug_log ("OBJECT_3D_SUB_OBJECT_COMANCHE_EO_CAMERA missing from Comanche");
	}

	memcpy (&vp->attitude, &inst3d->vp.attitude, sizeof (matrix3x3));

	//
	// fix up the instance position (just in case)
	//

	get_local_entity_vec3d (source, VEC3D_TYPE_POSITION, &inst3d->vp.position);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void inc_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

#ifdef OLD_EO
	if (eo->field_of_view < eo->max_field_of_view)
	{
		eo->field_of_view++;
	}
#else
	eo->zoom += 0.2;

	if (eo->zoom > 1.0)
	{
		eo->zoom = 1.0;
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fast_inc_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

#ifdef OLD_EO
	eo->field_of_view = eo->max_field_of_view;
#else
	eo->zoom = 1.0;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void dec_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

#ifdef OLD_EO
	if (eo->field_of_view > eo->min_field_of_view)
	{
		eo->field_of_view--;
	}
#else
	eo->zoom -= 0.2;

	if (eo->zoom < 0.0)
	{
		eo->zoom = 0.0;
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fast_dec_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

#ifdef OLD_EO
	eo->field_of_view = eo->min_field_of_view;
#else
	eo->zoom = 0.0;
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void comanche_toggle_ground_stabilisation (void)
{
	if (command_line_ground_stabilisation_available)
	{
		if (eo_ground_stabilised)
		{
			eo_ground_stabilised = 0;
		}
		else
		{
			matrix3x3
				attitude;

			eo_ground_stabilised = 1;

			get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

			eo_ground_stabilisation_value_heading = atan2 (attitude [2][0], attitude [2][2]);

			eo_ground_stabilisation_value_pitch = asin (attitude [2][1]);

//			eo_ground_stabilisation_value_roll = atan2 (-attitude [0][1], attitude [1][1]);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_comanche_eo (eo_params_dynamic_move *eo)
{
	float
		fine_slew_rate,
		medium_slew_rate,
		mouse_slew_rate, // Jabberwock 030930 
		coarse_slew_rate;

	ASSERT (eo);

	////////////////////////////////////////
	//
	// field of view
	//
	////////////////////////////////////////

	while (single_target_acquisition_system_inc_range_key)
	{
		dec_eo_field_of_view (eo);

		single_target_acquisition_system_inc_range_key--;
	}

	while (single_target_acquisition_system_inc_range_fast_key)
	{
		fast_dec_eo_field_of_view (eo);

		single_target_acquisition_system_inc_range_fast_key--;
	}

	////////////////////////////////////////

	while (single_target_acquisition_system_dec_range_key)
	{
		inc_eo_field_of_view (eo);

		single_target_acquisition_system_dec_range_key--;
	}

	while (single_target_acquisition_system_dec_range_fast_key)
	{
		fast_inc_eo_field_of_view (eo);

		single_target_acquisition_system_dec_range_fast_key--;
	}

	////////////////////////////////////////

	while (toggle_ground_stabilisation_key)
	{
		comanche_toggle_ground_stabilisation ();

		toggle_ground_stabilisation_key--;
	}

	////////////////////////////////////////

	if (command_line_eo_zoom_joystick_index != -1)
	{
		long pos = get_joystick_axis (command_line_eo_zoom_joystick_index, command_line_eo_zoom_joystick_axis);
		
		eo->zoom = (pos + 10000) / 20000.0;
	}

	////////////////////////////////////////
	//
	// slew optics
	//
	////////////////////////////////////////

#ifdef OLD_EO
	switch (eo->field_of_view)
	{
		////////////////////////////////////////
		case EO_FOV_NARROW:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (0.05) * get_delta_time ();

			medium_slew_rate = rad (0.25) * get_delta_time ();

			mouse_slew_rate = rad (0.6) * get_delta_time ();	// Jabberwock 030930
			
			coarse_slew_rate = rad (1.0) * get_delta_time ();

			break;
		}
		////////////////////////////////////////
		case EO_FOV_MEDIUM:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (0.5) * get_delta_time ();

			medium_slew_rate = rad (2.5) * get_delta_time ();
			
			mouse_slew_rate = rad (6) * get_delta_time ();	// Jabberwock 030930

			coarse_slew_rate = rad (10.0) * get_delta_time ();

			break;
		}
		////////////////////////////////////////
		case EO_FOV_WIDE:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (4.0) * get_delta_time ();

			medium_slew_rate = rad (20.0) * get_delta_time ();
			
			mouse_slew_rate = rad (48) * get_delta_time ();	// Jabberwock 030930

			coarse_slew_rate = rad (80.0) * get_delta_time ();

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid field of view = %d", eo->field_of_view);

			break;
		}
	}
#else
	{
		float exp_zoom_value = convert_linear_view_value (eo);

		fine_slew_rate = rad (4.0) * exp_zoom_value * get_delta_time ();

		medium_slew_rate = rad (20.0) * exp_zoom_value * get_delta_time ();
		
		mouse_slew_rate = rad (48.0) * exp_zoom_value * get_delta_time ();	// Jabberwock 030930

		coarse_slew_rate = rad (80.0) * exp_zoom_value * get_delta_time ();
	}
#endif

	////////////////////////////////////////

	if (continuous_target_acquisition_system_steer_left_fast_key)
	{
		eo_azimuth -= coarse_slew_rate;

		eo_azimuth = max (eo_azimuth, eo_min_azimuth);
	}
	else if (continuous_target_acquisition_system_steer_left_fine_key)
	{
		eo_azimuth -= fine_slew_rate;

		eo_azimuth = max (eo_azimuth, eo_min_azimuth);
	}
	else if (continuous_target_acquisition_system_steer_left_key)
	{
		eo_azimuth -= medium_slew_rate;

		eo_azimuth = max (eo_azimuth, eo_min_azimuth);
	}

	////////////////////////////////////////

	if (continuous_target_acquisition_system_steer_right_fast_key)
	{
		eo_azimuth += coarse_slew_rate;

		eo_azimuth = min (eo_azimuth, eo_max_azimuth);
	}
	else if (continuous_target_acquisition_system_steer_right_fine_key)
	{
		eo_azimuth += fine_slew_rate;

		eo_azimuth = min (eo_azimuth, eo_max_azimuth);
	}
	else if (continuous_target_acquisition_system_steer_right_key)
	{
		eo_azimuth += medium_slew_rate;

		eo_azimuth = min (eo_azimuth, eo_max_azimuth);
	}

	////////////////////////////////////////

	if (continuous_target_acquisition_system_steer_up_fast_key)
	{
		eo_elevation += coarse_slew_rate;

		eo_elevation = min (eo_elevation, eo_max_elevation);
	}
	else if (continuous_target_acquisition_system_steer_up_fine_key)
	{
		eo_elevation += fine_slew_rate;

		eo_elevation = min (eo_elevation, eo_max_elevation);
	}
	else if (continuous_target_acquisition_system_steer_up_key)
	{
		eo_elevation += medium_slew_rate;

		eo_elevation = min (eo_elevation, eo_max_elevation);
	}

	////////////////////////////////////////

	if (continuous_target_acquisition_system_steer_down_fast_key)
	{
		eo_elevation -= coarse_slew_rate;

		eo_elevation = max (eo_elevation, eo_min_elevation);
	}
	else if (continuous_target_acquisition_system_steer_down_fine_key)
	{
		eo_elevation -= fine_slew_rate;

		eo_elevation = max (eo_elevation, eo_min_elevation);
	}
	else if (continuous_target_acquisition_system_steer_down_key)
	{
		eo_elevation -= medium_slew_rate;

		eo_elevation = max (eo_elevation, eo_min_elevation);
	}
	

	////////////////////////////////////////

	if (continuous_target_acquisition_system_steer_right_fast_key)
	{
		eo_azimuth += coarse_slew_rate;

		eo_azimuth = min (eo_azimuth, eo_max_azimuth);
	}
	else if (continuous_target_acquisition_system_steer_right_fine_key)
	{
		eo_azimuth += fine_slew_rate;

		eo_azimuth = min (eo_azimuth, eo_max_azimuth);
	}
	else if (continuous_target_acquisition_system_steer_right_key)
	{
		eo_azimuth += medium_slew_rate;

		eo_azimuth = min (eo_azimuth, eo_max_azimuth);
	}

	////////////////////////////////////////

	if (continuous_target_acquisition_system_steer_up_fast_key)
	{
		eo_elevation += coarse_slew_rate;

		eo_elevation = min (eo_elevation, eo_max_elevation);
	}
	else if (continuous_target_acquisition_system_steer_up_fine_key)
	{
		eo_elevation += fine_slew_rate;

		eo_elevation = min (eo_elevation, eo_max_elevation);
	}
	else if (continuous_target_acquisition_system_steer_up_key)
	{
		eo_elevation += medium_slew_rate;

		eo_elevation = min (eo_elevation, eo_max_elevation);
	}

	////////////////////////////////////////

		// Jabberwock 030930 - Mouse FLIR control functions
		
		if (mouse_move_left) 
		{
			eo_azimuth -= mouse_slew_rate;
	
			eo_azimuth = max (eo_azimuth, eo_min_azimuth);
			
			mouse_move_left--;
		}
		
		if (mouse_move_right) 
		{
			eo_azimuth += mouse_slew_rate;
		
			eo_azimuth = min (eo_azimuth, eo_max_azimuth);
				
			mouse_move_right--;
		}
		
		if (mouse_move_up) 
		{
			eo_elevation -= medium_slew_rate;
		
			eo_elevation = max (eo_elevation, eo_min_elevation);
				
			mouse_move_up--;
		}
		
		if (mouse_move_down) 
		{
			eo_elevation += medium_slew_rate;
			
			eo_elevation = min (eo_elevation, eo_max_elevation);
					
			mouse_move_down--;
		}
		
		while (mouse_wheel_down)
		{
			
			#ifdef OLD_EO
				if (eo->field_of_view < eo->max_field_of_view)
				{
					eo->field_of_view++;
				}
			#else
				eo->zoom += 0.1;

				if (eo->zoom > 1.0)
				{
					eo->zoom = 1.0;
				}
			#endif

			mouse_wheel_down--;
		}
		
		while (mouse_wheel_up)
		{
			#ifdef OLD_EO
				if (eo->field_of_view > eo->min_field_of_view)
				{
					eo->field_of_view--;
				}
			#else
				eo->zoom -= 0.1;
			
				if (eo->zoom < 0.0)
				{
					eo->zoom = 0.0;
				}
			#endif

			mouse_wheel_up--;
		}
	
		// Jabberwock 030930 ends
	
	////////////////////////////////////////

	// loke 030315
	// added code to allow the user to slew the eo device using joystick axes

	if (command_line_eo_pan_joystick_index != -1)
	{
		float
			panning_offset_horiz,
			panning_offset_vert;

		int
			horizontal_value,
			vertical_value;
		
		horizontal_value = get_joystick_axis (command_line_eo_pan_joystick_index, command_line_eo_pan_horizontal_joystick_axis);

		panning_offset_horiz = make_panning_offset_from_axis (horizontal_value);

		eo_azimuth += panning_offset_horiz * coarse_slew_rate;

		if (panning_offset_horiz > 0)
		{
			eo_azimuth = min (eo_azimuth, eo_max_azimuth);
		}
		else
		{
			eo_azimuth = max (eo_azimuth, eo_min_azimuth);
		}


		vertical_value = get_joystick_axis (command_line_eo_pan_joystick_index, command_line_eo_pan_vertical_joystick_axis);

		panning_offset_vert = make_panning_offset_from_axis (vertical_value);

		eo_elevation -= panning_offset_vert * coarse_slew_rate;

		if (panning_offset_vert < 0)
		{
			eo_elevation = min (eo_elevation, eo_max_elevation);
		}
		else
		{
			eo_elevation = max (eo_elevation, eo_min_elevation);
		}
	}

	////////////////////////////////////////

	// loke 030322
	// handle the ground stabilisation

	if (eo_ground_stabilised)
	{
		matrix3x3
			attitude;

		float
			heading,
			pitch;

		float
			horizontal_pan_offset,
			vertical_pan_offset;

		get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

		heading = atan2 (attitude [2][0], attitude [2][2]);

		pitch = asin (attitude [2][1]);

		horizontal_pan_offset = eo_ground_stabilisation_value_heading - heading;

		eo_azimuth += horizontal_pan_offset;

		if (horizontal_pan_offset > 0)
		{
			eo_azimuth = min (eo_azimuth, eo_max_azimuth);
		}
		else
		{
			eo_azimuth = max (eo_azimuth, eo_min_azimuth);
		}
		

		vertical_pan_offset = eo_ground_stabilisation_value_pitch - pitch;

		eo_elevation += vertical_pan_offset;

		if (vertical_pan_offset > 0)
		{
			eo_elevation = min (eo_elevation, eo_max_elevation);
		}
		else
		{
			eo_elevation = max (eo_elevation, eo_min_elevation);
		}

		eo_ground_stabilisation_value_heading = heading;

		eo_ground_stabilisation_value_pitch = pitch;
	}

	////////////////////////////////////////

	while (single_target_acquisition_system_select_next_target_key)
	{
		select_next_eo_target ();

		single_target_acquisition_system_select_next_target_key--;
	}

	////////////////////////////////////////

	while (single_target_acquisition_system_select_previous_target_key)
	{
		select_previous_eo_target ();

		single_target_acquisition_system_select_previous_target_key--;
	}

// Jabberwock 031107 Designated targets
	
	while (single_target_acquisition_system_select_next_designated_key)
	{
		select_next_designated_eo_target ();

		single_target_acquisition_system_select_next_designated_key--;
	}

	////////////////////////////////////////

	while (single_target_acquisition_system_select_previous_designated_key)
	{
		select_previous_designated_eo_target ();

		single_target_acquisition_system_select_previous_designated_key--;
	}	
// Jabberwock 031107 ends	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void centre_comanche_eo (void)
{
	eo_azimuth = rad (0.0);

	eo_elevation = rad (0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_comanche_eo (object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search_heading;

	ASSERT (inst3d);

	//
	// TADS
	//

	search_heading.search_depth = 0;
	search_heading.search_object = inst3d;
	search_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_RAH66_TADS_HEADING;

	if (find_object_3d_sub_object (&search_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_heading.result_sub_object->relative_heading = eo_azimuth;
	}

	//
	// PNVS
	//

	search_heading.search_depth = 0;
	search_heading.search_object = inst3d;
	search_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_RAH66_PNVS_HEADING;

	if (find_object_3d_sub_object (&search_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_heading.result_sub_object->relative_heading = -pilot_head_heading;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void inc_comanche_eo_zoom(void)
{
	switch (eo_sensor)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
			dec_eo_field_of_view(&comanche_flir);
			break;
		case TARGET_ACQUISITION_SYSTEM_DTV:
			dec_eo_field_of_view(&comanche_dtv);
			break;
		default:
			break;
	}
}

void dec_comanche_eo_zoom(void)
{
	switch (eo_sensor)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
			inc_eo_field_of_view(&comanche_flir);
			break;
		case TARGET_ACQUISITION_SYSTEM_DTV:
			inc_eo_field_of_view(&comanche_dtv);
			break;
		default:
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_comanche_eo_system(void)
{
	switch (eo_sensor)
	{
	case TARGET_ACQUISITION_SYSTEM_FLIR:
		eo_sensor = TARGET_ACQUISITION_SYSTEM_DTV;

		copy_eo_zoom(&comanche_flir, &comanche_dtv);

		if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_FLIR)
			target_acquisition_system = TARGET_ACQUISITION_SYSTEM_DTV;

		break;
	case TARGET_ACQUISITION_SYSTEM_DTV:
		eo_sensor = TARGET_ACQUISITION_SYSTEM_FLIR;

		copy_eo_zoom(&comanche_dtv, &comanche_flir);

		if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DTV)
			target_acquisition_system = TARGET_ACQUISITION_SYSTEM_FLIR;

		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void slave_comanche_eo_to_current_target (void)
{
/*	if (eo_on_target)
	{
		switch (eo_sensor)
		{
			case TARGET_ACQUISITION_SYSTEM_FLIR:
			{
#ifdef OLD_EO
				comanche_flir.field_of_view = comanche_flir.min_field_of_view;
#else
				comanche_flir.zoom = 0.0;
#endif

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DTV:
			{
#ifdef OLD_EO
				comanche_dtv.field_of_view = comanche_dtv.min_field_of_view;
#else
				comanche_dtv.zoom = 0.0;
#endif

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DVO:
			{
#ifdef OLD_EO
				comanche_dvo.field_of_view = comanche_dvo.min_field_of_view;
#else
				comanche_dvo.zoom = 0.0;
#endif

				break;
			}
		}
	}
	else
	{
		switch (eo_sensor)
		{
			case TARGET_ACQUISITION_SYSTEM_FLIR:
			{
#ifdef OLD_EO
				comanche_flir.field_of_view = comanche_flir.max_field_of_view;
#else
				comanche_flir.zoom = 1.0;
#endif

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DTV:
			{
#ifdef OLD_EO
				comanche_dtv.field_of_view = comanche_dtv.max_field_of_view;
#else
				comanche_dtv.zoom = 1.0;
#endif

				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DVO:
			{
#ifdef OLD_EO
				comanche_dvo.field_of_view = comanche_dvo.max_field_of_view;
#else
				comanche_dvo.zoom = 1.0;
#endif

				break;
			}
		}
	}*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
