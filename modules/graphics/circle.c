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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define fast_set_pixel(X,Y,COL) (*((USHORT *) (screen_data + (Y) * screen_pitch) + (X)) = (COL))
#define fast_set_32bit_pixel(X,Y,COL) (*((ULONG *) (screen_data + (Y) * screen_pitch) + (X)) = (COL))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define fast_set_clipped_pixel(X,Y,COL)	\
{														\
	int												\
		x,												\
		y;												\
														\
	x = (X);											\
	y = (Y);											\
														\
	if													\
	(													\
		(x >= active_int_viewport.x_min) &&	\
		(y >= active_int_viewport.y_min) &&	\
		(x <= active_int_viewport.x_max) &&	\
		(y <= active_int_viewport.y_max)		\
	)													\
	{													\
		fast_set_pixel (x, y, (COL));  		\
	}													\
}

#define fast_set_32bit_clipped_pixel(X,Y,COL)	\
{														\
	int												\
		x,												\
		y;												\
														\
	x = (X);											\
	y = (Y);											\
														\
	if													\
	(													\
		(x >= active_int_viewport.x_min) &&	\
		(y >= active_int_viewport.y_min) &&	\
		(x <= active_int_viewport.x_max) &&	\
		(y <= active_int_viewport.y_max)		\
	)													\
	{													\
		fast_set_32bit_pixel (x, y, (COL));  		\
	}													\
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_circle (const float x, const float y, const float r, const rgb_colour colour)
{
   int
		x_centre,
		y_centre,
		radius,
		x_min,
		y_min,
		x_max,
		y_max,
		screen_pitch,
      x_offset,
      y_offset,
      decision;

	unsigned char
		*screen_data;

	ASSERT (active_screen);
	ASSERT (get_screen_locked (active_screen));

	if ( get_screen_pixel_width ( active_screen ) == 2 )
	{
	
		USHORT
			col;
	
		convert_float_to_int (x, &x_centre);
		convert_float_to_int (y, &y_centre);
		convert_float_to_int (r, &radius);
	
		//
		// trivially reject
		//
	
		if ((x_min = x_centre - radius) > active_int_viewport.x_max) return;
		if ((y_min = y_centre - radius) > active_int_viewport.y_max) return;
		if ((x_max = x_centre + radius) < active_int_viewport.x_min) return;
		if ((y_max = y_centre + radius) < active_int_viewport.y_min) return;
	
		//
		// get screen values
		//
	
		col = get_rgb_packed_value (colour);
	
		screen_data = get_screen_data (active_screen);
	
		screen_pitch = get_screen_pitch (active_screen);
	
		//
		// draw circle
		//
	
		x_offset = 0;
	
		y_offset = radius;
	
		decision = 3 - (radius << 1);
	
		if
		(
			(x_min >= active_int_viewport.x_min) &&
			(y_min >= active_int_viewport.y_min) &&
			(x_max <= active_int_viewport.x_max) &&
			(y_max <= active_int_viewport.y_max)
		)
		{
			//
			// draw unclipped circle
			//
	
			while (x_offset <= y_offset)
			{
				fast_set_pixel (x_centre + x_offset, y_centre + y_offset, col);
				fast_set_pixel (x_centre + x_offset, y_centre - y_offset, col);
				fast_set_pixel (x_centre - x_offset, y_centre + y_offset, col);
				fast_set_pixel (x_centre - x_offset, y_centre - y_offset, col);
				fast_set_pixel (x_centre + y_offset, y_centre + x_offset, col);
				fast_set_pixel (x_centre + y_offset, y_centre - x_offset, col);
				fast_set_pixel (x_centre - y_offset, y_centre + x_offset, col);
				fast_set_pixel (x_centre - y_offset, y_centre - x_offset, col);
	
				if (decision < 0)
				{
					decision += (x_offset << 2) + 6;
				}
				else
				{
					decision += ((x_offset - y_offset) << 2) + 10;
	
					y_offset--;
				}
	
				x_offset++;
			}
		}
		else
		{
			//
			// draw clipped circle
			//
	
			while (x_offset <= y_offset)
			{
				fast_set_clipped_pixel (x_centre + x_offset, y_centre + y_offset, col);
				fast_set_clipped_pixel (x_centre + x_offset, y_centre - y_offset, col);
				fast_set_clipped_pixel (x_centre - x_offset, y_centre + y_offset, col);
				fast_set_clipped_pixel (x_centre - x_offset, y_centre - y_offset, col);
				fast_set_clipped_pixel (x_centre + y_offset, y_centre + x_offset, col);
				fast_set_clipped_pixel (x_centre + y_offset, y_centre - x_offset, col);
				fast_set_clipped_pixel (x_centre - y_offset, y_centre + x_offset, col);
				fast_set_clipped_pixel (x_centre - y_offset, y_centre - x_offset, col);
	
				if (decision < 0)
				{
					decision += (x_offset << 2) + 6;
				}
				else
				{
					decision += ((x_offset - y_offset) << 2) + 10;
	
					y_offset--;
				}
	
				x_offset++;
			}
		}
	}
	else
	{
	
		ULONG
			col;
	
		convert_float_to_int (x, &x_centre);
		convert_float_to_int (y, &y_centre);
		convert_float_to_int (r, &radius);
	
		//
		// trivially reject
		//
	
		if ((x_min = x_centre - radius) > active_int_viewport.x_max) return;
		if ((y_min = y_centre - radius) > active_int_viewport.y_max) return;
		if ((x_max = x_centre + radius) < active_int_viewport.x_min) return;
		if ((y_max = y_centre + radius) < active_int_viewport.y_min) return;
	
		//
		// get screen values
		//
	
		col = get_rgb_packed_value (colour);
	
		screen_data = get_screen_data (active_screen);
		screen_pitch = get_screen_pitch (active_screen);
	
		//
		// draw circle
		//
	
		x_offset = 0;
	
		y_offset = radius;
	
		decision = 3 - (radius << 1);
	
		if
		(
			(x_min >= active_int_viewport.x_min) &&
			(y_min >= active_int_viewport.y_min) &&
			(x_max <= active_int_viewport.x_max) &&
			(y_max <= active_int_viewport.y_max)
		)
		{
			//
			// draw unclipped circle
			//
	
			while (x_offset <= y_offset)
			{
				fast_set_32bit_pixel (x_centre + x_offset, y_centre + y_offset, col);
				fast_set_32bit_pixel (x_centre + x_offset, y_centre - y_offset, col);
				fast_set_32bit_pixel (x_centre - x_offset, y_centre + y_offset, col);
				fast_set_32bit_pixel (x_centre - x_offset, y_centre - y_offset, col);
				fast_set_32bit_pixel (x_centre + y_offset, y_centre + x_offset, col);
				fast_set_32bit_pixel (x_centre + y_offset, y_centre - x_offset, col);
				fast_set_32bit_pixel (x_centre - y_offset, y_centre + x_offset, col);
				fast_set_32bit_pixel (x_centre - y_offset, y_centre - x_offset, col);
	
				if (decision < 0)
				{
					decision += (x_offset << 2) + 6;
				}
				else
				{
					decision += ((x_offset - y_offset) << 2) + 10;
	
					y_offset--;
				}
	
				x_offset++;
			}
		}
		else
		{
			//
			// draw clipped circle
			//
	
			while (x_offset <= y_offset)
			{
				fast_set_32bit_clipped_pixel (x_centre + x_offset, y_centre + y_offset, col);
				fast_set_32bit_clipped_pixel (x_centre + x_offset, y_centre - y_offset, col);
				fast_set_32bit_clipped_pixel (x_centre - x_offset, y_centre + y_offset, col);
				fast_set_32bit_clipped_pixel (x_centre - x_offset, y_centre - y_offset, col);
				fast_set_32bit_clipped_pixel (x_centre + y_offset, y_centre + x_offset, col);
				fast_set_32bit_clipped_pixel (x_centre + y_offset, y_centre - x_offset, col);
				fast_set_32bit_clipped_pixel (x_centre - y_offset, y_centre + x_offset, col);
				fast_set_32bit_clipped_pixel (x_centre - y_offset, y_centre - x_offset, col);
	
				if (decision < 0)
				{
					decision += (x_offset << 2) + 6;
				}
				else
				{
					decision += ((x_offset - y_offset) << 2) + 10;
	
					y_offset--;
				}
	
				x_offset++;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hatched_filled_circle ( const float x, const float y, const float r, const rgb_colour colour )
{
	
	int
		x_centre,
		y_centre,
		radius,
		x_min,
		y_min,
		x_max,
		y_max,
		screen_pitch,
		x_offset,
		y_offset,
		decision;
	
	unsigned char
		*screen_data;
	
	ASSERT ( active_screen );
	ASSERT ( get_screen_locked ( active_screen ) );
	
	if ( get_screen_pixel_width ( active_screen ) == 2 )
	{
	
		USHORT
			col;
		
		convert_float_to_int ( x, &x_centre );
		convert_float_to_int ( y, &y_centre );
		convert_float_to_int ( r, &radius );
		
		//
		// trivially reject
		//
		
		if ( ( x_min = x_centre - radius ) > active_int_viewport.x_max ) return;
		if ( ( y_min = y_centre - radius ) > active_int_viewport.y_max ) return;
		if ( ( x_max = x_centre + radius ) < active_int_viewport.x_min ) return;
		if ( ( y_max = y_centre + radius ) < active_int_viewport.y_min ) return;
		
		//
		// get screen values
		//
		
		col = get_rgb_packed_value ( colour );
		
		screen_data = get_screen_data ( active_screen );
		screen_pitch = get_screen_pitch ( active_screen );
		
		//
		// draw circle
		//
		
		x_offset = 0;
		
		y_offset = radius;
		
		decision = 3 - (radius << 1);
		
		if (	( x_min >= active_int_viewport.x_min ) && ( x_max <= active_int_viewport.x_max ) &&
				( y_min >= active_int_viewport.y_min ) && ( y_max <= active_int_viewport.y_max ) )
		{
			
			//
			// draw unclipped circle
			//
			
			while ( x_offset <= y_offset )
			{
	
				int
					x,
					xmin,
					xmax,
					y;
	
				unsigned short int
					*line_ptr;
				
				xmin = x_centre - x_offset;
				
				xmax = x_centre + x_offset;
	
				y = y_centre + y_offset;
	
				{
	
					line_ptr = ( unsigned short int * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
				
				y = y_centre - y_offset;
	
				{
	
					line_ptr = ( unsigned short int * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
	
				xmin = x_centre - y_offset;
				
				xmax = x_centre + y_offset;
	
				y = y_centre + x_offset;
				
				{
	
					line_ptr = ( unsigned short int * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
	
				y = y_centre - x_offset;
	
				{
	
					line_ptr = ( unsigned short int * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
				
				if ( decision < 0 )
				{
	
					decision += ( x_offset << 2 ) + 6;
				}
				else
				{
	
					decision += ( ( x_offset - y_offset ) << 2 ) + 10;
					
					y_offset--;
				}
				
				x_offset++;
			}
		}
		else
		{
			//
			// draw clipped circle
			//
			
			while ( x_offset <= y_offset )
			{
				
				int
					x,
					xmin,
					xmax,
					y;
	
				USHORT
					*line_ptr;
				
				xmin = x_centre - x_offset;
				
				xmax = x_centre + x_offset;
	
				if ( !( ( xmax < active_int_viewport.x_min ) || ( xmin > active_int_viewport.x_max ) ) )
				{
		
					xmin = bound ( xmin, active_int_viewport.x_min, active_int_viewport.x_max );
	
					xmax = bound ( xmax, active_int_viewport.x_min, active_int_viewport.x_max );
		
					y = y_centre + y_offset;
		
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( USHORT * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
					
					y = y_centre - y_offset;
		
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( USHORT * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
				}
	
				xmin = x_centre - y_offset;
				
				xmax = x_centre + y_offset;
	
				if ( !( ( xmax < active_int_viewport.x_min ) || ( xmin > active_int_viewport.x_max ) ) )
				{
	
					xmin = bound ( xmin, active_int_viewport.x_min, active_int_viewport.x_max );
	
					xmax = bound ( xmax, active_int_viewport.x_min, active_int_viewport.x_max );
		
					y = y_centre + x_offset;
					
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( USHORT * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
		
					y = y_centre - x_offset;
		
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( USHORT * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
				}
	
				if ( decision < 0 )
				{
	
					decision += ( x_offset << 2 ) + 6;
				}
				else
				{
					
					decision += ( ( x_offset - y_offset ) << 2 ) + 10;
					
					y_offset--;
				}
				
				x_offset++;
			}
		}
	}
	else
	{
	
		ULONG
			col;
		
		convert_float_to_int ( x, &x_centre );
		convert_float_to_int ( y, &y_centre );
		convert_float_to_int ( r, &radius );
		
		//
		// trivially reject
		//
		
		if ( ( x_min = x_centre - radius ) > active_int_viewport.x_max ) return;
		if ( ( y_min = y_centre - radius ) > active_int_viewport.y_max ) return;
		if ( ( x_max = x_centre + radius ) < active_int_viewport.x_min ) return;
		if ( ( y_max = y_centre + radius ) < active_int_viewport.y_min ) return;
		
		//
		// get screen values
		//
		
		col = get_rgb_packed_value ( colour );
		
		screen_data = get_screen_data ( active_screen );
		screen_pitch = get_screen_pitch ( active_screen );
		
		//
		// draw circle
		//
		
		x_offset = 0;
		
		y_offset = radius;
		
		decision = 3 - (radius << 1);
		
		if (	( x_min >= active_int_viewport.x_min ) && ( x_max <= active_int_viewport.x_max ) &&
				( y_min >= active_int_viewport.y_min ) && ( y_max <= active_int_viewport.y_max ) )
		{
			
			//
			// draw unclipped circle
			//
			
			while ( x_offset <= y_offset )
			{
	
				int
					x,
					xmin,
					xmax,
					y;
	
				ULONG
					*line_ptr;
				
				xmin = x_centre - x_offset;
				xmax = x_centre + x_offset;
	
				y = y_centre + y_offset;
	
				{
	
					line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
				
				y = y_centre - y_offset;
	
				{
	
					line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
	
				xmin = x_centre - y_offset;
				
				xmax = x_centre + y_offset;
	
				y = y_centre + x_offset;
				
				{
	
					line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
	
				y = y_centre - x_offset;
	
				{
	
					line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
	
					for ( x = xmin; x <= xmax; x++ )
					{
	
						if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
						{
	
							line_ptr[x] = col;
						}
					}
				}
				
				if ( decision < 0 )
				{
	
					decision += ( x_offset << 2 ) + 6;
				}
				else
				{
	
					decision += ( ( x_offset - y_offset ) << 2 ) + 10;
					
					y_offset--;
				}
				
				x_offset++;
			}
		}
		else
		{
			//
			// draw clipped circle
			//
			
			while ( x_offset <= y_offset )
			{
				
				int
					x,
					xmin,
					xmax,
					y;
	
				ULONG
					*line_ptr;
				
				xmin = x_centre - x_offset;
				xmax = x_centre + x_offset;
	
				if ( !( ( xmax < active_int_viewport.x_min ) || ( xmin > active_int_viewport.x_max ) ) )
				{
		
					xmin = bound ( xmin, active_int_viewport.x_min, active_int_viewport.x_max );
	
					xmax = bound ( xmax, active_int_viewport.x_min, active_int_viewport.x_max );
		
					y = y_centre + y_offset;
		
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
					
					y = y_centre - y_offset;
		
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
				}
	
				xmin = x_centre - y_offset;
				
				xmax = x_centre + y_offset;
	
				if ( !( ( xmax < active_int_viewport.x_min ) || ( xmin > active_int_viewport.x_max ) ) )
				{
	
					xmin = bound ( xmin, active_int_viewport.x_min, active_int_viewport.x_max );
	
					xmax = bound ( xmax, active_int_viewport.x_min, active_int_viewport.x_max );
		
					y = y_centre + x_offset;
					
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
		
					y = y_centre - x_offset;
		
					if ( ( y >= active_int_viewport.y_min ) && ( y <= active_int_viewport.y_max ) )
					{
		
						line_ptr = ( ULONG * ) ( screen_data + ( screen_pitch * y ) );
		
						for ( x = xmin; x <= xmax; x++ )
						{
		
							if ( ( 1 << ( 31 - ( x & 0x1f ) ) ) & graphics_hatch_pattern[ ( y & 0x1f ) ] )
							{
		
								line_ptr[x] = col;
							}
						}
					}
				}
	
				if ( decision < 0 )
				{
	
					decision += ( x_offset << 2 ) + 6;
				}
				else
				{
					
					decision += ( ( x_offset - y_offset ) << 2 ) + 10;
					
					y_offset--;
				}
				
				x_offset++;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_filled_circle ( float x, float y, float radius, int steps, rgb_colour col )
{

	float
		angle_step,
		angle,
		cos_radius,
		sin_radius,
		x1, y1,
		x2, y2;

	vertex
		*poly,
		points[3];

	rgb_colour
		specular;

	ASSERT ( d3d_in_3d_scene );

	angle_step = PI2 / steps;

	//
	// Set alpha-blending
	//

	if ( col.alpha != 255 )
	{

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );
	}
	else
	{

		set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );
	}

	//
	// Turn off texturing
	//

	set_d3d_plain_renderstate ();

	set_d3d_zbuffer_comparison ( FALSE );

	specular.r = 0;
	specular.g = 0;
	specular.b = 0;
	specular.a = 255;

	x2 = x + 0;
	y2 = y + radius;

	for ( angle = angle_step; angle < PI2; angle += angle_step )
	{

		int
			outcode,
			outcode2;

		x1 = x2;
		y1 = y2;

		cos_radius = cos ( angle ) * radius;
		sin_radius = sin ( angle ) * radius;

		x2 = x + sin_radius;
		y2 = y + cos_radius;

		points[0].i = x;
		points[0].j = y;

		points[1].i = x2;
		points[1].j = y2;

		points[2].i = x1;
		points[2].j = y1;

		points[0].q = 0.1;
		points[0].z = 10;
		points[1].q = 0.1;
		points[1].z = 10;
		points[2].q = 0.1;
		points[2].z = 10;

		points[0].next_vertex = &points[1];
		points[1].next_vertex = &points[2];
		points[2].next_vertex = NULL;

		points[0].outcode = generate_outcode ( points[0].i, points[0].j );
		points[1].outcode = generate_outcode ( points[1].i, points[1].j );
		points[2].outcode = generate_outcode ( points[2].i, points[2].j );

		outcode = points[0].outcode;
		outcode2 = points[0].outcode;
		outcode |= points[1].outcode;
		outcode2 &= points[1].outcode;
		outcode |= points[2].outcode;
		outcode2 &= points[2].outcode;

		if ( outcode2 == 0 )
		{

			poly = &points[0];

			if ( outcode )
			{

				clip_3d_coord = 0;

				poly = clip_3d_polygon ( poly, outcode );
			}

			if ( poly )
			{

				draw_wbuffered_plain_polygon ( poly, col, specular );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_outline_circle ( float x, float y, float radius, int steps, rgb_colour col )
{

	float
		angle_step,
		angle,
		cos_radius,
		sin_radius,
		x1, y1,
		x2, y2;

	vertex
		*poly,
		points[2];

	rgb_colour
		specular;

	ASSERT ( d3d_in_3d_scene );

	angle_step = PI2 / steps;

	//
	// Set alpha-blending
	//

	if ( col.alpha != 255 )
	{

		set_d3d_alpha_fog_zbuffer ( TRUE, FALSE, FALSE, FALSE );
	}
	else
	{

		set_d3d_alpha_fog_zbuffer ( FALSE, FALSE, FALSE, FALSE );
	}

	//
	// Turn off texturing
	//

	set_d3d_plain_renderstate ();

	set_d3d_zbuffer_comparison ( FALSE );

	specular.r = 0;
	specular.g = 0;
	specular.b = 0;
	specular.a = 255;

	x2 = x + 0;
	y2 = y + radius;

	for ( angle = angle_step; angle < PI2; angle += angle_step )
	{

		int
			outcode,
			outcode2;

		x1 = x2;
		y1 = y2;

		cos_radius = cos ( angle ) * radius;
		sin_radius = sin ( angle ) * radius;

		x2 = x + sin_radius;
		y2 = y + cos_radius;

		points[0].i = x2;
		points[0].j = y2;

		points[1].i = x1;
		points[1].j = y1;

		points[0].q = 0.1;
		points[0].z = 10;
		points[1].q = 0.1;
		points[1].z = 10;

		points[0].next_vertex = &points[1];
		points[1].next_vertex = NULL;

		points[0].outcode = generate_outcode ( points[0].i, points[0].j );
		points[1].outcode = generate_outcode ( points[1].i, points[1].j );

		outcode = points[0].outcode;
		outcode2 = points[0].outcode;
		outcode |= points[1].outcode;
		outcode2 &= points[1].outcode;

		if ( outcode2 == 0 )
		{

			poly = &points[0];

			if ( outcode )
			{

				clip_3d_coord = 0;

				poly = clip_3d_polygon ( poly, outcode );
			}

			if ( poly )
			{

				LPD3DTLVERTEX
					vertices;

				vertex
					*point1,
					*point2;
	
				vertices = get_d3d_line_vertices_points_address ();
			
				point1 = poly->next_vertex;
				point2 = poly;
			
				vertices[0].sx = point1->i;
				vertices[0].sy = point1->j;
				vertices[0].rhw = 0.1;
				vertices[0].sz = 0.1;
				vertices[0].color = col.colour;
				vertices[0].specular = specular.colour;
			
				vertices[1].sx = point2->i;
				vertices[1].sy = point2->j;
				vertices[1].rhw = 0.1;
				vertices[1].sz = 0.1;
				vertices[1].color = col.colour;
				vertices[1].specular = specular.colour;

				draw_line_primitive ( vertices );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

