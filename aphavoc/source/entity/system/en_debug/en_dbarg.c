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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	debug_log_entity_args_enabled = TRUE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	*debug_log_comms_prefix[NUM_COMMS_MODEL_TYPES][NUM_COMMS_DATA_FLOW_TYPES] =
	{
		{"SERVER/TX/", "SERVER/RX/"},
		{"CLIENT/TX/", "CLIENT/RX/"}
	};

static char
	*debug_log_mode_prefix[NUM_ENTITY_DEBUG_MODES] =
	{
		"LOCAL : ",
		"REMOTE: ",
		"PACK  : ",
		"UNPACK: "
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void enable_debug_log_entity_args (void)
{
	debug_log_entity_args_enabled = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void disable_debug_log_entity_args (void)
{
	debug_log_entity_args_enabled = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void debug_log_text (entity_debug_modes mode, entity *en, char *format, ...)
{
	va_list
		pargs;

	char
		s1[400],
		s2[400];
	const char
		*name;

	//
	// prefix
	//

	strcpy (s1, debug_log_comms_prefix[get_comms_model ()][get_comms_data_flow ()]);

	strcat (s1, debug_log_mode_prefix[mode]);

	//
	// entity type and index
	//

	if (en)
	{
		name = get_local_entity_type_name (en);
	}
	else
	{
		name = get_entity_type_name (ENTITY_TYPE_UNKNOWN);
	}

	sprintf (s2, "%-25.25s (index = %5d): ", name, get_local_entity_safe_index (en));

	strcat (s1, s2);

	//
	// args
	//

	va_start (pargs, format);

	vsprintf (s2, format, pargs);

	va_end (pargs);

	strcat (s1, s2);

	debug_log (s1);
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

void debug_log_entity_args (entity_debug_modes mode, entity_debug_args arg, entity *en, ...)
{
	va_list
		pargs;

	////////////////////////////////////////
	//
	// trap remote args in single player game
	//
	////////////////////////////////////////

	if (!debug_log_entity_args_enabled)
	{
		return;
	}

	if (mode == ENTITY_DEBUG_REMOTE)
	{
		if (direct_play_get_comms_mode () == DIRECT_PLAY_COMMS_MODE_NONE)
		{
			return;
		}
	}

	////////////////////////////////////////
	//
	// sort debug log text
	//
	////////////////////////////////////////

	va_start (pargs, en);

	switch (arg)
	{
		////////////////////////////////////////
		case ENTITY_DEBUG_ATTITUDE_ANGLES:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, float heading, float pitch, float roll)
			//

			float
				heading,
				pitch,
				roll;

			heading = va_arg (pargs, double);

			pitch = va_arg (pargs, double);

			roll = va_arg (pargs, double);

			debug_log_text (mode, en, "attitude angles (h = %.3f, p = %.3f, r = %.3f)", deg (heading), deg (pitch), deg (roll));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_ATTITUDE_MATRIX:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, matrix3x3 attitude)
			//

			matrix3x3
				*attitude;

			float
				heading,
				pitch,
				roll;

			attitude = va_arg (pargs, matrix3x3 *);

			ASSERT (attitude);

			heading = get_heading_from_attitude_matrix (*attitude);

			pitch = get_pitch_from_attitude_matrix (*attitude);

			roll = get_roll_from_attitude_matrix (*attitude);

			debug_log_text (mode, en, "attitude matrix (h = %.3f, p = %.3f, r = %.3f)", deg (heading), deg (pitch), deg (roll));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_CHAR_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, char_types type)
			//

			char_types
				type;

			type = va_arg (pargs, char_types);

			debug_log_text (mode, NULL, "char type = %s", get_char_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_CHAR_VALUE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, char_types type, char value)
			//

			char_types
				type;

			char
				value;

			type = va_arg (pargs, char_types);

			value = va_arg (pargs, int);

			debug_log_text (mode, en, "%s = %c", get_char_type_name (type), value);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_CREATE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_types type, int index)
			//

			entity_types
				type;

			int
				index;

			type = va_arg (pargs, entity_types);

			index = va_arg (pargs, int);

			debug_log_text (mode, NULL, "create %s (index = %d): ", get_entity_type_name (type), index);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_DESTROY:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en)
			//

			debug_log_text (mode, en, "destroy");

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_DESTROY_FAMILY:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en)
			//

			debug_log_text (mode, en, "destroy family");

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_ENTITY_ATTRIBUTE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_attributes attr)
			//

			entity_attributes
				attr;

			attr = va_arg (pargs, entity_attributes);

			debug_log_text (mode, NULL, "entity attribute = %s", get_entity_attribute_name (attr));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_ENTITY_COMMS_MESSAGE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_comms_messages message)
			//

			entity_comms_messages
				message;

			message = va_arg (pargs, entity_comms_messages);

			debug_log_text (mode, NULL, "entity comms message = %s", get_entity_comms_message_name (message));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_ENTITY_INDEX:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, int index)
			//

			int
				index;

			index = va_arg (pargs, int);

			debug_log_text (mode, en, "entity index = %d", index);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_ENTITY_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_types type)
			//

			entity_types
				type;

			type = va_arg (pargs, entity_types);

			debug_log_text (mode, en, "entity type = %s", get_entity_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_FLOAT_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, float_types type)
			//

			float_types
				type;

			type = va_arg (pargs, float_types);

			debug_log_text (mode, NULL, "float type = %s", get_float_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_FLOAT_VALUE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, float_types type, float value)
			//

			float_types
				type;

			float
				value;

			type = va_arg (pargs, float_types);

			value = va_arg (pargs, double);

			debug_log_text (mode, en, "%s = %.3f", get_float_type_name (type), value);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_INT_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, int_types type)
			//

			int_types
				type;

			type = va_arg (pargs, int_types);

			debug_log_text (mode, NULL, "int type = %s", get_int_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_INT_VALUE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, int_types type, int value)
			//

			int_types
				type;

			int
				value;

			type = va_arg (pargs, int_types);

			value = va_arg (pargs, int);

			debug_log_text (mode, en, "%s = %d", get_int_type_name (type), value);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_KILL:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en)
			//

			debug_log_text (mode, en, "kill");

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_LIST_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type)
			//

			list_types
				type;

			type = va_arg (pargs, list_types);

			debug_log_text (mode, NULL, "list type = %s", get_list_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_LIST_TYPE_CHILD_PRED:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *child_pred)
			//

			list_types
				type;

			entity
				*child_pred;

			int
				index;

			type = va_arg (pargs, list_types);

			child_pred = va_arg (pargs, entity *);

			index = get_local_entity_safe_index (child_pred);

			debug_log_text (mode, en, "%s child pred index = %d", get_list_type_name (type), index);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_LIST_TYPE_CHILD_SUCC:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *child_succ)
			//

			list_types
				type;

			entity
				*child_succ;

			int
				index;

			type = va_arg (pargs, list_types);

			child_succ = va_arg (pargs, entity *);

			index = get_local_entity_safe_index (child_succ);

			debug_log_text (mode, en, "%s child succ index = %d", get_list_type_name (type), index);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_LIST_TYPE_FIRST_CHILD:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *first_child)
			//

			list_types
				type;

			entity
				*first_child;

			int
				index;

			type = va_arg (pargs, list_types);

			first_child = va_arg (pargs, entity *);

			index = get_local_entity_safe_index (first_child);

			debug_log_text (mode, en, "%s first child index = %d", get_list_type_name (type), index);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_LIST_TYPE_PARENT:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *parent)
			//

			list_types
				type;

			entity
				*parent;

			int
				index;

			type = va_arg (pargs, list_types);

			parent = va_arg (pargs, entity *);

			index = get_local_entity_safe_index (parent);

			debug_log_text (mode, en, "%s parent index = %d", get_list_type_name (type), index);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_PTR_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, ptr_types type)
			//

			ptr_types
				type;

			type = va_arg (pargs, ptr_types);

			debug_log_text (mode, NULL, "ptr type = %s", get_ptr_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_PTR_VALUE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, ptr_types type, void *ptr)
			//

			ptr_types
				type;

			void
				*ptr;

			type = va_arg (pargs, ptr_types);

			ptr = va_arg (pargs, void *);

			debug_log_text (mode, en, "%s = 0x%x", get_ptr_type_name (type), ptr);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_STRING_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, string_types type)
			//

			string_types
				type;

			type = va_arg (pargs, string_types);

			debug_log_text (mode, NULL, "string type = %s", get_string_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_STRING:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, string_types type, char *s)
			//

			string_types
				type;

			char
				*s;

			type = va_arg (pargs, string_types);

			s = va_arg (pargs, char *);

			ASSERT (s);

			debug_log_text (mode, en, "%s = %s", get_string_type_name (type), s);

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_VEC3D_TYPE:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, vec3d_types type)
			//

			vec3d_types
				type;

			type = va_arg (pargs, vec3d_types);

			debug_log_text (mode, NULL, "vec3d type = %s", get_vec3d_type_name (type));

			break;
		}
		////////////////////////////////////////
		case ENTITY_DEBUG_VEC3D:
		////////////////////////////////////////
		{
			//
			// (entity_debug_modes mode, entity_debug_args arg, entity *en, vec3d_types type, vec3d *v)
			//

			vec3d_types
				type;

			vec3d
				*v;

			type = va_arg (pargs, vec3d_types);

			v = va_arg (pargs, vec3d *);

			ASSERT (v);

			if (type == VEC3D_TYPE_POSITION)
			{
				int
					x_sec,
					z_sec;

				get_x_sector (x_sec, v->x);
				get_z_sector (z_sec, v->z);

				debug_log_text (mode, en, "%s = (x = %.3f, y = %.3f, z = %.3f, x sec = %d, z sec = %d)", get_vec3d_type_name (type), v->x, v->y, v->z, x_sec, z_sec);
			}
			else
			{
				debug_log_text (mode, en, "%s = (x = %.3f, y = %.3f, z = %.3f)", get_vec3d_type_name (type), v->x, v->y, v->z);
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid entity debug arg = %d", arg);

			break;
		}
	}

	va_end (pargs);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
