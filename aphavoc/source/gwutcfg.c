//
//     Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
//     Copyright (C) 2000 Empire Interactive (Europe) Ltd,
//     677 High Road, North Finchley, London N12 0DA
//
//     Please see the document LICENSE.TXT for the full licence agreement
//
// 2. LICENCE
//  2.1
//    Subject to the provisions of this Agreement we now grant to you the
//    following rights in respect of the Source Code:
//   2.1.1
//    the non-exclusive right to Exploit  the Source Code and Executable
//    Code on any medium; and
//   2.1.2
//    the non-exclusive right to create and distribute Derivative Works.
//  2.2
//    Subject to the provisions of this Agreement we now grant you the
//    following rights in respect of the Object Code:
//   2.2.1
//    the non-exclusive right to Exploit the Object Code on the same
//    terms and conditions set out in clause 3, provided that any
//    distribution is done so on the terms of this Agreement and is
//    accompanied by the Source Code and Executable Code (as
//    applicable).
//
// 3. GENERAL OBLIGATIONS
//  3.1
//    In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1
//    that when you distribute the Source Code or Executable Code or
//    any Derivative Works to Recipients you will also include the
//    terms of this Agreement;
//   3.1.2
//    that when you make the Source Code, Executable Code or any
//    Derivative Works ("Materials") available to download, you will
//    ensure that Recipients must accept the terms of this Agreement
//    before being allowed to download such Materials;
//   3.1.3
//    that by Exploiting the Source Code or Executable Code you may
//    not impose any further restrictions on a Recipient's subsequent
//    Exploitation of the Source Code or Executable Code other than
//    those contained in the terms and conditions of this Agreement;
//   3.1.4
//    not (and not to allow any third party) to profit or make any
//    charge for the Source Code, or Executable Code, any
//    Exploitation of the Source Code or Executable Code, or for any
//    Derivative Works;
//   3.1.5
//    not to place any restrictions on the operability of the Source
//    Code;
//   3.1.6
//    to attach prominent notices to any Derivative Works stating
//    that you have changed the Source Code or Executable Code and to
//    include the details anddate of such change; and
//   3.1.7
//    not to Exploit the Source Code or Executable Code otherwise than
//    as expressly permitted by  this Agreement.
//

//
//   VJ WUT mod, date: 23-Feb-04
//
//   Description: NEW GWUT file handler
//
//   Details: http://home.planet.nl/~jette073
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CURRENT_HEADER "[GWUT file, version 1.3]"

#define IntToBin(v) (v==0?0:(int)(log((double)v)/log(2.0)))
#define BinToInt(v) (v==0?0:(int)exp((double)v*log(2.0))+1)


int INCLUDE_WEAPON_TYPES;
int WRITE_HEADER;
int READ_HEADER;

void DumpGWutInfo(char *filename)
{
	  FILE *fout;
	  int i, j, k;

	INCLUDE_WEAPON_TYPES = 0;
	WRITE_HEADER = 0;

	 fout = fopen(filename,"w");

	fprintf(fout,CURRENT_HEADER);
	fprintf(fout,"\n");

//aphavoc\source\entity\mobile\aircraft\ac_dbase.h
	fprintf(fout,"[AIRCRAFT]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,","full_name");
	fprintf(fout,"%s,","force");
	fprintf(fout,"%s,","default_weapon_config_type");
	fprintf(fout,"%s,","min_weapon_config_type");
	fprintf(fout,"%s,","max_weapon_config_type");
	fprintf(fout,"%s,","air_to_air_weapon_config_type");
	fprintf(fout,"%s,","air_to_surface_weapon_config_type");
	fprintf(fout,"%s,","scout_weapon_config_type");
	fprintf(fout,"%s,","default_weapon_type");
	fprintf(fout,"%s,","target_symbol_type");
	fprintf(fout,"%s,","target_priority_type");
	fprintf(fout,"%s,","force_info_catagory");
	fprintf(fout,"%s,","threat_type");
	//fprintf(fout,"%s,","view_category");
	//fprintf(fout,"%s,","view_type");
	//fprintf(fout,"%s,","map_icon");
	fprintf(fout,"%s,","centre_of_gravity_to_ground_distance");
	fprintf(fout,"%s,","centre_of_gravity_to_ground_distance_destroyed");
	fprintf(fout,"%s,","chase_view_min_distance");
	fprintf(fout,"%s,","chase_view_max_distance");
	fprintf(fout,"%s,","chase_view_min_distance_test");
	fprintf(fout,"%s,","chase_view_max_distance_test");
	fprintf(fout,"%s,","cruise_velocity");
	fprintf(fout,"%s,","cruise_altitude");
	fprintf(fout,"%s,","attack_altitude");
	fprintf(fout,"%s,","destroyed_bank_offset");
	fprintf(fout,"%s,","destroyed_pitch_offset");
	fprintf(fout,"%s,","fuselage_angle");
	fprintf(fout,"%s,","liftoff_velocity");
	fprintf(fout,"%s,","main_rotor_shaft_angle");
	fprintf(fout,"%s,","main_rotor_direction");
	fprintf(fout,"%s,","main_rotor_blade_droop_angle");
	fprintf(fout,"%s,","propellor_direction");
	fprintf(fout,"%s,","max_turn_rate");
	fprintf(fout,"%s,","max_roll");
	fprintf(fout,"%s,","max_vertical_turn_allowance");
	fprintf(fout,"%s,","avoidance_radius");
	fprintf(fout,"%s,","g_max");
	fprintf(fout,"%s,","power_output");
	fprintf(fout,"%s,","tail_rotor_direction");
	fprintf(fout,"%s,","recon_radius");
	fprintf(fout,"%s,","target_scan_delay");
	fprintf(fout,"%s,","air_scan_range");
	fprintf(fout,"%s,","surface_scan_range");
	fprintf(fout,"%s,","potential_air_to_air_threat");
	fprintf(fout,"%s,","potential_air_to_surface_threat");
	fprintf(fout,"%s,","ammo_economy");
	fprintf(fout,"%s,","fuel_default_weight");
	fprintf(fout,"%s,","fuel_economy");
	fprintf(fout,"%s,","number_of_main_rotors");
	fprintf(fout,"%s,","main_rotor_radius");
	fprintf(fout,"%s,","initial_damage_level");
	fprintf(fout,"%s,","explosive_quality");
	fprintf(fout,"%s,","explosive_power");
	fprintf(fout,"%s,","offensive_capability");
	fprintf(fout,"%s,","player_controllable");
	fprintf(fout,"%s\n","points_value");
	}
  for (i = 0; i < NUM_ENTITY_SUB_TYPE_AIRCRAFT; i++)
  {
		fprintf(fout,"%d,",i);
		fprintf(fout,"%s,",aircraft_database[i].full_name);
		fprintf(fout,"%d,",aircraft_database[i].force);
		fprintf(fout,"%d,",aircraft_database[i].default_weapon_config_type);
		fprintf(fout,"%d,",aircraft_database[i].min_weapon_config_type);
		fprintf(fout,"%d,",aircraft_database[i].max_weapon_config_type);
		fprintf(fout,"%d,",aircraft_database[i].air_to_air_weapon_config_type);
		fprintf(fout,"%d,",aircraft_database[i].air_to_surface_weapon_config_type);
		fprintf(fout,"%d,",aircraft_database[i].scout_weapon_config_type);
		fprintf(fout,"%d,",aircraft_database[i].default_weapon_type);
		fprintf(fout,"%d,",aircraft_database[i].target_symbol_type);
		fprintf(fout,"%d,",aircraft_database[i].target_priority_type);
		fprintf(fout,"%d,",aircraft_database[i].force_info_catagory);
		fprintf(fout,"%d,",aircraft_database[i].threat_type);
		//fprintf(fout,"%d,",aircraft_database[i].view_category);
		//fprintf(fout,"%d,",aircraft_database[i].view_type);
		//fprintf(fout,"%d,",aircraft_database[i].map_icon);
		fprintf(fout,"%g,",aircraft_database[i].centre_of_gravity_to_ground_distance);
		fprintf(fout,"%g,",aircraft_database[i].centre_of_gravity_to_ground_distance_destroyed);
		fprintf(fout,"%g,",aircraft_database[i].chase_view_min_distance);
		fprintf(fout,"%g,",aircraft_database[i].chase_view_max_distance);
		fprintf(fout,"%g,",aircraft_database[i].chase_view_min_distance_test);
		fprintf(fout,"%g,",aircraft_database[i].chase_view_max_distance_test);
		fprintf(fout,"%g,",aircraft_database[i].cruise_velocity);
		fprintf(fout,"%g,",aircraft_database[i].cruise_altitude);
		fprintf(fout,"%g,",aircraft_database[i].attack_altitude);
		fprintf(fout,"%g,",deg(aircraft_database[i].destroyed_bank_offset));
		fprintf(fout,"%g,",deg(aircraft_database[i].destroyed_pitch_offset));
		fprintf(fout,"%g,",deg(aircraft_database[i].fuselage_angle));
		fprintf(fout,"%g,",aircraft_database[i].liftoff_velocity);
		fprintf(fout,"%g,",deg(aircraft_database[i].main_rotor_shaft_angle));
		fprintf(fout,"%g,",aircraft_database[i].main_rotor_direction);
		fprintf(fout,"%g,",deg(aircraft_database[i].main_rotor_blade_droop_angle));
		fprintf(fout,"%g,",aircraft_database[i].propellor_direction);
		fprintf(fout,"%g,",deg(aircraft_database[i].max_turn_rate));
		fprintf(fout,"%g,",deg(aircraft_database[i].max_roll));
		fprintf(fout,"%g,",aircraft_database[i].max_vertical_turn_allowance);
		fprintf(fout,"%g,",aircraft_database[i].avoidance_radius);
		fprintf(fout,"%g,",aircraft_database[i].g_max);
		fprintf(fout,"%g,",aircraft_database[i].power_output);
		fprintf(fout,"%g,",deg(aircraft_database[i].tail_rotor_direction));
		fprintf(fout,"%g,",aircraft_database[i].recon_radius);
		fprintf(fout,"%g,",aircraft_database[i].target_scan_delay);
		fprintf(fout,"%g,",aircraft_database[i].air_scan_range);
		fprintf(fout,"%g,",aircraft_database[i].surface_scan_range);
		fprintf(fout,"%g,",aircraft_database[i].potential_air_to_air_threat);
		fprintf(fout,"%g,",aircraft_database[i].potential_air_to_surface_threat);
		fprintf(fout,"%g,",aircraft_database[i].ammo_economy);
		fprintf(fout,"%g,",aircraft_database[i].fuel_default_weight);
		fprintf(fout,"%g,",aircraft_database[i].fuel_economy);
		fprintf(fout,"%g,",aircraft_database[i].number_of_main_rotors);
		fprintf(fout,"%g,",aircraft_database[i].main_rotor_radius);
		fprintf(fout,"%d,",aircraft_database[i].initial_damage_level);
		fprintf(fout,"%d,",aircraft_database[i].explosive_quality);
		fprintf(fout,"%d,",aircraft_database[i].explosive_power);
		fprintf(fout,"%d,",aircraft_database[i].offensive_capability);//y/n  : 1,
		fprintf(fout,"%d,",aircraft_database[i].player_controllable);//y/n   : 1,
		fprintf(fout,"%d\n",aircraft_database[i].points_value);//???         : 12;
	}

