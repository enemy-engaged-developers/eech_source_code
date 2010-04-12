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

#include "cmndline.h"

#include "sound_internal.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAXIMUM_CURRENT_SYSTEM_SOUND_EFFECTS 256
static int
	maximum_current_system_sound_effects;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct SOUND_SAMPLE
{
	LPDIRECTSOUNDBUFFER
		sound_buffer;

	int
		size,
		default_rate;
};

typedef struct SOUND_SAMPLE sound_sample;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sound_sample
	*source_sound_samples = NULL;

int
	number_of_source_sound_samples = 0;

system_sound_effect
	current_system_sound_effects[MAXIMUM_CURRENT_SYSTEM_SOUND_EFFECTS];

int
	sound_system_initialised,
	sound_system_paused;

int
	sound_volume_lookup_table[SOUND_MAXIMUM_VOLUME+1];

static vec3d
	listener_right;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_free_sound_slot ( int *value );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int initialise_sound_system ( void )
{

	int
		count;

	if ( command_line_sound_hdwrbuf > 0 && command_line_sound_hdwrbuf <= MAXIMUM_CURRENT_SYSTEM_SOUND_EFFECTS )
		maximum_current_system_sound_effects = command_line_sound_hdwrbuf;
	else
		maximum_current_system_sound_effects = MAXIMUM_CURRENT_SYSTEM_SOUND_EFFECTS;

	if ( initialise_direct_sound () )
	{

		sound_system_initialised = TRUE;

		sound_system_paused = FALSE;
	
		//
		// Initialise the sound effects
		//
	
		for ( count = 0; count < maximum_current_system_sound_effects; count++ )
		{
	
			current_system_sound_effects[count].used = FALSE;
	
			current_system_sound_effects[count].sound_buffer = NULL;
	
			current_system_sound_effects[count].paused = FALSE;
		
			current_system_sound_effects[count].looping = FALSE;
		}
	
		//
		// Initialise the volume lookup table
		//
	
		for ( count = 0; count <= SOUND_MAXIMUM_VOLUME; count++ )
		{
	
			if ( count == 0 )
			{
	
				sound_volume_lookup_table[count] = -10000;
			}
			else
			{
	
				double
					numerator,
					denominator,
					bels;
	
				//
				// To convert from a linear range of 0... max to -10000 to 0 in decibels/100
				//
	
				numerator = log ( ( ( double ) SOUND_MAXIMUM_VOLUME ) / ( ( double ) count ) );
				denominator = log ( 2.0 );
	
				bels = numerator / denominator;
	
				bels *= -1000.0;
	
				bels = bound ( bels, -10000.0, 0 );
	
				sound_volume_lookup_table[count] = bels;
			}
		}

		return ( TRUE );
	}
	else
	{

		sound_system_initialised = FALSE;

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_sound_system ( void )
{
}

int get_sound_system_devices ( const char **devices, const char **default_device )
{
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void allocate_source_sound_samples ( int number )
{

	int
		count;

	ASSERT ( number );

	if ( source_sound_samples )
	{

		deallocate_source_sound_samples ();
	}

	//
	// Allocate an array of pointers
	//

	source_sound_samples = ( sound_sample * ) safe_malloc ( number * sizeof ( sound_sample ) );

	if ( !source_sound_samples )
	{

		debug_fatal ( "Unable to allocate enough memory for sound samples" );
	}


	for ( count = 0; count < number; count++ )
	{

		source_sound_samples[count].sound_buffer = NULL;
	}

	number_of_source_sound_samples = number;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deallocate_source_sound_samples ( void )
{

	int
		count;

	for ( count = 0; count < number_of_source_sound_samples; count++ )
	{

		if ( source_sound_samples[count].sound_buffer )
		{

			if ( source_sound_samples[count].sound_buffer )
			{

				dsound_destroy_sound_buffer ( source_sound_samples[count].sound_buffer );
	
				source_sound_samples[count].sound_buffer = NULL;
			}
		}
	}

	safe_free ( source_sound_samples );

	source_sound_samples = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

system_sound_effect * get_first_system_sound_effect ( void )
{

	int
		count;

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{

		if ( current_system_sound_effects[count].used )
		{

			return ( &current_system_sound_effects[count] );
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

system_sound_effect * get_next_system_sound_effect ( system_sound_effect *effect )
{

	int
		count;

	count = ( effect - current_system_sound_effects );

	count++;

	for ( ; count < maximum_current_system_sound_effects; count++ )
	{

		if ( current_system_sound_effects[count].used )
		{

			return ( &current_system_sound_effects[count] );
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

system_sound_effect * get_next_free_system_system_sound_effect ( void )
{

	int
		count;

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{

		if ( !current_system_sound_effects[count].used )
		{

			current_system_sound_effects[count].used = TRUE;

			return ( &current_system_sound_effects[count] );
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_all_system_sound_effects ( void )
{

	int
		count;

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{

		if ( current_system_sound_effects[count].used )
		{


			destroy_system_sound_effect ( &current_system_sound_effects[count] );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_system_sound_effect_playing ( system_sound_effect *effect )
{

	ASSERT ( effect );

	effect->playing = FALSE;

	if ( effect->sound_buffer )
	{

		DWORD
			status;

		if ( IDirectSoundBuffer_GetStatus ( (LPDIRECTSOUNDBUFFER) effect->sound_buffer, &status ) == DS_OK )
		{

			if ( ( status && DSBSTATUS_LOOPING ) || ( status && DSBSTATUS_PLAYING ) )
			{

				effect->playing = TRUE;
			}
		}
	}

	return ( effect->playing );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_source_sound_sample_valid ( int sample_index )
{

	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_source_sound_samples );

	if ( ( source_sound_samples[sample_index].sound_buffer ) && ( source_sound_samples[sample_index].size ) )
	{

		return ( TRUE );
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_source_sound_sample ( int sample_index, sample_types type, int default_rate, int size )
{

	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_source_sound_samples );

	if ( source_sound_samples[sample_index].sound_buffer )
	{

		debug_log ( "Leaking a DirectSoundBuffer, Sample index: %d", sample_index );
	}

	//
	// Create the sound buffer
	//

	source_sound_samples[sample_index].sound_buffer = dsound_create_sound_buffer ( type, default_rate, size );

	source_sound_samples[sample_index].size = size;

	source_sound_samples[sample_index].default_rate = default_rate;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_source_sound_sample ( int sample_index )
{

	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_source_sound_samples );
	ASSERT ( source_sound_samples[sample_index].sound_buffer );

	//
	// Destroy the sound buffer
	//

	dsound_destroy_sound_buffer ( source_sound_samples[sample_index].sound_buffer );

	source_sound_samples[sample_index].sound_buffer = NULL;
	source_sound_samples[sample_index].size = 0;
	source_sound_samples[sample_index].default_rate = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_source_sound_sample ( int sample_index, void *data )
{
	unsigned char
		*ptr;

	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_source_sound_samples );
	ASSERT ( source_sound_samples[sample_index].sound_buffer );

	ptr = dsound_lock_sound_buffer ( source_sound_samples[sample_index].sound_buffer, 0, source_sound_samples[sample_index].size );

	if ( ptr )
	{
		memcpy ( ptr, data, source_sound_samples[sample_index].size );

		dsound_unlock_sound_buffer ( source_sound_samples[sample_index].sound_buffer, ptr, source_sound_samples[sample_index].size );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

system_sound_effect * create_single_system_sound_effect ( int sound_sample_index, int volume, int looping, void *user_data )
{
	system_sound_effect
		*effect;

	if ( !sound_system_initialised )
	{
		return ( NULL );
	}

	ASSERT ( sound_sample_index >= 0 );
	ASSERT ( sound_sample_index < number_of_source_sound_samples );
	ASSERT ( volume >= 0 );
	ASSERT ( volume <= SOUND_MAXIMUM_VOLUME );

	//
	// Grab the next free sound effect structure.
	//

	effect = get_next_free_system_system_sound_effect ();

	if ( effect )
	{
		float
			rate;

		rate = source_sound_samples[sound_sample_index].default_rate;

		//
		// Fill in the details about this sound effect
		//

		effect->number_of_sequenced_samples = 1;

		effect->sound_sample_sequence[0].sound_sample_index = sound_sample_index;
		effect->sound_sample_sequence[0].rate = rate;

		effect->rate = rate;
		effect->playing = FALSE;
		effect->paused = FALSE;
		effect->looping = looping;
		effect->volume = volume;
		effect->pitch = 1.0;
		effect->panning = 0;
		effect->user_data = user_data;

		//
		// Duplicate the sound buffer concerned
		//

		effect->sound_buffer = dsound_duplicate_sound_buffer ( source_sound_samples[sound_sample_index].sound_buffer, source_sound_samples[sound_sample_index].size );

		if ( !effect->sound_buffer )
		{

			//
			// Free up the sound effect structure, and return NULL
			//

			effect->used = FALSE;

			effect = NULL;
		}
	}

	return ( effect );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

system_sound_effect * create_sequenced_system_sound_effect ( int number_of_samples, sound_sequence_information *samples, int volume, void *user_data )
{

	system_sound_effect
		*effect;

	if ( !sound_system_initialised )
	{

		return ( NULL );
	}

	ASSERT ( number_of_samples >= 2 );
	ASSERT ( number_of_samples < MAX_SEQUENCED_SAMPLES );

	//
	// Grab the next free sound effect structure.
	//

	effect = get_next_free_system_system_sound_effect ();

	if ( effect )
	{

		int
			count;

		//
		// Fill in the details about this sound effect
		//

		effect->number_of_sequenced_samples = number_of_samples;

		effect->current_sequenced_sample_offset = 0;

		for ( count = 0; count < number_of_samples; count++ )
		{

			ASSERT ( samples[count].sound_sample_index >= 0 );
			ASSERT ( samples[count].sound_sample_index < number_of_source_sound_samples );

			effect->sound_sample_sequence[count] = samples[count];

			//
			// Validate the rate
			//

			if ( samples[count].rate == 0 )
			{

				samples[count].rate = source_sound_samples[ samples[count].sound_sample_index ].default_rate;
			}
		}

		effect->looping = FALSE;
		effect->panning = 0;
		effect->volume = volume;
		effect->pitch = 1.0;
		effect->rate = samples[0].rate;
		effect->user_data = user_data;

		//
		// Duplicate the sound buffer concerned
		//

		effect->sound_buffer = dsound_duplicate_sound_buffer ( source_sound_samples[ samples[0].sound_sample_index ].sound_buffer, source_sound_samples[ samples[0].sound_sample_index ].size );

		if ( !effect->sound_buffer )
		{

			//
			// Free up the sound effect structure, and return NULL
			//

			effect->used = FALSE;

			effect = NULL;
		}
	}

	return ( effect );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_system_sound_effect ( system_sound_effect *effect )
{

	ASSERT ( effect );
	ASSERT ( effect->used );

	if ( effect->sound_buffer )
	{

		//
		// Release the duplicated sound buffer
		//

		dsound_destroy_sound_buffer ( effect->sound_buffer );

		effect->sound_buffer = NULL;
	}

	effect->used = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_system_sound_effect_user_data ( system_sound_effect *effect, void *user_data )
{

	ASSERT ( effect );

	effect->user_data = user_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void * get_system_sound_effect_user_data ( system_sound_effect *effect )
{

	ASSERT ( effect );

	return ( effect->user_data );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_system_sound_effect_system ( void )
{

	int
		count;

	system_sound_effect
		*effect;

	if ( sound_system_initialised )
	{
	
		//
		// Go through all the sound effects, updating their properties.
		//
	
		for ( count = 0; count < maximum_current_system_sound_effects; count++ )
		{
	
			effect = &current_system_sound_effects[count];
	
			if ( ( effect->used ) && ( effect->playing ) )
			{
	
				if ( effect->number_of_sequenced_samples == 1 )
				{
	
					//
					// Check the sound buffer really is still playing
					//
	
					if ( dsound_get_sound_buffer_status ( effect->sound_buffer ) == SAMPLE_STATE_FINISHED )
					{
	
						effect->playing = FALSE;
					}
				}
				else
				{
	
					//
					// Check the current sound buffer is still playing
					//
	
					if ( dsound_get_sound_buffer_status ( effect->sound_buffer ) == SAMPLE_STATE_FINISHED )
					{
	
						if ( effect->current_sequenced_sample_offset == ( effect->number_of_sequenced_samples - 1 ) )
						{
	
							//
							// The sound effect has now finished the sequence
							//
	
							effect->playing = FALSE;
						}
						else
						{
	
							int
								sound_sample_index;
							int intrate; //Werewolf pitch - I hate typecasts
							float floatrate = effect->rate*effect->pitch; //Werewolf
	
							//
							// Move the samples along one in the sequence
							//
	
							effect->current_sequenced_sample_offset++;
	
							//
							// Destroy the current duplicated sound buffer
							//
	
							dsound_destroy_sound_buffer ( effect->sound_buffer );
	
							//
							// Duplicate the next sound buffer in the sequence
							//
	
							effect->rate = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].rate;
	
							sound_sample_index = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].sound_sample_index;
	
							effect->sound_buffer = dsound_duplicate_sound_buffer ( source_sound_samples[sound_sample_index].sound_buffer, source_sound_samples[sound_sample_index].size );
	
							//
							// Start the buffer playing
							//

							convert_float_to_int (floatrate, &intrate);
							dsound_set_sound_buffer_rate ( effect->sound_buffer, intrate); //Werewolf
	
							dsound_set_sound_buffer_volume ( effect->sound_buffer, sound_volume_lookup_table[effect->volume] );
	
							dsound_set_sound_buffer_pan ( effect->sound_buffer, effect->panning );
	
							dsound_set_sound_buffer_position ( effect->sound_buffer, 0 );
	
							dsound_play_sound_buffer ( effect->sound_buffer, FALSE );
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_sequenced_system_sound_effect ( system_sound_effect *effect, int sequence_index, float time_position )
{
	int
		sound_sample_index;

	ASSERT ( effect );

	ASSERT ( sequence_index >= 0 );
	ASSERT ( sequence_index < effect->number_of_sequenced_samples );

	if ( !effect->playing )
	{

		if ( sequence_index == 0 )
		{
			play_system_sound_effect ( effect, time_position );
		}
		else
		{			

			effect->current_sequenced_sample_offset = sequence_index;

			//
			// Destroy the current duplicated sound buffer
			//

			if ( effect->sound_buffer )
			{

				dsound_destroy_sound_buffer ( effect->sound_buffer );
			}

			//
			// Duplicate the next sound buffer in the sequence
			//

			effect->rate = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].rate;

			sound_sample_index = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].sound_sample_index;

			effect->sound_buffer = dsound_duplicate_sound_buffer ( source_sound_samples[sound_sample_index].sound_buffer, source_sound_samples[sound_sample_index].size );

			//
			// Start the buffer playing
			//

			if ( effect->sound_buffer )
			{
				float
					rate = effect->rate * effect->pitch,
					position = time_position / rate;
				int
					int_rate,
					buffer_position;

				convert_float_to_int (rate, &int_rate);
				convert_float_to_int (position, &buffer_position);
	
				dsound_set_sound_buffer_rate ( effect->sound_buffer, int_rate );
				
				dsound_set_sound_buffer_volume ( effect->sound_buffer, sound_volume_lookup_table[effect->volume] );
	
				dsound_set_sound_buffer_pan ( effect->sound_buffer, effect->panning );
	
				dsound_set_sound_buffer_position ( effect->sound_buffer, buffer_position );
	
				dsound_play_sound_buffer ( effect->sound_buffer, FALSE );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_system_sound_effect ( system_sound_effect *effect, float time_position )
{
	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	if ( !effect->playing )
	{
		float
			rate = effect->rate * effect->pitch,
			position = time_position / rate;
		int
			int_rate,
			buffer_position;

		convert_float_to_int (rate, &int_rate);
		convert_float_to_int (position, &buffer_position);
	
		effect->playing = TRUE;
	
		effect->paused = FALSE;
	
		dsound_set_sound_buffer_rate ( effect->sound_buffer, int_rate);
	
		dsound_set_sound_buffer_volume ( effect->sound_buffer, sound_volume_lookup_table[effect->volume] );
	
		dsound_set_sound_buffer_pan ( effect->sound_buffer, effect->panning );
	
		dsound_set_sound_buffer_position ( effect->sound_buffer, buffer_position );
	
		dsound_play_sound_buffer ( effect->sound_buffer, effect->looping );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pause_system_sound_effect ( system_sound_effect *effect )
{

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	if ( !effect->paused )
	{

		effect->paused = TRUE;
	
		if ( !sound_system_paused )
		{
	
			dsound_stop_sound_buffer ( effect->sound_buffer );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_system_sound_effect ( system_sound_effect *effect )
{

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	if ( effect->number_of_sequenced_samples > 1 )
	{

		//
		// Reset the sequence here.
		//
	}
	else
	{

		//
		// Set the position of the sound buffer now
		//

		dsound_set_sound_buffer_position ( effect->sound_buffer, 0 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void continue_system_sound_effect ( system_sound_effect *effect )
{

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	if ( effect->paused )
	{
	
		effect->paused = FALSE;
	
		if ( !sound_system_paused )
		{
	
			dsound_play_sound_buffer ( effect->sound_buffer, effect->looping );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_system_sound_listener_orientation ( vec3d forward, vec3d up, vec3d right )
{
	listener_right = right;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void set_system_sound_effect_position ( system_sound_effect *effect, vec3d position )
{
	float
		length,
		ang,
		temp;

	int
		panning;

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	length = normalise_any_3d_vector ( &position );

	if ( length == 0.0 )
	{
		return;
	}

	ang = fabs ( acos ( get_3d_unit_vector_dot_product ( &position, &listener_right) ) );

	temp = 10000 + ( ( -10000 - 10000 ) * ( ang / PI ) );

	convert_float_to_int ( temp, &panning );

	effect->panning = panning;

	dsound_set_sound_buffer_pan ( effect->sound_buffer, effect->panning );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_system_sound_effect_panning ( system_sound_effect *effect )
{

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	return ( effect->panning );
}

//--Werewolf 4 Feb 2006 Sound pitch support
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_system_sound_effect_pitch ( system_sound_effect *effect, float pitch )
{
	int intrate; //Werewolf pitch - I hate typecasts
	float floatrate;

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	if (pitch < 0.1f)
		pitch = 0.1f;
	else if (pitch > 4.0)
		pitch = 4.0f;

	effect->pitch = pitch;

	floatrate = effect->rate*effect->pitch;
	convert_float_to_int (floatrate, &intrate);
//	debug_log ( "sound effect pitch change, pitch=%.2f  effect->pitch=%.2f  intrate=%d", pitch, effect->pitch, intrate);

	dsound_set_sound_buffer_rate ( effect->sound_buffer, intrate);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_system_sound_effect_pitch ( system_sound_effect *effect )
{

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	return ( effect->pitch );
}
//--END Werewolf 4 Feb 2006 Sound pitch support

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_system_sound_effect_volume ( system_sound_effect *effect, int volume )
{

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	ASSERT ( volume <= SOUND_MAXIMUM_VOLUME );
	ASSERT ( volume >= SOUND_MINIMUM_VOLUME );

	effect->volume = volume;

	dsound_set_sound_buffer_volume ( effect->sound_buffer, sound_volume_lookup_table[effect->volume] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_system_sound_effect_volume ( system_sound_effect *effect )
{

	ASSERT ( effect );
	ASSERT ( effect->sound_buffer );

	return ( effect->volume );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pause_sound_system ( void )
{

	if ( ( sound_system_initialised ) && ( !sound_system_paused ) )
	{
	
		int
			count;
	
		for ( count = 0; count < maximum_current_system_sound_effects; count++ )
		{
	
			if ( ( current_system_sound_effects[count].used ) && ( !current_system_sound_effects[count].paused ) )
			{
	
				dsound_stop_sound_buffer ( current_system_sound_effects[count].sound_buffer );
			}
		}
	
		sound_system_paused = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void continue_sound_system ( void )
{

	if ( ( sound_system_initialised ) && ( sound_system_paused ) )
	{
	
		int
			count;
	
		for ( count = 0; count < maximum_current_system_sound_effects; count++ )
		{
	
			if ( ( current_system_sound_effects[count].used ) && ( !current_system_sound_effects[count].paused ) )
			{
				dsound_play_sound_buffer ( current_system_sound_effects[count].sound_buffer, current_system_sound_effects[count].looping );
			}
		}
	
		sound_system_paused = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_sound_system_paused (void)
{
	return sound_system_paused;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

