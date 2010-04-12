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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TOTAL_3D_RAINDROPS 2048

#define RAINDROPS_AREA_HEIGHT 80
#define RAINDROPS_AREA_WIDTH 160
#define RAINDROPS_AREA_DEPTH 512

#define SNOWDROPS_AREA_HEIGHT 80
#define SNOWDROPS_AREA_WIDTH 160
#define SNOWDROPS_AREA_DEPTH 512

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RAINDROP_INFORMATION
{

	vec3d
		current_position;

	union
	{

		vec3d
			predicted_position;

		float
			relative_speed;
	};

	raindrop_types
		type;
};

typedef struct RAINDROP_INFORMATION raindrop_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RAINDROP_SETTINGS
{

	int
		number_of_raindrops,
		number_of_snowdrops;
};

typedef struct RAINDROP_SETTINGS raindrop_settings;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static raindrop_settings
	number_of_weather_particles_allowed[WEATHERMODE_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	time_rain_last_updated,
	rain_3d_delta_time,
	rain_3d_wind_speed,
	rain_3d_speed,
	snow_particle_radius;

static vec3d
	rain_3d_wind_direction;

static raindrop_information
	rain_3d_drops[TOTAL_3D_RAINDROPS];

static int
	rain_3d_raindrops_valid,
	rain_3d_snowdrops_valid;

static screen
	*snow_3d_texture;

static int
	special_snow_flag = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void transform_3d_rain ( void );

static void transform_3d_snow ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_rain ( float start_time, vec3d *start_position )
{

	int
		count;

	time_rain_last_updated = start_time;

	snow_particle_radius = 0.3f;

	//
	// Set the number of raindrops allowed per weathermode.
	//

	number_of_weather_particles_allowed[WEATHERMODE_DRY].number_of_raindrops = 0;
	number_of_weather_particles_allowed[WEATHERMODE_DRY].number_of_snowdrops = 0;

	number_of_weather_particles_allowed[WEATHERMODE_LIGHT_RAIN].number_of_raindrops = TOTAL_3D_RAINDROPS/2;
	number_of_weather_particles_allowed[WEATHERMODE_LIGHT_RAIN].number_of_snowdrops = 0;

	number_of_weather_particles_allowed[WEATHERMODE_HEAVY_RAIN].number_of_raindrops = TOTAL_3D_RAINDROPS;
	number_of_weather_particles_allowed[WEATHERMODE_HEAVY_RAIN].number_of_snowdrops = 0;

	number_of_weather_particles_allowed[WEATHERMODE_SNOW].number_of_raindrops = 0;
	number_of_weather_particles_allowed[WEATHERMODE_SNOW].number_of_snowdrops = TOTAL_3D_RAINDROPS/2;

	//
	// Initialise all the raindrops to be invalid.
	//

	rain_3d_raindrops_valid = 0;
	rain_3d_snowdrops_valid = 0;

	for ( count = 0; count < TOTAL_3D_RAINDROPS; count++ )
	{

		rain_3d_drops[count].type = RAINDROP_INVALID;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_snow_texture ( int snow_texture_index )
{

	snow_3d_texture = system_textures[snow_texture_index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_rain_speed ( float speed )
{

	rain_3d_speed = speed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_rain_special_snow_flag ( int flag )
{

	special_snow_flag = flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_rain_wind ( vec3d *direction, float speed )
{

	//
	// direction *must* be a unit vector - or expect the rain to move faster/slower than it should
	//

	rain_3d_wind_direction = *direction;

	rain_3d_wind_speed = speed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_3d_rain ( env_3d *env, float time, matrix3x3 view_attitude )
{

	int
		start_raindrop_number,
		end_raindrop_number,
		total_raindrop_number,

		start_snowdrop_number,
		end_snowdrop_number,
		total_snowdrop_number,

		creation_allowed,
		count;

	float
		displacement_magnitude,
		snow_displacement_magnitude,
		snow_fall_displacement,
		weather_t;

	vec3d
		distance_moved,
		rain_displacement,
		snow_drift_displacement,
		rain_streak_displacement,
		creation_vector;

	//
	// Calculate how many rain drops we should have. This is a linear scale, from 0, to TOTAL_3D_RAINDROPS.
	//  DRY = 0
	//  LIGHT_RAIN = TOTAL_3D_RAINDROPS / 2
	//  HEAVY_RAIN = TOTAL_3D_RAINDROPS
	//

	if ( visual_3d_vp )
	{
	
		if ( visual_3d_vp->position.y > get_cloud_3d_base_height () )
		{
	
			creation_allowed = FALSE;
		}
		else
		{
	
			creation_allowed = TRUE;
		}
	}
	else
	{

		creation_allowed = FALSE;
	}

	start_raindrop_number = number_of_weather_particles_allowed[env->weathermode].number_of_raindrops;
	start_snowdrop_number = number_of_weather_particles_allowed[env->weathermode].number_of_snowdrops;

	end_raindrop_number = number_of_weather_particles_allowed[env->target_weathermode].number_of_raindrops;
	end_snowdrop_number = number_of_weather_particles_allowed[env->target_weathermode].number_of_snowdrops;

	weather_t = env->weather_targetdistance;

	if ( weather_t == 0 )
	{

		total_raindrop_number = start_raindrop_number;
		total_snowdrop_number = start_snowdrop_number;
	}
	else if ( weather_t == 1 )
	{

		total_raindrop_number = end_raindrop_number;
		total_snowdrop_number = end_snowdrop_number;
	}
	else
	{

		total_raindrop_number = start_raindrop_number + ( ( ( float ) ( end_raindrop_number - start_raindrop_number ) ) * weather_t );
		total_snowdrop_number = start_snowdrop_number + ( ( ( float ) ( end_snowdrop_number - start_snowdrop_number ) ) * weather_t );
	}

	//
	// Special snow flag stuff
	//

	if ( special_snow_flag )
	{
/*
		if ( visual_3d_vp )
		{

			int
				x,
				z;

			int
				near_snow;

			float
				old_rain_total;

			near_snow = FALSE;

			for ( z = -1; z <= 1; z++ )
			{
	
				for ( x = -1; x <= 1; x++ )
				{

					float
						x_pos,
						z_pos;

					x_pos = visual_3d_vp->x + x * TERRAIN_3D_SECTOR_SIDE_LENGTH;
					z_pos = visual_3d_vp->z + z * TERRAIN_3D_SECTOR_SIDE_LENGTH;

					x_pos = bound ( x_pos, terrain_3d_min_map_x, terrain_3d_max_map_x );
					z_pos = bound ( z_pos, terrain_3d_min_map_z, terrain_3d_max_map_z );

					get_terrain_3d_types_in_sector ( x_pos, z_pos );

					if ( terrain_types_in_sector[TERRAIN_TYPE_ALTERED_LAND3] )
					{

						near_snow = TRUE;
					}
				}
			}

			if ( near_snow )
			{
	
				old_rain_total = total_raindrop_number;
	
				total_raindrop_number = old_rain_total * 0.0;
				total_snowdrop_number = old_rain_total * 1.0;
			}
		}
		*/
	}

	//
	//
	//

	rain_3d_delta_time = time - time_rain_last_updated;

	time_rain_last_updated = time;

	//
	// Calculate the distance moved by each raindrop.
	//

	distance_moved.x = rain_3d_wind_direction.x * rain_3d_wind_speed * rain_3d_delta_time;
	distance_moved.y = rain_3d_wind_direction.y * rain_3d_wind_speed * rain_3d_delta_time;
	distance_moved.z = rain_3d_wind_direction.z * rain_3d_wind_speed * rain_3d_delta_time;

	rain_displacement.x = distance_moved.x;
	rain_displacement.y = distance_moved.y + ( rain_3d_speed * rain_3d_delta_time );
	rain_displacement.z = distance_moved.z;

	//
	// Calculate the distance moved by each snowdrop.
	//

	snow_drift_displacement.x = distance_moved.x;
	snow_drift_displacement.y = distance_moved.y;
	snow_drift_displacement.z = distance_moved.z;

	snow_fall_displacement = ( rain_3d_speed / 4 ) * rain_3d_delta_time;

	snow_displacement_magnitude = get_3d_vector_magnitude ( &snow_drift_displacement );

	//
	// Calculate the 'streak' effect - this is now NOT framerate related
	//

	rain_streak_displacement = rain_displacement;

	displacement_magnitude = get_3d_vector_magnitude ( &rain_streak_displacement );

	if ( displacement_magnitude != 0 )
	{

		displacement_magnitude = 1.5 / displacement_magnitude;

		rain_streak_displacement.x *= displacement_magnitude;
		rain_streak_displacement.y *= displacement_magnitude;
		rain_streak_displacement.z *= displacement_magnitude;
	}
	else
	{

		//
		// Put artificial streaking in there ( game paused )
		//

		rain_streak_displacement.x = rain_3d_wind_direction.x * rain_3d_wind_speed * 0.05f;
		rain_streak_displacement.y = rain_3d_wind_direction.y * rain_3d_wind_speed * 0.05 + ( rain_3d_speed * 0.05 );
		rain_streak_displacement.z = rain_3d_wind_direction.z * rain_3d_wind_speed * 0.05f;
	
		displacement_magnitude = get_3d_vector_magnitude ( &rain_streak_displacement );
	
		if ( displacement_magnitude != 0 )
		{
	
			displacement_magnitude = 1.5 / displacement_magnitude;
	
			rain_streak_displacement.x *= displacement_magnitude;
			rain_streak_displacement.y *= displacement_magnitude;
			rain_streak_displacement.z *= displacement_magnitude;
		}
	}

	//
	// Remove any raindrops that have strayed out of the area of effect
	//

	creation_vector.x = rain_3d_wind_direction.x * rain_3d_wind_speed * 0.5;
	creation_vector.y = rain_3d_wind_direction.y * rain_3d_wind_speed * 0.5 + ( rain_3d_speed * 0.5 );
	creation_vector.z = rain_3d_wind_direction.z * rain_3d_wind_speed * 0.5;

	normalise_any_3d_vector ( &creation_vector );

	for ( count = 0; count < TOTAL_3D_RAINDROPS; count++ )
	{

		switch ( rain_3d_drops[count].type )
		{

			case RAINDROP_RAIN:
			{

				vec3d
					rel;

				//
				// Update the rain position
				//
			
				rain_3d_drops[count].current_position.x -= rain_displacement.x;
				rain_3d_drops[count].current_position.y -= rain_displacement.y;
				rain_3d_drops[count].current_position.z -= rain_displacement.z;

				rel.x = rain_3d_drops[count].current_position.x - visual_3d_vp->x;
				rel.y = rain_3d_drops[count].current_position.y - visual_3d_vp->y;
				rel.z = rain_3d_drops[count].current_position.z - visual_3d_vp->z;
	
				if (
						( rel.x > RAINDROPS_AREA_WIDTH ) || ( rel.x < ( -RAINDROPS_AREA_WIDTH ) ) ||
						( rel.y > RAINDROPS_AREA_HEIGHT ) || ( rel.y < ( -RAINDROPS_AREA_HEIGHT ) ) ||
						( rel.z > RAINDROPS_AREA_DEPTH ) || ( rel.z < ( -RAINDROPS_AREA_DEPTH ) )
					)
				{
	
	
					rain_3d_raindrops_valid--;
	
					rain_3d_drops[count].type = RAINDROP_INVALID;
				}

				break;
			}

			case RAINDROP_SNOW:
			{

				vec3d
					snow_noise,
					rel;

				float
					relative_speed;

				//
				// Update the rain position
				//

				snow_noise.x = sfrand1 () * rain_3d_delta_time;	//0.1	;//snow_displacement_magnitude;
				snow_noise.y = sfrand1 () * rain_3d_delta_time;	//0.1	;//snow_displacement_magnitude;
				snow_noise.z = sfrand1 () * rain_3d_delta_time;	//0.1	;//snow_displacement_magnitude;

				relative_speed = rain_3d_drops[count].relative_speed;
			
				rain_3d_drops[count].current_position.x -= ( snow_drift_displacement.x + snow_noise.x );
				rain_3d_drops[count].current_position.y -= ( snow_drift_displacement.y );
				rain_3d_drops[count].current_position.z -= ( snow_drift_displacement.z + snow_noise.x );

				rain_3d_drops[count].current_position.y -= ( snow_fall_displacement * relative_speed );

				rel.x = rain_3d_drops[count].current_position.x - visual_3d_vp->x;
				rel.y = rain_3d_drops[count].current_position.y - visual_3d_vp->y;
				rel.z = rain_3d_drops[count].current_position.z - visual_3d_vp->z;
	
				if (
						( rel.x > SNOWDROPS_AREA_WIDTH ) || ( rel.x < ( -SNOWDROPS_AREA_WIDTH ) ) ||
						( rel.y > SNOWDROPS_AREA_HEIGHT ) || ( rel.y < ( -SNOWDROPS_AREA_HEIGHT ) ) ||
						( rel.z > SNOWDROPS_AREA_DEPTH ) || ( rel.z < ( -SNOWDROPS_AREA_DEPTH ) )
					)
				{
	
					rain_3d_snowdrops_valid--;

					rain_3d_drops[count].type = RAINDROP_INVALID;
				}

				break;
			}
		}

		if ( ( rain_3d_drops[count].type == RAINDROP_INVALID ) && ( creation_allowed ) )
		{

			if ( rain_3d_raindrops_valid < total_raindrop_number )
			{
	
				float
					x,
					y,
					z,
					creation_distance;
	
				//
				// Generate a new rain drop randomly
				//
	
				z = ( ( frand1 () * 0.8 ) + 0.2 ) * ( RAINDROPS_AREA_DEPTH / 5 );
				x = sfrand1 () * ( RAINDROPS_AREA_WIDTH / 5 );
				y = sfrand1 () * ( RAINDROPS_AREA_HEIGHT / 5 );

				x *= z / 50;
				y *= z / 50;
	
				//
				// Now project along the motion vector
				//
	
				creation_distance = frand1 () * 8;
				x += creation_vector.x * creation_distance;
				y += creation_vector.y * creation_distance;
				z += creation_vector.z * creation_distance;
	
				//
				// Rotate this back into the view coordinate system
				//
	
				rain_3d_drops[count].current_position.x = x * view_attitude[0][0] + y * view_attitude[1][0] + z * view_attitude[2][0];
				rain_3d_drops[count].current_position.y = x * view_attitude[0][1] + y * view_attitude[1][1] + z * view_attitude[2][1];
				rain_3d_drops[count].current_position.z = x * view_attitude[0][2] + y * view_attitude[1][2] + z * view_attitude[2][2];

				rain_3d_drops[count].current_position.x += visual_3d_vp->x;
				rain_3d_drops[count].current_position.y += visual_3d_vp->y;
				rain_3d_drops[count].current_position.z += visual_3d_vp->z;

				rain_3d_drops[count].type = RAINDROP_RAIN;
	
				rain_3d_raindrops_valid++;
			}
			else if ( rain_3d_snowdrops_valid < total_snowdrop_number )
			{
	
				float
					x,
					y,
					z,
					creation_distance;

				//
				// Generate a new snowdrop
				//

				z = ( ( frand1 () * 0.8 ) + 0.2 ) * ( SNOWDROPS_AREA_DEPTH / 5 );
				x = sfrand1 () * ( SNOWDROPS_AREA_WIDTH / 5 );
				y = sfrand1 () * ( SNOWDROPS_AREA_HEIGHT / 5 );
	
				x *= z / 50;
				y *= z / 50;
	
				//
				// Now project along the motion vector
				//
	
				creation_distance = frand1 () * 8;
				x += creation_vector.x * creation_distance;
				y += creation_vector.y * creation_distance;
				z += creation_vector.z * creation_distance;
	
				//
				// Rotate this back into the view coordinate system
				//
	
				rain_3d_drops[count].current_position.x = x * view_attitude[0][0] + y * view_attitude[1][0] + z * view_attitude[2][0];
				rain_3d_drops[count].current_position.y = x * view_attitude[0][1] + y * view_attitude[1][1] + z * view_attitude[2][1];
				rain_3d_drops[count].current_position.z = x * view_attitude[0][2] + y * view_attitude[1][2] + z * view_attitude[2][2];
	
				rain_3d_drops[count].current_position.x += visual_3d_vp->x;
				rain_3d_drops[count].current_position.y += visual_3d_vp->y;
				rain_3d_drops[count].current_position.z += visual_3d_vp->z;

				rain_3d_drops[count].relative_speed = ( frand1() * 0.5 ) + 0.5;
	
				rain_3d_drops[count].type = RAINDROP_SNOW;
	
				rain_3d_snowdrops_valid++;
			}
		}
	}

	//
	// Now calculate the predicted positions for rendering
	//

	for ( count = 0; count < TOTAL_3D_RAINDROPS; count++ )
	{

		if ( rain_3d_drops[count].type == RAINDROP_RAIN )
		{
	
			rain_3d_drops[count].predicted_position.x = rain_3d_drops[count].current_position.x - rain_streak_displacement.x;
			rain_3d_drops[count].predicted_position.y = rain_3d_drops[count].current_position.y - rain_streak_displacement.y;
			rain_3d_drops[count].predicted_position.z = rain_3d_drops[count].current_position.z - rain_streak_displacement.z;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void invalidate_3d_rain ( void )
{

	int
		count;

	//
	// Go through tagging all the snow/raindrops as not in use
	//

	for ( count = 0; count < TOTAL_3D_RAINDROPS; count++ )
	{

		rain_3d_drops[count].type = RAINDROP_INVALID;
	}

	rain_3d_raindrops_valid = 0;

	rain_3d_snowdrops_valid = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_rain ( void )
{

	point_3d_plain_reference
		rain_point_references[2];

	int
		count,
		outcode;

	//
	// Calculate the rotation matrix, to transform rain drops relative to the view.
	//

	rotation_3d[0][0] = ( visual_3d_vp->xv.x );
	rotation_3d[0][1] = ( visual_3d_vp->yv.x );
	rotation_3d[0][2] = ( visual_3d_vp->zv.x );

	rotation_3d[1][0] = ( visual_3d_vp->xv.y );
	rotation_3d[1][1] = ( visual_3d_vp->yv.y );
	rotation_3d[1][2] = ( visual_3d_vp->zv.y );

	rotation_3d[2][0] = ( visual_3d_vp->xv.z );
	rotation_3d[2][1] = ( visual_3d_vp->yv.z );
	rotation_3d[2][2] = ( visual_3d_vp->zv.z );

	if ( rain_3d_raindrops_valid )
	{

		int
			number_of_valid_raindrops;

		float
			rain_intensity;

		int
			rain_whiteness;


		rain_intensity = ambient_3d_light.colour.red * 0.3 + ambient_3d_light.colour.green * 0.59 * ambient_3d_light.colour.blue * 0.11;

		rain_intensity *= 4;

		rain_intensity *= 255;

		rain_intensity = bound ( rain_intensity, 0, 255 );

		rain_whiteness = rain_intensity;

		//
		// Remeber the number of valid raindrops
		//

		number_of_valid_raindrops = rain_3d_raindrops_valid;

		//
		// Rotate the rain - putting the results in transformed_3d_points
		//
	
		transform_3d_rain ();
	
		//
		// Go through pairing up the transformed points, drawing lines between them.
		//
	
		rain_point_references[0].point = 0;
		rain_point_references[1].point = 1;
	
		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, TRUE, FALSE );

		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_GOURAUD );

		set_d3d_texture ( 0, NULL );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

		for ( count = 0; count < number_of_valid_raindrops; count++ )
		{
	
			vertex
				*line;
	
			//
			// Construct the 3d line
			//
	
			clip_3d_coord = 0;
	
			line = construct_3d_line ( rain_point_references, ( count * 2 ), &outcode );

			if ( line )
			{

				line->red = rain_whiteness;
				line->green = rain_whiteness;
				line->blue = rain_whiteness;
				line->alpha = 32;

				line->next_vertex->red = rain_whiteness;
				line->next_vertex->green = rain_whiteness;
				line->next_vertex->blue = rain_whiteness;
				line->next_vertex->alpha = 192;
		
				if ( outcode & CLIP_HITHER )
				{
			
					line = hither_clip_3d_polygon ( line, &outcode );
				}
	
				if ( line )
				{
		
					if ( outcode )
					{
				
						line = clip_3d_polygon ( line, outcode );
					}
	
					if ( line )
					{
	
						vertex
							*point1,
							*point2;
					
						LPD3DTLVERTEX
							vertices,
							vptr;

						vertices = get_d3d_line_vertices_points_address ();
					
						vptr = vertices;
					
						point2 = line;
					
						point1 = line->next_vertex;
					
						*( ( int * ) &vptr->sx ) = *( ( int * ) &point1->i );
						*( ( int * ) &vptr->sy ) = *( ( int * ) &point1->j );
						*( ( int * ) &vptr->rhw ) = *( ( int * ) &point1->q );
						vptr->sz = ( point1->q * zbuffer_factor ) + zbuffer_constant;
					
						vptr->color = point1->colour;
						vptr->specular = d3d_fog_intensity;
					
						vptr++;
					
						*( ( int * ) &vptr->sx ) = *( ( int * ) &point2->i );
						*( ( int * ) &vptr->sy ) = *( ( int * ) &point2->j );
						*( ( int * ) &vptr->rhw ) = *( ( int * ) &point2->q );
						vptr->sz = ( point2->q * zbuffer_factor ) + zbuffer_constant;
					
						vptr->color = point2->colour;
						vptr->specular = d3d_fog_intensity;
					
						draw_line_primitive ( vertices );
					}
				}
			}
		}

		flush_line_primitives ();

		set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
	}

	if ( rain_3d_snowdrops_valid )
	{

		real_colour
			snow_specular,
			snow_colour;
	
		//
		// Rotate the rain - putting the results in transformed_3d_points
		//
	
		transform_3d_snow ();

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );

		//
		// First, set the snow texture
		//

		set_d3d_texture ( 0, snow_3d_texture );

		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
		set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
		set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		snow_colour.red = 255;
		snow_colour.green = 255;
		snow_colour.blue = 255;
		snow_colour.alpha = 255;

		snow_specular.colour = d3d_fog_intensity;
	
		for ( count = 0; count < rain_3d_snowdrops_valid; count++ )
		{

			vertex
				*poly,
				snow_quad[4];

			if ( !transformed_3d_points[count].outcode )
			{

				float
					width,
					height;

				int
					outcode;

				//
				// We know the raindrop is on the screen ( to a certain extent )
				//

				width = active_3d_environment->screen_i_scale * snow_particle_radius * transformed_3d_points[count].q;
				height = active_3d_environment->screen_j_scale * snow_particle_radius * transformed_3d_points[count].q;

				snow_quad[0].q = transformed_3d_points[count].q;
				snow_quad[0].i = transformed_3d_points[count].i - ( width / 2 );
				snow_quad[0].j = transformed_3d_points[count].j - ( height / 2 );
				snow_quad[0].u = 0;
				snow_quad[0].v = 0;
				snow_quad[0].outcode = generate_3d_outcode ( snow_quad[0].i, snow_quad[0].j );
				snow_quad[0].next_vertex = &snow_quad[1];

				snow_quad[1].q = transformed_3d_points[count].q;
				snow_quad[1].i = transformed_3d_points[count].i + ( width / 2 );
				snow_quad[1].j = transformed_3d_points[count].j - ( height / 2 );
				snow_quad[1].u = 1;
				snow_quad[1].v = 0;
				snow_quad[1].outcode = generate_3d_outcode ( snow_quad[1].i, snow_quad[1].j );
				snow_quad[1].next_vertex = &snow_quad[2];

				snow_quad[2].q = transformed_3d_points[count].q;
				snow_quad[2].i = transformed_3d_points[count].i + ( width / 2 );
				snow_quad[2].j = transformed_3d_points[count].j + ( height / 2 );
				snow_quad[2].u = 1;
				snow_quad[2].v = 1;
				snow_quad[2].outcode = generate_3d_outcode ( snow_quad[2].i, snow_quad[2].j );
				snow_quad[2].next_vertex = &snow_quad[3];

				snow_quad[3].q = transformed_3d_points[count].q;
				snow_quad[3].i = transformed_3d_points[count].i - ( width / 2 );
				snow_quad[3].j = transformed_3d_points[count].j + ( height / 2 );
				snow_quad[3].u = 0;
				snow_quad[3].v = 1;
				snow_quad[3].outcode = generate_3d_outcode ( snow_quad[3].i, snow_quad[3].j );
				snow_quad[3].next_vertex = NULL;

				outcode = snow_quad[0].outcode;
				outcode |= snow_quad[1].outcode;
				outcode |= snow_quad[2].outcode;
				outcode |= snow_quad[3].outcode;

				poly = snow_quad;

				if ( outcode )
				{

					clip_3d_coord = 0;

					poly = clip_3d_polygon ( poly, outcode );
				}

				if ( poly )
				{

					draw_wbuffered_flat_shaded_textured_polygon ( poly, snow_colour, snow_specular );
				}
			}
		}

		set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, TRUE, TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_rain ( void )
{

	int
		count;

	vertex
		*result_points;

	float
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;


	//
	// Go through rotating/translating the rain positions, current and predicted, and draw lines accordingly.
	//

	//
	// We only need the fpu to be in single precision mode
	//

//	set_fpu_precision_mode_single ();

	result_points = transformed_3d_points;

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[0][2] = rotation_3d[0][2];

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = rotation_3d[1][2];

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[2][2] = rotation_3d[2][2];

	for ( count = 0; count < TOTAL_3D_RAINDROPS; count++ )
	{

		float
			x,
			y,
			z;

		vec3d
			*points;

		if ( rain_3d_drops[count].type == RAINDROP_RAIN )
		{

			vec3d
				rel;

			points = &rain_3d_drops[count].current_position;

			rel.x = points->x - visual_3d_vp->x;
			rel.y = points->y - visual_3d_vp->y;
			rel.z = points->z - visual_3d_vp->z;
	
			z = rel.x * scaled_rotation[0][2] + rel.y * scaled_rotation[1][2] + rel.z * scaled_rotation[2][2];
			x = rel.x * scaled_rotation[0][0] + rel.y * scaled_rotation[1][0] + rel.z * scaled_rotation[2][0];
			y = rel.x * scaled_rotation[0][1] + rel.y * scaled_rotation[1][1] + rel.z * scaled_rotation[2][1];
	
			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{
	
				float
					q,
					i,
					j;
	
				result_points->x = x;
				result_points->y = y;
				result_points->z = z;
	
				q = 1.0 / z;
				i = ( x * q );
				j = ( y * q );
	
				result_points->j = active_3d_environment->y_origin - j;
				result_points->i = active_3d_environment->x_origin + i;
	
				result_points->q = q;
	
				oxmax = active_viewport.x_max - result_points->i;
				oxmin = result_points->i - active_viewport.x_min;
				oymax = active_viewport.y_max - result_points->j;
				oymin = result_points->j - active_viewport.y_min;
			
				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );
			
				result_points->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
			}
			else
			{
	
				result_points->outcode = CLIP_HITHER;
				result_points->z = z;
				result_points->x = x;
				result_points->y = y;

				//
				// Mark this raindrop as invalid now
				//

				rain_3d_drops[count].type = RAINDROP_INVALID;

				rain_3d_raindrops_valid--;
			}
	
			result_points++;
	
			points = &rain_3d_drops[count].predicted_position;
	
			rel.x = points->x - visual_3d_vp->x;
			rel.y = points->y - visual_3d_vp->y;
			rel.z = points->z - visual_3d_vp->z;

			z = rel.x * scaled_rotation[0][2] + rel.y * scaled_rotation[1][2] + rel.z * scaled_rotation[2][2];
			x = rel.x * scaled_rotation[0][0] + rel.y * scaled_rotation[1][0] + rel.z * scaled_rotation[2][0];
			y = rel.x * scaled_rotation[0][1] + rel.y * scaled_rotation[1][1] + rel.z * scaled_rotation[2][1];

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{
	
				float
					q,
					i,
					j;
	
				result_points->x = x;
				result_points->y = y;
				result_points->z = z;
	
				q = 1.0 / z;
				i = ( x * q );
				j = ( y * q );
	
				result_points->j = active_3d_environment->y_origin - j + 1;
				result_points->i = active_3d_environment->x_origin + i + 1;
	
				result_points->q = q;
	
				oxmax = active_viewport.x_max - result_points->i;
				oxmin = result_points->i - active_viewport.x_min;
				oymax = active_viewport.y_max - result_points->j;
				oymin = result_points->j - active_viewport.y_min;
			
				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );
			
				result_points->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
			}
			else
			{

				result_points->outcode = CLIP_HITHER;
				result_points->z = z;
				result_points->x = x;
				result_points->y = y;
			}
	
			result_points++;
		}
	}

//	set_fpu_precision_mode_double ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_snow ( void )
{

	int
		count;

	vertex
		*result_points;

	float
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	vec3d
		rel;


	//
	// Go through rotating/translating the rain positions, current and predicted, and draw lines accordingly.
	//

	//
	// We only need the fpu to be in single precision mode
	//

//	set_fpu_precision_mode_single ();

	result_points = transformed_3d_points;

	scaled_rotation[0][0] = rotation_3d[0][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[0][1] = rotation_3d[0][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[0][2] = rotation_3d[0][2];

	scaled_rotation[1][0] = rotation_3d[1][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[1][1] = rotation_3d[1][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[1][2] = rotation_3d[1][2];

	scaled_rotation[2][0] = rotation_3d[2][0] * active_3d_environment->screen_i_scale;
	scaled_rotation[2][1] = rotation_3d[2][1] * active_3d_environment->screen_j_scale;
	scaled_rotation[2][2] = rotation_3d[2][2];

	for ( count = 0; count < TOTAL_3D_RAINDROPS; count++ )
	{

		float
			x,
			y,
			z;

		vec3d
			*points;

		if ( rain_3d_drops[count].type == RAINDROP_SNOW )
		{
	
			points = &rain_3d_drops[count].current_position;

			rel.x = points->x - visual_3d_vp->x;
			rel.y = points->y - visual_3d_vp->y;
			rel.z = points->z - visual_3d_vp->z;

			z = rel.x * scaled_rotation[0][2] + rel.y * scaled_rotation[1][2] + rel.z * scaled_rotation[2][2];
			x = rel.x * scaled_rotation[0][0] + rel.y * scaled_rotation[1][0] + rel.z * scaled_rotation[2][0];
			y = rel.x * scaled_rotation[0][1] + rel.y * scaled_rotation[1][1] + rel.z * scaled_rotation[2][1];

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{
	
				float
					q,
					i,
					j;
	
				result_points->x = x;
				result_points->y = y;
				result_points->z = z;
	
				q = 1.0 / z;
				i = ( x * q );
				j = ( y * q );
	
				result_points->j = active_3d_environment->y_origin - j;
				result_points->i = active_3d_environment->x_origin + i;
	
				result_points->q = q;
	
				oxmax = active_viewport.x_max - result_points->i;
				oxmin = result_points->i - active_viewport.x_min;
				oymax = active_viewport.y_max - result_points->j;
				oymin = result_points->j - active_viewport.y_min;
			
				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );
			
				result_points->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				result_points++;
			}
			else
			{
	
				//
				// Tag this snowdrop as invalid now
				//

				rain_3d_drops[count].type = RAINDROP_INVALID;

				rain_3d_snowdrops_valid--;
			}
		}
	}

//	set_fpu_precision_mode_double ();
}
