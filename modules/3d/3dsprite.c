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

void draw_3d_sprite ( object_3d_sprite *sprite )
{

	float
		x,
		y,
		z,
		q,
		i,
		j,
		radius,
		roll,
		sin_roll,
		cos_roll,
		width,
		height;

	vertex
		*poly = nullptr,
		sprite_quad[4];

	vec2d
		point1,
		point2,
		point3,
		point4;

	int
		outcode;

	number_of_sprites_in_3d_scene++;

	x = sprite->position.x;
	y = sprite->position.y;
	z = sprite->position.z;

	radius = sprite->radius;

	roll = sprite->roll;
	sin_roll = sin ( roll );
	cos_roll = cos ( roll );

	point1.x = ( -0.5 * ( +cos_roll ) ) + ( +0.5 * ( +sin_roll ) );
	point1.y = ( -0.5 * ( -sin_roll ) ) + ( +0.5 * ( +cos_roll ) );

	point2.x = ( -0.5 * ( +cos_roll ) ) + ( -0.5 * ( +sin_roll ) );
	point2.y = ( -0.5 * ( -sin_roll ) ) + ( -0.5 * ( +cos_roll ) );

	point3.x = ( +0.5 * ( +cos_roll ) ) + ( -0.5 * ( +sin_roll ) );
	point3.y = ( +0.5 * ( -sin_roll ) ) + ( -0.5 * ( +cos_roll ) );

	point4.x = ( +0.5 * ( +cos_roll ) ) + ( +0.5 * ( +sin_roll ) );
	point4.y = ( +0.5 * ( -sin_roll ) ) + ( +0.5 * ( +cos_roll ) );

	q = 1.0 / z;

	i = ( active_3d_environment->screen_i_scale * x * q );
	j = ( active_3d_environment->screen_j_scale * y * q );

	i = active_3d_environment->x_origin + i;
	j = active_3d_environment->y_origin - j;

	width = active_3d_environment->screen_i_scale * radius * q;
	height = active_3d_environment->screen_j_scale * radius * q;

	sprite_quad[0].q = q;
	sprite_quad[0].i = i + ( point1.x * width );
	sprite_quad[0].j = j + ( point1.y * height );
	sprite_quad[0].u = 0;
	sprite_quad[0].v = 0;
	sprite_quad[0].outcode = generate_3d_outcode ( sprite_quad[0].i, sprite_quad[0].j );
	sprite_quad[0].next_vertex = &sprite_quad[1];

	sprite_quad[1].q = q;
	sprite_quad[1].i = i + ( point2.x * width );
	sprite_quad[1].j = j + ( point2.y * height );
	sprite_quad[1].u = 1;
	sprite_quad[1].v = 0;
	sprite_quad[1].outcode = generate_3d_outcode ( sprite_quad[1].i, sprite_quad[1].j );
	sprite_quad[1].next_vertex = &sprite_quad[2];

	sprite_quad[2].q = q;
	sprite_quad[2].i = i + ( point3.x * width );
	sprite_quad[2].j = j + ( point3.y * height );
	sprite_quad[2].u = 1;
	sprite_quad[2].v = 1;
	sprite_quad[2].outcode = generate_3d_outcode ( sprite_quad[2].i, sprite_quad[2].j );
	sprite_quad[2].next_vertex = &sprite_quad[3];

	sprite_quad[3].q = q;
	sprite_quad[3].i = i + ( point4.x * width );
	sprite_quad[3].j = j + ( point4.y * height );
	sprite_quad[3].u = 0;
	sprite_quad[3].v = 1;
	sprite_quad[3].outcode = generate_3d_outcode ( sprite_quad[3].i, sprite_quad[3].j );
	sprite_quad[3].next_vertex = NULL;

	outcode = sprite_quad[0].outcode;
	outcode |= sprite_quad[1].outcode;
	outcode |= sprite_quad[2].outcode;
	outcode |= sprite_quad[3].outcode;

	poly = sprite_quad;

	if ( outcode )
	{

		clip_3d_coord = 0;

		poly = clip_3d_polygon ( poly, outcode );
	}

	if ( poly )
	{

		real_colour
			specular_colour;

		specular_colour.colour = 0;
		specular_colour.alpha = 255;

		set_d3d_sampler_state ( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		set_d3d_sampler_state ( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		set_d3d_sampler_state ( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT );

		if (sprite->additive && (active_3d_environment->render_filter == RENDER_INFRARED || active_3d_environment->render_filter == RENDER_MONOCHROME))
		{
			real_colour
				colour;

			colour.colour = sprite->colour;
			colour.red = colour.green = colour.blue = 255;
			sprite->colour = colour.colour;
		}
		else if (active_3d_environment->render_filter != RENDER_CLEAR )
		{

			float
				max_multiplier;
			real_colour
				colour;
			light_colour
				ambient;

			//
			// Colour the additive to the light colour
			//

			ambient.red = ambient_3d_light.colour.red + 0.75 * current_3d_sun->colour.red;
			ambient.green = ambient_3d_light.colour.green + 0.75 * current_3d_sun->colour.green;
			ambient.blue = ambient_3d_light.colour.blue + 0.75 * current_3d_sun->colour.blue;

			max_multiplier = max(ambient.red, max(ambient.green,ambient.blue));

			if (max_multiplier > 1 || sprite->additive && max_multiplier < 1)
			{
				ambient.red /= max_multiplier;
				ambient.green /= max_multiplier;
				ambient.blue /= max_multiplier;
			}

			colour.colour = sprite->colour;
			colour.red *= ambient.red;
			colour.green *= ambient.green;
			colour.blue *= ambient.blue;
			sprite->colour = colour.colour;
		}

		if ( sprite->additive )
		{

			set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_ONE );
			set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_ONE );

			set_d3d_flat_shaded_textured_renderstate ( sprite->texture );

			draw_wbuffered_flat_shaded_textured_polygon ( poly, *( ( real_colour * ) &sprite->colour ), specular_colour );
		}
		else
		{



			set_d3d_int_state ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			set_d3d_int_state ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

			set_d3d_flat_shaded_textured_renderstate ( sprite->texture );

			draw_wbuffered_flat_shaded_textured_polygon ( poly, *( ( real_colour * ) &sprite->colour ), specular_colour );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
