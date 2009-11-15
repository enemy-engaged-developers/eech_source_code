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

#define SHIP_BLURRED_ROTOR_THRESHOLD	3.0

#define SHIP_TEST_SPEED_MAX 8.0
#define SHIP_TEST_SPEED_INC 1.5

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	ship_test_speed = 0.0,
	ship_test_speed_inc = SHIP_TEST_SPEED_INC;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_ship_rotors (entity *en)
{
	ship_vehicle
		*raw;

	object_3d_instance
		*inst3d;

	float
		ang,
		speed;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	raw = (ship_vehicle *) get_local_entity_data (en);

	inst3d = raw->vh.inst3d;

	if ((in_flight_articulation_test) && (get_external_view_entity() == en))
	{
		//
		// debug articulation test
		//

		ship_test_speed += (ship_test_speed_inc * get_delta_time());

		if (ship_test_speed > SHIP_TEST_SPEED_MAX)
		{
			ship_test_speed_inc = -SHIP_TEST_SPEED_INC;
		}
		else if (ship_test_speed <= 0.0)
		{
			ship_test_speed_inc = SHIP_TEST_SPEED_INC;
		}

		ship_test_speed = bound (ship_test_speed, 0.0, SHIP_TEST_SPEED_MAX);

		speed = ship_test_speed;
	}
	else
	{
		//
		// normal operation
		//

		speed = get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY);
	}

	//
	// set the correct blade type visible status
	//

	if (speed > SHIP_BLURRED_ROTOR_THRESHOLD)
	{
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_MOVING, TRUE);
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_STATIC, FALSE);

		ang = PI / 20.0;
	}
	else
	{
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_MOVING, FALSE);
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_STATIC, TRUE);

		ang = 2.0 * speed * get_delta_time ();
	}

	//
	// rotate hub
	//

	modify_sub_object_type_heading_pitch_and_roll (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_HUB, ang, 0.0, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_ship_3d_object (entity *en)
{
	ship_vehicle
		*raw;

	ASSERT (en);

	raw = (ship_vehicle *) get_local_entity_data (en);

	if (raw->vh.object_3d_shape == get_local_entity_int_value (en, INT_TYPE_DESTROYED_3D_SHAPE))
	{
		return;
	}

	//
	// destruct old object
	//

	destruct_3d_object (raw->vh.inst3d);

	//
	// construct new (damaged) object
	//

	raw->vh.object_3d_shape = get_local_entity_int_value (en, INT_TYPE_DESTROYED_3D_SHAPE);

	raw->vh.inst3d = construct_3d_object (raw->vh.object_3d_shape);

	//
	// set id number for new object
	//

	set_routed_vehicle_id_number (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_ship_vehicle_id_number (entity *en)
{
	ship_vehicle
		*raw;

	ASSERT (en);

	raw = (ship_vehicle *) get_local_entity_data (en);

	if (raw->vh.mob.side == ENTITY_SIDE_BLUE_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_USA_NAVY__000,
			TEXTURE_ANIMATION_INDEX_USA_NAVY__001,
			TEXTURE_ANIMATION_INDEX_USA_NAVY__002,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST
		);
	}
	else if (raw->vh.mob.side == ENTITY_SIDE_RED_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_CIS_PENNANT__000,
			TEXTURE_ANIMATION_INDEX_CIS_PENNANT__001,
			TEXTURE_ANIMATION_INDEX_CIS_PENNANT__002,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









