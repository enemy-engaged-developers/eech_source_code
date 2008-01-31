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
	*virtual_cockpit_inst3d_detail_level_high_inst3d,
	*virtual_cockpit_inst3d_detail_level_medium_inst3d,
	*virtual_cockpit_inst3d_detail_level_low_inst3d,
	*virtual_cockpit_inst3d_detail_level_glass_inst3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0  // code moved to co_vckpt so other helicopters can use it as well
static int hokum_periscope_box_check ( void )	// Retro 6Feb2005 (whole block)
{
	if ( current_custom_cockpit_viewpoint.z < -0.150 )
	{
		if (( current_custom_cockpit_viewpoint.y > -0.05 ) &&
			( current_custom_cockpit_viewpoint.y < 0.05 ))
		{
			if (( current_custom_cockpit_viewpoint.x > -0.05 ) &&
				( current_custom_cockpit_viewpoint.x < 0.05 ))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int hokum_periscope_check ( int currentlyUsingPeriscope )	// Retro 6Feb2005 (whole block)
{
	// later I plan to use hysteresis (hence the argument) but not right now
	
	// check if we are in the periscope box.. if yes, return TRUE
	return hokum_periscope_box_check ();
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_hokum_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	virtual_cockpit_inst3d_detail_level_high_inst3d = construct_3d_object (OBJECT_3D_HOKUM_COCKPIT_LEVEL_1);

	virtual_cockpit_inst3d_detail_level_medium_inst3d = construct_3d_object (OBJECT_3D_HOKUM_COCKPIT_LEVEL_2);

	virtual_cockpit_inst3d_detail_level_low_inst3d = construct_3d_object (OBJECT_3D_HOKUM_COCKPIT_LEVEL_3);

	virtual_cockpit_inst3d_detail_level_glass_inst3d = construct_3d_object (OBJECT_3D_HOKUM_COCKPIT_JELLY);

	virtual_cockpit_inst3d = virtual_cockpit_inst3d_detail_level_high_inst3d;

	pilot_head_pitch_datum = get_hokum_pilot_head_pitch_datum ();

	co_pilot_head_pitch_datum = get_hokum_co_pilot_head_pitch_datum ();

	//
	// wipers and rain
	//

	initialise_hokum_virtual_cockpit_wiper_and_rain_effect ();

	//
	// crew animation
	//

	initialise_hokum_crew_animation ();

	//
	// canopy doors
	//

	initialise_hokum_virtual_cockpit_canopy_doors ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();

//VJ 050208 cleaing up wideview
	wide_cockpit_nr = WIDEVIEW_HOKUM_PILOT;
	
//VJ wideview mod, date: 20-mar-03
//start up in normal view because when you switch to wideview the parameters are read	
	set_global_wide_cockpit (FALSE);		
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hokum_virtual_cockpit (void)
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

	deinitialise_hokum_virtual_cockpit_wiper_and_rain_effect ();

	//
	// crew animation
	//

	deinitialise_hokum_crew_animation ();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hokum_virtual_cockpit (void)
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
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
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
	draw_crew = !(get_global_wide_cockpit () && wide_cockpit_nr == WIDEVIEW_HOKUM_PILOT);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_POSITION;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_crew;
	}

//VJ 050206: wideview improvement show other pilot when in wideview
	draw_crew = !(get_global_wide_cockpit () && wide_cockpit_nr == WIDEVIEW_HOKUM_COPILOT);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_POSITION;

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
	draw_controls = !(get_global_wide_cockpit () && wide_cockpit_nr == WIDEVIEW_HOKUM_PILOT);

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

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_JOYSTICK;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_COLLECTIVE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_PEDAL;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

	search.search_depth = 1;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_PEDAL;

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

	update_hokum_crew_animation ();

	//
	// canopy doors
	//

	animate_hokum_virtual_cockpit_canopy_doors ();

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

		search.search_depth = 0;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_HAND_STATIC;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_render_hokum_virtual_cockpit_displays (void)
{
	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
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

	draw_hokum_mfd ();

	draw_hokum_hud ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hokum_virtual_cockpit (void)
{
//VJ wideview mod, date: 18-mar-03	
	char buffer[128];
        
	int
		draw_main_rotors;

	float
		theta;
		
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
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		{
			break;
		}
		default:
		{
			if (!get_global_draw_cockpit_graphics ())
			{
				draw_external_hokum_hud ();

				return;
			}

			break;
		}
	}

	//
	// lamps and instruments
	//

	draw_hokum_virtual_cockpit_lamps ();

	draw_hokum_virtual_cockpit_instruments ();

	//
	// crew animation
	//

	set_hokum_crew_head_positions ();

	//
	// animate main rotors
	//

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

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d);

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

	animate_hokum_virtual_cockpit_eo (virtual_cockpit_inst3d);

	//
	// animate wipers
	//

	animate_hokum_wipers (virtual_cockpit_inst3d);

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

		matrix3x3
			m1,
			m2;

//VJ 050131 update on wideview mod, much better movement
		if (get_global_wide_cockpit () &&
	    (get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY)
	   )
		{
			get_hokum_crew_viewpoint ();
		
			virtual_cockpit_inst3d->vp.x += wide_cockpit_position[wide_cockpit_nr].x;
			virtual_cockpit_inst3d->vp.y += wide_cockpit_position[wide_cockpit_nr].y;
			virtual_cockpit_inst3d->vp.z += wide_cockpit_position[wide_cockpit_nr].z;	

			virtual_cockpit_inst3d->vp.x += bound(current_flight_dynamics->model_acceleration_vector.x * ONE_OVER_G, -3.0, 3.0) * 0.025 * command_line_g_force_head_movment_modifier;
			if (!current_flight_dynamics->auto_hover)   // arneh - auto hover has some weird dynamics which cause lots of g-forces, so disable head movement when auto hover is enabled
				virtual_cockpit_inst3d->vp.y += bound(current_flight_dynamics->g_force.value - 1.0, -1.5, 5.0) * 0.025 * command_line_g_force_head_movment_modifier;

		   if (wide_cockpit_nr == WIDEVIEW_HOKUM_PILOT)
	   		pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].p );
		   if (wide_cockpit_nr == WIDEVIEW_HOKUM_COPILOT)
	   		co_pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].p );

		  	set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);    	
		}

		if (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE) == DAY_SEGMENT_TYPE_DAY)
		{
			////////////////////////////////////////
			//
			// DAY LIGHTING
			//
			////////////////////////////////////////

			if (night_vision_system_active && (get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CREW))
			{
				//
				// active night vision system
				//

				get_3d_transformation_matrix (m1, rad (0.0), rad (135.0), rad (0.0));

				multiply_matrix3x3_matrix3x3 (m2, m1, virtual_cockpit_inst3d->vp.attitude);

				direction.x = m2[2][0];
				direction.y = m2[2][1];
				direction.z = m2[2][2];

				cockpit_light = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.5000, 0.4000, 0.0000);

				insert_light_3d_source_into_3d_scene (cockpit_light);

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

				draw_3d_scene ();

				end_3d_scene ();

				remove_light_3d_source_from_3d_scene (cockpit_light);

				destroy_light_3d_source (cockpit_light);
			}
			else
			{
				//
				// inactive night vision system
				//

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

				draw_3d_scene ();

				//VJ wideview mod, date: 18-mar-03	
				//VJ 50208 added pilot head pitch
				if (edit_wide_cockpit)
				{  
					sprintf(buffer,"HOKUM wide cockpit mod edit (set freelook off):"); 
				   ui_display_text (buffer, 10, 40);
					sprintf(buffer,"X: num1/3; Y: num 8/2; Z: num 4/6; pitch: num 7/9; Restore: num 0; Ctrl-\\ Leave");
				   ui_display_text (buffer, 10, 60);
				   sprintf(buffer,"x=%.3f, y=%.3f, z=%.3f, pitch=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z, wide_cockpit_position[wide_cockpit_nr].p);
				   ui_display_text (buffer, 10, 100);
				}
				
				end_3d_scene ();
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// NIGHT LIGHTING
			//
			////////////////////////////////////////

			direction.x = virtual_cockpit_inst3d->vp.zv.x;
			direction.y = virtual_cockpit_inst3d->vp.zv.y;
			direction.z = virtual_cockpit_inst3d->vp.zv.z;

			display_backlight = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.2500, 0.0980, 0.0000);

			if (night_vision_system_active && (get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CREW))
			{
				//
				// active night vision system
				//

				get_3d_transformation_matrix (m1, rad (0.0), rad (135.0), rad (0.0));

				multiply_matrix3x3_matrix3x3 (m2, m1, virtual_cockpit_inst3d->vp.attitude);

				direction.x = m2[2][0];
				direction.y = m2[2][1];
				direction.z = m2[2][2];

				cockpit_light = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.5000, 0.4000, 0.0000);
			}
			else
			{
				//
				// inactive night vision system
				//

				direction.x = virtual_cockpit_inst3d->vp.yv.x;
				direction.y = virtual_cockpit_inst3d->vp.yv.y;
				direction.z = virtual_cockpit_inst3d->vp.yv.z;

				cockpit_light = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.0666, 0.1098, 0.6431);
			}

			insert_light_3d_source_into_3d_scene (display_backlight);

			insert_light_3d_source_into_3d_scene (cockpit_light);

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			draw_3d_scene ();

			//VJ wideview mod, date: 18-mar-03	
			if (edit_wide_cockpit)
			{
				sprintf(buffer,"HOKUM wide cockpit mod edit (set freelook off):"); 
			   ui_display_text (buffer, 10, 40);
				sprintf(buffer,"X: num1/3; Y: num 8/2; Z: num 4/6; pitch: num 7/9; Restore: num 0; Ctrl-\\ Leave");
			   ui_display_text (buffer, 10, 60);
			   sprintf(buffer,"x=%.3f, y=%.3f, z=%.3f, pitch=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z, wide_cockpit_position[wide_cockpit_nr].p);
			   ui_display_text (buffer, 10, 100);
			}


			end_3d_scene ();

			remove_light_3d_source_from_3d_scene (display_backlight);

			remove_light_3d_source_from_3d_scene (cockpit_light);

			destroy_light_3d_source (display_backlight);

			destroy_light_3d_source (cockpit_light);
		}
	}

	////////////////////////////////////////
	//
	// wide cockpit position edit
	//
	////////////////////////////////////////

