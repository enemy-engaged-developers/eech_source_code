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

typedef enum PYLON_TYPES
{

	PYLON_TYPE_STANDARD,
	PYLON_TYPE_START_TERMINATOR,
	PYLON_TYPE_END_TERMINATOR,

	NUM_PYLON_TYPES

} pylon_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PYLON_ATTACHMENT_DATA
{
	object_3d_index_numbers
		default_object_3d_shape;

	char
		attachment_levels[ 6 ];

	vec3d
		attachment_offset[ 6 ];
};

typedef struct PYLON_ATTACHMENT_DATA pylon_attachment_data;


#define pylon_default_object_3d_shape(a) pylon_attachment_database[(a)].default_object_3d_shape

#define pylon_attachment_offset(a,b) pylon_attachment_database[(a)].attachment_offset[(b)]

#define pylon_attachment_level(a,b) pylon_attachment_database[(a)].attachment_levels[(b)]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CABLE_APPROXIMATION_DISTANCE_1		800.0

#define CABLE_APPROXIMATION_DISTANCE_2		1600.0

#define CABLE_APPROXIMATION_DISTANCE_3		4000.0

#define NUM_PYLON_ATTACHMENT_POINTS			6

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern pylon_attachment_data
	pylon_attachment_database[NUM_PYLON_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_pylon_database();

extern float get_pylon_sag_value( int index );

extern pylon_types get_pylon_sub_type( entity_sub_types sub_type );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
