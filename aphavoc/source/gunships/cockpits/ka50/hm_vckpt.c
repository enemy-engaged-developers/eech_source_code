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
#include "../../dynamics/common/co_undercarriage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static object_3d_instance
	*virtual_cockpit_inst3d_detail_level_high_inst3d,
	*virtual_cockpit_inst3d_detail_level_medium_inst3d,
	*virtual_cockpit_inst3d_detail_level_low_inst3d,
	*virtual_cockpit_inst3d_detail_level_glass_inst3d;

static object_3d_sub_instance
	*left_temperature,
	*left_temperature_small,
	*right_temperature,
	*right_temperature_small,

	// lamps
	*left_wheel_down_light,
	*right_wheel_down_light,
	*nose_wheel_down_light,
	*wheels_up_light,
	*rotor_rpm_light,
	*leng_rpm_light,
	*reng_rpm_light,
	*gmax_light,
	*max_isa_light,
	*fire_light,
	*master_alarm,
	*left_outer_wep_light,
	*left_inner_wep_light,
	*right_inner_wep_light,
	*right_outer_wep_light,
	*left_outer_wep_store_light,
	*left_inner_wep_store_light,
	*right_inner_wep_store_light,
	*right_outer_wep_store_light;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ka50_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	virtual_cockpit_inst3d_detail_level_high_inst3d = construct_3d_object (OBJECT_3D_KA50_COCKPIT);

	virtual_cockpit_inst3d_detail_level_medium_inst3d = construct_3d_object (OBJECT_3D_KA50_COCKPIT);

	virtual_cockpit_inst3d_detail_level_low_inst3d = construct_3d_object (OBJECT_3D_KA50_COCKPIT);

	virtual_cockpit_inst3d_detail_level_glass_inst3d = construct_3d_object (OBJECT_3D_KA50_COCKPIT);

	virtual_cockpit_inst3d = virtual_cockpit_inst3d_detail_level_high_inst3d;

	pilot_head_pitch_datum = get_ka50_pilot_head_pitch_datum ();

	left_temperature = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_ENG1_TEMP_LRG);
	left_temperature_small = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_ENG1_TEMP_SML);
	right_temperature = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_ENG2_TEMP_LRG);
	right_temperature_small = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_ENG2_TEMP_SML);

	//
	// Lamps
	//

	left_wheel_down_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_WHEEL_DOWN_LIGHT);
	right_wheel_down_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_WHEEL_DOWN_LIGHT);
	nose_wheel_down_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_NOSE_WHEEL_DOWN_LIGHT);
	wheels_up_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WHEELS_UP_LIGHT);
	leng_rpm_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_LENG_RPM_LAMP);
	reng_rpm_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_RENG_RPM_LAMP);
	rotor_rpm_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_ROTOR_RPM_LAMP);
	gmax_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_G_LIMIT_LAMP);
	max_isa_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_MAX_ISA_LAMP);
	fire_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_FIRE_LAMP);
	master_alarm = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_MASTER_ALARM_LAMP);

	left_outer_wep_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_LO_WEP_LAMP);
	left_inner_wep_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_LI_WEP_LAMP);
	right_inner_wep_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_RI_WEP_LAMP);
	right_outer_wep_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_RO_WEP_LAMP);
	left_outer_wep_store_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_LO_WEP_STORE_LAMP);
	left_inner_wep_store_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_LI_WEP_STORE_LAMP);
	right_inner_wep_store_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_RI_WEP_STORE_LAMP);
	right_outer_wep_store_light = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_RO_WEP_STORE_LAMP);

//	// Gear lever
//	gear_lever = find_sub_object(virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_BLACKSHARK_GEAR_LEVER);

	//
	// wipers and rain
	//

	initialise_ka50_virtual_cockpit_wiper_and_rain_effect ();

	//
	// crew animation
	//

	initialise_ka50_crew_animation ();

	//
	// canopy doors
	//

	initialise_ka50_virtual_cockpit_canopy_doors ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();

