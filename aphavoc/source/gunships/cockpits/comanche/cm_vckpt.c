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


#define DEBUG_MODULE					 										0

#define DEBUG_MODULE_FINE_DISPLAY_CAMERA_POSITION_ADJUSTMENT	0

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

void initialise_comanche_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	virtual_cockpit_inst3d_detail_level_high_inst3d = construct_3d_object (OBJECT_3D_COMANCHE_COCKPIT_LEVEL_1);

	virtual_cockpit_inst3d_detail_level_medium_inst3d = construct_3d_object (OBJECT_3D_COMANCHE_COCKPIT_LEVEL_2);

	virtual_cockpit_inst3d_detail_level_low_inst3d = construct_3d_object (OBJECT_3D_COMANCHE_COCKPIT_LEVEL_3);

	virtual_cockpit_inst3d_detail_level_glass_inst3d = construct_3d_object (OBJECT_3D_COMANCHE_COCKPIT_JELLY);

	virtual_cockpit_inst3d = virtual_cockpit_inst3d_detail_level_high_inst3d;

	pilot_head_pitch_datum = get_comanche_pilot_head_pitch_datum ();

	co_pilot_head_pitch_datum = get_comanche_co_pilot_head_pitch_datum ();

	//
	// wipers and rain
	//

	initialise_comanche_virtual_cockpit_wiper_and_rain_effect ();

	//
	// crew animation
	//

	initialise_comanche_crew_animation ();

	//
	// canopy doors
	//

	initialise_comanche_virtual_cockpit_canopy_doors ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();
		
//VJ wideview mod, date: 18-mar-03	
	wide_cockpit_nr = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_comanche_virtual_cockpit (void)
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

	deinitialise_comanche_virtual_cockpit_wiper_and_rain_effect ();

	//
	// crew animation
	//

	deinitialise_comanche_crew_animation ();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();
	
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_comanche_virtual_cockpit (void)
{
	int
		depth,
		draw_glass_cockpit,
		draw_controls,
		draw_crew,
		draw_pilot_cockpit,
		draw_co_pilot_cockpit;

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
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		{
			cockpit_detail_level = COCKPIT_DETAIL_LEVEL_HIGH;

			draw_glass_cockpit = FALSE;

			break;
		}
		default:
		{
			cockpit_detail_level = get_global_cockpit_detail_level ();

			draw_glass_cockpit = get_global_glass_cockpit ();

			break;
		}
	}

	draw_controls = !draw_glass_cockpit;

	if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CREW)
	{
		draw_pilot_cockpit = TRUE;

		draw_co_pilot_cockpit = TRUE;
	}
	else
	{
		if (get_crew_role () == CREW_ROLE_PILOT)
		{
			draw_pilot_cockpit = TRUE;

			draw_co_pilot_cockpit = FALSE;
		}
		else
		{
			draw_pilot_cockpit = FALSE;

			draw_co_pilot_cockpit = TRUE;
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
	// draw cockpits
	//

	depth = 0;

//VJ wideview mod, date: 18-mar-03	
	if (get_global_wide_cockpit ())
	{
  		draw_crew = FALSE;
	}

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_VISIBLE_TO_PILOT;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = draw_pilot_cockpit;
		}
		else
		{
			break;
		}

		depth++;
	}

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = virtual_cockpit_inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_VISIBLE_TO_WSO;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = draw_co_pilot_cockpit;
		}
		else
		{
			break;
		}

		depth++;
	}

	//
	// draw crew
	//

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COMANCHE_PILOT_VISIBLE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_crew;
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COMANCHE_WSO_VISIBLE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_crew;
	}

	//
	// draw controls
	//

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_JOYSTICK;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = draw_controls;
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_COLLECTIVE;

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

	////////////////////////////////////////
	//
	// update animations
	//
	////////////////////////////////////////

	//
	// crew animation
	//

	update_comanche_crew_animation ();

	//
	// canopy doors
	//

	animate_comanche_virtual_cockpit_canopy_doors ();

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

