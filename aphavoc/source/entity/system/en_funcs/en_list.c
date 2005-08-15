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

#define DEBUG_MODULE						0

#define DEBUG_MODULE_VALIDATE_LISTS	1

#define DEBUG_MODULE_PACK_ONE			0

#define DEBUG_MODULE_PACK_ALL	(PACK_ENTIRE_SESSION || 0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

list_type_data
	list_type_database[NUM_LIST_TYPES] =
	{
		{
			"LIST_TYPE_INVALID",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_AIRCREW",                               // name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_AIR_REGISTRY",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_ASSIGNED_TASK",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_BUILDING_GROUP",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_CAMPAIGN_OBJECTIVE",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_CARGO",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_CITY_BUILDING",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_COMPLETED_TASK",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_CURRENT_WAYPOINT",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_DESIGNATED_TARGET",								// name // Jabberwock 031107 Designated targets
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_DIVISION",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_DIVISION_HEADQUARTERS",						// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_FOLLOWER",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_FORCE",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_GROUND_REGISTRY",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_GUIDE",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_GUIDE_STACK",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_GUNSHIP_TARGET",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_HIERARCHY",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_INDEPENDENT_GROUP",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_KEYSITE_FORCE",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_KEYSITE_GROUP",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_LANDING_SITE",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_LAUNCHED_WEAPON",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_MEMBER",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_MOVEMENT_DEPENDENT",							// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_PADLOCK",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_PILOT",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_PILOT_LOCK",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_PLAYER_TASK",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_REGEN",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_SEA_REGISTRY",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_SECTOR",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_SECTOR_TASK",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_SEGMENT",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_SPECIAL_EFFECT",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_TAKEOFF_QUEUE",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_TARGET",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_TASK_DEPENDENT",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_UNASSIGNED_TASK",								// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_UPDATE",											// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_VIEW",												// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_VIEW_WEAPON",									// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
		{
			"LIST_TYPE_WAYPOINT",										// name
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*overload_invalid_list_type_message = "Overloaded entity function invoked with invalid list type",
	*debug_fatal_invalid_list_type_message = "Invalid list type (entity type = %s, index = %d, list type = %s, file = %s, line = %d)";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_set_local_entity_first_child[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type, entity *first_child);

entity *(*fn_get_local_entity_first_child[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type);

void (*fn_set_local_entity_parent[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type, entity *parent);

entity *(*fn_get_local_entity_parent[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type);

void (*fn_set_local_entity_child_succ[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type, entity *child_succ);

entity *(*fn_get_local_entity_child_succ[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type);

void (*fn_set_local_entity_child_pred[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type, entity *child_pred);

entity *(*fn_get_local_entity_child_pred[NUM_ENTITY_TYPES][NUM_LIST_TYPES]) (entity *en, list_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_first_child (entity *en, list_types type, entity *first_child)
{
	debug_fatal_invalid_list_type (en, type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *default_get_entity_first_child (entity *en, list_types type)
{
	// JB 030313 Fly any aircraft (test code)
	debug_fatal_invalid_list_type (en, type);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_parent (entity *en, list_types type, entity *parent)
{
	debug_fatal_invalid_list_type (en, type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *default_get_entity_parent (entity *en, list_types type)
{
	debug_fatal_invalid_list_type (en, type);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_child_succ (entity *en, list_types type, entity *child_succ)
{
	debug_fatal_invalid_list_type (en, type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *default_get_entity_child_succ (entity *en, list_types type)
{
	debug_fatal_invalid_list_type (en, type);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_child_pred (entity *en, list_types type, entity *child_pred)
{
	debug_fatal_invalid_list_type (en, type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *default_get_entity_child_pred (entity *en, list_types type)
{
	debug_fatal_invalid_list_type (en, type);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_list_default_functions (void)
{
	int
		i,
		j;

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{
		for (j = 0; j < NUM_LIST_TYPES; j++)
		{
			fn_set_local_entity_first_child[i][j]	= default_set_entity_first_child;

			fn_get_local_entity_first_child[i][j]	= default_get_entity_first_child;

			fn_set_local_entity_parent[i][j]			= default_set_entity_parent;

			fn_get_local_entity_parent[i][j]			= default_get_entity_parent;

			fn_set_local_entity_child_succ[i][j]	= default_set_entity_child_succ;

			fn_get_local_entity_child_succ[i][j]	= default_get_entity_child_succ;

			fn_set_local_entity_child_pred[i][j]	= default_set_entity_child_pred;

			fn_get_local_entity_child_pred[i][j]	= default_get_entity_child_pred;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// NOTE: If pred == NULL then the entity is inserted at the start of the list.
//

void insert_local_entity_into_parents_child_list (entity *en, list_types type, entity *parent, entity *pred)
{
	entity
		*succ;

	ASSERT (en);

	ASSERT (parent);

	ASSERT (pred != parent);

	#ifdef DEBUG

	#if DEBUG_MODULE_VALIDATE_LISTS
	{
		entity
			*item,
			*current_parent;

		current_parent = get_local_entity_parent (en, type);

		// current_parent should ideally always be NULL, but isn't always do to the way ENTITY_ATTR_PARENT works when creating entities

		if (current_parent)
		{
			item = get_local_entity_first_child (current_parent, type);
	
			while (item)
			{
				if (item == en)
				{
					debug_fatal ("Entity already in list (entity type = %s, list type = %s)", get_entity_type_name (get_local_entity_type (en)), get_list_type_name (type));
				}
	
				item = get_local_entity_child_succ (item, type);
			}
		}
	}
	#endif

	#endif

	if (pred)
	{
		succ = get_local_entity_child_succ (pred, type);
	}
	else
	{
		succ = get_local_entity_first_child (parent, type);
	}

	set_local_entity_child_succ (en, type, succ);

	set_local_entity_child_pred (en, type, pred);

	set_local_entity_parent (en, type, parent);

	if (succ)
	{
		set_local_entity_child_pred (succ, type, en);
	}

	if (pred)
	{
		set_local_entity_child_succ (pred, type, en);
	}
	else
	{
		set_local_entity_first_child (parent, type, en);
	}

	notify_local_entity (ENTITY_MESSAGE_LINK_CHILD, parent, en, type);

	notify_local_entity (ENTITY_MESSAGE_LINK_PARENT, en, parent, type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_local_entity_from_parents_child_list (entity *en, list_types type)
{
	entity
		*parent,
		*succ,
		*pred;

	ASSERT (en);

	parent = get_local_entity_parent (en, type);

	if (parent)
	{
		notify_local_entity (ENTITY_MESSAGE_UNLINK_CHILD, parent, en, type);

		notify_local_entity (ENTITY_MESSAGE_UNLINK_PARENT, en, parent, type);

		succ = get_local_entity_child_succ (en, type);

		pred = get_local_entity_child_pred (en, type);

		if (pred)
		{
			set_local_entity_child_succ (pred, type, succ);
		}
		else
		{
			set_local_entity_first_child (parent, type, succ);
		}

		if (succ)
		{
			set_local_entity_child_pred (succ, type, pred);
		}

		set_local_entity_parent (en, type, NULL);

		set_local_entity_child_succ (en, type, NULL);

		set_local_entity_child_pred (en, type, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unlink_local_entity_children (entity *en, list_types list)
{
	entity
		*child;

	ASSERT (en);

	while (child = get_local_entity_first_child (en, list))
	{
		delete_local_entity_from_parents_child_list (child, list);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_child_succ_circular (entity *en, list_types type)
{
	entity
		*succ,
		*parent;

	ASSERT (en);

	succ = get_local_entity_child_succ (en, type);

	if (!succ)
	{
		parent = get_local_entity_parent (en, type);

		ASSERT (parent);

		succ = get_local_entity_first_child (parent, type);
	}

	return (succ);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_child_pred_circular (entity *en, list_types type)
{
	entity
		*pred,
		*succ,
		*parent;

	ASSERT (en);

	pred = get_local_entity_child_pred (en, type);

	if (!pred)
	{
		parent = get_local_entity_parent (en, type);

		ASSERT (parent);

		pred = get_local_entity_first_child (parent, type);

		while (succ = get_local_entity_child_succ (pred, type))
		{
			pred = succ;
		}
	}

	return (pred);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_list_root (entity *en, list_types type, list_root *root)
{
	ASSERT ((type >= 0) && (type < NUM_LIST_TYPES));

	ASSERT (root);

	pack_entity_safe_ptr (root->first_child);

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (list_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_LIST_TYPE_FIRST_CHILD, en, type, root->first_child);
	}

	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_list_root (entity *en, list_types type, list_root *root)
{
	ASSERT ((type >= 0) && (type < NUM_LIST_TYPES));

	ASSERT (root);

	root->first_child = unpack_entity_safe_ptr ();

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (list_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_LIST_TYPE_FIRST_CHILD, en, type, root->first_child);
	}

	#endif

	//
	// All list must be validated and repaired.
	//

	register_entity_list_root_for_post_unpack_validation (en, type);

	//
	//
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_list_link (entity *en, list_types type, list_link *link)
{
	ASSERT ((type >= 0) && (type < NUM_LIST_TYPES));

	ASSERT (link);

	pack_entity_safe_ptr (link->parent);

	pack_entity_safe_ptr (link->child_succ);

	pack_entity_safe_ptr (link->child_pred);

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (list_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_LIST_TYPE_PARENT, en, type, link->parent);

		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_LIST_TYPE_CHILD_SUCC, en, type, link->child_succ);

		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_LIST_TYPE_CHILD_PRED, en, type, link->child_pred);
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_list_link (entity *en, list_types type, list_link *link)
{
	ASSERT ((type >= 0) && (type < NUM_LIST_TYPES));

	ASSERT (link);

	link->parent = unpack_entity_safe_ptr ();

	link->child_succ = unpack_entity_safe_ptr ();

	link->child_pred = unpack_entity_safe_ptr ();

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (list_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_LIST_TYPE_PARENT, en, type, link->parent);

		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_LIST_TYPE_CHILD_SUCC, en, type, link->child_succ);

		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_LIST_TYPE_CHILD_PRED, en, type, link->child_pred);
	}

	#endif

	//
	// All list must be validated and repaired.
	//

	if ((link->parent) || (link->child_succ) || (link->child_pred))
	{

		register_entity_list_link_for_post_unpack_validation (en, type);
	}

	//
	//
	//
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_list_type (list_types type)
{
	ASSERT ((type >= 0) && (type < NUM_LIST_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (list_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_LIST_TYPE, NULL, type);
	}

	#endif

	pack_unsigned_data (type, NUM_LIST_TYPE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

list_types unpack_list_type (void)
{
	list_types
		type;

	type = unpack_unsigned_data (NUM_LIST_TYPE_PACK_BITS);

	ASSERT ((type >= 0) && (type < NUM_LIST_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (list_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_LIST_TYPE, NULL, type);
	}

	#endif

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_client_server_entity_parent (entity *en, list_types type, entity *parent)
{
	ASSERT (en);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		////////////////////////////////////////
		//
		// SERVER/TX and SERVER/RX
		//
		////////////////////////////////////////

		delete_local_entity_from_parents_child_list (en, type);

		if (parent)
		{
			insert_local_entity_into_parents_child_list (en, type, parent, NULL);
		}

		transmit_entity_comms_message (ENTITY_COMMS_SWITCH_PARENT, en, type, parent);
	}
	else
	{
		if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
		{
			////////////////////////////////////////
			//
			// CLIENT/TX
			//
			////////////////////////////////////////

			transmit_entity_comms_message (ENTITY_COMMS_SWITCH_PARENT, en, type, parent);
		}
		else
		{
			////////////////////////////////////////
			//
			// CLIENT/RX
			//
			////////////////////////////////////////

			delete_local_entity_from_parents_child_list (en, type);

			if (parent)
			{
				insert_local_entity_into_parents_child_list (en, type, parent, NULL);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_list_size (entity *parent, list_types type)
{

	entity
		*child;

	int
		count;

	count = 0;

	child = get_local_entity_first_child (parent, type);

	while (child)
	{

		count ++;

		child = get_local_entity_child_succ (child, type);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
