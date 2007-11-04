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

#define MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD	(30.0)

#define TAIL_ROTOR_RPM_MOTION_BLUR_THRESHOLD	(25.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_main_rotors (entity *en, int ignore_drawn_once, int animate_virtual_cockpit_main_rotors)
{
	helicopter
		*raw;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_blade_moving,
		search_main_rotor_hub;

	int
		start_wind_down_sound,
		main_rotor_motion_blurred,
		search_main_rotor_shaft_depth,
		search_main_rotor_blade_root_static_depth,
		search_main_rotor_blade_section_static_depth,
		search_main_rotor_blade_moving_depth,
		ejected;

	float
		main_rotor_direction,
		main_rotor_rpm,
		main_rotor_pitch,
		main_rotor_roll,
		main_rotor_delta_heading,
		main_rotor_blade_coning_angle,
		main_rotor_blade_droop_angle;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	if (!ignore_drawn_once)
	{
		if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
		{
			return;
		}
	}

	raw = get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	main_rotor_direction = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_DIRECTION);

	start_wind_down_sound = FALSE;

	//
	// main rotor articulation test
	//

	if ((in_flight_articulation_test) && (get_external_view_entity () == en))
	{
		static float
			test_main_rotor_inc = 2.0,
			test_main_rotor_rpm = 0.0;

		test_main_rotor_rpm += test_main_rotor_inc;

		//
		// whilst test_main_rotor_rpm < 0.0 the main rotor blades are stationary
		//

		if ((test_main_rotor_rpm <= -10.0) || (test_main_rotor_rpm >= 100.0))
		{
			test_main_rotor_inc = -test_main_rotor_inc;
		}

		main_rotor_rpm = bound (test_main_rotor_rpm, 0.0, 100.0);

		if (main_rotor_rpm >= MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD)
		{
			main_rotor_blade_coning_angle = ((main_rotor_rpm - MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD) / (100.0 - MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD)) * rad (10.0);
		}
		else
		{
			main_rotor_blade_coning_angle = 0.0;
		}
	}
	else
	{
		main_rotor_rpm = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);

		main_rotor_blade_coning_angle = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE);
	}

	main_rotor_rpm = bound (main_rotor_rpm, 0.0, 100.0);

	main_rotor_blade_coning_angle = max (main_rotor_blade_coning_angle, 0.0);

	main_rotor_pitch = -get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_PITCH);

	main_rotor_roll = -get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_ROLL);

	main_rotor_blade_droop_angle = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_DROOP_ANGLE);

	if
	(
		(main_rotor_rpm < MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD) &&
		(
			(en == get_gunship_entity ()) ||
			(
				(get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDING) ||
				(get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED) ||
				(get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_TAKEOFF)
			)
		)
	)
	{
		main_rotor_motion_blurred = FALSE;

		main_rotor_delta_heading = rad (180.0) * main_rotor_rpm * (1.0 / MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD) * get_delta_time ();

		main_rotor_blade_droop_angle *= 1.0 - (main_rotor_rpm * (1.0 / MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD));
	}
	else
	{
		// arneh, june 06 - speed up main rotor (was 90 deg per second, now depending on rotor 
		// rpm and number of blades is between 180 and 900 deg per second))
		float rotor_angular_speed, blade_factor;
		entity_sub_types sub_type;
		
		main_rotor_motion_blurred = TRUE;

		sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
		switch (sub_type)
		{
		// Five or more rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION:
			blade_factor = 7.0;
			break;

		// four rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
		case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
		case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR:
			blade_factor = 10.0;
			break;

		// coaxial three rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
			blade_factor = 11.0;
			break;
	
		// three rotor blades		
		case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY:
			blade_factor = 15.0;
			break;

		// two rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA:
			blade_factor = 25.0;
			break;
		
		default:
			blade_factor = 15.0;
		}

		rotor_angular_speed = bound(blade_factor * main_rotor_rpm, 180, blade_factor*100);
		main_rotor_delta_heading = rad(rotor_angular_speed) * get_delta_time ();
		// end rotor speed fix
	}

	//
	// stop rotors from spinning if paused ( but must still switch the correct objects on and off )
	//

   if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		main_rotor_delta_heading = 0.0;
	}

	//
	// if animating virtual cockpit main rotors then do not rotate
	//

	if (animate_virtual_cockpit_main_rotors)
	{
		main_rotor_delta_heading = 0.0;
	}

	//
	// if ejected then disable all main rotor blades
	//

	ejected = get_local_entity_int_value (en, INT_TYPE_EJECTED);

	if (ejected)
	{
		main_rotor_motion_blurred = FALSE;

		main_rotor_delta_heading = 0.0;
	}

	//
	// locate rotor shaft
	//

	search_main_rotor_shaft_depth = 0;

	while (TRUE)
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// locate pitch and bank null
			//

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				//
				// set pitch and bank
				//

				search_main_rotor_pitch_bank_null.result_sub_object->relative_pitch = main_rotor_pitch;

				search_main_rotor_pitch_bank_null.result_sub_object->relative_roll = main_rotor_roll;

				//
				// locate heading null
				//

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					//
					// set heading
					//

					search_main_rotor_heading_null.result_sub_object->relative_heading = wrap_angle (search_main_rotor_heading_null.result_sub_object->relative_heading + (main_rotor_delta_heading * main_rotor_direction));

					if (!main_rotor_motion_blurred)
					{
						//
						// disable moving blades
						//

						search_main_rotor_blade_moving_depth = 0;

						while (TRUE)
						{
							search_main_rotor_blade_moving.search_depth = search_main_rotor_blade_moving_depth;
							search_main_rotor_blade_moving.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_MOVING;

							if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_moving) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
							{
								if (search_main_rotor_blade_moving.result_sub_object->visible_object)
								{
									start_wind_down_sound = TRUE;
								}

								search_main_rotor_blade_moving.result_sub_object->visible_object = FALSE;
							}
							else
							{
								break;
							}

							search_main_rotor_blade_moving_depth++;
						}

						//
						// enable static blade roots and set blade droop angle
						//

						search_main_rotor_blade_root_static_depth = 0;

						while (TRUE)
						{
							search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
							search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

							if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
							{
								search_main_rotor_blade_root_static.result_sub_object->visible_object = !ejected;

								search_main_rotor_blade_root_static.result_sub_object->relative_pitch = main_rotor_blade_droop_angle;

								//
								// locate static blade sections and set blade droop angle
								//

								search_main_rotor_blade_section_static_depth = 0;

								while (TRUE)
								{
									search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
									search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

									if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
									{
										search_main_rotor_blade_section_static.result_sub_object->relative_pitch = main_rotor_blade_droop_angle;
									}
									else
									{
										break;
									}

									search_main_rotor_blade_section_static_depth++;
								}
							}
							else
							{
								break;
							}

							search_main_rotor_blade_root_static_depth++;
						}

						//
						// disable moving hub
						//

						search_main_rotor_hub.search_depth = 0;
						search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_MOVING;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_hub.result_sub_object->visible_object = FALSE;
						}

						//
						// enable static hub and set heading
						//

						search_main_rotor_hub.search_depth = 0;
						search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_hub.result_sub_object->visible_object = TRUE;

							search_main_rotor_hub.result_sub_object->relative_heading = search_main_rotor_heading_null.result_sub_object->relative_heading;
						}
					}
					else
					{
						//
						// disable static blades
						//

						search_main_rotor_blade_root_static_depth = 0;

						while (TRUE)
						{
							search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
							search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

							if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
							{
								search_main_rotor_blade_root_static.result_sub_object->visible_object = FALSE;
							}
							else
							{
								break;
							}

							search_main_rotor_blade_root_static_depth++;
						}

						//
						// enable moving blades and set coning angle
						//

						search_main_rotor_blade_moving_depth = 0;

						while (TRUE)
						{
							search_main_rotor_blade_moving.search_depth = search_main_rotor_blade_moving_depth;
							search_main_rotor_blade_moving.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_MOVING;

							if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_moving) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
							{
								search_main_rotor_blade_moving.result_sub_object->visible_object = !ejected;

								search_main_rotor_blade_moving.result_sub_object->relative_pitch = main_rotor_blade_coning_angle;
							}
							else
							{
								break;
							}

							search_main_rotor_blade_moving_depth++;
						}

						//
						// disable static hub
						//

						search_main_rotor_hub.search_depth = 0;
						search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_hub.result_sub_object->visible_object = FALSE;
						}

						//
						// enable moving hub and set heading
						//

						search_main_rotor_hub.search_depth = 0;
						search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_MOVING;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_hub.result_sub_object->visible_object = TRUE;

							search_main_rotor_hub.result_sub_object->relative_heading = search_main_rotor_heading_null.result_sub_object->relative_heading;
						}
					}
				}
			}
		}
		else
		{
			break;
		}

		main_rotor_direction = -main_rotor_direction;

		search_main_rotor_shaft_depth++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_damaged_helicopter_main_rotors (entity *en, int ignore_drawn_once)
{
	helicopter
		*raw;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_hub;

	int
		seed,
		search_main_rotor_shaft_depth,
		search_main_rotor_blade_root_static_depth,
		search_main_rotor_blade_section_static_depth,
		ejected;

	float
		main_rotor_direction,
		main_rotor_rpm,
		main_rotor_pitch,
		main_rotor_roll,
		main_rotor_delta_heading,
		main_rotor_blade_coning_angle,
		main_rotor_blade_droop_angle,
		main_rotor_blade_random_droop_angle;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

   if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		return;
	}

	if (!ignore_drawn_once)
	{
		if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
		{
			return;
		}
	}

	raw = get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	main_rotor_direction = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_DIRECTION);

	main_rotor_rpm = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);

	main_rotor_blade_coning_angle = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE);

	main_rotor_rpm = bound (main_rotor_rpm, 0.0, 100.0);

	main_rotor_blade_coning_angle = max (main_rotor_blade_coning_angle, 0.0);

	main_rotor_pitch = -get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_PITCH);

	main_rotor_roll = -get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_ROLL);

	main_rotor_blade_droop_angle = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_DROOP_ANGLE);

	main_rotor_delta_heading = rad (180.0) * main_rotor_rpm * (1.0 / MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD) * get_delta_time ();

	main_rotor_blade_droop_angle *= 1.0 - (main_rotor_rpm * (1.0 / MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD));

	seed = get_client_server_entity_random_number_seed(en);

	//
	// if ejected then disable all main rotor blades
	//

	ejected = get_local_entity_int_value (en, INT_TYPE_EJECTED);

	if (ejected)
	{
		main_rotor_delta_heading = 0.0;
	}

	//
	// locate rotor shaft
	//

	search_main_rotor_shaft_depth = 0;

	while (TRUE)
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// locate pitch and bank null
			//

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				//
				// set pitch and bank
				//

				search_main_rotor_pitch_bank_null.result_sub_object->relative_pitch = main_rotor_pitch;

				search_main_rotor_pitch_bank_null.result_sub_object->relative_roll = main_rotor_roll;

				//
				// locate heading null
				//

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					//
					// set heading
					//

					search_main_rotor_heading_null.result_sub_object->relative_heading = wrap_angle (search_main_rotor_heading_null.result_sub_object->relative_heading + (main_rotor_delta_heading * main_rotor_direction));

					//
					// set blade droop angle
					//

					search_main_rotor_blade_root_static_depth = 0;

					while (TRUE)
					{
						search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
						search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

						main_rotor_blade_random_droop_angle = sfrand1x (&seed) * (PI * 0.0625);

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_blade_root_static.result_sub_object->visible_object = !ejected;

							search_main_rotor_blade_root_static.result_sub_object->relative_pitch = main_rotor_blade_droop_angle + main_rotor_blade_random_droop_angle;

							//
							// locate static blade sections and set blade droop angle
							//

							search_main_rotor_blade_section_static_depth = 0;

							while (TRUE)
							{
								search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
								search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

								main_rotor_blade_random_droop_angle = sfrand1x (&seed) * (PI * 0.0625);

								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
								{
									if (!search_main_rotor_blade_section_static.result_sub_object->visible_object)
									{
										//
										// stop when we get to a broken section
										//

										break;
									}

									search_main_rotor_blade_section_static.result_sub_object->relative_pitch = main_rotor_blade_droop_angle + main_rotor_blade_random_droop_angle;
								}
								else
								{
									break;
								}

								search_main_rotor_blade_section_static_depth++;
							}
						}
						else
						{
							break;
						}

						search_main_rotor_blade_root_static_depth++;
					}

					//
					// find static hub and set heading
					//

					search_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_STATIC;

					if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_main_rotor_hub.result_sub_object->relative_heading = search_main_rotor_heading_null.result_sub_object->relative_heading;
					}
				}
			}
		}
		else
		{
			break;
		}

		main_rotor_direction = -main_rotor_direction;

		search_main_rotor_shaft_depth++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_virtual_cockpit_main_rotors (entity *en, object_3d_instance *virtual_cockpit_main_rotor_inst3d)
{
	helicopter
		*raw;

	object_3d_instance
		*tmp;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	ASSERT (virtual_cockpit_main_rotor_inst3d);

	raw = get_local_entity_data (en);

	tmp = raw->ac.inst3d;

	raw->ac.inst3d = virtual_cockpit_main_rotor_inst3d;

	if (raw->main_rotor_damaged)
	{
		animate_damaged_helicopter_main_rotors (en, TRUE);
	}
	else
	{
		animate_helicopter_main_rotors (en, TRUE, TRUE);
	}

	raw->ac.inst3d = tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_tail_rotor (entity *en)
{
	helicopter
		*raw;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	int
		depth;

	float
		tail_rotor_direction,
		tail_rotor_rpm,
		tail_rotor_delta_pitch;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	raw = get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	tail_rotor_direction = get_local_entity_float_value (en, FLOAT_TYPE_TAIL_ROTOR_DIRECTION);

	//
	// tail rotor articulation test
	//

	if ((in_flight_articulation_test) && (get_external_view_entity () == en))
	{
		static float
			test_tail_rotor_inc = 2.0,
			test_tail_rotor_rpm = 0.0;

		test_tail_rotor_rpm += test_tail_rotor_inc;

		//
		// whilst test_tail_rotor_rpm < 0.0 the tail rotor blades are stationary
		//

		if ((test_tail_rotor_rpm <= -10.0) || (test_tail_rotor_rpm >= 100.0))
		{
			test_tail_rotor_inc = -test_tail_rotor_inc;
		}

		tail_rotor_rpm = bound (test_tail_rotor_rpm, 0.0, 100.0);
	}
	else
	{
		tail_rotor_rpm = get_local_entity_float_value (en, FLOAT_TYPE_TAIL_ROTOR_RPM);
	}

	tail_rotor_rpm = bound (tail_rotor_rpm, 0.0, 100.0);

	tail_rotor_delta_pitch = 0.0;

	if ((tail_rotor_rpm < TAIL_ROTOR_RPM_MOTION_BLUR_THRESHOLD) &&
		((en == get_gunship_entity ()) || ((get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDING) ||
		(get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED) ||
		(get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_TAKEOFF))))
	{
  		if (get_time_acceleration () != TIME_ACCELERATION_PAUSE)
		{
			tail_rotor_delta_pitch = rad (180.0) * tail_rotor_rpm * (1.0 / TAIL_ROTOR_RPM_MOTION_BLUR_THRESHOLD) * tail_rotor_direction * get_delta_time ();
		}

		//
		// disable moving tail rotor and set pitch (to keep in sync with static tail rotor)
		//

		depth = 0;

		while (TRUE)
		{
			search.search_depth = depth;
			search.search_object = inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_MOVING;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = FALSE;

				search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + tail_rotor_delta_pitch);
			}
			else
			{
				break;
			}

			depth++;
		}

		//
		// enable static tail rotor and set pitch
		//

		depth = 0;

		while (TRUE)
		{
			search.search_depth = depth;
			search.search_object = inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_STATIC;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = TRUE;

				search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + tail_rotor_delta_pitch);
			}
			else
			{
				break;
			}

			depth++;
		}
	}
	else
	{
  		if (get_time_acceleration () != TIME_ACCELERATION_PAUSE)
		{
			tail_rotor_delta_pitch = rad (180.0) * tail_rotor_direction * get_delta_time ();
		}

		//
		// disable static tail rotor and set pitch (to keep in sync with moving tail rotor)
		//

		depth = 0;

		while (TRUE)
		{
			search.search_depth = depth;
			search.search_object = inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_STATIC;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = FALSE;

				search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + tail_rotor_delta_pitch);
			}
			else
			{
				break;
			}

			depth++;
		}

		//
		// enable moving tail rotor and set pitch
		//

		depth = 0;

		while (TRUE)
		{
			search.search_depth = depth;
			search.search_object = inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_MOVING;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = TRUE;

				search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + tail_rotor_delta_pitch);
			}
			else
			{
				break;
			}

			depth++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_wipers (entity *en)
{
	helicopter
		*raw;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	//
	// only animate wipers on player's helicopter
	//

	if (en == get_gunship_entity ())
	{
		raw = get_local_entity_data (en);

		if (raw->ac.object_3d_shape == OBJECT_3D_AH64D_APACHE_LONGBOW)
		{
			animate_apache_external_wipers (raw->ac.inst3d);
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_MI28N_HAVOC)
		{
			animate_havoc_external_wipers (raw->ac.inst3d);
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_KA_52)
		{
			animate_hokum_wipers (raw->ac.inst3d);
		}
		////Moje 030602 Start

		else if (raw->ac.object_3d_shape == OBJECT_3D_UH60_BLACKHAWK)
		{
			animate_blackhawk_external_wipers (raw->ac.inst3d);
		}
		////Moje 030602 End
		////Moje 030619 Start
		else if (raw->ac.object_3d_shape == OBJECT_3D_MI24_HIND)
		{
			animate_hind_external_wipers (raw->ac.inst3d);
		}
		////Moje 030619 End
		////Moje 030816 Start

		else if (raw->ac.object_3d_shape == OBJECT_3D_AH_64A)
		{
			animate_ah64a_external_wipers (raw->ac.inst3d);
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_KA_50)
		{
			animate_ka50_external_wipers (raw->ac.inst3d);
		}
		////Moje 030619 End

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_eo (entity *en)
{
	helicopter
		*raw;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	//
	// only animate electro-optics on player's helicopter
	//

	if (en == get_gunship_entity ())
	{
		raw = get_local_entity_data (en);

		if (raw->ac.object_3d_shape == OBJECT_3D_AH64D_APACHE_LONGBOW)
		{
			animate_apache_eo (raw->ac.inst3d);
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_MI28N_HAVOC)
		{
			animate_havoc_eo (raw->ac.inst3d);
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_RAH66)
		{
			animate_comanche_eo (raw->ac.inst3d);
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_KA_52)
		{
			animate_hokum_eo (raw->ac.inst3d);
		}
		////Moje 030602 Start
		else if (raw->ac.object_3d_shape == OBJECT_3D_UH60_BLACKHAWK)
		{
			animate_blackhawk_eo (raw->ac.inst3d);
		}
		////Moje 030602 End
		////Moje 030619 Start
		else if (raw->ac.object_3d_shape == OBJECT_3D_MI24_HIND)
		{
			animate_hind_eo (raw->ac.inst3d);
		}
		////Moje 030619 End

		////Moje 030816 Start
		else if (raw->ac.object_3d_shape == OBJECT_3D_AH_64A)
		{
			animate_ah64a_eo (raw->ac.inst3d);
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_KA_50)
		{
			animate_ka50_eo (raw->ac.inst3d);
		}
		////Moje 030816 End

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_helicopter_3d_object (entity *en)
{
	helicopter
		*raw;

	ASSERT (en);

	raw = get_local_entity_data (en);

	//
	// store main rotor heading(s)
	//

	//
	// store tail rotor pitch(s)
	//

	//
	// destruct old object
	//

	destruct_3d_object (raw->ac.inst3d);

	//
	// construct new (damaged) object
	//

	raw->ac.object_3d_shape = get_local_entity_int_value (en, INT_TYPE_DESTROYED_3D_SHAPE);

	raw->ac.inst3d = construct_3d_object (raw->ac.object_3d_shape);

	//
	// set id number for new object
	//

	set_helicopter_id_number (en);

	//
	// restore main rotor heading(s)
	//

	//
	// restore tail rotor pitch(s)
	//

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int damage_helicopter_main_rotors (entity *en)
{
	helicopter
		*raw;

	object_3d_instance
		*inst3d;

	int
		seed,
		section_fragment_count;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	raw = get_local_entity_data (en);

	ASSERT (raw->main_rotor_damaged == FALSE);

	inst3d = raw->ac.inst3d;

	seed = get_client_server_entity_random_number_seed(en);

	//
	// damage main rotor object
	//

	section_fragment_count = damage_helicopter_main_rotor_inst3d (inst3d, seed);

	if (get_local_entity_int_value (en, INT_TYPE_EJECTED))
	{
		section_fragment_count = 0;
	}

	//
	// also damage virtual cockpit rotors if entity is the player
	//

	if (en == get_gunship_entity ())
	{
		damage_virtual_cockpit_main_rotors (seed);
	}

	raw->main_rotor_damaged = TRUE;

	return section_fragment_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int damage_helicopter_main_rotor_inst3d (object_3d_instance *inst3d, int seed)
{
	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_blade_moving,
		search_main_rotor_hub;

	int
		section_cut_off_point,
		section_fragment_count,
		search_main_rotor_shaft_depth,
		search_main_rotor_blade_root_static_depth,
		search_main_rotor_blade_section_static_depth,
		search_main_rotor_blade_moving_depth;

	if (!inst3d)
	{
		return 0;
	}

	section_fragment_count = 0;

	//
	// locate rotor shaft
	//

	search_main_rotor_shaft_depth = 0;

	while (TRUE)
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// locate pitch and bank null
			//

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				//
				// locate heading null
				//

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					//
					// disable moving blades
					//

					search_main_rotor_blade_moving_depth = 0;

					while (TRUE)
					{
						search_main_rotor_blade_moving.search_depth = search_main_rotor_blade_moving_depth;
						search_main_rotor_blade_moving.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_MOVING;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_moving) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_blade_moving.result_sub_object->visible_object = FALSE;
						}
						else
						{
							break;
						}

						search_main_rotor_blade_moving_depth++;
					}

					//
					// enable static blade roots
					//

					search_main_rotor_blade_root_static_depth = 0;

					while (TRUE)
					{
						search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
						search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_blade_root_static.result_sub_object->visible_object = TRUE;

							//
							// locate static blade sections
							//

							search_main_rotor_blade_section_static_depth = 0;

							while (TRUE)
							{
								search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
								search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

								search_main_rotor_blade_section_static_depth++;

								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
								{
									break;
								}
							}

							//
							// cut off static blade sections
							//

							if (search_main_rotor_blade_section_static_depth > 0)
							{
								section_cut_off_point = rand16x(&seed) % search_main_rotor_blade_section_static_depth;

								search_main_rotor_blade_section_static_depth = 0;

								while (TRUE)
								{
									search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
									search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

									if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
									{
										if (search_main_rotor_blade_section_static_depth >= section_cut_off_point)
										{
											search_main_rotor_blade_section_static.result_sub_object->visible_object = FALSE;

											section_fragment_count ++;
										}
									}
									else
									{
										break;
									}

									search_main_rotor_blade_section_static_depth++;
								}
							}
						}
						else
						{
							break;
						}

						search_main_rotor_blade_root_static_depth++;
					}

					//
					// disable moving hub
					//

					search_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_MOVING;

					if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_main_rotor_hub.result_sub_object->visible_object = FALSE;
					}

					//
					// enable static hub
					//

					search_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_STATIC;

					if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_main_rotor_hub.result_sub_object->visible_object = TRUE;
					}
				}
			}
		}
		else
		{
			break;
		}

		search_main_rotor_shaft_depth++;
	}

	return section_fragment_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int damage_helicopter_tail_rotors (entity *en)
{
	helicopter
		*raw;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	int
		depth,
		fragment_count;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	raw = get_local_entity_data (en);

	ASSERT (raw->tail_rotor_damaged == FALSE);

	inst3d = raw->ac.inst3d;

	fragment_count = 0;

	//
	// disable moving tail rotor
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_MOVING;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = FALSE;
		}
		else
		{
			break;
		}

		depth++;
	}

	//
	// disable static tail rotor
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_STATIC;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = FALSE;

			fragment_count ++;
		}
		else
		{
			break;
		}

		depth++;
	}

	return fragment_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_main_rotor_fragments (entity *en, int count)
{
	ASSERT (en);

	if ((count > 0) && (get_comms_model () == COMMS_MODEL_SERVER))
	{
		create_client_server_particle_entity
		(
			count,
			get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION),
			20,
			OBJECT_3D_ROTOR_BLADE_DAMAGED
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_tail_rotor_fragments (entity *en, int count)
{
	ASSERT (en);

	if ((count > 0) && (get_comms_model () == COMMS_MODEL_SERVER))
	{
		create_client_server_particle_entity
		(
			count,
			get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION),
			20,
			OBJECT_3D_TAIL_ROTOR_BLADE_DAMAGED
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int restore_helicopter_main_rotors (entity *en)
{
	helicopter
		*raw;

	object_3d_instance
		*inst3d;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	raw = get_local_entity_data (en);

	if (!raw->main_rotor_damaged)
	{
		return FALSE;
	}

	inst3d = raw->ac.inst3d;

	//
	// restore main rotor object
	//

	restore_helicopter_main_rotor_inst3d (inst3d);

	//
	// also restore virtual cockpit rotors if entity is the player
	//

	if (en == get_gunship_entity ())
	{
		restore_virtual_cockpit_main_rotors ();
	}

	raw->main_rotor_damaged = FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int restore_helicopter_main_rotor_inst3d (object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_blade_moving,
		search_main_rotor_hub;

	int
		search_main_rotor_shaft_depth,
		search_main_rotor_blade_root_static_depth,
		search_main_rotor_blade_section_static_depth,
		search_main_rotor_blade_moving_depth;

	if (!inst3d)
	{
		return 0;
	}

	//
	// locate rotor shaft
	//

	search_main_rotor_shaft_depth = 0;

	while (TRUE)
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// locate pitch and bank null
			//

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				//
				// locate heading null
				//

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					//
					// disable moving blades
					//

					search_main_rotor_blade_moving_depth = 0;

					while (TRUE)
					{
						search_main_rotor_blade_moving.search_depth = search_main_rotor_blade_moving_depth;
						search_main_rotor_blade_moving.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_MOVING;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_moving) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_blade_moving.result_sub_object->visible_object = FALSE;
						}
						else
						{
							break;
						}

						search_main_rotor_blade_moving_depth++;
					}

					//
					// enable static blade roots
					//

					search_main_rotor_blade_root_static_depth = 0;

					while (TRUE)
					{
						search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
						search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_blade_root_static.result_sub_object->visible_object = TRUE;

							//
							// locate static blade sections
							//

							search_main_rotor_blade_section_static_depth = 0;

							while (TRUE)
							{
								search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
								search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

								search_main_rotor_blade_section_static_depth++;

								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
								{
									break;
								}
							}

							//
							// cut off static blade sections
							//

							if (search_main_rotor_blade_section_static_depth > 0)
							{
								search_main_rotor_blade_section_static_depth = 0;

								while (TRUE)
								{
									search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
									search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

									if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
									{
										search_main_rotor_blade_section_static.result_sub_object->visible_object = TRUE;
									}
									else
									{
										break;
									}

									search_main_rotor_blade_section_static_depth++;
								}
							}
						}
						else
						{
							break;
						}

						search_main_rotor_blade_root_static_depth++;
					}

					//
					// disable moving hub
					//

					search_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_MOVING;

					if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_main_rotor_hub.result_sub_object->visible_object = FALSE;
					}

					//
					// enable static hub
					//

					search_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_STATIC;

					if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_main_rotor_hub.result_sub_object->visible_object = TRUE;
					}
				}
			}
		}
		else
		{
			break;
		}

		search_main_rotor_shaft_depth++;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int restore_helicopter_tail_rotors (entity *en)
{
	helicopter
		*raw;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	int
		depth;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	raw = get_local_entity_data (en);

	if (!raw->tail_rotor_damaged)
	{
		return FALSE;
	}

	inst3d = raw->ac.inst3d;

	//
	// disable moving tail rotor
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_MOVING;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = FALSE;
		}
		else
		{
			break;
		}

		depth++;
	}

	//
	// enable static tail rotor
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_STATIC;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = TRUE;
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