//aphavoc\source\entity\mobile\vehicle\vh_dbase.h
	fprintf(fout,"[VEHICLES]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,","full_name");
	fprintf(fout,"%s,","force");
	fprintf(fout,"%s,","default_weapon_config_type");
	fprintf(fout,"%s,","min_weapon_config_type");
	fprintf(fout,"%s,","max_weapon_config_type");
	fprintf(fout,"%s,","default_weapon_type");
	fprintf(fout,"%s,","target_type");
	fprintf(fout,"%s,","target_symbol_type");
	fprintf(fout,"%s,","target_priority_type");
	fprintf(fout,"%s,","force_info_catagory");
	fprintf(fout,"%s,","threat_type");
	//fprintf(fout,"%s,","view_category");
	//fprintf(fout,"%s,","view_type");
	//fprintf(fout,"%s,","map_icon");
	fprintf(fout,"%s,","carries_smoke_grenades");
	fprintf(fout,"%s,","chase_view_min_distance");
	fprintf(fout,"%s,","chase_view_max_distance");
	fprintf(fout,"%s,","chase_view_min_distance_test");
	fprintf(fout,"%s,","chase_view_max_distance_test");
	fprintf(fout,"%s,","cruise_velocity");
	fprintf(fout,"%s,","axle_length");
	fprintf(fout,"%s,","max_acceleration");
	fprintf(fout,"%s,","max_turn_rate");
	fprintf(fout,"%s,","g_max");
	fprintf(fout,"%s,","power_output");
	fprintf(fout,"%s,","recon_radius");
	fprintf(fout,"%s,","target_scan_delay");
	fprintf(fout,"%s,","air_scan_floor");
	fprintf(fout,"%s,","air_scan_ceiling");
	fprintf(fout,"%s,","air_scan_range");
	fprintf(fout,"%s,","surface_scan_range");
	fprintf(fout,"%s,","potential_surface_to_air_threat");
	fprintf(fout,"%s,","potential_surface_to_surface_threat");
	fprintf(fout,"%s,","ammo_economy");
	fprintf(fout,"%s,","fuel_economy");
	fprintf(fout,"%s,","armour_front");
	fprintf(fout,"%s,","armour_side");
	fprintf(fout,"%s,","armour_rear");
	fprintf(fout,"%s,","initial_damage_level");
	fprintf(fout,"%s,","warhead_effective_class");
	fprintf(fout,"%s,","explosive_quality");
	fprintf(fout,"%s,","explosive_power");
	fprintf(fout,"%s,","offensive_capability");
	fprintf(fout,"%s\n","points_value");
	}
	for (i = 0; i < NUM_ENTITY_SUB_TYPE_VEHICLES; i++)
	{
		fprintf(fout,"%d,",i);
		switch(vehicle_database[i].default_3d_shape) {
			case OBJECT_3D_US_MARINE_WALK: fprintf(fout,"%s Unarmed US,",vehicle_database[i].full_name);   break;
			case OBJECT_3D_US_MARINE_STANDING: fprintf(fout,"%s Standing US,",vehicle_database[i].full_name);  break;
			case OBJECT_3D_US_MARINE_KNEELING: fprintf(fout,"%s Kneeling US,",vehicle_database[i].full_name);  break;
			case OBJECT_3D_CIS_MARINE_WALK: fprintf(fout,"%s Unarmed CIS,",vehicle_database[i].full_name); break;
			case OBJECT_3D_RUSSIAN_MARINE_STANDING: fprintf(fout,"%s Standing CIS,",vehicle_database[i].full_name);break;
			case OBJECT_3D_RUSSIAN_MARINE_KNEELING: fprintf(fout,"%s Kneeling CIS,",vehicle_database[i].full_name);break;
			case OBJECT_3D_M_923A1_COVERED: fprintf(fout,"%s Covered,",vehicle_database[i].full_name); break;
			case OBJECT_3D_M_923A1_OPEN: fprintf(fout,"%s Open,",vehicle_database[i].full_name); break;
			default: fprintf(fout,"%s,",vehicle_database[i].full_name);
		}
		fprintf(fout,"%d,",vehicle_database[i].force);
		fprintf(fout,"%d,",vehicle_database[i].default_weapon_config_type);
		fprintf(fout,"%d,",vehicle_database[i].min_weapon_config_type);
		fprintf(fout,"%d,",vehicle_database[i].max_weapon_config_type);
		fprintf(fout,"%d,",vehicle_database[i].default_weapon_type);
		fprintf(fout,"%d,",vehicle_database[i].target_type);
		fprintf(fout,"%d,",vehicle_database[i].target_symbol_type);
		fprintf(fout,"%d,",vehicle_database[i].target_priority_type);
		fprintf(fout,"%d,",vehicle_database[i].force_info_catagory);
		fprintf(fout,"%d,",vehicle_database[i].threat_type);
		//fprintf(fout,"%d,",vehicle_database[i].view_category);
		//fprintf(fout,"%d,",vehicle_database[i].view_type);
		//fprintf(fout,"%d,",vehicle_database[i].map_icon);
		fprintf(fout,"%d,",vehicle_database[i].carries_smoke_grenades);
		fprintf(fout,"%g,",vehicle_database[i].chase_view_min_distance);
		fprintf(fout,"%g,",vehicle_database[i].chase_view_max_distance);
		fprintf(fout,"%g,",vehicle_database[i].chase_view_min_distance_test);
		fprintf(fout,"%g,",vehicle_database[i].chase_view_max_distance_test);
		fprintf(fout,"%g,",vehicle_database[i].cruise_velocity);
		fprintf(fout,"%g,",vehicle_database[i].axle_length);
		fprintf(fout,"%g,",vehicle_database[i].max_acceleration);
		fprintf(fout,"%g,",deg(vehicle_database[i].max_turn_rate));
		fprintf(fout,"%g,",vehicle_database[i].g_max);
		fprintf(fout,"%g,",vehicle_database[i].power_output);
		fprintf(fout,"%g,",vehicle_database[i].recon_radius);
		fprintf(fout,"%g,",vehicle_database[i].target_scan_delay);
		fprintf(fout,"%g,",vehicle_database[i].air_scan_floor);
		fprintf(fout,"%g,",vehicle_database[i].air_scan_ceiling);
		fprintf(fout,"%g,",vehicle_database[i].air_scan_range);
		fprintf(fout,"%g,",vehicle_database[i].surface_scan_range);
		fprintf(fout,"%g,",vehicle_database[i].potential_surface_to_air_threat);
		fprintf(fout,"%g,",vehicle_database[i].potential_surface_to_surface_threat);
		fprintf(fout,"%g,",vehicle_database[i].ammo_economy);
		fprintf(fout,"%g,",vehicle_database[i].fuel_economy);
		fprintf(fout,"%g,",vehicle_database[i].armour_front);
		fprintf(fout,"%g,",vehicle_database[i].armour_side);
		fprintf(fout,"%g,",vehicle_database[i].armour_rear);
		fprintf(fout,"%d,",vehicle_database[i].initial_damage_level);
		fprintf(fout,"%d,",IntToBin(vehicle_database[i].warhead_effective_class)); //!! convert to power of 2
		fprintf(fout,"%d,",vehicle_database[i].explosive_quality);
		fprintf(fout,"%d,",vehicle_database[i].explosive_power);
		fprintf(fout,"%d,",vehicle_database[i].offensive_capability);
		fprintf(fout,"%d\n",vehicle_database[i].points_value);
	}

//aphavoc\source\entity\mobile\weapon\wn_dbase.h
	fprintf(fout,"[WEAPONS]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,","full_name");
// fprintf(fout,"%s,","weapon_nr");
	fprintf(fout,"%s,","guidance_type");
	fprintf(fout,"%s,","aiming_type");
	fprintf(fout,"%s,","decoy_type");
	fprintf(fout,"%s,","warhead_type");
	fprintf(fout,"%s,","threat_type");
	fprintf(fout,"%s,","report_ammo_low_count");
	fprintf(fout,"%s,","gun_shake");
	fprintf(fout,"%s,","soft_damage_capability");
	fprintf(fout,"%s,","hard_damage_capability");
	fprintf(fout,"%s,","smoke_trail_type");
	fprintf(fout,"%s,","acquire_parent_forward_velocity");
	fprintf(fout,"%s,","ignore_gravity");
	fprintf(fout,"%s,","survive_ground_impact");
	fprintf(fout,"%s,","in_flight_collision_check");
	fprintf(fout,"%s,","viewable_weapon");
	fprintf(fout,"%s,","boresight_weapon");
	fprintf(fout,"%s,","hellfire_flight_profile");
