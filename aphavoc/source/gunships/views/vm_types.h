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

enum VIEW_MODES
{
	VIEW_MODE_COCKPIT_PANEL_UP40_LEFT90,
	VIEW_MODE_COCKPIT_PANEL_UP40_LEFT60,
	VIEW_MODE_COCKPIT_PANEL_UP40_LEFT30,
	VIEW_MODE_COCKPIT_PANEL_UP40_AHEAD,
	VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT30,
	VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT60,
	VIEW_MODE_COCKPIT_PANEL_UP40_RIGHT90,
	VIEW_MODE_COCKPIT_PANEL_UP20_LEFT90,
	VIEW_MODE_COCKPIT_PANEL_UP20_LEFT60,
	VIEW_MODE_COCKPIT_PANEL_UP20_LEFT30,
	VIEW_MODE_COCKPIT_PANEL_UP20_AHEAD,
	VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT30,
	VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT60,
	VIEW_MODE_COCKPIT_PANEL_UP20_RIGHT90,
	VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT90,
	VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT60,
	VIEW_MODE_COCKPIT_PANEL_LEVEL_LEFT30,
	VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD,
	VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT30,
	VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT60,
	VIEW_MODE_COCKPIT_PANEL_LEVEL_RIGHT90,
	VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT90,
	VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT60,
	VIEW_MODE_COCKPIT_PANEL_DOWN20_LEFT30,
	VIEW_MODE_COCKPIT_PANEL_DOWN20_AHEAD,
	VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT30,
	VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT60,
	VIEW_MODE_COCKPIT_PANEL_DOWN20_RIGHT90,
	VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD,
	VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD,
	VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV,
	VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD,
	VIEW_MODE_VIRTUAL_COCKPIT,
	VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK,
	VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET,
	VIEW_MODE_VIRTUAL_COCKPIT_CREW,
	VIEW_MODE_VIRTUAL_COCKPIT_HUD,
	VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE,
	VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY,
	VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY,
	VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY,
	VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY,
	VIEW_MODE_EXTERNAL,
	VIEW_MODE_SAFE,
	NUM_VIEW_MODES
};

typedef enum VIEW_MODES view_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// padlock target is handled via VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET
//

enum PADLOCK_MODES
{
	PADLOCK_MODE_NONE,
	PADLOCK_MODE_WINGMAN,
	PADLOCK_MODE_AIR_THREAT,
	PADLOCK_MODE_GROUND_THREAT,
	PADLOCK_MODE_MISSILE_THREAT,
	PADLOCK_MODE_WAYPOINT,
	NUM_PADLOCK_MODES
};

typedef enum PADLOCK_MODES padlock_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030318 wideview mod

#define set_global_wide_cockpit(FLAG) (wide_cockpit = (FLAG))

#define get_global_wide_cockpit() (wide_cockpit)

//VJ 030423 TSD render mod
#define set_TSD_render_mode(x) (tsd_render_mode = (x))


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
