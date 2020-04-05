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

#define BLURRED_WHEEL_THRESHOLD	3.0

#define TEST_SPEED_MAX 8.0
#define TEST_SPEED_INC 2.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	test_speed = 0.0,
	test_speed_inc = TEST_SPEED_INC;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_routed_vehicle_wheels (entity *en)
{
	routed_vehicle
		*raw = nullptr;

	object_3d_instance
		*inst3d = nullptr;

	float
		speed,
		delta_pitch;

	int
		blurred_flag;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

   if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		return;
	}

	if (!get_local_entity_int_value (en, INT_TYPE_MOBILE_MOVING))
	{
		return;
	}

	raw = (routed_vehicle *) get_local_entity_data (en);

	inst3d = raw->vh.inst3d;

	if ( ( in_flight_articulation_test ) && ( get_external_view_entity() == en ) )
	{
		//
		// debug articulation test
		//

		test_speed += ( test_speed_inc * get_delta_time() );

		if ( test_speed > TEST_SPEED_MAX )
		{
			test_speed_inc = -TEST_SPEED_INC;
		}
		else if ( test_speed <= 0.0 )
		{
			test_speed_inc = TEST_SPEED_INC;
		}

		test_speed = bound( test_speed, 0.0, TEST_SPEED_MAX );

		speed = test_speed;
	}
	else
	{
		//
		// normal operation
		//

		speed = get_local_entity_float_value( en, FLOAT_TYPE_VELOCITY );
	}

	blurred_flag = ( speed > BLURRED_WHEEL_THRESHOLD );

	if ( blurred_flag )
	{
		delta_pitch = PI / 20.0;
	}
	else
	{
		delta_pitch = 2 * speed * get_delta_time ();
	}

	//
	// rotate wheel objects
	//
	// if a blurred wheel type exists on the vehicle then set the correct wheel type visible status, and rotate it
	// otherwise just rotate the standard wheel type
	//

	// fixed
	if ( activate_and_modify_sub_object_type_heading_pitch_and_roll
					(
						inst3d,
						OBJECT_3D_SUB_OBJECT_FIXED_WHEEL_MOVING,
						blurred_flag,
						0.0, delta_pitch, 0.0
					) )
	{
		activate_and_modify_sub_object_type_heading_pitch_and_roll
					(
						inst3d,
						OBJECT_3D_SUB_OBJECT_FIXED_WHEEL,
						!blurred_flag,
						0.0, delta_pitch, 0.0
					);
	}
	else
	{
		activate_and_modify_sub_object_type_heading_pitch_and_roll
					(
						inst3d,
						OBJECT_3D_SUB_OBJECT_FIXED_WHEEL,
						TRUE,
						0.0, delta_pitch, 0.0
					);
	}

	// steerable
	if ( activate_and_modify_sub_object_type_heading_pitch_and_roll
					(
						inst3d,
						OBJECT_3D_SUB_OBJECT_STEERABLE_WHEEL_MOVING,
						blurred_flag,
						0.0, delta_pitch, 0.0
					) )
	{
		activate_and_modify_sub_object_type_heading_pitch_and_roll
					(
						inst3d,
						OBJECT_3D_SUB_OBJECT_STEERABLE_WHEEL,
						!blurred_flag,
						0.0, delta_pitch, 0.0
					);
	}
	else
	{
		activate_and_modify_sub_object_type_heading_pitch_and_roll
					(
						inst3d,
						OBJECT_3D_SUB_OBJECT_STEERABLE_WHEEL,
						TRUE,
						0.0, delta_pitch, 0.0
					);
	}

	//
	// animate track textures
	//

	if ( speed > 0.0 )
	{
		//
		// debug articulation test
		//

		advance_texture_animation_frame_on_object( inst3d, TEXTURE_ANIMATION_INDEX_TRAK0 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_initial_rotation_angle_of_routed_vehicle_wheels (object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search;

	int
		depth;

	float
		ang;

	//
	// vary wheel start positions (ok to use a random number as this is for visual effect only)
	//

	ASSERT (inst3d);

	//
	// fixed wheels
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_FIXED_WHEEL;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			ang = sfrand1() * PI;

			search.result_sub_object->relative_pitch = ang;
		}
		else
		{
			break;
		}

		depth++;
	}

	//
	// steerable wheels
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_STEERABLE_WHEEL;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			ang = sfrand1() * PI;

			search.result_sub_object->relative_pitch = ang;
		}
		else
		{
			break;
		}

		depth++;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_routed_vehicle_3d_object (entity *en)
{
	routed_vehicle
		*raw = nullptr;

	ASSERT (en);

	raw = (routed_vehicle *) get_local_entity_data (en);

	set_sub_object_type_visible_status (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_READY, FALSE);
	
	//	//
//	// destruct old object
//	//
//
//	destruct_3d_object (raw->vh.inst3d);
//
//	//
//	// construct new (damaged) object
//	//
//
//	raw->vh.object_3d_shape = get_local_entity_int_value (en, INT_TYPE_DESTROYED_3D_SHAPE);
//
//	raw->vh.inst3d = construct_3d_object (raw->vh.object_3d_shape);
//
//	//
//	// set id number for new object
//	//
//
//	set_routed_vehicle_id_number (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_routed_vehicle_id_number (entity *en)
{
	routed_vehicle
		*raw = nullptr;

	ASSERT (en);

	raw = (routed_vehicle *) get_local_entity_data (en);

	if (raw->vh.mob.side == ENTITY_SIDE_BLUE_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_USA_TANK_DIGIT__000,
			TEXTURE_ANIMATION_INDEX_USA_TANK_DIGIT__001,
			TEXTURE_ANIMATION_INDEX_USA_TANK_DIGIT__002,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST
		);
	}
	else if (raw->vh.mob.side == ENTITY_SIDE_RED_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_CIS_TANK_DIGIT__000,
			TEXTURE_ANIMATION_INDEX_CIS_TANK_DIGIT__001,
			TEXTURE_ANIMATION_INDEX_CIS_TANK_DIGIT__002,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
