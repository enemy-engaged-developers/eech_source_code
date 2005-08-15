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

enum FORMATION_TYPES
{

	FORMATION_NONE,
	FORMATION_1,
	FORMATION_ROW_LEFT,
	FORMATION_ROW_RIGHT,
	FORMATION_ECHELON_LEFT,
	FORMATION_ECHELON_RIGHT,
	FORMATION_COLUMN,
	FORMATION_WEDGE,
	FORMATION_80M_ROAD_NODE_16_TANKS,
	FORMATION_INFANTRY_COLUMN,

	FORMATION_INVALID,
	NUM_FORMATION_TYPES
};

typedef enum FORMATION_TYPES formation_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum FORMATION_COMPONENT_TYPES
{

	FORMATION_COMPONENT_HELICOPTER_LIGHT_ASSAULT_GROUP,
	FORMATION_COMPONENT_HELICOPTER_HEAVY_ASSAULT_GROUP,
	FORMATION_COMPONENT_HELICOPTER_MARINE_ASSAULT_GROUP_A,
	FORMATION_COMPONENT_HELICOPTER_MARINE_ASSAULT_GROUP_B,

	FORMATION_COMPONENT_HELICOPTER_LIGHT_ATTACK_GROUP_A,
	FORMATION_COMPONENT_HELICOPTER_LIGHT_ATTACK_GROUP_B,
	FORMATION_COMPONENT_HELICOPTER_HEAVY_ATTACK_GROUP_A,
	FORMATION_COMPONENT_HELICOPTER_HEAVY_ATTACK_GROUP_B,
	FORMATION_COMPONENT_HELICOPTER_MARINE_ATTACK_GROUP_A,
	FORMATION_COMPONENT_HELICOPTER_MARINE_ATTACK_GROUP_B,
	FORMATION_COMPONENT_HELICOPTER_MARINE_ATTACK_GROUP_C,
	FORMATION_COMPONENT_HELICOPTER_MARINE_ATTACK_GROUP_D,

	FORMATION_COMPONENT_HELICOPTER_LIGHT_RECON_GROUP,

	FORMATION_COMPONENT_HELICOPTER_LIGHT_RECON_ATTACK_GROUP,
	FORMATION_COMPONENT_HELICOPTER_HEAVY_RECON_ATTACK_GROUP,
	FORMATION_COMPONENT_HELICOPTER_HUNTER_KILLER_GROUP,

	FORMATION_COMPONENT_HELICOPTER_MEDIUM_LIFT_GROUP,
	FORMATION_COMPONENT_HELICOPTER_HEAVY_LIFT_GROUP_A,
	FORMATION_COMPONENT_HELICOPTER_HEAVY_LIFT_GROUP_B,

	FORMATION_COMPONENT_FIXED_WING_CLOSE_AIR_SUPPORT_GROUP,
	FORMATION_COMPONENT_FIXED_WING_MULTI_ROLE_GROUP,
	FORMATION_COMPONENT_FIXED_WING_CARRIER_BORNE_STRIKE_GROUP,
	FORMATION_COMPONENT_FIXED_WING_CARRIER_BORNE_INTERCEPTOR_GROUP,
	FORMATION_COMPONENT_FIXED_WING_MEDIUM_LIFT_GROUP,
	FORMATION_COMPONENT_FIXED_WING_HEAVY_LIFT_GROUP,
	FORMATION_COMPONENT_PRIMARY_FRONTLINE_GROUP,
	FORMATION_COMPONENT_SECONDARY_FRONTLINE_GROUP,
	FORMATION_COMPONENT_HEAVY_SAM_AAA_GROUP,
	FORMATION_COMPONENT_LIGHT_SAM_AAA_GROUP,
	FORMATION_COMPONENT_ARTILLERY_GROUP,
	FORMATION_COMPONENT_MLRS_GROUP,
	FORMATION_COMPONENT_INFANTRY,
	FORMATION_COMPONENT_INFANTRY_SAM_STANDING,
	FORMATION_COMPONENT_INFANTRY_SAM_KNEELING,
	FORMATION_COMPONENT_AIRCRAFT_CARRIER_GROUP,
	FORMATION_COMPONENT_FRIGATE_GROUP,
	FORMATION_COMPONENT_LANDING_GROUP,

	NUM_FORMATION_COMPONENT_TYPES
};

typedef enum FORMATION_COMPONENT_TYPES formation_component_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FORMATION_TYPE
{

	formation_types
		formation;

	char
		*name;

	short int
		number_in_formation;

	vec3d
		*sites;

	struct FORMATION_TYPE
		*next;
};

typedef struct FORMATION_TYPE formation_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FORMATION_VEHICLE_COMPONENTS
{

	formation_component_types
		formation_component;

	formation_types
		formation;

	int
		count,
		group_type,
		*components;

	struct FORMATION_VEHICLE_COMPONENTS
		*next;
};

typedef struct FORMATION_VEHICLE_COMPONENTS formation_vehicle_components;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*formation_names [],
	*formation_display_names [],
	*formation_component_names [];

extern formation_type
	*formation_database;

extern formation_vehicle_components
	*formation_component_database;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_formation_database (void);

extern void initialise_formation_database_table (void);

extern int add_formation_to_database (int formation_count, vec3d *site_positions);

extern int get_formation_database_count (void);

extern void deinitialise_formation_database (void);

extern formation_type *get_formation (formation_types formation);

extern short int get_number_in_formation (formation_types formation);

extern const char *get_formation_name (formation_types formation);

extern float get_formation_member_radius (formation_types form, int member_count);

extern void get_formation_position (formation_types form, int index, vec3d *vec);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_formation_component_database (void);

extern void deinitialise_formation_component_database (void);

extern formation_vehicle_components *get_formation_components (formation_component_types formation_component);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
