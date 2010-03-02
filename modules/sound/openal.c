#include "sound.h"

#include "cmndline.h"

#include <al.h>
#include <alc.h>

static DWORD
	context_thread_id;

#ifdef DEBUG
#define AL_CHECK(x) \
	do \
	{ \
		int al_error; \
		DWORD thread_id = GetCurrentThreadId(); \
		if ( thread_id != context_thread_id ) \
		{ \
			debug_fatal ( "%s:%u Invalid thread %u for operation %s (%u)", __FILE__, __LINE__, thread_id, #x, context_thread_id ); \
		} \
		x; \
		al_error = alGetError(); \
		if ( al_error != AL_NO_ERROR ) \
		{ \
			debug_fatal ( "%s:%u Failed to make OpenAL call '%s': %s", __FILE__, __LINE__, #x, alGetString ( al_error ) ); \
		} \
	} \
	while (0)
#else
#define AL_CHECK(x) x
#endif

enum DEVICES_EXT_PRESENT
{
	DEP_UNKNOWN,
	DEP_YES,
	DEP_NO
};

static enum DEVICES_EXT_PRESENT
	devices_ext_present = DEP_UNKNOWN;

static const ALCchar
	*reported_devices,
	*reported_default_device;

#define MAXIMUM_CURRENT_SYSTEM_SOUND_EFFECTS 256
#define DEFAULT_CURRENT_SYSTEM_SOUND_EFFECTS 50
static int
	maximum_current_system_sound_effects;

static system_sound_effect
	current_system_sound_effects[MAXIMUM_CURRENT_SYSTEM_SOUND_EFFECTS];

struct SOUND_BUFFER
{
	ALuint
		buffer;

	ALenum
		type;

	int
		default_rate,
		size;
};
typedef struct SOUND_BUFFER sound_buffer;

static int
	number_of_buffers;

static sound_buffer
	*buffers;

static int
	sound_system_initialised,
	sound_system_paused;

static ALCdevice
	*device;
static ALCcontext
	*context;

int initialise_sound_system ( void )
{
	int
		count;

	sound_system_initialised = FALSE;
	sound_system_paused = FALSE;

	if ( command_line_sound_hdwrbuf <= 0 || command_line_sound_hdwrbuf > MAXIMUM_CURRENT_SYSTEM_SOUND_EFFECTS )
	{
		command_line_sound_hdwrbuf = DEFAULT_CURRENT_SYSTEM_SOUND_EFFECTS;
	}
	maximum_current_system_sound_effects = command_line_sound_hdwrbuf;

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{
		current_system_sound_effects[count].used = FALSE;
		current_system_sound_effects[count].sound_buffer = NULL;
		current_system_sound_effects[count].paused = FALSE;
		current_system_sound_effects[count].looping = FALSE;
	}

	device = alcOpenDevice ( *command_line_sound_device ? command_line_sound_device : NULL );
	if ( !device )
	{
		return FALSE;
	}

	context = alcCreateContext ( device, NULL );
	alcMakeContextCurrent ( context );

	context_thread_id = GetCurrentThreadId();

	AL_CHECK ( alGetError () );

	AL_CHECK ( alDistanceModel ( AL_NONE ) );

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{
		current_system_sound_effects[count].used = FALSE;

		AL_CHECK ( alGenSources ( 1, ( ALuint * ) &current_system_sound_effects[count].panning ) );
		AL_CHECK ( alSourcei ( current_system_sound_effects[count].panning, AL_BUFFER, 0 ) );
		ASSERT ( alIsSource ( current_system_sound_effects[count].panning ) );
		AL_CHECK ( alSourcei ( current_system_sound_effects[count].panning, AL_SOURCE_RELATIVE, TRUE ) );
		AL_CHECK ( alSource3f ( current_system_sound_effects[count].panning, AL_VELOCITY, 0.0f, 0.0f, 0.0f ) );
	}

	sound_system_initialised = TRUE;

	return TRUE;
}

void deinitialise_sound_system ( void )
{
	// FIXME
}

int get_sound_system_devices ( const char **devices, const char **default_device )
{
	if ( devices_ext_present == DEP_UNKNOWN )
	{
		devices_ext_present = DEP_NO;
		if ( alcIsExtensionPresent ( NULL, "ALC_ENUMERATION_EXT" ) == AL_TRUE )
		{
			reported_devices = alcGetString ( NULL, ALC_ALL_DEVICES_SPECIFIER );
			reported_default_device = alcGetString ( NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER );
			if ( reported_devices && reported_default_device )
			{
				devices_ext_present = DEP_YES;
			}
		}
	}

	if ( devices_ext_present == DEP_NO )
	{
		return FALSE;
	}

	*devices = reported_devices;
	*default_device = reported_default_device;

	return TRUE;
}

void allocate_source_sound_samples ( int number )
{
	int
		i;

	deallocate_source_sound_samples ();

	number_of_buffers = number;

	buffers = ( sound_buffer * ) safe_malloc ( number_of_buffers * sizeof ( sound_buffer ) );

	for ( i = 0; i < number_of_buffers; i++ )
	{
		AL_CHECK ( alGenBuffers ( 1, &buffers[i].buffer ) );
		buffers[i].size = 0;
	}
}

void deallocate_source_sound_samples ( void )
{
	int
		i;

	if (!number_of_buffers)
	{
		return;
	}

	for ( i = 0; i < number_of_buffers; i++ )
	{
		AL_CHECK ( alDeleteBuffers ( 1, &buffers[i].buffer ) );
	}

	safe_free ( buffers );

	number_of_buffers = 0;
}

int is_source_sound_sample_valid ( int sample_index )
{
	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_buffers );

	return buffers[sample_index].size;
}

void create_source_sound_sample ( int sample_index, sample_types type, int default_rate, int size )
{
	ALenum
		al_type;

	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_buffers );
	ASSERT ( !buffers[sample_index].size );

	switch ( type )
	{
	case SAMPLE_TYPE_MONO_8BIT:
		al_type = AL_FORMAT_MONO8;
		break;
	case SAMPLE_TYPE_STEREO_8BIT:
		al_type = AL_FORMAT_STEREO8;
		break;
	case SAMPLE_TYPE_MONO_16BIT:
		al_type = AL_FORMAT_MONO16;
		break;
	case SAMPLE_TYPE_STEREO_16BIT:
		al_type = AL_FORMAT_STEREO16;
		break;
	default:
		ASSERT ( FALSE );
	}

	buffers[sample_index].type = al_type;
	buffers[sample_index].size = size;
	buffers[sample_index].default_rate = default_rate;
}

