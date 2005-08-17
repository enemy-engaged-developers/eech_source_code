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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FORCE
{
	char
		force_name [STRING_TYPE_FORCE_NAME_MAX_LENGTH + 1];

	list_root
		keysite_force_root,
		independent_group_root,
		pilot_root,
		division_root,
		campaign_objective_root,

		air_registry_root,
		ground_registry_root,
		sea_registry_root;

	list_link
		force_link,
		update_link;

	task_generation_type
		task_generation [NUM_ENTITY_SUB_TYPE_TASKS];

	campaign_criteria_type
		*campaign_criteria;

	int
		force_info_current_hardware [NUM_FORCE_INFO_CATAGORIES],
		force_info_reserve_hardware [NUM_FORCE_INFO_CATAGORIES];

	int
		kills [NUM_ENTITY_SUB_TYPE_GROUPS],
		losses [NUM_ENTITY_SUB_TYPE_GROUPS],
		group_count [NUM_ENTITY_SUB_TYPE_GROUPS];

	int
		sector_count;

	float
		sleep;

	unsigned int
		force_attitude				: NUM_FORCE_ATTITUDE_BITS,
		colour 						: NUM_COLOUR_BITS,
		side							: NUM_SIDE_BITS;
};

typedef struct FORCE force;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "fc_creat.h"

#include "fc_dstry.h"

#include "fc_float.h"

#include "fc_funcs.h"

#include "fc_int.h"

#include "fc_list.h"

#include "fc_msgs.h"

#include "fc_pack.h"

#include "fc_str.h"

#include "fc_updt.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	force_hardware_update;

#define set_force_hardware_update(FLAG) (force_hardware_update = (FLAG))

#define get_force_hardware_update() (force_hardware_update)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity *get_local_force_entity (entity_sides side);

extern void add_to_force_info (entity *force_en, entity *new_en);

extern void remove_from_force_info (entity *force_en, entity *new_en);

extern int get_force_space (entity *force_en, force_info_catagories force_info_catagory);

extern void replace_into_force_info (entity *force_en, entity *new_en);

extern void add_mobile_to_force_kills_stats (entity *en, entity *victim);

extern void add_mobile_to_force_losses_stats (entity *en, entity *victim);

extern void add_group_type_to_force_info (entity *en, entity_sub_types group_type);

extern void remove_group_type_from_force_info (entity *en, entity_sub_types group_type);

extern int get_local_force_entity_group_count (entity *en, entity_sub_types group_type);

extern void display_campaign_criteria_time_remaining (void);

extern void set_display_campaign_timer_valid (int valid);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
