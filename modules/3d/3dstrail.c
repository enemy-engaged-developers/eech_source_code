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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_3D_SMOKE_TRAILS 8192

#define MAX_3D_SMOKE_TRAIL_POINTS 32768

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

smoke_trail_information
	smoke_trail_headers[MAX_3D_SMOKE_TRAILS];

smoke_trail_data
	smoke_trail_point_data[MAX_3D_SMOKE_TRAIL_POINTS];

int
	number_of_smoke_trail_headers_used;

int
	number_of_smoke_trail_points_used;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static real_colour light_smoke_colour ( real_colour colour, int additive );

static void render_smoke_trail_polygon ( vertex *poly, screen *texture, int additive );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_smoke_trail_rendering_information ( void )
{

	number_of_smoke_trail_headers_used = 0;

	number_of_smoke_trail_points_used = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

smoke_trail_information *get_smoke_trail_header ( void )
{

	if ( ( number_of_smoke_trail_headers_used + 1 ) < MAX_3D_SMOKE_TRAILS )
	{

		int
			index;

		index = number_of_smoke_trail_headers_used;

		number_of_smoke_trail_headers_used++;

		return ( &smoke_trail_headers[index] );
	}
	else
	{
		debug_log("not enough place for smoke trails!");
		return ( NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

smoke_trail_data *get_smoke_trail_point_data ( int number_of_points )
{

	if ( ( number_of_smoke_trail_points_used + number_of_points ) < MAX_3D_SMOKE_TRAIL_POINTS )
	{

		int
			index;

		index = number_of_smoke_trail_points_used;

		number_of_smoke_trail_points_used += number_of_points;

		return ( &smoke_trail_point_data[index] );
	}
	else
	{
		debug_log("not enough place for smoke trail points!");

		return ( NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_smoke_trail_point_data ( int number_of_points )
{

	number_of_smoke_trail_points_used -= number_of_points;

	ASSERT ( number_of_smoke_trail_points_used >= 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_zbiased_smoke_trail_into_3d_scene ( int number_of_points, float zbias, int additive, screen *texture, float texture_distance, float texture_size, smoke_trail_data *points )
{

	smoke_trail_data
		*rotated_points;

	int
		count,
		visible;

	//
	// First, copy the ROTATED point data over to an internal 3d visual buffer ( checking for visibility )
	//

	visible = FALSE;

	rotated_points = get_smoke_trail_point_data ( number_of_points );

	if ( rotated_points )
	{

		for ( count = 0; count < number_of_points; count++ )
		{

			get_position_3d_relative_position ( &points[count].point1, &rotated_points[count].point1 );

			if ( rotated_points[count].point1.z > clip_hither )
			{

				visible = TRUE;
			}

			get_position_3d_relative_position ( &points[count].point2, &rotated_points[count].point2 );

			if ( rotated_points[count].point2.z > clip_hither )
			{

				visible = TRUE;
			}

			rotated_points[count].centre.x = ( rotated_points[count].point1.x + rotated_points[count].point2.x ) / 2;
			rotated_points[count].centre.y = ( rotated_points[count].point1.y + rotated_points[count].point2.y ) / 2;
			rotated_points[count].centre.z = ( rotated_points[count].point1.z + rotated_points[count].point2.z ) / 2;
		}

		if ( visible )
		{

			smoke_trail_information
				*smoke_trail;

			float
				texture_u;

			//
			// Some part ( or all ) of the smoke trail is visible - generate a smoke trail header.
			//

			smoke_trail = get_smoke_trail_header ();

			if ( smoke_trail )
			{

				smoke_trail->additive = additive;

				smoke_trail->texture = texture;

				smoke_trail->texture_size = texture_size;

				smoke_trail->number_of_points = number_of_points;

				smoke_trail->points = rotated_points;

				//
				// Go calculate the u texture coordinates
				//

				texture_u = texture_distance / texture_size;

				rotated_points[0].texture_u = texture_u;

				rotated_points[0].colour = points[0].colour;

				for ( count = 0; count < ( number_of_points - 1 ); count++ )
				{

					vec3d
						centre_point1,
						centre_point2,
						length_vector;

					float
						texture_temp_distance;

					centre_point1.x = ( points[count].point1.x + points[count].point2.x ) / 2;
					centre_point1.y = ( points[count].point1.y + points[count].point2.y ) / 2;
					centre_point1.z = ( points[count].point1.z + points[count].point2.z ) / 2;

					centre_point2.x = ( points[count+1].point1.x + points[count+1].point2.x ) / 2;
					centre_point2.y = ( points[count+1].point1.y + points[count+1].point2.y ) / 2;
					centre_point2.z = ( points[count+1].point1.z + points[count+1].point2.z ) / 2;

					length_vector.x = centre_point2.x - centre_point1.x;
					length_vector.y = centre_point2.y - centre_point1.y;
					length_vector.z = centre_point2.z - centre_point1.z;

					//
					// Calculate the length of line connecting the two centre points
					//

					texture_temp_distance = ( get_3d_vector_magnitude ( &length_vector ) / texture_size );

					texture_u += texture_temp_distance;

					rotated_points[count+1].texture_u = texture_u;
					rotated_points[count+1].colour = points[count+1].colour;
				}

				//
				// Now insert each segment dependant on it being visible or not.
				//

				for ( count = 0; count < ( number_of_points - 1 ); count++ )
				{

					if (	( rotated_points[count].point1.z > clip_hither ) || ( rotated_points[count].point2.z > clip_hither ) ||
							( rotated_points[count+1].point1.z > clip_hither ) || ( rotated_points[count+1].point1.z > clip_hither ) )
					{

						scene_slot_drawing_list
							*buffer;

						float
							average_z;

						average_z = (	( rotated_points[count].point1.z + rotated_points[count].point2.z ) +
											( rotated_points[count+1].point1.z + rotated_points[count+1].point2.z ) );

						average_z /= 4;

						average_z += zbias;

						buffer = get_3d_scene_slot ();

						if ( buffer )
						{

							buffer->type = OBJECT_3D_DRAW_TYPE_SMOKE_TRAIL;

							buffer->z = *( ( int * ) &average_z );

							buffer->smoke_trail.trail = smoke_trail;

							buffer->smoke_trail.segment = count;

							if ( points[count].point1.y > middle_scene_slot_height )
							{

								insert_high_nonzbuffered_scene_slot_into_3d_scene ( buffer );
							}
							else
							{

								insert_low_nonzbuffered_scene_slot_into_3d_scene ( buffer );
							}
						}
						else
						{

							debug_log ( "SMOKE TRAIL OVERFLOWED OBJECT BUFFER" );
						}
					}
				}
			}
			else
			{

				//
				// No point in freeing up the smoke trail point data, as all the headers are used up!
				//
			}
		}
		else
		{

			//
			// Free up the reserved smoke trail point data slots
			//

			remove_smoke_trail_point_data ( number_of_points );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
real_colour light_smoke_colour ( real_colour colour, int additive )
{

	real_colour
		result;

	float
		r,
		g,
		b,
		intensity;

	int
		ir,
		ig,
		ib;

	result.colour = colour.colour;

	if ( additive )
	{

		if (active_3d_environment->render_filter != RENDER_CLEAR )
		{

			//
			// Colour the additive to the light colour
			//

			r = colour.red;
			g = colour.green;
			b = colour.blue;

			intensity = ( 0.3 * r ) + ( 0.59 * g ) + ( 0.11 * b );

			r = intensity * ambient_3d_light.colour.red;
			g = intensity * ambient_3d_light.colour.green;
			b = intensity * ambient_3d_light.colour.blue;

			asm_convert_float_to_int ( r, &ir );
			asm_convert_float_to_int ( g, &ig );
			asm_convert_float_to_int ( b, &ib );

			result.red = ir;
			result.green = ig;
			result.blue = ib;
		}
		else
		{

			result = colour;
		}
	}
	else
	{

		r = colour.red;
		g = colour.green;
		b = colour.blue;

		r *= ambient_3d_light.colour.red * 1.866666;		//2.8;
		g *= ambient_3d_light.colour.green * 1.866666;	//2.8;
		b *= ambient_3d_light.colour.blue * 1.866666;	//2.8;

		asm_convert_float_to_int ( r, &ir );
		asm_convert_float_to_int ( g, &ig );
		asm_convert_float_to_int ( b, &ib );

		ir = bound ( ir, 0, 255 );
		ig = bound ( ig, 0, 255 );
		ib = bound ( ib, 0, 255 );

		result.red = ir;
		result.green = ig;
		result.blue = ib;
	}

	return ( result );
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_smoke_trail ( struct OBJECT_3D_SMOKE_TRAIL *smoke )
{

	vertex
		points[6];

	int
		segment,
		count,
		outcode,
		outcode2;

	segment = smoke->segment;

	set_d3d_fog_face_intensity ( 255 );

	//
	// Copy the 3d coordinates into a local quad
	//

	points[0].x = smoke->trail->points[segment].point1.x * active_3d_environment->screen_i_scale;
	points[0].y = smoke->trail->points[segment].point1.y * active_3d_environment->screen_j_scale;
	points[0].z = smoke->trail->points[segment].point1.z;
	points[0].u = smoke->trail->points[segment].texture_u;

	points[1].x = smoke->trail->points[segment].centre.x * active_3d_environment->screen_i_scale;
	points[1].y = smoke->trail->points[segment].centre.y * active_3d_environment->screen_j_scale;
	points[1].z = smoke->trail->points[segment].centre.z;
	points[1].u = smoke->trail->points[segment].texture_u;

	points[2].x = smoke->trail->points[segment].point2.x * active_3d_environment->screen_i_scale;
	points[2].y = smoke->trail->points[segment].point2.y * active_3d_environment->screen_j_scale;
	points[2].z = smoke->trail->points[segment].point2.z;
	points[2].u = smoke->trail->points[segment].texture_u;

	points[3].x = smoke->trail->points[segment+1].point1.x * active_3d_environment->screen_i_scale;
	points[3].y = smoke->trail->points[segment+1].point1.y * active_3d_environment->screen_j_scale;
	points[3].z = smoke->trail->points[segment+1].point1.z;
	points[3].u = smoke->trail->points[segment+1].texture_u;

	points[4].x = smoke->trail->points[segment+1].centre.x * active_3d_environment->screen_i_scale;
	points[4].y = smoke->trail->points[segment+1].centre.y * active_3d_environment->screen_j_scale;
	points[4].z = smoke->trail->points[segment+1].centre.z;
	points[4].u = smoke->trail->points[segment+1].texture_u;

	points[5].x = smoke->trail->points[segment+1].point2.x * active_3d_environment->screen_i_scale;
	points[5].y = smoke->trail->points[segment+1].point2.y * active_3d_environment->screen_j_scale;
	points[5].z = smoke->trail->points[segment+1].point2.z;
	points[5].u = smoke->trail->points[segment+1].texture_u;

	//
	// Transform the points and outcode the quad at the same time
	//

	outcode = 0;
	outcode2 = CLIP_HITHER | CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM;

	for ( count = 0; count < 6; count++ )
	{

		if ( *( ( int * ) &points[count].z ) >= *( ( int * ) &clip_hither ) )
		{

			float
				oxmax,
				oxmin,
				oymax,
				oymin,
				q,
				i,
				j;

			int
				ixmax,
				ixmin,
				iymax,
				iymin;

			q = 1.0 / points[count].z;

			i = ( points[count].x * q );
			j = ( points[count].y * q );

			j = active_3d_environment->y_origin - j;
			i = active_3d_environment->x_origin + i;

			points[count].j = j;
			points[count].i = i;
			points[count].q = q;

			oxmax = active_viewport.x_max - i;
			oxmin = i - active_viewport.x_min;
			oymax = active_viewport.y_max - j;
			oymin = j - active_viewport.y_min;

			ixmax = *( ( int * ) &oxmax );
			ixmin = *( ( int * ) &oxmin );
			iymax = *( ( int * ) &oymax );
			iymin = *( ( int * ) &oymin );

			points[count].outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );
		}
		else
		{

			points[count].outcode = CLIP_HITHER;
		}

		outcode |= points[count].outcode;
		outcode2 &= points[count].outcode;
	}

	if ( outcode2 == 0 )
	{

		points[0].u = smoke->trail->points[segment].texture_u;
		points[0].v = 0;
		points[0].colour = smoke->trail->points[segment].colour.colour;

		points[3].u = smoke->trail->points[segment+1].texture_u;
		points[3].v = 0;
		points[3].colour = smoke->trail->points[segment+1].colour.colour;

		points[4].u = smoke->trail->points[segment+1].texture_u;
		points[4].v = 0.5;
		points[4].colour = smoke->trail->points[segment+1].colour.colour;

		points[0].next_vertex = &points[3];
		points[3].next_vertex = &points[4];
		points[4].next_vertex = NULL;

		render_smoke_trail_polygon ( &points[0], smoke->trail->texture, smoke->trail->additive );

		points[0].u = smoke->trail->points[segment].texture_u;
		points[0].v = 0;
		points[0].colour = smoke->trail->points[segment].colour.colour;

		points[1].u = smoke->trail->points[segment].texture_u;
		points[1].v = 0.5;
		points[1].colour = smoke->trail->points[segment].colour.colour;

		points[4].u = smoke->trail->points[segment+1].texture_u;
		points[4].v = 0.5;
		points[4].colour = smoke->trail->points[segment+1].colour.colour;

		points[0].next_vertex = &points[4];
		points[4].next_vertex = &points[1];
		points[1].next_vertex = NULL;

		render_smoke_trail_polygon ( &points[0], smoke->trail->texture, smoke->trail->additive );

		points[1].u = smoke->trail->points[segment].texture_u;
		points[1].v = 0.5;
		points[1].colour = smoke->trail->points[segment].colour.colour;

		points[2].u = smoke->trail->points[segment].texture_u;
		points[2].v = 1;
		points[2].colour = smoke->trail->points[segment].colour.colour;

		points[4].u = smoke->trail->points[segment+1].texture_u;
		points[4].v = 0.5;
		points[4].colour = smoke->trail->points[segment+1].colour.colour;

		points[1].next_vertex = &points[4];
		points[4].next_vertex = &points[2];
		points[2].next_vertex = NULL;

		render_smoke_trail_polygon ( &points[1], smoke->trail->texture, smoke->trail->additive );

		points[2].u = smoke->trail->points[segment].texture_u;
		points[2].v = 1;
		points[2].colour = smoke->trail->points[segment].colour.colour;

		points[4].u = smoke->trail->points[segment+1].texture_u;
		points[4].v = 0.5;
		points[4].colour = smoke->trail->points[segment+1].colour.colour;

		points[5].u = smoke->trail->points[segment+1].texture_u;
		points[5].v = 1;
		points[5].colour = smoke->trail->points[segment+1].colour.colour;

		points[2].next_vertex = &points[4];
		points[4].next_vertex = &points[5];
		points[5].next_vertex = NULL;

		render_smoke_trail_polygon ( &points[2], smoke->trail->texture, smoke->trail->additive );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void render_smoke_trail_polygon ( vertex *poly, screen *texture, int additive )
{

	int
		outcode;

	vertex
		*tmp;

	tmp = poly;

	outcode = 0;

	while ( tmp )
	{

		outcode |= tmp->outcode;

		tmp = tmp->next_vertex;
	}


	if ( outcode )
	{

		clip_3d_coord = 0;

		if ( outcode & CLIP_HITHER )
		{

			poly = hither_clip_3d_polygon ( poly, &outcode );

			if ( !poly )
			{

				outcode = 0;
			}
		}

		if ( outcode )
		{

			apply_perspective_to_polygon_texture ( poly );

			poly = clip_3d_polygon ( poly, outcode );

			if ( poly )
			{

				remove_perspective_from_polygon_texture ( poly );
			}
		}
	}

	if ( poly )
	{

//		d3d_fog_intensity = D3DCOLOR_RGBA ( 0, 0, 0, 255 );

		//
		// Set the required renderstates
		//

		set_d3d_int_state ( D3DRS_SPECULARENABLE, FALSE );
//		set_d3d_int_state ( D3DRS_CULLMODE, D3DCULL_NONE );

		set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
		set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
		set_d3d_sampler_state ( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		set_d3d_sampler_state ( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		set_d3d_sampler_state ( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

		if ( additive )
		{

			set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_ONE );
			set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_ONE );

			set_d3d_gouraud_shaded_textured_renderstate ( texture );
			draw_wbuffered_gouraud_shaded_textured_polygon ( poly );
		}
		else
		{

			set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

			set_d3d_gouraud_shaded_textured_renderstate ( texture );
			draw_wbuffered_gouraud_shaded_textured_polygon ( poly );
		}

//		set_d3d_int_state ( D3DRS_CULLMODE, D3DCULL_CCW );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
