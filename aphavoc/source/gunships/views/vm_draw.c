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

static char
	status_message[200];

static float
	status_message_timer;

static status_message_types
	status_message_type;

static int
	in_tir_periscope = FALSE;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define STATUS_MESSAGE_FLASH_ON_TIME	((float) 0.666)
#define STATUS_MESSAGE_FLASH_OFF_TIME	((float) 0.333)
#define STATUS_MESSAGE_FLASH_PERIOD		(STATUS_MESSAGE_FLASH_ON_TIME + STATUS_MESSAGE_FLASH_OFF_TIME)

#define DEFAULT_FOV  rad(60.0)
#define FOV_CHANGE_RATE  rad(30.0)
	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_status_message (void)
{
	status_message[0] = '\0';

	status_message_timer = 0.0;

	status_message_type = STATUS_MESSAGE_TYPE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_status_message (void)
{
	clear_status_message ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_status_message (const char *s, status_message_types type)
{
	ASSERT ((type >= 0) && (type < NUM_STATUS_MESSAGE_TYPES));

	if (status_message_type != STATUS_MESSAGE_TYPE_ALERT)
	{
		if (s)
		{
			if (strlen (s))
			{
				strcpy (status_message, s);

				if (type == STATUS_MESSAGE_TYPE_ALERT)
				{
					status_message_timer = 5.0 * STATUS_MESSAGE_FLASH_PERIOD;
				}
				else
				{
					status_message_timer = 3.0;
				}

				status_message_type = type;
			}
			else
			{
				clear_status_message ();
			}
		}
		else
		{
			clear_status_message ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_status_message (void)
{
	float
		x,
		y;

	if (command_line_disable_message_text)
		return;
	
	if (status_message_timer > 0.0)
	{
		set_ui_font_type (UI_FONT_ARIAL_16);

		if (status_message_type == STATUS_MESSAGE_TYPE_ALERT)
		{
			if (fmod (status_message_timer, STATUS_MESSAGE_FLASH_PERIOD) >= STATUS_MESSAGE_FLASH_OFF_TIME)
			{
				set_ui_font_colour (ext_col_alert_message);

				x = (get_screen_width (active_screen) * 0.5) - (ui_get_string_length (status_message) * 0.5);

				y = 0.0;

				ui_display_text (status_message, x, y);
			}
		}
		else
		{
			set_ui_font_colour (ext_col_message);

			x = (get_screen_width (active_screen) * 0.5) - (ui_get_string_length (status_message) * 0.5);

			y = 0.0;

			ui_display_text (status_message, x, y);
		}

		//
		// (screen resolution switching can be time consuming - limit delta time to ensure the message gets displayed)
		//

		status_message_timer -= min (get_delta_time (), 1.0f);

		if (status_message_timer < 0.0)
		{
			clear_status_message ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_status_message_displayed (void)
{
	return (status_message_timer > 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

status_message_types get_status_message_type (void)
{
	return (status_message_type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_eject_message (void)
{
	int
		display_message;

	const char
		*s;

	float
		x,
		y;

	if (command_line_disable_message_text)
		return;
	
	display_message = FALSE;

	if (get_local_entity_int_value (get_camera_entity (), INT_TYPE_CAMERA_MODE) == CAMERA_MODE_EJECT)
	{
		display_message = TRUE;
	}
	else
	{
		if (get_gunship_entity ())
		{
			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
			{
				if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
				{
					display_message = TRUE;
				}
			}
		}
	}

	if (display_message)
	{
		s = get_trans ("Press SPACE");

		set_ui_font_type (UI_FONT_ARIAL_16);

		set_ui_font_colour (ext_col_message);

		x = (get_screen_width (active_screen) - ui_get_string_length (s)) * 0.5;

		y = full_screen_y_max * (440.0 / 480.0);

		ui_display_text (s, x, y);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_time_acceleration (void)
{
	const char
		*s;
	char
		buffer[80];

	float
		x,
		y;

	s = NULL;

	if (command_line_disable_message_text)
		return;

	if (get_time_acceleration () == 0)
	{
		s = get_trans ("Paused");
	}
	else if (get_time_acceleration () > 1)
	{
		sprintf (buffer, "x%d", get_time_acceleration ());

		s = buffer;
	}

	if (s)
	{
		set_ui_font_type (UI_FONT_ARIAL_16);

		set_ui_font_colour (ext_col_message);

		x = get_screen_width (active_screen) - ui_get_string_length (s) - 2.0;

		y = 0.0;

		ui_display_text (s, x, y);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_field_of_view(void)
{
	int
		max_fov = get_max_fov ();

	if (command_line_field_of_view_joystick_index != -1)
	{
		int joyval = get_joystick_axis(command_line_field_of_view_joystick_index, command_line_field_of_view_joystick_axis);
		float fov;

		if (joyval <= 0)
			fov = DEFAULT_FOV - (((float)joyval / JOYSTICK_AXIS_MINIMUM) * (DEFAULT_FOV - rad(command_line_min_fov)));
		else
			fov = DEFAULT_FOV + (((float)joyval / JOYSTICK_AXIS_MAXIMUM) * (rad(max_fov) - DEFAULT_FOV));

		full_screen_width_view_angle = fov;
		full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
	}
	else
	{		
		if (increase_fov_key_down)
		{
			full_screen_width_view_angle = bound(full_screen_width_view_angle + FOV_CHANGE_RATE * get_delta_time(), rad(command_line_min_fov), rad(max_fov));
			full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
		}
		else if (decrease_fov_key_down)
		{
			full_screen_width_view_angle = bound(full_screen_width_view_angle - FOV_CHANGE_RATE * get_delta_time(), rad(command_line_min_fov), rad(max_fov));
			full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_view (void)
{
	TIR_Poll (); // Retro 6Feb2005

	update_field_of_view();	

	// Retro 6Feb2005 (whole block)
	if ((command_line_TIR_6DOF)&&(query_TIR_active() == TRUE)&&
		(( view_mode == VIEW_MODE_VIRTUAL_COCKPIT)||( view_mode == VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE )))
	{
		current_custom_cockpit_viewpoint.x = getViewpointOffsetX(current_custom_cockpit_viewpoint.x);
		current_custom_cockpit_viewpoint.y = getViewpointOffsetY(current_custom_cockpit_viewpoint.y);
		current_custom_cockpit_viewpoint.z = getViewpointOffsetZ(current_custom_cockpit_viewpoint.z);
	}

   switch (view_mode)
   {
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP40_LEFT90);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP40_LEFT60);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP40_LEFT30);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP40_AHEAD);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP40_RIGHT30);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP40_RIGHT60);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP40_RIGHT90);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP20_LEFT90);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP20_LEFT60);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP20_LEFT30);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP20_AHEAD);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP20_RIGHT30);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP20_RIGHT60);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_UP20_RIGHT90);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_LEVEL_LEFT90);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_LEVEL_LEFT60);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_LEVEL_LEFT30);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_LEVEL_AHEAD);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_LEVEL_RIGHT30);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_LEVEL_RIGHT60);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_LEVEL_RIGHT90);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_DOWN20_LEFT90);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

         draw_cockpit (COCKPIT_PANEL_DOWN20_LEFT60);

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30:
      ////////////////////////////////////////
      {
         draw_fixed_cockpit_3d_view ();

			draw_cockpit (COCKPIT_PANEL_DOWN20_LEFT30);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			draw_fixed_cockpit_3d_view ();

			draw_cockpit (COCKPIT_PANEL_DOWN20_AHEAD);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			draw_fixed_cockpit_3d_view ();

			draw_cockpit (COCKPIT_PANEL_DOWN20_RIGHT30);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			draw_fixed_cockpit_3d_view ();

			draw_cockpit (COCKPIT_PANEL_DOWN20_RIGHT60);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90:
		////////////////////////////////////////
		{
			draw_fixed_cockpit_3d_view ();

			draw_cockpit (COCKPIT_PANEL_DOWN20_RIGHT90);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		////////////////////////////////////////
		{
			if ((!full_screen_hi_res) && (application_video_colourdepth == 16))
			{
				draw_cockpit (COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD);
			}
			else
			{
				float old_angle = full_screen_width_view_angle;

				full_screen_width_view_angle = rad(59.99);
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
				
				draw_virtual_cockpit_3d_display_view ();

				full_screen_width_view_angle = old_angle;
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		////////////////////////////////////////
		{
			if ((!full_screen_hi_res) && (application_video_colourdepth == 16))
			{
				draw_cockpit (COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD);
			}
			else
			{
				float old_angle = full_screen_width_view_angle;

				full_screen_width_view_angle = rad(59.99);
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
				
				draw_virtual_cockpit_3d_display_view ();

				full_screen_width_view_angle = old_angle;
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		////////////////////////////////////////
		{
			if ((!full_screen_hi_res) && (application_video_colourdepth == 16))
			{
				draw_cockpit (COCKPIT_PANEL_SPECIAL_HAVOC_TV);
			}
			else
			{
				float old_angle = full_screen_width_view_angle;

				full_screen_width_view_angle = rad(59.99);
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
				
				draw_virtual_cockpit_3d_display_view ();

				full_screen_width_view_angle = old_angle;
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			if ((!full_screen_hi_res) && (application_video_colourdepth == 16))
			{
				draw_fixed_cockpit_3d_view ();

				draw_cockpit (COCKPIT_PANEL_SPECIAL_HAVOC_HUD);
			}
			else
			{
				float old_angle = full_screen_width_view_angle;

				full_screen_width_view_angle = rad(40.0);
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;

				draw_virtual_cockpit_3d_hud_view ();
				
				full_screen_width_view_angle = old_angle;
				full_screen_height_view_angle = full_screen_width_view_angle / full_screen_aspect_ratio;
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT:
		////////////////////////////////////////
		{
			if (command_line_TIR_6DOF && query_TIR_active() && TIR_looking_in_periscope())
			{
				in_tir_periscope = TRUE;
				set_view_mode ( VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE);
				draw_virtual_cockpit_3d_periscope_view ();
			}
			else
				draw_virtual_cockpit_3d_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_crew_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_hud_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE:
		////////////////////////////////////////
		{
			if (in_tir_periscope && command_line_TIR_6DOF && query_TIR_active() && !TIR_looking_in_periscope())
			{
				set_view_mode ( VIEW_MODE_VIRTUAL_COCKPIT );
				draw_virtual_cockpit_3d_view ();
				in_tir_periscope = FALSE;
			}
			else	// original Razorworks call..
				draw_virtual_cockpit_3d_periscope_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			draw_virtual_cockpit_3d_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_EXTERNAL:
		////////////////////////////////////////
		{
			draw_external_3d_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_SAFE:
		////////////////////////////////////////
		{
			draw_safe_3d_view ();

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid view mode = %d", view_mode);

			break;
		}
	}

	////////////////////////////////////////
	//
	// display text
	//
	////////////////////////////////////////

	if (begin_3d_scene ())
	{

		set_full_screen_viewport ();

		display_in_flight_messages ();

		display_time_acceleration ();

		display_status_message ();

		display_eject_message ();

//VJ framerate 24-mar-03
		if (command_line_framerate)
			ShowFramerate();

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ framerate 24-mar-03
void ShowFramerate(void)
{
	char buf[25];

	timeframes += get_delta_time ();
	frames++; 

	if (timeframes >= 1.0)
	{
		framerate = frames / timeframes;
		frames = 0;
		timeframes = 0;

		if (command_line_framerate == 2)
		{
			FILE *file = fopen ("framerate.txt", "a");
			fprintf (file, "%6.1f\n", framerate);
			fclose (file);
		}
	}

	if (command_line_framerate == 3)
	{
		sprintf (buf, "%6.1f %6.1f", framerate, get_one_over_delta_time ());
	}
	else
	{
		sprintf (buf, "%6.1f", framerate);
	}
	ui_display_text (buf, 10, 24);
}
