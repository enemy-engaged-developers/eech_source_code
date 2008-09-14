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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"
#include "ai/ai_misc/ai_route.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char
	valid_warzone_bridges [NUM_ENTITY_SUB_TYPE_BRIDGES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_actual_bridge_length (vec3d *end1, vec3d *end2, entity_sub_types type, vec3d *actual_start, vec3d *actual_end, int *return_num_mid_sections);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_valid_warzone_bridge_database (void)
{

	int
		result;

	char
		temp_filename [128];

	session_list_data_type
		*current_session;

	FILE
		*file_ptr;

	file_tags
		tag;

	memset (valid_warzone_bridges, 0, sizeof (valid_warzone_bridges));

	//
	// read in valid_bridge_warzone file
	//

	ASSERT (get_valid_current_game_session ());

	current_session = get_current_game_session ();

	sprintf (temp_filename, "%s\\%s", current_session->data_path, VALID_BRIDGE_WARZONE_FILE);

	file_ptr = safe_fopen (temp_filename, "r");

	if (file_ptr)
	{
	
		while (TRUE)
		{
	
			tag = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
	
			switch (tag)
			{
	
				case FILE_TAG_START:
				{
	
					break;
				}
	
				case FILE_TAG_BRIDGE:
				{
	
					entity_sub_types
						bridge_type;
	
					while (check_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG) != FILE_TAG_END)
					{
	
						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
	
						ASSERT (result == FILE_TAG_TYPE);
	
						bridge_type = get_next_file_enum (file_ptr, entity_sub_type_bridge_names, NUM_ENTITY_SUB_TYPE_BRIDGES);
	
						valid_warzone_bridges [bridge_type] = TRUE;
					}
	
					break;
				}
	
				case FILE_TAG_END:
				{
	
					fclose (file_ptr);
	
					return;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_bridge( vec3d *end1, vec3d *end2, int start_node, int end_node, entity_sub_types type, float max_leg_height )
{

	const bridge_data
		*bridge_info;

	entity
		*segment_entity,
		*bridge_entity;

	float
		pitch,
		heading,
		start_length,
		actual_length;

	int
		element_loop,
		section_loop,
		num_mid_sections;

	vec3d
		start,
		end,
		pos,
		raw_vector;

	bridge_segment_types
		segment_type;

	ASSERT( ( type >= 0 ) && ( type < NUM_ENTITY_SUB_TYPE_BRIDGES ) );

	bridge_info = &bridge_database[ type ];

	#if DEBUG_MODULE

	debug_log ("BRIDGE : Creating Bridge type %s between nodes %d and %d ( max leg height = %.2f )", entity_sub_type_bridge_names [type], start_node, end_node, max_leg_height);

	#endif

	//
	// get adjusted start and end points
	//

	actual_length = get_actual_bridge_length (end1, end2, type, &start, &end, &num_mid_sections);

	raw_vector.x = end2->x - end1->x;
	raw_vector.y = end2->y - end1->y;
	raw_vector.z = end2->z - end1->z;

	normalise_3d_vector( &raw_vector );

	//
	// calculate heading and pitch for the segments
	//

	get_heading_and_pitch_from_3d_unit_vector( &raw_vector, &heading, &pitch );

	//
	// create bridge entity
	//

	bridge_entity = create_local_entity
	(
		ENTITY_TYPE_BRIDGE,
		ENTITY_INDEX_DONT_CARE,
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, type),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_START_NODE, start_node),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_END_NODE, end_node),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_PITCH, pitch),
		ENTITY_ATTR_END
	);

	//
	// create segments
	//

	//
	// start segment
	//

	if ( bridge_info->start_section_type != BRIDGE_SEGMENT_TYPE_NONE )
	{
		segment_entity = create_local_entity
		(
			ENTITY_TYPE_SEGMENT,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_BRIDGE_SEGMENT_TYPE, bridge_info->start_section_type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, bridge_segment_normal_object( bridge_info->start_section_type )),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_DAMAGE_LEVEL, bridge_segment_initial_damage_level( bridge_info->start_section_type )),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, start.x, start.y, start.z),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, heading),
			ENTITY_ATTR_PARENT (LIST_TYPE_SEGMENT, bridge_entity),
			ENTITY_ATTR_END
		);
	}

	//
	// mid segment(s)
	//

	start_length = bridge_segment_length( bridge_info->start_section_type );

	pos.x = start.x + ( raw_vector.x * start_length * 0.5 );
	pos.y = start.y + ( raw_vector.y * start_length * 0.5 );
	pos.z = start.z + ( raw_vector.z * start_length * 0.5 );

	for ( section_loop = 0 ; section_loop < num_mid_sections ; section_loop ++ )
	{

		for ( element_loop = 0 ; element_loop < bridge_info->num_elements_in_mid_section_pattern ; element_loop ++ )
		{

			segment_type = bridge_info->mid_section_type[ element_loop ];

			pos.x += ( raw_vector.x * bridge_segment_length( segment_type ) * 0.5 );
			pos.y += ( raw_vector.y * bridge_segment_length( segment_type ) * 0.5 );
			pos.z += ( raw_vector.z * bridge_segment_length( segment_type ) * 0.5 );

			segment_entity = create_local_entity
			(
				ENTITY_TYPE_SEGMENT,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, bridge_segment_sub_type( segment_type )),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_BRIDGE_SEGMENT_TYPE, segment_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, bridge_segment_normal_object( segment_type )),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_DAMAGE_LEVEL, bridge_segment_initial_damage_level( segment_type )),
				ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos.x, pos.y, pos.z),
				ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, heading),
				ENTITY_ATTR_PARENT (LIST_TYPE_SEGMENT, bridge_entity),
				ENTITY_ATTR_END
			);

			pos.x += ( raw_vector.x * bridge_segment_length( segment_type ) * 0.5 );
			pos.y += ( raw_vector.y * bridge_segment_length( segment_type ) * 0.5 );
			pos.z += ( raw_vector.z * bridge_segment_length( segment_type ) * 0.5 );
		}
	}

	//
	// end segment
	//

	if ( bridge_info->end_section_type != BRIDGE_SEGMENT_TYPE_NONE )
	{
		segment_entity = create_local_entity
		(
			ENTITY_TYPE_SEGMENT,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_BRIDGE_SEGMENT_TYPE, bridge_info->end_section_type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, bridge_segment_normal_object( bridge_info->end_section_type )),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_DAMAGE_LEVEL, bridge_segment_initial_damage_level( bridge_info->end_section_type )),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, end.x, end.y, end.z),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, heading),
			ENTITY_ATTR_PARENT (LIST_TYPE_SEGMENT, bridge_entity),
			ENTITY_ATTR_END
		);
	}

	//
	// scale the legs
	//

	if ( bridge_info->default_leg_height == 0.0 )
	{
		// bridge doesn't have legs

		set_local_entity_float_value( bridge_entity, FLOAT_TYPE_SCALE, 1.0 );
	}
	else
	{

		set_local_entity_float_value( bridge_entity, FLOAT_TYPE_SCALE, max_leg_height / bridge_info->default_leg_height );
	}

	return bridge_entity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_local_bridge_entities (pack_modes pack_mode)
{
	entity_sub_types
		type;

	char
		filename [512];

	session_list_data_type
		*current_session;

	FILE
		*fp;

	int
		loop,
		number_of_bridges,
		start_node,
		end_node;

	vec3d
		end1,
		end2;

	float
		max_leg_height;

	entity
		*first_bridge_entity;

	if (pack_mode == PACK_MODE_BROWSE_SESSION)
	{

		return;
	}

	first_bridge_entity = NULL;

	if (command_line_run_mode == RUN_MODE_AITOOL)
	{
		//return;
	}

	ASSERT (get_valid_current_game_session ());

	current_session = get_current_game_session ();

	sprintf (filename, "%s\\%s", current_session->data_path, BRIDGE_DATA_FILENAME);

	if (!file_exist (filename))
	{
		return;
	}

	fp = safe_fopen (filename, "rb");

	fread (&number_of_bridges, sizeof (int), 1, fp);

	for (loop = 0; loop < number_of_bridges; loop ++)
	{
		fread (&end1, sizeof (vec3d), 1, fp);

		fread (&end2, sizeof (vec3d), 1, fp);

		fread (&start_node, sizeof (int), 1, fp);

		fread (&end_node, sizeof (int), 1, fp);

		fread (&type, sizeof (int), 1, fp);

		fread (&max_leg_height, sizeof (float), 1, fp);

		type = get_most_suitable_bridge_type (&end1, &end2, max_leg_height);

		if (!first_bridge_entity)
		{

			first_bridge_entity = create_bridge (&end1, &end2, start_node, end_node, type, max_leg_height);
		}
		else
		{

			create_bridge (&end1, &end2, start_node, end_node, type, max_leg_height);
		}
	}

	safe_fclose (fp);

	#if DEBUG_MODULE

	debug_log ("BR_CREAT: creating bridge: Start entity %d", get_local_entity_index (first_bridge_entity));

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_actual_bridge_length (vec3d *end1, vec3d *end2, entity_sub_types type, vec3d *actual_start, vec3d *actual_end, int *return_num_mid_sections)
{
	const bridge_data
		*bridge_info;

	float
		mid_length,
		start_length,
		end_length,
		raw_length,
		actual_length,
		mid_section_pattern_length;

	int
		element_loop,
		num_mid_sections;

	vec3d
		raw_vector,
		mid_point;

	bridge_segment_types
		segment_type;

	ASSERT( ( type >= 0 ) && ( type < NUM_ENTITY_SUB_TYPE_BRIDGES ) );

	bridge_info = &bridge_database[ type ];

	//
	// find the length of the mid section pattern
	//

	mid_section_pattern_length = 0.0;

	for ( element_loop = 0 ; element_loop < bridge_info->num_elements_in_mid_section_pattern ; element_loop ++ )
	{
		segment_type = bridge_info->mid_section_type[ element_loop ];

		mid_section_pattern_length += bridge_segment_length( segment_type );
	}

	ASSERT( mid_section_pattern_length > 0.0 );

	//
	// find the length between the two points
	//

	raw_vector.x = end2->x - end1->x;
	raw_vector.y = end2->y - end1->y;
	raw_vector.z = end2->z - end1->z;

	mid_point.x = end1->x + ( raw_vector.x * 0.5 );
	mid_point.y = end1->y + ( raw_vector.y * 0.5 );
	mid_point.z = end1->z + ( raw_vector.z * 0.5 );

	raw_length = normalise_3d_vector( &raw_vector );

	//
	// find the length left after the start and end sections are considered
	//

	start_length = bridge_segment_length( bridge_info->start_section_type );

	end_length = bridge_segment_length( bridge_info->end_section_type );

	mid_length = raw_length - ( start_length * 0.5 );

	mid_length -= ( end_length * 0.5 );

	if ( mid_length <= 0.0 )
	{
		num_mid_sections = 0;
	}
	else
	{
		num_mid_sections = (int)( mid_length / mid_section_pattern_length ) + 1;
	}

	actual_length = ( start_length * 0.5 ) + ( end_length * 0.5 ) + ( mid_section_pattern_length * num_mid_sections );

	//
	// find actual start and end points
	//

	if (actual_start)
	{
		actual_start->x = mid_point.x - ( raw_vector.x * ( actual_length * 0.5 ) );
		actual_start->y = mid_point.y - ( raw_vector.y * ( actual_length * 0.5 ) );
		actual_start->z = mid_point.z - ( raw_vector.z * ( actual_length * 0.5 ) );
	}

	if (actual_end)
	{
		actual_end->x = mid_point.x + ( raw_vector.x * ( actual_length * 0.5 ) );
		actual_end->y = mid_point.y + ( raw_vector.y * ( actual_length * 0.5 ) );
		actual_end->z = mid_point.z + ( raw_vector.z * ( actual_length * 0.5 ) );
	}

	if (return_num_mid_sections)
	{
		(*return_num_mid_sections) = num_mid_sections;
	}

	return actual_length;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_sub_types get_most_suitable_bridge_type (vec3d *end1, vec3d *end2, float largest_depth)
{
	entity_sub_types
		type;

	float
		d,
		span,
		min_span,
		max_span,
		min_depth,
		max_depth,
		slope;

	float
		actual_span [NUM_ENTITY_SUB_TYPE_BRIDGES];

	int
		suitability [NUM_ENTITY_SUB_TYPE_BRIDGES];

	int
		num_suitable_types;

	vec3d
		v;

	ASSERT (end1 && end2);

	d = get_3d_range (end1, end2);

	memset (suitability, 0, sizeof (int) * NUM_ENTITY_SUB_TYPE_BRIDGES);

	num_suitable_types = 0;

	//
	// assess span length and warzone validity
	//

	for (type = 0; type < NUM_ENTITY_SUB_TYPE_BRIDGES; type ++)
	{
		if ((bridge_database [type].valid_bridge_type) && (valid_warzone_bridges [type]))
		{
			span = get_actual_bridge_length (end1, end2, type, NULL, NULL, NULL);

			min_span = bridge_database [type].min_suitable_span;
			max_span = bridge_database [type].max_suitable_span;

			if ((span >= min_span) && (span <= max_span))
			{
				suitability [type] = TRUE;

				num_suitable_types ++;
			}

			actual_span [type] = span;
		}
	}

	if (num_suitable_types == 0)
	{
		#if DEBUG_MODULE

		debug_log ("BRIDGE : NO SUITABLE TYPE FOUND ( span = %f )", d);

		#endif

		return ENTITY_SUB_TYPE_BRIDGE_GIRDER;
	}

	//
	// assess max distance down to water
	//

	for (type = 0; type < NUM_ENTITY_SUB_TYPE_BRIDGES; type ++)
	{
		if (!suitability [type])
		{
			continue;
		}

		min_depth = bridge_database [type].min_suitable_depth;
		max_depth = bridge_database [type].max_suitable_depth;

		if ((largest_depth < min_depth) || (largest_depth > max_depth))
		{
			suitability [type] = FALSE;

			num_suitable_types --;
		}
	}

	if (num_suitable_types == 0)
	{
		#if DEBUG_MODULE

		debug_log ("BRIDGE : NO SUITABLE TYPE FOUND ( span = %f, depth = %f )", d, largest_depth);

		#endif

		return ENTITY_SUB_TYPE_BRIDGE_GIRDER;
	}

	//
	// assess bridge slope
	//

	v.x = end2->x - end1->x;
	v.y = end2->y - end1->y;
	v.z = end2->z - end1->z;

	normalise_3d_vector (&v);

	slope = fabs (asin (v.y));

	for (type = 0; type < NUM_ENTITY_SUB_TYPE_BRIDGES; type ++)
	{
		if (!suitability [type])
		{
			continue;
		}

//		debug_log ("BRIDGE : %s max suitable slope = %f, actual slope = %f", entity_sub_type_bridge_names [type], deg (bridge_database [type].max_suitable_slope), deg (slope));

		if (slope > bridge_database [type].max_suitable_slope)
		{
//			debug_log ("          Failed");

			suitability [type] = FALSE;

			num_suitable_types --;
		}
	}

	if (num_suitable_types == 0)
	{
		#if DEBUG_MODULE

		debug_log ("BRIDGE : NO SUITABLE TYPE FOUND ( span = %f, depth = %f, slope = %f )", d, largest_depth, deg (slope));

		#endif

		return ENTITY_SUB_TYPE_BRIDGE_GIRDER;
	}

	//
	// end of criteria checks
	//

	if (num_suitable_types == 1)
	{
		//
		// trivial case
		//

		for (type = 0; type < NUM_ENTITY_SUB_TYPE_BRIDGES; type ++)
		{
			if (suitability [type])
			{
				#if DEBUG_MODULE

				debug_log ("BRIDGE : Single suitable type ( %s )", entity_sub_type_bridge_names [type]);

				#endif

				return type;
			}
		}

		debug_fatal ("BRIDGE: suitable type counter = %d, but no suitable types found", num_suitable_types);
	}
	else
	{
		//
		// find best fit
		//

		float
			span_difference,
			best_span_difference;

		int
			best_type;

		best_type = -1;

		best_span_difference = FLT_MAX;

		for (type = 0; type < NUM_ENTITY_SUB_TYPE_BRIDGES; type ++)
		{
			if (suitability [type])
			{
				span_difference = fabs (actual_span [type] - d);

				if (span_difference < best_span_difference)
				{
					best_type = type;

					best_span_difference = span_difference;
				}

				#if DEBUG_MODULE

				debug_log ("BRIDGE : Multiple suitable types ( %s ) - sd = %f", entity_sub_type_bridge_names [type], span_difference);

				#endif
			}
		}

		ASSERT (best_type != -1);

		#if DEBUG_MODULE

		debug_log ("BRIDGE : Best type ( %s ) - sd = %f", entity_sub_type_bridge_names [best_type], best_span_difference);

		#endif

		return best_type;
	}

	debug_fatal ("BRIDGE : No Valid Types Found");

	return ENTITY_SUB_TYPE_BRIDGE_GIRDER;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_bridge_max_leg_height (vec3d *end1, vec3d *end2, entity_sub_types type)
{

	const bridge_data
		*bridge_info;

	float
		start_length,
		actual_length,
		max_leg_height;

	int
		element_loop,
		section_loop,
		num_mid_sections;

	vec3d
		start,
		end,
		pos,
		raw_vector;

	bridge_segment_types
		segment_type;

	ASSERT( ( type >= 0 ) && ( type < NUM_ENTITY_SUB_TYPE_BRIDGES ) );

	bridge_info = &bridge_database[ type ];

	max_leg_height = 0.0;

	//
	// get adjusted start and end points
	//

	actual_length = get_actual_bridge_length (end1, end2, type, &start, &end, &num_mid_sections);

	raw_vector.x = end2->x - end1->x;
	raw_vector.y = end2->y - end1->y;
	raw_vector.z = end2->z - end1->z;

	normalise_3d_vector( &raw_vector );

	start_length = bridge_segment_length( bridge_info->start_section_type );

	pos.x = start.x + ( raw_vector.x * start_length * 0.5 );
	pos.y = start.y + ( raw_vector.y * start_length * 0.5 );
	pos.z = start.z + ( raw_vector.z * start_length * 0.5 );

	for ( section_loop = 0 ; section_loop < num_mid_sections ; section_loop ++ )
	{

		for ( element_loop = 0 ; element_loop < bridge_info->num_elements_in_mid_section_pattern ; element_loop ++ )
		{

			segment_type = bridge_info->mid_section_type[ element_loop ];

			pos.x += ( raw_vector.x * bridge_segment_length( segment_type ) * 0.5 );
			pos.y += ( raw_vector.y * bridge_segment_length( segment_type ) * 0.5 );
			pos.z += ( raw_vector.z * bridge_segment_length( segment_type ) * 0.5 );

			max_leg_height = max( max_leg_height, ( pos.y - get_3d_terrain_elevation( pos.x, pos.z ) ) );

			pos.x += ( raw_vector.x * bridge_segment_length( segment_type ) * 0.5 );
			pos.y += ( raw_vector.y * bridge_segment_length( segment_type ) * 0.5 );
			pos.z += ( raw_vector.z * bridge_segment_length( segment_type ) * 0.5 );
		}
	}

	return max_leg_height;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_client_server_bridge_entity (entity *en)
{
	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	repair_local_bridge_entity (en);

	transmit_entity_comms_message (ENTITY_COMMS_REPAIR_BRIDGE_ENTITY, en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_local_bridge_entity (entity *en)
{

	int
		start_node,
		end_node,
		count;

	entity
		*segment;

	ASSERT (en);

	//
	// repair segments
	//

	segment = get_local_entity_first_child (en, LIST_TYPE_SEGMENT);

	while (segment)
	{
		repair_local_segment_entity (segment);

		segment = get_local_entity_child_succ (segment, LIST_TYPE_SEGMENT);
	}

	//
	// set bridge alive flag
	//

	set_local_entity_int_value (en, INT_TYPE_ALIVE, TRUE);

	//
	// repair the link between nodes
	//

	start_node = get_local_entity_int_value (en, INT_TYPE_START_NODE);

	end_node = get_local_entity_int_value (en, INT_TYPE_END_NODE);

	count = get_road_link_breaks (start_node, end_node);

	count --;

	set_road_link_breaks (start_node, end_node, count);

	debug_log ("BRIDGE: Repairin bridge and route between %d and %d... broken bridge count = %d", count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




