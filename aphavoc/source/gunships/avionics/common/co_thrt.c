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

void activate_common_threat_warning_system (entity *threat)
{
	ASSERT (threat);

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			activate_apache_threat_warning_system (threat);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			activate_havoc_threat_warning_system (threat);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			activate_comanche_threat_warning_system (threat);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			activate_hokum_threat_warning_system (threat);

			break;
		}
		////Moje 030519 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			activate_blackhawk_threat_warning_system (threat);

			break;
		}
		////Moje 030519 End
		////Moje 030612 start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			activate_hind_threat_warning_system (threat);

			break;
		}
		////Moje 030612 end
		////Moje 030816 Start
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			activate_ah64a_threat_warning_system (threat);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			activate_ka50_threat_warning_system (threat);

			break;
		}
		////Moje 030816 end
		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		////////////////////////////////////////
		{
			activate_viper_threat_warning_system (threat);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			activate_kiowa_threat_warning_system (threat);

			break;
		}
		////////////////////////////////////////
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
/*
		default:
		////////////////////////////////////////
		{
			//debug_fatal ("Invalid gunship type = %d", get_global_gunship_type ());
		}
*/

		////////////////////////////////////////
		//  GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			activate_default_threat_warning_system (threat);

			break;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* get_threat_id_number(entity* threat)
{
	// only lists US systems, as russian threat warning displays are unable
	// of distinguishing types	
	char* id = NULL;
	entity_sub_types sub_type = get_local_entity_int_value(threat, INT_TYPE_ENTITY_SUB_TYPE);
	
	if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_VEHICLE))
	{
		switch (sub_type)
		{
		case ENTITY_SUB_TYPE_VEHICLE_SA19_GRISON:
			id = "19";
			break;
		case ENTITY_SUB_TYPE_VEHICLE_SA13_GOPHER:
			id = "13";
			break;
		case ENTITY_SUB_TYPE_VEHICLE_KIEV_CLASS:
			id = "N";
			break;
		case ENTITY_SUB_TYPE_VEHICLE_KRIVAK_II_CLASS:
			id = "N";
			break;
		}
	}
	else if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		switch (sub_type)
		{
		case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
			id = "28";
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
			id = "52";
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_MIG29_FULCRUM:
			id = "29";
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_YAK41_FREESTYLE:
			id = "41";
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_SU33_FLANKER:
			id = "33";
			break;
		}
	}
	
	return id;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
