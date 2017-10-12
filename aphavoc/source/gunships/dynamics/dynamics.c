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

#include "common/co_undercarriage.h"

#include "ah64a/ah_dyn.h"
#include "apache/ap_dyn.h"
#include "blackhawk/bh_dyn.h"
#include "comanche/cm_dyn.h"
#include "havoc/ha_dyn.h"
#include "hokum/ho_dyn.h"
#include "hind/hi_dyn.h"
#include "ka50/hm_dyn.h"
#include "viper/vi_dyn.h"
#include "kiowa/ki_dyn.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MIN_AUTOPILOT_HEIGHT 5.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity
	*current_flight_dynamics_landed_at_keysite;

dynamics_type
	*current_flight_dynamics;

int
	flight_dynamics_lock_position_flag;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*dynamics_options_type_names [] =
	{

		"CROSS_COUPLING",
		"DAMAGE",
		"DRAW_FLIGHT_PATH",
		"GROUND_COLLISIONS",
		"GROUND_EFFECT",
		"KEYBOARD_ASSISTANCE",
		"OBJECT_COLLISIONS",
		"OVER_TORQUE",
		"RETREATING_BLADE_STALL",
		"REVERSE_THROTTLE_INPUT",
		"TRANSITIONAL_LIFT",
		"VORTEX_RING",
		"WIND",
		"NUM_DYNAMICS_OPTIONS_TYPES"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*flight_path_action_names [] =
	{

		"ACTION_USER_NAVIGATING",
		"ACTION_AUTOPILOT_NAVIGATING",
		"ACTION_LAUNCH_WEAPON",
		"ACTION_HIT",
		"ACTION_DESTROYED",
		"ACTION_LANDED",
		"NUM_FLIGHT_PATH_ACTION_TYPES"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_DYNAMICS

float
	delta_heading_per_sec,
	delta_pitch_per_sec,
	delta_roll_per_sec;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_flight_dynamics_input_devices (void);

static void update_gunship_dynamics (void);

static void update_vector_flight_model (void);

/*static*/ void flight_dynamics_lock_position (void);

static void update_flight_path (void);

static int valid_dynamics_autos_on (dynamics_hover_hold_types type);

static void flight_dynamics_start_engine (int engine_number);
static void flight_dynamics_throttle_engine (int engine_number, int rpm_delta);
static void flight_dynamics_start_apu (void);
static void update_throttle_dynamics_inputs ();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_flight_dynamics (entity *en)
{

	ASSERT (en);

	#if DEBUG_DYNAMICS

	debug_log ("DYNAMICS: initialising flight model");

	#endif

	if (get_current_flight_dynamics ())
	{

		deinitialise_flight_dynamics ();
	}

	flight_dynamics_lock_position_flag = FALSE;

	if (get_global_dynamics_model () == DYNAMICS_MODEL_NONE)
	{

      set_global_dynamics_model (DEFAULT_DYNAMICS_MODEL);

	}

	//
	//
	//

	initialise_common_dynamics();

	switch (get_global_dynamics_model ())
	{

      case DYNAMICS_MODEL_ADVANCED:
      {

         switch (get_global_gunship_type ())
         {
			// JB 030313 Fly any aircraft
			default:
			case GUNSHIP_TYPE_APACHE:
            {
				if (command_line_dynamics_flight_model != 2)
					initialise_apache_advanced_dynamics (en);
				else
					initialise_advanced_dynamics (en);

				break;
            }

            case GUNSHIP_TYPE_COMANCHE:
            {

               initialise_comanche_advanced_dynamics (en);

               break;
            }

            case GUNSHIP_TYPE_HAVOC:
            {

               initialise_havoc_advanced_dynamics (en);

               break;
            }

            case GUNSHIP_TYPE_HOKUM:
            {

               initialise_hokum_advanced_dynamics (en);

               break;
            }
////Moje 030518 Start
            case GUNSHIP_TYPE_BLACKHAWK:
            {

               initialise_blackhawk_advanced_dynamics (en);

               break;
            }
////Moje 030518 End
////Moje 030612 Start
            case GUNSHIP_TYPE_HIND:
            {

               initialise_hind_advanced_dynamics (en);

               break;
            }
////Moje 020612 End
////Moje 030816 Start
            case GUNSHIP_TYPE_AH64A:
            {

               initialise_ah64a_advanced_dynamics (en);

               break;
            }

            case GUNSHIP_TYPE_KA50:
            {
               initialise_ka50_advanced_dynamics (en);

               break;
            }
////Moje 020816 End

            case GUNSHIP_TYPE_VIPER:
            {
               initialise_viper_advanced_dynamics (en);

               break;
            }

            case GUNSHIP_TYPE_KIOWA:
            {
               initialise_kiowa_advanced_dynamics (en);

               break;
            }
         }

         break;
      }
	}

	//
	//
	//

	load_dynamics_model (NULL);
	
	// safe check
	
	ASSERT(current_flight_dynamics->translational_lift.max >= current_flight_dynamics->translational_lift.min);
	ASSERT(current_flight_dynamics->translational_lift.modifier >= 0.009 && current_flight_dynamics->translational_lift.modifier <= 1.0);
		
	//
	//
	//

	set_dynamics_entity_values (en);

	//
	// Set model into 'Safe' state
	//

	if (en)
	{

		if (get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER) == 0.0)
		{

			// switch auto pilot on and clear the trim (manually - because helicopter may be below min height)

			set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT, TRUE);

			set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

			add_flight_path_action (current_flight_dynamics->position.x, current_flight_dynamics->position.z, FLIGHT_PATH_ACTION_AUTOPILOT_NAVIGATING);

			clear_trim_control (NULL);
		}
	}

	//
	//
	//

  	ASSERT (current_flight_dynamics);

	current_flight_dynamics->gunship = get_global_gunship_type ();

	push_event_overlay (set_flight_dynamics_events, "flight_dynamics");

	initialise_undercarriage_dynamics(en);

	initialise_dynamic_forces ();

	initialise_flight_dynamics_collision_points (FALSE);

	initialise_flight_dynamics_input_devices ();

	add_update_function (update_flight_path, 10.0, 0.0);

#if DEBUG_DYNAMICS

	debug_watch ("Model Simulation (per frame)	= %d", MT_INT, &current_flight_dynamics->model_iterations);
	debug_watch ("Model Simulation (per second)	= %d", MT_INT, &current_flight_dynamics->model_frame_rate);

	debug_watch ("model position x  				= %f", MT_DOUBLE, &current_flight_dynamics->position.x);
	debug_watch ("model position y  				= %f", MT_DOUBLE, &current_flight_dynamics->position.y);
	debug_watch ("model position z  				= %f", MT_DOUBLE, &current_flight_dynamics->position.z);

	debug_watch ("cyclic_x          					= %f", MT_FLOAT, &current_flight_dynamics->input_data.cyclic_x.value);
	debug_watch ("cyclic_y          					= %f", MT_FLOAT, &current_flight_dynamics->input_data.cyclic_y.value);
	debug_watch ("collective        					= %f", MT_FLOAT, &current_flight_dynamics->input_data.collective.value);
	debug_watch ("pedal             					= %f", MT_FLOAT, &current_flight_dynamics->input_data.pedal.value);

#endif

#if DEBUG_DYNAMICS >= 2

	debug_watch ("cyclic_input_pressure				= %f", MT_FLOAT, &current_flight_dynamics->input_data.cyclic_input_pressure);
	debug_watch ("cyclic_x_pressure    				= %f", MT_FLOAT, &current_flight_dynamics->input_data.cyclic_horizontal_pressure.value);
	debug_watch ("cyclic_y_pressure    				= %f", MT_FLOAT, &current_flight_dynamics->input_data.cyclic_vertical_pressure.value);
	debug_watch ("collective_input_pressure		= %f", MT_FLOAT, &current_flight_dynamics->input_data.collective_input_pressure);
	debug_watch ("collective_pressure				= %f", MT_FLOAT, &current_flight_dynamics->input_data.collective_pressure.value);
	debug_watch ("pedal_input_pressure				= %f", MT_FLOAT, &current_flight_dynamics->input_data.pedal_input_pressure);
	debug_watch ("pedal_pressure   					= %f", MT_FLOAT, &current_flight_dynamics->input_data.pedal_pressure.value);


	debug_watch ("apu_rpm   						= %f", MT_FLOAT, &current_flight_dynamics->apu_rpm.value);
	debug_watch ("apu_rpm max 						= %f", MT_FLOAT, &current_flight_dynamics->apu_rpm.max);

	debug_watch ("left N1 rpm   					= %f", MT_FLOAT, &current_flight_dynamics->left_engine_n1_rpm.value);
	debug_watch ("left min N1 rpm   				= %f", MT_FLOAT, &current_flight_dynamics->left_engine_n1_rpm.min);
	debug_watch ("left max N1 rpm   				= %f", MT_FLOAT, &current_flight_dynamics->left_engine_n1_rpm.max);
	debug_watch ("left N1 delta   					= %f", MT_FLOAT, &current_flight_dynamics->left_engine_n1_rpm.delta);
	debug_watch ("left N2 rpm   					= %f", MT_FLOAT, &current_flight_dynamics->left_engine_rpm.value);
	debug_watch ("left N2 delta   					= %f", MT_FLOAT, &current_flight_dynamics->left_engine_rpm.delta);
	debug_watch ("left max N2 rpm					= %f", MT_FLOAT, &current_flight_dynamics->left_engine_rpm.max);
	debug_watch ("left engine temp  				= %f", MT_FLOAT, &current_flight_dynamics->left_engine_temp.value);
	debug_watch ("left engine torque 				= %f", MT_FLOAT, &current_flight_dynamics->left_engine_torque.value);

	debug_watch ("right N1 rpm  					= %f", MT_FLOAT, &current_flight_dynamics->right_engine_n1_rpm.value);
	debug_watch ("right min N1 rpm   				= %f", MT_FLOAT, &current_flight_dynamics->right_engine_n1_rpm.min);
	debug_watch ("right max N1 rpm   				= %f", MT_FLOAT, &current_flight_dynamics->right_engine_n1_rpm.max);
	debug_watch ("right N1 delta   					= %f", MT_FLOAT, &current_flight_dynamics->right_engine_n1_rpm.delta);
	debug_watch ("right N2 rpm  					= %f", MT_FLOAT, &current_flight_dynamics->right_engine_rpm.value);
	debug_watch ("right N2 delta   					= %f", MT_FLOAT, &current_flight_dynamics->right_engine_rpm.delta);
	debug_watch ("right engine temp 				= %f", MT_FLOAT, &current_flight_dynamics->right_engine_temp.value);
	debug_watch ("right engine torque 				= %f", MT_FLOAT, &current_flight_dynamics->right_engine_torque.value);

	debug_watch ("vortex air flow				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_induced_vortex_air_flow.value);
	debug_watch ("main_rotor_induced			= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_induced_air.value);
	debug_watch ("main_blade_pitch  				= %f", MT_FLOAT, &current_flight_dynamics->main_blade_pitch.value);
	debug_watch ("main_rotor_roll   				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_roll_angle.value);
	debug_watch ("main_rotor_pitch  				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_pitch_angle.value);
	debug_watch ("main_rotor_thrust 				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_thrust.value);
	debug_watch ("main_rotor_rpm    				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_rpm.value);
	debug_watch ("main_rotor_rpm_delta 				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_rpm.delta);
	debug_watch ("main_rotor_rps    				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_rps.value);
	debug_watch ("main_rotor_angle  				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_angular_position.value);
	debug_watch ("main_rotor_inc	 				= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_angular_increment.value);
	debug_watch ("main_rotor_coning 			= %f", MT_FLOAT, &current_flight_dynamics->main_rotor_coning_angle.value);

	debug_watch ("tail_blade_pitch  				= %f", MT_FLOAT, &current_flight_dynamics->tail_blade_pitch.value);
	debug_watch ("tail_rotor_thrust 				= %f", MT_FLOAT, &current_flight_dynamics->tail_rotor_thrust.value);
	debug_watch ("tail_rotor_rpm    				= %f", MT_FLOAT, &current_flight_dynamics->tail_rotor_rpm.value);
	debug_watch ("main_rotor_rps    				= %f", MT_FLOAT, &current_flight_dynamics->tail_rotor_rps.value);
	debug_watch ("main_rotor_angle  				= %f", MT_FLOAT, &current_flight_dynamics->tail_rotor_angular_position.value);
	debug_watch ("crosscoupling eff 				= %f", MT_FLOAT, &current_flight_dynamics->cross_coupling_effect.value);

	debug_watch ("model_roll       				= %f", MT_FLOAT, &current_flight_dynamics->roll.value);
	debug_watch ("model_roll_delta 				= %f", MT_FLOAT, &current_flight_dynamics->roll.delta);
	debug_watch ("model_pitch      				= %f", MT_FLOAT, &current_flight_dynamics->pitch.value);
	debug_watch ("model_pitchdelta 			= %f", MT_FLOAT, &current_flight_dynamics->pitch.delta);
	debug_watch ("model_heading    			= %f", MT_FLOAT, &current_flight_dynamics->heading.value);
	debug_watch ("model_headingdelta 		= %f", MT_FLOAT, &current_flight_dynamics->heading.delta);
	debug_watch ("world velocity.z  			= %f", MT_FLOAT, &current_flight_dynamics->world_velocity_z.value);

	debug_watch ("Dheading / sec    				= %f", MT_FLOAT, &delta_heading_per_sec);
	debug_watch ("Dpitch / sec      				= %f", MT_FLOAT, &delta_pitch_per_sec);
	debug_watch ("Droll / sec :      					= %f", MT_FLOAT, &delta_roll_per_sec);

	debug_watch ("lift              						= %f", MT_FLOAT, &current_flight_dynamics->lift.value);
	debug_watch ("velocity.x        					= %f", MT_FLOAT, &current_flight_dynamics->velocity_x.value);
	debug_watch ("velocity.y        					= %f", MT_FLOAT, &current_flight_dynamics->velocity_y.value);
	debug_watch ("velocity.z        					= %f", MT_FLOAT, &current_flight_dynamics->velocity_z.value);
	debug_watch ("velocity.x drag   				= %f", MT_FLOAT, &current_flight_dynamics->drag_x.value);
	debug_watch ("velocity.y drag   				= %f", MT_FLOAT, &current_flight_dynamics->drag_y.value);
	debug_watch ("velocity.z drag   				= %f", MT_FLOAT, &current_flight_dynamics->drag_z.value);
	debug_watch ("velocity.x delta  				= %f", MT_FLOAT, &current_flight_dynamics->velocity_x.delta);
	debug_watch ("velocity.y delta  				= %f", MT_FLOAT, &current_flight_dynamics->velocity_y.delta);
	debug_watch ("velocity.z delta  				= %f", MT_FLOAT, &current_flight_dynamics->velocity_z.delta);
	debug_watch ("world velocity.x  				= %f", MT_FLOAT, &current_flight_dynamics->world_velocity_x.value);
	debug_watch ("world velocity.y	  				= %f", MT_FLOAT, &current_flight_dynamics->world_velocity_y.value);
	debug_watch ("world velocity.z  				= %f", MT_FLOAT, &current_flight_dynamics->world_velocity_z.value);
	debug_watch ("model acceleration.x  				= %f", MT_FLOAT, &current_flight_dynamics->model_acceleration_vector.x);
	debug_watch ("model acceleration.y	  				= %f", MT_FLOAT, &current_flight_dynamics->model_acceleration_vector.y);
	debug_watch ("model acceleration.z  				= %f", MT_FLOAT, &current_flight_dynamics->model_acceleration_vector.z);
	debug_watch ("world acceleration.x  				= %f", MT_FLOAT, &current_flight_dynamics->world_acceleration_vector.x);
	debug_watch ("world acceleration.y	  				= %f", MT_FLOAT, &current_flight_dynamics->world_acceleration_vector.y);
	debug_watch ("world acceleration.z  				= %f", MT_FLOAT, &current_flight_dynamics->world_acceleration_vector.z);

	debug_watch ("altitude   	   					= %f", MT_FLOAT, &current_flight_dynamics->altitude.value);
	debug_watch ("ground altitude   				= %f", MT_FLOAT, &current_flight_dynamics->altitude.min);
	debug_watch ("altitude_hold 						= %f", MT_FLOAT, &current_flight_dynamics->altitude.max);
	debug_watch ("radar altitude 						= %f", MT_FLOAT, &current_flight_dynamics->radar_altitude.value);
	debug_watch ("barometric altitude 				= %f", MT_FLOAT, &current_flight_dynamics->barometric_altitude.value);
	debug_watch ("air_density       					= %f", MT_FLOAT, &current_flight_dynamics->air_density.value);

	debug_watch ("power avaliable  		 		= %f", MT_FLOAT, &current_flight_dynamics->power_avaliable.value);
	debug_watch ("power required    				= %f", MT_FLOAT, &current_flight_dynamics->power_required.value);
	debug_watch ("power induced     				= %f", MT_FLOAT, &current_flight_dynamics->power_induced.value);
	debug_watch ("power profile     				= %f", MT_FLOAT, &current_flight_dynamics->power_profile.value);
	debug_watch ("power parasite    				= %f", MT_FLOAT, &current_flight_dynamics->power_parasite.value);
	debug_watch ("power surplus     				= %f", MT_FLOAT, &current_flight_dynamics->power_surplus.value);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_flight_dynamics_collision_points (int update_points_position)
{

	dynamics_collision_type
		*fixed_collision_points,
		*last_frame_fixed_collision_points,
		*moving_collision_points,
		*last_frame_moving_collision_points;

	int
		collision_type;

	object_3d_instance
		*temp_inst3d;

	object_3d_sub_object_search_data
		search;

	int
		depth,
			i;

	helicopter
		*raw;

	object_3d_sub_object_index_numbers
		sub_object_type;

	ASSERT (get_gunship_entity ());

	//
	//
	//

	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());

		temp_inst3d = raw->ac.inst3d;
		get_identity_matrix3x3(temp_inst3d->vp.attitude);

		temp_inst3d->vp.position.x = 0.0;
		temp_inst3d->vp.position.y = 0.0;
		temp_inst3d->vp.position.z = 0.0;

		current_flight_dynamics->number_of_fixed_collision_points = 0;
		current_flight_dynamics->number_of_moving_collision_points = 0;

		if (!update_points_position)
		{
			debug_log("%i blade roots, %i rotor shafts, %i tail blades found", count_sub_object_type_depth (temp_inst3d, OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_BLADE_ROOT_STATIC), 
					count_sub_object_type_depth (temp_inst3d, OBJECT_3D_SUB_OBJECT_MAIN_ROTOR_SHAFT), 
					count_sub_object_type_depth (temp_inst3d, OBJECT_3D_SUB_OBJECT_TAIL_ROTOR_STATIC));
		}

		for (collision_type = DYNAMICS_COLLISION_POINT_MAIN_ROTOR; collision_type < NUM_DYNAMICS_COLLISION_POINT_TYPES; collision_type ++)
		{

			if (!dynamics_collision_point_info [collision_type].moving)
			{

				//
				// Fixed
				//

				sub_object_type = dynamics_collision_point_info [collision_type].sub_object_type;

				depth = count_sub_object_type_depth (temp_inst3d, sub_object_type);

				if (depth > 0)
				{
					if (!update_points_position)
					{
						fixed_collision_points = (dynamics_collision_type *) malloc_heap_mem (sizeof (dynamics_collision_type) * (current_flight_dynamics->number_of_fixed_collision_points + depth));

						last_frame_fixed_collision_points = (dynamics_collision_type *) malloc_heap_mem (sizeof (dynamics_collision_type) * (current_flight_dynamics->number_of_fixed_collision_points + depth));

						if (current_flight_dynamics->fixed_collision_points)
						{

							memcpy (fixed_collision_points, current_flight_dynamics->fixed_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_fixed_collision_points);

							memcpy (last_frame_fixed_collision_points, current_flight_dynamics->last_frame_fixed_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_fixed_collision_points);

							free_mem (current_flight_dynamics->fixed_collision_points);

							free_mem (current_flight_dynamics->last_frame_fixed_collision_points);
						}

						current_flight_dynamics->fixed_collision_points = fixed_collision_points;

						current_flight_dynamics->last_frame_fixed_collision_points = last_frame_fixed_collision_points;

						current_flight_dynamics->valid_last_frame_fixed_collision_points = FALSE;
					}

					for (i = 0; i < depth; i++)
					{

						search.search_depth = i;
						search.search_object = temp_inst3d;
						search.sub_object_index = sub_object_type;

						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							viewpoint vp;
							int point_number = i + current_flight_dynamics->number_of_fixed_collision_points;

							get_3d_sub_object_world_viewpoint (&search, &vp);

							current_flight_dynamics->fixed_collision_points [point_number].model_point.x = vp.position.x;
							current_flight_dynamics->fixed_collision_points [point_number].model_point.y = vp.position.y;
							current_flight_dynamics->fixed_collision_points [point_number].model_point.z = vp.position.z;

							if (!update_points_position)
							{
								current_flight_dynamics->fixed_collision_points [point_number].collision_point_type = (dynamics_collision_point_types) collision_type;
								current_flight_dynamics->fixed_collision_points [point_number].terrain_elevation = 0.0;
								current_flight_dynamics->fixed_collision_points [point_number].violated = FALSE;

								debug_log ("DYNAMICS: Found fixed collision point %s (%d) at %f, %f, %f",
											dynamics_collision_point_info [current_flight_dynamics->fixed_collision_points [point_number].collision_point_type].name,
											point_number,
											current_flight_dynamics->fixed_collision_points [point_number].model_point.x,
											current_flight_dynamics->fixed_collision_points [point_number].model_point.y,
											current_flight_dynamics->fixed_collision_points [point_number].model_point.z);
							}

//						  we have separate modelling for the suspension, so don't let the collision points of the old fixed wheels get in the way. Raise them by 0.5 m
							if (collision_type == DYNAMICS_COLLISION_POINT_WHEEL)
								current_flight_dynamics->fixed_collision_points [point_number].model_point.y += 0.2 + 0.3 * !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT);

						}
					}

					current_flight_dynamics->number_of_fixed_collision_points += depth;

				}
				else if (!update_points_position)
				{
					debug_log ("DYNAMICS: WARNING: object %s with no %s collision points", entity_sub_type_aircraft_names [get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ENTITY_SUB_TYPE)], dynamics_collision_point_info [collision_type].name);
						// triggers for important points
					ASSERT(strcmp(dynamics_collision_point_info [collision_type].name, "DYNAMICS_COLLISION_POINT_ENGINE"));
					ASSERT(strcmp(dynamics_collision_point_info [collision_type].name, "DYNAMICS_COLLISION_POINT_MAIN_ROTOR"));
				}
			}
			else
			{

				//
				// Moving
				//

				sub_object_type = dynamics_collision_point_info [collision_type].sub_object_type;

				depth = count_sub_object_type_depth (temp_inst3d, sub_object_type);

				if (depth > 0)
				{

					if (!update_points_position)
					{
						moving_collision_points = (dynamics_collision_type *) malloc_heap_mem (sizeof (dynamics_collision_type) * (current_flight_dynamics->number_of_moving_collision_points + depth));

						last_frame_moving_collision_points = (dynamics_collision_type *) malloc_heap_mem (sizeof (dynamics_collision_type) * (current_flight_dynamics->number_of_moving_collision_points + depth));

						if (current_flight_dynamics->moving_collision_points)
						{

							memcpy (moving_collision_points, current_flight_dynamics->moving_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_moving_collision_points);

							memcpy (last_frame_moving_collision_points, current_flight_dynamics->last_frame_moving_collision_points, sizeof (dynamics_collision_type) * current_flight_dynamics->number_of_moving_collision_points);

							free_mem (current_flight_dynamics->moving_collision_points);

							free_mem (current_flight_dynamics->last_frame_moving_collision_points);
						}

						current_flight_dynamics->moving_collision_points = moving_collision_points;

						current_flight_dynamics->last_frame_moving_collision_points = last_frame_moving_collision_points;

						current_flight_dynamics->valid_last_frame_moving_collision_points = FALSE;
					}
					
					for (i = 0; i < depth; i++)
					{

						search.search_depth = i;
						search.search_object = temp_inst3d;
						search.sub_object_index = sub_object_type;

						if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{

							viewpoint
								vp;

							get_3d_sub_object_world_viewpoint (&search, &vp);

							current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].model_point.x = vp.position.x;
							current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].model_point.y = vp.position.y;
							current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].model_point.z = vp.position.z;

							if (!update_points_position)
							{
								current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].collision_point_type = (dynamics_collision_point_types) collision_type;
								current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].terrain_elevation = 0.0;
								current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].violated = FALSE;

								debug_log ("DYNAMICS: Found moving collision point %s (%d) at %f, %f, %f",
											dynamics_collision_point_info [current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].collision_point_type].name,
											i + current_flight_dynamics->number_of_moving_collision_points,
											current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].model_point.x,
											current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].model_point.y,
											current_flight_dynamics->moving_collision_points [i + current_flight_dynamics->number_of_moving_collision_points].model_point.z);
							}
						}
					}

					current_flight_dynamics->number_of_moving_collision_points += depth;
				}
				else if (!update_points_position)
				{
					debug_log ("DYNAMICS: WARNING: object %s with no %s collision points", entity_sub_type_aircraft_names [get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ENTITY_SUB_TYPE)], dynamics_collision_point_info [collision_type].name);
				}
			}
		}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_flight_dynamics_input_devices (void)
{
#if 0	// Retro 18Jul2004
	current_flight_dynamics->input_data.cyclic_joystick_device_index = global_options.joystick_device_index;
#else
	current_flight_dynamics->input_data.cyclic_joystick_device_index = command_line_cyclic_joystick_index;
#endif	// Retro 18Jul2004 end

	initialise_cyclic();
	initialise_collective();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_flight_dynamics (void)
{

	flight_path_data
		*destroy_flight_path,
		*flight_path;

	#if DEBUG_DYNAMICS

	debug_log ("DYNAMICS: Deinitialising flight dynamics");

	#endif

	if (current_flight_dynamics)
	{
		deinitialise_undercarriage_dynamics();

		deinitialise_dynamic_forces ();

		// free fixed collision points

		if (current_flight_dynamics->fixed_collision_points)
		{

			free_mem (current_flight_dynamics->fixed_collision_points);

			free_mem (current_flight_dynamics->last_frame_fixed_collision_points);

			current_flight_dynamics->valid_last_frame_fixed_collision_points = FALSE;

			current_flight_dynamics->fixed_collision_points = NULL;
		}

		// free moving collision points

		if (current_flight_dynamics->moving_collision_points)
		{

			free_mem (current_flight_dynamics->moving_collision_points);

			free_mem (current_flight_dynamics->last_frame_moving_collision_points);

			current_flight_dynamics->valid_last_frame_moving_collision_points = FALSE;

			current_flight_dynamics->moving_collision_points = NULL;
		}

		// free up flight path

		flight_path = current_flight_dynamics->flight_path;

		while (flight_path)
		{

			destroy_flight_path = flight_path;

			flight_path = flight_path->next;

			free_mem (destroy_flight_path);
		}

		//debug_log ("DYNAMICS: resetting flight path");

		current_flight_dynamics->flight_path = NULL;

		//

		current_flight_dynamics = NULL;

		pop_event (set_flight_dynamics_events);

		remove_update_function (update_flight_path);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_dynamics_entity_values (entity *en)
{

	entity
		*group;

	helicopter
		*raw;

	vec3d
		*pos,
		*motion_vector;

	float
		air_density;

	int
		no_right_engine;

	ASSERT (current_flight_dynamics);

	if (!en)
	{

		return;
	}

	raw = (helicopter *) get_local_entity_data (en);

	if (get_current_flight_dynamics_rotor_brake ())
	{

		set_current_flight_dynamics_rotor_brake (FALSE);
	}

	set_current_flight_dynamics_wheel_brake (TRUE);

	current_flight_dynamics->engine_idle_rpm = 60.0;
	current_flight_dynamics->main_rotor_governor_rpm = 100.0;
	current_flight_dynamics->main_rotor_idle_rpm = 70.0;
	current_flight_dynamics->main_rotor_max_rpm = 100.0;
	current_flight_dynamics->engine_start_timer = 0.0;

	no_right_engine = get_global_gunship_type() == GUNSHIP_TYPE_KIOWA;

	if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
	{
		current_flight_dynamics->main_rotor_governor_rpm = 97.5;
		current_flight_dynamics->main_rotor_max_rpm = 97.5;
		current_flight_dynamics->engine_idle_rpm = 72.0;
	}

	if ((!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT)) ||
		(get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM) == 0.0)) // engine off
	{

		// landed

		set_client_server_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDED);

		current_flight_dynamics->rotor_brake = TRUE;
		current_flight_dynamics->wheel_brake = TRUE;

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group)
		{

			current_flight_dynamics_landed_at_keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);
		}

		current_flight_dynamics->left_engine_torque.value = 0.0;
		current_flight_dynamics->right_engine_torque.value = 0.0;
		current_flight_dynamics->left_engine_torque.max = 120.0;
		current_flight_dynamics->right_engine_torque.max = no_right_engine ? 0.0 : 120.0;
		current_flight_dynamics->combined_engine_torque.value = 0.0;

		current_flight_dynamics->apu_rpm.value = 0.0;
		if (command_line_dynamics_engine_startup)
		{
			current_flight_dynamics->left_engine_n1_rpm.value = 0.0;
			current_flight_dynamics->right_engine_n1_rpm.value = 0.0;
			current_flight_dynamics->left_engine_n1_rpm.max = 0.0;
			current_flight_dynamics->right_engine_n1_rpm.max = 0.0;

			if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
				current_flight_dynamics->main_rotor_governor_rpm = 70.0;
		}
		else  // start with engines running
		{
			current_flight_dynamics->left_engine_n1_rpm.value = current_flight_dynamics->engine_idle_rpm;
			current_flight_dynamics->right_engine_n1_rpm.value = no_right_engine ? 0.0 : current_flight_dynamics->engine_idle_rpm;
			current_flight_dynamics->left_engine_n1_rpm.max = 110.0;
			current_flight_dynamics->right_engine_n1_rpm.max = no_right_engine ? 0.0 : 110.0;
		}

		current_flight_dynamics->left_engine_rpm.value = 0.0;
		current_flight_dynamics->right_engine_rpm.value = 0.0;
		current_flight_dynamics->left_engine_rpm.max = 100.0;
		current_flight_dynamics->right_engine_rpm.max = no_right_engine ? 0.0 : 100.0;
		current_flight_dynamics->main_rotor_rpm.value = 0.0;
		current_flight_dynamics->tail_rotor_rpm.value = 0.0;

		current_flight_dynamics->left_engine_temp.value = 35.0;
		current_flight_dynamics->right_engine_temp.value = no_right_engine ? 0.0 : 35.0;
		current_flight_dynamics->left_engine_temp.min = 100.0;
		current_flight_dynamics->right_engine_temp.min = no_right_engine ? 0.0 : 100.0;

		current_flight_dynamics->input_data.collective.value = 0.0;

		set_client_server_entity_int_value (en, INT_TYPE_AUTO_PILOT, FALSE);
	}
	else
	{

		// not landed

		current_flight_dynamics->left_engine_torque.value = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);
		current_flight_dynamics->right_engine_torque.value = no_right_engine ? 0.0 : get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);
		current_flight_dynamics->combined_engine_torque.value = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);
		current_flight_dynamics->left_engine_torque.max = 120.0;
		current_flight_dynamics->right_engine_torque.max = no_right_engine ? 0.0 : 120.0;

		current_flight_dynamics->apu_rpm.value = 0.0;  // APU only used during start up
		current_flight_dynamics->left_engine_rpm.value = 100.0;
		current_flight_dynamics->right_engine_rpm.value = no_right_engine ? 0.0 : 100.0;
		current_flight_dynamics->left_engine_rpm.max = 100.0;
		current_flight_dynamics->right_engine_rpm.max = no_right_engine ? 0.0 : 100.0;
		current_flight_dynamics->left_engine_n1_rpm.value = 80.0;
		current_flight_dynamics->right_engine_n1_rpm.value = no_right_engine ? 0.0 : 80.0;
		current_flight_dynamics->main_rotor_rpm.value = 100.0;
		current_flight_dynamics->tail_rotor_rpm.value = 100.0;

		current_flight_dynamics->input_data.collective.value = 0.0;

		current_flight_dynamics->left_engine_temp.value = 750.0;
		current_flight_dynamics->right_engine_temp.value = no_right_engine ? 0.0 : 750.0;
		current_flight_dynamics->left_engine_temp.min = 700.0;
		current_flight_dynamics->right_engine_temp.min = no_right_engine ? 0.0 : 700.0;

		if (get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM) != 0.0)
		{

			current_flight_dynamics->input_data.collective.value = max (50.0f, get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM));
		}
	}

	current_flight_dynamics->heading.value = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);
	current_flight_dynamics->pitch.value = get_local_entity_float_value (en, FLOAT_TYPE_PITCH);
	current_flight_dynamics->roll.value = get_local_entity_float_value (en, FLOAT_TYPE_ROLL);
	get_local_entity_attitude_matrix (en, current_flight_dynamics->attitude);

	motion_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);
	current_flight_dynamics->world_motion_vector = *motion_vector;

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	current_flight_dynamics->position.x = pos->x;
	current_flight_dynamics->position.y = pos->y;
	current_flight_dynamics->position.z = pos->z;

	current_flight_dynamics->world_velocity_y.value = current_flight_dynamics->world_motion_vector.y;

	current_flight_dynamics->velocity_z.value = get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY);

	air_density = get_air_density (current_flight_dynamics->altitude.value);
	current_flight_dynamics->indicated_airspeed.value = current_flight_dynamics->velocity_z.value * air_density;

	current_flight_dynamics->altitude.value = pos->y;
	current_flight_dynamics->altitude.min = get_3d_terrain_point_data_elevation (&raw->ac.terrain_info);

	current_flight_dynamics->barometric_altitude.value = pos->y - aircraft_database [current_flight_dynamics->sub_type].centre_of_gravity_to_ground_distance;
	current_flight_dynamics->radar_altitude.value = get_local_entity_float_value (en, FLOAT_TYPE_RADAR_ALTITUDE) - aircraft_database [current_flight_dynamics->sub_type].centre_of_gravity_to_ground_distance;

	//debug_log ("DYNAMICS: setting baro to %f, altitude %f", current_flight_dynamics->barometric_altitude.value, current_flight_dynamics->radar_altitude.value);

	// cross coupling to match main rotor rpm
	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
	{

		float
			Mrpm,
			Md,
			Pmax,
			Tl;

		Mrpm = current_flight_dynamics->main_rotor_rpm.value;

		Md = current_flight_dynamics->main_rotor_diameter.value;

		Pmax = current_flight_dynamics->tail_blade_pitch.max;

		Tl = current_flight_dynamics->tail_boom_length.value;

		current_flight_dynamics->cross_coupling_effect.value = (((200 * PI * Mrpm * Md * Pmax) / (1649 * Tl))) / (Pmax);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_helicopter_damage ()
{
	float damage_percentage;
	int invulunerable_flag = get_local_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS);
	
	set_client_server_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS, FALSE);
	
	damage_percentage = (float) get_local_entity_int_value (get_gunship_entity (), INT_TYPE_DAMAGE_LEVEL) / (float) get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INITIAL_DAMAGE_LEVEL);

	debug_log("DYNAMICS: damage_percentage is %.2f", damage_percentage);

	if (damage_percentage > 0.8)
	{

		dynamics_damage_model (DYNAMICS_DAMAGE_NONE, FALSE);
	}
	else if (damage_percentage > 0.7)
	{

		dynamics_damage_model (DYNAMICS_DAMAGE_LEFT_ENGINE, FALSE);
	}
	else if (damage_percentage > 0.4)
	{

		dynamics_damage_model (DYNAMICS_DAMAGE_RIGHT_ENGINE, FALSE);
	}
	else if (damage_percentage > 0.3)
	{

		dynamics_damage_model (DYNAMICS_DAMAGE_LOW_HYDRAULICS, FALSE);
	}
	else if (damage_percentage > 0.2)
	{

		dynamics_damage_model (DYNAMICS_DAMAGE_STABILISER, FALSE);
	}
	else
	{

		dynamics_damage_model (DYNAMICS_DAMAGE_STABILISER, TRUE);
	}

