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

#define VIRTUAL_COCKPIT_COCKPIT							(1 << 0)
#define VIRTUAL_COCKPIT_LARGE_HUD						(1 << 1)
#define VIRTUAL_COCKPIT_HUD_GLASS      				(1 << 2)
#define VIRTUAL_COCKPIT_HUD_DISPLAY    				(1 << 3)
#define VIRTUAL_COCKPIT_CRT_DISPLAY    				(1 << 4)
#define VIRTUAL_COCKPIT_LHS_MFD_DISPLAY 				(1 << 5)
#define VIRTUAL_COCKPIT_PILOT_LHS_MFD_DISPLAY 				(1 << 5)  // same as not specifying pilot
#define VIRTUAL_COCKPIT_RHS_MFD_DISPLAY 				(1 << 6)
#define VIRTUAL_COCKPIT_PILOT_RHS_MFD_DISPLAY 				(1 << 6)  // same as not specifying pilot
#define VIRTUAL_COCKPIT_ADI            				(1 << 7)
#define VIRTUAL_COCKPIT_LARGE_ADI						(1 << 8)
#define VIRTUAL_COCKPIT_HSI								(1 << 9)
#define VIRTUAL_COCKPIT_COMPASS							(1 << 10)
#define VIRTUAL_COCKPIT_EKRAN_DISPLAY					(1 << 11)
#define VIRTUAL_COCKPIT_MAIN_ROTOR     				(1 << 12)
#define VIRTUAL_COCKPIT_RENDERED_WIPER 				(1 << 13)
#define VIRTUAL_COCKPIT_STOWED_WIPER				(1 << 14)
#define VIRTUAL_COCKPIT_MOVING_WIPER				(1 << 15)
#define VIRTUAL_COCKPIT_RAIN_EFFECT					(1 << 16)
#define VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES			(1 << 17)
#define VIRTUAL_COCKPIT_INSTRUMENT_LARGE_NEEDLES	(1 << 18)
#define VIRTUAL_COCKPIT_UPFRONT_DISPLAY				(1 << 19)
#define VIRTUAL_COCKPIT_DISPLAY_VIEW				(1 << 20)
#define VIRTUAL_COCKPIT_CPG_LHS_MFD_DISPLAY 		(1 << 21)
#define VIRTUAL_COCKPIT_CPG_RHS_MFD_DISPLAY 		(1 << 22)
#define VIRTUAL_COCKPIT_ORT_DISPLAY 				(1 << 23)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	float* position;
	float initial_position;
	float depress_length;
	float depress_time;
	float delay;
	float timer;
} cockpit_switch;

extern cockpit_switch
	*engine_start_switch_animation_object,
	*apu_start_switch_animation_object,
	*apu_stop_switch_animation_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern object_3d_instance
	*virtual_cockpit_inst3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float
	pilot_head_pitch_datum,
	co_pilot_head_pitch_datum;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void pre_initialise_common_virtual_cockpit(void);
extern void initialise_common_virtual_cockpit (void);

extern void deinitialise_common_virtual_cockpit (void);

extern void update_common_virtual_cockpit (void);

extern void damage_virtual_cockpit_main_rotors (int seed);

extern void restore_virtual_cockpit_main_rotors (void);

extern void draw_virtual_cockpit_periscope_mask (int x_min, int x_max, int monoccular);

extern int TIR_looking_in_periscope(void);

extern void initialise_switch(cockpit_switch*, float* position, float depress_length, float depress_time, float delay);
extern void press_switch(cockpit_switch*);
extern void animate_switch(cockpit_switch*);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
