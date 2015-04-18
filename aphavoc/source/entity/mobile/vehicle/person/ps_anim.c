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
#define DEBUG_PERSON_ANIMATION 0

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
			1.0,						//Velocity
			0,							//start frame
			44,						//end frame
			1,							//repeat flag
			1.5,						//duration in sec.
		},

		{
			///////////// RUN ////////////
			3.2,						//Velocity
			60,						//start frame
			73,						//end frame
			1,							//repeat flag
			0.6,						//duration in sec.
		},

		{
			///////////// STAND1 ////////////
			0.0,						//Velocity
			240,						//start frame
			360,						//end frame
			0,							//repeat flag
			7.5,						//duration in sec.
		},

		{
			///////////// STAND2 ////////////
			0.0,						//Velocity
			360,						//start frame
			480,						//end frame
			0,							//repeat flag
			7.5,						//duration in sec.
		},

		{
			///////////// STAND3 ////////////
			0.0,						//Velocity
			480,						//start frame
			600,						//end frame
			0,							//repeat flag
			7.5,						//duration in sec.
		},

		{
			///////////// STAND4 ////////////
			0.0,						//Velocity
			600,						//start frame
			720,						//end frame
			0,							//repeat flag
			3.0,						//duration in sec.
		},
		{
			/// AIM_STANDING ///
			0.0,						//Velocity
			800,						//start frame
			824,						//end frame
			0,							//repeat flag
			0.75						//duration in sec.
		},
		{
			/// SHOOT_STANDING ///
			0.0,						//Velocity
			825,						//start frame
			849,						//end frame
			1,							//repeat flag
			0.75						//duration in sec.
		},
		{
			/// AIM_CROUCHING ///
			0.0,						//Velocity
			850,						//start frame
			874,						//end frame
			0,							//repeat flag
			0.75						//duration in sec.
		},
		{
			/// SHOOT_CROUCHING ///
			0.0,						//Velocity
			875,						//start frame
			899,						//end frame
			1,							//repeat flag
			0.75						//duration in sec.
		},
		{
			/// DEATH_STANDING1 ///
			0.0,						//Velocity
			900,						//start frame
			924,						//end frame
			0,							//repeat flag
			0.6						//duration in sec.
		},
		{
			/// DEATH_STANDING2 ///
			0.0,						//Velocity
			925,						//start frame
			949,						//end frame
			0,							//repeat flag
			0.6						//duration in sec.
		},
		{
			/// DEATH_CROUCHING1 ///
			0.0,						//Velocity
			950,						//start frame
			974,						//end frame
			0,							//repeat flag
			0.6						//duration in sec.
		},
		{
			/// DEATH_CROUCHING2 ///
			0.0,						//Velocity
			975,						//start frame
			999,						//end frame
			0,							//repeat flag
			0.6						//duration in sec.
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

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	get_keyframed_animation_state (raw->person_animation_state, &state, &remainder);

	scale = (person_animation_database[state].end - person_animation_database[state].start);

	position = (remainder * scale + person_animation_database[state].start) / PERSON_ANIMATION_TOTAL_LENGTH;

	#if DEBUG_PERSON_ANIMATION

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

	if(get_local_entity_parent (en, LIST_TYPE_TARGET) || state == PERSON_ANIM_SHOOT_STANDING || state == PERSON_ANIM_SHOOT_CROUCHING)
	{
		if (raw->vh.mob.target_link.parent)
		{
			float ps_heading;

			vec3d
				fire_heading,
				*target_pos;

			target_pos = get_local_entity_vec3d_ptr (raw->vh.mob.target_link.parent, VEC3D_TYPE_POSITION);

			if(target_pos)//valid target?
			{

				fire_heading.x = target_pos->x - raw->vh.mob.position.x;
				fire_heading.y = 0.0;
				fire_heading.z =  target_pos->z - raw->vh.mob.position.z;

				normalise_3d_vector (&fire_heading);

				ps_heading = atan2 (fire_heading.x, fire_heading.z);

				get_3d_transformation_heading_matrix (raw->vh.mob.attitude, ps_heading);
			}
		}

		
		if (state != PERSON_ANIM_NONE)
			frequency = 1.0 / person_animation_database[state].duration;
		else
			frequency = 0.0;

		wrapped = update_entity_simple_keyframed_value (en, &remainder, frequency);

		//we are firing, but not animated yet
		if (state != PERSON_ANIM_AIM_STANDING && state != PERSON_ANIM_SHOOT_STANDING && state != PERSON_ANIM_AIM_CROUCHING && state != PERSON_ANIM_SHOOT_CROUCHING)
			raw->person_animation_state = (rand16 () % 2) ? PERSON_ANIM_AIM_STANDING : PERSON_ANIM_AIM_CROUCHING;
		else
		{
			if (wrapped && !person_animation_database[state].repeat)//go from aiming to shoot anim
			{
				if (state == PERSON_ANIM_AIM_STANDING)
					state = PERSON_ANIM_SHOOT_STANDING;
				else if (state == PERSON_ANIM_AIM_CROUCHING)
					state = PERSON_ANIM_SHOOT_CROUCHING;

				raw->person_animation_state = state;
			}
			else
				if (!(!get_local_entity_float_value(en, FLOAT_TYPE_WEAPON_BURST_TIMER) && (state == PERSON_ANIM_SHOOT_STANDING || state == PERSON_ANIM_SHOOT_CROUCHING))) // freeze animation if unit not really firing
					raw->person_animation_state = state + remainder;
		}
	}
	else
	{	
		if (state != PERSON_ANIM_NONE)
		{
			frequency = 1.0 / person_animation_database[state].duration;

			wrapped = update_entity_simple_keyframed_value (en, &remainder, frequency);

			if (!(!get_local_entity_int_value (en, INT_TYPE_ALIVE) && wrapped))
			{
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

					raw->person_animation_state = state;
				}
				else
					raw->person_animation_state = state + remainder;
			}
		}
	}
	
	ASSERT ( raw->person_animation_state < NUM_PERSON_ANIMS );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_person_3d_object (entity *en)
{
	person
		*raw;
	int
		state,
		state_selector;

	float
		remainder;

	ASSERT (en);

	raw = (person *) get_local_entity_data (en);

	get_keyframed_animation_state (raw->person_animation_state, &state, &remainder);

	state_selector = rand16 () % 2;

	if (state == PERSON_ANIM_AIM_CROUCHING || state == PERSON_ANIM_SHOOT_CROUCHING)
		raw->person_animation_state = !state_selector ? PERSON_ANIM_DEATH_CROUCHING1 : PERSON_ANIM_DEATH_CROUCHING2;
	else
		raw->person_animation_state = !state_selector ? PERSON_ANIM_DEATH_STANDING1 : PERSON_ANIM_DEATH_STANDING2;
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
