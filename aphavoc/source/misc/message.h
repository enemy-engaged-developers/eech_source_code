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

enum MESSAGE_CATEGORIES
{

	MESSAGE_NONE,

	MESSAGE_DESTINATION_LIST,

	/////////////////////////////////////////////////////////////////
	//
	// destinations
	//
	/////////////////////////////////////////////////////////////////

	MESSAGE_GROUP_LIST,

	MESSAGE_WINGMAN_LIST,

	MESSAGE_LOCAL_BASE_LIST,

	MESSAGE_PILOT_LIST,

	MESSAGE_FORMATION_LIST,

	/////////////////////////////////////////////////////////////////
	//
	// messages
	//
	/////////////////////////////////////////////////////////////////

	// group

	MESSAGE_GROUP_ROW_LEFT, 
	MESSAGE_GROUP_ROW_RIGHT,
	MESSAGE_GROUP_ECHELON_LEFT, 	
	MESSAGE_GROUP_ECHELON_RIGHT, 
	MESSAGE_GROUP_COLUMN, 		
	MESSAGE_GROUP_WEDGE,
   //VJ 060212 for Maverick, added three formations, needs ne FORMS.DAt
   MESSAGE_GROUP_DIAMOND,  
   MESSAGE_GROUP_STAGGERED_TRAIL_LEFT,
   MESSAGE_GROUP_STAGGERED_TRAIL_RIGHT,
        

	// wingman

	MESSAGE_WINGMAN_SELECT,

	MESSAGE_WINGMAN_ATTACK_MY_TARGET,
	MESSAGE_WINGMAN_HELP_ME,
	MESSAGE_WINGMAN_WEAPONS_HOLD,
	MESSAGE_WINGMAN_WEAPONS_FREE,

	MESSAGE_WINGMAN_BOB_UP,
	MESSAGE_WINGMAN_ATTACK_PFZ,

	MESSAGE_WINGMAN_HOLD_POSITION,
	MESSAGE_WINGMAN_REJOIN_FORMATION,

	MESSAGE_WINGMAN_REQUEST_TARGET_LIST,
	MESSAGE_WINGMAN_KEYBOARD,

	MESSAGE_WINGMAN_REQUEST_STATUS,

	MESSAGE_WINGMAN_RETURN_TO_BASE,

	// local base

	MESSAGE_LOCAL_BASE_REQUEST_AIRSTRIKE,
	MESSAGE_LOCAL_BASE_REQUEST_ARTILLERY,
	MESSAGE_LOCAL_BASE_REQUEST_ASSISTANCE,
	MESSAGE_LOCAL_BASE_TRANSMIT_RECON,
	MESSAGE_LOCAL_BASE_CAMCOM_MESSAGE, // Jabberwock 031119 CamCom MP compatible

	// pilot

	MESSAGE_PILOT_KEYBOARD,
	
	// GCsDriver  08-12-2007 , if put to other destinations above the normal menu entries get irritated
	MESSAGE_CHANNEL_LIST,

	// GCsDriver  08-12-2007
	MESSAGE_ATC,
	MESSAGE_FAC,
	MESSAGE_GC,
	MESSAGE_WM,

	/////////////////////////////////////////////////////////////////

	NUM_MESSAGE_CATEGORIES
};

typedef enum MESSAGE_CATEGORIES message_categories;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MESSAGE_TEXT_TYPES
{
	// remember to update message_text_info in message.c when changing this!
	MESSAGE_TEXT_SYSTEM_NEW_PILOT,
	MESSAGE_TEXT_SYSTEM_ENTITY_KILLED,
	MESSAGE_TEXT_SYSTEM_ENTITY_UNDER_ATTACK,
	MESSAGE_TEXT_SYSTEM_RECON_DATA,
	MESSAGE_TEXT_SYSTEM_TASK_COMPLETED,
	MESSAGE_TEXT_SYSTEM_KEYSITE_CAPTURED,
	MESSAGE_TEXT_SYSTEM_KEYSITE_DESTROYED,
	MESSAGE_WINGMAN_STATUS_REPORT,

	MESSAGE_TEXT_PILOT_STRING,
	MESSAGE_TEXT_WINGMAN_STRING,
	MESSAGE_TEXT_SHORT_WINGMAN_STRING,
	MESSAGE_TEXT_LOCAL_MESSAGE,

	NUM_MESSAGE_TEXT_TYPES
};

typedef enum MESSAGE_TEXT_TYPES message_text_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct MESSAGE_TEXT_INFO_TYPE
{
	unsigned char
		send_string		: 1,
		echo				: 1,
		skip_queue		: 1;

	float
		display_time;
};

typedef struct MESSAGE_TEXT_INFO_TYPE message_text_info_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const message_text_info_type
	message_text_info [NUM_MESSAGE_TEXT_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void display_in_flight_messages (void);

extern int message_text_type_send_string (message_text_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
