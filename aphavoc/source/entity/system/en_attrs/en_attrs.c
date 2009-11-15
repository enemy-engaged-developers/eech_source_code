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

#define DEBUG_MODULE				0

#define DEBUG_MODULE_PACK_ONE	0

#define DEBUG_MODULE_PACK_ALL	(PACK_ENTIRE_SESSION || 0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_attribute_data
	entity_attribute_database[NUM_ENTITY_ATTRIBUTES] =
	{
		{
			"ENTITY_ATTR_END",							// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_ATTITUDE_ANGLES",			// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_CHAR_VALUE",					// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_CHILD_PRED",					// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_FLOAT_VALUE",					// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_INT_VALUE",					// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_PARENT",						// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_PTR_VALUE",					// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_STRING",						// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
		{
			"ENTITY_ATTR_VEC3D",							// name
			(DEBUG_MODULE_PACK_ALL || 0),				// debug_pack
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// mechanisim for unpacking strings (allows for one of each string type to be unpacked)
//

static char
	string_buffer[NUM_STRING_TYPES][STRING_TYPE_MAX_LENGTH + 1];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WARNING! CHARS AND SHORT INTS ARE PROMOTED TO INTS ON THE VARIABLE ARGUMENT LIST
//
//				FLOATS ARE PROMOTED TO DOUBLES ON THE VARIABLE ARGUMENT LIST
//
// NOTE: 	Entity attributes are set during entity creation. Only use "local" access functions.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_local_entity_attributes (entity *en, char *pargs)
{
	entity_attributes
		attr;

	ASSERT (en);

	ASSERT (pargs);

	while (TRUE)
	{
		attr = get_list_item (pargs, entity_attributes);

		switch (attr)
		{
			////////////////////////////////////////
			case entity_attr_end:
			////////////////////////////////////////
			{
				return;
			}
			////////////////////////////////////////
			case entity_attr_attitude_angles:
			////////////////////////////////////////
			{
				float
					heading,
					pitch,
					roll;

				heading = get_list_item (pargs, double);

				pitch = get_list_item (pargs, double);

				roll = get_list_item (pargs, double);

				set_local_entity_raw_attitude_angles (en, heading, pitch, roll);

				break;
			}
			////////////////////////////////////////
			case entity_attr_char_value:
			////////////////////////////////////////
			{
				char_types
					type;

				char
					value;

				type = get_list_item (pargs, char_types);

				value = get_list_item (pargs, int);

				set_local_entity_raw_char_value (en, type, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_child_pred:
			////////////////////////////////////////
			{
				list_types
					type;

				entity
					*child_pred;

				type = get_list_item (pargs, list_types);

				child_pred = get_list_item (pargs, entity *);

				set_local_entity_child_pred (en, type, child_pred);

				break;
			}
			////////////////////////////////////////
			case entity_attr_float_value:
			////////////////////////////////////////
			{
				float_types
					type;

				float
					value;

				type = get_list_item (pargs, float_types);

				value = get_list_item (pargs, double);

				set_local_entity_raw_float_value (en, type, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_int_value:
			////////////////////////////////////////
			{
				int_types
					type;

				int
					value;

				type = get_list_item (pargs, int_types);

				value = get_list_item (pargs, int);

				set_local_entity_raw_int_value (en, type, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_parent:
			////////////////////////////////////////
			{
				list_types
					type;

				entity
					*parent;

				type = get_list_item (pargs, list_types);

				parent = get_list_item (pargs, entity *);

				set_local_entity_parent (en, type, parent);

				break;
			}
			////////////////////////////////////////
			case entity_attr_ptr_value:
			////////////////////////////////////////
			{
				ptr_types
					type;

				void
					*ptr;

				type = get_list_item (pargs, ptr_types);

				ptr = get_list_item (pargs, void *);

				set_local_entity_ptr_value (en, type, ptr);

				break;
			}
			////////////////////////////////////////
			case entity_attr_string:
			////////////////////////////////////////
			{
				string_types
					type;

				const char
					*s;

				type = get_list_item (pargs, string_types);

				s = get_list_item (pargs, const char *);

				set_local_entity_raw_string (en, type, s);

				break;
			}
			////////////////////////////////////////
			case entity_attr_vec3d:
			////////////////////////////////////////
			{
				vec3d_types
					type;

				vec3d
					v;

				type = get_list_item (pargs, vec3d_types);

				v.x = get_list_item (pargs, double);

				v.y = get_list_item (pargs, double);

				v.z = get_list_item (pargs, double);

				set_local_entity_raw_vec3d (en, type, &v);

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid entity attribute = %d", attr);

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_entity_attributes (const char *buffer)
{
	entity_attributes
		attr;

	ASSERT (buffer);

	while (TRUE)
	{
		attr = get_list_item (buffer, entity_attributes);

		pack_entity_attribute (attr);

		switch (attr)
		{
			////////////////////////////////////////
			case entity_attr_end:
			////////////////////////////////////////
			{
				return;
			}
			////////////////////////////////////////
			case entity_attr_attitude_angles:
			////////////////////////////////////////
			{
				float
					heading,
					pitch,
					roll;

				heading = get_list_item (buffer, double);

				pitch = get_list_item (buffer, double);

				roll = get_list_item (buffer, double);

				pack_attitude_angles (NULL, heading, pitch, roll);

				break;
			}
			////////////////////////////////////////
			case entity_attr_char_value:
			////////////////////////////////////////
			{
				char_types
					type;

				char
					value;

				type = get_list_item (buffer, char_types);

				pack_char_type (type);

				value = get_list_item (buffer, int);

				pack_char_value (NULL, type, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_child_pred:
			////////////////////////////////////////
			{
				list_types
					type;

				entity
					*child_pred;

				type = get_list_item (buffer, list_types);

				pack_list_type (type);

				child_pred = get_list_item (buffer, entity *);

				pack_entity_safe_ptr (child_pred);

				break;
			}
			////////////////////////////////////////
			case entity_attr_float_value:
			////////////////////////////////////////
			{
				float_types
					type;

				float
					value;

				type = get_list_item (buffer, float_types);

				pack_float_type (type);

				value = get_list_item (buffer, double);

				pack_float_value (NULL, type, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_int_value:
			////////////////////////////////////////
			{
				int_types
					type;

				int
					value;

				type = get_list_item (buffer, int_types);

				pack_int_type (type);

				value = get_list_item (buffer, int);

				pack_int_value (NULL, type, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_parent:
			////////////////////////////////////////
			{
				list_types
					type;

				entity
					*parent;

				type = get_list_item (buffer, list_types);

				pack_list_type (type);

				parent = get_list_item (buffer, entity *);

				pack_entity_safe_ptr (parent);

				break;
			}
			////////////////////////////////////////
			case entity_attr_ptr_value:
			////////////////////////////////////////
			{
				debug_fatal ("Cannot pack entity attribute = %s", get_entity_attribute_name (attr));

				break;
			}
			////////////////////////////////////////
			case entity_attr_string:
			////////////////////////////////////////
			{
				string_types
					type;

				const char
					*s;

				type = get_list_item (buffer, string_types);

				pack_string_type (type);

				s = get_list_item (buffer, const char *);

				//
				// pack the string contents not the string pointer
				//

				pack_string (NULL, type, s);

				break;
			}
			////////////////////////////////////////
			case entity_attr_vec3d:
			////////////////////////////////////////
			{
				vec3d_types
					type;

				vec3d
					v;

				type = get_list_item (buffer, vec3d_types);

				pack_vec3d_type (type);

				v.x = get_list_item (buffer, double);

				v.y = get_list_item (buffer, double);

				v.z = get_list_item (buffer, double);

				pack_vec3d (NULL, type, &v);

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid entity attribute = %d", attr);

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int unpack_entity_attributes (char *buffer)
{
	int
		num_bytes;

	entity_attributes
		attr;

	ASSERT (buffer);

	num_bytes = 0;

	while (TRUE)
	{
		attr = unpack_entity_attribute ();

		num_bytes += set_list_item (buffer, entity_attributes, attr);

		switch (attr)
		{
			////////////////////////////////////////
			case entity_attr_end:
			////////////////////////////////////////
			{
				return (num_bytes);
			}
			////////////////////////////////////////
			case entity_attr_attitude_angles:
			////////////////////////////////////////
			{
				float
					heading,
					pitch,
					roll;

				unpack_attitude_angles (NULL, &heading, &pitch, &roll);

				num_bytes += set_list_item (buffer, double, heading);

				num_bytes += set_list_item (buffer, double, pitch);

				num_bytes += set_list_item (buffer, double, roll);

				break;
			}
			////////////////////////////////////////
			case entity_attr_char_value:
			////////////////////////////////////////
			{
				char_types
					type;

				char
					value;

				type = unpack_char_type ();

				num_bytes += set_list_item (buffer, char_types, type);

				value = unpack_char_value (NULL, type);

				num_bytes += set_list_item (buffer, int, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_child_pred:
			////////////////////////////////////////
			{
				list_types
					type;

				entity
					*child_pred;

				type = unpack_list_type ();

				num_bytes += set_list_item (buffer, list_types, type);

				child_pred = unpack_entity_safe_ptr ();

				num_bytes += set_list_item (buffer, entity *, child_pred);

				break;
			}
			////////////////////////////////////////
			case entity_attr_float_value:
			////////////////////////////////////////
			{
				float_types
					type;

				float
					value;

				type = unpack_float_type ();

				num_bytes += set_list_item (buffer, float_types, type);

				value = unpack_float_value (NULL, type);

				num_bytes += set_list_item (buffer, double, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_int_value:
			////////////////////////////////////////
			{
				int_types
					type;

				int
					value;

				type = unpack_int_type ();

				num_bytes += set_list_item (buffer, int_types, type);

				value = unpack_int_value (NULL, type);

				num_bytes += set_list_item (buffer, int, value);

				break;
			}
			////////////////////////////////////////
			case entity_attr_parent:
			////////////////////////////////////////
			{
				list_types
					type;

				entity
					*parent;

				type = unpack_list_type ();

				num_bytes += set_list_item (buffer, list_types, type);

				parent = unpack_entity_safe_ptr ();

				num_bytes += set_list_item (buffer, entity *, parent);

				break;
			}
			////////////////////////////////////////
			case entity_attr_ptr_value:
			////////////////////////////////////////
			{
				debug_fatal ("Cannot unpack entity attribute = %s", get_entity_attribute_name (attr));

				break;
			}
			////////////////////////////////////////
			case entity_attr_string:
			////////////////////////////////////////
			{
				string_types
					type;

				type = unpack_string_type ();

				num_bytes += set_list_item (buffer, string_types, type);

				//
				// unpack the string into the string buffer and put the address of this buffer into the attributes buffer
				//

				unpack_string (NULL, type, string_buffer[type]);

				num_bytes += set_list_item (buffer, char *, string_buffer[type]);

				break;
			}
			////////////////////////////////////////
			case entity_attr_vec3d:
			////////////////////////////////////////
			{
				vec3d_types
					type;

				vec3d
					v;

				type = unpack_vec3d_type ();

				num_bytes += set_list_item (buffer, vec3d_types, type);

				unpack_vec3d (NULL, type, &v);

				num_bytes += set_list_item (buffer, double, v.x);

				num_bytes += set_list_item (buffer, double, v.y);

				num_bytes += set_list_item (buffer, double, v.z);

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid entity attribute = %d", attr);

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_entity_attribute (entity_attributes attr)
{
	ASSERT ((attr >= 0) && (attr < NUM_ENTITY_ATTRIBUTES));
	ASSERT (!(attr >> NUM_ENTITY_ATTRIBUTE_PACK_BITS));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (entity_attribute_database[attr].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_ENTITY_ATTRIBUTE, NULL, attr);
	}

	#endif

	pack_unsigned_data (attr, NUM_ENTITY_ATTRIBUTE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_attributes unpack_entity_attribute (void)
{
	entity_attributes
		attr;

	attr = (entity_attributes) unpack_unsigned_data (NUM_ENTITY_ATTRIBUTE_PACK_BITS);

	ASSERT ((attr >= 0) && (attr < NUM_ENTITY_ATTRIBUTES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (entity_attribute_database[attr].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_ENTITY_ATTRIBUTE, NULL, attr);
	}

	#endif

	return (attr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
