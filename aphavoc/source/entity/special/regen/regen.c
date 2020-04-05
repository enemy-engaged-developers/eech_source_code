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

struct REGENERATION_OBJECT_DATABASE_STRUCTURE
{

	object_3d_index_numbers
		object_index;

	enum ENTITY_SUB_TYPE_REGEN
		regeneration_sub_type;
};

typedef struct REGENERATION_OBJECT_DATABASE_STRUCTURE regeneration_object_database_structure;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

regeneration_object_database_structure
	regeneration_object_database[OBJECT_3D_LAST];

int
	object_3d_updateable_flag[OBJECT_3D_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

regen_list_element
	*regen_queue[NUM_ENTITY_SIDES][NUM_ENTITY_SUB_TYPE_REGENS];

regen_management_element
	regen_manager [NUM_ENTITY_SIDES][NUM_ENTITY_SUB_TYPE_REGENS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	regen_to_landing_conversion [NUM_ENTITY_SUB_TYPE_REGENS];

float
	regen_frequency [NUM_ENTITY_SIDES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_3d_regeneration_database ( void )
{

	int
		count;

	//
	// Setup the regeneration flags for each 3d object
	//

	regen_to_landing_conversion [ENTITY_SUB_TYPE_REGEN_NONE] = 0;
	regen_to_landing_conversion [ENTITY_SUB_TYPE_REGEN_HELICOPTER] = ENTITY_SUB_TYPE_LANDING_HELICOPTER;
	regen_to_landing_conversion [ENTITY_SUB_TYPE_REGEN_FIXED_WING] = ENTITY_SUB_TYPE_LANDING_FIXED_WING;
	regen_to_landing_conversion [ENTITY_SUB_TYPE_REGEN_GROUND] = ENTITY_SUB_TYPE_LANDING_GROUND;
	regen_to_landing_conversion [ENTITY_SUB_TYPE_REGEN_PEOPLE] = ENTITY_SUB_TYPE_LANDING_PEOPLE;
	regen_to_landing_conversion [ENTITY_SUB_TYPE_REGEN_SEA] = ENTITY_SUB_TYPE_LANDING_SEA;

	for ( count = OBJECT_3D_INVALID_OBJECT_INDEX + 1; count < OBJECT_3D_LAST; count++ )
	{

		regeneration_object_database[count].object_index = OBJECT_3D_INVALID_OBJECT_INDEX;

		regeneration_object_database[count].regeneration_sub_type = NUM_ENTITY_SUB_TYPE_REGENS;
	}

	//
	// Setup the updateable flags for each 3d object
	//

	for ( count = OBJECT_3D_INVALID_OBJECT_INDEX + 1; count < OBJECT_3D_LAST; count++ )
	{

		object_3d_updateable_flag[count] = -1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_object_updateable_flag ( int object )
{

	if ( object_3d_updateable_flag[object] == -1 )
	{

		object_3d_instance
			*object_instance = nullptr;

		object_3d_sub_object_search_data
			search;

		object_3d_updateable_flag[object] = FALSE;

		object_instance = construct_3d_object ( object );

		search.search_object = object_instance;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_UPDATEABLE_OBJECT;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{

			object_3d_updateable_flag[object] = TRUE;
		}
		else
		{

			search.search_object = object_instance;
			search.search_depth = 0;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_RADAR;
		
			if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
			{
	
				object_3d_updateable_flag[object] = TRUE;
			}
			
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_GROUND_CREW;
		
			if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
			{
	
				object_3d_updateable_flag[object] = TRUE;
			}
		}

		destruct_3d_object ( object_instance );
	}

	return ( object_3d_updateable_flag[object] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_REGEN get_object_3d_regeneration_type ( object_3d_index_numbers object, int *landing_sub_type )
{

	ASSERT ( object > OBJECT_3D_INVALID_OBJECT_INDEX );

	ASSERT ( object < OBJECT_3D_LAST );

	*landing_sub_type = NUM_ENTITY_SUB_TYPE_LANDINGS;

	if ( regeneration_object_database[object].regeneration_sub_type == NUM_ENTITY_SUB_TYPE_REGENS )
	{

		object_3d_instance
			*object_instance = nullptr;

		object_3d_sub_object_search_data
			search;

		object_instance = construct_3d_object ( object );

		search.search_object = object_instance;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_REGEN_FIXED_WING;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{

			regeneration_object_database[object].regeneration_sub_type = ENTITY_SUB_TYPE_REGEN_FIXED_WING;

			*landing_sub_type = ENTITY_SUB_TYPE_LANDING_FIXED_WING;
		}

		search.search_object = object_instance;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_REGEN_HELICOPTER;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{

			regeneration_object_database[object].regeneration_sub_type = ENTITY_SUB_TYPE_REGEN_HELICOPTER;

			*landing_sub_type = ENTITY_SUB_TYPE_LANDING_HELICOPTER;
		}

		search.search_object = object_instance;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_REGEN_ROUTED_VEHICLE;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{

			regeneration_object_database[object].regeneration_sub_type = ENTITY_SUB_TYPE_REGEN_GROUND;

			*landing_sub_type = ENTITY_SUB_TYPE_LANDING_GROUND;
		}

		search.search_object = object_instance;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_REGEN_PERSON;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{

			regeneration_object_database[object].regeneration_sub_type = ENTITY_SUB_TYPE_REGEN_PEOPLE;

			*landing_sub_type = ENTITY_SUB_TYPE_LANDING_PEOPLE;
		}

/*
		search.object = object_instance;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_REGEN_SHIP_VEHICLE;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{

			regeneration_object_database[object].regeneration_sub_type = ENTITY_SUB_TYPE_REGEN_SHIP_VEHICLE;

			*landing_sub_type = ENTITY_SUB_TYPE_LANDING_SEA;
		}
*/
		destruct_3d_object ( object_instance );

		if ( regeneration_object_database[object].regeneration_sub_type == NUM_ENTITY_SUB_TYPE_REGENS )
		{

			regeneration_object_database[object].regeneration_sub_type = ENTITY_SUB_TYPE_REGEN_NONE;
		}
	}

	switch ( regeneration_object_database[object].regeneration_sub_type )
	{

		case ENTITY_SUB_TYPE_REGEN_FIXED_WING:	{ *landing_sub_type = ENTITY_SUB_TYPE_LANDING_FIXED_WING; break; }
		case ENTITY_SUB_TYPE_REGEN_HELICOPTER:	{ *landing_sub_type = ENTITY_SUB_TYPE_LANDING_HELICOPTER; break; }
		case ENTITY_SUB_TYPE_REGEN_GROUND:		{ *landing_sub_type = ENTITY_SUB_TYPE_LANDING_GROUND; break; }
		case ENTITY_SUB_TYPE_REGEN_PEOPLE:		{ *landing_sub_type = ENTITY_SUB_TYPE_LANDING_PEOPLE; break; }
		case ENTITY_SUB_TYPE_REGEN_NONE:			{ *landing_sub_type = NUM_ENTITY_SUB_TYPE_LANDINGS; break; }
		default:
		{

			debug_fatal ( "REGEN: unknown regen type" );
		}
	}

	return ( regeneration_object_database[object].regeneration_sub_type );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_regen_frequency_difficulty_modifier (void)
{
	//
	// Modify Regen Frequency wrt difficulty level
	//

	// (just use medium for now..)
	return REGEN_UPDATE_MEDIUM	;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

