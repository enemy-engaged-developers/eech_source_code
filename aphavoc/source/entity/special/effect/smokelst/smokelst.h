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


#include "sl_types.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct SMOKE_LIST
{
	effect
		eff;

	smoke_list_types
		smoke_type;

	float
		frequency,
		generator_lifetime,
		smoke_sleep,
		smoke_lifetime,
		texture_distance,
		width_adjustment,
	// Xhit: added scale for downwash effect (030328)
		scale;

	// Xhit: added alpha_percentage for downwash effect (030328)
	unsigned char
		alpha_percentage;

	unsigned int
		alive_count				:	15,
		infinite_generator	:	1;

	signed int		
		head						:	16,
		tail						:	16;

	vec3d
		initial_velocity,
		relative_position,
		*motion_vector,
		*position;

	float
		*start_rotation,
		current_frame;

	unsigned char
		*valid;
		
	list_link
		sector_link;
};

typedef struct SMOKE_LIST smoke_list;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define INFINITE_SMOKE_OFF	0.0

#define INFINITE_SMOKE_ON	1.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"sl_creat.h"

#include	"sl_dbase.h"

#include	"sl_draw.h"

#include	"sl_dstry.h"

#include	"sl_float.h"

// JB 030311 VC rename source files
#include	"sl_smokefuncs.h"

#include	"sl_int.h"

#include	"sl_list.h"

#include	"sl_meta.h"

#include	"sl_move.h"

#include	"sl_msgs.h"

#include	"sl_pack.h"

#include	"sl_updt.h"

#include	"sl_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int set_infinite_smoke_list_generating_state (entity *parent, entity_sub_types type, float state);

extern int clear_smoke_list_generator_lifetime (entity *parent, entity_sub_types type);

//extern int attach_client_server_meta_smoke_lists_to_object (entity *parent, meta_smoke_list_types meta_smoke_type, object_3d_sub_object_index_numbers sub_object_type);

extern int attach_local_meta_smoke_lists_to_object (entity *parent, meta_smoke_list_types meta_smoke_type, object_3d_sub_object_index_numbers sub_object_type, int *entity_index_list);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


