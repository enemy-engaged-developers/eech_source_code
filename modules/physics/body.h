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

// used for the number of temp rigid_body variables used in the integrator (midpoint = 2, runga kutta = 5)

#define RB_DEPTH 5

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// debug
extern struct OBJECT
	*camera_object;
// debug

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COLLISION_TYPES
{

	COLLISION_TYPE_NONE,
	COLLISION_TYPE_BOUNDING_BOX,
	COLLISION_TYPE_CYLINDER,
	COLLISION_TYPE_SPHERE,
	COLLISION_TYPE_COLLISION_TRIANGLES,
};

typedef enum COLLISION_TYPES collision_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum INTEGRATOR_TYPES
{

	INTEGRATOR_EULER,
	INTEGRATOR_MID_POINT,
	INTEGRATOR_RUNGA_KUTTA
};

typedef enum INTEGRATOR_TYPES integrator_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMIC_FORCES
{

	char
		*name;

	double_vec3d
		position,
		direction;

	double
		force;

	struct DYNAMIC_FORCES
		*next;
};

typedef struct DYNAMIC_FORCES dynamic_forces;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct RIGID_BODY_DYNAMICS
{

	char
		*name;

	int
		visited,
		system_id;

	double
		density,
		inverse_mass,
		coefficient_of_static_friction,
		coefficient_of_kinetic_friction,
		coefficient_of_restitution,
		mass;

	double_matrix3x3
		attitude,
		body_inertia_tensor,
		inverse_body_inertia_tensor,
		inverse_world_inertia_tensor;

	int
		collided_flag,
		powered,
		collisions,
		fixed_position,
		fixed_rotation,
		valid_last_bounding_box,
		number_of_collision_points;

	double_vec3d
		scaling,
		last_bounding_box [8],
		torque [RB_DEPTH],
		linear_force [RB_DEPTH],
		constraint_torque [RB_DEPTH],
		constraint_linear_force [RB_DEPTH],
		angular_momentum [RB_DEPTH],
		angular_velocity [RB_DEPTH],
		original_position_cm [RB_DEPTH],
		position_cm [RB_DEPTH],
		velocity_cm [RB_DEPTH],
		acceleration_cm [RB_DEPTH],
		*collision_points,
		collision_point [100],
		collision_normal [100];

	dynamic_forces
		*forces [RB_DEPTH];

	collision_types
		collision_type;

	double
		xmin,
		ymin,
		zmin,
		xmax,
		ymax,
		zmax;

	struct RIGID_BODY_DYNAMICS
		*prev,
		*next;
};

typedef struct RIGID_BODY_DYNAMICS rigid_body_dynamics;

extern rigid_body_dynamics
	*rigid_body_list_head;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	rigid_body_simulation_frequency;

#define set_rigid_body_simulation_frequency(FREQUENCY) (rigid_body_simulation_frequency = (FREQUENCY))

#define get_rigid_body_simulation_frequency() (rigid_body_simulation_frequency)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern double
	rigid_body_delta_time,
	rigid_body_slow_motion,
	one_over_rigid_body_delta_time;

extern void set_rigid_body_delta_time (double time);

#define get_rigid_body_delta_time() (rigid_body_delta_time)

#define get_one_over_rigid_body_delta_time() (one_over_rigid_body_delta_time)

#define set_rigid_body_slow_motion(SLOW_MO) (rigid_body_slow_motion = (SLOW_MO))

#define get_rigid_body_slow_motion() (rigid_body_slow_motion)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_rigid_body_system (void);

extern void deinitialise_rigid_body_system (void);

extern rigid_body_dynamics *create_rigid_body (struct OBJECT *obj, char *name, int object_number);

extern void set_rigid_body_mass (rigid_body_dynamics *rb, double mass);

extern double get_rigid_body_mass (rigid_body_dynamics *rb);

extern void set_rigid_body_scaling (rigid_body_dynamics *rb, double scaling_x, double scaling_y, double scaling_z);

extern void set_rigid_body_dimensions (rigid_body_dynamics *rb, double x, double y, double z);

extern void reset_rigid_body (rigid_body_dynamics *rb, double_vec3d *position);

extern void update_rigid_bodies (void);

extern void apply_forces (rigid_body_dynamics *rb, dynamic_forces **force_list);

extern void add_dynamic_force (dynamic_forces **force_list, double_vec3d *position, double_vec3d *direction, double force, char *name, rigid_body_dynamics *rb);

extern void resolve_forces (rigid_body_dynamics *rb, int index);

extern void integrate_quantities (integrator_types integrator);

extern void collision_check_with_ground (rigid_body_dynamics *rb, int index);

extern double get_total_rigid_body_energies (void);

extern double get_object_total_mass (rigid_body_dynamics *rb);

extern void save_rigid_body_system (void);

extern void load_rigid_body_system (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void create_arrow (char *name, double_vec3d *position, double_vec3d *direction, double size);

extern void draw_arrows (void);

extern void create_line (double_vec3d *position1, double_vec3d *position2);

extern void draw_lines (void);

extern void draw_rigid_body_bounding_box (rigid_body_dynamics *rb);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