// fprintf(fout,"%s,","weapon_class");
	fprintf(fout,"%s,","weapon_class_air_to_air");
	fprintf(fout,"%s,","weapon_class_air_to_surface");
	fprintf(fout,"%s,","weapon_class_surface_to_air");
	fprintf(fout,"%s,","weapon_class_surface_to_surface");
	fprintf(fout,"%s,","weapon_class_decoy");
	fprintf(fout,"%s,","weapon_class_cargo");
	fprintf(fout,"%s,","weapon_class_debris");
	fprintf(fout,"%s,","weight");
	fprintf(fout,"%s,","min_range");
	fprintf(fout,"%s,","max_range");
	fprintf(fout,"%s,","effective_range");
	fprintf(fout,"%s,","min_range_loal");
	fprintf(fout,"%s,","max_range_loal");
	fprintf(fout,"%s,","max_range_error_ratio");
	fprintf(fout,"%s,","muzzle_velocity");
	fprintf(fout,"%s,","muzzle_velocity_max_error");
	fprintf(fout,"%s,","cruise_velocity");
	fprintf(fout,"%s,","g_max");
	fprintf(fout,"%s,","burn_time");
	fprintf(fout,"%s,","cruise_time");
	fprintf(fout,"%s,","cruise_time_max_error");
	fprintf(fout,"%s,","inhibit_time");
	fprintf(fout,"%s,","burst_duration");
	fprintf(fout,"%s,","rate_of_fire");
	fprintf(fout,"%s,","reload_time");
	fprintf(fout,"%s\n","max_launch_angle_error");
	}
	for (i = 0; i < NUM_ENTITY_SUB_TYPE_WEAPONS; i++)
	{
		fprintf(fout,"%d,",i);
		fprintf(fout,"%s,",weapon_database[i].full_name);
//    fprintf(fout,"%d,",i);
//    fprintf(fout,"%s,",weapon_database[i].hud_name);
//    fprintf(fout,"%s,",weapon_database[i].mfd_name);
//    fprintf(fout,"%s,",weapon_database[i].weapon_loading_list_name);
//    fprintf(fout,"%s,",weapon_database[i].weapon_loading_name_text);
//    fprintf(fout,"%d,",weapon_database[i].default_3d_shape);
		fprintf(fout,"%d,",weapon_database[i].guidance_type);
		fprintf(fout,"%d,",weapon_database[i].aiming_type);
		fprintf(fout,"%d,",weapon_database[i].decoy_type);
		fprintf(fout,"%d,",weapon_database[i].warhead_type);
		fprintf(fout,"%d,",weapon_database[i].threat_type);
//    fprintf(fout,"%d,",weapon_database[i].launch_sound_effect_sub_type);
//    fprintf(fout,"%d,",weapon_database[i].interior_launch_sound_effect);
//    fprintf(fout,"%d,",weapon_database[i].exterior_launch_sound_effect);
//    fprintf(fout,"%d,",weapon_database[i].continuous_sound_effect);
//    fprintf(fout,"%d,",weapon_database[i].weapon_selected_cpg_speech);
//    fprintf(fout,"%d,",weapon_database[i].weapon_low_cpg_speech);
//    fprintf(fout,"%d,",weapon_database[i].weapon_out_cpg_speech);
//    fprintf(fout,"%d,",weapon_database[i].weapon_launched_cpg_speech);
//    fprintf(fout,"%d,",weapon_database[i].weapon_launched_wingman_speech);
		fprintf(fout,"%d,",weapon_database[i].report_ammo_low_count);
		fprintf(fout,"%d,",weapon_database[i].gun_shake);
		fprintf(fout,"%d,",weapon_database[i].soft_damage_capability);
		fprintf(fout,"%d,",weapon_database[i].hard_damage_capability);
		fprintf(fout,"%d,",weapon_database[i].smoke_trail_type);
		fprintf(fout,"%d,",weapon_database[i].acquire_parent_forward_velocity);
		fprintf(fout,"%d,",weapon_database[i].ignore_gravity);
		fprintf(fout,"%d,",weapon_database[i].survive_ground_impact);
		fprintf(fout,"%d,",weapon_database[i].in_flight_collision_check);
		fprintf(fout,"%d,",weapon_database[i].viewable_weapon);
		fprintf(fout,"%d,",weapon_database[i].boresight_weapon);// meaningful   for featured helicopters only
		fprintf(fout,"%d,",weapon_database[i].hellfire_flight_profile);// meaningful for Hellfire missiles only
//    fprintf(fout,"%d,",weapon_database[i].weapon_class);
		fprintf(fout,"%d,",weapon_database[i].weapon_class & 1   ? 1:0);//_air_to_air
		fprintf(fout,"%d,",weapon_database[i].weapon_class & 2   ? 1:0);//_air_to_surface
		fprintf(fout,"%d,",weapon_database[i].weapon_class & 4   ? 1:0);//_surface_to_air
		fprintf(fout,"%d,",weapon_database[i].weapon_class & 8   ? 1:0);//_surface_to_surface
		fprintf(fout,"%d,",weapon_database[i].weapon_class & 16 ?   1:0);//_decoy
		fprintf(fout,"%d,",weapon_database[i].weapon_class & 32 ?   1:0);//_cargo
		fprintf(fout,"%d,",weapon_database[i].weapon_class & 64 ?   1:0);//_debris
		fprintf(fout,"%g,",weapon_database[i].weight);// kilogrammes
		fprintf(fout,"%g,",weapon_database[i].min_range);// metres
		fprintf(fout,"%g,",weapon_database[i].max_range);// metres
		fprintf(fout,"%g,",weapon_database[i].effective_range);// metres
		fprintf(fout,"%g,",weapon_database[i].min_range_loal);// metres
		fprintf(fout,"%g,",weapon_database[i].max_range_loal);// metres
		fprintf(fout,"%g,",weapon_database[i].max_range_error_ratio);// max range error/max range
		fprintf(fout,"%g,",weapon_database[i].muzzle_velocity);// meters/second
		fprintf(fout,"%g,",weapon_database[i].muzzle_velocity_max_error);// meters/second
		fprintf(fout,"%g,",weapon_database[i].cruise_velocity);// meters/second
		fprintf(fout,"%g,",weapon_database[i].g_max);// g
		fprintf(fout,"%g,",weapon_database[i].burn_time);// seconds
		fprintf(fout,"%g,",weapon_database[i].cruise_time);// seconds
		fprintf(fout,"%g,",weapon_database[i].cruise_time_max_error);// seconds
		fprintf(fout,"%g,",weapon_database[i].inhibit_time);// seconds
		fprintf(fout,"%g,",weapon_database[i].burst_duration);// seconds
		fprintf(fout,"%g,",weapon_database[i].rate_of_fire);// rounds/minute
		fprintf(fout,"%g,",weapon_database[i].reload_time);// seconds
		fprintf(fout,"%g\n",deg(weapon_database[i].max_launch_angle_error));// radians
	}

	//aphavoc\source\entity\special\keysite\ks_dbase.h
	fprintf(fout,"[KEYSITES]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,", "full_name");
// fprintf(fout,"%s,", "default_supply_usage");
// fprintf(fout,"%s,", "air_to_ground_ammo_supply_level"); // is not used in code according to comments
// fprintf(fout,"%s,", "air_to_air_ammo_supply_level");
	fprintf(fout,"%s,", "ammo_supply_level");
	fprintf(fout,"%s,", "fuel_supply_level");
	fprintf(fout,"%s,", "importance");
	fprintf(fout,"%s,", "minimum_efficiency");
	fprintf(fout,"%s,", "importance_radius");
	fprintf(fout,"%s,", "air_coverage_radius");
	fprintf(fout,"%s,", "recon_distance");
	fprintf(fout,"%s,", "sector_side_max_value");
// fprintf(fout,"%s,", "map_layer_type");
// fprintf(fout,"%s,", "map_icon");
	fprintf(fout,"%s,", "align_with_terrain");
// fprintf(fout,"%s,", "unique_name");
	fprintf(fout,"%s,", "hidden_by_fog_of_war");
	fprintf(fout,"%s,", "air_force_capacity");
	fprintf(fout,"%s,", "report_ammo_level");
	fprintf(fout,"%s,", "report_fuel_level");
	fprintf(fout,"%s,", "assign_task_count");
	fprintf(fout,"%s,", "reserve_task_count");
	fprintf(fout,"%s,", "requires_cap");
	fprintf(fout,"%s,", "requires_barcap");
	fprintf(fout,"%s,", "repairable");
	fprintf(fout,"%s,", "oca_target");
	fprintf(fout,"%s,", "recon_target");
	fprintf(fout,"%s,", "ground_strike_target");
	fprintf(fout,"%s,", "ship_strike_target");
	fprintf(fout,"%s,", "troop_insertion_target");
	fprintf(fout,"%s\n","campaign_objective");
	}
	for (i = 0; i <   NUM_ENTITY_SUB_TYPE_KEYSITES; i++)
	{
		fprintf(fout,"%d,",i);
		fprintf(fout,"%s,",   keysite_database[i].full_name);
//    fprintf(fout,"%d,",   keysite_database[i].default_supply_usage);
//    fprintf(fout,"%g,",   keysite_database[i].default_supply_usage.air_to_ground_ammo_supply_level);
//    fprintf(fout,"%g,",   keysite_database[i].default_supply_usage.air_to_air_ammo_supply_level);
		fprintf(fout,"%g,",   keysite_database[i].default_supply_usage.ammo_supply_level);
		fprintf(fout,"%g,",   keysite_database[i].default_supply_usage.fuel_supply_level);
		fprintf(fout,"%g,",   keysite_database[i].importance);
		fprintf(fout,"%g,",   keysite_database[i].minimum_efficiency);
		fprintf(fout,"%g,",   keysite_database[i].importance_radius);
		fprintf(fout,"%g,",   keysite_database[i].air_coverage_radius);
		fprintf(fout,"%g,",   keysite_database[i].recon_distance);
		fprintf(fout,"%g,",   keysite_database[i].sector_side_max_value);
//    fprintf(fout,"%d,",   keysite_database[i].map_layer_type);
//    fprintf(fout,"%d,",   keysite_database[i].map_icon);
		fprintf(fout,"%d,",   keysite_database[i].align_with_terrain);
//    fprintf(fout,"%d,",   keysite_database[i].unique_name);
		fprintf(fout,"%d,",   keysite_database[i].hidden_by_fog_of_war);
		fprintf(fout,"%d,",   keysite_database[i].air_force_capacity);
		fprintf(fout,"%d,",   keysite_database[i].report_ammo_level);
		fprintf(fout,"%d,",   keysite_database[i].report_fuel_level);
		fprintf(fout,"%d,",   keysite_database[i].assign_task_count);
		fprintf(fout,"%d,",   keysite_database[i].reserve_task_count);
		fprintf(fout,"%d,",   keysite_database[i].requires_cap);
		fprintf(fout,"%d,",   keysite_database[i].requires_barcap);
		fprintf(fout,"%d,",   keysite_database[i].repairable);
		fprintf(fout,"%d,",   keysite_database[i].oca_target);
		fprintf(fout,"%d,",   keysite_database[i].recon_target);
		fprintf(fout,"%d,",   keysite_database[i].ground_strike_target);
		fprintf(fout,"%d,",   keysite_database[i].ship_strike_target);
		fprintf(fout,"%d,",   keysite_database[i].troop_insertion_target);
		fprintf(fout,"%d\n",  keysite_database[i].campaign_objective);
	}

//aphavoc\source\entity\special\group\gp_dbase.h
	fprintf(fout,"[GROUPS]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,",  "full_name");
	fprintf(fout,"%s,",  "group_category");
	fprintf(fout,"%s,",  "registry_list_type");
	fprintf(fout,"%s,",  "group_list_type");
	fprintf(fout,"%s,",  "movement_type");
	fprintf(fout,"%s,",  "default_landing_type");
	fprintf(fout,"%s,",  "default_entity_type");
	fprintf(fout,"%s,",  "default_blue_force_sub_type");
	fprintf(fout,"%s,",  "default_red_force_sub_type");
	fprintf(fout,"%s,",  "default_group_formation");
	fprintf(fout,"%s,",  "default_group_division");
	fprintf(fout,"%s,",  "maximum_groups_per_division");
// fprintf(fout,"%s,",  "platoon_name");
// fprintf(fout,"%s,",  "platoon_short_name_type");
// fprintf(fout,"%s,",  "map_layer_type");
// fprintf(fout,"%s,",  "map_icon");
	fprintf(fout,"%s,",  "rearming_time");
	fprintf(fout,"%s,",  "frontline_flag");
	fprintf(fout,"%s,",  "local_only_group");
	fprintf(fout,"%s,",  "default_engage_enemy");
	fprintf(fout,"%s,",  "amalgamate");
	fprintf(fout,"%s,",  "platoon_id_type");
	fprintf(fout,"%s,",  "maximum_member_count");
	fprintf(fout,"%s,",  "minimum_idle_count");
	fprintf(fout,"%s,",  "resupply_source");
	fprintf(fout,"%s,",  "ai_air_attack_strength");
	fprintf(fout,"%s,",  "ai_ground_attack_strength");
	fprintf(fout,"%s,",  "ai_movement_speed");
	fprintf(fout,"%s,",  "ai_movement_stealth");
	fprintf(fout,"%s,",  "ai_cargo_space");
	fprintf(fout,"%s\n", "ai_troop_space");
	}
	for (i = 0; i < NUM_ENTITY_SUB_TYPE_GROUPS; i++)
	{
		fprintf(fout,"%d,",i);
		if (strstr(group_database[i].full_name,"Infantry") != 0)
		{
			if (i == 19) fprintf(fout,"%s %s,",group_database[i].full_name,"(static)");
			if (i == 20) fprintf(fout,"%s %s,",group_database[i].full_name,"(group)");
			if (i == 21) fprintf(fout,"%s %s,",group_database[i].full_name,"(patrol)");
		}	
		else
			fprintf(fout,"%s,",group_database[i].full_name);
		fprintf(fout,"%d,",group_database[i].group_category);
		fprintf(fout,"%d,",group_database[i].registry_list_type);
		fprintf(fout,"%d,",group_database[i].group_list_type);
		fprintf(fout,"%d,",group_database[i].movement_type);
		fprintf(fout,"%d,",group_database[i].default_landing_type);
		fprintf(fout,"%d,",group_database[i].default_entity_type);
		fprintf(fout,"%d,",group_database[i].default_blue_force_sub_type);
		fprintf(fout,"%d,",group_database[i].default_red_force_sub_type);
		fprintf(fout,"%d,",group_database[i].default_group_formation);
		fprintf(fout,"%d,",group_database[i].default_group_division);
		fprintf(fout,"%d,",group_database[i].maximum_groups_per_division);
//    fprintf(fout,"%s,",group_database[i].platoon_name);
//    fprintf(fout,"%d,",group_database[i].platoon_short_name_type);
//    fprintf(fout,"%d,",group_database[i].map_layer_type);
//    fprintf(fout,"%d,",group_database[i].map_icon);
		fprintf(fout,"%g,",group_database[i].rearming_time);
		fprintf(fout,"%d,",group_database[i].frontline_flag);
		fprintf(fout,"%d,",group_database[i].local_only_group); //y/n
		fprintf(fout,"%d,",group_database[i].default_engage_enemy);//y/n
		fprintf(fout,"%d,",group_database[i].amalgamate);
		fprintf(fout,"%d,",group_database[i].platoon_id_type);
		fprintf(fout,"%d,",group_database[i].maximum_member_count);
		fprintf(fout,"%d,",group_database[i].minimum_idle_count);
		fprintf(fout,"%d,",group_database[i].resupply_source);
		fprintf(fout,"%d,",group_database[i].ai_stats.air_attack_strength);
		fprintf(fout,"%d,",group_database[i].ai_stats.ground_attack_strength);
		fprintf(fout,"%d,",group_database[i].ai_stats.movement_speed);
		fprintf(fout,"%d,",group_database[i].ai_stats.movement_stealth);
		fprintf(fout,"%d,",group_database[i].ai_stats.cargo_space);
		fprintf(fout,"%d\n",group_database[i].ai_stats.troop_space);
	}