//	already happens in initialise_avionics finction /thealx/
//	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_HELICOPTER_DAMAGE_FLAGS))
//	{
//
//		dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);
//	}
	
	 set_client_server_entity_int_value (get_session_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS, invulunerable_flag);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_flight_dynamics (void)
{

	//////////////////////////////////////////////////////////////////
	// ASSERT THAT USER HAS A TASK IF HE IS FLYING AROUND
	//////////////////////////////////////////////////////////////////

	#ifdef DEBUG
	/*
	if (get_comms_model () == COMMS_MODEL_SERVER)
	{

		if (get_game_type () == GAME_TYPE_CAMPAIGN)
		{

			entity
				*task;

			task = get_local_entity_primary_task (get_gunship_entity ());

			if (!task)
			{
				task = get_local_entity_current_task (get_gunship_entity ());
			}

			ASSERT (task);
		}
	}
	*/
	#endif

	//////////////////////////////////////////////////////////////////

	/// ForceFeedback by thealx 130224 ///////////////////////////////
	
	if (command_line_forcefeedback && feedback_device)
	{
	    int state = get_local_entity_undercarriage_state (get_gunship_entity ());
		vec3d pilot_forces;
		
		pilot_forces.x = pilot_forces.y = pilot_forces.z = 0;
		
		if (command_line_ffb_dynamics > 0 || command_line_ffb_vibrations > 0)
		{
			get_forces_acting_on_pilot(&pilot_forces.x, &pilot_forces.y, &pilot_forces.z, TRUE, FALSE);
			xforce += pilot_forces.x * 1000000;
			yforce += pilot_forces.z * 1000000;
		}
		
		if (command_line_ffb_dynamics > 0)
		{
			xforce += command_line_ffb_dynamics * sin (current_flight_dynamics->angular_roll_velocity.value) * 10000;
			yforce += command_line_ffb_dynamics * sin (current_flight_dynamics->angular_pitch_velocity.value) * 10000;
		}
		
	    // Gears events
	    
	    if (command_line_ffb_vibrations > 0 && (state == AIRCRAFT_UNDERCARRIAGE_LOWERING || state == AIRCRAFT_UNDERCARRIAGE_RAISING))
	    {
		    xfreq += command_line_ffb_vibrations * sfrand1();
		    xampl += command_line_ffb_vibrations * sfrand1() / 4;
		    yfreq += command_line_ffb_vibrations * sfrand1();
		    yampl += command_line_ffb_vibrations * sfrand1() / 4;
	    }

	    // main function
	    
	    set_joystick_force_feedback_forces();
	}
	//////////////////////////////////////////////////////////////////

	if ((get_comms_model () == COMMS_MODEL_CLIENT) && (!current_flight_dynamics))
	{

		//
		// Client probably waiting for server to set its old entity to AI
		//

		return;
	}

	ASSERT (current_flight_dynamics);

	//
	//
	//

	if ((!current_flight_dynamics->model_paused) && (!flight_dynamics_lock_position_flag))
	{

		update_cyclic_pressure_inputs ();

		update_collective_pressure_inputs ();

		update_pedal_pressure_inputs ();

		update_throttle_dynamics_inputs ();

		if (session_vector_flight_model) // Jabberwock - session settings
		{

			update_vector_flight_model ();
		}
		else
		{

			update_gunship_dynamics ();
		}
	}

	if (get_gunship_entity () && get_local_entity_int_value (get_gunship_entity(), INT_TYPE_ALIVE))
	{
		update_dynamics_at_keysite ();

		update_dynamics_damage ();

		if (!get_local_entity_int_value (get_gunship_entity(), INT_TYPE_ALIVE) || !current_flight_dynamics)
			return;

		current_flight_dynamics->velocity_z.value = bound (current_flight_dynamics->velocity_z.value, knots (-100), knots (200));

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
			current_flight_dynamics->g_force.value = 1.0 + current_flight_dynamics->model_acceleration_vector.y / G;
		else
			current_flight_dynamics->g_force.value = 1.0;

		// TODO: don't do this unconditionally
		set_local_entity_int_value(get_gunship_entity(), INT_TYPE_MOVED, TRUE);
		set_local_entity_int_value(get_gunship_entity(), INT_TYPE_ROTATED, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_gunship_dynamics (void)
{

	helicopter
		*raw;

	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());
	ASSERT(raw);
	if (!raw)
		return;

	current_flight_dynamics->model_iterations = (int) (get_delta_time () * MODEL_FRAME_RATE + 1.0);

	set_model_delta_time (get_delta_time () / current_flight_dynamics->model_iterations);

	switch (get_global_gunship_type ())
	{
		// JB 030313 Fly any aircraft
		default:
		case GUNSHIP_TYPE_APACHE:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_apache_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
		case GUNSHIP_TYPE_HAVOC:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_havoc_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
		case GUNSHIP_TYPE_COMANCHE:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_comanche_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
		case GUNSHIP_TYPE_HOKUM:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_hokum_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
////Moje 030518 Start

		case GUNSHIP_TYPE_BLACKHAWK:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_blackhawk_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}

////Moje 030518 End
////Moje 030612 Start
		case GUNSHIP_TYPE_HIND:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_hind_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
////Moje 030612 End
////Moje 030816 Start

		case GUNSHIP_TYPE_AH64A:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_ah64a_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
		case GUNSHIP_TYPE_KA50:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_ka50_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
////Moje 030816 End

		case GUNSHIP_TYPE_VIPER:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_viper_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}

		case GUNSHIP_TYPE_KIOWA:
		{
			while (current_flight_dynamics->model_iterations --)
			{
				get_3d_terrain_point_data (current_flight_dynamics->position.x, current_flight_dynamics->position.z, &raw->ac.terrain_info);

				update_kiowa_advanced_dynamics ();
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
				update_collision_dynamics ();
				// may get killed, so abort further calculations if so
				if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
					break;
			}

			update_dynamics_external_values ();

			break;
		}
	}

	if (get_gunship_entity ())
	{
		if (get_current_dynamics_options (DYNAMICS_OPTIONS_DRAW_FLIGHT_PATH))
		{
			draw_dynamic_forces ();

			update_dynamic_forces ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_dynamics_external_values (void)
{

	helicopter
		*raw;

	vec3d
		pos;

	float
		value,
		air_density,
		centre_of_gravity_to_ground_distance;

//	float rotor_workload; //Werewolf

	if (!current_flight_dynamics || !get_gunship_entity() || !get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
	{
		return;
	}

	////////////////////////////////////////
	//
	// KEEP ALL VALUES IN NATIVE FORM (do not convert to knots, or km/h etc.)
	//
	////////////////////////////////////////

	centre_of_gravity_to_ground_distance = aircraft_database [current_flight_dynamics->sub_type].centre_of_gravity_to_ground_distance;

	//
	// air density
	//

	air_density = get_air_density (current_flight_dynamics->altitude.value);

	//
	// indicated airspeed
	//

	current_flight_dynamics->indicated_airspeed.value = current_flight_dynamics->velocity_z.value * air_density;

	//
	// indicated slip
	//

	current_flight_dynamics->indicated_slip.value = current_flight_dynamics->velocity_x.value * air_density;

	//
	// barometric altitude
	//

	value = current_flight_dynamics->altitude.value;

	value -= centre_of_gravity_to_ground_distance;

	value = max (value, 0.0f);

	current_flight_dynamics->barometric_altitude.value = value;

	//
	// radar altitude
	//

	value = current_flight_dynamics->altitude.value;

	value -= current_flight_dynamics->altitude.min;

	value -= centre_of_gravity_to_ground_distance;

	value = max (value, 0.0f);

	current_flight_dynamics->radar_altitude.value = value;

	//
	// g-force
	//

	current_flight_dynamics->g_force.value = 1.0;

	//
	// combined engine rpm
	//

	value = max (current_flight_dynamics->left_engine_rpm.value, current_flight_dynamics->right_engine_rpm.value);

	value = bound (value, 0.0, 120.0);

	current_flight_dynamics->combined_engine_rpm.value = value;

	//
	// combined engine torque
	//

	value = max (current_flight_dynamics->left_engine_torque.value, current_flight_dynamics->right_engine_torque.value);

	value = bound (value, 0.0, 120.0);

	current_flight_dynamics->combined_engine_torque.value = value;

	//
	// rotor rpm
	//

	//Werewolf rotor sound pitch
//	rotor_workload = ((float) fabs (current_flight_dynamics->main_rotor_pitch_angle.value) + (float) fabs (current_flight_dynamics->main_rotor_roll_angle.value))
//			  * 1.0;
//	rotor_workload = bound (rotor_workload, 0.0, 100.0);
//	set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_MAIN_ROTOR_RPM, current_flight_dynamics->main_rotor_rpm.value / 1.20 - rotor_workload); // Werewolf

	set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_MAIN_ROTOR_RPM, current_flight_dynamics->main_rotor_rpm.value / 1.20);

	//
	// Player entity values
	//

	if (get_gunship_entity ())
	{

		set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_MAIN_ROTOR_PITCH, current_flight_dynamics->main_rotor_pitch_angle.value);

		set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_MAIN_ROTOR_ROLL, current_flight_dynamics->main_rotor_roll_angle.value);

		set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_MAIN_ROTOR_RPM, current_flight_dynamics->main_rotor_rpm.value);

		set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE, current_flight_dynamics->main_rotor_coning_angle.value);

		set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_TAIL_ROTOR_RPM, current_flight_dynamics->tail_rotor_rpm.value);

		current_flight_dynamics->model_motion_vector.x = bound (current_flight_dynamics->model_motion_vector.x, -100, 300);
		current_flight_dynamics->model_motion_vector.y = bound (current_flight_dynamics->model_motion_vector.y, -100, 300);
		current_flight_dynamics->model_motion_vector.z = bound (current_flight_dynamics->model_motion_vector.z, -100, 300);

		set_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_VELOCITY, current_flight_dynamics->model_motion_vector.z);

		set_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_MOTION_VECTOR, &current_flight_dynamics->world_motion_vector);

		//
		// position and attitude
		//

		raw = (helicopter *) get_local_entity_data (get_gunship_entity ());

		bound_double_position_to_adjusted_map_volume (&current_flight_dynamics->position);

		pos.x = current_flight_dynamics->position.x;
		pos.y = current_flight_dynamics->position.y;
		pos.z = current_flight_dynamics->position.z;

		set_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pos);

		normalise_any_3d_vector ((vec3d *) &current_flight_dynamics->attitude [0]);
		normalise_any_3d_vector ((vec3d *) &current_flight_dynamics->attitude [1]);
		normalise_any_3d_vector ((vec3d *) &current_flight_dynamics->attitude [2]);

		set_local_entity_attitude_matrix (get_gunship_entity (), current_flight_dynamics->attitude);

		if (get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info)) == TERRAIN_CLASS_LAND)
			current_flight_dynamics->position.y = bound (current_flight_dynamics->position.y, 0.0, MAX_MAP_Y);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_model_pause (event *ev)
{

	ev;

	current_flight_dynamics->model_paused = 1 - current_flight_dynamics->model_paused;

	if (current_flight_dynamics->model_paused)
	{

		debug_log ("model_paused");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void move_cog (void *ev)
{

	if (((event *) ev)->state == KEY_STATE_DOWN)
	{

		return;
	}

	switch (((event *) ev)->key)
	{

		case DIK_J:
		{

			current_flight_dynamics->centre_of_gravity.x += 0.001;

			break;
		}

		case	DIK_L:
		{

			current_flight_dynamics->centre_of_gravity.x -= 0.001;

			break;
		}

		case	DIK_K:
		{

			current_flight_dynamics->centre_of_gravity.z -= 0.001;

			break;
		}

		case	DIK_I:
		{

			current_flight_dynamics->centre_of_gravity.z += 0.001;

			break;
		}

		case	DIK_U:
		{

			current_flight_dynamics->centre_of_gravity.y += 0.001;

			break;
		}

		case	DIK_O:
		{

			current_flight_dynamics->centre_of_gravity.y -= 0.001;

			break;
		}
	}

	#if DEBUG_DYNAMICS

	debug_log ("Centre of gravity at x=%f y=%f z=%f", current_flight_dynamics->centre_of_gravity.x, current_flight_dynamics->centre_of_gravity.y, current_flight_dynamics->centre_of_gravity.z);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_dynamics_model (event *ev)
{

	FILE
		*file_ptr;

	file_ptr = fopen (current_flight_dynamics->filename, "w");

	if (file_ptr)
	{
		fprintf (file_ptr, "Comanche Hokum version = %d\n", global_options.version_number);

		fprintf (file_ptr, "left_engine_rpm value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->left_engine_rpm.value, current_flight_dynamics->left_engine_rpm.min, current_flight_dynamics->left_engine_rpm.max, current_flight_dynamics->left_engine_rpm.modifier);
		fprintf (file_ptr, "left_engine_torque value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->left_engine_torque.value, current_flight_dynamics->left_engine_torque.min, current_flight_dynamics->left_engine_torque.max, current_flight_dynamics->left_engine_torque.modifier);
		fprintf (file_ptr, "left_engine_temp value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->left_engine_temp.value, current_flight_dynamics->left_engine_temp.min, current_flight_dynamics->left_engine_temp.max, current_flight_dynamics->left_engine_temp.modifier);
		fprintf (file_ptr, "right_engine_rpm value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->right_engine_rpm.value, current_flight_dynamics->right_engine_rpm.min, current_flight_dynamics->right_engine_rpm.max, current_flight_dynamics->right_engine_rpm.modifier);
		fprintf (file_ptr, "right_engine_torque value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->right_engine_torque.value, current_flight_dynamics->right_engine_torque.min, current_flight_dynamics->right_engine_torque.max, current_flight_dynamics->right_engine_torque.modifier);
		fprintf (file_ptr, "right_engine_temp value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->right_engine_temp.value, current_flight_dynamics->right_engine_temp.min, current_flight_dynamics->right_engine_temp.max, current_flight_dynamics->right_engine_temp.modifier);
		fprintf (file_ptr, "main_rotor_number_of_blades value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_number_of_blades.value, current_flight_dynamics->main_rotor_number_of_blades.min, current_flight_dynamics->main_rotor_number_of_blades.max, current_flight_dynamics->main_rotor_number_of_blades.modifier);
		fprintf (file_ptr, "main_rotor_induced_air value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_induced_air.value, current_flight_dynamics->main_rotor_induced_air.min, current_flight_dynamics->main_rotor_induced_air.max, current_flight_dynamics->main_rotor_induced_air.modifier);
		fprintf (file_ptr, "main_rotor_induced_vortex_air_flow value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_induced_vortex_air_flow.value, current_flight_dynamics->main_rotor_induced_vortex_air_flow.min, current_flight_dynamics->main_rotor_induced_vortex_air_flow.max, current_flight_dynamics->main_rotor_induced_vortex_air_flow.modifier);
		fprintf (file_ptr, "main_rotor_diameter value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_diameter.value, current_flight_dynamics->main_rotor_diameter.min, current_flight_dynamics->main_rotor_diameter.max, current_flight_dynamics->main_rotor_diameter.modifier);
		fprintf (file_ptr, "main_rotor_area value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_area.value, current_flight_dynamics->main_rotor_area.min, current_flight_dynamics->main_rotor_area.max, current_flight_dynamics->main_rotor_area.modifier);
		fprintf (file_ptr, "main_rotor_thrust value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_thrust.value, current_flight_dynamics->main_rotor_thrust.min, current_flight_dynamics->main_rotor_thrust.max, current_flight_dynamics->main_rotor_thrust.modifier);
		fprintf (file_ptr, "main_rotor_roll_angle value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_roll_angle.value, current_flight_dynamics->main_rotor_roll_angle.min, current_flight_dynamics->main_rotor_roll_angle.max, current_flight_dynamics->main_rotor_roll_angle.modifier);
		fprintf (file_ptr, "main_rotor_pitch_angle value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_pitch_angle.value, current_flight_dynamics->main_rotor_pitch_angle.min, current_flight_dynamics->main_rotor_pitch_angle.max, current_flight_dynamics->main_rotor_pitch_angle.modifier);
		fprintf (file_ptr, "main_rotor_rpm value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_rpm.value, current_flight_dynamics->main_rotor_rpm.min, current_flight_dynamics->main_rotor_rpm.max, current_flight_dynamics->main_rotor_rpm.modifier);
		fprintf (file_ptr, "main_rotor_rps value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_rps.value, current_flight_dynamics->main_rotor_rps.min, current_flight_dynamics->main_rotor_rps.max, current_flight_dynamics->main_rotor_rps.modifier);
		fprintf (file_ptr, "main_rotor_coning_angle value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_coning_angle.value, current_flight_dynamics->main_rotor_coning_angle.min, current_flight_dynamics->main_rotor_coning_angle.max, current_flight_dynamics->main_rotor_coning_angle.modifier);
		fprintf (file_ptr, "main_rotor_angular_position value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_angular_position.value, current_flight_dynamics->main_rotor_angular_position.min, current_flight_dynamics->main_rotor_angular_position.max, current_flight_dynamics->main_rotor_angular_position.modifier);
		fprintf (file_ptr, "main_rotor_angular_increment value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_angular_increment.value, current_flight_dynamics->main_rotor_angular_increment.min, current_flight_dynamics->main_rotor_angular_increment.max, current_flight_dynamics->main_rotor_angular_increment.modifier);
		fprintf (file_ptr, "main_blade_pitch value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_blade_pitch.value, current_flight_dynamics->main_blade_pitch.min, current_flight_dynamics->main_blade_pitch.max, current_flight_dynamics->main_blade_pitch.modifier);
		fprintf (file_ptr, "main_blade_x_pitch value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_blade_x_pitch.value, current_flight_dynamics->main_blade_x_pitch.min, current_flight_dynamics->main_blade_x_pitch.max, current_flight_dynamics->main_blade_x_pitch.modifier);
		fprintf (file_ptr, "main_blade_y_pitch value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_blade_y_pitch.value, current_flight_dynamics->main_blade_y_pitch.min, current_flight_dynamics->main_blade_y_pitch.max, current_flight_dynamics->main_blade_y_pitch.modifier);
		fprintf (file_ptr, "main_rotor_swash_plate_pitch value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_swash_plate_pitch.value, current_flight_dynamics->main_rotor_swash_plate_pitch.min, current_flight_dynamics->main_rotor_swash_plate_pitch.max, current_flight_dynamics->main_rotor_swash_plate_pitch.modifier);
		fprintf (file_ptr, "main_rotor_swash_plate_roll value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->main_rotor_swash_plate_roll.value, current_flight_dynamics->main_rotor_swash_plate_roll.min, current_flight_dynamics->main_rotor_swash_plate_roll.max, current_flight_dynamics->main_rotor_swash_plate_roll.modifier);
		fprintf (file_ptr, "tail_rotor_induced_air value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_rotor_induced_air.value, current_flight_dynamics->tail_rotor_induced_air.min, current_flight_dynamics->tail_rotor_induced_air.max, current_flight_dynamics->tail_rotor_induced_air.modifier);
		fprintf (file_ptr, "tail_rotor_diameter value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_rotor_diameter.value, current_flight_dynamics->tail_rotor_diameter.min, current_flight_dynamics->tail_rotor_diameter.max, current_flight_dynamics->tail_rotor_diameter.modifier);
		fprintf (file_ptr, "tail_rotor_thrust value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_rotor_thrust.value, current_flight_dynamics->tail_rotor_thrust.min, current_flight_dynamics->tail_rotor_thrust.max, current_flight_dynamics->tail_rotor_thrust.modifier);
		fprintf (file_ptr, "tail_rotor_rpm value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_rotor_rpm.value, current_flight_dynamics->tail_rotor_rpm.min, current_flight_dynamics->tail_rotor_rpm.max, current_flight_dynamics->tail_rotor_rpm.modifier);
		fprintf (file_ptr, "tail_rotor_rps value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_rotor_rps.value, current_flight_dynamics->tail_rotor_rps.min, current_flight_dynamics->tail_rotor_rps.max, current_flight_dynamics->tail_rotor_rps.modifier);
		fprintf (file_ptr, "tail_rotor_angular_position value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_rotor_angular_position.value, current_flight_dynamics->tail_rotor_angular_position.min, current_flight_dynamics->tail_rotor_angular_position.max, current_flight_dynamics->tail_rotor_angular_position.modifier);
		fprintf (file_ptr, "tail_blade_pitch value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_blade_pitch.value, current_flight_dynamics->tail_blade_pitch.min, current_flight_dynamics->tail_blade_pitch.max, current_flight_dynamics->tail_blade_pitch.modifier);
		fprintf (file_ptr, "tail_boom_length value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->tail_boom_length.value, current_flight_dynamics->tail_boom_length.min, current_flight_dynamics->tail_boom_length.max, current_flight_dynamics->tail_boom_length.modifier);
		fprintf (file_ptr, "cross_coupling_effect value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->cross_coupling_effect.value, current_flight_dynamics->cross_coupling_effect.min, current_flight_dynamics->cross_coupling_effect.max, current_flight_dynamics->cross_coupling_effect.modifier);
		fprintf (file_ptr, "power_avaliable value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->power_avaliable.value, current_flight_dynamics->power_avaliable.min, current_flight_dynamics->power_avaliable.max, current_flight_dynamics->power_avaliable.modifier);
		fprintf (file_ptr, "power_required value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->power_required.value, current_flight_dynamics->power_required.min, current_flight_dynamics->power_required.max, current_flight_dynamics->power_required.modifier);
		fprintf (file_ptr, "power_induced value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->power_induced.value, current_flight_dynamics->power_induced.min, current_flight_dynamics->power_induced.max, current_flight_dynamics->power_induced.modifier);
		fprintf (file_ptr, "power_profile value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->power_profile.value, current_flight_dynamics->power_profile.min, current_flight_dynamics->power_profile.max, current_flight_dynamics->power_profile.modifier);
		fprintf (file_ptr, "power_parasite value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->power_parasite.value, current_flight_dynamics->power_parasite.min, current_flight_dynamics->power_parasite.max, current_flight_dynamics->power_parasite.modifier);
		fprintf (file_ptr, "power_surplus value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->power_surplus.value, current_flight_dynamics->power_surplus.min, current_flight_dynamics->power_surplus.max, current_flight_dynamics->power_surplus.modifier);
		fprintf (file_ptr, "velocity_x value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->velocity_x.value, current_flight_dynamics->velocity_x.min, current_flight_dynamics->velocity_x.max, current_flight_dynamics->velocity_x.modifier);
		fprintf (file_ptr, "velocity_y value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->velocity_y.value, current_flight_dynamics->velocity_y.min, current_flight_dynamics->velocity_y.max, current_flight_dynamics->velocity_y.modifier);
		fprintf (file_ptr, "velocity_z value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->velocity_z.value, current_flight_dynamics->velocity_z.min, 1.2 * aircraft_database[current_flight_dynamics->sub_type].cruise_velocity, current_flight_dynamics->velocity_z.modifier);
		fprintf (file_ptr, "acceleration_x value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->acceleration_x.value, current_flight_dynamics->acceleration_x.min, current_flight_dynamics->acceleration_x.max, current_flight_dynamics->acceleration_x.modifier);
		fprintf (file_ptr, "acceleration_y value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->acceleration_y.value, current_flight_dynamics->acceleration_y.min, current_flight_dynamics->acceleration_y.max, current_flight_dynamics->acceleration_y.modifier);
		fprintf (file_ptr, "acceleration_z value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->acceleration_z.value, current_flight_dynamics->acceleration_z.min, current_flight_dynamics->acceleration_z.max, current_flight_dynamics->acceleration_z.modifier);
		fprintf (file_ptr, "world_velocity_x value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->world_velocity_x.value, current_flight_dynamics->world_velocity_x.min, current_flight_dynamics->world_velocity_x.max, current_flight_dynamics->world_velocity_x.modifier);
		fprintf (file_ptr, "world_velocity_y value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->world_velocity_y.value, current_flight_dynamics->world_velocity_y.min, current_flight_dynamics->world_velocity_y.max, current_flight_dynamics->world_velocity_y.modifier);
		fprintf (file_ptr, "world_velocity_z value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->world_velocity_z.value, current_flight_dynamics->world_velocity_z.min, current_flight_dynamics->world_velocity_z.max, current_flight_dynamics->world_velocity_z.modifier);
		fprintf (file_ptr, "air_density value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->air_density.value, current_flight_dynamics->air_density.min, current_flight_dynamics->air_density.max, current_flight_dynamics->air_density.modifier);
		fprintf (file_ptr, "pitch value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->pitch.value, current_flight_dynamics->pitch.min, current_flight_dynamics->pitch.max, current_flight_dynamics->pitch.modifier);
		fprintf (file_ptr, "roll value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->roll.value, current_flight_dynamics->roll.min, current_flight_dynamics->roll.max, current_flight_dynamics->roll.modifier);
		fprintf (file_ptr, "heading value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->heading.value, current_flight_dynamics->heading.min, current_flight_dynamics->heading.max, current_flight_dynamics->heading.modifier);
		fprintf (file_ptr, "lift value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->lift.value, current_flight_dynamics->lift.min, current_flight_dynamics->lift.max, current_flight_dynamics->lift.modifier);
		fprintf (file_ptr, "translational_lift value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->translational_lift.value, current_flight_dynamics->translational_lift.min, current_flight_dynamics->translational_lift.max, current_flight_dynamics->translational_lift.modifier);
		fprintf (file_ptr, "altitude value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->altitude.value, current_flight_dynamics->altitude.min, current_flight_dynamics->altitude.max, current_flight_dynamics->altitude.modifier);
		fprintf (file_ptr, "drag_x value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->drag_x.value, current_flight_dynamics->drag_x.min, current_flight_dynamics->drag_x.max, current_flight_dynamics->drag_x.modifier);
		fprintf (file_ptr, "drag_y value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->drag_y.value, current_flight_dynamics->drag_y.min, current_flight_dynamics->drag_y.max, current_flight_dynamics->drag_y.modifier);
		fprintf (file_ptr, "drag_z value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->drag_z.value, current_flight_dynamics->drag_z.min, current_flight_dynamics->drag_z.max, current_flight_dynamics->drag_z.modifier);
		fprintf (file_ptr, "heading_inertia value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->heading_inertia.value, current_flight_dynamics->heading_inertia.min, current_flight_dynamics->heading_inertia.max, current_flight_dynamics->heading_inertia.modifier);
		fprintf (file_ptr, "pitch_inertia value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->pitch_inertia.value, current_flight_dynamics->pitch_inertia.min, current_flight_dynamics->pitch_inertia.max, current_flight_dynamics->pitch_inertia.modifier);
		fprintf (file_ptr, "roll_inertia value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->roll_inertia.value, current_flight_dynamics->roll_inertia.min, current_flight_dynamics->roll_inertia.max, current_flight_dynamics->roll_inertia.modifier);
		fprintf (file_ptr, "heading_moment value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->heading_moment.value, current_flight_dynamics->heading_moment.min, current_flight_dynamics->heading_moment.max, current_flight_dynamics->heading_moment.modifier);
		fprintf (file_ptr, "pitch_moment value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->pitch_moment.value, current_flight_dynamics->pitch_moment.min, current_flight_dynamics->pitch_moment.max, current_flight_dynamics->pitch_moment.modifier);
		fprintf (file_ptr, "roll_moment value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->roll_moment.value, current_flight_dynamics->roll_moment.min, current_flight_dynamics->roll_moment.max, current_flight_dynamics->roll_moment.modifier);
		fprintf (file_ptr, "heading_moment_reaction value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->heading_moment_reaction.value, current_flight_dynamics->heading_moment_reaction.min, current_flight_dynamics->heading_moment_reaction.max, current_flight_dynamics->heading_moment_reaction.modifier);
		fprintf (file_ptr, "pitch_moment_reaction value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->pitch_moment_reaction.value, current_flight_dynamics->pitch_moment_reaction.min, current_flight_dynamics->pitch_moment_reaction.max, current_flight_dynamics->pitch_moment_reaction.modifier);
		fprintf (file_ptr, "roll_moment_reaction value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->roll_moment_reaction.value, current_flight_dynamics->roll_moment_reaction.min, current_flight_dynamics->roll_moment_reaction.max, current_flight_dynamics->roll_moment_reaction.modifier);
		fprintf (file_ptr, "angular_heading_acceleration value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->angular_heading_acceleration.value, current_flight_dynamics->angular_heading_acceleration.min, current_flight_dynamics->angular_heading_acceleration.max, current_flight_dynamics->angular_heading_acceleration.modifier);
		fprintf (file_ptr, "angular_pitch_acceleration value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->angular_pitch_acceleration.value, current_flight_dynamics->angular_pitch_acceleration.min, current_flight_dynamics->angular_pitch_acceleration.max, current_flight_dynamics->angular_pitch_acceleration.modifier);
		fprintf (file_ptr, "angular_roll_acceleration value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->angular_roll_acceleration.value, current_flight_dynamics->angular_roll_acceleration.min, current_flight_dynamics->angular_roll_acceleration.max, current_flight_dynamics->angular_roll_acceleration.modifier);
		fprintf (file_ptr, "angular_heading_velocity value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->angular_heading_velocity.value, current_flight_dynamics->angular_heading_velocity.min, current_flight_dynamics->angular_heading_velocity.max, current_flight_dynamics->angular_heading_velocity.modifier);
		fprintf (file_ptr, "angular_pitch_velocity value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->angular_pitch_velocity.value, current_flight_dynamics->angular_pitch_velocity.min, current_flight_dynamics->angular_pitch_velocity.max, current_flight_dynamics->angular_pitch_velocity.modifier);
		fprintf (file_ptr, "angular_roll_velocity value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->angular_roll_velocity.value, current_flight_dynamics->angular_roll_velocity.min, current_flight_dynamics->angular_roll_velocity.max, current_flight_dynamics->angular_roll_velocity.modifier);
		fprintf (file_ptr, "landing_quality value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->landing_quality.value, current_flight_dynamics->landing_quality.min, current_flight_dynamics->landing_quality.max, current_flight_dynamics->landing_quality.modifier);
		fprintf (file_ptr, "mass value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->mass.value, current_flight_dynamics->mass.min, current_flight_dynamics->mass.max, current_flight_dynamics->mass.modifier);
		fprintf (file_ptr, "weapon_mass value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->weapon_mass.value, current_flight_dynamics->weapon_mass.min, current_flight_dynamics->weapon_mass.max, current_flight_dynamics->weapon_mass.modifier);
		fprintf (file_ptr, "ground_effect value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->ground_effect.value, current_flight_dynamics->ground_effect.min, current_flight_dynamics->ground_effect.max, current_flight_dynamics->ground_effect.modifier);
		fprintf (file_ptr, "indicated_airspeed value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->indicated_airspeed.value, current_flight_dynamics->indicated_airspeed.min, current_flight_dynamics->indicated_airspeed.max, current_flight_dynamics->indicated_airspeed.modifier);
		fprintf (file_ptr, "indicated_slip value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->indicated_slip.value, current_flight_dynamics->indicated_slip.min, current_flight_dynamics->indicated_slip.max, current_flight_dynamics->indicated_slip.modifier);
		fprintf (file_ptr, "barometric_altitude value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->barometric_altitude.value, current_flight_dynamics->barometric_altitude.min, current_flight_dynamics->barometric_altitude.max, current_flight_dynamics->barometric_altitude.modifier);
		fprintf (file_ptr, "radar_altitude value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->radar_altitude.value, current_flight_dynamics->radar_altitude.min, current_flight_dynamics->radar_altitude.max, current_flight_dynamics->radar_altitude.modifier);
		fprintf (file_ptr, "g_force value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->g_force.value, current_flight_dynamics->g_force.min, current_flight_dynamics->g_force.max, current_flight_dynamics->g_force.modifier);
		fprintf (file_ptr, "combined_engine_rpm value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->combined_engine_rpm.value, current_flight_dynamics->combined_engine_rpm.min, current_flight_dynamics->combined_engine_rpm.max, current_flight_dynamics->combined_engine_rpm.modifier);
		fprintf (file_ptr, "combined_engine_torque value = %f, min = %f, max = %f, modifier = %f\n", current_flight_dynamics->combined_engine_torque.value, current_flight_dynamics->combined_engine_torque.min, current_flight_dynamics->combined_engine_torque.max, current_flight_dynamics->combined_engine_torque.modifier);
		fprintf (file_ptr, "fuel_weight value = %f, min = %f, max = %f, modifier = %f, delta = %f\n", current_flight_dynamics->fuel_weight.value, current_flight_dynamics->fuel_weight.min, current_flight_dynamics->fuel_weight.max, current_flight_dynamics->fuel_weight.modifier, current_flight_dynamics->fuel_weight.delta);
		fprintf (file_ptr, "centre_of_gravity_x = %f, centre_of_gravity_y = %f, centre_of_gravity_z = %f\n", current_flight_dynamics->centre_of_gravity.x, current_flight_dynamics->centre_of_gravity.y, current_flight_dynamics->centre_of_gravity.z);
		fclose (file_ptr);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_dynamics_model (event *ev)
{

	int
		version_number;

	FILE
		*file_ptr;

	// JB 030313 Enable running out of separate directories
	if (file_exist (current_flight_dynamics->filename))
	{
		file_ptr = safe_fopen (current_flight_dynamics->filename, "r");
	}
	else
	{
		file_ptr = NULL;
	}

	if (file_ptr)
	{

		fscanf (file_ptr, "Comanche Hokum version = %d\n", &version_number);

		if (version_number != global_options.version_number)
		{

			if (command_line_dynamics_flight_model == 2)
			{
				ASSERT (!"DYNAMICS: Can't load dynamics file... wrong version. Reset to default FM");

				command_line_dynamics_flight_model = 0;
				initialise_flight_dynamics(get_gunship_entity ());
			}
			else
			{
				debug_log ("DYNAMICS: Can't load dynamics file... wrong version. Creating new dynamics file");

				fclose (file_ptr);

				save_dynamics_model (NULL);
			}				

			return;
		}

		fscanf (file_ptr, "left_engine_rpm value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->left_engine_rpm.value, &current_flight_dynamics->left_engine_rpm.min, &current_flight_dynamics->left_engine_rpm.max, &current_flight_dynamics->left_engine_rpm.modifier);
		fscanf (file_ptr, "left_engine_torque value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->left_engine_torque.value, &current_flight_dynamics->left_engine_torque.min, &current_flight_dynamics->left_engine_torque.max, &current_flight_dynamics->left_engine_torque.modifier);
		fscanf (file_ptr, "left_engine_temp value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->left_engine_temp.value, &current_flight_dynamics->left_engine_temp.min, &current_flight_dynamics->left_engine_temp.max, &current_flight_dynamics->left_engine_temp.modifier);
		fscanf (file_ptr, "right_engine_rpm value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->right_engine_rpm.value, &current_flight_dynamics->right_engine_rpm.min, &current_flight_dynamics->right_engine_rpm.max, &current_flight_dynamics->right_engine_rpm.modifier);
		fscanf (file_ptr, "right_engine_torque value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->right_engine_torque.value, &current_flight_dynamics->right_engine_torque.min, &current_flight_dynamics->right_engine_torque.max, &current_flight_dynamics->right_engine_torque.modifier);
		fscanf (file_ptr, "right_engine_temp value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->right_engine_temp.value, &current_flight_dynamics->right_engine_temp.min, &current_flight_dynamics->right_engine_temp.max, &current_flight_dynamics->right_engine_temp.modifier);
		fscanf (file_ptr, "main_rotor_number_of_blades value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_number_of_blades.value, &current_flight_dynamics->main_rotor_number_of_blades.min, &current_flight_dynamics->main_rotor_number_of_blades.max, &current_flight_dynamics->main_rotor_number_of_blades.modifier);
		fscanf (file_ptr, "main_rotor_induced_air value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_induced_air.value, &current_flight_dynamics->main_rotor_induced_air.min, &current_flight_dynamics->main_rotor_induced_air.max, &current_flight_dynamics->main_rotor_induced_air.modifier);
		fscanf (file_ptr, "main_rotor_induced_vortex_air_flow value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_induced_vortex_air_flow.value, &current_flight_dynamics->main_rotor_induced_vortex_air_flow.min, &current_flight_dynamics->main_rotor_induced_vortex_air_flow.max, &current_flight_dynamics->main_rotor_induced_vortex_air_flow.modifier);
		fscanf (file_ptr, "main_rotor_diameter value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_diameter.value, &current_flight_dynamics->main_rotor_diameter.min, &current_flight_dynamics->main_rotor_diameter.max, &current_flight_dynamics->main_rotor_diameter.modifier);
		fscanf (file_ptr, "main_rotor_area value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_area.value, &current_flight_dynamics->main_rotor_area.min, &current_flight_dynamics->main_rotor_area.max, &current_flight_dynamics->main_rotor_area.modifier);
		fscanf (file_ptr, "main_rotor_thrust value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_thrust.value, &current_flight_dynamics->main_rotor_thrust.min, &current_flight_dynamics->main_rotor_thrust.max, &current_flight_dynamics->main_rotor_thrust.modifier);
		fscanf (file_ptr, "main_rotor_roll_angle value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_roll_angle.value, &current_flight_dynamics->main_rotor_roll_angle.min, &current_flight_dynamics->main_rotor_roll_angle.max, &current_flight_dynamics->main_rotor_roll_angle.modifier);
		fscanf (file_ptr, "main_rotor_pitch_angle value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_pitch_angle.value, &current_flight_dynamics->main_rotor_pitch_angle.min, &current_flight_dynamics->main_rotor_pitch_angle.max, &current_flight_dynamics->main_rotor_pitch_angle.modifier);
		fscanf (file_ptr, "main_rotor_rpm value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_rpm.value, &current_flight_dynamics->main_rotor_rpm.min, &current_flight_dynamics->main_rotor_rpm.max, &current_flight_dynamics->main_rotor_rpm.modifier);
		fscanf (file_ptr, "main_rotor_rps value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_rps.value, &current_flight_dynamics->main_rotor_rps.min, &current_flight_dynamics->main_rotor_rps.max, &current_flight_dynamics->main_rotor_rps.modifier);
		fscanf (file_ptr, "main_rotor_coning_angle value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_coning_angle.value, &current_flight_dynamics->main_rotor_coning_angle.min, &current_flight_dynamics->main_rotor_coning_angle.max, &current_flight_dynamics->main_rotor_coning_angle.modifier);
		fscanf (file_ptr, "main_rotor_angular_position value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_angular_position.value, &current_flight_dynamics->main_rotor_angular_position.min, &current_flight_dynamics->main_rotor_angular_position.max, &current_flight_dynamics->main_rotor_angular_position.modifier);
		fscanf (file_ptr, "main_rotor_angular_increment value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_angular_increment.value, &current_flight_dynamics->main_rotor_angular_increment.min, &current_flight_dynamics->main_rotor_angular_increment.max, &current_flight_dynamics->main_rotor_angular_increment.modifier);
		fscanf (file_ptr, "main_blade_pitch value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_blade_pitch.value, &current_flight_dynamics->main_blade_pitch.min, &current_flight_dynamics->main_blade_pitch.max, &current_flight_dynamics->main_blade_pitch.modifier);
		fscanf (file_ptr, "main_blade_x_pitch value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_blade_x_pitch.value, &current_flight_dynamics->main_blade_x_pitch.min, &current_flight_dynamics->main_blade_x_pitch.max, &current_flight_dynamics->main_blade_x_pitch.modifier);
		fscanf (file_ptr, "main_blade_y_pitch value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_blade_y_pitch.value, &current_flight_dynamics->main_blade_y_pitch.min, &current_flight_dynamics->main_blade_y_pitch.max, &current_flight_dynamics->main_blade_y_pitch.modifier);
		fscanf (file_ptr, "main_rotor_swash_plate_pitch value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_swash_plate_pitch.value, &current_flight_dynamics->main_rotor_swash_plate_pitch.min, &current_flight_dynamics->main_rotor_swash_plate_pitch.max, &current_flight_dynamics->main_rotor_swash_plate_pitch.modifier);
		fscanf (file_ptr, "main_rotor_swash_plate_roll value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->main_rotor_swash_plate_roll.value, &current_flight_dynamics->main_rotor_swash_plate_roll.min, &current_flight_dynamics->main_rotor_swash_plate_roll.max, &current_flight_dynamics->main_rotor_swash_plate_roll.modifier);
		fscanf (file_ptr, "tail_rotor_induced_air value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_rotor_induced_air.value, &current_flight_dynamics->tail_rotor_induced_air.min, &current_flight_dynamics->tail_rotor_induced_air.max, &current_flight_dynamics->tail_rotor_induced_air.modifier);
		fscanf (file_ptr, "tail_rotor_diameter value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_rotor_diameter.value, &current_flight_dynamics->tail_rotor_diameter.min, &current_flight_dynamics->tail_rotor_diameter.max, &current_flight_dynamics->tail_rotor_diameter.modifier);
		fscanf (file_ptr, "tail_rotor_thrust value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_rotor_thrust.value, &current_flight_dynamics->tail_rotor_thrust.min, &current_flight_dynamics->tail_rotor_thrust.max, &current_flight_dynamics->tail_rotor_thrust.modifier);
		fscanf (file_ptr, "tail_rotor_rpm value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_rotor_rpm.value, &current_flight_dynamics->tail_rotor_rpm.min, &current_flight_dynamics->tail_rotor_rpm.max, &current_flight_dynamics->tail_rotor_rpm.modifier);
		fscanf (file_ptr, "tail_rotor_rps value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_rotor_rps.value, &current_flight_dynamics->tail_rotor_rps.min, &current_flight_dynamics->tail_rotor_rps.max, &current_flight_dynamics->tail_rotor_rps.modifier);
		fscanf (file_ptr, "tail_rotor_angular_position value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_rotor_angular_position.value, &current_flight_dynamics->tail_rotor_angular_position.min, &current_flight_dynamics->tail_rotor_angular_position.max, &current_flight_dynamics->tail_rotor_angular_position.modifier);
		fscanf (file_ptr, "tail_blade_pitch value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_blade_pitch.value, &current_flight_dynamics->tail_blade_pitch.min, &current_flight_dynamics->tail_blade_pitch.max, &current_flight_dynamics->tail_blade_pitch.modifier);
		fscanf (file_ptr, "tail_boom_length value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->tail_boom_length.value, &current_flight_dynamics->tail_boom_length.min, &current_flight_dynamics->tail_boom_length.max, &current_flight_dynamics->tail_boom_length.modifier);
		fscanf (file_ptr, "cross_coupling_effect value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->cross_coupling_effect.value, &current_flight_dynamics->cross_coupling_effect.min, &current_flight_dynamics->cross_coupling_effect.max, &current_flight_dynamics->cross_coupling_effect.modifier);
		fscanf (file_ptr, "power_avaliable value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->power_avaliable.value, &current_flight_dynamics->power_avaliable.min, &current_flight_dynamics->power_avaliable.max, &current_flight_dynamics->power_avaliable.modifier);
		fscanf (file_ptr, "power_required value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->power_required.value, &current_flight_dynamics->power_required.min, &current_flight_dynamics->power_required.max, &current_flight_dynamics->power_required.modifier);
		fscanf (file_ptr, "power_induced value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->power_induced.value, &current_flight_dynamics->power_induced.min, &current_flight_dynamics->power_induced.max, &current_flight_dynamics->power_induced.modifier);
		fscanf (file_ptr, "power_profile value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->power_profile.value, &current_flight_dynamics->power_profile.min, &current_flight_dynamics->power_profile.max, &current_flight_dynamics->power_profile.modifier);
		fscanf (file_ptr, "power_parasite value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->power_parasite.value, &current_flight_dynamics->power_parasite.min, &current_flight_dynamics->power_parasite.max, &current_flight_dynamics->power_parasite.modifier);
		fscanf (file_ptr, "power_surplus value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->power_surplus.value, &current_flight_dynamics->power_surplus.min, &current_flight_dynamics->power_surplus.max, &current_flight_dynamics->power_surplus.modifier);
		fscanf (file_ptr, "velocity_x value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->velocity_x.value, &current_flight_dynamics->velocity_x.min, &current_flight_dynamics->velocity_x.max, &current_flight_dynamics->velocity_x.modifier);
		fscanf (file_ptr, "velocity_y value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->velocity_y.value, &current_flight_dynamics->velocity_y.min, &current_flight_dynamics->velocity_y.max, &current_flight_dynamics->velocity_y.modifier);
		fscanf (file_ptr, "velocity_z value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->velocity_z.value, &current_flight_dynamics->velocity_z.min, &current_flight_dynamics->velocity_z.max, &current_flight_dynamics->velocity_z.modifier);
		current_flight_dynamics->velocity_z.max = 1.2 * aircraft_database[current_flight_dynamics->sub_type].cruise_velocity;
		fscanf (file_ptr, "acceleration_x value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->acceleration_x.value, &current_flight_dynamics->acceleration_x.min, &current_flight_dynamics->acceleration_x.max, &current_flight_dynamics->acceleration_x.modifier);
		fscanf (file_ptr, "acceleration_y value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->acceleration_y.value, &current_flight_dynamics->acceleration_y.min, &current_flight_dynamics->acceleration_y.max, &current_flight_dynamics->acceleration_y.modifier);
		fscanf (file_ptr, "acceleration_z value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->acceleration_z.value, &current_flight_dynamics->acceleration_z.min, &current_flight_dynamics->acceleration_z.max, &current_flight_dynamics->acceleration_z.modifier);
		fscanf (file_ptr, "world_velocity_x value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->world_velocity_x.value, &current_flight_dynamics->world_velocity_x.min, &current_flight_dynamics->world_velocity_x.max, &current_flight_dynamics->world_velocity_x.modifier);
		fscanf (file_ptr, "world_velocity_y value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->world_velocity_y.value, &current_flight_dynamics->world_velocity_y.min, &current_flight_dynamics->world_velocity_y.max, &current_flight_dynamics->world_velocity_y.modifier);
		fscanf (file_ptr, "world_velocity_z value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->world_velocity_z.value, &current_flight_dynamics->world_velocity_z.min, &current_flight_dynamics->world_velocity_z.max, &current_flight_dynamics->world_velocity_z.modifier);
		fscanf (file_ptr, "air_density value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->air_density.value, &current_flight_dynamics->air_density.min, &current_flight_dynamics->air_density.max, &current_flight_dynamics->air_density.modifier);
		fscanf (file_ptr, "pitch value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->pitch.value, &current_flight_dynamics->pitch.min, &current_flight_dynamics->pitch.max, &current_flight_dynamics->pitch.modifier);
		fscanf (file_ptr, "roll value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->roll.value, &current_flight_dynamics->roll.min, &current_flight_dynamics->roll.max, &current_flight_dynamics->roll.modifier);
		fscanf (file_ptr, "heading value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->heading.value, &current_flight_dynamics->heading.min, &current_flight_dynamics->heading.max, &current_flight_dynamics->heading.modifier);
		fscanf (file_ptr, "lift value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->lift.value, &current_flight_dynamics->lift.min, &current_flight_dynamics->lift.max, &current_flight_dynamics->lift.modifier);
		fscanf (file_ptr, "translational_lift value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->translational_lift.value, &current_flight_dynamics->translational_lift.min, &current_flight_dynamics->translational_lift.max, &current_flight_dynamics->translational_lift.modifier);
		fscanf (file_ptr, "altitude value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->altitude.value, &current_flight_dynamics->altitude.min, &current_flight_dynamics->altitude.max, &current_flight_dynamics->altitude.modifier);
		fscanf (file_ptr, "drag_x value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->drag_x.value, &current_flight_dynamics->drag_x.min, &current_flight_dynamics->drag_x.max, &current_flight_dynamics->drag_x.modifier);
		fscanf (file_ptr, "drag_y value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->drag_y.value, &current_flight_dynamics->drag_y.min, &current_flight_dynamics->drag_y.max, &current_flight_dynamics->drag_y.modifier);
		fscanf (file_ptr, "drag_z value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->drag_z.value, &current_flight_dynamics->drag_z.min, &current_flight_dynamics->drag_z.max, &current_flight_dynamics->drag_z.modifier);
		fscanf (file_ptr, "heading_inertia value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->heading_inertia.value, &current_flight_dynamics->heading_inertia.min, &current_flight_dynamics->heading_inertia.max, &current_flight_dynamics->heading_inertia.modifier);
		fscanf (file_ptr, "pitch_inertia value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->pitch_inertia.value, &current_flight_dynamics->pitch_inertia.min, &current_flight_dynamics->pitch_inertia.max, &current_flight_dynamics->pitch_inertia.modifier);
		fscanf (file_ptr, "roll_inertia value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->roll_inertia.value, &current_flight_dynamics->roll_inertia.min, &current_flight_dynamics->roll_inertia.max, &current_flight_dynamics->roll_inertia.modifier);
		fscanf (file_ptr, "heading_moment value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->heading_moment.value, &current_flight_dynamics->heading_moment.min, &current_flight_dynamics->heading_moment.max, &current_flight_dynamics->heading_moment.modifier);
		fscanf (file_ptr, "pitch_moment value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->pitch_moment.value, &current_flight_dynamics->pitch_moment.min, &current_flight_dynamics->pitch_moment.max, &current_flight_dynamics->pitch_moment.modifier);
		fscanf (file_ptr, "roll_moment value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->roll_moment.value, &current_flight_dynamics->roll_moment.min, &current_flight_dynamics->roll_moment.max, &current_flight_dynamics->roll_moment.modifier);
		fscanf (file_ptr, "heading_moment_reaction value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->heading_moment_reaction.value, &current_flight_dynamics->heading_moment_reaction.min, &current_flight_dynamics->heading_moment_reaction.max, &current_flight_dynamics->heading_moment_reaction.modifier);
		fscanf (file_ptr, "pitch_moment_reaction value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->pitch_moment_reaction.value, &current_flight_dynamics->pitch_moment_reaction.min, &current_flight_dynamics->pitch_moment_reaction.max, &current_flight_dynamics->pitch_moment_reaction.modifier);
		fscanf (file_ptr, "roll_moment_reaction value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->roll_moment_reaction.value, &current_flight_dynamics->roll_moment_reaction.min, &current_flight_dynamics->roll_moment_reaction.max, &current_flight_dynamics->roll_moment_reaction.modifier);
		fscanf (file_ptr, "angular_heading_acceleration value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->angular_heading_acceleration.value, &current_flight_dynamics->angular_heading_acceleration.min, &current_flight_dynamics->angular_heading_acceleration.max, &current_flight_dynamics->angular_heading_acceleration.modifier);
		fscanf (file_ptr, "angular_pitch_acceleration value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->angular_pitch_acceleration.value, &current_flight_dynamics->angular_pitch_acceleration.min, &current_flight_dynamics->angular_pitch_acceleration.max, &current_flight_dynamics->angular_pitch_acceleration.modifier);
		fscanf (file_ptr, "angular_roll_acceleration value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->angular_roll_acceleration.value, &current_flight_dynamics->angular_roll_acceleration.min, &current_flight_dynamics->angular_roll_acceleration.max, &current_flight_dynamics->angular_roll_acceleration.modifier);
		fscanf (file_ptr, "angular_heading_velocity value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->angular_heading_velocity.value, &current_flight_dynamics->angular_heading_velocity.min, &current_flight_dynamics->angular_heading_velocity.max, &current_flight_dynamics->angular_heading_velocity.modifier);
		fscanf (file_ptr, "angular_pitch_velocity value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->angular_pitch_velocity.value, &current_flight_dynamics->angular_pitch_velocity.min, &current_flight_dynamics->angular_pitch_velocity.max, &current_flight_dynamics->angular_pitch_velocity.modifier);
		fscanf (file_ptr, "angular_roll_velocity value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->angular_roll_velocity.value, &current_flight_dynamics->angular_roll_velocity.min, &current_flight_dynamics->angular_roll_velocity.max, &current_flight_dynamics->angular_roll_velocity.modifier);
		fscanf (file_ptr, "landing_quality value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->landing_quality.value, &current_flight_dynamics->landing_quality.min, &current_flight_dynamics->landing_quality.max, &current_flight_dynamics->landing_quality.modifier);
		fscanf (file_ptr, "mass value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->mass.value, &current_flight_dynamics->mass.min, &current_flight_dynamics->mass.max, &current_flight_dynamics->mass.modifier);
		fscanf (file_ptr, "weapon_mass value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->weapon_mass.value, &current_flight_dynamics->weapon_mass.min, &current_flight_dynamics->weapon_mass.max, &current_flight_dynamics->weapon_mass.modifier);
		fscanf (file_ptr, "ground_effect value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->ground_effect.value, &current_flight_dynamics->ground_effect.min, &current_flight_dynamics->ground_effect.max, &current_flight_dynamics->ground_effect.modifier);
		fscanf (file_ptr, "indicated_airspeed value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->indicated_airspeed.value, &current_flight_dynamics->indicated_airspeed.min, &current_flight_dynamics->indicated_airspeed.max, &current_flight_dynamics->indicated_airspeed.modifier);
		fscanf (file_ptr, "indicated_slip value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->indicated_slip.value, &current_flight_dynamics->indicated_slip.min, &current_flight_dynamics->indicated_slip.max, &current_flight_dynamics->indicated_slip.modifier);
		fscanf (file_ptr, "barometric_altitude value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->barometric_altitude.value, &current_flight_dynamics->barometric_altitude.min, &current_flight_dynamics->barometric_altitude.max, &current_flight_dynamics->barometric_altitude.modifier);
		fscanf (file_ptr, "radar_altitude value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->radar_altitude.value, &current_flight_dynamics->radar_altitude.min, &current_flight_dynamics->radar_altitude.max, &current_flight_dynamics->radar_altitude.modifier);
		fscanf (file_ptr, "g_force value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->g_force.value, &current_flight_dynamics->g_force.min, &current_flight_dynamics->g_force.max, &current_flight_dynamics->g_force.modifier);
		fscanf (file_ptr, "combined_engine_rpm value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->combined_engine_rpm.value, &current_flight_dynamics->combined_engine_rpm.min, &current_flight_dynamics->combined_engine_rpm.max, &current_flight_dynamics->combined_engine_rpm.modifier);
		fscanf (file_ptr, "combined_engine_torque value = %f, min = %f, max = %f, modifier = %f\n", &current_flight_dynamics->combined_engine_torque.value, &current_flight_dynamics->combined_engine_torque.min, &current_flight_dynamics->combined_engine_torque.max, &current_flight_dynamics->combined_engine_torque.modifier);
		fscanf (file_ptr, "fuel_weight value = %f, min = %f, max = %f, modifier = %f, delta = %f\n", &current_flight_dynamics->fuel_weight.value, &current_flight_dynamics->fuel_weight.min, &current_flight_dynamics->fuel_weight.max, &current_flight_dynamics->fuel_weight.modifier, &current_flight_dynamics->fuel_weight.delta);
		current_flight_dynamics->fuel_weight.value = current_flight_dynamics->fuel_weight.max = aircraft_database[current_flight_dynamics->sub_type].fuel_default_weight;
		fscanf (file_ptr, "centre_of_gravity_x = %f, centre_of_gravity_y = %f, centre_of_gravity_z = %f\n", &current_flight_dynamics->centre_of_gravity.x, &current_flight_dynamics->centre_of_gravity.y, &current_flight_dynamics->centre_of_gravity.z);
		fclose (file_ptr);
	}
	else
	{

		if (command_line_dynamics_flight_model != 2)
		{
			debug_log ("DYNAMICS: Can't load dynamics file. Creating new dynamics file");
		}
		else
		{
			debug_fatal("Dynamics file is missing for this helicopter! DO NOT USE DYN FILES FROM DEFAULT FLIGHT MODEL! ");
		}
		
		save_dynamics_model (NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_toggle_rotor_brake (event *ev)
{

	if (current_flight_dynamics->rotor_brake)
	{

		set_current_flight_dynamics_rotor_brake (FALSE);
	}
	else
	{

		set_current_flight_dynamics_rotor_brake (TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_current_flight_dynamics_rotor_brake (int flag)
{
	entity
		*group;

	current_flight_dynamics->rotor_brake = flag;

	if (flag)
	{

		#if DYNAMICS_DEBUG

		debug_log ("DYNAMICS: rotor brake engaged");

		#endif

		//
		// Enter debrief if
		//		landed &&
		//		rotor brake on &&
		//		no task (task must be complete
		//	Switch wheel brake on to stop sliding about.
		//

		if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{

			set_current_flight_dynamics_wheel_brake (TRUE);

			group = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_MEMBER);

			ASSERT (group);

			if ((get_keysite_currently_landed_at () == get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP)) &&
				(!get_local_entity_primary_task (get_gunship_entity ())))
			{

				entity
					*landing_task,
					*landed_wp,
					*landing_en;

				landed_wp = get_local_entity_current_waypoint (get_gunship_entity ());

				if (landed_wp)
				{

					landing_task = get_local_entity_parent (landed_wp, LIST_TYPE_WAYPOINT);

					if (landing_task)
					{

						if (get_local_entity_int_value (landing_task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_LANDING)
						{

							landing_en = get_local_entity_landing_entity (get_keysite_currently_landed_at (), ENTITY_SUB_TYPE_LANDING_HELICOPTER);

							if ((landing_en) && (!check_landing_route_lock_clear (landing_en, get_gunship_entity ())))
							{

								notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, landing_en, get_gunship_entity (), TASK_TERMINATED_WAYPOINT_ROUTE_COMPLETE);
							}
						}
					}
				}

				//
				// landed at MAIN-BASE go to weapon screen, do debrief and exit
				//

//				start_game_exit (GAME_EXIT_DEBRIEF, FALSE);
			}
			else if (get_keysite_currently_landed_at ())
			{

				//
				// landed at BASE go to weapon screen
				//

				//notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_WEAPON_LOADING);
			}
		}
	}
	else
	{

		#if DYNAMICS_DEBUG

		debug_log ("DYNAMICS: WARNING : rotor brake disengaged");

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_toggle_wheel_brake (event *ev)
{

	if (current_flight_dynamics->wheel_brake)
	{

		set_current_flight_dynamics_wheel_brake (FALSE);
	}
	else
	{

		set_current_flight_dynamics_wheel_brake (TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_current_flight_dynamics_wheel_brake (int flag)
{
	switch (get_global_gunship_type ())
	{
		case GUNSHIP_TYPE_VIPER:
		case GUNSHIP_TYPE_KIOWA:
			{
				flag = TRUE;
				break;
			}
		default:
			{
				break;
			}
	}

	current_flight_dynamics->wheel_brake = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_toggle_auto_hover (event *ev)
{

	dynamics_hover_hold_types
		type;

	ASSERT (get_gunship_entity ());
/*
	if ((current_flight_dynamics->auto_hover) ||
		(get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT)) ||
		(!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT)) ||
		(current_flight_dynamics->dynamics_damage != DYNAMICS_DAMAGE_NONE))
	{

		if (current_flight_dynamics->auto_hover)
		{

			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_OFF);
		}

		set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
	}
	else
	{

		if (current_flight_dynamics->velocity_z.value < knots_to_metres_per_second (20.0))
		{

			if (ev->modifier == MODIFIER_LEFT_SHIFT)
			{

				set_current_flight_dynamics_auto_hover (HOVER_HOLD_STABLE);
			}
			else
			{

				set_current_flight_dynamics_auto_hover (HOVER_HOLD_NORMAL);
			}

			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_ON);
		}
		else
		{

			if (sfrand1 () < 0.0)
			{

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_TOO_FAST1);
			}
			else
			{

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_TOO_FAST2);
			}
		}
	}
	*/

	type = HOVER_HOLD_NORMAL;

	if (ev->modifier == MODIFIER_LEFT_SHIFT)
	{
		type = HOVER_HOLD_STABLE;
	}

	if (valid_dynamics_autos_on (type))
	{
		set_current_flight_dynamics_auto_hover (type);
	}
	else
	{
		set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_current_flight_dynamics_auto_pilot (int flag)
{
	int
		no_right_engine;

	no_right_engine = get_global_gunship_type() == GUNSHIP_TYPE_KIOWA;

/*
	unsigned int
		damage;


	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT) == flag)
	{

		return;
	}

	// auto_pilot off if :
	//		helicopter damaged
	//		out of fuel
	//		lower than 25m

	damage = current_flight_dynamics->dynamics_damage;

	damage = damage & ~(DYNAMICS_DAMAGE_NONE | DYNAMICS_DAMAGE_AVIONICS);

	if (
			(!flag) ||
			(damage) ||
			(current_flight_dynamics->fuel_weight.value <= 0.0) ||
			(!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT)) ||
			(current_flight_dynamics->radar_altitude.value < MIN_AUTOPILOT_HEIGHT)
		)
	{

		current_flight_dynamics->valid_last_frame_moving_collision_points = FALSE;

		current_flight_dynamics->valid_last_frame_fixed_collision_points = FALSE;

		//current_flight_dynamics->main_rotor_rpm.value = 100.0;
		//current_flight_dynamics->tail_rotor_rpm.value = 100.0;

		if (get_current_flight_dynamics_rotor_brake ())
		{

			current_flight_dynamics->main_rotor_rpm.value = 0.0;
			current_flight_dynamics->tail_rotor_rpm.value = 0.0;
		}

		//current_flight_dynamics->combined_engine_torque.value = 100.0;
		//current_flight_dynamics->left_engine_torque.value = 100.0;
		//current_flight_dynamics->right_engine_torque.value = 100.0;

		add_flight_path_action (current_flight_dynamics->position.x, current_flight_dynamics->position.z, FLIGHT_PATH_ACTION_USER_NAVIGATING);

		if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{

			set_current_flight_dynamics_rotor_brake (TRUE);

			current_flight_dynamics->input_data.collective.value = 0.0;
		}
		else
		{

			if ((!flag) ||
				(damage) ||
				(current_flight_dynamics->fuel_weight.value <= 0.0))
			{

				if ((!flag) && (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT)))
				{

					play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_OFF);
				}
			}
			else if (current_flight_dynamics->radar_altitude.value < MIN_AUTOPILOT_HEIGHT)
			{

				if (sfrand1 () < 0.0)
				{

					play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_TOO_LOW1);
				}
				else
				{

					play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_TOO_LOW2);
				}
			}
		}

		set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT, FALSE);
	}
	else
	{

		//
		// Set operational state
		//

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{

			entity
				*task,
				*cwp;

//			cwp = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_CURRENT_WAYPOINT);
			cwp = get_local_entity_current_waypoint (get_gunship_entity ());

			if (cwp)
			{

				task = get_local_entity_parent (cwp, LIST_TYPE_WAYPOINT);

				if (task)
				{

					switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
					{

						case ENTITY_SUB_TYPE_TASK_LANDING:
						{

							set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING);

							break;
						}

						case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
						{

							set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING_HOLDING);

							break;
						}

						case ENTITY_SUB_TYPE_TASK_TAKEOFF:
						{

							set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF);

							break;
						}
						case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
						{

							set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF_HOLDING);

							break;
						}
					}
				}
			}

			debug_log ("DYNAMICS: autopilot on");

			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_ON);

			set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT, TRUE);

			set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

			add_flight_path_action (current_flight_dynamics->position.x, current_flight_dynamics->position.z, FLIGHT_PATH_ACTION_AUTOPILOT_NAVIGATING);
		}
	}
	*/

	//if (valid_dynamics_autos_on (HOVER_HOLD_AUTO_PILOT))
	if (flag)
	{

		entity
			*task,
			*cwp;

		cwp = get_local_entity_current_waypoint (get_gunship_entity ());

		if (cwp)
		{

			task = get_local_entity_parent (cwp, LIST_TYPE_WAYPOINT);

			if (task)
			{

				switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
				{

					case ENTITY_SUB_TYPE_TASK_LANDING:
					{

						set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING);

						break;
					}

					case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
					{

						set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDING_HOLDING);

						break;
					}

					case ENTITY_SUB_TYPE_TASK_TAKEOFF:
					{

						set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF);

						break;
					}
					case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
					{

						set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF_HOLDING);

						break;
					}
				}
			}
		}

		debug_log ("DYNAMICS: autopilot on");

		set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT, TRUE);

		set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);

		add_flight_path_action (current_flight_dynamics->position.x, current_flight_dynamics->position.z, FLIGHT_PATH_ACTION_AUTOPILOT_NAVIGATING);
	}
	else
	{

		current_flight_dynamics->valid_last_frame_moving_collision_points = FALSE;

		current_flight_dynamics->valid_last_frame_fixed_collision_points = FALSE;

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{
			current_flight_dynamics->left_engine_rpm.max = 100.0;  // engine is always trying for 100% N2 RPM
			current_flight_dynamics->left_engine_n1_rpm.max = 110.0;
			current_flight_dynamics->left_engine_torque.max = 120.0;

			current_flight_dynamics->right_engine_rpm.max = no_right_engine ? 0.0 : 100.0;
			current_flight_dynamics->right_engine_n1_rpm.max = no_right_engine ? 0.0 : 110.0;
			current_flight_dynamics->right_engine_torque.max = no_right_engine ? 0.0 : 120.0;
		}

		add_flight_path_action (current_flight_dynamics->position.x, current_flight_dynamics->position.z, FLIGHT_PATH_ACTION_USER_NAVIGATING);
/*
		if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		{

			set_current_flight_dynamics_rotor_brake (TRUE);

			current_flight_dynamics->input_data.collective.value = 0.0;
		}
*/

		set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_current_flight_dynamics_auto_pilot (void)
{

	int
		flag;

	ASSERT (get_gunship_entity ());

	flag = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT);

	return flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_toggle_auto_pilot (event *ev)
{

	//if (get_current_flight_dynamics_auto_pilot ())
	if (valid_dynamics_autos_on (HOVER_HOLD_AUTO_PILOT))
	{

		set_current_flight_dynamics_auto_pilot (TRUE);
	}
	else
	{

		set_current_flight_dynamics_auto_pilot (FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_toggle_altitude_lock (event *ev)
{
/*
	if ((current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK) ||
		(!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT)) ||
		(current_flight_dynamics->dynamics_damage != DYNAMICS_DAMAGE_NONE) ||
		(get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT)) ||
		(current_flight_dynamics->sub_type == ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW) ||
		(current_flight_dynamics->sub_type == ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B))
	{

		debug_log ("DYNAMICS: altitude_lock off");

		if (current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK)
		{

			play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_ALTITUDE_HOLD_OFF);
		}

		set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
	}
	else
	{

		current_flight_dynamics->altitude.max = current_flight_dynamics->altitude.value - current_flight_dynamics->altitude.min;

		debug_log ("DYNAMICS: altitude_lock on at %f ft", current_flight_dynamics->altitude.max);

		set_current_flight_dynamics_auto_hover (HOVER_HOLD_ALTITUDE_LOCK);

		play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_ALTITUDE_HOLD_ON);
	}

*/

	if (valid_dynamics_autos_on (HOVER_HOLD_ALTITUDE_LOCK))
	{

		current_flight_dynamics->altitude.max = current_flight_dynamics->altitude.value - current_flight_dynamics->altitude.min;

		debug_log ("DYNAMICS: altitude_lock on at %f ft", current_flight_dynamics->altitude.max);

		set_current_flight_dynamics_auto_hover (HOVER_HOLD_ALTITUDE_LOCK);
	}
	else
	{

		debug_log ("DYNAMICS: altitude_lock off");

		set_current_flight_dynamics_auto_hover (HOVER_HOLD_NONE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_decrease_altitude_lock (event *ev)
{

	if (current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK)
	{

		if (get_global_gunship_side () == ENTITY_SIDE_BLUE_FORCE)
		{

			current_flight_dynamics->altitude.max -= ONE_FOOT;

			debug_log ("DYNAMICS: altitude_lock on at %f ft", feet (current_flight_dynamics->altitude.max));
		}
		else
		{

			current_flight_dynamics->altitude.max -= METRE;

			debug_log ("DYNAMICS: altitude_lock on at %f m", current_flight_dynamics->altitude.max);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_increase_altitude_lock (event *ev)
{

	if (current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK)
	{

		if (get_global_gunship_side () == ENTITY_SIDE_BLUE_FORCE)
		{

			current_flight_dynamics->altitude.max += ONE_FOOT;

			debug_log ("DYNAMICS: altitude_lock on at %f ft", feet (current_flight_dynamics->altitude.max));
		}
		else
		{

			current_flight_dynamics->altitude.max += METRE;

			debug_log ("DYNAMICS: altitude_lock on at %f m", current_flight_dynamics->altitude.max);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_takeoff (void)
{

	debug_log ("DYNAMICS: ---------------------------------- TakeOff ---------------------------------------------");

	current_flight_dynamics_landed_at_keysite = NULL;

	current_flight_dynamics->refueling = current_fuel_level = available_fuel = FALSE;

	current_flight_dynamics->repairing = current_flight_dynamics->damage_repair_time = FALSE;

	current_flight_dynamics->repairing_damage = DYNAMICS_DAMAGE_NONE;

	set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);

	set_client_server_entity_float_value (get_gunship_entity (), FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER, 0.0);

	transmit_entity_comms_message (ENTITY_COMMS_MOBILE_TAKEOFF, get_gunship_entity ());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_land (void)
{

	float
		xmin,
		xmax,
		zmin,
		zmax,
		actual_range;

	vec3d
		model_position;

	entity
		*keysite;

	//#if DEBUG_DYNAMICS >= 1

	debug_log ("DYNAMICS: ---------------------------------- Landed ----------------------------------------------");

	//#endif

	current_flight_dynamics_landed_at_keysite = NULL;

	/////////////////////////////////////////////////////////////////
//	dynamics_restore_damage_values ();
	/////////////////////////////////////////////////////////////////

	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
	{

		return;
	}

	set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAXIING);

	set_current_flight_dynamics_auto_pilot (FALSE);

	//
	// find out if landed near keysite
	//

	model_position.x = current_flight_dynamics->position.x;
	model_position.y = current_flight_dynamics->position.y;
	model_position.z = current_flight_dynamics->position.z;

	keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, get_global_gunship_side (), &model_position, 5 * KILOMETRE, &actual_range, TRUE, NULL);

	if (keysite)
	{

		object_3d_instance
			*inst3d;

		vec3d
			*keysite_pos;

		struct OBJECT_3D_BOUNDS
			*bounding_box;

		xmin = 0.0;
		xmax = 0.0;
		zmin = 0.0;
		zmax = 0.0;

		switch (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE))
		{

			case ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE:
			{

				float
					heading = 0.0;

				entity
					*ship;

				ship = get_local_entity_parent (keysite, LIST_TYPE_MOVEMENT_DEPENDENT);

				ASSERT (ship);
				ASSERT (get_local_entity_type (ship) == ENTITY_TYPE_SHIP_VEHICLE);

				heading = get_local_entity_float_value (ship, FLOAT_TYPE_HEADING);

				//
				// rotate model position into 'keysite space'
				//

				keysite_pos = get_local_entity_vec3d_ptr (ship, VEC3D_TYPE_POSITION);

				model_position.x = current_flight_dynamics->position.x - keysite_pos->x;
				model_position.y = current_flight_dynamics->position.y - keysite_pos->y;
				model_position.z = current_flight_dynamics->position.z - keysite_pos->z;

				model_position.x = model_position.x * cos (-heading) + model_position.z * sin (-heading);
				model_position.z = model_position.z * cos (-heading) - model_position.x * sin (-heading);

				inst3d = (object_3d_instance *) get_local_entity_ptr_value (ship, PTR_TYPE_INSTANCE_3D_OBJECT);

				bounding_box = get_object_3d_bounding_box_without_lines (inst3d->object_number);

				break;
			}
			case ENTITY_SUB_TYPE_KEYSITE_FARP:
			{

				keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);

				model_position.x = current_flight_dynamics->position.x - keysite_pos->x;
				model_position.y = current_flight_dynamics->position.y - keysite_pos->y;
				model_position.z = current_flight_dynamics->position.z - keysite_pos->z;

				bounding_box = get_object_3d_bounding_box_without_lines (get_local_entity_int_value (keysite, INT_TYPE_OBJECT_INDEX));

				xmin = -400.0;
				xmax = 400.0;
				zmin = -400.0;
				zmax = 400.0;

				break;
			}
			default:
			{

				keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);

				model_position.x = current_flight_dynamics->position.x - keysite_pos->x;
				model_position.y = current_flight_dynamics->position.y - keysite_pos->y;
				model_position.z = current_flight_dynamics->position.z - keysite_pos->z;

				bounding_box = get_object_3d_bounding_box_without_lines (get_local_entity_int_value (keysite, INT_TYPE_OBJECT_INDEX));

				// make sure that the airbase is at least 400 m radius
				xmin = min (bounding_box->xmin, -400.0f);
				xmax = max (bounding_box->xmax, 400.0f);
				zmin = min (bounding_box->zmin, -400.0f);
				zmax = max (bounding_box->zmax, 400.0f);

				break;
			}
		}

		if (((model_position.x > bounding_box->xmin + xmin) && (model_position.x < bounding_box->xmax + xmax)) &&
			((model_position.z > bounding_box->zmin + zmin) && (model_position.z < bounding_box->zmax + zmax)))
		{
			debug_log ("DYNAMICS: model within keysite area, repairing and refueling");

			current_flight_dynamics_landed_at_keysite = keysite;

			current_flight_dynamics->refueling = TRUE;
			current_flight_dynamics->repairing = TRUE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_vector_flight_model (void)
{

	static float
		velocity_z = 0.0;

	float
		heading,
		pitch,
		roll,
		accelerator,
		velocity_amount,
		heading_amount,
		roll_amount,
		pitch_amount,
		y_amount;

   matrix3x3
      delta_attitude,
      attitude;

	velocity_amount = 5.0;
	heading_amount = rad (2.0);
	pitch_amount = rad (2.0);
	roll_amount = rad (2.0);
	accelerator = 1.0;
	y_amount = 2.0;

   get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

   heading = 0.0;

   pitch = 0.0;

   roll = 0.0;

	if (check_key (DIK_RSHIFT))
	{

		accelerator = 10.0;
	}

	// velocity

	if (check_key (DIK_Q))
	{

		velocity_z += velocity_amount * accelerator;
	}

	if (check_key (DIK_A))
	{

		velocity_z -= velocity_amount * accelerator;
	}

	// altitude

	if (check_key (DIK_W))
	{

		current_flight_dynamics->position.y += y_amount * accelerator;
	}

	if (check_key (DIK_S))
	{

		current_flight_dynamics->position.y -= y_amount * accelerator;
	}

	// heading

	if (check_key (DIK_Z))
	{

		heading = -heading_amount * accelerator;
	}

	if (check_key (DIK_X))
	{

		heading = heading_amount * accelerator;
	}

	// pitch

	if (check_key (DIK_UP))
	{

		pitch = -pitch_amount * accelerator;
	}

	if (check_key (DIK_DOWN))
	{

		pitch = pitch_amount * accelerator;
	}

	// roll

	if (check_key (DIK_LEFT))
	{

		roll = -roll_amount * accelerator;
	}

	if (check_key (DIK_RIGHT))
	{

		roll = roll_amount * accelerator;
	}

	// get attitude matrix

  	get_3d_transformation_matrix (delta_attitude, heading, pitch, roll);

	multiply_matrix3x3_matrix3x3 (current_flight_dynamics->attitude, delta_attitude, attitude);





/*
	get_3d_transformation_matrix (attitude, heading, pitch, roll);

	multiply_matrix3x3_matrix3x3 (current_flight_dynamics->attitude, current_flight_dynamics->attitude, attitude);
*/

	current_flight_dynamics->position.x += current_flight_dynamics->attitude [2][0] * velocity_z * get_delta_time ();
	current_flight_dynamics->position.y += current_flight_dynamics->attitude [2][1] * velocity_z * get_delta_time ();
	current_flight_dynamics->position.z += current_flight_dynamics->attitude [2][2] * velocity_z * get_delta_time ();

	update_dynamics_external_values ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_dynamics_normalised_fuel_value (void)
{

	return (current_flight_dynamics->fuel_weight.value / current_flight_dynamics->fuel_weight.max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_lock_position (void)
{

	if (flight_dynamics_lock_position_flag)
	{

		current_flight_dynamics->position = current_flight_dynamics->old_position;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_keysite_currently_landed_at (void)
{

	if (current_flight_dynamics_landed_at_keysite)
	{

		return current_flight_dynamics_landed_at_keysite;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_keysite_currently_landed_at (entity *en)
{

	ASSERT (en);

	current_flight_dynamics_landed_at_keysite = en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float set_flight_dynamics_mass (void)
{

	current_flight_dynamics->mass.value = current_flight_dynamics->mass.min +
														(current_flight_dynamics->fuel_weight.value /* * current_flight_dynamics->fuel_weight.modifier */) +
														(current_flight_dynamics->weapon_mass.modifier * get_local_entity_weapon_load_weight (get_gunship_entity ()));

	return current_flight_dynamics->mass.value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_current_flight_dynamics_fuel_weight (void)
{

	if (!current_flight_dynamics)
	{

		return;
	}

	if (!get_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_FUEL))
	{
		float fuel_delta = current_flight_dynamics->fuel_weight.delta * get_delta_time ();
		// arneh - adjust for engine RPM.  Adjusted to 1 at 85% N1 RPM on both engines
		fuel_delta *= (current_flight_dynamics->left_engine_n1_rpm.value +
					   current_flight_dynamics->right_engine_n1_rpm.value) / 170.0;

		current_flight_dynamics->fuel_weight.value -= fuel_delta;

		if (current_flight_dynamics->fuel_weight.value <= 0.0)
		{

			set_current_flight_dynamics_auto_pilot (FALSE);
		}
		else if (current_flight_dynamics->fuel_weight.value <= 100.0)
		{

			static float
				time = 0.0;

			time -= get_delta_time ();

			if (time <= 0.0)
			{

				play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_FUEL_LOW);

				time = DYNAMICS_LOW_FUEL_SPEECH_TIME;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_current_flight_dynamics_flight_time (void)
{

	player_log_type
		*log;

	//
	// only increment flight time if :-
	// 1. flight model inititalised
	// 2. not landed
	//

	if ((!current_flight_dynamics) ||
		(!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT)))
	{

		return;
	}

	log = get_current_player_log ();

	inc_player_log_flying_seconds (get_global_gunship_side (), log, get_delta_time ());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dynamics_kill_model (dynamics_destroy_types type, entity	*aggressor)
{
	ASSERT (get_gunship_entity ());

	// if aggressor check if inv from weapons... otherwise check inv from collisions

	if (((aggressor) && (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INVULNERABLE_FROM_WEAPONS))) ||
			(!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INVULNERABLE_FROM_COLLISIONS)))
	{

		if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
		{
			kill_client_server_entity (get_gunship_entity ());

//			start_game_exit (GAME_EXIT_CRASH, FALSE);
		}
/*
		if (aggressor)
		{

			debug_log ("CO_DMG: storing in debrief that %s %s destroyed user",
							entity_type_names [get_local_entity_type (aggressor)],
							get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME));
		}
*/
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_flight_path_action (float x, float z, flight_path_action_type action)
{

	flight_path_data
		*flight_path;

	flight_path = (flight_path_data *) malloc_heap_mem (sizeof (flight_path_data));

	flight_path->x = x;
	flight_path->z = z;
	flight_path->action = action;

	flight_path->next = current_flight_dynamics->flight_path;

	current_flight_dynamics->flight_path = flight_path;

	debug_log ("DYNAMICS: added flight path data [%f, %f] action %s", x, z, flight_path_action_names [action]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_flight_path (void)
{

	flight_path_action_type
		action;

	if (current_flight_dynamics)
	{

		if (get_current_flight_dynamics_auto_pilot ())
		{

			action = FLIGHT_PATH_ACTION_AUTOPILOT_NAVIGATING;
		}
		else
		{

			action = FLIGHT_PATH_ACTION_USER_NAVIGATING;
		}

		add_flight_path_action (current_flight_dynamics->position.x, current_flight_dynamics->position.z, action);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int valid_dynamics_autos_on (dynamics_hover_hold_types type)
{

	int
		speech,
		damage,
		flag;

	damage = current_flight_dynamics->dynamics_damage;

	damage = damage & ~(DYNAMICS_DAMAGE_NONE |
								DYNAMICS_DAMAGE_FIRE_EXTINGUISHER |
								DYNAMICS_DAMAGE_FUEL_LEAK |
								DYNAMICS_DAMAGE_UNDERCARRIAGE |
								DYNAMICS_DAMAGE_LOW_OIL_PRESSURE |
								DYNAMICS_DAMAGE_AVIONICS);

	flag = TRUE;

	//
	// General conditions to turn hover hold ON
	// NB. All these must fail
	//

	speech = FALSE;

	if (damage)
	{

		flag = FALSE;
	}

	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
	{

		flag = FALSE;
	}

	if (current_flight_dynamics->fuel_weight.value <= 0.0)
	{

		flag = FALSE;
	}

	//
	//
	//

	switch (type)
	{

		case HOVER_HOLD_NORMAL:
		case HOVER_HOLD_STABLE:
		{
			if (current_flight_dynamics->auto_hover == type)
			{
				flag = FALSE;
				speech = TRUE;
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_OFF);
			}

			if (flag)
			{

				if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT))
				{

					set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT, FALSE);
				}
				else if (get_global_avionics_realism_level () > AVIONICS_REALISM_LEVEL_SIMPLE && current_flight_dynamics->velocity_z.value > knots_to_metres_per_second (20.0))
				{

					if (!speech)
					{

						if (sfrand1 () < 0.0)
						{

							play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_TOO_FAST1);
						}
						else
						{

							play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_TOO_FAST2);
						}
					}

					speech = TRUE;

					flag = FALSE;
				}
			}

			// if joystic is not centered don't engage
			if (get_global_cyclic_input () == JOYSTICK_INPUT)
			{
				// 030418 loke
				// implemented multiple joystick device selection

				int
					joystick_x_pos,
					joystick_y_pos;

				if (command_line_cyclic_joystick_index == -1)
				{
					joystick_x_pos = get_joystick_axis (current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_ROLL);
					joystick_y_pos = get_joystick_axis (current_flight_dynamics->input_data.cyclic_joystick_device_index, JOYSTICK_DEFAULT_AXIS_PITCH);
				}
				else
				{
					joystick_x_pos = get_joystick_axis (command_line_cyclic_joystick_index, command_line_cyclic_joystick_x_axis);
					joystick_y_pos = get_joystick_axis (command_line_cyclic_joystick_index, command_line_cyclic_joystick_y_axis);
				}

				if (((float) fabs (200.0 * joystick_x_pos) / (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM) > 10.0) ||
					((float) fabs (200.0 * joystick_y_pos) / (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM) > 10.0))
				{

					flag = FALSE;
				}
			}

			if (flag)
			{

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_HOVER_HOLD_ON);
			}

			break;
		}

		case HOVER_HOLD_ALTITUDE_LOCK:
		{

			if (current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK)
			{

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_ALTITUDE_HOLD_OFF);

				flag = FALSE;
			}

      //ataribaby 1/1/2009 enable ALT HOLD for Apache and Havoc
      /*
			if ((current_flight_dynamics->sub_type == ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW) ||
				(current_flight_dynamics->sub_type == ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B))
			{

				flag = FALSE;
			}
      */

			if (flag)
			{

				if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT))
				{

					set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT, FALSE);
				}

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_ALTITUDE_HOLD_ON);
			}

			break;
		}

		case HOVER_HOLD_AUTO_PILOT:
		{

			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT))
			{

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_OFF);

				speech = TRUE;

				flag = FALSE;
			}

			if ((flag) && (current_flight_dynamics->radar_altitude.value < MIN_AUTOPILOT_HEIGHT))
			{

				flag = FALSE;

				if (!speech)
				{

					if (sfrand1 () < 0.0)
					{

						play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_TOO_LOW1);
					}
					else
					{

						play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_TOO_LOW2);
					}
				}

				speech = TRUE;
			}

			if (flag)
			{

				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_AUTOPILOT_ON);
			}

			break;
		}

		case HOVER_HOLD_NONE:
		default:
		{
		}
	}

	return flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// arneh, july 06 - event handler functions for new engine keys
void flight_dynamics_start_apu_ev (event* ev)
{
	flight_dynamics_start_apu();
}

void flight_dynamics_start_engine_ev (event* ev)
{
	if (ev->key == DIK_COMMA)
		flight_dynamics_start_engine(1);
	else if (ev->key == DIK_PERIOD)
		flight_dynamics_start_engine(2);
}

void flight_dynamics_throttle_engine_ev (event* ev)
{
	int engine = 1;
	int rpm_delta = 0;

	if (ev->key == DIK_COMMA)
		engine = 1;
	else if (ev->key == DIK_PERIOD)
		engine = 2;

	if (ev->modifier == MODIFIER_NONE)
		rpm_delta = 10;
	else if (ev->modifier == MODIFIER_LEFT_SHIFT)
		rpm_delta = -10;

	flight_dynamics_throttle_engine(engine, rpm_delta);
}

void flight_dynamics_increase_governor_rpm(event* ev)
{
	if (current_flight_dynamics->main_rotor_governor_rpm < 90.0)
		current_flight_dynamics->main_rotor_governor_rpm += 10.0;
	else
		current_flight_dynamics->main_rotor_governor_rpm = min(97.5, current_flight_dynamics->main_rotor_governor_rpm + 2.5);
}

void flight_dynamics_decrease_governor_rpm(event* ev)
{
	if (current_flight_dynamics->main_rotor_governor_rpm <= 90.0)
		current_flight_dynamics->main_rotor_governor_rpm = max(70.0, current_flight_dynamics->main_rotor_governor_rpm - 10.0);
	else
		current_flight_dynamics->main_rotor_governor_rpm -= 2.5;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_throttle_dynamics_inputs ()
{
	int joyval;
	float input;
	
	if (command_line_throttle_joystick_index != -1)
		joyval = get_joystick_axis (command_line_throttle_joystick_index, command_line_throttle_joystick_axis);
	else
		return;

	if (command_line_reverse_throttle)
		joyval *= -1;
	
	input = 0.5 + (float) joyval / (float) (JOYSTICK_AXIS_MAXIMUM - JOYSTICK_AXIS_MINIMUM);

	if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
	{
		current_flight_dynamics->main_rotor_governor_rpm = bound(70.0 + 27.5 * input, 70.0, 97.5);
	}
	else
	{
		if (current_flight_dynamics->left_engine_n1_rpm.value >= (current_flight_dynamics->engine_idle_rpm - 5.0) && 
				current_flight_dynamics->left_engine_n1_rpm.max >= current_flight_dynamics->engine_idle_rpm)
			current_flight_dynamics->left_engine_n1_rpm.max = bound(current_flight_dynamics->engine_idle_rpm + input * (110.0 - current_flight_dynamics->engine_idle_rpm), current_flight_dynamics->engine_idle_rpm, 110.0);

		if (get_global_gunship_type() != GUNSHIP_TYPE_KIOWA && current_flight_dynamics->right_engine_n1_rpm.value >= (current_flight_dynamics->engine_idle_rpm - 5.0) && 
				current_flight_dynamics->right_engine_n1_rpm.max >= current_flight_dynamics->engine_idle_rpm)
			current_flight_dynamics->right_engine_n1_rpm.max = bound(current_flight_dynamics->engine_idle_rpm + input * (110.0 - current_flight_dynamics->engine_idle_rpm), current_flight_dynamics->engine_idle_rpm, 110.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_start_engine (int engine_number)
{
	dynamics_float_variable* engine_rpm;

	// can only start one engine at a time, and not when rotor brake is active
	if (current_flight_dynamics->rotor_brake || current_flight_dynamics->left_engine_starter_active || current_flight_dynamics->right_engine_starter_active)
		return;

	ASSERT (engine_number >= 1 && engine_number <= 2);

	if (get_global_gunship_type() == GUNSHIP_TYPE_KIOWA)
	{
		engine_number = 1;
	}

	if (engine_number == 1)
	{
		engine_rpm = &current_flight_dynamics->left_engine_n1_rpm;
		if (engine_rpm->value > 60)
			return;
		current_flight_dynamics->left_engine_starter_active = TRUE;
	}
	else if (engine_number == 2)
	{
		engine_rpm = &current_flight_dynamics->right_engine_n1_rpm;
		if (engine_rpm->value > 60)
			return;
		current_flight_dynamics->right_engine_starter_active = TRUE;
	}
	else
		return;

	switch (get_global_gunship_type())
	{
	case GUNSHIP_TYPE_KIOWA:
	case GUNSHIP_TYPE_HIND:
	case GUNSHIP_TYPE_HAVOC:
	case GUNSHIP_TYPE_HOKUM:
	case GUNSHIP_TYPE_KA50:
		if (engine_rpm->value < 5.0)
			current_flight_dynamics->engine_start_timer = 4.5;
		break;
	}

	engine_rpm->max = max(engine_rpm->max, 20.0f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_throttle_engine (int engine_number, int rpm_delta)
{
	static int double_count[2] = {0, 0};

	dynamics_float_variable *engine_rpm, *engine_temp;

	ASSERT (engine_number == 1 || engine_number == 2);

	if (get_global_gunship_type() == GUNSHIP_TYPE_KIOWA)
	{
		engine_number = 1;
	}

	if (engine_number == 1)
	{
		engine_rpm = &current_flight_dynamics->left_engine_n1_rpm;
		engine_temp = &current_flight_dynamics->left_engine_temp;
	}
	else if (engine_number == 2)
	{
		engine_rpm = &current_flight_dynamics->right_engine_n1_rpm;
		engine_temp = &current_flight_dynamics->right_engine_temp;
	}
	else
		return;

	if (engine_rpm->damaged)
	{
		engine_rpm->max = 0.0;
		return;
	}

	// double throttle down with RPM under 62% shuts down engine
	if (((engine_rpm->value < (current_flight_dynamics->engine_idle_rpm + 2.0) && engine_rpm->max <= current_flight_dynamics->engine_idle_rpm)
		 || get_global_gunship_type() == GUNSHIP_TYPE_HIND)
		&& rpm_delta < 0.0)
	{
		if (double_count[engine_number-1] < 0)
		{
			engine_rpm->max = 0.0;
			if (engine_rpm->value > 25.0)
				play_helicopter_winding_rotor_sounds(get_gunship_entity(), -1, engine_number);
			double_count[engine_number-1] = 0;
		}
		else if(engine_rpm->max > 0.0)
			double_count[engine_number-1] = -1;
		else
			double_count[engine_number-1] = 0;

		return;
	}
	else if (engine_rpm->value < (current_flight_dynamics->engine_idle_rpm - 5.0) && rpm_delta > 0.0)
	{
		// igniting engine
		if (double_count[engine_number-1] > 0)
		{
			if (current_flight_dynamics->apu_rpm.value > 80.0 && engine_rpm->value > 12.0)
			{
				if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
					engine_rpm->max = 100.0;
				else
					engine_rpm->max = current_flight_dynamics->engine_idle_rpm;

				engine_temp->min += 250.0;
				play_helicopter_winding_rotor_sounds(get_gunship_entity(), 1, engine_number);
			}

			double_count[engine_number-1] = 0;
		}
		else if(engine_rpm->max < current_flight_dynamics->engine_idle_rpm)
			double_count[engine_number-1] = 1;
		else
			double_count[engine_number-1] = 0;

		return;
	}
	else
		double_count[engine_number-1] = 0;

	// throttles have no response until engine has powered up to at least 55%
	if (engine_rpm->value < (current_flight_dynamics->engine_idle_rpm - 5.0) && rpm_delta > 0.0)
		return;

	engine_rpm->max = bound(engine_rpm->max + rpm_delta, current_flight_dynamics->engine_idle_rpm, 110.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_dynamics_start_apu (void)
{
	if (current_flight_dynamics->apu_rpm.max > 0.0)
	{
		current_flight_dynamics->apu_rpm.max = 0.0;
		current_flight_dynamics->left_engine_starter_active = FALSE;
		current_flight_dynamics->right_engine_starter_active = FALSE;
		current_flight_dynamics->engine_start_timer = 0.0;
	}
	else
		current_flight_dynamics->apu_rpm.max = 100.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// arneh, july 06 - modelling of APU added
void update_apu_rpm_dynamics (void)
{
	if (!current_flight_dynamics->apu_rpm.damaged)
		current_flight_dynamics->apu_rpm.delta = bound(current_flight_dynamics->apu_rpm.max - current_flight_dynamics->apu_rpm.value, -30.0, 30.0);
	else
		current_flight_dynamics->apu_rpm.delta = -100.0;
	current_flight_dynamics->apu_rpm.value = bound(current_flight_dynamics->apu_rpm.value + current_flight_dynamics->apu_rpm.delta * get_model_delta_time(), 0.0, 100.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// arneh, july 06 - modelling of engine temperature added
void update_engine_temperature_dynamics (int engine_number)
{
	unsigned int engine_fire;
	dynamics_float_variable *n1_rpm, *n2_rpm, *engine_torque, *engine_temp;

	ASSERT(engine_number == 1 || engine_number == 2);

	if (get_global_gunship_type() == GUNSHIP_TYPE_KIOWA)
	{
		engine_number = 1;
	}

	if (engine_number == 1)
	{
		n1_rpm = &current_flight_dynamics->left_engine_n1_rpm;
		engine_temp = &current_flight_dynamics->left_engine_temp;
		n2_rpm = &current_flight_dynamics->left_engine_rpm;
		engine_fire = DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE;
		engine_torque = &current_flight_dynamics->left_engine_torque;
	}
	else if (engine_number == 2)
	{
		n1_rpm = &current_flight_dynamics->right_engine_n1_rpm;
		engine_temp = &current_flight_dynamics->right_engine_temp;
		n2_rpm = &current_flight_dynamics->right_engine_rpm;
		engine_fire = DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE;
		engine_torque = &current_flight_dynamics->right_engine_torque;
	}
	else
		return;

	ASSERT(engine_temp->value >= 0.0 && engine_temp->value <= 1500.0);

	// fire dies out if engine temp gets below 500 degrees (you have to stop the engine for that to happen)
	if (engine_temp->value < 500.0)
		current_flight_dynamics->dynamics_damage &= ~engine_fire;

	if (n1_rpm->max == 0.0)  // engine shutdown
	{
		engine_temp->min = 35.0;
		if (current_flight_dynamics->dynamics_damage & engine_fire)
			engine_temp->delta = bound((engine_temp->min - engine_temp->value) * 0.03, -30.0, 200.0);
		else
			engine_temp->delta = bound((engine_temp->min - engine_temp->value) * 0.03, -10.0, 200.0);
	}
	else if (n1_rpm->max == 20.0)  // no ignition, under APU power
	{
		engine_temp->min = 45.0;
		engine_temp->delta = bound((engine_temp->min - engine_temp->value) * 0.20, -20.0, 200.0);
	}
	else  // ignition
	{
		float rpm_factor;

//		engine_temp->value = max(engine_temp->value, 500.0);

		rpm_factor = 400.0 + (n1_rpm->value * n1_rpm->value * 0.035);
		if (n1_rpm->value > n2_rpm->value)  // should only happen during startup, or demanding really much from engine
			rpm_factor += (n1_rpm->value - n2_rpm->value) * 1.0;

		if (engine_torque->value > 100.0)   // increase temp more when overtorqueing
			rpm_factor += (engine_torque->value - 100.0) * 3.0;

		engine_temp->min = (1.0 - (0.5 * get_model_delta_time())) * engine_temp->min + 0.5 * get_model_delta_time() * rpm_factor;

		engine_temp->delta = bound((engine_temp->min - engine_temp->value) * 0.5, -20.0, 1000.0);

		// increase temp extra if engine on fire
		if (current_flight_dynamics->dynamics_damage & engine_fire)
			engine_temp->delta += 20.0;
	}

	engine_temp->value += engine_temp->delta * get_model_delta_time();

	if (current_flight_dynamics->dynamics_options.dynamics_options_over_torque)
		engine_temp->value = bound(engine_temp->value, 0.0, 1500.0);
	else
		engine_temp->value = bound(engine_temp->value, 0.0, 800.0);

	// if temp above 820 degrees, randomly damage engine. probability depending on temperature
	if (engine_temp->value > 820.0 && current_flight_dynamics->dynamics_options.dynamics_options_over_torque)
	{
		int probability = 5.0 * (int)(bound(1020.0 - engine_temp->value, 1.0, 200.0) / get_model_delta_time());
		if ((rand16() % (int)probability) == 0)
			dynamics_damage_model (engine_fire, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_engine_start_rpm(float* rpm)
{
	if (current_flight_dynamics->engine_start_timer > 3.0)
	{
		current_flight_dynamics->engine_start_timer -= get_model_delta_time();

		if (current_flight_dynamics->engine_start_timer <= 3.0)
			*rpm += 4.0;

		return;
	}

	*rpm -= sin(-current_flight_dynamics->engine_start_timer * PI * 6) * current_flight_dynamics->engine_start_timer * 1.5;
	current_flight_dynamics->engine_start_timer -= get_model_delta_time();
	*rpm += sin(-current_flight_dynamics->engine_start_timer * PI * 6) * current_flight_dynamics->engine_start_timer * 1.5;
}

void update_engine_rpm_dynamics (int engine_number)
{
	/* arneh - july 2006
	 * Ok, here's how the engine dynamics works now.  N1 (or NG) is the gas
	 * turbine which controls the amount of air/fuel which is combusted in the
	 * engine, and hence how much power it makes.  N2 (or NP, or in the code
	 * simply refered to as engine_rpm) is the power turbine which converts
	 * the combustion energy into shaft rotation.
	 *
	 * The N2 tubine is directly connected to the rotor (through a gearbox which
	 * reduces the real RPM from somewhere around 20,000 RPM to rotor RPM
	 * of around 300 RPM.  Left to itself the rotor and N2 RPM will drop under load
	 * and increase with less load.  The engine tries to keep N2 RPM constant at
	 * 100%, it does this by varying N1 speed (i.e. how much energy is produced by the
	 * engine).  However, changing turbine speed is not instant, and even
	 * when N1 speed has changed it might take a little longer before the extra
	 * energy reaches the N2 turbine and is converted into shaft power.  Hence
	 * it might not be able to keep N2 speed at exactly 100% at all times, especally
	 * initially after sudden changes of rotor drag (i.e. by changing rotor pitch
	 * suddenly (fast pulling collective), or by sudden heavy rotor load (increase
	 * in g-force by hard manouvering).
	 *
	 * The values are used as follow:
	 * *engine_rpm.value : actual RPM
	 * *engine_n1_rpm.max : max allowed rpm of N1 engine.  Is directly controlled
	 *    by pilot by use of throttle
	 * *engine_n1_rpm.min : RPM engine control system has demanded.  Always less then max.
	 * *rpm_delta : change of RPM in percent per second.  Controled by engine control system
	 * apu_rpm.max : APU RPM commanded by pilot (100% when APU on, 0% when off)
	 */


	float collect;
	dynamics_float_variable *n1_rpm, *n2_rpm, *engine_torque;
	short engine_damage;
	int starter_active;

	ASSERT(engine_number == 1 || engine_number == 2);

	if (get_global_gunship_type() == GUNSHIP_TYPE_KIOWA)
	{
		engine_number = 1;
	}

	collect = (current_flight_dynamics->input_data.collective.value / 120.0);
	collect = max (1.0f, collect);

	if (engine_number == 1)
	{
		n1_rpm = &current_flight_dynamics->left_engine_n1_rpm;
		n2_rpm = &current_flight_dynamics->left_engine_rpm;
		engine_damage = current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LEFT_ENGINE;
		engine_torque = &current_flight_dynamics->left_engine_torque;
		starter_active = current_flight_dynamics->left_engine_starter_active;
	}
	else if (engine_number == 2)
	{
		n1_rpm = &current_flight_dynamics->right_engine_n1_rpm;
		n2_rpm = &current_flight_dynamics->right_engine_rpm;
		engine_damage = current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_RIGHT_ENGINE;
		engine_torque = &current_flight_dynamics->right_engine_torque;
		starter_active = current_flight_dynamics->right_engine_starter_active;
	}
	else
		return;

	ASSERT(engine_torque->max > 0.0);
	// model N2 RPM as function of N1 RPM and torque
	{
		float torque_ratio, surplus_energy;

		float n1_power_ratio = (n1_rpm->value - current_flight_dynamics->engine_idle_rpm + 5.0) / (100.0 - current_flight_dynamics->engine_idle_rpm + 5.0);  // might be negative
		float n1_surplus;

		torque_ratio = (0.8 * engine_torque->value / engine_torque->max) + 0.2;
		surplus_energy = n1_power_ratio - torque_ratio;

		n1_surplus = ((max(n1_rpm->value - 25.0, 0.0) * 1.33) - n2_rpm->value);

//		if (n1_rpm->value > n2_rpm->value)
		if (n1_surplus > 0.0)
			surplus_energy += n1_surplus * 0.5;

		n2_rpm->delta = surplus_energy * 30.0;
		n2_rpm->value = bound(n2_rpm->value + n2_rpm->delta * get_model_delta_time (), 0.0, 110.0);
	}

	if (n1_rpm->value > current_flight_dynamics->engine_idle_rpm - 5.0)
	{
		float n2_delta, n1_delta;

		if (current_flight_dynamics->apu_rpm.max > 0.0)
		{
			// shut down engine starter if engine is running on own power
			if (n1_rpm->value > current_flight_dynamics->engine_idle_rpm - 1.0)
				starter_active = FALSE;
		}

		// figure out how much power we need
		n2_delta = current_flight_dynamics->main_rotor_governor_rpm - n2_rpm->value;  // this is how much we're trying to adjust N2 RPM
		n2_delta -= 2 * n2_rpm->delta;   // try predicting were N2 RPM is heading
		if (n2_rpm->value > n2_rpm->max) // be more aggresive about not going over 100% N2 RPM
			n1_delta = 3 * n2_delta;
		else
			n1_delta = n2_delta;

		if (current_flight_dynamics->dynamics_options.dynamics_options_over_torque)
			n1_rpm->min = bound(n1_rpm->value + n1_delta, current_flight_dynamics->engine_idle_rpm, 110.0);
		else
			n1_rpm->min = bound(n1_rpm->value + n1_delta, current_flight_dynamics->engine_idle_rpm, 100.0);

		n1_rpm->delta = min(n1_rpm->max, n1_rpm->min) - n1_rpm->value;
		n1_rpm->delta = bound (n1_rpm->delta, -8.0, 8.0);
	}
	else // in the realm of the APU
	{
		float delta = 0.0;

		if (current_flight_dynamics->apu_rpm.max == 0.0)  // engine not capable of keeping RPM without APU under 55% RPM
		{
			n1_rpm->max = 0.0;
			current_flight_dynamics->left_engine_starter_active = FALSE;
			current_flight_dynamics->right_engine_starter_active = FALSE;
			current_flight_dynamics->engine_start_timer = 0.0;
		}

		delta = n1_rpm->max - n1_rpm->value;
		if (delta < 0.0 || current_flight_dynamics->engine_start_timer > 3.0)
			n1_rpm->delta = bound(delta, -3.0, 0.0);
		else
		{
			float apu_contribution = 2.0 * current_flight_dynamics->apu_rpm.value * 0.01;

			if (n1_rpm->max < current_flight_dynamics->engine_idle_rpm)  // only APU
				n1_rpm->delta = min(apu_contribution, delta);
			else  // engine itself is helping
				n1_rpm->delta = min(delta, 1.0f + apu_contribution);
		}
	}

	//
	// damaged or out of fuel
	//

	if (n2_rpm->damaged)
	{
		n1_rpm->max = 0.0;
		n1_rpm->value -= n1_rpm->value * get_model_delta_time();
	}
	else
	{
		if (current_flight_dynamics->fuel_weight.value <= 0.0)
			n1_rpm->delta = -10.0;

		n1_rpm->value += n1_rpm->delta * get_model_delta_time ();

		if (starter_active && current_flight_dynamics->engine_start_timer > 0.0)
			animate_engine_start_rpm(&n1_rpm->value);

		n1_rpm->value = bound(n1_rpm->value, 0.0, 110.0);
	}

	if (engine_number == 1)
		current_flight_dynamics->left_engine_starter_active = starter_active;
	else
		current_flight_dynamics->right_engine_starter_active = starter_active;
}

// arneh, july 2006 - create vibration effect on rotor
void create_rotor_vibration(float force)
{
	static float time = 0;
	static int step = 0;
	float rpm, rotor_radius;

	float interval = 0.125;

	vec3d position,	direction;

	if (!get_gunship_entity ())
		return;
	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT))
		return;

	rpm = current_flight_dynamics->main_rotor_rpm.value / 100;
	rotor_radius = aircraft_database [get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ENTITY_SUB_TYPE)].main_rotor_radius;	
		
	force = bound (force, -2.5, 2.5) * rpm;

	// to create vibration we rotate a force around the rotor disk, moving it
	// a quarter rotation every step
	if (step == 0 || step == 2)
		position.x = rotor_radius;
	else
		position.x = -rotor_radius;

	if (step < 2)
		position.z = rotor_radius;
	else
		position.z = -rotor_radius;

	position.y = 0.0;

	time += get_model_delta_time() * rpm;
	// increase step every 0.125 seconds
	if (time > interval)
	{
		step++;
		if (step >= 4)
			step = 0;

		time = 0.0;
	}

	direction.x = 0.0;
	direction.y = current_flight_dynamics->rotor_rotation_direction;
	direction.z = 0.0;

	add_dynamic_force ("vibration", force, 0.0, &position, &direction, FALSE);
}

	// smooth vibrations /thealx/
void create_advanced_rotor_vibration(float force, int damaged)
{
	vec3d position,	direction;
	static float loop;
	float rpm, rotor_radius;

	if (!get_gunship_entity ())
		return;

	rpm = current_flight_dynamics->main_rotor_rpm.value / 100;
	rotor_radius = aircraft_database [get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ENTITY_SUB_TYPE)].main_rotor_radius;	
	
	if (damaged)
		force = bound (force, -2.5, 2.5) * rpm * rpm / rotor_radius * 10;

	loop += get_model_delta_time() * current_flight_dynamics->main_rotor_rpm.value * current_flight_dynamics->rotor_rotation_direction / 3;

	if (loop > PI2)
		loop -= PI2;
	else if (loop < - PI2)
		loop += PI2;

	position.x = sin(loop) * rotor_radius;
	position.z = cos(loop) * rotor_radius;
	position.y = 0.0;

	direction.x = position.x;
	direction.y = - damaged * rotor_radius / (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT) ? 2 : 10);
	direction.z = position.z;

	add_dynamic_force ("Main rotor vibration", force, 0.0, &position, &direction, FALSE);
	
	if (frand1() < (0.0001 * rpm) && damaged == TRUE)
		dynamics_damage_model(DYNAMICS_DAMAGE_MAIN_ROTOR, FALSE);
}

#ifdef DEBUG
// arneh - a few functions used for debugging by artificually introducing effects
// by pressing debugging keys
void debug_dynamics_event1(event* ev)
{
	debug_log("debug event 1");
	command_line_tacview_logging = 0;
}

void debug_dynamics_event2(event* ev)
{
	debug_log("debug event 2");
	command_line_tacview_logging = 1;
}

void debug_dynamics_event3(event* ev)
{
	debug_log("debug event 3");
	command_line_tacview_logging = 3;
}

void debug_dynamics_event4(event* ev)
{
	debug_log("debug event 4");
	dynamics_damage_model(DYNAMICS_DAMAGE_MAIN_ROTOR_BLADE, FALSE);
}
#endif // DEBUG
