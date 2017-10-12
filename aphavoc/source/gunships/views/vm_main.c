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

int get_max_fov ( void )
{
	int
		max_fov;

	switch ( get_global_gunship_type () )
	{
		case GUNSHIP_TYPE_APACHE:
			max_fov = command_line_max_fov0;
			break;
		case GUNSHIP_TYPE_HAVOC:
			max_fov = command_line_max_fov1;
			break;
		case GUNSHIP_TYPE_COMANCHE:
			max_fov = command_line_max_fov2;
			break;
		case GUNSHIP_TYPE_HOKUM:
			max_fov = command_line_max_fov3;
			break;
		case GUNSHIP_TYPE_BLACKHAWK:
			max_fov = command_line_max_fov0;
			break;
		case GUNSHIP_TYPE_HIND:
			max_fov = command_line_max_fov4;
			break;
		case GUNSHIP_TYPE_AH64A:
			max_fov = command_line_max_fov0;
			break;
		case GUNSHIP_TYPE_KA50:
			max_fov = command_line_max_fov7;
			break;
		case GUNSHIP_TYPE_KIOWA:
			max_fov = command_line_max_fov5;
			break;
		case GUNSHIP_TYPE_VIPER:
			max_fov = command_line_max_fov6;
			break;
		default:
			max_fov = command_line_max_fov0;
			break;
	}

	return max_fov;
}


