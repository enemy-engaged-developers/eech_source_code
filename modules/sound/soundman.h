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

//
// Sound system documentation
//
// Explanation of variables.
//
// Looping:	obvious, if its true the sound sample continuously loops, else it plays once and stops
//
// Volume:	volume is a linear scale from 0 to 255.
//
// Pan: 		Left / right sound control. In decibels.
//
// Rate:		Cycles per second of the sound wave.
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_SEQUENCED_SAMPLES 15

#define SOUND_MAXIMUM_VOLUME	255
#define SOUND_MAX_VOLUME	255

#define SOUND_MINIMUM_VOLUME	0
#define SOUND_MIN_VOLUME	0

#define SOUND_LEFT_PAN		DSBPAN_LEFT

#define SOUND_MIDDLE_PAN	DSBPAN_CENTER

#define SOUND_RIGHT_PAN		DSBPAN_RIGHT

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SOUND_SEQUENCE_INFORMATION
{

	int
		sound_sample_index,
		rate;
};

typedef struct SOUND_SEQUENCE_INFORMATION sound_sequence_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SYSTEM_SOUND_EFFECT
{

	LPDIRECTSOUNDBUFFER
		sound_buffer;

	int
		number_of_sequenced_samples,
		current_sequenced_sample_offset;

	sound_sequence_information
		sound_sample_sequence[MAX_SEQUENCED_SAMPLES];

	int
		rate,
		volume,
		panning,
		paused,
		playing,
		used,
		looping;

	void
		*user_data;
};

typedef struct SYSTEM_SOUND_EFFECT system_sound_effect;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// De/Initialise routine
//

extern int initialise_sound_system ( void );

extern void deinitialise_sound_system ( void );

//
// Sound Sample routines
//

extern void allocate_source_sound_samples ( int number );

extern void deallocate_source_sound_samples ( void );

extern int is_source_sound_sample_valid ( int sample_index );

extern void create_source_sound_sample ( int sample_index, sample_types type, int default_rate, int size );

extern void destroy_source_sound_sample ( int sample_index );

extern unsigned char * lock_source_sound_sample ( int sample_index );

extern void unlock_source_sound_sample ( int sample_index );

//
// Sound EFFECT routines
//

extern system_sound_effect * create_single_system_sound_effect ( int sound_sample_index, int panning, int rate, int volume, int looping, void *user_data );

extern system_sound_effect * create_sequenced_system_sound_effect ( int number_of_samples, sound_sequence_information *samples, int panning, int volume, void *user_data );

extern int get_system_sound_effect_playing ( system_sound_effect *effect );

extern void destroy_system_sound_effect ( system_sound_effect *effect );

extern void set_system_sound_effect_user_data ( system_sound_effect *effect, void *user_data );

extern void * get_system_sound_effect_user_data ( system_sound_effect *effect );

extern float get_system_sound_effect_playing_time ( system_sound_effect *effect );

extern void play_sequenced_system_sound_effect ( system_sound_effect *effect, int sequence_index, int buffer_position );

extern void play_system_sound_effect ( system_sound_effect *effect, int buffer_position );

extern void pause_system_sound_effect ( system_sound_effect *effect );

extern void continue_system_sound_effect ( system_sound_effect *effect );

extern system_sound_effect * get_first_system_sound_effect ( void );

extern system_sound_effect * get_next_system_sound_effect ( system_sound_effect *effect );

extern void destroy_all_system_sound_effects ( void );

extern void update_system_sound_effect_system ( void );

//
// Set volume / pan routines
//

extern void set_system_sound_effect_volume ( system_sound_effect *effect, int volume );

extern int get_system_sound_effect_volume ( system_sound_effect *effect );

extern void set_system_sound_effect_panning ( system_sound_effect *effect, int panning );

extern int get_system_sound_effect_panning ( system_sound_effect *effect );
//
// Sound SYSTEM routines
//

extern void pause_sound_system ( void );

extern void continue_sound_system ( void );

extern int get_sound_system_paused (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

