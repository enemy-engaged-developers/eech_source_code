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

struct TASK_DATA
{
	////////////////////////////////////////
	//
	// names
	//
	////////////////////////////////////////

	const char
		*full_name,
		*short_name,
		*key;

	task_category_types
		task_category;

	float
		task_priority;

	int
		difficulty_rating;

	unsigned int
		task_default_target_class	: NUM_TASK_TARGET_CLASS_BITS,
		task_default_target_source	: NUM_TASK_TARGET_SOURCE_BITS,
		task_default_target_type	: NUM_TASK_TARGET_TYPE_BITS,
		task_objective_info			: 2,
		minimum_member_count			: 4,
		rules_of_engagement			: NUM_TASK_ROE_TYPE_BITS,
		engage_enemy					: 1,
		escort_required_threshold	: 4;

	sys_colours
		waypoint_route_colour;

	unsigned int
		add_start_waypoint				: 1,
		primary_task						: 1,
		solo_task							: 1,
		persistent_task					: 1,
		visible_task						: 1,
		keysite_air_force_capacity		: 2,
		assess_landing						: 1,
		task_route_search					: 1,
		perform_debrief					: 1,
		delay_task_assignment			: 1,
		task_objective_preview			: 2,
		counts_towards_player_log		: 1,
		wait_for_end_task					: 1,
		player_reserve_factor			: 3;

	unsigned int
		task_pass_percentage_partial	: 7,
		task_pass_percentage_success	: 7,
		task_completed_score				: 16;

	movement_types
		movement_type;

	int
		landing_types;

	////////////////////////////////////////
	//
	// AI Statistics
	//
	////////////////////////////////////////

	ai_statistics
		ai_stats;
};

typedef struct TASK_DATA task_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition
extern task_data
	task_database[NUM_ENTITY_SUB_TYPE_TASKS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ESCORT_NEVER 15

#define ESCORT_CRITICAL 6

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

