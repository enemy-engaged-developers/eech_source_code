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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rgb_colour
	hud_colour_table[NUM_HUD_COLOURS];

rgb_colour
	hud_colour;

int
	display_hud_layout_grid,
	hud_bob_up_overlay;

float
	hud_bob_up_heading;

vec3d
	hud_bob_up_position;

hud_modes
	hud_mode, previous_hud_mode;

//VJ 050126 hud mod
hud_screen_data
	hsd;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_hud (void)
{
	//VJ 060212 save hud info mod ==>
	int gt=get_global_gunship_type();
	// happens at initialisation pahse, gunship not known yet
	if (gt >= NUM_GUNSHIP_TYPES)
		gt = 0;

	debug_log("hud colour %d %d",gt,hud_code[gt][HUD_CODES_COLOUR]);
	set_global_hud_colour((hud_colours) hud_code[gt][HUD_CODES_COLOUR]);
	global_hud_alpha = hud_code[gt][HUD_CODES_ALPHA];
	global_hud_size2 = 0.1* (float) hud_code[gt][HUD_CODES_SIZE];
	if (global_hud_size2 <= 1.0)
	{
		set_global_unscaled_displays (TRUE);
	}
	else
	{
		set_global_unscaled_displays (FALSE);
	}
	//<=== VJ 060212 save hud info mod
	global_mfd_size = hud_code[gt][HUD_CODES_MFD] / 20.0;

	display_hud_layout_grid = FALSE;

	hud_bob_up_overlay = FALSE;

	hud_bob_up_heading = 0.0;

	hud_bob_up_position.x = 0.0;
	hud_bob_up_position.y = 0.0;
	hud_bob_up_position.z = 0.0;

	// arneh, june 2006 - transtion mode hud fix
	hud_mode = HUD_MODE_TRANSITION;
	previous_hud_mode = HUD_MODE_TRANSITION;

	set_rgb_colour (hud_colour_table[HUD_COL_WHITE],   255, 255, 240, 255);
	set_rgb_colour (hud_colour_table[HUD_COL_RED],     255,  20,   0, 255);
	set_rgb_colour (hud_colour_table[HUD_COL_AMBER],   255, 153,  18, 255);
	set_rgb_colour (hud_colour_table[HUD_COL_GOLD],    255, 215,   0, 255);
	set_rgb_colour (hud_colour_table[HUD_COL_GREEN],     0, 255, 127, 255);
	set_rgb_colour (hud_colour_table[HUD_COL_CYAN],      0, 255, 255, 255);
	set_rgb_colour (hud_colour_table[HUD_COL_BLUE],     30, 144, 255, 255);
	set_rgb_colour (hud_colour_table[HUD_COL_BLACK],     0,   0,   0, 255);

   //060207 Mavericks hud colours mod.   "_L_=LIGHT", "_N_=NEON", "_D_=DARK"
   set_rgb_colour (hud_colour_table[HUD_COL_ORANGE],     255,   128,    0, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_D_ORANGE],   255,    68,    0, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_L_YELLO],    248,   255,  120, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_D_YELLO],    255,   191,    0, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_N1_GREEN],     34,  255,    0, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_D2_GREEN],   170,   255,    0, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_N3_GREEN],   190,   255,   60, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_LAVENDER1],    195,   0,  114, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_LAVENDER2],   114,    0,  195, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_D_LAVENDER],  61,     0,  105, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_D_BROWN],    125,    17,    0, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_PINK],       255,     0,  149, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_BLUE1],       68,   109,  140, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_BLUE2],       15,    26,   72, 255);
   set_rgb_colour (hud_colour_table[HUD_COL_BLUE3],       49,    66,  109, 255);

	if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
		hud_colour = get_hind_hud_colour();
	else
		hud_colour = hud_colour_table[get_global_hud_colour ()];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_hud (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_hud (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_next_hud_colour (void)
{
	if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
		hud_colour = get_next_hind_hud_colour();
	else
	{
		hud_colours
			col;

		col = get_global_hud_colour ();
		col = (hud_colours) ((int) col + 1);
		col = (col <= NUM_HUD_COLOURS - 1) ? col : (hud_colours) 0;

		set_global_hud_colour (col);
		hud_colour = hud_colour_table[col];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_prev_hud_colour (void)
{
	if (get_global_gunship_type() == GUNSHIP_TYPE_HIND)
		hud_colour = get_prev_hind_hud_colour();
	else
	{
		hud_colours
			col;

		col = get_global_hud_colour ();
		col = (hud_colours) ((int) col - 1);
		col = (col >= 0) ? col : (hud_colours) (NUM_HUD_COLOURS - 1);

		set_global_hud_colour (col);
		hud_colour = hud_colour_table[col];
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_hud_bob_up_overlay (void)
{
	hud_bob_up_overlay = TRUE;

	hud_bob_up_heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &hud_bob_up_position);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void switch_hud_mode(void)
{
	if (hud_mode == HUD_MODE_WEAPON)
		return;

	if (hud_mode == HUD_MODE_TRANSITION)
		hud_mode = HUD_MODE_NAVIGATION;
	else
		hud_mode = HUD_MODE_TRANSITION;

	previous_hud_mode = hud_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_hud_bob_up_overlay (void)
{
	hud_bob_up_overlay = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_hud_on_external_view (void)
{
	if (get_gunship_entity ())
	{
		switch (get_global_gunship_type ())
		{
			////////////////////////////////////////
			// JB 030313 Fly any aircraft
//			default:
			case GUNSHIP_TYPE_APACHE:
			////////////////////////////////////////
			{
				draw_apache_hud ();

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_HAVOC:
			////////////////////////////////////////
			{
				draw_external_havoc_hud ();

				draw_havoc_hms ();

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_COMANCHE:
			////////////////////////////////////////
			{

				draw_comanche_hud ();

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_HOKUM:
			////////////////////////////////////////
			{
				draw_external_hokum_hud ();

				draw_hokum_hms ();

				break;
			}
			////Moje 030518 Start
			case GUNSHIP_TYPE_BLACKHAWK:
			////////////////////////////////////////
			{
				draw_blackhawk_hud ();

				break;
			}
			////Moje 030518 End
			////Moje 030612 start
			////////////////////////////////////////
			case GUNSHIP_TYPE_HIND:
			////////////////////////////////////////
			{
				draw_external_hind_hud ();

				draw_hind_hms ();

				break;
			}
			////Moje 030612 end
			////Moje 030816 Start
			case GUNSHIP_TYPE_AH64A:
			////////////////////////////////////////
			{
				draw_ah64a_hud ();
				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_KA50:
			////////////////////////////////////////
			{
				draw_external_ka50_hud ();
				draw_ka50_hms ();
				break;
			}
			////Moje 030816 end
			////////////////////////////////////////
			case GUNSHIP_TYPE_VIPER:
			////////////////////////////////////////
			{
				draw_viper_hud ();

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_KIOWA:
			////////////////////////////////////////
			{

				draw_kiowa_hud ();

				break;
			}

			////////////////////////////////////////
			// GCsDriver  08-12-2007
			default:
			////////////////////////////////////////
			{
				draw_default_hud ();

				break;
			}

		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050126 hud mod background colour
void draw_hud_background (hud_screen_data *hd, int alpha )
{
#ifndef OGRE_EE
	vertex
		quad[4];

	real_colour
		clear_hud_colour,
		colour,
		specular;

	set_active_screen (hd->hud_texture_screen);

	if (lock_screen (hd->hud_texture_screen))
	{
		set_rgb_colour (clear_hud_colour, 255,255,255,255);

		set_block (hd->hud_viewport_x_min, hd->hud_viewport_y_min, hd->hud_viewport_x_max - 1, hd->hud_viewport_y_max - 1, clear_hud_colour);

		unlock_screen (hd->hud_texture_screen);
	}

	set_active_screen (video_screen);

	////////////////////////////////////////
	//
	// render HUD to screen
	//
	////////////////////////////////////////

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

		switch (get_global_gunship_type ())
		{
			case GUNSHIP_TYPE_COMANCHE:
			case GUNSHIP_TYPE_VIPER:
			case GUNSHIP_TYPE_KIOWA:
			{
				set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD));
				break;
			}
			default:
			{
				set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_COMANCHE_MFD2));
				break;
			}
		}

		////////////////////////////////////////
		//

		colour.red	 			= 48;
		colour.green			= 48;
		colour.blue	 			= 16;
		colour.alpha  			= min(alpha, global_hud_alpha);

		specular.red 			= 0;
		specular.green	 		= 0;
		specular.blue 			= 0;
		specular.alpha	  		= 255;

		quad[0].i 				= hd->hud_screen_x_min;
		quad[0].j  				= hd->hud_screen_y_min;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= 0.0;
		quad[0].v				= 0.0;

		quad[1].i  				= hd->hud_screen_x_max;
		quad[1].j  				= hd->hud_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 1.0;
		quad[1].v  				= 0.0;

		quad[2].i				= hd->hud_screen_x_max;
		quad[2].j  				= hd->hud_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 1.0;
		quad[2].v  				= 1.0;

		quad[3].i  				= hd->hud_screen_x_min;
		quad[3].j  				= hd->hud_screen_y_max;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
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
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
