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

#define DEFAULT_GROUP_ASSISTANCE_REQUEST_TIMER	(ONE_MINUTE + (sfrand1 () * 20.0))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GROUP_CALLSIGN_TYPES
{
	GROUP_CALLSIGN_ANGEL,
	GROUP_CALLSIGN_APOLLO,
	GROUP_CALLSIGN_ARCHER,
	GROUP_CALLSIGN_BANSHEE,
	GROUP_CALLSIGN_BLOODHOUND,
	GROUP_CALLSIGN_BULLDOG,
	GROUP_CALLSIGN_CHARGER,
	GROUP_CALLSIGN_CHEETAH,
	GROUP_CALLSIGN_CHIEFTAIN,
	GROUP_CALLSIGN_COBRA,
	GROUP_CALLSIGN_COMET,
	GROUP_CALLSIGN_CONDOR,
	GROUP_CALLSIGN_COUGAR,
	GROUP_CALLSIGN_COWBOY,
	GROUP_CALLSIGN_DARKHORSE,
	GROUP_CALLSIGN_DEMON,
	GROUP_CALLSIGN_DODGER,
	GROUP_CALLSIGN_DRAGON,
	GROUP_CALLSIGN_EAGLE,
	GROUP_CALLSIGN_EIGHTBALL,
	GROUP_CALLSIGN_FARSIGHT,
	GROUP_CALLSIGN_FIREBALL,
	GROUP_CALLSIGN_FIREBIRD,
	GROUP_CALLSIGN_FIREFOX,
	GROUP_CALLSIGN_FREELANCER,
	GROUP_CALLSIGN_GATOR,
	GROUP_CALLSIGN_GAUNTLET,
	GROUP_CALLSIGN_GHOSTRIDER,
	GROUP_CALLSIGN_GLADIATOR,
	GROUP_CALLSIGN_GOLIATH,
	GROUP_CALLSIGN_GOOSE,
	GROUP_CALLSIGN_HAWKEYE,
	GROUP_CALLSIGN_HELLCAT,
	GROUP_CALLSIGN_HUNTER,
	GROUP_CALLSIGN_JAGUAR,
	GROUP_CALLSIGN_JESTER,
	GROUP_CALLSIGN_JUPITER,
	GROUP_CALLSIGN_JUGGERNAUT,
	GROUP_CALLSIGN_KESTREL,
	GROUP_CALLSIGN_LANCER,
	GROUP_CALLSIGN_LIMA,
	GROUP_CALLSIGN_MANIAC,
	GROUP_CALLSIGN_MANTIS,
	GROUP_CALLSIGN_MAULER,
	GROUP_CALLSIGN_MERCURY,
	GROUP_CALLSIGN_MERLIN,
	GROUP_CALLSIGN_MILKMAN,
	GROUP_CALLSIGN_MUSTANG,
	GROUP_CALLSIGN_NIGHTMARE,
	GROUP_CALLSIGN_PANTHER,
	GROUP_CALLSIGN_PATRIOT,
	GROUP_CALLSIGN_PHANTOM,
	GROUP_CALLSIGN_PHOENIX,
	GROUP_CALLSIGN_PREACHER,
	GROUP_CALLSIGN_PYTHON,
	GROUP_CALLSIGN_RAPTOR,
	GROUP_CALLSIGN_RATTLESNAKE,
	GROUP_CALLSIGN_RAZORBACK,
	GROUP_CALLSIGN_RAZORWORKS,
	GROUP_CALLSIGN_REAPER,
	GROUP_CALLSIGN_RENEGADE,
	GROUP_CALLSIGN_SABRE,
	GROUP_CALLSIGN_SAVAGE,
	GROUP_CALLSIGN_SHADOW,
	GROUP_CALLSIGN_SHERIFF,
	GROUP_CALLSIGN_SHOGUN,
	GROUP_CALLSIGN_SNOWBALL,
	GROUP_CALLSIGN_SPARTAKUS,
	GROUP_CALLSIGN_SPECTRUM,
	GROUP_CALLSIGN_STALKER,
	GROUP_CALLSIGN_STINGRAY,
	GROUP_CALLSIGN_STRIKER,
	GROUP_CALLSIGN_SUNDOWN,
	GROUP_CALLSIGN_SWAMP_FOX,
	GROUP_CALLSIGN_TEMPEST,
	GROUP_CALLSIGN_TIGER_SHARK,
	GROUP_CALLSIGN_TOUCHDOWN,
	GROUP_CALLSIGN_VAMPIRE,
	GROUP_CALLSIGN_VERTIGO,
	GROUP_CALLSIGN_VIGILANTE,
	GROUP_CALLSIGN_VIKING,
	GROUP_CALLSIGN_VIPER,
	GROUP_CALLSIGN_VOODOO,
	GROUP_CALLSIGN_VULCAN,
	GROUP_CALLSIGN_VULTURE,
	GROUP_CALLSIGN_WARLOCK,
	GROUP_CALLSIGN_WARLORD,
	GROUP_CALLSIGN_WARRIOR,
	GROUP_CALLSIGN_WILDCAT,
	GROUP_CALLSIGN_WOLFPACK,
	NUM_GROUP_CALLSIGNS
};

