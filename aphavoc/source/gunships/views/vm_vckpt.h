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

extern void initialise_virtual_cockpit_view (void);

extern void reinitialise_virtual_cockpit_view (void);

extern void deinitialise_virtual_cockpit_view (void);

extern void update_virtual_cockpit_view (void);

extern void update_virtual_cockpit_track_target_view (void);

extern void update_virtual_cockpit_crew_view (void);

extern void update_virtual_cockpit_hud_view (void);

extern void update_virtual_cockpit_display_view (void);

extern void get_pilot_head_viewpoint (void);

extern void get_pilot_head_heading_and_pitch_to_target (entity *target);

extern void draw_virtual_cockpit_3d_view (void);

extern void draw_virtual_cockpit_3d_crew_view (void);

extern void draw_virtual_cockpit_3d_hud_view (void);

extern void update_virtual_cockpit_periscope_view (void);

extern void draw_virtual_cockpit_3d_periscope_view (void);

extern void draw_virtual_cockpit_3d_display_view (void);

extern void switch_seat_position (void);

extern void set_pilot_seat_position (void);

extern void set_co_pilot_seat_position (void);

extern void leave_seat_position (view_modes new_view_mode, view_modes old_view_mode);

extern padlock_modes get_padlock_mode (void);

extern void leave_padlock_view (void);

extern void select_padlock_view_event (padlock_modes mode);

extern entity *get_players_padlock (void);

extern void update_virtual_cockpit_padlock_view (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
