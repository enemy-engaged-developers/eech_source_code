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

enum KA50_MFD_MODES
{
	KA50_MFD_MODE_OFF,
	KA50_MFD_MODE_DAMAGED,
	KA50_MFD_MODE_FLIR,			//  Javelin 7/19
	KA50_MFD_MODE_LLLTV,
	KA50_MFD_MODE_TSD,
	KA50_MFD_MODE_ASE,
	KA50_MFD_MODE_WEAPON,
	KA50_MFD_MODE_SYSTEM,
	KA50_MFD_MODE_ENGINE,
	KA50_MFD_MODE_FLIGHT,
	KA50_MFD_MODE_MISSION,
	NUM_KA50_MFD_MODES
};

typedef enum KA50_MFD_MODES ka50_mfd_modes;

#define ka50_mfd_mode_valid(MODE) (((MODE) >= KA50_MFD_MODE_OFF) && ((MODE) < NUM_KA50_MFD_MODES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum KA50_MFD_LOCATIONS
{
	KA50_MFD_LOCATION_SHKVAL,
	KA50_MFD_LOCATION_ABRIS,
	NUM_KA50_MFD_LOCATIONS
};

typedef enum KA50_MFD_LOCATIONS ka50_mfd_locations;

#define ka50_mfd_location_valid(LOCATION) (((LOCATION) >= KA50_MFD_LOCATION_SHKVAL) && ((LOCATION) < NUM_KA50_MFD_LOCATIONS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_ka50_mfd (void);

extern void deinitialise_ka50_mfd (void);

extern void draw_ka50_mfd (void);

extern void set_ka50_text_display_text (char *s1, char *s2, char *s3);

extern void draw_ka50_full_screen_display (void);

extern void draw_overlaid_ka50_mfd (void);

extern void select_ka50_mfd_mode (ka50_mfd_modes mfd_mode, ka50_mfd_locations mfd_location);

extern void select_next_ka50_mfd (ka50_mfd_locations mfd_location);

extern void select_previous_ka50_mfd (ka50_mfd_locations mfd_location);

extern void toggle_ka50_mfd_on_off (ka50_mfd_locations mfd_location);

extern ka50_mfd_modes get_ka50_mfd_mode (ka50_mfd_locations mfd_location);

extern void select_next_ka50_tsd_ase_range (void);

extern void select_previous_ka50_tsd_ase_range (void);

extern void select_next_ka50_tsd_declutter_level (void);

extern void select_previous_ka50_tsd_declutter_level (void);

extern void toggle_ka50_ase_auto_page (void);

extern void auto_page_ka50_ase_mfd (void);

extern void select_ka50_eo_mfd (target_acquisition_systems system);	//  Javelin  7/19

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
