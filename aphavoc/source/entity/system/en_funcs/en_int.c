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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE				0

#define DEBUG_MODULE_PACK_ONE	0

#define DEBUG_MODULE_PACK_ALL	(PACK_ENTIRE_SESSION || 0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ILLEGAL	(FALSE)												// use for values which cannot be fast tracked

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int_type_data
	int_type_database[NUM_INT_TYPES] =
	{
		{
			"INT_TYPE_ADDITIVE",	 			             			// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			NUM_ADDITIVE_BITS,											// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AIR_ATTACK_STRENGTH",							// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,	 															// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE",				// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_WEAPON_CONFIG_TYPE_BITS,	 							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE",		// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_WEAPON_CONFIG_TYPE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AIRBORNE_AIRCRAFT",	              			// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			NUM_AIRBORNE_AIRCRAFT_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AIRCRAFT_GROUP",	  	            			// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ALIGN_WITH_TERRAIN",	  						// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_ALIGN_WITH_TERRAIN_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ALIVE",												// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_ALIVE_BITS,												// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ANIMATED_TEXTURE",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ANIMATED_TEXTURE_BITS,                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_APPROXIMATION_OBJECT_3D_SHAPE",				// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_OBJECT_3D_SHAPE_BITS,                				// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ASSESS_LANDING",                			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AUTO_ASSIGN_GUNSHIP",               		// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_AUTO_ASSIGN_GUNSHIP_BITS,               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AUTO_PILOT",           			    		// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_AUTO_PILOT_BITS,  			             			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AWARDED_MEDALS",         			    		// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_AWARDED_MEDALS_BITS,						  			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_AWARDED_PROMOTION",      			    		// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_AWARDED_PROMOTION_BITS,						  		// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_BRIDGE_SEGMENT_TYPE",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CAMERA_MODE",	  									// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,	 															// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CAMPAIGN_CRITERIA_COUNT",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CAMPAIGN_CRITERIA_COUNT_BITS,						// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CAMPAIGN_CRITERIA_RESULT",					// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CAMPAIGN_CRITERIA_RESULT_BITS,						// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CAMPAIGN_CRITERIA_TYPE",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CAMPAIGN_CRITERIA_TYPE_BITS,							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CAMPAIGN_CRITERIA_VALUE",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CAMPAIGN_CRITERIA_VALUE_BITS,						// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CAMPAIGN_MEDAL",									// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CAMPAIGN_MEDAL_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC",			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CAMPAIGN_REQUIRES_APACHE_HAVOC_BITS,				// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CHEATS_ENABLED",									// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CHEATS_ENABLED_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CHECK_WAYPOINT_ACTION",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CHECK_WAYPOINT_ACTION_BITS,							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CHILD_COUNT",										// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_CHILD_COUNT_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COLLISION_TEST_FIXED",  		 				// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,											 					// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COLLISION_TEST_MOBILE",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COLOUR",                        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_COLOUR_BITS,												// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COLOUR_ALPHA",                    			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_COLOUR_COMPONENT_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COLOUR_BLUE",                     			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_COLOUR_COMPONENT_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COLOUR_GREEN",                    			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_COLOUR_COMPONENT_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COLOUR_RED",                      			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_COLOUR_COMPONENT_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_COUNT",   	                     			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CPG_IDENTIFIED",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_CPG_IDENTIFIED_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CREW_ROLE",										// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_CREW_ROLE_BITS,											// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_CRITICAL_TASK",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_CRITICAL_TASK_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DAMAGE_LEVEL",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_DAMAGE_BITS,												// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DAY",              								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_DAY_BITS,  					              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DAY_SEGMENT_TYPE",              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_DAY_SEGMENT_TYPE_BITS,                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DELAY_TASK_ASSIGNMENT",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1, 	                                      			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DEFAULT_3D_SHAPE",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DEFAULT_ENGAGE_ENEMY",							// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ENGAGE_ENEMY_BITS,		                 			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DEFAULT_GROUP_LIST_TYPE",         			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE",					// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_CONFIG_TYPE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DEFAULT_WEAPON_TYPE",							// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DESTROYED_3D_SHAPE",							// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DIFFICULTY_LEVEL",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_DIFFICULTY_LEVEL_BITS,                  			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_DIVISION_ID",                     			// name
			INT_PACK_TYPE_UNSIGNED,   	               			// pack_type
			NUM_DIVISION_ID_BITS,                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_EJECTED",			               			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_EJECTED_BITS,												// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			TRUE,																// fast_track
		},
		{
			"INT_TYPE_END_NODE",			               			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,		 						                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ENGAGE_ENEMY",	               			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ENGAGE_ENEMY_BITS,		                 			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ENTITY_SUB_TYPE",               			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ENTITY_SUB_TYPE_BITS,                 			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_EVADE_FIRE",  		             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,  								               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_EXPLOSIVE_POWER",                 			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_EXPLOSIVE_POWER_BITS,                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_EXPLOSIVE_QUALITY",               			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_EXPLOSIVE_QUALITY_BITS,                 			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_EXPOSURE_LEVEL",                			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			8,	                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FOLLOW_FORMATION",  	          			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FORCE",        			          			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FORCE_ATTITUDE",			          			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			NUM_FORCE_ATTITUDE_BITS,                    			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FORCE_INFO_CATAGORY",				  			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_FORCE_INFO_CATAGORY_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FORCE_SECTOR_COUNT",				  			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_FORCE_SECTOR_COUNT_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FORMATION_POSITION",            			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_FORMATION_BITS,											// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FORMATION_POSITIONS",            			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_FORMATION_POSITIONS_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FREE_LANDING_SITES",            			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_FRONTLINE",     			           			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_FRONTLINE_BITS,                         			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUND_RADAR_CLUTTER",							// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,			 													// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_AMALGAMATE",                			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32,   								              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_CALLSIGN",                  			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GROUP_CALLSIGN_BITS,                    			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_CATEGORY",                  			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32,   							                 			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_DEFAULT_FORMATION",         			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GROUP_FORMATION_BITS,                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_FORMATION",                 			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GROUP_FORMATION_BITS,                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_LEADER",   		          			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GROUP_LEADER_BITS,    			           			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_LIST_TYPE",  	            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_LIST_TYPE_PACK_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_MEMBER_ID",	             			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32,   								            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_MEMBER_NUMBER",             			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GROUP_MEMBER_NUMBER_BITS,               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_MEMBER_STATE",             			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32, 									              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GROUP_MODE",                    			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GROUP_MODE_BITS,                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GUIDE_CRITERIA_TYPE",             			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GUIDE_CRITERIA_TYPE_BITS,               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GUIDE_POSITION_TYPE",             			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GUIDE_POSITION_TYPE_BITS,               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR",						// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_GUNSHIP_RADAR_LOS_CLEAR_BITS,						// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_GUNSHIP_TYPE",                    			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_GUNSHIP_TYPE_BITS,                      			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_HAND_OFF_TARGET_COUNT",           			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_HAND_OFF_TARGET_COUNT_BITS,             			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_HARD_DAMAGE_CAPABILITY",          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,   								             			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_HELICOPTER_DAMAGE_FLAGS",         			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_HELICOPTER_DAMAGE_FLAGS_BITS,           			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_HELICOPTER_DAMAGE_LEVEL",         			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_HELICOPTER_DAMAGE_LEVEL_BITS,           			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_HIDDEN_BY_FOG_OF_WAR",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_AIRCRAFT",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_ANTI_AIRCRAFT",          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_CARGO",		             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_FIXED",                			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_FIXED_WING",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_HELICOPTER",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_MOBILE",               			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_ROUTED", 	             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_SHIP_VEHICLE",           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_VEHICLE",              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_WAYPOINT",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IDENTIFY_WEAPON",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ID_NUMBER",                      			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32,               				            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS",				// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			32,               				            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INFINITE_FUEL",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_INFINITE_FUEL_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INFINITE_GENERATOR",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INFINITE_WEAPONS",  	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_INFINITE_WEAPONS_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INFRA_RED_JAMMER_ON",							// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_INFRA_RED_JAMMER_ON_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INITIAL_DAMAGE_LEVEL",							// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_DAMAGE_BITS,												// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INSIDE_HANGAR",                   			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INVULNERABLE_FROM_COLLISIONS",           // name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_INVULNERABLE_BITS,                      			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_INVULNERABLE_FROM_WEAPONS",              // name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_INVULNERABLE_BITS,                      			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_IN_USE",                        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,                                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_KEYSITE_COUNT",                 			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			8,	                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_KEYSITE_ID",                      			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_KEYSITE_ID_BITS,  			            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_KEYSITE_USABLE_STATE",            			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_KEYSITE_USABLE_STATE_BITS,              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_KILL_NEXT_UPDATE",              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_KILL_NEXT_UPDATE_BITS,                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_KILLS",                         			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			NUM_KILLS_BITS,                             			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LANDED",                   					// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,	                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LANDED_LOCK",                   			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LANDED_ON_CARRIER",               			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,	                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LANDING_LOCK",                  			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LANDING_TYPES",                 			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_LANDING_TYPE_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LASER_ON",											// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_LASER_ON_BITS,											// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LENGTH",			                 			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_LENGTH_BITS,												// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LIGHTS_ON",                     			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_LIGHTS_ON_BITS,											// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LOCAL_EFFECT_COUNT",              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_LOCAL_EFFECT_COUNT_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LOCAL_ONLY_GROUP",                			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_LOCAL_ONLY_GROUP_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LOCAL_WEATHER_MODEL",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_LOCAL_WEATHER_MODEL_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LOCK_ON_AFTER_LAUNCH",							// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_LOCK_ON_AFTER_LAUNCH_BITS,							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LOSSES",                         			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_LOSSES_BITS,                            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_LOS_TO_TARGET",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_LOS_TO_TARGET_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MAIN_ROTOR_DAMAGED",		        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,																	// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MAP_ICON",		   		          			// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MAXIMUM_MEMBER_COUNT", 	              	// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MAXIMUM_VOLUME", 			              	// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MAX_WEAPON_CONFIG_TYPE",               	// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_CONFIG_TYPE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MEMBER_COUNT", 		              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_MEMBER_COUNT_BITS,                      			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MESSAGE_TEXT_TYPE",  	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_MESSAGE_TEXT_TYPE_BITS,     	         			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_META_EXPLOSION_TYPE",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_META_EXPLOSION_TYPE_BITS,              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_META_SMOKE_LIST_TYPE",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_META_SMOKE_LIST_TYPE_BITS,              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MINIMUM_IDLE_COUNT", 		              	// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MINIMUM_MEMBER_COUNT", 	              	// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MIN_WEAPON_CONFIG_TYPE",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_CONFIG_TYPE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MOBILE_FOLLOW_WAYPOINT_OFFSET",				// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,  									              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MOBILE_MOVING",									// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_MOBILE_MOVING_BITS,  		              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MOVEMENT_TYPE",	                			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			NUM_MOVEMENT_TYPE_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_MULTIPLAYER_GROUP",	              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_MULTIPLAYER_GROUP_BITS,                 			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_OBJECT_3D_SHAPE",               			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_OBJECT_3D_SHAPE_BITS,                 			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME",				// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_OBJECT_DRAWN_ONCE_THIS_FRAME_BITS,					// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_OBJECT_INDEX",									// name
			INT_PACK_TYPE_SIGNED,   	                			// pack_type
			NUM_OBJECT_INDEX_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_OBJECT_SCALING",									// name
			INT_PACK_TYPE_SIGNED,   	                			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_OFFENSIVE_CAPABILITY",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,    		 													// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_OPERATIONAL_STATE",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_OPERATIONAL_STATE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PARTICLE_COUNT",                  			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_PARTICLE_COUNT_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PERFORM_DEBRIEF",                 			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_PERFORM_DEBRIEF_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PILOT_RANK",                      			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_PILOT_RANK_BITS,                        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PLANNER_MOVEABLE",                			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,						                          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PLAYER",                        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32, 					                         			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PLAYER_CONTROLLABLE",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_PLAYER_BITS,                          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PLAYER_TASK",                     			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_PLAYER_TASK_BITS,                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_POINTS_VALUE",   	              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_POSITION_HOLD",                 			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_POSITION_HOLD_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_POSITION_TYPE",                 			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_POSITION_TYPE_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_POTENTIAL_CAMPAIGN_OBJECTIVE",    			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,																	// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PRIMARY_TASK",                    			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,    						                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PROTOTYPE_1",										// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PROTOTYPE_2",										// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PROTOTYPE_3",										// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_PROTOTYPE_4",										// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_RADAR_JAMMER_ON",								// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_RADAR_JAMMER_ON_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_RADAR_ON",     					   			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_RADAR_ON_BITS,       		            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_RADIO_MESSAGE_TYPE",   		   			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_RADIO_MESSAGE_TYPE_BITS,               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_RADIO_MESSAGE_VALUE",   		   			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_RADIO_MESSAGE_VALUE_BITS,               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_REARMING",						        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_REARMING_BITS, 		                  			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_REGEN_CREATION_SUB_TYPE",        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ENTITY_SUB_TYPE_BITS,                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_REGISTRY_LIST_TYPE",              			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_RESERVED_LANDING_SITES",        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_RESUPPLY_SOURCE",			        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_RESUPPLY_SOURCE_BITS,                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ROUTE_CHECK_SUM",                 			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ROUTE_CHECK_SUM_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ROUTE_LENGTH",                  			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ROUTE_LENGTH_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_ROUTE_NODE",                    			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ROUTE_NODE_BITS,											// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_RULES_OF_ENGAGEMENT",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_ROE_TYPE_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE",					// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,     					                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SECTOR_SIDE",                     			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,     					                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SELECTED_WEAPON",                    		// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_ENTITY_SUB_TYPE_WEAPON_BITS,							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			TRUE,																// fast_track
		},
		{
			"INT_TYPE_SELECTED_WEAPON_SYSTEM_READY",				// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_SELECTED_WEAPON_SYSTEM_READY_BITS,					// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SESSION_COMPLETE",                			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SESSION_COMPLETE_BITS,                  			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SIDE",                          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SIDE_BITS,                            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SKIP_NIGHT_TIME",                    		// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SKIP_NIGHT_TIME_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SMOKE_TYPE",                      			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SMOKE_TYPE_BITS,											// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOFT_DAMAGE_CAPABILITY",          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,   								             			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOLO_TASK",  	                  			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,    						                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_CHANNEL", 		 	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SOUND_CHANNEL_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_EFFECT_INDEX",							// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			NUM_SOUND_EFFECT_INDEX_BITS,	  							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_EFFECT_LOOPING",                   // name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SOUND_EFFECT_LOOPING_BITS,  							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_EFFECT_PANNING",                   // name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			NUM_SOUND_EFFECT_PANNING_BITS,  							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_EFFECT_RATE", 	                  // name
			INT_PACK_TYPE_SIGNED,	                   			// pack_type
			NUM_SOUND_EFFECT_RATE_BITS, 	 							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_EFFECT_SEQUENCE_COUNT",            // name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			NUM_SOUND_EFFECT_SEQUENCE_COUNT_BITS, 	 				// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_LIST_VALID",								// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,  																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SOUND_LOCALITY", 	 	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SOUND_LOCALITY_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SPEECH_CATEGORY", 		          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SPEECH_CATEGORY_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SPEECH_INDEX", 		 	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SPEECH_INDEX_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_START_NODE",                    			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_STRATEGY",			                			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_STRATEGY_LEVEL",                			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SUB_OBJECT_DEPTH",  	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,   									           			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SUB_OBJECT_TYPE",  		          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,   									           			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SUB_WAYPOINT_COUNT",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_SUB_WAYPOINT_COUNT_BITS,              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_SUPPRESS_AI_FIRE",								// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_SUPPRESS_AI_FIRE_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TAIL_ROTOR_DAMAGED",		        			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,																	// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TAKEOFF_LOCK",                  			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TARGET_PRIORITY_TYPE",	  						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,    		 													// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TARGET_SYMBOL_TYPE",	  						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,    		 													// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TARGET_TYPE",                   			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,    		 													// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TARGET_WEATHER_MODE",           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEATHER_MODE_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_CATEGORY",									// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,   							                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_COMPLETED",									// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_COMPLETED_BITS,                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_DIFFICULTY",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_DIFFICULTY_BITS,                   			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_GENERATION",		           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_GENERATION_BITS,	   	          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_ID",		 		     		     			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_ID_BITS,	   				          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_LEADER",   			          			// name
			INT_PACK_TYPE_UNSIGNED,                     			// pack_type
			NUM_TASK_LEADER_BITS,    			           			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_OBJECTIVE_PREVIEW_TYPE",	  			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,	  										        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_PASS_PERCENTAGE_PARTIAL",	  			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,	  										        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_PASS_PERCENTAGE_SUCCESS",    			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,	  										        			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_ROUTE_SEARCH",	           				// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			1,											          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_SCORE",				           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_SCORE_BITS,	   		 	         			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_STATE",				           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_STATE_BITS,	   		 	         			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_TARGET_CLASS", 				         // name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_TARGET_CLASS_BITS,		          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_TARGET_SOURCE", 	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_TARGET_SOURCE_BITS,		          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_TARGET_TYPE",	 	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_TARGET_TYPE_BITS,			          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TASK_TERMINATED",	 	          			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_TASK_TERMINATED_BITS,			          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TERRAIN_FOLLOW_MODE",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_THREAT_TYPE",		                 			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TIMER",                         			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TOTAL_LANDING_SITES",           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,   					                      			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_TRACK_ENTITY_ON_MAP",           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,   					                      			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_UNIQUE_ID",                     			// name
			INT_PACK_TYPE_SIGNED,    	               			// pack_type
			NUM_UNIQUE_ID_BITS,                         			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_UPDATED",	                     			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VALID",												// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_VALID_BITS, 				               			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VALID_GUIDE_MEMBERS",							// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_VALID_GUIDE_MEMBERS_BITS, 			     			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VALID_SOUND_EFFECT",							// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_VALID_SOUND_EFFECT_BITS,                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VALUE",												// name
			INT_PACK_TYPE_SIGNED,	                   			// pack_type
			32,								                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VEHICLE_GROUP",	  	            			// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VERBOSE_OPERATIONAL_STATE",					// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			NUM_VERBOSE_OPERATIONAL_STATE_BITS,         			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VERSION_NUMBER",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_VERSION_NUMBER_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VIEW_CATEGORY",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,		  														// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VIEW_TYPE",										// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,		  														// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VIEWABLE",											// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,								                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VIEWABLE_WEAPON",								// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,								                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_VISIBLE_TASK",									// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,								                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WAIT_FOR_END_TASK",								// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			32,								                			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WARHEAD_EFFECTIVE_CLASS",		 				// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WAYPOINT_COUNT",                			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WAYPOINT_COUNT_BITS,                  			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WAYPOINT_FORMATION",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WAYPOINT_FORMATION_BITS,              			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WAYPOINT_GUIDE_TYPE",            			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,    									          			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WAYPOINT_NEXT_INDEX",             			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WAYPOINT_INDEX_BITS,                  			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WAYPOINT_THIS_INDEX",               		// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WAYPOINT_INDEX_BITS,                  			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID",			// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_WEAPON_AND_TARGET_VECTORS_VALID_BITS,				// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_BURST_SIZE",				 				// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_BURST_SIZE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_CAMERA_PRIMED",							// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			32,																// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_CONFIG_TYPE",							// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_CONFIG_TYPE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			ILLEGAL,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_DECOY_TYPE",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_GUIDANCE_TYPE",           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_KILL_CODE",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_KILL_CODE_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_MISSILE_PHASE",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_MISSILE_PHASE_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_ON_GROUND",								// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_ON_GROUND_BITS,									// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_PACKAGE_DAMAGED",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_PACKAGE_DAMAGED_BITS,							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_PACKAGE_HEADING_DEPTH",				// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_PACKAGE_HEADING_DEPTH_BITS,					// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_PACKAGE_NUMBER",						// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			NUM_WEAPON_PACKAGE_NUMBER_BITS,							// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_SMOKE_TRAIL_TYPE",         			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_SYSTEM_READY",         	  			// name
			INT_PACK_TYPE_UNSIGNED,	                   			// pack_type
			1,																	// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPON_WARHEAD_TYPE",           			// name
			INT_PACK_TYPE_UNSIGNED,                   			// pack_type
			32,                                       			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEAPONS_HOLD",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_WEAPONS_HOLD_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEATHER_INCREASING",							// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_WEATHER_INCREASING_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WEATHER_MODE",									// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_WEATHER_MODE_BITS,										// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_WIND_INCREASING",								// name
			INT_PACK_TYPE_UNSIGNED,										// pack_type
			NUM_WEATHER_INCREASING_BITS,								// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_X_SECTOR",                      			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			NUM_SECTOR_BITS,                            			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"INT_TYPE_Z_SECTOR",                      			// name
			INT_PACK_TYPE_SIGNED,                     			// pack_type
			NUM_SECTOR_BITS,                           			// num_pack_bits (including sign bit)
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*overload_invalid_int_type_message = "Overloaded entity function invoked with invalid int type",
	*debug_fatal_invalid_int_type_message = "Invalid int type (entity type = %s, index = %d, int type = %s, file = %s, line = %d)";

#define DEBUG_PACK_OVERFLOW

#ifdef DEBUG_PACK_OVERFLOW
static FILE *debug_pack_file = NULL;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_set_local_entity_raw_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES]) (entity *en, int_types type, int value);

