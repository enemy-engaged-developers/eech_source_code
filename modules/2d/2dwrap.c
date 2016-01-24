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

#include "graphics.h"

#include "2d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_pixel (float x, float y, const rgb_colour col)
{
	float
		xt,
		yt;

	int
		xi,
		yi;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	xt = (x * active_2d_environment->composite_transformation[0][0]) +
		  (y * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	yt = (x * active_2d_environment->composite_transformation[0][1]) +
		  (y * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	xt += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	yt -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	convert_float_to_int (xt, &xi);
	convert_float_to_int (yt, &yi);

	set_clipped_pixel (xi, yi, col);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_line (float x1, float y1, float x2, float y2, const rgb_colour col)
{
	float
		x1t,
		y1t,
		x2t,
		y2t;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	x1t = (x1 * active_2d_environment->composite_transformation[0][0]) +
		   (y1 * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y1t = (x1 * active_2d_environment->composite_transformation[0][1]) +
			(y1 * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x2t = (x2 * active_2d_environment->composite_transformation[0][0]) +
			(y2 * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y2t = (x2 * active_2d_environment->composite_transformation[0][1]) +
			(y2 * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x1t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	x2t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	y1t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;
	y2t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	if (clip_line (&x1t, &y1t, &x2t, &y2t))
	{
		draw_line (x1t, y1t, x2t, y2t, col);
	}
}

void draw_2d_dash_line(float x1, float y1, float x2, float y2, const rgb_colour col1, rgb_colour col2, float length, int thick)
{
	int i;
	vec2d magn;
	float angle_cos, angle_sin, x0 = x2, y0 = y2;
	
	magn.x = x2 - x1;
	magn.y = y2 - y1;
	
	i = (int) (get_2d_vector_magnitude(&magn) / length);
	angle_cos = magn.x / (sqrt(magn.x * magn.x + magn.y * magn.y));
	angle_sin = magn.y / (sqrt(magn.x * magn.x + magn.y * magn.y));
	
	for (; i >= 0; i--)
	{
		if (!i)
		{
			x2 = x0;
			y2 = y0;
		}
		else
		{
			x2 = x1 + length * angle_cos;
			y2 = y1 + length * angle_sin;
		}
		
		if (thick)
			draw_2d_half_thick_line (x1, y1, x2, y2, (i % 2) ? col1 : col2);
		else
			draw_2d_line (x1, y1, x2, y2, (i % 2) ? col1 : col2);

		x1 = x2;
		y1 = y2;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_half_thick_line (float x1, float y1, float x2, float y2, const rgb_colour col)
{
	float
		x1t,
		y1t,
		x2t,
		y2t;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	x1t = (x1 * active_2d_environment->composite_transformation[0][0]) +
		   (y1 * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y1t = (x1 * active_2d_environment->composite_transformation[0][1]) +
			(y1 * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x2t = (x2 * active_2d_environment->composite_transformation[0][0]) +
			(y2 * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y2t = (x2 * active_2d_environment->composite_transformation[0][1]) +
			(y2 * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x1t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	x2t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	y1t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;
	y2t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	if (clip_line (&x1t, &y1t, &x2t, &y2t))
	{
		draw_half_thick_line (x1t, y1t, x2t, y2t, col);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_filled_triangle (float x1, float y1, float x2, float y2, float x3, float y3, const rgb_colour col)
{
	float
		x1t,
		y1t,
		x2t,
		y2t,
		x3t,
		y3t;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	x1t = (x1 * active_2d_environment->composite_transformation[0][0]) +
		   (y1 * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y1t = (x1 * active_2d_environment->composite_transformation[0][1]) +
			(y1 * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x2t = (x2 * active_2d_environment->composite_transformation[0][0]) +
			(y2 * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y2t = (x2 * active_2d_environment->composite_transformation[0][1]) +
			(y2 * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x3t = (x3 * active_2d_environment->composite_transformation[0][0]) +
			(y3 * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y3t = (x3 * active_2d_environment->composite_transformation[0][1]) +
			(y3 * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x1t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	x2t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	x3t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;

	y1t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;
	y2t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;
	y3t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	draw_software_plain_triangle ( x1t, y1t, x2t, y2t, x3t, y3t, col );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_2d_mono_font_position (float x, float y)
{
	float
		x1t,
		y1t;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	x1t = (x * active_2d_environment->composite_transformation[0][0]) +
		   (y * active_2d_environment->composite_transformation[1][0]) +
			active_2d_environment->composite_transformation[2][0];

	y1t = (x * active_2d_environment->composite_transformation[0][1]) +
			(y * active_2d_environment->composite_transformation[1][1]) +
			active_2d_environment->composite_transformation[2][1];

	x1t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	y1t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	set_mono_font_position (x1t, y1t);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_world_position (const float x, const float y, float *x_world, float *y_world)
{
	ASSERT (active_2d_environment);

	validate_2d_inverse_composite_transformation_matrix (active_2d_environment);

	*x_world = (x * active_2d_environment->inverse_composite_transformation[0][0]) +
		   	  (y * active_2d_environment->inverse_composite_transformation[1][0]) +
				  active_2d_environment->inverse_composite_transformation[2][0];

	*y_world = (x * active_2d_environment->inverse_composite_transformation[0][1]) +
				  (y * active_2d_environment->inverse_composite_transformation[1][1]) +
				  active_2d_environment->inverse_composite_transformation[2][1];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_int_screen_coordinates (const float wx, const float wy, int *x, int *y)
{
	float
		xt,
		yt;

	int
		xi,
		yi;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	xt = (wx * active_2d_environment->composite_transformation[0][0]) +
		  (wy * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	yt = (wx * active_2d_environment->composite_transformation[0][1]) +
		  (wy * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	convert_float_to_int (xt, &xi);
	convert_float_to_int (yt, &yi);

	*x = xi;

	*y = yi;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_float_screen_coordinates (float wx, float wy, float *x, float *y)
{
	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	*x = (wx * active_2d_environment->composite_transformation[0][0]) +
		  (wy * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	*y = (wx * active_2d_environment->composite_transformation[0][1]) +
		  (wy * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_float_screen_x_coordinate (const float wx, float *x)
{
	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	*x = (wx * active_2d_environment->composite_transformation[0][0]) +
		  active_2d_environment->composite_transformation[2][0];

	*x -= active_2d_environment->offset_x;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_2d_float_screen_y_coordinate (const float wy, float *y)
{
	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	*y = (wy * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	*y -= active_2d_environment->offset_y;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_mono_sprite (const char *sprite_ptr, float x, float y, const rgb_colour colour)
{
	float
		xt,
		yt;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	xt = (x * active_2d_environment->composite_transformation[0][0]) +
		  (y * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	yt = (x * active_2d_environment->composite_transformation[0][1]) +
		  (y * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	xt += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	yt -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	draw_mono_sprite (sprite_ptr, xt, yt, colour);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_circle (float x, float y, const float r, const rgb_colour col)
{
	float
		xt,
		yt,
		rt;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	xt = (x * active_2d_environment->composite_transformation[0][0]) +
		  (y * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	yt = (x * active_2d_environment->composite_transformation[0][1]) +
		  (y * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	rt = r * active_2d_environment->window_scaling[0][0];

	xt += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	yt -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	draw_circle (xt, yt, rt, col);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_arc (float x, float y, const float r, unsigned part, const rgb_colour col)
{
	float
		xt,
		yt,
		rt;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	xt = (x * active_2d_environment->composite_transformation[0][0]) +
		  (y * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	yt = (x * active_2d_environment->composite_transformation[0][1]) +
		  (y * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	rt = r * active_2d_environment->window_scaling[0][0];

	xt += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	yt -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	draw_arc (xt, yt, rt, part, col);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_hatched_area (float x1, float y1, float x2, float y2, const rgb_colour col)
{
	float
		x1t,
		y1t,
		x2t,
		y2t;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	x1t = (x1 * active_2d_environment->composite_transformation[0][0]) +
		  (y1 * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	y1t = (x1 * active_2d_environment->composite_transformation[0][1]) +
		  (y1 * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	x2t = (x2 * active_2d_environment->composite_transformation[0][0]) +
		  (y2 * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	y2t = (x2 * active_2d_environment->composite_transformation[0][1]) +
		  (y2 * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	x1t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	x2t += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;

	y1t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;
	y2t -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	x1t = bound (x1t, active_viewport.x_min, active_viewport.x_max);
	y1t = bound (y1t, active_viewport.y_min, active_viewport.y_max);

	x2t = bound (x2t, active_viewport.x_min, active_viewport.x_max);
	y2t = bound (y2t, active_viewport.y_min, active_viewport.y_max);

	set_hatched_block (x1t, y2t, x2t, y1t, col);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_hatched_circle (float x, float y, const float r, const rgb_colour col)
{
	float
		xt,
		yt,
		rt;

	ASSERT (active_2d_environment);

	validate_2d_composite_transformation_matrix (active_2d_environment);

	xt = (x * active_2d_environment->composite_transformation[0][0]) +
		  (y * active_2d_environment->composite_transformation[1][0]) +
		  active_2d_environment->composite_transformation[2][0];

	yt = (x * active_2d_environment->composite_transformation[0][1]) +
		  (y * active_2d_environment->composite_transformation[1][1]) +
		  active_2d_environment->composite_transformation[2][1];

	xt += active_2d_environment->offset_x * active_2d_environment->window_scaling[0][0] * 0.9;
	yt -= active_2d_environment->offset_y * active_2d_environment->window_scaling[1][1] * 0.9;

	rt = r * active_2d_environment->window_scaling[0][0];

	draw_hatched_filled_circle (xt, yt, rt, col);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_2d_box(float x1_c, float y1_c, float x2_c, float y2_c, int filled, int thick_border, rgb_colour colour)
{
	float x1, x2, y1, y2;
	float x_min, x_max, y_min, y_max;

	get_2d_float_screen_coordinates (x1_c, y1_c, &x1, &y1);
	get_2d_float_screen_coordinates (x2_c, y2_c, &x2, &y2);

	x1 = bound(x1, active_2d_environment->vp.x_min, active_2d_environment->vp.x_max - 1);
	x2 = bound(x2, active_2d_environment->vp.x_min, active_2d_environment->vp.x_max - 1);
	y1 = bound(y1, active_2d_environment->vp.x_min, active_2d_environment->vp.x_max - 1);
	y2 = bound(y2, active_2d_environment->vp.x_min, active_2d_environment->vp.x_max - 1);

	x_min = min(x1, x2); x_max = max(x1, x2);
	y_min = min(y1, y2); y_max = max(y1, y2);

	if (filled)
	{

		// set block likes to have its smallest arguments first
		set_block(x_min, y_min, x_max, y_max, colour);
	}
	else
	{
		draw_line(x_min, y_min, x_max, y_min, colour);
		draw_line(x_min, y_min, x_min, y_max, colour);
		draw_line(x_min, y_max, x_max, y_max, colour);
		draw_line(x_max, y_min, x_max, y_max, colour);

		if (thick_border)
		{
			draw_line(x_min, y_min-1, x_max, y_min-1, colour);
			draw_line(x_min-1, y_min, x_min-1, y_max, colour);
			draw_line(x_min, y_max+1, x_max, y_max+1, colour);
			draw_line(x_max+1, y_min, x_max+1, y_max, colour);
		}
	}
}
#endif
