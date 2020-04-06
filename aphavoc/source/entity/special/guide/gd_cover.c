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

#define NUM_COVER_CHECKS_PER_FRAME 3

#define SEEK_COUNT_LIMIT	(1 << NUM_SEEK_COVER_COUNT_BITS)

#define MIN_LOS_ALTITUDE	10.0
#define MAX_LOS_ALTITUDE	50.0
#define INC_LOS_ALTITUDE	10.0

#define GUIDE_COVER_ALTITUDE	5.0

#define MAX_COVER_FOREST_POLY_CHECKS_PER_FRAME 12

#define MAX_COVER_FOREST_POSITION_CHECKS_PER_FRAME 2

#define SEEK_COVER_CURRENT_POSITION_THRESHOLD	100

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum GUIDE_SEEK_COVER_MODES
{
	SEEK_COVER_MODE_CURRENT_POSITION,
	SEEK_COVER_MODE_CHECK_SCORE1,

	SEEK_COVER_MODE_BUILDINGS,
	SEEK_COVER_MODE_BRIDGES,
	SEEK_COVER_MODE_CITY_BUILDINGS,
	SEEK_COVER_MODE_CHECK_SCORE2,
	
	SEEK_COVER_MODE_FOREST,
	SEEK_COVER_MODE_RIVER,
	SEEK_COVER_MODE_CHECK_SCORE3,

	SEEK_COVER_MODE_DEFAULT_TERRAIN,
	SEEK_COVER_MODE_CHECK_SCORE4,

	NUM_GUIDE_SEEK_COVER_MODES
};

typedef enum GUIDE_SEEK_COVER_MODES guide_seek_cover_modes;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_guide_seek_cover_next_search_mode (entity *en);

static int update_guide_seek_cover_fixed_structure_search (entity *en);

static int update_guide_seek_cover_forest_search (entity *en);

static int update_guide_seek_cover_default_terrain_search (entity *en);

