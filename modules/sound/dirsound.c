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

#include "sound.h"

#include "cmndline.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPDIRECTSOUND
	dsound = NULL;

LPDIRECTSOUNDBUFFER
	dsound_primary_buffer = NULL;

LPDIRECTSOUND3DLISTENER
	d3dsound_listener;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static BOOL dsound_release_objects ( void );

static void dsound_restore_objects ( int activate );

BOOL dsound_initialise ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL initialise_direct_sound ( void )
{

	static int
		direct_sound_initialised = FALSE;

	if ( !direct_sound_initialised )
	{

		if ( dsound_initialise () )
		{
			// crh 030320 lack of (void *) cast generates a warning with open watcom
			// feel free to yell at me if this is a problem
			register_exit_function ( ( void (*) ( void ) ) dsound_release_objects );

			register_post_activate_message_function ( dsound_restore_objects );
		
			direct_sound_initialised = TRUE;

			set_fpu_rounding_mode_zero ();

			return ( TRUE );
		}
		else
		{

			return ( FALSE );
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL dsound_initialise ( void )
{
	
	HRESULT
		dsrval;

	DSBUFFERDESC
		dsbdesc;

	//
	// Create the direct sound object
	//

	dsrval = DirectSoundCreate (NULL, &dsound, NULL);
	
	// JB 030311 compile fix
	if ( dsrval != DS_OK )
	{

		debug_log ( "Unable to create direct sound object: %s", get_dsound_error_message ( dsrval ) );

		return ( FALSE );
	}

	dsrval = IDirectSound_SetCooperativeLevel ( dsound, application_window, DSSCL_PRIORITY );

	// JB 030311 compile fix
	if ( dsrval != DS_OK )
	{

		debug_log ( "Unable to set direct sound cooperative level: %s", get_dsound_error_message ( dsrval ) );

		//
		// Remove the DirectSound object
		//

		IDirectSound_Release ( dsound );

		return ( FALSE );
	}

	memset ( &dsbdesc, 0, sizeof ( DSBUFFERDESC ) );

	dsbdesc.dwSize = sizeof ( DSBUFFERDESC );

	dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;

	dsrval = IDirectSound_CreateSoundBuffer ( dsound, &dsbdesc, &dsound_primary_buffer, NULL );

	if ( dsrval != DS_OK )
	{

		debug_log ( "Unable to create primary sound buffer: %s", get_dsound_error_message ( dsrval ) );

		//
		// Reset cooperative level, release DirectSound object
		//

		IDirectSound_SetCooperativeLevel ( dsound, application_window, DSSCL_NORMAL );

		IDirectSound_Release ( dsound );

		return ( FALSE );
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dsound_restore_objects ( int activate )
{
	
	if ( ( application_active ) && ( dsound ) )
	{

		//
		// Go through all the sound buffers, checking if lost, and restore if necessary
		//
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static BOOL dsound_release_objects ( void )
{

	if ( dsound )
	{

		if ( dsound_primary_buffer )
		{

			IDirectSoundBuffer_Release ( dsound_primary_buffer );

			dsound_primary_buffer = NULL;
		}

		IDirectSound_Release ( dsound );

		dsound = NULL;
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPDIRECTSOUNDBUFFER dsound_create_sound_buffer ( sample_types type, int rate, int size )
{

	PCMWAVEFORMAT
		pcmwf;

	DSBUFFERDESC
		dsbdesc;

	LPDIRECTSOUNDBUFFER
		buffer;

	HRESULT
		dsrval;

	if ( !dsound )
	{

		return ( NULL );
	}
	else
	{
	
		memset ( &pcmwf, 0, sizeof ( PCMWAVEFORMAT ) );
	
		pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM;
	
		switch ( type )
		{
	
			case SAMPLE_TYPE_MONO_8BIT:
			{
	
					pcmwf.wf.nChannels = 1;
	
					pcmwf.wf.nBlockAlign = 1;
	
					pcmwf.wBitsPerSample = 8;
	
					break;
			}
	
			case SAMPLE_TYPE_STEREO_8BIT:
			{
	
					pcmwf.wf.nChannels = 2;
	
					pcmwf.wf.nBlockAlign = 2;
	
					pcmwf.wBitsPerSample = 8;
	
					break;
			}
	
			case SAMPLE_TYPE_MONO_16BIT:
			{
	
					pcmwf.wf.nChannels = 1;
	
					pcmwf.wf.nBlockAlign = 2;
	
					pcmwf.wBitsPerSample = 16;
	
					break;
			}
	
			case SAMPLE_TYPE_STEREO_16BIT:
			{
	
					pcmwf.wf.nChannels = 2;
	
					pcmwf.wf.nBlockAlign = 4;
	
					pcmwf.wBitsPerSample = 16;
	
					break;
			}
	
			default:
			{
	
				debug_fatal ( "Unknown sample type in create_sound_buffer" );
	
				break;
			}
		}
	
		memset ( &dsbdesc, 0, sizeof ( DSBUFFERDESC ) );
	
		dsbdesc.dwSize = sizeof ( DSBUFFERDESC );
	
		dsbdesc.lpwfxFormat = ( LPWAVEFORMATEX ) &pcmwf;
	
		dsbdesc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_LOCSOFTWARE;
	
		dsbdesc.dwBufferBytes = size;
	
		pcmwf.wf.nSamplesPerSec = rate;
	
		pcmwf.wf.nAvgBytesPerSec = ( pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign );
	
		dsrval = IDirectSound_CreateSoundBuffer ( dsound, &dsbdesc, &buffer, NULL );
	
		if ( dsrval != DS_OK )
		{
	
			debug_log ( "Unable to create sound buffer: ( %d, %d ) - %s", rate, size, get_dsound_error_message ( dsrval ) );
	
			return ( NULL );
		}
	
		return ( buffer );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPDIRECTSOUNDBUFFER dsound_duplicate_sound_buffer ( LPDIRECTSOUNDBUFFER buffer, int size )
{

	HRESULT
		dsrval;

	LPDIRECTSOUNDBUFFER
		duplicand;

	WAVEFORMATEX
		pcmwf;
	DSBUFFERDESC
		dsbdesc;
	unsigned char * datasrc, * datadst;

	ASSERT ( buffer );

	// Casm 11JUN05 Hardware sound buffers
	if ( command_line_sound_hdwrbuf > 0 )
	{
		dsrval = IDirectSoundBuffer_GetFormat ( buffer, ( LPWAVEFORMATEX ) &pcmwf, sizeof(pcmwf), NULL );
		if ( dsrval != DS_OK )
		{
			debug_log ( "Unable to get format: %s", get_dsound_error_message ( dsrval ) );
			return ( NULL );
		}

		memset ( &dsbdesc, 0, sizeof ( DSBUFFERDESC ) );
		dsbdesc.dwSize = sizeof ( DSBUFFERDESC );
		dsbdesc.lpwfxFormat = ( LPWAVEFORMATEX ) &pcmwf;
		dsbdesc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_LOCHARDWARE;
		dsbdesc.dwBufferBytes = size;

		dsrval = IDirectSound_CreateSoundBuffer ( dsound, &dsbdesc, &duplicand, NULL );
		if ( dsrval != DS_OK )
		{
			debug_log ( "Unable to create hardware sound buffer: ( %d, %d ) - %s", pcmwf.nSamplesPerSec, size, get_dsound_error_message ( dsrval ) );
			return ( NULL );
		}

		datasrc = dsound_lock_sound_buffer ( buffer, 0, size );
		if ( datasrc == NULL )
		{
			IDirectSoundBuffer_Release ( duplicand );
			return ( NULL );
		}
		datadst = dsound_lock_sound_buffer ( duplicand, 0, size );
		if ( datadst == NULL )
		{
			dsound_unlock_sound_buffer ( buffer, datasrc, size );
			IDirectSoundBuffer_Release ( duplicand );
			return ( NULL );
		}
		memcpy ( datadst, datasrc, size );
		dsound_unlock_sound_buffer ( buffer, datasrc, size );
		dsound_unlock_sound_buffer ( duplicand, datadst, size );

		return ( duplicand );
	}
	// Casm 11JUN05 Hardware sound buffers

	dsrval = IDirectSound_DuplicateSoundBuffer ( dsound, buffer, &duplicand );

	if ( dsrval != DS_OK )
	{

		debug_log ( "Unable to duplicate sound buffer: %s", get_dsound_error_message ( dsrval ) );

		return ( NULL );
	}

	return ( duplicand );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dsound_destroy_sound_buffer ( LPDIRECTSOUNDBUFFER buffer )
{

	HRESULT
		dsrval;

	ASSERT ( buffer );

	dsrval = IDirectSoundBuffer_Release ( buffer );

	if ( dsrval != DS_OK )
	{

		debug_log ( "Unable to destroy a sound buffer: %s", get_dsound_error_message ( dsrval ) );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DSOUND_ERROR_MESSAGE
{

	HRESULT
		error;

	char
		* error_string;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct DSOUND_ERROR_MESSAGE dsound_error_table[] =
{

	{ DSERR_ALLOCATED, "DSERR_ALLOCATED" },
	{ DSERR_CONTROLUNAVAIL, "DSERR_CONTROLUNAVAIL" },
	{ DSERR_INVALIDPARAM, "DSERR_INVALIDPARAM" },
	{ DSERR_INVALIDCALL, "DSERR_INVALIDCALL" },
	{ DSERR_GENERIC, "DSERR_GENERIC" },
	{ DSERR_PRIOLEVELNEEDED, "DSERR_PRIOLEVELNEEDED" },
	{ DSERR_OUTOFMEMORY, "DSERR_OUTOFMEMORY" },
	{ DSERR_BADFORMAT, "DSERR_BADFORMAT" },
	{ DSERR_UNSUPPORTED, "DSERR_UNSUPPORTED" },
	{ DSERR_NODRIVER, "DSERR_NODRIVER" },
	{ DSERR_ALREADYINITIALIZED, "DSERR_ALREADYINITIALIZED" },
	{ DSERR_NOAGGREGATION, "DSERR_NOAGGREGATION" },
	{ DSERR_BUFFERLOST, "DSERR_BUFFERLOST" },
	{ DSERR_OTHERAPPHASPRIO, "DSERR_OTHERAPPHASPRIO" },
	{ DSERR_UNINITIALIZED, "DSERR_UNINITIALIZED" },
	{ DS_OK, "DS_OK - should not have got here!" },
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char * get_dsound_error_message ( HRESULT error )
{

	int
		count;


	count = 0;

	while ( ( dsound_error_table[count].error != 0 ) && ( dsound_error_table[count].error != error ) )
	{

		count ++;
	}

	return ( dsound_error_table[count].error_string );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

