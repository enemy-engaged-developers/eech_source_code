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

#include "assign.h"

#include "croute.h"

#include "engage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_ROUTE_NODES 			(32)

#define TASK_ASSIGN_NO_MEMBERS	(0)
#define TASK_ASSIGN_ALL_MEMBERS	(0xffffffff)

#define TASK_THREAD 					0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern vec3d
	terminator_point;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity *create_task
						(
							entity_sub_types sub_type,
							entity_sides side,
							movement_types movement_type,
							entity *start_keysite,
							entity *end_keysite,
							entity *originator,
							int critical_task,
							float expire_timer,
							float stop_timer,
							entity *task_objective,
							float task_priority,
							...
						);

extern entity *create_anti_ship_strike_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_bai_task (entity_sides side, entity *target_group, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_barcap_task (entity_sides side, entity *this_keysite, entity *originator, int critical, vec3d *centre_position, float priority, float duration, entity *start_keysite, entity *end_keysite);

extern entity *create_bda_task (entity_sides side, entity *objective, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_cap_task (entity_sides side, entity *this_keysite, entity *originator, int critical, float priority, float duration, entity *start_keysite, entity *end_keysite);

extern entity *create_close_air_support_task (entity_sides side, entity *target_group, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_coastal_patrol_task (entity_sides side, vec3d *source_position, vec3d *destination_position, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_escort_task (entity *group, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_ground_force_task (entity_sub_types type, entity *group, int from_node, int to_node, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_ground_strike_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_oca_strike_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_oca_sweep_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_recon_task (entity_sides side, entity *objective, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_repair_task (entity_sides side, vec3d *pos, entity *objective, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_sead_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_supply_task (entity *requester, entity *supplier, entity *cargo, movement_types movement_type, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_transfer_task (entity_sides side, entity_sub_types task_type, float priority, entity *start_keysite, entity *end_keysite, int emergency);

extern entity *create_troop_insertion_task (entity_sides side, entity *destination_keysite, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite);

extern entity *create_troop_movement_capture_task (entity_sides side, vec3d *start_pos, entity *insert_task, entity *keysite, entity *helicopter);

extern entity *create_troop_movement_defend_task (entity_sides side, vec3d *start_pos, vec3d *mid_pos, vec3d *end_pos, entity *insert_task, entity *keysite);

extern entity *create_troop_movement_patrol_task (entity_sides side, vec3d *start_pos, float radius, entity *keysite);

extern entity *create_user_task (entity *en, entity_sub_types type, vec3d *start_pos, entity *start_keysite, entity *end_keysite);

// creation tools

extern float get_estimated_task_duration (entity *task);

extern int validate_task_generation (entity_sides side, entity_sub_types sub_type);

extern void display_task_generation_stats (entity *force_en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



