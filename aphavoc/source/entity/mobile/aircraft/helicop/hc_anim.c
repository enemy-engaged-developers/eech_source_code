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
#include "gunships/dynamics/common/co_undercarriage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD	(30.0)

#define TAIL_ROTOR_RPM_MOTION_BLUR_THRESHOLD	(25.0)

static void create_rotor_blade_fragment (entity *en, viewpoint blade_vp, int main_rotor);

int
	quantity_of_roots[NUM_ENTITY_SUB_TYPE_AIRCRAFT],
	quantity_of_shafts[NUM_ENTITY_SUB_TYPE_AIRCRAFT],
	quantity_of_sections[NUM_ENTITY_SUB_TYPE_AIRCRAFT];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_controls ( entity *en )
{
	helicopter
		*raw = nullptr;

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return;

	raw = (helicopter *) get_local_entity_data (en);

	animate_entity_simple_keyframed_sub_objects( raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_AH64D_TAILPLANE, bound(- raw->ac.mob.velocity / 25 + 1.5, 0, 1));
	animate_entity_simple_keyframed_sub_objects( raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_MIL_TAILPLANE, bound(get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE) * 10, 0, 1));
	animate_entity_simple_keyframed_sub_objects( raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TILT_ROTOR, bound( raw->ac.mob.velocity / 80, 0, 1));
	if (en == get_gunship_entity())
		animate_entity_simple_keyframed_sub_objects( raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_KA52_RUDDER, (100 + current_flight_dynamics->input_data.pedal.value) / 200 );
	else
		animate_entity_simple_keyframed_sub_objects( raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_KA52_RUDDER, 0.5 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_main_rotors (entity *en, int ignore_drawn_once)
{
	helicopter
		*raw = nullptr;

	object_3d_instance
		*inst3d = nullptr;

	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_blade_moving,
		search_main_rotor_hub;

	int
		start_wind_down_sound = FALSE,
		search_main_rotor_shaft_depth,
		search_main_rotor_blade_root_static_depth,
		search_main_rotor_blade_section_static_depth,
		search_main_rotor_blade_moving_depth,
		ejected,
		blades_dissolve;

	unsigned int
		last_moving_blade_state,
		subtype;

	float
		main_rotor_direction,
		main_rotor_rpm,
		main_rotor_pitch,
		main_rotor_roll,
		main_rotor_delta_heading,
		main_rotor_blade_coning_angle,
		main_rotor_blade_droop_angle,
		real_rotor_rpm,
		blade_heading;

	ASSERT (en);
	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	if (!ignore_drawn_once && get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME) || !get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return;

	raw = (helicopter *) get_local_entity_data (en);
	inst3d = raw->ac.inst3d;
	if (!inst3d)
		return;

	subtype = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	ASSERT (subtype < NUM_ENTITY_SUB_TYPE_AIRCRAFT);

	// count rotors

	if (!quantity_of_roots[subtype])
		quantity_of_roots[subtype] = count_sub_object_type_depth(inst3d, OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC);
	if (!quantity_of_shafts[subtype])
		quantity_of_shafts[subtype] = count_sub_object_type_depth(inst3d, OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT);
	if (!quantity_of_sections[subtype])
		quantity_of_sections[subtype] = count_sub_object_type_depth(inst3d, OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC);

	// main rotor articulation test

	if ((in_flight_articulation_test) && (get_external_view_entity () == en))
	{
		static float
			test_main_rotor_inc = 2.0,
			test_main_rotor_rpm = 0.0;

		test_main_rotor_rpm += test_main_rotor_inc;

		// whilst test_main_rotor_rpm < 0.0 the main rotor blades are stationary

		if ((test_main_rotor_rpm <= -10.0) || (test_main_rotor_rpm >= 100.0))
			test_main_rotor_inc = -test_main_rotor_inc;

		main_rotor_rpm = bound (test_main_rotor_rpm, 0.0, 100.0);

		if (main_rotor_rpm >= MAIN_ROTOR_RPM_MOTION_BLUR_THRESHOLD)
			main_rotor_blade_coning_angle = main_rotor_rpm / 100.0 * rad (5.0);
	}
	else
	{
		main_rotor_rpm = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);
		main_rotor_blade_coning_angle = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE);
	}

	main_rotor_direction = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_DIRECTION);
	main_rotor_rpm = bound (main_rotor_rpm * (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_DEAD ? 1.0 : 0.0), 0.0, 100.0); // stop spinning if heli destroyed
	main_rotor_blade_coning_angle = max (0.5f * main_rotor_blade_coning_angle, 0.0f);
	main_rotor_pitch = -get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_PITCH);
	main_rotor_roll = -get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_ROLL);
	main_rotor_blade_droop_angle = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_BLADE_DROOP_ANGLE) * 0.75;
	ejected = get_local_entity_int_value (en, INT_TYPE_EJECTED);
	blades_dissolve = 255 - 255 * command_line_blurred_rotor_blades * bound(1.1 * main_rotor_rpm - 70, 0, 30) / 30;

	switch (subtype)
	{
		// Seven rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION: // 185, 9.7
			real_rotor_rpm = 185;
			break;
		// Five rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B: // 242, 12.7
		case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND: // 240, 12.6
			real_rotor_rpm = 240;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP: // 192, 10
			real_rotor_rpm = 192;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK: // 120, 6.28
			real_rotor_rpm = 120;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE: // 354, 18.5
			real_rotor_rpm = 354;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT:
			real_rotor_rpm = 130;
			break;
		// four rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK: // 258, 13.5
			real_rotor_rpm = 258;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR: // 396, 20.7
			real_rotor_rpm = 396;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW: // 292, 15.3
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE: // 289, 15
			real_rotor_rpm = 290;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER:
			real_rotor_rpm = 290;
			break;
		// three rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B: // 237, 12.4
			real_rotor_rpm = 237;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
			real_rotor_rpm = 300;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK: // 225, 11.8
		case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT: // 264, 13.8
			real_rotor_rpm = 225;
			break;
		case ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY: // 338, 17.7
			real_rotor_rpm = 338;
			break;
		// two rotor blades
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA: // 324, 17
			real_rotor_rpm = 324;
			break;
		default:
			real_rotor_rpm = 180;
	}

	main_rotor_delta_heading = min(real_rotor_rpm * PI2 * main_rotor_rpm / 6000 * get_delta_time (), PI2 / quantity_of_roots[subtype] * quantity_of_shafts[subtype] / 3.75f);

	main_rotor_blade_droop_angle *= max (1.0f - main_rotor_rpm / 60.0f, - 0.1f);

	// stop rotors from spinning if paused ( but must still switch the correct objects on and off )

	if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
		main_rotor_delta_heading = 0.0;

	// locate rotor shaft

	search_main_rotor_shaft_depth = 0;

	while (TRUE)
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			// locate pitch and bank null

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				// set pitch and bank

				search_main_rotor_pitch_bank_null.result_sub_object->relative_pitch = main_rotor_pitch * main_rotor_rpm / 100.0f;
				search_main_rotor_pitch_bank_null.result_sub_object->relative_roll = main_rotor_roll * main_rotor_rpm / 100.0f;

				// locate heading null

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					// set heading

					search_main_rotor_heading_null.result_sub_object->relative_heading = wrap_angle (search_main_rotor_heading_null.result_sub_object->relative_heading + main_rotor_delta_heading * main_rotor_direction);

					// adjust moving blades and static blade roots

					search_main_rotor_blade_root_static_depth = 0;
					search_main_rotor_blade_moving_depth = 0;

					while (TRUE)
					{
						float blade_pitch = main_rotor_rpm / 5000.0 + main_rotor_blade_coning_angle;
						float blade_roll = 0.0;

						search_main_rotor_blade_moving.search_depth = search_main_rotor_blade_moving_depth;
						search_main_rotor_blade_moving.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_MOVING;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_moving) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							blade_heading = search_main_rotor_blade_moving.result_sub_object->relative_heading;
							blade_roll = 2.0f * main_rotor_direction * bound(-cos(blade_heading + search_main_rotor_heading_null.result_sub_object->relative_heading) * main_rotor_pitch +
								sin(blade_heading + search_main_rotor_heading_null.result_sub_object->relative_heading) * main_rotor_roll + main_rotor_blade_coning_angle, rad(-10.0), rad(10.0));

							search_main_rotor_blade_moving.result_sub_object->relative_pitch = blade_pitch;
							search_main_rotor_blade_moving.result_sub_object->relative_roll = 0.0;
							if ((get_time_acceleration () == TIME_ACCELERATION_PAUSE && !command_line_blurred_rotor_blades) || ejected) // hide moving blades
								search_main_rotor_blade_moving.result_sub_object->visible_object = last_moving_blade_state = 0;
							else
								search_main_rotor_blade_moving.result_sub_object->visible_object = (main_rotor_rpm >= 50.0);
							search_main_rotor_blade_moving.result_sub_object->relative_scale.x = (1.0 + command_line_blurred_rotor_blades) * max((main_rotor_rpm - 50.0f) / 100.0f, 0.0f);
							search_main_rotor_blade_moving.result_sub_object->relative_scale.y = 0.1;
							if (search_main_rotor_blade_moving.result_sub_object->visible_object < last_moving_blade_state)
								start_wind_down_sound = TRUE;
							last_moving_blade_state = search_main_rotor_blade_moving.result_sub_object->visible_object;
						}

						search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
						search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_main_rotor_blade_root_static.result_sub_object->visible_object = !ejected;
							search_main_rotor_blade_root_static.result_sub_object->relative_pitch = blade_pitch + main_rotor_blade_droop_angle;
							search_main_rotor_blade_root_static.result_sub_object->relative_roll = blade_roll;
