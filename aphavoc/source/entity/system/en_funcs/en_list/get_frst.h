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

switch (type)
{
	////////////////////////////////////////

	#ifdef LIST_TYPE_AIRCREW_ROOT

	case LIST_TYPE_AIRCREW:
	{
		first_child = raw->aircrew_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_AIR_REGISTRY_ROOT

	case LIST_TYPE_AIR_REGISTRY:
	{
		first_child = raw->air_registry_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_ASSIGNED_TASK_ROOT

	case LIST_TYPE_ASSIGNED_TASK:
	{
		first_child = raw->assigned_task_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_BUILDING_GROUP_ROOT

	case LIST_TYPE_BUILDING_GROUP:
	{
		first_child = raw->building_group_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CAMPAIGN_OBJECTIVE_ROOT

	case LIST_TYPE_CAMPAIGN_OBJECTIVE:
	{
		first_child = raw->campaign_objective_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CARGO_ROOT

	case LIST_TYPE_CARGO:
	{
		first_child = raw->cargo_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CITY_BUILDING_ROOT

	case LIST_TYPE_CITY_BUILDING:
	{
		first_child = raw->city_building_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_COMPLETED_TASK_ROOT

	case LIST_TYPE_COMPLETED_TASK:
	{
		first_child = raw->completed_task_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CURRENT_WAYPOINT_ROOT

	case LIST_TYPE_CURRENT_WAYPOINT:
	{
		first_child = raw->current_waypoint_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_ROOT

	case LIST_TYPE_DIVISION:
	{
		first_child = raw->division_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_HEADQUARTERS_ROOT

	case LIST_TYPE_DIVISION_HEADQUARTERS:
	{
		first_child = raw->division_headquarters_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FOLLOWER_ROOT

	case LIST_TYPE_FOLLOWER:
	{
		first_child = raw->follower_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FORCE_ROOT

	case LIST_TYPE_FORCE:
	{
		first_child = raw->force_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GROUND_REGISTRY_ROOT

	case LIST_TYPE_GROUND_REGISTRY:
	{
		first_child = raw->ground_registry_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_ROOT

	case LIST_TYPE_GUIDE:
	{
		first_child = raw->guide_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_STACK_ROOT

	case LIST_TYPE_GUIDE_STACK:
	{
		first_child = raw->guide_stack_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUNSHIP_TARGET_ROOT

	case LIST_TYPE_GUNSHIP_TARGET:
	{
		first_child = raw->gunship_target_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_INDEPENDENT_GROUP_ROOT

	case LIST_TYPE_INDEPENDENT_GROUP:
	{
		first_child = raw->independent_group_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_HIERARCHY_ROOT

	case LIST_TYPE_HIERARCHY:
	{
		first_child = raw->hierarchy_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_FORCE_ROOT

	case LIST_TYPE_KEYSITE_FORCE:
	{
		first_child = raw->keysite_force_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_GROUP_ROOT

	case LIST_TYPE_KEYSITE_GROUP:
	{
		first_child = raw->keysite_group_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LAUNCHED_WEAPON_ROOT

	case LIST_TYPE_LAUNCHED_WEAPON:
	{
		first_child = raw->launched_weapon_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LANDING_SITE_ROOT

	case LIST_TYPE_LANDING_SITE:
	{
		first_child = raw->landing_site_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MEMBER_ROOT

	case LIST_TYPE_MEMBER:
	{
		first_child = raw->member_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MOVEMENT_DEPENDENT_ROOT

	case LIST_TYPE_MOVEMENT_DEPENDENT:
	{
		first_child = raw->movement_dependent_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PADLOCK_ROOT

	case LIST_TYPE_PADLOCK:
	{
		first_child = raw->padlock_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_ROOT

	case LIST_TYPE_PILOT:
	{
		first_child = raw->pilot_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_LOCK_ROOT

	case LIST_TYPE_PILOT_LOCK:
	{
		first_child = raw->pilot_lock_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PLAYER_TASK_ROOT

	case LIST_TYPE_PLAYER_TASK:
	{
		first_child = raw->player_task_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_REGEN_ROOT

	case LIST_TYPE_REGEN:
	{
		first_child = raw->regen_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SEA_REGISTRY_ROOT

	case LIST_TYPE_SEA_REGISTRY:
	{
		first_child = raw->sea_registry_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_ROOT

	case LIST_TYPE_SECTOR:
	{
		first_child = raw->sector_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_TASK_ROOT

	case LIST_TYPE_SECTOR_TASK:
	{
		first_child = raw->sector_task_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SEGMENT_ROOT

	case LIST_TYPE_SEGMENT:
	{
		first_child = raw->segment_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SPECIAL_EFFECT_ROOT

	case LIST_TYPE_SPECIAL_EFFECT:
	{
		first_child = raw->special_effect_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TAKEOFF_QUEUE_ROOT

	case LIST_TYPE_TAKEOFF_QUEUE:
	{
		first_child = raw->takeoff_queue_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TARGET_ROOT

	case LIST_TYPE_TARGET:
	{
		first_child = raw->target_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TASK_DEPENDENT_ROOT

	case LIST_TYPE_TASK_DEPENDENT:
	{
		first_child = raw->task_dependent_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UNASSIGNED_TASK_ROOT

	case LIST_TYPE_UNASSIGNED_TASK:
	{
		first_child = raw->unassigned_task_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UPDATE_ROOT

	case LIST_TYPE_UPDATE:
	{
		first_child = raw->update_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_ROOT

	case LIST_TYPE_VIEW:
	{
		first_child = raw->view_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_WEAPON_ROOT

	case LIST_TYPE_VIEW_WEAPON:
	{
		first_child = raw->view_weapon_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_WAYPOINT_ROOT

	case LIST_TYPE_WAYPOINT:
	{
		first_child = raw->waypoint_root.first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	default:
	{
		debug_fatal_invalid_list_type (en, type);

		first_child = NULL;

		break;
	}

	////////////////////////////////////////
}

//
// check list integrity
//

ASSERT (en != first_child);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

