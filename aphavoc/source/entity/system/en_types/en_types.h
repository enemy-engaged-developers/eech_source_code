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

#ifdef NO_ENTITY_SYMBOLS

#define ENTITY_STRUCTURE_ALL_DEBUG_INFO	0

#define ENTITY_STRUCTURE_AI_DEBUG_INFO		0

#else

#define ENTITY_STRUCTURE_ALL_DEBUG_INFO	1

#define ENTITY_STRUCTURE_AI_DEBUG_INFO		0

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ENTITY_TYPE_DONT_CARE			(-1)

#define NUM_ENTITY_TYPE_PACK_BITS	(6)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_TYPES
{
	ENTITY_TYPE_UNKNOWN,
	ENTITY_TYPE_ANTI_AIRCRAFT,
	ENTITY_TYPE_BRIDGE,
	ENTITY_TYPE_CAMERA,
	ENTITY_TYPE_CARGO,
	ENTITY_TYPE_CITY,
	ENTITY_TYPE_CITY_BUILDING,
	ENTITY_TYPE_CRATER,
	ENTITY_TYPE_DIVISION,
	ENTITY_TYPE_EXPLOSION,
	ENTITY_TYPE_FIXED_WING,
	ENTITY_TYPE_FORCE,
	ENTITY_TYPE_GROUP,
	ENTITY_TYPE_GUIDE,
	ENTITY_TYPE_HELICOPTER,
	ENTITY_TYPE_KEYSITE,
	ENTITY_TYPE_LANDING,
	ENTITY_TYPE_OBJECT,
	ENTITY_TYPE_PARTICLE,
	ENTITY_TYPE_PERSON,
	ENTITY_TYPE_PILOT,
	ENTITY_TYPE_PYLON,
	ENTITY_TYPE_REGEN,
	ENTITY_TYPE_ROUTED_VEHICLE,
	ENTITY_TYPE_SCENIC,
	ENTITY_TYPE_SECTOR,
	ENTITY_TYPE_SEGMENT,
	ENTITY_TYPE_SESSION,
	ENTITY_TYPE_SHIP_VEHICLE,
	ENTITY_TYPE_SITE,
	ENTITY_TYPE_SITE_UPDATABLE,
	ENTITY_TYPE_SMOKE_LIST,
	ENTITY_TYPE_SOUND_EFFECT,
	ENTITY_TYPE_SPRITE,
	ENTITY_TYPE_TASK,
	ENTITY_TYPE_UPDATE,
	ENTITY_TYPE_WAYPOINT,
	ENTITY_TYPE_WEAPON,
	NUM_ENTITY_TYPES
};

