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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int notify_campaign_screen (campaign_screen_messages message, entity *sender)
{
	#if !DEMO_VERSION

	int
		loop;

	ASSERT ((message >= 0) && (message < NUM_CAMPAIGN_SCREEN_MESSAGES));

	if (get_game_status () != GAME_STATUS_INITIALISED)
	{
		return FALSE;
	}

	if (
			(get_game_type () != GAME_TYPE_CAMPAIGN) &&
			(get_game_type () != GAME_TYPE_SKIRMISH)
		)
	{
		return FALSE;
	}

	for (loop = 0; loop < NUM_CAMPAIGN_SCREEN_MESSAGE_TARGETS; loop ++)
	{
		campaign_screen_message_responses[loop][message] (message, sender);
	}

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int (*campaign_screen_message_responses[NUM_CAMPAIGN_SCREEN_MESSAGE_TARGETS][NUM_CAMPAIGN_SCREEN_MESSAGES]) (campaign_screen_messages message, entity *sender);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int default_message_response (campaign_screen_messages message, entity *sender)
{
	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_campaign_screen_message_responses (void)
{
	int
		i,
		j;

	//
	// set default message responses
	//

	for (i = 0; i < NUM_CAMPAIGN_SCREEN_MESSAGE_TARGETS; i ++)
	{
		for (j = 0; j < NUM_CAMPAIGN_SCREEN_MESSAGES; j ++)
		{
			campaign_screen_message_responses[i][j] = default_message_response;
		}
	}

	//
	// overload default message responses
	//

	overload_mission_list_message_responses ();

	overload_group_list_message_responses ();

	overload_base_list_message_responses ();


	overload_base_page_message_responses ();

	overload_briefing_page_message_responses (); 

	overload_debriefing_page_message_responses ();

	overload_group_page_message_responses ();

	overload_log_page_message_responses ();

	overload_chat_page_message_responses ();

	overload_stats_page_message_responses ();

	overload_weapon_loading_page_message_responses ();


	overload_campaign_selection_message_responses ();

	overload_campaign_history_message_responses ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
