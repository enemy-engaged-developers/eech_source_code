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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition
waypoint_data
   waypoint_database[NUM_ENTITY_SUB_TYPE_WAYPOINTS] =
	{
		/////////////////////////////////////////////////////////////////
      {
         "Approach",    			             				// Name
			VERBOSE_OPERATIONAL_STATE_RETURING_TO_BASE,		// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_APPROACH_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         0.5,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         0.7,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
      {
         "Attack",  				                 				// Name
			VERBOSE_OPERATIONAL_STATE_APPROACHING_TARGET,	// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			ENTITY_MESSAGE_WAYPOINT_ATTACK_ACTION,				// waypoint action message
			NUM_ENTITY_MESSAGES,										// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			TRUE,															// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			TRUE,															// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			8 * KILOMETRE, 											// Minimum previous waypoint distance
         8 * KILOMETRE,                           			// Action Radius
         2 * KILOMETRE,                           			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			5 * KILOMETRE, 											// Minimum previous waypoint distance
         5 * KILOMETRE,                           			// Action Radius
         0.5 * KILOMETRE,                         			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
      {
         "CAP Loop",		 				           				// Name
			VERBOSE_OPERATIONAL_STATE_EN_ROUTE,					// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_NAVIGATION_REACHED,		// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			TRUE,															// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         150,                                    			// Action Radius
         150,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         40,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "CAP Start",	  				          				// Name
			VERBOSE_OPERATIONAL_STATE_EN_ROUTE,					// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_NAVIGATION_REACHED,		// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         150,                                    			// Action Radius
         150,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         40,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Convoy",  				             					// Name
			VERBOSE_OPERATIONAL_STATE_MANOEUVRING,				// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_CONVOY_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         40,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,	                                    			// Action Radius
         1,	                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Defend",  				             					// Name
			VERBOSE_OPERATIONAL_STATE_MANOEUVRING,				// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_DEFEND_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,	                                    			// Action Radius
         1,	                                    			// Reached Radius
         1.0,  									       			// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Drop Off",     			          					// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_DROP_OFF_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			TRUE,															// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,                                    			// Action Radius
         100,                                    			// Reached Radius
         0.6,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         40,                                    			// Reached Radius
         0.6,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "End",     			               					// Name
			VERBOSE_OPERATIONAL_STATE_EN_ROUTE,					// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_END_REACHED,				// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         40,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Escort",  			               					// Name
			VERBOSE_OPERATIONAL_STATE_AIR_PATROL,				// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			NUM_ENTITY_MESSAGES,										// waypoint reached message
			WAYPOINT_REACHED_FALSE,									// waypoint reached return value
			FALSE,														// Planner moveable
			TRUE,															// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_VIRTUAL,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         500,                                    			// Action Radius
         500,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,                                    			// Action Radius
         100,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Finish Drop Off",   			            		// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_FINISH_DROP_OFF_REACHED,// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,	                                   			// Action Radius
         100,	                                   			// Reached Radius
         0.6,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,	                                   			// Action Radius
         40,	                                   			// Reached Radius
         0.6,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                 			   // Action Radius
         20,                                 			   // Reached Radius
         1.0,  									    			   // Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Holding",		 				           				// Name
			VERBOSE_OPERATIONAL_STATE_HOLDING,					// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_NAVIGATION_REACHED,		// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         150,                                    			// Action Radius
         150,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         50,                                    			// Action Radius
         50,                                    			// Reached Radius
         1.0,  									      			// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Holding Loop",                   					// Name
			VERBOSE_OPERATIONAL_STATE_HOLDING,					// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_LOOP_REACHED,				// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_LOOP,					// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,                                    			// Action Radius
         100,                                    			// Reached Radius
         0.8,  										       		// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         40,                                    			// Reached Radius
         0.8,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
			20,															// Action Radius
			20,															// Reached Radius
			1.0,															// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Impossible",  			                 			// Name
			VERBOSE_OPERATIONAL_STATE_APPROACHING_TARGET,	// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			NUM_ENTITY_MESSAGES,										// waypoint reached message
			WAYPOINT_REACHED_FALSE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         1.0,  									   				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         5,                                     			// Action Radius
         5,                                     			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         50,                                   				// Action Radius
         50,                                   				// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Land",  			                 					// Name
			VERBOSE_OPERATIONAL_STATE_LANDING,					// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_LAND_REACHED,				// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         500,                                     			// Action Radius
         500,                                     			// Reached Radius
         1.0, 		 									     			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         500,                                     			// Action Radius
         500,                                     			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         10,   	                                			// Action Radius
         10,   	                                			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Landed",  			            						// Name
			VERBOSE_OPERATIONAL_STATE_REPAIRING,				// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_LANDED_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_LANDED,							// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         2,	                                    			// Action Radius
         2,	                                    			// Reached Radius
         0.04,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         2,	                                    			// Action Radius
         2,	                                    			// Reached Radius
         0.1,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Lift Off", 						         			// Name
			VERBOSE_OPERATIONAL_STATE_TAKEOFF,					// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_LIFT_OFF_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT,				// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         25,                                    			// Action Radius
         25,                                    			// Reached Radius
         0.4,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
      {
         "Lower Undercarriage",   			 					// Name
			VERBOSE_OPERATIONAL_STATE_LANDING,					// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			ENTITY_MESSAGE_WAYPOINT_LOWER_UNDERCARRIAGE_ACTION,			// waypoint action message
			NUM_ENTITY_MESSAGES,										// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			TRUE,															// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,                                    			// Action Radius
         100,                                    			// Reached Radius
         0.5,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         15,                                    			// Reached Radius
         0.6,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
			20,															// Action Radius
			20,															// Reached Radius
			1.0,															// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Navigation",	 				           				// Name
			VERBOSE_OPERATIONAL_STATE_EN_ROUTE,					// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_NAVIGATION_REACHED,		// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			TRUE,															// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         150,                                    			// Action Radius
         150,                                    			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         50,                                    			// Action Radius
         50,                                    			// Reached Radius
         1.0,  									      			// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Prepare For Drop Off",   			            	// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_PREPARE_FOR_DROP_OFF_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,	                                   			// Action Radius
         100,	                                   			// Reached Radius
         0.6,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,	                                   			// Action Radius
         40,	                                   			// Reached Radius
         0.6,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                 			   // Action Radius
         20,                                 			   // Reached Radius
         1.0,  									    			   // Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Pick Up",  			              					// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_PICK_UP_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,	                                   			// Action Radius
         100,	                                   			// Reached Radius
         0.6,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,	                                   			// Action Radius
         40,	                                   			// Reached Radius
         0.6,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                 			   // Action Radius
         20,                                 			   // Reached Radius
         1.0,  									    			   // Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Raise Undercarriage",    								// Name
			VERBOSE_OPERATIONAL_STATE_TAKEOFF,					// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_RAISE_UNDERCARRIAGE_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			TRUE,															// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT,				// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         100,                                    			// Action Radius
         100,                                    			// Reached Radius
         0.7,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         15,                                    			// Action Radius
         15,                                    			// Reached Radius
         0.2,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
			20,															// Action Radius
			20,															// Reached Radius
			1.0,															// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Recon", 	 			               				// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_RECON,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			ENTITY_MESSAGE_WAYPOINT_RECON_ACTION,				// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_RECON_REACHED,				// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			TRUE,															// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			TRUE,															// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			8 * KILOMETRE, 											// Minimum previous waypoint distance
         1.5 * KILOMETRE,                         			// Action Radius
         1.5 * KILOMETRE,                         			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			TRUE,															// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			5 * KILOMETRE, 											// Minimum previous waypoint distance
         1.0 * KILOMETRE,                         			// Action Radius
         0.25 * KILOMETRE,                        			// Reached Radius
         1.0,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			TRUE,															// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                 			   // Action Radius
         20,                                 			   // Reached Radius
         1.0,  									    			   // Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Repair", 				                				// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_RECON,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_REPAIR_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			TRUE,															// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         400,                                    			// Action Radius
         400,                                    			// Reached Radius
         0.6,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			TRUE,															// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         50,                                    			// Action Radius
         50,                                    			// Reached Radius
         0.5,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			TRUE,															// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                 			   // Action Radius
         20,                                 			   // Reached Radius
         1.0,  									    			   // Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
		{
         "Reverse Convoy",   			      					// Name
			VERBOSE_OPERATIONAL_STATE_MANOEUVRING,				// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_REVERSE_CONVOY_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ROUTED,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,	                                    			// Action Radius
         1,	                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
		{
         "Start Up",				 				  					// Name
			VERBOSE_OPERATIONAL_STATE_PREPARING_FOR_TAKEOFF,// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_START_UP_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT,				// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         3,                                    				// Action Radius
         3,                                    				// Reached Radius
         0.06,  									    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                     			// Action Radius
         0,                                     			// Reached Radius
         0,	                                    			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
		{
         "Sub Route Navigation",		 				  			// Name
			VERBOSE_OPERATIONAL_STATE_MANOEUVRING,				// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_SUB_ROUTE_NAVIGATION_REACHED,			// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Taken Off",     				  							// Name
			VERBOSE_OPERATIONAL_STATE_TAKEOFF,					// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TAKEN_OFF_REACHED,		// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			TRUE,															// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         150,                                    			// Action Radius
         150,                                    			// Reached Radius
         0.8,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         40,                                    			// Action Radius
         40,                                    			// Reached Radius
         0.8,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Target",    			             					// Name
			VERBOSE_OPERATIONAL_STATE_ENGAGING_TARGET,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_END_REACHED,				// waypoint reached message
			WAYPOINT_REACHED_TRUE_ROUTE_END,						// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         150,                                    			// Action Radius
         150,                                    			// Reached Radius
         0.75,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,	                                   			// Action Radius
         20,	                                   			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         10,                                     			// Action Radius
         10,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1 * KILOMETRE,                           			// Action Radius
         1 * KILOMETRE,                           			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_VIRTUAL,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Taxi",   				              					// Name
			VERBOSE_OPERATIONAL_STATE_TAXIING,					// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TAXI_REACHED,				// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			TRUE,															// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT,				// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         10,                                    			// Action Radius
         10,                                    			// Reached Radius
         0.04,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         10,	                                   			// Action Radius
         10,	                                   			// Reached Radius
         0.2,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,                                     			// Action Radius
         1,                                     			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         20,                                    			// Action Radius
         20,                                    			// Reached Radius
         1.0,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_SEA,										// Movement type
      },
      {
         "Touch Down",    			   							// Name
			VERBOSE_OPERATIONAL_STATE_TAXIING,					// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TOUCH_DOWN_REACHED,		// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT,				// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         30,                                    			// Action Radius
         30,                                    			// Reached Radius
         0.4,  									      			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
      {
         "Capture",  					  							// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TROOP_CAPTURE_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,	                                    			// Action Radius
         1,	                                    			// Reached Radius
         0.2,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1.0,                                  				// Action Radius
         1.0,                                  				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
      {
         "Defend",    												// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TROOP_DEFEND_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,	                                    			// Action Radius
         1,	                                    			// Reached Radius
         0.2,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1.0,                                  				// Action Radius
         1.0,                                  				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
      {
         "Insert Troops",  			  							// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TROOP_INSERT_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			TRUE,															// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ALTITUDE,		// guide sub type
			MAP_ICON_WAYPOINT_TARGET,								// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         5,	                                    			// Action Radius
         5,	                                    			// Reached Radius
         0.2,  									       			// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
      {
         "Troop Pickup Point End", 								// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TROOP_PICKUP_POINT_END_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ALTITUDE,		// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,	                                    			// Action Radius
         0,	                                    			// Reached Radius
         0,		  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1.0,                                  				// Action Radius
         1.0,                                  				// Reached Radius
         5.0,                                  				// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type
      },
      {
         "Troop Pickup Point Start", 							// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TROOP_PICKUP_POINT_START_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,			// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,	                                    			// Action Radius
         0,	                                    			// Reached Radius
         0,		  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1.0,                                  				// Action Radius
         1.0,                                  				// Reached Radius
         5.0,                                  				// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type
      },
      {
         "Troop Putdown Point",									// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			TRUE,															// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_TROOP_PUTDOWN_POINT_REACHED,	// waypoint reached message
			WAYPOINT_REACHED_TRUE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ALTITUDE,		// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,	                                    			// Action Radius
         0,	                                    			// Reached Radius
         0,		  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1.0,                                  				// Action Radius
         1.0,                                  				// Reached Radius
         5.0,                                  				// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_GROUND,									// Movement type
      },
      {
         "Wait", 						   							// Name
			VERBOSE_OPERATIONAL_STATE_PERFORMING_TASK,		// En-route verbose_operational_state
			FALSE,														// mobile follow waypoint offset
			NUM_ENTITY_MESSAGES,										// waypoint action message
			ENTITY_MESSAGE_WAYPOINT_WAIT_REACHED,				// waypoint reached message
			WAYPOINT_REACHED_FALSE,									// waypoint reached return value
			FALSE,														// Planner moveable
			FALSE,														// Objective Waypoint
			FALSE,														// Player Skip Waypoint
			FALSE,														// Check Waypoint Action
			ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ALTITUDE,		// guide sub type
			MAP_ICON_WAYPOINT_NAV,									// map icon type

			// FIXED WING
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// HELICOPTER
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         1,	                                    			// Action Radius
         1,	                                    			// Reached Radius
         0.2,  									       			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// GROUND
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0,                                    				// Action Radius
         0,                                    				// Reached Radius
         0,                                    				// Velocity
			TRUE,															// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type

			// SEA
			0 * KILOMETRE, 											// Minimum previous waypoint distance
         0, 	                                   			// Action Radius
         0, 	                                   			// Reached Radius
         0,    	                                			// Velocity
			FALSE,														// Criteria Last To Reach
			FALSE,														// Criteria Transmit Recon
			POSITION_TYPE_ABSOLUTE,									// Position type
			MOVEMENT_TYPE_AIR,										// Movement type
      },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_waypoint_database_action_radius_value (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_action_radius;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_action_radius;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_action_radius;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_action_radius;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_entity_waypoint_database_action_radius_value (entity *waypoint, entity *mobile)
{
	entity_sub_types
		waypoint_type,
		mobile_type;

	waypoint_type = get_local_entity_int_value (waypoint, INT_TYPE_ENTITY_SUB_TYPE);

	mobile_type = get_local_entity_type (mobile);

	return get_waypoint_database_action_radius_value (waypoint_type, mobile_type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_waypoint_database_reached_radius_value (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_reached_radius;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_reached_radius;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_reached_radius;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_reached_radius;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_entity_waypoint_database_reached_radius_value (entity *waypoint, entity *mobile)
{
	entity_sub_types
		waypoint_type,
		mobile_type;

	waypoint_type = get_local_entity_int_value (waypoint, INT_TYPE_ENTITY_SUB_TYPE);

	mobile_type = get_local_entity_type (mobile);

	return get_waypoint_database_reached_radius_value (waypoint_type, mobile_type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_waypoint_database_velocity_value (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_velocity;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_velocity;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_velocity;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_velocity;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_waypoint_database_transmit_recon_flag (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_criteria_transmit_recon;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_criteria_transmit_recon;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_criteria_transmit_recon;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_criteria_transmit_recon;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_waypoint_database_last_to_reach_flag (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_criteria_last_to_reach;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_criteria_last_to_reach;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_criteria_last_to_reach;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_criteria_last_to_reach;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_waypoint_database_position_type_value (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_position_type;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_position_type;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_position_type;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_position_type;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_waypoint_database_movement_type_value (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_movement_type;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_movement_type;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_movement_type;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_movement_type;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_waypoint_database_minimum_previous_waypoint_distance (entity_sub_types waypoint_type, entity_types mobile_type)
{
	switch (mobile_type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			return waypoint_database [waypoint_type].fw_minimum_previous_waypoint_distance;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			return waypoint_database [waypoint_type].hc_minimum_previous_waypoint_distance;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_ANTI_AIRCRAFT:
		case ENTITY_TYPE_PERSON:
		{
			return waypoint_database [waypoint_type].rv_minimum_previous_waypoint_distance;
		}
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			return waypoint_database [waypoint_type].sh_minimum_previous_waypoint_distance;
		}
	}

	debug_fatal ("WP_DBASE : Invalid entity type (%s)", get_entity_type_name (mobile_type));

	return 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
