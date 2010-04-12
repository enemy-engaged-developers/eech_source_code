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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SOUND_CHANNEL_INFO_TYPE
{
	int
		mute,
		volume;

	const char
		*text;
};

typedef struct SOUND_CHANNEL_INFO_TYPE sound_channel_info_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static sound_channel_info_type
	sound_channel_info [NUM_SOUND_CHANNEL_TYPES] =
	{
		{FALSE,		10,			"Sound Effects"},
		{FALSE,		10,			"Warning System"},
		{FALSE,		10,			"Co-Pilot Speech"},
		{FALSE,		10,			"Wingmen Speech"},
		{FALSE,		10,			"Air Traffic Control"},
		{FALSE,		10,			"Forward Air Control"},
		{FALSE,		10,			"Ground Control"},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ataribaby 29/12/2008 for muted UI sounds
int ui_sounds_muted = FALSE;

static void play_local_sound (entity *en, viewpoint *vp, float range)
{
	entity
		*parent;

	sound_effect
		*raw;

	int
		volume,
		maximum_volume;

	float
		v,
		channel_volume,
		minimum_sound_range,
		reference_sound_range,
		maximum_sound_range;

	raw = (sound_effect *) get_local_entity_data (en);

	ASSERT (raw->effect_index);

	//
	// check sound effect / speech options
	//

	switch (raw->eff.sub_type)
	{
		case ENTITY_SUB_TYPE_EFFECT_SOUND_CPG_MESSAGE:
		{
			if (!get_global_copilot_speech_effects_enabled ())
			{
				return;
			}

			// deliberate fall-through ...
		}
		case ENTITY_SUB_TYPE_EFFECT_SOUND_MISC_SPEECH:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_WARNING_MESSAGE:
		{
			//
			// SPEECH
			//

			if (!get_global_speech_effects_enabled())
			{
				return;
			}

			break;
		}
		default:
		{
			//
			// SOUND EFFECTS
			//

			if (!get_global_sound_effects_enabled())
			{
				return;
			}

			break;
		}
	}

	//
	// turn on/off the interior/exterior sounds
	//

	parent = get_local_entity_parent (en, LIST_TYPE_SPECIAL_EFFECT);

	if (
			(!parent) ||
			((raw->sound_locality == SOUND_LOCALITY_EXTERIOR) && (in_cockpit) && (parent == get_gunship_entity ())) ||
			((raw->sound_locality == SOUND_LOCALITY_INTERIOR) && ((!in_cockpit) || ((parent != get_gunship_entity ()) && (parent != get_session_entity ()))))
//			((raw->sound_locality == SOUND_LOCALITY_EXTERIOR) && (in_cockpit) && canopy_door_state == CANOPY_DOOR_STATE_CLOSED && (parent == get_gunship_entity ())) ||
//			((raw->sound_locality == SOUND_LOCALITY_INTERIOR) && ((!in_cockpit) || canopy_door_state != CANOPY_DOOR_STATE_CLOSED || ((parent != get_gunship_entity ()) && (parent != get_session_entity ()))))
			)
	{
		//
		// added the !parent clause. Should really ASSERT on !parent, but there is the case of client lag meaning
		// the S.E. was unlinked but has not been destroyed yet.
		//
		
		if (raw->sound_effect_data)
		{
			destroy_system_sound_effect (raw->sound_effect_data);

			set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
		}

		return;
	}

	//
	// don't play radio messages if radio broken
	//

	if (raw->eff.sub_type == ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE) 
	{
		if (get_gunship_entity ())
		{
			if (!get_gunship_comms_equipment_ok ())
			{
				if (raw->sound_effect_data)
				{
					destroy_system_sound_effect (raw->sound_effect_data);

					set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
				}

				return;
			}
		}
	}

	if ((!raw->valid_sound_effect) && (raw->valid_effect_lifetime <= 0.0))
	{
		//
		// destroy sound if it is playing
		//

		if (raw->sound_effect_data)
		{
			destroy_system_sound_effect (raw->sound_effect_data);

			set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
		}

		return;
	}

	//
	// check if sound is within range
	//

	minimum_sound_range = get_local_entity_float_value (en, FLOAT_TYPE_MINIMUM_SOUND_RANGE);
	reference_sound_range = get_local_entity_float_value (en, FLOAT_TYPE_REFERENCE_SOUND_RANGE);
	maximum_sound_range = get_local_entity_float_value (en, FLOAT_TYPE_MAXIMUM_SOUND_RANGE);

	maximum_volume = get_local_entity_int_value (en, INT_TYPE_MAXIMUM_VOLUME);

	if ((maximum_sound_range == 0.0) || (range == 0.0))
	{
		v = maximum_volume;
	}
	else
	{
		if (range >= maximum_sound_range)
		{
			#if DEBUG_MODULE
		
			debug_log ("SE_SND : Don't play sound ( range = %.2f, zr = %.2f, index = %s )", range, zero_volume_range, application_sound_effects [raw->effect_index [0]].name);
		
			#endif
		
			if (raw->sound_effect_data)
			{
				destroy_system_sound_effect (raw->sound_effect_data);

				set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
			}

			return;
		}

		//
		// adjust volume with range
		//
		{
//			float temp;
//			temp = zero_volume_range - range;
//			v = maximum_volume * ((temp * temp) / (zero_volume_range * zero_volume_range));
			if ((minimum_sound_range == 0.0) && (reference_sound_range == 0.0))
			{
				float temp;
				temp = maximum_sound_range - range;
				v = ((temp * temp) / (maximum_sound_range * maximum_sound_range));
			}
			else if (minimum_sound_range == 0.0)
			{
				v = range >= maximum_sound_range ? 0.0 : range > reference_sound_range ? reference_sound_range / range : 1.0;
			}
			else
			{
				v = 0.0;
				if((range >= maximum_sound_range) || (range <= minimum_sound_range))
					v = 0.0;
				else if (range < reference_sound_range)
					v = (range-minimum_sound_range) / (reference_sound_range-minimum_sound_range);
				else
					v = 1- ((range-reference_sound_range) / (maximum_sound_range-reference_sound_range));
				//Normalize
				v = bound(v, 0.0, 1.0);
			}
			v = v * maximum_volume;
		}
	}

	//
	// adjust volume with entity amplification level
	//
	
	v *= raw->amplification;

	//
	// arneh - adjust volume with canopy close/open
	//

	if (in_cockpit)
	{
		// Casm 03MAR10 Canopy sound amplification control
		csa_codes
			csa_code;

		// Casm 07DEC09
		switch (raw->eff.sub_type)
		{
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP:
			//ataribaby 28/12/2008 if in player heli then do it as internal otherwise as external sound from other helis 
			if (parent == get_gunship_entity ())
			{
				csa_code = CSA_CODES_ROTOR_PLAYER;
			}
			else
			{
				csa_code = CSA_CODES_ROTOR_EXTERNAL;
			}
			break;
		//ataribaby 28/12/2008 lets guns rocks
		case ENTITY_SUB_TYPE_EFFECT_SOUND_GATLING_GUN: 
		case ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_GUN_PODS:
			csa_code = CSA_CODES_GUNS;
			break;
		//ataribaby 28/12/2008 all external sound sources gets influenced by external_sounds_volume setting			
		case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_RAIN:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_WIND:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_RAIN:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_WIND:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_JUNGLE:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_SEA:
			csa_code = CSA_CODES_ENV;
			break;
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE1:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN1:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN2:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP1:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP2:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE2:
			//ataribaby 28/12/2008 if in player heli then do it as internal otherwise as external sound from other helis 
			if (parent == get_gunship_entity ())
			{
				csa_code = CSA_CODES_ENGINE_PLAYER;
			}
			else
			{
				csa_code = CSA_CODES_ENGINE_EXTERNAL;
			}
			break;
		case ENTITY_SUB_TYPE_EFFECT_SOUND_MISC:
			if (parent == get_gunship_entity ())
			{
				csa_code = CSA_CODES_MISC_PLAYER;
			}
			else
			{
				csa_code = CSA_CODES_MISC_EXTERNAL;
			}
			break;
		case ENTITY_SUB_TYPE_EFFECT_SOUND_CPG_MESSAGE:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_MCA:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_MISC_SPEECH:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_TRACKED:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_APU_TURBINE:
		case ENTITY_SUB_TYPE_EFFECT_SOUND_WARNING_MESSAGE:
		default:
			csa_code = CSA_CODES_LAST;
			break;
		}

		if (csa_code != CSA_CODES_LAST)
		{
			int
				*values;

			values = canopy_sound_amp[csa_code];
			v *= values[CSA_VALUES_MIN] * 0.01 + bound((int)(canopy_door_state * 100), 0, values[CSA_VALUES_TOP]) * values[CSA_VALUES_MUL] * 0.0001;
		}
	}

	if (ui_sounds_muted == 1)
		v = 0.0; //ataribaby 29/12/2008 for muted UI sounds

	//
	// adjust volume with channel sound settings
	//

	ASSERT (raw->sound_channel < NUM_SOUND_CHANNEL_TYPES);

	if (sound_channel_info [raw->sound_channel].mute)
	{
		v = SOUND_MINIMUM_VOLUME;
	}
	else
	{
		channel_volume = (float)(sound_channel_info [raw->sound_channel].volume);

		v *= (channel_volume * 0.1f);
	}

	//
	// adjust volume for "dying" sound effects (currently only applies to chaingun etc.) 
	//
	
	if ((!raw->valid_sound_effect) && (raw->valid_effect_lifetime < 0.25))
	{
		v *= (raw->valid_effect_lifetime * 4.0);
	}

	v = bound (v, SOUND_MINIMUM_VOLUME, SOUND_MAXIMUM_VOLUME);

	convert_float_to_int (v, &volume);

	#if DEBUG_MODULE
	
	debug_log ("SE_SND : Play sound ( range = %.2f, volume = %d, index = %s )", range, volume, application_sound_effects [raw->effect_index [0]].name);
	
	#endif
	
	if (volume > SOUND_MINIMUM_VOLUME)
	{
		if (!raw->sound_effect_data)
		{
			#if DEBUG_MODULE
	
			debug_log ("SE_SND: creating sound effect");
	
			#endif
	
			if (raw->sound_effect_sequence_count > 1)
			{
				//
				// play sequence of sounds
				//

				unsigned int
					sample_loop;

				sound_sequence_information
					*samples;

				ASSERT (!raw->looping);

				samples = (sound_sequence_information *) malloc_fast_mem (sizeof (sound_sequence_information) * raw->sound_effect_sequence_count);

				for (sample_loop = 0; sample_loop < raw->sound_effect_sequence_count; sample_loop ++)
				{
					samples [sample_loop].sound_sample_index = raw->effect_index [sample_loop];

					samples [sample_loop].rate = application_sound_effects [raw->effect_index [sample_loop]].rate;
				}

				raw->sound_effect_data = create_sequenced_system_sound_effect (raw->sound_effect_sequence_count, samples, volume, (void *) en);

				free_mem (samples);
			}
			else
			{
				//
				// play single sound
				//

				raw->sound_effect_data = create_single_system_sound_effect (raw->effect_index [0], volume, raw->looping, (void *) en);
			}

			if (!raw->sound_effect_data)
			{
				#if DEBUG_MODULE
	
				debug_log ("SE_SND: UNABLE TO CREATE SOUND EFFECT");
	
				#endif
	
				return;
			}
		}
	
		if (raw->sound_effect_data)
		{
			//
			// set volume
			//

			set_system_sound_effect_volume (raw->sound_effect_data, volume);

			//
			// set panning
			//

			if ((raw->panning) && (raw->sound_locality != SOUND_LOCALITY_INTERIOR))
			{
				vec3d
					sound_vector;

				sound_vector.x = raw->eff.position.x - vp->x;
				sound_vector.y = raw->eff.position.y - vp->y;
				sound_vector.z = raw->eff.position.z - vp->z;

				// Casm 07DEC09 OpenAL support
				set_system_sound_effect_position (raw->sound_effect_data, sound_vector);
			}

			//Werewolf pitch 4 Feb 2006
			if (raw->pitch)
			{
				float pitch = raw->pitch;
//				debug_log ( "sound entity pitch change, pitch=%.2f ", pitch);

				set_system_sound_effect_pitch (raw->sound_effect_data, pitch);
			}
			//End Werewolf pitch 4 Feb 2006
				
			if (!get_system_sound_effect_playing (raw->sound_effect_data))
			{
				if (!raw->looping)
				{
					if (raw->effect_lifetime > 0.0)
					{
						float
							sample_time,
							d,
							rate,
							size;
	
						//
						// play sound part way through
						//
	
						if (raw->sound_effect_sequence_count > 1)
						{
							//
							// sequenced sound
							//

							int
								current_index;

							float
								lifetime;

							lifetime = raw->effect_lifetime;

							for (current_index = raw->sound_effect_sequence_count - 1; current_index >= 0; current_index --)
							{
								rate = (float)(application_sound_effects [raw->effect_index [current_index]].rate);
								size = (float)(application_sound_effects [raw->effect_index [current_index]].size);

								sample_time = size / rate; // It's not correct because of pitch

								if (lifetime <= sample_time)
								{
									d = sample_time - lifetime;

									d = bound (d, 0.0, sample_time);

									play_sequenced_system_sound_effect (raw->sound_effect_data, current_index, d);

									break;
								}

								lifetime -= sample_time;
							}
						}
						else
						{
							//
							// single sound
							//

							rate = (float)(application_sound_effects [raw->effect_index [0]].rate);
							size = (float)(application_sound_effects [raw->effect_index [0]].size);
	
							sample_time = size / rate; // It's not correct because of pitch

							d = sample_time - raw->effect_lifetime;
	
							d = bound (d, 0.0, sample_time);

							#if DEBUG_MODULE
		
							debug_log ("SE_SND: playing sound from byte %d / %.0f", buffer_position, size);
			
							#endif

							play_system_sound_effect (raw->sound_effect_data, d);
						}
					}
				}
				else
				{
					//
					// play sound from start
					//
	
					#if DEBUG_MODULE
	
					debug_log ("SE_SND: playing sound from start");
		
					#endif

					play_system_sound_effect (raw->sound_effect_data, 0.0);
				}
			}
		}
	}
	else
	{
		//
		// destroy sound if it is playing
		//

		if (raw->sound_effect_data)
		{
			#if DEBUG_MODULE
	
			debug_log ("SE_SND: destroying sound (volume too low)");
		
			#endif

			destroy_system_sound_effect (raw->sound_effect_data);

			set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_sound_effect_sound_functions (void)
{
	fn_play_local_entity_sound[ENTITY_TYPE_SOUND_EFFECT]	= play_local_sound;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_sound_channel_name (int channel)
{
	return sound_channel_info [channel].text;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_sound_channel_volume (int channel)
{
	return sound_channel_info [channel].volume;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_sound_channel_volume (int channel, int volume)
{
	volume = bound (volume, 1, 10);
	
	sound_channel_info [channel].volume = volume;

	set_global_sound_channel_volume (channel, volume);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_sound_channel_muted (int channel)
{
	return sound_channel_info [channel].mute;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_sound_channel_muted (int channel, int mute)
{
	sound_channel_info [channel].mute = mute;

	set_global_sound_channel_muted (channel, mute);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_sound_channels (void)
{
	int
		loop;

	for (loop = 0; loop < NUM_SOUND_CHANNEL_TYPES; loop ++)
	{
		sound_channel_info [loop].mute = get_global_sound_channel_muted (loop);

		sound_channel_info [loop].volume = get_global_sound_channel_volume (loop);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
