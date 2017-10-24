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

struct HELICOPTER
{
	aircraft
		ac;

	int
		timer;

	float
		fuel_supply_level,
		invulnerable_timer,
		main_rotor_rpm,
		main_rotor_pitch,
		main_rotor_roll,
		main_rotor_blade_coning_angle,
		main_rotor_spin_up_timer,
		// Jabberwock 050310 MP Cannon bug
		player_weapon_heading,
		player_weapon_pitch,
		// Jabberwock 050310 ends
		tail_rotor_rpm;

	unsigned int
		helicopter_damage_flags	: NUM_HELICOPTER_DAMAGE_FLAGS_BITS,
		helicopter_weapon_damage_flags	: NUM_HELICOPTER_DAMAGE_FLAGS_BITS,
		auto_pilot					: NUM_AUTO_PILOT_BITS,
		player						: NUM_PLAYER_BITS,
		main_rotor_damaged		: 1,
		tail_rotor_damaged		: 1,
		los_to_target				: NUM_LOS_TO_TARGET_BITS,
		radar_on						: NUM_RADAR_ON_BITS,
		laser_on						: NUM_LASER_ON_BITS,
		infra_red_jammer_on		: NUM_INFRA_RED_JAMMER_ON_BITS,
		radar_jammer_on			: NUM_RADAR_JAMMER_ON_BITS,
		weapons_hold				: NUM_WEAPONS_HOLD_BITS,
		position_hold				: NUM_POSITION_HOLD_BITS,
		lock_on_after_launch		: NUM_LOCK_ON_AFTER_LAUNCH_BITS;

	list_root
		designated_target_root,	// Jabberwock 031107 Designated target
		gunship_target_root,
		padlock_root;

	vec3d
		cover_position,
		wait_position,
		eo_tracking_point;
};

typedef struct HELICOPTER helicopter;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern entity
	*gunship_entity;

struct SECTOR;

extern struct SECTOR
	*gunship_current_sector;

#define get_gunship_entity() (gunship_entity)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAIN_ROTOR_SPIN_UP_TIMER 25.0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_gunship_entity (entity *en);

extern void assign_entity_to_user (entity *en);

extern void set_raw_gunship_entity (entity *en);

extern void set_gunship_entity_to_external_view_entity (event *ev);

extern void restore_helicopter_entity (entity *en);

extern void notify_gunship_entity_mission_completed (entity *en, entity *task);

extern void notify_gunship_entity_mission_terminated (entity *en, entity *task);

extern void create_helicopter_rotor_sound_effects (entity *en);

extern void kill_helicopter_rotor_sound_effects (entity *en);

extern void update_local_helicopter_rotor_sounds (entity *en);

extern void play_helicopter_winding_rotor_sounds (entity *en, int direction, int engine_num);

extern int get_local_entity_suitable_for_player (entity *en, entity *pilot);

extern void helicopter_assume_player_control (entity *en);

extern void helicopter_release_player_control (entity *en);

extern void transmit_player_recon_data (entity *en);

extern int get_helicopter_allowed_to_rearm (entity *en);

extern int helicopter_within_keysite_area (entity *en);

extern int player_mission_logged(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "hc_anim.h"

#include "hc_creat.h"

#include "hc_draw.h"

#include "hc_dstry.h"

#include "hc_float.h"

#include "hc_funcs.h"

#include "hc_int.h"

#include "hc_list.h"

#include "hc_move.h"

#include "hc_msgs.h"

#include "hc_pack.h"

#include "hc_tgt.h"

#include "hc_updt.h"

#include "hc_vec3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
