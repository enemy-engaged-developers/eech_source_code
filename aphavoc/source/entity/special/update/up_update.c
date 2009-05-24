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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "entity/tacview/tacview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity
	*update_entity = NULL,
	*update_succ = NULL;

unsigned int
	moved_entities[MAX_NUM_ENTITIES / (sizeof (unsigned int) * 8)],
	rotated_entities[MAX_NUM_ENTITIES / (sizeof (unsigned int) * 8)],
	updated_entities [MAX_NUM_ENTITIES / (sizeof (unsigned int) * 8)];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_update_entity (entity *en)
{
	update_entity = en;

	if (en)
	{
		debug_log ("Setting update_entity (type = %s, index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
	}
	else
	{
		debug_log ("Setting update_entity to NULL");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_client_server_entities (void)
{
	entity
		*en;

	float
		delta_time;

	int
		loop,
		iterations;

	ASSERT (get_update_entity ());

	/////////////////////////////////////////////////

	iterations = 1;

	if (!locked_frame_rate)
	{

		delta_time = get_delta_time ();

		iterations = set_entity_update_frame_rate (command_line_entity_update_frame_rate);
	}

	if (tacview_is_logging() && tacview_reset_frame())
	{
		write_tacview_frame_header();
		memset (moved_entities, 0, MAX_NUM_ENTITIES / (sizeof (unsigned int) * 8));
		memset (rotated_entities, 0, MAX_NUM_ENTITIES / (sizeof (unsigned int) * 8));
	}

	for (loop = 0; loop < iterations; loop ++)
	{

		////////////////////////////////////////

		//
		// update_entities is coded around the entity system to avoid spinning through
		// the update list twice (which Vtune shows up as slow). MB_INT sets and gets
		// the values. You may only set the value to true. It is set to false by the
		// memset below.
		//

		memset (updated_entities, 0, MAX_NUM_ENTITIES / (sizeof (unsigned int) * 8));

		//
		// replaces....
		//
		/*
		en = get_local_entity_first_child (get_update_entity (), LIST_TYPE_UPDATE);

		while (en)
		{

			set_local_entity_int_value (en, INT_TYPE_UPDATED, FALSE);

			en = get_local_entity_child_succ (en, LIST_TYPE_UPDATE);
		}
		*/
		////////////////////////////////////////

		en = get_local_entity_first_child (get_update_entity (), LIST_TYPE_UPDATE);

		while (en)
		{
			set_update_succ (get_local_entity_child_succ (en, LIST_TYPE_UPDATE));

			update_client_server_entity (en);

			set_local_entity_int_value (en, INT_TYPE_UPDATED, TRUE);

			en = get_update_succ ();
		}

		set_update_succ (NULL);

		////////////////////////////////////////
	}

	if (!locked_frame_rate)
	{

		set_manual_delta_time (delta_time);
	}

	/////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_entity_update_frame_rate (int frame_rate)
{

	int
		entity_update_iterations;

	float
		entity_update_delta_time;

	entity_update_iterations = 1;

	ASSERT ((frame_rate >= 1) && (frame_rate <= 100));

	entity_update_iterations = (int) (get_delta_time () * frame_rate + 1.0);

	entity_update_delta_time = get_delta_time () / entity_update_iterations;

	#if DEBUG_MODULE

	debug_log ("UPDATE: requested frame rate %d, delta time %f, iterations %d, set_delta_time %f", frame_rate, get_delta_time (), entity_update_iterations, entity_update_delta_time);

	#endif

	set_manual_delta_time (entity_update_delta_time);

	return entity_update_iterations;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
