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

enum KIOWA_MAIN_MFD_MODES
{
	KIOWA_MAIN_MFD_MODE_OFF,
	KIOWA_MAIN_MFD_MODE_DAMAGED,
	KIOWA_MAIN_MFD_MODE_FLIR,
	KIOWA_MAIN_MFD_MODE_DTV,
	KIOWA_MAIN_MFD_MODE_TSD,
	KIOWA_MAIN_MFD_MODE_ASE,
	KIOWA_MAIN_MFD_MODE_WEAPON,
	KIOWA_MAIN_MFD_MODE_SYSTEM,
	KIOWA_MAIN_MFD_MODE_ENGINE,
	KIOWA_MAIN_MFD_MODE_FLIGHT,
	KIOWA_MAIN_MFD_MODE_MISSION,
	NUM_KIOWA_MAIN_MFD_MODES
};

typedef enum KIOWA_MAIN_MFD_MODES kiowa_main_mfd_modes;

#define kiowa_main_mfd_mode_valid(MODE) (((MODE) >= KIOWA_MAIN_MFD_MODE_OFF) && ((MODE) < NUM_KIOWA_MAIN_MFD_MODES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum KIOWA_MAIN_MFD_LOCATIONS
{
	KIOWA_MAIN_MFD_LOCATION_CO_PILOT,
	KIOWA_MAIN_MFD_LOCATION_PILOT,
	KIOWA_MAIN_MFD_LOCATION_CENTER,
	NUM_KIOWA_MAIN_MFD_LOCATIONS
};

typedef enum KIOWA_MAIN_MFD_LOCATIONS kiowa_main_mfd_locations;

#define kiowa_main_mfd_location_valid(LOCATION) (((LOCATION) >= KIOWA_MAIN_MFD_LOCATION_CO_PILOT) && ((LOCATION) < NUM_KIOWA_MAIN_MFD_LOCATIONS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_kiowa_mfd (void);

extern void deinitialise_kiowa_mfd (void);

extern void draw_kiowa_mfd (void);

extern void draw_kiowa_full_screen_display (void);

extern void draw_overlaid_kiowa_mfd (void);

extern int get_kiowa_main_mfd_has_focus (kiowa_main_mfd_locations mfd_location);

extern void select_kiowa_main_mfd_mode (kiowa_main_mfd_modes mfd_mode, kiowa_main_mfd_locations mfd_location);

extern void select_next_kiowa_main_mfd (kiowa_main_mfd_locations mfd_location);

extern void select_previous_kiowa_main_mfd (kiowa_main_mfd_locations mfd_location);

extern void toggle_kiowa_main_mfd_on_off (kiowa_main_mfd_locations mfd_location);


extern void select_next_kiowa_pilot_tsd_ase_range (void);

extern void select_next_kiowa_co_pilot_tsd_ase_range (void);

extern void select_previous_kiowa_pilot_tsd_ase_range (void);

extern void select_previous_kiowa_co_pilot_tsd_ase_range (void);

extern void select_next_kiowa_pilot_tsd_declutter_level (void);

extern void select_next_kiowa_co_pilot_tsd_declutter_level (void);

extern void select_previous_kiowa_pilot_tsd_declutter_level (void);

extern void select_previous_kiowa_co_pilot_tsd_declutter_level (void);

extern void toggle_kiowa_ase_auto_page (void);

extern void auto_page_kiowa_ase_main_mfd (void);

extern void select_kiowa_tads_main_mfd (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