static int update_guide_seek_cover_current_position_search (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_guide_seek_cover_results (entity *en)
{
	guide
		*raw = nullptr;

	ASSERT (en);

	raw = (guide *) get_local_entity_data (en);

	memset (&(raw->current_seek_cover_result), 0, sizeof (guide_seek_cover_result_type));

	memset (&(raw->best_seek_cover_result), 0, sizeof (guide_seek_cover_result_type));

	if (raw->terrain_polygon_list)
	{
		free_mem (raw->terrain_polygon_list);

		raw->terrain_polygon_list = NULL;

		raw->terrain_polygon_count = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_guide_seek_cover_results (entity *en)
{
	guide
		*raw = nullptr;

	entity
		*group = nullptr,
		*guide = nullptr,
		*member = nullptr,
		*aggressor = nullptr;

	int
		loop;

	ASSERT (en);

	//
	// wait till other *AI* members have found cover
	//

	aggressor = get_local_entity_first_child (en, LIST_TYPE_FOLLOWER);

	ASSERT (aggressor);

	group = get_local_entity_parent (aggressor, LIST_TYPE_MEMBER);

	ASSERT (group);

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		if (member == aggressor)
		{
			break;
		}

		if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

			if (guide)
			{
				if (get_local_entity_int_value (guide, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_SEEK_COVER)
				{
					return FALSE;
				}
			}
		}

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	//
	// seek cover
	//

	raw = (struct GUIDE *) get_local_entity_data (en);

	for (loop = 0; loop < NUM_COVER_CHECKS_PER_FRAME; loop ++)
	{
		switch (raw->current_seek_cover_result.search_mode)
		{
			case SEEK_COVER_MODE_CURRENT_POSITION:
			{
				update_guide_seek_cover_current_position_search (en);
	
				break;
			}
	
			case SEEK_COVER_MODE_BUILDINGS:
			case SEEK_COVER_MODE_BRIDGES:
			{
				update_guide_seek_cover_fixed_structure_search (en);
	
				break;
			}
	
			case SEEK_COVER_MODE_CITY_BUILDINGS:
			{
				update_guide_seek_cover_fixed_structure_search (en);

				loop += 2;		// less checks per frame for cities (check is slow)
	
				break;
			}
	
			case SEEK_COVER_MODE_FOREST:
			{
				update_guide_seek_cover_forest_search (en);
	
				break;
			}
	
			case SEEK_COVER_MODE_RIVER:
			{
				set_guide_seek_cover_next_search_mode (en);
	
				break;
			}
	
			case SEEK_COVER_MODE_DEFAULT_TERRAIN:
			{
				update_guide_seek_cover_default_terrain_search (en);
	
				break;
			}
	
			case SEEK_COVER_MODE_CHECK_SCORE1:
			case SEEK_COVER_MODE_CHECK_SCORE2:
			case SEEK_COVER_MODE_CHECK_SCORE3:
			case SEEK_COVER_MODE_CHECK_SCORE4:
			{
				//
				// Check current score and early out if good
				//
				
				if (raw->best_seek_cover_result.score > SEEK_COVER_CURRENT_POSITION_THRESHOLD)
				{
					//
					// set cover position to best result
					//
	
					set_attack_guide_fly_to_cover_position (en);
	
					reset_guide_seek_cover_results (en);

					return TRUE;
				}
				else
				{
					set_guide_seek_cover_next_search_mode (en);
				}
	
				break;
			}
	
			case NUM_GUIDE_SEEK_COVER_MODES:
			{
				if (raw->best_seek_cover_result.score > 0)
				{
					//
					// set cover position to best result
					//
	
					set_attack_guide_fly_to_cover_position (en);
				}
				else
				{
					debug_colour_log (DEBUG_COLOUR_DARK_GREEN, "GD_COVER: No Cover found for %s", get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME));
	
					attack_guide_no_cover_found (en);
				}
	
				reset_guide_seek_cover_results (en);
	
				return TRUE;
			}
	
			default:
			{
				debug_fatal ("GD_COVER: Invalid seek mode %d", raw->current_seek_cover_result.search_mode);
			}
		}
	}
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_guide_seek_cover_next_search_mode (entity *en)
{
	guide
		*raw = nullptr;

	ASSERT (en);

	raw = (guide *) get_local_entity_data (en);

	raw->current_seek_cover_result.search_mode ++;

	raw->current_seek_cover_result.sector = 0;
	
	raw->current_seek_cover_result.count = 0;

	if (raw->terrain_polygon_list)
	{
		free_mem (raw->terrain_polygon_list);

		raw->terrain_polygon_list = NULL;

		raw->terrain_polygon_count = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static unsigned char assess_cover_position (entity *en, entity *aggressor, entity *target, vec3d *cover_pos, entity *cover_structure)
{
	guide
		*raw = nullptr;

	vec3d
		*aggressor_pos = nullptr,
		*target_pos = nullptr,
		*structure_pos = nullptr,
		check_pos,
		aggressor_min,
		aggressor_max,
		ta_vec,
		tc_vec,
		ac_vec;

	vec2d
		check_point;

	float
		ta_range,
		tc_range,
		ac_range,
		tc_rating,
		ac_rating,
		heading,
		altitude,
		altitude_rating,
		total,
		wmin,
		wmax,
		aggressor_height,
		aggressor_width,
		object_height,
		weapon_max_range,
		weapon_min_range,
		weapon_effective_range;

	unsigned int
		result;

	object_3d_bounds
		*aggressor_bounding_box = nullptr,
		*object_bounding_box = nullptr;

	object_3d_index_numbers
		aggressor_3d_index,
		object_3d_index;

	entity_sub_types
		selected_weapon;

	raw = (guide *) get_local_entity_data (en);

	result = 0;

	#if DEBUG_MODULE

	if (cover_structure)
	{
		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("*************************************");
			debug_filtered_log ("GD_COVER: Checking %s (%s)", get_local_entity_string (cover_structure, STRING_TYPE_FULL_NAME), object_3d_enumeration_names[get_local_entity_int_value (cover_structure, INT_TYPE_OBJECT_3D_SHAPE)]);
		}
	}

	#endif

	//
	// check position is within map boundaries (TRIVIAL REJECTION)
	//

	if (!point_inside_map_area (cover_pos))
	{
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("	- REJECTED (point outside map area)");
		}

		#endif

		return result;
	}

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	//
	// target to aggressor vector
	//

	ta_vec.x = aggressor_pos->x - target_pos->x;
	ta_vec.y = 0.0;
	ta_vec.z = aggressor_pos->z - target_pos->z;

	ta_range = normalise_any_3d_vector (&ta_vec);

	//
	// target to cover vector
	//

	tc_vec.x = cover_pos->x - target_pos->x;
	tc_vec.y = 0.0;
	tc_vec.z = cover_pos->z - target_pos->z;

	tc_range = normalise_any_3d_vector (&tc_vec);

	//
	// aggressor to cover vector
	//
	
	ac_vec.x = cover_pos->x - aggressor_pos->x;
	ac_vec.y = 0.0;
	ac_vec.z = cover_pos->z - aggressor_pos->z;

	ac_range = normalise_any_3d_vector (&ac_vec);

	//
	// check if aggressor has to fly past target (TRIVIAL REJECTION) 
	//

	if (get_3d_unit_vector_dot_product (&ta_vec, &tc_vec) < 0.0)
	{
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("	- REJECTED (fly past target)");
		}

		#endif

		return result;
	}

	//
	// find aggressors selected weapon
	//

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	if (selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		return result;
	
	weapon_max_range = weapon_database [selected_weapon].max_range * 0.9;

	weapon_min_range = weapon_database [selected_weapon].min_range;

	weapon_effective_range = weapon_database [selected_weapon].effective_range;

	//
	// check cover pos lies within range of weapon (TRIVIAL REJECTION)
	//

	if ((tc_range < weapon_min_range) || (tc_range > weapon_max_range))
	{
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("	- REJECTED (out of weapon range)");
		}

		#endif

		return result;
	}

	//
	// check object is big enough to provide cover
	//

	aggressor_3d_index = get_local_entity_int_value (aggressor, INT_TYPE_OBJECT_3D_SHAPE);

	ASSERT (aggressor_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

	aggressor_bounding_box = get_object_3d_bounding_box_without_lines (aggressor_3d_index);

	ASSERT (aggressor_bounding_box);

	aggressor_min.x = cover_pos->x + aggressor_bounding_box->xmin;
	aggressor_min.y = cover_pos->y + aggressor_bounding_box->ymin;
	aggressor_min.z = cover_pos->z + aggressor_bounding_box->zmin;

	aggressor_max.x = cover_pos->x + aggressor_bounding_box->xmax;
	aggressor_max.y = cover_pos->y + aggressor_bounding_box->ymax;
	aggressor_max.z = cover_pos->z + aggressor_bounding_box->zmax;

	if (cover_structure)
	{
		aggressor_height = aggressor_bounding_box->ymax;

		object_3d_index = get_local_entity_int_value (cover_structure, INT_TYPE_OBJECT_3D_SHAPE);

		ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

		object_bounding_box = get_object_3d_bounding_box_without_lines (object_3d_index);

		object_height = object_bounding_box->ymax;

		//
		// check height
		//

		if (object_height < (GUIDE_COVER_ALTITUDE + (0.666 * aggressor_height)))
		{
			#if DEBUG_MODULE

			if (aggressor == get_external_view_entity ())
			{
				debug_filtered_log ("	- REJECTED (structure too short - %f / %f)", object_height, (GUIDE_COVER_ALTITUDE + (0.666 * aggressor_height)));
			}

			#endif

			return result;
		}

		//
		// check width
		//

		aggressor_width = aggressor_bounding_box->xmax - aggressor_bounding_box->xmin;

		structure_pos = get_local_entity_vec3d_ptr (cover_structure, VEC3D_TYPE_POSITION);

		heading = -atan2 (tc_vec.x, tc_vec.z);

		wmin = 0.0;
		wmax = 0.0;

		// point 1

		check_point.x = object_bounding_box->xmin;
		check_point.y = object_bounding_box->zmin;

		rotate_2d_vector (&check_point, heading);

		wmin = min (wmin, check_point.x);
		wmax = max (wmax, check_point.x);

		// point 2

		check_point.x = object_bounding_box->xmax;
		check_point.y = object_bounding_box->zmin;

		rotate_2d_vector (&check_point, heading);

		wmin = min (wmin, check_point.x);
		wmax = max (wmax, check_point.x);

		// point 3

		check_point.x = object_bounding_box->xmin;
		check_point.y = object_bounding_box->zmax;

		rotate_2d_vector (&check_point, heading);

		wmin = min (wmin, check_point.x);
		wmax = max (wmax, check_point.x);

		// point 4

		check_point.x = object_bounding_box->xmax;
		check_point.y = object_bounding_box->zmax;

		rotate_2d_vector (&check_point, heading);

		wmin = min (wmin, check_point.x);
		wmax = max (wmax, check_point.x);

		aggressor_width *= (0.5 * 0.75);

		if ((wmax < aggressor_width) || ((-wmin) < aggressor_width))
		{
			#if DEBUG_MODULE

			if (aggressor == get_external_view_entity ())
			{
				debug_filtered_log ("	- REJECTED (structure too narrow - %f / %f)", fabs (check_point.x), aggressor_width);
			}

			#endif

			return result;
		}
	}

	//
	// check if other group members are hiding here (TRIVIAL REJECTION) 
	//

	{
		entity
			*group = nullptr,
			*member = nullptr,
			*guide = nullptr;

		entity_sub_types
			guide_type;

		vec3d
			member_pos;

		float
			distance;

		group = get_local_entity_parent (en, LIST_TYPE_GUIDE_STACK);

		ASSERT (group);

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			if (member != aggressor)
			{
				guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

				if (guide)
				{
					guide_type = get_local_entity_int_value (guide, INT_TYPE_ENTITY_SUB_TYPE);

					if (
							(guide_type == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FLY_TO_COVER) ||
							(guide_type == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER) ||
							(guide_type == ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE)
						)
					{
						//
						// find distance between members hiding position, and the test hiding position
						//

						get_local_entity_vec3d (guide, VEC3D_TYPE_GUIDE_POSITION, &member_pos);

						distance = get_2d_range (&member_pos, cover_pos);

						#if DEBUG_MODULE

						if (aggressor == get_external_view_entity ())
						{
							debug_filtered_log ("%s (%d) hiding %f metres from cover pos",
													get_local_entity_string (member, STRING_TYPE_FULL_NAME),
													get_local_entity_index (member),
													distance);
						}

						#endif

						//
						// subtract the aggressors radius
						//

						distance -= get_object_3d_radius (aggressor_3d_index);

						//
						// subtract this members radius
						//

						object_3d_index = get_local_entity_int_value (member, INT_TYPE_OBJECT_3D_SHAPE);

						ASSERT (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX);

						distance -= get_object_3d_radius (object_3d_index);

						//
						// if distance < 0 then the two members would clash
						//
						
						#if DEBUG_MODULE

						if (aggressor == get_external_view_entity ())
						{
							debug_filtered_log ("-  adjusted distance %f", distance);
						}

						#endif

						if (distance < 0.0)
						{
							return result;
						}
					}
				}
			}

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}

	//
	// check LOS at cover position (TRIVIAL REJECTION)
	//

	if (check_position_line_of_sight (aggressor, target, cover_pos, target_pos, MOBILE_LOS_CHECK_ALL))
	{
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("	- REJECTED (no LOS at cover position)");
		}

		#endif

		return result;
	}

	//
	// find target->cover rating
	// 

	if (tc_range < weapon_effective_range)
	{
		tc_rating = (tc_range - weapon_min_range) / (weapon_effective_range - weapon_min_range);
	}
	else
	{
		tc_rating = (weapon_max_range - tc_range) / (weapon_max_range - weapon_effective_range);
	}

	//
	// find aggressor->cover rating
	//
	
//	get_3d_unit_vector_dot_product (&ta_vec, &ac_vec)	// rate differently depending on whether the aggressor must
																		// fly towards, or away from, the target ?

	if (ac_range >= 1000.0)		//temp
	{
		ac_rating = 0.0;
	}
	else
	{
		ac_rating = (1000.0 - ac_range) / 1000.0;
	}

	//
	// find altitude required for LOS rating
	//

	check_pos.x = cover_pos->x;
	check_pos.z = cover_pos->z;
	
	for (altitude = MIN_LOS_ALTITUDE; altitude < MAX_LOS_ALTITUDE; altitude += INC_LOS_ALTITUDE)
	{
		check_pos.y = cover_pos->y + altitude;

		if (check_position_line_of_sight (aggressor, target, &check_pos, target_pos, MOBILE_LOS_CHECK_ALL))
		{
			break;
		}
	}

	if (altitude >= MAX_LOS_ALTITUDE)
	{
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("	- REJECTED (no LOS until max altitude)");
		}

		#endif

		return result;
	}

	altitude_rating = (MAX_LOS_ALTITUDE - altitude) / (MAX_LOS_ALTITUDE - MIN_LOS_ALTITUDE);

	//
	// check for collision with other objects in sector (TRIVIAL REJECTION)
	//
	{
		entity
			*sector = nullptr,
			*object = nullptr;
	
		vec3d
			*object_pos = nullptr,
			object_min,
			object_max;

		sector = get_local_sector_entity (cover_pos);

		ASSERT (sector);

		//
		// check each object in the sector
		//
		
		object = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

		while (object)
		{
			if ((object != aggressor) && (object != target))
			{
				switch (get_local_entity_type (object))
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
					{
						object_3d_index = get_local_entity_int_value (object, INT_TYPE_OBJECT_3D_SHAPE);
				
						if (object_3d_index != OBJECT_3D_INVALID_OBJECT_INDEX)
						{
							object_bounding_box = get_object_3d_bounding_box_without_lines (object_3d_index);
					
							ASSERT (object_bounding_box);
		
							object_pos = get_local_entity_vec3d_ptr (object, VEC3D_TYPE_POSITION);
		
							ASSERT (object_pos);
					
							object_min.x = object_pos->x + object_bounding_box->xmin;
							object_min.y = object_pos->y + object_bounding_box->ymin;
							object_min.z = object_pos->z + object_bounding_box->zmin;
					
							object_max.x = object_pos->x + object_bounding_box->xmax;
							object_max.y = object_pos->y + object_bounding_box->ymax;
							object_max.z = object_pos->z + object_bounding_box->zmax;
					
							if (get_3d_vector_cube_cube_intersect (&aggressor_min, &aggressor_max, &object_min, &object_max))
							{	
								#if DEBUG_MODULE
		
								if (aggressor == get_external_view_entity ())
								{
									debug_filtered_log ("	- REJECTED (object placed at cover position)");
								}
	
								#endif
		
								return result;
							}
						}

						break;
					}
				}
			}

			object = get_local_entity_child_succ (object, LIST_TYPE_SECTOR);
		}
	}

	//
	// overall rating
	//

	total = (tc_rating + ac_rating + altitude_rating) / 3.0;		// temp

	total = bound (total, 0.0, 1.0);

	total *= 255.0 * frand1(); // add random factor to avoid looping

	result = (unsigned char)total; 

	//
	// best so far ?
	//

	if (result > raw->best_seek_cover_result.score)
	{
		raw->best_seek_cover_result = raw->current_seek_cover_result;

		raw->best_seek_cover_result.score = result;

		set_local_entity_vec3d (aggressor, VEC3D_TYPE_COVER_POSITION, cover_pos);
	}

	#if DEBUG_MODULE

	if (aggressor == get_external_view_entity ())
	{
		debug_filtered_log ("	- ACCEPTED");
	}

	#endif

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_fixed_structure_search_object_type (entity *en, entity *structure)
{
	guide
		*raw = nullptr;

	ASSERT (en);

	raw = (guide *) get_local_entity_data (en);

	switch (raw->current_seek_cover_result.search_mode)
	{
		case SEEK_COVER_MODE_BUILDINGS:
		{
			if (
					(get_local_entity_type (structure) == ENTITY_TYPE_SCENIC) ||
					(get_local_entity_type (structure) == ENTITY_TYPE_SITE) ||
					(get_local_entity_type (structure) == ENTITY_TYPE_SITE_UPDATABLE)
				)
			{
				return TRUE;
			}

			break;
		}

		case SEEK_COVER_MODE_BRIDGES:
		{
			if (get_local_entity_type (structure) == ENTITY_TYPE_SEGMENT)
			{
				return TRUE;
			}

			break;
		}	

		case SEEK_COVER_MODE_CITY_BUILDINGS:
		{
			if (get_local_entity_type (structure) == ENTITY_TYPE_CITY_BUILDING)
			{
				return TRUE;
			}

			break;
		}	
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_guide_seek_cover_fixed_structure_search (entity *en)
{
	entity
		*aggressor = nullptr,
		*target = nullptr,
		*task = nullptr,
		*sector = nullptr,
		*structure = nullptr;

	guide
		*raw = nullptr;

	int
		count,
		search_count;

	vec3d
		*target_pos = nullptr,
		*structure_pos = nullptr,
		cover_vec,
		cover_pos;

	float
		distance;

	unsigned char
		score;

	ASSERT(en);
	
	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	raw = (guide *) get_local_entity_data (en);

	//
	// get search sector
	//
	
	if (raw->current_seek_cover_result.sector)
	{
		sector = get_local_entity_parent (target, LIST_TYPE_SECTOR);

		if (sector == get_local_entity_parent (aggressor, LIST_TYPE_SECTOR))
		{
			set_guide_seek_cover_next_search_mode (en);

			return FALSE;
		}
	}
	else
	{
		sector = get_local_entity_parent (aggressor, LIST_TYPE_SECTOR);
	}

	//
	// find next object to check
	//	

	count = 0;

	search_count = raw->current_seek_cover_result.count;

	structure = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);

	while (structure)
	{
		if (structure != target)			// just in case
		{
			if (check_fixed_structure_search_object_type (en, structure))
			{
				if (!get_local_entity_first_child (structure, LIST_TYPE_TARGET))	// don't hide behind something that is going to be blown up !
				{
					ASSERT (count < SEEK_COUNT_LIMIT);

					//
					// is this the next object to check ?
					//
	
					if (count == search_count)
					{
						break;
					}
	
					count ++;
				}
			}
		}

		structure = get_local_entity_child_succ (structure, LIST_TYPE_SECTOR);
	}

	//
	// find cover position for structure
	//

	if (structure)
	{
		//
		// find vector from target to structure
		//
		
		target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	
		structure_pos = get_local_entity_vec3d_ptr (structure, VEC3D_TYPE_POSITION);
	
		cover_vec.x = structure_pos->x - target_pos->x;
		cover_vec.y = 0.0;
		cover_vec.z = structure_pos->z - target_pos->z;
	
		distance = normalise_any_3d_vector (&cover_vec);
	
		//
		// find size of structure, and determine how far behind it the aggressor should be
		//
	
		{
			struct OBJECT_3D_BOUNDS
				*bounding_box = nullptr;
	
			vec3d
				d;
	
			float
				size;
	
			bounding_box = get_object_3d_bounding_box_without_lines (get_local_entity_int_value (structure, INT_TYPE_OBJECT_3D_SHAPE));
	
			ASSERT (bounding_box);
	
			d.x = bounding_box->xmax - bounding_box->xmin;
			d.y = 0.0;
			d.z = bounding_box->zmax - bounding_box->zmin;
	
			size = normalise_any_3d_vector (&d);
	
			distance += (size * 0.5);		// to clear the structure
	
			distance += 20.0;					// to leave plenty of room for the aggressor
		}
	
		//
		// find cover position
		//
	
		cover_pos.x = target_pos->x + (cover_vec.x * distance);
		cover_pos.z = target_pos->z + (cover_vec.z * distance);
	
		bound_position_to_map_area (&cover_pos);

		cover_pos.y = get_3d_terrain_elevation (cover_pos.x, cover_pos.z) + GUIDE_COVER_ALTITUDE;
	
		//
		// assess cover position
		//
	
		score = assess_cover_position (en, aggressor, target, &cover_pos, structure);

		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			vec3d
				*aggressor_pos = nullptr;
	
			debug_filtered_log ("GD_COVER: (%d - %d) Checking %s (%d) SCORE %d",
										 raw->current_seek_cover_result.search_mode,
										 count,
										 get_local_entity_type_name (structure),
										 get_local_entity_index (structure),
										 score);
	
			aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	
			create_debug_3d_line (aggressor_pos, &cover_pos, sys_col_amber, 2.0);

			create_debug_3d_line (aggressor_pos, target_pos, sys_col_red, 0.0);
		}
		#endif
	}

	//
	// if no object found, or limit reached - go to next search
	//

	if ((!structure) || (raw->current_seek_cover_result.count == (SEEK_COUNT_LIMIT - 1)))
	{
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("GD_COVER: (%d) ---------------------------", raw->current_seek_cover_result.search_mode);
		}

		#endif

		if (raw->current_seek_cover_result.sector)
		{
			set_guide_seek_cover_next_search_mode (en);
		}
		else
		{
			raw->current_seek_cover_result.sector = TRUE;

			raw->current_seek_cover_result.count = 0;
		}

		return FALSE;
	}

	//
	// next structure in sector...
	//

	raw->current_seek_cover_result.count ++;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_guide_seek_cover_forest_search (entity *en)
{
	entity
		*aggressor = nullptr,
		*target = nullptr,
		*task = nullptr,
		*sector = nullptr;

	guide
		*raw = nullptr;

	int
		loop,
		count,
		check_count;

	vec3d
		*target_pos = nullptr,
		*aggressor_pos = nullptr,
		*normal = nullptr,
		*point = nullptr,
		average_point,
		cover_vec,
		cover_pos;

	terrain_3d_point_data
		terrain_point_data;

	float
		x, z,
		distance;

	unsigned char
		score;

	ASSERT(en);
	
	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	raw = (guide *) get_local_entity_data (en);

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	
	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	
	//
	// get search sector
	//
	
	if (raw->current_seek_cover_result.sector)
	{
		sector = get_local_entity_parent (target, LIST_TYPE_SECTOR);

		if (sector == get_local_entity_parent (aggressor, LIST_TYPE_SECTOR))
		{
			set_guide_seek_cover_next_search_mode (en);

			return FALSE;
		}

		x = target_pos->x;

		z = target_pos->z;
	}
	else
	{
		sector = get_local_entity_parent (aggressor, LIST_TYPE_SECTOR);

		x = aggressor_pos->x;

		z = aggressor_pos->z;
	}

	//
	// Grab polygons (first time only)
	//
	
	if (!raw->terrain_polygon_list)
	{
		count = get_terrain_3d_number_of_type_triangles_in_sector (x, z, TERRAIN_TYPE_FOREST_SIDE_MID_X);

		raw->terrain_polygon_count = count + get_terrain_3d_number_of_type_triangles_in_sector (x, z, TERRAIN_TYPE_FOREST_SIDE_MID_Z);

		if (raw->terrain_polygon_count == 0)
		{
			//
			// None found - skip search
			//
			
			if (raw->current_seek_cover_result.sector)
			{
				set_guide_seek_cover_next_search_mode (en);
			}
			else
			{
				raw->current_seek_cover_result.sector = TRUE;

				raw->current_seek_cover_result.count = 0;
			}
		
			return FALSE;
		}

		raw->terrain_polygon_list = (terrain_3d_triangle *) malloc_fast_mem (sizeof (terrain_3d_triangle) * raw->terrain_polygon_count);

		get_terrain_3d_type_triangles_in_sector (x, z, TERRAIN_TYPE_FOREST_SIDE_MID_X, raw->terrain_polygon_list);

		get_terrain_3d_type_triangles_in_sector (x, z, TERRAIN_TYPE_FOREST_SIDE_MID_Z, &raw->terrain_polygon_list [count]);

		raw->terrain_polygon_count -= 1;		// use as a countdown to reference into polygon array
	}

	//
	// Test polygons
	//
	// Only do few proper assessments per frame, but check many polygons for trivial rejection (i.e. facing wrong way)
	//

	check_count = 0;

	for (loop = 0; loop < MAX_COVER_FOREST_POLY_CHECKS_PER_FRAME; loop ++)
	{
		ASSERT (raw->terrain_polygon_list);
	
		if (raw->terrain_polygon_count < 0)
		{
			//
			// Finished search
			//
			
			if (raw->current_seek_cover_result.sector)
			{
				set_guide_seek_cover_next_search_mode (en);
			}
			else
			{
				raw->current_seek_cover_result.sector = TRUE;
	
				raw->current_seek_cover_result.count = 0;
			}
			
			return FALSE;
		}
	
		count = raw->terrain_polygon_count;
	
		raw->terrain_polygon_count -= 1;
	
		//
		// Grab poly details
		//
	
		normal = &(raw->terrain_polygon_list [count].normal);
	
		point = &(raw->terrain_polygon_list [count].point1);
	
		average_point = *point;
	
		point = &(raw->terrain_polygon_list [count].point2);
	
		average_point.x += point->x;
		average_point.z += point->z;
	
		point = &(raw->terrain_polygon_list [count].point3);
	
		average_point.x += point->x;
		average_point.z += point->z;
	
		average_point.x *= 0.333333;
		average_point.z *= 0.333333;
		
		//
		// Find cover position
		//
	
		distance = 25.0;					// to leave plenty of room for the aggressor (not forgetting tree objects
		
		cover_pos.x = average_point.x + (normal->x * distance);
		cover_pos.z = average_point.z + (normal->z * distance);

		memset (&terrain_point_data, 0, sizeof (terrain_3d_point_data));
		
		cover_vec.x = cover_pos.x - target_pos->x;
		cover_vec.y = 0.0;
		cover_vec.z = cover_pos.z - target_pos->z;
	
		normalise_any_3d_vector (&cover_vec);
	
		//
		// determine cover Y position (complicated since cover pos could be in a river "gorge")
		//
		{
			vec3d
				test_pos;
	
			// find height of forest tops
			test_pos.x = average_point.x - (normal->x * 10.0);
			test_pos.z = average_point.z - (normal->z * 10.0);
	
			bound_position_to_map_area (&test_pos);

			test_pos.y = get_3d_terrain_point_data (test_pos.x, test_pos.z, &terrain_point_data);
			test_pos.y -= 6.0;	//magic number
	
			// find standard cover position height
			bound_position_to_map_area (&cover_pos);

			cover_pos.y = get_3d_terrain_point_data (cover_pos.x, cover_pos.z, &terrain_point_data);
			cover_pos.y += GUIDE_COVER_ALTITUDE;
	
			// use the larger of the two
			cover_pos.y = max(cover_pos.y, test_pos.y);
		}
	
		//
		// Check forest is facing away from target
		//
		
		if (get_3d_unit_vector_dot_product (normal, &cover_vec) <= 0.0)
		{
			continue;
		}
	
		//
		// Check position is not on top of more forest
		//
	
		if (get_terrain_type_class (get_3d_terrain_point_data_type (&terrain_point_data)) == TERRAIN_CLASS_FOREST)
		{
			continue;
		}
	
		//
		// assess cover position
		//
		
		score = assess_cover_position (en, aggressor, target, &cover_pos, NULL);
	
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("GD_COVER: (%d - %d) SCORE %d",
										 raw->current_seek_cover_result.search_mode,
										 count,
										 score);
		
			create_debug_3d_line (aggressor_pos, &cover_pos, sys_col_ultramarine, 2.0);

			create_debug_3d_line (aggressor_pos, target_pos, sys_col_red, 0.0);
		}
		#endif

		check_count ++;

		if (check_count >= MAX_COVER_FOREST_POSITION_CHECKS_PER_FRAME)
		{
			return check_count;
		}
		else
		{
			continue;
		}
	}

	return check_count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_RADIAL_CHECKS		15

#define MAX_DISTANCE_CHECKS	8

#define MAX_DEFLECTION			rad (45)

int update_guide_seek_cover_default_terrain_search (entity *en)
{
	entity
		*aggressor = nullptr,
		*target = nullptr,
		*task = nullptr;

	guide
		*raw = nullptr;

	int
		a,
		b,
		count,
		selected_weapon;

	vec2d
		ta_vec;

	vec3d
		*target_pos = nullptr,
		*aggressor_pos = nullptr,
		cover_pos;

	float
		theta,
		distance,
		min_range,
		eff_range;

	unsigned char
		score;

	ASSERT(en);
	
	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	raw = (guide *) get_local_entity_data (en);

	//
	// find constants
	//	

	count = raw->current_seek_cover_result.count;

	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	
	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);

	selected_weapon = get_local_entity_int_value (aggressor, INT_TYPE_SELECTED_WEAPON);

	if (selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		return FALSE;
	
	min_range = weapon_database [selected_weapon].min_range;

	eff_range = weapon_database [selected_weapon].effective_range;

	ta_vec.x = aggressor_pos->x - target_pos->x;
	ta_vec.y = aggressor_pos->z - target_pos->z;
	
	normalise_any_2d_vector (&ta_vec);

	a = count;

	theta = (((2.0 * (float)a) / MAX_RADIAL_CHECKS) - 1.0) * MAX_DEFLECTION;

	rotate_2d_vector (&ta_vec, theta);
	
	//
	// find position to check
	//	

	for (b = 0; b < MAX_DISTANCE_CHECKS; b ++)
	{
		distance = eff_range - (((float)b / MAX_DISTANCE_CHECKS) * (eff_range - min_range));
	
		//
		// find cover position
		//
	
		cover_pos.x = target_pos->x + (ta_vec.x * distance);
		cover_pos.z = target_pos->z + (ta_vec.y * distance);
		
		bound_position_to_map_area (&cover_pos);

		cover_pos.y = get_3d_terrain_elevation (cover_pos.x, cover_pos.z) + GUIDE_COVER_ALTITUDE;
		
		//
		// assess cover position
		//
		
		score = assess_cover_position (en, aggressor, target, &cover_pos, NULL);
	
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("GD_COVER: (%d - %d) Checking distance %f angle %f SCORE %d",
										raw->current_seek_cover_result.search_mode,
										count,
										distance,
										deg (theta),
										score);
		
			create_debug_3d_line (target_pos, &cover_pos, sys_col_dark_blue, 10.0);

			create_debug_3d_line (aggressor_pos, target_pos, sys_col_red, 0.0);
		}	
		#endif
	}
	
	count ++;

	if (count >= min (MAX_RADIAL_CHECKS, SEEK_COUNT_LIMIT))
	{
		#if DEBUG_MODULE

		if (aggressor == get_external_view_entity ())
		{
			debug_filtered_log ("GD_COVER: (%d) ---------------------------", raw->current_seek_cover_result.search_mode);
		}

		#endif

		set_guide_seek_cover_next_search_mode (en);

		return FALSE;
	}

	raw->current_seek_cover_result.count = count;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_guide_seek_cover_current_position_search (entity *en)
{
	entity
		*aggressor = nullptr,
		*target = nullptr,
		*task = nullptr;

	vec3d
		*aggressor_pos = nullptr;

	unsigned char
		score;

	ASSERT(en);
	
	aggressor = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);
	ASSERT(aggressor);
	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	ASSERT(task);
	target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	ASSERT(target);

	aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	
	set_guide_seek_cover_next_search_mode (en);

	score = assess_cover_position (en, aggressor, target, aggressor_pos, NULL);

	#if DEBUG_MODULE

	if (aggressor == get_external_view_entity ())
	{
		debug_filtered_log ("GD_COVER: (Current Position) SCORE %d", score);
	}

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

