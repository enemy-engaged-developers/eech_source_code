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

struct VEHICLE
{
	mobile
		mob;

	object_3d_index_numbers
		object_3d_shape;

	object_3d_instance
		*inst3d;

	list_root
		task_dependent_root,
		launched_weapon_root,
		movement_dependent_root;

	list_link
		designated_target_link, // Jabberwock 031107 Designated targets
		follower_link,
		gunship_target_link,
		member_link,
		movement_dependent_link,
		view_link,
		takeoff_queue_link;

	float
		sleep,
		distance,
		loading_door_state,
		radar_rotation_state,
		target_scan_timer,
		target_fire_timer,
		view_interest_level,
		weapon_burst_timer,
		weapon_system_ready_state,
		decoy_release_timer,
		death_timer;

	weapon_config_types
		weapon_config_type;

	weapon_package_status
		*weapon_package_status_array;

	entity_sub_types
		selected_weapon;

	struct SYSTEM_SOUND_EFFECT
		*sound_effect_data;

	unsigned int
		formation_position					:NUM_FORMATION_POSITION_BITS,
		operational_state						:NUM_OPERATIONAL_STATE_BITS,
		selected_weapon_system_ready	  	:NUM_SELECTED_WEAPON_SYSTEM_READY_BITS,
		weapon_and_target_vectors_valid	:NUM_WEAPON_AND_TARGET_VECTORS_VALID_BITS,
		gunship_radar_los_clear				:NUM_GUNSHIP_RADAR_LOS_CLEAR_BITS,
		los_to_target							:NUM_LOS_TO_TARGET_BITS,
		lights_on								:NUM_LIGHTS_ON_BITS,
		cpg_identified							:NUM_CPG_IDENTIFIED_BITS,
		group_member_number					:NUM_GROUP_MEMBER_NUMBER_BITS,
		id_number_significant_digits		:NUM_ID_NUMBER_SIGNIFICANT_DIGIT_BITS;

	int
		damage_level,
		id_number;

	vec3d
		weapon_vector,
		weapon_to_target_vector;

	terrain_3d_point_data
		terrain_info;
};

typedef struct VEHICLE vehicle;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "vh_anim.h"

#include "vh_dbase.h"

#include "vh_float.h"

#include "vh_funcs.h"

#include "vh_int.h"

#include "vh_list.h"

#include "vh_msgs.h"

#include "vh_pack.h"

#include "vh_ptr.h"

#include "vh_str.h"

#include "vh_tgt.h"

#include "vh_vec3d.h"

#include "vh_wpn.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "anti_air/anti_air.h"

#include "person/person.h"

#include "routed/routed.h"

#include "ship/ship.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void play_vehicle_shot_at_speech (entity *victim, entity *aggressor);

extern void play_vehicle_destroyed_speech (entity *victim, entity *aggressor);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





