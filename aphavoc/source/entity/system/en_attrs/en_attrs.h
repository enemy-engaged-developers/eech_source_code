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

enum ENTITY_ATTRIBUTES
{
	entity_attr_end,
	entity_attr_attitude_angles,
	entity_attr_char_value,
	entity_attr_child_pred,
	entity_attr_float_value,
	entity_attr_int_value,
	entity_attr_parent,
	entity_attr_ptr_value,
	entity_attr_string,
	entity_attr_vec3d,
	NUM_ENTITY_ATTRIBUTES
};

typedef enum ENTITY_ATTRIBUTES entity_attributes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_ENTITY_ATTRIBUTE_PACK_BITS	(4)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ENTITY_ATTRIBUTE_DATA
{
	char
		*name;

	int
		debug_pack;
};

typedef struct ENTITY_ATTRIBUTE_DATA entity_attribute_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity_attribute_data
	entity_attribute_database[NUM_ENTITY_ATTRIBUTES];

#define get_entity_attribute_name(ATTR) (entity_attribute_database[(ATTR)].name)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ENTITY_ATTR_END entity_attr_end

#define ENTITY_ATTR_ATTITUDE_ANGLES(HEADING,PITCH,ROLL) entity_attr_attitude_angles, ((float) (HEADING)), ((float) (PITCH)), ((float) (ROLL))

#define ENTITY_ATTR_CHAR_VALUE(CHAR_TYPE,VALUE) entity_attr_char_value, ((char_types) (CHAR_TYPE)), ((char) (VALUE))

#define ENTITY_ATTR_CHILD_PRED(LIST_TYPE,CHILD_PRED) entity_attr_child_pred, ((list_types) (LIST_TYPE)), ((entity *) (CHILD_PRED))

#define ENTITY_ATTR_FLOAT_VALUE(FLOAT_TYPE,VALUE) entity_attr_float_value, ((float_types) (FLOAT_TYPE)), ((float) (VALUE))

#define ENTITY_ATTR_INT_VALUE(INT_TYPE,VALUE) entity_attr_int_value, ((int_types) (INT_TYPE)), ((int) (VALUE))

#define ENTITY_ATTR_PARENT(LIST_TYPE,PARENT) entity_attr_parent, ((list_types) (LIST_TYPE)), ((entity *) (PARENT))

#define ENTITY_ATTR_PTR_VALUE(PTR_TYPE,PTR) entity_attr_ptr_value, ((ptr_types) (PTR_TYPE)), ((void *) (PTR))

#define ENTITY_ATTR_STRING(STRING_TYPE,STRING) entity_attr_string, ((string_types) (STRING_TYPE)), ((char *) (STRING))

#define ENTITY_ATTR_VEC3D(VEC3D_TYPE,X,Y,Z) entity_attr_vec3d, ((vec3d_types) (VEC3D_TYPE)), ((float) (X)), ((float) (Y)), ((float) (Z))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_local_entity_attributes (entity *en, char *pargs);

extern void pack_entity_attributes (char *buffer);

extern int unpack_entity_attributes (char *buffer);

extern void pack_entity_attribute (entity_attributes attr);

extern entity_attributes unpack_entity_attribute (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