//VJ 050208 cleaing up wideview
	wide_cockpit_nr = WIDEVIEW_KA50_PILOT;

//VJ wideview mod, date: 20-mar-03
//start up in normal view because when you switch to wideview the parameters are read
	set_global_wide_cockpit (FALSE);
	
	// set up cockpit light
	{
		cockpit_light_colors colors[] = {COCKPIT_LIGHT_NONE, COCKPIT_LIGHT_YELLOW, COCKPIT_LIGHT_BLUE};
		initialise_cockpit_lights(colors, 3);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ka50_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	destruct_3d_object (virtual_cockpit_inst3d_detail_level_high_inst3d);

	destruct_3d_object (virtual_cockpit_inst3d_detail_level_medium_inst3d);

	destruct_3d_object (virtual_cockpit_inst3d_detail_level_low_inst3d);

	destruct_3d_object (virtual_cockpit_inst3d_detail_level_glass_inst3d);

	virtual_cockpit_inst3d = NULL;

	//
	// wipers and rain
	//

	deinitialise_ka50_virtual_cockpit_wiper_and_rain_effect ();

	//
	// crew animation
	//

	deinitialise_ka50_crew_animation ();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();
	
	clear_head_movement_data();

	// remove cockpit lights
	deinitialise_cockpit_lights();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_ka50_virtual_cockpit (void)
{
	int
		draw_glass_cockpit,
		draw_controls, tmp_draw_controls,
		draw_crew,
		draw_seats;

	cockpit_detail_levels
		cockpit_detail_level;

	object_3d_sub_object_search_data
		search;

	update_gear_lamps();
	update_blackshark_warning_lamps();
	update_weapon_status_lamps();

	////////////////////////////////////////
	//
	// sort out what to draw
	//
	////////////////////////////////////////

	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		{
			cockpit_detail_level = COCKPIT_DETAIL_LEVEL_HIGH;

			draw_glass_cockpit = FALSE;

			draw_controls = TRUE;

			break;
		}
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			cockpit_detail_level = COCKPIT_DETAIL_LEVEL_HIGH;

			draw_glass_cockpit = FALSE;

			draw_controls = FALSE;

			break;
		}
		default:
		{
			cockpit_detail_level = get_global_cockpit_detail_level ();

			draw_glass_cockpit = get_global_glass_cockpit ();

			draw_controls = !draw_glass_cockpit;

			break;
		}
	}

	//
	// select 3D instance
	//

	if (draw_glass_cockpit)
	{
		if (virtual_cockpit_inst3d != virtual_cockpit_inst3d_detail_level_glass_inst3d)
		{
			virtual_cockpit_inst3d_detail_level_glass_inst3d->vp = virtual_cockpit_inst3d->vp;

			virtual_cockpit_inst3d = virtual_cockpit_inst3d_detail_level_glass_inst3d;
		}

		draw_crew = FALSE;
	}
	else
	{
		switch (cockpit_detail_level)
		{
			////////////////////////////////////////
			case COCKPIT_DETAIL_LEVEL_LOW:
			////////////////////////////////////////
			{
				if (virtual_cockpit_inst3d != virtual_cockpit_inst3d_detail_level_low_inst3d)
				{
					virtual_cockpit_inst3d_detail_level_low_inst3d->vp = virtual_cockpit_inst3d->vp;

					virtual_cockpit_inst3d = virtual_cockpit_inst3d_detail_level_low_inst3d;
				}

				draw_crew = FALSE;

				break;
			}
			////////////////////////////////////////
			case COCKPIT_DETAIL_LEVEL_MEDIUM:
			////////////////////////////////////////
			{
				if (virtual_cockpit_inst3d != virtual_cockpit_inst3d_detail_level_medium_inst3d)
				{
					virtual_cockpit_inst3d_detail_level_medium_inst3d->vp = virtual_cockpit_inst3d->vp;

					virtual_cockpit_inst3d = virtual_cockpit_inst3d_detail_level_medium_inst3d;
				}

				draw_crew = TRUE;

				break;
			}
			////////////////////////////////////////
			case COCKPIT_DETAIL_LEVEL_HIGH:
			////////////////////////////////////////
			{
				if (virtual_cockpit_inst3d != virtual_cockpit_inst3d_detail_level_high_inst3d)
				{
					virtual_cockpit_inst3d_detail_level_high_inst3d->vp = virtual_cockpit_inst3d->vp;

					virtual_cockpit_inst3d = virtual_cockpit_inst3d_detail_level_high_inst3d;
				}

				draw_crew = TRUE;

				break;
			}
		}
	}

	//
	// HUD view
	//

	//
	// ejected
	//

	draw_seats = TRUE;

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
	{
		if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CREW)
		{
			draw_controls = FALSE;
		}
		else
		{
			draw_crew = FALSE;

			draw_seats = FALSE;
		}
	}

	//
	// draw crew
	//

