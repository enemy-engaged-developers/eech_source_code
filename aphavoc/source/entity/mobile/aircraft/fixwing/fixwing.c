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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 									0

#define MAX_META_SMOKE_LIST_ATTACHMENT_POINTS 	2

#define MIN_CRATE_DROPPING_RANGE 					(100 * METRE)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct ATTACHED_META_SMOKE_LIST_TABLE
{

	meta_smoke_list_types							type;
	object_3d_sub_object_index_numbers			attachment_point[MAX_META_SMOKE_LIST_ATTACHMENT_POINTS];

} attached_meta_smoke_list_table[] =
	{
		////////////////////////////////////////////////
		//
		// LIGHT DAMAGE
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE,
			{
				OBJECT_3D_SUB_OBJECT_DAMAGED_SMOKE,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// MEDIUM DAMAGE
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_AIRCRAFT_MEDIUM_DAMAGE,
			{
				OBJECT_3D_SUB_OBJECT_DAMAGED_SMOKE,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// HEAVY DAMAGE
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE,
			{
				OBJECT_3D_SUB_OBJECT_DAMAGED_SMOKE,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// TERMINATOR
		//
		////////////////////////////////////////////////
		{
			-1,
			{
				-1,
				-1
			}
		}
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attach_fixed_wing_meta_smoke_lists (entity *en)
{
	int
		item,
		point;

	object_3d_sub_object_index_numbers
		attachment_point;

	meta_smoke_list_types
		type;

	item = 0;

	while (TRUE)
	{
		type = attached_meta_smoke_list_table [item].type;

		if (type == -1)
		{
			break;
		}
		else
		{
			point = 0;

			while (TRUE)
			{
				attachment_point = attached_meta_smoke_list_table [item].attachment_point [point];

				if (attachment_point == -1)
				{
					break;
				}

				if (point >= MAX_META_SMOKE_LIST_ATTACHMENT_POINTS)
				{
					debug_fatal ("FIXWING: Attach meta smoke lists - too many attachment points");
				}

				attach_local_meta_smoke_lists_to_object (en, type, attachment_point, NULL);

				point ++;
			}
		}

		item ++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_fixed_wing_meta_smoke_lists (entity *en, pack_modes mode)
{
	object_3d_instance
		*inst3d;

	int
		item,
		loop,
		count,
		point,
		packed_indices;

	entity
		*special_effect;

	object_3d_sub_object_index_numbers
		attachment_point;

	meta_smoke_list_types
		type;

	if (mode == PACK_MODE_SERVER_SESSION)
	{
		//
		// no need to pack indices as the server can use "ENTITY_INDEX_DONT_CARE"s when unpacking
		//

		return;
	}

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

		if (inst3d)
		{
			#if DEBUG_MODULE

			debug_log ("FIXWING : Packing smoke for %s ( %d )", aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, en);

			#endif

			item = 0;

			special_effect = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

			while (TRUE)
			{
				type = attached_meta_smoke_list_table [item].type;

				if (type == -1)
				{
					break;
				}
				else
				{
					count = 0;

					point = 0;

					while (TRUE)
					{
						attachment_point = attached_meta_smoke_list_table [item].attachment_point [point];

						if (attachment_point == -1)
						{
							break;
						}
						else
						{
							if (point >= MAX_META_SMOKE_LIST_ATTACHMENT_POINTS)
							{
								debug_fatal ("FIXWING: Pack meta smoke lists - too many attachment points");
							}

							count += count_sub_object_type_depth (inst3d, attachment_point);

							point ++;
						}
					}

					count *= count_entities_in_meta_smoke_list (type);

					if (count > 0)
					{
						packed_indices = 0;

						for (loop = 0 ; loop < count ; loop ++)
						{
							while (TRUE)
							{
								ASSERT (special_effect);
			
								if (special_effect->type == ENTITY_TYPE_SMOKE_LIST)
								{
									if (effect_database [get_local_entity_int_value (special_effect, INT_TYPE_ENTITY_SUB_TYPE)].constructed_locally)
									{
										pack_entity_safe_index (get_local_entity_index (special_effect));
	
										#if DEBUG_MODULE
	
										debug_log ("FIXWING : Index %d = %d", packed_indices, get_local_entity_index (special_effect));
	
										#endif
	
										packed_indices ++;

										special_effect = get_local_entity_child_succ (special_effect, LIST_TYPE_SPECIAL_EFFECT);

										break;
									}
								}
	
								special_effect = get_local_entity_child_succ (special_effect, LIST_TYPE_SPECIAL_EFFECT);
							}
						}

						//
						// check to make sure that only vehicle wake smoke lists are being sent across ( and also the right amount of them )
						//

						ASSERT (packed_indices == count);
					}
				}

				item ++;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_fixed_wing_meta_smoke_lists (entity *en, pack_modes mode)
{
	object_3d_instance
		*inst3d;

	int
		item,
		loop,
		count,
		point,
		*entity_index_list;

	meta_smoke_list_types
		type;

	object_3d_sub_object_index_numbers
		attachment_point;

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

		if (inst3d)
		{
			#if DEBUG_MODULE

			debug_log ("FIXWING : Unpacking smoke for %s ( %d )", aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, en);

			#endif

			item = 0;

			while (TRUE)
			{
				type = attached_meta_smoke_list_table [item].type;

				if (type == -1)
				{
					break;
				}
				else
				{
					point = 0;

					while (TRUE)
					{
						attachment_point = attached_meta_smoke_list_table [item].attachment_point [point];

						if (attachment_point == -1)
						{
							break;
						}
						else
						{
							if (point >= MAX_META_SMOKE_LIST_ATTACHMENT_POINTS)
							{
								debug_fatal ("FIXWING: Unpack meta smoke lists - too many attachment points");
							}

							count = count_sub_object_type_depth (inst3d, attachment_point);

							if (count >0)
							{
								count *= count_entities_in_meta_smoke_list (type);						

								entity_index_list = malloc_fast_mem (sizeof (int) * count);

								for (loop = 0; loop < count; loop ++)
								{
									if (mode == PACK_MODE_SERVER_SESSION)
									{
										entity_index_list [loop] = ENTITY_INDEX_DONT_CARE;
									}
									else
									{
										entity_index_list [loop] = unpack_entity_safe_index ();
									}
	
									#if DEBUG_MODULE

									debug_log ("FIXWING : Index %d = %d", loop, entity_index_list [loop]);

									#endif
								}

								register_attach_meta_smoke_list_to_object (en, type, attachment_point, entity_index_list, count);

								free_mem (entity_index_list);
							}

							point ++;
						}
					}
				}

				item ++;
			}

			//
			// activate smoke lists
			//

			//
			// N.B. CAN'T ACTIVATE SMOKE AS THE SPECIAL EFFECT LIST IS NOT YET LINKED UP TO THE PARENT ENTITY
			//
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LIGHT_DAMAGE_THRESHOLD	50.0
#define MEDIUM_DAMAGE_THRESHOLD	35.0
#define HEAVY_DAMAGE_THRESHOLD	20.0

void assess_fixed_wing_damage_level (entity *en, int old_damage_level, int new_damage_level)
{

	fixed_wing
		*raw;

	float
		initial_damage,
		old_percent_damaged,
		new_percent_damaged;

	if (old_damage_level == new_damage_level)
	{
		return;
	}
	
	if (get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY) <= FIXED_WING_DAMAGE_TRAIL_CUT_OFF_SPEED)
	{
		return;
	}

	raw = get_local_entity_data (en);

	initial_damage = (float)(aircraft_database[raw->ac.mob.sub_type].initial_damage_level);
	
	old_percent_damaged = (100.0 * (float)old_damage_level) / initial_damage;
	new_percent_damaged = (100.0 * (float)new_damage_level) / initial_damage;

	if ((new_percent_damaged <= HEAVY_DAMAGE_THRESHOLD) && (old_percent_damaged > HEAVY_DAMAGE_THRESHOLD))
	{
		// activate heavy damage effect
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE, INFINITE_SMOKE_OFF);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE, INFINITE_SMOKE_OFF);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE, INFINITE_SMOKE_ON);
	}
	if ((new_percent_damaged <= MEDIUM_DAMAGE_THRESHOLD) && (old_percent_damaged > MEDIUM_DAMAGE_THRESHOLD))
	{
		// activate medium damage effect
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE, INFINITE_SMOKE_OFF);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE, INFINITE_SMOKE_ON);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE, INFINITE_SMOKE_OFF);
	}
	if ((new_percent_damaged <= LIGHT_DAMAGE_THRESHOLD) && (old_percent_damaged > LIGHT_DAMAGE_THRESHOLD))
	{
		// activate light damage effect
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE, INFINITE_SMOKE_ON);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE, INFINITE_SMOKE_OFF);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE, INFINITE_SMOKE_OFF);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_fixed_wing_crate_dropping (entity *en)
{

	entity
		*current_waypoint,
		*crate;

	vec3d
		*crate_pos,
		*en_pos;

	float
		range;

	current_waypoint = get_local_entity_current_waypoint (en);

	// only perform code if next waypoint is FINISH_DROP_OFF (ie, drop crates between DROP_OFF and FINISH_DROP_OFF)
	if ((current_waypoint) && (get_local_entity_int_value (current_waypoint, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_FINISH_DROP_OFF))
	{
	
		crate = get_local_entity_first_child (en, LIST_TYPE_LAUNCHED_WEAPON);
	
		if (crate)
		{
		
			crate_pos = get_local_entity_vec3d_ptr (crate, VEC3D_TYPE_POSITION);
			
			en_pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
		
			range = get_sqr_3d_range (crate_pos, en_pos);
		}
		
		if ((!crate) || (range > (MIN_CRATE_DROPPING_RANGE * MIN_CRATE_DROPPING_RANGE)))
		{
		
			if (get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON) == ENTITY_SUB_TYPE_WEAPON_CRATE)
			{
		
				if (aircraft_fire_weapon (en, AIRCRAFT_FIRE_WEAPON_SYSTEM_NOT_READY) == AIRCRAFT_FIRE_WEAPON_SYSTEM_NOT_READY)
				{
		
					//
					// go round again
					//
	
					#if DEBUG_MODULE
	
					debug_log ("FIXWING: SUPPLY_INFO: aircraft not ready to drop crates");
	
					#endif
				}
				else
				{
	
					#if DEBUG_MODULE
	
					debug_log ("FIXWING: SUPPLY_INFO: aircraft dropping crate");
	
					#endif
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
