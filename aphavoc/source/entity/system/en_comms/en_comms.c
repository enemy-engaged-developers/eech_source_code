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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "ai/ai_misc/ai_route.h"
#include "ai/taskgen/assign.h"
#include "ai/taskgen/engage.h"
#include "ai/taskgen/croute.h"
#include "ai/highlevl/imaps.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE_MESSAGE_TEXT	0

#define DEBUG_MODULE_PACK_ONE			0

#define DEBUG_MODULE_PACK_ALL			(PACK_ENTIRE_SESSION || 0)

#define FAST_TRACK						1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_comms_message_data
	entity_comms_message_database[NUM_ENTITY_COMMS_MESSAGES] =
	{
		{
			"ENTITY_COMMS_ZERO",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_ADD_PLANNER_WAYPOINT",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_ADVISE_TRANSMIT_RECON",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_ATTITUDE_ANGLES",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_ATTITUDE_MATRIX",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CAMPAIGN_COMPLETED",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CAPTURE_KEYSITE",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CHAR_VALUE",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CREATE",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CREATE_META_EXPLOSION",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CREATE_META_SMOKE_LIST_SPECIFIED_OFFSET",			// name
			(DEBUG_MODULE_PACK_ALL || 0),												// debug_pack
		},
		{
			"ENTITY_COMMS_CREATE_META_SMOKE_LIST_SUB_OBJECT_OFFSET",			// name
			(DEBUG_MODULE_PACK_ALL || 0),												// debug_pack
		},
		{
			"ENTITY_COMMS_CREATE_SOUND_EFFECT",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CREATE_WAYPOINT_ROUTE",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_CREATE_WEAPON",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_DAMAGE_PLAYER",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_DAMAGE_PLAYER_AVIONICS",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_DAMAGE_WEAPON_PACKAGE",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_DESTROY",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_DESTROY_FAMILY",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_DESTROY_LOCAL_FAMILY",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_END",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_FLOAT_VALUE",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_INT_VALUE",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_KILL",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_MOBILE_KILL",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_MOBILE_LAND",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_MOBILE_TAKEOFF",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_MOVE_PLANNER_WAYPOINT",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PAUSE_SOUND_TYPE",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PAUSE_WEAPON_SOUND_TYPE",				// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PILOT_COMMUNICATION",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PILOT_PFZ_TRANSFER",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PILOT_REQUEST_ACCEPTED",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PLAY_CPG_CONTACT_MESSAGE",				// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PLAY_CPG_MESSAGE",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PLAY_WARNING_MESSAGE",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PLAYER_KILL",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PLAYER_TASK_COMPLETED",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_PLAYER_TASK_TERMINATED",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_RADIO_MESSAGE",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_REPAIR_ANTI_AIRCRAFT_GROUP",			// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_REPAIR_BRIDGE_ENTITY",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_REQUEST_TARGET_LIST",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_RESTORE_ENTITY",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_RESTORE_FIXED_ENTITY",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_RESUME_SOUND_TYPE",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_ROUTED_VEHICLE_ROUTE_DATA",				// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SEND_TARGET_LIST",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SET_EXTERNAL_VIEW_ENTITY",				// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SET_GUIDE_CRITERIA",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SET_GUIDE_POSITION_ENTITY",				// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SET_TASK_POINTERS",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SET_WAYPOINT",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SPEECH_MESSAGE",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_STRING",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SWITCH_LIST",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_SWITCH_PARENT",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_TASK_ASSIGN_REQUEST",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_TASK_ASSIGN_RESULT",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_TASK_KILL",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_TASK_LOSS",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_UPDATE",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_UPDATE_FOG_OF_WAR",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_UPDATE_SECTOR_SIDE",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_UPDATE_SECTOR_SIDE_COUNT",				// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_VEC3D",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_ZERO_DESIRED_VELOCITY",					// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"ENTITY_COMMS_ZERO_VELOCITY",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ATTRIBUTE_BUFFER_SIZE (1000)

static char
	attribute_buffer[ATTRIBUTE_BUFFER_SIZE];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	comms_messages_enabled = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void enable_entity_comms_messages (void)
{
	debug_log ("Setting comms messages to ENABLED");

	comms_messages_enabled = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void disable_entity_comms_messages (void)
{
	debug_log ("Setting comms messages to DISABLED");

	comms_messages_enabled = FALSE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transmit_pfz(entity* sender, entity* receiver, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, entity* targets[])
{
	entity* target;
	int i;

	////////////////////////////////////////
	//
	// trap single player or comms messages disabled
	//
	////////////////////////////////////////

	if ((direct_play_get_comms_mode () == DIRECT_PLAY_COMMS_MODE_NONE) || (!comms_messages_enabled))
	{
		return;
	}

	////////////////////////////////////////
	//
	// build message
	//
	////////////////////////////////////////

	pack_entity_comms_message (ENTITY_COMMS_PILOT_PFZ_TRANSFER);

	pack_entity_safe_ptr (sender);
	pack_entity_safe_ptr (receiver);

	pack_float_value(NULL, FLOAT_TYPE_PFZ_X1, x1);
	pack_float_value(NULL, FLOAT_TYPE_PFZ_Y1, y1);
	pack_float_value(NULL, FLOAT_TYPE_PFZ_X2, x2);
	pack_float_value(NULL, FLOAT_TYPE_PFZ_Y2, y2);
	pack_float_value(NULL, FLOAT_TYPE_PFZ_X3, x3);
	pack_float_value(NULL, FLOAT_TYPE_PFZ_Y3, y3);
	pack_float_value(NULL, FLOAT_TYPE_PFZ_X4, x4);
	pack_float_value(NULL, FLOAT_TYPE_PFZ_Y1, y4);

	// pack list of targets
	for (target = targets[0], i=0; target && i < 16; target = targets[i], i++)
		if (target != sender && target != receiver)
			pack_entity_safe_ptr(target);

	// end marker
	pack_entity_safe_ptr(NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WARNING! CHARS AND SHORT INTS ARE PROMOTED TO INTS ON THE VARIABLE ARGUMENT LIST
//
//				FLOATS ARE PROMOTED TO DOUBLES ON THE VARIABLE ARGUMENT LIST
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transmit_entity_comms_message (entity_comms_messages message, entity *en, ...)
{
	va_list
		pargs;

	////////////////////////////////////////
	//
	// trap single player or comms messages disabled
	//
	////////////////////////////////////////

	if ((direct_play_get_comms_mode () == DIRECT_PLAY_COMMS_MODE_NONE) || (!comms_messages_enabled))
	{
		return;
	}

	////////////////////////////////////////
	//
	// build message
	//
	////////////////////////////////////////

	va_start (pargs, en);

	pack_entity_comms_message (message);

	switch (message)
	{
		////////////////////////////////////////
		case ENTITY_COMMS_ZERO:
		////////////////////////////////////////
		{
			debug_fatal ("ENTITY_COMMS_ZERO encountered during transmit");

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_ADD_PLANNER_WAYPOINT:
		////////////////////////////////////////
		{
			vec3d
				*pos;

			//
			// (entity_comms_messages message, entity *wp, vec3d *pos)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			pos = va_arg (pargs, vec3d *);

			pack_vec3d (en, VEC3D_TYPE_POSITION, pos);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending add planner waypoint at %f, %f, %f", pos->x, pos->y, pos->z);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_ADVISE_TRANSMIT_RECON:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *wp)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending advise transmit recon");

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_ATTITUDE_ANGLES:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, float heading, float pitch, float roll)
			//

			float
				heading,
				pitch,
				roll;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			heading = va_arg (pargs, double);

			pitch = va_arg (pargs, double);

			roll = va_arg (pargs, double);

			pack_attitude_angles (en, heading, pitch, roll);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending attitude angle for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_ATTITUDE_MATRIX:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, matrix3x3 attitude)
			//

			matrix3x3
				*attitude;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			attitude = va_arg (pargs, matrix3x3 *);

			pack_attitude_matrix (en, *attitude);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending attitude matrix for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CAMPAIGN_COMPLETED:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, int side)
			//

			entity_sides
				side;

			campaign_completed_types
				complete;

			ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

			ASSERT (en);

			pack_entity_safe_ptr (en);

			side = va_arg (pargs, entity_sides);

			pack_int_value (en, INT_TYPE_SIDE, side);

			complete = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_SESSION_COMPLETE, complete);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending campaign completed by %s", entity_side_names [side]);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CAPTURE_KEYSITE:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, int side)
			//

			entity_sides
				side;

			ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

			ASSERT (en);

			pack_entity_safe_ptr (en);

			side = va_arg (pargs, entity_sides);

			pack_int_value (en, INT_TYPE_SIDE, side);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending captured keysite for %s", entity_side_names [side]);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CHAR_VALUE:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, char_types type, char value)
			//

			char_types
				type;

			char
				value;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, char_types);

			pack_char_type (type);

			value = va_arg (pargs, int);

			pack_char_value (en, type, value);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending char for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CREATE:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, entity_types type, int index, char *pargs)
			//

			entity_types
				type;

			int
				index;

			const char
				*buffer;

			ASSERT (!en);

			type = va_arg (pargs, entity_types);

			pack_entity_type (type);

			index = va_arg (pargs, int);

			pack_entity_safe_index (index);

			buffer = va_arg (pargs, const char *);

			pack_entity_attributes (buffer);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending create for %s (index %d)", entity_type_names [type], index);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CREATE_META_EXPLOSION:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, meta_explosion_types type, vec3d *position, entity *parent, int entity_index_list[])
			//

			entity
				*parent;

			meta_explosion_types
				type;

			int
				loop,
				index,
				list_count,
				*entity_index_list;

			vec3d
				*position;

			ASSERT (!en);

			type = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_META_EXPLOSION_TYPE, type);

			position = va_arg (pargs, vec3d *);

			pack_vec3d (en, VEC3D_TYPE_POSITION, position);

			parent = va_arg (pargs, entity *);

			pack_entity_safe_ptr (parent);

			list_count = count_entities_in_meta_explosion (type);

			entity_index_list = va_arg (pargs, int *);

			for (loop = 0; loop < list_count; loop ++)
			{
				index = entity_index_list [loop];

				pack_entity_safe_index (index);
			}

			#if DEBUG_MODULE_MESSAGE_TEXT

			if (parent)
			{

				debug_log ("EN_COMMS: sending create meta explosion for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));
			}
			else
			{

				debug_log ("EN_COMMS: sending create meta explosion");
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CREATE_META_SMOKE_LIST_SPECIFIED_OFFSET:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, meta_smoke_list_types type, entity *parent, vec3d *rel_pos, int entity_index_list[])
			//

			entity
				*parent;

			meta_smoke_list_types
				type;

			int
				loop,
				index,
				list_count,
				*entity_index_list;

			vec3d
				*rel_pos;

			ASSERT (!en);

			type = va_arg (pargs, meta_smoke_list_types);

			pack_int_value (en, INT_TYPE_META_SMOKE_LIST_TYPE, type);

			parent = va_arg (pargs, entity *);

			pack_entity_safe_ptr (parent);

			rel_pos = va_arg (pargs, vec3d *);

			if (rel_pos)
			{
				if (parent)
				{
					pack_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, rel_pos);
				}
				else
				{
					pack_vec3d (en, VEC3D_TYPE_POSITION, rel_pos);
				}
			}
			else
			{
				vec3d
					def_pos;

				def_pos.x = 0.0;
				def_pos.y = 0.0;
				def_pos.z = 0.0;

				pack_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, &def_pos);
			}

			list_count = count_entities_in_meta_smoke_list (type);

			entity_index_list = va_arg (pargs, int *);

			for (loop = 0; loop < list_count; loop ++)
			{
				index = entity_index_list [loop];

				pack_entity_safe_index (index);
			}

			#if DEBUG_MODULE_MESSAGE_TEXT

			if (parent)
			{

				debug_log ("EN_COMMS: sending create meta smoke ( spec pos ) for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));
			}
			else
			{

				debug_log ("EN_COMMS: sending create meta smoke");
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CREATE_META_SMOKE_LIST_SUB_OBJECT_OFFSET:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, meta_smoke_list_types type, entity *parent, int sub_object_type, int sub_object_depth, int entity_index_list[])
			//

			entity
				*parent;

			meta_smoke_list_types
				type;

			int
				loop,
				index,
				list_count,
				sub_object_type,
				sub_object_depth,
				*entity_index_list;

			ASSERT (!en);

			type = va_arg (pargs, meta_smoke_list_types);

			pack_int_value (en, INT_TYPE_META_SMOKE_LIST_TYPE, type);

			parent = va_arg (pargs, entity *);

			pack_entity_safe_ptr (parent);

			sub_object_type = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_SUB_OBJECT_TYPE, sub_object_type);

			sub_object_depth = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_SUB_OBJECT_DEPTH, sub_object_depth);

			list_count = count_entities_in_meta_smoke_list (type);

			entity_index_list = va_arg (pargs, int *);

			for (loop = 0; loop < list_count; loop ++)
			{
				index = entity_index_list [loop];

				pack_entity_safe_index (index);
			}

			#if DEBUG_MODULE_MESSAGE_TEXT

			if (parent)
			{

				debug_log ("EN_COMMS: sending create meta smoke ( sub pos ) for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));
			}
			else
			{

				debug_log ("EN_COMMS: sending create meta smoke");
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CREATE_SOUND_EFFECT:
		////////////////////////////////////////
		{
			entity
				*parent;

			entity_sub_types
				sub_type;

			int
				loop,
				index,
				valid,
				side,
				channel,
				locality,
				looping,
				position_valid,
				sample_count,
				*sample_index_list;

			float
				amp, pitch;

			vec3d
				*position;

			ASSERT (!en);

			index = va_arg (pargs, int);
			pack_entity_safe_index (index);

			parent = va_arg (pargs, entity *);
			pack_entity_safe_ptr (parent);

			side = va_arg (pargs, entity_sides);
			pack_int_value (en, INT_TYPE_SIDE, side);

			sub_type = va_arg (pargs, entity_sub_types);
			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, sub_type);

			channel = va_arg (pargs, int);
			pack_int_value (en, INT_TYPE_SOUND_CHANNEL, channel);

			locality = va_arg (pargs, int);
			pack_int_value (en, INT_TYPE_SOUND_LOCALITY, locality);

			position = va_arg (pargs, vec3d *);
			if (position)
			{
				position_valid = TRUE;

				pack_int_value (en, INT_TYPE_VALID, position_valid);

				pack_vec3d (en, VEC3D_TYPE_POSITION, position);
			}
			else
			{
				position_valid = FALSE;

				pack_int_value (en, INT_TYPE_VALID, position_valid);
			}

			amp = va_arg (pargs, double);
			pack_float_value (en, FLOAT_TYPE_AMPLIFICATION, amp);

			pitch = va_arg (pargs, double);
			pack_float_value (en, FLOAT_TYPE_SOUNDPITCH, pitch);

			valid = va_arg (pargs, int);
			pack_int_value (en, INT_TYPE_VALID_SOUND_EFFECT, valid);

			looping = va_arg (pargs, int);
			pack_int_value (en, INT_TYPE_SOUND_EFFECT_LOOPING, looping);

			sample_count = va_arg (pargs, int);
			pack_int_value (en, INT_TYPE_SOUND_EFFECT_SEQUENCE_COUNT, sample_count);

			sample_index_list = va_arg (pargs, int *);

			for (loop = 0; loop < sample_count; loop ++)
			{
				index = sample_index_list [loop];

				pack_int_value (en, INT_TYPE_SOUND_EFFECT_INDEX, index);
			}

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending create sound effect for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CREATE_WAYPOINT_ROUTE:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, unsigned int check_sum)
			//

			vec3d
				*start,
				*stop;

			entity
				*wp,
				*group,
				*return_keysite;

			unsigned int
				count,
				check_sum;

			////////////////////////////////////////

			ASSERT (en);
			pack_entity_safe_ptr (en);

			group = va_arg (pargs, entity *);
			pack_entity_safe_ptr (group);

			return_keysite = va_arg (pargs, entity *);
			pack_entity_safe_ptr (return_keysite);

			start = va_arg (pargs, vec3d *);

			if (start)
			{

				pack_int_value (NULL, INT_TYPE_VALID, TRUE);
				pack_vec3d (NULL, VEC3D_TYPE_POSITION, start);
			}
			else
			{

				pack_int_value (NULL, INT_TYPE_VALID, FALSE);
			}

			stop = va_arg (pargs, vec3d *);

			if (stop)
			{

				pack_int_value (NULL, INT_TYPE_VALID, TRUE);
				pack_vec3d (NULL, VEC3D_TYPE_POSITION, stop);
			}
			else
			{

				pack_int_value (NULL, INT_TYPE_VALID, FALSE);
			}

			////////////////////////////////////////

			check_sum = va_arg (pargs, unsigned int);

			pack_int_value (en, INT_TYPE_ROUTE_CHECK_SUM, check_sum);

			////////////////////////////////////////
			
			count = 0;

			wp = get_local_entity_first_child (en, LIST_TYPE_WAYPOINT);

			while (wp)
			{

				count ++;

				wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
			}

			pack_int_value (en, INT_TYPE_ROUTE_LENGTH, count);

			////////////////////////////////////////

			wp = get_local_entity_first_child (en, LIST_TYPE_WAYPOINT);

			while (wp)
			{

				pack_entity_safe_index (get_local_entity_index (wp));

				wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
			}

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending create waypoint route for %s (%d) check_sum %d", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en), check_sum);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_CREATE_WEAPON:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, entity *launcher, entity_sub_type weapon_sub_type, int weapon_index, int burst_size, int *smoke_trail_indices)
			//

			entity
				*launcher;

			entity_sub_types
				weapon_sub_type;

			int
				weapon_index,
				burst_size,
				*smoke_trail_indices,
				num_smoke_trail_entities,
				i;

			meta_smoke_list_types
				smoke_trail_type;

			ASSERT (!en);

			////////////////////////////////////////

			launcher = va_arg (pargs, entity *);

			ASSERT (launcher);

			////////////////////////////////////////
			// DEBUG COMMS WEAPON LAG TIMING
			////////////////////////////////////////
			if (get_comms_model () == COMMS_MODEL_CLIENT)
			{

				if (launcher == get_gunship_entity ())
				{

					comms_weapon_lag_timing = TRUE;

					comms_weapon_lag_time = ((float) get_system_time () / (float) TIME_1_SECOND);
				}
			}
			////////////////////////////////////////
			// DEBUG COMMS WEAPON LAG TIMING
			////////////////////////////////////////

			pack_entity_safe_ptr (launcher);

			////////////////////////////////////////

			weapon_sub_type = va_arg (pargs, entity_sub_types);

			ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, weapon_sub_type);

			////////////////////////////////////////

			weapon_index = va_arg (pargs, int);

			pack_entity_safe_index (weapon_index);

			////////////////////////////////////////

			burst_size = va_arg (pargs, int);

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
				ASSERT (burst_size > 0);

				if (weapon_database[weapon_sub_type].rate_of_fire != FIRE_SINGLE_WEAPON)
				{
					pack_int_value (en, INT_TYPE_WEAPON_BURST_SIZE, burst_size);
				}
			}
			else
			{
				ASSERT (burst_size == BURST_SIZE_DONT_CARE);
			}

			////////////////////////////////////////

			smoke_trail_indices = va_arg (pargs, int *);

			if (smoke_trail_indices)
			{
				ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

				smoke_trail_type = weapon_database[weapon_sub_type].smoke_trail_type;

				ASSERT (smoke_trail_type != META_SMOKE_LIST_TYPE_NONE);

				num_smoke_trail_entities = count_entities_in_meta_smoke_list (smoke_trail_type);

				ASSERT (num_smoke_trail_entities > 0);

				for (i = 0; i < num_smoke_trail_entities; i++)
				{
					pack_entity_safe_index (smoke_trail_indices[i]);
				}
			}

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending create weapon for %s (%d)", entity_sub_type_weapon_names [weapon_sub_type], entity_type_names [launcher->type], get_local_entity_index (launcher));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_DAMAGE_PLAYER:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, int damage, int random);
			//

			unsigned int
				index,
				random,
				damage;

			ASSERT (en);

			index = get_local_entity_index (en);

			pack_entity_safe_index (index);

			damage = va_arg (pargs, unsigned int);

			random = va_arg (pargs, unsigned int);

			//DEBUG// mis-using INT_TYPE_HELICOPTER_DAMAGE_FLAGS
			pack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_FLAGS, damage);
			//DEBUG// mis-using INT_TYPE_HELICOPTER_DAMAGE_FLAGS

			pack_int_value (en, INT_TYPE_VALID, random);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending damage helicopter dynamics %d for %s (%d)", damage, get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_DAMAGE_PLAYER_AVIONICS:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, gunship_damage_levels damage_level)
			//

			int
				index;

			gunship_damage_levels
				damage_level;

			ASSERT (en);

			index = get_local_entity_index (en);

			pack_entity_safe_index (index);

			damage_level = va_arg (pargs, gunship_damage_levels);

			pack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_LEVEL, damage_level);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending damage helicopter avionics %d for %s (%d)", damage_level, get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_DAMAGE_WEAPON_PACKAGE:
		////////////////////////////////////////
		{
			int
				weapon_package_heading_depth,
				weapon_package_damaged;

			entity_sub_types
				weapon_sub_type;

			//
		 	// (entity_comms_messages message, entity *en, int weapon_package_heading_depth, entity_sub_types weapon_sub_type, int weapon_package_damaged)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			weapon_package_heading_depth = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_WEAPON_PACKAGE_HEADING_DEPTH, weapon_package_heading_depth);

			weapon_sub_type = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, weapon_sub_type);

			weapon_package_damaged = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_WEAPON_PACKAGE_DAMAGED, weapon_package_damaged);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log
			(
				"EN_COMMS: sending damage weapon package for %s (%d), heading_depth = %d, weapon_sub_type = %d, damaged = %d",
				get_local_entity_string (en, STRING_TYPE_FULL_NAME),
				get_local_entity_index (en),
				weapon_package_heading_depth,
				weapon_sub_type,
				weapon_package_damaged
			);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_DESTROY:
		case ENTITY_COMMS_DESTROY_FAMILY:
		case ENTITY_COMMS_DESTROY_LOCAL_FAMILY:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending destroy for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_END:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (!en);

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_FLOAT_VALUE:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, float_types type, float value)
			//

			float_types
				type;

			float
				value;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, float_types);

			pack_float_type (type);

			value = va_arg (pargs, double);

			pack_float_value (en, type, value);

			#if FAST_TRACK

			if ((float_type_database[type].fast_track) && (get_comms_model () == COMMS_MODEL_CLIENT) && (en == get_gunship_entity ()))
			{
				set_local_entity_float_value (en, type, value);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: sending fast_track float value %s = %f for %s (%d)", float_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

				#endif
			}

			#endif

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending float value %s = %f for %s (%d)", float_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_INT_VALUE:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, int_types type, int value)
			//

			int_types
				type;

			int
				value;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, int_types);

			pack_int_type (type);

			value = va_arg (pargs, int);

			pack_int_value (en, type, value);

			#if FAST_TRACK

			if ((int_type_database[type].fast_track) && (get_comms_model () == COMMS_MODEL_CLIENT) && (en == get_gunship_entity ()))
			{
				set_local_entity_int_value (en, type, value);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: sending fast_track int value %s = %d for %s (%d)", int_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

				#endif
			}

			#endif

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending int value %s = %d for %s (%d)", int_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_KILL:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending kill for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_MOBILE_KILL:
		////////////////////////////////////////
		{
			entity
				*victim;

			//
			// (entity_comms_messages message, entity *force, entity *victim)
			//

			victim = va_arg (pargs, entity *);

			ASSERT (victim);

			pack_entity_safe_ptr (en);

			pack_entity_safe_ptr (victim);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending mobile kill for %s (%d)", get_local_entity_type_name (victim), get_local_entity_index (victim));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_MOBILE_LAND:
		////////////////////////////////////////
		{

			entity
				*wp;

			//
			// (entity_comms_messages message, entity *en, entity *wp)
			//

			ASSERT (en);

			wp = va_arg (pargs, entity *);

			ASSERT (wp);

			pack_entity_safe_ptr (en);

			pack_entity_safe_ptr (wp);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending mobile land for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_MOBILE_TAKEOFF:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, entity *wp)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending mobile takeoff for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_MOVE_PLANNER_WAYPOINT:
		////////////////////////////////////////
		{
			vec3d
				*pos;

			//
			// (entity_comms_messages message, entity *wp, vec3d *pos)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			pos = va_arg (pargs, vec3d *);

			pack_vec3d (en, VEC3D_TYPE_POSITION, pos);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending move planner_waypoint for %s (%d) to %f, %f, %f", get_local_entity_type_name (en), get_local_entity_index (en), pos->x, pos->y, pos->z);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PAUSE_SOUND_TYPE:
		////////////////////////////////////////
		{
			entity_sub_types
				type;

			float
				delay;

			//
			// (entity_comms_messages message, entity *en, entity_sub_types type, float delay)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, type);

			delay = va_arg (pargs, double);

			pack_float_value (en, FLOAT_TYPE_VALID_EFFECT_LIFETIME, delay);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending pause sound type %s for %s (%d)", entity_sub_type_effect_names [type], get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PAUSE_WEAPON_SOUND_TYPE:
		////////////////////////////////////////
		{
			entity_sub_types
				weapon_sub_type;

			//
			// (entity_comms_messages message, entity *en, entity_sub_types weapon_sub_type)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			weapon_sub_type = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, weapon_sub_type);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending pause weapon sound type for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PILOT_COMMUNICATION:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *sender, entity *target, int type, char *message)
			//

			const char
				*message;

			entity
				*target;

			message_text_types
				type;

			pack_entity_safe_ptr (en);

			target = va_arg (pargs, entity *);

			pack_entity_safe_ptr (target);

			type = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_MESSAGE_TEXT_TYPE, type);

			message = va_arg (pargs, const char *);

			if (message_text_type_send_string (type))
			{
				ASSERT (message);

				pack_string (en, STRING_TYPE_PILOT_MESSAGE, message);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: sending communication message %s", message);

				#endif
			}
			else
			{
				ASSERT (message == NULL);
			}

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PILOT_PFZ_TRANSFER:
		////////////////////////////////////////
		{
			ASSERT(!"Use transmit_pfz() function");

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PILOT_REQUEST_ACCEPTED:
		////////////////////////////////////////
		{

			int
				pilot_index,
				destination_id;
			//
			// (entity_comms_messages message, int destination_id, int index)
			//

			pack_entity_safe_ptr (en);

			destination_id = va_arg (pargs, int);

			pilot_index = va_arg (pargs, int);

			pack_int_value (NULL, INT_TYPE_VALUE, destination_id);

			pack_int_value (NULL, INT_TYPE_VALUE, pilot_index);

			//#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending Pilot request accepted to %d for entity %d", destination_id, pilot_index);

			//#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PLAY_CPG_CONTACT_MESSAGE:
		////////////////////////////////////////
		{
			int
				speech_index1,
				speech_index2,
				speech_index3;

			//
			// (entity_comms_messages message, entity *en, int speech_index1, int speech_index2, int speech_index3)
			//

			speech_index1 = va_arg (pargs, int);

			speech_index2 = va_arg (pargs, int);

			speech_index3 = va_arg (pargs, int);

			ASSERT (en);

			pack_entity_safe_ptr (en);

			pack_int_value (en, INT_TYPE_SPEECH_INDEX, speech_index1);

			pack_int_value (en, INT_TYPE_SPEECH_INDEX, speech_index2);

			pack_int_value (en, INT_TYPE_SPEECH_INDEX, speech_index3);

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PLAY_CPG_MESSAGE:
		////////////////////////////////////////
		{
			int
				speech_index,
				speech_category;

			float
				priority,
				expire_time,
				category_silence_timer;

			//
			// (entity_comms_messages message, entity *en, float priority, float expire_time, int speech_category, float category_silence_timer, int speech_index)
			//

			priority = va_arg (pargs, double);

			expire_time = va_arg (pargs, double);

			speech_category = va_arg (pargs, int);

			category_silence_timer = va_arg (pargs, double);

			speech_index = va_arg (pargs, int);

			ASSERT (en);

			pack_entity_safe_ptr (en);

			pack_float_value (en, FLOAT_TYPE_SPEECH_PRIORITY, priority);

			pack_float_value (en, FLOAT_TYPE_SPEECH_EXPIRE_TIME, expire_time);

			pack_int_value (en, INT_TYPE_SPEECH_CATEGORY, speech_category);

			pack_float_value (en, FLOAT_TYPE_SPEECH_CATEGORY_SILENCE_TIMER, category_silence_timer);

			pack_int_value (en, INT_TYPE_SPEECH_INDEX, speech_index);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending play cpg message for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PLAY_WARNING_MESSAGE:
		////////////////////////////////////////
		{
			int
				speech_index;

			//
			// (entity_comms_messages message, entity *en, int speech_index)
			//

			speech_index = va_arg (pargs, int);

			ASSERT (en);

			pack_entity_safe_ptr (en);

			pack_int_value (en, INT_TYPE_SPEECH_INDEX, speech_index);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending play warning message for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PLAYER_KILL:
		////////////////////////////////////////
		{
			entity
				*aggressor,
				*victim;

			//
			// (entity_comms_messages message, entity *aggressor, entity *victim)
			//

			aggressor = en;

			victim = va_arg (pargs, entity *);

			ASSERT (victim);

			pack_entity_safe_ptr (aggressor);

			pack_entity_safe_ptr (victim);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending player kill for %s (%d)", get_local_entity_type_name (victim), get_local_entity_index (victim));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PLAYER_TASK_COMPLETED:
		////////////////////////////////////////
		{
			entity
				*task;

			//
			// (entity_comms_messages message, entity *en, entity *task)
			//

			ASSERT (en);

			task = va_arg (pargs, entity *);

			pack_entity_safe_ptr (en);

			pack_entity_safe_ptr (task);

//			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending player task %s (%d) completed for %s (%d)",
							get_local_entity_string (task, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (task),
							get_local_entity_string (en, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (en));

//			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_PLAYER_TASK_TERMINATED:
		////////////////////////////////////////
		{

			entity
				*task;

			//
			// (entity_comms_messages message, entity *en, entity *task)
			//

			ASSERT (en);

			task = va_arg (pargs, entity *);

			pack_entity_safe_ptr (en);

			pack_entity_safe_ptr (task);

//			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending player task %s (%d) terminated for %s (%d)",
							get_local_entity_string (task, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (task),
							get_local_entity_string (en, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (en));

//			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_RADIO_MESSAGE:
		////////////////////////////////////////
		{

			int
				message_type,
				message_value;

			//
			// (entity_comms_messages message, entity *en, int message_type, int message_value)
			//

			ASSERT (en);

			message_type = va_arg (pargs, int);

			message_value = va_arg (pargs, int);

			pack_entity_safe_ptr (en);

			pack_int_value (en, INT_TYPE_RADIO_MESSAGE_TYPE, message_type);

			pack_int_value (en, INT_TYPE_RADIO_MESSAGE_VALUE, message_value);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending radio message for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_REPAIR_ANTI_AIRCRAFT_GROUP:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending Repair AA Group for (%d)", get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_REPAIR_BRIDGE_ENTITY:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_BRIDGE);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending Repair Bridge for (%d)", get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_REQUEST_TARGET_LIST:
		////////////////////////////////////////
		{
			entity
				*destination;

			//
			// (entity_comms_messages message, entity *en, entity *destination)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			destination = va_arg (pargs, entity *);

			ASSERT (destination);

			pack_entity_safe_ptr (destination);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending request target list from %s (%d) to %s (%d)",
							get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
							get_local_entity_string (destination, STRING_TYPE_FULL_NAME), get_local_entity_index (destination));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_RESTORE_ENTITY:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, vec3d *pos, int operational_state)
			//

			vec3d
				*pos;

			int
				operational_state;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			pos = va_arg (pargs, vec3d *);

			pack_vec3d (en, VEC3D_TYPE_POSITION, pos);

			operational_state = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_OPERATIONAL_STATE, operational_state);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending restore entity for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_RESTORE_FIXED_ENTITY:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending restore entity for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_RESUME_SOUND_TYPE:
		////////////////////////////////////////
		{
			entity_sub_types
				type;

			//
			// (entity_comms_messages message, entity *en, entity_sub_types type)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, type);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending resume sound type %s for %s (%d)", entity_sub_type_effect_names [type], get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_ROUTED_VEHICLE_ROUTE_DATA:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, vec3d *pos, int operational_state)
			//

			routed_vehicle
				*raw;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			raw = get_local_entity_data (en);

			pack_int_value (en, INT_TYPE_WAYPOINT_THIS_INDEX, raw->waypoint_this_index);

			pack_int_value (en, INT_TYPE_WAYPOINT_NEXT_INDEX, raw->waypoint_next_index);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending routed_vehicle %d route between %d and %d", get_local_entity_index (en), raw->waypoint_this_index, raw->waypoint_next_index);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SEND_TARGET_LIST:
		////////////////////////////////////////
		{
			entity
				*destination;

			int
				loop,
				*index_list,
				target_count;

			//
			// (entity_comms_messages message, entity *en, entity *destination, int target_count, int index_list [target_count])
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			destination = va_arg (pargs, entity *);

			ASSERT (destination);

			pack_entity_safe_ptr (destination);

			target_count = va_arg (pargs, int);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending %d targets from %s (%d) to %s (%d)", target_count,
							get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
							get_local_entity_string (destination, STRING_TYPE_FULL_NAME), get_local_entity_index (destination));

			#endif

			ASSERT (target_count > 0);

			pack_int_value (en, INT_TYPE_HAND_OFF_TARGET_COUNT, target_count);

			index_list = va_arg (pargs, int *);

			ASSERT (index_list);

			for (loop = 0; loop < target_count; loop ++)
			{
				pack_entity_safe_index (index_list [loop]);
			}

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SET_EXTERNAL_VIEW_ENTITY:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE

			debug_log ("EN_COMMS: sending set external view entity to %s (%d)", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SET_GUIDE_CRITERIA:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, int type, int valid, float value)
			//

			int
				type,
				valid;

			float
				value;

			ASSERT (en);

			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GUIDE);

			ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
	
			pack_entity_safe_ptr (en);

			type = va_arg (pargs, int);

			valid = va_arg (pargs, int);

			value = va_arg (pargs, double);

			pack_int_value (en, INT_TYPE_GUIDE_CRITERIA_TYPE, type);

			pack_int_value (en, INT_TYPE_VALID, valid);

			pack_float_value (en, FLOAT_TYPE_GUIDE_CRITERIA_VALUE, value);

			#if DEBUG_MODULE

			debug_log ("EN_COMMS: sending set guide criteria for %d", get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SET_GUIDE_POSITION_ENTITY:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, entity *position_entity)
			//

			entity
				*position_entity;

			ASSERT (en);

			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GUIDE);

			ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
	
			pack_entity_safe_ptr (en);

			position_entity = va_arg (pargs, entity *);

			pack_entity_safe_ptr (position_entity);

			#if DEBUG_MODULE

			debug_log ("EN_COMMS: sending set guide position entity for %d", get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SET_TASK_POINTERS:
		////////////////////////////////////////
		{

			task
				*raw;

			int
				loop;

			//
			// (entity_comms_messages message, entity *en)
			//

			pack_entity_safe_ptr (en);

			raw = get_local_entity_data (en);

			// positions

			for (loop = 0; loop < raw->route_length; loop ++)
			{

				pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->route_nodes [loop]);
			}

			// formations

			for (loop = 0; loop < raw->route_length; loop ++)
			{

				pack_int_value (en, INT_TYPE_WAYPOINT_FORMATION, raw->route_formation_types [loop]);
			}

			// waypoint types

			for (loop = 0; loop < raw->route_length; loop ++)
			{

				pack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, raw->route_waypoint_types [loop]);
			}

			// dependents

			for (loop = 0; loop < raw->route_length; loop ++)
			{

				if (raw->route_dependents [loop])
				{

					pack_int_value (en, INT_TYPE_VALID, TRUE);

					pack_entity_safe_ptr (raw->route_dependents [loop]);
				}
				else
				{

					pack_int_value (en, INT_TYPE_VALID, FALSE);
				}
			}

			// return keysite

			pack_entity_safe_ptr (raw->return_keysite);

			#if DEBUG_MODULE

			debug_log ("EN_COMMS: sending set task pointers entity %s %d", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SET_WAYPOINT:
		////////////////////////////////////////
		{
			entity
				*wp;

			//
			// (entity_comms_messages message, entity *en, entity *wp)
			//

			ASSERT (en);

			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GUIDE);

			wp = va_arg (pargs, entity *);

			ASSERT (wp);

			pack_entity_safe_ptr (en);

			pack_entity_safe_ptr (wp);

			#if DEBUG_MODULE

			debug_log ("EN_COMMS: sending set waypoint");

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_STRING:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, string_types type, char *s)
			//

			string_types
				type;

			const char
				*s;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, string_types);

			pack_string_type (type);

			s = va_arg (pargs, const char *);

			pack_string (en, type, s);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending string %s for %s (%d)", s, get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SWITCH_LIST:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, list_types type, entity *parent)
			//

			list_types
				type1,
				type2;

			entity
				*parent;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type1 = va_arg (pargs, list_types);

			pack_list_type (type1);

			parent = va_arg (pargs, entity *);

			pack_entity_safe_ptr (parent);

			type2 = va_arg (pargs, list_types);

			pack_list_type (type2);

			#if DEBUG_MODULE_MESSAGE_TEXT

			if (parent)
			{

				debug_log ("EN_COMMS: sending switch list for %s (%d) list %s to list %s (parent %s (%d))",
							get_local_entity_type_name (en), get_local_entity_index (en), get_list_type_name (type1),
							get_list_type_name (type2), get_local_entity_type_name (parent), get_local_entity_index (parent));
			}
			else
			{

				debug_log ("EN_COMMS: sending switch list for %s (%d) list %s to list %s (parent NULL)",
							get_local_entity_type_name (en), get_local_entity_index (en), get_list_type_name (type1),
							get_list_type_name (type2));
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_SWITCH_PARENT:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, list_types type, entity *parent)
			//

			list_types
				type;

			entity
				*parent;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, list_types);

			pack_list_type (type);

			parent = va_arg (pargs, entity *);

			pack_entity_safe_ptr (parent);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending switch parent for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_TASK_ASSIGN_REQUEST:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en (pilot_entity), entity *task, entity *mobile)
			//

			entity
				*task,
				*mobile;;

			ASSERT (en);

			ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);

			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_PILOT);

			pack_entity_safe_ptr (en);

			task = va_arg (pargs, entity *);

			pack_entity_safe_ptr (task);

			mobile = va_arg (pargs, entity *);

			pack_entity_safe_ptr (mobile);

//			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending assign task request %s for %s", get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_string (en, STRING_TYPE_PILOTS_NAME));

//			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_TASK_ASSIGN_RESULT:
		////////////////////////////////////////
		{
			entity
				*task,
				*mobile;

			//
			// (entity_comms_messages message, entity *pilot, entity *task, entity *mobile)
			//

			ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

			ASSERT (en);

			pack_entity_safe_ptr (en);

			task = va_arg (pargs, entity *);

			pack_entity_safe_ptr (task);

			mobile = va_arg (pargs, entity *);

			pack_entity_safe_ptr (mobile);

//			#if DEBUG_MODULE_MESSAGE_TEXT

			if (task)
			{

				debug_log ("EN_COMMS: sending assign task %s accepted for %s", get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_string (en, STRING_TYPE_PILOTS_NAME));
			}
			else
			{

				debug_log ("EN_COMMS: sending assign task refused for %s", get_local_entity_string (en, STRING_TYPE_PILOTS_NAME));
			}

//			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_TASK_KILL:
		////////////////////////////////////////
		{
			entity
				*victim,
				*aggressor;

			//
			// (entity_comms_messages message, entity *task, entity *victim, entity *aggressor)
			//

			ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

			ASSERT (en);

			victim = va_arg (pargs, entity *);

			aggressor = va_arg (pargs, entity *);

			pack_entity_safe_ptr (en);
			pack_entity_safe_ptr (victim);
			pack_entity_safe_ptr (aggressor);

			debug_log ("EN_COMMS: sending task kill for %s (%d), victim %s (%d), aggressor %s (%d)",
							get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
							get_local_entity_string (victim, STRING_TYPE_FULL_NAME), get_local_entity_index (victim),
							get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME), get_local_entity_index (aggressor));

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_TASK_LOSS:
		////////////////////////////////////////
		{
			entity
				*victim,
				*aggressor;

			//
			// (entity_comms_messages message, entity *task, entity *victim, entity *aggressor)
			//

			ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

			ASSERT (en);

			victim = va_arg (pargs, entity *);

			aggressor = va_arg (pargs, entity *);

			pack_entity_safe_ptr (en);
			pack_entity_safe_ptr (victim);
			pack_entity_safe_ptr (aggressor);

			debug_log ("EN_COMMS: sending task loss for %s (%d), victim %s (%d), aggressor %s (%d)",
							get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
							get_local_entity_string (victim, STRING_TYPE_FULL_NAME), get_local_entity_index (victim),
							get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME), get_local_entity_index (aggressor));

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_UPDATE:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			pack_local_entity_data (en, PACK_MODE_UPDATE_ENTITY);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending update for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_UPDATE_FOG_OF_WAR:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, int in_use)
			//

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending update fog of war");

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_UPDATE_SECTOR_SIDE:
		////////////////////////////////////////
		{
			int
				in_use;

			//
			// (entity_comms_messages message, entity *en, int in_use)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			in_use = va_arg (pargs, int);

			pack_int_value (en, INT_TYPE_IN_USE, in_use);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending update sector side for %s (%d) - in use %d", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en), in_use);

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_UPDATE_SECTOR_SIDE_COUNT:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending update sector side count");

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_VEC3D:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en, vec3d_types type, vec3d *v)
			//

			vec3d_types
				type;

			vec3d
				*v;

			ASSERT (en);

			pack_entity_safe_ptr (en);

			type = va_arg (pargs, vec3d_types);

			pack_vec3d_type (type);

			v = va_arg (pargs, vec3d *);

			pack_vec3d (en, type, v);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending vec3d for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		case ENTITY_COMMS_ZERO_DESIRED_VELOCITY:
		case ENTITY_COMMS_ZERO_VELOCITY:
		////////////////////////////////////////
		{
			//
			// (entity_comms_messages message, entity *en)
			//

			ASSERT (en);

			pack_entity_safe_ptr (en);

			#if DEBUG_MODULE_MESSAGE_TEXT

			debug_log ("EN_COMMS: sending zero velocity for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

			#endif

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Transmit invalid entity comms message = %d", message);

			break;
		}
	}

	va_end (pargs);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_received_entity_comms_messages (void)
{
	int
		done;

	entity_comms_messages
		message;

	////////////////////////////////////////
	//
	// trap single player
	//
	////////////////////////////////////////

	ASSERT (direct_play_get_comms_mode () == DIRECT_PLAY_COMMS_MODE_MULTI);

	////////////////////////////////////////
	//
	// process messages
	//
	////////////////////////////////////////

	set_comms_data_flow (COMMS_DATA_FLOW_RX);

	done = FALSE;

	while (!done)
	{
		message = unpack_entity_comms_message ();

		switch (message)
		{
			////////////////////////////////////////
			case ENTITY_COMMS_ZERO:
			////////////////////////////////////////
			{
				debug_fatal ("ENTITY_COMMS_ZERO encountered during receive");

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_ADD_PLANNER_WAYPOINT:
			////////////////////////////////////////
			{
				entity
					*wp;

				vec3d
					pos;

				int
					create_stack_attributes;

				ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

				wp = unpack_entity_safe_ptr ();

				unpack_vec3d (wp, VEC3D_TYPE_POSITION, &pos);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received add planner waypoint at %f, %f, %f", pos.x, pos.y, pos.z);

				#endif

				create_stack_attributes = force_local_entity_create_stack_attributes;

				set_force_local_entity_create_stack_attributes (TRUE);

				map_add_waypoint (wp, &pos);

				set_force_local_entity_create_stack_attributes (create_stack_attributes);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_ADVISE_TRANSMIT_RECON:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received advise transmit recon");

				#endif

				if (en == get_gunship_entity ())
				{
					set_status_message (get_trans ("ADVISE_TRANSMIT_RECON"), STATUS_MESSAGE_TYPE_ALERT);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_ATTITUDE_ANGLES:
			////////////////////////////////////////
			{
				entity
					*en;

				float
					heading,
					pitch,
					roll;

				en = unpack_entity_safe_ptr ();

				unpack_attitude_angles (en, &heading, &pitch, &roll);

				set_client_server_entity_attitude_angles (en, heading, pitch, roll);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received attitude angle for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_ATTITUDE_MATRIX:
			////////////////////////////////////////
			{
				entity
					*en;

				matrix3x3
					attitude;

				en = unpack_entity_safe_ptr ();

				unpack_attitude_matrix (en, attitude);

				set_client_server_entity_attitude_matrix (en, attitude);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received attitude matrix for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CAMPAIGN_COMPLETED:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, int side)
				//

				entity
					*en;

				entity_sides
					side;

				campaign_completed_types
					complete;

				en = unpack_entity_safe_ptr ();

				side = unpack_int_value (en, INT_TYPE_SIDE);

				complete = unpack_int_value (en, INT_TYPE_SESSION_COMPLETE);

				campaign_completed (side, complete);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received campaign completed by %s", entity_side_names [side]);

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CAPTURE_KEYSITE:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, int side)
				//

				entity
					*en;

				entity_sides
					side;

				en = unpack_entity_safe_ptr ();

				side = unpack_int_value (en, INT_TYPE_SIDE);

				change_local_keysite_building_sides (en, side);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received captured keysite for %s", entity_side_names [side]);

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CHAR_VALUE:
			////////////////////////////////////////
			{
				entity
					*en;

				char_types
					type;

				char
					value;

				en = unpack_entity_safe_ptr ();

				type = unpack_char_type ();

				value = unpack_char_value (en, type);

				set_client_server_entity_char_value (en, type, value);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received char for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CREATE:
			////////////////////////////////////////
			{
				entity_types
					type;

				int
					index,
					num_bytes;

				type = unpack_entity_type ();

				index = unpack_entity_safe_index ();

				num_bytes = unpack_entity_attributes (attribute_buffer);

				ASSERT (num_bytes <= ATTRIBUTE_BUFFER_SIZE);

				create_client_server_entity (type, index, attribute_buffer);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received create for %s (index %d)", entity_type_names [type], index);

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CREATE_META_EXPLOSION:
			////////////////////////////////////////
			{
				entity
					*parent;

				meta_explosion_types
					type;

				int
					loop,
					list_count,
					*entity_index_list;

				vec3d
					position;

				type = unpack_int_value (NULL, INT_TYPE_META_EXPLOSION_TYPE);

				unpack_vec3d (NULL, VEC3D_TYPE_POSITION, &position);

				parent = unpack_entity_safe_ptr ();

				list_count = count_entities_in_meta_explosion (type);

				entity_index_list = malloc_fast_mem (sizeof (int) * list_count);

				for (loop = 0; loop < list_count; loop ++)
				{
					entity_index_list [loop] = unpack_entity_safe_index ();
				}

				create_meta_explosion (type, &position, parent, entity_index_list);

				free_mem (entity_index_list);

				#if DEBUG_MODULE_MESSAGE_TEXT

				if (parent)
				{

					debug_log ("EN_COMMS: received create meta explosion for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));
				}
				else
				{

					debug_log ("EN_COMMS: received create meta explosion");
				}

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CREATE_META_SMOKE_LIST_SPECIFIED_OFFSET:
			////////////////////////////////////////
			{
				entity
					*parent;

				meta_smoke_list_types
					type;

				int
					loop,
					list_count,
					*entity_index_list;

				vec3d
					rel_pos;

				type = unpack_int_value (NULL, INT_TYPE_META_SMOKE_LIST_TYPE);

				parent = unpack_entity_safe_ptr ();

				if (parent)
				{
					unpack_vec3d (NULL, VEC3D_TYPE_RELATIVE_POSITION, &rel_pos);
				}
				else
				{
					unpack_vec3d (NULL, VEC3D_TYPE_POSITION, &rel_pos);
				}

				list_count = count_entities_in_meta_smoke_list (type);

				entity_index_list = malloc_fast_mem (sizeof (int) * list_count);

				for (loop = 0; loop < list_count; loop ++)
				{
					entity_index_list [loop] = unpack_entity_safe_index ();
				}

				create_meta_smoke_list_specified_offset (type, parent, &rel_pos, entity_index_list);

				free_mem (entity_index_list);

				#if DEBUG_MODULE_MESSAGE_TEXT

				if (parent)
				{

					debug_log ("EN_COMMS: received create smoke list ( spec offset ) for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));
				}
				else
				{

					debug_log ("EN_COMMS: received create smoke list ( sub offset )");
				}

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CREATE_META_SMOKE_LIST_SUB_OBJECT_OFFSET:
			////////////////////////////////////////
			{
				entity
					*parent;

				meta_smoke_list_types
					type;

				int
					loop,
					list_count,
					sub_object_type,
					sub_object_depth,
					*entity_index_list;

				type = unpack_int_value (NULL, INT_TYPE_META_SMOKE_LIST_TYPE);

				parent = unpack_entity_safe_ptr ();

				sub_object_type = unpack_int_value (NULL, INT_TYPE_SUB_OBJECT_TYPE);

				sub_object_depth = unpack_int_value (NULL, INT_TYPE_SUB_OBJECT_DEPTH);

				list_count = count_entities_in_meta_smoke_list (type);

				entity_index_list = malloc_fast_mem (sizeof (int) * list_count);

				for (loop = 0; loop < list_count; loop ++)
				{
					entity_index_list [loop] = unpack_entity_safe_index ();
				}

				create_meta_smoke_list_sub_object_offset (type, parent, sub_object_type, sub_object_depth, entity_index_list);

				free_mem (entity_index_list);

				#if DEBUG_MODULE_MESSAGE_TEXT

				if (parent)
				{

					debug_log ("EN_COMMS: received create smoke list ( spec offset ) for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));
				}
				else
				{

					debug_log ("EN_COMMS: received create smoke list ( sub offset )");
				}

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CREATE_SOUND_EFFECT:
			////////////////////////////////////////
			{
				entity
					*parent;

				entity_sub_types
					sub_type;

				int
					loop,
					index,
					valid,
					side,
					channel,
					locality,
					looping,
					valid_position,
					sample_count,
					*sample_index_list,
					create_stack_attributes;

				float
					amp, pitch;

				vec3d
					*pos,
					position;

				index = unpack_entity_safe_index ();

				parent = unpack_entity_safe_ptr ();

				side = unpack_int_value (NULL, INT_TYPE_SIDE);

				sub_type = unpack_int_value (NULL, INT_TYPE_ENTITY_SUB_TYPE);

				channel = unpack_int_value (NULL, INT_TYPE_SOUND_CHANNEL);

				locality = unpack_int_value (NULL, INT_TYPE_SOUND_LOCALITY);

				valid_position = unpack_int_value (NULL, INT_TYPE_VALID);

				if (valid_position)
				{
					unpack_vec3d (NULL, VEC3D_TYPE_POSITION, &position);

					pos = &position;
				}
				else
				{
					pos = NULL;
				}

				amp = unpack_float_value (NULL, FLOAT_TYPE_AMPLIFICATION);

				pitch = unpack_float_value (NULL, FLOAT_TYPE_SOUNDPITCH);

				valid = unpack_int_value (NULL, INT_TYPE_VALID_SOUND_EFFECT);

				looping = unpack_int_value (NULL, INT_TYPE_SOUND_EFFECT_LOOPING);

				sample_count = unpack_int_value (NULL, INT_TYPE_SOUND_EFFECT_SEQUENCE_COUNT);

				ASSERT (sample_count > 0);

				sample_index_list = malloc_fast_mem (sizeof (sound_sample_indices) * sample_count);

				for (loop = 0; loop < sample_count; loop ++)
				{
					sample_index_list [loop] = unpack_int_value (NULL, INT_TYPE_SOUND_EFFECT_INDEX);
				}

				create_stack_attributes = force_local_entity_create_stack_attributes;

				set_force_local_entity_create_stack_attributes (TRUE);

				create_local_sound_effect_entity
				(
					index,
					parent,
					side,
					sub_type,
					channel,
					locality,
					pos,
					amp,
					pitch,
					valid,
					looping,
					sample_count,
					sample_index_list
				);

				set_force_local_entity_create_stack_attributes (create_stack_attributes);

				free_mem (sample_index_list);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received create sound effect for %s (%d)", entity_type_names [parent->type], get_local_entity_index (parent));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CREATE_WAYPOINT_ROUTE:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, unsigned int check_sum)
				//

				vec3d
					*start_ptr,
					*stop_ptr,
					start,
					stop;

				entity
					*task,
					*group,
					*return_keysite;
	
				unsigned int
					*waypoint_indices,
					loop,
					count,
					check_sum;
	
				task = unpack_entity_safe_ptr ();

				group = unpack_entity_safe_ptr ();

				return_keysite = unpack_entity_safe_ptr ();

				start_ptr = NULL;
				stop_ptr = NULL;

				if (unpack_int_value (NULL, INT_TYPE_VALID))
				{

					unpack_vec3d (NULL, VEC3D_TYPE_POSITION, &start);

					start_ptr = &start;
				}

				if (unpack_int_value (NULL, INT_TYPE_VALID))
				{

					unpack_vec3d (NULL, VEC3D_TYPE_POSITION, &stop);

					stop_ptr = &stop;
				}
	
				////////////////////////////////////////
	
				check_sum = unpack_int_value (NULL, INT_TYPE_ROUTE_CHECK_SUM);
	
				////////////////////////////////////////

				count = unpack_int_value (NULL, INT_TYPE_ROUTE_LENGTH);

				waypoint_indices = malloc_heap_mem (sizeof (int) * count);

				for (loop = 0; loop < count; loop ++)
				{

					waypoint_indices [loop] = unpack_entity_safe_index ();
				}

				if (create_generic_waypoint_route (group, task, return_keysite, start_ptr, stop_ptr, waypoint_indices, count))
				{

					debug_log ("EN_COMMS: created route on client successfully");
				}

				free_mem (waypoint_indices);
	
				#if DEBUG_MODULE_MESSAGE_TEXT
	
				debug_log ("EN_COMMS: received create waypoint route for %s (%d) check_sum %d", get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_index (task), check_sum);
	
				#endif
	
				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_CREATE_WEAPON:
			////////////////////////////////////////
			{
				entity
					*launcher;

				entity_sub_types
					weapon_sub_type;

				int
					weapon_index,
					burst_size,
					*smoke_trail_indices,
					num_smoke_trail_entities,
					i;

				meta_smoke_list_types
					smoke_trail_type;

				launcher = unpack_entity_safe_ptr ();
	
				////////////////////////////////////////
				// DEBUG COMMS WEAPON LAG TIMING
				////////////////////////////////////////
				if (get_comms_model () == COMMS_MODEL_CLIENT)
				{
	
					if (launcher == get_gunship_entity ())
					{

						comms_weapon_lag_timing = FALSE;
	
						comms_weapon_lag_time = ((float) get_system_time () / (float) TIME_1_SECOND) - comms_weapon_lag_time;
					}
				}
				////////////////////////////////////////
				// DEBUG COMMS WEAPON LAG TIMING
				////////////////////////////////////////
	
				////////////////////////////////////////

				weapon_sub_type = unpack_int_value (NULL, INT_TYPE_ENTITY_SUB_TYPE);

				ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

				////////////////////////////////////////

				weapon_index = unpack_entity_safe_index ();

				////////////////////////////////////////

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					burst_size = BURST_SIZE_DONT_CARE;
				}
				else
				{
					if (weapon_database[weapon_sub_type].rate_of_fire != FIRE_SINGLE_WEAPON)
					{
						burst_size = unpack_int_value (NULL, INT_TYPE_WEAPON_BURST_SIZE);
					}
					else
					{
						burst_size = 1;
					}
				}

				////////////////////////////////////////

				smoke_trail_indices = NULL;

				if (get_comms_model () == COMMS_MODEL_CLIENT)
				{
					smoke_trail_type = weapon_database[weapon_sub_type].smoke_trail_type;

					if (smoke_trail_type != META_SMOKE_LIST_TYPE_NONE)
					{
						num_smoke_trail_entities = count_entities_in_meta_smoke_list (smoke_trail_type);

						ASSERT (num_smoke_trail_entities > 0);

						smoke_trail_indices = malloc_fast_mem (sizeof (int) * num_smoke_trail_entities);

						for (i = 0; i < num_smoke_trail_entities; i++)
						{
							smoke_trail_indices[i] = unpack_entity_safe_index ();
						}
					}
				}

				////////////////////////////////////////

				create_client_server_entity_weapon (launcher, weapon_sub_type, weapon_index, burst_size, smoke_trail_indices);

				////////////////////////////////////////

				if (smoke_trail_indices)
				{
					free_mem (smoke_trail_indices);
				}

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received create weapon %s for %s (%d)", entity_sub_type_weapon_names [weapon_sub_type], entity_type_names [launcher->type], get_local_entity_index (launcher));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_DAMAGE_PLAYER:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, int damage, int random);
				//

				entity
					*en;

				unsigned int
					random,
					damage;

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				damage = unpack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_FLAGS);

				random = unpack_int_value (en, INT_TYPE_VALID);

				//
				// Only damage correct player
				//

				if (en == get_gunship_entity ())
				{

					dynamics_damage_model (damage, random);

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: received damage helicopter dynamics %d for %s (%d)", damage, get_local_entity_type_name (en), get_local_entity_index (en));

					#endif
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_DAMAGE_PLAYER_AVIONICS:
			////////////////////////////////////////
			{
				entity
					*en;

				gunship_damage_levels
					damage_level;

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				damage_level = unpack_int_value (en, INT_TYPE_HELICOPTER_DAMAGE_LEVEL);

				if (en == get_gunship_entity ())
				{
					damage_gunship (damage_level);

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: received damage helicopter avionics %d for %s (%d)", damage_level, get_local_entity_type_name (en), get_local_entity_index (en));

					#endif
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_DAMAGE_WEAPON_PACKAGE:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					weapon_package_heading_depth,
					weapon_package_damaged;

				entity_sub_types
					weapon_sub_type;

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				weapon_package_heading_depth = unpack_int_value (en, INT_TYPE_WEAPON_PACKAGE_HEADING_DEPTH);

				weapon_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

				weapon_package_damaged = unpack_int_value (en, INT_TYPE_WEAPON_PACKAGE_DAMAGED);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log
				(
					"EN_COMMS: receiving damage weapon package for %s (%d), heading_depth = %d, weapon_sub_type = %d, damaged = %d",
					get_local_entity_string (en, STRING_TYPE_FULL_NAME),
					get_local_entity_index (en),
					weapon_package_heading_depth,
					weapon_sub_type,
					weapon_package_damaged
				);

				#endif

				set_client_server_entity_weapon_damage (en, weapon_package_heading_depth, weapon_sub_type, weapon_package_damaged);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_DESTROY:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received destroy entity %s index %d", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				destroy_client_server_entity (en);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_DESTROY_FAMILY:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received destroy entity family %s index %d", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				destroy_client_server_entity_family (en);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_DESTROY_LOCAL_FAMILY:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received destroy local entity family %s index %d", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				destroy_local_entity_family (en);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_END:
			////////////////////////////////////////
			{
				done = TRUE;

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_FLOAT_VALUE:
			////////////////////////////////////////
			{
				entity
					*en;

				float_types
					type;

				float
					value;

				en = unpack_entity_safe_ptr ();

				type = unpack_float_type ();

				value = unpack_float_value (en, type);

				#if FAST_TRACK

				if ((float_type_database[type].fast_track) && (get_comms_model () == COMMS_MODEL_CLIENT) && (en == get_gunship_entity ()))
				{
					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: ignore received fast_track float %s = %f for %s (%d)", float_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

					#endif
				}
				else
				{
					set_client_server_entity_float_value (en, type, value);

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: received float %s = %f for %s (%d)", float_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

					#endif
				}

				#else

				set_client_server_entity_float_value (en, type, value);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received float %s = %f for %s (%d)", float_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_INT_VALUE:
			////////////////////////////////////////
			{
				entity
					*en;

				int_types
					type;

				int
					value;

				en = unpack_entity_safe_ptr ();

				type = unpack_int_type ();

				value = unpack_int_value (en, type);

				#if FAST_TRACK

				if ((int_type_database[type].fast_track) && (get_comms_model () == COMMS_MODEL_CLIENT) && (en == get_gunship_entity ()))
				{
					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: ignore received fast_track int value %s = %d for %s (%d)", int_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

					#endif
				}
				else
				{
					set_client_server_entity_int_value (en, type, value);

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: received int value %s = %d for %s (%d)", int_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

					#endif
				}

				#else

				set_client_server_entity_int_value (en, type, value);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received int value %s = %d for %s (%d)", int_type_database [type].name, value, get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_KILL:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					create_stack_attributes;

				en = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received kill for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				create_stack_attributes = force_local_entity_create_stack_attributes;

				set_force_local_entity_create_stack_attributes (TRUE);

				kill_client_server_entity (en);

				set_force_local_entity_create_stack_attributes (create_stack_attributes);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_MOBILE_KILL:
			////////////////////////////////////////
			{
				entity
					*en,
					*victim;

				en = unpack_entity_safe_ptr ();

				victim = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received mobile kill for %s (%d)", get_local_entity_type_name (victim), get_local_entity_index (victim));

				#endif

				ASSERT (get_local_entity_type (en) == ENTITY_TYPE_FORCE);
	
				add_mobile_to_force_kills_stats (en, victim);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_MOBILE_LAND:
			////////////////////////////////////////
			{
				entity
					*wp,
					*en;

				en = unpack_entity_safe_ptr ();

				wp = unpack_entity_safe_ptr ();

				insert_local_entity_into_parents_child_list (en, LIST_TYPE_CURRENT_WAYPOINT, wp, NULL);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received mobile land for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDED);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_MOBILE_TAKEOFF:
			////////////////////////////////////////
			{
				entity
					*en,
//					*cwp,
//					*group,
					*landing_en;
//					*landing_task;

				en = unpack_entity_safe_ptr ();

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{

					set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);

					delete_local_entity_from_parents_child_list (en, LIST_TYPE_MOVEMENT_DEPENDENT);

					//
					// Unlock landing lock if group doesn't have task (ie it wouldn't have been unlocked automatically be task assignment)
					//

					landing_en = NULL;//get_local_group_member_landing_entity (en);

//					group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

//					if ((group) && (!get_local_entity_first_child (group, LIST_TYPE_TASK_STACK)))
					{

//						cwp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

//						if (cwp)
//						{

//							landing_task = get_local_entity_parent (cwp, LIST_TYPE_WAYPOINT);

//							landing_en = get_local_entity_parent (landing_task, LIST_TYPE_GENERIC_TASK);

							if (landing_en)
							{

								notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing_en, en);

//								delete_local_entity_from_parents_child_list (en, LIST_TYPE_CURRENT_WAYPOINT);
							}
//						}
					}
				}

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received mobile takeoff for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_MOVE_PLANNER_WAYPOINT:
			////////////////////////////////////////
			{
				entity
					*member,
					*wp;

				vec3d
					pos;

				ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

				wp = unpack_entity_safe_ptr ();

				unpack_vec3d (wp, VEC3D_TYPE_POSITION, &pos);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received move planner waypoint for %s (%d) to %f, %f, %f", get_local_entity_type_name (wp), get_local_entity_index (wp), pos.x, pos.y, pos.z);

				#endif

				set_client_server_entity_vec3d (wp, VEC3D_TYPE_POSITION, &pos);

				member = get_local_entity_first_child (wp, LIST_TYPE_CURRENT_WAYPOINT);

				while (member)
				{

//					set_client_server_mobile_internal_waypoint (member, wp);

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS:     setting internal waypoint for %s (%d) to %f, %f, %f", get_local_entity_type_name (member), get_local_entity_index (member), pos.x, pos.y, pos.z);

					#endif

					member = get_local_entity_child_succ (member, LIST_TYPE_CURRENT_WAYPOINT);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PAUSE_SOUND_TYPE:
			////////////////////////////////////////
			{
				entity
					*en;

				entity_sub_types
					type;

				float
					delay;

				//
				// (entity_comms_messages message, entity *en, entity_sub_types type, float delay)
				//

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

				delay = unpack_float_value (en, FLOAT_TYPE_VALID_EFFECT_LIFETIME);

				pause_local_entity_sound_type (en, type, delay);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received pause sound type for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PAUSE_WEAPON_SOUND_TYPE:
			////////////////////////////////////////
			{
				entity
					*en;

				entity_sub_types
					weapon_sub_type;

				//
				// (entity_comms_messages message, entity *en, entity_sub_types weapon_sub_type)
				//

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				weapon_sub_type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

				pause_local_continuous_weapon_sound_effect (en, weapon_sub_type);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received pause weapon sound type for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PILOT_COMMUNICATION:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *sender, entity *target, int type, char *message)
				//

				entity
					*sender,
					*target;

				message_text_types
					type;

				char
					*string,
					message [STRING_TYPE_MESSAGE_LENGTH];

				sender = unpack_entity_safe_ptr ();

				target = unpack_entity_safe_ptr ();

				type = unpack_int_value (NULL, INT_TYPE_MESSAGE_TEXT_TYPE);

				if (message_text_type_send_string (type))
				{
					unpack_string (NULL, STRING_TYPE_PILOT_MESSAGE, message);

					string = message;

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: received communication message %s", message);

					#endif
				}
				else
				{
					string = NULL;
				}

				//
				// notify messaging system of received message
				//

				set_incoming_message (sender, target, type, string);

				//
				// server needs to forward any messages on to clients (unless it was only meant for him)
				//

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					//
					// very dodgy stuff indeed...
					//

					set_comms_data_flow (COMMS_DATA_FLOW_TX);

					transmit_entity_comms_message (ENTITY_COMMS_PILOT_COMMUNICATION, sender, target, type, string);

					set_comms_data_flow (COMMS_DATA_FLOW_RX);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PILOT_PFZ_TRANSFER:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *sender, entity *target, int type, char *message)
				//

				entity
					*sender,
					*wingman;

				entity
					*targets[17];
				
				unsigned int i;

				vec3d corner1, corner2, corner3, corner4;

				sender = unpack_entity_safe_ptr ();
				wingman = unpack_entity_safe_ptr ();

				corner1.x = unpack_float_value(NULL, FLOAT_TYPE_PFZ_X1);
				corner1.z = unpack_float_value(NULL, FLOAT_TYPE_PFZ_Y1);
				corner2.x = unpack_float_value(NULL, FLOAT_TYPE_PFZ_X2);
				corner2.z = unpack_float_value(NULL, FLOAT_TYPE_PFZ_Y2);
				corner3.x = unpack_float_value(NULL, FLOAT_TYPE_PFZ_X3);
				corner3.z = unpack_float_value(NULL, FLOAT_TYPE_PFZ_Y3);
				corner4.x = unpack_float_value(NULL, FLOAT_TYPE_PFZ_X4);
				corner4.z = unpack_float_value(NULL, FLOAT_TYPE_PFZ_Y4);

				for (i=0; i < 16; i++)
				{
					targets[i] = unpack_entity_safe_ptr();
					if (!targets[i])
						break;

					if (get_gunship_entity() == wingman)  // add targets to radar
						if (!get_local_entity_parent (targets[i], LIST_TYPE_GUNSHIP_TARGET))  // target we don't have already
							insert_local_entity_into_parents_child_list (targets[i], LIST_TYPE_GUNSHIP_TARGET, wingman, NULL);	
				}

				// be sure to terminate
				targets[i] = NULL;

				//
				// notify messaging system of received message
				//

				if (get_gunship_entity() == wingman)
				{	// someone has sent us a pfz, create it
					int pfz_number;
					char attack_message[100];

					add_pfz(&corner1, &corner2, &corner3, &corner4);
					pfz_number = next_free_pfz;

					sprintf(attack_message, "Attack PFZ %d", pfz_number);

					set_incoming_message(sender, get_pilot_entity(), MESSAGE_TEXT_LOCAL_MESSAGE, attack_message);
				}

				//
				// server needs to forward any messages on to clients (unless it was only meant for him)
				//

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					//
					// very dodgy stuff indeed...
					//

					set_comms_data_flow (COMMS_DATA_FLOW_TX);

					transmit_pfz(sender, wingman,
						corner1.x, corner1.z,
						corner2.x, corner2.z,
						corner3.x, corner3.z,
						corner4.x, corner4.z,
						targets);

					set_comms_data_flow (COMMS_DATA_FLOW_RX);

					// if message is for AI wingman create engage tasks
/*					if (get_local_entity_int_value (wingman, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
					{
						entity
							*target,
							*group;

						unsigned int valid_members = 0, member_number;

						group = get_local_entity_parent(wingman, LIST_TYPE_MEMBER);

						member_number = get_local_entity_int_value(wingman, INT_TYPE_GROUP_MEMBER_NUMBER);
						valid_members = (1 << member_number);
						
			//			clear_local_entity_list(wingman, LIST_TYPE_DESIGNATED_TARGET);
				
						for (target = targets[0];
							 target;
							 target++)
						{
							debug_log("adding engage task for %p", target);
			//					insert_local_ry_into_parents_child_list(target, LIST_TYPE_DESIGNATED_TARGET, wingman, NULL);
							engage_specific_target(group, target, valid_members, FALSE);
						}
					}*/
					if (get_local_entity_int_value (wingman, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
						engage_specific_targets(wingman, targets);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PILOT_REQUEST_ACCEPTED:
			////////////////////////////////////////
			{

				entity
					*en;
	
				int
					pilot_index,
					destination_id;
				//
				// (entity_comms_messages message, int destination_id, int index)
				//

				en = unpack_entity_safe_ptr ();
	
				destination_id = unpack_int_value (en, INT_TYPE_VALUE);
	
				pilot_index = unpack_int_value (en, INT_TYPE_VALUE);

				//#if DEBUG_MODULE_MESSAGE_TEXT
		
				debug_log ("EN_COMMS: received Pilot request accepted to %d for entity %d", destination_id, pilot_index);
		
				//#endif

				if (destination_id == direct_play_get_player_id ())
				{

					set_pilot_entity (get_local_entity_safe_ptr (pilot_index));
				}
	
				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PLAY_CPG_CONTACT_MESSAGE:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					speech_index1,
					speech_index2,
					speech_index3;

				//
				// (entity_comms_messages message, entity *en, int speech_index1, int speech_index2, int speech_index3)
				//

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				speech_index1 = unpack_int_value (en, INT_TYPE_SPEECH_INDEX);

				speech_index2 = unpack_int_value (en, INT_TYPE_SPEECH_INDEX);

				speech_index3 = unpack_int_value (en, INT_TYPE_SPEECH_INDEX);

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					play_client_server_cpg_contact_message (en, speech_index1, speech_index2, speech_index3);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PLAY_CPG_MESSAGE:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					speech_index,
					speech_category;

				float
					priority,
					expire_time,
					category_silence_timer;

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				priority = unpack_float_value (en, FLOAT_TYPE_SPEECH_PRIORITY);

				expire_time = unpack_float_value (en, FLOAT_TYPE_SPEECH_EXPIRE_TIME);

				speech_category = unpack_int_value (en, INT_TYPE_SPEECH_CATEGORY);

				category_silence_timer = unpack_float_value (en, FLOAT_TYPE_SPEECH_CATEGORY_SILENCE_TIMER);

				speech_index = unpack_int_value (en, INT_TYPE_SPEECH_INDEX);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received play cpg message for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					play_client_server_cpg_message (en, priority, expire_time, speech_category, category_silence_timer, speech_index);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PLAY_WARNING_MESSAGE:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					speech_index;

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				speech_index = unpack_int_value (en, INT_TYPE_SPEECH_INDEX);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received play warning message for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					play_client_server_warning_message (en, speech_index);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PLAYER_KILL:
			////////////////////////////////////////
			{
				entity
					*aggressor,
					*victim;

				aggressor = unpack_entity_safe_ptr ();

				victim = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received player kill for %s (%d)", get_local_entity_type_name (victim), get_local_entity_index (victim));

				#endif

				if ((get_local_entity_int_value (victim, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL) ||
					((aggressor) && (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL)))
				{
					inc_player_log_kills (get_global_gunship_side (), get_current_player_log (), victim);
				}
/*
				if (victim == get_gunship_entity ())
				{
					start_game_exit (GAME_EXIT_CRASH, FALSE);
				}
*/
				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PLAYER_TASK_COMPLETED:
			////////////////////////////////////////
			{
				entity
					*task,
					*en;

				en = unpack_entity_safe_ptr ();

				task = unpack_entity_safe_ptr ();

				ASSERT (en);

				ASSERT (task);

//				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received player task %s (%d) completed for %s (%d)",
							get_local_entity_string (task, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (task),
							get_local_entity_string (en, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (en));

//				#endif

				if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL)
				{
					notify_gunship_entity_mission_completed (en, task);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_PLAYER_TASK_TERMINATED:
			////////////////////////////////////////
			{
				entity
					*task,
					*en;

				en = unpack_entity_safe_ptr ();

				task = unpack_entity_safe_ptr ();

				ASSERT (en);

				ASSERT (task);

//				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received player task %s (%d) terminated for %s (%d)",
							get_local_entity_string (task, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (task),
							get_local_entity_string (en, STRING_TYPE_FULL_NAME),
							get_local_entity_safe_index (en));

//				#endif

				if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL)
				{
					notify_gunship_entity_mission_terminated (en, task);
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_RADIO_MESSAGE:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					message_type,
					message_value,
					create_stack_attributes;

				//
				// (entity_comms_messages message, entity *en, int message_type, int message_value)
				//

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				message_type = unpack_int_value (en, INT_TYPE_RADIO_MESSAGE_TYPE);

				message_value = unpack_int_value (en, INT_TYPE_RADIO_MESSAGE_VALUE);

				create_stack_attributes = force_local_entity_create_stack_attributes;

				set_force_local_entity_create_stack_attributes (TRUE);

				process_radio_message (en, message_type, message_value);

				set_force_local_entity_create_stack_attributes (create_stack_attributes);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received radio message for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_REPAIR_ANTI_AIRCRAFT_GROUP:
			////////////////////////////////////////
			{
				entity
					*en;

				//
				// (entity_comms_messages message, entity *en)
				//

				en = unpack_entity_safe_ptr ();
				
				ASSERT (en);

				ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GROUP);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: Received Repair AA Group for (%d)", get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_REPAIR_BRIDGE_ENTITY:
			////////////////////////////////////////
			{
				entity
					*en;

				//
				// (entity_comms_messages message, entity *en)
				//

				en = unpack_entity_safe_ptr ();
				
				ASSERT (en);

				ASSERT (get_local_entity_type (en) == ENTITY_TYPE_BRIDGE);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: Received Repair Bridge for (%d)", get_local_entity_index (en));

				#endif

				repair_local_bridge_entity (en);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_REQUEST_TARGET_LIST:
			////////////////////////////////////////
			{
				entity
					*en,
					*destination;

				//
				// (entity_comms_messages message, entity *en, entity *destination)
				//

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				destination = unpack_entity_safe_ptr ();

				ASSERT (destination);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received request target list from %s (%d) to %s (%d)",
								get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
								get_local_entity_string (destination, STRING_TYPE_FULL_NAME), get_local_entity_index (destination));

				#endif

				if (destination == get_gunship_entity ())
				{
					int
						loop,
						*index_list,
						target_count;

					target_count = get_number_of_valid_gunship_targets (en);

					if (target_count > 0)
					{
						target_count = min (target_count, 255);

						index_list = malloc_fast_mem (sizeof (int) * target_count);

						for (loop = 0; loop < target_count; loop ++)
						{
							index_list [loop] = get_valid_gunship_target_safe_index (en, loop);
						}

						set_comms_data_flow (COMMS_DATA_FLOW_TX);

						transmit_entity_comms_message (ENTITY_COMMS_SEND_TARGET_LIST, destination, en, target_count, index_list);

						set_comms_data_flow (COMMS_DATA_FLOW_RX);

						free_mem (index_list);
					}
				}
				else
				{
					//
					// server needs to forward any messages on to clients
					//

					if (get_comms_model () == COMMS_MODEL_SERVER)
					{
						set_comms_data_flow (COMMS_DATA_FLOW_TX);

						transmit_entity_comms_message (ENTITY_COMMS_REQUEST_TARGET_LIST, en, destination);

						set_comms_data_flow (COMMS_DATA_FLOW_RX);
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_RESTORE_ENTITY:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					operational_state;

				vec3d
					pos;

				en = unpack_entity_safe_ptr ();

				unpack_vec3d (en, VEC3D_TYPE_POSITION, &pos);

				operational_state = unpack_int_value (en, INT_TYPE_OPERATIONAL_STATE);

				//
				// currently only for helicopters, but could make it more generic if possible
				//

				if (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER)
				{
					restore_helicopter_entity (en, &pos, operational_state);
				}

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received restore entity for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_RESTORE_FIXED_ENTITY:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				restore_local_fixed_entity (en);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received restore entity for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_RESUME_SOUND_TYPE:
			////////////////////////////////////////
			{
				entity
					*en;

				entity_sub_types
					type;

				//
				// (entity_comms_messages message, entity *en, entity_sub_types type)
				//

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				type = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

				resume_local_entity_sound_type (en, type);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received resume sound type for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_ROUTED_VEHICLE_ROUTE_DATA:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, vec3d *pos, int operational_state)
				//
	
				node_link_data
					*sub_route_node;

				int
					count,
					this_index,
					next_index;

				entity
					*en,
					*group,
					*mb;

				// unpack group data
	
				en = unpack_entity_safe_ptr ();
	
				ASSERT (en);
	
				this_index = unpack_int_value (en, INT_TYPE_WAYPOINT_THIS_INDEX);
				next_index = unpack_int_value (en, INT_TYPE_WAYPOINT_NEXT_INDEX);
	
				sub_route_node = get_road_sub_route (this_index, next_index, &count, NULL);

				// loop each member

				group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

				mb = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

				while (mb)
				{
	
					routed_vehicle
						*raw;
	
					set_local_entity_int_value (mb, INT_TYPE_WAYPOINT_THIS_INDEX, this_index);
					set_local_entity_int_value (mb, INT_TYPE_WAYPOINT_NEXT_INDEX, next_index);
					set_local_entity_int_value (mb, INT_TYPE_SUB_WAYPOINT_COUNT, count);
	
					if (sub_route_node)
					{
	
						raw = get_local_entity_data (mb);
		
						raw->sub_route = sub_route_node;
					}
	
					#if DEBUG_MODULE_MESSAGE_TEXT
	
					debug_log ("EN_COMMS: received routed_vehicle %d route between %d and %d", get_local_entity_index (mb), raw->waypoint_this_index, raw->waypoint_next_index);
	
					#endif
	
					mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
				}
	
				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SEND_TARGET_LIST:
			////////////////////////////////////////
			{
				entity
					*en,
					*destination;

				int
					loop,
					*index_list,
					target_count;

				//
				// (entity_comms_messages message, entity *en, entity *destination, int target_count, int index_list [target_count])
				//

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				destination = unpack_entity_safe_ptr ();

				ASSERT (destination);

				target_count = unpack_int_value (en, INT_TYPE_HAND_OFF_TARGET_COUNT);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received %d targets from %s (%d) to %s (%d)", target_count,
								get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en),
								get_local_entity_string (destination, STRING_TYPE_FULL_NAME), get_local_entity_index (destination));

				#endif

				ASSERT (target_count > 0);

				index_list = malloc_fast_mem (sizeof (int) * target_count);

				for (loop = 0; loop < target_count; loop ++)
				{
					index_list [loop] = unpack_entity_safe_index ();
				}

				if (destination == get_gunship_entity ())
				{
					for (loop = 0; loop < target_count; loop ++)
					{
						set_valid_gunship_target_safe_index (index_list [loop]);
					}
				}
				else
				{
					//
					// server needs to forward any messages on to clients
					//

					if (get_comms_model () == COMMS_MODEL_SERVER)
					{
						set_comms_data_flow (COMMS_DATA_FLOW_TX);

						transmit_entity_comms_message (ENTITY_COMMS_SEND_TARGET_LIST, en, destination, target_count, index_list);

						set_comms_data_flow (COMMS_DATA_FLOW_RX);
					}
				}

				free_mem (index_list);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SET_EXTERNAL_VIEW_ENTITY:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en)
				//

				entity
					*en;

				en = unpack_entity_safe_ptr ();

				ASSERT (en);

				#if DEBUG_MODULE

				debug_log ("EN_COMMS: sending set external view entity to %s (%d)", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

				#endif

				set_external_view_entity (en);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SET_GUIDE_CRITERIA:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, int type, int valid, float value)
				//

				entity
					*en;
	
				int
					type,
					valid;
	
				float
					value;
	
				en = unpack_entity_safe_ptr ();

				ASSERT (en);
	
				ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GUIDE);

				ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);
	
				type = unpack_int_value (en, INT_TYPE_GUIDE_CRITERIA_TYPE);

				valid = unpack_int_value (en, INT_TYPE_VALID);
	
				value = unpack_float_value (en, FLOAT_TYPE_GUIDE_CRITERIA_VALUE);
	
				#if DEBUG_MODULE
	
				debug_log ("EN_COMMS: received set guide criteria for %d", get_local_entity_index (en));
	
				#endif
	
				set_local_guide_criteria_valid (en, type, valid, value);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SET_GUIDE_POSITION_ENTITY:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, entity *position_entity)
				//

				entity
					*en,
					*position_entity;
	
				en = unpack_entity_safe_ptr ();

				ASSERT (en);
	
				ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GUIDE);

				ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);
	
				position_entity = unpack_entity_safe_ptr ();

				#if DEBUG_MODULE
	
				debug_log ("EN_COMMS: received set guide position entity for %d", get_local_entity_index (en));
	
				#endif
	
				set_local_entity_ptr_value (en, PTR_TYPE_POSITION_ENTITY, position_entity);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SET_TASK_POINTERS:
			////////////////////////////////////////
			{

				entity
					*en;

				task
					*raw;

				int
					loop;

				//
				// (entity_comms_messages message, entity *en)
				//
	
				en = unpack_entity_safe_ptr ();
	
				raw = get_local_entity_data (en);

				// malloc memory

				raw->route_nodes = (vec3d *) malloc_heap_mem (sizeof (vec3d) * raw->route_length);
				memset (raw->route_nodes, 0, sizeof (vec3d) * raw->route_length);
			
				raw->route_dependents = (entity **) malloc_heap_mem (sizeof (entity *) * raw->route_length);
				memset (raw->route_dependents, 0, sizeof (entity *) * raw->route_length);
			
				raw->route_waypoint_types = (entity_sub_types *) malloc_heap_mem (sizeof (entity_sub_types) * raw->route_length);
				memset (raw->route_waypoint_types, 0, sizeof (entity_sub_types) * raw->route_length);
			
				raw->route_formation_types = (formation_types *) malloc_heap_mem (sizeof (entity_sub_types) * raw->route_length);
				memset (raw->route_formation_types, 0, sizeof (entity_sub_types) * raw->route_length);
				
				// positions
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{
	
					unpack_vec3d (en, VEC3D_TYPE_POSITION, &raw->route_nodes [loop]);
				}
	
				// formations
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{

					raw->route_formation_types [loop] = unpack_int_value (en, INT_TYPE_WAYPOINT_FORMATION);
				}
	
				// waypoint types
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{

					raw->route_waypoint_types [loop] = unpack_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
				}
	
				// dependents
	
				for (loop = 0; loop < raw->route_length; loop ++)
				{

					if (unpack_int_value (en, INT_TYPE_VALID))
					{
	
						raw->route_dependents [loop] = unpack_entity_safe_ptr ();
					}
				}
	
				// return keysite
	
				raw->return_keysite = unpack_entity_safe_ptr ();
	
				#if DEBUG_MODULE
	
				debug_log ("EN_COMMS: received set task pointers entity %s %d", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));
	
				#endif
	
				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SET_WAYPOINT:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en, entity *wp)
				//

				entity
					*en,
					*wp;
	
				en = unpack_entity_safe_ptr ();

				wp = unpack_entity_safe_ptr ();

				ASSERT (en);
	
				ASSERT (get_local_entity_type (en) == ENTITY_TYPE_GUIDE);

				ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

				#if DEBUG_MODULE
	
				debug_log ("EN_COMMS: received set waypoint");
	
				#endif
	
				set_guide_new_waypoint (en, wp);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_STRING:
			////////////////////////////////////////
			{
				entity
					*en;

				string_types
					type;

				char
					s[STRING_TYPE_MAX_LENGTH+1];

				en = unpack_entity_safe_ptr ();

				type = unpack_string_type ();

				unpack_string (en, type, s);

				set_client_server_entity_string (en, type, s);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received string %s for %s (%d)", s, get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SWITCH_LIST:
			////////////////////////////////////////
			{
				entity
					*en,
					*parent;

				list_types
					type1,
					type2;

				en = unpack_entity_safe_ptr ();

				type1 = unpack_list_type ();

				parent = unpack_entity_safe_ptr ();

				type2 = unpack_list_type ();

				delete_local_entity_from_parents_child_list (en, type1);

				if (parent)
				{

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: received switch list for %s (%d) list %s to list %s (parent %s (%d))",
								get_local_entity_type_name (en), get_local_entity_index (en), get_list_type_name (type1),
								get_list_type_name (type2), get_local_entity_type_name (parent), get_local_entity_index (en));

					#endif

					insert_local_entity_into_parents_child_list (en, type2, parent, NULL);
				}
				else
				{

					#if DEBUG_MODULE_MESSAGE_TEXT

					debug_log ("EN_COMMS: received switch list for %s (%d) list %s to no list",
								get_local_entity_type_name (en), get_local_entity_index (en), get_list_type_name (type1));

					#endif
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_SWITCH_PARENT:
			////////////////////////////////////////
			{
				entity
					*en,
					*parent;

				list_types
					type;

				en = unpack_entity_safe_ptr ();

				type = unpack_list_type ();

				parent = unpack_entity_safe_ptr ();

				set_client_server_entity_parent (en, type, parent);

				//
				// add radar_swept targets to map
				//
/*
				if ((type == LIST_TYPE_TARGET) || (type == LIST_TYPE_GUNSHIP_TARGET))
				{

					if (get_local_entity_int_value (en, INT_TYPE_SIDE) == get_global_gunship_side ())
					{

						set_planner_icon_update (parent, FALSE);
					}
				}
*/
				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received switch list %s parent for %s (%d)",
								get_list_type_name (type),
								get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_TASK_ASSIGN_REQUEST:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *en (pilot_entity), entity *task, entity *mobile)
				//

				entity
					*en,
					*mobile,
					*task;

				ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

				en = unpack_entity_safe_ptr ();

				ASSERT (get_local_entity_type (en) == ENTITY_TYPE_PILOT);

				task = unpack_entity_safe_ptr ();

				ASSERT (get_local_entity_type (task) == ENTITY_TYPE_TASK);

				mobile = unpack_entity_safe_ptr ();

//				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received assign task request %s for %s", get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_string (en, STRING_TYPE_PILOTS_NAME));

//				#endif

				ASSERT (!force_local_entity_create_stack_attributes);

				set_force_local_entity_create_stack_attributes (TRUE);

				respond_to_player_task_assign_request (en, task, mobile);

				set_force_local_entity_create_stack_attributes (FALSE);

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_TASK_ASSIGN_RESULT:
			////////////////////////////////////////
			{
				//
				// (entity_comms_messages message, entity *pilot, entity *task, entity *mobile)
				//

				entity
					*en,
					*task,
					*mobile;

				ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);

				en = unpack_entity_safe_ptr ();

				task = unpack_entity_safe_ptr ();

				mobile = unpack_entity_safe_ptr ();

				if (en == get_pilot_entity ())
				{
					if (task)
					{
						ASSERT (mobile);

						player_assigned_new_task (mobile, task);
					}
					else
					{
						notify_clear_current_selections (NULL, NULL);
					}
				}

//				#if DEBUG_MODULE_MESSAGE_TEXT
				
				if (task)
				{

					debug_log ("EN_COMMS: received assign task %s accepted for %s", get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_string (en, STRING_TYPE_PILOTS_NAME));
				}
				else
				{

					debug_log ("EN_COMMS: received assign task refused for %s", get_local_entity_string (en, STRING_TYPE_PILOTS_NAME));
				}

//				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_TASK_KILL:
			////////////////////////////////////////
			{
	
				entity
					*task_en,
					*victim,
					*aggressor;
	
				//
				// (entity_comms_messages message, entity *task, entity *victim, entity *aggressor)
				//
	
				ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);
	
				task_en = unpack_entity_safe_ptr ();
				victim = unpack_entity_safe_ptr ();
				aggressor = unpack_entity_safe_ptr ();
	
				add_kill_to_task (task_en, victim, aggressor);
	
				debug_log ("EN_COMMS: received task kill for %s (%d), victim %s (%d), aggressor %s (%d)",
								get_local_entity_string (task_en, STRING_TYPE_FULL_NAME), get_local_entity_index (task_en),
								get_local_entity_string (victim, STRING_TYPE_FULL_NAME), get_local_entity_index (victim),
								get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME), get_local_entity_index (aggressor));
	
				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_TASK_LOSS:
			////////////////////////////////////////
			{
	
				entity
					*task_en,
					*victim,
					*aggressor;
	
				//
				// (entity_comms_messages message, entity *task, entity *victim, entity *aggressor)
				//
	
				ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);
	
				task_en = unpack_entity_safe_ptr ();
				victim = unpack_entity_safe_ptr ();
				aggressor = unpack_entity_safe_ptr ();
	
				add_loss_to_task (task_en, victim, aggressor);
	
				debug_log ("EN_COMMS: received task loss for %s (%d), victim %s (%d), aggressor %s (%d)",
								get_local_entity_string (task_en, STRING_TYPE_FULL_NAME), get_local_entity_index (task_en),
								get_local_entity_string (victim, STRING_TYPE_FULL_NAME), get_local_entity_index (victim),
								get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME), get_local_entity_index (aggressor));
	
				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_UPDATE:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				// The local player always ignores echoed update data.
				//
				// This is handled in the unpack functions because the data must still be unpacked.

				unpack_client_server_entity_data (en);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received update for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_UPDATE_FOG_OF_WAR:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();
	
				#if DEBUG_MODULE_MESSAGE_TEXT
	
				debug_log ("EN_COMMS: received update fog of war");
	
				#endif
	
				update_sector_fog_of_war ();

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_UPDATE_SECTOR_SIDE:
			////////////////////////////////////////
			{
				entity
					*en;

				int
					in_use;

				en = unpack_entity_safe_ptr ();

				in_use = unpack_int_value (en, INT_TYPE_IN_USE);

				update_imap_sector_side (en, in_use);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received update sector side for %s (%d) - in_use", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en), in_use);

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_UPDATE_SECTOR_SIDE_COUNT:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();
	
				#if DEBUG_MODULE_MESSAGE_TEXT
	
				debug_log ("EN_COMMS: received update sector side count");
	
				#endif
	
				update_sector_side_count ();

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_VEC3D:
			////////////////////////////////////////
			{
				entity
					*en;

				vec3d_types
					type;

				vec3d
					v;

				en = unpack_entity_safe_ptr ();

				type = unpack_vec3d_type ();

				unpack_vec3d (en, type, &v);

				set_client_server_entity_vec3d (en, type, &v);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received vec3d for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_ZERO_DESIRED_VELOCITY:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				set_local_entity_float_value (en, FLOAT_TYPE_DESIRED_VELOCITY, 0.0);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received zero desired velocity for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			case ENTITY_COMMS_ZERO_VELOCITY:
			////////////////////////////////////////
			{
				entity
					*en;

				en = unpack_entity_safe_ptr ();

				set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, 0.0);

				#if DEBUG_MODULE_MESSAGE_TEXT

				debug_log ("EN_COMMS: received zero velocity for %s (%d)", get_local_entity_type_name (en), get_local_entity_index (en));

				#endif

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Received invalid entity comms message = %d", message);

				break;
			}
		}
	}

	set_comms_data_flow (COMMS_DATA_FLOW_TX);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_entity_comms_message (entity_comms_messages message)
{
	ASSERT ((message >= 0) && (message < NUM_ENTITY_COMMS_MESSAGES));
	ASSERT (!(message >> NUM_ENTITY_COMMS_MESSAGE_PACK_BITS));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (entity_comms_message_database[message].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_ENTITY_COMMS_MESSAGE, NULL, message);
	}

	#endif

	pack_unsigned_data (message, NUM_ENTITY_COMMS_MESSAGE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_comms_messages unpack_entity_comms_message (void)
{
	entity_comms_messages
		message;

	message = unpack_unsigned_data (NUM_ENTITY_COMMS_MESSAGE_PACK_BITS);

	ASSERT ((message >= 0) && (message < NUM_ENTITY_COMMS_MESSAGES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (entity_comms_message_database[message].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_ENTITY_COMMS_MESSAGE, NULL, message);
	}

	#endif

	return (message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
