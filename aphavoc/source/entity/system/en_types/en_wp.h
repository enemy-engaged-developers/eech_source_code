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

enum POSITION_TYPES
{

	POSITION_TYPE_ABSOLUTE,
	POSITION_TYPE_RELATIVE,
	POSITION_TYPE_VIRTUAL,
	NUM_POSITION_TYPES
};

typedef enum POSITION_TYPES position_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum WAYPOINT_REACHED_TYPES
{

	WAYPOINT_REACHED_FALSE,
	WAYPOINT_REACHED_FALSE_HEADING,
	WAYPOINT_REACHED_FALSE_ABOVE_ALTITUDE,
	WAYPOINT_REACHED_FALSE_BELOW_ALTITUDE,
	WAYPOINT_REACHED_FALSE_RADIUS,
	WAYPOINT_REACHED_FALSE_TRANSMIT_DATA,
	WAYPOINT_REACHED_FALSE_WAIT,
	WAYPOINT_REACHED_TRUE,
	WAYPOINT_REACHED_TRUE_ROUTE_END,
	WAYPOINT_REACHED_TRUE_ROUTE_LOOP,
	NUM_WAYPOINT_REACHED_TYPES
};

typedef enum WAYPOINT_REACHED_TYPES waypoint_reached_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
enum WAYPOINT_CRITERIA_TYPES
{

	WAYPOINT_CRITERIA_NONE						= 0,
	WAYPOINT_CRITERIA_TIME						= 1,
	WAYPOINT_CRITERIA_DELTA_TIME				= 2,
	WAYPOINT_CRITERIA_MIN_RADIUS				= 4,
	WAYPOINT_CRITERIA_MAX_RADIUS				= 8,
	WAYPOINT_CRITERIA_HEADING					= 16,
	WAYPOINT_CRITERIA_ALTITUDE					= 32,
	WAYPOINT_CRITERIA_VELOCITY					= 64,
	WAYPOINT_CRITERIA_RADIUS_OR_FLY_PAST	= 128,
	WAYPOINT_CRITERIA_TRANSMIT_DATA			= 256,

	//
	// LAST_TO_REACH must be last valid criteria.
	//

	WAYPOINT_CRITERIA_LAST_TO_REACH			= 512,
	NUM_WAYPOINT_CRITERIA_TYPES				= 1024
};

typedef enum WAYPOINT_CRITERIA_TYPES waypoint_criteria_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct WAYPOINT_CRITERIA
{

	unsigned short int
		criteria_flags;

	int
		time,
		delta_time,
		timer,
		reached_counter;

	float
		radius,
		heading,
		altitude,
		velocity;
};

typedef struct WAYPOINT_CRITERIA waypoint_criteria;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern char *waypoint_criteria_names [];
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
