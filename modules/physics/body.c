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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "physics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 		0

#define GRAVITY	 			9.81

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// debug
object
	*camera_object = NULL;
// debug

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rigid_body_dynamics
	*rigid_body_list_head = nullptr;

int
	rigid_body_simulation_frequency = 50;

double
	rigid_body_delta_time,
	rigid_body_slow_motion = 1.0,
	one_over_rigid_body_delta_time;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void matrix_skew (double_matrix3x3 skew, double_vec3d *vec);

static void orthonormalize_attitude (double_matrix3x3 attitude);

static void resolve_collision (rigid_body_dynamics *rb1, rigid_body_dynamics *rb2, double_vec3d *collision_point, double_vec3d *face_normal, int index1, int index2);

int get_object_object_bounding_collision_point (object *obj1, object *obj2, double_vec3d *double_position, double_vec3d *double_face_normal);

static void euler_integrator (rigid_body_dynamics *rb, int initial_index, int source_index, int target_index, double delta_time);

static void copy_rigid_body (rigid_body_dynamics *rb, int source, int target);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// debug functions

void create_vectored_debug_3d_object (double_vec3d *position, double_vec3d *direction, int object_number, double scaling);

void create_line (double_vec3d *position1, double_vec3d *position2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_rigid_body_system (void)
{

	debug_log ("BODY: Initialised Rigid Body System");

	debug_watch ("Rigid Body Frequency			= %d", MT_INT, &rigid_body_simulation_frequency);

	debug_watch ("Rigid Body delta time			= %f", MT_DOUBLE, &rigid_body_delta_time);

	deinitialise_rigid_body_system ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_rigid_body_system (void)
{

	rigid_body_dynamics
		*destroy_rb = nullptr;

	while (rigid_body_list_head)
	{

		destroy_rb = rigid_body_list_head;

		rigid_body_list_head = rigid_body_list_head->next;

		if (destroy_rb->name)
		{

			free_mem (destroy_rb->name);
		}

		if (destroy_rb->collision_points)
		{

			free_mem (destroy_rb->collision_points);
		}

		free_mem (destroy_rb);
	}

	rigid_body_list_head = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_rigid_body_delta_time (double time)
{

	rigid_body_delta_time = time / rigid_body_slow_motion;

	one_over_rigid_body_delta_time = 1.0 / rigid_body_delta_time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rigid_body_dynamics *create_rigid_body (struct OBJECT *obj, char *name, int object_number)
{

	struct OBJECT_3D_BOUNDS
		*bounding_box = nullptr;

	double
		xmax,
		xmin,
		ymax,
		ymin,
		zmax,
		zmin,
		dx,
		dy,
		dz;

	rigid_body_dynamics
		*new_rb = nullptr;

	//
	// Create new Rigid body
	//

	new_rb = (rigid_body_dynamics *) malloc_heap_mem (sizeof (rigid_body_dynamics));

	memset (new_rb, 0, sizeof (rigid_body_dynamics));

	new_rb->next = rigid_body_list_head;

	if (rigid_body_list_head)
	{

		rigid_body_list_head->prev = new_rb;
	}

	rigid_body_list_head = new_rb;

	new_rb->prev = NULL;

	if (obj)
	{

		obj->rigid_body = new_rb;
	}

	if (name)
	{

		new_rb->name = (char *) malloc_heap_mem (strlen (name) + 2);

		sprintf (new_rb->name, "%s", name);
	}

	//
	// Setup Rigid body
	//

	bounding_box = get_object_3d_bounding_box (object_number);

	xmax = bounding_box->xmax;
	xmin = bounding_box->xmin;
	ymax = bounding_box->ymax;
	ymin = bounding_box->ymin;
	zmax = bounding_box->zmax;
	zmin = bounding_box->zmin;

	new_rb->scaling.x = 1.0;
	new_rb->scaling.y = 1.0;
	new_rb->scaling.z = 1.0;

	// debug
	if ((stricmp (name, "WHEEL_FRONT_LEFT") == 0) || (stricmp (name, "WHEEL_FRONT_RIGHT") == 0))
	{

		xmin = -0.125;
		ymin = -0.34;
		zmin = -0.34;
		xmax = 0.125;
		ymax = 0.34;
		zmax = 0.34;
	} 
	else if ((stricmp (name, "WHEEL_BACK_LEFT") == 0) || (stricmp (name, "WHEEL_BACK_RIGHT") == 0))
	{

		xmin = -0.14;
		ymin = -0.34;
		zmin = -0.34;
		xmax = 0.14;
		ymax = 0.34;
		zmax = 0.34;
	}
	// debug

	new_rb->xmin = xmin;
	new_rb->ymin = ymin;
	new_rb->zmin = zmin;
	new_rb->xmax = xmax;
	new_rb->ymax = ymax;
	new_rb->zmax = zmax;

	dx = xmax - xmin;
	dy = ymax - ymin;
	dz = zmax - zmin;

	get_identity_double_matrix3x3 (new_rb->attitude);

	// determine body constants // I_-1(cm), M

	new_rb->powered = FALSE;

	new_rb->density = 0.04;

	new_rb->valid_last_bounding_box = FALSE;

	set_rigid_body_mass (new_rb, 8.0 * new_rb->density * dx * dy * dz);

	new_rb->coefficient_of_static_friction = 0.0;
	new_rb->coefficient_of_kinetic_friction = 0.0;

	new_rb->coefficient_of_restitution = 0.01;

	// determine intial conditions
		// r(cm), v(cm) A, L(cm)

	new_rb->fixed_position = FALSE;
	new_rb->fixed_rotation = FALSE;

	memset (new_rb->velocity_cm, 0, sizeof (double_vec3d) * RB_DEPTH);

	memset (new_rb->angular_momentum, 0, sizeof (double_vec3d) * RB_DEPTH);

	//
	// Collision points
	// NB. Should be done dynamically via lightwave object
	//

	new_rb->collision_type = COLLISION_TYPE_BOUNDING_BOX;

	new_rb->number_of_collision_points = 8;

	new_rb->collision_points = (double_vec3d *) malloc_heap_mem (sizeof (double_vec3d) * new_rb->number_of_collision_points);

	new_rb->collision_points [0].x = xmin;
	new_rb->collision_points [0].y = ymin;
	new_rb->collision_points [0].z = zmin;

	new_rb->collision_points [1].x = xmin;
	new_rb->collision_points [1].y = ymin;
	new_rb->collision_points [1].z = zmax;

	new_rb->collision_points [2].x = xmax;
	new_rb->collision_points [2].y = ymin;
	new_rb->collision_points [2].z = zmax;

	new_rb->collision_points [3].x = xmax;
	new_rb->collision_points [3].y = ymin;
	new_rb->collision_points [3].z = zmin;

	new_rb->collision_points [4].x = xmin;
	new_rb->collision_points [4].y = ymax;
	new_rb->collision_points [4].z = zmin;

	new_rb->collision_points [5].x = xmin;
	new_rb->collision_points [5].y = ymax;
	new_rb->collision_points [5].z = zmax;

	new_rb->collision_points [6].x = xmax;
	new_rb->collision_points [6].y = ymax;
	new_rb->collision_points [6].z = zmax;

	new_rb->collision_points [7].x = xmax;
	new_rb->collision_points [7].y = ymax;
	new_rb->collision_points [7].z = zmin;

	return new_rb;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_rigid_body_mass (rigid_body_dynamics *rb, double mass)
{

	double
		a,
		b,
		dx,
		dy,
		dz;

	//a = radius;
	//b = cylinder width;

	dx = rb->xmax - rb->xmin;
	dy = rb->ymax - rb->ymin;
	dz = rb->zmax - rb->zmin;

	dx *= rb->scaling.x;
	dy *= rb->scaling.y;
	dz *= rb->scaling.z;

	rb->mass = mass;

	rb->inverse_mass = 1.0 / rb->mass;

	// cube
	//rb->inverse_body_inertia_tensor [0][0] = 3.0 / (rb->mass * ((dy * dy) + (dz * dz)));
	//rb->inverse_body_inertia_tensor [1][1] = 3.0 / (rb->mass * ((dx * dx) + (dz * dz)));
	//rb->inverse_body_inertia_tensor [2][2] = 3.0 / (rb->mass * ((dx * dx) + (dy * dy)));
	rb->body_inertia_tensor [0][0] = (rb->mass / 4.0) * (((dy * dy) + (dz * dz)));
	rb->body_inertia_tensor [1][1] = (rb->mass / 4.0) * (((dx * dx) + (dz * dz)));
	rb->body_inertia_tensor [2][2] = (rb->mass / 4.0) * (((dx * dx) + (dy * dy)));

	// sphere
	//a = 3.535533;
	//rb->body_inertia_tensor [0][0] = (5.0 * (rb->mass * (a * a))) / 2.0;
	//rb->body_inertia_tensor [1][1] = (5.0 * (rb->mass * (a * a))) / 2.0;
	//rb->body_inertia_tensor [2][2] = (5.0 * (rb->mass * (a * a))) / 2.0;

	// cylinder
	a = 3.535533;
	b = 5.0;
	//rb->body_inertia_tensor [0][0] = (rb->mass / 2.0) * ((0.5 * a * a) + ((1.0 / 3.0) * b * b));
	//rb->body_inertia_tensor [1][1] = (rb->mass / 2.0) * ((0.5 * a * a) + ((1.0 / 3.0) * b * b));
	//rb->body_inertia_tensor [2][2] = (rb->mass / 2.0) * (a * a);

	get_inverse_double_matrix (rb->inverse_body_inertia_tensor, rb->body_inertia_tensor);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double get_rigid_body_mass (rigid_body_dynamics *rb)
{

	return rb->mass;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_rigid_body_scaling (rigid_body_dynamics *rb, double scaling_x, double scaling_y, double scaling_z)
{

	rb->scaling.x = scaling_x;
	rb->scaling.y = scaling_y;
	rb->scaling.z = scaling_z;

	// recalculate inverse body inertia tensor
	set_rigid_body_mass (rb, rb->mass);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_rigid_body_dimensions (rigid_body_dynamics *rb, double x, double y, double z)
{

	double
		dx,
		dy,
		dz;

	dx = rb->xmax - rb->xmin;
	dy = rb->ymax - rb->ymin;
	dz = rb->zmax - rb->zmin;

	rb->scaling.x = x / dx;
	rb->scaling.y = y / dy;
	rb->scaling.z = z / dz;

	// recalculate inverse body inertia tensor
	set_rigid_body_mass (rb, rb->mass);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_rigid_body (rigid_body_dynamics *rb, double_vec3d *position)
{

	int
		loop;

	dynamic_forces
		*force = nullptr,
		*destroy_force = nullptr;

	get_identity_double_matrix3x3 (rb->attitude);

	rb->valid_last_bounding_box = FALSE;

	for (loop = 0; loop < RB_DEPTH; loop ++)
	{
	
		force = rb->forces [loop];
	
		while (force)
		{
	
			destroy_force = force;
	
			force = force->next;
	
			if (destroy_force->name)
			{
	
				free_mem (destroy_force->name);
			}
	
			free_mem (destroy_force);
		}

		memset (&rb->torque [loop], 0.0, sizeof (double_vec3d));
		memset (&rb->linear_force [loop], 0.0, sizeof (double_vec3d));
		memset (&rb->angular_momentum [loop], 0.0, sizeof (double_vec3d));
		memset (&rb->angular_velocity [loop], 0.0, sizeof (double_vec3d));

		rb->original_position_cm [loop] = *position;
		rb->position_cm [loop] = *position;
		
		memset (&rb->velocity_cm [loop], 0.0, sizeof (double_vec3d));
		memset (&rb->acceleration_cm [loop], 0.0, sizeof (double_vec3d));

		rb->forces [loop] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_rigid_bodies (void)
{

	double
		relative_velocity;

	dynamic_forces
		*force = nullptr,
		*destroy_force = nullptr;

	rigid_body_dynamics
		*current_rb = nullptr;

	#if DEBUG_MODULE
				
	debug_log ("BODY: update rigid bodies");

	#endif

	//
	// apply forces
	//

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		memset (&current_rb->linear_force [0], 0, sizeof (double_vec3d));
		memset (&current_rb->torque [0], 0, sizeof (double_vec3d));

		apply_forces (current_rb, &current_rb->forces [0]);

		if (current_rb->collisions)
		{

			collision_check_with_ground (current_rb, 0);
		}

		current_rb = current_rb->next;
	}

	//
	// resolve forces
	//

	update_connections_parameters (0);

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		resolve_forces (current_rb, 0);

		current_rb = current_rb->next;
	}

	// friction1

	#if DEBUG_MODULE
				
	debug_log ("BODY: friction 1");

	#endif

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		if (current_rb->collided_flag)
		{
		
			calculate_friction (current_rb, 0);
		}

		current_rb = current_rb->next;
	}

	// constraints1

	#if DEBUG_MODULE
				
	debug_log ("BODY: constraint 1");

	#endif

	update_connections_constraints (0);

	destroy_friction_forces ();

	// friction2

	#if DEBUG_MODULE
				
	debug_log ("BODY: friction 2");

	#endif

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		if (current_rb->collided_flag)
		{
		
			calculate_friction (current_rb, 0);
		}

		current_rb = current_rb->next;
	}

	//destroy_constraint_forces ();

	//constraints2

	#if DEBUG_MODULE
				
	debug_log ("BODY: constraint 2");

	#endif

	//update_connections_constraints (0);

	apply_constraint_forces (0);

	apply_friction_forces (0);

	//
	// do integrator
	//

	if (rigid_body_list_head)
	{

		double_vec3d
			position1,
			position2;

		position1 = rigid_body_list_head->position_cm [0];

		//integrate_quantities (INTEGRATOR_MID_POINT);
		integrate_quantities (INTEGRATOR_EULER);

		position2 = rigid_body_list_head->position_cm [0];

		create_line (&position1, &position2);
	}

	//
	// reset forces
	//

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		relative_velocity = current_rb->angular_velocity [0].x;

		// destroy rigid_body forces

		force = current_rb->forces [0];

		while (force)
		{

			destroy_force = force;

			force = force->next;

			if (destroy_force->name)
			{

				free_mem (destroy_force->name);
			}

			free_mem (destroy_force);
		}

		current_rb->forces [0] = NULL;
		current_rb->forces [1] = NULL;

		current_rb = current_rb->next;

		if (current_rb)
		{

			relative_velocity -= current_rb->angular_velocity [0].x;
		}
	}

	//debug_log ("relative vel = %f", relative_velocity);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apply_forces (rigid_body_dynamics *rb, dynamic_forces **force_list)
{

	double_vec3d
		position,
		direction;

	//
	// apply forces
	//

	// Gravity

	position.x = 0.0;
	position.y = 0.0;
	position.z = 0.0;

	multiply_double_matrix3x3_double_vec3d (&position, rb->attitude, &position);

	direction.x = 0.0;
	direction.y = -1.0;
	direction.z = 0.0;

	add_dynamic_force (force_list, &position, &direction, G * rb->mass, "Gravity", rb);

	{

		static double
			f = 1.0;

		if (check_key (DIK_F))
		{
	
			//if (stricmp (rb->name, "body") == 0)
			{
			
				position.x = 2.5;
				position.y = 2.5;
				position.z = 2.5;
			
				multiply_double_matrix3x3_double_vec3d (&position, rb->attitude, &position);
			
				direction.x = 0.0;
				direction.y = 0.0;
				direction.z = 1.0;
			
				add_dynamic_force (force_list, &position, &direction, f * rb->mass, "Special force", rb);

				// debug
				rb->collision_point [0] = position;
				// debug
			}
		}
	}

	/*
	if ((stricmp (rb->name, "wheel 2") == 0))
	{

		double_vec3d
			position,
			direction,
			torque;

		position.x = 0.0;
		position.y = -1.0;
		position.x = 0.0;

		torque.x = rb->mass;
		torque.y = 0.0;
		torque.z = 0.0;

		get_3d_double_vector_cross_product (&direction, &torque, &position);

		direction.z /= 3.535533;

		position.x = 0.0;
		position.y = -3.535533;
		position.x = 0.0;

		add_dynamic_force (force_list, &position, &direction, 1.0, "Force 2", rb);
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_dynamic_force (dynamic_forces **force_list, double_vec3d *position, double_vec3d *direction, double force, char *name, rigid_body_dynamics *rb)
{

	dynamic_forces
		*new_force = nullptr;

	// all in world space (except position, thats in object space)

	new_force = (dynamic_forces *) malloc_heap_mem (sizeof (dynamic_forces));

	memset (new_force, 0, sizeof (dynamic_forces));

	new_force->name = (char *) malloc_heap_mem (sizeof (char) * (strlen (name) + 2));

	sprintf (new_force->name, "%s", name);

	new_force->position = *position;

	new_force->direction = *direction;

	new_force->force = force;

	new_force->next = *force_list;

	*force_list = new_force;

	// debug
	#if 1
	{

		double_vec3d
			temp_direction,
			temp_position;

		//debug_log ("BODY: add_force: %s force = %f direction = [%f, %f, %f] position [%f, %f, %f]", name, force, direction->x, direction->y, direction->z, position->x, position->y, position->z);

		temp_position = *position;

		temp_position.x = rb->position_cm [0].x + temp_position.x;
		temp_position.y = rb->position_cm [0].y + temp_position.y;
		temp_position.z = rb->position_cm [0].z + temp_position.z;

		temp_direction = *direction;

		if (strcmp ("Ground Friction", name) == 0)
		{

			create_arrow ("TIP_ARROW", &temp_position, &temp_direction, 1.0);
		}
		else if (strcmp ("Acceleration", name) == 0)
		{

			create_arrow ("TAIL_ARROW", &temp_position, &temp_direction, 10.0);
		}
		else
		{

			create_arrow ("CENTRE_ARROW", &temp_position, &temp_direction, 1.0);
		}
	}
	#endif
	// debug
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resolve_forces (rigid_body_dynamics *rb, int index)
{

	double_vec3d
		cross;

	dynamic_forces
		*force = nullptr;

	// all in world space

	force = rb->forces [index];

	while (force)
	{

		//
		// Linearly
		//

		rb->linear_force [index].x += force->force * force->direction.x;
		rb->linear_force [index].y += force->force * force->direction.y;
		rb->linear_force [index].z += force->force * force->direction.z;

		//
		// Angularly
		//

		get_3d_double_vector_cross_product (&cross, &force->direction, &force->position);

		rb->torque [index].x += force->force * cross.x;
		rb->torque [index].y += force->force * cross.y;
		rb->torque [index].z += force->force * cross.z;

		force = force->next;
	}

	update_connections_forces (rb, index);

	///////////////////////////////////////////////////////////////////////////////
	// debug
	///////////////////////////////////////////////////////////////////////////////
	#if 0
	//if ((rb->powered) && (stricmp (rb->name, "wheel 2") != 0))
	if (rb->powered) 
	{

		static double
			t= 0.0;

		double_vec3d
			torque;

		if (check_key (DIK_I))
		{
	
			t -= 10.0 * get_rigid_body_delta_time ();
	
			debug_log ("rb %d, TORQUE %f", rb, t);
		}
		else if (check_key (DIK_K))
		{

			t += 10.0 * get_rigid_body_delta_time ();
	
			debug_log ("rb %d, TORQUE %f", rb, t);
		}
		else if (check_key (DIK_M))
		{
	
			t = 0.0;
	
			debug_log ("rb %d, TORQUE %f", rb, t);
		}

		t = -1.0;

		torque.x = t * rb->mass;
		torque.y = 0.0;
		torque.z = 0.0;
	
		multiply_double_matrix3x3_double_vec3d (&torque, rb->attitude, &torque);

		rb->torque [index].x += torque.x;
		rb->torque [index].y += torque.y;
		rb->torque [index].z += torque.z;
	}
	#endif
	///////////////////////////////////////////////////////////////////////////////
	// debug
	///////////////////////////////////////////////////////////////////////////////

	// damping

	//rb->linear_force [index].x += -0.4 * rb->velocity_cm [index].x * rb->mass;
	//rb->linear_force [index].y += -0.4 * rb->velocity_cm [index].y * rb->mass;
	//rb->linear_force [index].z += -0.4 * rb->velocity_cm [index].z * rb->mass;

	//rb->torque [index].x += -0.4 * rb->angular_velocity [index].x * rb->mass;
	//rb->torque [index].y += -0.4 * rb->angular_velocity [index].y * rb->mass;
	//rb->torque [index].z += -0.4 * rb->angular_velocity [index].z * rb->mass;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void euler_integrator (rigid_body_dynamics *rb, int initial_index, int source_index, int target_index, double delta_time)
{

	double_matrix3x3
		result;
		//skew_angular;

	double
		mass,
		inverse_mass;

	//
	// get total mass of system
	//

	mass = rb->mass;

	inverse_mass = 1.0 / mass;

	/////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Linearly
	//
	/////////////////////////////////////////////////////////////////////////////////////////////

	// acceleration
	rb->acceleration_cm [target_index].x = rb->linear_force [source_index].x * inverse_mass;
	rb->acceleration_cm [target_index].y = rb->linear_force [source_index].y * inverse_mass;
	rb->acceleration_cm [target_index].z = rb->linear_force [source_index].z * inverse_mass;

	if (!rb->fixed_position)
	{
	
		// velocity
		rb->velocity_cm [target_index].x = rb->velocity_cm [initial_index].x + (rb->acceleration_cm [source_index].x * delta_time);
		rb->velocity_cm [target_index].y = rb->velocity_cm [initial_index].y + (rb->acceleration_cm [source_index].y * delta_time);
		rb->velocity_cm [target_index].z = rb->velocity_cm [initial_index].z + (rb->acceleration_cm [source_index].z * delta_time);
	
  		// position
		rb->position_cm [target_index].x = rb->position_cm [initial_index].x + (rb->velocity_cm [source_index].x * delta_time);
		rb->position_cm [target_index].y = rb->position_cm [initial_index].y + (rb->velocity_cm [source_index].y * delta_time);
		rb->position_cm [target_index].z = rb->position_cm [initial_index].z + (rb->velocity_cm [source_index].z * delta_time);
	}

	if (!rb->fixed_rotation)
	{

		double_matrix3x3
			m;

		double_vec3d
			torque,
			angular_velocity;

		double
			mag;

		/////////////////////////////////////////////////////////////////////////////////////////////
		//
		// Angularly
		//
		/////////////////////////////////////////////////////////////////////////////////////////////
	
		// angular_momentum 

		multiply_transpose_double_matrix3x3_double_vec3d (&torque, rb->attitude, &rb->torque [initial_index]);

		rb->angular_momentum [target_index].x += torque.x * delta_time;
		rb->angular_momentum [target_index].y += torque.y * delta_time;
		rb->angular_momentum [target_index].z += torque.z * delta_time;

		// inverse_world_inertia_tensor

		multiply_double_matrix3x3_double_matrix3x3 (result, rb->attitude, rb->inverse_body_inertia_tensor);
		multiply_double_matrix3x3_transpose_double_matrix3x3 (rb->inverse_world_inertia_tensor, result, rb->attitude);
	
		// angular_velocity

		multiply_double_matrix3x3_double_vec3d (&rb->angular_velocity [target_index], result, &rb->angular_momentum [target_index]);

		// attitude

		angular_velocity = rb->angular_velocity [source_index];

		mag = normalise_any_3d_double_vector (&angular_velocity);
	
		get_arbitrary_rotation_double_matrix (m, &angular_velocity, mag * delta_time);

		multiply_double_matrix3x3_double_vec3d ((double_vec3d *) rb->attitude [0], m, (double_vec3d *) rb->attitude [0]);
		multiply_double_matrix3x3_double_vec3d ((double_vec3d *) rb->attitude [1], m, (double_vec3d *) rb->attitude [1]);
		multiply_double_matrix3x3_double_vec3d ((double_vec3d *) rb->attitude [2], m, (double_vec3d *) rb->attitude [2]);
	
		orthonormalize_attitude (rb->attitude);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void integrate_quantities (integrator_types integrator)
{

	switch (integrator)
	{

		case INTEGRATOR_EULER:
		{

			rigid_body_dynamics
				*current_rb = nullptr;

			//
			// Euler Integrator
			//

			current_rb = rigid_body_list_head;

			while (current_rb)
			{

				euler_integrator (current_rb, 0, 0, 0, get_rigid_body_delta_time ());

				current_rb = current_rb->next;
			}

			break;
		}

		case INTEGRATOR_MID_POINT:
		{

			//
			// Mid point Integrator
			//

			rigid_body_dynamics
				*current_rb = nullptr;

			double
				half_delta_time;

			// 1st step

			current_rb = rigid_body_list_head;

			while (current_rb)
			{

				copy_rigid_body (current_rb, 0, 1);

				current_rb->forces [1] = current_rb->forces [0];

				half_delta_time = get_rigid_body_delta_time () * 0.5;

				euler_integrator (current_rb, 0, 0, 1, half_delta_time);

				current_rb = current_rb->next;
			}

			//
			// forces
			//

			current_rb = rigid_body_list_head;

			while (current_rb)
			{

				memset (&current_rb->linear_force [1], 0, sizeof (double_vec3d));
				memset (&current_rb->torque [1], 0, sizeof (double_vec3d));

				resolve_forces (current_rb, 1);

				current_rb = current_rb->next;
			}

			{
				// friction1

				#if DEBUG_MODULE
				
				debug_log ("BODY: mid - friction 1");

				#endif
			
				current_rb = rigid_body_list_head;
			
				while (current_rb)
				{
			
					if (current_rb->collided_flag)
					{
					
						calculate_friction (current_rb, 1);
					}
			
					current_rb = current_rb->next;
				}
			
				// constraints1

				#if DEBUG_MODULE
				
				debug_log ("BODY: mid - constraint 1");

				#endif
			
				update_connections_constraints (1);
			
				destroy_friction_forces ();
			
				// friction2

				#if DEBUG_MODULE
				
				debug_log ("BODY: mid - friction 2");

				#endif
			
				current_rb = rigid_body_list_head;
			
				while (current_rb)
				{
			
					if (current_rb->collided_flag)
					{
					
						calculate_friction (current_rb, 1);

						current_rb->collided_flag = FALSE;
					}
			
					current_rb = current_rb->next;
				}
			
				//destroy_constraint_forces ();
			
				//constraints2

				#if DEBUG_MODULE
				
				debug_log ("BODY: mid - constraint 2");

				#endif
			
				//update_connections_constraints (1);
			
				apply_constraint_forces (1);
			
				apply_friction_forces (1);
			}

			// 2nd step

			current_rb = rigid_body_list_head;

			while (current_rb)
			{

				euler_integrator (current_rb, 0, 1, 0, get_rigid_body_delta_time ());

				current_rb = current_rb->next;
			}

			break;
		}

		case INTEGRATOR_RUNGA_KUTTA:
		{

			debug_fatal ("RUNGA-KUTTA INTEGRATOR NOT CODED");
/*
			//
			// Runga Kutta Integrator
			//

			// was in resolve forces... moved to euler... needs to be added somewhere for RK4
			// acceleration
			rb->acceleration_cm [target_index].x = rb->linear_force [source_index].x * rb->inverse_mass;
			rb->acceleration_cm [target_index].y = rb->linear_force [source_index].y * rb->inverse_mass;
			rb->acceleration_cm [target_index].z = rb->linear_force [source_index].z * rb->inverse_mass;
		
			object
				*current_object = nullptr;

			rigid_body_dynamics
				*source = nullptr,
				*target = nullptr,
				*accum1 = nullptr,
				*accum2 = nullptr,
				*accum3 = nullptr,
				*accum4 = nullptr;

			double
				half_delta_time,
				sixth_delta_time;

			half_delta_time = get_rigid_body_delta_time () * 0.5;
			sixth_delta_time = (1.0 / 6.0);

			while (iterations --)
			{
	
				// 1st step
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					source = &current_object->rigid_body [0];
					target = &current_object->rigid_body [1];
					accum1 = &current_object->rigid_body [2];
	
					accum1->linear_force.x = half_delta_time * source->linear_force.x * source->inverse_mass;
					accum1->linear_force.y = half_delta_time * source->linear_force.y * source->inverse_mass;
					accum1->linear_force.z = half_delta_time * source->linear_force.z * source->inverse_mass;

					accum1->velocity_cm.x = half_delta_time * source->velocity_cm.x;
					accum1->velocity_cm.y = half_delta_time * source->velocity_cm.y;
					accum1->velocity_cm.z = half_delta_time * source->velocity_cm.z;

					// DETERMINE THE NEW VELOCITY FOR THE PARTICLE OVER 1/2 TIME
					target->velocity_cm.x = source->velocity_cm.x + (accum1->linear_force.x);
					target->velocity_cm.y = source->velocity_cm.y + (accum1->linear_force.y);
					target->velocity_cm.z = source->velocity_cm.z + (accum1->linear_force.z);
			
					target->inverse_mass = source->inverse_mass;
			
					// SET THE NEW POSITION
					target->position_cm.x = source->position_cm.x + (accum1->velocity_cm.x);
					target->position_cm.y = source->position_cm.y + (accum1->velocity_cm.y);
					target->position_cm.z = source->position_cm.z + (accum1->velocity_cm.z);
	
					current_object = current_object->next;
				}

				// destroy forces

				current_object= object_list_head;

				while (current_object)
				{

					int
						loop;
			
					// destroy rigid_body forces
			
					for (loop = 0; loop < 5; loop ++)
					{

						dynamic_forces
							*force = nullptr,
							*destroy_force = nullptr;
				
						force = current_object->rigid_body [loop].forces;
				
						while (force)
						{
				
							destroy_force = force;
				
							force = force->next;

							if (destroy_force->name)
							{

								free_mem (destroy_force->name);
							}

							free_mem (destroy_force);
						}
				
						current_object->rigid_body [loop].forces = NULL;
					}
			
					current_object= current_object->next;
				}
	
				// forces
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					if (!current_object->fixed_position)
					{

						ASSERT (!current_object->rigid_body [1].forces);
	
						apply_forces (current_object, &current_object->rigid_body [1]);
					}
	
					current_object = current_object->next;
				}
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					if (!current_object->fixed_position)
					{
	
						//resolve_forces (current_object, &current_object->rigid_body [1]);
					}
	
					current_object = current_object->next;
				}

				// 2nd Step
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					source = &current_object->rigid_body [0];
					target = &current_object->rigid_body [1];
					accum1 = &current_object->rigid_body [3];

					accum1->linear_force.x = half_delta_time * target->linear_force.x * source->inverse_mass;
					accum1->linear_force.y = half_delta_time * target->linear_force.y * source->inverse_mass;
					accum1->linear_force.z = half_delta_time * target->linear_force.z * source->inverse_mass;

					accum1->velocity_cm.x = half_delta_time * target->velocity_cm.x;
					accum1->velocity_cm.y = half_delta_time * target->velocity_cm.y;
					accum1->velocity_cm.z = half_delta_time * target->velocity_cm.z;
			
					target->velocity_cm.x = source->velocity_cm.x + (accum1->linear_force.x);
					target->velocity_cm.y = source->velocity_cm.y + (accum1->linear_force.y);
					target->velocity_cm.z = source->velocity_cm.z + (accum1->linear_force.z);
			
					target->inverse_mass = source->inverse_mass;
			
					target->position_cm.x = source->position_cm.x + (accum1->velocity_cm.x);
					target->position_cm.y = source->position_cm.y + (accum1->velocity_cm.y);
					target->position_cm.z = source->position_cm.z + (accum1->velocity_cm.z);
	
					current_object = current_object->next;
				}

				// destroy forces

				current_object= object_list_head;

				while (current_object)
				{

					int
						loop;
			
					// destroy rigid_body forces
			
					for (loop = 0; loop < 5; loop ++)
					{

						dynamic_forces
							*force = nullptr,
							*destroy_force = nullptr;
				
						force = current_object->rigid_body [loop].forces;
				
						while (force)
						{
				
							destroy_force = force;
				
							force = force->next;

							if (destroy_force->name)
							{

								free_mem (destroy_force->name);
							}

							free_mem (destroy_force);
						}
				
						current_object->rigid_body [loop].forces = NULL;
					}
			
					current_object= current_object->next;
				}
	
				// forces
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					if (!current_object->fixed_position)
					{

						ASSERT (!current_object->rigid_body [1].forces);
	
						apply_forces (current_object, &current_object->rigid_body [1]);
					}
	
					current_object = current_object->next;
				}
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					if (!current_object->fixed_position)
					{
	
						//resolve_forces (current_object, &current_object->rigid_body [1]);
					}
	
					current_object = current_object->next;
				}

				// 3nd Step
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					source = &current_object->rigid_body [0];
					target = &current_object->rigid_body [1];
					accum1 = &current_object->rigid_body [4];

					accum1->linear_force.x = get_rigid_body_delta_time () * target->linear_force.x * source->inverse_mass;
					accum1->linear_force.y = get_rigid_body_delta_time () * target->linear_force.y * source->inverse_mass;
					accum1->linear_force.z = get_rigid_body_delta_time () * target->linear_force.z * source->inverse_mass;

					accum1->velocity_cm.x = get_rigid_body_delta_time () * target->velocity_cm.x;
					accum1->velocity_cm.y = get_rigid_body_delta_time () * target->velocity_cm.y;
					accum1->velocity_cm.z = get_rigid_body_delta_time () * target->velocity_cm.z;
			
					target->velocity_cm.x = source->velocity_cm.x + (accum1->linear_force.x);
					target->velocity_cm.y = source->velocity_cm.y + (accum1->linear_force.y);
					target->velocity_cm.z = source->velocity_cm.z + (accum1->linear_force.z);
			
					target->inverse_mass = source->inverse_mass;
			
					target->position_cm.x = source->position_cm.x + (accum1->velocity_cm.x);
					target->position_cm.y = source->position_cm.y + (accum1->velocity_cm.y);
					target->position_cm.z = source->position_cm.z + (accum1->velocity_cm.z);

					current_object = current_object->next;
				}
	
				// destroy forces

				current_object= object_list_head;

				while (current_object)
				{

					int
						loop;
			
					// destroy rigid_body forces
			
					for (loop = 0; loop < 5; loop ++)
					{

						dynamic_forces
							*force = nullptr,
							*destroy_force = nullptr;
				
						force = current_object->rigid_body [loop].forces;
				
						while (force)
						{
				
							destroy_force = force;
				
							force = force->next;

							if (destroy_force->name)
							{

								free_mem (destroy_force->name);
							}

							free_mem (destroy_force);
						}
				
						current_object->rigid_body [loop].forces = NULL;
					}
			
					current_object= current_object->next;
				}
	
				// forces
	
				current_object = object_list_head;
	
				while (current_object)
				{

					ASSERT (!current_object->rigid_body [1].forces);
	
					if (!current_object->fixed_position)
					{
	
						apply_forces (current_object, &current_object->rigid_body [1]);
					}
	
					current_object = current_object->next;
				}
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					if (!current_object->fixed_position)
					{
	
						//resolve_forces (current_object, &current_object->rigid_body [1]);
					}
	
					current_object = current_object->next;
				}

				// 4th Step
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					source = &current_object->rigid_body [0];
					target = &current_object->rigid_body [1];
					accum1 = &current_object->rigid_body [5];

					accum1->linear_force.x = get_rigid_body_delta_time () * target->linear_force.x * source->inverse_mass;
					accum1->linear_force.y = get_rigid_body_delta_time () * target->linear_force.y * source->inverse_mass;
					accum1->linear_force.z = get_rigid_body_delta_time () * target->linear_force.z * source->inverse_mass;
			
					accum1->velocity_cm.x = get_rigid_body_delta_time () * target->velocity_cm.x;
					accum1->velocity_cm.y = get_rigid_body_delta_time () * target->velocity_cm.y;
					accum1->velocity_cm.z = get_rigid_body_delta_time () * target->velocity_cm.z;
	
					current_object = current_object->next;
				}

				// destroy forces

				current_object= object_list_head;

				while (current_object)
				{

					int
						loop;
			
					// destroy rigid_body forces
			
					for (loop = 0; loop < 5; loop ++)
					{

						dynamic_forces
							*force = nullptr,
							*destroy_force = nullptr;
				
						force = current_object->rigid_body [loop].forces;
				
						while (force)
						{
				
							destroy_force = force;
				
							force = force->next;

							if (destroy_force->name)
							{

								free_mem (destroy_force->name);
							}

							free_mem (destroy_force);
						}
				
						current_object->rigid_body [loop].forces = NULL;
					}
			
					current_object= current_object->next;
				}

				// Final step
	
				current_object = object_list_head;
	
				while (current_object)
				{
	
					source = &current_object->rigid_body [0];
					target = &current_object->rigid_body [0];
					accum1 = &current_object->rigid_body [2];
					accum2 = &current_object->rigid_body [3];
					accum3 = &current_object->rigid_body [4];
					accum4 = &current_object->rigid_body [5];

					target->velocity_cm.x = source->velocity_cm.x + ((accum1->linear_force.x + ((accum2->linear_force.x + accum3->linear_force.x) * 2.0) + accum4->linear_force.x) * sixth_delta_time);
					target->velocity_cm.y = source->velocity_cm.y + ((accum1->linear_force.y + ((accum2->linear_force.y + accum3->linear_force.y) * 2.0) + accum4->linear_force.y) * sixth_delta_time);
					target->velocity_cm.z = source->velocity_cm.z + ((accum1->linear_force.z + ((accum2->linear_force.z + accum3->linear_force.z) * 2.0) + accum4->linear_force.z) * sixth_delta_time);

					target->position_cm.x = source->position_cm.x + ((accum1->velocity_cm.x + ((accum2->velocity_cm.x + accum3->velocity_cm.x) * 2.0) + accum4->velocity_cm.x) * sixth_delta_time);
					target->position_cm.y = source->position_cm.y + ((accum1->velocity_cm.y + ((accum2->velocity_cm.y + accum3->velocity_cm.y) * 2.0) + accum4->velocity_cm.y) * sixth_delta_time);
					target->position_cm.z = source->position_cm.z + ((accum1->velocity_cm.z + ((accum2->velocity_cm.z + accum3->velocity_cm.z) * 2.0) + accum4->velocity_cm.z) * sixth_delta_time);

					current_object = current_object->next;
				}
			}

*/
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void matrix_skew (double_matrix3x3 skew, double_vec3d *vec)
{

	skew [0][0] = 0.0;
	skew [0][1] = -vec->z;
	skew [0][2] = vec->y;

	skew [1][0] = vec->z;
	skew [1][1] = 0.0;
	skew [1][2] = -vec->x;

	skew [2][0] = -vec->y;
	skew [2][1] = vec->x;
	skew [2][2] = 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void orthonormalize_attitude (double_matrix3x3 attitude)
{

	double_vec3d
		x,
		y;

	normalise_any_3d_double_vector ((double_vec3d *) attitude [2]);

	get_3d_double_vector_cross_product (&y, (double_vec3d *) attitude [2], (double_vec3d *) attitude [0]);
	normalise_any_3d_double_vector (&y);

	get_3d_double_vector_cross_product (&x, &y, (double_vec3d *) attitude [2]);
	normalise_any_3d_double_vector (&x);

	memcpy (&attitude [0][0], &x, sizeof (double_vec3d));
	memcpy (&attitude [1][0], &y, sizeof (double_vec3d));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void collision_check_with_ground (rigid_body_dynamics *rb, int index)
{

	//rb->collision_type = COLLISION_TYPE_CYLINDER;

	rb->collided_flag = 0;

	switch (rb->collision_type)
	{

		case COLLISION_TYPE_BOUNDING_BOX:
		{
			//terrain_3d_point_data
				//terrain_info;

			double_vec3d
				collision_points [100];

			double_vec3d
				collision_point,
				face_normal,
				world_point;
		
			double
				terrain_elevation;
		
			int
				collision_count,
				loop;

			//object
				//*obj2;

			//memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

			memset (collision_points, 0, sizeof (double_vec3d) * 100);

			collision_count = 0;
		
			for (loop = 0; loop < rb->number_of_collision_points; loop ++)
			{
		
	  			// rotate into world space
				multiply_double_matrix3x3_double_vec3d (&collision_point, rb->attitude, &rb->collision_points [loop]);
		
				world_point.x = rb->position_cm [index].x + (collision_point.x * rb->scaling.x);
				world_point.y = rb->position_cm [index].y + (collision_point.y * rb->scaling.y);
				world_point.z = rb->position_cm [index].z + (collision_point.z * rb->scaling.z);
		
				//
				// Terrain collision
				//
		
				//get_3d_terrain_point_data (world_point.x, world_point.z, &terrain_info);
		
				terrain_elevation = 0.0;//get_3d_terrain_point_data_elevation (&terrain_info);
		
				if (terrain_elevation >= world_point.y)
				{
		
					//memcpy (&face_normal, get_3d_terrain_point_data_normal (&terrain_info), sizeof (double_vec3d));
					face_normal.x = 0.0;
					face_normal.y = 1.0;
					face_normal.z = 0.0;

					create_arrow ("CENTRE_ARROW", &world_point, &face_normal, 1.0);
		
					//debug_log ("BODY: collision with point %d rb = %d (index %d)", loop, rb, index);
		
					rb->position_cm [index].y = terrain_elevation + (rb->position_cm [index].y - world_point.y) + 0.0;

					collision_points [collision_count] = rb->collision_points [loop];

					collision_count ++;
					resolve_collision (rb, NULL, &rb->collision_points [loop], &face_normal, index, 0);
				}
			}

			if (collision_count > 0)
			{

				double_vec3d
					average_collision_point;

				// average collision point
		
				average_collision_point.x = 0.0;
				average_collision_point.y = 0.0;
				average_collision_point.z = 0.0;

				for (loop = 0; loop < collision_count; loop ++)
				{

					average_collision_point.x += collision_points [loop].x;
					average_collision_point.y += collision_points [loop].y;
					average_collision_point.z += collision_points [loop].z;
				}

				average_collision_point.x /= collision_count;
				average_collision_point.y /= collision_count;
				average_collision_point.z /= collision_count;
		
				//resolve_collision (rb, NULL, &average_collision_point, &face_normal, index, 0);
			}
		
			//
			// inter-object collision
			//
/*
			obj2 = get_object_list_head ();

			while (obj2)
			{
		
				if (obj1 != obj2)
				{
		
					if (get_object_object_bounding_collision_point (obj2, obj1, &collision_point, &face_normal))
					{
		
						//resolve_collision (obj1, rb, obj2, obj2->rigid_body [0], &collision_point, &face_normal, index, 0);
					}
				}
		
				obj2 = obj2->next;
			}
			*/

			break;
		}

		case COLLISION_TYPE_CYLINDER:
		{

			//terrain_3d_point_data
				//terrain_info;

			double_vec3d
				collision_point,
				face_normal;
		
			double
				radius,
				terrain_elevation;
		
			//object
				//*obj2;

			//memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

			radius = sqrt ((rb->collision_points [0].x * rb->collision_points [0].x) + (rb->collision_points [0].y * rb->collision_points [0].y));

			radius *= rb->scaling.y;
	
			//
			// Terrain collision
			//
	
			//get_3d_terrain_point_data (world_point.x, world_point.z, &terrain_info);
	
			terrain_elevation = 0.0;//get_3d_terrain_point_data_elevation (&terrain_info);
	
			//memcpy (&face_normal, get_3d_terrain_point_data_normal (&terrain_info), sizeof (double_vec3d));
			face_normal.x = 0.0;
			face_normal.y = 1.0;
			face_normal.z = 0.0;

			// Assuming flat ground... needs to check distance along terrain normal.

			if (terrain_elevation >= rb->position_cm [index].y - radius)
			{
	
				rb->position_cm [index].y = terrain_elevation + radius;

				collision_point.x = -face_normal.x * radius;
				collision_point.y = -face_normal.y * radius;
				collision_point.z = -face_normal.z * radius;

				multiply_transpose_double_matrix3x3_double_vec3d (&collision_point, rb->attitude, &collision_point);
	
				resolve_collision (rb, NULL, &collision_point, &face_normal, index, 0);
			}
		
			//
			// inter-object collision
			//

			/*
			obj2 = get_object_list_head ();
		
			while (obj2)
			{
		
				if (obj1 != obj2)
				{
		
					if (get_object_object_bounding_collision_point (obj2, obj1, &collision_point, &face_normal))
					{
		
						//resolve_collision (obj1, rb, obj2, obj2->rigid_body [0], &collision_point, &face_normal, index, 0);
					}
				}
		
				obj2 = obj2->next;
			}
			*/


			break;
		}

		default:
		{

			debug_fatal ("BODY: Unknown collision type %d", rb->collision_type);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resolve_collision (rigid_body_dynamics *rb1, rigid_body_dynamics *rb2, double_vec3d *collision_point, double_vec3d *face_normal, int index1, int index2)
{

	double
		value,
		impulse_numerator,
		impulse_denominator,
		inverse_mass1,
		inverse_mass2,
		dot1,
		dot2;

	double_vec3d
		impulse_force,
		inertia_result,
		collision_point1,
		collision_point2,
		cross_result,
		points_velocity,
		point_velocity1,
		point_velocity2;

	// velocity 1

	// rotate into relative world space

	multiply_double_matrix3x3_double_vec3d (&collision_point1, rb1->attitude, collision_point);

	get_3d_double_vector_cross_product (&cross_result, &collision_point1, &rb1->angular_velocity [index1]);

	point_velocity1.x = rb1->velocity_cm [index1].x + cross_result.x;
	point_velocity1.y = rb1->velocity_cm [index1].y + cross_result.y; 
	point_velocity1.z = rb1->velocity_cm [index1].z + cross_result.z;

	// velocity 2

	point_velocity2.x = 0;
	point_velocity2.y = 0;
	point_velocity2.z = 0;

	if (rb2)
	{ 	

		collision_point2 = collision_point1;

		collision_point2.x += rb1->position_cm->x;
		collision_point2.y += rb1->position_cm->y;
		collision_point2.z += rb1->position_cm->z;
		collision_point2.x -= rb2->position_cm->x;
		collision_point2.y -= rb2->position_cm->y;
		collision_point2.z -= rb2->position_cm->z;

		// rotate into relative world space

		get_3d_double_vector_cross_product (&cross_result, &collision_point2, &rb2->angular_velocity [0]);
	
		point_velocity2.x = rb2->velocity_cm [index1].x + cross_result.x;
		point_velocity2.y = rb2->velocity_cm [index1].y + cross_result.y;
		point_velocity2.z = rb2->velocity_cm [index1].z + cross_result.z;
	}

	// find body's relative velocity

	points_velocity.x = point_velocity1.x - point_velocity2.x;
	points_velocity.y = point_velocity1.y - point_velocity2.y;
	points_velocity.z = point_velocity1.z - point_velocity2.z;

	if (!check_zero_3d_double_vector (&points_velocity))
	{
	
		value = get_3d_double_vector_dot_product (&points_velocity, face_normal);
	
		if (value <= 0.0)
		{

			//
			//
			//

			dot1 = (points_velocity.x * face_normal->x) + (points_velocity.y * face_normal->y) + (points_velocity.z * face_normal->z);
	
			impulse_numerator = - (1.0 + rb1->coefficient_of_restitution) * dot1;
	
			get_3d_double_vector_cross_product (&cross_result, &collision_point1, face_normal);
			multiply_double_matrix3x3_double_vec3d (&inertia_result, rb1->inverse_world_inertia_tensor, &cross_result);
			get_3d_double_vector_cross_product (&cross_result, &inertia_result, &collision_point1);
	
			dot1 = (cross_result.x * face_normal->x) + (cross_result.y * face_normal->y) + (cross_result.z * face_normal->z);
	
  			inverse_mass1 = rb1->inverse_mass;
			inverse_mass2 = 0.0;
			dot2 = 0.0;
	
			if (rb2)
			{
		
				get_3d_double_vector_cross_product (&cross_result, &collision_point2, face_normal);
				multiply_double_matrix3x3_double_vec3d (&inertia_result, rb2->inverse_world_inertia_tensor, &cross_result);
				get_3d_double_vector_cross_product (&cross_result, &inertia_result, &collision_point2);
		
				dot2 = (cross_result.x * face_normal->x) + (cross_result.y * face_normal->y) + (cross_result.z * face_normal->z);
	
				inverse_mass2 = rb2->inverse_mass;
			}
	
			impulse_denominator = inverse_mass1 + inverse_mass2 + dot1 + dot2;

			impulse_force.x = (impulse_numerator / impulse_denominator) * face_normal->x;
			impulse_force.y = (impulse_numerator / impulse_denominator) * face_normal->y;
			impulse_force.z = (impulse_numerator / impulse_denominator) * face_normal->z;
	
			// apply force linearly

			rb1->velocity_cm [index1].x += inverse_mass1 * impulse_force.x;
			rb1->velocity_cm [index1].y += inverse_mass1 * impulse_force.y;
			rb1->velocity_cm [index1].z += inverse_mass1 * impulse_force.z;

			// apply force angularly
			
			get_3d_double_vector_cross_product (&cross_result, &impulse_force, collision_point);

			rb1->angular_momentum [index1].x += cross_result.x;
			rb1->angular_momentum [index1].y += cross_result.y;
			rb1->angular_momentum [index1].z += cross_result.z;
	
			// auxilary variables
	
			//multiply_double_matrix3x3_double_vec3d (&rb1->angular_velocity [index1], rb1->inverse_world_inertia_tensor, &rb1->angular_momentum [index1]);
			{

				double_matrix3x3
					result;

				// inverse_world_inertia_tensor
				multiply_double_matrix3x3_double_matrix3x3 (result, rb1->attitude, rb1->inverse_body_inertia_tensor);
	
				// angular_velocity
				multiply_double_matrix3x3_double_vec3d (&rb1->angular_velocity [index1], result, &rb1->angular_momentum [index1]);
			}

			// flag for friction
	
			rb1->collision_normal [rb1->collided_flag] = *face_normal;
			rb1->collision_point [rb1->collided_flag] = collision_point1;

			rb1->collided_flag ++;
	
			if (rb2)
			{
	
				// apply force
				
				get_3d_double_vector_cross_product (&cross_result, &impulse_force, &collision_point2);
				rb2->angular_momentum [index2].x -= cross_result.x;
				rb2->angular_momentum [index2].y -= cross_result.y;
				rb2->angular_momentum [index2].z -= cross_result.z;
	
				// auxilary variables
	
				rb2->velocity_cm [index2].x -= rb2->inverse_mass * impulse_force.x;
				rb2->velocity_cm [index2].y -= rb2->inverse_mass * impulse_force.y;
				rb2->velocity_cm [index2].z -= rb2->inverse_mass * impulse_force.z;
		
				multiply_double_matrix3x3_double_vec3d (&rb2->angular_velocity [index2], rb2->inverse_world_inertia_tensor, &rb2->angular_momentum [index2]);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_object_bounding_collision_point (object *obj1, object *obj2, double_vec3d *double_position, double_vec3d *double_face_normal)
{

	vec3d
		last_bounding_box,
		position,
		face_normal,
		a [8],
		q [8],
		p [8];

	struct OBJECT_3D_BOUNDS
		*bounding_box = nullptr;

	int
		return_flag,
		loop;

	position.x = double_position->x;
	position.y = double_position->y;
	position.z = double_position->z;

	face_normal.x = double_face_normal->x;
	face_normal.y = double_face_normal->y;
	face_normal.z = double_face_normal->z;

	return_flag = FALSE;

	bounding_box = get_object_3d_bounding_box (obj2->inst3d->object_number);

	//
	// rotate object 2 vertices bounding box
	//

	p [0].x = bounding_box->xmin;
	p [0].y = bounding_box->ymin;
	p [0].z = bounding_box->zmin;

	p [1].x = bounding_box->xmin;
	p [1].y = bounding_box->ymin;
	p [1].z = bounding_box->zmax;

	p [2].x = bounding_box->xmax;
	p [2].y = bounding_box->ymin;
	p [2].z = bounding_box->zmax;

	p [3].x = bounding_box->xmax;
	p [3].y = bounding_box->ymin;
	p [3].z = bounding_box->zmin;

	p [4].x = bounding_box->xmin;
	p [4].y = bounding_box->ymax;
	p [4].z = bounding_box->zmin;

	p [5].x = bounding_box->xmin;
	p [5].y = bounding_box->ymax;
	p [5].z = bounding_box->zmax;

	p [6].x = bounding_box->xmax;
	p [6].y = bounding_box->ymax;
	p [6].z = bounding_box->zmax;

	p [7].x = bounding_box->xmax;
	p [7].y = bounding_box->ymax;
	p [7].z = bounding_box->zmin;

	for (loop = 0; loop < 8; loop ++)
	{

		// coords are in obj2 space
	
		// transform into world space, wrt obj2
		multiply_double_matrix3x3_vec3d (&p [loop], obj2->rigid_body->attitude, &p [loop]);
	
		// move into world coords 
		p [loop].x += obj2->position.x;
		p [loop].y += obj2->position.y;
		p [loop].z += obj2->position.z;

		// store world coords
		q [loop] = p [loop];

		// move into world space, wrt obj1
		obj2->rigid_body [0].last_bounding_box [loop].x -= obj1->position.x;
		obj2->rigid_body [0].last_bounding_box [loop].y -= obj1->position.y;
		obj2->rigid_body [0].last_bounding_box [loop].z -= obj1->position.z;

		p [loop].x -= obj1->position.x;
		p [loop].y -= obj1->position.y;
		p [loop].z -= obj1->position.z;

		// transform into obj1 space
		multiply_transpose_double_matrix3x3_double_vec3d (&obj2->rigid_body->last_bounding_box [loop], obj1->rigid_body->attitude, &obj2->rigid_body->last_bounding_box [loop]);

		multiply_transpose_double_matrix3x3_vec3d (&p [loop], obj1->rigid_body->attitude, &p [loop]);
	}

	// store last frames positions if 1st time in
	if (!obj2->rigid_body->valid_last_bounding_box)
	{

		memcpy (&obj2->rigid_body->last_bounding_box, &q, sizeof (double_vec3d) * 8);

		obj2->rigid_body->valid_last_bounding_box = TRUE;

		return FALSE;
	}

	//
	// get object1 bounding box
	//

	bounding_box = get_object_3d_bounding_box (obj1->inst3d->object_number);

	a [0].x = bounding_box->xmin;
	a [0].y = bounding_box->ymin;
	a [0].z = bounding_box->zmin;

	a [1].x = bounding_box->xmin;
	a [1].y = bounding_box->ymin;
	a [1].z = bounding_box->zmax;

	a [2].x = bounding_box->xmax;
	a [2].y = bounding_box->ymin;
	a [2].z = bounding_box->zmax;

	a [3].x = bounding_box->xmax;
	a [3].y = bounding_box->ymin;
	a [3].z = bounding_box->zmin;

	a [4].x = bounding_box->xmin;
	a [4].y = bounding_box->ymax;
	a [4].z = bounding_box->zmin;

	a [5].x = bounding_box->xmin;
	a [5].y = bounding_box->ymax;
	a [5].z = bounding_box->zmax;

	a [6].x = bounding_box->xmax;
	a [6].y = bounding_box->ymax;
	a [6].z = bounding_box->zmax;

	a [7].x = bounding_box->xmax;
	a [7].y = bounding_box->ymax;
	a [7].z = bounding_box->zmin;

	// perform collision checks
	for (loop = 0; loop < 8; loop ++)
	{

		last_bounding_box.x = obj2->rigid_body->last_bounding_box [loop].x;
		last_bounding_box.y = obj2->rigid_body->last_bounding_box [loop].y;
		last_bounding_box.z = obj2->rigid_body->last_bounding_box [loop].z;
	
		if (get_3d_line_quad_intersection (&p [loop], &last_bounding_box, &a[0], &a[3], &a[2], &a[1], &position, &face_normal))
		{

			return_flag = TRUE;

			break;
		}

		if (get_3d_line_quad_intersection (&p [loop], &last_bounding_box, &a[3], &a[7], &a[6], &a[2], &position, &face_normal))
		{

			return_flag = TRUE;

			break;
		}
	
		if (get_3d_line_quad_intersection (&p [loop], &last_bounding_box, &a[7], &a[4], &a[5], &a[6], &position, &face_normal))
		{

			return_flag = TRUE;

			break;
		}

		if (get_3d_line_quad_intersection (&p [loop], &last_bounding_box, &a[4], &a[0], &a[1], &a[5], &position, &face_normal))
		{

			return_flag = TRUE;

			break;
		}
	
		if (get_3d_line_quad_intersection (&p [loop], &last_bounding_box, &a[1], &a[2], &a[6], &a[5], &position, &face_normal))
		{

			return_flag = TRUE;

			break;
		}

		if (get_3d_line_quad_intersection (&p [loop], &last_bounding_box, &a[0], &a[4], &a[7], &a[3], &position, &face_normal))
		{

			return_flag = TRUE;

			break;
		}
	}

	// store this frames positions for next frame
	memcpy (&obj2->rigid_body->last_bounding_box, &q, sizeof (double_vec3d) * 8);

	// if collision
	if (return_flag)
	{

		// normal in world coords
		multiply_double_matrix3x3_double_vec3d (double_face_normal, obj1->rigid_body->attitude, double_face_normal);
	}

	return return_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_rigid_body_system (void)
{

	dynamic_forces
		*force = nullptr;

	rigid_body_dynamics
		*current_rb = nullptr;

	FILE
		*file_ptr = nullptr;

	int
		count,
		depth_loop,
		name_length;

	file_ptr = fopen ("r_bodies.bin", "wb");

	count = 0;

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		count ++;

		current_rb = current_rb->next;
	}

	fprintf (file_ptr, "%d", count);

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		// data

		fwrite (current_rb, sizeof (rigid_body_dynamics), 1, file_ptr);

		// name

		if (current_rb->name)
		{

			name_length = strlen (current_rb->name) + 1;

			fprintf (file_ptr, "%d", name_length);

			fwrite (current_rb->name, name_length, 1, file_ptr);
		}

		// collision_points

		fwrite (current_rb->collision_points, sizeof (double_vec3d) * current_rb->number_of_collision_points, 1, file_ptr);

		// forces

		depth_loop = 0;

		while (depth_loop < RB_DEPTH)
		{
	
			count = 0;
	
			force = current_rb->forces [depth_loop];
	
			while (force)
			{
	
				count ++;
	
				force = force->next;
			}
	
			fprintf (file_ptr, "%d", count);
	
			force = current_rb->forces [depth_loop];
	
			while (force)
			{
	
				fwrite (force, sizeof (dynamic_forces), 1, file_ptr);
	
				if (force->name)
				{
		
					name_length = strlen (force->name) + 1;
		
					fprintf (file_ptr, "%d", name_length);
		
					fwrite (force->name, name_length, 1, file_ptr);
				}
	
				force = force->next;
			}

			depth_loop ++;
		}

		current_rb = current_rb->next;
	}

	fclose (file_ptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_rigid_body_system (void)
{

	dynamic_forces
		*force = nullptr,
		*last_force = nullptr;

	rigid_body_dynamics
		*current_rb = nullptr,
		*last_current_rb = nullptr;

	FILE
		*file_ptr = nullptr;

	int
		loop,
		count,
		depth_loop,
		force_count,
		name_length;

	last_current_rb = NULL;
	
	deinitialise_rigid_body_system ();

	file_ptr = fopen ("r_bodies.bin", "rb");

	fscanf (file_ptr, "%d", &count);

	for (loop = 0; loop < count; loop ++)
	{

		current_rb = (rigid_body_dynamics *) malloc_heap_mem (sizeof (rigid_body_dynamics));

		// data

		fread (current_rb, sizeof (rigid_body_dynamics), 1, file_ptr);

		// name

		fscanf (file_ptr, "%d", &name_length);

		if (name_length > 0)
		{

			current_rb->name = (char *) malloc_heap_mem (sizeof (char) * (name_length));

			fread (current_rb->name, name_length, 1, file_ptr);
		}

		// collision_points

		current_rb->collision_points = (double_vec3d *) malloc_heap_mem (sizeof (double_vec3d) * (current_rb->number_of_collision_points));

		fread (current_rb->collision_points, sizeof (double_vec3d) * current_rb->number_of_collision_points, 1, file_ptr);

		// forces

		depth_loop = 0;

		while (depth_loop < RB_DEPTH)
		{
	
			last_force = NULL;
	
			fscanf (file_ptr, "%d", &force_count);

			current_rb->forces [depth_loop] = NULL;
	
			if (force_count > 0)
			{

				while (force_count > 0)
				{
		
					force = (dynamic_forces *) malloc_heap_mem (sizeof (dynamic_forces));
		
					fread (force, sizeof (dynamic_forces), 1, file_ptr);
		
					fscanf (file_ptr, "%d", &name_length);
		
					if (name_length > 0)
					{
			
						force->name = (char *) malloc_heap_mem (sizeof (char) * (name_length));
			
						fread (force->name, name_length, 1, file_ptr);
					}
		
					force->next = last_force;
		
					last_force = force;
	
					force_count --;
				}
	
				current_rb->forces [depth_loop] = force;
			}

			depth_loop ++;
		}

		// sort out list links

		current_rb->next = last_current_rb;

		current_rb->prev = NULL;

		if (last_current_rb)
		{

			last_current_rb->prev = current_rb;
		}

		last_current_rb = current_rb;
	}

	rigid_body_list_head = current_rb;

	fclose (file_ptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_vectored_debug_3d_object (double_vec3d *position, double_vec3d *direction, int object_number, double scaling)
{

	object_3d_instance
		*inst3d = nullptr;

	double_vec3d
		dir;

	inst3d = construct_temporary_3d_object (object_number, FALSE);
	
	if (inst3d)
	{

		dir = *direction;

		normalise_any_3d_double_vector (&dir);

		inst3d->vp.position.x = position->x;
		inst3d->vp.position.y = position->y;
		inst3d->vp.position.z = position->z;

		get_matrix3x3_from_unit_double_vec3d_and_roll (inst3d->vp.attitude, &dir, 0.0);

		inst3d->relative_scale.x = scaling;
		inst3d->relative_scale.y = scaling;
		inst3d->relative_scale.z = scaling;

		inst3d->object_has_shadow = FALSE;

		insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, inst3d);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ARROW_TYPE
{

	int
		object;

	double_vec3d
		position,
		direction;

	double
		size,
		lifetime;

	struct ARROW_TYPE
		*next = nullptr;
};

typedef struct ARROW_TYPE arrow_type;

arrow_type
	*arrow_list_head = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_arrow (char *name, double_vec3d *position, double_vec3d *direction, double size)
{

	arrow_type
		*new_arrow = nullptr;

	int
		object;

	if (check_zero_3d_double_vector (direction))
	{

		return;
	}

	new_arrow = (arrow_type *) malloc_heap_mem (sizeof (arrow_type));

	object = get_object_3d_index_from_name (name);

	new_arrow->object = object;

	new_arrow->position = *position;

	new_arrow->direction = *direction;

	new_arrow->size = size;

	new_arrow->next = arrow_list_head;

	new_arrow->lifetime = 0.01;

	arrow_list_head = new_arrow;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_arrows (void)
{

	arrow_type
		*this_arrow = nullptr,
		*prev_arrow = nullptr,
		*arrow = nullptr;

	arrow = arrow_list_head;

	this_arrow = NULL;

	prev_arrow = NULL;

	while (arrow)
	{

		this_arrow = arrow;

		arrow = arrow->next;

		create_vectored_debug_3d_object (&this_arrow->position, &this_arrow->direction, this_arrow->object, this_arrow->size);

		this_arrow->lifetime -= get_rigid_body_delta_time ();

		if (this_arrow->lifetime < 0.0)
		{

			if (prev_arrow)
			{
			

				prev_arrow->next = this_arrow->next;
			}
			else
			{

				arrow_list_head = this_arrow->next;
			}

			free_mem (this_arrow);
		}
		else
		{

			prev_arrow = this_arrow;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct LINE_TYPE
{

	double_vec3d
		position1,
		position2;

	double
		lifetime;

	struct LINE_TYPE
		*next = nullptr;
};

typedef struct LINE_TYPE line_type;

line_type
	*line_list_head = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_line (double_vec3d *position1, double_vec3d *position2)
{

	line_type
		*new_line = nullptr;

	new_line = (line_type *) malloc_heap_mem (sizeof (line_type));

	new_line->position1 = *position1;

	new_line->position2 = *position2;

	new_line->next = line_list_head;

	new_line->lifetime = 0.01;

	line_list_head = new_line;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_lines (void)
{

	line_type
		*this_line = nullptr,
		*prev_line = nullptr,
		*line = nullptr;

	vec3d
		points [2];

	rgb_colour
		cable_colour;

	cable_colour.r = 0.0;
	cable_colour.g = 255.0;
	cable_colour.b = 255.0;
	cable_colour.a = 255.0;

	line = line_list_head;

	this_line = NULL;

	prev_line = NULL;

	while (line)
	{

		this_line = line;

		line = line->next;

		points [0].x = this_line->position1.x;
		points [0].y = this_line->position1.y;
		points [0].z = this_line->position1.z;

		points [1].x = this_line->position2.x;
		points [1].y = this_line->position2.y;
		points [1].z = this_line->position2.z;

		insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points);

		this_line->lifetime -= get_rigid_body_delta_time ();

		if (this_line->lifetime < 0.0)
		{

			if (prev_line)
			{
			

				prev_line->next = this_line->next;
			}
			else
			{

				line_list_head = this_line->next;
			}

			free_mem (this_line);
		}
		else
		{

			prev_line = this_line;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void copy_rigid_body (rigid_body_dynamics *rb, int source, int target)
{

	rb->position_cm [target] = rb->position_cm [source];
	rb->velocity_cm [target] = rb->velocity_cm [source];
	rb->acceleration_cm [target] = rb->acceleration_cm [source];

	rb->angular_momentum [target] = rb->angular_momentum [source];
	rb->angular_velocity [target] = rb->angular_velocity [source];

	rb->linear_force [target] = rb->linear_force [source];
	rb->torque [target] = rb->torque [source];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double get_total_rigid_body_energies (void)
{

	double
		terrain_elevation,
		linear_velocity_mag,
		angular_velocity_mag,
		total_velocity,
		kinetic_energy,
		potential_energy,
		total_energy;

	rigid_body_dynamics
		*current_rb = nullptr;

	//ke = 0.5mv^2
	//pe = mgh

	total_energy = 0.0;

	current_rb = rigid_body_list_head;

	while (current_rb)
	{

		linear_velocity_mag = get_3d_double_vector_magnitude (&current_rb->velocity_cm [0]);

		angular_velocity_mag = get_3d_double_vector_magnitude (&current_rb->angular_velocity [0]);

		total_velocity = linear_velocity_mag + angular_velocity_mag;

		kinetic_energy = 0.5 * current_rb->mass * (total_velocity * total_velocity);

		terrain_elevation = 0.0;

		potential_energy = current_rb->mass * G * (current_rb->position_cm [0].y - terrain_elevation);

		total_energy += (kinetic_energy + potential_energy);

		//debug_log ("BODY: total = %f, ke = %f, pe = %f", total_energy, kinetic_energy, potential_energy);

		current_rb = current_rb->next;
	}

	return total_energy;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// temp function

double get_object_total_mass (rigid_body_dynamics *rb)
{

	double
		mass;

	rigid_body_dynamics
		*this_rb = nullptr;

	mass = 0.0;

	this_rb = rb;

	while (this_rb->prev)
	{

		this_rb = this_rb->prev;
	}

	while (this_rb)
	{

		mass += this_rb->mass;

		this_rb = this_rb->next;
	}

	return mass;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_rigid_body_bounding_box (rigid_body_dynamics *rb)
{

	// draw bounding box

	rgb_colour
		cable_colour;

	double_vec3d
		start_position,
		end_position;

	vec3d
		points [2];

	double
		xmin,
		ymin,
		zmin,
		xmax,
		ymax,
		zmax;

	cable_colour.r = 0.0;
	cable_colour.g = 255.0;
	cable_colour.b = 255.0;
	cable_colour.a = 255.0;

	xmin = rb->xmin;
	ymin = rb->ymin;
	zmin = rb->zmin;

	xmax = rb->xmax;
	ymax = rb->ymax;
	zmax = rb->zmax;

	// 0 -> 1

	start_position.x = xmin;
	start_position.y = ymin;
	start_position.z = zmin;

	end_position.x = xmin;
	end_position.y = ymin;
	end_position.z = zmax;

	multiply_double_matrix3x3_double_vec3d (&start_position, rb->attitude, &start_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 1 -> 2

	start_position = end_position;

	end_position.x = xmax;
	end_position.y = ymin;
	end_position.z = zmax;

	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 2 -> 3

	start_position = end_position;

	end_position.x = xmax;
	end_position.y = ymin;
	end_position.z = zmin;

	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 3 -> 1

	start_position = end_position;

	end_position.x = xmin;
	end_position.y = ymin;
	end_position.z = zmin;

	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 5 -> 6

	start_position.x = xmin;
	start_position.y = ymax;
	start_position.z = zmin;

	end_position.x = xmin;
	end_position.y = ymax;
	end_position.z = zmax;

	multiply_double_matrix3x3_double_vec3d (&start_position, rb->attitude, &start_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 6 -> 7

	start_position = end_position;

	end_position.x = xmax;
	end_position.y = ymax;
	end_position.z = zmax;

	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 7 -> 8

	start_position = end_position;

	end_position.x = xmax;
	end_position.y = ymax;
	end_position.z = zmin;

	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 8 -> 5

	start_position = end_position;

	end_position.x = xmin;
	end_position.y = ymax;
	end_position.z = zmin;

	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 0 -> 5

	start_position.x = xmin;
	start_position.y = ymin;
	start_position.z = zmin;

	end_position.x = xmin;
	end_position.y = ymax;
	end_position.z = zmin;

	multiply_double_matrix3x3_double_vec3d (&start_position, rb->attitude, &start_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 1 -> 6

	start_position.x = xmin;
	start_position.y = ymin;
	start_position.z = zmax;

	end_position.x = xmin;
	end_position.y = ymax;
	end_position.z = zmax;

	multiply_double_matrix3x3_double_vec3d (&start_position, rb->attitude, &start_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 2 -> 7

	start_position.x = xmax;
	start_position.y = ymin;
	start_position.z = zmax;

	end_position.x = xmax;
	end_position.y = ymax;
	end_position.z = zmax;

	multiply_double_matrix3x3_double_vec3d (&start_position, rb->attitude, &start_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );

	// 3 -> 6

	start_position.x = xmax;
	start_position.y = ymin;
	start_position.z = zmin;

	end_position.x = xmax;
	end_position.y = ymax;
	end_position.z = zmin;

	multiply_double_matrix3x3_double_vec3d (&start_position, rb->attitude, &start_position);
	multiply_double_matrix3x3_double_vec3d (&end_position, rb->attitude, &end_position);

	points [0].x = rb->position_cm [0].x + start_position.x;
	points [0].y = rb->position_cm [0].y + start_position.y;
	points [0].z = rb->position_cm [0].z + start_position.z;

	points [1].x = rb->position_cm [1].x + end_position.x;
	points [1].y = rb->position_cm [1].y + end_position.y;
	points [1].z = rb->position_cm [1].z + end_position.z;

	insert_zbiased_polyline_into_3d_scene (2, 0.0, TRUE, cable_colour, points );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
