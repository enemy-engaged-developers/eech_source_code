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

	#ifdef LIST_TYPE_AIRCREW_LINK

	case LIST_TYPE_AIRCREW:
	{
		child_succ = raw->aircrew_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_ASSIGNED_TASK_LINK

	case LIST_TYPE_ASSIGNED_TASK:
	{
		child_succ = raw->task_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CAMPAIGN_OBJECTIVE_LINK

	case LIST_TYPE_CAMPAIGN_OBJECTIVE:
	{
		child_succ = raw->campaign_objective_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CARGO_LINK

	case LIST_TYPE_CARGO:
	{
		child_succ = raw->cargo_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CITY_BUILDING_LINK

	case LIST_TYPE_CITY_BUILDING:
	{
		child_succ = raw->city_building_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_COMPLETED_TASK_LINK

	case LIST_TYPE_COMPLETED_TASK:
	{
		child_succ = raw->task_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CURRENT_WAYPOINT_LINK

	case LIST_TYPE_CURRENT_WAYPOINT:
	{
		child_succ = raw->current_waypoint_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_LINK

	case LIST_TYPE_DIVISION:
	{
		child_succ = raw->division_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_HEADQUARTERS_LINK

	case LIST_TYPE_DIVISION_HEADQUARTERS:
	{
		child_succ = raw->division_headquarters_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FOLLOWER_LINK

	case LIST_TYPE_FOLLOWER:
	{
		child_succ = raw->follower_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FORCE_LINK

	case LIST_TYPE_FORCE:
	{
		child_succ = raw->force_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GROUP_LINK

	case LIST_TYPE_BUILDING_GROUP:
	case LIST_TYPE_INDEPENDENT_GROUP:
	case LIST_TYPE_KEYSITE_GROUP:
	{
		child_succ = raw->group_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_LINK

	case LIST_TYPE_GUIDE:
	{
		child_succ = raw->guide_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_STACK_LINK

	case LIST_TYPE_GUIDE_STACK:
	{
		child_succ = raw->guide_stack_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUNSHIP_TARGET_LINK

	case LIST_TYPE_GUNSHIP_TARGET:
	{
		child_succ = raw->gunship_target_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_HIERARCHY_LINK

	case LIST_TYPE_HIERARCHY:
	{
		child_succ = raw->hierarchy_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_FORCE_LINK

	case LIST_TYPE_KEYSITE_FORCE:
	{
		child_succ = raw->keysite_force_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LAUNCHED_WEAPON_LINK

	case LIST_TYPE_LAUNCHED_WEAPON:
	{
		child_succ = raw->launched_weapon_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LANDING_SITE_LINK

	case LIST_TYPE_LANDING_SITE:
	{
		child_succ = raw->landing_site_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MEMBER_LINK

	case LIST_TYPE_MEMBER:
	{
		child_succ = raw->member_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MOVEMENT_DEPENDENT_LINK

	case LIST_TYPE_MOVEMENT_DEPENDENT:
	{
		child_succ = raw->movement_dependent_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PADLOCK_LINK

	case LIST_TYPE_PADLOCK:
	{
		child_succ = raw->padlock_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_LINK

	case LIST_TYPE_PILOT:
	{
		child_succ = raw->pilot_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_LOCK_LINK

	case LIST_TYPE_PILOT_LOCK:
	{
		child_succ = raw->pilot_lock_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PLAYER_TASK_LINK

	case LIST_TYPE_PLAYER_TASK:
	{
		child_succ = raw->player_task_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_REGEN_LINK

	case LIST_TYPE_REGEN:
	{
		child_succ = raw->regen_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_REGISTRY_LINK

	case LIST_TYPE_AIR_REGISTRY:
	case LIST_TYPE_GROUND_REGISTRY:
	case LIST_TYPE_SEA_REGISTRY:
	{
		child_succ = raw->registry_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_LINK

	case LIST_TYPE_SECTOR:
	{
		child_succ = raw->sector_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_TASK_LINK

	case LIST_TYPE_SECTOR_TASK:
	{
		child_succ = raw->sector_task_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SEGMENT_LINK

	case LIST_TYPE_SEGMENT:
	{
		child_succ = raw->segment_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SPECIAL_EFFECT_LINK

	case LIST_TYPE_SPECIAL_EFFECT:
	{
		child_succ = raw->special_effect_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TAKEOFF_QUEUE_LINK

	case LIST_TYPE_TAKEOFF_QUEUE:
	{
		child_succ = raw->takeoff_queue_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TARGET_LINK

	case LIST_TYPE_TARGET:
	{
		child_succ = raw->target_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TASK_DEPENDENT_LINK

	case LIST_TYPE_TASK_DEPENDENT:
	{
		child_succ = raw->task_dependent_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UNASSIGNED_TASK_LINK

	case LIST_TYPE_UNASSIGNED_TASK:
	{
		child_succ = raw->task_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UPDATE_LINK

	case LIST_TYPE_UPDATE:
	{
		child_succ = raw->update_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_LINK

	case LIST_TYPE_VIEW:
	{
		child_succ = raw->view_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_WEAPON_LINK

	case LIST_TYPE_VIEW_WEAPON:
	{
		child_succ = raw->view_weapon_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_WAYPOINT_LINK

	case LIST_TYPE_WAYPOINT:
	{
		child_succ = raw->waypoint_link.child_succ;

		break;
	}

	#endif

	////////////////////////////////////////

	default:
	{
		debug_fatal_invalid_list_type (en, type);

		child_succ = NULL;

		break;
	}

	////////////////////////////////////////
}

//
// check list integrity
//

ASSERT (en != child_succ);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

