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

{
	////////////////////////////////////////
	//
	// LIST_TYPE_AIRCREW
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_AIRCREW_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_AIRCREW]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_AIRCREW]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_AIRCREW_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_AIRCREW]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_AIRCREW]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_AIRCREW]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_AIRCREW]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_AIRCREW]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_AIRCREW]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_AIR_REGISTRY
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_AIR_REGISTRY_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= get_local_first_child;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_ASSIGNED_TASK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_ASSIGNED_TASK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_ASSIGNED_TASK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_ASSIGNED_TASK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_BUILDING_GROUP
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_BUILDING_GROUP_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_GROUP_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_BUILDING_GROUP]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_CAMPAIGN_OBJECTIVE
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_CAMPAIGN_OBJECTIVE_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_CAMPAIGN_OBJECTIVE_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_CAMPAIGN_OBJECTIVE]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_CARGO
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_CARGO_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_CARGO]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_CARGO]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_CARGO_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_CARGO]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_CARGO]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_CARGO]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_CARGO]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_CARGO]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_CARGO]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_CITY_BUILDING
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_CITY_BUILDING_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_CITY_BUILDING]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_CITY_BUILDING]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_CITY_BUILDING_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_CITY_BUILDING]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_CITY_BUILDING]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_CITY_BUILDING]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_CITY_BUILDING]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_CITY_BUILDING]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_CITY_BUILDING]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_COMPLETED_TASK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_COMPLETED_TASK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_COMPLETED_TASK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_COMPLETED_TASK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_CURRENT_WAYPOINT
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_CURRENT_WAYPOINT_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_CURRENT_WAYPOINT_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_CURRENT_WAYPOINT]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_DIVISION
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_DIVISION]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_DIVISION]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_DIVISION_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_DIVISION]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_DIVISION]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_DIVISION]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_DIVISION]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_DIVISION]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_DIVISION]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_DIVISION_HEADQUARTERS
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_DIVISION_HEADQUARTERS_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_DIVISION_HEADQUARTERS_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_DIVISION_HEADQUARTERS]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_FOLLOWER
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_FOLLOWER_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_FOLLOWER]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_FOLLOWER]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_FOLLOWER_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_FOLLOWER]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_FOLLOWER]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_FOLLOWER]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_FOLLOWER]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_FOLLOWER]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_FOLLOWER]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_FORCE
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_FORCE_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_FORCE]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_FORCE]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_FORCE_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_FORCE]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_FORCE]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_FORCE]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_FORCE]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_FORCE]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_FORCE]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_GROUND_REGISTRY
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_GROUND_REGISTRY_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= get_local_first_child;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_GUIDE
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_GUIDE]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_GUIDE]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_GUIDE_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_GUIDE]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_GUIDE]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_GUIDE]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_GUIDE]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_GUIDE]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_GUIDE]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_GUIDE_STACK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_GUIDE_STACK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_GUIDE_STACK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_GUIDE_STACK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_GUIDE_STACK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_GUIDE_STACK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_GUIDE_STACK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_GUIDE_STACK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_GUIDE_STACK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_GUIDE_STACK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_GUIDE_STACK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_GUNSHIP_TARGET
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_GUNSHIP_TARGET_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_GUNSHIP_TARGET_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_GUNSHIP_TARGET]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_HIERARCHY
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_HIERARCHY_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_HIERARCHY]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_HIERARCHY]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_HIERARCHY_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_HIERARCHY]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_HIERARCHY]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_HIERARCHY]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_HIERARCHY]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_HIERARCHY]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_HIERARCHY]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_INDEPENDENT_GROUP
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_INDEPENDENT_GROUP_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_GROUP_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_INDEPENDENT_GROUP]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_KEYSITE_FORCE
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_FORCE_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_KEYSITE_FORCE_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_KEYSITE_FORCE]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_KEYSITE_GROUP
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_KEYSITE_GROUP_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_GROUP_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_KEYSITE_GROUP]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_LAUNCHED_WEAPON
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_LAUNCHED_WEAPON_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_LAUNCHED_WEAPON_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_LAUNCHED_WEAPON]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_LANDING_SITE
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_LANDING_SITE_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_LANDING_SITE]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_LANDING_SITE]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_LANDING_SITE_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_LANDING_SITE]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_LANDING_SITE]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_LANDING_SITE]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_LANDING_SITE]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_LANDING_SITE]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_LANDING_SITE]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_MEMBER
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_MEMBER_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_MEMBER]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_MEMBER]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_MEMBER_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_MEMBER]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_MEMBER]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_MEMBER]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_MEMBER]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_MEMBER]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_MEMBER]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_MOVEMENT_DEPENDENT
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_MOVEMENT_DEPENDENT_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_MOVEMENT_DEPENDENT_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_MOVEMENT_DEPENDENT]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_PADLOCK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_PADLOCK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_PADLOCK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_PADLOCK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_PADLOCK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_PADLOCK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_PADLOCK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_PADLOCK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_PADLOCK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_PADLOCK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_PADLOCK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_PILOT
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_PILOT]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_PILOT]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_PILOT_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_PILOT]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_PILOT]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_PILOT]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_PILOT]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_PILOT]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_PILOT]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_PILOT_LOCK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_PILOT_LOCK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_PILOT_LOCK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_PILOT_LOCK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_PILOT_LOCK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_PILOT_LOCK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_PILOT_LOCK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_PILOT_LOCK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_PILOT_LOCK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_PILOT_LOCK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_PILOT_LOCK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_PLAYER_TASK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_PLAYER_TASK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_PLAYER_TASK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_PLAYER_TASK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_PLAYER_TASK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_PLAYER_TASK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_PLAYER_TASK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_PLAYER_TASK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_PLAYER_TASK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_PLAYER_TASK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_PLAYER_TASK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_REGEN
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_REGEN_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_REGEN]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_REGEN]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_REGEN_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_REGEN]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_REGEN]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_REGEN]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_REGEN]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_REGEN]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_REGEN]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_REGISTRY (AIR, FREE, GROUND and SEA)
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_REGISTRY_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_AIR_REGISTRY]	= get_local_child_pred;

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_GROUND_REGISTRY]	= get_local_child_pred;

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_SEA_REGISTRY
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_SEA_REGISTRY_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_SEA_REGISTRY]	= get_local_first_child;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_SECTOR
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_SECTOR]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_SECTOR]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_SECTOR_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_SECTOR]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_SECTOR]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_SECTOR]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_SECTOR]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_SECTOR]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_SECTOR]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_SECTOR_TASK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_SECTOR_TASK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_SECTOR_TASK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_SECTOR_TASK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_SECTOR_TASK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_SECTOR_TASK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_SECTOR_TASK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_SECTOR_TASK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_SECTOR_TASK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_SECTOR_TASK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_SECTOR_TASK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_SEGMENT
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_SEGMENT_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_SEGMENT]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_SEGMENT]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_SEGMENT_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_SEGMENT]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_SEGMENT]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_SEGMENT]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_SEGMENT]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_SEGMENT]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_SEGMENT]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_SPECIAL_EFFECT
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_SPECIAL_EFFECT_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_SPECIAL_EFFECT_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_SPECIAL_EFFECT]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_TAKEOFF_QUEUE
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_TAKEOFF_QUEUE_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_TAKEOFF_QUEUE_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_TAKEOFF_QUEUE]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_TARGET
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_TARGET_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_TARGET]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_TARGET]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_TARGET_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_TARGET]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_TARGET]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_TARGET]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_TARGET]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_TARGET]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_TARGET]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_TASK_DEPENDENT
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_TASK_DEPENDENT_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_TASK_DEPENDENT_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_TASK_DEPENDENT]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_UNASSIGNED_TASK
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_UNASSIGNED_TASK_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_UNASSIGNED_TASK_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_UNASSIGNED_TASK]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_UPDATE
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_UPDATE_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_UPDATE]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_UPDATE]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_UPDATE_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_UPDATE]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_UPDATE]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_UPDATE]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_UPDATE]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_UPDATE]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_UPDATE]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_VIEW
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_VIEW]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_VIEW]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_VIEW_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_VIEW]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_VIEW]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_VIEW]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_VIEW]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_VIEW]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_VIEW]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_VIEW_WEAPON
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_VIEW_WEAPON_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_VIEW_WEAPON_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_VIEW_WEAPON]	= get_local_child_pred;

	#endif

	////////////////////////////////////////
	//
	// LIST_TYPE_WAYPOINT
	//
	////////////////////////////////////////

	#ifdef LIST_TYPE_WAYPOINT_ROOT

	fn_set_local_entity_first_child	[(TYPE)][LIST_TYPE_WAYPOINT]	= set_local_first_child;

	fn_get_local_entity_first_child	[(TYPE)][LIST_TYPE_WAYPOINT]	= get_local_first_child;

	#endif

	#ifdef LIST_TYPE_WAYPOINT_LINK

	fn_set_local_entity_parent			[(TYPE)][LIST_TYPE_WAYPOINT]	= set_local_parent;

	fn_get_local_entity_parent			[(TYPE)][LIST_TYPE_WAYPOINT]	= get_local_parent;

	fn_set_local_entity_child_succ	[(TYPE)][LIST_TYPE_WAYPOINT]	= set_local_child_succ;

	fn_get_local_entity_child_succ	[(TYPE)][LIST_TYPE_WAYPOINT]	= get_local_child_succ;

	fn_set_local_entity_child_pred	[(TYPE)][LIST_TYPE_WAYPOINT]	= set_local_child_pred;

	fn_get_local_entity_child_pred	[(TYPE)][LIST_TYPE_WAYPOINT]	= get_local_child_pred;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