//aphavoc\source\entity\special\task\ts_dbase.h
	fprintf(fout,"[TASKS]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,","full_name");
	fprintf(fout,"%s,","task_category");
	fprintf(fout,"%s,","task_priority");
	fprintf(fout,"%s,","difficulty_rating");
	fprintf(fout,"%s,","task_default_target_class");
	fprintf(fout,"%s,","task_default_target_source");
	fprintf(fout,"%s,","task_default_target_type");
	fprintf(fout,"%s,","task_objective_info");
	fprintf(fout,"%s,","minimum_member_count");
	fprintf(fout,"%s,","rules_of_engagement");
	fprintf(fout,"%s,","engage_enemy");
	fprintf(fout,"%s,","escort_required_threshold");
// fprintf(fout,"%s,","waypoint_route_colour");
	fprintf(fout,"%s,","add_start_waypoint");
	fprintf(fout,"%s,","primary_task");
	fprintf(fout,"%s,","solo_task");
	fprintf(fout,"%s,","persistent_task");
	fprintf(fout,"%s,","visible_task");
	fprintf(fout,"%s,","keysite_air_force_capacity");
	fprintf(fout,"%s,","assess_landing");
	fprintf(fout,"%s,","task_route_search");
	fprintf(fout,"%s,","perform_debrief");
	fprintf(fout,"%s,","delay_task_assignment");
	fprintf(fout,"%s,","task_objective_preview");
	fprintf(fout,"%s,","counts_towards_player_log");
	fprintf(fout,"%s,","wait_for_end_task");
	fprintf(fout,"%s,","player_reserve_factor");
	fprintf(fout,"%s,","task_pass_percentage_partial");
	fprintf(fout,"%s,","task_pass_percentage_success");
	fprintf(fout,"%s,","task_completed_score");
	fprintf(fout,"%s,","movement_type");
	fprintf(fout,"%s,","landing_type_fixedwing");
	fprintf(fout,"%s,","landing_type_fixedw_transport");
	fprintf(fout,"%s,","landing_type_helicopter");
	fprintf(fout,"%s,","landing_type_ground");
	fprintf(fout,"%s,","landing_type_people");
	fprintf(fout,"%s,","landing_type_sea");
	fprintf(fout,"%s,","ai_air_attack_strength");
	fprintf(fout,"%s,","ai_ground_attack_strength");
	fprintf(fout,"%s,","ai_movement_speed");
	fprintf(fout,"%s,","ai_movement_stealth");
	fprintf(fout,"%s,","ai_cargo_space");
	fprintf(fout,"%s\n","ai_troop_space");
	}
	for (i = 0; i <   NUM_ENTITY_SUB_TYPE_TASKS; i++)
	{
		fprintf(fout,"%d,",i);
		fprintf(fout,"%s,",task_database[i].full_name);
		fprintf(fout,"%d,",task_database[i].task_category);
		fprintf(fout,"%g,",task_database[i].task_priority);
		fprintf(fout,"%d,",task_database[i].difficulty_rating);
		fprintf(fout,"%d,",task_database[i].task_default_target_class);
		fprintf(fout,"%d,",task_database[i].task_default_target_source);
		fprintf(fout,"%d,",IntToBin(task_database[i].task_default_target_type));
		fprintf(fout,"%d,",task_database[i].task_objective_info);
		fprintf(fout,"%d,",task_database[i].minimum_member_count);
		fprintf(fout,"%d,",task_database[i].rules_of_engagement);
		fprintf(fout,"%d,",task_database[i].engage_enemy);
		fprintf(fout,"%d,",task_database[i].escort_required_threshold);
//    fprintf(fout,"%d,",task_database[i].waypoint_route_colour);
		fprintf(fout,"%d,",task_database[i].add_start_waypoint);
		fprintf(fout,"%d,",task_database[i].primary_task);
		fprintf(fout,"%d,",task_database[i].solo_task);
		fprintf(fout,"%d,",task_database[i].persistent_task);
		fprintf(fout,"%d,",task_database[i].visible_task);
		fprintf(fout,"%d,",task_database[i].keysite_air_force_capacity);
		fprintf(fout,"%d,",task_database[i].assess_landing);
		fprintf(fout,"%d,",task_database[i].task_route_search);
		fprintf(fout,"%d,",task_database[i].perform_debrief);
		fprintf(fout,"%d,",task_database[i].delay_task_assignment);
		fprintf(fout,"%d,",task_database[i].task_objective_preview);
		fprintf(fout,"%d,",task_database[i].counts_towards_player_log);
		fprintf(fout,"%d,",task_database[i].wait_for_end_task);
		fprintf(fout,"%d,",task_database[i].player_reserve_factor);
		fprintf(fout,"%d,",task_database[i].task_pass_percentage_partial);
		fprintf(fout,"%d,",task_database[i].task_pass_percentage_success);
		fprintf(fout,"%d,",task_database[i].task_completed_score);
		fprintf(fout,"%d,",task_database[i].movement_type);
		/*fprintf(fout,"%d,",(task_database[i].landing_types>>0&1==1)?1:0);
		fprintf(fout,"%d,",(task_database[i].landing_types>>1&1==1)?1:0);
		fprintf(fout,"%d,",(task_database[i].landing_types>>2&1==1)?1:0);
		fprintf(fout,"%d,",(task_database[i].landing_types>>3&1==1)?1:0);
		fprintf(fout,"%d,",(task_database[i].landing_types>>4&1==1)?1:0);
		fprintf(fout,"%d,",(task_database[i].landing_types>>5&1==1)?1:0);*/
		fprintf(fout,"%d,",task_database[i].landing_types>>0&1);
		fprintf(fout,"%d,",task_database[i].landing_types>>1&1);
		fprintf(fout,"%d,",task_database[i].landing_types>>2&1);
		fprintf(fout,"%d,",task_database[i].landing_types>>3&1);
		fprintf(fout,"%d,",task_database[i].landing_types>>4&1);
		fprintf(fout,"%d,",task_database[i].landing_types>>5&1);
		fprintf(fout,"%d,",task_database[i].ai_stats.air_attack_strength);
		fprintf(fout,"%d,",task_database[i].ai_stats.ground_attack_strength);
		fprintf(fout,"%d,",task_database[i].ai_stats.movement_speed);
		fprintf(fout,"%d,",task_database[i].ai_stats.movement_stealth);
		fprintf(fout,"%d,",task_database[i].ai_stats.cargo_space);
		fprintf(fout,"%d\n",task_database[i].ai_stats.troop_space);
	}

//aphavoc\source\entity\special\waypoint\wp_dbase.h
	fprintf(fout,"[WAYPOINTS]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,","full_name");
	fprintf(fout,"%s,","verbose_operational_state");
	fprintf(fout,"%s,","mobile_follow_waypoint_offset");
	fprintf(fout,"%s,","waypoint_action_message");
	fprintf(fout,"%s,","waypoint_reached_message");
	fprintf(fout,"%s,","waypoint_reached_return_value");
	fprintf(fout,"%s,","planner_moveable");
	fprintf(fout,"%s,","objective_waypoint");
	fprintf(fout,"%s,","player_skip_waypoint");
	fprintf(fout,"%s,","check_waypoint_action");
	fprintf(fout,"%s,","guide_sub_type");
