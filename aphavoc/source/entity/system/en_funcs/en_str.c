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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE				0

#define DEBUG_MODULE_PACK_ONE	0

#define DEBUG_MODULE_PACK_ALL	(PACK_ENTIRE_SESSION || 0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string_type_data
	string_type_database[NUM_STRING_TYPES] =
	{
		{
			"STRING_TYPE_DIVISION_NAME",						// name
			STRING_TYPE_DIVISION_NAME_MAX_LENGTH,			// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"UNKNOWN",												// default_value
		},
		{
			"STRING_TYPE_EASY_DISPLAY_NAME",					// name
			STRING_TYPE_EASY_DISPLAY_NAME_MAX_LENGTH,		// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"UNKNOWN",												// default_value
		},
		{
			"STRING_TYPE_FORCE_NAME",							// name
			STRING_TYPE_FORCE_NAME_MAX_LENGTH,				// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"Unknown",												// default_value
		},
		{
			"STRING_TYPE_FULL_NAME",							// name
			STRING_TYPE_FULL_NAME_MAX_LENGTH,				// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"Unknown",												// default_value
		},
		{
			"STRING_TYPE_GROUP_CALLSIGN",						// name
			STRING_TYPE_FULL_NAME_MAX_LENGTH,				// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"Unknown",												// default_value
		},
		{
			"STRING_TYPE_GROUP_SHORT_NAME",					// name
			STRING_TYPE_FULL_NAME_MAX_LENGTH,				// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"Unknown",												// default_value
		},
		{
			"STRING_TYPE_HUD_NAME",								// name
			STRING_TYPE_HUD_NAME_MAX_LENGTH,					// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"Unknown", 												// default_value
		},
		{
			"STRING_TYPE_KEYSITE_NAME",						// name
			STRING_TYPE_KEYSITE_NAME_MAX_LENGTH,			// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			NULL,														// default_value
		},
		{
			"STRING_TYPE_LONG_DISPLAY_NAME",			  		// name
			STRING_TYPE_LONG_DISPLAY_NAME_MAX_LENGTH,		// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"UNKNOWN",	 											// default_value
		},
		{
			"STRING_TYPE_PILOT_MESSAGE",						// name
			STRING_TYPE_MESSAGE_LENGTH,						// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			NULL,														// default_value
		},
		{
			"STRING_TYPE_PILOTS_NAME",							// name
			STRING_TYPE_PLAYERS_NAME_MAX_LENGTH,			// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			NULL,														// default_value
		},
		{
			"STRING_TYPE_PLAYERS_NAME",						// name
			STRING_TYPE_PLAYERS_NAME_MAX_LENGTH,			// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"Anonymous",											// default_value
		},
		{
			"STRING_TYPE_SHORT_DISPLAY_NAME",			  	// name
			STRING_TYPE_SHORT_DISPLAY_NAME_MAX_LENGTH,	// max_length
			(DEBUG_MODULE_PACK_ALL || 0),						// debug_pack
			"UNKNOWN",	 											// default_value
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*overload_invalid_string_type_message = "Overloaded entity function invoked with invalid string type",
	*debug_fatal_invalid_string_type_message = "Invalid string type (entity type = %s, index = %d, string type = %s, file = %s, line = %d)";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_set_local_entity_raw_string[NUM_ENTITY_TYPES][NUM_STRING_TYPES]) (entity *en, string_types type, const char *s);

void (*fn_set_local_entity_string[NUM_ENTITY_TYPES][NUM_STRING_TYPES]) (entity *en, string_types type, const char *s);

void (*fn_set_client_server_entity_string[NUM_ENTITY_TYPES][NUM_STRING_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en, string_types type, const char *s);

const char *(*fn_get_local_entity_string[NUM_ENTITY_TYPES][NUM_STRING_TYPES]) (entity *en, string_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_string (entity *en, string_types type, const char *s)
{
	ASSERT (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char *default_get_entity_string (entity *en, string_types type)
{
	char
		*s;

	switch (type)
	{
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			s = string_type_database[type].default_value;

			break;
		}
	}

	return (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_string_default_functions (void)
{
	int
		i,
		j;

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{
		for (j = 0; j < NUM_STRING_TYPES; j++)
		{
			fn_set_local_entity_raw_string[i][j]									= default_set_entity_string;

			fn_set_local_entity_string[i][j]									  		= default_set_entity_string;

			fn_set_client_server_entity_string[i][j][COMMS_MODEL_SERVER]	= default_set_entity_string;

			fn_set_client_server_entity_string[i][j][COMMS_MODEL_CLIENT]	= default_set_entity_string;

			fn_get_local_entity_string[i][j]									 		= default_get_entity_string;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_string (entity *en, string_types type, const char *s)
{
	ASSERT ((type >= 0) && (type < NUM_STRING_TYPES));

	ASSERT (s);

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (string_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_STRING, en, type, s);
	}

	#endif

	ASSERT (strlen (s) <= get_string_type_max_length (type));

	while (*s)
	{
		pack_unsigned_data ((unsigned char)*s++, 8);//DEBUG//
	}

	pack_unsigned_data (0, 8);//DEBUG//
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_string (entity *en, string_types type, char *s)
{
	char
		buffer[STRING_TYPE_MAX_LENGTH+1],
		*p;

	ASSERT ((type >= 0) && (type < NUM_STRING_TYPES));

	ASSERT (s);

	p = buffer;

	do
	{
	 	*p = unpack_unsigned_data (8);//DEBUG//
	}
	while (*p++);

	ASSERT (strlen (buffer) <= get_string_type_max_length (type));

	strcpy (s, buffer);

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (string_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_STRING, en, type, s);
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_string_type (string_types type)
{
	ASSERT ((type >= 0) && (type < NUM_STRING_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (string_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_STRING_TYPE, NULL, type);
	}

	#endif

	ASSERT(!(type >> NUM_STRING_TYPE_PACK_BITS));

	pack_unsigned_data (type, NUM_STRING_TYPE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string_types unpack_string_type (void)
{
	string_types
		type;

	type = (string_types) unpack_unsigned_data (NUM_STRING_TYPE_PACK_BITS);

	ASSERT ((type >= 0) && (type < NUM_STRING_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (string_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_STRING_TYPE, NULL, type);
	}

	#endif

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
