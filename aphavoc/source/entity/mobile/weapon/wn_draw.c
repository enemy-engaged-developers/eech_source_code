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
	weapon
		*raw;

	object_3d_instance
		*inst3d;

	raw = get_local_entity_data (en);

	if (!raw->mob.alive)
	{
		return;
	}

	//
	// do not draw if kill_next_update as the weapon will appear frozen for one frame
	//

	if (raw->mob.kill_next_update)
	{
		return;
	}

	switch (weapon_database[raw->mob.sub_type].default_3d_shape)
	{
		////////////////////////////////////////
		case OBJECT_3D_INVALID_OBJECT_INDEX:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_CANNON_SHELL:
		case OBJECT_3D_CANNON_SHELL_BLUE:
		case OBJECT_3D_CANNON_SHELL_GREEN:
		case OBJECT_3D_CANNON_SHELL_ORANGE:
		case OBJECT_3D_CANNON_SHELL_PURPLE:
		case OBJECT_3D_CANNON_SHELL_RED:
		case OBJECT_3D_CANNON_SHELL_WHITE:
		////////////////////////////////////////
		{
			float
				heading,
				pitch,
				roll;

			inst3d = construct_temporary_3d_object (weapon_database[raw->mob.sub_type].default_3d_shape, FALSE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				//
				// scale tracer wrt velocity and frame rate
				//

				inst3d->relative_scale.x = 100.0;
				inst3d->relative_scale.y = 100.0;
				inst3d->relative_scale.z = raw->mob.velocity * get_delta_time () * 0.75;

				//
				// roll for visual effect
				//

				heading = get_heading_from_attitude_matrix (raw->mob.attitude);

				pitch = get_pitch_from_attitude_matrix (raw->mob.attitude);

				roll = sfrand1 () * PI;

				get_3d_transformation_matrix (inst3d->vp.attitude, heading, pitch, roll);

				//
				// draw
				//

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_ARTILLERY_SHELL:
		////////////////////////////////////////
		{
			inst3d = construct_temporary_3d_object (weapon_database[raw->mob.sub_type].default_3d_shape, FALSE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				memcpy (inst3d->vp.attitude, raw->mob.attitude, sizeof (matrix3x3));

				inst3d->relative_scale.x = 10.0;
				inst3d->relative_scale.y = 10.0;
				inst3d->relative_scale.z = 10.0;

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_EFFECT_CHAFF_1:
		////////////////////////////////////////
		{
			int
				seed;

			object_3d_index_numbers
				chaff_index;

			float
				heading,
				pitch,
				roll,
				cruise_time_error,
				total_cruise_time,
				lifetime_ratio,
				scale;

			seed = get_client_server_entity_random_number_seed (en);

			cruise_time_error = frand1x (&seed) * weapon_database[raw->mob.sub_type].cruise_time_max_error;

			total_cruise_time = weapon_database[raw->mob.sub_type].cruise_time + cruise_time_error;

			lifetime_ratio = -raw->weapon_lifetime / total_cruise_time;

			if (lifetime_ratio < 0.7)
			{
				chaff_index = OBJECT_3D_EFFECT_CHAFF_1;
			}
			else if (lifetime_ratio < 0.8)
			{
				chaff_index = OBJECT_3D_EFFECT_CHAFF_2;
			}
			else if (lifetime_ratio < 0.9)
			{
				chaff_index = OBJECT_3D_EFFECT_CHAFF_3;
			}
			else
			{
				chaff_index = OBJECT_3D_EFFECT_CHAFF_4;
			}

			inst3d = construct_temporary_3d_object (chaff_index, FALSE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				//
				// scale wrt lifetime
				//

				scale = (lifetime_ratio * 20.0) + 1.0;

				inst3d->relative_scale.x = scale;
				inst3d->relative_scale.y = scale;
				inst3d->relative_scale.z = scale;

				//
				// tumble
				//

				heading = 0.0;

				pitch = lifetime_ratio * rad (360.0);

				roll = lifetime_ratio * rad (360.0);

				if (sfrand1x (&seed) < 0.0)
				{
					roll = -roll;
				}

				get_3d_transformation_matrix (inst3d->vp.attitude, heading, pitch, roll);

				//
				// draw
				//

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_KA52_ROTOR_WEAPON:
		////////////////////////////////////////
		{
			int
				seed;

			float
				heading,
				pitch,
				roll,
				rate,
				theta;

			seed = get_client_server_entity_random_number_seed (en);

			rate = (frand1x (&seed) * 0.25) + 0.25;

			theta = (frand1x (&seed) + (raw->weapon_lifetime * -rate)) * rad (360.0);

			inst3d = construct_temporary_3d_object (weapon_database[raw->mob.sub_type].default_3d_shape, FALSE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				//
				// tumble
				//

				if (sfrand1x (&seed) < 0.0)
				{
					heading = theta;
					pitch = 0.0;
					roll = -theta;
				}
				else
				{
					heading = -theta;
					pitch = 0.0;
					roll = theta;
				}

				get_3d_transformation_matrix (inst3d->vp.attitude, heading, pitch, roll);

				//
				// draw
				//

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_KA52_DOOR_LHS_WEAPON:
		case OBJECT_3D_KA52_DOOR_RHS_WEAPON:
		////////////////////////////////////////
		{
			int
				seed;

			float
				heading,
				pitch,
				roll,
				rate,
				theta;

			seed = get_client_server_entity_random_number_seed (en);

			rate = (frand1x (&seed) * 0.25) + 0.25;

			theta = (frand1x (&seed) + (raw->weapon_lifetime * -rate)) * rad (360.0);

			inst3d = construct_temporary_3d_object (weapon_database[raw->mob.sub_type].default_3d_shape, FALSE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				//
				// tumble
				//

				if (sfrand1x (&seed) < 0.0)
				{
					heading = 0.0;
					pitch = theta;
					roll = -theta;
				}
				else
				{
					heading = 0.0;
					pitch = -theta;
					roll = theta;
				}

				get_3d_transformation_matrix (inst3d->vp.attitude, heading, pitch, roll);

				//
				// draw
				//

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_KA52_PILOT_SEAT_WEAPON:
		case OBJECT_3D_KA52_WSO_SEAT_WEAPON:
		////////////////////////////////////////
		{
			int
				rocket_seat,
				parachute1,
				parachute2,
				parachute3,
				ejected_pilot;

			float
				heading,
				pitch,
				roll,
				lifetime;

			object_3d_sub_object_search_data
				search;

			inst3d = construct_temporary_3d_object (weapon_database[raw->mob.sub_type].default_3d_shape, TRUE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				//
				// animate
				//

				rocket_seat = FALSE;
				parachute1 = FALSE;
				parachute2 = FALSE;
				parachute3 = FALSE;
				ejected_pilot = FALSE;

				heading = get_heading_from_attitude_matrix (raw->mob.attitude);

				pitch = get_pitch_from_attitude_matrix (raw->mob.attitude);

				roll = 0.0;

				lifetime = -raw->weapon_lifetime;

				switch (raw->parachute_status)
				{
					case PARACHUTE_STATUS_CLOSED:
					{
						float
							pitch_ratio,
							delta_pitch;

						pitch_ratio = min (lifetime, 3.0) * (1.0 / 3.0);

						delta_pitch = rad (90.0) - pitch;

						pitch += delta_pitch * pitch_ratio;

						rocket_seat = TRUE;

						break;
					}
					case PARACHUTE_STATUS_OPEN1:
					{
						pitch = rad (90.0);

						parachute1 = TRUE;

						ejected_pilot = TRUE;

						break;
					}
					case PARACHUTE_STATUS_OPEN2:
					{
						pitch = rad (90.0);

						parachute2 = TRUE;

						ejected_pilot = TRUE;

						break;
					}
					case PARACHUTE_STATUS_OPEN3:
					{
						float
							t;

						//
						// rock & roll
						//

						t = fmod (lifetime, 7.0) * PI2 / 7.0;

						pitch = rad (90.0) + (sin (t) * rad (6.0));

						t = fmod (lifetime, 5.0) * PI2 / 5.0;

						heading += sin (t) * rad (10.0);

						parachute3 = TRUE;

						ejected_pilot = TRUE;

						break;
					}
					default:
					{
						debug_fatal ("Invalid parachute status = %d", raw->parachute_status);

						break;
					}
				}

				get_3d_transformation_matrix (inst3d->vp.attitude, heading, pitch, roll);

				//
				// draw
				//

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_ROCKET_SEAT;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = rocket_seat;
				}

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_PARACHUTE_01;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = parachute1;
				}

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_PARACHUTE_02;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = parachute2;
				}

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_PARACHUTE_03;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = parachute3;
				}

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_PILOT_EJECTED;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = ejected_pilot;

					//
					// animate
					//

					{
						float
							anim_frame;

						switch (weapon_database[raw->mob.sub_type].default_3d_shape)
						{
							case OBJECT_3D_KA52_PILOT_SEAT_WEAPON:
							{
								anim_frame = fmod (lifetime, 6.0) / 6.0;

								anim_frame = bound (anim_frame, 0.0, 1.0);

								animate_entity_simple_keyframed_sub_objects (inst3d, OBJECT_3D_SUB_OBJECT_PILOT_LEG, anim_frame);

								animate_entity_simple_keyframed_sub_objects (inst3d, OBJECT_3D_SUB_OBJECT_PILOT_HEAD, anim_frame);

								break;
							}
							case OBJECT_3D_KA52_WSO_SEAT_WEAPON:
							{
								anim_frame = fmod (lifetime, 6.0) / 6.0;

								anim_frame = bound (anim_frame, 0.0, 1.0);

								animate_entity_simple_keyframed_sub_objects (inst3d, OBJECT_3D_SUB_OBJECT_WSO_LEG, anim_frame);

								animate_entity_simple_keyframed_sub_objects (inst3d, OBJECT_3D_SUB_OBJECT_WSO_HEAD, anim_frame);

								break;
							}
						}
					}
				}

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
		////////////////////////////////////////
		case OBJECT_3D_C130_CRATE_WEAPON:
		////////////////////////////////////////
		{
			int
				parachute1,
				parachute2,
				parachute3,
				parachute_collapsed;

			float
				heading,
				pitch,
				roll,
				lifetime;

			object_3d_sub_object_search_data
				search;

			inst3d = construct_temporary_3d_object (weapon_database[raw->mob.sub_type].default_3d_shape, TRUE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				//
				// animate
				//

				parachute1 = FALSE;
				parachute2 = FALSE;
				parachute3 = FALSE;
				parachute_collapsed = FALSE;

				heading = get_heading_from_attitude_matrix (raw->mob.attitude);

				pitch = get_pitch_from_attitude_matrix (raw->mob.attitude);

				roll = 0.0;

				lifetime = -raw->weapon_lifetime;

				switch (raw->parachute_status)
				{
					case PARACHUTE_STATUS_CLOSED:
					{
						pitch = rad (90.0);

						break;
					}
					case PARACHUTE_STATUS_OPEN1:
					{
						pitch = rad (90.0);

						parachute1 = TRUE;

						break;
					}
					case PARACHUTE_STATUS_OPEN2:
					{
						pitch = rad (90.0);

						parachute2 = TRUE;

						break;
					}
					case PARACHUTE_STATUS_OPEN3:
					{
						float
							t;

						//
						// rock & roll
						//

						t = fmod (lifetime, 7.0) * PI2 / 7.0;

						pitch = rad (90.0) + (sin (t) * rad (6.0));

						t = fmod (lifetime, 5.0) * PI2 / 5.0;

						heading += sin (t) * rad (10.0);

						parachute3 = TRUE;

						break;
					}
					case PARACHUTE_STATUS_COLLAPSED:
					{
						pitch = rad (90.0);

						parachute_collapsed = TRUE;

						break;
					}
					default:
					{
						debug_fatal ("Invalid parachute status = %d", raw->parachute_status);

						break;
					}
				}

				get_3d_transformation_matrix (inst3d->vp.attitude, heading, pitch, roll);

				//
				// draw
				//

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_CRATE_PARACHUTE_01;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = parachute1;
				}

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_CRATE_PARACHUTE_02;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = parachute2;
				}

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_CRATE_PARACHUTE_03;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = parachute3;
				}

				search.search_depth = 0;
				search.search_object = inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_CRATE_PARACHUTE_04;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->visible_object = parachute_collapsed;
				}

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			inst3d = construct_temporary_3d_object (weapon_database[raw->mob.sub_type].default_3d_shape, FALSE);

			if (inst3d)
			{
				inst3d->vp.position = raw->mob.position;

				memcpy (inst3d->vp.attitude, raw->mob.attitude, sizeof (matrix3x3));

				inst3d->object_has_shadow = FALSE;

				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
static void draw_local_2d_symbol (entity *en)
{
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_weapon_draw_functions (void)
{
	fn_draw_local_entity_3d_object[ENTITY_TYPE_WEAPON]	= draw_local_3d_object;

	//fn_draw_local_entity_2d_symbol[ENTITY_TYPE_WEAPON]	= draw_local_2d_symbol;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_weapon_entity_parachute_open (entity *en)
{
	weapon
		*raw;

	ASSERT (en);

	ASSERT (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_WEAPON));

	raw = get_local_entity_data (en);

	if (raw->parachute_status == PARACHUTE_STATUS_OPEN3)
	{
		if (raw->weapon_lifetime < -1.0)
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_weapon_ejector_seat_animation (weapon *raw)
{
	float
		lifetime;

	ASSERT (raw);

	lifetime = -raw->weapon_lifetime;

	switch (raw->parachute_status)
	{
		////////////////////////////////////////
		case PARACHUTE_STATUS_CLOSED:
		////////////////////////////////////////
		{
			if ((lifetime > 3.0) && (raw->mob.motion_vector.y < 0.0))
			{
				raw->parachute_status = PARACHUTE_STATUS_OPEN1;

				raw->weapon_lifetime = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case PARACHUTE_STATUS_OPEN1:
		////////////////////////////////////////
		{
			if (lifetime > 0.1)
			{
				raw->parachute_status = PARACHUTE_STATUS_OPEN2;

				raw->weapon_lifetime = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case PARACHUTE_STATUS_OPEN2:
		////////////////////////////////////////
		{
			if (lifetime > 0.1)
			{
				raw->parachute_status = PARACHUTE_STATUS_OPEN3;

				raw->weapon_lifetime = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case PARACHUTE_STATUS_OPEN3:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid parachute status = %d", raw->parachute_status);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_weapon_crate_animation (weapon *raw)
{
	float
		lifetime;

	ASSERT (raw);

	lifetime = -raw->weapon_lifetime;

	if (raw->weapon_on_ground)
	{
		raw->parachute_status = PARACHUTE_STATUS_COLLAPSED;
	}

	switch (raw->parachute_status)
	{
		////////////////////////////////////////
		case PARACHUTE_STATUS_CLOSED:
		////////////////////////////////////////
		{
			if ((lifetime > 0.5) && (raw->mob.motion_vector.y < 0.0))
			{
				raw->parachute_status = PARACHUTE_STATUS_OPEN1;

				raw->weapon_lifetime = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case PARACHUTE_STATUS_OPEN1:
		////////////////////////////////////////
		{
			if (lifetime > 0.1)
			{
				raw->parachute_status = PARACHUTE_STATUS_OPEN2;

				raw->weapon_lifetime = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case PARACHUTE_STATUS_OPEN2:
		////////////////////////////////////////
		{
			if (lifetime > 0.1)
			{
				raw->parachute_status = PARACHUTE_STATUS_OPEN3;

				raw->weapon_lifetime = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case PARACHUTE_STATUS_OPEN3:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PARACHUTE_STATUS_COLLAPSED:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid parachute status = %d", raw->parachute_status);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
