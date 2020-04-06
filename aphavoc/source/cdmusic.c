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
static music_tracks music_track_playing = MUSIC_TRACK_INVALID;
static music_types music_type_playing = MUSIC_TYPE_INVALID;
static music_tracks last_music_track_played[MUSIC_TYPE_LAST];
static entity *music_entity = NULL;
static float music_update_timer = 0.0;
static float music_fadeout_timer = -1.0;
static float music_fadeout = 0.0;

static void create_music_entity( music_tracks track, music_types type, int repeate );
static music_tracks music_track_is_playing ( void );
static music_tracks get_last_played_track(music_types type);
static void play_music_track ( music_tracks track, music_types type );
static void play_one_shot_music_track ( music_tracks track, music_types type );
static music_types music_type_is_playing ( void );
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_music (music_types music_type, int force)
{
#ifndef OGRE_EE
	music_tracks
		track, last_played;

	if (get_global_sound_music () != GAME_MUSIC_ON || command_line_no_sound || command_line_comms_dedicated_server) {
		return;
	}
		
	#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: play_music");
	#endif

	// SKIP UNWANTED
	switch (music_type)
	{
		case MUSIC_TYPE_INTRO:
			if (command_line_no_intro_music)
				return;
			break;
		case MUSIC_TYPE_INGAME:
			if (command_line_no_ingame_music)
				return;
			break;
		case MUSIC_TYPE_ACTION:
			if (command_line_no_action_music)
				return;
			break;					
		case MUSIC_TYPE_MISSION_COMPLETE:
			if (command_line_no_mission_complete_music)
				return;
			break;
		default:
			break;
	}

	// Never play over an already playing track
	if (music_track_is_playing ()) {
		if (force) {
			stop_music(0.0);
		}
		else {
			#if DEBUG_MODULE
				debug_log ("CDMUSIC.C: already playing music, skip");
			#endif
			return;
		}
	}

	if (!music_track_is_playing()) 
	{
		last_played = get_last_played_track(music_type);

		switch (music_type)
		{
			case MUSIC_TYPE_INTRO:
				/*play_music_track (MUSIC_TRACK_INTRO, music_type);
				#if DEBUG_MODULE
					debug_log ("CDMUSIC.C: Playing Intro Tune");
				#endif*/
				break;
			case MUSIC_TYPE_INGAME:
				do {
					track = ( music_tracks ) ( MUSIC_TRACK_INGAME1 + (rand16() % NUM_CD_MUSIC_INGAME_TRACKS) );
				} while ( track == last_played );
				play_music_track (track, music_type);
				#if DEBUG_MODULE
					debug_log ("CDMUSIC.C: Playing Ingame Tune, no:%d", track);
				#endif
				break;
			case MUSIC_TYPE_ACTION:
				do {
					track = ( music_tracks ) ( MUSIC_TRACK_ACTION1 + (rand16() % NUM_CD_MUSIC_ACTION_TRACKS) );
				} while ( track == last_played );
				play_music_track (track, music_type);
				#if DEBUG_MODULE
					debug_log ("CDMUSIC.C: Playing Fight Tune, no:%d", track);
				#endif
				break;					
			case MUSIC_TYPE_MISSION_COMPLETE:
				do {
					track = ( music_tracks ) ( MUSIC_TRACK_MISSION_COMPLETE1 + (rand16() % NUM_CD_MUSIC_MISSION_COMPLETE_TRACKS) );
				} while ( track == last_played );
				play_one_shot_music_track (track, music_type);
				#if DEBUG_MODULE
					debug_log ("CDMUSIC.C: Playing Mission Complete Tune, no:%d", track);
				#endif
				break;
			default:
				#if DEBUG_MODULE
					debug_log ("CDMUSIC.C: Unknown Tune");
				#endif					
				break;
		}
	} else {
		#if DEBUG_MODULE
			debug_log ("CDMUSIC.C: Already playing music");
		#endif
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void probably_change_cd_music ()
{
#ifndef OGRE_EE
	music_tracks music_track_playing;
	music_types music_type_playing;	
	int is_airborne, is_active_target, player_have_target, player_firing_weapon;
	
	if ( get_global_sound_music () != GAME_MUSIC_ON || command_line_no_sound || command_line_comms_dedicated_server || !get_gunship_entity()/*pilot_entity*/) {
		return;
	}
	
	music_track_playing = music_track_is_playing();
	music_type_playing = music_type_is_playing();
	
	is_airborne = get_local_entity_int_value (get_gunship_entity(), INT_TYPE_AIRBORNE_AIRCRAFT);
	is_active_target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_TARGET) != NULL;
	player_have_target = FALSE;//get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET) != NULL;
	player_firing_weapon = get_local_entity_first_child (get_gunship_entity(), LIST_TYPE_LAUNCHED_WEAPON) != NULL;
	
	#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: probably_change_cd_music, airborne: %d, active target: %d, have target: %d, firing weapon: %d", is_airborne, is_active_target, player_have_target, player_firing_weapon);
	#endif

	// CHANGE TO FIGHT TRACK
	if (is_active_target && music_type_playing != MUSIC_TYPE_ACTION && music_type_playing != MUSIC_TYPE_MISSION_COMPLETE) {
		play_music(MUSIC_TYPE_ACTION, TRUE);
	}
	// STOP FIGHT TRACK
	else if (!is_active_target && !player_have_target && !player_firing_weapon && music_type_playing == MUSIC_TYPE_ACTION) {
		stop_music(10.0);
	}
	// CHANGE TO INGAME TRACK
	else if (!music_track_playing && is_airborne) {
		play_music(MUSIC_TYPE_INGAME, FALSE);
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pause_music ( void )
{
#ifndef OGRE_EE

#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: pause_music");
	#endif

	if ( get_global_sound_music () != GAME_MUSIC_ON || command_line_no_sound || command_line_comms_dedicated_server || !music_track_playing) {
		return;
	}

	ASSERT( music_entity );

	if (music_entity != NULL) {
		pause_local_entity_sound_type(music_entity, ENTITY_SUB_TYPE_EFFECT_SOUND_MUSIC, 0.0/*get_local_entity_float_value(music_entity, FLOAT_TYPE_EFFECT_LIFETIME)*/);
	}
	
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpause_music ( void )
{
#ifndef OGRE_EE
	
	#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: unpause_music");
	#endif

	if ( get_global_sound_music () != GAME_MUSIC_ON || command_line_no_sound || command_line_comms_dedicated_server || !music_track_playing) {
		return;
	}

	ASSERT( music_entity );

	if (music_entity != NULL) {
		resume_local_entity_sound_type(music_entity, ENTITY_SUB_TYPE_EFFECT_SOUND_MUSIC);
	}
	
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_music ( float fadeout )
{
#ifndef OGRE_EE

	if ( get_global_sound_music () != GAME_MUSIC_ON || command_line_no_sound || command_line_comms_dedicated_server || !music_track_playing) {
		return;
	}

	#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: stop_music");
	#endif

	ASSERT (music_entity);
		
	if (fadeout == 0.0) {
		music_track_playing = MUSIC_TRACK_INVALID;
		music_type_playing = MUSIC_TYPE_INVALID;

		if (music_entity != NULL) {
			destroy_local_entity (music_entity);
			music_entity = NULL;
		}
	}
	else {
		music_fadeout_timer = fadeout;
		music_fadeout = fadeout;
	}
	
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_music (void) {
#ifndef OGRE_EE

	int i;
	for (i = 0; i < MUSIC_TYPE_LAST; i++) {
		last_music_track_played[i] = MUSIC_TRACK_INVALID;
	}

	add_update_function (update_music, 1.0, 1.0);
	add_update_function (update_music_fadeout, 0.1, 1.0);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE

void play_music_track ( music_tracks track, music_types type )
{
	#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: play_music_track");
	#endif

	create_music_entity(track, type, TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_one_shot_music_track ( music_tracks track, music_types type )
{
	#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: play_one_shot_music_track");
	#endif

	create_music_entity(track, type, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_music_entity( music_tracks track, music_types type, int loop ) {
	sound_sample_indices sample_index;
	vec3d pos;
	
	if (!get_gunship_entity()/*pilot_entity*/) {
		return;
	}
	
	pos.x = 0.0;
	pos.z = 0.0;
	pos.y = 10.0;
	
	sample_index = SOUND_SAMPLE_INDEX_MUSIC_INVALID + track;

	music_entity = create_local_sound_effect_entity
	(
		ENTITY_INDEX_DONT_CARE,
		get_gunship_entity()/*pilot_entity*/,
		ENTITY_SIDE_NEUTRAL,
		ENTITY_SUB_TYPE_EFFECT_SOUND_MUSIC,
		SOUND_CHANNEL_SYSTEM,
		SOUND_LOCALITY_INTERIOR,
		&pos,												// position
		1.0,												// amplification
		1.0,												// Werewolf pitch
		TRUE,												// valid sound effect
		loop,											// looping
		1,													// sample count
		&sample_index									// sample index list
	);	
	
	ASSERT( music_entity );

	if (music_entity != NULL) {
		music_track_playing = track;
		music_type_playing = type;
		last_music_track_played[type] = track;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

music_tracks music_track_is_playing ( void )
{
	if (music_track_playing) {
		ASSERT(music_entity);
	
		#if DEBUG_MODULE
			debug_log ("CDMUSIC.C: Music is playing: %d", music_track_playing);
		#endif

		if (music_entity != NULL) {
			if (!get_local_entity_int_value(music_entity, INT_TYPE_SOUND_EFFECT_LOOPING) && get_local_entity_float_value(music_entity, FLOAT_TYPE_EFFECT_LIFETIME) <= 0) {
				#if DEBUG_MODULE
					debug_log ("CDMUSIC.C: Music is should be stopped 1: %d", music_track_playing);
				#endif
				stop_music(0.0);
			}
		} else {
			#if DEBUG_MODULE
				debug_log ("CDMUSIC.C: Music is should be stopped 2: %d", music_track_playing);
			#endif
			stop_music(0.0);
		}
		
		return music_track_playing;
	}

	#if DEBUG_MODULE
		debug_log ("CDMUSIC.C: Music is not playing");
	#endif

	return music_track_playing;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

music_types music_type_is_playing ( void )
{
	return music_type_playing;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

music_tracks get_last_played_track(music_types type) {
	return last_music_track_played[type];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_music( void ) {
	if ( get_global_sound_music () != GAME_MUSIC_ON || command_line_no_sound || command_line_comms_dedicated_server) {
		return;
	}
	
	if (music_track_is_playing() && get_gunship_entity() == NULL ) {
		stop_music(0.0);
	}
	else if (get_gunship_entity() && get_time_acceleration () != TIME_ACCELERATION_PAUSE) {
		music_update_timer -= 1.0;
		if (music_update_timer <= 0.0) {
			music_update_timer = 10.0 + frand1() * 10.0;
			probably_change_cd_music();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_music_fadeout( void ) {
	if ( get_global_sound_music () != GAME_MUSIC_ON || command_line_no_sound || command_line_comms_dedicated_server)
		return;
	if (music_fadeout_timer < 0.0)
		return;
	if (!music_track_is_playing())
		return;
	if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
		return;

	ASSERT(music_entity);
	
	music_fadeout_timer -= 0.1;
	
#if DEBUG_MODULE
	debug_log ("CDMUSIC.C: Fadeout: %f / %f", music_fadeout_timer, music_fadeout);
#endif

	if (music_entity != NULL) {
		if (get_gunship_entity() == NULL || music_fadeout_timer < 0.0) {
			stop_music(0.0);
		} else {
			set_local_entity_float_value(music_entity, FLOAT_TYPE_AMPLIFICATION, fmax(0, music_fadeout_timer / music_fadeout));
		}
	}
}

#endif