//VJ 050206: wideview improvement show other pilot when in wideview
	draw_crew = !(get_global_wide_cockpit () && wide_cockpit_nr == WIDEVIEW_KA50_PILOT);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_POSITION;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_crew;
	}

	//
	// draw seats
	//

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_EJECTOR_SEAT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_seats;
	}

	search.search_depth = 1;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_EJECTOR_SEAT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_seats;
	}

	//
	// draw controls
	//

//VJ 050206 wideview improvement
	tmp_draw_controls = draw_controls;
	draw_controls = !(get_global_wide_cockpit () && wide_cockpit_nr == WIDEVIEW_KA50_PILOT);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_JOYSTICK;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

//VJ 050206 wideview improvement
	draw_controls = tmp_draw_controls;

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_COLLECTIVE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_PEDAL;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

	search.search_depth = 1;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_PEDAL;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

	////////////////////////////////////////
	//
	// update animations
	//
	////////////////////////////////////////

	//
	// crew animation
	//

	update_ka50_crew_animation ();

	//
	// canopy doors
	//

	animate_ka50_virtual_cockpit_canopy_doors ();

	////////////////////////////////////////
	//
	// sort static hands
	//
	////////////////////////////////////////

	if (!draw_crew)
	{
		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_HAND_STATIC;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_render_ka50_virtual_cockpit_displays (void)
{
	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			break;
		}
		default:
		{
			if (!get_global_draw_cockpit_graphics ())
			{
				return;
			}

			break;
		}
	}

	draw_ka50_mfd ();

	draw_ka50_hud ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_virtual_cockpit (void)
{
	int
		draw_main_rotors;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			break;
		}
		default:
		{
			if (!get_global_draw_cockpit_graphics ())
			{
				draw_external_ka50_hud ();

				return;
			}

			break;
		}
	}

	draw_ka50_virtual_cockpit_instruments ();

	get_ka50_temperature_needle_values(current_flight_dynamics->left_engine_temp.value, &left_temperature->relative_roll, &left_temperature_small->relative_roll);
	get_ka50_temperature_needle_values(current_flight_dynamics->right_engine_temp.value, &right_temperature->relative_roll, &right_temperature_small->relative_roll);

	//
	// crew animation
	//

	set_ka50_crew_head_positions ();

	//
	// animate main rotors
	//

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d, inst3d);

	draw_main_rotors = TRUE;

	if (get_global_glass_cockpit ())
	{
		draw_main_rotors = FALSE;
	}
	else
	{
		if (get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CREW)
		{
			if (get_helicopter_main_rotors_blurred (get_gunship_entity ()))
			{
				if (!get_global_blurred_main_rotors_visible_from_cockpit ())
				{
					draw_main_rotors = FALSE;
				}
			}
		}
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_main_rotors;
	}

	search.search_depth = 1;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_main_rotors;
	}

	//
	// animate electro-optics
	//

	animate_ka50_virtual_cockpit_eo (virtual_cockpit_inst3d);

	//
	// animate wipers
	//

	animate_ka50_wipers (virtual_cockpit_inst3d);