void (*fn_set_local_entity_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES]) (entity *en, int_types type, int value);

void (*fn_set_client_server_entity_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en, int_types type, int value);

int (*fn_get_local_entity_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES]) (entity *en, int_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_int_value (entity *en, int_types type, int value)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_log_pack_overflow(const char* type, const char* name, unsigned int width, int value, float fvalue)
{
	debug_log("Overflow - type: %s, width %d, value: %d", name, width, value);

	#ifdef DEBUG_PACK_OVERFLOW	
		if (!debug_pack_file)
			debug_pack_file = fopen("debug-save-errors.txt","a");
		if (!debug_pack_file)
		{
			const char* error_msg = strerror(errno);
			debug_fatal ("Could not open debug errors file: %s", error_msg);
			return;
		}

		ASSERT(debug_pack_file);
		
		fprintf(debug_pack_file, "Overflow %s type: %s, width %d, int value: %d, float value: %f\n", type, name, width, value, fvalue);
		fclose(debug_pack_file);
	#endif
}

/*static void debug_log_pack(const char* string)
{
	#ifdef DEBUG_PACK_OVERFLOW	
		if (!debug_pack_file)
			debug_pack_file = fopen("debug-save-errors.txt","a");
		if (!debug_pack_file)
		{
			const char* error_msg = strerror(errno);
			debug_fatal ("Could not open debug errors file: %s", error_msg);
			return;
		}

		ASSERT(debug_pack_file);
		
		fprintf(debug_pack_file, string);
		fclose(debug_pack_file);
	#endif
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int default_get_entity_int_value (entity *en, int_types type)
{
	int
		value;

	switch (type)
	{
		////////////////////////////////////////
		case INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_CONFIG_TYPE_UNARMED;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_CONFIG_TYPE_UNARMED;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DAY_SEGMENT_TYPE:
		////////////////////////////////////////
		{
			value = DAY_SEGMENT_TYPE_DAY;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_3D_SHAPE:
		////////////////////////////////////////
		{
			value = OBJECT_3D_INVALID_OBJECT_INDEX;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_CONFIG_TYPE_UNARMED;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DEFAULT_WEAPON_TYPE:
		////////////////////////////////////////
		{
			value = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_DIFFICULTY_LEVEL:
		////////////////////////////////////////
		{
			value = GAME_DIFFICULTY_INVALID;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_ENTITY_SUB_TYPE:
		////////////////////////////////////////
		{
			value = ENTITY_SUB_TYPE_UNKNOWN;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_FORCE:
		////////////////////////////////////////
		{
			value = ENTITY_FORCE_UNKNOWN;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_GUNSHIP_TYPE:
		////////////////////////////////////////
		{
			value = GUNSHIP_TYPE_APACHE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MAX_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_CONFIG_TYPE_UNARMED;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_MIN_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_CONFIG_TYPE_UNARMED;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OBJECT_3D_SHAPE:
		////////////////////////////////////////
		{
			value = OBJECT_3D_INVALID_OBJECT_INDEX;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_OPERATIONAL_STATE:
		////////////////////////////////////////
		{
			value = OPERATIONAL_STATE_UNKNOWN;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_PLAYER:
		////////////////////////////////////////
		{
			value = ENTITY_PLAYER_AI;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_CONFIG_TYPE_UNARMED;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SELECTED_WEAPON:
		////////////////////////////////////////
		{
			value = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_SIDE:
		////////////////////////////////////////
		{
			value = ENTITY_SIDE_NEUTRAL;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_STRATEGY:
		////////////////////////////////////////
		{
			value = STRATEGY_TYPE_ADVANCE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_PRIORITY_TYPE:
		////////////////////////////////////////
		{
			value = TARGET_PRIORITY_UNKNOWN;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_SYMBOL_TYPE:
		////////////////////////////////////////
		{
			value = TARGET_SYMBOL_UNKNOWN;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_TYPE:
		////////////////////////////////////////
		{
			value = TARGET_TYPE_INVALID;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_TARGET_WEATHER_MODE:
		////////////////////////////////////////
		{
			value = WEATHERMODE_INVALID;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_THREAT_TYPE:
		////////////////////////////////////////
		{
			value = THREAT_TYPE_INVALID;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_CONFIG_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_CONFIG_TYPE_UNARMED;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_DECOY_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_DECOY_TYPE_NONE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_GUIDANCE_TYPE:
		////////////////////////////////////////
		{
			value = WEAPON_GUIDANCE_TYPE_NONE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_KILL_CODE:
		////////////////////////////////////////
		{
			value = WEAPON_KILL_CODE_OK;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_WEAPON_SMOKE_TRAIL_TYPE:
		////////////////////////////////////////
		{
			value = ENTITY_SUB_TYPE_NONE;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_X_SECTOR:
		////////////////////////////////////////
		{
			value = MIN_MAP_X_SECTOR;

			break;
		}
		////////////////////////////////////////
		case INT_TYPE_Z_SECTOR:
		////////////////////////////////////////
		{
			value = MIN_MAP_Z_SECTOR;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			value = 0;

			break;
		}
	}

	return (value);
}

/*
   The definition below is used to offer a compile time check for bits packing. It 
   uses the fact that you can't define a zero length array. It is only usable with 
   a num_bits argument of less than 32 since a left shift of one by 32 overflows.
 */
#define COMPILE_ASSERT_PACK(max_value, num_bits, msg) {\
    char l__array[((num_bits) < 32) && (((1 << (num_bits)) - (max_value)) > 0)]; l__array[0] = 0; \
}

