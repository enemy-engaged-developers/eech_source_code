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

#include "userint.h"

#include "graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour
	ui_button_up_background = {33, 49, 115, 0},
	ui_button_up_light_edge = {115, 148, 222, 0},
	ui_button_up_dark_edge = {16, 24, 66, 0},
	ui_button_down_background = {148, 57, 0, 0},
	ui_button_down_dark_edge = {82, 33, 0, 0},
	ui_button_down_light_edge = {255, 156, 82, 0};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_draw_button (float x1, float y1, float x2, float y2, int state)
{

	float
		new_x1,
		new_y1,
		new_x2,
		new_y2;

	int
		int_x1,
		int_y1,
		int_x2,
		int_y2;


	rgb_colour
		background_colour,
		top_line_colour,
		bottom_line_colour,
		left_line_colour,
		right_line_colour,
		top_left_pixel_colour,
		bottom_left_pixel_colour,
		top_right_pixel_colour,
		bottom_right_pixel_colour;

	x1 -= ui_x_origin;
	y1 -= ui_y_origin;
	x2 -= ui_x_origin;
	y2 -= ui_y_origin;

	new_x1 = x1;

	new_y1 = y1;

	new_x2 = x2;

	new_y2 = y2;

	// clip button to ui viewport

	ui_clip_area (&new_x1, &new_y1, &new_x2, &new_y2);

	// button coords should be in viewport coords,
	// so add ui_origin to convert into screen coords

	x1 += ui_x_origin;

	y1 += ui_y_origin;

	x2 += ui_x_origin;

	y2 += ui_y_origin;

	new_x1 += ui_x_origin;

	new_y1 += ui_y_origin;

	new_x2 += ui_x_origin;

	new_y2 += ui_y_origin;

	// check if possible to draw

	if ((new_x2 - new_x1 < 2) || (new_y2 - new_y1 <= 2))
	{

		return;
	}

	// convert variabless to ints to save crap conversion

	convert_float_to_int (new_x1, &int_x1);
	convert_float_to_int (new_y1, &int_y1);
	convert_float_to_int (new_x2, &int_x2);
	convert_float_to_int (new_y2, &int_y2);

	// assign correct colours

	if (state)
	{

		background_colour = ui_button_down_background;
		top_line_colour = ui_button_down_dark_edge;
		bottom_line_colour = ui_button_down_light_edge;
		left_line_colour = ui_button_down_dark_edge;
		right_line_colour = ui_button_down_light_edge;
		top_left_pixel_colour = ui_button_down_dark_edge;
		bottom_left_pixel_colour = ui_button_down_light_edge;
		top_right_pixel_colour = ui_button_down_light_edge;
		bottom_right_pixel_colour = ui_button_down_light_edge;
	}
	else
	{

		background_colour = ui_button_up_background;
		top_line_colour = ui_button_up_light_edge;
		bottom_line_colour = ui_button_up_dark_edge;
		left_line_colour = ui_button_up_light_edge;
		right_line_colour = ui_button_up_dark_edge;
		top_left_pixel_colour = ui_button_up_light_edge;
		bottom_left_pixel_colour = ui_button_up_light_edge;
		top_right_pixel_colour = ui_button_up_light_edge;
		bottom_right_pixel_colour = ui_button_up_dark_edge;
	}

	// draw background

	if (x1 != new_x1)
	{

		if (y1 != new_y1)
		{
			
			set_block (int_x1, int_y1, int_x2, int_y2, background_colour);
		}
		else
		{

			set_block (int_x1, int_y1 + 1, int_x2, int_y2, background_colour);
		}
	}
	else if (y1 != new_y1)
	{

		set_block (int_x1 + 1 , int_y1, int_x2, int_y2, background_colour);
	}
	else
	{

		set_block (int_x1 + 1 , int_y1 + 1, int_x2 - 1, int_y2 - 1, background_colour);
	}

	// draw top line

	if (y1 == new_y1)
	{
		
	  	if ((x1 == new_x1) && (x2 == new_x2))
		{
			
			draw_line (new_x1 + 2, new_y1, new_x2 - 2, new_y1, top_line_colour);
		}
	  	else if (x1 == new_x1)
		{
			
			draw_line (new_x1 + 2, new_y1, new_x2, new_y1, top_line_colour);
		}
	  	else if (x2 == new_x2)
		{
			
			draw_line (new_x1, new_y1, new_x2 - 2, new_y1, top_line_colour);
		}
	  	else
		{
			
			draw_line (new_x1, new_y1, new_x2, new_y1, top_line_colour);
		}
	}

	// draw botton line

	if (y2 == new_y2)
	{

	  	if ((x1 == new_x1) && (x2 == new_x2))
		{
			
			draw_line (new_x1 + 2, new_y2, new_x2 - 2, new_y2, bottom_line_colour);
		}
	  	else if (x1 == new_x1)
		{

			draw_line (new_x1 + 2, new_y2, new_x2, new_y2, bottom_line_colour);
		}
	  	else if (x2 == new_x2)
		{
			
			draw_line (new_x1, new_y2, new_x2 - 2, new_y2, bottom_line_colour);
		}
	  	else
		{
			
			draw_line (new_x1, new_y2, new_x2, new_y2, bottom_line_colour);
		}
	}

	// draw left side

	if (x1 == new_x1)
	{
		
	  	if ((y1 == new_y1) && (y2 == new_y2))
		{
			
			draw_line (new_x1, new_y1 + 2, new_x1, new_y2 - 2, left_line_colour);
		}
	  	else if (y1 == new_y1)
		{

			draw_line (new_x1, new_y1 + 2, new_x1, new_y2, left_line_colour);
		}
	  	else if (y2 == new_y2)
		{
			
			draw_line (new_x1, new_y1, new_x1, new_y2 - 2, left_line_colour);
		}
	  	else
		{
			
			draw_line (new_x1, new_y1, new_x1, new_y2, left_line_colour);
		}
	}

	// draw right side

	if (x2 == new_x2)
	{

	  	if ((y1 == new_y1) && (y2 == new_y2))
		{
			
			draw_line (new_x2, new_y1 + 2, new_x2, new_y2 - 2, right_line_colour);
		}
	  	else if (y1 == new_y1)
		{

			draw_line (new_x2, new_y1 + 2, new_x2, new_y2, right_line_colour);
		}
	  	else if (y2 == new_y2)
		{
			
			draw_line (new_x2, new_y1, new_x2, new_y2 - 2, right_line_colour);
		}
	  	else
		{
			
			draw_line (new_x2, new_y1, new_x2, new_y2, right_line_colour);
		}
	}

	// draw odd pixels in corners

	if (x1 == new_x1)
	{

		// top left
		if (y1 == new_y1)
		{
			
			set_pixel (int_x1 + 1, int_y1 + 1, top_left_pixel_colour);
		}

		// bottom left
		if (y2 == new_y2)
		{

			set_pixel (int_x1 + 1, int_y2 - 1, bottom_left_pixel_colour);
		}
	}

	if (x2 == new_x2)
	{

		// top right
		if (y1 == new_y1)
		{
			
			set_pixel (int_x2 - 1, int_y1 + 1, top_right_pixel_colour);
		}

		// bottom right
		if (y2 == new_y2)
		{

			set_pixel (int_x2 - 1, int_y2 - 1, bottom_right_pixel_colour);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
