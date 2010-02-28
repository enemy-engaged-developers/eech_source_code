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

const effect_data
   effect_database[NUM_ENTITY_SUB_TYPE_EFFECTS] =
   {
      // ENTITY_SUB_TYPE_EFFECT_PARTICLE
      {
         FALSE,															// constructed locally
      },
	  // Xhit: added for downwash effect (030328)
	  // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_DOWNWASH
      {
         TRUE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_PARTICLE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_TRAIL
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_VEHICLE_WAKE
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_RAIN
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_WIND
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_RAIN
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_WIND
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_JUNGLE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_SEA
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN_LOOPING
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_GATLING_GUN
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_GUN_PODS
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_CO_PILOT_MESSAGE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2
      {
         TRUE,																// constructed locally
      },
		//	ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING,
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_MCA
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_MISC
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_MISC_SPEECH
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED,
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_TRACKED,
      {
         TRUE,																// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_APU_TURBINE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE1
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN1
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN2
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP1
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP2
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_WARNING_MESSAGE
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SPRITE
      {
         FALSE,															// constructed locally
      },

      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMB1
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMB2
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMB3
      {
         FALSE,															// constructed locally
      },
      // ENTITY_SUB_TYPE_EFFECT_SOUND_AMB4
      {
         FALSE,															// constructed locally
      },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
