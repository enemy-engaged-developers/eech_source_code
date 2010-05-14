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

static int
	entity_count,
	entity_peak_count;

static struct
{
	int
		total_created,
		count,
		peak_count;
}
entity_type_stats[NUM_ENTITY_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_system_statistics (void)
{
	entity_count = 0;

	entity_peak_count = 0;

	memset (entity_type_stats, 0, sizeof (entity_type_stats));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_create_entity_statistics (entity_types type)
{
	ASSERT ((type > ENTITY_TYPE_UNKNOWN) && (type < NUM_ENTITY_TYPES));

	//
	// ignore client create on transmit (wait until client create on receive)
	//

	if ((get_comms_model () == COMMS_MODEL_CLIENT) && (get_comms_data_flow () == COMMS_DATA_FLOW_TX))
	{
		return;
	}

	if (++entity_count > entity_peak_count)
	{
		entity_peak_count = entity_count;
	}

	entity_type_stats[type].total_created++;

	if (++entity_type_stats[type].count > entity_type_stats[type].peak_count)
	{
		entity_type_stats[type].peak_count = entity_type_stats[type].count;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_destroy_entity_statistics (entity *en)
{
	ASSERT (en);

	entity_count--;

	entity_type_stats[get_local_entity_type (en)].count--;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if ENTITY_SYSTEM_STATISTICS_ENABLED

void display_entity_system_statistics (void)
{
	entity_types
		type;

	debug_colour_log (DEBUG_COLOUR_AMBER, "=====================================");
	debug_colour_log (DEBUG_COLOUR_AMBER, "ENTITY SYSTEM STATISTICS");
	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");

	debug_colour_log
	(
		DEBUG_COLOUR_RED,
		"%-25.25s: entity peak count = %d (%.2f percent usage)",
		"ENTITY PEAK USAGE",
		entity_peak_count,
		((float) entity_peak_count * 100.0) / (float) number_of_entities
	);

	for (type = (entity_types) 0; type < NUM_ENTITY_TYPES; type = (entity_types) ((int)type + 1))
	{
		debug_colour_log
	  	(
			DEBUG_COLOUR_AMBER,
			"%-25.25s: total created = %5d, count = %5d, peak count = %5d, sizeof = %5d",
			get_entity_type_name (type),
			entity_type_stats[type].total_created,
			entity_type_stats[type].count,
			entity_type_stats[type].peak_count,
			entity_type_database[type].size_of_data
		);
	}

	debug_colour_log (DEBUG_COLOUR_AMBER, "=====================================");
}

#else

void display_entity_system_statistics (void)
{
	debug_colour_log (DEBUG_COLOUR_RED, "WARNING! Entity system statistics are not enabled");
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity_sides get_aircraft_side (entity_sub_types type)
{
	switch (type)
	{
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
		case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
		case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_A10A_THUNDERBOLT:
		case ENTITY_SUB_TYPE_AIRCRAFT_F16_FIGHTING_FALCON:
		case ENTITY_SUB_TYPE_AIRCRAFT_AV8B_HARRIER:
		case ENTITY_SUB_TYPE_AIRCRAFT_FA18_HORNET:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
		case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR:
		case ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION:
		case ENTITY_SUB_TYPE_AIRCRAFT_C17_GLOBEMASTER_III:
		case ENTITY_SUB_TYPE_AIRCRAFT_C130J_HERCULES_II:
		{
			return (ENTITY_SIDE_BLUE_FORCE);

			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_SU25_FROGFOOT:
		case ENTITY_SUB_TYPE_AIRCRAFT_MIG29_FULCRUM:
		case ENTITY_SUB_TYPE_AIRCRAFT_YAK41_FREESTYLE:
		case ENTITY_SUB_TYPE_AIRCRAFT_SU33_FLANKER:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
		case ENTITY_SUB_TYPE_AIRCRAFT_IL76MD_CANDID_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_AN12B_CUB:
		{
			return (ENTITY_SIDE_RED_FORCE);

			break;
		}
	}

	return (ENTITY_SIDE_NEUTRAL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity_sides get_vehicle_side (entity_sub_types type)
{
	switch (type)
	{
		case ENTITY_SUB_TYPE_VEHICLE_M1A2_ABRAMS:
		case ENTITY_SUB_TYPE_VEHICLE_M2A2_BRADLEY:
		case ENTITY_SUB_TYPE_VEHICLE_M113A2:
		case ENTITY_SUB_TYPE_VEHICLE_M1025_HUMVEE:
		case ENTITY_SUB_TYPE_VEHICLE_M109A2:
		case ENTITY_SUB_TYPE_VEHICLE_M270_MLRS:
		case ENTITY_SUB_TYPE_VEHICLE_M163_VULCAN:
		case ENTITY_SUB_TYPE_VEHICLE_M1037_AVENGER:
		case ENTITY_SUB_TYPE_VEHICLE_M48A1_CHAPARRAL:
		case ENTITY_SUB_TYPE_VEHICLE_M998_HUMVEE:
		case ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT:
		case ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT_COVERED:
		case ENTITY_SUB_TYPE_VEHICLE_M978_HEMTT:
		case ENTITY_SUB_TYPE_VEHICLE_TARAWA_CLASS:
		case ENTITY_SUB_TYPE_VEHICLE_OLIVER_HAZARD_PERRY_CLASS:
		case ENTITY_SUB_TYPE_VEHICLE_LCU:
		case ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY:
		case ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_STANDING:
		case ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_KNEELING:
		{
			return (ENTITY_SIDE_BLUE_FORCE);

			break;
		}
		case ENTITY_SUB_TYPE_VEHICLE_T80U:
		case ENTITY_SUB_TYPE_VEHICLE_BMP2:
		case ENTITY_SUB_TYPE_VEHICLE_BMP3:
		case ENTITY_SUB_TYPE_VEHICLE_BTR80:
		case ENTITY_SUB_TYPE_VEHICLE_BRDM2:
		case ENTITY_SUB_TYPE_VEHICLE_2S19:
		case ENTITY_SUB_TYPE_VEHICLE_BM21_GRAD:
		case ENTITY_SUB_TYPE_VEHICLE_SA19_GRISON:
		case ENTITY_SUB_TYPE_VEHICLE_SA13_GOPHER:
		case ENTITY_SUB_TYPE_VEHICLE_UAZ469B:
		case ENTITY_SUB_TYPE_VEHICLE_URAL_4320:
		case ENTITY_SUB_TYPE_VEHICLE_URAL_FUEL_TANKER:
		case ENTITY_SUB_TYPE_VEHICLE_KIEV_CLASS:
		case ENTITY_SUB_TYPE_VEHICLE_KRIVAK_II_CLASS:
		case ENTITY_SUB_TYPE_VEHICLE_LCAC:
		case ENTITY_SUB_TYPE_VEHICLE_AIST_CLASS:
		case ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY:
		case ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_STANDING:
		case ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_KNEELING:
		{
			return (ENTITY_SIDE_RED_FORCE);

			break;
		}
	}

	return (ENTITY_SIDE_NEUTRAL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dump_aircraft_and_vehicle_count (void)
{
	entity
		*en;

	entity_sub_types
		sub_type;

	int
		total_count,
		total_blue_aircraft_count,
		total_blue_vehicle_count,
		total_red_aircraft_count,
		total_red_vehicle_count,
		blue_aircraft_count[NUM_ENTITY_SUB_TYPE_AIRCRAFT],
		blue_vehicle_count[NUM_ENTITY_SUB_TYPE_VEHICLES],
		red_aircraft_count[NUM_ENTITY_SUB_TYPE_AIRCRAFT],
		red_vehicle_count[NUM_ENTITY_SUB_TYPE_VEHICLES];

	total_count = 0;

	total_blue_aircraft_count = 0;
	total_blue_vehicle_count = 0;

	total_red_aircraft_count = 0;
	total_red_vehicle_count = 0;

	memset (blue_aircraft_count, 0, sizeof (blue_aircraft_count));
	memset (blue_vehicle_count, 0, sizeof (blue_vehicle_count));

	memset (red_aircraft_count, 0, sizeof (red_aircraft_count));
	memset (red_vehicle_count, 0, sizeof (red_vehicle_count));

	en = first_used_entity;

	while (en)
	{
		sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
		{
			ASSERT (entity_sub_type_aircraft_valid (sub_type));

			if (get_local_entity_int_value (en, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
			{
				total_count++;

				blue_aircraft_count[sub_type]++;

				total_blue_aircraft_count++;
			}
			else if (get_local_entity_int_value (en, INT_TYPE_SIDE) == ENTITY_SIDE_RED_FORCE)
			{
				total_count++;

				red_aircraft_count[sub_type]++;

				total_red_aircraft_count++;
			}
		}
		else if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_VEHICLE))
		{
			ASSERT (entity_sub_type_vehicle_valid (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)));

			if (get_local_entity_int_value (en, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
			{
				total_count++;

				blue_vehicle_count[sub_type]++;

				total_blue_vehicle_count++;
			}
			else if (get_local_entity_int_value (en, INT_TYPE_SIDE) == ENTITY_SIDE_RED_FORCE)
			{
				total_count++;

				red_vehicle_count[sub_type]++;

				total_red_vehicle_count++;
			}
		}

		en = get_local_entity_succ (en);
	}

	debug_colour_log (DEBUG_COLOUR_AMBER, "=====================================");
	debug_colour_log (DEBUG_COLOUR_AMBER, "START FORCE COUNT (total = %d)", total_count);
	debug_colour_log (DEBUG_COLOUR_AMBER, "=====================================");

	////////////////////////////////////////

	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");
	debug_colour_log (DEBUG_COLOUR_AMBER, "BLUE AIRCRAFT (total = %d)", total_blue_aircraft_count);
	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");

	for (sub_type = 0; sub_type < NUM_ENTITY_SUB_TYPE_AIRCRAFT; sub_type++)
	{
		if (get_aircraft_side (sub_type) == ENTITY_SIDE_BLUE_FORCE)
		{
			debug_colour_log (DEBUG_COLOUR_AMBER, "%4dx %s", blue_aircraft_count[sub_type], entity_sub_type_aircraft_names[sub_type]);
		}
	}

	////////////////////////////////////////

	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");
	debug_colour_log (DEBUG_COLOUR_AMBER, "BLUE VEHICLES (total = %d)", total_blue_vehicle_count);
	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");

	for (sub_type = 0; sub_type < NUM_ENTITY_SUB_TYPE_VEHICLES; sub_type++)
	{
		if (get_vehicle_side (sub_type) == ENTITY_SIDE_BLUE_FORCE)
		{
			debug_colour_log (DEBUG_COLOUR_AMBER, "%4dx %s", blue_vehicle_count[sub_type], entity_sub_type_vehicle_names[sub_type]);
		}
	}

	////////////////////////////////////////

	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");
	debug_colour_log (DEBUG_COLOUR_AMBER, "RED AIRCRAFT (total = %d)", total_red_aircraft_count);
	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");

	for (sub_type = 0; sub_type < NUM_ENTITY_SUB_TYPE_AIRCRAFT; sub_type++)
	{
		if (get_aircraft_side (sub_type) == ENTITY_SIDE_RED_FORCE)
		{
			debug_colour_log (DEBUG_COLOUR_AMBER, "%4dx %s", red_aircraft_count[sub_type], entity_sub_type_aircraft_names[sub_type]);
		}
	}

	////////////////////////////////////////

	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");
	debug_colour_log (DEBUG_COLOUR_AMBER, "RED VEHICLES (total = %d)", total_red_vehicle_count);
	debug_colour_log (DEBUG_COLOUR_AMBER, "-------------------------------------");

	for (sub_type = 0; sub_type < NUM_ENTITY_SUB_TYPE_VEHICLES; sub_type++)
	{
		if (get_vehicle_side (sub_type) == ENTITY_SIDE_RED_FORCE)
		{
			debug_colour_log (DEBUG_COLOUR_AMBER, "%4dx %s", red_vehicle_count[sub_type], entity_sub_type_vehicle_names[sub_type]);
		}
	}

	////////////////////////////////////////

	debug_colour_log (DEBUG_COLOUR_AMBER, "=====================================");
	debug_colour_log (DEBUG_COLOUR_AMBER, "END FORCE COUNT");
	debug_colour_log (DEBUG_COLOUR_AMBER, "=====================================");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