#ifndef OGRE_EE
	//
	// draw 3D scene
	//

	set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

	realise_3d_clip_extents (main_3d_env);

	recalculate_3d_environment_settings (main_3d_env);

	clear_zbuffer_screen ();

	if (begin_3d_scene ())
	{
		//
		// light direction is in world coordinates
		//

		light_3d_source
			*display_backlight,
			*cockpit_light;

		vec3d
			direction;

		float
			mfd_light_power = 0.0;

//VJ 050131 update on wideview mod, much better movement
		if (get_global_wide_cockpit () &&
	    (get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY)
	   )
		{
			get_ka50_crew_viewpoint ();

			virtual_cockpit_inst3d->vp.x += wide_cockpit_position[wide_cockpit_nr].c.x;
			virtual_cockpit_inst3d->vp.y += wide_cockpit_position[wide_cockpit_nr].c.y;
			virtual_cockpit_inst3d->vp.z += wide_cockpit_position[wide_cockpit_nr].c.z;

			if (wide_cockpit_nr == WIDEVIEW_KA50_PILOT)
				pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].c.p );

		  	set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);
		}

		//ataribaby 27/12/2008 new head g-force movement and vibration from main rotor
		if (get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY &&
  	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY &&
  	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY &&
  	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY)
			get_forces_acting_on_pilot(&virtual_cockpit_inst3d->vp.x, &virtual_cockpit_inst3d->vp.y, &virtual_cockpit_inst3d->vp.z, FALSE, TRUE);

		// set cockpit lights

		mfd_light_power = (float)(get_ka50_mfd_mode(KA50_MFD_LOCATION_SHKVAL) % NUM_KA50_MFD_LOCATIONS + !!get_ka50_mfd_mode(KA50_MFD_LOCATION_SHKVAL) + 
					get_ka50_mfd_mode(KA50_MFD_LOCATION_ABRIS) % NUM_KA50_MFD_LOCATIONS + !!get_ka50_mfd_mode(KA50_MFD_LOCATION_ABRIS))
					/ (float)(NUM_KA50_MFD_LOCATIONS * NUM_KA50_MFD_LOCATIONS);
		
		ASSERT(mfd_light_power >= 0.0 && mfd_light_power <= 1.0);
		
		if (mfd_light_power)
		{
			direction = get_cockpit_backlight_direction();
			display_backlight = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.244 * mfd_light_power, 0.306 * mfd_light_power, 0.278 * mfd_light_power); 
			insert_light_3d_source_into_3d_scene (display_backlight);
		}

		if (electrical_system_active() || cockpit_light_color_array[cockpit_light_color_index[0]] == COCKPIT_LIGHT_NONE)
		{
			light_colour cockpit_light_color = cockpit_light_color_table[cockpit_light_color_array[cockpit_light_color_index[0]]];
			direction = get_cockpit_light_direction();
			cockpit_light = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, cockpit_light_color.red, cockpit_light_color.green, cockpit_light_color.blue);
			insert_light_3d_source_into_3d_scene (cockpit_light);
		}

		disable_normals_specularity = TRUE;

		insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

		draw_3d_scene ();

		print_edit_wide_cockpit ();
		print_repairing_status();

		end_3d_scene ();

		// clear cockpit lights
		
		if (mfd_light_power)
		{
			remove_light_3d_source_from_3d_scene (display_backlight);
			destroy_light_3d_source (display_backlight);
		}

		if (electrical_system_active() || cockpit_light_color_array[cockpit_light_color_index[0]] == COCKPIT_LIGHT_NONE)
		{
			remove_light_3d_source_from_3d_scene (cockpit_light);
			destroy_light_3d_source (cockpit_light);
		}

		disable_normals_specularity = FALSE;
	}

	move_edit_wide_cockpit ();