static int view_mode_available (view_modes mode)
{
	int
		available;

	if (get_time_acceleration () == 0)
	{
		if (in_cockpit_flags[mode])
		{
			return (FALSE);
		}
	}

	switch (mode)
	{
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		////////////////////////////////////////
		{
			available =
			(
				get_gunship_entity () &&
				get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE) &&
				get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET)
			);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && (get_num_virtual_cockpit_cameras (get_crew_role ()) > 0) && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		////////////////////////////////////////
		{
			available = FALSE;

			if (get_gunship_entity ())
			{
				if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
				{
					switch (get_global_gunship_type ())
					{
					case GUNSHIP_TYPE_HOKUM:
						{
							if (get_crew_role () == CREW_ROLE_PILOT)
							{
								available = TRUE;
							}
							break;
						}
					case GUNSHIP_TYPE_KA50:
						{
							available = TRUE;
							break;
						}
					}
				}
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE:
		////////////////////////////////////////
		{
			available = FALSE;

			if (get_gunship_entity ())
			{
				if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
				{
					if (get_global_gunship_type () == GUNSHIP_TYPE_HOKUM
						|| get_global_gunship_type () == GUNSHIP_TYPE_APACHE)
					{
						if (get_crew_role () == CREW_ROLE_CO_PILOT)
							if (get_global_gunship_type () == GUNSHIP_TYPE_APACHE || target_acquisition_system == TARGET_ACQUISITION_SYSTEM_PERISCOPE)
								available = TRUE;
					}
					else if (get_global_gunship_type () == GUNSHIP_TYPE_HIND)
						available = TRUE;
				}
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			available = get_gunship_entity () && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_EXTERNAL:
		////////////////////////////////////////
		{
			available = (get_camera_entity () != NULL) && (get_local_entity_first_child (get_camera_entity (), LIST_TYPE_VIEW));

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_SAFE:
		////////////////////////////////////////
		{
			available = TRUE;

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

	return (available);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void leave_view_mode (view_modes mode)
{
	switch (mode)
	{
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		////////////////////////////////////////
		{
			leave_padlock_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE:
		////////////////////////////////////////
		{
			// DVO only available in ORT view
			if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE
				&& target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DVO)
			{
				select_apache_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_DTV);
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_EXTERNAL:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_SAFE:
		////////////////////////////////////////
		{
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void enter_view_mode (view_modes mode)
{
	in_cockpit = in_cockpit_flags[mode];

	cockpit_panorama_row = cockpit_panorama_row_values[mode];
	cockpit_panorama_col = cockpit_panorama_col_values[mode];

	leave_seat_position (mode, view_mode);

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE); // Jabberwock 031009 Clear fog

	switch (mode)
	{
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD:
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90:
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD:
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90:
		////////////////////////////////////////
		{
			pilot_head_heading = pilot_head_heading_values[mode];

			pilot_head_pitch = pilot_head_pitch_values[mode];

			mode = VIEW_MODE_VIRTUAL_COCKPIT;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			pilot_head_heading = pilot_head_heading_values[mode];

			pilot_head_pitch = pilot_head_pitch_values[mode];

			{
				gunship_types type = get_global_gunship_type();
				//VJ 050211 needed for wideview pitch setting
				//VJ 060910 use correct pitch in comanche and hokum
				// arneh - adjusted for helicopter types which have several crew positions
				switch (type)
				{
					case GUNSHIP_TYPE_COMANCHE:
					case GUNSHIP_TYPE_HOKUM:
					case GUNSHIP_TYPE_VIPER:
					case GUNSHIP_TYPE_KIOWA:
					{
						break;
					}
					default:
					{
						if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT)
							pilot_head_pitch = co_pilot_head_pitch_datum;
						else
							pilot_head_pitch = pilot_head_pitch_datum;
						break;
					}
				}

				mode = VIEW_MODE_VIRTUAL_COCKPIT;
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			switch (get_global_gunship_type ())
			{
				// JB 030313 Fly any aircraft
				default:
				case GUNSHIP_TYPE_APACHE:
				////Moje 030518 Start
				case GUNSHIP_TYPE_BLACKHAWK:
				////Moje 030518 End
				////Moje 030612 Start
				case GUNSHIP_TYPE_HIND:
				////Moje 030612 End
				////Moje 030816 Start
				case GUNSHIP_TYPE_AH64A:
				case GUNSHIP_TYPE_KA50:
				{
					pilot_head_heading = pilot_head_heading_values[mode];

					pilot_head_pitch = pilot_head_pitch_values[mode];

					mode = VIEW_MODE_VIRTUAL_COCKPIT;

					break;
				}
				case GUNSHIP_TYPE_HAVOC:
				{
					pilot_head_heading = pilot_head_heading_values[mode];

					pilot_head_pitch = pilot_head_pitch_values[mode];

					mode = VIEW_MODE_VIRTUAL_COCKPIT;

					break;
				}
				case GUNSHIP_TYPE_COMANCHE:
				{
					pilot_head_heading = COMANCHE_INSTRUMENT_VIEW_HEADING;

					pilot_head_pitch = COMANCHE_INSTRUMENT_VIEW_PITCH;

					mode = VIEW_MODE_VIRTUAL_COCKPIT;

					break;
				}
				case GUNSHIP_TYPE_HOKUM:
				{
					pilot_head_heading = HOKUM_INSTRUMENT_VIEW_HEADING;

					pilot_head_pitch = HOKUM_INSTRUMENT_VIEW_PITCH;

					mode = VIEW_MODE_VIRTUAL_COCKPIT;

					break;
				}
				////Moje 030816 End
				case GUNSHIP_TYPE_VIPER:
				{
					pilot_head_heading = VIPER_INSTRUMENT_VIEW_HEADING;

					pilot_head_pitch = VIPER_INSTRUMENT_VIEW_PITCH;

					mode = VIEW_MODE_VIRTUAL_COCKPIT;

					break;
				}
				case GUNSHIP_TYPE_KIOWA:
				{
					pilot_head_heading = KIOWA_INSTRUMENT_VIEW_HEADING;

					pilot_head_pitch = KIOWA_INSTRUMENT_VIEW_PITCH;

					mode = VIEW_MODE_VIRTUAL_COCKPIT;

					break;
				}
			}

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			pilot_head_heading = pilot_head_heading_values[mode];

			pilot_head_pitch = pilot_head_pitch_values[mode];

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT:
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		case VIEW_MODE_EXTERNAL:
		case VIEW_MODE_SAFE:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		////////////////////////////////////////
		{
			char
				s[200];

			entity
				*target;

			ASSERT (get_gunship_entity ());

			target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

			ASSERT (target);

			sprintf (s, "%s %s", get_trans ("Padlock target"), get_local_entity_string (target, STRING_TYPE_FULL_NAME));

			set_status_message (s, STATUS_MESSAGE_TYPE_NONE);

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		////////////////////////////////////////
		{
			pilot_head_heading = 0.0;

			pilot_head_pitch = 0.0;

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE:
		////////////////////////////////////////
		{
			//FIXME
			if (get_global_gunship_type () == GUNSHIP_TYPE_HOKUM
				|| get_global_gunship_type () == GUNSHIP_TYPE_HIND
				|| get_global_gunship_type () == GUNSHIP_TYPE_APACHE)
			{
				pilot_head_heading = HOKUM_INSTRUMENT_VIEW_HEADING;

				pilot_head_pitch = HOKUM_INSTRUMENT_VIEW_PITCH;
			}

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

	view_mode = mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_view_mode (view_modes mode)
{
	int
		available;

	ASSERT ((mode >= 0) && (mode < NUM_VIEW_MODES));

	if (available = view_mode_available (mode))
	{
		leave_view_mode (view_mode);

		enter_view_mode (mode);

		//
		// clear any 'camera' messages
		//

		if (in_cockpit)
		{
			if (get_status_message_type () == STATUS_MESSAGE_TYPE_CAMERA)
			{
				set_status_message (NULL, STATUS_MESSAGE_TYPE_NONE);
			}
		}
	}

	return (available);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_viewed_entity (void)
{
	entity
		*en;

	switch (get_view_mode ())
	{
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD:
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90:
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD:
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60:
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90:
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		case VIEW_MODE_VIRTUAL_COCKPIT:
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		case VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			en = get_gunship_entity ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_EXTERNAL:
		////////////////////////////////////////
		{
			en = get_external_view_entity ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_SAFE:
		////////////////////////////////////////
		{
			en = NULL;

			break;
		}
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
