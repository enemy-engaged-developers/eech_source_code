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
		parent = raw->aircrew_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_ASSIGNED_TASK_LINK

	case LIST_TYPE_ASSIGNED_TASK:
	{
		parent = raw->task_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CAMPAIGN_OBJECTIVE_LINK

	case LIST_TYPE_CAMPAIGN_OBJECTIVE:
	{
		parent = raw->campaign_objective_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CARGO_LINK

	case LIST_TYPE_CARGO:
	{
		parent = raw->cargo_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CITY_BUILDING_LINK

	case LIST_TYPE_CITY_BUILDING:
	{
		parent = raw->city_building_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_COMPLETED_TASK_LINK

	case LIST_TYPE_COMPLETED_TASK:
	{
		parent = raw->task_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_CURRENT_WAYPOINT_LINK

	case LIST_TYPE_CURRENT_WAYPOINT:
	{
		parent = raw->current_waypoint_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	// Jabbewock 031107 Designated targets
	
	#ifdef LIST_TYPE_DESIGNATED_TARGET_LINK

	case LIST_TYPE_DESIGNATED_TARGET:
	{
		parent = raw->designated_target_link.parent;

		break;
	}

	#endif

	// Jabbewock 031107 ends

	#ifdef LIST_TYPE_DIVISION_LINK

	case LIST_TYPE_DIVISION:
	{
		parent = raw->division_link.parent;

		break;
	}

	#endif
	
	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_HEADQUARTERS_LINK

	case LIST_TYPE_DIVISION_HEADQUARTERS:
	{
		parent = raw->division_headquarters_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FOLLOWER_LINK

	case LIST_TYPE_FOLLOWER:
	{
		parent = raw->follower_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_FORCE_LINK

	case LIST_TYPE_FORCE:
	{
		parent = raw->force_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GROUP_LINK

	case LIST_TYPE_BUILDING_GROUP:
	case LIST_TYPE_INDEPENDENT_GROUP:
	case LIST_TYPE_KEYSITE_GROUP:
	{
		parent = raw->group_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_LINK

	case LIST_TYPE_GUIDE:
	{
		parent = raw->guide_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_STACK_LINK

	case LIST_TYPE_GUIDE_STACK:
	{
		parent = raw->guide_stack_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_GUNSHIP_TARGET_LINK

	case LIST_TYPE_GUNSHIP_TARGET:
	{
		parent = raw->gunship_target_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_HIERARCHY_LINK

	case LIST_TYPE_HIERARCHY:
	{
		parent = raw->hierarchy_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_FORCE_LINK

	case LIST_TYPE_KEYSITE_FORCE:
	{
		parent = raw->keysite_force_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LAUNCHED_WEAPON_LINK

	case LIST_TYPE_LAUNCHED_WEAPON:
	{
		parent = raw->launched_weapon_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_LANDING_SITE_LINK

	case LIST_TYPE_LANDING_SITE:
	{
		parent = raw->landing_site_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MEMBER_LINK

	case LIST_TYPE_MEMBER:
	{
		parent = raw->member_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_MOVEMENT_DEPENDENT_LINK

	case LIST_TYPE_MOVEMENT_DEPENDENT:
	{
		parent = raw->movement_dependent_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PADLOCK_LINK

	case LIST_TYPE_PADLOCK:
	{
		parent = raw->padlock_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_LINK

	case LIST_TYPE_PILOT:
	{
		parent = raw->pilot_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_LOCK_LINK

	case LIST_TYPE_PILOT_LOCK:
	{
		parent = raw->pilot_lock_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_PLAYER_TASK_LINK

	case LIST_TYPE_PLAYER_TASK:
	{
		parent = raw->player_task_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_REGEN_LINK

	case LIST_TYPE_REGEN:
	{
		parent = raw->regen_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_REGISTRY_LINK

	case LIST_TYPE_AIR_REGISTRY:
	case LIST_TYPE_GROUND_REGISTRY:
	case LIST_TYPE_SEA_REGISTRY:
	{
		parent = raw->registry_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_LINK

	case LIST_TYPE_SECTOR:
	{
		parent = raw->sector_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_TASK_LINK

	case LIST_TYPE_SECTOR_TASK:
	{
		parent = raw->sector_task_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SEGMENT_LINK

	case LIST_TYPE_SEGMENT:
	{
		parent = raw->segment_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_SPECIAL_EFFECT_LINK

	case LIST_TYPE_SPECIAL_EFFECT:
	{
		parent = raw->special_effect_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TAKEOFF_QUEUE_LINK

	case LIST_TYPE_TAKEOFF_QUEUE:
	{
		parent = raw->takeoff_queue_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TARGET_LINK

	case LIST_TYPE_TARGET:
	{
		parent = raw->target_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_TASK_DEPENDENT_LINK

	case LIST_TYPE_TASK_DEPENDENT:
	{
		parent = raw->task_dependent_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UNASSIGNED_TASK_LINK

	case LIST_TYPE_UNASSIGNED_TASK:
	{
		parent = raw->task_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_UPDATE_LINK

	case LIST_TYPE_UPDATE:
	{
		parent = raw->update_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_LINK

	case LIST_TYPE_VIEW:
	{
		parent = raw->view_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_WEAPON_LINK

	case LIST_TYPE_VIEW_WEAPON:
	{
		parent = raw->view_weapon_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	#ifdef LIST_TYPE_WAYPOINT_LINK

	case LIST_TYPE_WAYPOINT:
	{
		parent = raw->waypoint_link.parent;

		break;
	}

	#endif

	////////////////////////////////////////

	default:
	{
		debug_fatal_invalid_list_type (en, type);

		parent = NULL;

		break;
	}

	////////////////////////////////////////
}

//
// check list integrity
//

ASSERT (en != parent);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