int get_helicopter_main_rotors_blurred (entity *en)
{
	float
		main_rotor_rpm;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE) == FALSE)
	{
		return FALSE;
	}
	else
	{
		main_rotor_rpm = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);

		return (main_rotor_rpm >= MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_rotation_angle_of_helicopter_main_rotors (object_3d_instance *inst3d, float theta)
{
	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null;

	int
		search_main_rotor_shaft_depth;

	float
		main_rotor_direction;

	ASSERT (inst3d);

	//
	// do not need to use the true main rotor direction (wrt helicopter type)
	//

	main_rotor_direction = 1.0;

	//
	// locate rotor shaft
	//

	search_main_rotor_shaft_depth = 0;

	while (TRUE)
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// locate pitch and bank null
			//

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				//
				// locate heading null
				//

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					//
					// set heading
					//

					search_main_rotor_heading_null.result_sub_object->relative_heading = wrap_angle (theta * main_rotor_direction);
				}
			}
		}
		else
		{
			break;
		}

		main_rotor_direction = -main_rotor_direction;

		search_main_rotor_shaft_depth++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_rotation_angle_of_helicopter_main_rotors (object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null;

	ASSERT (inst3d);

	//
	// locate rotor shaft
	//

	search_main_rotor_shaft.search_depth = 0;
	search_main_rotor_shaft.search_object = inst3d;
	search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

	if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		//
		// locate pitch and bank null
		//

		search_main_rotor_pitch_bank_null.search_depth = 0;
		search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

		if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			//
			// locate heading null
			//

			search_main_rotor_heading_null.search_depth = 0;
			search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				//
				// get heading
				//

				return (search_main_rotor_heading_null.result_sub_object->relative_heading);
			}
		}
	}

	return (0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_rotation_angle_of_helicopter_tail_rotor (object_3d_instance *inst3d, float theta)
{
	object_3d_sub_object_search_data
		search;

	int
		depth;

	ASSERT (inst3d);

	//
	// set static tail rotor rotation angle
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_STATIC;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + theta);
		}
		else
		{
			break;
		}

		depth++;
	}

	//
	// set moving tail rotor rotation angle
	//

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_MOVING;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->relative_pitch = wrap_angle (search.result_sub_object->relative_pitch + theta);
		}
		else
		{
			break;
		}

		depth++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_helicopter_id_number (entity *en)
{
	helicopter
		*raw;

	ASSERT (en);

	raw = get_local_entity_data (en);

	if (raw->ac.mob.side == ENTITY_SIDE_BLUE_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__000,
			TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__001,
			TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__002,
			TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__003,
			TEXTURE_ANIMATION_INDEX_USA_COPTER_DIGIT__004
		);
	}
	else if (raw->ac.mob.side == ENTITY_SIDE_RED_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__000,
			TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__001,
			TEXTURE_ANIMATION_INDEX_CIS_COPTER_DIGIT__002,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
