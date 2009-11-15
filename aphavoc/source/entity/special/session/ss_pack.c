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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void pack_local_data (entity *en, pack_modes mode)
{
   ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

   switch (mode)
   {
      ////////////////////////////////////////
      case PACK_MODE_SERVER_SESSION:
      case PACK_MODE_CLIENT_SESSION:
      case PACK_MODE_BROWSE_SESSION:
      ////////////////////////////////////////
		{

			break;
		}

      ////////////////////////////////////////
      case PACK_MODE_UPDATE_ENTITY:
      ////////////////////////////////////////
      {
         session
            *raw;

         raw = (session *) get_local_entity_data (en);

         pack_float_value (en, FLOAT_TYPE_ELAPSED_TIME, raw->elapsed_time);

         pack_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER, raw->lightning_timer);

			//
			// rain effect
			//

         pack_float_value (en, FLOAT_TYPE_WEATHER_RADIUS, raw->weather_radius);

			pack_vec3d (en, VEC3D_TYPE_WEATHER_POSITION, &raw->weather_position);
			pack_vec3d (en, VEC3D_TYPE_WEATHER_VELOCITY, &raw->weather_velocity);

			//
			// wind effect
			//

         pack_float_value (en, FLOAT_TYPE_WIND_EFFECT_RADIUS, raw->wind_effect_radius);
         pack_float_value (en, FLOAT_TYPE_WIND_GUSTING_VALUE, raw->wind_gusting_value);

			pack_vec3d (en, VEC3D_TYPE_WIND_DIRECTION_VECTOR, &raw->wind_direction_vector);
			pack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_POSITION, &raw->wind_effect_position);
			pack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_VELOCITY, &raw->wind_effect_velocity);

			//

         pack_int_value (en, INT_TYPE_WEATHER_INCREASING, raw->weather_increasing);

         pack_int_value (en, INT_TYPE_WIND_INCREASING, raw->wind_increasing);

         break;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void unpack_local_data (entity *en, entity_types type, pack_modes mode)
{
   ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

   switch (mode)
   {
      ////////////////////////////////////////
      case PACK_MODE_SERVER_SESSION:
      case PACK_MODE_CLIENT_SESSION:
		case PACK_MODE_BROWSE_SESSION:
      ////////////////////////////////////////
		{

			break;
		}

		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			vec3d
				v;

			//
			// always use access functions to set the data
			//

			set_local_entity_float_value (en, FLOAT_TYPE_ELAPSED_TIME, unpack_float_value (en, FLOAT_TYPE_ELAPSED_TIME));

         set_local_entity_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER, unpack_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER));

			//
			// rain effect
			//

         set_local_entity_float_value (en, FLOAT_TYPE_WEATHER_RADIUS, unpack_float_value (en, FLOAT_TYPE_WEATHER_RADIUS));

			unpack_vec3d (en, VEC3D_TYPE_WEATHER_POSITION, &v);
			set_local_entity_vec3d (en, VEC3D_TYPE_WEATHER_POSITION, &v);

			unpack_vec3d (en, VEC3D_TYPE_WEATHER_VELOCITY, &v);
			set_local_entity_vec3d (en, VEC3D_TYPE_WEATHER_VELOCITY, &v);

			//
			// wind effect
			//

			set_local_entity_float_value (en, FLOAT_TYPE_WIND_EFFECT_RADIUS, unpack_float_value (en, FLOAT_TYPE_WIND_EFFECT_RADIUS));
			set_local_entity_float_value (en, FLOAT_TYPE_WIND_GUSTING_VALUE, unpack_float_value (en, FLOAT_TYPE_WIND_GUSTING_VALUE));

			unpack_vec3d (en, VEC3D_TYPE_WIND_DIRECTION_VECTOR, &v);
			set_local_entity_vec3d (en, VEC3D_TYPE_WIND_DIRECTION_VECTOR, &v);

			unpack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_POSITION, &v);
			set_local_entity_vec3d (en, VEC3D_TYPE_WIND_EFFECT_POSITION, &v);

			unpack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_VELOCITY, &v);
			set_local_entity_vec3d (en, VEC3D_TYPE_WIND_EFFECT_VELOCITY, &v);

			//

         set_local_entity_int_value (en, INT_TYPE_WEATHER_INCREASING, unpack_int_value (en, INT_TYPE_WEATHER_INCREASING));

         set_local_entity_int_value (en, INT_TYPE_WIND_INCREASING, unpack_int_value (en, INT_TYPE_WIND_INCREASING));

			set_display_campaign_timer_valid (TRUE);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_session_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_SESSION]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_SESSION]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_local_session_data (pack_modes mode)
{
	session
		*raw;

	entity
		*en;

   ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	en = get_session_entity ();

	ASSERT (en);

	raw = (session *) get_local_entity_data (en);

   switch (mode)
   {
      ////////////////////////////////////////
      case PACK_MODE_SERVER_SESSION:
      ////////////////////////////////////////
		{
			ASSERT (!raw->session_complete);
		
			pack_int_value (en, INT_TYPE_VERSION_NUMBER, raw->version_number);
		
			pack_list_root (en, LIST_TYPE_FORCE, &raw->force_root);
		
			// special_effect_root
		
			// update_link
		
			pack_float_value (en, FLOAT_TYPE_ELAPSED_TIME, raw->elapsed_time);
		
			pack_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER, raw->lightning_timer);
		
			pack_float_value (en, FLOAT_TYPE_START_TIME, raw->start_time);
		
			// time_of_day_resync
		
			pack_float_value (en, FLOAT_TYPE_TIME_OF_DAY_ACCELERATION, raw->time_of_day_acceleration);
		
			pack_float_value (en, FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE, raw->fog_of_war_maximum_value);
		
			//
			// rain effect
			//
		
			pack_float_value (en, FLOAT_TYPE_WEATHER_RADIUS, raw->weather_radius);
			pack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD, raw->weather_mode_transitional_period);
			pack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS, raw->weather_mode_transitional_status);
		
			pack_int_value (en, INT_TYPE_WEATHER_MODE, raw->weather_mode);
			pack_int_value (en, INT_TYPE_TARGET_WEATHER_MODE, raw->target_weather_mode);
		
			pack_vec3d (en, VEC3D_TYPE_WEATHER_POSITION, &raw->weather_position);
			pack_vec3d (en, VEC3D_TYPE_WEATHER_VELOCITY, &raw->weather_velocity);
		
			//
			// wind effect
			//
		
			pack_float_value (en, FLOAT_TYPE_WIND_EFFECT_RADIUS, raw->wind_effect_radius);
			pack_float_value (en, FLOAT_TYPE_WIND_GUSTING_VALUE, raw->wind_gusting_value);
			pack_float_value (en, FLOAT_TYPE_WIND_MINIMUM_SPEED, raw->wind_minimum_speed);
			pack_float_value (en, FLOAT_TYPE_WIND_MAXIMUM_SPEED, raw->wind_maximum_speed);
		
			pack_vec3d (en, VEC3D_TYPE_WIND_DIRECTION_VECTOR, &raw->wind_direction_vector);
			pack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_POSITION, &raw->wind_effect_position);
			pack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_VELOCITY, &raw->wind_effect_velocity);
		
			//
		
			pack_int_value (en, INT_TYPE_DAY_SEGMENT_TYPE, raw->day_segment_type);

			pack_float_value (en, FLOAT_TYPE_POPULATION_X_MIN, raw->population_x_min);
			pack_float_value (en, FLOAT_TYPE_POPULATION_X_MAX, raw->population_x_max);
			pack_float_value (en, FLOAT_TYPE_POPULATION_Z_MIN, raw->population_z_min);
			pack_float_value (en, FLOAT_TYPE_POPULATION_Z_MAX, raw->population_z_max);
		
			pack_int_value (en, INT_TYPE_CAMPAIGN_MEDAL, raw->campaign_medal);

			pack_int_value (en, INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC, raw->campaign_requires_apache_havoc);
		
			pack_int_value (en, INT_TYPE_AUTO_ASSIGN_GUNSHIP, raw->auto_assign_gunship);
		
			pack_int_value (en, INT_TYPE_INFINITE_FUEL, raw->infinite_fuel);
		
			pack_int_value (en, INT_TYPE_INFINITE_WEAPONS, raw->infinite_weapons);
		
			pack_int_value (en, INT_TYPE_SUPPRESS_AI_FIRE, raw->suppress_ai_fire);
		
			pack_int_value (en, INT_TYPE_INVULNERABLE_FROM_COLLISIONS, raw->invulnerable_from_collisions);

			pack_int_value (en, INT_TYPE_INVULNERABLE_FROM_WEAPONS, raw->invulnerable_from_weapons);
		
			pack_int_value (en, INT_TYPE_CHEATS_ENABLED, raw->cheats_enabled);
		
			pack_int_value (en, INT_TYPE_SKIP_NIGHT_TIME, raw->skip_night_time);
		
			pack_int_value (en, INT_TYPE_WEATHER_INCREASING, raw->weather_increasing);
		
			pack_int_value (en, INT_TYPE_WIND_INCREASING, raw->wind_increasing);
		
			pack_int_value (en, INT_TYPE_LOCAL_WEATHER_MODEL, raw->local_weather_model);

			break;
		}

      ////////////////////////////////////////
      case PACK_MODE_CLIENT_SESSION:
      ////////////////////////////////////////
      {
         pack_entity_safe_ptr (en);

         pack_int_value (en, INT_TYPE_VERSION_NUMBER, raw->version_number);

			pack_int_value (en, INT_TYPE_SESSION_COMPLETE, raw->session_complete);
		
         pack_list_root (en, LIST_TYPE_FORCE, &raw->force_root);

			pack_list_root (en, LIST_TYPE_SPECIAL_EFFECT, &raw->special_effect_root);

			// update_link

         pack_float_value (en, FLOAT_TYPE_ELAPSED_TIME, raw->elapsed_time);

         pack_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER, raw->lightning_timer);

         pack_float_value (en, FLOAT_TYPE_START_TIME, raw->start_time);

			// time_of_day_resync

         pack_float_value (en, FLOAT_TYPE_TIME_OF_DAY_ACCELERATION, raw->time_of_day_acceleration);

			pack_float_value (en, FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE, raw->fog_of_war_maximum_value);
		
			//
			// rain effect
			//

         pack_float_value (en, FLOAT_TYPE_WEATHER_RADIUS, raw->weather_radius);
         pack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD, raw->weather_mode_transitional_period);
         pack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS, raw->weather_mode_transitional_status);

         pack_int_value (en, INT_TYPE_WEATHER_MODE, raw->weather_mode);
         pack_int_value (en, INT_TYPE_TARGET_WEATHER_MODE, raw->target_weather_mode);

			pack_vec3d (en, VEC3D_TYPE_WEATHER_POSITION, &raw->weather_position);
			pack_vec3d (en, VEC3D_TYPE_WEATHER_VELOCITY, &raw->weather_velocity);

			//
			// wind effect
			//

         pack_float_value (en, FLOAT_TYPE_WIND_EFFECT_RADIUS, raw->wind_effect_radius);
         pack_float_value (en, FLOAT_TYPE_WIND_GUSTING_VALUE, raw->wind_gusting_value);
         pack_float_value (en, FLOAT_TYPE_WIND_MINIMUM_SPEED, raw->wind_minimum_speed);
         pack_float_value (en, FLOAT_TYPE_WIND_MAXIMUM_SPEED, raw->wind_maximum_speed);

			pack_vec3d (en, VEC3D_TYPE_WIND_DIRECTION_VECTOR, &raw->wind_direction_vector);
			pack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_POSITION, &raw->wind_effect_position);
			pack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_VELOCITY, &raw->wind_effect_velocity);

			//

         pack_int_value (en, INT_TYPE_DAY_SEGMENT_TYPE, raw->day_segment_type);

			pack_float_value (en, FLOAT_TYPE_POPULATION_X_MIN, raw->population_x_min);
			pack_float_value (en, FLOAT_TYPE_POPULATION_X_MAX, raw->population_x_max);
			pack_float_value (en, FLOAT_TYPE_POPULATION_Z_MIN, raw->population_z_min);
			pack_float_value (en, FLOAT_TYPE_POPULATION_Z_MAX, raw->population_z_max);
		
			pack_int_value (en, INT_TYPE_CAMPAIGN_MEDAL, raw->campaign_medal);
		
			pack_int_value (en, INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC, raw->campaign_requires_apache_havoc);

         pack_int_value (en, INT_TYPE_AUTO_ASSIGN_GUNSHIP, raw->auto_assign_gunship);

         pack_int_value (en, INT_TYPE_INFINITE_FUEL, raw->infinite_fuel);

         pack_int_value (en, INT_TYPE_INFINITE_WEAPONS, raw->infinite_weapons);

         pack_int_value (en, INT_TYPE_SUPPRESS_AI_FIRE, raw->suppress_ai_fire);

         pack_int_value (en, INT_TYPE_INVULNERABLE_FROM_COLLISIONS, raw->invulnerable_from_collisions);

         pack_int_value (en, INT_TYPE_INVULNERABLE_FROM_WEAPONS, raw->invulnerable_from_weapons);

			pack_int_value (en, INT_TYPE_CHEATS_ENABLED, raw->cheats_enabled);
		
         pack_int_value (en, INT_TYPE_SKIP_NIGHT_TIME, raw->skip_night_time);

         pack_int_value (en, INT_TYPE_WEATHER_INCREASING, raw->weather_increasing);

         pack_int_value (en, INT_TYPE_WIND_INCREASING, raw->wind_increasing);

         pack_int_value (en, INT_TYPE_LOCAL_WEATHER_MODEL, raw->local_weather_model);

         break;
      }

      ////////////////////////////////////////
      case PACK_MODE_BROWSE_SESSION:
      ////////////////////////////////////////
      {
         pack_entity_safe_ptr (en);

			pack_int_value (en, INT_TYPE_VERSION_NUMBER, raw->version_number);

         pack_list_root (en, LIST_TYPE_FORCE, &raw->force_root);

			// update_link

			// tour of duty time

         pack_float_value (en, FLOAT_TYPE_ELAPSED_TIME, raw->elapsed_time);

			// lightning_timer

         pack_float_value (en, FLOAT_TYPE_START_TIME, raw->start_time);

			// time_of_day_resync

			// time_of_day_acceleration

			// weather radius

			// weather_mode_transitional_period

			// weather_mode_transitional_status

         pack_int_value (en, INT_TYPE_WEATHER_MODE, raw->weather_mode);

			// target_weather_mode

			// weather position

			// weather velocity

         pack_int_value (en, INT_TYPE_DAY_SEGMENT_TYPE, raw->day_segment_type);

			pack_float_value (en, FLOAT_TYPE_POPULATION_X_MIN, raw->population_x_min);
			pack_float_value (en, FLOAT_TYPE_POPULATION_X_MAX, raw->population_x_max);
			pack_float_value (en, FLOAT_TYPE_POPULATION_Z_MIN, raw->population_z_min);
			pack_float_value (en, FLOAT_TYPE_POPULATION_Z_MAX, raw->population_z_max);
		
			pack_int_value (en, INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC, raw->campaign_requires_apache_havoc);

			// infinite_weapons

			// skip_night_time

			// weather increasing

         break;
      }
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_local_session_data (pack_modes mode)
{
	session
		*raw;

	entity
		*en;

	int
		index;

   ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

   switch (mode)
   {
      ////////////////////////////////////////
      case PACK_MODE_SERVER_SESSION:
      ////////////////////////////////////////
		{
			en = get_session_entity ();

			ASSERT (en);
			
			raw = (session *) get_local_entity_data (en);

			raw->version_number = unpack_int_value (en, INT_TYPE_VERSION_NUMBER);
		
			unpack_list_root (en, LIST_TYPE_FORCE, &raw->force_root);
		
			// special_effect_root
		
			// update_link
		
			raw->elapsed_time = unpack_float_value (en, FLOAT_TYPE_ELAPSED_TIME);
		
			raw->lightning_timer = unpack_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER);
		
			raw->start_time = unpack_float_value (en, FLOAT_TYPE_START_TIME);
		
			// time_of_day_resync
		
			raw->time_of_day_acceleration = unpack_float_value (en, FLOAT_TYPE_TIME_OF_DAY_ACCELERATION);
		
			raw->fog_of_war_maximum_value = unpack_float_value (en, FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE);
		
			//
			// rain effect
			//
		
			raw->weather_radius = unpack_float_value (en, FLOAT_TYPE_WEATHER_RADIUS);
			raw->weather_mode_transitional_period = unpack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD);
			raw->weather_mode_transitional_status = unpack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS);
		
			raw->weather_mode = (weathermodes) unpack_int_value (en, INT_TYPE_WEATHER_MODE);
			raw->target_weather_mode = (weathermodes) unpack_int_value (en, INT_TYPE_TARGET_WEATHER_MODE);
		
			unpack_vec3d (en, VEC3D_TYPE_WEATHER_POSITION, &raw->weather_position);
			unpack_vec3d (en, VEC3D_TYPE_WEATHER_VELOCITY, &raw->weather_velocity);
		
			//
			// wind effect
			//
		
			raw->wind_effect_radius = unpack_float_value (en, FLOAT_TYPE_WIND_EFFECT_RADIUS);
			raw->wind_gusting_value = unpack_float_value (en, FLOAT_TYPE_WIND_GUSTING_VALUE);
			raw->wind_minimum_speed = unpack_float_value (en, FLOAT_TYPE_WIND_MINIMUM_SPEED);
			raw->wind_maximum_speed = unpack_float_value (en, FLOAT_TYPE_WIND_MAXIMUM_SPEED);
		
			unpack_vec3d (en, VEC3D_TYPE_WIND_DIRECTION_VECTOR, &raw->wind_direction_vector);
			unpack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_POSITION, &raw->wind_effect_position);
			unpack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_VELOCITY, &raw->wind_effect_velocity);
		
			//
		
			raw->day_segment_type = (day_segment_types) unpack_int_value (en, INT_TYPE_DAY_SEGMENT_TYPE);

			raw->population_x_min = unpack_float_value (en, FLOAT_TYPE_POPULATION_X_MIN);
			raw->population_x_max = unpack_float_value (en, FLOAT_TYPE_POPULATION_X_MAX);
			raw->population_z_min = unpack_float_value (en, FLOAT_TYPE_POPULATION_Z_MIN);
			raw->population_z_max = unpack_float_value (en, FLOAT_TYPE_POPULATION_Z_MAX);
		
			raw->campaign_medal = unpack_int_value (en, INT_TYPE_CAMPAIGN_MEDAL);
		
			raw->campaign_requires_apache_havoc = unpack_int_value (en, INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC);
		
			raw->auto_assign_gunship = unpack_int_value (en, INT_TYPE_AUTO_ASSIGN_GUNSHIP);
		
			raw->infinite_fuel = unpack_int_value (en, INT_TYPE_INFINITE_FUEL);
		
			raw->infinite_weapons = unpack_int_value (en, INT_TYPE_INFINITE_WEAPONS);
		
			raw->suppress_ai_fire = unpack_int_value (en, INT_TYPE_SUPPRESS_AI_FIRE);
		
			raw->invulnerable_from_collisions = unpack_int_value (en, INT_TYPE_INVULNERABLE_FROM_COLLISIONS);

			raw->invulnerable_from_weapons = unpack_int_value (en, INT_TYPE_INVULNERABLE_FROM_WEAPONS);
		
			raw->cheats_enabled = unpack_int_value (en, INT_TYPE_CHEATS_ENABLED);
		
			raw->skip_night_time = unpack_int_value (en, INT_TYPE_SKIP_NIGHT_TIME);
		
			raw->weather_increasing = unpack_int_value (en, INT_TYPE_WEATHER_INCREASING);
		
			raw->wind_increasing = unpack_int_value (en, INT_TYPE_WIND_INCREASING);
		
			raw->local_weather_model = unpack_int_value (en, INT_TYPE_LOCAL_WEATHER_MODEL);

			break;
		}
      ////////////////////////////////////////
      case PACK_MODE_CLIENT_SESSION:
      ////////////////////////////////////////
      {
         //
         // create entity
         //

			ASSERT (!get_session_entity ());

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, ENTITY_TYPE_SESSION);

			raw = (session *) malloc_fast_mem (sizeof (session));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (session));

			//
			// unpack data (in exactly the same order as the data was packed)
			//

			raw->version_number = unpack_int_value (en, INT_TYPE_VERSION_NUMBER);

			raw->session_complete = unpack_int_value (en, INT_TYPE_SESSION_COMPLETE);
		
			unpack_list_root (en, LIST_TYPE_FORCE, &raw->force_root);

			unpack_list_root (en, LIST_TYPE_SPECIAL_EFFECT, &raw->special_effect_root);

			// update_link

			raw->elapsed_time = unpack_float_value (en, FLOAT_TYPE_ELAPSED_TIME);

         raw->lightning_timer = unpack_float_value (en, FLOAT_TYPE_LIGHTNING_TIMER);

			raw->start_time = unpack_float_value (en, FLOAT_TYPE_START_TIME);

			// time_of_day_resync

			raw->time_of_day_acceleration = unpack_float_value (en, FLOAT_TYPE_TIME_OF_DAY_ACCELERATION);

			raw->fog_of_war_maximum_value = unpack_float_value (en, FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE);
		
			//
			// rain effect
			//

         raw->weather_radius = unpack_float_value (en, FLOAT_TYPE_WEATHER_RADIUS);
         raw->weather_mode_transitional_period = unpack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD);
         raw->weather_mode_transitional_status = unpack_float_value (en, FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS);

         raw->weather_mode = (weathermodes) unpack_int_value (en, INT_TYPE_WEATHER_MODE);
         raw->target_weather_mode = (weathermodes) unpack_int_value (en, INT_TYPE_TARGET_WEATHER_MODE);

			unpack_vec3d (en, VEC3D_TYPE_WEATHER_POSITION, &raw->weather_position);
			unpack_vec3d (en, VEC3D_TYPE_WEATHER_VELOCITY, &raw->weather_velocity);

			//
			// wind effect
			//

			raw->wind_effect_radius = unpack_float_value (en, FLOAT_TYPE_WIND_EFFECT_RADIUS);
         raw->wind_gusting_value = unpack_float_value (en, FLOAT_TYPE_WIND_GUSTING_VALUE);
			raw->wind_minimum_speed = unpack_float_value (en, FLOAT_TYPE_WIND_MINIMUM_SPEED);
			raw->wind_maximum_speed = unpack_float_value (en, FLOAT_TYPE_WIND_MAXIMUM_SPEED);

			unpack_vec3d (en, VEC3D_TYPE_WIND_DIRECTION_VECTOR, &raw->wind_direction_vector);
			unpack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_POSITION, &raw->wind_effect_position);
			unpack_vec3d (en, VEC3D_TYPE_WIND_EFFECT_VELOCITY, &raw->wind_effect_velocity);

			//

			raw->day_segment_type = (day_segment_types) unpack_int_value (en, INT_TYPE_DAY_SEGMENT_TYPE);

			raw->population_x_min = unpack_float_value (en, FLOAT_TYPE_POPULATION_X_MIN);
			raw->population_x_max = unpack_float_value (en, FLOAT_TYPE_POPULATION_X_MAX);
			raw->population_z_min = unpack_float_value (en, FLOAT_TYPE_POPULATION_Z_MIN);
			raw->population_z_max = unpack_float_value (en, FLOAT_TYPE_POPULATION_Z_MAX);
		
			raw->campaign_medal = unpack_int_value (en, INT_TYPE_CAMPAIGN_MEDAL);
		
			raw->campaign_requires_apache_havoc = unpack_int_value (en, INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC);

			raw->auto_assign_gunship = unpack_int_value (en, INT_TYPE_AUTO_ASSIGN_GUNSHIP);

         raw->infinite_fuel = unpack_int_value (en, INT_TYPE_INFINITE_FUEL);

         raw->infinite_weapons = unpack_int_value (en, INT_TYPE_INFINITE_WEAPONS);

         raw->suppress_ai_fire = unpack_int_value (en, INT_TYPE_SUPPRESS_AI_FIRE);
		
			raw->invulnerable_from_collisions = unpack_int_value (en, INT_TYPE_INVULNERABLE_FROM_COLLISIONS);

			raw->invulnerable_from_weapons = unpack_int_value (en, INT_TYPE_INVULNERABLE_FROM_WEAPONS);

			raw->cheats_enabled = unpack_int_value (en, INT_TYPE_CHEATS_ENABLED);
		
         raw->skip_night_time = unpack_int_value (en, INT_TYPE_SKIP_NIGHT_TIME);

         raw->weather_increasing = unpack_int_value (en, INT_TYPE_WEATHER_INCREASING);

         raw->wind_increasing = unpack_int_value (en, INT_TYPE_WIND_INCREASING);

         raw->local_weather_model = unpack_int_value (en, INT_TYPE_LOCAL_WEATHER_MODEL);

			//
			// link into system
			//

			//
			// need to insert session into update list after camera entity
			//

			ASSERT (get_camera_entity ());

         insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), get_camera_entity ());

			set_session_entity (en);

			set_display_campaign_timer_valid (FALSE);

			break;
		}

		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			//
			// create entity
			//

			ASSERT (!get_session_entity ());

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, ENTITY_TYPE_SESSION);

			raw = (session *) malloc_fast_mem (sizeof (session));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (session));

			//
			// unpack data (in exactly the same order as the data was packed)
			//

         raw->version_number = unpack_int_value (en, INT_TYPE_VERSION_NUMBER);

			unpack_list_root (en, LIST_TYPE_FORCE, &raw->force_root);

			// update_link

			// tour of duty time

			raw->elapsed_time = unpack_float_value (en, FLOAT_TYPE_ELAPSED_TIME);

			raw->start_time = unpack_float_value (en, FLOAT_TYPE_START_TIME);

			// time_of_day_resync

			// time_of_day_acceleration

			// weather radius

			// weather_mode_transitional_period

			// weather_mode_transitional_status

			raw->weather_mode = (weathermodes) unpack_int_value (en, INT_TYPE_WEATHER_MODE);

			// target_weather_mode

			// weather position

			// weather velocity

			raw->day_segment_type = (day_segment_types) unpack_int_value (en, INT_TYPE_DAY_SEGMENT_TYPE);

			raw->population_x_min = unpack_float_value (en, FLOAT_TYPE_POPULATION_X_MIN);
			raw->population_x_max = unpack_float_value (en, FLOAT_TYPE_POPULATION_X_MAX);
			raw->population_z_min = unpack_float_value (en, FLOAT_TYPE_POPULATION_Z_MIN);
			raw->population_z_max = unpack_float_value (en, FLOAT_TYPE_POPULATION_Z_MAX);
		
			raw->campaign_requires_apache_havoc = unpack_int_value (en, INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC);

			// infinite_weapons

			// skip_night_time

			// weather increasing

			set_session_entity (en);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
