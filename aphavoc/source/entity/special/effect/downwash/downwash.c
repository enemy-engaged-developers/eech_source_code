///////////////////////////////////////////////////////////////////////////////////////////
//	Filename		: DOWNWASH.C
//	Authors		: Xhit (Ingemar Persson)
//	Date			: 2003-03-28
//	Update		:
//
//	Description	:	Checks if downwash effect is needed and creates one accordingly
//						The external function (draw_downwash_effect) call is made by HC_DRAW.C	
//
///////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DOWNWASH_EFFECT_MAX_ALTITUDE (main_rotor_radius * 3.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int create_downwash_effect_component(downwash_component *this_downwash_component, downwash_types downwash_type, vec3d *position, int *entity_index_list, float main_rotor_radius, float main_rotor_rpm, float min_altitude);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_downwash_effect(downwash_types type, vec3d *position, float main_rotor_radius, float main_rotor_rpm, float min_altitude)
{
	int	
		loop,
		count,
		num_components,
		comp,
		index_counter,
		*entity_index_list;

	downwash_component
		*this_downwash_component;

	ASSERT (type >= 0);

	ASSERT (type < NUM_DOWNWASH_TYPES);

	ASSERT (type != DOWNWASH_TYPE_NONE);

	//
	// create an array of entity index numbers and fill them all with ENTITY_INDEX_DONT_CARE
	//

	count = count_entities_in_downwash (type);

	ASSERT (count);

	entity_index_list = malloc_fast_mem (sizeof (int) * count);

	//Xhit replaced ENTITY_INDEX_DONT_CARE with ENTITY_INDEX_CREATE_LOCAL (030428)
	//This and the changes made to the entity heap and some smoke functions
	//clears the MP-bug caused by that local entities were not allowed to be created on a client
	for ( loop = 0 ; loop < count ; loop ++ )
	{
		entity_index_list [loop] = ENTITY_INDEX_CREATE_LOCAL;
	}

	index_counter = 0;

	num_components = downwash_database[ type ].number_of_components;

	for ( comp = 0 ; comp < num_components ; comp ++ )
	{

		this_downwash_component = &(downwash_database[ type ].component[ comp ]);
		index_counter += create_downwash_effect_component( this_downwash_component, type, position, &entity_index_list[ index_counter ], main_rotor_radius, main_rotor_rpm, min_altitude);	

	}
	
	free_mem (entity_index_list);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
//	Function		: create_downwash_effect_component
//	Authors		: Xhit (Ingemar Persson)
//	Date			: 2003-03-28
//	Update		:
//
//	Description	:	The effects position(x,z), height(y), scale, lifetime and alpha percentage is
//						decided here. The position is randomly set and height is set depending on the 
//						position. Normally there are 4 smoke list effects created for every downwash
//						per frame with one smoke list per quadrant around the helicopter. 
//						If the helicopter got 2 main rotors on different axis then 2 additional 
//						smoke list are created at the side of the helicopter.
//
///////////////////////////////////////////////////////////////////////////////////////////

int create_downwash_effect_component(downwash_component *this_downwash_component, downwash_types downwash_type, vec3d *position, int *entity_index_list, float main_rotor_radius, float main_rotor_rpm, float min_altitude)
{
	int
		loop,
		count,
		terrain_type,
		trail_type;

	short int
		quadrant_x,
		quadrant_z;
	
	unsigned char
		alpha_percentage;

	float
		lifetime,
		lifetime_min,
		lifetime_max,
		scale_min,
		scale_max,
		scale,
		angle,
		radius,
		relative_radius,
		height,
		altitude,
		half_altitude,
		main_rotor_radius_minus_altitude;

	vec3d
		pos,
		offset,
		iv;

	terrain_3d_point_data
		terrain_info;

	entity
		*new_entity;

	memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

	count = this_downwash_component->trail_count;

	if ( count < 1 )
	{
		return 0;
	}

	// Xhit: This is the altitude of the helicopter relative to the ground level. (030328)
	altitude = position->y - min_altitude;
	half_altitude = (altitude / 2.0);

	main_rotor_radius_minus_altitude = main_rotor_radius - altitude;

	scale_min = this_downwash_component->scale_min;
	scale_max = this_downwash_component->scale_max;

	lifetime_min = this_downwash_component->lifetime_min;
	lifetime_max = this_downwash_component->lifetime_max;

	// Xhit: initialising quadrant variables (030328)
	quadrant_x = 1;
	quadrant_z = 1;

	//
	// create smoke trails
	//

	for ( loop = 0 ; loop < count ; loop ++ )
	{
		lifetime = lifetime_min + fabs( ( lifetime_max - lifetime_min ) * sfrand1() );

		angle = frand1() * PI_OVER_TWO;

		relative_radius = main_rotor_radius * frand1();

		scale = relative_radius + scale_min;
		if(scale > scale_max)
				scale = scale_max;

		switch(downwash_type)
		{
			case DOWNWASH_TYPE_LAND:
			case DOWNWASH_TYPE_LAND_DUAL_ROTORS:
			{
				//Xhit: If altitude bigger than main rotor radius then the smoke should be centered beneath the helicopter. (030328)
				if(altitude >= main_rotor_radius)
				{
					radius = relative_radius;
					height = (half_altitude * (radius / main_rotor_radius) + half_altitude) * frand1();
			
				}else
				{
					radius = relative_radius + main_rotor_radius_minus_altitude;
					height = (half_altitude * ((radius - main_rotor_radius_minus_altitude) / main_rotor_radius) + half_altitude + scale ) * frand1();
				}
				break;
			}
			case DOWNWASH_TYPE_WATER:
			case DOWNWASH_TYPE_WATER_DUAL_ROTORS:
			{
				if(altitude >= main_rotor_radius)
				{
					radius = relative_radius;
			
				}else
				{
					radius = relative_radius + main_rotor_radius_minus_altitude;
				}

				height =  main_rotor_radius * frand1();
				break;
			}
			default:
			{
				debug_fatal("DOWNWASH : trying to create an unrecogniseable downwash effect");
				break;
			}
		}


		//Xhit: If main rotor(s) only (not displaced main rotors) then. (030328)
		if((this_downwash_component->create_in_all_quadrants) && (loop < 4))
		{
			//Xhit:	This cryptical thing is to determine in which quadrant this sprite is going to be created. (030328)
			//		 ^z
			//		 |
			//		1|0  x
			//		-+--->
			//		3|2
			//
			//		loop = 0 -> x=	1,	z=	1; loop = 1 -> x=	-1, z=	 1;
			//		loop = 2 -> x=   1,	z= -1; loop = 3 -> x=	-1, z=	-1;
			quadrant_x = 1 | -(loop & 1);
			quadrant_z = 1 | -(loop & 2);
						
			offset.x = quadrant_x * radius * ( cos ( angle ) );
			offset.y = height;
			offset.z = quadrant_z * radius * ( sin ( angle ) );

		}else
		//Xhit:	If scattered downwash effect and if the heli got more than one main rotor (on different axis) then 
		//			add two more trails at the sides of the heli. (030328)
		if((this_downwash_component->create_in_all_quadrants) && (loop >= 4) && (count == 6))
		{
			//Xhit: loop = 4 -> x=	1; loop = 5 -> x=	-1; (030328)
			quadrant_x = 1 | -(loop & 1);

			relative_radius = main_rotor_radius * frand1();

			offset.x = quadrant_x * radius;
			offset.y = height;
			offset.z = frand1() * (main_rotor_radius / 2);
		}else
		{
			debug_fatal("DOWNWASH : trying to create an unrecogniseable downwash effect");
		}

		pos.x = position->x + offset.x ;
		pos.z = position->z + offset.z;

		//Xhit: This is necessary if it's going to work on tilting terrain. (030328)
		get_3d_terrain_point_data (pos.x, pos.z, &terrain_info);
		pos.y = get_3d_terrain_point_data_elevation (&terrain_info);

		pos.y = pos.y + offset.y;

		bound_position_to_map_volume( &pos );

		//Xhit: Decide which trail type is going to be used, this makes mapping to type of downwash effect fast. (030328)
		terrain_type = get_3d_terrain_point_data_type(&terrain_info);
		trail_type = get_terrain_surface_type(terrain_type) + SMOKE_LIST_TYPE_DOWNWASH_START;

		#if DEBUG_MODULE
		
		debug_log("DOWNWASH.C: terrain_type: %d, trail_type: %d", terrain_type, trail_type);

		#endif		

		iv.x = pos.x - position->x;
		iv.y = relative_radius;
		iv.z = pos.z - position->z;

		//Xhit:	If heli on ground then let the dust-smoke fade in according to increasing main_rotor_rpm
		//		otherwise set it according to the altitude of the heli (higher = less dust smoke) (030328)
		if(altitude < 1.0)
		{
			alpha_percentage = (unsigned char)(main_rotor_rpm);
		}else
		{
			//Xhit: "+ 1.0" is to guarantee that alpha_percentage > 0. (030328)
			alpha_percentage = (unsigned char)((1.0 - (altitude / (DOWNWASH_EFFECT_MAX_ALTITUDE + 1.0))) * 100);
		}

		new_entity = create_local_entity
		(
			ENTITY_TYPE_SMOKE_LIST,
			entity_index_list[ loop ],
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_DOWNWASH),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_SMOKE_TYPE, trail_type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR_ALPHA, alpha_percentage),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_GENERATOR_LIFETIME, this_downwash_component->generator_lifetime),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FREQUENCY, this_downwash_component->frequency),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SMOKE_LIFETIME, lifetime),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_SCALE, scale),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_INITIAL_VELOCITY, iv.x, iv.y, iv.z),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos.x, pos.y, pos.z),
			ENTITY_ATTR_END
		);

		entity_index_list[ loop ] = get_local_entity_index( new_entity );
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int count_entities_in_downwash( downwash_types type )
{
	int
		comp,
		index_counter,
		num_components;

	downwash_component
		*downwash_component;
	
	ASSERT (type >= 0);

	ASSERT (type < NUM_DOWNWASH_TYPES);

	ASSERT (type != DOWNWASH_TYPE_NONE);

	index_counter = 0;

	num_components = downwash_database[ type ].number_of_components;

	for ( comp = 0 ; comp < num_components ; comp ++ )
	{

		downwash_component = &(downwash_database[ type ].component[ comp ]);

		index_counter += downwash_component->trail_count;

	}
	
	return index_counter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
//	Function		: draw_downwash_effect
//	Authors		: Xhit (Ingemar Persson)
//	Date			: 2003-03-28
//	Update		:
//
//	Description	:	Checks if downwash effect is going to be drawed (depending on helictoper
//						altitude and helicopter main rotor rpm). If it's going to be drawn the type 
//						of downwash effect is set depending on if it's land or water beneath the helicopter.
//
///////////////////////////////////////////////////////////////////////////////////////////

void draw_downwash_effect(entity *en)
{

	vec3d
		*position,
		pos;

	terrain_3d_point_data
		terrain_info;

	float
		main_rotor_radius,
		main_rotor_rpm,
		min_altitude;

	int
		number_of_main_rotors;

	terrain_types
		type_of_terrain;

	downwash_types
		type_of_downwash;


	ASSERT( en );

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER);

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return;
	}

	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
	{
		return;
	}

	if (get_time_acceleration () == TIME_ACCELERATION_PAUSE)
	{
		return;
	}

	memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

	main_rotor_rpm = get_local_entity_float_value (en, FLOAT_TYPE_MAIN_ROTOR_RPM);

	position = get_local_entity_vec3d_ptr(en, VEC3D_TYPE_POSITION);

	pos.x = position->x;
	pos.y = position->y - aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].centre_of_gravity_to_ground_distance;
	pos.z = position->z;

	get_3d_terrain_point_data (pos.x, pos.z, &terrain_info);
	min_altitude = get_3d_terrain_point_data_elevation (&terrain_info);

	//Xhit: main_rotor_radius is got here because DOWNWASH_EFFECT_MAX_ALTITUDE depends on it. (030328)
	main_rotor_radius = aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].main_rotor_radius;

	if((main_rotor_rpm > 20.0) && ((pos.y - min_altitude) < DOWNWASH_EFFECT_MAX_ALTITUDE))
	{
		
		number_of_main_rotors = (int) aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].number_of_main_rotors;

		type_of_terrain = get_3d_terrain_point_data_type(&terrain_info);

		switch( get_terrain_type_class(type_of_terrain) )
		{
			case TERRAIN_CLASS_LAND: 
			{

				if(number_of_main_rotors > 1)
					type_of_downwash = DOWNWASH_TYPE_LAND_DUAL_ROTORS;
				else
					type_of_downwash = DOWNWASH_TYPE_LAND;
				
				create_downwash_effect(type_of_downwash, &pos, main_rotor_radius, main_rotor_rpm, min_altitude);
				break;
			}
			case TERRAIN_CLASS_WATER:
			{
				
				if(number_of_main_rotors > 1)
					type_of_downwash = DOWNWASH_TYPE_WATER_DUAL_ROTORS;
				else
					type_of_downwash = DOWNWASH_TYPE_WATER;

				create_downwash_effect(type_of_downwash, &pos, main_rotor_radius, main_rotor_rpm, min_altitude);
				break;
			}
			//Xhit: No downwash effect for FORESTS. (030328)
			case TERRAIN_CLASS_FOREST:
			default:
			{
				break;
			}
		}
	}
	
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
