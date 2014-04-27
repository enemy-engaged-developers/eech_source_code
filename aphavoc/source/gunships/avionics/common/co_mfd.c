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

#include "project.h"

#define CLICK_TOLERANCE  0.025

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	display_mfd_layout_grid;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*mfd_mode_names[NUM_MFD_MODES] =
	{
		"MFD_MODE_OFF",
		"MFD_MODE_DAMAGED",
		"MFD_MODE_GROUND_RADAR",
		"MFD_MODE_AIR_RADAR",
		"MFD_MODE_FLIR",
		"MFD_MODE_DTV",
		"MFD_MODE_DVO",
		"MFD_MODE_LLLTV",
		"MFD_MODE_TSD",
		"MFD_MODE_ASE",
		"MFD_MODE_WEAPON",
		"MFD_MODE_SYSTEM",
		"MFD_MODE_ENGINE",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

screen
	*large_eo_3d_texture_screen,
	*small_eo_3d_texture_screen;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	pointer_position_x = 1.0,
	pointer_position_y = -1.0;

extern float
	clicked_position_x = 0.0,
	clicked_position_y = 0.0;	
	
static int
	left_button_held = FALSE,
	right_button_held = FALSE;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_mfd_mouse_buttons(void)
{
	left_button_held = right_button_held = FALSE;	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_mfd (void)
{
	display_mfd_layout_grid = FALSE;
	reset_mfd_mouse_buttons();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_mfd (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_mfd_3d_textures (void)
{
	if (d3d_can_render_to_texture)
	{
		large_eo_3d_texture_screen = create_user_3dvisual_texture_screen (256, 256, TEXTURE_TYPE_SCREEN);
		small_eo_3d_texture_screen = create_user_3dvisual_texture_screen (128, 128, TEXTURE_TYPE_SCREEN);
	}
	else
	{
		large_eo_3d_texture_screen = NULL;
		small_eo_3d_texture_screen = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_mfd_3d_textures (void)
{
	if (d3d_can_render_to_texture)
	{
		destroy_screen (large_eo_3d_texture_screen);
		destroy_screen (small_eo_3d_texture_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void store_point(int button_down, int left_button)
{
	if (button_down)
	{
		clicked_position_x = pointer_position_x;
		clicked_position_y = pointer_position_y;
		
		if (left_button)
		{
			left_button_held = TRUE;
			right_button_held = FALSE;
		}
		else
		{
			right_button_held = TRUE;
			left_button_held = FALSE;
		}
	}
	else
	{
		if (get_global_gunship_type () == GUNSHIP_TYPE_APACHE)
		{
			if (left_button_held && left_button
				&& fabs(clicked_position_x - pointer_position_x) < CLICK_TOLERANCE
				&& fabs(clicked_position_y - pointer_position_y) < CLICK_TOLERANCE)
			{
				apache_select_clicked_target();
			}
			else if ((left_button_held && left_button)
					 || (right_button_held && !left_button))
			{
				create_apache_pfz(!left_button);
			}
		}

		left_button_held = right_button_held = FALSE;
	}
}

void store_point_left_event (event* ev)
{
	store_point(ev->state == BUTTON_STATE_DOWN, TRUE);
}

void store_point_right_event (event* ev)
{
	store_point(ev->state == BUTTON_STATE_DOWN, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_holding_left_button (void)
{
	return left_button_held;
}

int is_holding_right_button (void)
{
	return right_button_held;
}

void update_pointer_position (void)
{
	static int previous_mouse_update_flag = 1;

	
	// don't move pointer when ah64d's EO is active thealx 130215

	if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE && command_line_mouse_look  != MOUSELOOK_ON)
	{

	}
	else if (previous_mouse_update_flag != get_mouse_update_flag())
	{
		float dx, dy;

		dx = get_mouse_move_delta_x() * 0.001;
		dy = -get_mouse_move_delta_y() * 0.001;

		previous_mouse_update_flag = get_mouse_update_flag();

		pointer_position_x += dx;
		pointer_position_y += dy;

		pointer_position_x = bound(pointer_position_x, -1.1, 1.1);
		pointer_position_y = bound(pointer_position_y, -1.1, 1.1);		
	}
}

void move_targeting_gates(float *x, float *y)
{
	*x = (0.2 * frand1() + 0.8) * bound(50 * current_flight_dynamics->heading.delta, - 0.1, 0.1);
	*y = - (0.2 * frand1() + 0.8) * bound(50 * current_flight_dynamics->pitch.delta, - 0.1, 0.1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_symbology_to_texture(
	screen* texture_screen,
	texture_index_numbers texture_index,
	int texture_width,
	int texture_height,
	int x_min,
	int y_min,
	int x_max,
	int y_max,
	rgb_colour colour,
	rgb_colour background_colour,
	void (*draw_2d_symbols_function)(int))
{
	vertex
		quad[4];

	real_colour
		specular;

	//
	// draw MFD on texture
	//

	set_active_screen (texture_screen);

	if (lock_screen (texture_screen))
	{
//		set_block (x_min, y_min, x_max, y_max, clear_colour);
		set_block (0, 0, texture_width-1, texture_height-1, background_colour);

//		draw_layout_grid ();

		draw_2d_symbols_function(TRUE);

		flush_screen_texture_graphics (texture_screen);
		unlock_screen (texture_screen);
	}

	set_active_screen (video_screen);

	//
	// render MFD to screen
	//

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		set_d3d_transparency_on ();
		set_d3d_zbuffer_comparison (FALSE);
		set_d3d_culling (FALSE);
		set_d3d_texture_wrapping (0, FALSE);

		if ((application_video_width == 640) || (get_global_unscaled_displays ()))
		{
			set_d3d_texture_mag_filtering (FALSE);
			set_d3d_texture_min_filtering (FALSE);
			set_d3d_texture_mip_filtering (FALSE);
		}
		else
		{
			set_d3d_texture_mag_filtering (TRUE);
			set_d3d_texture_min_filtering (TRUE);
			set_d3d_texture_mip_filtering (FALSE);
		}

//		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_AVCKPT_DISPLAY_ORT));
		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (texture_index));

      ////////////////////////////////////////
      //

/*		colour.red				= hud_colour_table[get_global_hud_colour ()].r;
		colour.green			= hud_colour_table[get_global_hud_colour ()].g;
		colour.blue				= hud_colour_table[get_global_hud_colour ()].b;
		colour.alpha			= 255;
*/
		specular.red			= 0;
		specular.green			= 0;
		specular.blue			= 0;
		specular.alpha			= 255;

		quad[0].i				= x_min;
		quad[0].j	  			= y_min;
		quad[0].z	  			= 0.5;
		quad[0].q	  			= 0.5;
		quad[0].u	  			= 0.0;
		quad[0].v	  			= 0.0;

		quad[1].i				= x_max;
		quad[1].j  				= y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 1.0;
		quad[1].v  				= 0.0;

		quad[2].i				= x_max;
		quad[2].j 				= y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 1.0;
		quad[2].v  				= 1.0;

		quad[3].i				= x_min;
		quad[3].j				= y_max;
		quad[3].z				= 0.5;
		quad[3].q				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 1.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

      //
      ////////////////////////////////////////

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		set_d3d_transparency_off ();
		set_d3d_zbuffer_comparison (TRUE);
		set_d3d_culling (TRUE);
		end_3d_scene ();
	}
}