// fprintf(fout,"%s,","map_icon");
	fprintf(fout,"%s,","fw_minimum_previous_waypoint_distance");//fw = fixed wing
	fprintf(fout,"%s,","fw_action_radius");
	fprintf(fout,"%s,","fw_reached_radius");
	fprintf(fout,"%s,","fw_velocity");
	fprintf(fout,"%s,","fw_criteria_last_to_reach");
	fprintf(fout,"%s,","fw_criteria_transmit_recon");
	fprintf(fout,"%s,","fw_position_type");
	fprintf(fout,"%s,","fw_movement_type");
	fprintf(fout,"%s,","hc_minimum_previous_waypoint_distance");//hc = helicopter
	fprintf(fout,"%s,","hc_action_radius");
	fprintf(fout,"%s,","hc_reached_radius");
	fprintf(fout,"%s,","hc_velocity");
	fprintf(fout,"%s,","hc_criteria_last_to_reach");
	fprintf(fout,"%s,","hc_criteria_transmit_recon");
	fprintf(fout,"%s,","hc_position_type");
	fprintf(fout,"%s,","hc_movement_type");
	fprintf(fout,"%s,","rv_minimum_previous_waypoint_distance");//ground vehicle
	fprintf(fout,"%s,","rv_action_radius");
	fprintf(fout,"%s,","rv_reached_radius");
	fprintf(fout,"%s,","rv_velocity");
	fprintf(fout,"%s,","rv_criteria_last_to_reach");
	fprintf(fout,"%s,","rv_criteria_transmit_recon");
	fprintf(fout,"%s,","rv_position_type");
	fprintf(fout,"%s,","rv_movement_type");
	fprintf(fout,"%s,","sh_minimum_previous_waypoint_distance");//sh=sea vehicle
	fprintf(fout,"%s,","sh_action_radius");
	fprintf(fout,"%s,","sh_reached_radius");
	fprintf(fout,"%s,","sh_velocity");
	fprintf(fout,"%s,","sh_criteria_last_to_reach");
	fprintf(fout,"%s,","sh_criteria_transmit_recon");
	fprintf(fout,"%s,","sh_position_type");
	fprintf(fout,"%s\n","sh_movement_type");
	}
	for (i = 0; i < NUM_ENTITY_SUB_TYPE_WAYPOINTS; i++)
	{
		fprintf(fout,"%d,",i);
		fprintf(fout,"%s,",waypoint_database[i].full_name);
		fprintf(fout,"%d,",waypoint_database[i].verbose_operational_state);
		fprintf(fout,"%d,",waypoint_database[i].mobile_follow_waypoint_offset);
		fprintf(fout,"%d,",waypoint_database[i].waypoint_action_message);
		fprintf(fout,"%d,",waypoint_database[i].waypoint_reached_message);
		fprintf(fout,"%d,",waypoint_database[i].waypoint_reached_return_value);
		fprintf(fout,"%d,",waypoint_database[i].planner_moveable);
		fprintf(fout,"%d,",waypoint_database[i].objective_waypoint);
		fprintf(fout,"%d,",waypoint_database[i].player_skip_waypoint);
		fprintf(fout,"%d,",waypoint_database[i].check_waypoint_action);
		fprintf(fout,"%d,",waypoint_database[i].guide_sub_type);
//    fprintf(fout,"%d,",waypoint_database[i].map_icon);
		fprintf(fout,"%g,",waypoint_database[i].fw_minimum_previous_waypoint_distance);
		fprintf(fout,"%g,",waypoint_database[i].fw_action_radius);
		fprintf(fout,"%g,",waypoint_database[i].fw_reached_radius);
		fprintf(fout,"%g,",waypoint_database[i].fw_velocity);
		fprintf(fout,"%d,",waypoint_database[i].fw_criteria_last_to_reach);
		fprintf(fout,"%d,",waypoint_database[i].fw_criteria_transmit_recon);
		fprintf(fout,"%d,",waypoint_database[i].fw_position_type);
		fprintf(fout,"%d,",waypoint_database[i].fw_movement_type);
		fprintf(fout,"%g,",waypoint_database[i].hc_minimum_previous_waypoint_distance);
		fprintf(fout,"%g,",waypoint_database[i].hc_action_radius);
		fprintf(fout,"%g,",waypoint_database[i].hc_reached_radius);
		fprintf(fout,"%g,",waypoint_database[i].hc_velocity);
		fprintf(fout,"%d,",waypoint_database[i].hc_criteria_last_to_reach);
		fprintf(fout,"%d,",waypoint_database[i].hc_criteria_transmit_recon);
		fprintf(fout,"%d,",waypoint_database[i].hc_position_type);
		fprintf(fout,"%d,",waypoint_database[i].hc_movement_type);
		fprintf(fout,"%g,",waypoint_database[i].rv_minimum_previous_waypoint_distance);
		fprintf(fout,"%g,",waypoint_database[i].rv_action_radius);
		fprintf(fout,"%g,",waypoint_database[i].rv_reached_radius);
		fprintf(fout,"%g,",waypoint_database[i].rv_velocity);
		fprintf(fout,"%d,",waypoint_database[i].rv_criteria_last_to_reach);
		fprintf(fout,"%d,",waypoint_database[i].rv_criteria_transmit_recon);
		fprintf(fout,"%d,",waypoint_database[i].rv_position_type);
		fprintf(fout,"%d,",waypoint_database[i].rv_movement_type);
		fprintf(fout,"%g,",waypoint_database[i].sh_minimum_previous_waypoint_distance);
		fprintf(fout,"%g,",waypoint_database[i].sh_action_radius);
		fprintf(fout,"%g,",waypoint_database[i].sh_reached_radius);
		fprintf(fout,"%g,",waypoint_database[i].sh_velocity);
		fprintf(fout,"%d,",waypoint_database[i].sh_criteria_last_to_reach);
		fprintf(fout,"%d,",waypoint_database[i].sh_criteria_transmit_recon);
		fprintf(fout,"%d,",waypoint_database[i].sh_position_type);
		fprintf(fout,"%d\n",waypoint_database[i].sh_movement_type);
	}

	//GUIDE CRITERIA
	fprintf(fout,"[GUIDE CRITERIA]\n");
	if (WRITE_HEADER) {
	fprintf(fout,"%s,","evade_fire");
	fprintf(fout,"%s,","follow_formation");
	fprintf(fout,"%s,","position_type");
	fprintf(fout,"%s,","terrain_follow_mode");
	fprintf(fout,"%s,","Radius_valid");
	fprintf(fout,"%s,","Radius_value");
	fprintf(fout,"%s,","Heading_valid");
	fprintf(fout,"%s,","Heading_value");
	fprintf(fout,"%s,","Altitude_valid");
	fprintf(fout,"%s,","Altitude_value");
	fprintf(fout,"%s,","Transmit_Data_valid");
	fprintf(fout,"%s,","Transmit_Data_value");
	fprintf(fout,"%s,","Last_To_Reach_valid");
	fprintf(fout,"%s,","Last_To_Reach_value");
	fprintf(fout,"%s,","Weapon_Vector_valid");
	fprintf(fout,"%s\n","Weapon_Vector_value");
	}

	for (i = 0; i < NUM_ENTITY_SUB_TYPE_GUIDES; i++)
	{
		fprintf(fout,"%d",i);
		switch (i) {
		case 0 : fprintf(fout,",%s","Navigation_Direct");            break;
		case 1 : fprintf(fout,",%s","Navigation_Virtual");           break;
		case 2 : fprintf(fout,",%s","Navigation_Routed");            break;
		case 3 : fprintf(fout,",%s","Navigation_Altitude");          break;
		case 4 : fprintf(fout,",%s","Landing_Direct");               break;
		case 5 : fprintf(fout,",%s","Landed");                       break;
		case 6 : fprintf(fout,",%s","Attack_AA_Move_Six");           break;
		case 7 : fprintf(fout,",%s","Attack_AA_Move_Circle");        break;
		case 8 : fprintf(fout,",%s","Attack_AA_Fire_Intercept");     break;
		case 9 : fprintf(fout,",%s","Attack_AG_Approach");           break;
		case 10: fprintf(fout,",%s","Attack_AG_Seek_Cover");         break;
		case 11: fprintf(fout,",%s","Attack_AG_Fly_To_Cover");       break;
		case 12: fprintf(fout,",%s","Attack_AG_Take_Cover");         break;
		case 13: fprintf(fout,",%s","Attack_AG_Climb");              break;
		case 14: fprintf(fout,",%s","Attack_AG_Dive");               break;
		case 15: fprintf(fout,",%s","Attack_AG_Fire");               break;
		case 16: fprintf(fout,",%s","Attack_AG_Fire_Virtual");       break;
		case 17: fprintf(fout,",%s","Attack_AG_Disengage");          break;
		case 18: fprintf(fout,",%s","Attack_AG_Disengage_Virtual");  break;
		case 19: fprintf(fout,",%s","Attack_AG_Egress");             break;
		case 20: fprintf(fout,",%s","Attack_AG_Hasty_Fire");         break;
		case 21: fprintf(fout,",%s","Attack_AG_Hasty_Take_Cover");    break;
		}

		fprintf(fout,",%d",guide_database[i].evade_fire);
		fprintf(fout,",%d",guide_database[i].follow_formation);
		fprintf(fout,",%d",guide_database[i].position_type);
		fprintf(fout,",%d",guide_database[i].terrain_follow_mode);
		fprintf(fout,",%d",guide_database[i].criteria[0].valid);
		fprintf(fout,",%g",guide_database[i].criteria[0].value);
		fprintf(fout,",%d",guide_database[i].criteria[1].valid);
		fprintf(fout,",%g",deg(guide_database[i].criteria[1].value));
		fprintf(fout,",%d",guide_database[i].criteria[2].valid);
		fprintf(fout,",%g",guide_database[i].criteria[2].value);
		fprintf(fout,",%d",guide_database[i].criteria[3].valid);
		fprintf(fout,",%g",guide_database[i].criteria[3].value);
		fprintf(fout,",%d",guide_database[i].criteria[4].valid);
		fprintf(fout,",%g",guide_database[i].criteria[4].value);
		fprintf(fout,",%d",guide_database[i].criteria[5].valid);
		fprintf(fout,",%g",guide_database[i].criteria[5].value);
		fprintf(fout,"\n");
	}

	//AMMO
	fprintf(fout, "[AMMO]\n");
	if (WRITE_HEADER) {
	fprintf(fout, "Aircraft \\ Vehicle,min weapon config,max weapon config,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,");
	fprintf(fout, "weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo,weapon,ammo\n");
	}						
	for (i = 0; i < NUM_ENTITY_SUB_TYPE_AIRCRAFT; i++)
	{
		//for each aircraft i
		int w[48], a[48];
		//w = weapon type number and a = amount
		int l = 0;
		int Found=0;

		for (k = 0; k < 48; k++)
		{
			w[k] = 0; a[k] = 0;
		}

		if (aircraft_database[i].max_weapon_config_type > 0)
		{
			fprintf(fout,"%d",i);
			fprintf(fout,",%s",aircraft_database[i].full_name);
			fprintf(fout,",%d",aircraft_database[i].min_weapon_config_type);
			fprintf(fout,",%d",aircraft_database[i].max_weapon_config_type);
			for (j = aircraft_database[i].min_weapon_config_type;j <= aircraft_database[i].max_weapon_config_type; j++)
			{
				// for each weapon config type of this aircraft i
				for (k = 0; k < NUM_WEAPON_PACKAGES; k++)
				{
					Found = 0;
					// for all packages in the config type j > 0
					if(weapon_config_database[j][k].sub_type > 0)
					{
						int m;
						int wtype = (int)weapon_config_database[j][k].sub_type;
						
						if ((i < 6 || i == 20 || i == 21) &&
							(int)weapon_config_database[j][k].sub_type >= 30 &&
							(int)weapon_config_database[j][k].sub_type < 50)
						{
							int hd = (int)weapon_config_database[j][k].heading_depth;
//ap,hi 0=1 2=3 4=5
//ha,bh 0=1 2=3
//co 0=1 5=8 6=9 7=10
//ho 1=2 3=4
		 
							if (i == 0 || i == 1 || i == 4 || i == 5 || i == 20)
							{
								if (hd == 0) hd = 1;
								if (hd == 2) hd = 3;
								if (hd == 4) hd = 5;
							}
							if (i == 2) 
							{
								if (hd == 0) hd = 1;
								if (hd == 5) hd = 8;
								if (hd == 6) hd = 9;
								if (hd == 10) hd = 7;
							}
							if ( i == 3 || i == 21)
							{
								if (hd == 1) hd = 2;
								if (hd == 3) hd = 4;
							}

							wtype += 100*hd;
							// add pod weapon number
						}
						
						for (m = 0; m < 48; m++)
							if (w[m] == wtype)
								Found = 1;
						// check is it is not found yet and add it
						if (!Found && l < 48)
						{
							w[l] = wtype;//(int)weapon_config_database[j][k].sub_type;
							a[l] = (int)weapon_config_database[j][k].number;
							l++;
						}
					}
				}
			}
			for (k = 0; k < 32; k++)
				if (w[k] > 0)
					fprintf(fout,",%d,%d",w[k],a[k]);
			fprintf(fout,"\n");
		}
	}
	for (i = 0; i < NUM_ENTITY_SUB_TYPE_VEHICLES; i++)
	{
		//for each aircraft i
		int w[32], a[32];
		int l = 0;
		int Found=0;

		for (k = 0; k < 32; k++)
		{
			w[k] = 0; a[k] = 0;
		}

		if (vehicle_database[i].max_weapon_config_type > 0)
		{
			fprintf(fout,"%d",i);
			fprintf(fout,",%s",vehicle_database[i].full_name);
			fprintf(fout,",%d",vehicle_database[i].min_weapon_config_type);
			fprintf(fout,",%d",vehicle_database[i].max_weapon_config_type);
			for (j = vehicle_database[i].min_weapon_config_type;j <= vehicle_database[i].max_weapon_config_type; j++)
			{
				// for each weapon config type of this vehicle i
				for (k = 0; k < NUM_WEAPON_PACKAGES; k++)
				{
					Found = 0;
					// for all packages in the config type j > 0
					if(weapon_config_database[j][k].sub_type > 0)
					{
						int m;
						for (m = 0; m < 32; m++)
							if (w[m] == (int)weapon_config_database[j][k].sub_type)
								Found = 1;
								
						// check is it is not found yet and add it
						if (!Found && l < 32)
						{
							w[l] = (int)weapon_config_database[j][k].sub_type;
							a[l] = (int)weapon_config_database[j][k].number;
							l++;
						}
					}
				}
			}
			for (k = 0; k < 32; k++)
				if (w[k] > 0)
					fprintf(fout,",%d,%d",w[k],a[k]);
			fprintf(fout,"\n");
		}
	}

	//RADAR
	fprintf(fout,"[RADAR]\n");
	if (WRITE_HEADER)
		fprintf(fout,"Aircraft,Radar Range 1,Radar Range 2,Radar Range 3,Radar Range 4,Radar Range 5\n");
	fprintf(fout,"0,Comanche,%.0f,%.0f,%.0f,%.0f,%.0f\n",radar_range_comanche[0],radar_range_comanche[1],radar_range_comanche[2],radar_range_comanche[3],radar_range_comanche[4]);
	fprintf(fout,"1,Apache,%.0f,%.0f,%.0f,%.0f,%.0f\n",radar_range_apache[0],radar_range_apache[1],radar_range_apache[2],radar_range_apache[3],radar_range_apache[4]);
	fprintf(fout,"2,Black Hawk,%.0f,%.0f,%.0f,%.0f,%.0f\n",radar_range_blackhawk[0],radar_range_blackhawk[1],radar_range_blackhawk[2],radar_range_blackhawk[3],radar_range_blackhawk[4]);
	fprintf(fout,"3,Hokum,%.0f,%.0f,%.0f,%.0f,%.0f\n",radar_range_hokum[0],radar_range_hokum[1],radar_range_hokum[2],radar_range_hokum[3],radar_range_hokum[4]);
	fprintf(fout,"4,Havoc,%.0f,%.0f,%.0f,%.0f\n",radar_range_havoc[0],radar_range_havoc[1],radar_range_havoc[2],radar_range_havoc[3]);
	fprintf(fout,"5,Hind,%.0f,%.0f,%.0f,%.0f\n",radar_range_hind[0],radar_range_hind[1],radar_range_hind[2],radar_range_hind[3]);



