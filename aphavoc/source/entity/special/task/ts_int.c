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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_local_int_value (entity *en, int_types type, int value)
{
   task
      *raw = nullptr;

   #if DEBUG_MODULE

   debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_INT_VALUE, en, type, value);

   #endif

   raw = (task *) get_local_entity_data (en);

   switch (type)
   {
      ////////////////////////////////////////
      case INT_TYPE_AWARDED_MEDALS:
      ////////////////////////////////////////
      {
         raw->awarded_medals = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_AWARDED_PROMOTION:
      ////////////////////////////////////////
      {
         raw->awarded_promotion = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_CRITICAL_TASK:
      ////////////////////////////////////////
      {
         raw->critical_task = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_ENTITY_SUB_TYPE:
      ////////////////////////////////////////
      {
         raw->sub_type = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_KILLS:
      ////////////////////////////////////////
      {
         raw->kills = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_LOSSES:
      ////////////////////////////////////////
      {
         raw->losses = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_MOVEMENT_TYPE:
      ////////////////////////////////////////
      {
         raw->movement_type = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_PLAYER_TASK:
      ////////////////////////////////////////
      {
         raw->player_task = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_ROUTE_CHECK_SUM:
      ////////////////////////////////////////
      {
         raw->route_check_sum = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_ROUTE_LENGTH:
      ////////////////////////////////////////
      {
         raw->route_length = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_SIDE:
      ////////////////////////////////////////
      {
         raw->side = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_COMPLETED:
      ////////////////////////////////////////
      {
         raw->task_completed = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_DIFFICULTY:
      ////////////////////////////////////////
      {
         raw->difficulty = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_ID:
      ////////////////////////////////////////
      {
         raw->task_id = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_SCORE:
      ////////////////////////////////////////
      {
         raw->task_score = value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_STATE:
      ////////////////////////////////////////
      {
         raw->task_state = (task_state_types) value;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_TERMINATED:
      ////////////////////////////////////////
      {
         raw->task_terminated = (task_terminated_types) value;

         break;
      }
      ////////////////////////////////////////
      default:
      ////////////////////////////////////////
      {
         debug_fatal_invalid_int_type (en, type);

         break;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_remote_int_value (entity *en, int_types type, int value)
{
   #if DEBUG_MODULE

   debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_INT_VALUE, en, type, value);

   #endif

   transmit_entity_comms_message (ENTITY_COMMS_INT_VALUE, en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_server_int_value (entity *en, int_types type, int value)
{
   validate_client_server_local_fn ();

   set_local_int_value (en, type, value);

   validate_client_server_remote_fn ();

   set_remote_int_value (en, type, value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_client_int_value (entity *en, int_types type, int value)
{
   if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
   {
      validate_client_server_remote_fn ();

      set_remote_int_value (en, type, value);
   }
   else
   {
      validate_client_server_local_fn ();

      set_local_int_value (en, type, value);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_local_int_value (entity *en, int_types type)
{
   task
      *raw = nullptr;

   int
      value;

   raw = (task *) get_local_entity_data (en);

   switch (type)
   {
      ////////////////////////////////////////
      case INT_TYPE_ASSESS_LANDING:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].assess_landing;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_AWARDED_MEDALS:
      ////////////////////////////////////////
      {
         value = raw->awarded_medals;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_AWARDED_PROMOTION:
      ////////////////////////////////////////
      {
         value = raw->awarded_promotion;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_CRITICAL_TASK:
      ////////////////////////////////////////
      {
         value = raw->critical_task;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_DEFAULT_ENGAGE_ENEMY:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].engage_enemy;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_DELAY_TASK_ASSIGNMENT:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].delay_task_assignment;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_ENTITY_SUB_TYPE:
      ////////////////////////////////////////
      {
         value = raw->sub_type;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_KILLS:
      ////////////////////////////////////////
      {
         value = raw->kills;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_LOSSES:
      ////////////////////////////////////////
      {
         value = raw->losses;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_MAP_ICON:
      ////////////////////////////////////////
      {
         value = MAP_ICON_MISSION;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_MINIMUM_MEMBER_COUNT:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].minimum_member_count;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_MOVEMENT_TYPE:
      ////////////////////////////////////////
      {
         value = raw->movement_type;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_PERFORM_DEBRIEF:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].perform_debrief;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_PLAYER_TASK:
      ////////////////////////////////////////
      {
         value = raw->player_task;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_POINTS_VALUE:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_completed_score;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_PRIMARY_TASK:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].primary_task;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_ROUTE_CHECK_SUM:
      ////////////////////////////////////////
      {
         value = raw->route_check_sum;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_ROUTE_LENGTH:
      ////////////////////////////////////////
      {
         value = raw->route_length;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_RULES_OF_ENGAGEMENT:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].rules_of_engagement;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_SIDE:
      ////////////////////////////////////////
      {
         value = raw->side;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_SOLO_TASK:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].solo_task;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_CATEGORY:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_category;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_COMPLETED:
      ////////////////////////////////////////
      {
         value = raw->task_completed;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_DIFFICULTY:
      ////////////////////////////////////////
      {
         value = raw->difficulty;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_ID:
      ////////////////////////////////////////
      {
         value = raw->task_id;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_OBJECTIVE_PREVIEW_TYPE:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_objective_preview;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_PASS_PERCENTAGE_PARTIAL:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_pass_percentage_partial;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_PASS_PERCENTAGE_SUCCESS:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_pass_percentage_success;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_ROUTE_SEARCH:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_route_search;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_SCORE:
      ////////////////////////////////////////
      {
         value = raw->task_score;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_STATE:
      ////////////////////////////////////////
      {
         value = raw->task_state;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_TARGET_CLASS:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_default_target_class;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_TARGET_SOURCE:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_default_target_source;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_TARGET_TYPE:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].task_default_target_type;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_TASK_TERMINATED:
      ////////////////////////////////////////
      {
         value = raw->task_terminated;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_VISIBLE_TASK:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].visible_task;

         break;
      }
      ////////////////////////////////////////
      case INT_TYPE_WAIT_FOR_END_TASK:
      ////////////////////////////////////////
      {
         value = task_database [raw->sub_type].wait_for_end_task;

         break;
      }
      ////////////////////////////////////////
      default:
      ////////////////////////////////////////
      {
         debug_fatal_invalid_int_type (en, type);

         break;
      }
   }

   return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_task_int_value_functions (void)
{
   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_ASSESS_LANDING]                  		= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_MEDALS]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_MEDALS]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_MEDALS][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_MEDALS][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_MEDALS]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_PROMOTION]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_PROMOTION]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_PROMOTION][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_PROMOTION][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_AWARDED_PROMOTION]								= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_CRITICAL_TASK]								= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_CRITICAL_TASK]								= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_CRITICAL_TASK][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_CRITICAL_TASK][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_CRITICAL_TASK]								= get_local_int_value;

	fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_DEFAULT_ENGAGE_ENEMY]             		= get_local_int_value;

   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_DELAY_TASK_ASSIGNMENT]            		= get_local_int_value;

   fn_set_local_entity_raw_int_value      [ENTITY_TYPE_TASK][INT_TYPE_ENTITY_SUB_TYPE]                      = set_local_int_value;
   fn_set_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_ENTITY_SUB_TYPE]                      = set_local_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_SERVER]  = set_server_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_ENTITY_SUB_TYPE][COMMS_MODEL_CLIENT]  = set_client_int_value;
   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_ENTITY_SUB_TYPE]                  		= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_KILLS]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_KILLS]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_KILLS][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_KILLS][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_KILLS]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_LOSSES]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_LOSSES]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_LOSSES][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_LOSSES][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_LOSSES]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_MAP_ICON]								= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_MINIMUM_MEMBER_COUNT]				= get_local_int_value;

   fn_set_local_entity_raw_int_value      [ENTITY_TYPE_TASK][INT_TYPE_MOVEMENT_TYPE]                      		= set_local_int_value;
   fn_set_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_MOVEMENT_TYPE]                      		= set_local_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_MOVEMENT_TYPE][COMMS_MODEL_SERVER] 		= set_server_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_MOVEMENT_TYPE][COMMS_MODEL_CLIENT] 		= set_client_int_value;
   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_MOVEMENT_TYPE]                  			= get_local_int_value;

   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_PERFORM_DEBRIEF]                  			= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_PLAYER_TASK]										= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_PLAYER_TASK]										= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_PLAYER_TASK][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_PLAYER_TASK][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_PLAYER_TASK]										= get_local_int_value;

   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_POINTS_VALUE] 					    		= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_PRIMARY_TASK]										= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_CHECK_SUM]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_CHECK_SUM]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_CHECK_SUM][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_CHECK_SUM][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_CHECK_SUM]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_LENGTH]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_LENGTH]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_LENGTH][COMMS_MODEL_SERVER]		= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_LENGTH][COMMS_MODEL_CLIENT]		= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_ROUTE_LENGTH]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_RULES_OF_ENGAGEMENT]						= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_SIDE]											= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_SIDE]											= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_SIDE][COMMS_MODEL_SERVER]					= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_SIDE][COMMS_MODEL_CLIENT]					= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_SIDE]											= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_SOLO_TASK]										= get_local_int_value;

   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_CATEGORY]                  		= get_local_int_value;

   fn_set_local_entity_raw_int_value      [ENTITY_TYPE_TASK][INT_TYPE_TASK_COMPLETED]                     	= set_local_int_value;
   fn_set_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_COMPLETED]                     	= set_local_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_TASK_COMPLETED][COMMS_MODEL_SERVER] 	= set_server_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_TASK_COMPLETED][COMMS_MODEL_CLIENT] 	= set_client_int_value;
   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_COMPLETED]                  		= get_local_int_value;

   fn_set_local_entity_raw_int_value      [ENTITY_TYPE_TASK][INT_TYPE_TASK_DIFFICULTY]                      = set_local_int_value;
   fn_set_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_DIFFICULTY]                      = set_local_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_TASK_DIFFICULTY][COMMS_MODEL_SERVER]  = set_server_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_TASK_DIFFICULTY][COMMS_MODEL_CLIENT]  = set_client_int_value;
   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_DIFFICULTY]                  		= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_TASK_ID]										= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_ID]										= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_TASK_ID][COMMS_MODEL_SERVER]				= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_TASK_ID][COMMS_MODEL_CLIENT]				= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_ID]										= get_local_int_value;

   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_OBJECTIVE_PREVIEW_TYPE]     		= get_local_int_value;

   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_PASS_PERCENTAGE_PARTIAL]     		= get_local_int_value;

   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_PASS_PERCENTAGE_SUCCESS]     		= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_ROUTE_SEARCH]							= get_local_int_value;

   fn_set_local_entity_raw_int_value      [ENTITY_TYPE_TASK][INT_TYPE_TASK_SCORE]                     		= set_local_int_value;
   fn_set_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_SCORE]                     		= set_local_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_TASK_SCORE][COMMS_MODEL_SERVER] 		= set_server_int_value;
   fn_set_client_server_entity_int_value  [ENTITY_TYPE_TASK][INT_TYPE_TASK_SCORE][COMMS_MODEL_CLIENT] 		= set_client_int_value;
   fn_get_local_entity_int_value          [ENTITY_TYPE_TASK][INT_TYPE_TASK_SCORE]                  			= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_TASK_STATE]									= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_STATE]									= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_TASK_STATE][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_TASK_STATE][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_STATE]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_TARGET_CLASS]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_TARGET_SOURCE]									= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_TARGET_TYPE]									= get_local_int_value;

	fn_set_local_entity_raw_int_value		[ENTITY_TYPE_TASK][INT_TYPE_TASK_TERMINATED]										= set_local_int_value;
	fn_set_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_TERMINATED]										= set_local_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_TASK_TERMINATED][COMMS_MODEL_SERVER]			= set_server_int_value;
	fn_set_client_server_entity_int_value	[ENTITY_TYPE_TASK][INT_TYPE_TASK_TERMINATED][COMMS_MODEL_CLIENT]			= set_client_int_value;
	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_TASK_TERMINATED]										= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_VISIBLE_TASK]											= get_local_int_value;

	fn_get_local_entity_int_value				[ENTITY_TYPE_TASK][INT_TYPE_WAIT_FOR_END_TASK]									= get_local_int_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