#ifndef OGRE_EE
							search_main_rotor_blade_root_static.result_sub_object->object_dissolve_value = blades_dissolve;
#endif

							// locate static blade sections and set blade droop angle

							search_main_rotor_blade_section_static_depth = 0;

							while (TRUE)
							{
								search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
								search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
								{
									if (search_main_rotor_blade_section_static.result_sub_object->visible_object)
									{
										search_main_rotor_blade_section_static.result_sub_object->visible_object = !ejected;
										search_main_rotor_blade_section_static.result_sub_object->relative_pitch = main_rotor_blade_droop_angle;
									}
									else
									{
										last_moving_blade_state = search_main_rotor_blade_moving.result_sub_object->visible_object = FALSE; // disable moving blade if it's damaged
#ifndef OGRE_EE
										search_main_rotor_blade_root_static.result_sub_object->object_dissolve_value = 255;
#endif
										break;
									}
								}
								else
									break;

								search_main_rotor_blade_section_static_depth++;
							}
						}
						else
							break;

						search_main_rotor_blade_moving_depth++;
						search_main_rotor_blade_root_static_depth++;;
					}

					// disable moving hub

					search_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_MOVING;

					while (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND && search_main_rotor_hub.result_sub_object->visible_object)
					{
						search_main_rotor_hub.result_sub_object->visible_object = FALSE;
						search_main_rotor_hub.search_depth++;
					}

					// enable static hub and set heading

					search_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_STATIC;

					while (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_main_rotor_hub.result_sub_object->relative_heading = search_main_rotor_heading_null.result_sub_object->relative_heading;
						search_main_rotor_hub.search_depth++;
					}
				}
			}
		}
		else
			break;


		main_rotor_direction = -main_rotor_direction;
		search_main_rotor_shaft_depth++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_virtual_cockpit_main_rotors (entity *en, object_3d_instance *cockpit_main_rotor_inst3d, object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_blade_moving,
		search_main_rotor_hub,
		search_cockpit_main_rotor_shaft,
		search_cockpit_main_rotor_pitch_bank_null,
		search_cockpit_main_rotor_heading_null,
		search_cockpit_main_rotor_blade_root_static,
		search_cockpit_main_rotor_blade_section_static,
		search_cockpit_main_rotor_blade_moving,
		search_cockpit_main_rotor_hub;

	int
		search_main_rotor_shaft_depth = 0,
		search_main_rotor_blade_root_static_depth = 0,
		search_main_rotor_blade_section_static_depth = 0,
		search_main_rotor_blade_moving_depth = 0;

	ASSERT (en);
	ASSERT (en == get_gunship_entity());

	while (TRUE)
	{
		search_main_rotor_shaft.search_depth = search_cockpit_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_cockpit_main_rotor_shaft.search_object = cockpit_main_rotor_inst3d;
		search_main_rotor_shaft.sub_object_index = search_cockpit_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
				find_object_3d_sub_object (&search_cockpit_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			// locate pitch and bank null

			search_main_rotor_pitch_bank_null.search_depth = search_cockpit_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = search_cockpit_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
					find_object_3d_sub_object_from_sub_object (&search_cockpit_main_rotor_shaft, &search_cockpit_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				// copy pitch and bank

				search_cockpit_main_rotor_pitch_bank_null.result_sub_object->relative_pitch = search_main_rotor_pitch_bank_null.result_sub_object->relative_pitch;
				search_cockpit_main_rotor_pitch_bank_null.result_sub_object->relative_roll = search_main_rotor_pitch_bank_null.result_sub_object->relative_roll;

				// locate heading null

				search_main_rotor_heading_null.search_depth = search_cockpit_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = search_cockpit_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
						find_object_3d_sub_object_from_sub_object (&search_cockpit_main_rotor_pitch_bank_null, &search_cockpit_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					// copy heading

					search_cockpit_main_rotor_heading_null.result_sub_object->relative_heading = search_main_rotor_heading_null.result_sub_object->relative_heading;

					// find static and moving blades

					search_main_rotor_blade_root_static_depth = 0;
					search_main_rotor_blade_moving_depth = 0;

					while (TRUE)
					{
						search_main_rotor_blade_moving.search_depth = search_cockpit_main_rotor_blade_moving.search_depth = search_main_rotor_blade_moving_depth;
						search_main_rotor_blade_moving.sub_object_index = search_cockpit_main_rotor_blade_moving.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_MOVING;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_moving) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
								find_object_3d_sub_object_from_sub_object (&search_cockpit_main_rotor_heading_null, &search_cockpit_main_rotor_blade_moving) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_cockpit_main_rotor_blade_moving.result_sub_object->relative_pitch = search_main_rotor_blade_moving.result_sub_object->relative_pitch;
							search_cockpit_main_rotor_blade_moving.result_sub_object->relative_roll = search_main_rotor_blade_moving.result_sub_object->relative_roll;
							search_cockpit_main_rotor_blade_moving.result_sub_object->visible_object = search_main_rotor_blade_moving.result_sub_object->visible_object;
							search_cockpit_main_rotor_blade_moving.result_sub_object->relative_scale.x = search_main_rotor_blade_moving.result_sub_object->relative_scale.x;
							search_cockpit_main_rotor_blade_moving.result_sub_object->relative_scale.y = search_main_rotor_blade_moving.result_sub_object->relative_scale.y;
						}

						search_main_rotor_blade_root_static.search_depth = search_cockpit_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
						search_main_rotor_blade_root_static.sub_object_index = search_cockpit_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
								find_object_3d_sub_object_from_sub_object (&search_cockpit_main_rotor_heading_null, &search_cockpit_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_cockpit_main_rotor_blade_root_static.result_sub_object->visible_object = search_main_rotor_blade_root_static.result_sub_object->visible_object;
							search_cockpit_main_rotor_blade_root_static.result_sub_object->relative_pitch = search_main_rotor_blade_root_static.result_sub_object->relative_pitch;
							search_cockpit_main_rotor_blade_root_static.result_sub_object->relative_roll = search_main_rotor_blade_root_static.result_sub_object->relative_roll;
#ifndef OGRE_EE
							search_cockpit_main_rotor_blade_root_static.result_sub_object->object_dissolve_value = search_main_rotor_blade_root_static.result_sub_object->object_dissolve_value;
#endif

							// locate static blade sections and copy blade droop angle

							search_main_rotor_blade_section_static_depth = 0;

							while (TRUE)
							{
								search_main_rotor_blade_section_static.search_depth = search_cockpit_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
								search_main_rotor_blade_section_static.sub_object_index = search_cockpit_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
										find_object_3d_sub_object_from_sub_object (&search_cockpit_main_rotor_blade_root_static, &search_cockpit_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
								{
									search_cockpit_main_rotor_blade_section_static.result_sub_object->relative_pitch = search_main_rotor_blade_section_static.result_sub_object->relative_pitch;
									search_cockpit_main_rotor_blade_section_static.result_sub_object->visible_object = search_main_rotor_blade_section_static.result_sub_object->visible_object;
								}
								else
									break;

								search_main_rotor_blade_section_static_depth++;
							}
						}
						else
							break;

						search_main_rotor_blade_moving_depth++;
						search_main_rotor_blade_root_static_depth++;;
					}

					// copy moving hub

					search_main_rotor_hub.search_depth = search_cockpit_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = search_cockpit_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_MOVING;

					while (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
							find_object_3d_sub_object_from_sub_object (&search_cockpit_main_rotor_shaft, &search_cockpit_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_cockpit_main_rotor_hub.result_sub_object->visible_object = search_main_rotor_hub.result_sub_object->visible_object;
						search_cockpit_main_rotor_hub.result_sub_object->relative_heading = search_main_rotor_hub.result_sub_object->relative_heading;
						search_main_rotor_hub.search_depth++;
						search_cockpit_main_rotor_hub.search_depth++;
					}

					// copy static hub

					search_main_rotor_hub.search_depth = search_cockpit_main_rotor_hub.search_depth = 0;
					search_main_rotor_hub.sub_object_index = search_cockpit_main_rotor_hub.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HUB_STATIC;

					while (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND &&
							find_object_3d_sub_object_from_sub_object (&search_cockpit_main_rotor_shaft, &search_cockpit_main_rotor_hub) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_cockpit_main_rotor_hub.result_sub_object->relative_heading = search_main_rotor_hub.result_sub_object->relative_heading;
						search_cockpit_main_rotor_hub.result_sub_object->visible_object = search_main_rotor_hub.result_sub_object->visible_object;
						search_main_rotor_hub.search_depth++;
						search_cockpit_main_rotor_hub.search_depth++;
					}
				}
			}
		}
		else
			break;

		search_main_rotor_shaft_depth++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_tail_rotor (entity *en)
{
	helicopter
		*raw = nullptr;

	object_3d_instance
		*inst3d = nullptr;

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

	raw = (helicopter *) get_local_entity_data (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME) || raw->tail_rotor_damaged || !get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return;
	}

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
		*raw = nullptr;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME) || !get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return;
	}

	//
	// only animate wipers on player's helicopter
	//

	if (en == get_gunship_entity ())
	{
		raw = (helicopter *) get_local_entity_data (en);

		switch (raw->ac.object_3d_shape)
		{
		case OBJECT_3D_AH64D_APACHE_LONGBOW:
		{
			animate_apache_external_wipers (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_MI28N_HAVOC:
		{
			animate_havoc_external_wipers (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_KA_52:
		{
			animate_hokum_wipers (raw->ac.inst3d);
			break;
		}
		////Moje 030602 Start
		case OBJECT_3D_UH60_BLACKHAWK:
		{
			animate_blackhawk_external_wipers (raw->ac.inst3d);
			break;
		}
		////Moje 030602 End
		////Moje 030619 Start
		case OBJECT_3D_MI24_HIND:
		{
			animate_hind_external_wipers (raw->ac.inst3d);
			break;
		}
		////Moje 030619 End
		////Moje 030816 Start
		case OBJECT_3D_AH_64A:
		{
			animate_ah64a_external_wipers (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_KA_50:
		{
			animate_ka50_wipers (raw->ac.inst3d);
			break;
		}
		////Moje 030619 End
		default:
		{
			animate_default_external_wipers(raw->ac.inst3d);
			break;
		}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_eo (entity *en)
{
	helicopter
		*raw = nullptr;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME) || !get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return;
	}

	//
	// only animate electro-optics on player's helicopter
	//

	if (en == get_gunship_entity ())
	{
		raw = (helicopter *) get_local_entity_data (en);

		switch (raw->ac.object_3d_shape)
		{
		case OBJECT_3D_AH64D_APACHE_LONGBOW:
		{
			animate_apache_eo (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_MI28N_HAVOC:
		{
			animate_havoc_eo (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_RAH66:
		{
			animate_comanche_eo (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_KA_52:
		{
			animate_hokum_eo (raw->ac.inst3d);
			break;
		}
		////Moje 030602 Start
		case OBJECT_3D_UH60_BLACKHAWK:
		{
			animate_blackhawk_eo (raw->ac.inst3d);
			break;
		}
		////Moje 030602 End
		////Moje 030619 Start
		case OBJECT_3D_MI24_HIND:
		{
			animate_hind_eo (raw->ac.inst3d);
			break;
		}
		////Moje 030619 End
		////Moje 030816 Start
		case OBJECT_3D_AH_64A:
		{
			animate_ah64a_eo (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_KA_50:
		{
			animate_ka50_eo (raw->ac.inst3d);
			break;
		}
		////Moje 030816 End
		case OBJECT_3D_AH1Z:
		{
			animate_viper_eo (raw->ac.inst3d);
			break;
		}
		case OBJECT_3D_OH58D:
		{
			animate_kiowa_eo (raw->ac.inst3d);
			break;
		}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_helicopter_wheels (entity *en)
{
	helicopter
		*raw = nullptr;

	ASSERT (en);
	ASSERT (en == get_gunship_entity());

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	//
	// only animate wheels rotation on player's helicopter
	//

	if (en == get_gunship_entity ())
	{
		raw = (helicopter *) get_local_entity_data (en);

		rotate_helicopter_wheels(raw->ac.inst3d);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_helicopter_3d_object (entity *en)
{
	helicopter
		*raw = nullptr;

	ASSERT (en);

	raw = (helicopter *) get_local_entity_data (en);

	damage_helicopter_main_rotors(en, -2);
	damage_helicopter_tail_rotors(en);

	set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_WEAPON, FALSE);
	set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_PILOT, FALSE);
	set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_AH64D_PILOT, FALSE);
	set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_MOVING, FALSE);
	set_sub_object_type_visible_status (raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_MOVING, FALSE);

	set_local_entity_int_value (en, INT_TYPE_TROOPS_ONBOARD, 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int damage_helicopter_main_rotors (entity *en, int blade_number)
{
	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_collision_point;

	int
		section_cut_off_point,
		search_main_rotor_shaft_depth,
		search_main_rotor_blade_root_static_depth,
		search_main_rotor_blade_section_static_depth;

	unsigned int subtype;

	float
		main_rotor_direction;

	helicopter
		*raw = nullptr;
	object_3d_instance
		*inst3d = nullptr;

	ASSERT (en);
	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return FALSE;

	raw = (helicopter *) get_local_entity_data (en);

	inst3d = raw->ac.inst3d;
	if (!inst3d)
		return FALSE;

	subtype = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	ASSERT (subtype < NUM_ENTITY_SUB_TYPE_AIRCRAFT);

	main_rotor_direction = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_DIRECTION);

	// locate rotor shaft

	search_main_rotor_shaft_depth = 0;

	while (search_main_rotor_shaft_depth < quantity_of_shafts[subtype])
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			// locate pitch and bank null

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				// locate heading null

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
						// locate static blade root by it's number, if it presents
					search_main_rotor_blade_root_static_depth = blade_number >= 0 ? (blade_number - search_main_rotor_shaft_depth * quantity_of_roots[subtype] / quantity_of_shafts[subtype]) : 0;

					while (search_main_rotor_blade_root_static_depth < quantity_of_roots[subtype] / quantity_of_shafts[subtype] && search_main_rotor_blade_root_static_depth >= 0)
					{
						search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
						search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							// count static blade sections

							search_main_rotor_blade_section_static_depth = 0;

							while (search_main_rotor_blade_section_static_depth < quantity_of_sections[subtype] / quantity_of_roots[subtype])
							{
								search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
								search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;
								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static))
								{
									if (search_main_rotor_blade_section_static.result_sub_object->visible_object)
									{
										search_main_rotor_blade_section_static_depth++;
									}
									else
										break;
								}
								else
									break;
							}

							// cut off static blade sections - last one, all of them or random

							if (search_main_rotor_blade_section_static_depth > 0)
							{
								float collision_point = 0;

								section_cut_off_point = blade_number >= 0 ? (search_main_rotor_blade_section_static_depth - 1) :
									(blade_number == -1 ? 0 : rand16() % search_main_rotor_blade_section_static_depth);

								#if DEBUG_MODULE
									debug_log("blade num %i, cut off %i, depth %i", blade_number, section_cut_off_point, search_main_rotor_blade_section_static_depth);
								#endif

								search_main_rotor_blade_section_static_depth = 0;

								while (search_main_rotor_blade_section_static_depth < quantity_of_sections[subtype] / quantity_of_roots[subtype])
								{
									viewpoint blade_vp;
									vec3d blade_direction;

									search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
									search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

									if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
									{
										if (search_main_rotor_blade_section_static.result_sub_object->visible_object)
										{
											if (search_main_rotor_blade_section_static_depth <= section_cut_off_point)
												collision_point += search_main_rotor_blade_section_static.result_sub_object->relative_position.z;

											if (search_main_rotor_blade_section_static_depth >= section_cut_off_point)
											{
												search_main_rotor_blade_section_static.result_sub_object->visible_object = FALSE;

												memcpy ( blade_vp.attitude, raw->ac.mob.attitude, sizeof ( matrix3x3 ) );
												blade_vp.position = raw->ac.mob.position;
												get_3d_sub_object_viewpoint(&search_main_rotor_blade_section_static, &blade_vp, TRUE);

												if (!bound_position_to_map_volume(&blade_vp.position))
												{
													create_rotor_blade_fragment(en, blade_vp, TRUE);

													if (en == get_gunship_entity())
													{
														current_flight_dynamics->main_rotor_rpm.value *= 0.99;

														blade_direction.x = main_rotor_direction;
														blade_direction.y = blade_direction.z = 0;
														multiply_matrix3x3_vec3d(&blade_direction, blade_vp.attitude, &blade_direction);
														add_dynamic_force ("Rotor blade damage", 0.000005 * current_flight_dynamics->main_rotor_rpm.value, 0, &blade_vp.position, &blade_direction, FALSE);
														#if DEBUG_MODULE
															create_vectored_debug_3d_object (&blade_vp.position, &blade_direction, OBJECT_3D_ARROW_FORCES, 10, 5.0);
														#endif
													}
												}
											}
										}
										else
											break;
									}
									else
										break;

									search_main_rotor_blade_section_static_depth++;
								}

								// move collision point

								search_main_rotor_collision_point.search_depth = 0;
								search_main_rotor_collision_point.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_COLLISION_POINT;

								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_collision_point) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
								{
									#if DEBUG_MODULE
										debug_log("moving blade collision point - old position %f, new position %f", search_main_rotor_collision_point.result_sub_object->relative_position.z, collision_point);
									#endif

									search_main_rotor_collision_point.result_sub_object->relative_position.z = collision_point;
								}
							}
						}
						else
							break;

						if (blade_number >= 0)
							break;
						else
							search_main_rotor_blade_root_static_depth++;
					}
				}
			}
		}
		else
			break;

		search_main_rotor_shaft_depth++;
		main_rotor_direction *= - 1;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_helicopter_tail_rotors (entity *en)
{
	helicopter
		*raw = nullptr;

	object_3d_instance
		*inst3d = nullptr;

	object_3d_sub_object_search_data
		search;

	int
		depth;

	viewpoint
		blade_vp;

	ASSERT (en);
	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return;

	raw = (helicopter *) get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	if (!inst3d)
		return;

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

			memcpy ( blade_vp.attitude, raw->ac.mob.attitude, sizeof ( matrix3x3 ) );
			blade_vp.position = raw->ac.mob.position;
			get_3d_sub_object_viewpoint(&search, &blade_vp, TRUE);
			if (!bound_position_to_map_volume(&blade_vp.position))
				create_rotor_blade_fragment(en, blade_vp, FALSE);
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

void create_rotor_blade_fragment (entity *en, viewpoint blade_vp, int main_rotor)
{
	object_3d_index_numbers blade_object;

	ASSERT (en);
	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);
	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return;

	if (main_rotor)
		switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
		{
			case ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION:
				blade_object = OBJECT_3D_CH53_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
				blade_object = OBJECT_3D_MI28_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
				blade_object = OBJECT_3D_MI24_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP:
				blade_object = OBJECT_3D_MI17_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK:
				blade_object = OBJECT_3D_MI6_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
				blade_object = OBJECT_3D_RAH66_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT:
				blade_object = OBJECT_3D_CH3_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
				blade_object = OBJECT_3D_UH60_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR:
				blade_object = OBJECT_3D_OH58_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
				blade_object = OBJECT_3D_AH64D_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
				blade_object = OBJECT_3D_AH64A_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER:
				blade_object = OBJECT_3D_AH1Z_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
				blade_object = OBJECT_3D_KA29_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
				blade_object = OBJECT_3D_KA52_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
				blade_object = OBJECT_3D_KA50_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
				blade_object = OBJECT_3D_CH47_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
				blade_object = OBJECT_3D_CH46_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY:
				blade_object = OBJECT_3D_MV22_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
				blade_object = OBJECT_3D_AH1T_ROTOR_BLADE_DAMAGED;
				break;
			case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA:
				blade_object = OBJECT_3D_AH1W_ROTOR_BLADE_DAMAGED;
				break;
			default:
				blade_object = OBJECT_3D_ROTOR_BLADE_DAMAGED;
		}
	else
		blade_object = OBJECT_3D_ROTOR_BLADE_DAMAGED;

	if (get_comms_model () == COMMS_MODEL_SERVER)
		create_client_server_particle_entity
		(
			1,
			blade_vp,
			frand1() * 75.0,
			blade_object,
			sin(PI / 6)
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int restore_helicopter_main_rotors (entity *en)
{
	object_3d_sub_object_search_data
		search_main_rotor_shaft,
		search_main_rotor_pitch_bank_null,
		search_main_rotor_heading_null,
		search_main_rotor_blade_root_static,
		search_main_rotor_blade_section_static,
		search_main_rotor_collision_point;

	int
		search_main_rotor_shaft_depth,
		search_main_rotor_blade_root_static_depth,
		search_main_rotor_blade_section_static_depth;

	unsigned int subtype;

	float
		collision_point;

	helicopter
		*raw = nullptr;

	object_3d_instance
		*inst3d = nullptr;

	ASSERT (en);
	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);
	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return FALSE;

	raw = (helicopter *) get_local_entity_data (en);
	inst3d = raw->ac.inst3d;
	if (!inst3d)
		return FALSE;

	subtype = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
	ASSERT (subtype < NUM_ENTITY_SUB_TYPE_AIRCRAFT);

	//
	// locate rotor shaft
	//

	search_main_rotor_shaft_depth = 0;

	while (search_main_rotor_shaft_depth < quantity_of_shafts[subtype])
	{
		search_main_rotor_shaft.search_depth = search_main_rotor_shaft_depth;
		search_main_rotor_shaft.search_object = inst3d;
		search_main_rotor_shaft.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT;

		if (find_object_3d_sub_object (&search_main_rotor_shaft) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			// locate pitch and bank null

			search_main_rotor_pitch_bank_null.search_depth = 0;
			search_main_rotor_pitch_bank_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_PITCH_BANK_NULL;

			if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_shaft, &search_main_rotor_pitch_bank_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				// locate heading null

				search_main_rotor_heading_null.search_depth = 0;
				search_main_rotor_heading_null.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_HEADING_NULL;

				if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_pitch_bank_null, &search_main_rotor_heading_null) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					// locate static blade roots

					search_main_rotor_blade_root_static_depth = 0;

					while (search_main_rotor_blade_root_static_depth < quantity_of_roots[subtype] / quantity_of_shafts[subtype])
					{
						search_main_rotor_blade_root_static.search_depth = search_main_rotor_blade_root_static_depth;
						search_main_rotor_blade_root_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_heading_null, &search_main_rotor_blade_root_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							// repair static blade sections

							search_main_rotor_blade_section_static_depth = 0;

							while (search_main_rotor_blade_section_static_depth < quantity_of_sections[subtype] / quantity_of_roots[subtype])
							{
								search_main_rotor_blade_section_static.search_depth = search_main_rotor_blade_section_static_depth;
								search_main_rotor_blade_section_static.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_SECTION_STATIC;

								if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_blade_section_static) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
									search_main_rotor_blade_section_static.result_sub_object->visible_object = TRUE;
								else
									break;

								search_main_rotor_blade_section_static_depth++;
							}
						}
						else
							break;

						// move collision point

						search_main_rotor_collision_point.search_depth = 0;
						search_main_rotor_collision_point.sub_object_index = OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_COLLISION_POINT;

						if (find_object_3d_sub_object_from_sub_object (&search_main_rotor_blade_root_static, &search_main_rotor_collision_point) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							collision_point = - aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].main_rotor_radius + get_3d_vector_magnitude((vec3d *) &search_main_rotor_blade_root_static.result_sub_object->relative_position);

							#if DEBUG_MODULE
								debug_log("restoring blade collision point - old position %f, new position %f", search_main_rotor_collision_point.result_sub_object->relative_position.z, collision_point);
							#endif

							search_main_rotor_collision_point.result_sub_object->relative_position.z = collision_point;
						}

						search_main_rotor_blade_root_static_depth++;
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

	raw->main_rotor_damaged = FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int restore_helicopter_tail_rotors (entity *en)
{
	helicopter
		*raw = nullptr;

	object_3d_instance
		*inst3d = nullptr;

	object_3d_sub_object_search_data
		search;

	int
		depth;

	ASSERT (en);
	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);
	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return FALSE;

	raw = (helicopter *) get_local_entity_data (en);
	if (!raw->tail_rotor_damaged)
		return FALSE;
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


	raw->tail_rotor_damaged = FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_helicopter_main_rotors_blurred (entity *en)
{
	float
		main_rotor_rpm;
	int
		ejected;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE) == FALSE)
	{
		return FALSE;
	}
	else
	{
		main_rotor_rpm = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);
		ejected = get_local_entity_int_value (en, INT_TYPE_EJECTED);
		return ((main_rotor_rpm >= 50) * !ejected);
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
		*raw = nullptr;

	ASSERT (en);

	raw = (helicopter *) get_local_entity_data (en);

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
