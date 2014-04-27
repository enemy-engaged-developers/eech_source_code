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

// Whole file Retro 6Feb2005
// Manages movement of Pilothead, currently only for trackir vector

// todo
// ) still need a way to tell if this version of the TIR supports this (or if the axis are active)
// ) also need a good (faster ?) way to clip to cockpit limits
// ) make limits configurable

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

static float
	command_line_viewpoint_left_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25} },
	command_line_viewpoint_right_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25} },
	command_line_viewpoint_up_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25} },
	command_line_viewpoint_down_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25} },
	command_line_viewpoint_fore_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {0.4, 0.4}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25} },
	command_line_viewpoint_aft_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {-0.4, -0.4}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25} };

//ataribaby 27/12/2008 for new head g-force movement
static float
	head_vibration[3] = {0, 0, 0},
	head_vibration_force = 0,
	ffb_vibration[3] = {0, 0, 0},
	ffb_vibration_force = 0;
static vec3d
	head_movement,
	ffb_movement;

static float getMaxLeft()
{
	return command_line_viewpoint_left_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxRight()
{
	return command_line_viewpoint_right_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxForeward()
{
	return command_line_viewpoint_fore_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxBackward()
{
	return command_line_viewpoint_aft_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxUp()
{
	return command_line_viewpoint_up_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxDown()
{
	return command_line_viewpoint_down_limit[get_global_gunship_type ()][get_crew_role ()];
}

void clear_head_movement_data (void)
{
	head_movement.x = head_movement.y = head_movement.z = 0.0;	
	ffb_movement.x = ffb_movement.y = ffb_movement.z = 0.0;	
}

	//ataribaby 27/12/2008 new head g-force movement and vibration from main rotor
			// some changes /thealx/

void get_forces_acting_on_pilot (float* x, float* y, float* z, int invert, int view)
{
	int i;
	float
		vibrations_power,
		inertia_power,
		*vibration,
		*vibration_force,
		*rotor_rpm = &current_flight_dynamics->main_rotor_rpm.value;
	dynamics_float_variable
		*velocity = &current_flight_dynamics->velocity_z;
	vec3d
		*movement,
		*accel = &current_flight_dynamics->model_acceleration_vector;
			

	if (view)
	{
		vibrations_power = command_line_cockpit_vibrations;
		inertia_power = command_line_g_force_head_movment_modifier;
		movement = &head_movement;
		vibration = &head_vibration;
		vibration_force = &head_vibration_force;
	}
	else
	{
		vibrations_power = command_line_ffb_vibrations;
		inertia_power = command_line_ffb_dynamics / 10;
		movement = &ffb_movement;
		vibration = &ffb_vibration;
		vibration_force = &ffb_vibration_force;
	}
	
	if (get_time_acceleration() != TIME_ACCELERATION_PAUSE && vibrations_power > 0)
	{
		float z_velocity = 100 * bound(velocity->value * velocity->modifier - 0.9 * velocity->max, 0, 30),
				y_acceleration = *rotor_rpm * max((accel->y > 1.0) * (accel->y - 1.0),
					(current_flight_dynamics->velocity_y.value < - 10.0) * (- current_flight_dynamics->velocity_y.value - 10.0));

		*vibration_force = move_by_rate(*vibration_force, 0.000002 * (vibrations_power * max(z_velocity, y_acceleration) + max(0, vibrations_power - 1) * 5 * *rotor_rpm + 20 * max(0, 40 - fabs(*rotor_rpm - 50))), 0.01); // G force > 1.1, rotor spin-up, vortex ring or maximum speed
		for (i = 0; i < 3; i++)
			vibration[i] = (vibration[i] >= 0 ? -1 : 1) * frand1() * *vibration_force; // should be negative to previous
	}
	else
		for (i = 0; i < 3; i++)
			vibration[i] = 0;

	movement->x = move_by_rate(movement->x, (bound(accel->x * ONE_OVER_G, -3.0, 3.0) * 0.05) * inertia_power, 0.005) + vibration[0];
	movement->y = move_by_rate(movement->y, (bound(accel->y * ONE_OVER_G, -2.0, 5.0) * 0.025) * inertia_power, 0.025) + vibration[1];
	movement->z = move_by_rate(movement->z, (bound(accel->z * ONE_OVER_G, -3.0, 3.0) * 0.05) * inertia_power, 0.05) + vibration[2];

	*x += invert ? - movement->x : movement->x;
	*y += invert ? - movement->y : movement->y;
	*z += invert ? - movement->z : movement->z;
}

float getViewpointOffsetX (float x)
{
	if ((command_line_TIR_6DOF == TRUE) && ( query_TIR_active () == TRUE ))
	{
		float tmp = TIR_GetX() / TIR_GetMaxXY();

		if (tmp >= 0)
			x = tmp * getMaxLeft();
		else
			x = tmp * -getMaxRight();
	}

	x += head_movement.x;
	x = bound ( x, getMaxRight(), getMaxLeft() );
	return x;
}

float getViewpointOffsetY (float y)
{
	if ((command_line_TIR_6DOF == TRUE) && ( query_TIR_active () == TRUE ))
	{
		float tmp = TIR_GetY() / TIR_GetMaxXY();
		if (tmp >= 0)
			y = tmp * -getMaxUp();
		else
			y = tmp * getMaxDown();
	}

	y += head_movement.y;
	y = bound ( y, getMaxDown(), getMaxUp());
	return y;
}

float getViewpointOffsetZ (float z)
{
	if ((command_line_TIR_6DOF == TRUE) && ( query_TIR_active () == TRUE ))
	{
		float tmp = TIR_GetZ() / 16383.;	// this value is fixed, as opposed to x and y
		if (tmp >= 0)
			z = tmp * getMaxForeward();
		else
			z = tmp * -getMaxBackward();
	}

	z += head_movement.z;
	z = bound ( z, getMaxBackward(), getMaxForeward() );

	return z;
}