//VJ wideview mod, date: 18-mar-03	
	if (edit_wide_cockpit)
	{
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
            wide_cockpit_position[wide_cockpit_nr].z += 0.005;
      }  
		if (check_key(DIK_NUMPAD4))
		{
            wide_cockpit_position[wide_cockpit_nr].z -= 0.005;
      }  
		if (check_key(DIK_NUMPAD8))
		{
            wide_cockpit_position[wide_cockpit_nr].y -= 0.005;
      }  
		if (check_key(DIK_NUMPAD2))
		{
            wide_cockpit_position[wide_cockpit_nr].y += 0.005;
      }  
   		if (check_key(DIK_NUMPAD3))
		{
            wide_cockpit_position[wide_cockpit_nr].x += 0.005;
      }  
		if (check_key(DIK_NUMPAD1))
		{
            wide_cockpit_position[wide_cockpit_nr].x -= 0.005;
      }  
//VJ 050131 update on wideview mod, much better movement
		if (check_key(DIK_NUMPAD0))
		{
			wide_cockpit_position[wide_cockpit_nr].x = 0;
			wide_cockpit_position[wide_cockpit_nr].y = 0;
			wide_cockpit_position[wide_cockpit_nr].z = 0.300;
			wide_cockpit_position[wide_cockpit_nr].p = 0;
      }     
	}            	


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

