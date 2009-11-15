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

#define FIXED_WING_AFTERBURNER_OFF_STATE						0.0
#define FIXED_WING_AFTERBURNER_EXTENDING_START_STATE		1.0
#define FIXED_WING_AFTERBURNER_EXTENDING_END_STATE			2.0
#define FIXED_WING_AFTERBURNER_ON_START_STATE				3.0
#define FIXED_WING_AFTERBURNER_ON_END_STATE					4.0
#define FIXED_WING_AFTERBURNER_RETRACTING_START_STATE		5.0
#define FIXED_WING_AFTERBURNER_RETRACTING_END_STATE		6.0

#define FIXED_WING_AFTERBURNER_ANIMATION_RATE				0.5

static int
	direction = FALSE;		//DEBUG

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AFTERBURNERS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_client_server_fixed_wing_afterburner_state (entity *en, int state)
{
	fixed_wing
		*raw;

	object_3d_instance
		*inst3d;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (fixed_wing *) get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	if (state)
	{
		#if DEBUG_MODULE

		debug_log( "TURNING AFTERBURNER ON ( entity %d, %s )", en, entity_sub_type_aircraft_names [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)]);

		#endif

		if (raw->afterburner_state < FIXED_WING_AFTERBURNER_EXTENDING_START_STATE)
		{
			//
			// currently off - so turn them on
			//

			set_client_server_entity_float_value (en, FLOAT_TYPE_AFTERBURNER_STATE, FIXED_WING_AFTERBURNER_EXTENDING_START_STATE);

			//
			// sound effects
			//

			if (object_contains_sub_object_type (inst3d, OBJECT_3D_SUB_OBJECT_EFFECT_AFTERBURNER, 0, NULL))
			{
				resume_client_server_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2);

				pause_client_server_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1, 0.5);
			}
		}
		else if (raw->afterburner_state >= FIXED_WING_AFTERBURNER_RETRACTING_START_STATE)
		{
			//
			// currently being retracted - so reverse the animation
			//

			set_client_server_entity_float_value (en, FLOAT_TYPE_AFTERBURNER_STATE, 7.0 - raw->afterburner_state);
		}
	}
	else
	{
		#if DEBUG_MODULE

		debug_log( "TURNING AFTERBURNER OFF ( entity %d, %s )", en, entity_sub_type_aircraft_names [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)]);

		#endif

		if (raw->afterburner_state < FIXED_WING_AFTERBURNER_EXTENDING_START_STATE)
		{
		}
		else if (raw->afterburner_state >= FIXED_WING_AFTERBURNER_RETRACTING_START_STATE)
		{
		}
		else if (raw->afterburner_state <= FIXED_WING_AFTERBURNER_EXTENDING_END_STATE	)
		{
			//
			// currently being extended - so reverse the animation
			//

			set_client_server_entity_float_value (en, FLOAT_TYPE_AFTERBURNER_STATE, 7.0 - raw->afterburner_state);
		}
		else
		{
			//
			// currently on - so turn them off
			//

			set_client_server_entity_float_value (en, FLOAT_TYPE_AFTERBURNER_STATE, FIXED_WING_AFTERBURNER_RETRACTING_START_STATE);

			//
			// sound effects
			//

			if (object_contains_sub_object_type (inst3d, OBJECT_3D_SUB_OBJECT_EFFECT_AFTERBURNER, 0, NULL))
			{
				resume_client_server_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1);

				pause_client_server_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2, 0.5);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_local_fixed_wing_afterburner_state (entity *en, int state)
{
	fixed_wing
		*raw;

	object_3d_instance
		*inst3d;

	ASSERT (en);

	raw = (fixed_wing *) get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	if (state)
	{
		if (raw->afterburner_state < FIXED_WING_AFTERBURNER_EXTENDING_START_STATE)
		{
			//
			// currently off - so turn them on
			//

			raw->afterburner_state = FIXED_WING_AFTERBURNER_EXTENDING_START_STATE;

			//
			// sound effects
			//

			if (object_contains_sub_object_type (inst3d, OBJECT_3D_SUB_OBJECT_EFFECT_AFTERBURNER, 0, NULL))
			{
				pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1, 0.5);

				resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2);
			}
		}
		else if (raw->afterburner_state >= FIXED_WING_AFTERBURNER_RETRACTING_START_STATE)
		{
			//
			// currently being retracted - so reverse the animation
			//

			raw->afterburner_state = 7.0 - raw->afterburner_state;
		}
	}
	else
	{
		if (raw->afterburner_state < FIXED_WING_AFTERBURNER_EXTENDING_START_STATE)
		{
		}
		else if (raw->afterburner_state >= FIXED_WING_AFTERBURNER_RETRACTING_START_STATE)
		{
		}
		else if (raw->afterburner_state <= FIXED_WING_AFTERBURNER_EXTENDING_END_STATE	)
		{
			//
			// currently being extended - so reverse the animation
			//

			raw->afterburner_state = 7.0 - raw->afterburner_state;
		}
		else
		{
			//
			// currently on - so turn them off
			//

			raw->afterburner_state = FIXED_WING_AFTERBURNER_RETRACTING_START_STATE;

			//
			// sound effects
			//

			if (object_contains_sub_object_type (inst3d, OBJECT_3D_SUB_OBJECT_EFFECT_AFTERBURNER, 0, NULL))
			{
				pause_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2, 0.5);

				resume_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_fixed_wing_afterburners( entity *en )
{
	fixed_wing
		*raw;

	object_3d_instance
		*inst3d;

	float
		val,
		frac,
		base;

	ASSERT( en );

	raw = (fixed_wing *) get_local_entity_data( en );

	inst3d = raw->ac.inst3d;

	frac = fast_modf (raw->afterburner_state, &base);

	base = floor (base * 0.5);

	val = (base + frac) / 3.0;

	animate_entity_simple_keyframed_sub_objects (inst3d, OBJECT_3D_SUB_OBJECT_EFFECT_AFTERBURNER, val);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_fixed_wing_afterburners (entity *en)
{
	fixed_wing
		*raw;

	float
		frac,
		state;

	ASSERT( en );

	raw = (fixed_wing *) get_local_entity_data( en );

	//
	// break down afterburner state into integer and fractional parts
	//

	frac = fast_modf (raw->afterburner_state, &state);

	if ( ( in_flight_articulation_test ) && ( get_comms_model() == COMMS_MODEL_SERVER ) )
	{
		//
		// debug articulation test
		//

		if (state == FIXED_WING_AFTERBURNER_OFF_STATE)
		{
			//
			// if afterburners are off - turn them on !
			//

			raw->afterburner_state = FIXED_WING_AFTERBURNER_EXTENDING_START_STATE;

			return;
		}

		//
		// update state, but don't loop the looping bit
		//

		frac += (get_delta_time () * FIXED_WING_AFTERBURNER_ANIMATION_RATE);

		while (frac >= 1.0)
		{
			frac -= 1.0;

			state += 2.0;
		}
	}
	else
	{
		//
		// normal operation
		//

		if (state == FIXED_WING_AFTERBURNER_OFF_STATE)
		{

			return;
		}

		//
		// update state
		//

		frac += (get_delta_time () * FIXED_WING_AFTERBURNER_ANIMATION_RATE);

		while (frac >= 1.0)
		{
			frac -= 1.0;

			if (state != FIXED_WING_AFTERBURNER_ON_START_STATE)
			{
				//
				// only change state if not in looping part
				//

				state += 2.0;
			}
		}
	}

	//
	// passed the end of the animation, so return to OFF state
	//

	if (state >= FIXED_WING_AFTERBURNER_RETRACTING_END_STATE)
	{
		raw->afterburner_state = FIXED_WING_AFTERBURNER_OFF_STATE;
	}
	else
	{
		raw->afterburner_state = state + frac;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AIRBRAKES
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define FIXED_WING_AIRBRAKES_CLOSED_FLOAT_VALUE 						0.0

#define FIXED_WING_AIRBRAKES_OPENING_FLOAT_VALUE 						1.0

//#define FIXED_WING_AIRBRAKES_OPEN_FLOAT_VALUE							2.0

#define FIXED_WING_AIRBRAKES_CLOSING_FLOAT_VALUE						3.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_fixed_wing_airbrakes( entity *en )
{
	fixed_wing
		*raw;

	//
	// animates the airbrakes on a fixed wing aircraft
	//

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	raw = (fixed_wing *) get_local_entity_data (en);

	animate_entity_reversable_keyframed_sub_objects( raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_AIR_BRAKE, raw->airbrake_state );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_fixed_wing_airbrakes( entity *en )
{
	fixed_wing
		*raw;

	int
		airbrake_state;

	//
	// updates the airbrakes status ( regardless of whether the aircraft is drawn or not )
	//

	ASSERT( en );

	raw = (fixed_wing *) get_local_entity_data( en );

	airbrake_state = update_entity_reversable_keyframed_value( en, &raw->airbrake_state, 0.5 );

	if ( ( in_flight_articulation_test ) && ( get_comms_model() == COMMS_MODEL_SERVER ) )
	{
		switch ( airbrake_state )
		{
			//////////////////////////////////////////////////
			case 0:
			//////////////////////////////////////////////////
			{
				open_client_server_entity_airbrakes( en );

				break;
			}
			//////////////////////////////////////////////////
			case 2:
			//////////////////////////////////////////////////
			{
				close_client_server_entity_airbrakes( en );

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FLAPS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define FIXED_WING_FLAPS_CLOSED_FLOAT_VALUE 					0.0

#define FIXED_WING_FLAPS_OPENING_FLOAT_VALUE 					1.0

//#define FIXED_WING_FLAPS_OPEN_FLOAT_VALUE						2.0

#define FIXED_WING_FLAPS_CLOSING_FLOAT_VALUE						3.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_fixed_wing_flaps( entity *en )
{
	fixed_wing
		*raw;

	//
	// animates the flaps on a fixed wing aircraft
	//

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	raw = (fixed_wing *) get_local_entity_data (en);

	animate_entity_reversable_keyframed_sub_objects( raw->ac.inst3d, OBJECT_3D_SUB_OBJECT_FLAPS, raw->flap_state );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_fixed_wing_flaps( entity *en )
{
	fixed_wing
		*raw;

	int
		flap_state;

	//
	// updates the flaps status ( regardless of whether the aircraft is drawn or not )
	//

	ASSERT( en );

	raw = (fixed_wing *) get_local_entity_data( en );

	flap_state = update_entity_reversable_keyframed_value( en, &raw->flap_state, 0.5 );

	if ( ( in_flight_articulation_test ) && ( get_comms_model() == COMMS_MODEL_SERVER ) )
	{
		switch ( flap_state )
		{
			//////////////////////////////////////////////////
			case 0:
			//////////////////////////////////////////////////
			{
				open_client_server_entity_flaps( en );

				break;
			}
			//////////////////////////////////////////////////
			case 2:
			//////////////////////////////////////////////////
			{
				close_client_server_entity_flaps( en );

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PROPELLOR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_fixed_wing_propellors( entity *en )
{
	fixed_wing
		*raw;

	object_3d_instance
		*inst3d;

	float
		ang;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	raw = (fixed_wing *) get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	if ((in_flight_articulation_test) && (en == get_external_view_entity ()))
	{
		if (direction)
		{
			raw->propellor_rpm += 5.0 * get_delta_time ();

			if (raw->propellor_rpm >= 40.0)
			{
				direction = FALSE;
			}
		}
		else
		{
			raw->propellor_rpm -= 5.0 * get_delta_time ();

			if (raw->propellor_rpm <= 0.0)
			{
				direction = TRUE;
			}
		}
	}

	//
	// set the correct blade type visible status
	//

	if (raw->propellor_rpm > 15.0)
	{
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_MOVING, TRUE);
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_STATIC, FALSE);

		ang = PI / 20.0;
	}
	else
	{
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_MOVING, FALSE);
		set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_STATIC, TRUE);

		ang = 0.25 * raw->propellor_rpm * get_delta_time ();
	}

	//
	// stop props from spinning if paused ( but must still switch the correct objects on and off )
	//

   if (get_time_acceleration () != TIME_ACCELERATION_PAUSE)
	{
		ang *= get_local_entity_float_value (en, FLOAT_TYPE_PROPELLOR_DIRECTION);

		//
		// rotate hub
		//

		modify_sub_object_type_heading_pitch_and_roll (inst3d, OBJECT_3D_SUB_OBJECT_PROPELLER_HUB, 0.0, 0.0, ang);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_fixed_wing_propellors (entity *en)
{
	fixed_wing
		*raw;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search;

	int
		depth;

	ASSERT (en);

	raw = (fixed_wing *) get_local_entity_data (en);

	inst3d = raw->ac.inst3d;

	depth = 0;

	while (TRUE)
	{
		search.search_depth = depth;
		search.search_object = inst3d;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_PROPELLER_HUB;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			#if RECOGNITION_GUIDE

			search.result_sub_object->relative_roll = 0.0;

			#else

			search.result_sub_object->relative_roll = sfrand1 () * PI;

			#endif
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

void damage_fixed_wing_3d_object (entity *en)
{
	fixed_wing
		*raw;

	ASSERT (en);

	raw = (fixed_wing *) get_local_entity_data (en);

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

	set_fixed_wing_id_number (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_fixed_wing_id_number (entity *en)
{
	fixed_wing
		*raw;

	ASSERT (en);

	raw = (fixed_wing *) get_local_entity_data (en);

	if (raw->ac.mob.side == ENTITY_SIDE_BLUE_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_USA_AC_DIGIT__000,
			TEXTURE_ANIMATION_INDEX_USA_AC_DIGIT__001,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST
		);
	}
	else if (raw->ac.mob.side == ENTITY_SIDE_RED_FORCE)
	{
		set_local_entity_id_number
		(
			en,
			TEXTURE_ANIMATION_INDEX_CIS_AC_DIGIT__000,
			TEXTURE_ANIMATION_INDEX_CIS_AC_DIGIT__001,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST,
			TEXTURE_ANIMATION_INDEX_LAST
		);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

