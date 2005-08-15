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

struct AIRCRAFT_DATA
{
	char
		*full_name,
		*long_display_name,
		*short_display_name,
		*easy_display_name;

	object_3d_index_numbers
		default_3d_shape;

	gunship_types
		gunship_type;

	entity_forces
		force;

	weapon_config_types
		default_weapon_config_type,
		min_weapon_config_type,
		max_weapon_config_type,
		air_to_air_weapon_config_type,
		air_to_surface_weapon_config_type,
		scout_weapon_config_type;

	entity_sub_types
		default_weapon_type;

	target_symbol_types
		target_symbol_type;

	target_priority_types
		target_priority_type;

	force_info_catagories
		force_info_catagory;

	threat_types
		threat_type;

	view_categories
		view_category;

	view_types
		view_type;

	int
		map_icon;

	float
		centre_of_gravity_to_ground_distance,
		centre_of_gravity_to_ground_distance_destroyed,
		chase_view_min_distance,
		chase_view_max_distance,
		chase_view_min_distance_test,
		chase_view_max_distance_test,
		cruise_velocity,
		cruise_altitude,
		attack_altitude,
		destroyed_bank_offset,
		destroyed_pitch_offset,
		fuselage_angle,
		liftoff_velocity,
		main_rotor_shaft_angle,
		main_rotor_direction,
		main_rotor_blade_droop_angle,
		propellor_direction,
		max_turn_rate,
		max_roll,
		max_vertical_turn_allowance,
		avoidance_radius,
		g_max,
		power_output,
		tail_rotor_direction,
		recon_radius,
		target_scan_delay,
		air_scan_range,
		surface_scan_range,
		potential_air_to_air_threat,
		potential_air_to_surface_threat,
		ammo_economy,
		fuel_default_weight,
		fuel_economy,
		// Xhit: added "number_of_main_rotors" for downwash effect. (030328) 
		// The reason why it is a float is because that for some reason all integer values are packed
		// where float can be choosen not to be packed. 
		number_of_main_rotors,
		// Xhit: added "main_rotor_radius" for downwash effect. (030328) 
		main_rotor_radius;

	int
		initial_damage_level;

	unsigned int
		explosive_quality 	: NUM_EXPLOSIVE_QUALITY_BITS,
		explosive_power 		: NUM_EXPLOSIVE_POWER_BITS,
		offensive_capability	: 1,
		player_controllable	: 1,
		points_value			: 12;

	sound_sample_indices
		continuous_sound_effect_index,
		wind_up_sound_effect_index,
		wind_down_sound_effect_index;
};

typedef struct AIRCRAFT_DATA aircraft_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition
extern aircraft_data
	aircraft_database[NUM_ENTITY_SUB_TYPE_AIRCRAFT];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
