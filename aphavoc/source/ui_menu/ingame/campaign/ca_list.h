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

#define CAMPAIGN_LIST_TITLE_FONT UI_FONT_ARIAL_18

#define CAMPAIGN_LIST_SUB_TITLE_FONT UI_FONT_ARIAL_16

#define CAMPAIGN_LIST_SUB_SUB_TITLE_FONT UI_FONT_ITALIC_ARIAL_16

#define CAMPAIGN_LIST_ITEM_FONT UI_FONT_ITALIC_ARIAL_16

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMMON_LIST_MODES
{
	COMMON_LIST_MODE_MISSION,
	COMMON_LIST_MODE_GROUP,
	COMMON_LIST_MODE_BASE,

	NUM_COMMON_LIST_MODES
};

typedef enum COMMON_LIST_MODES common_list_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMMON_LIST_TEXT_TYPES
{
	COMMON_LIST_TEXT_AVAILABLE,
	COMMON_LIST_TEXT_BUSY,
	COMMON_LIST_TEXT_COMPLETE,
	COMMON_LIST_TEXT_UNAVAILABLE,

	NUM_COMMON_TEXT_TYPES
};

typedef enum COMMON_LIST_TEXT_TYPES common_list_text_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern ui_object
	*common_list [NUM_COMMON_LIST_MODES];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_campaign_screen_list_objects (void);

extern void add_mission_to_common_list (entity *en, int text_type);

extern void add_group_to_common_list (entity *en, int text_type);

extern void add_base_to_common_list (entity *en, int text_type);

extern void show_base_list (ui_object *obj, void *arg);

extern void show_group_list (ui_object *obj, void *arg);

extern void show_mission_list (ui_object *obj, void *arg);

extern void update_campaign_screen_list_objects (void);

extern void define_campaign_screen_list_objects (void);

extern void undefine_campaign_screen_list_objects (void);

extern void set_mission_filter (int index);

extern void set_group_filter (int index);

extern int get_current_list_mode (void);

extern int get_mission_sort_mode (void);

extern int get_group_sort_mode (void);

extern int get_base_sort_mode (void);

extern void set_common_list_available_only_state (int flag);

extern int get_common_list_available_only_state (void);

extern void overload_mission_list_message_responses (void);

extern void overload_group_list_message_responses (void);

extern void overload_base_list_message_responses (void);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

