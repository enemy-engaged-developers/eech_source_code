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

typedef enum SOUND_LOCALITY_TYPES
{
	SOUND_LOCALITY_ALL,
	SOUND_LOCALITY_INTERIOR,
	SOUND_LOCALITY_EXTERIOR,

	NUM_SOUND_LOCALITY_TYPES

} sound_locality_types;

#define SOUND_LOCALITY_RADIO SOUND_LOCALITY_ALL

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum SOUND_CHANNEL_TYPES
{
	SOUND_CHANNEL_SOUND_EFFECT,
	SOUND_CHANNEL_SYSTEM,
	SOUND_CHANNEL_CO_PILOT,
	SOUND_CHANNEL_WINGMAN,
	SOUND_CHANNEL_AIR_TRAFFIC_CONTROLLER,
	SOUND_CHANNEL_FORWARD_AIR_CONTROLLER,
	SOUND_CHANNEL_GROUND_CONTROLLER,

	NUM_SOUND_CHANNEL_TYPES

} sound_channel_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SOUND_EFFECT
{
	effect
		eff;

	sound_sample_indices
		*effect_index;

	float
		amplification,
		effect_lifetime,
		valid_effect_lifetime;

	struct SYSTEM_SOUND_EFFECT
		*sound_effect_data;

	unsigned int
		side 									: NUM_SIDE_BITS,
		sound_channel						: NUM_SOUND_CHANNEL_BITS,
		sound_locality						: NUM_SOUND_LOCALITY_BITS,
		valid_sound_effect				: NUM_VALID_SOUND_EFFECT_BITS,
		looping								: NUM_SOUND_EFFECT_LOOPING_BITS,
		panning								: NUM_SOUND_EFFECT_PANNING_BITS,
		sound_effect_sequence_count	: 4;
};

typedef struct SOUND_EFFECT sound_effect;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"se_creat.h"

#include	"se_dstry.h"

#include	"se_float.h"

#include	"se_funcs.h"

#include	"se_int.h"

#include	"se_list.h"

#include	"se_msgs.h"

#include	"se_pack.h"

#include	"se_ptr.h"

#include	"se_snd.h"

#include	"se_updt.h"

#include	"se_vec3d.h"

#include	"speech.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int pause_local_entity_sound_type (entity *en, entity_sub_types type, float delay);

extern int resume_local_entity_sound_type (entity *en, entity_sub_types type);

extern int pause_client_server_entity_sound_type (entity *en, entity_sub_types type, float delay);

extern int resume_client_server_entity_sound_type (entity *en, entity_sub_types type);

extern void kill_local_entity_sound_type (entity *en, entity_sub_types type);

extern void kill_client_server_entity_sound_type (entity *en, entity_sub_types type);

extern void destroy_local_sound_effects (entity *en);

extern void destroy_client_server_sound_effects (entity *en);

extern void pause_local_continuous_weapon_sound_effect (entity *en, entity_sub_types weapon_sub_type);

extern void pause_client_server_continuous_weapon_sound_effect (entity *en, entity_sub_types weapon_sub_type);

extern int resume_client_server_continuous_weapon_sound_effect (entity *en, entity_sub_types weapon_sub_type);

extern int get_local_entity_sound_type_valid (entity *en, entity_sub_types type);

extern entity *create_local_sound_effect_entity
			(
				int index,
				entity *parent,
				entity_sides side,
				entity_sub_types sub_type,
				sound_channel_types channel,
				sound_locality_types locality,
				vec3d *position,
				float amp,
				int valid,
				int looping,
				int sample_count,
				sound_sample_indices *sample_indices
			);

extern entity *create_client_server_sound_effect_entity
			(
				entity *parent,
				entity_sides side,
				entity_sub_types sub_type,
				sound_channel_types channel,
				sound_locality_types locality,
				vec3d *position,
				float amp,
				int valid,
				int looping,
				int sample_count,
				sound_sample_indices *sample_indices
			);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

