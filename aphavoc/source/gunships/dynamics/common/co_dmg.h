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

#define NUM_DYNAMIC_DAMAGES 15

enum DYNAMICS_DAMAGE_TYPES
{

	DYNAMICS_DAMAGE_NONE							= (1 << 0),		// 1
	DYNAMICS_DAMAGE_MAIN_ROTOR 				= (1 << 1),		// 2
	DYNAMICS_DAMAGE_TAIL_ROTOR 				= (1 << 2),		// 4
	DYNAMICS_DAMAGE_LEFT_ENGINE				= (1 << 3),		// 8
	DYNAMICS_DAMAGE_RIGHT_ENGINE				= (1 << 4),		// 16
	DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE			= (1 << 5),		// 32
	DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE		= (1 << 6),		// 64
	DYNAMICS_DAMAGE_LOW_HYDRAULICS			= (1 << 7),		// 128
	DYNAMICS_DAMAGE_STABILISER					= (1 << 8),		// 256
	DYNAMICS_DAMAGE_FUEL_LEAK					= (1 << 9),		// 512
	DYNAMICS_DAMAGE_LOW_OIL_PRESSURE			= (1 << 10),	// 1k
	DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE		= (1 << 11),	// 2k
	DYNAMICS_DAMAGE_AVIONICS					= (1 << 12),	// 4k
	DYNAMICS_DAMAGE_FIRE_EXTINGUISHER		= (1 << 13),	// 8k
	DYNAMICS_DAMAGE_UNDERCARRIAGE				= (1 << 14),	// 16k
	NUM_DYNAMICS_DAMAGE_TYPES					= (1 << NUM_DYNAMIC_DAMAGES)		// 32
};

typedef enum DYNAMICS_DAMAGE_TYPES dynamics_damage_types;

#define DYNAMICS_DAMAGE_ALL (NUM_DYNAMICS_DAMAGE_TYPES - 1)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMICS_DAMAGE_TYPE
{

	char
		*name;

	dynamics_damage_types
		type;

	float
		kickin_value,
		damage_severity,
		repair_time;

	int
		store_aggressor_in_debrief,
		repairable;
};

typedef struct DYNAMICS_DAMAGE_TYPE dynamics_damage_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define get_dynamics_damage() (current_flight_dynamics->dynamics_damage)

#define get_dynamics_damage_type(TYPE) ((current_flight_dynamics->dynamics_damage & (TYPE)) ? TRUE : FALSE)

#define set_dynamics_damage_repair_type(TYPE) (current_flight_dynamics->dynamics_damage &= (~(TYPE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void dynamics_damage_model (unsigned int damage, int random);

extern int get_current_dynamics_fatal_damage (void);

extern void update_dynamics_at_keysite (void);

extern void update_dynamics_damage (void);

extern void dynamics_restore_damage_values (void);

extern int get_dynamics_damage_currently_repairing_type (void);

extern void repair_damage_model (unsigned int damage);

extern void damage_entity_to_flight_model (entity *en);

extern void damage_helicopter_via_damage_level (entity *en, entity *aggressor);

extern void set_current_dynamics_options (dynamics_options_types option, int flag);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
