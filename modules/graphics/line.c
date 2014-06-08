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

#include "graphics.h"

#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void clip_line_left ( float *x1, float *y1, float *x2, float *y2 );

static void clip_line_right ( float *x1, float *y1, float *x2, float *y2 );

static void clip_line_top ( float *x1, float *y1, float *x2, float *y2 );

static void clip_line_bottom ( float *x1, float *y1, float *x2, float *y2 );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_line ( float fx1, float fy1, float fx2, float fy2, rgb_colour colour )
{

	ASSERT ( active_screen );

	if ( get_screen_locked ( active_screen ) )
	{

		int
			x1,
			y1,
			x2,
			y2,
			dx,
			dy,
			error,
			screen_pitch;


		unsigned int
			*screen_data;

		{

			unsigned int
				col;

			col = colour.colour;

			screen_data = get_screen_data (active_screen);
			screen_pitch = get_screen_pitch (active_screen);

			convert_float_to_int ( fx1, &x1 );
			convert_float_to_int ( fy1, &y1 );
			convert_float_to_int ( fx2, &x2 );
			convert_float_to_int ( fy2, &y2 );

			dx = x2 - x1;

			if ( dx < 0 )
			{

				dx = -dx;

				dy = y2 - y1;

				if ( dy < 0 )
				{

					dy = -dy;

					if ( dx > dy )
					{

						error = ( ( dx + 1 ) >> 1 );

						for ( ; x1 >= x2; x1-- )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dy ) <= 0 )
							{

								error += dx;

								y1--;
							}
						}
					}
					else
					{

						error = ( (  dy + 1 ) >> 1 );

						for ( ; y1>=y2; y1-- )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dx ) <= 0 )
							{

								error += dy;

								x1--;
							}
						}
					}
				}
				else
				{

					if ( dx > dy )
					{

						error = ( ( dx + 1 ) >> 1 );

						for ( ; x1 >= x2; x1-- )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dy ) <= 0 )
							{

								error += dx;

								y1++;
							}
						}
					}
					else
					{

						error = ( ( dy + 1 ) >> 1 );

						for ( ; y1 <= y2; y1++ )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dx ) <= 0 )
							{

								error += dy;

								x1--;
							}
						}
					}
				}
			}
			else
			{
				dy = y2 - y1;

				if ( dy < 0 )
				{

					dy = -dy;

					if ( dx > dy )
					{

						error = ( ( dx + 1 ) >> 1 );

						for ( ; x1 <= x2; x1++ )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dy ) <= 0 )
							{

								error += dx;

								y1--;
							}
						}
					}
					else
					{

						error = ( ( dy + 1 ) >> 1 );

						for ( ; y1 >= y2; y1 -- )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dx ) <= 0 )
							{

								error += dy;

								x1++;
							}
						}
					}
				}
				else
				{

					if ( dx > dy )
					{

						error = ( ( dx + 1 ) >> 1 );

						for ( ; x1 <= x2; x1 ++ )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dy ) <= 0 )
							{

								error += dx;

								y1 ++;
							}
						}
					}
					else
					{

						error = ( ( dy + 1 ) >> 1 );

						for ( ; y1 <= y2; y1++ )
						{

							*((screen_data + y1 * screen_pitch) + x1) = col;

							if ( ( error -= dx ) <= 0 )
							{

								error += dy;

								x1 ++;
							}
						}
					}
				}
			}
		}
	}
	else
	{

		if ( d3d_in_3d_scene )
		{

			vertex
				*poly,
				*point1,
				*point2,
				line[2];

			LPTLVERTEX
				vertices;

			int
				outcode,
				outcode2;

			line[0].i = fx1;
			line[0].j = fy1;
			line[0].outcode = generate_outcode ( fx1, fy1 );
			line[0].next_vertex = &line[1];

			line[1].i = fx2;
			line[1].j = fy2;
			line[1].outcode = generate_outcode ( fx2, fy2 );
			line[1].next_vertex = NULL;

			outcode = outcode2 = line[0].outcode;
			outcode |= line[1].outcode;
			outcode2 &= line[1].outcode;

			poly = line;

			if ( outcode2 == 0 )
			{

				real_colour
					col;

				if ( outcode )
				{

					clip_3d_coord = 0;

					poly = clip_3d_polygon ( poly, ( unsigned char ) outcode );
				}

				if ( !poly )
				{

					return;
				}

				col.red = colour.r;
				col.green = colour.g;
				col.blue = colour.b;
				col.alpha = 255;	//colour.a;

				set_d3d_alpha_fog_zbuffer ( FALSE, TRUE, FALSE, FALSE );
//				set_d3d_alpha_blending ( FALSE );
//				set_d3d_zbuffer_comparison ( FALSE );
//				set_d3d_zbuffer_writing ( FALSE );

				set_d3d_int_state ( D3DRS_SPECULARENABLE, FALSE );

				set_d3d_texture_stage_state ( 0, D3DTSS_COLOROP, D3DTOP_DISABLE );

				vertices = get_d3d_line_vertices_points_address ();

				point1 = poly->next_vertex;
				point2 = poly;

				vertices[0].sx = point1->i;
				vertices[0].sy = point1->j;
				vertices[0].rhw = 0.1;//point1->q;
				vertices[0].sz = 0.1;//( point1->q * zbuffer_factor ) + zbuffer_constant;
				vertices[0].color = col.colour;	//*( ( D3DCOLOR * ) &colour );
				vertices[0].specular = d3d_fog_intensity;

				vertices[1].sx = point2->i;
				vertices[1].sy = point2->j;
				vertices[1].rhw = 0.1;	//point2->q;
				vertices[1].sz = 0.1;	//( point2->q * zbuffer_factor ) + zbuffer_constant;
				vertices[1].color = col.colour;	//*( ( D3DCOLOR * ) &colour );
				vertices[1].specular = d3d_fog_intensity;

				draw_line_primitive ( vertices );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_thick_line ( float fx1, float fy1, float fx2, float fy2, rgb_colour colour_rgb, float thickness )
{

	ASSERT ( active_screen );

	if ( d3d_in_3d_scene )
	{

		unsigned char
			outcode,
			outcode2;

		vertex
			vertices[4];

		vec3d
			normal;

		real_colour
			colour,
			specular;

		specular.red = 0;
		specular.green = 0;
		specular.blue = 0;
		specular.alpha = 255;

		colour.red = colour_rgb.r;
		colour.green = colour_rgb.g;
		colour.blue = colour_rgb.b;
		colour.alpha = colour_rgb.a;

		normal.x = fy2 - fy1;
		normal.z = fx1 - fx2;
		normal.y = 0;

		normalise_any_3d_vector ( &normal );
		normal.x *= thickness;
		normal.z *= thickness;

		vertices[0].i = fx1 - normal.x;
		vertices[0].j = fy1 - normal.z;
		vertices[1].i = fx1 + normal.x;
		vertices[1].j = fy1 + normal.z;
		vertices[2].i = fx2 - normal.x;
		vertices[2].j = fy2 - normal.z;
		vertices[3].i = fx2 + normal.x;
		vertices[3].j = fy2 + normal.z;

		vertices[0].outcode = generate_outcode ( vertices[0].i, vertices[0].j );
		vertices[1].outcode = generate_outcode ( vertices[1].i, vertices[1].j );
		vertices[2].outcode = generate_outcode ( vertices[2].i, vertices[2].j );
		vertices[3].outcode = generate_outcode ( vertices[3].i, vertices[3].j );

		vertices[0].next_vertex = &vertices[1];
		vertices[1].next_vertex = &vertices[3];
		vertices[3].next_vertex = &vertices[2];
		vertices[2].next_vertex = NULL;

		vertices[0].z = 10; vertices[0].q = 0.1;
		vertices[1].z = 10; vertices[1].q = 0.1;
		vertices[2].z = 10; vertices[2].q = 0.1;
		vertices[3].z = 10; vertices[3].q = 0.1;

		outcode = vertices[0].outcode; outcode2 = vertices[0].outcode;
		outcode |= vertices[1].outcode; outcode2 &= vertices[1].outcode;
		outcode |= vertices[2].outcode; outcode2 &= vertices[2].outcode;
		outcode |= vertices[3].outcode; outcode2 &= vertices[3].outcode;

		if ( outcode2 == 0 )
		{

			vertex
				*poly;

			poly = &vertices[0];

			if ( outcode )
			{

				clip_3d_coord = 0;;

				poly = clip_3d_polygon ( poly, outcode );
			}

			if ( poly )
			{

				zbuffer_constant = zbuffer_constant_elevated_bias;

				draw_wbuffered_plain_polygon ( poly, colour, specular );

				zbuffer_constant = zbuffer_constant_normal_bias;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_half_thick_line ( float fx1, float fy1, float fx2, float fy2, rgb_colour colour )
{

	int
		x,
		y,
		x1,
		y1,
		x2,
		y2,
		dx,
		dy,
		error,
		screen_pitch;

	unsigned int
		*screen_data;

	{

		ULONG
			col;

		ASSERT ( active_screen );
		ASSERT ( get_screen_locked ( active_screen ) );

		col = colour.colour;

		screen_data = get_screen_data (active_screen);
		screen_pitch = get_screen_pitch (active_screen);

		convert_float_to_int ( fx1, &x1 );
		convert_float_to_int ( fy1, &y1 );
		convert_float_to_int ( fx2, &x2 );
		convert_float_to_int ( fy2, &y2 );

		dx = x2 - x1;

		if ( dx < 0 )
		{

			dx = -dx;

			dy = y2 - y1;

			if ( dy < 0 )
			{

				dy = -dy;

				if ( dx > dy )
				{

					error = ( ( dx + 1 ) >> 1 );

					for ( ; x1 >= x2; x1-- )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						y = y1 - 1;

						if ( y >= active_int_viewport.y_min )
						{

							*((screen_data + y * screen_pitch) + x1 ) = col;
						}

						if ( ( error -= dy ) <= 0 )
						{

							error += dx;

							y1--;
						}
					}
				}
				else
				{

					error = ( (  dy + 1 ) >> 1 );

					for ( ; y1>=y2; y1-- )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						x = x1 - 1;

						if ( x >= active_int_viewport.x_min )
						{

							*( (screen_data + y1 * screen_pitch) + x ) = col;
						}

						if ( ( error -= dx ) <= 0 )
						{

							error += dy;

							x1--;
						}
					}
				}
			}
			else
			{

				if ( dx > dy )
				{

					error = ( ( dx + 1 ) >> 1 );

					for ( ; x1 >= x2; x1-- )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						y = y1 - 1;

						if ( y >= active_int_viewport.y_min )
						{

							*( (screen_data + y * screen_pitch) + x1 ) = col;
						}

						if ( ( error -= dy ) <= 0 )
						{

							error += dx;

							y1++;
						}
					}
				}
				else
				{

					error = ( ( dy + 1 ) >> 1 );

					for ( ; y1 <= y2; y1++ )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						x = x1 - 1;

						if ( x >= active_int_viewport.x_min )
						{

							*((screen_data + y1 * screen_pitch) + x ) = col;
						}

						if ( ( error -= dx ) <= 0 )
						{

							error += dy;

							x1--;
						}
					}
				}
			}
		}
		else
		{
			dy = y2 - y1;

			if ( dy < 0 )
			{

				dy = -dy;

				if ( dx > dy )
				{

					error = ( ( dx + 1 ) >> 1 );

					for ( ; x1 <= x2; x1++ )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						y = y1 - 1;

						if ( y >= active_int_viewport.y_min )
						{

							*((screen_data + y * screen_pitch) + x1 ) = col;
						}

						if ( ( error -= dy ) <= 0 )
						{

							error += dx;

							y1--;
						}
					}
				}
				else
				{

					error = ( ( dy + 1 ) >> 1 );

					for ( ; y1 >= y2; y1 -- )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						x = x1 - 1;

						if ( x >= active_int_viewport.x_min )
						{

							*((screen_data + y1 * screen_pitch) + x ) = col;
						}

						if ( ( error -= dx ) <= 0 )
						{

							error += dy;

							x1++;
						}
					}
				}
			}
			else
			{

				if ( dx > dy )
				{

					error = ( ( dx + 1 ) >> 1 );

					for ( ; x1 <= x2; x1 ++ )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						y = y1 - 1;

						if ( y >= active_int_viewport.y_min )
						{

							*( (screen_data + y * screen_pitch) + x1 ) = col;
						}

						if ( ( error -= dy ) <= 0 )
						{

							error += dx;

							y1 ++;
						}
					}
				}
				else
				{

					error = ( ( dy + 1 ) >> 1 );

					for ( ; y1 <= y2; y1++ )
					{

						*((screen_data + y1 * screen_pitch) + x1) = col;

						x = x1 - 1;

						if ( x >= active_int_viewport.x_min )
						{

							*((screen_data + y1 * screen_pitch) + x ) = col;
						}

						if ( ( error -= dx ) <= 0 )
						{

							error += dy;

							x1 ++;
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int clip_line ( float *x1, float *y1, float *x2, float *y2 )
{

	int
		outcode1,
		outcode2;

	outcode1 = generate_outcode ( *x1, *y1 );

	outcode2 = generate_outcode ( *x2, *y2 );

	if ( outcode1 & outcode2 )
	{

		//
		// Line does not intersect with the screen
		//

		return ( FALSE );
	}
	else
	{

		if ( ! ( outcode1 | outcode2 ) )
		{

			return ( TRUE );
		}
	}

	if ( *( int * ) x1 < *( ( int * ) &active_viewport.x_min ) )
	{

		clip_line_left ( x1, y1, x2, y2 );
	}

	if ( *( int * ) x2 < *( ( int * ) &active_viewport.x_min ) )
	{

		clip_line_left ( x2, y2, x1, y1 );
	}

	if ( *( int * ) x1 > *( ( int * ) &active_viewport.x_max ) )
	{

		clip_line_right ( x1, y1, x2, y2 );
	}

	if ( *( int * ) x2 > *( ( int * ) &active_viewport.x_max ) )
	{

		clip_line_right ( x2, y2, x1, y1 );
	}

	if ( *( int * ) y1 < *( ( int * ) &active_viewport.y_min ) )
	{

		clip_line_top ( x1, y1, x2, y2 );
	}

	if ( *( int * ) y2 < *( ( int * ) &active_viewport.y_min ) )
	{

		clip_line_top ( x2, y2, x1, y1 );
	}

	if ( *( int * ) y1 > *( ( int * ) &active_viewport.y_max ) )
	{

		clip_line_bottom ( x1, y1, x2, y2 );
	}

	if ( *( int * ) y2 > *( ( int * ) &active_viewport.y_max ) )
	{

		clip_line_bottom ( x2, y2, x1, y1 );
	}

	outcode1 = generate_outcode ( *x1, *y1 );

	outcode2 = generate_outcode ( *x2, *y2 );

	if ( outcode1 | outcode2 )
	{

		return ( FALSE );
	}

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clip_line_left ( float *x1, float *y1, float *x2, float *y2 )
{

	float
		numerator,
		denominator,
		t;

	numerator = active_viewport.x_min - *x2;

	denominator = *x2 - *x1;

	t = numerator / denominator;

	*x1 = active_viewport.x_min;

	*y1 = *y2 + ( t * ( *y2 - *y1 ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clip_line_right ( float *x1, float *y1, float *x2, float *y2 )
{

	float
		numerator,
		denominator,
		t;

	numerator = active_viewport.x_max - *x2;

	denominator = *x2 - *x1;

	t = numerator / denominator;

	*x1 = active_viewport.x_max;

	*y1 = *y2 + ( t * ( *y2 - *y1 ) );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clip_line_top ( float *x1, float *y1, float *x2, float *y2 )
{

	float
		numerator,
		denominator,
		t;

	numerator = active_viewport.y_min - *y2;

	denominator = *y2 - *y1;

	t = numerator / denominator;

	*x1 = *x2 + ( t * ( *x2 - *x1 ) );

	*y1 = active_viewport.y_min;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clip_line_bottom ( float *x1, float *y1, float *x2, float *y2 )
{
	float
		numerator,
		denominator,
		t;

	numerator = active_viewport.y_max - *y2;

	denominator = *y2 - *y1;

	t = numerator / denominator;

	*x1 = *x2 + ( t * ( *x2 - *x1 ) );

	*y1 = active_viewport.y_max;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_outcode ( float i, float j )
{

	unsigned int
		ixmax,
		ixmin,
		iymax,
		iymin;

	float
		oxmax,
		oxmin,
		oymax,
		oymin;

	oxmax = active_viewport.x_max - i;
	oxmin = i - active_viewport.x_min;
	oymax = active_viewport.y_max - j;
	oymin = j - active_viewport.y_min;

	ixmax = *( ( unsigned int * ) &oxmax );
	ixmin = *( ( unsigned int * ) &oxmin );
	iymax = *( ( unsigned int * ) &oymax );
	iymin = *( ( unsigned int * ) &oymin );

	ixmin >>= 31;
	iymin &= 0x80000000;
	ixmax >>= 29;
	iymax &= 0x80000000;
	iymin >>= 30;
	ixmin &= 0x00000001;
	iymax >>= 28;
	ixmax &= 0x00000004;
	ixmin |= iymin;
	ixmax |= iymax;

	return ( ixmin | ixmax );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_arrow (float centre_x, float centre_y, float dot_x, float dot_y, float scale_x, float scale_y, rgb_colour colour)
{
	draw_line (centre_x, centre_y, dot_x, dot_y, colour);
	if (scale_x > 1.1)
	{
		draw_line (centre_x + 1, centre_y, dot_x + 1, dot_y, colour);
		draw_line (centre_x - 1, centre_y, dot_x - 1, dot_y, colour);
		draw_line (centre_x + 1, centre_y, dot_x + 1, dot_y, colour);
		draw_line (centre_x - 1, centre_y, dot_x - 1, dot_y, colour);
	}
	if (scale_y > 1.1)
	{
		draw_line (centre_x, centre_y + 1, dot_x, dot_y + 1, colour);
		draw_line (centre_x, centre_y - 1, dot_x, dot_y - 1, colour);
		draw_line (centre_x, centre_y + 1, dot_x, dot_y + 1, colour);
		draw_line (centre_x, centre_y - 1, dot_x, dot_y - 1, colour);
	}
	if (scale_x > 2.1)
	{
		draw_line (centre_x + 2, centre_y, dot_x + 2, dot_y, colour);
		draw_line (centre_x - 2, centre_y, dot_x - 2, dot_y, colour);
		draw_line (centre_x + 2, centre_y, dot_x + 2, dot_y, colour);
		draw_line (centre_x - 2, centre_y, dot_x - 2, dot_y, colour);
	}
	if (scale_y > 2.1)
	{
		draw_line (centre_x, centre_y + 2, dot_x, dot_y + 2, colour);
		draw_line (centre_x, centre_y - 2, dot_x, dot_y - 2, colour);
		draw_line (centre_x, centre_y + 2, dot_x, dot_y + 2, colour);
		draw_line (centre_x, centre_y - 2, dot_x, dot_y - 2, colour);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
