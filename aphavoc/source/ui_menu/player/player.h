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

#include "play_sc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_PLAYER_LEVELS	10

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MEDAL_HOURS_TO_BECOME_MASTER_AVIATOR 50

#define MEDAL_HOURS_TO_BECOME_SENIOR_AVIATOR 15

#define MEDAL_HOURS_TO_BECOME_ARMY_AVIATOR 4

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum PILOT_RANK_TYPES
{

	PILOT_RANK_NONE,
	PILOT_RANK_LIEUTENANT,
	PILOT_RANK_CAPTAIN,
	PILOT_RANK_MAJOR,
	PILOT_RANK_LT_COLONEL,
	PILOT_RANK_COLONEL,
	NUM_PILOT_RANKS
};

typedef enum PILOT_RANK_TYPES pilot_rank_types;

extern const char
	*pilot_rank_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum WEAPON_LOG_FIELDS
{
	WEAPON_LOG_FIRED,
	WEAPON_LOG_HIT,

	NUM_WEAPON_LOG_FIELDS
};

typedef enum WEAPON_LOG_FIELDS weapon_log_fields;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MEDAL_TYPES
{
	MEDAL_TYPE_NONE,
	MEDAL_SAUDI,
	MEDAL_LEBANON,
	MEDAL_TAIWAN,
	MEDAL_ARMY_AVIATOR,
	MEDAL_SENIOR_AVIATOR,
	MEDAL_MASTER_AVIATOR,
	MEDAL_PURPLE_HEART,
	MEDAL_AIR_MEDAL,
	MEDAL_FLYING_CROSS,
	MEDAL_SILVER_STAR,
	MEDAL_DISTINGUISHED_SERVICE,
	MEDAL_MEDAL_OF_HONOUR,
	
	NUM_MEDAL_TYPES
};

typedef enum MEDAL_TYPES medal_types;

extern const char
	*medal_type_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PLAYER_KILLS_TYPE
{
	int
		air,
		ground,
		sea,
		fixed,
		deaths,
		friendly;
};

typedef struct PLAYER_KILLS_TYPE player_kills_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PLAYER_COMMISSIONED_TYPE
{
	unsigned short int
		day			:	5,
		month			:	4,
		year			:	7;
};

typedef struct PLAYER_COMMISSIONED_TYPE player_commissioned_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PLAYER_SIDE_LOG_TYPE
{
	int
		rank,
		experience,
		failed_tours,
		missions_flown,
		successful_tours,
		air_medal_counter,
		medals [NUM_MEDAL_TYPES],
		level [NUM_PLAYER_LEVELS];

	float
		flying_seconds,
		mission_success_rate;

	player_kills_type
		kills;

	int
		weapon_usage[NUM_ENTITY_SUB_TYPE_WEAPONS][NUM_WEAPON_LOG_FIELDS];
};

typedef struct PLAYER_SIDE_LOG_TYPE player_side_log_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PLAYER_LOG_TYPE
{

	unsigned char
		*name;

	int
		unique_id;

	player_commissioned_type
		date_commissioned;

	player_side_log_type
		side_log [NUM_ENTITY_SIDES + 1];

	struct PLAYER_LOG_TYPE
		*next;
};

typedef struct PLAYER_LOG_TYPE player_log_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*us_medal_type_names [NUM_MEDAL_TYPES],
	*cis_medal_type_names [NUM_MEDAL_TYPES],
	*rank_type_names [NUM_PILOT_RANKS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_medal_and_promotion_names (void);

extern const char *get_pilot_rank_name (int rank);
extern const char *get_pilot_rank_short_name (int rank);
extern const char *get_untranslated_pilot_rank_short_name (int rank);

extern player_log_type *get_player_log_list ();
extern void set_player_log_list (player_log_type *log);

extern player_log_type *get_current_player_log ();
extern void set_current_player_log (player_log_type *log);

extern player_log_type *get_player_log_next (player_log_type *log);

extern char *get_player_log_name (player_log_type *log);

extern int get_player_rank_from_points ( int points );
extern int get_player_points_from_rank ( int rank );

extern int get_player_log_rank (int side, player_log_type *log);
extern void set_player_log_rank (int side, player_log_type *log, int rank);

extern int get_player_log_experience (int side, player_log_type *log);
extern void set_player_log_experience (int side, player_log_type *log, int experience);
extern void inc_player_log_experience (int side, player_log_type *log, int delta_experience);

extern int get_player_log_missions_flown (int side, player_log_type *log);
extern void set_player_log_missions_flown (int side, player_log_type *log, int missions_flown);
extern void inc_player_log_missions_flown (int side, player_log_type *log);

extern int get_player_log_failed_tours (int side, player_log_type *log);
extern void set_player_log_failed_tours (int side, player_log_type *log, int failed_tours);
extern void inc_player_log_failed_tours (int side, player_log_type *log);

extern int get_player_log_successful_tours (int side, player_log_type *log);
extern void set_player_log_successful_tours (int side, player_log_type *log, int successful_tours);
extern void inc_player_log_successful_tours (int side, player_log_type *log);

extern int get_player_log_level (int side, player_log_type *log);
extern void set_player_log_level (int side, player_log_type *log, int level);

extern int get_player_log_task_level (int side, player_log_type *log);

extern float get_player_log_flying_hours (int side, player_log_type *log);
extern float get_player_log_flying_seconds (int side, player_log_type *log);
extern void set_player_log_flying_seconds (int side, player_log_type *log, float flying_seconds);
extern void inc_player_log_flying_seconds (int side, player_log_type *log, float delta_flying_seconds);

extern void inc_player_log_kills (int side, player_log_type *log, entity *victim);

extern void update_player_log_mission_success_rate (int side, player_log_type *log, float success_rate);

extern int get_player_weapon_log_fired (int side, player_log_type *log, int weapon);
extern void set_player_weapon_log_fired (int side, player_log_type *log, int weapon, int hit_count);
extern void inc_player_weapon_log_fired (int side, player_log_type *log, int weapon);

extern int get_player_weapon_log_hit (int side, player_log_type *log, int weapon);
extern void set_player_weapon_log_hit (int side, player_log_type *log, int weapon, int hit_count);
extern void inc_player_weapon_log_hit (int side, player_log_type *log, int weapon);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
