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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "faction.h"
#include "parser.h"

#include "../ai_misc/ai_route.h"
#include "../highlevl/imaps.h"
#include "../parser/parsgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

frontline_forces_placement_data
	*frontline_forces_data = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *load_keysite_data (entity_sub_types keysite_type, entity_sides keysite_side);

static entity *create_mobile_member (
									entity_types type,
									int index,
									int client_server_create,
									entity *group,
									vec3d *position,
									entity_sub_types member_type,
									int formation_position,
									int operational_state,
									entity_sides side,
									float uc_state);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_campaign (session_list_data_type *session)
{

	char
		filename [256];

	int
		offset;

   disable_entity_comms_messages ();

   ASSERT (!get_session_entity ());

   ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

   #if DEBUG_MODULE

   debug_log ("FACTION: initialise faction");

   #endif

	initialise_division_database ();

	initialise_parser ();

   //
   // load campaign description
   //

	offset = 0;

   //load_campaign_file (session);

	sprintf (filename, "%s\\%s\\%s", session->data_path, session->campaign_directory, session->campaign_filename);

	parser_campaign_file (filename, &offset);

	ASSERT (get_session_entity ());

	attach_session_sound_effects (get_session_entity ());

   enable_entity_comms_messages ();
   
//VJ 060217 initialize map info after parsing the campaign file
//VJ 060319 further bug fixes
  	read_map_info_data();      
	debug_log("###CUSTOM TEXTURE STARTUP: faction.c: create_campaign: read_map_info_data");
	  	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_campaign (void)
{

   #if DEBUG_MODULE

   debug_log ("FACTION: deinitialise faction");

   #endif
	
	if (campaign_population_filename)
	{

		free_mem (campaign_population_filename);
	}

	campaign_population_filename = NULL;
	
	if (population_placement_filename)
	{

		free_mem (population_placement_filename);
	}

	population_placement_filename = NULL;
	
	if (side_data_filename)
	{

		free_mem (side_data_filename);
	}

	side_data_filename = NULL;

	initialise_route_data ();

	deinitialise_division_database ();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_factions (void)
{

   entity
      *this_force;

   if (get_session_entity ())
   {

      this_force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

      while (this_force)
      {

         unlink_local_entity_children (this_force, LIST_TYPE_KEYSITE_FORCE);

         this_force = get_local_entity_child_succ (this_force, LIST_TYPE_FORCE);
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_faction (entity_sides side, int colour)
{

   static entity
      *this_force;

   #if DEBUG_MODULE

   debug_log ("FACTION: create faction for side %d", side);

   #endif

   debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

   //
   // this_force
   //

   this_force = create_local_entity
   (
      ENTITY_TYPE_FORCE,
      ENTITY_INDEX_DONT_CARE,
      ENTITY_ATTR_PARENT (LIST_TYPE_FORCE, get_session_entity ()),
      ENTITY_ATTR_INT_VALUE (INT_TYPE_COLOUR, colour),
      ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
      ENTITY_ATTR_END
   );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_landed_faction_members (entity *keysite, entity_sub_types member_type, entity_sub_types group_type, int number)
{
   float
      fuselage_angle = 0,
      heading,
      pitch,
      roll;

   matrix3x3
      attitude;

   vec3d
      pos,
      face_normal;

	list_types
		list_type;

   int
		index,
      formation_position,
      loop;

   entity
      *wp,
      *group,
      *member,
		*parent,
      *landing_en,
		*movement_parent;

	entity_sides
		side;

   #if DEBUG_MODULE

   debug_log ("FACTION: create landed members type %d, sub type %d, number %d", member_type, group_type, number);

   #endif

	ASSERT (keysite);
	
	ASSERT (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE);

	side = (entity_sides) get_local_entity_int_value (keysite, INT_TYPE_SIDE);

	list_type = group_database [group_type].group_list_type;

	if (list_type == LIST_TYPE_INDEPENDENT_GROUP)
	{
		parent = get_local_force_entity (side);
	}
	else
	{
		parent = keysite;
	}

	ASSERT (parent);

	landing_en = NULL;

   debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_game_status () == GAME_STATUS_INITIALISING);

   landing_en = get_local_entity_landing_entity (keysite, group_database [group_type].default_landing_type);

   if (landing_en)
   {

      //
      // skip through route to last waypoint, i.e. landed waypoint.
      //

      wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_LANDING);

      while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
      {

         wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
      }

      ASSERT (wp);

		if (number > 0)
		{

			//
			// create group
			//

			get_local_entity_vec3d (keysite, VEC3D_TYPE_POSITION, &pos);

			group = create_local_entity
			(
				ENTITY_TYPE_GROUP,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_PARENT (list_type, parent),
				ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos.x, pos.y, pos.z),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, group_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_VERBOSE_OPERATIONAL_STATE, VERBOSE_OPERATIONAL_STATE_WAITING),
				ENTITY_ATTR_END
			);

			//
			// create members
			//

			for (loop = 0; loop < number; loop++)
			{

				//
				// mark Keysite as used (after it has actually been used!)
				//

				if (!get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
				{
	
					set_local_entity_int_value (keysite, INT_TYPE_IN_USE, TRUE);

					update_imap_sector_side (keysite, TRUE);

					update_imap_importance_level (keysite, TRUE);

					update_keysite_distance_to_friendly_base (keysite, side);
				}

				//
				// calculate formation position to suite landing entity
				//

				formation_position = 0;

				while ((formation_position < get_local_entity_int_value (landing_en, INT_TYPE_TOTAL_LANDING_SITES)) && ((1 << formation_position) & (get_local_entity_int_value (landing_en, INT_TYPE_LANDED_LOCK))))
				{

					formation_position ++;
				}

				member = create_mobile_member
				(
					group_database [group_type].default_entity_type,
					ENTITY_INDEX_DONT_CARE,
					TRUE,
					group,
					&pos,
					member_type,
					formation_position,
					OPERATIONAL_STATE_LANDED,
					side,
					AIRCRAFT_UNDERCARRIAGE_DOWN_FLOAT_VALUE
				);

				movement_parent = get_local_entity_parent (get_parser_keysite (), LIST_TYPE_MOVEMENT_DEPENDENT);

				if ((group_database [group_type].default_entity_type != ENTITY_TYPE_SHIP_VEHICLE) && (movement_parent))
				{

					insert_local_entity_into_parents_child_list (member, LIST_TYPE_MOVEMENT_DEPENDENT, movement_parent, NULL);
				}

				index = get_local_entity_int_value (member, INT_TYPE_FORMATION_POSITION);

				get_local_waypoint_formation_position (index, wp, &pos);

				if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE)
				{

					pos.y = get_3d_terrain_elevation (pos.x, pos.z);
				}

				fuselage_angle = get_local_entity_float_value (member, FLOAT_TYPE_FUSELAGE_ANGLE);

				pos.y += get_local_entity_float_value (member, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

				////////////////////////////////////////
				//
				// attitude
				//
				////////////////////////////////////////

				heading = get_local_entity_float_value (keysite, FLOAT_TYPE_HEADING);

				get_3d_terrain_face_normal (&face_normal, pos.x, pos.z);

				get_3d_transformation_matrix_from_face_normal_and_heading (attitude, &face_normal, heading);

				pitch = get_pitch_from_attitude_matrix (attitude);

				pitch += fuselage_angle;

				roll = get_roll_from_attitude_matrix (attitude);

				set_local_entity_attitude_angles (member, heading, pitch, roll);

				set_local_entity_vec3d (member, VEC3D_TYPE_POSITION, &pos);

				#if DEBUG_MODULE

				debug_log ("FACTION: placing member %d (%s) at %f, %f, %f, formation_pos %d at keysite %s", member, get_local_entity_type_name (member), pos.x, pos.y, pos.z, formation_position, get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

				#endif

				//
				// Lock landing site for member and add to dependent list
				//

				notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_SITE, landing_en, member);
			}

			//
			// Assign each member a unique ID number
			//

			set_group_member_numbers (group);

			return group;
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_landed_faction_group (entity *keysite, entity_sub_types group_type, formation_component_types formation_component)
{

	formation_vehicle_components
		*formation_components;

   float
      fuselage_angle = 0,
      heading,
      pitch,
      roll;

   matrix3x3
      attitude;

   vec3d
      pos,
      face_normal;

   int
		number,
		index,
      formation_position,
      loop;

	list_types
		list_type;

   entity
      *wp,
      *group,
      *member,
		*parent,
      *landing_en,
		*movement_parent;

	entity_sides
		side;

	entity_sub_types
		member_type;

	ASSERT (keysite);

   debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	side = (entity_sides) get_local_entity_int_value (keysite, INT_TYPE_SIDE);

	list_type = group_database [group_type].group_list_type;

	if (list_type == LIST_TYPE_INDEPENDENT_GROUP)
	{
		parent = get_local_force_entity (side);
	}
	else
	{
		parent = keysite;
	}

	ASSERT (parent);

	ASSERT (get_game_status () == GAME_STATUS_INITIALISING);

	formation_components = get_formation_components (formation_component);

	landing_en = NULL;

   landing_en = get_local_entity_landing_entity (keysite, group_database [group_type].default_landing_type);

   if (landing_en)
   {

      //
      // skip through route to last waypoint, i.e. landed waypoint.
      //

      wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_LANDING);

      while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
      {

         wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
      }

      ASSERT (wp);

		//
		// create group
		//

		get_local_entity_vec3d (keysite, VEC3D_TYPE_POSITION, &pos);

		group = create_local_entity
		(
			ENTITY_TYPE_GROUP,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT (list_type, parent),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos.x, pos.y, pos.z),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, group_type),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
			ENTITY_ATTR_END
		);

		//
		// create members
		//

		ASSERT (formation_components);

		number = formation_components->count;

		for (loop = 0; loop < number; loop++)
		{

			//
			// mark Keysite as used (after it has actually been used!)
			//

			if (!get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
			{

				set_local_entity_int_value (keysite, INT_TYPE_IN_USE, TRUE);

				update_imap_sector_side (keysite, TRUE);

				update_imap_importance_level (keysite, TRUE);

				update_keysite_distance_to_friendly_base (keysite, side);
			}

			//
			// calculate formation position to suite landing entity
			//

			formation_position = 0;

			while ((formation_position < get_local_entity_int_value (landing_en, INT_TYPE_TOTAL_LANDING_SITES)) &&
					((1 << formation_position) & (get_local_entity_int_value (landing_en, INT_TYPE_LANDED_LOCK))))
			{

				formation_position ++;
			}

			if (formation_position >= get_local_entity_int_value (landing_en, INT_TYPE_TOTAL_LANDING_SITES))
			{

				debug_fatal ("FACTION: Placing too many aircraft (group %s, (%d)) at %s (%d) - posn %d",
								get_local_entity_string (group, STRING_TYPE_FULL_NAME),
								get_local_entity_index (group),
								get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
								get_local_entity_index (keysite),
								formation_position,
								get_local_entity_int_value (landing_en, INT_TYPE_TOTAL_LANDING_SITES));

				continue;
			}

			//
			// calculate formation position to suite landing entity
			//

			if (side == ENTITY_SIDE_BLUE_FORCE)
			{

				member_type = formation_components->components [loop * 2];
			}
			else
			{
				
				member_type = formation_components->components [(loop * 2) + 1];
			}

			member = create_mobile_member
			(
				group_database [group_type].default_entity_type,
				ENTITY_INDEX_DONT_CARE,
				TRUE,
				group,
				&pos,
				member_type,
				formation_position,
				OPERATIONAL_STATE_LANDED,
				side,
				AIRCRAFT_UNDERCARRIAGE_DOWN_FLOAT_VALUE
			);

			movement_parent = get_local_entity_parent (get_parser_keysite (), LIST_TYPE_MOVEMENT_DEPENDENT);

			if ((group_database [group_type].default_entity_type != ENTITY_TYPE_SHIP_VEHICLE) && (movement_parent))
			{

				insert_local_entity_into_parents_child_list (member, LIST_TYPE_MOVEMENT_DEPENDENT, movement_parent, NULL);
			}

			index = get_local_entity_int_value (member, INT_TYPE_FORMATION_POSITION);

			get_local_waypoint_formation_position (index, wp, &pos);

			if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE)
			{

				pos.y = get_3d_terrain_elevation (pos.x, pos.z);
			}

			fuselage_angle = get_local_entity_float_value (member, FLOAT_TYPE_FUSELAGE_ANGLE);

			pos.y += get_local_entity_float_value (member, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

			////////////////////////////////////////
			//
			// attitude
			//
			////////////////////////////////////////

			heading = get_local_entity_float_value (keysite, FLOAT_TYPE_HEADING);

			get_3d_terrain_face_normal (&face_normal, pos.x, pos.z);

			get_3d_transformation_matrix_from_face_normal_and_heading (attitude, &face_normal, heading);

			pitch = get_pitch_from_attitude_matrix (attitude);

			pitch += fuselage_angle;

			roll = get_roll_from_attitude_matrix (attitude);

			set_local_entity_attitude_angles (member, heading, pitch, roll);

			set_local_entity_vec3d (member, VEC3D_TYPE_POSITION, &pos);

			#if DEBUG_MODULE

			debug_log ("FACTION: placing member %d (%s) at %f, %f, %f, formation_pos %d at keysite %s", get_local_entity_index (member), get_local_entity_type_name (member), pos.x, pos.y, pos.z, formation_position, get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

			#endif

			//
			// Lock landing site for member and add to dependent list
			//

			notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_SITE, landing_en, member);
		}

		//
		// Assign each member a unique ID number
		//

		set_group_member_numbers (group);

		return group;
	}
	else
	{
		#ifdef DEBUG
		
		debug_fatal ("FACTION: No landing entity for group type %s at %s (%d)",
								group_database [group_type].full_name,
								get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME),
								get_local_entity_index (keysite));

		#endif
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_landing_faction_members (entity *keysite, entity_sub_types member_type, entity_sub_types group_type, int number, entity *cwp, vec3d *start_position)
{

   float
      fuselage_angle = 0,
      heading,
      pitch,
      roll;

   matrix3x3
      attitude;

   vec3d
		pos,
		*wp_pos,
		*normal,
		start_wp_pos,
		member_pos,
      direction;

   int
		free_sites,
		landing_formation,
		formation_test,
      formation_position,
      loop;

	terrain_3d_point_data
		terrain_info;

   entity
      *wp,
		*force,
      *group,
      *member,
      *landing_en;

	ASSERT (keysite);

	ASSERT (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (get_game_status () == GAME_STATUS_INITIALISED);

   #if DEBUG_MODULE

   debug_log ("FACTION: create landing members type %d, sub type %d, number %d, at %s", member_type, group_type, number, get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

   #endif

	force = get_local_entity_parent (keysite, LIST_TYPE_KEYSITE_FORCE);

	ASSERT (force);

	wp_pos = get_local_entity_vec3d_ptr (cwp, VEC3D_TYPE_POSITION);

	landing_en = NULL;

   debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

   landing_en = get_local_entity_landing_entity (keysite, group_database [group_type].default_landing_type);

   if (landing_en)
   {

      //
      // skip through route to last waypoint, i.e. landed waypoint.
      //

      wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_LANDING);

		landing_formation = get_number_in_formation ((formation_types)get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

      while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
      {

         wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
      }

      ASSERT (wp);

		free_sites = get_local_entity_int_value (landing_en, INT_TYPE_TOTAL_LANDING_SITES) - int_bit_count (get_local_entity_int_value (landing_en, INT_TYPE_LANDED_LOCK));

		ASSERT (free_sites >= 0);

		if ((number > 0) && ((free_sites - get_local_entity_int_value (landing_en, INT_TYPE_RESERVED_LANDING_SITES)) > 0))
		 //&& (get_local_entity_int_value (landing_en, INT_TYPE_FREE_LANDING_SITES) > get_local_entity_int_value (landing_en, INT_TYPE_RESERVED_LANDING_SITES)))
		{

			//
			// quick check to see if any members will fit (landing / reserved / landed)
			//

			formation_position = 0;

			formation_test = (1 << formation_position);

			while ((formation_test & (get_local_entity_int_value (landing_en, INT_TYPE_LANDED_LOCK))) ||
					((1 << (formation_position % landing_formation)) & (get_local_entity_int_value (landing_en, INT_TYPE_LANDING_LOCK))))
			{

				formation_position ++;

				formation_test = (1 << formation_position);

				if (formation_position >= get_local_entity_int_value (landing_en, INT_TYPE_TOTAL_LANDING_SITES))
				{

					#if DEBUG_MODULE

					debug_log ("FACTION: creation failed... can't lock landing/landed site");
	
					#endif
  			
					return NULL;
				}
			}

			//
			// create group
			//

			group = create_client_server_entity
			(
				ENTITY_TYPE_GROUP,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_PARENT (LIST_TYPE_KEYSITE_GROUP, keysite),
				ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, start_position->x, start_position->y, start_position->z),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, group_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, get_local_entity_int_value (keysite, INT_TYPE_SIDE)),
				ENTITY_ATTR_END
			);

			//
			// create members
			//

			for (loop = 0; loop < number; loop++)
			{

				//
				// calculate formation position to suite landing entity
				//

				formation_position = 0;

				formation_test = (1 << formation_position);

				while ((formation_test & (get_local_entity_int_value (landing_en, INT_TYPE_LANDED_LOCK))) ||
						((1 << (formation_position % landing_formation)) & (get_local_entity_int_value (landing_en, INT_TYPE_LANDING_LOCK))))
				{

					formation_position ++;
	
					formation_test = (1 << formation_position);
	
					if (formation_position >= get_local_entity_int_value (landing_en, INT_TYPE_TOTAL_LANDING_SITES))
					{
		
						return NULL;
					}
				}

				#if DEBUG_MODULE

				debug_log ("FACTION: placing member type %d side %s formation pos %d at %f, %f, %f", member_type, entity_side_names [get_local_entity_int_value (keysite, INT_TYPE_SIDE)], formation_position, start_position->x, start_position->y, start_position->z);

				#endif

				member = create_mobile_member
				(
					group_database [group_type].default_entity_type,
					ENTITY_INDEX_DONT_CARE,
					TRUE,
					group,
					start_position,
					member_type,
					formation_position,
					OPERATIONAL_STATE_TAXIING,
					(entity_sides)get_local_entity_int_value (keysite, INT_TYPE_SIDE),
					AIRCRAFT_UNDERCARRIAGE_DOWN_FLOAT_VALUE
				);

				get_local_waypoint_formation_position (formation_position, cwp, &start_wp_pos);

				direction.x = start_wp_pos.x - start_position->x;
				direction.y = start_wp_pos.y - start_position->y;
				direction.z = start_wp_pos.z - start_position->z;

				normalise_3d_vector (&direction);

				heading = atan2 (direction.x, direction.z);

				memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

				ASSERT(point_inside_map_area(start_position));
				
				get_3d_terrain_point_data (start_position->x, start_position->z, &terrain_info);

				normal = get_3d_terrain_point_data_normal (&terrain_info);

				get_3d_transformation_matrix_from_face_normal_and_heading (attitude, normal, heading);

				pitch = get_pitch_from_attitude_matrix (attitude);

				pitch += fuselage_angle;

				roll = get_roll_from_attitude_matrix (attitude);

				set_client_server_entity_attitude_angles (member, heading, pitch, roll);

				member_pos = *start_position;

				member_pos.y += get_local_entity_float_value (member, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);

				pos = *start_position;

				if (get_local_entity_int_value (group, INT_TYPE_MOVEMENT_TYPE) == MOVEMENT_TYPE_AIR)
				{

					pos.y += aircraft_database [member_type].centre_of_gravity_to_ground_distance;
				}

				set_client_server_entity_vec3d (member, VEC3D_TYPE_POSITION, &pos);

				set_local_entity_float_value (member, FLOAT_TYPE_MAIN_ROTOR_RPM, 60.0);

				notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_SITE, landing_en, member);

				notify_local_entity (ENTITY_MESSAGE_LOCK_LANDING_ROUTE, landing_en, member);
			}

			//
			// Assign each member a unique ID number
			//

			set_group_member_numbers (group);

			//
			// mark Keysite as used (after it has actually been used!)
			//

			if (!get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
			{
				set_client_server_entity_int_value (keysite, INT_TYPE_IN_USE, TRUE);
	
				update_imap_sector_side (keysite, TRUE);

				transmit_entity_comms_message (ENTITY_COMMS_UPDATE_SECTOR_SIDE, keysite, TRUE);

				update_imap_importance_level (keysite, TRUE);

				update_keysite_distance_to_friendly_base (keysite, (entity_sides)get_local_entity_int_value (keysite, INT_TYPE_SIDE));
			}

			//
			// Link group to a division
			//
	
			add_group_to_division (group, NULL);

			return group;
		}
		else
		{

			#if DEBUG_MODULE

			debug_log ("FACTION: cant regen. Free %d, reserved %d", free_sites, get_local_entity_int_value (landing_en, INT_TYPE_RESERVED_LANDING_SITES));

			#endif
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_faction_members (entity *keysite, entity_sub_types group_type, formation_component_types formation, int number, entity_sides side, vec3d *position, int client_server_create, int place_at_ground_height)
{

	formation_vehicle_components
		*formation_components;

	formation_type
		*formation_data;

   float
		formation_radius,
		radius,
      fuselage_angle,
      heading,
      pitch,
      roll;

   matrix3x3
      attitude;

   vec3d
      pos,
		delta,
      face_normal;

	list_types
		list_type;

   int
		road_node,
		formation_position,
      loop;

   entity
		*parent,
      *group,
      *member;

	entity_sub_types
		member_type;

	terrain_3d_point_data
		point_data;

   debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	if (keysite)
	{
		ASSERT (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE);
	}

	list_type = group_database [group_type].group_list_type;

	if (list_type == LIST_TYPE_INDEPENDENT_GROUP)
	{
		parent = get_local_force_entity (side);
	}
	else
	{
		ASSERT (keysite);

		parent = keysite;
	}

	ASSERT (parent);

	fuselage_angle = 0;

	if (number > 0)
	{
		memset (&point_data, 0, sizeof (terrain_3d_point_data));

		ASSERT(point_inside_map_area(position));
				
		get_3d_terrain_point_data (position->x, position->z, &point_data);

		if (group_database [group_type].registry_list_type == LIST_TYPE_GROUND_REGISTRY)
		{

			if (get_terrain_type_class (get_3d_terrain_point_data_type (&point_data)) != TERRAIN_CLASS_LAND)
			{

				return NULL;
			}
		}

		formation_components = get_formation_components (formation);

		ASSERT (formation_components);
		
		//
		// create group
		//

		if (client_server_create)
		{
			group = create_client_server_entity
			(
				ENTITY_TYPE_GROUP,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_PARENT (list_type, parent),
				ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, group_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENGAGE_ENEMY, group_database [group_type].default_engage_enemy),
				ENTITY_ATTR_END
			);
		}
		else
		{
			group = create_local_entity
			(
				ENTITY_TYPE_GROUP,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_PARENT (list_type, parent),
				ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position->x, position->y, position->z),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, group_type),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENGAGE_ENEMY, group_database [group_type].default_engage_enemy),
				ENTITY_ATTR_END
			);
		}

		//
		// create members
		//

		formation_data = get_formation (formation_components->formation);

		road_node = get_closest_road_node (position, 5.0);

		formation_radius = get_formation_member_radius (formation_components->formation, number);

		radius = min ((float)(road_nodes [road_node].safe_radius - 5), formation_radius);

		radius = max (radius, 5.0f);

		for (loop = 0; loop < number; loop ++)
		{

			formation_position = (number - loop) - 1;

			//
			// calculate formation position to suite landing entity
			//

			if (side == ENTITY_SIDE_BLUE_FORCE)
			{

				member_type = formation_components->components [loop * 2];
			}
			else
			{
				
				member_type = formation_components->components [(loop * 2) + 1];
			}

			member = create_mobile_member
			(
				group_database [group_type].default_entity_type,
				ENTITY_INDEX_DONT_CARE,
				client_server_create,
				group,
				position,
				member_type,
				formation_position,
				OPERATIONAL_STATE_STOPPED,
				side,
				AIRCRAFT_UNDERCARRIAGE_DOWN_FLOAT_VALUE
			);

			get_local_waypoint_simple_formation_position (formation_position, position, formation_components->formation, &pos);

			bound_position_to_map_area (&pos);

			//
			// Spread out into safe radius
			//

			if (get_local_entity_type (member) == ENTITY_TYPE_ROUTED_VEHICLE)
			{
		
				if (formation_radius != 0.0)
				{

					delta.x = pos.x - position->x;
					delta.y = pos.y - position->y;
					delta.z = pos.z - position->z;
			
					pos.x = position->x + ((delta.x * radius) / formation_radius);
					pos.y = position->y + ((delta.y * radius) / formation_radius);
					pos.z = position->z + ((delta.z * radius) / formation_radius);
				}
			}

			fuselage_angle = get_local_entity_float_value (member, FLOAT_TYPE_FUSELAGE_ANGLE);

			if (place_at_ground_height)
			{
	
				pos.y = get_3d_terrain_elevation_and_face_normal (pos.x, pos.z, &face_normal, NULL);
	
				pos.y += get_local_entity_float_value (member, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);
			}

			////////////////////////////////////////
			//
			// attitude
			//
			////////////////////////////////////////

			if (get_local_entity_type (member) == ENTITY_TYPE_ROUTED_VEHICLE)
			{

				heading = rad ((get_local_entity_index (member) * get_local_entity_index (member)) % 360); // debug - random heading...
			}
			else
			{
				heading = 0.0;
			}

			get_3d_transformation_matrix_from_face_normal_and_heading (attitude, &face_normal, heading);

			pitch = get_pitch_from_attitude_matrix (attitude);

			pitch += fuselage_angle;

			roll = get_roll_from_attitude_matrix (attitude);

			set_local_entity_attitude_angles (member, heading, pitch, roll);

			//
			// set position
			//

			set_local_entity_vec3d (member, VEC3D_TYPE_POSITION, &pos);

			#if DEBUG_MODULE

			debug_log ("FACTION: create members type %d, sub type %d, number %d at %f, %f, %f, in formation %s", member_type, group_type, number, position->x, position->y, position->z, get_formation_name (formation));

			#endif
		}

		//
		// Assign each member a unique ID number
		//

		set_group_member_numbers (group);

		return group;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void place_frontline_forces (entity *force, int force_size)
{

	sector
		*sector_raw;

	formation_component_types
		formation_component;

	entity
		*group,
		*keysite,
		*sector_en;

	entity_sides
		side,
		enemy_side;

	unsigned int
		node2;

	int
		artillery_node,
		secondary_node,
		mlrs_flag,
		node,
		number;

	vec3d
		*pos;

	if (!get_road_nodes_loaded ())
	{
		return;
	}

	//
	// Setup frontline_forces data
	//

	if (frontline_forces_data)
	{
		free_mem (frontline_forces_data);
	}

	frontline_forces_data = (frontline_forces_placement_data *) malloc_heap_mem (sizeof (frontline_forces_placement_data) * total_number_of_road_nodes);

	memset (frontline_forces_data, 0, sizeof (frontline_forces_placement_data) * total_number_of_road_nodes);

	side = (entity_sides)get_local_entity_int_value (force, INT_TYPE_SIDE);

	enemy_side = get_enemy_side (side);

	for (node = 0; node < total_number_of_road_nodes; node ++)
	{
		sector_en = get_local_sector_entity (&road_node_positions [node]);

		frontline_forces_data [node].side = get_local_entity_int_value (sector_en, INT_TYPE_SIDE);
	}
	
	//
	// Parse route data for Primary placement
	//

	for (node = 0; node < total_number_of_road_nodes; node ++)
	{

		sector_en = get_local_sector_entity (&road_node_positions [node]);

		sector_raw = (sector *) get_local_entity_data (sector_en);

		if (sector_raw->side != side)
		{

			continue;
		}

		//
		// Check if node links cross frontline
		//

		for (node2 = 0; node2 < road_nodes [node].number_of_links; node2 ++)
		{
			if (frontline_forces_data [road_nodes [node].links [node2].node].side == enemy_side)
			{

				#if DEBUG_MODULE

				debug_log ("FACTION: marking node %d for PRIMARY FORCE PLACEMENT side %s (boundary node)", node, entity_side_names [side]);

				#endif

				frontline_forces_data [node].force_placement_type = FRONTLINE_FORCE_PRIMARY;
	
				break;
			}
		}
	}
	
	//
	// Parse route data for Secondary placement
	//

	for (node = 0; node < total_number_of_road_nodes; node ++)
	{

		sector_en = get_local_sector_entity (&road_node_positions [node]);

		sector_raw = (sector *) get_local_entity_data (sector_en);

		if (sector_raw->side != side)
		{

			continue;
		}

		if (frontline_forces_data [node].force_placement_type == FRONTLINE_FORCE_PRIMARY)
		{

			for (node2 = 0; node2 < road_nodes [node].number_of_links; node2 ++)
			{

				secondary_node = road_nodes [node].links [node2].node;

//				if ((road_nodes [secondary_node].side_aware & side) &&
				if ((frontline_forces_data [secondary_node].side == side) &&
					(frontline_forces_data [secondary_node].force_placement_type == FRONTLINE_FORCE_NONE))
				{

					#if DEBUG_MODULE

					debug_log ("FACTION: marking node %d for SECONDARY FORCE PLACEMENT side %s (supporting %d)", secondary_node, entity_side_names [side], node);

					#endif

					frontline_forces_data [secondary_node].force_placement_type = FRONTLINE_FORCE_SECONDARY;

//					frontline_forces_data [secondary_node].side = side;
				}
			}
		}
	}

	//
	// Parse route data for Artillery placement
	//

	for (node = 0; node < total_number_of_road_nodes; node ++)
	{

		sector_en = get_local_sector_entity (&road_node_positions [node]);

		sector_raw = (sector *) get_local_entity_data (sector_en);

		if (sector_raw->side != side)
		{

			continue;
		}

		if (frontline_forces_data [node].force_placement_type == FRONTLINE_FORCE_SECONDARY)
		{

			for (node2 = 0; node2 < road_nodes [node].number_of_links; node2 ++)
			{

				artillery_node = road_nodes [node].links [node2].node;

//				if ((road_nodes [artillery_node].side_aware & side) &&
				if ((frontline_forces_data [artillery_node].side == side) &&
					(frontline_forces_data [artillery_node].force_placement_type == FRONTLINE_FORCE_NONE))
				{

					#if DEBUG_MODULE

					debug_log ("FACTION: marking node %d for ARTILLERY FORCE PLACEMENT side %s (supporting %d)", artillery_node, entity_side_names [side], node);

					#endif

					frontline_forces_data [artillery_node].force_placement_type = FRONTLINE_FORCE_ARTILLERY;

//					frontline_forces_data [artillery_node].side = side;
				}
			}
		}
	}

	//
	// Now actually place Units according to frontline_force_data
	//

	mlrs_flag = FALSE;

	for (node = 0; node < total_number_of_road_nodes; node ++)
	{

		switch (frontline_forces_data [node].force_placement_type)
		{

			case FRONTLINE_FORCE_PRIMARY:
			{

				//
				// place suitable number of units
				//

				pos = &road_node_positions [node];

				if ((point_inside_adjusted_map_area (pos)) && (check_point_inside_population_area (pos)))
				{
					#if DEBUG_MODULE

					debug_log ("FACTION: placing PRIMARY forces at node %d", node);

					#endif

//					number = rand16 () % max (1, (int) (road_nodes [node].safe_radius / 3.0));
					number = (int)((road_nodes [node].safe_radius / 4.0) + (sfrand1 () * 2.0));
	
					number = bound (number, 1, force_size);
	
					formation_component = FORMATION_COMPONENT_PRIMARY_FRONTLINE_GROUP;
	
					keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, side, pos, 1.0 * KILOMETRE, NULL, NULL);
	
					ASSERT (keysite);
	
					group = create_faction_members (keysite, ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE, formation_component, number, side, pos, TRUE, TRUE);
	
					if (group)
					{
						set_local_entity_int_value (group, INT_TYPE_ROUTE_NODE, node);
		
						road_nodes [node].side_occupying = side;
					}
	
					//return; // debug just make 1 group
				}

				break;
			}

			case FRONTLINE_FORCE_SECONDARY:
			{

				pos = &road_node_positions [node];

				if ((point_inside_adjusted_map_area (pos)) && (check_point_inside_population_area (pos)))
				{
					#if DEBUG_MODULE
		
					debug_log ("FACTION: placing SECONDARY forces at node %d", node);
	
					#endif
	
//					number = rand16 () % max (1, (int) (road_nodes [node].safe_radius / 3.0));
					number = (int)((road_nodes [node].safe_radius / 4.0) + (sfrand1 () * 2.0));
	
					number = bound (number, 1, force_size);
	
					formation_component = FORMATION_COMPONENT_SECONDARY_FRONTLINE_GROUP;
	
					keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, side, pos, 1.0 * KILOMETRE, NULL, NULL);
	
					ASSERT (keysite);
	
					group = create_faction_members (keysite, ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE, formation_component, number, side, pos, TRUE, TRUE);
	
					if (group)
					{
						set_local_entity_int_value (group, INT_TYPE_ROUTE_NODE, node);
		
						road_nodes [node].side_occupying = side;
					}
				}
				
				break;
			}

			case FRONTLINE_FORCE_ARTILLERY:
			{

				formation_vehicle_components
					*formation_component_data;

				formation_type
					*formation_data;

				int
					size;

				pos = &road_node_positions [node];

				if ((point_inside_adjusted_map_area (pos)) && (check_point_inside_population_area (pos)))
				{
					#if DEBUG_MODULE
		
					debug_log ("FACTION: placing ARTILLERY forces at node %d", node);
	
					#endif
	
					if (mlrs_flag)
					{
						formation_component = FORMATION_COMPONENT_MLRS_GROUP;
					}
					else
					{
						formation_component = FORMATION_COMPONENT_ARTILLERY_GROUP;
					}
	
					mlrs_flag = !mlrs_flag;
	
					formation_component_data = get_formation_components (formation_component);
	
					formation_data = get_formation (formation_component_data->formation);
	
//					number = rand16 () % max (1, (int) (road_nodes [node].safe_radius / 3.0));
					number = (int)(road_nodes [node].safe_radius / 5.0);
	
					size = min (force_size, formation_component_data->count);
	
					number = bound (number, 1, size);
	
					keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, side, pos, 1.0 * KILOMETRE, NULL, NULL);
	
					ASSERT (keysite);
	
					group = create_faction_members (keysite, formation_component_data->group_type, formation_component, number, side, pos, TRUE, TRUE);
	
					if (group)
					{
						set_local_entity_int_value (group, INT_TYPE_ROUTE_NODE, node);
		
						road_nodes [node].side_occupying = side;
					}
				}
				
				break;
			}
		}
	}

	//
	// Free memory
	//

	free_mem (frontline_forces_data);

	frontline_forces_data = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_mobile_member (
									entity_types type,
									int index,
									int client_server_create,
									entity *group,
									vec3d *position,
									entity_sub_types member_type,
									int formation_position,
									int operational_state,
									entity_sides side,
									float uc_state)
{

	entity
		*member;
	
	member = NULL;

	if ((!client_server_create) || (command_line_run_mode == RUN_MODE_AITOOL))
	{
		//
		// Run mode "AI tool" - everything gets created local-only
		//
		
		switch (type)
		{

			case ENTITY_TYPE_ANTI_AIRCRAFT:
			{
				member = create_local_entity_anti_aircraft (index, member_type, group, position);
	
				break;
			}

			case ENTITY_TYPE_ROUTED_VEHICLE:
			{

				member = create_local_entity_routed_vehicle (index, member_type, group, position);

				break;
			}

			case ENTITY_TYPE_SHIP_VEHICLE:
			{

				member = create_local_entity_ship (index, member_type, group, position);

				break;
			}

			case ENTITY_TYPE_PERSON:
			{

				member = create_local_entity_person (index, member_type, group, position);

				break;
			}

			default:
			{
				debug_fatal ("FACTION : Invalid mobile created ( type %s )", entity_type_names [type]);
			}
		}

		set_local_entity_int_value (member, INT_TYPE_FORMATION_POSITION, formation_position);

		set_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, operational_state);
	}
	else
	{
		//
		// Run mode "normal" - everything gets created client-server
		//
	
		switch (type)
		{
	
			case ENTITY_TYPE_ANTI_AIRCRAFT:
			{
				member = create_client_server_entity_anti_aircraft (index, member_type, group, position);

				break;
			}

			case ENTITY_TYPE_FIXED_WING:
			{
		
				member = create_client_server_entity_fixed_wing (index, member_type, group, position);
	
				set_client_server_entity_float_value (member, FLOAT_TYPE_UNDERCARRIAGE_STATE, uc_state);
	
				break;
			}
	
			case ENTITY_TYPE_HELICOPTER:
			{
	
				member = create_client_server_entity_helicopter (index, member_type, group, position);
	
				set_client_server_entity_float_value (member, FLOAT_TYPE_UNDERCARRIAGE_STATE, uc_state);
	
				break;
			}
	
			case ENTITY_TYPE_ROUTED_VEHICLE:
			{
	
				member = create_client_server_entity_routed_vehicle (index, member_type, group, position);

				debug_log ("FACTION: created ROUTED_VEHICLE %s (%d) with formation %d", get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member), formation_position);
	
				break;
			}
	
			case ENTITY_TYPE_SHIP_VEHICLE:
			{
	
				member = create_client_server_entity_ship (index, member_type, group, position);
	
				break;
			}
	
			case ENTITY_TYPE_PERSON:
			{
	
				member = create_client_server_entity_person (index, member_type, group, position);
	
				break;
			}
	
			default:
			{
				debug_fatal ("FACTION : Invalid mobile created ( type %s )", entity_type_names [type]);
			}
		}
	
		set_client_server_entity_int_value (member, INT_TYPE_FORMATION_POSITION, formation_position);

		set_client_server_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, operational_state);
	}

	return member;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

