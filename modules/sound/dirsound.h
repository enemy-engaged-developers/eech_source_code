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

enum SAMPLE_STATES
{

	SAMPLE_STATE_INVALID,
	SAMPLE_STATE_PLAYING,
	SAMPLE_STATE_PAUSED,
	SAMPLE_STATE_FINISHED,
};

typedef enum SAMPLE_STATES sample_state;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern LPDIRECTSOUND
	dsound;

extern LPDIRECTSOUNDBUFFER
	dsound_primary_buffer;

extern LPDIRECTSOUND3DLISTENER
	d3dsound_listener;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char * get_dsound_error_message ( HRESULT error );

extern BOOL initialise_direct_sound ( void );

//
// Creation / destruction
//

extern LPDIRECTSOUNDBUFFER dsound_create_sound_buffer ( sample_types type, int rate, int size );

extern LPDIRECTSOUNDBUFFER dsound_duplicate_sound_buffer ( LPDIRECTSOUNDBUFFER buffer, int size );

extern void dsound_destroy_sound_buffer ( LPDIRECTSOUNDBUFFER buffer );

//
// Set / Access functions
//

extern void dsound_play_buffer ( LPDIRECTSOUNDBUFFER buffer, int loop );

extern void dsound_stop_buffer ( LPDIRECTSOUNDBUFFER buffer );

extern void dsound_set_buffer_rate ( LPDIRECTSOUNDBUFFER buffer, int rate );

extern int dsound_get_buffer_rate ( LPDIRECTSOUNDBUFFER buffer );

extern void dsound_set_buffer_volume ( LPDIRECTSOUNDBUFFER buffer, int volume );

extern int dsound_get_buffer_volume ( LPDIRECTSOUNDBUFFER buffer );

extern void dsound_set_buffer_pan ( LPDIRECTSOUNDBUFFER buffer, int pan );

extern int dsound_get_buffer_pan ( LPDIRECTSOUNDBUFFER buffer );

extern void dsound_set_buffer_position ( LPDIRECTSOUNDBUFFER buffer, int position );

extern int dsound_get_buffer_position ( LPDIRECTSOUNDBUFFER buffer );

extern enum SAMPLE_STATES dsound_get_buffer_status ( LPDIRECTSOUNDBUFFER buffer );

extern unsigned char * dsound_lock_buffer ( LPDIRECTSOUNDBUFFER buffer, int position, int size );

extern BOOL dsound_unlock_buffer ( LPDIRECTSOUNDBUFFER buffer, unsigned char *data, int length );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

