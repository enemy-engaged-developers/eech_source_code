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

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Render lightmap polygons. Several rules with lightmaps:
//
// The base polygon they are on cannot be additive ( but may be translucent/luminous )
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void calculate_lightmap_luminous_colour ( real_colour *colour );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculate_lightmap_luminous_colour ( real_colour *colour )
{

	float
		red,
		green,
		blue;

	int
		ired,
		igreen,
		iblue;

	if ( active_3d_environment->infrared_mode == INFRARED_ON )
	{
	
		float
			grey;
	
		red = current_object_3d_surface->red;
		green = current_object_3d_surface->green;
		blue = current_object_3d_surface->blue;

		grey = red * 0.3 + green * 0.59 + blue * 0.11;
		grey *= current_object_3d_dissolve_factor;

		asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.red ), &ired );
		asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.green ), &igreen );
		asm_convert_float_to_int ( ( grey * ambient_3d_light.colour.blue ), &iblue );

		colour->red = ired;
		colour->green = igreen;
		colour->blue = iblue;
	}
	else
	{
	
		red = current_object_3d_surface->red;
		green = current_object_3d_surface->green;
		blue = current_object_3d_surface->blue;

		asm_convert_float_to_int ( ( red * current_object_3d_dissolve_factor ), &ired );
		asm_convert_float_to_int ( ( green * current_object_3d_dissolve_factor ), &igreen );
		asm_convert_float_to_int ( ( blue * current_object_3d_dissolve_factor ), &iblue );

		colour->red = ired;
		colour->green = igreen;
		colour->blue = iblue;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_clipped_3d_object_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
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
																					current_object_3d_point_list,
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
		
				buffer_sorted_translucent_flat_shaded_textured_polygon ( poly, current_object_3d_texture,
																								current_object_3d_texture_filter,
																								current_object_3d_texture_mipmap,
																								current_object_3d_texture_u_address,
																								current_object_3d_texture_v_address,
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
					destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
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

void render_clipped_3d_object_gouraud_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
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
																								current_object_3d_point_list,
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

				buffer_sorted_translucent_gouraud_shaded_textured_polygon ( poly, current_object_3d_texture,
																								current_object_3d_texture_filter,
																								current_object_3d_texture_mipmap,
																								current_object_3d_texture_u_address,
																								current_object_3d_texture_v_address,
																								current_object_3d_specular,
																								FALSE );
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
						destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
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

void render_unclipped_3d_object_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	real_colour
		colour,
		lightmap_colour,
		specular_colour;

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
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
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

		add_translucent_sorted_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_FLAT, current_object_3d_texture,
																	current_object_3d_texture_filter,
																	current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address,
																	current_object_3d_texture_v_address,
																	current_object_3d_specular,
																	FALSE );

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
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
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

void render_unclipped_3d_object_gouraud_textured_lightmap_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
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
			destination_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
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

		add_translucent_sorted_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_GOURAUD, current_object_3d_texture,
																	current_object_3d_texture_filter,
																	current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address,
																	current_object_3d_texture_v_address,
																	current_object_3d_specular,
																	FALSE );
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
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->q * zbuffer_factor ) + zbuffer_constant;
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