// complete weapon type config info
	if (INCLUDE_WEAPON_TYPES)
	{

		fprintf(fout, "[WEAPON TYPES CONFIG INFO]\n");

		if (WRITE_HEADER) {
		fprintf(fout,"%s,","weapon config type nr");
		fprintf(fout,"%s,","carrier name");
//       fprintf(fout,"%s,","weapon package nr");

		for ( i = 0; i < 12; i++)
		{
			fprintf(fout,"%s,","weapon name");
			fprintf(fout,"%s,","weapon nr");
		}
/*
		fprintf(fout,"%s,","amount");
		fprintf(fout,"%s,","heading depth");
		fprintf(fout,"%s,","pitch depth");
		fprintf(fout,"%s,","muzzle depth");
		fprintf(fout,"%s,","make weapon system ready");
		fprintf(fout,"%s,","rotate");
		fprintf(fout,"%s,","salvo size");
		fprintf(fout,"%s,","heading rate");
		fprintf(fout,"%s,","min heading limit");
		fprintf(fout,"%s,","max heading limit");
		fprintf(fout,"%s,","pitch rate");
		fprintf(fout,"%s,","min pitch limit");
		fprintf(fout,"%s,","max pitch limit");
		fprintf(fout,"%s,","muzzle rotate rate");
		fprintf(fout,"%s,","rotate inhibit velocity");
		fprintf(fout,"%s,","heading share mask");
		fprintf(fout,"%s,","pitch share mask");
		fprintf(fout,"%s","muzzle flash type");
*/
		fprintf(fout,"\n");
		}
		k = 0;
		for ( i = 0; i < NUM_WEAPON_CONFIG_TYPES; i++)
		{
			//int l = 0;
			//for (j = 0; j < NUM_WEAPON_PACKAGES; j++)
//          if(weapon_config_database[i][j].sub_type > 0) l++;

			if (i < 611)
			{
				fprintf(fout,"%d,%s,",i,aircraft_database[k].full_name);
				fprintf(fout,"%d,%d,",aircraft_database[k].min_weapon_config_type,aircraft_database[k].max_weapon_config_type);
			}
			else
			{
				fprintf(fout,"%d,%s,",i,vehicle_database[k].full_name);
				fprintf(fout,"%d,%d,",vehicle_database[k].min_weapon_config_type,vehicle_database[k].max_weapon_config_type);
			}
			for (j = 0; j < NUM_WEAPON_PACKAGES; j++)
			{

				if(weapon_config_database[i][j].sub_type > 0)
				{

//             if (i < 610)
//             fprintf(fout,"%d,%s,",i*100000+l*100+j,aircraft_database[k].full_name);
//             fprintf(fout,"%d,%d,%s,",i*100000+l*100+j,l*100+j,aircraft_database[k].full_name);
//             fprintf(fout,"%d,%s,",i,aircraft_database[k].full_name);
//             else
//             fprintf(fout,"%d,%s,",i*100000+l*100+j,vehicle_database[k].full_name);
//             fprintf(fout,"%d,%d,%s,",i*100000+l*100+j,l*100+j,vehicle_database[k].full_name);
//             fprintf(fout,"%d,%s,",i,vehicle_database[k].full_name);

					//fprintf(fout,"%s,",weapon_database[weapon_config_database[i][j].sub_type].full_name);
					fprintf(fout,"%d,",weapon_config_database[i][j].sub_type);
					fprintf(fout,"%d,",weapon_config_database[i][j].number);

/*
					fprintf(fout,"%d,",weapon_config_database[i][j].heading_depth);
					fprintf(fout,"%d,",weapon_config_database[i][j].pitch_depth);
					fprintf(fout,"%d,",weapon_config_database[i][j].muzzle_depth);
					fprintf(fout,"%d,",weapon_config_database[i][j].make_weapon_system_ready);
					fprintf(fout,"%d,",weapon_config_database[i][j].rotate);
					fprintf(fout,"%d,",weapon_config_database[i][j].salvo_size);
					fprintf(fout,"%g,",weapon_config_database[i][j].heading_rate);
					fprintf(fout,"%g,",weapon_config_database[i][j].min_heading_limit);
					fprintf(fout,"%g,",weapon_config_database[i][j].max_heading_limit);
					fprintf(fout,"%g,",weapon_config_database[i][j].pitch_rate);
					fprintf(fout,"%g,",weapon_config_database[i][j].min_pitch_limit);
					fprintf(fout,"%g,",weapon_config_database[i][j].max_pitch_limit);
					fprintf(fout,"%g,",weapon_config_database[i][j].muzzle_rotate_rate);
					fprintf(fout,"%g,",weapon_config_database[i][j].rotate_inhibit_velocity);
					fprintf(fout,"%d,",weapon_config_database[i][j].heading_share_mask);
					fprintf(fout,"%d,",weapon_config_database[i][j].pitch_share_mask);
					fprintf(fout,"%d\n",weapon_config_database[i][j].muzzle_flash_type);
*/
				}
			}
			if (i < 611)
			{
				if (i == aircraft_database[k].max_weapon_config_type)
					k++;
				if (i == 610)
				k = 0;
			}
			else
			{
				if (i == vehicle_database[k].max_weapon_config_type)
					k++;
				if (k == 7) k = 8;
				if (k == 18) k = 25;
				if (k == 29) k = 31;
				if (k == 32) k = 33;
				if (k == 35) k = 36;

			}
			fprintf(fout,"0\n");
		}
	}


	fprintf(fout,"[End of GWUT file]\n");

	fclose(fout);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IntValue(p)  atoi(strtok(NULL,","))
