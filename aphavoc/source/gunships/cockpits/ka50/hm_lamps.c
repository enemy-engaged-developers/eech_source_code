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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ka50_lamp_flags
	ka50_lamps;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ka50_lamps (void)
{
	memset (&ka50_lamps, 0, sizeof (ka50_lamp_flags));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ka50_lamps (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define draw_lamp(FLAG,TEXTURE)																		\
{																												\
	if ((FLAG))																								\
	{																											\
		set_texture_animation_frame_on_object (virtual_cockpit_inst3d, (TEXTURE), 1);	\
	}																											\
	else																										\
	{																											\
		set_texture_animation_frame_on_object (virtual_cockpit_inst3d, (TEXTURE), 0);	\
	}																											\
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_virtual_cockpit_lamps (void)
{
//	ASSERT (virtual_cockpit_inst3d);
//
//	draw_lamp (ka50_lamps.master_caution, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__022);
//
//	draw_lamp (ka50_lamps.left_engine_fire, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__019);
//
//	draw_lamp (ka50_lamps.apu_fire, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__020);
//
//	draw_lamp (ka50_lamps.right_engine_fire, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__021);
//
//	draw_lamp (ka50_lamps.fire_extinguiser, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__018);
//
//	draw_lamp (ka50_lamps.hydraulic_pressure, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__003);
//
//	draw_lamp (ka50_lamps.oil_pressure, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__004);
//
//	draw_lamp (ka50_lamps.oil_temperature, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__005);
//
//	draw_lamp (ka50_lamps.overtorque, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__000);
//
//	draw_lamp (ka50_lamps.rotor_rpm, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__001);
//
//	draw_lamp (ka50_lamps.fuel_low, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__002);
//
//	draw_lamp (ka50_lamps.rotor_brake, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__006);
//
//	draw_lamp (ka50_lamps.wheel_brake, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__007);
//
//	draw_lamp (ka50_lamps.navigation_lights, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__008);
//
//	draw_lamp (ka50_lamps.hover_hold, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__009);
//
//	draw_lamp (ka50_lamps.altitude_hold, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__010);
//
//	draw_lamp (ka50_lamps.auto_pilot, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__011);
//
//	draw_lamp (ka50_lamps.laser, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__013);
//
//	draw_lamp (ka50_lamps.radar_jammer, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__014);
//
//	draw_lamp (ka50_lamps.ir_jammer, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__015);
//
//	draw_lamp (ka50_lamps.auto_counter_measures, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__016);
//
//	draw_lamp (ka50_lamps.ase_auto_page, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__017);
//
//	draw_lamp (ka50_lamps.gear_damaged, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__024);
//
//	draw_lamp (ka50_lamps.gear_status, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_LAMP__023);
//
//	draw_lamp (ka50_lamps.gear_red, TEXTURE_ANIMATION_INDEX_HOKUM_COCKPIT_GEAR__029);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