#if RECOGNITION_GUIDE
	set_3d_view_distances (main_3d_env, 10000.0, 100.0, 1.0, 0.0);
#else
	set_3d_view_distances (main_3d_env, 10000.0, 1.0, 1.0, 0.0);
#endif

	realise_3d_clip_extents (main_3d_env);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ka50_crew_viewpoint (void)
{
	object_3d_sub_object_search_data
		search_head,
		search_viewpoint;

	viewpoint
		vp;

	float
		head_pitch_datum;

	//
	// select head
	//

	search_head.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_HEAD;

	search_viewpoint.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_VIEWPOINT;

	head_pitch_datum = pilot_head_pitch_datum;

	//
	// rotate head
	//

	search_head.search_depth = 0;
	search_head.search_object = virtual_cockpit_inst3d;

	if (find_object_3d_sub_object (&search_head) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_head.result_sub_object->relative_heading = -pilot_head_heading;
		search_head.result_sub_object->relative_pitch = head_pitch_datum - pilot_head_pitch;

		if ((command_line_TIR_6DOF == TRUE)&&(query_TIR_active() == TRUE))	// Retro 6Feb2005
			search_head.result_sub_object->relative_roll = TIR_GetRoll() / 16383. * PI / 2.;	// Retro 6Feb2005
		else
			search_head.result_sub_object->relative_roll = 0.0;
	}
	else
	{
		debug_fatal ("Failed to locate crew's head in virtual cockpit");
	}

	//
	// get viewpoint (avoid jitter)
	//

	search_viewpoint.search_object = virtual_cockpit_inst3d;
	search_viewpoint.search_depth = 0;

	if (find_object_3d_sub_object (&search_viewpoint) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		virtual_cockpit_inst3d->vp.position.x = 0.0;
		virtual_cockpit_inst3d->vp.position.y = 0.0;
		virtual_cockpit_inst3d->vp.position.z = 0.0;

		get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

		get_3d_sub_object_world_viewpoint (&search_viewpoint, &vp);

		get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

		pilot_head_vp.x += vp.x;
		pilot_head_vp.y += vp.y;
		pilot_head_vp.z += vp.z;

		if ((command_line_TIR_6DOF == TRUE)&&(query_TIR_active() == TRUE))	// Retro 6Feb2005 (whole block)
		{
			matrix3x3 invAttitude;
			vec3d
				shiftVP, shiftWorld;

			// First lets find out the displacement the user wants.. this is in the user's viewsystem coords !!
			// Now store this info in a temp vect3d..
			shiftVP.x = current_custom_cockpit_viewpoint.x;
			shiftVP.y = current_custom_cockpit_viewpoint.y;
			shiftVP.z = current_custom_cockpit_viewpoint.z;

			// Now we need to convert our vec3d into world coords.. for this we need the inverse of the viewpoint attitude matrix..
			get_inverse_matrix (invAttitude, vp.attitude);
			// And rotate ! Voila, the result vec3d is now in world coords..
			multiply_transpose_matrix3x3_vec3d (&shiftWorld, invAttitude, &shiftVP);
			// Now apply that displacement.. BUT ONLY TO THE HEAD !!
			pilot_head_vp.x -= shiftWorld.x;
			pilot_head_vp.y -= shiftWorld.y;
			pilot_head_vp.z -= shiftWorld.z;
		}

		memcpy (pilot_head_vp.attitude, vp.attitude, sizeof (matrix3x3));

		vp.x = -vp.x;
		vp.y = -vp.y;
		vp.z = -vp.z;

		multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, pilot_head_vp.attitude, &vp.position);

		if ((command_line_TIR_6DOF == TRUE)&&(query_TIR_active() == TRUE))	// Retro 6Feb2005 (whole block)
		{
			// Now shift the viewpoint (AND the model) by the positive displacement.. puts the cockpit back were it belongs..
			// but the viewpoint (the head) is in another place.. fini
			virtual_cockpit_inst3d->vp.position.x += current_custom_cockpit_viewpoint.x;
			virtual_cockpit_inst3d->vp.position.y += current_custom_cockpit_viewpoint.y;
			virtual_cockpit_inst3d->vp.position.z += current_custom_cockpit_viewpoint.z;
		}
	}
	else
	{
		debug_fatal ("Failed to locate crew's viewpoint in virtual cockpit");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_ka50_display_viewpoint (view_modes mode)
{
	object_3d_sub_object_index_numbers
		index;

	object_3d_sub_object_search_data
		search;

	vec3d
		position;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_inst3d);

	switch (mode)
	{
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_2;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_LHS_1;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_1;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RHS_2;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid view mode = %d", mode);

			break;
		}
	}

	virtual_cockpit_inst3d->vp.position.x = 0.0;
	virtual_cockpit_inst3d->vp.position.y = 0.0;
	virtual_cockpit_inst3d->vp.position.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = index;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (&search, &main_vp);
	}
	else
	{
		debug_fatal ("Failed to locate display viewpoint in virtual cockpit");
	}

	position.x = -main_vp.x;
	position.y = -main_vp.y;
	position.z = -main_vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, main_vp.attitude, &position);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	main_vp.x += position.x;
	main_vp.y += position.y;
	main_vp.z += position.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_gear_lamps(void) {
	// Gear lamps

	if (get_local_entity_undercarriage_state(get_gunship_entity()) == AIRCRAFT_UNDERCARRIAGE_DOWN)
	{
		wheels_up_light->visible_object = FALSE;

		left_wheel_down_light->visible_object = left_main_wheel_locked_down();
		right_wheel_down_light->visible_object = right_main_wheel_locked_down();
		nose_wheel_down_light->visible_object = nose_wheel_locked_down();
	}
	else
	{
		wheels_up_light->visible_object = get_local_entity_undercarriage_state(get_gunship_entity()) == AIRCRAFT_UNDERCARRIAGE_UP;
		left_wheel_down_light->visible_object = FALSE;
		right_wheel_down_light->visible_object = FALSE;
		nose_wheel_down_light->visible_object = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_blackshark_warning_lamps(void) {
	// Engine RPM warning lamps

		leng_rpm_light->visible_object = ka50_lamps.leng_overtorque;
		reng_rpm_light->visible_object = ka50_lamps.reng_overtorque;

	// Rotor RPM lamp

		rotor_rpm_light->visible_object = ka50_lamps.rotor_rpm;

	// Max G Warning lamp
		gmax_light->visible_object = ka50_lamps.max_g;

	// Fire lamp

		fire_light->visible_object = ka50_lamps.left_engine_fire;

		fire_light->visible_object = ka50_lamps.right_engine_fire;

		fire_light->visible_object = ka50_lamps.apu_fire;

	// Max ISA exceeded lamp

		max_isa_light->visible_object = ka50_lamps.max_isa_light;

	// Landing Gear Warning lamp

	// TODO if Landing gear is not down and locked, Low level flight with descent, and IAS < 30.0 km/h

	// Master Alarm

		master_alarm->visible_object = ka50_lamps.master_caution;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_weapon_status_lamps(void) {
		// Weapon selected lamps
		left_outer_wep_light->visible_object = ka50_lamps.lo_wep_light;
		left_inner_wep_light->visible_object = ka50_lamps.li_wep_light;
		right_inner_wep_light->visible_object = ka50_lamps.ri_wep_light;
		right_outer_wep_light->visible_object = ka50_lamps.ro_wep_light;

		// Weapon store lamps
		left_outer_wep_store_light->visible_object = ka50_lamps.lo_wep_store_light;
		left_inner_wep_store_light->visible_object = ka50_lamps.li_wep_store_light;
		right_inner_wep_store_light->visible_object = ka50_lamps.ri_wep_store_light;
		right_outer_wep_store_light->visible_object = ka50_lamps.ro_wep_store_light;
}
