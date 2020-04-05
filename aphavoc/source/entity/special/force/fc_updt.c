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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NB: 	for criteria, all success criteria must be met for the campaign to be completed successfully.
//			Any failures and the campaign will be failed instantly.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define CAMPAIGN_COMPLETION_TIMER 5

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
/*
	int
		loop;

	float
		objective_sectors_percentage,
		force_percentage,
		total_forces,
		this_force;

	char
		buffer [1024];

	force
		*enemy_force_raw = nullptr,
		*raw = nullptr;

	entity
		*allied_force = nullptr,
		*enemy_force = nullptr;

	campaign_result_types
		campaign_status;

	campaign_criteria_type
		*result_campaign_criteria = nullptr,
		*this_campaign_criteria = nullptr;

	player_log_type
		*log = nullptr;

	int
		success_required_count,
		success_achieved_count;

	allied_force = en;

	raw = get_local_entity_data (en);

	raw->sleep -= get_delta_time ();

	success_required_count = 0;

	success_achieved_count = 0;

	if (raw->sleep <= 0.0)
	{

		raw->sleep = CAMPAIGN_COMPLETION_TIMER;

		//
		// work out total force percentage
		//

		total_forces = 0;

		this_force = 0;

		enemy_force = get_local_force_entity (get_enemy_side (raw->side));

		enemy_force_raw = get_local_entity_data (enemy_force);

		for (loop = FORCE_INFO_CATAGORY_ARMED_FIXED_WING; loop < NUM_FORCE_INFO_CATAGORIES; loop ++)
		{

			total_forces += raw->force_info_current_hardware [loop] + enemy_force_raw->force_info_current_hardware [loop];

			this_force += raw->force_info_current_hardware [loop];
		}

		force_percentage = 0.0;

		if (total_forces)
		{

			force_percentage = this_force / total_forces;
		}

		if (force_percentage != raw->force_percentage)
		{

			set_client_server_entity_float_value (en, FLOAT_TYPE_FORCE_PERCENTAGE, force_percentage);
		}

		//
		// assess completion. (also work out objective_sectors_percentage and time_percentage)
		//

		campaign_status = CAMPAIGN_CRITERIA_RESULT_NONE;

		this_campaign_criteria = raw->campaign_criteria;

  		while (this_campaign_criteria)
		{

			if ( this_campaign_criteria->result == CAMPAIGN_CRITERIA_RESULT_SUCCESS )
			{

				success_required_count++;
			}

			switch (this_campaign_criteria->criteria_type)
			{

				case CAMPAIGN_CRITERIA_BALANCE_OF_POWER:
				{

					this_campaign_criteria->count = (int) (raw->force_percentage * 100.0);


					if (this_campaign_criteria->count >= this_campaign_criteria->goal)
					{

						if (campaign_status != CAMPAIGN_CRITERIA_RESULT_FAIL)
						{

							campaign_status = this_campaign_criteria->result;

							result_campaign_criteria = this_campaign_criteria;

							if ( this_campaign_criteria->result == CAMPAIGN_CRITERIA_RESULT_SUCCESS )
							{

								success_achieved_count++;
							}

							#if DEBUG_MODULE

							debug_log ("FC_UPDT: Met Campaign criteria %s type %d, goal %d, count %d to %s",
										campaign_criteria_names [this_campaign_criteria->criteria_type],
										this_campaign_criteria->type,
										this_campaign_criteria->goal,
										this_campaign_criteria->count,
										campaign_result_names [this_campaign_criteria->result]);

							#endif
						}
					}

					break;
				}
				case CAMPAIGN_CRITERIA_CAPTURED_SECTORS:
				{

					objective_sectors_percentage = 1.0;

					if (this_campaign_criteria->goal != 0)
					{

						objective_sectors_percentage = (float) this_campaign_criteria->count / this_campaign_criteria->goal;
					}

					if (objective_sectors_percentage != raw->objective_sectors_percentage)
					{

						set_client_server_entity_float_value (en, FLOAT_TYPE_OBJECTIVE_SECTORS_PERCENTAGE, objective_sectors_percentage);

						set_client_server_entity_int_value (en, INT_TYPE_OBJECTIVE_SECTORS_HELD, this_campaign_criteria->count);

						set_client_server_entity_int_value (en, INT_TYPE_OBJECTIVE_SECTORS_REQUIRED, this_campaign_criteria->goal);
					}

					// intentional follow through...
				}
				case CAMPAIGN_CRITERIA_COMPLETED_TASKS:
				case CAMPAIGN_CRITERIA_DESTROYED_ALLIED_OBJECTS:
				case CAMPAIGN_CRITERIA_DESTROYED_ENEMY_OBJECTS:
				case CAMPAIGN_CRITERIA_ENEMY_FIRED:
				case CAMPAIGN_CRITERIA_FAILED_TASKS:
				case CAMPAIGN_CRITERIA_LOST_SECTORS:
				case CAMPAIGN_CRITERIA_REACHED_WAYPOINTS:
				case CAMPAIGN_CRITERIA_SECTOR_REACHED:
				case CAMPAIGN_CRITERIA_SPECIAL_KILLS:
				case CAMPAIGN_CRITERIA_SURRENDERED_SIDES:
				{

					if (this_campaign_criteria->valid)
					{

						if (this_campaign_criteria->count >= this_campaign_criteria->goal)
						{

							if (campaign_status != CAMPAIGN_CRITERIA_RESULT_FAIL)
							{

								campaign_status = this_campaign_criteria->result;

								result_campaign_criteria = this_campaign_criteria;
							}

							if ( this_campaign_criteria->result == CAMPAIGN_CRITERIA_RESULT_SUCCESS )
							{

								success_achieved_count++;
							}

							#if DEBUG_MODULE

							debug_log ("FC_UPDT: Met Campaign criteria %s type %d, goal %d, count %d to %s",
										campaign_criteria_names [this_campaign_criteria->criteria_type],
										this_campaign_criteria->type,
										this_campaign_criteria->goal,
										this_campaign_criteria->count,
										campaign_result_names [this_campaign_criteria->result]);

							#endif
						}
					}

					break;
				}

				case CAMPAIGN_CRITERIA_TIME_DURATION:
				{

					float
						this_time,
						elapsed_hours,
						elapsed_minutes,
						elapsed_seconds;

					session
						*session_raw = nullptr;

					if (this_campaign_criteria->valid)
					{

						session_raw = get_local_entity_data (get_session_entity ());

						//
						// calculate time_percentage
						//

						this_time = get_time_of_day (this_campaign_criteria->hours, this_campaign_criteria->minutes, this_campaign_criteria->seconds);

						if (this_campaign_criteria->result == CAMPAIGN_CRITERIA_RESULT_SUCCESS)
						{

							raw->time_percentage = 0.0;

							if (session_raw->elapsed_time_of_day != 0)
							{

								raw->time_percentage = this_time / session_raw->elapsed_time_of_day;
							}
						}
						else
						{

							raw->time_percentage = 1.0;

							if (session_raw->elapsed_time_of_day != 0)
							{

								raw->time_percentage = 1.0 - (this_time / session_raw->elapsed_time_of_day);
							}
						}

						//
						// check time criteria
						//

						get_digital_clock_values (session_raw->elapsed_time_of_day, &elapsed_hours, &elapsed_minutes, &elapsed_seconds);

						#if DEBUG_MODULE

						debug_log ("FC_UPDT: Campaign criteria %s hours %02f, minutes %02f, seconds %02f to %s",
											campaign_criteria_names [this_campaign_criteria->criteria_type],
											this_campaign_criteria->hours - elapsed_hours,
											this_campaign_criteria->minutes - elapsed_minutes,
											this_campaign_criteria->seconds - elapsed_seconds,
											campaign_result_names [this_campaign_criteria->result]);

						#endif

						if (session_raw->elapsed_days >= this_campaign_criteria->days)
						{

							if (elapsed_hours >= this_campaign_criteria->hours)
							{

								if (elapsed_minutes >= this_campaign_criteria->minutes)
								{

									if (elapsed_seconds >= this_campaign_criteria->seconds)
									{

										if (campaign_status != CAMPAIGN_CRITERIA_RESULT_FAIL)
										{

											campaign_status = this_campaign_criteria->result;

											result_campaign_criteria = this_campaign_criteria;
										}

										//
										// DEBUG - SHOULD THIS JUST BE SUCCESS REGARDLESS OF OTHER CRITERIA ?????
										//

										if ( this_campaign_criteria->result == CAMPAIGN_CRITERIA_RESULT_SUCCESS )
										{

											success_achieved_count++;
										}
									}
								}
							}
						}
					}

					break;
				}

				default:
				{

					debug_fatal ("FC_UPDT: undefined campaign critera type %s", campaign_criteria_names [this_campaign_criteria->criteria_type]);
				}
			}

			//
			// If any of the result are FAIL then stop
			//

			if (campaign_status == CAMPAIGN_CRITERIA_RESULT_FAIL)
			{

  				break;
			}

			this_campaign_criteria = this_campaign_criteria->next;
		}

		//
		// Results - if we have success set, count em up.
		//

		if ( campaign_status == CAMPAIGN_CRITERIA_RESULT_SUCCESS )
		{

			if ( success_achieved_count < success_required_count )
			{

				campaign_status = CAMPAIGN_CRITERIA_RESULT_NONE;
			}
		}

		log = get_current_player_log ();

		if (campaign_status == CAMPAIGN_CRITERIA_RESULT_SUCCESS)
		{

			if (result_campaign_criteria->experience_variable)
			{

				*result_campaign_criteria->experience_variable += result_campaign_criteria->experience_points;

				#if DEBUG_MODULE

				debug_log ("FC_UPDT: awarding %d experience points", result_campaign_criteria->experience_points);

				#endif
			}

			if (result_campaign_criteria->rank_variable)
			{

				*result_campaign_criteria->rank_variable += result_campaign_criteria->rank_points;

				#if DEBUG_MODULE

				debug_log ("FC_UPDT: awarding %d rank points", result_campaign_criteria->rank_points);

				#endif
			}

			if (get_game_type () == GAME_TYPE_CAMPAIGN)
			{
				sprintf (buffer, "Campaign completed successfully by %s", entity_side_names [raw->side]);

				inc_player_log_successful_tours (get_global_gunship_side (), log);
			}
		}
		else if (campaign_status == CAMPAIGN_CRITERIA_RESULT_FAIL)
		{

			if (get_game_type () == GAME_TYPE_CAMPAIGN)
			{
				sprintf (buffer, "Campaign completed unsuccessfully by %s", entity_side_names [raw->side]);

				inc_player_log_failed_tours (get_global_gunship_side (), log);
			}
		}
		else
		{

			return;
		}

		//
		// We have either succeeded by now, or failed
		//

		setup_campaign_over_screen (en, campaign_status);

		start_game_exit (GAME_EXIT_KICKOUT, FALSE);

		push_ui_screen (campaign_over_screen);
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_force_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_FORCE][COMMS_MODEL_SERVER]  	= update_server;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
