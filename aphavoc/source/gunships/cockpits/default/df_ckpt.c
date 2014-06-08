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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_default_cockpits (void)
{
	initialise_default_lamps ();

	initialise_default_instrument_colours ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_default_cockpits (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_default_cockpits (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void draw_default_cockpit (cockpit_panels panel)
{
	////////////////////////////////////////
	//
	// select cockpit graphics wrt time of day
	//
	////////////////////////////////////////

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		case DAY_SEGMENT_TYPE_DAWN:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DAY:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL1_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DUSK:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_NIGHT:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL3_BASE;

			break;
		}
	}

	#if DEMO_VERSION

	base_cockpit_graphics_file = GRAPHICS_COCKPITS_APACHE_LEVEL1_BASE;

	#endif

	set_default_instrument_colours ();

	////////////////////////////////////////
	//
	// draw overlaid instruments
	//
	////////////////////////////////////////

	if (!get_global_draw_cockpit_graphics ())
	{
		if (get_global_draw_overlaid_instruments ())
		{
			if ((panel != COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD) && (panel != COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD))
			{
				draw_overlaid_default_mfd (68.0, 412.0, 128.0, MFD_LOCATION_LHS);

				draw_overlaid_default_mfd (572.0, 412.0, 128.0, MFD_LOCATION_RHS);
			}
		}
	}

	////////////////////////////////////////
	//
	// draw cockpits
	//
	////////////////////////////////////////

	switch (panel)
	{
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_LEFT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U40_L90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U40_L60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U40_L30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U40_AHD_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U40_R30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U40_R60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U40_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_LEFT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U20_L90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U20_L60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_U20_L30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U20_L30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_U20_AHD_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U20_AHD_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U20_R30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U20_R60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_U20_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LVL_L90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LVL_L60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_LVL_L30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LVL_L30_RLE), ix_640_480, iy_640_480);

					draw_default_indicator_lamps (panel);

					draw_default_fire_detector_lamps (panel);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_LVL_AHD_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LVL_AHD_RLE), ix_640_480, iy_640_480);

					draw_default_indicator_lamps (panel);

					draw_default_fire_detector_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_default_upfront_display_on_cockpit (fx_640_480 + 338.0, fy_640_480 + 428.0);
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_LVL_R30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LVL_R30_RLE), ix_640_480, iy_640_480);

					draw_default_indicator_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_default_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_UPFRONT_DISPLAY
				);
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LVL_R60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LVL_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_D20_L90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_D20_L60_RLE), ix_640_480, iy_640_480);

					draw_default_fixed_cockpit_clock_hands (panel);

					draw_default_armament_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_default_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_D20_L30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_D20_L30_RLE), ix_640_480, iy_640_480);

					draw_default_fixed_cockpit_clock_hands (panel);

					draw_default_indicator_lamps (panel);

					draw_default_fire_detector_lamps (panel);

					draw_default_armament_lamps (panel);

					draw_default_mfd_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_default_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_MFD_MASK_D20_L30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_COMPASS,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_D20_AHD_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_D20_AHD_RLE), ix_640_480, iy_640_480);

					draw_default_fixed_cockpit_airspeed_indicator_needle (panel);

					draw_default_fixed_cockpit_barometric_altimeter_digits (panel);

					draw_default_fixed_cockpit_barometric_altimeter_needle (panel);

					draw_default_fixed_cockpit_clock_hands (panel);

					draw_default_indicator_lamps (panel);

					draw_default_fire_detector_lamps (panel);

					draw_default_armament_lamps (panel);

					draw_default_mfd_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_default_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);

				draw_default_upfront_display_on_cockpit (fx_640_480 + 334.0, fy_640_480 + 226.0);

				draw_default_mfd_on_cockpit (fx_640_480 + 226.0, fy_640_480 + 367.0, FALSE, FALSE, MFD_LOCATION_LHS);

				draw_default_mfd_on_cockpit (fx_640_480 + 414.0, fy_640_480 + 367.0, FALSE, FALSE, MFD_LOCATION_RHS);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_MFD_MASK_D20_AHD_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_COMPASS,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_WIPER_D20_R30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_D20_R30_RLE), ix_640_480, iy_640_480);

					draw_default_fixed_cockpit_airspeed_indicator_needle (panel);

					draw_default_fixed_cockpit_barometric_altimeter_needle (panel);

					draw_default_indicator_lamps (panel);

					draw_default_mfd_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_default_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_MFD_MASK_D20_R30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_COMPASS,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_D20_R60_RLE), ix_640_480, iy_640_480);

					draw_default_fixed_cockpit_airspeed_indicator_needle (panel);

					draw_default_fixed_cockpit_barometric_altimeter_needle (panel);

					unlock_screen (active_screen);
				}

				draw_default_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_default_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_D20_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}

			draw_default_hud ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				blit_rgb_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_LHS_MFD_RGB), ix_640_480, iy_640_480);

				draw_default_armament_lamps (panel);

				draw_default_mfd_lamps (panel);

				unlock_screen (active_screen);
			}

			draw_default_mfd_on_cockpit (fx_640_480 + 320.0, fy_640_480 + 235.0, TRUE, FALSE, MFD_LOCATION_LHS);

			if (lock_screen (active_screen))
			{
				blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_MFD_MASK_LHS_MFD_RLE), ix_640_480, iy_640_480);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD:
		////////////////////////////////////////
		{
			draw_default_external_virtual_cockpit
			(
				VIRTUAL_COCKPIT_LARGE_ADI,
				NULL
			);

			if (lock_screen (active_screen))
			{
				blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_RHS_MFD_RLE), ix_640_480, iy_640_480);

				draw_default_mfd_lamps (panel);

				unlock_screen (active_screen);
			}

			draw_default_internal_virtual_cockpit
			(
				VIRTUAL_COCKPIT_INSTRUMENT_LARGE_NEEDLES
			);

			draw_default_mfd_on_cockpit (fx_640_480 + 320.0, fy_640_480 + 235.0, TRUE, FALSE, MFD_LOCATION_RHS);

			if (lock_screen (active_screen))
			{
				blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_APACHE_MFD_MASK_RHS_MFD_RLE), ix_640_480, iy_640_480);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid cockpit panel = %d", panel);

			break;
		}
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
