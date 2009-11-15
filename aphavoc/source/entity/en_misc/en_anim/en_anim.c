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

#define DEBUG_MODULE					0

#define DEBUG_MODULE_ID_NUMBER	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_client_server_entity_loading_doors( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (en->type == ENTITY_TYPE_SHIP_VEHICLE)
	{
		//
		// temp - when a mobile lands it opens it's doors - but this isn't such a good idea for ships as they are out at sea
		//

		return;
	}

	val = set_entity_keyframe_value_animating_forwards( en, get_local_entity_float_value( en, FLOAT_TYPE_LOADING_DOOR_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_LOADING_DOOR_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_LOADING_DOOR_STATE, val);

		// Sound now made by "CARGO DOORS"
//		notify_local_entity (ENTITY_MESSAGE_ARTICULATE_LOADING_DOORS, en, en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void close_client_server_entity_loading_doors( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	val = set_entity_keyframe_value_animating_reverse( en, get_local_entity_float_value( en, FLOAT_TYPE_LOADING_DOOR_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_LOADING_DOOR_STATE))
	{
		set_client_server_entity_float_value( en, FLOAT_TYPE_LOADING_DOOR_STATE, val );

		// Sound now made by "CARGO DOORS"
//		notify_local_entity (ENTITY_MESSAGE_ARTICULATE_LOADING_DOORS, en, en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_client_server_entity_cargo_doors( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	val = set_entity_keyframe_value_animating_forwards( en, get_local_entity_float_value( en, FLOAT_TYPE_CARGO_DOOR_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_CARGO_DOOR_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_CARGO_DOOR_STATE, val);

		notify_local_entity (ENTITY_MESSAGE_ARTICULATE_LOADING_DOORS, en, en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void close_client_server_entity_cargo_doors( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	val = set_entity_keyframe_value_animating_reverse( en, get_local_entity_float_value( en, FLOAT_TYPE_CARGO_DOOR_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_CARGO_DOOR_STATE))
	{
		set_client_server_entity_float_value( en, FLOAT_TYPE_CARGO_DOOR_STATE, val );

		notify_local_entity (ENTITY_MESSAGE_ARTICULATE_LOADING_DOORS, en, en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_client_server_entity_airbrakes( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	val = set_entity_keyframe_value_animating_forwards( en, get_local_entity_float_value( en, FLOAT_TYPE_AIRBRAKE_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_AIRBRAKE_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_AIRBRAKE_STATE, val);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void close_client_server_entity_airbrakes( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	val = set_entity_keyframe_value_animating_reverse( en, get_local_entity_float_value( en, FLOAT_TYPE_AIRBRAKE_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_AIRBRAKE_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_AIRBRAKE_STATE, val);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_client_server_entity_flaps( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	val = set_entity_keyframe_value_animating_forwards( en, get_local_entity_float_value( en, FLOAT_TYPE_FLAP_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_FLAP_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_FLAP_STATE, val);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void close_client_server_entity_flaps( entity *en )
{
	float
		val;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	val = set_entity_keyframe_value_animating_reverse( en, get_local_entity_float_value( en, FLOAT_TYPE_FLAP_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_FLAP_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_FLAP_STATE, val);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lower_client_server_entity_undercarriage( entity *en )
{
	float
		val;

	val = set_entity_keyframe_value_animating_forwards( en, get_local_entity_float_value( en, FLOAT_TYPE_UNDERCARRIAGE_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_UNDERCARRIAGE_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_UNDERCARRIAGE_STATE, val);

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{
			notify_local_entity (ENTITY_MESSAGE_ARTICULATE_UNDERCARRIAGE, en, en);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void raise_client_server_entity_undercarriage( entity *en )
{
	float
		val;

	val = set_entity_keyframe_value_animating_reverse( en, get_local_entity_float_value( en, FLOAT_TYPE_UNDERCARRIAGE_STATE ) );

	if (val != get_local_entity_float_value (en, FLOAT_TYPE_UNDERCARRIAGE_STATE))
	{
		set_client_server_entity_float_value (en, FLOAT_TYPE_UNDERCARRIAGE_STATE, val);

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{
			notify_local_entity (ENTITY_MESSAGE_ARTICULATE_UNDERCARRIAGE, en, en);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_undercarriage_state (entity *en)
{
	int
		state;

	ASSERT (en);

	get_keyframed_animation_state (get_local_entity_float_value (en, FLOAT_TYPE_UNDERCARRIAGE_STATE), &state, NULL);

	return state;
}

// start add loading and cargo doors for separate switching in helis by GCsDriver 08-12-2007
int get_local_entity_loading_door_state (entity *en)
{
	int
		state;

	ASSERT (en);

	get_keyframed_animation_state (get_local_entity_float_value (en, FLOAT_TYPE_LOADING_DOOR_STATE), &state, NULL);

	return state;
}

int get_local_entity_cargo_door_state (entity *en)
{
	int
		state;

	ASSERT (en);

	get_keyframed_animation_state (get_local_entity_float_value (en, FLOAT_TYPE_CARGO_DOOR_STATE), &state, NULL);

	return state;
}
// end add loading and cargo doors for separate switching in helis by GCsDriver 08-12-2007

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_entity_weapon_system_ready (entity *en)
{
	float
		val;

	val = set_entity_keyframe_value_animating_forwards( en, get_local_entity_float_value( en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE ) );

	set_local_entity_float_value( en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE, val );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void close_entity_weapon_system_ready( entity *en )
{
	float
		val;

	val = set_entity_keyframe_value_animating_reverse( en, get_local_entity_float_value( en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE ) );

	set_local_entity_float_value( en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE, val );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_weapon_system_ready_state (entity *en)
{
	int
		state;

	ASSERT (en);

	get_keyframed_animation_state (get_local_entity_float_value (en, FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE), &state, NULL);

	return state;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_local_entity_id_number
(
	entity *en,
	texture_animation_indices digit0,
	texture_animation_indices digit1,
	texture_animation_indices digit2,
	texture_animation_indices digit3,
	texture_animation_indices digit4
)
{
	object_3d_instance
		*inst3d;

	int
		seed,
		id_number,
		id_modulo,
		significant_digits;

	ASSERT (en);

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

	if (inst3d)
	{
		if ((digit0 < TEXTURE_ANIMATION_INDEX_LAST) && set_texture_animation_frame_on_object (inst3d, digit0, 0))
		{
			id_modulo = 10;

			significant_digits = 1;

			if ((digit1 < TEXTURE_ANIMATION_INDEX_LAST) && set_texture_animation_frame_on_object (inst3d, digit1, 0))
			{
				id_modulo = 100;

				significant_digits = 2;

				if ((digit2 < TEXTURE_ANIMATION_INDEX_LAST) && set_texture_animation_frame_on_object (inst3d, digit2, 0))
				{
					id_modulo = 1000;

					significant_digits = 3;

					if ((digit3 < TEXTURE_ANIMATION_INDEX_LAST) && set_texture_animation_frame_on_object (inst3d, digit3, 0))
					{
						id_modulo = 10000;

						significant_digits = 4;

						if ((digit4 < TEXTURE_ANIMATION_INDEX_LAST) && set_texture_animation_frame_on_object (inst3d, digit4, 0))
						{
							id_modulo = 100000;

							significant_digits = 5;
						}
					}
				}
			}

			seed = get_client_server_entity_random_number_seed (en);

			id_number = rand16x (&seed) % id_modulo;

			if (id_number == 0)
			{
				id_number = 1;
			}

			#if DEBUG_MODULE_ID_NUMBER

			debug_log
			(
				"%-30.30s: index = %5d, id_modulo = %6d, id_number = %5d, significant_digits = %d",
				get_local_entity_string (en, STRING_TYPE_FULL_NAME),
				get_local_entity_index (en),
				id_modulo,
				id_number,
				significant_digits
			);

			#endif

			set_local_entity_int_value (en, INT_TYPE_ID_NUMBER, id_number);

			set_local_entity_int_value (en, INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS, significant_digits);

			switch (id_modulo)
			{
				case 100000:
				{
					set_texture_animation_frame_on_object (inst3d, digit4, id_number % 10);

					id_number /= 10;
				}
				case 10000:
				{
					set_texture_animation_frame_on_object (inst3d, digit3, id_number % 10);

					id_number /= 10;
				}
				case 1000:
				{
					set_texture_animation_frame_on_object (inst3d, digit2, id_number % 10);

					id_number /= 10;
				}
				case 100:
				{
					set_texture_animation_frame_on_object (inst3d, digit1, id_number % 10);

					id_number /= 10;
				}
				case 10:
				{
					set_texture_animation_frame_on_object (inst3d, digit0, id_number % 10);

					break;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *get_local_entity_id_number_string (entity *en, char *buffer)
{
	static char
		format[] = "%01d";

	int
		id_number,
		id_number_significant_digits;

	ASSERT (en);

	ASSERT (buffer);

	id_number = get_local_entity_int_value (en, INT_TYPE_ID_NUMBER);

	if (id_number > 0)
	{
		id_number_significant_digits = get_local_entity_int_value (en, INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS);

		ASSERT ((id_number_significant_digits >= 1) && (id_number_significant_digits <= 5));

		format[2] = id_number_significant_digits + '0';

		sprintf (buffer, format, id_number);

		return (buffer);
	}

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
