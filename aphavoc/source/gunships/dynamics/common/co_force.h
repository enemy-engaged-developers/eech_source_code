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

extern int
	fixed_collision_count,
	moving_collision_count;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DYNAMICS_COLLISION_POINT_TYPES
{

	DYNAMICS_COLLISION_POINT_MAIN_ROTOR,
	DYNAMICS_COLLISION_POINT_TAIL_ROTOR,
	DYNAMICS_COLLISION_POINT_FUSELAGE,
	DYNAMICS_COLLISION_POINT_NOSE_GUN,
	DYNAMICS_COLLISION_POINT_WHEEL,
	DYNAMICS_COLLISION_POINT_WING_TIP,
	NUM_DYNAMICS_COLLISION_POINT_TYPES
};

typedef enum DYNAMICS_COLLISION_POINT_TYPES dynamics_collision_point_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMICS_COLLISION_POINT_TYPE
{

	char
		*name;

	object_3d_sub_object_index_numbers
		sub_object_type;

	int
		moving;

	dynamics_damage_types
		damage_type;
};

typedef struct DYNAMICS_COLLISION_POINT_TYPE dynamics_collision_point_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMICS_COLLISION_TYPE
{

	dynamics_collision_point_types
		collision_point_type;

	vec3d
		face_normal,
		world_point,
		model_point,
		collision_point;

	float
		terrain_elevation,
		violation_distance;

	unsigned short int
		violated;
};

typedef struct DYNAMICS_COLLISION_TYPE dynamics_collision_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMIC_FORCE_TYPE
{

	vec3d
		direction,
		position;

	float
		duration,
		linear_force;

	char
		*name;

	unsigned short int
		valid;
};

typedef struct DYNAMIC_FORCE_TYPE dynamic_force_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_dynamic_forces (void);

extern void initialise_flight_dynamics_collision_points (void);

extern void deinitialise_dynamic_forces (void);

extern void update_collision_dynamics (void);

extern void add_dynamic_force (char *name, float force, float duration, vec3d *position, vec3d *direction, int flag);

extern void update_dynamic_forces (void);

extern void resolve_dynamic_forces (void);

extern void draw_dynamic_forces (void);

extern void add_dynamic_explosion_force (vec3d *explosion_position, float force);

extern void add_dynamic_weapon_launch_force (vec3d *position, vec3d *direction, float force, float duration);

extern void resolve_moments (float x, float y, float z, float *x_axis_moment, float *y_axis_moment, float *z_axis_moment);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
