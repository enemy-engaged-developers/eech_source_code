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



#include	"graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_plain_line ( vertex *point1, vertex *point2 );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_software_pixel ( int x, int y, unsigned int colour )
{

	unsigned int
		*data = nullptr;

	unsigned int
		*pixels = nullptr;

	data = get_screen_data ( active_screen );

	pixels = data + ( y * get_screen_pitch ( active_screen ) );

	pixels += x;

	*pixels = colour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_plain_line ( vertex *line, unsigned int whole_colour, float red, float green, float blue )
{

	int
		x1,
		y1,
		x2,
		y2,
		dx,
		dy,
		error;

	unsigned short int
		colour;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	colour = whole_colour;

	convert_float_to_int ( line->i, &x1 );

	convert_float_to_int ( line->j, &y1 );

	convert_float_to_int ( line->next_vertex->i, &x2 );

	convert_float_to_int ( line->next_vertex->j, &y2 );

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

				for ( ; x1 > x2; x1-- )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1--;
					}
				}
			}
			else
			{

				error = ( (  dy + 1 ) >> 1 );

				for ( ; y1 > y2; y1-- )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
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

				for ( ; x1 > x2; x1-- )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1++;
					}
				}
			}
			else
			{

				error = ( ( dy + 1 ) >> 1 );

				for ( ; y1 < y2; y1++ )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
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

				for ( ; x1 < x2; x1++ )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1--;
					}
				}
			}
			else
			{

				error = ( ( dy + 1 ) >> 1 );

				for ( ; y1 > y2; y1 -- )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
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

				for ( ; x1 < x2; x1 ++ )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1 ++;
					}
				}
			}
			else
			{

				error = ( ( dy + 1 ) >> 1 );

				for ( ; y1 < y2; y1++ )
				{

					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
					{

						error += dy;

						x1 ++;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_software_gouraud_shaded_line ( vertex *line, unsigned int colour, float red, float green, float blue )
{
/*
	int
		x1,
		y1,
		x2,
		y2,
		dx,
		dy,
		error,
		int_intensity;

	unsigned int
		*colour_table = nullptr;

	float
		intensity,
		intensity2,
		dintensity;

	ASSERT ( active_screen );

	ASSERT ( get_screen_locked ( active_screen ) );

	convert_float_to_int ( line->i, &x1 );

	convert_float_to_int ( line->j, &y1 );

	convert_float_to_int ( line->next_vertex->i, &x2 );

	convert_float_to_int ( line->next_vertex->j, &y2 );

	intensity = line->intensity;

	intensity2 = line->next_vertex->intensity;

	dintensity = intensity2 - intensity;

	dx = x2 - x1;

	colour_table = application_shading_table[colour];

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

				dintensity /= dx;

				for ( ; x1 >= x2; x1-- )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1--;
					}

					intensity += dintensity;
				}
			}
			else
			{

				error = ( (  dy + 1 ) >> 1 );

				dintensity /= dy;

				for ( ; y1>=y2; y1-- )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
					{

						error += dy;

						x1--;
					}

					intensity += dintensity;
				}
			}
		}
		else
		{

			if ( dx > dy )
			{

				error = ( ( dx + 1 ) >> 1 );

				dintensity /= dx;

				for ( ; x1 >= x2; x1-- )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1++;
					}

					intensity += dintensity;
				}
			}
			else
			{

				error = ( ( dy + 1 ) >> 1 );

				dintensity /= dy;

				for ( ; y1 <= y2; y1++ )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
					{

						error += dy;

						x1--;
					}

					intensity += dintensity;
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

				dintensity /= dx;

				for ( ; x1 <= x2; x1++ )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1--;
					}

					intensity += dintensity;
				}
			}
			else
			{

				error = ( ( dy + 1 ) >> 1 );

				dintensity /= dy;

				for ( ; y1 >= y2; y1 -- )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
					{

						error += dy;

						x1++;
					}

					intensity += dintensity;
				}
			}
		}
		else
		{

			if ( dx > dy )
			{

				error = ( ( dx + 1 ) >> 1 );

				dintensity /= dx;

				for ( ; x1 <= x2; x1 ++ )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y1 ++;
					}

					intensity += dintensity;
				}
			}
			else
			{

				error = ( ( dy + 1 ) >> 1 );

				dintensity /= dy;

				for ( ; y1 <= y2; y1++ )
				{

					convert_float_to_int ( ( intensity * 31 ), &int_intensity );

					int_intensity = bound ( int_intensity, 0, 31 );

					set_software_pixel ( x1, y1, colour_table[int_intensity] );

//					set_software_pixel ( x1, y1, colour );

					if ( ( error -= dx ) < 0 )
					{

						error += dy;

						x1 ++;
					}

					intensity += dintensity;
				}
			}
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
