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

void update_view (void)
{
	update_view_menu ();

	update_joystick_pov_position ();

	if (in_cockpit)
	{
		if (joystick_pov_engage)
		{
			set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);
		}
		else if (joystick_pov_disengage)
		{
			if (get_apache_havoc_gunship_fixed_cockpit ())
			{
				set_view_mode (get_nearest_fixed_cockpit_view (pilot_head_heading, pilot_head_pitch));
			}
		}
	}

   switch (view_mode)
   {
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

			break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

         break;
      }
      ////////////////////////////////////////
      case VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30:
      ////////////////////////////////////////
      {
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			update_fixed_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT:
		////////////////////////////////////////
		{
			update_virtual_cockpit_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		////////////////////////////////////////
		{
			update_virtual_cockpit_padlock_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		////////////////////////////////////////
		{
			update_virtual_cockpit_track_target_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		////////////////////////////////////////
		{
			update_virtual_cockpit_crew_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		////////////////////////////////////////
		{
			update_virtual_cockpit_hud_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE:
		////////////////////////////////////////
		{
			update_virtual_cockpit_periscope_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			update_virtual_cockpit_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			update_virtual_cockpit_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		////////////////////////////////////////
		{
			update_virtual_cockpit_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		////////////////////////////////////////
		{
			update_virtual_cockpit_display_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_EXTERNAL:
		////////////////////////////////////////
		{
			update_external_view ();

			break;
		}
		////////////////////////////////////////
		case VIEW_MODE_SAFE:
		////////////////////////////////////////
		{
			update_safe_view ();

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

	//
	// set main viewpoint to a known state so that 3D cockpit instruments etc. work (even with no main 3D visual)
	//

	get_pilot_head_viewpoint ();

	main_vp = pilot_head_vp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
