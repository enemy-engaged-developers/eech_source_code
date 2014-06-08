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

void initialise_hind_cockpits (void)
{
	initialise_hind_lamps ();

	initialise_havoc_instrument_colours ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_cockpits (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hind_cockpits (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
void draw_hind_cockpit (cockpit_panels panel)
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
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DAY:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL1_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_DUSK:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL2_BASE;

			break;
		}
		case DAY_SEGMENT_TYPE_NIGHT:
		{
			base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL3_BASE;

			break;
		}
	}

	#if DEMO_VERSION

	base_cockpit_graphics_file = GRAPHICS_COCKPITS_HAVOC_LEVEL1_BASE;

	#endif

	set_havoc_instrument_colours ();

	////////////////////////////////////////
	//
	// draw overlaid instruments
	//
	////////////////////////////////////////

	if (!get_global_draw_cockpit_graphics ())
	{
		if (get_global_draw_overlaid_instruments ())
		{
			if (panel != COCKPIT_PANEL_SPECIAL_HAVOC_TV)
			{
				draw_overlaid_hind_mfd (68.0, 412.0, 128.0);

				draw_overlaid_hind_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
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
				if (custom_3d_models.arneh_mi24v_cockpit)
					draw_hind_external_3d_cockpit(0, NULL);
				else
				{
					draw_hind_external_virtual_cockpit
					(
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR,
						NULL
					);

					if (lock_screen (active_screen))
					{
						blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U40_L90_RLE), ix_640_480, iy_640_480);

						unlock_screen (active_screen);
					}
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U40_L60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR |
					VIRTUAL_COCKPIT_COMPASS,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U40_L30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR |
					VIRTUAL_COCKPIT_COMPASS,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_U40_AHD_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U40_AHD_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_U40_R30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U40_R30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U40_R60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP40_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U40_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_LEFT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U20_L90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U20_L60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				if (custom_3d_models.arneh_mi24v_cockpit)
				{
					draw_hind_external_3d_cockpit(0, NULL);
					draw_hind_internal_3d_cockpit(0);
				}
				else
				{
					draw_hind_external_virtual_cockpit
					(
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR |
						VIRTUAL_COCKPIT_COMPASS,
						NULL
					);

					if (lock_screen (active_screen))
					{
						blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U20_L30_RLE), ix_640_480, iy_640_480);

						unlock_screen (active_screen);
					}

					draw_hind_internal_virtual_cockpit
					(
						VIRTUAL_COCKPIT_HUD_GLASS |
						VIRTUAL_COCKPIT_HUD_DISPLAY
					);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR |
					VIRTUAL_COCKPIT_COMPASS,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_U20_AHD_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U20_AHD_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY
				);
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_U20_R30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U20_R30_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY
				);
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U20_R60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_UP20_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_U20_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_LVL_L90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_LVL_L60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_LVL_L30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_LVL_L30_RLE), ix_640_480, iy_640_480);

					draw_havoc_g_meter (panel);

					draw_havoc_radar_altimeter (panel);

					draw_hind_weapons_management_panel_lamps (panel);

					draw_hind_master_caution_lamp (panel);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY
				);
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_LVL_AHD_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_LVL_AHD_RLE), ix_640_480, iy_640_480);

					draw_havoc_g_meter (panel);

					draw_havoc_radar_altimeter (panel);

					draw_havoc_weapons_management_panel_lamps (panel);

					draw_hind_threat_warning_display (panel);

					draw_hind_master_caution_lamp (panel);

					draw_hind_warning_panel_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit (VIRTUAL_COCKPIT_HUD_GLASS);

				draw_hind_hud_on_cockpit (get_global_hud_enlarge ());
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_LVL_R30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_LVL_R30_RLE), ix_640_480, iy_640_480);

					draw_hind_status_panel_lamps (panel);

					draw_hind_threat_warning_display (panel);

					draw_hind_warning_panel_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY
				);
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_LVL_R60_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_LEVEL_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_LVL_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_D20_L90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_D20_L60_RLE), ix_640_480, iy_640_480);

					draw_havoc_barometric_altimeter (panel);

					draw_hind_weapons_management_panel_lamps (panel);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_LEFT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_HSI |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_D20_L30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_D20_L30_RLE), ix_640_480, iy_640_480);

					draw_havoc_barometric_altimeter (panel);

					draw_havoc_airspeed_indicator (panel);

					draw_havoc_main_rotor_rpm_indicator (panel);

					draw_havoc_g_meter (panel);

					draw_havoc_vertical_speed_indicator (panel);

					draw_havoc_clock (panel);

					draw_havoc_radar_altimeter (panel);

					draw_hind_weapons_management_panel_lamps (panel);

					draw_hind_master_caution_lamp (panel);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY |
					VIRTUAL_COCKPIT_CRT_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_AHEAD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_HSI |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_D20_AHD_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_D20_AHD_RLE), ix_640_480, iy_640_480);

					draw_havoc_barometric_altimeter (panel);

					draw_havoc_airspeed_indicator (panel);

					draw_havoc_main_rotor_rpm_indicator (panel);

					draw_havoc_g_meter (panel);

					draw_havoc_engine_torque_indicator (panel);

					draw_havoc_engine_temperature_indicator (panel);

					draw_havoc_engine_rpm_indicator (panel);

					draw_havoc_engine_temperature_and_rpm_indicator_ticks (panel);

					draw_havoc_vertical_speed_indicator (panel);

					draw_havoc_clock (panel);

					draw_havoc_radar_altimeter (panel);

					draw_havoc_fuel_gauge (panel);

					draw_havoc_fixed_cockpit_hsi_waypoint_distance_digits (panel);

					draw_havoc_fixed_cockpit_hsi_waypoint_identifier (panel);

					draw_havoc_weapons_management_panel_lamps (panel);

					draw_havoc_status_panel_lamps (panel);

					draw_havoc_threat_warning_display (panel);

					draw_havoc_master_caution_lamp (panel);

					draw_havoc_warning_panel_lamps (panel);

					draw_havoc_radio_lamp (panel);

					draw_havoc_oil_gauges (panel);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);

				draw_hind_mfd_on_cockpit (fx_640_480 + 354.0, fy_640_480 + 337.0, FALSE, FALSE);

				draw_hind_ekran_display_on_cockpit (fx_640_480 + 459.0, fy_640_480 + 310.0);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_CRT_MASK_D20_AHD_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT30:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_D20_R30_RLE)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_D20_R30_RLE), ix_640_480, iy_640_480);

					draw_havoc_engine_torque_indicator (panel);

					draw_havoc_engine_temperature_indicator (panel);

					draw_havoc_engine_rpm_indicator (panel);

					draw_havoc_engine_temperature_and_rpm_indicator_ticks (panel);

					draw_havoc_fuel_gauge (panel);

					draw_hind_status_panel_lamps (panel);

					draw_hind_threat_warning_display (panel);

					draw_hind_warning_panel_lamps (panel);

					draw_hind_radio_lamp (panel);

					draw_havoc_oil_gauges (panel);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY |
					VIRTUAL_COCKPIT_CRT_DISPLAY |
					VIRTUAL_COCKPIT_EKRAN_DISPLAY
				);
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT60:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_D20_R60_RLE), ix_640_480, iy_640_480);

					draw_hind_status_panel_lamps (panel);

					draw_hind_radio_lamp (panel);

					draw_havoc_oil_gauges (panel);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_DOWN20_RIGHT90:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_D20_R90_RLE), ix_640_480, iy_640_480);

					unlock_screen (active_screen);
				}
			}
			else
			{
				draw_hind_hud_on_cockpit (TRUE);
			}

			draw_hind_hms ();

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				blit_rgb_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_CRT_RGB), ix_640_480, iy_640_480);

				unlock_screen (active_screen);
			}

			draw_hind_mfd_on_cockpit (fx_640_480 + 321.0, fy_640_480 + 229.0, TRUE, FALSE);

			if (lock_screen (active_screen))
			{
				blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_CRT_MASK_CRT_RLE), ix_640_480, iy_640_480);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				draw_hind_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_LARGE_HUD |
					VIRTUAL_COCKPIT_RENDERED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_WIPER_HUD)
				);

				if (lock_screen (active_screen))
				{
					blit_rle_graphic (get_graphics_file_data (base_cockpit_graphics_file + GRAPHICS_COCKPITS_HAVOC_HUD_RLE), ix_640_480, iy_640_480);

					draw_hind_threat_warning_display (panel);

					draw_hind_master_caution_lamp (panel);

					draw_hind_warning_panel_lamps (panel);

					unlock_screen (active_screen);
				}

				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_LARGE_HUD |
					VIRTUAL_COCKPIT_HUD_GLASS
				);
			}

			draw_hind_hud_on_cockpit (TRUE);

			draw_hind_hms ();

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
