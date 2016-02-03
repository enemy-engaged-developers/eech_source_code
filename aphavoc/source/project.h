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

#define INTERNAL_MODULES 1

#ifndef INTERNAL_MODULES
#define NO_INTERNAL_MODULES 1
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// For the small oem demonstration version for 3dlabs
//

#define OEM_3DLABS_VERSION 0

//
// For the demo version (Remake and delete sound block if changed)
//

#define DEMO_VERSION 		0

//
// Initialises 3D object sub-object states for recognition guide
//

#define RECOGNITION_GUIDE 	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "system.h"

#include "graphics.h"

#include "maths.h"

#include "misc.h"

#include "multi.h"

#include "userint2.h"

#include "2d.h"

#include "3d.h"

#include "sound.h"

#ifdef OGRE_EE
// FIXME
#define screen void
#define display_device void
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ai_extrn.h"

#include "cmndline.h"

#include "deinit.h"

#include "flight.h"

#include "game.h"

#include "gfxfiles.h"

#include "global.h"

#include "init.h"

#include "test.h"

#include "update.h"

#include "install.h"

#include "cdmusic.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "appsound/appsound.h"

#include "comms/comms.h"

#include "entity/entity.h"

#include "ai/ai.h"

#include "app3d/app3d.h"

#include "events/events.h"

#include "gameflow/gameflow.h"

#include "gunships/gunships.h"

#include "misc/miscell.h"

#include "ui_menu/ui_menu.h"

#include "eechini.h"  //VJ 030403

#include "servlog.h" // Jabberwock 031119 Server log

#include "wutcfg.h"   //VJ 030326

#include "gwutcfg.h"   //VJ 040220

#include "sharedmem.h"	// Retro 8Mar2005

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	cdrom_drive_letter;

extern int
	apache_havoc_installation_path_valid;

extern char
	apache_havoc_installation_path[];

// JB 030311 Enable running out of separate directories
extern char
	comanche_hokum_installation_path[];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_registry_language_settings ( void );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef OGRE_EE
#define read_joystick_values(x)

// This is temporary while gunships\avionics and gnuships\cockpits build disabled
// gunships
#define reset_hokum_crew_eject_sequence()
extern int rocket_salvo_count, fire_continuous_weapon, hud_mode, previous_hud_mode;
#define HUD_MODE_WEAPON 0
#define select_simple_avionics_target_acquisition_system()
#define AIR_RADAR_CONTACT_TIMEOUT	(10.0)
#define activate_common_threat_warning_system(x)
#define damage_client_server_entity_avionics(x, y)
#define update_avionics()
#define update_cockpits()
#define repair_gunship_weapon_damage()
#define eo_tracking_point_valid(x) 0
#define get_crew_role() crew_role
extern int crew_role;
extern int
	mouse_move_left,
	mouse_move_right,
	mouse_move_up,
	mouse_move_down,
	mouse_wheel_up,
	mouse_wheel_down;
#define get_gunship_comms_equipment_ok() 0
extern float canopy_door_state;
#define gunship_damage_levels int
#define set_gunship_weapon(x)
extern int display_hud_layout_grid, display_mfd_layout_grid, test_cockpit_instruments, draw_virtual_cockpit_needles_on_fixed_cockpits, night_vision_system_active, draw_radar_sweep, draw_hms_field_of_view, draw_radar_terrain_los_markers, draw_hms_terrain_los_markers, draw_eo_boresight, draw_eo_terrain_los_markers;
#define partially_repair_gunship_damage()
#define fully_repair_gunship_damage()
#define notify_avionics_of_dynamics_fault(x)
#define partially_repair_local_entity_avionics(x)
#define fully_repair_local_entity_avionics(x)
extern int fire_extinguisher_used;
extern float debug_var_x, debug_var_y, debug_var_z;
#define display_hud_on_external_view()
#define get_num_virtual_cockpit_cameras(x) 0
#define move_by_rate(x, y, z) ((x) + (y) + (z))
extern float radar_range_apache[5];
extern float radar_range_comanche[5];
extern float radar_range_blackhawk[5];
extern float radar_range_havoc[5];
extern float radar_range_hokum[5];
extern float radar_range_hind[5];
extern float radar_range_default[5];
#define initialise_cockpits()
#define initialise_avionics()
#define deinitialise_cockpits()
#define deinitialise_avionics()
#define damage_gunship(x)
#define add_pfz(a, b, c, d)
#define next_free_pfz 0
#define get_number_of_valid_gunship_targets(x) 0
#define get_valid_gunship_target_safe_index(x, y) 0
#define set_valid_gunship_target_safe_index(x)
#define cycle_tsd_map_palette()
#define select_next_current_virtual_cockpit_camera(x)
extern float pilot_head_pitch_datum, co_pilot_head_pitch_datum;

extern void deinitialise_population_name_database (void);
#endif
