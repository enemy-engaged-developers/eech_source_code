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

screen
	*sun_texture,
	*sun_flare_texture;

float
	sun_3d_heading,
	sun_3d_pitch,
	sun_3d_scale,
	sun_3d_intensity;

light_colour
	sun_3d_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_sun_polygon ( matrix3x3 sun_matrix, vertex *sun_quad, float sun_width, float sun_height, float sun_depth );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_sun ( texture_index_numbers sun_index, texture_index_numbers sun_flare_index )
{

	sun_texture = system_textures[sun_index];

	sun_flare_texture = system_textures[sun_flare_index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_sun_position ( float heading, float pitch )
{

	sun_3d_heading = heading;

	sun_3d_pitch = pitch;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_sun_colour ( light_colour *colour )
{

	ASSERT ( colour );

	sun_3d_colour = *colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_sun_light_intensity ( float intensity )
{

	sun_3d_intensity = intensity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_3d_sun_scale ( float scale )
{

	sun_3d_scale = scale;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_3d_sun ( void )
{

	vertex
		*sun_polygon,
		sun_quad[4];

	matrix3x3
		sun_matrix;

	float
		flare_intensity;

	int
		sun_red,
		sun_green,
		sun_blue;

	real_colour
		colour,
		specular;

	//
	// Draw the main sun object
	//

	get_3d_transformation_matrix ( sun_matrix, sun_3d_heading, sun_3d_pitch, 0 );

	sun_polygon = construct_sun_polygon ( sun_matrix, sun_quad, 32000 * sun_3d_scale, 32000 * sun_3d_scale, 100000 );

	specular.colour = 0;

	if ( sun_polygon )
	{

		asm_convert_float_to_int ( ( sun_3d_colour.red * 255 ), &sun_red );
		asm_convert_float_to_int ( ( sun_3d_colour.green * 255 ), &sun_green );
		asm_convert_float_to_int ( ( sun_3d_colour.blue * 255 ), &sun_blue );

		colour.red = sun_red;
		colour.green = sun_green;
		colour.blue = sun_blue;

		set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );
		set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
	
		suspend_d3d_fog ();
	
		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
		set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
		set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, ADDITIVE_SOURCE_BLEND );
		set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, ADDITIVE_DESTINATION_BLEND );

		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
		set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
		set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

		set_d3d_texture ( 0, sun_texture );

		draw_wbuffered_flat_shaded_textured_polygon ( sun_polygon, colour, specular );
	}

	//
	// Now render the flare around the sun, if it is indeed there.
	//

	//
	// Calculate the intensity of the sun flare
	//

	flare_intensity = (	( sun_matrix[2][0] * visual_3d_vp->zv.x ) +
							 	( sun_matrix[2][1] * visual_3d_vp->zv.y ) +
							 	( sun_matrix[2][2] * visual_3d_vp->zv.z ) );

	flare_intensity *= flare_intensity;
	flare_intensity *= flare_intensity;
	flare_intensity *= flare_intensity;
	flare_intensity *= flare_intensity;
	flare_intensity *= flare_intensity;
	flare_intensity *= flare_intensity;
	flare_intensity *= flare_intensity;

	flare_intensity *= sun_3d_intensity;
	flare_intensity *= sun_3d_intensity;
	flare_intensity *= sun_3d_intensity;

	flare_intensity *= 255;

	sun_polygon = construct_sun_polygon ( sun_matrix, sun_quad, 144000, 69750, 100000 );

	if ( sun_polygon )
	{

		asm_convert_float_to_int ( ( ( 74.0 / 255.0 ) * flare_intensity ), &sun_red );
		asm_convert_float_to_int ( ( ( 177.0 / 255.0 ) * flare_intensity ), &sun_green );
		asm_convert_float_to_int ( ( ( 248.0 / 255.0 ) * flare_intensity ), &sun_blue );
//		asm_convert_float_to_int ( ( sun_3d_colour.red * flare_intensity ), &sun_red );
//		asm_convert_float_to_int ( ( sun_3d_colour.green * flare_intensity ), &sun_green );
//		asm_convert_float_to_int ( ( sun_3d_colour.blue * flare_intensity ), &sun_blue );

		colour.red = sun_red;
		colour.green = sun_green;
		colour.blue = sun_blue;

		set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, D3DCMP_ALWAYS );
		set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
	
		suspend_d3d_fog ();
	
		set_d3d_int_state ( D3DRENDERSTATE_SHADEMODE, D3DSHADE_FLAT );
		set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, TRUE );
		set_d3d_int_state ( D3DRENDERSTATE_SRCBLEND, ADDITIVE_SOURCE_BLEND );
		set_d3d_int_state ( D3DRENDERSTATE_DESTBLEND, ADDITIVE_DESTINATION_BLEND );

		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
		set_d3d_texture_stage_state ( 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
		set_d3d_texture_stage_state ( 0, D3DTSS_MAGFILTER, D3DTFG_LINEAR );
		set_d3d_texture_stage_state ( 0, D3DTSS_MINFILTER, D3DTFN_LINEAR );

		set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

		set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
	
		set_d3d_texture ( 0, sun_flare_texture );

		draw_wbuffered_flat_shaded_textured_polygon ( sun_polygon, colour, specular );
	}

	set_d3d_int_state ( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );

	set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );
	set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	set_d3d_texture_stage_state ( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	set_d3d_texture ( 0, NULL );

	set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
	set_d3d_texture_stage_state ( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	reinstate_d3d_fog ();

	set_d3d_int_state ( D3DRENDERSTATE_ZFUNC, zbuffer_default_comparison );
	set_d3d_int_state ( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vertex * construct_sun_polygon ( matrix3x3 sun_matrix, vertex *sun_quad, float sun_width, float sun_height, float sun_depth )
{

	vertex
		*sun_polygon,
		*vert;

	int
		outcode,
		outcode2,
		count;

	sun_quad[0].next_vertex = &sun_quad[1];
	sun_quad[1].next_vertex = &sun_quad[2];
	sun_quad[2].next_vertex = &sun_quad[3];
	sun_quad[3].next_vertex = NULL;

	sun_quad[0].x = -sun_width/2;
	sun_quad[0].y = sun_height/2;
	sun_quad[0].z = sun_depth;
	sun_quad[0].u = 0;
	sun_quad[0].v = 0;

	sun_quad[1].x = sun_width/2;
	sun_quad[1].y = sun_height/2;
	sun_quad[1].z = sun_depth;
	sun_quad[1].u = 1;
	sun_quad[1].v = 0;

	sun_quad[2].x = sun_width/2;
	sun_quad[2].y = -sun_height/2;
	sun_quad[2].z = sun_depth;
	sun_quad[2].u = 1;
	sun_quad[2].v = 1;

	sun_quad[3].x = -sun_width/2;
	sun_quad[3].y = -sun_height/2;
	sun_quad[3].z = sun_depth;
	sun_quad[3].u = 0;
	sun_quad[3].v = 1;

	for ( count = 0; count < 4; count++ )
	{

		float
			x,
			y,
			z;


		x = sun_quad[count].x * sun_matrix[0][0] + sun_quad[count].y * sun_matrix[1][0] + sun_quad[count].z * sun_matrix[2][0];
		y = sun_quad[count].x * sun_matrix[0][1] + sun_quad[count].y * sun_matrix[1][1] + sun_quad[count].z * sun_matrix[2][1];
		z = sun_quad[count].x * sun_matrix[0][2] + sun_quad[count].y * sun_matrix[1][2] + sun_quad[count].z * sun_matrix[2][2];

		sun_quad[count].x = x;
		sun_quad[count].y = y;
		sun_quad[count].z = z;
	}

	//
	// Clip the sun to the horizon
	//

	clip_3d_coord = 0;

	sun_polygon = horizon_clip_3d_polygon ( sun_quad );

	if ( sun_polygon )
	{

		//
		// Rotate the polygon around to the users viewpoint
		//
	
		vert = sun_polygon;
	
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

			return ( NULL );
		}


		if ( outcode & CLIP_HITHER )
		{
	
			sun_polygon = hither_clip_3d_polygon ( sun_polygon, &outcode );

			if ( !sun_polygon )
			{

				return ( NULL );
			}
		}
	
		if ( outcode )
		{

			apply_perspective_to_polygon_texture ( sun_polygon );
			
			sun_polygon = clip_3d_polygon ( sun_polygon, outcode );

			if ( !sun_polygon )
			{

				return ( NULL );
			}

			remove_perspective_from_polygon_texture ( sun_polygon );
		}

		if ( sun_polygon )
		{

			vertex
				*p;

			p = sun_polygon;

			while ( p )
			{

				if ( p->q < clip_yonder_reciprocal )
				{

					p->q = clip_yonder_reciprocal;
				}

				p = p->next_vertex;
			}
		}

		return ( sun_polygon );
	}
	else
	{

		return ( NULL );
	}
}
