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

#if 0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_textured_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	real_colour
		colour,
		specular_colour;

	int
		outcode,
		triangle_count;

	ASSERT ( current_object_3d_surface->polygons );

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( &colour );

		specular_colour.colour = d3d_fog_intensity;
	}
	else
	{

		//
		// Look up the colour of the face normal
		//

		colour.colour = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].colour;
		colour.alpha = current_object_3d_dissolve_value;

		//
		// Construct the specular colour
		//

		if ( current_object_3d_surface->additive )
		{
	
			specular_colour.colour = d3d_fog_intensity;
		}
		else
		{
	
			float
				specular;
	
			int
				ispecular;
	
			specular = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;
	
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
	
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;
		}
	}

			
	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{
	
		poly = construct_3d_vertex_textured_triangle_fan ( triangle_count,
																			NULL,	//current_object_3d_point_list,
																			current_object_3d_texture_list,
																			object_base->points_base,
																			&outcode );

		if ( poly )
		{
	
			clip_3d_coord = 0;
		
			if ( outcode & CLIP_HITHER )
			{
		
				poly = hither_clip_3d_polygon ( poly, &outcode );
		
				if ( !poly )
				{
		
					continue;
				}
			}
		
			if ( outcode )
			{
		
				apply_perspective_to_polygon_texture ( poly );
					
				poly = clip_3d_polygon ( poly, outcode );
		
				if ( !poly )
				{
		
					continue;
				}
		
				remove_perspective_from_polygon_texture ( poly );
			}
		
			{
		
				if ( current_object_3d_surface->additive )
				{
		
					buffer_zbuffered_flat_shaded_textured_polygon ( poly, current_object_3d_texture,
																					current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																					current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																					colour, specular_colour, TRUE );
				}
				else
				{
			
					if ( current_object_3d_texture->contains_alpha )
					{
			
						buffer_zbuffered_flat_shaded_textured_polygon ( poly, current_object_3d_texture,
																						current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																						current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																						colour, specular_colour, FALSE );
					}
					else
					{
		
						commit_deferred_state_changes ();
		
						draw_zbuffered_flat_shaded_textured_polygon ( poly, colour, specular_colour );
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_gouraud_textured_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		triangle_count,
		outcode;

	float
		specular;

	vertex
		*poly;

	ASSERT ( current_object_3d_surface->polygons );

	specular = current_object_3d_surface->specularity;

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{

		poly = construct_3d_vertex_gouraud_textured_triangle_fan ( triangle_count,
																						specular,
																						NULL,	//current_object_3d_point_list,
																						current_object_3d_gouraud_list,
																						current_object_3d_texture_list,
																						object_base->points_base,
																						&outcode );
		if ( poly )
		{

			if ( outcode )
			{
		
				clip_3d_coord = 0;

				if ( outcode & CLIP_HITHER )
				{
			
					poly = hither_clip_3d_polygon ( poly, &outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			
				if ( outcode )
				{
		
					apply_perspective_to_polygon_texture ( poly );
						
					poly = clip_3d_polygon ( poly, outcode );
		
					if ( !poly )
					{
		
						continue;
					}
		
					remove_perspective_from_polygon_texture ( poly );
				}
			}
		

			if ( current_object_3d_texture->contains_alpha )
			{

				//
				// Should draw a transparent gouraud shaded textured polygon
				//

				buffer_zbuffered_gouraud_shaded_textured_polygon ( poly, current_object_3d_texture,
																					current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																					current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																					current_object_3d_specular, FALSE );
			}
			else
			{

				//
				// Should draw a solid gouraud shaded textured polygon
				//

				commit_deferred_state_changes ();

				draw_zbuffered_gouraud_shaded_textured_polygon ( poly );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	int
		outcode,
		triangle_count;

	real_colour
		colour,
		specular_colour;

	ASSERT ( current_object_3d_surface->polygons );

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( &colour );

		specular_colour.colour = d3d_fog_intensity;
	}
	else
	{

		float
			red,
			green,
			blue,
			specular;

		int
			ir,
			ig,
			ib,
			ispecular;

		//
		// Look up the colour of the face normal
		//
	
		red = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].r;
		green = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].g;
		blue = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].b;
		specular = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;
	
		red /= 255.0;
		green /= 255.0;
		blue /= 255.0;
	
		asm_convert_float_to_int ( ( red * current_object_3d_surface->red ), &ir );
		asm_convert_float_to_int ( ( green * current_object_3d_surface->green ), &ig );
		asm_convert_float_to_int ( ( blue * current_object_3d_surface->blue ), &ib );
		asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
	
		colour.red = ir;
		colour.green = ig;
		colour.blue = ib;

		specular_colour.colour = d3d_fog_intensity;
		specular_colour.red = ispecular;
		specular_colour.green = ispecular;
		specular_colour.blue = ispecular;
	}

	{

		int
			imixed_dissolve;

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &imixed_dissolve );
		colour.alpha = imixed_dissolve;
	}

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{

		poly = construct_3d_vertex_triangle_fan ( triangle_count, NULL,	//current_object_3d_point_list,
																		object_base->points_base, &outcode );

		if ( poly )
		{

			if ( outcode )
			{
		
				clip_3d_coord = 0;

				if ( outcode & CLIP_HITHER )
				{
			
					poly = hither_clip_3d_polygon ( poly, &outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			
				if ( outcode )
				{
			
					poly = clip_3d_polygon ( poly, outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			}
		
			if ( current_object_3d_surface->translucent )
			{
		
				buffer_zbuffered_plain_polygon ( poly, colour, specular_colour, current_object_3d_surface->additive );
			}
			else
			{
		
				commit_deferred_state_changes ();
		
				draw_zbuffered_plain_polygon ( poly, colour, specular_colour );
			}
		}
	}

/*
	if ( current_object_3d_surface->reflectivity != 0.0 )
	{

		matrix3x3
			reflection_matrix;

		int
			count,
			normal_index;

		vec3d
			camera_position,
			reflected_ray;

		float
			model_x,
			model_y,
			model_z,
			u,
			v;

		vertex
			*this_point;

		normal_index = current_object_3d_face_normal_list->point;

		get_reflection_matrix ( reflection_matrix, &objects_3d_data[object_base->object_number].point_normals[normal_index] );

		camera_position = object_base->camera_position;

		//
		// Now get the u,v coordinates
		//

		this_point = poly;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vec3d
				ray;

			model_x = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].x;
			model_y = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].y;
			model_z = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].z;
	
			ray.x = camera_position.x - model_x;
			ray.y = camera_position.y - model_y;
			ray.z = camera_position.z - model_z;

			multiply_matrix3x3_vec3d ( &reflected_ray, reflection_matrix, &ray );
	
			normalise_any_3d_vector ( &reflected_ray );
	
			u = atan2 ( reflected_ray.x, reflected_ray.z );
			v = asin ( reflected_ray.y );

			this_point->u = u / PI2;
			this_point->v = v / PI2;

			this_point = this_point->next_vertex;
		}
	}
	*/

	//
	// Should draw a light sourced plain polygon
	//

/*
	if ( current_object_3d_surface->reflectivity != 0.0 )
	{

		real_colour
			this_colour;

		this_colour.red = 255;
		this_colour.green = 255;
		this_colour.blue = 255;
		this_colour.alpha = 255;

		buffer_sorted_translucent_flat_shaded_textured_polygon ( poly, &system_textures[TEXTURE_INDEX_CLOUDDRY],
																					D3DFILTER_LINEAR, D3DFILTER_NEAREST, D3DTADDRESS_WRAP,
																					this_colour, FALSE );
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_gouraud_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	int
		triangle_count,
		outcode,
		polygon_alpha;

	float
		surface_red,
		surface_green,
		surface_blue,
		surface_specular;


	//
	// The face is a true polygon - triangle or above
	//

	ASSERT ( current_object_3d_surface->polygons );

	surface_red = ( ( float ) current_object_3d_surface->red ) / 255.0;
	surface_green = ( ( float ) current_object_3d_surface->green ) / 255.0;
	surface_blue = ( ( float ) current_object_3d_surface->blue ) / 255.0;

	if ( current_object_3d_specular )
	{

		surface_specular = ( float ) current_object_3d_surface->specularity;
	}
	else
	{

		surface_specular = 0;
	}

	if ( current_object_3d_surface->translucent )
	{

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &polygon_alpha );
	}

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{

		poly = construct_3d_vertex_gouraud_triangle_fan ( triangle_count,
																			surface_specular,
																			NULL,	//current_object_3d_point_list,
																			current_object_3d_gouraud_list,
																			object_base->points_base,
																			&outcode );

		if ( poly )
		{
	
			if ( outcode )
			{
		
				clip_3d_coord = 0;

				if ( outcode & CLIP_HITHER )
				{
			
					poly = hither_clip_3d_polygon ( poly, &outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			
				if ( outcode )
				{
			
					poly = clip_3d_polygon ( poly, outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			}
		
			//
			// Should draw a gouraud shaded polygon
			//
	
			if ( current_object_3d_surface->translucent )
			{

				buffer_zbuffered_gouraud_shaded_polygon ( poly, surface_red, surface_green, surface_blue, polygon_alpha, surface_specular, FALSE );
			}
			else
			{
	
				commit_deferred_state_changes ();

				draw_zbuffered_gouraud_shaded_polygon ( poly, surface_red, surface_green, surface_blue );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_white_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	int
		outcode,
		triangle_count;

	real_colour
		colour,
		specular_colour;

	ASSERT ( current_object_3d_surface->polygons );

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( &colour );
	
		specular_colour.colour = d3d_fog_intensity;
	}
	else
	{

		//
		// Look up the colour of the face normal
		//
	
		colour.red = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].r;
		colour.green = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].g;
		colour.blue = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].b;
	
		specular_colour.colour = d3d_fog_intensity;
	}

	{

		int
			imixed_dissolve;

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &imixed_dissolve );
		colour.alpha = imixed_dissolve;
	}

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{

		poly = construct_3d_vertex_triangle_fan ( triangle_count, NULL,	//current_object_3d_point_list,
																	object_base->points_base, &outcode );

		if ( poly )
		{

			if ( outcode )
			{
		
				clip_3d_coord = 0;

				if ( outcode & CLIP_HITHER )
				{
			
					poly = hither_clip_3d_polygon ( poly, &outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			
				if ( outcode )
				{
			
					poly = clip_3d_polygon ( poly, outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			}
		
			if ( current_object_3d_surface->translucent )
			{
		
				buffer_zbuffered_plain_polygon ( poly, colour, specular_colour, current_object_3d_surface->additive );
			}
			else
			{
		
				commit_deferred_state_changes ();
		
				draw_zbuffered_plain_polygon ( poly, colour, specular_colour );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_gouraud_white_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	int
		triangle_count,
		outcode,
		polygon_alpha;


	//
	// The face is a true polygon - triangle or above
	//

	ASSERT ( current_object_3d_surface->polygons );

	if ( current_object_3d_surface->translucent )
	{

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &polygon_alpha );
	}

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{

		poly = construct_3d_vertex_gouraud_triangle_fan ( triangle_count,
																			0,
																			NULL,	//current_object_3d_point_list,
																			current_object_3d_gouraud_list,
																			object_base->points_base,
																			&outcode );

		if ( poly )
		{
	
			if ( outcode )
			{
		
				clip_3d_coord = 0;

				if ( outcode & CLIP_HITHER )
				{
			
					poly = hither_clip_3d_polygon ( poly, &outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			
				if ( outcode )
				{
			
					poly = clip_3d_polygon ( poly, outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			}
		
			//
			// Should draw a gouraud shaded polygon
			//
	
			if ( current_object_3d_surface->translucent )
			{

				buffer_zbuffered_gouraud_shaded_polygon ( poly, 1.0, 1.0, 1.0, polygon_alpha, 0, FALSE );
			}
			else
			{
	
				commit_deferred_state_changes ();

				draw_zbuffered_gouraud_shaded_polygon ( poly, 1.0, 1.0, 1.0 );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	real_colour
		colour,
		specular_colour,
		lightmap_colour;

	int
		outcode,
		triangle_count;

	ASSERT ( current_object_3d_surface->polygons );

	specular_colour.colour = d3d_fog_intensity;

	if ( current_object_3d_surface->luminous )
	{
	
		colour.red = current_object_3d_surface->red;
		colour.green = current_object_3d_surface->green;
		colour.blue = current_object_3d_surface->blue;
		colour.alpha = current_object_3d_dissolve_value;
	}
	else
	{

		float
			specular;

		int
			ispecular;

		//
		// Look up the colour of the face normal
		//

		colour.colour = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].colour;
		colour.alpha = current_object_3d_dissolve_value;

		//
		// Construct the specular colour
		//
	
		specular = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;
	
		asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
	
		specular_colour.colour = d3d_fog_intensity;
		specular_colour.red = ispecular;
		specular_colour.green = ispecular;
		specular_colour.blue = ispecular;
	}

	//
	// Now figure out the lightmap colours
	//

	lightmap_colour.red = current_object_3d_surface->red;
	lightmap_colour.green = current_object_3d_surface->green;
	lightmap_colour.blue = current_object_3d_surface->blue;
	lightmap_colour.alpha = 255;

	calculate_lightmap_luminous_colour ( &lightmap_colour );

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{
	
		poly = construct_3d_vertex_dual_textured_triangle_fan ( triangle_count,
																					NULL,	//current_object_3d_point_list,
																					current_object_3d_texture_list,
																					current_object_3d_texture_list + this_face->number_of_points,
																					object_base->points_base,
																					&outcode );

		if ( poly )
		{
	
			clip_3d_coord = 0;
		
			if ( outcode & CLIP_HITHER )
			{
		
				poly = hither_clip_3d_dual_texture_polygon ( poly, &outcode );
		
				if ( !poly )
				{
		
					continue;
				}
			}
		
			if ( outcode )
			{
		
				apply_perspective_to_polygon_dual_texture ( poly );
					
				poly = clip_3d_dual_texture_polygon ( poly, outcode );
		
				if ( !poly )
				{
		
					continue;
				}
		
				remove_perspective_from_polygon_dual_texture ( poly );
			}
		
			if ( current_object_3d_texture->contains_alpha )
			{
		
				buffer_zbuffered_flat_shaded_textured_polygon ( poly, current_object_3d_texture,
																				current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																				current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																				colour, specular_colour, FALSE );
			}
			else
			{
		
				vertex
					*vert;
		
				int
					number_of_points,
					count;
		
				LPD3DTLVERTEX
					destination_vertices,
					lightmap_vertices;
		
				//
				// Set main polygon rendertype
				//
		
				commit_deferred_state_changes ();
		
				//
				// Count vertices
				//
		
				number_of_points = 0;
		
				vert = poly;
		
				while ( vert )
				{
		
					number_of_points++;
		
					vert = vert->next_vertex;
				}
		
				destination_vertices = get_d3d_vertices_points_address ( number_of_points );
		
				lightmap_vertices = get_temporary_translucent_polygon_vertices ();
		
				vert = poly;
				count = 0;
		
				while ( vert )
				{
		
					destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
					destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
					destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
					destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;
		
		
					destination_vertices[count].tu = vert->u;
					destination_vertices[count].tv = vert->v;

					lightmap_vertices[count].tu = vert->u2;
					lightmap_vertices[count].tv = vert->v2;
		
					destination_vertices[count].color = colour.colour;
					destination_vertices[count].specular = specular_colour.colour;
		
					lightmap_vertices[count].color = lightmap_colour.colour;
					lightmap_vertices[count].specular = d3d_fog_intensity;
		
					vert = vert->next_vertex;
					count++;
				}
			
				draw_fan_primitive ( number_of_points, destination_vertices );
		
				if ( current_object_3d_light_maps_enabled )
				{
		
					add_temporary_buffered_processed_polygon ( number_of_points,
																					current_object_3d_luminosity_texture,
																					current_object_3d_luminosity_texture_filter,
																					current_object_3d_luminosity_texture_mipmap,
																					current_object_3d_luminosity_texture_u_address,
																					current_object_3d_luminosity_texture_v_address,
																					TRUE );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_gouraud_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		triangle_count,
		outcode;

	vertex
		*poly;

	float
		specular;

	real_colour
		lightmap_colour;

	ASSERT ( current_object_3d_surface->polygons );

	//
	// Figure out the lightmap colours
	//

	lightmap_colour.red = current_object_3d_surface->red;
	lightmap_colour.green = current_object_3d_surface->green;
	lightmap_colour.blue = current_object_3d_surface->blue;
	lightmap_colour.alpha = 255;

	calculate_lightmap_luminous_colour ( &lightmap_colour );

	specular = current_object_3d_surface->specularity;

	for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
	{

		poly = construct_3d_vertex_gouraud_dual_textured_triangle_fan ( triangle_count,
																								specular,
																								NULL,	//current_object_3d_point_list,
																								current_object_3d_gouraud_list,
																								current_object_3d_texture_list,
																								current_object_3d_texture_list + this_face->number_of_points,
																								object_base->points_base,
																								&outcode );
		if ( poly )
		{
		
			if ( outcode )
			{
		
				clip_3d_coord = 0;

				if ( outcode & CLIP_HITHER )
				{
			
					poly = hither_clip_3d_dual_texture_polygon ( poly, &outcode );
		
					if ( !poly )
					{
		
						continue;
					}
				}
			
				if ( outcode )
				{
		
					apply_perspective_to_polygon_dual_texture ( poly );
						
					poly = clip_3d_dual_texture_polygon ( poly, outcode );
		
					if ( !poly )
					{
		
						continue;
					}
		
					remove_perspective_from_polygon_dual_texture ( poly );
				}
			}
		

			if ( current_object_3d_texture->contains_alpha )
			{

				//
				// Should draw a transparent gouraud shaded textured polygon
				//

				buffer_zbuffered_gouraud_shaded_textured_polygon ( poly, current_object_3d_texture,
																					current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																					current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																					current_object_3d_specular, FALSE );
			}
			else
			{

				//
				// Should draw a solid gouraud shaded textured polygon
				//

				{
			
					vertex
						*vert;
		
					int
						number_of_points,
						count;
		
					LPD3DTLVERTEX
						destination_vertices,
						lightmap_vertices;

					real_colour
						specular_colour;
		
					//
					// Set main polygon rendertype
					//
		
					commit_deferred_state_changes ();
		
					//
					// Count vertices
					//
		
					number_of_points = 0;
		
					vert = poly;
		
					while ( vert )
					{
		
						number_of_points++;
		
						vert = vert->next_vertex;
					}
		
					destination_vertices = get_d3d_vertices_points_address ( number_of_points );
		
					lightmap_vertices = get_temporary_translucent_polygon_vertices ();
		
					vert = poly;
					count = 0;

					specular_colour.colour = d3d_fog_intensity;
		
					while ( vert )
					{

						destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
						destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
						destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
						destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;
			
						destination_vertices[count].tu = vert->u;
						destination_vertices[count].tv = vert->v;

						lightmap_vertices[count].tu = vert->u2;
						lightmap_vertices[count].tv = vert->v2;

						specular_colour.red = vert->specular;
						specular_colour.green = vert->specular;
						specular_colour.blue = vert->specular;

						destination_vertices[count].color = vert->colour;
						destination_vertices[count].specular = specular_colour.colour;

						lightmap_vertices[count].color = lightmap_colour.colour;
						lightmap_vertices[count].specular = d3d_fog_intensity;
		
						vert = vert->next_vertex;
						count++;
					}
				
					draw_fan_primitive ( number_of_points, destination_vertices );

					if ( current_object_3d_light_maps_enabled )
					{
	
						add_temporary_buffered_processed_polygon ( number_of_points,
																						current_object_3d_luminosity_texture,
																						current_object_3d_luminosity_texture_filter,
																						current_object_3d_luminosity_texture_mipmap,
																						current_object_3d_luminosity_texture_u_address,
																						current_object_3d_luminosity_texture_v_address,
																						TRUE );
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_textured_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	real_colour
		colour;

	real_colour
		specular_colour;

	ASSERT ( current_object_3d_surface->polygons );

	colour.alpha = current_object_3d_dissolve_value;

	specular_colour.colour = d3d_fog_intensity;

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( &colour );
	}
	else
	{

		//
		// Look up the colour of the face normal
		//

		colour.colour = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].colour;

		if ( current_object_3d_specular )
		{
	
			int
				ispecular;
	
			float
				specular;
	
			specular = current_object_3d_surface->specularity * current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;
	
			asm_convert_float_to_int ( specular, &ispecular );
	
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;
		}
	}

	if ( ( current_object_3d_surface->additive ) || ( current_object_3d_texture->contains_alpha ) )
	{

		int
			count;

		object_transformed_2d_point
			*vert,
			*transformed_points;
	
		LPD3DTLVERTEX
			destination_vertices;
	
		object_3d_short_textured_point
			*texture_list;

		float
			distance;

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_translucent_polygon_vertices ();
	
		texture_list = current_object_3d_texture_list;

		distance = 0;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;
			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;

			distance += vert->q;

			texture_list++;
		}
	
		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_FLAT, current_object_3d_texture,
																	current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																	current_object_3d_specular, current_object_3d_surface->additive );
	}
	else
	{

		int
			count;
	
		object_transformed_2d_point
			*vert,
			*transformed_points;
	
		LPD3DTLVERTEX
			destination_vertices;
	
		object_3d_short_textured_point
			*texture_list;

		commit_deferred_state_changes ();

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
	
		texture_list = current_object_3d_texture_list;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;

			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;
			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;

			texture_list++;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
/*
//		if ( current_object_3d_surface->reflectivity != 0.0 )
		{
	
			int
				count;
	
			vec3d
				*normal,
				reflected_ray,
				camera_position;
	
			float
				model_x,
				model_y,
				model_z,
				u,
				v;
	
			real_colour
				this_colour;
	
			LPD3DTLVERTEX
				reflection_vertices;

			reflection_vertices = get_temporary_translucent_polygon_vertices ();
	
			camera_position = object_base->camera_position;

			normal = &objects_3d_data[object_base->object_number].point_normals[current_object_3d_face_normal_list->point];

			this_colour.red = 255;
			this_colour.green = 255;
			this_colour.blue = 255;
			this_colour.alpha = 64;

			//
			// Now get the u,v coordinates
			//
	
			for ( count = 0; count < this_face->number_of_points; count++ )
			{
	
				vec3d
					ray;

				float
					ndotr,
					denominator;
	
				model_x = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].x;
				model_y = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].y;
				model_z = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].z;

				ray.x = camera_position.x - model_x;
				ray.y = camera_position.y - model_y;
				ray.z = camera_position.z - model_z;

				normalise_any_3d_vector ( &ray );

				//
				// Reflection = 2.0 * ( Normal . Ray ) * Normal - Ray
				//

				ndotr = ray.x * normal->x + ray.y * normal->y + ray.z * normal->z;

				reflected_ray.x = 2.0 * ndotr * normal->x - ray.x;
				reflected_ray.y = 2.0 * ndotr * normal->y - ray.y;
				reflected_ray.z = 2.0 * ndotr * normal->z - ray.z;

				normalise_any_3d_vector ( &reflected_ray );

				multiply_matrix3x3_vec3d ( &ray, object_base->object_vp->attitude, &reflected_ray );

				reflected_ray = ray;
	
				denominator = get_inverse_square_root ( 2.0 * ( reflected_ray.z + 1 ) );

				u = 0.5 + ( reflected_ray.x * denominator ) / 2.0;
				v = 0.5 + ( reflected_ray.y * denominator ) / 2.0;

				vert = transformed_points + current_object_3d_point_list[count].point;
		
				*( ( int * ) &reflection_vertices[count].sx ) = *( ( int * ) &vert->i );
				*( ( int * ) &reflection_vertices[count].sy ) = *( ( int * ) &vert->j );
				reflection_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
				reflection_vertices[count].rhw = vert->q;
				reflection_vertices[count].tu = v;
				reflection_vertices[count].tv = u;
				reflection_vertices[count].color = this_colour.colour;
				reflection_vertices[count].specular = d3d_fog_intensity;
			}
	
			add_temporary_buffered_processed_polygon ( this_face->number_of_points, D3DSHADE_GOURAUD, &system_textures[TEXTURE_INDEX_SPHERICAL_MAP],
																			D3DFILTER_LINEAR,
																			D3DFILTER_NEAREST,
																			D3DTADDRESS_CLAMP,
																			D3DTADDRESS_CLAMP,
																			FALSE );
		}
		*/
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_gouraud_textured_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		ispecular,
		count;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	LPD3DTLVERTEX
		destination_vertices;

	object_3d_short_textured_point
		*texture_list;

	point_3d_plain_reference
		*gouraud_list;

	real_colour
		specular_colour;

	float
		specular;

	ASSERT ( current_object_3d_surface->polygons );

	transformed_points = transformed_3d_2d_points + object_base->points_base;

	texture_list = current_object_3d_texture_list;

	gouraud_list = current_object_3d_gouraud_list;

	if ( current_object_3d_texture->contains_alpha )
	{

		float
			distance;

		//
		// Should draw a gouraud shaded TRANSLUCENT polygon
		//

		distance = 0;

		destination_vertices = get_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;
			destination_vertices[count].color = current_object_3d_transformed_normals[gouraud_list->point].colour;

			specular = current_object_3d_transformed_normals[gouraud_list->point].specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;

			distance += vert->q;

			gouraud_list++;
			texture_list++;
		}

		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_GOURAUD, current_object_3d_texture,
																	current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																	current_object_3d_specular, FALSE );
	}
	else
	{

		//
		// Should draw a gouraud shaded polygon
		//

		commit_deferred_state_changes ();

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			real_colour
				specular_colour;

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;
			destination_vertices[count].color = current_object_3d_transformed_normals[gouraud_list->point].colour;

			specular = current_object_3d_transformed_normals[gouraud_list->point].specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;

			gouraud_list++;
			texture_list++;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
/*
//		if ( current_object_3d_surface->reflectivity != 0.0 )
		{
	
			int
				count;
	
			vec3d
				reflected_ray,
				camera_position;
	
			float
				model_x,
				model_y,
				model_z;

			real_colour
				this_colour;
	
			LPD3DTLVERTEX
				reflection_vertices;

			gouraud_list = current_object_3d_gouraud_list;

			reflection_vertices = get_temporary_translucent_polygon_vertices ();
	
			camera_position = object_base->camera_position;

			this_colour.red = 255;
			this_colour.green = 255;
			this_colour.blue = 255;
			this_colour.alpha = 192;
	
			//
			// Now get the u,v coordinates
			//
	
			for ( count = 0; count < this_face->number_of_points; count++ )
			{
	
				vec3d
					ray,
					*normal;

				double
					ndotr,
					denominator,
					u,
					v;

				normal = &objects_3d_data[object_base->object_number].point_normals[gouraud_list->point];

				model_x = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].x;
				model_y = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].y;
				model_z = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].z;

				ray.x = camera_position.x - model_x;
				ray.y = camera_position.y - model_y;
				ray.z = camera_position.z - model_z;

				normalise_any_3d_vector ( &ray );

				//
				// Reflection = 2.0 * ( Normal . Ray ) * Normal - Ray
				//

				ndotr = ( ray.x * normal->x + ray.y * normal->y + ray.z * normal->z ) * 2.0;

				reflected_ray.x = ndotr * normal->x - ray.x;
				reflected_ray.y = ndotr * normal->y - ray.y;
				reflected_ray.z = ndotr * normal->z - ray.z;

				normalise_any_3d_vector ( &reflected_ray );

				multiply_matrix3x3_vec3d ( &ray, object_base->object_vp->attitude, &reflected_ray );

				reflected_ray = ray;
	
				denominator = get_inverse_square_root ( 2.0 * ( reflected_ray.z + 1 ) );

				v = 0.5 + ( ( double ) reflected_ray.x * denominator ) / 2.0;
				u = 0.5 + ( ( double ) reflected_ray.y * denominator ) / 2.0;

				vert = transformed_points + current_object_3d_point_list[count].point;
		
				*( ( int * ) &reflection_vertices[count].sx ) = *( ( int * ) &vert->i );
				*( ( int * ) &reflection_vertices[count].sy ) = *( ( int * ) &vert->j );
				reflection_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
				reflection_vertices[count].rhw = vert->q;
				reflection_vertices[count].tu = v;
				reflection_vertices[count].tv = u;
				reflection_vertices[count].color = this_colour.colour;
				reflection_vertices[count].specular = d3d_fog_intensity;

				gouraud_list++;
			}

			add_temporary_buffered_processed_polygon ( this_face->number_of_points, D3DSHADE_GOURAUD, &system_textures[TEXTURE_INDEX_TERRAIN_SEA001],
																			D3DFILTER_LINEAR,
																			D3DFILTER_NEAREST,
																			D3DTADDRESS_CLAMP,
																			D3DTADDRESS_CLAMP,
																			FALSE );
		}
		*/
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_gouraud_textured_nospecular_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		count;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	LPD3DTLVERTEX
		destination_vertices;

	object_3d_short_textured_point
		*texture_list;

	point_3d_plain_reference
		*gouraud_list;

	ASSERT ( current_object_3d_surface->polygons );

	transformed_points = transformed_3d_2d_points + object_base->points_base;

	texture_list = current_object_3d_texture_list;

	gouraud_list = current_object_3d_gouraud_list;

	if ( current_object_3d_texture->contains_alpha )
	{

		float
			distance;

		//
		// Should draw a gouraud shaded TRANSLUCENT polygon
		//

		distance = 0;

		destination_vertices = get_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;
			destination_vertices[count].color = current_object_3d_transformed_normals[gouraud_list->point].colour;
			destination_vertices[count].specular = d3d_fog_intensity;

			distance += vert->q;

			gouraud_list++;
			texture_list++;
		}

		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_GOURAUD, current_object_3d_texture,
																	current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																	current_object_3d_specular, FALSE );
	}
	else
	{

		//
		// Commit renderstates, and inline the first 3 vertices data copying
		//

		commit_deferred_state_changes ();

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
	
		vert = transformed_points + current_object_3d_point_list[0].point;
		destination_vertices[0].sx = vert->i;
		destination_vertices[0].sy = vert->j;
		destination_vertices[0].rhw = vert->q;
		destination_vertices[0].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[0].tu = texture_list[0].u;
		destination_vertices[0].tv = texture_list[0].v;
		destination_vertices[0].color = current_object_3d_transformed_normals[gouraud_list[0].point].colour;
		destination_vertices[0].specular = d3d_fog_intensity;

		vert = transformed_points + current_object_3d_point_list[1].point;
		destination_vertices[1].sx = vert->i;
		destination_vertices[1].sy = vert->j;
		destination_vertices[1].rhw = vert->q;
		destination_vertices[1].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[1].tu = texture_list[1].u;
		destination_vertices[1].tv = texture_list[1].v;
		destination_vertices[1].color = current_object_3d_transformed_normals[gouraud_list[1].point].colour;
		destination_vertices[1].specular = d3d_fog_intensity;

		vert = transformed_points + current_object_3d_point_list[2].point;
		destination_vertices[2].sx = vert->i;
		destination_vertices[2].sy = vert->j;
		destination_vertices[2].rhw = vert->q;
		destination_vertices[2].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
		destination_vertices[2].tu = texture_list[2].u;
		destination_vertices[2].tv = texture_list[2].v;
		destination_vertices[2].color = current_object_3d_transformed_normals[gouraud_list[2].point].colour;
		destination_vertices[2].specular = d3d_fog_intensity;

		gouraud_list+=3;
		texture_list+=3;

		for ( count = 3; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;
			destination_vertices[count].color = current_object_3d_transformed_normals[gouraud_list->point].colour;
			destination_vertices[count].specular = d3d_fog_intensity;


			gouraud_list++;
			texture_list++;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	real_colour
		colour,
		specular_colour;

	ASSERT ( current_object_3d_surface->polygons );

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( &colour );
	
		specular_colour.colour = d3d_fog_intensity;
	}
	else
	{

		float
			red,
			green,
			blue,
			specular;

		int
			ir,
			ig,
			ib,
			ispecular;

		//
		// Look up the colour of the face normal
		//
	
		red = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].r;
		green = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].g;
		blue = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].b;
		specular = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;
	
		red /= 255.0;
		green /= 255.0;
		blue /= 255.0;
	
		asm_convert_float_to_int ( ( red * current_object_3d_surface->red ), &ir );
		asm_convert_float_to_int ( ( green * current_object_3d_surface->green ), &ig );
		asm_convert_float_to_int ( ( blue * current_object_3d_surface->blue ), &ib );
		asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
	
		colour.red = ir;
		colour.green = ig;
		colour.blue = ib;

		specular_colour.colour = d3d_fog_intensity;
		specular_colour.red = ispecular;
		specular_colour.green = ispecular;
		specular_colour.blue = ispecular;
	}

	{

		int
			imixed_dissolve;

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &imixed_dissolve );

		colour.alpha = imixed_dissolve;
	}

	if ( current_object_3d_surface->translucent )
	{

		poly = construct_3d_vertex_polygon ( this_face->number_of_points,
																	NULL,	//current_object_3d_point_list,
																	object_base->points_base );

		buffer_zbuffered_plain_polygon ( poly, colour, specular_colour, current_object_3d_surface->additive );
	}
	else
	{

		int
			count;
	
		LPD3DTLVERTEX
			destination_vertices;

		object_transformed_2d_point
			*vert,
			*transformed_points;

		commit_deferred_state_changes ();

		transformed_points = transformed_3d_2d_points + object_base->points_base;

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
	}
	
/*
	if ( current_object_3d_surface->reflectivity != 0.0 )
	{

		matrix3x3
			reflection_matrix;

		int
			count,
			normal_index;

		vec3d
			reflected_ray,
			camera_position;

		float
			model_x,
			model_y,
			model_z,
			u,
			v;

		vertex
			*this_point;

		real_colour
			this_colour;

		normal_index = current_object_3d_face_normal_list->point;

		get_reflection_matrix ( reflection_matrix, &objects_3d_data[object_base->object_number].point_normals[normal_index] );

		camera_position = object_base->camera_position;

		//
		// Now get the u,v coordinates
		//

		this_point = poly;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vec3d
				ray;

			model_x = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].x;
			model_y = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].y;
			model_z = objects_3d_data[object_base->object_number].points[current_object_3d_point_list[count].point].z;
	
			ray.x = camera_position.x - model_x;
			ray.y = camera_position.y - model_y;
			ray.z = camera_position.z - model_z;

			multiply_matrix3x3_vec3d ( &reflected_ray, reflection_matrix, &ray );
	
			normalise_any_3d_vector ( &reflected_ray );
	
			u = atan2 ( reflected_ray.x, reflected_ray.z );
			v = asin ( reflected_ray.y );

			this_point->u = u / PI2;
			this_point->v = v / PI2;

			this_point = this_point->next_vertex;
		}

		this_colour.red = 255;
		this_colour.green = 255;
		this_colour.blue = 255;
		this_colour.alpha = 255;

		buffer_sorted_translucent_flat_shaded_textured_polygon ( poly, &system_textures[TEXTURE_INDEX_SPHERMAP],
																					D3DFILTER_LINEAR, D3DFILTER_NEAREST, D3DTADDRESS_WRAP,
																					this_colour, FALSE );
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_gouraud_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	//
	// The face is a true polygon - triangle or above
	//

	ASSERT ( current_object_3d_surface->polygons );

	{

		float
			surface_red,
			surface_green,
			surface_blue,
			surface_specular;

		surface_red = ( ( float ) current_object_3d_surface->red ) / 255.0;
		surface_green = ( ( float ) current_object_3d_surface->green ) / 255.0;
		surface_blue = ( ( float ) current_object_3d_surface->blue ) / 255.0;

		if ( current_object_3d_specular )
		{
	
			surface_specular = ( float ) current_object_3d_surface->specularity;
		}
		else
		{
	
			surface_specular = 0;
		}

		if ( !current_object_3d_surface->translucent )
		{

			int
				count;
		
			int
				r,
				g,
				b;
		
			float
				red,
				green,
				blue;

			LPD3DTLVERTEX
				destination_vertices;

			object_transformed_2d_point
				*vert,
				*transformed_points;
	
			point_3d_plain_reference
				*gouraud_list;
		
			commit_deferred_state_changes ();

			transformed_points = transformed_3d_2d_points + object_base->points_base;
	
			destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

			gouraud_list = current_object_3d_gouraud_list;
		
			for ( count = 0; count < this_face->number_of_points; count++ )
			{

				vert = transformed_points + current_object_3d_point_list[count].point;
			
				*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
				*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
				destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
				destination_vertices[count].rhw = vert->q;

				red = ( current_object_3d_transformed_normals[gouraud_list->point].r * surface_red ) + FLOAT_FLOAT_FACTOR;
				green = ( current_object_3d_transformed_normals[gouraud_list->point].g * surface_green ) + FLOAT_FLOAT_FACTOR;
				blue = ( current_object_3d_transformed_normals[gouraud_list->point].b * surface_blue ) + FLOAT_FLOAT_FACTOR;

				r = ( *( int * ) &red ) - INTEGER_FLOAT_FACTOR;
				g = ( *( int * ) &green ) - INTEGER_FLOAT_FACTOR;
				b = ( *( int * ) &blue ) - INTEGER_FLOAT_FACTOR;

				destination_vertices[count].color = RGB_MAKE ( r, g, b );

				destination_vertices[count].specular = d3d_fog_intensity;

				gouraud_list++;
			}
		
			draw_fan_primitive ( this_face->number_of_points, destination_vertices );
		}
		else
		{
		
			int
				triangle_count,
				polygon_alpha;
	
			asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &polygon_alpha );

			for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
			{
		
				//
				// Should draw a translucent gouraud shaded polygon
				//
		
				poly = construct_3d_vertex_unclipped_gouraud_triangle_fan ( triangle_count,
																									surface_specular,
																									NULL,	//current_object_3d_point_list,
																									current_object_3d_gouraud_list,
																									object_base->points_base );
		
				buffer_zbuffered_gouraud_shaded_polygon ( poly, surface_red, surface_green, surface_blue, polygon_alpha,
																		surface_specular, current_object_3d_surface->additive );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_white_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	real_colour
		colour,
		specular_colour;

	ASSERT ( current_object_3d_surface->polygons );

	if ( current_object_3d_surface->luminous )
	{

		calculate_luminous_colour ( &colour );
	
		specular_colour.colour = d3d_fog_intensity;
	}
	else
	{

		//
		// Look up the colour of the face normal
		//
	
		colour.red = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].r;
		colour.green = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].g;
		colour.blue = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].b;
	
		specular_colour.colour = d3d_fog_intensity;
	}

	{

		int
			imixed_dissolve;

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &imixed_dissolve );

		colour.alpha = imixed_dissolve;
	}

	if ( current_object_3d_surface->translucent )
	{

		poly = construct_3d_vertex_polygon ( this_face->number_of_points,
																NULL,	//current_object_3d_point_list,
																object_base->points_base );

		buffer_zbuffered_plain_polygon ( poly, colour, specular_colour, current_object_3d_surface->additive );
	}
	else
	{

		int
			count;
	
		LPD3DTLVERTEX
			destination_vertices;

		object_transformed_2d_point
			*vert,
			*transformed_points;

		commit_deferred_state_changes ();

		transformed_points = transformed_3d_2d_points + object_base->points_base;

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_gouraud_white_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	//
	// The face is a true polygon - triangle or above
	//

	ASSERT ( current_object_3d_surface->polygons );

	{

		if ( !current_object_3d_surface->translucent )
		{

			int
				count;
		
			LPD3DTLVERTEX
				destination_vertices;

			object_transformed_2d_point
				*vert,
				*transformed_points;
	
			point_3d_plain_reference
				*gouraud_list;
		
			commit_deferred_state_changes ();

			transformed_points = transformed_3d_2d_points + object_base->points_base;
	
			destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

			gouraud_list = current_object_3d_gouraud_list;
		
			for ( count = 0; count < this_face->number_of_points; count++ )
			{

				vert = transformed_points + current_object_3d_point_list[count].point;
			
				*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
				*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
				destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
				destination_vertices[count].rhw = vert->q;
				destination_vertices[count].color = current_object_3d_transformed_normals[gouraud_list->point].colour;
				destination_vertices[count].specular = d3d_fog_intensity;

				gouraud_list++;
			}
		
			draw_fan_primitive ( this_face->number_of_points, destination_vertices );
		}
		else
		{
		
			int
				triangle_count,
				polygon_alpha;
	
			asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &polygon_alpha );

			for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
			{
		
				//
				// Should draw a translucent gouraud shaded polygon
				//
		
				poly = construct_3d_vertex_unclipped_gouraud_triangle_fan ( triangle_count,
																									0,
																									NULL,	//current_object_3d_point_list,
																									current_object_3d_gouraud_list,
																									object_base->points_base );
		
				buffer_zbuffered_gouraud_shaded_polygon ( poly, 1, 1, 1, polygon_alpha, 0, current_object_3d_surface->additive );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	real_colour
		colour,
		lightmap_colour,
		specular_colour;

	ASSERT ( current_object_3d_surface->polygons );

	specular_colour.colour = d3d_fog_intensity;

	if ( current_object_3d_surface->luminous )
	{
	
		colour.red = current_object_3d_surface->red;
		colour.green = current_object_3d_surface->green;
		colour.blue = current_object_3d_surface->blue;
		colour.alpha = current_object_3d_dissolve_value;
	}
	else
	{

		float
			specular;

		int
			ispecular;

		//
		// Look up the colour of the face normal
		//

		colour.colour = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].colour;
		colour.alpha = current_object_3d_dissolve_value;

		//
		// Construct the specular colour
		//
	
		specular = current_object_3d_transformed_normals[current_object_3d_face_normal_list->point].specular;
	
		asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
	
		specular_colour.colour = d3d_fog_intensity;
		specular_colour.red = ispecular;
		specular_colour.green = ispecular;
		specular_colour.blue = ispecular;
	}

	//
	// Now figure out the lightmap colours
	//

	lightmap_colour.red = current_object_3d_surface->red;
	lightmap_colour.green = current_object_3d_surface->green;
	lightmap_colour.blue = current_object_3d_surface->blue;
	lightmap_colour.alpha = 255;

	calculate_lightmap_luminous_colour ( &lightmap_colour );

	if ( current_object_3d_texture->contains_alpha )
	{

		int
			count;

		object_transformed_2d_point
			*vert,
			*transformed_points;
	
		LPD3DTLVERTEX
			destination_vertices,
			lightmap_vertices;
	
		object_3d_short_textured_point
			*texture_list,
			*luminosity_texture_list;

		float
			distance;

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_translucent_polygon_vertices ();
	
		lightmap_vertices = get_temporary_translucent_polygon_vertices ();
	
		texture_list = current_object_3d_texture_list;

		luminosity_texture_list = texture_list + this_face->number_of_points;

		distance = 0;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
			destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;

			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;

			lightmap_vertices[count].tu = luminosity_texture_list->u;
			lightmap_vertices[count].tv = luminosity_texture_list->v;

			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;
			lightmap_vertices[count].color = lightmap_colour.colour;
			lightmap_vertices[count].specular = d3d_fog_intensity;


			distance += vert->q;

			texture_list++;
			luminosity_texture_list++;
		}
	
		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_FLAT, current_object_3d_texture,
																	current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																	current_object_3d_specular, FALSE );

		if ( current_object_3d_light_maps_enabled )
		{

			add_temporary_buffered_processed_polygon ( this_face->number_of_points, current_object_3d_luminosity_texture,
																			current_object_3d_luminosity_texture_filter,
																			current_object_3d_luminosity_texture_mipmap,
																			current_object_3d_luminosity_texture_u_address,
																			current_object_3d_luminosity_texture_v_address,
																			TRUE );
		}
	}
	else
	{

		int
			count;
	
		object_transformed_2d_point
			*vert,
			*transformed_points;
	
		LPD3DTLVERTEX
			destination_vertices,
			lightmap_vertices;
	
		object_3d_short_textured_point
			*texture_list,
			*luminosity_texture_list;

		//
		// Should draw a flat shaded polygon - with a lightmap
		//

		commit_deferred_state_changes ();

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

		lightmap_vertices = get_temporary_translucent_polygon_vertices ();
	
		texture_list = current_object_3d_texture_list;

		luminosity_texture_list = texture_list + this_face->number_of_points;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
			destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;

			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;

			lightmap_vertices[count].tu = luminosity_texture_list->u;
			lightmap_vertices[count].tv = luminosity_texture_list->v;

			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;

			lightmap_vertices[count].color = lightmap_colour.colour;
			lightmap_vertices[count].specular = d3d_fog_intensity;

			texture_list++;
			luminosity_texture_list++;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );

		if ( current_object_3d_light_maps_enabled )
		{

			add_temporary_buffered_processed_polygon ( this_face->number_of_points, current_object_3d_luminosity_texture,
																			current_object_3d_luminosity_texture_filter,
																			current_object_3d_luminosity_texture_mipmap,
																			current_object_3d_luminosity_texture_u_address,
																			current_object_3d_luminosity_texture_v_address,
																			TRUE );
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_gouraud_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		ispecular,
		count;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	LPD3DTLVERTEX
		destination_vertices,
		lightmap_vertices;

	object_3d_short_textured_point
		*texture_list,
		*luminosity_texture_list;

	point_3d_plain_reference
		*gouraud_list;

	real_colour
		specular_colour;

	float
		specular;

	real_colour
		lightmap_colour;

	ASSERT ( current_object_3d_surface->polygons );

	//
	// Figure out the lightmap colours
	//

	lightmap_colour.red = current_object_3d_surface->red;
	lightmap_colour.green = current_object_3d_surface->green;
	lightmap_colour.blue = current_object_3d_surface->blue;
	lightmap_colour.alpha = 255;

	calculate_lightmap_luminous_colour ( &lightmap_colour );

	transformed_points = transformed_3d_2d_points + object_base->points_base;

	texture_list = current_object_3d_texture_list;

	luminosity_texture_list = texture_list + this_face->number_of_points;

	gouraud_list = current_object_3d_gouraud_list;

	if ( current_object_3d_texture->contains_alpha )
	{

		float
			distance;

		real_colour
			translucent_colour;

		//
		// Should draw a gouraud shaded TRANSLUCENT polygon
		//

		distance = 0;

		destination_vertices = get_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;
			translucent_colour.colour = current_object_3d_transformed_normals[gouraud_list->point].colour;
			translucent_colour.alpha = current_object_3d_dissolve_value;
			destination_vertices[count].color = translucent_colour.colour;

			specular = current_object_3d_transformed_normals[gouraud_list->point].specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;

			distance += vert->q;

			gouraud_list++;
			texture_list++;
		}

		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_GOURAUD, current_object_3d_texture,
																	current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																	current_object_3d_specular, FALSE );
	}
	else
	{

		//
		// Should draw a flat shaded polygon - with a lightmap
		//

		commit_deferred_state_changes ();

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
	
		lightmap_vertices = get_temporary_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			vert = transformed_points + current_object_3d_point_list[count].point;
		
			destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
			destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
			destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;

			destination_vertices[count].tu = texture_list->u;
			destination_vertices[count].tv = texture_list->v;

			lightmap_vertices[count].tu = luminosity_texture_list->u;
			lightmap_vertices[count].tv = luminosity_texture_list->v;

			destination_vertices[count].color = current_object_3d_transformed_normals[gouraud_list->point].colour;
			lightmap_vertices[count].color = lightmap_colour.colour;

			specular = current_object_3d_transformed_normals[gouraud_list->point].specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;
			lightmap_vertices[count].specular = d3d_fog_intensity;

			gouraud_list++;
			texture_list++;
			luminosity_texture_list++;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );

		if ( current_object_3d_light_maps_enabled )
		{

			add_temporary_buffered_processed_polygon ( this_face->number_of_points, current_object_3d_luminosity_texture,
																			current_object_3d_luminosity_texture_filter,
																			current_object_3d_luminosity_texture_mipmap,
																			current_object_3d_luminosity_texture_u_address,
																			current_object_3d_luminosity_texture_v_address,
																			TRUE );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_textured_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	int
		outcode;


	ASSERT ( !current_object_3d_surface->polygons );

	clip_3d_coord = 0;

	line = construct_3d_vertex_textured_line ( NULL, //current_object_3d_point_list,
																current_object_3d_texture_list, object_base->points_base, &outcode );

	if ( !line )
	{

		return;
	}

	if ( outcode & CLIP_HITHER )
	{

		line = hither_clip_3d_polygon ( line, &outcode );

		if ( !line )
		{

			return;
		}
	}

	if ( outcode )
	{

		apply_perspective_to_polygon_texture ( line );
				
		line = clip_3d_polygon ( line, outcode );

		if ( !line )
		{

			return;
		}

		remove_perspective_from_polygon_texture ( line );
	}


	if ( current_object_3d_surface->smoothed )
	{

		commit_deferred_state_changes ();

		draw_zbuffered_gouraud_shaded_textured_line ( line, &system_textures[current_object_3d_surface->texture_index] );
	}
	else
	{

		real_colour
			colour;

		if ( current_object_3d_surface->luminous )
		{

			calculate_luminous_colour ( &colour );

			colour.alpha = 255;
		}
		else
		{

			colour = calculate_line_colour ( object_base );
		}

		if ( current_object_3d_surface->additive )
		{

			buffer_zbuffered_flat_shaded_textured_line ( line, &system_textures[current_object_3d_surface->texture_index],
																		current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																		current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																		colour, TRUE );
		}
		else
		{
	
			commit_deferred_state_changes ();

			draw_zbuffered_flat_shaded_textured_line ( line, &system_textures[current_object_3d_surface->texture_index], colour );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_plain_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	int
		outcode;

	ASSERT ( !current_object_3d_surface->polygons );

	clip_3d_coord = 0;

	line = construct_3d_vertex_line ( NULL, //current_object_3d_point_list,
													object_base->points_base, &outcode );

	if ( !line )
	{

		return;
	}

	if ( outcode & CLIP_HITHER )
	{

		line = hither_clip_3d_polygon ( line, &outcode );

		if ( !line )
		{

			return;
		}
	}

	if ( outcode )
	{

		line = clip_3d_polygon ( line, outcode );

		if ( !line )
		{

			return;
		}
	}

	if ( current_object_3d_surface->smoothed )
	{

		commit_deferred_state_changes ();

		draw_zbuffered_gouraud_shaded_line ( line, current_object_3d_surface->red, current_object_3d_surface->green, current_object_3d_surface->blue );
	}
	else
	{

		real_colour
			colour;

		colour = calculate_line_colour ( object_base );

		commit_deferred_state_changes ();

		draw_zbuffered_plain_line ( line, colour );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_clipped_3d_object_plain_white_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	int
		outcode;

	ASSERT ( !current_object_3d_surface->polygons );

	clip_3d_coord = 0;

	line = construct_3d_vertex_line ( NULL,	//current_object_3d_point_list,
												object_base->points_base, &outcode );

	if ( !line )
	{

		return;
	}

	if ( outcode & CLIP_HITHER )
	{

		line = hither_clip_3d_polygon ( line, &outcode );

		if ( !line )
		{

			return;
		}
	}

	if ( outcode )
	{

		line = clip_3d_polygon ( line, outcode );

		if ( !line )
		{

			return;
		}
	}

	if ( current_object_3d_surface->smoothed )
	{

		commit_deferred_state_changes ();

		draw_zbuffered_gouraud_shaded_line ( line, 255, 255, 255 );
	}
	else
	{

		real_colour
			colour;

		colour = calculate_line_colour ( object_base );

		commit_deferred_state_changes ();

		draw_zbuffered_plain_line ( line, colour );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_textured_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	ASSERT ( !current_object_3d_surface->polygons );

	clip_3d_coord = 0;

	line = construct_3d_vertex_unclipped_textured_line ( NULL, //current_object_3d_point_list,
																			current_object_3d_texture_list, object_base->points_base );

	if ( current_object_3d_surface->smoothed )
	{

		commit_deferred_state_changes ();

		draw_zbuffered_gouraud_shaded_textured_line ( line, &system_textures[current_object_3d_surface->texture_index] );
	}
	else
	{

		real_colour
			colour;

		if ( current_object_3d_surface->luminous )
		{

			calculate_luminous_colour ( &colour );
		}
		else
		{

			colour = calculate_line_colour ( object_base );
		}

		if ( current_object_3d_surface->additive )
		{

			buffer_zbuffered_flat_shaded_textured_line ( line, &system_textures[current_object_3d_surface->texture_index],
																		current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																		current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																		colour, TRUE );
		}
		else
		{
	
			commit_deferred_state_changes ();

			draw_zbuffered_flat_shaded_textured_line ( line, &system_textures[current_object_3d_surface->texture_index], colour );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_plain_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	ASSERT ( !current_object_3d_surface->polygons );

	clip_3d_coord = 0;

	commit_deferred_state_changes ();

	line = construct_3d_vertex_unclipped_line ( NULL,	//current_object_3d_point_list,
																object_base->points_base );

	if ( current_object_3d_surface->smoothed )
	{

		draw_zbuffered_gouraud_shaded_line ( line, current_object_3d_surface->red, current_object_3d_surface->green, current_object_3d_surface->blue );
	}
	else
	{

		real_colour
			colour;

		colour = calculate_line_colour (  object_base );

		draw_zbuffered_plain_line ( line, colour );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_plain_white_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	ASSERT ( !current_object_3d_surface->polygons );

	clip_3d_coord = 0;

	commit_deferred_state_changes ();

	line = construct_3d_vertex_unclipped_line ( NULL,	//current_object_3d_point_list,
																object_base->points_base );

	if ( current_object_3d_surface->smoothed )
	{

		draw_zbuffered_gouraud_shaded_line ( line, 255, 255, 255 );
	}
	else
	{

		real_colour
			colour;

		colour = calculate_line_colour ( object_base );

		draw_zbuffered_plain_line ( line, colour );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_3d_shadow_surface_plain_polygon ( object_3d_face *this_face, int surface_index, int reference_offset, struct OBJECT_3D_INFO *object_base )
{

	face_surface_description
		*surface;

	vertex
		*poly;

	int
		outcode;

	point_3d_plain_reference
		*point_list;

	surface = &objects_3d_data[ object_base->object_number ].surfaces[surface_index];

	//
	// The face is a true polygon - triangle or above
	//

	ASSERT ( surface->polygons );

	if ( surface->detail )
	{

		return;
	}

	point_list = NULL;	//objects_3d_data[object_base->object_number].object_faces_point_plain_list;

	point_list += reference_offset;

	if ( !outcode_3d_polygon ( this_face->number_of_points, point_list, object_base->points_base, &outcode ) )
	{

		if ( outcode == 0 )
		{
	
			int
				count;
		
			vertex
				*vert;
		
			LPD3DTLVERTEX
				destination_vertices;
		
			vertex
				*transformed_points;
		
			//
			// Should draw a gouraud shaded polygon
			//
	
			set_d3d_plain_renderstate ();

			transformed_points = &transformed_3d_points[object_base->points_base];
		
			destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
		
			for ( count = 0; count < this_face->number_of_points; count++ )
			{

				vert = &transformed_points[ point_list[count].point ];
			
				destination_vertices[count].sx = vert->i;
				destination_vertices[count].sy = vert->j;
				destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
				destination_vertices[count].rhw = vert->q;
				destination_vertices[count].color = polygon_shadow_colour;
				destination_vertices[count].specular = d3d_fog_intensity;
			}
		
			draw_fan_primitive ( this_face->number_of_points, destination_vertices );
		}
		else
		{

			int
				triangle_count;
	
			for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
			{
			
		
				poly = construct_3d_triangle_fan ( triangle_count, point_list, object_base->points_base, &outcode );
			
				if ( !poly )
				{
			
					continue;
				}
			
				if ( outcode )
				{
			
					clip_3d_coord = 0;
			
					if ( outcode & CLIP_HITHER )
					{
				
						poly = hither_clip_3d_polygon ( poly, &outcode );
			
						if ( !poly )
						{
			
							continue;
						}
					}
				
					if ( outcode )
					{
				
						poly = clip_3d_polygon ( poly, outcode );
			
						if ( !poly )
						{
			
							continue;
						}
					}
				}
			
				draw_zbuffered_shadow_polygon ( poly, 0, 0, 0 );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_3d_shadow_surface_alpha_textured_polygon ( object_3d_face *this_face, face_surface_description *surface, int reference_offset, int texture_offset, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*poly;

	int
		outcode;

	point_3d_plain_reference
		*point_list;

	object_3d_short_textured_point
		*texture_list;

	texture_map
		*texture;

	ASSERT ( surface->polygons );

	if ( surface->detail )
	{

		return;
	}

	point_list = NULL;	//objects_3d_data[object_base->object_number].object_faces_point_plain_list;

	point_list += reference_offset;

	texture_list = NULL;	//objects_3d_data[object_base->object_number].object_faces_texture_point_list;

	texture_list += texture_offset;

	if ( surface->texture_animation )
	{

		int
			frame;

		frame = texture_animations[surface->texture_index].current_frame;

		texture = &system_textures[ texture_animations[surface->texture_index].texture_indices[frame] ];
	}
	else
	{

		texture = &system_textures[surface->texture_index];
	}

	if ( !outcode_3d_polygon ( this_face->number_of_points, point_list, object_base->points_base, &outcode ) )
	{

		if ( outcode == 0 )
		{
	
			int
				count;
		
			vertex
				*vert;
		
			LPD3DTLVERTEX
				destination_vertices;
		
			vertex
				*transformed_points;
		
			//
			// Should draw a gouraud shaded polygon
			//
	
			set_d3d_flat_shaded_textured_renderstate ( texture );

			transformed_points = &transformed_3d_points[object_base->points_base];
		
			destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
		
			for ( count = 0; count < this_face->number_of_points; count++ )
			{

				vert = &transformed_points[ point_list[count].point ];
			
				destination_vertices[count].sx = vert->i;
				destination_vertices[count].sy = vert->j;
				destination_vertices[count].sz = ( vert->z * zbuffer_factor ) + zbuffer_constant;
				destination_vertices[count].rhw = vert->q;
				destination_vertices[count].tu = texture_list->u;
				destination_vertices[count].tv = texture_list->v;
				destination_vertices[count].color = polygon_shadow_colour;
				destination_vertices[count].specular = d3d_fog_intensity;

				texture_list++;
			}
		
			draw_fan_primitive ( this_face->number_of_points, destination_vertices );
		}
		else
		{
	
			int
				triangle_count;
	
			for ( triangle_count = 0; triangle_count < ( this_face->number_of_points - 2 ); triangle_count++ )
			{
			
		
				poly = construct_3d_textured_triangle_fan ( triangle_count, point_list, texture_list, object_base->points_base, &outcode );
			
				if ( !poly )
				{
			
					continue;
				}
			
				if ( outcode )
				{
			
					clip_3d_coord = 0;
			
					if ( outcode & CLIP_HITHER )
					{
				
						poly = hither_clip_3d_polygon ( poly, &outcode );
			
						if ( !poly )
						{
			
							continue;
						}
					}
				
					if ( outcode )
					{

						apply_perspective_to_polygon_texture ( poly );

						poly = clip_3d_polygon ( poly, outcode );
			
						if ( !poly )
						{
			
							continue;
						}

						remove_perspective_from_polygon_texture ( poly );
					}
				}
			
				set_d3d_flat_shaded_textured_renderstate ( texture );

				draw_zbuffered_shadow_textured_polygon ( poly, texture );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