void debug_check_pack_types (void)
{
	// arneh - june 2006
	// If you get an assert in this function there is a enum which has more
	// values than bits available for storing it.
	// You can increase the number of bits by changing its corresponding
	// value above.  But this makes this exe incompatible with previous
	// save games.  So if you do it, check if there are any warnings for
	// any other values as well (i.e. they're close to exceeding the limit)
	// and change them at the same time, so that we won't have to change save
	// format too often (you can find warnings in the debug log).  And remember
	// to mention it in the release notes, and on the dev mailing list.

	COMPILE_ASSERT_PACK(NUM_DAY_SEGMENT_TYPES, NUM_DAY_SEGMENT_TYPE_BITS, "Not enough bits, increase definition of second argument");

	COMPILE_ASSERT_PACK(NUM_ENTITY_ATTRIBUTES, NUM_ENTITY_ATTRIBUTE_PACK_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_ENTITY_COMMS_MESSAGES, NUM_ENTITY_COMMS_MESSAGE_PACK_BITS, "Not enough bits, increase definition of second argument");
    COMPILE_ASSERT_PACK(NUM_MESSAGE_CATEGORIES, NUM_RADIO_MESSAGE_TYPE_BITS, "Not enough bits, increase definition of second argument");
    COMPILE_ASSERT_PACK(NUM_ENTITY_SUB_TYPE_FIXED, NUM_ENTITY_SUB_TYPE_FIXED_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_ENTITY_SUB_TYPE_WEAPON_BITS, NUM_ENTITY_SUB_TYPE_WEAPON_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_ENTITY_TYPES, NUM_ENTITY_TYPE_PACK_BITS, "Not enough bits, increase definition of second argument");

	COMPILE_ASSERT_PACK(NUM_FLOAT_TYPES, NUM_FLOAT_TYPE_PACK_BITS, "Not enough bits, increase definition of second argument");
	//COMPILE_ASSERT_PACK(NUM_FORMATION_TYPES, NUM_FORMATION_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_GROUP_MODE_TYPES, NUM_GROUP_MODE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_GUIDE_CRITERIA_TYPES, NUM_GUIDE_CRITERIA_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_GUIDE_POSITION_TYPES, NUM_GUIDE_POSITION_TYPE_BITS, !"Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_GUNSHIP_TYPES, NUM_GUNSHIP_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_INT_TYPES, NUM_INT_TYPE_PACK_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_LIST_TYPES, NUM_LIST_TYPE_PACK_BITS, "Not enough bits, increase definition of second argument");

	COMPILE_ASSERT_PACK(NUM_MESSAGE_TEXT_TYPES, NUM_MESSAGE_TEXT_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_META_EXPLOSION_TYPES, NUM_META_EXPLOSION_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_META_SMOKE_LIST_TYPES, NUM_META_SMOKE_LIST_TYPE_BITS, "Not enough bits, increase definition of second argument"); 
	COMPILE_ASSERT_PACK(NUM_MOVEMENT_TYPES, NUM_MOVEMENT_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_OPERATIONAL_STATE_TYPES, NUM_OPERATIONAL_STATE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_POSITION_TYPES, NUM_POSITION_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_RESUPPLY_SOURCE_TYPES, NUM_RESUPPLY_SOURCE_BITS, "Not enough bits, increase definition of second argument");

	COMPILE_ASSERT_PACK(NUM_SOUND_CHANNEL_TYPES, NUM_SOUND_CHANNEL_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_SOUND_LOCALITY_TYPES, NUM_SOUND_LOCALITY_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_SPEECH_CATEGORY_TYPES, NUM_SPEECH_CATEGORY_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_STRING_TYPES, NUM_STRING_TYPE_PACK_BITS, "Not enough bits, increase definition of second argument");

	COMPILE_ASSERT_PACK(NUM_TASK_COMPLETED_TYPES, NUM_TASK_COMPLETED_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_TASK_ROE_TYPES, NUM_TASK_ROE_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_TASK_STATE_TYPES, NUM_TASK_STATE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_TASK_TARGET_CLASS_TYPES, NUM_TASK_TARGET_CLASS_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_TASK_TARGET_SOURCE_TYPES, NUM_TASK_TARGET_SOURCE_BITS, "Not enough bits, increase definition of second argument");
	//COMPILE_ASSERT_PACK(NUM_TASK_TARGET_TYPES, NUM_TASK_TARGET_TYPE_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_TASK_TERMINATED_TYPES, NUM_TASK_TERMINATED_BITS, "Not enough bits, increase definition of second argument");

	COMPILE_ASSERT_PACK(NUM_VEC3D_TYPES, NUM_VEC3D_TYPE_PACK_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_WAYPOINT_REACHED_TYPES, NUM_WAYPOINT_REACHED_BITS, "Not enough bits, increase definition of second argument");
	COMPILE_ASSERT_PACK(NUM_WEAPON_CONFIG_TYPES, NUM_WEAPON_CONFIG_TYPE_BITS, "Not enough bits, increase definition of second argument");

    COMPILE_ASSERT_PACK(TEXTURE_ANIMATION_INDEX_LAST, NUM_ANIMATED_TEXTURE_BITS, "Not enough bits, increase definition of second argument");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_int_value_default_functions (void)
{
	int
		i,
		j;

	debug_check_pack_types();

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{
		for (j = 0; j < NUM_INT_TYPES; j++)
		{
			fn_set_local_entity_raw_int_value[i][j]									= default_set_entity_int_value;

			fn_set_local_entity_int_value[i][j]											= default_set_entity_int_value;

			fn_set_client_server_entity_int_value[i][j][COMMS_MODEL_SERVER]	= default_set_entity_int_value;

			fn_set_client_server_entity_int_value[i][j][COMMS_MODEL_CLIENT]	= default_set_entity_int_value;

			fn_get_local_entity_int_value[i][j]											= default_get_entity_int_value;
		}
	}

	ASSERT(int_type_database[INT_TYPE_Z_SECTOR].name && strcmp(int_type_database[INT_TYPE_Z_SECTOR].name, "INT_TYPE_Z_SECTOR") == 0);  // if this fails then initialization order and defines differ in number!
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_int_value (entity *en, int_types type, int value)
{
	unsigned int pack_bits;
	
	ASSERT ((type >= 0) && (type < NUM_INT_TYPES));

	pack_bits = int_type_database[type].num_pack_bits;
	ASSERT(pack_bits > 0 && pack_bits <= 32);

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (int_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_INT_VALUE, en, type, value);
	}

	#endif

	switch (int_type_database[type].pack_type)
	{
		////////////////////////////////////////
		case INT_PACK_TYPE_SIGNED:
		////////////////////////////////////////
		{
			int max_val = (1 << (pack_bits - 1)) - 1;
			int min_val = -max_val - 1;
			
			if (pack_bits < 32 && (value > max_val || value < min_val))
			{
				#ifdef DEBUG_PACK_OVERFLOW
					debug_log_pack_overflow("signed int", get_int_type_name(type), pack_bits, value, 0.0);
				#endif
				
				if (value > 0)
					value = max_val;
				else
					value = min_val;
				
				ASSERT(!"Overflow when packing signed int type!");
			}

			pack_signed_data (value, pack_bits);

			break;
		}
		////////////////////////////////////////
		case INT_PACK_TYPE_UNSIGNED:
		////////////////////////////////////////
		{
			if (pack_bits < 32 && value & (0xffffffff << pack_bits))
			{
				#ifdef DEBUG_PACK_OVERFLOW
					debug_log_pack_overflow("unsigned int", get_int_type_name(type), pack_bits, value, 0.0);
				#endif
				
				value = (1 << pack_bits) - 1;
				
				ASSERT(!"Overflow when packing unsigned int type!");
			}
			
			pack_unsigned_data (value, pack_bits);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid int pack type = %d", int_type_database[type].pack_type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int unpack_int_value (entity *en, int_types type)
{
	int
		value;

	ASSERT ((type >= 0) && (type < NUM_INT_TYPES));

	switch (int_type_database[type].pack_type)
	{
		////////////////////////////////////////
		case INT_PACK_TYPE_SIGNED:
		////////////////////////////////////////
		{
			value = unpack_signed_data (int_type_database[type].num_pack_bits);

			break;
		}
		////////////////////////////////////////
		case INT_PACK_TYPE_UNSIGNED:
		////////////////////////////////////////
		{
			value = unpack_unsigned_data (int_type_database[type].num_pack_bits);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid int pack type = %d", int_type_database[type].pack_type);

			break;
		}
	}

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (int_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_INT_VALUE, en, type, value);
	}

	#endif

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_int_type (int_types type)
{
	ASSERT ((type >= 0) && (type < NUM_INT_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (int_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_INT_TYPE, NULL, type);
	}

	#endif

	ASSERT(!(type >> NUM_INT_TYPE_PACK_BITS));

	pack_unsigned_data (type, NUM_INT_TYPE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int_types unpack_int_type (void)
{
	int_types
		type;

	type = unpack_unsigned_data (NUM_INT_TYPE_PACK_BITS);

	ASSERT ((type >= 0) && (type < NUM_INT_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (int_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_INT_TYPE, NULL, type);
	}

	#endif

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
