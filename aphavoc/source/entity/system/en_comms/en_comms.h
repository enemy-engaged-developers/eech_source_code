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

enum ENTITY_COMMS_MESSAGES
{
	ENTITY_COMMS_ZERO, 														// trap zero data
	ENTITY_COMMS_ADD_PLANNER_WAYPOINT,									// (entity_comms_messages message, entity *en, vec3d *pos)
	ENTITY_COMMS_ADVISE_TRANSMIT_RECON,									// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_ATTITUDE_ANGLES,											// (entity_comms_messages message, entity *en, float heading, float pitch, float roll)
	ENTITY_COMMS_ATTITUDE_MATRIX,											// (entity_comms_messages message, entity *en, matrix3x3 attitude)
	ENTITY_COMMS_CAMPAIGN_COMPLETED,										// (entity_comms_messages message, entity *en, entity_sides side)
	ENTITY_COMMS_CAPTURE_KEYSITE,											// (entity_comms_messages message, entity *en, entity_sides side)
	ENTITY_COMMS_CHAR_VALUE,												// (entity_comms_messages message, entity *en, char_types type, char value)
	ENTITY_COMMS_CREATE,														// (entity_comms_messages message, entity *en, entity_types type, int index, char *pargs)
	ENTITY_COMMS_CREATE_META_EXPLOSION,									// (entity_comms_messages message, entity *en, meta_explosion_types type, vec3d *position, entity *parent, int entity_index_list[])
	ENTITY_COMMS_CREATE_META_SMOKE_LIST_SPECIFIED_OFFSET,			// (entity_comms_messages message, entity *en, entity_sub_type meta_explosion_sub_type, entity *parent, vec3d *rel_pos, int entity_index_list[])
	ENTITY_COMMS_CREATE_META_SMOKE_LIST_SUB_OBJECT_OFFSET,		// (entity_comms_messages message, entity *en, entity_sub_type meta_explosion_sub_type, entity *parent, int sub_object_type, int sub_object_depth, int entity_index_list[])
	ENTITY_COMMS_CREATE_SOUND_EFFECT,									// (entity_comms_messages message, entity *en, int index, entity_sub_types sub_type, entity *parent, int locality, vec3d *position, float amp, int valid, int looping, int sample_count, int *sample_index_list)
	ENTITY_COMMS_CREATE_WAYPOINT_ROUTE,									// (entity_comms_messages message, entity *en, entity *launcher, entity_sub_type weapon_sub_type, int weapon_index, int burst_size, int *smoke_trail_indices)
	ENTITY_COMMS_CREATE_WEAPON,											// (entity_comms_messages message, entity *en, entity *launcher, entity_sub_type weapon_sub_type, int weapon_index, int burst_size, int *smoke_trail_indices)
	ENTITY_COMMS_DAMAGE_PLAYER,											// (entity_comms_messages message, entity *en, int damage)
	ENTITY_COMMS_DAMAGE_PLAYER_AVIONICS,								// (entity_comms_messages message, entity *en, gunship_damage_levels damage_level)
	ENTITY_COMMS_DAMAGE_WEAPON_PACKAGE,									// (entity_comms_messages message, entity *en, int weapon_package_heading_depth, entity_sub_types weapon_sub_type, int weapon_package_damaged)
	ENTITY_COMMS_DESTROY,													// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_DESTROY_FAMILY,											// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_DESTROY_LOCAL_FAMILY,									// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_END,															// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_FLOAT_VALUE,												// (entity_comms_messages message, entity *en, float_types type, float value)
	ENTITY_COMMS_INT_VALUE,													// (entity_comms_messages message, entity *en, int_types type, int value)
	ENTITY_COMMS_KILL,			  											// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_MOBILE_KILL,												// (entity_comms_messages message, entity *force, entity *victim)
	ENTITY_COMMS_MOBILE_LAND,												// (entity_comms_messages message, entity *en, entity *wp)
	ENTITY_COMMS_MOBILE_TAKEOFF,											// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_MOVE_PLANNER_WAYPOINT,									// (entity_comms_messages message, entity *en, vec3d *pos)
	ENTITY_COMMS_PAUSE_SOUND_TYPE,										// (entity_comms_messages message, entity *en, entity_sub_types type, float delay)
	ENTITY_COMMS_PAUSE_WEAPON_SOUND_TYPE,								// (entity_comms_messages message, entity *en, entity_sub_types weapon_sub_type)
	ENTITY_COMMS_PILOT_COMMUNICATION,									// (entity_comms_messages message, entity *sender, int target_id, char *message)
	ENTITY_COMMS_PILOT_REQUEST_ACCEPTED,								// (entity_comms_messages message, entity *sender, int destination id, int index)
	ENTITY_COMMS_PLAY_CPG_CONTACT_MESSAGE,								// (entity_comms_messages message, entity *en, int speech_index, int speech_index, int speech_index)
	ENTITY_COMMS_PLAY_CPG_MESSAGE,										// (entity_comms_messages message, entity *en, int speech_index, int speech_category, float delay)
	ENTITY_COMMS_PLAY_WARNING_MESSAGE,									// (entity_comms_messages message, entity *en, int speech_index)
	ENTITY_COMMS_PLAYER_KILL,												// (entity_comms_messages message, entity *aggressor, entity *victim)
	ENTITY_COMMS_PLAYER_TASK_COMPLETED,									// (entity_comms_messages message, entity *en, entity *task)
	ENTITY_COMMS_PLAYER_TASK_TERMINATED,								// (entity_comms_messages message, entity *en, entity *task)
	ENTITY_COMMS_RADIO_MESSAGE,											// (entity_comms_messages message, entity *en, int message_type, int message_value)
	ENTITY_COMMS_REPAIR_ANTI_AIRCRAFT_GROUP,							// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_REPAIR_BRIDGE_ENTITY,									// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_REQUEST_TARGET_LIST,									// (entity_comms_messages message, entity *en, entity *destination)
	ENTITY_COMMS_RESTORE_ENTITY,											// (entity_comms_messages message, entity *en, vec3d *pos, int operational_state)
	ENTITY_COMMS_RESTORE_FIXED_ENTITY,									// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_RESUME_SOUND_TYPE,										// (entity_comms_messages message, entity *en, entity_sub_types type)
	ENTITY_COMMS_ROUTED_VEHICLE_ROUTE_DATA,							// (entity_comms_messages message, entity *en, int index1, index2, count1, *route_ptr)
	ENTITY_COMMS_SEND_TARGET_LIST,										// (entity_comms_messages message, entity *en, entity *destination, int target_count, int index_list [target_count])
	ENTITY_COMMS_SET_EXTERNAL_VIEW_ENTITY,								// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_SET_GUIDE_CRITERIA,										// (entity_comms_messages message, entity *en, int type, int valid, float value, float tolerance)
	ENTITY_COMMS_SET_GUIDE_POSITION_ENTITY,							// (entity_comms_messages message, entity *en, entity *position_entity)
	ENTITY_COMMS_SET_TASK_POINTERS,										// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_SET_WAYPOINT,												// (entity_comms_messages message, entity *en, entity *wp)
	ENTITY_COMMS_SPEECH_MESSAGE,											// (entity_comms_messages message, entity *en, message)
	ENTITY_COMMS_STRING,			  											// (entity_comms_messages message, entity *en, string_types type, char *s)
	ENTITY_COMMS_SWITCH_LIST,  											// (entity_comms_messages message, entity *en, list_types type, entity *parent)
	ENTITY_COMMS_SWITCH_PARENT,  											// (entity_comms_messages message, entity *en, list_types type, entity *parent)
	ENTITY_COMMS_TASK_ASSIGN_REQUEST,									// (entity_comms_messages message, entity *pilot, entity *task, entity *mobile)
	ENTITY_COMMS_TASK_ASSIGN_RESULT,										// (entity_comms_messages message, entity *pilot, entity *task, entity *mobile)
	ENTITY_COMMS_TASK_KILL,													// (entity_comms_messages message, entity *task, entity *victim, entity *aggressor)
	ENTITY_COMMS_TASK_LOSS,													// (entity_comms_messages message, entity *task, entity *victim, entity *aggressor)
	ENTITY_COMMS_UPDATE,														// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_UPDATE_FOG_OF_WAR,										// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_UPDATE_SECTOR_SIDE,										// (entity_comms_messages message, entity *en, int in_use)
	ENTITY_COMMS_UPDATE_SECTOR_SIDE_COUNT,								// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_VEC3D,			  											// (entity_comms_messages message, entity *en, vec3d_types type, vec3d *v)
	ENTITY_COMMS_ZERO_DESIRED_VELOCITY,									// (entity_comms_messages message, entity *en)
	ENTITY_COMMS_ZERO_VELOCITY,  											// (entity_comms_messages message, entity *en)
	NUM_ENTITY_COMMS_MESSAGES
};

typedef enum ENTITY_COMMS_MESSAGES entity_comms_messages;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_ENTITY_COMMS_MESSAGE_PACK_BITS	(7)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ENTITY_COMMS_MESSAGE_DATA
{
	char
		*name;

	int
		debug_pack;
};

typedef struct ENTITY_COMMS_MESSAGE_DATA entity_comms_message_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity_comms_message_data
	entity_comms_message_database[NUM_ENTITY_COMMS_MESSAGES];

#define get_entity_comms_message_name(MESSAGE) (entity_comms_message_database[(MESSAGE)].name)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void enable_entity_comms_messages (void);

extern void disable_entity_comms_messages (void);

extern void transmit_entity_comms_message (entity_comms_messages message, entity *en, ...);

extern void process_received_entity_comms_messages (void);

extern void pack_entity_comms_message (entity_comms_messages message);

extern entity_comms_messages unpack_entity_comms_message (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "en_sessn.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
