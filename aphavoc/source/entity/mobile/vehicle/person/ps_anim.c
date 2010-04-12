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

#define PERSON_ANIMATION_TOTAL_LENGTH 1000.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PERSON_ANIMATION_DATA
{
	
	float
		velocity,
		start,
		end;

	int
		repeat;

	float
		duration;
};

typedef struct PERSON_ANIMATION_DATA person_animation_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//note: frame 240 is a neutral state, 0 is start of walk cycle

const person_animation_data
   person_animation_database[NUM_PERSON_ANIMS] =
   {
		{
			///////////// NONE ////////////
			0.0,						//Velocity
			240,						//start frame
			240,						//end frame
			0,							//repeat flag
			0.0,						//duration in sec.
		},

		{
			///////////// WALK ////////////
			0.8f,						//Velocity
			0,							//start frame
			44,						//end frame
			1,							//repeat flag
			1.5,						//duration in sec.
		},

		{
			///////////// RUN ////////////
			2.7f,						//Velocity
			60,						//start frame
			73,						//end frame
			1,							//repeat flag
			0.6f,						//duration in sec.
		},

		{
			///////////// STAND1 ////////////
			0.0,						//Velocity
			240,						//start frame
			360,						//end frame
			0,							//repeat flag
			5.0,						//duration in sec.
		},

		{
			///////////// STAND2 ////////////
			0.0,						//Velocity
			360,						//start frame
			480,						//end frame
			0,							//repeat flag
			5.0,						//duration in sec.
		},

		{
			///////////// STAND3 ////////////
			0.0,						//Velocity
			480,						//start frame
			600,						//end frame
			0,							//repeat flag
			5.0,						//duration in sec.
		},

		{
			///////////// STAND4 ////////////
			0.0,						//Velocity
			600,						//start frame
			720,						//end frame
			0,							//repeat flag
			2.0,						//duration in sec.
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_person (entity *en)
{
	person
		*raw;
	
	int
		state;
			
	float
		scale,
		remainder,
		position;
	
	ASSERT (en);
	
	raw = (person *) get_local_entity_data (en);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
		{
			return;
		}
	
		get_keyframed_animation_state (raw->person_animation_state, &state, &remainder);
	
		scale = (person_animation_database[state].end - person_animation_database[state].start);
					
		position = (remainder * scale + person_animation_database[state].start) / PERSON_ANIMATION_TOTAL_LENGTH;
					
		#ifdef DEBUG_PERSON_ANIMATION
	
		if (en == get_external_view_entity ())
		{
			debug_log ("frame :%f", (position * PERSON_ANIMATION_TOTAL_LENGTH));
		}
	
		#endif
	
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_TORSO, position);
	
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_ARM, position);
	
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_HEAD, position);
	
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_LEG, position);
	}
	else
	{
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_TORSO, raw->person_animation_state);
	
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_ARM, raw->person_animation_state);
	
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_HEAD, raw->person_animation_state);
	
		animate_entity_simple_keyframed_sub_objects (raw->vh.inst3d, OBJECT_3D_SUB_OBJECT_TROOP_LEG, raw->person_animation_state);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_person_animation (entity *en)
{
	person
		*raw;

	int
		wrapped,
		state;

	float
		frequency,
		remainder;

	ASSERT( en );

	raw = (person *) get_local_entity_data (en);

	//update character animation

	get_keyframed_animation_state (raw->person_animation_state, &state, &remainder);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		if (state != PERSON_ANIM_NONE)
		{
			frequency = 1.0 / person_animation_database[state].duration;

			wrapped = update_entity_simple_keyframed_value (en, &remainder, frequency);

			if ( (wrapped) && (!person_animation_database[state].repeat) )
			{
				int
					state_selector;

				// set new animation that isn't same as previous
				state_selector = rand16 () % 4;

				switch ( state_selector )
				{

					case 0: state = ( state == PERSON_ANIM_STAND1 ) ? PERSON_ANIM_STAND2 : PERSON_ANIM_STAND1; break;
					case 1: state = ( state == PERSON_ANIM_STAND2 ) ? PERSON_ANIM_STAND3 : PERSON_ANIM_STAND2; break;
					case 2: state = ( state == PERSON_ANIM_STAND3 ) ? PERSON_ANIM_STAND4 : PERSON_ANIM_STAND3; break;
					case 3: state = ( state == PERSON_ANIM_STAND4 ) ? PERSON_ANIM_STAND1 : PERSON_ANIM_STAND4; break;
				}
				
				remainder = 0.0;
		
				raw->person_animation_state = state + remainder;

				ASSERT ( raw->person_animation_state < NUM_PERSON_ANIMS );
			}
			else
			{
				raw->person_animation_state = state + remainder;

				ASSERT ( raw->person_animation_state < NUM_PERSON_ANIMS );
			}
		}
	}
	else
	{
		raw->person_animation_state += 1.4 * get_entity_movement_delta_time ();

		if (raw->person_animation_state >= 1.0)
		{
			raw->person_animation_state = 1.0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_person_3d_object (entity *en)
{
	person
		*raw;

	ASSERT (en);

	raw = (person *) get_local_entity_data (en);

	// destruct old object

	destruct_3d_object (raw->vh.inst3d);

	// construct new (damaged) object

	raw->vh.object_3d_shape = get_local_entity_int_value (en, INT_TYPE_DESTROYED_3D_SHAPE);

	raw->vh.inst3d = construct_3d_object (raw->vh.object_3d_shape);

	//set animation variable to start playing death anim

	raw->person_animation_state = 0.0;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_person_database_velocity (person_animations anim)
{

	return person_animation_database [anim].velocity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
