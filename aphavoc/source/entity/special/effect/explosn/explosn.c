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

static int create_meta_explosion_sprites( meta_explosion_component *explosion_component, vec3d *position, entity *parent, int *entity_index_list );

static int create_meta_explosion_objects( meta_explosion_component *explosion_component, vec3d *position, int *entity_index_list );

static int create_meta_explosion_particles( meta_explosion_component *explosion_component, vec3d *position, int *entity_index_list );

static int create_meta_explosion_smoke_trails( meta_explosion_component *explosion_component, vec3d *position, entity *parent, int *entity_index_list );

static int create_meta_explosion_sound_effect( meta_explosion_component *explosion_component, vec3d *position, int *entity_index_list );

static void damage_objects_within_explosion_damage_radius (entity *en, entity *target);

static void create_client_server_dust_object_explosion_effect (entity *en, vec3d *pos, int explosive_power);

static void create_client_server_explosive_object_explosion_effect (entity *en, vec3d *pos, int explosive_power);

static void create_client_server_flammable_object_explosion_effect (entity *en, vec3d *pos, int explosive_power);

static void create_client_server_explosion_effect (meta_explosion_types type, vec3d *position, entity *parent);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_explosion( meta_explosion_types type, vec3d *position, entity *parent, int *entity_index_list )
{
	int
		comp,
		index_counter,
		num_components;

	int
		create_stack_attributes;

	meta_explosion_component
		*explosion_component;

	ASSERT (type >= 0);

	ASSERT (type < NUM_META_EXPLOSION_TYPES);

	ASSERT (type != META_EXPLOSION_TYPE_NONE);

	index_counter = 0;

	create_stack_attributes = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{
		set_force_local_entity_create_stack_attributes (TRUE);
	}

	num_components = meta_explosion_database[ type ].number_of_components;

	for ( comp = 0 ; comp < num_components ; comp ++ )
	{

		explosion_component = &(meta_explosion_database[ type ].component[ comp ]);

		switch ( explosion_component->type )
		{
			case EXPLOSION_SPRITES:
			{
				index_counter += create_meta_explosion_sprites( explosion_component, position, parent, &entity_index_list[ index_counter ] );

				break;
			}
			case EXPLOSION_OBJECTS:
			{
				index_counter += create_meta_explosion_objects( explosion_component, position, &entity_index_list[ index_counter ] );

				break;
			}
			case EXPLOSION_PARTICLES:
			{
				index_counter += create_meta_explosion_particles( explosion_component, position, &entity_index_list[ index_counter ] );

				break;
			}
			case EXPLOSION_SMOKE_TRAILS:
			{
				index_counter += create_meta_explosion_smoke_trails( explosion_component, position, parent, &entity_index_list[ index_counter ] );

				break;
			}
			case EXPLOSION_SOUND_EFFECT:
			{
				index_counter += create_meta_explosion_sound_effect( explosion_component, position, &entity_index_list[ index_counter ] );

				break;
			}
			default:
			{
				debug_fatal("EXPLOSION : Unknown component type %d", explosion_component->type );
			}
		}
	}

	//
	// Draw little icon on map
	//

	if (meta_explosion_database[ type ].show_on_map)
	{
		add_map_event (MAP_EVENT_EXPLOSION, position->x, position->z, 1.5);
	}

	set_force_local_entity_create_stack_attributes (create_stack_attributes);

	return index_counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_explosion_sprites( meta_explosion_component *explosion_component, vec3d *position, entity *parent, int *entity_index_list )
{
	vec3d
		pos,
		offset;

	float
		delay,
		lifetime,
		lifetime_min,
		lifetime_max,
//		scale,
		scale_min,
		scale_max,
		radius,
		blast_radius,
		heading,
		pitch;

	texture_animation_indices
		texture;

	int
		count,
		loop;

	entity
		*new_entity;

	//
	// determine constants
	//

	texture = explosion_component->animated_texture;

	count = explosion_component->sprite_count;

	if ( count < 1 )
	{
		return 0;
	}

	scale_min = explosion_component->scale_min;
	scale_max = explosion_component->scale_max;

	lifetime_min = explosion_component->lifetime_min;
	lifetime_max = explosion_component->lifetime_max;

	#if DEBUG_MODULE >= 2

	debug_log("EXPLOSION : creating %d sprites", count );

	#endif

	if (explosion_component->blast_radius < 0.0)
	{

		struct OBJECT_3D_BOUNDS
			*bounding_box;

		vec3d
			d;

		ASSERT (parent);

		bounding_box = get_object_3d_bounding_box (get_local_entity_int_value (parent, INT_TYPE_OBJECT_3D_SHAPE));

		d.x = bounding_box->xmax - bounding_box->xmin;
//		d.y = bounding_box->ymax - bounding_box->ymin;
		d.y = 0.0;
		d.z = bounding_box->zmax - bounding_box->zmin;

		blast_radius = get_3d_vector_magnitude (&d) * (-explosion_component->blast_radius) * 0.5;
	}
	else
	{
		blast_radius = explosion_component->blast_radius;
	}

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		//
		// create each individual element
		//

		delay = -( explosion_component->delay_max * frand1() );
//		delay = - explosion_component->delay_max;

//		scale = scale_min + fabs( ( scale_max - scale_min ) * sfrand1() );

		lifetime = lifetime_min + fabs( ( lifetime_max - lifetime_min ) * sfrand1() );

		if ( blast_radius > 0.0 )
		{
			heading = ( PI * sfrand1() );

			if ( explosion_component->blast_hemisphere_only )
			{
				pitch = ( PI_OVER_TWO * frand1() );
			}
			else
			{
				pitch = ( PI_OVER_TWO * sfrand1() );
			}

			get_3d_unit_vector_from_heading_and_pitch( &offset, heading, pitch );

//			radius = frand1() * blast_radius;
			radius = blast_radius;

			pos.x = position->x + ( radius * offset.x );
			pos.y = position->y + ( radius * offset.y );
			pos.z = position->z + ( radius * offset.z );
		}
		else
		{
			pos.x = position->x;
			pos.y = position->y;
			pos.z = position->z;
		}

		bound_position_to_map_volume( &pos );

		new_entity = create_local_entity
		(
			ENTITY_TYPE_SPRITE,
			entity_index_list[ loop ],
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ANIMATED_TEXTURE, texture),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_RED, explosion_component->red),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_GREEN, explosion_component->green),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_BLUE, explosion_component->blue),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_ALPHA, explosion_component->alpha),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ADDITIVE, explosion_component->additive),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_MAX_TURN_RATE, explosion_component->rotation_rate),
//			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SCALE, scale),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_START_SCALE, scale_min),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_END_SCALE, scale_max),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_EFFECT_LIFETIME, delay),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SPRITE_LIFETIME, lifetime),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_ANIMATION_FREQUENCY, explosion_component->animation_frequency),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos.x, pos.y, pos.z),
			ENTITY_ATTR_END
		);

		entity_index_list[ loop ] = get_local_entity_index( new_entity );

		#if DEBUG_MODULE >= 2

		debug_log( "index : %d", entity_index_list[ loop ] );

		#endif
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_explosion_objects( meta_explosion_component *explosion_component, vec3d *position, int *entity_index_list )
{
	vec3d
		pos,
		offset;

	float
		d,
		delay,
		state,
		lifetime,
		lifetime_min,
		lifetime_max,
		scale,
		scale_min,
		scale_max,
		radius,
		heading,
		pitch;

	int
		count,
		loop;

	entity
		*new_entity;

	//
	// determine constants
	//

	count = explosion_component->object_count;

	if ( count < 1 )
	{
		return 0;
	}

	scale_min = explosion_component->scale_min;
	scale_max = explosion_component->scale_max;

	lifetime_min = explosion_component->lifetime_min;
	lifetime_max = explosion_component->lifetime_max;

	#if DEBUG_MODULE >= 2

	debug_log("EXPLOSION : creating %d objects", count );

	#endif

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		//
		// create each individual element
		//

		if ( explosion_component->blast_radius > 0.0 )
		{
			heading = ( PI * sfrand1() );

			if ( explosion_component->blast_hemisphere_only )
			{
				pitch = ( PI_OVER_TWO * frand1() );
			}
			else
			{
				pitch = ( PI_OVER_TWO * sfrand1() );
			}

			get_3d_unit_vector_from_heading_and_pitch( &offset, heading, pitch );

			d = frand1();

			radius = ( d * explosion_component->blast_radius );

			pos.x = position->x + ( radius * offset.x );
			pos.y = position->y + ( radius * offset.y );
			pos.z = position->z + ( radius * offset.z );
		}
		else
		{
			d = 0.0;

			pos.x = position->x;
			pos.y = position->y;
			pos.z = position->z;
		}

		bound_position_to_map_volume( &pos );

		// set delay so the explosion expands outwards
		delay = - fabs( explosion_component->delay_max );

		scale = scale_min + fabs( ( scale_max - scale_min ) * ( 1.0 - d ) );

		lifetime = lifetime_min + fabs( ( lifetime_max - lifetime_min ) * ( 1.0 - d ) );

		state = delay / lifetime;

		new_entity = create_local_entity
		(
			ENTITY_TYPE_EXPLOSION,
			entity_index_list[ loop ],
			ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, explosion_component->object_3d_shape),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_RED, explosion_component->red),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_GREEN, explosion_component->green),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_BLUE, explosion_component->blue),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_ALPHA, explosion_component->alpha),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SCALE, scale),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_EXPLOSION_STATE, state),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_ANIMATION_FREQUENCY, lifetime),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos.x, pos.y, pos.z),
			ENTITY_ATTR_END
		);

		entity_index_list[ loop ] = get_local_entity_index( new_entity );

		#if DEBUG_MODULE >= 2

		debug_log( "index : %d", entity_index_list[ loop ] );

		#endif
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_explosion_particles( meta_explosion_component *explosion_component, vec3d *position, int *entity_index_list )
{
	entity
		*particle_entity;

	int
		loop,
		count,
		trail_type;

	entity
		*new_entity;


	count = explosion_component->particle_count;

	if ( count < 1 )
	{
		return 0;
	}

	//
	// create particle entity
	//

	#if DEBUG_MODULE >= 2

	debug_log("EXPLOSION : creating %d particles", count );

	#endif

	particle_entity = create_local_entity
	(
		ENTITY_TYPE_PARTICLE,
		entity_index_list[ 0 ],
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_EFFECT_PARTICLE),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_PARTICLE_COUNT, count),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_INITIAL_SPEED, explosion_component->initial_speed),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_MOTION_VECTOR_PITCH, sin(rad(explosion_component->motion_vector_pitch))),
		ENTITY_ATTR_END
	);

	entity_index_list[ 0 ] = get_local_entity_index( particle_entity );

	#if DEBUG_MODULE >= 2

	debug_log( "index : %d", entity_index_list[ 0 ] );

	#endif

	//
	// create and link smoke trails to the particle
	//

	#if DEBUG_MODULE >= 2

	debug_log("EXPLOSION : creating %d smoke trails", count );

	#endif

	trail_type = explosion_component->trail_type;

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		new_entity = create_local_entity
		(
			ENTITY_TYPE_SMOKE_LIST,
			entity_index_list[ loop + 1 ],
			ENTITY_ATTR_PARENT (LIST_TYPE_SPECIAL_EFFECT, particle_entity),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_PARTICLE),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_SMOKE_TYPE, trail_type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_INFINITE_GENERATOR, FALSE),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_GENERATOR_LIFETIME, explosion_component->particle_generator_lifetime),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FREQUENCY, explosion_component->frequency),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SMOKE_LIFETIME, explosion_component->smoke_lifetime),
