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

union COMANCHE_DAMAGE_FLAGS
{
	unsigned int
		flags;

	struct
	{
		unsigned int
			radar								:1,	// 1
			flir								:1,	// 2
			dtv								:1,	// 3
			dvo								:1,	// 4
			laser_designator				:1,	// 5
			radar_jammer					:1,	// 6
			infra_red_jammer				:1,	// 7
			navigation_computer			:1,	// 8
			communications					:1,	// 9
			radar_warning_system			:1,	// 10
			hidss				 				:1,	// 11
			spare_1							:1,	// 12
			pilot_lh_main_mfd	  			:1,	// 13
			pilot_rh_main_mfd				:1,	// 14
			pilot_lh_side_mfd		  		:1,	// 15
			pilot_rh_side_mfd		  		:1,	// 16
			co_pilot_lh_main_mfd	  		:1,	// 17
			co_pilot_rh_main_mfd	  		:1,	// 18
			co_pilot_lh_side_mfd	  		:1,	// 19
			co_pilot_rh_side_mfd	  		:1,	// 20
			pnvs								:1,	// 21
			gun_jammed						:1,	// 22
			lh_stub_wing_pylon			:1,	// 23
			lh_bay_door_inner_pylon		:1,	// 24
			lh_bay_door_middle_pylon	:1,	// 25
			lh_bay_door_outer_pylon		:1,	// 26
			rh_stub_wing_pylon			:1,	// 27
			rh_bay_door_inner_pylon		:1,	// 28
			rh_bay_door_middle_pylon	:1,	// 29
			rh_bay_door_outer_pylon		:1,	// 30
			chaff_dispensers				:1,	// 31
			flare_dispensers				:1;	// 32
	};
};

typedef union COMANCHE_DAMAGE_FLAGS comanche_damage_flags;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern comanche_damage_flags
	comanche_damage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_comanche_weapon_damage_status (void);

extern void fully_repair_comanche_damage (void);

extern void partially_repair_comanche_damage (void);

extern void repair_comanche_weapon_damage (void);

extern void damage_comanche (gunship_damage_levels damage_level);

extern void notify_comanche_avionics_of_dynamics_fault (unsigned int damage);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
