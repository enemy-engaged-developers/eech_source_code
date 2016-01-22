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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAXIMUM_SHADOW_DISTANCE 650.0

#define MAX_SHADOW_VIEW_DISTANCE 650.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	translucent_3d_shadows = TRUE,
	detailed_3d_shadows = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void transform_3d_object_shadow ( object_3d *object,
															vec3d *scale,
															viewpoint *vp,
															vec3d *pos,
															vec3d *terrain_normal,
															vec3d *projection_direction,
															double projection_constant,
															double projection_factor, int points_base );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_shadows ( void )
{

	set_3d_shadows_detailed ( detailed_3d_shadows );

	set_3d_shadows_translucent ( translucent_3d_shadows );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_shadows_detailed ( int detailed )
{

	detailed_3d_shadows = detailed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_shadows_translucent ( int translucent )
{

	translucent_3d_shadows = translucent;

	if ( translucent_3d_shadows )
	{

		set_d3d_shadow_zbias ( POLYGON_ZDISTANCE_ELEVATED_BIAS );
	}
	else
	{

		set_d3d_shadow_zbias ( POLYGON_ZDISTANCE_MINIMAL_ELEVATED_BIAS );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_shadows_translucent ( void )
{

	return ( translucent_3d_shadows );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_object_shadow ( object_3d_instance *obj )
{
	int
		object_number,
		draw_sub_objects,
		count;

	object_3d_face
		*faces;

	viewpoint
		real_object_position;

	light_3d_source
		*prev_light,
		*light_ptr,
		*light;

	vec3d
		*pos,
		shadow_world_position,
		terrain_normal,
		current_sun_object_view_vector,
		current_scaled_sun_object_view_vector;

	float
		shadow_intensity;

	double
		projection_factor,
		projection_constant;

	if ( current_3d_sun->light_direction.y < 0.1 )
	{
		return;
	}

	//
	// Store the object's position now, and restore it after drawing the shadow.
	//

	real_object_position = obj->vp;

	//
	// First, find the position of the shadow on the ground.
	//
	//  Take the height of the ground directly below the 3d object, and project from the sun down to that height.
	//   This does lead to some errors, but hopefully not noticable.
	//

	{
		float
			light_angle,
			light_intensity,
			ambient_intensity,
			ground_height,
			constant,
			scalar_distance,
			object_dissolve,
			view_distance;

		vec3d
			vector_distance,
			view_vector;

		if ( !position_on_3d_terrain ( real_object_position.x, real_object_position.z ) )
		{
			return;
		}

		ground_height = get_3d_terrain_elevation ( real_object_position.x, real_object_position.z );

		//
		// Strike a vector from object to the ground, with the same gradient as the sun's direction vector
		//  This is a simple line equation with the gradient of the line being the sun's direction vector
		//
		//   P = P1 + c ( gradient )
		//
		// So, as we know the y value at both points,
		//   Py = P1y + c ( gradient.y )
		//   c = ( Py - P1y ) / gradient.y
		//
		// Therefore
		//  Px = P1x + c * gradient.x
		//  Pz = P1z + c * gradient.z
		//


		constant = ( ( ground_height - real_object_position.y ) / current_3d_sun->light_direction.y );

		shadow_world_position.x = real_object_position.x + ( constant * current_3d_sun->light_direction.x );
		shadow_world_position.z = real_object_position.z + ( constant * current_3d_sun->light_direction.z );

		if ( !position_on_3d_terrain ( shadow_world_position.x, shadow_world_position.z ) )
		{
			return;
		}

		shadow_world_position.y = get_3d_terrain_point_data ( shadow_world_position.x, shadow_world_position.z, NULL );

		get_3d_terrain_last_normal ( &terrain_normal );

		//
		// Test to see the distance from the shadow's centre point to the viewpoint
		//

		view_vector.x = shadow_world_position.x - visual_3d_vp->x;
		view_vector.y = shadow_world_position.y - visual_3d_vp->y;
		view_vector.z = shadow_world_position.z - visual_3d_vp->z;

		view_distance = get_3d_vector_magnitude ( &view_vector );

		if ( view_distance > MAX_SHADOW_VIEW_DISTANCE )
		{
			return;
		}

		//
		// To actually project a point onto the terrain face, we have to calculate the intercept point between the plane and the line
		//  ( the line is the ray of light from the 3d point on the object to the terrain face ).
		//
		// The equation of the line is:
		//   P = S + t(D)
		//
		// where P is any point on the line, S is the start point of the line, D is the direction vector, and t is a scalar variable.
		//
		// The equation of the plane is N.R + d = 0
		//  where N is the plane normal vector, R is any point ON the plane, and d is a scalar constant.
		//
		// After substituting R for P in the plane equation, and back substituting ( -N.R ) for d, we get the equation:
		//  t = ( ( N.R - N.S ) / N.D )
		//
		// This is good, as N.R is constant so long as the plane doesn't move ( which it doesn't ), and
		//   N.D is also constant so long as the light doesn't move ( again, it doesn't - not during the rendering of one scene )
		//
		// So, N.R is called the projection_constant, and N.D is called the projection factor.
		//

		projection_constant = shadow_world_position.x * terrain_normal.x +
										shadow_world_position.y * terrain_normal.y +
										shadow_world_position.z * terrain_normal.z;

		projection_factor = terrain_normal.x * current_3d_sun->light_direction.x +
									terrain_normal.y * current_3d_sun->light_direction.y +
									terrain_normal.z * current_3d_sun->light_direction.z;

		//
		// However, as a speed up, we don't want to do a division, so take the reciprocal of the projection factor, and multiply instead
		//

		projection_factor = 1.0 / projection_factor;

		//
		// The other thing we can do is figure out how much light has fallen on the face due to the main light source, and how
		//		much due to the ambient light, and make it darker accordingly.
		//

		light_angle = (	current_3d_sun->light_direction.x * terrain_normal.x +
								current_3d_sun->light_direction.y * terrain_normal.y +
								current_3d_sun->light_direction.z * terrain_normal.z );


		light_intensity = current_3d_sun->colour.red * 0.3 + current_3d_sun->colour.green * 0.59 + current_3d_sun->colour.blue * 0.11;

		ambient_intensity = ambient_3d_light.colour.red * 0.3 + ambient_3d_light.colour.green * 0.59 + ambient_3d_light.colour.blue * 0.11;

		shadow_intensity = light_intensity;

		//
		// We have a 'fudge factor' here - for some reason 176 looks the best
		//

		shadow_intensity = shadow_intensity * light_angle * 255;

		//
		// Now factor in a distance from the ground fudge
		//

		vector_distance.x = shadow_world_position.x - real_object_position.x;
		vector_distance.y = shadow_world_position.y - real_object_position.y;
		vector_distance.z = shadow_world_position.z - real_object_position.z;

		scalar_distance = get_3d_vector_magnitude ( &vector_distance );

		scalar_distance = bound ( scalar_distance, 0, MAXIMUM_SHADOW_DISTANCE );

		scalar_distance = 1.0 - ( scalar_distance / MAXIMUM_SHADOW_DISTANCE );

		shadow_intensity *= scalar_distance;

		object_dissolve = obj->object_dissolve_value;

		object_dissolve /= 255.0;

		shadow_intensity *= object_dissolve;

		shadow_intensity *= shadows_strength;

		if ( translucent_3d_shadows )
		{
			set_d3d_shadow_colour ( 0, 0, 0, shadow_intensity );
		}
	}

	//
	// If shadows are too translucent to be noticed - don't draw them
	//

	if ( shadow_intensity < 1 )
	{
		return;
	}

	//
	// Set up the object drawing global variables
	//

	object_3d_points_current_base = 0;

	object_3d_object_current_base = 0;

	object_3d_light_3d_current_base = 0;

	//
	// Set the shadow zbiasing constants
	//

	zbuffer_constant = zbuffer_constant_shadow_bias;

	//
	// Calculate the object's position relative to the view.
	//

	pos = &obj->view_position;

	{
		float
			fog_intensity;

		int
			ifog_intensity;

		vec3d
			shadow_relative_position;

		float
			shadow_relative_depth;

		//
		// Rotate the shadow world position to a relative position
		//

		shadow_relative_position.x = shadow_world_position.x - visual_3d_vp->x;
		shadow_relative_position.y = shadow_world_position.y - visual_3d_vp->y;
		shadow_relative_position.z = shadow_world_position.z - visual_3d_vp->z;

		//
		// Get only the Z value ( as we only want the fog value )
		//

		shadow_relative_depth = shadow_relative_position.x * visual_3d_vp->attitude[0][0];
		shadow_relative_depth += shadow_relative_position.y * visual_3d_vp->attitude[1][0];
		shadow_relative_depth += shadow_relative_position.z * visual_3d_vp->attitude[2][0];

		fog_intensity = get_fog_distance_value ( shadow_relative_depth );

		asm_convert_float_to_int ( fog_intensity, &ifog_intensity );

		set_d3d_fog_face_intensity ( ifog_intensity );
	}

	//
	// Rotate the sun's direction vector into the object's coordinate system
	//

	{

		float
			lx,
			ly,
			lz;

		lx = ( current_3d_sun->lx * obj->vp.attitude[0][0] );
		lx +=  ( current_3d_sun->ly * obj->vp.attitude[0][1] );
		lx += ( current_3d_sun->lz * obj->vp.attitude[0][2] );

		ly = ( current_3d_sun->lx * obj->vp.attitude[1][0] );
		ly += ( current_3d_sun->ly * obj->vp.attitude[1][1] );
		ly += ( current_3d_sun->lz * obj->vp.attitude[1][2] );


		lz = ( current_3d_sun->lx * obj->vp.attitude[2][0] );
		lz += ( current_3d_sun->ly * obj->vp.attitude[2][1] );
		lz += ( current_3d_sun->lz * obj->vp.attitude[2][2] );

		current_sun_object_view_vector.x = lx;
		current_sun_object_view_vector.y = ly;
		current_sun_object_view_vector.z = lz;

		//
		// Calculate the relative camera position in the object viewspace
		//

		current_scaled_sun_object_view_vector.x = lx * 55;
		current_scaled_sun_object_view_vector.y = ly * 55;
		current_scaled_sun_object_view_vector.z = lz * 55;
	}

	//
	// Put the view attitude matrix into the rotation matrix.
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

	//
	// Rotate the light source vector to be relative to the object.
	//

	light_ptr = current_3d_lights;

	prev_light = NULL;

	light = NULL;

	//
	//	Set up this objects' object info structure
	//

	object_3d_object_base[object_3d_object_current_base].lights = light;

	object_3d_object_base[object_3d_object_current_base].points_base = object_3d_points_current_base;

	current_object_3d_object_base = &object_3d_object_base[object_3d_object_current_base];

	//
	// Get the object number
	//

	object_number = get_object_shadow_polygon_object ( obj->object_number );

	if ( object_number )
	{
		//
		// We have a soft shadow object
		//

		object_3d_object_base[object_3d_object_current_base].object_number = object_number;

		//
		// Transform the object's shape data
		//

		{
			vec3d
				scale;

			scale.x = objects_3d_scene_database[obj->object_number].shadow_polygon_object_scale.x;
			scale.y = objects_3d_scene_database[obj->object_number].shadow_polygon_object_scale.y;
			scale.z = objects_3d_scene_database[obj->object_number].shadow_polygon_object_scale.z;
			scale.x *= obj->relative_scale.x;	//1;
			scale.y *= obj->relative_scale.y;	//1;
			scale.z *= obj->relative_scale.z;	//1;


			transform_3d_object_shadow ( &objects_3d_data[object_number],
													&scale,
													&obj->vp, &obj->vp.position,
													&terrain_normal, &current_3d_sun->light_direction,
													projection_constant, projection_factor,
													object_3d_points_current_base );
		}

//		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );
		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_shadow_comparison );	//D3DCMP_GREATER );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		set_d3d_sampler_state ( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		set_d3d_sampler_state ( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		set_d3d_sampler_state ( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT );
		set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
		set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );

		set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		set_d3d_int_state ( D3DRS_CULLMODE, D3DCULL_NONE );

		shadow_intensity = bound ( shadow_intensity, 0, 255 );

		{
			face_surface_description
				*surface;

			int
				number_of_surface_points,
				surfaces_left,
				surface_face_count,
				point_reference_index,
				texture_reference_index;

			point_reference_index = 0;

			texture_reference_index = 0;

			surface = objects_3d_data[object_number].surfaces;

			faces = objects_3d_data[object_number].faces;

			surface_face_count = surface->number_of_faces;

			current_object_3d_surface = objects_3d_data[object_number].surfaces;
			current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
			current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;
			current_object_3d_transformed_normals = transformed_3d_normals;

			current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;
			current_object_3d_surface_point_texture_list = objects_3d_data[object_number].surface_texture_points;
			current_object_3d_surface_point_normal_list = objects_3d_data[object_number].surface_point_normals;

			for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
			{
				int
					faces_left;

				number_of_surface_points = current_object_3d_surface->number_of_points;
				if ( number_of_surface_points == 0 )
				{
					number_of_surface_points = 256;
				}

				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( surface->polygons )
					{
						if ( surface->textured )
						{
							vec3d
								vec1,
								vec2,
								face_normal;

							object_short_3d_point
								*points;

							int
								point0,
								point1,
								point2;

							float
								angle;

							points = objects_3d_data[object_number].points;

							//
							// Calculate the face normal
							//

							point0 = current_object_3d_surface_point_list[ current_object_3d_point_list[0].point ].point;
							point1 = current_object_3d_surface_point_list[ current_object_3d_point_list[1].point ].point;
							point2 = current_object_3d_surface_point_list[ current_object_3d_point_list[2].point ].point;

							vec2.x = points[point2].x - points[point1].x;
							vec2.y = points[point2].y - points[point1].y;
							vec2.z = points[point2].z - points[point1].z;
							vec1.x = points[point1].x - points[point0].x;
							vec1.y = points[point1].y - points[point0].y;
							vec1.z = points[point1].z - points[point0].z;

							face_normal.x = ( vec1.y * vec2.z ) - ( vec1.z * vec2.y );
							face_normal.y = ( vec1.z * vec2.x ) - ( vec1.x * vec2.z );
							face_normal.z = ( vec1.x * vec2.y ) - ( vec1.y * vec2.x );

							normalise_any_3d_vector ( &face_normal );

							//
							// Calculate the angle this face makes with the light.
							//

							angle = (	face_normal.x * current_sun_object_view_vector.x +
											face_normal.y * current_sun_object_view_vector.y +
											face_normal.z * current_sun_object_view_vector.z  );

							//
							// Angle goes between -1 & 1 ( for -90 to +90 )
							//
							// Scale to -0.707 to 0.707 ( for -45 to +45 )
							//

							angle = fabs ( angle );

							angle -= 0.5;

							angle *= ( 1.0 / ( 1.0 - 0.5 ) );

							angle *= shadow_intensity * 2;

							{

								float
									new_shadow_intensity;

								new_shadow_intensity = angle;

								new_shadow_intensity = bound ( new_shadow_intensity, 0, 255 );

								set_d3d_shadow_colour ( 0, 0, 0, new_shadow_intensity );

								wrender_3d_shadow_surface_alpha_textured_polygon ( faces );
							}
						}
						if ( !current_object_3d_surface->smoothed )
						{
							current_object_3d_face_normal_list++;
						}
						current_object_3d_point_list += faces->number_of_points;
						faces++;
					}
					else
					{
						current_object_3d_point_list += 2;
					}
				}

				current_object_3d_surface_point_list += number_of_surface_points;
				if ( current_object_3d_surface->smoothed )
				{
					current_object_3d_surface_point_normal_list += number_of_surface_points;
				}
				if ( current_object_3d_surface->textured )
				{
					current_object_3d_surface_point_texture_list += number_of_surface_points;
				}
				if ( current_object_3d_surface->has_luminosity_texture )
				{
					current_object_3d_surface_point_texture_list += number_of_surface_points;
				}
				current_object_3d_surface++;
			}
		}

		//
		// Set the renderstates back to where they were
		//

		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );

		set_d3d_int_state ( D3DRS_CULLMODE, D3DCULL_CCW );
	}
	else
	{
		double
			zbias_decrement;

		object_number = get_object_shadow_approximation_number ( obj->object_number, pos->z, &draw_sub_objects );
		if ( object_number == 0 )
		{
			return;
		}

//		calculate_object_normal_factors ( objects_3d_data[object_number].point_normals,
//														objects_3d_data[object_number].number_of_point_normals,
//														&current_scaled_sun_object_view_vector,
//														&objects_3d_data[object_number].bounding_box, 0 );
		//
		// Set the zbiasing decrementing constant
		//

		zbias_decrement = ( POLYGON_ZDISTANCE_ELEVATED_BIAS - POLYGON_ZDISTANCE_SHADOW_ELEVATED_BIAS );	//( 8.0 / 65535.0 ) - ( 6.0 / 65535.0 ) );

		{
			int
				surfaces_left,
				point_reference_index,
				number_of_faces_to_render;

			point_reference_index = 0;

			number_of_faces_to_render = 0;

			faces = objects_3d_data[object_number].faces;

			current_object_3d_surface = objects_3d_data[object_number].surfaces;

			current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;

			for ( surfaces_left = objects_3d_data[object_number].number_of_surfaces; surfaces_left > 0; surfaces_left-- )
			{
				int
					faces_left;

				for ( faces_left = current_object_3d_surface->number_of_faces; faces_left > 0; faces_left-- )
				{
					if ( current_object_3d_surface->polygons )
					{
//						if ( transformed_3d_normal_visibilities[current_object_3d_face_normal_list->point] )
						{
							number_of_faces_to_render++;
						}

						if ( !current_object_3d_surface->smoothed )
						{
							current_object_3d_face_normal_list++;
						}
						faces++;
					}
				}

				current_object_3d_surface++;
			}

			zbias_decrement /= number_of_faces_to_render;
		}

		if ( object_number )
		{
			object_3d_object_base[object_3d_object_current_base].object_number = object_number;

			//
			// Transform the object's shape data
			//

			{
				vec3d
					scale;

				scale.x = 1;
				scale.y = 1;
				scale.z = 1;

				transform_3d_object_shadow ( &objects_3d_data[object_number],
														&scale,
														&obj->vp, &obj->vp.position,
														&terrain_normal,
														&current_3d_sun->light_direction,
														projection_constant, projection_factor,
														object_3d_points_current_base );
			}

			if ( translucent_3d_shadows )
			{
				//
				// Alpha blending is already on - set the Ztest & enable writing.
				//

				set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_shadow_comparison );	//D3DCMP_GREATER );
				set_d3d_int_state ( D3DRS_ZWRITEENABLE, TRUE );

				set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
				set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
			}
			else
			{
				set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );
			}

			{
				int
					surface;

				int
					surface_face_count,
					point_reference_index;

				point_reference_index = 0;

				surface = 0;

				current_object_3d_surface = objects_3d_data[object_number].surfaces;
				current_object_3d_point_list = objects_3d_data[object_number].object_faces_point_plain_list;
				current_object_3d_face_normal_list = objects_3d_data[object_number].object_face_normal_references;

				current_object_3d_surface_point_list = objects_3d_data[object_number].surface_points;

				faces = objects_3d_data[object_number].faces;

				for ( count = objects_3d_data[object_number].number_of_surfaces; count > 0; count-- )
				{
					int
						number_of_surface_points,
						face_count;

					surface_face_count = current_object_3d_surface->number_of_faces;

					number_of_surface_points = current_object_3d_surface->number_of_points;
					if ( number_of_surface_points == 0 )
					{
						number_of_surface_points = 256;
					}

					for ( face_count = surface_face_count; face_count > 0; face_count-- )
					{
						if ( current_object_3d_surface->polygons )
						{
//							if (transformed_3d_normal_visibilities[current_object_3d_face_normal_list->point])
							{
								wrender_3d_shadow_surface_plain_polygon ( faces );
							}
							current_object_3d_point_list += faces->number_of_points;
							if ( !current_object_3d_surface->smoothed )
							{
								current_object_3d_face_normal_list++;
							}
							faces++;
						}
						else
						{
							current_object_3d_point_list += 2;
						}
						zbuffer_constant -= zbuffer_constant_shadow_bias_decrement;
					}
					current_object_3d_surface_point_list += number_of_surface_points;
					current_object_3d_surface++;
				}
			}

			if ( translucent_3d_shadows )
			{
				//
				// Set the renderstates back to where they were
				//
				//
				set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );
				set_d3d_int_state ( D3DRS_ZWRITEENABLE, FALSE );
			}
		}
	}

	//
	// Restore the object's true 3d position now
	//

	obj->vp = real_object_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transform_3d_object_shadow ( object_3d *object, vec3d *object_3d_scale, viewpoint *vp, vec3d *pos, vec3d *terrain_normal, vec3d *projection_direction, double projection_constant, double projection_factor, int points_base )
{

	int
		count,
		number_of_points;

	object_short_3d_point
		*points;

	vertex
		*last_transformed_point,
		*result_points,
		tmp_vertex;

	float
		xmax,
		ymax,
		zmax,
		pos_x,
		pos_y,
		pos_z,
		oxmax,
		oxmin,
		oymax,
		oymin;

	int
		ixmax,
		ixmin,
		iymax,
		iymin;

	matrix3x3
		rotation_matrix;

	number_of_points = object->number_of_points;

	points = object->points;

	result_points = &transformed_3d_points[points_base];

	last_transformed_point = &tmp_vertex;

	pos_x = pos->x;

	pos_y = pos->y;

	pos_z = pos->z;

	memcpy ( rotation_matrix, vp->attitude, sizeof ( matrix3x3 ) );

	//
	// Calculate the object's rotation matrix, to transform its 3d points relative to the view.
	//

	xmax = max ( fabs ( object->bounding_box.xmin ), fabs ( object->bounding_box.xmax ) );
	ymax = max ( fabs ( object->bounding_box.ymin ), fabs ( object->bounding_box.ymax ) );
	zmax = max ( fabs ( object->bounding_box.zmin ), fabs ( object->bounding_box.zmax ) );

	rotation_matrix[0][0] *= object_3d_scale->x * ( xmax / 32767.0 );
	rotation_matrix[0][1] *= object_3d_scale->x * ( xmax / 32767.0 );
	rotation_matrix[0][2] *= object_3d_scale->x * ( xmax / 32767.0 );

	rotation_matrix[1][0] *= object_3d_scale->y * ( ymax / 32767.0 );
	rotation_matrix[1][1] *= object_3d_scale->y * ( ymax / 32767.0 );
	rotation_matrix[1][2] *= object_3d_scale->y * ( ymax / 32767.0 );

	rotation_matrix[2][0] *= object_3d_scale->z * ( zmax / 32767.0 );
	rotation_matrix[2][1] *= object_3d_scale->z * ( zmax / 32767.0 );
	rotation_matrix[2][2] *= object_3d_scale->z * ( zmax / 32767.0 );

	for ( count = number_of_points; count > 0; count-- )
	{

		float
			n_s,
			t,
			pointx,
			pointy,
			pointz,
			x_world,
			y_world,
			z_world,
			x,
			y,
			z;

		//
		// Convert the 3d point into float format
		//

		pointx = points->x;
		pointy = points->y;
		pointz = points->z;

		//
		// First, rotate the object into world space ( inverse attitude matrix )
		//

		x_world = pointx * rotation_matrix[0][0] + pointy * rotation_matrix[1][0] + pointz * rotation_matrix[2][0] + pos_x;
		y_world = pointx * rotation_matrix[0][1] + pointy * rotation_matrix[1][1] + pointz * rotation_matrix[2][1] + pos_y;
		z_world = pointx * rotation_matrix[0][2] + pointy * rotation_matrix[1][2] + pointz * rotation_matrix[2][2] + pos_z;

		//
		// Now project the points along the light's direction vector
		//

		//
		// Dot product the point and the face normal vector.
		//

		n_s = terrain_normal->x * x_world + terrain_normal->y * y_world + terrain_normal->z * z_world;

		t = ( ( projection_constant - n_s ) * projection_factor );

		x_world += projection_direction->x * t;
		y_world += projection_direction->y * t;
		z_world += projection_direction->z * t;

		x_world -= visual_3d_vp->x;
		y_world -= visual_3d_vp->y;
		z_world -= visual_3d_vp->z;

		//
		// Next, transform into the viewing coordinate system
		//

		x = x_world * rotation_3d[0][0] + y_world * rotation_3d[1][0] + z_world * rotation_3d[2][0];
		y = x_world * rotation_3d[0][1] + y_world * rotation_3d[1][1] + z_world * rotation_3d[2][1];
		z = x_world * rotation_3d[0][2] + y_world * rotation_3d[1][2] + z_world * rotation_3d[2][2];

		x *= active_3d_environment->screen_i_scale;
		y *= active_3d_environment->screen_j_scale;

		if ( z >= clip_hither )
		{

			float
				q,
				i,
				j;

			oxmax = active_viewport.x_max - last_transformed_point->i;
			oxmin = last_transformed_point->i - active_viewport.x_min;
			oymax = active_viewport.y_max - last_transformed_point->j;
			oymin = last_transformed_point->j - active_viewport.y_min;

			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );

			last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

			q = 1.0 / z;

			result_points->x = x;
			result_points->y = y;
			result_points->z = z;

			last_transformed_point = result_points;

			i = ( x * q );
			j = ( y * q );

			result_points->j = active_3d_environment->y_origin - j;
			result_points->i = active_3d_environment->x_origin + i;

			result_points->q = q;
		}
		else
		{

			result_points->outcode = CLIP_HITHER;

			result_points->z = z;
			result_points->x = x;
			result_points->y = y;
		}

		result_points++;

		points++;
	}

	oxmax = active_viewport.x_max - last_transformed_point->i;
	oxmin = last_transformed_point->i - active_viewport.x_min;
	oymax = active_viewport.y_max - last_transformed_point->j;
	oymin = last_transformed_point->j - active_viewport.y_min;

	ixmax = *( ( int * ) &oxmax );
	ixmin = *( ( int * ) &oxmin );
	iymax = *( ( int * ) &oymax );
	iymin = *( ( int * ) &oymin );

	last_transformed_point->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum OBJECT_3D_VISIBILITY get_object_3d_instance_shadow_visibility ( object_3d_instance *obj )
{

	int
		object_number,
		draw_sub_objects,
		outcode,
		outcode2,
		count;

	viewpoint
		real_object_position;

	object_3d_point
		*object_points,
		object_box[8];

	vec3d
		*pos,
		terrain_normal,
		current_sun_object_view_vector;

	float
		projection_factor,
		projection_constant;

	viewpoint
		*vp;

	//
	// Have to project the corner points of the object onto the landscape to ensure we aren't doing tons more work than we have to.
	//

	if ( current_3d_sun->light_direction.y < 0.1 )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}

	//
	// Store the object's position now, and restore it after drawing the shadow.
	//

	real_object_position = obj->vp;

	vp = visual_3d_vp;

	//
	// Calculate the object's position relative to the view.
	//

	pos = &obj->vp.position;

	//
	// Get the object number
	//

	object_number = get_object_shadow_polygon_object ( obj->object_number );

	if ( !object_number )
	{

		object_number = get_object_approximation_number ( obj->object_number, pos->z, &draw_sub_objects );
	}

	if ( object_number == 0 )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}


	if ( objects_3d_data[object_number].number_of_points == 0 )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}

	//
	// First, find the position of the shadow on the ground.
	//
	//  Take the height of the ground directly below the 3d object, and project from the sun down to that height.
	//   This does lead to some errors, but hopefully not noticable.
	//

	{

		float
			ground_height,
			constant;

		vec3d
			position;

		if ( !position_on_3d_terrain ( real_object_position.x, real_object_position.z ) )
		{

			return ( OBJECT_3D_NOT_VISIBLE );
		}

		ground_height = get_3d_terrain_elevation ( real_object_position.x, real_object_position.z );

		//
		// Strike a vector from object to the ground, with the same gradient as the sun's direction vector
		//  This is a simple line equation with the gradient of the line being the sun's direction vector
		//
		//   P = P1 + c ( gradient )
		//
		// So, as we know the y value at both points,
		//   Py = P1y + c ( gradient.y )
		//   c = ( Py - P1y ) / gradient.y
		//
		// Therefore
		//  Px = P1x + c * gradient.x
		//  Pz = P1z + c * gradient.z
		//


		constant = ( ( ground_height - real_object_position.y ) / current_3d_sun->light_direction.y );

		position.x = real_object_position.x + ( constant * current_3d_sun->light_direction.x );
		position.z = real_object_position.z + ( constant * current_3d_sun->light_direction.z );

		if ( !position_on_3d_terrain ( position.x, position.z ) )
		{

			return ( OBJECT_3D_NOT_VISIBLE );
		}

		position.y = get_3d_terrain_point_data ( position.x, position.z, NULL );	//&terrain_normal, NULL );

		get_3d_terrain_last_normal ( &terrain_normal );

		//
		// To actually project a point onto the terrain face, we have to calculate the intercept point between the plane and the line
		//  ( the line is the ray of light from the 3d point on the object to the terrain face ).
		//
		// The equation of the line is:
		//   P = S + t(D)
		//
		// where P is any point on the line, S is the start point of the line, D is the direction vector, and t is a scalar variable.
		//
		// The equation of the plane is N.R + d = 0
		//  where N is the plane normal vector, R is any point ON the plane, and d is a scalar constant.
		//
		// After substituting R for P in the plane equation, and back substituting ( -N.R ) for d, we get the equation:
		//  t = ( ( N.R - N.S ) / N.D )
		//
		// This is good, as N.R is constant so long as the plane doesn't move ( which it doesn't ), and
		//   N.D is also constant so long as the light doesn't move ( again, it doesn't - not during the rendering of one scene )
		//
		// So, N.R is called the projection_constant, and N.D is called the projection factor.
		//

		projection_constant = position.x * terrain_normal.x +
										position.y * terrain_normal.y +
										position.z * terrain_normal.z;

		projection_factor = terrain_normal.x * current_3d_sun->light_direction.x +
									terrain_normal.y * current_3d_sun->light_direction.y +
									terrain_normal.z * current_3d_sun->light_direction.z;

		//
		// However, as a speed up, we don't want to do a division, so take the reciprocal of the projection factor, and multiply instead
		//

		projection_factor = 1.0 / projection_factor;
	}

	//
	// Set up the object drawing global variables
	//

	//
	// Rotate the sun's direction vector into the object's coordinate system
	//

	{

		float
			lx,
			ly,
			lz;

		lx = ( current_3d_sun->lx * obj->vp.attitude[0][0] );
		lx +=  ( current_3d_sun->ly * obj->vp.attitude[0][1] );
		lx += ( current_3d_sun->lz * obj->vp.attitude[0][2] );

		ly = ( current_3d_sun->lx * obj->vp.attitude[1][0] );
		ly += ( current_3d_sun->ly * obj->vp.attitude[1][1] );
		ly += ( current_3d_sun->lz * obj->vp.attitude[1][2] );


		lz = ( current_3d_sun->lx * obj->vp.attitude[2][0] );
		lz += ( current_3d_sun->ly * obj->vp.attitude[2][1] );
		lz += ( current_3d_sun->lz * obj->vp.attitude[2][2] );

		current_sun_object_view_vector.x = lx;
		current_sun_object_view_vector.y = ly;
		current_sun_object_view_vector.z = lz;
	}

	//
	// Put the view attitude matrix into the rotation matrix.
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

	//
	// Project the bounding points of the object
	//

	object_box[0].x = objects_3d_data[object_number].bounding_box.xmin;
	object_box[0].y = objects_3d_data[object_number].bounding_box.ymin;
	object_box[0].z = objects_3d_data[object_number].bounding_box.zmin;

	object_box[1].x = objects_3d_data[object_number].bounding_box.xmin;
	object_box[1].y = objects_3d_data[object_number].bounding_box.ymin;
	object_box[1].z = objects_3d_data[object_number].bounding_box.zmax;

	object_box[2].x = objects_3d_data[object_number].bounding_box.xmin;
	object_box[2].y = objects_3d_data[object_number].bounding_box.ymax;
	object_box[2].z = objects_3d_data[object_number].bounding_box.zmin;

	object_box[3].x = objects_3d_data[object_number].bounding_box.xmin;
	object_box[3].y = objects_3d_data[object_number].bounding_box.ymax;
	object_box[3].z = objects_3d_data[object_number].bounding_box.zmax;

	object_box[4].x = objects_3d_data[object_number].bounding_box.xmax;
	object_box[4].y = objects_3d_data[object_number].bounding_box.ymin;
	object_box[4].z = objects_3d_data[object_number].bounding_box.zmin;

	object_box[5].x = objects_3d_data[object_number].bounding_box.xmax;
	object_box[5].y = objects_3d_data[object_number].bounding_box.ymin;
	object_box[5].z = objects_3d_data[object_number].bounding_box.zmax;

	object_box[6].x = objects_3d_data[object_number].bounding_box.xmax;
	object_box[6].y = objects_3d_data[object_number].bounding_box.ymax;
	object_box[6].z = objects_3d_data[object_number].bounding_box.zmin;

	object_box[7].x = objects_3d_data[object_number].bounding_box.xmax;
	object_box[7].y = objects_3d_data[object_number].bounding_box.ymax;
	object_box[7].z = objects_3d_data[object_number].bounding_box.zmax;

	object_points = object_box;

	{

		object_3d_point
			*points;

		vertex
			*result_points;

		float
			pos_x,
			pos_y,
			pos_z,
			oxmax,
			oxmin,
			oymax,
			oymin;

		int
			ixmax,
			ixmin,
			iymax,
			iymin;

		points = object_points;	//objects_3d_data[object_number].points;

		result_points = &transformed_3d_points[0];

		pos_x = pos->x;
		pos_y = pos->y;
		pos_z = pos->z;

		for ( count = 8; count > 0; count-- )
		{

			float
				n_s,
				t,
				x_world,
				y_world,
				z_world,
				x,
				y,
				z;

			//
			// First, rotate the object into world space ( inverse attitude matrix )
			//

			x_world = points->x * obj->vp.xv.x + points->y * obj->vp.yv.x + points->z * obj->vp.zv.x + pos_x;
			y_world = points->x * obj->vp.xv.y + points->y * obj->vp.yv.y + points->z * obj->vp.zv.y + pos_y;
			z_world = points->x * obj->vp.xv.z + points->y * obj->vp.yv.z + points->z * obj->vp.zv.z + pos_z;

			//
			// Now project the points along the light's direction vector
			//

			//
			// Dot product the point and the face normal vector.
			//

			n_s = terrain_normal.x * x_world + terrain_normal.y * y_world + terrain_normal.z * z_world;

			t = ( ( projection_constant - n_s ) * projection_factor );

			x_world += current_3d_sun->light_direction.x * t;
			y_world += current_3d_sun->light_direction.y * t;
			z_world += current_3d_sun->light_direction.z * t;

			x_world -= visual_3d_vp->x;
			y_world -= visual_3d_vp->y;
			z_world -= visual_3d_vp->z;

			//
			// Next, transform into the viewing coordinate system
			//

			x = x_world * rotation_3d[0][0] + y_world * rotation_3d[1][0] + z_world * rotation_3d[2][0];
			y = x_world * rotation_3d[0][1] + y_world * rotation_3d[1][1] + z_world * rotation_3d[2][1];
			z = x_world * rotation_3d[0][2] + y_world * rotation_3d[1][2] + z_world * rotation_3d[2][2];

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{

				float
					q,
					i,
					j;

				q = 1.0 / z;

				result_points->x = x;
				result_points->y = y;
				result_points->z = z;

				i = ( active_3d_environment->screen_i_scale * x * q );
				j = ( active_3d_environment->screen_j_scale * y * q );

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
			}

			result_points++;

			points++;
		}
	}


	outcode = transformed_3d_points[7].outcode;
	outcode2 = transformed_3d_points[7].outcode;

	for ( count = 6; count >= 0; count-- )
	{

		outcode |= transformed_3d_points[count].outcode;
		outcode2 &= transformed_3d_points[count].outcode;
	}

	if ( outcode2 != 0 )
	{

		return ( OBJECT_3D_NOT_VISIBLE );
	}
	else
	{

		return ( OBJECT_3D_PARTIALLY_VISIBLE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
