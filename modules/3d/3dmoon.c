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



#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen
	*moon_texture = nullptr;

float
	moon_3d_heading,
	moon_3d_pitch;

light_colour
	moon_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_moon ( texture_index_numbers moon_index )
{

	moon_texture = system_textures[moon_index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_moon_position ( float heading, float pitch )
{

	moon_3d_heading = heading;

	moon_3d_pitch = pitch;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_moon_colour ( light_colour *colour )
{

	ASSERT ( colour );

	moon_colour = *colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_moon ( void )
{


	vertex
		*moon_polygon = nullptr,
		*vert = nullptr,
		moon_quad[4];

	int
		outcode,
		outcode2,
		count;

	float
		moon_width,
		moon_height,
		moon_depth;

	matrix3x3
		moon_matrix;

	int
		moon_red,
		moon_green,
		moon_blue;

	real_colour
		colour,
		specular;

	moon_polygon = moon_quad;

	moon_width = 12000;
	moon_height = 12000;
	moon_depth = 100000;

	memset ( moon_quad, 0, sizeof ( moon_quad ) );
	moon_quad[0].next_vertex = &moon_quad[1];
	moon_quad[1].next_vertex = &moon_quad[2];
	moon_quad[2].next_vertex = &moon_quad[3];
	moon_quad[3].next_vertex = NULL;

	moon_quad[0].x = -moon_width/2;
	moon_quad[0].y = moon_height/2;
	moon_quad[0].z = moon_depth;
	moon_quad[0].u = 0;
	moon_quad[0].v = 0;

	moon_quad[1].x = moon_width/2;
	moon_quad[1].y = moon_height/2;
	moon_quad[1].z = moon_depth;
	moon_quad[1].u = 1;
	moon_quad[1].v = 0;

	moon_quad[2].x = moon_width/2;
	moon_quad[2].y = -moon_height/2;
	moon_quad[2].z = moon_depth;
	moon_quad[2].u = 1;
	moon_quad[2].v = 1;

	moon_quad[3].x = -moon_width/2;
	moon_quad[3].y = -moon_height/2;
	moon_quad[3].z = moon_depth;
	moon_quad[3].u = 0;
	moon_quad[3].v = 1;

	//
	// Rotate the moon into position
	//

	get_3d_transformation_matrix ( moon_matrix, moon_3d_heading, moon_3d_pitch, 0 );

	for ( count = 0; count < 4; count++ )
	{

		float
			x,
			y,
			z;


		x = moon_quad[count].x * moon_matrix[0][0] + moon_quad[count].y * moon_matrix[1][0] + moon_quad[count].z * moon_matrix[2][0];
		y = moon_quad[count].x * moon_matrix[0][1] + moon_quad[count].y * moon_matrix[1][1] + moon_quad[count].z * moon_matrix[2][1];
		z = moon_quad[count].x * moon_matrix[0][2] + moon_quad[count].y * moon_matrix[1][2] + moon_quad[count].z * moon_matrix[2][2];

		moon_quad[count].x = x;
		moon_quad[count].y = y;
		moon_quad[count].z = z;
	}

	//
	// Clip the moon to the horizon
	//

	clip_3d_coord = 0;

	moon_polygon = horizon_clip_3d_polygon ( moon_quad );

	if ( moon_polygon )
	{

		//
		// Rotate the polygon around to the users viewpoint
		//

		vert = moon_polygon;

		rotation_3d[0][0] = ( visual_3d_vp->xv.x );
		rotation_3d[0][1] = ( visual_3d_vp->yv.x );
		rotation_3d[0][2] = ( visual_3d_vp->zv.x );

		rotation_3d[1][0] = ( visual_3d_vp->xv.y );
		rotation_3d[1][1] = ( visual_3d_vp->yv.y );
		rotation_3d[1][2] = ( visual_3d_vp->zv.y );

		rotation_3d[2][0] = ( visual_3d_vp->xv.z );
		rotation_3d[2][1] = ( visual_3d_vp->yv.z );
		rotation_3d[2][2] = ( visual_3d_vp->zv.z );

		outcode = 0;

		outcode2 = CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM | CLIP_HITHER | CLIP_YONDER;

		while ( vert )
		{

			float
				x,
				y,
				z;

			x = vert->x * rotation_3d[0][0] + vert->y * rotation_3d[1][0] + vert->z * rotation_3d[2][0];
			y = vert->x * rotation_3d[0][1] + vert->y * rotation_3d[1][1] + vert->z * rotation_3d[2][1];
			z = vert->x * rotation_3d[0][2] + vert->y * rotation_3d[1][2] + vert->z * rotation_3d[2][2];

			x *= active_3d_environment->screen_i_scale;
			y *= active_3d_environment->screen_j_scale;

			if ( *( ( int * ) &z ) >= *( ( int * ) &clip_hither ) )
			{

				float
					q,
					i,
					j;

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

				q = 1.0 / z;

				vert->x = x;
				vert->y = y;
				vert->z = z;
				vert->q = q;

				i = ( x * q );
				j = ( y * q );

				vert->j = active_3d_environment->y_origin - j;
				vert->i = active_3d_environment->x_origin + i;

				oxmax = active_viewport.x_max - vert->i;
				oxmin = vert->i - active_viewport.x_min;
				oymax = active_viewport.y_max - vert->j;
				oymin = vert->j - active_viewport.y_min;

				ixmax = *( ( int * ) &oxmax );
				ixmin = *( ( int * ) &oxmin );
				iymax = *( ( int * ) &oymax );
				iymin = *( ( int * ) &oymin );

				vert->outcode = generate_lookup_outcode ( ixmin, iymin, ixmax, iymax );

				outcode |= vert->outcode;
				outcode2 &= vert->outcode;
			}
			else
			{

				vert->outcode = CLIP_HITHER;
				vert->z = z;
				vert->x = x;
				vert->y = y;

				outcode |= vert->outcode;
				outcode2 &= vert->outcode;
			}

			vert = vert->next_vertex;
		}

		if ( outcode2 )
		{

			return;
		}


		if ( outcode & CLIP_HITHER )
		{

			moon_polygon = hither_clip_3d_polygon ( moon_polygon, &outcode );

			if ( !moon_polygon )
			{

				return;
			}
		}

		if ( outcode )
		{

			apply_perspective_to_polygon_texture ( moon_polygon );

			moon_polygon = clip_3d_polygon ( moon_polygon, outcode );

			if ( !moon_polygon )
			{

				return;
			}

			remove_perspective_from_polygon_texture ( moon_polygon );
		}

		asm_convert_float_to_int ( ( moon_colour.red * 255 ), &moon_red );
		asm_convert_float_to_int ( ( moon_colour.green * 255 ), &moon_green );
		asm_convert_float_to_int ( ( moon_colour.blue * 255 ), &moon_blue );

		colour.red = moon_red;
		colour.green = moon_green;
		colour.blue = moon_blue;

		specular.colour = 0;

		set_d3d_int_state ( D3DRS_ZFUNC, D3DCMP_ALWAYS );
		set_d3d_int_state ( D3DRS_ZWRITEENABLE, FALSE );

		suspend_d3d_fog ();

		set_d3d_int_state ( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
		set_d3d_int_state ( D3DRS_ALPHABLENDENABLE, TRUE );
		set_d3d_int_state ( D3DRS_SRCBLEND, ADDITIVE_SOURCE_BLEND );
		set_d3d_int_state ( D3DRS_DESTBLEND, ADDITIVE_DESTINATION_BLEND );

		set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
		set_d3d_sampler_state ( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
		set_d3d_sampler_state ( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		set_d3d_sampler_state ( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		set_d3d_texture ( 0, moon_texture );

		draw_wbuffered_flat_shaded_textured_polygon ( moon_polygon, colour, specular );

		set_d3d_int_state ( D3DRS_ALPHABLENDENABLE, FALSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		set_d3d_texture ( 0, NULL );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

		reinstate_d3d_fog ();

		set_d3d_int_state ( D3DRS_ZFUNC, zbuffer_default_comparison );
		set_d3d_int_state ( D3DRS_ZWRITEENABLE, TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
