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

void overload_weapon_functions (void)
{
	overload_mobile_functions (ENTITY_TYPE_WEAPON);

	overload_weapon_create_functions ();

	overload_weapon_destroy_functions ();

	overload_weapon_draw_functions ();

	overload_weapon_float_value_functions ();

	overload_weapon_int_value_functions ();

	overload_weapon_list_functions ();

	overload_weapon_pack_functions ();

	overload_weapon_string_functions ();

	overload_weapon_update_functions ();

	overload_weapon_vec3d_functions ();

	validate_weapon_database ();

	initialise_target_point_offsets ();
}

float get_weapon_current_weight(float lifetime, entity_sub_types subtype)
{
	if (lifetime > 0)
	{
		float boost_consumption = weapon_database[subtype].boost_power * weapon_database[subtype].boost_time;
		float sustain_consumption = weapon_database[subtype].sustain_power * weapon_database[subtype].sustain_time;
		float boost_scale = boost_consumption / (boost_consumption + sustain_consumption);
		float sustain_scale = sustain_consumption / (boost_consumption + sustain_consumption);
		float sustain_time_scale = weapon_database[subtype].sustain_time / (weapon_database[subtype].boost_time + weapon_database[subtype].sustain_time);
		float boost_time_scale = weapon_database[subtype].boost_time / (weapon_database[subtype].boost_time + weapon_database[subtype].sustain_time);
		float time_scale = lifetime / (weapon_database[subtype].boost_time + weapon_database[subtype].sustain_time);
		float delta_weight = weapon_database[subtype].start_weight - weapon_database[subtype].final_weight;
		float boost_fuel_weight = delta_weight * boost_scale * max(0, (time_scale - sustain_time_scale) / boost_time_scale);
		float sustain_fuel_weight = sustain_time_scale ? (delta_weight * sustain_scale * min(1, time_scale / sustain_time_scale)) : 0;
		
		return weapon_database[subtype].final_weight + boost_fuel_weight + sustain_fuel_weight;
	}
	else
		return weapon_database[subtype].final_weight;
}


float get_weapon_drag(float speed, float alt, float diameter, float drag_coefficient)
{
	float
		m = 0.0289644, // physics constants
		r = 8.31447,
		l = 0.0065,
		p0 = 101325, // standard air pressure, Pa
		t0 = 288.15, // standard temperature, K
		area = PI * diameter * diameter / 4, // projectile area, m^2
		t = t0 - l * alt, // actual temperature, K
		p = p0 * exp(- (G * m * alt) / (r * t0)), // air pressure, Pa
		air_density = p * m / (r * t), // kg/m^3
		mach = speed / (20.046 * sqrt(t)), // velocity, mach
		cd; // drag coefficient

	// get drag coefficient (air resistance law of 1943)
	
	if (mach <= 0.8)
		cd = 0.158;
	else if (mach <= 0.9)
		cd = 0.137 * mach * mach  + 0.0865 * mach + 0.000898;
	else if (mach <= 1.0)
		cd = 1.35 * mach - 1.025;
	else if (mach <= 1.4)
		cd = - 0.925 * mach * mach + 2.335 * mach - 1.085;
	else if (mach <= 4)
		cd = - 0.0917 * mach + 0.4993;
	else
		cd = 0.1325;

	return 0.5 * drag_coefficient * air_density * speed * speed * cd * area;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
