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

meta_smoke_list_data
	meta_smoke_list_database[NUM_META_SMOKE_LIST_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int create_meta_smoke_list_sprites( meta_smoke_list_component *smoke_list_component, entity *parent, vec3d *relative_position, int *entity_index_list );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_client_server_meta_smoke_list_sub_object_offset (meta_smoke_list_types type, entity *parent, object_3d_sub_object_index_numbers sub_object_type, int sub_object_depth)
{
	int
		loop,
		count,
		*entity_index_list;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// create an array of entity index numbers and fill them all with ENTITY_INDEX_DONT_CARE
	//

	count = count_entities_in_meta_smoke_list (type);

	ASSERT (count);

	entity_index_list = (int *) malloc_fast_mem (sizeof (int) * count);

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		entity_index_list [loop] = ENTITY_INDEX_DONT_CARE;
	}

	//
	// call the create function which will create the entities on the server, and also fill in the entity index list
	//

	create_meta_smoke_list_sub_object_offset (type, parent, sub_object_type, sub_object_depth, entity_index_list);

	//
	// now notify the clients to create same smoke list and pass them the list of indices to use
	//

	transmit_entity_comms_message
	(
		ENTITY_COMMS_CREATE_META_SMOKE_LIST_SUB_OBJECT_OFFSET,
		NULL,
		type,
		parent,
		sub_object_type,
		sub_object_depth,
		entity_index_list
	);

	//
	//
	//

	free_mem (entity_index_list);

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_smoke_list_sub_object_offset( meta_smoke_list_types type, entity *parent, object_3d_sub_object_index_numbers sub_object_type, int sub_object_depth, int *entity_index_list)
{
	int
		comp,
		save_attr,
		index_counter,
		num_components;

	vec3d
		width_position,
		relative_position;

	float
		width_adjustment;

	meta_smoke_list_component
		*smoke_list_component;

	ASSERT (type > META_SMOKE_LIST_TYPE_NONE);

	ASSERT (type < NUM_META_SMOKE_LIST_TYPES );

	index_counter = 0;

	width_adjustment = 0.0;

	save_attr = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{
		set_force_local_entity_create_stack_attributes (TRUE);
	}
	else
	{
		if (get_comms_model () == COMMS_MODEL_CLIENT)
		{
			debug_fatal ("CREATE META SMOKE LIST : CLIENT creating in t/x mode");
		}
	}

	//
	// find the offset to the parent ( if necessary )
	//

	relative_position.x = 0.0;
	relative_position.y = 0.0;
	relative_position.z = 0.0;

	if ((parent) && (sub_object_type != OBJECT_3D_INVALID_SUB_OBJECT_INDEX))
	{
		object_3d_instance
			*inst3d;

		object_3d_sub_object_search_data
			effect_position_search,
			effect_width_search;

		inst3d = (object_3d_instance *) get_local_entity_ptr_value (parent, PTR_TYPE_INSTANCE_3D_OBJECT);

		if (inst3d)
		{
			//
			// locate attachment position on parent entity
			//

			if (get_sub_object_relative_position (inst3d, sub_object_type, sub_object_depth, &relative_position, &effect_position_search))
			{
				//
				// search from attachment position to find a width position, and add it to the smoke
				//

				effect_width_search.search_depth = 0;
				effect_width_search.sub_object_index = OBJECT_3D_SUB_OBJECT_EFFECT_WIDTH_POSITION;

				if (find_object_3d_sub_object_from_sub_object ( &effect_position_search, &effect_width_search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					width_position.x = effect_width_search.result_sub_object->relative_position.x;
					width_position.y = effect_width_search.result_sub_object->relative_position.y;
					width_position.z = effect_width_search.result_sub_object->relative_position.z;

					width_adjustment = get_3d_vector_magnitude( &width_position );

					#if DEBUG_MODULE

					debug_log("SL_META : Found effect width at depth %d : width_adjustment = %f", sub_object_depth, width_adjustment);

					#endif
				}
			}
		}
		else
		{
			//
			// parent does not have a 3d instance ( possibly construct a temporary one )
			//
		}
	}

	num_components = meta_smoke_list_database[ type ].number_of_components;

	for ( comp = 0 ; comp < num_components ; comp ++ )
	{

		smoke_list_component = &(meta_smoke_list_database[ type ].component[ comp ]);

		switch ( smoke_list_component->type )
		{
			case SMOKE_LIST_NONE:
			{
				break;
			}
			case SMOKE_LIST_SPRITES:
			{
				index_counter += create_meta_smoke_list_sprites( smoke_list_component, parent, &relative_position, &entity_index_list[ index_counter ] );

				break;
			}
			case SMOKE_LIST_TRAILS:
			{
				index_counter += create_meta_smoke_list_trails( smoke_list_component, parent, &relative_position, width_adjustment, &entity_index_list[ index_counter ] );

				break;
			}
			default:
			{
				debug_fatal("META SMOKE LIST : Unknown component type %d", smoke_list_component->type );
			}
		}
	}

	set_force_local_entity_create_stack_attributes (save_attr);

	return index_counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_client_server_meta_smoke_list_specified_offset (meta_smoke_list_types type, entity *parent, vec3d *relative_offset)
{
	int
		loop,
		count,
		*entity_index_list;

	//
	// N.B. if parent is NULL then relative offset is taken to be the absolute position
	//

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// create an array of entity index numbers and fill them all with ENTITY_INDEX_DONT_CARE
	//

	count = count_entities_in_meta_smoke_list (type);

	ASSERT (count);

	entity_index_list = (int *) malloc_fast_mem (sizeof (int) * count);

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		entity_index_list [loop] = ENTITY_INDEX_DONT_CARE;
	}

	//
	// call the create function which will create the entities on the server, and also fill in the entity index list
	//

	create_meta_smoke_list_specified_offset (type, parent, relative_offset, entity_index_list);

	//
	// now notify the clients to create same smoke list and pass them the list of indices to use
	//

	transmit_entity_comms_message
	(
		ENTITY_COMMS_CREATE_META_SMOKE_LIST_SPECIFIED_OFFSET,
		NULL,
		type,
		parent,
		relative_offset,
		entity_index_list
	);

	//
	//
	//

	free_mem (entity_index_list);

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_smoke_list_specified_offset( meta_smoke_list_types type, entity *parent, vec3d *relative_offset, int *entity_index_list)
{
	int
		comp,
		save_attr,
		index_counter,
		num_components;

	meta_smoke_list_component
		*smoke_list_component;

	vec3d
		relative_position;

	ASSERT (type > META_SMOKE_LIST_TYPE_NONE);

	ASSERT (type < NUM_META_SMOKE_LIST_TYPES );

	index_counter = 0;

	save_attr = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{
		set_force_local_entity_create_stack_attributes (TRUE);
	}
	else
	{
		if (get_comms_model () == COMMS_MODEL_CLIENT)
		{
			debug_fatal ("CREATE META SMOKE LIST : CLIENT creating in t/x mode");
		}
	}

	if (relative_offset)
	{
		relative_position.x = relative_offset->x;
		relative_position.y = relative_offset->y;
		relative_position.z = relative_offset->z;
	}
	else
	{
		//
		// shouldn't have no parent and no position
		//

		ASSERT (parent);

		relative_position.x = 0.0;
		relative_position.y = 0.0;
		relative_position.z = 0.0;
	}

	num_components = meta_smoke_list_database[ type ].number_of_components;

	for ( comp = 0 ; comp < num_components ; comp ++ )
	{

		smoke_list_component = &(meta_smoke_list_database[ type ].component[ comp ]);

		switch ( smoke_list_component->type )
		{
			case SMOKE_LIST_NONE:
			{
				break;
			}
			case SMOKE_LIST_SPRITES:
			{
				index_counter += create_meta_smoke_list_sprites( smoke_list_component, parent, &relative_position, &entity_index_list[ index_counter ] );

				break;
			}
			case SMOKE_LIST_TRAILS:
			{
				index_counter += create_meta_smoke_list_trails( smoke_list_component, parent, &relative_position, 0.0, &entity_index_list[ index_counter ] );

				break;
			}
			default:
			{
				debug_fatal("META SMOKE LIST : Unknown component type %d", smoke_list_component->type );
			}
		}
	}

	set_force_local_entity_create_stack_attributes (save_attr);

	return index_counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_smoke_list_sprites( meta_smoke_list_component *smoke_list_component, entity *parent, vec3d *relative_position, int *entity_index_list )
{
	vec3d
		*pos;

	float
		animation_frequency,
		lifetime,
		scale;

	texture_animation_indices
		texture;

	int
		count,
		loop;

	entity
		*new_entity;

	ASSERT (parent);

	//
	// determine constants
	//

	texture = smoke_list_component->animated_texture;

	count = smoke_list_component->sprite_count;

	if ( count < 1 )
	{
		return 0;
	}

	scale = smoke_list_component->scale;

	lifetime = smoke_list_component->lifetime;

	animation_frequency = smoke_list_component->animation_frequency;

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		//
		// create each individual element
		//

		pos = get_local_entity_vec3d_ptr( parent, VEC3D_TYPE_POSITION );

		new_entity = create_local_entity
		(
			ENTITY_TYPE_SPRITE,
			entity_index_list[ loop ],
			ENTITY_ATTR_PARENT (LIST_TYPE_SPECIAL_EFFECT, parent),
			ENTITY_ATTR_CHILD_PRED (LIST_TYPE_UPDATE, parent),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ANIMATED_TEXTURE, texture),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_RED, smoke_list_component->red),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_GREEN, smoke_list_component->green),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_BLUE, smoke_list_component->blue),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_ALPHA, smoke_list_component->alpha),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ADDITIVE, smoke_list_component->additive),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_MAX_TURN_RATE, smoke_list_component->rotation_rate),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_START_SCALE, scale),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_END_SCALE, scale),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SPRITE_LIFETIME, lifetime),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_ANIMATION_FREQUENCY, animation_frequency),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos->x, pos->y, pos->z),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_RELATIVE_POSITION, relative_position->x, relative_position->y, relative_position->z),
			ENTITY_ATTR_END
		);

		entity_index_list[ loop ] = get_local_entity_index( new_entity );

	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_smoke_list_trails( meta_smoke_list_component *smoke_list_component, entity *parent, vec3d *relative_position, float width_adjustment, int *entity_index_list )
{
	float
		lifetime = 0.0;

	entity
		*new_entity,
		*effect_list_parent;

	vec3d
		*pos;

	if ( smoke_list_component->trail_count < 1 )
	{
		return 0;
	}

	ASSERT (smoke_list_component->trail_count == 1 );

	//
	// create trail entity
	//

	if (parent)
	{
		pos = get_local_entity_vec3d_ptr( parent, VEC3D_TYPE_POSITION );
	}
	else
	{
		//
		// if no parent is specified, the relative position is used as the absolute position
		//

		pos = relative_position;

		ASSERT (pos);
	}

	if (width_adjustment != 0.0)
	{
		width_adjustment -= smoke_list_database [smoke_list_component->trail_type].radius_start;
	}

	//
	// some smoke lists should not be linked to a parent, even though a parent entity is passed across ( for position ref etc.. )
	//

	if (smoke_list_database [smoke_list_component->trail_type].lock_to_parent)
	{
		effect_list_parent = parent;
	}
	else
	{
		effect_list_parent = NULL;
	}

	// arneh - let rockets generate smoke only as long as the rocket engine burns
	if (parent && parent->type == ENTITY_TYPE_WEAPON)
	{
		weapon* raw = (weapon *) get_local_entity_data (parent);
		lifetime = weapon_database[raw->mob.sub_type].burn_time;
	}

	if (lifetime == 0.0)
		lifetime = smoke_list_component->generator_lifetime;

	//
	// create entity
	//

	new_entity = create_local_entity
	(
		ENTITY_TYPE_SMOKE_LIST,
		entity_index_list[ 0 ],
		ENTITY_ATTR_PARENT (LIST_TYPE_SPECIAL_EFFECT, effect_list_parent),
		ENTITY_ATTR_CHILD_PRED (LIST_TYPE_UPDATE, effect_list_parent),
     	ENTITY_ATTR_INT_VALUE (INT_TYPE_SMOKE_TYPE, smoke_list_component->trail_type),
     	ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, smoke_list_component->entity_sub_type),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_INFINITE_GENERATOR, smoke_list_component->infinite),
     	ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_GENERATOR_LIFETIME, lifetime),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FREQUENCY, smoke_list_component->frequency),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SMOKE_LIFETIME, smoke_list_component->smoke_lifetime),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_WIDTH_ADJUSTMENT, width_adjustment),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos->x, pos->y, pos->z),
		ENTITY_ATTR_END
	);

	if (parent && relative_position)
	{
		set_local_entity_vec3d (new_entity, VEC3D_TYPE_RELATIVE_POSITION, relative_position);
	}

	entity_index_list[ 0 ] = get_local_entity_index( new_entity );

	update_client_server_entity( new_entity );

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int count_entities_in_meta_smoke_list( meta_smoke_list_types type )
{
	int
		comp,
		index_counter,
		num_components;

	meta_smoke_list_component
		*smoke_list_component;


	ASSERT (type > META_SMOKE_LIST_TYPE_NONE);

	ASSERT (type < NUM_META_SMOKE_LIST_TYPES );

	index_counter = 0;

	num_components = meta_smoke_list_database[ type ].number_of_components;

	for ( comp = 0 ; comp < num_components ; comp ++ )
	{

		smoke_list_component = &(meta_smoke_list_database[ type ].component[ comp ]);

		switch ( smoke_list_component->type )
		{
			case SMOKE_LIST_NONE:
			{
				break;
			}
			case SMOKE_LIST_SPRITES:
			{
				index_counter += smoke_list_component->sprite_count;

				break;
			}
			case SMOKE_LIST_TRAILS:
			{
				index_counter += smoke_list_component->trail_count;

				break;
			}
			default:
			{
				debug_fatal("META SMOKE LIST : Unknown component type %d", smoke_list_component->type );
			}
		}
	}

	return index_counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 23OCT11 Casm Meta Smoke database import/export begin
#define SMOKE_LIST_DECLARATION(x)
#define SMOKE_LIST(x)
#define SMOKE_LIST_(x)
#define META_SMOKE_LIST_DECLARATION(x)
#define META_SMOKE_LIST(x) #x,
#define META_SMOKE_LIST_(x) NULL
const char* meta_smoke_list_names[] =
{
#include "sl_types.h"
};
#undef SMOKE_LIST_DECLARATION
#undef SMOKE_LIST
#undef SMOKE_LIST_
#undef META_SMOKE_LIST_DECLARATION
#undef META_SMOKE_LIST
#undef META_SMOKE_LIST_

int get_meta_smoke_type_by_name ( const char *name )
{
	int
		count;

	for ( count = 0; meta_smoke_list_names[count]; count++ )
	{
		if ( !stricmp ( name, meta_smoke_list_names[count] ) )
		{
			return count;
		}
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define META_SMOKE_LIST_DATABASE_FILENAME "METASMOK.CSV"

static void export_meta_smoke_list_database (void)
{
	FILE
		*file;
	int
		count1,
		count2;
	const meta_smoke_list_data
		*meta_smoke;
	const meta_smoke_list_component
		*co;

	file = safe_fopen (META_SMOKE_LIST_DATABASE_FILENAME, "w");
	fprintf (file, "META_SMOKE;2\n");
	fprintf (file,
		"#Meta Smoke index;Meta Smoke name\n"
		"#SPRITES;Animated texture;Sprite count;"
			"Color (red;green;blue;alpha);"
			"Animation frequency;Lifetime;Scale;Rotation rate;"
			"Additive\n"
		"#TRAILS;Trail type;"
			"Effect;"
			"Trail count;Infinite;"
			"Generator lifetime;Frequency;Smoke lifetime\n"
		);
	for (count1 = 1; count1 < NUM_META_SMOKE_LIST_TYPES; count1++)
	{
		meta_smoke = &meta_smoke_list_database[count1];
		fprintf(file,
			"%i;%s\n",
			count1, meta_smoke_list_names[count1]);
		for (count2 = 0; count2 < meta_smoke->number_of_components; count2++)
		{
			co = &meta_smoke->component[count2];
			switch (co->type)
			{
			case SMOKE_LIST_SPRITES:
				fprintf (file,
					"SPRITES;%s;%i;"
					"%i;%i;%i;%i;"
					"%f;%f;%f;%f;"
					"%i\n",
					texture_animation_names[co->animated_texture], co->sprite_count,
					co->red, co->green, co->blue, co->alpha,
					co->animation_frequency, co->lifetime, co->scale, co->rotation_rate,
					co->additive);
				break;
			case SMOKE_LIST_TRAILS:
				fprintf (file,
					"TRAILS;%s;"
					"%s;"
					"%i;%i;"
					"%f;%f;%f\n",
					smoke_list_types_names[co->trail_type],
					entity_sub_type_effect_names[co->entity_sub_type],
					co->trail_count, co->infinite,
					co->generator_lifetime, co->frequency, co->smoke_lifetime);
				break;
			default:
				ASSERT(FALSE);
			}
		}
	}
	safe_fclose (file);
}

static void import_meta_smoke_list_database (void)
{
	FILE
		*file;
	char
		buf[2048],
		*ptr,
		*name,
		*effect;
	int
		count,
		type;
	meta_smoke_list_data
		*meta_smoke;
	meta_smoke_list_component
		*co;
	int
		red,
		green,
		blue,
		alpha,
		additive;

	file = safe_fopen(META_SMOKE_LIST_DATABASE_FILENAME, "r");
	fgets(buf, sizeof (buf), file);
	if (!strcmp(buf, "META_SMOKE;2\n"))
	{
		while (fgets(buf, sizeof (buf), file))
		{
			ptr = strchr(buf, '#');
			if (ptr)
			{
				*ptr = '\0';
			}
			ptr = strchr(buf, ';');
			if (!ptr)
			{
				continue;
			}
			*ptr = '\0';

			type = NUM_SMOKE_LIST_COMPONENT_TYPES;
			if (!strcmp(buf, "SPRITES"))
			{
				type = SMOKE_LIST_SPRITES;
			}
			else if (!strcmp(buf, "TRAILS"))
			{
				type = SMOKE_LIST_TRAILS;
			}

			if (type == NUM_SMOKE_LIST_COMPONENT_TYPES)
			{
				meta_smoke = NULL;
				if (sscanf(buf, "%i", &count) != 1 || count < 0 || count >= NUM_META_SMOKE_LIST_TYPES)
				{
					continue;
				}
				meta_smoke = &meta_smoke_list_database[count];
				meta_smoke->number_of_components = 0;
			}
			else
			{
				if (!meta_smoke)
				{
					continue;
				}

				name = ptr + 1;
				ptr = strchr(name, ';');
				if (!ptr)
				{
					continue;
				}
				*ptr = 0;

				ASSERT (meta_smoke->number_of_components < MAX_COMPONENTS_PER_META_SMOKE_LIST);
				co = &meta_smoke->component[meta_smoke->number_of_components];
				switch (type)
				{
				case SMOKE_LIST_SPRITES:
					{
						if (sscanf(ptr + 1,
							"%i;"
							"%i;%i;%i;%i;"
							"%f;%f;%f;%f;"
							"%i",
							&co->sprite_count,
							&red, &green, &blue, &alpha,
							&co->animation_frequency, &co->lifetime, &co->scale, &co->rotation_rate,
							&additive) != 9)
						{
							continue;
						}
						co->animated_texture = (texture_animation_indices)add_new_animation(name);
						co->red = (unsigned char)bound (red, 0, 255);
						co->green = (unsigned char)bound (green, 0, 255);
						co->blue = (unsigned char)bound (blue, 0, 255);
						co->alpha = (unsigned char)bound (alpha, 0, 255);
						co->additive = additive != 0;
						meta_smoke->number_of_components++;
						break;
					}
				case SMOKE_LIST_TRAILS:
					{
						effect = ptr + 1;
						ptr = strchr(effect, ';');
						if (!ptr)
						{
							continue;
						}
						*ptr = '\0';
						count = get_smoke_type_by_name(name);
						if (count < 0)
						{
							continue;
						}
						co->trail_type = (smoke_list_types)count;
						co->entity_sub_type = -1;
						for (count = ENTITY_SUB_TYPE_EFFECT_PARTICLE; count < NUM_ENTITY_SUB_TYPE_EFFECTS; count++)
						{
							if (!strcmp(effect, entity_sub_type_effect_names[count]))
							{
								co->entity_sub_type = count;
								break;
							}
						}
						if (co->entity_sub_type < 0)
						{
							continue;
						}
						if (sscanf(ptr + 1,
							"%i;%i;"
							"%f;%f;%f",
							&co->trail_count, &co->infinite,
							&co->generator_lifetime, &co->frequency, &co->smoke_lifetime) != 5)
						{
							continue;
						}
						meta_smoke->number_of_components++;
						break;
					}
				default:
					ASSERT(FALSE);
				};
			}
		}
	}
	safe_fclose (file);
}
// 23OCT11 Casm Meta Smoke database import/export end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_meta_smoke_list_database(void)
{

	meta_smoke_list_component
		*smoke_list_info;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// GENERIC ROCKET TRAIL
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL ].number_of_components = 3;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_GREY_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	10.0;
	smoke_list_info->frequency 				=	0.05;
	smoke_list_info->smoke_lifetime 			=	4.0;

	//
	// component 1
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL ].component[ 1 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_ADDITIVE_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	10.0;
	smoke_list_info->frequency 				=	0.05;
	smoke_list_info->smoke_lifetime 			=	0.6;

	//
	// component 2
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_GENERIC_ROCKET_TRAIL ].component[ 2 ]);

	smoke_list_info->type 						=	SMOKE_LIST_SPRITES;

	smoke_list_info->animated_texture		=	TEXTURE_ANIMATION_INDEX_MISSILE_FLARE;

	smoke_list_info->sprite_count	 			=	1;

	smoke_list_info->red 						=	255;
	smoke_list_info->green 						=	255;
	smoke_list_info->blue 						=	255;
	smoke_list_info->alpha 						=	255;

	smoke_list_info->animation_frequency 	=	0.1;

	smoke_list_info->lifetime 					=	1.5;

	smoke_list_info->scale 						=	3.0;

	smoke_list_info->rotation_rate 	=	1.0;

	smoke_list_info->additive 					=	TRUE;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// SMALL ROCKET TRAIL
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_SMALL_ROCKET_TRAIL ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_SMALL_ROCKET_TRAIL ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_GREY_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	3.0;
	smoke_list_info->frequency 				=	0.08;
	smoke_list_info->smoke_lifetime 			=	3.0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// DECOY FLARE TRAIL
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_DECOY_FLARE_TRAIL ].number_of_components = 3;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_DECOY_FLARE_TRAIL ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_WHITE_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	8.0;
	smoke_list_info->frequency 				=	0.05;
	smoke_list_info->smoke_lifetime 			=	3.0;

	//
	// component 1
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_DECOY_FLARE_TRAIL ].component[ 1 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_ADDITIVE_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	8.0;
	smoke_list_info->frequency 				=	0.05;
	smoke_list_info->smoke_lifetime 			=	1.2;

	//
	// component 2
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_DECOY_FLARE_TRAIL ].component[ 2 ]);

	smoke_list_info->type 						=	SMOKE_LIST_SPRITES;

	smoke_list_info->animated_texture		=	TEXTURE_ANIMATION_INDEX_FLARE;

	smoke_list_info->sprite_count	 			=	1;

	smoke_list_info->red 						=	255;
	smoke_list_info->green 						=	255;
	smoke_list_info->blue 						=	255;
	smoke_list_info->alpha 						=	255;

	smoke_list_info->animation_frequency 	=	0.1;

	smoke_list_info->lifetime 					=	5.0;

	smoke_list_info->scale 						=	12.5;

	smoke_list_info->rotation_rate 	=	1.0;

	smoke_list_info->additive 					=	TRUE;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// INFINITE FIRE
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_INFINITE_FIRE ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_INFINITE_FIRE ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_FIRE;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_ON;
	smoke_list_info->frequency 				=	0.75;
	smoke_list_info->smoke_lifetime 			=	8.5;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// FIRE ( SHORT DURATION )
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_FIRE_SHORT_DURATION ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_FIRE_SHORT_DURATION ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_FIRE;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	180.0;
	smoke_list_info->frequency 				=	0.5;
	smoke_list_info->smoke_lifetime 			=	8.5;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// SMALL FIRE ( SHORT DURATION )
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_SMALL_FIRE_SHORT_DURATION ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_SMALL_FIRE_SHORT_DURATION ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_SMALL_FIRE;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	60.0;
	smoke_list_info->frequency 				=	0.2;
	smoke_list_info->smoke_lifetime 			=	4.5;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// VEHICLE DUST TRAIL
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_VEHICLE_DUST_TRAIL ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_VEHICLE_DUST_TRAIL ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_DUST_TRAIL_1;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_VEHICLE_WAKE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_OFF;
	smoke_list_info->frequency 				=	0.1;
	smoke_list_info->smoke_lifetime 			=	0.75;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// REAR SHIP WAKE
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_REAR_SHIP_WAKE ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_REAR_SHIP_WAKE ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_REAR_SHIP_WAKE;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_VEHICLE_WAKE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_OFF;
	smoke_list_info->frequency 				=	1.0;
	smoke_list_info->smoke_lifetime 			=	35.0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// FRONT SHIP WAKE
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_FRONT_SHIP_WAKE ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_FRONT_SHIP_WAKE ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_FRONT_SHIP_WAKE;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_VEHICLE_WAKE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_OFF;
	smoke_list_info->frequency 				=	1.0;
	smoke_list_info->smoke_lifetime 			=	35.0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// AIRCRAFT LIGHT DAMAGE
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_OFF;
	smoke_list_info->frequency 				=	0.06;
	smoke_list_info->smoke_lifetime 			=	2.0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// AIRCRAFT MEDIUM DAMAGE
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_MEDIUM_DAMAGE ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_MEDIUM_DAMAGE ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_AIRCRAFT_MEDIUM_DAMAGE_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_OFF;
	smoke_list_info->frequency 				=	0.06;
	smoke_list_info->smoke_lifetime 			=	2.0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// AIRCRAFT HEAVY DAMAGE
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE ].number_of_components = 2;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_OFF;
	smoke_list_info->frequency 				=	0.06;
	smoke_list_info->smoke_lifetime 			=	2.5;

	//
	// component 1
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE ].component[ 1 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_AIRCRAFT_ADDITIVE_DAMAGE_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	TRUE;

	smoke_list_info->generator_lifetime 	=	INFINITE_SMOKE_OFF;
	smoke_list_info->frequency 				=	0.05;
	smoke_list_info->smoke_lifetime 			=	0.55;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// AIRCRAFT_SMALL_TOUCHDOWN_TRAIL
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_SMALL_TOUCHDOWN_TRAIL ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_SMALL_TOUCHDOWN_TRAIL ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_AIRCRAFT_SMALL_TOUCHDOWN_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	1.0;
	smoke_list_info->frequency 				=	0.02;
	smoke_list_info->smoke_lifetime 			=	2.5;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// AIRCRAFT_LARGE_TOUCHDOWN_TRAIL
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_LARGE_TOUCHDOWN_TRAIL ].number_of_components = 1;

	//
	// component 0
	//

	smoke_list_info = &(meta_smoke_list_database[ META_SMOKE_LIST_TYPE_AIRCRAFT_LARGE_TOUCHDOWN_TRAIL ].component[ 0 ]);

	smoke_list_info->type 						=	SMOKE_LIST_TRAILS;

	smoke_list_info->trail_type	 			=	SMOKE_LIST_TYPE_AIRCRAFT_LARGE_TOUCHDOWN_TRAIL;

	smoke_list_info->entity_sub_type			=	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE;

	smoke_list_info->trail_count	 			=	1;

	smoke_list_info->infinite 					=	FALSE;

	smoke_list_info->generator_lifetime 	=	1.0;
	smoke_list_info->frequency 				=	0.04;
	smoke_list_info->smoke_lifetime 			=	4.5;

	// 23OCT11 Casm Meta Smoke database import/export
	if (file_exist (META_SMOKE_LIST_DATABASE_FILENAME))
	{
		import_meta_smoke_list_database ();
	}
	else
	{
		export_meta_smoke_list_database ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_meta_smoke_list_database(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



