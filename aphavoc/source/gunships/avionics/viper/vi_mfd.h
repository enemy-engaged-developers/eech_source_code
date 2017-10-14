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

enum VIPER_MFD_MODES
{
	VIPER_MFD_MODE_OFF,
	VIPER_MFD_MODE_DAMAGED,
	VIPER_MFD_MODE_FLIR,
	VIPER_MFD_MODE_DTV,
	VIPER_MFD_MODE_TSD,
	VIPER_MFD_MODE_ASE,
	VIPER_MFD_MODE_WEAPON,
	VIPER_MFD_MODE_SYSTEM,
	VIPER_MFD_MODE_ENGINE,
	VIPER_MFD_MODE_FLIGHT,
	VIPER_MFD_MODE_MISSION,
	NUM_VIPER_MFD_MODES
};

typedef enum VIPER_MFD_MODES viper_mfd_modes;

#define viper_mfd_mode_valid(MODE) (((MODE) >= VIPER_MFD_MODE_OFF) && ((MODE) < NUM_VIPER_MFD_MODES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum VIPER_MFD_LOCATIONS
{
	VIPER_MFD_LOCATION_PILOT_LHS,
	VIPER_MFD_LOCATION_PILOT_RHS,
	VIPER_MFD_LOCATION_CO_PILOT_LHS,
	VIPER_MFD_LOCATION_CO_PILOT_RHS,
	VIPER_MFD_LOCATION_PILOT_DFD,
	VIPER_MFD_LOCATION_CO_PILOT_DFD,
	NUM_VIPER_MFD_LOCATIONS
};

typedef enum VIPER_MFD_LOCATIONS viper_mfd_locations;

#define viper_mfd_location_valid(LOCATION) (((LOCATION) >= VIPER_MFD_LOCATION_PILOT_LHS) && ((LOCATION) < NUM_VIPER_MFD_LOCATIONS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_viper_mfd (void);

extern void deinitialise_viper_mfd (void);

extern void draw_viper_mfd (void);

extern void set_viper_text_display_text (char *s1, char *s2);

extern void draw_viper_full_screen_display (void);

extern void draw_overlaid_viper_mfd (void);

extern int get_viper_mfd_has_focus (viper_mfd_locations mfd_location);

extern void select_viper_mfd_mode (viper_mfd_modes mfd_mode, viper_mfd_locations mfd_location);

extern void select_next_viper_mfd (viper_mfd_locations mfd_location);

extern void select_previous_viper_mfd (viper_mfd_locations mfd_location);

extern void toggle_viper_mfd_on_off (viper_mfd_locations mfd_location);

extern viper_mfd_modes get_viper_mfd_mode (viper_mfd_locations mfd_location);

extern void select_next_viper_pilot_tsd_ase_range (void);

extern void select_next_viper_co_pilot_tsd_ase_range (void);

extern void select_previous_viper_pilot_tsd_ase_range (void);

extern void select_previous_viper_co_pilot_tsd_ase_range (void);

extern void select_next_viper_pilot_tsd_declutter_level (void);

extern void select_next_viper_co_pilot_tsd_declutter_level (void);

extern void select_previous_viper_pilot_tsd_declutter_level (void);

extern void select_previous_viper_co_pilot_tsd_declutter_level (void);

extern void toggle_viper_ase_auto_page (void);

extern void auto_page_viper_ase_mfd (void);

extern void select_viper_tads_mfd (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
