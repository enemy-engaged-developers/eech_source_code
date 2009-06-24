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

void zrender_unclipped_3d_object_textured_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	real_colour
		colour;

	real_colour
		specular_colour;

	int
		surface_point_index;

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
	
		float
			distance;

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_translucent_polygon_vertices ();
	
		distance = 0;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;

			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;

			distance += vert->q;
		}
	
		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_FLAT, current_object_3d_texture,
																	current_object_3d_texture_filter,
																	current_object_3d_texture_mipmap,
																	current_object_3d_texture_u_address,
																	current_object_3d_texture_v_address,
																	current_object_3d_specular,
																	current_object_3d_surface->additive );
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
	
		commit_deferred_state_changes ();

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;

			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_gouraud_textured_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		surface_point_index,
		ispecular,
		count;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	LPD3DTLVERTEX
		destination_vertices;

	real_colour
		specular_colour;

	float
		specular;

	ASSERT ( current_object_3d_surface->polygons );

	transformed_points = transformed_3d_2d_points + object_base->points_base;

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

			object_3d_transformed_point_normal
				*normal;

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];

			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
			destination_vertices[count].color = normal->colour;

			specular = normal->specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;

			distance += vert->q;
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

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;

			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
			destination_vertices[count].color = current_object_3d_transformed_normals[current_object_3d_surface_point_normal_list[surface_point_index].point].colour;

			specular = current_object_3d_transformed_normals[current_object_3d_surface_point_normal_list[surface_point_index].point].specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_gouraud_textured_nospecular_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	int
		surface_point_index,
		count;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	LPD3DTLVERTEX
		destination_vertices;

	ASSERT ( current_object_3d_surface->polygons );

	transformed_points = transformed_3d_2d_points + object_base->points_base;

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

			object_3d_transformed_point_normal
				*normal;

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];

			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
			destination_vertices[count].color = normal->colour;
			destination_vertices[count].specular = d3d_fog_intensity;

			distance += vert->q;
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
	
		surface_point_index = current_object_3d_point_list[0].point;
		vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
		destination_vertices[0].sx = vert->i;
		destination_vertices[0].sy = vert->j;
		destination_vertices[0].rhw = vert->q;
		destination_vertices[0].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
		destination_vertices[0].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
		destination_vertices[0].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
		destination_vertices[0].color = current_object_3d_transformed_normals[current_object_3d_surface_point_normal_list[surface_point_index].point].colour;
		destination_vertices[0].specular = d3d_fog_intensity;

		surface_point_index = current_object_3d_point_list[1].point;
		vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
		destination_vertices[1].sx = vert->i;
		destination_vertices[1].sy = vert->j;
		destination_vertices[1].rhw = vert->q;
		destination_vertices[1].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
		destination_vertices[1].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
		destination_vertices[1].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
		destination_vertices[1].color = current_object_3d_transformed_normals[current_object_3d_surface_point_normal_list[surface_point_index].point].colour;
		destination_vertices[1].specular = d3d_fog_intensity;

		surface_point_index = current_object_3d_point_list[2].point;
		vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
		destination_vertices[2].sx = vert->i;
		destination_vertices[2].sy = vert->j;
		destination_vertices[2].rhw = vert->q;
		destination_vertices[2].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
		destination_vertices[2].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
		destination_vertices[2].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
		destination_vertices[2].color = current_object_3d_transformed_normals[current_object_3d_surface_point_normal_list[surface_point_index].point].colour;
		destination_vertices[2].specular = d3d_fog_intensity;

		for ( count = 3; count < this_face->number_of_points; count++ )
		{

			object_3d_transformed_point_normal
				*normal;

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];

			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_point_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_point_index].v;
			destination_vertices[count].color = normal->colour;
			destination_vertices[count].specular = d3d_fog_intensity;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void zrender_unclipped_3d_object_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	real_colour
		colour,
		specular_colour;

	LPD3DTLVERTEX
		destination_vertices;

	int
		count,
		surface_point_index;

	object_transformed_2d_point
		*vert,
		*transformed_points;

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

		float
			distance;

		//
		// Should draw a plain shaded TRANSLUCENT polygon
		//

		distance = 0;

		transformed_points = transformed_3d_2d_points + object_base->points_base;

		destination_vertices = get_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;

			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = d3d_fog_intensity;

			distance += vert->q;
		}

		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_FLAT, NULL, 0, 0, 0, 0, 0, FALSE );
	}
	else
	{

		commit_deferred_state_changes ();

		transformed_points = transformed_3d_2d_points + object_base->points_base;

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
		
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
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

void zrender_unclipped_3d_object_gouraud_polygon ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	LPD3DTLVERTEX
		destination_vertices;

	object_transformed_2d_point
		*vert,
		*transformed_points;

	int
		ispecular,
		r,
		g,
		b,
		count,
		surface_point_index;

	float
		red,
		green,
		blue;

	float
		surface_red,
		surface_green,
		surface_blue,
		surface_specular,
		specular;

	real_colour
		specular_colour;

	//
	// The face is a true polygon - triangle or above
	//

	ASSERT ( current_object_3d_surface->polygons );

	transformed_points = transformed_3d_2d_points + object_base->points_base;
	
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

		commit_deferred_state_changes ();

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			object_3d_transformed_point_normal
				*normal;

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];
		
			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			red = ( normal->r * surface_red ) + FLOAT_FLOAT_FACTOR;
			green = ( normal->g * surface_green ) + FLOAT_FLOAT_FACTOR;
			blue = ( normal->b * surface_blue ) + FLOAT_FLOAT_FACTOR;
			r = ( *( int * ) &red ) - INTEGER_FLOAT_FACTOR;
			g = ( *( int * ) &green ) - INTEGER_FLOAT_FACTOR;
			b = ( *( int * ) &blue ) - INTEGER_FLOAT_FACTOR;
			destination_vertices[count].color = RGB_MAKE ( r, g, b );

			specular = normal->specular;
			asm_convert_float_to_int ( ( specular * surface_specular ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;
		}
	
		draw_fan_primitive ( this_face->number_of_points, destination_vertices );
	}
	else
	{
	
		int
			polygon_alpha;

		float
			distance;

		//
		// Should draw a gouraud shaded translucent polygon
		//

		asm_convert_float_to_int ( ( current_object_3d_surface->alpha * current_object_3d_dissolve_factor ), &polygon_alpha );

		distance = 0;

		destination_vertices = get_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			object_3d_transformed_point_normal
				*normal;

			surface_point_index = current_object_3d_point_list[count].point;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];
		
			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			red = ( normal->r * surface_red ) + FLOAT_FLOAT_FACTOR;
			green = ( normal->g * surface_green ) + FLOAT_FLOAT_FACTOR;
			blue = ( normal->b * surface_blue ) + FLOAT_FLOAT_FACTOR;
			r = ( *( int * ) &red ) - INTEGER_FLOAT_FACTOR;
			g = ( *( int * ) &green ) - INTEGER_FLOAT_FACTOR;
			b = ( *( int * ) &blue ) - INTEGER_FLOAT_FACTOR;
			destination_vertices[count].color = RGBA_MAKE ( r, g, b, polygon_alpha );

			specular = normal->specular;
			asm_convert_float_to_int ( ( specular * surface_specular ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;

			distance += vert->q;
		}

		distance *= one_over_table[this_face->number_of_points];

		add_buffered_processed_polygon ( this_face->number_of_points, distance, D3DSHADE_GOURAUD, NULL, 0, 0, 0, 0, current_object_3d_specular, 0 );
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

		poly = construct_3d_surface_polygon ( this_face->number_of_points, object_base->points_base );

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

			int
				surface_point_index;

			surface_point_index = current_object_3d_point_list[count].point;

			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			
			*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
			*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
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
	
			commit_deferred_state_changes ();

			transformed_points = transformed_3d_2d_points + object_base->points_base;
	
			destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

			for ( count = 0; count < this_face->number_of_points; count++ )
			{

				int
					surface_point_index;

				object_3d_transformed_point_normal
					*normal;

				surface_point_index = current_object_3d_point_list[count].point;

				vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
				normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];
			
				*( ( int * ) &destination_vertices[count].sx ) = *( ( int * ) &vert->i );
				*( ( int * ) &destination_vertices[count].sy ) = *( ( int * ) &vert->j );
				destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
				destination_vertices[count].rhw = vert->q;
				destination_vertices[count].color = normal->colour;
				destination_vertices[count].specular = d3d_fog_intensity;
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
		
				poly = construct_3d_surface_unclipped_gouraud_triangle_fan ( triangle_count, 0, object_base->points_base );
		
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
	
		float
			distance;

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_translucent_polygon_vertices ();
	
		lightmap_vertices = get_temporary_translucent_polygon_vertices ();
	
		distance = 0;

		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			int
				surface_point_index,
				surface_texture_index;

			surface_point_index = current_object_3d_point_list[count].point;
			surface_texture_index = surface_point_index * 2;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
		
			destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
			destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;

			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_texture_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_texture_index].v;

			lightmap_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
			lightmap_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;

			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;
			lightmap_vertices[count].color = lightmap_colour.colour;
			lightmap_vertices[count].specular = d3d_fog_intensity;

			distance += vert->q;
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
	
		//
		// Should draw a flat shaded polygon - with a lightmap
		//

		commit_deferred_state_changes ();

		transformed_points = transformed_3d_2d_points + object_base->points_base;
	
		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );

		lightmap_vertices = get_temporary_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			int
				surface_point_index,
				surface_texture_index;

			surface_point_index = current_object_3d_point_list[count].point;
			surface_texture_index = surface_point_index * 2;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
		
			destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
			destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;

			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_texture_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_texture_index].v;

			lightmap_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
			lightmap_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;

			destination_vertices[count].color = colour.colour;
			destination_vertices[count].specular = specular_colour.colour;

			lightmap_vertices[count].color = lightmap_colour.colour;
			lightmap_vertices[count].specular = d3d_fog_intensity;
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

			int
				surface_point_index,
				surface_texture_index;

			object_3d_transformed_point_normal
				*normal;

			surface_point_index = current_object_3d_point_list[count].point;
			surface_texture_index = surface_point_index * 2;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];

			destination_vertices[count].sx = vert->i;
			destination_vertices[count].sy = vert->j;
			destination_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = vert->q;
			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_texture_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_texture_index].v;
			translucent_colour.colour = normal->colour;
			translucent_colour.alpha = current_object_3d_dissolve_value;
			destination_vertices[count].color = translucent_colour.colour;

			specular = normal->specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;

			distance += vert->q;
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
		// Should draw a gouraud shaded polygon - with a lightmap
		//

		commit_deferred_state_changes ();

		destination_vertices = get_d3d_vertices_points_address ( this_face->number_of_points );
	
		lightmap_vertices = get_temporary_translucent_polygon_vertices ();
	
		for ( count = 0; count < this_face->number_of_points; count++ )
		{

			int
				surface_point_index,
				surface_texture_index;

			object_3d_transformed_point_normal
				*normal;

			surface_point_index = current_object_3d_point_list[count].point;
			surface_texture_index = surface_point_index * 2;
			vert = transformed_points + current_object_3d_surface_point_list[surface_point_index].point;
			normal = &current_object_3d_transformed_normals[ current_object_3d_surface_point_normal_list[surface_point_index].point ];

			destination_vertices[count].sx = lightmap_vertices[count].sx = vert->i;
			destination_vertices[count].sy = lightmap_vertices[count].sy = vert->j;
			destination_vertices[count].sz = lightmap_vertices[count].sz = ( vert->z * wbuffer_factor ) + wbuffer_constant;
			destination_vertices[count].rhw = lightmap_vertices[count].rhw = vert->q;

			destination_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_texture_index].u;
			destination_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_texture_index].v;

			lightmap_vertices[count].tu = current_object_3d_surface_point_texture_list[surface_texture_index+1].u;
			lightmap_vertices[count].tv = current_object_3d_surface_point_texture_list[surface_texture_index+1].v;

			destination_vertices[count].color = normal->colour;
			lightmap_vertices[count].color = lightmap_colour.colour;

			specular = normal->specular;
			asm_convert_float_to_int ( ( specular * current_object_3d_surface->specularity ), &ispecular );
			specular_colour.colour = d3d_fog_intensity;
			specular_colour.red = ispecular;
			specular_colour.green = ispecular;
			specular_colour.blue = ispecular;

			destination_vertices[count].specular = specular_colour.colour;
			lightmap_vertices[count].specular = d3d_fog_intensity;
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

