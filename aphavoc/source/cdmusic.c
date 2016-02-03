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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
static cd_music_tracks
	current_music_track = CD_MUSIC_TRACK_INVALID;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_cd_music (cd_music_types music_type)
{
#ifndef OGRE_EE
	cd_music_tracks
		track;

	// Check that we've got permission to play the track
	if (get_global_sound_music () == GAME_MUSIC_ON)
	{
		// Never play over an already playing track
		if (!is_cd_audio_playing ())
		{
			switch (music_type)
			{
		
				case CD_MUSIC_TYPE_INTRO:
				{
					current_music_track = CD_MUSIC_TRACK_INTRO;

					play_one_shot_cd_audio_track (CD_MUSIC_TRACK_INTRO);
			
					#if DEBUG_MODULE
						debug_filtered_log ("CDMUSIC.C: Playing Intro Tune");
					#endif
		
					break;
				}
		
				case CD_MUSIC_TYPE_COCKPIT:
				{
		
					track = ( cd_music_tracks ) ( CD_MUSIC_TRACK_INGAME1 + (rand16() % NUM_CD_MUSIC_COCKPIT_TRACKS) );
					
					current_music_track = track;
		
					play_one_shot_cd_audio_track (track);
		
					#if DEBUG_MODULE
						debug_filtered_log ("CDMUSIC.C: Playing Cockpit Tune, no:%d", current_music_track);
					#endif
		
					break;
				}
				
				case CD_MUSIC_TYPE_MISSION_COMPLETE:
				{
		
					track = ( cd_music_tracks ) ( CD_MUSIC_TRACK_MISSION_COMPLETE1 + (rand16() % NUM_CD_MUSIC_MISSION_COMPLETE_TRACKS) );
					
					current_music_track = track;
		
					play_one_shot_cd_audio_track (track);
		
					#if DEBUG_MODULE
						debug_filtered_log ("CDMUSIC.C: Playing Mission Complete Tune, no:%d", current_music_track);
					#endif
		
					break;
				}
			}
			#if DEBUG_MODULE
				debug_filtered_log ("CDMUSIC.C: Already playing music");
			#endif
		}
		#if DEBUG_MODULE
			debug_filtered_log ("CDMUSIC.C: Music set to OFF");
		#endif
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_cd_music ( void )
{
#ifndef OGRE_EE

	if ( current_music_track != CD_MUSIC_TRACK_INVALID )
	{
	
		stop_cd_audio ();
	
		current_music_track = CD_MUSIC_TRACK_INVALID;
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
