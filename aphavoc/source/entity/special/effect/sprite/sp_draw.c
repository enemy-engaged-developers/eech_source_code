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

	sprite
		*raw;

#ifndef OGRE_EE
	object_3d_sprite
#else
	struct OgreParticle
#endif
		spr;

	real_colour
		colour;

	float
		lifescale;

	int
		frame,
		number_of_frames;
	
	entity
		*parent;

	raw = (sprite *) get_local_entity_data (en);

	if ( raw->effect_lifetime < 0.0 )
	{
		return;
	}

	//
	// set the sprite dependant on the effect_lifetime
	//

	lifescale = raw->effect_lifetime / raw->sprite_lifetime;

	number_of_frames = get_texture_animation_number_of_frames ( raw->animated_texture );
	
	if ((raw->animation_frequency == 0.0) || (lifescale == 0.0) || (number_of_frames == 1))
	{
		frame = 0;
	}
	else
	{
		float
			v;

		v = lifescale * raw->animation_frequency;

		v = frac (v);

		v *= (float)number_of_frames;

		convert_float_to_int (v, &frame);

		//
		// Because "lifescale" should always be less than 1.0, frame should also always be less than number_of_frames,
		//  but check just in case
		//

		frame = min (frame, number_of_frames - 1);
	}

#ifndef OGRE_EE
	spr.texture = get_texture_animation_texture_pointer ( raw->animated_texture, frame );
#else
	spr.texture_animation = raw->animated_texture;
	spr.frame = frame;
#endif

	spr.additive = raw->additive;

	if ( raw->additive )
	{
		float
			red,
			green,
			blue;

		colour.alpha = 255;

		red = (float)raw->colour_red * ( 1.0 - lifescale );
		green = (float)raw->colour_green * ( 1.0 - lifescale );
		blue = (float)raw->colour_blue * ( 1.0 - lifescale );

		colour.red = (unsigned char)red;
		colour.green = (unsigned char)green;
		colour.blue = (unsigned char)blue;
	}
	else
	{
		float
			alpha;

		alpha = 255.0 * ( 1.0 - lifescale );

		colour.alpha = (unsigned char)alpha;

		colour.red = raw->colour_red;
		colour.green = raw->colour_green;
		colour.blue = raw->colour_blue;
	}

	spr.colour = colour.colour;

	spr.roll = wrap_angle( ( raw->rotation_rate * raw->effect_lifetime * PI ) );		//temp

	spr.radius = raw->start_scale + ((raw->end_scale - raw->start_scale) * lifescale);

	parent = get_local_entity_parent (en, LIST_TYPE_SPECIAL_EFFECT);

	if (parent)
	{
		vec3d
			*offset,
			*raw_position;

		matrix3x3
			m;

		raw_position = get_local_entity_vec3d_ptr (parent, VEC3D_TYPE_POSITION);

		offset = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_RELATIVE_POSITION);

		if (check_zero_3d_vector (offset))
		{
			memcpy (&(spr.position), raw_position, sizeof (vec3d));
		}
		else
		{	
			get_local_entity_attitude_matrix (parent, m);
	
			spr.position.x = raw_position->x + ( ( offset->x * m[0][0] ) + ( offset->y * m[1][0] ) + ( offset->z * m[2][0] ) );
			spr.position.y = raw_position->y + ( ( offset->x * m[0][1] ) + ( offset->y * m[1][1] ) + ( offset->z * m[2][1] ) );
			spr.position.z = raw_position->z + ( ( offset->x * m[0][2] ) + ( offset->y * m[1][2] ) + ( offset->z * m[2][2] ) );
		}
	}
	else
	{
		memcpy (&(spr.position), &(raw->eff.position), sizeof (vec3d));
	}

#ifndef OGRE_EE
	insert_zbiased_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_SPRITE, &spr, -1.0);
#else
	ogre_particles_draw (&spr, 0, NULL);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_sprite_draw_functions (void)
{
	fn_draw_local_entity_3d_object[ENTITY_TYPE_SPRITE]	= draw_local_3d_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
