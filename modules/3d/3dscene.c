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



#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "3d.h"

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	allow_perturbed_bounce = FALSE,
	allow_bounce_light = FALSE,
	allow_cloud_light = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int begin_3d_scene ( void )
{

	int
		scene_valid;

	reset_sub_object_search_statistics ();

	reset_3d_polylines ();

	reset_smoke_trail_rendering_information ();

	reset_translucent_buffering_system ();

	scene_valid = d3d_begin_scene ();

	//
	// Clear performance stats
	//

	reset_3d_transformation_stats ();

	reset_d3d_state_performance ();

	//
	// Clear clipping stats
	//

	reset_clip_statistics ();

	//
	// Reset vertex caches
	//

	vertex_cache_size = 3;

	set_vertex_cache_size ( vertex_cache_size );

	reset_vertex_cache_data ();

	//
	// Setup the object sorting bins
	//

	clear_3d_scene_objects ();

	//
	// Remove all lights from the scene
	//

	reset_light_3d_sources_in_3d_scene ();

	//
	// Setup the lighting conditions
	//

	if ( active_3d_environment )
	{

		//
		// There are circumstances when we don't need an environment ( terrain 3d map renderer )
		//

		setup_environment_lights_in_scene ( active_3d_environment );
	}

	//
	// Clear any temporary 3d instances - in case any have been created after the last end_scene call
	//

	clear_temporary_3d_instances ();

	//
	// Set the fog mode renderstates
	//

	set_d3d_fog_renderstates ();

	//
	// Set the visual effects flags ( for infrared stuff )
	//

	if (( active_3d_environment ) && ( active_3d_environment->render_filter == RENDER_INFRARED ) )
	{

		textured_object_rendering_enabled = FALSE;

		terrain_object_rendering_enabled = TRUE;
	}
	else
	{

		textured_object_rendering_enabled = TRUE;

		terrain_object_rendering_enabled = TRUE;
	}

	//
	// Initialise the terrain performance figures
	//
/*
	total_number_of_terrain_points = 0;

	total_number_of_terrain_points_transformed = 0;

	terrain_3d_faces_considered = 0;

	terrain_3d_faces_outcoded = 0;

	terrain_3d_faces_constructed = 0;

	terrain_3d_faces_rejected = 0;

	terrain_3d_faces_hither_clipped = 0;

	terrain_3d_faces_screen_clipped = 0;

	terrain_3d_sectors_inserted = 0;

	terrain_3d_sectors_totally_visible = 0;

	terrain_3d_sectors_trivially_culled = 0;

	terrain_3d_sectors_complex_culled = 0;
*/
	number_of_objects_in_3d_scene = 0;

	number_of_sprites_in_3d_scene = 0;

	if ( scene_valid )
	{

		set_d3d_int_state ( D3DRS_ZENABLE, TRUE );
		set_d3d_int_state ( D3DRS_ZWRITEENABLE, TRUE );
		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );

		set_d3d_int_state ( D3DRS_ALPHATESTENABLE, FALSE );
		set_d3d_int_state ( D3DRS_ALPHABLENDENABLE, FALSE );
		set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}

	return ( scene_valid );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void end_3d_scene ( void )
{

	//
	// Finally, end the scene.
	//

	d3d_end_scene ();

	//
	// Report on the state performance
	//

	report_d3d_state_performance ();

	//
	// Report on the clip performance
	//

	report_clip_statistics ();

	//
	// Report vertex cache performance
	//

	report_vertex_cache_statistics ();

	//
	// Clear any temporary 3d instances
	//

	clear_temporary_3d_instances ();

	//
	// Finalise the performance figures for the 3d visual.
	//
/*
	final_total_number_of_terrain_points = total_number_of_terrain_points;

	final_total_number_of_terrain_points_transformed = total_number_of_terrain_points_transformed;

	final_terrain_3d_faces_considered = terrain_3d_faces_considered;

	final_terrain_3d_faces_outcoded = terrain_3d_faces_outcoded;

	final_terrain_3d_faces_constructed = terrain_3d_faces_constructed;

	final_terrain_3d_faces_rejected = terrain_3d_faces_rejected;

	final_terrain_3d_faces_hither_clipped = terrain_3d_faces_hither_clipped;

	final_terrain_3d_faces_screen_clipped = terrain_3d_faces_screen_clipped;

	final_terrain_3d_sectors_inserted = terrain_3d_sectors_inserted;

	final_terrain_3d_sectors_totally_visible = terrain_3d_sectors_totally_visible;

	final_terrain_3d_sectors_trivially_culled = terrain_3d_sectors_trivially_culled;

	final_terrain_3d_sectors_complex_culled = terrain_3d_sectors_complex_culled;
*/

	final_number_of_objects_in_3d_scene = number_of_objects_in_3d_scene;

	final_number_of_sprites_in_3d_scene = number_of_sprites_in_3d_scene;

	report_sub_object_search_statistics ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static light_3d_source
	spare_3d_system_lights[8];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup_environment_lights_in_scene ( env_3d *env )
{

	ASSERT ( env );

	//
	// Remove all lights from the scene
	//

	reset_light_3d_sources_in_3d_scene ();

	if ( env->lightmode == LIGHTMODE_AUTOMATIC_LIGHT )
	{

		//
		// Set up the sun light
		//

		if ( env->sun_light.main_light )
		{

			light_3d_source
				*list;

			float
				angle;

			int
				light_count,
				light_index;

			vec3d
				normal_vector,
				rotation_vector,
				reflection_vector;

			matrix3x3
				m;

			insert_main_3d_light_into_3d_scene ( &env->sun_3d_light );

			//
			// Add a couple of filler lights
			//

			normal_vector.x = 0;
			normal_vector.y = 1;
			normal_vector.z = 0;

			angle = normal_vector.x * env->sun_3d_light.light_direction.x +
						normal_vector.y * env->sun_3d_light.light_direction.y +
						normal_vector.z * env->sun_3d_light.light_direction.z;

			angle = acos ( angle );

			get_3d_vector_cross_product ( &rotation_vector, &env->sun_3d_light.light_direction, &normal_vector );

			angle = bound ( angle, -PI/8, PI/8 );

			if ( !allow_perturbed_bounce )
			{

				angle = 0;
			}

			get_arbitrary_rotation_matrix ( m, &rotation_vector, angle );

			multiply_matrix3x3_vec3d ( &reflection_vector, m, &normal_vector );

			light_index = 0;

			if ( allow_bounce_light )
			{

				spare_3d_system_lights[light_index].light_direction.x = -reflection_vector.x;
				spare_3d_system_lights[light_index].light_direction.y = -reflection_vector.y;
				spare_3d_system_lights[light_index].light_direction.z = -reflection_vector.z;

				spare_3d_system_lights[light_index].colour.red = env->sun_3d_light.colour.red / 5;
				spare_3d_system_lights[light_index].colour.green = env->sun_3d_light.colour.green / 5;
				spare_3d_system_lights[light_index].colour.blue = env->sun_3d_light.colour.blue / 5;
				spare_3d_system_lights[light_index].intensity = env->sun_3d_light.intensity / 5;

				spare_3d_system_lights[light_index].type = LIGHT_3D_TYPE_DIRECTIONAL;

				light_index++;
			}

			if ( allow_cloud_light )
			{

				spare_3d_system_lights[light_index].light_direction.x = 0.0;
				spare_3d_system_lights[light_index].light_direction.y = 1.0;
				spare_3d_system_lights[light_index].light_direction.z = 0.0;

				spare_3d_system_lights[light_index].colour.red = env->sun_3d_light.colour.red / 10;
				spare_3d_system_lights[light_index].colour.green = env->sun_3d_light.colour.green / 10;
				spare_3d_system_lights[light_index].colour.blue = env->sun_3d_light.colour.blue / 10;
				spare_3d_system_lights[light_index].intensity = env->sun_3d_light.intensity / 10;

				spare_3d_system_lights[light_index].type = LIGHT_3D_TYPE_DIRECTIONAL;

				light_index++;
			}

			for ( light_count = 0; light_count < light_index; light_count++ )
			{

				list = current_3d_lights;

				if ( list )
				{

					while ( list->succ )
					{

						list = list->succ;
					}
				}

				if ( list )
				{

					list->succ = &spare_3d_system_lights[light_count];
				}
				else
				{

					current_3d_lights = &spare_3d_system_lights[0];
				}

				spare_3d_system_lights[light_count].succ = NULL;	//&spare_3d_system_lights[1];
			}
		}

		//
		// Set up the moon light
		//

		if ( env->moon_light.main_light )
		{

			insert_main_3d_light_into_3d_scene ( &env->moon_3d_light );
		}
	}
	else
	{

		insert_main_3d_light_into_3d_scene ( &env->main_3d_light );
	}

	//
	// Add secondary lights into the list
	//

	if ( env->secondary_light_sources )
	{

		light_3d_source
			*list;

		list = current_3d_lights;

		if ( list )
		{

			while ( list->succ )
			{

				list = list->succ;
			}
		}

		if ( list )
		{

			list->succ = env->secondary_light_sources;
		}
		else
		{

			current_3d_lights = env->secondary_light_sources;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