//			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SCALE, explosion_component->trail_scale),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
			ENTITY_ATTR_END
		);

		entity_index_list[ loop + 1 ] = get_local_entity_index( new_entity );

		#if DEBUG_MODULE >= 2

		debug_log( "index : %d", entity_index_list[ loop + 1 ] );

		#endif

	}

	return ( count + 1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_explosion_smoke_trails( meta_explosion_component *explosion_component, vec3d *position, entity *parent, int *entity_index_list )
{

	int
		loop,
		count,
		trail_type;

	entity
		*new_entity,
		*effect_list_parent;

	vec3d
		*iv;

	count = explosion_component->trail_count;

	if ( count < 1 )
	{
		return 0;
	}

	#if DEBUG_MODULE >= 2

	debug_log("EXPLOSION : creating %d smoke trails", count );

	#endif

	trail_type = explosion_component->trail_type;

	iv = &(explosion_component->initial_velocity);

	//
	// some smoke lists should not be linked to a parent, even though a parent entity is passed across ( for position ref etc.. )
	//

	if ((!parent) || (!get_local_entity_int_value (parent, INT_TYPE_IDENTIFY_MOBILE)) || (!smoke_list_database [trail_type].lock_to_parent))
	{
		effect_list_parent = NULL;
	}
	else
	{
		effect_list_parent = parent;
	}

	//
	// create smoke trails
	//

	for ( loop = 0 ; loop < count ; loop ++ )
	{

		new_entity = create_local_entity
		(
			ENTITY_TYPE_SMOKE_LIST,
			entity_index_list[ loop ],
			ENTITY_ATTR_PARENT (LIST_TYPE_SPECIAL_EFFECT, effect_list_parent),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_TRAIL),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_SMOKE_TYPE, trail_type),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_GENERATOR_LIFETIME, explosion_component->generator_lifetime),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FREQUENCY, explosion_component->frequency),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SMOKE_LIFETIME, explosion_component->smoke_lifetime),