#define FloatValue(p)   atof(strtok(NULL,","))
#define TESTDUMP(s) if(testdump){fprintf(fout,"%s\n",buf);fflush(fout);}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
// VJ040229 Function to read the entire GWUT file
// VJ 040321 corrected ammo bugs, include pylon number
void ReadGWutInfo(char *fname)
{
	FILE *f;
	FILE *fout;
	int i, j, k;
	char buf[2048];
	char *p;
	int testdump = 0;

	READ_HEADER = 0;

	if (testdump)
	{
		fout = fopen("dumpgwut.txt","w");
		fprintf(fout,"Dumping file: %s\n",fname);
	}	
/*
//VJ 040322 moved to the function parse_WUT_file
	
	if (!file_exist(fname))
	{
		debug_fatal("WUT filename error",fname);
		return;
	}
*/
	f = fopen(fname, "r");
	if (!f)
	{
		debug_fatal("Error opening GWUT file: [ %s ]",fname);
		return;
	}

	fscanf(f,"%[^\n]\n",buf);	
	// read file header
	TESTDUMP(buf);
			
	if (!strcmp(buf,CURRENT_HEADER) == 0)
	{
		debug_fatal("GWUT file %s has the wrong header, version 1.3 is needed: %s",fname,buf);
		return;
	}

	fscanf(f,"%[^\n]\n",buf);
	 //skip [AIRCRAFT] string
	TESTDUMP(buf);
	 
	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	 //read first values
	TESTDUMP(buf);

	//[AIRCRAFT]
	while (!(strcmp(buf,"[VEHICLES]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name
		aircraft_database[i].force                                         = IntValue(p);
		aircraft_database[i].default_weapon_config_type                    = IntValue(p);
		aircraft_database[i].min_weapon_config_type                        = IntValue(p);
		aircraft_database[i].max_weapon_config_type                        = IntValue(p);
		aircraft_database[i].air_to_air_weapon_config_type                 = IntValue(p);
		aircraft_database[i].air_to_surface_weapon_config_type             = IntValue(p);
		aircraft_database[i].scout_weapon_config_type                      = IntValue(p);
		aircraft_database[i].default_weapon_type                           = IntValue(p);
		aircraft_database[i].target_symbol_type                            = IntValue(p);
		aircraft_database[i].target_priority_type                          = IntValue(p);
		aircraft_database[i].force_info_catagory                           = IntValue(p);
		aircraft_database[i].threat_type                                   = IntValue(p);
		aircraft_database[i].centre_of_gravity_to_ground_distance          = FloatValue(p);
		aircraft_database[i].centre_of_gravity_to_ground_distance_destroyed= FloatValue(p);
		aircraft_database[i].chase_view_min_distance                       = FloatValue(p);
		aircraft_database[i].chase_view_max_distance                       = FloatValue(p);
		aircraft_database[i].chase_view_min_distance_test                  = FloatValue(p);
		aircraft_database[i].chase_view_max_distance_test                  = FloatValue(p);
		aircraft_database[i].cruise_velocity                               = FloatValue(p);
		aircraft_database[i].cruise_altitude                               = FloatValue(p);
		aircraft_database[i].attack_altitude                               = FloatValue(p);
		aircraft_database[i].destroyed_bank_offset                         = rad (FloatValue(p));
		aircraft_database[i].destroyed_pitch_offset                        = rad (FloatValue(p));
		aircraft_database[i].fuselage_angle                                = rad (FloatValue(p));
		aircraft_database[i].liftoff_velocity                              = FloatValue(p);
		aircraft_database[i].main_rotor_shaft_angle                        = rad (FloatValue(p));
		aircraft_database[i].main_rotor_direction                          = FloatValue(p);
		aircraft_database[i].main_rotor_blade_droop_angle                  = rad (FloatValue(p));
		aircraft_database[i].propellor_direction                           = FloatValue(p);
		aircraft_database[i].max_turn_rate                                 = rad (FloatValue(p));
		aircraft_database[i].max_roll                                      = rad (FloatValue(p));
		aircraft_database[i].max_vertical_turn_allowance                   = FloatValue(p);
		aircraft_database[i].avoidance_radius                              = FloatValue(p);
		aircraft_database[i].g_max                                         = FloatValue(p);
		aircraft_database[i].power_output                                  = FloatValue(p);
		aircraft_database[i].tail_rotor_direction                          = FloatValue(p);
		aircraft_database[i].recon_radius                                  = FloatValue(p);
		aircraft_database[i].target_scan_delay                             = FloatValue(p);
		aircraft_database[i].air_scan_range                                = FloatValue(p);
		aircraft_database[i].surface_scan_range                            = FloatValue(p);
		aircraft_database[i].potential_air_to_air_threat                   = FloatValue(p);
		aircraft_database[i].potential_air_to_surface_threat               = FloatValue(p);
		aircraft_database[i].ammo_economy                                  = FloatValue(p);
		aircraft_database[i].fuel_default_weight                           = FloatValue(p);
		aircraft_database[i].fuel_economy                                  = FloatValue(p);
		aircraft_database[i].number_of_main_rotors                         = FloatValue(p);
		aircraft_database[i].main_rotor_radius                             = FloatValue(p);
		aircraft_database[i].initial_damage_level                          = IntValue(p);
		aircraft_database[i].explosive_quality                             = IntValue(p);
		aircraft_database[i].explosive_power                               = IntValue(p);
		aircraft_database[i].offensive_capability                          = IntValue(p);
//VJ 010604 skip player controlable because of FAA setting in eech.ini, k acts as dummy		
		k = IntValue(p);
//		aircraft_database[i].player_controllable                           = IntValue(p);
		aircraft_database[i].points_value                                  = IntValue(p);

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}


	// READ [VEHICLES]

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[WEAPONS]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name

		vehicle_database[i].force                               = IntValue(p);
		vehicle_database[i].default_weapon_config_type          = IntValue(p);
		vehicle_database[i].min_weapon_config_type              = IntValue(p);
		vehicle_database[i].max_weapon_config_type              = IntValue(p);
		vehicle_database[i].default_weapon_type                 = IntValue(p);
		vehicle_database[i].target_type                         = IntValue(p);
		vehicle_database[i].target_symbol_type                  = IntValue(p);
		vehicle_database[i].target_priority_type                = IntValue(p);
		vehicle_database[i].force_info_catagory                 = IntValue(p);
		vehicle_database[i].threat_type                         = IntValue(p);
		vehicle_database[i].carries_smoke_grenades              = IntValue(p);
		vehicle_database[i].chase_view_min_distance             = FloatValue(p);
		vehicle_database[i].chase_view_max_distance             = FloatValue(p);
		vehicle_database[i].chase_view_min_distance_test        = FloatValue(p);
		vehicle_database[i].chase_view_max_distance_test        = FloatValue(p);
		vehicle_database[i].cruise_velocity                     = FloatValue(p);
		vehicle_database[i].axle_length                         = FloatValue(p);
		vehicle_database[i].max_acceleration                    = FloatValue(p);
		vehicle_database[i].max_turn_rate                       = rad (FloatValue(p));
		vehicle_database[i].g_max                               = FloatValue(p);
		vehicle_database[i].power_output                        = FloatValue(p);
		vehicle_database[i].recon_radius                        = FloatValue(p);
		vehicle_database[i].target_scan_delay                   = FloatValue(p);
		vehicle_database[i].air_scan_floor                      = FloatValue(p);
		vehicle_database[i].air_scan_ceiling                    = FloatValue(p);
		vehicle_database[i].air_scan_range                      = FloatValue(p);
		vehicle_database[i].surface_scan_range                  = FloatValue(p);
		vehicle_database[i].potential_surface_to_air_threat     = FloatValue(p);
		vehicle_database[i].potential_surface_to_surface_threat = FloatValue(p);
		vehicle_database[i].ammo_economy                        = FloatValue(p);
		vehicle_database[i].fuel_economy                        = FloatValue(p);
		vehicle_database[i].armour_front                        = FloatValue(p);
		vehicle_database[i].armour_side                         = FloatValue(p);
		vehicle_database[i].armour_rear                         = FloatValue(p);
		vehicle_database[i].initial_damage_level                = IntValue(p);
		j = IntValue(p); k = BinToInt(j);
		if (testdump) fprintf(fout,"%d %d\n",vehicle_database[i].warhead_effective_class, k);
		vehicle_database[i].warhead_effective_class             = k;
		vehicle_database[i].explosive_quality                   = IntValue(p);
		vehicle_database[i].explosive_power                     = IntValue(p);
		vehicle_database[i].offensive_capability                = IntValue(p);
		vehicle_database[i].points_value                        = IntValue(p);

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	
	}

	//read WEAPONS

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[KEYSITES]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name

		weapon_database[i].guidance_type                   = IntValue(p);
		weapon_database[i].aiming_type                     = IntValue(p);
		weapon_database[i].decoy_type                      = IntValue(p);
		weapon_database[i].warhead_type                    = IntValue(p);
		weapon_database[i].threat_type                     = IntValue(p);
		weapon_database[i].report_ammo_low_count           = IntValue(p);
		weapon_database[i].gun_shake                       = IntValue(p);
		weapon_database[i].soft_damage_capability          = IntValue(p);
		weapon_database[i].hard_damage_capability          = IntValue(p);
		weapon_database[i].smoke_trail_type                = IntValue(p);
		weapon_database[i].acquire_parent_forward_velocity = IntValue(p);
		weapon_database[i].ignore_gravity                  = IntValue(p);
		weapon_database[i].survive_ground_impact           = IntValue(p);
		weapon_database[i].in_flight_collision_check       = IntValue(p);
		weapon_database[i].viewable_weapon                 = IntValue(p);
		weapon_database[i].boresight_weapon                = IntValue(p);
		weapon_database[i].hellfire_flight_profile         = IntValue(p);
		k = 0;
		j = IntValue(p); if (j == 1) k = 1;
		j = IntValue(p); if (j == 1) k = k | 2;
		j = IntValue(p); if (j == 1) k = k | 4;
		j = IntValue(p); if (j == 1) k = k | 8;
		j = IntValue(p); if (j == 1) k = k | 16;
		j = IntValue(p); if (j == 1) k = k | 32;
		j = IntValue(p); if (j == 1) k = k | 64;
//    fprintf(fout,"%d %d\n",weapon_database[i].weapon_class, k);
		weapon_database[i].weapon_class = k;
		weapon_database[i].weight                    = FloatValue(p);
		weapon_database[i].min_range                 = FloatValue(p);
		weapon_database[i].max_range                 = FloatValue(p);
		weapon_database[i].effective_range           = FloatValue(p);
		weapon_database[i].min_range_loal            = FloatValue(p);
		weapon_database[i].max_range_loal            = FloatValue(p);
		weapon_database[i].max_range_error_ratio     = FloatValue(p);
		weapon_database[i].muzzle_velocity           = FloatValue(p);
		weapon_database[i].muzzle_velocity_max_error = FloatValue(p);
		weapon_database[i].cruise_velocity           = FloatValue(p);
		weapon_database[i].g_max                     = FloatValue(p);
		weapon_database[i].burn_time                 = FloatValue(p);
		weapon_database[i].cruise_time               = FloatValue(p);
		weapon_database[i].cruise_time_max_error     = FloatValue(p);
		weapon_database[i].inhibit_time              = FloatValue(p);
		weapon_database[i].burst_duration            = FloatValue(p);
		weapon_database[i].rate_of_fire              = FloatValue(p);
		weapon_database[i].reload_time               = FloatValue(p);
		weapon_database[i].max_launch_angle_error    = rad(FloatValue(p));

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}

	//read KEYSITES

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[GROUPS]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name

		keysite_database[i].default_supply_usage.ammo_supply_level= FloatValue(p);
		keysite_database[i].default_supply_usage.fuel_supply_level= FloatValue(p);
		keysite_database[i].importance                            = FloatValue(p);
		keysite_database[i].minimum_efficiency                    = FloatValue(p);
		keysite_database[i].importance_radius                     = FloatValue(p);
		keysite_database[i].air_coverage_radius                   = FloatValue(p);
		keysite_database[i].recon_distance                        = FloatValue(p);
		keysite_database[i].sector_side_max_value                 = FloatValue(p);
		keysite_database[i].align_with_terrain                    = IntValue(p);
		keysite_database[i].hidden_by_fog_of_war                  = IntValue(p);
		keysite_database[i].air_force_capacity                    = IntValue(p);
		keysite_database[i].report_ammo_level                     = IntValue(p);
		keysite_database[i].report_fuel_level                     = IntValue(p);
		keysite_database[i].assign_task_count                     = IntValue(p);
		keysite_database[i].reserve_task_count                    = IntValue(p);
		keysite_database[i].requires_cap                          = IntValue(p);
		keysite_database[i].requires_barcap                       = IntValue(p);
		keysite_database[i].repairable                            = IntValue(p);
		keysite_database[i].oca_target                            = IntValue(p);
		keysite_database[i].recon_target                          = IntValue(p);
		keysite_database[i].ground_strike_target                  = IntValue(p);
		keysite_database[i].ship_strike_target                    = IntValue(p);
		keysite_database[i].troop_insertion_target                = IntValue(p);
		keysite_database[i].campaign_objective                    = IntValue(p);

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}

	//read GROUPS

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[TASKS]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name

		group_database[i].group_category                  = IntValue(p);
		group_database[i].registry_list_type              = IntValue(p);
		group_database[i].group_list_type                 = IntValue(p);
		group_database[i].movement_type                   = IntValue(p);
		group_database[i].default_landing_type            = IntValue(p);
		group_database[i].default_entity_type             = IntValue(p);
		group_database[i].default_blue_force_sub_type     = IntValue(p);
		group_database[i].default_red_force_sub_type      = IntValue(p);
		group_database[i].default_group_formation         = IntValue(p);
		group_database[i].default_group_division          = IntValue(p);
		group_database[i].maximum_groups_per_division     = IntValue(p);
		group_database[i].rearming_time                   = IntValue(p);
		group_database[i].frontline_flag                  = IntValue(p);
		group_database[i].local_only_group                = IntValue(p);
		group_database[i].default_engage_enemy            = IntValue(p);
		group_database[i].amalgamate                      = IntValue(p);
		group_database[i].platoon_id_type                 = IntValue(p);
		group_database[i].maximum_member_count            = IntValue(p);
		group_database[i].minimum_idle_count              = IntValue(p);
		group_database[i].resupply_source                 = IntValue(p);
		group_database[i].ai_stats.air_attack_strength    = IntValue(p);
		group_database[i].ai_stats.ground_attack_strength = IntValue(p);
		group_database[i].ai_stats.movement_speed         = IntValue(p);
		group_database[i].ai_stats.movement_stealth       = IntValue(p);
		group_database[i].ai_stats.cargo_space            = IntValue(p);
		group_database[i].ai_stats.troop_space            = IntValue(p);

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}

	//read TASKS

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[WAYPOINTS]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name

		task_database[i].task_category                   = IntValue(p);
		task_database[i].task_priority                   = IntValue(p);
		task_database[i].difficulty_rating               = IntValue(p);
		task_database[i].task_default_target_class       = IntValue(p);
		task_database[i].task_default_target_source      = IntValue(p);
		j = IntValue(p); k = BinToInt(j);
		task_database[i].task_default_target_type = k;
		task_database[i].task_objective_info             = IntValue(p);
		task_database[i].minimum_member_count            = IntValue(p);
		task_database[i].rules_of_engagement             = IntValue(p);
		task_database[i].engage_enemy                    = IntValue(p);
		task_database[i].escort_required_threshold       = IntValue(p);
		task_database[i].add_start_waypoint              = IntValue(p);
		task_database[i].primary_task                    = IntValue(p);
		task_database[i].solo_task                       = IntValue(p);
		task_database[i].persistent_task                 = IntValue(p);
		task_database[i].visible_task                    = IntValue(p);
		task_database[i].keysite_air_force_capacity      = IntValue(p);
		task_database[i].assess_landing                  = IntValue(p);
		task_database[i].task_route_search               = IntValue(p);
		task_database[i].perform_debrief                 = IntValue(p);
		task_database[i].delay_task_assignment           = IntValue(p);
		task_database[i].task_objective_preview          = IntValue(p);
		task_database[i].counts_towards_player_log       = IntValue(p);
		task_database[i].wait_for_end_task               = IntValue(p);
		task_database[i].player_reserve_factor           = IntValue(p);
		task_database[i].task_pass_percentage_partial    = IntValue(p);
		task_database[i].task_pass_percentage_success    = IntValue(p);
		task_database[i].task_completed_score            = IntValue(p);
		task_database[i].movement_type                   = IntValue(p);
		k = 0;
		j = IntValue(p); if (j == 1) k = 1;
		j = IntValue(p); if (j == 1) k = k | 2;
		j = IntValue(p); if (j == 1) k = k | 4;
		j = IntValue(p); if (j == 1) k = k | 8;
		j = IntValue(p); if (j == 1) k = k | 16;
		j = IntValue(p); if (j == 1) k = k | 32;
