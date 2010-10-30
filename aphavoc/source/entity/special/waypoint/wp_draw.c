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

// 1 just draw yellow lines
// 2 draw lines and red crosses

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static void draw_local_3d_object (entity *en, float range)
{

	int
		formation_count;

	waypoint
		*raw;

	entity
		*next_waypoint;

	vec3d
		*next_waypoint_position,
		direction;

	formation_type
		*formation_data;

	float
		size,
		length;

	sys_colours
		col;

	raw = (waypoint *) get_local_entity_data (en);

	if (raw->position_type == POSITION_TYPE_VIRTUAL)
	{

		return;
	}

	////////////////////////////////////////
	//
	// draw waypoint
	//
	////////////////////////////////////////

	next_waypoint_position = NULL;

	next_waypoint = raw->waypoint_link.child_succ;

	if (!next_waypoint)
	{
		
		next_waypoint = get_local_entity_first_child (raw->waypoint_link.parent, LIST_TYPE_WAYPOINT);
	}

	if (en != next_waypoint)
	{

		next_waypoint_position = get_local_entity_vec3d_ptr (next_waypoint, VEC3D_TYPE_POSITION);

		direction.x = (next_waypoint_position->x - raw->position.x);
		direction.y = (next_waypoint_position->y - raw->position.y);
		direction.z = (next_waypoint_position->z - raw->position.z);
	}
	else
	{

		direction.x = 0.0;
		direction.y = 1.0;
		direction.z = 0.0;
	}

	length = get_3d_vector_magnitude (&direction);

	if (length > 0.0)
	{

		normalise_3d_vector_given_magnitude (&direction, length);

		#if DEBUG_MODULE >= 2

		create_vectored_debug_3d_object (&raw->position, &direction, OBJECT_3D_RED_ARROW, 0, 1.0);

		#endif

		if (next_waypoint_position)
		{

			if ((raw->sub_type == ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP) || (raw->waypoint_link.child_succ))
			{

				col = COLOUR_YELLOW;

				if (raw->waypoint_link.parent)
				{

					if (((entity *) (raw->waypoint_link.parent))->type == ENTITY_TYPE_TASK)
					{

						col = task_database [get_local_entity_int_value ((entity *) (raw->waypoint_link.parent), INT_TYPE_ENTITY_SUB_TYPE)].waypoint_route_colour;
					}
				}
	
				create_debug_3d_line (&raw->position, next_waypoint_position, *sys_colour_table [col], 1.0);
			}
		}
	}

	////////////////////////////////////////
	//
	// represent formation positions
	//
	////////////////////////////////////////

	formation_data = get_formation (raw->waypoint_formation);

	formation_count = formation_data->number_in_formation;

	direction.x = 0.0;
	direction.y = 1.0;
	direction.z = 0.0;

	while (formation_count)
	{

		vec3d
			pos;

		pos.x = raw->position.x + formation_data->sites [formation_count].x;
		pos.y = raw->position.y + formation_data->sites [formation_count].y;
		pos.z = raw->position.z + formation_data->sites [formation_count].z;

		size = 1.0 / formation_count + 1;

		#if DEBUG_MODULE >= 2

		create_vectored_debug_3d_object (&pos, &direction, OBJECT_3D_RED_ARROW, 0, size);

		#endif
	
		formation_count --;
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_local_waypoint_2d_symbol (entity *en, int add_waypoint_flag, int draw_waypoint_icon, sys_colours waypoint_route_colour)
{

	int
		loop;

	entity
		*task,
		*succ;

	waypoint
		*raw;

	vec3d
		position1,
		position2;

	formation_type
		*formation_data;

	ASSERT (en->type == ENTITY_TYPE_WAYPOINT);

	raw = (waypoint *) get_local_entity_data (en);

	task = get_local_entity_parent (en, LIST_TYPE_WAYPOINT);

	succ = raw->waypoint_link.child_succ;

	//
	// Complete waypoint route for "loop" waypoints
	//

	if (raw->sub_type == ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP)
	{

		succ = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);
	}

	//
	// Draw waypoint (with formation positions if AI-tool)
	//

	formation_data = get_formation ((formation_types) raw->waypoint_formation);

	for (loop = 0; loop < formation_data->number_in_formation; loop ++)
	{

		get_local_waypoint_formation_position (loop, en, &position1);

		if (succ)
		{

			//
			// draw waypoint line
			//
	
			reset_2d_instance (active_2d_environment);
	
			get_local_waypoint_formation_position (loop, succ, &position2);

			draw_2d_half_thick_line (position1.x, position1.z, position2.x, position2.z, *sys_colour_table [waypoint_route_colour]);

			//
			// draw add waypoint icon
			//

			if (add_waypoint_flag)
			{

				vec3d
					add_waypoint_icon_position;

				add_waypoint_icon_position.x = position1.x + ((position2.x - position1.x) / 2);
				add_waypoint_icon_position.z = position1.z + ((position2.z - position1.z) / 2);

//				draw_alpha_icon (GRAPHICS_UI_COMMON_US_WAYPOINT_ADD_ICON, add_waypoint_icon_position.x, add_waypoint_icon_position.z);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_waypoint_draw_functions (void)
{
	#if DEBUG_MODULE

	fn_draw_local_entity_3d_object[ENTITY_TYPE_WAYPOINT]	= draw_local_3d_object;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
