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

static void draw_local_3d_object (entity *en, float range)
{
	pylon
		*raw,
		*succ;

	object_3d_instance
		*inst3d;

	float
		this_pylon_heading,
		next_pylon_heading;

	vec3d
		face_normal,
		this_pylon_offset,
		next_pylon_offset;

	int
		cable_loop,
		point_loop,
		this_pylon_type,
		next_pylon_type;

	vec3d
		d,
		pos [NUMBER_OF_PYLON_CABLE_POINTS];

	char
		cable_detail_level;

	rgb_colour
		cable_colour;

	raw = (pylon *) get_local_entity_data (en);

	if (raw->fix.alive)
	{
		//
		// draw pylon object
		//

		inst3d = construct_temporary_3d_object (raw->fix.object_3d_shape, FALSE);

		if (inst3d)
		{
			//
			// cable colour
			//

			cable_colour.r = 96;
			cable_colour.g = 96;
			cable_colour.b = 96;
			cable_colour.a = 255;

			//
			// cable approximations
			//

			if (range < CABLE_APPROXIMATION_DISTANCE_1)
			{
				cable_detail_level = 3;
			}
			else if (range < CABLE_APPROXIMATION_DISTANCE_2)
			{
				cable_detail_level = 2;
			}
			else if (range < CABLE_APPROXIMATION_DISTANCE_3)
			{
				cable_detail_level = 1;
			}
			else
			{
				cable_detail_level = 0;
			}

			memcpy (&inst3d->vp.position, &raw->fix.position, sizeof (vec3d));

			this_pylon_heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

			this_pylon_type = get_pylon_sub_type (raw->fix.sub_type);

			if (fixed_database [raw->fix.sub_type].align_with_terrain)
			{
				get_3d_terrain_face_normal (&face_normal, raw->fix.position.x, raw->fix.position.z);

				get_3d_transformation_matrix_from_face_normal_and_heading (inst3d->vp.attitude, &face_normal, this_pylon_heading);
			}
			else
			{
				get_3d_transformation_matrix (inst3d->vp.attitude, this_pylon_heading, 0.0, 0.0);
			}

			insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);

			//
			// draw connecting wires
			//

			if (raw->succ)
			{
				succ = (pylon *) get_local_entity_data (raw->succ);

				if (succ->fix.alive)
				{
					next_pylon_type = get_pylon_sub_type (succ->fix.sub_type);

					next_pylon_heading = get_local_entity_float_value (raw->succ, FLOAT_TYPE_HEADING);

					for (cable_loop = NUM_PYLON_ATTACHMENT_POINTS - 1; cable_loop >= 0; cable_loop --)
					{
						if (pylon_attachment_level (this_pylon_type, cable_loop) >= cable_detail_level)
						{
							continue;
						}

						this_pylon_offset = pylon_attachment_offset (this_pylon_type, cable_loop);
						next_pylon_offset = pylon_attachment_offset (next_pylon_type, cable_loop);

						//
						// get first point
						//
						pos [0].x = raw->fix.position.x + (this_pylon_offset.x * cos (this_pylon_heading));
						pos [0].y = raw->fix.position.y + this_pylon_offset.y;
						pos [0].z = raw->fix.position.z - (this_pylon_offset.x * sin (this_pylon_heading));

						//
						// get last point
						//
						pos [NUMBER_OF_PYLON_CABLE_POINTS - 1].x = succ->fix.position.x + (next_pylon_offset.x * cos (next_pylon_heading));
						pos [NUMBER_OF_PYLON_CABLE_POINTS - 1].y = succ->fix.position.y + next_pylon_offset.y;
						pos [NUMBER_OF_PYLON_CABLE_POINTS - 1].z = succ->fix.position.z - (next_pylon_offset.x * sin (next_pylon_heading));

						//
						// calculate intermediate points
						//

						d.x = (pos [NUMBER_OF_PYLON_CABLE_POINTS - 1].x - pos [0].x) / NUMBER_OF_PYLON_CABLE_POINTS;
						d.y = (pos [NUMBER_OF_PYLON_CABLE_POINTS - 1].y - pos [0].y) / NUMBER_OF_PYLON_CABLE_POINTS;
						d.z = (pos [NUMBER_OF_PYLON_CABLE_POINTS - 1].z - pos [0].z) / NUMBER_OF_PYLON_CABLE_POINTS;

						for (point_loop = 1 ; point_loop < NUMBER_OF_PYLON_CABLE_POINTS - 1 ; point_loop++)
						{
							pos [point_loop].x = pos [point_loop - 1].x + d.x;
							pos [point_loop].y = pos [point_loop - 1].y + d.y;
							pos [point_loop].z = pos [point_loop - 1].z + d.z;
						}

						//
						// add "sag"
						//

						for (point_loop = 1 ; point_loop < NUMBER_OF_PYLON_CABLE_POINTS - 1 ; point_loop++)
						{
							pos [point_loop].y -= (get_pylon_sag_value (point_loop) * MAX_PYLON_CABLE_SAG);
						}

						//
						// draw cable
						//

						insert_zbiased_polyline_into_3d_scene (NUMBER_OF_PYLON_CABLE_POINTS, 0.0, TRUE, cable_colour, pos );

					}
				}
				else
				{
					//
					// next pylon is not alive, so make cables "hang loose"
					//

					for (cable_loop = NUM_PYLON_ATTACHMENT_POINTS - 1; cable_loop >= 0; cable_loop --)
					{
						if (pylon_attachment_level (this_pylon_type, cable_loop) >= cable_detail_level)
						{
							continue;
						}

						this_pylon_offset = pylon_attachment_offset (this_pylon_type, cable_loop);

						//
						// get first point
						//

						pos [0].x = raw->fix.position.x + (this_pylon_offset.x * cos (this_pylon_heading));
						pos [0].y = raw->fix.position.y + this_pylon_offset.y;
						pos [0].z = raw->fix.position.z - (this_pylon_offset.x * sin (this_pylon_heading));

						//
						// get last point
						//

						pos [1].x = pos [0].x;
						pos [1].y = pos [0].y - 20.0;
						pos [1].z = pos [0].z;

						//
						// draw cable
						//

						insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, pos );

					}
				}
			}
		}
	}
	else
	{
		//
		// draw destroyed pylon object
		//

		inst3d = construct_temporary_3d_object (raw->fix.object_3d_shape, FALSE);

		if (inst3d)
		{

			memcpy (&inst3d->vp.position, &raw->fix.position, sizeof (vec3d));

			this_pylon_heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

			if (fixed_database [raw->fix.sub_type].align_with_terrain)
			{
				get_3d_terrain_face_normal (&face_normal, raw->fix.position.x, raw->fix.position.z);

				get_3d_transformation_matrix_from_face_normal_and_heading (inst3d->vp.attitude, &face_normal, this_pylon_heading);
			}
			else
			{
				get_3d_transformation_matrix (inst3d->vp.attitude, this_pylon_heading, 0.0, 0.0);
			}

			insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*static*/ void draw_local_2d_symbol (entity *en)
{
	pylon
		*raw;

	raw = (pylon *) get_local_entity_data (en);

	if (!raw->fix.alive)
	{
		return;
	}

	//
	// Debug
	//

	if ((int) en % 5)
	{

		return;
	}

	//
	//
	//

	set_2d_instance_position (active_2d_environment, raw->fix.position.x, raw->fix.position.z);

	draw_2d_square (sys_col_yellow);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_pylon_draw_functions (void)
{
	fn_draw_local_entity_3d_object [ENTITY_TYPE_PYLON]	 = draw_local_3d_object;

	//fn_draw_local_entity_2d_symbol [ENTITY_TYPE_PYLON]	 = draw_local_2d_symbol;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
