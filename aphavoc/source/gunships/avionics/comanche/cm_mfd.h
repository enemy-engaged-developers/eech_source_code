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

enum COMANCHE_MAIN_MFD_MODES
{
	COMANCHE_MAIN_MFD_MODE_OFF,
	COMANCHE_MAIN_MFD_MODE_DAMAGED,
	COMANCHE_MAIN_MFD_MODE_GROUND_RADAR,
	COMANCHE_MAIN_MFD_MODE_AIR_RADAR,
	COMANCHE_MAIN_MFD_MODE_FLIR,
	COMANCHE_MAIN_MFD_MODE_DTV,
	COMANCHE_MAIN_MFD_MODE_DVO,
	COMANCHE_MAIN_MFD_MODE_TSD,
	COMANCHE_MAIN_MFD_MODE_ASE,
	COMANCHE_MAIN_MFD_MODE_WEAPON,
	COMANCHE_MAIN_MFD_MODE_SYSTEM,
	COMANCHE_MAIN_MFD_MODE_ENGINE,
	COMANCHE_MAIN_MFD_MODE_FLIGHT,
	COMANCHE_MAIN_MFD_MODE_MISSION,
	NUM_COMANCHE_MAIN_MFD_MODES
};

typedef enum COMANCHE_MAIN_MFD_MODES comanche_main_mfd_modes;

#define comanche_main_mfd_mode_valid(MODE) (((MODE) >= COMANCHE_MAIN_MFD_MODE_OFF) && ((MODE) < NUM_COMANCHE_MAIN_MFD_MODES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMANCHE_MAIN_MFD_LOCATIONS
{
	COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS,
	COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS,
	COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS,
	COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS,
	NUM_COMANCHE_MAIN_MFD_LOCATIONS
};

typedef enum COMANCHE_MAIN_MFD_LOCATIONS comanche_main_mfd_locations;

#define comanche_main_mfd_location_valid(LOCATION) (((LOCATION) >= COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS) && ((LOCATION) < NUM_COMANCHE_MAIN_MFD_LOCATIONS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMANCHE_SIDE_MFD_MODES
{
	COMANCHE_SIDE_MFD_MODE_OFF,
	COMANCHE_SIDE_MFD_MODE_DAMAGED,
	COMANCHE_SIDE_MFD_MODE_WEAPON,
	COMANCHE_SIDE_MFD_MODE_SYSTEM,
	COMANCHE_SIDE_MFD_MODE_ENGINE,
	COMANCHE_SIDE_MFD_MODE_FLIGHT,
	NUM_COMANCHE_SIDE_MFD_MODES
};

typedef enum COMANCHE_SIDE_MFD_MODES comanche_side_mfd_modes;

#define comanche_side_mfd_mode_valid(MODE) (((MODE) >= COMANCHE_SIDE_MFD_MODE_OFF) && ((MODE) < NUM_COMANCHE_SIDE_MFD_MODES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMANCHE_SIDE_MFD_LOCATIONS
{
	COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS,
	COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS,
	COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS,
	COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS,
	NUM_COMANCHE_SIDE_MFD_LOCATIONS
};

typedef enum COMANCHE_SIDE_MFD_LOCATIONS comanche_side_mfd_locations;

#define comanche_side_mfd_location_valid(LOCATION) (((LOCATION) >= COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS) && ((LOCATION) < NUM_COMANCHE_SIDE_MFD_LOCATIONS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_comanche_mfd (void);

extern void deinitialise_comanche_mfd (void);

extern void draw_comanche_mfd (void);

extern void set_comanche_text_display_text (char *s1, char *s2);

extern void draw_comanche_full_screen_display (void);

extern void draw_overlaid_comanche_mfd (void);

extern int get_comanche_main_mfd_has_focus (comanche_main_mfd_locations mfd_location);

extern void select_comanche_main_mfd_mode (comanche_main_mfd_modes mfd_mode, comanche_main_mfd_locations mfd_location);

extern void select_comanche_side_mfd_mode (comanche_side_mfd_modes mfd_mode, comanche_side_mfd_locations mfd_location);

extern void select_next_comanche_main_mfd (comanche_main_mfd_locations mfd_location);

extern void select_previous_comanche_main_mfd (comanche_main_mfd_locations mfd_location);

extern void toggle_comanche_main_mfd_on_off (comanche_main_mfd_locations mfd_location);

extern void toggle_comanche_side_mfd_on_off (comanche_side_mfd_locations mfd_location);

extern void select_next_comanche_pilot_tsd_ase_range (void);

extern void select_next_comanche_co_pilot_tsd_ase_range (void);

extern void select_previous_comanche_pilot_tsd_ase_range (void);

extern void select_previous_comanche_co_pilot_tsd_ase_range (void);

extern void select_next_comanche_pilot_tsd_declutter_level (void);

extern void select_next_comanche_co_pilot_tsd_declutter_level (void);

extern void select_previous_comanche_pilot_tsd_declutter_level (void);

extern void select_previous_comanche_co_pilot_tsd_declutter_level (void);

extern void toggle_comanche_ase_auto_page (void);

extern void auto_page_comanche_ase_main_mfd (void);

extern void select_comanche_ground_radar_main_mfd (void);

extern void select_comanche_air_radar_main_mfd (void);

extern void select_comanche_tads_main_mfd (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
