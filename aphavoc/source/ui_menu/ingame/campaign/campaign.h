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

#define CAMPAIGN_INSET_PAGE_X1	0.22
#define CAMPAIGN_INSET_PAGE_Y1	0.048
#define CAMPAIGN_INSET_PAGE_X2	1.0
#define CAMPAIGN_INSET_PAGE_Y2	0.78

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CAMPAIGN_PAGES
{
	CAMPAIGN_PAGE_BASE,
	CAMPAIGN_PAGE_BRIEFING,
	CAMPAIGN_PAGE_DEBRIEFING,
	CAMPAIGN_PAGE_GROUP,
	CAMPAIGN_PAGE_LOG,
	CAMPAIGN_PAGE_MAP,
	CAMPAIGN_PAGE_STATS,
	CAMPAIGN_PAGE_CHAT,
	CAMPAIGN_PAGE_SAVE,
	CAMPAIGN_PAGE_WEAPON_LOADING,

	NUM_CAMPAIGN_PAGES
};

typedef enum CAMPAIGN_PAGES campaign_pages;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CAMPAIGN_COMPLETED_TYPES
{
	CAMPAIGN_COMPLETED_FALSE,
	CAMPAIGN_COMPLETED_OBJECTIVES,
	CAMPAIGN_COMPLETED_VALID_GUNSHIPS,

	NUM_CAMPAIGN_COMPLETED_TYPES
};

typedef enum CAMPAIGN_COMPLETED_TYPES campaign_completed_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern ui_object
	*campaign_screen,
	*campaign_page [NUM_CAMPAIGN_PAGES];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_main_campaign_screen (void);

extern void deinitialise_main_campaign_screen (void);

extern void display_campaign_page (campaign_pages page, int index, int add_to_history);

extern campaign_pages get_current_campaign_page (void);

extern void initialise_campaign_screen (void);

extern void deinitialise_campaign_screen (void);

extern void setup_campaign_quit_mission_dialog (void);

extern void setup_campaign_quit_campaign_dialog (void);

extern void setup_campaign_completed_dialog (entity_sides side, campaign_completed_types complete);

extern void campaign_completed (entity_sides side, campaign_completed_types complete);

extern void campaign_screen_show_external_view_entity (event *ev);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ca_base.h"

#include "ca_brief.h"

#include "ca_chat.h"

#include "ca_dbf.h"

#include "ca_fsmap.h"

#include "ca_group.h"

#include "ca_hist.h"

#include "ca_info.h"

#include "ca_list.h"

#include "ca_log.h"

#include "ca_map.h"

#include "ca_menu.h"

#include "ca_msgs.h"

#include "ca_save.h"

#include "ca_selct.h"

#include "ca_sort.h"

#include "ca_stat.h"

#include "ca_wload.h"

#include "ca_3d.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


