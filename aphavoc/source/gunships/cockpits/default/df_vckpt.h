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

#define APACHE_INSTRUMENT_VIEW_HEADING	((float) (rad (0.0)))
#define APACHE_INSTRUMENT_VIEW_PITCH	((float) (rad (-20.0f)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_default_virtual_cockpit (void);

extern void deinitialise_default_virtual_cockpit (void);

extern void update_default_virtual_cockpit (void);

extern void draw_default_internal_virtual_cockpit (unsigned int flags);

extern void draw_default_external_virtual_cockpit (unsigned int flags, unsigned char *wiper_rle_graphic);

extern void damage_default_virtual_cockpit_main_rotors (int seed);

extern void restore_default_virtual_cockpit_main_rotors (void);

//VJ 050101 3d cockpit mod, in development

extern void initialise_default_virtual_cockpit_3d (void);

extern void draw_default_internal_virtual_cockpit_3d (unsigned int flags);

extern void draw_default_external_virtual_cockpit_3d (unsigned int flags);

extern void get_default_crew_viewpoint (int index, object_3d_instance   *virtual_cockpit_inst3d);

extern void draw_default_indicator_lamps_3d( void );

/*
extern  object_3d_instance
	*virtual_cockpit_level1_inst3d,
	*virtual_cockpit_level2_inst3d,
	*virtual_cockpit_level3_inst3d,
	*virtual_cockpit_fillet_level1_inst3d,
	*virtual_cockpit_fillet_level2_inst3d,
	*virtual_cockpit_fillet_level3_inst3d,
	*virtual_cockpit_main_rotor_inst3d,
	*virtual_cockpit_adi_inst3d,
	*virtual_cockpit_large_adi_inst3d,
	*virtual_cockpit_compass_inst3d,
	*virtual_cockpit_instrument_needles_inst3d,
	*virtual_cockpit_instrument_large_needles_inst3d,
	*virtual_cockpit_upfront_display_inst3d,
	*virtual_cockpit_lhs_mfd_inst3d,
	*virtual_cockpit_rhs_mfd_inst3d,
	*virtual_cockpit_display_view_mfd_inst3d;
*/

void initialise_default_lamp_screen (void);
void deinitialise_default_lamp_screen (void);
void draw_default_lamp_on_texture (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
