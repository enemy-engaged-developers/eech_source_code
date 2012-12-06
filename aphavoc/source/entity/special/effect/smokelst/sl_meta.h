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

#define MAX_COMPONENTS_PER_META_SMOKE_LIST	4

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum SMOKE_LIST_COMPONENT_TYPES
{
	SMOKE_LIST_NONE,
	SMOKE_LIST_SPRITES,
	SMOKE_LIST_TRAILS,

	NUM_SMOKE_LIST_COMPONENT_TYPES

} smoke_list_component_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct META_SMOKE_LIST_COMPONENT
{

	smoke_list_component_types
		type;

	union
	{
		struct
		{
			//
			// SMOKE LIST SPRITES
			//

			texture_animation_indices
				animated_texture;
		
			int
				sprite_count;
		
			unsigned char
				red,
				green,
				blue,
				alpha;
		
			float
				animation_frequency,
				lifetime,
				scale,
				rotation_rate;

			unsigned char
				additive	: 1;

		};

		struct
		{
			//
			// SMOKE LIST TRAILS
			//

			int
				trail_count;

			smoke_list_types
				trail_type;

			entity_sub_types
				entity_sub_type;

			int
				infinite;

			float
				generator_lifetime,
				frequency,
				smoke_lifetime;
		
		};
	};
};

typedef struct META_SMOKE_LIST_COMPONENT meta_smoke_list_component;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct META_SMOKE_LIST_DATA
{

	int
		number_of_components;

	meta_smoke_list_component
		component[ MAX_COMPONENTS_PER_META_SMOKE_LIST ];

};

typedef struct META_SMOKE_LIST_DATA meta_smoke_list_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern meta_smoke_list_data
	meta_smoke_list_database[NUM_META_SMOKE_LIST_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int create_client_server_meta_smoke_list_sub_object_offset (meta_smoke_list_types type, entity *parent, object_3d_sub_object_index_numbers sub_object_type, int sub_object_depth);

extern int create_client_server_meta_smoke_list_specified_offset (meta_smoke_list_types type, entity *parent, vec3d *relative_offset);

extern int create_meta_smoke_list_sub_object_offset( meta_smoke_list_types type, entity *parent, object_3d_sub_object_index_numbers sub_object_type, int sub_object_depth, int *entity_index_list);

extern int create_meta_smoke_list_specified_offset( meta_smoke_list_types type, entity *parent, vec3d *relative_offset, int *entity_index_list);

extern int create_meta_smoke_list_trails( meta_smoke_list_component *smoke_list_component, entity *parent, vec3d *relative_position, float width, int *entity_index_list );

extern int count_entities_in_meta_smoke_list( meta_smoke_list_types type );

extern void initialise_meta_smoke_list_database(void);

extern void deinitialise_meta_smoke_list_database(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