void destroy_source_sound_sample ( int sample_index )
{
	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_buffers );
	ASSERT ( buffers[sample_index].size );

	AL_CHECK ( alBufferData ( buffers[sample_index].buffer, AL_FORMAT_MONO8, NULL, 0, 0 ) );
	buffers[sample_index].size = 0;
}

void load_source_sound_sample ( int sample_index, void* data )
{
	ASSERT ( sample_index >= 0 );
	ASSERT ( sample_index < number_of_buffers );
	ASSERT ( buffers[sample_index].size );

	AL_CHECK ( alBufferData ( buffers[sample_index].buffer, buffers[sample_index].type, data, buffers[sample_index].size, buffers[sample_index].default_rate ) );
}

static system_sound_effect * get_next_free_system_system_sound_effect ( void )
{
	int
		count;

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{
		if ( !current_system_sound_effects[count].used )
		{
			current_system_sound_effects[count].used = TRUE;

			return &current_system_sound_effects[count];
		}
	}

	return NULL;
}

system_sound_effect * create_single_system_sound_effect ( int sound_sample_index, int volume, int looping, void *user_data )
{
	system_sound_effect
		*effect;

	if ( !sound_system_initialised )
	{
		return NULL;
	}

	ASSERT ( sound_sample_index >= 0 );
	ASSERT ( sound_sample_index < number_of_buffers );
	ASSERT ( volume >= 0 );
	ASSERT ( volume <= SOUND_MAXIMUM_VOLUME );

	effect = get_next_free_system_system_sound_effect ();
	if ( effect )
	{
		float
			rate;

		rate = buffers[sound_sample_index].default_rate;

		effect->number_of_sequenced_samples = 1;
		effect->sound_sample_sequence[0].sound_sample_index = sound_sample_index;
		effect->sound_sample_sequence[0].rate = rate;
		effect->rate = rate;
		effect->playing = FALSE;
		effect->paused = FALSE;
		effect->looping = looping;
		effect->volume = volume;
		effect->pitch = 1.0;
		effect->user_data = user_data;

		AL_CHECK ( alSourceStop ( effect->panning ) );
		AL_CHECK ( alSourcei ( effect->panning, AL_BUFFER, buffers[sound_sample_index].buffer ) );
	}

	return effect;
}

