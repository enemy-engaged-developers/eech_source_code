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

struct TASK_KILL_LOSS_DATA
{

	entity_types
		victim_type,
		aggressor_type;

	entity_sides
		victim_side,
		aggressor_side;

	entity_sub_types
		victim_sub_type,
		aggressor_sub_type;
		
	int
		victim_id,
		aggressor_id;

	float
		time;

	int
		day;

	struct TASK_KILL_LOSS_DATA
		*next;
};

typedef struct TASK_KILL_LOSS_DATA task_kill_loss_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TASK
{

	entity_sub_types
		sub_type;

	task_state_types
		task_state;

	vec3d
		position,
		*route_nodes;

	float
		task_user_data,
		task_priority,
		rating,
		start_time,
		stop_timer,
		expire_timer;

	entity
		*return_keysite,
		**route_dependents;

	formation_types
		*route_formation_types;

	entity_sub_types
		*route_waypoint_types;

	list_root
		guide_root,
		player_task_root,
		task_dependent_root,
		waypoint_root;

	list_link
		pilot_lock_link,
		sector_task_link,
		task_dependent_link,
		task_link, 					// used for both assigned and unassigned task
		update_link;

	task_terminated_types
		task_terminated;

	task_kill_loss_data
		*task_kills,
		*task_losses;

	unsigned int
		awarded_medals				: NUM_AWARDED_MEDALS_BITS,
		awarded_promotion			: NUM_AWARDED_PROMOTION_BITS,
		task_id						: NUM_TASK_ID_BITS,
		task_completed				: NUM_TASK_COMPLETED_BITS,
		route_check_sum			: NUM_ROUTE_CHECK_SUM_BITS,
		kills							: NUM_KILLS_BITS,
		losses						: NUM_LOSSES_BITS,
		player_task					: NUM_PLAYER_TASK_BITS,
		movement_type				: NUM_MOVEMENT_TYPE_BITS,
		difficulty					: NUM_TASK_DIFFICULTY_BITS,
		critical_task				: NUM_CRITICAL_TASK_BITS,
		task_score					: NUM_TASK_SCORE_BITS,
		route_length				: NUM_ROUTE_LENGTH_BITS,
		side							: NUM_SIDE_BITS;
};

typedef struct TASK task;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ts_creat.h"

#include "ts_dbase.h"

#include "ts_dstry.h"

#include "ts_float.h"

#include "ts_funcs.h"

#include "ts_int.h"

#include "ts_list.h"

#include "ts_msgs.h"

#include "ts_pack.h"

#include "ts_ptr.h"

#include "ts_str.h"

#include "ts_updt.h"

#include "ts_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern task_completed_types assess_task_completeness (entity *en, task_terminated_types task_terminated);

extern int award_points_for_task_completion (entity *en);

extern list_types get_local_task_list_type (entity *task_en);

extern entity *get_local_entity_current_task (entity *member);

extern int entity_is_object_of_task (entity *en, entity_sub_types task_type, entity_sides side);

extern int assess_task_locality_factor (entity *task_en, vec3d *pos1, float cruise_speed, float *return_distance);

extern int assess_task_difficulty (entity *task_en, int *route_air_threat, int *route_enemy_sectors);

extern entity *get_local_group_primary_task (entity *en);

extern entity *get_local_entity_primary_task (entity *en);

extern entity *find_most_suitable_keysite_for_task (entity_sub_types task_type, entity_sides side, vec3d *pos, int check_capacity);

#ifdef DEBUG

extern void validate_task_entity (entity *en);

#endif

extern void add_kill_to_task (entity *task_en, entity *victim, entity *aggressor);

extern void add_loss_to_task (entity *task_en, entity *victim, entity *aggressor);

extern float get_task_estimated_route_duration (entity *task);

extern void set_completed_task_expire_time (float value);

extern float get_completed_task_expire_time (void);

extern const char *get_task_objective_string (entity *en);

extern void get_task_objective_mfd_display_string (entity *en, char *s);

extern int get_task_friendly_fire_incidents (entity *task);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





