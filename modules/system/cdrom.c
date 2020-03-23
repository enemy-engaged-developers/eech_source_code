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



#ifndef OGRE_EE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
#if 0
	cdrom_finder_initialised = FALSE,
	number_of_cdrom_drives,
#endif
	cdrom_track_playing = -1,
	cdrom_track_repeat = FALSE,
	cdrom_audio_track_playing = FALSE;
#if 0
	cdrom_drives[32],
	cdrom_file_drive_index = -1;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_cdrom_finder ( void );

static int internal_play_cd_audio_track ( void *data );

static long cdrom_notification_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_cdrom_system ( void )
{
#if 0
	register_system_message_function ( MM_MCINOTIFY, cdrom_notification_routine );
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_cdrom_file_exists ( const char *filename )
{
#if 0

	int
		count;

	char
		path[1024];

	if ( !cdrom_finder_initialised )
	{

		initialise_cdrom_finder ();
	}

	for ( count = 0; count < number_of_cdrom_drives; count++ )
	{

		sprintf ( path, "%c:\\%s", cdrom_drives[count], filename );

		if ( file_exist ( path ) )
		{

			cdrom_file_drive_index = count;

			return ( cdrom_drives[count] );
		}
	}
#endif
	return ( FALSE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void initialise_cdrom_finder ( void )
{

	char
		path[16];

	int
		letter;

	number_of_cdrom_drives = 0;

	for ( letter = 'A'; letter <= 'Z'; letter++ )
	{

		sprintf ( path, "%c:\\", letter );

		switch ( GetDriveType ( path ) )
		{

			case DRIVE_CDROM:
			{

				cdrom_drives[number_of_cdrom_drives] = letter;

				number_of_cdrom_drives++;

				break;
			}
		}
	}

	cdrom_finder_initialised = TRUE;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	cdrom_device_captured = FALSE;

static UINT
	cdrom_device_id = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int capture_cd_audio_device ( void )
{
#if 0
	DWORD
		value;

	char
		cdrom_element_name[4];

	DWORD
		dwFlags;

	MCI_OPEN_PARMS
		open_parameters;

	memset ( &open_parameters, 0, sizeof ( MCI_OPEN_PARMS ) );

	open_parameters.lpstrDeviceType = ( LPTSTR ) MCI_DEVTYPE_CD_AUDIO;

	if ( cdrom_file_drive_index != -1 )
	{

		//
		// We found a CD drive which we want to use for music
		//

		sprintf ( cdrom_element_name, "%c:", cdrom_drives[cdrom_file_drive_index] );

		open_parameters.lpstrElementName = cdrom_element_name;
	
		open_parameters.lpstrAlias = "CD Apache Havoc";
	
		dwFlags = MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE | MCI_OPEN_ALIAS | MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_WAIT;
	}
	else
	{

		//
		// We haven't looked for a CD drive - just use the standard cdaudio
		//

		dwFlags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE;
	}

	value = mciSendCommand ( 0, MCI_OPEN, dwFlags, ( DWORD ) ( LPVOID ) &open_parameters );

	if ( value )
	{

		debug_log ( "Unable to capture cd audio" );

		return ( FALSE );
	}
	else
	{

		MCI_SET_PARMS
			set_parameters;

		//
		// Get the device ID.
		//

		cdrom_device_id = open_parameters.wDeviceID;

		//
		// Set the cdrom format to tracks/minutes/seconds/frames
		//

		set_parameters.dwTimeFormat = MCI_FORMAT_TMSF;

		value = mciSendCommand ( cdrom_device_id, MCI_SET, MCI_SET_TIME_FORMAT, ( DWORD ) ( LPVOID ) &set_parameters );

		if ( value )
		{

			//
			// Release the device - it can't handle us!
			//

			debug_log ( "Unable to set cd audio format" );

			mciSendCommand ( cdrom_device_id, MCI_CLOSE, 0, 0 );

			return ( FALSE );
		}

		cdrom_device_captured = TRUE;

		register_exit_function ( release_cd_audio_device );

		return ( TRUE );
	}
#endif
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void release_cd_audio_device ( void )
{
#if 0
	if ( cdrom_device_captured )
	{

		mciSendCommand ( cdrom_device_id, MCI_CLOSE, 0, 0 );

		cdrom_device_captured = FALSE;
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_cd_audio_track ( int track )
{

	cdrom_track_repeat = FALSE;

	cdrom_track_playing = track;

	system_thread_function ( internal_play_cd_audio_track, &track );

	cdrom_track_repeat = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_one_shot_cd_audio_track ( int track )
{

	cdrom_track_repeat = FALSE;

	cdrom_track_playing = track;

	system_thread_function ( internal_play_cd_audio_track, &track );

	cdrom_track_repeat = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int internal_play_cd_audio_track ( void *data )
{

	int
		track;

	track = *( ( int * ) data );

	if ( cdrom_device_captured )
	{

		MCI_PLAY_PARMS
			play_parameters;

		MCI_STATUS_PARMS
			status_parameters;

		DWORD
			value;

		status_parameters.dwItem = MCI_STATUS_LENGTH;
		status_parameters.dwTrack = track;

		value = mciSendCommand ( cdrom_device_id, MCI_STATUS, ( MCI_TRACK | MCI_STATUS_ITEM ), ( DWORD ) ( LPVOID ) &status_parameters );

		if ( value )
		{

			debug_log ( "Unable to get track length" );
		}
		else
		{

			int
				minutes,
				seconds,
				frames;
	
			minutes = MCI_MSF_MINUTE ( status_parameters.dwReturn ),
			seconds = MCI_MSF_SECOND ( status_parameters.dwReturn ),
			frames = MCI_MSF_FRAME ( status_parameters.dwReturn ),
	
			play_parameters.dwFrom = 0;
			play_parameters.dwTo = 0;
			play_parameters.dwFrom = MCI_MAKE_TMSF ( track, 0, 0, 0 );
			play_parameters.dwTo = MCI_MAKE_TMSF ( track, minutes, seconds, frames );
			play_parameters.dwCallback = ( DWORD ) application_window;
	
			value = mciSendCommand ( cdrom_device_id, MCI_PLAY, ( MCI_FROM | MCI_TO | MCI_NOTIFY ), ( DWORD ) ( LPVOID ) &play_parameters );
	
			if ( value )
			{
	
				//
				// Ditch the cd player!
				//
	
				debug_log ( "Unable to play cd" );
	
				release_cd_audio_device ();
			}
			else
			{
	
				cdrom_audio_track_playing = TRUE;
			}
		}
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pause_cd_audio ( void )
{

	if ( cdrom_device_captured )
	{

		MCI_PLAY_PARMS
			pause_parameters;

		DWORD
			value;
	
		pause_parameters.dwCallback = 0;

		value = mciSendCommand ( cdrom_device_id, MCI_PAUSE, 0, ( DWORD ) ( LPVOID ) &pause_parameters );

		if ( value )
		{

			//
			// Ditch the cd player!
			//

			debug_log ( "Unable to pause cd" );

			release_cd_audio_device ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpause_cd_audio ( void )
{

	if ( cdrom_device_captured )
	{

		MCI_PLAY_PARMS
			pause_parameters;

		DWORD
			value;
	
		pause_parameters.dwCallback = 0;

		value = mciSendCommand ( cdrom_device_id, MCI_PLAY, 0, ( DWORD ) ( LPVOID ) &pause_parameters );

		if ( value )
		{

			//
			// Ditch the cd player!
			//

			debug_log ( "Unable to pause cd" );

			release_cd_audio_device ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_cd_audio ( void )
{

	if ( cdrom_device_captured )
	{

		MCI_PLAY_PARMS
			stop_parameters;

		DWORD
			value;
	
		stop_parameters.dwCallback = 0;

		cdrom_track_repeat = FALSE;

		value = mciSendCommand ( cdrom_device_id, MCI_PAUSE, 0, ( DWORD ) ( LPVOID ) &stop_parameters );

		if ( value )
		{

			//
			// Ditch the cd player!
			//

			debug_log ( "Unable to stop cd" );

			release_cd_audio_device ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_cd_audio_playing ( void )
{

	return ( cdrom_audio_track_playing );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
long cdrom_notification_routine ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	if ( cdrom_track_repeat )
	{

		MCI_PLAY_PARMS
			play_parameters;

		MCI_STATUS_PARMS
			status_parameters;

		DWORD
			value;

		status_parameters.dwItem = MCI_STATUS_LENGTH;
		status_parameters.dwTrack = cdrom_track_playing;

		value = mciSendCommand ( cdrom_device_id, MCI_STATUS, ( MCI_TRACK | MCI_STATUS_ITEM ), ( DWORD ) ( LPVOID ) &status_parameters );

		if ( !value )
		{

			int
				minutes,
				seconds,
				frames;
	
			minutes = MCI_MSF_MINUTE ( status_parameters.dwReturn ),
			seconds = MCI_MSF_SECOND ( status_parameters.dwReturn ),
			frames = MCI_MSF_FRAME ( status_parameters.dwReturn ),
	
			play_parameters.dwFrom = 0;
			play_parameters.dwTo = 0;
			play_parameters.dwFrom = MCI_MAKE_TMSF ( cdrom_track_playing, 0, 0, 0 );
			play_parameters.dwTo = MCI_MAKE_TMSF ( cdrom_track_playing, minutes, seconds, frames );
			play_parameters.dwCallback = ( DWORD ) application_window;
	
			mciSendCommand ( cdrom_device_id, MCI_PLAY, ( MCI_FROM | MCI_TO | MCI_NOTIFY ), ( DWORD ) ( LPVOID ) &play_parameters );
		}
	}
	else
	{

		cdrom_audio_track_playing = FALSE;
	}

	return ( TRUE );
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_cd_for_80_minutes ( void )
{

	if ( cdrom_device_captured )
	{

		int
			number_of_tracks,
			starting_position,
			track_length,
			total_cd_length,
			minute_cd_length,
			second_cd_length;

		MCI_STATUS_PARMS
			mciStatusParms;

		MCI_SET_PARMS
			set_parameters;
	
		//
		// Get the number of tracks; 
		//

		mciStatusParms.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;

		if ( mciSendCommand ( cdrom_device_id, MCI_STATUS, MCI_STATUS_ITEM, (DWORD) (LPVOID) &mciStatusParms ) )
		{

			debug_log ( "Unable to get number of tracks on CD" );

			return ( FALSE );
		}

		number_of_tracks = mciStatusParms.dwReturn;

		//
		// Now change the format of the CD to milliseconds
		//

		//
		// Set the cdrom format to tracks/minutes/seconds/frames
		//

		set_parameters.dwTimeFormat = MCI_FORMAT_MILLISECONDS;

		if ( mciSendCommand ( cdrom_device_id, MCI_SET, MCI_SET_TIME_FORMAT, ( DWORD ) ( LPVOID ) &set_parameters ) )
		{

			debug_log ( "Unable to set the cd to milliseconds format" );

			return ( FALSE );
		}

		//
		// Get the starting position of the last track
		//

		mciStatusParms.dwItem = MCI_STATUS_POSITION;

		mciStatusParms.dwTrack = number_of_tracks;

		if ( mciSendCommand ( cdrom_device_id, MCI_STATUS, MCI_STATUS_ITEM | MCI_TRACK, ( DWORD ) ( LPVOID ) &mciStatusParms ) )
		{

			debug_log ( "Unable to get position of last track ( %d )", number_of_tracks );

			return ( FALSE );
		}

		starting_position = mciStatusParms.dwReturn;

		//
		// Get the length of the last track
		//

		mciStatusParms.dwItem = MCI_STATUS_LENGTH;

		mciStatusParms.dwTrack = number_of_tracks;

		if ( mciSendCommand ( cdrom_device_id, MCI_STATUS, MCI_STATUS_ITEM | MCI_TRACK, ( DWORD ) ( LPVOID ) &mciStatusParms ) )
		{

			debug_log ( "Unable to get length of last track ( %d )", number_of_tracks );

			return ( FALSE );
		}

		track_length = mciStatusParms.dwReturn;

		debug_log ( "Cd has %d tracks - last one starts at %d, and is %d long", number_of_tracks, starting_position, track_length );

		//
		// Set the cdrom format to tracks/minutes/seconds/frames
		//

		set_parameters.dwTimeFormat = MCI_FORMAT_TMSF;

		if ( mciSendCommand ( cdrom_device_id, MCI_SET, MCI_SET_TIME_FORMAT, ( DWORD ) ( LPVOID ) &set_parameters ) )
		{

			debug_log ( "Unable to set the CD back to tracks format" );
		}

		//
		// Now calculate the end time of the CD
		//

		total_cd_length = starting_position + track_length;

		total_cd_length /= 1000;

		minute_cd_length = total_cd_length / 60;

		second_cd_length = total_cd_length - ( minute_cd_length * 60 );

		debug_log ( "I figure the CD is %d minutes, %d seconds long", minute_cd_length, second_cd_length );

		if ( minute_cd_length >= 75 )
		{

			debug_log ( "Successful: %d minute long CD", total_cd_length );

			return ( TRUE );
		}
		else
		{
	
			debug_log ( "Failure: %d minute long CD", total_cd_length );

			return ( FALSE );
		}
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
