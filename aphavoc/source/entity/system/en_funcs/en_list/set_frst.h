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

//
// check list integrity
//

ASSERT (en != first_child);

switch (type)
{
	////////////////////////////////////////

	#ifdef LIST_TYPE_AIRCREW_ROOT

	case LIST_TYPE_AIRCREW:
	{
		raw->aircrew_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_AIR_REGISTRY_ROOT

	case LIST_TYPE_AIR_REGISTRY:
	{
		raw->air_registry_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_ASSIGNED_TASK_ROOT

	case LIST_TYPE_ASSIGNED_TASK:
	{
		raw->assigned_task_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_BUILDING_GROUP_ROOT

	case LIST_TYPE_BUILDING_GROUP:
	{
		raw->building_group_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CAMPAIGN_OBJECTIVE_ROOT

	case LIST_TYPE_CAMPAIGN_OBJECTIVE:
	{
		raw->campaign_objective_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CARGO_ROOT

	case LIST_TYPE_CARGO:
	{
		raw->cargo_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CITY_BUILDING_ROOT

	case LIST_TYPE_CITY_BUILDING:
	{
		raw->city_building_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_COMPLETED_TASK_ROOT

	case LIST_TYPE_COMPLETED_TASK:
	{
		raw->completed_task_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CURRENT_WAYPOINT_ROOT

	case LIST_TYPE_CURRENT_WAYPOINT:
	{
		raw->current_waypoint_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	// Jabbewock 031107 Designated targets
		
	#ifdef LIST_TYPE_DESIGNATED_TARGET_ROOT

	case LIST_TYPE_DESIGNATED_TARGET:
	{
		raw->designated_target_root.first_child = first_child;

		break;
	}

	#endif
	
	// Jabbewock 031107 ends

	#ifdef LIST_TYPE_DIVISION_ROOT

	case LIST_TYPE_DIVISION:
	{
		raw->division_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_HEADQUARTERS_ROOT

	case LIST_TYPE_DIVISION_HEADQUARTERS:
	{
		raw->division_headquarters_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FOLLOWER_ROOT

	case LIST_TYPE_FOLLOWER:
	{
		raw->follower_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FORCE_ROOT

	case LIST_TYPE_FORCE:
	{
		raw->force_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GROUND_REGISTRY_ROOT

	case LIST_TYPE_GROUND_REGISTRY:
	{
		raw->ground_registry_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_ROOT

	case LIST_TYPE_GUIDE:
	{
		raw->guide_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_STACK_ROOT

	case LIST_TYPE_GUIDE_STACK:
	{
		raw->guide_stack_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUNSHIP_TARGET_ROOT

	case LIST_TYPE_GUNSHIP_TARGET:
	{
		raw->gunship_target_root.first_child = first_child;

		break;
	}

	#endif
	
	////////////////////////////////////////

	#ifdef LIST_TYPE_INDEPENDENT_GROUP_ROOT

	case LIST_TYPE_INDEPENDENT_GROUP:
	{
		raw->independent_group_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_HIERARCHY_ROOT

	case LIST_TYPE_HIERARCHY:
	{
		raw->hierarchy_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_FORCE_ROOT

	case LIST_TYPE_KEYSITE_FORCE:
	{
		raw->keysite_force_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_GROUP_ROOT

	case LIST_TYPE_KEYSITE_GROUP:
	{
		raw->keysite_group_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LAUNCHED_WEAPON_ROOT

	case LIST_TYPE_LAUNCHED_WEAPON:
	{
		raw->launched_weapon_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LANDING_SITE_ROOT

	case LIST_TYPE_LANDING_SITE:
	{
		raw->landing_site_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MEMBER_ROOT

	case LIST_TYPE_MEMBER:
	{
		raw->member_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MOVEMENT_DEPENDENT_ROOT

	case LIST_TYPE_MOVEMENT_DEPENDENT:
	{
		raw->movement_dependent_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PADLOCK_ROOT

	case LIST_TYPE_PADLOCK:
	{
		raw->padlock_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_ROOT

	case LIST_TYPE_PILOT:
	{
		raw->pilot_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_LOCK_ROOT

	case LIST_TYPE_PILOT_LOCK:
	{
		raw->pilot_lock_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PLAYER_TASK_ROOT

	case LIST_TYPE_PLAYER_TASK:
	{
		raw->player_task_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_REGEN_ROOT

	case LIST_TYPE_REGEN:
	{
		raw->regen_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SEA_REGISTRY_ROOT

	case LIST_TYPE_SEA_REGISTRY:
	{
		raw->sea_registry_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_ROOT

	case LIST_TYPE_SECTOR:
	{
		raw->sector_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_TASK_ROOT

	case LIST_TYPE_SECTOR_TASK:
	{
		raw->sector_task_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SEGMENT_ROOT

	case LIST_TYPE_SEGMENT:
	{
		raw->segment_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SPECIAL_EFFECT_ROOT

	case LIST_TYPE_SPECIAL_EFFECT:
	{
		raw->special_effect_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TAKEOFF_QUEUE_ROOT

	case LIST_TYPE_TAKEOFF_QUEUE:
	{
		raw->takeoff_queue_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TARGET_ROOT

	case LIST_TYPE_TARGET:
	{
		raw->target_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TASK_DEPENDENT_ROOT

	case LIST_TYPE_TASK_DEPENDENT:
	{
		raw->task_dependent_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UNASSIGNED_TASK_ROOT

	case LIST_TYPE_UNASSIGNED_TASK:
	{
		raw->unassigned_task_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UPDATE_ROOT

	case LIST_TYPE_UPDATE:
	{
		raw->update_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_ROOT

	case LIST_TYPE_VIEW:
	{
		raw->view_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_WEAPON_ROOT

	case LIST_TYPE_VIEW_WEAPON:
	{
		raw->view_weapon_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_WAYPOINT_ROOT

	case LIST_TYPE_WAYPOINT:
	{
		raw->waypoint_root.first_child = first_child;

		break;
	}

	#endif

	////////////////////////////////////////

	default:
	{
		debug_fatal_invalid_list_type (en, type);

		break;
	}

	////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