system_sound_effect * create_sequenced_system_sound_effect ( int number_of_samples, sound_sequence_information *samples, int volume, void *user_data )
{
	system_sound_effect
		*effect;

	if ( !sound_system_initialised )
	{
		return NULL;
	}

	ASSERT ( number_of_samples >= 2 );
	ASSERT ( number_of_samples < MAX_SEQUENCED_SAMPLES );

	effect = get_next_free_system_system_sound_effect ();
	if ( effect )
	{
		int
			count;

		effect->number_of_sequenced_samples = number_of_samples;
		effect->current_sequenced_sample_offset = 0;
		for ( count = 0; count < number_of_samples; count++ )
		{
			ASSERT ( samples[count].sound_sample_index >= 0 );
			ASSERT ( samples[count].sound_sample_index < number_of_buffers );

			effect->sound_sample_sequence[count] = samples[count];
			if ( samples[count].rate == 0 )
			{
				samples[count].rate = buffers[ samples[count].sound_sample_index ].default_rate;
			}
		}

		effect->looping = FALSE;
		effect->volume = volume;
		effect->pitch = 1.0;
		effect->rate = samples[0].rate;
		effect->user_data = user_data;

		AL_CHECK ( alSourceStop ( effect->panning ) );
		AL_CHECK ( alSourcei ( effect->panning, AL_BUFFER, buffers[samples[0].sound_sample_index].buffer ) );
	}

	return ( effect );
}

int get_system_sound_effect_playing ( system_sound_effect *effect )
{
	ASSERT ( effect );

	effect->playing = FALSE;
	if ( effect->used )
	{
		ALint
			status;

		AL_CHECK ( alGetSourcei ( effect->panning, AL_SOURCE_STATE, &status ) );
		effect->playing = status == AL_PLAYING;
	}

	return effect->playing;
}

void destroy_system_sound_effect ( system_sound_effect *effect )
{
	ASSERT ( effect );
	ASSERT ( effect->used );

	AL_CHECK ( alSourceStop ( effect->panning ) );
	AL_CHECK ( alSourcei ( effect->panning, AL_BUFFER, 0 ) );

	effect->used = FALSE;
}

void set_system_sound_effect_user_data ( system_sound_effect *effect, void *user_data )
{
	ASSERT ( effect );
	effect->user_data = user_data;
}

void * get_system_sound_effect_user_data ( system_sound_effect *effect )
{
	ASSERT ( effect );
	return ( effect->user_data );
}

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

			effect->rate = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].rate;
			sound_sample_index = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].sound_sample_index;
			AL_CHECK ( alSourcei ( effect->panning, AL_BUFFER, buffers[sound_sample_index].buffer ) );
			AL_CHECK ( alSourcef ( effect->panning, AL_PITCH, effect->pitch ) );
			AL_CHECK ( alSourcef ( effect->panning, AL_GAIN, ( float ) effect->volume / SOUND_MAXIMUM_VOLUME ) );
			AL_CHECK ( alSource3f ( effect->panning, AL_POSITION, 0.0f, 0.0f, 0.0f ) );
			AL_CHECK ( alSourcef ( effect->panning, AL_SEC_OFFSET, time_position ) );
			AL_CHECK ( alSourcei ( effect->panning, AL_LOOPING, 0 ) );

			AL_CHECK ( alSourcePlay ( effect->panning ) );
		}
	}
}

void play_system_sound_effect ( system_sound_effect *effect, float time_position )
{
	ASSERT ( effect );
	ASSERT ( effect->used );

	if ( !effect->playing )
	{
		effect->playing = TRUE;
		effect->paused = FALSE;

		AL_CHECK ( alSourcef ( effect->panning, AL_PITCH, effect->pitch ) );
		AL_CHECK ( alSourcef ( effect->panning, AL_GAIN, ( float ) effect->volume / SOUND_MAXIMUM_VOLUME ) );
		AL_CHECK ( alSource3f ( effect->panning, AL_POSITION, 0.0f, 0.0f, 0.0f ) );
		AL_CHECK ( alSourcef ( effect->panning, AL_SEC_OFFSET, time_position ) );

		AL_CHECK ( alSourcePlay ( effect->panning ) );
	}
}

void pause_system_sound_effect ( system_sound_effect *effect )
{
	ASSERT ( effect );
	ASSERT ( effect->used );

	if ( !effect->paused )
	{
		effect->paused = TRUE;

		if ( !sound_system_paused )
		{
			AL_CHECK ( alSourceStop ( effect->panning ) );
		}
	}
}

void continue_system_sound_effect ( system_sound_effect *effect )
{
	ASSERT ( effect );
	ASSERT ( effect->used );

	if ( effect->paused )
	{
		effect->paused = FALSE;

		if ( !sound_system_paused )
		{
			AL_CHECK ( alSourcePlay ( effect->panning ) );
		}
	}
}

system_sound_effect * get_first_system_sound_effect ( void )
{
	int
		count;

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{
		if ( current_system_sound_effects[count].used )
		{
			return &current_system_sound_effects[count];
		}
	}

	return NULL;
}

