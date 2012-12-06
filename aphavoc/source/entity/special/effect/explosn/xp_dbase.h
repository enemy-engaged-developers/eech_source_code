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

typedef enum EXPLOSION_COMPONENT_TYPES
{
	EXPLOSION_SPRITES,
	EXPLOSION_OBJECTS,
	EXPLOSION_PARTICLES,
	EXPLOSION_SMOKE_TRAILS,
	EXPLOSION_SOUND_EFFECT,

	NUM_EXPLOSION_COMPONENT_TYPES

} explosion_component_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct META_EXPLOSION_COMPONENT
{

	explosion_component_types
		type;

	union
	{
		struct
		{
			//
			// EXPLOSION OBJECTS / SPRITES
			//

			union
			{

				texture_animation_indices
					animated_texture;

				object_3d_index_numbers
					object_3d_shape;
			};
			

			union
			{

				int
					sprite_count;

				int
					object_count;
			};
			
			unsigned char
				red,
				green,
				blue,
				alpha;

			unsigned char
				additive						: 1,
				blast_hemisphere_only	: 1;

			float
				delay_max,
				lifetime_min,
				lifetime_max,
				scale_min,
				scale_max;
		
			float
				blast_radius;

			// sprites only
			float
				animation_frequency,
				rotation_rate;
		};

		struct
		{
			//
			// EXPLOSION PARTICLES / EXPLOSION SMOKE TRAILS
			//

			union
			{

				int
					particle_count;

				int
					trail_count;
			};

			int
				trail_type;

			union
			{

				struct
				{
					float
						initial_speed,
						frequency,
						smoke_lifetime;
//						trail_scale;
				};

				struct
				{
					float
						generator_lifetime,
						frequency,
						smoke_lifetime;
//						scale;
		
					vec3d
						initial_velocity;
				};
			};
		};

		struct
		{
			//
			// EXPLOSION SOUND EFFECT
			//

			int
				sound_type;

			float
				sound_volume;
		};
	};
};

typedef struct META_EXPLOSION_COMPONENT meta_explosion_component;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct META_EXPLOSION_DATA
{
	int
		number_of_components;

	float
		damage_radius;

	int
		show_on_map;

	meta_explosion_component
		*component;
};

typedef struct META_EXPLOSION_DATA meta_explosion_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern meta_explosion_data
	meta_explosion_database[NUM_META_EXPLOSION_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_explosion_database(void);

extern void deinitialise_explosion_database(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