void zrender_unclipped_3d_object_textured_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	ASSERT ( !current_object_3d_surface->polygons );

	line = construct_3d_surface_unclipped_textured_line ( object_base->points_base );

	if ( current_object_3d_surface->smoothed )
	{

		commit_deferred_state_changes ();

		draw_wbuffered_gouraud_shaded_textured_line ( line, system_textures[current_object_3d_surface->texture_index] );
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

			buffer_zbuffered_flat_shaded_textured_line ( line, system_textures[current_object_3d_surface->texture_index],
																		current_object_3d_texture_filter, current_object_3d_texture_mipmap,
																		current_object_3d_texture_u_address, current_object_3d_texture_v_address,
																		colour, TRUE );
		}
		else
		{
	
			commit_deferred_state_changes ();

			draw_zbuffered_flat_shaded_textured_line ( line, system_textures[current_object_3d_surface->texture_index], colour );
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

	line = construct_3d_surface_unclipped_line ( object_base->points_base );

	if ( current_object_3d_surface->smoothed )
	{

		draw_zbuffered_gouraud_shaded_line ( line, current_object_3d_surface->red, current_object_3d_surface->green, current_object_3d_surface->blue );
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

void zrender_unclipped_3d_object_plain_white_line ( object_3d_face *this_face, struct OBJECT_3D_INFO *object_base )
{

	vertex
		*line;

	clip_3d_coord = 0;

	ASSERT ( !current_object_3d_surface->polygons );

	commit_deferred_state_changes ();

	line = construct_3d_surface_unclipped_line ( object_base->points_base );

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