typedef enum GROUP_CALLSIGN_TYPES group_callsign_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GROUP_CALLSIGN_NAME_TYPE
{

	unsigned char
		*callsign;

	char
		side [NUM_ENTITY_SIDES];
};

typedef struct GROUP_CALLSIGN_NAME_TYPE group_callsign_name_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern group_callsign_name_type
	group_callsign_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GROUP_FRONTLINE_FLAG_TYPES
{
	GROUP_FRONTLINE_FLAG_NONE,
	GROUP_FRONTLINE_FLAG_PRIMARY,
	GROUP_FRONTLINE_FLAG_SECONDARY,
	GROUP_FRONTLINE_FLAG_ARTILLERY,

	NUM_GROUP_FRONTLINE_FLAG_TYPES
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct GROUP
{
	entity_sub_types
		sub_type;

	list_root
		member_root,
		guide_stack_root,
		task_dependent_root;

	list_link
		group_link,
		division_link,
		pilot_lock_link,
		registry_link,
		task_dependent_link,
		update_link;

	list_types
		group_list_type;

	float
		sleep,
		assist_timer;

	supply_type
		supplies;

	unsigned int
		alive								: NUM_ALIVE_BITS,
		engage_enemy					: NUM_ENGAGE_ENEMY_BITS,
		group_callsign					: NUM_GROUP_CALLSIGN_BITS,
		group_formation				: NUM_GROUP_FORMATION_BITS,
		kills								: NUM_KILLS_BITS,
		losses							: NUM_LOSSES_BITS,
		member_count					: NUM_MEMBER_COUNT_BITS,
		multiplayer_group				: NUM_MULTIPLAYER_GROUP_BITS,
		route_node						: NUM_ROUTE_NODE_BITS,
		side								: NUM_SIDE_BITS,
		unique_id						: NUM_UNIQUE_ID_BITS,
		verbose_operational_state	: NUM_VERBOSE_OPERATIONAL_STATE_BITS;

	unsigned char
		division_name [STRING_TYPE_DIVISION_NAME_MAX_LENGTH + 1];
};

typedef struct GROUP group;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "gp_creat.h"

#include "gp_dbase.h"

#include "gp_dstry.h"

#include "gp_int.h"

#include "gp_float.h"

#include "gp_funcs.h"

#include "gp_list.h"

#include "gp_msgs.h"

#include "gp_pack.h"

#include "gp_ptr.h"

#include "gp_str.h"

#include "gp_updt.h"

#include "gp_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int get_local_group_member_count (entity *group);

extern int get_local_group_member_max_formation_position (entity *group);

extern int assess_group_task_locality_factor (entity *group_en, entity *task_en, float *return_distance);

extern entity *get_group_at_road_node (int node);

extern int amalgamate_groups (entity *receiving_group, entity *donating_group);

extern void set_group_verbose_operational_state (entity *en, int state);

extern int get_group_suitable_for_player (entity *group, entity *pilot);

extern void assess_group_supplies (entity *en);

extern void set_group_member_numbers (entity *en);

extern void set_group_formation_positions (entity *en);

extern void group_return_to_base (entity *en);

extern void group_terminate_all_tasks (entity *en);

extern void group_kill_all_members (entity *en);

extern void group_destroy_all_members (entity *en);

extern void kill_client_server_group_entity (entity *en);

extern int create_group_emergency_transfer_task (entity *en);

extern int check_group_task_type (entity *group, entity_sub_types task_type);

extern int check_group_task_type_valid_members (entity *group, entity_sub_types task_type);

extern int group_task_specific_retaliation_checks (entity *group, entity *aggressor, int assisted);

extern void initialise_group_callsign_database (void);

extern int assign_group_callsign (entity *en);

extern void free_group_callsign (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
