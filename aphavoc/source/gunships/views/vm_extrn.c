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

rgb_colour
	ext_col_message,
	ext_col_alert_message,
	ext_col_menu_title,
	ext_col_list_title,
	ext_col_list_item_available,
	ext_col_list_item_unavailable,
	ext_col_list_item_selected,
	ext_col_blue_force,
	ext_col_red_force;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	external_view_inset_target;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_external_view (void)
{
	set_rgb_colour (ext_col_message,						255, 215,   0, 255);	// gold
	set_rgb_colour (ext_col_alert_message,				255,  20,   0, 255);	// red
	set_rgb_colour (ext_col_menu_title,					255, 215,   0, 255);	// gold
	set_rgb_colour (ext_col_list_title,					255, 153,  18, 255);	// cadmium yellow
	set_rgb_colour (ext_col_list_item_available,		255, 255, 240, 255);	// ivory
	set_rgb_colour (ext_col_list_item_unavailable,	192, 192, 192, 255);	// grey
	set_rgb_colour (ext_col_list_item_selected,		255, 215,   0, 255);	// gold
	set_rgb_colour (ext_col_blue_force,					 30, 144, 255, 255);	// dodger blue
	set_rgb_colour (ext_col_red_force,					255,  20,   0, 255);	// red

	external_view_inset_target = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_external_view (void)
{
	external_view_inset_target = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_external_view (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_demo_logo (void)
{
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	float
		x_min,
		y_min,
		x_max,
		y_max;

	if (get_global_current_language () != LANGUAGE_RUSSIAN)
	{
		set_3d_active_environment (main_3d_env);
	
		if (begin_3d_scene ())
		{
			colour.red		= 255;
			colour.green	= 255;
			colour.blue		= 255;
			colour.alpha	= 255;
	
			specular.red	= 0;
			specular.green	= 0;
			specular.blue	= 0;
			specular.alpha	= 255;
	
			set_d3d_transparency_on ();
	
			set_d3d_zbuffer_comparison (FALSE);
	
			set_d3d_culling (FALSE);
	
			set_d3d_texture_wrapping (0, FALSE);
	
			if ( application_video_width == 640 )
			{
	
				set_d3d_texture_mag_filtering ( FALSE );
				set_d3d_texture_min_filtering ( FALSE );
				set_d3d_texture_mip_filtering ( FALSE );
			}
			else
			{
	
				set_d3d_texture_mag_filtering ( TRUE );
				set_d3d_texture_min_filtering ( TRUE );
				set_d3d_texture_mip_filtering ( FALSE );
			}
	
			set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_CH_LOGO));
	
			x_min = full_screen_x_min;
			y_min = full_screen_y_min;
			x_max = full_screen_width * (256.0 / 640.0);
			y_max = x_max;
	
			quad[0].i 				= x_min;
			quad[0].j  				= y_min;
			quad[0].z  				= 0.5;
			quad[0].q  				= 0.5;
			quad[0].u  				= 0.0;
			quad[0].v				= 0.0;
	
			quad[1].i  				= x_max;
			quad[1].j  				= y_min;
			quad[1].z  				= 0.5;
			quad[1].q  				= 0.5;
			quad[1].u  				= 1.0;
			quad[1].v  				= 0.0;
	
			quad[2].i				= x_max;
			quad[2].j  				= y_max;
			quad[2].z  				= 0.5;
			quad[2].q  				= 0.5;
			quad[2].u  				= 1.0;
			quad[2].v  				= 1.0;
	
			quad[3].i  				= x_min;
			quad[3].j  				= y_max;
			quad[3].z  				= 0.5;
			quad[3].q  				= 0.5;
			quad[3].u				= 0.0;
			quad[3].v				= 1.0;
	
			quad[0].next_vertex	= &quad[1];
			quad[1].next_vertex	= &quad[2];
			quad[2].next_vertex	= &quad[3];
			quad[3].next_vertex	= NULL;
	
			draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);
	
			set_d3d_transparency_off ();
	
			set_d3d_zbuffer_comparison (TRUE);
	
			set_d3d_culling (TRUE);
	
			end_3d_scene ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_external_view_text (void)
{
	if (begin_3d_scene ())
	{
		set_full_screen_viewport ();

		switch (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE))
		{
			////////////////////////////////////////////////////////////////////////////////
			case CAMERA_MODE_EJECT:
			case CAMERA_MODE_BUILDING:
			case CAMERA_MODE_WEAPON_EXPLOSION:
			case CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW:
			case CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW:
			case CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW:
			case CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW:
			////////////////////////////////////////////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////////////////////////////////////////////
			case CAMERA_MODE_WEAPON:
			////////////////////////////////////////////////////////////////////////////////
			{
			   char
      			*s,
					buffer[200];

				entity
					*weapon,
					*launcher,
					*target;

				vec3d
					*weapon_position,
					*target_position;

				float
					x,
					y,
					time_to_impact,
					weapon_velocity,
					target_range;

				weapon = get_local_entity_first_child (get_camera_entity (), LIST_TYPE_VIEW_WEAPON);

				if (weapon)
				{
					target = get_local_entity_parent (weapon, LIST_TYPE_TARGET);

					////////////////////////////////////////
					//
					// WEAPON & TIME TO IMPACT
					//
					////////////////////////////////////////

					sprintf (buffer, "Weapon: %s", get_local_entity_string (weapon, STRING_TYPE_FULL_NAME));

					if (target)
					{
						if (get_local_entity_int_value (weapon, INT_TYPE_WEAPON_GUIDANCE_TYPE) != WEAPON_GUIDANCE_TYPE_NONE)
						{
							weapon_position = get_local_entity_vec3d_ptr (weapon, VEC3D_TYPE_POSITION);

							target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							target_range = get_3d_range (weapon_position, target_position);

							weapon_velocity = get_local_entity_float_value (weapon, FLOAT_TYPE_VELOCITY);

							if (weapon_velocity > 0.0)
							{
								time_to_impact = target_range / weapon_velocity;

								sprintf (buffer, "Weapon: %s (%.1f)", get_local_entity_string (weapon, STRING_TYPE_FULL_NAME), time_to_impact);
							}
						}
					}

					s = buffer;

					set_ui_font_type (UI_FONT_ARIAL_16);

					set_ui_font_colour (ext_col_message);

					x = (get_screen_width (active_screen) - ui_get_string_length (s)) * 0.5;

					y = full_screen_y_max * (420.0 / 480.0);

					ui_display_text (s, x, y);

					////////////////////////////////////////
					//
					// LAUNCHER
					//
					////////////////////////////////////////

					set_ui_font_type (UI_FONT_ARIAL_16);

					launcher = get_local_entity_parent (weapon, LIST_TYPE_LAUNCHED_WEAPON);

					if (launcher)
					{
						sprintf (buffer, "Launcher: %s", get_local_entity_string (launcher, STRING_TYPE_FULL_NAME));

						s = buffer;

						if (get_local_entity_int_value (launcher, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
						{
							set_ui_font_colour (ext_col_blue_force);
						}
						else
						{
							set_ui_font_colour (ext_col_red_force);
						}
					}
					else
					{
						s = "Launcher: Unknown";

						set_ui_font_colour (ext_col_message);
					}

					x = (get_screen_width (active_screen) - ui_get_string_length (s)) * 0.5;

					y = full_screen_y_max * (440.0 / 480.0);

					ui_display_text (s, x, y);

					////////////////////////////////////////
					//
					// TARGET
					//
					////////////////////////////////////////

					if (target)
					{
						if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_WEAPON))
						{
							//
							// the weapon has been spoofed - display the intended target
							//

							target = get_local_entity_parent (target, LIST_TYPE_LAUNCHED_WEAPON);
						}
					}

					set_ui_font_type (UI_FONT_ARIAL_16);

					if (target)
					{
						sprintf (buffer, "Target: %s", get_local_entity_string (target, STRING_TYPE_FULL_NAME));

						s = buffer;

						if (get_local_entity_int_value (target, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
						{
							set_ui_font_colour (ext_col_blue_force);
						}
						else
						{
							set_ui_font_colour (ext_col_red_force);
						}
					}
					else
					{
						s = "Target: Unknown";

						set_ui_font_colour (ext_col_message);
					}

					x = (get_screen_width (active_screen) - ui_get_string_length (s)) * 0.5;

					y = full_screen_y_max * (460.0 / 480.0);

					ui_display_text (s, x, y);
				}

				break;
			}
			////////////////////////////////////////////////////////////////////////////////
			default:
			////////////////////////////////////////////////////////////////////////////////
			{
   			char
      			*s1,
					*s2,
					buffer1[200],
					buffer2[200],
					tmp[200],
					*full_name,
					*first_name,
					*last_name,
					*group_name,
					*task_name;

				float
					x,
					y;

   			entity
      			*en,
					*aircrew,
					*group,
					*task,
					*company;

				en = get_external_view_entity ();

				aircrew = NULL;

				////////////////////////////////////////
				//
				// LINE 1 - vehicle info
				//
				////////////////////////////////////////

				s1 = NULL;

				full_name = get_local_entity_string (en, STRING_TYPE_FULL_NAME);

				if (full_name && strlen (full_name))
				{
					if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
					{
						s1 = full_name;
					}
					else
					{
						aircrew = get_local_entity_first_child (en, LIST_TYPE_AIRCREW);

						while (aircrew)
						{
							if (get_local_entity_int_value (aircrew, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_PILOT_PILOT)
							{
								break;
							}

							aircrew = get_local_entity_child_succ (aircrew, LIST_TYPE_AIRCREW);
						}

						if (aircrew)
						{
							first_name = get_pilot_rank_short_name (get_local_entity_int_value (aircrew, INT_TYPE_PILOT_RANK));

							last_name = get_local_entity_string (aircrew, STRING_TYPE_PILOTS_NAME);

							if ((first_name && strlen (first_name)) && (last_name && strlen (last_name)))
							{
								sprintf (buffer1, "%s (%s %s)", full_name, first_name, last_name);

								s1 = buffer1;
							}
							else
							{
								s1 = full_name;
							}
						}
					}
				}

				////////////////////////////////////////
				//
				// LINE 2 - group info
				//
				////////////////////////////////////////

				s2 = NULL;

				//
				// group info
				//

				group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

				if (group)
				{
					group_name = get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN);

					company = get_local_entity_parent (group, LIST_TYPE_DIVISION);

					ASSERT (company);

					if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
					{
						sprintf (buffer2, "'%s 1-%d', %s",
									group_name,
									get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_ID),
									get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));
					}
					else
					{
						sprintf (buffer2, "%s, %s",
									get_local_entity_string (group, STRING_TYPE_DIVISION_NAME),
									get_local_entity_string (company, STRING_TYPE_DIVISION_NAME));
					}

					task = get_local_entity_primary_task (en);

					if (task)
					{
						if (get_local_entity_int_value (task, INT_TYPE_VISIBLE_TASK))
						{
							sprintf
							(
								tmp,
								", %s:%d %s:%d",
								get_trans ("KILLS"),
								get_local_entity_int_value (task, INT_TYPE_KILLS),
								get_trans ("LOSSES"),
								get_local_entity_int_value (task, INT_TYPE_LOSSES)
							);

							strcat (buffer2, tmp);

							task_name = get_local_entity_string (task, STRING_TYPE_FULL_NAME);

							if (task_name && strlen (task_name))
							{
								sprintf
								(
									tmp,
									", %s:%s (%s)",
									get_trans ("TASK"),
									task_name,
									group_member_state_names [get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_STATE)]
								);

								strcat (buffer2, tmp);
							}
						}
					}

					if (strlen (buffer2))
					{
						s2 = buffer2;
					}
				}

				////////////////////////////////////////
				//
				// display text
				//
				////////////////////////////////////////

				if (s1)
				{
					set_ui_font_type (UI_FONT_ARIAL_16);

					if (get_local_entity_int_value (en, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
					{
						set_ui_font_colour (ext_col_blue_force);
					}
					else
					{
						set_ui_font_colour (ext_col_red_force);
					}

					x = (get_screen_width (active_screen) - ui_get_string_length (s1)) * 0.5;

					y = full_screen_y_max * (420.0 / 480.0);

					ui_display_text (s1, x, y);
				}

				if (s2)
				{
					set_ui_font_type (UI_FONT_ARIAL_16);

					set_ui_font_colour (ext_col_message);

					x = (get_screen_width (active_screen) - ui_get_string_length (s2)) * 0.5;

					y = full_screen_y_max * (440.0 / 480.0);

					ui_display_text (s2, x, y);
				}

				//
				// LINE 3 - view menu search string
				//

				set_ui_font_type (UI_FONT_ARIAL_16);

				x = get_screen_width (active_screen) * 0.5;

				y = full_screen_y_max * (460.0 / 480.0);

				display_view_menu_search_string (x, y);

				break;
			}
		}

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_external_3d_view (void)
{
   ASSERT (get_external_view_entity ());

	////////////////////////////////////////
	//
	// draw main 3D scene
	//
	////////////////////////////////////////

   //
   // get camera position and attitude
   //

   get_local_entity_vec3d (get_camera_entity (), VEC3D_TYPE_POSITION, &main_vp.position);

   get_local_entity_attitude_matrix (get_camera_entity (), main_vp.attitude);

   //
   // draw 3D scene
   //

	// Jabberwock 031009 - Tint for satellite view
	
	if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_SATELLITE)
	{
		set_main_3d_full_screen_params (DISPLAY_3D_TINT_BLUE, DISPLAY_3D_LIGHT_LEVEL_LOW, DISPLAY_3D_NOISE_LEVEL_MEDIUM);
	}
	else
	{
			set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);
	}

	draw_main_3d_scene (&main_vp);

	////////////////////////////////////////
	//
	// draw inset target 3D scene
	//
	////////////////////////////////////////

	if (external_view_inset_target)
	{
		entity
			*source,
			*target;

		viewpoint
			vp;

		source = get_external_view_entity ();

		ASSERT (source);

		// Jabberwock 031016 Inset view
		target = get_inset ();

		if (target)
		{
			switch (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE))
			{
				case CAMERA_MODE_CHASE:
				case CAMERA_MODE_DROP:
				case CAMERA_MODE_STATIC:
				case CAMERA_MODE_SATELLITE:		// Jabberwock 031009 Satellite view
				case CAMERA_MODE_FLY_BY:
				case CAMERA_MODE_CINEMATIC:
				{
					store_reverse_tactical_camera_values ();

					set_reverse_tactical_camera_values (source, target);

		   		get_local_entity_vec3d (get_camera_entity (), VEC3D_TYPE_POSITION, &vp.position);

   				get_local_entity_attitude_matrix (get_camera_entity (), vp.attitude);

					set_main_3d_inset_target_screen_params ();

					draw_main_3d_scene (&vp);

					restore_reverse_tactical_camera_values ();

					set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

					break;
				}
			}
		}
	}

	////////////////////////////////////////
	//
	// eject fade
	//
	////////////////////////////////////////

	if (eject_fader > 0.0)
	{
		if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_EJECT)
		{
			if (begin_3d_scene ())
			{
				vertex
					quad[4];

				real_colour
					colour,
					specular;

				int
					alpha;

				set_viewport (full_screen_x_min, full_screen_y_min, full_screen_x_max, full_screen_y_max);

				alpha = (int) (eject_fader * (float) 255.0);

				alpha = bound (alpha, 0, 255);

				colour.red = 0;
				colour.green = 0;
				colour.blue = 0;
				colour.alpha = alpha;

				specular.red = 0;
				specular.green = 0;
				specular.blue = 0;
				specular.alpha = 255;

				set_d3d_transparency_on ();

				set_d3d_zbuffer_comparison (FALSE);

				set_d3d_plain_renderstate ();

				set_d3d_culling (FALSE);

				quad[0].i = full_screen_x_min;
				quad[0].j = full_screen_y_min;
				quad[0].z = 0.5;
				quad[0].q = 0.5;
				quad[0].next_vertex = &quad[1];

				quad[1].i = full_screen_x_max;
				quad[1].j = full_screen_y_min;
				quad[1].z = 0.5;
				quad[1].q = 0.5;
				quad[1].next_vertex = &quad[2];

				quad[2].i = full_screen_x_max;
				quad[2].j = full_screen_y_max;
				quad[2].z = 0.5;
				quad[2].q = 0.5;
				quad[2].next_vertex = &quad[3];

				quad[3].i = full_screen_x_min;
				quad[3].j = full_screen_y_max;
				quad[3].z = 0.5;
				quad[3].q = 0.5;
				quad[3].next_vertex = NULL;

				draw_wbuffered_plain_polygon (quad, colour, specular);

				set_d3d_transparency_off ();

				set_d3d_zbuffer_comparison (TRUE);

				end_3d_scene ();
			}
		}
	}

   ////////////////////////////////////////
   //
   // overlay text
   //
   ////////////////////////////////////////

	if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_DEBRIEFING)
	{
	}
	else
	{
		if (!get_display_exit_message())
		{
			// Jabberwock 031009 Satellite view - turn off text for keysites
			if (get_global_display_external_view_name () && (get_local_entity_type(get_external_view_entity()) != ENTITY_TYPE_KEYSITE))
			{
				display_external_view_text ();
			}
			// Jabberwock 031110 Satellite info
			if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_SATELLITE)
			{
			//	draw_satellite_info (); not ready yet
			}
			// Jabberwock 031110 ends
			
			if (get_global_display_hud_on_external_view ())
			{
				if (!get_view_menu_display_visible_status ())
				{
					if (get_external_view_entity () == get_gunship_entity ())
					{
						if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
						{
							if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_CHASE)
							{
								display_hud_on_external_view ();
							}
						}
					}
				}
			}
		}
	}

   ////////////////////////////////////////
   //
   // view menu
   //
   ////////////////////////////////////////

	if (begin_3d_scene ())
	{
		display_view_menu ();

		end_3d_scene ();
	}

	////////////////////////////////////////
	//
	// logo for demo mode
	//
	////////////////////////////////////////

	if (get_game_type () == GAME_TYPE_DEMO)
	{
		draw_demo_logo ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_external_view (void)
{
	camera_modes
		mode;

	ASSERT (get_camera_entity ());

	if (get_view_mode () != VIEW_MODE_EXTERNAL)
	{
		notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_CHASE);
	}
	else
	{
		mode = get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE);

		switch (mode)
		{
			//case CAMERA_MODE_CHASE:
			case CAMERA_MODE_END_OF_MISSION:
			case CAMERA_MODE_DROP:
			case CAMERA_MODE_STATIC:
//			case CAMERA_MODE_SATELLITE:		// Jabberwock 031009 Satellite view
			case CAMERA_MODE_EJECT:
			//case CAMERA_MODE_FLY_BY:
			//case CAMERA_MODE_CINEMATIC:
			case CAMERA_MODE_BUILDING:
			case CAMERA_MODE_WEAPON:
			case CAMERA_MODE_WEAPON_EXPLOSION:
			case CAMERA_MODE_DEBRIEFING:
			case CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW:
			case CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW:
			case CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW:
			case CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW:
			{
				notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_CHASE);

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