system_sound_effect * get_next_system_sound_effect ( system_sound_effect *effect )
{
	int
		count;

	count = effect - current_system_sound_effects;

	count++;

	for ( ; count < maximum_current_system_sound_effects; count++ )
	{
		if ( current_system_sound_effects[count].used )
		{
			return &current_system_sound_effects[count];
		}
	}

	return NULL;
}

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

void update_system_sound_effect_system ( void )
{
	int
		count;

	system_sound_effect
		*effect;

	ALint
		status;

	if ( !sound_system_initialised )
	{
		return;
	}

	for ( count = 0; count < maximum_current_system_sound_effects; count++ )
	{
		effect = &current_system_sound_effects[count];

		if ( !effect->used || !effect->playing )
		{
			continue;
		}

		AL_CHECK ( alGetSourcei ( effect->panning, AL_SOURCE_STATE, &status ) );
		if ( status == AL_PLAYING )
		{
			continue;
		}

		if ( effect->number_of_sequenced_samples == 1 )
		{
			effect->playing = FALSE;
			continue;
		}

		if ( effect->current_sequenced_sample_offset == effect->number_of_sequenced_samples - 1 )
		{
			effect->playing = FALSE;
			continue;
		}

		{
			int
				sound_sample_index;

			effect->current_sequenced_sample_offset++;
			effect->rate = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].rate;
			sound_sample_index = effect->sound_sample_sequence[ effect->current_sequenced_sample_offset ].sound_sample_index;
			AL_CHECK ( alSourcei ( effect->panning, AL_BUFFER, buffers[sound_sample_index].buffer ) );
			AL_CHECK ( alSourcef ( effect->panning, AL_PITCH, effect->pitch ) );
			AL_CHECK ( alSourcef ( effect->panning, AL_GAIN, ( float ) effect->volume / SOUND_MAXIMUM_VOLUME ) );
			AL_CHECK ( alSource3f ( effect->panning, AL_POSITION, 0.0f, 0.0f, 0.0f ) );
			AL_CHECK ( alSourcef ( effect->panning, AL_SEC_OFFSET, 0.0 ) );
			AL_CHECK ( alSourcei ( effect->panning, AL_LOOPING, 0 ) );

			AL_CHECK ( alSourcePlay ( effect->panning ) );
		}
	}
}

void set_system_sound_effect_volume ( system_sound_effect *effect, int volume )
{
	ASSERT ( effect );
	ASSERT ( effect->used );

	ASSERT ( volume <= SOUND_MAXIMUM_VOLUME );
	ASSERT ( volume >= SOUND_MINIMUM_VOLUME );

	effect->volume = volume;

	AL_CHECK ( alSourcef ( effect->panning, AL_GAIN, ( float ) effect->volume / SOUND_MAXIMUM_VOLUME ) );
}

void set_system_sound_listener_orientation ( vec3d forward, vec3d up, vec3d right )
{
	float v[6];
	v[0] = forward.x;
	v[1] = forward.y;
	v[2] = forward.z;
	v[3] = up.x;
	v[4] = up.y;
	v[5] = up.z;
	AL_CHECK ( alListenerfv ( AL_ORIENTATION, v ) );
}

void set_system_sound_effect_position ( system_sound_effect *effect, vec3d position )
{
	ASSERT ( effect );
	ASSERT ( effect->used );

	// FIXME

	AL_CHECK ( alSource3f ( effect->panning, AL_POSITION, position.x, position.y, position.z ) );
}

void set_system_sound_effect_pitch ( system_sound_effect *effect, float pitch )
{
	ASSERT ( effect );
	ASSERT ( effect->used );

	effect->pitch = bound ( pitch, 0.1, 4.0 );

	AL_CHECK ( alSourcef ( effect->panning, AL_PITCH, effect->pitch ) );
}

void pause_sound_system ( void )
{
	if ( sound_system_initialised && !sound_system_paused )
	{
		int
			count;

		for ( count = 0; count < maximum_current_system_sound_effects; count++ )
		{

			if ( current_system_sound_effects[count].used && !current_system_sound_effects[count].paused )
			{
				AL_CHECK ( alSourceStop ( current_system_sound_effects[count].panning ) );
			}
		}

		sound_system_paused = TRUE;
	}
}

void continue_sound_system ( void )
{
	if ( sound_system_initialised && sound_system_paused )
	{
		int
			count;

		for ( count = 0; count < maximum_current_system_sound_effects; count++ )
		{
			if ( current_system_sound_effects[count].used && !current_system_sound_effects[count].paused )
			{
				AL_CHECK ( alSourcePlay ( current_system_sound_effects[count].panning ) );
			}
		}

		sound_system_paused = FALSE;
	}
}

int get_sound_system_paused ( void )
{
	return sound_system_paused;
}