void get_hokum_crew_viewpoint (void)
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

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
	{
		search_head.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_HEAD;

		search_viewpoint.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_VIEWPOINT;

		head_pitch_datum = pilot_head_pitch_datum;
	}
	else
	{
		search_head.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_HEAD;

		search_viewpoint.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_VIEWPOINT;

		head_pitch_datum = co_pilot_head_pitch_datum;
	}

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
		virtual_cockpit_inst3d->vp.x = 0.0;
		virtual_cockpit_inst3d->vp.y = 0.0;
		virtual_cockpit_inst3d->vp.z = 0.0;

		get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

		get_3d_sub_object_world_viewpoint (search_viewpoint.result_sub_object, &vp);

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
			virtual_cockpit_inst3d->vp.x += current_custom_cockpit_viewpoint.x;
			virtual_cockpit_inst3d->vp.y += current_custom_cockpit_viewpoint.y;
			virtual_cockpit_inst3d->vp.z += current_custom_cockpit_viewpoint.z;
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

void get_hokum_display_viewpoint (view_modes mode)
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

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = index;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		get_3d_sub_object_world_viewpoint (search.result_sub_object, &main_vp);
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

void damage_hokum_virtual_cockpit_main_rotors (int seed)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_inst3d_detail_level_high_inst3d);
	ASSERT (virtual_cockpit_inst3d_detail_level_medium_inst3d);
	ASSERT (virtual_cockpit_inst3d_detail_level_low_inst3d);
	ASSERT (virtual_cockpit_inst3d_detail_level_glass_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_high_inst3d, theta);
	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_medium_inst3d, theta);
	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_low_inst3d, theta);
	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_glass_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_high_inst3d);
	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_medium_inst3d);
	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_low_inst3d);
	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_glass_inst3d);

	damage_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_high_inst3d, seed);
	damage_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_medium_inst3d, seed);
	damage_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_low_inst3d, seed);
	damage_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_glass_inst3d, seed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_hokum_virtual_cockpit_main_rotors (void)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_inst3d_detail_level_high_inst3d);
	ASSERT (virtual_cockpit_inst3d_detail_level_medium_inst3d);
	ASSERT (virtual_cockpit_inst3d_detail_level_low_inst3d);
	ASSERT (virtual_cockpit_inst3d_detail_level_glass_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_high_inst3d, theta);
	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_medium_inst3d, theta);
	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_low_inst3d, theta);
	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_inst3d_detail_level_glass_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_high_inst3d);
	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_medium_inst3d);
	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_low_inst3d);
	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_inst3d_detail_level_glass_inst3d);

	restore_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_high_inst3d);
	restore_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_medium_inst3d);
	restore_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_low_inst3d);
	restore_helicopter_main_rotor_inst3d (virtual_cockpit_inst3d_detail_level_glass_inst3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
