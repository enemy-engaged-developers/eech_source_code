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

enum ENTITY_DEBUG_MODES
{
	ENTITY_DEBUG_LOCAL,
	ENTITY_DEBUG_REMOTE,
	ENTITY_DEBUG_PACK,
	ENTITY_DEBUG_UNPACK,
	NUM_ENTITY_DEBUG_MODES
};

typedef enum ENTITY_DEBUG_MODES entity_debug_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_DEBUG_ARGS
{
	ENTITY_DEBUG_ATTITUDE_ANGLES,	  		// (entity_debug_modes mode, entity_debug_args arg, entity *en, float heading, float pitch, float roll)
	ENTITY_DEBUG_ATTITUDE_MATRIX,	  		// (entity_debug_modes mode, entity_debug_args arg, entity *en, matrix3x3 attitude)
	ENTITY_DEBUG_CHAR_TYPE,	  		 		// (entity_debug_modes mode, entity_debug_args arg, entity *en, char_types type)
	ENTITY_DEBUG_CHAR_VALUE,		  		// (entity_debug_modes mode, entity_debug_args arg, entity *en, char_types type, char value)
	ENTITY_DEBUG_CREATE,			  	  		// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_types type, int index)
	ENTITY_DEBUG_DESTROY,		  	  		// (entity_debug_modes mode, entity_debug_args arg, entity *en)
	ENTITY_DEBUG_DESTROY_FAMILY,			// (entity_debug_modes mode, entity_debug_args arg, entity *en)
	ENTITY_DEBUG_ENTITY_ATTRIBUTE,  		// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_attributes attr)
	ENTITY_DEBUG_ENTITY_COMMS_MESSAGE,	// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_comms_messages message)
	ENTITY_DEBUG_ENTITY_INDEX,	  			// (entity_debug_modes mode, entity_debug_args arg, entity *en, int index)
	ENTITY_DEBUG_ENTITY_TYPE,	 	 		// (entity_debug_modes mode, entity_debug_args arg, entity *en, entity_types type)
	ENTITY_DEBUG_FLOAT_TYPE,	  	  		// (entity_debug_modes mode, entity_debug_args arg, entity *en, float_types type)
	ENTITY_DEBUG_FLOAT_VALUE,			  	// (entity_debug_modes mode, entity_debug_args arg, entity *en, float_types type, float value)
	ENTITY_DEBUG_INT_TYPE,	  	  			// (entity_debug_modes mode, entity_debug_args arg, entity *en, int_types type)
	ENTITY_DEBUG_INT_VALUE,			  		// (entity_debug_modes mode, entity_debug_args arg, entity *en, int_types type, int value)
	ENTITY_DEBUG_KILL,			  	  		// (entity_debug_modes mode, entity_debug_args arg, entity *en)
	ENTITY_DEBUG_LIST_TYPE,	  	  			// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type)
	ENTITY_DEBUG_LIST_TYPE_CHILD_PRED,	// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *child_pred)
	ENTITY_DEBUG_LIST_TYPE_CHILD_SUCC,	// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *child_succ)
	ENTITY_DEBUG_LIST_TYPE_FIRST_CHILD,	// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *first_child)
	ENTITY_DEBUG_LIST_TYPE_PARENT, 		// (entity_debug_modes mode, entity_debug_args arg, entity *en, list_types type, entity *parent)
	ENTITY_DEBUG_PTR_TYPE,	 	 			// (entity_debug_modes mode, entity_debug_args arg, entity *en, ptr_types type)
	ENTITY_DEBUG_PTR_VALUE,	 		 		// (entity_debug_modes mode, entity_debug_args arg, entity *en, ptr_types type, void *ptr)
	ENTITY_DEBUG_STRING_TYPE, 	  			// (entity_debug_modes mode, entity_debug_args arg, entity *en, string_types type)
	ENTITY_DEBUG_STRING,			 			// (entity_debug_modes mode, entity_debug_args arg, entity *en, string_types type, char *s)
	ENTITY_DEBUG_VEC3D_TYPE, 	  			// (entity_debug_modes mode, entity_debug_args arg, entity *en, vec3d_types type)
	ENTITY_DEBUG_VEC3D,						// (entity_debug_modes mode, entity_debug_args arg, entity *en, vec3d_types type, vec3d *v)
	NUM_ENTITY_DEBUG_ARGS
};

typedef enum ENTITY_DEBUG_ARGS entity_debug_args;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void enable_debug_log_entity_args (void);

extern void disable_debug_log_entity_args (void);

extern void debug_log_entity_args (entity_debug_modes mode, entity_debug_args arg, entity *en, ...);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