typedef enum ENTITY_TYPES entity_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ENTITY
{
	entity_types
		type;

	//
	// union pointer types for debugging
	//

	union
	{
		void
			*data;

		#if ENTITY_STRUCTURE_ALL_DEBUG_INFO

		struct ANTI_AIRCRAFT
			*anti_aircraft_data;

		struct BRIDGE
			*bridge_data;

		struct CAMERA
			*camera_data;

		struct CARGO
			*cargo_data;

		struct CITY
			*city_data;

		struct CITY_BUILDING
			*city_building_data;

		struct CRATER
			*crater_data;

		struct DIVISION
			*division_data;

		struct EXPLOSION
			*explosion_data;

		struct FIXED_WING
			*fixed_wing_data;

		struct FORCE
			*force_data;

		struct GROUP
			*group_data;

		struct GUIDE
			*guide_data;

		struct HELICOPTER
			*helicopter_data;

		struct KEYSITE
			*keysite_data;

		struct LANDING
			*landing_data;

		struct OBJECT
			*object_data;

		struct PARTICLE
			*particle_data;

		struct PERSON
			*person_data;

		struct PILOT
			*pilot_data;

		struct PYLON
			*pylon_data;

		struct REGEN
			*regen_data;

		struct ROUTED_VEHICLE
			*routed_vehicle_data;

		struct SCENIC
			*scenic_data;

		struct SECTOR
			*sector_data;

		struct SEGMENT
			*segment_data;

		struct SESSION
			*session_data;

		struct SHIP_VEHICLE
			*ship_data;

		struct SITE
			*site_data;

		struct SITE_UPDATABLE
			*site_updatable_data;

		struct SMOKE_LIST
			*smoke_list_data;

		struct SOUND_EFFECT
			*sound_effect_data;

		struct SPRITE
			*sprite_data;

		struct TASK
			*task_data;

		struct UPDATE
			*update_data;

		struct WAYPOINT
			*waypoint_data;

		struct WEAPON
			*weapon_data;

		#else

		#if ENTITY_STRUCTURE_AI_DEBUG_INFO

		struct ANTI_AIRCRAFT
			*anti_aircraft_data;

		struct EXPLOSION
			*explosion_data;

		struct FIXED_WING
			*fixed_wing_data;

		struct FORCE
			*force_data;

		struct GROUP
			*group_data;

		struct GUIDE
			*guide_data;

		struct HELICOPTER
			*helicopter_data;

		struct KEYSITE
			*keysite_data;

		struct LANDING
			*landing_data;

		struct OBJECT
			*object_data;

		struct PERSON
			*person_data;

		struct REGEN
			*regen_data;

		struct ROUTED_VEHICLE
			*routed_vehicle_data;

		struct SCENIC
			*scenic_data;

		struct SECTOR
			*sector_data;

		struct SESSION
			*session_data;

		struct SHIP_VEHICLE
			*ship_data;

		struct SITE
			*site_data;

		struct SITE_UPDATABLE
			*site_updatable_data;

		struct SMOKE_LIST
			*smoke_list_data;

		struct SOUND_EFFECT
			*sound_effect_data;

		struct SPRITE
			*sprite_data;

		struct TASK
			*task_data;

		struct WAYPOINT
			*waypoint_data;

		struct WEAPON
			*weapon_data;

		#endif

		#endif
	};

	struct ENTITY
		*succ,
		*pred;
};

typedef struct ENTITY entity;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern char
	*null_entity_pointer_message;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern char
	**entity_type_names;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ENTITY_TYPE_DATA
{
	char
		*name;

	int
		size_of_data,
		debug_pack;
};

typedef struct ENTITY_TYPE_DATA entity_type_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity_type_data
	entity_type_database[NUM_ENTITY_TYPES];

#define get_entity_type_name(ENTITY_TYPE) (entity_type_database[(ENTITY_TYPE)].name)

#define get_local_entity_type_name(EN) (entity_type_database[get_local_entity_type ((EN))].name)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define set_local_entity_type(EN,TYPE) ((EN)->type = (TYPE))

#ifdef DEBUG

#define get_local_entity_type(EN) ((EN) ? ((EN)->type) : (process_assert (null_entity_pointer_message, __FILE__, __LINE__), ENTITY_TYPE_UNKNOWN))

#else

#define get_local_entity_type(EN) ((EN)->type)

#endif

#define set_local_entity_data(EN,DATA) ((EN)->data = (DATA))

#define get_local_entity_data(EN) ((EN)->data)

#define set_local_entity_succ(EN,SUCC) ((EN)->succ = (SUCC))

#define get_local_entity_succ(EN) ((EN)->succ)

#define set_local_entity_pred(EN,PRED) ((EN)->pred = (PRED))

#define get_local_entity_pred(EN) ((EN)->pred)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_entity_type_names (void);

extern void deinitialise_entity_type_names (void);

extern void pack_entity_type (entity_types type);

extern entity_types unpack_entity_type (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "en_crew.h"

#include "en_day.h"

#include "en_force.h"

#include "en_forms.h"

#include "en_group.h"

#include "en_plyr.h"

#include "en_sbtyp.h"

#include "en_side.h"

#include "en_state.h"

#include "en_suply.h"

#include "en_task.h"

#include "en_tgt.h"

#include "en_thrt.h"

#include "en_view.h"

#include "en_wp.h"

#include "en_route.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
