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

struct DIVISION
{
	entity_sub_types
		sub_type;

	int
		division_id;

	list_root
		division_root;

	list_link
		division_link,
		division_headquarters_link;

	char
		division_name [STRING_TYPE_DIVISION_NAME_MAX_LENGTH + 1];
};

typedef struct DIVISION division;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum PLATOON_ID_TYPES
{
	PLATOON_ID_NONE,

	PLATOON_ID_NUMBER,
	PLATOON_ID_LETTER,
	PLATOON_ID_CALLSIGN,
	PLATOON_ID_KEYSITE,

	NUM_PLATOON_ID_TYPES
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum PLATOON_SHORT_NAME_TYPES
{
	PLATOON_SHORT_NAME_INVALID,
	
	PLATOON_SHORT_NAME_CALLSIGN,
	PLATOON_SHORT_NAME_ARMOUR,
	PLATOON_SHORT_NAME_SHIPS,
	PLATOON_SHORT_NAME_KEYSITE,

	NUM_PLATOON_SHORT_NAME_TYPES
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity *create_new_division (entity_sub_types type, entity_sides side, entity *parent, entity *hq, int local_only);

extern entity *add_group_to_division (entity *group, entity *known_division);

extern void get_number_extension (int number, char *extension);

extern int set_local_division_name (entity *en, char *s);

extern void initialise_division_database (void);

extern void deinitialise_division_database (void);

extern void pack_local_division_database (pack_modes mode);

extern void unpack_local_division_database (pack_modes mode);

extern void add_division_id_data (int side, int type, int count, int *number_list);

extern int get_next_free_division_id (int side, int type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "dv_dbase.h"

#include "dv_creat.h"

#include "dv_dstry.h"

#include "dv_int.h"

#include "dv_funcs.h"

#include "dv_list.h"

#include "dv_msgs.h"

#include "dv_pack.h"

#include "dv_str.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
