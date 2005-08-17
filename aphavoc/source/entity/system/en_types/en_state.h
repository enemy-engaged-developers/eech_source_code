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

enum OPERATIONAL_STATE_TYPES
{

	OPERATIONAL_STATE_UNKNOWN,
	OPERATIONAL_STATE_ASLEEP,
	OPERATIONAL_STATE_DEAD,
	OPERATIONAL_STATE_DYING,
	OPERATIONAL_STATE_LANDED,
	OPERATIONAL_STATE_LANDING,
	OPERATIONAL_STATE_LANDING_HOLDING,
	OPERATIONAL_STATE_NAVIGATING,
	OPERATIONAL_STATE_STOPPED,
	OPERATIONAL_STATE_TAKEOFF,
	OPERATIONAL_STATE_TAKEOFF_HOLDING,
	OPERATIONAL_STATE_TAXIING,
	OPERATIONAL_STATE_WAITING,
	NUM_OPERATIONAL_STATE_TYPES
};

typedef enum OPERATIONAL_STATE_TYPES operational_state_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum VERBOSE_OPERATIONAL_STATES
{

	VERBOSE_OPERATIONAL_STATE_UNKNOWN,
	VERBOSE_OPERATIONAL_STATE_AIR_PATROL,
	VERBOSE_OPERATIONAL_STATE_APPROACHING_TARGET,
	VERBOSE_OPERATIONAL_STATE_APPROACHING_WAYPOINT,
	VERBOSE_OPERATIONAL_STATE_AWAITING_LANDING_CLEARANCE,
	VERBOSE_OPERATIONAL_STATE_AWAITING_TAKEOFF_CLEARANCE,
	VERBOSE_OPERATIONAL_STATE_ENGAGING_TARGET,
	VERBOSE_OPERATIONAL_STATE_EN_ROUTE,
	VERBOSE_OPERATIONAL_STATE_EN_ROUTE_TO_TARGET,
	VERBOSE_OPERATIONAL_STATE_HOLDING,
	VERBOSE_OPERATIONAL_STATE_LANDING,
	VERBOSE_OPERATIONAL_STATE_MANOEUVRING,
	VERBOSE_OPERATIONAL_STATE_PERFORMING_RECON,
	VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,
	VERBOSE_OPERATIONAL_STATE_PREPARING_FOR_TAKEOFF,
	VERBOSE_OPERATIONAL_STATE_REARMING,
	VERBOSE_OPERATIONAL_STATE_REFUELING,
	VERBOSE_OPERATIONAL_STATE_REPAIRING,
	VERBOSE_OPERATIONAL_STATE_RETURING_TO_BASE,
	VERBOSE_OPERATIONAL_STATE_SEARCHING_FOR_TARGET,
	VERBOSE_OPERATIONAL_STATE_TAKEOFF,
	VERBOSE_OPERATIONAL_STATE_TAXIING,
	VERBOSE_OPERATIONAL_STATE_WAITING,
	NUM_VERBOSE_OPERATIONAL_STATES
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GROUP_MEMBER_STATE_TYPES
{
	GROUP_MEMBER_STATE_IDLE,
	GROUP_MEMBER_STATE_WAITING,
	GROUP_MEMBER_STATE_TAKING_OFF,
	GROUP_MEMBER_STATE_NAVIGATING,
	GROUP_MEMBER_STATE_ATTACKING,
	GROUP_MEMBER_STATE_RETURNING,
	GROUP_MEMBER_STATE_LANDING,

	NUM_GROUP_MEMBER_STATE_TYPES
};

typedef enum GROUP_MEMBER_STATE_TYPES group_member_state_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum KEYSITE_USABLE_STATES
{
	KEYSITE_STATE_USABLE,
	KEYSITE_STATE_UNUSABLE,
	KEYSITE_STATE_REPAIRING,

	NUM_KEYSITE_USABLE_STATES
};

typedef enum KEYSITE_USABLE_STATES keysite_usable_states;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*operational_state_names [],
	*verbose_operational_state_names [],
	*group_member_state_names [],
	*keysite_usable_state_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