//			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SCALE, explosion_component->scale),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_INITIAL_VELOCITY, sfrand1() * iv->x, frand1() * iv->y, sfrand1() * iv->z),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
			ENTITY_ATTR_END
		);

		entity_index_list[ loop ] = get_local_entity_index( new_entity );

		#if DEBUG_MODULE >= 2

		debug_log( "index : %d", entity_index_list[ loop ] );

		#endif
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_meta_explosion_sound_effect( meta_explosion_component *explosion_component, vec3d *position, int *entity_index_list )
{
	entity
		*new_entity;
	int sampleToUse;

	#if DEBUG_MODULE >= 2

	debug_log("EXPLOSION : creating sound effect" );

	#endif


	if ((explosion_component->sound_type == SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1) || 
		(explosion_component->sound_type == SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_2) ||
		(explosion_component->sound_type == SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_3) ||
		(explosion_component->sound_type == SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_4) ||
		(explosion_component->sound_type == SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_5) ||
		(explosion_component->sound_type == SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_6) ||
		(explosion_component->sound_type == SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_7))
	{
		sampleToUse = 1 + (int) (7.0*rand()/(RAND_MAX+1.0));
		switch(sampleToUse)
		{
			case 1:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1;
					break;
			case 2:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_2;
					break;
			case 3:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_3;
					break;
			case 4:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_4;
					break;
			case 5:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_5;
					break;
			case 6:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_6;
					break;
			case 7:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_7;
					break;
			default:	explosion_component->sound_type = SOUND_SAMPLE_INDEX_EXPLOSION_DISTANT_1;
					break;
		}
	}


	new_entity = create_local_sound_effect_entity
	(
		entity_index_list [0],
		get_local_sector_entity (position),
		ENTITY_SIDE_NEUTRAL,
		ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
		SOUND_CHANNEL_SOUND_EFFECT,
		SOUND_LOCALITY_ALL,
		position,										// position
		explosion_component->sound_volume,		// amplification
		1.0,						// Werewolf pitch
		TRUE,												// valid sound effect
		FALSE,											// looping
		1,													// sample count
		&(explosion_component->sound_type)		// sample index list
	);

	entity_index_list[ 0 ] = get_local_entity_index( new_entity );

	#if DEBUG_MODULE >= 2

	debug_log( "index : %d", entity_index_list[ 0 ] );

	#endif

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int count_entities_in_meta_explosion( meta_explosion_types type )
{
	int
		comp,
		index_counter,
		num_components;

	meta_explosion_component
		*explosion_component;

	ASSERT (type >= 0);

	ASSERT (type < NUM_META_EXPLOSION_TYPES);

	ASSERT (type != META_EXPLOSION_TYPE_NONE);

	index_counter = 0;

	num_components = meta_explosion_database[ type ].number_of_components;

	for ( comp = 0 ; comp < num_components ; comp ++ )
	{

		explosion_component = &(meta_explosion_database[ type ].component[ comp ]);

		switch ( explosion_component->type )
		{
			case EXPLOSION_SPRITES:
			{
				index_counter += explosion_component->sprite_count;

				break;
			}
			case EXPLOSION_OBJECTS:
			{
				index_counter += explosion_component->object_count;

				break;
			}
			case EXPLOSION_PARTICLES:
			{
				index_counter += ( explosion_component->particle_count + 1 );

				break;
			}
			case EXPLOSION_SMOKE_TRAILS:
			{
				index_counter += explosion_component->trail_count;

				break;
			}
			case EXPLOSION_SOUND_EFFECT:
			{
				index_counter += 1;

				break;
			}
			default:
			{
				debug_fatal("EXPLOSION : Unknown component type %d", explosion_component->type );
			}
		}
	}

	return index_counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_weapon_killed_explosion_effect (entity *en)
{
	vec3d
		*pos;

	meta_explosion_types
		explosion_type,
		collision_type;

	weapon_kill_codes
		kill_code;

	weapon_warhead_types
		warhead_type;

	terrain_3d_point_data
		point_data;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	kill_code = (weapon_kill_codes) get_local_entity_int_value (en, INT_TYPE_WEAPON_KILL_CODE);

	warhead_type = (weapon_warhead_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_WARHEAD_TYPE);

	// calculate type of resulting explosion

	switch (kill_code)
	{
		case WEAPON_KILL_CODE_HIT_LAND:
		case WEAPON_KILL_CODE_HIT_TARGET:
		case WEAPON_KILL_CODE_OVERSHOT_TARGET:
		case WEAPON_KILL_CODE_SELF_DESTRUCT:
		{
			explosion_type = get_suitable_weapon_explosion_type (en, WEAPON_KILL_CODE_OK);
			break;
		}
		default:
			explosion_type = META_EXPLOSION_TYPE_NONE;
	}

	// calculate type of collision effects

	switch (kill_code)
	{
		case WEAPON_KILL_CODE_HIT_WATER:
		case WEAPON_KILL_CODE_HIT_LAND:
		case WEAPON_KILL_CODE_HIT_TARGET:
		{
			collision_type = get_suitable_weapon_explosion_type (en, kill_code);
			break;
		}
		default:
			collision_type = META_EXPLOSION_TYPE_NONE;
	}

	//
	// apply damage to surrounding objects and/or target
	//

	switch (kill_code)
	{
		case WEAPON_KILL_CODE_EXHAUSTED:
		case WEAPON_KILL_CODE_OUT_OF_BOUNDS:
		case WEAPON_KILL_CODE_HIT_WATER:
		{
			//
			// do nothing
			//

			break;
		}
		case WEAPON_KILL_CODE_HIT_LAND:
		{
			//
			// create a crater
			//

			memset (&point_data, 0, sizeof (terrain_3d_point_data));

			ASSERT(point_inside_map_area(pos));
			get_3d_terrain_point_data (pos->x, pos->z, &point_data);

			if (get_terrain_type_draw_crater (point_data.terrain_type))
			{
				create_client_server_weapon_hit_ground_crater (en, pos);
			}

			damage_objects_within_explosion_damage_radius (en, NULL);

			//
			// deliberate fall-through
			//
		}
		case WEAPON_KILL_CODE_OVERSHOT_TARGET:
		case WEAPON_KILL_CODE_SELF_DESTRUCT:
		{
			//
			// notify all objects within blast radius
			//

			damage_objects_within_explosion_damage_radius (en, NULL);

			break;
		}
		case WEAPON_KILL_CODE_HIT_TARGET:
		{
			entity
				*target;

			target = get_local_entity_parent (en, LIST_TYPE_TARGET);

			//
			// notify the target of a direct hit
			//

			if (target)
			{
				if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
				{
					notify_local_entity (ENTITY_MESSAGE_COLLISION, target, en, 0.0);
				}
			}

			//
			// notify all objects within blast radius ( except the target )
			//

			damage_objects_within_explosion_damage_radius (en, target);

			break;
		}
		default:
		{
			debug_fatal ("EXPLOSN : Invalid weapon kill code ( %d )", kill_code);
		}
	}

	#if DEBUG_MODULE > 1

	debug_log ("EXPLOSN : Creating Weapon Killed effect, type %d, at %f, %f", explosion_type, pos->x, pos->z);

	#endif

	if (explosion_type != META_EXPLOSION_TYPE_NONE)
		create_client_server_explosion_effect (explosion_type, pos, NULL);
	
	if (collision_type != META_EXPLOSION_TYPE_NONE)
		create_client_server_explosion_effect (collision_type, pos, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_objects_within_explosion_damage_radius (entity *en, entity *target)
{
	float
		range,
		temp_x,
		temp_z,
		damage_radius,
		damage_modifier;

	int
		sx,
		sz,
		min_sector_x,
		max_sector_x,
		min_sector_z,
		max_sector_z,
		damage_capability;

	vec3d
		*explosion_position,
		*object_position;

	entity
		*sect,
		*object;
	weapon_warhead_types
		warhead_type;

	warhead_type = (weapon_warhead_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_WARHEAD_TYPE);
	damage_capability = get_local_entity_int_value (en, INT_TYPE_DAMAGE_CAPABILITY);

	damage_radius = sqrt((float)damage_capability);

	if (damage_radius == 0.0)
	{
		return;
	}

	explosion_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	temp_x = explosion_position->x - damage_radius;
	temp_z = explosion_position->z - damage_radius;

	get_x_sector (min_sector_x, temp_x);
	get_z_sector (min_sector_z, temp_z);

	temp_x = explosion_position->x + damage_radius;
	temp_z = explosion_position->z + damage_radius;

	get_x_sector (max_sector_x, temp_x);
	get_z_sector (max_sector_z, temp_z);

	min_sector_x = bound (min_sector_x, MIN_MAP_X_SECTOR, MAX_MAP_X_SECTOR);
	max_sector_x = bound (max_sector_x, MIN_MAP_X_SECTOR, MAX_MAP_X_SECTOR);

	min_sector_z = bound (min_sector_z, MIN_MAP_Z_SECTOR, MAX_MAP_Z_SECTOR);
	max_sector_z = bound (max_sector_z, MIN_MAP_Z_SECTOR, MAX_MAP_Z_SECTOR);

	for (sz = min_sector_z; sz <= max_sector_z; sz ++)
	{
		for (sx = min_sector_x; sx <= max_sector_x; sx ++)
		{
			sect = get_local_raw_sector_entity (sx, sz);

			//
			// search for damagable objects
			//

			object = get_local_entity_first_child (sect, LIST_TYPE_SECTOR);

			while (object)
			{
				if (object == target)
				{
					//
					// skip target, as it is dealt with elsewhere
					//

					object = get_local_entity_child_succ (object, LIST_TYPE_SECTOR);

					continue;
				}

				switch (object->type)
				{
					case ENTITY_TYPE_ANTI_AIRCRAFT:
					case ENTITY_TYPE_CITY_BUILDING:
					case ENTITY_TYPE_FIXED_WING:
					case ENTITY_TYPE_HELICOPTER:
					case ENTITY_TYPE_PERSON:
					case ENTITY_TYPE_PYLON:
					case ENTITY_TYPE_ROUTED_VEHICLE:
					case ENTITY_TYPE_SCENIC:
					case ENTITY_TYPE_SEGMENT:
					case ENTITY_TYPE_SHIP_VEHICLE:
					case ENTITY_TYPE_SITE:
					case ENTITY_TYPE_SITE_UPDATABLE:
					case ENTITY_TYPE_WEAPON:
					{
						if (get_local_entity_int_value (object, INT_TYPE_ALIVE))
						{
							object_position = get_local_entity_vec3d_ptr (object, VEC3D_TYPE_POSITION);

							if (object_position)
							{
								range = get_3d_range (explosion_position, object_position);

								if (range && (range < damage_radius))
								{
									damage_modifier = range / damage_radius; // less value - more damage!

									#if DEBUG_MODULE
									debug_log ("EXPLOSN : damage radius %.2f, range %.2f, damage modifier = %f", damage_radius, range, damage_modifier);
									#endif

									if (object->type != ENTITY_TYPE_WEAPON)
										notify_local_entity (ENTITY_MESSAGE_COLLISION, object, en, damage_modifier);
									else if (1 - pow(damage_modifier, pow((float)(warhead_type - 3) / 3, 1.5f)) > 0.75 && get_local_entity_int_value (object, INT_TYPE_WEAPON_ROCKET))
									{
										#if DEBUG_MODULE
										debug_log ("EXPLOSN : MISSILE DESTROYED!");
										#endif

										set_local_entity_int_value (object, INT_TYPE_WEAPON_KILL_CODE, WEAPON_KILL_CODE_OVERSHOT_TARGET);
									}
								}
							}
						}

						break;
					}
				}

				object = get_local_entity_child_succ (object, LIST_TYPE_SECTOR);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_collision_effect (vec3d *pos, dynamics_collision_surface_types surface, unsigned power)
{
	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);
	ASSERT (power < 5);
	ASSERT (surface >= 0 && surface < NUM_DYNAMICS_COLLISION_SURFACE_TYPES);

	#if DEBUG_MODULE

	debug_log ("EXPLOSN : Creating Object Hit Ground effect, type %d, at %f, %f", type, pos->x, pos->z);

	#endif

	switch (surface)
	{
		case DYNAMICS_COLLISION_SURFACE_WATER:
		{
			switch (power)
			{
				case 1:
				{
					create_client_server_explosion_effect (MEDIUM_WATER_META_EXPLOSION, pos, NULL);
					break;
				}
				case 2:
				{
					create_client_server_explosion_effect (LARGE_WATER_META_EXPLOSION, pos, NULL);
					break;
				}
			}
			break;
		}
		case DYNAMICS_COLLISION_SURFACE_GROUND:
		{
			switch (power)
			{
				case 1:
				{
					create_client_server_explosion_effect (SMALL_GROUND_META_EXPLOSION, pos, NULL);
					break;
				}
				case 2:
				{
					create_client_server_explosion_effect (MEDIUM_GROUND_META_EXPLOSION, pos, NULL);
					break;
				}
				case 3:
				{
					create_client_server_explosion_effect (LARGE_GROUND_META_EXPLOSION, pos, NULL);
					break;
				}
				case 4:
				{
					create_client_server_explosion_effect (XLARGE_GROUND_META_EXPLOSION, pos, NULL);
					break;
				}
			}
			break;
		}
		case DYNAMICS_COLLISION_SURFACE_OBJECT:
		{
			switch (power)
			{
				case 1:
				{
					create_client_server_explosion_effect (SMALL_OBJECT_META_EXPLOSION, pos, NULL);
					break;
				}
				case 2:
				{
					create_client_server_explosion_effect (MEDIUM_OBJECT_META_EXPLOSION, pos, NULL);
					break;
				}
				case 3:
				{
					create_client_server_explosion_effect (LARGE_OBJECT_META_EXPLOSION, pos, NULL);
					break;
				}
			}
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_object_killed_explosion_effect (entity *en)
{
	vec3d
		pos;

	int
		explosive_power,
		explosive_quality;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	explosive_quality = get_local_entity_int_value (en, INT_TYPE_EXPLOSIVE_QUALITY);

	explosive_power = get_local_entity_int_value (en, INT_TYPE_EXPLOSIVE_POWER);

	if (explosive_power == EXPLOSIVE_POWER_NONE)
	{
		return;
	}

	get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &pos);

	if (explosive_quality & EXPLOSIVE_QUALITY_DUST)
	{
		create_client_server_dust_object_explosion_effect (en, &pos, explosive_power);
	}

	if (explosive_quality & EXPLOSIVE_QUALITY_EXPLOSIVE)
	{
		create_client_server_explosive_object_explosion_effect (en, &pos, explosive_power);
	}

	if (explosive_quality & EXPLOSIVE_QUALITY_FLAMMABLE)
	{
		create_client_server_flammable_object_explosion_effect (en, &pos, explosive_power);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_dust_object_explosion_effect (entity *en, vec3d *pos, int explosive_power)
{
	meta_explosion_types
		type;

	switch (explosive_power)
	{
		case EXPLOSIVE_POWER_LOW:
		{
			type = SMALL_DUST_META_EXPLOSION;

			break;
		}
		case EXPLOSIVE_POWER_MEDIUM:
		{
			type = MEDIUM_DUST_META_EXPLOSION;

			break;
		}
		case EXPLOSIVE_POWER_HIGH:
		{
			type = LARGE_DUST_META_EXPLOSION;

			break;
		}
		default:
		{
			return;
		}
	}

	#if DEBUG_MODULE

	debug_log ("EXPLOSN : Creating Object Killed Dust effect, type %d, at %f, %f ( object %s )", type, pos->x, pos->z, entity_type_names [en->type]);

	#endif

	create_client_server_explosion_effect (type, pos, en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_explosive_object_explosion_effect (entity *en, vec3d *pos, int explosive_power)
{
	meta_explosion_types
		type;

	switch (explosive_power)
	{
		case EXPLOSIVE_POWER_LOW:
		{
			type = SMALL_EXPLOSIVE_OBJECT_META_EXPLOSION;

			break;
		}
		case EXPLOSIVE_POWER_MEDIUM:
		{
			type = MEDIUM_EXPLOSIVE_OBJECT_META_EXPLOSION;

			break;
		}
		case EXPLOSIVE_POWER_HIGH:
		{
			type = LARGE_EXPLOSIVE_OBJECT_META_EXPLOSION;

			break;
		}
		default:
		{
			return;
		}
	}

	#if DEBUG_MODULE

	debug_log ("EXPLOSN : Creating Object Killed Explosive effect, type %d, at %f, %f ( object %s )", type, pos->x, pos->z, entity_type_names [en->type]);

	#endif

	create_client_server_explosion_effect (type, pos, en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_flammable_object_explosion_effect (entity *en, vec3d *pos, int explosive_power)
{
	//
	// currently only used for "smoking boots" on infantry...
	//

	switch (explosive_power)
	{
		case EXPLOSIVE_POWER_LOW:
		{
			create_client_server_meta_smoke_list_specified_offset (META_SMOKE_LIST_TYPE_SMALL_FIRE_SHORT_DURATION, en, NULL);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_client_server_explosion_effect (meta_explosion_types type, vec3d *position, entity *parent)
{
	int
		loop,
		count,
		*entity_index_list;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// create an array of entity index numbers and fill them all with ENTITY_INDEX_DONT_CARE
	//

	count = count_entities_in_meta_explosion (type);

	ASSERT (count);

	entity_index_list = (int *) malloc_fast_mem (sizeof (int) * count);

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		entity_index_list [loop] = ENTITY_INDEX_DONT_CARE;
	}

	//
	// call the create function which will create the entities on the server, and also fill in the entity index list
	//

	create_meta_explosion (type, position, parent, entity_index_list);

	//
	// now notify the clients to create same explosion and pass them the list of indices to use
	//

	transmit_entity_comms_message
	(
		ENTITY_COMMS_CREATE_META_EXPLOSION,
		NULL,
		type,
		position,
		parent,
		entity_index_list
	);

	//
	//
	//

	free_mem (entity_index_list);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