//    fprintf(fout,"%d %d\n",task_database[i].landing_types, k);
		task_database[i].landing_types = k;
		task_database[i].ai_stats.air_attack_strength    = IntValue(p);
		task_database[i].ai_stats.ground_attack_strength = IntValue(p);
		task_database[i].ai_stats.movement_speed         = IntValue(p);
		task_database[i].ai_stats.movement_stealth       = IntValue(p);
		task_database[i].ai_stats.cargo_space            = IntValue(p);
		task_database[i].ai_stats.troop_space            = IntValue(p);

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}

	//read WAYPOINTS

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[GUIDE CRITERIA]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name

		waypoint_database[i].verbose_operational_state              = IntValue(p);
		waypoint_database[i].mobile_follow_waypoint_offset          = IntValue(p);
		waypoint_database[i].waypoint_action_message                = IntValue(p);
		waypoint_database[i].waypoint_reached_message               = IntValue(p);
		waypoint_database[i].waypoint_reached_return_value          = IntValue(p);
		waypoint_database[i].planner_moveable                       = IntValue(p);
		waypoint_database[i].objective_waypoint                     = IntValue(p);
		waypoint_database[i].player_skip_waypoint                   = IntValue(p);
		waypoint_database[i].check_waypoint_action                  = IntValue(p);
		waypoint_database[i].guide_sub_type                         = IntValue(p);
		waypoint_database[i].fw_minimum_previous_waypoint_distance  = FloatValue(p);
		waypoint_database[i].fw_action_radius                       = FloatValue(p);
		waypoint_database[i].fw_reached_radius                      = FloatValue(p);
		waypoint_database[i].fw_velocity                            = FloatValue(p);
		waypoint_database[i].fw_criteria_last_to_reach              = IntValue(p);
		waypoint_database[i].fw_criteria_transmit_recon             = IntValue(p);
		waypoint_database[i].fw_position_type                       = IntValue(p);
		waypoint_database[i].fw_movement_type                       = IntValue(p);
		waypoint_database[i].hc_minimum_previous_waypoint_distance  = FloatValue(p);
		waypoint_database[i].hc_action_radius                       = FloatValue(p);
		waypoint_database[i].hc_reached_radius                      = FloatValue(p);
		waypoint_database[i].hc_velocity                            = FloatValue(p);
		waypoint_database[i].hc_criteria_last_to_reach              = IntValue(p);
		waypoint_database[i].hc_criteria_transmit_recon             = IntValue(p);
		waypoint_database[i].hc_position_type                       = IntValue(p);
		waypoint_database[i].hc_movement_type                       = IntValue(p);
		waypoint_database[i].rv_minimum_previous_waypoint_distance  = FloatValue(p);
		waypoint_database[i].rv_action_radius                       = FloatValue(p);
		waypoint_database[i].rv_reached_radius                      = FloatValue(p);
		waypoint_database[i].rv_velocity                            = FloatValue(p);
		waypoint_database[i].rv_criteria_last_to_reach              = IntValue(p);
		waypoint_database[i].rv_criteria_transmit_recon             = IntValue(p);
		waypoint_database[i].rv_position_type                       = IntValue(p);
		waypoint_database[i].rv_movement_type                       = IntValue(p);
		waypoint_database[i].sh_minimum_previous_waypoint_distance  = FloatValue(p);
		waypoint_database[i].sh_action_radius                       = FloatValue(p);
		waypoint_database[i].sh_reached_radius                      = FloatValue(p);
		waypoint_database[i].sh_velocity                            = FloatValue(p);
		waypoint_database[i].sh_criteria_last_to_reach              = IntValue(p);
		waypoint_database[i].sh_criteria_transmit_recon             = IntValue(p);
		waypoint_database[i].sh_position_type                       = IntValue(p);
		waypoint_database[i].sh_movement_type                       = IntValue(p);

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}


	//read GUIDE CRITERIA

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[AMMO]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{		
		p = strtok(buf,",");
		i = atoi(p);
		//get entity number
		p = strtok(NULL,",");
		//skip full name
		
		guide_database[i].evade_fire                 = IntValue(p);
		guide_database[i].follow_formation           = IntValue(p);
		guide_database[i].position_type              = IntValue(p);
		guide_database[i].terrain_follow_mode        = IntValue(p);
		guide_database[i].criteria[0].valid          = IntValue(p);
		guide_database[i].criteria[0].value          = FloatValue(p);
		guide_database[i].criteria[1].valid          = IntValue(p);
		guide_database[i].criteria[1].value          = rad (FloatValue(p));
		guide_database[i].criteria[2].valid          = IntValue(p);
		guide_database[i].criteria[2].value          = FloatValue(p);
		guide_database[i].criteria[3].valid          = IntValue(p);
		guide_database[i].criteria[3].value          = FloatValue(p);
		guide_database[i].criteria[4].valid          = IntValue(p);
		guide_database[i].criteria[4].value          = FloatValue(p);
		guide_database[i].criteria[5].valid          = IntValue(p);
		guide_database[i].criteria[5].value          = FloatValue(p);

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}

	//read AMMO

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!(strcmp(buf,"[RADAR]")==0) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		int minwn, maxwn;
		int w[48], a[48];
		int anr = -1;

		p = strtok(buf,",");
		anr = atoi(p);
		// aircraft/vehicle number
		p = strtok(NULL,",");
		// skip aircraft/vehicle name
		p = strtok(NULL,",");
		minwn = atoi(p);
		//min weapon confg nr
		p = strtok(NULL,",");
		maxwn = atoi(p);
		//max weapon confg nr

		for (k = 0; k < 48; k++)
		{
			w[k] = 0;
			a[k] = 0;
		}

		k = 0;
		while (p && k < 48)
		{
			//read all weapons info
			p = strtok(NULL,",");
			if (p)
				w[k] = atoi(p);
			p = strtok(NULL,",");
			if (p)
				a[k] = atoi(p);
			k++;
		}

	// for (k = 0; k < 32; k++)
	// if (w[k] > 0)
	// fprintf(fout,"%d %d ",w[k],a[k]);
	// fprintf(fout, "\n");

		//get weapon info
		for (i = minwn; i <= maxwn; i++)
		{
			for (j = 0; j < NUM_WEAPON_PACKAGES; j++)
				if(weapon_config_database[i][j].sub_type > 0)
				{
					for (k = 0; k < 48; k++)
					if (w[k] > 0)
					{
						int wtype = w[k];
						int L1=-1, L2=-1;
						if (w[k] > 99)
						{
							L2 = (int)floor(wtype/100);
							if (anr == 0 || anr == 1 || anr == 4 || anr == 5 || anr == 20)
							{
								if (L2 == 1) L1 = 0; 
								if (L2 == 3) L1 = 2; 
								if (L2 == 5) L1 = 4; 
							}
							if (anr == 2) 
							{
								if (L2 == 1) L1 = 0;
								if (L2 == 8) L1 = 5;
								if (L2 == 9) L1 = 6;
								if (L2 == 7) L1 = 10;
							}
							if (anr == 3 || anr == 21)
							{
								if (L2 == 2) L1 = 1;
								if (L2 == 4) L1 = 3;
							}
							wtype = wtype - L2*100;
							if (testdump)
							fprintf(fout,"anr %d pack nr %d L1 %d L2 %d wtype %d w[k]%d \n",anr,i,L1,L2,wtype,w[k]);
						}
						
						if (weapon_config_database[i][j].sub_type == wtype) //w[k])
						{
							if (L1 < 0)
								weapon_config_database[i][j].number = a[k];
							else
							{
							if (weapon_config_database[i][j].heading_depth == L1 || weapon_config_database[i][j].heading_depth == L1)
								weapon_config_database[i][j].number = a[k];	
							}	
							
							if (testdump)
		                fprintf(fout,"%d %d %d %d \n",i,j,weapon_config_database[i][j].sub_type,weapon_config_database[i][j].number);
						}
					}
				}
		}

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}

	//read RADAR

	if (READ_HEADER)
		fscanf(f,"%[^\n]\n",buf);
	TESTDUMP(buf);

	fscanf(f,"%[^\n]\n",buf);
	// read first values
	TESTDUMP(buf);

	while (!feof(f) && !(strcmp(buf,"[End of GWUT file]")==0))
	{
		p = strtok(buf,",");
		i = atoi(p);
//    fprintf(fout,"%d\n",i);
		//get entity number
		p = strtok(NULL,",");
		//skip full name

		if (i == 0) {
				radar_range_apache[0] = FloatValue(p);
				radar_range_apache[1] = FloatValue(p);
				radar_range_apache[2] = FloatValue(p);
				radar_range_apache[3] = FloatValue(p);
				radar_range_apache[4] = FloatValue(p);
		} else
		if (i == 1) {
				radar_range_comanche[0] = FloatValue(p);
				radar_range_comanche[1] = FloatValue(p);
				radar_range_comanche[2] = FloatValue(p);
				radar_range_comanche[3] = FloatValue(p);
				radar_range_comanche[4] = FloatValue(p);
		} else
		if (i == 2) {
				radar_range_blackhawk[0] = FloatValue(p);
				radar_range_blackhawk[1] = FloatValue(p);
				radar_range_blackhawk[2] = FloatValue(p);
				radar_range_blackhawk[3] = FloatValue(p);
				radar_range_blackhawk[4] = FloatValue(p);
		} else
		if (i == 3) {
				radar_range_hokum[0] = FloatValue(p);
				radar_range_hokum[1] = FloatValue(p);
				radar_range_hokum[2] = FloatValue(p);
				radar_range_hokum[3] = FloatValue(p);
				radar_range_hokum[4] = FloatValue(p);
		}  else
		if (i == 4) {
				radar_range_havoc[0] = FloatValue(p);
				radar_range_havoc[1] = FloatValue(p);
				radar_range_havoc[2] = FloatValue(p);
				radar_range_havoc[3] = FloatValue(p);
		}
		if (i == 5) {
				radar_range_hind[0] = FloatValue(p);
				radar_range_hind[1] = FloatValue(p);
				radar_range_hind[2] = FloatValue(p);
				radar_range_hind[3] = FloatValue(p);
			}

		fscanf(f,"%[^\n]\n",buf);
		TESTDUMP(buf);
	}

	fclose(f);
	if (testdump) fclose(fout);

}


