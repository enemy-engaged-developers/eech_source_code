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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEXTURE_ANIMATION_INFORMATION
{

	int
		number_of_frames,
		current_frame,
		texture_indices[256];
};

typedef struct TEXTURE_ANIMATION_INFORMATION texture_animation_information;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TEXTURE_ANIMATION_INDICES
{

	TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__003,
	TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__002,
	TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__004,
	TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__002,
	TEXTURE_ANIMATION_INDEX_USA_AC_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_USA_AC_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_CIS_AC_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_CIS_AC_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_USA2_AC_DIGIT__004,
	TEXTURE_ANIMATION_INDEX_USA2_AC_DIGIT__003,
	TEXTURE_ANIMATION_INDEX_USA2_AC_DIGIT__002,
	TEXTURE_ANIMATION_INDEX_USA2_AC_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_USA2_AC_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_CIS_BLUE_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_CIS_BLUE_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_ADDITIVE_SMOKE_TRAIL,
	TEXTURE_ANIMATION_INDEX_CANNON_FLARE,
	TEXTURE_ANIMATION_INDEX_BOMB_C,
	TEXTURE_ANIMATION_INDEX_FLARE,
	TEXTURE_ANIMATION_INDEX_GUN,
	TEXTURE_ANIMATION_INDEX_GUN_FLARE,
	TEXTURE_ANIMATION_INDEX_GUN_SMOKE,
	TEXTURE_ANIMATION_INDEX_GUN_SMOKE_FRONT,
	TEXTURE_ANIMATION_INDEX_LIGHTNING,
	TEXTURE_ANIMATION_INDEX_MISSILE_FLARE,
	TEXTURE_ANIMATION_INDEX_SHIP_WAKE,
	TEXTURE_ANIMATION_INDEX_SMOKE,
	TEXTURE_ANIMATION_INDEX_SMOKE_TRAIL,
	TEXTURE_ANIMATION_INDEX_USA_NAVY__002,
	TEXTURE_ANIMATION_INDEX_USA_NAVY__000,
	TEXTURE_ANIMATION_INDEX_USA_NAVY__001,
	TEXTURE_ANIMATION_INDEX_CIS_PENNANT__000,
	TEXTURE_ANIMATION_INDEX_CIS_PENNANT__002,
	TEXTURE_ANIMATION_INDEX_CIS_PENNANT__001,
	TEXTURE_ANIMATION_INDEX_USA_TANK_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_USA_TANK_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_TRAK0,
	TEXTURE_ANIMATION_INDEX_CIS_TANK_DIGIT__000,
	TEXTURE_ANIMATION_INDEX_CIS_TANK_DIGIT__001,
	TEXTURE_ANIMATION_INDEX_CIS_TANK_DIGIT__002,
	TEXTURE_ANIMATION_INDEX_USA_TANK_DIGIT__002,

	TEXTURE_ANIMATION_INDEX_LAST,
};

typedef enum TEXTURE_ANIMATION_INDICES texture_animation_indices;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern texture_animation_information
		texture_animations[];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

