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

#define INCOMING_MISSILE_SOUND_PERIOD	(1.5)

#define RADAR_LOCKED_SOUND_PERIOD		(1.5)

static float
	incoming_missile_sound_timer,
	radar_locked_sound_timer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_havoc_threat_warning_system (void)
{
	incoming_missile_sound_timer = 0.0;

	radar_locked_sound_timer = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_havoc_threat_warning_system (void)
{
	if (get_gunship_entity ())
	{
		pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING, 0.5);

		pause_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED, 0.5);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void reset_time_accel (void)
{
	if (get_time_acceleration () != TIME_ACCELERATION_PAUSE)
	{
		set_min_time_acceleration (NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_havoc_threat_warning_system (entity *threat)
{
	ASSERT (threat);

	if (havoc_damage.threat_warning_display)
	{
		return;
	}

	switch (get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE))
	{
		////////////////////////////////////////
		case THREAT_TYPE_INVALID:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_RF_MISSILE:
		////////////////////////////////////////
		{
			if (!havoc_damage.radar_warning_system)
			{
				reset_time_accel ();

				incoming_missile_sound_timer = INCOMING_MISSILE_SOUND_PERIOD;

				resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING);

				play_client_server_cpg_contact_message
				(
					get_gunship_entity (),
					SPEECH_CPG_INCOMING_MISSILE,
					get_speech_heading_type (get_gunship_entity (), threat),
					get_speech_distance_type (get_gunship_entity (), threat)
				);
			}

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_IR_MISSILE:
		////////////////////////////////////////
		{
			reset_time_accel ();

			incoming_missile_sound_timer = INCOMING_MISSILE_SOUND_PERIOD;

			resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING);

			play_client_server_cpg_contact_message
			(
				get_gunship_entity (),
				SPEECH_CPG_INCOMING_MISSILE,
				get_speech_heading_type (get_gunship_entity (), threat),
				get_speech_distance_type (get_gunship_entity (), threat)
			);

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_LASER_MISSILE:
		////////////////////////////////////////
		{
			reset_time_accel ();

			incoming_missile_sound_timer = INCOMING_MISSILE_SOUND_PERIOD;

			resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING);

			play_client_server_cpg_contact_message
			(
				get_gunship_entity (),
				SPEECH_CPG_INCOMING_MISSILE,
				get_speech_heading_type (get_gunship_entity (), threat),
				get_speech_distance_type (get_gunship_entity (), threat)
			);

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_AIRBORNE_RADAR:
		////////////////////////////////////////
		{
			if (!havoc_damage.radar_warning_system)
			{
				reset_time_accel ();

				radar_locked_sound_timer = RADAR_LOCKED_SOUND_PERIOD;

				resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED);

				if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_HELICOPTER))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_CHOPPERS,
						get_speech_heading_type (get_gunship_entity (), threat),
						get_speech_distance_type (get_gunship_entity (), threat)
					);
				}
				else if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_FIXED_WING))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_FAST_MOVERS,
						get_speech_heading_type (get_gunship_entity (), threat),
						get_speech_distance_type (get_gunship_entity (), threat)
					);
				}
			}

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_SAM:
		////////////////////////////////////////
		{
			if (!havoc_damage.radar_warning_system)
			{
				reset_time_accel ();

				radar_locked_sound_timer = RADAR_LOCKED_SOUND_PERIOD;

				resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED);

				if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_SHIP_VEHICLE))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_WARSHIPS,
						get_speech_heading_type (get_gunship_entity (), threat),
						get_speech_distance_type (get_gunship_entity (), threat)
					);
				}
				else
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_SAM,
						get_speech_heading_type (get_gunship_entity (), threat),
						get_speech_distance_type (get_gunship_entity (), threat)
					);
				}
			}

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_AAA:
		////////////////////////////////////////
		{
			if (!havoc_damage.radar_warning_system)
			{
				reset_time_accel ();

				radar_locked_sound_timer = RADAR_LOCKED_SOUND_PERIOD;

				resume_local_entity_sound_type (get_gunship_entity (), ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED);

				if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_SHIP_VEHICLE))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_WARSHIPS,
						get_speech_heading_type (get_gunship_entity (), threat),
						get_speech_distance_type (get_gunship_entity (), threat)
					);
				}
				else
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_TRIPLE_A,
						get_speech_heading_type (get_gunship_entity (), threat),
						get_speech_distance_type (get_gunship_entity (), threat)
					);
				}
			}

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_EARLY_WARNING_RADAR:
		////////////////////////////////////////
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_havoc_threat_warning_system (void)
{
	int
		radar_jammer_on,
		infra_red_jammer_on;

	entity
		*source,
		*threat;

	source = get_gunship_entity ();

	radar_jammer_on = FALSE;

	infra_red_jammer_on = FALSE;

	threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

	while (threat)
	{
		switch (get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE))
		{
			////////////////////////////////////////
			case THREAT_TYPE_INVALID:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case THREAT_TYPE_RF_MISSILE:
			////////////////////////////////////////
			{
				radar_jammer_on = TRUE;

				break;
			}
			////////////////////////////////////////
			case THREAT_TYPE_IR_MISSILE:
			////////////////////////////////////////
			{
				infra_red_jammer_on = TRUE;

				break;
			}
			////////////////////////////////////////
			case THREAT_TYPE_LASER_MISSILE:
			////////////////////////////////////////
			{
				break;
			}
			////////////////////////////////////////
			case THREAT_TYPE_AIRBORNE_RADAR:
			case THREAT_TYPE_SAM:
			case THREAT_TYPE_AAA:
			case THREAT_TYPE_EARLY_WARNING_RADAR:
			////////////////////////////////////////
			{
				radar_jammer_on = TRUE;

				break;
			}
		}

		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
	}

	//
	// jammers
	//

	if (havoc_damage.radar_warning_system)
	{
		radar_jammer_on = FALSE;
	}

	set_havoc_radar_jammer_auto (radar_jammer_on);

	set_havoc_infra_red_jammer_auto (infra_red_jammer_on);

	//
	// warning sounds
	//

	if (incoming_missile_sound_timer > 0.0)
	{
		incoming_missile_sound_timer -= get_delta_time ();

		if (incoming_missile_sound_timer <= 0.0)
		{
			pause_local_entity_sound_type (source, ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING, 0.5);
		}
	}

	if (radar_locked_sound_timer > 0.0)
	{
		radar_locked_sound_timer -= get_delta_time ();

		if (radar_locked_sound_timer <= 0.0)
		{
			pause_local_entity_sound_type (source, ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED, 0.5);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