void pre_render_comanche_virtual_cockpit_displays (void)
{
	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
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

	draw_comanche_mfd ();

	if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CREW)
	{
		draw_comanche_hud_on_lens_texture ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_comanche_virtual_cockpit (void)
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

	//
	// lamps
	//

	draw_comanche_virtual_cockpit_lamps ();

	//
	// crew animation
	//

	set_comanche_crew_head_positions ();

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

	//
	// draw 3D scene
	//

	set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

//VJ wideview mod, date: 18-mar-03	
	if (get_global_wide_cockpit () &&
	    (get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY &&
	     get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY &&
         get_view_mode () != VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY ) )
	    {
			virtual_cockpit_inst3d->vp.x = wide_cockpit_position[wide_cockpit_nr].x;
			virtual_cockpit_inst3d->vp.y = wide_cockpit_position[wide_cockpit_nr].y;
			virtual_cockpit_inst3d->vp.z = wide_cockpit_position[wide_cockpit_nr].z;
		
        	set_3d_view_distances (main_3d_env, 10.0, 0.2, 1.0, 0.0);
        }	

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

				cockpit_light = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.0000, 0.5000, 0.0000);

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
                if (edit_wide_cockpit)
	            {
					sprintf(buffer,"COMANCHE wide cockpit mod edit:"); 
                    ui_display_text (buffer, 10, 40);
					sprintf(buffer,"X: numpad 1/3; Y: numpad 8/2; Z: numpad 4/6; Restore: numpad 0; Save: Alt-\\"); 
                    ui_display_text (buffer, 10, 60);
                    sprintf(buffer,"x=%.3f y=%.3f z=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z);
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

			display_backlight = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.0627, 0.2039, 0.0392);

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

				cockpit_light = create_light_3d_source (LIGHT_3D_TYPE_DIRECTIONAL, FALSE, &direction, 0, 0.0000, 0.5000, 0.0000);
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
				sprintf(buffer,"COMANCHE wide cockpit mod edit:"); 
                ui_display_text (buffer, 10, 40);
				sprintf(buffer,"X: numpad 1/3; Y: numpad 8/2; Z: numpad 4/6; Restore: numpad 0; Save: Alt-\\"); 
                ui_display_text (buffer, 10, 60);
                sprintf(buffer,"x=%.3f y=%.3f z=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z);
                ui_display_text (buffer, 10, 100);
            }

			end_3d_scene ();

			remove_light_3d_source_from_3d_scene (display_backlight);

			remove_light_3d_source_from_3d_scene (cockpit_light);

			destroy_light_3d_source (display_backlight);

			destroy_light_3d_source (cockpit_light);
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
            wide_cockpit_position[wide_cockpit_nr].z += 0.005;
        }  
		if (check_key(DIK_NUMPAD4))
		{
            wide_cockpit_position[wide_cockpit_nr].z -= 0.005;
        }  
		if (check_key(DIK_NUMPAD8))
		{
            wide_cockpit_position[wide_cockpit_nr].y += 0.005;
        }  
		if (check_key(DIK_NUMPAD2))
		{
            wide_cockpit_position[wide_cockpit_nr].y -= 0.005;
        }  
		if (check_key(DIK_NUMPAD3))
		{
            wide_cockpit_position[wide_cockpit_nr].x += 0.005;
        }  
		if (check_key(DIK_NUMPAD1))
		{
            wide_cockpit_position[wide_cockpit_nr].x -= 0.005;
        }  
		if (check_key(DIK_NUMPAD0))
		{
			if (wide_cockpit_nr==0)
			{
  		      	wide_cockpit_position[0].x = 0;    
				wide_cockpit_position[0].y = 1.15; 
				wide_cockpit_position[0].z = -2.43;
			}	
			if (wide_cockpit_nr==1)
			{
				wide_cockpit_position[1].x = 0;    
				wide_cockpit_position[1].y = 0.85; 
				wide_cockpit_position[1].z = -1.03;
			}	
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

void get_comanche_crew_viewpoint (void)
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

		memcpy (pilot_head_vp.attitude, vp.attitude, sizeof (matrix3x3));

		vp.x = -vp.x;
		vp.y = -vp.y;
		vp.z = -vp.z;

		multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, pilot_head_vp.attitude, &vp.position);
/*		
		debug_log("pilot vp: %f %f %f  ",virtual_cockpit_inst3d->vp.x,virtual_cockpit_inst3d->vp.y,virtual_cockpit_inst3d->vp.z);

//VJ wideview mod, date: 18-mar-03	
	
		if (get_global_wide_cockpit ())
		{	
			virtual_cockpit_inst3d->vp.x = wide_cockpit_position[wide_cockpit_nr].x;
			virtual_cockpit_inst3d->vp.y = wide_cockpit_position[wide_cockpit_nr].y;
			virtual_cockpit_inst3d->vp.z = wide_cockpit_position[wide_cockpit_nr].z;
		//debug_log("pilot vp: %f %f %f  ",virtual_cockpit_inst3d->vp.x,virtual_cockpit_inst3d->vp.y,virtual_cockpit_inst3d->vp.z);				
		}
*/		
	}
	else
	{
		debug_fatal ("Failed to locate crew's viewpoint in virtual cockpit");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_comanche_display_viewpoint (view_modes mode)
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
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_FL;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_FR;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RL;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			index = OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_RR;

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

	////////////////////////////////////////
	//

	#if DEBUG_MODULE_FINE_DISPLAY_CAMERA_POSITION_ADJUSTMENT

	get_identity_matrix3x3 (virtual_cockpit_inst3d->vp.attitude);

	#else

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	#endif

	//
	////////////////////////////////////////

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

	////////////////////////////////////////
	//

	#if DEBUG_MODULE_FINE_DISPLAY_CAMERA_POSITION_ADJUSTMENT
	{
		static float
			z_offset = 0.0;

		float
			dx,
			dy,
			dz;

		if (check_key (DIK_Q))
		{
			z_offset -= 0.0001;
		}

		if (check_key (DIK_A))
		{
			z_offset += 0.0001;
		}

		dx = main_vp.zv.x * z_offset;
		dy = main_vp.zv.y * z_offset;
		dz = main_vp.zv.z * z_offset;

		position.x += dx;
		position.y += dy;
		position.z += dz;

		debug_filtered_log ("offset=%.6f x=%.6f y=%.6f z=%.6f", z_offset, position.x, position.y, position.z);
	}
	#endif

	//
	////////////////////////////////////////

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, main_vp.attitude, &position);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	main_vp.x += position.x;
	main_vp.y += position.y;
	main_vp.z += position.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_comanche_virtual_cockpit_main_rotors (int seed)
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

void restore_comanche_virtual_cockpit_main_rotors (void)
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
