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

union BLACKHAWK_DAMAGE_FLAGS
{
	unsigned int
		flags;

	struct
	{
		unsigned int
			radar		  					:1,	// 1
			spare_1						:1,	// 2
			flir							:1,	// 3
			dtv							:1,	// 4
			dvo							:1,	// 5
			spare_2						:1,	// 6
			laser_designator			:1,	// 7
			radar_jammer				:1,	// 8
			infra_red_jammer	  		:1,	// 9
			spare_3						:1,	// 10
			navigation_computer 		:1,	// 11
			spare_4						:1,	// 12
			communications		  		:1,	// 13
			radar_warning_system		:1,	// 14
			ihadss						:1,	// 15
			lh_mfd						:1,	// 16
			spare_5						:1,	// 17
			rh_mfd						:1,	// 18
			pnvs							:1,	// 19
			gun_jammed					:1,	// 20
			lh_wing_tip_mount			:1,	// 21
			spare_6						:1,	// 22
			lh_outer_pylon				:1,	// 23
			lh_inner_pylon				:1,	// 24
			spare_7						:1,	// 25
			rh_wing_tip_mount			:1,	// 26
			rh_outer_pylon				:1,	// 27
			spare_8						:1,	// 28
			rh_inner_pylon				:1,	// 29
			chaff_dispenser			:1,	// 30
			spare_9						:1,	// 31
			flare_dispenser			:1;	// 32
	};
};

typedef union BLACKHAWK_DAMAGE_FLAGS blackhawk_damage_flags;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern blackhawk_damage_flags
	blackhawk_damage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_blackhawk_weapon_damage_status (void);

extern void fully_repair_blackhawk_damage (void);

extern void partially_repair_blackhawk_damage (void);

extern void repair_blackhawk_weapon_damage (void);

extern void damage_blackhawk (gunship_damage_levels damage_level);

extern void notify_blackhawk_avionics_of_dynamics_fault (unsigned int damage);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
