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

extern void open_client_server_entity_loading_doors( entity *en );

extern void close_client_server_entity_loading_doors( entity *en );

extern void open_client_server_entity_cargo_doors( entity *en );

extern void close_client_server_entity_cargo_doors( entity *en );

extern void open_client_server_entity_airbrakes( entity *en );

extern void close_client_server_entity_airbrakes( entity *en );

extern void open_client_server_entity_flaps( entity *en );

extern void close_client_server_entity_flaps( entity *en );

extern void lower_client_server_entity_undercarriage( entity *en );

extern void raise_client_server_entity_undercarriage( entity *en );

extern int get_local_entity_undercarriage_state (entity *en);

// start add loading and cargo doors for separate switching in helis by GCsDriver  08-12-2007
extern int get_local_entity_loading_door_state (entity *en);

extern int get_local_entity_cargo_door_state (entity *en);
// end add loading and cargo doors for separate switching in helis by GCsDriver   08-12-2007

extern void open_entity_weapon_system_ready( entity *en );

extern void close_entity_weapon_system_ready( entity *en );

extern int get_local_entity_weapon_system_ready_state (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_local_entity_id_number
(
	entity *en,
	texture_animation_indices digit0,
	texture_animation_indices digit1,
	texture_animation_indices digit2,
	texture_animation_indices digit3,
	texture_animation_indices digit4
);

extern char *get_local_entity_id_number_string (entity *en, char *buffer);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define WEAPON_SYSTEM_READY_CLOSED		0
#define WEAPON_SYSTEM_READY_OPENING		1
#define WEAPON_SYSTEM_READY_OPEN			2
#define WEAPON_SYSTEM_READY_CLOSING		3

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "key_anim.h"

#include "sub_anim.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
