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
#include "3d/3dfunc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REPORT_VIEWPORTS 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

viewport
	active_viewport;

int_viewport
	active_int_viewport;

int
	left_clip_bit_array[] = { CLIP_LEFT, 0 },
	right_clip_bit_array[] = { CLIP_RIGHT, 0 },
	top_clip_bit_array[] = { CLIP_TOP, 0 },
	bottom_clip_bit_array[] = { CLIP_BOTTOM, 0 };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// IMPORTANT!
//
// To ensure clipping works as expected use '0.000' on min values
// and '0.999' on max values, as shown in the following example:-
//
// set_viewport (0.000, 0.000, 639.999, 479.999);	// 640 * 480 screen
//
////////////////////////////////////////

void set_viewport ( float x_min, float y_min, float x_max, float y_max )
{

	ASSERT ( x_min <= x_max );
	ASSERT ( y_min <= y_max );

	active_viewport.x_min = x_min;
	active_viewport.x_max = x_max;
	active_viewport.y_min = y_min;
	active_viewport.y_max = y_max;

	convert_float_to_int (x_min, &active_int_viewport.x_min);
	convert_float_to_int (x_max, &active_int_viewport.x_max);
	convert_float_to_int (y_min, &active_int_viewport.y_min);
	convert_float_to_int (y_max, &active_int_viewport.y_max);

	if ( ( d3d_initialised ) && ( d3d_valid ) )
	{

		D3DVIEWPORT7
			viewdata;
	
		float
			fwidth,
			fheight;

		int
			iwidth,
			iheight;

		//
		// Flush graphics, or else we get any queued polys clipped wrongly!
		//

		flush_triangle_primitives ();

		flush_line_primitives ();

		viewdata.dwX = x_min;
		viewdata.dwY = y_min;

		fwidth = x_max - x_min;
		fheight = y_max - y_min;

		iwidth = ( int ) fwidth;
		iheight = ( int ) fheight;

		if ( ( fwidth - ( float ) iwidth ) != 0.0 )
		{

			iwidth++;
		}

		if ( ( fheight - ( float ) iheight ) != 0.0 )
		{

			iheight++;
		}

		viewdata.dwWidth = iwidth;
		viewdata.dwHeight = iheight;
		
		viewdata.dvMinZ = 0.0;
		viewdata.dvMaxZ = 1.0;

		f3d_set_viewport ( &viewdata );

#if REPORT_VIEWPORTS
		{

			debug_log ( "Set viewport: %d, %d ( %d, %d ) [ %f %f ]", viewdata.dwX, viewdata.dwY, viewdata.dwWidth, viewdata.dwHeight, viewdata.dvMinZ, viewdata.dvMaxZ );
		}
#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_basic_viewport ( float x_min, float y_min, float x_max, float y_max )
{

	ASSERT ( x_min <= x_max );
	ASSERT ( y_min <= y_max );

	active_viewport.x_min = x_min;
	active_viewport.x_max = x_max;
	active_viewport.y_min = y_min;
	active_viewport.y_max = y_max;

	convert_float_to_int (x_min, &active_int_viewport.x_min);
	convert_float_to_int (x_max, &active_int_viewport.x_max);
	convert_float_to_int (y_min, &active_int_viewport.y_min);
	convert_float_to_int (y_max, &active_int_viewport.y_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_full_viewport ( float x_min, float y_min, float x_max, float y_max, float z_min, float z_max )
{

	ASSERT ( x_min <= x_max );
	ASSERT ( y_min <= y_max );

	active_viewport.x_min = x_min;
	active_viewport.x_max = x_max;
	active_viewport.y_min = y_min;
	active_viewport.y_max = y_max;

	convert_float_to_int (x_min, &active_int_viewport.x_min);
	convert_float_to_int (x_max, &active_int_viewport.x_max);
	convert_float_to_int (y_min, &active_int_viewport.y_min);
	convert_float_to_int (y_max, &active_int_viewport.y_max);

	if ( ( d3d_initialised ) && ( d3d_valid ) )
	{


		D3DVIEWPORT7
			viewdata;
	
		float
			fwidth,
			fheight;

		int
			iwidth,
			iheight;

		viewdata.dwX = x_min;
		viewdata.dwY = y_min;

		fwidth = x_max - x_min;
		fheight = y_max - y_min;

		iwidth = ( int ) fwidth;
		iheight = ( int ) fheight;

		if ( ( fwidth - ( float ) iwidth ) != 0.0 )
		{

			iwidth++;
		}

		if ( ( fheight - ( float ) iheight ) != 0.0 )
		{

			iheight++;
		}

		viewdata.dwWidth = iwidth;
		viewdata.dwHeight = iheight;
		
		viewdata.dvMinZ = z_max;
		viewdata.dvMaxZ = z_min;

		f3d_set_viewport ( &viewdata );

#if REPORT_VIEWPORTS
		{

			debug_log ( "Set viewport: %d, %d ( %d, %d ) [ %f %f ]", viewdata.dwX, viewdata.dwY, viewdata.dwWidth, viewdata.dwHeight, viewdata.dvMinZ, viewdata.dvMaxZ );
		}
#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_viewport ( const rgb_colour colour )
{

	set_block ( active_int_viewport.x_min,
					active_int_viewport.y_min,
					active_int_viewport.x_max,
					active_int_viewport.y_max,
					colour );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
