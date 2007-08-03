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

eo_params
	apache_flir,
	apache_dtv,
	apache_dvo;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_eo (void)
{
	eo_sensor							= TARGET_ACQUISITION_SYSTEM_FLIR;

	eo_azimuth							= rad (0.0);
	eo_min_azimuth						= rad (-120.0);
	eo_max_azimuth						= rad (120.0);
	eo_elevation						= rad (0.0);
	eo_min_elevation					= rad (-60.0);
	eo_max_elevation					= rad (30.0);
	eo_max_visual_range				= 6000.0;

	apache_flir.field_of_view		= EO_FOV_WIDE;
	apache_flir.min_field_of_view	= EO_FOV_ZOOM;
	apache_flir.max_field_of_view	= EO_FOV_WIDE;

	apache_dtv.field_of_view		= EO_FOV_MEDIUM;
	apache_dtv.min_field_of_view	= EO_FOV_NARROW;
	apache_dtv.max_field_of_view	= EO_FOV_MEDIUM;

	apache_dvo.field_of_view		= EO_FOV_MEDIUM;
	apache_dvo.min_field_of_view	= EO_FOV_MEDIUM;
	apache_dvo.max_field_of_view	= EO_FOV_WIDE;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_apache_eo (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_apache_eo_centred_viewpoint (viewpoint *vp)
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
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_AH64D_TADS_HEADING;

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

		debug_log ("OBJECT_3D_SUB_OBJECT_AH64D_TADS_HEADING missing from Apache");
	}

	memcpy (&vp->attitude, &inst3d->vp.attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void inc_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	if (eo->field_of_view < eo->max_field_of_view)
	{
		eo->field_of_view++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fast_inc_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	eo->field_of_view = eo->max_field_of_view;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void dec_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	if (eo->field_of_view > eo->min_field_of_view)
	{
		eo->field_of_view--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fast_dec_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	eo->field_of_view = eo->min_field_of_view;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_apache_eo (eo_params *eo)
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
	//
	// slew optics
	//
	////////////////////////////////////////

	switch (eo->field_of_view)
	{
		////////////////////////////////////////
		case EO_FOV_ZOOM:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (0.1) * get_delta_time ();

			medium_slew_rate = rad (0.5) * get_delta_time ();

			mouse_slew_rate = rad (1.2) * get_delta_time ();	// Jabberwock 030930
			
			coarse_slew_rate = rad (2.0) * get_delta_time ();

			break;
		}
		////////////////////////////////////////
		case EO_FOV_NARROW:
		////////////////////////////////////////
		{
			fine_slew_rate = rad (0.25) * get_delta_time ();

			medium_slew_rate = rad (1.0) * get_delta_time ();

			mouse_slew_rate = rad (2.0) * get_delta_time ();	// Jabberwock 030930
			
			coarse_slew_rate = rad (4.0) * get_delta_time ();

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

		if (eo->field_of_view < eo->max_field_of_view)
		{
			eo->field_of_view++;
		}

		mouse_wheel_down--;
	}

	while (mouse_wheel_up)
	{
		if (eo->field_of_view > eo->min_field_of_view)
		{
			eo->field_of_view--;
		}

		mouse_wheel_up--;
	}

	// Jabberwock 030930 ends

	////////////////////////////////////////

	// Retro 31Oct2004 - copy+paste of loke's comanche EO slew code
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void centre_apache_eo (void)
{
	eo_azimuth = rad (0.0);

	eo_elevation = rad (0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_apache_eo (object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search_heading,
		search_pitch;

	ASSERT (inst3d);

	//
	// TADS
	//

	search_heading.search_depth = 0;
	search_heading.search_object = inst3d;
	search_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_AH64D_TADS_HEADING;

	if (find_object_3d_sub_object (&search_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_heading.result_sub_object->relative_heading = eo_azimuth;

		search_pitch.search_depth = 0;
		search_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_AH64D_TADS_PITCH;

		if (find_object_3d_sub_object_from_sub_object (&search_heading, &search_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search_pitch.result_sub_object->relative_pitch = -eo_elevation;
		}
	}

	//
	// PNVS
	//

	search_heading.search_depth = 0;
	search_heading.search_object = inst3d;
	search_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_AH64D_PNVS_HEADING;

	if (find_object_3d_sub_object (&search_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_heading.result_sub_object->relative_heading = -pilot_head_heading;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void slave_apache_eo_to_current_target (void)
{
	if (eo_on_target)
	{
		switch (eo_sensor)
		{
			case TARGET_ACQUISITION_SYSTEM_FLIR:
			{
				apache_flir.field_of_view = apache_flir.min_field_of_view;
				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DTV:
			{
				apache_dtv.field_of_view = apache_dtv.min_field_of_view;
				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DVO:
			{
				apache_dvo.field_of_view = apache_dvo.min_field_of_view;
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
				apache_flir.field_of_view = apache_flir.max_field_of_view;
				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DTV:
			{
				apache_dtv.field_of_view = apache_dtv.max_field_of_view;
				break;
			}
			case TARGET_ACQUISITION_SYSTEM_DVO:
			{
				apache_dvo.field_of_view = apache_dvo.max_field_of_view;
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
