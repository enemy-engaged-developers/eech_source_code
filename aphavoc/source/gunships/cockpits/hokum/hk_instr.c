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

void draw_hokum_virtual_cockpit_instruments (void)
{
	matrix3x3
		*attitude;

	object_3d_sub_object_search_data
		search;

	ASSERT (get_gunship_entity ());

	ASSERT (current_flight_dynamics);

	ASSERT (virtual_cockpit_inst3d);

	attitude = get_local_entity_attitude_matrix_ptr (get_gunship_entity ());

	////////////////////////////////////////
	//
	// ADI
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_ADI;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			heading,
			pitch,
			roll;

		matrix3x3
			inverse_attitude,
			heading_rotation,
			result;

		//
		// get inverse attitude (attiude * inverse attitude = identity) which aligns the ADI with the world axis
		//

		inverse_attitude[0][0] = (*attitude)[0][0];
		inverse_attitude[1][0] = (*attitude)[0][1];
		inverse_attitude[2][0] = (*attitude)[0][2];
		inverse_attitude[0][1] = (*attitude)[1][0];
		inverse_attitude[1][1] = (*attitude)[1][1];
		inverse_attitude[2][1] = (*attitude)[1][2];
		inverse_attitude[0][2] = (*attitude)[2][0];
		inverse_attitude[1][2] = (*attitude)[2][1];
		inverse_attitude[2][2] = (*attitude)[2][2];

		//
		// rotate heading so that the ADI pitch markings face the pilot
		//

		get_3d_transformation_matrix (heading_rotation, get_heading_from_attitude_matrix (*attitude), 0.0, 0.0);

		multiply_matrix3x3_matrix3x3 (result, heading_rotation, inverse_attitude);

		heading = get_heading_from_attitude_matrix (result);

		pitch = get_pitch_from_attitude_matrix (result);

		roll = get_roll_from_attitude_matrix (result);

		search.result_sub_object->relative_heading = -heading;

		search.result_sub_object->relative_pitch = pitch;

		search.result_sub_object->relative_roll = -roll;
	}

	////////////////////////////////////////
	//
	// compass
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_COMPASS;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
	}

	////////////////////////////////////////
	//
	// airspeed
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_AIRSPEED;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			airspeed;

		airspeed = kilometres_per_hour (current_flight_dynamics->indicated_airspeed.value);

		airspeed = bound (airspeed, -50.0, 450.0);

		airspeed *= rad (-180.0) / 400.0;

		search.result_sub_object->relative_roll = airspeed;
	}

	////////////////////////////////////////
	//
	// slip
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_SIDESLIP;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			slip;

		slip = kilometres_per_hour (current_flight_dynamics->indicated_slip.value);

		slip = bound (slip, -100.0, 100.0);

		slip *= rad (45.0) / 100.0;

		search.result_sub_object->relative_roll = slip;
	}

	////////////////////////////////////////
	//
	// altimeter
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_ALITIMETER_LARGE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			altitude;

		altitude = fmod (current_flight_dynamics->barometric_altitude.value, 1000.0f);

		altitude *= rad (-360.0) / 1000.0;

		search.result_sub_object->relative_roll = altitude;
	}

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_ALITIMETER_SMALL;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			altitude;

		altitude = fmod (current_flight_dynamics->barometric_altitude.value, 10000.0f);

		altitude *= rad (-360.0) / 10000.0;

		search.result_sub_object->relative_roll = altitude;
	}

	////////////////////////////////////////
	//
	// vertical speed indicator
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HOKUM_COCKPIT_VERTICAL_SPEED;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		float
			vertical_speed;

		vertical_speed = metres_per_minute (current_flight_dynamics->world_velocity_y.value);

		vertical_speed = bound (vertical_speed, -300.0, 300.0);

		//
		// non-linear scale
		//

		if (vertical_speed < -100.0)
		{
			vertical_speed = rad (90.0) + ((vertical_speed + 100.0) * rad (-90.0) / 200.0);
		}
		else if (vertical_speed > 100.0)
		{
			vertical_speed = rad (-90.0) + ((vertical_speed - 100.0) * rad (-90.0) / 200.0);
		}
	  	else
		{
			vertical_speed *= rad (-90.0) / 100.0;
		}

		search.result_sub_object->relative_roll = vertical_speed;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
