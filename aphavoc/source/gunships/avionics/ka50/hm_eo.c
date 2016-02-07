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
#define OLD_EO

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
eo_params
	ka50_llltv;
#else
eo_params_dynamic_move
	ka50_llltv;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ka50_eo (void)
{
	eo_sensor									= TARGET_ACQUISITION_SYSTEM_LLLTV;

	eo_azimuth									= rad (0.0);
	eo_min_azimuth								= rad (-35.0);
	eo_max_azimuth								= rad (35.0);
	eo_elevation								= rad (0.0);
	eo_min_elevation							= rad (-80.0);
	eo_max_elevation							= rad (15.0);
	eo_max_visual_range						= 5000.0,
	eo_ground_stabilised					= 0;

#ifdef OLD_EO
	ka50_llltv.field_of_view				= EO_FOV_MEDIUM;
	ka50_llltv.min_field_of_view			= EO_FOV_NARROW;
	ka50_llltv.max_field_of_view			= EO_FOV_MEDIUM;
#else
	ka50_llltv.zoom							= 1/7.0;
	ka50_llltv.min_zoom						= 1/7.0;
	ka50_llltv.max_zoom						= 1/23.0;
#endif
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ka50_eo (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ka50_eo_centred_viewpoint (viewpoint *vp)
{
	entity
		*source;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	ASSERT (vp);

	source = get_gunship_entity ();

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (source, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	get_local_entity_vec3d (source, VEC3D_TYPE_POSITION, &inst3d->vp.position);

	get_local_entity_attitude_matrix (source, inst3d->vp.attitude);

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_SAMSHIT_VIEWPOINT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (&search, vp);
	}
	else
	{
		//
		// can happpen if the object is being destroyed
		//

		memcpy (&vp->position, &inst3d->vp.position, sizeof (vec3d));

		debug_log ("OBJECT_3D_SUB_OBJECT_KA52_SAMSHIT_VIEWPOINT missing from Ka-50");
	}

	memcpy (&vp->attitude, &inst3d->vp.attitude, sizeof (matrix3x3));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ka50_eo_relative_centred_viewpoint (viewpoint *vp)
{
	entity
		*source;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	ASSERT (vp);

	source = get_gunship_entity ();

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (source, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	inst3d->vp.position.x = 0.0;
	inst3d->vp.position.y = 0.0;
	inst3d->vp.position.z = 0.0;

	get_local_entity_attitude_matrix (source, inst3d->vp.attitude);

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_SAMSHIT_VIEWPOINT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (&search, vp);
	}
	else
	{
		//
		// can happpen if the object is being destroyed
		//

		memcpy (&vp->position, &inst3d->vp.position, sizeof (vec3d));

		debug_log ("OBJECT_3D_SUB_OBJECT_KA52_SAMSHIT_VIEWPOINT missing from Ka-50");
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

#ifdef OLD_EO
static void inc_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	if (eo->field_of_view < eo->max_field_of_view)
	{
		eo->field_of_view++;
	}
}
#else
static void inc_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

	eo->zoom += 0.2;

	if (eo->zoom > 1.0)
	{
		eo->zoom = 1.0;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
static void fast_inc_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	eo->field_of_view = eo->max_field_of_view;
}
#else
static void fast_inc_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

	eo->zoom = 1.0;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
static void dec_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	if (eo->field_of_view > eo->min_field_of_view)
	{
		eo->field_of_view--;
	}
}
#else
static void dec_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

	eo->zoom -= 0.2;

	if (eo->zoom < 0.0)
	{
		eo->zoom = 0.0;
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
static void fast_dec_eo_field_of_view (eo_params *eo)
{
	ASSERT (eo);

	eo->field_of_view = eo->min_field_of_view;
}
#else
static void fast_dec_eo_field_of_view (eo_params_dynamic_move *eo)
{
	ASSERT (eo);

	eo->zoom = 0.0;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OLD_EO
void update_ka50_eo (eo_params *eo)
#else
void update_ka50_eo (eo_params_dynamic_move *eo)
#endif
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
		toggle_ground_stabilisation ();

		toggle_ground_stabilisation_key--;
	}

	////////////////////////////////////////

#ifndef OLD_EO
	if (command_line_eo_zoom_joystick_index != -1)
	{
		long pos = get_joystick_axis (command_line_eo_zoom_joystick_index, command_line_eo_zoom_joystick_axis);

		eo->zoom = (pos + 10000) / 20000.0;
	}
#endif

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

		mouse_slew_rate = rad (48) * exp_zoom_value * get_delta_time ();	// Jabberwock 030930

		coarse_slew_rate = rad (80.0) * exp_zoom_value * get_delta_time ();
	}
#endif

	////////////////////////////////////////

	keyboard_slew_eo_system(fine_slew_rate, medium_slew_rate, coarse_slew_rate);

	if ( command_line_eo_pan_joystick_index == -1 )
	{						
		float ROTATE_RATE = (float) command_line_mouse_look_speed / 5.0;

		eo_azimuth = get_eo_azimuth (ROTATE_RATE, coarse_slew_rate, eo_azimuth, eo_min_azimuth, eo_max_azimuth, mouse_slew_rate);
		eo_elevation = get_eo_elevation (ROTATE_RATE, coarse_slew_rate, eo_elevation, eo_min_elevation, eo_max_elevation, mouse_slew_rate);
	}

#ifdef OLD_EO
	eo->field_of_view = get_old_eo_zoom(eo->field_of_view, eo->max_field_of_view, eo->min_field_of_view);
#else
	if (command_line_eo_zoom_joystick_index == -1 && (command_line_mouse_look != MOUSELOOK_ON || command_line_field_of_view_joystick_index != -1))
		eo->zoom = get_new_eo_zoom(eo->zoom);
#endif

	////////////////////////////////////////
	// loke 030315
	// added code to allow the user to slew the eo device using joystick axes

	joystick_slew_eo_system(medium_slew_rate);

	////////////////////////////////////////

	// loke 030322
	// handle the ground stabilisation

	if (eo_ground_stabilised)
	{
		handle_ground_stabilisation();
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
}
// Jabberwock 031107 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void centre_ka50_eo (void)
{
	eo_azimuth = rad (0.0);

	eo_elevation = rad (0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_ka50_eo (object_3d_instance *inst3d)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_ka50_virtual_cockpit_eo (object_3d_instance *inst3d)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void inc_ka50_eo_zoom(void)
{
	switch (eo_sensor)
	{
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
			dec_eo_field_of_view(&ka50_llltv);
			break;
		default:
			break;
	}
}

void dec_ka50_eo_zoom(void)
{
	switch (eo_sensor)
	{
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
			inc_eo_field_of_view(&ka50_llltv);
			break;
		default:
			break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void slave_ka50_eo_to_current_target (void)
{
	if (command_line_manual_laser_radar)
		return;

	if (eo_on_target)
	{
		switch (eo_sensor)
		{
			case TARGET_ACQUISITION_SYSTEM_LLLTV:
			{
#ifdef OLD_EO
				ka50_llltv.field_of_view = ka50_llltv.min_field_of_view;
#else
				ka50_llltv.zoom = 0.0;
#endif
				break;
			}
		}
	}
	else
	{
		switch (eo_sensor)
		{
			case TARGET_ACQUISITION_SYSTEM_LLLTV:
			{
#ifdef OLD_EO
				ka50_llltv.field_of_view = ka50_llltv.min_field_of_view;
#else
				ka50_llltv.zoom = 0.0;
#endif
				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef OLD_EO
