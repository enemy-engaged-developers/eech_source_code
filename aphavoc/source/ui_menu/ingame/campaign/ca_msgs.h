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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CAMPAIGN_SCREEN_MESSAGE_TARGETS
{
	CAMPAIGN_SCREEN_TARGET_MISSION_LIST,
	CAMPAIGN_SCREEN_TARGET_GROUP_LIST,
	CAMPAIGN_SCREEN_TARGET_BASE_LIST,

	CAMPAIGN_SCREEN_TARGET_BASE_PAGE,
	CAMPAIGN_SCREEN_TARGET_BRIEFING_PAGE,
	CAMPAIGN_SCREEN_TARGET_DEBRIEFING_PAGE,
	CAMPAIGN_SCREEN_TARGET_GROUP_PAGE,
	CAMPAIGN_SCREEN_TARGET_LOG_PAGE,
	CAMPAIGN_SCREEN_TARGET_CHAT_PAGE,
	CAMPAIGN_SCREEN_TARGET_STATS_PAGE,
	CAMPAIGN_SCREEN_TARGET_WEAPON_LOADING_PAGE,

	CAMPAIGN_SCREEN_TARGET_SELECTIONS,
	CAMPAIGN_SCREEN_TARGET_HISTORY,

	NUM_CAMPAIGN_SCREEN_MESSAGE_TARGETS
};

typedef enum CAMPAIGN_SCREEN_MESSAGE_TARGETS campaign_screen_message_targets;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CAMPAIGN_SCREEN_MESSAGES
{
	CAMPAIGN_SCREEN_MISSION_CREATED,
	CAMPAIGN_SCREEN_MISSION_ASSIGNED,
	CAMPAIGN_SCREEN_MISSION_COMPLETED,
	CAMPAIGN_SCREEN_MISSION_DESTROYED,

	CAMPAIGN_SCREEN_GROUP_CREATED,
	CAMPAIGN_SCREEN_GROUP_DESTROYED,
	CAMPAIGN_SCREEN_GROUP_CHANGE_BASE,
	CAMPAIGN_SCREEN_GROUP_ADD_MEMBER,
	CAMPAIGN_SCREEN_GROUP_REMOVE_MEMBER,

	CAMPAIGN_SCREEN_BASE_CREATED,
	CAMPAIGN_SCREEN_BASE_DESTROYED,

	CAMPAIGN_SCREEN_PLAYER_LEAVE_MISSION,

	CAMPAIGN_SCREEN_NEW_MESSAGE,

	CAMPAIGN_SCREEN_FORCE_UPDATE,

   NUM_CAMPAIGN_SCREEN_MESSAGES
};

typedef enum CAMPAIGN_SCREEN_MESSAGES campaign_screen_messages;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int notify_campaign_screen (campaign_screen_messages message, entity *sender);

extern void initialise_campaign_screen_message_responses (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int (*campaign_screen_message_responses[NUM_CAMPAIGN_SCREEN_MESSAGE_TARGETS][NUM_CAMPAIGN_SCREEN_MESSAGES]) (campaign_screen_messages message, entity *sender);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
